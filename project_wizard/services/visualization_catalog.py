from __future__ import annotations

from typing import Any

from ..models import VisualizationSignal


def config_int(value: str, default: int, minimum: int, maximum: int) -> int:
    try:
        parsed = int(str(value))
    except (TypeError, ValueError):
        parsed = default
    return max(minimum, min(maximum, parsed))


def dac8831_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    return [
        VisualizationSignal(
            signal_id=f"dac8831_{slot_lower}_ch{channel}",
            slot=slot,
            label=f"{slot} DAC8831 output channel {channel}",
            enum_name=f"JSO_DAC8831_{slot}_CH{channel}",
            pointer_expression=f"&data->av.dac8831_{slot_lower}_ch{channel}",
        )
        for channel in range(8)
    ]


def temperature_visualization_signals(slot_lower: str, preset: str) -> list[VisualizationSignal]:
    signals: list[VisualizationSignal] = []
    slot = slot_lower.upper()
    zero_based_connector_labels = preset == "type_k_thermocouple"
    for group in ["A", "B", "C"]:
        for array_index in range(20):
            if zero_based_connector_labels:
                channel_label = f"{array_index:02d}"
                signal_id_channel = str(array_index)
                enum_channel = str(array_index)
            else:
                channel_label = str(array_index + 1)
                signal_id_channel = str(array_index + 1)
                enum_channel = str(array_index + 1)
            signal_id = f"temp_{slot_lower}_{group.lower()}_{signal_id_channel}"
            enum_name = f"JSO_TEMP_{slot_lower.upper()}_{group}_CH{enum_channel}"
            pointer = f"&data->av.temperature_card_{slot_lower}_channel_{group}.temperature[{array_index}]"
            signals.append(
                VisualizationSignal(
                    signal_id=signal_id,
                    slot=slot,
                    label=f"{slot_lower.upper()} temperature group {group} channel {channel_label}",
                    enum_name=enum_name,
                    pointer_expression=pointer,
                )
            )
    return signals


def encoder_visualization_signals(interface: str, prefix: str, slot_lower: str, channel: int) -> list[VisualizationSignal]:
    base_id = f"{prefix}_{slot_lower}_{channel}"
    enum_base = f"JSO_{interface.upper()}_{slot_lower.upper()}_CH{channel}"
    label_base = f"{slot_lower.upper()} {interface.upper()} channel {channel}"
    slot = slot_lower.upper()
    fields = [
        ("position_raw_single_turn", "POS_RAW_ST", "position raw single turn", "uint32"),
        ("position_raw_multi_turn", "POS_RAW_MT", "position raw multi turn", "uint32"),
        ("position_multi_turn", "POS_MT", "position multi turn", "uint32"),
        ("position_mech_si_single_turn", "POS_MECH_ST", "position mech SI single turn", "float"),
        ("position_el_si_single_turn", "POS_EL_ST", "position el SI single turn", "float"),
        ("speed_mech_si", "SPEED_MECH_SI", "speed mech SI", "float"),
        ("speed_el_si", "SPEED_EL_SI", "speed el SI", "float"),
        ("speed_mech_rpm", "SPEED_MECH_RPM", "speed mech rpm", "float"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"{base_id}_{field}",
            slot=slot,
            label=f"{label_base} {label}",
            enum_name=f"{enum_base}_{enum_suffix}",
            pointer_expression=f"&data->av.{base_id}_{field}",
            source_type=source_type,
        )
        for field, enum_suffix, label, source_type in fields
    ]


def incremental_encoder_visualization_signals(slot_lower: str, channel: int) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    base_id = f"incremental_encoder_{slot_lower}_{channel}"
    enum_base = f"JSO_INCREMENTAL_ENCODER_{slot}_CH{channel}"
    label_base = f"{slot} incremental encoder channel {channel}"
    fields = [
        ("theta_el", "THETA_EL", "electrical angle", "float"),
        ("omega_mech", "OMEGA_MECH", "mechanical speed", "float"),
        ("omega_mech_ma_n4", "OMEGA_MECH_MA_N4", "mechanical speed moving average N4", "float"),
        ("position", "POSITION", "position", "uint32"),
        ("position_w_offset", "POSITION_W_OFFSET", "position with offset", "uint32"),
        ("index_found", "INDEX_FOUND", "index found", "uint32"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"{base_id}_{field}",
            slot=slot,
            label=f"{label_base} {label}",
            enum_name=f"{enum_base}_{enum_suffix}",
            pointer_expression=f"&data->av.{base_id}_{field}",
            source_type=source_type,
        )
        for field, enum_suffix, label, source_type in fields
    ]


