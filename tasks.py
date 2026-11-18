"""Repository tasks behind the Bash/PowerShell launchers; standard library only."""
import argparse
import hashlib
import json
import os
import platform
from pathlib import Path
import subprocess
import sys
import tempfile
import tomllib

ROOT = Path(__file__).resolve().parent
WINDOWS = os.name == "nt"
PROJECTS = {"cli": "uz_cli", "viewer": "uz_dataviewer"}
SOURCES = ("local", "stable", "prerelease")


def run(*command, interactive=False, **kwargs):
    command = [str(part) for part in command]
    print("+", " ".join(command), flush=True)
    if not interactive:
        subprocess.run(command, check=True, **kwargs)
        return
    # Ctrl-C belongs to the interactive child shell, not this launcher.
    with subprocess.Popen(command, **kwargs) as child:
        while True:
            try:
                code = child.wait()
                break
            except KeyboardInterrupt:
                continue
    if code:
        raise subprocess.CalledProcessError(code, command)


def scripts():
    return ROOT / ".venv" / ("Scripts" if WINDOWS else "bin")


def executable(name):
    return scripts() / (name + (".exe" if WINDOWS else ""))


def environment_context():
    # Venv scripts and editable installs contain absolute paths. A checkout
    # mounted in a container (or moved on the host) needs to be prepared again,
    # even if its tracked inputs have not changed. Do not hash sys.executable:
    # the bootstrap's isolated environment has a different path on each call.
    return dict(root=str(ROOT), python_prefix=sys.base_prefix, python_version=list(sys.version_info[:3]),
                platform=sys.platform, machine=platform.machine(), libc=list(platform.libc_ver()))


def fingerprint():
    digest = hashlib.sha256()
    digest.update(json.dumps(environment_context()).encode())
    for path in (".python-version", "tasks.py", "uz_dataviewer/pyproject.toml", "uz_dataviewer/uv.lock"):
        digest.update((ROOT / path).read_bytes())
    return digest.hexdigest()


def saved_setup():
    try:
        state = json.loads((ROOT / ".venv" / ".uz-setup.json").read_text())
        return state if isinstance(state, dict) and state.get("source") in SOURCES else {}
    except (OSError, ValueError):
        return {}


def project_task(project, task, *arguments):
    # Keep the caller's directory: paths such as --cli-wheel are relative to it.
    run(sys.executable, ROOT / PROJECTS[project] / "tasks.py", task, *arguments)


