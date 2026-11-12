"""Regression tests for plot-panel range handling (no GUI window required).

Guards the bug where signals were not drawn over their time axis: the cell's
data extent must reflect the real (non-zero-based) time range, and out-of-range
or non-finite axis limits must not be used as a downsample window.
"""

from __future__ import annotations

import pytest
from uz_dataviewer import nodes, session
from uz_dataviewer.commands import CommandError


import numpy as np


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


def test_link_enable_syncs_driver(app_state, gui_frame):
    s = app_state
    s.services.display.synchronous = True
    s.registry.add_run("a", "a", np.arange(100.0), {"a": np.arange(100.0)}, {})
    s.set_grid(1, 2)
    for c in s.cells:
        c.add((1, "a"))
    panel = PlotsPanel()
    s.set_plot_x_limits(1, 10, 20)
    for _ in range(3):
        gui_frame(panel, s)
    panel._driver = 0
    s.commands.execute(s, "link_x", [False])
    s.set_plot_x_limits(1, 30, 40)
    for _ in range(3):
        gui_frame(panel, s)
    s.commands.execute(s, "link_x", [True])
    for _ in range(3):
        gui_frame(panel, s)
    assert s.cells[0].x_lim == s.cells[1].x_lim
    assert s.plot_time_range(1) == s.cells[0].x_lim


@pytest.mark.parametrize('target', [0, 1])
@pytest.mark.parametrize('axis_only', [False, True])
def test_linked_mouse_zoom_and_pan_keep_analysis_and_export_in_sync(
        app_state, gui_frame, tmp_path, target, axis_only):
    from imgui_bundle import imgui, implot
    state = app_state
    state.services.display.synchronous = True
    state.set_grid(2, 1)
    t = np.arange(1001.) / 100
    run = state.registry.add_run('run', '', t, {'a': np.sin(t)}, {})
    for cell in state.cells:
        cell.add((run.id, 'a'))
    state.set_plot_x_limits(1, 2., 8.)
    panel = PlotsPanel()
    geometry = {}
    def capture(state, index, cell, lo, hi):
        geometry[index] = (implot.get_plot_pos(), implot.get_plot_size())
    panel._time_series_input = capture
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1400, 1100)
    def frame():
        gui_frame(panel, state)
    for _ in range(3):
        frame()
    # Establish the other plot as driver, then move straight to the target axis.
    pos, size = geometry[1 - target]
    io.add_mouse_pos_event(pos.x + size.x * .5, pos.y + size.y * .5)
    frame()
    pos, size = geometry[target]
    x = pos.x + size.x * .5
    y = pos.y + size.y + 8 if axis_only else pos.y + size.y * .5
    io.add_mouse_pos_event(x, y)
    frame()
    io.add_mouse_wheel_event(0., 1.)
    frame()
    frame()  # Earlier cells adopt the later cell's changed range next frame.
    zoomed = state.cells[target].x_lim
    assert zoomed[1] - zoomed[0] < 6.
    assert state.cells[1 - target].x_lim == pytest.approx(zoomed)
    # Axis-only panning must also update the shared effective window.
    button = implot.get_input_map().pan
    io.add_mouse_button_event(button, True)
    frame()
    io.add_mouse_pos_event(x + 40, y)
    frame()
    io.add_mouse_button_event(button, False)
    frame()
    frame()
    window = state.cells[target].x_lim
    assert window != pytest.approx(zoomed)
    assert window[1] - window[0] == pytest.approx(zoomed[1] - zoomed[0])
    # Native box selection must survive the next shared-axis update as well.
    pos, size = geometry[target]
    io.add_mouse_pos_event(pos.x + size.x * .2, pos.y + size.y * .2)
    frame()
    io.add_mouse_button_event(implot.get_input_map().select, True)
    frame()
    io.add_mouse_pos_event(pos.x + size.x * .6, pos.y + size.y * .7)
    frame()
    io.add_mouse_button_event(implot.get_input_map().select, False)
    frame()
    frame()
    boxed = state.cells[target].x_lim
    assert boxed[1] - boxed[0] < window[1] - window[0]
    # EndPlot applies double-click fitting after get_plot_limits was captured.
    # That fitted range must not snap back on the following frame.
    for _ in range(30):
        frame()
    for down in (True, False, True):
        io.add_mouse_button_event(implot.get_input_map().fit, down)
        frame()
    window = state.cells[target].x_lim
    assert window != pytest.approx(boxed)
    io.add_mouse_button_event(implot.get_input_map().fit, False)
    frame()
    frame()
    for i, cell in enumerate(state.cells, 1):
        assert cell.x_lim == pytest.approx(window)
        assert state.plot_time_range(i) == pytest.approx(window)
        assert state.resolve_x_window(i, (0, 0), [(run.id, 'a')]) == pytest.approx(window)
    path = tmp_path / 'zoom.csv'
    session.export_data(state, target, str(path))
    actual = np.genfromtxt(path, delimiter=',', skip_header=1)[:, 0]
    np.testing.assert_allclose(actual, t[(t >= window[0]) & (t <= window[1])])


