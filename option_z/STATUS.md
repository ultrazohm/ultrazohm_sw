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
  ~10,000 IPIs/s. First guess was the A53 (long reads of an unchanged chain
  discarded by keep sweeps). WRONG, see "chain validation" below: the R5
  main loop is the limit.
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
- CANape with MAX_DTO 1024 not tried yet.

## Bench run 2026-11-17, chain validation (commit c271e7a flashed)

- `xcp_gw_ocm_torn` 0 and `xcp_gw_ocm_skipped_writing` 0 in every run
  (before: ~33,000 discarded reads per 30 s at overload). 1000 B/cycle still
  clean (60 s, 0 loss).
- The overload limit did NOT move: 1200 / 1500 / 2000 B/cycle still deliver
  280-290 Mbit/s with large `xcp_r5_queue_lost`, A53 ~2,400 IPIs/s.
- Root cause, measured by polling `xcp_r5_sweep_count` during the run (after
  resetting `xcp_r5_sweep_gap_max_us` with SET_MTA + DOWNLOAD, which also
  proves the write gate on hardware): the R5 manages 9,986 exchanges/s at
  8 B/cycle, 8,785/s at 1000 B (longest gap 250 us), but only 2,224-2,311/s
  at 1200-1500 B (longest gap 826 us). The main-loop exchange moves about
  40 MB/s (~320 Mbit/s of chain bytes) with the ~30 % of the R5 that the
  40 kHz ISR leaves, whatever the chain size. In overload every rewrite
  sweep is followed by one hold sweep (`xcp_r5_tx_held` = `xcp_r5_out_held`),
  because the next sweep starts at once after a long one, before the A53 has
  read. The A53 is not the bottleneck; the discarded reads were a symptom.
- Commands during overload: ~40 SHORT_UPLOADs per 10 s run, 0 timeouts.
- Levers to raise the ceiling at 40 kHz (none implemented): make the R5 copy
  into XCP_OUT cheaper (non-cacheable MPU mapping of XCP_OUT, or DMA), avoid
  the copy (DAQ queue in OCM, read directly by the A53), or free R5 time in
  the ISR (DAQ queue in TCM, lower control rate). Starting the 100 us
  interval at the end of a sweep would only remove the wasted hold sweeps.

## Bench run 2026-11-17 evening, profile build (93f74de flashed, asserts on)

Functional checks (scratchpad script, all against the live board):
- 24 of 24 passed: writes accepted for .bss/.data, refused with
  ERR_WRITE_PROTECTED (and counted) for .text, .rodata, heap, stack, ATCM,
  BTCM, OCM; reads refused with ERR_ACCESS_DENIED outside R5 memory and
  across the end of R5 DDR; ODT entry 241 B and prescaler 2 refused; DAQ
  tables overflow after 765 entries in one 50-ODT list; oversize (300 B)
  and malformed datagrams leave the session intact; 30 x connect / DAQ
  320 Mbit/s / stop / disconnect without any loss counter moving.
- Address 0 itself is not readable (engine null-pointer check), contrary
  to "TCM readable" in the docs. Harmless, docs to be adjusted.
- Rasters: 40000 / 1000 / 100 / 10 / 1 Hz on events 0..4.

R5 time profile (xcp_poll.py --stress, 20 s each, 40 kHz):

| B/cycle | exchanges/s | copy CPU us/KB | flush CPU us/KB | xcp_r5_event avg (max) | ISR / exchanges / rest of main loop |
|---|---|---|---|---|---|
| 8   | 9201 | (tiny) | (tiny) | 1.23 (1.91) us | 61.9 / 3.0 / 35.1 % |
| 250 | 9337 | 2.52 | 1.82 | 1.66 (2.84) us | 63.7 / 5.8 / 30.5 % |
| 500 | 9286 | 3.03 | 1.54 | 2.10 (3.31) us | 65.7 / 10.5 / 23.8 % |
| 750 | 9279 | 3.11 | 1.61 | 2.59 (4.05) us | 67.7 / 15.5 / 16.8 % |

- The copy and flush cost only ~4.6 us of CPU per KB together (the wall
  time is ~3x that because the ISR interrupts them). At 750 B the R5 still
  idles 17 % of the time. So the ~25 us/KB "ceiling" derived earlier from
  exchange rates was wrong: the overload collapse is probably not CPU but
  the exchange scheduling (a long rewrite exchange is followed at once by a
  keep exchange, then the R5 waits for the next 100 us slot). Needs the
  profile at 1000-1500 B to confirm; the run stopped before that.
- The XCP part of the ISR: ~1.2 us + ~1.8 us per KB of measured data (one
  ODT), the rest of ISR_Control ~14.2 us.