def setup(source=None, *, reuse=False):
    """Install both commands into the repository venv; shell reuses a completed setup."""
    state = saved_setup()
    context = environment_context()
    selected = source or state.get("source", "stable")
    signature = fingerprint()
    if (reuse and source is None and state.get("fingerprint") == signature
            and all(executable(name).is_file() for name in ("python", "ultrazohm_cli", "uz-dataviewer"))):
        return

    viewer = ROOT / "uz_dataviewer"
    python_version = (ROOT / ".python-version").read_text().strip()
    metadata = tomllib.loads((viewer / "pyproject.toml").read_text())
    # Respect the viewer's minimum CLI version for published packages. Local
    # builds deliberately override it (their base version may be older).
    requirement = next(dep.split(";")[0].strip() for dep in metadata["project"]["dependencies"]
                       if dep.startswith("ultrazohm_cli"))
    with tempfile.TemporaryDirectory(prefix="uz-wheel-") as directory:
        package = requirement
        if selected == "local":
            project_task("cli", "wheel", "--out", directory)
            wheels = list(Path(directory).glob("ultrazohm_cli-*.whl"))
            if len(wheels) != 1:
                raise SystemExit(f"Expected one CLI wheel in {directory}, found {len(wheels)}")
            package = str(wheels[0])

        marker = ROOT / ".venv" / ".uz-setup.json"
        # Retain the previous selection for retries, but never regard a
        # partially updated environment as ready after a failed sync/install.
        retry_state = json.dumps({"source": state.get("source", selected),
                                  "context": state.get("context", context)}) + "\n"
        if marker.exists():
            marker.write_text(retry_state)
        env = os.environ.copy()
        env.pop("VIRTUAL_ENV", None)
        env["UV_PROJECT_ENVIRONMENT"] = str(ROOT / ".venv")
        if state.get("context") is not None and state["context"] != context:
            # Updating packages alone does not repair activation scripts or
            # native libraries copied from a different host/container.
            run("uv", "venv", "--clear", "--python", python_version, ROOT / ".venv", env=env)
            marker.write_text(retry_state)
        # Install the viewer and its locked dependencies, selecting the CLI
        # separately so stable/prerelease/local never rewrites uv.lock.
        run("uv", "sync", "--project", viewer, "--python", python_version,
            "--locked", "--inexact", "--no-dev", "--no-install-package", "ultrazohm-cli",
            "--no-build-package", "imgui-bundle", env=env)
        # Sync may recreate the venv for a different interpreter. Write after
        # it completes, also avoiding a non-venv directory on first setup.
        marker.write_text(retry_state)
        options = [] if selected == "local" else [
            "--only-binary", ":all:", "--upgrade-package", "ultrazohm_cli",
            "--prerelease", "allow" if selected == "prerelease" else "disallow"]
        try:
            run("uv", "pip", "install", "--python", executable("python"), "--no-deps",
                "--reinstall-package", "ultrazohm_cli", *options, package)
        except subprocess.CalledProcessError:
            if selected == "stable":
                launcher = ".\\uz.ps1" if WINDOWS else "./uz"
                print(f"Stable CLI installation failed. If no compatible stable wheel exists, use\n"
                      f"  {launcher} setup prerelease\n"
                      f"or {launcher} setup local (requires Rust/C++ tools).", file=sys.stderr)
            raise
        # Fail during setup if either installed entry point cannot load.
        for name in ("ultrazohm_cli", "uz-dataviewer"):
            run(executable(name), "--help", stdout=subprocess.DEVNULL)
        marker.write_text(json.dumps({"source": selected, "fingerprint": signature, "context": context}) + "\n")
    print(f"Both applications are ready in {ROOT / '.venv'} ({selected} CLI).", flush=True)


def main(argv=None):
    parser = argparse.ArgumentParser(
        prog=".\\uz.ps1" if WINDOWS else "./uz",
        description="Set up, build and check the CLI and Data Viewer with one shared environment.")
    commands = parser.add_subparsers(dest="command")
    for name in ("setup", "shell"):
        task = commands.add_parser(name, help="prepare both applications" if name == "setup" else
                                   "prepare both applications and open an activated shell")
        task.add_argument("source", nargs="?", choices=(*SOURCES, "release"),
                          help="CLI source: reuse last selection, or stable on first use; release aliases stable")
    for name in ("build", "check", "task"):
        help_text = {"build": "build a CLI wheel or viewer desktop bundle",
                     "check": "run the same checks as CI",
                     "task": "run a project task (e.g. task cli release-wheel, task viewer bundle-smoke)"}[name]
        task = commands.add_parser(name, help=help_text)
        task.add_argument("project", choices=PROJECTS)
        if name == "task":
            task.add_argument("task", help="project task; use 'help' to list tasks")
        task.add_argument("arguments", nargs=argparse.REMAINDER, help="arguments forwarded to the project task")
    args = parser.parse_args(argv)
    if args.command is None:
        parser.print_help()
        return
    try:
        if args.command in ("setup", "shell"):
            source = "stable" if args.source == "release" else args.source
            setup(source, reuse=args.command == "shell")
            if args.command == "shell":
                run(executable("python"), "-m", "uz_dataviewer.env_shell", interactive=True)
            else:
                print("Enter with .\\uz.ps1 shell or .\\.venv\\Scripts\\Activate.ps1" if WINDOWS else
                      "Enter with ./uz shell or source .venv/bin/activate")
        else:
            task = args.task if args.command == "task" else (
                "check" if args.command == "check" else "wheel" if args.project == "cli" else "bundle")
            if args.command == "check" and not set(args.arguments) & {"--help", "-h"}:
                run(sys.executable, "-m", "unittest", "discover", "-s", str(ROOT / "tests"), "-v")
            project_task(args.project, task, *args.arguments)
    except subprocess.CalledProcessError as error:
        raise SystemExit(error.returncode or 1)
    except KeyboardInterrupt:
        raise SystemExit(130)


if __name__ == "__main__":
    main()
