from __future__ import annotations

import re
from dataclasses import dataclass, field
from functools import lru_cache
from pathlib import Path

from ..repositories import CardDatabase
from ..template_renderer import SimpleTemplateRenderer


SLOTS = ["A1", "A2", "A3", "D1", "D2", "D3", "D4", "D5"]

GLOBAL_DATA_MARKERS = {
    "actual_values": (
        "/* Project Wizard BEGIN: actualValues */",
        "/* Project Wizard END: actualValues */",
    ),
    "objects": (
        "/* Project Wizard BEGIN: objects */",
        "/* Project Wizard END: objects */",
    ),
}

FILE_MARKERS = {
    "adc_readout_definitions": (
        "/* Project Wizard BEGIN: adc_readout_definitions */",
        "/* Project Wizard END: adc_readout_definitions */",
    ),
    "adc_readout": (
        "/* Project Wizard BEGIN: adc_readout */",
        "/* Project Wizard END: adc_readout */",
    ),
    "main_init_ip_cores": (
        "/* Project Wizard BEGIN: init_ip_cores */",
        "/* Project Wizard END: init_ip_cores */",
    ),
    "javascope_observables": (
        "/* Project Wizard BEGIN: javascope_observables */",
        "/* Project Wizard END: javascope_observables */",
    ),
    "javascope_observable_pointers": (
        "/* Project Wizard BEGIN: javascope_observable_pointers */",
        "/* Project Wizard END: javascope_observable_pointers */",
    ),
}


@dataclass
class SlotSoftwareContent:
    header_includes: list[str] = field(default_factory=list)
    header_prototypes: list[str] = field(default_factory=list)
    source_definitions: list[str] = field(default_factory=list)


@dataclass
class SoftwarePlan:
    slot_content: dict[str, SlotSoftwareContent]
    actual_values: list[str]
    objects: list[str]
    adc_readout_definitions: list[str]
    adc_readout: list[str]
    main_init: list[str]
    isr_control_by_slot: dict[str, list[str]]
    javascope_observable_enums: list[str]
    javascope_observable_pointers: list[str]
    available_visualization_signals: list["VisualizationSignal"]
    instance_counts: dict[str, int]
    warnings: list[str]


@dataclass(frozen=True)
class SoftwareGenerationResult:
    written_files: list[Path]
    patched_files: list[Path]
    warnings: list[str]


@dataclass(frozen=True)
class VisualizationSignal:
    signal_id: str
    slot: str
    label: str
    enum_name: str
    pointer_expression: str


@dataclass(frozen=True)
class DriverConfigField:
    id: str
    label: str
    default: str
    multiline: bool = False


@dataclass(frozen=True)
class DriverConfigInstance:
    id: str
    slot: str
    label: str
    driver: str
    fields: list[DriverConfigField]


class MarkerError(ValueError):
    pass


