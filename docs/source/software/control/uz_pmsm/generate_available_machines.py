#!/usr/bin/env python3
"""Generate PMSM machine inventory CSV and C init macros from docs datasets."""

from __future__ import annotations

import argparse
import csv
import re
from dataclasses import dataclass
from pathlib import Path

REQUIRED_C_PARAMETERS: tuple[str, ...] = (
    "R_ph_Ohm",
    "Ld_Henry",
    "Lq_Henry",
    "Psi_PM_Vs",
    "polePairs",
    "J_kg_m_squared",
    "I_max_Ampere",
)


@dataclass(frozen=True)
class MachineEntry:
    machine_id: str
    macro_name: str
    machine_name: str
    dataset_name: str
    machine_parameters_csv: str
    parameters: dict[str, float]


def _repo_root() -> Path:
    return Path(__file__).resolve().parents[5]


def _default_uz_pmsm_dir() -> Path:
    return Path(__file__).resolve().parent


def _default_inventory_path() -> Path:
    return _default_uz_pmsm_dir() / "avialable_machines.csv"


def _default_header_path() -> Path:
    return _repo_root() / "vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_avialable_machines_auto_generated.h"


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--uz-pmsm-dir",
        type=Path,
        default=_default_uz_pmsm_dir(),
        help="Root directory containing PMSM machine folders.",
    )
    parser.add_argument(
        "--inventory-output",
        type=Path,
        default=_default_inventory_path(),
        help="Output CSV listing all discovered machines.",
    )
    parser.add_argument(
        "--header-output",
        type=Path,
        default=_default_header_path(),
        help="Output header containing generated PMSM init macros.",
    )
    return parser.parse_args()


def _read_key_value_csv(csv_path: Path) -> dict[str, str]:
    rows: list[tuple[str, str]] = []
    with csv_path.open(newline="", encoding="utf-8") as csv_file:
        reader = csv.reader(csv_file)
        try:
            header = next(reader)
        except StopIteration as exc:
            raise ValueError(f"Empty parameter CSV: {csv_path}") from exc

        if header[:2] != ["parameter", "value"]:
            raise ValueError(
                f"Parameter CSV must start with 'parameter,value': {csv_path}"
            )

        for row in reader:
            if not row or all(cell.strip() == "" for cell in row):
                break
            if len(row) != 2:
                break
            rows.append((row[0].strip(), row[1].strip()))

    return dict(rows)


def _normalize_identifier(value: str) -> str:
    normalized = re.sub(r"[^0-9A-Za-z]+", "_", value.strip()).strip("_")
    normalized = re.sub(r"_+", "_", normalized)
    if not normalized:
        raise ValueError("Identifier normalization produced an empty string")
    if normalized[0].isdigit():
        normalized = f"MACHINE_{normalized}"
    return normalized.upper()


def _validate_parameters(parameters: dict[str, float], csv_path: Path) -> None:
    missing = [name for name in REQUIRED_C_PARAMETERS if name not in parameters]
    if missing:
        raise ValueError(f"Missing PMSM parameters in {csv_path}: {missing}")

    checks = {
        "R_ph_Ohm": parameters["R_ph_Ohm"] > 0.0,
        "Ld_Henry": parameters["Ld_Henry"] > 0.0,
        "Lq_Henry": parameters["Lq_Henry"] > 0.0,
        "Psi_PM_Vs": parameters["Psi_PM_Vs"] >= 0.0,
        "polePairs": parameters["polePairs"] > 0.0 and parameters["polePairs"] % 1.0 == 0.0,
        "J_kg_m_squared": parameters["J_kg_m_squared"] > 0.0,
        "I_max_Ampere": parameters["I_max_Ampere"] > 0.0,
    }
    invalid = [name for name, is_valid in checks.items() if not is_valid]
    if invalid:
        raise ValueError(f"Invalid PMSM parameters in {csv_path}: {invalid}")


