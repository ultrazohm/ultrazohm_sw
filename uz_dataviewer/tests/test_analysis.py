"""Tests for the FFT/Histogram command surface and CSV export."""

from __future__ import annotations

import csv
import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import session  # noqa: E402
from uz_dataviewer.analysis import _next_fast_len, compute_fft  # noqa: E402
from uz_dataviewer.commands import _parse_fwindow  # noqa: E402
from uz_dataviewer.state import AppState  # noqa: E402


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
