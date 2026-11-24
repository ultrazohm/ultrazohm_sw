"""Build, install and validate checkout applications using the CI tasks."""

import argparse
import os
import subprocess
import sys
from pathlib import Path

from uz import run
from uz_build import build_lock, single_wheel
from uz_venv import build_development, development_shell

ROOT = Path(__file__).resolve().parent
PROJECTS = {"cli": "ultrazohm_cli", "dataviewer": "ultrazohm_dataviewer"}


def task(project, name, *arguments):
    run([sys.executable, ROOT / PROJECTS[project] / "tasks.py", name, *arguments])


def candidates():
    return [
        "--cli-wheel",
        single_wheel(ROOT / "ultrazohm_cli/target/wheels-release"),
        "--dataviewer-wheel",
        single_wheel(ROOT / "ultrazohm_dataviewer/dist-wheels", "ultrazohm_dataviewer"),
    ]


def main(argv=None):
    launcher = ".\\uz_developer.ps1" if os.name == "nt" else "./uz_developer"
    parser = argparse.ArgumentParser(
        prog=launcher,
        description="Build checkout wheels and update the persistent development environment.",
        epilog="Use shell (or ./uz venv dev) after building. Published tools use ./uz cli/dataviewer.",
    )
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser(
        "shell", help="Activate the existing development environment without rebuilding"
    )
    for name in ("build", "check", "task"):
        command = commands.add_parser(name)
        command.add_argument(
            "project",
            choices=list(PROJECTS)
            + ([] if name == "task" else ["linux_wheels", "windows_bundle"]),
        )
        if name == "task":
            command.add_argument("task")
        command.add_argument("arguments", nargs=argparse.REMAINDER)
    argv = list(sys.argv[1:] if argv is None else argv)
    if argv == ["help"]:
        argv = ["--help"]
    args = parser.parse_args(argv or ["--help"])
    try:
        if args.command == "shell":
            development_shell(ROOT, run)
        elif args.command == "task":
            task(args.project, args.task, *args.arguments)
        elif args.command == "build":
            if args.arguments:
                parser.error(
                    "Build updates the development environment; use task for low-level artifact options"
                )
            if args.project == "linux_wheels" and sys.platform != "linux":
                parser.error("linux_wheels must be built on Linux")
            if args.project == "windows_bundle" and os.name != "nt":
                parser.error("windows_bundle must be built on Windows")
            # Both apps have an exact version relationship. Refresh the pair even
            # when one application is named; Cargo reuses unchanged compilation.
            with build_lock(ROOT, "development"):
                build_development(ROOT, run)
                if args.project == "windows_bundle":
                    task("cli", "standalone")
                    task("dataviewer", "bundle", *candidates())
        elif args.project in PROJECTS:
            task(args.project, "check", *args.arguments)
        elif args.project == "linux_wheels":
            if sys.platform != "linux":
                parser.error("linux_wheels checks require Linux")
            with build_lock(ROOT, "development"):
                wheels = candidates()
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
                parser.error("windows_bundle checks require Windows")
            task("cli", "release-check", "--standalone")
            task("dataviewer", "bundle-smoke", *args.arguments)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1) from None
    except (OSError, RuntimeError) as error:
        parser.exit(1, f"{error}\n")
    except KeyboardInterrupt:
        raise SystemExit(130) from None


if __name__ == "__main__":
    main()
