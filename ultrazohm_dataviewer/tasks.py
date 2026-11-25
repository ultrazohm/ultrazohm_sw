"""Viewer build tasks, run as ``./uz_developer dataviewer TASK`` locally and in CI."""

import os
import shutil
import sys
import tempfile
import tomllib
from functools import partial
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
from uz_build import Task, single_wheel, venv_bin, wheel_version  # noqa: E402
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


def sync(venv, *, inexact=False):
    """Install the locked dependencies into ``venv`` and return its interpreter."""
    env = os.environ.copy()
    env["UV_PROJECT_ENVIRONMENT"] = str(venv)
    run(*SYNC, *(["--inexact"] if inexact else []), env=env)
    return python_in(venv)


# The CLI tasks building the wheel the DataViewer is tested or bundled with.
CLI_WHEEL_TASKS = {False: "debug-wheel", True: "release-wheel"}


def cli_tasks(*args):
    run(sys.executable, HERE.parent / "uz_developer.py", "cli", *args)


built_wheel = single_wheel


def install_packages(python, args, *, release=False):
    if args.cli_wheel is None:
        with tempfile.TemporaryDirectory(prefix="cli-release-wheel-") as directory:
            cli_tasks(CLI_WHEEL_TASKS[release], "--out", directory)
            from argparse import Namespace

            return install_packages(
                python,
                Namespace(**{**vars(args), "cli_wheel": built_wheel(Path(directory))}),
            )
    cli_wheel = args.cli_wheel
    cli_wheel = Path(cli_wheel).resolve()
    version = wheel_version(cli_wheel)
    dataviewer_wheel = args.dataviewer_wheel
    with tempfile.TemporaryDirectory(prefix="dataviewer-wheel-") as directory:
        if dataviewer_wheel is None:
            run(
                sys.executable,
                HERE.parent / "uz_developer.py",
                "dataviewer",
                "wheel",
                "--out",
                directory,
                env={**os.environ, "UZ_CLI_RELEASE_VERSION": version},
            )
            (dataviewer_wheel,) = Path(directory).glob("*.whl")
        run(
            "uv",
            "pip",
            "install",
            "--python",
            python,
            "--reinstall",
            "--no-deps",
            cli_wheel,
            Path(dataviewer_wheel).resolve(),
        )
    run("uv", "pip", "check", "--python", python)
    # Import from outside the checkout to catch absent package data/imports.
    with tempfile.TemporaryDirectory(prefix="installed-viewer-") as directory:
        run(python, "-m", "ultrazohm_dataviewer", "--help", cwd=directory)
        run(python, "-m", "ultrazohm_cli", "--version", cwd=directory)


def ruff(*arguments, target="."):
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
        target,
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
            if sys.platform == "linux" and not os.environ.get("DISPLAY"):
                run("xvfb-run", "-a", python, HERE / "build/smoke_gui.py")
            else:
                run(python, HERE / "build/smoke_gui.py")


def generate(_args):
    """Regenerate client_methods.py from the command specifications."""
    with tempfile.TemporaryDirectory(prefix="uz-viewer-generate-") as directory:
        python = sync(Path(directory) / "environment")
        run(python, HERE / "tools" / "generate_client.py")
    ruff("format", target=HERE / "src" / "ultrazohm_dataviewer" / "client_methods.py")


def check(args):
    """Lint and tests (including generated-code freshness), as CI does."""
    lint(args)
    format_check(args)
    test(args)


def wheel(args):
    """Build the publishable viewer wheel from staged sources."""
    sys.path.insert(0, str(HERE / "tools"))
    from release_build import staged_project

    output = args.out.resolve() if args.out else HERE / "dist-wheels"
    if args.out is None:
        shutil.rmtree(output, ignore_errors=True)
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


def _wheel_arguments(parser, *, gui_smoke=False):
    parser.add_argument("--cli-wheel", type=Path, help="matching CLI wheel")
    parser.add_argument(
        "--dataviewer-wheel",
        type=Path,
        help="matching DataViewer wheel; otherwise build it",
    )
    if gui_smoke:
        parser.add_argument(
            "--gui-smoke",
            action="store_true",
            help="Also launch the installed GUI (requires a display)",
        )


LOCK = "dataviewer"
TASKS = {
    "format": Task(format_code, format_code.__doc__),
    "format-check": Task(format_check, format_check.__doc__),
    "lint": Task(lint, lint.__doc__),
    "generate": Task(generate, generate.__doc__),
    "test": Task(
        test, test.__doc__, lambda parser: _wheel_arguments(parser, gui_smoke=True)
    ),
    "check": Task(
        check,
        "Lint and run the full test suite in a temporary environment, as CI does. "
        "Without --cli-wheel, a debug CLI wheel is built from ../ultrazohm_cli so live "
        "tests use this checkout.",
        lambda parser: _wheel_arguments(parser, gui_smoke=True),
    ),
    # Private wheel outputs need no shared lock (bundle may invoke wheel).
    "wheel": Task(
        wheel,
        wheel.__doc__,
        lambda parser: parser.add_argument("--out", type=Path),
        locked=lambda args: args.out is None,
    ),
    "bundle": Task(
        bundle,
        "Build the PyInstaller desktop bundle in dist/ from a temporary environment. "
        "Without --cli-wheel, a release CLI wheel is built from ../ultrazohm_cli. "
        "Standalone bundles are Windows-only; Linux uses Python wheels.",
        _wheel_arguments,
        locked=lambda args: True,
    ),
    "bundle-smoke": Task(bundle_smoke, bundle_smoke.__doc__, locked=lambda args: True),
}
