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
