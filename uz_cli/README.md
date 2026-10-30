# UltraZohm CLI and Python API

Rust acquisition, control and CSV/Parquet logging for JavaScope firmware on
Linux and Windows. The CLI, Python API and native [Data Viewer](../uz_dataviewer/README.md)
use the same Rust service. The standalone CLI executable needs no Python or GUI.

This guide covers setup and usage. See the [wire/API specification](docs/protocol.md)
for firmware contracts and the [architecture](docs/architecture.md) for ownership,
concurrency, storage guarantees and deferred work.

## One-command setup and launch

With uv installed, run from the repository root:

```sh
./uz_cli/run.sh
```

On Windows PowerShell:

```powershell
.\uz_cli\run.ps1
```

Both launchers provision the Python series from `.devcontainer/Dockerfile`, create
`uz_cli/.venv-host` (or `.venv-container` in Docker), install a compatible binary
wheel plus example dependencies, and start the interactive CLI. No Rust compiler
is needed. Run the scripts; do not source them. Virtual environments belong to
the machine/container that created them.

If local wheels exist in `uz_cli/target/wheels`, choose the newest local build or
a GitHub release. Downloads verify SHA-256 checksums and are cached there.
The release channel defaults to `testing` on `feature/uz_cli26`, otherwise `stable`.
An explicit channel controls downloads; local builds can come from either channel.
Downloaded wheels contain released code, not unbuilt local Rust changes.

| Option | Purpose |
|---|---|
| `--latest --channel stable` or `testing` | Download the newest release in that channel |
| `--local-newest` | Use the newest compatible local wheel by modification time |
| `--wheel PATH` | Use an exact wheel file |
| `--venv PATH` | Use a different environment |
| `--launch shell` | Open an activated shell |
| `--launch none` | Install without starting a process |
| `--launch example` | Run `example_python_usage.py`; review its device settings first |
| `--no-examples` | Omit Matplotlib and other example-only dependencies |

Without an interactive terminal, choose a wheel explicitly with `--wheel`,
`--local-newest` or `--latest`. Arguments after `--` go to the launched program:

```sh
./uz_cli/run.sh --local-newest --launch cli -- --help
./uz_cli/run.sh --wheel /path/to/ultrazohm-VERSION-TAGS.whl --launch cli -- serve --interactive --device 192.168.1.233:1000 --format csv
```

PowerShell accepts the same options. Setup can also be invoked directly:

```sh
uv run --no-project --python 3.12 uz_cli/setup_uv.py --examples
```

Direct setup defaults to installation only; `--python VERSION` selects the
interpreter for a new environment. Existing environments must use that Python
series. Setup prints the activation command and validates the installed CLI
without connecting to hardware. Re-running reinstalls the selected wheel.

Inside the activated environment, use `ultrazohm`, `python -m ultrazohm`, or
`uv run --no-project --active ultrazohm`. You can also call the environment's
`bin/ultrazohm` or `Scripts/ultrazohm.exe` directly.

## Build

Source builds require Rust 1.90.0 and a native C/C++ toolchain (Linux:
`build-essential`; Windows: Visual Studio Build Tools with C++ development).
The devcontainer supplies Rust, Maturin and uv. Its post-create script builds a
wheel into `uz_cli/target/wheels`, installs it with example dependencies and
checks imports. Re-run `bash .devcontainer/post-create.sh` to refresh it.
Container-built wheels require a compatible Linux host; Windows needs its own wheel.

From `uz_cli`, the Makefile provides:

| Target | Output |
|---|---|
| `make wheel` | Python wheel, including native extension and CLI entry point |
| `make cli` | Standalone `target/release/ultrazohm` (`.exe` on Windows) |
| `make native` | Rust library artifacts without Python bindings |
| `make all` | All three outputs |
| `make clean` | Remove `target/`, including its wheels; preserve environments and logs |

