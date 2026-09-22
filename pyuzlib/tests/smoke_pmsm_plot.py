"""Opt-in C-export-to-Python-plot check, separate from the ordinary pytest suite."""

from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import runpy
import shlex
import subprocess
import tempfile
from unittest.mock import patch

from pyuzlib._repo_paths import repo_root_from


def check_and_render(artifact_dir: Path, plot_script: Path, png_path: Path) -> None:
    import matplotlib

    matplotlib.use("Agg", force=True)
    import matplotlib.pyplot as plt
    import numpy as np
    import pandas as pd

    from pyuzlib.docs.test_results import pmsm_swmodel_result_paths

    results_path, config_path = pmsm_swmodel_result_paths(artifact_dir)
    results = pd.read_csv(results_path, sep=";")
    config = pd.read_csv(config_path, sep=";")
    required_columns = {
        "time", "input_d", "input_q", "input_omega_mech_1_s", "input_load_torque",
        "output_d", "output_q", "output_torque_Nm", "output_omega_mech_1_s",
    }
    missing = required_columns - set(results.columns)
    if missing:
        raise ValueError(f"Exported results lack plot columns: {sorted(missing)}")
    if len(results) < 2 or len(config) != 1:
        raise ValueError("Expected at least two result rows and exactly one configuration row")
    if not np.isfinite(results.to_numpy(dtype=float)).all() or not np.isfinite(config.to_numpy(dtype=float)).all():
        raise ValueError("Exported CSVs contain non-finite data")
    if "output_sample_time" not in config:
        raise ValueError("Exported configuration lacks output_sample_time")
    sample_time = float(config["output_sample_time"].iloc[0])
    if sample_time <= 0 or results["time"].iloc[0] != 0 or not np.allclose(
        np.diff(results["time"]), sample_time, rtol=1e-5, atol=1e-10,
    ):
        raise ValueError("Exported timestamps do not match the configuration sample time")

    try:
        # Execute the real docs reader, including its environment-based path lookup.
        with patch.object(plt, "show"):
            namespace = runpy.run_path(str(plot_script))
        if namespace["CSV_PATH"] != results_path or namespace["CONFIG_CSV_PATH"] != config_path:
            raise ValueError("Plot reader did not consume this smoke test's fresh artifacts")
        figure = namespace["fig"]
        if len(figure.axes) != 4 or any(len(axis.lines) != 2 for axis in figure.axes):
            raise ValueError("Expected all four PMSM plots with two data series each")
        figure.savefig(png_path)
        if not png_path.read_bytes().startswith(b"\x89PNG\r\n\x1a\n") or png_path.stat().st_size < 1000:
            raise ValueError("Plot rendering did not produce a valid nonempty PNG")
    finally:
        plt.close("all")
    print(f"PMSM plot smoke test passed: {len(results)} C-exported rows rendered to PNG.")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--ceedling", default="ceedling", help="Ceedling command (default: ceedling)")
    args = parser.parse_args(argv)
    command = shlex.split(args.ceedling)
    if not command:
        parser.error("--ceedling must name a command")
    repo_root = repo_root_from(__file__)
    baremetal = repo_root / "vitis/software/Baremetal"
    with tempfile.TemporaryDirectory(prefix="uz-pmsm-plot-smoke-") as directory:
        scratch = Path(directory).resolve()
        # Only the C helper may create this directory: missing exports must fail.
        artifact_dir = scratch / "test-data"
        build_mixin = scratch / "build.yml"
        build_mixin.write_text(
            ":project:\n  :build_root: " + json.dumps(str(scratch / "build")) + "\n",
            encoding="utf-8",
        )
        os.environ["UZ_TEST_DATA_DIR"] = str(artifact_dir)
        os.environ["MPLCONFIGDIR"] = str(scratch / "matplotlib")
        os.environ["MPLBACKEND"] = "Agg"
        subprocess.run(
            [
                *command, "--mixin=config/csv_export.yml", f"--mixin={build_mixin}",
                "test:test_uz_pmsm_swmodel",
            ],
            cwd=baremetal,
            check=True,
        )
        check_and_render(
            artifact_dir,
            repo_root / "docs/source/software/control/uz_pmsm_swmodel/view_pmsm_model_test_results.py",
            scratch / "pmsm.png",
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
