# Option Z — open gaps & improvement backlog

Status as of 2026-07-09, after the CP7 pass that ported the hedrive hardware
lessons (seqlock, CTO mailbox, XCP_IN generation handshake, gateway-owned CTR,
dedicated CTO queue, TX batching, deep DAQ queue — see
`uz_sw_xcp_hedrive_andi/XCP_BOTTLENECK_ANALYSIS.md` T1/T3/T8/B1/B5). Everything
below is **known and accepted** for hardware bring-up; this file is the
prioritized list of what to measure, what debt remains, and what must happen
before production-like use.

Verified already inherited (not open): the mandatory `portMEMORY_BARRIER` +
`use_task_fpu_support 2` BSP fix is present in `tcl_scripts/` and in all three
generated `FreeRTOSConfig.h` copies — the historical "A53 freezes after minutes
of traffic" bug is covered.

## 1. Measure on first hardware contact (cheap, decides the next change)

### 1.1 XCP sweep moved OUT of `ISR_Control` — implemented 2026-07-11 (CP11)
Measured with the sweep still in the ISR (via `isr_execution_time_us`,
`--stress` at 10 kHz): 16.1 µs XCP idle (engine ≈ +10 µs over baseline),
18.3 µs @ 100 B, 27.1 µs @ 1 kB, 52.9 µs @ 4 kB/cycle — linear
~10 µs base + ~10 µs/KB. Unacceptable for the **100 kHz ISR target**
(10 µs total budget), so the §1.1 lever is now implemented:

- ISR keeps ONLY `xcp_r5_event()` (the DAQ sampling copy; ~sub-µs idle,
  ~5 µs/KB measured-payload marginal).
- Everything else (command processing, queue drain → OCM, cache
  maintenance, IPI trigger) runs from the main loop via
  `xcp_r5_background()`, paced at `XCP_R5_SWEEP_PERIOD_US` (100 µs — the
  soak-validated exchange cadence; the A53 gateway sees the same IPI rate
  as before).
- queue32 (32 KB, was 8 KB) is the ISR/main boundary; its internal locks
  are pointer-arithmetic-short, and the IRQ-disabling lock that used to sit
  around the 252-byte OCM memcpy in `xcp_r5_tx_pump` is GONE (everything
  CTR-related is single-context now). New counters: `xcp_r5_queue_lost`
  (ISR out-produced the sweep — raise queue size/sweep rate),
  `xcp_r5_sweep_count` (main-loop liveness).

**Re-measure `isr_execution_time_us` after rebuild** — expected: near the
non-XCP baseline at idle, ~+5 µs/KB of measured payload when streaming.
At 100 kHz later: mind the queue sizing math in `xcptl_ocm.c`, the 1 µs DAQ
timestamp granularity (10 ticks/cycle), and the R5 heap (queueInit now
takes 32 KB of the 128 KB heap; watch `xcp_r5_init_result == -1`).

### 1.2 Declared vs real DAQ event rate — RESOLVED (CP12, 2026-08-03)
`DAQ_R5` used to declare a hardcoded 1 ms while firing at the control rate.
It now declares `XCP_R5_ISR_PERIOD_NS`, derived in `xcptl_ocm.c` from
`UZ_PWM_FREQUENCY x Interrupt_ISR_freq_factor / INTERRUPT_ADC_TO_ISR_RATIO`
(the expression `main.c` uses for `isr_samplerate_s`) — 25 µs at the current
40 kHz configuration.

Same pass added the hedrive time slices as derived rasters (see
`kXcpR5Slice`): event channels 1..4 = `daq_1ms` / `daq_10ms` / `daq_100ms` /
`daq_1s`, counted down from the ISR rate and staggered so they never fire in
the same control cycle. Slow signals no longer have to ride the ISR raster,
which is the cheapest possible bandwidth cut on the OCM/UDP path. Channel
numbers are creation order and are mirrored in `CANape/UZ_XCP/uz.A2L` — a
mismatch would silently move signals to the wrong raster, so `xcp_r5_init()`
verifies the numbering and latches `xcp_r5_init_result = -4` if it ever
shifts. DAQ table memory went 3 KB → 6 KB (`OPTION_DAQ_MEM_SIZE`) for the
five lists.

