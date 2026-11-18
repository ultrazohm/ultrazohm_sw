"""UltraZohm Data Viewer -- an imgui_bundle based log viewer.

A desktop data viewer for JavaScope ``.csv`` and ``.parquet`` logs, providing
the same core functionality as the legacy Plotly/Dash ``dataviewer.py`` with a
VSCode-style docked layout, drag-and-drop subplots and range-aware downsampling.

The data/analysis core is also usable **headlessly as a library** -- see
:mod:`uz_dataviewer.api` (and the repository's ``uz_dataviewer_library.rst``). Importing this package does
**not** import the imgui GUI stack; GUI entry points live in ``uz_dataviewer.app``. Headless operations need only
numpy/pandas/pyarrow.
"""

from __future__ import annotations

__version__ = "0.1.0"

# Control clients need only the standard library. Numerical dependencies are
# loaded when their public functions are first requested.
from .client import Client, ViewerError, RunHandle, NodeHandle, ViewHandle


def __getattr__(name):
    if name in {"Dataset", "fft", "fft_frame", "kinds", "node", "read"}:
        from . import api
        value = getattr(api, name)
        globals()[name] = value
        return value
    raise AttributeError(f"module {__name__!r} has no attribute {name!r}")

__all__ = [
    "__version__",
    "Client",
    "ViewerError",
    "RunHandle",
    "NodeHandle",
    "ViewHandle",
    # headless library API
    "Dataset",
    "read",
    "fft",
    "fft_frame",
    "node",
    "kinds",
]
