from __future__ import annotations

from typing import Any


def build_config_document(
    platform: dict[str, Any],
    slots: dict[str, str],
    slot_options: dict[str, dict[str, str]],
    slot_cplds: dict[str, str],
    axi: dict[str, str],
) -> dict[str, Any]:
    return {
        "schema_version": 1,
        "platform": platform.get("id", ""),
        "platform_revision": platform.get("revision", ""),
        "slots": slots,
        "slot_options": slot_options,
        "slot_cplds": slot_cplds,
        "axi": axi,
    }
