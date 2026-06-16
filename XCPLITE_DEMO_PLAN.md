# XCPlite-on-A53 Demo — Implementation Plan (agent handoff)

## 0. Goal
Stand up a working demo of **XCPlite** (Vector's MIT-licensed XCP-on-Ethernet slave)
running on the **A53 / FreeRTOS / lwIP** of the UltraZohm, measurable from **CANape over
UDP**, coexisting with the existing **JavaScope (TCP)** path as a compile-time **XOR**
feature. Build it up in phases; the first milestone is A53-only and needs no R5 work.

Two repos:
- **XCPlite source (read-only reference, already cloned):** `C:\Users\ga92wum\git\uz\xcp_lite`
- **Target (implement here):** `C:\Users\ga92wum\git\uz\uz_sw_xcp_lite` (branch `feature/xcp_lite`, a develop clone)

This plan is distilled from a long prior debugging effort on the sibling branch
`uz_sw_xcp_hedrive_andi`; the constraints and gotchas below are battle-tested, not
speculative. Treat them as load-bearing.

---

## STATUS — 2026-06-16 (Phase 0 compiles & links)

Both apps build clean against Vitis 2022.2:
- **Baremetal (R5):** builds + links (`Baremetal.elf`), incl. `xcp_meas_r5.c`.
- **FreeRTOS (A53):** builds + links (`FreeRTOS.elf`); all 11 vendored XCPlite
  TUs + UZ glue compile warning-free, link is clean (no undefined refs).

XCPlite RAM footprint is small: `gXcpData` ≈ 3.2 KB + a few tens of KB code; the
~196 MB `bss` is the pre-existing FreeRTOS DDR heap (`ucHeap`), **not** XCPlite.

Compile/link fixes applied this session (were blocking the FreeRTOS build):
1. **Config not reaching the build.** Vitis passed *no* `-D` flags, so the UZ
   override never loaded (`OPTION_ENABLE_TCP` stayed defined → `#error` in
   `platform_freertos.c`). Made the config self-contained: `_FREE_RTOS` is now
   forced at the top of `platform.h` (before its platform `#error`), and
   `xcplib_cfg.h` unconditionally includes `xcplib_uz_cfg.h`. No `-D` needed.
2. **PC-only sources still compiling.** Renamed `a2l.c`, `a2l_writer.c`,
   `persistence.c`, `shm.c` → `*.c.EXCLUDED` (matches the existing `platform.c`
   convention) so Vitis' scan skips them. Verified nothing references their
   symbols.
3. **`isr.c` (FreeRTOS) bad include path** — `"sw/xcp_lite/…"` resolved to
   `sw/sw/xcp_lite/…` from `sw/isr.c`; fixed to `"xcp_lite/…"`.
4. **Duplicate definition** of `xcp_meas_event_handle` (in both
   `xcp_server_uz.c` and `xcp_meas_image_a53.c`) → kept the one in
   `xcp_meas_image_a53.c`.
5. **AArch64 asm** `dsb` needs an operand → `dsb sy` in `xcp_cal_image_a53.c`.
6. **`-O3 -Warray-bounds`** on the absolute-address CAL image memset → route the
   base through a `volatile uintptr_t` so writes are not elided.

Test tooling added so the demo can be exercised **without CANape**:
- `tools/xcp_test/xcp_poll.py` — XCP-over-UDP client: CONNECT + `SHORT_UPLOAD`
  polls the demo counter/sine straight from target memory (no A2L). Auto-reads
  addresses from the ELF.
- `tools/xcp_test/gen_a2l.py` — emits an address-matched A2L for the CANape path.
- `tools/xcp_test/TESTING.md` — step-by-step (find board IP → run client).
- The app now prints `APU: XCPlite slave (UDP) at <ip>:5556` on the serial
  console (`print_xcp_app_header`), and `xcp_server_uz_start()` brings up the
  Phase 1 demo + UDP server even if the Phase 3 MEAS path fails (best-effort).

> Note: `XCP_MEAS_IMAGE_ENABLE` (Baremetal) and `LOGGING_PATH_XCP_LITE`
> (FreeRTOS) are both currently **1**, i.e. the Phase 3 R5→A53 MEAS path is
> wired in already (not strictly needed for the Phase 1 A53-only spike). Next
> up: flash both ELFs and run the **Phase 1** test via `xcp_poll.py` (then
> CANape if desired). **But first read the rethink below** — it challenges
> whether the image-based architecture is the right target at all.

---

## RETHINK — 2026-06-16: challenge the load-bearing assumptions

The prototype compiles and is testable, but several "battle-tested" constraints
in this plan deserve a hard second look *before* sinking effort into Phases 3–4.

1. **queue32 vs queue64 — the throughput sacrifice may rest on a misapplied
   argument.** §2 forces `OPTION_QUEUE_32` (mutex queue) citing "C11 `stdatomic`
   is only valid in one cache-coherent domain, and R5/A53 aren't coherent." But
   the DAQ queue lives **entirely on the single A53 FreeRTOS core** — both the
   producer (`XcpEvent`) and the consumer (tx task) run on the A53. The
   cross-core coherency problem applies to the **MEAS image** (R5↔A53), *not* to
   the queue. aarch64 gcc supplies the needed 64-bit atomics (we already link
   `__aarch64_cas4_*`). → **Action:** in Phase 1, A/B `OPTION_QUEUE_64_VAR_SIZE`
   vs `OPTION_QUEUE_32` for DAQ throughput; the lockless queue is likely a free
   win. Keep queue32 only if a measured problem shows up.

2. **Arbitrary-address vs curated-image is THE product gate — and "A53 can't
   read R5 memory" is overstated.** It is a *coherency* constraint, not a
   physical one: on ZynqMP the A53 can address R5 DDR/OCM/TCM. The real issue is
   the R5's *cached* writes. If the R5 control variables live in a known DDR
   region with periodic cache maintenance (or a write-through / non-cacheable
   mapping), the A53 could DAQ **arbitrary** R5 addresses — restoring XCP's core
   value: measure/calibrate *anything* without editing a struct, rebuilding, and
   regenerating the A2L. The current image model effectively reduces XCP to
   "JavaScope with standard tooling": only the curated `signal[]` is visible.
   → **Action (decision gate, below):** spike a direct coherent A53 read of one
   known R5 DDR variable and measure staleness/jitter. Decide image vs
   direct-address *before* Phase 3/4. If arbitrary addressing is required and
   direct reads are too incoherent, **escalate — the A53-slave may be the wrong
   tool** (an XCP slave co-located with the control code on the R5, tunnelled
   over the A53's Ethernet, would be the alternative to weigh).

3. **Clock source mismatch + DAQ timestamp semantics.** §6 says wire the 1 µs
   clock to `uz_SystemTime`; the implementation uses the A53 `XTime_GetTime`.
   Harmless for Phase 1, but in Phase 3 the meaningful timestamp is *when the R5
   sampled* (the image's `timestamp_us`), not when the A53 happened to run
   `XcpEvent` — IPI + task-wake jitter otherwise smears DAQ timing. Align the XCP
   clock to the same time base the R5 stamps (shared AXI timer / `uz_SystemTime`)
   and consider deriving event timestamps from the image.

4. **Phase 4 (calibration write-back into the live motor loop) is a large safety
   surface — reconsider scope.** Pushing CANape parameter writes into a running
   motor controller via a page-flip needs range checks, atomic adoption, torn/
   invalid-page rejection, and a rollback/fault policy. Recommend making the
   product target **measurement-only** first and treating calibration as a
   separate, reviewed work item (or out of demo scope). The Phase 4 structures
   are already wired but inert (`XCP_CAL_IMAGE` disabled) — keep them disabled.

5. **Be honest about the value.** Image-based XCP buys: standard tool (CANape),
   standard format (A2L), and decoupling from the bespoke JavaScope
   tool/protocol — over a *curated* signal set. In image mode it does **not**
   give arbitrary-variable measurement. If stakeholders expect "measure any
   variable like on an ECU," either set that expectation or pursue finding #2.

6. **Scope already jumped to Phase 3/4.** `xcp_meas_r5_update()` now runs inside
   the R5 control ISR every cycle (OCM write + cache flush). Validate **Phase 1
   in isolation** (A53-local dummy DAQ via `xcp_poll.py`) before trusting the R5
   ISR changes, and **measure the added ISR cost** of the image write+flush.

### New decision gate (insert between Phase 1 and Phase 3)

**GATE — image vs direct-address.** Acceptance to proceed to Phase 3 as written:
(a) Phase 1 passes on hardware; (b) a spike confirms whether the A53 can read R5
control memory coherently enough for DAQ; (c) stakeholders confirm a *curated*
signal set is acceptable. If (b)/(c) fail, redesign before writing more Phase 3/4
code.

> **PREREQUISITE — do this before anything else:** merge branch
> **`feature/freertos_memory_barrier_patch`** (in `C:\Users\ga92wum\git\uz\uz_sw_memory_barrier`)
> into `develop`, then bring `develop` into this `feature/xcp_lite` branch. That branch
> already solves the two mandatory kernel issues below (`portMEMORY_BARRIER` +
> `use_task_fpu_support=2`). Once merged, this work **inherits** the fix — do not
> re-implement it. See Phase 0.

---

## 1. Why this architecture (read before designing)
- **License:** the current UZ XCP uses Vector's *XCP Basic* driver, whose EULA is
  use-only / **non-transferable** — it must **not** live in an open-source repo. XCPlite
  is **MIT** and redistributable. (Do **not** copy any XCP Basic source into this repo.)
- **Slave runs on the A53, not the R5.** XCPlite is built for an OS + sockets + a
  free-running clock; its DAQ queue uses **C11 `stdatomic`** that is only valid inside one
  cache-coherent domain. The R5 and A53 are **not** cache-coherent, so XCPlite's queue
  **cannot** be shared across the two cores. Therefore the slave lives entirely on the A53.
- **"Shared image" measurement model.** Because the A53 cannot read R5 memory directly,
  the only things measurable are values the R5 **copies into a shared-memory image** (in
  OCM) each control cycle; the A53 slave samples that image. A2L addresses are offsets into
  the image (XCPlite uses absolute addressing on embedded). You measure a *curated set*,
  not arbitrary R5 addresses. (Today's `data_R2A_t` / `javascope_data_t` are tiny examples
  of exactly this pattern.)

---

## 2. Hard constraints / prerequisites (verified facts)
1. **MANDATORY kernel fix — without it the A53 freezes under load.** The Vitis 2022.2
   Cortex-A53 FreeRTOS port (kernel 10.4.6) ships `portMEMORY_BARRIER` **undefined**, which
   lets GCC -O2 corrupt the scheduler's task lists → total APU freeze after minutes of
   traffic. The fix is two parts:
   - `#define portMEMORY_BARRIER() __asm volatile ( "" ::: "memory" )` in the generated
     `FreeRTOSConfig.h` (both the `bsp/.../include/` copy and the `libsrc/.../src/` copy),
     re-applied after every `bsp regenerate` via a tcl helper.
   - `bsp config use_task_fpu_support 2` (NEON context for all tasks).
   **This is already implemented** on branch `feature/freertos_memory_barrier_patch`
   (`tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl` + the `use_task_fpu_support 2` line
   in `vitis_configure_UltraZohm_bsp_settings.tcl`, called from both
   `vitis_update_platform.tcl` and `vitis_generate_UltraZohm_workspace.tcl`). **Merge that
   branch first (see Prerequisite above); inherit it — do NOT re-implement.** Fixed upstream
   in embeddedsw ≥ 2023.1; harmless duplicate there.
2. **lwIP already supports UDP+TCP simultaneously** (`LWIP_UDP=1`, `LWIP_TCP=1`,
   `MEMP_NUM_UDP_PCB=4`, `LWIP_DHCP=1`). No BSP/lwipopts change needed for transport.
3. **XCPlite on FreeRTOS is UDP-only** — `platform.c` hard-asserts
   `assert(!(flags & SOCKET_MODE_TCP)); // TCP not supported on FreeRTOS/lwIP`. So XCP runs
   on UDP; JavaScope stays on TCP. (This is fine; the two are independent endpoints.)
4. **XCPlite's FreeRTOS socket backend uses lwIP directly** (`#include "lwip/sockets.h"`,
   `lwip_socket/bind/recvfrom/sendto`; `socketStartup` is a no-op — the app already runs
   `tcpip_init`). Matches UZ exactly.
5. **No on-target A2L generation on embedded** — generate the A2L offline (host build /
   XCPlite tooling) and load it in CANape manually.
6. **Clock:** XCPlite embedded uses a **1 µs arbitrary-epoch** clock → wire it to
   `uz_SystemTime` (`uz_SystemTime_GetUptimeInUs`).
7. **Task priorities:** the XCPlite rx/tx tasks must sit **at/below** the lwIP threads
   (`TCPIP_THREAD_PRIO == DEFAULT_THREAD_PRIO == 2`). Running network producers above lwIP
   starves RX/ACK processing and stalls the stack — a previously-hit failure.
8. **Do not modify the JavaScope path.** XCP is added strictly as an XOR alternative.
9. **Toolchain:** needs C11 + `stdatomic` (A53 aarch64 gcc in Vitis has it — confirm in
   Phase 1) and C++17 *only if* you compile the C++ API (prefer the **C API** to avoid it).

---

## 3. Reference material in the XCPlite clone (read these first)
- `examples/freertos_demo/` — canonical FreeRTOS usage (API call order, `FreeRTOSConfig.h`).
- `examples/esp32_freertos_demo/` — **closest analog**: embedded + lwIP + UDP; includes
  `stm32h7_lwip_xcp_debug_checklist.md` (an lwIP+FreeRTOS XCP bring-up checklist — follow it).
- `src/xcplib_rtos_cfg.h` — the embedded config override (UDP-only, 1µs clock, no A2L gen,
  absolute addressing, reduced queue/segment counts). Your config starts from this.
- `src/platform.c` (FreeRTOS/lwIP sections), `src/xcpethserver.c` — server init + rx/tx tasks.
- `inc/xcplib.h` — public C API: `XcpInit`, `XcpEthServerInit(addr,port,use_tcp,queue_size)`,
  `XcpCreateEvent`, `XcpEvent`, `DaqCreateEvent*` macros, `ApplXcpGetAddr/BaseAddr`.
- `inc/a2l.h` + `tools/` (`bintool`, A2L tooling), `CANape.aml`, `XCP_104.aml` — A2L/CANape.

---

## 4. Build integration (Vitis, not CMake)
XCPlite ships CMake; UZ builds via the Vitis FreeRTOS app (compiles all `.c` under the app
`src` dirs). So **vendor the needed sources** into the target app, e.g.
`vitis/software/FreeRTOS/sw/xcp_lite/`:
- **Include:** `xcplite.c`, `xcp.h/xcplite.h`, `queue*.c` (pick the variant the rtos cfg
  selects — 32-bit DAQ queue), `xcptl`/`xcpethtl.c`, `xcpethserver.c`, `platform.c`,
  `util.c`, `cal.c`, plus the `inc/` headers and a project config override
  `xcplib_uz_cfg.h` (start from `xcplib_rtos_cfg.h`).
- **Exclude (PC-only):** `shm.c`/`xcpshmserver` (multi-process SHM), `persistence.c`,
  on-target `a2l.c` generation, `ptptool`, keyboard, anything guarded `_LINUX/_WIN`.
- Define the platform: `-D_FREE_RTOS -DOPTION_FREERTOS_LWIP` and point the cfg override at
  `xcplib_uz_cfg.h` (XCPlite reads `XCPLIB_CFG_OVERRIDE`).
- Keep the vendored tree clearly marked as upstream MIT (retain `LICENSE`, note the source
  commit hash of the `xcp_lite` clone in a `VENDOR.md`).

---

## 5. Phases & acceptance criteria

### Phase 0 — BSP kernel fix + skeleton (no XCP behaviour yet)
- Port the `portMEMORY_BARRIER` + `use_task_fpu_support 2` fix (Section 2.1) into this
  repo's `tcl_scripts` (mirror `uz_sw_memory_barrier`). 
- Vendor XCPlite sources (Section 4); get the FreeRTOS app to **compile and link** with the
  XCPlite objects (no calls yet).
- **Accept:** clean build; `portMEMORY_BARRIER` present in generated `FreeRTOSConfig.h`;
  record XCPlite flash/RAM footprint delta.

### Phase 1 — A53-only XCP bring-up (the spike; no R5)
- Initialize XCPlite, start the UDP server (`XcpEthServerInit(..., use_tcp=false, ...)`) on
  a dedicated UDP port; hook the 1 µs clock to `uz_SystemTime`.
- Register **2–3 A53-local dummy variables** (e.g. a counter + a sine) and one event;
  call `XcpEvent` from a periodic FreeRTOS task.
- Generate the A2L offline; load in CANape; connect over UDP.
- **Accept:** CANape connects, DAQ-measures the dummy variables, calibration of a dummy
  parameter works. This proves clock + queue + lwIP/UDP + C11 atomics on the real toolchain.
  Capture achievable DAQ rate + footprint.

### Phase 2 — XOR integration with JavaScope
- Add a `LOGGING_PATH` selector to `vitis/software/FreeRTOS/defines.h`
  (`LOGGING_PATH_JAVASCOPE` | `LOGGING_PATH_XCP_LITE`); under JavaScope, start the existing
  JS server (unchanged); under XCP_LITE, start the XCPlite UDP server. Both compile; one is
  selected. (Optionally a runtime toggle later — they are independent UDP/TCP endpoints.)
- **Accept:** building either mode yields the corresponding working logger; JavaScope path
  byte-identical to before.

### Phase 3 — Shared MEAS image from R5 (coherent real-signal DAQ) [needs R5 + hardware]
- Define a `MEAS image` struct in a dedicated OCM region. R5 control ISR writes a coherent
  snapshot each cycle (double-buffer or seqlock) + cache-flush + IPI (reuse the existing
  IPI mechanism; do **not** use XCPlite's atomics across cores).
- A53 IPI handler stages the image into an A53-local buffer, then calls `XcpEvent`; point
  the XCPlite measurements/A2L at that buffer (absolute addressing).
- **Accept:** CANape DAQ of real control signals, coherent (no torn multi-signal samples),
  at the control event rate.

### Phase 4 — Calibration image write-back [safety-critical, review]
- Add a double-buffered `CAL image`; map XCPlite calibration segments → CAL image; R5 adopts
  the active page atomically at a safe point in its cycle.
- **Accept:** live parameter change from CANape reaches R5 deterministically; reviewed for
  motor-control safety.

---

## 6. Open questions the agent should resolve and report
- Footprint (flash/RAM) of XCPlite on the A53 domain — gate for keeping the approach.
- Confirm C11 `stdatomic` builds under the Vitis 2022.2 aarch64 gcc (expected yes).
- Is **image-based** measurement acceptable for the intended workflow, or is
  arbitrary-R5-address measurement required? (If the latter, this whole A53 approach is the
  wrong tool — escalate.)
- DAQ throughput over UDP vs the JavaScope TCP baseline (~140 Mbit/s reference).
- Phase 4 calibration coherence/safety design before any live use.

## 7. Guardrails
- Never copy Vector **XCP Basic** sources here (license). XCPlite (MIT) only.
- Do not change JavaScope. Do not raise XCP task priority above lwIP.
- Commit only when the user asks; keep the vendored XCPlite tree and its MIT LICENSE intact.
