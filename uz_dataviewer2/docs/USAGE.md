# Usage guide

How to drive the UltraZohm Data Viewer. For internals see
**[ARCHITECTURE.md](ARCHITECTURE.md)**; for packaging see **[BUILD.md](BUILD.md)**.

---

## Launching

```bash
pip install -r requirements.txt      # or: pip install -e .
python run.py                        # or: python -m uz_dataviewer
python run.py ../javascope/Log_2026-06-11_22-45-16.csv   # preload file(s)
python run.py session.uzscript       # replay a saved session at startup
```

The window has five dockable areas — **Navigation** (left), **Plots / FFT /
Histogram / Nodes** (center tabs), **Console** (bottom) — which you can rearrange.

---

## Loading data

- **Navigation ▸ Open file(s)…** loads `.csv` (JavaScope `;`-separated **or** standard
  `,`-separated — the delimiter is auto-detected) and `.parquet`, multiple at once.
- Expand a run to see its channels. The checkbox (de)activates a run; right-click ▸
  **Remove run** drops it.
- **Per-log time normalization:** right-click a run ▸ tick **Normalize start time** and
  enter a start (default `0`), then **Apply**. This shifts that log's time axis without
  touching the samples; untick to restore. (Also `load("Log.csv", 0)`.)

---

## Plots

- **Drag** a channel from the tree onto a plot cell to add it.
- **Layout** toolbar sets the grid (`1x1` default … `2x2`, `3x1`, …).
- **Type** (per cell): `line` / `scatter` / `stairs` / `xy` (one signal vs another —
  pick the X signal in the cell header). Time-series types use min/max downsampling that
  preserves spikes; `xy` decimates by plain stride, so a very dense phase plot can alias.
- **Link X axes** (toolbar): pan/zoom one subplot and the others follow.
- **Max points** (toolbar): the per-signal downsample budget; "downsampling: active/off"
  tells you whether the current view is decimated. Zoom in to reveal more detail.
- **Reset view** auto-fits the cell to its data; **Clear** empties it.
- **Right axis:** right-click a signal in the legend ▸ **Right axis** to put it on its own
  (secondary Y) scale.
- **samples** — a marker at every sample. **spy** — drag a rectangle on the plot; the inset
  below shows just that region. **cursors** — two draggable vertical lines with a
  Δx / frequency / Δy readout.
- **Export** writes the cell's signals over its current X window to CSV; tick **start at 0**
  to rebase the time column. (The export is comma-separated and re-imports cleanly.)

---

## FFT & Histogram windows

Both work the same way:

1. **Drag signals in** (from the tree or a plot) to overlay several.
2. **Window** selector — choose the time window:
   - `plot_N` — follow that subplot's current X range (computes immediately),
   - `Full` — the whole record,
   - `Custom` — type `t min` / `t max`.
   Switching to `Full`/`Custom` does **not** auto-compute (the window may be huge).
3. Press **Compute**. If settings changed since the last compute you'll see
   **⚠ stale - press Compute**.
4. **FFT** options: **Remove DC**, **Hann window**, **log x** / **log y**. **Histogram**
   option: **bins**.
5. **Export** writes the result to CSV (FFT: `frequency,<sig>…`; Histogram: `bin_center,<sig>…`).

---

## Nodes (transforms → derived signals)

The **Nodes** window is a dataflow canvas: build a small graph that turns signals
into **new signals**, which then appear in Navigation and can be dragged into any
plot / FFT / Histogram like a loaded channel.

1. **Add a source** — drag a channel onto the `[ drop signal here -> +source ]`
   button (or it can be added by command). A source node wraps that signal.
