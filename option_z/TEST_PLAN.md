# Option Z — test plan (XCPlite engine on the R5)

Option Z is **fully wired and both apps build green**, but it has **not run on
hardware** — the integration was done "assume it works". Test it incrementally:
each step isolates one layer so a failure points at a specific place. If you get
stuck, the **fallback** (bottom) returns you to the validated curated path.

> **2026-07-04 hardening pass (pre-hardware audit).** A code audit of the whole
> untested path found and fixed 8 defects before this test plan was ever run:
> (1) A53 boot crash — IPI ISR ran up to ~7.5 s before the gateway queues
> existed (`gGwReady` guard added); (2) size-chain corruption — MAX_DTO 1024 /
> segment 7968 vs the 255-byte FIFO record cap (R5 now MTU 284 → segment 252,
> CTO/DTO 248/248, matching `gen_a2l.py`); (3) DAQ data never left the queue —
> `queuePop(flush=false)` never returns a lone open segment (now `flush=true`
> per cycle); (4) duplicate command execution on a delayed IPI (R5 now zeroes
> the XCP_IN chain head after consuming it); (5) **R5 data abort from the
> network** — no memory access check; any bad address in SHORT_UPLOAD/DOWNLOAD/
> DAQ killed the control core (allow-list added: ATCM/BTCM/DDR/OCM only, else
> ERR_ACCESS_DENIED); (6) CTO reserve 256 < max CRM record 260 and XCP_IN too
> small (now reserve 512, XCP_IN 1024); (7) IPI status cleared *after* handling
> → lost cycles (now cleared first); (8) failed init crashed the ISR instead of
> disabling XCP (`gQueue` guards + `xcp_r5_init_result` latch).
> New diagnostics: `xcp_r5_init_result`, `xcp_r5_cycle_count`,
> `xcp_r5_tx_oversize_drop` (all readable via JTAG or `--watch`).

## Configuration (what's active)

| Flag | File | Value | Meaning |
|------|------|-------|---------|
| `XCP_ENGINE_R5_ENABLE` | `Baremetal/src/defines.h` | **1** | R5 runs the XCPlite engine |
| `LOGGING_PATH_XCP_R5_GATEWAY` | `FreeRTOS/defines.h` | **1** | A53 runs the UDP⇄OCM gateway |
| `LOGGING_PATH_XCP_LITE` / `_JAVASCOPE` | `FreeRTOS/defines.h` | 0 | (off) |

Data path: `CANape/xcp_poll ⇄ UDP:5556 ⇄ A53 rx/tx tasks ⇄ queues ⇄ APU_IPI_ISR
⇄ OCM FIFO ⇄ R5 XcpCommand/XcpEvent` (engine, identity addressing). OCM regions:
`XCP_IN 0xFFFFC000` (A53→R5), `XCP_OUT 0xFFFFE000` (R5→A53).

## Build & flash

1. Build **both** apps (Vitis IDE rebuilds the makefiles and auto-compiles the
   new `xcp_engine/` and `xcp_gateway/` folders; the Baremetal app already
   passes `-DARMR5`). Or use the verified `make` outputs already in the Debug
   folders.
2. Flash **both** `Baremetal.elf` (R5) and `FreeRTOS.elf` (A53).

## Test 1 — both cores boot (serial console, 115200)

Expect the R5 banner (`Welcome to the UltraZohm`, `RPU: Build Date…`) and the
A53 line:
```
APU: XCPlite slave (UDP) at 192.168.1.233:5556
```
- ✅ both appear → cores up, `xcp_r5_init` didn't assert, gateway init ran.
- ❌ no A53 line / hang → A53 gateway init failed (socket/bind) or a mode flag is
  wrong. ❌ R5 silent → `xcp_r5_init` (queueInit malloc, XcpInit) faulted; check
  the R5 heap size in the linker script.

> Note: the R5 engine runs with debug prints **off** (no XCP chatter on R5
> serial) — that's intentional (no stdout retarget in the control ISR).

## Test 2 — connectivity (no CANape)

```
python tools/xcp_test/xcp_poll.py --ip 192.168.1.233
```
The default is now **connect-only**: CONNECT, print `MAX_CTO=248 MAX_DTO=248`,
exit. (It no longer polls the A53 demo addresses — those are invalid on the R5
slave and are behind `--demo` for the curated A53 build.)

- ✅ `CONNECTED` → the whole path works: UDP → gateway → OCM → R5 engine →
  CONNECT response → OCM → gateway → UDP. This is the big one.
- ❌ `no XCP response` (timeout) → the command isn't completing the round trip.
  See **Debugging** below.

## Test 3 — arbitrary R5 measurement (the Option Z payoff)

Read any R5 variable **by name** from the R5 ELF (no curated struct):
```
python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 ^
  --watch xcp_r5_cycle_count:u32 --watch xcp_r5_init_result:i32
```
(`--elf` defaults to `FreeRTOS.elf`; unresolved names fall back to
`Baremetal.elf` automatically.) `xcp_r5_cycle_count` increments every control
cycle — if it climbs, the R5 engine is alive; `xcp_r5_init_result` must be 0.
Pick further variables that move, e.g. a `Global_Data.av.*` address
(get it from `armr5-none-eabi-nm Baremetal.elf`) once currents flow.

- ✅ values read back and update → arbitrary addressing through the full stack
  works. **Option Z is proven.**
