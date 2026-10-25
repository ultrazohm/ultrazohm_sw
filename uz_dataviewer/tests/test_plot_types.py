"""Headless render smoke tests for every plot type and the spy inset.

Drives a few real ImGui/ImPlot frames (no window) to make sure each cell mode
renders without raising -- the begin_plot/end_plot pairing, Spec markers,
histogram, XY and FFT paths, and the drag-rect spy inset.
"""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.panels.plots import PlotsPanel  # noqa: E402
from uz_dataviewer.state import AppState, PlotType  # noqa: E402


def _state():
    state = AppState()
    time = np.linspace(2.0, 6.0, 2000)
    state.registry.add_run(
        "Log.csv", "Log.csv", time,
        {"ia": np.sin(time).astype(np.float32), "ib": np.cos(time).astype(np.float32)},
        {"ia": "", "ib": ""},
    )
    return state


def _drive(state, frames=3):
    from imgui_bundle import imgui, implot

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1400, 900)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures

    panel = PlotsPanel()
    try:
        for _ in range(frames):
            imgui.new_frame()
            imgui.begin("Plots")
            panel.render(state)
            imgui.end()
            imgui.render()
    finally:
        implot.destroy_context()
        imgui.destroy_context()


def test_render_every_plot_type():
    state = _state()
    state.set_grid(2, 2)
    types = [PlotType.LINE, PlotType.SCATTER, PlotType.STAIRS, PlotType.XY]
    for i, t in enumerate(types):
        state.cells[i].plot_type = t
        state.cells[i].add((1, "ia"))
        if t is PlotType.XY:
            state.cells[i].xy_source = (1, "ib")
    state.cells[0].show_samples = True  # exercise the Spec marker path
    _drive(state)  # must not raise


def test_render_xy_styles():
    from uz_dataviewer.state import XyStyle

    for style in XyStyle:
        state = _state()
        state.set_grid(1, 1)
        state.cells[0].plot_type = PlotType.XY
        state.cells[0].xy_source = (1, "ib")
        state.cells[0].add((1, "ia"))
        state.cells[0].xy_style = style
        _drive(state)  # markers / line / both must all render without raising


def test_render_spy_inset():
    state = _state()
    state.set_grid(1, 1)
    state.cells[0].add((1, "ia"))
    state.cells[0].spy = True
    _drive(state, frames=4)  # initialises spy_rect then renders the inset
    assert state.cells[0].spy_rect is not None


def test_render_cursors_and_secondary_axis():
    state = _state()
    state.set_grid(1, 1)
    state.cells[0].add((1, "ia"))
    state.cells[0].add((1, "ib"))
    state.cells[0].y2_signals = [(1, "ib")]  # ib on the right axis
    state.cells[0].cursors = True
    _drive(state, frames=4)  # initialises cursor_x then renders cursors + y2
    assert state.cells[0].cursor_x is not None


def _drive_window(panel, state, frames=4):
    from imgui_bundle import imgui, implot

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1000, 700)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    try:
        import time
        deadline = time.monotonic() + 10
        rendered = 0
        while rendered < frames or getattr(panel, "_analysis_pending", None) is not None:
            assert time.monotonic() < deadline, "Background analysis did not finish"
            rendered += 1
            time.sleep(.002)
            imgui.new_frame()
            imgui.begin("W")
            panel.render(state)
            imgui.end()
            imgui.render()
    finally:
        implot.destroy_context()
        imgui.destroy_context()


def test_fft_window_renders_multiple_signals():
    from uz_dataviewer.panels.fft import FftPanel

    state = _state()
    state.commands.dispatch(state, "fft_source(Log.csv, ia)")
    state.commands.dispatch(state, "fft_source(Log.csv, ib)")
    panel = FftPanel()
    _drive_window(panel, state)
    assert len(panel._results) == 2  # one spectrum per source


def test_histogram_window_renders_multiple_signals():
    from uz_dataviewer.panels.histogram import HistogramPanel

    state = _state()
    state.commands.dispatch(state, "hist_source(Log.csv, ia)")
    state.commands.dispatch(state, "hist_source(Log.csv, ib)")
    panel = HistogramPanel()
    _drive_window(panel, state)
    assert len(panel._results) == 2  # one distribution per source


