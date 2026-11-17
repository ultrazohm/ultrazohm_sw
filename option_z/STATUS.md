# Option Z — XCPlite engine on the R5 (status)

Goal: run XCPlite's **protocol engine on the R5** (the control core) with the A53
as an Ethernet gateway — the `uz_sw_xcp_hedrive_andi` architecture, but with
**MIT XCPlite** instead of the non-redistributable XCP Basic. This gives
**arbitrary-address** measurement + calibration, which the earlier A53-image
approach (a curated eight-signal MEAS image served by an XCPlite copy on the
A53) could not. That A53-hosted path and its plan document
(`XCPLITE_DEMO_PLAN.md`, which also holds the Option Z rationale) were removed
on 2026-11-16; both are in git history up to commit c51d06c.

User documentation: `docs/source/guide/XCP/` (usage, architecture with block
diagrams, diagnostics). This file and its neighbours are the development log.

## Bench run 2026-11-17 (40 kHz control rate, MAX_DTO 248)

The 2026-11-16 series below ran on hardware for the first time, stress tests
only (`xcp_poll.py --stress`, 20-60 s each):
- 100, 250 and 400 B/cycle (up to 128 Mbit/s): no loss anywhere. The
  consumption handshake caught every late IPI read (`xcp_r5_out_held` > 0,
  `xcp_r5_queue_lost` 0).
- 500 B/cycle (160 Mbit/s): borderline, 0 loss in one run, some
  `xcp_r5_queue_lost` in another; 8 % of the A53 reads torn.
- 1000 B/cycle (320 Mbit/s): collapse. About a third of the cycles lost in
  the R5 queue, 61 % of the A53 reads torn, A53 handled only ~3,500 of
  ~10,000 IPIs/s. Likely mechanism: at 40 kHz the ISR leaves little R5 time,
  each exchange sweep stretches, the A53 read window shrinks; keep sweeps
  still bump the seqlock, so long reads of an unchanged chain are discarded
  and the chain grows to 32 KB. Not fixed yet (candidates: cap the chain per
  sweep, start the sweep interval at the end of the previous sweep, validate
  the chain by `chain_seq` instead of the seqlock).
- ISR cost of `xcp_r5_event()` (DAQ of `timingR5.isr_execution_time_us`):
  14.2 us ISR without DAQ, about +1 us for the first ODT, +0.6-0.8 us per
  further ODT, about 1 us per KB of data. Cost is per ODT (one DAQ message
  each), not per byte. Hence MAX_DTO 1024 (8baa085), not yet measured.

## Bench run 2026-11-17, MAX_DTO 1024 (commit 8baa085 flashed)

- ISR (DAQ of `timingR5`, entries packed into ODTs like CANape): 15.3 us
  timing only, 15.9 / 16.3 / 17.3 us mean at 250 / 500 / 1000 B per cycle,
  all in one ODT, max 20.1 us; about 2 us per KB. The same 1000 B as six
  ODTs: 18.9 us mean while already losing samples.
- `xcp_poll.py --stress`: 1000 B/cycle (320 Mbit/s) clean for 60 s and for
  300 s (12.0 M cycles at 40,000 Hz, `xcp_r5_queue_lost` 0, net wire loss
  0, `xcp_gw_txq_dropped` 0, 0.55 % of the A53 reads torn and recovered via
  `xcp_r5_out_held`). 1200 B (384 Mbit/s), 1500 B and 2000 B: same collapse
  as before (about 280 Mbit/s delivered, A53 handles only ~2,400-2,900
  IPIs/s, 25-30 % of the cycles lost in the R5 queue).
- So the limit at 40 kHz moved from ~160 to between 320 and 384 Mbit/s.
  The overload collapse itself is still open (candidates in the run above).
- CANape with MAX_DTO 1024 not tried yet.

## Changes after the July hardware run (2026-11-16/17)

Syntax-checked with the Vitis toolchains; the 2026-11-16 part ran in the
bench run above. Rebuild and flash both applications, then rerun TEST_PLAN
tests 1 to 4.

