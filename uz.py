"""Dispatch repository commands to the CLI or viewer's own tasks."""

import argparse
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PROJECTS = {"cli": "ultrazohm_cli", "viewer": "ultrazohm_dataviewer"}


def clear_venv():
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


def main(argv=None):
    launcher = ".\\uz.ps1" if os.name == "nt" else "./uz"
    parser = argparse.ArgumentParser(
        prog=launcher,
        description="Set up, build and check the UltraZohm CLI and Data Viewer.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=f"""Getting started:
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
    if args.command == "clear_venv":
        try:
            clear_venv()
        except OSError as error:
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
