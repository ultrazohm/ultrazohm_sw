# FSD-MPC A53 accelerator: architecture audit and implementation gate

**State: stopped before A53 integration. No A53 FSD code was installed or timed.** This is the mandatory source and timing audit for the existing UltraZohm mechanism. The present hookup does not establish the required one-period command timing, and its response path does not provide the freshness and timeout contract needed for stateful FSD-MPC. R5-only benchmark and controller code remain unchanged.

## Provenance and evidence state

- Target checkout: `C:\GIT\UltraZohm\software\ultrazohm_sw_ZC_test_2`, branch `feature/uz_fsd_mpc_3ph_pmsm`, starting HEAD `adab99dce996e082eccf88f7d9bd98342f0c703b` (2026-10-09). Existing untracked reports `FSD_EXECUTION_TIME_REPORT.md`, `FSD_TIMING_INTEGRATION_AUDIT.md`, `INTEGRATION_PLAN.md`, `INTEGRATION_REPORT.md`, and `PWM_SAFETY_AUDIT.md` were present and left untouched.
- Source inspection only; no new R5/A53 source, shared ABI, PWM code, build configuration, controller mathematics, golden vectors, or archived qualification data changed. This report is the sole file created by the audit.
- The existing Vitis workspace has R5 and A53 projects and an older `FreeRTOS.elf`; that ELF is **not** an FSD accelerator build. The target hardware and a fresh A53/R5 deployment were not accessed in this campaign. No A53 runtime, numerical-equivalence, or timing result is claimed.

## Existing mechanism and precise paths

The platform documentation [A53 accelerator guide](docs/source/guide/apu_software/a53_accelerator.rst) describes an *experimental* JavaScope-coupled mechanism. [R5 data mover guide](docs/source/guide/rpu_software/datamover_r5.rst) describes the underlying OCM/IPI exchange. [Project setup](docs/source/guide/how_to_guides/vitis/create_project.rst) uses R5 bare metal and one A53 FreeRTOS application; [optimization guide](docs/source/guide/how_to_guides/vitis/gcc_optimization.rst) lists R5 `-O2` and A53 `-O3` defaults. Actual flags must be captured from the fresh target builds.

| Concern | Existing implementation |
|---|---|
| Shared memory/ABI | [`vitis/software/shared/APU_RPU_shared.h`](vitis/software/shared/APU_RPU_shared.h): bank 1 `0xFFFD0000` R5→A53 user data, bank 2 `0xFFFE0000` A53→R5 user data, bank 3 `0xFFFF0000` JavaScope; 64 KiB per bank. `USE_A53_AS_ACCELERATOR_FOR_R5_ISR` currently `FALSE`. User structs carry only `slowDataCounter`; no FSD request, response, ID, or sequence. |
| R5 request and return | [`vitis/software/Baremetal/src/sw/javascope.c`](vitis/software/Baremetal/src/sw/javascope.c), `JavaScope_update`: optional bank-1 write/flush, bank-3 JavaScope write/flush, `XIpiPsu_TriggerIpi`, optional `XIpiPsu_PollForAck(...,1000)`, IPI response-message read, bank-2 invalidate/read. Poll failure only increments `pollErrorCnt`; the function still reads the return path. |
| R5 scheduling | [`vitis/software/Baremetal/src/sw/isr.c`](vitis/software/Baremetal/src/sw/isr.c), `ISR_Control`: ADC/encoder and optional idle-only R5 benchmark, then existing PWM duty setters, **then** `JavaScope_update`, then ISR-timer toc. Thus an A53 result returned by this call cannot affect the PWM setters already executed in that ISR. No FSD duties currently reach PWM. |
| A53 work and reply | [`vitis/software/FreeRTOS/sw/isr.c`](vitis/software/FreeRTOS/sw/isr.c), `APU_IPI_ISR`: invalidates bank 3 and optional bank 1, handles JavaScope/one control message, contains an empty accelerator computation placeholder, optionally flushes bank 2, writes IPI response message, clears IPI interrupt status. It does not instantiate FSD-MPC. |
| A53 startup | [`vitis/software/FreeRTOS/main.c`](vitis/software/FreeRTOS/main.c) calls `Initialize_InterruptHandler` before starting the scheduler; `main_thread` calls `initialize_ipi_runtime`. [`vitis/software/FreeRTOS/sw/isr.c`](vitis/software/FreeRTOS/sw/isr.c) owns the IPI/GIC instances. No A53 FSD preload/reset lifecycle exists. |
| FSD state | [`vitis/software/Baremetal/src/uz/uz_fsd_mpc/uz_fsd_mpc.c`](vitis/software/Baremetal/src/uz/uz_fsd_mpc/uz_fsd_mpc.c): `uz_fsd_mpc_init/reset/step` manage a static instance, `next_applied`, update count and fault latch. [Public header](vitis/software/Baremetal/src/uz/uz_fsd_mpc/uz_fsd_mpc.h) exposes inputs, output/diagnostics and status, but no split-computation or state-transfer API. |
| R5 timing baseline | [Measured R5 report](FSD_EXECUTION_TIME_REPORT.md), [benchmark source](vitis/software/Baremetal/src/sw/fsd_mpc_benchmark.c), 100 MHz AXI uptime timer. The benchmark uses a frozen six-sample synthetic sequence, 12 warm-up steps and 6,000 measured steps per variant. |

