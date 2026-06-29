from __future__ import annotations

import argparse
import csv
import re
from dataclasses import dataclass
from pathlib import Path

from ._repo_paths import machine_catalog_default_paths
from ._repo_paths import repo_root_from
from .pmsm.parameters import CParameterField
from .pmsm.parameters import PMSMParameters
from .pmsm.parameters import SUPPORTED_C_PARAMETER_TYPES


@dataclass(frozen=True)
class MachineCatalogEntry:
    machine_id: str
    macro_name: str
    machine_name: str
    dataset_name: str
    machine_parameters_csv: str
    parameters: dict[str, float | int]


def parse_uz_pmsm_struct_fields(header_path: str | Path) -> tuple[CParameterField, ...]:
    header_path = Path(header_path)
    text = header_path.read_text(encoding="utf-8")
    match = re.search(
        r"typedef\s+struct\s+uz_PMSM_t\s*\{(?P<body>.*?)\}\s*uz_PMSM_t\s*;",
        text,
        re.DOTALL,
    )
    if not match:
        raise ValueError(f"Could not locate uz_PMSM_t in {header_path}")

    body = re.sub(r"/\*.*?\*/", "", match.group("body"), flags=re.DOTALL)
    fields: list[CParameterField] = []
    for line in body.splitlines():
        stripped = re.sub(r"//.*", "", line).strip()
        if not stripped:
            continue
        field_match = re.fullmatch(
            r"(?P<ctype>[A-Za-z_][A-Za-z0-9_]*)\s+"
            r"(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s*;",
            stripped,
        )
        if field_match:
            ctype = field_match.group("ctype")
            if ctype not in SUPPORTED_C_PARAMETER_TYPES:
                raise ValueError(
                    f"Unsupported uz_PMSM_t field type in {header_path}: "
                    f"{ctype} {field_match.group('name')}"
                )
            fields.append(CParameterField(ctype=ctype, name=field_match.group("name")))
            continue
        raise ValueError(
            f"Unsupported uz_PMSM_t field declaration in {header_path}: {stripped}"
        )

    if not fields:
        raise ValueError(f"No uz_PMSM_t fields parsed from {header_path}")
    return tuple(fields)


def normalize_machine_identifier(value: str) -> str:
    normalized = re.sub(r"[^0-9A-Za-z]+", "_", value.strip()).strip("_")
    normalized = re.sub(r"_+", "_", normalized)
    if not normalized:
        raise ValueError("Identifier normalization produced an empty string")
    if normalized[0].isdigit():
        normalized = f"MACHINE_{normalized}"
    return normalized.upper()


def format_c_float(value: float) -> str:
    text = format(value, ".15g")
    if "e" not in text.lower() and "." not in text:
        text = f"{text}.0"
    return f"{text}f"


def format_c_value(value: float | int, ctype: str) -> str:
    if ctype == "float":
        return format_c_float(float(value))
    if ctype == "uint32_t":
        parsed_value = int(value)
        if parsed_value != float(value):
            raise ValueError(f"Cannot render non-integer value {value!r} as uint32_t")
        if parsed_value < 0 or parsed_value > 0xFFFFFFFF:
            raise ValueError(f"Cannot render out-of-range value {value!r} as uint32_t")
        return f"{parsed_value}u"
    raise ValueError(f"Unsupported C field type: {ctype}")


def format_path_for_generated_comment(path: str | Path, repo_root: str | Path) -> str:
    resolved_path = Path(path).resolve()
    resolved_repo_root = Path(repo_root).resolve()
    if resolved_path.is_relative_to(resolved_repo_root):
        return resolved_path.relative_to(resolved_repo_root).as_posix()
    return resolved_path.as_posix()


_PARAMETER_HINTS: dict[str, tuple[str, str]] = {
    # field_name: (constraint, description)
    "machine_id":       ("positive integer, unique across all motors", "auto-assigned, change only if needed"),
    "R_ph_Ohm":         ("> 0",                    "phase resistance in Ohm"),
    "Ld_Henry":         ("> 0",                    "d-axis inductance in H"),
    "Lq_Henry":         ("> 0",                    "q-axis inductance in H"),
    "Psi_PM_Vs":        (">= 0",                   "PM flux linkage in Vs"),
    "polePairs":        ("> 0, integer value",      "e.g. 2, 4, 6"),
    "J_kg_m_squared":   ("> 0",                    "rotor inertia in kg·m²"),
    "I_max_Ampere":     ("> 0",                    "peak phase current in A"),
    "I_rated_Ampere":   ("0 < value <= I_max_Ampere", ""),
    "Torque_rated_Nm":  ("> 0",                    ""),
    "Torque_max_Nm":    (">= Torque_rated_Nm",     ""),
    "Torque_min_Nm":    ("<= 0, < Torque_max_Nm",  ""),
    "speed_rated_rpm":  ("> 0",                    ""),
    "speed_max_rpm":    (">= speed_rated_rpm",     ""),
    "speed_min_rpm":    ("<= 0, < speed_max_rpm",  ""),
    "V_dc_nominal_V":   ("> 0",                    "nominal DC-link voltage in V"),
    "I_d_max_A":        (">= I_d_min_A",           ""),
    "I_d_min_A":        ("any float",              ""),
    "I_q_max_A":        (">= I_q_min_A",           ""),
    "I_q_min_A":        ("any float",              ""),
}

