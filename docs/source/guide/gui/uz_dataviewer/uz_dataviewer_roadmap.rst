.. _uz_dataviewer_roadmap:

=======
Roadmap
=======

Open ideas for the UltraZohm Data Viewer and the record of what's already shipped.
For how to use the app see :doc:`uz_dataviewer_usage`; for internals see :doc:`uz_dataviewer_architecture`.

This is the **single entry point** for future work: the table below is the index; deep-dive files hold the detailed analysis for nodes, web large-log handling, and the cloud-data proposal.

Open ideas
==========

.. list-table::
   :header-rows: 1
   :widths: 22 12 44 22

   * - Idea
     - Area
     - Status
     - Detail
   * - **FFT as a plot type** (vs. the current dedicated window)
     - Plots
     - Deferred — the window was kept on purpose (per-frame transforms of a large window
       would tank fps; explicit *Compute* keeps it snappy). Revisit only if an inline
       spectrum cell is really wanted.
     - :ref:`uz_dataviewer_design_decisions`
   * - **Polars for load/perf**
     - Loader
     - Idea — measure first; the hot paths (Arrow parse, NumPy pyramid/FFT) are already
       native, so the win may be small.
     - —
   * - **3D flux maps from ``pyuzlib``**
     - Plots
     - Idea — plot machine data with 3D flux maps. Larger feature; no design yet.
     - —
   * - **ILA-mode (logic viewer)**
     - Loader/Plots
     - Idea — read ILA data (CSV or native) and show it as a logic-analyzer view.
     - —
   * - **Node graph edges & polish** (input order, FFT x-axis label, unit propagation,
       name collisions, source-on-derived chaining)
     - Nodes
     - Open follow-ups, all low/low-medium severity — not core-path bugs.
     - :doc:`uz_dataviewer_nodes_future_ideas` (items A–E)
   * - **Inline-code nodes** (user Python typed into a node)
     - Nodes
     - Assessed, deferred — plugin files (Option B) shipped first; inline code would need
       a code-carrying command path + a trust model.
     - :ref:`uz_dataviewer_custom_code_nodes`
   * - **Fixed FFT bin count** (resample / Welch cap)
     - FFT
     - Idea — a user-set cap so huge windows compute cheaply. Trade-offs worked out; see
       analysis below.
     - :ref:`uz_dataviewer_fixed_bin_count`
   * - **Move one-time ``rfft`` off the render thread**
     - FFT
     - Idea — kills the ~0.5 s *Compute* freeze on native (web has no worker threads).
     - :ref:`uz_dataviewer_fft_deferred`
   * - **Cloud logs (authenticated file store)**
     - Loader
     - Proposed — serve logs from a PocketBase file store for native + web; client
       downloads and loads them through the existing pipeline (decimation stays
       client-side, local path untouched).
     - :doc:`uz_dataviewer_remote_data`
   * - **Large logs in the web build (out-of-core)**
     - Loader
     - Analysis — wasm32's ~4 GB heap blocks big logs in the browser; out-of-core via an
       embedded DB or on-disk pyramid on OPFS is the fix (also removes the native RAM
       bound). Approach deferred. The **native** lean-loading path is now **shipped**
       (float32 channels, large-Parquet streaming, CSV size guard, CSV→Parquet
       ``convert``); only the web/out-of-core route remains.
     - :doc:`uz_dataviewer_web_large_logs`

.. _uz_dataviewer_fft_deferred:

FFT — deferred analysis
=======================

Background measurements (15M-sample window, one core):

- One-time ``rfft`` + magnitude on *Compute*: **~512 ms** → ~7.5M bins (60 MB float32).
- Per-frame plotting (pyramid-backed ``decimate_range``): **~0.3 ms**.

Power-of-2 padding
------------------

15M is 5-smooth, so NumPy's pocketfft factors it well; the cost is mostly size, not
factoring. Padding *up* to the next power-of-2 (16.7M) adds more points, more bins, and
more memory — not a speedup. Zero-padding only sinc-interpolates the spectrum (cosmetic,
no new resolution). The useful form — rounding the FFT length *down* to the nearest
5-smooth number — avoids large prime factors, but it is a micro-opt and only relevant
for pathological window sizes. **Verdict: no padding knob.**

