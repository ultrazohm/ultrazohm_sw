# UltraZohm CLI and Python API

Standalone Rust acquisition, control and CSV/Parquet logging for the existing
JavaScope firmware. Linux and Windows use the same code. No firmware changes,
GUI, Python interpreter or cloud service are required by the executable.

Read the [wire/API specification](docs/protocol.md) and
[implementation plan and architecture](docs/architecture.md) before adapting a
profile to different firmware. Viewer integration is deliberately deferred.

## Build

Install Rust 1.90.0 and a native C/C++ build toolchain (Linux: build-essential;
Windows: Visual Studio Build Tools with Desktop development with C++).
The updated devcontainer includes Rust, rustfmt, clippy, maturin and uv. Its
`.devcontainer/post-create.sh` builds a wheel from the mounted checkout and saves
it in `uz_cli/target/wheels` for `run.sh`. It installs that same wheel with the
`examples` extra (Python Polars and Matplotlib), then verifies imports.
Wait for post-create setup to finish; the first Rust build can take time.
To rebuild the wheel and update packages in an already running container, run
from the repository root:

```sh
bash .devcontainer/post-create.sh
```

The saved wheel targets the container's Linux environment; using it on a host
requires a compatible OS, architecture and glibc version. Windows needs its own wheel.

Use the same Python interpreter to run `uz_cli/example_python_usage.py`.
Installing the Python package also provides an `ultrazohm` console command and
`python -m ultrazohm`. They call the same compiled Rust CLI implementation as the
standalone executable; no separate executable is needed. Installing from source
builds the native extension; installing a prebuilt wheel needs no Rust toolchain.
Reinstall after Rust source changes to refresh the native extension.

```sh
cd uz_cli
make cli
# Optional: install the standalone executable onto Cargo's bin path.
cargo install --path . --locked
```

The [Makefile](Makefile) provides separate build targets (GNU Make):

| Command, from `uz_cli` | Output |
|---|---|
| `make wheel` | Python wheel in `target/wheels`, including the Rust extension and Python CLI entry point |
| `make cli` | Standalone executable in `target/release` |
| `make native` | Rust library artifacts (`.rlib` and platform shared library) in `target/release`, without Python bindings |
| `make all` | All three outputs |

From the repository root, use `make -C uz_cli wheel`, etc. Both Maturin and Cargo
reuse Cargo's build cache. The wheel already contains its native Python extension;
`make native` is not a prerequisite. Likewise, the standalone CLI does not need
a separate library build. All targets use release mode and the checked-in lockfile.
`make` alone prints help. Override tool paths with `CARGO=...` / `MATURIN=...`,
or change wheel output with `WHEEL_DIR=...`. No target installs packages or connects
to a device. On Windows without GNU Make, use the underlying Cargo/Maturin commands.

The executable is `target/release/ultrazohm` (`ultrazohm.exe` on Windows).
Copying it to another machine requires a compatible OS/architecture and system
runtime. Build natively for Linux ARM64 to run on an UltraZohm Linux installation;
this is not an executable for the R5 baremetal/FreeRTOS environment. It still
connects to a compatible TCP acquisition source; direct Linux hardware drivers
are outside this implementation.

## One-command setup and launch

With uv installed (no Rust, Cargo or C/C++ build tools needed):

```sh
./uz_cli/run.sh
```

Windows PowerShell:

```powershell
.\uz_cli\run.ps1
```

Both scripts read the Python version from `.devcontainer/Dockerfile` (currently
3.12), ask uv to install that interpreter, create/reuse the host or container
virtual environment, install the wheel plus Polars/Matplotlib, and launch
an activated environment shell. No device connection is opened. Type `exit` to leave
the environment shell. No Rust toolchain is needed.
The Docker tag specifies the 3.12 series, not an exact patch release. An existing
environment must use that Python series; choose a new `--venv` path when changing
Python versions. Run the scripts rather than sourcing/dot-sourcing them.

If compatible wheels exist in `uz_cli/target/wheels`, setup offers a numbered
menu with each local wheel and **Download newest CLI release**. Local wheels are
ordered by package version, then platform-tag preference. With no compatible local
wheel, it automatically downloads the newest published release for the selected
channel, verifies its SHA-256 checksum and saves it in that directory.

