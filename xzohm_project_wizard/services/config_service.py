from __future__ import annotations

from typing import Any


def build_config_document(
    platform: dict[str, Any],
    toolchain: dict[str, str],
    slots: dict[str, str],
    slot_options: dict[str, dict[str, str]],
    slot_cplds: dict[str, str],
    cpld_programmer: dict[str, str],
    axi: dict[str, str],
) -> dict[str, Any]:
    return {
        "schema_version": 1,
        "platform": platform.get("id", ""),
        "platform_revision": platform.get("revision", ""),
        "toolchain": toolchain,
        "slots": slots,
        "slot_options": slot_options,
        "slot_cplds": slot_cplds,
        "cpld_programmer": cpld_programmer,
        "axi": axi,
    }