- engine upgraded to upstream XCPlite V2.3.4, review fix series
- A53-hosted XCPlite server removed; JavaScope and Option Z remain, selected
  by one define in `vitis/software/shared/uz_logging_path.h` (mismatch warning
  on the A53 console)
- OCM layout changed: consumption handshake on the XCP_OUT chain (DAQ
  survives a late IPI read), XCP_OUT now 32 KB at `0xFFFF4000`, XCP_IN header
  128 bytes, gateway counters mirrored into the XCP_IN header
- gateway closes the session when the master is unreachable
- write gate for calibration (data sections only), `XCP_R5_READ_ONLY`
- A2L: structures for `Global_Data`, ODT entry size 240, T1 5000 ms
- 2026-11-17, bench-tested (stress tests only, see above): MAX_DTO 1024
  (was 248), OCM chain records up to 1400 B (`OCM_XCP_RECORD_MAX`, 16-bit
  lengths), gateway DAQ queue 65536 x 1.4 KB; `xcp_poll.py --stress` packs
  ODTs up to MAX_DTO

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
IPI latency > 100 µs; pure DAQ gaps at that time, closed by the consumption
handshake of 2026-11-16 — pre-CP7 any such cycle carrying
a command response killed the session, the hedrive T8 random-death cause).

R5 ISR budget measured (IMPROVEMENTS §1.1): with the sweep in the ISR,
~10 µs engine base + ~10 µs per KB of DAQ payload per cycle — too much for
the 100 kHz ISR target, so CP11 moved the exchange sweep to the main loop
(`xcp_r5_background()`, paced at 100 µs; only the XcpEvent sampling copy
stays in the ISR). Re-measure `isr_execution_time_us` after rebuild:
expected near the non-XCP baseline at idle, ~+5 µs/KB while streaming.
**Transport validated for use (1 h soak).** Open since then: the ISR-cost
re-measurement after the CP11 split, and a hardware run of the 2026-11-16
changes (see the top of this file).

## DAQ rasters (CP12, 2026-08-03)

The slave offers the hedrive set of measurement rasters, all served from
`ISR_Control` (`xcp_r5_event()`): event channel 0 `DAQ_R5` at the control-ISR
rate (now *declared* at its real period instead of a hardcoded 1 ms) plus the
derived slices 1 `daq_1ms`, 2 `daq_10ms`, 3 `daq_100ms`, 4 `daq_1s`. Dividers
come from `UZ_PWM_FREQUENCY` and the trigger factor, so they follow a PWM
frequency change (40 kHz on the test bench → 40 control cycles per ms; the
repository default of 10 kHz → 10); the counters are
staggered so no two slices fire in the same cycle. Channel numbers are the
creation order and are mirrored in `CANape/UZ_XCP/uz.A2L`; `xcp_r5_init()`
refuses to run (`xcp_r5_init_result = -4`) if the numbering ever shifts.
Test without CANape: `xcp_poll.py --daq --daq-event 1..4`.

## Code-complete & compile-verified (2026-06-17)

The full Option Z stack is written and compiles/links for both toolchains.
What remains is Vitis assembly + on-hardware bring-up (see "Integration").

| Milestone | State |
|-----------|-------|
| Z1 engine on armr5 | ✅ engine (`xcplite/queue32/util/xcpappl`) compiles unchanged for armr5 + `_BAREMETAL` platform branch — upstream **V2.3.4** since 2026-11-16 (was V2.1.0; see IMPROVEMENTS §4b, not yet hardware-tested) |
| Z2 R5 transport | ✅ `xcptl_ocm.c` (engine TL + `xcp_r5_init/event/background/poll`) + `ocm_xcp_fifo.c` — R5 stack links to **only `uz_SystemTime`** (~36 KB) |
| Z3 A53 gateway | ✅ `xcp_gateway_a53.c` (UDP ⇄ OCM, IPI-ISR + 2 tasks) — compiles against the A53 BSP, no unexpected unresolved syms |
| Z1b Vitis wiring | ✅ integrated in-tree and brought up on hardware (2026-07-10), see "Integration" below |
| Z4 arbitrary A2L | ✅ `gen_a2l.py`, `dwarf_structs.py`, `xcp_poll.py --watch/--daq`; CANape project in `CANape/UZ_XCP` |

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
                            event/background/poll/tx_pump), memory access check
                            and write gate. Replaces xcpethtl.c on the R5.
