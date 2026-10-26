use crate::{
    profile::Profile,
    protocol::{Frame, decode_frame, encode_command},
    recording::{Recordings, Routes},
    storage::Format,
};
use anyhow::{Context, Result, bail, ensure};
use serde::{Deserialize, Serialize};
use serde_json::{Value, json};
use std::{
    collections::VecDeque,
    fs::{self, File, OpenOptions},
    io::{Read, Write},
    net::{Shutdown, SocketAddr, TcpListener, TcpStream, ToSocketAddrs},
    path::PathBuf,
    sync::{
        Arc, Mutex,
        atomic::{AtomicBool, Ordering},
    },
    thread,
    time::{Duration, Instant, SystemTime, UNIX_EPOCH},
};

pub const DEFAULT_DEVICE_IP: &str = "192.168.1.233";
pub const DEFAULT_DEVICE_PORT: u16 = 1000;
pub const DEFAULT_ENDPOINT: &str = "127.0.0.1:19740";
const MAX_MESSAGE: usize = 65536;
#[derive(Debug, Serialize, Deserialize)]
#[serde(tag = "op", rename_all = "snake_case", deny_unknown_fields)]
pub enum Operation {
    Connect { ip: String, port: u16 },
    Status,
    Observables,
    Stop,
    EnableSystem,
    EnableControl,
    ErrorReset,
    SetVariable { name: String, value: f32 },
    SetObservable { name: String, channel: u32 },
    Button { number: u32 },
    SendAck { enabled: bool },
    StartLogging,
    StopLogging,
    StartLoggingSlowData,
    StopLoggingSlowData,
    Shutdown,
}
#[derive(Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Request {
    pub api_version: u32,
    pub command: Operation,
}
#[derive(Clone, Debug)]
pub struct Config {
    pub device: Option<String>,
    pub endpoint: String,
    pub profile: Profile,
    pub output: Option<PathBuf>,
    pub format: Format,
    pub ack: bool,
}
#[derive(Default, Serialize)]
struct State {
    connected: bool,
    device: Option<String>,
    frames: u64,
    samples: u64,
    status: u32,
    platform_state: Option<String>,
    commands_sent: u64,
    ack_sent: u64,
    error: Option<String>,
}
fn now_ns() -> u64 {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap_or_default()
        .as_nanos() as u64
}
fn local_address(s: &str) -> Result<SocketAddr> {
    let addr: SocketAddr = s
        .parse()
        .context("control endpoint must be a numeric loopback address:port")?;
    ensure!(addr.ip().is_loopback(), "control endpoint must be loopback");
    Ok(addr)
}
fn read_line(stream: &mut TcpStream, timeout: Duration) -> Result<Vec<u8>> {
    let mut data = Vec::new();
    let mut b = [0u8];
    let started = Instant::now();
    while data.len() < MAX_MESSAGE {
        ensure!(
            started.elapsed() < timeout,
            "control message deadline exceeded"
        );
        ensure!(
            stream.read(&mut b)? != 0,
            "connection closed before newline"
        );
        if b[0] == b'\n' {
            return Ok(data);
        }
        data.push(b[0]);
    }
    bail!("control message exceeds {MAX_MESSAGE} bytes")
}
pub fn request(endpoint: &str, command: Operation) -> Result<Value> {
    let mut socket = TcpStream::connect_timeout(&local_address(endpoint)?, Duration::from_secs(2))?;
    let timeout = Duration::from_secs(if matches!(command, Operation::Connect { .. }) {
        30
    } else {
        5
    });
    socket.set_read_timeout(Some(timeout))?;
    socket.set_write_timeout(Some(Duration::from_secs(2)))?;
    serde_json::to_writer(
        &mut socket,
        &Request {
            api_version: 1,
            command,
        },
    )?;
    socket.write_all(b"\n")?;
    let reply: Value = serde_json::from_slice(&read_line(&mut socket, timeout)?)?;
    ensure!(
        reply["api_version"] == 1,
        "unsupported response API version"
    );
    ensure!(reply["ok"] == true, "{}", reply["error"]);
    Ok(reply)
}
fn send(writer: &Mutex<TcpStream>, id: u32, value: f32) -> Result<()> {
    writer
        .lock()
        .unwrap()
        .write_all(&encode_command(id, value)?)?;
    Ok(())
}