def resolver_ip_visualization_signals(slot_lower: str, channel: int) -> list[VisualizationSignal]:
    base_id = f"resolver_ip_{slot_lower}_{channel}"
    slot = slot_lower.upper()
    label_base = f"{slot} resolver IP channel {channel}"
    enum_base = f"JSO_RESOLVER_IP_{slot}_CH{channel}"
    fields = [
        ("position_mech_2pi", "POSITION_MECH_2PI", "position mech 2pi"),
        ("position_el_2pi", "POSITION_EL_2PI", "position el 2pi"),
        ("omega_mech_rad_s", "OMEGA_MECH_RAD_S", "omega mech rad/s"),
        ("n_mech_rpm", "N_MECH_RPM", "n mech rpm"),
        ("omega_el_rad_s", "OMEGA_EL_RAD_S", "omega el rad/s"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"{base_id}_{field}",
            slot=slot,
            label=f"{label_base} {label}",
            enum_name=f"{enum_base}_{enum_suffix}",
            pointer_expression=f"&data->av.{base_id}_{field}",
        )
        for field, enum_suffix, label in fields
    ]


def resolver_pl_interface_visualization_signals(slot_lower: str, channel: int) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    base_id = f"resolver_pl_interface_{slot_lower}_{channel}"
    enum_base = f"JSO_RESOLVER_PL_{slot}_CH{channel}"
    label_base = f"{slot} resolver PL interface channel {channel}"
    fields = [
        ("position_mech_2pi", "POS_MECH_2PI", "mechanical position", "float"),
        ("position_el_2pi", "POS_EL_2PI", "electrical position", "float"),
        ("omega_mech_rad_s", "OMEGA_MECH_RAD_S", "mechanical speed rad/s", "float"),
        ("n_mech_rpm", "N_MECH_RPM", "mechanical speed rpm", "float"),
        ("omega_el_rad_s", "OMEGA_EL_RAD_S", "electrical speed rad/s", "float"),
        ("revolution_counter", "REVOLUTION_COUNTER", "revolution counter", "int32"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"{base_id}_{field}",
            slot=slot,
            label=f"{label_base} {label}",
            enum_name=f"{enum_base}_{enum_suffix}",
            pointer_expression=f"&data->av.{base_id}_{field}",
            source_type=source_type,
        )
        for field, enum_suffix, label, source_type in fields
    ]


def io_card_visualization_signals(
    slot_lower: str,
    card: dict[str, object],
    option_values: dict[str, str],
) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    pins = io_card_axi_input_pins(card, option_values)
    return [
        VisualizationSignal(
            signal_id=f"io_card_{slot_lower}_pin_{pin:02d}",
            slot=slot,
            label=f"{slot} IO pin {pin:02d} (RX, AXI GPIO)",
            enum_name=f"JSO_IO_CARD_{slot}_PIN_{pin:02d}",
            pointer_expression=f"&data->av.io_card_{slot_lower}_dig_{pin:02d}",
            source_type="uint32",
        )
        for pin in pins
    ]


def io_card_axi_pins(card: dict[str, object], option_values: dict[str, str]) -> list[tuple[int, str]]:
    directions = io_card_directions(card, option_values)
    default_modes = card.get("vivado", {}).get("io_card", {}).get("default_modes", {})
    if not isinstance(default_modes, dict):
        default_modes = {}
    pins: list[tuple[int, str]] = []
    for index, direction in enumerate(directions):
        mode = option_values.get(f"io_pin_{index:02d}_mode", str(default_modes.get(direction, "axi_gpio")))
        if direction == "rx" and mode not in {"axi_gpio", "top_level"}:
            mode = "axi_gpio"
        if direction == "tx" and mode not in {"axi_gpio", "source_pin", "pwm", "constant"}:
            mode = "axi_gpio"
        if mode == "axi_gpio":
            pins.append((index, direction))
    return pins


