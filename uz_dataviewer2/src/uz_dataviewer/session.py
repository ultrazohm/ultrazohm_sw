"""Save / restore the GUI state, and export / replay it as a command script.

Two complementary formats, both exposed as commands (see :mod:`commands`):

* **JSON snapshot** (``save_state`` / ``load_state``) -- the exact view: grid,
  per-cell signal assignments, plot types, link/downsample settings, FFT/Histogram config
  and the set of loaded files. Restores to the same picture, including which
  files to reload.
* **Command script** (``export_script`` / ``run_script``) -- a human-readable,
  editable ``.uzscript`` of canonical commands (``load(...)``, ``set_grid(...)``,
  ``add_signal(...)`` ...) that reproduces the session when replayed.

Signals are referenced by ``(run_label, signal_name)`` rather than the volatile
integer run id, so assignments survive the reload that restore performs.
"""

from __future__ import annotations

import json
from typing import TYPE_CHECKING

from .downsample import visible_slice
from .state import PlotType

if TYPE_CHECKING:  # pragma: no cover - typing only
    from .state import AppState, SubplotCell

SCHEMA_VERSION = 1


# -- helpers ------------------------------------------------------------------
def _ref_to_labelled(state: "AppState", ref) -> list | None:
    """``(run_id, name)`` -> ``[run_label, name]`` (or ``None``)."""
    if ref is None:
        return None
    run = state.registry.get(ref[0])
    if run is None:
        return None
    return [run.label, ref[1]]


def _label_to_run_id(state: "AppState", label: str) -> int | None:
    for run in state.registry.runs:
        if run.label == label:
            return run.id
    return None


# -- JSON snapshot ------------------------------------------------------------
def to_dict(state: "AppState") -> dict:
    cells = []
    for cell in state.cells:
        cells.append(
            {
                "signals": [_ref_to_labelled(state, r) for r in cell.signals],
                "type": cell.plot_type.value,
                "show_samples": cell.show_samples,
                "spy": cell.spy,
                "spy_rect": list(cell.spy_rect) if cell.spy_rect else None,
                "cursors": cell.cursors,
                "cursor_x": list(cell.cursor_x) if cell.cursor_x else None,
                "export_relative": cell.export_relative,
                "xy_source": _ref_to_labelled(state, cell.xy_source),
                "y2": [_ref_to_labelled(state, r) for r in cell.y2_signals],
            }
        )
    return {
        "version": SCHEMA_VERSION,
        "grid": [state.rows, state.cols],
        "link_x": state.link_x,
        "max_points": state.max_points,
        "files": [run.path for run in state.registry.runs],
        "time_origins": {
            run.label: run.time_origin
            for run in state.registry.runs
            if run.time_origin is not None
        },
        "cells": cells,
        "fft": {
            "sources": [_ref_to_labelled(state, r) for r in state.fft.sources],
            "follow_plot": state.fft.follow_plot,
            "x_min": state.fft.x_min,
            "x_max": state.fft.x_max,
            "remove_dc": state.fft.remove_dc,
            "window": state.fft.window,
            "log_x": state.fft.log_x,
            "log_y": state.fft.log_y,
        },
        "histogram": {
            "sources": [_ref_to_labelled(state, r) for r in state.histogram.sources],
            "follow_plot": state.histogram.follow_plot,
            "x_min": state.histogram.x_min,
            "x_max": state.histogram.x_max,
            "bins": state.histogram.bins,
        },
    }


def save_state(state: "AppState", path: str) -> None:
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(to_dict(state), fh, indent=2)


def load_state(state: "AppState", path: str) -> None:
    with open(path, encoding="utf-8") as fh:
        data = json.load(fh)
    apply_dict(state, data)


