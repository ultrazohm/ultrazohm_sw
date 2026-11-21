.. _ultrazohm_dataviewer_usage:

===========
Usage guide
===========


JavaScope interaction
=====================

``ultrazohm_dataviewer`` is designed to work with the data logged by the UltraZohm hardware and the :ref:`JavaScope` software.
:ref:`JavaScope` is for *running an experiment*: connect, trigger, observe live, tune parameters, and record.
``ultrazohm_dataviewer`` is for *understanding the recording afterwards*: open one or many logs, arrange subplots, zoom into gigabyte-scale data, run FFTs.

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
         Log_*.csv  ──────────────┬───────────────► Matlab (JS_plot_data.m), Python (ultrazohm_dataviewer.read())
                                  │
                                  ▼
                    ┌────────────────────────────┐
                    │  (ultrazohm_dataviewer)           │  Data inspection, FFT, analysis
                    └────────────────────────────┘


Loading data
============

- **Navigation ▸ Open file(s)…** loads ``.csv`` (JavaScope ``;``-separated **or** standard ``,``-separated — the delimiter is auto-detected) and ``.parquet``, multiple at once. You can also drag ``.csv``/``.parquet`` files onto the window.
- Expand a run to see its channels. The checkbox (de)activates a run; right-click ▸ **Remove run** drops it.
- **Per-log time normalization:** right-click a run ▸ tick **Normalize start time** and enter a start (default ``0``), then **Apply**. This shifts that log's time axis without touching the samples; untick to restore. (Also ``load("Log.csv", 0)``.)
- **Large logs:** desktop lazy loading reads raw windows without retaining the complete recording. In-memory CSV loading enforces a numeric-data budget. Convert CSV to Parquet for faster repeated access, using ``viewer.convert("Log.csv")`` or ``ultrazohm-dataviewer convert Log.csv`` against an open viewer.

Settings
--------

The **Settings** menu opens a non-modal window with **General**, **Data loading**, and **Performance** sections.
Changes persist as application defaults; each section can be reset independently.
General includes the log browser directory and startup visibility of Application log and Python.
Leave the directory empty to use the firmware checkout's ``artifacts`` directory.
Startup visibility takes effect on the next launch; other changes apply immediately.

Settings are stored in ``viewer_preferences.json`` in the platform user data directory, separately from session files and device configuration.
Loading a session restores its own data and plot settings without changing saved defaults.
The Python client exposes the same service through ``viewer.get_settings()`` and ``viewer.set_setting("cache_budget", 512)``.

Backend and loading mode
------------------------

The **Backend** selector in **Settings → Data loading** chooses **PyArrow** or **Polars** for subsequently opened recordings.
The independent **Loading** selector chooses **In memory** or **Lazy**.
Changing either setting leaves already loaded recordings unchanged.
CSV selections larger than 1 GiB show a conversion recommendation for drag-and-drop, the Log Browser and the file picker.
**Open CSV** reads the original directly without automatic cached conversion.
**Convert to Parquet** writes a sibling file with the same stem and a ``.parquet`` extension in the background, then opens it using the selected backend and loading mode.
Existing Parquet files are protected from overwriting; the dialog offers **Open existing Parquet** instead.
**Cancel** skips the selected file, and multi-file selections are prompted individually.

The shared timestamp and summary cache defaults to **1,024 MiB** and remains configurable with **Settings → Performance → RAM cache (MiB)**.
This is a retained-cache budget, not a limit on total application RAM.
The status bar shows retained RAM cache usage next to FPS.
The Data Viewer never uses GUI idle throttling: live, paused, and offline views continue rendering without mouse or keyboard input.
An amber **cache limit hit** indication appears for five seconds after an entry is evicted or a result exceeds the cache capacity.
Hover over it to see eviction and oversized-result counts since the last cache clear.
Auto loading and the obsolete memory-budget controls have been removed; recreate old sessions with explicit loading settings.
The application defaults to **Polars + Lazy**.
The Log Browser's **Open lazy** and **Open in-memory** actions use the selected backend.
A loaded run's context menu shows its backend.
CSV conversion and CSV exports use the currently selected backend.
JSON sessions retain the backend and storage mode for each file.

A single ``time`` or ``frequency`` column selects the independent axis automatically.
FFT exports reopen with frequency semantics. For other column names, or if both names
are present, the GUI asks for the independent column and its domain (seconds or Hz).
Python automation passes ``axis_column="seconds", axis_domain="time"`` to
``read()``, ``viewer.load()`` or ``viewer.convert()``. Terminal control uses
``ultrazohm-dataviewer load file.csv --axis-column seconds --axis-domain time``.
Parquet conversion and JSON sessions preserve this choice. Existing schema-6 sessions
without axis fields retain their former time/first-column choice.


