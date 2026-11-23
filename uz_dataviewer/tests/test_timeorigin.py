"""Tests for per-log time normalisation and the FFT follow-plot window."""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import session  # noqa: E402
from uz_dataviewer.state import AppState  # noqa: E402

SAMPLE = (
    "time;CH8=8)ia;\n"
    "12.0;0.0;\n"
    "12.1;1.0;\n"
    "12.2;2.0;\n"
)


def _state(tmp_path):
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = AppState()
    state.commands.dispatch(state, f'load("{csv}")')
    return state, state.registry.get(1)


def test_normalize_time_shifts_to_zero(tmp_path):
    state, run = _state(tmp_path)
    assert abs(run.time[0] - 12.0) < 1e-6
    state.commands.dispatch(state, "normalize_time(run_1)")  # default start 0
    assert abs(run.time[0] - 0.0) < 1e-6
    assert abs(run.time[-1] - 0.2) < 1e-6
    # signal values untouched, only the axis shifted
    np.testing.assert_allclose(run.signals["ia"].y, [0.0, 1.0, 2.0], rtol=1e-5)


def test_normalize_to_custom_start_and_reset(tmp_path):
    state, run = _state(tmp_path)
    state.commands.dispatch(state, "normalize_time(run_1, 100.0)")
    assert abs(run.time[0] - 100.0) < 1e-6
    state.commands.dispatch(state, "reset_time(run_1)")
    assert abs(run.time[0] - 12.0) < 1e-6
    assert run.time_origin is None


def test_load_with_normalize_flag(tmp_path):
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = AppState()
    state.commands.dispatch(state, f'load("{csv}", 0)')
    run = state.registry.get(1)
    assert abs(run.time[0] - 0.0) < 1e-6


def test_time_origin_survives_session_roundtrip(tmp_path):
    state, run = _state(tmp_path)
    state.commands.dispatch(state, "normalize_time(run_1, 5.0)")
    snap = tmp_path / "s.json"
    session.save_state(state, str(snap))

    restored = AppState()
    session.load_state(restored, str(snap))
    assert abs(restored.registry.get(1).time[0] - 5.0) < 1e-6

    # And the script path emits the normalised load.
    script = tmp_path / "s.uzscript"
    session.export_script(state, str(script))
    assert "load(" in script.read_text()
    replayed = AppState()
    session.run_script(replayed, str(script))
    assert abs(replayed.registry.get(1).time[0] - 5.0) < 1e-6


def test_time_version_bumps_on_normalize(tmp_path):
    # The plot decimation cache is keyed on run.time_version; normalising the axis
    # must bump it so a cached envelope (built from the old time) is not reused.
    state, run = _state(tmp_path)
    v0 = run.time_version
    state.commands.dispatch(state, "normalize_time(run_1)")
    assert run.time_version != v0
    state.commands.dispatch(state, "reset_time(run_1)")
    assert run.time_version not in (v0, None)


def test_derived_refresh_bumps_signal_and_time_version(tmp_path):
    # A derived run refreshed in place reuses the run id (so plots survive), but its
    # signal array and time are new -> both versions must change so caches that keyed
    # on id(signal.y) (now the version) cannot false-hit on a reused address.
    state, _ = _state(tmp_path)
    t = np.linspace(0.0, 1.0, 8)
    rid = state.upsert_derived_run("deriv", t, np.zeros(8))
    run = state.registry.get(rid)
    sv0, tv0 = run.signals["out"].version, run.time_version
    state.upsert_derived_run("deriv", t, np.ones(8))
    run2 = state.registry.get(rid)
    assert run2.id == rid
    assert run2.signals["out"].version != sv0
    assert run2.time_version != tv0


def test_fft_follow_plot_resolves_range(tmp_path):
    state, run = _state(tmp_path)
    state.set_grid(2, 1)
    state.cells[0].add((1, "ia"))
    # Publish a range for plot_1 and have the FFT follow it.
    state.plot_x_ranges[1] = (12.05, 12.15)
    win = state.resolve_x_window(1, (0.0, 0.0), [(1, "ia")])
    assert win == (12.05, 12.15)
    # Custom (follow_plot == 0) uses the explicit values.
    assert state.resolve_x_window(0, (1.0, 2.0), [(1, "ia")]) == (1.0, 2.0)
    # Full (follow_plot == -1) uses the whole record.
    full = state.resolve_x_window(-1, (0.0, 0.0), [(1, "ia")])
    assert abs(full[0] - 12.0) < 1e-6 and abs(full[1] - 12.2) < 1e-6
    # Following a plot with no published range falls back to the full record.
    fb = state.resolve_x_window(2, (0.0, 0.0), [(1, "ia")])
    assert abs(fb[0] - 12.0) < 1e-6 and abs(fb[1] - 12.2) < 1e-6
