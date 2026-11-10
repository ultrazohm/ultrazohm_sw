use crate::{
    data::{DataView, Query, Selection, Source, Stream},
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
    io::{BufRead, BufReader, Read, Write},
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
/// Local API version. v2: persistent connections and coded errors.
pub const API_VERSION: u32 = 2;

/// An error with a stable machine-readable `code`, carried in JSON error replies.
#[derive(Debug)]
pub struct ApiError {
    pub code: String,
    pub message: String,
}
impl std::fmt::Display for ApiError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(&self.message)
    }
}
impl std::error::Error for ApiError {}

pub(crate) fn coded(code: &str, message: impl Into<String>) -> anyhow::Error {
    ApiError {
        code: code.into(),
        message: message.into(),
    }
    .into()
}

/// The error code of the first coded error in an error chain, if any.
pub fn error_code(error: &anyhow::Error) -> Option<&str> {
    error
        .chain()
        .find_map(|e| e.downcast_ref::<ApiError>())
        .map(|e| e.code.as_str())
}

fn ok_reply(mut fields: Value) -> Value {
    fields["api_version"] = json!(API_VERSION);
    fields["ok"] = json!(true);
    fields
}

fn error_reply(error: &anyhow::Error) -> Value {
    json!({"api_version":API_VERSION,"ok":false,"error":format!("{error:#}"),"code":error_code(error)})
}

#[derive(Debug, Serialize, Deserialize)]
#[serde(tag = "op", rename_all = "snake_case", deny_unknown_fields)]
pub enum Operation {
    Connect {
        ip: String,
        port: u16,
    },
    Status,
    Catalog,
    Observables,
    DataInfo {
        source: Source,
    },
    ReadData {
        query: Query,
    },
    Recordings,
    Stop,
    EnableSystem,
    EnableControl,
    SetVariable {
        name: String,
        value: f32,
    },
    SetObservable {
        name: String,
        channel: u32,
    },
    Button {
        number: u32,
    },
    SendAck {
        enabled: bool,
    },
    StartLogging {
        #[serde(default)]
        stream: Stream,
    },
    StopLogging {
        #[serde(default)]
        stream: Stream,
    },
    PauseLogging {
        #[serde(default)]
        stream: Stream,
    },
    ResumeLogging {
        #[serde(default)]
        stream: Stream,
    },
    Shutdown,
}
impl Operation {
    /// Reads have no device or recording side effects and may be retried.
    pub fn read_only(&self) -> bool {
        matches!(
            self,
            Self::Status
                | Self::Catalog
                | Self::Observables
                | Self::DataInfo { .. }
                | Self::ReadData { .. }
                | Self::Recordings
        )
    }
    /// Device commands that a later Stop supersedes while still queued.
    pub fn superseded_by_stop(&self) -> bool {
        matches!(
            self,
            Self::Stop
                | Self::EnableSystem
                | Self::EnableControl
                | Self::SetVariable { .. }
                | Self::SetObservable { .. }
                | Self::Button { .. }
        )
    }
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
/// Read one newline-terminated message through a buffer; the binary body of a
/// data reply stays in the same reader. `Ok(None)` is EOF before a message, or
/// `idle_stop` becoming set, including during a partial request.
fn read_message(
    reader: &mut impl BufRead,
    deadline: Duration,
    idle_stop: Option<&AtomicBool>,
) -> Result<Option<Vec<u8>>> {
    let mut data = Vec::new();
    let mut started: Option<Instant> = None;
    loop {
        if idle_stop.is_some_and(|stop| stop.load(Ordering::SeqCst)) {
            return Ok(None);
        }
        if let Some(started) = started {
            ensure!(
                started.elapsed() < deadline,
                "control message deadline exceeded"
            );
        }
        let available = match reader.fill_buf() {
            Ok(bytes) => bytes,
            Err(e) if e.kind() == std::io::ErrorKind::Interrupted => continue,
            Err(e)
                if matches!(
                    e.kind(),
                    std::io::ErrorKind::WouldBlock | std::io::ErrorKind::TimedOut
                ) =>
            {
                match (started, idle_stop) {
                    (Some(t), _) => {
                        ensure!(t.elapsed() < deadline, "control message deadline exceeded")
                    }
                    (None, Some(stop)) if stop.load(Ordering::SeqCst) => return Ok(None),
                    (None, Some(_)) => {}
                    (None, None) => bail!("timed out waiting for a reply"),
                }
                continue;
            }
            Err(e) => return Err(e.into()),
        };
        // Check successful reads too: a peer can otherwise evade the deadline
        // by continuously sending fragments faster than the socket timeout.
        if let Some(started) = started {
            ensure!(
                started.elapsed() < deadline,
                "control message deadline exceeded"
            );
        }
        if idle_stop.is_some_and(|stop| stop.load(Ordering::SeqCst)) {
            return Ok(None);
        }
        if available.is_empty() {
            ensure!(data.is_empty(), "connection closed before newline");
            return Ok(None);
        }
        started.get_or_insert_with(Instant::now);
        let newline = available.iter().position(|&b| b == b'\n');
        let take = newline.unwrap_or(available.len());
        data.extend_from_slice(&available[..take]);
        reader.consume(take + usize::from(newline.is_some()));
        ensure!(
            data.len() <= MAX_MESSAGE,
            "control message exceeds {MAX_MESSAGE} bytes"
        );
        if newline.is_some() {
            return Ok(Some(data));
        }
    }
}

/// One request on a fresh connection, for short-lived CLI invocations.
pub fn request(endpoint: &str, command: Operation) -> Result<Value> {
    ensure!(
        !matches!(command, Operation::ReadData { .. }),
        "use read_data for binary sample responses"
    );
    let (reply, _) = Connection::new(endpoint).exchange(command, false)?;
    Ok(reply)
}

pub(crate) fn exchange(
    endpoint: &str,
    command: Operation,
    binary: bool,
) -> Result<(Value, Vec<u8>)> {
    Connection::new(endpoint).exchange(command, binary)
}

/// A persistent client connection. Requests are sent sequentially on one socket;
/// a broken socket is dropped and reopened. Only read-only operations are
/// retried automatically, because a device command must never be replayed.
pub struct Connection {
    endpoint: String,
    socket: Option<(BufReader<TcpStream>, TcpStream)>,
}
impl Connection {
    pub fn new(endpoint: &str) -> Self {
        Self {
            endpoint: endpoint.into(),
            socket: None,
        }
    }