def _discover_entries(uz_pmsm_dir: Path) -> list[MachineEntry]:
    entries: list[MachineEntry] = []
    used_machine_ids: set[str] = set()

    for csv_path in sorted(uz_pmsm_dir.rglob("machine_parameters.csv")):
        relative_csv_path = csv_path.relative_to(uz_pmsm_dir)
        if len(relative_csv_path.parts) != 3:
            continue

        machine_dir, dataset_dir, _ = relative_csv_path.parts
        raw_values = _read_key_value_csv(csv_path)
        parameters = {name: float(raw_values[name]) for name in REQUIRED_C_PARAMETERS}
        _validate_parameters(parameters, csv_path)

        machine_id = _normalize_identifier(f"{machine_dir}_{dataset_dir}")
        if machine_id in used_machine_ids:
            raise ValueError(f"Duplicate machine id generated for {csv_path}: {machine_id}")
        used_machine_ids.add(machine_id)

        machine_name = raw_values.get("machine_name", machine_dir)
        entries.append(
            MachineEntry(
                machine_id=machine_id,
                macro_name=f"UZ_PMSM_{machine_id}_INIT",
                machine_name=machine_name,
                dataset_name=dataset_dir,
                machine_parameters_csv=str(relative_csv_path).replace("\\", "/"),
                parameters=parameters,
            )
        )

    if not entries:
        raise ValueError(f"No machine_parameters.csv files found below {uz_pmsm_dir}")

    return entries


def _format_c_float(value: float) -> str:
    text = format(value, ".15g")
    if "e" not in text.lower() and "." not in text:
        text = f"{text}.0"
    return f"{text}f"


def _write_inventory_csv(entries: list[MachineEntry], output_path: Path) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    fieldnames = [
        "machine_id",
        "macro_name",
        "machine_name",
        "dataset_name",
        "machine_parameters_csv",
        *REQUIRED_C_PARAMETERS,
    ]
    with output_path.open("w", newline="", encoding="utf-8") as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()
        for entry in entries:
            row = {
                "machine_id": entry.machine_id,
                "macro_name": entry.macro_name,
                "machine_name": entry.machine_name,
                "dataset_name": entry.dataset_name,
                "machine_parameters_csv": entry.machine_parameters_csv,
            }
            row.update({name: format(entry.parameters[name], ".15g") for name in REQUIRED_C_PARAMETERS})
            writer.writerow(row)


def _render_header(entries: list[MachineEntry], uz_pmsm_dir: Path, inventory_output: Path) -> str:
    relative_inventory = inventory_output.relative_to(_repo_root())
    relative_source_root = uz_pmsm_dir.relative_to(_repo_root())
    lines = [
        "#ifndef UZ_AVIALABLE_MACHINES_AUTO_GENERATED_H",
        "#define UZ_AVIALABLE_MACHINES_AUTO_GENERATED_H",
        "",
        "#pragma once",
        "",
        "/* This file is auto-generated by docs/source/software/control/uz_pmsm/generate_available_machines.py. */",
        f"/* Source PMSM datasets root: {relative_source_root.as_posix()} */",
        f"/* Generated machine inventory: {relative_inventory.as_posix()} */",
        "/* Do not edit this file manually. */",
        "",
    ]

    for entry in entries:
        lines.append(f"/* {entry.machine_name} ({entry.dataset_name}) from {entry.machine_parameters_csv} */")
        lines.append(f"#define {entry.macro_name} \\")
        lines.append("    { \\")
        for name in REQUIRED_C_PARAMETERS:
            line = f"        .{name} = {_format_c_float(entry.parameters[name])}, "
            lines.append(line + "\\")
        lines.append("    }")
        lines.append("")

    lines.append("#endif // UZ_AVIALABLE_MACHINES_AUTO_GENERATED_H")
    lines.append("")
    return "\n".join(lines)


def _write_header(entries: list[MachineEntry], uz_pmsm_dir: Path, inventory_output: Path, output_path: Path) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(
        _render_header(entries, uz_pmsm_dir=uz_pmsm_dir, inventory_output=inventory_output),
        encoding="utf-8",
    )


def main() -> None:
    args = _parse_args()
    uz_pmsm_dir = args.uz_pmsm_dir.resolve()
    inventory_output = args.inventory_output.resolve()
    header_output = args.header_output.resolve()

    entries = _discover_entries(uz_pmsm_dir)
    _write_inventory_csv(entries, inventory_output)
    _write_header(entries, uz_pmsm_dir=uz_pmsm_dir, inventory_output=inventory_output, output_path=header_output)

    print(f"Generated {len(entries)} PMSM machine entries")
    print(f"Inventory CSV: {inventory_output}")
    print(f"Header: {header_output}")


if __name__ == "__main__":
    main()