.. code-block:: bash

   ultrazohm-dataviewer gui --backend polars --loading-mode lazy
   ultrazohm-dataviewer gui --backend pyarrow --loading-mode memory
   # In a second terminal, control the running viewer:
   ultrazohm-dataviewer backend polars
   ultrazohm-dataviewer convert path/to/log.csv

The Python client equivalents are ``viewer.backend("polars")``, ``viewer.loading_mode("lazy")`` and ``viewer.load("path/to/log.parquet")``.
The headless library accepts ``uz.read(path, backend="polars")``; its dataframe conversion returns a Polars DataFrame when that backend is selected.
The default library backend preserves the existing pandas DataFrame interface.
Polars uses its native streaming reader and writer; CSV conversion can use more RAM than PyArrow.
Disk caching is disabled by default; indexes and summaries stay in RAM, and lazy CSV files are scanned directly.
Enable **Settings → Data loading → Disk cache**, ``--disk-cache`` or ``viewer.disk_cache(True)`` to reuse disk summaries and converted CSVs across restarts.
The setting affects newly opened files; reopen existing files to apply it.
When enabled, the application cache is stored in the selected workspace under ``artifacts/_user/viewer_cache``, unless overridden by ``UZ_DATAVIEWER_CACHE``.
Polars stores its disk caches in a separate ``polars/`` subdirectory, and the engines have distinct in-memory cache identities.

Local log browser
-----------------

The desktop **Log Browser** window is docked below Navigation in the default layout.
It starts at the checkout's ``javascope/`` directory when available, otherwise at ``javascope/`` beneath the working directory.
Use **Open directory...** to choose another root directory and **Refresh** to rescan it.
The flat list includes only ``.csv`` and ``.parquet`` files from that directory and its subdirectories, with relative paths to distinguish duplicate filenames.
Right-click a row and choose **Open lazy** or **Open in-memory** to select the mode for that file without changing the default loading mode.
Alternatively, drag a row anywhere inside the **Navigation** pane to open it.
The selected loading mode applies just as it does when opening a file through the dialog.
Scanning runs in the background and does not load measurement data.
The directory selection lasts for the current application session.
Existing saved window layouts are preserved; the Log Browser can be moved and docked like the Console.

Window types
============

The center area holds four window types, shown as dockable tabs:

- :ref:`ultrazohm_dataviewer_plot_window`
- :ref:`ultrazohm_dataviewer_fft_window`
- :ref:`ultrazohm_dataviewer_histogram_window`
- :ref:`ultrazohm_dataviewer_nodes`

.. _ultrazohm_dataviewer_plot_window:

Plot window
===========

