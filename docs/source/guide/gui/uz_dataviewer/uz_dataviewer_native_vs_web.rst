.. _uz_dataviewer_native_vs_web:

==========================
Limitations of web version
==========================

The ``uz_dataviewer`` runs on the desktop (*native*) and in the browser.
Native is a self-contained desktop application; web is a static page you open in a browser.
Almost everything behaves the same on both: the command console and scripting, every plot type (cursors, spy, secondary axis, linked X, CSV export), the FFT & Histogram windows, the node graph with its built-in transforms, range-aware downsampling, and ``.uzscript`` replay.
The one feature web cannot offer is custom node plugins: the browser runs the built-in transforms only, while native can also load your own from a plugin folder (see :doc:`uz_dataviewer_plugins`).
Otherwise the differences are in file access, loading speed, and the memory limit due to browser constraints.

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
     - Large **CSV** rejected above the numeric-data budget; **Parquet** must fit in memory
   * - **Export / Save**
     - OS save dialog
     - Browser download (and a file picker to load sessions back)
   * - **Custom node plugins**
     - Built-in transforms plus your own plugin folder
     - Built-in transforms only
   * - **Memory**
     - Your machine's RAM
     - Hard ~4 GB browser limit
   * - **Internet**
     - Not required
     - Required at load to fetch the runtime

File access
===========

On the desktop you open files via the OS dialog, or **drag** ``.csv`` / ``.parquet`` files onto the window.
A browser tab has no OS dialog, so **Open file(s)…** opens an HTML file picker instead.
Saving works the same way in reverse: native pops an OS save dialog, web triggers a **browser download**.
The Session menu works on web too — **Save state* / *Export script** download a file, and **Load state* / *Run script** open a file picker to upload one back.

.. note::

   A restored JSON snapshot re-loads its data files by path, which won't exist in a fresh browser tab.
   On web, re-open the logs alongside it, or use a ``.uzscript`` (it carries the ``load(...)`` lines).

Loading speed
=============

Native parses files in the background, so the window keeps rendering during a big load.
The browser has no background threads, so a load blocks the tab until parsing finishes.

.. _uz_dataviewer_native_web_memory:

Memory limit
============

A browser tab can address only ~4 GB of WASM memory. Uploaded backing files and any file caches occupy the tab's temporary filesystem within that budget.
Memory loading also retains the parsed numeric arrays (roughly ``rows x channels x 4`` bytes plus timestamps); Lazy delays reading decoded channels.
Small CSV uploads and Parquet files honor the same loading/cache settings as console loads. File caches disappear on page reload.
Large streamed CSVs have no backing file and remain numeric arrays regardless of the loading setting.
The browser keeps a margin below that ceiling for the runtime and the app itself, so a log loads at full resolution in the browser only while its numeric size stays under ~1.5 GB.

How a larger log is handled depends on the file type:

- Streamed CSVs preserve every sample. Files exceeding the estimated or actual numeric-data budget (~1.5 GiB) are rejected with a message directing users to the native app.
- All accepted recordings load at full resolution. The CSV numeric-data budget does not bound total browser memory, and Parquet files have no equivalent preflight guard. Use the native app for recordings that do not fit.

For full resolution on multi-gigabyte logs, use the native app — it is limited only by your machine's RAM.