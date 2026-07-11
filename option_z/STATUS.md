# Option Z — XCPlite engine on the R5 (status)

Goal: run XCPlite's **protocol engine on the R5** (the control core) with the A53
as an Ethernet gateway — the `uz_sw_xcp_hedrive_andi` architecture, but with
**MIT XCPlite** instead of the non-redistributable XCP Basic. This gives
**arbitrary-address** measurement + calibration, which the A53-image approach
(Phases 0/1/3, already working) cannot.

See `XCPLITE_DEMO_PLAN.md` → "Option Z" for the rationale and milestones.

## HARDWARE VALIDATED (2026-07-10/11)

First hardware bring-up succeeded and the endurance soak is passed:
**1 hour @ 325.7 Mbit/s** (4000 B/cycle, 10 kHz, 622 million TL frames,
149 GB) with the session alive and responsive throughout — zero R5-side
drops over 36.6 M control cycles, command/response handshake perfect
(65/65 generations, 0 CTO drops), net wire loss 0.00055 % attributed to the
lab PC's NIC receive path (see TEST_PLAN "Interpreting ctr reordering").
That is 2x the sibling hedrive rig's reference rate, which historically
died randomly within 5 min–2 h — the CP7 exchange protocol holds.

A53 gateway counters after the soak (JTAG) — the CP7/CP9 mechanisms at work:
`sendto_drop 0` / `txq_dropped 0` (nothing ECU-side ever lost),
`sendto_err 17` (transient lwIP stumbles across 146 M datagrams, every one
recovered by the CP9 bounded retry), `ocm_torn 10` + `ocm_skipped 10`
(seqlock caught 20 R5/A53 write-read collisions — each would have been
corrupt wire data pre-CP7), `ocm_cycles_missed 943` (0.0026 % of cycles:
IPI latency > 100 µs; pure DAQ gaps now — pre-CP7 any such cycle carrying
a command response killed the session, the hedrive T8 random-death cause).

R5 ISR budget measured (IMPROVEMENTS §1.1): ~10 µs engine base +
~10 µs per KB of DAQ payload per cycle; 52.9 µs at the 326 Mbit/s worst
case — fits the 100 µs cycle with 47 µs headroom. **All planned
measurements complete; the transport is validated for use.**

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

## Files (in-tree — these are what the Vitis projects link and build)

> The `option_z/{shared,r5_engine,a53_gateway}` reference copies were removed
> on 2026-07-04 — they were unbuilt duplicates that had to be hand-synced. The
> single source of truth is `vitis/software/` (only docs remain in `option_z/`).

```
vitis/software/Baremetal/src/sw/xcp_engine/ocm_xcp_fifo.{c,h}
                            OCM FIFO, one impl for both cores (ARMR5 selects
                            side); second compile-copy for the A53 lives in
                            FreeRTOS/sw/xcp_gateway/ (keep byte-identical!).
                            Adapted from the hardware-proven hedrive
                            RPU_APU_exchange (sweep model + CTO reserve + bounds).
vitis/software/Baremetal/src/sw/xcp_engine/platform_baremetal.c
                            R5 platform backend (mutex = IRQ critical section,
                            clock = uz_SystemTime).
vitis/software/Baremetal/src/sw/xcp_engine/xcptl_ocm.c
                            R5 XCP transport + driving API (XcpTl* + xcp_r5_init/
                            event/poll/tx_pump). Replaces xcpethtl.c on the R5.
vitis/software/Baremetal/src/sw/xcp_engine/xcplib_r5_cfg.h
                            R5 config: no sockets, queue32, OPTION_CAL_SEGMENTS off
                            (direct addressing), 1 us clock, MTU 284 / DTO 248
                            (OCM record cap), no A2L gen/persistence.
vitis/software/FreeRTOS/sw/xcp_gateway/xcp_gateway_a53.c
                            A53 UDP<->OCM gateway: xcp_gateway_a53_init() +
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

Since CP7 (2026-07-09) the exchange carries the full hedrive T8 protocol:
XCP_OUT is seqlock-guarded (torn reads discarded on the A53), command
responses ride an acknowledged CTO mailbox (never lost to a cycle rewrite),
commands ride a generation handshake on XCP_IN (rewritten every IPI until the
R5 acks execution), the A53 owns the wire CTR (stamped at transmission time),
CTO frames take a dedicated queue past the deep (262144-record ≈ 68 MB,
hedrive stall-bridging sizing) DAQ backlog, and the tx task batches records
into ~1400-byte datagrams (one `sendto` for many frames). See
`option_z/TEST_PLAN.md` (CP7 blockquote) for the counter set.

## Integration — DONE (2026-06-17, hardened 2026-07-04)

All of the following is integrated in-tree and builds green; see
`option_z/TEST_PLAN.md` for the bring-up sequence and the 2026-07-04 hardening:

**R5 (Baremetal):** engine + glue live in `Baremetal/src/sw/xcp_engine/`
(gated by `XCP_ENGINE_R5_ENABLE` in `Baremetal/src/defines.h`):
`xcp_r5_init("UltraZohm_XCP","1.0")` in `main.c` (init_interrupts state);
`xcp_r5_event(); xcp_r5_poll(); XIpiPsu_TriggerIpi(...)` in `ISR_Control`
(`Baremetal/src/sw/isr.c`). `platform.h` auto-selects `_BAREMETAL` on ARMR5.

**A53 (FreeRTOS):** gateway lives in `FreeRTOS/sw/xcp_gateway/` (gated by
`LOGGING_PATH_XCP_R5_GATEWAY` in `FreeRTOS/defines.h`, XOR with JAVASCOPE /
XCP_LITE): `xcp_gateway_a53_init(...)` from `main.c` after the IP is up;
`xcp_gateway_a53_on_ipi(&woken)` in `APU_IPI_ISR` (`FreeRTOS/sw/isr.c`).

**Z4 — arbitrary A2L/measurement:** `tools/xcp_test/gen_a2l.py --symbols` emits
MEASUREMENTs from R5 `Baremetal.elf` symbols; `xcp_poll.py --watch/--daq` reads/
streams any R5 variable, no curated struct.

## Standalone verify (no hardware)

```bash
# R5 side (in vitis/software/Baremetal/src/sw/xcp_engine/)
ARMR5="armr5-none-eabi-gcc -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -DARMR5 -O2 -c -I<shared> -I<R5 BSP>"
$ARMR5 xcplite.c queue32.c util.c xcpappl.c platform_baremetal.c xcptl_ocm.c ocm_xcp_fifo.c
armr5-none-eabi-nm *.o | awk '$1=="U"{print $2}' | sort -u   # only uz_SystemTime + libc

# A53 gateway (in vitis/software/FreeRTOS/sw/xcp_gateway/)
aarch64-none-elf-gcc -O2 -c -I<A53 BSP> xcp_gateway_a53.c ocm_xcp_fifo.c
```
