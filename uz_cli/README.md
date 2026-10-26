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
| `make clean` | Remove `uz_cli/target/`, including build artifacts and wheels stored there; keep virtual environments and logs |

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
`ultrazohm` directly in that environment. Its interactive session starts disconnected,
with CSV and Parquet output configured and logging off. Type `connect` to connect
to the device and `shutdown` to exit. No Rust toolchain is needed.
Use `--launch shell` to open an activated environment shell instead.
The Docker tag specifies the 3.12 series, not an exact patch release. An existing
environment must use that Python series; choose a new `--venv` path when changing
Python versions. Run the scripts rather than sourcing/dot-sourcing them.

If compatible wheels exist in `uz_cli/target/wheels`, setup offers a numbered
menu with only **Use latest local build** and **Download latest from GitHub**.
The local choice uses file modification time (newest first), and excludes legacy wheels
without the `ultrazohm` console command. With no compatible local
wheel, it automatically downloads the newest published release for the selected
channel, verifies its SHA-256 checksum and saves it in that directory.

The channel defaults to `testing` on `feature/uz_cli26` and `stable` on all other
branches (including detached checkouts or when Git is unavailable). Override it
with `--channel stable` or `--channel testing`. The latest local wheel may come from either channel; the channel controls downloads. Drafts, other software releases
and releases from the other channel are ignored. If the newest release has no
compatible wheel, setup fails clearly instead of silently installing an older one.

For explicit selection or unattended setup:

```sh
./uz_cli/run.sh --latest --channel stable   # download even if local wheels exist
./uz_cli/run.sh --latest --channel testing
./uz_cli/run.sh --local-newest              # most recently modified compatible local CLI wheel
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
the fast/slow final Parquet files, optionally exports their CSV counterparts, and retains the indexed segments as the canonical recording. Wait for process exit and inspect `end.json` for
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
| `channel_mappings/default.json` | Firmware API version, mapping name, repository name/commit, packet geometry, observable/slow/variable/command IDs, platform-state mask/shift/names |

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

### Generate a mapping from the checkout

```sh
ultrazohm create-json-from-javascope-h
# Optional overrides:
ultrazohm create-json-from-javascope-h --repo /path/to/ultrazohm_sw --output my-mapping.json
```

The command works standalone and at the `ultrazohm>` prompt, including tab
completion. It finds the repository above the current directory and writes
`<repo>/artifacts/channel_mappings/javascope.json` by default, creating its parent
directories. An explicit `--output` path is relative to the current directory.
Re-running replaces the output after parsing and validation succeed.

It reads these repository paths:

- `vitis/software/Baremetal/src/include/javascope.h`: observable, slow-signal,
  and command enums, plus the commented `SND_FLD` names used by JavaScope.
  Send-field names become writable variable names mapped to `Set_Send_Field_N` IDs.
- `vitis/software/Baremetal/src/include/javascope_status.h`: platform-state mask
  and wire codes. Names come from `JAVASCOPE_PLATFORM_<NAME>`, lowercased.
- `vitis/software/shared/APU_RPU_shared.h`: `JS_CHANNELS`.
- `vitis/software/FreeRTOS/main.h` and `defines.h`: `NETWORK_SEND_FIELD_SIZE`
  and its referenced `JS_SAMPLES_PER_PACKET` constant.

Like JavaScope, header sections use one entry per line between the existing
zero/end markers. Inline comments and whitespace are removed; the commented
visualization block is intentionally read. Numeric enums honor explicit integer
assignments and implicit increments. Constants support decimal, hex, octal,
integer suffixes, `UINT32_C`, parentheses, and named constant aliases. This is
not a C preprocessor: unsupported expressions, missing/duplicate markers,
duplicate writable names, and unsupported wire geometry fail with an error
instead of silently producing a mapping. GUI-only units, button labels, and
receive-field layout are not part of the CLI mapping schema.

No Vitis, C compiler, Python parser, or Rust toolchain is needed at runtime.
Git is optional: provenance records HEAD and a `-dirty` suffix when the input
headers have local changes; without Git metadata it records `unknown`.

Load the result when starting a new service:

```sh
ultrazohm serve --interactive --channel-mapping artifacts/channel_mappings/javascope.json
```

Or pass that path as Python `Acquisition(channel_mapping=...)`. Generating JSON
inside a running shell does not change that service's active mapping. It also
does not replace the embedded default or change the runtime profile.

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

For embedded acquisition with the same defaults as bare `ultrazohm`:

```python
import ultrazohm

