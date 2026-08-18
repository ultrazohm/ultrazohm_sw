from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Literal

from .paths import DIGITAL_SLOTS, SLOTS


PROJECT_CONFIG_SCHEMA_VERSION = 2


@dataclass(frozen=True)
class PlatformConfig:
    id: str
    revision: str
    cpld: dict[str, str] = field(default_factory=dict)

    @classmethod
    def from_document(cls, document: dict[str, Any]) -> "PlatformConfig":
        return cls(
            id=str(document.get("id", "")),
            revision=str(document.get("revision", "")),
            cpld=_string_dict(document.get("cpld", {})),
        )

    def to_document(self) -> dict[str, Any]:
        return {
            "id": self.id,
            "revision": self.revision,
            "cpld": self.cpld,
        }


@dataclass(frozen=True)
class SlotConfig:
    card_id: str = "empty"
    options: dict[str, str] = field(default_factory=dict)
    cpld_program: str = "none"

    @classmethod
    def from_document(cls, document: dict[str, Any]) -> "SlotConfig":
        return cls(
            card_id=str(document.get("card", "empty")),
            options=_string_dict(document.get("options", {})),
            cpld_program=str(document.get("cpld", "none")),
        )

    def to_document(self) -> dict[str, Any]:
        return {
            "card": self.card_id,
            "options": self.options,
            "cpld": self.cpld_program,
        }


@dataclass(frozen=True)
class SoftwareConfig:
    source_dir: str
    modes: dict[str, str] = field(default_factory=dict)
    presets: dict[str, str] = field(default_factory=dict)
    visualization_routes: dict[str, str] = field(default_factory=dict)
    driver_config: dict[str, dict[str, str]] = field(default_factory=dict)
    extra: dict[str, str] = field(default_factory=dict)

    @classmethod
    def from_document(cls, document: dict[str, Any]) -> "SoftwareConfig":
        return cls(
            source_dir=str(document.get("source_dir", "")),
            modes=_string_dict(document.get("modes", {})),
            presets=_string_dict(document.get("presets", {})),
            visualization_routes=_string_dict(document.get("visualization_routes", {})),
            driver_config=_nested_string_dict(document.get("driver_config", {})),
            extra=_string_dict(document.get("extra", {})),
        )

    def to_document(self) -> dict[str, Any]:
        return {
            "source_dir": self.source_dir,
            "modes": self.modes,
            "presets": self.presets,
            "visualization_routes": self.visualization_routes,
            "driver_config": self.driver_config,
            "extra": self.extra,
        }

    def to_flat_dict(self) -> dict[str, str]:
        values = {"source_dir": self.source_dir}
        values.update(self.extra)
        values.update({f"{slot}_mode": self.modes.get(slot, "follow_hardware") for slot in SLOTS})
        values.update({f"{slot}_preset": self.presets.get(slot, "default") for slot in SLOTS})
        values.update({f"visualize_{signal_id}": route for signal_id, route in self.visualization_routes.items()})
        for instance_id, fields in self.driver_config.items():
            for field_id, value in fields.items():
                values[f"driver_config_{instance_id}_{field_id}"] = value
        return values