Targets use release builds and the lockfile, reuse Cargo's cache, and do not
install packages or connect to hardware. Override `CARGO`, `MATURIN` or `WHEEL_DIR`
if needed. Without GNU Make, use the corresponding commands:

```sh
cargo build --release --locked
maturin build --release --locked --out target/wheels
cargo build --release --locked --lib
```

`cargo install --path . --locked` installs the standalone CLI. For Python source
development, install Maturin into a virtual environment and run `maturin develop`.
Rebuild/reinstall after Rust changes. Native Linux ARM64 builds are possible;
these are Linux applications, not executables for the R5 baremetal environment.

## Run

Bare `ultrazohm` starts an interactive, disconnected session with Parquet and CSV
exports configured. At its prompt, enter commands without the executable prefix:

```text
connect                        # default 192.168.1.233:1000
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

Use `help` or `help set-variable`. Tab completes command names; Up/Down recalls
commands from this session. Piped input works too. Arguments are space-separated;
quote paths containing spaces. Backslashes are literal and there is no shell
expansion. Invalid commands report errors and leave the prompt running.
Underscore aliases such as `set_variable` and `start_logging` are also accepted.

For an unattended service, or an interactive service with explicit settings:

```sh
ultrazohm serve --device 192.168.1.233:1000 --output measurement-001 --format csv
ultrazohm serve --interactive --channel-mapping my-mapping.json
```

`serve` without `--device` waits for `connect [IP] [PORT]`. A failed connect can
be retried; a second connect while connected is rejected. Transport failure after
connection ends acquisition and finalizes logs. External CLI/Python clients can
control the service while its interactive prompt waits for input.

All entry points reserve a new output directory but start with logging off.
Without `--output`, CLI/Python sessions use
`<repo>/artifacts/live_logs/<UTC timestamp>`, searching upward from the current
directory; outside a checkout the current directory is the base. Explicit output
directories must not exist and their parent must exist. `serve` defaults to
`--format parquet`; `--format csv` adds CSV exports. Bare `ultrazohm` and Python
`Acquisition()` default to `csv`, which retains Parquet too.

The viewer owns its workspace preferences and log paths separately:
`artifacts/_user` in developer mode and `artifacts/_user_standalone` in standalone
mode. See [viewer usage](../uz_dataviewer/README.md) for settings and worker launch.
The CLI console and Python automation work on Linux and Windows; the viewer's
`uz …` console shortcut is available only on Linux.

### Control and recording lifecycle

- `enable-system`, `enable-control`, `button 1..8`, `set-variable` and `stop`
  send firmware commands. `stop` leaves acquisition running.
- Fast and slow start/stop logging are independent and do not change device state.
  Stop detaches a stream at a complete frame boundary; queued frames drain in the
  background. Wait for `status.logging.<stream>.phase` to become `complete` before
  reading final exports or starting another recording of that stream.
- `pause-logging` / `resume-logging` retain the same fast recording; slow equivalents
  add `-slow-data`. Paused intervals are omitted, with gaps retained in timestamps.
  Observable changes are blocked while either stream is recording or paused.
  Device controls and the live RAM buffer continue during pauses.
- `shutdown`, Ctrl-C, interactive EOF and `Acquisition.close()` send device Stop
  before waiting for queries and recording finalization. Shutdown's reply confirms
  acceptance; process exit and `end.json` report completion. EOF is Ctrl-D on Linux
  or Ctrl-Z then Enter on Windows. Unattended `serve` ignores stdin.

Logging phases are `idle`, `recording`, `paused`, `finalizing`, `complete` and
`failed`. Invalid transitions return errors. Disk/export errors are reported,
not silently ignored. Finalization can take time and additional disk space.
Use an OS process supervisor when acquisition must outlive a terminal or Python.

Local control defaults to numeric loopback `127.0.0.1:19740`; pass `--endpoint`
on both service and clients for another port. This is a trusted-user local API.
Wire commands are `sent_unconfirmed`: firmware has no command acknowledgments.
`error-reset` reports an error because its firmware case is empty.

ACKs default off for current FreeRTOS. `--ack on` or `send-ack on/off` controls
legacy pacing. `status.state.platform_state` reports the latest received mapped
platform state, independently of sent commands. It is null before reception,
after disconnection, and for legacy headers lacking `javascope_status.h`.
Legacy firmware control/logging remains supported; see the
[protocol limitations](docs/protocol.md).

## Runtime profile and firmware channel mapping

| Configuration | Contents |
|---|---|
| Embedded `profiles/standard.json`, or `--profile PATH` | Schema version, name, nominal sample period, initial channels |
| Header-generated mapping, or `--channel-mapping PATH` | Firmware IDs, packet geometry, platform-state decoding and source provenance |

There is no embedded firmware mapping. Without an explicit mapping, run inside
the firmware checkout so headers can be parsed. The two flags are independent:

```sh
ultrazohm profile > my-profile.json
ultrazohm channel-mapping > my-mapping.json
ultrazohm serve --interactive --profile my-profile.json --channel-mapping my-mapping.json
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

