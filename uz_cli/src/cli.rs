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
#[command(version, about = "Standalone UltraZohm control and acquisition")]
struct Args {
    #[arg(long,global=true,default_value=service::DEFAULT_ENDPOINT)]
    endpoint: String,
    #[command(subcommand)]
    command: Option<Command>,
}
#[derive(Subcommand)]
enum Command {
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
        let words: Vec<_> = line.split_whitespace().collect();
        if words.is_empty() {
            continue;
        }
        match InteractiveArgs::try_parse_from(std::iter::once("").chain(words)) {
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