pub fn serve(config: Config, shutdown: Arc<AtomicBool>) -> Result<()> {
    serve_with_ready(config, shutdown, || {})
}

/// Invoke `ready` once this service owns the endpoint and any requested initial connection is ready.
/// The callback must return promptly so control requests can be processed.
pub fn serve_with_ready(
    config: Config,
    shutdown: Arc<AtomicBool>,
    ready: impl FnOnce(),
) -> Result<()> {
    config.profile.validate()?;
    // Claim the control endpoint before touching the device (new device clients replace old ones).
    let listener = TcpListener::bind(local_address(&config.endpoint)?)?;
    listener.set_nonblocking(true)?;
    if let Some(dir) = &config.output {
        ensure!(
            !dir.exists(),
            "run directory already exists: {}",
            dir.display()
        );
    }
    let state = Arc::new(Mutex::new(State::default()));
    let ack = Arc::new(AtomicBool::new(config.ack));
    let mut events: Option<File> = None;
    if let Some(dir) = &config.output {
        fs::create_dir(dir)?;
        fs::write(
            dir.join("run.json"),
            serde_json::to_vec_pretty(&json!({
                "schema_version":4,"run_id":format!("{}-{}",now_ns(),std::process::id()),"started_unix_ns":now_ns(),"device":config.device,
                "profile":config.profile,"format":config.format,
                "time_basis":"seconds from acquisition start; configured sample period; gaps unknown",
                "storage_layout":"explicit_independent_recordings","source":"ultrazohm",
                "software_version":env!("CARGO_PKG_VERSION")
            }))?,
        )?;
        events = Some(
            OpenOptions::new()
                .create_new(true)
                .append(true)
                .open(dir.join("commands.jsonl"))?,
        );
    }
    let mut recordings =
        Recordings::new(config.output.clone(), config.profile.clone(), config.format);
    let routes = recordings.routes.clone();
    let context = ConnectionContext {
        profile: config.profile.clone(),
        shutdown: shutdown.clone(),
        state: state.clone(),
        ack: ack.clone(),
        routes,
    };
    let mut connection = None;
    let mut selections = json!({});
    if let Some(device) = &config.device {
        let (opened, initial) = context.connect(device, &mut events)?;
        connection = Some(opened);
        selections = initial;
    }
    eprintln!("UltraZohm service listening on {}", config.endpoint);
    ready();
    while !shutdown.load(Ordering::SeqCst) {
        if let Some(error) = recordings.error() {
            state.lock().unwrap().error.get_or_insert(error);
            shutdown.store(true, Ordering::SeqCst);
        }
        if connection
            .as_ref()
            .is_some_and(|c| c.acquisition.is_finished())
        {
            shutdown.store(true, Ordering::SeqCst);
            break;
        }
        match listener.accept() {
            Ok((mut socket, _)) => {
                let result: Result<Value> = (|| {
                    // Windows accepted sockets inherit the nonblocking listener mode.
                    // Requests and replies below use blocking I/O with bounded timeouts.
                    socket.set_nonblocking(false)?;
                    socket.set_read_timeout(Some(Duration::from_secs(1)))?;
                    socket.set_write_timeout(Some(Duration::from_secs(1)))?;
                    let req: Request =
                        serde_json::from_slice(&read_line(&mut socket, Duration::from_secs(2))?)?;
                    ensure!(req.api_version == 1, "unsupported API version");
                    let mut wire = None;
                    match &req.command {
                        Operation::Connect { ip, port } => {
                            ensure!(connection.is_none(), "already connected");
                            ensure!(*port != 0, "port must be 1..65535");
                            let address = SocketAddr::new(
                                ip.parse()
                                    .context("device IP must be a numeric IPv4 or IPv6 address")?,
                                *port,
                            );
                            let (opened, initial) =
                                context.connect(&address.to_string(), &mut events)?;
                            connection = Some(opened);
                            selections = initial;
                        }
                        Operation::Status => {
                            return Ok(
                                json!({"api_version":1,"ok":true,"state":*state.lock().unwrap(),"send_ack":ack.load(Ordering::SeqCst),"logging":recordings.status()}),
                            );
                        }
                        Operation::Observables => {
                            let channels: Vec<Value> = (1..=config.profile.channels).map(|channel| {
                                let requested = selections[channel.to_string()].as_str();
                                let entry = requested.and_then(|name| {
                                    config.profile.observables.get_key_value(name).or_else(||
                                        config.profile.observables.get_key_value(&format!("JSO_{name}")))
                                });
                                json!({"channel":channel,
                                    "name":entry.map(|(name, _)| name),
                                    "id":entry.map(|(_, id)| id),
                                    "state":if entry.is_some() {"sent_unconfirmed"} else {"unknown"}})
                            }).collect();
                            return Ok(json!({"api_version":1,"ok":true,
                                "source":"service_requested_assignments",
                                "device_readback":false,"channels":channels}));
                        }
                        Operation::StartLogging => {
                            ensure!(connection.is_some(), "not connected; use connect first");
                            recordings.start(false, &selections)?;
                        }
                        Operation::StopLogging => recordings.stop(false)?,
                        Operation::StartLoggingSlowData => {
                            ensure!(connection.is_some(), "not connected; use connect first");
                            recordings.start(true, &selections)?;
                        }
                        Operation::StopLoggingSlowData => recordings.stop(true)?,
                        Operation::Shutdown => {
                            shutdown.store(true, Ordering::SeqCst);
                        }
                        Operation::SendAck { enabled } => {
                            // An immediate zero wakes a paused legacy peer when re-enabling.
                            if *enabled
                                && !ack.load(Ordering::SeqCst)
                                && let Some(c) = &connection
                                && let Err(e) = send(&c.writer, 0, 0.0)
                            {
                                state.lock().unwrap().error =
                                    Some(format!("ACK write failed; outcome unknown: {e}"));
                                shutdown.store(true, Ordering::SeqCst);
                                return Err(e);
                            }
                            ack.store(*enabled, Ordering::SeqCst);
                        }
                        Operation::SetVariable { name, value } => {
                            wire = Some((config.profile.variable(name)?, *value))
                        }
                        Operation::SetObservable { name, channel } => {
                            ensure!(
                                !recordings.active(),
                                "setting observable is not possible when logging is active; stop fast and slow logging first"
                            );
                            wire = Some(config.profile.observable(name, *channel)?)
                        }
                        Operation::Button { number } => {
                            ensure!((1..=8).contains(number), "button must be 1..8");
                            wire = Some((
                                config.profile.command(&format!("My_Button_{number}"))?,
                                0.0,
                            ));
                        }
                        Operation::Stop => wire = Some((config.profile.command("Stop")?, 0.0)),
                        Operation::EnableSystem => {
                            wire = Some((config.profile.command("Enable_System")?, 0.0))
                        }
                        Operation::EnableControl => {
                            wire = Some((config.profile.command("Enable_Control")?, 0.0))
                        }
                        Operation::ErrorReset => bail!(
                            "Error_Reset is a no-op in this firmware; use stop to leave error state"
                        ),
                    }
                    if let Some((id, value)) = wire {
                        let connected = connection
                            .as_ref()
                            .context("not connected; use connect first")?;
                        encode_command(id, value)?; // Validation errors must not terminate acquisition.
                        if let Err(e) = send(&connected.writer, id, value) {
                            state.lock().unwrap().error =
                                Some(format!("command write failed; outcome unknown: {e}"));
                            shutdown.store(true, Ordering::SeqCst);
                            return Err(e);
                        }
                        state.lock().unwrap().commands_sent += 1;
                        if let Operation::SetObservable { name, channel } = &req.command {
                            selections[channel.to_string()] = json!(name);
                        }
                    }
                    if let Some(file) = events.as_mut()
                        && let Err(e) = (|| -> Result<()> {
                            serde_json::to_writer(
                                &mut *file,
                                &json!({"host_unix_ns":now_ns(),"request":req,"wire":wire,"outcome":if wire.is_some(){"sent_unconfirmed"}else{"applied_locally"}}),
                            )?;
                            file.write_all(b"\n")?;
                            file.flush()?;
                            Ok(())
                        })()
                    {
                        state.lock().unwrap().error =
                            Some(format!("command audit failed after send: {e}"));
                        shutdown.store(true, Ordering::SeqCst);
                        return Err(e);
                    }
                    Ok(
                        json!({"api_version":1,"ok":true,"outcome":if wire.is_some(){"sent_unconfirmed"}else{"applied_locally"},"logging":recordings.status()}),
                    )
                })();
                let response = match result {
                    Ok(v) => v,
                    Err(e) => json!({"api_version":1,"ok":false,"error":format!("{e:#}")}),
                };
                let _ = serde_json::to_writer(&mut socket, &response);
                let _ = socket.write_all(b"\n");
            }
            Err(e) if e.kind() == std::io::ErrorKind::WouldBlock => {
                thread::sleep(Duration::from_millis(5))
            }
            Err(e) => {
                state.lock().unwrap().error = Some(e.to_string());
                shutdown.store(true, Ordering::SeqCst);
            }
        }
    }
    if let Some(Connection {
        writer,
        acquisition,
    }) = connection
    {
        if acquisition.join().is_err() {
            state.lock().unwrap().error = Some("acquisition thread panicked".into());
        }
        let _ = writer.lock().unwrap().shutdown(Shutdown::Both);
    }
    if let Err(e) = recordings.finish() {
        state
            .lock()
            .unwrap()
            .error
            .get_or_insert_with(|| format!("{e:#}"));
    }
    let s = state.lock().unwrap();
    if let Some(dir) = config.output {
        fs::write(
            dir.join("end.json"),
            serde_json::to_vec_pretty(
                &json!({"ended_unix_ns":now_ns(),"state":*s,"complete":s.error.is_none()}),
            )?,
        )?;
    }
    if let Some(e) = &s.error {
        bail!("{e}");
    }
    Ok(())
}

