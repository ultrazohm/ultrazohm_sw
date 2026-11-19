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

ROOT = Path(__file__).resolve().parent
WINDOWS = os.name == "nt"
PROJECTS = {"cli": "ultrazohm_cli", "viewer": "ultrazohm_dataviewer"}
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
    for path in (".python-version", "tasks.py", "ultrazohm_dataviewer/pyproject.toml", "ultrazohm_dataviewer/uv.lock"):
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


def setup(source=None, *, app=None, reuse=False):
    """Prepare published applications or the local checkout in the managed venv."""
    state = saved_setup()
    selected = source or state.get("source", "stable")
    selected_app = app or state.get("app", "viewer")
    context = environment_context()
    signature = fingerprint()
    commands = ["ultrazohm-cli"]
    if selected_app == "viewer":
        commands.append("ultrazohm-dataviewer")
    if (reuse and source is None and app is None and state.get("fingerprint") == signature
            and state.get("app") == selected_app
            and all(executable(name).is_file() for name in ["python", *commands])):
        return
    python_version = (ROOT / ".python-version").read_text().strip()
    env = os.environ.copy()
    env.pop("VIRTUAL_ENV", None)
    env["UV_PROJECT_ENVIRONMENT"] = str(ROOT / ".venv")
    marker = ROOT / ".venv" / ".uz-setup.json"
    with tempfile.TemporaryDirectory(prefix="uz-wheel-") as directory:
        wheel = None
        if selected == "local":
            project_task("cli", "wheel", "--out", directory)
            wheels = list(Path(directory).glob("ultrazohm_cli-*.whl"))
            if len(wheels) != 1:
                raise SystemExit(f"Expected one CLI wheel in {directory}, found {len(wheels)}")
            wheel = wheels[0]
        # Build first, then replace the managed environment. This removes stale
        # editable installs and GUI dependencies when changing application sets.
        if marker.exists():
            marker.unlink()
        run("uv", "venv", "--clear", "--python", python_version, ROOT / ".venv", env=env)
        marker.write_text(json.dumps({"source": selected, "app": selected_app}) + "\n")
        if selected == "local":
            packages = [wheel]
            if selected_app == "viewer":
                packages += ["--editable", ROOT / "ultrazohm_dataviewer"]
            run("uv", "pip", "install", "--python", executable("python"),
                "--no-sources", "--only-binary", "imgui-bundle", *packages, env=env)
        else:
            package = "ultrazohm-cli" if selected_app == "cli" else "ultrazohm-dataviewer"
            run("uv", "pip", "install", "--python", executable("python"),
                "--only-binary", ":all:", "--prerelease",
                "allow" if selected == "prerelease" else "disallow", package, env=env)
        run("uv", "pip", "check", "--python", executable("python"), env=env)
        for name in commands:
            run(executable(name), "--help", stdout=subprocess.DEVNULL)
        versions = subprocess.check_output(
            [str(executable("python")), "-c",
             "import importlib.metadata,json; print(json.dumps({d.metadata['Name']: d.version "
             "for d in importlib.metadata.distributions()}))"], text=True)
        marker.write_text(json.dumps({"source": selected, "app": selected_app,
                                     "fingerprint": signature, "context": context,
                                     "versions": json.loads(versions)}) + "\n")
    print(f"{selected_app} environment ready in {ROOT / '.venv'} ({selected}).", flush=True)


def main(argv=None):
    parser = argparse.ArgumentParser(
        prog=".\\uz.ps1" if WINDOWS else "./uz",
        description="Set up, build and check the CLI and Data Viewer with one shared environment.")
    commands = parser.add_subparsers(dest="command")
    for name in ("setup", "shell"):
        task = commands.add_parser(name, help="prepare both applications" if name == "setup" else
                                   "prepare both applications and open an activated shell")
        task.add_argument("source", nargs="?", choices=SOURCES,
                          help="Application source: reuse last selection, or stable on first use")
        task.add_argument("--app", choices=PROJECTS, help="cli only, or viewer with CLI; defaults to last selection or viewer")
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
            setup(args.source, app=args.app, reuse=args.command == "shell")
            if args.command == "shell":
                run(executable("python"), ROOT / "scripts" / "env_shell.py", interactive=True)
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
