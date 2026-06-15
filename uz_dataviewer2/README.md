# UltraZohm Data Viewer (`uz_dataviewer`)

A native/web data viewer for UltraZohm JavaScope logs, built with
[Dear ImGui via `imgui_bundle`](https://github.com/pthom/imgui_bundle) and ImPlot.
It is the spiritual successor to the Plotly/Dash `javascope/dataviewer.py`, with a
VSCode-style docked layout, drag-and-drop subplots and range-aware downsampling so
multi-gigabyte logs stay interactive.

## Layout

```
+--------------------------------------------------------------+
|  Navigation  |            Plots  /  FFT  (tabs)              |
|   (left)     |                                               |
|  runs &      |   runtime grid of subplots (1x1 ... 2x2 ...)  |
|  signals     |   drag a signal here to plot it               |
|              |                                               |
|--------------+-----------------------------------------------|
|                    Console  (bottom)                         |
+--------------------------------------------------------------+
```

## Features

- **Load many files** — `.csv` (JavaScope `;`-separated) and `.parquet`, multiple at once.
  CSV is read with Apache Arrow's multi-threaded parser for speed on huge logs.
- **navigation Style** — expand a run to see its channels, (de)activate runs,
  remove runs. Channel headers like `CH8=8)ia` are cleaned to friendly names with
  units (`rpm`, `us`, …) detected for axis labels.
- **Drag & drop subplots** — drag a signal from the tree onto any plot cell.
- **Runtime-settable grid** — `1x1`, `1x2`, `2x1`, `2x2`, `1x3`, `3x1`; assignments survive resizes.
- **Per-cell plot type** — line / scatter / stairs / **histogram** / **XY** (signal-vs-signal) / **FFT**.
- **Show samples** — toggle a marker at every sample on a line plot.
- **Spy tool** — drag a rectangle on a plot and see just that region in an inset below
  (ImPlot's drag-rect), per cell.
- **Cursors** — two draggable vertical cursors per cell with a Δx / frequency / Δy readout.
- **Secondary Y axis** — right-click a signal in the legend ▸ *Right axis* to move it to its
  own scale (or `set_axis(plot_1, run_1, ib, right)`).
- **Data export** — per-cell **Export** button (or `export_data(...)`) writes the visible
  window to CSV, with an optional `relative=true` to zero the start time.
- **Linked X axes** — pan/zoom one subplot and the others follow (the old "lock time axis").
- **Range-aware downsampling** — MinMax-LTTB via `tsdownsample`; zoom in to reveal detail.
- **FFT** — as a dedicated panel *and* as a per-cell plot type; both overlay several signals
  (drag them in), with DC removal and a Hann window. The time window is explicit: a
  **Custom / plot_N** selector either follows a chosen subplot's X range or uses manual
  `t min`/`t max`. The transform runs only on demand (**Compute** / **Calc FFT** button, or once
  when an input changes) so it never tanks the frame rate on large windows.
- **Per-log time normalization** — right-click a run ▸ *Normalize start time* (default 0, or any
  value), or load pre-normalized with `load("Log.csv", 0)`.
- **MaterialFlat theme.**
- **Scriptable command console** — see below.

## Command console & scripting

Every click is a command. The bottom **Console** echoes each action as a canonical call
(`> add_signal(plot_1, run_1, ia)`, `> set_x_lim(plot_1, 1.2, 1.8)` when you zoom) and its
input box runs the same commands. Type a command name for completion (matches listed below
the box; **Tab** fills the first; **Up/Down** for history); type `help` for the full list.

```text
load("Log_2026-06-11.csv")
set_grid(2, 2)
add_signal(plot_1, run_1, ia)                       # run by id ...
add_signal(plot_2, Log_2026-06-11.csv, Speed_rpm)   # ... or by file label
set_plot_type(plot_3, FFT)
set_x_lim(plot_1, 1.0, 2.0)
show_samples(plot_1, on)
cursors(plot_1, on)
set_axis(plot_1, run_1, Speed_rpm, right)
spy(plot_2, on)
export_data(plot_1, "out.csv", true)   # true = zero the start time
```

Plots are referenced as `plot_1..plot_N` (row-major); runs as `run_<id>` or by file name.
The console body is a read-only, always-selectable text box (drag to mark, Ctrl+C to copy)
that auto-scrolls. A `.uzscript` passed on the command line is replayed at startup
(`python run.py session.uzscript`).

### Save / restore the session

- **Session ▸ Save state… / Load state…** — exact JSON snapshot (grid, assignments, plot
  types, link/downsample settings, FFT config, file list); restore reloads the files and
  rebuilds the view.
- **Session ▸ Export script… / Run script…** — a human-readable, editable `.uzscript` of the
  commands that reproduce the session when replayed (also available as the `save_state` /
  `load_state` / `export_script` / `run_script` console commands).

- **Console** — load status, errors and actions are logged in the bottom panel.

## Quick start

```bash
pip install -r requirements.txt          # or: pip install -e .
python run.py                            # or: python -m uz_dataviewer
# optionally pass files to preload:
python run.py ../javascope/Log_2026-06-11_22-45-16.csv
```

Then click **Open file(s)…** in the Navigation panel, expand the run, and drag
signals into the plot cells.

## Downsampling — relationship to the old viewer

`dataviewer.py` used `plotly_resampler.FigureResampler`. That class is bound to
Plotly figures and **cannot** be reused with ImPlot. Its decimation engine,
however, is the standalone [`tsdownsample`](https://github.com/predict-idlab/tsdownsample)
package — which *is* reusable. `uz_dataviewer` calls `tsdownsample`'s
MinMax-LTTB downsampler directly against the visible X range of each plot
(`src/uz_dataviewer/downsample.py`). On platforms without a `tsdownsample` wheel
(e.g. the web/Pyodide build) it falls back to a pure-NumPy MinMax decimator.

## Project structure

```
uz_dataviewer/
├── pyproject.toml            # packaging + `uz-dataviewer` entry point
├── requirements.txt
├── run.py                    # run from a source checkout without installing
├── src/uz_dataviewer/
│   ├── app.py                # docking layout + immapp runner + Session menu
│   ├── state.py              # AppState: grid, cells, async loading, FFT config
│   ├── commands.py           # command registry / parser / dispatcher (the script API)
│   ├── session.py            # JSON save/restore + .uzscript export/replay
│   ├── analysis.py           # GUI-free transforms (FFT) shared by panel + plot type
│   ├── model.py              # Run / Signal / DataRegistry
│   ├── loader.py             # CSV/Parquet loading + channel-name parsing
│   ├── downsample.py         # MinMax-LTTB (tsdownsample) + NumPy fallback
│   ├── console.py            # bottom console/log + command input
│   └── panels/
│       ├── navigation.py     # left tree, drag sources, file dialog
│       ├── plots.py          # subplot grid, plot types, spy, drop targets, axis linking
│       └── fft.py            # FFT panel
├── tests/                    # pytest (loader, downsampler, commands, session, plot types)
└── build/                    # native (PyInstaller) + web (Pyodide) build flow
```

## Building native / web apps

See **[docs/BUILD.md](docs/BUILD.md)**. In short:

| Target            | Command                                   | Output                     |
|-------------------|-------------------------------------------|----------------------------|
| Linux / Ubuntu    | `./build/build_native.sh`                 | `dist/uz_dataviewer`       |
| Windows           | `.\build\build_native.ps1`                | `dist\uz_dataviewer.exe`   |
| macOS             | `./build/build_native.sh`                 | `dist/uz_dataviewer`       |
| Web (WASM/Pyodide)| `./build/build_web.sh`                    | `web/` (serve statically)  |

## Tests

```bash
pip install pytest
pytest
```