The channel defaults to `testing` on `feature/uz_cli26` and `stable` on all other
branches (including detached checkouts or when Git is unavailable). Override it
with `--channel stable` or `--channel testing`. Local wheels from either channel
remain selectable; the channel controls downloads. Drafts, other software releases
and releases from the other channel are ignored. If the newest release has no
compatible wheel, setup fails clearly instead of silently installing an older one.

For explicit selection or unattended setup:

```sh
./uz_cli/run.sh --latest --channel stable   # download even if local wheels exist
./uz_cli/run.sh --latest --channel testing
./uz_cli/run.sh --local-newest              # highest-version compatible local wheel
```

Without an interactive terminal, local wheels require `--wheel`, `--local-newest`
or `--latest`. `--wheel` validates and uses that exact file. Pass CLI arguments
after `--`:

```sh
./uz_cli/run.sh --wheel /path/to/ultrazohm-VERSION-TAGS.whl --launch cli -- serve --interactive --device 192.168.1.233:1000 --output measurement-008 --format both
```

PowerShell accepts the same selection, channel, `--venv`, and launch arguments.
For the existing Python example instead of the CLI, use `--launch example`:

```sh
./uz_cli/run.sh --wheel /path/to/ultrazohm-VERSION-TAGS.whl --launch example
```

That example executes the running/control/stop sequence against its configured
device; edit its device/profile settings first. `--launch cli -- --help` launches CLI help
without connecting. Output paths remain relative to the directory you launch from.
The scripts install binary wheels only; they never build Rust or install docs tools.
Release downloads use the public `ultrazohm/ultrazohm_sw` GitHub repository and
need network access. A local-wheel selection does not contact the GitHub API.
Downloaded wheels contain the released code, not changes in your local Rust sources.

## Install a local wheel with uv (no Rust needed)

The user needs uv and a wheel compatible with their OS/architecture and Python
(Python 3.10 or newer). The wheel contains the compiled Rust CLI/backend. It does
not launch Cargo or a separately installed Rust executable.

From the repository root:

```sh
uv run --no-project --python 3.12 uz_cli/setup_uv.py --examples
```

The cross-platform script creates `uz_cli/.venv-host` on the host or
`uz_cli/.venv-container` inside Docker and uses the same selection/download flow.
It **never builds the package** and allows only binary dependency distributions.
`--examples` also installs Python Polars and Matplotlib; omit it for just the CLI
and Python API. Compatibility checks use the destination interpreter's wheel tags.
Existing local wheels are preserved (a verified download may replace the same
release filename). To select a particular local wheel:

```sh
uv run --no-project --python 3.12 uz_cli/setup_uv.py --wheel /path/to/ultrazohm-VERSION-TAGS.whl --examples
```

Use `--venv PATH` for a different environment or `--python VERSION` for a new
environment's interpreter. Create the environment on the machine/container where it will run; virtual
environments cannot be shared between host and container. Existing environments
are reused without being cleared;
rerunning setup reinstalls UltraZohm from the selected wheel. uv rejects incompatible
wheel tags. Setup checks the installed CLI with `--version`, without device access.

An older shared `uz_cli/.venv` may contain container paths and must not be activated
on the host. Run `deactivate` first if it is active, then run setup using `python3`
or uv with the local wheel. Inside Docker, activate `uz_cli/.venv-container/bin/activate`.
The script prints the exact activation command for its environment.

Activate on the Linux host:

```sh
source uz_cli/.venv-host/bin/activate
ultrazohm serve --interactive --device 192.168.1.233:1000 --output measurement-001 --format both
# Equivalently: python -m ultrazohm serve --interactive ...
```

Activate in Windows PowerShell:

```powershell
.\uz_cli\.venv-host\Scripts\Activate.ps1
ultrazohm serve --interactive --device 192.168.1.233:1000 --output measurement-001 --format both
```

Within the activated environment, `uv run --no-project --active ultrazohm ...`
also works. Use `--no-project` to avoid uv attempting to build this repository's
source project. No activation is needed if you call `uz_cli/.venv-host/bin/ultrazohm`
(or `uz_cli\.venv-host\Scripts\ultrazohm.exe`) directly. Python API and console entry
point use the same installed wheel. `serve` remains alive until shutdown/Ctrl-C;
embedded `Acquisition` remains bounded by its Python process.

