"""Viewer build implementation shared by the repository launcher and CI."""

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
import tomllib
from contextlib import nullcontext
from functools import partial
from pathlib import Path

HERE = Path(__file__).resolve().parent
CLI = HERE.parent / "ultrazohm_cli"
sys.path.insert(0, str(HERE.parent))
from uz_build import build_lock, single_wheel, venv_bin, wheel_version  # noqa: E402
from uz_build import run as build_run  # noqa: E402

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


run = partial(build_run, cwd=HERE)

python_in = venv_bin


def sync(venv):
    """Install the locked dependencies into ``venv`` and return its interpreter."""
    env = os.environ.copy()
    env["UV_PROJECT_ENVIRONMENT"] = str(venv)
    run(*SYNC, env=env)
    return python_in(venv)


def cli_tasks(*args):
    run(sys.executable, CLI / "tasks.py", *args)


built_wheel = single_wheel


def install_packages(python, args, *, release=False):
    if args.cli_wheel is None:
        with tempfile.TemporaryDirectory(prefix="cli-release-wheel-") as directory:
            cli_tasks("wheel" if release else "debug-wheel", "--out", directory)
            from argparse import Namespace

            return install_packages(
                python,
                Namespace(**{**vars(args), "cli_wheel": built_wheel(Path(directory))}),
            )
    cli_wheel = args.cli_wheel
    cli_wheel = Path(cli_wheel).resolve()
    version = wheel_version(cli_wheel)
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
    with tempfile.TemporaryDirectory(prefix="uz-viewer-test-") as directory:
        python = sync(Path(directory) / "environment")
        install_packages(python, args)
        run(python, "-m", "pytest", "-q", env={**os.environ, "UZ_TEST_INSTALLED": "1"})
        if getattr(args, "gui_smoke", False):
            run(python, HERE / "build/smoke_gui.py")


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
    with tempfile.TemporaryDirectory(prefix="uz-viewer-build-") as directory:
        python = sync(Path(directory) / "environment")
        install_packages(python, args, release=True)
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
    python = sys.executable  # Smoke drivers use only the standard library.
    executable = HERE / "dist" / "ultrazohm-dataviewer" / "ultrazohm-dataviewer.exe"
    run(python, Path("build") / "smoke_binary.py", executable)
    run(python, Path("build") / "smoke_live.py", executable)
    run(python, Path("build") / "smoke_powershell.py", executable.with_suffix(".ps1"))


def _invocation():
    prefix = ".\\uz_developer.ps1" if WINDOWS else "./uz_developer"
    return lambda task, args="": (
        f"{prefix} task viewer {task}" + (f" {args}" if args else "")
    )


def overview():
    print(
        "Viewer build tasks: lint, format, format-check, test, check, wheel, bundle, bundle-smoke"
    )
    print(
        "Use ./uz venv dev to run both applications; ./uz_developer task viewer TASK --help for details."
    )


DESCRIPTIONS = {
    "check": "Lint and run the full test suite in a temporary environment, as CI does. Without --cli-wheel, a debug "
    "CLI wheel is built from ../ultrazohm_cli so live tests use this checkout.",
    "bundle": "Build the PyInstaller desktop bundle in dist/ from a temporary environment. Without --cli-wheel, a "
    "release CLI wheel is built from ../ultrazohm_cli. Standalone bundles are Windows-only; "
    "Linux uses Python wheels.",
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
        if name in ("test", "check"):
            task.add_argument(
                "--gui-smoke",
                action="store_true",
                help="Also launch the installed GUI (requires a display)",
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
    argv = list(sys.argv[1:] if argv is None else argv)
    if not argv or argv[0] in ("-h", "--help", "help"):
        overview()
        return
    args = parser.parse_args(argv)
    try:
        # Private wheel outputs need no shared lock (bundle may invoke wheel).
        shared = args.task in ("bundle", "bundle-smoke") or (
            args.task == "wheel" and args.out is None
        )
        with build_lock(HERE.parent, "viewer") if shared else nullcontext():
            args.function(args)
    except RuntimeError as error:
        raise SystemExit(str(error)) from None
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1) from None


if __name__ == "__main__":
    main()
