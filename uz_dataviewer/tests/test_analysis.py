"""Tests for the FFT/Histogram command surface and CSV export."""

from __future__ import annotations

import csv
import os
import sys
import numpy as np
import pytest
import threading
import time


sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import session
from uz_dataviewer.analysis import _next_fast_len, compute_fft, histogram_sources
from uz_dataviewer.commands import _parse_fwindow
from uz_dataviewer.session import export_fft, export_histogram
from uz_dataviewer.sources import ArraySource
from uz_dataviewer.state import AppState
from uz_dataviewer.panels.fft import FftPanel
from uz_dataviewer.panels.histogram import HistogramPanel
from uz_dataviewer.requests import Requests
from uz_dataviewer.session import apply_dict, to_dict


@pytest.mark.parametrize('channels', [('bad', 'good'), ('good', 'bad'), ('bad',)])
def test_fft_panel_reports_each_failed_signal(app_state, tmp_path, channels, compute_panel):
    from uz_dataviewer.panels.fft import FftPanel
    run = app_state.registry.add_run('recording', 'recording', np.arange(8.),
                                     {'bad': np.full(8, np.nan), 'good': np.arange(8.)}, {})
    app_state.fft.sources = [(run.id, channel) for channel in channels]
    panel = FftPanel()
    compute_panel(panel, app_state, app_state.fft, 0, 7)
    expected = [(run.id, 'good')] if 'good' in channels else []
    assert panel._result_refs() == expected
    assert f'{len(expected)} succeeded, 1 failed' in panel._info
    assert 'bad @ recording' in panel._info
    assert 'non-finite' in panel._info
    destination = tmp_path / 'fft.csv'
    destination.write_text('existing export')
    with pytest.raises(ValueError, match='bad @ recording.*non-finite'):
        export_fft(app_state, str(destination))
    assert destination.read_text() == 'existing export'


def test_next_fast_len_is_5_smooth_and_ge():
    for n in (1, 6, 7, 17, 100, 19_997, 9_000_001):
        m = _next_fast_len(n)
        assert m >= n
        r = m
        for p in (2, 3, 5):
            while r % p == 0:
                r //= p
        assert r == 1 or n <= 6, (n, m)  # m is 2^a*3^b*5^c (n>6)
    assert _next_fast_len(17) == 18
    assert _next_fast_len(100) == 100  # already smooth
    assert _next_fast_len(19_997) == 20_000


def test_compute_fft_recovers_tone_on_bad_length_in_float32():
    # A prime window length exercises the zero-pad-to-fast-length path; amplitude
    # and frequency must survive padding, and the output stays float32.
    fs, n, freq, amp = 5000.0, 19_997, 50.0, 2.0
    t = (np.arange(n) / fs).astype(np.float64)
    y = (amp * np.sin(2 * np.pi * freq * t)).astype(np.float32)
    r = compute_fft(t, y, float(t[0]), float(t[-1]), remove_dc=True, window=False)
    assert r.ok
    assert r.freqs.dtype == np.float32 and r.mag.dtype == np.float32
    assert abs(float(r.freqs[np.argmax(r.mag)]) - freq) < fs / n * 3
    assert abs(float(r.mag.max()) - amp) < 0.05  # normalised by original n, not padded length


def test_compute_fft_recovers_tone_amplitude_with_hann_window():
    # With the Hann window on (the default), the amplitude must be normalised by the
    # window's coherent gain (Sum w), not by n -- otherwise the peak reads ~A/2.
    fs, n, freq, amp = 5000.0, 8192, 50.0, 2.0
    t = (np.arange(n) / fs).astype(np.float64)
    y = (amp * np.sin(2 * np.pi * freq * t)).astype(np.float32)
    r = compute_fft(t, y, float(t[0]), float(t[-1]), remove_dc=True, window=True)
    assert r.ok
    assert abs(float(r.freqs[np.argmax(r.mag)]) - freq) < fs / n * 3
    assert abs(float(r.mag.max()) - amp) < 0.05  # not ~A/2


def test_compute_fft_empty_and_nonfinite_return_error_not_crash():
    # Empty run -> clear error, not an IndexError on time[0].
    r = compute_fft(np.array([], dtype=np.float64), np.array([], dtype=np.float32), 0.0, 0.0)
    assert not r.ok and "No samples" in r.info
    # A non-finite window -> clear error instead of a NaN-poisoned spectrum.
    t = np.linspace(0.0, 1.0, 64)
    y = np.full(64, np.nan, dtype=np.float32)
    r2 = compute_fft(t, y, float(t[0]), float(t[-1]))
    assert not r2.ok and "non-finite" in r2.info


