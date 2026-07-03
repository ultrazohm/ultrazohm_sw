from __future__ import annotations

import argparse
import csv
import math
import re
from dataclasses import dataclass
from pathlib import Path

import numpy as np
import pandas as pd

from ._repo_paths import machine_catalog_default_paths
from ._repo_paths import repo_root_from
from .pmsm.differential_inductance import CANONICAL_DIFFERENTIAL_INDUCTANCE_COLUMNS
from .pmsm.flux_map import FluxMap
from .pmsm.parameters import CParameterField
from .pmsm.parameters import PMSM_PARAMETER_CONSTRAINTS
from .pmsm.parameters import PMSMParameters
from .pmsm.parameters import SUPPORTED_C_PARAMETER_TYPES


@dataclass(frozen=True)
class MachineCatalogEntry:
    catalog_id: str
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
    if not math.isfinite(value):
        raise ValueError(f"Cannot render non-finite value {value!r} as C float")
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
    hints = {entry.name: entry for entry in PMSM_PARAMETER_CONSTRAINTS}
    name_w = max(len(n) for n in hints) + 2
    constraint_w = max(len(entry.constraint) for entry in PMSM_PARAMETER_CONSTRAINTS) + 2
    print("\nParameter constraints:")
    for field in PMSMParameters.C_PARAMETER_FIELDS:
        entry = hints.get(field.name)
        constraint = entry.constraint if entry else ""
        description = entry.description if entry else ""
        if field.name == "machine_id":
            constraint = f"positive integer, unique across all motors (pre-filled: {next_id})"
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


def _read_machine_id_from_csv(csv_path: Path) -> int | None:
    for line in csv_path.read_text(encoding="utf-8").splitlines():
        if line.startswith("machine_id,"):
            try:
                return int(line.split(",", 1)[1].strip())
            except (ValueError, IndexError):
                return None
    return None


def _rewrite_machine_id_in_csv(csv_path: Path, new_id: int) -> None:
    lines = csv_path.read_text(encoding="utf-8").splitlines(keepends=True)
    for index, line in enumerate(lines):
        if line.startswith("machine_id,"):
            newline = "\n" if line.endswith("\n") else ""
            lines[index] = f"machine_id,{new_id}{newline}"
            break
    else:
        insert_index = 1 if lines else 0
        lines.insert(insert_index, f"machine_id,{new_id}\n")
    csv_path.write_text("".join(lines), encoding="utf-8")


def renumber_duplicate_machine_ids(uz_pmsm_dir: str | Path) -> list[tuple[str, int, int]]:
    """Deterministically resolve unusable machine_id values across all datasets.

    Datasets are visited in sorted catalog-id order; the first positive occurrence of each id
    keeps it, and every duplicate, missing, malformed, or zero id is rewritten to the next unused
    positive id. Only the machine_id row is rewritten or inserted in a changed
    machine_parameters.csv. Returns the list of applied (machine_parameters_csv, old_id, new_id)
    changes. This is opt-in (``--renumber``) so stable ids stay stable during a normal catalog
    regeneration.
    """
    uz_pmsm_dir = Path(uz_pmsm_dir)
    datasets: list[tuple[str, Path, int | None]] = []
    for csv_path in sorted(uz_pmsm_dir.rglob("machine_parameters.csv")):
        relative_csv_path = csv_path.relative_to(uz_pmsm_dir)
        if len(relative_csv_path.parts) != 3:
            continue
        machine_dir, dataset_dir, _ = relative_csv_path.parts
        catalog_id = normalize_machine_identifier(f"{machine_dir}_{dataset_dir}")
        datasets.append((catalog_id, csv_path, _read_machine_id_from_csv(csv_path)))

    datasets.sort(key=lambda entry: entry[0])
    reserved_ids: set[int] = set()
    for _, _, machine_id in datasets:
        if machine_id is not None and machine_id > 0 and machine_id not in reserved_ids:
            reserved_ids.add(machine_id)

    used_ids: set[int] = set()
    changes: list[tuple[str, int, int]] = []
    for _, csv_path, machine_id in datasets:
        if machine_id is not None and machine_id > 0 and machine_id not in used_ids:
            used_ids.add(machine_id)
            continue
        new_id = next(
            i
            for i in range(1, len(datasets) + len(used_ids) + 2)
            if i not in reserved_ids and i not in used_ids
        )
        used_ids.add(new_id)
        _rewrite_machine_id_in_csv(csv_path, new_id)
        relative = str(csv_path.relative_to(uz_pmsm_dir)).replace("\\", "/")
        changes.append((relative, machine_id if machine_id is not None else 0, new_id))
    return changes


