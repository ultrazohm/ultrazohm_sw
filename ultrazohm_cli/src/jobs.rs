//! Shared log-draining and completion rules for terminal and Python job followers.
use anyhow::{Context, Result, ensure};
use serde_json::Value;

pub fn progress(offset: u64, reply: &Value) -> Result<Value> {
    let next = reply["next_offset"]
        .as_u64()
        .context("job reply has no next_offset")?;
    ensure!(next >= offset, "job log offset moved backwards");
    let state = reply["job"]["state"]
        .as_str()
        .context("job reply has no state")?;
    ensure!(
        ["running", "succeeded", "failed"].contains(&state),
        "unknown job state"
    );
    Ok(serde_json::json!({
        "next_offset": next,
        "complete": state != "running" && next == offset,
        "error": if state == "failed" { reply["job"]["result"].clone() } else { Value::Null },
    }))
}
