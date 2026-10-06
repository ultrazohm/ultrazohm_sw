"""Command-routed state for dynamic Data Viewer-style live plot windows."""

from __future__ import annotations

import enum
from dataclasses import dataclass, field


class PlotType(enum.Enum):
    LINE = "Line"
    SCATTER = "Scatter"
    STAIRS = "Stairs"
    XY = "XY"


class XyStyle(enum.Enum):
    LINE = "Line"
    MARKERS = "Markers"
    BOTH = "Both"


GRID_PRESETS = ((1, 1), (1, 2), (2, 1), (2, 2), (1, 3), (3, 1))


@dataclass
class PlotCellState:
    segments: list[int] = field(default_factory=list)
    plot_type: PlotType = PlotType.LINE
    xy_source: int | None = None
    xy_style: XyStyle = XyStyle.LINE
    y2_segments: list[int] = field(default_factory=list)
    show_samples: bool = False
    cursors: bool = False
    cursor_x: tuple[float, float] | None = None
    spy: bool = False
    spy_rect: tuple[float, float, float, float] | None = None
    fit_pending: bool = True
    pending_x: tuple[float, float] | None = None
    pending_y: tuple[float, float] | None = None
    export_relative: bool = False

    def add(self, segment_id: int) -> bool:
        if segment_id in self.segments:
            return False
        self.segments.append(segment_id)
        self.fit_pending = True
        return True

    def remove(self, segment_id: int) -> None:
        if segment_id in self.segments:
            self.segments.remove(segment_id)
        if segment_id in self.y2_segments:
            self.y2_segments.remove(segment_id)
        if self.xy_source == segment_id:
            self.xy_source = None


@dataclass
class PlotWindowState:
    id: int
    title: str
    rows: int = 1
    cols: int = 1
    cells: list[PlotCellState] = field(default_factory=lambda: [PlotCellState()])
    follow_live: bool = True
    link_x: bool = True
    open: bool = True
    shared_x: tuple[float, float] | None = None
    capture_sequence: int = 0

    @property
    def token(self) -> str:
        return f"window_{self.id}"

    def set_grid(self, rows: int, cols: int) -> None:
        rows, cols = max(1, rows), max(1, cols)
        cells = [PlotCellState() for _ in range(rows * cols)]
        for i in range(min(len(cells), len(self.cells))):
            cells[i] = self.cells[i]
        self.rows, self.cols, self.cells = rows, cols, cells


class PlotWorkspace:
    def __init__(self) -> None:
        self.windows: list[PlotWindowState] = [PlotWindowState(1, "Plot 1")]
        self._next_id = 2

    def get(self, window_id: int) -> PlotWindowState | None:
        return next((w for w in self.windows if w.id == int(window_id)), None)

    def create(self, title: str | None = None) -> PlotWindowState:
        wid = self._next_id
        self._next_id += 1
        window = PlotWindowState(wid, title or f"Plot {wid}")
        self.windows.append(window)
        return window

    def close(self, window_id: int) -> None:
        window = self.get(window_id)
        if window is not None:
            window.open = False

    def replace_segments(self, mapping: dict[int, int]) -> None:
        """Rebind active plot sources across reconnect-created segments."""
        for window in self.windows:
            for cell in window.cells:
                cell.segments = [mapping.get(sid, sid) for sid in cell.segments]
                cell.y2_segments = [mapping.get(sid, sid) for sid in cell.y2_segments]
                if cell.xy_source in mapping:
                    cell.xy_source = mapping[cell.xy_source]

    def prune_segments(self, valid: set[int]) -> None:
        for window in self.windows:
            for cell in window.cells:
                cell.segments = [sid for sid in cell.segments if sid in valid]
                cell.y2_segments = [sid for sid in cell.y2_segments if sid in valid]
                if cell.xy_source not in valid:
                    cell.xy_source = None

    def to_dict(self) -> dict:
        return {
            "next_id": self._next_id,
            "windows": [
                {
                    "id": w.id,
                    "title": w.title,
                    "rows": w.rows,
                    "cols": w.cols,
                    "follow_live": w.follow_live,
                    "link_x": w.link_x,
                    "open": w.open,
                    "cells": [
                        {
                            "segments": list(c.segments),
                            "plot_type": c.plot_type.value,
                            "xy_source": c.xy_source,
                            "xy_style": c.xy_style.value,
                            "y2": list(c.y2_segments),
                            "show_samples": c.show_samples,
                            "cursors": c.cursors,
                            "cursor_x": list(c.cursor_x) if c.cursor_x else None,
                            "spy": c.spy,
                            "spy_rect": list(c.spy_rect) if c.spy_rect else None,
                            "export_relative": c.export_relative,
                        }
                        for c in w.cells
                    ],
                }
                for w in self.windows
            ],
        }

    @classmethod
    def from_dict(cls, data: dict) -> "PlotWorkspace":
        result = cls()
        result.windows = []
        for raw in data.get("windows", []):
            window = PlotWindowState(
                int(raw.get("id", len(result.windows) + 1)),
                str(raw.get("title", f"Plot {len(result.windows) + 1}")),
            )
            window.set_grid(int(raw.get("rows", 1)), int(raw.get("cols", 1)))
            window.follow_live = bool(raw.get("follow_live", True))
            window.link_x = bool(raw.get("link_x", True))
            window.open = bool(raw.get("open", True))
            for cell, spec in zip(window.cells, raw.get("cells", [])):
                cell.segments = [int(v) for v in spec.get("segments", [])]
                try:
                    cell.plot_type = PlotType(spec.get("plot_type", "Line"))
                    cell.xy_style = XyStyle(spec.get("xy_style", "Line"))
                except ValueError:
                    pass
                cell.xy_source = spec.get("xy_source")
                cell.y2_segments = [int(v) for v in spec.get("y2", [])]
                cell.show_samples = bool(spec.get("show_samples", False))
                cell.cursors = bool(spec.get("cursors", False))
                cell.cursor_x = tuple(spec["cursor_x"]) if spec.get("cursor_x") else None
                cell.spy = bool(spec.get("spy", False))
                cell.spy_rect = tuple(spec["spy_rect"]) if spec.get("spy_rect") else None
                cell.export_relative = bool(spec.get("export_relative", False))
                cell.fit_pending = True
            result.windows.append(window)
        if not result.windows:
            result.windows = [PlotWindowState(1, "Plot 1")]
        result._next_id = max(
            int(data.get("next_id", 1 + max(w.id for w in result.windows))),
            1 + max(w.id for w in result.windows),
        )
        return result