def test_compute_fft_dc_bin_not_double_counted():
    # A pure DC offset should read its true amplitude at f=0 (the single-sided x2
    # applies only to the mirrored AC bins, not DC).
    fs, n, offset = 1000.0, 4096, 3.0
    t = (np.arange(n) / fs).astype(np.float64)
    y = np.full(n, offset, dtype=np.float32)
    r = compute_fft(t, y, float(t[0]), float(t[-1]), remove_dc=False, window=False)
    assert r.ok
    assert float(r.freqs[0]) == 0.0
    assert abs(float(r.mag[0]) - offset) < 0.01  # not 2*offset


def _state():
    state = AppState()
    t = np.linspace(0.0, 2.0, 4000)
    state.registry.add_run(
        "Log.csv", "Log.csv", t,
        {"ia": np.sin(2 * np.pi * 50 * t).astype(np.float32),
         "ib": np.cos(2 * np.pi * 20 * t).astype(np.float32)},
        {"ia": "", "ib": ""},
    )
    return state


def test_fwindow_parsing():
    assert _parse_fwindow("custom") == 0
    assert _parse_fwindow("full") == -1
    assert _parse_fwindow("plot_3") == 3
    assert _parse_fwindow(2) == 2


def test_fft_follow_command_sets_mode_and_echoes():
    state = _state()
    state.commands.dispatch(state, "fft_source(run_1, ia)")
    state.commands.dispatch(state, "fft_follow(full)")
    assert state.fft.follow_plot == -1
    state.commands.dispatch(state, "fft_follow(custom)")
    assert state.fft.follow_plot == 0
    state.commands.dispatch(state, "fft_follow(plot_1)")
    assert state.fft.follow_plot == 1
    # Following a plot requests a compute; custom/full do not.
    assert state.fft.compute_requested is True
    # The canonical call was echoed to the console.
    cmds = [e.message for e in state.console._entries if e.level == "CMD"]
    assert "fft_follow(full)" in cmds and "fft_follow(plot_1)" in cmds


def test_fft_option_commands():
    state = _state()
    state.commands.dispatch(state, "fft_remove_dc(off)")
    state.commands.dispatch(state, "fft_hann(off)")
    state.commands.dispatch(state, "fft_logx(on)")
    state.commands.dispatch(state, "fft_logy(on)")
    assert state.fft.remove_dc is False
    assert state.fft.window is False
    assert state.fft.log_x is True and state.fft.log_y is True


def test_hist_bins_and_range_commands():
    state = _state()
    state.commands.dispatch(state, "hist_bins(33)")
    assert state.histogram.bins == 33
    state.commands.dispatch(state, "fft_range(0.5, 1.5)")
    assert (state.fft.x_min, state.fft.x_max) == (0.5, 1.5)


def test_xlim_commands_set_pending():
    state = _state()
    state.commands.dispatch(state, "fft_xlim(10, 200)")
    assert state.fft.pending_x_lim == (10.0, 200.0)
    state.commands.dispatch(state, "hist_xlim(-1, 1)")
    assert state.histogram.pending_x_lim == (-1.0, 1.0)


def test_export_fft(tmp_path):
    state = _state()
    state.commands.dispatch(state, "fft_source(run_1, ia)")
    state.commands.dispatch(state, "fft_source(run_1, ib)")
    out = tmp_path / "fft.csv"
    n = session.export_fft(state, str(out))
    assert n == 3  # frequency + ia + ib
    header = out.read_text().splitlines()[0]
    assert header.startswith("frequency,") and "ia" in header and "ib" in header


