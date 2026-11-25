//! One acquisition session: device connection, live ring, recordings and audit.
//! All mutable session state stays on the control thread; the connection
//! context shares only the synchronized state needed by acquisition workers.
use super::{
    Config, Operation, Selections,
    replies::{
        AssignmentState, CatalogReply, CommandReply, DataInfoReply, ObservableChannel,
        ObservablesReply, Outcome, RecordingListCursor, RecordingsPageReply, SessionStatus,
    },
    wire::{MAX_REPLY, VERSION, coded, error_code},
};
use crate::{
    data::{DataView, Query, Selection, Source, Stream},
    live::{LiveBuffer, MAX_SNAPSHOT_BYTES},
    protocol::{decode_frame, encode_command},
    recording::{Recordings, Routes},
};
use anyhow::{Context, Result, bail, ensure};
use serde::Serialize;
use serde_json::{Value, json};
use std::{
    fs::{self, OpenOptions},
    io::{Read, Write},
    net::{Shutdown, SocketAddr, TcpStream, ToSocketAddrs},
    sync::{
        Arc, Mutex,
        atomic::{AtomicBool, Ordering},
    },
    thread,
    time::{Duration, Instant, SystemTime, UNIX_EPOCH},
};

pub(super) fn now_ns() -> u64 {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap_or_default()
        .as_nanos() as u64
}