For the developer who manually builds the wheel (Rust and Maturin required):

```sh
cd uz_cli
make wheel
# Equivalent: maturin build --release --locked --out target/wheels
```

Build separately for each target platform. The setup script has no build step.

## Run

Start one acquisition process and leave it running:

```sh
ultrazohm serve --device 192.168.1.233:1000 --output measurement-001 --format both
```

The output directory must be new; its parent must exist. `serve --output` reserves
a session directory but **does not start logging**. Format is `parquet` (default),
`csv`, or `both`. Start fast and slow recording explicitly and independently.
Each enabled recording uses Parquet segments, merges on stop, and optionally
converts its completed Parquet to CSV. Omit `--output` for control/monitoring only;
start-logging commands then return a clear error.
In another terminal:

```sh
ultrazohm status
ultrazohm set-variable send_field_1 12.5
ultrazohm set-observable JSO_lifecheck 1
ultrazohm set-observable ISR_Period_us 2
ultrazohm start-logging
ultrazohm start-logging-slow-data
ultrazohm send-ack on
ultrazohm send-ack off
ultrazohm stop-logging
ultrazohm stop-logging-slow-data
ultrazohm status
ultrazohm stop
ultrazohm shutdown
```

Alternatively, use a command prompt in the same terminal (Linux and Windows):

```sh
ultrazohm serve --interactive --device 192.168.1.233:1000 --output measurement-001 --format both
```

At `ultrazohm>`, type commands without the executable prefix:

```text
status
set-variable send_field_1 -12.5
set-observable lifecheck 1
start-logging
start-logging-slow-data
send-ack on
stop
stop-logging
stop-logging-slow-data
status
shutdown
```

This is the application's prompt, not your operating-system shell. Use
space-separated arguments and `help` or `help set-variable` for usage. Invalid
commands report an error and leave the session running. External CLI/Python
clients can still send commands while the prompt waits for input. `stop` keeps
acquisition running; `shutdown`, Ctrl-C, or stdin EOF ends the service and waits
for log finalization before returning to your shell. On a terminal, EOF is
Ctrl-D on Linux or Ctrl-Z followed by Enter on Windows. Startup or acquisition
failure exits even if the prompt is waiting for input. Without `--interactive`,
`serve` keeps its existing unattended behavior and ignores stdin.

Underscore aliases work too: `set_variable`, `set_observable`, `send_ack`,
`enable_system`, `enable_control`, `error_reset`, and all four logging commands. Shell syntax uses space-separated
arguments; Python provides `client.set_variable("send_field_1", 12.5)`.

`start-logging` / `stop-logging` control fast data; `start-logging-slow-data` /
`stop-logging-slow-data` control slow data. Neither changes device state.
Stopping removes the recording from the receiver at a complete frame boundary;
already queued frames drain and finalization runs in the background. The reply's
`logging` object (also returned by `status`) reports `idle`, `recording`,
`finalizing`, `complete`, or `failed`, with the output path and any error.
Wait for `complete` before reading the final file or restarting that stream.
Acquisition and the other stream continue. Repeated starts while recording or
finalizing, and stops of an inactive stream, return errors.

`set-observable` is rejected while **either** stream is recording:
`setting observable is not possible when logging is active; stop fast and slow logging first`.
The rejected command sends nothing to the device. Selection is allowed again once
both stop commands have detached their streams, even while files finalize.

`enable-system`, `enable-control`, and `button 1..8` expose the corresponding
firmware requests. `stop` sends the device Stop request; acquisition continues.
`shutdown` requests the end of acquisition; its reply acknowledges the request,
not completed export. The service then drains its queue, merges segments into
the fast/slow final Parquet files, optionally exports their CSV counterparts, and removes the segments only after
that recording's requested outputs succeed. Wait for process exit and inspect `end.json` for
the result. Shutdown does not stop the device. Ctrl-C follows the same finalization
path. Large recordings can take time and require space for segments plus the final
Parquet and optional CSV during finalization. For detached use, run `serve` under systemd,
Windows Task Scheduler, or your existing process supervisor. Closing the GUI or
exiting a short CLI command has no effect on `serve`.

All wire-command results are **sent_unconfirmed**: current firmware has no
command acknowledgment. `error-reset` explicitly errors because its firmware
case is empty. Read [protocol limitations](docs/protocol.md) for state-machine
sequencing, unknown data gaps, single-device-client ownership and time semantics.

