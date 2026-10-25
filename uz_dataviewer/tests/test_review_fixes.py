"""Regressions for session validation, mouse views, and evicted FFT displays."""
import copy
import subprocess
import sys
import threading
import time

import numpy as np
import pytest

from uz_dataviewer.panels.fft import FftPanel
from uz_dataviewer.panels.histogram import HistogramPanel
from uz_dataviewer.panels.plots import PlotsPanel
from uz_dataviewer.requests import Requests
from uz_dataviewer.session import apply_dict, to_dict
from uz_dataviewer.sources import ArraySource


@pytest.mark.parametrize('field,value', [
    ('cursor_x', [1]), ('cursor_x', [0, float('nan')]),
    ('spy_rect', [0, 1]), ('spy_rect', [2, 0, 1, 1]),
    ('type', 'obsolete'), ('xy_style', 'obsolete'), ('cursors', 'false'),
])
def test_bad_session_view_preserves_current_session(app_state, gui_frame, field, value):
    data = to_dict(app_state)
    data['cells'][0][field] = value
    token, cell = app_state.session_token, app_state.cells[0]
    with pytest.raises(ValueError):
        apply_dict(app_state, data)
    assert app_state.session_token is token
    assert app_state.cells[0] is cell
    gui_frame(PlotsPanel(), app_state)


@pytest.mark.parametrize('value', [0, -1, 100001, 2147483648, float('inf'), 1.5])
def test_histogram_bounds_reject_before_mutation(app_state, gui_frame, value):
    previous = app_state.histogram.bins
    with pytest.raises((ValueError, OverflowError)):
        app_state.commands.execute(app_state, 'hist_bins', [value])
    assert app_state.histogram.bins == previous
    data = to_dict(app_state)
    data['histogram']['bins'] = value
    token = app_state.session_token
    with pytest.raises(ValueError):
        apply_dict(app_state, data)
    assert app_state.session_token is token
    gui_frame(HistogramPanel(), app_state)


@pytest.mark.parametrize('command,args', [
    ('set_grid', [0, 1]), ('set_grid', [1000000, 1]),
    ('set_max_points', [2147483648]), ('cache_budget', [2147483648]),
    ('set_cursors', [1, float('inf'), 1]),
    ('set_spy_rect', [1, 2, 0, 1, 1]),
])
def test_invalid_command_is_atomic(app_state, command, args):
    before = copy.deepcopy(to_dict(app_state))
    with pytest.raises(ValueError):
        app_state.commands.execute(app_state, command, args)
    assert to_dict(app_state) == before


@pytest.mark.parametrize('panel_type,field', [(FftPanel, 'fft'), (HistogramPanel, 'histogram')])
def test_mouse_zoom_saved_and_preserved_on_compute(app_state, gui_frame, monkeypatch, recording_csv,
                                                  panel_type, field):
    from imgui_bundle import implot
    state = app_state
    state.load_sync(str(recording_csv))
    state.analysis_jobs.close()
    state.analysis_jobs = Requests(synchronous=True)
    state.analysis_displays['fft'].close()
    state.analysis_displays['fft'] = Requests(synchronous=True)
    panel = panel_type()
    cfg = panel.config(state)
    cfg.sources = [(1, 'a')]
    cfg.follow_plot = -1
    cfg.compute_requested = True
    for _ in range(4):
        gui_frame(panel, state)
    # Exercise the render path for a settled mouse gesture, not a limit command.
    panel._last_logged_x = (0., 10.)
    monkeypatch.setattr(implot, 'is_plot_hovered', lambda: True)
    class Axis:
        min, max = 2., 5.
    class Limits:
        x = Axis()
    monkeypatch.setattr(implot, 'get_plot_limits', lambda: Limits())
    gui_frame(panel, state)
    assert cfg.x_lim == (2., 5.)
    assert cfg.pending_x_lim is None
    saved = to_dict(state)
    assert saved[field]['x_lim'] == (2., 5.)
    cfg.compute_requested = True
    gui_frame(panel, state)
    assert cfg.x_lim == (2., 5.)
    apply_dict(state, saved)
    assert panel.config(state).x_lim == (2., 5.)


def test_evicted_fft_summary_rebuilds_in_worker(app_state, gui_frame, monkeypatch):
    state = app_state
    t = np.arange(262144.) / 1000
    state.registry.add_run('test', 'test', t, {'y': np.sin(t)}, {})
    state.fft.sources = [(1, 'y')]
    state.fft.follow_plot = -1
    state.max_points = 100
    panel = FftPanel()
    panel._compute(state, state.fft, t[0], t[-1])
    state.registry.cache.clear()  # Equivalent to eviction by another trace.
    started, release = threading.Event(), threading.Event()
    threads = []
    original = ArraySource._base_summary
    def blocked_summary(self, *args):
        threads.append(threading.current_thread())
        started.set()
        assert release.wait(5)
        return original(self, *args)
    monkeypatch.setattr(ArraySource, '_base_summary', blocked_summary)
    try:
        gui_frame(panel, state)
        assert started.wait(2)
        assert threads and all(t is not threading.main_thread() for t in threads)
        assert panel._fit_pending  # Fit once asynchronously prepared data arrives.
        # Rendering the other analysis panel must not cancel FFT display requests.
        gui_frame(HistogramPanel(), state, 'Histogram')
        assert state.analysis_displays['fft'].pending
        release.set()
        deadline = time.monotonic() + 3
        while state.analysis_displays['fft'].pending and time.monotonic() < deadline:
            time.sleep(.005)
        gui_frame(panel, state)
        assert not panel._fit_pending
        assert state.analysis_displays['fft'].results
    finally:
        release.set()


def test_headless_operations_do_not_import_gui(recording_csv):
    code = '''
import sys
import uz_dataviewer as uz
from uz_dataviewer.loader import convert_csv_to_parquet
for backend in ('pyarrow', 'polars'):
    data = uz.read(sys.argv[1], backend=backend)
    data.to_dataframe()
    uz.fft_frame(data.time, data['a'], backend=backend)
convert_csv_to_parquet(sys.argv[1])
assert 'imgui_bundle' not in sys.modules
assert 'uz_dataviewer.webbridge' not in sys.modules
'''
    result = subprocess.run([sys.executable, '-c', code, str(recording_csv)],
                            capture_output=True, text=True)
    assert result.returncode == 0, result.stderr


@pytest.mark.parametrize('field,value', [
    ('max_points', 2147483648), ('grid', [1.5, 1]),
    ('shared_x', [0, float('inf')]), ('link_x', 'false'),
])
def test_invalid_session_settings_are_transactional(app_state, field, value):
    data = to_dict(app_state)
    data[field] = value
    token = app_state.session_token
    with pytest.raises(ValueError):
        apply_dict(app_state, data)
    assert app_state.session_token is token


@pytest.mark.parametrize('panel_type', [FftPanel, HistogramPanel])
def test_analysis_autofit_does_not_become_explicit_zoom(app_state, gui_frame, monkeypatch, panel_type):
    from imgui_bundle import implot
    monkeypatch.setattr(implot, 'is_plot_hovered', lambda: True)
    panel = panel_type()
    for _ in range(4):
        gui_frame(panel, app_state)
    assert panel.config(app_state).x_lim is None


@pytest.mark.parametrize('bins', [1, 100000])
def test_histogram_accepts_both_bounds(app_state, gui_frame, bins):
    app_state.commands.execute(app_state, 'hist_bins', [bins])
    apply_dict(app_state, to_dict(app_state))
    assert app_state.histogram.bins == bins
    gui_frame(HistogramPanel(), app_state)
