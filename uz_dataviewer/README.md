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
  `.parquet`, read with Apache Arrow.
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
  (`node_*`) and extensible with your own **Python plugin nodes** (see docs/PLUGINS.md).
- **Scriptable command console** — every action echoes a command; the input runs them, with
  completion, history and a selectable log. Sessions save to JSON or a replayable `.uzscript`.
- **MaterialFlat theme.** Runs natively (Windows/Linux/macOS) and in the browser (Pyodide/WASM).

## Quick start

```bash
pip install -r requirements.txt      # or: pip install -e .
python run.py                        # or: python -m uz_dataviewer
python run.py ../javascope/Log_2026-06-11_22-45-16.csv   # preload
python run.py session.uzscript       # replay a saved session
```

Then **Open file(s)…** in the Navigation panel, expand the run, and drag signals into the
plots (or the FFT / Histogram windows).

## Documentation

| Doc | For |
|-----|-----|
| **[docs/USAGE.md](docs/USAGE.md)** | Driving the app: panels, plots, analysis windows, the command console & scripting, full command reference. |
| **[docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)** | Developers: module map, the state-driven/command-routed design, internals, how to extend, testing, design decisions. |
| **[docs/BUILD.md](docs/BUILD.md)** | Building native executables and the web/WASM app. |
| **[docs/NATIVE_VS_WEB.md](docs/NATIVE_VS_WEB.md)** | What differs between the desktop and browser builds (file I/O, threading, memory) and what's identical. |
| **[docs/PLUGINS.md](docs/PLUGINS.md)** | Writing your own node transforms as Python plugins. |
| **[docs/ROADMAP.md](docs/ROADMAP.md)** | Open ideas and the record of what's already shipped. |

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
│   ├── session.py            # JSON save/restore + .uzscript + CSV export
│   ├── webbridge.py          # browser integration (file input, array load, downloads)
│   └── panels/               # navigation, plots, analysis base, fft, histogram, nodes
├── tests/                    # pytest (logic via commands + headless rendering)
├── docs/                     # USAGE / ARCHITECTURE / BUILD
└── build/                    # native (PyInstaller) + web (Pyodide) build flow
```

## Tests

```bash
pip install pytest
pytest
```