## 2. Design debt — fix only if symptoms appear

### 2.1 DAQ frames of a missed cycle are still lost — ~~RESOLVED for sessions~~, gaps remain by design (CP7)
The R5 still rewinds the XCP_OUT chain every control cycle. What CP7 fixed
(hedrive T8): a late/overlapping A53 IPI can no longer kill the session or
corrupt data — command **responses** ride the acknowledged CTO mailbox,
**commands** ride the XCP_IN generation handshake (rewrite-until-acked), and
CTR gaps are gone because the A53 stamps the counter at transmission time.
What remains lossy: **DAQ frames** of a cycle the A53 never saw (counted in
`xcp_gw_ocm_cycles_missed`) — a measurement gap, not a failure. A real OCM
ring buffer would close even that; only worth it if the counters show
meaningful gap rates in practice.

### 2.2 Torn-read window — RESOLVED (CP7)
XCP_OUT now carries a seqlock (odd while the R5 writes, published after the
payload flush). The A53 stages all records in the IPI ISR and commits them
only if the sequence was stable — torn frames can no longer reach the
network. Discards are counted (`xcp_gw_ocm_torn`, `xcp_gw_ocm_skipped_writing`).

### 2.3 Throughput ceiling — MITIGATED (CP7), lwIP knobs remain
`xcp_gw_tx_task` now batches queued records into one ≤1400-byte UDP datagram
per `sendto` (hedrive B1; both CANape and `xcp_poll.py` parse multi-frame
datagrams), and the DAQ queue is a deep burst absorber (262144 records ≈
68 MB heap ≈ 1.5 s at 320 Mbit/s, matching hedrive's multi-second-stall
sizing; tail-drop + `xcp_gw_txq_dropped` on overflow — hedrive B5 final
form). UDP has no backpressure, so PC-side receive pauses are absorbed by
the receiver instead (`xcp_poll.py` sets a 32 MB socket buffer).
If throughput still limits: DAQ prescaler in CANape, or the parked lwIP BSP
knobs (`TCP_SND_BUF`-class tuning does not apply to UDP; pbuf/GEM BD counts
would).

## 3. Safety scope — required before live calibration (Z5)

### 3.1 `DOWNLOAD` can write anywhere in the allow-list — including code
R5 `.text` lives in DDR, and `ApplXcpCheckMemory` has no read/write
distinction, so a stray CANape calibration write can patch running code over
UDP. Options, in increasing effort:
- **Measurement-only build**: drop `RM_CAL_PAG` from `CRM_CONNECT_RESOURCE`
  (xcplite.c CONNECT handler) behind a UZ config switch.
- **Write-specific check**: extend the check callback path with a read/write
  flag (small xcplite.c touch) and deny writes to the `.text`/`.rodata`
  ranges (readable from the ELF/linker map).
- Full Z5 review: range checks per parameter, atomic adoption, rollback —
  see the plan's Phase 4 notes.

### 3.2 Zero authentication
`xcp_gw_rx_task` adopts whoever sends a datagram as master (`gMaster`), and
XCP has no session security here. Acceptable on the isolated lab bench only.
Mitigations if ever needed: bind gateway to a dedicated interface/subnet,
pin the master IP after first CONNECT, or XCP seed&key.

## 4. Fallback honesty

If Option Z fails on hardware, note that the "validated" curated fallback
(`LOGGING_PATH_XCP_LITE`, A53 XCPlite server + MEAS image) **also never ran on
hardware** — it is compile-validated only. The only hardware-proven fallback
is `LOGGING_PATH_JAVASCOPE`.

## 4b. Vendored XCPlite version (upgraded 2026-11-16)

In-tree: upstream **V2.3.4** (github vectorgrp/XCPlite main, "Dev 2.3.4",
2026-11-11), taken file-for-file from the local clone `..\xcp_lite` for every
engine file we vendor (`xcplite.c/h`, `xcp*.h`, `queue32.c`, `queue.h`,
`xcpappl.c`, `platform.h`, `util.c/h`, `dbg_print.h`, the inactive
`cal/persistence/shm/a2l/xcpeth*` headers, new `sockets.h`). The R5 glue
(`xcptl_ocm.c`, `platform_baremetal.c`, `ocm_xcp_fifo.c`) and the public API it
uses (`XcpInit/XcpStart/XcpCreateEvent/XcpEvent/XcpCommand`, the
`ApplXcp*` callbacks, `XcpTl*`) are unchanged by the upgrade. Everything R5
specific lives in `xcplib_r5_cfg.h`, applied at the end of `xcplib_cfg.h`
like upstream's own `xcplib_rtos_cfg.h` override.

