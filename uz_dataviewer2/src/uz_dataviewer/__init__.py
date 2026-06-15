"""UltraZohm Data Viewer -- an imgui_bundle based log viewer.

A native/web data viewer for JavaScope ``.csv`` and ``.parquet`` logs, providing
the same core functionality as the legacy Plotly/Dash ``dataviewer.py`` with a
VSCode-style docked layout, drag-and-drop subplots and range-aware downsampling.
"""

from __future__ import annotations

__version__ = "0.1.0"

from .app import DataViewerApp, main

__all__ = ["DataViewerApp", "main", "__version__"]