def apply_dict(state: "AppState", data: dict) -> None:
    # Reload any files referenced by the snapshot that are not already present.
    have = {run.label for run in state.registry.runs}
    for file_path in data.get("files", []):
        label = file_path.rsplit("/", 1)[-1].rsplit("\\", 1)[-1]
        if label not in have:
            state.load_sync(file_path)
            have.add(label)

    # Re-apply per-log time normalisation.
    origins = data.get("time_origins", {})
    for run in state.registry.runs:
        if run.label in origins and origins[run.label] is not None:
            run.set_time_origin(float(origins[run.label]))

    rows, cols = data.get("grid", [state.rows, state.cols])
    state.set_grid(int(rows), int(cols))
    state.link_x = bool(data.get("link_x", state.link_x))
    state.max_points = int(data.get("max_points", state.max_points))

    def _resolve(labelled) -> tuple[int, str] | None:
        if not labelled:
            return None
        run_id = _label_to_run_id(state, labelled[0])
        return None if run_id is None else (run_id, labelled[1])

    for i, spec in enumerate(data.get("cells", [])):
        if i >= len(state.cells):
            break
        cell = state.cells[i]
        cell.signals = [r for r in (_resolve(s) for s in spec.get("signals", [])) if r is not None]
        try:
            cell.plot_type = PlotType(spec.get("type", PlotType.LINE.value))
        except ValueError:
            cell.plot_type = PlotType.LINE
        cell.show_samples = bool(spec.get("show_samples", False))
        cell.spy = bool(spec.get("spy", False))
        cell.spy_rect = tuple(spec["spy_rect"]) if spec.get("spy_rect") else None
        cell.cursors = bool(spec.get("cursors", False))
        cell.cursor_x = tuple(spec["cursor_x"]) if spec.get("cursor_x") else None
        cell.export_relative = bool(spec.get("export_relative", False))
        cell.xy_source = _resolve(spec.get("xy_source"))
        cell.y2_signals = [r for r in (_resolve(s) for s in spec.get("y2", [])) if r is not None]
        cell.fit_pending = True

    fft = data.get("fft") or {}
    state.fft.sources = [r for r in (_resolve(s) for s in fft.get("sources", [])) if r is not None]
    state.fft.follow_plot = int(fft.get("follow_plot", state.fft.follow_plot))
    state.fft.x_min = float(fft.get("x_min", state.fft.x_min))
    state.fft.x_max = float(fft.get("x_max", state.fft.x_max))
    state.fft.remove_dc = bool(fft.get("remove_dc", state.fft.remove_dc))
    state.fft.window = bool(fft.get("window", state.fft.window))
    state.fft.log_x = bool(fft.get("log_x", state.fft.log_x))
    state.fft.log_y = bool(fft.get("log_y", state.fft.log_y))

    hist = data.get("histogram") or {}
    state.histogram.sources = [r for r in (_resolve(s) for s in hist.get("sources", [])) if r is not None]
    state.histogram.follow_plot = int(hist.get("follow_plot", state.histogram.follow_plot))
    state.histogram.x_min = float(hist.get("x_min", state.histogram.x_min))
    state.histogram.x_max = float(hist.get("x_max", state.histogram.x_max))
    state.histogram.bins = int(hist.get("bins", state.histogram.bins))


# -- command script -----------------------------------------------------------
def _arg(token: str) -> str:
    from .commands import _fmt_str

    return _fmt_str(token)


def to_script(state: "AppState") -> list[str]:
    lines: list[str] = ["# UltraZohm Data Viewer session script"]
    for run in state.registry.runs:
        if run.time_origin is not None:
            lines.append(f"load({_arg(run.path)}, {run.time_origin:.6g})")
        else:
            lines.append(f"load({_arg(run.path)})")
    lines.append(f"set_grid({state.rows}, {state.cols})")
    lines.append(f"set_max_points({state.max_points})")
    lines.append(f"link_x({'true' if state.link_x else 'false'})")

    for i, cell in enumerate(state.cells, start=1):
        if cell.plot_type is not PlotType.LINE:
            lines.append(f"set_plot_type(plot_{i}, {cell.plot_type.value})")
        for ref in cell.signals:
            labelled = _ref_to_labelled(state, ref)
            if labelled:
                lines.append(f"add_signal(plot_{i}, {_arg(labelled[0])}, {_arg(labelled[1])})")
        if cell.xy_source is not None:
            labelled = _ref_to_labelled(state, cell.xy_source)
            if labelled:
                lines.append(f"set_xy(plot_{i}, {_arg(labelled[0])}, {_arg(labelled[1])})")
        for ref in cell.y2_signals:
            labelled = _ref_to_labelled(state, ref)
            if labelled:
                lines.append(f"set_axis(plot_{i}, {_arg(labelled[0])}, {_arg(labelled[1])}, right)")
        if cell.show_samples:
            lines.append(f"show_samples(plot_{i}, true)")
        if cell.spy:
            if cell.spy_rect:
                x1, y1, x2, y2 = cell.spy_rect
                lines.append(f"set_spy_rect(plot_{i}, {x1:.6g}, {y1:.6g}, {x2:.6g}, {y2:.6g})")
            else:
                lines.append(f"spy(plot_{i}, true)")
        if cell.cursors:
            if cell.cursor_x:
                lines.append(f"set_cursors(plot_{i}, {cell.cursor_x[0]:.6g}, {cell.cursor_x[1]:.6g})")
            else:
                lines.append(f"cursors(plot_{i}, true)")

    for ref in state.fft.sources:
        labelled = _ref_to_labelled(state, ref)
        if labelled:
            lines.append(f"fft_source({_arg(labelled[0])}, {_arg(labelled[1])})")
    for ref in state.histogram.sources:
        labelled = _ref_to_labelled(state, ref)
        if labelled:
            lines.append(f"hist_source({_arg(labelled[0])}, {_arg(labelled[1])})")
    return lines


def export_script(state: "AppState", path: str) -> None:
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("\n".join(to_script(state)) + "\n")


def run_script(state: "AppState", path: str) -> int:
    """Replay a script file line by line; returns the number of commands run."""
    with open(path, encoding="utf-8") as fh:
        lines = fh.readlines()
    count = 0
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        state.commands.dispatch(state, line)
        count += 1
    return count


