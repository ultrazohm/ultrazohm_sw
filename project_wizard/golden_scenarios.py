from __future__ import annotations

import argparse
import difflib
import hashlib
import json
import re
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from .models import SystemConfig
from .paths import APP_DIR, DATA_FILE, DIGITAL_SLOTS, GOLDEN_SCENARIO_DIR, SLOTS
from .repositories import CardDatabase
from .services.card_service import default_cpld_for_card
from .services.software_generator_service import SoftwareGenerator
from .services.system_resolver import SystemResolver
from .tcl_generator import TclGenerator


@dataclass(frozen=True)
class GoldenScenario:
    name: str
    description: str
    document: dict[str, Any]


def base_document(database: CardDatabase) -> dict[str, Any]:
    source_dir = APP_DIR.parent / "vitis" / "software" / "Baremetal" / "src"
    hardware = {
        "vivado_project_file": str(APP_DIR.parent / "vivado" / "project" / "ultrazohm.xpr"),
        "block_design_name": "zusys",
        "tcl_workflow_local": "true",
        "tcl_workflow_remote": "false",
        "validate_block_design": "true",
        "save_block_design": "true",
        "open_vivado_gui": "false",
        "disable_bd_synth_checkpoints": "false",
        "generate_bitstream": "false",
        "export_xsa_after_build": "false",
        "pwm_2l_instances": "4",
        "pwm_2l_idle_error_behavior": "tristate_with_duty_cycle",
        "pwm_2l_idle_error_duty_hb1": "0.0f",
        "pwm_2l_idle_error_duty_hb2": "0.0f",
        "pwm_2l_idle_error_duty_hb3": "0.0f",
        "pwm_3l_instances": "1",
        "pwm_enable_source": "uz_system/Enable_Gate",
        "interrupt_isr_source": "1U",
        "interrupt_isr_trigger_on_adc_data_ready": "0U",
        "interrupt_adc_to_isr_ratio": "1U",
        "adc_trigger_delay_us": "0.01f",
        "pwm_frequency": "10.0e3f",
        "pwm_deadtime_us": "1.0f",
        "pwm_min_pulse_width_us": "0.5f",
    }
    software = {"source_dir": str(source_dir)}
    software.update({f"{slot}_mode": "follow_hardware" for slot in SLOTS})
    software.update({f"{slot}_preset": "default" for slot in SLOTS})
    return {
        "schema_version": 2,
        "platform": {
            "id": "ultrazohm",
            "revision": "Rev06",
            "cpld": {"rev04_cpld_type": "la4128v"},
        },
        "toolchain": {},
        "hardware": hardware,
        "slots": {
            slot: {
                "card": "empty" if slot.startswith("D") else "no_adapter_board",
                "options": {},
                "cpld": "none",
            }
            for slot in SLOTS
        },
        "cpld_programmer": {},
        "axi": {str(key): str(value) for key, value in database.axi_interconnect.items()},
        "software": {
            "source_dir": str(source_dir),
            "modes": {slot: "follow_hardware" for slot in SLOTS},
            "presets": {slot: "default" for slot in SLOTS},
            "visualization_routes": {},
            "driver_config": {},
            "extra": {},
        },
    }


def with_assignments(
    database: CardDatabase,
    document: dict[str, Any],
    assignments: dict[str, str],
    options: dict[str, dict[str, str]] | None = None,
    software: dict[str, str] | None = None,
    hardware: dict[str, str] | None = None,
) -> dict[str, Any]:
    result = json.loads(json.dumps(document))
    for slot, card_id in assignments.items():
        result["slots"].setdefault(slot, {"card": "empty", "options": {}, "cpld": "none"})
        result["slots"][slot]["card"] = card_id
    for slot, slot_options in (options or {}).items():
        result["slots"].setdefault(slot, {"card": "empty", "options": {}, "cpld": "none"})
        result["slots"][slot]["options"].update(slot_options)
    if software:
        for key, value in software.items():
            if key.endswith("_mode") and key[:2] in SLOTS:
                result["software"]["modes"][key[:2]] = value
            elif key.endswith("_preset") and key[:2] in SLOTS:
                result["software"]["presets"][key[:2]] = value
            elif key.startswith("visualize_"):
                result["software"]["visualization_routes"][key.removeprefix("visualize_")] = value
            elif key.startswith("driver_config_"):
                remainder = key.removeprefix("driver_config_")
                instance_id, field_id = remainder.rsplit("_", 1)
                result["software"]["driver_config"].setdefault(instance_id, {})[field_id] = value
            else:
                result["software"]["extra"][key] = value
    result["hardware"].update(hardware or {})
    for slot, slot_config in result["slots"].items():
        if slot in DIGITAL_SLOTS:
            card_id = slot_config["card"]
            card = database.card_by_id(card_id)
            if card and card.get("vivado", {}).get("io_card"):
                slot_config["cpld"] = TclGenerator.io_card_cpld_program(
                    card,
                    slot_config.get("options", {}),
                )
            else:
                slot_config["cpld"] = default_cpld_for_card(database, card_id, slot)
    return result


