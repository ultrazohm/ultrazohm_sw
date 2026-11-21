"""Fresh local-source shells; uv owns downloads and Rust owns compilation caches."""

import os
import sys
import tempfile
from pathlib import Path


def development_shell(root, run):
    root = Path(root)
    with tempfile.TemporaryDirectory(prefix="uz-dev-") as directory:
        directory = Path(directory)
        wheels = directory / "wheels"
        run([sys.executable, root / "ultrazohm_cli/tasks.py", "wheel", "--out", wheels])
        built = list(wheels.glob("ultrazohm_cli-*.whl"))
        if len(built) != 1:
            raise RuntimeError(
                f"Expected one locally built CLI wheel, found {len(built)}"
            )
        constraints = directory / "constraints.txt"
        run(
            [
                "uv",
                "export",
                "--project",
                root / "ultrazohm_dataviewer",
                "--locked",
                "--no-dev",
                "--no-emit-project",
                "--no-emit-package",
                "ultrazohm-cli",
                "--no-hashes",
                "--format",
                "requirements.txt",
                "--output-file",
                constraints,
            ]
        )
        venv = directory / "environment"
        run(
            [
                "uv",
                "venv",
                "--python",
                (root / ".python-version").read_text().strip(),
                venv,
            ]
        )
        python = venv / ("Scripts/python.exe" if os.name == "nt" else "bin/python")
        run(
            [
                "uv",
                "pip",
                "install",
                "--python",
                python,
                "--no-sources",
                "--constraint",
                constraints,
                "--only-binary",
                "imgui-bundle",
                built[0],
                "--editable",
                root / "ultrazohm_dataviewer",
                "--requirements",
                root / "requirements.txt",
            ]
        )
        run(["uv", "pip", "check", "--python", python])
        print(
            f"Local development environment: {venv}\n"
            "Close applications before exiting this shell; its environment is temporary.",
            flush=True,
        )
        run([python, root / "uz_shell.py"])