Local control defaults to `127.0.0.1:19740`. Use `--endpoint 127.0.0.1:19741` on
both service and commands for another device. Only numeric loopback endpoints
are accepted. This is a local trusted-user API, not an authenticated remote API.

ACKs default off for current FreeRTOS. `--ack on` enables them from startup;
`send-ack on/off` changes the persistent background policy without reconnecting.
With legacy pacing, leaving ACK off eventually causes the five-second stream
stall timeout. Real current FreeRTOS streams continuously with ACKs disabled.

## Runtime profile and firmware channel mapping

Two independent JSON files are loaded at startup:

| File | Purpose |
|---|---|
| `profiles/standard.json` | Profile schema/name, sample period, initial channel selections |
| `channel_mappings/default.json` | Firmware API version, mapping name, repository name/commit, packet geometry, observable/slow/variable/command IDs |

Both defaults are embedded in the executable, so no JSON files are required at
runtime unless you want overrides. Export editable copies:

```sh
ultrazohm profile > my-profile.json
ultrazohm channel-mapping > my-channel-mapping.json
ultrazohm serve --interactive --device 192.168.1.233:1000 --output measurement-001 --profile my-profile.json --channel-mapping my-channel-mapping.json
```

Either flag can be omitted independently. The other file then uses its embedded
default. Both files are read at startup; changing them requires restarting the
service, not recompiling. The former combined `profiles/default.json` has been
replaced by these two files; old combined profiles are rejected rather than
silently interpreted with the wrong settings.

A runtime profile looks like:

```json
{
  "schema_version": 1,
  "name": "my-measurement",
  "sample_period_us": 100.0,
  "initial_channels": {
    "1": "JSO_lifecheck",
    "2": "JSO_ISR_ExecTime_us"
  }
}
```

The supplied standard profile selects observable IDs **1 through 20**, in order,
into channels **1 through 20**. ID 0 (zero placeholder) is excluded. Thus channel
1 starts with `JSO_ISR_ExecTime_us`, channel 2 with `JSO_ISR_Period_us`, channel 3
with `JSO_lifecheck`, and channel 20 with `JSO_Theta_el`. Some firmware observables
are declared but unassigned and still return zero.

Startup validates all selections against the chosen mapping before connecting.
After connecting it sends selections in channel order, records them in
`commands.jsonl` when an output directory is configured, and only then starts
serving user commands. It does not enable the system, enable control, or start
logging. Set `initial_channels` to `{}` (or omit it in a custom profile) to send
no startup selections. Unlisted channels are untouched and remain unknown.

The channel mapping is a firmware contract, not discovery. Its `repository.name`
and `repository.commit` identify the source of the mapping, not a verified running
firmware revision. The default records `ultrazohm/ultrazohm_sw` at
`6b04d018fc11898247ef8c4ce3dc6fde7adaecca`. Wire geometry and IDs must match the
deployed firmware. The runtime profile's sample period must match actual sampling;
do not estimate it from packet arrival rate.

`set-observable JSO_lifecheck 1` resolves ID 3 from the mapping's `observables` and
sends command 201 with float value 3. Adding a mapping entry only names an already
implemented firmware observable; it cannot add firmware behavior. `variables` is
a separate map of writable send-field commands (IDs 4..23). For example,
`"speed_reference": 4` is valid only if send field 1 means that in your firmware.

Inspect assignments with `ultrazohm observables` (alias `get-observables`), or
`observables` at the interactive prompt. The JSON lists all 20 channels with
`channel`, canonical mapping `name`, numeric observable `id`, and `state`.
Startup and manual selections are `sent_unconfirmed`; untouched channels have
null name/ID and `unknown`. Firmware has no assignment query or acknowledgment,
so the response says `device_readback: false`. A restart reapplies the new
profile's initial selections; other channels remain unknown even if the device
retains old assignments. Failed or rejected selections do not change the reported
mapping. Python: `Client().observables()`.