class SoftwareGenerator:
    def __init__(self, database: CardDatabase) -> None:
        self.database = database
        self.renderer = SimpleTemplateRenderer()

    def driver_definition(self, driver_id: str) -> dict[str, object]:
        definition = self.database.software_driver_by_id(driver_id)
        if definition is None:
            raise ValueError(f"Software driver definition not found: {driver_id}")
        return definition

    def driver_template(self, driver_id: str, template_kind: str) -> str:
        templates = self.driver_definition(driver_id).get("templates", {})
        if not isinstance(templates, dict) or not templates.get(template_kind):
            raise ValueError(f"Software driver '{driver_id}' has no {template_kind} template.")
        return str(templates[template_kind])

    def driver_config_fields(self, driver_id: str, preset: str = "default") -> list[DriverConfigField]:
        raw_fields = self.driver_definition(driver_id).get("config_fields", [])
        if not isinstance(raw_fields, list):
            raise ValueError(f"Software driver '{driver_id}' field definition must be a list.")
        fields: list[DriverConfigField] = []
        for raw_field in raw_fields:
            if not isinstance(raw_field, dict):
                continue
            default = str(raw_field.get("default", ""))
            if default == "{{ temperature_configdata_a }}":
                default = temperature_configdata_a(preset)
            fields.append(
                DriverConfigField(
                    id=str(raw_field.get("id", "")),
                    label=str(raw_field.get("label", raw_field.get("id", ""))),
                    default=default,
                    multiline=bool(raw_field.get("multiline", False)),
                )
            )
        return fields

    def build_plan(
        self,
        source_dir: Path,
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        software_modes: dict[str, str] | None = None,
        software_presets: dict[str, str] | None = None,
        visualization_signals: set[str] | list[str] | None = None,
        driver_config: dict[str, dict[str, str]] | None = None,
    ) -> SoftwarePlan:
        software_modes = software_modes or {}
        software_presets = software_presets or {}
        driver_config = driver_config or {}
        selected_visualization_signals = set(visualization_signals or [])
        slot_content = {slot: SlotSoftwareContent() for slot in SLOTS}
        actual_values: list[str] = []
        objects: list[str] = []
        adc_readout_definitions: list[str] = []
        adc_readout: list[str] = []
        main_init: list[str] = []
        isr_control_by_slot: dict[str, list[str]] = {slot: [] for slot in SLOTS}
        available_visualization_signals: list[VisualizationSignal] = []
        warnings: list[str] = []
        temperature_instances = 0
        adc_ltc2311_instances = 0
        endat_instances = 0
        ssi_instances = 0

        for slot in SLOTS:
            mode = software_modes.get(slot, "follow_hardware")
            card_id = assignments.get(slot, "empty") if mode == "follow_hardware" else "empty"
            if card_id == "analog_ltc2311_16":
                adc_ltc2311_instances += 1
                context = self._adc_ltc2311_context(
                    slot,
                    source_dir,
                    driver_instance_values(
                        f"{slot.lower()}_adc_ltc2311", self.driver_config_fields("uz_adc_ltc2311"), driver_config
                    ),
                )
                warnings.extend(context.pop("warnings"))
                header_includes, header_prototypes = split_header_template(
                    self.renderer.render_file(self.driver_template("uz_adc_ltc2311", "header"), context)
                )
                slot_content[slot].header_includes.extend(header_includes)
                slot_content[slot].header_prototypes.extend(header_prototypes)
                slot_content[slot].source_definitions.append(
                    self.renderer.render_file(self.driver_template("uz_adc_ltc2311", "source"), context).rstrip()
                )
                objects.append(f"\tuz_adcLtc2311_t* adc_ltc2311_{context['slot_lower']};")
                main_init.append(
                    f"\t\t\tGlobal_Data.objects.adc_ltc2311_{context['slot_lower']} = initialize_adc_ltc2311_{context['slot_lower']}();"
                )
                actual_values.extend(adc_ltc2311_actual_values(str(context["slot_lower"])))
                isr_control_by_slot[slot].extend(adc_ltc2311_isr_lines(slot, context))
                available_visualization_signals.extend(adc_ltc2311_visualization_signals(str(context["slot_lower"])))
            elif card_id == "uz_d_temperature_ltc2983":
                temperature_instances += 1
                preset = software_presets.get(slot, "default")
                context = self._temperature_context(
                    slot,
                    source_dir,
                    preset,
                    driver_instance_values(
                        f"{slot.lower()}_temperature", self.driver_config_fields("temperature_card", preset), driver_config
                    ),
                )
                warnings.extend(context.pop("warnings"))
                header_includes, header_prototypes = split_header_template(
                    self.renderer.render_file(self.driver_template("temperature_card", "header"), context)
                )
                slot_content[slot].header_includes.extend(header_includes)
                slot_content[slot].header_prototypes.extend(header_prototypes)
                slot_content[slot].source_definitions.append(
                    self.renderer.render_file(self.driver_template("temperature_card", "source"), context).rstrip()
                )
                actual_values.extend(
                    [
                        f"\tuz_temperaturecard_OneGroup temperature_card_{context['slot_lower']}_channel_A;",
                        f"\tuz_temperaturecard_OneGroup temperature_card_{context['slot_lower']}_channel_B;",
                        f"\tuz_temperaturecard_OneGroup temperature_card_{context['slot_lower']}_channel_C;",
                    ]
                )
                objects.append(f"\tuz_temperaturecard_t* temperature_card_{context['slot_lower']};")
                main_init.extend(
                    [
                        f"\t\t\tGlobal_Data.objects.temperature_card_{context['slot_lower']} = initialize_temperature_card_{context['slot_lower']}();",
                        f"\t\t\tuz_TempCard_IF_Reset(Global_Data.objects.temperature_card_{context['slot_lower']});",
                        f"\t\t\tuz_TempCard_IF_Start(Global_Data.objects.temperature_card_{context['slot_lower']});",
                    ]
                )
                isr_control_by_slot[slot].extend(
                    [
                        f"    uz_TempCard_IF_MeasureTemps_cyclic(Global_Data.objects.temperature_card_{context['slot_lower']});",
                        (
                            f"    Global_Data.av.temperature_card_{context['slot_lower']}_channel_A = "
                            f"uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_{context['slot_lower']}, 'A');"
                        ),
                        (
                            f"    Global_Data.av.temperature_card_{context['slot_lower']}_channel_B = "
                            f"uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_{context['slot_lower']}, 'B');"
                        ),
                        (
                            f"    Global_Data.av.temperature_card_{context['slot_lower']}_channel_C = "
                            f"uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_{context['slot_lower']}, 'C');"
                        ),
                    ]
                )
                available_visualization_signals.extend(temperature_visualization_signals(str(context["slot_lower"]), preset))
            elif card_id == "uz_d_absolute_encoder":
                for channel_index in range(1, 4):
                    option_id = f"channel_{channel_index}"
                    interface = option_values.get(slot, {}).get(option_id, "none")
                    if interface == "endat":
                        endat_instances += 1
                        context = self._serial_encoder_context(
                            slot,
                            channel_index,
                            "endat",
                            source_dir,
                            driver_instance_values(
                                f"{slot.lower()}_channel_{channel_index}_endat",
                                self.driver_config_fields("uz_endat_interface"),
                                driver_config,
                            ),
                        )
                        warnings.extend(context.pop("warnings"))
                        header_includes, header_prototypes = split_header_template(
                            self.renderer.render_file(self.driver_template("uz_endat_interface", "header"), context)
                        )
                        slot_content[slot].header_includes.extend(header_includes)
                        slot_content[slot].header_prototypes.extend(header_prototypes)
                        slot_content[slot].source_definitions.append(
                            self.renderer.render_file(self.driver_template("uz_endat_interface", "source"), context).rstrip()
                        )
                        objects.append(f"\tuz_endat_interface_t* endat_encoder_{context['slot_lower']}_{channel_index};")
                        actual_values.extend(encoder_actual_values("endat_encoder", str(context["slot_lower"]), channel_index))
                        main_init.extend(
                            [
                                f"\t\t\tGlobal_Data.objects.endat_encoder_{context['slot_lower']}_{channel_index} = initialize_endat_encoder_{context['slot_lower']}_{channel_index}();",
                                f"\t\t\tuz_endat_interface_set_mode_command(Global_Data.objects.endat_encoder_{context['slot_lower']}_{channel_index}, uz_endat_interface_send_position);",
                                f"\t\t\tuz_endat_interface_enable_ip(Global_Data.objects.endat_encoder_{context['slot_lower']}_{channel_index}, true);",
                            ]
                        )
                        isr_control_by_slot[slot].extend(
                            encoder_isr_lines("endat", "endat_encoder", str(context["slot_lower"]), channel_index)
                        )
                        available_visualization_signals.extend(
                            encoder_visualization_signals("endat", "endat_encoder", str(context["slot_lower"]), channel_index)
                        )
                    elif interface == "ssi":
                        ssi_instances += 1
                        context = self._serial_encoder_context(
                            slot,
                            channel_index,
                            "ssi",
                            source_dir,
                            driver_instance_values(
                                f"{slot.lower()}_channel_{channel_index}_ssi",
                                self.driver_config_fields("uz_ssi_interface"),
                                driver_config,
                            ),
                        )
                        warnings.extend(context.pop("warnings"))
                        header_includes, header_prototypes = split_header_template(
                            self.renderer.render_file(self.driver_template("uz_ssi_interface", "header"), context)
                        )
                        slot_content[slot].header_includes.extend(header_includes)
                        slot_content[slot].header_prototypes.extend(header_prototypes)
                        slot_content[slot].source_definitions.append(
                            self.renderer.render_file(self.driver_template("uz_ssi_interface", "source"), context).rstrip()
                        )
                        objects.append(f"\tuz_ssi_interface_t* ssi_encoder_{context['slot_lower']}_{channel_index};")
                        actual_values.extend(encoder_actual_values("ssi_encoder", str(context["slot_lower"]), channel_index))
                        main_init.extend(
                            [
                                f"\t\t\tGlobal_Data.objects.ssi_encoder_{context['slot_lower']}_{channel_index} = initialize_ssi_encoder_{context['slot_lower']}_{channel_index}();",
                                f"\t\t\tuz_ssi_interface_enable_ip(Global_Data.objects.ssi_encoder_{context['slot_lower']}_{channel_index}, true);",
                            ]
                        )
                        isr_control_by_slot[slot].extend(
                            encoder_isr_lines("ssi", "ssi_encoder", str(context["slot_lower"]), channel_index)
                        )
                        available_visualization_signals.extend(
                            encoder_visualization_signals("ssi", "ssi_encoder", str(context["slot_lower"]), channel_index)
                        )
            elif card_id not in {"empty", "no_adapter_board"}:
                card = self.database.card_by_id(card_id) or {}
                driver = card.get("vitis", {}).get("driver", "")
                if driver:
                    warnings.append(f"{slot}: software integration for driver '{driver}' is not implemented yet.")

        if adc_ltc2311_instances:
            adc_readout_definitions.append("static uz_array_int16_t adc_ltc2311_data;")
            adc_readout.append("    adc_ltc2311_data = uz_dataMover_update_buffer_and_get_data();")

        selected_signals = [
            signal for signal in available_visualization_signals if signal.signal_id in selected_visualization_signals
        ]
        return SoftwarePlan(
            slot_content=slot_content,
            actual_values=actual_values,
            objects=objects,
            adc_readout_definitions=adc_readout_definitions,
            adc_readout=adc_readout,
            main_init=main_init,
            isr_control_by_slot=isr_control_by_slot,
            javascope_observable_enums=[f"\t{signal.enum_name}," for signal in selected_signals],
            javascope_observable_pointers=[
                f"\tjs_ch_observable[{signal.enum_name}] = {signal.pointer_expression};" for signal in selected_signals
            ],
            available_visualization_signals=available_visualization_signals,
            instance_counts={
                "UZ_ADCLTC2311_MAX_INSTANCES": adc_ltc2311_instances,
                "UZ_TEMPERATURE_CARD_MAX_INSTANCES": temperature_instances,
                "UZ_ENDAT_INTERFACE_MAX_INSTANCES": endat_instances,
                "UZ_SSI_INTERFACE_MAX_INSTANCES": ssi_instances,
            },
            warnings=warnings,
        )

    def preview(
        self,
        source_dir: Path,
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        software_modes: dict[str, str] | None = None,
        software_presets: dict[str, str] | None = None,
        visualization_signals: set[str] | list[str] | None = None,
        driver_config: dict[str, dict[str, str]] | None = None,
    ) -> str:
        plan = self.build_plan(
            source_dir, assignments, option_values, software_modes, software_presets, visualization_signals, driver_config
        )
        lines = [
            "Software generation preview",
            f"Source directory: {source_dir}",
            "",
            "Slot files to update:",
        ]
        updated_slots = [slot for slot, content in plan.slot_content.items() if content.header_includes or content.source_definitions]
        if updated_slots:
            for slot in updated_slots:
                slot_lower = slot.lower()
                lines.append(f"- include/{slot_lower}_adapter_init.h")
                lines.append(f"- hw_init/{slot_lower}_adapter_init.c")
        else:
            lines.append("- none")

        lines.extend(["", "globalData.h marker content:", "actualValues:"])
        lines.extend(f"  {entry.strip()}" for entry in plan.actual_values) if plan.actual_values else lines.append("  none")
        lines.append("objects:")
        lines.extend(f"  {entry.strip()}" for entry in plan.objects) if plan.objects else lines.append("  none")
        lines.extend(["", "sw/isr.c ADC readout definitions marker content:"])
        lines.extend(f"  {entry.strip()}" for entry in plan.adc_readout_definitions) if plan.adc_readout_definitions else lines.append("  none")
        lines.extend(["", "sw/isr.c ADC readout marker content:"])
        lines.extend(f"  {entry.strip()}" for entry in plan.adc_readout) if plan.adc_readout else lines.append("  none")
        lines.extend(["", "main.c init_ip_cores marker content:"])
        lines.extend(f"  {entry.strip()}" for entry in plan.main_init) if plan.main_init else lines.append("  none")
        lines.extend(["", "sw/isr.c per-slot ISR marker content:"])
        any_isr_content = False
        for slot in SLOTS:
            entries = plan.isr_control_by_slot[slot]
            if entries:
                any_isr_content = True
                lines.append(f"{slot}:")
                lines.extend(f"  {entry.strip()}" for entry in entries)
        if not any_isr_content:
            lines.append("  none")
        lines.extend(["", "uz_global_configuration.h instance counts:"])
        for define, count in plan.instance_counts.items():
            lines.append(f"  {define} {count}U")
        lines.extend(["", "Javascope observable signals:"])
        if plan.javascope_observable_enums:
            lines.extend(f"  {entry.strip().rstrip(',')}" for entry in plan.javascope_observable_enums)
        else:
            lines.append("  none")
        if plan.warnings:
            lines.extend(["", "Warnings:"])
            lines.extend(f"- {warning}" for warning in plan.warnings)
        return "\n".join(lines)

    def visualization_signals(
        self,
        source_dir: Path,
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        software_modes: dict[str, str] | None = None,
        software_presets: dict[str, str] | None = None,
    ) -> list[VisualizationSignal]:
        plan = self.build_plan(source_dir, assignments, option_values, software_modes, software_presets)
        return plan.available_visualization_signals

    def driver_config_instances(
        self,
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        software_modes: dict[str, str] | None = None,
        software_presets: dict[str, str] | None = None,
    ) -> list[DriverConfigInstance]:
        software_modes = software_modes or {}
        software_presets = software_presets or {}
        instances: list[DriverConfigInstance] = []
        for slot in SLOTS:
            card_id = assignments.get(slot, "empty") if software_modes.get(slot, "follow_hardware") == "follow_hardware" else "empty"
            slot_lower = slot.lower()
            if card_id == "uz_d_temperature_ltc2983":
                preset = software_presets.get(slot, "default")
                instances.append(
                    DriverConfigInstance(
                        id=f"{slot_lower}_temperature",
                        slot=slot,
                        label=f"{slot} temperature card",
                        driver="temperature",
                        fields=self.driver_config_fields("temperature_card", preset),
                    )
                )
            elif card_id == "analog_ltc2311_16":
                instances.append(
                    DriverConfigInstance(
                        id=f"{slot_lower}_adc_ltc2311",
                        slot=slot,
                        label=f"{slot} ADC LTC2311",
                        driver="adc_ltc2311",
                        fields=self.driver_config_fields("uz_adc_ltc2311"),
                    )
                )
            elif card_id == "uz_d_absolute_encoder":
                for channel_index in range(1, 4):
                    interface = option_values.get(slot, {}).get(f"channel_{channel_index}", "none")
                    if interface == "endat":
                        instances.append(
                            DriverConfigInstance(
                                id=f"{slot_lower}_channel_{channel_index}_endat",
                                slot=slot,
                                label=f"{slot} channel {channel_index} EnDat",
                                driver="endat",
                                fields=self.driver_config_fields("uz_endat_interface"),
                            )
                        )
                    elif interface == "ssi":
                        instances.append(
                            DriverConfigInstance(
                                id=f"{slot_lower}_channel_{channel_index}_ssi",
                                slot=slot,
                                label=f"{slot} channel {channel_index} SSI",
                                driver="ssi",
                                fields=self.driver_config_fields("uz_ssi_interface"),
                            )
                        )
        return instances

    def generate(
        self,
        source_dir: Path,
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        software_modes: dict[str, str] | None = None,
        software_presets: dict[str, str] | None = None,
        visualization_signals: set[str] | list[str] | None = None,
        driver_config: dict[str, dict[str, str]] | None = None,
    ) -> SoftwareGenerationResult:
        plan = self.build_plan(
            source_dir, assignments, option_values, software_modes, software_presets, visualization_signals, driver_config
        )
        written_files: list[Path] = []
        patched_files: list[Path] = []

        for slot, content in plan.slot_content.items():
            slot_lower = slot.lower()
            header_path = source_dir / "include" / f"{slot_lower}_adapter_init.h"
            source_path = source_dir / "hw_init" / f"{slot_lower}_adapter_init.c"
            patch_slot_header(header_path, slot, content.header_includes, content.header_prototypes)
            written_files.append(header_path)
            patch_slot_source(source_path, slot, content.source_definitions)
            written_files.append(source_path)

        global_data = source_dir / "globalData.h"
        patch_global_data(global_data, plan.actual_values, plan.objects)
        patched_files.append(global_data)

        main_c = source_dir / "main.c"
        patch_marker_file(main_c, "main_init_ip_cores", plan.main_init)
        patched_files.append(main_c)

        isr_c = source_dir / "sw" / "isr.c"
        patch_marker_file(isr_c, "adc_readout_definitions", plan.adc_readout_definitions)
        patch_marker_file(isr_c, "adc_readout", plan.adc_readout)
        patch_slot_isr_control(isr_c, plan.isr_control_by_slot)
        patched_files.append(isr_c)

        javascope_h = source_dir / "include" / "javascope.h"
        patch_javascope_header(javascope_h, plan.javascope_observable_enums)
        patched_files.append(javascope_h)

        javascope_c = source_dir / "sw" / "javascope.c"
        patch_javascope_source(javascope_c, plan.javascope_observable_pointers)
        patched_files.append(javascope_c)

        global_configuration = source_dir / "uz" / "uz_global_configuration.h"
        if plan.instance_counts:
            patch_instance_counts(global_configuration, plan.instance_counts)
            patched_files.append(global_configuration)

        return SoftwareGenerationResult(written_files, patched_files, plan.warnings)

    def _temperature_context(
        self, slot: str, source_dir: Path, preset: str, config_values: dict[str, str]
    ) -> dict[str, object]:
        slot_lower = slot.lower()
        base_address_macro, warning = resolve_base_address_macro(source_dir, slot, "temperature")
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

    def _adc_ltc2311_context(self, slot: str, source_dir: Path, config_values: dict[str, str]) -> dict[str, object]:
        slot_lower = slot.lower()
        base_address_macro, warning = resolve_base_address_macro(source_dir, slot, "adc_ltc2311")
        warnings = [warning] if warning else []
        context = {
            "slot": slot,
            "slot_lower": slot_lower,
            "base_address_macro": base_address_macro,
            "warnings": warnings,
        }
        context.update(config_values)
        return context

    def _serial_encoder_context(
        self, slot: str, channel: int, interface: str, source_dir: Path, config_values: dict[str, str]
    ) -> dict[str, object]:
        slot_lower = slot.lower()
        base_address_macro, warning = resolve_base_address_macro(source_dir, slot, interface, channel)
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