A53 HANG during the 900 B run (~16:42, 5 min after boot):
- DAQ data arrived for the full 20 s, then commands got no answer; no ping,
  no ARP, no packets at all from the board; Ethernet link still up. R5
  alive (XCP_OUT cycle_seq rising, DAQ still running, chains given up after
  the 50-exchange hold since nothing acknowledges).
- A53 #0 "Running" in xsct; halted for inspection (then resumed): stuck in
  xTaskResumeAll() (tasks.c 2244-2260, the xPendingReadyList loop) called
  from xQueueSemaphoreTake() of xcp_gw_tx_task (xSemaphoreTake(gTxSignal)),
  ullCriticalNesting 1, GICC_PMR 0x90 (FreeRTOS critical mask) forever,
  tick frozen at 31462, IPI (ID 67) and tick (ID 68) pending, xYieldPending
  1, uxTopReadyPriority 9 although ready list 3 is empty, gTxSignal holds a
  token that is never taken.
- Ruled out: GIC priorities (IPI/GEM 0xA0, tick 0xF0, mask 0x90), FPU
  context (port saves it in the IRQ entry), EL3 stack (60 KB), tx/idle/
  timer task stack overflow (fill pattern intact), neighbouring buffers
  (only kernel/BSP variables around the kernel lists).
- ROOT CAUSE (confirmed the same evening): the FreeRTOS kernel was built
  WITHOUT the portMEMORY_BARRIER patch
  (tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl). In the workspace
  regeneration of 2026-11-17 13:57, `bsp regenerate` failed on a file held
  by another process (libsrc/standalone_v8_0/src/arm/cortexa9/sleep.c), the
  patch step then found no FreeRTOSConfig.h and only printed a warning, and
  Vitis generated the BSP sources later without the patch
  (vitis/logs/generate_workspace_17-11-2026_13-57-45-08.log). The June
  workspace (July bench, 1 h soak) had the patch.
- Without the barrier, GCC -O2 loads pxTCB and its list containers once,
  before the xPendingReadyList loop of xTaskResumeAll(). With two or more
  tasks in that list, the second pass works on the first TCB again and
  decrements the "list count" through a NULL container (x3 = 0, i.e. the
  u64 at address 0, the first vector-table entry), so
  xPendingReadyList.uxNumberOfItems never reaches 0: endless loop inside the
  critical section. Two pending tasks need two ISRs readying tasks while the
  scheduler is suspended, here the GEM (xemacif_input_thread, prio 3) and
  the IPI (xcp_gw_tx, prio 2), hence load dependent.
- Proof on the hung board (xsct, A53 halted briefly and resumed): pc in the
  loop, x3 = 0 and x0 = TCB of xemacif_input_thread in every sample, the
  pending list holds xcp_gw_tx with count 1; the u64 at 0x0 went from
  0x14000630 (`b _boot`) to 0xFFFFFFB2_CDBF6B90 and kept falling by
  ~26 M/s: 3.3e11 passes = 3.5 h = the time since the hang. The workspace
  tasks.o is identical to a rebuild without the barrier; with the barrier
  (or -fno-strict-aliasing) the loop re-reads the list head on every pass.
- The workspace headers were re-patched the same evening with the project's
  own uz_vitis_patch_freertos_bsp; platform and FreeRTOS app to be rebuilt.
- The one-socket-from-two-tasks use of lwIP (LWIP_NETCONN_FULLDUPLEX = 0),
  suspected first, is not the cause of this hang (still a design point).
- The board stays hung (state preserved); a single-core A53 restart is
  excluded (known mailbox deadlock), so both apps must be programmed again.

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
- 2026-11-17, bench-tested (stress tests): the DAQ chain is validated by
  its own `chain_seq` (0 while rewritten, published after the chain bytes)
  instead of the seqlock, so a long A53 read of a kept chain is no longer
  thrown away (ocm_xcp_fifo.c mechanism 5). Discarded reads went to 0; the
  overload limit did not move (R5-bound, see above). Counter meanings:
  `xcp_gw_ocm_skipped_writing` = header copy unusable, `xcp_gw_ocm_torn` =
  chain really rewritten mid-read
- 2026-11-17, NOT yet on hardware: R5 time profile `xcp_r5_prof` (PMU cycle
  counter: exchange phases refresh/commands/copy/flush with the ISR time
  inside them, the XCP part of the ISR, the R5 time split); printed by
  `xcp_poll.py --stress`. Switch `XCP_R5_PROFILE` (xcp_r5.h, default 1)
- 2026-11-17, NOT yet on hardware: `XCP_R5_ENGINE_ASSERTS` (xcplib_r5_cfg.h,
  default 1 = upstream asserts active in the Debug build) to measure and
  optionally drop the engine asserts in the ISR path

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
