from __future__ import annotations

from dataclasses import dataclass, field
from typing import Any, Literal


@dataclass(frozen=True)
class SystemConfig:
    schema_version: int
    platform: str
    platform_revision: str
    platform_cpld: dict[str, str] = field(default_factory=dict)
    toolchain: dict[str, str] = field(default_factory=dict)
    hardware: dict[str, str] = field(default_factory=dict)
    slots: dict[str, str] = field(default_factory=dict)
    slot_options: dict[str, dict[str, str]] = field(default_factory=dict)
    slot_cplds: dict[str, str] = field(default_factory=dict)
    cpld_programmer: dict[str, str] = field(default_factory=dict)
    axi: dict[str, str] = field(default_factory=dict)
    software: dict[str, str] = field(default_factory=dict)

    @classmethod
    def from_document(cls, document: dict[str, Any]) -> "SystemConfig":
        slot_options = document.get("slot_options", {})
        if not isinstance(slot_options, dict):
            slot_options = {}
        return cls(
            schema_version=int(document.get("schema_version", 1)),
            platform=str(document.get("platform", "")),
            platform_revision=str(document.get("platform_revision", "")),
            platform_cpld=_string_dict(document.get("platform_cpld", {})),
            toolchain=_string_dict(document.get("toolchain", {})),
            hardware=_string_dict(document.get("hardware", {})),
            slots=_string_dict(document.get("slots", {})),
            slot_options={
                str(slot): _string_dict(options)
                for slot, options in slot_options.items()
                if isinstance(options, dict)
            },
            slot_cplds=_string_dict(document.get("slot_cplds", {})),
            cpld_programmer=_string_dict(document.get("cpld_programmer", {})),
            axi=_string_dict(document.get("axi", {})),
            software=_string_dict(document.get("software", {})),
        )

    def to_document(self) -> dict[str, Any]:
        return {
            "schema_version": self.schema_version,
            "platform": self.platform,
            "platform_revision": self.platform_revision,
            "platform_cpld": self.platform_cpld,
            "toolchain": self.toolchain,
            "hardware": self.hardware,
            "slots": self.slots,
            "slot_options": self.slot_options,
            "slot_cplds": self.slot_cplds,
            "cpld_programmer": self.cpld_programmer,
            "axi": self.axi,
            "software": self.software,
        }


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