// Bounded audit IO: slow storage must never hold up device Stop. Audit failure
// is reported in status and in run.json's end section; it never ends
// acquisition or control.
pub(super) struct Audit {
    tx: std::sync::mpsc::SyncSender<Value>,
    worker: thread::JoinHandle<()>,
}
impl Audit {
    fn new(mut file: impl Write + Send + 'static, state: Arc<Mutex<State>>) -> Self {
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
                    record_audit_error(&state, format!("command audit failed: {error:#}"));
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
    /// Submit an event; a failure is recorded once and never fails the command.
    fn record(&self, event: Value, state: &Mutex<State>) {
        if let Err(error) = self.send(event) {
            record_audit_error(state, format!("{error:#}; later commands are not audited"));
        }
    }
    fn finish(self) -> Result<()> {
        drop(self.tx);
        self.worker
            .join()
            .map_err(|_| anyhow::anyhow!("command audit worker panicked"))
    }
}

/// Keep the first audit failure; it marks the session incomplete without ending it.
fn record_audit_error(state: &Mutex<State>, message: String) {
    state.lock().unwrap().audit_error.get_or_insert(message);
}

/// A device write that failed after the command was validated: the device may
/// or may not have received it. Audited as `write_failed`.
#[derive(Debug)]
struct WriteFailed(&'static str);
impl std::fmt::Display for WriteFailed {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(self.0)
    }
}

/// Acquisition health shared with the receiver thread.
#[derive(Clone, Default, Serialize)]
pub struct State {
    pub connected: bool,
    pub device: Option<String>,
    pub frames: u64,
    pub samples: u64,
    pub status: u32,
    pub user_buttons: [bool; 8],
    pub platform_state: Option<String>,
    pub commands_sent: u64,
    pub ack_sent: u64,
    pub error: Option<String>,
    /// Command audit failure; acquisition, control and recordings continue.
    pub audit_error: Option<String>,
}

pub(super) enum Reply {
    Json(Value),
    Data(Box<DataView>, Query),
}
impl Reply {
    pub(super) fn of(body: impl Serialize) -> Result<Self> {
        Ok(Self::Json(serde_json::to_value(body)?))
    }
}

fn send(writer: &Mutex<TcpStream>, id: u32, value: f32) -> Result<()> {
    writer
        .lock()
        .unwrap()
        .write_all(&encode_command(id, value)?)?;
    Ok(())
}

pub(super) struct DeviceConnection {
    writer: Arc<Mutex<TcpStream>>,
    acquisition: thread::JoinHandle<Result<()>>,
}

pub(super) struct Session {
    pub reconnect_error: Option<String>,
    pub config: Config,
    context: ConnectionContext,
    pub run_id: String,
    events: Option<Audit>,
    recordings: Recordings,
    connection: Option<DeviceConnection>,
    pub selections: Selections,
    /// Incremented whenever the requested observables change.
    revision: u64,
    pub shutdown_stop_sent: bool,
    run_metadata: Value,
}

impl Session {
    pub fn new(mut config: Config, shutdown: Arc<AtomicBool>) -> Result<Self> {
        config.profile.validate()?;
        config.data.resolve(config.profile.sample_period_us)?;
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
        // Session description; the service adds an "end" section when it exits.
        let run_metadata = json!({
            "schema_version":5,"run_id":run_id,"started_unix_ns":now_ns(),"device":config.device,
            "profile":config.profile,"format":config.format,"data_options":config.data,
            "time_basis":"seconds from acquisition start; configured sample period; gaps unknown",
            "storage_layout":"consolidated_recordings","source":"ultrazohm_cli",
            "software_version":crate::VERSION
        });
        if let Some(dir) = &config.output {
            fs::create_dir(dir)?;
            fs::write(
                dir.join("run.json"),
                serde_json::to_vec_pretty(&run_metadata)?,
            )?;
            events = Some(Audit::new(
                OpenOptions::new()
                    .create_new(true)
                    .append(true)
                    .open(dir.join("commands.jsonl"))?,
                state.clone(),
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
        if let (Some(current), Some(output)) = (&config.current_output, &config.output) {
            *current.lock().unwrap() = output.clone();
        }
        let mut session = Self {
            reconnect_error: None,
            config,
            context,
            run_id,
            events,
            recordings,
            connection: None,
            selections: Selections::new(),
            revision: 0,
            shutdown_stop_sent: false,
            run_metadata,
        };
        if let Some(device) = session.config.device.clone() {
            session.connect(&device)?;
        }
        Ok(session)
    }

    pub fn connected(&self) -> bool {
        self.connection.is_some()
    }

    /// The receiver ended (device disconnect or failure) or shutdown was requested.
    pub fn ended(&self) -> bool {
        self.context.shutdown.load(Ordering::SeqCst)
            || self
                .connection
                .as_ref()
                .is_some_and(|c| c.acquisition.is_finished())
    }

    /// Ask acquisition to end; [`Session::finish`] completes it.
    pub fn request_end(&self) {
        self.context.shutdown.store(true, Ordering::SeqCst);
    }

    pub fn error(&self) -> Option<String> {
        self.context.state.lock().unwrap().error.clone()
    }

    pub fn device(&self) -> Option<String> {
        self.context.state.lock().unwrap().device.clone()
    }

    pub fn ack(&self) -> bool {
        self.context.ack.load(Ordering::SeqCst)
    }

    /// Identifies the catalog and the requested observables of this session.
    pub fn configuration_revision(&self) -> String {
        format!("{}:{}", self.run_id, self.revision)
    }

    pub fn state(&self) -> State {
        self.context.state.lock().unwrap().clone()
    }

    pub fn status(&self) -> SessionStatus {
        SessionStatus {
            send_ack: self.ack(),
            logging: self.recordings.status(),
            data_options: self.config.data.clone(),
            buffer_available_samples: self.context.ring.lock().unwrap().available(),
        }
    }

    /// Send device Stop; a failure is recorded as the session error.
    pub fn stop_device(&mut self) {
        if let Err(error) = self.handle(Operation::Stop) {
            self.context.state.lock().unwrap().error = Some(format!("Stop failed: {error:#}"));
        }
    }

    fn connect(&mut self, device: &str) -> Result<()> {
        let (connection, selections) = self.context.connect(device, &self.events)?;
        self.connection = Some(connection);
        self.reconnect_error = None;
        self.selections = selections;
        self.revision += 1;
        Ok(())
    }

    /// Connect to `target`, retrying until `deadline` (the firmware may still boot).
    pub fn connect_until(&mut self, target: &str, deadline: Instant) -> Result<()> {
        loop {
            match self.connect(target) {
                Ok(()) => return Ok(()),
                Err(e) if Instant::now() >= deadline => return Err(e),
                Err(_) => thread::sleep(Duration::from_millis(100)),
            }
        }
    }

    pub fn handle(&mut self, command: Operation) -> Result<Reply> {
        match &command {
            Operation::ReadData { query } => {
                let view = self.view(&query.source, Some(&query.selection))?;
                let Operation::ReadData { query } = command else {
                    unreachable!()
                };
                return Ok(Reply::Data(Box::new(view), query));
            }
            Operation::DataInfo { source } => {
                return Reply::of(DataInfoReply {
                    info: self.view(source, None)?.info,
                });
            }
            Operation::RecordingsPage { cursor, limit } => {
                return Reply::of(self.recordings_page(cursor.clone(), *limit)?);
            }
            Operation::Catalog => {
                return Reply::of(CatalogReply {
                    profile: &self.config.profile,
                    device_readback: false,
                });
            }
            Operation::Observables => return Reply::of(self.observables()),
            _ => {}
        }
        // Every command that reached execution is audited, including rejected
        // ones and writes whose outcome on the device is unknown.
        let result = self.apply(&command);
        if let Some(audit) = self.events.as_ref() {
            let entry = match &result {
                Ok(wire) => json!({"host_unix_ns":now_ns(),"command":command,"wire":wire,
                    "outcome":outcome(wire)}),
                Err(error) => json!({"host_unix_ns":now_ns(),"command":command,
                    "outcome":if error.downcast_ref::<WriteFailed>().is_some(){"write_failed"}else{"rejected"},
                    "error":format!("{error:#}"),"code":error_code(error)}),
            };
            audit.record(entry, &self.context.state);
        }
        let wire = result?;
        Reply::of(CommandReply {
            outcome: outcome(&wire),
            logging: Some(self.recordings.status()),
        })
    }

    fn recordings_page(
        &self,
        cursor: Option<RecordingListCursor>,
        limit: usize,
    ) -> Result<RecordingsPageReply> {
        ensure!(
            (1..=1000).contains(&limit),
            "recording page limit must be 1..1000"
        );
        let sources = self.recordings.sources();
        let slot = |source: &Source| usize::from(source.stream == Stream::Slow);
        let number = |source: &Source| source.recording.expect("recorded source");
        let mut upper = [0; 2];
        for source in &sources {
            upper[slot(source)] = upper[slot(source)].max(number(source));
        }
        let mut cursor = cursor.unwrap_or(RecordingListCursor {
            run_id: self.run_id.clone(),
            upper,
            offset: 0,
        });
        if cursor.run_id != self.run_id
            || cursor
                .upper
                .iter()
                .zip(upper)
                .any(|(old, current)| *old > current)
        {
            return Err(coded("cursor_expired", "recording list session changed"));
        }
        let sources: Vec<_> = sources
            .into_iter()
            .filter(|source| number(source) <= cursor.upper[slot(source)])
            .collect();
        ensure!(
            cursor.offset <= sources.len(),
            "invalid recording list offset"
        );
        let mut infos = Vec::new();
        let mut bytes = 0;
        for source in sources.iter().skip(cursor.offset).take(limit) {
            let info = self.view(source, None)?.info;
            let size = serde_json::to_vec(&info)?.len();
            ensure!(
                size <= MAX_REPLY / 2,
                "individual recording metadata exceeds page limit"
            );
            if bytes + size > MAX_REPLY / 2 {
                break;
            }
            bytes += size;
            infos.push(info);
        }
        cursor.offset += infos.len();
        let next_cursor = (cursor.offset < sources.len()).then_some(cursor);
        Ok(RecordingsPageReply {
            recordings: infos,
            next_cursor,
        })
    }

    fn observables(&self) -> ObservablesReply {
        let profile = &self.config.profile;
        let channels = (1..=profile.channels as u32)
            .map(|channel| {
                let entry = self.selections.get(&channel).and_then(|name| {
                    profile
                        .observables
                        .get_key_value(name)
                        .or_else(|| profile.observables.get_key_value(&format!("JSO_{name}")))
                });
                ObservableChannel {
                    channel,
                    name: entry.map(|(name, _)| name.clone()),
                    id: entry.map(|(_, id)| *id),
                    state: if entry.is_some() {
                        AssignmentState::SentUnconfirmed
                    } else {
                        AssignmentState::Unknown
                    },
                }
            })
            .collect();
        ObservablesReply {
            source: "service_requested_assignments",
            device_readback: false,
            channels,
        }
    }

    /// Execute a command and return the device command it wrote, if any.
    fn apply(&mut self, command: &Operation) -> Result<Option<(u32, f32)>> {
        let profile = &self.config.profile;
        let wire = match command {
            Operation::Connect { ip, port } => {
                ensure!(self.connection.is_none(), "already connected");
                ensure!(*port != 0, "port must be 1..65535");
                let address = SocketAddr::new(
                    ip.parse()
                        .context("device IP must be a numeric IPv4 or IPv6 address")?,
                    *port,
                );
                self.connect(&address.to_string())?;
                None
            }
            Operation::StartLogging { stream } => {
                if self.connection.is_none() {
                    return Err(coded("not_connected", "not connected; use connect first"));
                }
                self.recordings
                    .start(*stream == Stream::Slow, &self.selections)?;
                None
            }
            Operation::StopLogging { stream } => {
                self.recordings.stop(*stream == Stream::Slow)?;
                None
            }
            Operation::PauseLogging { stream } => {
                self.recordings.pause(*stream == Stream::Slow, true)?;
                None
            }
            Operation::ResumeLogging { stream } => {
                self.recordings.pause(*stream == Stream::Slow, false)?;
                None
            }
            Operation::Shutdown => {
                self.context.shutdown.store(true, Ordering::SeqCst);
                if self.connection.is_some() {
                    Some((profile.command("Stop")?, 0.0))
                } else {
                    None
                }
            }
            Operation::SendAck { enabled } => {
                // An immediate zero wakes a paused legacy peer when re-enabling.
                if *enabled
                    && !self.context.ack.load(Ordering::SeqCst)
                    && let Some(c) = &self.connection
                    && let Err(e) = send(&c.writer, 0, 0.0)
                {
                    self.context
                        .fail(format!("ACK write failed; outcome unknown: {e}"));
                    return Err(e.context(WriteFailed("ACK write failed; outcome unknown")));
                }
                self.context.ack.store(*enabled, Ordering::SeqCst);
                None
            }
            Operation::SetVariable { name, value } => Some((profile.variable(name)?, *value)),
            Operation::SetObservable { name, channel } => {
                ensure!(
                    !self.recordings.active(),
                    "setting observable is not possible when logging is active; stop fast and slow logging first"
                );
                Some(profile.observable(name, *channel)?)
            }
            Operation::Button { number } => {
                ensure!((1..=8).contains(number), "button must be 1..8");
                Some((profile.command(&format!("My_Button_{number}"))?, 0.0))
            }
            Operation::Stop => Some((profile.command("Stop")?, 0.0)),
            Operation::EnableSystem => Some((profile.command("Enable_System")?, 0.0)),
            Operation::EnableControl => Some((profile.command("Enable_Control")?, 0.0)),
            Operation::Firmware { .. }
            | Operation::Jobs
            | Operation::Job { .. }
            | Operation::OwnedShutdown { .. } => {
                bail!("controller operation reached an acquisition session")
            }
            Operation::ReadData { .. }
            | Operation::DataInfo { .. }
            | Operation::RecordingsPage { .. }
            | Operation::Status
            | Operation::Catalog
            | Operation::Observables => bail!("read operation reached command execution"),
        };
        if let Some((id, value)) = wire {
            let Some(connected) = self.connection.as_ref() else {
                return Err(coded("not_connected", "not connected; use connect first"));
            };
            encode_command(id, value)?; // Validation errors must not terminate acquisition.
            if let Err(e) = send(&connected.writer, id, value) {
                self.context
                    .fail(format!("command write failed; outcome unknown: {e}"));
                return Err(e.context(WriteFailed("command write failed; outcome unknown")));
            }
            self.context.state.lock().unwrap().commands_sent += 1;
            if matches!(command, Operation::Shutdown) {
                self.shutdown_stop_sent = true;
            }
            if let Operation::SetObservable { name, channel } = command {
                self.selections.insert(*channel, name.clone());
                self.revision += 1;
                // Retain other channels, but never relabel this channel's old samples.
                self.context
                    .ring
                    .lock()
                    .unwrap()
                    .clear_channel(*channel as usize - 1);
            }
        }
        Ok(wire)
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

    /// Configuration to recreate this session: current ack, device and selections.
    pub fn snapshot_config(&self) -> Config {
        let mut config = self.config.clone();
        config.ack = self.ack();
        config.device = self.device().or(config.device);
        config.profile.initial_channels.extend(
            self.selections
                .iter()
                .map(|(channel, name)| (*channel, name.clone())),
        );
        config
    }

    pub fn finish(mut self) -> Result<()> {
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
                        .fail(format!("shutdown device Stop failed: {error:#}"));
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
            record_audit_error(&self.context.state, format!("{error:#}"));
        }
        let s = self.context.state.lock().unwrap();
        let complete = s.error.is_none() && s.audit_error.is_none();
        if let Some(dir) = self.config.output {
            // A missing end section means the service did not exit normally.
            let mut run = self.run_metadata;
            run["end"] = json!({"ended_unix_ns":now_ns(),"state":*s,"complete":complete});
            let target = dir.join("run.json");
            let partial = dir.join("run.json.partial");
            let file = fs::File::create(&partial)?;
            serde_json::to_writer_pretty(&file, &run)?;
            file.sync_all()?;
            drop(file);
            crate::backend::replace_file(&partial, &target)?;
        }
        match (&s.error, &s.audit_error) {
            (Some(e), Some(a)) => bail!("{e}; {a}"),
            (Some(e), None) | (None, Some(e)) => bail!("{e}"),
            (None, None) => Ok(()),
        }
    }
}

fn outcome(wire: &Option<(u32, f32)>) -> Outcome {
    if wire.is_some() {
        Outcome::SentUnconfirmed
    } else {
        Outcome::AppliedLocally
    }
}

/// Write a data reply: header line, then the Arrow body.
pub(super) fn serve_data_query(
    socket: &mut TcpStream,
    id: u64,
    view: DataView,
    query: Query,
) -> std::io::Result<()> {
    use super::{replies::DataReply, wire};
    use polars::prelude::*;
    let result = (|| -> Result<(Value, Vec<u8>)> {
        let (mut df, cursor, start, stop) = view.read(&query)?;
        let mut bytes = Vec::new();
        IpcStreamWriter::new(&mut bytes).finish(&mut df)?;
        ensure!(
            bytes.len() <= MAX_SNAPSHOT_BYTES,
            "snapshot exceeds response limit; request a smaller range"
        );
        let header = serde_json::to_value(DataReply {
            info: &view.info,
            cursor,
            start,
            stop,
            rows: df.height(),
            arrow_bytes: bytes.len(),
            mapping_confirmed: false,
        })?;
        Ok((wire::ok_reply(Some(id), header), bytes))
    })();
    let (header, body) = match result {
        Ok(value) => value,
        Err(error) => (wire::error_reply(Some(id), &error), Vec::new()),
    };
    // Reject an oversized header before writing any Arrow bytes; otherwise the
    // unread body would corrupt the next response on this persistent connection.
    match wire::encode_reply(&header) {
        Ok(line) => {
            socket.write_all(&line)?;
            socket.write_all(&body)
        }
        Err(error) => wire::write_reply(socket, &wire::error_reply(Some(id), &error)),
    }
}

struct ConnectionContext {
    profile: crate::profile::Profile,
    shutdown: Arc<AtomicBool>,
    state: Arc<Mutex<State>>,
    ack: Arc<AtomicBool>,
    routes: Routes,
    ring: Arc<Mutex<LiveBuffer>>,
}
impl ConnectionContext {
    /// Record the first terminal error (later errors never mask the root cause)
    /// and end acquisition.
    fn fail(&self, message: String) {
        self.state.lock().unwrap().error.get_or_insert(message);
        self.shutdown.store(true, Ordering::SeqCst);
    }

    fn connect(
        &self,
        device: &str,
        events: &Option<Audit>,
    ) -> Result<(DeviceConnection, Selections)> {
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
        let mut selections = Selections::new();
        // All names/channels were validated before opening the socket. Apply only
        // selections (never enable/control commands) before accepting user commands.
        for (&channel, name) in &self.profile.initial_channels {
            let (id, value) = self.profile.observable(name, channel)?;
            send(&writer, id, value).with_context(|| {
                format!("initial channel {channel} write failed; outcome unknown")
            })?;
            selections.insert(channel, name.clone());
            self.state.lock().unwrap().commands_sent += 1;
            if let Some(audit) = events.as_ref() {
                audit.record(
                    json!({
                        "host_unix_ns":now_ns(),"source":"initial_channels","version":VERSION,
                        "command":{"op":"set_observable","name":name,"channel":channel},
                        "wire":[id,value],"outcome":Outcome::SentUnconfirmed
                    }),
                    &self.state,
                );
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
                        s.user_buttons = crate::protocol::user_buttons(frame.status);
                        s.platform_state = profile
                            .platform_state
                            .as_ref()
                            .and_then(|mapping| mapping.decode(frame.status))
                            .map(str::to_owned);
                    }
                    let frame = Arc::new(frame);
                    ring.lock().unwrap().push(index, frame.clone());
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
        let state = Arc::new(Mutex::new(State::default()));
        let audit = Audit::new(
            BlockedWriter {
                entered: Some(entered_tx),
                release: release_rx,
            },
            state.clone(),
        );
        audit.send(json!({"first": true})).unwrap();
        entered_rx.recv_timeout(Duration::from_secs(2)).unwrap();
        for _ in 0..2048 {
            audit.send(json!({"queued": true})).unwrap();
        }
        assert!(audit.send(json!({"overflow": true})).is_err());
        // Overflow is reported once and never becomes a session error.
        audit.record(json!({"overflow": true}), &state);
        audit.record(json!({"again": true}), &state);
        {
            let state = state.lock().unwrap();
            assert!(state.error.is_none());
            assert!(state.audit_error.as_deref().unwrap().contains("queue full"));
        }
        release_tx.send(()).unwrap();
        audit.finish().unwrap();
    }

    struct FailingWriter;
    impl Write for FailingWriter {
        fn write(&mut self, _: &[u8]) -> std::io::Result<usize> {
            Err(std::io::Error::other("disk full"))
        }
        fn flush(&mut self) -> std::io::Result<()> {
            Ok(())
        }
    }
    #[test]
    fn failed_audit_write_is_reported_without_session_error() {
        let state = Arc::new(Mutex::new(State::default()));
        let audit = Audit::new(FailingWriter, state.clone());
        audit.record(json!({"first": true}), &state);
        audit.finish().unwrap();
        let state = state.lock().unwrap();
        assert!(state.error.is_none());
        assert!(state.audit_error.as_deref().unwrap().contains("disk full"));
    }
}
