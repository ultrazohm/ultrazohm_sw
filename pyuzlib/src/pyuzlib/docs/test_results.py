"""Locate existing C-test artifacts for plotting; never run tests or write files."""

from __future__ import annotations

import os
from pathlib import Path

from .._repo_paths import repo_root_from


def pmsm_swmodel_result_paths(
    artifact_dir: str | Path | None = None,
) -> tuple[Path, Path]:
    """Return result/config CSV paths, honoring the test exporter directory override.

    Relative overrides are interpreted against the caller's working directory.
    Use an absolute UZ_TEST_DATA_DIR when tests and plots run from different places.
    """
    selected = artifact_dir if artifact_dir is not None else os.environ.get("UZ_TEST_DATA_DIR")
    root = (
        Path(selected).resolve()
        if selected
        else repo_root_from(__file__) / "vitis/software/Baremetal/build/artifacts/test-data"
    )
    directory = root / "uz/uz_pmsm_swmodel"
    paths = (
        directory / "uz_pmsm_swmodel_results.csv",
        directory / "uz_pmsm_swmodel_config.csv",
    )
    missing = [str(path) for path in paths if not path.is_file()]
    if missing:
        raise FileNotFoundError(
            "Missing PMSM test artifacts: " + ", ".join(missing)
            + ". Enable CEEDLING_GLOBAL_CSV_EXPORT in "
            "vitis/software/Baremetal/src/uz/uz_global_configuration.h, then run "
            "'make ceedling-test' from the repository root, or "
            "'ceedling test:test_uz_pmsm_swmodel' from vitis/software/Baremetal. "
            "Restore the export switch to 0 afterwards. For a custom directory, "
            "use the same absolute UZ_TEST_DATA_DIR for tests and plots."
        )
    return paths
