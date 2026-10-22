# FSD-MPC feature-branch integration report

## State and disposition

Source FSD checkout: `C:\GIT\hoernermi\publications\adaptive_modulation`, `main`, starting HEAD `1b847323269f75a59ac341b176cc8a9af40450c4`, initially clean. Target UltraZohm checkout: `C:\GIT\UltraZohm\software\ultrazohm_sw_ZC_test_2`, `feature/uz_fsd_mpc_3ph_pmsm`, HEAD `6425fe9794a4d27bf99f02758ed9a4bffa3abf36`, initially clean. Both HEADs remain unchanged; work is uncommitted. The earlier `ultrazohm_sw_develop` checkout was not edited.

**Integration status: partial.** The installed native SimplexFace module compiles and passes independent host C fixture checks and full Python64 differential replay. The actual target Ceedling suite could not run: `ceedling test:all` returned command not found; Ruby/Ceedling/Sphinx are not on PATH, the Docker daemon is unavailable, and WSL distribution enumeration is denied. No target runtime, stack, gate timing or power-stage claim follows from this work.

## Installed paths and provenance

Under `vitis/software/Baremetal/`:

| Installed file | Source and change | Installed SHA-256 |
|---|---|---|
| `src/uz/uz_fsd_mpc/uz_fsd_mpc.h` | FSD `c/uz_fsd_mpc/uz_fsd_mpc.h`, byte-identical | `E673649CF55749F87374C80231951C66A93184E04F734BA8F1CAEB242098A0D1` |
| `src/uz/uz_fsd_mpc/uz_fsd_mpc_math.c` | FSD `c/uz_fsd_mpc/uz_fsd_mpc_math.c`, byte-identical | `2C57530FE41BF40E7E146BF14260C90B47AD0131056119D7CF3FC5149B1F2129` |
| `src/uz/uz_fsd_mpc/uz_fsd_mpc.c` | FSD core, adds only a compile-time rejection of ActiveSet when the optional backend is absent | `6B6B5C7CCA0994EB860F8DE3F4569B48E1BA3DE74B43D7E2890BE3CC29131AD1` |
| `src/uz/uz_fsd_mpc/uz_fsd_mpc_private.h` | FSD private header, adds default-off backend switch | `D4616A344919B5DF7D22F44B48A7DA9C7152E8B395FA2BBBCA262AF54F7D86CD` |
| `src/uz/uz_fsd_mpc/uz_fsd_mpc_solver.c` | FSD solver adapter, conditionally compiles the unchanged generated-double adapter | `456CC899F5840E66BAE997584C1ECB4F4A6959136DD1D3519349B3820C327AE2` |
| `test/uz/uz_fsd_mpc/uz_fsd_mpc_fixture.h` | Offline generated from frozen JSON, nine SimplexFace configurations and 54 steps | `EE4804E027A41DD256601DCF55258302291CE5EA320D93AB4D56813212C83194` |
| `test/uz/uz_fsd_mpc/test_uz_fsd_mpc.c` | Native Unity numerical, state, status and assertion tests | `7C471A8CEF58F341778FE17817ABB0CE2C7E6F0A871CA4343EA435D790B07494` |
| `test/uz/uz_fsd_mpc/test_uz_fsd_mpc_limit.c` | Native Unity static-pool limit test | `B141455B98F8268701E57373E7DB1DDB7E96799FD7786E1BE9EC874846076B2B` |

`src/uz/uz_global_configuration.h` adds `UZ_FSD_MPC_MAX_INSTANCES=1` for production and 12 for tests. `docs/source/software/control/uz_fsd_mpc/uz_fsd_mpc.rst` is registered by one new entry in `software_framework_control.rst`. The root has `INTEGRATION_PLAN.md`, `PWM_SAFETY_AUDIT.md` and this report. No unrelated UltraZohm module was edited.

The frozen JSON oracle remains `qualification/c_golden/fsd_mpc_c_v1.json`, SHA-256 `78f4870515e6af85204f02269a25dc927b76ab14a1d1a136a06b489d9bb7ff45`; mixed-QP evidence SHA-256 `FE94F5E1C841AEBED69321A4BE8CB3E3AE58708CFD052AED39712D0FB545CB3F`. Selection is every qualified SimplexFace record (six SI and three p.u.), all six steps each, plus one selected-path QP. The offline script is `qualification/ultrazohm_integration/generate_fixture.py` in the FSD checkout. Expected values are rounded to float32 in the C fixture; tests use the measured field limits from `PRECISION_QUALIFICATION.md`.

## Backend and license

