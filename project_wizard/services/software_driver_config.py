from __future__ import annotations

from .software_models import DriverConfigField


def driver_instance_values(
    instance_id: str,
    fields: list[DriverConfigField],
    driver_config: dict[str, dict[str, str]],
) -> dict[str, str]:
    configured = driver_config.get(instance_id, {})
    if configured.get("mode") != "custom":
        configured = {}
    return {field.id: configured.get(field.id, field.default) for field in fields}