def test_export_fft_mixed_sample_rates_pairs_freq_with_amp(tmp_path):
    # Two runs at *different* sample rates -> different FFT frequency axes. The CSV
    # must keep each amplitude paired with its own frequency axis (per-signal
    # `<name>_frequency` columns), not collapse onto one shared frequency column.
    import pandas as pd

    state = AppState()
    t1 = np.linspace(0.0, 1.0, 1000, endpoint=False)   # fs = 1000 Hz -> 501 bins
    t2 = np.linspace(0.0, 1.0, 4000, endpoint=False)   # fs = 4000 Hz -> 2001 bins
    state.registry.add_run("a.csv", "a.csv", t1,
                           {"sa": np.sin(2 * np.pi * 50 * t1).astype(np.float32)}, {"sa": ""})
    state.registry.add_run("b.csv", "b.csv", t2,
                           {"sb": np.sin(2 * np.pi * 123 * t2).astype(np.float32)}, {"sb": ""})
    state.commands.dispatch(state, "fft_source(run_1, sa)")
    state.commands.dispatch(state, "fft_source(run_2, sb)")
    out = tmp_path / "fft_mixed.csv"
    session.export_fft(state, str(out))
    df = pd.read_csv(out)
    assert "frequency" not in df.columns  # mixed axes -> no single shared column
    assert {"sa_frequency", "sa", "sb_frequency", "sb"} <= set(df.columns)
    sa = df[["sa_frequency", "sa"]].dropna().reset_index(drop=True)
    sb = df[["sb_frequency", "sb"]].dropna().reset_index(drop=True)
    assert abs(float(sa["sa_frequency"][int(sa["sa"].values.argmax())]) - 50.0) < 2.0
    assert abs(float(sb["sb_frequency"][int(sb["sb"].values.argmax())]) - 123.0) < 2.0


def test_export_histogram(tmp_path):
    state = _state()
    state.commands.dispatch(state, "hist_source(run_1, ia)")
    state.commands.dispatch(state, "hist_source(run_1, ib)")
    state.commands.dispatch(state, "hist_bins(20)")
    out = tmp_path / "hist.csv"
    n = session.export_histogram(state, str(out))
    assert n == 3  # bin_center + ia + ib
    rows = list(csv.DictReader(open(out)))
    assert len(rows) == 20  # one row per bin
    assert "bin_center" in rows[0] and "ia" in rows[0] and "ib" in rows[0]


def test_fft_export_command_via_dispatch(tmp_path):
    state = _state()
    state.commands.dispatch(state, "fft_source(run_1, ia)")
    out = tmp_path / "viacmd.csv"
    state.commands.dispatch(state, f'fft_export("{out}")')
    assert out.exists()


def test_analysis_replacement_clears_old_results_until_new_computation(app_state, gui_frame, tmp_path, monkeypatch, compute_panel):
    import threading
    import time
    from imgui_bundle import implot
    from uz_dataviewer.panels.fft import FftPanel
    from uz_dataviewer.session import to_dict, apply_dict
    state = app_state
    for name, frequency in [('old', 8), ('new', 16)]:
        t = np.arange(64) / 64
        np.savetxt(tmp_path / f'{name}.csv', np.column_stack([t, np.sin(2*np.pi*frequency*t)]),
                   delimiter=';', header='time;a', comments='')
    state.load_sync(str(tmp_path / 'old.csv'))
    state.fft.sources = [(1, 'a')]
    state.fft.follow_plot = -1
    panel = FftPanel()
    compute_panel(panel, state, state.fft, 0, 63/64)
    panel._computed_key = panel._current_key(state, state.fft)
    for _ in range(3):
        gui_frame(panel, state)
    saved = to_dict(state)
    saved['runs'][0]['path'] = str(tmp_path / 'new.csv')
    apply_dict(state, saved)
    release, started = threading.Event(), threading.Event()

    def block(cancel):
        started.set()
        assert release.wait(5)

    state.services.analysis_jobs.request('block', 1, 1, block)
    assert started.wait(2)
    drawn = []
    original_line = implot.plot_line

    def capture(label, x, y, *args):
        drawn.append((label, float(x[np.argmax(y)])))
        original_line(label, x, y, *args)

    monkeypatch.setattr(implot, 'plot_line', capture)
    try:
        for _ in range(3):
            gui_frame(panel, state)
        assert not drawn and not panel._results
        release.set()
        deadline = time.monotonic() + 5
        while time.monotonic() < deadline and not drawn:
            gui_frame(panel, state)
            time.sleep(.01)
        assert drawn and all('new.csv' in label and peak == 16 for label, peak in drawn)
    finally:
        release.set()


