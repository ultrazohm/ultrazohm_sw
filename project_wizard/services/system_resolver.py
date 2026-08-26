from __future__ import annotations

from typing import Any

from ..models import (
    ResolvedAnalogDataMover,
    ResolvedAnalogStream,
    ResolvedAxiCleanupSlot,
    ResolvedAxiInterconnect,
    ResolvedAxiInterface,
    ResolvedAxiSlot,
    ResolvedOptionChoice,
    ResolvedSlot,
    ResolvedSoftwareDriverInstance,
    ResolvedSystemModel,
    SystemConfig,
    ValidationIssue,
    VisualizationSignal,
)
from ..paths import SLOTS
from ..repositories import CardDatabase
from .visualization_catalog import (
    adc_ltc2311_visualization_signals,
    adc_max11331_visualization_signals,
    dac8831_visualization_signals,
    encoder_visualization_signals,
    incremental_encoder_visualization_signals,
    inverter_adapter_visualization_signals,
    io_card_needs_axi,
    io_card_visualization_signals,
    resolver_ip_visualization_signals,
    resolver_pl_interface_visualization_signals,
    selected_io_card_variant,
    temperature_visualization_signals,
)


class SystemResolver:
    def __init__(self, database: CardDatabase) -> None:
        self.database = database

    def resolve(self, config: SystemConfig) -> ResolvedSystemModel:
        platform = self.database.platform_by_id(config.platform_id)
        slots = [self._resolve_slot(slot_name, config) for slot_name in SLOTS]
        return ResolvedSystemModel(
            config=config,
            platform=platform,
            slots=slots,
            analog_datamover=self._resolve_analog_datamover(slots),
            axi_interconnect=self._resolve_axi_interconnect(config, slots),
            software_driver_instances=self._resolve_software_driver_instances(config, slots),
            available_visualization_signals=self._resolve_visualization_signals(config, slots),
        )

    def validate(self, model: ResolvedSystemModel) -> list[ValidationIssue]:
        issues: list[ValidationIssue] = []
        if model.platform is None:
            issues.append(
                ValidationIssue(
                    severity="error",
                    code="PLATFORM_UNKNOWN",
                    message=f"Unknown platform: {model.config.platform_id}",
                    path="platform",
                )
            )
        for slot in model.slots:
            if slot.card is None and slot.card_id not in {"empty", "no_adapter_board"}:
                issues.append(
                    ValidationIssue(
                        severity="error",
                        code="CARD_UNKNOWN",
                        message=f"{slot.name} uses unknown adapter card '{slot.card_id}'.",
                        path=f"slots.{slot.name}",
                    )
                )
                continue
            if slot.card and slot.name not in slot.card.get("compatible_slots", []):
                issues.append(
                    ValidationIssue(
                        severity="error",
                        code="CARD_SLOT_INCOMPATIBLE",
                        message=f"{slot.card_id} is not compatible with {slot.name}.",
                        path=f"slots.{slot.name}",
                    )
                )
        return issues

    def _resolve_slot(self, slot_name: str, config: SystemConfig) -> ResolvedSlot:
        slot_config = config.slot_configs.get(slot_name)
        card_id = slot_config.card_id if slot_config else "empty"
        card = self.database.card_by_id(card_id)
        option_values = slot_config.options if slot_config else {}
        default_cpld_program = self._default_cpld_program(card, slot_name, option_values)
        return ResolvedSlot(
            name=slot_name,
            card_id=card_id,
            card=card,
            cpld_program=slot_config.cpld_program if slot_config else "none",
            default_cpld_program=default_cpld_program,
            option_values=option_values,
            options=self._resolve_options(card, option_values),
        )

    @classmethod
    def _default_cpld_program(
        cls,
        card: dict[str, Any] | None,
        slot_name: str,
        option_values: dict[str, str],
    ) -> str:
        if not card:
            return "none"
        io_card = card.get("vivado", {}).get("io_card")
        if io_card:
            return cls._io_card_cpld_program(card, option_values)
        by_slot = card.get("slot_cpld_by_slot", {})
        if isinstance(by_slot, dict):
            slot_program = by_slot.get(slot_name)
            if slot_program:
                return str(slot_program)
        return str(card.get("slot_cpld", "none") or "none")

    @staticmethod
    def _io_card_cpld_program(card: dict[str, Any], option_values: dict[str, str]) -> str:
        io_card = card.get("vivado", {}).get("io_card", {})
        variant = selected_io_card_variant(io_card, option_values)
        if variant:
            return str(variant.get("cpld_program", card.get("slot_cpld", "none")) or "none")
        kind = str(io_card.get("kind", ""))
        if kind == "voltage_grouped":
            groups = io_card.get("groups", [])
            parts = []
            for group_index, group in enumerate(groups, start=1):
                width = _config_int(group.get("width", 0), default=0, minimum=0, maximum=30)
                direction = option_values.get(f"direction_group_{group_index}", str(group.get("default", "rx")))
                parts.append(f"{width}{direction if direction in {'tx', 'rx'} else 'rx'}")
            return f"voltage_{'_'.join(parts)}"
        return str(card.get("slot_cpld", "none") or "none")

    @staticmethod
    def _resolve_analog_datamover(slots: list[ResolvedSlot]) -> ResolvedAnalogDataMover:
        streams: list[ResolvedAnalogStream] = []
        packed_offset = 0
        for slot in slots:
            if slot.name not in {"A1", "A2", "A3"}:
                continue
            adc_stream = (slot.card or {}).get("vivado", {}).get("adc_stream", {})
            if not adc_stream:
                continue
            channel_count = int(str(adc_stream.get("channel_count", 8)), 0)
            sample_width = int(str(adc_stream.get("sample_width", 16)), 0)
            raw_value_signal = str(adc_stream.get("raw_value_signal", "{slot}_RAW_Value")).format(
                slot=slot.name,
                slot_index=slot.name[1:],
            )
            raw_valid_signal = str(adc_stream.get("raw_valid_signal", "{slot}_RAW_Valid")).format(
                slot=slot.name,
                slot_index=slot.name[1:],
            )
            streams.append(
                ResolvedAnalogStream(
                    slot=slot.name,
                    card_id=slot.card_id,
                    raw_value_pin=f"uz_analog_adapter/{raw_value_signal}",
                    raw_valid_pin=f"uz_analog_adapter/{raw_valid_signal}",
                    channel_count=channel_count,
                    sample_width=sample_width,
                    packed_offset=packed_offset,
                )
            )
            packed_offset += channel_count
        return ResolvedAnalogDataMover(streams=streams, minimum_channel_count=2)

    def _resolve_axi_interconnect(self, config: SystemConfig, slots: list[ResolvedSlot]) -> ResolvedAxiInterconnect:
        axi_config = dict(self.database.axi_interconnect)
        axi_config.update({key: value for key, value in config.axi.items() if value})
        d_slot_axi = {
            "upstream_smartconnect": axi_config.get(
                "d_upstream_smartconnect",
                axi_config.get("upstream_smartconnect", ""),
            ),
            "clock_pin": axi_config.get("d_clock_pin", axi_config.get("clock_pin", "")),
            "resetn_pin": axi_config.get("d_resetn_pin", axi_config.get("resetn_pin", "")),
            "address_space": axi_config.get("d_address_space", axi_config.get("address_space", "")),
        }
        a_slot_axi = {
            "upstream_smartconnect": axi_config.get("a_upstream_smartconnect", ""),
            "clock_pin": axi_config.get("a_clock_pin", ""),
            "resetn_pin": axi_config.get("a_resetn_pin", ""),
            "address_space": axi_config.get("a_address_space", ""),
        }
        local_name = axi_config.get("local_smartconnect_name", "axi_smartconnect")
        axi_slots: list[ResolvedAxiSlot] = []
        cleanup_slots: list[ResolvedAxiCleanupSlot] = []
        upstream_smartconnects: list[str] = []

        for slot in slots:
            if slot.is_bypass:
                continue
            slot_axi = a_slot_axi if slot.name.startswith("A") else d_slot_axi
            adapter_root_hier = (slot.card or {}).get("vivado", {}).get("adapter_parent_hier", _adapter_root_hier(slot.name))
            local_smartconnect_path = f"{adapter_root_hier}/{slot.name}_adapter/{local_name}"
            if slot.is_no_adapter_board:
                cleanup_slots.append(
                    ResolvedAxiCleanupSlot(
                        slot=slot.name,
                        adapter_root_hier=_adapter_root_hier(slot.name),
                        local_smartconnect_path=f"{_adapter_root_hier(slot.name)}/{slot.name}_adapter/{local_name}",
                        upstream_smartconnect=slot_axi["upstream_smartconnect"],
                    )
                )
                continue
            if not slot.card:
                continue
            interfaces = self._axi_interfaces_for_slot(slot)
            if not interfaces:
                cleanup_slots.append(
                    ResolvedAxiCleanupSlot(
                        slot=slot.name,
                        adapter_root_hier=adapter_root_hier,
                        local_smartconnect_path=local_smartconnect_path,
                        upstream_smartconnect=slot_axi["upstream_smartconnect"],
                    )
                )
                continue
            axi_slot = ResolvedAxiSlot(
                slot=slot.name,
                adapter_root_hier=adapter_root_hier,
                adapter_hier_path=f"{adapter_root_hier}/{slot.name}_adapter",
                local_smartconnect_path=local_smartconnect_path,
                adapter_clock_pin=(slot.card or {}).get("vivado", {}).get("adapter_clock_pin", "clk"),
                adapter_resetn_pin=(slot.card or {}).get("vivado", {}).get("adapter_resetn_pin", "resetn"),
                upstream_smartconnect=slot_axi["upstream_smartconnect"],
                clock_pin=slot_axi["clock_pin"],
                resetn_pin=slot_axi["resetn_pin"],
                address_space=slot_axi["address_space"],
                axi_interfaces=interfaces,
            )
            axi_slots.append(axi_slot)
            if slot_axi["upstream_smartconnect"] and slot_axi["upstream_smartconnect"] not in upstream_smartconnects:
                upstream_smartconnects.append(slot_axi["upstream_smartconnect"])

        for cleanup_slot in cleanup_slots:
            upstream = cleanup_slot.upstream_smartconnect
            if upstream and upstream not in upstream_smartconnects:
                upstream_smartconnects.append(upstream)

        context = {
            "upstream_smartconnect": d_slot_axi["upstream_smartconnect"],
            "clock_pin": d_slot_axi["clock_pin"],
            "resetn_pin": d_slot_axi["resetn_pin"],
            "address_space": d_slot_axi["address_space"],
            "d_upstream_smartconnect": d_slot_axi["upstream_smartconnect"],
            "d_clock_pin": d_slot_axi["clock_pin"],
            "d_resetn_pin": d_slot_axi["resetn_pin"],
            "d_address_space": d_slot_axi["address_space"],
            "a_upstream_smartconnect": axi_config.get("a_upstream_smartconnect", ""),
            "a_clock_pin": axi_config.get("a_clock_pin", ""),
            "a_resetn_pin": axi_config.get("a_resetn_pin", ""),
            "a_address_space": axi_config.get("a_address_space", ""),
            "local_smartconnect_vlnv": axi_config.get("local_smartconnect_vlnv", "xilinx.com:ip:smartconnect"),
            "has_stale_axi_cleanup_slots": bool(cleanup_slots),
            "stale_axi_cleanup_slots": [
                {
                    "slot": cleanup_slot.slot,
                    "adapter_root_hier": cleanup_slot.adapter_root_hier,
                    "local_smartconnect_path": cleanup_slot.local_smartconnect_path,
                    "upstream_smartconnect": cleanup_slot.upstream_smartconnect,
                }
                for cleanup_slot in cleanup_slots
            ],
            "has_axi": bool(axi_slots),
            "axi_slots": [
                {
                    "slot": axi_slot.slot,
                    "slot_lower": axi_slot.slot_lower,
                    "adapter_root_hier": axi_slot.adapter_root_hier,
                    "adapter_hier_path": axi_slot.adapter_hier_path,
                    "local_smartconnect_path": axi_slot.local_smartconnect_path,
                    "adapter_clock_pin": axi_slot.adapter_clock_pin,
                    "adapter_resetn_pin": axi_slot.adapter_resetn_pin,
                    "upstream_smartconnect": axi_slot.upstream_smartconnect,
                    "clock_pin": axi_slot.clock_pin,
                    "resetn_pin": axi_slot.resetn_pin,
                    "address_space": axi_slot.address_space,
                    "interface_count": len(axi_slot.axi_interfaces),
                    "axi_interfaces": [
                        {
                            "name": interface.name,
                            "path": interface.path,
                            "addr_seg": interface.addr_seg,
                            "index": interface.index,
                        }
                        for interface in axi_slot.axi_interfaces
                    ],
                }
                for axi_slot in axi_slots
            ],
            "axi_connections": [
                {
                    "slot": axi_slot.slot,
                    "local_smartconnect_path": axi_slot.local_smartconnect_path,
                    "index": interface.index,
                    "path": interface.path,
                    "addr_seg": interface.addr_seg,
                    "address_space": axi_slot.address_space,
                    "address_assignment_command": _address_assignment_command(axi_slot.address_space, interface.addr_seg),
                }
                for axi_slot in axi_slots
                for interface in axi_slot.axi_interfaces
            ],
            "has_upstream_smartconnects": bool(upstream_smartconnects),
            "upstream_smartconnects": [{"path": smartconnect} for smartconnect in upstream_smartconnects],
        }
        return ResolvedAxiInterconnect(context=context, axi_slots=axi_slots, stale_cleanup_slots=cleanup_slots)

    def _axi_interfaces_for_slot(self, slot: ResolvedSlot) -> list[ResolvedAxiInterface]:
        if not slot.card:
            return []
        slot_index = slot.name[1:]
        if slot.card_id == "uz_d_resolver":
            interfaces = self._resolver_axi_interfaces(slot)
        elif slot.card_id == "uz_d_incremental_encoder":
            interfaces = self._incremental_encoder_axi_interfaces(slot)
        elif slot.card.get("vivado", {}).get("io_card"):
            if not io_card_needs_axi(slot.card, slot.option_values):
                interfaces = []
            else:
                slot_lower = slot.name.lower()
                interfaces = [
                    ResolvedAxiInterface(
                        name="S_AXI",
                        path=f"uz_digital_adapter/{slot.name}_adapter/axi_gpio_{slot_lower}/S_AXI",
                        addr_seg=f"uz_digital_adapter/{slot.name}_adapter/axi_gpio_{slot_lower}/S_AXI/Reg",
                    )
                ]
        else:
            interfaces = _format_axi_interfaces(slot.name, slot_index, slot.card.get("vivado", {}).get("axi_interfaces", []))
            for option in slot.card.get("options", []):
                selected_choice = next((choice.choice for choice in slot.options if choice.option_id == option.get("id", "")), None)
                if not selected_choice or selected_choice.get("id") == "none":
                    continue
                interfaces.extend(
                    _format_axi_interfaces(
                        slot.name,
                        slot_index,
                        selected_choice.get("vivado", {}).get("axi_interfaces", []),
                        option_id=option.get("id", ""),
                        choice_id=selected_choice.get("id", ""),
                    )
                )
        return [
            ResolvedAxiInterface(
                name=interface.name,
                path=interface.path,
                addr_seg=interface.addr_seg,
                index=index,
            )
            for index, interface in enumerate(interfaces)
        ]

    @staticmethod
    def _incremental_encoder_axi_interfaces(slot: ResolvedSlot) -> list[ResolvedAxiInterface]:
        interfaces: list[ResolvedAxiInterface] = []
        slot_lower = slot.name.lower()
        for channel_index in range(1, 4):
            if not _incremental_encoder_enabled(slot.option_values, channel_index):
                continue
            interfaces.append(
                ResolvedAxiInterface(
                    name="AXI4_Lite",
                    path=f"uz_digital_adapter/{slot.name}_adapter/incremental_encoder_{slot_lower}_{channel_index}/AXI4_Lite",
                    addr_seg=(
                        f"uz_digital_adapter/{slot.name}_adapter/incremental_encoder_{slot_lower}_{channel_index}/"
                        "AXI4_Lite/reg0"
                    ),
                )
            )
        return interfaces

    @staticmethod
    def _resolver_axi_interfaces(slot: ResolvedSlot) -> list[ResolvedAxiInterface]:
        interfaces: list[ResolvedAxiInterface] = []
        for channel_index in range(1, _resolver_channel_count(slot.name) + 1):
            interfaces.append(
                ResolvedAxiInterface(
                    name="s00_axi",
                    path=f"uz_digital_adapter/{slot.name}_adapter/resolver_ip_{slot.name.lower()}_{channel_index}/s00_axi",
                    addr_seg=(
                        f"uz_digital_adapter/{slot.name}_adapter/resolver_ip_{slot.name.lower()}_{channel_index}/s00_axi/reg0"
                    ),
                )
            )
            if _resolver_pl_interface_enabled(slot.option_values, channel_index):
                interfaces.append(
                    ResolvedAxiInterface(
                        name="AXI4_Lite",
                        path=(
                            f"uz_digital_adapter/{slot.name}_adapter/"
                            f"resolver_pl_interface_{slot.name.lower()}_{channel_index}/AXI4_Lite"
                        ),
                        addr_seg=(
                            f"uz_digital_adapter/{slot.name}_adapter/"
                            f"resolver_pl_interface_{slot.name.lower()}_{channel_index}/AXI4_Lite/reg0"
                        ),
                    )
                )
        return interfaces

    @staticmethod
    def _resolve_options(card: dict[str, Any] | None, option_values: dict[str, str]) -> list[ResolvedOptionChoice]:
        if not card:
            return []
        resolved = []
        for option in card.get("options", []):
            option_id = str(option.get("id", ""))
            selected_choice_id = option_values.get(option_id, str(option.get("default", "")))
            choice = next(
                (candidate for candidate in option.get("choices", []) if candidate.get("id") == selected_choice_id),
                None,
            )
            if choice is None and option.get("choices"):
                choice = option["choices"][0]
            if choice is None:
                continue
            resolved.append(
                ResolvedOptionChoice(
                    option_id=option_id,
                    choice_id=str(choice.get("id", "")),
                    option=option,
                    choice=choice,
                )
            )
        return resolved

    def _resolve_software_driver_instances(
        self,
        config: SystemConfig,
        slots: list[ResolvedSlot],
    ) -> list[ResolvedSoftwareDriverInstance]:
        instances: list[ResolvedSoftwareDriverInstance] = []
        pwm_2l_instance_count = _config_int(config.hardware.get("pwm_2l_instances", "4"), default=4, minimum=1, maximum=10)
        pwm_3l_enabled = _config_int(config.hardware.get("pwm_3l_instances", "1"), default=1, minimum=0, maximum=1) > 0
        for index in range(pwm_2l_instance_count):
            instances.append(
                ResolvedSoftwareDriverInstance(
                    id=f"pwm_2l_{index}",
                    slot="PWM",
                    label=f"2L PWM instance {index}",
                    driver="pwm_2l",
                    driver_definition_id="pwm_2l",
                )
            )
            instances.append(
                ResolvedSoftwareDriverInstance(
                    id=f"deadtime_2l_{index}",
                    slot="PWM",
                    label=f"2L deadtime instance {index}",
                    driver="deadtime_2l",
                    driver_definition_id="deadtime_2l",
                )
            )
        if pwm_3l_enabled:
            instances.append(
                ResolvedSoftwareDriverInstance(
                    id="pwm_3l_0",
                    slot="PWM",
                    label="3L PWM instance 0",
                    driver="pwm_3l",
                    driver_definition_id="pwm_3l",
                )
            )
        for slot in slots:
            card_id = slot.card_id if config.software_modes.get(slot.name, "follow_hardware") == "follow_hardware" else "empty"
            slot_lower = slot.name.lower()
            if card_id == "uz_d_temperature_ltc2983":
                preset = config.software_presets.get(slot.name, "default")
                instances.append(
                    ResolvedSoftwareDriverInstance(
                        id=f"{slot_lower}_temperature",
                        slot=slot.name,
                        label=f"{slot.name} temperature card",
                        driver="temperature",
                        driver_definition_id="temperature_card",
                        preset=preset,
                    )
                )
            elif card_id == "analog_ltc2311_16":
                instances.append(_software_instance(slot.name, "adc_ltc2311", "ADC LTC2311", "uz_adc_ltc2311"))
            elif card_id == "analog_max11331":
                instances.append(_software_instance(slot.name, "adc_max11331", "ADC MAX11331", "uz_adc_max11331"))
            elif card_id == "analog_dac8831":
                instances.append(_software_instance(slot.name, "dac8831", "DAC8831", "uz_dac_interface"))
            elif card_id == "uz_d_inverter_adapter":
                instances.append(_software_instance(slot.name, "inverter_adapter", "inverter adapter", "uz_inverter_adapter"))
            elif card_id == "uz_d_incremental_encoder":
                for channel_index in range(1, 4):
                    if not _incremental_encoder_enabled(slot.option_values, channel_index):
                        continue
                    instances.append(
                        ResolvedSoftwareDriverInstance(
                            id=f"{slot_lower}_incremental_encoder_{channel_index}",
                            slot=slot.name,
                            label=f"{slot.name} incremental encoder channel {channel_index}",
                            driver="incremental_encoder",
                            driver_definition_id="uz_incrementalEncoder",
                        )
                    )
            elif card_id == "uz_d_resolver":
                for channel_index in range(1, _resolver_channel_count(slot.name) + 1):
                    instances.append(
                        ResolvedSoftwareDriverInstance(
                            id=f"{slot_lower}_resolver_ip_{channel_index}",
                            slot=slot.name,
                            label=f"{slot.name} resolver IP channel {channel_index}",
                            driver="resolver_ip",
                            driver_definition_id="uz_resolverIP",
                        )
                    )
                    if _resolver_pl_interface_enabled(slot.option_values, channel_index):
                        instances.append(
                            ResolvedSoftwareDriverInstance(
                                id=f"{slot_lower}_resolver_pl_interface_{channel_index}",
                                slot=slot.name,
                                label=f"{slot.name} resolver PL interface channel {channel_index}",
                                driver="resolver_pl_interface",
                                driver_definition_id="uz_resolver_pl_interface",
                            )
                        )
            elif card_id in {"uz_d_optical_io", "uz_d_voltage_3v3_5v"}:
                if io_card_needs_axi(slot.card or {}, slot.option_values):
                    instances.append(_software_instance(slot.name, "axi_gpio", "AXI GPIO IO card", "uz_axi_gpio"))
            elif card_id == "uz_d_absolute_encoder":
                for channel_index in range(1, 4):
                    interface = slot.option_values.get(f"channel_{channel_index}", "none")
                    if interface == "endat":
                        instances.append(
                            ResolvedSoftwareDriverInstance(
                                id=f"{slot_lower}_channel_{channel_index}_endat",
                                slot=slot.name,
                                label=f"{slot.name} channel {channel_index} EnDat",
                                driver="endat",
                                driver_definition_id="uz_endat_interface",
                            )
                        )
                    elif interface == "ssi":
                        instances.append(
                            ResolvedSoftwareDriverInstance(
                                id=f"{slot_lower}_channel_{channel_index}_ssi",
                                slot=slot.name,
                                label=f"{slot.name} channel {channel_index} SSI",
                                driver="ssi",
                                driver_definition_id="uz_ssi_interface",
                            )
                        )
        return instances

    @staticmethod
    def _resolve_visualization_signals(
        config: SystemConfig,
        slots: list[ResolvedSlot],
    ) -> list[VisualizationSignal]:
        signals: list[VisualizationSignal] = []
        for slot in slots:
            card_id = slot.card_id if config.software_modes.get(slot.name, "follow_hardware") == "follow_hardware" else "empty"
            slot_lower = slot.name.lower()
            if card_id == "analog_ltc2311_16":
                signals.extend(adc_ltc2311_visualization_signals(slot_lower))
            elif card_id == "analog_max11331":
                signals.extend(adc_max11331_visualization_signals(slot_lower))
            elif card_id == "analog_dac8831":
                signals.extend(dac8831_visualization_signals(slot_lower))
            elif card_id == "uz_d_inverter_adapter":
                signals.extend(inverter_adapter_visualization_signals(slot_lower))
            elif card_id == "uz_d_temperature_ltc2983":
                signals.extend(temperature_visualization_signals(slot_lower, config.software_presets.get(slot.name, "default")))
            elif card_id == "uz_d_incremental_encoder":
                for channel_index in range(1, 4):
                    if not _incremental_encoder_enabled(slot.option_values, channel_index):
                        continue
                    signals.extend(incremental_encoder_visualization_signals(slot_lower, channel_index))
            elif card_id == "uz_d_resolver":
                for channel_index in range(1, _resolver_channel_count(slot.name) + 1):
                    if _resolver_pl_interface_enabled(slot.option_values, channel_index):
                        signals.extend(resolver_pl_interface_visualization_signals(slot_lower, channel_index))
                    else:
                        signals.extend(resolver_ip_visualization_signals(slot_lower, channel_index))
            elif (slot.card or {}).get("vivado", {}).get("io_card"):
                if io_card_needs_axi(slot.card or {}, slot.option_values):
                    signals.extend(io_card_visualization_signals(slot_lower, slot.card or {}, slot.option_values))
            elif card_id == "uz_d_absolute_encoder":
                for channel_index in range(1, 4):
                    interface = slot.option_values.get(f"channel_{channel_index}", "none")
                    if interface == "endat":
                        signals.extend(encoder_visualization_signals("endat", "endat_encoder", slot_lower, channel_index))
                    elif interface == "ssi":
                        signals.extend(encoder_visualization_signals("ssi", "ssi_encoder", slot_lower, channel_index))
        return signals


