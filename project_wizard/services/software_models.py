from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path

from ..models import VisualizationSignal


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
    "reference_and_set_values": (
        "/* Project Wizard BEGIN: referenceAndSetValues */",
        "/* Project Wizard END: referenceAndSetValues */",
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
    "main_rasv_initializer": (
        "/* Project Wizard BEGIN: rasv_initializer */",
        "/* Project Wizard END: rasv_initializer */",
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
    "interrupt_isr_source": "INTERRUPT_ISR_SOURCE_USER_CHOICE",
    "interrupt_isr_trigger_on_adc_data_ready": "INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY",
    "interrupt_adc_to_isr_ratio": "INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE",
    "adc_trigger_delay_us": "ADC_TRIGGER_DELAY_IN_US",
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
    reference_and_set_values: list[str]
    objects: list[str]
    adc_readout_definitions: list[str]
    adc_readout: list[str]
    main_init: list[str]
    main_rasv_initializer: list[str]
    isr_control_by_slot: dict[str, list[str]]
    state_isr_actions: dict[str, list[str]]
    datamover_array_length: int
    javascope_observable_enums: list[str]
    javascope_observable_pointers: list[str]
    javascope_slowdata_enums: list[str]
    javascope_slowdata_pointers: list[str]
    available_visualization_signals: list[VisualizationSignal]
    instance_counts: dict[str, int]
    warnings: list[str]


@dataclass(frozen=True)
class SoftwareGenerationResult:
    written_files: list[Path]
    patched_files: list[Path]
    warnings: list[str]


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
