//! Shared startup preferences and vendor tool selection, also used without Python.
use crate::profile::{ChannelMapping, Profile, ProfileSettings};
use anyhow::{Context, Result, ensure};
use serde_json::Value;
use std::{
    env, fs,
    io::Write,
    path::{Path, PathBuf},
    sync::atomic::{AtomicU64, Ordering},
};

pub fn directory(repo: Option<&Path>) -> Result<PathBuf> {
    let discovered = if repo.is_none() {
        crate::vitis::repository(None).ok()
    } else {
        None
    };
    if let Some(repo) = repo.or(discovered.as_deref()) {
        return Ok(repo.join("artifacts/_user"));
    }
    let home = env::var_os(if cfg!(windows) { "USERPROFILE" } else { "HOME" })
        .context("home directory unavailable")?;
    let base = if cfg!(windows) {
        PathBuf::from(
            env::var_os("LOCALAPPDATA")
                .unwrap_or_else(|| PathBuf::from(&home).join("AppData/Local").into_os_string()),
        )
        .join("UltraZohm")
    } else {
        PathBuf::from(
            env::var_os("XDG_DATA_HOME")
                .unwrap_or_else(|| PathBuf::from(&home).join(".local/share").into_os_string()),
        )
        .join("ultrazohm")
    };
    Ok(base.join("ultrazohm_dataviewer"))
}

pub fn write_json(path: &Path, value: &impl serde::Serialize, overwrite: bool) -> Result<()> {
    static SEQUENCE: AtomicU64 = AtomicU64::new(0);
    let parent = path.parent().context("settings path has no parent")?;
    fs::create_dir_all(parent)?;
    let bytes = serde_json::to_vec_pretty(value)?;
    let temporary = parent.join(format!(
        ".uz-settings-{}-{}-{}.tmp",
        std::process::id(),
        std::time::SystemTime::now()
            .duration_since(std::time::UNIX_EPOCH)?
            .as_nanos(),
        SEQUENCE.fetch_add(1, Ordering::Relaxed)
    ));
    let result = (|| -> Result<()> {
        let mut file = fs::OpenOptions::new()
            .create_new(true)
            .write(true)
            .open(&temporary)?;
        file.write_all(&bytes)?;
        file.sync_all()?;
        drop(file);
        if overwrite {
            fs::rename(&temporary, path)?;
        } else {
            match crate::backend::publish_new(&temporary, path) {
                Ok(()) => (),
                Err(e) if e.kind() == std::io::ErrorKind::AlreadyExists => (),
                Err(e) => return Err(e.into()),
            }
        }
        Ok(())
    })();
    let _ = fs::remove_file(&temporary);
    result
}

pub fn load_or_seed(path: &Path, mapping: &ChannelMapping) -> Result<ProfileSettings> {
    if !path.exists() {
        let defaults = ProfileSettings::for_mapping(None, mapping)?;
        Profile::from_mapping(defaults.clone(), mapping.clone())?;
        write_json(path, &defaults, false)?;
    }
    let settings = ProfileSettings::load(Some(path))?;
    write_json(
        &path.parent().context("profile parent")?.join("tools.json"),
        &serde_json::json!({"xsct": null}),
        false,
    )?;
    Ok(settings)
}

pub fn save_profile(
    path: &Path,
    settings: &ProfileSettings,
    mapping: &ChannelMapping,
) -> Result<()> {
    settings.validate()?;
    Profile::from_mapping(settings.clone(), mapping.clone())?;
    write_json(path, settings, true)
}

pub fn selected_profile(explicit: Option<&Path>, repo: Option<&Path>) -> Result<Option<PathBuf>> {
    if let Some(path) = explicit {
        return Ok(Some(path.to_path_buf()));
    }
    if let Some(repo) = repo {
        let saved = directory(Some(repo))?.join("settings.json");
        if saved.is_file() {
            return Ok(Some(saved));
        }
    }
    Ok(None)
}

pub fn validate_xsct(path: &Path) -> Result<PathBuf> {
    ensure!(
        path.is_file(),
        "XSCT launcher not found: {}",
        path.display()
    );
    #[cfg(unix)]
    {
        use std::os::unix::fs::PermissionsExt;
        ensure!(
            fs::metadata(path)?.permissions().mode() & 0o111 != 0,
            "XSCT launcher is not executable: {}",
            path.display()
        );
    }
    std::path::absolute(path).context("resolve XSCT launcher")
}

pub fn saved_xsct(repo: Option<&Path>) -> Result<Option<PathBuf>> {
    let path = directory(repo)?.join("tools.json");
    if !path.exists() {
        return Ok(None);
    }
    let value: Value = serde_json::from_slice(&fs::read(&path)?)?;
    ensure!(
        value.is_object(),
        "Invalid tool preferences: expected object"
    );
    match value.get("xsct") {
        None | Some(Value::Null) => Ok(None),
        Some(Value::String(path)) => Ok(Some(validate_xsct(Path::new(path))?)),
        _ => anyhow::bail!("Invalid tool preferences: XSCT path must be a string or null"),
    }
}

pub fn resolve_xsct(explicit: Option<&Path>, repo: Option<&Path>) -> Result<PathBuf> {
    if let Some(path) = explicit {
        return validate_xsct(path);
    }
    if let Some(path) = saved_xsct(repo)? {
        return Ok(path);
    }
    crate::vitis::xsct()
}

pub fn save_xsct(path: &Path, repo: Option<&Path>) -> Result<PathBuf> {
    let launcher = validate_xsct(path)?;
    let settings = directory(repo)?.join("tools.json");
    let mut value: Value = if settings.exists() {
        serde_json::from_slice(&fs::read(&settings)?)?
    } else {
        serde_json::json!({})
    };
    ensure!(
        value.is_object(),
        "Invalid tool preferences: expected object"
    );
    value["xsct"] = serde_json::to_value(&launcher)?;
    write_json(&settings, &value, true)?;
    Ok(launcher)
}

#[cfg(test)]
mod publication_tests {
    use super::*;
    #[test]
    fn publication_preserves_existing_preferences() {
        let dir =
            std::env::temp_dir().join(format!("uz-preferences-review-{}", std::process::id()));
        fs::create_dir_all(&dir).unwrap();
        let path = dir.join("settings.json");
        write_json(&path, &serde_json::json!({"saved": true}), true).unwrap();
        write_json(&path, &serde_json::json!({"saved": false}), false).unwrap();
        assert_eq!(
            serde_json::from_slice::<Value>(&fs::read(&path).unwrap()).unwrap()["saved"],
            true
        );
        fs::remove_dir_all(dir).unwrap();
    }
}
