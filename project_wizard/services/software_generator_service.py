from __future__ import annotations

import re
from dataclasses import dataclass, field
from functools import lru_cache
from pathlib import Path

from ..repositories import CardDatabase
from ..template_renderer import SimpleTemplateRenderer


SLOTS = ["A1", "A2", "A3", "D1", "D2", "D3", "D4", "D5"]

DAC_WAVEGEN_TYPES = {
    "sine": {
        "type": "uz_wavegen_sine_t",
        "init": "uz_wavegen_sine_init",
        "count_define": "UZ_WAVEGEN_SINE_MAX_INSTANCES",
    },
    "sawtooth": {
        "type": "uz_wavegen_sawtooth_t",
        "init": "uz_wavegen_sawtooth_init",
        "count_define": "UZ_WAVEGEN_SAWTOOTH_MAX_INSTANCES",
    },
    "triangle": {
        "type": "uz_wavegen_triangle_t",
        "init": "uz_wavegen_triangle_init",
        "count_define": "UZ_WAVEGEN_TRIANGLE_MAX_INSTANCES",
    },
    "square": {
        "type": "uz_wavegen_square_t",
        "init": "uz_wavegen_square_init",
        "count_define": "UZ_WAVEGEN_SQUARE_MAX_INSTANCES",
    },
    "pulse": {
        "type": "uz_wavegen_pulse_t",
        "init": "uz_wavegen_pulse_init",
        "count_define": "UZ_WAVEGEN_PULSE_MAX_INSTANCES",
    },
}

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
    "hardware_version": (
        "/* Project Wizard BEGIN: hardware_version */",
        "/* Project Wizard END: hardware_version */",
    ),
    "adc_readout_definitions": (
        "/* Project Wizard BEGIN: adc_readout_definitions */",
        "/* Project Wizard END: adc_readout_definitions */",
    ),
    "adc_readout": (
        "/* Project Wizard BEGIN: adc_readout */",
        "/* Project Wizard END: adc_readout */",
    ),
    "datamover_array_length": (
        "/* Project Wizard BEGIN: datamover_array_length */",
        "/* Project Wizard END: datamover_array_length */",
    ),
    "main_init_ip_cores": (
        "/* Project Wizard BEGIN: init_ip_cores */",
        "/* Project Wizard END: init_ip_cores */",
    ),
    "pwm_runtime": (
        "/* Project Wizard BEGIN: pwm_runtime */",
        "/* Project Wizard END: pwm_runtime */",
    ),
    "idle_state_isr_actions": (
        "/* Project Wizard BEGIN: idle_state isr_actions */",
        "/* Project Wizard END: idle_state isr_actions */",
    ),
    "running_state_isr_actions": (
        "/* Project Wizard BEGIN: running_state isr_actions */",
        "/* Project Wizard END: running_state isr_actions */",
    ),
    "control_state_isr_actions": (
        "/* Project Wizard BEGIN: control_state isr_actions */",
        "/* Project Wizard END: control_state isr_actions */",
    ),
    "error_state_isr_actions": (
        "/* Project Wizard BEGIN: error_state isr_actions */",
        "/* Project Wizard END: error_state isr_actions */",
    ),
    "javascope_observables": (
        "/* Project Wizard BEGIN: javascope_observables */",
        "/* Project Wizard END: javascope_observables */",
    ),
    "javascope_slowdata": (
        "/* Project Wizard BEGIN: javascope_slowdata */",
        "/* Project Wizard END: javascope_slowdata */",
    ),
    "javascope_observable_pointers": (
        "/* Project Wizard BEGIN: javascope_observable_pointers */",
        "/* Project Wizard END: javascope_observable_pointers */",
    ),
    "javascope_slowdata_pointers": (
        "/* Project Wizard BEGIN: javascope_slowdata_pointers */",
        "/* Project Wizard END: javascope_slowdata_pointers */",
    ),
}

PWM_GLOBAL_DEFINE_KEYS = {
    "pwm_frequency": "UZ_PWM_FREQUENCY",
    "pwm_deadtime_us": "UZ_PWM_DEADTIME_IN_US",
    "pwm_min_pulse_width_us": "UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US",
}

PWM_2L_MODE_OPTIONS = (
    ("normalized_input_via_AXI", "normalized_input_via_AXI"),
    ("normalized_input_via_FPGA", "normalized_input_via_FPGA"),
    ("direct_control_via_FPGA", "direct_control_via_FPGA"),
)

PWM_2L_TRIGGER_SOURCE_OPTIONS = (
    ("trigger_at_MIN", "trigger_at_MIN"),
    ("trigger_at_MAX", "trigger_at_MAX"),
    ("trigger_at_EITHER", "trigger_at_EITHER"),
)

BOOL_LITERAL_OPTIONS = (
    ("true", "true"),
    ("false", "false"),
)


@dataclass
class SlotSoftwareContent:
    header_includes: list[str] = field(default_factory=list)
    header_prototypes: list[str] = field(default_factory=list)
    source_definitions: list[str] = field(default_factory=list)


@dataclass
class SoftwarePlan:
    slot_content: dict[str, SlotSoftwareContent]
    generated_files: dict[str, str]
    actual_values: list[str]
    objects: list[str]
    adc_readout_definitions: list[str]
    adc_readout: list[str]
    main_init: list[str]
    isr_control_by_slot: dict[str, list[str]]
    state_isr_actions: dict[str, list[str]]
    datamover_array_length: int
    javascope_observable_enums: list[str]
    javascope_observable_pointers: list[str]
    javascope_slowdata_enums: list[str]
    javascope_slowdata_pointers: list[str]
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
    source_expression: str = ""
    source_type: str = "float"

    @property
    def field_name(self) -> str:
        return f"viz_{re.sub(r'[^0-9A-Za-z_]', '_', self.signal_id)}"

    @property
    def float_expression(self) -> str:
        expression = self.source_expression or self.pointer_expression.removeprefix("&")
        if self.source_type == "bool":
            return f"({expression} ? 1.0f : 0.0f)"
        if self.source_type in {"uint32", "int32", "uint16", "int16", "enum"}:
            return f"((float){expression})"
        return expression


