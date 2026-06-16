"""Round-trip tests for JSON state save/restore and script export/replay."""

from __future__ import annotations

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import session  # noqa: E402
from uz_dataviewer.state import AppState, PlotType  # noqa: E402

SAMPLE = (
    "time;CH8=8)ia;CH9=9)ib;\n"
    "0.0;0.1;1.0;\n"
    "0.1;0.2;1.1;\n"
    "0.2;0.3;1.2;\n"
)


def _populated_state(csv_path):
    state = AppState()
    state.commands.dispatch(state, f'load("{csv_path}")')
    state.commands.dispatch(state, "set_grid(2, 1)")
    state.commands.dispatch(state, "add_signal(plot_1, Log_test.csv, ia)")
    state.commands.dispatch(state, "set_plot_type(plot_2, Scatter)")
    state.commands.dispatch(state, "add_signal(plot_2, Log_test.csv, ib)")
    state.commands.dispatch(state, "show_samples(plot_1, on)")
    state.commands.dispatch(state, "set_max_points(750)")
    return state


def test_json_roundtrip(tmp_path):
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = _populated_state(str(csv))

    out = tmp_path / "session.json"
    session.save_state(state, str(out))

    restored = AppState()
    session.load_state(restored, str(out))

    assert (restored.rows, restored.cols) == (2, 1)
    assert restored.max_points == 750
    assert restored.cells[0].plot_type is PlotType.LINE
    assert restored.cells[0].show_samples is True
    assert restored.cells[1].plot_type is PlotType.SCATTER
    # Signals resolve back to the reloaded run by label.
    assert [r[1] for r in restored.cells[0].signals] == ["ia"]
    assert [r[1] for r in restored.cells[1].signals] == ["ib"]


def test_script_export_and_replay(tmp_path):
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = _populated_state(str(csv))

    script = tmp_path / "session.uzscript"
    session.export_script(state, str(script))
    text = script.read_text()
    assert "add_signal(plot_1," in text
    assert "set_plot_type(plot_2, Scatter)" in text

    replayed = AppState()
    n = session.run_script(replayed, str(script))
    assert n > 0
    assert (replayed.rows, replayed.cols) == (2, 1)
    assert [r[1] for r in replayed.cells[0].signals] == ["ia"]
    assert replayed.cells[1].plot_type is PlotType.SCATTER
    assert replayed.cells[0].show_samples is True
