"""Tests for the command layer: parsing, coercion and dispatch (no GUI)."""

from __future__ import annotations

import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.commands import CommandError, format_call, parse_call  # noqa: E402
from uz_dataviewer.state import AppState, PlotType  # noqa: E402


def _state_with_run():
    state = AppState()
    time = np.linspace(0.0, 4.0, 1000)
    state.registry.add_run(
        "Log.csv", "/tmp/Log.csv", time,
        {"ia": np.sin(time).astype(np.float32), "ib": np.cos(time).astype(np.float32)},
        {"ia": "", "ib": ""},
    )
    return state


def test_parse_call_variants():
    assert parse_call("fft") == ("fft", [])
    assert parse_call("set_grid(2, 2)") == ("set_grid", ["2", "2"])
    assert parse_call('load("a, b.csv")') == ("load", ["a, b.csv"])
    assert parse_call("set_x_lim(plot_1, 0.0, 0.5)") == ("set_x_lim", ["plot_1", "0.0", "0.5"])


def test_parse_call_rejects_garbage():
    with pytest.raises(CommandError):
        parse_call("not a command!!")


def test_dispatch_builds_plot_state():
    state = _state_with_run()
    for line in [
        "set_grid(2, 2)",
        "add_signal(plot_1, run_1, ia)",
        "add_signal(plot_1, Log.csv, ib)",  # run resolved by label
        "set_plot_type(plot_2, Scatter)",
        "set_x_lim(plot_1, 1.0, 2.0)",
        "show_samples(plot_1, on)",
        "set_max_points(500)",
        "link_x(off)",
    ]:
        state.commands.dispatch(state, line)

    assert state.cells[0].signals == [(1, "ia"), (1, "ib")]
    assert state.cells[0].show_samples is True
    assert state.cells[0].pending_x_lim == (1.0, 2.0)
    assert state.cells[1].plot_type is PlotType.SCATTER
    assert state.max_points == 500
    assert state.link_x is False


def test_cursors_recenter_on_enable():
    state = _state_with_run()
    cell = state.cells[0]
    cell.cursor_x = (0.1, 0.2)  # a position placed at an earlier zoom
    cell.cursors = False
    state.commands.dispatch(state, "cursors(plot_1, on)")
    assert cell.cursor_x is None  # cleared -> re-centers to the current view
    assert cell.cursors is True
    cell.cursor_x = (0.3, 0.4)
    state.commands.dispatch(state, "cursors(plot_1, on)")  # already on -> keep it
    assert cell.cursor_x == (0.3, 0.4)


def test_spy_recenter_on_enable():
    state = _state_with_run()
    cell = state.cells[0]
    cell.spy_rect = (0.0, 0.0, 1.0, 1.0)
    cell.spy = False
    state.commands.dispatch(state, "spy(plot_1, on)")
    assert cell.spy_rect is None
    assert cell.spy is True


def test_set_xy_switches_type_and_source():
    state = _state_with_run()
    state.commands.dispatch(state, "set_xy(plot_1, run_1, ia)")
    assert state.cells[0].plot_type is PlotType.XY
    assert state.cells[0].xy_source == (1, "ia")


def test_set_xy_style():
    from uz_dataviewer.state import XyStyle

    state = _state_with_run()
    assert state.cells[0].xy_style is XyStyle.LINE  # default preserves old behaviour
    state.commands.dispatch(state, "set_xy_style(plot_1, markers)")
    assert state.cells[0].xy_style is XyStyle.MARKERS
    state.commands.dispatch(state, "set_xy_style(plot_1, Both)")  # case-insensitive
    assert state.cells[0].xy_style is XyStyle.BOTH
    # An unknown style is reported to the console, not applied.
    state.commands.dispatch(state, "set_xy_style(plot_1, nope)")
    assert state.cells[0].xy_style is XyStyle.BOTH


def test_unknown_signal_is_reported_not_raised():
    state = _state_with_run()
    # Dispatch swallows errors into the console rather than raising.
    state.commands.dispatch(state, "add_signal(plot_1, run_1, nope)")
    assert state.cells[0].signals == []


def test_plot_out_of_range_reported():
    state = _state_with_run()
    state.commands.dispatch(state, "add_signal(plot_9, run_1, ia)")
    assert all(not c.signals for c in state.cells)


def test_comment_and_blank_lines_ignored():
    state = _state_with_run()
    state.commands.dispatch(state, "# a comment")
    state.commands.dispatch(state, "   ")
    assert all(not c.signals for c in state.cells)


def test_format_call_is_canonical():
    state = _state_with_run()
    cmd = state.commands.get("set_x_lim")
    assert format_call(cmd, [1, 1.0, 2.0]) == "set_x_lim(plot_1, 1, 2)"
    cmd = state.commands.get("link_x")
    assert format_call(cmd, [True]) == "link_x(true)"


def test_default_grid_is_1x1():
    state = AppState()
    assert (state.rows, state.cols) == (1, 1)
    assert len(state.cells) == 1


def test_fft_panel_multi_source_and_clear():
    state = _state_with_run()
    state.commands.dispatch(state, "fft_source(run_1, ia)")
    state.commands.dispatch(state, "fft_source(run_1, ib)")
    state.commands.dispatch(state, "fft_source(run_1, ia)")  # dedup
    assert state.fft.sources == [(1, "ia"), (1, "ib")]
    state.commands.dispatch(state, "fft_clear")
    assert state.fft.sources == []


def test_completion_matches_prefix():
    state = _state_with_run()
    assert "set_x_lim" in state.commands.complete("set_x")
    assert state.commands.complete("") == []  # nothing to complete on an empty prefix
    # The registry completes on the command name (before the paren).
    assert state.commands.complete("set_grid(") == ["set_grid"]