acquisition = ultrazohm.Acquisition()
uz = ultrazohm.Client()
uz.connect()       # 192.168.1.233:1000
uz.start_logging()
print(acquisition.output)
# Run your tests, then finalize all logs:
acquisition.close()
```

`Acquisition()` starts disconnected on `127.0.0.1:19740`, loads the embedded
profile and channel mapping, and prepares
`<repo>/artifacts/live_logs/<UTC timestamp>` (or beneath the current directory
when outside a checkout). Parent directories are created automatically. It
records Parquet and CSV by default, with ACKs and both loggers initially off.
The constructor returns only when the service is ready, so immediate `connect()`
and `start_logging()` calls need no startup polling. If a `device` is passed,
it also waits for that initial connection. Startup failures raise immediately;
`close()` waits for finalization and surfaces later runtime/logging errors.

For custom settings and guaranteed cleanup:

```python
import time
import ultrazohm

acquisition = ultrazohm.Acquisition(
    "127.0.0.1:1000", output="python-run", format="parquet",
    profile="my-profile.json", channel_mapping="my-channel-mapping.json",
)
try:
    uz = ultrazohm.Client()
    uz.set_observable("lifecheck", 1)
    uz.start_logging()
    time.sleep(2)
    uz.stop_logging()
finally:
    acquisition.close()
```

Python access to local build/flash/generation commands and optional Vitis tool
paths is tracked in the [roadmap](docs/architecture.md#todo-python-access-to-local-tooling).

### Live snapshots and completed recordings

The service retains recent fast-channel samples in RAM even when logging is off.
Python returns independent Polars DataFrames; the CLI prints the first 20 rows
and the total returned row count:

```sh
ultrazohm get-live-data --last-n-samples 500
```

The same command works at the interactive prompt (`get_live_data` is an alias).
Snapshots use the acquisition's nominal `time`, packet `status`, and canonical
observable names in channel order. Duplicate selected observables appear once.
They contain the fast channels, not the rotating slow-data updates. Float32
NaN/Inf values are preserved. Samples cross the local socket as binary Arrow IPC,
not per-value JSON. The Python package includes Polars as a runtime dependency.

```python
import ultrazohm

acquisition = ultrazohm.Acquisition(
    buffer_samples=100_000, segment_rows=50_000, flush_interval_ms=1000,
)
uz = ultrazohm.Client()
try:
    uz.connect()
    import time
    while uz.status()["buffer_available_samples"] < 500:
        time.sleep(0.05)
    df = uz.get_live_data(last_n_samples=500)
    uz.start_logging()
    time.sleep(1)  # Perform the measurement here.
finally:
    acquisition.close()

