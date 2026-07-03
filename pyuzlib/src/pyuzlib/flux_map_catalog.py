from __future__ import annotations

import argparse
from dataclasses import dataclass
from pathlib import Path

from ._repo_paths import machine_catalog_default_paths
from ._repo_paths import repo_root_from
from .machine_catalog import format_c_float
from .machine_catalog import format_path_for_generated_comment
from .machine_catalog import normalize_machine_identifier
from .pmsm.differential_inductance import DifferentialInductanceMap
from .pmsm.flux_map import FluxMap


@dataclass(frozen=True)
class FluxMapCatalogEntry:
    catalog_id: str
    machine_dir: str
    dataset_dir: str
    flux_map_csv: str
    i_d_breakpoints_A: tuple[float, ...]
    i_q_breakpoints_A: tuple[float, ...]
    psi_d_Vs: tuple[float, ...]  # row-major, i_d (x-axis) changing fastest
    psi_q_Vs: tuple[float, ...]  # row-major, i_d (x-axis) changing fastest


@dataclass(frozen=True)
class DifferentialInductanceCatalogEntry:
    catalog_id: str
    machine_dir: str
    dataset_dir: str
    differential_inductances_csv: str
    i_d_breakpoints_A: tuple[float, ...]
    i_q_breakpoints_A: tuple[float, ...]
    L_dd_H: tuple[float, ...]  # row-major, i_d (x-axis) changing fastest
    L_dq_H: tuple[float, ...]
    L_qd_H: tuple[float, ...]
    L_qq_H: tuple[float, ...]


def flux_map_catalog_default_paths(anchor: str | Path) -> dict[str, Path]:
    paths = machine_catalog_default_paths(anchor)
    paths["flux_map_header_output"] = (
        paths["repo_root"]
        / "vitis/software/Baremetal/src/uz/uz_pmsm_flux_map/uz_pmsm_flux_maps_auto_generated.h"
    )
    paths["differential_inductance_header_output"] = (
        paths["repo_root"]
        / "vitis/software/Baremetal/src/uz/uz_pmsm_differential_inductance"
        / "uz_pmsm_differential_inductances_auto_generated.h"
    )
    return paths


def discover_flux_map_catalog(uz_pmsm_dir: str | Path) -> list[FluxMapCatalogEntry]:
    uz_pmsm_dir = Path(uz_pmsm_dir)
    entries: list[FluxMapCatalogEntry] = []
    used_catalog_ids: set[str] = set()

    for csv_path in sorted(uz_pmsm_dir.rglob("flux_map.csv")):
        relative_csv_path = csv_path.relative_to(uz_pmsm_dir)
        if len(relative_csv_path.parts) != 3:
            continue
        machine_dir, dataset_dir, _ = relative_csv_path.parts

        try:
            flux_map = FluxMap.from_csv(csv_path)
        except (ValueError, FileNotFoundError) as exc:
            raise ValueError(f"Invalid flux map CSV {csv_path}: {exc}") from exc

        # FluxMap.psi_d/.psi_q pivot to index=i_q_A (rows), columns=i_d_A (cols), both ascending.
        # ravel() is row-major -> i_d fastest, matching uz_LUT_2D (index = i_q_idx * N_id + i_d_idx).
        psi_d = flux_map.psi_d
        psi_q = flux_map.psi_q
        i_d_breakpoints = tuple(float(value) for value in psi_d.columns.to_numpy())
        i_q_breakpoints = tuple(float(value) for value in psi_d.index.to_numpy())
        psi_d_flat = tuple(float(value) for value in psi_d.to_numpy().ravel())
        psi_q_flat = tuple(float(value) for value in psi_q.to_numpy().ravel())

        catalog_id = normalize_machine_identifier(f"{machine_dir}_{dataset_dir}")
        if catalog_id in used_catalog_ids:
            raise ValueError(f"Duplicate catalog id generated for {csv_path}: {catalog_id}")
        used_catalog_ids.add(catalog_id)

        entries.append(
            FluxMapCatalogEntry(
                catalog_id=catalog_id,
                machine_dir=machine_dir,
                dataset_dir=dataset_dir,
                flux_map_csv=str(relative_csv_path).replace("\\", "/"),
                i_d_breakpoints_A=i_d_breakpoints,
                i_q_breakpoints_A=i_q_breakpoints,
                psi_d_Vs=psi_d_flat,
                psi_q_Vs=psi_q_flat,
            )
        )

    if not entries:
        raise ValueError(f"No flux_map.csv files found below {uz_pmsm_dir}")
    return entries


