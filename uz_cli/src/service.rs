use crate::{
    data::{DataView, Query, Selection, Source},
    live::{DataOptions, LiveBuffer, MAX_SNAPSHOT_BYTES},
    profile::Profile,
    protocol::{decode_frame, encode_command},
    recording::{Recordings, Routes},
    storage::Format,
};
use anyhow::{Context, Result, bail, ensure};
use serde::{Deserialize, Serialize};
use serde_json::{Value, json};
use std::{
    fs::{self, OpenOptions},
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

mod control;

// Bounded audit IO: slow storage must never hold up device Stop.
struct Audit {
    tx: std::sync::mpsc::SyncSender<Value>,
    worker: thread::JoinHandle<()>,
}
impl Audit {
    fn new(
        mut file: impl Write + Send + 'static,
        state: Arc<Mutex<State>>,
        shutdown: Arc<AtomicBool>,
    ) -> Self {
        let (tx, rx) = std::sync::mpsc::sync_channel::<Value>(2048);
        let worker = thread::spawn(move || {
            for event in rx {
                let result = (|| -> Result<()> {
                    serde_json::to_writer(&mut file, &event)?;
                    file.write_all(b"\n")?;
                    file.flush()?;
                    Ok(())
                })();
                if let Err(error) = result {
                    state
                        .lock()
                        .unwrap()
                        .error
                        .get_or_insert_with(|| format!("command audit failed: {error:#}"));
                    shutdown.store(true, Ordering::SeqCst);
                    break;
                }
            }
        });
        Self { tx, worker }
    }
    fn send(&self, event: Value) -> Result<()> {
        self.tx
            .try_send(event)
            .context("command audit queue full or failed")
    }
    fn finish(self) -> Result<()> {
        drop(self.tx);
        self.worker
            .join()
            .map_err(|_| anyhow::anyhow!("command audit worker panicked"))
    }
}

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
    PauseLogging,
    ResumeLogging,
    StartLoggingSlowData,
    StopLoggingSlowData,
    PauseLoggingSlowData,
    ResumeLoggingSlowData,
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
        !matches!(command, Operation::ReadData { .. }),
        "use read_data for binary sample responses"
    );
    let (reply, _) = exchange(endpoint, command, false)?;
    Ok(reply)
}

pub(crate) fn exchange(
    endpoint: &str,
    command: Operation,
    binary: bool,
) -> Result<(Value, Vec<u8>)> {
    // Windows retries refused loopback connections for about two seconds.
    // A two-second deadline can mask ConnectionRefused as TimedOut, preventing
    // callers from recognizing a stopped service during managed flashing.
    let connect_timeout = Duration::from_secs(if cfg!(windows) { 5 } else { 2 });
    let mut socket = TcpStream::connect_timeout(&local_address(endpoint)?, connect_timeout)?;
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
    let service = Service::new(config, shutdown)?;
    eprintln!("UltraZohm service listening on {}", service.config.endpoint);
    ready();
    service.run(listener)
}

/// All mutable session ownership stays on the control thread. The connection
/// context shares only the synchronized state needed by acquisition workers.
struct Service {
    config: Config,
    context: ConnectionContext,
    run_id: String,
    events: Option<Audit>,
    recordings: Recordings,
    connection: Option<Connection>,
    selections: Value,
    shutdown_stop_sent: bool,
}

enum Reply {
    Json(Value),
    Data(Box<DataView>, Query),
}

impl Service {
    fn new(config: Config, shutdown: Arc<AtomicBool>) -> Result<Self> {
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
        let mut events: Option<Audit> = None;
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
            events = Some(Audit::new(
                OpenOptions::new()
                    .create_new(true)
                    .append(true)
                    .open(dir.join("commands.jsonl"))?,
                state.clone(),
                shutdown.clone(),
            ));
        }
        let recordings = Recordings::new(
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
        let context = ConnectionContext {
            profile: config.profile.clone(),
            shutdown,
            state,
            ack,
            routes: recordings.routes.clone(),
            ring,
        };
        let mut service = Self {
            config,
            context,
            run_id,
            events,
            recordings,
            connection: None,
            selections: json!({}),
            shutdown_stop_sent: false,
        };
        if let Some(device) = service.config.device.clone() {
            service.connect(&device)?;
        }
        Ok(service)
    }

    fn connect(&mut self, device: &str) -> Result<()> {
        let (connection, selections) = self.context.connect(device, &mut self.events)?;
        self.connection = Some(connection);
        self.selections = selections;
        Ok(())
    }