def scenario_documents(database: CardDatabase) -> list[GoldenScenario]:
    base = base_document(database)
    scenarios = [
        GoldenScenario("default_empty", "Default project with A-slots removed and D-slots bypassed.", base),
        GoldenScenario(
            "all_no_adapter",
            "Every adapter slot selected as No adapter board.",
            with_assignments(database, base, {slot: "no_adapter_board" for slot in SLOTS}),
        ),
        GoldenScenario(
            "temperature_d3_d4",
            "Two temperature cards with Type K software presets and visualization routes.",
            with_assignments(
                database,
                base,
                {"D3": "uz_d_temperature_ltc2983", "D4": "uz_d_temperature_ltc2983"},
                software={
                    "D3_preset": "type_k_thermocouple",
                    "D4_preset": "type_k_thermocouple",
                    **{f"visualize_temp_d3_a_{index}": "both" for index in range(4)},
                    **{f"visualize_temp_d4_a_{index}": "both" for index in range(4)},
                },
            ),
        ),
        GoldenScenario(
            "optical_axi_gpio_d2",
            "Optical 14TX4RX card using default AXI GPIO visualization-capable IO.",
            with_assignments(database, base, {"D2": "uz_d_optical_io"}),
        ),
        GoldenScenario(
            "optical_no_axi_d2",
            "Optical card with TX pins driven from PWM/custom sources and RX pins as top-level ports.",
            with_assignments(
                database,
                base,
                {"D2": "uz_d_optical_io"},
                options={
                    "D2": {
                        **{f"io_pin_{index:02d}_mode": "source_pin" for index in range(14)},
                        **{f"io_pin_{index:02d}_source": "uz_pwm/Gate_Signals_2L_0" for index in range(14)},
                        **{f"io_pin_{index:02d}_mode": "top_level" for index in range(14, 18)},
                    }
                },
            ),
        ),
        GoldenScenario(
            "resolver_d4_mixed_pl",
            "D4 resolver with channel 2 using base resolver IP readout and channels 1/3 using PL interface.",
            with_assignments(
                database,
                base,
                {"D4": "uz_d_resolver"},
                options={
                    "D4": {
                        "enable_pl_interface_ch1": "true",
                        "enable_pl_interface_ch2": "false",
                        "enable_pl_interface_ch3": "true",
                    }
                },
            ),
        ),
        GoldenScenario(
            "resolver_d5_two_channel",
            "D5 resolver two-channel mapping with PL interfaces enabled.",
            with_assignments(database, base, {"D5": "uz_d_resolver"}),
        ),
        GoldenScenario(
            "analog_adc_chain",
            "A-slot ADC chain to exercise analog datamover and trigger wiring.",
            with_assignments(
                database,
                base,
                {"A1": "analog_ltc2311_16", "A2": "analog_max11331", "A3": "analog_dac8831"},
            ),
        ),
        GoldenScenario(
            "ten_pwm_2l",
            "Maximum 2L PWM instance count.",
            with_assignments(database, base, {}, hardware={"pwm_2l_instances": "10"}),
        ),
        GoldenScenario(
            "local_workflow_full",
            "Local workflow with GUI mode, bitstream generation, XSA export, and disabled checkpoints.",
            with_assignments(
                database,
                base,
                {"D3": "uz_d_temperature_ltc2983"},
                hardware={
                    "open_vivado_gui": "true",
                    "disable_bd_synth_checkpoints": "true",
                    "generate_bitstream": "true",
                    "export_xsa_after_build": "true",
                },
            ),
        ),
    ]
    proven_config = GOLDEN_SCENARIO_DIR / "configs" / "proven_large_integration.pw.json"
    if proven_config.exists():
        scenarios.append(
            GoldenScenario(
                "proven_large_integration",
                "User-proven large integration scenario built successfully via workstation flow.",
                json.loads(proven_config.read_text(encoding="utf-8")),
            )
        )
    return scenarios


def render_outputs(database: CardDatabase, document: dict[str, Any]) -> tuple[str, dict[str, Any]]:
    tcl_generator = TclGenerator(database)
    software_generator = SoftwareGenerator(database)
    model = SystemResolver(database).resolve(SystemConfig.from_document(document))
    tcl_text = tcl_generator.generate_model(model)
    plan = software_generator.build_plan_model(model, resolve_base_addresses=False)
    summary = {
        "tcl_line_count": len(tcl_text.splitlines()),
        "tcl_warning_count": len(re.findall(r"^# WARNING:", tcl_text, re.MULTILINE)),
        "software_warnings": plan.warnings,
        "software_content_hashes": software_content_hashes(plan),
        "generated_files": sorted(plan.generated_files),
        "actual_values": plan.actual_values,
        "reference_and_set_values": plan.reference_and_set_values,
        "objects": plan.objects,
        "main_init": plan.main_init,
        "main_rasv_initializer": plan.main_rasv_initializer,
        "datamover_array_length": plan.datamover_array_length,
        "instance_counts": plan.instance_counts,
        "visualization_signal_ids": sorted(signal.signal_id for signal in plan.available_visualization_signals),
    }
    return tcl_text, summary


