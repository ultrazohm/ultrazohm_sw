"""Local build and test task dispatcher."""

import argparse
import os
import subprocess
import sys

from pathlib import Path

from uz import run

ROOT = Path(__file__).resolve().parent
PROJECTS = {"cli": "ultrazohm_cli", "viewer": "ultrazohm_dataviewer"}


def main(argv=None):
    launcher = ".\\uz_developer.ps1" if os.name == "nt" else "./uz_developer"
    parser = argparse.ArgumentParser(
        prog=launcher,
        description="Build and test local checkout code. External dependencies and build tools may be downloaded.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=f"""Command syntax:
  {launcher} build {{cli|viewer}} [TASK_ARGS...]
  {launcher} check {{cli|viewer}} [TASK_ARGS...]
  {launcher} task {{cli|viewer}} TASK [TASK_ARGS...]

Examples:
  {launcher} build cli --out /path/to/wheels
  {launcher} check viewer
  {launcher} task cli release-wheel
  {launcher} task viewer check --help

Build/test Python environments are temporary and isolated per run. Download and
compilation caches are reused; shared artifact outputs are protected by locks.
Use task cli help or task viewer help to list project tasks.
For a local development shell, use ./uz venv dev (also inside the dev container).
Use ./uz cli or ./uz dataviewer to run published applications.""",
    )
    commands = parser.add_subparsers(dest="command", required=True)
    for name in ("build", "check", "task"):
        descriptions = {
            "build": "Build a local CLI wheel or Windows DataViewer bundle",
            "check": "Run the selected local project's checks and tests",
            "task": "Run a specific local project task; use TASK --help for options",
        }
        command = commands.add_parser(
            name, help=descriptions[name], description=descriptions[name]
        )
        command.add_argument("project", choices=PROJECTS)
        if name == "task":
            command.add_argument("task")
        command.add_argument(
            "arguments",
            nargs=argparse.REMAINDER,
            help="Arguments forwarded to the project task",
        )
    argv = list(sys.argv[1:] if argv is None else argv)
    if argv == ["help"]:
        argv = ["--help"]
    args = parser.parse_args(argv or ["--help"])
    task = (
        args.task
        if args.command == "task"
        else (
            "check"
            if args.command == "check"
            else "wheel"
            if args.project == "cli"
            else "bundle"
        )
    )
    try:
        run(
            [
                sys.executable,
                ROOT / PROJECTS[args.project] / "tasks.py",
                task,
                *args.arguments,
            ]
        )
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1) from None
    except (OSError, RuntimeError) as error:
        parser.exit(1, f"{error}\n")
    except KeyboardInterrupt:
        raise SystemExit(130) from None


if __name__ == "__main__":
    main()