What the upgrade brought in (from upstream's CHANGELOG, V2.1.1 → V2.3.4):
the remaining #126 DAQ-configuration robustness (allocation overflow and
`WRITE_DAQ_MULTIPLE` errors invalidate the whole configuration, ODT sizes are
validated before commit, `SET_DAQ_PTR` sequence check, selected lists are
validated before `START_STOP_SYNCH` start), the `XcpSetDaqListMode` link-loop
fix we had already cherry-picked, `XcpEventEnable` range checks, and the
explicit `OPTION_DAQ_EVENT_LIST` / `OPTION_SECTION_REGISTRATION` split (we use
the run-time event list, no linker sections). Behavioural change to note:
`GET_DAQ_RESOLUTION_INFO` now reports the 1 µs clock as `UNIT_1NS` with 1000
ticks per unit instead of `UNIT_1US` with 1 tick (same resolution; the A2L
keeps `0x1 SIZE_DWORD UNIT_1US TIMESTAMP_FIXED`, which is what upstream's
own A2L writer still emits).

Local patches on top of upstream, every one marked `UZ` in the source and
default-off where it touches engine behaviour (re-apply after the next
upgrade — the list is also in the session memory of the coding agent):
- `platform.h`: `ARMR5` → `_BAREMETAL` platform branch (atomics, IRQ
  critical-section mutex, no threads).
- `xcpappl.c`: `_BAREMETAL` accepted as platform, base address 0.
- `xcptl_cfg.h`: `XCPTL_MAX_DTO_SIZE` and `XCPTL_MAX_SEGMENT_SIZE` may be
  predefined (the OCM record cap is 255 B, upstream's MTU formula rounds the
  segment to a multiple of 8 — 256 would not fit; we set 252 = 4 + 248).
- `xcplib_cfg.h`: includes `xcplib_r5_cfg.h` at the end.
- `xcp_cfg.h`: `OPTION_DISABLE_DYN_ADDRESSING` switch (R5 has no
  `XcpEventExt` context to execute event-relative commands).
- `xcplite.c`: `XCP_ENABLE_MTA_RANGE_CHECK` (size check on every
  `XcpReadMta`/`XcpWriteMta`), `calcChecksum` size-0 error and
  `XCP_CHECKSUM_MAX_SIZE` cap.
- `queue32.c`: `packets_lost` read/reset under the queue lock.

Not upgraded: the A53 **fallback** XCPlite server copy in
`vitis/software/FreeRTOS/sw/xcp_lite/` (`LOGGING_PATH_XCPLITE_A53`, not the
Option Z gateway) is still the untouched upstream V2.1.0. Upstream now uses
`queue32m.c`, `sockets.c` and a split `platform.c` for FreeRTOS, so that
copy needs its own port; it is not compiled into the Option Z data path.

The upgrade is compile-validated only (armr5 syntax + object build, external
symbols unchanged: libc, `Xil_DCacheFlushRange`, `uz_SystemTime`); it has
**not** run on hardware yet — rerun TEST_PLAN.md §1–§3 (connect, DAQ, stress)
before trusting it.

## 5. Small stuff

- The checked-in A2L files (`tools/xcp_test/*.a2l`) go stale with every build
  (link addresses move). Consider gitignoring them and always regenerating
  via `gen_a2l.py`.
- `xcp_poll.py --daq` streams a single variable (1 list / 1 ODT / 1 entry).
  Extending to multiple entries/lists would make a nicer demo but adds
  nothing diagnostically.
- `ocm_xcp_fifo.c/h` is intentionally duplicated between
  `Baremetal/src/sw/xcp_engine/` and `FreeRTOS/sw/xcp_gateway/` (each app
  compiles its own copy; `ARMR5` selects the side). Keep the two copies
  byte-identical — or teach both Vitis projects to link one shared folder
  (like `vitis/software/shared/`) to remove the duplication entirely.
