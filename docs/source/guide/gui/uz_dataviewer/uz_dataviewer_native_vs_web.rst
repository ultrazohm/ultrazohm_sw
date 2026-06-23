.. _uz_dataviewer_native_vs_web:

=============
Native vs Web
=============

The same ``uz_dataviewer`` Python runs on the desktop **and** in the browser.
Native is CPython (a PyInstaller-frozen interpreter). 
Web is **Pyodide** (CPython compiled to WebAssembly).
The flag ``webbridge.IS_WEB`` gates a handful of places where there are differences.

The UI, the command layer, plots, FFT/Histogram, nodes, and the downsampler are **identical** on both targets.
The differences are file I/O, threading, and the WASM memory ceiling.
For building each target see :doc:`uz_dataviewer_build`.
For internals see :ref:`uz_dataviewer_arch_native_web`.

At a glance
===========

.. list-table::
   :header-rows: 1
   :widths: 20 40 40

   * - Concern
     - Native (desktop)
     - Web (Pyodide/WASM)
   * - **Runtime**
     - CPython, frozen by PyInstaller
     - CPython → WebAssembly (Pyodide)
   * - **Distribution**
     - One self-contained executable
     - A static web page (must be served over HTTP)
   * - **File open**
     - OS file dialog (``portable_file_dialogs``) + drag files onto the window (GLFW)
     - Hidden HTML ``<input type=file>`` picker
   * - **Loading**
     - Async on a ``ThreadPoolExecutor``
     - **Synchronous** (Pyodide has no worker threads)
   * - **Large CSV**
     - Arrow reads the whole file
     - **> 200 MB** is **stream-parsed** into typed arrays; ≤ 200 MB CSV and any Parquet still go through Arrow
   * - **Downsampler**
     - Min/max pyramid (pure NumPy)
     - **Identical** — same code, no native dependency
   * - **Export / Save**
     - OS save dialog
     - Browser download (Blob + anchor); session save/restore uses download + a hidden file picker
   * - **Memory**
     - OS RAM
     - Hard ~4 GB wasm32 address space
   * - **Internet needed?**
     - No
     - **Yes at load** — fetches the Pyodide runtime + wheels

Why these differences exist
===========================

File access
-----------

On the desktop you can open files via the OS dialog **or drag** ``.csv``/``.parquet`` files **onto the window** (a GLFW drop callback; a no-op without the GLFW backend).
A browser tab has no OS file dialog, so **Open file(s)…** opens an HTML picker instead.
Saving works the same way in reverse: native pops an OS save dialog; web triggers a **browser download** via ``webbridge.download`` (a Blob + a synthetic anchor click).
The **Session menu works on web** too: *Save state* / *Export script* write to the Pyodide FS and download; *Load state / Run script* opens a second hidden file picker (``uzSessionInput``) whose upload is routed by extension — ``.json`` → ``load_state``,
``.uzscript``/``.txt`` → ``run_script`` (``webbridge.load_uploaded_session``).
One caveat: a restored JSON snapshot re-loads its data files **by path**, which won't exist in a fresh tab, so on web re-open the logs (or use a ``.uzscript``, which carries the ``load(...)`` lines) alongside it.

Threading
---------

Native loads files on a background ``ThreadPoolExecutor`` so the UI keeps rendering during a big parse. The worker only **parses** the file into a ``ParsedRun`` (plain arrays).
The shared ``DataRegistry`` is mutated only on the main thread, which **registers** the result in ``poll_pending_loads`` — so the registry stays single-threaded even though parsing is off-thread.
Pyodide has **no worker threads**, so web loads **synchronously** — the tab blocks for the duration of the parse (and registers inline).

.. _uz_dataviewer_native_web_memory:

Large CSVs and the memory ceiling
---------------------------------

The real constraint on web is wasm32's **~4 GB address space**. What matters is not the raw text size but the **numeric** footprint after parsing (``rows x channels x 4`` bytes for ``float32`` channels + a ``float64`` time axis).

- **≤ 200 MB CSV and any Parquet** are written to the Pyodide FS and parsed by Arrow, same as native.
- **CSV > 200 MB** is **stream-parsed in the browser** directly into per-column typed arrays (``webbridge.load_columns``): the file blob is read in chunks, so the multi-gigabyte *text* never sits in WASM memory — only the compact numeric result.