def io_card_axi_output_pins(card: dict[str, object], option_values: dict[str, str]) -> list[int]:
    return [index for index, direction in io_card_axi_pins(card, option_values) if direction == "tx"]


def io_card_axi_input_pins(card: dict[str, object], option_values: dict[str, str]) -> list[int]:
    return [index for index, direction in io_card_axi_pins(card, option_values) if direction == "rx"]


def io_card_needs_axi(card: dict[str, object], option_values: dict[str, str]) -> bool:
    return bool(io_card_axi_pins(card, option_values))


def io_card_direction_mask(card: dict[str, object], option_values: dict[str, str]) -> int:
    directions = io_card_directions(card, option_values)
    mask = 0
    for index, direction in enumerate(directions):
        if direction == "rx":
            mask |= 1 << index
    return mask


def io_card_directions(card: dict[str, object], option_values: dict[str, str]) -> list[str]:
    io_card = card.get("vivado", {}).get("io_card", {})
    if not isinstance(io_card, dict):
        return []
    kind = str(io_card.get("kind", ""))
    pin_count = config_int(str(io_card.get("pin_count", "30")), default=30, minimum=1, maximum=30)
    variant_directions = io_card_variant_directions(io_card, option_values)
    if variant_directions:
        return variant_directions[:pin_count]
    if kind == "voltage_grouped":
        directions: list[str] = []
        groups = io_card.get("groups", [])
        if not isinstance(groups, list):
            return ["rx"] * pin_count
        for group_index, group in enumerate(groups, start=1):
            if not isinstance(group, dict):
                continue
            width = config_int(str(group.get("width", "0")), default=0, minimum=0, maximum=30)
            direction = option_values.get(f"direction_group_{group_index}", str(group.get("default", "rx")))
            directions.extend([direction if direction in {"tx", "rx"} else "rx"] * width)
        return directions[:pin_count]
    return ["rx"] * pin_count


def io_card_variant_directions(io_card: dict[str, object], option_values: dict[str, str]) -> list[str]:
    variant = selected_io_card_variant(io_card, option_values)
    if not variant:
        return []
    directions: list[str] = []
    for group in variant.get("directions", []):
        if not isinstance(group, dict):
            continue
        direction = str(group.get("direction", "rx")).strip().lower()
        if direction not in {"tx", "rx"}:
            direction = "rx"
        width = config_int(str(group.get("width", "0")), default=0, minimum=0, maximum=30)
        directions.extend([direction] * width)
    return directions


def selected_io_card_variant(io_card: dict[str, object], option_values: dict[str, str]) -> dict[str, object] | None:
    variants = io_card.get("variants", [])
    if not isinstance(variants, list) or not variants:
        return None
    option_id = str(io_card.get("variant_option", "io_variant"))
    selected_id = option_values.get(option_id, str(io_card.get("default_variant", "")))
    for variant in variants:
        if isinstance(variant, dict) and str(variant.get("id", "")) == selected_id:
            return variant
    first = variants[0]
    return first if isinstance(first, dict) else None


def adc_ltc2311_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    return [
        VisualizationSignal(
            signal_id=f"adc_ltc2311_{slot_lower}_ch{channel}",
            slot=slot,
            label=f"{slot} ADC LTC2311 channel {channel}",
            enum_name=f"JSO_ADC_{slot}_CH{channel}",
            pointer_expression=f"&data->av.adc_ltc2311_{slot_lower}_ch{channel}",
        )
        for channel in range(8)
    ]


def adc_max11331_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    return [
        VisualizationSignal(
            signal_id=f"adc_max11331_{slot_lower}_ch{channel}",
            slot=slot,
            label=f"{slot} ADC MAX11331 channel {channel}",
            enum_name=f"JSO_ADC_MAX11331_{slot}_CH{channel}",
            pointer_expression=f"&data->av.adc_max11331_{slot_lower}_ch{channel}",
        )
        for channel in range(24)
    ]


