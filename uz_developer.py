"""Build, check and release the checkout applications with the CI tasks.

Commands:
  shell                         activate the persistent development environment
  build [--bundle]              build the wheel pair and update that environment
  cli TASK [ARGS]               ultrazohm-cli tasks (ultrazohm_cli/tasks.py)
  dataviewer TASK [ARGS]        DataViewer tasks (ultrazohm_dataviewer/tasks.py)
  verify {linux,windows} [ARGS] release checks of the built pair
"""

import argparse
import os
import subprocess
import sys
from contextlib import nullcontext
from importlib.util import module_from_spec, spec_from_file_location
from pathlib import Path

from uz import run
from uz_build import build_lock, single_wheel
from uz_venv import build_development, development_shell

ROOT = Path(__file__).resolve().parent
PROJECTS = {"cli": "ultrazohm_cli", "dataviewer": "ultrazohm_dataviewer"}


def project_tasks(project):
    """Import a project's task registry (``TASKS`` and ``LOCK``)."""
    path = Path(__file__).resolve().parent / PROJECTS[project] / "tasks.py"
    spec = spec_from_file_location(f"{project}_tasks", path)
    module = module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def task(project, name, *arguments):
    """Run a project task in a child process (its own lock and environment)."""
    run([sys.executable, ROOT / "uz_developer.py", project, name, *arguments])


def candidates():
    return [
        "--cli-wheel",
        single_wheel(ROOT / "ultrazohm_cli/target/wheels-release"),
        "--dataviewer-wheel",
        single_wheel(ROOT / "ultrazohm_dataviewer/dist-wheels", "ultrazohm_dataviewer"),
    ]


def parser(launcher):
    root = argparse.ArgumentParser(
        prog=launcher,
        description=__doc__.split("\n\n")[0],
        epilog="Use shell (or ./uz venv dev) after building. Published tools use ./uz cli/dataviewer.",
    )
    commands = root.add_subparsers(dest="command", required=True)
    commands.add_parser(
        "shell", help="Activate the existing development environment without rebuilding"
    )
    build = commands.add_parser(
        "build",
        help="Build the matching wheel pair and update the development environment",
    )
    build.add_argument(
        "--bundle",
        action="store_true",
        help="also build the standalone CLI and the desktop bundle (Windows)",
    )
    for project in PROJECTS:
        module = project_tasks(project)
        command = commands.add_parser(project, help=f"{project} tasks")
        names = command.add_subparsers(dest="task", required=True, metavar="TASK")
        for name, definition in module.TASKS.items():
            child = names.add_parser(
                name, help=definition.help, description=definition.help
            )
            definition.arguments(child)
            child.set_defaults(definition=definition, lock=module.LOCK)
    verify = commands.add_parser(
        "verify", help="Release checks of the built wheel pair or Windows bundle"
    )
    verify.add_argument("target", choices=("linux", "windows"))
    verify.add_argument("arguments", nargs=argparse.REMAINDER)
    return root


def main(argv=None):
    launcher = ".\\uz_developer.ps1" if os.name == "nt" else "./uz_developer"
    argv = list(sys.argv[1:] if argv is None else argv)
    if argv == ["help"]:
        argv = ["--help"]
    commands = parser(launcher)
    args = commands.parse_args(argv or ["--help"])
    try:
        if args.command == "shell":
            development_shell(ROOT, run)
        elif args.command == "build":
            if args.bundle and os.name != "nt":
                commands.error("--bundle must be built on Windows")
            # Both apps have an exact version relationship. Refresh the pair;
            # Cargo reuses unchanged compilation.
            with build_lock(ROOT, "development"):
                build_development(ROOT, run)
                if args.bundle:
                    task("cli", "standalone")
                    task("dataviewer", "bundle", *map(str, candidates()))
        elif args.command in PROJECTS:
            lock = args.definition.locked(args)
            with build_lock(ROOT, args.lock) if lock else nullcontext():
                args.definition.function(args)
        elif args.target == "linux":
            if sys.platform != "linux":
                commands.error("linux verification requires Linux")
            with build_lock(ROOT, "development"):
                wheels = [str(item) for item in candidates()]
                task("cli", "check")
                task("cli", "release-check")
                task("dataviewer", "check", "--gui-smoke", *wheels, *args.arguments)
                run(
                    [
                        sys.executable,
                        "-m",
                        "unittest",
                        "test_uz",
                        "test_uz_developer",
                        "-v",
                    ]
                )
        else:
            if os.name != "nt":
                commands.error("windows verification requires Windows")
            task("cli", "release-check", "--standalone")
            task("dataviewer", "bundle-smoke", *args.arguments)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1) from None
    except (OSError, RuntimeError) as error:
        commands.exit(1, f"{error}\n")
    except KeyboardInterrupt:
        raise SystemExit(130) from None


if __name__ == "__main__":
    main()
