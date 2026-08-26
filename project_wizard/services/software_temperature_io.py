from __future__ import annotations

from pathlib import Path

from .visualization_catalog import io_card_axi_input_pins, io_card_axi_output_pins, io_card_direction_mask
from .xparameters import resolve_base_address_macro, resolve_device_id_macro


def temperature_context(
    slot: str,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "temperature", search_xparameters=resolve_base_addresses
    )
    warnings = [warning] if warning else []
    return {
        "slot": slot,
        "slot_lower": slot_lower,
        "base_address_macro": base_address_macro,
        "ip_clk_frequency_hz": config_values["ip_clk_frequency_hz"],
        "sample_frequency_hz": config_values["sample_frequency_hz"],
        "config_global_a": config_values["config_global_a"],
        "config_mux_a": config_values["config_mux_a"],
        "config_global_b": config_values["config_global_b"],
        "config_mux_b": config_values["config_mux_b"],
        "config_global_c": config_values["config_global_c"],
        "config_mux_c": config_values["config_mux_c"],
        "configdata_a": config_values["configdata_a"],
        "configdata_b": config_values["configdata_b"],
        "configdata_c": config_values["configdata_c"],
        "warnings": warnings,
    }


def temperature_actual_values(slot_lower: str) -> list[str]:
    return [
        f"\tuz_temperaturecard_OneGroup temperature_card_{slot_lower}_channel_A;",
        f"\tuz_temperaturecard_OneGroup temperature_card_{slot_lower}_channel_B;",
        f"\tuz_temperaturecard_OneGroup temperature_card_{slot_lower}_channel_C;",
    ]


def temperature_main_init(slot_lower: str) -> list[str]:
    return [
        f"\t\t\tGlobal_Data.objects.temperature_card_{slot_lower} = initialize_temperature_card_{slot_lower}();",
        f"\t\t\tuz_TempCard_IF_Reset(Global_Data.objects.temperature_card_{slot_lower});",
        f"\t\t\tuz_TempCard_IF_Start(Global_Data.objects.temperature_card_{slot_lower});",
    ]


def temperature_isr_lines(slot_lower: str) -> list[str]:
    return [
        f"    uz_TempCard_IF_MeasureTemps_cyclic(Global_Data.objects.temperature_card_{slot_lower});",
        (
            f"    Global_Data.av.temperature_card_{slot_lower}_channel_A = "
            f"uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_{slot_lower}, 'A');"
        ),
        (
            f"    Global_Data.av.temperature_card_{slot_lower}_channel_B = "
            f"uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_{slot_lower}, 'B');"
        ),
        (
            f"    Global_Data.av.temperature_card_{slot_lower}_channel_C = "
            f"uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_{slot_lower}, 'C');"
        ),
    ]


def temperature_configdata_a(preset: str) -> str:
    values = ["0U"] * 20
    if preset == "type_k_thermocouple":
        values[1] = "SENSOR_TYPE__SENSE_RESISTOR | SENSE_RESISTOR_VALUE_1k"
        values[3] = (
            "SENSOR_TYPE__RTD_PT_100 | RTD_RSENSE_CHANNEL__2 | RTD_NUM_WIRES__2_WIRE | "
            "RTD_EXCITATION_MODE__NO_ROTATION_SHARING | RTD_EXCITATION_CURRENT__100UA | RTD_STANDARD__EUROPEAN"
        )
        for index in range(4, 20):
            values[index] = (
                "SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | "
                "TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO"
            )
    elif preset == "pt100_2wire":
        values[1] = "SENSOR_TYPE__SENSE_RESISTOR | SENSE_RESISTOR_VALUE_1k"
        for index in range(3, 20, 2):
            values[index] = (
                "SENSOR_TYPE__RTD_PT_100 | RTD_RSENSE_CHANNEL__2 | RTD_NUM_WIRES__2_WIRE | "
                "RTD_EXCITATION_MODE__NO_ROTATION_SHARING | RTD_EXCITATION_CURRENT__100UA | RTD_STANDARD__EUROPEAN"
            )
    return "\n".join(f"        [{index}] = {value}," for index, value in enumerate(values))


def axi_gpio_context(
    slot: str,
    source_dir: Path,
    card: dict[str, object],
    option_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "axi_gpio", search_xparameters=resolve_base_addresses
    )
    device_id_macro, device_warning = resolve_device_id_macro(
        source_dir, slot, "axi_gpio", search_xparameters=resolve_base_addresses
    )
    warnings = [entry for entry in [warning, device_warning] if entry]
    return {
        "slot": slot,
        "slot_lower": slot_lower,
        "base_address_macro": base_address_macro,
        "device_id_macro": device_id_macro,
        "fallback_device_id": d_slot_index(slot) - 1,
        "direction_mask": f"0x{io_card_direction_mask(card, option_values):08X}",
        "direction_mask_define": f"PROJECT_WIZARD_IO_CARD_{slot.upper()}_DIRECTION_MASK",
        "axi_input_pins": io_card_axi_input_pins(card, option_values),
        "axi_output_pins": io_card_axi_output_pins(card, option_values),
        "warnings": warnings,
    }


def axi_gpio_actual_values(slot_lower: str, input_pins: list[int]) -> list[str]:
    lines = [f"\tuint32_t io_card_{slot_lower}_state;"]
    lines.extend(f"\tuint32_t io_card_{slot_lower}_dig_{pin:02d};" for pin in input_pins)
    return lines


def axi_gpio_main_init(slot_lower: str) -> list[str]:
    return [f"\t\t\tGlobal_Data.objects.axi_gpio_{slot_lower} = initialize_axi_gpio_{slot_lower}();"]


def axi_gpio_isr_lines(slot_lower: str, input_pins: list[int], output_pins: list[int]) -> list[str]:
    lines = [
        f"    Global_Data.av.io_card_{slot_lower}_state = uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_{slot_lower});"
    ]
    lines.extend(
        f"    Global_Data.av.io_card_{slot_lower}_dig_{pin:02d} = "
        f"(Global_Data.av.io_card_{slot_lower}_state >> DIG_{pin:02d}) & 0x1U;"
        for pin in input_pins
    )
    if output_pins:
        lines.extend(
            [
                f"    update_axi_gpio_{slot_lower}_outputs();",
                f"    uz_axi_gpio_flush_outputs(Global_Data.objects.axi_gpio_{slot_lower});",
            ]
        )
    return lines


def axi_gpio_isr_user_block(slot_lower: str, output_pins: list[int]) -> list[str]:
    if not output_pins:
        return []
    lines = [f"static void update_axi_gpio_{slot_lower}_outputs(void)", "{"]
    lines.extend(
        f"    uz_axi_gpio_set_output_pin_to(Global_Data.objects.axi_gpio_{slot_lower}, DIG_{pin:02d}, LOW);"
        for pin in output_pins
    )
    lines.append("}")
    return lines


def d_slot_index(slot: str) -> int:
    try:
        return int(slot[1:])
    except (TypeError, ValueError):
        return 1
