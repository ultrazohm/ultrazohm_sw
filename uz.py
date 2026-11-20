"""Dispatch repository commands to the CLI or viewer's own tasks."""

import argparse
import importlib
import json
import os
import shutil
import signal
import socket
import time
import subprocess
import sys
from pathlib import Path

from uz_environment import environment_lock

ROOT = Path(__file__).resolve().parent
PROJECTS = {"cli": "ultrazohm_cli", "viewer": "ultrazohm_dataviewer"}


def clear_venv():
    with environment_lock(ROOT):
        _clear_venv()


def _clear_venv():
    """Remove only this checkout's managed environment and setup selection."""
    venv = ROOT / ".venv"
    if venv.is_symlink():
        venv.unlink()
    elif venv.exists():
        shutil.rmtree(venv)
    else:
        print(f"No managed environment at {venv}.")
        return
    print(f"Removed {venv}; application/source selection cleared.")


def selected_app():
    try:
        state = json.loads((ROOT / ".venv/.uz-setup.json").read_text())
        app = state.get("app") if isinstance(state, dict) else None
        return app if app in PROJECTS else "viewer"
    except (OSError, ValueError):
        return "viewer"


def wait_for_viewer(child, python, timeout=30):
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        code = child.poll()
        if code is not None:
            raise RuntimeError(f"DataViewer exited during startup (exit code {code}).")
        try:
            result = subprocess.run(
                [
                    str(python),
                    "-c",
                    "from ultrazohm_dataviewer import Client; "
                    "Client(timeout=1).status()",
                ],
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                timeout=2,
            )
            if result.returncode == 0 and child.poll() is None:
                return
        except subprocess.TimeoutExpired:
            pass
        time.sleep(0.1)
    raise RuntimeError(
        f"DataViewer control API was not ready within {timeout} seconds."
    )


def stop_background(child):
    if child.poll() is not None:
        return
    if os.name == "nt":
        subprocess.run(["taskkill", "/PID", str(child.pid), "/T", "/F"], check=True)
    else:
        os.killpg(child.pid, signal.SIGTERM)
    child.wait(timeout=10)
    if os.name != "nt":
        # The supervisor may exit before a child that handles SIGTERM.
        try:
            os.killpg(child.pid, signal.SIGKILL)
        except ProcessLookupError:
            pass


def launch_app(args):
    project = "viewer" if args.command == "dataviewer" else "cli"
    setup = importlib.import_module(f"{PROJECTS[project]}.tools.setup_env")
    state = setup.saved_setup()
    # A viewer installation already contains the CLI. Validate it using its owner.
    if (
        project == "cli"
        and state.get("app") == "viewer"
        and state.get("source") == args.source
    ):
        setup = importlib.import_module("ultrazohm_dataviewer.tools.setup_env")
    source = None if state.get("source") == args.source else args.source
    try:
        setup.setup(source, reuse=True)
    except subprocess.CalledProcessError:
        if args.source == "stable":
            launcher = ".\\uz.ps1" if os.name == "nt" else "./uz"
            print(
                f"Stable setup failed. To explicitly allow prereleases, run: "
                f"{launcher} {args.command} --prerelease",
                file=sys.stderr,
            )
        raise
    marker = ROOT / ".venv/.uz-setup.json"
    expected = marker.read_bytes() if marker.exists() else None
    with environment_lock(ROOT, use=True):
        if expected is not None and marker.read_bytes() != expected:
            raise RuntimeError(
                "The environment changed during launch; retry the command."
            )
        executable = setup.executable(f"ultrazohm-{args.command}")
        if not getattr(args, "interactive", False):
            setup.run(executable, interactive=True)
            return
        endpoint = os.environ.get("UZ_DATAVIEWER_ENDPOINT", "127.0.0.1:19741")
        host, port = endpoint.rsplit(":", 1)
        with socket.socket() as listener:
            try:
                listener.bind((host, int(port)))
            except OSError as error:
                raise RuntimeError(
                    f"DataViewer endpoint {endpoint} is already in use."
                ) from error
        options = (
            {"creationflags": subprocess.CREATE_NEW_PROCESS_GROUP}
            if os.name == "nt"
            else {"start_new_session": True}
        )
        child = subprocess.Popen(
            [
                sys.executable,
                str(ROOT / "uz_environment.py"),
                str(ROOT),
                str(executable),
            ],
            stdin=subprocess.DEVNULL,
            **options,
        )
        try:
            wait_for_viewer(child, setup.executable("python"))
        except BaseException:
            stop_background(child)
            raise
        setup.run(
            setup.executable("python"),
            ROOT / PROJECTS[project] / "tools/env_shell.py",
            interactive=True,
        )