def test_frequency_outputs_keep_independent_axes(app_state, gui_frame, tmp_path):
    s = app_state
    s.services.display.synchronous = True
    t = np.arange(128.0) / 128
    run = s.registry.add_run("a", "a", t, {"a": np.sin(2 * np.pi * 8 * t)}, {})
    src = s.nodes.add("source", ref=(run.id, "a"))
    fft = s.nodes.add("fft")
    s.nodes.link(src.id, fft.id)
    assert nodes.evaluate(s) == 1
    spectrum = s.registry.get(fft.out_run_id)
    assert spectrum.axis_domain == "frequency"
    s.set_grid(1, 2)
    s.commands.execute(s, "add_signal", [1, run.id, "a"])
    s.commands.execute(s, "add_signal", [2, spectrum.id, "out"])
    s.set_plot_x_limits(1, 0.1, 0.5)
    s.set_plot_x_limits(2, 1, 40)
    assert s.shared_x == (0.1, 0.5)
    assert s.plot_time_range(2) == (1, 40)
    panel = PlotsPanel()
    for _ in range(3):
        gui_frame(panel, s)
    assert s.cells[1].x_lim == (1, 40)
    path = tmp_path / "spectrum.csv"
    session.export_data(s, 1, str(path))
    assert path.read_text().splitlines()[0] == "frequency,out"
    for command, args in [
        ("add_signal", [1, spectrum.id, "out"]),
        ("fft_source", [spectrum.id, "out"]),
        ("normalize_time", [spectrum.id, 0]),
        ("fft_follow", [2]),
    ]:
        with pytest.raises((ValueError, CommandError)):
            s.commands.execute(s, command, args)
    math = s.nodes.add("math")
    s.nodes.link(fft.id, math.id)
    assert nodes.evaluate(s) == 1
    assert s.registry.get(math.out_run_id).axis_domain == "frequency"
    filter_node = s.nodes.add("filter")
    s.nodes.link(fft.id, filter_node.id)
    assert nodes.evaluate(s) == 0
    assert "time-domain" in filter_node.error


@pytest.mark.parametrize('cols', [1, 2])
@pytest.mark.parametrize('font_scale', [1., 2.])
def test_subplot_popup_keeps_independent_controls(app_state, gui_frame, monkeypatch, cols, font_scale):
    """Right-click opens viewer controls alongside ImPlot's native menus."""
    from imgui_bundle import imgui, implot

    state = app_state
    state.set_grid(2, cols)
    panel = PlotsPanel()
    imgui.get_style().font_scale_main = font_scale
    geometry = {}
    controls = {}
    current = None
    original_controls = panel._cell_controls

    def capture_geometry(state, index, cell, lo, hi):
        geometry[index] = (implot.get_plot_pos(), implot.get_plot_size())

    def cell_controls(state, index, cell):
        nonlocal current
        current = index
        try:
            original_controls(state, index, cell)
        finally:
            current = None

    original_checkbox = imgui.checkbox
    def checkbox(label, *args):
        result = original_checkbox(label, *args)
        if current is not None:
            lo, hi = imgui.get_item_rect_min(), imgui.get_item_rect_max()
            controls[current, label] = ((lo.x + hi.x) / 2, (lo.y + hi.y) / 2)
        return result

    monkeypatch.setattr(panel, '_time_series_input', capture_geometry)
    monkeypatch.setattr(panel, '_cell_controls', cell_controls)
    monkeypatch.setattr(imgui, 'checkbox', checkbox)
    for _ in range(4):
        gui_frame(panel, state)
    assert len(geometry) == state.cell_count
    pos, size = geometry[0]
    io = imgui.get_io()
    io.add_mouse_pos_event(pos.x + size.x * .6, pos.y + size.y * .4)
    gui_frame(panel, state)
    io.add_mouse_button_event(implot.get_input_map().menu, True)
    gui_frame(panel, state)
    io.add_mouse_button_event(implot.get_input_map().menu, False)
    for _ in range(4):
        gui_frame(panel, state)
    assert (0, 'samples') in controls
    io.add_mouse_pos_event(*controls[0, 'samples'])
    gui_frame(panel, state)
    io.add_mouse_button_event(0, True)
    gui_frame(panel, state)
    io.add_mouse_button_event(0, False)
    gui_frame(panel, state)
    assert state.cells[0].show_samples
    assert not any(cell.show_samples for cell in state.cells[1:])