struct Connection {
    writer: Arc<Mutex<TcpStream>>,
    acquisition: thread::JoinHandle<Result<()>>,
}
struct ConnectionContext {
    profile: Profile,
    shutdown: Arc<AtomicBool>,
    state: Arc<Mutex<State>>,
    ack: Arc<AtomicBool>,
    routes: Routes,
}
impl ConnectionContext {
    fn connect(&self, device: &str, events: &mut Option<File>) -> Result<(Connection, Value)> {
        let addr = device
            .to_socket_addrs()?
            .next()
            .context("device has no address")?;
        let mut reader = TcpStream::connect_timeout(&addr, Duration::from_secs(3))
            .with_context(|| format!("could not connect to device {addr}"))?;
        reader.set_nodelay(true)?;
        reader.set_read_timeout(Some(Duration::from_millis(50)))?;
        reader.set_write_timeout(Some(Duration::from_secs(1)))?;
        let writer = Arc::new(Mutex::new(reader.try_clone()?));
        let mut selections = json!({});
        // All names/channels were validated before opening the socket. Apply only
        // selections (never enable/control commands) before accepting user commands.
        for (&channel, name) in &self.profile.initial_channels {
            let (id, value) = self.profile.observable(name, channel)?;
            send(&writer, id, value).with_context(|| {
                format!("initial channel {channel} write failed; outcome unknown")
            })?;
            selections[channel.to_string()] = json!(name);
            self.state.lock().unwrap().commands_sent += 1;
            if let Some(file) = events.as_mut() {
                serde_json::to_writer(
                    &mut *file,
                    &json!({
                        "host_unix_ns":now_ns(),"source":"initial_channels",
                        "request":{"api_version":1,"command":{"op":"set_observable","name":name,"channel":channel}},
                        "wire":[id,value],"outcome":"sent_unconfirmed"
                    }),
                )?;
                file.write_all(b"\n")?;
                file.flush()?;
            }
        }
        {
            let mut state = self.state.lock().unwrap();
            state.connected = true;
            state.device = Some(device.to_string());
        }
        let stopped = self.shutdown.clone();
        let health = self.state.clone();
        let ack_on = self.ack.clone();
        let output = writer.clone();
        let profile = self.profile.clone();
        let routes = self.routes.clone();
        let ring = Arc::new(Mutex::new(VecDeque::<Frame>::with_capacity(64)));
        let acquisition = thread::spawn(move || {
            let result: Result<()> = (|| {
                let mut buf = vec![0; 4 + (profile.channels + 2) * profile.samples_per_packet * 4];
                let mut fill = 0;
                let mut last = Instant::now();
                let mut index = 0;
                while !stopped.load(Ordering::SeqCst) {
                    match reader.read(&mut buf[fill..]) {
                        Ok(0) if stopped.load(Ordering::SeqCst) => break,
                        Ok(0) => bail!("device disconnected with {fill} partial frame bytes"),
                        Ok(n) => {
                            fill += n;
                            last = Instant::now();
                        }
                        Err(e)
                            if matches!(
                                e.kind(),
                                std::io::ErrorKind::WouldBlock | std::io::ErrorKind::TimedOut
                            ) =>
                        {
                            ensure!(
                                last.elapsed() < Duration::from_secs(5),
                                "device stream stalled (partial bytes: {fill})"
                            );
                            continue;
                        }
                        Err(_) if stopped.load(Ordering::SeqCst) => break,
                        Err(e) => return Err(e.into()),
                    }
                    if fill != buf.len() {
                        continue;
                    }
                    let frame = decode_frame(
                        &buf,
                        profile.channels,
                        profile.samples_per_packet,
                        profile.slow_signals.len() as u32,
                    )?;
                    fill = 0;
                    if ack_on.load(Ordering::SeqCst) {
                        send(&output, 0, 0.0)?;
                        health.lock().unwrap().ack_sent += 1;
                    }
                    {
                        let mut s = health.lock().unwrap();
                        s.frames += 1;
                        s.samples += profile.samples_per_packet as u64;
                        s.status = frame.status;
                        s.platform_state = profile
                            .platform_state
                            .decode(frame.status)
                            .map(str::to_owned);
                    }
                    {
                        let mut r = ring.lock().unwrap();
                        if r.len() == 64 {
                            r.pop_front();
                        }
                        r.push_back(frame.clone());
                    }
                    {
                        let destinations = routes.lock().unwrap();
                        for tx in destinations.iter().flatten() {
                            tx.try_send((index, frame.clone())).context("logger queue full or failed; acquisition stopped, samples not silently discarded")?;
                        }
                    }
                    index += profile.samples_per_packet as u64;
                }
                Ok(())
            })();
            {
                let mut state = health.lock().unwrap();
                state.connected = false;
                state.platform_state = None;
            }
            if let Err(e) = &result {
                health
                    .lock()
                    .unwrap()
                    .error
                    .get_or_insert_with(|| format!("acquisition: {e:#}"));
                stopped.store(true, Ordering::SeqCst);
            }
            result
        });
        Ok((
            Connection {
                writer,
                acquisition,
            },
            selections,
        ))
    }
}