```mermaid
sequenceDiagram
    participant R5 as R5 ISR_Control
    participant OCM as OCM banks 1/2/3
    participant A53 as A53 APU_IPI_ISR
    R5->>R5: ADC / encoder; existing PWM duty writes
    R5->>OCM: JavaScope_update: optional user request; cache flush
    R5->>A53: IPI trigger
    A53->>OCM: Invalidate request; optional computation; flush reply
    A53-->>R5: IPI acknowledgment and response message
    R5->>OCM: Invalidate/read user reply
    Note over R5: Current PWM setters have already run
```

The [accelerator guide's delay section](docs/source/guide/apu_software/a53_accelerator.rst) explicitly says this default placement adds an ISR-cycle offset for a controller result. It suggests moving `JavaScope_update` before the PWM setters, with a logging phase shift. That is a possible migration using the existing IPI/OCM mechanism, but it must be separately qualified for FSD and the 100 µs deadline. Reinterpreting the extra cycle by changing `+0.5Ts/+1.5Ts` prediction or adding a software duty queue is prohibited.

The application code uses `Xil_DCacheFlushRange` and `Xil_DCacheInvalidateRange` around its OCM exchanges; no explicit `DMB`/`DSB` instruction or sequence-word barrier appears in the inspected R5/A53 application functions. The generated BSP implementations of those cache calls and cache-line alignment must be checked in the actual build before extending the shared structs. The inspected accelerator example contains no calibrated A53 computation or R5↔A53 round-trip timing series for FSD-MPC.

## Proposed partition and wire contract, not implemented

The existing public FSD API makes an *entire `uz_fsd_mpc_step` on A53* the smallest behavior-preserving computational boundary. Offloading only `uz_fsd_mpc_solve_qp` would require a new partial-step API and moving candidate matrices and per-path solutions across OCM. For exhaustive SVM/IFT/VFT this increases transfers and still leaves gradients, prediction, objective, policy and duties on the R5. Copying the qualified float32 module to the A53 FreeRTOS project, with native SimplexFace only, would preserve its internal eight-observation math and one-period `next_applied` state. The R5 would own sampled input, expected request/update sequence, returned applied/calculated command chronology, safety validation and eventual PWM handoff; the A53 would own the numerical instance. That dual ownership needs explicit startup/reset synchronization.

A safe extension of the **existing** bank-1/bank-2 structs needs a fixed request kind (`init`, `step`, `reset`), monotonically increasing sequence and variant, eight float32 inputs, and a matching reply sequence, controller status, output/diagnostic fields and valid/invalid marker. R5 must reject a missing, stale, mismatched, invalid or late reply; it must stop benchmarking and leave duties invalid. It must never silently reuse the prior response. The existing bank-1 flush and bank-2 invalidate must be retained; both structs must remain within their 64 KiB banks and cache-line ownership must be checked. `XIpiPsu_PollForAck` alone is insufficient to prove the returned FSD output belongs to the current sample. The hard-coded poll count of 1000 is not calibrated as a 100 µs timeout.

The exact timing gate is: sample at `t_k`; request and full A53 calculation plus return must finish before the PWM-update point that makes command `k` active at `t_(k+1)`. If the JavaScope call stays after the PWM setters, an A53 result can first reach those setters at the *next* ISR, creating the documented extra cycle. To remove that structural delay, move the request/return point ahead of the setters **only under an explicit, default-disabled A53 benchmark build mode**, and demonstrate the returned command is ready before that update point. The current R5-only path must remain unchanged. No FSD output should be connected to the PWM driver during the benchmark.

## Timing plan and comparison status

Use the R5 100 MHz AXI uptime timer to measure preparation, request-to-ack, result handling, full round trip and total ISR. Use a documented A53 clock/counter only for its local full FSD computation; convert both to microseconds before comparison. Without a shared calibrated clock, one-way transfer latencies cannot be separately inferred from two unsynchronized timestamps. Measure initialization/preload apart from steps, timer read overhead, 6,000 valid post-warm-up calls, min/mean/max/p95/p99, misses and communication failures. A controller-only result below 100 µs would still not qualify the full ISR.

| Variant | Selector | Policy | QPs/step | R5 raw mean/max µs | A53 compute µs | R5↔A53 round-trip µs | Full ISR/deadline |
|---:|---|---|---:|---|---|---|---|
| 0 | Exhaustive | SVM | 6 | 297.41 / 307.41 | Not measured | Not measured | Not measured |
| 1 | Exhaustive | IFT | 6 | 190.85 / 197.42 | Not measured | Not measured | Not measured |
| 2 | Exhaustive | VFT | 12 | 410.41 / 426.84 | Not measured | Not measured | Not measured |
| 3 | Deadbeat | SVM | 1 | 57.79 / 62.93 | Not measured | Not measured | Not measured |
| 4 | Deadbeat | IFT | 1 | 40.51 / 43.58 | Not measured | Not measured | Not measured |
| 5 | Deadbeat | VFT | 2 | 76.79 / 84.70 | Not measured | Not measured | Not measured |

The R5 table is the supplied prior 100 µs-period campaign, `-O2`, 100 MHz timer, 6,000 steps per variant, all OK. It is baseline evidence, **not** an A53 result. No architecture winner can be selected.

## Implementation gate and minimum next actions

The blocker is the currently unqualified **one-period result/response contract** at `JavaScope_update`: its call site follows PWM setters, the enabled path has only an uncalibrated acknowledgment poll and no request/reply sequence or fault latch, and neither an A53 FSD instance nor an R5/A53 numerical replay exists. Installing a full stateful controller into that path now would risk an extra control cycle or accepting stale output. This triggers the campaign's instruction to report the timing blocker before changing the controller. It is not evidence that A53 acceleration is inherently too slow.

The smallest resolution is to (1) qualify a default-disabled early-ISR placement of the *existing* JavaScope IPI exchange with no PWM connection, (2) add a sequence-checked, status-bearing fixed OCM request/reply to the existing structs and a bounded time-based wait, (3) build both target projects and verify startup/reset/timeout/stale-result behavior, (4) then run the unchanged full float32 FSD step on A53 against frozen golden vectors and a stateful R5 replay, and (5) measure complete round-trip and full-ISR timing for all six variants before considering any live PWM integration. The Vitis workspace must be rebuilt/deployed with both R5 bare-metal and A53 FreeRTOS applications using the same shared header; the [workspace creation guide](docs/source/guide/how_to_guides/vitis/create_project.rst) and [`vitis/run_generate_workspace.bat`](vitis/run_generate_workspace.bat) describe project generation. No target measurement, Ceedling run or Vitis build was performed for this audit-only file.