The streaming loader **estimates the numeric footprint up front** and, if it would exceed a safe budget (~1.5 GB), **decimates ``1:stride`` on the way in** and says so in the console (e.g. *"Loaded … decimated 1:3 … use the native app for full detail"*).
So a log under the budget loads at **full resolution**, and a genuinely huge one (e.g. 5 GB) loads a usable **decimated** view instead of silently aborting the WASM runtime.
**For full resolution on multi-GB logs, use the native app.**

Cloud logs (proposed — see :ref:`uz_dataviewer_remote_data`) download and load through this same in-memory path, so the heap budget above still applies to an oversize log in the browser.
Lifting that ceiling (out-of-core via OPFS) is analysed separately in :doc:`uz_dataviewer_web_large_logs`.

Downsampling is the same on both
--------------------------------

The decimator is a pure-NumPy min/max pyramid (``downsample.py``) — there is no native/Rust dependency to wheel for the browser, so native and web run **exactly the same** decimation code. (This is why the legacy ``tsdownsample`` dependency was dropped.)

Web-only operational notes
==========================

- **A local web server is required — ``file://`` does not work.** The browser blocks Pyodide's package downloads from a ``file://`` origin.
  Serve the page over HTTP (``python -m http.server``, nginx, GitHub/GitLab Pages, S3, ...).