def inverter_adapter_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    fields = [
        ("pwm_duty_h1", "PWMdutyCycNormalized_H1", "PWM duty H1", "PWM_DUTY_H1", "float"),
        ("pwm_duty_l1", "PWMdutyCycNormalized_L1", "PWM duty L1", "PWM_DUTY_L1", "float"),
        ("pwm_duty_h2", "PWMdutyCycNormalized_H2", "PWM duty H2", "PWM_DUTY_H2", "float"),
        ("pwm_duty_l2", "PWMdutyCycNormalized_L2", "PWM duty L2", "PWM_DUTY_L2", "float"),
        ("pwm_duty_h3", "PWMdutyCycNormalized_H3", "PWM duty H3", "PWM_DUTY_H3", "float"),
        ("pwm_duty_l3", "PWMdutyCycNormalized_L3", "PWM duty L3", "PWM_DUTY_L3", "float"),
        ("chip_temp_h1", "ChipTempDegreesCelsius_H1", "chip temperature H1", "CHIP_TEMP_H1", "float"),
        ("chip_temp_l1", "ChipTempDegreesCelsius_L1", "chip temperature L1", "CHIP_TEMP_L1", "float"),
        ("chip_temp_h2", "ChipTempDegreesCelsius_H2", "chip temperature H2", "CHIP_TEMP_H2", "float"),
        ("chip_temp_l2", "ChipTempDegreesCelsius_L2", "chip temperature L2", "CHIP_TEMP_L2", "float"),
        ("chip_temp_h3", "ChipTempDegreesCelsius_H3", "chip temperature H3", "CHIP_TEMP_H3", "float"),
        ("chip_temp_l3", "ChipTempDegreesCelsius_L3", "chip temperature L3", "CHIP_TEMP_L3", "float"),
        ("oc", "OC", "OC status word", "OC", "uint32"),
        ("oc_h1", "OC_H1", "OC H1", "OC_H1", "bool"),
        ("oc_l1", "OC_L1", "OC L1", "OC_L1", "bool"),
        ("oc_h2", "OC_H2", "OC H2", "OC_H2", "bool"),
        ("oc_l2", "OC_L2", "OC L2", "OC_L2", "bool"),
        ("oc_h3", "OC_H3", "OC H3", "OC_H3", "bool"),
        ("oc_l3", "OC_L3", "OC L3", "OC_L3", "bool"),
        ("fault", "FAULT", "FAULT status word", "FAULT", "uint32"),
        ("fault_h1", "FAULT_H1", "FAULT H1", "FAULT_H1", "bool"),
        ("fault_l1", "FAULT_L1", "FAULT L1", "FAULT_L1", "bool"),
        ("fault_h2", "FAULT_H2", "FAULT H2", "FAULT_H2", "bool"),
        ("fault_l2", "FAULT_L2", "FAULT L2", "FAULT_L2", "bool"),
        ("fault_h3", "FAULT_H3", "FAULT H3", "FAULT_H3", "bool"),
        ("fault_l3", "FAULT_L3", "FAULT L3", "FAULT_L3", "bool"),
        ("i_diag", "I_DIAG", "I_DIAG status word", "I_DIAG", "uint32"),
        ("i_dc_diag", "I_DC_DIAG", "I DC diagnostic", "I_DC_DIAG", "bool"),
        ("i1_diag", "I1_DIAG", "I1 diagnostic", "I1_DIAG", "bool"),
        ("i2_diag", "I2_DIAG", "I2 diagnostic", "I2_DIAG", "bool"),
        ("i3_diag", "I3_DIAG", "I3 diagnostic", "I3_DIAG", "bool"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"inverter_adapter_{slot_lower}_{signal_suffix}",
            slot=slot,
            label=f"{slot} inverter adapter {label}",
            enum_name=f"JSO_INVERTER_ADAPTER_{slot}_{enum_suffix}",
            pointer_expression=f"&data->av.inverter_adapter_{slot_lower}.{field_name}",
            source_type=source_type,
        )
        for signal_suffix, field_name, label, enum_suffix, source_type in fields
    ]

