# XCP Implementation — Bottleneck Analysis

Audit of the full XCP data path on the A53/FreeRTOS side:

```
R5 (XCP slave, XcpBasic)
  └─ OCM FIFO (RPU_APU_exchange: XCP_OUT @ 0xFFFFE000/512 B, XCP_IN @ 0xFFFFC000/256 B)
       └─ IPI ISR  (Transfer_ipc_Intr_Handler → ocm_eth_adapter_irq)
            └─ FreeRTOS queues (queue_xcp_tx / queue_xcp_rx)
                 └─ TCP tasks (ocm_eth_adapter_tx / _rx, port 12340)
                      └─ XCP master (CANape)
```

Files: `vitis/software/FreeRTOS/sw/xcp/OCM_eth_adapter.c`,
`vitis/software/FreeRTOS/sw/xcp/RPU_APU_exchange.c`,
`vitis/software/FreeRTOS/sw/isr.c`

Constraint: fixes are **application-code only** — no lwIP/BSP/lwipopts changes.

---

## Already fixed (committed)

### F1. System freeze: blocking calls from ISR context — `5067f8179`
`read_OCM_write_txQueue()` (runs in the IPI ISR) called `vTaskDelay(5)` and
`xil_printf()` when `queue_xcp_tx` was full. Both are illegal from ISR context:
`vTaskDelay` suspends the *interrupted* task and breaks `xTaskResumeAll`,
corrupting the scheduler. Observed as `tcpip_thread` wedged in
`xTaskResumeAll`/`xQueueReceive`; only a power-cycle recovered. The 20 kHz PWM
(doubled DAQ rate) made the TX-queue overflow easy to hit.
**Fix:** on queue-full → drop frame, count (`xcp_txq_overflow_dropped`), set
`xcp_txq_purge_requested`; TX task resets the queue (drops stale backlog).
Never block/delay/print in ISR context.

### F2. XCP only worked for the first connection per boot — `3d08480f4`
TX worker was created once (`flag_xcp_eth_tx_created_once`) and never
recreated; both workers got `&new_sd` (dangling pointer to a loop-local);
double `close()` on the shared fd; RX task leaked on queue-full.
**Fix:** fd passed by value, fresh TX+RX pair per connection, accept loop
waits for both workers to exit and closes the fd exactly once, single master
at a time.

---

## Open bottlenecks (prioritized)

### B1. One `write()` per 68-byte frame — main throughput limiter — **FIXED**
**Where:** `ocm_eth_adapter_tx()`
**Problem:** every XCP frame is sent with its own socket `write()`. In the
Xilinx lwIP socket layer each send is marshalled through the `tcpip_thread`
mailbox — a full round-trip per 68 bytes. At DAQ rates this floods
`tcpip_thread` (the same mbox machinery the freeze stack sat in) and caps
throughput by *calls/sec*, not bytes/sec.
**Fix (code-only):** drain up to N frames from `queue_xcp_tx` into a
~1400-byte staging buffer (≈ one TCP MSS) and `write()` once.
≈ 20× fewer socket calls. This is the develop-branch JavaScope batching
pattern applied to the XCP path.

### B2. No yield after ISR enqueue — up to one tick of added latency — **FIXED**
**Where:** `read_OCM_write_txQueue()` / `Transfer_ipc_Intr_Handler`
**Problem:** `xQueueSendFromISR(..., NULL)` discards the
`xHigherPriorityTaskWoken` result and in XCP mode nothing yields at ISR end,
so the TX task is only scheduled at the next tick interrupt (typ. 100 Hz →
up to **10 ms** avoidable latency per wakeup).
**Fix:** thread a `BaseType_t woken` through `ocm_eth_adapter_irq()` and
`portYIELD_FROM_ISR()` it at the end of the IPI ISR.

### B3. RX assumes 1 `read()` = 1 XCP command — framing bug — **FIXED**
**Where:** `ocm_eth_adapter_rx()`
**Problem:** TCP is a byte stream. During connection setup CANape sends
command bursts (`SET_DAQ_PTR`/`WRITE_DAQ` flurries) that can coalesce into
one segment or split across reads. The code reads ≤ 68 bytes and forwards
the buffer as-is: a coalesced second command is silently lost (CANape
timeout); a split command corrupts parsing on the R5.
Related: `rpu_apu_exchange_writeOCM(BUF_SIZE_XCP_RX, …)` always writes the
fixed 68 bytes, including garbage tail bytes, regardless of how many bytes
`read()` returned.
**Fix:** parse the 4-byte XCP length header in a staging buffer; forward
only complete messages with their actual length.

### B4. `XCP_IN` OCM region can silently overflow — **FIXED**
**Where:** `read_rxQueue_write_OCM()` + `RPU_APU_exchange.c`
**Problem:** the per-ISR drain writes the *entire* RX queue (up to 10
commands) into `XCP_IN`, but the region is **256 bytes** ≈ room for ~3
commands (4-byte len + 68-byte payload each). A burst of 4+ commands
overruns the region — no bounds check, silent corruption of adjacent OCM.
**Fix:** bound the per-ISR drain by remaining region space; leave the rest
queued for the next ISR.