def _required_numeric_columns(
    *,
    csv_path: Path,
    data: pd.DataFrame,
    columns: tuple[str, ...],
    file_kind: str,
) -> pd.DataFrame:
    missing_columns = set(columns) - set(data.columns)
    if missing_columns:
        raise ValueError(
            f"{file_kind} {csv_path} is missing required columns: {sorted(missing_columns)}"
        )
    try:
        numeric_data = data.loc[:, list(columns)].apply(pd.to_numeric, errors="raise")
    except (TypeError, ValueError) as exc:
        raise ValueError(f"{file_kind} {csv_path} contains non-numeric values: {exc}") from exc
    if not np.isfinite(numeric_data.to_numpy(dtype=float)).all():
        raise ValueError(f"{file_kind} {csv_path} contains non-finite values")
    return numeric_data


def _integer_series(series: pd.Series, *, csv_path: Path, column: str) -> pd.Series:
    numeric_values = pd.to_numeric(series, errors="raise")
    if not np.isfinite(numeric_values.to_numpy(dtype=float)).all():
        raise ValueError(f"{csv_path} column {column} contains non-finite values")
    integer_values = numeric_values.astype(int)
    if not np.array_equal(numeric_values.to_numpy(dtype=float), integer_values.to_numpy(dtype=float)):
        raise ValueError(f"{csv_path} column {column} must contain integer values")
    return integer_values


def _expected_flux_order(flux_map: FluxMap) -> pd.DataFrame:
    expected = flux_map.data.loc[:, ["i_d_A", "i_q_A"]].copy()
    expected.insert(0, "operating_point", range(len(expected)))
    return expected


def _validate_flux_map_file_order(flux_path: Path, flux_map: FluxMap) -> None:
    raw_flux_data = pd.read_csv(flux_path)
    order_data = _required_numeric_columns(
        csv_path=flux_path,
        data=raw_flux_data,
        columns=("i_d_A", "i_q_A"),
        file_kind="Flux map CSV",
    )
    expected_order = _expected_flux_order(flux_map)
    if not np.array_equal(
        order_data.loc[:, ["i_d_A", "i_q_A"]].to_numpy(dtype=float),
        expected_order.loc[:, ["i_d_A", "i_q_A"]].to_numpy(dtype=float),
    ):
        raise ValueError(
            f"Flux map CSV {flux_path} must be stored in canonical row-major order "
            "sorted by i_q_A and then i_d_A"
        )

    if "operating_point" not in raw_flux_data.columns:
        return
    operating_point = _integer_series(
        raw_flux_data["operating_point"],
        csv_path=flux_path,
        column="operating_point",
    )
    if not np.array_equal(
        operating_point.to_numpy(dtype=int),
        expected_order["operating_point"].to_numpy(dtype=int),
    ):
        raise ValueError(
            f"Flux map CSV {flux_path} operating_point must be 0..N-1 in canonical row-major order"
        )


def _validate_differential_inductances_csv(
    differential_path: Path,
    flux_map: FluxMap,
) -> None:
    differential_data = pd.read_csv(differential_path)
    numeric_data = _required_numeric_columns(
        csv_path=differential_path,
        data=differential_data,
        columns=CANONICAL_DIFFERENTIAL_INDUCTANCE_COLUMNS,
        file_kind="Differential inductance CSV",
    )
    actual_order = numeric_data.loc[:, ["operating_point", "i_d_A", "i_q_A"]].copy()
    actual_order = actual_order.assign(
        operating_point=_integer_series(
            actual_order["operating_point"],
            csv_path=differential_path,
            column="operating_point",
        )
    ).reset_index(drop=True)
    expected_order = _expected_flux_order(flux_map)
    if (
        not np.array_equal(
            actual_order["operating_point"].to_numpy(dtype=int),
            expected_order["operating_point"].to_numpy(dtype=int),
        )
        or not np.array_equal(
            actual_order.loc[:, ["i_d_A", "i_q_A"]].to_numpy(dtype=float),
            expected_order.loc[:, ["i_d_A", "i_q_A"]].to_numpy(dtype=float),
        )
    ):
        raise ValueError(
            f"Differential inductance CSV {differential_path} must use the same "
            "operating_point, i_d_A, and i_q_A order as the canonical flux map"
        )