def patch_slot_header(path: Path, slot: str, includes: list[str], prototypes: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_named_block(text, slot, "includes", includes)
    text = replace_named_block(text, slot, "prototypes", prototypes)
    path.write_text(text, encoding="utf-8")


def split_header_template(rendered_header: str) -> tuple[list[str], list[str]]:
    includes: list[str] = []
    prototypes: list[str] = []
    for line in rendered_header.splitlines():
        stripped = line.strip()
        if not stripped:
            continue
        if stripped.startswith("#include") or stripped.startswith("/*"):
            includes.append(line)
        else:
            prototypes.append(line)
    return includes, prototypes


def driver_instance_values(
    instance_id: str, fields: list[DriverConfigField], driver_config: dict[str, dict[str, str]]
) -> dict[str, str]:
    configured = driver_config.get(instance_id, {})
    if configured.get("mode") != "custom":
        configured = {}
    return {field.id: configured.get(field.id, field.default) for field in fields}


def patch_slot_source(path: Path, slot: str, definitions: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_named_block(text, slot, "definitions", definitions)
    path.write_text(text, encoding="utf-8")


def patch_global_data(path: Path, actual_values: list[str], objects: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_block(text, GLOBAL_DATA_MARKERS["actual_values"], actual_values)
    text = replace_block(text, GLOBAL_DATA_MARKERS["objects"], objects)
    path.write_text(text, encoding="utf-8")


def patch_marker_file(path: Path, marker_key: str, lines: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_block(text, FILE_MARKERS[marker_key], lines)
    path.write_text(text, encoding="utf-8")


def patch_slot_isr_control(path: Path, isr_control_by_slot: dict[str, list[str]]) -> None:
    text = path.read_text(encoding="utf-8")
    for slot in SLOTS:
        text = replace_named_block(text, slot, "isr_control", isr_control_by_slot.get(slot, []))
    path.write_text(text, encoding="utf-8")


def patch_javascope_header(path: Path, observable_enums: list[str]) -> None:
    patch_marker_file(path, "javascope_observables", observable_enums)


def patch_javascope_source(path: Path, observable_pointers: list[str]) -> None:
    patch_marker_file(path, "javascope_observable_pointers", observable_pointers)


def patch_instance_counts(path: Path, counts: dict[str, int]) -> None:
    text = path.read_text(encoding="utf-8")
    production_text, separator, test_text = text.partition("\n// Configuration defines for the number of used instances for testing")
    for define, count in counts.items():
        pattern = re.compile(rf"^#define\s+{re.escape(define)}\s+\d+U", re.MULTILINE)
        production_text, replacements = pattern.subn(f"#define {define:<49} {count}U", production_text, count=1)
        if replacements != 1:
            raise MarkerError(f"Could not find {define} in {path}.")
    path.write_text(production_text + separator + test_text, encoding="utf-8")


def replace_named_block(text: str, slot: str, block_name: str, lines: list[str]) -> str:
    marker = (
        f"/* Project Wizard BEGIN: {slot} {block_name} */",
        f"/* Project Wizard END: {slot} {block_name} */",
    )
    return replace_block(text, marker, lines)


def replace_block(text: str, marker: tuple[str, str], lines: list[str]) -> str:
    begin, end = marker
    body = "\n".join(lines)
    if body:
        body = body + "\n"
    pattern = re.compile(rf"{re.escape(begin)}.*?{re.escape(end)}", re.DOTALL)
    text, count = pattern.subn(f"{begin}\n{body}{end}", text, count=1)
    if count != 1:
        raise MarkerError(f"Could not find marker block {begin}.")
    return text


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


def temperature_visualization_signals(slot_lower: str, preset: str) -> list[VisualizationSignal]:
    signals: list[VisualizationSignal] = []
    slot = slot_lower.upper()
    zero_based_connector_labels = preset == "type_k_thermocouple"
    for group in ["A", "B", "C"]:
        for array_index in range(20):
            if zero_based_connector_labels:
                channel_label = f"{array_index:02d}"
                signal_id_channel = str(array_index)
                enum_channel = str(array_index)
            else:
                channel_label = str(array_index + 1)
                signal_id_channel = str(array_index + 1)
                enum_channel = str(array_index + 1)
            signal_id = f"temp_{slot_lower}_{group.lower()}_{signal_id_channel}"
            enum_name = f"JSO_TEMP_{slot_lower.upper()}_{group}_CH{enum_channel}"
            pointer = f"&data->av.temperature_card_{slot_lower}_channel_{group}.temperature[{array_index}]"
            signals.append(
                VisualizationSignal(
                    signal_id=signal_id,
                    slot=slot,
                    label=f"{slot_lower.upper()} temperature group {group} channel {channel_label}",
                    enum_name=enum_name,
                    pointer_expression=pointer,
                )
            )
    return signals


def encoder_visualization_signals(interface: str, prefix: str, slot_lower: str, channel: int) -> list[VisualizationSignal]:
    base_id = f"{prefix}_{slot_lower}_{channel}"
    enum_base = f"JSO_{interface.upper()}_{slot_lower.upper()}_CH{channel}"
    label_base = f"{slot_lower.upper()} {interface.upper()} channel {channel}"
    slot = slot_lower.upper()
    fields = [
        ("position_mech_si_single_turn", "POS_MECH_ST", "position mech SI single turn"),
        ("position_el_si_single_turn", "POS_EL_ST", "position el SI single turn"),
        ("speed_mech_si", "SPEED_MECH_SI", "speed mech SI"),
        ("speed_el_si", "SPEED_EL_SI", "speed el SI"),
        ("speed_mech_rpm", "SPEED_MECH_RPM", "speed mech rpm"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"{base_id}_{field}",
            slot=slot,
            label=f"{label_base} {label}",
            enum_name=f"{enum_base}_{enum_suffix}",
            pointer_expression=f"&data->av.{base_id}_{field}",
        )
        for field, enum_suffix, label in fields
    ]


def adc_ltc2311_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    return [
        VisualizationSignal(
            signal_id=f"adc_ltc2311_{slot_lower}_ch{channel}",
            slot=slot,
            label=f"{slot} ADC LTC2311 channel {channel}",
            enum_name=f"JSO_ADC_{slot}_CH{channel}",
            pointer_expression=f"&data->av.adc_ltc2311_{slot_lower}_ch{channel}",
        )
        for channel in range(8)
    ]


def adc_ltc2311_actual_values(slot_lower: str) -> list[str]:
    return [f"\tfloat adc_ltc2311_{slot_lower}_ch{channel};" for channel in range(8)]


def adc_ltc2311_isr_lines(slot: str, context: dict[str, object]) -> list[str]:
    slot_index = int(slot[1]) - 1
    buffer_offset = slot_index * 8
    slot_lower = slot.lower()
    return [
        (
            f"    Global_Data.av.adc_ltc2311_{slot_lower}_ch{channel} = "
            f"uz_adcLtc2311_convert_raw_to_physical_value("
            f"Global_Data.objects.adc_ltc2311_{slot_lower}, adc_ltc2311_data.data[{buffer_offset + channel}], {channel}U);"
        )
        for channel in range(8)
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


def resolve_base_address_macro(source_dir: Path, slot: str, interface: str, channel: int | None = None) -> tuple[str, str]:
    slot_lower = slot.lower()
    if interface == "temperature":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_TEMPERATURE_CARD_INT_0_BASEADDR"
        search_terms = ["TEMP", "TEMPERATURE"]
    elif interface == "adc_ltc2311":
        fallback = f"XPAR_UZ_ANALOG_ADAPTER_{slot.upper()}_ADAPTER_{slot.upper()}_ADC_LTC2311_S00_AXI_BASEADDR"
        search_terms = ["ADC_LTC2311", "ADCLTC2311", "LTC2311"]
    elif interface == "endat":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_UZ_ENDAT_INTERFACE_{slot.upper()}_CHANNEL_{channel}_BASEADDR"
        search_terms = ["ENDAT"]
    elif interface == "ssi":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_UZ_SSI_INTERFACE_{slot.upper()}_CHANNEL_{channel}_BASEADDR"
        search_terms = ["SSI"]
    else:
        fallback = f"XPAR_{slot.upper()}_BASEADDR"
        search_terms = [interface.upper()]
    xparameters, macros = xparameter_baseaddr_macros(source_dir)
    if xparameters is None:
        return fallback, f"{slot}: xparameters.h not found. Using fallback base-address macro {fallback}."

    candidates = [
        macro
        for macro in macros
        if any(term in macro for term in search_terms)
    ]
    slot_candidates = [candidate for candidate in candidates if slot.upper() in candidate or slot_lower.upper() in candidate]
    if channel is not None:
        channel_candidates = [candidate for candidate in slot_candidates if f"CHANNEL_{channel}" in candidate]
        if channel_candidates:
            return channel_candidates[0], ""
    if slot_candidates:
        return slot_candidates[0], ""
    if candidates:
        return candidates[0], f"{slot}: no slot-specific {interface} BASEADDR macro found. Using {candidates[0]} from {xparameters}."
    return fallback, f"{slot}: no {interface} BASEADDR macro found in {xparameters}. Using fallback {fallback}."


@lru_cache(maxsize=16)
def xparameter_baseaddr_macros(source_dir: Path) -> tuple[Path | None, tuple[str, ...]]:
    xparameters = find_xparameters(source_dir)
    if xparameters is None:
        return None, ()
    text = xparameters.read_text(encoding="utf-8", errors="ignore")
    macros = tuple(re.findall(r"^#define\s+(XPAR_[A-Z0-9_]*BASEADDR)\b", text, re.MULTILINE))
    return xparameters, macros


@lru_cache(maxsize=16)
def find_xparameters(source_dir: Path) -> Path | None:
    search_roots = [source_dir]
    search_roots.extend(parent for parent in source_dir.parents if parent.name.lower() in {"baremetal", "software", "vitis"})
    seen: set[Path] = set()
    for root in search_roots:
        if root in seen or not root.exists():
            continue
        seen.add(root)
        matches = [path for path in root.rglob("xparameters.h") if "test" not in {part.lower() for part in path.parts}]
        if matches:
            return matches[0]
    return None
