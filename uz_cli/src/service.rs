use crate::{
    data::{DataView, Query, Selection, Source},
    live::{DataOptions, LiveBuffer, MAX_SNAPSHOT_BYTES, selected_columns},
    profile::Profile,
    protocol::{decode_frame, encode_command},
    recording::{Recordings, Routes},
    storage::Format,
};
use anyhow::{Context, Result, bail, ensure};
use serde::{Deserialize, Serialize};
use serde_json::{Value, json};
use std::{
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
/// Resolve session output identically for CLI and embedded Python acquisition.
pub fn session_output(output: Option<PathBuf>) -> Result<PathBuf> {
    if let Some(path) = output {
        return std::path::absolute(path).context("cannot resolve output directory");
    }
    let root = crate::vitis::repository(None).or_else(|_| std::env::current_dir())?;
    let parent = root.join("artifacts/live_logs");
    fs::create_dir_all(&parent)?;
    let now: chrono::DateTime<chrono::Utc> = std::time::SystemTime::now().into();
    Ok(parent.join(now.format("%Y%m%d-%H%M%S-%fZ").to_string()))
}

const MAX_MESSAGE: usize = 65536;
#[derive(Debug, Serialize, Deserialize)]
#[serde(tag = "op", rename_all = "snake_case", deny_unknown_fields)]
pub enum Operation {
    Connect { ip: String, port: u16 },
    Status,
    Catalog,
    Observables,
    GetLiveData { last_n_samples: usize },
    DataInfo { source: Source },
    ReadData { query: Query },
    Recordings,
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
    pub data: DataOptions,
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
    ensure!(
        !matches!(
            command,
            Operation::GetLiveData { .. } | Operation::ReadData { .. }
        ),
        "use get_live_data for binary sample responses"
    );
    let (reply, _) = exchange(endpoint, command, false)?;
    Ok(reply)
}

/// Control metadata followed by Arrow IPC stream bytes; samples are never JSON numbers.
pub fn get_live_data(endpoint: &str, last_n_samples: usize) -> Result<Vec<u8>> {
    let (_, bytes) = exchange(endpoint, Operation::GetLiveData { last_n_samples }, true)?;
    Ok(bytes)
}

pub(crate) fn exchange(
    endpoint: &str,
    command: Operation,
    binary: bool,
) -> Result<(Value, Vec<u8>)> {
    let mut socket = TcpStream::connect_timeout(&local_address(endpoint)?, Duration::from_secs(2))?;
    let timeout = Duration::from_secs(if binary || matches!(command, Operation::Connect { .. }) {
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
    let mut bytes = Vec::new();
    if binary {
        let len = reply["arrow_bytes"]
            .as_u64()
            .context("missing Arrow response length")?;
        ensure!(
            len <= MAX_SNAPSHOT_BYTES as u64,
            "snapshot exceeds response limit"
        );
        bytes.resize(len as usize, 0);
        socket.read_exact(&mut bytes)?;
    }
    Ok((reply, bytes))
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
    mut config: Config,
    shutdown: Arc<AtomicBool>,
    ready: impl FnOnce(),
) -> Result<()> {
    config.profile.validate()?;
    config.data.resolve(config.profile.sample_period_us)?;
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
    let run_id = format!("{}-{}", now_ns(), std::process::id());
    let mut events: Option<File> = None;
    if let Some(dir) = &config.output {
        fs::create_dir(dir)?;
        fs::write(
            dir.join("run.json"),
            serde_json::to_vec_pretty(&json!({
                "schema_version":4,"run_id":run_id,"started_unix_ns":now_ns(),"device":config.device,
                "profile":config.profile,"format":config.format,"data_options":config.data,
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
    let mut recordings = Recordings::new(
        config.output.clone(),
        config.profile.clone(),
        config.format,
        config.data.clone(),
    );
    let ring = Arc::new(Mutex::new(LiveBuffer::new(
        config
            .data
            .buffer_samples
            .expect("buffer capacity resolved"),
    )));
    let routes = recordings.routes.clone();
    let context = ConnectionContext {
        profile: config.profile.clone(),
        shutdown: shutdown.clone(),
        state: state.clone(),
        ack: ack.clone(),
        routes,
        ring: ring.clone(),
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
    let mut query_workers: Vec<thread::JoinHandle<()>> = Vec::new();
    while !shutdown.load(Ordering::SeqCst) {
        query_workers.retain(|worker| !worker.is_finished());
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
                let mut payload = None;
                let mut query_job = None;
                let result: Result<Value> = (|| {
                    // Windows accepted sockets inherit the nonblocking listener mode.
                    // Requests and replies below use blocking I/O with bounded timeouts.
                    socket.set_nonblocking(false)?;
                    socket.set_read_timeout(Some(Duration::from_secs(1)))?;
                    socket.set_write_timeout(Some(Duration::from_secs(5)))?;
                    let req: Request =
                        serde_json::from_slice(&read_line(&mut socket, Duration::from_secs(2))?)?;
                    ensure!(req.api_version == 1, "unsupported API version");
                    let mut wire = None;
                    match &req.command {
                        Operation::ReadData { query } => {
                            ensure!(
                                query_workers.len() < 4,
                                "too many concurrent data queries; retry after a current query finishes"
                            );
                            let view = data_view(
                                &run_id,
                                &query.source,
                                &ring,
                                &recordings,
                                &config.profile,
                                &selections,
                                connection.is_some(),
                                Some(&query.selection),
                            )?;
                            query_job = Some((view, query.clone()));
                            return Ok(json!({}));
                        }
                        Operation::DataInfo { source } => {
                            let view = data_view(
                                &run_id,
                                source,
                                &ring,
                                &recordings,
                                &config.profile,
                                &selections,
                                connection.is_some(),
                                None,
                            )?;
                            return Ok(json!({"api_version":1,"ok":true,"info":view.info}));
                        }
                        Operation::Recordings => {
                            let mut infos = Vec::new();
                            for source in recordings.sources() {
                                infos.push(
                                    data_view(
                                        &run_id,
                                        &source,
                                        &ring,
                                        &recordings,
                                        &config.profile,
                                        &selections,
                                        connection.is_some(),
                                        None,
                                    )?
                                    .info,
                                );
                            }
                            return Ok(json!({"api_version":1,"ok":true,"recordings":infos}));
                        }
                        Operation::GetLiveData { last_n_samples } => {
                            use polars::prelude::*;
                            ensure!(connection.is_some(), "not connected; use connect first");
                            ensure!(*last_n_samples > 0, "last_n_samples must be positive");
                            let columns = selected_columns(&config.profile, &selections)?;
                            // Reserve headroom for Arrow metadata and buffer alignment.
                            let row_bytes = 12 + 4 * columns.len();
                            ensure!(
                                *last_n_samples <= (MAX_SNAPSHOT_BYTES - 65536) / row_bytes,
                                "snapshot exceeds response limit; request fewer samples"
                            );
                            let snapshot = ring.lock().unwrap().snapshot(*last_n_samples)?;
                            let mut df =
                                snapshot.dataframe(config.profile.sample_period_us, &columns)?;
                            let mut bytes = Vec::new();
                            IpcStreamWriter::new(&mut bytes).finish(&mut df)?;
                            ensure!(
                                bytes.len() <= MAX_SNAPSHOT_BYTES,
                                "snapshot exceeds response limit"
                            );
                            let reply = json!({"api_version":1,"ok":true,"rows":snapshot.rows,
                                "arrow_bytes":bytes.len(),"mapping_confirmed":false});
                            payload = Some(bytes);
                            return Ok(reply);
                        }
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
                                json!({"api_version":1,"ok":true,"state":*state.lock().unwrap(),"send_ack":ack.load(Ordering::SeqCst),"logging":recordings.status(),
                                    "data_options":config.data,"buffer_available_samples":ring.lock().unwrap().available()}),
                            );
                        }
                        Operation::Catalog => {
                            return Ok(json!({"api_version":1,"ok":true,
                                "profile":config.profile,
                                "device_readback":false}));
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
                            // Previously retained samples must not acquire the new column labels.
                            ring.lock().unwrap().clear();
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
                if let Some((view, query)) = query_job {
                    query_workers
                        .push(thread::spawn(move || serve_data_query(socket, view, query)));
                    continue;
                }
                let response = match result {
                    Ok(v) => v,
                    Err(e) => json!({"api_version":1,"ok":false,"error":format!("{e:#}")}),
                };
                if serde_json::to_writer(&mut socket, &response).is_ok()
                    && socket.write_all(b"\n").is_ok()
                    && let Some(bytes) = payload
                {
                    let _ = socket.write_all(&bytes);
                }
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
    for worker in query_workers {
        let _ = worker.join();
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

#[allow(clippy::too_many_arguments)] // Immutable service context plus the requested source/window.
fn data_view(
    run_id: &str,
    source: &Source,
    ring: &Mutex<LiveBuffer>,
    recordings: &Recordings,
    profile: &Profile,
    selections: &Value,
    connected: bool,
    selection: Option<&Selection>,
) -> Result<DataView> {
    if let Some(n) = source.recording {
        DataView::recorded(
            run_id,
            source,
            recordings.history(&source.stream, n)?.as_ref(),
            profile,
            selection,
        )
    } else {
        ensure!(connected, "not connected; use connect first");
        DataView::live(run_id, source, ring, profile, selections, selection)
    }
}

fn serve_data_query(mut socket: TcpStream, view: DataView, query: Query) {
    use polars::prelude::*;
    let result = (|| -> Result<(Value, Vec<u8>)> {
        let (mut df, cursor, start, stop) = view.read(&query)?;
        let mut bytes = Vec::new();
        IpcStreamWriter::new(&mut bytes).finish(&mut df)?;
        ensure!(
            bytes.len() <= MAX_SNAPSHOT_BYTES,
            "snapshot exceeds response limit; request a smaller range"
        );
        Ok((
            json!({"api_version":1,"ok":true,"info":view.info,"cursor":cursor,"start":start,"stop":stop,
            "rows":df.height(),"arrow_bytes":bytes.len(),"mapping_confirmed":false}),
            bytes,
        ))
    })();
    let (header, body) = match result {
        Ok(value) => value,
        Err(error) => (
            json!({"api_version":1,"ok":false,"error":format!("{error:#}")}),
            Vec::new(),
        ),
    };
    if serde_json::to_writer(&mut socket, &header).is_ok() && socket.write_all(b"\n").is_ok() {
        let _ = socket.write_all(&body);
    }
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
    ring: Arc<Mutex<LiveBuffer>>,
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
        let ring = self.ring.clone();
        ring.lock().unwrap().clear();
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
                    let frame = Arc::new(frame);
                    {
                        ring.lock().unwrap().push(index, frame.clone());
                    }
                    {
                        let destinations = routes.lock().unwrap();
                        for tx in destinations.iter().flatten() {
                            tx.send(index, frame.clone())?;
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
