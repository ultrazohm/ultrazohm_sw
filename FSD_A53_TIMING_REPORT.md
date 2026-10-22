# FSD-MPC A53 execution-time benchmark

**Status:** six R5/A53 configurations were measured on the connected UltraZohm through JTAG on 9 October 2026. Each completed 6,000 measured controller steps with status OK and no failed calls. The A53 benchmark remained isolated from PWM. The raw UART lines and ELF hashes are preserved in [FSD_A53_TIMING_RAW.md](FSD_A53_TIMING_RAW.md). A clean XSCT `app build` still returned `Invalid Workspace`; the executed ELFs were linked from existing Vitis workspace objects plus newly cross-compiled benchmark/worker objects. This build provenance limits independent clean-build reproducibility, but the linked binaries did execute and produce the measured target results.

## Provenance and changed files

Target checkout: `C:\GIT\UltraZohm\software\ultrazohm_sw_ZC_test_2`, branch `feature/uz_fsd_mpc_3ph_pmsm`, starting HEAD `adab99dce996e082eccf88f7d9bd98342f0c703b`. Existing untracked R5 and integration reports were preserved. The preceding [architecture audit](FSD_A53_ACCELERATOR_REPORT.md) documented the production one-period timing gate; this continuation accepts the additional cycle **only for the isolated timing benchmark**.

Changed existing files: `vitis/software/shared/APU_RPU_shared.h`, `vitis/software/Baremetal/src/main.c`, `vitis/software/Baremetal/src/sw/isr.c`, `vitis/software/Baremetal/src/sw/javascope.c`, and `vitis/software/FreeRTOS/sw/isr.c`. New R5 benchmark helper: `src/include/fsd_a53_benchmark.h`, `src/sw/fsd_a53_benchmark.c`. New A53 worker: `vitis/software/FreeRTOS/include/fsd_a53_worker.h`, `sw/fsd_a53_worker.c`, and minimal `uz/uz_global_configuration.h`. The five files under `vitis/software/FreeRTOS/uz/uz_fsd_mpc/` are SHA-256 identical copies of the qualified R5 FSD module's C and header files. Native float32 SimplexFace is used; the optional MATLAB-generated solver is not copied or linked. Reproducible host test files are under `vitis/software/FreeRTOS/test/`. No controller mathematics, R5 controller source, frozen input data, PWM driver, GPIO or platform safety state machine was changed.

## Existing accelerator, benchmark sequence and safety

The mechanism remains the documented [JavaScope-coupled A53 accelerator](docs/source/guide/apu_software/a53_accelerator.rst): R5 writes an optional request to OCM bank 1 (`0xFFFD0000`) and flushes it, writes JavaScope data to bank 3, triggers the existing IPI, polls for acknowledgment, invalidates OCM bank 2 (`0xFFFE0000`) and reads the A53 response. A53 `APU_IPI_ISR` invalidates bank 1, runs the complete `uz_fsd_mpc_init/reset/step` in its existing accelerator placeholder, writes/flushes bank 2, then completes the existing IPI response. The shared header still owns the fixed OCM ABI. Bank sizes remain far below 64 KiB.

```mermaid
sequenceDiagram
    participant R5 as R5 JavaScope_update
    participant OCM as OCM bank 1 / bank 2
    participant A53 as A53 APU_IPI_ISR
    R5->>OCM: request kind, sequence, variant, eight input floats; flush bank 1
    R5->>A53: existing IPI trigger / acknowledgment poll
    A53->>OCM: invalidate bank 1; copy request
    A53->>A53: complete float32 FSD init or step; XTime ticks
    A53->>OCM: status, sequence, duties, update count, timing; flush bank 2
    A53-->>R5: existing IPI acknowledgment
    R5->>OCM: invalidate bank 2; validate response
    R5->>R5: record complete R5 round trip and A53 compute time
```

`UZ_FSD_A53_BENCHMARK_ENABLE` defaults to `0` in `APU_RPU_shared.h`. With it enabled in **both** processor builds, the R5-only benchmark is suppressed without changing its normal configuration. `UZ_FSD_A53_BENCHMARK_VARIANT` selects one of six variants per build. R5 sends the same six float32 input samples and order as its existing [R5 benchmark](vitis/software/Baremetal/src/sw/fsd_mpc_benchmark.c): one initialization/preload, then 12 warm-up steps and 6,000 measured steps. A53 holds the qualified controller's one-period `next_applied` state across consecutive calls. No FSD output is assigned to `Global_Data.rasv` or passed to a PWM setter. The benchmark only issues FSD requests while the platform is in `idle_state`. The pre-existing PWM setters and JavaScope call order are unchanged.