# Resolves this acquisition's files; no repeated output path is needed.
recorded = acquisition.read_recording()  # stream="fast", recording=1
# If slow logging or additional fast recordings were started:
# slow = acquisition.read_recording(stream="slow", recording=1)
# second = acquisition.read_recording(recording=2)
```

`get_live_data` requires a connection, a positive sample count, and enough
retained samples. Requests exceeding current availability fail with the available
count; they never silently truncate. An individual response is limited to 128 MiB,
including Arrow metadata. Old snapshots remain unchanged as acquisition continues.
Successful observable changes clear retained history to avoid relabeling it.
Firmware-buffered old values can still arrive afterward: selection is unconfirmed,
as with logging. This compatibility snapshot operation reads RAM only. The range API below also reads recording history. Pre-trigger capture and live subscriptions remain deferred. Samples that leave RAM while logging is off cannot be retrieved.

`read_recording` requires `close()` first and a completed backend index. It reads
through the recording backend and materializes the result, so large recordings must
fit in memory. For slow streams it now returns the original ID/value updates;
`recording_path(stream="slow")` still resolves the separate wide Parquet export. Never-started, missing, and failed recordings raise errors. Recording
numbers start at 1 and are independent for fast and slow streams.

Configure the service from the CLI with:

```sh
ultrazohm serve --buffer-samples 100000 --segment-rows 50000 --flush-interval-ms 1000
```

Defaults are 960 retained samples, a 1,000,000-row segment target, and a 60,000 ms
flush interval. At a sustained 10 kHz this normally produces about one 600,000-row
chunk per minute (60 files per hour per stream), instead of thousands of small files.
The row limit still bounds batches at higher rates. All values must be positive
and are fixed for the service lifetime.
The buffer retains whole frames internally, with at most one partial extra frame;
queries expose only the configured number of samples. Each logger flushes at the
row target or elapsed interval, rounded to complete frames, and resets its timer
after every flush. Queue and disk delays can extend commit latency. Each logger has
a separate bounded 2,048-frame queue (3.072 seconds at 10 kHz with 15-sample frames)
to absorb acquisition while a large chunk is encoded and synced. The live-history
buffer does not affect chunk size or logger queue capacity. These settings are
recorded in `run.json` and exposed as `status.data_options`;
`status.buffer_available_samples` reports current history.

Stopping logging or shutting down flushes a partial batch immediately. A process
crash can lose the current uncommitted interval plus pending writes, so choose a
shorter flush interval if a minute of buffered data is unacceptable. The example
above requests more frequent publication; both thresholds must be increased to
produce larger chunks. Range queries provide recording history independently of
these thresholds; pending samples remain readable before their chunk is committed.

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
    data_slow_data.parquet   # Slow: time, status, JSSD_ZEROVALUE, JSSD_FLOAT_..., ...
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
65,536 rows. The backend retains canonical segments and a `*.recording.json`
range index, including after successful export. The final Parquet/CSV files are
additional exports, so budget disk space for both. Existing index readers remain
valid during finalization. A failure retains committed chunks and published outputs. Canonical backend
completion precedes export; a failed optional export does not invalidate indexed
data, although the logging status and acquisition close still report that error.

`time` is the only time column: nominal seconds since **acquisition** started,
using the profile's configured sample period. It does not reset when a logger
starts, so separately started fast/slow recordings share the same time origin.
The internal sample counter is not exported. No `sample_index`, `time_s` or
`host_received_unix_ns` columns remain. `status` is still the packet's last-sample
status word, repeated across that packet; it is not a precise transition timestamp.

Slow segments contain raw rotating updates (`observable`, `slow_id`, `slow_raw`,
`slow_value`), including placeholder ID 0. During finalization they are converted
into a wide table: `time`, `status`, then one Float32 column per slow observable,
ordered by numeric slow ID and named using the full mapping name. Each update
sets that observable's value; subsequent rows hold its last received value, across
segment boundaries. Rows with any missing values are omitted after forward filling, so final output
starts only once every slow observable has been received in this recording. Values
are never backfilled from future updates or carried from a previous recording.
If any observable is never received, final slow output has no data rows. Received NaN/Inf
values are retained as values, rather than replaced by older finite values.

Final CSV is exported from this same wide Parquet table. The raw ID/value columns
are not included in final files. Recording metadata uses schema version 5 and
marks slow output as `wide_forward_filled`. A filled value may have been sampled
earlier than its row's `time`; the table is not a simultaneous slow-signal snapshot.
Fast output is unchanged. Because start/stop times are independent, fast/slow row
counts need not match. Overlapping rows can be aligned on `time`. Firmware gaps
and exact selection boundaries remain unknown.

```python
import polars as pl