_PREPROCESS_SCRIPT_TEMPLATE = '''\
#!/usr/bin/env python3
"""Convert raw flux-map data to the canonical uz_pmsm format.

Edit the column name strings below to match your source file, then run this script once.
Commit flux_map.csv and differential_inductances.csv; the raw source file is optional.
"""
from pathlib import Path
import pyuzlib

SCRIPT_DIR = Path(__file__).resolve().parent

motor = pyuzlib.pmsm.PMSM()
motor.load_flux_map_csv(
    SCRIPT_DIR / "flux_map_raw.csv",  # TODO: rename to match your raw file
    i_d_col="i_d",     # TODO: column name for d-axis current in your source file
    i_q_col="i_q",     # TODO: column name for q-axis current
    psi_d_col="psi_d", # TODO: column name for d-axis flux linkage
    psi_q_col="psi_q", # TODO: column name for q-axis flux linkage
)
motor.calculate_differential_inductances()
motor.export_flux_map_csv(SCRIPT_DIR / "flux_map.csv")
motor.export_differential_inductances_csv(SCRIPT_DIR / "differential_inductances.csv")
print("Exported flux_map.csv and differential_inductances.csv.")
'''


def _print_parameter_hints(next_id: int) -> None:
    name_w = max(len(n) for n in _PARAMETER_HINTS) + 2
    constraint_w = max(len(c) for c, _ in _PARAMETER_HINTS.values()) + 2
    print("\nParameter constraints:")
    for field in PMSMParameters.C_PARAMETER_FIELDS:
        constraint, description = _PARAMETER_HINTS.get(field.name, ("", ""))
        if field.name == "machine_id":
            constraint = f"positive integer, unique across all motors (auto-assigned: {next_id})"
        desc_part = f"  {description}" if description else ""
        print(f"  {field.name:<{name_w}} ({field.ctype})  {constraint:<{constraint_w}}{desc_part}")


def _write_preprocess_script_template(dataset_dir: Path) -> Path:
    script_path = dataset_dir / "preprocess_to_correct_data_format.py"
    script_path.write_text(_PREPROCESS_SCRIPT_TEMPLATE, encoding="utf-8")
    return script_path


def create_machine_template(
    motor_name: str,
    dataset_name: str,
    uz_pmsm_dir: str | Path,
    with_raw_data: bool = False,
) -> tuple[Path, Path | None, int]:
    uz_pmsm_dir = Path(uz_pmsm_dir)
    dataset_dir = uz_pmsm_dir / motor_name / dataset_name
    if dataset_dir.exists():
        raise ValueError(f"Dataset directory already exists: {dataset_dir}")

    used_ids: set[int] = set()
    for csv_path in uz_pmsm_dir.rglob("machine_parameters.csv"):
        relative = csv_path.relative_to(uz_pmsm_dir)
        if len(relative.parts) != 3:
            continue
        for line in csv_path.read_text(encoding="utf-8").splitlines():
            if line.startswith("machine_id,"):
                try:
                    used_ids.add(int(line.split(",", 1)[1].strip()))
                except (ValueError, IndexError):
                    pass
                break

    next_id = next(i for i in range(1, len(used_ids) + 2) if i not in used_ids)

    dataset_dir.mkdir(parents=True)
    csv_path = dataset_dir / "machine_parameters.csv"
    lines = ["parameter,value", f"machine_name,{motor_name}", f"machine_id,{next_id}"]
    for field in PMSMParameters.C_PARAMETER_FIELDS:
        if field.name == "machine_id":
            continue
        lines.append(f"{field.name},")
    csv_path.write_text("\n".join(lines) + "\n", encoding="utf-8")

    script_path = _write_preprocess_script_template(dataset_dir) if with_raw_data else None
    return csv_path, script_path, next_id


