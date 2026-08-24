from __future__ import annotations

from pathlib import Path

from .software_driver_config import driver_instance_values
from .software_models import (
    BOOL_LITERAL_OPTIONS,
    PWM_2L_MODE_OPTIONS,
    PWM_2L_TRIGGER_SOURCE_OPTIONS,
    DriverConfigField,
)
from .xparameters import resolve_pwm_base_address_macro


def build_project_wizard_pwm_context(
    source_dir: Path,
    pwm_2l_instance_count: int,
    pwm_3l_enabled: bool,
    driver_config: dict[str, dict[str, str]] | None = None,
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    driver_config = driver_config or {}
    instances: list[dict[str, object]] = []
    warnings: list[str] = []
    for index in range(pwm_2l_instance_count):
        pwm_macro, pwm_warning = resolve_pwm_base_address_macro(
            source_dir, "pwm_2l", index, search_xparameters=resolve_base_addresses
        )
        deadtime_macro, deadtime_warning = resolve_pwm_base_address_macro(
            source_dir, "deadtime_2l", index, search_xparameters=resolve_base_addresses
        )
        if pwm_warning:
            warnings.append(pwm_warning)
        if deadtime_warning:
            warnings.append(deadtime_warning)
        pwm_values = driver_instance_values(f"pwm_2l_{index}", pwm_2l_config_fields(), driver_config)
        deadtime_values = driver_instance_values(f"deadtime_2l_{index}", deadtime_2l_config_fields(), driver_config)
        instances.append(
            {
                "index": index,
                "pwm_base_address_macro": pwm_macro,
                "deadtime_base_address_macro": deadtime_macro,
                "duty_cycle_a": f"pwm_2L_{index}_halfBridgeDutyCycle_1",
                "duty_cycle_b": f"pwm_2L_{index}_halfBridgeDutyCycle_2",
                "duty_cycle_c": f"pwm_2L_{index}_halfBridgeDutyCycle_3",
                "pwm_config": pwm_values,
                "deadtime_config": deadtime_values,
            }
        )
    pwm_3l_macro = ""
    pwm_3l_config = driver_instance_values("pwm_3l_0", pwm_3l_config_fields(), driver_config)
    if pwm_3l_enabled:
        pwm_3l_macro, pwm_3l_warning = resolve_pwm_base_address_macro(
            source_dir, "pwm_3l", 0, search_xparameters=resolve_base_addresses
        )
        if pwm_3l_warning:
            warnings.append(pwm_3l_warning)
    return {
        "pwm_2l_instances": instances,
        "pwm_3l_enabled": pwm_3l_enabled,
        "pwm_3l_base_address_macro": pwm_3l_macro,
        "pwm_3l_config": pwm_3l_config,
        "warnings": warnings,
    }


def pwm_2l_config_fields() -> list[DriverConfigField]:
    return [
        DriverConfigField("ip_clk_frequency_Hz", "IP clock frequency Hz", "100000000"),
        DriverConfigField("Tristate_HB1", "Tristate HB1", "false", input_type="choice", options=BOOL_LITERAL_OPTIONS),
        DriverConfigField("Tristate_HB2", "Tristate HB2", "false", input_type="choice", options=BOOL_LITERAL_OPTIONS),
        DriverConfigField("Tristate_HB3", "Tristate HB3", "false", input_type="choice", options=BOOL_LITERAL_OPTIONS),
        DriverConfigField(
            "min_pulse_width_in_microseconds",
            "Minimum pulse width us",
            "UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US + UZ_PWM_DEADTIME_IN_US",
        ),
        DriverConfigField("PWM_freq_Hz", "PWM frequency Hz", "UZ_PWM_FREQUENCY"),
        DriverConfigField(
            "PWM_mode",
            "PWM mode",
            "normalized_input_via_AXI",
            input_type="choice",
            options=PWM_2L_MODE_OPTIONS,
        ),
        DriverConfigField("PWM_en", "PWM enable", "true", input_type="choice", options=BOOL_LITERAL_OPTIONS),
        DriverConfigField(
            "use_external_counter",
            "Use external counter",
            "true",
            input_type="choice",
            options=BOOL_LITERAL_OPTIONS,
        ),
        DriverConfigField("init_dutyCyc_HB1", "Initial duty HB1", "0.0f"),
        DriverConfigField("init_dutyCyc_HB2", "Initial duty HB2", "0.0f"),
        DriverConfigField("init_dutyCyc_HB3", "Initial duty HB3", "0.0f"),
        DriverConfigField("triangle_shift_HB1", "Triangle shift HB1", "0.0f"),
        DriverConfigField("triangle_shift_HB2", "Triangle shift HB2", "0.0f"),
        DriverConfigField("triangle_shift_HB3", "Triangle shift HB3", "0.0f"),
        DriverConfigField(
            "trigger_source",
            "Trigger source",
            "trigger_at_MIN",
            input_type="choice",
            options=PWM_2L_TRIGGER_SOURCE_OPTIONS,
        ),
    ]


def deadtime_2l_config_fields() -> list[DriverConfigField]:
    return [
        DriverConfigField("clock_frequency_MHz", "Clock frequency MHz", "100"),
        DriverConfigField("deadtime_us", "Deadtime us", "UZ_PWM_DEADTIME_IN_US"),
        DriverConfigField(
            "inverse_bottom_switch",
            "Inverse bottom switch",
            "false",
            input_type="choice",
            options=BOOL_LITERAL_OPTIONS,
        ),
    ]


def pwm_3l_config_fields() -> list[DriverConfigField]:
    return [
        DriverConfigField("enable", "Enable", "1"),
        DriverConfigField("mode", "Mode", "0"),
        DriverConfigField("carrier_frequency_Hz", "Carrier frequency Hz", "data->av.pwm_frequency_hz"),
        DriverConfigField("minimum_pulse_width", "Minimum pulse width", "0.01f"),
        DriverConfigField("initial_duty_a", "Initial duty A", "data->rasv.pwm_3L_0_halfBridgeDutyCycle_1"),
        DriverConfigField("initial_duty_b", "Initial duty B", "data->rasv.pwm_3L_0_halfBridgeDutyCycle_2"),
        DriverConfigField("initial_duty_c", "Initial duty C", "data->rasv.pwm_3L_0_halfBridgeDutyCycle_3"),
        DriverConfigField("tristate_a", "Tristate A", "0"),
        DriverConfigField("tristate_b", "Tristate B", "0"),
        DriverConfigField("tristate_c", "Tristate C", "0"),
    ]


def pwm_2l_state_isr_actions(instance_count: int, hardware_config: dict[str, str]) -> dict[str, list[str]]:
    behavior = hardware_config.get("pwm_2l_idle_error_behavior", "tristate_with_duty_cycle")
    enable_tristate = behavior == "tristate_with_duty_cycle"
    duty_values = [
        hardware_config.get("pwm_2l_idle_error_duty_hb1", "0.0f") or "0.0f",
        hardware_config.get("pwm_2l_idle_error_duty_hb2", "0.0f") or "0.0f",
        hardware_config.get("pwm_2l_idle_error_duty_hb3", "0.0f") or "0.0f",
    ]
    idle_error_lines: list[str] = []
    running_lines: list[str] = []
    for index in range(instance_count):
        for offset, duty_value in enumerate(duty_values):
            half_bridge = offset + 1
            idle_error_lines.append(
                f"Global_Data.rasv.pwm_2L_{index}_halfBridgeDutyCycle_{half_bridge} = {duty_value};"
            )
        if enable_tristate:
            idle_error_lines.append(
                f"uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_{index}, true, true, true);"
            )
            running_lines.append(
                f"uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_{index}, false, false, false);"
            )
    return {
        "idle_state": list(idle_error_lines),
        "running_state": running_lines,
        "control_state": [],
        "error_state": list(idle_error_lines),
    }


def half_bridge_duty_cycle_fields(pwm_2l_instance_count: int, pwm_3l_enabled: bool) -> list[str]:
    fields = [
        f"\tfloat pwm_2L_{pwm_index}_halfBridgeDutyCycle_{half_bridge};"
        for pwm_index in range(pwm_2l_instance_count)
        for half_bridge in range(1, 4)
    ]
    if pwm_3l_enabled:
        fields.extend(f"\tfloat pwm_3L_0_halfBridgeDutyCycle_{half_bridge};" for half_bridge in range(1, 4))
    return fields


def half_bridge_duty_cycle_initializers(pwm_2l_instance_count: int, pwm_3l_enabled: bool) -> list[str]:
    initializers = [
        f"        .pwm_2L_{pwm_index}_halfBridgeDutyCycle_{half_bridge} = 0.0f,"
        for pwm_index in range(pwm_2l_instance_count)
        for half_bridge in range(1, 4)
    ]
    if pwm_3l_enabled:
        initializers.extend(f"        .pwm_3L_0_halfBridgeDutyCycle_{half_bridge} = 0.0f," for half_bridge in range(1, 4))
    return initializers


def project_wizard_pwm_runtime_lines() -> list[str]:
    return ["    project_wizard_update_pwm_outputs(&Global_Data);"]
