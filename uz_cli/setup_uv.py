"""Create a uv environment from a local or GitHub release wheel; never build Rust.

From the repository root (uv must already be installed):
    uv run --no-project --python 3.12 uz_cli/setup_uv.py
    uv run --no-project --python 3.12 uz_cli/setup_uv.py --examples

Use the newest compatible local wheel or download the newest CLI release.
With no compatible local wheels, download automatically.
"""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys
import shlex
import tempfile
from wheel_releases import compatible_wheels, choose_local, detect_channel, download_latest, local_cli_wheels, validate_cli_wheel


def main():
    root = Path(__file__).resolve().parent
    parser = argparse.ArgumentParser(description=__doc__)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument("--wheel", type=Path, help="Use this exact local wheel")
    selection.add_argument("--latest", action="store_true", help="Download newest CLI release, even with local wheels")
    selection.add_argument("--local-newest", action="store_true", help="Use the most recently modified compatible local CLI wheel without prompting")
    parser.add_argument("--channel", choices=["stable", "testing"],
                        help="Release channel (default: testing on feature/uz_cli26, stable otherwise)")
    in_container = Path("/.dockerenv").exists() or Path("/run/.containerenv").exists()
    default_venv = root / (".venv-container" if in_container else ".venv-host")
    parser.add_argument("--venv", type=Path, default=default_venv,
                        help="Environment path (default: .venv-host, or .venv-container inside Docker)")
    parser.add_argument("--python", default="3.12", help="Python version or interpreter for a new environment")
    parser.add_argument("--examples", action="store_true", help="Also install Python Polars and Matplotlib")
    parser.add_argument("--launch", choices=["shell", "cli", "example"], help="Open an activated shell, CLI or Python example after installation")
    parser.add_argument("command", nargs=argparse.REMAINDER, help="CLI arguments after -- (default: ultrazohm's interactive session)")
    args = parser.parse_args()
    extra = args.command[1:] if args.command[:1] == ["--"] else args.command
    if extra and args.launch != "cli":
        parser.error("CLI arguments require --launch cli")
    uv = shutil.which("uv")
    if uv is None:
        parser.error("uv must be installed and available on PATH")

    wheel = args.wheel
    wheels = list((root / "target" / "wheels").glob("ultrazohm-*.whl")) if wheel is None else []
    if wheel is not None:
        wheel = wheel.resolve()
        if not wheel.is_file() or not wheel.name.startswith("ultrazohm-") or wheel.suffix != ".whl":
            parser.error("--wheel must name an existing ultrazohm wheel (source installs are not supported)")

    # Ignore an activated environment from another machine/container.
    install_env = os.environ.copy()
    install_env.pop("VIRTUAL_ENV", None)
    venv = args.venv.resolve()
    if venv.exists() and not (venv / "pyvenv.cfg").is_file():
        parser.error(f"Refusing to overwrite a non-virtual-environment directory: {venv}")
    if not venv.exists():
        subprocess.run([uv, "venv", "--python", args.python, str(venv)], check=True, env=install_env)
    scripts = venv / ("Scripts" if sys.platform == "win32" else "bin")
    python = scripts / ("python.exe" if sys.platform == "win32" else "python")
    command = scripts / ("ultrazohm.exe" if sys.platform == "win32" else "ultrazohm")
    if not python.is_file():
        parser.error("The existing environment's Python is missing. Virtual environments are not "
                     "portable between host/container; use --venv with a new path.")
    expected_python = subprocess.check_output(
        [uv, "python", "find", args.python], env=install_env, text=True
    ).strip()
    version_code = "import sys; print('.'.join(map(str, sys.version_info[:2])))"
    expected_version = subprocess.check_output([expected_python, "-c", version_code], text=True).strip()
    actual_version = subprocess.check_output([str(python), "-c", version_code], text=True).strip()
    if actual_version != expected_version:
        parser.error(f"Existing environment uses Python {actual_version}, expected {expected_version}; "
                     "use --venv with a new path to preserve the existing environment.")
    # Compatibility must be checked against the destination Python, including
    # for explicitly selected wheels and remote release assets.
    subprocess.run([uv, "pip", "install", "--python", str(python),
                    "--only-binary", ":all:", "packaging"], check=True, env=install_env)
    channel = args.channel or detect_channel(root.parent)
    print(f"CLI release channel: {channel}", flush=True)
    if wheel is not None:
        if not compatible_wheels([wheel], python, install_env):
            parser.error(f"Wheel is incompatible with this environment: {wheel.name}")
    else:
        local = local_cli_wheels([p.resolve() for p in wheels], python, install_env)
        if args.local_newest:
            if not local:
                parser.error("No compatible local wheel exists; use --latest to download one")
            wheel = Path(local[0])
        elif not args.latest:
            wheel = choose_local(local, channel, sys.stdin.isatty())
        if wheel is None:
            wheel = download_latest(channel, root / "target" / "wheels", python, install_env)
    validate_cli_wheel(wheel)
    print(f"Using wheel: {wheel.name}", flush=True)
    package = "ultrazohm[examples]" if args.examples else "ultrazohm"
    # Wheel-only installation means no Rust/compiler/build backend is needed.
    subprocess.run([uv, "pip", "install", "--python", str(python),
                    "--only-binary", ":all:", "--reinstall-package", "ultrazohm",
                    f"{package} @ {wheel.as_uri()}"], check=True, env=install_env)
    subprocess.run([str(python), "-c", "from ultrazohm import Acquisition, Client"], check=True)
    if not command.is_file():
        raise ValueError(f"Installation did not create the CLI command: {command}")
    subprocess.run([str(command), "--version"], check=True, env=install_env)
    if args.launch:
        extra = args.command[1:] if args.command[:1] == ["--"] else args.command
        rc_path = None
        if args.launch == "shell":
            if sys.platform == "win32":
                shell = shutil.which("pwsh") or shutil.which("powershell")
                if not shell:
                    parser.error("PowerShell is required to open the environment shell")
                activate = str(scripts / "Activate.ps1").replace("'", "''")
                launch = [shell, "-NoExit", "-Command", f". '{activate}'"]
            else:
                shell = shutil.which("bash")
                if not shell:
                    parser.error("Bash is required to open the environment shell")
                with tempfile.NamedTemporaryFile(mode="w", suffix=".bashrc", delete=False) as rc:
                    rc.write('if [ -f "$HOME/.bashrc" ]; then . "$HOME/.bashrc"; fi\n')
                    rc.write("source " + shlex.quote(str(scripts / "activate")) + "\n")
                    rc_path = Path(rc.name)
                launch = [shell, "--noprofile", "--rcfile", str(rc_path), "-i"]
        elif args.launch == "example":
            if extra:
                parser.error("the Python example does not take CLI arguments")
            launch = [str(python), str(root / "example_python_usage.py")]
        else:
            launch = [str(command), *extra]
        launch_env = install_env.copy()
        launch_env["VIRTUAL_ENV"] = str(venv)
        launch_env["PATH"] = str(scripts) + os.pathsep + launch_env.get("PATH", "")
        print({"shell": "Opening activated environment shell; type exit to return.",
               "example": "Starting Python example", "cli": "Starting UltraZohm CLI"}[args.launch], flush=True)
        try:
            child = subprocess.Popen(launch, env=launch_env)
            while True:
                try:
                    raise SystemExit(child.wait())
                except KeyboardInterrupt:
                    # Let the child handle console signals and finish its work.
                    continue
        finally:
            if rc_path is not None:
                rc_path.unlink(missing_ok=True)
    print(f"Ready. Run: {command} serve --interactive", flush=True)
    print(f"Or: {python} -m ultrazohm --help", flush=True)
    if sys.platform == "win32":
        print(f"Activate in PowerShell: & '{scripts / 'Activate.ps1'}'", flush=True)
    else:
        print(f"Activate: source {shlex.quote(str(scripts / 'activate'))}", flush=True)


if __name__ == "__main__":
    try:
        main()
    except (OSError, subprocess.CalledProcessError, ValueError, EOFError) as error:
        print(f"Setup failed: {error}", file=sys.stderr)
        raise SystemExit(1)
