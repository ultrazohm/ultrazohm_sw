from __future__ import annotations

import argparse
import csv
import re
from dataclasses import dataclass
from pathlib import Path

from ._repo_paths import machine_catalog_default_paths
from ._repo_paths import repo_root_from
from .pmsm import PMSM
from .pmsm import PMSMParameters


@dataclass(frozen=True)
class MachineCatalogEntry:
    machine_id: str
    macro_name: str
    machine_name: str
    dataset_name: str
    machine_parameters_csv: str
    parameters: dict[str, float]

def parse_uz_pmsm_struct_fields(header_path: str | Path) -> tuple[str, ...]:
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
    fields: list[str] = []
    for line in body.splitlines():
        stripped = line.strip()
        if not stripped:
            continue
        field_match = re.match(r"(?:float|double|uint32_t|int32_t|bool)\s+([A-Za-z_][A-Za-z0-9_]*)\s*;", stripped)
        if field_match:
            fields.append(field_match.group(1))

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


def format_path_for_generated_comment(path: str | Path, repo_root: str | Path) -> str:
    resolved_path = Path(path).resolve()
    resolved_repo_root = Path(repo_root).resolve()
    if resolved_path.is_relative_to(resolved_repo_root):
        return resolved_path.relative_to(resolved_repo_root).as_posix()
    return resolved_path.as_posix()


def discover_machine_catalog(
    uz_pmsm_dir: str | Path,
    c_header_path: str | Path,
) -> tuple[tuple[str, ...], list[MachineCatalogEntry]]:
    uz_pmsm_dir = Path(uz_pmsm_dir)
    c_parameter_names = parse_uz_pmsm_struct_fields(c_header_path)
    if c_parameter_names != PMSMParameters.C_PARAMETER_NAMES:
        raise ValueError(
            "pyuzlib.PMSMParameters and uz_PMSM_t differ. "
            f"Python fields: {PMSMParameters.C_PARAMETER_NAMES}, C fields: {c_parameter_names}"
        )
    entries: list[MachineCatalogEntry] = []
    used_machine_ids: set[str] = set()

    for csv_path in sorted(uz_pmsm_dir.rglob("machine_parameters.csv")):
        relative_csv_path = csv_path.relative_to(uz_pmsm_dir)
        if len(relative_csv_path.parts) != 3:
            continue

        machine_dir, dataset_dir, _ = relative_csv_path.parts
        motor = PMSM()
        parameters = motor.load_parameters_csv(csv_path)
        values = parameters.to_dict(include_additional=True)

        missing = [name for name in c_parameter_names if values.get(name) is None]
        if missing:
            raise ValueError(f"Missing uz_PMSM_t fields in {csv_path}: {missing}")

        c_values = {name: float(values[name]) for name in c_parameter_names}
        parameters.validate_for_c()

        machine_id = normalize_machine_identifier(f"{machine_dir}_{dataset_dir}")
        if machine_id in used_machine_ids:
            raise ValueError(f"Duplicate machine id generated for {csv_path}: {machine_id}")
        used_machine_ids.add(machine_id)

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

    return c_parameter_names, entries


def write_available_machines_csv(
    entries: list[MachineCatalogEntry],
    output_path: str | Path,
    c_parameter_names: tuple[str, ...],
) -> None:
    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    fieldnames = [
        "machine_id",
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
                "machine_id": entry.machine_id,
                "macro_name": entry.macro_name,
                "machine_name": entry.machine_name,
                "dataset_name": entry.dataset_name,
                "machine_parameters_csv": entry.machine_parameters_csv,
            }
            row.update({name: format(entry.parameters[name], ".15g") for name in c_parameter_names})
            writer.writerow(row)


def render_c_init_header(
    entries: list[MachineCatalogEntry],
    *,
    c_parameter_names: tuple[str, ...],
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
        "#ifndef UZ_AVIALABLE_MACHINES_AUTO_GENERATED_H",
        "#define UZ_AVIALABLE_MACHINES_AUTO_GENERATED_H",
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
        for name in c_parameter_names:
            lines.append(f"        .{name} = {format_c_float(entry.parameters[name])}, \\")
        lines.append("    }")
        lines.append("")

    lines.append("#endif // UZ_AVIALABLE_MACHINES_AUTO_GENERATED_H")
    lines.append("")
    return "\n".join(lines)


def write_c_init_header(
    entries: list[MachineCatalogEntry],
    output_path: str | Path,
    *,
    c_parameter_names: tuple[str, ...],
    source_root: str | Path,
    inventory_output: str | Path,
    generator_script: str,
) -> None:
    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(
        render_c_init_header(
            entries,
            c_parameter_names=c_parameter_names,
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
    c_parameter_names, entries = discover_machine_catalog(
        uz_pmsm_dir=uz_pmsm_dir,
        c_header_path=c_header_path,
    )
    write_available_machines_csv(entries, inventory_output, c_parameter_names)
    write_c_init_header(
        entries,
        generated_header_output,
        c_parameter_names=c_parameter_names,
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
    return parser


def main(argv: list[str] | None = None, *, default_anchor: str | Path | None = None) -> int:
    anchor = default_anchor or __file__
    parser = build_arg_parser(anchor)
    args = parser.parse_args(argv)

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
