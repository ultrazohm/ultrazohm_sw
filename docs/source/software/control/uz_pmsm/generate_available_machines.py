#!/usr/bin/env python3
"""Generate PMSM machine inventory CSV and C init macros from docs datasets."""

from __future__ import annotations

try:
    from pyuzlib.machine_catalog import main
except ModuleNotFoundError as exc:
    raise SystemExit(
        "pyuzlib is not importable. Install it with 'python -m pip install -e pyuzlib' "
        "or run with 'PYTHONPATH=pyuzlib/src python -m pyuzlib.machine_catalog'."
    ) from exc


if __name__ == "__main__":
    raise SystemExit(main(default_anchor=__file__))