Each response must match request kind and sequence, report controller status OK, provide finite duties in `[0,1]`, keep a stable A53 timer frequency, and advance `update_count` as expected. A failed IPI trigger, acknowledgment, response-message read, stale sequence, invalid duty or controller status stops collection and reports a failed call. The A53 worker also rejects a duplicate/out-of-order step. Only active FSD requests use the benchmark poll. Its allowance is increased from 1,000 to 1,000,000 iterations to permit complete A53 solves; this is an **uncalibrated polling bound**, not a production deadline or fault-inhibit mechanism. Because PWM remains disconnected, the default late `JavaScope_update` placement and its additional control-cycle delay are accepted here only.

## Clocks, timers and measurement boundaries

The installed 2022.2 Vitis project uses R5 `-O2` and A53 `-O3` per `.cproject` and generated object build recipes. Generated BSP `xparameters.h` reports R5 processor clock **500 MHz**, A53 processor clock **1.05 GHz**, R5 AXI uptime timer **100 MHz**, and A53 timestamp counter **33,333,332 Hz** (`COUNTS_PER_SECOND` in `xtime_l.h`). These are distinct clock domains. The benchmark prints both timer frequencies from the compiled code; on-target output must confirm them before interpreting timing.

- **R5 round trip:** 100 MHz AXI timer read immediately before request flush through IPI trigger, acknowledgment and bank-2 invalidate, ending immediately before response validation. It includes JavaScope/IPI/cache work within that span and A53 computation. An empty timer-read pair is not yet measured for this new span.
- **A53-only computation:** A53 `XTime_GetTime` immediately around `uz_fsd_mpc_init/reset` or `uz_fsd_mpc_step`, excluding request copy and response copy/flush. Initialization/preload and measured steps are separate.
- **Communication residual:** for the same successful samples, `mean(R5 round-trip ticks)/100000000 × 10^6 − mean(A53 compute ticks)/33333332 × 10^6` µs. This includes R5 preparation/handling, cache and IPI overhead and timer-read effects; it cannot be split into calibrated one-way transfer times from unsynchronized counters.
- **Histogram:** fixed 1 µs bins with p95/p99 reported as bin upper edges; bin 100 means ≥100 µs. Raw min/mean/max remain primary. The existing total ISR timer can be inspected separately; controller/round-trip timing alone does not qualify the complete ISR.

## Six-variant target comparison

The earlier R5-only campaign used `-O2`; this A53 campaign used A53 `-O3` and R5 `-O2`. The table uses **raw**, uncorrected ticks converted by the measured timer frequencies. R5-only means/maxima come from [FSD_EXECUTION_TIME_REPORT.md](FSD_EXECUTION_TIME_REPORT.md). The first three R5-only variants exceeded 100 us on every measured call in that campaign. Each A53 row here has status OK, 6,000 valid samples and zero failed calls.

| Variant | Selector | Policy | QPs/step | R5-only mean/max us | A53 compute min/mean/max us | R5/A53 round trip min/mean/max us | Mean residual us | Round trips >=100 us |
|---:|---|---|---:|---:|---:|---:|---:|---:|
| 0 | Exhaustive | SVM | 6 | 297.41 / 307.41 | 90.63 / **91.95** / 94.14 | 96.33 / **97.71** / 99.98 | 5.76 | 0 |
| 1 | Exhaustive | IFT | 6 | 190.85 / 197.42 | 56.55 / **57.45** / 58.83 | 62.33 / **63.25** / 64.65 | 5.80 | 0 |
| 2 | Exhaustive | VFT | 12 | 410.41 / 426.84 | 116.91 / **118.80** / 122.10 | 122.47 / **124.57** / 127.86 | 5.77 | 6,000 |
| 3 | Deadbeat | SVM | 1 | 57.79 / 62.93 | 16.35 / **16.80** / 17.97 | 21.97 / **22.61** / 23.85 | 5.81 | 0 |
| 4 | Deadbeat | IFT | 1 | 40.51 / 43.58 | 10.80 / **11.04** / 11.61 | 16.44 / **16.84** / 17.45 | 5.80 | 0 |
| 5 | Deadbeat | VFT | 2 | 76.79 / 84.70 | 20.76 / **21.45** / 23.10 | 26.49 / **27.29** / 28.98 | 5.84 | 0 |

