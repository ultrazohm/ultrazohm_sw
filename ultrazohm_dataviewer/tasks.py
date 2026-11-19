"""Viewer build implementation shared by the repository launcher and CI."""

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
import tomllib
import zipfile
from email.parser import BytesParser
from pathlib import Path

HERE = Path(__file__).resolve().parent
CLI = HERE.parent / "ultrazohm_cli"
WINDOWS = os.name == "nt"
# The repository's single Python pin. uv reads .python-version only inside the
# project directory, so pass it explicitly.
PYTHON = (HERE.parent / ".python-version").read_text(encoding="utf-8").strip()
SYNC = [
    "uv",
    "sync",
    "--locked",
    "--extra",
    "dev",
    "--python",
    PYTHON,
    "--no-build-package",
    "imgui-bundle",
    "--no-install-project",
    "--no-install-package",
    "ultrazohm-cli",
]


def run(*command, cwd=HERE, env=None):
    command = [str(part) for part in command]
    print("+", " ".join(command), flush=True)
    subprocess.run(command, cwd=cwd, env=env, check=True)


def python_in(venv):
    return venv / ("Scripts/python.exe" if WINDOWS else "bin/python")


def sync(venv):
    """Install the locked dependencies into ``venv`` and return its interpreter."""
    env = os.environ.copy()
    env["UV_PROJECT_ENVIRONMENT"] = str(venv)
    run(*SYNC, env=env)
    return python_in(venv)


def cli_tasks(*args):
    run(sys.executable, CLI / "tasks.py", *args)


def built_wheel(directory):
    wheels = sorted(directory.glob("ultrazohm_cli-*.whl"))
    if len(wheels) != 1:
        raise SystemExit(
            f"Expected exactly one wheel in {directory}, found {len(wheels)}"
        )
    return wheels[0]


def install_packages(python, args):
    cli_wheel = args.cli_wheel
    if cli_wheel is None:
        cli_tasks("debug-wheel")
        cli_wheel = built_wheel(CLI / "target" / "wheels-debug")
    cli_wheel = Path(cli_wheel).resolve()
    with zipfile.ZipFile(cli_wheel) as archive:
        metadata_path = next(
            n for n in archive.namelist() if n.endswith(".dist-info/METADATA")
        )
        version = BytesParser().parsebytes(archive.read(metadata_path))["Version"]
    viewer_wheel = args.viewer_wheel
    with tempfile.TemporaryDirectory(prefix="viewer-wheel-") as directory:
        if viewer_wheel is None:
            run(
                sys.executable,
                HERE / "tasks.py",
                "wheel",
                "--out",
                directory,
                env={**os.environ, "UZ_CLI_RELEASE_VERSION": version},
            )
            (viewer_wheel,) = Path(directory).glob("*.whl")
        run(
            "uv",
            "pip",
            "install",
            "--python",
            python,
            "--reinstall",
            "--no-deps",
            cli_wheel,
            Path(viewer_wheel).resolve(),
        )
    run("uv", "pip", "check", "--python", python)
    # Import from outside the checkout to catch absent package data/imports.
    with tempfile.TemporaryDirectory(prefix="installed-viewer-") as directory:
        run(python, "-m", "ultrazohm_dataviewer", "--help", cwd=directory)
        run(python, "-m", "ultrazohm_cli", "--version", cwd=directory)


def ruff(*arguments):
    """Run this project's pinned Ruff without installing application dependencies."""
    config = HERE / "pyproject.toml"
    settings = tomllib.loads(config.read_text(encoding="utf-8"))["tool"]["ruff"]
    run(
        "uv",
        "tool",
        "run",
        "--from",
        "ruff" + settings["required-version"],
        "ruff",
        *arguments,
        "--config",
        config,
        ".",
    )


def lint(_args):
    """Check this project's Python code without changing files."""
    ruff("check")


def format_code(_args):
    """Format this project's Python code in place (no lint fixes)."""
    ruff("format")


def format_check(_args):
    """Check this project's Python formatting without changing files."""
    ruff("format", "--check")


def test(args):
    """Run pytest with a CLI wheel matching this checkout."""
    python = sync(HERE / ".venv-ci")
    install_packages(python, args)
    run(python, "-m", "pytest", "-q", env={**os.environ, "UZ_TEST_INSTALLED": "1"})


def check(args):
    """Lint and test, as CI does."""
    lint(args)
    format_check(args)
    test(args)


