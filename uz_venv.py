"""Container-owned development environment, installed from CI-format wheels."""

import hashlib
import os
import sys
import tempfile
from pathlib import Path

from uz_build import venv_bin


def development_environment(root):
    override = os.environ.get("UZ_DEVELOPMENT_ENVIRONMENT")
    if override:
        return Path(override).resolve()
    identity = hashlib.sha256(str(Path(root).resolve()).encode()).hexdigest()[:12]
    cache = Path(os.environ.get("LOCALAPPDATA", Path.home() / ".cache"))
    return cache / "ultrazohm" / "development" / identity


def build_development(root, run):
    """Build the matching wheel pair and update the persistent environment."""
    root = Path(root)
    run([sys.executable, root / "ultrazohm_cli/tasks.py", "release-wheel"])
    run([sys.executable, root / "ultrazohm_dataviewer/tasks.py", "wheel"])
    install_development(root, run)


def install_development(root, run):
    from argparse import Namespace
    from importlib.util import module_from_spec, spec_from_file_location
    from uz_build import single_wheel

    root = Path(root)
    spec = spec_from_file_location(
        "dataviewer_tasks", root / "ultrazohm_dataviewer/tasks.py"
    )
    tasks = module_from_spec(spec)
    spec.loader.exec_module(tasks)
    python = tasks.sync(development_environment(root), inexact=True)
    tasks.install_packages(
        python,
        Namespace(
            cli_wheel=single_wheel(root / "ultrazohm_cli/target/wheels-release"),
            dataviewer_wheel=single_wheel(
                root / "ultrazohm_dataviewer/dist-wheels", "ultrazohm_dataviewer"
            ),
        ),
    )
    with tempfile.TemporaryDirectory(prefix="uz-development-") as directory:
        constraints = Path(directory) / "constraints.txt"
        run(
            [
                "uv",
                "export",
                "--project",
                root / "ultrazohm_dataviewer",
                "--locked",
                "--extra",
                "dev",
                "--no-emit-project",
                "--no-emit-package",
                "ultrazohm-cli",
                "--no-hashes",
                "--output-file",
                constraints,
            ]
        )
        run(
            [
                "uv",
                "pip",
                "install",
                "--python",
                python,
                "--constraint",
                constraints,
                "-r",
                root / "requirements.txt",
            ]
        )
    run(["uv", "pip", "check", "--python", python])


def development_shell(root, run):
    python = venv_bin(development_environment(root))
    if not python.exists():
        raise RuntimeError("Build first: ./uz_developer build linux_wheels")
    run([python, Path(root) / "uz_shell.py"])
