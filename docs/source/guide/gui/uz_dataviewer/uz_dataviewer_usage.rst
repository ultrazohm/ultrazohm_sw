.. _uz_dataviewer_usage:

===========
Usage guide
===========


JavaScope interaction
=====================

``uz_dataviewer`` is designed to work with the data logged by the UltraZohm hardware and the :ref:`JavaScope` software.
:ref:`JavaScope` is for *running an experiment*: connect, trigger, observe live, tune parameters, and record.
``uz_dataviewer`` is for *understanding the recording afterwards*: open one or many logs, arrange subplots, zoom into gigabyte-scale data, run FFTs.

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
         Log_*.csv  ──────────────┬───────────────► Matlab (JS_plot_data.m), Python (uz_dataviewer.read())
                                  │
                                  ▼
                    ┌────────────────────────────┐
                    │  (uz_dataviewer)           │  Data inspection, FFT, analysis
                    └────────────────────────────┘


Loading data
============

- **Navigation ▸ Open file(s)…** loads ``.csv`` (JavaScope ``;``-separated **or** standard ``,``-separated — the delimiter is auto-detected) and ``.parquet``, multiple at once. On the desktop you can also drag ``.csv``/``.parquet`` files onto the window.
- Expand a run to see its channels. The checkbox (de)activates a run; right-click ▸ **Remove run** drops it.
- **Per-log time normalization:** right-click a run ▸ tick **Normalize start time** and enter a start (default ``0``), then **Apply**. This shifts that log's time axis without touching the samples; untick to restore. (Also ``load("Log.csv", 0)``.)
- **Large logs:** channels load compactly and large Parquet files stream in, so a multi-million-sample log opens at roughly its in-memory size. A **very large CSV is refused** (parsing it whole would risk running out of memory) with a message pointing you to convert it once: ``convert("Log.csv")`` in the console, or ``uz-dataviewer convert Log.csv`` from a shell — both write a ``.parquet`` beside the source that loads leanly. (Native; the browser build is bounded by its ~4 GB limit — see :doc:`uz_dataviewer_native_vs_web`.)

Window types
============

The center area holds four window types, shown as dockable tabs:

- :ref:`uz_dataviewer_plot_window`
- :ref:`uz_dataviewer_fft_window`
- :ref:`uz_dataviewer_histogram_window`
- :ref:`uz_dataviewer_nodes`

.. _uz_dataviewer_plot_window:

Plot window
===========