### B5. `QUEUE_XCP_TX_LEN = 10000` — ~680 KB heap, unbounded latency — **FIXED**
**Where:** `OCM_eth_adapter.c` configuration
**Problem:** 10000 × 68 B ≈ 680 KB of FreeRTOS heap for the TX queue, and a
"full" queue represents seconds of stale backlog (which is what made the
purge so violent). With backpressure (F1) in place, a much smaller queue
gives bounded worst-case latency.
**Fix:** reduce to ~256–1024 entries (one `#define`).

### B6. Minor ISR costs (acceptable, listed for completeness)
- Debug counters (`try_to_read_ocm`, `msg_*`) incremented in ISR context.
- Two full-range cache flush/invalidates (512 B + 256 B) per IPI ISR.
- `Xil_DCacheFlushRange` (clean+invalidate) is used where a pure invalidate
  would do for the read direction; harmless today because the A53 never
  dirties the `XCP_OUT` lines, but fragile if that ever changes.
- Accept loop polls worker-exit flags at 20 ms — negligible.

## Hardware test findings

### T1. Request timeout ~4 min into a DAQ measurement — **FIXED**
First hardware test after F1/F2/B1/B2/B4: no more freezes (R5 keeps
running, `tcpip_thread` stack shows its normal idle mbox-fetch), but CANape
reported "Timeout: Keine Response zur Request-Message empfangen" ~4 min
into a measurement.
**Mechanism:** DAQ production slightly exceeded TCP drain, so the (then
10000-deep) TX queue filled slowly — a surplus of ~40 frames/s fills it in
~4 min. A CTO response enqueued behind thousands of DAQ frames exceeds the
master's response timeout; alternatively the overflow purge wiped the
response together with the stale DAQ backlog. Either way: no response →
session timeout.
**Fix:** dedicated CTO queue (`queue_xcp_tx_cto`, classified in the ISR by
XCP PID ≥ 0xFC = RES/ERR/EV/SERV). CTO responses jump the DAQ backlog in
the TX batch, are never purged, and the ISR keeps draining the OCM on
DAQ-queue overflow so a trailing CTO still gets through. Plus B5: DAQ queue
shrunk 10000 → 512 (bounded backlog latency, ~645 KB heap freed).
**Expected behaviour under sustained overload now:** DAQ gaps
(`xcp_txq_overflow_dropped` climbs, purges drop stale samples) but the
session stays alive and responsive.