    /// Drop the socket; the next exchange reconnects.
    pub fn reset(&mut self) {
        self.socket = None;
    }

    fn open(&mut self) -> Result<&mut (BufReader<TcpStream>, TcpStream)> {
        // A service that closed an idle connection (restart, shutdown) leaves a
        // readable EOF; detect it before sending rather than after.
        if let Some((reader, _)) = &mut self.socket {
            let stale = reader.buffer().is_empty() && {
                let socket = reader.get_ref();
                socket.set_nonblocking(true)?;
                let mut probe = [0u8];
                let state = socket.peek(&mut probe);
                socket.set_nonblocking(false)?;
                !matches!(&state, Err(e) if e.kind() == std::io::ErrorKind::WouldBlock)
            };
            if stale {
                self.socket = None;
            }
        }
        if self.socket.is_none() {
            // Windows retries refused loopback connections for about two seconds.
            // A two-second deadline can mask ConnectionRefused as TimedOut, preventing
            // callers from recognizing a stopped service during managed flashing.
            let connect_timeout = Duration::from_secs(if cfg!(windows) { 5 } else { 2 });
            let socket =
                TcpStream::connect_timeout(&local_address(&self.endpoint)?, connect_timeout)?;
            socket.set_nodelay(true)?;
            socket.set_write_timeout(Some(Duration::from_secs(2)))?;
            self.socket = Some((BufReader::new(socket.try_clone()?), socket));
        }
        Ok(self.socket.as_mut().expect("socket opened above"))
    }

    pub fn exchange(&mut self, command: Operation, binary: bool) -> Result<(Value, Vec<u8>)> {
        let retry = command.read_only();
        let timeout =
            Duration::from_secs(if binary || matches!(command, Operation::Connect { .. }) {
                30
            } else {
                5
            });
        let request = serde_json::to_vec(&Request {
            api_version: API_VERSION,
            command,
        })?;
        let result = self.send(&request, binary, timeout);
        if let Err(error) = &result
            && retry
            && error.downcast_ref::<std::io::Error>().is_some()
        {
            self.socket = None;
            return self.send(&request, binary, timeout);
        }
        result
    }

