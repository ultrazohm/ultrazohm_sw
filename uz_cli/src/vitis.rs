//! Local Vitis operations; independent of the acquisition service.
use anyhow::{Context, Result, bail, ensure};
use std::{
    env,
    path::{Path, PathBuf},
    process::Command,
};

const SCRIPT: &str = "tcl_scripts/vitis_headless.tcl";

fn is_repository(path: &Path) -> bool {
    path.join(SCRIPT).is_file() && path.join("vitis/software").is_dir()
}

pub fn repository(explicit: Option<&Path>) -> Result<PathBuf> {
    if let Some(path) = explicit {
        let root = std::path::absolute(path)
            .with_context(|| format!("cannot access repository {}", path.display()))?;
        ensure!(
            is_repository(&root),
            "{} is not an UltraZohm repository with {SCRIPT} and vitis/software",
            root.display()
        );
        return Ok(root);
    }
    let cwd = env::current_dir().context("cannot determine current directory")?;
    for path in cwd.ancestors() {
        if is_repository(path) {
            return Ok(path.to_path_buf());
        }
    }
    bail!(
        "UltraZohm repository not found above {}; run from the checkout or pass --repo PATH",
        cwd.display()
    )
}

fn xsct() -> Result<PathBuf> {
    #[cfg(windows)]
    let names = ["xsct.exe", "xsct.cmd", "xsct.bat"];
    #[cfg(not(windows))]
    let names = ["xsct"];
    for dir in env::split_paths(&env::var_os("PATH").unwrap_or_default()) {
        for name in names {
            let path = dir.join(name);
            if path.is_file() {
                // Resolve relative PATH entries before changing the child's cwd.
                return std::path::absolute(path).context("cannot resolve XSCT launcher");
            }
        }
    }
    bail!(
        "Vitis XSCT (xsct) not found on PATH. Load the Vitis 2022.2 environment (settings64.sh on Linux or a Vitis command prompt on Windows), then retry. These commands require XSCT, not only the Vitis GUI."
    )
}

pub fn run(action: &str, repo: Option<&Path>, profile: Option<&str>) -> Result<()> {
    let root = repository(repo)?;
    let executable = xsct()?;
    eprintln!("Vitis {action}: repository {}", root.display());
    let mut command = Command::new(&executable);
    command
        .current_dir(&root)
        .arg("-nodisp")
        .arg(root.join(SCRIPT))
        .arg(action);
    if let Some(profile) = profile {
        command.arg(profile);
    }
    let status = command
        .status()
        .with_context(|| format!("failed to start Vitis XSCT at {}", executable.display()))?;
    ensure!(
        status.success(),
        "Vitis {action} failed ({status}); see XSCT output above"
    );
    Ok(())
}