@dataclass(frozen=True)
class SystemConfig:
    schema_version: int = PROJECT_CONFIG_SCHEMA_VERSION
    platform_config: PlatformConfig = field(default_factory=lambda: PlatformConfig(id="ultrazohm", revision="Rev06"))
    toolchain: dict[str, str] = field(default_factory=dict)
    hardware: dict[str, str] = field(default_factory=dict)
    slot_configs: dict[str, SlotConfig] = field(default_factory=dict)
    cpld_programmer: dict[str, str] = field(default_factory=dict)
    axi: dict[str, str] = field(default_factory=dict)
    software_config: SoftwareConfig = field(default_factory=lambda: SoftwareConfig(source_dir=""))

    @classmethod
    def from_document(cls, document: dict[str, Any]) -> "SystemConfig":
        if not isinstance(document, dict):
            raise ValueError("Config must be a JSON object.")
        schema_version = int(document.get("schema_version", 0))
        if schema_version != PROJECT_CONFIG_SCHEMA_VERSION:
            raise ValueError(
                f"Unsupported Project Wizard config schema {schema_version}. "
                f"Expected schema {PROJECT_CONFIG_SCHEMA_VERSION}."
            )
        platform = document.get("platform", {})
        if not isinstance(platform, dict):
            raise ValueError("Config field 'platform' must be a JSON object.")
        slots = document.get("slots", {})
        if not isinstance(slots, dict):
            raise ValueError("Config field 'slots' must be a JSON object.")
        software = document.get("software", {})
        if not isinstance(software, dict):
            raise ValueError("Config field 'software' must be a JSON object.")
        return cls(
            schema_version=schema_version,
            platform_config=PlatformConfig.from_document(platform),
            toolchain=_string_dict(document.get("toolchain", {})),
            hardware=_string_dict(document.get("hardware", {})),
            slot_configs={slot: SlotConfig.from_document(slots.get(slot, {})) for slot in SLOTS},
            cpld_programmer=_string_dict(document.get("cpld_programmer", {})),
            axi=_string_dict(document.get("axi", {})),
            software_config=SoftwareConfig.from_document(software),
        )

    def to_document(self) -> dict[str, Any]:
        return {
            "schema_version": self.schema_version,
            "platform": self.platform_config.to_document(),
            "toolchain": self.toolchain,
            "hardware": self.hardware,
            "slots": {slot: self.slot_configs.get(slot, SlotConfig()).to_document() for slot in SLOTS},
            "cpld_programmer": self.cpld_programmer,
            "axi": self.axi,
            "software": self.software_config.to_document(),
        }

    @property
    def platform(self) -> str:
        return self.platform_config.id

    @property
    def platform_revision(self) -> str:
        return self.platform_config.revision

    @property
    def platform_cpld(self) -> dict[str, str]:
        return self.platform_config.cpld

    @property
    def slots(self) -> dict[str, str]:
        return {slot: self.slot_configs.get(slot, SlotConfig()).card_id for slot in SLOTS}

    @property
    def slot_options(self) -> dict[str, dict[str, str]]:
        return {slot: self.slot_configs.get(slot, SlotConfig()).options for slot in SLOTS}

    @property
    def slot_cplds(self) -> dict[str, str]:
        return {
            slot: self.slot_configs.get(slot, SlotConfig()).cpld_program
            for slot in DIGITAL_SLOTS
        }

    @property
    def software(self) -> dict[str, str]:
        return self.software_config.to_flat_dict()

    @property
    def software_modes(self) -> dict[str, str]:
        return {slot: self.software_config.modes.get(slot, "follow_hardware") for slot in SLOTS}

    @property
    def software_presets(self) -> dict[str, str]:
        return {slot: self.software_config.presets.get(slot, "default") for slot in SLOTS}

    @property
    def visualization_routes(self) -> dict[str, str]:
        return self.software_config.visualization_routes

    @property
    def driver_config(self) -> dict[str, dict[str, str]]:
        return self.software_config.driver_config

    @property
    def software_source_dir(self) -> Path:
        return Path(self.software_config.source_dir)


@dataclass(frozen=True)
class ResolvedOptionChoice:
    option_id: str
    choice_id: str
    option: dict[str, Any]
    choice: dict[str, Any]


@dataclass(frozen=True)
class ResolvedSlot:
    name: str
    card_id: str
    card: dict[str, Any] | None
    option_values: dict[str, str] = field(default_factory=dict)
    options: list[ResolvedOptionChoice] = field(default_factory=list)

    @property
    def is_bypass(self) -> bool:
        return self.card_id == "empty"

    @property
    def is_no_adapter_board(self) -> bool:
        return self.card_id == "no_adapter_board"

    @property
    def family(self) -> str:
        return str((self.card or {}).get("family", ""))


@dataclass(frozen=True)
class ResolvedAnalogStream:
    slot: str
    card_id: str
    raw_value_pin: str
    raw_valid_pin: str
    channel_count: int
    sample_width: int
    packed_offset: int


@dataclass(frozen=True)
class ResolvedAnalogDataMover:
    streams: list[ResolvedAnalogStream] = field(default_factory=list)
    minimum_channel_count: int = 2

    @property
    def channel_count(self) -> int:
        if not self.streams:
            return self.minimum_channel_count
        return max(self.minimum_channel_count, sum(stream.channel_count for stream in self.streams))

    @property
    def data_width(self) -> int:
        return self.channel_count * 16


@dataclass(frozen=True)
class ResolvedSystemModel:
    config: SystemConfig
    platform: dict[str, Any] | None
    slots: list[ResolvedSlot]
    analog_datamover: ResolvedAnalogDataMover = field(default_factory=ResolvedAnalogDataMover)

    def slot(self, name: str) -> ResolvedSlot | None:
        return next((slot for slot in self.slots if slot.name == name), None)


@dataclass(frozen=True)
class ValidationIssue:
    severity: Literal["error", "warning", "info"]
    code: str
    message: str
    path: str = ""


def _string_dict(value: Any) -> dict[str, str]:
    if not isinstance(value, dict):
        return {}
    return {str(key): str(item) for key, item in value.items()}


def _nested_string_dict(value: Any) -> dict[str, dict[str, str]]:
    if not isinstance(value, dict):
        return {}
    return {
        str(key): _string_dict(item)
        for key, item in value.items()
        if isinstance(item, dict)
    }
