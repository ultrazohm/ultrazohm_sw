# Architecture & Design (developer guide)

This document explains how `uz_dataviewer` is put together, the design decisions
behind it, and how to extend it. For end-user docs see **[USAGE.md](USAGE.md)**;
for packaging see **[BUILD.md](BUILD.md)**.

---

## 1. The one big idea

The viewer is **state-driven and command-routed**:

- There is a single source of truth, `AppState` ([state.py](../src/uz_dataviewer/state.py)).
  Panels are (almost) pure render functions: each frame they read `AppState` and draw it.
- **Every discrete user action goes through the command registry**
  ([commands.py](../src/uz_dataviewer/commands.py)). A command mutates `AppState`
  *and* echoes its canonical call to the console.

Because of this, four things fall out for free:

1. **Scriptability** — anything you can click, you can type or replay (`.uzscript`).
2. **A live transcript** — the console shows exactly what happened, as commands.
3. **Save/restore** — sessions serialise to JSON or to a replayable command script.
4. **Testability** — the whole app logic is exercised by dispatching command strings;
   no window required.

> If you add a feature and the only way to trigger it is a direct widget mutation,
> you've broken the model. Add a command and have the widget call it.

---

## 2. Frame flow

`immapp.run()` (hello_imgui) drives a classic immediate-mode loop. Per frame:

```
pre_new_frame()                      # app.py: poll async loads, focus requests, file dialogs
└─ docking layout renders each DockableWindow's gui_function:
   ├─ NavigationPanel.render(state)  # left: runs + signals + normalize menu
   ├─ PlotsPanel.render(state)       # center: subplot grid
   ├─ FftPanel.render(state)         # center tab: FFT window
   ├─ HistogramPanel.render(state)   # center tab: Histogram window
   └─ Console.render(state)          # bottom: log + command input
```

Immediate mode has one structural consequence the code leans on everywhere:
**there is no retained widget state**, so anything that must persist across frames
lives in `AppState`/`SubplotCell`. Transient "do this once next frame" requests use
a **pending-flag pattern**: e.g. `cell.fit_pending`, `cell.pending_x_lim`,
`cfg.compute_requested`. The renderer consumes and clears the flag.

---

## 3. Module map

| Module | Responsibility | Key types |
|--------|----------------|-----------|
| [app.py](../src/uz_dataviewer/app.py) | Docking layout, `immapp` runner, theme, Session menu, `.uzscript`/file startup | `DataViewerApp` |
| [state.py](../src/uz_dataviewer/state.py) | The single app state, grid/cells, analysis configs, async load orchestration | `AppState`, `SubplotCell`, `PlotType`, `AnalysisConfig`/`FftConfig`/`HistogramConfig` |
| [commands.py](../src/uz_dataviewer/commands.py) | Command registry, parser, dispatcher, the ~50 built-in commands | `CommandRegistry`, `Command`, `Param` |
| [console.py](../src/uz_dataviewer/console.py) | Bottom console: scrolling selectable log + command input/completion/history | `Console` |
| [model.py](../src/uz_dataviewer/model.py) | Loaded data + per-log time normalization | `Run`, `Signal`, `DataRegistry` |
| [loader.py](../src/uz_dataviewer/loader.py) | CSV (Arrow) / Parquet loading, header cleaning, delimiter sniffing | `load_file`, `parse_channel_name` |
| [downsample.py](../src/uz_dataviewer/downsample.py) | Range-aware MinMax-LTTB decimation (+ NumPy fallback) | `downsample_xy`, `visible_slice` |
| [analysis.py](../src/uz_dataviewer/analysis.py) | GUI-free transforms (FFT) | `compute_fft`, `FftResult` |
| [session.py](../src/uz_dataviewer/session.py) | JSON save/restore, `.uzscript` export/replay, CSV exports | `to_dict`/`apply_dict`, `export_*` |
| [webbridge.py](../src/uz_dataviewer/webbridge.py) | Browser integration (file input, array load, downloads) | `IS_WEB`, `load_columns`, `download` |
| panels/[navigation.py](../src/uz_dataviewer/panels/navigation.py) | Left tree, drag sources, file dialog, normalize menu | `NavigationPanel` |
| panels/[plots.py](../src/uz_dataviewer/panels/plots.py) | Subplot grid: types, cursors, spy, axis linking, secondary axis, export | `PlotsPanel` |
| panels/[analysis.py](../src/uz_dataviewer/panels/analysis.py) | Shared base for analysis windows (sources, follow-window, compute, stale, zoom, export) | `AnalysisPanel`, `follow_combo` |
| panels/[fft.py](../src/uz_dataviewer/panels/fft.py) | FFT window | `FftPanel(AnalysisPanel)` |
| panels/[histogram.py](../src/uz_dataviewer/panels/histogram.py) | Histogram window | `HistogramPanel(AnalysisPanel)` |

