//! Firmware job vocabulary and the shared log-draining and completion rules for
//! terminal and Python job followers.
use crate::vitis::VitisAction;
use anyhow::{Context, Result, ensure};
use serde::{Deserialize, Serialize};
use serde_json::Value;

/// Firmware operation submitted to a service (or run locally with `--local`).
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize, clap::ValueEnum)]
#[serde(rename_all = "kebab-case")]
pub enum FirmwareAction {
    /// Generate/build an empty Vitis workspace.
    Generate,
    /// Incrementally build Baremetal and FreeRTOS.
    Build,
    /// Clean, then rebuild both applications.
    BuildClean,
    /// Build, JTAG program and run; reconnects the acquisition session.
    Flash,
}
impl FirmwareAction {
    /// The Vitis step run before any programming.
    pub fn build_step(self) -> VitisAction {
        match self {
            Self::Generate => VitisAction::Generate,
            Self::Build | Self::Flash => VitisAction::Build,
            Self::BuildClean => VitisAction::BuildClean,
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize)]
#[serde(rename_all = "snake_case")]
pub enum JobPhase {
    Preparing,
    /// Finalizing the replaced acquisition session's recordings.
    Finalizing,
    Building,
    Programming,
    LoadingConfiguration,
    Reconnecting,
    Complete,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum JobState {
    Running,
    Succeeded,
    Failed,
}

/// Follower progress after one `job` poll.
#[derive(Debug, Serialize)]
pub struct Progress {
    pub next_offset: u64,
    /// The job ended and its log is fully drained.
    pub complete: bool,
    /// Failure result of a completed failed job.
    pub error: Option<Value>,
}

/// Interpret a `job` reply result polled from `offset`.
pub fn progress(offset: u64, reply: &Value) -> Result<Progress> {
    let next = reply["next_offset"]
        .as_u64()
        .context("job reply has no next_offset")?;
    ensure!(next >= offset, "job log offset moved backwards");
    let state: JobState = serde_json::from_value(reply["job"]["state"].clone())
        .context("job reply has no valid state")?;
    Ok(Progress {
        next_offset: next,
        complete: state != JobState::Running && next == offset,
        error: (state == JobState::Failed).then(|| reply["job"]["result"].clone()),
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::json;

    #[test]
    fn completion_requires_drained_log() {
        let running = json!({"next_offset":4,"job":{"state":"running"}});
        assert!(!progress(0, &running).unwrap().complete);
        let failed = json!({"next_offset":4,"job":{"state":"failed","result":{"ok":false}}});
        assert!(!progress(0, &failed).unwrap().complete);
        let drained = progress(4, &failed).unwrap();
        assert!(drained.complete && drained.error.is_some());
        assert!(progress(5, &failed).is_err());
        assert!(progress(0, &json!({"next_offset":0,"job":{"state":"odd"}})).is_err());
    }
}
