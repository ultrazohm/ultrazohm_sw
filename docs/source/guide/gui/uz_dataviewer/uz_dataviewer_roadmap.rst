.. _uz_dataviewer_roadmap:

=======
Roadmap
=======

Developer reference for open ideas and shipped features of ``uz_dataviewer``.
For usage see :doc:`uz_dataviewer_usage`; for internals see :doc:`uz_dataviewer_architecture`.

The table below is the index of open work; the sections after it hold the detailed analysis for the larger items (FFT, cloud logs, node-graph follow-ups).

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
     - Deferred. The window is intentional: per-frame transforms of a large window would drop
       fps, while explicit *Compute* stays responsive. Revisit only if an inline spectrum cell
       is needed.
     - :ref:`uz_dataviewer_design_decisions`
   * - **Polars for load/perf**
     - Loader
     - Idea. Measure first; the hot paths (Arrow parse, NumPy pyramid/FFT) are already native,
       so the gain may be small.
     - —
   * - **3D flux maps from ``pyuzlib``**
     - Plots
     - Idea. Plot machine data as 3D flux maps. Larger feature; no design yet.
     - —
   * - **ILA-mode (logic viewer)**
     - Loader/Plots
     - Idea. Read ILA data (CSV or native) and show it as a logic-analyzer view.
     - —
   * - **Node graph edges & polish** (input order, FFT x-axis label, unit propagation,
       name collisions, source-on-derived chaining)
     - Nodes
     - Open follow-ups, all low / low-medium severity; not core-path bugs.
     - :ref:`uz_dataviewer_node_followups`
   * - **Fixed FFT bin count** (resample / Welch cap)
     - FFT
     - Idea. A user-set cap so huge windows compute cheaply. Trade-offs analysed below.
     - :ref:`uz_dataviewer_fixed_bin_count`
   * - **Move one-time ``rfft`` off the render thread**
     - FFT
     - Idea. Removes the ~0.5 s *Compute* freeze on native (web has no worker threads).
     - :ref:`uz_dataviewer_fft_deferred`
   * - **Cloud logs (authenticated file store)**
     - Loader
     - Proposed. Serve logs from a PocketBase file store for native + web; the client
       downloads and loads them through the existing pipeline (decimation stays client-side,
       local path untouched).
     - :ref:`uz_dataviewer_remote_data`
   * - **Large logs in the web build (out-of-core)**
     - Loader
     - Analysis. wasm32's ~4 GB heap blocks big logs in the browser; out-of-core via an
       embedded DB or on-disk pyramid on OPFS is the fix (also removes the native RAM bound).
       Deferred. The **native** lean-loading path is **shipped** (float32 channels,
       large-Parquet streaming, CSV size guard, CSV→Parquet ``convert``); only the
       web/out-of-core route remains.
     - :ref:`uz_dataviewer_web_large_logs`

.. _uz_dataviewer_fft_deferred:

FFT — deferred analysis
=======================

Background measurements (15M-sample window, one core):

- One-time ``rfft`` + magnitude on *Compute*: **~512 ms** → ~7.5M bins (60 MB float32).
- Per-frame plotting (pyramid-backed ``decimate_range``): **~0.3 ms**.

Moving the one-time ``rfft`` off the render thread (reusing the existing ``ThreadPoolExecutor``) would remove the *Compute* freeze on native.
It is independent of the bin-count work below and is a no-op on web (no worker threads).

Power-of-2 padding
------------------

15M is 5-smooth, so NumPy's pocketfft factors it well; the cost is mostly size, not factoring.
Padding *up* to the next power-of-2 (16.7M) adds more points, bins, and memory — not a speedup.
Zero-padding only sinc-interpolates the spectrum (cosmetic, no new resolution).
Rounding the FFT length *down* to the nearest 5-smooth number avoids large prime factors, but is a micro-optimisation relevant only for pathological window sizes.
**Decision: no padding knob.**

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

Key relation: ``Δf = fs/N = 1/T``, so resampling changes only the frequency *range*, not the *resolution*.
Welch keeps the full range and reduces variance by averaging periodograms.