def discover_machine_catalog(
    uz_pmsm_dir: str | Path,
    c_header_path: str | Path,
) -> tuple[tuple[CParameterField, ...], list[MachineCatalogEntry]]:
    uz_pmsm_dir = Path(uz_pmsm_dir)
    c_fields = parse_uz_pmsm_struct_fields(c_header_path)
    if c_fields != PMSMParameters.C_PARAMETER_FIELDS:
        raise ValueError(
            "pyuzlib.PMSMParameters and uz_PMSM_t differ. "
            f"Python fields: {PMSMParameters.C_PARAMETER_FIELDS}, C fields: {c_fields}"
        )
    entries: list[MachineCatalogEntry] = []
    used_machine_ids: set[str] = set()
    used_numeric_machine_ids: set[int] = set()

    for csv_path in sorted(uz_pmsm_dir.rglob("machine_parameters.csv")):
        relative_csv_path = csv_path.relative_to(uz_pmsm_dir)
        if len(relative_csv_path.parts) != 3:
            continue

        machine_dir, dataset_dir, _ = relative_csv_path.parts
        parameters = PMSMParameters.from_csv(csv_path)
        values = parameters.to_dict(include_additional=True)

        try:
            c_dict = parameters.to_c_dict()
        except ValueError as exc:
            raise ValueError(f"Invalid PMSM parameter CSV {csv_path}: {exc}") from exc
        c_values = {field.name: c_dict[field.name] for field in c_fields}

        machine_id = normalize_machine_identifier(f"{machine_dir}_{dataset_dir}")
        if machine_id in used_machine_ids:
            raise ValueError(f"Duplicate machine id generated for {csv_path}: {machine_id}")
        used_machine_ids.add(machine_id)

        numeric_machine_id = int(c_values.get("machine_id", 0))
        if numeric_machine_id in used_numeric_machine_ids:
            next_id = next(
                i for i in range(1, len(used_numeric_machine_ids) + 2)
                if i not in used_numeric_machine_ids
            )
            raise ValueError(
                f"Duplicate numeric machine_id {numeric_machine_id} in {csv_path}. "
                f"Next unused machine_id is {next_id}. "
                "Each machine_parameters.csv must have a unique machine_id value."
            )
        used_numeric_machine_ids.add(numeric_machine_id)

        machine_name = str(values.get("machine_name", machine_dir))
        entries.append(
            MachineCatalogEntry(
                machine_id=machine_id,
                macro_name=f"UZ_PMSM_{machine_id}_INIT",
                machine_name=machine_name,
                dataset_name=dataset_dir,
                machine_parameters_csv=str(relative_csv_path).replace("\\", "/"),
                parameters=c_values,
            )
        )

    if not entries:
        raise ValueError(f"No machine_parameters.csv files found below {uz_pmsm_dir}")

    return c_fields, entries


def write_available_machines_csv(
    entries: list[MachineCatalogEntry],
    output_path: str | Path,
    c_fields: tuple[CParameterField, ...],
) -> None:
    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    c_parameter_names = tuple(field.name for field in c_fields)
    fieldnames = [
        "catalog_id",
        "macro_name",
        "machine_name",
        "dataset_name",
        "machine_parameters_csv",
        *c_parameter_names,
    ]
    with output_path.open("w", newline="", encoding="utf-8") as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()
        for entry in entries:
            row = {
                "catalog_id": entry.machine_id,
                "macro_name": entry.macro_name,
                "machine_name": entry.machine_name,
                "dataset_name": entry.dataset_name,
                "machine_parameters_csv": entry.machine_parameters_csv,
            }
            row.update(
                {
                    field.name: format(entry.parameters[field.name], ".15g")
                    for field in c_fields
                }
            )
            writer.writerow(row)


def render_c_init_header(
    entries: list[MachineCatalogEntry],
    *,
    c_fields: tuple[CParameterField, ...],
    source_root: str | Path,
    inventory_output: str | Path,
    generator_script: str,
) -> str:
    source_root = Path(source_root)
    inventory_output = Path(inventory_output)
    repo_root = repo_root_from(source_root)
    source_root_comment = format_path_for_generated_comment(source_root, repo_root)
    inventory_comment = format_path_for_generated_comment(inventory_output, repo_root)
    lines = [
        "#ifndef UZ_AVAILABLE_MACHINES_AUTO_GENERATED_H",
        "#define UZ_AVAILABLE_MACHINES_AUTO_GENERATED_H",
        "",
        "#pragma once",
        "",
        f"/* This file is auto-generated by {generator_script}. */",
        f"/* Source PMSM datasets root: {source_root_comment} */",
        f"/* Generated machine inventory: {inventory_comment} */",
        "/* Do not edit this file manually. */",
        "",
    ]

    for entry in entries:
        lines.append(
            f"/* {entry.machine_name} ({entry.dataset_name}) from {entry.machine_parameters_csv} */"
        )
        lines.append(f"#define {entry.macro_name} \\")
        lines.append("    { \\")
        for field in c_fields:
            lines.append(
                f"        .{field.name} = "
                f"{format_c_value(entry.parameters[field.name], field.ctype)}, \\"
            )
        lines.append("    }")
        lines.append("")

    lines.append("#endif // UZ_AVAILABLE_MACHINES_AUTO_GENERATED_H")
    lines.append("")
    return "\n".join(lines)


