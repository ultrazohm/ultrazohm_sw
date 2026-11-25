//! Local Vitis operations; independent of the acquisition service.
use anyhow::{Context, Result, bail, ensure};
use std::{
    env,
    path::{Path, PathBuf},
    process::Command,
};

include!(concat!(env!("OUT_DIR"), "/firmware_resources.rs"));

/// Actions of `tcl_scripts/vitis_headless.tcl`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum VitisAction {
    Open,
    Generate,
    GenerateOpen,
    Build,
    BuildClean,
    /// JTAG program and run the already built applications.
    ProgramBuilt,
}
impl VitisAction {
    pub fn as_str(self) -> &'static str {
        match self {
            Self::Open => "open",
            Self::Generate => "generate",
            Self::GenerateOpen => "generate-open",
            Self::Build => "build",
            Self::BuildClean => "build-clean",
            Self::ProgramBuilt => "program-built",
        }
    }
    /// Only Linux XSCT distinguishes GUI actions (see `-nodisp` below).
    #[cfg(target_os = "linux")]
    fn opens_gui(self) -> bool {
        matches!(self, Self::Open | Self::GenerateOpen)
    }
}

/// Launch configuration used to program and run the firmware.
pub const RUN_PROFILE: &str = "Run_UltraZohm";

// Called under the firmware checkout lock. Content-addressed paths preserve
// incremental-build signatures across processes and survive GUI termination.
fn entry_script(root: &Path) -> Result<PathBuf> {
    if let Some(directory) = env::var_os("UZ_CLI_TCL_DIR") {
        let path = std::path::absolute(PathBuf::from(directory).join("vitis_headless.tcl"))?;
        ensure!(
            path.is_file(),
            "Vitis entry script not found: {}",
            path.display()
        );
        return Ok(path);
    }
    let directory = root
        .join("artifacts/cli-tools")
        .join(RESOURCE_ID)
        .join("tcl_scripts");
    for (name, contents) in RESOURCES {
        let path = directory.join(name);
        if std::fs::read(&path).ok().as_deref() != Some(*contents) {
            std::fs::create_dir_all(path.parent().unwrap())?;
            std::fs::write(&path, contents)?;
        }
    }
    Ok(directory.join("vitis_headless.tcl"))
}

fn is_repository(path: &Path) -> bool {
    path.join("vitis/software/Baremetal/src/include/javascope.h")
        .is_file()
}

pub fn repository(explicit: Option<&Path>) -> Result<PathBuf> {
    if let Some(path) = explicit {
        let root = std::path::absolute(path)
            .with_context(|| format!("cannot access repository {}", path.display()))?;
        ensure!(
            is_repository(&root),
            "{} is not an UltraZohm repository with vitis/software/Baremetal/src/include/javascope.h",
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

pub(crate) fn xsct() -> Result<PathBuf> {
    #[cfg(windows)]
    let names = ["xsct.exe", "xsct.cmd", "xsct.bat"];
    #[cfg(not(windows))]
    let names = ["xsct"];
    for dir in env::split_paths(&env::var_os("PATH").unwrap_or_default()) {
        for name in names {
            let path = dir.join(name);
            if crate::preferences::validate_xsct(&path).is_ok() {
                // Resolve relative PATH entries before changing the child's cwd.
                return std::path::absolute(path).context("cannot resolve XSCT launcher");
            }
        }
    }
    bail!(
        "Vitis XSCT (xsct) not found on PATH. Load the Vitis 2022.2 environment (settings64.sh on Linux or a Vitis command prompt on Windows), then retry. These commands require XSCT, not only the Vitis GUI."
    )
}

/// Run Vitis steps locally under the checkout lock, without a service.
pub fn run(steps: &[(VitisAction, Option<&str>)], repo: Option<&Path>) -> Result<()> {
    let root = repository(repo)?;
    let artifacts = root.join("artifacts");
    crate::artifacts::ensure_ignore_file(&artifacts)?;
    let lock = std::fs::OpenOptions::new()
        .create(true)
        .truncate(false)
        .read(true)
        .write(true)
        .open(artifacts.join("firmware.lock"))?;
    lock.try_lock().context("firmware workspace is in use")?;
    for (action, profile) in steps {
        execute(*action, Some(&root), *profile, None, None)?;
    }
    Ok(())
}

pub(crate) fn execute(
    action: VitisAction,
    repo: Option<&Path>,
    profile: Option<&str>,
    log: Option<&std::fs::File>,
    xsct_override: Option<&Path>,
) -> Result<()> {
    let root = repository(repo)?;
    let script = entry_script(&root)?;
    let executable = crate::preferences::resolve_xsct(xsct_override, Some(&root))?;
    eprintln!("Vitis {}: repository {}", action.as_str(), root.display());
    // Every caller holds the checkout lock. Clear the previous receipt before
    // each invocation: XSCT can exit zero before it even runs our Tcl script.
    let completion = root.join("artifacts/firmware-completed");
    match std::fs::remove_file(&completion) {
        Ok(()) => (),
        Err(error) if error.kind() == std::io::ErrorKind::NotFound => (),
        Err(error) => return Err(error.into()),
    }
    let mut command = Command::new(&executable);
    // Linux XSCT owns display validation and Xvfb lifecycle. -nodisp skips
    // that setup; it is appropriate only when opening an existing desktop.
    #[cfg(target_os = "linux")]
    {
        command.arg("-norlwrap");
        if action.opens_gui() {
            command.arg("-nodisp");
        }
    }
    command
        .current_dir(&root)
        .env("UZ_WORKSPACE_ROOT", &root)
        .env("UZ_VITIS_COMPLETION", &completion)
        .arg(script)
        .arg(action.as_str());
    if let Some(profile) = profile {
        command.arg(profile);
    }
    if let Some(log) = log {
        command.stdout(log.try_clone()?).stderr(log.try_clone()?);
    }
    let status = command
        .status()
        .with_context(|| format!("failed to start Vitis XSCT at {}", executable.display()))?;
    let completed = std::fs::read_to_string(&completion).ok().as_deref() == Some(action.as_str());
    let action = action.as_str();
    let _ = std::fs::remove_file(&completion);
    ensure!(
        status.success(),
        "Vitis {action} failed ({status}); see XSCT output above and {}/vitis/workspace/IDE.log (check timestamps). On Linux, batch firmware operations need xlsclients and, without a usable display, Xvfb on the service host.",
        root.display()
    );
    ensure!(
        completed,
        "Vitis {action} did not confirm completion despite {status}; XSCT may have failed before running Tcl. See XSCT output and the firmware job log."
    );
    Ok(())
}