2. **Add a transform** — toolbar `+ fft` / `+ math` / `+ filter`:
   - **fft** — amplitude spectrum (its output's x-axis is frequency); options
     *remove DC*, *Hann*.
   - **math** — `scale`/`offset` (with a constant *k*), `derivative`, `integral`
     (one input), or `A-B` / `A/B` (two inputs of equal length).
   - **filter** — windowed-sinc FIR *low* / *high* / *band* pass; set *cutoff* (Hz),
     *cutoff2* for band, and *taps* (more = sharper).
3. **Wire it** — drag from a node's **out** pin to another node's **in** pin. You can
   chain transforms (e.g. *filter → fft*).
4. **Evaluate** — the toolbar **Evaluate** (whole graph) or a node's **eval** button
   computes on demand and materializes each transform's result as a derived run
   named `node_<id>`. Edit anything and the node shows **(stale)** until re-evaluated.
5. **Use the result** — the derived `node_<id>` appears in Navigation; drag its `out`
   channel into a plot, or feed it to the FFT/Histogram windows.

Everything here is a command (`node_*`), so a graph is fully scriptable and saved
with the session. Rename a node to give its derived run a friendlier name.

## Console & scripting

Every action is echoed to the **Console** as a canonical command
(`> add_signal(plot_1, run_1, ia)`, and `> set_x_lim(plot_1, 1.2, 1.8)` when you zoom).
The input box runs the same commands:

- type a command name for **completion** (matches listed below the box; **Tab** fills the
  first; **Up/Down** cycle history),
- `help` lists everything, `help <name>` shows one,
- the log body is **always selectable** (drag to mark, **Ctrl+C** to copy) and auto-scrolls.

```text
load("Log.csv")                         # optional 2nd arg normalises the start time
set_grid(2, 2)
add_signal(plot_1, run_1, ia)           # run by id ...
add_signal(plot_2, Log.csv, Speed_rpm)  # ... or by file label
set_axis(plot_1, run_1, Speed_rpm, right)
cursors(plot_1, on)
fft_source(run_1, ia)                    # send to the FFT window
fft_follow(full)                         # analyse the whole record
fft()                                    # compute + focus the FFT window
export_data(plot_1, "out.csv", true)     # true = rebase start time to 0
```

Plots are referenced `plot_1..plot_N` (row-major); runs as `run_<id>` or by file name.

### Save / restore a session

- **Session ▸ Save state… / Load state…** — exact JSON snapshot (grid, assignments, plot
  types, cursors/spy, secondary axes, FFT/Histogram config, time normalization, file list);
  restore reloads the files and rebuilds the view.
- **Session ▸ Export script… / Run script…** — an editable `.uzscript` of commands that
  reproduces the session when replayed.

---

## Command reference

| Group | Commands |
|-------|----------|
| Data / runs | `load(path, [start])`, `remove_run(run)`, `set_active(run, on)`, `normalize_time(run, [start])`, `reset_time(run)` |
| Layout | `set_grid(rows, cols)`, `link_x(on)`, `set_max_points(n)` |
| Signals | `add_signal(plot, run, signal)`, `remove_signal(plot, run, signal)`, `clear_plot(plot)`, `set_plot_type(plot, type)`, `set_xy(plot, run, signal)`, `set_axis(plot, run, signal, side)` |
| View | `set_x_lim(plot, min, max)`, `set_y_lim(plot, min, max)`, `reset_view(plot)` |
| Tools | `show_samples(plot, on)`, `cursors(plot, on)`, `set_cursors(plot, x1, x2)`, `spy(plot, on)`, `set_spy_rect(plot, xmin, ymin, xmax, ymax)`, `export_data(plot, path, [relative])`, `set_export_relative(plot, on)` |
| FFT window | `fft_source(run, signal)`, `fft_remove(run, signal)`, `fft_clear()`, `fft_follow(custom\|full\|plot_N)`, `fft_range(min, max)`, `fft_remove_dc(on)`, `fft_hann(on)`, `fft_logx(on)`, `fft_logy(on)`, `fft_xlim(min, max)`, `fft()`, `fft_export(path)` |
| Histogram window | `hist_source(run, signal)`, `hist_remove(run, signal)`, `hist_clear()`, `hist_follow(custom\|full\|plot_N)`, `hist_range(min, max)`, `hist_bins(n)`, `hist_xlim(min, max)`, `histogram()`, `hist_export(path)` |
| Nodes | `node_source(run, signal)`, `node_add(fft\|math\|filter)`, `node_set(node, key, value)`, `node_link(src, dst)`, `node_unlink(src, dst)`, `node_remove(node)`, `node_rename(node, name)`, `node_pos(node, x, y)`, `node_eval([node])` |
| Session | `save_state(path)`, `load_state(path)`, `export_script(path)`, `run_script(path)` |
| Console | `help([name])`, `clear_console()` |

(`help` prints this list live from the registry, so it is always current.)

---

## Web build differences

The browser build (GitLab/GitHub Pages, or `build/build_web.sh`) runs the same UI, with a
few platform limits: synchronous loading, large CSVs stream-parsed at full resolution,
Export via browser download, and the Session-menu save/restore disabled (no OS dialog).
Details in **[BUILD.md](BUILD.md)**.
