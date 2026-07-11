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

### 1.1 `xcp_r5_poll()` runs inside `ISR_Control` — MEASURED 2026-07-11, acceptable
Command processing, DAQ queue drain, and cache flushes all execute in the
~100 µs control ISR (`Baremetal/src/sw/isr.c`). Measured via `uz_SystemTime`
`isr_execution_time_us` under `--stress` load (10 kHz):

| DAQ payload/cycle | ISR exec | note |
|---|---|---|
| XCP idle | 16.1 µs | engine adds ~10 µs over the non-XCP baseline |
| 100 B | 18.3 µs | |
| 1000 B (80 Mbit/s) | 27.1 µs | |
| 4000 B (326 Mbit/s) | 52.9 µs | soak-validated worst case; 47 µs headroom |

Scaling is linear: **~10 µs base + ~9–10 µs per KB of DAQ payload per cycle**
(two copies: XcpEvent sample→queue + poll queue→OCM, plus cache flushes).
Budgeting rule for real control applications: reserve
`16 µs + 10 µs × (KB/cycle)` for XCP. If a heavy controller needs the
headroom back, the prepared lever stands: move `xcp_r5_poll()` +
`XIpiPsu_TriggerIpi` to the R5 main loop (halves the marginal cost — only
the XcpEvent sampling copy must stay in the ISR; the mutex in
`platform_baremetal.c` already makes the split safe).

### 1.2 Declared vs real DAQ event rate (cosmetic)
`XcpCreateEvent("DAQ_R5", 1000000, 0)` in `xcptl_ocm.c` declares 1 ms; the
event actually fires at the control rate (likely 100 µs). Only affects
CANape's displayed rate. Align the constant once the real rate is confirmed
on the bench.

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

## 4b. Vendored XCPlite version (checked 2026-07-11)

In-tree: **V2.1.0** (imported 2026-06-16) + one local fix (queue32.c
`queuePop` reported `packets_lost` after zeroing it — upstream adopted the
same fix later). Upstream: V2.1.5 (2026-06-18), **V2.1.6 (2026-07-08)**.
Diffed V2.1.0→V2.1.6 for every file we vendor: no fix we are exposed to —
the rest is refactoring (EPK API renames, xcp_evts event-registry rework,
`ApplXcpRegisterIdleCallback`, atomic event counter for multithreaded
producers, `queue32m.c` critical-section queue for FreeRTOS targets) that
affects neither the single-context R5 engine nor the OCM transport. The
harmless boot warning `No xcp_evts section found` is restructured upstream
(we register events at runtime; the section legitimately doesn't exist).
An upgrade to V2.1.6 is a backlog item (touches cfg headers +
`platform_baremetal.c` against renamed APIs; the A53 fallback path would
also need `queue32m.c`) — do it after the soak, not mid-bring-up.

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
