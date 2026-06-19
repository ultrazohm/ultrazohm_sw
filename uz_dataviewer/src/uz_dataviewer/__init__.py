"""UltraZohm Data Viewer -- an imgui_bundle based log viewer.

A native/web data viewer for JavaScope ``.csv`` and ``.parquet`` logs, providing
the same core functionality as the legacy Plotly/Dash ``dataviewer.py`` with a
VSCode-style docked layout, drag-and-drop subplots and range-aware downsampling.

The data/analysis core is also usable **headlessly as a library** -- see
:mod:`uz_dataviewer.api` (and ``docs/LIBRARY.md``). Importing this package does
**not** import the imgui GUI stack; the GUI (``DataViewerApp``/``main``) is loaded
lazily, only when first accessed, so a headless ``import uz_dataviewer`` needs only
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
    # GUI entry points (lazily imported -- see __getattr__)
    "DataViewerApp",
    "main",
]


def __getattr__(name: str):
    """Lazily expose the GUI entry points without importing imgui at package load.

    ``from uz_dataviewer import main`` / ``DataViewerApp`` keep working, but the
    ``.app`` module (and the whole imgui_bundle stack it pulls in) is only imported
    on first access -- so a headless ``import uz_dataviewer`` stays GUI-free.
    """
    if name in ("DataViewerApp", "main"):
        from . import app

        return getattr(app, name)
    raise AttributeError(f"module {__name__!r} has no attribute {name!r}")