def test_fft_export_rejects_partial_results_before_writing(app_state, tmp_path):
    import pytest
    state = app_state
    t = np.arange(16) / 16
    good = np.sin(2*np.pi*2*t)
    bad = good.copy()
    bad[3] = np.nan
    state.add_run_from_arrays('input', 'input', t, {'good': good, 'bad': bad}, {})
    state.fft.follow_plot = -1
    destination = tmp_path / 'spectra.csv'
    for refs in [[(1, 'good'), (1, 'bad')], [(1, 'bad'), (1, 'good')], [(1, 'good'), (1, 'missing')]]:
        state.fft.sources = refs
        destination.write_text('previous successful export')
        with pytest.raises(ValueError, match='bad|missing'):
            session.export_fft(state, str(destination))
        assert destination.read_text() == 'previous successful export'
        destination.unlink()
        with pytest.raises(ValueError, match='bad|missing'):
            session.export_fft(state, str(destination))
        assert not destination.exists()


def test_grid_shrink_resets_removed_analysis_targets(app_state):
    import pytest
    from uz_dataviewer.commands import CommandError
    state = app_state
    state.add_run_from_arrays('input', 'input', np.arange(8.) + 100, {'a': np.arange(8.)}, {})
    state.set_grid(1, 2)
    state.plot_x_ranges = {1: (100., 104.), 2: (101., 102.)}
    for cfg in (state.fft, state.histogram):
        cfg.sources = [(1, 'a')]
        cfg.follow_plot = 2
        cfg.compute_requested = False
    state.commands.execute(state, 'set_grid', [1, 1])
    assert state.plot_x_ranges == {1: (100., 104.)}
    for cfg in (state.fft, state.histogram):
        assert cfg.follow_plot == -1 and cfg.compute_requested
        assert state.resolve_x_window(cfg.follow_plot, (0., 1.), cfg.sources) == (100., 107.)
    for command in ('fft_follow', 'hist_follow'):
        for target in ('plot_2', -2):
            with pytest.raises(CommandError, match='Analysis window'):
                state.commands.execute(state, command, [target])
    state.set_grid(1, 2)
    assert 2 not in state.plot_x_ranges


@pytest.mark.parametrize('exporter,config,axis', [
    (export_fft, 'fft', 'frequency'), (export_histogram, 'histogram', 'bin_center'),
])
def test_exports_preserve_duplicate_recordings(states, tmp_path, exporter, config, axis):
    import pandas as pd
    state = states()
    for i in range(3):
        path = tmp_path / str(i) / 'same.csv'
        path.parent.mkdir()
        path.write_text('time;a\n' + ''.join((f'{j};{(i + 1) * (j + 1)}\n' for j in range(8))))
        run = state.load_sync(str(path))
        getattr(state, config).sources.append((run.id, 'a'))
    getattr(state, config).follow_plot = -1
    path = tmp_path / 'analysis.csv'
    exporter(state, str(path))
    frame = pd.read_csv(path)
    assert frame.columns[0] == axis and len(frame.columns) == 4 and frame.columns.is_unique
    assert len({state.signal_label(ref) for ref in getattr(state, config).sources}) == 3
    if config == 'fft':
        np.testing.assert_allclose(frame.iloc[:, 2], 2 * frame.iloc[:, 1], rtol=1e-6, atol=1e-6)
        np.testing.assert_allclose(frame.iloc[:, 3], 3 * frame.iloc[:, 1], rtol=1e-6, atol=1e-6)
    else:
        np.testing.assert_array_equal(frame.iloc[:, 1:].sum(axis=0), [8, 8, 8])


def test_analysis_remove_uses_reference_after_rename(states, recording_csv, compute_panel):
    from uz_dataviewer.panels.fft import FftPanel
    state = states()
    for _ in range(3):
        run = state.load_sync(str(recording_csv))
        state.fft.sources.append((run.id, 'a'))
    panel = FftPanel()
    compute_panel(panel, state, state.fft, 0, 7)
    state.registry.get(2).label = 'renamed'
    panel._remove(state, panel._result_refs()[1])
    assert state.fft.sources == [(1, 'a'), (3, 'a')]


def test_histogram_exact_window():
    source = ArraySource(np.arange(3.), {'a':np.arange(3.,dtype=np.float32)})
    assert histogram_sources([('a',source,'a',0)], .9, 1.1, 5)[1] == 1
    assert histogram_sources([('a',source,'a',0)], 10, 11, 5)[1] == 0


@pytest.mark.parametrize('value', [0., 1., -1., 1e16, -1e16, 1e20, -1e20,
                                  np.finfo(np.float32).max, -np.finfo(np.float32).max])
