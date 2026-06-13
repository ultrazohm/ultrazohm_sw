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

### T6. THE root cause: missing portMEMORY_BARRIER in the Xilinx A53 port — **FIXED**
Found by live disassembly of the spinning `xTaskResumeAll()` loop after T5
proved insufficient. The kernel source places `portMEMORY_BARRIER()` inside
the pending-ready drain loop (tasks.c:2248) specifically to force the
compiler to re-read the list head each iteration. The Xilinx ARM_CA53 port
**never defines this macro**, the kernel default is **empty**, all list
macros inline at -O2 — so GCC legally **hoisted `pxTCB` and every derived
pointer out of the `while` loop** (verified instruction by instruction:
loads at 0x9aa4–0x9acc, loop body 0x9ad4–0x9b84 with no reload).
Consequence: whenever **two or more tasks are woken into
`xPendingReadyList` during a single scheduler-suspension window**, the
second iteration re-processes the stale first task, performs pointer
surgery through stale addresses, and corrupts the kernel lists → infinite
loop holding a critical section → `PMR = 0x90` → every interrupt masked →
total freeze, power-cycle only.
This explains the entire incident history: stochastic minutes-scale
failures (probability of a double-wake per window), load dependence, why
the 10 kHz `portYIELD_FROM_ISR` + priority changes made this branch fail
in minutes while develop survives (fewer FromISR wakes per window), the
valid-looking 1-item list in every snapshot, the silent watchpoint on the
list header, and the rotating victim tasks.
**Fix:** `#define portMEMORY_BARRIER() __asm volatile ( "" ::: "memory" )`
in `FreeRTOSConfig.h` (both copies; auto-patched after regeneration by
`vitis_update_platform.tcl` — no BSP parameter exists for it).
Platform/BSP rebuild + app rebuild required.

**Upstream status (verified on GitHub):** AMD/Xilinx fixed this in
`embeddedsw` between releases — `xilinx_v2022.2` (our Vitis, kernel 10.4.6
port): **no** `portMEMORY_BARRIER`; `xilinx_v2023.1` (kernel 10.5.1 port)
and master (10.6.1): defines it **character-for-character identical** to
our workaround. So: known-and-fixed upstream, silently via the kernel
rebase; Vitis ≥ 2023.1 contains it. The failure mode is also publicly
documented in the FreeRTOS forums ("stuck in xTaskResumeAll with more than
two items in xPendingReadyList", Microblaze portMEMORY_BARRIER thread,
"A53 on Zynq UltraScale+ stucks after some time"). Our config-level define
is the correct backport for Vitis 2022.2 and becomes a harmless duplicate
after any future Vitis upgrade.

### T7. lwIP 2.1.1 / GEM (xemacpsif) driver audit — no remaining bomb for our config
Companion audit to T6 (the FreeRTOS-kernel half). Method: compare every
post-2022.2 fix (lwIP upstream 2.1.2/2.1.3/2.2.0 + AMD embeddedsw GEM/lwIP
changelog) against THIS configuration: lwIP 2.1.1, NO_SYS=0 (socket /
tcpip_thread), TCP only (no TLS/IPv6/UDP-app), DHCP on, GEM xemacpsif_dma on
ZynqMP (gigeversion > 2), HW checksum offload, 64/64 RX/TX BDs.