- **Drag** a channel from the tree onto a plot cell to add it.
- **Layout** toolbar sets the grid (``1x1`` default … ``2x2``, ``3x1``, …).
- **Type** (per cell): ``line`` / ``scatter`` / ``stairs`` / ``xy`` (one signal vs another — pick the X signal in the cell header, and a **style** dropdown selects ``Line`` / ``Markers`` / ``Both``). Time-series types preserve spikes when downsampling; ``xy`` uses a plain stride, so a very dense phase plot can alias.
- **Link X axes** (toolbar): pan/zoom one subplot and the others follow. **Any** plot you pan/zoom drives the shared range — there is no master plot; all linked plots show the same time window.
- **Max points** (toolbar, with a quick-pick presets dropdown): the per-signal drawing budget — the visible window is drawn with about this many points and stays ~constant as you zoom. "downsampling: **active**" means the view is decimated; it switches to "**off (all samples)**" once the visible window holds fewer **raw samples** than Max points. The cell header shows ``~N pts shown (M in view)`` so you see both the drawn budget and the raw samples in the window.
- **Reset view** auto-fits the cell to its data; **Clear** empties it.
- **Right axis:** right-click a signal in the legend ▸ **Right axis** to put it on its own (secondary Y) scale.
- **samples** — a marker at every sample. **spy** — drag a rectangle on the plot; the inset below shows just that region (its line colours match the main plot). **cursors** — two draggable vertical lines with a Δx / frequency / Δy readout. Enabling **cursors**/**spy** places them at 25 % / 75 % of the *current* view, so they always start on-screen.
- **Export** writes the cell's signals over its current X window to CSV; tick **start at 0** to rebase the time column. (The export is comma-separated and re-imports cleanly. On a log already time-normalized to 0, the start is 0 either way.)

For all plots: the mouse wheel zooms, right-click and drag draws a zoom rectangle, hold **Shift** to zoom only X, hold **Alt** to zoom only Y. Right-click an axis for more options.

.. _uz_dataviewer_fft_window:

FFT window
==========

#. **Drag signals in** (from the tree or a plot) to overlay several.
#. **Window** selector — choose the time window:

   - ``plot_N`` — follow that subplot's current X range (computes immediately),
   - ``Full`` — the whole record,
   - ``Custom`` — type ``t min`` / ``t max``.

   Switching to ``Full`` / ``Custom`` does **not** auto-compute (the window may be huge).
#. Press **Compute**. If settings changed since the last compute you'll see **⚠ stale - press Compute**.
#. **Options:** **Remove DC**, **Hann window**, **log x** / **log y**.
#. **Export** writes the spectrum to CSV (``frequency,<sig>…``).

.. _uz_dataviewer_histogram_window:

Histogram window
================

The Histogram window works exactly like the :ref:`uz_dataviewer_fft_window`: drag signals in, pick the time window, press **Compute**, and **Export** (``bin_center,<sig>…``).
Its only option is the number of **bins**.

.. _uz_dataviewer_nodes:

Nodes (transforms → derived signals)
====================================

The **Nodes** window is a dataflow canvas: build a small graph that turns signals into **new signals**, which then appear in Navigation and can be dragged into any plot / FFT / Histogram like a loaded channel.

#. **Add a source** — drag a channel from Navigation **onto the canvas**; a source node wraps that signal at the drop point (or ``node_source(run, signal)``). Tick **crop time** on the node to use only a ``t min … t max`` window instead of the full record.
#. **Add a transform** — toolbar ``+ fft`` / ``+ math`` / ``+ filter`` / ``+ shift``:

   - **fft** — amplitude spectrum (its output's x-axis is frequency); options *remove DC*, *Hann*.
   - **math** — ``scale`` / ``offset`` (with a constant *k*), ``derivative``, ``integral``, ``reciprocal`` (1/A) (one input), or ``A+B`` / ``A-B`` / ``A*B`` / ``A/B`` (two inputs of equal length).
   - **filter** — windowed-sinc FIR *low* / *high* / *band* pass; set *cutoff* (Hz), *cutoff2* for band, and *taps* (more = sharper).
   - **shift** — offset the signal's time axis by a constant (``by`` seconds).
#. **Wire it** — drag from a node's **out** pin to another node's **in** pin. You can chain transforms (e.g. *filter → fft*).
#. **Evaluate** — the toolbar **Evaluate** (whole graph) or a node's **eval** button computes on demand and materializes each transform's result as a derived run named ``node_<id>``. Edit anything and the node shows **(stale)** until re-evaluated.
#. **Use the result** — the derived ``node_<id>`` appears in Navigation; drag its ``out`` channel into a plot, or feed it to the FFT / Histogram windows.

Everything here is a command (``node_*``), so a graph is fully scriptable and saved with the session.
**Double-click a node** to rename it inline; its derived signal takes the new name (or ``node_rename(node, name)``).

**Custom transforms (plugins):** you can add your own node kinds by dropping a small Python file in a plugin folder — see :doc:`uz_dataviewer_plugins`.

Console & scripting
===================

Every action is echoed to the **Console** as a canonical command (``> add_signal(plot_1, run_1, ia)``, and ``> set_x_lim(plot_1, 1.2, 1.8)`` when you zoom).
The input box runs the same commands:

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

The **Arguments** column lists each parameter as ``name:kind``; optional ones are bracketed
(``[start:float]``). The argument *kinds* are: ``plot`` = ``plot_N``; ``run`` = ``run_N`` or a
file label; ``fwindow`` = ``custom`` / ``full`` / ``plot_N``; ``bool`` = ``on``/``off`` (or
``true``/``false``); the rest are ``int`` / ``float`` / ``str``.

.. csv-table:: uz_dataviewer console commands
   :file: uz_dataviewer_commands.csv
   :header-rows: 1
   :widths: 16 12 34 22 16

This table is generated from the live command registry (``python -m uz_dataviewer.command_doc``),
and ``help`` prints the same list in the console, so both stay current.
