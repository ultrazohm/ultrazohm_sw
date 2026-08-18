from __future__ import annotations

from typing import Any

from ..models import (
    PROJECT_CONFIG_SCHEMA_VERSION,
    PlatformConfig,
    SlotConfig,
    SoftwareConfig,
    SystemConfig,
)
from ..paths import DIGITAL_SLOTS, SLOTS


def build_system_config(
    platform: dict[str, Any],
    platform_cpld: dict[str, str],
    toolchain: dict[str, str],
    hardware: dict[str, str],
    slots: dict[str, str],
    slot_options: dict[str, dict[str, str]],
    slot_cplds: dict[str, str],
    cpld_programmer: dict[str, str],
    axi: dict[str, str],
    software_source_dir: str,
    software_modes: dict[str, str],
    software_presets: dict[str, str],
    visualization_routes: dict[str, str],
    driver_config: dict[str, dict[str, str]],
    software_extra: dict[str, str] | None = None,
) -> SystemConfig:
    return SystemConfig(
        schema_version=PROJECT_CONFIG_SCHEMA_VERSION,
        platform_config=PlatformConfig(
            id=str(platform.get("id", "")),
            revision=str(platform.get("revision", "")),
            cpld={str(key): str(value) for key, value in platform_cpld.items()},
        ),
        toolchain={str(key): str(value) for key, value in toolchain.items()},
        hardware={str(key): str(value) for key, value in hardware.items()},
        slot_configs={
            slot: SlotConfig(
                card_id=str(slots.get(slot, "empty")),
                options={str(key): str(value) for key, value in slot_options.get(slot, {}).items()},
                cpld_program=str(slot_cplds.get(slot, "none")) if slot in DIGITAL_SLOTS else "none",
            )
            for slot in SLOTS
        },
        cpld_programmer={str(key): str(value) for key, value in cpld_programmer.items()},
        axi={str(key): str(value) for key, value in axi.items()},
        software_config=SoftwareConfig(
            source_dir=str(software_source_dir),
            modes={slot: str(software_modes.get(slot, "follow_hardware")) for slot in SLOTS},
            presets={slot: str(software_presets.get(slot, "default")) for slot in SLOTS},
            visualization_routes={str(key): str(value) for key, value in visualization_routes.items()},
            driver_config={
                str(instance_id): {str(key): str(value) for key, value in fields.items()}
                for instance_id, fields in driver_config.items()
            },
            extra={str(key): str(value) for key, value in (software_extra or {}).items()},
        ),
    )


def build_config_document(
    platform: dict[str, Any],
    platform_cpld: dict[str, str],
    toolchain: dict[str, str],
    hardware: dict[str, str],
    slots: dict[str, str],
    slot_options: dict[str, dict[str, str]],
    slot_cplds: dict[str, str],
    cpld_programmer: dict[str, str],
    axi: dict[str, str],
    software: dict[str, str],
    software_modes: dict[str, str] | None = None,
    software_presets: dict[str, str] | None = None,
    visualization_routes: dict[str, str] | None = None,
    driver_config: dict[str, dict[str, str]] | None = None,
) -> dict[str, Any]:
    source_dir = software.get("source_dir", "")
    modes = software_modes or {slot: software.get(f"{slot}_mode", "follow_hardware") for slot in SLOTS}
    presets = software_presets or {slot: software.get(f"{slot}_preset", "default") for slot in SLOTS}
    routes = visualization_routes or {
        key.removeprefix("visualize_"): value
        for key, value in software.items()
        if key.startswith("visualize_")
    }
    drivers = driver_config or _driver_config_from_flat_software(software)
    mode_and_preset_keys = {f"{slot}_mode" for slot in SLOTS} | {f"{slot}_preset" for slot in SLOTS}
    extra = {
        key: value
        for key, value in software.items()
        if key != "source_dir"
        and key not in mode_and_preset_keys
        and not key.startswith("visualize_")
        and not key.startswith("driver_config_")
    }
    return build_system_config(
        platform,
        platform_cpld,
        toolchain,
        hardware,
        slots,
        slot_options,
        slot_cplds,
        cpld_programmer,
        axi,
        source_dir,
        modes,
        presets,
        routes,
        drivers,
        extra,
    ).to_document()


def _driver_config_from_flat_software(software: dict[str, str]) -> dict[str, dict[str, str]]:
    values: dict[str, dict[str, str]] = {}
    for key, value in software.items():
        if not key.startswith("driver_config_"):
            continue
        remainder = key.removeprefix("driver_config_")
        if remainder.endswith("_mode"):
            instance_id = remainder.removesuffix("_mode")
            values.setdefault(instance_id, {})["mode"] = value
    return values
