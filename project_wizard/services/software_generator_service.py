from __future__ import annotations

from pathlib import Path

from ..models import ResolvedAnalogDataMover, ResolvedSystemModel, VisualizationSignal
from ..repositories import CardDatabase
from ..template_renderer import SimpleTemplateRenderer
from .software_models import (
    PWM_GLOBAL_DEFINE_KEYS,
    SLOTS,
    DriverConfigField,
    DriverConfigInstance,
    SlotSoftwareContent,
    SoftwareGenerationResult,
    SoftwarePlan,
)
from .software_analog import (
    adc_ltc2311_actual_values,
    adc_ltc2311_context,
    adc_ltc2311_isr_lines,
    adc_max11331_actual_values,
    adc_max11331_context,
    adc_max11331_isr_lines,
    analog_adc_packed_offsets,
    dac8831_active_channels,
    dac8831_context,
    dac8831_rasv_initializers,
    dac8831_reference_and_set_values,
)
from .software_driver_config import driver_instance_values
from .software_digital import (
    encoder_actual_values,
    encoder_isr_lines,
    endat_main_init,
    incremental_encoder_actual_values,
    incremental_encoder_context,
    incremental_encoder_isr_lines,
    incremental_encoder_main_init,
    inverter_adapter_actual_values,
    inverter_adapter_context,
    inverter_adapter_isr_lines,
    inverter_adapter_main_init,
    inverter_adapter_state_actions,
    resolver_channel_count,
    resolver_ip_actual_values,
    resolver_ip_context,
    resolver_ip_isr_lines,
    resolver_ip_main_init,
    resolver_pl_interface_actual_values,
    resolver_pl_interface_context,
    resolver_pl_interface_enabled,
    resolver_pl_interface_isr_lines,
    resolver_pl_interface_main_init,
    serial_encoder_context,
    ssi_main_init,
)
from .software_patcher import apply_software_plan, hardware_revision_define_value
from .software_pwm import (
    build_project_wizard_pwm_context,
    deadtime_2l_config_fields,
    half_bridge_duty_cycle_fields,
    half_bridge_duty_cycle_initializers,
    project_wizard_pwm_runtime_lines,
    pwm_2l_config_fields,
    pwm_2l_state_isr_actions,
    pwm_3l_config_fields,
)
from .software_visualization import build_software_visualization_fragments, normalize_visualization_routes
from .software_temperature_io import (
    axi_gpio_actual_values,
    axi_gpio_context,
    axi_gpio_isr_lines,
    axi_gpio_isr_user_block,
    axi_gpio_main_init,
    temperature_actual_values,
    temperature_configdata_a,
    temperature_context,
    temperature_isr_lines,
    temperature_main_init,
)
from .visualization_catalog import (
    adc_ltc2311_visualization_signals,
    adc_max11331_visualization_signals,
    config_int,
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
from .xparameters import (
    clear_xparameters_cache,
)


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

    def _build_plan_from_values(
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
        analog_datamover: ResolvedAnalogDataMover | None = None,
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
        reference_and_set_values: list[str] = []
        objects: list[str] = []
        adc_readout_definitions: list[str] = []
        adc_readout: list[str] = []
        main_init: list[str] = []
        main_rasv_initializer: list[str] = []
        isr_control_by_slot: dict[str, list[str]] = {slot: [] for slot in SLOTS}
        isr_user_blocks_by_slot: dict[str, list[str]] = {slot: [] for slot in SLOTS}
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
        if analog_datamover is None:
            analog_adc_offsets = analog_adc_packed_offsets(assignments)
            datamover_array_length = max(2, sum(stream["channel_count"] for stream in analog_adc_offsets.values()))
        else:
            analog_adc_offsets = {
                stream.slot: {
                    "offset": stream.packed_offset,
                    "channel_count": stream.channel_count,
                }
                for stream in analog_datamover.streams
            }
            datamover_array_length = analog_datamover.channel_count
        endat_instances = 0
        ssi_instances = 0
        pwm_2l_instance_count = config_int(hardware_config.get("pwm_2l_instances", "4"), default=4, minimum=1, maximum=10)
        pwm_3l_enabled = config_int(hardware_config.get("pwm_3l_instances", "1"), default=1, minimum=0, maximum=1) > 0
        reference_and_set_values.extend(half_bridge_duty_cycle_fields(pwm_2l_instance_count, pwm_3l_enabled))
        main_rasv_initializer.extend(half_bridge_duty_cycle_initializers(pwm_2l_instance_count, pwm_3l_enabled))
        state_isr_actions.update(pwm_2l_state_isr_actions(pwm_2l_instance_count, hardware_config))
        pwm_context = build_project_wizard_pwm_context(
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

        for slot in SLOTS:
            mode = software_modes.get(slot, "follow_hardware")
            card_id = assignments.get(slot, "empty") if mode == "follow_hardware" else "empty"
            if card_id == "analog_ltc2311_16":
                adc_ltc2311_instances += 1
                context = adc_ltc2311_context(
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
                context = adc_max11331_context(
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
                context = dac8831_context(
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
                reference_and_set_values.extend(
                    dac8831_reference_and_set_values(str(context["slot_lower"]), context)
                )
                main_rasv_initializer.extend(dac8831_rasv_initializers(str(context["slot_lower"]), context))
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
                available_visualization_signals.extend(
                    dac8831_visualization_signals(
                        str(context["slot_lower"]),
                        dac8831_active_channels(context),
                    )
                )
            elif card_id == "uz_d_inverter_adapter":
                inverter_adapter_instances += 1
                context = inverter_adapter_context(
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
                actual_values.extend(inverter_adapter_actual_values(str(context["slot_lower"])))
                main_init.extend(inverter_adapter_main_init(str(context["slot_lower"])))
                for state_name, actions in inverter_adapter_state_actions(str(context["slot_lower"])).items():
                    state_isr_actions[state_name].extend(actions)
                isr_control_by_slot[slot].extend(inverter_adapter_isr_lines(str(context["slot_lower"])))
                available_visualization_signals.extend(inverter_adapter_visualization_signals(str(context["slot_lower"])))
            elif card_id == "uz_d_temperature_ltc2983":
                temperature_instances += 1
                preset = software_presets.get(slot, "default")
                context = temperature_context(
                    slot,
                    source_dir,
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
                actual_values.extend(temperature_actual_values(str(context["slot_lower"])))
                objects.append(f"\tuz_temperaturecard_t* temperature_card_{context['slot_lower']};")
                main_init.extend(temperature_main_init(str(context["slot_lower"])))
                isr_control_by_slot[slot].extend(temperature_isr_lines(str(context["slot_lower"])))
                available_visualization_signals.extend(temperature_visualization_signals(str(context["slot_lower"]), preset))
            elif card_id == "uz_d_incremental_encoder":
                slot_options = option_values.get(slot, {})
                for channel_index in range(1, 4):
                    if slot_options.get(f"channel_{channel_index}", "incremental_encoder") == "none":
                        continue
                    incremental_encoder_instances += 1
                    context = incremental_encoder_context(
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
                    _extend_unique(slot_content[slot].header_includes, header_includes)
                    slot_content[slot].header_prototypes.extend(header_prototypes)
                    slot_content[slot].source_definitions.append(
                        self.renderer.render_file(self.driver_template("uz_incrementalEncoder", "source"), context).rstrip()
                    )
                    objects.append(f"\tuz_incrementalEncoder_t* incremental_encoder_{context['slot_lower']}_{channel_index};")
                    actual_values.extend(incremental_encoder_actual_values(str(context["slot_lower"]), channel_index))
                    main_init.extend(incremental_encoder_main_init(str(context["slot_lower"]), channel_index))
                    isr_control_by_slot[slot].extend(incremental_encoder_isr_lines(context))
                    available_visualization_signals.extend(
                        incremental_encoder_visualization_signals(str(context["slot_lower"]), channel_index)
                    )
            elif card_id == "uz_d_resolver":
                channel_count = resolver_channel_count(slot)
                slot_options = option_values.get(slot, {})
                for channel_index in range(1, channel_count + 1):
                    resolver_ip_instances += 1
                    resolver_context = resolver_ip_context(
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
                    main_init.extend(resolver_ip_main_init(str(resolver_context["slot_lower"]), channel_index))
                    if resolver_pl_interface_enabled(slot_options, channel_index):
                        resolver_pl_interface_instances += 1
                        pl_context = resolver_pl_interface_context(
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
                        main_init.extend(resolver_pl_interface_main_init(str(pl_context["slot_lower"]), channel_index))
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
                    context = axi_gpio_context(slot, source_dir, card, slot_options, resolve_base_addresses)
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
                    input_pins = list(context["axi_input_pins"])
                    output_pins = list(context["axi_output_pins"])
                    actual_values.extend(axi_gpio_actual_values(str(context["slot_lower"]), input_pins))
                    main_init.extend(axi_gpio_main_init(str(context["slot_lower"])))
                    isr_control_by_slot[slot].extend(axi_gpio_isr_lines(str(context["slot_lower"]), input_pins, output_pins))
                    isr_user_blocks_by_slot[slot].extend(
                        axi_gpio_isr_user_block(str(context["slot_lower"]), output_pins)
                    )
                    available_visualization_signals.extend(
                        io_card_visualization_signals(str(context["slot_lower"]), card, slot_options)
                    )
            elif card_id == "uz_d_absolute_encoder":
                for channel_index in range(1, 4):
                    option_id = f"channel_{channel_index}"
                    interface = option_values.get(slot, {}).get(option_id, "none")
                    if interface == "endat":
                        endat_instances += 1
                        context = serial_encoder_context(
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
                        main_init.extend(endat_main_init(str(context["slot_lower"]), channel_index))
                        isr_control_by_slot[slot].extend(
                            encoder_isr_lines("endat", "endat_encoder", str(context["slot_lower"]), channel_index)
                        )
                        available_visualization_signals.extend(
                            encoder_visualization_signals("endat", "endat_encoder", str(context["slot_lower"]), channel_index)
                        )
                    elif interface == "ssi":
                        ssi_instances += 1
                        context = serial_encoder_context(
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
                        main_init.extend(ssi_main_init(str(context["slot_lower"]), channel_index))
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

        visualization_fragments = build_software_visualization_fragments(
            available_visualization_signals,
            selected_visualization_routes,
        )
        generated_files["include/project_wizard_visualization.h"] = self.renderer.render_file(
            "software/project_wizard_visualization.h.tpl", visualization_fragments.generated_file_context
        ).rstrip() + "\n"
        generated_files["sw/project_wizard_visualization.c"] = self.renderer.render_file(
            "software/project_wizard_visualization.c.tpl", visualization_fragments.generated_file_context
        ).rstrip() + "\n"
        return SoftwarePlan(
            slot_content=slot_content,
            generated_files=generated_files,
            actual_values=actual_values,
            reference_and_set_values=reference_and_set_values,
            objects=objects,
            adc_readout_definitions=adc_readout_definitions,
            adc_readout=adc_readout,
            main_init=main_init,
            main_rasv_initializer=main_rasv_initializer,
            isr_control_by_slot=isr_control_by_slot,
            isr_user_blocks_by_slot=isr_user_blocks_by_slot,
            state_isr_actions=state_isr_actions,
            datamover_array_length=datamover_array_length,
            javascope_observable_enums=visualization_fragments.javascope_observable_enums,
            javascope_observable_pointers=visualization_fragments.javascope_observable_pointers,
            javascope_slowdata_enums=visualization_fragments.javascope_slowdata_enums,
            javascope_slowdata_pointers=visualization_fragments.javascope_slowdata_pointers,
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

    def build_plan(self, model: ResolvedSystemModel, resolve_base_addresses: bool = True) -> SoftwarePlan:
        legacy_values = model.config.legacy_generator_values()
        return self._build_plan_from_values(
            model.config.software_source_dir,
            legacy_values["slots"],
            legacy_values["slot_options"],
            model.config.software_modes,
            model.config.software_presets,
            model.config.visualization_routes,
            model.config.driver_config,
            model.config.hardware,
            resolve_base_addresses=resolve_base_addresses,
            analog_datamover=model.analog_datamover,
        )

    def _preview_from_values(
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
        analog_datamover: ResolvedAnalogDataMover | None = None,
    ) -> str:
        plan = self._build_plan_from_values(
            source_dir,
            assignments,
            option_values,
            software_modes,
            software_presets,
            visualization_signals,
            driver_config,
            hardware_config,
            resolve_base_addresses=False,
            analog_datamover=analog_datamover,
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

    def preview(self, model: ResolvedSystemModel) -> str:
        legacy_values = model.config.legacy_generator_values()
        return self._preview_from_values(
            model.config.software_source_dir,
            legacy_values["slots"],
            legacy_values["slot_options"],
            model.config.platform_revision,
            model.config.software_modes,
            model.config.software_presets,
            model.config.visualization_routes,
            model.config.driver_config,
            model.config.hardware,
            model.analog_datamover,
        )

    def visualization_signals(self, model: ResolvedSystemModel) -> list[VisualizationSignal]:
        return model.available_visualization_signals

    def driver_config_instances(self, model: ResolvedSystemModel) -> list[DriverConfigInstance]:
        instances: list[DriverConfigInstance] = []
        for resolved in model.software_driver_instances:
            if resolved.driver_definition_id == "pwm_2l":
                fields = pwm_2l_config_fields()
            elif resolved.driver_definition_id == "deadtime_2l":
                fields = deadtime_2l_config_fields()
            elif resolved.driver_definition_id == "pwm_3l":
                fields = pwm_3l_config_fields()
            else:
                fields = self.driver_config_fields(resolved.driver_definition_id, resolved.preset)
            instances.append(
                DriverConfigInstance(
                    id=resolved.id,
                    slot=resolved.slot,
                    label=resolved.label,
                    driver=resolved.driver,
                    fields=fields,
                )
            )
        return instances

    def generate(self, model: ResolvedSystemModel) -> SoftwareGenerationResult:
        legacy_values = model.config.legacy_generator_values()
        return self._generate_from_values(
            model.config.software_source_dir,
            legacy_values["slots"],
            legacy_values["slot_options"],
            model.config.platform_revision,
            model.config.software_modes,
            model.config.software_presets,
            model.config.visualization_routes,
            model.config.driver_config,
            model.config.hardware,
            model.analog_datamover,
        )

    def _generate_from_values(
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
        analog_datamover: ResolvedAnalogDataMover | None = None,
    ) -> SoftwareGenerationResult:
        plan = self._build_plan_from_values(
            source_dir,
            assignments,
            option_values,
            software_modes,
            software_presets,
            visualization_signals,
            driver_config,
            hardware_config,
            analog_datamover=analog_datamover,
        )
        return apply_software_plan(
            source_dir,
            plan,
            platform_revision,
            hardware_config or {},
            project_wizard_pwm_runtime_lines(),
        )

def split_header_template(rendered_header: str) -> tuple[list[str], list[str]]:
    includes: list[str] = []
    prototypes: list[str] = []
    seen_includes: set[str] = set()
    for line in rendered_header.splitlines():
        stripped = line.strip()
        if not stripped:
            continue
        if stripped.startswith("#include"):
            if stripped in seen_includes:
                continue
            seen_includes.add(stripped)
            includes.append(line)
        elif stripped.startswith("/*"):
            includes.append(line)
        else:
            prototypes.append(line)
    return includes, prototypes


def _extend_unique(target: list[str], entries: list[str]) -> None:
    seen = {entry.strip() for entry in target}
    for entry in entries:
        key = entry.strip()
        if key in seen:
            continue
        seen.add(key)
        target.append(entry)



