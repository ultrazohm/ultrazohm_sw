# Option Z — test plan (XCPlite engine on the R5)

Option Z is **fully wired and both apps build green**, but it has **not run on
hardware** — the integration was done "assume it works". Test it incrementally:
each step isolates one layer so a failure points at a specific place. If you get
stuck, the **fallback** (bottom) returns you to the validated curated path.

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
The default poll resolves demo symbols from `FreeRTOS.elf` and will fail to find
them (those are A53 symbols) — that's fine; what matters is **`[+] CONNECTED`**.

- ✅ `CONNECTED` → the whole path works: UDP → gateway → OCM → R5 engine →
  CONNECT response → OCM → gateway → UDP. This is the big one.
- ❌ `no XCP response` (timeout) → the command isn't completing the round trip.
  See **Debugging** below.

## Test 3 — arbitrary R5 measurement (the Option Z payoff)

Read any R5 variable **by name** from the R5 ELF (no curated struct):
```
python tools/xcp_test/xcp_poll.py --ip 192.168.1.233 ^
  --elf vitis/workspace/Baremetal/Debug/Baremetal.elf ^
  --watch xcp_r5_daq_event:u16 --watch apu_version_final:u32
```
Pick variables that move for a livelier demo, e.g. a `Global_Data.av.*` address
(get it from `armr5-none-eabi-nm Baremetal.elf`) once currents flow, or add a
free-running counter to the R5.

- ✅ values read back and update → arbitrary addressing through the full stack
  works. **Option Z is proven.**
- ❌ `CONNECTED` but reads time out → SHORT_UPLOAD path issue (address handling
  on the R5, or DTO/CRM framing). See Debugging.

## Test 4 — CANape (optional)

```
python tools/xcp_test/gen_a2l.py --elf vitis/workspace/Baremetal/Debug/Baremetal.elf ^
  --symbols "xcp_r5_daq_event:u16,apu_version_final:u32" --ip 192.168.1.233 ^
  --out UltraZohm_XCP_R5.a2l
```
Attach to a CANape XCP/UDP device at `192.168.1.233:5556`, measure, and try DAQ
on the `DAQ_R5` event.

## Debugging (it's untested — likely first-try issues)

Inspect these via the JTAG debugger (the R5 keeps stats):
- **OCM FIFO counters** (`option_z`/`xcp_engine/ocm_xcp_fifo.c`):
  `ocm_xcp_w_dropped` (write region full) and `ocm_xcp_r_overrun` (bad
  length / past region). Non-zero → framing or sizing problem.
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

## Fallback to the validated curated path

If Option Z misbehaves and you want the known-good demo back, set:
- `Baremetal/src/defines.h`: `XCP_ENGINE_R5_ENABLE 0`
- `FreeRTOS/defines.h`: `LOGGING_PATH_XCP_R5_GATEWAY 0`, `LOGGING_PATH_XCP_LITE 1`

Rebuild + reflash → the curated A53 path (Phases 0/1/3, the ISR-timing demo)
runs exactly as before. These are independent compile-time modes; both build
green.
