use anyhow::{Context, Result, ensure};
use serde::{Deserialize, Serialize};
use std::{collections::BTreeMap, path::Path};

/// Runtime preferences; independent of firmware signal IDs.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct ProfileSettings {
    pub schema_version: u32,
    pub name: String,
    pub sample_period_us: f64,
    #[serde(default)]
    pub initial_channels: BTreeMap<u32, String>,
}
impl ProfileSettings {
    pub fn load(path: Option<&Path>) -> Result<Self> {
        let text = match path {
            Some(p) => std::fs::read_to_string(p)
                .with_context(|| format!("reading profile {}", p.display()))?,
            None => include_str!("../profiles/standard.json").to_owned(),
        };
        let settings: Self = serde_json::from_str(&text)
            .context("invalid runtime profile (use --channel-mapping for firmware IDs)")?;
        ensure!(
            settings.schema_version == 1,
            "unsupported profile schema_version"
        );
        Ok(settings)
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Repository {
    pub name: String,
    pub commit: String,
}

/// Two-bit platform-state field and its user-facing names, supplied by firmware mapping.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct PlatformStateMapping {
    pub mask: u32,
    pub shift: u32,
    pub values: BTreeMap<u32, String>,
}
impl PlatformStateMapping {
    pub fn validate(&self) -> Result<()> {
        ensure!(self.shift <= 30, "platform_state.shift must be 0..30");
        ensure!(
            self.mask == (3_u32 << self.shift),
            "platform_state.mask must select two bits at shift"
        );
        ensure!(
            self.values.len() == 4
                && (0..4).all(|code| self
                    .values
                    .get(&code)
                    .is_some_and(|name| !name.trim().is_empty())),
            "platform_state.values must name codes 0, 1, 2, and 3"
        );
        Ok(())
    }
    pub fn decode(&self, status: u32) -> Option<&str> {
        self.values
            .get(&((status & self.mask).checked_shr(self.shift)?))
            .map(String::as_str)
    }
}

/// Firmware wire geometry, names and IDs. Provenance is descriptive, not device readback.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct ChannelMapping {
    pub api_version: u32,
    pub name: String,
    pub repository: Repository,
    pub channels: usize,
    pub samples_per_packet: usize,
    pub observables: BTreeMap<String, u32>,
    pub slow_signals: BTreeMap<String, u32>,
    pub variables: BTreeMap<String, u32>,
    pub commands: BTreeMap<String, u32>,
    pub platform_state: PlatformStateMapping,
}
impl ChannelMapping {
    pub fn load(path: Option<&Path>) -> Result<Self> {
        let Some(path) = path else {
            let root = crate::vitis::repository(None).context(
                "generating firmware mapping requires a checkout; run from the repository or pass --channel-mapping with header-generated JSON",
            )?;
            return crate::header_mapping::generate(&root);
        };
        let text = std::fs::read_to_string(path)
            .with_context(|| format!("reading channel mapping {}", path.display()))?;
        let mapping: Self =
            serde_json::from_str(&text).context("invalid firmware channel mapping")?;
        mapping.platform_state.validate()?;
        Ok(mapping)
    }
}