def test_histogram_skips_non_finite_samples(compute_panel):
    from uz_dataviewer.panels.histogram import HistogramPanel

    state = AppState()
    t = np.linspace(0.0, 1.0, 6)
    y = np.array([0.0, 1.0, np.nan, 2.0, np.inf, 3.0], dtype=np.float32)
    state.registry.add_run("L.csv", "L.csv", t, {"s": y}, {"s": ""})
    state.histogram.sources = [(1, "s")]
    panel = HistogramPanel()
    compute_panel(panel, state, state.histogram, float(t[0]), float(t[-1]))
    assert len(panel._results) == 1
    _, centers, counts, _ = panel._results[0]
    assert np.isfinite(centers).all()  # NaN/Inf did not poison the bin edges
    assert counts.sum() == 4            # only the 4 finite samples binned
    assert "non-finite skipped" in panel._info


def test_analysis_window_computes_on_demand_not_every_frame(monkeypatch):
    """The FFT window computes only when asked (drag/compute), never per frame."""
    import uz_dataviewer.analysis as fft_mod
    from uz_dataviewer.panels.fft import FftPanel

    calls = {"n": 0}
    real = fft_mod.compute_fft

    def counting(*a, **k):
        calls["n"] += 1
        return real(*a, **k)

    monkeypatch.setattr(fft_mod, "compute_fft", counting)
    state = _state()
    state.commands.dispatch(state, "fft_source(Log.csv, ia)")  # sets compute_requested
    _drive_window(FftPanel(), state, frames=6)
    assert calls["n"] == 1  # computed once for the one source, not 6x


def test_xy_rejects_changed_files_and_reads_lazy_data_off_thread(app_state, gui_frame, tmp_path, monkeypatch):
    import threading
    import time
    from imgui_bundle import implot
    state = app_state
    state.backend, state.loading_mode = 'pyarrow', 'lazy'
    path = tmp_path / 'xy.csv'

    def write(offset):
        path.write_text('time;a;b\n' + ''.join(f'{i};{i};{i+offset}\n' for i in range(8)))

    write(10)
    run = state.load_sync(str(path))
    cell = state.cells[0]
    cell.plot_type, cell.xy_source, cell.signals = PlotType.XY, (run.id, 'a'), [(run.id, 'b')]
    source = run.data_source()
    threads, drawn = [], []
    original_read, original_line = source.iter_raw, implot.plot_line

    def read(*args, **kwargs):
        threads.append(threading.current_thread())
        yield from original_read(*args, **kwargs)

    def line(label, x, y, *args):
        drawn.append(float(y[0]))
        original_line(label, x, y, *args)

    monkeypatch.setattr(source, 'iter_raw', read)
    monkeypatch.setattr(implot, 'plot_line', line)
    panel = PlotsPanel()
    deadline = time.monotonic() + 5
    while not drawn and time.monotonic() < deadline:
        gui_frame(panel, state)
        time.sleep(.01)
    assert drawn and drawn[-1] == 10
    assert threads and all(thread is not threading.main_thread() for thread in threads)
    write(20)
    drawn.clear()
    for _ in range(3):
        gui_frame(panel, state)
    assert not drawn
    assert any('Source changed' in entry.message for entry in state.console._entries)
    assert not state.services.display.results  # no reusable stale XY data remains


def test_xy_surfaces_read_errors_without_drawing_stale_data(app_state, gui_frame, tmp_path, monkeypatch):
    import time
    from imgui_bundle import implot
    state = app_state
    state.backend, state.loading_mode = 'pyarrow', 'lazy'
    path = tmp_path / 'xy.csv'
    path.write_text('time;a;b\n' + ''.join(f'{i};{i};{i+10}\n' for i in range(8)))
    run = state.load_sync(str(path))
    cell = state.cells[0]
    cell.plot_type, cell.xy_source, cell.signals = PlotType.XY, (run.id, 'a'), [(run.id, 'b')]
    panel = PlotsPanel()
    drawn = []
    original = implot.plot_line

    def line(label, x, y, *args):
        drawn.append(label)
        original(label, x, y, *args)

    monkeypatch.setattr(implot, 'plot_line', line)
    deadline = time.monotonic() + 5
    while not drawn and time.monotonic() < deadline:
        gui_frame(panel, state)
        time.sleep(.01)
    assert drawn

    def broken(*args, **kwargs):
        raise OSError('test read failure')

    monkeypatch.setattr(run.data_source(), 'iter_raw', broken)
    state.max_points = 2  # new stride requests fresh data
    deadline = time.monotonic() + 5
    while not state.services.display.errors and time.monotonic() < deadline:
        gui_frame(panel, state)
        time.sleep(.01)
    assert state.services.display.errors
    drawn.clear()
    for _ in range(3):
        gui_frame(panel, state)
    assert not drawn
    assert any('test read failure' in entry.message for entry in state.console._entries)
