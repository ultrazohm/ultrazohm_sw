.. _uz_dataviewer_native_vs_web:

=============
Native vs Web
=============

The same ``uz_dataviewer`` runs on the desktop **and** in the browser.
Native is a self-contained desktop application; web is a static page you open in a browser (Pyodide/WebAssembly).
The UI, plots, FFT/Histogram, nodes, scripting and downsampling are the **same** on both — only file access, loading speed, and the memory limit differ.
For building each target see :doc:`uz_dataviewer_build`; for the internals see :ref:`uz_dataviewer_arch_native_web`.

At a glance
===========

.. list-table::
   :header-rows: 1
   :widths: 20 40 40

   * - Concern
     - Native (desktop)
     - Web (browser)
   * - **Distribution**
     - One self-contained executable
     - A static web page (served over HTTP)
   * - **Open files**
     - OS file dialog, or drag files onto the window
     - **Open file(s)…** button (HTML file picker)
   * - **Loading**
     - In the background; the UI stays responsive
     - Blocks the tab until the file is parsed
   * - **Very large logs**
     - Limited only by your machine's RAM
     - Decimated on load above ~1.5 GB of data; full resolution below
   * - **Export / Save**
     - OS save dialog
     - Browser download (and a file picker to load sessions back)
   * - **Memory**
     - Your machine's RAM
     - Hard ~4 GB browser limit
   * - **Internet**
     - Not needed
     - **Needed at load** to fetch the runtime

File access
===========

On the desktop you open files via the OS dialog, or **drag** ``.csv`` / ``.parquet`` files onto the window.
A browser tab has no OS dialog, so **Open file(s)…** opens an HTML file picker instead.
Saving works the same way in reverse: native pops an OS save dialog, web triggers a **browser download**.
The **Session menu works on web** too — *Save state* / *Export script* download a file, and *Load state* / *Run script* open a file picker to upload one back.

.. note::

   A restored JSON snapshot re-loads its data files **by path**, which won't exist in a fresh browser tab.
   On web, re-open the logs alongside it, or use a ``.uzscript`` (it carries the ``load(...)`` lines).

Loading speed
=============

Native parses files in the background, so the window keeps rendering during a big load.
The browser has no background threads, so a load **blocks the tab** until parsing finishes.

.. _uz_dataviewer_native_web_memory:

Memory limit
============

A browser tab can address only **~4 GB** of memory, and the whole dataset must fit there.
What counts is the **numeric** size after parsing (roughly ``rows × channels × 4`` bytes), not the raw text size — so a multi-gigabyte CSV is far smaller once loaded.

- A log whose numeric size is **under ~1.5 GB** loads at **full resolution** in the browser.
- A larger log is **decimated on load** (a coarse overview), with a message in the console (e.g. *"Loaded … decimated 1:3 … use the native app for full detail"*).

**For full resolution on multi-gigabyte logs, use the native app** — it is limited only by your machine's RAM.
Lifting the browser ceiling (out-of-core storage) is future work — see :ref:`uz_dataviewer_web_large_logs`.

Running the web build
=====================

- **A local web server is required — ``file://`` does not work.** Serve the page over HTTP (``python -m http.server``, nginx, GitHub/GitLab Pages, S3, …).
- **Internet access is needed at load** to fetch the Pyodide runtime and the Python packages; once loaded, everything runs locally in the tab.

What is identical
=================

The command console and scripting, all plot types (cursors, spy, secondary axis, linked X, CSV export), the FFT & Histogram windows, the node graph and built-in transforms, range-aware downsampling, and ``.uzscript`` replay all behave the same on native and web.
Plugins are native-first; web plugin loading is a future idea — see :doc:`uz_dataviewer_plugins` and :doc:`uz_dataviewer_roadmap`.
