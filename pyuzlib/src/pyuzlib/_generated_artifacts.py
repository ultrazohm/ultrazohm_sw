"""Read-only checks of generated artifacts, with opt-in CSV value tolerance."""

from __future__ import annotations

import csv
import difflib
import io
import math
import shlex
from pathlib import Path


def _csv_values_match(actual: bytes, expected: str, columns: frozenset[str]) -> bool:
    """Allow roundoff only in declared value columns, never grid coordinates.

    The absolute tolerance covers near-zero derivatives; the relative tolerance
    allows double-precision numerical noise without hiding meaningful changes.
    """
    try:
        old = list(csv.reader(io.StringIO(actual.decode("utf-8")), strict=True))
        new = list(csv.reader(io.StringIO(expected), strict=True))
        if not new or not old or old[0] != new[0] or len(old) != len(new):
            return False
        for old_row, new_row in zip(old[1:], new[1:]):
            if len(old_row) != len(new[0]) or len(new_row) != len(new[0]):
                return False
            for name, a, b in zip(new[0], old_row, new_row):
                if name in columns:
                    a_value, b_value = float(a), float(b)
                    if not (math.isfinite(a_value) and math.isfinite(b_value)):
                        return False
                    if not math.isclose(a_value, b_value, rel_tol=1e-12, abs_tol=1e-14):
                        return False
                elif a != b:
                    return False
        return True
    except (UnicodeDecodeError, ValueError, csv.Error):
        return False


def check_generated_artifacts(
    artifacts: dict[Path, str],
    *,
    regenerate_args: list[str],
    numeric_csv_columns: frozenset[str] = frozenset(),
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
        if (
            path.suffix == ".csv"
            and numeric_csv_columns
            and _csv_values_match(actual, expected, numeric_csv_columns)
        ):
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
