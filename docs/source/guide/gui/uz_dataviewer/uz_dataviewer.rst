.. _uz_dataviewer:

========================
UltraZohm Data Viewer
========================

``uz_dataviewer`` is an ImGui/ImPlot desktop and web application for inspecting the ``Log_*.csv`` / ``.parquet`` logs that JavaScope records.
It does not talk to hardware — it reads files only — and is built to make multi-gigabyte logs fast and interactive.

.. code-block:: text

   +------------------------------------------------------------------+
   |  Navigation  |      Plots / FFT / Histogram  (docked tabs)       |
   |   (left)     |   Plots: runtime grid of subplots (1x1 ... 2x2)   |
   |  runs &      |   FFT / Histogram: dedicated analysis windows      |
   |  signals     |                                                    |
   |--------------+----------------------------------------------------|
   |                       Console  (bottom)                          |
   +------------------------------------------------------------------+

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