def test_constant_histogram_and_plot_fit_have_distinct_finite_bounds(app_state, value):
    from uz_dataviewer.panels.plots import PlotsPanel
    run = app_state.registry.add_run('constant', 'constant', np.arange(8.),
                                     {'a': np.full(8, value, dtype=np.float32)}, {})
    results, total, dropped = histogram_sources([('a', run.data_source(), 'a', 0)], 0, 7, 50)
    _, centers, counts, width = results[0]
    assert total == counts.sum() == 8 and dropped == 0
    assert width > 0 and np.isfinite(width)
    assert np.isfinite(centers).all() and np.all(np.diff(centers) > 0)
    app_state.cells[0].add((run.id, 'a'))
    lo, hi = PlotsPanel()._cell_y_extent(app_state, app_state.cells[0])
    assert np.isfinite([lo, hi]).all() and lo < hi
    assert lo <= float(run.signals['a'].y[0]) <= hi


def test_fft_releases_hann_window_after_computation(monkeypatch):
    import weakref
    from uz_dataviewer import analysis
    original = analysis._hann
    windows = []

    def track(n):
        window, total = original(n)
        windows.append(weakref.ref(window))
        return window, total

    monkeypatch.setattr(analysis, '_hann', track)
    for n in (64, 128, 64):
        result = compute_fft(np.arange(n, dtype=float), np.ones(n), 0, n - 1)
        assert result.ok
        assert all(reference() is None for reference in windows)


@pytest.mark.parametrize('value', [1e20, -1e20])
def test_histogram_expands_nearly_constant_float64_range(value):
    values = np.array([value, np.nextafter(value, np.inf)])
    source = ArraySource(np.arange(2.), {'a': values})
    results, total, _ = histogram_sources([('a', source, 'a', 0)], 0, 1, 50)
    _, centers, counts, width = results[0]
    assert total == counts.sum() == 2
    assert width > 0 and np.all(np.diff(centers) > 0)


@pytest.mark.parametrize('timestamps', [[0,0,0,100], [0,1,2,4], [0,1,np.nan,3]])
def test_fft_rejects_irregular_time(timestamps):
    assert not compute_fft(np.array(timestamps,dtype=float), np.arange(4.), 0,100).ok

@pytest.mark.parametrize('time,values', [
    (np.arange(8.), np.ones((8, 2))),
    (np.ones((8, 2)), np.arange(8.)),
    (np.arange(8.), np.arange(4.)),
    (np.array(1.), np.array(2.)),
])
@pytest.mark.parametrize('window', [False, True])
def test_fft_rejects_malformed_input_shapes(time, values, window):
    from uz_dataviewer.api import fft
    for result in (compute_fft(time, values, 0., 7., window=window),
                   fft(time, values, window=window)):
        assert not result.ok
        assert 'equal-length one-dimensional' in result.info


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


@pytest.mark.parametrize('panel_type,field', [(FftPanel, 'fft'), (HistogramPanel, 'histogram')])
def test_mouse_zoom_saved_and_preserved_on_compute(app_state, gui_frame, monkeypatch, recording_csv,
                                                  panel_type, field):
    from imgui_bundle import implot
    state = app_state
    state.load_sync(str(recording_csv))
    state.services.analysis_jobs.close()
    state.services.analysis_jobs = Requests(synchronous=True)
    state.services.analysis_displays['fft'].close()
    state.services.analysis_displays['fft'] = Requests(synchronous=True)
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


def test_evicted_fft_summary_rebuilds_in_worker(app_state, gui_frame, monkeypatch, compute_panel):
    state = app_state
    t = np.arange(262144.) / 1000
    state.registry.add_run('test', 'test', t, {'y': np.sin(t)}, {})
    state.fft.sources = [(1, 'y')]
    state.fft.follow_plot = -1
    state.max_points = 100
    panel = FftPanel()
    compute_panel(panel, state, state.fft, t[0], t[-1])
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
        assert state.services.analysis_displays['fft'].pending
        release.set()
        deadline = time.monotonic() + 3
        while state.services.analysis_displays['fft'].pending and time.monotonic() < deadline:
            time.sleep(.005)
        gui_frame(panel, state)
        assert not panel._fit_pending
        assert state.services.analysis_displays['fft'].results
    finally:
        release.set()


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


