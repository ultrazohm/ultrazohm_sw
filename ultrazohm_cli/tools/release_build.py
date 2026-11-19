"""Stage release sources without changing checkout metadata or lockfiles."""

import re
import shutil
import tempfile
from contextlib import contextmanager
from pathlib import Path

import tomllib

VERSION = re.compile(r"\d+\.\d+\.\d+(?:\.dev\d+)?")


@contextmanager
def staged_project(project, version=None):
    project = Path(project)
    metadata = tomllib.loads((project / "pyproject.toml").read_text())
    version = version or metadata["project"]["version"]
    if not VERSION.fullmatch(version):
        raise ValueError(f"Invalid release version: {version!r}")
    with tempfile.TemporaryDirectory(prefix="ultrazohm-release-") as directory:
        stage = Path(directory) / project.name
        stage.mkdir()
        for name in (
            "pyproject.toml",
            "README.md",
            "Cargo.toml",
            "Cargo.lock",
            "rust-toolchain.toml",
            "src",
            "python",
            "profiles",
        ):
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
        text = path.read_text()
        text, count = re.subn(
            r'^version = "[^"]+"$',
            f'version = "{version}"',
            text,
            count=1,
            flags=re.MULTILINE,
        )
        if count != 1:
            raise ValueError("Project version is missing")
        path.write_text(text)
        yield stage, version
