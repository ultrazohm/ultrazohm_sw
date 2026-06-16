# Option Z — XCPlite engine on the R5 (status)

Goal: run XCPlite's **protocol engine on the R5** (the control core) with the A53
as an Ethernet gateway — i.e. the `uz_sw_xcp_hedrive_andi` architecture, but with
**MIT XCPlite** instead of the non-redistributable XCP Basic. This gives
**arbitrary-address** measurement + calibration, which the A53-image approach
(Phases 0/1/3, already working) cannot.

See `XCPLITE_DEMO_PLAN.md` → "Option Z" for the full rationale and milestones.

## Done & verified (2026-06-16)

**Z1 — engine compiles + links for the bare-metal R5.** ✅ Proven with
`armr5-none-eabi-gcc 11.2.0` (`-mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16
-D_BAREMETAL`):

- The XCPlite engine is portable: `xcplite.c`, `queue32.c`, `util.c`,
  `xcpappl.c` all compile for armr5 unchanged. `<pthread.h>` is `TEST_*`-only
  (not compiled); the C11 atomics compile and give ISR-vs-main safety for free.
- Added an **additive `_BAREMETAL` branch** to the vendored
  `vitis/software/FreeRTOS/sw/xcp_lite/platform.h` (atomics include, MUTEX =
  IRQ critical section, no-thread stubs). It does **not** affect the A53 build
  (which selects `_FREE_RTOS`) — A53 re-verified green after the change.

**Z2 — OCM transport layer.** ✅ ~90%: written and compiling. Only the OCM FIFO
implementation remains (a port of hedrive's proven `RPU_APU_exchange`).

The full R5 XCP stack links with **only 4 external symbols** unresolved:

```
uz_SystemTime_GetUptimeInUs   <- already in the Baremetal lib
ocm_xcp_init                  <- Z2 FIFO (port RPU_APU_exchange)
ocm_xcp_read_cmd              <- Z2 FIFO
ocm_xcp_write_rsp             <- Z2 FIFO
```

Everything else resolves to libc/libgcc/libm. **Footprint ≈ 35 KB text + 5 KB
bss** — trivial for the R5's DDR.

## Files here

| File | Role |
|------|------|
| `platform_baremetal.c` | Bare-metal platform backend: `mutex*` (IRQ critical section), `clock*` (← `uz_SystemTime`). Replaces `platform_freertos.c`/`platform.c` on the R5. |
| `xcptl_ocm.c` | XCP transport over OCM: `XcpTlGetCtr/SendCrm/WaitForTransmitQueueEmpty` + `xcp_r5_init/rx_pump/tx_pump`. Replaces `xcpethtl.c` (sockets) on the R5. |
| `xcplib_r5_cfg.h` | R5 config override: no sockets, `OPTION_QUEUE_32`, `OPTION_CAL_SEGMENTS` **off** (direct addressing), 1 µs clock, no A2L gen / persistence. |

These are staged **outside** the Vitis source trees so the default Baremetal /
FreeRTOS builds stay green until integration (Z1b).

## Remaining

- **Z1b — Vitis integration.** Compile the engine + these files in the Baremetal
  app. Either copy the engine `.c` into `Baremetal/src/sw/xcp_engine/` (Vitis
  auto-compiles the tree) or add them as linked resources. The Baremetal build
  must pass `-D_BAREMETAL` (or force it like the A53 forces `_FREE_RTOS`, but in
  an R5-only header so it doesn't collide). Exclude the same PC-only files as on
  the A53 (a2l/persistence/shm/xcpeth*).
- **Z2 finish — OCM FIFO.** Port `shared/RPU_APU_exchange_impl.c` from
  `uz_sw_xcp_hedrive_andi` and implement `ocm_xcp_init/read_cmd/write_rsp` on top
  of it (one TL frame per call). This is the proven FIFO (its bug history is in
  hedrive's `XCP_BOTTLENECK_ANALYSIS.md` — reuse the fixes).
- **Z3 — A53 gateway.** Port hedrive's `OCM_eth_adapter` (OCM ↔ **UDP**) into the
  FreeRTOS app as an XOR alternative to the current A53 XCPlite server.
- **Z4 — arbitrary measurement.** `xcp_r5_init` already sets base 0 (identity →
  any R5 address). Call `XcpEvent()` from `ISR_Control`; generate the A2L from
  the R5 ELF symbols (any variable, no curated struct).
- **Z5 — calibration** (direct writes; safety review).

## Build/verify recipe (standalone, no hardware)

```bash
GCC="armr5-none-eabi-gcc -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -D_BAREMETAL -Wall -O2 -c -I<xcp_lite headers>"
$GCC xcplite.c queue32.c util.c xcpappl.c platform_baremetal.c xcptl_ocm.c
# then check only uz_SystemTime + ocm_xcp_* remain unresolved:
armr5-none-eabi-nm *.o | awk '$1=="U"{print $2}' | sort -u
```
