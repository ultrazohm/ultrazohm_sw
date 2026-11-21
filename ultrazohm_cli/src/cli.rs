use crate::{
    data::{Cursor, Query, Selection, Source, Stream},
    live::DataOptions,
    profile::{ChannelMapping, Profile, ProfileSettings},
    service::{self, Config, Operation},
    storage::Format,
};
use anyhow::{Result, bail};
use clap::{CommandFactory, Parser, Subcommand};
use rustyline::{completion::Completer, error::ReadlineError, history::DefaultHistory};
use std::{
    io::{self, BufRead, IsTerminal, Write},
    path::PathBuf,
    sync::{
        Arc,
        atomic::{AtomicBool, Ordering},
    },
};
#[derive(Parser)]
#[command(name = "ultrazohm-cli", version = crate::VERSION, about = "Standalone UltraZohm control and acquisition")]
struct Args {
    #[arg(long,global=true,default_value=service::DEFAULT_ENDPOINT)]
    endpoint: String,
    #[command(subcommand)]
    command: Option<Command>,
}
#[derive(Subcommand)]
enum Command {
    /// Generate/build an empty Vitis workspace (optionally open the GUI).
    Generate {
        #[arg(long)]
        local: bool,
        #[arg(long)]
        no_wait: bool,
        /// Repository root; otherwise search upward from the current directory.
        #[arg(long)]
        repo: Option<PathBuf>,
        #[arg(long)]
        open: bool,
    },
    /// Incrementally build Baremetal and FreeRTOS (including platform dependencies).
    Build {
        #[arg(long)]
        local: bool,
        #[arg(long)]
        no_wait: bool,
        #[arg(long)]
        repo: Option<PathBuf>,
    },
    /// Clean the platform and applications, then rebuild both applications.
    BuildClean {
        #[arg(long)]
        local: bool,
        #[arg(long)]
        no_wait: bool,
        #[arg(long)]
        repo: Option<PathBuf>,
    },
    /// Build, then JTAG program and run. Does not write persistent flash memory.
    Flash {
        #[arg(long)]
        device: Option<String>,
        #[arg(long)]
        no_reconnect: bool,
        #[arg(long)]
        no_wait: bool,
    },
    Jobs,
    Job {
        id: String,
        #[arg(long)]
        follow: bool,
    },
    /// Run the control service until Ctrl-C or shutdown; starts disconnected by default. Run as an OS service for unattended use.
    Serve {
        #[arg(long, hide = true)]
        launch_id: Option<String>,
        /// XSCT launcher on the service machine; otherwise use its PATH.
        #[arg(long)]
        xsct: Option<PathBuf>,
        #[command(flatten)]
        data: DataOptions,
        /// Connect immediately instead of waiting for the connect command.
        #[arg(long)]
        device: Option<String>,
        #[arg(long)]
        profile: Option<PathBuf>,
        /// Firmware names, numeric IDs, wire geometry and repository provenance.
        #[arg(long)]
        channel_mapping: Option<PathBuf>,
        /// Firmware checkout to use instead of the current working directory.
        #[arg(long, conflicts_with = "channel_mapping")]
        repo: Option<PathBuf>,
        /// New session directory (default: repo artifacts/live_logs/<UTC timestamp>).
        /// Logging stays off until start-logging commands.
        #[arg(long)]
        output: Option<PathBuf>,
        /// parquet: final Parquet only; csv: also convert the final Parquet to CSV.
        #[arg(long, value_enum, default_value = "parquet")]
        format: Format,
        #[arg(long,default_value="off",value_parser=["on","off"])]
        ack: String,
        /// Read commands at a prompt while acquisition runs. EOF ends the service.
        #[arg(long)]
        interactive: bool,
    },
    /// Begin fast recording in the session output directory.
    StartLogging,
    /// Stop fast recording and finalize it in the background; check status.
    StopLogging,
    /// Suspend fast recording; acquisition continues. Resume keeps the same file.
    PauseLogging,
    /// Resume a paused fast recording, retaining the acquisition timestamp gap.
    ResumeLogging,
    StartLoggingSlowData,
    StopLoggingSlowData,
    /// Suspend slow recording without finalizing it.
    PauseLoggingSlowData,
    /// Resume the same slow recording.
    ResumeLoggingSlowData,
    /// Connect to a device and apply the configured initial observables.
    Connect {
        #[arg(default_value = service::DEFAULT_DEVICE_IP)]
        ip: String,
        #[arg(default_value_t = service::DEFAULT_DEVICE_PORT)]
        port: u16,
    },
    Status,
    /// Show the firmware mapping and runtime profile loaded by the service.
    Catalog,
    /// List all channel assignments requested in this service session (not device readback).
    Observables,
    /// List recordings created in this acquisition, including older recording numbers.
    Recordings,
    /// Report the available sample range and durable write boundary.
    DataInfo {
        #[arg(long, value_enum, default_value = "fast")]
        stream: Stream,
        #[arg(long)]
        recording: Option<u64>,
    },
    /// Preview the last N available samples from RAM or a recording.
    Tail {
        count: usize,
        #[arg(long, value_enum, default_value = "fast")]
        stream: Stream,
        #[arg(long)]
        recording: Option<u64>,
        #[arg(long, value_delimiter = ',')]
        channels: Option<Vec<String>>,
    },
    /// Preview a sample range [start, stop): acquisition positions for RAM, recorded-row positions with --recording.
    ReadRange {
        start: u64,
        stop: u64,
        #[arg(long, value_enum, default_value = "fast")]
        stream: Stream,
        #[arg(long)]
        recording: Option<u64>,
        #[arg(long, value_delimiter = ',')]
        channels: Option<Vec<String>>,
    },
    /// Read a bounded page; use the returned JSON cursor for the next call.
    ReadSince {
        #[arg(long)]
        cursor: Option<String>,
        #[arg(long, default_value_t = 10000)]
        limit: usize,
        #[arg(long, value_enum, default_value = "fast")]
        stream: Stream,
        #[arg(long)]
        recording: Option<u64>,
        #[arg(long, value_delimiter = ',')]
        channels: Option<Vec<String>>,
    },
    Stop,
    EnableSystem,
    EnableControl,
    /// Explain why Error_Reset is unavailable (its firmware case is empty).
    ErrorReset,
    SetVariable {
        name: String,
        #[arg(allow_hyphen_values = true)]
        value: f32,
    },
    /// Select a named observable into a 1-based channel; does not write the signal.
    SetObservable {
        name: String,
        channel: u32,
    },
    Button {
        number: u32,
    },
    SendAck {
        #[arg(value_parser=["on","off"])]
        enabled: String,
    },
    /// Send device Stop, end acquisition, finalize recordings, and exit the service.
    Shutdown,
    /// Print the built-in runtime profile (initial channels and sampling period).
    Profile {
        /// Filter built-in defaults against this firmware checkout.
        #[arg(long, conflicts_with = "channel_mapping")]
        repo: Option<PathBuf>,
        #[arg(long)]
        channel_mapping: Option<PathBuf>,
    },
    /// Generate a channel-mapping JSON from the repository's JavaScope headers.
    CreateJsonFromJavascopeH {
        /// Repository root; otherwise search upward from the current directory.
        #[arg(long)]
        repo: Option<PathBuf>,
        /// Output JSON (default: <repo>/artifacts/channel_mappings/javascope.json).
        #[arg(long)]
        output: Option<PathBuf>,
    },
    /// Generate and print the firmware channel mapping from the checkout headers.
    ChannelMapping {
        #[arg(long)]
        repo: Option<PathBuf>,
    },
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
    let command = args.command.unwrap_or_else(|| Command::Serve {
        launch_id: None,
        xsct: None,
        data: DataOptions::default(),
        device: None,
        profile: None,
        channel_mapping: None,
        repo: None,
        output: None,
        format: Format::Parquet,
        ack: "off".into(),
        interactive: true,
    });
    match command {
        Command::Serve {
            launch_id,
            xsct,
            data,
            device,
            profile,
            channel_mapping,
            repo,
            output,
            format,
            ack,
            interactive,
        } => {
            let repo = repo
                .as_deref()
                .map(|path| crate::vitis::repository(Some(path)))
                .transpose()?
                .or_else(|| {
                    if channel_mapping.is_none() {
                        crate::vitis::repository(None).ok()
                    } else {
                        None
                    }
                });
            let profile = Profile::load_repository(
                profile.as_deref(),
                channel_mapping.as_deref(),
                repo.as_deref(),
            )?;
            let output = service::session_output_for_repository(output, repo.as_deref())?;
            eprintln!(
                "Session output: {} (logging starts on request)",
                output.display()
            );
            let shutdown = Arc::new(AtomicBool::new(false));
            let signal = shutdown.clone();
            ctrlc::set_handler(move || signal.store(true, Ordering::SeqCst))?;
            let endpoint = args.endpoint.clone();
            let stopped = shutdown.clone();
            service::serve_with_ready(
                Config {
                    launch_id,
                    current_output: None,
                    repo: repo.clone(),
                    xsct,
                    data,
                    device,
                    endpoint: args.endpoint,
                    profile,
                    output: Some(output),
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

struct CommandCompleter {
    names: Vec<String>,
}

impl CommandCompleter {
    fn new() -> Self {
        let mut parser = InteractiveArgs::command();
        parser.build();
        let mut names = Vec::new();
        for command in parser.get_subcommands() {
            if command.get_name() == "serve" || command.is_hide_set() {
                continue;
            }
            names.push(command.get_name().to_owned());
        }
        names.sort();
        names.dedup();
        Self { names }
    }

    fn candidates(&self, line: &str, pos: usize) -> (usize, Vec<String>) {
        let prefix = &line[..pos];
        let word = prefix.trim_start();
        let start = prefix.len() - word.len();
        if word.chars().any(char::is_whitespace) {
            return (pos, Vec::new());
        }
        (
            start,
            self.names
                .iter()
                .filter(|name| name.starts_with(word))
                .cloned()
                .collect(),
        )
    }
}

impl Completer for CommandCompleter {
    type Candidate = String;

    fn complete(
        &self,
        line: &str,
        pos: usize,
        _ctx: &rustyline::Context<'_>,
    ) -> rustyline::Result<(usize, Vec<String>)> {
        Ok(self.candidates(line, pos))
    }
}
impl rustyline::hint::Hinter for CommandCompleter {
    type Hint = String;
}
impl rustyline::highlight::Highlighter for CommandCompleter {}
impl rustyline::validate::Validator for CommandCompleter {}
impl rustyline::Helper for CommandCompleter {}

fn prompt(endpoint: &str, shutdown: &AtomicBool) -> Result<()> {
    eprintln!(
        "Type help for commands; Tab completes command names. shutdown, Ctrl-C or EOF sends device Stop, ends acquisition and finalizes logs."
    );
    let stdin = io::stdin();
    // Keep redirected input unchanged for scripts and automated sessions.
    let mut editor = if stdin.is_terminal() && io::stdout().is_terminal() {
        let config = rustyline::Config::builder()
            .completion_type(rustyline::CompletionType::List)
            .build();
        let mut editor =
            rustyline::Editor::<CommandCompleter, DefaultHistory>::with_config(config)?;
        editor.set_helper(Some(CommandCompleter::new()));
        Some(editor)
    } else {
        None
    };
    let mut input = stdin.lock();
    while !shutdown.load(Ordering::SeqCst) {
        let line = if let Some(editor) = &mut editor {
            match editor.readline("ultrazohm-cli> ") {
                Ok(line) => {
                    editor.add_history_entry(line.as_str())?;
                    line
                }
                Err(ReadlineError::Interrupted | ReadlineError::Eof) => break,
                Err(error) => return Err(error.into()),
            }
        } else {
            print!("ultrazohm-cli> ");
            io::stdout().flush()?;
            let mut line = String::new();
            if input.read_line(&mut line)? == 0 {
                break;
            }
            line
        };
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

/// A parsed command is either a request to the service or a local tool run.
enum Action {
    Service(Operation),
    Local(Command),
}

fn classify(command: Command) -> Result<Action> {
    if let Some((op, _)) = firmware_command(&command)? {
        return Ok(Action::Service(op));
    }
    let op = match command {
        Command::Jobs => Operation::Jobs,
        Command::Job { id, .. } => Operation::Job { id, offset: 0 },
        Command::Recordings => Operation::Recordings,
        Command::DataInfo { stream, recording } => Operation::DataInfo {
            source: Source { stream, recording },
        },
        Command::Tail {
            count,
            stream,
            recording,
            channels,
        } => Operation::ReadData {
            query: Query {
                source: Source { stream, recording },
                selection: Selection::Tail { count },
                channels,
            },
        },
        Command::ReadRange {
            start,
            stop,
            stream,
            recording,
            channels,
        } => Operation::ReadData {
            query: Query {
                source: Source { stream, recording },
                selection: Selection::Range { start, stop },
                channels,
            },
        },
        Command::ReadSince {
            cursor,
            limit,
            stream,
            recording,
            channels,
        } => {
            let cursor: Option<Cursor> = cursor.map(|s| serde_json::from_str(&s)).transpose()?;
            let source = cursor
                .as_ref()
                .map(|c| Source {
                    stream: c.stream.clone(),
                    recording: c.recording,
                })
                .unwrap_or(Source { stream, recording });
            Operation::ReadData {
                query: Query {
                    source,
                    selection: Selection::Since { cursor, limit },
                    channels,
                },
            }
        }
        local @ (Command::Generate { .. }
        | Command::Build { .. }
        | Command::BuildClean { .. }
        | Command::Flash { .. }
        | Command::Serve { .. }
        | Command::Profile { .. }
        | Command::CreateJsonFromJavascopeH { .. }
        | Command::ChannelMapping { .. }) => return Ok(Action::Local(local)),
        Command::StartLogging => Operation::StartLogging {
            stream: Stream::Fast,
        },
        Command::StopLogging => Operation::StopLogging {
            stream: Stream::Fast,
        },
        Command::PauseLogging => Operation::PauseLogging {
            stream: Stream::Fast,
        },
        Command::ResumeLogging => Operation::ResumeLogging {
            stream: Stream::Fast,
        },
        Command::StartLoggingSlowData => Operation::StartLogging {
            stream: Stream::Slow,
        },
        Command::StopLoggingSlowData => Operation::StopLogging {
            stream: Stream::Slow,
        },
        Command::PauseLoggingSlowData => Operation::PauseLogging {
            stream: Stream::Slow,
        },
        Command::ResumeLoggingSlowData => Operation::ResumeLogging {
            stream: Stream::Slow,
        },
        Command::Connect { ip, port } => Operation::Connect { ip, port },
        Command::Status => Operation::Status,
        Command::Observables => Operation::Observables,
        Command::Catalog => Operation::Catalog,
        Command::Stop => Operation::Stop,
        Command::EnableSystem => Operation::EnableSystem,
        Command::EnableControl => Operation::EnableControl,
        Command::ErrorReset => {
            bail!("Error_Reset is a no-op in this firmware; use stop to leave error state")
        }
        Command::Shutdown => Operation::Shutdown,
        Command::SetVariable { name, value } => Operation::SetVariable { name, value },
        Command::SetObservable { name, channel } => Operation::SetObservable { name, channel },
        Command::Button { number } => Operation::Button { number },
        Command::SendAck { enabled } => Operation::SendAck {
            enabled: enabled == "on",
        },
    };
    Ok(Action::Service(op))
}

/// Run a command that does not talk to the service.
fn run_local(command: Command) -> Result<()> {
    match command {
        Command::Generate { repo, open, .. } => crate::vitis::run(
            if open { "generate-open" } else { "generate" },
            repo.as_deref(),
            None,
        ),
        Command::Build { repo, .. } => crate::vitis::run("build", repo.as_deref(), None),
        Command::BuildClean { repo, .. } => crate::vitis::run("build-clean", repo.as_deref(), None),
        Command::Serve { .. } => {
            bail!("serve cannot be started inside an existing interactive session")
        }
        Command::Profile {
            repo,
            channel_mapping,
        } => {
            println!(
                "{}",
                serde_json::to_string_pretty(&if repo.is_some() || channel_mapping.is_some() {
                    let mapping = ChannelMapping::load_repository(
                        channel_mapping.as_deref(),
                        repo.as_deref(),
                    )?;
                    let settings = ProfileSettings::for_mapping(None, &mapping)?;
                    Profile::from_mapping(settings.clone(), mapping)?;
                    settings
                } else {
                    ProfileSettings::load(None)?
                })?
            );
            Ok(())
        }
        Command::CreateJsonFromJavascopeH { repo, output } => {
            let path = crate::header_mapping::run(repo.as_deref(), output.as_deref())?;
            println!("Created channel mapping: {}", path.display());
            Ok(())
        }
        Command::ChannelMapping { repo } => {
            println!(
                "{}",
                serde_json::to_string_pretty(&ChannelMapping::load_repository(
                    None,
                    repo.as_deref()
                )?)?
            );
            Ok(())
        }
        _ => unreachable!("classify returns only local commands as Local"),
    }
}

/// Send one operation and write its reply: JSON, or a short table for data reads.
fn send_operation(op: Operation, endpoint: &str, out: &mut impl Write) -> Result<()> {
    if matches!(op, Operation::ReadData { .. }) {
        use polars::prelude::*;
        let (header, bytes) = service::exchange(endpoint, op, true)?;
        writeln!(out, "{}", serde_json::to_string(&header)?)?;
        let df = IpcStreamReader::new(std::io::Cursor::new(bytes)).finish()?;
        writeln!(
            out,
            "{} rows × {} columns (showing first {})",
            df.height(),
            df.width(),
            df.height().min(20)
        )?;
        writeln!(
            out,
            "{}",
            df.get_column_names()
                .iter()
                .map(|s| s.as_str())
                .collect::<Vec<_>>()
                .join("\t")
        )?;
        for row in 0..df.height().min(20) {
            writeln!(
                out,
                "{}",
                df.get_columns()
                    .iter()
                    .map(|c| c.get(row).map(|v| v.to_string()))
                    .collect::<std::result::Result<Vec<_>, _>>()?
                    .join("\t")
            )?;
        }
        return Ok(());
    }
    writeln!(
        out,
        "{}",
        serde_json::to_string_pretty(&service::request(endpoint, op)?)?
    )?;
    Ok(())
}

fn follow_job(endpoint: &str, id: &str, follow: bool) -> Result<()> {
    let mut offset = 0;
    loop {
        let reply = service::request(
            endpoint,
            Operation::Job {
                id: id.into(),
                offset,
            },
        )?;
        print!("{}", reply["log"].as_str().unwrap_or(""));
        io::stdout().flush()?;
        let progress = crate::jobs::progress(offset as u64, &reply)?;
        let next = progress["next_offset"].as_u64().unwrap() as usize;
        if !follow {
            println!("{}", serde_json::to_string_pretty(&reply["job"])?);
            return Ok(());
        }
        if progress["complete"] == true {
            anyhow::ensure!(
                reply["job"]["state"] == "succeeded",
                "firmware job failed: {}",
                reply["job"]["result"]
            );
            return Ok(());
        }
        offset = next;
        std::thread::sleep(std::time::Duration::from_millis(100));
    }
}

fn firmware_command(command: &Command) -> Result<Option<(Operation, bool)>> {
    let firmware = match command {
        Command::Generate {
            local: false,
            repo,
            open,
            no_wait,
        } => {
            anyhow::ensure!(
                repo.is_none() && !open,
                "select --repo at serve startup; --open requires --local"
            );
            Some(("generate", *no_wait, None, false))
        }
        Command::Build {
            local: false,
            repo,
            no_wait,
        }
        | Command::BuildClean {
            local: false,
            repo,
            no_wait,
        } => {
            anyhow::ensure!(
                repo.is_none(),
                "select --repo at serve startup, or use --local"
            );
            Some((
                if matches!(command, Command::Build { .. }) {
                    "build"
                } else {
                    "build-clean"
                },
                *no_wait,
                None,
                false,
            ))
        }
        Command::Flash {
            device,
            no_wait,
            no_reconnect,
        } => Some(("flash", *no_wait, device.clone(), *no_reconnect)),
        _ => None,
    };
    if let Some((action, no_wait, device, no_reconnect)) = firmware {
        let request_id = format!(
            "{}-{}",
            std::process::id(),
            std::time::SystemTime::now()
                .duration_since(std::time::UNIX_EPOCH)?
                .as_nanos()
        );
        return Ok(Some((
            Operation::Firmware {
                action: action.into(),
                request_id,
                device,
                no_reconnect,
            },
            no_wait,
        )));
    }
    Ok(None)
}

fn execute(command: Command, endpoint: &str) -> Result<()> {
    if let Command::Job { id, follow } = &command {
        return follow_job(endpoint, id, *follow);
    }
    if let Some((operation, no_wait)) = firmware_command(&command)? {
        let reply = service::request(endpoint, operation)?;
        let id = reply["job"]["id"].as_str().unwrap();
        println!("Job {id}");
        return if no_wait {
            Ok(())
        } else {
            follow_job(endpoint, id, true)
        };
    }

    match classify(command)? {
        Action::Service(op) => send_operation(op, endpoint, &mut io::stdout().lock()),
        Action::Local(command) => run_local(command),
    }
}

/// Run one line of the interactive prompt's syntax against the service at
/// `endpoint` and return what it prints. Only service commands are accepted:
/// firmware submissions return job metadata; local tools require a terminal.
/// Help output is returned as text; parse errors and failed requests are errors.
pub fn console_command(endpoint: &str, line: &str) -> Result<String> {
    let mut words = prompt_words(line)?;
    if words.is_empty() {
        words.push("help".into());
    }
    let command = match InteractiveArgs::try_parse_from(std::iter::once(String::new()).chain(words))
    {
        Ok(args) => args.command,
        Err(error) if error.use_stderr() => bail!("{}", error.render().to_string().trim_end()),
        Err(help) => return Ok(help.render().to_string()),
    };
    match classify(command)? {
        Action::Service(op) => {
            let mut out = Vec::new();
            send_operation(op, endpoint, &mut out)?;
            Ok(String::from_utf8_lossy(&out).into_owned())
        }
        Action::Local(_) => bail!(
            "this command runs local tools, not the service; run it in a terminal \
             with explicit local execution"
        ),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn completion_matches_commands_only_in_first_word() {
        let helper = CommandCompleter::new();
        assert_eq!(helper.candidates("shut", 4), (0, vec!["shutdown".into()]));
        assert_eq!(helper.candidates("  shut", 6), (2, vec!["shutdown".into()]));
        assert_eq!(
            helper.candidates("build", 5).1,
            vec!["build", "build-clean"]
        );
        assert!(
            helper
                .candidates("start-", 6)
                .1
                .contains(&"start-logging".into())
        );
        assert!(helper.candidates("", 0).1.contains(&"help".into()));
        assert_eq!(
            helper.candidates("create-json", 11).1,
            vec!["create-json-from-javascope-h"]
        );
        assert!(!helper.candidates("", 0).1.contains(&"serve".into()));
        assert!(helper.candidates("connect ", 8).1.is_empty());
        assert!(helper.candidates("unknown", 7).1.is_empty());
    }

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
        let standalone = Args::try_parse_from(["ultrazohm_cli", "connect"]).unwrap();
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
            Args::try_parse_from(["ultrazohm_cli"])
                .unwrap()
                .command
                .is_none()
        );
    }
}