vitis/software/Baremetal/src/sw/xcp_engine/xcplib_r5_cfg.h
                            R5 config: no sockets, queue32, OPTION_CAL_SEGMENTS off
                            (direct addressing), 1 us clock, segment 252 / DTO 248
                            (OCM record cap), ODT entry 240, no DAQ prescaler,
                            no A2L gen/persistence.
vitis/software/FreeRTOS/sw/xcp_gateway/xcp_gateway_a53.c
                            A53 UDP<->OCM gateway: xcp_gateway_a53_init() +
                            xcp_gateway_a53_on_ipi() + rx/tx tasks.
```

## Data path

```
CANape --UDP:5556--> rx_task --rxq--> APU_IPI_ISR --> XCP_IN  --> R5 XcpCommand
R5 XcpEvent/CRM ----> XCP_OUT --> APU_IPI_ISR --txq--> tx_task --UDP--> CANape
```
The R5 triggers the IPI once per exchange sweep: since CP11 from the main loop
(`xcp_r5_background()`, every 100 µs), before that once per control cycle from
the ISR. The A53 IPI ISR touches only OCM + FreeRTOS queues (sockets live in
the tasks — hedrive F1). Frame = `[dlc:u16][ctr:u16][packet]` (= the XCP-on-UDP datagram payload).

Since CP7 (2026-07-09) the exchange carries the full hedrive T8 protocol:
XCP_OUT is seqlock-guarded (torn reads discarded on the A53), command
responses ride an acknowledged CTO mailbox (never lost to a cycle rewrite),
commands ride a generation handshake on XCP_IN (rewritten every IPI until the
R5 acks execution), the A53 owns the wire CTR (stamped at transmission time),
CTO frames take a dedicated queue past the deep (262144-record ≈ 68 MB,
hedrive stall-bridging sizing) DAQ backlog, and the tx task batches records
into ~1400-byte datagrams (one `sendto` for many frames). See
`option_z/TEST_PLAN.md` (CP7 blockquote) for the counter set. Since
2026-11-16 the DAQ chain is acknowledged as well (consumption handshake,
IMPROVEMENTS §2.1), so a late IPI read no longer loses measurement data.

## Integration — DONE (2026-06-17, hardened 2026-07-04)

All of the following is integrated in-tree and builds green; see
`option_z/TEST_PLAN.md` for the bring-up sequence and the 2026-07-04 hardening:

**R5 (Baremetal):** engine + glue live in `Baremetal/src/sw/xcp_engine/`
(gated by `XCP_ENGINE_R5_ENABLE` in `Baremetal/src/defines.h`, derived from
`UZ_LOGGING_PATH` in `shared/uz_logging_path.h`):
`xcp_r5_init("UltraZohm_XCP","1.0")` in `main.c` (init_interrupts state);
`xcp_r5_event()` in `ISR_Control` (`Baremetal/src/sw/isr.c`);
`xcp_r5_background()` + `XIpiPsu_TriggerIpi(...)` in the main loop of `main.c`
(infinite_loop state, since CP11). `platform.h` auto-selects `_BAREMETAL` on ARMR5.

**A53 (FreeRTOS):** gateway lives in `FreeRTOS/sw/xcp_gateway/` (gated by
`LOGGING_PATH_XCP_R5_GATEWAY` in `FreeRTOS/defines.h`, derived from the same
`UZ_LOGGING_PATH`, XOR with JAVASCOPE): `xcp_gateway_a53_init(...)` from
`main.c` after the IP is up;
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
