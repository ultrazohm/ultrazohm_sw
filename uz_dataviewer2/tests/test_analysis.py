"""Tests for the FFT/Histogram command surface and CSV export."""

from __future__ import annotations

import csv
import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import session  # noqa: E402
from uz_dataviewer.commands import _parse_fwindow  # noqa: E402
from uz_dataviewer.state import AppState  # noqa: E402


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