# After status reports this recording complete, or acquisition.close() returns:
data = pl.read_parquet("measurement-001/data.parquet")
```

Shutdown and Python `Acquisition.close()` finalize all active recordings and wait
for finalizers already running. A sudden kill leaves complete segments recoverable
but does not automatically merge them. A `Recording` handle can read indexed,
committed ranges of an incomplete run; unindexed partial/orphan files are excluded.
Automatic repair is not implemented.
`run.json` contains session metadata; `commands.jsonl` audits host command events;
recording sidecars summarize individual files; `end.json` reports session health.
Existing recordings are not migrated. See [architecture.md](docs/architecture.md).

## Unified RAM and recording access

The existing Rust/Polars/TCP/Arrow stack now exposes a common range API. The only
registered recording backend is `parquet` (`--recording-backend parquet`, or Python
`recording_backend="parquet"`). Backend selection is separate from `--format`,
which controls the additional completed Parquet/CSV exports.

```python
from ultrazohm import Client, Recording

uz = Client()
recent = uz.tail(500)                         # Recent RAM, independent of logging
info = uz.data_info()                         # start/stop are absolute sample positions
# Enable logging first, then wait for data_info(recording=1)["stop"] to become non-null.
recorded = uz.data_info(recording=1)
if recorded["start"] is not None:
    df = uz.read_range(recorded["start"], recorded["stop"], recording=1)
page = uz.read_since(recording=1, limit=10000)
next_page = uz.read_since(page.cursor, limit=10000)
# Each page contains .data (Polars), .cursor, .start, .stop, and .info.
# Supply channels=["JSO_lifecheck"] to return that signal plus time/status.

# After acquisition.close(), the originating object provides the handle:
# handle = acquisition.recording(stream="fast", recording=1)
# df = acquisition.read_recording()            # Backend-independent convenience
# Or reopen the durable handle without a running service:
# handle = Recording("measurement-001/data.recording.json")
# for batch in handle.iter_batches(10000):
#     analyze(batch)
```

`recording=None` queries the bounded live ring; `recording=1`, `2`, etc. queries
that recording's complete history from its own start. Fast and slow numbering is
independent; `stream="slow"` exposes `time`, `status`, `observable`, `slow_id`,
`slow_raw`, and `slow_value`. Wide forward-filled slow tables remain separate
exports. `uz.recordings()` lists every recording in the acquisition.

Ranges are half-open `[start, stop)`. Indices count received samples since
connection, using the configured nominal period; they are not device sequence
numbers or proof of gap-free firmware delivery. No samples before logging started
are implicitly included. A recording's selected columns remain fixed even after
later live observable changes. Metadata reports `start`, `stop` (accepted),
`persisted_stop` (successfully indexed), `complete`, schema, and nominal timing.
Up to four background range queries run concurrently, leaving control requests
available during disk reads. A busy limit returns an explicit retryable error.
Published chunks and pending RAM are combined at one captured write boundary;
queries neither duplicate nor omit the overlap. The pending frame references are
bounded by the configured writer batch plus the bounded logger queue, independently
of the live ring. They share immutable payloads with the receiver and writers.

`read_since` starts at the earliest available position when no cursor is supplied.
Its opaque JSON cursor identifies the run, stream, recording and live mapping
generation. Reuse it unchanged. Empty pages preserve the position. Expired RAM
cursors, mismatched sources, unavailable ranges and unknown channels raise errors.
Each network response is limited to 128 MiB; page large requests. The durable
`Recording` reader reads only indexed data; use `Client` to include pending samples.

CLI equivalents print metadata and at most 20 preview rows:

```sh
ultrazohm data-info --recording 1
ultrazohm recordings
ultrazohm tail 500 --recording 1
ultrazohm read-range 1000 2000 --recording 1 --channels JSO_lifecheck
ultrazohm read-since --recording 1 --limit 10000
# Resume with --cursor '<cursor JSON from the previous reply>'.
```

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

- Release abi3 wheel built in the development container, installed with `run.sh`,
  and tested in its CPython 3.12 virtual environment.
- 24 Rust tests cover codec/storage, range indexing, publication failure,
  final exports, and injection of an alternate recording backend.
- 70 Python tests cover simulator communication, RAM/pending/disk history,
  cursor validation, independent recordings, completed handles, disk/export errors,
  CLI operations, and the existing build/mapping/release workflows.
- Connected UltraZohm tests through the `run.sh` interactive CLI verified a
  recording of over 30,000 samples with a 31-sample live ring, reads across chunk boundaries,
  concurrent history/status requests, slow updates, ACK policy, restarts, and
  readback after service exit. Embedded Python close/readback also passed.
- Rust formatting, strict Clippy with Python enabled, and `git diff --check` passed.
- Windows and ARM64 execution were not tested locally.

### Starting offline and connecting later

`serve` starts disconnected unless `--device IP:PORT` is supplied:

```sh
./uz_cli/run.sh                 # prepare uv environment and launch ultrazohm
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
then call `Client().connect()` immediately after construction. Passing
`device="192.168.1.233:1000"` to `Acquisition` retains immediate connection.
The launchers also support explicit `--launch cli` or `--launch example`.