- ❌ `CONNECTED` but reads time out → SHORT_UPLOAD path issue (address handling
  on the R5, or DTO/CRM framing). See Debugging.
- ❌ `ERR_ACCESS_DENIED` (0x24) → the address is outside the R5 allow-list
  (ATCM/BTCM/DDR/OCM, `xcp_r5_check_memory` in `xcptl_ocm.c`) — by design.

## Test 3b — DAQ smoke test (streams like CANape, without CANape)

```
python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 --daq
```
Sets up a real dynamic DAQ list (1 list / 1 ODT / 1 entry, timestamped, event 0
= `DAQ_R5`) on `xcp_r5_cycle_count` and streams it for 3 s.

- ✅ `DAQ OK: N samples … (~F Hz)` with F ≈ the control frequency → the entire
  DAQ path (XcpEvent → queue → OCM → gateway → UDP) is proven; CANape will work.
- ❌ commands OK but `no DTOs received` → DAQ transmit path: check
  `ocm_xcp_w_dropped` / `xcp_r5_tx_oversize_drop` on the R5 and `gMasterValid`
  on the A53 (JTAG).

## Test 4 — CANape (optional)

```
python tools/xcp_test/gen_a2l.py --elf vitis/workspace/Baremetal/Debug/Baremetal.elf ^
  --symbols "xcp_r5_cycle_count:u32,xcp_r5_init_result:i32" --ip 192.168.1.233 ^
  --out UltraZohm_XCP_R5.a2l
```
Attach to a CANape XCP/UDP device at `192.168.1.233:5556`, measure, and try DAQ
on the `DAQ_R5` event.

## Debugging (it's untested — likely first-try issues)

Inspect these via the JTAG debugger (the R5 keeps stats):
- **Engine health globals** (`xcp_engine/xcptl_ocm.c`): `xcp_r5_init_result`
  (0 = ok, -1 queueInit, -2 XcpInit, -3 event, 0x7FFFFFFF = init never ran) and
  `xcp_r5_cycle_count` (must climb at the control rate). If init failed, the
  engine self-disables (`gQueue == NULL` guards) instead of crashing the ISR.
- **OCM FIFO counters** (`vitis/software/Baremetal/src/sw/xcp_engine/ocm_xcp_fifo.c`):
  `ocm_xcp_w_dropped` (write region full) and `ocm_xcp_r_overrun` (bad
  length / past region). Non-zero → framing or sizing problem. Also
  `xcp_r5_tx_oversize_drop` (popped segment > 255 B — must stay 0; the R5
  config bounds segments to 252 B).
- **R5 ISR budget**: the R5 runs `xcp_r5_event()` + `xcp_r5_poll()` + IPI inside
  `ISR_Control` at the control rate. If `uz_SystemTime` ISR-exec jumps, the
  command/DAQ work is too heavy for the 100 µs budget — move `xcp_r5_poll()` to
  the main loop and trigger the IPI at a divided rate.
- **IPI fires**: the A53 `APU_IPI_ISR` (gateway branch) must run each R5 cycle.
  Breakpoint `xcp_gateway_a53_on_ipi`. If never hit, the R5 `XIpiPsu_TriggerIpi`
  isn't reaching the A53 (mask/registration).
- **Master learned**: the A53 `tx_task` drops frames until `gMasterValid` is set
  by the first received datagram (`gMaster`). So a CONNECT must arrive before any
  response can be sent back — `xcp_poll`/CANape do CONNECT first, so this is
  fine, but verify `gMasterValid==1` after connecting.
- **Cache coherency**: the FIFO uses `Xil_DCacheFlushRange`/`InvalidateRange`
  around the sweep. If reads look stale/torn, check the OCM region is mapped the
  same way the curated MEAS image is (it works, so this should too).
- **Endianness/framing**: a TL frame is `[dlc:u16 LE][ctr:u16 LE][packet]`; the
  FIFO prepends a `u32` length. The A53 forwards the TL frame verbatim as the UDP
  payload. If CANape rejects responses, dump the bytes.

### Known residual risks (accepted for bring-up)

- **Lossy-by-design channel**: the R5 rewinds XCP_OUT every control cycle. If
  the A53's IPI handling ever slips past a full cycle, that cycle's DAQ frames
  are gone — visible to the master as transport-counter (ctr) gaps, and to
  CANape as overload. Commands can also be lost in the mirror-image race after
  the R5's consume-zeroing of XCP_IN; the master's retry covers it.
- **ISR budget**: `xcp_r5_poll()` (command processing + queue drain + cache
  flushes) runs inside `ISR_Control`. Watch `uz_SystemTime` ISR-exec time under
  DAQ load; if it jumps, move `xcp_r5_poll()` to the main loop.
- **DAQ rate**: event 0 fires at the full control rate; a DAQ list without
  prescaler streams one UDP datagram per cycle. If lwIP chokes, set a
  prescaler in CANape (or reduce the measurement).

## Fallback to the validated curated path

If Option Z misbehaves and you want the known-good demo back, set:
- `Baremetal/src/defines.h`: `XCP_ENGINE_R5_ENABLE 0`
- `FreeRTOS/defines.h`: `LOGGING_PATH_XCP_R5_GATEWAY 0`, `LOGGING_PATH_XCP_LITE 1`

Rebuild + reflash → the curated A53 path (Phases 0/1/3, the ISR-timing demo)
runs exactly as before. These are independent compile-time modes; both build
green.
