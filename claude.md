# UltraZohm Data Viewer — Build Session Log

Export of the working conversation that produced `uz_dataviewer2/` (an
imgui_bundle/ImPlot reimplementation of the JavaScope `dataviewer.py`).

> **Historical document.** This is a snapshot of the *initial* build session and is kept
> for context only — it does not track later changes. For current documentation see:
> [uz_dataviewer2/README.md](uz_dataviewer2/README.md),
> [docs/USAGE.md](uz_dataviewer2/docs/USAGE.md),
> [docs/ARCHITECTURE.md](uz_dataviewer2/docs/ARCHITECTURE.md), and
> [docs/BUILD.md](uz_dataviewer2/docs/BUILD.md).

---

## 1. Original task (`dataviewer.md`)

Build a data viewer with the same functionality as `javascope/dataviewer.py`
(Plotly/Dash) but using [`pthom/imgui_bundle`](https://github.com/pthom/imgui_bundle):

- Read JavaScope logs — `.csv` (`;`-separated) **and** `.parquet`; files can be
  **>1 GB**, so downsampling is needed. Check what the old viewer uses for
  downsampling and whether it's reusable.
- VSCode-style **3-panel layout**: navigation left, main view right, console bottom.
- Navigation: load **multiple files**, activate the ones to use, "click open" a run
  to see its logged signals (Matlab-style).
- Create **multiple subplots**, **drag & drop** signals into them. Plot grid
  **runtime-settable** (1x1, 1x2, 2x2, …), plot **type changeable**.
- Later: plot a time signal and show its **FFT**, selecting which part of the
  signal feeds the FFT.
- New repo-level dir `uz_dataviewer`; clean structure; compile to native apps for
  Windows, Ubuntu, and Web; **clean build flow is essential**.

---

## 2. Investigation & key findings

- **Data format:** `time;CH1=1)ISR_ExecTime_us;CH2=2)…;` header, `;`-separated,
  trailing `;` on every row (→ empty trailing column). 20 channels, time starts at
  a non-zero value (e.g. `11.979 s`). Largest sample log ≈ **2.4 GB**.
- **Downsampling (the important finding):** the old viewer used
  `plotly_resampler.FigureResampler`, which is **bound to Plotly figures and cannot
  be reused with ImPlot**. But its decimation engine — the standalone
  **`tsdownsample`** package (MinMax-LTTB) — **is** reusable. The new viewer calls
  `tsdownsample` directly against the visible X-range, with a pure-NumPy MinMax
  fallback for environments lacking the Rust wheel (web/Pyodide).
- **Environment:** Python 3.12; imgui_bundle 1.92.801, pandas, pyarrow, numpy,
  tsdownsample all available. No display in the dev sandbox (validated via tests +
  a headless ImGui-frame harness, not a real window).

---

## 3. What was built

`uz_dataviewer2/` (directory later renamed from `uz_dataviewer`):

```
uz_dataviewer2/
├── pyproject.toml            # packaging + `uz-dataviewer` entry point
├── requirements.txt
├── run.py                    # run from a source checkout without installing
├── src/uz_dataviewer/
│   ├── app.py                # hello_imgui docking layout + immapp runner
│   ├── state.py              # AppState: grid, cells, async loading, FFT config
│   ├── model.py              # Run / Signal / DataRegistry
│   ├── loader.py             # CSV/Parquet loading + channel-name parsing
│   ├── downsample.py         # MinMax-LTTB (tsdownsample) + NumPy fallback
│   ├── console.py            # bottom console/log
│   └── panels/
│       ├── navigation.py     # left tree, drag sources, file dialog
│       ├── plots.py          # subplot grid, drop targets, axis linking
│       └── fft.py            # FFT panel
├── tests/                    # pytest (loader, downsampler, plots — no GUI window)
├── build/                    # PyInstaller spec + native/web build scripts
└── docs/BUILD.md
```

**Features:** 3-panel docked layout; multi-file CSV/Parquet load on a background
thread; Matlab-style run→signal tree with activate/remove; drag-and-drop signals
into plot cells; runtime grid (1x1…3x1); per-cell plot type (line/scatter/stairs);
linked X axes; range-aware downsampling; FFT panel (DC removal + Hann window,
window follows the linked plot range); console.

**Build flow:** `pyproject.toml` + entry point; PyInstaller spec and
`build_native.sh`/`.ps1` for Windows/Ubuntu/macOS; `build_web.sh` for a Pyodide/WASM
bundle; pytest tests.

---

## 4. Architecture Q&A — imgui vs egui (Rust)

User asked whether imgui was the right choice or egui (Rust) would be better.

**Conclusion:** for a desktop-first viewer, **imgui_bundle + ImPlot is the right
call**, mainly because of ImPlot and the Python data stack. egui becomes preferable
only if *polished web delivery* is a primary goal.

- **imgui/ImPlot wins (decisive for the core):** ImPlot has no real egui equivalent
  for drag-drop into plots, plot-type switching, linked/multi axes; Python data
  ecosystem (pyarrow, numpy FFT, **tsdownsample reused directly**); faster iteration;
  fits the existing Python/C/MATLAB repo and team.
- **egui wins:** web (clean native WASM vs heavy Pyodide); small/fast native binary
  (vs ~200 MB PyInstaller bundle); raw perf/memory on huge files — though our hot
  paths (Arrow parse, tsdownsample, numpy FFT) are already native, so the gap is
  smaller than it looks.
- **Decision hinge:** desktop-primary → stay on imgui/ImPlot. Web first-class → the
  stronger alternative is arguably **C++ imgui+ImPlot via emscripten** (keeps ImPlot,
  clean WASM, drops the Python data stack), not egui.

---

## 5. Bugs found & fixed (in order)

### 5.1 PyInstaller: `attempted relative import with no known parent package`
The spec used `__main__.py` (which has `from .app import main`) as the entry script;
PyInstaller runs the entry as top-level `__main__` with no package context.
**Fix:** added `build/entrypoint.py` with an absolute import, put `src/` on the path
in the spec, and bundled the package via `collect_submodules("uz_dataviewer")`.
Rebuilt successfully (exit 0); binary then ran past the import.

### 5.2 Directory renamed
`uz_dataviewer` → `uz_dataviewer2` (per user request). Inner package kept its name,
so imports/entry point/spec were unchanged. Tests stayed green.

### 5.3 Plots not drawn over time — empty/garbage limits
Range-aware downsampling read `get_plot_limits()` **before** the axis had ever fit to
data. On the first frame the limits were the default `(0, 1)`, which doesn't overlap
a log whose time starts at `11.979 s` → empty slice → a single point corrupted
ImPlot's autofit → limits blew up to `9.8e36` and never recovered.
**Fix:** one-shot fit to the data's true time extent (`fit_pending`); clamp the slice
window to the data extent; reject non-finite/degenerate limits; guard the shared-X
update. Regression tests added.

### 5.4 Scattered data & **negative times** — dtype byte-misread
ImPlot's `PlotLine` is templated on a **single type `T`** for both `xs` and `ys`.
We passed `time` as **float64** and `y` as **float32**; the binding silently accepts
the mismatch and reinterprets one buffer as the wrong type → garbage, including
negative times. (Slipped past earlier headless checks because they used `t=0` data
that happened to overlap.)
**Fix:** cast both arrays to the **same dtype (float64)** right before plotting
(time kept float64 for precision; `y` cast up — cheap because arrays are already
downsampled). Verified `plot_line` receives matched float64 arrays spanning
`11.979…16.084 s`, monotonic, no negatives. Regression test drives a real frame.

### 5.5 "Reset view" instead of double-click intercept
Because we downsample to the *visible* range, ImPlot's built-in double-click fit only
sees the visible slice and can't zoom back out. First implemented a double-click
intercept, then (per user) replaced it with a per-cell **"Reset view" button** that
triggers the one-shot fit — extended to fit **both axes** to the **full data extent**
(`_cell_y_extent` scans full arrays on fit frames only). Verified: zoom to
`[13.0, 13.5]` → Reset view → both axes back to `[11.979, 16.084]`.

### 5.6 Downsampling: remove checkbox → user-set fixed budget + indicator
Removed the on/off checkbox; downsampling is **always on**. Added a **`Max points`**
toolbar input (default **2000**, min 100) used as the per-signal budget, plus a live
indicator:
- **`downsampling: active`** (amber) when any visible signal is decimated.
- **`downsampling: off (all samples)`** (green) when everything fits the budget.
Each cell header shows `~N pts shown`. Decimation is detected by comparing points
drawn vs the raw visible slice (`xs.shape[0] < stop - start`).

**Confirmed:** when you zoom in far enough that the visible window holds fewer raw
samples than the budget, downsampling stops and **all original points are shown**
(full view of 41,055 rows → 2000 pts, active; zoom to `13.00–13.05 s` → 503 pts,
off/all samples).

---

## 6. How many samples are shown?

At most **`max_points` (default 2000) per signal**, per visible range, via
MinMax-LTTB. Zooming in redraws the same budget over a narrower window (progressive
detail) until the visible slice is smaller than the budget, at which point **every
raw sample is drawn**. The budget is per signal (N signals ≈ N×budget points).

---

## 7. Status

- **14 pytest tests pass** (loader, channel parsing, parquet, downsampler ranges +
  fallback, plot range/dtype regressions).
- All panels validated through a headless ImGui+ImPlot frame harness (no windowed
  run possible in the sandbox — no display).
- Real file `javascope/Log_2026-06-11_22-45-16.csv` (41,055 rows, 20 signals) loads
  in ~0.22 s and plots correctly over time.

### Run
```bash
cd uz_dataviewer2
pip install -r requirements.txt
python run.py ../javascope/Log_2026-06-11_22-45-16.csv
```

### Build
| Target             | Command                     | Output                   |
|--------------------|-----------------------------|--------------------------|
| Linux / Ubuntu     | `./build/build_native.sh`   | `dist/uz_dataviewer`     |
| Windows            | `.\build\build_native.ps1`  | `dist\uz_dataviewer.exe` |
| Web (WASM/Pyodide) | `./build/build_web.sh`      | `web/` (serve statically)|