Log headers use observable names only, for example `JSO_lifecheck`, with no channel
prefix or number. Names are resolved from the active channel mapping and frozen
when logging starts. A repeated observable ID appears once, using its first selected
slot; unassigned slots are omitted. Fast logging requires at least one known selection.
Both CSV and Parquet are self-describing; no sidecar lookup is needed to identify
signals. Sidecars still preserve the requested assignments for diagnostics. Buffered
old data may arrive after a selection because firmware has no acknowledgment, so the
labels represent requested assignments rather than confirmed sample boundaries.
Changes are allowed only before either logger starts or after both loggers stop.

## Python

Build/install the native package using a Python virtual environment:

```sh
python -m pip install maturin
python -m pip install ./uz_cli
# Or, from uz_cli: maturin develop
```

For an external acquisition process:

```python
from ultrazohm import Client

uz = Client()  # Existing `ultrazohm serve` process
uz.set_variable("send_field_1", 12.5)
uz.set_observable("lifecheck", 1)  # Before either logger starts.
uz.start_logging()
uz.start_logging_slow_data()
uz.send_ack(True)
print(uz.status())
uz.stop_logging()
uz.stop_logging_slow_data()
uz.stop()
```

For embedded acquisition (no CLI executable required; omit `profile` and
`channel_mapping` to use embedded defaults):

```python
import time
from ultrazohm import Acquisition, Client

acquisition = Acquisition(
    "127.0.0.1:1000", output="python-run", format="parquet",
    profile="my-profile.json", channel_mapping="my-channel-mapping.json",
)
try:
    uz = Client()
    # Service startup is asynchronous. close() surfaces any startup/runtime error.
    while True:
        if acquisition.is_finished():
            acquisition.close()
            raise RuntimeError("acquisition ended before startup")
        try:
            uz.status()
            break
        except RuntimeError:
            time.sleep(0.05)
    uz.set_observable("lifecheck", 1)
    uz.start_logging()
    time.sleep(2)
    uz.stop_logging()
finally:
    acquisition.close()  # Wait for draining, Parquet merge and optional CSV export
```

The embedded service lifetime is bounded by the Python process. The external
service is the option for logging that must survive Python exit. Both use Rust
threads, Rust TCP decoding and Rust Polars writers. Python control calls release
the GIL; Python never processes individual incoming samples.

## Recording outputs

Only explicitly started streams produce measurement files. During recording,
`data-part-00000000.parquet` and/or `data_slow_data-part-00000000.parquet` are
complete, independently readable segments. `.partial` files are not published output.

After stopping both first recordings and waiting for `complete`:

```text
measurement-001/
    run.json
    commands.jsonl
    data.parquet            # Fast: time, status, JSO_ISR_ExecTime_us, ...
    data.json               # Requested channel assignments, rows, completion
    data_slow_data.parquet   # Slow: time, status, observable, slow_id, slow_raw, slow_value
    data_slow_data.json
    data.csv                # Only for --format csv or --format both
    data_slow_data.csv       # Only for --format csv or --format both
    end.json                # Created when the service exits
```

Each stream has an independent recording counter. Subsequent recordings use
`data_0002.parquet`, `data_0003.parquet`, etc. and
`data_0002_slow_data.parquet`, etc. Earlier recordings are never overwritten.
Never-started streams produce no measurement file. Started but empty recordings
produce a typed zero-row Parquet and, if requested, a header-only CSV.

The finalizer reads one segment at a time and validates the schema, nominal times
and row count. CSV conversion reads the completed Parquet in slices of at most
65,536 rows. Each recording removes its segments only after its own merge and
requested CSV export succeed. A failure retains that recording's segments and
already published outputs; independently completed recordings remain usable.

`time` is the only time column: nominal seconds since **acquisition** started,
using the profile's configured sample period. It does not reset when a logger
starts, so separately started fast/slow recordings share the same time origin.
The internal sample counter is not exported. No `sample_index`, `time_s` or
`host_received_unix_ns` columns remain. `status` is still the packet's last-sample
status word, repeated across that packet; it is not a precise transition timestamp.

Slow rows contain the received rotating updates, including placeholder ID 0. The
`observable` string column gives the full signal name on each row alongside
`slow_id`, `slow_raw` and `slow_value`; no mapping lookup is required. There is no
forward-fill. Because start/stop
times are independent, fast/slow row counts need not match. Overlapping rows can
be aligned on `time`. Firmware gaps and exact selection boundaries remain unknown.

```python
import polars as pl

# After status reports this recording complete, or acquisition.close() returns:
data = pl.read_parquet("measurement-001/data.parquet")
```

