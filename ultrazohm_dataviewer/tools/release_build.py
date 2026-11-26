"""Viewer release inputs and matching CLI dependency."""

import re
import sys
from contextlib import contextmanager
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from uz_build import VERSION as VERSION  # noqa: E402
from uz_build import staged_sources  # noqa: E402


@contextmanager
def staged_project(project, version=None):
    with staged_sources(project, ("pyproject.toml", "README.md", "src"), version) as (
        stage,
        version,
    ):
        path = stage / "pyproject.toml"
        text = path.read_text(encoding="utf-8")
        text, count = re.subn(
            r'"ultrazohm-cli==[^"]+"', f'"ultrazohm-cli=={version}"', text
        )
        if count != 1:
            raise ValueError("Viewer must declare one exact CLI dependency")
        module = stage / "src" / "ultrazohm_dataviewer" / "_version.py"
        if module.parent.is_dir():
            module.write_text(f"__version__ = {version!r}\n")
        path.write_text(text)
        yield stage, version