.. _uz_dataviewer_fixed_bin_count:

Fixed bin count (resample / Welch)
----------------------------------

Goal: a user-set cap on bin count so large windows compute cheaply.

.. list-table::
   :header-rows: 1
   :widths: 22 18 18 20 22

   * - Mode
     - Bins
     - Δf
     - Max freq
     - Trade-off
   * - **Resample to N_fft**
     - fixed N_fft/2+1
     - 1/T — fine, kept
     - lowered to N_fft/(2T)
     - needs anti-alias low-pass; loses high-freq content
   * - **Welch (N_seg segments, averaged)**
     - fixed N_seg/2+1
     - coarser (fs/N_seg)
     - full fs/2, kept
     - smoother PSD; pure NumPy

Key math: ``Δf = fs/N = 1/T``, so resampling changes only the frequency *range*, not
frequency *resolution*. Welch keeps full range but reduces variance by averaging
periodograms.

Implementation: new ``fft_max_bins(n)`` command (default ``0`` = full resolution,
current behavior). Resample mode needs an anti-alias FIR (NumPy, not scipy, to keep
native + web on one dependency-free path). Welch is trivially pure NumPy. Touch-points:
``analysis.compute_fft``, ``panels/fft.py``, ``panels/analysis.py``, ``commands.py``,
session round-trip, USAGE/ARCHITECTURE docs.

Open decisions before building:

#. Which mode(s) to expose — resample (keeps Δf, loses high freq), Welch (keeps full
   range, coarser, smoother), or both. Leaning: Welch as the default cap.
#. Anti-alias implementation — hand-roll a NumPy FIR/polyphase decimator (consistent with
   dropping ``tsdownsample``), or add ``scipy`` (installed locally but not in requirements
   and is a heavy Pyodide wheel). Leaning: NumPy decimator.
#. Moving the one-time ``rfft`` off the render thread — independent of the above; reuses
   the existing ``ThreadPoolExecutor``. No-op on web (no worker threads).

Shipped
=======

Items from the original idea list that are now implemented (see :doc:`uz_dataviewer_usage` / :doc:`uz_dataviewer_architecture`):

- **Scriptable command API** — every click is a logged, replayable command; unified
  grammar.
- **Command console** — the bottom log shows commands and accepts command input, with
  completion and history.
- **Zoom/gesture echo** — e.g. a zoom emits ``set_x_lim(plot_1, min, max)`` to the log.
- **Save / restore state** — JSON snapshot and an editable, replayable ``.uzscript``.
- **Nodes** — drag a signal into a canvas, apply a transform, get a new draggable signal;
  scriptable like everything else (``node_*``). Extensible via **plugins** (:doc:`uz_dataviewer_plugins`).
- **More plot types** — XY plot; **Histogram** (as a dedicated window, like FFT).
- **Show samples** — per-sample markers on line plots.
- **Spy** — drag a rectangle; an inset below shows only that region.
- **MaterialFlat theme.**
- **Pyodide/web downsampling** — no longer needs a ``tsdownsample`` wheel: the decimator
  is a pure-NumPy min/max pyramid, so native and web share one code path.

.. _uz_dataviewer_remote_data:

======================================================
Cloud logs via an authenticated file store (proposal)
======================================================

.. note::

   Status: **proposed, not built.** Part of the :doc:`uz_dataviewer_roadmap`. This is a design / feasibility note, not a spec for code that exists today.

Why
===

Central, authenticated access to logs — for both native and web builds — so analysts can
open recordings without copying multi-gigabyte files around by hand.

A ">8 GB log" is the **CSV text** size.
The same record is only **~15M rows ≈ ~1.3 GB of numeric data** (15M × ~20 channels × 4 B + a float64 time axis).
That fits the web build's ~1.5 GB wasm-heap budget (see :doc:`uz_dataviewer_native_vs_web`), so such a log already loads at **full resolution in the browser** and trivially on native.
The goal is **central, authenticated access** — not raising the memory ceiling — and the design can stay small.

Constraints
===========

- **All decimation stays client-side and unchanged** — the in-memory min/max ``Pyramid``
  (``downsample.py``) keeps doing the work; the backend does **no** decimation.
