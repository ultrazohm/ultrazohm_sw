"""Dispatch repository commands to the CLI or viewer's own tasks."""

import argparse
import json
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PROJECTS = {"cli": "ultrazohm_cli", "viewer": "ultrazohm_dataviewer"}


def selected_app():
    try:
        state = json.loads((ROOT / ".venv/.uz-setup.json").read_text())
        app = state.get("app") if isinstance(state, dict) else None
        return app if app in PROJECTS else "viewer"
    except (OSError, ValueError):
        return "viewer"


def main(argv=None):
    parser = argparse.ArgumentParser(prog=".\\uz.ps1" if os.name == "nt" else "./uz")
    commands = parser.add_subparsers(dest="command")
    for name in ("setup", "shell"):
        command = commands.add_parser(name)
        command.add_argument(
            "source", nargs="?", choices=("local", "stable", "prerelease")
        )
        command.add_argument("--app", choices=PROJECTS)
    for name in ("build", "check", "task"):
        command = commands.add_parser(name)
        command.add_argument("project", choices=PROJECTS)
        if name == "task":
            command.add_argument("task")
        command.add_argument("arguments", nargs=argparse.REMAINDER)
    args = parser.parse_args(argv)
    if args.command is None:
        parser.print_help()
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
