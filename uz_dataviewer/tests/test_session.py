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


def test_export_relative_flag(tmp_path):
    """'start at 0' must rebase only when on; toggling on then off keeps real time."""
    import pandas as pd

    csv = tmp_path / "Log_export.csv"
    csv.write_text("time;CH8=8)ia;\n100.0;1.0;\n100.1;2.0;\n100.2;3.0;\n")
    state = AppState()
    state.commands.dispatch(state, f'load("{csv}")')
    state.commands.dispatch(state, "add_signal(plot_1, Log_export.csv, ia)")
    out = tmp_path / "out.csv"

    # relative off -> keeps the real start time
    state.commands.dispatch(state, f'export_data(plot_1, "{out}", false)')
    assert float(pd.read_csv(out)["time"].iloc[0]) == 100.0

    # toggling the flag on then off must NOT leave the export rebased
    state.commands.dispatch(state, "set_export_relative(plot_1, on)")
    state.commands.dispatch(state, "set_export_relative(plot_1, off)")
    assert state.cells[0].export_relative is False
    state.commands.dispatch(state, f'export_data(plot_1, "{out}", false)')
    assert float(pd.read_csv(out)["time"].iloc[0]) == 100.0

    # relative on -> rebased to 0
    state.commands.dispatch(state, f'export_data(plot_1, "{out}", true)')
    assert float(pd.read_csv(out)["time"].iloc[0]) == 0.0


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


def test_xy_style_roundtrip_and_script(tmp_path):
    from uz_dataviewer.state import XyStyle

    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = AppState()
    state.commands.dispatch(state, f'load("{csv}")')
    state.commands.dispatch(state, "set_xy(plot_1, Log_test.csv, ia)")
    state.commands.dispatch(state, "add_signal(plot_1, Log_test.csv, ib)")
    state.commands.dispatch(state, "set_xy_style(plot_1, both)")

    # JSON round-trip.
    out = tmp_path / "session.json"
    session.save_state(state, str(out))
    restored = AppState()
    session.load_state(restored, str(out))
    assert restored.cells[0].plot_type is PlotType.XY
    assert restored.cells[0].xy_style is XyStyle.BOTH

    # .uzscript export emits the non-default style and replays it.
    script = tmp_path / "session.uzscript"
    session.export_script(state, str(script))
    assert "set_xy_style(plot_1, Both)" in script.read_text()
    replayed = AppState()
    session.run_script(replayed, str(script))
    assert replayed.cells[0].xy_style is XyStyle.BOTH


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


def test_json_restore_flags_analysis_recompute(tmp_path):
    """Restoring a session with FFT/Histogram sources must request a recompute,
    so the windows draw their results without a manual Compute click."""
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = _populated_state(str(csv))
    state.commands.dispatch(state, "fft_source(Log_test.csv, ia)")
    state.commands.dispatch(state, "hist_source(Log_test.csv, ib)")

    out = tmp_path / "session.json"
    session.save_state(state, str(out))

    restored = AppState()
    assert restored.fft.compute_requested is False  # fresh state
    session.load_state(restored, str(out))
    assert [r[1] for r in restored.fft.sources] == ["ia"]
    assert [r[1] for r in restored.histogram.sources] == ["ib"]
    assert restored.fft.compute_requested is True
    assert restored.histogram.compute_requested is True

    # No analysis sources -> no recompute requested.
    plain = _populated_state(str(csv))
    plain_out = tmp_path / "plain.json"
    session.save_state(plain, str(plain_out))
    restored_plain = AppState()
    session.load_state(restored_plain, str(plain_out))
    assert restored_plain.fft.compute_requested is False


def test_script_preserves_analysis_options(tmp_path):
    """A .uzscript must reproduce the FFT/Histogram options, not silently reset
    them to defaults (DC removal/Hann on, 50 bins, follow plot_1)."""
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = _populated_state(str(csv))
    state.commands.dispatch(state, "fft_source(Log_test.csv, ia)")
    state.commands.dispatch(state, "fft_remove_dc(false)")
    state.commands.dispatch(state, "fft_hann(false)")
    state.commands.dispatch(state, "fft_logy(true)")
    state.commands.dispatch(state, "hist_source(Log_test.csv, ib)")
    state.commands.dispatch(state, "hist_bins(128)")
    state.commands.dispatch(state, "set_export_relative(plot_1, true)")

    script = tmp_path / "session.uzscript"
    session.export_script(state, str(script))
    text = script.read_text()
    assert "fft_remove_dc(false)" in text
    assert "fft_hann(false)" in text
    assert "fft_logy(true)" in text
    assert "hist_bins(128)" in text
    assert "set_export_relative(plot_1, true)" in text

    replayed = AppState()
    session.run_script(replayed, str(script))
    assert replayed.fft.remove_dc is False
    assert replayed.fft.window is False
    assert replayed.fft.log_y is True
    assert [r[1] for r in replayed.fft.sources] == ["ia"]
    assert replayed.histogram.bins == 128
    assert [r[1] for r in replayed.histogram.sources] == ["ib"]
    assert replayed.cells[0].export_relative is True
