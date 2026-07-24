from __future__ import annotations

from pathlib import Path


def repo_root_from(path: str | Path) -> Path:
    path = Path(path).resolve()
    for candidate in [path, *path.parents]:
        if (candidate / "pyuzlib/pyproject.toml").exists() and (candidate / "vitis").exists():
            return candidate
    raise ValueError(f"Could not determine repository root from {path}")


def machine_catalog_default_paths(anchor: str | Path) -> dict[str, Path]:
    repo_root = repo_root_from(anchor)
    return {
        "repo_root": repo_root,
        "uz_pmsm_dir": repo_root / "docs/source/software/control/uz_pmsm",
        "inventory_output": repo_root / "docs/source/software/control/uz_pmsm/available_machines.csv",
        "c_header_path": repo_root / "vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        "generated_header_output": repo_root / "vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_available_machines_auto_generated.h",
    }