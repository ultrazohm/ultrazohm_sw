from __future__ import annotations

from pathlib import Path

from .xparameters import resolve_base_address_macro


def inverter_adapter_context(
    slot: str,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "inverter_adapter", search_xparameters=resolve_base_addresses
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


def inverter_adapter_actual_values(slot_lower: str) -> list[str]:
    return [f"\tstruct uz_inverter_adapter_outputs_t inverter_adapter_{slot_lower};"]


def inverter_adapter_main_init(slot_lower: str) -> list[str]:
    return [f"\t\t\tGlobal_Data.objects.inverter_adapter_{slot_lower} = initialize_inverter_adapter_{slot_lower}();"]


def inverter_adapter_state_actions(slot_lower: str) -> dict[str, list[str]]:
    return {
        "idle_state": [f"uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_{slot_lower}, false);"],
        "running_state": [f"uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_{slot_lower}, true);"],
        "control_state": [],
        "error_state": [f"uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_{slot_lower}, false);"],
    }


def inverter_adapter_isr_lines(slot_lower: str) -> list[str]:
    return [f"    update_inverter_adapter_{slot_lower}_outputs(&Global_Data);"]


def incremental_encoder_context(
    slot: str,
    channel: int,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "incremental_encoder", channel, search_xparameters=resolve_base_addresses
    )
    warnings = [warning] if warning else []
    context = {
        "slot": slot,
        "slot_lower": slot_lower,
        "channel": str(channel),
        "base_address_macro": base_address_macro,
        "warnings": warnings,
    }
    context.update(config_values)
    return context


def incremental_encoder_actual_values(slot_lower: str, channel: int) -> list[str]:
    name = f"incremental_encoder_{slot_lower}_{channel}"
    return [
        f"\tfloat {name}_theta_el;",
        f"\tfloat {name}_omega_mech;",
        f"\tfloat {name}_omega_mech_ma_n4;",
        f"\tuint32_t {name}_position;",
        f"\tuint32_t {name}_position_w_offset;",
        f"\tuint32_t {name}_index_found;",
    ]


def incremental_encoder_main_init(slot_lower: str, channel: int) -> list[str]:
    return [f"\t\t\tGlobal_Data.objects.incremental_encoder_{slot_lower}_{channel} = initialize_incremental_encoder_{slot_lower}_{channel}();"]


def incremental_encoder_isr_lines(context: dict[str, object]) -> list[str]:
    slot_lower = str(context["slot_lower"])
    channel = str(context["channel"])
    name = f"incremental_encoder_{slot_lower}_{channel}"
    object_ref = f"Global_Data.objects.{name}"
    return [
        f"    Global_Data.av.{name}_theta_el = uz_incrementalEncoder_get_theta_el({object_ref});",
        f"    Global_Data.av.{name}_omega_mech = uz_incrementalEncoder_get_omega_mech({object_ref});",
        f"    Global_Data.av.{name}_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4({object_ref});",
        f"    Global_Data.av.{name}_position = uz_incrementalEncoder_get_position({object_ref});",
        f"    Global_Data.av.{name}_position_w_offset = uz_incrementalEncoder_get_position_wOffset({object_ref});",
        f"    Global_Data.av.{name}_index_found = uz_incrementalEncoder_get_Index_Found({object_ref});",
    ]


def resolver_ip_context(
    slot: str,
    channel: int,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "resolver_ip", channel, search_xparameters=resolve_base_addresses
    )
    warnings = [warning] if warning else []
    context = {
        "slot": slot,
        "slot_lower": slot_lower,
        "channel": str(channel),
        "base_address_macro": base_address_macro,
        "warnings": warnings,
    }
    context.update(config_values)
    return context


def resolver_pl_interface_context(
    slot: str,
    channel: int,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, "resolver_pl_interface", channel, search_xparameters=resolve_base_addresses
    )
    warnings = [warning] if warning else []
    context = {
        "slot": slot,
        "slot_lower": slot_lower,
        "channel": str(channel),
        "base_address_macro": base_address_macro,
        "warnings": warnings,
    }
    context.update(config_values)
    return context


def resolver_channel_count(slot: str) -> int:
    return 2 if slot == "D5" else 3


def resolver_pl_interface_enabled(option_values: dict[str, str], channel: int) -> bool:
    return config_bool(option_values.get(f"enable_pl_interface_ch{channel}", "true"), default=True)


def resolver_ip_actual_values(slot_lower: str, channel: int) -> list[str]:
    name = f"resolver_ip_{slot_lower}_{channel}"
    return [
        f"\tfloat {name}_position_mech_2pi;",
        f"\tfloat {name}_position_el_2pi;",
        f"\tfloat {name}_omega_mech_rad_s;",
        f"\tfloat {name}_n_mech_rpm;",
        f"\tfloat {name}_omega_el_rad_s;",
    ]


def resolver_ip_main_init(slot_lower: str, channel: int) -> list[str]:
    return [f"\t\t\tGlobal_Data.objects.resolver_ip_{slot_lower}_{channel} = initialize_resolver_ip_{slot_lower}_{channel}();"]


def resolver_ip_isr_lines(slot_lower: str, channel: int) -> list[str]:
    name = f"resolver_ip_{slot_lower}_{channel}"
    object_ref = f"Global_Data.objects.{name}"
    mechanical_ref = f"{name}_mechanical"
    electrical_ref = f"{name}_electrical"
    return [
        f"    struct uz_resolverIP_position_velocity_t {mechanical_ref} = uz_resolverIP_readMechanicalPositionAndVelocity({object_ref});",
        f"    struct uz_resolverIP_position_velocity_t {electrical_ref} = uz_resolverIP_readElectricalPositionAndVelocity({object_ref});",
        f"    Global_Data.av.{name}_position_mech_2pi = {mechanical_ref}.position;",
        f"    Global_Data.av.{name}_position_el_2pi = {electrical_ref}.position;",
        f"    Global_Data.av.{name}_omega_mech_rad_s = {mechanical_ref}.velocity;",
        f"    Global_Data.av.{name}_n_mech_rpm = {mechanical_ref}.velocity * 9.549296585513721f;",
        f"    Global_Data.av.{name}_omega_el_rad_s = {electrical_ref}.velocity;",
    ]


def resolver_pl_interface_actual_values(slot_lower: str, channel: int) -> list[str]:
    name = f"resolver_pl_interface_{slot_lower}_{channel}"
    return [
        f"\tint32_t {name}_revolution_counter;",
        f"\tfloat {name}_position_mech_2pi;",
        f"\tfloat {name}_position_el_2pi;",
        f"\tfloat {name}_omega_mech_rad_s;",
        f"\tfloat {name}_n_mech_rpm;",
        f"\tfloat {name}_omega_el_rad_s;",
    ]


def resolver_pl_interface_main_init(slot_lower: str, channel: int) -> list[str]:
    return [
        f"\t\t\tGlobal_Data.objects.resolver_pl_interface_{slot_lower}_{channel} = initialize_resolver_pl_interface_{slot_lower}_{channel}();"
    ]


def resolver_pl_interface_isr_lines(slot_lower: str, channel: int) -> list[str]:
    name = f"resolver_pl_interface_{slot_lower}_{channel}"
    object_ref = f"Global_Data.objects.{name}"
    output_ref = f"{name}_outputs"
    return [
        f"    struct uz_resolver_pl_interface_outputs_t {output_ref} = uz_resolver_pl_interface_get_outputs({object_ref});",
        f"    Global_Data.av.{name}_revolution_counter = {output_ref}.revolution_counter;",
        f"    Global_Data.av.{name}_position_mech_2pi = {output_ref}.position_mech_2pi;",
        f"    Global_Data.av.{name}_position_el_2pi = {output_ref}.position_el_2pi;",
        f"    Global_Data.av.{name}_omega_mech_rad_s = {output_ref}.omega_mech_rad_s;",
        f"    Global_Data.av.{name}_n_mech_rpm = {output_ref}.n_mech_rpm;",
        f"    Global_Data.av.{name}_omega_el_rad_s = {output_ref}.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_{slot_lower}_{channel});",
    ]


def serial_encoder_context(
    slot: str,
    channel: int,
    interface: str,
    source_dir: Path,
    config_values: dict[str, str],
    resolve_base_addresses: bool = True,
) -> dict[str, object]:
    slot_lower = slot.lower()
    base_address_macro, warning = resolve_base_address_macro(
        source_dir, slot, interface, channel, search_xparameters=resolve_base_addresses
    )
    warnings = [warning] if warning else []
    context = {
        "slot": slot,
        "slot_lower": slot_lower,
        "channel": str(channel),
        "base_address_macro": base_address_macro,
        "warnings": warnings,
    }
    context.update(config_values)
    return context


def encoder_actual_values(prefix: str, slot_lower: str, channel: int) -> list[str]:
    name = f"{prefix}_{slot_lower}_{channel}"
    return [
        f"\tuint32_t {name}_position_raw_single_turn;",
        f"\tuint32_t {name}_position_raw_multi_turn;",
        f"\tuint32_t {name}_position_multi_turn;",
        f"\tfloat {name}_position_mech_si_single_turn;",
        f"\tfloat {name}_position_el_si_single_turn;",
        f"\tfloat {name}_speed_mech_si;",
        f"\tfloat {name}_speed_el_si;",
        f"\tfloat {name}_speed_mech_rpm;",
    ]


def endat_main_init(slot_lower: str, channel: int) -> list[str]:
    return [
        f"\t\t\tGlobal_Data.objects.endat_encoder_{slot_lower}_{channel} = initialize_endat_encoder_{slot_lower}_{channel}();",
        f"\t\t\tuz_endat_interface_set_mode_command(Global_Data.objects.endat_encoder_{slot_lower}_{channel}, uz_endat_interface_send_position);",
        f"\t\t\tuz_endat_interface_enable_ip(Global_Data.objects.endat_encoder_{slot_lower}_{channel}, true);",
    ]


def ssi_main_init(slot_lower: str, channel: int) -> list[str]:
    return [
        f"\t\t\tGlobal_Data.objects.ssi_encoder_{slot_lower}_{channel} = initialize_ssi_encoder_{slot_lower}_{channel}();",
        f"\t\t\tuz_ssi_interface_enable_ip(Global_Data.objects.ssi_encoder_{slot_lower}_{channel}, true);",
    ]


def encoder_isr_lines(interface: str, prefix: str, slot_lower: str, channel: int) -> list[str]:
    name = f"{prefix}_{slot_lower}_{channel}"
    driver_prefix = f"uz_{interface}_interface"
    object_ref = f"Global_Data.objects.{name}"
    return [
        f"    Global_Data.av.{name}_position_raw_single_turn = {driver_prefix}_get_position_raw_single_turn({object_ref});",
        f"    Global_Data.av.{name}_position_raw_multi_turn = {driver_prefix}_get_position_raw_multi_turn({object_ref});",
        f"    Global_Data.av.{name}_position_multi_turn = {driver_prefix}_get_position_multi_turn({object_ref});",
        f"    Global_Data.av.{name}_position_mech_si_single_turn = {driver_prefix}_get_position_mech_si_single_turn({object_ref});",
        f"    Global_Data.av.{name}_position_el_si_single_turn = {driver_prefix}_get_position_el_si_single_turn({object_ref});",
        f"    Global_Data.av.{name}_speed_mech_si = {driver_prefix}_get_speed_mech_si({object_ref});",
        f"    Global_Data.av.{name}_speed_el_si = {driver_prefix}_get_speed_el_si({object_ref});",
        f"    Global_Data.av.{name}_speed_mech_rpm = {driver_prefix}_get_speed_mech_rpm({object_ref});",
    ]


def config_bool(value: object, default: bool = False) -> bool:
    if value is None:
        return default
    if isinstance(value, bool):
        return value
    return str(value).strip().lower() in {"1", "true", "yes", "on"}
