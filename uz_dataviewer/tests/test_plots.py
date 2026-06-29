"""Regression tests for plot-panel range handling (no GUI window required).

Guards the bug where signals were not drawn over their time axis: the cell's
data extent must reflect the real (non-zero-based) time range, and out-of-range
or non-finite axis limits must not be used as a downsample window.
"""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.downsample import visible_slice  # noqa: E402
from uz_dataviewer.model import DataRegistry  # noqa: E402
from uz_dataviewer.panels.plots import PlotsPanel, _is_finite_range  # noqa: E402
from uz_dataviewer.state import AppState, SubplotCell  # noqa: E402


def _registry_with_run(t_start: float):
    state = AppState()
    time = np.linspace(t_start, t_start + 4.0, 1000)
    signals = {"theta": np.sin(time).astype(np.float32)}
    run = state.registry.add_run("Log.csv", "Log.csv", time, signals, {"theta": ""})
    return state, run


def test_cell_extent_reflects_real_time_range():
    state, run = _registry_with_run(t_start=11.979)
    cell = SubplotCell()
    cell.add((run.id, "theta"))
    lo, hi = PlotsPanel()._cell_x_extent(state, cell)
    assert lo == 11.979
    assert abs(hi - 15.979) < 1e-6


def test_cell_extent_empty_for_no_signals():
    state = AppState()
    assert PlotsPanel()._cell_x_extent(state, SubplotCell()) == (None, None)


def test_is_finite_range_rejects_default_and_garbage():
    assert not _is_finite_range(0.0, 0.0)
    assert not _is_finite_range(1.0, 0.0)
    assert not _is_finite_range(0.0, float("inf"))
    assert _is_finite_range(11.979, 16.084)


def test_default_limits_window_yields_no_overlap():
    # Reproduces the broken state: ImPlot's default (0, 1) window does not
    # overlap a log whose time starts at ~12 s -> empty slice. The panel must
    # therefore fall back to the data extent (covered by the extent test above).
    state, run = _registry_with_run(t_start=11.979)
    start, stop = visible_slice(run.time, 0.0, 1.0)
    assert stop - start <= 1  # nothing meaningful in the default window

    start, stop = visible_slice(run.time, 11.979, 15.979)
    assert stop - start > 100  # full extent renders correctly


def test_add_sets_fit_pending():
    cell = SubplotCell()
    cell.fit_pending = False
    cell.add((1, "theta"))
    assert cell.fit_pending is True


def test_plot_line_receives_matched_dtype_arrays():
    """ImPlot's PlotLine is templated on one type for xs and ys; a dtype
    mismatch makes it reinterpret a buffer as the wrong type, producing the
    scattered/negative-time corruption. Drive a real frame and assert the
    arrays handed to plot_line share a dtype and span the true time range.
    """
    from imgui_bundle import imgui, implot

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1200, 800)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures

    state, run = _registry_with_run(t_start=11.979)
    panel = PlotsPanel()
    state.cells[0].add((run.id, "theta"))
    state.set_grid(1, 1)

    seen = {}
    original = implot.plot_line

    def capture(label, xs, ys, *a, **k):
        seen["xs_dtype"] = xs.dtype
        seen["ys_dtype"] = ys.dtype
        seen["x_min"] = float(xs.min())
        seen["monotonic"] = bool(np.all(np.diff(xs) >= 0))
        return original(label, xs, ys, *a, **k)

    implot.plot_line = capture
    try:
        for _ in range(3):  # first frame's begin_plot returns False
            imgui.new_frame()
            imgui.begin("Plots")
            panel.render(state)
            imgui.end()
            imgui.render()
    finally:
        implot.plot_line = original

    assert seen, "plot_line was never called"
    assert seen["xs_dtype"] == seen["ys_dtype"]
    assert seen["x_min"] >= 11.979 - 1e-6  # no negative/garbage times
    assert seen["monotonic"]