def write_c_init_header(
    entries: list[MachineCatalogEntry],
    output_path: str | Path,
    *,
    c_fields: tuple[CParameterField, ...],
    source_root: str | Path,
    inventory_output: str | Path,
    generator_script: str,
) -> None:
    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(
        render_c_init_header(
            entries,
            c_fields=c_fields,
            source_root=source_root,
            inventory_output=inventory_output,
            generator_script=generator_script,
        ),
        encoding="utf-8",
    )

def generate_machine_catalog(
    *,
    uz_pmsm_dir: str | Path,
    c_header_path: str | Path,
    inventory_output: str | Path,
    generated_header_output: str | Path,
    generator_script: str,
) -> list[MachineCatalogEntry]:
    c_fields, entries = discover_machine_catalog(
        uz_pmsm_dir=uz_pmsm_dir,
        c_header_path=c_header_path,
    )
    write_available_machines_csv(entries, inventory_output, c_fields)
    write_c_init_header(
        entries,
        generated_header_output,
        c_fields=c_fields,
        source_root=uz_pmsm_dir,
        inventory_output=inventory_output,
        generator_script=generator_script,
    )
    return entries


def build_arg_parser(default_anchor: str | Path) -> argparse.ArgumentParser:
    defaults = machine_catalog_default_paths(default_anchor)
    parser = argparse.ArgumentParser(
        description="Generate PMSM machine inventory CSV and C init macros from docs datasets.",
    )
    parser.add_argument("--uz-pmsm-dir", type=Path, default=defaults["uz_pmsm_dir"])
    parser.add_argument("--c-header-path", type=Path, default=defaults["c_header_path"])
    parser.add_argument("--inventory-output", type=Path, default=defaults["inventory_output"])
    parser.add_argument(
        "--header-output",
        type=Path,
        default=defaults["generated_header_output"],
    )

    subparsers = parser.add_subparsers(dest="command")
    add_machine = subparsers.add_parser(
        "add_machine",
        help="Create a new motor dataset directory with a machine_parameters.csv template.",
    )
    add_machine.add_argument("motor_name", help="Motor directory name, e.g. my_motor")
    add_machine.add_argument("dataset_name", help="Dataset directory name, e.g. nominal_v1")
    add_machine.add_argument(
        "--with-raw-data",
        action="store_true",
        default=False,
        help="Also create a preprocess_to_correct_data_format.py template for raw FEM/measurement data.",
    )

    return parser


def main(argv: list[str] | None = None, *, default_anchor: str | Path | None = None) -> int:
    anchor = default_anchor or __file__
    parser = build_arg_parser(anchor)
    args = parser.parse_args(argv)

    if args.command == "add_machine":
        csv_path, script_path, next_id = create_machine_template(
            motor_name=args.motor_name,
            dataset_name=args.dataset_name,
            uz_pmsm_dir=args.uz_pmsm_dir,
            with_raw_data=args.with_raw_data,
        )
        macro_name = (
            f"UZ_PMSM_{normalize_machine_identifier(f'{args.motor_name}_{args.dataset_name}')}_INIT"
        )
        print(f"Created: {csv_path}")
        if script_path is not None:
            print(f"Created: {script_path}")
        print(f"Fill in all empty values, then run the catalog generator.")
        print(f"C macro will be: {macro_name}")
        _print_parameter_hints(next_id)
        return 0

    entries = generate_machine_catalog(
        uz_pmsm_dir=args.uz_pmsm_dir,
        c_header_path=args.c_header_path,
        inventory_output=args.inventory_output,
        generated_header_output=args.header_output,
        generator_script="pyuzlib.machine_catalog",
    )
    print(f"Generated {len(entries)} PMSM machine entries")
    print(f"Inventory CSV: {Path(args.inventory_output).resolve()}")
    print(f"Header: {Path(args.header_output).resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