def software_content_hashes(plan: Any) -> dict[str, str]:
    hashes = {
        f"generated_files/{path}": sha256_text(content)
        for path, content in sorted(plan.generated_files.items())
    }
    for slot, content in sorted(plan.slot_content.items()):
        for index, text in enumerate(content.header_includes):
            hashes[f"slot_content/{slot}/header_includes/{index}"] = sha256_text(text)
        for index, text in enumerate(content.header_prototypes):
            hashes[f"slot_content/{slot}/header_prototypes/{index}"] = sha256_text(text)
        for index, text in enumerate(content.source_definitions):
            hashes[f"slot_content/{slot}/source_definitions/{index}"] = sha256_text(text)
    return hashes


def sha256_text(text: str) -> str:
    return hashlib.sha256(text.encode("utf-8")).hexdigest()


def write_golden_outputs(output_dir: Path = GOLDEN_SCENARIO_DIR) -> None:
    database = CardDatabase.load(DATA_FILE)
    config_dir = output_dir / "configs"
    tcl_dir = output_dir / "tcl"
    summary_dir = output_dir / "summaries"
    for directory in (config_dir, tcl_dir, summary_dir):
        directory.mkdir(parents=True, exist_ok=True)
    manifest = []
    for scenario in scenario_documents(database):
        tcl_text, summary = render_outputs(database, scenario.document)
        config_path = config_dir / f"{scenario.name}.pw.json"
        tcl_path = tcl_dir / f"{scenario.name}.tcl"
        summary_path = summary_dir / f"{scenario.name}.summary.json"
        config_path.write_text(json.dumps(scenario.document, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        tcl_path.write_text(tcl_text, encoding="utf-8")
        summary_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        manifest.append(
            {
                "name": scenario.name,
                "description": scenario.description,
                "config": str(config_path.relative_to(output_dir)),
                "tcl": str(tcl_path.relative_to(output_dir)),
                "summary": str(summary_path.relative_to(output_dir)),
            }
        )
    (output_dir / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")


def check_golden_outputs(output_dir: Path = GOLDEN_SCENARIO_DIR) -> int:
    database = CardDatabase.load(DATA_FILE)
    failures: list[str] = []
    for scenario in scenario_documents(database):
        tcl_text, summary = render_outputs(database, scenario.document)
        expected_tcl_path = output_dir / "tcl" / f"{scenario.name}.tcl"
        expected_summary_path = output_dir / "summaries" / f"{scenario.name}.summary.json"
        expected_tcl = expected_tcl_path.read_text(encoding="utf-8")
        expected_summary = expected_summary_path.read_text(encoding="utf-8")
        actual_summary = json.dumps(summary, indent=2, sort_keys=True) + "\n"
        if tcl_text != expected_tcl:
            diff = "\n".join(
                difflib.unified_diff(
                    expected_tcl.splitlines(),
                    tcl_text.splitlines(),
                    fromfile=str(expected_tcl_path),
                    tofile=f"current/{scenario.name}.tcl",
                    lineterm="",
                    n=3,
                )
            )
            failures.append(f"{scenario.name}: TCL differs\n{diff[:4000]}")
        if actual_summary != expected_summary:
            diff = "\n".join(
                difflib.unified_diff(
                    expected_summary.splitlines(),
                    actual_summary.splitlines(),
                    fromfile=str(expected_summary_path),
                    tofile=f"current/{scenario.name}.summary.json",
                    lineterm="",
                    n=3,
                )
            )
            failures.append(f"{scenario.name}: summary differs\n{diff[:4000]}")
    if failures:
        print("\n\n".join(failures))
        return 1
    print(f"Golden scenario check passed: {len(scenario_documents(database))} scenarios.")
    return 0


def main() -> None:
    parser = argparse.ArgumentParser(description="Write Project Wizard golden scenario configs and generated baselines.")
    parser.add_argument("--output-dir", type=Path, default=GOLDEN_SCENARIO_DIR)
    parser.add_argument("--check", action="store_true", help="Compare current generator output against existing baselines.")
    args = parser.parse_args()
    if args.check:
        raise SystemExit(check_golden_outputs(args.output_dir))
    write_golden_outputs(args.output_dir)


if __name__ == "__main__":
    main()