The bundled standard profile selects 20 named observables; each must exist in
the mapping. The CLI validates them before connecting. The viewer seeds its own
settings from that template, filtering unavailable names without rewriting
existing preferences. Set `initial_channels` to `{}` or omit it in a custom
profile to leave all slots untouched. Initial selections are sent before the
service becomes ready; they do not enable the system or start logging.

Mapping provenance describes source headers, not verified running firmware.
The IDs, geometry and configured sample period must match the deployed firmware.
Changing JSON requires a service restart, not recompilation. `observables` lists
requested slot assignments and `catalog` returns loaded configuration; neither
claims device readback. Unknown slots are omitted from logs; duplicate observable
IDs use the first selected slot. Names are frozen at recording start.

### Generate a mapping from the checkout

```sh
ultrazohm create-json-from-javascope-h
ultrazohm create-json-from-javascope-h --repo /path/to/ultrazohm_sw --output my-mapping.json
```

The default destination is `<repo>/artifacts/channel_mappings/javascope.json`;
re-running replaces it only after parsing and validation. The command reads
JavaScope enums/send-field names, status definitions, channel count and packet
size from the checkout's headers. No Vitis, C compiler or Python parser is needed.
Git is optional; provenance is `unknown` without it and marks modified headers
with `-dirty`. This parser is not a C preprocessor: unsupported expressions,
duplicate names and unsupported geometry fail explicitly. See the
[header contract](docs/protocol.md#generating-a-mapping-from-firmware-headers).
Generating a file does not reconfigure a running service.

## Python

`Client` controls an existing service. `Acquisition` owns an embedded instance of
the same Rust service and waits until startup is ready. Socket calls release the
GIL; Python does not process incoming samples. Always close an embedded acquisition:

```python
import time
from ultrazohm import Acquisition, Client

acquisition = Acquisition(output="python-run", format="csv")
uz = Client()
try:
    uz.connect()  # or pass device="192.168.1.233:1000" to Acquisition
    uz.set_observable("lifecheck", 1)
    uz.set_variable("send_field_1", 12.5)
    uz.start_logging()
    time.sleep(1)  # Perform the measurement here.
    print(uz.status())
finally:
    acquisition.close()  # Stop, finalize, and surface runtime/storage errors.

recorded = acquisition.read_recording()  # First fast recording, as Polars.
```

`Acquisition` also accepts `profile`, `channel_mapping`, `endpoint`,
`buffer_samples`, `segment_rows`, `flush_interval_ms` and `recording_backend`.
`output` exposes the resolved session directory. `Client` has matching named
control/logging methods, including pause/resume for both streams. Embedded
acquisition ends with its Python process; an external service can survive it.
Local Vitis tools currently use the CLI, not module-level Python functions.

## Unified RAM and recording access

```python
from ultrazohm import Client, Recording

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

`recording=None` selects the bounded live ring; positive recording numbers select
that recording's history, including pending samples. Fast/slow numbering is
independent; `stream="slow"` returns original rotating updates. `recordings()`
lists sources. Durable `Recording` handles include only indexed, committed data.
`acquisition.recording()` and `read_recording()` require successful close and
backend completion; `recording_path()` resolves a completed merged export.

Ranges are half-open `[start, stop)`. Live positions count acquisition samples;
recording positions count recorded rows from their first accepted acquisition
position. Check `position_basis`; use `time` for timestamps, especially after
pauses. Cursors identify run/source/mapping generation and must be reused unchanged.
Expired cursors, unknown channels, unavailable ranges and oversized tails fail
explicitly. Empty pages preserve the cursor position.

Results are independent Polars frames transported as Arrow IPC. `DataPage`
provides `.data`, `.cursor`, `.start`, `.stop` and `.info`. Column selection keeps
`time`/`status`, preserves requested order and removes duplicates; `channels=[]`
selects only time/status. Disk projection occurs before decoding/transferring
unrequested signals. Metadata distinguishes accepted and persisted ranges.
Up to four background reads run concurrently; each response is capped at 128 MiB.
Page large reads instead of materializing the full recording.

CLI equivalents print metadata and at most 20 preview rows:

```sh
ultrazohm data-info --recording 1
ultrazohm recordings
ultrazohm tail 500
ultrazohm read-range 1000 2000 --recording 1 --channels JSO_lifecheck
ultrazohm read-since --recording 1 --limit 10000
```

Supply `--cursor '<previous cursor JSON>'` to continue. `tail` replaces the old
`get-live-data` / `Client.get_live_data` interface; only the unified query path is supported.

## Recording outputs

Only explicitly started streams produce measurement files. Each recording keeps
immutable Parquet parts and a `*.recording.json` index as canonical storage.
Finalization adds merged Parquet and optionally CSV; parts remain available to
concurrent/durable readers. Budget disk space for both. For the first recordings:

```text
measurement-001/
    run.json                       # Validated configuration and session metadata
    commands.jsonl                 # Host command audit
    data.recording.json            # Fast backend/range index
    data-part-00000000.parquet      # Canonical fast segment (more as needed)
    data.parquet                   # Merged fast export
    data.json                      # Assignments, rows and completion
    data.csv                       # Additional export for --format csv
    data_slow_data.recording.json   # Slow index; corresponding parts/exports
    end.json                       # Session health, written at service exit
```

Subsequent recordings use `data_0002...`, with independent counters for each
stream. Existing files are not overwritten. Empty started recordings produce
typed empty outputs. `.partial` files are not published measurements.

Fast columns are `time` (Float64 nominal seconds), `status` (UInt32 packet status)
and selected observable names (Float32). Time starts with acquisition, not logging.
NaN/Inf are preserved. The status word describes the packet's last sample and is
repeated across its rows; it is not a precise transition timestamp.

Canonical slow history contains `observable`, `slow_id`, `slow_raw`, `slow_value`,
`time` and `status`. Final slow exports are wide, forward-filled tables, marked
`wide_forward_filled` in metadata. They emit rows only after all observables have
values, carry values across segments, and reset filling after pauses. A never-seen
observable makes the wide export empty. Held values are not newly sampled values;
raw update history remains available. Fast and slow row counts may differ.

### Buffering and failure behavior

Defaults retain 30 seconds in RAM, flush at 1,000,000 rows or 60,000 ms, and use
an independent bounded 2,048-frame queue per logger. Configure them with:

```sh
ultrazohm serve --buffer-samples 100000 --segment-rows 50000 --flush-interval-ms 1000
```

Settings are fixed for the service lifetime and reported in `status.data_options`.
The ring retains at most one partial extra frame internally; queries respect its
exact sample capacity. Observable changes clear live history and invalidate its
cursors. Samples that leave RAM while logging is off cannot be recovered.

Stopping flushes partial batches. Queue overflow, disk failure and export failure
are explicit errors; committed chunks remain readable. Abrupt termination can lose
uncommitted batches and pending writes. Incomplete indexed runs remain readable,
but automatic repair/merge is not implemented. Optional export failure does not
invalidate canonical data, though close/status still report the error.
Firmware gaps and exact observable-switch boundaries cannot be recovered from
this protocol. See [architecture](docs/architecture.md) for the storage invariants.

## Vitis workspace, build and JTAG programming

Load the Vitis 2022.2 environment so `xsct` is on PATH:

```sh
ultrazohm generate              # generate/build an empty vitis/workspace
ultrazohm generate --open       # also open Vitis GUI; needs its launcher on PATH
ultrazohm build                 # incremental application build
ultrazohm build-clean           # clean platform/applications, then rebuild
ultrazohm flash                 # incremental build, JTAG program and run
ultrazohm build --repo "/path/to/ultrazohm_sw"
```

These local commands need a checkout, not an acquisition service. Repository
search starts from the current directory; `--repo` selects an exact root. The
workspace is `<repo>/vitis/workspace`; generation refuses populated workspaces.
`generate-workspace` aliases `generate`. `flash --profile Run_UltraZohm` is the
supported launch profile; debug profiles use the GUI. Flash here means JTAG
programming/execution, not persistent flash-memory writing.

Commands run `xsct -nodisp .../tcl_scripts/vitis_headless.tcl`, stream its output
and propagate failures. On Linux load `settings64.sh`; on Windows use the Vitis
command environment. The viewer also provides an XSCT picker and remembers its
launcher in workspace `tools.json`. Avoid concurrent Vitis operations on one
workspace and close acquisition before programming the connected device.

Incremental builds reuse generated Makefiles when inputs are unchanged, report
whether work is needed, and refresh through Vitis when metadata/toolchain inputs
change. `flash` programs even when no rebuild is needed. `build-clean` rebuilds
platform/BSPs and applications while preserving sources/configuration. These
commands do not generate SD-card BOOT.BIN images. Equivalent Make targets are
`make -C vitis build` and `make -C vitis build-clean`.

## Tests

From the repository root:

```sh
cargo test --manifest-path uz_cli/Cargo.toml --locked
cargo build --manifest-path uz_cli/Cargo.toml --locked
cargo clippy --manifest-path uz_cli/Cargo.toml --all-targets --features python --locked -- -D warnings
python -m unittest discover -s uz_cli/tests -v
```

Set `UZ_CLI_BIN` for another executable. Install the wheel and Polars to exercise
Python bindings and independently read outputs. Tests use loopback simulators,
including `--legacy-ack`, and fake Vitis tooling; they do not program hardware.
Manual simulation: `python javascope/test_server.py --host 127.0.0.1 --port 1000`.
Synthetic dynamics do not model hardware interlocks or firmware queue races.
Linux/Windows CI and hardware validation remain separate from local test results.

## Publishing CLI wheels

The [CLI workflow](../.github/workflows/ultrazohm-cli.yml) checks Linux and Windows.
After successful checks, pushes/manual runs on `main` publish stable wheels and
`feature/uz_cli26` publishes testing prereleases. Other branches and PRs only test.
Publishing requires both platform checks and tested release wheels.

Release targets are Windows x86-64 and Linux x86-64 `manylinux_2_28` (glibc 2.28+),
using Python's 3.10+ stable ABI. macOS/ARM64 release wheels are not included.
CI derives `.postN` or `.devN` versions from the base project version and run
identity. Tags use `uz-cli-v<VERSION>` or `uz-cli-testing-v<VERSION>`. Wheels and
`SHA256SUMS` are staged in a draft, then published using `GITHUB_TOKEN`.
Setup selects by CLI tag/channel/publication time; these releases do not replace
the repository's overall latest release. Local wheels work before any release exists.
