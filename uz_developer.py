"""Explicit local development setup, launches, and project tasks."""

import argparse
import json
import os
import shutil
import sys

import uz_developer_environment as environment
from uz_environment import environment_lock

ROOT = environment.ROOT
PROJECTS = {"cli": "ultrazohm_cli", "viewer": "ultrazohm_dataviewer"}


def main(argv=None):
    launcher = ".\\uz_developer.ps1" if os.name == "nt" else "./uz_developer"
    parser = argparse.ArgumentParser(
        prog=launcher,
        description="Build and run the local checkout's CLI and DataViewer. "
        "Application code comes from this checkout, not published PyPI releases; "
        "external dependencies and build tools may still be downloaded.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=f"""Command syntax:
  {launcher} setup
  {launcher} cli [-- APPLICATION_ARGS...]
  {launcher} dataviewer [-- APPLICATION_ARGS...]
  {launcher} shell
  {launcher} status
  {launcher} clear_venv
  {launcher} build {{cli|viewer}} [TASK_ARGS...]
  {launcher} check {{cli|viewer}} [TASK_ARGS...]
  {launcher} task {{cli|viewer}} TASK [TASK_ARGS...]

setup builds the local CLI wheel and installs the local DataViewer in editable
mode into .venv. Launches and shells use that prepared local installation and
never rebuild or reinstall. Run setup again after CLI or dependency changes;
restart the viewer after edits to its Python source.

Examples:
  {launcher} setup
  {launcher} dataviewer
  {launcher} cli -- --help
  {launcher} build cli --out /path/to/wheels
  {launcher} check viewer
  {launcher} task cli release-wheel
  {launcher} task viewer check --help

Use task cli help or task viewer help to list project tasks.
Inside the dev container, run installed application commands directly;
build/check/task remain available. Use ./uz for published application versions.""",
    )
    commands = parser.add_subparsers(dest="command", required=True)
    for name, help_text in (
        ("setup", "Build/install both local applications into .venv"),
        ("shell", "Open the existing development environment; never reinstall"),
        ("status", "Show development environment location and installed versions"),
        ("clear_venv", "Remove the development environment when unused"),
    ):
        commands.add_parser(name, help=help_text)
    for name in ("cli", "dataviewer"):
        command = commands.add_parser(name, help=f"Run local {name}; never reinstall")
        command.add_argument("arguments", nargs=argparse.REMAINDER)
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
    try:
        if args.command == "setup":
            environment.setup()
        elif args.command in ("cli", "dataviewer", "shell"):
            environment.guard_host_environment()
            with environment_lock(ROOT, use=True):
                environment.require_environment()
                if args.command == "shell":
                    environment.run(
                        environment.executable("python"), ROOT / "uz_shell.py"
                    )
                else:
                    arguments = args.arguments
                    if arguments[:1] == ["--"]:
                        arguments = arguments[1:]
                    environment.run(
                        environment.executable(f"ultrazohm-{args.command}"), *arguments
                    )
        elif args.command == "clear_venv":
            environment.guard_host_environment()
            with environment_lock(ROOT):
                venv = ROOT / ".venv"
                if venv.is_symlink():
                    venv.unlink()
                elif venv.exists():
                    shutil.rmtree(venv)
                print(f"Removed development environment: {venv}")
        elif args.command == "status":
            environment.guard_host_environment()
            try:
                with environment_lock(ROOT):
                    pass
                print("Usage: idle")
            except RuntimeError:
                print("Usage: in use by a managed application, shell, or setup")
            with environment_lock(ROOT, use=True):
                print(f"Development environment: {ROOT / '.venv'}")
                print(json.dumps(environment.saved_setup(), indent=2))
                try:
                    environment.require_environment()
                except RuntimeError as error:
                    print(error)
                else:
                    environment.run(
                        environment.executable("python"),
                        "-c",
                        "import sys,importlib.metadata as m; print('Python:', sys.executable); "
                        "print('CLI:', m.version('ultrazohm-cli')); "
                        "print('DataViewer:', m.version('ultrazohm-dataviewer'))",
                    )
        else:
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
            if task in ("setup", "shell"):
                parser.error(
                    f"Use uz_developer {task} instead of per-project environment tasks"
                )
            environment.run(
                sys.executable,
                ROOT / PROJECTS[args.project] / "tasks.py",
                task,
                *args.arguments,
            )
    except environment.subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1) from None
    except (OSError, RuntimeError) as error:
        parser.exit(1, f"{error}\n")
    except KeyboardInterrupt:
        raise SystemExit(130) from None


if __name__ == "__main__":
    main()
