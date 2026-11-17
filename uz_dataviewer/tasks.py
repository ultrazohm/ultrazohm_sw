"""Build and test tasks for uz_dataviewer, identical on Linux, Windows and in CI.

Standard library only. Run from anywhere:

    python uz_dataviewer/tasks.py lint
    python uz_dataviewer/tasks.py test [--cli-wheel PATH]     pytest with a matching CLI wheel
    python uz_dataviewer/tasks.py check [--cli-wheel PATH]    lint and test
    python uz_dataviewer/tasks.py bundle [--cli-wheel PATH]   PyInstaller desktop bundle in dist/
    python uz_dataviewer/tasks.py bundle-smoke                start the bundle and its live workers

Without --cli-wheel, a wheel is built from ../uz_cli (debug for tests, release
for bundles). The bundle is portable only when built on an old glibc (CI uses
Ubuntu 22.04). Environments: .venv-ci for tests, .venv-build for bundles; .venv
belongs to the launchers.
"""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys

HERE = Path(__file__).resolve().parent
CLI = HERE.parent / "uz_cli"
WINDOWS = os.name == "nt"
# The repository's single Python pin. uv reads .python-version only inside the
# project directory, so pass it explicitly.
PYTHON = (HERE.parent / ".python-version").read_text(encoding="utf-8").strip()
SYNC = ["uv", "sync", "--locked", "--extra", "dev", "--python", PYTHON, "--no-build-package", "imgui-bundle"]


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
        raise SystemExit(f"Expected exactly one wheel in {directory}, found {len(wheels)}")
    return wheels[0]


def install_cli(python, wheel):
    # uv sync removes packages outside the lockfile, so install after syncing.
    run("uv", "pip", "install", "--quiet", "--python", python, "--no-deps", "--reinstall", wheel)


def lint(_args):
    python = sync(HERE / ".venv-ci")
    run(python, "-m", "ruff", "check", "src", "tests", "build", "examples", "launch.py", "tasks.py")


def test(args):
    python = sync(HERE / ".venv-ci")
    wheel = args.cli_wheel
    if wheel is None:
        cli_tasks("debug-wheel")
        wheel = built_wheel(CLI / "target" / "wheels-debug")
    install_cli(python, Path(wheel).resolve())
    run(python, "-m", "pytest", "-q")


def check(args):
    lint(args)
    test(args)


def bundle(args):
    wheel = args.cli_wheel
    if wheel is None:
        cli_tasks("release-wheel")
        wheel = built_wheel(CLI / "target" / "wheels-release")
    python = sync(HERE / ".venv-build")
    install_cli(python, Path(wheel).resolve())
    shutil.rmtree(HERE / "build" / "native", ignore_errors=True)
    shutil.rmtree(HERE / "dist", ignore_errors=True)
    run(python, "-m", "PyInstaller", "--noconfirm", "--clean", "--distpath", "dist",
        "--workpath", Path("build") / "native", Path("build") / "uz_dataviewer.spec")
    print(f"Built: {HERE / 'dist' / 'uz_dataviewer'}", flush=True)


def bundle_smoke(_args):
    python = python_in(HERE / ".venv-build")
    executable = HERE / "dist" / "uz_dataviewer" / ("uz_dataviewer.exe" if WINDOWS else "uz_dataviewer")
    run(python, Path("build") / "smoke_binary.py", executable)
    run(python, Path("build") / "smoke_live.py", executable)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    tasks = parser.add_subparsers(dest="task", required=True)
    for name, function, wheel in (("lint", lint, False), ("test", test, True), ("check", check, True),
                                  ("bundle", bundle, True), ("bundle-smoke", bundle_smoke, False)):
        task = tasks.add_parser(name)
        if wheel:
            task.add_argument("--cli-wheel", type=Path, help="matching CLI wheel (default: build one from ../uz_cli)")
        task.set_defaults(function=function)
    args = parser.parse_args()
    try:
        args.function(args)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1)


if __name__ == "__main__":
    main()
