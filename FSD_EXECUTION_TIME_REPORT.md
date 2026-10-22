# FSD-MPC R5 execution-time benchmark report

**Status: first on-target R5 controller-only timing campaign recorded.** The measured values below were supplied after the benchmark implementation campaign; the original host fake-timer values are excluded. The target logs/build artifacts were not supplied for independent re-extraction. This report preserves the raw measurements as given and distinguishes them from the earlier host checks.

## Provenance and changed files

Target UltraZohm checkout: `C:\GIT\UltraZohm\software\ultrazohm_sw_ZC_test_2`, branch `feature/uz_fsd_mpc_3ph_pmsm`, starting HEAD `7088abbd63ba3903731b44568e81787683219683`. FSD reference checkout: `C:\GIT\hoernermi\publications\adaptive_modulation`, starting HEAD `92cb4d121885a632f2c30f7c8cbcf7bdbdfda378`. Both HEADs remained unchanged during this task. The user's uncommitted target include fixes and existing integration documents were preserved. The source checkout received only the three matching include-path corrections and a host-test include search path; numerical code and frozen vectors were not modified.

New target files: `src/include/fsd_mpc_benchmark.h`, `src/include/fsd_mpc_benchmark_stats.h`, `src/sw/fsd_mpc_benchmark.c`, `src/sw/fsd_mpc_benchmark_stats.c`, `test/sw/test_fsd_mpc_benchmark_stats.c`, `docs/source/software/control/uz_fsd_mpc/target_timing.rst`, `FSD_TIMING_INTEGRATION_AUDIT.md`, and this report. Small guarded edits: `src/uz/uz_global_configuration.h`, `src/globalData.h`, `src/main.c`, `src/sw/isr.c`, and the control documentation toctree. The FSD controller, solver, PWM driver, platform error handler and generated solver are unchanged.

## Benchmark configuration and safety

The build defaults to `UZ_FSD_BENCHMARK_ENABLE=0`. When enabled, the benchmark follows the documented PLL instance pattern: one pointer in `Global_Data.objects`, init in `main.c::init_software` after `uz_SystemTime_init`, and stepping in `ISR_Control`. The call is gated to `idle_state`. It never reads live ADC as FSD input, writes FSD duties to `Global_Data.rasv`, calls any PWM duty setter, changes enable GPIO, or enables a power stage. It tests the installed SI controller at `Rs=.51 ohm`, `Ld=Lq=.002 H`, `psi_pm=.042 Vs`, `Ts=.0001 s`, `lambda=10`, native SimplexFace. One build selects one of six variants:

| Variant | Selector | Policy | QP solves per step |
|---:|---|---|---:|
| 0 | exhaustive | SVM | 6 |
| 1 | exhaustive | IFT | 6 |
| 2 | exhaustive | VFT | 12 |
| 3 | deadbeat | SVM | 1 |
| 4 | deadbeat | IFT | 1 |
| 5 | deadbeat | VFT | 2 |

Six ordered samples come from frozen JSON SHA-256 `78f4870515e6af85204f02269a25dc927b76ab14a1d1a136a06b489d9bb7ff45`. The sequence is repeated across 12 warm-up and 6,000 measured calls; it includes sector, high modulation, low-voltage/negative-id, signed-speed and zero-speed cases. This is a synthetic stateful sequence, not a closed-loop plant run. Input validity is checked before each call. Status, finite duty bounds and physical schedule are checked after each call; any failure stops collection. The full step is timed, with no logging or schedule validation inside the timer pair.

## Timer and statistics

The target-supported source is `uz_AxiTimer64Bit_ReadValue64Bit()` from the cascaded 64-bit uptime timer already initialized by `uz_SystemTime_init`. Frequency comes from BSP macro `XPAR_UZ_SYSTEM_TIMER_UPTIME_64BIT_CLOCK_FREQ_HZ` via `UZ_AXI_TIMER_CLOCK_FREQ`; the measured campaign confirmed **100 MHz** (10 ns/tick). The target build used **`-O2`**, with **100 µs** configured sampling period. The benchmark stores raw ticks, preload ticks, minimum empty-read-pair overhead, min/max/mean step ticks, a bounded 1-us histogram with p95/p99 bins, count of samples at/above 100 us and exact failure status/index. Unsigned subtraction covers a timer wrap if one interval is shorter than the full counter range. Bin 100 represents `>=100 us` and has no upper bound. After the bounded run the R5 main loop prints one report outside the ISR timing interval. The existing ISR time remains a separate measurement; controller-only time cannot establish total ISR schedulability.

