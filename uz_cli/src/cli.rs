use crate::{
    profile::{ChannelMapping, Profile, ProfileSettings},
    service::{self, Config, Operation},
    storage::Format,
};
use anyhow::{Result, bail};
use clap::{Parser, Subcommand};
use std::{
    io::{self, BufRead, Write},
    path::PathBuf,
    sync::{
        Arc,
        atomic::{AtomicBool, Ordering},
    },
};
#[derive(Parser)]
#[command(version = option_env!("ULTRAZOHM_RELEASE_VERSION").unwrap_or(env!("CARGO_PKG_VERSION")), about = "Standalone UltraZohm control and acquisition")]
struct Args {
    #[arg(long,global=true,default_value=service::DEFAULT_ENDPOINT)]
    endpoint: String,
    #[command(subcommand)]
    command: Option<Command>,
}
#[derive(Subcommand)]
enum Command {
    /// Generate/build an empty Vitis workspace (optionally open the GUI).
    #[command(alias = "generate-workspace")]
    Generate {
        /// Repository root; otherwise search upward from the current directory.
        #[arg(long)]
        repo: Option<PathBuf>,
        #[arg(long)]
        open: bool,
    },
    /// Incrementally build Baremetal and FreeRTOS (including platform dependencies).
    Build {
        #[arg(long)]
        repo: Option<PathBuf>,
    },
    /// Clean the platform and applications, then rebuild both applications.
    BuildClean {
        #[arg(long)]
        repo: Option<PathBuf>,
    },
    /// Build, then JTAG program and run. Does not write persistent flash memory.
    Flash {
        #[arg(long)]
        repo: Option<PathBuf>,
        #[arg(long, default_value = "Run_UltraZohm", value_parser = ["Run_UltraZohm"])]
        profile: String,
    },
    /// Run the control service until Ctrl-C or shutdown; starts disconnected by default. Run as an OS service for unattended use.
    Serve {
        /// Connect immediately instead of waiting for the connect command.
        #[arg(long)]
        device: Option<String>,
        #[arg(long)]
        profile: Option<PathBuf>,
        /// Firmware names, numeric IDs, wire geometry and repository provenance.
        #[arg(long)]
        channel_mapping: Option<PathBuf>,
        /// New session directory; logging stays off until start-logging commands.
        #[arg(long)]
        output: Option<PathBuf>,
        /// parquet: final Parquet only; csv/both: also convert the final Parquet to CSV.
        #[arg(long, value_enum, default_value = "parquet")]
        format: Format,
        #[arg(long,default_value="off",value_parser=["on","off"])]
        ack: String,
        /// Read commands at a prompt while acquisition runs. EOF ends the service.
        #[arg(long)]
        interactive: bool,
    },
    /// Begin fast recording in the session output directory.
    #[command(alias = "start_logging")]
    StartLogging,
    /// Stop fast recording and finalize it in the background; check status.
    #[command(alias = "stop_logging")]
    StopLogging,
    #[command(alias = "start_logging_slow_data")]
    StartLoggingSlowData,
    #[command(alias = "stop_logging_slow_data")]
    StopLoggingSlowData,
    /// Connect to a device and apply the configured initial observables.
    Connect {
        #[arg(default_value = service::DEFAULT_DEVICE_IP)]
        ip: String,
        #[arg(default_value_t = service::DEFAULT_DEVICE_PORT)]
        port: u16,
    },
    Status,
    /// List all channel assignments requested in this service session (not device readback).
    #[command(aliases = ["get-observables", "get_observables"])]
    Observables,
    Stop,
    #[command(alias = "enable_system")]
    EnableSystem,
    #[command(alias = "enable_control")]
    EnableControl,
    #[command(alias = "error_reset")]
    ErrorReset,
    #[command(alias = "set_variable")]
    SetVariable {
        name: String,
        #[arg(allow_hyphen_values = true)]
        value: f32,
    },
    /// Select a named observable into a 1-based channel; does not write the signal.
    #[command(alias = "set_observable")]
    SetObservable {
        name: String,
        channel: u32,
    },
    Button {
        number: u32,
    },
    #[command(alias = "send_ack")]
    SendAck {
        #[arg(value_parser=["on","off"])]
        enabled: String,
    },
    /// End acquisition and flush logs. Does not send the device Stop command.
    Shutdown,
    /// Print the built-in runtime profile (initial channels and sampling period).
    Profile,
    /// Print the built-in firmware channel mapping (IDs and provenance).
    ChannelMapping,
}
#[derive(Parser)]
#[command(
    name = "",
    about = "UltraZohm interactive commands (space-separated arguments)"
)]
struct InteractiveArgs {
    #[command(subcommand)]
    command: Command,
}