def analysis_setup(state, panel_type):
    state.services.analysis_jobs.close()
    state.services.analysis_jobs = Requests(synchronous=True)
    for label in ('a', 'b'):
        state.registry.add_run(label, label, np.arange(64.) / 64,
                               {'y': np.sin(np.arange(64.))}, {})
    panel = panel_type()
    cfg = panel.config(state)
    cfg.sources = [(1, 'y'), (2, 'y')]
    cfg.follow_plot = -1
    cfg.compute_requested = True
    return panel, cfg


@pytest.mark.parametrize('panel_type', [FftPanel, HistogramPanel])
def test_removed_analysis_trace_disappears_while_worker_is_blocked(app_state, gui_frame, panel_type):
    state = app_state
    panel, cfg = analysis_setup(state, panel_type)
    for _ in range(3):
        gui_frame(panel, state)
    assert len(panel._result_refs()) == 2
    state.services.analysis_jobs.close()
    state.services.analysis_jobs = Requests()
    started, release = threading.Event(), threading.Event()
    def block(cancel):
        started.set()
        assert release.wait(5)
    state.services.analysis_jobs.request('block', 1, 1, block)
    assert started.wait(2)
    try:
        state.remove_run(1)
        gui_frame(panel, state)
        assert (1, 'y') not in panel._result_refs()
        assert cfg.sources == [(2, 'y')]
    finally:
        release.set()


@pytest.mark.parametrize('panel_type,prefix', [(FftPanel, 'fft'), (HistogramPanel, 'hist')])
def test_explicit_analysis_zoom_survives_recompute(app_state, gui_frame, monkeypatch, panel_type, prefix):
    from imgui_bundle import implot
    state = app_state
    panel, cfg = analysis_setup(state, panel_type)
    for _ in range(3):
        gui_frame(panel, state)
    state.commands.execute(state, prefix + '_xlim', [2, 5])
    # First consume the zoom in a frame, then complete another computation.
    gui_frame(panel, state)
    assert cfg.pending_x_lim is None
    cfg.compute_requested = True
    applied = []
    original = implot.setup_axis_limits
    def capture(axis, lo, hi, *args):
        applied.append((axis, lo, hi))
        return original(axis, lo, hi, *args)
    monkeypatch.setattr(implot, 'setup_axis_limits', capture)
    gui_frame(panel, state)
    assert (implot.ImAxis_.x1, 2, 5) in applied
    assert cfg.x_lim == (2, 5)