---

## 4. Data model

- A **`Run`** is one loaded file: a shared `time` axis (`float64`) plus one
  **`Signal`** per channel (`y` as `float32`, contiguous, ready for ImPlot/`tsdownsample`).
- **`DataRegistry`** owns runs and hands out stable integer ids; `SignalRef = (run_id, name)`
  identifies a signal everywhere.
- **Time normalization** is per-log: `Run.set_time_origin(target)` keeps the original
  `time_raw` and derives `time = time_raw - time_raw[0] + target`. It's reversible
  (`target=None` restores raw) and only re-derives on change, never per frame.

Channel headers like `CH8=8)ia` are cleaned to `ia` by `parse_channel_name`, which
also detects a trailing unit token (`_rpm`, `_us`, …) for axis labels.

---

## 5. The command layer

`CommandRegistry` holds `Command`s (a name, typed `Param`s, a handler, help). The grammar
is a single function call, `name(arg, arg, ...)` (`parse_call`).

- **Param kinds** drive both coercion and canonical formatting: `int`, `float`, `bool`,
  `str`, `plot` (`plot_1`↔index), `run` (`run_2` or a file label), `fwindow`
  (`custom`/`full`/`plot_N` for analysis windows).
- **Three entry points**:
  - `execute(state, name, args)` — used by UI handlers; coerces, runs, **echoes** the
    canonical call.
  - `dispatch(state, text)` — used by the console/scripts; parses then executes; errors
    go to the console.
  - `echo(state, name, values)` — logs a command **without** running it. Used for
    continuous gestures (zoom, cursor/spy drag) that ImPlot has *already* applied — the
    echo settles once on mouse-up rather than firing every frame.
- **Run resolution by label** is what lets scripts say `add_signal(plot_1, Log.csv, ia)`
  and survive run-id reassignment after a reload.

Panels never mutate `AppState` for a user action directly; they call
`state.commands.execute(...)` (often via a small `self._emit` wrapper that logs errors).
This is the invariant that keeps everything scriptable.

---

## 6. Plots panel internals ([panels/plots.py](../src/uz_dataviewer/panels/plots.py))

A runtime grid of `SubplotCell`s. Cell types: `line` / `scatter` / `stairs` (time series)
and `xy` (one signal vs another). FFT and Histogram are **separate windows**, not cell types.

Per time-series cell, each frame:

1. Compute the data extent and apply any **pending** axis limits (`fit_pending`,
   `pending_x_lim`, `pending_y_lim`) with `Cond_.Always`.