Shutdown and Python `Acquisition.close()` finalize all active recordings and wait
for finalizers already running. A sudden kill leaves complete segments recoverable
but does not automatically merge them. Automatic recovery is not implemented.
`run.json` contains session metadata; `commands.jsonl` audits host command events;
recording sidecars summarize individual files; `end.json` reports session health.
Existing recordings are not migrated. See [architecture.md](docs/architecture.md).

## Tests

From the repository root:

```sh
cargo test --manifest-path uz_cli/Cargo.toml --locked
cargo build --manifest-path uz_cli/Cargo.toml --locked
python -m unittest discover -s uz_cli/tests -v
```

Set `UZ_CLI_BIN` to test another executable. Install the Python wheel and Python
`polars` to additionally exercise native control bindings and independently read
Parquet output. The tests launch only loopback fixtures, not hardware.

Manual test server:

```sh
python javascope/test_server.py --host 127.0.0.1 --port 1000
ultrazohm serve --device 127.0.0.1:1000 --output test-run --format both
```

The simulator now streams independently of commands, accumulates fragmented
8-byte commands and processes coalesced commands. It starts channels at zero,
returns zero for unassigned firmware pointers, preserves device state across
connections, and leaves Error_Reset as a no-op.
`--legacy-ack` enables the old lock-step fixture for ACK tests. Its motor dynamics,
scheduling and sample generation remain synthetic: it does not simulate actual
hardware interlocks, ISR latency, firmware queue overflow or shared-memory races.

The CI workflow builds/tests on Linux and Windows and builds the native Python
wheel. Hardware validation, Windows runtime validation outside CI, and an ARM64
hardware run are separate from local Linux simulator validation.

### Local validation (2026-10-26)

- Linux x86_64 standalone release build succeeded; dynamic dependencies are the
  standard C/math/GCC runtimes, with no Python or Java dependency.
- Native abi3 Python wheel built and installed; tested using CPython 3.10.
- Six Rust codec/storage tests cover multiple-segment merging, final batches,
  empty recordings, CSV conversion across slice boundaries, and retention after
  merge/export failure. Twenty-four simulator/integration tests cover release-binary
  control, ACK toggling, active segment reads, native Python acquisition,
  malformed/fragmented frames, disconnects, disk errors, final CSV outputs, and
  interactive commands, EOF, external shutdown and Ctrl-C.
- `cargo fmt --check`, strict Clippy with Python enabled, and `git diff --check`
  passed.
- Windows CI is configured but was not executed locally. Hardware/ARM64 runs and
  rebuilding the full devcontainer image were not performed in this environment.

### Starting offline and connecting later

`serve` starts disconnected unless `--device IP:PORT` is supplied:

```sh
./uz_cli/run.sh                 # prepare uv environment and open an activated shell
ultrazohm serve --interactive --output measurement-009 --format both
```

At the `ultrazohm>` prompt:

```text
status
connect                        # defaults to 192.168.1.233 port 1000
# Or: connect 192.168.1.234 1000
start-logging
stop-logging
shutdown
```

From another terminal use `ultrazohm connect [IP] [PORT]`. A failed connection
attempt leaves the service running so you can retry. `status` includes
`state.connected` and `state.device`. Initial observables are applied upon
connection; before that, assignments are unknown. Logging and device commands
require a connection. A second connect while connected is rejected. Transport
failure after connection still ends acquisition and finalizes logs.

Python can also create `Acquisition(output="measurement-010")` without a device,
then call `Client().connect()` once the service endpoint is ready. Passing
`device="192.168.1.233:1000"` to `Acquisition` retains immediate connection.
The launchers also support explicit `--launch cli` or `--launch example`.

### Default interactive session

Run `ultrazohm` (or `python -m ultrazohm`) without a command to open an interactive,
disconnected session. It creates `measurement-YYYYMMDD-HHMMSS-NNNNNNNNNZ` in the
current directory; the timestamp is UTC with nanoseconds to avoid collisions.
The output path is printed at startup. Both Parquet and CSV are enabled, but
logging stays off until requested:

```text
ultrazohm> connect
ultrazohm> start-logging
ultrazohm> stop-logging
ultrazohm> shutdown
```