/// Shared entry point for the standalone executable and Python console script.
/// Return an exit code instead of exiting the interpreter for help/parse errors.
pub fn run(argv: impl IntoIterator<Item = String>) -> i32 {
    let args = match Args::try_parse_from(argv) {
        Ok(args) => args,
        Err(error) => {
            let code = error.exit_code();
            let _ = error.print();
            return code;
        }
    };
    match dispatch(args) {
        Ok(()) => 0,
        Err(error) => {
            eprintln!("Error: {error:#}");
            1
        }
    }
}

fn dispatch(args: Args) -> Result<()> {
    let command = args.command.unwrap_or_else(|| {
        let now: chrono::DateTime<chrono::Utc> = std::time::SystemTime::now().into();
        let output = PathBuf::from(format!("measurement-{}", now.format("%Y%m%d-%H%M%S-%fZ")));
        eprintln!(
            "Session output: {} (Parquet and CSV; logging starts on request)",
            output.display()
        );
        Command::Serve {
            device: None,
            profile: None,
            channel_mapping: None,
            output: Some(output),
            format: Format::Both,
            ack: "off".into(),
            interactive: true,
        }
    });
    match command {
        Command::Serve {
            device,
            profile,
            channel_mapping,
            output,
            format,
            ack,
            interactive,
        } => {
            let shutdown = Arc::new(AtomicBool::new(false));
            let signal = shutdown.clone();
            ctrlc::set_handler(move || signal.store(true, Ordering::SeqCst))?;
            let endpoint = args.endpoint.clone();
            let stopped = shutdown.clone();
            service::serve_with_ready(
                Config {
                    device,
                    endpoint: args.endpoint,
                    profile: Profile::load_files(profile.as_deref(), channel_mapping.as_deref())?,
                    output,
                    format,
                    ack: ack == "on",
                },
                shutdown,
                move || {
                    if interactive {
                        // Only the stdin reader is detached. The main thread still waits
                        // for acquisition and logging, even if stdin remains blocked.
                        std::thread::spawn(move || {
                            if let Err(error) = prompt(&endpoint, &stopped) {
                                eprintln!("Interactive input: {error:#}");
                            }
                            stopped.store(true, Ordering::SeqCst);
                        });
                    }
                },
            )
        }
        command => execute(command, &args.endpoint),
    }
}

// Quotes group paths containing spaces. Backslashes remain literal, including
// Windows paths; this prompt does not perform shell expansion or escape processing.
fn prompt_words(line: &str) -> Result<Vec<String>> {
    let mut words = Vec::new();
    let mut word = String::new();
    let mut quote = None;
    let mut started = false;
    for ch in line.chars() {
        if let Some(delimiter) = quote {
            if ch == delimiter {
                quote = None;
            } else {
                word.push(ch);
            }
        } else if ch == '\'' || ch == '"' {
            quote = Some(ch);
            started = true;
        } else if ch.is_whitespace() {
            if started {
                words.push(std::mem::take(&mut word));
                started = false;
            }
        } else {
            word.push(ch);
            started = true;
        }
    }
    if quote.is_some() {
        bail!("unclosed quote in command");
    }
    if started {
        words.push(word);
    }
    Ok(words)
}

