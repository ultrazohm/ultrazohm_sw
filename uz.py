"""UltraZohm applications and isolated published/local-source shells.

The uz / uz.ps1 launchers bootstrap uv and Python before calling this module.
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PACKAGES = {"cli": "ultrazohm-cli", "dataviewer": "ultrazohm-dataviewer"}


def run(command):
    print("+", " ".join(map(str, command)), file=sys.stderr, flush=True)
    with subprocess.Popen([str(part) for part in command]) as child:
        while True:
            try:
                code = child.wait()
                break
            except KeyboardInterrupt:
                continue
    if code:
        raise subprocess.CalledProcessError(code, command)


def main(argv=None):
    launcher = ".\\uz.ps1" if os.name == "nt" else "./uz"
    parser = argparse.ArgumentParser(
        prog=launcher,
        description="Run UltraZohm tools and open isolated Python shells; never modify a repository .venv.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=f"""Command syntax:
  {launcher} cli [stable|prerelease] [-- APPLICATION_ARGS...]
  {launcher} dataviewer [stable|prerelease] [-- APPLICATION_ARGS...]
  {launcher} venv [stable|prerelease|dev]
  {launcher} install {{dataviewer|cli}} [stable|prerelease]

The channel defaults to stable. prerelease also allows development releases.
Application arguments use the stable channel unless a channel is specified.
venv stable/prerelease reuses a uv-managed cached environment.
venv dev activates the persistent checkout environment; build it first using
uz_developer build linux_wheels. All shells include requirements.txt.
Exit closes the shell. No repository .venv is used.

Examples:
  {launcher} dataviewer prerelease
  {launcher} cli stable -- --help
  {launcher} venv prerelease
  {launcher} venv dev
  {launcher} install cli prerelease

Use COMMAND --help for command details. For local source builds, use uz_developer.""",
    )
    commands = parser.add_subparsers(dest="command", required=True)
    descriptions = {
        "cli": "Run the published CLI",
        "dataviewer": "Run the published DataViewer",
        "venv": "Open a shell with published libraries or the existing development environment (dev)",
        "install": "Install a published application command for your user account",
    }
    for name in (*PACKAGES, "venv", "install"):
        command = commands.add_parser(
            name, help=descriptions[name], description=descriptions[name]
        )
        if name == "install":
            command.add_argument("application", choices=PACKAGES)
        command.add_argument(
            "channel",
            nargs="?",
            choices=("stable", "prerelease", "dev")
            if name == "venv"
            else ("stable", "prerelease"),
            default="stable",
            help="Release channel (default: stable); prerelease allows development releases",
        )
        if name in PACKAGES:
            command.add_argument(
                "arguments",
                nargs=argparse.REMAINDER,
                help="Application arguments (after the channel)",
            )
    argv = list(sys.argv[1:] if argv is None else argv)
    if argv == ["help"]:
        argv = ["--help"]
    if (
        len(argv) > 1
        and argv[0] in PACKAGES
        and argv[1] not in {"stable", "prerelease", "--help", "-h", "local"}
    ):
        argv[1:1] = ["stable"] if argv[1] == "--" else ["stable", "--"]
    args = parser.parse_args(argv or ["--help"])
    if args.command == "venv" and args.channel == "dev":
        from uz_venv import development_shell

        try:
            development_shell(ROOT, run)
        except subprocess.CalledProcessError as error:
            raise SystemExit(error.returncode or 1) from None
        except (OSError, RuntimeError) as error:
            parser.exit(1, f"{error}\n")
        except KeyboardInterrupt:
            raise SystemExit(130) from None
        return
    selection = [
        "--python",
        (ROOT / ".python-version").read_text().strip(),
        "--prerelease",
        "allow" if args.channel == "prerelease" else "disallow",
    ]
    if args.command == "install":
        command = [
            "uv",
            "tool",
            "install",
            "--force",
            *selection,
            PACKAGES[args.application],
        ]
    elif args.command == "venv":
        # uv owns this cached environment. It includes the viewer's CLI dependency,
        # never the checkout's .venv. Opening a second shell just reuses it.
        command = [
            "uv",
            "tool",
            "run",
            "--isolated",
            *selection,
            "--with-requirements",
            ROOT / "requirements.txt",
            "--from",
            PACKAGES["dataviewer"],
            "python",
            ROOT / "uz_shell.py",
        ]
    else:
        arguments = args.arguments
        if arguments[:1] == ["--"]:
            arguments = arguments[1:]
        command = [
            "uv",
            "tool",
            "run",
            "--isolated",
            *selection,
            PACKAGES[args.command],
            *arguments,
        ]
    try:
        run(command)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1) from None
    except OSError as error:
        parser.exit(1, f"{error}\n")
    except KeyboardInterrupt:
        raise SystemExit(130) from None


if __name__ == "__main__":
    main()
