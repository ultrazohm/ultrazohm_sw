# ultrazohm-cli and Python API

Rust acquisition, control and CSV/Parquet logging for JavaScope firmware on Linux and Windows.
The ultrazohm-cli command, ultrazohm_cli Python API and native [DataViewer](../ultrazohm_dataviewer/README.md) use the Rust acquisition backend provided by ultrazohm-cli.
The standalone ultrazohm-cli executable needs no Python or GUI.

This guide covers setup and usage.
See the [wire/API specification](docs/protocol.md) for firmware contracts and the [architecture](docs/architecture.md) for ownership, concurrency, storage guarantees and deferred work.

## Install

See the [application installation guide](../README.MD#ultrazohm-cli-and-dataviewer) for Python/uv, Windows standalone downloads, and repository environments.

```sh
uvx ultrazohm-cli
# For Python scripts in your virtual environment:
pip install ultrazohm-cli
# For local development of both applications:
./uz_developer build
./uz_developer shell
```

Python imports use `ultrazohm_cli`; `python -m ultrazohm_cli` runs the ultrazohm-cli.

## Build

Source builds require Rust 1.90.0 and a native C/C++ toolchain (Linux: `build-essential`; Windows: Visual Studio Build Tools with C++ development).
The devcontainer supplies Rust, Maturin and uv.
Its post-create script installs both applications and example dependencies into the container development environment, independently of the host `.venv`.
Run the application commands directly inside the container.
Both `ultrazohm-cli` and `ultrazohm-dataviewer` are available in new container terminals.
Run `./uz_developer build` to refresh both applications.
Container-built wheels require a compatible Linux host; Windows needs its own wheel.

Builds and checks run through `tasks.py`, which uses only the Python standard library and behaves the same on Linux, Windows and in CI.
From the repository root:

| Task | Output |
|---|---|
| `./uz_developer build` | Portable CLI and DataViewer wheels, installed into the development environment |
| `./uz_developer cli debug-wheel` | Unoptimized wheel for tests in `target/wheels-debug` |
| `./uz_developer cli release-wheel` | Portable release wheel in `target/wheels-release` |

On Windows, use `.\uz_developer.ps1` with the same arguments.
Maturin and Zig run together through `uv tool run`, independently of the launcher's Python environment.
The standalone executable is `cargo build --release --locked --bin ultrazohm-cli`.

`cargo install --path . --locked` installs the standalone ultrazohm-cli.
For application development, use `./uz_developer build` and `./uz_developer shell`.
Rebuild/reinstall after Rust changes.
Native Linux ARM64 builds are possible; these are Linux applications, not executables for the R5 baremetal environment.

## Run

Run `ultrazohm-cli` from the firmware checkout to open a disconnected interactive session.
Use `ultrazohm-cli serve --interactive --repo PATH` to select a checkout explicitly.
At its prompt, enter commands without the executable prefix:

```text
connect
status
set-variable send_field_1 -12.5
set-observable lifecheck 1
start-logging
start-logging-slow-data
tail 500
stop
stop-logging
stop-logging-slow-data
shutdown
```

Use `help` or `help set-variable`.
With no arguments, `connect` uses `192.168.1.233:1000`.
Tab completes command names; Up/Down recalls commands from this session.
Piped input works too.
Arguments are space-separated; quote paths containing spaces.
Backslashes are literal and there is no shell expansion.
Invalid commands report errors and leave the prompt running.

For an unattended ultrazohm-cli process, or an interactive ultrazohm-cli process with explicit settings:

```sh
ultrazohm-cli serve --device 192.168.1.233:1000 --output measurement-001 --format csv
ultrazohm-cli serve --interactive --channel-mapping my-mapping.json
```

`serve` without `--device` waits for `connect [IP] [PORT]`.
A failed connect can be retried; a second connect while connected is rejected.
Transport failure ends the acquisition session and finalizes logs; the ultrazohm-cli process remains available to report the failure and accept a new connection.
External ultrazohm-cli/Python clients can control the ultrazohm-cli process while its interactive prompt waits for input.

All entry points reserve a new output directory but start with logging off.
Without `--output`, ultrazohm-cli/Python sessions use `<repo>/artifacts/live_logs/<UTC timestamp>`, searching upward from the current directory; outside a checkout the current directory is the base.
Explicit output directories must not exist and their parent must exist.
Every entry point (bare `ultrazohm-cli`, `serve`, Python `Acquisition()` and the DataViewer) writes Parquet only by default; `--format csv` (`format="csv"` in Python) adds CSV exports.

The DataViewer keeps its preferences and log paths in `artifacts/_user` of the selected checkout.
See [DataViewer usage](../ultrazohm_dataviewer/README.md) for settings and worker launch.

### Control and recording lifecycle

- `enable-system`, `enable-control`, `button 1..8`, `set-variable` and `stop` send firmware commands.
  `stop` leaves acquisition running.
- Fast and slow start/stop logging are independent and do not change device state.
  Stop detaches a stream at a complete frame boundary; queued frames drain in the background.
  Wait for `status.logging.<stream>.phase` to become `complete` before reading final exports or starting another recording of that stream.
- `pause-logging` / `resume-logging` retain the same fast recording; slow equivalents add `-slow-data`.
  Paused intervals are omitted, with gaps retained in timestamps.
  Observable changes are blocked while either stream is recording or paused.
  Device controls and the live RAM buffer continue during pauses.
- `shutdown`, Ctrl-C, interactive EOF and `Acquisition.close()` send device Stop before waiting for queries and recording finalization.
  Shutdown's reply confirms acceptance; process exit and the `end` section of `run.json` report completion.
  EOF is Ctrl-D on Linux or Ctrl-Z then Enter on Windows.
  Unattended `serve` ignores stdin.

Logging phases are `idle`, `recording`, `paused`, `finalizing`, `complete` and `failed`.
Invalid transitions return errors.
Disk/export errors are reported, not silently ignored.
Finalization can take time and additional disk space.
Use an OS process supervisor when acquisition must outlive a terminal or Python.

Local control defaults to numeric loopback `127.0.0.1:19740`; pass `--endpoint` on both ultrazohm-cli process and clients for another port.
This is a trusted-user local API.
Wire commands are `sent_unconfirmed`: firmware has no command acknowledgments.
`error-reset` reports an error because its firmware case is empty.

ACKs default off for current FreeRTOS.
`--ack on` or `send-ack on/off` controls legacy pacing.
`status.state.platform_state` reports the latest received mapped platform state, independently of sent commands.
It is null before reception, after disconnection, and for legacy headers lacking `javascope_status.h`.
Legacy firmware control/logging remains supported; see the [protocol limitations](docs/protocol.md).

## Runtime profile and firmware channel mapping

| Configuration | Contents |
|---|---|
| Embedded `profiles/standard.json`, or `--profile PATH` | Schema version, name, nominal sample period, initial channels |
| Header-generated mapping, or `--channel-mapping PATH` | Firmware IDs, packet geometry, platform-state decoding and source provenance |

There is no embedded firmware mapping.
Select the firmware checkout explicitly:

```sh
ultrazohm-cli serve --interactive --repo /path/to/firmware/ultrazohm_sw
```

This reads that checkout's current headers, keeps only built-in default channel assignments available in the mapping, and puts default session output under that checkout's `artifacts/live_logs`.
It does not require generating a JSON file first.
`catalog` reports the effective configuration.
Runtime settings use explicit `--profile`, then `<repo>/artifacts/_user/settings.json`, then built-in defaults.
Saved DataViewer startup settings therefore also affect ultrazohm-cli sessions.
Only built-in defaults are filtered; invalid saved assignments fail validation.
Inspect `catalog` and correct the saved profile or supply an explicit profile.
The built-in nominal sample period is 100 microseconds; it is not inferred from headers.

Without `--repo` or `--channel-mapping`, headers are discovered from the current directory.
`--repo` and `--channel-mapping` are mutually exclusive.
A custom `--profile` works with either and is validated strictly: unknown assignments are errors, never silently dropped.
To inspect or customize repository defaults:

```sh
ultrazohm-cli profile --repo /path/to/firmware/ultrazohm_sw > my-profile.json
ultrazohm-cli channel-mapping --repo /path/to/firmware/ultrazohm_sw
```

Explicit mapping files remain supported:

```sh
ultrazohm-cli profile > my-profile.json
ultrazohm-cli channel-mapping > my-mapping.json
ultrazohm-cli serve --interactive --profile my-profile.json --channel-mapping my-mapping.json
```

A runtime profile can select only the observables needed for a measurement:

```json
{
  "schema_version": 1,
  "name": "my-measurement",
  "sample_period_us": 100,
  "initial_channels": {"1": "JSO_lifecheck", "2": "JSO_ISR_ExecTime_us"}
}
```

The bundled standard profile proposes 20 named observables; unavailable defaults are skipped with a diagnostic.
Explicit profiles must reference valid observables.
The DataViewer gets matching defaults from the ultrazohm-cli and seeds missing workspace settings; existing preferences are passed unchanged to ultrazohm-cli process validation.
Set `initial_channels` to `{}` or omit it in a custom profile to leave all slots untouched.
Initial selections are sent before the ultrazohm-cli process becomes ready; they do not enable the system or start logging.

Mapping provenance describes source headers, not verified running firmware.
The IDs, geometry and configured sample period must match the deployed firmware.
Changing the ultrazohm-cli process checkout requires a restart.
Flashing reloads firmware configuration into a new acquisition session without restarting the ultrazohm-cli process.
`observables` lists requested slot assignments and `catalog` returns loaded configuration; neither claims device readback.
Unknown slots are omitted from logs; duplicate observable IDs use the first selected slot.
Names are frozen at recording start.

### Generate a mapping from the checkout

```sh
ultrazohm-cli create-json-from-javascope-h
ultrazohm-cli create-json-from-javascope-h --repo /path/to/ultrazohm_sw --output my-mapping.json
```

The default destination is `<repo>/artifacts/channel_mappings/javascope.json`; re-running replaces it only after parsing and validation.
The command reads JavaScope enums and visualization sections (field names, units, button captions, receive-field assignments), status definitions, channel count and packet size from the checkout's headers.
No Vitis, C compiler or Python parser is needed.
Git is optional; provenance is `unknown` without it and marks modified headers with `-dirty`.
This parser is not a C preprocessor: unsupported expressions, duplicate names and unsupported geometry fail explicitly.
See the [header contract](docs/protocol.md#generating-a-mapping-from-firmware-headers).
Generating a file does not reconfigure a running ultrazohm-cli process.
The optional `javascope` JSON object also records slow-signal float/integer types.
This metadata is included in the ultrazohm-cli process profile/catalog.
The DataViewer uses its button captions in the Control pane, falling back to `User N` when a caption is absent.
Existing mappings without this metadata remain supported.

## Python

`Client` controls an existing ultrazohm-cli process.
`Acquisition` owns an embedded instance of the same Rust acquisition backend provided by ultrazohm-cli and waits until startup is ready.
Socket calls release the GIL; Python does not process incoming samples.
Use an embedded acquisition as a context manager; leaving the block, also through an exception, sends device Stop, finalizes recordings and raises runtime/storage errors:

```python
import time
from ultrazohm_cli import Acquisition, Client

with Acquisition(output="python-run", format="csv") as acquisition:
    uz = Client()
    uz.connect()  # or pass device="192.168.1.233:1000" to Acquisition
    uz.set_observable("lifecheck", 1)
    uz.set_variable("send_field_1", 12.5)
    uz.start_logging()
    time.sleep(1)  # Perform the measurement here.
    print(uz.status())

recorded = acquisition.read_recording()  # First fast recording, as Polars.
```

`acquisition.close()` does the same explicitly.
An acquisition that is never closed is closed when it is garbage collected or the interpreter exits, which also sends device Stop; errors are then only printed to standard error.

`Acquisition` also accepts `profile`, `channel_mapping`, `endpoint`, `buffer_samples`, `segment_rows`, `flush_interval_ms` and `recording_backend`.
`output` exposes the resolved session directory.
`Client` has matching named control/logging methods, including pause/resume for both streams.
Embedded acquisition ends with its Python process; an external ultrazohm-cli process can survive it.
Local Vitis tools currently use the ultrazohm-cli, not module-level Python functions.

## Unified RAM and recording access

```python
from ultrazohm_cli import Client, Recording

uz = Client()
recent = uz.tail(500)  # After at least 500 samples; logging need not be enabled.
info = uz.data_info(recording=1)
if info["start"] is not None:
    df = uz.read_range(info["start"], info["stop"], recording=1)
page = uz.read_since(recording=1, limit=10000)
next_page = uz.read_since(page.cursor, limit=10000)

# Reopen committed data without a running service:
handle = Recording("python-run/data.recording.json")
for batch in handle.iter_batches(10000, channels=["JSO_lifecheck"]):
    print(batch.shape)
```

`recording=None` selects the bounded live ring; positive recording numbers select that recording's history, including pending samples.
Ranges are half-open `[start, stop)`, cursors must be reused unchanged, and each page is a Polars frame transported as Arrow IPC.
Durable `Recording` handles read only indexed, committed data.
See the [protocol](docs/protocol.md) for positions, cursors, column selection and limits.

ultrazohm-cli equivalents print metadata and at most 20 preview rows:

```sh
ultrazohm-cli data-info --recording 1
ultrazohm-cli recordings
ultrazohm-cli tail 500
ultrazohm-cli read-range 1000 2000 --recording 1 --channels JSO_lifecheck
ultrazohm-cli read-since --recording 1 --limit 10000
```

Supply `--cursor '<previous cursor JSON>'` to continue.

## Recording outputs

Only explicitly started streams produce measurement files.
While a recording runs, it writes immutable Parquet parts (`data-part-00000000.parquet`, ...)
and a `*.recording.json` index, so committed data survives a crash and can be read during acquisition.
When the recording stops, the parts are merged; the index is pointed at the merged file and the parts are deleted.
Finished recordings therefore contain each sample once.
For a finished session with one fast and one slow recording:

```text
measurement-001/
    run.json                          # Configuration; "end" section written at service exit
    commands.jsonl                    # Host command audit
    data.recording.json               # Fast index; "metadata": assignments, rows, completion
    data.parquet                      # Fast recording (canonical and export)
    data.csv                          # Additional export for --format csv
    data_slow_data.recording.json     # Slow index and metadata
    data_slow_data.updates.parquet    # Slow raw update history (canonical)
    data_slow_data.parquet            # Slow wide forward-filled export
```

`run.json` without an `end` section means the ultrazohm-cli process did not exit normally.
If merging fails, the parts and their index remain the canonical recording.

Subsequent recordings use `data_0002...`, with independent counters for each stream.
Existing files are not overwritten.
Empty started recordings produce typed empty outputs.
`.partial` files are not published measurements.

Fast columns are `time` (Float64 nominal seconds), `status` (UInt32 packet status) and selected observable names (Float32).
Time starts with acquisition, not logging.
NaN/Inf are preserved.
The status word describes the packet's last sample and is repeated across its rows; it is not a precise transition timestamp.

Canonical slow history contains `observable`, `slow_id`, `slow_raw`, `slow_value`, `time` and `status`.
Final slow exports are wide, forward-filled tables, marked `wide_forward_filled` in metadata.
They emit rows only after all observables have values, carry values across segments, and reset filling after pauses.
A never-seen observable makes the wide export empty.
Held values are not newly sampled values; raw update history remains available.
Fast and slow row counts may differ.

### Buffering and failure behavior

Defaults retain 30 seconds in RAM, flush at 1,000,000 rows or 60,000 ms, and give each logger an independent queue of 3 seconds of acquisition (never fewer than 2,048 frames) to absorb slow disk writes.
Configure them with:

```sh
ultrazohm-cli serve --buffer-samples 100000 --segment-rows 50000 --flush-interval-ms 1000 --queue-seconds 10
```

Settings are fixed for an acquisition session and reported in `status.data_options`.
If the disk cannot keep up and a logger queue overflows, only that recording ends as `failed`; acquisition, device control and the other stream continue.
Committed chunks stay readable after disk or export failures.
See [architecture](docs/architecture.md) for the storage invariants and failure behavior.

## Development

From the repository root, on Linux (dev container) or Windows (`.\uz_developer.ps1`):

```sh
./uz_developer cli check           # Ruff, fmt, clippy, Rust tests, integration tests against a debug wheel
./uz_developer cli release-wheel   # portable release wheel in target/wheels-release
./uz_developer cli release-check   # integration tests against that installed wheel
```

Set `UZ_CLI_BIN` to test another executable.
Tests use loopback simulators, including `--legacy-ack`, and fake Vitis tooling; they do not program hardware.
Manual simulation: `python javascope/test_server.py --host 127.0.0.1 --port 1000`.
See the [build guide](../docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_build.rst) for linting, the CI pipeline and releases.

## Hardware acceptance (pending)

Simulator and fake-XSCT checks do not establish physical-device readiness.
Before a hardware release, record the firmware revision, board, host OS and Vitis version, then verify:

- Discover mappings from the selected checkout, connect, and compare observable names and assignments with firmware.
- Exercise system enable, control enable, device Stop and independent fast/slow recording.
  Confirm Stop leaves acquisition connected and shutdown finalizes recordings.
- Record through a disconnect and inspect completion flags, CSV/Parquet output and partial-file cleanup.
- Flash through XSCT/JTAG, reconnect, and verify preserved assignments and idle logging.

These checks require a device and Vitis installation and remain pending; CI does not claim to perform them.

After flash, reconnection retries for up to 20 seconds.
A failed reconnect does not invalidate completed recordings or prevent another flash.
Replacement sessions receive a fresh directory under the same output parent.

Python `Acquisition.output` and its recording helpers follow the latest session, including after close.
Save a durable `Recording` handle before flashing to retain access to an earlier session; recording numbers restart in each session.

Shutdown during programming waits for completion, then retries device Stop delivery for a bounded 20-second boot window when the firmware mapping is known.
Failed programming or uncertain mapping is reported as an error without guessing command IDs.
If delivery fails, the firmware job log and stderr contain the failure and the ultrazohm-cli process exits nonzero.
The DataViewer submits Stop and shutdown independently of flash progress without blocking its UI.
A successful retry clears that operation's displayed failure for the same ultrazohm-cli process, while the Console retains the diagnostic history.

## Configuration and owned ultrazohm-cli processes from Python

Offline helpers use the same Rust validation and remapping as the ultrazohm-cli process:

```python
from ultrazohm_cli.configuration import channel_mapping, default_profile, remap_profile

mapping = channel_mapping("/path/to/ultrazohm_sw")
profile = default_profile("/path/to/ultrazohm_sw")
profile, removed = remap_profile(mapping, profile, {"1": "lifecheck"})
```

`validate_profile` validates runtime preferences; `read_profile` loads them from JSON.
Remapping returns removed names explicitly.
Applications deciding to save a startup profile should reject unwanted removals rather than silently changing user choices.

`ultrazohm_cli.process.ServiceProcess` owns an external ultrazohm-cli process.
`start` accepts its endpoint, output directory, firmware repository or mapping, optional profile and recording options.
`shutdown` checks ultrazohm-cli process identity before requesting shutdown; `wait` waits for finalization and can yield to a caller's cancellation event.
The caller decides when to stop or shut down a device.
Creating a helper or attaching an ordinary `Client` does not transfer ownership of an existing ultrazohm-cli process.

ultrazohm-cli native executables and Python wheels embed the firmware Tcl scripts and launch templates.
DataViewer uses these ultrazohm-cli-owned resources in both source and frozen mode.
See [which Tcl scripts run](#which-tcl-scripts-run) for development rebuilds, the explicit runtime override, and the separate Vitis IDE Run/Debug path.

`status.state.user_buttons` contains eight decoded booleans in button order 1–8.
Clients should use them instead of interpreting JavaScope wire-status bit positions.

### Shared startup preferences and job monitoring

ultrazohm-cli process startup selects an explicit `--profile`, then the selected checkout's `artifacts/_user/settings.json`, then built-in defaults.
Existing profiles are validated strictly, never silently rewritten.
Python `load_or_seed_profile(path, mapping)` seeds missing defaults atomically; `save_profile(path, profile, mapping)` validates against firmware before replacing the file.
DataViewer uses these same helpers; view preferences remain independent.

XSCT selection uses an explicit launcher, then the workspace's saved `tools.json` selection, then PATH.
A missing or invalid saved launcher reports an error rather than silently selecting another installation.
Python `save_xsct`, `saved_xsct`, and `resolve_xsct` in `ultrazohm_cli.configuration` share the native ultrazohm-cli's logic.
Saving or inspecting a launcher does not change the caller's PATH.
A running ultrazohm-cli process's explicit `--xsct` continues to take precedence over saved preferences.

`ultrazohm_cli.jobs.FirmwareJob(client, job_id, offset=0)` tracks log offsets.
Call `poll()` at the application's chosen interval and display the returned log and job metadata.
`complete` becomes true after final logs have drained; `raise_for_status()` then reports job failure.
Stopping polling never cancels the ultrazohm-cli process job.
Another client can resume with its ID and last offset.

A `ServiceProcess` launch uses a unique identifier to verify the child answering its endpoint.
Automatic cleanup sends that identity with the shutdown request; the ultrazohm-cli process rejects a mismatch before any shutdown side effects.
Explicit user shutdown remains available for attached ultrazohm-cli processes.
`wait(timeout=...)` bounds finalization waiting without killing an ultrazohm-cli process still writing recordings.

Firmware mappings must contain the mandatory `Stop` command.
Validation rejects an incomplete lifecycle contract before opening a device connection.

The Bash and PowerShell user/developer entry points share platform bootstrap helpers.
`.uv-version` pins uv when installation is needed; `.python-version` selects Python.
Application arguments can use the default stable channel directly: `./uz cli status` or `./uz cli -- status`.
Use `./uz cli stable -- --help` for application help; `./uz cli --help` describes the launcher.

Build tasks share environment paths, wheel inspection, subprocess execution, and release staging through `uz_build.py`.
Staging never rewrites the checkout.
See `.devcontainer/build-tools.txt` for exact build-tool pins.

Linux firmware display requirements
----------------------------------

Batch firmware operations require xlsclients and, without a usable display, Xvfb on the machine running XSCT.
On Debian/Ubuntu install x11-utils and xvfb; dbus-x11 provides the optional dbus-launch helper.
Acquisition alone does not need these tools.
Native Windows needs no X11 packages or Linux launcher flags.
An attached laptop needs none of these firmware-host dependencies.

Use xsct -norlwrap for direct Linux batch execution.
For Linux open and generate-open, use xsct -norlwrap -nodisp with an existing desktop display.
The ultrazohm-cli and Make targets select these flags automatically.
A temporary batch display cannot host a persistent Vitis GUI.

Start the ultrazohm-cli process normally over SSH after installing the dependencies; no xvfb-run wrapper is necessary.
Rebuild the checkout ultrazohm-cli and restart its ultrazohm-cli process to pick up launcher changes.
Failed generation can leave a partial workspace: preserve it before retrying in an empty workspace.
Inspect the job output and timestamp-matching vitis/workspace/IDE.log; Channel closed alone does not identify its cause.