- **Drag** a channel from the tree onto a plot cell to add it.
- **Layout** toolbar sets the grid (``1x1`` default … ``2x2``, ``3x1``, …).
- **Type** (per cell): ``line`` / ``scatter`` / ``stairs`` / ``xy`` (one signal vs another — pick the X signal in the cell header, and a **style** dropdown selects ``Line`` / ``Markers`` / ``Both``). Time-series types preserve spikes when downsampling; ``xy`` uses a plain stride, so a very dense phase plot can alias.
- **Link X axes** (toolbar): pan/zoom one subplot and the others follow. **Any** plot you pan/zoom drives the shared range — there is no master plot; all linked plots show the same time window.
- **Max points** (toolbar, with a quick-pick presets dropdown): the per-signal drawing budget — the visible window is drawn with about this many points and stays ~constant as you zoom. "downsampling: **active**" means the view is decimated; it switches to "**off (all samples)**" once the visible window holds fewer **raw samples** than Max points. The cell header shows ``~N pts shown (M in view)`` so you see both the drawn budget and the raw samples in the window.
- **Reset view** auto-fits the cell to its data; double-left-clicking a plot or axis performs the same reset. The toolbar's Reset view resets all subplots. **Clear** empties the cell.
- **Right axis:** right-click a signal in the legend ▸ **Right axis** to put it on its own (secondary Y) scale.
- **samples** — a marker at every sample. **spy** — drag a rectangle on the plot; the inset below shows that region for primary (left) Y-axis signals only (its line colours match the main plot). Right-axis signals are excluded. **cursors** — two draggable vertical lines with a Δx / frequency / Δy readout. Enabling **cursors**/**spy** places them at 25 % / 75 % of the *current* view, so they always start on-screen.
- **Export** writes the cell's signals over its current X window to CSV; tick **start at 0** to rebase the time column. (The export is comma-separated and re-imports cleanly. On a log already time-normalized to 0, the start is 0 either way.)

For all plots: the mouse wheel zooms, right-click and drag draws a zoom rectangle, hold **Shift** to zoom only X, hold **Alt** to zoom only Y. Right-click an axis for more options.

In **Live Plots**, **Reset view** and double-left-click also enable **Follow live** again, catch up to the newest samples, and keep the selected **Time depth (s)**.
Unchecking **Follow live**, horizontal panning, or Shift-modified wheel/box zoom freezes the displayed snapshot; acquisition and logging continue.
Checking **Follow live** resumes display updates.
Ordinary wheel and box zoom keep following.

.. _ultrazohm_dataviewer_fft_window:

FFT window
==========

#. **Drag signals in** (from the tree or a plot) to overlay several.
#. **Window** selector — choose the time window:

   - ``plot_N`` — follow that subplot's current X range (computes immediately),
   - ``Full`` — the complete time extent of all selected recordings,
   - ``Custom`` — type ``t min`` / ``t max``.

   Switching to ``Full`` / ``Custom`` does **not** auto-compute (the window may be huge).
#. Press **Compute**. If settings changed since the last compute you'll see **⚠ stale - press Compute**.
#. **Options:** **Remove DC**, **Hann window**, **log x** / **log y**.
#. **Export** writes the spectrum to CSV (``frequency,<sig>…``).

.. _ultrazohm_dataviewer_histogram_window:

Histogram window
================

The Histogram window works exactly like the :ref:`ultrazohm_dataviewer_fft_window`: drag signals in, pick the time window, press **Compute**, and **Export** (``bin_center,<sig>…``).
Its only option is the number of **bins**.

.. _ultrazohm_dataviewer_nodes:

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

**Custom transforms (plugins):** you can add your own node kinds by dropping a small Python file in a plugin folder — see :doc:`ultrazohm_dataviewer_plugins`.

Python and terminal automation
==============================

The viewer listens on ``127.0.0.1:19741`` by default.
Open the project environment with ``./uz venv dev`` and control the existing viewer:

.. code-block:: python

   from ultrazohm_dataviewer import Client
   viewer = Client()
   run = viewer.load("Log.csv")
   viewer.set_grid(2, 2)
   viewer.add_signal(1, run, "ia")
   viewer.save_session("analysis.json")

The same operations are available as terminal subcommands, for example ``ultrazohm-dataviewer set-grid 2 2``.
Use ``--endpoint`` to select another instance and ``--json`` for machine-readable output.
Python uses ``UZ_DATAVIEWER_ENDPOINT`` when no endpoint is specified.
Handles identify recordings, nodes, and views within a session.
Use ``view=viewer.create_view()`` to target an additional grid.

**View → Python** opens an editor for normal Python files, available without a device connection.
Run saves and executes in a fresh process.
Managed device runs also receive ``UZ_ACQUISITION_ENDPOINT`` and provide **Stop script + device**.
The application log is read-only; the old command language and ``.uzscript`` are removed.
External terminals and IDEs use the same client API.

Save and restore
----------------

JSON schema 6 captures recordings, nodes, analysis settings, and plot views.
Recording paths resolve relative to the snapshot.
Saving is atomic and loading is transactional.
Use ``viewer.save_session(path)`` and ``viewer.load_session(path)``.
Python interpreter variables and running processes are not saved.

Public method reference
=======================

Methods accept ordinary Python values and session-scoped handles.
The table is generated from the client signatures with ``python -m ultrazohm_dataviewer.command_doc``.

.. csv-table:: Python viewer API
   :file: ultrazohm_dataviewer_commands.csv
   :header-rows: 1
   :widths: 18 14 40 28

Session compatibility and analysis windows
------------------------------------------

Failed restoration preserves the current session.
Recordings without a backing file (live snapshots, node outputs) must be exported as data before saving a reloadable session.
Transforms must be chained through node links, not by creating source nodes from derived outputs.

Python scripts obtain a derived recording handle with ``viewer.node_output(node)`` after evaluating the node.

Saved sessions use schema version 6 and preserve separate instances of logs with identical filenames or paths.
Restoring a session replaces the currently loaded session.
Version 1/2/3/4/5 snapshots and all generated session scripts must be recreated as JSON sessions.
Generated script export has been removed.
Histogram, FFT, export and node crop ranges include only samples inside the selected time window.
FFT and FIR filters require strictly increasing, uniformly spaced timestamps (100 ppm tolerance plus floating-point roundoff).
Binary math requires matching time axes throughout both inputs.
Unsupported sampling is rejected without interpolation.
FFT export rejects an invalid selected channel with its name and reason before writing any output.
Applied primary and secondary Y limits, including mouse zoom, survive saving and restoring.
Recomputing node outputs preserves their time normalization.
Shrinking the grid switches analysis windows following removed plots to Full.

XY alignment and invalid results
--------------------------------

XY inputs must have equal lengths and matching displayed timestamps, including any per-run normalization.
Mismatches are rejected instead of pairing unrelated samples.
XY zoom and explicit X/Y limits survive JSON round trips; XY coordinates never drive linked time axes.

Changed source files must be reopened, including CSV files opened through a disk-cached Parquet conversion.
Stale or failed node outputs keep their signal assignments, including across JSON restoration, but are unavailable to plots, analysis and exports until successful reevaluation.
Fix the graph and evaluate it to repopulate the existing assignments.
