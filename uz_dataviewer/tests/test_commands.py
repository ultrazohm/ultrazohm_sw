"""Tests for the command layer: parsing, coercion and dispatch (no GUI)."""

from __future__ import annotations

import numpy as np
import pytest
import copy



from uz_dataviewer.commands import CommandError, _fmt_str, format_call, parse_call
from uz_dataviewer.state import AppState, PlotType
from uz_dataviewer.session import to_dict


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
    assert format_call(cmd, [1, 1.0, 2.0]) == "set_x_lim(plot_1, 1.0, 2.0)"
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


@pytest.mark.parametrize('command', ['set_x_lim', 'set_y_lim', 'fft_xlim', 'hist_xlim'])
@pytest.mark.parametrize('limits', [(5, 2), (1, 1), (float('nan'), 2), (0, float('inf'))])
def test_invalid_axis_limits_do_not_mutate_state(app_state, command, limits):
    from uz_dataviewer.session import to_dict
    state = app_state
    before = to_dict(state)
    args = [1, *limits] if command.startswith('set_') else list(limits)
    with pytest.raises(ValueError):
        state.commands.execute(state, command, args)
    assert to_dict(state) == before
    assert state.fft.pending_x_lim is None and state.histogram.pending_x_lim is None


def test_clear_plot_removes_secondary_assignments(app_state, tmp_path):
    from uz_dataviewer.session import apply_dict, to_dict
    state = app_state
    path = tmp_path / 'clear.csv'
    path.write_text('time;a\n0;1\n1;2\n')
    state.load_sync(str(path))
    state.commands.execute(state, 'add_signal', [1, 1, 'a'])
    state.commands.execute(state, 'set_axis', [1, 1, 'a', 'right'])
    state.commands.execute(state, 'clear_plot', [1])
    assert not state.cells[0].signals and not state.cells[0].y2_signals
    apply_dict(state, to_dict(state))
    state.commands.execute(state, 'add_signal', [1, 1, 'a'])
    assert not state.cells[0].y2_signals


@pytest.mark.parametrize('value', ['a"b.csv', '', "a'b.csv", ' leading ', r'C:\logs\a.csv', 'comma,name'])
def test_script_string_roundtrip(value):
    assert parse_call('load('+_fmt_str(value)+')')[1] == [value]


def test_unterminated_quote_rejected():
    with pytest.raises(CommandError):
        parse_call('load("incomplete)')


@pytest.mark.parametrize('command,args', [
    ('set_grid', [0, 1]), ('set_grid', [1000000, 1]),
    ('set_max_points', [2147483648]), ('cache_budget', [2147483648]),
    ('set_cursors', [1, float('inf'), 1]),
    ('set_spy_rect', [1, 2, 0, 1, 1]),
])
def test_invalid_command_is_atomic(app_state, command, args):
    before = copy.deepcopy(to_dict(app_state))
    with pytest.raises(ValueError):
        app_state.commands.execute(app_state, command, args)
    assert to_dict(app_state) == before


def test_xy_rejection_preserves_plot_and_clear_releases_hidden_source(app_state):
    from uz_dataviewer import nodes
    s = app_state
    run = s.registry.add_run('input', 'input', np.arange(8.), {'a': np.ones(8)}, {})
    source = s.nodes.add('source', ref=(run.id, 'a'))
    fft = s.nodes.add('fft')
    s.nodes.link(source.id, fft.id)
    nodes.evaluate(s)
    execute = lambda command, *args: s.commands.execute(s, command, list(args))
    execute('add_signal', 1, run.id, 'a')
    execute('set_x_lim', 1, 1, 5)
    before = copy.deepcopy(s.cells[0])
    with pytest.raises(CommandError, match='axis domain'):
        execute('set_xy', 1, fft.out_run_id, 'out')
    assert s.cells[0] == before
    execute('set_xy', 1, run.id, 'a')
    execute('set_plot_type', 1, 'line')
    execute('remove_signal', 1, run.id, 'a')
    execute('add_signal', 1, fft.out_run_id, 'out')
    assert s.plot_domain(s.cells[0]) == 'frequency'
    execute('set_plot_type', 1, 'xy')
    assert s.cells[0].xy_source is None
    execute('set_xy', 1, fft.out_run_id, 'out')
    execute('clear_plot', 1)
    assert not s.cells[0].signals and s.cells[0].xy_source is None