def discover_differential_inductance_catalog(
    uz_pmsm_dir: str | Path,
) -> list[DifferentialInductanceCatalogEntry]:
    uz_pmsm_dir = Path(uz_pmsm_dir)
    entries: list[DifferentialInductanceCatalogEntry] = []
    used_catalog_ids: set[str] = set()

    for csv_path in sorted(uz_pmsm_dir.rglob("differential_inductances.csv")):
        relative_csv_path = csv_path.relative_to(uz_pmsm_dir)
        if len(relative_csv_path.parts) != 3:
            continue
        machine_dir, dataset_dir, _ = relative_csv_path.parts

        try:
            diff_ind = DifferentialInductanceMap.from_csv(csv_path)
        except (ValueError, FileNotFoundError) as exc:
            raise ValueError(f"Invalid differential inductance CSV {csv_path}: {exc}") from exc

        # .L_dd/.L_dq/.L_qd/.L_qq pivot to index=i_q_A (rows), columns=i_d_A (cols), both ascending.
        # ravel() is row-major -> i_d fastest, matching uz_LUT_2D (index = i_q_idx * N_id + i_d_idx).
        L_dd = diff_ind.L_dd
        i_d_breakpoints = tuple(float(value) for value in L_dd.columns.to_numpy())
        i_q_breakpoints = tuple(float(value) for value in L_dd.index.to_numpy())

        catalog_id = normalize_machine_identifier(f"{machine_dir}_{dataset_dir}")
        if catalog_id in used_catalog_ids:
            raise ValueError(f"Duplicate catalog id generated for {csv_path}: {catalog_id}")
        used_catalog_ids.add(catalog_id)

        entries.append(
            DifferentialInductanceCatalogEntry(
                catalog_id=catalog_id,
                machine_dir=machine_dir,
                dataset_dir=dataset_dir,
                differential_inductances_csv=str(relative_csv_path).replace("\\", "/"),
                i_d_breakpoints_A=i_d_breakpoints,
                i_q_breakpoints_A=i_q_breakpoints,
                L_dd_H=tuple(float(value) for value in L_dd.to_numpy().ravel()),
                L_dq_H=tuple(float(value) for value in diff_ind.L_dq.to_numpy().ravel()),
                L_qd_H=tuple(float(value) for value in diff_ind.L_qd.to_numpy().ravel()),
                L_qq_H=tuple(float(value) for value in diff_ind.L_qq.to_numpy().ravel()),
            )
        )

    if not entries:
        raise ValueError(f"No differential_inductances.csv files found below {uz_pmsm_dir}")
    return entries


def _render_inline_float_list(values: tuple[float, ...]) -> str:
    return "{ " + ", ".join(format_c_float(value) for value in values) + " }"


def _render_grid_macro(name: str, values: tuple[float, ...], columns_per_row: int) -> str:
    lines = [f"#define {name} \\", "    { \\"]
    for row_start in range(0, len(values), columns_per_row):
        row = values[row_start:row_start + columns_per_row]
        lines.append("        " + ", ".join(format_c_float(value) for value in row) + ", \\")
    lines.append("    }")
    return "\n".join(lines)


