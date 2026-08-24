from __future__ import annotations

import re
from pathlib import Path

from .software_models import (
    FILE_MARKERS,
    GLOBAL_DATA_MARKERS,
    PWM_GLOBAL_DEFINE_KEYS,
    SLOTS,
    MarkerError,
    SoftwareGenerationResult,
    SoftwarePlan,
)


def apply_software_plan(
    source_dir: Path,
    plan: SoftwarePlan,
    platform_revision: str,
    hardware_config: dict[str, str],
    pwm_runtime_lines: list[str],
) -> SoftwareGenerationResult:
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
    patch_global_data(global_data, plan.actual_values, plan.reference_and_set_values, plan.objects)
    patched_files.append(global_data)

    main_c = source_dir / "main.c"
    patch_marker_file(main_c, "main_rasv_initializer", plan.main_rasv_initializer)
    patch_marker_file(main_c, "main_init_ip_cores", plan.main_init)
    patched_files.append(main_c)

    isr_c = source_dir / "sw" / "isr.c"
    patch_marker_file(isr_c, "adc_readout_definitions", plan.adc_readout_definitions)
    patch_marker_file(isr_c, "adc_readout", plan.adc_readout)
    patch_marker_file(isr_c, "pwm_runtime", pwm_runtime_lines)
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
    patch_pwm_global_defines(global_configuration, hardware_config)
    if plan.instance_counts:
        patch_instance_counts(global_configuration, plan.instance_counts)
    patched_files.append(global_configuration)

    return SoftwareGenerationResult(written_files, patched_files, plan.warnings)


def patch_slot_header(path: Path, slot: str, includes: list[str], prototypes: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_named_block(text, slot, "includes", includes)
    text = replace_named_block(text, slot, "prototypes", prototypes)
    path.write_text(text, encoding="utf-8")


def patch_slot_source(path: Path, slot: str, definitions: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_named_block(text, slot, "definitions", definitions)
    path.write_text(text, encoding="utf-8")


def patch_global_data(path: Path, actual_values: list[str], reference_and_set_values: list[str], objects: list[str]) -> None:
    text = path.read_text(encoding="utf-8")
    text = replace_block(text, GLOBAL_DATA_MARKERS["actual_values"], actual_values)
    text = replace_block(text, GLOBAL_DATA_MARKERS["reference_and_set_values"], reference_and_set_values)
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