Implementation: a new ``fft_max_bins(n)`` command (default ``0`` = full resolution, current behavior).
Resample mode needs an anti-alias FIR (NumPy, not scipy, to keep native + web on one dependency-free path); Welch is pure NumPy.
Touch-points: ``analysis.compute_fft``, ``panels/fft.py``, ``panels/analysis.py``, ``commands.py``, session round-trip, usage / architecture docs.

Open decisions before building:

#. Which mode(s) to expose — resample (keeps Δf, loses high freq), Welch (keeps full range, coarser, smoother), or both. Proposed default: Welch.
#. Anti-alias implementation — a NumPy FIR/polyphase decimator (consistent with dropping ``tsdownsample``), or add ``scipy`` (installed locally but not in requirements, and a heavy Pyodide wheel). Proposed: NumPy decimator.
#. Moving the one-time ``rfft`` off the render thread — independent of the above; reuses the existing ``ThreadPoolExecutor``. No-op on web.

.. _uz_dataviewer_remote_data:

Cloud logs via an authenticated file store (proposal)
=====================================================

.. note::

   Status: **proposed, not built.**
   Design / feasibility note, not a spec for existing code.

Goal: central, authenticated access to logs for both native and web builds, so analysts can open recordings without copying multi-gigabyte files by hand.

Note that a ">8 GB log" is the **CSV text** size; the same record is only ~15M rows ≈ ~1.3 GB of numeric data, which fits the web build's ~1.5 GB wasm-heap budget (see :doc:`uz_dataviewer_native_vs_web`).
Such a log already loads at full resolution in the browser and trivially on native.
The goal is **access**, not raising the memory ceiling, so the design stays small.

Constraints
-----------

- **Decimation stays client-side and unchanged** — the in-memory min/max ``Pyramid`` (``downsample.py``) does the work; the backend does no decimation.
- **The local-file path is untouched** — opening a file from disk behaves exactly as now.
- **One simple backend** — no second store, no server-side compute.

Approach
--------

Store each log as a **Parquet file** in the cloud; the client downloads it and loads it through the existing loader, producing an ordinary in-memory ``Run``.
Cloud access is purely additive and converges onto the current code path.

Backend — `PocketBase <https://pocketbase.io/>`_, a single Go binary (SQLite + auth + REST + file storage), used only as an authenticated file store:

- A ``runs`` collection: metadata (``label``, recorded date, notes, ``t_min``/``t_max``, channel list) **plus a Parquet file attachment** per run.
- Built-in auth gates who can list and download runs.
- **Store logs as file attachments, not per-sample records.** A 15M-row log as a Parquet attachment is a few-hundred-MB download; the same data as per-sample records would be 15M+ rows, far outside SQLite's comfort zone (and PocketBase has no server-side aggregation).
- **Ingest** is an offline script: convert a log (CSV/Parquet) to compact Parquet and upload it with metadata. No live/growing-log support in v1.

Client — "Open from cloud" reuses the existing loader:

#. **Authenticate** against the PocketBase instance (token / OAuth2).
#. **List** runs from the ``runs`` collection (shown in Navigation, like local runs).
#. **Download** the chosen Parquet into the Pyodide FS (web) or a temp file (native).
#. Hand it to the existing ``loader.load_file`` via ``AppState.request_load`` (``state.py``, ``loader.py``).

From step 4 on it is a normal ``Run`` with the lazily-built client ``Pyramid``, identical to a local file.
It is scriptable via ``connect(url[, token])`` + ``open_cloud(run_id)`` in ``commands.py``.
Transport is gated on ``webbridge.IS_WEB``: web uses ``js.fetch`` to pull the file into the FS then loads it; native uses ``urllib``/``requests`` on the loader thread.

Limit and future hook
---------------------

"Download then load" is still bounded by the **wasm heap on web**: a log whose *numeric* size exceeds ~1.5 GB won't fit in a browser tab (native has no such limit).
The extension, if logs ever outgrow browser memory, is **range-streaming** — fetch only the visible window and decimate it client-side (a thin range API + an async per-window cache in the plot path).
That is deliberately out of scope here and shares plumbing with the web out-of-core work (:ref:`uz_dataviewer_web_large_logs`).