2. **Linked X:** the hovered cell becomes the `_driver` and publishes its X range to
   `state.shared_x`; followers lock to it. Every time-series cell also publishes its own
   range to `state.plot_x_ranges[plot_n]` (used by analysis windows' "follow plot_N").
3. **Downsample** each signal to `max_points` over the visible window
   (`downsample_xy`) — this is what keeps multi-GB logs interactive.
4. Draw it (line/scatter/stairs), optionally with per-sample markers (`Spec.marker`),
   routing the left/right (secondary `ImAxis_.y2`) axis per signal.
5. **Cursors** (two `drag_line_x`) and **spy** (`drag_rect` + a `canvas_only` inset) draw
   on top. Their readouts and rectangles are computed cheaply and only recomputed on move.
6. **Zoom echo:** when a pan/zoom settles, `echo set_x_lim(plot_n, ...)`.

> **Performance landmine (documented in code):** cursor readouts originally used
> `np.interp`, which **up-casts the entire `float32` signal to `float64` on every call**
> — ~150 ms/frame on a 5 M-point log. It was replaced with an O(log n) `searchsorted`
> lookup (`_value_at`) that touches only the two bracketing samples.

---

## 7. Analysis windows ([panels/analysis.py](../src/uz_dataviewer/panels/analysis.py))

FFT and Histogram share `AnalysisPanel`. Subclasses set a command `prefix`
(`fft`/`hist`) and a `compute_command`, then implement `_compute`, `_draw`,
`_options_key`, and any `_extra_controls`. The base provides:

- A **sources list** fed by drag-drop (`*_source` command) and the legend "Remove"
  (`*_remove`).
- A **time-window selector** (`follow_combo`): `Custom` (`0`), `Full` (`-1`), or
  `plot_N` (`≥1`), resolved by `AppState.resolve_x_window`. Switching to a plot computes
  immediately; switching to Custom/Full does **not** (the window can be the whole log).
- **On-demand compute only** — never per frame. A compute happens on the *Compute* button,
  on a drag-in, or once when an input changes (`compute_requested`). Following a plot and
  then panning it goes **stale** rather than recomputing.
- A **stale indicator**: a `_computed_key` snapshot (sources + window + options) is compared
  to the current key each frame; mismatch shows "⚠ stale - press Compute".
- **Every control routed through commands** (`fft_follow`, `fft_remove_dc`, `hist_bins`,
  `*_xlim` on zoom, `*_export`, …) and **Export** (OS dialog on desktop, browser download on web).

This is why "absolutely everything is a command" holds for the analysis windows too.

---

## 8. Downsampling ([downsample.py](../src/uz_dataviewer/downsample.py))

Two layers, because per-frame cost matters on multi-GB logs:

- **One-shot (`downsample_xy`)** — crops to the visible window, then decimates to
  `max_points` with `tsdownsample` MinMax-LTTB (or a pure-NumPy fallback on web). Cost is
  **O(visible points)**: fine for small signals/zoomed-in views, but re-scanning tens of
  millions of points *every frame* is what made a 5 GB log drop to ~13 fps.
- **Multi-resolution pyramid (`Pyramid`)** — the primary path for large signals
  (`> PYRAMID_MIN_POINTS`). Built **once per signal on first display** (lazily, cached on
  `Signal.pyramid`): geometric min/max levels (bucket sizes `64, 512, 4096, …`), each
  aggregated from the previous, so the build is O(n). At query time the finest level whose
  density fits `max_points` is sliced to the window and expanded into a min/max envelope.
  Per-frame cost is **O(output)** — independent of signal length.

> Measured on 50 M points (≈5 GB log scale): per-frame decimation **~17 ms → 0.012 ms**
> (~1300×), build ~96 ms once, pyramid memory ~3.6 % of the signal. X is **not** stored —
> bucket positions map to raw indices, so X is read from the run's `time` axis at query
> time (and the pyramid is unaffected by time normalization).

This is also why the design stays true to immediate mode: the pyramid makes per-frame work
genuinely cheap, so the renderer re-decimates every frame (no result caching) while staying
smooth — the expensive structure is built once, like loading the file.

---

## 9. Sessions ([session.py](../src/uz_dataviewer/session.py))

Two complementary formats:

- **JSON snapshot** (`save_state`/`load_state`) — the exact view (grid, assignments,
  plot types, cursors/spy, secondary axes, FFT/Histogram config, time origins, file list).
  Restore reloads files then resolves assignments **by run label** (not id).
- **`.uzscript`** (`export_script`/`run_script`) — a human-readable, editable list of
  commands that reproduces the session when replayed. Normalised loads round-trip as
  `load(path, start)`.

CSV exports (`export_data`, `export_fft`, `export_histogram`) also live here.

---

## 10. Native vs Web ([webbridge.py](../src/uz_dataviewer/webbridge.py))

The same Python runs on the desktop and in the browser via Pyodide (CPython→WASM).
`webbridge.IS_WEB` gates the differences:

| Concern | Native | Web |
|---|---|---|
| File open | OS dialog (`portable_file_dialogs`) | hidden HTML `<input type=file>` |
| Loading | async on a `ThreadPoolExecutor` | synchronous (no worker threads) |
| Large CSV | Arrow reads the whole file | **stream-parsed into typed arrays** (`load_columns`) so the multi-GB text never sits in wasm32 memory |
| Downsampler | Rust `tsdownsample` | pure-NumPy fallback (no WASM wheel) |
| Export / Save | OS save dialog | `webbridge.download` (Blob + anchor click); session menu disabled |

The hard ceiling is wasm32's ~4 GB address space: the *numeric* data must fit
(`rows × channels × 4` bytes), far below the raw CSV size. See **[BUILD.md](BUILD.md)**.

---

## 11. Extending the app

**Add a command** — register it in `register_builtins` ([commands.py](../src/uz_dataviewer/commands.py)):
```python
def my_action(state, a):
    plot_n, value = a
    state.cells[plot_n - 1].something = value
reg.add("my_action", [Param("plot", "plot"), Param("value", "float")], my_action, "help text")
```
Then have the widget call `state.commands.execute(state, "my_action", [plot_n, value])`
(via the panel's `_emit`) on change. Persist it in `session.py` if it should be saved.

**Add a time-series option** — add a field to `SubplotCell`, a command to toggle it, a
checkbox in `PlotsPanel._cell_header` that emits the command, the rendering in
`_render_time_series`, and the session round-trip.

**Add an analysis window** — subclass `AnalysisPanel`, set `prefix`/`compute_command`,
implement `_compute`/`_draw`/`_options_key`/`_extra_controls`; register the per-type
commands (the common ones come from `_register_analysis_common`); add a `DockableWindow`
in `app.py` and a config dataclass + serialisation.

**Add a plot type** — extend `PlotType`, branch in `PlotsPanel._render_cell`, and update
`session.py` if it carries extra per-cell state.

---

## 12. Testing

Tests are pure `pytest`, no real window. Two patterns:

- **Logic via commands** — dispatch command strings against an `AppState` and assert on
  state (e.g. [test_commands.py](../tests/test_commands.py), [test_session.py](../tests/test_session.py)).
- **Headless rendering** — create an ImGui/ImPlot context, set a backend-textures flag,
  and drive a few frames calling `panel.render(state)` (e.g.
  [test_plot_types.py](../tests/test_plot_types.py)). This exercises the real ImPlot calls
  (begin/end pairing, Spec markers, drag tools) without a GPU window. Destroy the contexts
  in a `finally` so tests don't leak across modules.

Run: `pytest` from the project root.

---

## 13. Design decisions, in brief

| Decision | Why |
|---|---|
| Single `AppState`, panels as renderers | One source of truth; trivial to serialise and test; no scattered widget state. |
| Command layer is the only mutation path | Scriptability, console transcript, save/restore-by-replay, and headless testing all derive from it. |
| Gestures **echo**, discrete actions **execute** | Zoom/drag are continuous; echoing once on settle keeps the console readable while staying replayable. |
| Reuse `tsdownsample`, not `plotly_resampler` | The only part of the old viewer reusable with ImPlot. |
| Min/max **pyramid** for large signals | Per-frame decimation becomes O(output), not O(visible points), so multi-GB logs pan at full fps — built once at first view, ~3.6% memory overhead. |
| FFT/Histogram are windows, on-demand | Per-frame transforms of a large window would tank the frame rate; explicit Compute keeps it snappy. |
| `searchsorted` not `np.interp` for cursors | `np.interp` up-casts the whole array each call — catastrophic per frame. |
| Session refs by run **label** | Run ids are reassigned on reload; labels survive. |
| Per-log time normalization keeps `time_raw` | Reversible, cheap (recompute on change only), and signals are never touched. |
| Web: stream-parse CSV → arrays | Avoids holding multi-GB text in 32-bit WASM memory; loads full resolution. |
| Pending-flag pattern (`fit_pending`, `compute_requested`, …) | The immediate-mode way to express "do X once next frame". |