- **Internet access is needed at runtime** to fetch the Pyodide runtime and the wheels (the ``imgui_bundle`` WASM wheel from pthom's hosting, plus ``numpy``/``pandas``/``pyarrow``).
- **Version pins matter:** the ``imgui_bundle`` wheel is built against one specific Pyodide release. If you bump one (``PYODIDE_VERSION`` / ``IMGUI_BUNDLE_WHEEL`` in ``build/gen_web.py``), bump the other to a compatible pair.
- A true *double-click-the-HTML, no-server* app would require a **C++ + emscripten ``SINGLE_FILE`` rebuild** (embedding the wasm as base64), which would drop the Python data stack — a separate effort, not this app. See :ref:`uz_dataviewer_build_web`.

What is identical
=================

The **command API and console**, **plots** (types, cursors, spy, secondary axis, linked X, CSV export), **FFT & Histogram windows**, the **node graph** and built-in transforms, **range-aware downsampling**, and the **``.uzscript``** replay all behave the same on native and web.
Plugins are native-first (real filesystem + ``importlib``); web plugin loading is a future idea — see :doc:`uz_dataviewer_plugins` and :doc:`uz_dataviewer_roadmap`.

Maintenance notes:

- Version pins live in ``build/gen_web.py`` (``PYODIDE_VERSION``, ``IMGUI_BUNDLE_WHEEL``). The wheel is built against one specific Pyodide release; if you bump one, bump the other to a compatible pair (see the imgui_bundle Pyodide docs).
Reference: imgui_bundle Pyodide docs — `pthom.github.io/imgui_bundle/python_pyodide.html <https://pthom.github.io/imgui_bundle/python_pyodide.html>`_



Loading data in the browser
---------------------------

There is no OS file dialog in a tab, so the **Open file(s)…** button opens an HTML file picker.
Loading is synchronous (Pyodide has no worker threads):

- **Small files (≤ 200 MB) and any Parquet** are written to the Pyodide FS and parsed by Arrow as usual.
- **Large CSVs (> 200 MB)** are **stream-parsed in the browser** directly into per-column typed arrays (``webbridge.load_columns``): the File blob is read in chunks, so the multi-gigabyte *text* is never resident in 32-bit WASM memory — only the compact numeric result (time ``float64`` + channels ``float32``).

The hard limit is wasm32's ~4 GB address space: the *numeric* arrays must fit(≈``rows x channels x 4`` bytes), which is far smaller than the raw CSV but still caps how big a log the browser can hold.
The streaming loader estimates that footprint up front and, if it would exceed a safe budget (~1.5 GB), decimates ``1:stride`` on the way in and says so in the console (e.g. *"Loaded … decimated
1:3 … use the native app for full detail"*).
So a file under the budget loads at full resolution, and a huge one (e.g. a 5 GB log) loads a usable **decimated** view instead of silently aborting the WASM runtime.
For full resolution on multi-GB logs, use the native app.


.. _uz_dataviewer_web_large_logs:

Large logs in the web build (the wasm32 memory limit)
=====================================================

.. note::

   Status: **analysis / design note, not built.** Part of the :doc:`uz_dataviewer_roadmap`.
   This is **separate** from the cloud-data feature (:ref:`uz_dataviewer_remote_data`) — it is purely about why the *browser* build can't open very large logs and what could fix it.
   The implementation approach is intentionally left open.

   **Native** large logs are already handled by lean loading (float32-at-parse, streaming Parquet, a CSV size guard and a CSV→Parquet ``convert``) — see :ref:`uz_dataviewer_loader_large_logs`. This doc is only about the harder **web / larger-than-RAM** case that lean loading can't reach.

The problem (concrete)
======================

``Log_2026-06-16_10-46-24.csv``: **~4.6 GB text, 21 columns** (``time`` + 20 channels,``;``-delimited), **~55M rows**. Parsed to numbers:

- ``time`` ``float64`` (8 B) + 20 channels ``float32`` (80 B) = **88 B/row x 55M ≈ ~4.8 GB   numeric.**

The web build cannot hold that, so today it either decimates ``1:stride`` on load (lossy overview; see ``build/gen_web.py`` ``MEM_BUDGET``) or the tab runs out of memory.
Native opens it fine (it uses the PC's RAM).

Why it's hard: the wasm32 ceiling
=================================

Pyodide runs in **wasm32**'s single ~4 GiB linear memory (~2-3 GB usable), and **everything** Python touches lives there — numpy arrays, Arrow's parse buffers, the CSV text, all Python objects (the basics are in :ref:`uz_dataviewer_native_web_memory`).
The loader materialises the **whole** dataset and builds the pyramid in that same memory, so ~4.8 GB doesn't fit in a ~4 GB address space.

**This cap is on linear memory (RAM), not on what the tab can store overall** — which is why an embedded database using OPFS can help despite running in the same browser tab.

Mitigations
===========

.. list-table::
   :header-rows: 1
   :widths: 40 25 35

   * - Option
     - Helps?
     - Cost
   * - **Decimate-on-load** (current)
     - Loads a coarse *overview* only — no full-res zoom
     - already done; lossy
   * - **Shrink the footprint** (load only selected channels; store ``y`` as
       ``float16``/``int16``)
     - ~2–4× more headroom
     - cheap, partial; precision loss
   * - **Out-of-core via OPFS** (embedded DB or on-disk pyramid)
     - **Real fix** — data on disk, not in the 4 GB RAM
     - significant change
   * - **wasm64 / memory64**
     - Raises the address space past 4 GB
     - needs a memory64 Pyodide + imgui_bundle build and broad browser support — not practical yet, and still bounded by device RAM
   * - **Web Workers / SharedArrayBuffer**
     - **No** — still 32-bit linear memory per module
     - only improves responsiveness, not capacity

Why an embedded database resolves it — even in the same browser tab
===================================================================

A tab has **two separate memory pools**, and the 4 GB cap applies to only one:

#. **wasm linear memory (RAM)** — the single ~4 GB ``ArrayBuffer``. This is the wall.
#. **OPFS (Origin Private File System)** — large, persistent, **disk-backed** storage for  the origin (many GB, up to a big fraction of free disk).
   It is **not** part of linear memory and is **not** addressed by wasm pointers.

An embedded database compiled to wasm — **DuckDB-wasm**, or **SQLite-wasm** with the OPFS VFS — keeps its tables/files in **OPFS (disk)** and runs queries **out-of-core**: it pages only the data it currently needs into a **bounded buffer** in linear memory, scans, and frees it; the result it returns is **small** (~``max_points`` per signal).
So:

- the full ~4.8 GB dataset lives **on disk** (OPFS) in the same browser, and
- only a **bounded working set** ever occupies the 4 GB RAM, flowing through it in small pages.

Hence the dataset can be **far larger than 4 GB** even though it's the same tab — the database is the bridge between disk-resident data and RAM-bounded compute.
"Same window" is true; "same 4 GB RAM" is not — the data sits on disk and only streams through RAM.

The catch (the real work)
-------------------------

This only works if the app **never materializes the whole dataset in RAM**.
Today we do the equivalent of ``SELECT *`` into numpy.
To go out-of-core the data path must switch to **query the visible window per view**:

- zoomed in → a **range** query (few rows) → exact;
- zoomed out → a **min/max-per-bucket** query for the overview (can't pull all raw rows into RAM);
- fetched **async + cached**, debounced on pan/zoom settle (the same idea as the zoom echo in ``panels/plots.py``).

The zoomed-out overview min/max therefore has to be computed **out-of-core** — by the engine, not by loading everything.

Pandas / Polars / native RAM bound
==================================

- **Native is also bound by RAM today.** The current loader (native *and* web) reads the **whole** log into in-memory numpy arrays + pyramid.
  Native just has a far higher ceiling (the PC's RAM — tens of GB), so a ~4.8 GB log is comfortable, but a much larger one (e.g. 50 GB) would still exhaust native RAM.
  "Bound by RAM" holds on both; only the ceiling differs (machine RAM vs ~4 GB wasm).
- **…and the load *peak* (separate from the resident bound) is now handled on native.** The old loader peaked at ~24 GB on the 4.6 GB example (float64 inference + a float32 re-cast, and Arrow holding the whole table).
  Lean loading has since shipped — float32-at-parse, streaming **CSV** *and* Parquet (~1.5× resident instead of CSV's old ~4x bulk peak), and releasing Arrow's retained pool after each parse — bringing the native peak down near the resident size; see :ref:`uz_dataviewer_loader_large_logs`.
  That fixes the *peak*, but not the *resident* bound: the full dataset still lives in RAM, which is exactly what the out-of-core work below removes.
- **pandas** is in-memory only — it loads the whole frame into RAM. It can read in fixed ``chunksize`` passes, but has no random-access "read just the visible window" model for interactive use.
  Not an out-of-core fix by itself.
- **Polars** *can* do it: its **lazy + streaming** mode (``scan_parquet``/``scan_csv`` → ``collect(streaming=…)``) is out-of-core. Over **Parquet** it does **predicate + projection pushdown** — it skips row groups outside the time range and reads only the needed columns, streaming in bounded-memory batches — so a min/max-per-bucket over a window reads only what it needs.
  **DuckDB over Parquet** does the same. So this capability genuinely exists.
- **The catch is *where* it runs.** Those engines help only if (a) they run in the target and (b) the data sits on **disk** they can stream from.
  On **native**, both hold → Polars/DuckDB over Parquet is the easy out-of-core path, and it would **lift the native RAM bound too**.
  In the **browser**, the Python builds of Polars/pandas aren't set up for Pyodide + OPFS streaming (and a file in Pyodide's in-memory FS counts against the same 4 GB), so the practical engine there is **DuckDB-wasm** (the JS/wasm package) reading from **OPFS** — i.e. approach A below.

So the out-of-core idea is engine-agnostic: on native you'd reach for Polars/DuckDB over Parquet (easy, and removes the native RAM bound); in the browser you'd use DuckDB-wasm + OPFS, or our own on-disk pyramid in OPFS.

Two implementation approaches (presented, not chosen) — for the web/out-of-core case
====================================================================================

**A. DuckDB-wasm + OPFS.** Store the log as Parquet/tables in OPFS; do range filters and min/max-per-bucket in SQL. Least bespoke code, but adds a large second wasm runtime (~tens of MB to download) and moves the decimation math into the DB (still in-browser, but no longer our pyramid).

**B. On-disk pyramid in OPFS (no DB).** A one-time **streaming ingest** reads the user's file in chunks via the browser File API (never holding it all in RAM) and writes columnar data plus our min/max ``Pyramid`` levels into OPFS; the client then reads small levels/ranges per view.
 Keeps our existing decimation and needs no heavy dependency, but is more bespoke out-of-core file code.

**Shared to both:**

- a one-time **ingest pass** is required to get the data into OPFS (time + disk space, subject to the browser's OPFS quota);
- the in-app **"windowed run"** abstraction (a run whose arrays are fetched per visible window, async + cached, instead of held whole) is the **same** plumbing the cloud feature would use — only the *source* differs (local OPFS here vs a remote URL there).
  The two features are kept separate, but this part is worth building once.

Scope
=====

Substantial: a new run type in ``model.py`` and a shift in ``panels/plots.py`` from per-frame in-memory decimation to an async windowed fetch + cache.
The **native path is unaffected**.
The A-vs-B choice is deferred until this is actually scheduled.
