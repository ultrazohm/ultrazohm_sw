.. _uz_dataviewer_remote_data:

======================================================
Cloud logs via an authenticated file store (proposal)
======================================================

.. note::

   Status: **proposed, not built.** Part of the :doc:`roadmap`. This is a design /
   feasibility note, not a spec for code that exists today.

Why
===

Central, authenticated access to logs — for both native and web builds — so analysts can
open recordings without copying multi-gigabyte files around by hand.

A ">8 GB log" is the **CSV text** size. The same record is only **~15M rows ≈ ~1.3 GB of
numeric data** (15M × ~20 channels × 4 B + a float64 time axis). That fits the web build's
~1.5 GB wasm-heap budget (see :doc:`native_vs_web`), so such a log already loads at **full
resolution in the browser** and trivially on native. The goal is **central, authenticated
access** — not raising the memory ceiling — and the design can stay small.

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
