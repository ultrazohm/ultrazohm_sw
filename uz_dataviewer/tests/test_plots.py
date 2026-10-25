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


def test_plot_line_receives_matched_dtype_arrays(gui_frame):
    """ImPlot's PlotLine is templated on one type for xs and ys; a dtype
    mismatch makes it reinterpret a buffer as the wrong type, producing the
    scattered/negative-time corruption. Drive a real frame and assert the
    arrays handed to plot_line share a dtype and span the true time range.
    """
    from imgui_bundle import implot

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
            gui_frame(panel, state, 'Plots')
    finally:
        state.shutdown()
        implot.plot_line = original

    assert seen, "plot_line was never called"
    assert seen["xs_dtype"] == seen["ys_dtype"]
    assert seen["x_min"] >= 11.979 - 1e-6  # no negative/garbage times
    assert seen["monotonic"]


def test_restored_x_window_still_fits_delayed_y(app_state, gui_frame, tmp_path, monkeypatch):
    import threading
    import time
    from imgui_bundle import implot
    from uz_dataviewer.session import to_dict, apply_dict
    state = app_state
    path = tmp_path / 'high.csv'
    path.write_text('time;a\n' + ''.join(f'{i};{500+i}\n' for i in range(8)))
    state.load_sync(str(path))
    state.cells[0].signals = [(1, 'a')]
    state.plot_x_ranges[1] = (2., 4.)
    apply_dict(state, to_dict(state))
    panel = PlotsPanel()
    release, started = threading.Event(), threading.Event()
    source = state.registry.get(1).data_source()
    original_read = source.read_plot

    def delayed(*args, **kwargs):
        started.set()
        assert release.wait(5)
        return original_read(*args, **kwargs)

    monkeypatch.setattr(source, 'read_plot', delayed)
    limits = []
    original_end = implot.end_plot

    def capture():
        value = implot.get_plot_limits()
        limits.append((value.x.min, value.x.max, value.y.min, value.y.max))
        original_end()

    monkeypatch.setattr(implot, 'end_plot', capture)
    try:
        for _ in range(3):
            gui_frame(panel, state)
        assert started.wait(2)
        release.set()
        deadline = time.monotonic() + 5
        while time.monotonic() < deadline:
            gui_frame(panel, state)
            if limits and limits[-1][2] <= 502 and limits[-1][3] >= 504:
                break
            time.sleep(.01)
        assert limits[-1][:2] == (2., 4.)
        assert limits[-1][2] <= 502 and limits[-1][3] >= 504
    finally:
        release.set()


def test_linked_reset_updates_export_and_render(app_state, gui_frame, tmp_path):
    from uz_dataviewer.session import export_data, to_dict
    state = app_state
    state.backend = 'pyarrow'
    run = state.registry.add_run('test', 'test', np.arange(100.),
                                 {'a': np.arange(100, dtype=np.float32)}, {})
    state.set_grid(1, 2)
    for cell in state.cells:
        cell.add((run.id, 'a'))
    state.commands.execute(state, 'set_x_lim', [1, 20, 30])
    output = tmp_path / 'plot.csv'
    export_data(state, 1, str(output))
    data = np.genfromtxt(output, delimiter=',', skip_header=1)
    np.testing.assert_array_equal(data[:, 0], np.arange(20, 31))
    assert state.resolve_x_window(2, (0, 0), [(run.id, 'a')]) == (20, 30)
    assert to_dict(state)['cells'][1]['x_lim'] == (20, 30)
    panel = PlotsPanel()
    for _ in range(3):
        gui_frame(panel, state)
    panel._driver = 0
    state.commands.execute(state, 'reset_view', [2])
    assert state.plot_time_range(1) == (0, 99)
    for _ in range(3):
        gui_frame(panel, state)
    assert all(cell.x_lim == (0, 99) for cell in state.cells)
    state.commands.execute(state, 'link_x', [False])
    state.commands.execute(state, 'set_x_lim', [2, 40, 50])
    assert state.plot_time_range(1) == (0, 99)
    assert state.plot_time_range(2) == (40, 50)