    fn send(
        &mut self,
        request: &[u8],
        binary: bool,
        timeout: Duration,
    ) -> Result<(Value, Vec<u8>)> {
        let result = (|| -> Result<(Value, Vec<u8>)> {
            let (reader, socket) = self.open()?;
            socket.set_read_timeout(Some(timeout))?;
            socket.write_all(request)?;
            socket.write_all(b"\n")?;
            let line = read_message(reader, timeout, None)?.ok_or_else(|| {
                std::io::Error::new(
                    std::io::ErrorKind::UnexpectedEof,
                    "service closed the connection",
                )
            })?;
            let reply: Value = serde_json::from_slice(&line)?;
            ensure!(
                reply["api_version"] == API_VERSION,
                "unsupported response API version {}; client and service versions differ",
                reply["api_version"]
            );
            if reply["ok"] != true {
                return Err(ApiError {
                    code: reply["code"].as_str().unwrap_or("error").into(),
                    message: reply["error"].as_str().unwrap_or("request failed").into(),
                }
                .into());
            }
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
                reader.read_exact(&mut bytes)?;
            }
            Ok((reply, bytes))
        })();
        // A reply error leaves the stream in sync; any other failure may not.
        if let Err(error) = &result
            && error.downcast_ref::<ApiError>().is_none()
        {
            self.socket = None;
        }
        result
    }
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
    connection: Option<DeviceConnection>,
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

    /// Record the first terminal error (later errors never mask the root cause)
    /// and end acquisition.
    fn fail(&self, message: String) {
        self.context.fail(message);
    }

    fn connect(&mut self, device: &str) -> Result<()> {
        let (connection, selections) = self.context.connect(device, &self.events)?;
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
                self.fail(format!("control transport: {error:#}"));
                if let Err(finish) = self.finish() {
                    eprintln!("Service finalization: {finish:#}");
                }
                return Err(error);
            }
        };
        while !self.context.shutdown.load(Ordering::SeqCst) {
            // A failed recording is reported in its status and at exit; it never
            // ends acquisition or device control (optional exports included).
            if self
                .connection
                .as_ref()
                .is_some_and(|c| c.acquisition.is_finished())
            {
                self.context.shutdown.store(true, Ordering::SeqCst);
                break;
            }
            // Wake on the next request; time out to recheck acquisition state.
            if let Some(pending) = control.next(Duration::from_millis(50)) {
                let response = self.handle(pending.request);
                // A client that disconnected meanwhile no longer needs the reply.
                let _ = pending.reply.send(response);
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
                return Ok(Reply::Json(ok_reply(json!({"info":view.info}))));
            }
            Operation::Recordings => {
                let mut infos = Vec::new();
                for source in self.recordings.sources() {
                    infos.push(self.view(&source, None)?.info);
                }
                return Ok(Reply::Json(ok_reply(json!({"recordings":infos}))));
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
                let available = self.context.ring.lock().unwrap().available();
                let state = serde_json::to_value(&*self.context.state.lock().unwrap())?;
                return Ok(Reply::Json(ok_reply(json!({
                    "state":state,"send_ack":self.context.ack.load(Ordering::SeqCst),
                    "logging":self.recordings.status(),"data_options":self.config.data,
                    "buffer_available_samples":available}))));
            }
            Operation::Catalog => {
                return Ok(Reply::Json(ok_reply(json!({
                    "profile":self.config.profile,"device_readback":false}))));
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
                return Ok(Reply::Json(ok_reply(json!({
                    "source":"service_requested_assignments",
                    "device_readback":false,"channels":channels}))));
            }
            Operation::StartLogging { stream } => {
                if self.connection.is_none() {
                    return Err(coded("not_connected", "not connected; use connect first"));
                }
                self.recordings
                    .start(*stream == Stream::Slow, &self.selections)?;
            }
            Operation::StopLogging { stream } => self.recordings.stop(*stream == Stream::Slow)?,
            Operation::PauseLogging { stream } => {
                self.recordings.pause(*stream == Stream::Slow, true)?
            }
            Operation::ResumeLogging { stream } => {
                self.recordings.pause(*stream == Stream::Slow, false)?
            }
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
                    self.fail(format!("ACK write failed; outcome unknown: {e}"));
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
        }
        if let Some((id, value)) = wire {
            let Some(connected) = self.connection.as_ref() else {
                return Err(coded("not_connected", "not connected; use connect first"));
            };
            encode_command(id, value)?; // Validation errors must not terminate acquisition.
            if let Err(e) = send(&connected.writer, id, value) {
                self.fail(format!("command write failed; outcome unknown: {e}"));
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
            self.fail(format!("command audit failed after send: {e}"));
            return Err(e);
        }
        Ok(Reply::Json(ok_reply(
            json!({"outcome":if wire.is_some(){"sent_unconfirmed"}else{"applied_locally"},"logging":self.recordings.status()}),
        )))
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
            if self.connection.is_none() {
                return Err(coded("not_connected", "not connected; use connect first"));
            }
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
                    self.fail(format!("shutdown device Stop failed: {error:#}"));
                }
            }
        }
        if let Some(DeviceConnection {
            writer,
            acquisition,
        }) = self.connection
        {
            if acquisition.join().is_err() {
                self.context.fail("acquisition thread panicked".into());
            }
            // The device socket may already be closed by the peer.
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
            self.context.fail(format!("{error:#}"));
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

/// Read the next request on a persistent connection. Idle connections wait
/// until `stop` is set; a started request must complete within two seconds.
fn read_request(reader: &mut impl BufRead, stop: &AtomicBool) -> Result<Option<Request>> {
    let Some(line) = read_message(reader, Duration::from_secs(2), Some(stop))? else {
        return Ok(None);
    };
    let req: Request = serde_json::from_slice(&line)?;
    ensure!(
        req.api_version == API_VERSION,
        "unsupported API version {}; this service speaks {API_VERSION}",
        req.api_version
    );
    Ok(Some(req))
}

fn write_reply(socket: &mut TcpStream, reply: &Value) -> std::io::Result<()> {
    let mut line = serde_json::to_vec(reply)?;
    line.push(b'\n');
    socket.write_all(&line)
}

fn serve_data_query(socket: &mut TcpStream, view: DataView, query: Query) -> std::io::Result<()> {
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
            ok_reply(
                json!({"info":view.info,"cursor":cursor,"start":start,"stop":stop,
            "rows":df.height(),"arrow_bytes":bytes.len(),"mapping_confirmed":false}),
            ),
            bytes,
        ))
    })();
    let (header, body) = match result {
        Ok(value) => value,
        Err(error) => (error_reply(&error), Vec::new()),
    };
    write_reply(socket, &header)?;
    socket.write_all(&body)
}

