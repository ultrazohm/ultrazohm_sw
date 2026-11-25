//! Acquisition service: configuration, operations and startup.
//!
//! - [`wire`]: API v4 envelope, framing and the client [`Connection`].
//! - [`control`]: client connections and the serialized request queue.
//! - [`controller`]: the persistent controller owning sessions and firmware jobs.
//! - [`session`]: one acquisition session (device connection, recordings, audit).
//! - [`replies`]: typed reply bodies.
use crate::{
    data::{Query, Source, Stream},
    jobs::FirmwareAction,
    live::DataOptions,
    profile::Profile,
    storage::Format,
};
use anyhow::{Context, Result};
use serde::{Deserialize, Serialize};
use std::{
    fs,
    net::TcpListener,
    path::{Path, PathBuf},
    sync::{Arc, Mutex, atomic::AtomicBool},
};

mod control;
mod controller;
pub mod replies;
mod session;
pub mod wire;

pub use replies::RecordingListCursor;
pub use wire::{
    ApiError, Connection, VERSION as API_VERSION, client_error_code, error_code, request,
};
pub(crate) use wire::{coded, exchange};

/// Requested channel assignments: 1-based channel to observable name.
pub type Selections = std::collections::BTreeMap<u32, String>;

pub const DEFAULT_DEVICE_IP: &str = "192.168.1.233";
pub const DEFAULT_DEVICE_PORT: u16 = 1000;
pub const DEFAULT_ENDPOINT: &str = "127.0.0.1:19740";

fn timestamp_directory(parent: &Path) -> PathBuf {
    let now: chrono::DateTime<chrono::Utc> = std::time::SystemTime::now().into();
    parent.join(now.format("%Y%m%d-%H%M%S-%fZ").to_string())
}

/// Resolve session output identically for CLI and embedded Python acquisition.
pub fn session_output(output: Option<PathBuf>) -> Result<PathBuf> {
    session_output_for_repository(output, None)
}
pub fn session_output_for_repository(
    output: Option<PathBuf>,
    repo: Option<&Path>,
) -> Result<PathBuf> {
    if let Some(path) = output {
        return std::path::absolute(path).context("cannot resolve output directory");
    }
    let root = match repo {
        Some(path) => path.to_path_buf(),
        None => crate::vitis::repository(None).or_else(|_| std::env::current_dir())?,
    };
    let artifacts = root.join("artifacts");
    crate::artifacts::ensure_ignore_file(&artifacts)?;
    let parent = artifacts.join("live_logs");
    fs::create_dir_all(&parent)?;
    Ok(timestamp_directory(&parent))
}

/// A sibling of the previous session directory, or a new default directory.
fn replacement_output(previous: Option<&Path>, repo: Option<&Path>) -> Result<PathBuf> {
    match previous.and_then(Path::parent) {
        Some(parent) => Ok(timestamp_directory(parent)),
        None => session_output_for_repository(None, repo),
    }
}

#[derive(Debug, Serialize, Deserialize)]
#[serde(tag = "op", rename_all = "snake_case", deny_unknown_fields)]
pub enum Operation {
    Firmware {
        action: FirmwareAction,
        request_id: String,
        #[serde(default)]
        device: Option<String>,
        #[serde(default)]
        no_reconnect: bool,
    },
    Jobs,
    Job {
        id: String,
        #[serde(default)]
        offset: usize,
    },
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
    RecordingsPage {
        #[serde(default)]
        cursor: Option<RecordingListCursor>,
        limit: usize,
    },
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
    OwnedShutdown {
        service_id: String,
    },
    Shutdown,
}
impl Operation {
    /// Reads have no device or recording side effects and may be retried.
    pub fn read_only(&self) -> bool {
        matches!(
            self,
            Self::Status
                | Self::Jobs
                | Self::Job { .. }
                | Self::Catalog
                | Self::Observables
                | Self::DataInfo { .. }
                | Self::ReadData { .. }
                | Self::RecordingsPage { .. }
        )
    }
    /// Device commands that a later Stop supersedes while still queued.
    /// A queued Stop is kept: every Stop caller receives its own reply.
    pub fn superseded_by_stop(&self) -> bool {
        matches!(
            self,
            Self::EnableSystem
                | Self::EnableControl
                | Self::SetVariable { .. }
                | Self::SetObservable { .. }
                | Self::Button { .. }
        )
    }
    /// Lifecycle requests that survive acquisition-session replacement.
    pub fn survives_session_replacement(&self) -> bool {
        self.read_only()
            || matches!(
                self,
                Self::Stop | Self::Shutdown | Self::OwnedShutdown { .. } | Self::Firmware { .. }
            )
    }
}

#[derive(Clone, Debug)]
pub struct Config {
    pub launch_id: Option<String>,
    pub current_output: Option<Arc<Mutex<PathBuf>>>,
    pub repo: Option<PathBuf>,
    pub xsct: Option<PathBuf>,
    pub device: Option<String>,
    pub endpoint: String,
    pub profile: Profile,
    pub output: Option<PathBuf>,
    pub format: Format,
    pub ack: bool,
    pub data: DataOptions,
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
    let listener = TcpListener::bind(wire::local_address(&config.endpoint)?)?;
    listener.set_nonblocking(true)?;
    controller::run(config, shutdown, listener, ready)
}
