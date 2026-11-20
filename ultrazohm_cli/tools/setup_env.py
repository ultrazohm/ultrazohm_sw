"""Project installation and activated shell support; standard library only."""

import hashlib
import json
import os
import platform
import shutil
import subprocess
import sys
import tempfile
from contextlib import contextmanager
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from uz_environment import environment_lock  # noqa: E402

WINDOWS = os.name == "nt"
APP = "cli"
PROJECT = "ultrazohm_cli"
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
    return {
        "root": str(ROOT),
        "python_prefix": sys.base_prefix,
        "python_version": list(sys.version_info[:3]),
        "platform": sys.platform,
        "machine": platform.machine(),
        "libc": list(platform.libc_ver()),
    }


def fingerprint():
    digest = hashlib.sha256()
    digest.update(json.dumps(environment_context()).encode())
    for path in (
        ".python-version",
        f"{PROJECT}/tasks.py",
        f"{PROJECT}/tools/setup_env.py",
        f"{PROJECT}/pyproject.toml",
        f"{PROJECT}/Cargo.lock",
    ):
        digest.update((ROOT / path).read_bytes())
    return digest.hexdigest()


def saved_setup():
    try:
        state = json.loads((ROOT / ".venv" / ".uz-setup.json").read_text())
        return (
            state if isinstance(state, dict) and state.get("source") in SOURCES else {}
        )
    except (OSError, ValueError):
        return {}


def cli_task(task, *arguments):
    # Keep the caller's directory: paths such as --cli-wheel are relative to it.
    run(sys.executable, ROOT / "ultrazohm_cli" / "tasks.py", task, *arguments)


@contextmanager
def replace_environment():
    with environment_lock(ROOT):
        with _replace_environment():
            yield


@contextmanager
def _replace_environment():
    """Restore on failure; retain the backup if recovery itself fails."""
    environment = ROOT / ".venv"
    directory = Path(tempfile.mkdtemp(prefix=".uz-backup-", dir=ROOT))
    backup = directory / "environment"
    succeeded = False
    try:
        existed = environment.exists()
        if existed:
            environment.rename(backup)
        try:
            yield
            succeeded = True
        except BaseException:
            try:
                if environment.exists():
                    shutil.rmtree(environment)
                if existed:
                    backup.rename(environment)
            except BaseException as recovery_error:
                message = (
                    f"Environment recovery failed. Previous environment retained at {backup}. "
                    f"After resolving the filesystem error, restore it to {environment}."
                    if existed
                    else f"Could not remove the failed environment at {environment}."
                )
                raise RuntimeError(message) from recovery_error
            raise
    finally:
        # Never let automatic temporary-directory cleanup erase the only backup.
        if succeeded:
            shutil.rmtree(directory)
        elif not backup.exists():
            shutil.rmtree(directory, ignore_errors=True)


def setup(source=None, *, reuse=False):
    """Prepare published applications or the local checkout in the managed venv."""
    state = saved_setup()
    selected = source or state.get("source", "stable")
    context = environment_context()
    signature = fingerprint()
    commands = ["ultrazohm-cli"]
    if (
        reuse
        and source is None
        and state.get("fingerprint") == signature
        and state.get("app") == APP
        and all(executable(name).is_file() for name in ["python", *commands])
    ):
        return
    python_version = (ROOT / ".python-version").read_text().strip()
    env = os.environ.copy()
    env.pop("VIRTUAL_ENV", None)
    env["UV_PROJECT_ENVIRONMENT"] = str(ROOT / ".venv")
    marker = ROOT / ".venv" / ".uz-setup.json"
    with tempfile.TemporaryDirectory(prefix="uz-wheel-") as directory:
        wheel = None
        if selected == "local":
            cli_task("wheel", "--out", directory)
            wheels = list(Path(directory).glob("ultrazohm_cli-*.whl"))
            if len(wheels) != 1:
                raise SystemExit(
                    f"Expected one CLI wheel in {directory}, found {len(wheels)}"
                )
            wheel = wheels[0]
        if selected != "local":
            # Resolve and download the published package before moving the working
            # environment. The final install reuses uv's wheel cache; rollback
            # still covers installation, dependency checks and command smoke tests.
            run(
                "uv",
                "pip",
                "install",
                "--python",
                python_version,
                "--target",
                Path(directory) / "preflight",
                "--only-binary",
                ":all:",
                "--prerelease",
                "allow" if selected == "prerelease" else "disallow",
                "ultrazohm-cli",
                env=env,
            )
        # Build first, then replace the managed environment. This removes stale
        # editable installs and GUI dependencies when changing application sets.
        with replace_environment():
            if marker.exists():
                marker.unlink()
            run(
                "uv",
                "venv",
                "--clear",
                "--python",
                python_version,
                ROOT / ".venv",
                env=env,
            )
            marker.write_text(json.dumps({"source": selected, "app": APP}) + "\n")
            if selected == "local":
                run(
                    "uv",
                    "pip",
                    "install",
                    "--python",
                    executable("python"),
                    wheel,
                    env=env,
                )
            else:
                package = "ultrazohm-cli"
                run(
                    "uv",
                    "pip",
                    "install",
                    "--python",
                    executable("python"),
                    "--only-binary",
                    ":all:",
                    "--prerelease",
                    "allow" if selected == "prerelease" else "disallow",
                    package,
                    env=env,
                )
            run("uv", "pip", "check", "--python", executable("python"), env=env)
            for name in commands:
                run(executable(name), "--help", stdout=subprocess.DEVNULL)
            versions = subprocess.check_output(
                [
                    str(executable("python")),
                    "-c",
                    "import importlib.metadata,json; print(json.dumps({d.metadata['Name']: d.version "
                    "for d in importlib.metadata.distributions()}))",
                ],
                text=True,
            )
            marker.write_text(
                json.dumps(
                    {
                        "source": selected,
                        "app": APP,
                        "fingerprint": signature,
                        "context": context,
                        "versions": json.loads(versions),
                    }
                )
                + "\n"
            )
    print(f"{APP} environment ready in {ROOT / '.venv'} ({selected}).", flush=True)


def setup_task(args):
    try:
        setup(args.source, reuse=args.task == "shell")
    except subprocess.CalledProcessError:
        if (args.source or saved_setup().get("source", "stable")) == "stable":
            launcher = ".\\uz.ps1" if os.name == "nt" else "./uz"
            print(
                "Stable installation failed. If only development releases are available, "
                f"run {launcher} setup prerelease --app {APP}. "
                "The previous environment has been preserved.",
                file=sys.stderr,
            )
        raise
    if args.task == "shell":
        with environment_lock(ROOT, use=True):
            run(
                executable("python"),
                Path(__file__).with_name("env_shell.py"),
                interactive=True,
            )