struct DeviceConnection {
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
    fn fail(&self, message: String) {
        self.state.lock().unwrap().error.get_or_insert(message);
        self.shutdown.store(true, Ordering::SeqCst);
    }

    fn connect(&self, device: &str, events: &Option<Audit>) -> Result<(DeviceConnection, Value)> {
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
                        "request":{"api_version":API_VERSION,"command":{"op":"set_observable","name":name,"channel":channel}},
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
                        let mut destinations = routes.lock().unwrap();
                        for slot in destinations.iter_mut() {
                            let open = match slot {
                                Some(route) => route.send(index, frame.clone())?,
                                None => true,
                            };
                            if !open {
                                // Its writer failed and published the error; keep acquiring.
                                *slot = None;
                            }
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
            DeviceConnection {
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
    fn message_deadline_includes_successful_fragment_reads() {
        struct Fragments(usize);
        impl Read for Fragments {
            fn read(&mut self, buffer: &mut [u8]) -> std::io::Result<usize> {
                if self.0 != 0 {
                    thread::sleep(Duration::from_millis(20));
                }
                buffer[0] = if self.0 == 0 { b'x' } else { b'\n' };
                self.0 += 1;
                Ok(1)
            }
        }
        let mut reader = BufReader::with_capacity(1, Fragments(0));
        let error = read_message(&mut reader, Duration::from_millis(10), None).unwrap_err();
        assert!(error.to_string().contains("deadline exceeded"));
    }

    #[test]
    fn shutdown_does_not_admit_buffered_requests() {
        let mut reader = std::io::Cursor::new(b"request\n");
        assert!(
            read_message(
                &mut reader,
                Duration::from_secs(2),
                Some(&AtomicBool::new(true)),
            )
            .unwrap()
            .is_none()
        );
    }

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
