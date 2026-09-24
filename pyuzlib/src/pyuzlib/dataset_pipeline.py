"""Prepare committed PMSM maps from declared dataset sources."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from ._generated_artifacts import check_generated_artifacts
from ._repo_paths import machine_catalog_default_paths
from .pmsm.differential_inductance import DifferentialInductanceMap
from .pmsm.flux_map import FluxMap

SOURCE_FILENAME = "flux_map_source.csv"


def _dataset_outputs(dataset_dir: Path) -> dict[Path, str]:
    recipe_path = dataset_dir / "dataset.json"
    recipe = json.loads(recipe_path.read_text(encoding="utf-8"))
    if not isinstance(recipe, dict) or set(recipe) != {"columns", "edge_order"}:
        raise ValueError(f"{recipe_path}: columns and edge_order are required")
    columns = recipe["columns"]
    if not isinstance(columns, dict) or set(columns) != {"i_d", "i_q", "psi_d", "psi_q"}:
        raise ValueError(f"{recipe_path}: columns must map i_d, i_q, psi_d, and psi_q")
    if not all(isinstance(value, str) and value for value in columns.values()):
        raise ValueError(f"{recipe_path}: column names must be nonempty strings")

    edge_order = recipe["edge_order"]
    if type(edge_order) is not int or edge_order not in (1, 2):
        raise ValueError(f"{recipe_path}: edge_order must be 1 or 2")

    source_path = dataset_dir / SOURCE_FILENAME
    flux_map = FluxMap.from_csv(source_path, columns=columns)
    flux_data = flux_map.data.copy()
    flux_data.insert(0, "operating_point", range(len(flux_data)))
    outputs = {dataset_dir / "flux_map.csv": flux_data.to_csv(index=False)}

    inductances = DifferentialInductanceMap.from_flux_map(flux_map, edge_order=edge_order)
    outputs[dataset_dir / "differential_inductances.csv"] = inductances.data.to_csv(index=False)
    return outputs


def collect_dataset_outputs(uz_pmsm_dir: Path) -> dict[Path, str]:
    outputs: dict[Path, str] = {}
    recipes = sorted(uz_pmsm_dir.glob("*/*/dataset.json"))
    for recipe in recipes:
        outputs.update(_dataset_outputs(recipe.parent))
    for name in ("flux_map_source.csv", "flux_map.csv", "differential_inductances.csv"):
        for path in uz_pmsm_dir.glob(f"*/*/{name}"):
            if not (path.parent / "dataset.json").exists():
                raise ValueError(f"{path}: missing dataset.json")
    return outputs


def main(argv: list[str] | None = None) -> int:
    defaults = machine_catalog_default_paths(__file__)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--uz-pmsm-dir", type=Path, default=defaults["uz_pmsm_dir"])
    parser.add_argument("--check", action="store_true", help="Compare committed maps without writing")
    args = parser.parse_args(argv)
    outputs = collect_dataset_outputs(args.uz_pmsm_dir)
    if args.check:
        return check_generated_artifacts(
            outputs,
            regenerate_args=["python3", "-m", "pyuzlib.dataset_pipeline", "--uz-pmsm-dir", str(args.uz_pmsm_dir.resolve())],
        )
    for path, content in outputs.items():
        path.write_text(content, encoding="utf-8", newline="")
        print(f"Generated: {path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