@pytest.mark.parametrize('axis', ['rows', 'columns'])
def test_native_subplot_splitters_resize_and_restore(app_state, gui_frame, monkeypatch, axis):
    from imgui_bundle import imgui, implot
    from uz_dataviewer.session import apply_dict, to_dict

    state = app_state
    state.set_grid(2, 2)
    panel = PlotsPanel()
    frames = {}
    def geometry(state, index, cell, lo, hi):
        rect = implot.internal.get_current_plot().frame_rect
        frames[index] = (rect.min.x, rect.min.y, rect.max.x, rect.max.y)
    monkeypatch.setattr(panel, '_time_series_input', geometry)
    for _ in range(4):
        gui_frame(panel, state)
    a = frames[0]
    if axis == 'rows':
        b = frames[2]
        x, y = (a[0] + a[2]) / 2, (a[3] + b[1]) / 2
        dx, dy = 0, 70
    else:
        b = frames[1]
        x, y = (a[2] + b[0]) / 2, (a[1] + a[3]) / 2
        dx, dy = 70, 0
    io = imgui.get_io()
    io.add_mouse_pos_event(x, y)
    for _ in range(6):
        gui_frame(panel, state)
    io.add_mouse_button_event(0, True)
    gui_frame(panel, state)
    io.add_mouse_pos_event(x + dx, y + dy)
    gui_frame(panel, state)
    io.add_mouse_button_event(0, False)
    gui_frame(panel, state)
    ratios = state.row_ratios if axis == 'rows' else state.col_ratios
    assert ratios[0] > .5
    assert sum(ratios) == pytest.approx(1.)
    saved = to_dict(state)
    apply_dict(state, saved)
    gui_frame(panel, state)
    assert state.row_ratios == pytest.approx(saved['row_ratios'])
    assert state.col_ratios == pytest.approx(saved['col_ratios'])


@pytest.mark.parametrize('rows,cols', [(1, 5), (5, 1), (5, 5)])
def test_native_grid_renders_every_cell_and_spy_stays_outside(app_state, gui_frame, monkeypatch, rows, cols):
    from imgui_bundle import implot
    state = app_state
    state.set_grid(rows, cols)
    panel = PlotsPanel()
    state.cells[0].spy = True
    seen = []
    def geometry(state, index, cell, lo, hi):
        seen.append(index)
        assert implot.get_plot_size().x > 0
        assert implot.get_plot_size().y > 0
    monkeypatch.setattr(panel, '_time_series_input', geometry)
    for _ in range(4):
        seen.clear()
        gui_frame(panel, state)
        assert seen == list(range(rows * cols))
    assert state.cells[0].spy_rect is not None


