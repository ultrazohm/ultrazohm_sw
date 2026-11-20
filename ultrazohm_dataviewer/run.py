#!/usr/bin/env python3
"""Convenience launcher that works from a source checkout without installing.

Usage::

    python run.py gui [file1.csv file2.parquet session.json ...]
"""

from __future__ import annotations

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "src"))

from ultrazohm_dataviewer.cli import main  # noqa: E402

if __name__ == "__main__":
    raise SystemExit(main())