### Default interactive session

Run `ultrazohm` (or `python -m ultrazohm`) without a command to open an interactive,
disconnected session. Without an explicit `--output`, sessions use
`artifacts/live_logs/YYYYMMDD-HHMMSS-NNNNNNNNNZ` at the repository root, found by
searching upward from the current directory. Outside a checkout, the current
directory is used as the base. Missing directories are created automatically.
The entire repo-level `artifacts/` directory is ignored by Git. The timestamp is
UTC with nanoseconds to avoid collisions.
In a terminal, press Tab to complete command names (including aliases), or press
Tab twice to list ambiguous matches. Up/Down recalls commands from the current
session. Completion applies to command names, not arguments or observable names.
Piped input remains supported without terminal editing.

The output path is printed at startup. Both Parquet and CSV are enabled, but
logging stays off until requested:

```text
ultrazohm> connect
ultrazohm> start-logging
ultrazohm> stop-logging
ultrazohm> shutdown
```

`serve` and `serve --interactive` use the same default output location when
`--output` is omitted; explicit output paths are used unchanged. `--endpoint ADDRESS` can also select the control endpoint for the
default session. The uv launch scripts start this default session after setup.

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
`build` and `flash` report `changes found, building` when work is needed, or
`no changes found` when both applications are up to date. Make checks source/header
dependencies with `make -q` before running build recipes. A missing build-state
stamp or changed workspace metadata takes the build path. Dependency-check errors
stop the operation. `flash` still programs the board after `no changes found`.
`build-clean` reports `clean build requested, building` and always rebuilds. Platform inputs/outputs,
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

Rust checks and release-wheel builds run in parallel. Check jobs use cached Rust
dependencies and a debug wheel for integration tests, avoiding a second optimized
wheel build. Release builds use Maturin's compiler cache. Publishing waits for both
platform check jobs and both tested release wheels; PRs and other branches run
only the check jobs. The first run populates the caches, so subsequent runs should
be faster. Cache misses still perform complete builds.

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

### Platform state feedback

`uz.status()["state"]["platform_state"]` (also in CLI `status`) reports `idle`,
`running` (system enabled), `control` (control enabled), or `error` from status
bits 31:30. The decoder reads the mask, shift, and names from the active channel
mapping's required `platform_state` object (shown below), rather than hard-coding
the names in Rust. Existing custom mapping files must add this object.
It is `None`/JSON null before reception and after disconnection.

```json
"platform_state": {
  "mask": 3221225472,
  "shift": 30,
  "values": {"0": "idle", "1": "running", "2": "control", "3": "error"}
}
```

The mask is `0xC0000000` written as a decimal JSON integer. State codes are
`(status & mask) >> shift`; `values` must contain a nonempty name for each code
0 through 3. The mask must select two bits at `shift` (0 through 30).
Use `--channel-mapping PATH` or Python `Acquisition(channel_mapping=PATH)` to
select a custom mapping. `ultrazohm channel-mapping` exports the embedded default.

```python
state = uz.status()["state"]["platform_state"]  # e.g. "running"
```

This is the latest received platform state, independent of blinking LED bits;
it is not an acknowledgment of a sent command. The raw `status` is retained in
status responses and recordings. See [protocol.md](docs/protocol.md#signals-and-status).
