.. _uz_scope_architecture:

======================
uz_scope architecture
======================

Design goal: the Ethernet ingest is the product.
Today the device streams 20 channels at 10 kHz (~0.9 MB/s); the firmware roadmap is 200 channels at 10 kHz (~8 MB/s) and eventually 200 channels at 100 kHz — **80.8 MB/s (647 Mbit/s)**.
``uz_scope`` is built and benchmarked against that end state while speaking today's protocol unchanged.

Wire protocol
=============

TCP client to the APU (FreeRTOS/lwIP, ``vitis/software/FreeRTOS/sw/ethernet.c``), little-endian, **no framing header**.
With ``C`` channels and ``N`` samples per packet one frame is::

   uint32  status              # LEDs, MyButton indicators, ext-log bit 12
   uint32  slow_raw[N]         # slowdata payload, round-robin, raw bits
   float32 ch[C][N]            # channel-major fast samples
   float32 slow_id[N]          # JS_SlowData index of each slow_raw entry

That is ``4 + (C+2)·N·4`` bytes — 1324 at the current C=20, N=15.
The uplink is an 8-byte ``{uint32 id; float value}`` command; ids come from ``enum gui_button_mapping`` and channel selects use ids 201….
Because the protocol is headerless, geometry and timestep are **configuration** and must match the firmware build; the diagnostics (throughput %, lifecheck, rate detection) surface a mismatch.

Ack pacing: the JavaScope answers every received frame with one 8-byte command (a zero-ack when idle).
The real APU drains its receive queue independently, but the bundled ``javascope/test_server.py`` is strictly lock-step *and reads only the first 8 bytes per receive*, so ``uz_scope`` paces one single-write command per frame (TCP_NODELAY) — configurable via ``ack_pacing(on/off)``.

Threading
=========

Three thread roles, one owner per resource:

- **Reader** (``netclient.py``): owns the socket.
  It ``recv_into``\ s a preallocated 4 MiB buffer (releases the GIL), parses *all* complete frames in one vectorized NumPy call (``protocol.parse_frames`` — zero per-value Python), appends to the ring, feeds trigger/slowdata/lifecheck, taps the logger queue, and sends the acks.
  It reconnects with 1/2/5 s backoff, and an exception in any frame consumer surfaces through the normal disconnect path instead of silently killing the thread.
- **Logger** (``capture_log.py``): encodes Parquet/CSV/bin behind a bounded queue.
  A slow disk drops whole chunks (counted and reported) rather than ever stalling ingest.
- **History spill** (``history.py``, disk mode only): writes the raw stream to one flat float32 file per channel behind its own bounded queue (same drop-and-count policy); a further worker serves asynchronous full-detail read-backs for the plots.
- **UI** (main): renders at full rate (hello_imgui idling disabled) but refreshes plot data at a decoupled ~30 Hz.
  Each refresh queries the session history for the visible x-range of every plot cell, which decimates to ~2× the plot pixel width with a min/max envelope, and applies the display transform on the decimated points only — so the per-frame cost is independent of ring size, session length and rate.

The ring (``ring.py``) is a preallocated ``(channels, capacity)`` float32 array.
Time is never stored: an absolute int64 sample counter converts to float64 seconds only at the edges (float32 would lose sample precision within minutes at 100 kHz).

Session history
===============

``history.py`` makes the whole session pan/zoomable without keeping it raw in RAM:

- ``LivePyramid`` — an *incremental* multi-resolution min/max pyramid, appended on the reader thread (one vectorized reduction per block, all channels at once).
  Unlike ``uz_dataviewer``'s rebuild-only pyramid it stores bucket **values**, not sample indices, so it survives ring eviction; the last bucket of every level is partial and updated by running min/max, which keeps all buckets index-aligned.
  Levels coarsen geometrically (factor 8) and a byte cap folds the finest level pairwise when exceeded, so memory is bounded regardless of session length.
- ``SessionHistory.query(ring, channel, start, stop, n_out, dt)`` — the one call the plots make: the ring serves the resident tail sample-exact, the pyramid serves the evicted head as an envelope, both clamped to the slot's *epoch* (set when a channel select reassigns the slot).
- Disk mode adds ``DiskSpill`` (per-channel flat files, NaN backfill keeps file offset == absolute sample index) and ``HistoryReader`` (latest-request-wins worker); the envelope renders immediately and full detail swaps in when the read completes.

The trigger (``acquisition.py``) runs on the reader thread: the JavaScope's three-point edge test, vectorized, with two samples carried across block boundaries so no edge is lost between packets.
Capture positions are absolute indices, and the window is copied out of the ring under its lock the moment the last sample arrives.

Measured performance
====================

On a 16-core dev container (loopback, ``tools/bench_server.py`` + ``tools/bench_client.py``):

- 60 s soak at 200 ch × 100 kHz: **80.84 MB/s sustained**, 6,001,920 samples lifecheck-verified, **zero gaps**.
- Parse + ring append alone: ~3.8 GB/s (≈47× headroom over the target).
- Live logging at full rate: Parquet and bin both kept up with zero dropped chunks.

Reproduce with::

   python uz_scope/tools/bench_server.py --channels 200 --rate 100000
   python uz_scope/tools/bench_client.py --channels 200 --rate 100000 --seconds 60

Module map
==========

.. list-table::
   :widths: 30 70

   * - ``protocol.py``
     - Frame geometry, vectorized parse, command encoding
   * - ``javascope_header.py``
     - Marker-based ``javascope.h`` parser (names, ids)
   * - ``config.py``
     - ``ScopeConfig`` JSON + ``properties.ini`` import
   * - ``netclient.py``
     - Reader thread, ack pacing, reconnect, stats
   * - ``ring.py``
     - Channel-major ring, wrap-aware snapshots
   * - ``acquisition.py``
     - Trigger engine (auto/normal/single, pretrigger)
   * - ``slowdata.py``
     - Typed SlowData store
   * - ``capture_log.py``
     - Streaming Parquet/CSV/bin logger, capture export
   * - ``lifecheck.py``
     - Sample-continuity monitor
   * - ``history.py``
     - Session history: incremental envelope pyramid, disk spill, read-back
   * - ``dashboard.py``
     - Dashboard widget model (bindings, ``dash_*`` helpers)
   * - ``commands.py`` / ``state.py``
     - Command registry and the single app state
   * - ``session.py``
     - JSON snapshots and ``.uzscript`` export/replay
   * - ``panels/``
     - ImGui panels (plot windows, logged variables, observables, dashboard, control, …)

All non-``panels`` modules are GUI-free and covered by the test suite (``python -m pytest uz_scope/tests``).
The suite also spawns the real ``javascope/test_server.py`` for an end-to-end exchange and re-opens logged files with ``uz_dataviewer.loader`` as the compatibility contract.