@pytest.mark.parametrize('panel_type,prefix', [(FftPanel, 'fft'), (HistogramPanel, 'hist')])
def test_zoom_issued_during_computation_survives_completion(app_state, gui_frame, monkeypatch, panel_type, prefix):
    import time
    from imgui_bundle import implot
    state = app_state
    panel, cfg = analysis_setup(state, panel_type)
    for _ in range(3):
        gui_frame(panel, state)
    state.services.analysis_jobs.close()
    state.services.analysis_jobs = Requests()
    started, release = threading.Event(), threading.Event()
    from uz_dataviewer.analysis import FftRequest, HistogramRequest
    request_type = FftRequest if panel_type is FftPanel else HistogramRequest
    original_compute = request_type.compute
    def blocked_compute(self, *args):
        started.set()
        assert release.wait(5)
        return original_compute(self, *args)
    monkeypatch.setattr(request_type, 'compute', blocked_compute)
    cfg.compute_requested = True
    gui_frame(panel, state)
    assert started.wait(2)
    applied = []
    original_limits = implot.setup_axis_limits
    def capture(axis, lo, hi, *args):
        applied.append((axis, lo, hi))
        return original_limits(axis, lo, hi, *args)
    monkeypatch.setattr(implot, 'setup_axis_limits', capture)
    try:
        state.commands.execute(state, prefix + '_xlim', [2, 5])
        gui_frame(panel, state)
        assert (implot.ImAxis_.x1, 2, 5) in applied
        applied.clear()
    finally:
        release.set()
    deadline = time.monotonic() + 3
    while panel._analysis_pending is not None and time.monotonic() < deadline:
        gui_frame(panel, state)
        time.sleep(.01)
    assert panel._analysis_pending is None
    assert (implot.ImAxis_.x1, 2, 5) in applied


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy'])
@pytest.mark.parametrize('offset', [0, 10])
@pytest.mark.parametrize('reverse', [False, True])
def test_full_analysis_includes_all_recordings(app_state, tmp_path, backend, mode, offset, reverse):
    state = app_state
    state.backend, state.loading_mode = backend, mode
    runs = []
    for name, timestamps in [('short', np.arange(4.)), ('long', np.arange(10.) + offset)]:
        path = tmp_path / f'{name}.csv'
        np.savetxt(path, np.column_stack([timestamps, np.sin(timestamps)]), delimiter=',',
                   header=f'time,{name}', comments='')
        runs.append(state.load_sync(str(path)))
    refs = [(run.id, next(iter(run.signals))) for run in runs]
    if reverse:
        refs.reverse()
    state.fft.sources = state.histogram.sources = refs
    state.fft.follow_plot = state.histogram.follow_plot = -1
    window = state.resolve_x_window(-1, (0, 0), refs)
    assert window == (0, offset + 9)
    for panel_type in (FftPanel, HistogramPanel):
        panel = panel_type()
        result = panel._make_request(state, panel.config(state), *window).compute()
        if panel_type is HistogramPanel:
            assert {ref[1]: counts.sum() for ref, _, counts, _ in result.series} == {'short': 4, 'long': 10}
        else:
            assert {ref[1]: len(freqs) for ref, freqs, _, _ in result.series} == {'short': 3, 'long': 6}
    hist_path, fft_path = tmp_path / 'hist.csv', tmp_path / 'fft.csv'
    export_histogram(state, str(hist_path))
    export_fft(state, str(fft_path))
    with hist_path.open() as fh:
        rows = list(csv.DictReader(fh))
    assert sum(int(row['short']) for row in rows) == 4
    assert sum(int(row['long']) for row in rows) == 10
    with fft_path.open() as fh:
        rows = list(csv.DictReader(fh))
    for name, count in [('short', 3), ('long', 6)]:
        actual = [float(row[f'{name}_frequency']) for row in rows if row[f'{name}_frequency']]
        actual = [value for value in actual if np.isfinite(value)]
        np.testing.assert_allclose(actual, np.fft.rfftfreq((count - 1) * 2))


def test_full_window_fallback_and_explicit_windows(app_state):
    state = app_state
    a = state.registry.add_run('a', 'a', np.arange(4.), {'y': np.ones(4)}, {})
    b = state.registry.add_run('b', 'b', np.arange(10.) + 20, {'y': np.ones(10)}, {})
    refs = [(a.id, 'y'), (b.id, 'y')]
    assert state.resolve_x_window(1, (0, 0), refs) == (0, 29)
    assert state.resolve_x_window(0, (1, 2), refs) == (1, 2)
    state.set_plot_x_limits(1, 1, 2)
    assert state.resolve_x_window(1, (0, 0), refs) == (1, 2)
    b.set_time_origin(-20)
    assert state.resolve_x_window(-1, (0, 0), refs) == (-20, 3)


def test_fft_integer_time_matches_float_time():
    t, y = np.arange(10), np.arange(10.)
    actual = compute_fft(t, y, .2, 7.2, window=False)
    expected = compute_fft(t.astype(float), y, .2, 7.2, window=False)
    assert actual.ok and expected.ok
    assert actual.info == expected.info
    np.testing.assert_array_equal(actual.freqs, expected.freqs)
    np.testing.assert_array_equal(actual.mag, expected.mag)
    assert not compute_fft(t, y, .2, .9).ok


@pytest.mark.parametrize('panel_type', [FftPanel, HistogramPanel])
def test_analysis_request_captures_inputs_without_gui_state(app_state, panel_type):
    from dataclasses import FrozenInstanceError
    state = app_state
    run = state.registry.add_run('a', 'a', np.arange(8.), {'y': np.arange(8.)}, {})
    panel = panel_type()
    cfg = panel.config(state)
    cfg.sources = [(run.id, 'y')]
    request = panel._make_request(state, cfg, 0, 7)
    expected = request.compute()
    cfg.sources.clear()
    cfg.bins = 3
    cfg.remove_dc = False
    run.set_time_origin(100)
    state.registry.remove_run(run.id)
    actual = request.compute()
    assert actual.info == expected.info
    for left, right in zip(actual.series[0][1:3], expected.series[0][1:3]):
        np.testing.assert_array_equal(left, right)
    with pytest.raises(FrozenInstanceError):
        request.window = (100, 107)