The native float32 SimplexFace core builds with no generated files. `UZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET` defaults to zero. When zero, selecting ActiveSet asserts at initialization; there is no hidden fallback. A local academic research build may set it to one, include the unchanged `fsd_quadprog_api.h` and compile/link `fsd_quadprog_generated.c` plus `rt_nonfinite.c` from the FSD research checkout. The generated C itself, its 60 extracted numerical functions, static managers and seven-iteration cap were not copied or modified. Its notice restricts use to teaching, academic research and course requirements at degree-granting institutions. Permission to redistribute it under the UltraZohm tree has not been established, so it remains outside this checkout. Calls to that backend must be serialized.

## Tests and build results

| Check | Command/result |
|---|---|
| Installed core, generated backend off | GCC C99 `-O2 -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wswitch-default -Walloca -Werror -DTEST`; compiled with actual target instance configuration, zero own-source warnings |
| Installed native fixture C executable | Built from installed source and installed Unity-test code with a small host assertion/Unity shim; nine configurations/54 steps, representative H/f/cost, schedules, faults and reset passed |
| Static instance limit executable | Built from installed source/test, 12 allocations then expected assertion passed |
| Installed core differential | Native-only nine configurations: result dictionary exactly matched qualified source C; no errors or material decision differences |
| Optional generated backend differential | Explicit `-DUZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET=1`, linking unchanged research solver locally; all 15 configurations/90 steps exactly matched qualified C differential metrics; no errors or material decisions |
| FSD golden JSON replay | Replayed 15 configurations/90 steps with unchanged oracle SHA-256 |
| Mixed-QP and precision checks | Byte-identical mixed-QP replay and C host precision metrics |
| Frozen Python trace | 252/252 arrays matched |
| Native Ceedling | `ceedling test:all` in `vitis/software/Baremetal`: **not run**, command not found |
| Sphinx docs build | **Not run**, `sphinx-build` unavailable; registered toctree target exists |

The repeatable installed-source host check is:

```powershell
cd C:\GIT\hoernermi\publications\adaptive_modulation
python -m qualification.ultrazohm_integration.check_installed C:\GIT\UltraZohm\software\ultrazohm_sw_ZC_test_2
python -m pytest -q -p no:cacheprovider
python -m qualification.architecture_trace qualification/frozen_architecture_trace.npz --compare
python -m qualification.c_golden.replay
python -m qualification.c_golden.mixed_qp
python -m c.test.qualify
```

The host C shim used by `check_installed` only substitutes Unity/CException assertion handling; it compiles the **installed** production C and native test files with the feature branch's actual test instance configuration. It is not a Ceedling result. In a supported UltraZohm development container, run `ceedling test:all` from `vitis/software/Baremetal`.

The FSD Python suite initially reported 331 passed/1 failed after the prior Git freeze because the oracle replayer compared the current Git HEAD metadata to the historical capture HEAD. Numerical records and every captured source-file hash matched. The replay/generator scripts now preserve the stored capture HEAD during byte comparison while still checking all source hashes and all numerical bytes. The frozen JSON was not changed. Final command `python -m pytest -q -p no:cacheprovider`: **332 passed**.

The own C files compile without warnings under the strict host flags above. If the optional generated source is compiled with the same aggressive flags, its archived code emits `-Wswitch-default`, possible aggressive-loop undefined behavior, possible uninitialized-value, and `rt_nonfinite.c` float-conversion warnings; its source was not edited to suppress these. No static analyzer was available. The installed controller has fixed-size state/workspaces and no heap allocation. Target stack, ABI size and WCET remain unmeasured.

## PWM finding and remaining work

`PWM_SAFETY_AUDIT.md` traces the actual duty path. The 2-level PWM driver uses range assertions, not an explicit finite-status return. NaN fails its `>=0` assertion; Inf fails a bound assertion. An invalid-duty call therefore triggers platform assertion behavior rather than a recoverable controller error. Omitting a register write leaves the previous duty and is not output inhibition. The identified system inhibit path is `ultrazohm_state_machine_set_error(true)` -> error entry -> `uz_axigpio_disable_pwm_and_power_electronics()`, which clears PWM and digital-enable GPIO bits. Its timing/electrical behavior still requires target validation. No adapter was connected and no live switching occurred.

Before target use: run native Ceedling in the documented development container; confirm local licensing for any optional generated backend; implement and test a hardware adapter that checks status/finite/range and invokes the verified inhibit path; measure actual stack and worst-case controller execution time; establish duty polarity and PWM update timing on the target; then conduct separate hardware qualification.