| Post-2022.2 fix | Applies here? |
|---|---|
| GEM RX cache byte-flip / L1-prefetch corruption (the famous ZynqMP one) | ALREADY present in 2022.2 -- our xemacpsif_dma.c RX handler already does Xil_DCacheInvalidateRange(p->payload, rx_bytes) with the "L1 cache prefetch conditions" comment (the fix text). OK |
| GEM RX-hang erratum SI#692601 (resetrx_on_no_rxdata) | N/A -- Zynq-7000 (gigeversion 2) only; no-op on ZynqMP. Our RX watchdog (ebd01c5da) is harmless redundancy. |
| lwIP tcp_recved overflow-check assertion (2.1.2, bug #55015) | Low risk -- edge-case window-update assert; lwIP asserts are active here. One-function backport or LWIP_NOASSERT if ever hit. |
| lwIP RST-from-port-0, poll-assert, TLS use-after-free (2.1.2/2.1.3) | Cosmetic / N/A (no TLS, no socket-poll). |
| AMD "TCPIP_CORE_LOCK not released when LWIP_TIMERS==0" (lwip220, 2025.1) | N/A -- we have LWIP_TIMERS==1 (NO_SYS=0). |
| emacps post-2022.2: 10GbE, multi-packet, priority queuing, SGMII/PHY (2024.2+) | N/A -- features, not fixes; standard 1G GEM + existing PHY. |

Verdict: no stability landmine in the lwIP/GEM half matching this config --
the one famous data-corruption bug is already fixed in 2022.2 and the RX-hang
erratum does not apply to ZynqMP. Residual items are throughput knobs, not
bugs: MEMP_NUM_PBUF = 16 (small), TX BD ring = 64, TCP_SND_BUF = 8192 (the
window ceiling discussed under throughput). Same caveat as T6: changelog-
mining cannot catch a silently fixed bug (T6 itself was not in any changelog)
-- but every known post-2022.2 fix is already present, N/A, or a sizing knob.

### T5. Earlier finding (real, but not the trigger): FPU context not saved on task switch — **FIXED**
All "stall" incidents (T2's priority fix and the GEM watchdog helped real but
secondary issues) shared one true root cause, finally caught **live** in the
debugger: the CPU was not blocked but **spinning inside `xTaskResumeAll`
(tasks.c:2250)** on a corrupted (circular) `xPendingReadyList`, holding a
critical section → GIC `PMR = 0x90` → every interrupt masked (tick, GEM, IPI
all pending in `ISPENDR`, never delivered) → scheduler dead, network dead,
only power-cycle recovers.

**Mechanism:** the BSP had `configUSE_TASK_FPU_SUPPORT = 1`: FP/NEON
registers are saved on context switch **only for tasks that called
`vPortTaskUsesFPU()` — and no task in the codebase ever did**. On aarch64,
GCC uses NEON Q-registers inside ordinary `memcpy` (proven via objdump:
callers include `prvCopyDataToQueue` — the FreeRTOS kernel itself — plus
`ocm_eth_adapter_tx/rx`, `tcp_write`, `pbuf_*`). A task preempted mid-memcpy
resumes with corrupted Q-registers and completes the copy with garbage;
when the victim copy involved kernel/queue data, kernel lists corrupted.
Stochastic (227 s / 447 s observed), load-dependent. The XCP work made it
acute: the 10 kHz `portYIELD_FROM_ISR` (B2) plus lower task priorities
multiplied preemptions by orders of magnitude — develop's polling-style
JavaScope path rarely preempts, which is why it survives 140 Mbit/s runs.

**Fix:** `configUSE_TASK_FPU_SUPPORT = 2` (FPU context for ALL tasks), set in
three places: the generated `FreeRTOSConfig.h` (both copies, immediate), the
domain's `system.mss` (`use_task_fpu_support = 2`, survives `bsp
regenerate`), and `tcl_scripts/vitis_update_platform.tcl` (`bsp config
use_task_fpu_support 2`, survives platform updates — same mechanism as the
heap-size precedent). Requires a **platform/BSP rebuild, then the FreeRTOS
app**; the R5/Baremetal is unaffected (no FreeRTOS).

### T2. Network stack stall under sustained DAQ load — **FIXED** (secondary)
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

### R2. XCP event dividers hardcoded to a 10 kHz base — **FIXED** (+ important correction)
**Correction to the earlier analysis:** the ISR actually still runs at
**10 kHz** — `UZ_PWM_FREQUENCY = 10.0e3f` configures the PWM IP, and the
active trigger choice (`INTERRUPT_ISR_SOURCE_USER_CHOICE = 1` →
`Interrupt_2L_min`, factor 1) fires once per PWM period. So the XCP event
dividers were coincidentally correct. The "10→20 kHz" feature commit only
regenerated the **Simulink FOC model** for a 50 µs step (`FOC_T_fast` =
5e-5) — see the new finding below.
**Fix anyway:** dividers now derived from
`UZ_PWM_FREQUENCY × Interrupt_ISR_freq_factor`, so the named events stay
correct under any future PWM/trigger change. Timestamp shares the cycle.

### ⚠ NEW finding (control domain, NOT fixed — needs owner decision):
The FOC model (`FOC_FCF_data.c`) was regenerated for a **50 µs** step
(20 kHz), but the PWM IP and the control ISR run at **10 kHz** (100 µs):
all model-internal time constants/integrators execute 2× slower than
designed. Either set `UZ_PWM_FREQUENCY = 20.0e3f` (and verify PWM hardware
+ CPU headroom) or regenerate the model for 100 µs.

### R3. DAQ timestamp unit inconsistent — **FIXED**
Was: `xcp_timestamp += 1` per ISR cycle while `xcp_cfg.h` declared
`DAQ_TIMESTAMP_UNIT_10NS` — masters using slave timestamps got a time axis
off by orders of magnitude.
**Fix:** timestamp now sourced from `uz_SystemTime_GetUptimeInUs()` once per
cycle (all events of a cycle share it) and declared as
`DAQ_TIMESTAMP_UNIT_1US`, ticks-per-unit 1.

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

### R4. Duplicated protocol file — **FIXED**
Was: `RPU_APU_exchange.c/.h` existed as two copies (R5 + APU) that had
already diverged once.
**Fix:** single-sourced in `vitis/software/shared/` (`RPU_APU_exchange.h` +
`RPU_APU_exchange_impl.c`), resolved via the shared include path both
projects already use for `APU_RPU_shared.h`. Each app compiles the
implementation through a thin local stub
(`.../sw/xcp/RPU_APU_exchange.c` → `#include "RPU_APU_exchange_impl.c"`);
the per-side behaviour is selected by the BSP's `ARMR5` define.

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
