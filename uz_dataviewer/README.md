# UltraZohm Data Viewer (`uz_dataviewer`)

A native/web data viewer for UltraZohm JavaScope logs, built with
[Dear ImGui via `imgui_bundle`](https://github.com/pthom/imgui_bundle) and ImPlot.
It is the offline successor to the Plotly/Dash `javascope/dataviewer.py`: a VSCode-style
docked layout, drag-and-drop subplots, dedicated FFT/Histogram analysis windows, range-aware
downsampling for multi-gigabyte logs, and a **scriptable command console** where every click
is a replayable command.

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
- **Scriptable command console** — every action echoes a command; the input runs them, with
  completion, history and a selectable log. Sessions save to JSON or a replayable `.uzscript`.
- **MaterialFlat theme.** Runs natively (Windows/Linux/macOS) and in the browser (Pyodide/WASM).

## Quick start

Run the launcher from the repository root (Linux/macOS):

```bash
./uz_dataviewer/start.sh
./uz_dataviewer/start.sh path/to/log.csv    # preload one or more files
./uz_dataviewer/start.sh session.uzscript   # replay a saved session
```

On Windows, use PowerShell:

```powershell
.\uz_dataviewer\start.ps1
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

Alternatively, install and run manually from `uz_dataviewer/`:

```bash
pip install -r requirements.txt      # or: pip install -e .
python run.py                        # or: python -m uz_dataviewer
python run.py ../javascope/Log_2026-06-11_22-45-16.csv   # preload
python run.py session.uzscript       # replay a saved session
```

On desktop, selecting a CSV larger than 1 GiB prompts **Large log, conversion to parquet recommended**.
Choose **Open CSV** to read it directly, or **Convert to Parquet** to create and open a file with the same stem and directory (for example, `logs/run.csv` becomes `logs/run.parquet`).
This applies to native drag-and-drop, the Log Browser and the file picker.
Conversion runs in the background using the selected backend and opens the result with the selected loading mode.
The original CSV is preserved; an existing Parquet file is never overwritten and can instead be opened explicitly.
Choosing **Open CSV** skips automatic disk-cache conversion for that load, even when disk caching is enabled.

Then **Open file(s)…** in the Navigation panel, expand the run, and drag signals into the
plots (or the FFT / Histogram windows).

## Large recordings and responsiveness

The desktop defaults to **Polars + Lazy**; the online version uses **PyArrow + In memory**.
Choose **Loading → In memory / Lazy** in Navigation before opening files,
or select the mode at startup:

```bash
./uz_dataviewer/start.sh --loading-mode lazy path/to/log.parquet
./uz_dataviewer/start.sh --loading-mode lazy path/to/log.csv
```

- **In memory** retains the existing full NumPy arrays for fast analysis.
- **Lazy** (desktop default) reads selected columns and sample ranges from Parquet or streams CSV directly.
  CSV requires repeated text scanning and is slower for interactive navigation.

The setting affects subsequent opens. Existing runs retain their storage mode;
JSON sessions and exported scripts preserve mixed modes. The console equivalents
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
not reused.

The shared timestamp/summary RAM cache defaults to 1,024 MiB and is configurable
under **Memory settings**. Prepared plot arrays are bounded by display budgets.
Cache limits are **not a hard process-RAM limit**: decoded batches, index-building
scratch, FFTs, explicit NumPy conversions, exports and Python transformation
plugins can allocate additional memory. A full-recording FFT still needs its raw
input and output arrays. Histograms stream raw batches in two passes. Explicit
console/script commands and node/plugin evaluation retain synchronous semantics.

Measurement caches stay in RAM by default; no automatic CSV conversion is written.
Enable **Disk cache (new opens)** under **Cache settings**, pass `--disk-cache`, or use `disk_cache(true)` to persist indexes and summaries and convert lazy CSV inputs into reusable Parquet files.
Reopen existing files to change their cache policy.
Sessions and scripts preserve the setting for each file.
When enabled, disk caches live in `~/.cache/uz_dataviewer` (Polars uses its `polars/` subdirectory), or the directory selected by `UZ_DATAVIEWER_CACHE`.
They are disposable and source-versioned; close the viewer before clearing that directory.
Disabling disk caching leaves existing cache files untouched and does not read them.
There is currently no automatic disk-cache size limit.
Read-only or full summary-cache storage falls back to RAM; enabled lazy CSV conversion requires writable cache space.
The browser build retains synchronous execution because its current runtime has no worker-thread support.

### Session format and analysis correctness

Sessions now use schema version 4 with explicit run identities, including repeated opens and identical filenames in different directories.
Node links preserve explicit input slots, including disconnected slots. Canvas connection order does not change subtraction or division.
Restoring a saved session replaces the current session only after successful loading. Failed restoration leaves the current session intact. Old snapshots and older exported session scripts must be recreated.
Plot windows, precise time ranges and inactive recordings survive JSON and script round trips. Restoring a session resets panel caches and canvas positions; Y fitting completes when lazy samples arrive.
Small browser uploads use separate backing paths even when filenames match. Failed exports never download an earlier result.
Streamed browser recordings have no backing file, so session saving is rejected; export their data first.
Chain transforms with node links; using derived outputs as new source nodes is no longer supported.
Analysis and exports use exact time windows, while plotting retains edge padding.
FFT rejects duplicate or irregular timestamps instead of producing an incorrect frequency axis.

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
│   ├── downsample.py         # min/max pyramid (pure NumPy, O(output) per frame)
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