def render_flux_map_header(
    entries: list[FluxMapCatalogEntry],
    *,
    source_root: str | Path,
    generator_script: str,
) -> str:
    source_root = Path(source_root)
    repo_root = repo_root_from(source_root)
    source_root_comment = format_path_for_generated_comment(source_root, repo_root)
    lines = [
        "#ifndef UZ_PMSM_FLUX_MAPS_AUTO_GENERATED_H",
        "#define UZ_PMSM_FLUX_MAPS_AUTO_GENERATED_H",
        "",
        "#pragma once",
        "",
        f"/* This file is auto-generated by {generator_script}. */",
        f"/* Source PMSM datasets root: {source_root_comment} */",
        "/* Do not edit this file manually. */",
        "/* Each macro expands to a C initializer list; a macro that is never used costs zero bytes. */",
        "/* Macro naming: UZ_FLUXMAP_<MOTOR_DIR>_<DATASET_DIR>_..., uppercased, non-alphanumerics replaced by '_'. */",
        "/* psi_d/psi_q arrays are row-major with i_d (x-axis) changing fastest, matching uz_LUT_2D. */",
        "",
    ]

    for entry in entries:
        n_id = len(entry.i_d_breakpoints_A)
        n_iq = len(entry.i_q_breakpoints_A)
        prefix = f"UZ_FLUXMAP_{entry.catalog_id}"
        lines.append(
            f"/* {entry.machine_dir} ({entry.dataset_dir}) from {entry.flux_map_csv}; "
            f"grid {n_id} x {n_iq} (i_d x i_q) */"
        )
        lines.append(f"#define {prefix}_I_D_LENGTH {n_id}")
        lines.append(f"#define {prefix}_I_Q_LENGTH {n_iq}")
        lines.append(f"#define {prefix}_I_D_BREAKPOINTS_A {_render_inline_float_list(entry.i_d_breakpoints_A)}")
        lines.append(f"#define {prefix}_I_Q_BREAKPOINTS_A {_render_inline_float_list(entry.i_q_breakpoints_A)}")
        lines.append(_render_grid_macro(f"{prefix}_PSI_D_VS", entry.psi_d_Vs, n_id))
        lines.append(_render_grid_macro(f"{prefix}_PSI_Q_VS", entry.psi_q_Vs, n_id))
        lines.append("")

    lines.append("#endif // UZ_PMSM_FLUX_MAPS_AUTO_GENERATED_H")
    lines.append("")
    return "\n".join(lines)


def generate_flux_map_header(
    *,
    uz_pmsm_dir: str | Path,
    header_output: str | Path,
    generator_script: str,
) -> list[FluxMapCatalogEntry]:
    entries = discover_flux_map_catalog(uz_pmsm_dir)
    header_output = Path(header_output)
    header_output.parent.mkdir(parents=True, exist_ok=True)
    header_output.write_text(
        render_flux_map_header(
            entries,
            source_root=uz_pmsm_dir,
            generator_script=generator_script,
        ),
        encoding="utf-8",
    )
    return entries


