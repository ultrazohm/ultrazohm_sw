"""One local development environment for the CLI and editable DataViewer."""

import json
import os
import shutil
import subprocess
import sys
import tempfile
from contextlib import contextmanager
from pathlib import Path

from uz_environment import environment_lock

ROOT = Path(__file__).resolve().parent


def run(*command):
    command = [str(part) for part in command]
    print("+", " ".join(command), flush=True)
    with subprocess.Popen(command) as child:
        while True:
            try:
                code = child.wait()
                break
            except KeyboardInterrupt:
                continue
    if code:
        raise subprocess.CalledProcessError(code, command)


def executable(name):
    return (
        ROOT
        / ".venv"
        / ("Scripts" if os.name == "nt" else "bin")
        / (name + (".exe" if os.name == "nt" else ""))
    )


def saved_setup():
    try:
        state = json.loads((ROOT / ".venv/.uz-setup.json").read_text())
        return state if isinstance(state, dict) else {}
    except (OSError, ValueError):
        return {}


def guard_host_environment():
    if os.environ.get("UZ_DEV_CONTAINER") == "1":
        raise RuntimeError(
            "The dev container uses its own Python. Run ultrazohm-cli, "
            "ultrazohm-dataviewer, or python directly; refresh with "
            "bash .devcontainer/post-create.sh. The workspace .venv belongs to the host."
        )


def require_environment():
    guard_host_environment()
    state = saved_setup()
    context = state.get("context", {})
    if (
        state.get("source") != "local"
        or state.get("app") != "viewer"
        or context.get("root") != str(ROOT)
        or context.get("platform") != sys.platform
        or not all(
            executable(name).is_file()
            for name in ("python", "ultrazohm-cli", "ultrazohm-dataviewer")
        )
    ):
        raise RuntimeError(
            "No usable local development environment for this checkout/platform. "
            "Run uz_developer setup first."
        )
    # Also detects moved/deleted interpreter targets and incompatible binaries.
    try:
        subprocess.run(
            [str(executable("python")), "-c", "import sys"],
            check=True,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
    except (OSError, subprocess.CalledProcessError) as error:
        raise RuntimeError(
            "Development Python is unusable; run uz_developer setup."
        ) from error


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


def setup():
    guard_host_environment()
    # Lock before building: refuse immediately if a shell/application is active.
    with environment_lock(ROOT):
        with tempfile.TemporaryDirectory(prefix="uz-wheel-") as directory:
            directory = Path(directory)
            run(
                sys.executable,
                ROOT / "ultrazohm_cli/tasks.py",
                "wheel",
                "--out",
                directory,
            )
            wheels = list(directory.glob("ultrazohm_cli-*.whl"))
            if len(wheels) != 1:
                raise RuntimeError(f"Expected one CLI wheel, found {len(wheels)}")
            constraints = directory / "constraints.txt"
            run(
                "uv",
                "export",
                "--project",
                ROOT / "ultrazohm_dataviewer",
                "--locked",
                "--no-dev",
                "--no-emit-project",
                "--no-emit-package",
                "ultrazohm-cli",
                "--no-hashes",
                "--format",
                "requirements.txt",
                "--output-file",
                constraints,
            )
            with _replace_environment():
                run(
                    "uv",
                    "venv",
                    "--clear",
                    "--python",
                    (ROOT / ".python-version").read_text().strip(),
                    ROOT / ".venv",
                )
                run(
                    "uv",
                    "pip",
                    "install",
                    "--python",
                    executable("python"),
                    "--no-sources",
                    "--constraint",
                    constraints,
                    "--only-binary",
                    "imgui-bundle",
                    wheels[0],
                    "--editable",
                    ROOT / "ultrazohm_dataviewer",
                )
                run("uv", "pip", "check", "--python", executable("python"))
                for name in ("ultrazohm-cli", "ultrazohm-dataviewer"):
                    run(executable(name), "--help")
                versions = subprocess.check_output(
                    [
                        str(executable("python")),
                        "-c",
                        "import importlib.metadata,json; print(json.dumps({d.metadata['Name']: "
                        "d.version for d in importlib.metadata.distributions()}))",
                    ],
                    text=True,
                )
                (ROOT / ".venv/.uz-setup.json").write_text(
                    json.dumps(
                        {
                            "source": "local",
                            "app": "viewer",
                            "context": {"root": str(ROOT), "platform": sys.platform},
                            "versions": json.loads(versions),
                        }
                    )
                    + "\n"
                )
    print(f"Development environment ready in {ROOT / '.venv'}.")