@dataclass(frozen=True)
class DriverConfigField:
    id: str
    label: str
    default: str
    multiline: bool = False
    help_text: str = ""
    input_type: str = "text"
    options: tuple[tuple[str, str], ...] = ()
    visible_when: tuple[tuple[str, tuple[str, ...]], ...] = ()


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
                    help_text=str(raw_field.get("help", "")),
                    input_type=str(raw_field.get("input", "text")),
                    options=tuple(
                        (str(option.get("value", "")), str(option.get("label", option.get("value", ""))))
                        for option in raw_field.get("options", [])
                        if isinstance(option, dict)
                    ),
                    visible_when=tuple(
                        (str(controller), tuple(str(value) for value in allowed_values))
                        for controller, allowed_values in raw_field.get("visible_when", {}).items()
                        if isinstance(allowed_values, list)
                    ),
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
        hardware_config: dict[str, str] | None = None,
        resolve_base_addresses: bool = True,
    ) -> SoftwarePlan:
        if resolve_base_addresses:
            clear_xparameters_cache()
        software_modes = software_modes or {}
        software_presets = software_presets or {}
        driver_config = driver_config or {}
        hardware_config = hardware_config or {}
        selected_visualization_routes = normalize_visualization_routes(visualization_signals)
        slot_content = {slot: SlotSoftwareContent() for slot in SLOTS}
        generated_files: dict[str, str] = {}
        actual_values: list[str] = []
        objects: list[str] = []
        adc_readout_definitions: list[str] = []
        adc_readout: list[str] = []
        main_init: list[str] = []
        isr_control_by_slot: dict[str, list[str]] = {slot: [] for slot in SLOTS}
        state_isr_actions: dict[str, list[str]] = {
            "idle_state": [],
            "running_state": [],
            "control_state": [],
            "error_state": [],
        }
        available_visualization_signals: list[VisualizationSignal] = []
        warnings: list[str] = []
        temperature_instances = 0
        adc_ltc2311_instances = 0
        adc_max11331_instances = 0
        dac8831_instances = 0
        inverter_adapter_instances = 0
        incremental_encoder_instances = 0
        resolver_ip_instances = 0
        resolver_pl_interface_instances = 0
        axi_gpio_instances = 0
        wavegen_instance_counts = {
            "UZ_WAVEGEN_SINE_MAX_INSTANCES": 0,
            "UZ_WAVEGEN_SAWTOOTH_MAX_INSTANCES": 0,
            "UZ_WAVEGEN_TRIANGLE_MAX_INSTANCES": 0,
            "UZ_WAVEGEN_SQUARE_MAX_INSTANCES": 0,
            "UZ_WAVEGEN_PULSE_MAX_INSTANCES": 0,
        }
        analog_adc_offsets = analog_adc_packed_offsets(assignments)
        datamover_array_length = max(2, sum(stream["channel_count"] for stream in analog_adc_offsets.values()))
        endat_instances = 0
        ssi_instances = 0
        pwm_2l_instance_count = config_int(hardware_config.get("pwm_2l_instances", "4"), default=4, minimum=1, maximum=10)
        pwm_3l_enabled = config_int(hardware_config.get("pwm_3l_instances", "1"), default=1, minimum=0, maximum=1) > 0
        state_isr_actions.update(pwm_2l_state_isr_actions(pwm_2l_instance_count, hardware_config))
        pwm_context = self._project_wizard_pwm_context(
            source_dir, pwm_2l_instance_count, pwm_3l_enabled, driver_config, resolve_base_addresses
        )
        warnings.extend(pwm_context.pop("warnings"))
        generated_files["include/pwm_init.h"] = self.renderer.render_file(
            "software/pwm_init.h.tpl", pwm_context
        ).rstrip() + "\n"
        generated_files["hw_init/pwm_init.c"] = self.renderer.render_file(
            "software/pwm_init.c.tpl", pwm_context
        ).rstrip() + "\n"
        for instance in pwm_context["pwm_2l_instances"]:
            objects.extend(
                [
                    f"\tuz_PWM_SS_2L_t* project_wizard_pwm_2l_{instance['index']};",
                    f"\tuz_interlockDeadtime2L_handle project_wizard_deadtime_2l_{instance['index']};",
                ]
            )
            main_init.extend(
                [
                    f"\t\t\tGlobal_Data.objects.project_wizard_deadtime_2l_{instance['index']} = initialize_project_wizard_deadtime_2l_{instance['index']}();",
                    f"\t\t\tuz_interlockDeadtime2L_set_enable_output(Global_Data.objects.project_wizard_deadtime_2l_{instance['index']}, true);",
                    f"\t\t\tGlobal_Data.objects.project_wizard_pwm_2l_{instance['index']} = initialize_project_wizard_pwm_2l_{instance['index']}();",
                ]
            )
        if pwm_3l_enabled:
            main_init.append("\t\t\tinitialize_project_wizard_pwm_3l(&Global_Data);")
        objects.append("\tuz_wavegen_three_phase* three_phase_sine;")
        main_init.append("\t\t\tGlobal_Data.objects.three_phase_sine = uz_wavegen_three_phase_init();")

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
                    resolve_base_addresses,
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
                isr_control_by_slot[slot].extend(
                    adc_ltc2311_isr_lines(slot, context, analog_adc_offsets[slot]["offset"])
                )
                available_visualization_signals.extend(adc_ltc2311_visualization_signals(str(context["slot_lower"])))
            elif card_id == "analog_max11331":
                adc_max11331_instances += 1
                context = self._adc_max11331_context(
                    slot,
                    source_dir,
                    driver_instance_values(
                        f"{slot.lower()}_adc_max11331", self.driver_config_fields("uz_adc_max11331"), driver_config
                    ),
                    resolve_base_addresses,
                )
                warnings.extend(context.pop("warnings"))
                header_includes, header_prototypes = split_header_template(
                    self.renderer.render_file(self.driver_template("uz_adc_max11331", "header"), context)
                )
                slot_content[slot].header_includes.extend(header_includes)
                slot_content[slot].header_prototypes.extend(header_prototypes)
                slot_content[slot].source_definitions.append(
                    self.renderer.render_file(self.driver_template("uz_adc_max11331", "source"), context).rstrip()
                )
                objects.append(f"\tuz_adcMax11331_t* adc_max11331_{context['slot_lower']};")
                main_init.append(
                    f"\t\t\tGlobal_Data.objects.adc_max11331_{context['slot_lower']} = initialize_adc_max11331_{context['slot_lower']}();"
                )
                actual_values.extend(adc_max11331_actual_values(str(context["slot_lower"])))
                isr_control_by_slot[slot].extend(
                    adc_max11331_isr_lines(slot, context, analog_adc_offsets[slot]["offset"])
                )
                available_visualization_signals.extend(adc_max11331_visualization_signals(str(context["slot_lower"])))
            elif card_id == "analog_dac8831":
                dac8831_instances += 1
                context = self._dac8831_context(
                    slot,
                    source_dir,
                    driver_instance_values(
                        f"{slot.lower()}_dac8831", self.driver_config_fields("uz_dac_interface"), driver_config
                    ),
                    resolve_base_addresses,
                )
                warnings.extend(context.pop("warnings"))
                wavegen_instances = context.pop("wavegen_instances")
                header_includes, header_prototypes = split_header_template(
                    self.renderer.render_file(self.driver_template("uz_dac_interface", "header"), context)
                )
                slot_content[slot].header_includes.extend(header_includes)
                slot_content[slot].header_prototypes.extend(header_prototypes)
                slot_content[slot].source_definitions.append(
                    self.renderer.render_file(self.driver_template("uz_dac_interface", "source"), context).rstrip()
                )
                objects.append(f"\tuz_dac_interface_t* dac8831_{context['slot_lower']};")
                for instance in wavegen_instances:
                    objects.append(f"\t{instance['type']}* {instance['object_name']};")
                actual_values.extend(dac8831_actual_values(str(context["slot_lower"])))
                main_init.append(
                    f"\t\t\tGlobal_Data.objects.dac8831_{context['slot_lower']} = initialize_dac8831_{context['slot_lower']}();"
                )
                for instance in wavegen_instances:
                    main_init.append(
                        f"\t\t\tGlobal_Data.objects.{instance['object_name']} = {instance['init']}();"
                    )
                    wavegen_instance_counts[instance["count_define"]] += 1
                isr_control_by_slot[slot].append(
                    "    update_dac8831_{slot_lower}_outputs(&Global_Data);".format(
                        slot_lower=context["slot_lower"]
                    )
                )
                available_visualization_signals.extend(dac8831_visualization_signals(str(context["slot_lower"])))
            elif card_id == "uz_d_inverter_adapter":
                inverter_adapter_instances += 1
                context = self._inverter_adapter_context(
                    slot,
                    source_dir,
                    driver_instance_values(
                        f"{slot.lower()}_inverter_adapter",
                        self.driver_config_fields("uz_inverter_adapter"),
                        driver_config,
                    ),
                    resolve_base_addresses,
                )
                warnings.extend(context.pop("warnings"))
                header_includes, header_prototypes = split_header_template(
                    self.renderer.render_file(self.driver_template("uz_inverter_adapter", "header"), context)
                )
                slot_content[slot].header_includes.extend(header_includes)
                slot_content[slot].header_prototypes.extend(header_prototypes)
                slot_content[slot].source_definitions.append(
                    self.renderer.render_file(self.driver_template("uz_inverter_adapter", "source"), context).rstrip()
                )
                objects.append(f"\tuz_inverter_adapter_t* inverter_adapter_{context['slot_lower']};")
                actual_values.append(f"\tstruct uz_inverter_adapter_outputs_t inverter_adapter_{context['slot_lower']};")
                main_init.append(
                    f"\t\t\tGlobal_Data.objects.inverter_adapter_{context['slot_lower']} = initialize_inverter_adapter_{context['slot_lower']}();"
                )
                state_isr_actions["idle_state"].append(
                    f"uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_{context['slot_lower']}, false);"
                )
                state_isr_actions["running_state"].append(
                    f"uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_{context['slot_lower']}, true);"
                )
                state_isr_actions["error_state"].append(
                    f"uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_adapter_{context['slot_lower']}, false);"
                )
                isr_control_by_slot[slot].append(
                    "    update_inverter_adapter_{slot_lower}_outputs(&Global_Data);".format(
                        slot_lower=context["slot_lower"]
                    )
                )
                available_visualization_signals.extend(inverter_adapter_visualization_signals(str(context["slot_lower"])))
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
                    resolve_base_addresses,
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
            elif card_id == "uz_d_incremental_encoder":
                for channel_index in range(1, 4):
                    incremental_encoder_instances += 1
                    context = self._incremental_encoder_context(
                        slot,
                        channel_index,
                        source_dir,
                        driver_instance_values(
                            f"{slot.lower()}_incremental_encoder_{channel_index}",
                            self.driver_config_fields("uz_incrementalEncoder"),
                            driver_config,
                        ),
                        resolve_base_addresses,
                    )
                    warnings.extend(context.pop("warnings"))
                    header_includes, header_prototypes = split_header_template(
                        self.renderer.render_file(self.driver_template("uz_incrementalEncoder", "header"), context)
                    )
                    slot_content[slot].header_includes.extend(header_includes)
                    slot_content[slot].header_prototypes.extend(header_prototypes)
                    slot_content[slot].source_definitions.append(
                        self.renderer.render_file(self.driver_template("uz_incrementalEncoder", "source"), context).rstrip()
                    )
                    objects.append(f"\tuz_incrementalEncoder_t* incremental_encoder_{context['slot_lower']}_{channel_index};")
                    actual_values.extend(incremental_encoder_actual_values(str(context["slot_lower"]), channel_index))
                    main_init.append(
                        f"\t\t\tGlobal_Data.objects.incremental_encoder_{context['slot_lower']}_{channel_index} = initialize_incremental_encoder_{context['slot_lower']}_{channel_index}();"
                    )
                    isr_control_by_slot[slot].extend(incremental_encoder_isr_lines(context))
                    available_visualization_signals.extend(
                        incremental_encoder_visualization_signals(str(context["slot_lower"]), channel_index)
                    )
            elif card_id == "uz_d_resolver":
                channel_count = resolver_channel_count(slot)
                slot_options = option_values.get(slot, {})
                for channel_index in range(1, channel_count + 1):
                    resolver_ip_instances += 1
                    resolver_context = self._resolver_ip_context(
                        slot,
                        channel_index,
                        source_dir,
                        driver_instance_values(
                            f"{slot.lower()}_resolver_ip_{channel_index}",
                            self.driver_config_fields("uz_resolverIP"),
                            driver_config,
                        ),
                        resolve_base_addresses,
                    )
                    warnings.extend(resolver_context.pop("warnings"))
                    header_includes, header_prototypes = split_header_template(
                        self.renderer.render_file(self.driver_template("uz_resolverIP", "header"), resolver_context)
                    )
                    slot_content[slot].header_includes.extend(header_includes)
                    slot_content[slot].header_prototypes.extend(header_prototypes)
                    slot_content[slot].source_definitions.append(
                        self.renderer.render_file(self.driver_template("uz_resolverIP", "source"), resolver_context).rstrip()
                    )
                    objects.append(f"\tuz_resolverIP_t* resolver_ip_{resolver_context['slot_lower']}_{channel_index};")
                    main_init.append(
                        f"\t\t\tGlobal_Data.objects.resolver_ip_{resolver_context['slot_lower']}_{channel_index} = initialize_resolver_ip_{resolver_context['slot_lower']}_{channel_index}();"
                    )
                    if resolver_pl_interface_enabled(slot_options, channel_index):
                        resolver_pl_interface_instances += 1
                        pl_context = self._resolver_pl_interface_context(
                            slot,
                            channel_index,
                            source_dir,
                            driver_instance_values(
                                f"{slot.lower()}_resolver_pl_interface_{channel_index}",
                                self.driver_config_fields("uz_resolver_pl_interface"),
                                driver_config,
                            ),
                            resolve_base_addresses,
                        )
                        warnings.extend(pl_context.pop("warnings"))
                        header_includes, header_prototypes = split_header_template(
                            self.renderer.render_file(
                                self.driver_template("uz_resolver_pl_interface", "header"),
                                pl_context,
                            )
                        )
                        slot_content[slot].header_includes.extend(header_includes)
                        slot_content[slot].header_prototypes.extend(header_prototypes)
                        slot_content[slot].source_definitions.append(
                            self.renderer.render_file(
                                self.driver_template("uz_resolver_pl_interface", "source"),
                                pl_context,
                            ).rstrip()
                        )
                        objects.append(
                            f"\tuz_resolver_pl_interface_t* resolver_pl_interface_{pl_context['slot_lower']}_{channel_index};"
                        )
                        actual_values.extend(resolver_pl_interface_actual_values(str(pl_context["slot_lower"]), channel_index))
                        main_init.append(
                            f"\t\t\tGlobal_Data.objects.resolver_pl_interface_{pl_context['slot_lower']}_{channel_index} = initialize_resolver_pl_interface_{pl_context['slot_lower']}_{channel_index}();"
                        )
                        isr_control_by_slot[slot].extend(
                            resolver_pl_interface_isr_lines(str(pl_context["slot_lower"]), channel_index)
                        )
                        available_visualization_signals.extend(
                            resolver_pl_interface_visualization_signals(str(pl_context["slot_lower"]), channel_index)
                        )
                    else:
                        actual_values.extend(resolver_ip_actual_values(str(resolver_context["slot_lower"]), channel_index))
                        isr_control_by_slot[slot].extend(
                            resolver_ip_isr_lines(str(resolver_context["slot_lower"]), channel_index)
                        )
                        available_visualization_signals.extend(
                            resolver_ip_visualization_signals(str(resolver_context["slot_lower"]), channel_index)
                        )
            elif (self.database.card_by_id(card_id) or {}).get("vivado", {}).get("io_card"):
                card = self.database.card_by_id(card_id) or {}
                slot_options = option_values.get(slot, {})
                if io_card_needs_axi(card, slot_options):
                    axi_gpio_instances += 1
                    context = self._axi_gpio_context(slot, source_dir, card, slot_options, resolve_base_addresses)
                    warnings.extend(context.pop("warnings"))
                    header_includes, header_prototypes = split_header_template(
                        self.renderer.render_file(self.driver_template("uz_axi_gpio", "header"), context)
                    )
                    slot_content[slot].header_includes.extend(header_includes)
                    slot_content[slot].header_prototypes.extend(header_prototypes)
                    slot_content[slot].source_definitions.append(
                        self.renderer.render_file(self.driver_template("uz_axi_gpio", "source"), context).rstrip()
                    )
                    objects.append(f"\tuz_axi_gpio_t* axi_gpio_{context['slot_lower']};")
                    actual_values.append(f"\tuint32_t io_card_{context['slot_lower']}_state;")
                    main_init.append(
                        f"\t\t\tGlobal_Data.objects.axi_gpio_{context['slot_lower']} = initialize_axi_gpio_{context['slot_lower']}();"
                    )
                    isr_control_by_slot[slot].append(
                        f"    Global_Data.av.io_card_{context['slot_lower']}_state = uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_{context['slot_lower']});"
                    )
                    available_visualization_signals.extend(io_card_visualization_signals(str(context["slot_lower"])))
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
                        resolve_base_addresses,
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
                        resolve_base_addresses,
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

        if adc_ltc2311_instances or adc_max11331_instances:
            adc_readout_definitions.append("static uz_array_int16_t analog_adc_data;")
            adc_readout.append("    analog_adc_data = uz_dataMover_update_buffer_and_get_data();")

        selected_javascope_signals = [
            signal
            for signal in available_visualization_signals
            if selected_visualization_routes.get(signal.signal_id) in {"javascope", "both"}
        ]
        selected_slowdata_signals = [
            signal
            for signal in available_visualization_signals
            if selected_visualization_routes.get(signal.signal_id) in {"slow_data", "both"}
        ]
        routed_visualization_signals = list(
            {signal.signal_id: signal for signal in selected_javascope_signals + selected_slowdata_signals}.values()
        )
        field_declarations = [
            f"    float {signal.field_name};" for signal in routed_visualization_signals
        ] or ["    float unused;"]
        update_assignments = [
            f"    project_wizard_visualization_data.{signal.field_name} = {signal.float_expression};"
            for signal in routed_visualization_signals
        ]
        visualization_context = {
            "field_declarations": "\n".join(field_declarations),
            "update_assignments": "\n".join(update_assignments),
        }
        generated_files["include/project_wizard_visualization.h"] = self.renderer.render_file(
            "software/project_wizard_visualization.h.tpl", visualization_context
        ).rstrip() + "\n"
        generated_files["sw/project_wizard_visualization.c"] = self.renderer.render_file(
            "software/project_wizard_visualization.c.tpl", visualization_context
        ).rstrip() + "\n"
        return SoftwarePlan(
            slot_content=slot_content,
            generated_files=generated_files,
            actual_values=actual_values,
            objects=objects,
            adc_readout_definitions=adc_readout_definitions,
            adc_readout=adc_readout,
            main_init=main_init,
            isr_control_by_slot=isr_control_by_slot,
            state_isr_actions=state_isr_actions,
            datamover_array_length=datamover_array_length,
            javascope_observable_enums=[f"\t{signal.enum_name}," for signal in selected_javascope_signals],
            javascope_observable_pointers=[
                f"\tjs_ch_observable[{signal.enum_name}] = &project_wizard_visualization_data.{signal.field_name};"
                for signal in selected_javascope_signals
            ],
            javascope_slowdata_enums=[
                f"\tJSSD_FLOAT_{signal.enum_name.removeprefix('JSO_')}," for signal in selected_slowdata_signals
            ],
            javascope_slowdata_pointers=[
                f"\tjs_slowDataArray[JSSD_FLOAT_{signal.enum_name.removeprefix('JSO_')}] = &project_wizard_visualization_data.{signal.field_name};"
                for signal in selected_slowdata_signals
            ],
            available_visualization_signals=available_visualization_signals,
            instance_counts={
                "UZ_PWM_SS_2L_MAX_INSTANCES": pwm_2l_instance_count,
                "UZ_ADCLTC2311_MAX_INSTANCES": adc_ltc2311_instances,
                "UZ_ADCMAX11331_MAX_INSTANCES": adc_max11331_instances,
                "UZ_TEMPERATURE_CARD_MAX_INSTANCES": temperature_instances,
                "UZ_ENDAT_INTERFACE_MAX_INSTANCES": endat_instances,
                "UZ_SSI_INTERFACE_MAX_INSTANCES": ssi_instances,
                "UZ_DAC_INTERFACE_MAX_INSTANCES": dac8831_instances,
                "UZ_INVERTER_ADAPTER_MAX_INSTANCES": inverter_adapter_instances,
                "UZ_INCREMENTALENCODER_MAX_INSTANCES": incremental_encoder_instances,
                "UZ_RESOLVERIP_MAX_INSTANCES": resolver_ip_instances,
                "UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES": resolver_pl_interface_instances,
                "UZ_AXI_GPIO_MAX_INSTANCES": axi_gpio_instances,
                **wavegen_instance_counts,
            },
            warnings=warnings,
        )

    def preview(
        self,
        source_dir: Path,
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        platform_revision: str = "",
        software_modes: dict[str, str] | None = None,
        software_presets: dict[str, str] | None = None,
        visualization_signals: set[str] | list[str] | None = None,
        driver_config: dict[str, dict[str, str]] | None = None,
        hardware_config: dict[str, str] | None = None,
    ) -> str:
        plan = self.build_plan(
            source_dir,
            assignments,
            option_values,
            software_modes,
            software_presets,
            visualization_signals,
            driver_config,
            hardware_config,
            resolve_base_addresses=False,
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
        lines.extend(["", "Generated subsystem files:"])
        if plan.generated_files:
            lines.extend(f"- {path}" for path in plan.generated_files)
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
        lines.extend(["", "sw/isr.c PWM runtime marker content:"])
        lines.extend(f"  {entry.strip()}" for entry in project_wizard_pwm_runtime_lines())
        lines.extend(["", "sw/isr.c platform-state action marker content:"])
        for state_name in ["idle_state", "running_state", "control_state", "error_state"]:
            lines.append(f"{state_name}:")
            entries = plan.state_isr_actions.get(state_name, [])
            if entries:
                lines.extend(f"  {entry.strip()}" for entry in entries)
            else:
                lines.append("  none")
        lines.extend(["", "uz_global_configuration.h hardware revision:"])
        lines.append(f"  UZ_HARDWARE_VERSION {hardware_revision_define_value(platform_revision)}")
        lines.extend(["", "uz_global_configuration.h PWM timing defines:"])
        for config_key, define in PWM_GLOBAL_DEFINE_KEYS.items():
            value = (hardware_config or {}).get(config_key, "")
            if value:
                lines.append(f"  {define} {value}")
        lines.extend(["", "uz_global_configuration.h instance counts:"])
        for define, count in plan.instance_counts.items():
            lines.append(f"  {define} {count}U")
        lines.extend(["", "Javascope observable signals:"])
        if plan.javascope_observable_enums:
            lines.extend(f"  {entry.strip().rstrip(',')}" for entry in plan.javascope_observable_enums)
        else:
            lines.append("  none")
        lines.extend(["", "Javascope slow-data signals:"])
        if plan.javascope_slowdata_enums:
            lines.extend(f"  {entry.strip().rstrip(',')}" for entry in plan.javascope_slowdata_enums)
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
        plan = self.build_plan(
            source_dir,
            assignments,
            option_values,
            software_modes,
            software_presets,
            resolve_base_addresses=False,
        )
        return plan.available_visualization_signals

    def driver_config_instances(
        self,
        assignments: dict[str, str],
        option_values: dict[str, dict[str, str]],
        software_modes: dict[str, str] | None = None,
        software_presets: dict[str, str] | None = None,
        hardware_config: dict[str, str] | None = None,
    ) -> list[DriverConfigInstance]:
        software_modes = software_modes or {}
        software_presets = software_presets or {}
        hardware_config = hardware_config or {}
        instances: list[DriverConfigInstance] = []
        pwm_2l_instance_count = config_int(hardware_config.get("pwm_2l_instances", "4"), default=4, minimum=1, maximum=10)
        pwm_3l_enabled = config_int(hardware_config.get("pwm_3l_instances", "1"), default=1, minimum=0, maximum=1) > 0
        for index in range(pwm_2l_instance_count):
            instances.append(
                DriverConfigInstance(
                    id=f"pwm_2l_{index}",
                    slot="PWM",
                    label=f"2L PWM instance {index}",
                    driver="pwm_2l",
                    fields=pwm_2l_config_fields(),
                )
            )
            instances.append(
                DriverConfigInstance(
                    id=f"deadtime_2l_{index}",
                    slot="PWM",
                    label=f"2L deadtime instance {index}",
                    driver="deadtime_2l",
                    fields=deadtime_2l_config_fields(),
                )
            )
        if pwm_3l_enabled:
            instances.append(
                DriverConfigInstance(
                    id="pwm_3l_0",
                    slot="PWM",
                    label="3L PWM instance 0",
                    driver="pwm_3l",
                    fields=pwm_3l_config_fields(),
                )
            )
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
            elif card_id == "analog_max11331":
                instances.append(
                    DriverConfigInstance(
                        id=f"{slot_lower}_adc_max11331",
                        slot=slot,
                        label=f"{slot} ADC MAX11331",
                        driver="adc_max11331",
                        fields=self.driver_config_fields("uz_adc_max11331"),
                    )
                )
            elif card_id == "analog_dac8831":
                instances.append(
                    DriverConfigInstance(
                        id=f"{slot_lower}_dac8831",
                        slot=slot,
                        label=f"{slot} DAC8831",
                        driver="dac8831",
                        fields=self.driver_config_fields("uz_dac_interface"),
                    )
                )
            elif card_id == "uz_d_inverter_adapter":
                instances.append(
                    DriverConfigInstance(
                        id=f"{slot_lower}_inverter_adapter",
                        slot=slot,
                        label=f"{slot} inverter adapter",
                        driver="inverter_adapter",
                        fields=self.driver_config_fields("uz_inverter_adapter"),
                    )
                )
            elif card_id == "uz_d_incremental_encoder":
                for channel_index in range(1, 4):
                    instances.append(
                        DriverConfigInstance(
                            id=f"{slot_lower}_incremental_encoder_{channel_index}",
                            slot=slot,
                            label=f"{slot} incremental encoder channel {channel_index}",
                            driver="incremental_encoder",
                            fields=self.driver_config_fields("uz_incrementalEncoder"),
                        )
                    )
            elif card_id == "uz_d_resolver":
                channel_count = resolver_channel_count(slot)
                slot_options = option_values.get(slot, {})
                for channel_index in range(1, channel_count + 1):
                    instances.append(
                        DriverConfigInstance(
                            id=f"{slot_lower}_resolver_ip_{channel_index}",
                            slot=slot,
                            label=f"{slot} resolver IP channel {channel_index}",
                            driver="resolver_ip",
                            fields=self.driver_config_fields("uz_resolverIP"),
                        )
                    )
                    if resolver_pl_interface_enabled(slot_options, channel_index):
                        instances.append(
                            DriverConfigInstance(
                                id=f"{slot_lower}_resolver_pl_interface_{channel_index}",
                                slot=slot,
                                label=f"{slot} resolver PL interface channel {channel_index}",
                                driver="resolver_pl_interface",
                                fields=self.driver_config_fields("uz_resolver_pl_interface"),
                            )
                        )
            elif card_id in {"uz_d_optical_io", "uz_d_voltage_3v3_5v"}:
                card = self.database.card_by_id(card_id) or {}
                if io_card_needs_axi(card, option_values.get(slot, {})):
                    instances.append(
                        DriverConfigInstance(
                            id=f"{slot_lower}_axi_gpio",
                            slot=slot,
                            label=f"{slot} AXI GPIO IO card",
                            driver="axi_gpio",
                            fields=self.driver_config_fields("uz_axi_gpio"),
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
        platform_revision: str = "",
        software_modes: dict[str, str] | None = None,
        software_presets: dict[str, str] | None = None,
        visualization_signals: set[str] | list[str] | None = None,
        driver_config: dict[str, dict[str, str]] | None = None,
        hardware_config: dict[str, str] | None = None,
    ) -> SoftwareGenerationResult:
        plan = self.build_plan(
            source_dir, assignments, option_values, software_modes, software_presets, visualization_signals, driver_config, hardware_config
        )
        written_files: list[Path] = []
        patched_files: list[Path] = []

        for relative_path, content in plan.generated_files.items():
            path = source_dir / relative_path
            path.write_text(content, encoding="utf-8")
            written_files.append(path)

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
        patch_marker_file(isr_c, "pwm_runtime", project_wizard_pwm_runtime_lines())
        patch_platform_state_isr_actions(isr_c, plan.state_isr_actions)
        patch_slot_isr_control(isr_c, plan.isr_control_by_slot)
        patched_files.append(isr_c)

        datamover_c = source_dir / "IP_Cores" / "uz_dataMover" / "uz_dataMover.c"
        patch_marker_file(datamover_c, "datamover_array_length", [f"#define UZ_DATAMOVER_ARRAY_LENGTH {plan.datamover_array_length}"])
        patched_files.append(datamover_c)

        javascope_h = source_dir / "include" / "javascope.h"
        patch_javascope_header(javascope_h, plan.javascope_observable_enums, plan.javascope_slowdata_enums)
        patched_files.append(javascope_h)

        javascope_c = source_dir / "sw" / "javascope.c"
        patch_javascope_source(javascope_c, plan.javascope_observable_pointers, plan.javascope_slowdata_pointers)
        patched_files.append(javascope_c)

        global_configuration = source_dir / "uz" / "uz_global_configuration.h"
        patch_hardware_revision(global_configuration, platform_revision)
        patch_pwm_global_defines(global_configuration, hardware_config or {})
        if plan.instance_counts:
            patch_instance_counts(global_configuration, plan.instance_counts)
        patched_files.append(global_configuration)

        return SoftwareGenerationResult(written_files, patched_files, plan.warnings)

    def _project_wizard_pwm_context(
        self,
        source_dir: Path,
        pwm_2l_instance_count: int,
        pwm_3l_enabled: bool,
        driver_config: dict[str, dict[str, str]] | None = None,
        resolve_base_addresses: bool = True,
    ) -> dict[str, object]:
        driver_config = driver_config or {}
        instances: list[dict[str, object]] = []
        warnings: list[str] = []
        for index in range(pwm_2l_instance_count):
            pwm_macro, pwm_warning = resolve_pwm_base_address_macro(
                source_dir, "pwm_2l", index, search_xparameters=resolve_base_addresses
            )
            deadtime_macro, deadtime_warning = resolve_pwm_base_address_macro(
                source_dir, "deadtime_2l", index, search_xparameters=resolve_base_addresses
            )
            if pwm_warning:
                warnings.append(pwm_warning)
            if deadtime_warning:
                warnings.append(deadtime_warning)
            half_bridge_base = index * 3 + 1
            pwm_values = driver_instance_values(f"pwm_2l_{index}", pwm_2l_config_fields(), driver_config)
            deadtime_values = driver_instance_values(f"deadtime_2l_{index}", deadtime_2l_config_fields(), driver_config)
            instances.append(
                {
                    "index": index,
                    "pwm_base_address_macro": pwm_macro,
                    "deadtime_base_address_macro": deadtime_macro,
                    "half_bridge_a": half_bridge_base,
                    "half_bridge_b": half_bridge_base + 1,
                    "half_bridge_c": half_bridge_base + 2,
                    "pwm_config": pwm_values,
                    "deadtime_config": deadtime_values,
                }
            )
        pwm_3l_macro = ""
        pwm_3l_config = driver_instance_values("pwm_3l_0", pwm_3l_config_fields(), driver_config)
        if pwm_3l_enabled:
            pwm_3l_macro, pwm_3l_warning = resolve_pwm_base_address_macro(
                source_dir, "pwm_3l", 0, search_xparameters=resolve_base_addresses
            )
            if pwm_3l_warning:
                warnings.append(pwm_3l_warning)
        return {
            "pwm_2l_instances": instances,
            "pwm_3l_enabled": pwm_3l_enabled,
            "pwm_3l_base_address_macro": pwm_3l_macro,
            "pwm_3l_config": pwm_3l_config,
            "warnings": warnings,
        }

    def _temperature_context(
        self,
        slot: str,
        source_dir: Path,
        preset: str,
        config_values: dict[str, str],
        resolve_base_addresses: bool = True,
    ) -> dict[str, object]:
        slot_lower = slot.lower()
        base_address_macro, warning = resolve_base_address_macro(
            source_dir, slot, "temperature", search_xparameters=resolve_base_addresses
        )
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

    def _adc_ltc2311_context(
        self, slot: str, source_dir: Path, config_values: dict[str, str], resolve_base_addresses: bool = True
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

    def _adc_max11331_context(
        self, slot: str, source_dir: Path, config_values: dict[str, str], resolve_base_addresses: bool = True
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

    def _dac8831_context(
        self, slot: str, source_dir: Path, config_values: dict[str, str], resolve_base_addresses: bool = True
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

    def _inverter_adapter_context(
        self, slot: str, source_dir: Path, config_values: dict[str, str], resolve_base_addresses: bool = True
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

    def _incremental_encoder_context(
        self,
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

    def _resolver_ip_context(
        self,
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

    def _resolver_pl_interface_context(
        self,
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

    def _serial_encoder_context(
        self,
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

    def _axi_gpio_context(
        self,
        slot: str,
        source_dir: Path,
        card: dict[str, object],
        option_values: dict[str, str],
        resolve_base_addresses: bool = True,
    ) -> dict[str, object]:
        slot_lower = slot.lower()
        base_address_macro, warning = resolve_base_address_macro(
            source_dir, slot, "axi_gpio", search_xparameters=resolve_base_addresses
        )
        device_id_macro, device_warning = resolve_device_id_macro(
            source_dir, slot, "axi_gpio", search_xparameters=resolve_base_addresses
        )
        warnings = [entry for entry in [warning, device_warning] if entry]
        return {
            "slot": slot,
            "slot_lower": slot_lower,
            "base_address_macro": base_address_macro,
            "device_id_macro": device_id_macro,
            "fallback_device_id": d_slot_index(slot) - 1,
            "direction_mask": f"0x{io_card_direction_mask(card, option_values):08X}",
            "direction_mask_define": f"PROJECT_WIZARD_IO_CARD_{slot.upper()}_DIRECTION_MASK",
            "warnings": warnings,
        }


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


def pwm_2l_config_fields() -> list[DriverConfigField]:
    return [
        DriverConfigField("ip_clk_frequency_Hz", "IP clock frequency Hz", "100000000"),
        DriverConfigField("Tristate_HB1", "Tristate HB1", "false", input_type="choice", options=BOOL_LITERAL_OPTIONS),
        DriverConfigField("Tristate_HB2", "Tristate HB2", "false", input_type="choice", options=BOOL_LITERAL_OPTIONS),
        DriverConfigField("Tristate_HB3", "Tristate HB3", "false", input_type="choice", options=BOOL_LITERAL_OPTIONS),
        DriverConfigField(
            "min_pulse_width_in_microseconds",
            "Minimum pulse width us",
            "UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US + UZ_PWM_DEADTIME_IN_US",
        ),
        DriverConfigField("PWM_freq_Hz", "PWM frequency Hz", "UZ_PWM_FREQUENCY"),
        DriverConfigField(
            "PWM_mode",
            "PWM mode",
            "normalized_input_via_AXI",
            input_type="choice",
            options=PWM_2L_MODE_OPTIONS,
        ),
        DriverConfigField("PWM_en", "PWM enable", "true", input_type="choice", options=BOOL_LITERAL_OPTIONS),
        DriverConfigField(
            "use_external_counter",
            "Use external counter",
            "true",
            input_type="choice",
            options=BOOL_LITERAL_OPTIONS,
        ),
        DriverConfigField("init_dutyCyc_HB1", "Initial duty HB1", "0.0f"),
        DriverConfigField("init_dutyCyc_HB2", "Initial duty HB2", "0.0f"),
        DriverConfigField("init_dutyCyc_HB3", "Initial duty HB3", "0.0f"),
        DriverConfigField("triangle_shift_HB1", "Triangle shift HB1", "0.0f"),
        DriverConfigField("triangle_shift_HB2", "Triangle shift HB2", "0.0f"),
        DriverConfigField("triangle_shift_HB3", "Triangle shift HB3", "0.0f"),
        DriverConfigField(
            "trigger_source",
            "Trigger source",
            "trigger_at_MIN",
            input_type="choice",
            options=PWM_2L_TRIGGER_SOURCE_OPTIONS,
        ),
    ]


def deadtime_2l_config_fields() -> list[DriverConfigField]:
    return [
        DriverConfigField("clock_frequency_MHz", "Clock frequency MHz", "100"),
        DriverConfigField("deadtime_us", "Deadtime us", "UZ_PWM_DEADTIME_IN_US"),
        DriverConfigField(
            "inverse_bottom_switch",
            "Inverse bottom switch",
            "false",
            input_type="choice",
            options=BOOL_LITERAL_OPTIONS,
        ),
    ]


def pwm_3l_config_fields() -> list[DriverConfigField]:
    return [
        DriverConfigField("enable", "Enable", "1"),
        DriverConfigField("mode", "Mode", "0"),
        DriverConfigField("carrier_frequency_Hz", "Carrier frequency Hz", "data->av.pwm_frequency_hz"),
        DriverConfigField("minimum_pulse_width", "Minimum pulse width", "0.01f"),
        DriverConfigField("initial_duty_a", "Initial duty A", "data->rasv.halfBridge1DutyCycle"),
        DriverConfigField("initial_duty_b", "Initial duty B", "data->rasv.halfBridge2DutyCycle"),
        DriverConfigField("initial_duty_c", "Initial duty C", "data->rasv.halfBridge3DutyCycle"),
        DriverConfigField("tristate_a", "Tristate A", "0"),
        DriverConfigField("tristate_b", "Tristate B", "0"),
        DriverConfigField("tristate_c", "Tristate C", "0"),
    ]


def config_int(value: str, default: int, minimum: int, maximum: int) -> int:
    try:
        parsed = int(str(value))
    except (TypeError, ValueError):
        parsed = default
    return max(minimum, min(maximum, parsed))


def config_bool(value: object, default: bool = False) -> bool:
    if value is None:
        return default
    if isinstance(value, bool):
        return value
    return str(value).strip().lower() in {"1", "true", "yes", "on"}


def normalize_visualization_routes(visualization_signals: object) -> dict[str, str]:
    if visualization_signals is None:
        return {}
    if isinstance(visualization_signals, dict):
        routes: dict[str, str] = {}
        for signal_id, route in visualization_signals.items():
            normalized_route = str(route).strip().lower()
            if normalized_route in {"javascope", "slow_data", "both"}:
                routes[str(signal_id)] = normalized_route
        return routes
    return {str(signal_id): "javascope" for signal_id in visualization_signals}


def pwm_2l_state_isr_actions(instance_count: int, hardware_config: dict[str, str]) -> dict[str, list[str]]:
    behavior = hardware_config.get("pwm_2l_idle_error_behavior", "tristate_with_duty_cycle")
    enable_tristate = behavior == "tristate_with_duty_cycle"
    duty_values = [
        hardware_config.get("pwm_2l_idle_error_duty_hb1", "0.0f") or "0.0f",
        hardware_config.get("pwm_2l_idle_error_duty_hb2", "0.0f") or "0.0f",
        hardware_config.get("pwm_2l_idle_error_duty_hb3", "0.0f") or "0.0f",
    ]
    idle_error_lines: list[str] = []
    running_lines: list[str] = []
    for index in range(instance_count):
        half_bridge_base = index * 3 + 1
        for offset, duty_value in enumerate(duty_values):
            half_bridge = half_bridge_base + offset
            idle_error_lines.append(f"Global_Data.rasv.halfBridge{half_bridge}DutyCycle = {duty_value};")
        if enable_tristate:
            idle_error_lines.append(
                f"uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_{index}, true, true, true);"
            )
            running_lines.append(
                f"uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_{index}, false, false, false);"
            )
    return {
        "idle_state": list(idle_error_lines),
        "running_state": running_lines,
        "control_state": [],
        "error_state": list(idle_error_lines),
    }


def project_wizard_pwm_runtime_lines() -> list[str]:
    return ["    project_wizard_update_pwm_outputs(&Global_Data);"]


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


def dac8831_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    return [
        VisualizationSignal(
            signal_id=f"dac8831_{slot_lower}_ch{channel}",
            slot=slot,
            label=f"{slot} DAC8831 output channel {channel}",
            enum_name=f"JSO_DAC8831_{slot}_CH{channel}",
            pointer_expression=f"&data->av.dac8831_{slot_lower}_ch{channel}",
        )
        for channel in range(8)
    ]


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


def patch_platform_state_isr_actions(path: Path, state_isr_actions: dict[str, list[str]]) -> None:
    text = path.read_text(encoding="utf-8")
    for state_name in ["idle_state", "running_state", "control_state", "error_state"]:
        lines = [f"        {line.strip()}" for line in state_isr_actions.get(state_name, [])]
        text = replace_block(text, FILE_MARKERS[f"{state_name}_isr_actions"], lines)
    path.write_text(text, encoding="utf-8")


def patch_javascope_header(path: Path, observable_enums: list[str], slowdata_enums: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_block(text, FILE_MARKERS["javascope_observables"], observable_enums)
    text = replace_block(text, FILE_MARKERS["javascope_slowdata"], slowdata_enums)
    path.write_text(text, encoding="utf-8")


def patch_javascope_source(path: Path, observable_pointers: list[str], slowdata_pointers: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_block(text, FILE_MARKERS["javascope_observable_pointers"], observable_pointers)
    text = replace_block(text, FILE_MARKERS["javascope_slowdata_pointers"], slowdata_pointers)
    path.write_text(text, encoding="utf-8")


def hardware_revision_define_value(platform_revision: str) -> str:
    match = re.search(r"(\d+)", platform_revision)
    if not match:
        return "4U"
    return f"{int(match.group(1))}U"


def patch_hardware_revision(path: Path, platform_revision: str) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_block(
        text,
        FILE_MARKERS["hardware_version"],
        [f"#define UZ_HARDWARE_VERSION {hardware_revision_define_value(platform_revision)}"],
    )
    path.write_text(text, encoding="utf-8")


def patch_pwm_global_defines(path: Path, hardware_config: dict[str, str]) -> None:
    text = path.read_text(encoding="utf-8")
    production_text, separator, test_text = text.partition("\n// Configuration defines for the number of used instances for testing")
    for config_key, define in PWM_GLOBAL_DEFINE_KEYS.items():
        value = hardware_config.get(config_key, "").strip()
        if not value:
            continue
        pattern = re.compile(rf"^#define\s+{re.escape(define)}\s+\S+", re.MULTILINE)
        production_text, replacements = pattern.subn(f"#define {define:<40} {value}", production_text, count=1)
        if replacements != 1:
            raise MarkerError(f"Could not find {define} in {path}.")
    path.write_text(production_text + separator + test_text, encoding="utf-8")


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
        ("position_raw_single_turn", "POS_RAW_ST", "position raw single turn", "uint32"),
        ("position_raw_multi_turn", "POS_RAW_MT", "position raw multi turn", "uint32"),
        ("position_multi_turn", "POS_MT", "position multi turn", "uint32"),
        ("position_mech_si_single_turn", "POS_MECH_ST", "position mech SI single turn", "float"),
        ("position_el_si_single_turn", "POS_EL_ST", "position el SI single turn", "float"),
        ("speed_mech_si", "SPEED_MECH_SI", "speed mech SI", "float"),
        ("speed_el_si", "SPEED_EL_SI", "speed el SI", "float"),
        ("speed_mech_rpm", "SPEED_MECH_RPM", "speed mech rpm", "float"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"{base_id}_{field}",
            slot=slot,
            label=f"{label_base} {label}",
            enum_name=f"{enum_base}_{enum_suffix}",
            pointer_expression=f"&data->av.{base_id}_{field}",
            source_type=source_type,
        )
        for field, enum_suffix, label, source_type in fields
    ]


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


def incremental_encoder_visualization_signals(slot_lower: str, channel: int) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    base_id = f"incremental_encoder_{slot_lower}_{channel}"
    enum_base = f"JSO_INCREMENTAL_ENCODER_{slot}_CH{channel}"
    label_base = f"{slot} incremental encoder channel {channel}"
    fields = [
        ("theta_el", "THETA_EL", "electrical angle", "float"),
        ("omega_mech", "OMEGA_MECH", "mechanical speed", "float"),
        ("omega_mech_ma_n4", "OMEGA_MECH_MA_N4", "mechanical speed moving average N4", "float"),
        ("position", "POSITION", "position", "uint32"),
        ("position_w_offset", "POSITION_W_OFFSET", "position with offset", "uint32"),
        ("index_found", "INDEX_FOUND", "index found", "uint32"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"{base_id}_{field}",
            slot=slot,
            label=f"{label_base} {label}",
            enum_name=f"{enum_base}_{enum_suffix}",
            pointer_expression=f"&data->av.{base_id}_{field}",
            source_type=source_type,
        )
        for field, enum_suffix, label, source_type in fields
    ]


def resolver_channel_count(slot: str) -> int:
    return 2 if slot == "D5" else 3


def d_slot_index(slot: str) -> int:
    try:
        return int(slot[1:])
    except (TypeError, ValueError):
        return 1


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


def resolver_ip_visualization_signals(slot_lower: str, channel: int) -> list[VisualizationSignal]:
    base_id = f"resolver_ip_{slot_lower}_{channel}"
    slot = slot_lower.upper()
    label_base = f"{slot} resolver IP channel {channel}"
    enum_base = f"JSO_RESOLVER_IP_{slot}_CH{channel}"
    fields = [
        ("position_mech_2pi", "POSITION_MECH_2PI", "position mech 2pi"),
        ("position_el_2pi", "POSITION_EL_2PI", "position el 2pi"),
        ("omega_mech_rad_s", "OMEGA_MECH_RAD_S", "omega mech rad/s"),
        ("n_mech_rpm", "N_MECH_RPM", "n mech rpm"),
        ("omega_el_rad_s", "OMEGA_EL_RAD_S", "omega el rad/s"),
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


def resolver_pl_interface_visualization_signals(slot_lower: str, channel: int) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    base_id = f"resolver_pl_interface_{slot_lower}_{channel}"
    enum_base = f"JSO_RESOLVER_PL_{slot}_CH{channel}"
    label_base = f"{slot} resolver PL interface channel {channel}"
    fields = [
        ("position_mech_2pi", "POS_MECH_2PI", "mechanical position", "float"),
        ("position_el_2pi", "POS_EL_2PI", "electrical position", "float"),
        ("omega_mech_rad_s", "OMEGA_MECH_RAD_S", "mechanical speed rad/s", "float"),
        ("n_mech_rpm", "N_MECH_RPM", "mechanical speed rpm", "float"),
        ("omega_el_rad_s", "OMEGA_EL_RAD_S", "electrical speed rad/s", "float"),
        ("revolution_counter", "REVOLUTION_COUNTER", "revolution counter", "int32"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"{base_id}_{field}",
            slot=slot,
            label=f"{label_base} {label}",
            enum_name=f"{enum_base}_{enum_suffix}",
            pointer_expression=f"&data->av.{base_id}_{field}",
            source_type=source_type,
        )
        for field, enum_suffix, label, source_type in fields
    ]


def io_card_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    return [
        VisualizationSignal(
            signal_id=f"io_card_{slot_lower}_pin_{pin:02d}",
            slot=slot,
            label=f"{slot} IO pin {pin:02d}",
            enum_name=f"JSO_IO_CARD_{slot}_PIN_{pin:02d}",
            pointer_expression=f"&data->av.io_card_{slot_lower}_state",
            source_expression=f"((data->av.io_card_{slot_lower}_state >> {pin}U) & 0x1U)",
            source_type="uint32",
        )
        for pin in range(30)
    ]


def io_card_needs_axi(card: dict[str, object], option_values: dict[str, str]) -> bool:
    directions = io_card_directions(card, option_values)
    default_modes = card.get("vivado", {}).get("io_card", {}).get("default_modes", {})
    if not isinstance(default_modes, dict):
        default_modes = {}
    for index, direction in enumerate(directions):
        mode = option_values.get(f"io_pin_{index:02d}_mode", str(default_modes.get(direction, "axi_gpio")))
        if direction == "rx" and mode not in {"axi_gpio", "top_level"}:
            mode = "axi_gpio"
        if direction == "tx" and mode not in {"axi_gpio", "source_pin", "pwm", "constant"}:
            mode = "axi_gpio"
        if mode == "axi_gpio":
            return True
    return False


def io_card_direction_mask(card: dict[str, object], option_values: dict[str, str]) -> int:
    directions = io_card_directions(card, option_values)
    mask = 0
    for index, direction in enumerate(directions):
        if direction == "rx":
            mask |= 1 << index
    return mask


def io_card_directions(card: dict[str, object], option_values: dict[str, str]) -> list[str]:
    io_card = card.get("vivado", {}).get("io_card", {})
    if not isinstance(io_card, dict):
        return []
    kind = str(io_card.get("kind", ""))
    pin_count = config_int(str(io_card.get("pin_count", "30")), default=30, minimum=1, maximum=30)
    variant_directions = io_card_variant_directions(io_card, option_values)
    if variant_directions:
        return variant_directions[:pin_count]
    if kind == "voltage_grouped":
        directions: list[str] = []
        groups = io_card.get("groups", [])
        if not isinstance(groups, list):
            return ["rx"] * pin_count
        for group_index, group in enumerate(groups, start=1):
            if not isinstance(group, dict):
                continue
            width = config_int(str(group.get("width", "0")), default=0, minimum=0, maximum=30)
            direction = option_values.get(f"direction_group_{group_index}", str(group.get("default", "rx")))
            directions.extend([direction if direction in {"tx", "rx"} else "rx"] * width)
        return directions[:pin_count]
    return ["rx"] * pin_count


def io_card_variant_directions(io_card: dict[str, object], option_values: dict[str, str]) -> list[str]:
    variant = selected_io_card_variant(io_card, option_values)
    if not variant:
        return []
    directions: list[str] = []
    for group in variant.get("directions", []):
        if not isinstance(group, dict):
            continue
        direction = str(group.get("direction", "rx")).strip().lower()
        if direction not in {"tx", "rx"}:
            direction = "rx"
        width = config_int(str(group.get("width", "0")), default=0, minimum=0, maximum=30)
        directions.extend([direction] * width)
    return directions


def selected_io_card_variant(io_card: dict[str, object], option_values: dict[str, str]) -> dict[str, object] | None:
    variants = io_card.get("variants", [])
    if not isinstance(variants, list) or not variants:
        return None
    option_id = str(io_card.get("variant_option", "io_variant"))
    selected_id = option_values.get(option_id, str(io_card.get("default_variant", "")))
    for variant in variants:
        if isinstance(variant, dict) and str(variant.get("id", "")) == selected_id:
            return variant
    first = variants[0]
    return first if isinstance(first, dict) else None


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


def adc_max11331_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    return [
        VisualizationSignal(
            signal_id=f"adc_max11331_{slot_lower}_ch{channel}",
            slot=slot,
            label=f"{slot} ADC MAX11331 channel {channel}",
            enum_name=f"JSO_ADC_MAX11331_{slot}_CH{channel}",
            pointer_expression=f"&data->av.adc_max11331_{slot_lower}_ch{channel}",
        )
        for channel in range(24)
    ]


def adc_max11331_actual_values(slot_lower: str) -> list[str]:
    return [f"\tfloat adc_max11331_{slot_lower}_ch{channel};" for channel in range(24)]


def inverter_adapter_visualization_signals(slot_lower: str) -> list[VisualizationSignal]:
    slot = slot_lower.upper()
    fields = [
        ("pwm_duty_h1", "PWMdutyCycNormalized_H1", "PWM duty H1", "PWM_DUTY_H1", "float"),
        ("pwm_duty_l1", "PWMdutyCycNormalized_L1", "PWM duty L1", "PWM_DUTY_L1", "float"),
        ("pwm_duty_h2", "PWMdutyCycNormalized_H2", "PWM duty H2", "PWM_DUTY_H2", "float"),
        ("pwm_duty_l2", "PWMdutyCycNormalized_L2", "PWM duty L2", "PWM_DUTY_L2", "float"),
        ("pwm_duty_h3", "PWMdutyCycNormalized_H3", "PWM duty H3", "PWM_DUTY_H3", "float"),
        ("pwm_duty_l3", "PWMdutyCycNormalized_L3", "PWM duty L3", "PWM_DUTY_L3", "float"),
        ("chip_temp_h1", "ChipTempDegreesCelsius_H1", "chip temperature H1", "CHIP_TEMP_H1", "float"),
        ("chip_temp_l1", "ChipTempDegreesCelsius_L1", "chip temperature L1", "CHIP_TEMP_L1", "float"),
        ("chip_temp_h2", "ChipTempDegreesCelsius_H2", "chip temperature H2", "CHIP_TEMP_H2", "float"),
        ("chip_temp_l2", "ChipTempDegreesCelsius_L2", "chip temperature L2", "CHIP_TEMP_L2", "float"),
        ("chip_temp_h3", "ChipTempDegreesCelsius_H3", "chip temperature H3", "CHIP_TEMP_H3", "float"),
        ("chip_temp_l3", "ChipTempDegreesCelsius_L3", "chip temperature L3", "CHIP_TEMP_L3", "float"),
        ("oc", "OC", "OC status word", "OC", "uint32"),
        ("oc_h1", "OC_H1", "OC H1", "OC_H1", "bool"),
        ("oc_l1", "OC_L1", "OC L1", "OC_L1", "bool"),
        ("oc_h2", "OC_H2", "OC H2", "OC_H2", "bool"),
        ("oc_l2", "OC_L2", "OC L2", "OC_L2", "bool"),
        ("oc_h3", "OC_H3", "OC H3", "OC_H3", "bool"),
        ("oc_l3", "OC_L3", "OC L3", "OC_L3", "bool"),
        ("fault", "FAULT", "FAULT status word", "FAULT", "uint32"),
        ("fault_h1", "FAULT_H1", "FAULT H1", "FAULT_H1", "bool"),
        ("fault_l1", "FAULT_L1", "FAULT L1", "FAULT_L1", "bool"),
        ("fault_h2", "FAULT_H2", "FAULT H2", "FAULT_H2", "bool"),
        ("fault_l2", "FAULT_L2", "FAULT L2", "FAULT_L2", "bool"),
        ("fault_h3", "FAULT_H3", "FAULT H3", "FAULT_H3", "bool"),
        ("fault_l3", "FAULT_L3", "FAULT L3", "FAULT_L3", "bool"),
        ("i_diag", "I_DIAG", "I_DIAG status word", "I_DIAG", "uint32"),
        ("i_dc_diag", "I_DC_DIAG", "I DC diagnostic", "I_DC_DIAG", "bool"),
        ("i1_diag", "I1_DIAG", "I1 diagnostic", "I1_DIAG", "bool"),
        ("i2_diag", "I2_DIAG", "I2 diagnostic", "I2_DIAG", "bool"),
        ("i3_diag", "I3_DIAG", "I3 diagnostic", "I3_DIAG", "bool"),
    ]
    return [
        VisualizationSignal(
            signal_id=f"inverter_adapter_{slot_lower}_{signal_suffix}",
            slot=slot,
            label=f"{slot} inverter adapter {label}",
            enum_name=f"JSO_INVERTER_ADAPTER_{slot}_{enum_suffix}",
            pointer_expression=f"&data->av.inverter_adapter_{slot_lower}.{field_name}",
            source_type=source_type,
        )
        for signal_suffix, field_name, label, enum_suffix, source_type in fields
    ]


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


def resolve_base_address_macro(
    source_dir: Path,
    slot: str,
    interface: str,
    channel: int | None = None,
    search_xparameters: bool = True,
) -> tuple[str, str]:
    slot_lower = slot.lower()
    if interface == "temperature":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_TEMPERATURE_CARD_INT_0_BASEADDR"
        search_terms = ["TEMP", "TEMPERATURE"]
    elif interface == "adc_ltc2311":
        fallback = f"XPAR_UZ_ANALOG_ADAPTER_{slot.upper()}_ADAPTER_{slot.upper()}_ADC_LTC2311_S00_AXI_BASEADDR"
        search_terms = ["ADC_LTC2311", "ADCLTC2311", "LTC2311"]
    elif interface == "adc_max11331":
        fallback = f"XPAR_UZ_ANALOG_ADAPTER_{slot.upper()}_ADAPTER_{slot.upper()}_ADC_MAX11331_BASEADDR"
        search_terms = ["ADC_MAX11331", "ADCMAX11331", "MAX11331"]
    elif interface == "dac8831":
        fallback = f"XPAR_UZ_ANALOG_ADAPTER_{slot.upper()}_ADAPTER_{slot.upper()}_DAC8831_BASEADDR"
        search_terms = ["DAC8831", "DAC_SPI", "DAC"]
    elif interface == "inverter_adapter":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_UZ_D_INVERTER_ADAPTER_{slot.upper()}_BASEADDR"
        search_terms = ["INVERTER_ADAPTER", "UZ_D_INVERTER", "INVERTER"]
    elif interface == "incremental_encoder":
        if channel is None:
            fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_INCREMENTAL_ENCODER_{slot.upper()}_BASEADDR"
        else:
            fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_INCREMENTAL_ENCODER_{slot.upper()}_{channel}_BASEADDR"
        search_terms = ["INCREMENTAL_ENCODER", "INCREMENTAL", "ENCODER"]
    elif interface == "resolver_ip":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_RESOLVER_IP_{slot.upper()}_{channel}_BASEADDR"
        search_terms = ["RESOLVER_IP", "RESOLVER_INTERFACE", "RESOLVER"]
    elif interface == "resolver_pl_interface":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_RESOLVER_PL_INTERFACE_{slot.upper()}_{channel}_BASEADDR"
        search_terms = ["RESOLVER_PL_INTERFACE", "RESOLVER_PL"]
    elif interface == "endat":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_UZ_ENDAT_INTERFACE_{slot.upper()}_CHANNEL_{channel}_BASEADDR"
        search_terms = ["ENDAT"]
    elif interface == "ssi":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_UZ_SSI_INTERFACE_{slot.upper()}_CHANNEL_{channel}_BASEADDR"
        search_terms = ["SSI"]
    elif interface == "axi_gpio":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_AXI_GPIO_{slot.upper()}_BASEADDR"
        search_terms = ["AXI_GPIO"]
    else:
        fallback = f"XPAR_{slot.upper()}_BASEADDR"
        search_terms = [interface.upper()]
    if not search_xparameters:
        return fallback, ""
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
        channel_markers = [
            f"CHANNEL_{channel}",
            f"_{slot.upper()}_{channel}_BASEADDR",
            f"_{channel}_BASEADDR",
        ]
        channel_candidates = [candidate for candidate in slot_candidates if any(marker in candidate for marker in channel_markers)]
        if channel_candidates:
            return channel_candidates[0], ""
        if interface == "incremental_encoder" and channel == 1:
            legacy_candidates = [candidate for candidate in slot_candidates if f"_{slot.upper()}_BASEADDR" in candidate]
            if legacy_candidates:
                return legacy_candidates[0], ""
        return fallback, f"{slot}: no channel {channel} {interface} BASEADDR macro found in {xparameters}. Using fallback {fallback}."
    if slot_candidates:
        return slot_candidates[0], ""
    if interface == "axi_gpio":
        return fallback, f"{slot}: no slot-specific {interface} BASEADDR macro found in {xparameters}. Using fallback {fallback}."
    if candidates:
        return candidates[0], f"{slot}: no slot-specific {interface} BASEADDR macro found. Using {candidates[0]} from {xparameters}."
    return fallback, f"{slot}: no {interface} BASEADDR macro found in {xparameters}. Using fallback {fallback}."


def resolve_device_id_macro(
    source_dir: Path,
    slot: str,
    interface: str,
    search_xparameters: bool = True,
) -> tuple[str, str]:
    if interface == "axi_gpio":
        fallback = f"XPAR_UZ_DIGITAL_ADAPTER_{slot.upper()}_ADAPTER_AXI_GPIO_{slot.upper()}_DEVICE_ID"
        search_terms = ["AXI_GPIO"]
    else:
        fallback = f"XPAR_{slot.upper()}_DEVICE_ID"
        search_terms = [interface.upper()]
    if not search_xparameters:
        return fallback, ""
    xparameters = find_xparameters(source_dir)
    if xparameters is None:
        return fallback, f"{slot}: xparameters.h not found. Using fallback device-id macro {fallback}."
    text = xparameters.read_text(encoding="utf-8", errors="ignore")
    macros = tuple(re.findall(r"^#define\s+(XPAR_[A-Z0-9_]*DEVICE_ID)\b", text, re.MULTILINE))
    candidates = [macro for macro in macros if any(term in macro for term in search_terms)]
    slot_candidates = [candidate for candidate in candidates if slot.upper() in candidate]
    if slot_candidates:
        return slot_candidates[0], ""
    if interface == "axi_gpio":
        return fallback, f"{slot}: no slot-specific {interface} DEVICE_ID macro found in {xparameters}. Using fallback {fallback}."
    if candidates:
        return candidates[0], f"{slot}: no slot-specific {interface} DEVICE_ID macro found. Using {candidates[0]} from {xparameters}."
    return fallback, f"{slot}: no {interface} DEVICE_ID macro found in {xparameters}. Using fallback {fallback}."


def resolve_pwm_base_address_macro(
    source_dir: Path, interface: str, index: int, search_xparameters: bool = True
) -> tuple[str, str]:
    if interface == "pwm_2l":
        fallback = f"XPAR_UZ_PWM_PWM_2L_PWM_AND_SS_CONTROL_V_{index}_BASEADDR"
        required_terms = ["UZ_PWM", "PWM_2L", "PWM_AND_SS_CONTROL_V"]
    elif interface == "deadtime_2l":
        fallback = f"XPAR_UZ_PWM_PWM_2L_UZ_INTERLOCKDEADTIME_{index}_BASEADDR"
        required_terms = ["UZ_PWM", "PWM_2L", "UZ_INTERLOCKDEADTIME"]
    elif interface == "pwm_3l":
        fallback = "XPAR_UZ_PWM_PWM_3L_PWM_SS_3L_IP_0_BASEADDR"
        required_terms = ["UZ_PWM", "PWM_3L", "PWM_SS_3L_IP"]
    else:
        fallback = f"XPAR_UZ_PWM_{interface.upper()}_{index}_BASEADDR"
        required_terms = ["UZ_PWM", interface.upper()]
    if not search_xparameters:
        return fallback, ""

    xparameters, macros = xparameter_baseaddr_macros(source_dir)
    if xparameters is None:
        return fallback, f"PWM: xparameters.h not found. Using fallback base-address macro {fallback}."

    indexed_suffix = f"_{index}_BASEADDR"
    candidates = [
        macro
        for macro in macros
        if all(term in macro for term in required_terms) and macro.endswith(indexed_suffix)
    ]
    if candidates:
        return candidates[0], ""

    return fallback, f"PWM: no {interface} BASEADDR macro for instance {index} found in {xparameters}. Using fallback {fallback}."


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
    candidates = [
        source_dir / "xparameters.h",
        source_dir / "include" / "xparameters.h",
        source_dir / "xilinx" / "xparameters.h",
    ]
    for parent in source_dir.parents:
        if parent.name.lower() not in {"baremetal", "software"}:
            continue
        candidates.extend(
            [
                parent / "src" / "xparameters.h",
                parent / "src" / "include" / "xparameters.h",
                parent / "include" / "xparameters.h",
            ]
        )
        if parent.name.lower() == "software":
            vitis_root = parent.parent
            workspace_root = vitis_root / "workspace"
            candidates.extend(
                sorted(
                    workspace_root.glob(
                        "*/psu_cortexr5_0/Baremetal_domain/bsp/psu_cortexr5_0/include/xparameters.h"
                    )
                )
            )
            candidates.extend(
                sorted(
                    workspace_root.glob(
                        "*/export/*/sw/*/Baremetal_domain/bspinclude/include/xparameters.h"
                    )
                )
            )
    seen: set[Path] = set()
    for candidate in candidates:
        if candidate in seen:
            continue
        seen.add(candidate)
        if candidate.exists() and "test" not in {part.lower() for part in candidate.parts}:
            return candidate
    return None


def clear_xparameters_cache() -> None:
    xparameter_baseaddr_macros.cache_clear()
    find_xparameters.cache_clear()