def render_differential_inductance_header(
    entries: list[DifferentialInductanceCatalogEntry],
    *,
    source_root: str | Path,
    generator_script: str,
) -> str:
    source_root = Path(source_root)
    repo_root = repo_root_from(source_root)
    source_root_comment = format_path_for_generated_comment(source_root, repo_root)
    lines = [
        "#ifndef UZ_PMSM_DIFFERENTIAL_INDUCTANCES_AUTO_GENERATED_H",
        "#define UZ_PMSM_DIFFERENTIAL_INDUCTANCES_AUTO_GENERATED_H",
        "",
        "#pragma once",
        "",
        f"/* This file is auto-generated by {generator_script}. */",
        f"/* Source PMSM datasets root: {source_root_comment} */",
        "/* Do not edit this file manually. */",
        "/* Each macro expands to a C initializer list; a macro that is never used costs zero bytes. */",
        "/* Macro naming: UZ_DIFFIND_<MOTOR_DIR>_<DATASET_DIR>_..., uppercased, non-alphanumerics replaced by '_'. */",
        "/* L_dd/L_dq/L_qd/L_qq arrays are row-major with i_d (x-axis) changing fastest, matching uz_LUT_2D. */",
        "",
    ]

    for entry in entries:
        n_id = len(entry.i_d_breakpoints_A)
        n_iq = len(entry.i_q_breakpoints_A)
        prefix = f"UZ_DIFFIND_{entry.catalog_id}"
        lines.append(
            f"/* {entry.machine_dir} ({entry.dataset_dir}) from {entry.differential_inductances_csv}; "
            f"grid {n_id} x {n_iq} (i_d x i_q) */"
        )
        lines.append(f"#define {prefix}_I_D_LENGTH {n_id}")
        lines.append(f"#define {prefix}_I_Q_LENGTH {n_iq}")
        lines.append(f"#define {prefix}_I_D_BREAKPOINTS_A {_render_inline_float_list(entry.i_d_breakpoints_A)}")
        lines.append(f"#define {prefix}_I_Q_BREAKPOINTS_A {_render_inline_float_list(entry.i_q_breakpoints_A)}")
        lines.append(_render_grid_macro(f"{prefix}_L_DD_H", entry.L_dd_H, n_id))
        lines.append(_render_grid_macro(f"{prefix}_L_DQ_H", entry.L_dq_H, n_id))
        lines.append(_render_grid_macro(f"{prefix}_L_QD_H", entry.L_qd_H, n_id))
        lines.append(_render_grid_macro(f"{prefix}_L_QQ_H", entry.L_qq_H, n_id))
        lines.append("")

    lines.append("#endif // UZ_PMSM_DIFFERENTIAL_INDUCTANCES_AUTO_GENERATED_H")
    lines.append("")
    return "\n".join(lines)


def generate_differential_inductance_header(
    *,
    uz_pmsm_dir: str | Path,
    header_output: str | Path,
    generator_script: str,
) -> list[DifferentialInductanceCatalogEntry]:
    entries = discover_differential_inductance_catalog(uz_pmsm_dir)
    header_output = Path(header_output)
    header_output.parent.mkdir(parents=True, exist_ok=True)
    header_output.write_text(
        render_differential_inductance_header(
            entries,
            source_root=uz_pmsm_dir,
            generator_script=generator_script,
        ),
        encoding="utf-8",
    )
    return entries


def build_arg_parser(default_anchor: str | Path) -> argparse.ArgumentParser:
    defaults = flux_map_catalog_default_paths(default_anchor)
    parser = argparse.ArgumentParser(
        description="Generate the PMSM flux-map C macro header from the docs datasets.",
    )
    parser.add_argument("--uz-pmsm-dir", type=Path, default=defaults["uz_pmsm_dir"])
    parser.add_argument(
        "--header-output",
        type=Path,
        default=defaults["flux_map_header_output"],
    )
    parser.add_argument(
        "--diffind-header-output",
        type=Path,
        default=defaults["differential_inductance_header_output"],
    )
    return parser


def main(argv: list[str] | None = None, *, default_anchor: str | Path | None = None) -> int:
    anchor = default_anchor or __file__
    parser = build_arg_parser(anchor)
    args = parser.parse_args(argv)

    flux_entries = generate_flux_map_header(
        uz_pmsm_dir=args.uz_pmsm_dir,
        header_output=args.header_output,
        generator_script="pyuzlib.flux_map_catalog",
    )
    print(f"Generated {len(flux_entries)} PMSM flux-map entries")
    print(f"Header: {Path(args.header_output).resolve()}")

    diffind_entries = generate_differential_inductance_header(
        uz_pmsm_dir=args.uz_pmsm_dir,
        header_output=args.diffind_header_output,
        generator_script="pyuzlib.flux_map_catalog",
    )
    print(f"Generated {len(diffind_entries)} PMSM differential-inductance entries")
    print(f"Header: {Path(args.diffind_header_output).resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
