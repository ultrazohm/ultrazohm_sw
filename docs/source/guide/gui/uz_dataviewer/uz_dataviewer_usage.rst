.. _uz_dataviewer_usage:

===========
Usage guide
===========

Features
========

- **Load many files** — ``.csv`` (JavaScope ``;`` *or* standard ``,``, auto-detected) and ``.parquet``, read with Apache Arrow. Open via the button or **drag files onto the window** (desktop).
- **Matlab-style navigation** — runs → channels, (de)activate/remove, **per-log time normalization**.
- **Subplot grid** — drag-and-drop signals, runtime layout, types line/scatter/stairs/**XY**, **linked X axes**, **secondary Y axis**, **cursors**, **spy** zoom inset, **show samples**, per-cell **CSV export**.
- **Range-aware downsampling** — a min/max pyramid (pure NumPy) for time series; multi-GB logs pan at full fps and zoom reveals detail. XY plots decimate by plain stride.
- **FFT & Histogram windows** — overlay several signals, pick the time window (follow a plot / full / custom), compute on demand, log axes, CSV export.
- **Node canvas** — drag a signal into a graph, apply transforms (FFT / math / filter / shift), and the result becomes a new draggable signal. Fully scriptable (``node_*``) and extensible with Python plugin nodes (see :doc:`uz_dataviewer_plugins`).
- **Scriptable command console** — every action echoes a command; the input runs them, with completion, history and a selectable log. Sessions save to JSON or a replayable ``.uzscript``.
- **MaterialFlat theme.** Runs natively (Windows/Linux/macOS) and in the browser (Pyodide/WASM).



``uz_dataviewer`` is designed to work with the data logged by the UltraZohm hardware and :ref:`JavaScope` software.

.. code-block:: text

      UltraZohm hardware
           │  TCP :1000  (live stream, 20 ch)
           ▼
    ┌──────────────────────┐     commands / parameters
    │  JavaScope (Java)     │ ───────────────────────────►  back to device
    │  live scope + control │
    └──────────┬───────────┘
               │ writes
               ▼
         Log_*.csv  ──────────────┬───────────────► JS_plot_data.m (Matlab import), Python import
                                  │
                                  ▼
                    ┌────────────────────────────┐
                    │  (uz_dataviewer)           │  Data inspection, FFT, analysis
                    └────────────────────────────┘

- **JavaScope** is for *running an experiment*: connect, trigger, observe live, tune parameters, and record.
- **Data Viewer** is for *understanding the recording afterwards*: open one or many logs, arrange subplots, zoom into gigabyte-scale data, run FFTs.

Launching
=========

.. code-block:: bash

   cd uz_dataviewer
   pip install -r requirements.txt                          # or: pip install -e .
   python run.py                                            # or: python -m uz_dataviewer
   python run.py ../javascope/Log_2026-06-11_22-45-16.csv   # preload file(s)
   python run.py session.uzscript                           # replay a saved session at startup

The window has dockable panels — **Navigation** (left), **Plots / FFT /Histogram / Nodes** (center, as tabs), and **Console** (bottom) — which you can rearrange.

Loading data
============

- **Navigation ▸ Open file(s)…** loads ``.csv`` (JavaScope ``;``-separated **or** standard ``,``-separated — the delimiter is auto-detected) and ``.parquet``, multiple at once. On the desktop you can also drag ``.csv``/``.parquet`` files onto the window to load them.
- Expand a run to see its channels. The checkbox (de)activates a run; right-click ▸ **Remove run** drops it.
- **Per-log time normalization:** right-click a run ▸ tick **Normalize start time** and enter a start (default ``0``), then **Apply**. This shifts that log's time axis without touching the samples; untick to restore. (Also ``load("Log.csv", 0)``.)
- **Large logs:** channels load as ``float32`` and large Parquet files stream in, so a multi-million-sample log opens at roughly its in-memory size. A **very large CSV is refused** (bulk CSV parsing would risk running out of memory) with a message pointing you to convert it once: ``convert("Log.csv")`` in the console, or ``uz-dataviewer convert Log.csv`` from a shell — both write a ``.parquet`` beside the source that loads leanly. (Native; the browser build is still bounded by its ~4 GB heap.)

Plots
=====

- **Drag** a channel from the tree onto a plot cell to add it.
- **Layout** toolbar sets the grid (``1x1`` default … ``2x2``, ``3x1``, …).
- **Type** (per cell): ``line`` / ``scatter`` / ``stairs`` / ``xy`` (one signal vs another — pick the X signal in the cell header, and a **style** dropdown selects ``Line`` / ``Markers`` / ``Both``). Time-series types use min/max downsampling that preserves spikes; ``xy`` decimates by plain stride, so a very dense phase plot can alias.
- **Link X axes** (toolbar): pan/zoom one subplot and the others follow. **Any** plot you pan/zoom drives the shared range — there is no master plot; all linked plots show (and decimate over) the same time window.
- **Max points** (toolbar, with a quick-pick presets dropdown): the per-signal downsample budget — the visible window is drawn as a min/max envelope of about this many points (it stays ~constant as you zoom). "downsampling: **active**" means the view is decimated; it switches to "**off (all samples)**" once the visible window holds fewer **raw samples** than Max points — on a multi-million-sample log that needs deep zoom. The cell header shows ``~N pts shown (M in view)`` so you can see both the drawn budget and the raw samples in the window.
- **Reset view** auto-fits the cell to its data; **Clear** empties it.
- **Right axis:** right-click a signal in the legend ▸ **Right axis** to put it on its own (secondary Y) scale.
- **samples** — a marker at every sample. **spy** — drag a rectangle on the plot; the inset below shows just that region (its line colours match the main plot).
  **cursors** — two draggable vertical lines with a Δx / frequency / Δy readout. Enabling **cursors**/**spy** places them at 25 %/75 % of the *current* view, so they always start on-screen.
