"""Tests for the parity features: cursors, secondary Y axis and data export."""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import session  # noqa: E402
from uz_dataviewer.state import AppState  # noqa: E402

SAMPLE = (
    "time;CH8=8)ia;CH9=9)ib;\n"
    "0.0;0.0;10.0;\n"
    "1.0;1.0;20.0;\n"
    "2.0;2.0;30.0;\n"
    "3.0;3.0;40.0;\n"
)


def _state(tmp_path):
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = AppState()
    state.commands.dispatch(state, f'load("{csv}")')
    state.commands.dispatch(state, "set_grid(1, 1)")
    state.commands.dispatch(state, "add_signal(plot_1, Log_test.csv, ia)")
    state.commands.dispatch(state, "add_signal(plot_1, Log_test.csv, ib)")
    return state


def test_cursors_command_toggles(tmp_path):
    state = _state(tmp_path)
    state.commands.dispatch(state, "cursors(plot_1, on)")
    assert state.cells[0].cursors is True
    state.commands.dispatch(state, "cursors(plot_1, off)")
    assert state.cells[0].cursors is False


def test_set_cursors_places_and_enables(tmp_path):
    state = _state(tmp_path)
    state.commands.dispatch(state, "set_cursors(plot_1, 0.5, 2.5)")
    assert state.cells[0].cursors is True
    assert state.cells[0].cursor_x == (0.5, 2.5)


def test_set_spy_rect_places_and_enables(tmp_path):
    state = _state(tmp_path)
    state.commands.dispatch(state, "set_spy_rect(plot_1, 0.5, -1.0, 1.5, 1.0)")
    assert state.cells[0].spy is True
    assert state.cells[0].spy_rect == (0.5, -1.0, 1.5, 1.0)


def test_value_at_matches_linear_interp(tmp_path):
    # The cheap searchsorted lookup must agree with np.interp on the data.
    import numpy as np

    from uz_dataviewer.panels.plots import PlotsPanel

    state = _state(tmp_path)
    run = state.registry.get(1)
    sig = state.registry.get_signal(1, "ib")  # ib = 10,20,30,40 at t=0,1,2,3
    for x in (0.0, 0.5, 1.5, 2.25, 3.0):
        got = PlotsPanel._value_at(run.time, sig.y, x)
        assert abs(got - float(np.interp(x, run.time, sig.y))) < 1e-4


def test_set_axis_assigns_right_and_back(tmp_path):
    state = _state(tmp_path)
    state.commands.dispatch(state, "set_axis(plot_1, Log_test.csv, ib, right)")
    assert (1, "ib") in state.cells[0].y2_signals
    state.commands.dispatch(state, "set_axis(plot_1, Log_test.csv, ib, left)")
    assert (1, "ib") not in state.cells[0].y2_signals


def test_set_axis_rejects_unassigned_signal(tmp_path):
    state = _state(tmp_path)
    # 'ic' is not in the plot -> reported (swallowed) and no change.
    state.commands.dispatch(state, "set_axis(plot_1, Log_test.csv, ic, right)")
    assert state.cells[0].y2_signals == []


def test_removing_signal_clears_secondary_axis(tmp_path):
    state = _state(tmp_path)
    state.commands.dispatch(state, "set_axis(plot_1, Log_test.csv, ib, right)")
    state.commands.dispatch(state, "remove_signal(plot_1, Log_test.csv, ib)")
    assert state.cells[0].y2_signals == []


def test_export_data_writes_csv(tmp_path):
    state = _state(tmp_path)
    out = tmp_path / "out.csv"
    n = session.export_data(state, 0, str(out), relative=False)
    assert n == 3  # time + ia + ib
    text = out.read_text()
    header = text.splitlines()[0]
    assert header.startswith("time,")
    assert "ia" in header and "ib" in header


def test_export_uses_plots_own_range(tmp_path):
    state = _state(tmp_path)
    # Each plot publishes its own X range; export must use plot_1's, not a global.
    state.plot_x_ranges[1] = (1.5, 3.0)
    out = tmp_path / "win.csv"
    session.export_data(state, 0, str(out), relative=False)
    import csv

    with open(out) as fh:
        times = [float(r["time"]) for r in csv.DictReader(fh)]
    assert min(times) >= 1.0 and max(times) <= 3.0  # only the plot's window


def test_export_relative_time_zeroes_start(tmp_path):
    state = _state(tmp_path)
    # A window starting above t=0 so 'relative' is observable.
    state.plot_x_ranges[1] = (1.5, 3.0)
    out = tmp_path / "rel.csv"
    session.export_data(state, 0, str(out), relative=True)
    import csv

    with open(out) as fh:
        rows = list(csv.DictReader(fh))
    assert float(rows[0]["time"]) == 0.0  # first timestamp rebased to zero


def test_export_command_via_dispatch(tmp_path):
    state = _state(tmp_path)
    out = tmp_path / "cmd.csv"
    state.commands.dispatch(state, f'export_data(plot_1, "{out}")')
    assert out.exists()


def test_export_then_import_roundtrips(tmp_path):
    """Exported CSV is comma-separated; the loader must sniff that and re-import."""
    from uz_dataviewer.loader import load_file
    from uz_dataviewer.model import DataRegistry

    state = _state(tmp_path)
    out = tmp_path / "exported.csv"
    session.export_data(state, 0, str(out))
    run = load_file(str(out), DataRegistry())
    assert set(run.signals) >= {"ia", "ib"}
    assert run.n_rows >= 1


def test_session_roundtrip_preserves_parity(tmp_path):
    state = _state(tmp_path)
    state.commands.dispatch(state, "set_axis(plot_1, Log_test.csv, ib, right)")
    state.commands.dispatch(state, "cursors(plot_1, on)")

    snap = tmp_path / "s.json"
    session.save_state(state, str(snap))
    restored = AppState()
    session.load_state(restored, str(snap))
    assert (1, "ib") in restored.cells[0].y2_signals
    assert restored.cells[0].cursors is True

    # And via the script path.
    script = tmp_path / "s.uzscript"
    session.export_script(state, str(script))
    text = script.read_text()
    assert "set_axis(plot_1, Log_test.csv, ib, right)" in text
    assert "cursors(plot_1, true)" in text
