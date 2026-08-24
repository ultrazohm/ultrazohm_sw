from __future__ import annotations

from pathlib import Path

from .software_models import DAC_WAVEGEN_TYPES
from .xparameters import resolve_base_address_macro


def adc_ltc2311_context(
    slot: str,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "adc_ltc2311", search_xparameters=resolve_base_addresses
    )
    warnings = [warning] if warning else []
    context = {
        "slot": slot,
        "slot_lower": slot_lower,
        "base_address_macro": base_address_macro,
        "warnings": warnings,
    }
    context.update(config_values)
    return context


def adc_max11331_context(
    slot: str,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "adc_max11331", search_xparameters=resolve_base_addresses
    )
    warnings = [warning] if warning else []
    context = {
        "slot": slot,
        "slot_lower": slot_lower,
        "base_address_macro": base_address_macro,
        "warnings": warnings,
    }
    context.update(config_values)
    return context


def dac8831_context(
    slot: str,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "dac8831", search_xparameters=resolve_base_addresses
    )
    warnings = [warning] if warning else []
    output_assignments = [
        dac8831_output_assignment(slot_lower, channel, config_values)
        for channel in range(8)
    ]
    wavegen_instances = dac8831_wavegen_instances(slot_lower, config_values)
    context = {
        "slot": slot,
        "slot_lower": slot_lower,
        "base_address_macro": base_address_macro,
        "output_assignments": output_assignments,
        "wavegen_instances": wavegen_instances,
        "warnings": warnings,
    }
    context.update(config_values)
    return context


def dac8831_output_assignment(slot_lower: str, channel: int, config_values: dict[str, str]) -> str:
    prefix = f"output_ch{channel}"
    mode = config_values.get(f"{prefix}_source", "constant")
    constant = config_values.get(f"{prefix}_constant", "0.0f")
    amplitude = config_values.get(f"{prefix}_amplitude", "1.0f")
    frequency = config_values.get(f"{prefix}_frequency_Hz", "10.0f")
    duty_cycle = config_values.get(f"{prefix}_duty_cycle", "0.5f")
    offset = config_values.get(f"{prefix}_offset", "0.0f")
    if mode == "sine":
        expression = (
            f"uz_wavegen_sine_sample_with_offset("
            f"data->objects.{dac8831_wavegen_object_name(slot_lower, channel, mode)}, {amplitude}, {frequency}, {offset})"
        )
    elif mode == "sawtooth":
        expression = (
            f"uz_wavegen_sawtooth_sample_with_offset("
            f"data->objects.{dac8831_wavegen_object_name(slot_lower, channel, mode)}, {amplitude}, {frequency}, {offset})"
        )
    elif mode == "triangle":
        expression = (
            f"uz_wavegen_triangle_sample_with_offset("
            f"data->objects.{dac8831_wavegen_object_name(slot_lower, channel, mode)}, {amplitude}, {frequency}, {offset})"
        )
    elif mode == "square":
        expression = (
            f"uz_wavegen_square_sample("
            f"data->objects.{dac8831_wavegen_object_name(slot_lower, channel, mode)}, "
            f"{amplitude}, {frequency}, {duty_cycle}) + {offset}"
        )
    elif mode == "pulse":
        expression = (
            f"uz_wavegen_pulse_sample("
            f"data->objects.{dac8831_wavegen_object_name(slot_lower, channel, mode)}, "
            f"{amplitude}, {frequency}, {duty_cycle}) + {offset}"
        )
    elif mode == "white_noise":
        expression = f"uz_wavegen_white_noise({amplitude}) + {offset}"
    else:
        expression = constant
    return (
        f"    data->av.dac8831_{slot_lower}_ch{channel} = {expression};\n"
        f"    dac8831_{slot_lower}_outputs[{channel}] = data->av.dac8831_{slot_lower}_ch{channel};"
    )


def dac8831_actual_values(slot_lower: str) -> list[str]:
    return [f"\tfloat dac8831_{slot_lower}_ch{channel};" for channel in range(8)]


def dac8831_wavegen_object_name(slot_lower: str, channel: int, mode: str) -> str:
    return f"dac8831_{slot_lower}_ch{channel}_{mode}"


def dac8831_wavegen_instances(slot_lower: str, config_values: dict[str, str]) -> list[dict[str, str]]:
    instances: list[dict[str, str]] = []
    for channel in range(8):
        mode = config_values.get(f"output_ch{channel}_source", "constant")
        metadata = DAC_WAVEGEN_TYPES.get(mode)
        if metadata is None:
            continue
        instances.append(
            {
                "object_name": dac8831_wavegen_object_name(slot_lower, channel, mode),
                "type": metadata["type"],
                "init": metadata["init"],
                "count_define": metadata["count_define"],
            }
        )
    return instances


def adc_ltc2311_actual_values(slot_lower: str) -> list[str]:
    return [f"\tfloat adc_ltc2311_{slot_lower}_ch{channel};" for channel in range(8)]


def adc_max11331_actual_values(slot_lower: str) -> list[str]:
    return [f"\tfloat adc_max11331_{slot_lower}_ch{channel};" for channel in range(24)]


def analog_adc_packed_offsets(assignments: dict[str, str]) -> dict[str, dict[str, int]]:
    offsets: dict[str, dict[str, int]] = {}
    next_offset = 0
    for slot in ["A1", "A2", "A3"]:
        card_id = assignments.get(slot, "empty")
        if card_id == "analog_ltc2311_16":
            channel_count = 8
        elif card_id == "analog_max11331":
            channel_count = 24
        else:
            continue
        offsets[slot] = {
            "offset": next_offset,
            "channel_count": channel_count,
        }
        next_offset += channel_count
    return offsets


def adc_ltc2311_isr_lines(slot: str, context: dict[str, object], buffer_offset: int) -> list[str]:
    slot_lower = slot.lower()
    return [
        (
            f"    Global_Data.av.adc_ltc2311_{slot_lower}_ch{channel} = "
            f"uz_adcLtc2311_convert_raw_to_physical_value("
            f"Global_Data.objects.adc_ltc2311_{slot_lower}, analog_adc_data.data[{buffer_offset + channel}], {channel}U);"
        )
        for channel in range(8)
    ]


def adc_max11331_isr_lines(slot: str, context: dict[str, object], buffer_offset: int) -> list[str]:
    slot_lower = slot.lower()
    return [
        (
            f"    Global_Data.av.adc_max11331_{slot_lower}_ch{channel} = "
            f"convert_adc_max11331_{slot_lower}_raw_to_physical_value(analog_adc_data.data[{buffer_offset + channel}]);"
        )
        for channel in range(24)
    ]