    fn run(mut self, listener: TcpListener) -> Result<()> {
        let control = match control::ControlServer::new(
            listener,
            self.context.shutdown.clone(),
            self.context.state.clone(),
        ) {
            Ok(control) => control,
            Err(error) => {
                self.context.state.lock().unwrap().error =
                    Some(format!("control transport: {error:#}"));
                self.context.shutdown.store(true, Ordering::SeqCst);
                let _ = self.finish();
                return Err(error);
            }
        };
        while !self.context.shutdown.load(Ordering::SeqCst) {
            if let Some(error) = self.recordings.error() {
                self.context
                    .state
                    .lock()
                    .unwrap()
                    .error
                    .get_or_insert(error);
                self.context.shutdown.store(true, Ordering::SeqCst);
                break;
            }
            if self
                .connection
                .as_ref()
                .is_some_and(|c| c.acquisition.is_finished())
            {
                self.context.shutdown.store(true, Ordering::SeqCst);
                break;
            }
            if let Some(pending) = control.next() {
                let response = self.handle(pending.request);
                let _ = pending.reply.send(response);
            } else {
                thread::sleep(Duration::from_millis(5));
            }
        }
        // Stop the device before waiting for any slow client or disk worker.
        let result = self.finish();
        let connections = control.finish();
        result.and(connections)
    }