/// Validated combination used internally and saved in run metadata.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Profile {
    pub api_version: u32,
    pub channel_mapping_name: String,
    pub repository: Repository,
    pub initial_channels: BTreeMap<u32, String>,
    pub name: String,
    pub channels: usize,
    pub samples_per_packet: usize,
    pub sample_period_us: f64,
    pub observables: BTreeMap<String, u32>,
    pub slow_signals: BTreeMap<String, u32>,
    pub variables: BTreeMap<String, u32>,
    pub commands: BTreeMap<String, u32>,
    pub platform_state: PlatformStateMapping,
}
impl Profile {
    pub fn load(path: Option<&Path>) -> Result<Self> {
        Self::load_files(path, None)
    }
    pub fn load_files(profile: Option<&Path>, mapping: Option<&Path>) -> Result<Self> {
        let settings = ProfileSettings::load(profile)?;
        let mapping = ChannelMapping::load(mapping)?;
        Self::from_mapping(settings, mapping)
    }
    pub fn from_mapping(settings: ProfileSettings, mapping: ChannelMapping) -> Result<Self> {
        let p = Self {
            api_version: mapping.api_version,
            name: settings.name,
            channel_mapping_name: mapping.name,
            repository: mapping.repository,
            initial_channels: settings.initial_channels,
            channels: mapping.channels,
            samples_per_packet: mapping.samples_per_packet,
            sample_period_us: settings.sample_period_us,
            observables: mapping.observables,
            slow_signals: mapping.slow_signals,
            variables: mapping.variables,
            commands: mapping.commands,
            platform_state: mapping.platform_state,
        };
        p.validate()?;
        Ok(p)
    }
    pub fn validate(&self) -> Result<()> {
        self.platform_state.validate()?;
        ensure!(
            self.api_version == 1 && self.channels == 20,
            "requires v1 profile and 20-channel firmware"
        );
        ensure!(
            (1..=4096).contains(&self.samples_per_packet),
            "samples_per_packet must be 1..4096"
        );
        ensure!(
            self.sample_period_us.is_finite() && self.sample_period_us > 0.0,
            "invalid sample period"
        );
        ensure!(
            !self.slow_signals.is_empty() && self.slow_signals.len() <= 65536,
            "invalid slow signal table"
        );
        let mut ids: Vec<_> = self.slow_signals.values().copied().collect();
        ids.sort_unstable();
        ensure!(
            ids == (0..ids.len() as u32).collect::<Vec<_>>(),
            "slow IDs must be contiguous from zero"
        );
        ensure!(
            self.variables.values().all(|id| (4..=23).contains(id)),
            "variable IDs must be send fields 4..23"
        );
        ensure!(
            self.observables.values().all(|&id| id < 16777216),
            "observable ID not exactly representable as float32"
        );
        ensure!(
            !self.repository.name.trim().is_empty() && !self.repository.commit.trim().is_empty(),
            "mapping repository name and commit must not be empty"
        );
        for (&channel, name) in &self.initial_channels {
            self.observable(name, channel)
                .with_context(|| format!("invalid initial channel {channel}"))?;
        }
        Ok(())
    }
    pub fn command(&self, name: &str) -> Result<u32> {
        self.commands
            .get(name)
            .copied()
            .with_context(|| format!("command absent from profile: {name}"))
    }
    pub fn variable(&self, name: &str) -> Result<u32> {
        self.variables
            .get(name)
            .copied()
            .with_context(|| format!("unknown writable variable: {name}"))
    }
    pub fn observable(&self, name: &str, channel: u32) -> Result<(u32, f32)> {
        ensure!((1..=20).contains(&channel), "channel must be 1..20");
        let id = self
            .observables
            .get(name)
            .or_else(|| self.observables.get(&format!("JSO_{name}")))
            .with_context(|| format!("unknown observable: {name}"))?;
        Ok((200 + channel, *id as f32))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn platform_state_uses_mapping_and_preserves_feedback() {
        let mut mapping = ChannelMapping::load(None).unwrap().platform_state;
        for (code, name) in [(0, "idle"), (1, "running"), (2, "control"), (3, "error")] {
            for feedback in [0, 1, 15, 0x3FFF_FFFF] {
                assert_eq!(mapping.decode((code << 30) | feedback), Some(name));
            }
        }
        mapping.values.insert(1, "enabled".into());
        assert_eq!(mapping.decode(0x4000_0001), Some("enabled"));
        mapping.shift = 4;
        mapping.mask = 0x30;
        mapping.validate().unwrap();
        assert_eq!(mapping.decode(0xFFFF_FFDF), Some("enabled"));
    }

    #[test]
    fn rejects_invalid_state_mappings() {
        let original = ChannelMapping::load(None).unwrap().platform_state;
        let mut mapping = original.clone();
        mapping.shift = 32;
        assert!(mapping.validate().is_err());
        mapping = original.clone();
        mapping.mask = 1;
        assert!(mapping.validate().is_err());
        mapping = original.clone();
        mapping.values.remove(&3);
        assert!(mapping.validate().is_err());
        mapping = original;
        mapping.values.insert(0, " ".into());
        assert!(mapping.validate().is_err());
    }
}
