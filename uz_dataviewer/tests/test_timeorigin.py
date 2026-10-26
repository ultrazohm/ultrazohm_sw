"""Tests for per-log time normalisation and the FFT follow-plot window."""

from __future__ import annotations

import json


import numpy as np
import pytest


from uz_dataviewer import session
from uz_dataviewer.state import AppState


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
    state.commands.dispatch(state, f'load({json.dumps(str(csv))})')
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
    state.commands.dispatch(state, f'load({json.dumps(str(csv))}, 0)')
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
    state.upsert_derived_run("deriv", t, np.ones(8), run_id=rid)
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


@pytest.mark.parametrize('mode', ['memory', 'lazy'])
@pytest.mark.parametrize('target', [float('nan'), float('inf'), -float('inf')])
def test_nonfinite_origin_is_rejected_before_mutation(app_state, tmp_path, mode, target):
    path = tmp_path / 'origin.csv'
    path.write_text(SAMPLE)
    app_state.loading_mode = mode
    run = app_state.load_sync(str(path))
    version, original = run.time_version, np.asarray(run.time).copy()
    with pytest.raises(ValueError, match='finite'):
        app_state.commands.execute(app_state, 'normalize_time', [run.id, target])
    assert run.time_version == version and run.time_origin is None
    np.testing.assert_array_equal(np.asarray(run.time), original)


@pytest.mark.parametrize("backend", ["pyarrow", "polars"])
def test_normalized_full_window_preserves_all_samples(tmp_path, backend):
    p = tmp_path / "log.csv"
    p.write_text("time;a\n" + "".join(f"{i / 10};{i}\n" for i in range(1, 9)))
    from uz_dataviewer.loader import open_file
    from uz_dataviewer.model import DataRegistry

    results = []
    for mode in ("memory", "lazy"):
        run = open_file(str(p), mode, backend=backend).register(DataRegistry())
        run.set_time_origin(100)
        limits = (float(run.time[0]), float(run.time[-1]))
        results.append(run.read_window(["a"], *limits)[1]["a"].tolist())
    assert results == [list(range(1, 9)), list(range(1, 9))]


@pytest.mark.parametrize("backend", ["pyarrow", "polars"])
@pytest.mark.parametrize("origin", [100.0, 1e16, -100.0, 0.1])
@pytest.mark.parametrize("raw_origin", [0.0, 1e16])
def test_displayed_selection_matches_resident_mask(
    tmp_path, backend, origin, raw_origin
):
    from uz_dataviewer.loader import open_file
    from uz_dataviewer.model import DataRegistry
    from uz_dataviewer.analysis import AnalysisInput, histogram_sources
    from uz_dataviewer.sources import displayed_bounds

    path = tmp_path / "samples.csv"
    raw = raw_origin + np.array([0.1, 0.2, 0.2, 0.3, 0.8])
    path.write_text("time,a\n" + "".join(f"{t},{i}\n" for i, t in enumerate(raw)))
    displayed = (raw - raw[0]) + origin
    for mode in ("memory", "lazy"):
        run = open_file(str(path), mode, backend=backend).register(DataRegistry())
        run.set_time_origin(origin)
        assert run.time[0] == origin
        selected = AnalysisInput.capture(DataRegistryWithRun(run), [(run.id, "a")])[0]
        for lo, hi in [
            (displayed[0], displayed[-1]),
            (displayed[1], displayed[1]),
            (displayed[1], displayed[-1]),
            (origin - 10, origin - 5),
        ]:
            mask = (displayed >= lo) & (displayed <= hi)
            t, y = selected.read_window(lo, hi, None)
            np.testing.assert_array_equal(t, displayed[mask])
            np.testing.assert_array_equal(y, np.arange(len(raw))[mask])
            a, b = displayed_bounds(run.data_source(), lo, hi, run.time_offset)
            assert b - a == mask.sum()
            plot = run.data_source().read_plot(
                "a", lo, hi, 100, padding=False, offset=run.time_offset
            )
            assert plot.raw_count == mask.sum()
            _, count, dropped = histogram_sources(
                [("a", run.data_source(), "a", run.time_offset)], lo, hi, 5
            )
            assert count == mask.sum() and dropped == 0


class DataRegistryWithRun:
    def __init__(self, run):
        self.run = run

    def get(self, run_id):
        return self.run if run_id == self.run.id else None
