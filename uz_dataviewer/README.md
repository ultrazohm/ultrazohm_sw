# UltraZohm Data Viewer (`uz_dataviewer`)

A desktop data viewer (Windows and Linux) for UltraZohm JavaScope logs, built with
[Dear ImGui via `imgui_bundle`](https://github.com/pthom/imgui_bundle) and ImPlot.
It succeeds the Plotly/Dash `javascope/dataviewer.py`, with a native live-data prototype and a VSCode-style
docked layout, drag-and-drop subplots, dedicated FFT/Histogram analysis windows, range-aware
downsampling for multi-gigabyte logs, and a **Python and terminal control API** for automating data, analysis and plot settings.

```
+------------------------------------------------------------------+
|  Navigation  |      Plots / FFT / Histogram  (docked tabs)         |
|  runs &      |   Plots: runtime grid of subplots (1x1 ... 5x5)    |
|  signals     |   FFT / Histogram: dedicated analysis windows     |
|--------------|                                                   |
| Log Browser  |                                                   |
| / Console    |                                                   |
+------------------------------------------------------------------+
```

Log Browser and Console share the lower-left dock; Log Browser is selected at startup.
On Windows and Linux sessions identified as X11 (`XDG_SESSION_TYPE=x11`),
drag a panel's tab outside the main window to detach it into a desktop window.
Drag it back to redock. Other environments keep panels inside the main window.
**View → New plot window** opens an additional empty grid. Its signal assignments,
axis ranges, cursors and downsampling settings are independent; recordings and
their data cache are shared. Hide and reopen these windows using View.
Additional plot windows last for the current session: loading a session closes
them, and saved sessions preserve their independent grids. Their actions appear as labelled informational messages in the console.

## Features at a glance

- **Load many files** — `.csv` (JavaScope `;` *or* standard `,`, auto-detected) and
  `.parquet`, read with Apache Arrow. Open via the button or **drag files onto the window**
  (desktop).
- **Matlab-style navigation** — runs → channels, (de)activate/remove, **per-log time
  normalization**.
- **Subplot grid** — independent **Rows** and **Columns** sliders (1–5), draggable
  dividers, drag-and-drop signals, types line/scatter/stairs/**XY**, **linked X axes**
  and **secondary Y axis**. Right-click a plot for Reset view, Clear, **cursors**,
  **show samples**, **CSV export** and **spy** (a separate zoom window).
  Double-left-click a plot or axis to perform **Reset view** for that subplot.
  The popup's **Grid layout** menu also offers the sliders and **Equal sizes**.
  Divider sizes are saved with JSON sessions; older sessions start with equal sizes.
- **Range-aware downsampling** — a min/max pyramid (pure NumPy) for time series; multi-GB logs
  pan at full fps and zoom reveals detail. (XY plots decimate by plain stride.)
- **FFT & Histogram windows** — overlay several signals, pick the time window
  (follow a plot / full / custom), compute on demand, log axes, CSV export.
- **Node canvas** — drag a signal into a graph, apply transforms (FFT / math /
  filter / shift), and the result becomes a new draggable signal. Fully scriptable
  (`node_*`) and extensible with your own **Python plugin nodes** (see [Plugins](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_plugins.rst)).
- **Python automation** — control the open viewer with `uz_dataviewer.Client` from a terminal,
  Python file, or the Python panel. The application log reports actions and errors. Sessions save to JSON.
- **MaterialFlat theme.** Runs on Windows and Linux.

## Quick start

From the repository root, prepare and enter the shared CLI/viewer environment:

```bash
./uz shell                    # Windows PowerShell: .\uz.ps1 shell
uz-dataviewer
uz-dataviewer gui path/to/log.csv
uz-dataviewer gui session.json
```

`./uz shell [local|stable|prerelease]` selects the CLI source; without a source it
reuses the last setup, or selects stable on first use. `local` builds the checkout's
Rust CLI. The viewer is installed from source into the repository `.venv` along
with its locked runtime dependencies. Both `uz-dataviewer` and `ultrazohm_cli`
are available in the shell. `exit` returns to the original terminal.

The Bash and PowerShell launchers bootstrap missing uv and the pinned Python;
host Python and Make are not required. `./uz setup` prepares the environment
without opening a shell. See the [shared launcher guide](../README.MD#cli-and-data-viewer)
for source selection, prerequisites and build commands.

Start the GUI with `uz-dataviewer`, then use `uz-dataviewer status` from another
activated terminal to control it. `uz-dataviewer --help` lists application commands;
`./uz --help` lists repository tasks. Input paths are relative to your current directory.

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

## Settings

Click **Settings** in the menu bar to open a non-modal window:

- **General:** log browser directory and startup visibility of Application log and Python.
- **Data loading:** backend, loading mode, and disk cache for newly opened recordings.
- **Performance:** RAM cache limit and display points per signal.

Edits apply immediately (except startup visibility) and persist as application defaults
in `viewer_preferences.json` in the platform user data directory. Each section has
**Reset this section**. An empty log directory uses the firmware checkout's `artifacts`
directory. The status bar displays FPS and cache usage.

Session files retain their own data and plot settings; loading a session does not
rewrite application defaults. Explicit startup options override saved defaults for
that launch. Device configuration remains in its acquisition panels.
The Python client uses the same settings service:

```python
viewer.get_settings()
viewer.set_setting("cache_budget", 512)
viewer.set_setting("show_application_log", False)
```

## Large recordings and responsiveness

The Data Viewer never uses GUI idle throttling. Idling stays disabled during live
streaming, paused views, and offline analysis, even without mouse or keyboard
input. Actual FPS still depends on rendering workload and display synchronization.

The desktop defaults to **Polars + Lazy**; the online version uses **PyArrow + In memory**.
Choose **Settings → Data loading → Loading → In memory / Lazy** before opening files,
or select the mode at startup:

```bash
uz-dataviewer gui --loading-mode lazy path/to/log.parquet
uz-dataviewer gui --loading-mode lazy path/to/log.csv
```

- **In memory** retains the existing full NumPy arrays for fast analysis.
- **Lazy** (desktop default) reads selected columns and sample ranges from Parquet or streams CSV directly.
  CSV requires repeated text scanning and is slower for interactive navigation.

The setting affects subsequent opens. Existing runs retain their storage mode;
JSON sessions preserve mixed modes. The Python client equivalents
are `viewer.loading_mode("lazy")` and `viewer.cache_budget(1024)`.

Plot preparation, first-use summaries, XY sampling, cursor reads, and GUI FFT /
histogram computation run outside the desktop rendering thread. During an update,
the last completed plot remains visible. Up to four plot requests run concurrently,
so a slow first-time summary of one channel does not hold back other subplots;
concurrent requests can each hold their own decoded batches in memory.
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
with **Settings → Performance → RAM cache (MiB)**. Prepared plot arrays are bounded by display budgets.
Cache limits are **not a hard process-RAM limit**: decoded batches, index-building
scratch, FFTs, explicit NumPy conversions, exports and Python transformation
plugins can allocate additional memory. A full-recording FFT still needs its raw
input and output arrays. Histograms stream raw batches in two passes.
Node evaluation runs on a detached graph in a background worker. Results are published
on the application thread only if the graph and source inputs still match. Editing
inputs during evaluation discards the result; evaluate again to use the new settings.
Cancellation takes effect between reads and transforms; a running native transform
returns before its cancellation can be observed.

Measurement caches stay in RAM by default; no automatic CSV conversion is written.
Enable **Settings → Data loading → Disk cache**, pass `--disk-cache`, or use `viewer.disk_cache(True)` to persist indexes and summaries and convert lazy CSV inputs into reusable Parquet files.
Reopen existing files to change their cache policy.
JSON sessions preserve the setting for each file.
When enabled, disk caches live in `~/.cache/uz_dataviewer` (Polars uses its `polars/` subdirectory), or the directory selected by `UZ_DATAVIEWER_CACHE`.
They are disposable and source-versioned; close the viewer before clearing that directory.
Disabling disk caching leaves existing cache files untouched and does not read them.
There is currently no automatic disk-cache size limit.
Read-only or full summary-cache storage falls back to RAM; enabled lazy CSV conversion requires writable cache space.

### Session format and analysis correctness

Sessions now use schema version 6 with explicit run identities, including repeated opens and identical filenames in different directories.
Node links preserve explicit input slots, including disconnected slots. Canvas connection order does not change subtraction or division.
Restoring a saved session replaces the current session only after successful loading. Failed restoration leaves the current session intact. Version 1–5 snapshots and generated session scripts must be recreated as JSON sessions; version 6 records the materialized output domain explicitly.
Plot windows, precise time ranges and inactive recordings survive JSON round trips. Restoring a session resets panel caches and canvas positions; Y fitting completes when lazy samples arrive. Both primary and secondary Y limits survive JSON saves, including mouse zoom.
Removing a followed subplot switches its analysis windows to Full and discards the removed plot's cached range.
Recomputing a node preserves its derived recording's selected time origin.
Live snapshots and other runs without a backing file cannot be saved in a session; export their data first.
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
JSON is the only saved-session format; generated session-script export has been removed. Python automation uses `viewer.load_session("session.json")`; calls run sequentially and exceptions stop the script unless handled. Completing an export dialog after its subplot was removed cancels the export.
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
transient growth copies remain outside the numeric-data budget. Both CSV
backends share missing-value spellings (including NA, NULL and NaN).

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
| **[Usage](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_usage.rst)** | Driving the app: panels, plots, analysis windows, Python automation, application log, full client API reference. |
| **[Architecture](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_architecture.rst)** | Developers: module map, the state-driven/command-routed design, internals, how to extend, testing, design decisions. |
| **[Build](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_build.rst)** | Tasks, desktop bundles and releases. |
| **[Plugins](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_plugins.rst)** | Writing your own node transforms as Python plugins. |
| **[Library](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_library.rst)** | Using the data/analysis core headlessly as a Python library (load logs, FFT, node transforms) — no GUI. |
| **[Roadmap](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer_roadmap.rst)** | Open ideas and the record of what's already shipped. |
| **[Dataviewer V Javascope](../docs/source/guide/gui/uz_dataviewer/uz_dataviewer.rst)** | How the live JavaScope and this offline viewer relate, and the legacy `dataviewer.py` it succeeds. |

## Project layout

```
uz_dataviewer/
├── run.py                    # run from a source checkout (also accepts Python startup files)
├── src/uz_dataviewer/
│   ├── app.py                # docking layout, runner, theme, Session menu
│   ├── state.py              # AppState, SubplotCell, FFT/Histogram configs
│   ├── commands.py           # command registry / parser / dispatcher (the script API)
│   ├── console.py            # application activity log
│   ├── model.py              # Run / Signal / DataRegistry (+ time normalization)
│   ├── loader.py             # CSV/Parquet loading + channel-name parsing
│   ├── sources.py            # raw sources, bounded caches and min/max summaries
│   ├── downsample.py         # visible-window selection and display adapter
│   ├── analysis.py           # GUI-free transforms (FFT)
│   ├── transforms.py         # GUI-free node transforms (math, FIR filter)
│   ├── nodes.py              # dataflow graph + evaluation -> derived signals
│   ├── plugins.py            # external transform-node plugins (@transform, loader)
│   ├── session.py            # JSON save/restore + CSV export
│   └── panels/               # navigation, plots, analysis base, fft, histogram, nodes
├── tests/                    # pytest (logic via commands + headless rendering)
├── tasks.py                  # lint, test, bundle, bundle-smoke (Linux, Windows, CI)
└── build/                    # PyInstaller spec and frozen smoke tests
```

Documentation lives in `../docs/source/guide/gui/uz_dataviewer/`.

## Tests

Run the same checks as CI, on Linux (dev container) or Windows:

```bash
./uz check viewer                  # ruff and the full pytest suite, with a CLI wheel from this checkout
./uz build viewer                 # PyInstaller bundle in dist/
./uz task viewer bundle-smoke           # its smoke tests
```

The tasks use `uz_dataviewer/.venv-ci`, separate from the shared repository `.venv`.
`check` builds a debug CLI wheel from `../uz_cli` unless `--cli-wheel PATH` is given,
so the live tests run against the same commit. `./uz check viewer` forwards to the same task implementation. Linux CI runs it in the `ci` stage of `.devcontainer/Dockerfile`;
only the published Linux bundle is built in Ubuntu 22.04, because PyInstaller copies
the build system's libraries.

The console transcript does not capture every GUI gesture (including analysis
Reset view and some Y/XY gestures). Use JSON snapshots for supported view settings.
FFT-derived plots use Hz, remain independent of linked time axes, and export a
`frequency` column. Time normalization and time-based analysis reject spectra.

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

### Python and terminal automation

The viewer hosts a local control API at `127.0.0.1:19741`. Open an environment
shell with `./uz shell`, then use ordinary Python or
terminal commands. Control commands attach to an existing application:

```bash
uz-dataviewer --endpoint 127.0.0.1:19741 gui
# In another terminal:
uz-dataviewer status
uz-dataviewer load recording.csv
uz-dataviewer set-grid 3 2
uz-dataviewer --json list-runs
```

```python
from uz_dataviewer import Client

with Client() as viewer:
    run = viewer.load("recording.csv")
    viewer.set_grid(2, 1)
    viewer.add_signal(1, run, "current")
    view = viewer.create_view()
    viewer.add_signal(1, run, "current", view=view)
    viewer.save_session("analysis.json")
```

`Client` uses an explicit endpoint, then `UZ_DATAVIEWER_ENDPOINT`, then the default.
Each viewer instance needs a distinct endpoint. Recording, node, and view handles
belong to a session; removal or session replacement invalidates old handles.
`list_runs()`, `list_nodes()`, `list_plots()`, and `list_views()` inspect state.
Terminal subcommands use hyphens, Python methods use underscores. Run
`uz-dataviewer --help` or a subcommand's `--help` for signatures. `--json` prints
machine-readable results; failures return a nonzero exit code.

Calls execute sequentially for each client. Loads and exports return when ready,
while manual GUI interaction remains available. Manual changes can occur between
calls; interactive automation is not a deterministic batch transaction. Client
paths resolve from the caller's working directory. Mutations are never retried
automatically after a transport failure, because they may already have completed.

The **Python** panel is available in offline and live modes through **View → Python**.
It edits ordinary `.py` files. Run saves the file and starts a fresh process in the
viewer environment, with `UZ_DATAVIEWER_ENDPOINT` supplied. **Managed device run**
requires a connected acquisition service, supplies `UZ_ACQUISITION_ENDPOINT`, locks
manual device controls, and provides **Stop script + device**. Ordinary **Stop script**
terminates Python without issuing a hardware Stop. External terminal processes
remain externally owned. A script can import both `uz_dataviewer.Client` and
`ultrazohm_cli.Client`; the latter connects to the acquisition service.

The **Application log** displays diagnostics and operation activity. It has no
command input. `.uzscript` and the old `uz …` console shortcut are removed. Use
normal `.py` files and the acquisition package's terminal interface instead.
See [compare_recordings.py](examples/compare_recordings.py) for the two-recording
PT1 comparison workflow.

JSON schema 6 snapshots preserve recording references, node graphs, analysis
settings, and additional plot grids. Recording paths are relative to the JSON
file where possible. Saves replace files atomically; failed restoration leaves
the existing workspace intact. Python variables, processes, and interpreter state
are not persisted. Source builds use the project venv; frozen builds run scripts
using bundled modules. An external Python environment can also attach to either.
Choosing **Load state** manually stops app-owned scripts and clears pending startup
automation before loading. External scripts retain ownership of their processes;
their old session handles are rejected after replacement.

Each viewer creates a random local control credential. Python clients and the CLI
discover it automatically in a private per-user directory under the OS temporary
directory. No token needs to be copied for normal use. Credentials are removed on
shutdown; a restarted viewer requires a new client. The listener accepts only
loopback connections and does not execute Python code from requests.

### Starting acquisition

The ordinary launcher and the bundle include the CLI; no Rust compiler is needed.
Startup does not connect to hardware; **Connect** starts acquisition; **Existing service → Attach** reuses an existing service. Relative
recording arguments keep their original working directory.

Launching `uz-dataviewer` from an UltraZohm checkout (or any of its subdirectories)
automatically selects that checkout for live mode. `gui --live-repo PATH` overrides
this default. Outside a checkout, use **Live Data → Browse for ultrazohm_sw**;
Browse also lets you switch to another checkout after startup.

Preparing the selected checkout
asks the CLI for `channel-mapping --repo PATH` and, when preferences are missing,
`profile --repo PATH`. The CLI reads current headers and filters only built-in
default assignments. Metadata is returned directly; ordinary preparation creates
no mapping cache file. Preparation runs in the background, and failures appear in
Live Data without closing the viewer. Connect and Flash UZ require successful
preparation; attaching to an existing service does not.

Connect launches `serve --repo PATH --profile settings.json`. The service resolves
the firmware configuration itself, strictly validates saved preferences, and
exposes the effective configuration through `catalog`. An existing service keeps
its loaded configuration. Shut it down and reconnect to apply a different
repository or changed headers. Select the checkout in the viewer, or pass `uz-dataviewer gui --live-repo PATH`.

The shared launcher selects the CLI with `./uz setup stable`, `prerelease`, or
`local`. Published versions must satisfy the viewer's minimum dependency version;
other dependencies stay locked. Local setup builds this checkout's CLI and does
not download the published CLI. Re-run `./uz setup local` after Rust changes.
Plain `./uz shell` preserves the last selection; `./uz setup stable` switches back.

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

Managed flashing uses `javascope_<commit>.json` in the applicable user directory, including
`-dirty` when applicable, and regenerates/replaces that cache on every attempt,
like startup. The prototype assumes headers stay
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
  to choose an observable using case-insensitive fuzzy search. Use **Up/Down** to
  highlight a result, **Enter** to assign it, and **Esc** to cancel. Typing continues
  filtering the list after arrow navigation; editing the query highlights the first
  match. Matches accept gaps between characters, but require their original order;
  contiguous matches rank first. Selection is blocked
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
  bounded RAM snapshot while acquisition and logging continue. Horizontal panning
  also enters Inspect. Unchecking **Follow live** freezes the display in the same
  way. The slider controls the same X duration.
  In Inspect, normal cursor-centered zoom and pan work; the slider changes duration
  around the current view's center. Checking **Follow live** catches up to the newest
  samples at the chosen duration. **Reset view**, including a double-left-click on
  a plot or axis, also resumes Follow live and resets the subplot's axes while
  preserving the chosen time depth. The toolbar's Reset view resets all subplots;
  the popup and double-click reset the selected subplot. No disk/cloud history is
  fetched in either mode.
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

A polling worker uses `Client.read_since()` at up to 30 Hz and retains at most the
service's configured sample capacity. Device commands, Connect, Shutdown and Flash UZ
run on a separate worker with their own service connection, so live plots keep
updating while a command is in progress (polling pauses only during Flash UZ).
Each publication is an immutable NumPy-backed snapshot that also carries per-bucket
minima/maxima, maintained incrementally as samples arrive; wide windows are drawn
from these buckets, narrow windows from raw samples, using the existing background
request scheduler. The GUI does not read intermediate recording files.
The default ring covers 30 seconds at the configured sample rate (300,000 samples
at 10 kHz; 3,000,000 at 100 kHz). The slider's maximum automatically follows the
service capacity times its configured sample period, not a measured wall clock.
Your selected time depth is preserved and clamped when needed. The plot shows
only the samples received so far while the buffer fills. Requests are paged
independently of buffer capacity to respect the CLI response-size limit.
Stale data, backend errors and cursor resynchronization are shown in the UI.

To compare live-data preparation performance between machines, run this with the
viewer's installed Python environment (PowerShell shown):

```powershell
.\.venv\Scripts\python.exe .\uz_dataviewer\build\benchmark_live.py --sample-rate 10000 --traces 3
```

On Linux, use `.venv/bin/python` with the same script and options.
The benchmark simulates filling and wrapping the 30-second buffer and prints
JSON timings for appends and preparing the visible traces. It needs no hardware.
`--channels` defaults to 20: buffering work depends on acquired channels even
when only three are plotted. These are CPU timings, not GUI FPS; they exclude
the CLI, network, graphics driver and competition between worker threads.
The reported ring allocation also excludes the CLI and older snapshots still
held by Inspect or display readers. The status bar's RAM cache is a separate
cache and does not include these live buffers.

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

The Python panel starts hidden; open it with **View → Python**. Set **Arguments**
(quote values containing spaces) and **Working directory** before running. Arguments
are passed directly to Python without shell expansion; use forward slashes for
Windows paths. Scripts receive viewer and available acquisition endpoints through
`UZ_DATAVIEWER_ENDPOINT` and `UZ_ACQUISITION_ENDPOINT`.
The ordinary runner stops the script process; **Managed device run** also provides
the device Stop workflow. Python client export calls wait for publication and raise
on failure. Startup Python files run sequentially after the GUI opens, so the
viewer can process their requests; a failed startup script stops the sequence.

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
./uz shell
./uz shell local   # with this checkout's CLI
```

The same works on Windows. Run
`python measurement.py` or `ultrazohm_cli status`. Type `deactivate` to deactivate
within the child shell, or `exit` to return to the original terminal.

### Combined desktop distribution

Extract the entire release archive and launch `uz_dataviewer/uz_dataviewer`
(or `uz_dataviewer.exe` inside that folder on Windows). Keep `_internal` beside
it. Python and uv are bundled; Vitis is not. Select the **ultrazohm_sw root directory** with **Live Data → Browse for ultrazohm_sw**,
next to **Browse for XSCT**, or launch with `gui --live-repo PATH`. Offline viewing needs no selection. All available windows except Python and Application log open at startup; Navigation, Plots and Log
Browser are selected. Mode selects Analysis or Live tabs without closing other
windows. Use View to open Python or toggle individual windows. The source launcher
behaves the same; all available windows except Python and Application log start open, with Analysis tabs selected.

The source and packaged applications use the same CLI and script worker logic.
Scripts execute as ordinary `__main__` files with the arguments entered in the
Python panel and endpoint environment variables. No client object is injected. Source scripts use the venv's modules; packaged scripts use bundled
modules. Additional dependencies can be used in an external venv with a matching
CLI wheel attached to the service. Such scripts are not terminated by GUI Stop.

Writable data belongs to the selected firmware workspace, the same folder for the
bundle and the source launcher: `<workspace>/artifacts/_user/`. Until a workspace
is known (for example a bundle started outside a checkout), the viewer uses a
per-user folder instead of its working directory: `%LOCALAPPDATA%\UltraZohm\uz_dataviewer`
on Windows, `${XDG_DATA_HOME:-~/.local/share}/ultrazohm/uz_dataviewer` on Linux.

The directory contains `logs/` for recordings and service logs, `viewer.ini`
for layout settings, and `viewer_cache/` for optional data caches. Flash-generated
`javascope_*.json` snapshots and editable `settings.json` and `tools.json`
preferences live directly in the applicable user directory. Application packages,
Tcl scripts, assets and built-in defaults remain bundled in the standalone
application; workspace preferences are never written into `_internal/`.

After root-directory selection and successful header parsing, preparation creates missing
runtime settings from the bundled CLI defaults, filtered for that workspace's
observables. It also creates missing tool preferences with no XSCT selection
and creates the logs directory. Existing preferences are preserved byte for byte.
Layout settings are managed by the GUI framework when the viewer runs.
Connect passes `settings.json` unchanged and rejects unavailable explicit channel
assignments. Flash preserves its separate migration step and profile snapshot,
reporting assignments removed by the new firmware. Edit `sample_period_us`
and `initial_channels` before the next Connect; an empty `initial_channels`
object sends no initial selections. Browsing for XSCT explicitly updates
`tools.json`. The service rereads headers at each repository-based launch.

**Save live settings**, next to **Browse for ultrazohm_sw**, saves the current
channel assignments as `initial_channels` in `settings.json`. It also writes
`live_view.json` with connection fields, the recording parent directory, the live plot grid and signal names,
axis settings, follow mode, time depth, filters, and variable input values.
Selecting that workspace on a later launch restores the preferences; plot traces
are restored when live data arrives. Saving while disconnected preserves the
existing startup channel assignments. Restoring preferences does not connect,
send variable values, or start logging. Acquisition data and an Inspect snapshot
are not included; use recording or Freeze/export for those.

Two viewers on the same checkout share preferences, layout, caches and default
logs. An already running acquisition service owns its configuration: use
Existing service > Attach from the other viewer rather than starting another
service at the same endpoint. Do not flash/build the shared Vitis workspace
concurrently from two viewers.
Explicit output paths and `UZ_DATAVIEWER_CACHE` still override their defaults.
Data from earlier versions in `artifacts/_user_standalone/` is left in place;
copy settings or recordings into `artifacts/_user/` if needed.

For flashing, XSCT is detected on PATH. If it is absent, use **Browse for XSCT**
and select the vendor launcher, such as `Vitis/2022.2/bin/xsct.bat` on Windows
or `bin/xsct` on Linux. Select XSCT rather than the Vitis GUI executable.
The viewer remembers the path in `tools.json` in its user directory and prepends its directory
to PATH for itself and its child processes on subsequent starts. The system
PATH is unchanged. Starting the viewer from a Vitis command prompt (or after
sourcing `settings64.sh`) also works.

To build the combined application, run `./uz build viewer`
(optionally with `--cli-wheel PATH` for a wheel built from the same commit). The task
synchronizes locked dependencies before installing that wheel. CI builds both OS
wheels once, packages folder distributions from them, and tests frozen workers
against the JavaScope simulator. Releases from `develop` and
`feature/uz_cli_dataviewer_testing` are prereleases; `main` releases are stable.
Each release holds both bundles and both CLI wheels, which are also on PyPI.

The standalone distribution bundles repository Tcl scripts and Vitis launch
presets. Its CLI workers always use those scripts, with the selected repository
passed separately as the workspace root. Source/venv execution uses the
checkout's Tcl scripts. JSON generation only needs the firmware headers and does
not require Tcl or Vitis. Default runtime profile settings come from the CLI,
not a `uz_cli` directory in the selected checkout.

Firmware operations still require Vitis 2022.2/XSCT, its compilers and utilities,
JTAG drivers/server and hardware access, plus project firmware sources, linker
scripts and hardware export (XSA/bitstream). Flash builds the existing Vitis
workspace before programming; generate it first if absent. The hardware-specific
`psu_init.tcl` comes from that hardware export; vendor `fsbl.tcl` and
`zynqmp_utils.tcl` come from Vitis. They are not generic application resources.

The distribution includes two entry points: `uz_dataviewer` (`uz_dataviewer.exe`
on Windows) launches the desktop without a console window; `uz-dataviewer`
(`uz-dataviewer.exe`) is the terminal entry point with stdout, stderr and exit
codes. Both share the same packaged modules. Use the terminal executable for
`status`, `list-runs`, and other control commands.

Discovery methods return typed handles, including handles nested in plot
references. For example, `viewer.add_signal(1, viewer.list_runs()[0]["handle"], "y")`
adds a recording already opened manually. CLI output remains ordinary JSON.
Cancellation can stop preparation; once application-thread commit starts, the
operation finishes publication and cannot be rolled back by disconnecting.

Application log starts hidden; enable it through **View → Application log**.
The Log Browser starts at the selected checkout’s `artifacts/` directory.