def _config_int(value: Any, default: int, minimum: int, maximum: int) -> int:
    try:
        parsed = int(str(value).replace("U", ""), 0)
    except (TypeError, ValueError):
        parsed = default
    return max(minimum, min(maximum, parsed))


def _adapter_root_hier(slot: str) -> str:
    return "uz_analog_adapter" if slot.startswith("A") else "uz_digital_adapter"


def _format_axi_interfaces(
    slot: str,
    slot_index: str,
    interfaces: list[dict[str, Any]],
    option_id: str = "",
    choice_id: str = "",
) -> list[ResolvedAxiInterface]:
    formatted: list[ResolvedAxiInterface] = []
    for interface in interfaces:
        context = {
            "slot": slot,
            "slot_lower": slot.lower(),
            "slot_index": slot_index,
            "option_id": option_id,
            "choice_id": choice_id,
        }
        formatted.append(
            ResolvedAxiInterface(
                name=str(interface.get("name", "axi")),
                path=str(interface.get("path_template", "")).format(**context),
                addr_seg=str(interface.get("addr_seg_template", "")).format(**context),
            )
        )
    return formatted


def _address_assignment_command(address_space: str, addr_seg: str) -> str:
    return f"assign_bd_address -target_address_space {address_space} [get_bd_addr_segs {addr_seg}] -force"


def _software_instance(
    slot: str,
    driver: str,
    label_suffix: str,
    driver_definition_id: str,
) -> ResolvedSoftwareDriverInstance:
    return ResolvedSoftwareDriverInstance(
        id=f"{slot.lower()}_{driver}",
        slot=slot,
        label=f"{slot} {label_suffix}",
        driver=driver,
        driver_definition_id=driver_definition_id,
    )


def _resolver_channel_count(slot: str) -> int:
    return 2 if slot == "D5" else 3


def _resolver_pl_interface_enabled(option_values: dict[str, str], channel: int) -> bool:
    return option_values.get(f"enable_pl_interface_ch{channel}", "true") == "true"


def _incremental_encoder_enabled(option_values: dict[str, str], channel: int) -> bool:
    return option_values.get(f"channel_{channel}", "incremental_encoder") == "incremental_encoder"
