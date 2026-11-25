"""CLI release inputs and embedded firmware resources."""

import shutil
import sys
from contextlib import contextmanager
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from uz_build import VERSION as VERSION  # noqa: E402
from uz_build import staged_sources  # noqa: E402


@contextmanager
def staged_project(project, version=None):
    project = Path(project)
    files = (
        "pyproject.toml",
        "README.md",
        "Cargo.toml",
        "build.rs",
        "Cargo.lock",
        "rust-toolchain.toml",
        "src",
        "python",
        "profiles",
    )
    with staged_sources(project, files, version) as (stage, version):
        resources = stage / "firmware_resources"
        shutil.copytree(project.parent / "tcl_scripts", resources)
        (resources / "launch").mkdir(exist_ok=True)
        for name in (
            "Debug_UltraZohm.launch",
            "Run_UltraZohm.launch",
            "Debug_UltraZohm_fast_restart_PL_reset.launch",
        ):
            shutil.copy2(
                project.parent / "vitis/software" / name, resources / "launch" / name
            )
        yield stage, version