Rough effort (small–medium): PocketBase schema + ingest script; a client cloud module (authenticate, list, download-to-FS, hand to ``request_load``); ``connect`` / ``open_cloud`` commands + a Navigation "Open from cloud…" entry.
Auth / multi-user is free from PocketBase.

.. _uz_dataviewer_node_followups:

Nodes — known limitations & follow-ups
======================================

From a review of the node-graph feature (engine in ``nodes.py`` / ``transforms.py``, canvas in ``panels/nodes.py``).
The review fixed three items first: transitive staleness (a downstream node reads ``(stale)`` when an upstream changes), op-aware input-pin count on ``math`` nodes, and skip-fresh evaluation (``node_eval`` only recomputes stale nodes).
The items below are edges and polish, not core-path bugs.

A. **Binary math input order is implicit (connection order).** ``A-B`` / ``A/B`` take ``inputs[0]`` and ``inputs[1]`` in the order the links were *created*, not by which input pin (``in1``/``in2``) the user dropped onto.
The editor reports the target slot in ``query_new_link``, but ``NodesPanel._try_link`` ignores it and ``node_link`` just appends.
Severity low–medium (wrong order silently swaps A and B).
Fix: decode the dropped slot and have ``node_link`` place the source at that index (a small command-grammar change to carry an optional slot).

B. **FFT-derived run's x-axis is frequency but plots label it "time".** An ``fft`` node's derived run uses ``time = freqs``, so dropping it into a time-series cell shows a spectrum under an x-axis labelled "time", and **Link X** would couple a frequency axis to time axes.
Severity low (cosmetic / semantic).
Fix: tag derived runs with an x-axis kind/label; have ``PlotsPanel`` honour it and exclude frequency-axis runs from link-X.

C. **Units are not propagated to derived signals.** Every derived signal is created with unit ``""``.
For ``filter`` and ``offset`` the physical unit is unchanged and could be carried over; ``scale``/``derivative``/``integral`` change it.
Severity low.
Fix: pass the input unit through for unit-preserving ops in ``nodes._compute`` / ``upsert_derived_run``.

D. **Name / label collisions.** Derived runs are labelled by node name (``node_<id>`` by default).
If a loaded file is named like a node, or two nodes share a label, ``_label_to_run_id`` resolves to the first match; ``node_rename`` checks other node names but not loaded run labels.
Severity low (needs a deliberate clash).
Fix: validate node names against ``registry`` labels too and reject duplicates.

E. **Source-on-derived chaining is fragile across restore/script.** A source node wrapping *another node's* derived run works at runtime (the run id is valid) but may not survive save/restore or ``.uzscript`` replay, because the derived run does not exist until its producing node is evaluated.
Chaining is meant to go through ``node_link`` (transform → transform).
Severity low.
Fix: resolve such source refs lazily at eval time, or block creating a source from a derived run and steer users to ``node_link``.

Shipped
=======

Items from the original idea list now implemented (see :doc:`uz_dataviewer_usage` / :doc:`uz_dataviewer_architecture`):

- **Scriptable command API** — every click is a logged, replayable command; unified grammar.
- **Command console** — the bottom log shows commands and accepts command input, with completion and history.
- **Zoom/gesture echo** — e.g. a zoom emits ``set_x_lim(plot_1, min, max)`` to the log.
- **Save / restore state** — JSON snapshot and an editable, replayable ``.uzscript``.
- **Nodes** — drag a signal into a canvas, apply a transform, get a new draggable signal; scriptable (``node_*``) and extensible via **plugins** (:doc:`uz_dataviewer_plugins`).
- **More plot types** — XY plot; **Histogram** (a dedicated window, like FFT).
- **Show samples** — per-sample markers on line plots.
- **Spy** — drag a rectangle; an inset below shows only that region.
- **MaterialFlat theme.**
- **Pyodide/web downsampling** — no ``tsdownsample`` wheel needed: the decimator is a pure-NumPy min/max pyramid, so native and web share one code path.
- **Native lean loading** — float32-at-parse, large-Parquet streaming, CSV size guard, and a CSV→Parquet ``convert`` command/CLI (see :ref:`uz_dataviewer_loader_large_logs`).