fn prompt(endpoint: &str, shutdown: &AtomicBool) -> Result<()> {
    eprintln!(
        "Type help for commands. shutdown, Ctrl-C or EOF ends acquisition and finalizes logs."
    );
    let stdin = io::stdin();
    let mut input = stdin.lock();
    while !shutdown.load(Ordering::SeqCst) {
        print!("ultrazohm> ");
        io::stdout().flush()?;
        let mut line = String::new();
        if input.read_line(&mut line)? == 0 {
            break;
        }
        if shutdown.load(Ordering::SeqCst) {
            break;
        }
        let words = match prompt_words(&line) {
            Ok(words) => words,
            Err(error) => {
                eprintln!("Error: {error:#}");
                continue;
            }
        };
        if words.is_empty() {
            continue;
        }
        match InteractiveArgs::try_parse_from(std::iter::once(String::new()).chain(words)) {
            Ok(args) => {
                let finishing = matches!(args.command, Command::Shutdown);
                match execute(args.command, endpoint) {
                    Ok(()) if finishing => break,
                    Ok(()) => {}
                    Err(error) => eprintln!("Error: {error:#}"),
                }
            }
            Err(error) => {
                error.print()?;
            }
        }
    }
    Ok(())
}

fn execute(command: Command, endpoint: &str) -> Result<()> {
    let op = match command {
        Command::Generate { repo, open } => {
            return crate::vitis::run(
                if open { "generate-open" } else { "generate" },
                repo.as_deref(),
                None,
            );
        }
        Command::Build { repo } => {
            return crate::vitis::run("build", repo.as_deref(), None);
        }
        Command::BuildClean { repo } => {
            return crate::vitis::run("build-clean", repo.as_deref(), None);
        }
        Command::Flash { repo, profile } => {
            return crate::vitis::run("flash", repo.as_deref(), Some(&profile));
        }
        Command::Serve { .. } => {
            bail!("serve cannot be started inside an existing interactive session")
        }
        Command::Profile => {
            println!(
                "{}",
                serde_json::to_string_pretty(&ProfileSettings::load(None)?)?
            );
            return Ok(());
        }
        Command::ChannelMapping => {
            println!(
                "{}",
                serde_json::to_string_pretty(&ChannelMapping::load(None)?)?
            );
            return Ok(());
        }
        Command::StartLogging => Operation::StartLogging,
        Command::StopLogging => Operation::StopLogging,
        Command::StartLoggingSlowData => Operation::StartLoggingSlowData,
        Command::StopLoggingSlowData => Operation::StopLoggingSlowData,
        Command::Connect { ip, port } => Operation::Connect { ip, port },
        Command::Status => Operation::Status,
        Command::Observables => Operation::Observables,
        Command::Stop => Operation::Stop,
        Command::EnableSystem => Operation::EnableSystem,
        Command::EnableControl => Operation::EnableControl,
        Command::ErrorReset => Operation::ErrorReset,
        Command::Shutdown => Operation::Shutdown,
        Command::SetVariable { name, value } => Operation::SetVariable { name, value },
        Command::SetObservable { name, channel } => Operation::SetObservable { name, channel },
        Command::Button { number } => Operation::Button { number },
        Command::SendAck { enabled } => Operation::SendAck {
            enabled: enabled == "on",
        },
    };
    println!(
        "{}",
        serde_json::to_string_pretty(&service::request(endpoint, op)?)?
    );
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn prompt_preserves_quoted_paths_and_windows_separators() {
        assert_eq!(
            prompt_words(r#"build --repo "C:\My Projects\ultrazohm_sw""#).unwrap(),
            vec!["build", "--repo", r"C:\My Projects\ultrazohm_sw"]
        );
        assert_eq!(
            prompt_words("generate --repo '/tmp/repo with spaces'").unwrap(),
            vec!["generate", "--repo", "/tmp/repo with spaces"]
        );
        assert!(prompt_words("build --repo 'unfinished").is_err());
    }

    #[test]
    fn connect_defaults_match_in_shell_and_standalone_cli() {
        let standalone = Args::try_parse_from(["ultrazohm", "connect"]).unwrap();
        let interactive = InteractiveArgs::try_parse_from(["", "connect"]).unwrap();
        for command in [standalone.command.unwrap(), interactive.command] {
            match command {
                Command::Connect { ip, port } => {
                    assert_eq!(ip, "192.168.1.233");
                    assert_eq!(port, 1000);
                }
                _ => panic!("expected connect"),
            }
        }
        assert!(
            Args::try_parse_from(["ultrazohm"])
                .unwrap()
                .command
                .is_none()
        );
    }
}