@pytest.mark.parametrize('linked', [False, True])
def test_toolbar_reset_fits_all_subplots(app_state, gui_frame, monkeypatch, linked):
    from imgui_bundle import imgui
    state = app_state
    state.set_grid(2, 1)
    state.link_x = linked
    for index, cell in enumerate(state.cells):
        t = np.arange(10.) + 10 * index
        y = np.arange(10.) + 100 * index
        run = state.registry.add_run(str(index), str(index), t, {'a': y}, {})
        cell.add((run.id, 'a'))
        cell.set_limits('x', 3, 4)
        cell.set_limits('y', 500, 600)
    state.shared_x = (3., 4.) if linked else None
    panel = PlotsPanel()
    button_pos = None
    original = imgui.button
    def button(label, *args, **kwargs):
        nonlocal button_pos
        clicked = original(label, *args, **kwargs)
        if label == 'Reset view':
            lo, hi = imgui.get_item_rect_min(), imgui.get_item_rect_max()
            button_pos = ((lo.x + hi.x) / 2, (lo.y + hi.y) / 2)
        return clicked
    monkeypatch.setattr(imgui, 'button', button)
    for _ in range(3):
        gui_frame(panel, state)
    assert all(cell.y_lim == (500., 600.) for cell in state.cells)
    io = imgui.get_io()
    io.add_mouse_pos_event(*button_pos)
    gui_frame(panel, state)
    io.add_mouse_button_event(0, True)
    gui_frame(panel, state)
    io.add_mouse_button_event(0, False)
    for _ in range(4):
        gui_frame(panel, state)
    for index, cell in enumerate(state.cells):
        assert cell.x_lim == pytest.approx((0, 19) if linked else (index * 10, index * 10 + 9))
        assert cell.y_lim[0] <= index * 100
        assert index * 100 + 9 <= cell.y_lim[1] < 500


@pytest.mark.parametrize('linked', [False, True])
@pytest.mark.parametrize('target', [0, 1])
def test_popup_reset_fits_x_without_old_frame_overwriting_it(app_state, gui_frame, monkeypatch, linked, target):
    from imgui_bundle import imgui, implot
    state = app_state
    state.set_grid(2, 1)
    state.link_x = linked
    for index, cell in enumerate(state.cells):
        t = np.arange(10.) + 10 * index
        run = state.registry.add_run(str(index), str(index), t, {'a': np.arange(10.)}, {})
        cell.add((run.id, 'a'))
        cell.set_limits('x', 3, 4)
        cell.set_limits('y', 500, 600)
    state.shared_x = (3., 4.) if linked else None
    panel = PlotsPanel()
    geometry = {}
    reset_pos = None
    def capture(state, index, cell, lo, hi):
        geometry[index] = (implot.get_plot_pos(), implot.get_plot_size())
    original = imgui.small_button
    def button(label):
        nonlocal reset_pos
        clicked = original(label)
        if label == 'Reset view':
            lo, hi = imgui.get_item_rect_min(), imgui.get_item_rect_max()
            reset_pos = ((lo.x + hi.x) / 2, (lo.y + hi.y) / 2)
        return clicked
    monkeypatch.setattr(panel, '_time_series_input', capture)
    monkeypatch.setattr(imgui, 'small_button', button)
    for _ in range(4):
        gui_frame(panel, state)
    pos, size = geometry[target]
    io = imgui.get_io()
    io.add_mouse_pos_event(pos.x + size.x * .6, pos.y + size.y * .4)
    gui_frame(panel, state)
    io.add_mouse_button_event(implot.get_input_map().menu, True)
    gui_frame(panel, state)
    io.add_mouse_button_event(implot.get_input_map().menu, False)
    for _ in range(4):
        gui_frame(panel, state)
    assert reset_pos is not None
    io.add_mouse_pos_event(*reset_pos)
    gui_frame(panel, state)
    io.add_mouse_button_event(0, True)
    gui_frame(panel, state)
    io.add_mouse_button_event(0, False)
    for _ in range(5):
        gui_frame(panel, state)
    expected = (0, 19) if linked else (target * 10, target * 10 + 9)
    assert state.cells[target].x_lim == pytest.approx(expected)
    assert state.plot_time_range(target + 1) == pytest.approx(expected)
    assert state.cells[target].y_lim[0] <= 0
    assert 9 <= state.cells[target].y_lim[1] < 500
    other = state.cells[1 - target]
    assert other.x_lim == pytest.approx(expected if linked else (3, 4))
    assert other.y_lim == (500., 600.)