### T2. Network stack stall under sustained DAQ load — **FIXED**
After T1: A53 "stalled" with `xemacif_input_thread` (and earlier
`tcpip_thread`) parked in their idle waits; R5 unaffected. Those stacks are
the threads' *normal* blocked states — the real failure was that no network
data moved anymore: a livelock, not a scheduler freeze.
**Mechanism (priority inversion):** the XCP workers ran at priority 4/5,
**above** the BSP's lwIP threads (`TCPIP_THREAD_PRIO` =
`DEFAULT_THREAD_PRIO` = 2). Under sustained DAQ load the TX worker (woken up
to 20 k×/s, batching hard) starved `xemacif_input_thread`/`tcpip_thread` →
CANape's ACKs were not processed → the 8 KB `TCP_SND_BUF` never reopened →
`write()` blocked; GEM RX can die permanently once its buffers run dry.
**Fix:** `PRIO_XCP_TX`/`PRIO_XCP_RX` lowered to **1** (below the network
stack). XCP consumes leftover CPU; overload now lands in our DAQ queue
(drops + purge, session-safe) instead of inside lwIP (fatal).
**If throughput gaps become an issue later:** the proper lever is the BSP
(`TCP_SND_BUF` 8 K → 32 K, cf. develop's TODO in its ethernet.c) — BSP
settings can be made regeneration-proof via `vitis_update_platform.tcl`,
which already patches the FreeRTOS heap the same way. Parked per the
no-lwIP/BSP-changes constraint.

---

## Deep dive: R5 side (XcpBasic + glue)

Audited after the disconnect fixes: `Baremetal/src/sw/xcp/xcp_interface.c`,
`XCP_Basic/xcp_cfg.h`, R5 copy of `RPU_APU_exchange.c`, call site in
`Baremetal/src/sw/isr.c:198` (`xcp_irq()` inside `ISR_Control`).

### R1. Unbounded DAQ burst into the 512-byte XCP_OUT window — **FIXED**
`XCP_DISABLE_SEND_QUEUE` is set, so XcpBasic sends *direct*: every DAQ
sample of every event goes through `ApplXcpSend` → `rpu_apu_exchange_writeOCM`
**in the same ISR cycle**. The R5 copy of `writeOCM` has **no bounds check**
(unlike the APU copy since B4), and `kXcpDaqMemSize = 2 KB` allows CANape DAQ
configs that produce far more than the 512-byte window per cycle.
Overflow consequences compound on the APU side: `readOCM` follows the
length-chain **past the region end** (unbounded, in ISR context — with
garbage lengths it can walk far beyond OCM), and the cache-invalidate only
covers 512 B, so overflowed frames are read stale → garbage to CANape.
**Fix (two halves):**
- R5: port the B4 bounds check to the R5 copy of `writeOCM` (drop + count).
  Optionally enable `XCP_ENABLE_SEND_QUEUE` so XcpBasic buffers DTOs in its
  2 KB DAQ memory and the glue drains ≤ window-budget per cycle (no loss,
  bounded ISR time) — requires restructuring the `XcpSendCallBack()` call.
- APU: bound `readOCM` to the region end (mirror of B4 for the read side).

### R2. XCP event rates are 2× off since the 20 kHz PWM change
`xcp_interface_events_10kHz()` derives the 1ms/10ms/100ms/1s events from
fixed dividers (10/100/1000/10000) assuming a **10 kHz** base, but
`xcp_irq()` runs at `UZ_PWM_FREQUENCY` = **20 kHz** since the feature merge.
All named event periods are half their label (1MS fires every 0.5 ms, 1S
every 0.5 s), and `XCP_EVENT_FAST` doubled its data volume (which is what
overloaded the TX path originally).
**Fix:** derive the dividers from `UZ_PWM_FREQUENCY` instead of hardcoding.

### R3. DAQ timestamp unit inconsistent
`xcp_timestamp += 1` per ISR cycle (50 µs at 20 kHz), but `xcp_cfg.h`
declares `kXcpDaqTimestampUnit DAQ_TIMESTAMP_UNIT_10NS`. If CANape uses
slave timestamps, the time axis is off by orders of magnitude (works today
only if CANape is set to PC arrival time). The commented hint
`uz_SystemTime_GetUptimeInUs()` + unit `1US` would make it consistent.

### T3. CANape "Ungültiger Zähler im XCP-Transport-Layer-Header" — **FIXED**
Counter errors right at measurement start (expected 130/131/132, received
131/130/132 = reordered). Root cause: the transport CTR was assigned on the
**R5 at production time** (`ApplXcpSend`), but the T1 fix deliberately
reorders frames (CTO responses overtake queued DAQ frames), and every
intentional drop (queue overflow, purge, OCM bounds) creates CTR gaps.
**Fix:** the A53 — the actual TCP transport endpoint — now owns the CTR and
stamps it in `tx_batch_append()` at transmission time, in transmission
order (reset per connection). Reordering and drops are no longer visible at
the transport layer; dropped DAQ frames appear only as measurement gaps.

### Throughput: XCP_OUT window 512 B → 7680 B — **DONE**
`XCP_OUT` grown to 7680 B (~100 DTO frames/cycle, 15× the old budget; end
address 0xFFFFFE00 deliberately below the 32-bit wrap on the R5). The last
256 B are a **CTO reserve** (R5 write side only): a DAQ burst can never
squeeze out a command response. Cache cost handled: the A53 invalidates
lazily per message in `readOCM` (instead of the whole window every IPI),
and both sides flush only the bytes actually written. APU-side IPI-ISR
drain capped at 32 frames/IRQ to bound ISR time.
**Both ELFs must always be rebuilt together after OCM layout changes.**

### R4. Duplicated protocol file
`RPU_APU_exchange.c/.h` exist as **two copies** (R5: `Baremetal/src/sw/xcp/`,
APU: `FreeRTOS/sw/xcp/`) sharing the OCM layout via duplicated `#define`s.
They have now diverged (B4 only on APU). Any change to the region
addresses/sizes must be made in both; longer-term the file should be shared
like `APU_RPU_shared.h`.

### Headroom note
The 512 B/cycle window ≈ 6–7 DTO frames ≈ ~7 MB/s theoretical at 20 kHz —
adequate *if respected* (R1). OCM bank 3 has ~7.5 KB unused above
`XCP_OUT`; the window could grow (e.g. 2–8 KB) if more per-cycle DAQ volume
is ever needed — must be changed in both copies (R4) and in the APU
cache-invalidate range.

---

### Deliberately out of scope (user constraint: no lwIP/BSP changes)
- `TCP_NODELAY` via `setsockopt()` on the accepted socket would reduce
  Nagle-induced stalls on CTO responses. It is a per-socket *code* call, not
  an lwipopts edit, but is parked until explicitly approved.
- lwIP buffer/priority tuning (`TCP_SND_BUF`, `TCPIP_THREAD_PRIO`, …).

---

## Suggested implementation order

| Step | Item | Risk | Expected effect | Status |
|------|------|------|-----------------|--------|
| 1 | B1 batching | low | biggest DAQ throughput gain, less tcpip_thread load | fixed |
| 2 | B2 ISR yield | low | up to ~10 ms latency removed per wakeup | fixed |
| 3 | B3 RX framing | medium | no lost/corrupt commands in bursts | open |
| 4 | B4 XCP_IN bound | low | removes silent OCM corruption | fixed (APU side; R5 copy of RPU_APU_exchange.c unchanged) |
| 5 | B5 queue size | trivial | ~600 KB RAM freed, bounded latency | open |

Each step is independently committable and hardware-testable (CANape DAQ
load test + connect/disconnect/reconnect cycles).

---
*Generated 2026-06 on branch `merge-freertos-from-develop`; analysis as of
commit `3d08480f4`.*
