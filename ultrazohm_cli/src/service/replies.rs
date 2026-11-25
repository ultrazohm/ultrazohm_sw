//! Typed reply bodies (the envelope's `result`). See docs/protocol.md.
use super::session::State;
use crate::{
    data::{Cursor, DataInfo},
    jobs::{FirmwareAction, JobPhase, JobState},
    live::DataOptions,
    profile::Profile,
    recording::RecordingsStatus,
};
use serde::{Deserialize, Serialize};
use std::path::PathBuf;

/// What happened to a command. Device commands have no acknowledgment.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize)]
#[serde(rename_all = "snake_case")]
pub enum Outcome {
    /// Written to the device; the firmware does not confirm receipt.
    SentUnconfirmed,
    /// Executed by the service without a device write.
    AppliedLocally,
    /// No device connection; nothing was sent.
    Disconnected,
}

#[derive(Serialize)]
pub struct CommandReply {
    pub outcome: Outcome,
    pub logging: Option<RecordingsStatus>,
}

/// Session part of the status reply; absent fields mean no acquisition session.
#[derive(Serialize)]
pub struct SessionStatus {
    pub send_ack: bool,
    pub logging: RecordingsStatus,
    pub data_options: DataOptions,
    pub buffer_available_samples: usize,
}

#[derive(Clone, Copy, Serialize)]
#[serde(rename_all = "snake_case")]
pub enum Lifecycle {
    Ready,
    Disconnected,
    FirmwareJob,
    Finalizing,
    ShuttingDown,
}

#[derive(Serialize)]
pub struct StatusReply {
    pub state: State,
    #[serde(flatten)]
    pub session: Option<SessionStatus>,
    pub software_version: &'static str,
    pub service_id: String,
    pub session_id: Option<String>,
    /// Changes whenever the catalog or the requested observables may have
    /// changed: refresh `catalog` and `observables` only when it differs.
    pub configuration_revision: Option<String>,
    pub output: Option<PathBuf>,
    pub repository: Option<PathBuf>,
    pub device_target: Option<String>,
    pub firmware_available: bool,
    pub active_job: Option<JobStatus>,
    pub error: Option<String>,
    pub configuration_valid: bool,
    pub lifecycle: Lifecycle,
    pub shutting_down: bool,
}

#[derive(Clone, Debug, Serialize)]
pub struct JobResult {
    pub ok: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub error: Option<String>,
}

#[derive(Clone, Debug, Serialize)]
pub struct JobStatus {
    pub id: String,
    pub request_id: String,
    pub action: FirmwareAction,
    pub phase: JobPhase,
    pub state: JobState,
    pub result: Option<JobResult>,
}

#[derive(Serialize)]
pub struct JobReply {
    pub job: JobStatus,
}

#[derive(Serialize)]
pub struct JobsReply {
    pub jobs: Vec<JobStatus>,
}

#[derive(Serialize)]
pub struct JobLogReply {
    pub job: JobStatus,
    /// Log text from `offset`.
    pub log: String,
    pub next_offset: u64,
}

#[derive(Serialize)]
pub struct CatalogReply<'a> {
    pub profile: &'a Profile,
    pub device_readback: bool,
}

#[derive(Clone, Copy, Serialize)]
#[serde(rename_all = "snake_case")]
pub enum AssignmentState {
    SentUnconfirmed,
    Unknown,
}

#[derive(Serialize)]
pub struct ObservableChannel {
    pub channel: u32,
    pub name: Option<String>,
    pub id: Option<u32>,
    pub state: AssignmentState,
}

#[derive(Serialize)]
pub struct ObservablesReply {
    pub source: &'static str,
    pub device_readback: bool,
    pub channels: Vec<ObservableChannel>,
}

#[derive(Serialize)]
pub struct ShutdownReply {
    pub shutdown_requested: bool,
    /// A firmware job or finalization runs first.
    pub deferred: bool,
    pub service_id: String,
    pub outcome: Option<Outcome>,
}

#[derive(Serialize)]
pub struct DataInfoReply {
    pub info: DataInfo,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct RecordingListCursor {
    pub(super) run_id: String,
    pub(super) upper: [u64; 2],
    pub(super) offset: usize,
}

#[derive(Serialize)]
pub struct RecordingsPageReply {
    pub recordings: Vec<DataInfo>,
    pub next_cursor: Option<RecordingListCursor>,
}

/// Header of a `read_data` reply; `arrow_bytes` of Arrow IPC follow it.
#[derive(Serialize)]
pub struct DataReply<'a> {
    pub info: &'a DataInfo,
    pub cursor: Cursor,
    pub start: u64,
    pub stop: u64,
    pub rows: usize,
    pub arrow_bytes: usize,
    pub mapping_confirmed: bool,
}