def wheel(args):
    """Build the publishable viewer wheel from staged sources."""
    sys.path.insert(0, str(HERE / "tools"))
    from release_build import staged_project

    output = args.out.resolve() if args.out else HERE / "dist-wheels"
    with staged_project(HERE, os.environ.get("UZ_CLI_RELEASE_VERSION")) as (
        stage,
        _version,
    ):
        run("uv", "build", "--wheel", "--out-dir", output, stage)


def bundle(args):
    """Build the PyInstaller desktop bundle in dist/."""
    if not WINDOWS:
        raise SystemExit(
            "Standalone bundles are Windows-only; use the Python wheel on Linux."
        )
    python = sync(HERE / ".venv-build")
    install_packages(python, args)
    shutil.rmtree(HERE / "build" / "native", ignore_errors=True)
    shutil.rmtree(HERE / "dist", ignore_errors=True)
    run(
        python,
        "-m",
        "PyInstaller",
        "--noconfirm",
        "--clean",
        "--distpath",
        "dist",
        "--workpath",
        Path("build") / "native",
        Path("build") / "ultrazohm_dataviewer.spec",
    )
    shutil.copy2(
        HERE / "build" / "ultrazohm-dataviewer.ps1",
        HERE / "dist" / "ultrazohm-dataviewer",
    )
    print(f"Built: {HERE / 'dist' / 'ultrazohm-dataviewer'}", flush=True)


def bundle_smoke(_args):
    """Start the bundle and its live workers headless."""
    python = python_in(HERE / ".venv-build")
    executable = HERE / "dist" / "ultrazohm-dataviewer" / "ultrazohm-dataviewer.exe"
    run(python, Path("build") / "smoke_binary.py", executable)
    run(python, Path("build") / "smoke_live.py", executable)
    run(python, Path("build") / "smoke_powershell.py", executable.with_suffix(".ps1"))


def _invocation():
    prefix = ".\\uz.ps1" if WINDOWS else "./uz"
    return lambda task, args="": (
        f"{prefix} task viewer {task}" + (f" {args}" if args else "")
    )


def overview():
    print(
        "Viewer build tasks: setup, shell, lint, format, format-check, test, check, bundle, bundle-smoke"
    )
    print(
        "Use ./uz shell to run both applications; ./uz task viewer TASK --help for details."
    )


DESCRIPTIONS = {
    "check": "Lint and run the full test suite in .venv-ci, as CI does. Without --cli-wheel, a debug "
    "CLI wheel is built from ../ultrazohm_cli so live tests use this checkout.",
    "bundle": "Build the PyInstaller desktop bundle in dist/ from .venv-build. Without --cli-wheel, a "
    "release CLI wheel is built from ../ultrazohm_cli. A bundle runs on systems with at least the "
    "build system's glibc; CI builds the published one on Ubuntu 22.04.",
}


def main(argv=None):
    call = _invocation()
    parser = argparse.ArgumentParser(prog=call("").strip(), add_help=False)
    tasks = parser.add_subparsers(dest="task")

    def add(name, function, *, wheel=False):
        task = tasks.add_parser(
            name, prog=call(name), description=DESCRIPTIONS.get(name, function.__doc__)
        )
        if wheel:
            task.add_argument("--cli-wheel", type=Path, help="matching CLI wheel")
            task.add_argument(
                "--viewer-wheel",
                type=Path,
                help="matching viewer wheel; otherwise build it",
            )
        task.set_defaults(function=function)

    for name, function, needs_wheel in (
        ("format", format_code, False),
        ("format-check", format_check, False),
        ("lint", lint, False),
        ("test", test, True),
        ("check", check, True),
        ("bundle", bundle, True),
        ("bundle-smoke", bundle_smoke, False),
    ):
        add(name, function, wheel=needs_wheel)
    wheel_task = tasks.add_parser("wheel", description=wheel.__doc__)
    wheel_task.add_argument("--out", type=Path)
    wheel_task.set_defaults(function=wheel)
    from tools.setup_env import setup_task

    for name in ("setup", "shell"):
        setup_parser = tasks.add_parser(
            name, description="Prepare this application's environment."
        )
        setup_parser.add_argument(
            "source", nargs="?", choices=("local", "stable", "prerelease")
        )
        setup_parser.set_defaults(function=setup_task)
    argv = list(sys.argv[1:] if argv is None else argv)
    if not argv or argv[0] in ("-h", "--help", "help"):
        overview()
        return
    args = parser.parse_args(argv)
    try:
        args.function(args)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1) from None


if __name__ == "__main__":
    main()
