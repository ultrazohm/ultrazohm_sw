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
opens afterward and **Connect** starts/attaches acquisition as usual. Relative
recording arguments keep their original working directory.

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

Use a wheel built with the `catalog` API. Without the wheel, offline viewing still
works and Live Data displays installation instructions. Live acquisition is native
only; the browser cannot connect to the local CLI socket.

- **Live Data** sits beside Navigation. **Connect** attaches to the service endpoint,
  or launches an independent CLI service if none is available, then connects to the
  device. **Attach service** attaches without changing the device connection. An
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
  and searchable named variables with an explicit Send action. Commands are sent
  without firmware acknowledgment; streamed platform state is shown separately.
  Error Reset is omitted because current firmware does not implement it.
- Fast and slow logging have independent Start/Stop controls and phase/error/path
  indicators. **Open completed log** opens the final Parquet through the ordinary
  lazy file workflow. Stopping logging does not stop acquisition or the device.
- Closing the viewer or **Detach viewer** leaves the service and logging running.
  **Shutdown service** ends acquisition and finalizes logs; device Stop is separate.
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