- **The local-file path is untouched** — opening a file from disk behaves exactly as now.
- **One simple backend** — no second store, no server-side compute.

Approach: the cloud is just an authenticated file store
=======================================================

Store each log as a **Parquet file** in the cloud; the client **downloads it and loads it
through the existing loader**, producing an ordinary in-memory ``Run``. Cloud access is
purely additive and converges onto the current code path.

Backend — PocketBase (one binary)
---------------------------------

`PocketBase <https://pocketbase.io/>`_ is a single Go binary providing SQLite +
auth/users/OAuth2 + REST API + admin UI + **file storage**. We use it only as an
authenticated file store:

- A ``runs`` collection: metadata (``label``, recorded date, notes, ``t_min``/``t_max``,
  channel list) **plus a Parquet file attachment** per run.
- Built-in auth gates who can list and download runs (the multi-user piece, for free).
- **Store logs as files, not per-sample records.** This is the crux of the scale
  question: a 15M-row log as a Parquet *attachment* is a few-hundred-MB download (no
  PocketBase scale issue), whereas the same data as per-sample *records* would be 15M+
  rows — far outside PocketBase/SQLite's comfort zone (ingest cost, DB bloat, and
  PocketBase has no server-side sampling/aggregation anyway). File attachments are the
  right approach.
- **Ingest** = an offline script: convert a log (CSV/Parquet) to compact Parquet and
  upload it with its metadata. (No live/growing-log support in v1.)

Client — "Open from cloud" → the existing loader
------------------------------------------------

#. **Authenticate** against the PocketBase instance (token / OAuth2).
#. **List** runs from the ``runs`` collection (shown in Navigation, like local runs).
#. **Download** the chosen Parquet into the Pyodide FS (web) or a temp file (native).
#. Hand it to the **existing** ``loader.load_file`` via ``AppState.request_load``
   (``state.py``, ``loader.py``).

From step 4 on it's a normal ``Run`` with the lazily-built client ``Pyramid`` —
**identical to a local file**. Nothing in the local-file path, decimation, plots, or
session formats changes.

- **Scriptable**: a ``connect(url[, token])`` + ``open_cloud(run_id)`` command in
  ``commands.py``, so cloud opens are logged and replayable like every other action.
- **Transport** is gated on ``webbridge.IS_WEB`` (``webbridge.py``): web uses ``js.fetch``
  to pull the file into the FS then loads it (the same hand-off point the HTML file picker
  uses today); native uses ``urllib``/``requests`` on the existing loader thread.

How this satisfies the constraints
==================================

.. list-table::
   :header-rows: 1
   :widths: 35 65

   * - Constraint
     - How
   * - Decimation stays client-side
     - The backend serves bytes only; the in-memory pyramid is unchanged.
   * - Local path untouched
     - Cloud runs reuse ``load_file``; a cloud run *is* a ``Run``.
   * - One simple backend
     - PocketBase only — auth + metadata + file storage.
   * - 15M-row log
     - A normal file download that loads at full resolution (fits the wasm heap).

Limit, and the future hook
==========================

The "download then load" model is still bounded by the **wasm heap on the web build**: a
log whose *numeric* size exceeds ~1.5 GB (well beyond 15M rows) won't fit in a browser
tab. Native has no such limit. If logs ever outgrow browser memory, the extension is
**range-streaming** — fetch only the visible window and decimate that client-side (a thin
range API + an async per-window cache in the plot path). That is deliberately **out of
scope** here; we keep the simple file-store design until a real need for
larger-than-memory web logs appears.

Rough effort (small–medium)
===========================

#. PocketBase schema (``runs`` collection + file field) and an ingest/upload script.
#. A client cloud module: authenticate, list, download-to-FS, then hand to ``request_load``.
#. ``connect`` / ``open_cloud`` commands + a Navigation "Open from cloud…" entry.
#. Auth / multi-user — free from PocketBase.

Validating it (when built)
==========================

Stand up a local PocketBase with one Parquet run; from the app, authenticate, list,
download, and load it through the existing pipeline; confirm it behaves exactly like a
local file (plots, pyramid, cursors, export). Then check auth (a user without access can't
list/download it).
