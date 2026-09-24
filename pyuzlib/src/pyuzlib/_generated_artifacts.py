"""Read-only, byte-exact checks of generated UTF-8 artifacts."""

from __future__ import annotations

import difflib
import shlex
from pathlib import Path


def check_generated_artifacts(
    artifacts: dict[Path, str], *, regenerate_args: list[str]
) -> int:
    stale = False
    for path, expected in artifacts.items():
        try:
            actual = path.read_bytes()
        except FileNotFoundError:
            print(f"Missing generated artifact: {path}")
            stale = True
            continue
        if actual == expected.encode("utf-8"):
            continue
        stale = True
        print(f"Stale generated artifact: {path}")
        diff = difflib.unified_diff(
            actual.decode("utf-8", errors="replace").splitlines(keepends=True),
            expected.splitlines(keepends=True),
            fromfile=str(path),
            tofile=f"{path} (expected)",
        )
        print("".join(diff), end="\n")
    if stale:
        print("Regenerate from the repository root with:")
        print(f"  PYTHONPATH=pyuzlib/src {shlex.join(regenerate_args)}")
        return 1
    print("Generated artifacts are up-to-date.")
    return 0
