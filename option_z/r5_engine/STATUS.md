# Option Z — XCPlite engine on the R5 (status)

Goal: run XCPlite's **protocol engine on the R5** (the control core) with the A53
as an Ethernet gateway — the `uz_sw_xcp_hedrive_andi` architecture, but with
**MIT XCPlite** instead of the non-redistributable XCP Basic. This gives
**arbitrary-address** measurement + calibration, which the A53-image approach
(Phases 0/1/3, already working) cannot.

See `XCPLITE_DEMO_PLAN.md` → "Option Z" for the rationale and milestones.

## Code-complete & compile-verified (2026-06-17)

The full Option Z stack is written and compiles/links for both toolchains.
What remains is Vitis assembly + on-hardware bring-up (see "Integration").

| Milestone | State |
|-----------|-------|
| Z1 engine on armr5 | ✅ engine (`xcplite/queue32/util/xcpappl`) compiles unchanged for armr5 + `_BAREMETAL` platform branch |
| Z2 R5 transport | ✅ `xctpl_ocm.c` (engine TL + `xcp_r5_init/event/poll`) + `ocm_xcp_fifo.c` — R5 stack links to **only `uz_SystemTime`** (~36 KB) |
| Z3 A53 gateway | ✅ `xcp_gateway_a53.c` (UDP ⇄ OCM, IPI-ISR + 2 tasks) — compiles against the A53 BSP, no unexpected unresolved syms |
| Z1b Vitis wiring | ⏳ documented below (needs the board to bring up) |
| Z4 arbitrary A2L | ⏳ documented below |

Verified with `armr5-none-eabi-gcc` / `aarch64-none-elf-gcc` 11.2.0.

## Files (`option_z/`)

```
shared/ocm_xcp_fifo.{c,h}   OCM FIFO, one impl for both cores (ARMR5 selects side).
                            Adapted from the hardware-proven hedrive
                            RPU_APU_exchange (sweep model + CTO reserve + bounds).
r5_engine/platform_baremetal.c  R5 platform backend (mutex = IRQ critical section,
                            clock = uz_SystemTime).
r5_engine/xcptl_ocm.c       R5 XCP transport + driving API (XcpTl* + xcp_r5_init/
                            event/poll/tx_pump). Replaces xcpethtl.c on the R5.
r5_engine/xcplib_r5_cfg.h   R5 config: no sockets, queue32, OPTION_CAL_SEGMENTS off
                            (direct addressing), 1 us clock, no A2L gen/persistence.
a53_gateway/xcp_gateway_a53.c   A53 UDP<->OCM gateway: xcp_gateway_a53_init() +
                            xcp_gateway_a53_on_ipi() + rx/tx tasks.
```

## Data path

```
CANape --UDP:5556--> rx_task --rxq--> APU_IPI_ISR --> XCP_IN  --> R5 XcpCommand
R5 XcpEvent/CRM ----> XCP_OUT --> APU_IPI_ISR --txq--> tx_task --UDP--> CANape
```
The R5 triggers the IPI once per control cycle (after `xcp_r5_poll()`); the A53
IPI ISR touches only OCM + FreeRTOS queues (sockets live in the tasks — hedrive
F1). Frame = `[dlc:u16][ctr:u16][packet]` (= the XCP-on-UDP datagram payload).

## Integration (do on the bench, one step at a time)

**R5 (Baremetal):**
1. Copy into `Baremetal/src/sw/xcp_engine/`: the engine `.c/.h`
   (`xcplite, queue32, util, xcpappl` + headers), `platform_baremetal.c`,
   `xcptl_ocm.c`, `xcplib_r5_cfg.h`, and `shared/ocm_xcp_fifo.{c,h}`.
   Do **not** copy `a2l.c/persistence.c/shm.c/xcpethtl.c/xcpethserver.c`.
2. Use an **R5 copy of `platform.h`** that forces `_BAREMETAL` (not `_FREE_RTOS`)
   at the top; wire `xcplib_r5_cfg.h` into its `xcplib_cfg.h` (as the A53 does).
   Add `-D_BAREMETAL` to the Baremetal app (it already passes `-DARMR5`).
3. Wire (gate all behind `XCP_ENGINE_R5_ENABLE`):
   - after `uz_SystemTime` init → `xcp_r5_init("UltraZohm_XCP", "1.0");`
   - in `ISR_Control` → `xcp_r5_event();`
   - in the main loop (`infinite_loop`) → `xcp_r5_poll();` then trigger the IPI
     to the A53 (reuse the existing `XIpiPsu_TriggerIpi`).

**A53 (FreeRTOS):**
1. Copy `xcp_gateway_a53.c` + `shared/ocm_xcp_fifo.{c,h}` into `FreeRTOS/sw/`.
2. Add a third logging mode `LOGGING_PATH_XCP_R5_GATEWAY` (XOR with JAVASCOPE /
   XCP_LITE in `defines.h`).
3. Under that mode: in `main` after the IP is up → `xcp_gateway_a53_init(stack,
   prio)`; in `APU_IPI_ISR` → `xcp_gateway_a53_on_ipi(&woken)` (instead of the
   curated MEAS/JavaScope handling).

**Z4 — arbitrary A2L.** Generate the A2L from the **R5** `Baremetal.elf` symbols
(any variable, by address) — extend `tools/xcp_test/gen_a2l.py` to read the R5
ELF and emit `MEASUREMENT`s for the symbols you choose. Then `xcp_poll.py` /
CANape can read *any* R5 variable, no curated struct.

## Standalone verify (no hardware)

```bash
# R5 side
ARMR5="armr5-none-eabi-gcc -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -DARMR5 -D_BAREMETAL -O2 -c -I<xcp_lite hdrs> -I option_z/shared -I<R5 BSP>"
$ARMR5 xcplite.c queue32.c util.c xcpappl.c platform_baremetal.c xcptl_ocm.c ocm_xcp_fifo.c
armr5-none-eabi-nm *.o | awk '$1=="U"{print $2}' | sort -u   # only uz_SystemTime + libc

# A53 gateway
aarch64-none-elf-gcc -O2 -c -I option_z/shared -I<A53 BSP> xcp_gateway_a53.c ocm_xcp_fifo.c
```
