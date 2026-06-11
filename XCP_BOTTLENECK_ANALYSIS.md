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

### B3. RX assumes 1 `read()` = 1 XCP command — framing bug
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

### B5. `QUEUE_XCP_TX_LEN = 10000` — ~680 KB heap, unbounded latency
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
