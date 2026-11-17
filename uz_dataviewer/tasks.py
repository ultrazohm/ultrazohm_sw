"""Start, build and test uz_dataviewer; the same tasks on Linux, Windows and in CI.

Standard library only; needs uv. `python uz_dataviewer/tasks.py` (or `make` in
this directory) lists the tasks; `TASK --help` explains one.
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
    """Open the viewer from uz_dataviewer/.venv, keeping the caller's working directory."""
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


def _invocation():
    """How this script was called, so help shows commands that can be copied."""
    if os.environ.get("UZ_TASKS_VIA_MAKE"):
        return lambda task, args="": f'make {task}' + (f' ARGS="{args}"' if args else "")
    return lambda task, args="": f"uv run uz_dataviewer/tasks.py {task}" + (f" {args}" if args else "")


def overview():
    call = _invocation()
    usage = 'make TASK [ARGS="..."]' if os.environ.get("UZ_TASKS_VIA_MAKE") else "uv run uz_dataviewer/tasks.py TASK [...]"
    print(f"""uz_dataviewer tasks                       {usage}

Use
  start          Open the viewer with the published CLI; arguments go to the viewer
  shell          Terminal with the viewer environment activated

Develop
  develop        Open the viewer with this checkout's CLI (builds it; needs Rust)
  check          Lint and full test suite, as CI
  bundle         Build the desktop bundle in dist/ (bundle-smoke tests it)

CI only: lint, test, bundle-smoke

Examples
  {call("start", "log.parquet")}
  {call("develop")}
  {call("check")}

Details: {call("TASK", "--help")}""")


DESCRIPTIONS = {
    "start": "Open the viewer from uz_dataviewer/.venv with the locked dependencies, including the "
             "published CLI (ultrazohm_cli). Arguments after the task go to the viewer, including its "
             "options; '--' before --help shows the viewer's own help. Relative file paths are "
             "resolved from your current directory.",
    "develop": "Like start, but first build ../uz_cli and install it over the locked CLI (needs Rust "
               "and a C/C++ toolchain). The next ordinary start returns to the locked version.",
    "shell": "Open a terminal with uz_dataviewer/.venv activated: python, uz-dataviewer and "
             "ultrazohm_cli at the viewer's versions. --dev-cli uses this checkout's CLI.",
    "check": "Lint and run the full test suite in .venv-ci, as CI does. Without --cli-wheel, a debug "
             "CLI wheel is built from ../uz_cli so live tests use this checkout.",
    "bundle": "Build the PyInstaller desktop bundle in dist/ from .venv-build. Without --cli-wheel, a "
              "release CLI wheel is built from ../uz_cli. A bundle runs on systems with at least the "
              "build system's glibc; CI builds the published one on Ubuntu 22.04.",
}


def main(argv=None):
    call = _invocation()
    parser = argparse.ArgumentParser(prog=call("").strip(), add_help=False)
    tasks = parser.add_subparsers(dest="task")

    def add(name, function, *, dev_cli=False, wheel=False, viewer=False):
        task = tasks.add_parser(name, prog=call(name), description=DESCRIPTIONS.get(name, function.__doc__))
        if dev_cli:
            task.add_argument("--dev-cli", action="store_true", help="build and use this checkout's CLI")
        if wheel:
            task.add_argument("--cli-wheel", type=Path, help="matching CLI wheel (default: build one from ../uz_cli)")
        if viewer:
            task.add_argument("viewer", nargs="*", help="arguments for the viewer, including its options")
        task.set_defaults(function=function)
    add("start", start, viewer=True)
    add("develop", start, viewer=True)
    add("shell", shell, dev_cli=True)
    for name, function, wheel in (("lint", lint, False), ("test", test, True), ("check", check, True),
                                  ("bundle", bundle, True), ("bundle-smoke", bundle_smoke, False)):
        add(name, function, wheel=wheel)
    argv = list(sys.argv[1:] if argv is None else argv)
    if not argv or argv[0] in ("-h", "--help", "help"):
        overview()
        return
    if argv[0] in ("start", "develop") and not set(argv[1:2]) & {"-h", "--help"}:
        # Everything after the task belongs to the viewer, including its own
        # options; "--" passes the viewer's --help.
        viewer = argv[1:]
        dev_cli = argv[0] == "develop" or viewer[:1] == ["--dev-cli"]  # start --dev-cli == develop
        if viewer[:1] == ["--dev-cli"]:
            viewer = viewer[1:]
        args = argparse.Namespace(function=start, dev_cli=dev_cli,
                                  viewer=viewer[1:] if viewer[:1] == ["--"] else viewer)
    else:
        args = parser.parse_args(argv)
    try:
        args.function(args)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1)


if __name__ == "__main__":
    main()
