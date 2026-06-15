# UltraZohm Data Viewer (uz_dataviewer)

Native data viewer for javascope log files, built with
[imgui_bundle](https://github.com/pthom/imgui_bundle) (Dear ImGui + ImPlot).
It is the successor of the plotly/Dash based `javascope/dataviewer.py` with a
VS-Code-like 3-pane layout and handles very large logs (> 1 GB) through
viewport-aware downsampling.

![layout](docs/screenshot.png)

## Features

- Reads javascope log files: **`.csv`** (`;`-separated, `time` column) and
  **`.parquet`** — multiple files at once, loaded on background threads.
- **3-pane layout**: navigation (left), plot area (right), console (bottom).
- Navigation tree (Matlab-style): expand a run to see its logged signals,
  checkbox to activate/deactivate a whole run, right-click to remove it.
- **Drag & drop** signals from the tree into any plot.
- Runtime-settable **plot grid** (1x1, 1x2, 2x1, 2x2, 2x3, 3x3); each cell
  keeps its configuration when switching grids.
- Per-cell **plot type**: *Time series* or *FFT*.
  - Time series: cursors (draggable A/B lines with value/delta readout),
    secondary y-axis per signal (right-click the legend entry), CSV export of
    the cursor region (optionally with time restarting at 0), axis fit.
  - FFT: select a source time plot + signal; the spectrum is computed over
    the region between the source plot's cursors (or its visible range),
    with Hann/Hamming/rectangular windows and log axes.
- **Lock time axes**: pan/zoom of one time plot is applied to all.
- **Downsampling for large files**: only the visible time range is drawn,
  reduced to a few thousand points with MinMaxLTTB
  ([tsdownsample](https://github.com/predict-idlab/tsdownsample) — the same
  Rust core that plotly-resampler uses in the old dataviewer). Spikes stay
  visible; zooming in reveals detail. A pure-numpy min/max fallback is used
  where tsdownsample is unavailable (web build). The point budget is
  adjustable via the *Detail* combo in the toolbar.
- Console with log levels, filtering and auto-scroll.

## Run from source

```bash
cd uz_dataviewer
pip install -e ".[dev]"        # includes tsdownsample + pytest
uz-dataviewer                  # or: python -m uz_dataviewer
uz-dataviewer my_log.parquet   # open files directly
```

## Tests

```bash
python -m pytest                       # unit tests (loader, downsample, fft, store)
xvfb-run -a python tests/smoke_gui.py  # headless GUI smoke test (CI)
```

## Build flow

### Native: Linux (Ubuntu)

```bash
./packaging/desktop/build.sh
# -> dist/uz-dataviewer/uz-dataviewer
```

### Native: Windows

```powershell
powershell -ExecutionPolicy Bypass -File packaging\desktop\build.ps1
# -> dist\uz-dataviewer\uz-dataviewer.exe
```

Both scripts create a `.venv-build` virtualenv, install the package with the
`fast` + `build` extras and run PyInstaller with
`packaging/desktop/uz_dataviewer.spec` (which collects imgui_bundle's assets
and native libraries).

### Web (pyodide / WebAssembly)

Per the [imgui_bundle pyodide docs](https://imgui-bundle.pages.dev/doc/), the
same Python code runs in the browser:

```bash
./packaging/web/build_web.sh [optional_demo.csv]
python -m http.server -d packaging/web/site 8000
# open http://localhost:8000
```

The script builds the app wheel, downloads the imgui_bundle emscripten wheel
and assembles a static site (`packaging/web/site/`) that can be hosted
anywhere. Web-build limitations:

- no native file dialogs — data files must be placed into the pyodide
  filesystem (the template fetches an optional `demo.csv`) and are loaded via
  the path box in the navigation panel;
- `tsdownsample` has no wasm wheel — the numpy fallback is used automatically;
- parquet support depends on `pyarrow` availability in the pyodide
  distribution; CSV always works (pure-python fallback reader).

## Architecture

```
src/uz_dataviewer/
├── app.py                  # entry point, hello_imgui docking layout
├── core/
│   ├── loader.py           # csv/parquet -> Run (numpy arrays), pyarrow based
│   ├── data_store.py       # loaded runs, async loading, drag&drop payloads
│   ├── downsample.py       # viewport MinMaxLTTB downsampling + cache
│   └── console.py          # thread-safe log buffer
├── analysis/
│   └── fft.py              # windowed amplitude spectrum over a region
└── ui/
    ├── app_state.py        # shared UI state (grid, plot configs)
    ├── navigation_panel.py # left: file tree, drag sources
    ├── plot_grid.py        # main: toolbar + cell grid
    ├── plot_panel.py       # time-series cell (drop target, cursors, export)
    ├── fft_panel.py        # FFT cell
    └── console_panel.py    # bottom console
```

### Why not plotly-resampler?

The old dataviewer downsamples with `plotly_resampler.FigureResampler`, which
is tightly coupled to plotly figures and Dash callbacks and cannot be reused
with imgui_bundle. Its underlying aggregation algorithm (MinMaxLTTB from the
`tsdownsample` package) is framework-agnostic, so exactly that core is reused
here: on every axes change the visible slice of each signal is re-downsampled
to the point budget, with caching and view-padding so panning stays smooth.
