"""Shared application build primitives; independent of either runtime package."""

import os
import re
import subprocess
import zipfile
from collections.abc import Callable
from contextlib import contextmanager
from dataclasses import dataclass, field
from email.parser import BytesParser
from pathlib import Path

VERSION = re.compile(r"\d+\.\d+\.\d+(?:\.dev\d+)?")


@dataclass(frozen=True)
class Task:
    """A project task exposed as ``uz_developer PROJECT NAME``."""

    function: Callable
    help: str
    arguments: Callable = field(default=lambda parser: None)
    # Whether this invocation writes shared outputs and needs the project lock.
    locked: Callable = field(default=lambda args: False)


def run(*command, cwd=None, env=None):
    command = [str(part) for part in command]
    print("+", " ".join(command), flush=True)
    subprocess.run(command, cwd=cwd, env=env, check=True)


def venv_bin(venv, name="python"):
    windows = os.name == "nt"
    return (
        Path(venv)
        / ("Scripts" if windows else "bin")
        / (name + (".exe" if windows else ""))
    )


def single_wheel(directory, package="ultrazohm_cli"):
    wheels = sorted(Path(directory).glob(f"{package}-*.whl"))
    if len(wheels) != 1:
        raise SystemExit(
            f"Expected exactly one wheel in {directory}, found {len(wheels)}"
        )
    return wheels[0]


def wheel_version(path):
    with zipfile.ZipFile(path) as archive:
        metadata = [
            name for name in archive.namelist() if name.endswith(".dist-info/METADATA")
        ]
        if len(metadata) != 1:
            raise ValueError(f"Expected one wheel metadata file in {path}")
        version = BytesParser().parsebytes(archive.read(metadata[0]))["Version"]
        if not version:
            raise ValueError(f"Wheel metadata is missing its version: {path}")
        return version


@contextmanager
def build_lock(root, project):
    # Keep the lock on the shared filesystem, not in host/container-specific /tmp.
    directory = Path(root) / ".uz-build-locks"
    directory.mkdir(exist_ok=True)
    with (directory / f"{project}.lock").open("a+b") as stream:
        if stream.tell() == 0:
            stream.write(b"0")
            stream.flush()
        stream.seek(0)
        try:
            if os.name == "nt":
                import msvcrt

                msvcrt.locking(stream.fileno(), msvcrt.LK_NBLCK, 1)
            else:
                import fcntl

                fcntl.flock(stream, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except OSError as error:
            raise RuntimeError(
                f"Another {project} build is using this checkout's outputs; retry when it finishes."
            ) from error
        try:
            yield
        finally:
            if os.name == "nt":
                msvcrt.locking(stream.fileno(), msvcrt.LK_UNLCK, 1)
            else:
                fcntl.flock(stream, fcntl.LOCK_UN)
    # Never unlink lock files: another process may already have one open.


@contextmanager
def staged_sources(project, files, version=None):
    """Copy explicit release inputs and stamp metadata without editing the checkout."""
    import shutil
    import tempfile
    import tomllib

    project = Path(project)
    metadata = tomllib.loads((project / "pyproject.toml").read_text(encoding="utf-8"))
    version = version or metadata["project"]["version"]
    if not VERSION.fullmatch(version):
        raise ValueError(f"Invalid release version: {version!r}")
    with tempfile.TemporaryDirectory(prefix="ultrazohm-release-") as directory:
        stage = Path(directory) / project.name
        stage.mkdir()
        for name in files:
            source = project / name
            if source.is_dir():
                shutil.copytree(
                    source,
                    stage / name,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc", "*.egg-info"),
                )
            elif source.is_file():
                shutil.copy2(source, stage / name)
        path = stage / "pyproject.toml"
        text, count = re.subn(
            r'^version = "[^"]+"$',
            f'version = "{version}"',
            path.read_text(encoding="utf-8"),
            count=1,
            flags=re.MULTILINE,
        )
        if count != 1:
            raise ValueError("Project version is missing")
        path.write_text(text, encoding="utf-8")
        yield stage, version
