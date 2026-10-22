# Experimental Yang selector: measured UltraZohm R5 and A53 timing

After the [shared float32 scheduler correction](FSD_YANG_C_INTEGRATION_REPORT.md), all nine variants completed 6,000 measured controller steps with status OK and no failed steps on the connected UltraZohm. This is a controller-only synthetic benchmark. The board has no attached power stage and controller commands were not connected to PWM. All 18 UART captures and 17 JTAG launch captures are in `adaptive_modulation/qualification/yang_c_experiment/target_logs/` in the publications checkout; the first R5-only Yang/SVM run has UART evidence but no saved JTAG launch capture. Each variant used the same six synthetic input samples and 12 warm-ups.

## R5-only execution

The R5 timer is 100 MHz. Times are raw ticks divided by 100, without overhead subtraction. The read-pair overhead is 145 ticks (1.45 µs); initialization/preload is separate. Every variant formulates six QPs per step. The overrun column counts measured calls above 100 µs, not full ISR deadlines.

| Variant | Selector / policy | QP solves/step | Raw min / mean / max (µs) | Init (µs) | >100 µs |
|---:|---|---:|---:|---:|---:|
| 0 | Exhaustive / SVM | 6 | 293.90 / 297.74 / 307.25 | 319.56 | 6,000 |
| 1 | Exhaustive / IFT | 6 | 189.01 / 191.49 / 198.12 | 214.56 | 6,000 |
| 2 | Exhaustive / VFT | 12 | 405.71 / 411.45 / 427.32 | 438.05 | 6,000 |
| 3 | Deadbeat / SVM | 1 | 55.85 / 58.21 / 63.91 | 79.47 | 0 |
| 4 | Deadbeat / IFT | 1 | 39.02 / 41.08 / 44.35 | 64.72 | 0 |
| 5 | Deadbeat / VFT | 2 | 74.08 / 77.14 / 85.64 | 101.84 | 0 |
| 6 | Yang / SVM | 1 or 2 | 103.80 / 126.21 / 153.07 | 127.85 | 6,000 |
| 7 | Yang / IFT | 1 or 2 | 86.58 / 99.54 / 114.91 | 111.41 | 3,000 |
| 8 | Yang / VFT | 2 or 4 | 122.24 / 154.88 / 195.45 | 149.85 | 6,000 |

Yang retained one path on 3,000 calls and two paths on 3,000 calls. SVM/IFT therefore solved 9,000 QPs in 6,000 steps; VFT solved 18,000. The independent 2,706-state corpus has a different distribution (one/two/six paths: 1,701/987/18). The R5 histogram's one-microsecond `100` bin overflows, so exact p95/p99 above 100 µs are unavailable. Raw min/mean/max and overrun counts are the primary measurements.

## R5/A53 execution

The 100 MHz R5 timer encloses OCM/IPI request, A53 controller step and response. The local A53 `XTime` counter is 33,333,332 Hz and encloses its full controller step. Each clock is converted independently. Values are raw ticks divided by the respective clock frequency, rounded to two decimals. Timer overhead was not subtracted. All runs had 6,000 valid requests and zero failed steps.

| Variant | Selector / policy | R5 round-trip min / mean / max (µs) | A53 compute min / mean / max (µs) | >100 µs round trips | Init R5 / A53 (µs) |
|---:|---|---:|---:|---:|---:|
| 0 | Exhaustive / SVM | 96.44 / 97.75 / 100.09 | 90.72 / 92.04 / 94.38 | 2 | 116.35 / 104.52 |
| 1 | Exhaustive / IFT | 62.24 / 63.15 / 64.57 | 56.70 / 57.42 / 58.83 | 0 | 81.38 / 69.48 |
| 2 | Exhaustive / VFT | 122.52 / 124.22 / 127.70 | 116.85 / 118.50 / 121.95 | 6,000 | 142.87 / 131.10 |
| 3 | Deadbeat / SVM | 22.03 / 22.53 / 23.73 | 16.35 / 16.80 / 17.97 | 0 | 40.99 / 28.98 |
| 4 | Deadbeat / IFT | 16.34 / 16.80 / 17.48 | 10.80 / 11.07 / 11.73 | 0 | 35.20 / 23.01 |
| 5 | Deadbeat / VFT | 26.39 / 27.11 / 28.81 | 20.76 / 21.39 / 23.07 | 0 | 46.85 / 34.29 |
| 6 | Yang / SVM | 43.67 / 49.82 / 57.10 | 38.04 / 44.10 / 51.30 | 0 | 61.31 / 49.65 |
| 7 | Yang / IFT | 37.93 / 41.07 / 44.59 | 32.37 / 35.34 / 38.82 | 0 | 56.37 / 44.34 |
| 8 | Yang / VFT | 47.98 / 56.58 / 66.81 | 42.39 / 50.85 / 61.14 | 0 | 66.17 / 54.60 |