- **Export** writes the cell's signals over its current X window to CSV; tick **start at 0** to rebase the time column. (The export is comma-separated and re-imports cleanly. Note: on a log already time-normalized to 0, the start is 0 with or without this option.)

FFT & Histogram windows
=======================

Both work the same way:

#. **Drag signals in** (from the tree or a plot) to overlay several.
#. **Window** selector — choose the time window:

   - ``plot_N`` — follow that subplot's current X range (computes immediately),
   - ``Full`` — the whole record,
   - ``Custom`` — type ``t min`` / ``t max``.

   Switching to ``Full``/``Custom`` does **not** auto-compute (the window may be huge).
#. Press **Compute**. If settings changed since the last compute you'll see **⚠ stale - press Compute**.
#. **FFT** options: **Remove DC**, **Hann window**, **log x** / **log y**. **Histogram** option: **bins**.
#. **Export** writes the result to CSV (FFT: ``frequency,<sig>…``; Histogram: ``bin_center,<sig>…``).

.. _uz_dataviewer_usage_nodes:

Nodes (transforms → derived signals)
====================================

The **Nodes** window is a dataflow canvas: build a small graph that turns signals into **new signals**, which then appear in Navigation and can be dragged into any plot / FFT / Histogram like a loaded channel.

#. **Add a source** — drag a channel from Navigation **onto the canvas**; a source node wraps that signal at the drop point (or ``node_source(run, signal)``). Tick **crop time** on the node to use only a ``t min … t max`` window instead of the full record.
#. **Add a transform** — toolbar ``+ fft`` / ``+ math`` / ``+ filter`` / ``+ shift``:

   - **fft** — amplitude spectrum (its output's x-axis is frequency); options *remove DC*, *Hann*.
   - **math** — ``scale``/``offset`` (with a constant *k*), ``derivative``, ``integral``, ``reciprocal`` (1/A) (one input), or ``A+B`` / ``A-B`` / ``A*B`` / ``A/B`` (two inputs of equal length).
   - **filter** — windowed-sinc FIR *low* / *high* / *band* pass; set *cutoff* (Hz), *cutoff2* for band, and *taps* (more = sharper).
   - **shift** — offset the signal's time axis by a constant (``by`` seconds).
#. **Wire it** — drag from a node's **out** pin to another node's **in** pin. You can chain transforms (e.g. *filter → fft*).
#. **Evaluate** — the toolbar **Evaluate** (whole graph) or a node's **eval** button computes on demand and materializes each transform's result as a derived run named ``node_<id>``. Edit anything and the node shows **(stale)** until re-evaluated.
#. **Use the result** — the derived ``node_<id>`` appears in Navigation; drag its ``out`` channel into a plot, or feed it to the FFT/Histogram windows.

Everything here is a command (``node_*``), so a graph is fully scriptable and saved with the session. **Double-click a node** to rename it inline.
Its derived signal takes the new name (or ``node_rename(node, name)``).

**Custom transforms (plugins):** you can add your own node kinds by dropping a small Python file in a plugin folder — see :doc:`uz_dataviewer_plugins`.

Console & scripting
===================

Every action is echoed to the **Console** as a canonical command (``> add_signal(plot_1, run_1, ia)``, and ``> set_x_lim(plot_1, 1.2, 1.8)`` when you zoom). The input box runs the same commands:

- type a command name for **completion** (matches listed below the box; **Tab** fills the first; **Up/Down** cycle history),
- ``help`` lists everything, ``help <name>`` shows one,
- the log body is **always selectable** (drag to mark, **Ctrl+C** to copy) and auto-scrolls.

.. code-block:: text

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

Plots are referenced ``plot_1..plot_N`` (row-major); runs as ``run_<id>`` or by filename.

Save / restore a session
------------------------

- **Session ▸ Save state… / Load state…** — exact JSON snapshot (grid, assignments, plot types, cursors/spy, secondary axes, FFT/Histogram config, time normalization, file list); restore reloads the files and rebuilds the view.
- **Session ▸ Export script… / Run script…** — an editable ``.uzscript`` of commands that reproduces the session when replayed.

Command reference
=================

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - Group
     - Commands
   * - Data / runs
     - ``load(path, [start])``, ``convert(src, [dst])``, ``remove_run(run)``,
       ``set_active(run, on)``, ``normalize_time(run, [start])``, ``reset_time(run)``
   * - Layout
     - ``set_grid(rows, cols)``, ``link_x(on)``, ``set_max_points(n)``
   * - Signals
     - ``add_signal(plot, run, signal)``, ``remove_signal(plot, run, signal)``,
       ``clear_plot(plot)``, ``set_plot_type(plot, type)``, ``set_xy(plot, run, signal)``,
       ``set_xy_style(plot, line|markers|both)``, ``set_axis(plot, run, signal, side)``
   * - View
     - ``set_x_lim(plot, min, max)``, ``set_y_lim(plot, min, max)``, ``reset_view(plot)``
   * - Tools
     - ``show_samples(plot, on)``, ``cursors(plot, on)``, ``set_cursors(plot, x1, x2)``,
       ``spy(plot, on)``, ``set_spy_rect(plot, xmin, ymin, xmax, ymax)``,
       ``export_data(plot, path, [relative])``, ``set_export_relative(plot, on)``
   * - FFT window
     - ``fft_source(run, signal)``, ``fft_remove(run, signal)``, ``fft_clear()``,
       ``fft_follow(custom|full|plot_N)``, ``fft_range(min, max)``, ``fft_remove_dc(on)``,
       ``fft_hann(on)``, ``fft_logx(on)``, ``fft_logy(on)``, ``fft_xlim(min, max)``,
       ``fft()``, ``fft_export(path)``
   * - Histogram window
     - ``hist_source(run, signal)``, ``hist_remove(run, signal)``, ``hist_clear()``,
       ``hist_follow(custom|full|plot_N)``, ``hist_range(min, max)``, ``hist_bins(n)``,
       ``hist_xlim(min, max)``, ``histogram()``, ``hist_export(path)``
   * - Nodes
     - ``node_source(run, signal)``, ``node_add(fft|math|filter|shift|…)``,
       ``node_set(node, key, value)``, ``node_link(src, dst)``, ``node_unlink(src, dst)``,
       ``node_remove(node)``, ``node_rename(node, name)``, ``node_pos(node, x, y)``,
       ``node_eval([node])``, ``load_plugins([dir])``
   * - Session
     - ``save_state(path)``, ``load_state(path)``, ``export_script(path)``,
       ``run_script(path)``
   * - Console
     - ``help([name])``, ``clear_console()``

(``help`` prints this list live from the registry, so it is always current.)

Web build differences
=====================

The browser build (GitLab/GitHub Pages, or ``build/build_web.sh``) runs the same UI, with a few platform limits: synchronous loading, large CSVs stream-parsed at full resolution, and Export plus Session save/restore via browser download and a hidden file picker (no OS dialog).
For all platform differences and the memory ceiling see :doc:`uz_dataviewer_native_vs_web`; for building the web artifact see :doc:`uz_dataviewer_build`.