# -- data export --------------------------------------------------------------
def export_data(state: "AppState", plot_index: int, path: str, relative: bool = False) -> int:
    """Write a subplot's signals to a wide CSV (``time`` + one column per signal).

    Exports the currently visible time window (the linked range when set, else the
    full extent). ``relative`` rebases the time column to start at 0 -- the legacy
    viewer's "start time at 0" option. Signals whose run differs from the first
    signal's (different time base) are skipped with a warning.
    """
    import pandas as pd

    if not 0 <= plot_index < len(state.cells):
        raise ValueError(f"plot_{plot_index + 1} out of range")
    cell = state.cells[plot_index]
    if not cell.signals:
        raise ValueError(f"plot_{plot_index + 1} has no signals to export")

    run0 = state.registry.get(cell.signals[0][0])
    if run0 is None:
        raise ValueError("source run is not loaded")
    time = run0.time

    # Use *this* subplot's own visible X range (not the global linked range), so
    # it is unambiguous which plot you are exporting. Fall back to the full extent.
    own = state.plot_x_ranges.get(plot_index + 1)
    if own is not None:
        x_min = max(own[0], float(time[0]))
        x_max = min(own[1], float(time[-1]))
        if x_max <= x_min:
            x_min, x_max = float(time[0]), float(time[-1])
    else:
        x_min, x_max = float(time[0]), float(time[-1])

    start, stop = visible_slice(time, x_min, x_max)
    t = time[start:stop]
    columns = {"time": (t - t[0]) if relative else t}
    for ref in cell.signals:
        if ref[0] != run0.id:
            state.console.warn(f"export: skipped {state.signal_label(ref)} (different time base)")
            continue
        signal = state.registry.get_signal(ref[0], ref[1])
        if signal is not None:
            # Use the plain channel name (e.g. "ia"), as in the source log -- not
            # the "ia @ Log.csv" display label.
            columns[ref[1]] = signal.y[start:stop]

    pd.DataFrame(columns).to_csv(path, index=False)
    return len(columns)


def export_fft(state: "AppState", path: str) -> int:
    """Write the FFT window's spectra to a wide CSV: ``frequency`` + one amplitude
    column per signal (named by the plain channel name)."""
    import numpy as np
    import pandas as pd

    from .analysis import compute_fft

    cfg = state.fft
    if not cfg.sources:
        raise ValueError("FFT window has no signals")
    x_min, x_max = state.resolve_x_window(cfg.follow_plot, (cfg.x_min, cfg.x_max), cfg.sources)

    columns: dict[str, np.ndarray] = {}
    for ref in cfg.sources:
        run = state.registry.get(ref[0])
        signal = state.registry.get_signal(ref[0], ref[1])
        if run is None or signal is None:
            continue
        result = compute_fft(run.time, signal.y, x_min, x_max, remove_dc=cfg.remove_dc, window=cfg.window)
        if not result.ok:
            continue
        if "frequency" not in columns:
            columns["frequency"] = result.freqs
        columns[ref[1]] = result.mag
    if "frequency" not in columns:
        raise ValueError("no spectra to export")
    # Align all columns to the shortest (spectra share the window, so equal in
    # the common single-run case; trim defensively for mixed sample rates).
    m = min(len(v) for v in columns.values())
    pd.DataFrame({k: v[:m] for k, v in columns.items()}).to_csv(path, index=False)
    return len(columns)


def export_histogram(state: "AppState", path: str) -> int:
    """Write the Histogram window's bins to a wide CSV: ``bin_center`` + one count
    column per signal, computed over a shared value range so columns align."""
    import numpy as np
    import pandas as pd

    cfg = state.histogram
    if not cfg.sources:
        raise ValueError("Histogram window has no signals")
    x_min, x_max = state.resolve_x_window(cfg.follow_plot, (cfg.x_min, cfg.x_max), cfg.sources)

    series: dict[str, np.ndarray] = {}
    lo = hi = None
    for ref in cfg.sources:
        run = state.registry.get(ref[0])
        signal = state.registry.get_signal(ref[0], ref[1])
        if run is None or signal is None:
            continue
        start, stop = visible_slice(run.time, x_min, x_max)
        values = signal.y[start:stop].astype(np.float64)
        if values.size == 0:
            continue
        series[ref[1]] = values
        lo = float(values.min()) if lo is None else min(lo, float(values.min()))
        hi = float(values.max()) if hi is None else max(hi, float(values.max()))
    if not series:
        raise ValueError("no data to export")
    if hi <= lo:
        hi = lo + 1.0
    bins = max(1, cfg.bins)
    edges = np.linspace(lo, hi, bins + 1)
    columns: dict[str, np.ndarray] = {"bin_center": (edges[:-1] + edges[1:]) / 2.0}
    for name, values in series.items():
        columns[name], _ = np.histogram(values, bins=edges)
    pd.DataFrame(columns).to_csv(path, index=False)
    return len(columns)
