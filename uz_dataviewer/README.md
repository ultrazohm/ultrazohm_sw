# UltraZohm Data Viewer (`uz_dataviewer`)

A native/web data viewer for UltraZohm JavaScope logs, built with
[Dear ImGui via `imgui_bundle`](https://github.com/pthom/imgui_bundle) and ImPlot.
It succeeds the Plotly/Dash `javascope/dataviewer.py`, with a native live-data prototype and a VSCode-style
docked layout, drag-and-drop subplots, dedicated FFT/Histogram analysis windows, range-aware
downsampling for multi-gigabyte logs, and a **scriptable command console** for automating data, analysis and plot settings.

```
+------------------------------------------------------------------+
|  Navigation  |      Plots / FFT / Histogram  (docked tabs)       |
|   (left)     |   Plots: runtime grid of subplots (1x1 ... 2x2)   |
|  runs &      |   FFT / Histogram: dedicated analysis windows     |
|  signals     |                                                   |
|--------------+---------------------------------------------------|
|                       Console  (bottom)                          |
+------------------------------------------------------------------+
```

## Features at a glance

- **Load many files** — `.csv` (JavaScope `;` *or* standard `,`, auto-detected) and
  `.parquet`, read with Apache Arrow. Open via the button or **drag files onto the window**
  (desktop).
- **Matlab-style navigation** — runs → channels, (de)activate/remove, **per-log time
  normalization**.
- **Subplot grid** — drag-and-drop signals, runtime layout, types line/scatter/stairs/**XY**,
  **linked X axes**, **secondary Y axis**, **cursors**, **spy** zoom inset, **show samples**,
  per-cell **CSV export**.
- **Range-aware downsampling** — a min/max pyramid (pure NumPy) for time series; multi-GB logs
  pan at full fps and zoom reveals detail. (XY plots decimate by plain stride.)
- **FFT & Histogram windows** — overlay several signals, pick the time window
  (follow a plot / full / custom), compute on demand, log axes, CSV export.
- **Node canvas** — drag a signal into a graph, apply transforms (FFT / math /
  filter / shift), and the result becomes a new draggable signal. Fully scriptable
  (`node_*`) and extensible with your own **Python plugin nodes** (see [Plugins](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_plugins.rst)).
- **Scriptable command console** — supported actions echo commands; the input runs them, with
  completion, history and a selectable log. Sessions save to JSON; `.uzscript` files run command automation.
- **MaterialFlat theme.** Runs natively (Windows/Linux/macOS) and in the browser (Pyodide/WASM).

## Quick start

Run the launcher from the repository root (Linux/macOS):

```bash
./uz_dataviewer/start.sh
./uz_dataviewer/start.sh --use-live          # set up CLI backend, then open viewer
./uz_dataviewer/start.sh path/to/log.csv    # preload one or more files
./uz_dataviewer/start.sh session.json       # restore a saved session
```

Ordinary startup shows the offline workspace, even if the CLI wheel is already
installed. Pass `--use-live` (or `--live-wheel PATH` / `--live-channel CHANNEL`)
to include Live Data, Live Plots, Control, and Python. The Python entry point and
installed `uz-dataviewer` command also accept `--use-live` to enable those panels.

On Windows, use PowerShell:

```powershell
.\uz_dataviewer\start.ps1
.\uz_dataviewer\start.ps1 --use-live
.\uz_dataviewer\start.ps1 "path\to\log.csv"
```

If Windows blocks script execution, run `powershell -ExecutionPolicy Bypass -File .\uz_dataviewer\start.ps1`.
Both launchers automatically install missing uv using the [official installer](https://docs.astral.sh/uv/reference/installer/), without modifying shell profiles.
Linux/macOS requires `curl` or `wget` for this initial download.
The launchers use `uv run` to create/reuse `uz_dataviewer/.venv`, install the project and all runtime dependencies from `pyproject.toml`, and start the viewer.
It selects Python 3.12 (downloaded by uv if needed) and requires a prebuilt
`imgui-bundle` wheel, avoiding an accidental native build with Python 3.10.
An existing `.venv` using another Python version is recreated by uv.
The first run needs internet access and uses the included `uz_dataviewer/uv.lock`.
No manual virtual environment activation is needed. Input paths are relative to
your current directory; the launcher itself can be called from any directory.
Startup files are processed in argument order, so a script can use recordings
listed before it. A failed startup argument stops the remaining arguments and
reports the error in the console.

Alternatively, install and run manually from `uz_dataviewer/`:

```bash
pip install -r requirements.txt      # or: pip install -e .
python run.py                        # or: python -m uz_dataviewer
python run.py ../javascope/Log_2026-06-11_22-45-16.csv   # preload
python run.py session.json           # restore a saved session
```

On desktop, selecting a CSV larger than 1 GiB prompts **Large log, conversion to parquet recommended**.
Choose **Open CSV** to read it directly, or **Convert to Parquet** to create and open a file with the same stem and directory (for example, `logs/run.csv` becomes `logs/run.parquet`).
This applies to native drag-and-drop, the Log Browser and the file picker.
Conversion runs in the background using the selected backend and opens the result with the selected loading mode.
The original CSV is preserved; an existing Parquet file is never overwritten and can instead be opened explicitly.
Choosing **Open CSV** skips automatic disk-cache conversion for that load, even when disk caching is enabled.
Console/API conversion follows the same safety policy: existing destinations are
never overwritten, empty recordings are rejected, and failed or cancelled
conversions clean up temporary output.

Then **Open file(s)…** in the Navigation panel, expand the run, and drag signals into the
plots (or the FFT / Histogram windows).

## Large recordings and responsiveness

The desktop defaults to **Polars + Lazy**; the online version uses **PyArrow + In memory**.
Choose **Loading → In memory / Lazy** on the bottom status bar before opening files,
or select the mode at startup:

```bash
./uz_dataviewer/start.sh --loading-mode lazy path/to/log.parquet
./uz_dataviewer/start.sh --loading-mode lazy path/to/log.csv
```

- **In memory** retains the existing full NumPy arrays for fast analysis.
- **Lazy** (desktop default) reads selected columns and sample ranges from Parquet or streams CSV directly.
  CSV requires repeated text scanning and is slower for interactive navigation.

The setting affects subsequent opens. Existing runs retain their storage mode;
JSON sessions preserve mixed modes. The console equivalents
are `loading_mode(lazy)` and `cache_budget(1024)`.

Plot preparation, first-use summaries, XY sampling, cursor reads, and GUI FFT /
histogram computation run outside the desktop rendering thread. During an update,
the last completed plot remains visible with an **Updating plots...** indicator.
Superseded display requests are cancelled or discarded. Main and spy plots reuse
completed results, and finite display-point budgets account for pixel width and
trace count. Gap markers may add points beyond the finite-point budget.

Parquet opens use footer statistics when available. The first sample query
validates timestamp order and builds a persistent timestamp index; files without
usable statistics need that scan during opening. First display of a channel
builds its persistent min/max summaries. These operations stream through the
file and can take seconds for large recordings. Reopening reuses valid indexes.
Changed files must be reopened; cached results from their previous version are
not reused, including in XY plots and cursor readouts. Lazy reads run on the desktop worker even for short recordings.

The shared timestamp/summary RAM cache defaults to 1,024 MiB and is configurable
with **Cache (MiB)** on the bottom status bar. Prepared plot arrays are bounded by display budgets.
Cache limits are **not a hard process-RAM limit**: decoded batches, index-building
scratch, FFTs, explicit NumPy conversions, exports and Python transformation
plugins can allocate additional memory. A full-recording FFT still needs its raw
input and output arrays. Histograms stream raw batches in two passes. Explicit
console/script commands and node/plugin evaluation retain synchronous semantics.

Measurement caches stay in RAM by default; no automatic CSV conversion is written.
Enable **Disk cache** on the bottom status bar, pass `--disk-cache`, or use `disk_cache(true)` to persist indexes and summaries and convert lazy CSV inputs into reusable Parquet files.
Reopen existing files to change their cache policy.
JSON sessions preserve the setting for each file.
When enabled, disk caches live in `~/.cache/uz_dataviewer` (Polars uses its `polars/` subdirectory), or the directory selected by `UZ_DATAVIEWER_CACHE`.
They are disposable and source-versioned; close the viewer before clearing that directory.
Disabling disk caching leaves existing cache files untouched and does not read them.
There is currently no automatic disk-cache size limit.
Read-only or full summary-cache storage falls back to RAM; enabled lazy CSV conversion requires writable cache space.
The browser build retains synchronous execution because its current runtime has no worker-thread support.
Browser uploads with backing files honor the same loading and cache settings as console loads.
Browser file caches live in the tab's temporary filesystem and are cleared on page reload; large streamed CSVs remain array-backed. Streamed CSVs preserve every sample and reject estimated or actual numeric data above the 1.5 GiB budget. Use native lazy loading for larger recordings; load-time stride decimation has been removed.

### Session format and analysis correctness

Sessions now use schema version 5 with explicit run identities, including repeated opens and identical filenames in different directories.
Node links preserve explicit input slots, including disconnected slots. Canvas connection order does not change subtraction or division.
Restoring a saved session replaces the current session only after successful loading. Failed restoration leaves the current session intact. Version 1–4 snapshots and generated session scripts must be recreated as JSON sessions; version 5 records the materialized output domain explicitly.
Plot windows, precise time ranges and inactive recordings survive JSON round trips. Restoring a session resets panel caches and canvas positions; Y fitting completes when lazy samples arrive. Both primary and secondary Y limits survive JSON saves, including mouse zoom.
Removing a followed subplot switches its analysis windows to Full and discards the removed plot's cached range.
Recomputing a node preserves its derived recording's selected time origin.
Small browser uploads use separate backing paths even when filenames match. Failed exports never download an earlier result.
Streamed browser recordings have no backing file, so session saving is rejected; export their data first.
Chain transforms with node links; using derived outputs as new source nodes is no longer supported.
Analysis and exports use exact time windows, while plotting retains edge padding. Full analysis covers all selected recordings regardless of selection order.
Linked time ranges apply immediately to scripts, exports and analysis, including
before the first GUI frame. Reset view updates the linked range to the selected
plot's recording extent. FFT inputs must be equal-length one-dimensional arrays.
FFT and FIR filters reject duplicate or irregular timestamps. JavaScope logs identified by
raw `CHn=n)` headers use their 10 ns timestamp resolution: samples must fit one uniform
grid within ±5 ns plus floating-point roundoff. This also applies after conversion to
Parquet and time normalization. Other inputs retain the 100 ppm interval tolerance.
For plain-array API calls, pass `timestamp_resolution=data.timestamp_resolution` from
`data = uz.read(path)` to `uz.fft(...)` or `uz.filter(...)`; the default is unspecified
precision, not an assumed JavaScope format. No samples are resampled.
Binary math and XY plots require matching timestamps throughout both inputs; implicit index alignment and XY truncation have been removed. XY limits and zoom survive session round trips without changing linked time axes.
Stale or failed derived outputs are blocked from plots, analysis and exports until successful reevaluation; existing assignments are preserved, including across JSON restoration. Failed graphs restore with empty, unavailable output placeholders until repaired. Source validation covers original CSV files even when reading a cached conversion.
JSON is the only saved-session format; generated session-script export has been removed. Ordinary `.uzscript` automation remains supported and can call `load_state("session.json")`; commands run sequentially and stop at the first error. Completing an export dialog after its subplot was removed cancels the export.
FFT export validates every selected signal before writing: an invalid channel fails the export with its name and reason, preserving any existing destination file.
The FFT window reports each failed channel even when other channels succeed.
Plugin imports roll back their registrations on failure. Existing transform kinds
cannot be replaced at runtime; restart the viewer after editing a loaded plugin.

Division and reciprocal transforms preserve undefined samples as NaN gaps; FFTs
reject those inputs rather than treating undefined values as zero. Numeric node
parameters must be finite, and integer parameters must fit a 32-bit integer.
Built-in and plugin parameter editors use the same declared types as validation.
Removing a recording immediately invalidates its analysis results. Explicit
FFT/histogram X limits survive recomputation; Reset view clears those limits.
These explicit analysis view limits also survive JSON session restoration.
Shared upstream nodes are validated once per traversal, avoiding exponential
work in graphs with reused inputs. Hann windows are released after each FFT.
Native CSV materialization uses checked batch allocation for both backends,
including actual row counts and retained buffer capacity. Parser scratch and
transient growth copies remain outside the numeric-data budget. Native and
browser CSV loaders share missing-value spellings (including NA, NULL and NaN).

Session restoration rejects malformed coordinates, unknown plot types/styles, and
invalid numeric settings before replacing the current session. Commands use the
same bounds: 1–100,000 histogram bins, 1–16 rows/columns, 2–1,000,000 display
points, and 1–1,048,576 MiB of cache. Mouse zoom in analysis windows persists
through recomputation and JSON restoration. FFT display sampling, including
summary rebuilds after cache eviction, runs on a desktop worker.
Headless reads, conversions, and analysis do not import the GUI. Import GUI entry
points explicitly from `uz_dataviewer.app`; package-root GUI aliases were removed.

## Documentation

| Doc | For |
|-----|-----|
| **[Usage](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_usage.rst)** | Driving the app: panels, plots, analysis windows, the command console & scripting, full command reference. |
| **[Architecture](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_architecture.rst)** | Developers: module map, the state-driven/command-routed design, internals, how to extend, testing, design decisions. |
| **[Build](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_build.rst)** | Building native executables and the web/WASM app. |
| **[Native Vs Web](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_native_vs_web.rst)** | What differs between the desktop and browser builds (file I/O, threading, memory) and what's identical. |
| **[Plugins](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_plugins.rst)** | Writing your own node transforms as Python plugins. |
| **[Library](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_library.rst)** | Using the data/analysis core headlessly as a Python library (load logs, FFT, node transforms) — no GUI. |
| **[Roadmap](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_roadmap.rst)** | Open ideas and the record of what's already shipped. |
| **[Dataviewer V Javascope](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer.rst)** | How the live JavaScope and this offline viewer relate, and the legacy `dataviewer.py` it succeeds. |

## Project layout

```
uz_dataviewer/
├── run.py                    # run from a source checkout (also replays *.uzscript)
├── src/uz_dataviewer/
│   ├── app.py                # docking layout, runner, theme, Session menu
│   ├── state.py              # AppState, SubplotCell, FFT/Histogram configs
│   ├── commands.py           # command registry / parser / dispatcher (the script API)
│   ├── console.py            # console: selectable log + command input
│   ├── model.py              # Run / Signal / DataRegistry (+ time normalization)
│   ├── loader.py             # CSV/Parquet loading + channel-name parsing
│   ├── sources.py            # raw sources, bounded caches and min/max summaries
│   ├── downsample.py         # visible-window selection and display adapter
│   ├── analysis.py           # GUI-free transforms (FFT)
│   ├── transforms.py         # GUI-free node transforms (math, FIR filter)
│   ├── nodes.py              # dataflow graph + evaluation -> derived signals
│   ├── plugins.py            # external transform-node plugins (@transform, loader)
│   ├── session.py            # JSON save/restore + .uzscript + CSV export
│   ├── webbridge.py          # browser integration (file input, array load, downloads)
│   └── panels/               # navigation, plots, analysis base, fft, histogram, nodes
├── tests/                    # pytest (logic via commands + headless rendering)
└── build/                    # native (PyInstaller) + web (Pyodide) build flow
```

Documentation lives in `../docs/source/guide/gui/uz_dataviewer/`.

## Tests

```bash
pip install pytest
pytest
```

The console transcript does not capture every GUI gesture (including analysis
Reset view and some Y/XY gestures). Use JSON snapshots for supported view settings.
FFT-derived plots use Hz, remain independent of linked time axes, and export a
`frequency` column. Time normalization and time-based analysis reject spectra.

Browser uploads are temporary and cannot be saved as reloadable sessions.
Memory imports release the uploaded file after parsing; lazy imports release it
when the last referencing run is removed or the session closes.

Sampling and domain transitions
------------------------------

Timestamp roundoff allowances are bounded to one percent of a sample interval.
FFT and FIR reject axes whose absolute timestamp precision cannot establish that
bound; binary math and XY never treat a sample-sized displacement as roundoff.
Graph domain resolution shares a per-evaluation cache and uses iterative traversal.
When a saved graph changes an output's domain, restoration discards its incompatible
normalization and consumer assignments, matching live reevaluation. Failed outputs
retain their saved domain as unavailable placeholders until repaired.

## Native live-data prototype

### Debug CLI in the Console

With live mode enabled, enter `uz` followed by CLI arguments in the existing
Console:

```text
uz --help
uz status
uz set-variable send_field_19 5
uz start-logging
uz build
uz flash
```

Only the exact first token `uz` bypasses the viewer command parser. The installed
CLI handles parsing, validation, and help, so all its commands are available.
Each invocation runs asynchronously in the viewer's Python environment; stdout
and stderr appear incrementally in the Console with a command number and exit
status. Up to four invocations can run concurrently. Bare `uz` shows CLI help.
Without live mode or the CLI wheel, the Console reports **Live is not activated.**

Service commands use the attached endpoint (or the endpoint entered in Live Data
when detached); an explicit CLI `--endpoint` overrides this default. Local commands
inherit the viewer's working directory and environment, including Vitis/XSCT on
PATH. Use `--repo` on commands that need a different checkout. Quoted paths are
supported. This is a noninteractive CLI interface with no shell expansion or
shell operators.

These are direct debug invocations, including while GUI controls are locked by
a Python script. `flash` runs as entered and may disconnect the viewer; it does
not coordinate recording finalization, shutdown, or reconnection. CLI processes
continue if the viewer closes, with active output files retained in a temporary
`uz-cli-console-*` directory. The regular viewer console commands remain available
without the `uz` prefix.

### Python measurement scripts

The native source launcher with `--use-live` includes a **Python** window beside
Live Plots. **Open Python file…** opens a native file picker. **Save** writes the
current file; **Save as…** chooses a new filename. **Choose template** opens the
built-in template list and loads the selection as an unsaved script. The editor
shows only the filename or “Unsaved script”; full paths stay internal.

Connect in Live Data, then press **Run** to save and execute the script in a
separate Python process using the viewer's environment. Unsaved scripts first
open a save dialog. Cancelling that dialog leaves the editor unchanged and does
not execute code. File dialogs are polled without blocking live plots.

Run launches an ordinary Python script with the attached service endpoint:

```bash
python measurement.py --endpoint 127.0.0.1:19740
```

The same file works unchanged from an activated terminal. The viewer does not
inject variables or call a special function. Templates include explicit imports,
argument parsing, and Client construction:

```python
import argparse
import time
from ultrazohm import Client

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--endpoint", default="127.0.0.1:19740")
    uz = Client(parser.parse_args().endpoint)
    uz.set_variable("send_field_1", 0.0)
    uz.start_logging()
    time.sleep(10)
    uz.stop_logging()
```

Each Run uses a fresh process in the existing viewer virtual environment, not a
new environment. The script receives `--endpoint HOST:PORT` and should parse it
if it needs device access. `__name__`, `__file__`, arguments, imports beside the
script, and exit codes follow ordinary script conventions. On Windows a minimal
bootstrap establishes the child-process job before executing the script as
`__main__`; it does not import the CLI or inject a Client.

Existing files that only define `run(uz)` need an explicit entry point (parse
`--endpoint`, create `Client`, then call `run(uz)`). Saved user files are not
rewritten automatically. Terminal execution does not lock viewer controls or
provide its Stop button/process cleanup.

Use `uz.enable_system()`, `uz.enable_control()`, `uz.stop()`, and the other Client
methods for device commands. Commands have no firmware acknowledgment: sequences
requiring state confirmation must check `uz.status()` before proceeding. Stopping
logging starts finalization; check its phase in `uz.status()['logging']` if the
script needs a completed file before continuing.

Scripts can import helper modules beside their file and packages installed in the
viewer environment. The window shows output and Python tracebacks (the most recent
64 KiB). The ImGuiColorTextEdit editor provides Python syntax highlighting, line
numbers, four-space indentation, matching brackets, and undo/redo. It becomes
read-only during execution. This prototype does not include an interactive REPL
or package management. Frozen executables
do not support script execution; use `start.sh --use-live` / `start.ps1 --use-live`.

While a script runs, manual connection, assignment, logging, and device controls
are locked in this viewer; plots remain interactive. **Stop script + device** in
Python and **Stop** in Control terminate the script process before independently
sending device Stop. Logging remains enabled. Normal completion and errors leave
device and logging state as the script left them, then restore manual controls.
Stop discards pending GUI commands and waits for an in-flight control command
before sending device Stop. Closing a connected viewer sends Stop, including when
no script is running; an active script is terminated first. The acquisition
service and logging continue when the service was started externally. When the
viewer started the service, closing the viewer requests shutdown and waits for
recordings to finalize and the service to exit, even if the viewer was detached.
Other CLI clients are not locked.

### Starting acquisition

Enable live support using the same wheel selection/download flow as `uz_cli`:

```bash
./uz_dataviewer/start.sh --use-live
```

```powershell
.\uz_dataviewer\start.ps1 --use-live
```

The launcher installs the locked viewer dependencies, then calls `uz_cli/run.sh`
or `run.ps1` in setup-only mode, targeting `uz_dataviewer/.venv`. It offers the
CLI's local-wheel menu when compatible local wheels exist, or downloads the latest
release when none exist. No Rust compiler is needed for prebuilt wheels. The CLI
launcher does not start an interactive CLI or connect to hardware; the viewer
opens afterward and **Connect** starts acquisition; **Existing service → Attach** reuses an existing service. Relative
recording arguments keep their original working directory.

Each live startup then calls the installed CLI's `create-json-from-javascope-h`
command against the checkout's current JavaScope headers. It stores a fresh JSON
in `<repo>/artifacts/channel_mappings/`, named
`javascope_<UTC timestamp>_<repository commit>.json`. The commit is taken from the
generated metadata and includes `-dirty` when the relevant headers have local
changes. These cache files are ignored by Git. Header parsing failures stop startup
with an error. Offline startup does not generate a mapping.

The cached path is prefilled in **Live Data → Service settings → Channel mapping
JSON** and passed to services launched by the viewer. An existing service keeps
its loaded configuration; Connect/Attach reports a notice when its mapping differs
from the selected file. Use Shutdown service and reconnect to apply the new map.
Both launchers pass their checkout root, so this also works from another working
directory. With a manually installed viewer, use `--use-live --live-repo PATH`
when the repository cannot be discovered from the current directory or source tree.

The release channel follows the CLI default. Override it with
`--use-live --live-channel testing` (or `stable`). A published wheel must contain
the live-viewer APIs; incompatible older wheels fail during setup with an error.
For unpublished prototype changes, build a matching wheel in the development
container and use `--live-wheel` to select it explicitly. That flag also enables
live setup, so `--use-live` is optional with an exact wheel:

```bash
./uz_dataviewer/start.sh --live-wheel /absolute/path/to/ultrazohm-....whl
```

```powershell
.\uz_dataviewer\start.ps1 --live-wheel C:\path\to\ultrazohm-....whl
```

Use a wheel built with the `catalog` API. Offline viewing works without the wheel;
live panels are only created when explicitly enabled. Live acquisition is native
only; the browser cannot connect to the local CLI socket.

**Flash UZ**, beside Connect/Disconnect, opens an **OK / Cancel** confirmation.
The button is greyed out when Vitis XSCT is missing from PATH, with a tooltip
explaining how to load the Vitis environment and restart the viewer. Availability
is also checked again before any device or logging changes.
OK sends device Stop, stops active fast and slow logging and waits for completed
files, shuts down the service, regenerates the header mapping, and runs the CLI's
build/program operation. Progress and tool output appear in the Console while
the GUI stays responsive. After success, a fresh acquisition session starts and
connects to the device. Logging is idle and system/control remain in the firmware
startup state. Cancel makes no changes. If no service is running, programming can
start directly. A Python script or active debug CLI jobs disable the flash button;
the workflow locks device controls, script execution, and debug CLI submissions.

Managed flashing uses `artifacts/channel_mappings/javascope_<commit>.json`, including
`-dirty` when applicable, and regenerates/replaces that cache on every attempt.
Startup's timestamped caches remain available. The prototype assumes headers stay
unchanged during build/programming, as agreed; no checksum check is performed.
The restarted service loads the new JSON, keeps existing channel assignments
whose names remain available, and reports removed names. Sampling period, buffer,
flush settings, and ACK policy are preserved when restarting an existing service.
Existing recordings retain their original data and mapping. Errors stop later
steps and appear in the Console; retries retain the captured service settings.
If the viewer closes during programming, the CLI finishes independently and the
viewer does not start a replacement service afterward.

- **Live Data** sits beside Navigation. **Connect** starts a service at the selected endpoint
  and connects it to the device. **Existing service → Attach** attaches to an
  already running service without changing its device connection. An
  existing service owns its settings; session directory and channel mapping fields
  apply only when launching a new service. The session directory must not exist.
  A sibling `<session>.service.log` contains service startup diagnostics.
  Connection progress appears immediately above the controls, followed by a
  connected/data-reception indicator or an error. Progress and results also appear
  in the Console; connection buttons stay disabled while a request is pending.
- The 20 channel slots show the service's requested assignments. Double-click a slot
  to choose an observable using case-insensitive fuzzy search. Selection is blocked
  while either stream is recording. A mapping/reconnect generation change clears
  live plot assignments and cached samples; drag the desired signals again.
- Drag channels into **Live Plots**. This reuses the normal plot renderer, grid,
  zooming and display downsampling, with independent live axes and drag targets.
  **Follow live** anchors the right edge at the newest sample. Mouse-wheel zoom
  changes X and Y like the ordinary Plots window; X zoom updates **Time depth (s)**.
  Live Plots uses exactly the ordinary Plots window's ImPlot mouse mapping, including
  its pan/box-selection buttons and modifier-based axis constraints; it does not
  remap buttons. Ordinary wheel and box zoom keep following: their X span becomes
  the time depth and the right edge returns to the newest samples. **Shift-modified
  zoom** enters **Inspect** and keeps the selected region, freezing the current
  bounded RAM snapshot while acquisition and logging continue. Panning also enters
  Inspect. The slider controls the same X duration. Inspect has a button (or uncheck
  Follow live).
  In Inspect, normal cursor-centered zoom and pan work; the slider changes duration
  around the current view's center. **Resume live** catches up to the newest samples
  at the chosen duration. No disk/cloud history is fetched in either mode.
- **Freeze plot 1 for analysis** copies all channels in that plot's time window to
  Navigation and assigns its plotted signals to the normal Plots window. FFT,
  histogram and nodes can then consume stable samples. Snapshots are memory-only;
  export them if needed before closing the viewer.
- **Control** exposes Enable System, Enable Control, device Stop, user buttons 1–8,
  and a scrollable variable table populated from the service's JSON mapping. Each
  row retains its own entered value; press **Enter** in that input to send it.
  A successful send highlights that value blue for 0.2 seconds.
  Editing, leaving a field, and filtering do not send commands. The filter narrows
  the table; rows follow command-ID order. Entered values are local, not device
  readbacks, and inputs are disabled while a Python script runs. Commands are sent
  without firmware acknowledgment; streamed platform state is shown separately.
  Error Reset is omitted because current firmware does not implement it.
- Fast and slow logging have independent Start/Stop controls and phase/error/path
  indicators. **Open completed log** opens the final Parquet through the ordinary
  lazy file workflow. Stopping logging does not stop acquisition or the device.
- **Existing service → Detach** leaves the service and logging running. Closing
  the viewer shuts down a viewer-started service; for an external service it sends
  device Stop and leaves logging running.
  **Disconnect** and **Existing service → Shutdown** send device Stop, ends acquisition, finalizes logs, and exits the service.
  An external CLI can attach to the same endpoint throughout.

The IO worker uses `Client.read_since()` at up to 30 Hz and retains at most the
service's configured sample capacity. Each publication is an immutable NumPy-backed
snapshot; plotting work uses the existing background request scheduler and visible
window min/max decimation. The GUI does not read intermediate recording files.
The default ring covers 30 seconds at the configured sample rate (300,000 samples
at 10 kHz; 3,000,000 at 100 kHz). The slider's maximum automatically follows the
service capacity times its configured sample period, not a measured wall clock.
Your selected time depth is preserved and clamped when needed. The plot shows
only the samples received so far while the buffer fills. Requests are paged
independently of buffer capacity to respect the CLI response-size limit.
Stale data, backend errors and cursor resynchronization are shown in the UI.

Prototype limits: live history is RAM-bounded even while logging. Full recording
history during acquisition and cloud access are future adapters using the same
source/query boundary. Live windows/settings are not saved in offline sessions;
analysis runs only on explicit frozen snapshots. Session times follow the CLI's
nominal sampling clock; transport gaps cannot currently be reconstructed.

GUI plot, FFT, and histogram exports run in the background using captured settings.
The Console reports completion or failure; one export per workspace runs at a time.
Closing the workspace cancels publication of an unfinished export.
Measurement-script completion terminates remaining child processes in its process group
(on Windows, its job object) before manual controls are restored.

The Python panel starts hidden in live mode; open it with **View → Python**.
GUI `.uzscript` replay yields between commands and waits for each background
export before running dependent commands. An export failure aborts the replay.
Startup command-line scripts still execute sequentially before the GUI opens.

**Connect** starts a viewer-managed service and connects to the selected device IP.
If an external service already occupies that endpoint, use **Existing service →
Attach**. **Disconnect** sends shutdown (device Stop, recording finalization, and
service exit) and leaves the GUI open. For a viewer-started service it waits for
process exit before enabling Connect again. Each subsequent connection uses a
fresh recording directory. The **Existing service** section contains Attach,
Detach (viewer only), and Shutdown; Disconnect also shuts down an attached external
service, whereas closing the GUI retains the external-service ownership policy.

To open an activated DataViewer environment without launching the GUI or a service:

```bash
./uz_dataviewer/start.sh --launch shell
# Also set up live dependencies if needed:
./uz_dataviewer/start.sh --use-live --launch shell
```

PowerShell supports the same options through `start.ps1`. Existing optional CLI
packages are preserved in shell mode. Run `python measurement.py` or
`ultrazohm status` (when the CLI wheel is installed). Type `deactivate` to deactivate
within the child shell, or `exit` to return to the original terminal.
The CLI equivalent is `./uz_cli/run.sh --local-newest --launch shell`
(`run.ps1` on Windows).

### Combined desktop distribution

Extract the entire release archive and launch `uz_dataviewer/uz_dataviewer`
(or `uz_dataviewer.exe` inside that folder on Windows). Keep `_internal` beside
it. Python and uv are bundled; Vitis is not. Select the `ultrazohm_sw` workspace
at startup, or pass `--live-repo PATH`. All available windows except Python open at startup; Navigation, Plots and Log
Browser are selected. Mode selects Analysis or Live tabs without closing other
windows. Use View to open Python or toggle individual windows. Source launchers retain
`--use-live` for installing the CLI wheel; all available windows except Python start open, with Analysis tabs selected.

The source and packaged applications use the same CLI and script worker logic.
Scripts execute as ordinary `__main__` files with `--endpoint`, with no injected
client. Source scripts use the venv's modules; packaged scripts use bundled
modules. Additional dependencies can be used in an external venv with a matching
CLI wheel attached to the service. Such scripts are not terminated by GUI Stop.

Default recording directories and GUI layout settings are stored under
the selected workspace’s `artifacts` directory: `live_logs/` for recordings,
`viewer.ini` for layout settings and `viewer_cache/` for optional data caches.
Generated mapping JSON files are in `artifacts/channel_mappings/`. Explicit
output paths and `UZ_DATAVIEWER_CACHE` still override their respective defaults.

To build the combined application, set `UZ_CLI_WHEEL` to the absolute path of a
wheel built from the same commit, then run `build/build_native.sh` or its
PowerShell equivalent. Build scripts synchronize locked dependencies before
installing that wheel. CI builds both OS wheels, packages folder distributions,
and tests frozen workers against the JavaScope simulator. Integration-branch
releases are prereleases; main releases are stable. Browser builds remain separate.
