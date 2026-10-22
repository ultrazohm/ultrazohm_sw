# PWM invalid-duty and inhibit audit (feature branch)

Target checkout: `feature/uz_fsd_mpc_3ph_pmsm`, HEAD `6425fe9794a4d27bf99f02758ed9a4bffa3abf36`. This is a source audit, not a hardware timing qualification. No FSD output was routed to a live PWM.

## Duty path and invalid values

`vitis/software/Baremetal/src/IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.c::uz_PWM_SS_2L_set_duty_cycle` forwards three normalized float duties to `uz_PWM_SS_2L_hw_SetDutyCycle` after pointer/instance assertions. The hardware function in `uz_PWM_SS_2L_hw.c` checks `duty >= 0.0f` and `duty <= 1.0f` for each phase, then calls `uz_convert_float_to_sfixed(duty,16)` and writes the three Q16 values with `uz_axi_write_uint32` to `m_u1_norm`, `m_u2_norm` and `m_u3_norm` AXI registers. `uz_AXI.h::uz_convert_float_to_sfixed` uses `ldexpf` followed by a cast to `int32_t`.

There is **no explicit `isfinite` check**. NaN makes both ordered comparisons false, so it triggers an assertion before the cast in this code path. `+Inf` fails the upper-bound assertion; `-Inf` fails the lower-bound assertion. This is not a recoverable error return: the production `uz_assert` in `uz_HAL.h` invokes `Xil_Assert`, whose callback stops/disables the platform. Test builds throw a CException. Relying on assertion behavior is unsuitable for the controller's recoverable runtime-status contract; `NaN` remains an invalid marker and must never be passed to the driver. The existing PWM hardware tests cover ordinary out-of-range finite duties and base-address assertions, not NaN/Inf.

The driver itself accepts normalized phase duties in `[0,1]`; it performs Q16 conversion. The PWM IP uses configurable `trigger_at_MIN`, `trigger_at_MAX` or `trigger_at_EITHER` for output of new duty/triangle-shift signals (`docs/source/ip_cores/uz_PWM_SS_2L/uz_pwm_ss_2l.rst`, `uz_PWM_SS_2L.h`). These update events are distinct from a software-side decision to skip a register write. Skipping a write leaves the previous value in place and does **not** inhibit gates. No implicit `1-duty` conversion is present in the inspected duty path; any required physical polarity/carrier mapping must be established in a later hardware adapter and kept out of the FSD core.

## Inhibit mechanism and timing limit

`uz_PWM_SS_2L_hw_SetStatus(base_address, false)` writes the PWM IP enable register, but the public `uz_PWM_SS_2L` API exposes its enable flag only through initialization. `uz_PWM_SS_2L_set_tristate` writes half-bridge tristate controls; it is a separate IP feature, not the established system fault path.

The documented platform state machine has an error state (`docs/source/guide/rpu_software/r5_statemachine.rst`). `vitis/software/Baremetal/src/hw_init/uz_platform_state_machine.c::ultrazohm_state_machine_set_error(true)` enters error and calls the state-machine step. On error entry, `uz_axigpio_disable_pwm_and_power_electronics()` is called. In `vitis/software/Baremetal/src/hw_init/gpio_axi.c`, that function clears both `AXI_GPIO_PWM_MODULES` and `AXI_GPIO_DIGITAL_ENABLE` via `XGpio_DiscreteClear`. The state-machine documentation says gate signals are not routed through the CPLD outside Running/Control. This is the identified platform-level inhibit path. Its call-to-gate latency and electrical behavior have **not** been measured here.

A later hardware adapter must check `status == UZ_FSD_MPC_OK`, `isfinite` for all duties, and `[0,1]` bounds **before** any PWM duty write. On failure it should request the documented platform error/inhibit path and avoid writing duties. That adapter must be unit-tested and hardware-qualified before live use. The integration campaign does not implement or call a live PWM adapter.
