"""UltraZohm Data Viewer -- an imgui_bundle based log viewer.

A native/web data viewer for JavaScope ``.csv`` and ``.parquet`` logs, providing
the same core functionality as the legacy Plotly/Dash ``dataviewer.py`` with a
VSCode-style docked layout, drag-and-drop subplots and range-aware downsampling.

The data/analysis core is also usable **headlessly as a library** -- see
:mod:`uz_dataviewer.api` (and the repository's ``uz_dataviewer_library.rst``). Importing this package does
**not** import the imgui GUI stack; GUI entry points live in ``uz_dataviewer.app``. Headless operations need only
numpy/pandas/pyarrow.
"""

from __future__ import annotations

__version__ = "0.1.0"

# GUI-free facade -- safe to import on a headless box (no imgui_bundle needed).
from .api import Dataset, fft, fft_frame, kinds, node, read

__all__ = [
    "__version__",
    # headless library API
    "Dataset",
    "read",
    "fft",
    "fft_frame",
    "node",
    "kinds",
]
