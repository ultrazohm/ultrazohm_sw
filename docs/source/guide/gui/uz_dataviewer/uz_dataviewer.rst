.. _uz_dataviewer:

=============
uz_dataviewer
=============

``uz_dataviewer`` is a tool to inspect log files from measurements conduced using the UltraZohm.
Specifically, the ``Log_*.csv`` logs that the :ref:`JavaScope`  records can be read.
Additionally,  JavasScope logs that are converted to ``.parquet`` can be loaded, which is recommended for large logs.
``uz_dataviewer`` is based on `ImGUI bundle <https://github.com/pthom/imgui_bundle>`_, which in turn uses ImGui/ImPlot.
The Python API of ImGUI bundle is utilized.
``uz_dataviewer`` is available as a desktop and (local) web application.
Note that the binary is not distributed but has to be build by the user from source.
Detailed guidelines for building are given in :doc:`uz_dataviewer_build`.

The basic layout of  the application is as follows

.. code-block:: text

   +------------------------------------------------------------------+
   |  Navigation  |      Plots / FFT / Histogram  (docked tabs)       |
   |   (left)     |   Plots: runtime grid of subplots (1x1 ... 2x2)   |
   |  runs &      |   FFT / Histogram: dedicated analysis windows     |
   |  signals     |                                                   |
   |--------------+---------------------------------------------------|
   |                       Console  (bottom)                          |
   +------------------------------------------------------------------+

..  _uz_dataviewer_layout:

..  figure:: uz_dataviewer_currents.png
    :align: center
    :width: 500px

    Layout of ```uz_dataviewer``.

:numref:`uz_dataviewer_layout` shows the Layout of ```uz_dataviewer`` with data navigation (1),  window control (2), plot setup (3), subplot setup (4), console (5), and settings (6).
The data navigation is used to open log files.
Log files can be opened by clicking the *Open file(s)...* button or by dragging and dropping files onto the navigation panel (native only).
Individual signals of a log can be dragged and dropped into the plot area.
Right click on the log shows information and gives access to additional per-log settings, such as time normalization.
The window control (2) controls settings for the complete window, e.g., the plot, histogram, FFT, or Nodes window.
Windows can be closed, floated, docked as tabs and are resizable.
The window control (2) for the plot window gives access to, for example, the plot layout such as 1x1 or 2x1.
Settings of the window control (2) are global for the complete window.
The subplot setup (4) controls individual subplots and gives access to settings such as the plot type (line, scatter, stairs, XY), or secondary y-axis.
The console (5) shows the command log and allows to enter commands, which are also logged.
The settings (6) give access to application settings, such import and export of current application state (session) and settings the view (view), e.g., reset to default view.

For all plots, the following interactions are available: Mouse wheel zooms in and out, right-click and drag creates a zoom rectangle, right-click while holding shift only zooms the x-axis, while holding Alt only zooms the y-axis.
Right-clicking the x-axis or y-axis gives access to additional settings.

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

Quick start
===========

.. code-block:: bash

   pip install -r requirements.txt      # or: pip install -e .
   python run.py                        # or: python -m uz_dataviewer
   python run.py ../javascope/Log_2026-06-11_22-45-16.csv   # preload
   python run.py session.uzscript       # replay a saved session

Then **Open file(s)…** in the Navigation panel, expand the run, and drag signals into the plots (or the FFT / Histogram windows).

Project layout
==============

.. code-block:: text

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
   ├── docs/                     # USAGE / ARCHITECTURE / BUILD / NATIVE_VS_WEB / PLUGINS / ROADMAP
   └── build/                    # native (PyInstaller) + web (Pyodide) build flow

Tests
=====

.. code-block:: bash

   pip install pytest
   pytest

.. toctree::
   :maxdepth: 1
   :caption: User documentation

   uz_dataviewer_usage
   uz_dataviewer_build
   uz_dataviewer_library
   uz_dataviewer_plugins

.. toctree::
   :maxdepth: 1
   :caption: Design & internals

   uz_dataviewer_architecture
   uz_dataviewer_native_vs_web

.. toctree::
   :maxdepth: 1
   :caption: Roadmap & proposals

   uz_dataviewer_roadmap
   uz_dataviewer_nodes_future_ideas
   uz_dataviewer_web_large_logs
