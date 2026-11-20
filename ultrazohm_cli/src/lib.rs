mod artifacts;
pub mod backend;
pub mod cli;
pub mod data;
mod header_mapping;
pub mod live;
pub mod profile;
pub mod protocol;
#[cfg(feature = "python")]
mod python;
mod recording;
pub mod service;
pub mod storage;
mod vitis;

/// Software version: the release version stamped by CI, otherwise the crate version.
/// Shown by `--version`, `status` and stored in each run's `run.json`.
pub const VERSION: &str = match option_env!("UZ_CLI_RELEASE_VERSION") {
    Some(version) => version,
    None => env!("CARGO_PKG_VERSION"),
};