def validate_uz_pmsm_dataset_maps(uz_pmsm_dir: str | Path) -> None:
    """Validate canonical flux-map and differential-inductance CSVs below uz_pmsm_dir."""

    uz_pmsm_dir = Path(uz_pmsm_dir)
    for flux_path in sorted(uz_pmsm_dir.rglob("flux_map.csv")):
        relative_flux_path = flux_path.relative_to(uz_pmsm_dir)
        if len(relative_flux_path.parts) != 3:
            continue
        try:
            flux_map = FluxMap.from_csv(flux_path)
            _validate_flux_map_file_order(flux_path, flux_map)
            differential_path = flux_path.with_name("differential_inductances.csv")
            if differential_path.exists():
                _validate_differential_inductances_csv(differential_path, flux_map)
        except ValueError as exc:
            raise ValueError(f"Invalid PMSM dataset maps below {flux_path.parent}: {exc}") from exc


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
    used_catalog_ids: set[str] = set()
    used_numeric_machine_ids: set[int] = set()

    for csv_path in sorted(uz_pmsm_dir.rglob("machine_parameters.csv")):
        relative_csv_path = csv_path.relative_to(uz_pmsm_dir)
        if len(relative_csv_path.parts) != 3:
            continue

        machine_dir, dataset_dir, _ = relative_csv_path.parts
        try:
            parameters = PMSMParameters.from_csv(csv_path)
            c_dict = parameters.to_c_dict()
        except ValueError as exc:
            raise ValueError(f"Invalid PMSM parameter CSV {csv_path}: {exc}") from exc
        values = parameters.to_dict(include_additional=True)
        c_values = {field.name: c_dict[field.name] for field in c_fields}

        catalog_id = normalize_machine_identifier(f"{machine_dir}_{dataset_dir}")
        if catalog_id in used_catalog_ids:
            raise ValueError(f"Duplicate catalog id generated for {csv_path}: {catalog_id}")
        used_catalog_ids.add(catalog_id)

        numeric_machine_id = int(c_values.get("machine_id", 0))
        if numeric_machine_id <= 0:
            raise ValueError(
                f"machine_id must be a positive integer in {csv_path}; "
                "0 is reserved for manual or unassigned configs"
            )
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
                catalog_id=catalog_id,
                macro_name=f"UZ_PMSM_{catalog_id}_INIT",
                machine_name=machine_name,
                dataset_name=dataset_dir,
                machine_parameters_csv=str(relative_csv_path).replace("\\", "/"),
                parameters=c_values,
            )
        )

    if not entries:
        raise ValueError(f"No machine_parameters.csv files found below {uz_pmsm_dir}")

    validate_uz_pmsm_dataset_maps(uz_pmsm_dir)

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
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames, lineterminator="\n")
        writer.writeheader()
        for entry in entries:
            row = {
                "catalog_id": entry.catalog_id,
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
        "/* Macro naming: UZ_PMSM_<MOTOR_DIR>_<DATASET_DIR>_INIT, uppercased, non-alphanumerics replaced by '_'. */",
        "/* machine_id is a stable, manually assigned identifier reserved for future runtime machine selection. */",
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
    parser.add_argument(
        "--renumber",
        action="store_true",
        default=False,
        help="Before generating, deterministically reassign duplicate machine_id values "
        "or missing/zero ids (useful after merging motors added on separate branches). "
        "Rewrites the affected machine_parameters.csv files.",
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

    if args.renumber:
        changes = renumber_duplicate_machine_ids(args.uz_pmsm_dir)
        if changes:
            print(f"Renumbered {len(changes)} machine_id value(s):")
            for csv_path, old_id, new_id in changes:
                print(f"  {csv_path}: {old_id} -> {new_id}")
        else:
            print("No duplicate, missing, or zero machine_id values found.")

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