Mean A53 computation is 3.23-3.67 times faster than the corresponding R5-only mean. End-to-end R5/A53 round-trip means are 2.41-3.29 times faster than R5-only computation. The communication residual is consistently about 5.8 us; it is an **aggregate subtraction from unsynchronized clocks**, not a one-way transport latency. Variant 4 (deadbeat + IFT) is fastest: 11.04 us A53 mean and 16.84 us round-trip mean. Variant 0's maximum round trip was 99.98 us, leaving essentially no nominal 100-us margin for the rest of the ISR. Variant 2 exceeded 100 us in all 6,000 round trips. The others' measured round trips fit below 100 us, but **none is a full-ISR deadline qualification**.

The 1-us histogram upper-edge p95/p99 values for R5 round trip were respectively 100/100, 65/65, >=100/>=100, 24/24, 18/18 and 29/29 us for variants 0-5. A53 compute p95/p99 upper edges were 94/94, 59/59, >=100/>=100, 18/18, 12/12 and 23/24 us. Bin 100 is saturated and means **at least** 100 us; its value is not an exact percentile for variant 2. Raw maxima above are more informative. The benchmark did not measure an empty timer-read pair, so no timer overhead has been subtracted.

### Initialization and validity

Initialization/preload was measured separately from the 6,000 steps. R5 round-trip/A53-only initialization times in variant order were 115.59/103.56, 80.68/68.58, 143.29/130.98, 41.35/29.16, 35.31/23.10 and 46.39/33.81 us. They do not enter the steady-step table.

Each R5 response check required matching request kind/sequence, status OK, expected update count, stable nonzero A53 timer frequency and finite phase duties in `[0,1]`. All six runs passed those checks. The separate 6,012-step host replay checked stateful numerical agreement with a second instance of the same qualified C controller at `1e-6` duty tolerance and rejected duplicate sequences. That host replay is numerical/protocol evidence, while the UART tick values are the target timing evidence.

## Build, tests and deployment

The target was confirmed to have no attached power stage. COM5 was captured at 115200 baud. For each variant, both processor ELFs were compiled with `UZ_FSD_A53_BENCHMARK_ENABLE=1` and matching `UZ_FSD_A53_BENCHMARK_VARIANT`, linked against the existing generated BSP libraries and available Vitis workspace object set, then downloaded by the repository's standard full-reset JTAG sequence. Six independent full-reset loads succeeded; their timing lines and ELF SHA-256 hashes are in the raw evidence file. The benchmark enable remains `0U` in the source header. FSD duties were never routed to PWM, and the board was left running the completed variant-5 benchmark in its normal Idle state.

The standalone [build-and-launch helper](vitis/software/FreeRTOS/test/build_a53_benchmark_variant.py) reproduces this **hybrid** object-link method with `python vitis/software/FreeRTOS/test/build_a53_benchmark_variant.py N` for variant `N=0..5`; it writes both ELFs and a `launch.tcl` under `FSD_A53_BUILD_DIR` (default: system temporary directory). Run the generated Tcl with XSCT while capturing COM5 at 115200 baud. It does not replace a clean Vitis application build.

The Vitis 2022.2 R5 cross compiler used `-O2`, Cortex-R5 hard-float VFPv3-D16; the A53 cross compiler used `-O3`. The checked-in generated workspace makefiles had stale resource lists for newly added files. An attempted clean `app build` in XSCT returned `Invalid Workspace`, so the executed ELFs used newly compiled changed files plus pre-existing workspace objects; this is recorded rather than represented as a clean project rebuild. Existing BSP clocks and the UART's reported clock values agreed: R5 timer 100 MHz, A53 timer 33,333,332 Hz. The host worker test passed for all six variants. Ceedling was unavailable in this shell. `git diff --check` passed.

**Limitations:** The A53 path uses the end-of-ISR JavaScope exchange and introduces an additional control-cycle delay. The result is an isolated timing benchmark, not closed-loop use. The host replay compares two instances of the same qualified C mathematics, not independent target hardware arithmetic. The synthetic six-sample corpus and 6,000 finite samples do not prove WCET. Neither the complete ISR deadline nor one-way communication latency was measured. A clean, fully regenerated Vitis build and full closed-loop timing/safety qualification remain outstanding. The optional MATLAB-generated ActiveSet backend was excluded.