| Target result | Value |
|---|---|
| Processor/core | UltraZohm R5 application ISR; R5 processor clock not recorded in the supplied summary |
| Timer frequency | 100 MHz; 10 ns/tick, reported for the on-target run |
| Compiler/optimization/build mode | Target optimization `-O2`; other build flags not recorded in the supplied summary |
| Empty timer-read-pair overhead | 145 ticks = 1.45 µs, separate diagnostic |
| Initialization/preload duration | Timed separately by implementation; numerical result not supplied |
| Valid sample count | 6,000 per variant, after 12 warm-up calls |
| Raw min/max/mean | Complete six-variant results below |
| Raw p95/p99 | Collected by histogram but not supplied for this ledger update |
| Corrected min/max/mean | Not reported; raw measurements are primary |
| ISR duration/interrupt interference | Not measured on target |
| Stack and linker memory | Not measured on target |
| 100-us controller-only threshold | Variants 0–2: all 6,000 calls exceed 100 µs; variants 3–5: zero measured calls exceed 100 µs |
| Full-ISR deadline or WCET | No conclusion |

### Raw on-target controller-step results

Each row reports 6,000 measured consecutive `uz_fsd_mpc_step()` calls using the fixed six-sample sequence. All returned status OK, with no failed steps. The measured 145-tick read-pair overhead is **not subtracted** from these primary values; initialization/preload is a separate timing interval.

| Variant | Selector | Policy | QPs/step | Mean µs | Max µs | Min µs | Calls >100 µs | Status / failed steps |
|---:|---|---|---:|---:|---:|---:|---:|---|
| 0 | Exhaustive | SVM | 6 | 297.41 | 307.41 | 293.48 | 6,000 | OK / 0 |
| 1 | Exhaustive | IFT | 6 | 190.85 | 197.42 | 188.04 | 6,000 | OK / 0 |
| 2 | Exhaustive | VFT | 12 | 410.41 | 426.84 | 404.53 | 6,000 | OK / 0 |
| 3 | Deadbeat | SVM | 1 | 57.79 | 62.93 | 55.60 | 0 | OK / 0 |
| 4 | Deadbeat | IFT | 1 | 40.51 | 43.58 | 38.75 | 0 | OK / 0 |
| 5 | Deadbeat | VFT | 2 | 76.79 | 84.70 | 73.81 | 0 | OK / 0 |

The structural candidate counts match [the benchmark variant setup](vitis/software/Baremetal/src/sw/fsd_mpc_benchmark.c). Deadbeat selection substantially reduces both QP count and measured time. At equal candidate count, IFT is faster than SVM, consistent with [the SimplexFace mask loop](vitis/software/Baremetal/src/uz/uz_fsd_mpc/uz_fsd_mpc_solver.c) enumerating 7 admissible faces with a suppressed zero versus 15 without one. VFT performs provisional free QPs, doubling the counts shown above, and is more expensive in both selector groups. This explains the measured ordering but does not isolate every cycle of cost. Deadbeat + IFT is fastest here (40.51 µs mean, 43.58 µs maximum).

## Tests and outstanding qualification

`gcc -std=c99 -O2 -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wswitch-default -Walloca -Werror` compiled the benchmark and pure statistics code with host substitutes for the target BSP headers, without warnings. The new statistics tests passed in a host Unity-compatible harness (raw ticks, mean, histogram percentiles, wrap and default-disabled mode). A host flow harness with a fake timer compiled the installed controller and exercised all six variants for 6,000 measured stateful steps each; all ended with OK status and valid output. **The fake timer's ticks are not execution-time measurements.** The FSD source suite passed 332 tests after the include correction.

The user reported a prior 3/3 isolated FSD Ceedling result, 1507 passed / 2 expected ignored in the full suite, and a successful docs build; those were pre-benchmark results and were not independently rerun in the implementation shell. At that earlier point, `ceedling`, Sphinx and Vitis tools were unavailable there, and Docker access was denied. The later measured R5 campaign necessarily used a target build and execution, but its build log, Ceedling result, link map, ISR profile and raw terminal output were not supplied with the numerical summary. Those remain unverified in this documentation update.

The finite synthetic six-sample corpus does not prove worst-case execution time. In particular, zero controller-only overruns in variants 3–5 do not establish the complete ISR's 100 µs deadline margin. A future qualification should retain the target build and terminal logs, inspect link map/stack and all compiler flags, profile full-ISR duration and interrupt interference, and expand input coverage. The optional academic-license generated MATLAB ActiveSet backend has not been benchmarked.
