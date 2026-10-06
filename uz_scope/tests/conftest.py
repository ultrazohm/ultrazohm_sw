from __future__ import annotations

import sys
from pathlib import Path

import pytest

TESTS_DIR = Path(__file__).resolve().parent
UZ_SCOPE_DIR = TESTS_DIR.parent
REPO_ROOT = UZ_SCOPE_DIR.parent

# Run from a source checkout without installing.
sys.path.insert(0, str(UZ_SCOPE_DIR / "src"))


@pytest.fixture(scope="session")
def repo_root() -> Path:
    return REPO_ROOT


@pytest.fixture(scope="session")
def real_header_path(repo_root: Path) -> Path:
    path = repo_root / "vitis/software/Baremetal/src/include/javascope.h"
    assert path.is_file(), f"expected repo header at {path}"
    return path


@pytest.fixture(scope="session")
def real_properties_path(repo_root: Path) -> Path:
    path = repo_root / "javascope/properties.ini"
    assert path.is_file(), f"expected legacy properties at {path}"
    return path
