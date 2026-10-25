"""Headless render smoke tests for every plot type and the spy inset.

Drives a few real ImGui/ImPlot frames (no window) to make sure each cell mode
renders without raising -- the begin_plot/end_plot pairing, Spec markers,
histogram, XY and FFT paths, and the drag-rect spy inset.
"""

from __future__ import annotations


import numpy as np


from uz_dataviewer.panels.plots import PlotsPanel  # noqa: E402
from uz_dataviewer.state import PlotType  # noqa: E402


def _state(states):
    state = states()
    time = np.linspace(2.0, 6.0, 2000)
    state.registry.add_run(
        "Log.csv", "Log.csv", time,
        {"ia": np.sin(time).astype(np.float32), "ib": np.cos(time).astype(np.float32)},
        {"ia": "", "ib": ""},
    )
    return state


def _drive(state, gui_frame, frames=3):
    panel = PlotsPanel()
    for _ in range(frames):
        gui_frame(panel, state, 'Plots')


def test_render_every_plot_type(states, gui_frame):
    state = _state(states)
    state.set_grid(2, 2)
    types = [PlotType.LINE, PlotType.SCATTER, PlotType.STAIRS, PlotType.XY]
    for i, t in enumerate(types):
        state.cells[i].plot_type = t
        state.cells[i].add((1, "ia"))
        if t is PlotType.XY:
            state.cells[i].xy_source = (1, "ib")
    state.cells[0].show_samples = True  # exercise the Spec marker path
    _drive(state, gui_frame)  # must not raise


def test_render_xy_styles(states, gui_frame):
    from uz_dataviewer.state import XyStyle

    for style in XyStyle:
        state = _state(states)
        state.set_grid(1, 1)
        state.cells[0].plot_type = PlotType.XY
        state.cells[0].xy_source = (1, "ib")
        state.cells[0].add((1, "ia"))
        state.cells[0].xy_style = style
        _drive(state, gui_frame)  # markers / line / both must all render without raising


def test_render_spy_inset(states, gui_frame):
    state = _state(states)
    state.set_grid(1, 1)
    state.cells[0].add((1, "ia"))
    state.cells[0].spy = True
    _drive(state, gui_frame, frames=4)  # initialises spy_rect then renders the inset
    assert state.cells[0].spy_rect is not None


def test_render_cursors_and_secondary_axis(states, gui_frame):
    state = _state(states)
    state.set_grid(1, 1)
    state.cells[0].add((1, "ia"))
    state.cells[0].add((1, "ib"))
    state.cells[0].y2_signals = [(1, "ib")]  # ib on the right axis
    state.cells[0].cursors = True
    _drive(state, gui_frame, frames=4)  # initialises cursor_x then renders cursors + y2
    assert state.cells[0].cursor_x is not None


def _drive_window(panel, state, gui_frame, frames=4):
    import time
    deadline = time.monotonic() + 10
    rendered = 0
    while rendered < frames or getattr(panel, "_analysis_pending", None) is not None:
        assert time.monotonic() < deadline, "Background analysis did not finish"
        rendered += 1
        time.sleep(.002)
        gui_frame(panel, state)


def test_fft_window_renders_multiple_signals(states, gui_frame):
    from uz_dataviewer.panels.fft import FftPanel

    state = _state(states)
    state.commands.dispatch(state, "fft_source(Log.csv, ia)")
    state.commands.dispatch(state, "fft_source(Log.csv, ib)")
    panel = FftPanel()
    _drive_window(panel, state, gui_frame)
    assert len(panel._results) == 2  # one spectrum per source


def test_histogram_window_renders_multiple_signals(states, gui_frame):
    from uz_dataviewer.panels.histogram import HistogramPanel

    state = _state(states)
    state.commands.dispatch(state, "hist_source(Log.csv, ia)")
    state.commands.dispatch(state, "hist_source(Log.csv, ib)")
    panel = HistogramPanel()
    _drive_window(panel, state, gui_frame)
    assert len(panel._results) == 2  # one distribution per source


def test_histogram_skips_non_finite_samples(compute_panel, app_state):
    from uz_dataviewer.panels.histogram import HistogramPanel

    state = app_state
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


def test_analysis_window_computes_on_demand_not_every_frame(monkeypatch, states, gui_frame):
    """The FFT window computes only when asked (drag/compute), never per frame."""
    import uz_dataviewer.analysis as fft_mod
    from uz_dataviewer.panels.fft import FftPanel

    calls = {"n": 0}
    real = fft_mod.compute_fft

    def counting(*a, **k):
        calls["n"] += 1
        return real(*a, **k)

    monkeypatch.setattr(fft_mod, "compute_fft", counting)
    state = _state(states)
    state.commands.dispatch(state, "fft_source(Log.csv, ia)")  # sets compute_requested
    _drive_window(FftPanel(), state, gui_frame, frames=6)
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


def test_spy_uses_primary_axis_independent_of_trace_order(states, gui_frame, monkeypatch):
    from imgui_bundle import implot

    drawn = []
    original = PlotsPanel._render_spy_inset
    original_line = implot.plot_line

    def inset(panel, *args):
        def capture(label, *values):
            drawn.append(label)
            return original_line(label, *values)
        with monkeypatch.context() as patch:
            patch.setattr(implot, 'plot_line', capture)
            return original(panel, *args)

    monkeypatch.setattr(PlotsPanel, '_render_spy_inset', inset)
    for order in (('a', 'b'), ('b', 'a')):
        state = states()
        state.services.display.synchronous = True
        state.registry.add_run('r', 'r', np.arange(10.),
                               {'a': np.arange(10.), 'b': np.linspace(100, 200, 10)}, {})
        cell = state.cells[0]
        cell.signals = [(1, name) for name in order]
        cell.y2_signals = [(1, 'b')]
        cell.spy = True
        cell.set_limits('x', 0, 9)
        cell.set_limits('y', 0, 10)
        cell.set_limits('y2', 100, 200)
        panel = PlotsPanel()
        drawn.clear()
        gui_frame(panel, state, str(order))
        np.testing.assert_allclose(cell.spy_rect, (2.25, 2.5, 6.75, 7.5))
        assert drawn == [state.signal_label((1, 'a'))]


def test_xy_source_picker_chooses_compatible_domain(app_state, gui_frame):
    from uz_dataviewer import nodes
    s = app_state
    s.services.display.synchronous = True
    run = s.registry.add_run('time', 'time', np.arange(8.), {'a': np.ones(8)}, {})
    src, fft = s.nodes.add('source', ref=(run.id, 'a')), s.nodes.add('fft')
    s.nodes.link(src.id, fft.id)
    nodes.evaluate(s)
    s.commands.execute(s, 'add_signal', [1, fft.out_run_id, 'out'])
    s.commands.execute(s, 'set_plot_type', [1, 'xy'])
    panel = PlotsPanel()
    for _ in range(3):
        gui_frame(panel, s)
    assert s.cells[0].xy_source == (fft.out_run_id, 'out')
    assert not [entry for entry in s.console._entries if entry.level == 'ERROR']