def main(argv=None):
    launcher = ".\\uz.ps1" if os.name == "nt" else "./uz"
    parser = argparse.ArgumentParser(
        prog=launcher,
        description="Set up, build and check the UltraZohm CLI and Data Viewer.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=f"""Getting started:
  {launcher} dataviewer               Start the stable DataViewer
  {launcher} dataviewer --interactive Start the viewer and open a command shell
  {launcher} cli                      Start the stable interactive CLI
  Both shortcuts accept --stable (default), --prerelease, or --local.

  {launcher} shell stable             Install the published viewer + CLI and open a shell
  {launcher} shell local              Build/install this checkout and open a shell
  {launcher} shell stable --app cli   Install only the published CLI and open a shell
  {launcher} shell                    Reuse the last application/source selection

Installation choices (setup and shell):
  stable       Published stable packages from PyPI (first-use default)
  prerelease   Allow prerelease packages from PyPI
  local        Build the CLI from this checkout; install the viewer in editable mode
  --app cli    CLI only
  --app viewer Viewer with its CLI dependency (first-use default)

  setup prepares the repository .venv without opening a shell.
  shell prepares it as needed and opens an activated shell; use exit to return.
  Changing the application or source recreates that managed environment.
  Inside the shell, run ultrazohm-cli --help or ultrazohm-dataviewer --help.

Reset the environment:
  {launcher} clear_venv               Remove .venv and forget the setup selection
  Exit the activated shell first. The next setup/shell command creates a new environment.

Development checks and formatting:
  {launcher} check cli                Python style, Rust fmt/Clippy, and CLI tests
  {launcher} check viewer             Python style and viewer tests
  {launcher} task cli lint            Check CLI Python lint rules
  {launcher} task viewer format       Apply viewer Python formatting
  {launcher} task cli format-check    Check CLI Python formatting without changes
  Replace cli/viewer to select the other project for Python style tasks.
  Rust formatting: run cargo fmt from ultrazohm_cli/.

Builds:
  {launcher} build cli                Build an optimized CLI wheel for this machine
  {launcher} task viewer wheel        Build a viewer Python wheel
  {launcher} build viewer             Build a standalone viewer bundle (Windows only)

More help:
  {launcher} setup --help             Installation options
  {launcher} task cli help            List CLI project tasks
  {launcher} task viewer help         List viewer project tasks
  {launcher} task cli wheel --help    Options for a specific task

Build/check/task commands run the selected project's tasks.py.
They do not require running setup first; build tools may still be required.""",
    )
    descriptions = {
        "setup": "prepare the selected application's environment",
        "shell": "prepare the environment and open an activated shell",
        "build": "build a CLI wheel or viewer desktop bundle",
        "check": "run the selected project's checks",
        "task": "run a project task, such as lint or format",
    }
    commands = parser.add_subparsers(dest="command")
    for name in ("dataviewer", "cli"):
        command = commands.add_parser(name, help=f"Prepare and start {name}")
        sources = command.add_mutually_exclusive_group()
        for source in ("stable", "prerelease", "local"):
            sources.add_argument(
                f"--{source}",
                dest="source",
                action="store_const",
                const=source,
                help=f"Use {source} packages"
                + (" (default)" if source == "stable" else ""),
            )
        command.set_defaults(source="stable")
        if name == "dataviewer":
            command.add_argument(
                "--interactive",
                action="store_true",
                help="Launch the viewer in the background and open an activated command shell",
            )
    commands.add_parser(
        "clear_venv",
        help="remove the repository .venv and forget the setup selection",
        description="Remove the repository .venv, including its saved application/source selection. "
        "Exit the activated shell first. No environment is recreated by this command.",
    )
    for name in ("setup", "shell"):
        command = commands.add_parser(
            name, help=descriptions[name], description=descriptions[name]
        )
        command.add_argument(
            "source",
            nargs="?",
            choices=("local", "stable", "prerelease"),
            help="installation source; defaults to the last selection, or stable on first use",
        )
        command.add_argument(
            "--app",
            choices=PROJECTS,
            help="CLI only, or viewer with CLI; defaults to the last selection, or viewer",
        )
    for name in ("build", "check", "task"):
        command = commands.add_parser(
            name, help=descriptions[name], description=descriptions[name]
        )
        command.add_argument("project", choices=PROJECTS, help="project to run")
        if name == "task":
            command.add_argument("task", help="project task; use help to list tasks")
        command.add_argument(
            "arguments",
            nargs=argparse.REMAINDER,
            help="arguments forwarded to the project task",
        )
    argv = list(sys.argv[1:] if argv is None else argv)
    if argv == ["help"]:
        argv = ["--help"]
    args = parser.parse_args(argv)
    if args.command is None:
        parser.print_help()
        return
    if args.command in ("dataviewer", "cli"):
        try:
            launch_app(args)
        except subprocess.CalledProcessError as error:
            raise SystemExit(error.returncode or 1) from None
        except RuntimeError as error:
            parser.exit(1, f"{error}\n")
        except KeyboardInterrupt:
            raise SystemExit(130) from None
        return
    if args.command == "clear_venv":
        try:
            clear_venv()
        except (OSError, RuntimeError) as error:
            parser.exit(1, f"Could not clear {ROOT / '.venv'}: {error}\n")
        return
    if args.command in ("setup", "shell"):
        project = args.app or selected_app()
        arguments = [args.command] + ([args.source] if args.source else [])
    else:
        project = args.project
        task = (
            args.task
            if args.command == "task"
            else (
                "check"
                if args.command == "check"
                else "wheel"
                if project == "cli"
                else "bundle"
            )
        )
        arguments = [task, *args.arguments]
    try:
        with subprocess.Popen(
            [sys.executable, str(ROOT / PROJECTS[project] / "tasks.py"), *arguments]
        ) as child:
            while True:
                try:
                    code = child.wait()
                    break
                except KeyboardInterrupt:
                    if arguments[0] != "shell":
                        raise
                    # The activated shell handles Ctrl-C; keep its launcher alive.
            if code:
                raise SystemExit(code)
    except KeyboardInterrupt:
        raise SystemExit(130) from None


if __name__ == "__main__":
    main()