Explicit commands retain their behavior, including `serve`, `serve --interactive`,
and `--help`. `--endpoint ADDRESS` can also select the control endpoint for the
default session. The uv launch scripts still only open an environment shell.

### Vitis workspace, build and JTAG programming

With the Vitis 2022.2 environment loaded and `xsct` on `PATH`:

```sh
ultrazohm generate              # generate/build an empty vitis/workspace
ultrazohm generate --open       # also open the Vitis GUI
ultrazohm build                 # incremental application build
ultrazohm build-clean           # clean platform and applications, then rebuild
ultrazohm flash                 # incremental build, then JTAG program and run
ultrazohm build --repo "/path/to/ultrazohm_sw"
```

`generate-workspace` is an alias for `generate`. `flash --profile Run_UltraZohm`
is the supported launch profile; debug profiles require the Vitis GUI. Here
“flash” means JTAG programming and execution, not persistent flash-memory writing.

These commands run locally without a running acquisition service. They search
upward from the current working directory for `tcl_scripts/vitis_headless.tcl`
and `vitis/software`, or use the exact repository root supplied by `--repo`.
They do not search relative to the installed executable or Python package. A wheel
installation still needs a checkout containing the Vitis scripts and sources.
Relative `--repo` paths are relative to your current directory. The workspace
remains `<repo>/vitis/workspace`; generation refuses an already populated workspace.

The CLI invokes `xsct -nodisp <repo>/tcl_scripts/vitis_headless.tcl <action>`,
with the repository as its working directory, and streams tool output to the
terminal. Missing XSCT and failed tool invocations return errors. Load
`settings64.sh` on Linux or use the Vitis command environment on Windows;
`generate --open` additionally requires the `vitis` GUI launcher on `PATH`.

The same commands work at the interactive prompt. Quote paths containing spaces,
e.g. `build --repo "C:\Projects with spaces\ultrazohm_sw"`. Prompt backslashes
are literal; it does not perform shell expansion. Vitis runs in the foreground,
so the prompt waits for completion. Do not run concurrent Vitis operations on the
same workspace, or program hardware while recording from that device.

`build` reuses Vitis-generated Makefiles when workspace inputs are unchanged.
Make checks source/header dependencies each time. Platform inputs/outputs,
application metadata, generated Makefiles, source-file lists and toolchain paths
are checked against the last successful build. Changes or missing files fall back
to Vitis named application builds to refresh the workspace. The first build after
this update also takes that path.
It does not force platform regeneration or package system-project BOOT.BIN files.
`flash` uses this same incremental path before programming. `build-clean` cleans
both applications and the platform (including BSPs), then rebuilds the applications;
it preserves workspace configuration and sources. Neither build command generates
SD-card boot images. The corresponding Make targets are `make -C vitis build`
and `make -C vitis build-clean`.

## Publishing CLI wheels

The `UltraZohm CLI` GitHub Actions workflow tests on pushes and pull requests.
After its tests pass, pushes affecting the CLI/workflow on `main` publish stable
CLI releases; `feature/uz_cli26` publishes testing prereleases. Manual workflow
dispatch is also supported on those two branches. Other branches and pull requests
never publish. No separate upload credential is needed: the publish job uses
`GITHUB_TOKEN` with `contents: write`.

Each release builds and tests these wheels before publishing:

- Windows x86-64 (`win_amd64`).
- Linux x86-64 (`manylinux_2_28`, glibc 2.28+, including Ubuntu 20.04 and newer).

ARM64 and macOS release wheels are not included. The extension uses the Python
3.10+ stable ABI; the launch scripts currently provision Python 3.12. Linux wheels
are built inside the manylinux container, not the newer development container.

`pyproject.toml` contains the base version. CI adds `.postN` for stable releases
or `.devN` for testing, where N combines the workflow run number and retry attempt.
This makes every published build identifiable without changing the source version
on each commit. The release CLI's `--version` reports that same wheel version.
Tags are `uz-cli-v<VERSION>` and `uz-cli-testing-v<VERSION>`. Assets are staged in a
draft release with `SHA256SUMS`, then published after both uploads are complete.
CLI releases do not replace GitHub's overall latest repository release; setup
selects CLI releases by tag prefix, channel and publication time.

The first successful workflow run on the relevant branch must publish a release
before automatic downloads can work. Existing local wheels work before that.
