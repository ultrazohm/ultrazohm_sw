"""Start, build and test uz_dataviewer, identical on Linux, Windows and in CI.

Standard library only; needs uv. Run from anywhere, for example with
`uv run uz_dataviewer/tasks.py TASK` (start.sh/start.ps1 install uv first and run
`start`; on Linux, `make -C uz_dataviewer TASK` is a shortcut):

    start [--dev-cli] [VIEWER_ARGS...]   open the viewer from uz_dataviewer/.venv (locked
                                         dependencies, including the published CLI)
    shell [--dev-cli]                    terminal with uz_dataviewer/.venv activated
    lint                                 ruff
    test [--cli-wheel PATH]              pytest with a matching CLI wheel
    check [--cli-wheel PATH]             lint and test
    bundle [--cli-wheel PATH]            PyInstaller desktop bundle in dist/
    bundle-smoke                         start the bundle and its live workers headless

--dev-cli builds ../uz_cli and installs it over the locked CLI for that start
(Rust needed); the next ordinary start restores the locked version. Without
--cli-wheel, test and bundle build a wheel from ../uz_cli (debug for tests,
release for bundles). A bundle is portable only when built on an old glibc (CI
uses Ubuntu 22.04). Environments: .venv for start/shell, .venv-ci for tests,
.venv-build for bundles. Viewer options after the task name pass through, e.g.
`start --backend pyarrow log.csv`; use `start -- --help` for the viewer's help.
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
    """Run ruff over sources, tests and build scripts."""
    python = sync(HERE / ".venv-ci")
    run(python, "-m", "ruff", "check", "src", "tests", "build", "examples", "tasks.py")


def test(args):
    """Run pytest with a CLI wheel matching this checkout."""
    python = sync(HERE / ".venv-ci")
    wheel = args.cli_wheel
    if wheel is None:
        cli_tasks("debug-wheel")
        wheel = built_wheel(CLI / "target" / "wheels-debug")
    install_cli(python, Path(wheel).resolve())
    run(python, "-m", "pytest", "-q")


def check(args):
    """Lint and test, as CI does."""
    lint(args)
    test(args)


def bundle(args):
    """Build the PyInstaller desktop bundle in dist/."""
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
    """Start the bundle and its live workers headless."""
    python = python_in(HERE / ".venv-build")
    executable = HERE / "dist" / "uz_dataviewer" / ("uz_dataviewer.exe" if WINDOWS else "uz_dataviewer")
    run(python, Path("build") / "smoke_binary.py", executable)
    run(python, Path("build") / "smoke_live.py", executable)


def _viewer_environment(dev_cli):
    """Sync uz_dataviewer/.venv (keeping a development CLI) and return its scripts directory."""
    common = ["--project", str(HERE), "--python", PYTHON, "--no-build-package", "imgui-bundle"]
    subprocess.run(["uv", "sync", *common, "--inexact"], check=True)
    scripts = HERE / ".venv" / ("Scripts" if WINDOWS else "bin")
    if dev_cli:
        # Install this checkout's CLI over the locked one for this start only.
        wheels = CLI / "target" / "wheels-dev"
        shutil.rmtree(wheels, ignore_errors=True)
        cli_tasks("wheel", "--out", wheels)
        install_cli(scripts / ("python.exe" if WINDOWS else "python"), built_wheel(wheels))
    return scripts


def start(args):
    # Keep the caller's working directory: relative recording paths stay valid.
    viewer = ["--live-repo", str(HERE.parent), *args.viewer]
    if not args.dev_cli:
        common = ["--project", str(HERE), "--python", PYTHON, "--no-build-package", "imgui-bundle"]
        raise SystemExit(subprocess.call(["uv", "run", *common, "uz-dataviewer", *viewer]))
    scripts = _viewer_environment(True)
    executable = scripts / ("uz-dataviewer.exe" if WINDOWS else "uz-dataviewer")
    raise SystemExit(subprocess.call([str(executable), *viewer]))


def shell(args):
    scripts = _viewer_environment(args.dev_cli)
    python = scripts / ("python.exe" if WINDOWS else "python")
    raise SystemExit(subprocess.call([str(python), "-m", "uz_dataviewer.env_shell"]))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    tasks = parser.add_subparsers(dest="task", required=True)
    started = tasks.add_parser("start", help="Open the viewer (the default of start.sh/start.ps1).")
    started.add_argument("--dev-cli", action="store_true", help="build and use this checkout's CLI")
    started.add_argument("viewer", nargs="*", help="arguments for the viewer, including its options")
    started.set_defaults(function=start)
    shelled = tasks.add_parser("shell", help="Open a terminal with the viewer environment activated.")
    shelled.add_argument("--dev-cli", action="store_true", help="build and use this checkout's CLI")
    shelled.set_defaults(function=shell)
    for name, function, wheel in (("lint", lint, False), ("test", test, True), ("check", check, True),
                                  ("bundle", bundle, True), ("bundle-smoke", bundle_smoke, False)):
        task = tasks.add_parser(name, help=(function.__doc__ or name).splitlines()[0])
        if wheel:
            task.add_argument("--cli-wheel", type=Path, help="matching CLI wheel (default: build one from ../uz_cli)")
        task.set_defaults(function=function)
    argv = list(sys.argv[1:] if argv is None else argv)
    if argv[:1] == ["start"] and not set(argv[1:2]) & {"-h", "--help"}:
        # Everything after "start" (and an optional leading --dev-cli) belongs to
        # the viewer, including its own options; "--" passes viewer --help.
        dev_cli = argv[1:2] == ["--dev-cli"]
        viewer = argv[2 if dev_cli else 1:]
        args = argparse.Namespace(function=start, dev_cli=dev_cli, viewer=viewer[1:] if viewer[:1] == ["--"] else viewer)
    else:
        args = parser.parse_args(argv)
    try:
        args.function(args)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1)


if __name__ == "__main__":
    main()