    fn handle(&mut self, req: Request) -> Result<Reply> {
        let mut wire = None;
        match &req.command {
            Operation::ReadData { query } => {
                let view = self.view(&query.source, Some(&query.selection))?;
                return Ok(Reply::Data(Box::new(view), query.clone()));
            }
            Operation::DataInfo { source } => {
                let view = self.view(source, None)?;
                return Ok(Reply::Json(
                    json!({"api_version":1,"ok":true,"info":view.info}),
                ));
            }
            Operation::Recordings => {
                let mut infos = Vec::new();
                for source in self.recordings.sources() {
                    infos.push(self.view(&source, None)?.info);
                }
                return Ok(Reply::Json(
                    json!({"api_version":1,"ok":true,"recordings":infos}),
                ));
            }
            Operation::Connect { ip, port } => {
                ensure!(self.connection.is_none(), "already connected");
                ensure!(*port != 0, "port must be 1..65535");
                let address = SocketAddr::new(
                    ip.parse()
                        .context("device IP must be a numeric IPv4 or IPv6 address")?,
                    *port,
                );
                self.connect(&address.to_string())?;
            }
            Operation::Status => {
                return Ok(Reply::Json(
                    json!({"api_version":1,"ok":true,"state":*self.context.state.lock().unwrap(),"send_ack":self.context.ack.load(Ordering::SeqCst),"logging":self.recordings.status(),
                        "data_options":self.config.data,"buffer_available_samples":self.context.ring.lock().unwrap().available()}),
                ));
            }
            Operation::Catalog => {
                return Ok(Reply::Json(json!({"api_version":1,"ok":true,
                    "profile":self.config.profile,
                    "device_readback":false})));
            }
            Operation::Observables => {
                let channels: Vec<Value> = (1..=self.config.profile.channels)
                    .map(|channel| {
                        let requested = self.selections[channel.to_string()].as_str();
                        let entry = requested.and_then(|name| {
                            self.config
                                .profile
                                .observables
                                .get_key_value(name)
                                .or_else(|| {
                                    self.config
                                        .profile
                                        .observables
                                        .get_key_value(&format!("JSO_{name}"))
                                })
                        });
                        json!({"channel":channel,
                        "name":entry.map(|(name, _)| name),
                        "id":entry.map(|(_, id)| id),
                        "state":if entry.is_some() {"sent_unconfirmed"} else {"unknown"}})
                    })
                    .collect();
                return Ok(Reply::Json(json!({"api_version":1,"ok":true,
                    "source":"service_requested_assignments",
                    "device_readback":false,"channels":channels})));
            }
            Operation::StartLogging => {
                ensure!(
                    self.connection.is_some(),
                    "not connected; use connect first"
                );
                self.recordings.start(false, &self.selections)?;
            }
            Operation::StopLogging => self.recordings.stop(false)?,
            Operation::PauseLogging => self.recordings.pause(false, true)?,
            Operation::ResumeLogging => self.recordings.pause(false, false)?,
            Operation::StartLoggingSlowData => {
                ensure!(
                    self.connection.is_some(),
                    "not connected; use connect first"
                );
                self.recordings.start(true, &self.selections)?;
            }
            Operation::StopLoggingSlowData => self.recordings.stop(true)?,
            Operation::PauseLoggingSlowData => self.recordings.pause(true, true)?,
            Operation::ResumeLoggingSlowData => self.recordings.pause(true, false)?,
            Operation::Shutdown => {
                self.context.shutdown.store(true, Ordering::SeqCst);
                if self.connection.is_some() {
                    wire = Some((self.config.profile.command("Stop")?, 0.0));
                }
            }
            Operation::SendAck { enabled } => {
                // An immediate zero wakes a paused legacy peer when re-enabling.
                if *enabled
                    && !self.context.ack.load(Ordering::SeqCst)
                    && let Some(c) = &self.connection
                    && let Err(e) = send(&c.writer, 0, 0.0)
                {
                    self.context.state.lock().unwrap().error =
                        Some(format!("ACK write failed; outcome unknown: {e}"));
                    self.context.shutdown.store(true, Ordering::SeqCst);
                    return Err(e);
                }
                self.context.ack.store(*enabled, Ordering::SeqCst);
            }
            Operation::SetVariable { name, value } => {
                wire = Some((self.config.profile.variable(name)?, *value))
            }
            Operation::SetObservable { name, channel } => {
                ensure!(
                    !self.recordings.active(),
                    "setting observable is not possible when logging is active; stop fast and slow logging first"
                );
                wire = Some(self.config.profile.observable(name, *channel)?)
            }
            Operation::Button { number } => {
                ensure!((1..=8).contains(number), "button must be 1..8");
                wire = Some((
                    self.config
                        .profile
                        .command(&format!("My_Button_{number}"))?,
                    0.0,
                ));
            }
            Operation::Stop => wire = Some((self.config.profile.command("Stop")?, 0.0)),
            Operation::EnableSystem => {
                wire = Some((self.config.profile.command("Enable_System")?, 0.0))
            }
            Operation::EnableControl => {
                wire = Some((self.config.profile.command("Enable_Control")?, 0.0))
            }
            Operation::ErrorReset => {
                bail!("Error_Reset is a no-op in this firmware; use stop to leave error state")
            }
        }
        if let Some((id, value)) = wire {
            let connected = self
                .connection
                .as_ref()
                .context("not connected; use connect first")?;
            encode_command(id, value)?; // Validation errors must not terminate acquisition.
            if let Err(e) = send(&connected.writer, id, value) {
                self.context.state.lock().unwrap().error =
                    Some(format!("command write failed; outcome unknown: {e}"));
                self.context.shutdown.store(true, Ordering::SeqCst);
                return Err(e);
            }
            self.context.state.lock().unwrap().commands_sent += 1;
            if matches!(req.command, Operation::Shutdown) {
                self.shutdown_stop_sent = true;
            }
            if let Operation::SetObservable { name, channel } = &req.command {
                self.selections[channel.to_string()] = json!(name);
                // Previously retained samples must not acquire the new column labels.
                self.context.ring.lock().unwrap().clear();
            }
        }
        if let Some(audit) = self.events.as_ref()
            && let Err(e) = audit.send(json!({"host_unix_ns":now_ns(),"request":req,"wire":wire,"outcome":if wire.is_some(){"sent_unconfirmed"}else{"applied_locally"}}))
        {
            self.context.state.lock().unwrap().error =
                Some(format!("command audit failed after send: {e}"));
            self.context.shutdown.store(true, Ordering::SeqCst);
            return Err(e);
        }
        Ok(Reply::Json(
            json!({"api_version":1,"ok":true,"outcome":if wire.is_some(){"sent_unconfirmed"}else{"applied_locally"},"logging":self.recordings.status()}),
        ))
    }

    fn view(&self, source: &Source, selection: Option<&Selection>) -> Result<DataView> {
        if let Some(n) = source.recording {
            DataView::recorded(
                &self.run_id,
                source,
                self.recordings.history(&source.stream, n)?.as_ref(),
                &self.config.profile,
                selection,
            )
        } else {
            ensure!(
                self.connection.is_some(),
                "not connected; use connect first"
            );
            DataView::live(
                &self.run_id,
                source,
                &self.context.ring,
                &self.config.profile,
                &self.selections,
                selection,
            )
        }
    }

