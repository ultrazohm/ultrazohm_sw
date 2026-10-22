# Experimental feasible-zero Yang selector: C integration and numerical gate

**Result:** The optional float32 selector matches the qualified Python64 six-bit screen on all 2,706 fixed-domain QP states, and C Yang selects the same physical command as C exhaustive for SVM, IFT and VFT. The five pre-existing SVM schedule rejections were resolved at the shared solver-to-scheduler float32 representation boundary. All 8,118 Yang and 8,118 exhaustive selected corpus schedules now pass, and the optional R5/A53 timing variants were measured on target. This remains an experimental branch, with no PWM or power-stage connection.

## Provenance and implemented contract

- UltraZohm checkout: `C:\GIT\UltraZohm\software\ultrazohm_sw_ZC_test_2`, branch `feature/uz_fsd_mpc_3ph_pmsm`, HEAD `adab99dce996e082eccf88f7d9bd98342f0c703b`. The checkout already contained unrelated modified and untracked A53 integration work; those changes were retained. No commit was made.
- Reference checkout: `C:\GIT\hoernermi\publications\adaptive_modulation`, HEAD `d4a878129d074ab102e69287b76a4960fff714c2`. Its existing research worktree files and frozen golden artifacts were retained. The new reproducible host scripts are in `qualification/yang_c_experiment/`.
- Source provenance: [Yang et al., IEEE TPEL 2022, Sec. IV-D](https://www.tobiasgeyer.org/YKTGLGK21_GradientBasedDMPC_2L.pdf), [adapted equation audit](../../../hoernermi/publications/adaptive_modulation/qualification/yang_adapted_preselection/SOURCE_AND_EQUATION_AUDIT.md), and [2 mH domain qualification](../../../hoernermi/publications/adaptive_modulation/qualification/yang_domain_qualification/REPORT.md). The feasible-zero anchor is project-derived; the paper does not guarantee it for this PMSM objective.
- The installed [R5 controller](vitis/software/Baremetal/src/uz/uz_fsd_mpc/uz_fsd_mpc.c) and [A53 copy](vitis/software/FreeRTOS/uz/uz_fsd_mpc/uz_fsd_mpc.c) have identical SHA-256 `85ED798AD182BAD7356120094001FA578467896F86260A06F88450F025DDE1A2`. Their public headers are identical, SHA-256 `9408FB21E8531B2E43E9FAF28673439973EC079918F9CD21465B465E7B06AF8C`. The solver and QP mathematics were not modified. The one change to the shared math/scheduler file is documented below. No generated MATLAB ActiveSet solver was linked.

For each path, the installed QP uses `J_s(x)=0.5 xᵀH_s x+f_sᵀx+c_s`, with `sum(x)=0.5`. The selector forms all six existing `H,f` pairs once. It evaluates `a=(0.25,0,0,0.25)`, `g=H a+f`, `z=a−g/128`, and `p=z+(0.5−sum(z))/4`. A path is suitable exactly when `p[1]>=0 && p[2]>=0`; zero is retained, with no clipping or tolerance. The step `1/128 A⁻²` is `1/(8√2 A)²`, matching the Python SI screen. Scaling the *whole* SI cost by `1/I_B²` would require the corresponding unit step in p.u.; a Yang+p.u. configuration is currently rejected explicitly, so no unqualified finite-precision equivalence is asserted.

Yang is selector enum value 2, behind a separately disabled benchmark opt-in; exhaustive and deadbeat retain enum values 0 and 1. It preserves canonical path order, strict lower-cost tie rule, the one-period command buffer, native float32 SimplexFace, and the existing SVM/IFT/VFT policy functions. An empty retained set returns `UZ_FSD_MPC_SELECTOR_EMPTY=5`, marks all duties invalid, and latches the controller fault. No fallback occurs. `output.work` gives six-bit mask, formulations and QP solves without copying the large diagnostic workspace during timing. The optional detailed diagnostic workspace still reports each solved candidate.

## Gate A evidence

Commands from `adaptive_modulation`:

```text
& qualification/yang_c_experiment/build_host.ps1
python -m qualification.yang_c_experiment.check_screen
python -m qualification.yang_c_experiment.check_corpus
python -m qualification.yang_c_experiment.check_steps
python -m qualification.yang_c_experiment.check_negative
python -m qualification.yang_c_experiment.check_empty
python -m qualification.architecture_trace qualification/frozen_architecture_trace.npz --compare
python -m pytest -q -p no:cacheprovider
```

The host DLL used the installed R5 sources, GCC `-std=c11 -O2 -DTEST -Wall -Wextra -Werror`. `check_screen` reconstructs each QP from the qualified CSV and compares both cast-Python64 `H,f` and natively formed C float32 `H,f`: **0/16,236 suitability-bit differences**, 0/2,706 six-bit-vector differences. Maximum absolute `H` and `f` differences from Python64 were 0.01088 and 0.00503 in the SI cost matrix/vector, respectively; decisions remained identical. All six sectors, 36/48/60 V, reverse speed, negative-id, FW, current limit, overmodulation, boundaries and zero ties are represented by that fixed corpus.

| Policy | Cases | Retain 1 / 2 / 6 | C Yang regret vs C exhaustive | Duty/schedule differences | QPs per step |
|---|---:|---:|---:|---:|---|
| SVM | 2,706 | 1,701 / 987 / 18 | 0 | 0 / 0 | 1 / 2 / 6 |
| IFT | 2,706 | 1,701 / 987 / 18 | 0 | 0 / 0 | 1 / 2 / 6 |
| VFT | 2,706 | 1,701 / 987 / 18 | 0 | 0 / 0 | 2 / 4 / 12 |

Sixty-four path IDs per policy differ from exhaustive; every associated C duty and physical schedule matches exactly, reflecting degenerate path representations. The largest absolute C exhaustive versus Python64 objective difference was 0.01008 A² across the corpus; this is a float32 differential observation, not a tuned acceptance tolerance. The existing frozen controller host fixtures still define their own qualified tolerances. The benchmark's six-sample stateful C replay ran 6,012 steps for each policy with no path/duty differences from C exhaustive. The A53 worker host test ran 6,012 matching stateful steps in each of variants 0–8 and rejected duplicate sequences.

Before the controller's existing representation-only clipping, 8/33/25 selected SVM/IFT/VFT commands had a phase duty outside `[0,1]` by at most `1.1921e−7`. None exceeded the existing `2e−7` clipping tolerance, and there was no Yang-versus-exhaustive duty difference. All final duties satisfy `[0,1]` after that existing clip.

The three historical λ=0/1 empty-set cases remain empty in float32: `boundary_0_0_0`, `boundary_0_2_6`, and `random_1`. The four historical positive-regret cases retain their previous sole paths (`2`, `3`, `0`, `4` respectively); this is a negative control, not qualification at λ=0/1. An explicit C-controller empty-set test returned status 5 with NaN duty markers and status 4 on the next call. NaNs are never passed to a PWM driver.

**Resolved shared float32 schedule boundary.** The solver accepts `fabsf(sum(x)-0.5f) <= 2e-7f`, and the scheduler's initial half-dwell check uses the same bound. Mirroring both halves can double the residual; the scheduler's former final check used only `2e-7f * period_s`. For all five cases, float32 full-period accumulation exceeded `T_s` by `2.1827872842550278e-11 s`, just above the former `2e-11 s` bound at `T_s=100 µs`. The single shared correction sets the final full-period check to `4e-7f * period_s` (`4e-11 s` here), matching two accepted half-period representation errors. The existing final-dwell reconciliation subtracts `2.1827872842550278e-11 s`. The solver, objective, Yang screen, policy and physical B6 construction are unchanged.

The R5 and A53 scheduler source files are byte-identical after the change (SHA-256 `264E6736684B646F7DE5F3B6B3DFFE79E381004596759B01A925F1D8262D38DD`). The same final-check correction was applied to the publications reference C copy so that its frozen differential tests exercise the same float32 contract.

| Previously rejected case | Half-sum residual | Path | B6 sequence |
|---|---:|---:|---|
| `eq_1_4_2_4` | +6.5193e-8 | 2 | 0,2,3,7,3,2,0 |
| `eq_1_8_2_5` | +5.2154e-8 | 3 | 0,1,3,7,3,1,0 |
| `op_48_1400_2_4` | +6.8918e-8 | 0 | 0,4,6,7,6,4,0 |
| `op_48_2000_0_0` | +7.0082e-8 | 1 | 0,2,6,7,6,2,0 |
| `step_torque_0109` | +6.7055e-8 | 5 | 0,4,5,7,5,4,0 |

For all five, the QP solution, path, duties, fixed-zero constraints, nonnegativity and B6 order are identical before and after the correction. All fixed-zero QP dwell coordinates remain exactly zero. Only the last dwell is shortened by the stated float32 reconciliation amount; the smallest post-correction dwell among the five is `6.888295160933922e-7 s`, so no dwell approaches zero. A Unity regression covers these five and still rejects a genuinely out-of-range half sum of `0.5000003`. The complete Yang/exhaustive C corpus now has zero selected schedule rejections, zero regret and zero duty or schedule differences. The six-sample stateful C comparison has 6,012 matching steps per policy, and the A53 worker host comparison has 6,012 matching steps in each variant 0–8.

The Python suite passed **354/354**, including frozen C golden differential tests, and the frozen architecture trace matched **252 arrays**. The installed target Unity source compiled and ran five relevant test functions under a GCC host harness; all passed. An attempt to run `ceedling test:all` in `vitis/software/Baremetal` failed because `ceedling` is not installed; Ruby is also unavailable in this shell. Thus the complete Ceedling runner and its CException-based invalid-configuration test remain unexecuted here. `git diff --check` passed. The correction is in the R5 and A53 copies of `uz_fsd_mpc_math.c` and the reference C copy; `uz_fsd_mpc_solver.c` is unchanged. See [measured R5/A53 timing](FSD_YANG_R5_A53_TIMING_REPORT.md).

## Changed files owned by this campaign

- R5: `vitis/software/Baremetal/src/uz/uz_fsd_mpc/{uz_fsd_mpc.c,uz_fsd_mpc.h,uz_fsd_mpc_private.h,uz_fsd_mpc_math.c}`, `src/uz/uz_global_configuration.h`, `src/sw/fsd_mpc_benchmark.c`, `src/sw/fsd_a53_benchmark.c`, and `test/uz/uz_fsd_mpc/test_uz_fsd_mpc.c`.
- A53: `vitis/software/FreeRTOS/uz/uz_fsd_mpc/{uz_fsd_mpc.c,uz_fsd_mpc.h,uz_fsd_mpc_private.h,uz_fsd_mpc_math.c}`, `sw/fsd_a53_worker.c`, `test/{build_a53_benchmark_variant.py,run_fsd_a53_worker_host.ps1,fsd_a53_worker_host.c}`.
- Shared: `vitis/software/shared/APU_RPU_shared.h` (three work-count response fields when the benchmark ABI is enabled).
- Evidence: this report, `FSD_YANG_R5_A53_TIMING_REPORT.md`, and new reference-only `qualification/yang_c_experiment/` scripts. The latter's host DLL is ignored. All existing benchmark variants 0–5, ISR order, PWM drivers, GPIO and safety state machine remain as they were.