The A53 Yang path/QP histogram matched R5-only: 3,000 one-path and 3,000 two-path calls. Round-trip minus A53 compute mean is about 5.7 µs; this aggregate includes handoff and timer measurement and is not a calibrated one-way latency. One-microsecond histogram p95/p99 upper bins for Yang round-trip / compute were 57/52 µs (SVM), 45/39 µs (IFT), and 67/61 µs (VFT). Bins saturate at 100 µs for exhaustive VFT. Exhaustive SVM had two round trips above 100 µs despite its mean below 100 µs.

## Interpretation and limitations

On these six samples, Yang is faster than exhaustive and slower than deadbeat in both execution modes. The selector reduces QP solves but still forms six QPs and computes six projections per step. Yang/IFT was the fastest measured Yang policy: R5 mean 99.54 µs with 3,000 over-budget calls; A53 compute mean 35.34 µs; R5/A53 round-trip mean 41.07 µs with zero measured overruns. The synthetic workload does not establish general execution bounds, formal WCET or full-ISR deadline qualification. The experimental A53 extra-cycle handoff is not a qualified closed-loop deployment. No generated MATLAB ActiveSet benchmark was performed. Historical comparison reports are [R5](FSD_EXECUTION_TIME_REPORT.md) and [A53](FSD_A53_TIMING_REPORT.md); the table above is a fresh same-campaign rerun.

## Build and measurement provenance

- Target: UltraZohm R5/A53 via XSCT 2022.2 JTAG, UART COM5 at 115200 baud, no power stage. A full reset and new ELF download preceded each variant. No PWM or safety state machine was changed for this experiment.
- Compiler: Vitis 2022.2; R5 `-O2 -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16`, A53 `-O3`. The helper links newly compiled changed sources with existing Vitis workspace objects/BSP libraries. These are hybrid object links, not clean Vitis workspace builds. Existing FreeRTOS ISR and R5 JavaScope warnings did not prevent linking.
- Rebuild: `python vitis/software/FreeRTOS/test/build_a53_benchmark_variant.py N --r5-only` for R5-only, or omit `--r5-only` for the R5/A53 pair, where `N=0..8`. Yang 6–8 use explicit `UZ_FSD_YANG_EXPERIMENT_ENABLE=1`. Capture with `adaptive_modulation/qualification/yang_c_experiment/run_target_variant.ps1 -Mode r5|a53 -Variant N`.
- Rebuilt SHA-256, Yang variants 6/7/8 respectively: R5-only `B9F62FB39C292FB965A0AF481821F5B5E4C1736C1CEF0BF5F6D420BFBE9E9BC5`, `BB0D6345669052519C3FC60355FDD06DDC252CF56B36982E890C13D2BAA58E89`, `ADA64BAD51ABD44AAED56C7B9D4CE7F366305F9B7D6A66BB81259C01C2F63D80`; paired R5 `47A7522E952B8C06173FE78FB00ADE78A976FD42E09A2EA33AF3618B7E54B975`, `E7563F4314331F79A54EF41E5D7A3F42AF5502CAFEC4A5F5B6FF1291DA8D232C`, `B18777C884D90880950B2A65E914D2EB94AAAC09638C4291DFF1E92469B6CDE2`; A53 `5DD51A8834EF9426213F4B03ED1E034A0983FF2D66AA190F59D0BC85470D8CDC`, `F0CDF4D98358927542DCE70A885AC05E2338E8553811F7D123AF352BD8F150FC`, `572599D1EE44F36278E2BEDADBF350A6936F56C4994776287F5883BEC931CC5A`.

The [integration report](FSD_YANG_C_INTEGRATION_REPORT.md) records the float32 correction, five counterexamples and host regressions. Ceedling itself remains unavailable in this environment; a direct GCC harness ran five relevant installed Unity test functions successfully.