    fn finish(mut self) -> Result<()> {
        // All exit paths (shutdown command, Ctrl-C, EOF, embedded close, or failure)
        // stop the device before waiting for data queries and recording finalization.
        if !self.shutdown_stop_sent
            && let Some(c) = &self.connection
        {
            match self
                .config
                .profile
                .command("Stop")
                .and_then(|id| send(&c.writer, id, 0.0))
            {
                Ok(()) => self.context.state.lock().unwrap().commands_sent += 1,
                Err(error) => {
                    eprintln!("Shutdown device Stop failed: {error:#}");
                    self.context
                        .state
                        .lock()
                        .unwrap()
                        .error
                        .get_or_insert_with(|| format!("shutdown device Stop failed: {error:#}"));
                }
            }
        }
        if let Some(Connection {
            writer,
            acquisition,
        }) = self.connection
        {
            if acquisition.join().is_err() {
                self.context.state.lock().unwrap().error =
                    Some("acquisition thread panicked".into());
            }
            let _ = writer.lock().unwrap().shutdown(Shutdown::Both);
        }
        if let Err(e) = self.recordings.finish() {
            // Acquisition may observe the closed logger channel before the writer
            // publishes its actual IO error. Preserve that cause after joining it.
            let detail = format!("{e:#}");
            let mut state = self.context.state.lock().unwrap();
            match &mut state.error {
                Some(existing) if existing != &detail => {
                    existing.push_str("; ");
                    existing.push_str(&detail);
                }
                None => state.error = Some(detail),
                _ => {}
            }
        }
        if let Some(audit) = self.events
            && let Err(error) = audit.finish()
        {
            self.context
                .state
                .lock()
                .unwrap()
                .error
                .get_or_insert_with(|| format!("{error:#}"));
        }
        let s = self.context.state.lock().unwrap();
        if let Some(dir) = self.config.output {
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
}

fn read_request(socket: &mut TcpStream) -> Result<Request> {
    // Windows accepted sockets inherit the nonblocking listener mode.
    // Requests and replies use blocking I/O with bounded timeouts.
    socket.set_nonblocking(false)?;
    socket.set_read_timeout(Some(Duration::from_secs(1)))?;
    socket.set_write_timeout(Some(Duration::from_secs(5)))?;
    let req: Request = serde_json::from_slice(&read_line(socket, Duration::from_secs(2))?)?;
    ensure!(req.api_version == 1, "unsupported API version");
    Ok(req)
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
    fn connect(&self, device: &str, events: &mut Option<Audit>) -> Result<(Connection, Value)> {
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
            if let Some(audit) = events.as_ref() {
                audit.send(json!({
                        "host_unix_ns":now_ns(),"source":"initial_channels",
                        "request":{"api_version":1,"command":{"op":"set_observable","name":name,"channel":channel}},
                        "wire":[id,value],"outcome":"sent_unconfirmed"
                    }))?;
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
                            .as_ref()
                            .and_then(|mapping| mapping.decode(frame.status))
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

#[cfg(test)]
mod transport_tests {
    use super::*;

    #[test]
    fn stopped_service_reports_connection_refused() {
        let listener = TcpListener::bind("127.0.0.1:0").unwrap();
        let endpoint = listener.local_addr().unwrap().to_string();
        drop(listener);

        let error = request(&endpoint, Operation::Status).unwrap_err();
        assert_eq!(
            error.downcast_ref::<std::io::Error>().map(|e| e.kind()),
            Some(std::io::ErrorKind::ConnectionRefused),
            "a stopped service must report refusal, not a timeout: {error:#}"
        );
    }
}

#[cfg(test)]
mod audit_tests {
    use super::*;
    use std::sync::mpsc;

    struct BlockedWriter {
        entered: Option<mpsc::Sender<()>>,
        release: mpsc::Receiver<()>,
    }
    impl Write for BlockedWriter {
        fn write(&mut self, bytes: &[u8]) -> std::io::Result<usize> {
            if let Some(entered) = self.entered.take() {
                entered.send(()).unwrap();
                self.release.recv_timeout(Duration::from_secs(5)).unwrap();
            }
            Ok(bytes.len())
        }
        fn flush(&mut self) -> std::io::Result<()> {
            Ok(())
        }
    }
    #[test]
    fn slow_audit_is_bounded_and_does_not_block_submission() {
        let (entered_tx, entered_rx) = mpsc::channel();
        let (release_tx, release_rx) = mpsc::channel();
        let audit = Audit::new(
            BlockedWriter {
                entered: Some(entered_tx),
                release: release_rx,
            },
            Arc::new(Mutex::new(State::default())),
            Arc::new(AtomicBool::new(false)),
        );
        audit.send(json!({"first": true})).unwrap();
        entered_rx.recv_timeout(Duration::from_secs(2)).unwrap();
        for _ in 0..2048 {
            audit.send(json!({"queued": true})).unwrap();
        }
        assert!(audit.send(json!({"overflow": true})).is_err());
        release_tx.send(()).unwrap();
        audit.finish().unwrap();
    }
}
