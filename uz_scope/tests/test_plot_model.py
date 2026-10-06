"""Plot-window model: grid reflow, cell assignment, x-modes, view state."""

from __future__ import annotations

import pytest

from uz_scope.config import ScopeConfig, X_MODE_CONT
from uz_scope.javascope_header import parse_header
from uz_scope.state import ScopeAppState


@pytest.fixture
def state(real_header_path, tmp_path):
    return ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings.json",
    )


def run(state, line: str) -> None:
    state.commands.dispatch(state, line)


def errors(state) -> list[str]:
    return [e.message for e in state.console._entries if e.level == "ERROR"]


def test_default_config_has_one_plot_window(state):
    assert len(state.config.plots) == 1
    win = state.config.plots[0]
    assert win.title == "Scope" and (win.rows, win.cols) == (1, 1)
    assert win.cells == [[]]


def test_visible_flag_mirrors_cell_membership(state):
    run(state, "ch_visible(3, on)")
    assert state.config.plots[0].cells[0] == [2]
    assert state.config.channel_settings[2].visible
    run(state, "ch_visible(3, off)")
    assert state.config.plots[0].cells[0] == []
    assert not state.config.channel_settings[2].visible
    # Showing a slot logged it (slot 2 stays in the pool when hidden), and
    # enable_all shows every *logged* channel (not all 20 raw slots).
    assert state.config.logged_slots == [2]
    run(state, "log_add(4)")
    run(state, "log_add(5)")
    run(state, "enable_all(on)")
    assert sorted(state.config.plots[0].cells[0]) == [0, 1, 2]
    run(state, "enable_all(off)")
    assert state.config.plots[0].cells[0] == []


def test_plot_assign_unassign_and_sync(state):
    run(state, "plot_assign(1, 1, 5)")
    assert state.config.channel_settings[4].visible  # win 1 cell 1 == visible
    run(state, "plot_grid(1, 2, 2)")
    run(state, "plot_assign(1, 4, 5)")
    assert state.config.plots[0].cells[3] == [4]
    run(state, "plot_unassign(1, 4, 5)")
    assert state.config.plots[0].cells[3] == []
    assert state.config.channel_settings[4].visible  # cell 4 doesn't sync


def test_grid_reflow_merges_extra_cells(state):
    run(state, "plot_grid(1, 2, 2)")
    run(state, "plot_assign(1, 1, 1)")
    run(state, "plot_assign(1, 3, 2)")
    run(state, "plot_assign(1, 4, 3)")
    run(state, "plot_grid(1, 1, 2)")
    win = state.config.plots[0]
    assert len(win.cells) == 2
    assert win.cells[0] == [0]
    assert set(win.cells[1]) == {1, 2}  # merged from the removed cells


def test_plot_add_remove_and_view_shift(state):
    run(state, "plot_add()")
    run(state, "plot_add(Bench)")
    assert [w.title for w in state.config.plots] == ["Scope", "Scope 2", "Bench"]
    state.plot_view(3).attached = False
    run(state, "plot_remove(2)")
    assert [w.title for w in state.config.plots] == ["Scope", "Bench"]
    assert not state.plot_view(2).attached  # view followed its window
    run(state, "plot_remove(1)")
    assert errors(state)  # window 1 is permanent
    assert len(state.config.plots) == 2


def test_xmode_and_follow_commands(state):
    run(state, "plot_xmode(1, cont)")
    assert state.config.plots[0].x_mode == X_MODE_CONT
    assert state.config.plots[0].window_seconds() is None
    run(state, "plot_xmode(1, 2.5)")
    assert state.config.plots[0].x_mode == "2.5"
    assert state.config.window_seconds == 2.5  # window 1 keeps the legacy field
    run(state, "set_window(0.1)")
    assert state.config.plots[0].x_mode == "0.1"
    run(state, "x_lim(1, 1.0, 2.0)")
    view = state.plot_view(1)
    assert not view.attached and view.pending_x == (1.0, 2.0)
    run(state, "plot_follow(1, on)")
    assert view.attached and view.pending_x is None
    run(state, "plot_xmode(1, bogus)")
    assert errors(state)


def test_x_lim_validation(state):
    run(state, "x_lim(1, 2.0, 1.0)")
    assert errors(state)
    run(state, "x_lim(9, 0.0, 1.0)")
    assert any("out of range" in e for e in errors(state))


def test_plots_config_roundtrip(state, tmp_path):
    run(state, "plot_grid(1, 1, 2)")
    run(state, "plot_assign(1, 2, 7)")
    run(state, "plot_add(Bench)")
    run(state, "plot_xmode(2, cont)")
    run(state, "plot_link_x(2, on)")
    path = tmp_path / "snap.json"
    state.config.save(path)
    loaded = ScopeConfig.load(path)
    assert len(loaded.plots) == 2
    assert loaded.plots[0].cells[1] == [6]
    assert loaded.plots[1].title == "Bench"
    assert loaded.plots[1].x_mode == X_MODE_CONT
    assert loaded.plots[1].link_x


def test_legacy_settings_migrate_visible_flags(tmp_path):
    cfg = ScopeConfig()
    cfg.channel_settings[1].visible = True
    cfg.channel_settings[5].visible = True
    cfg.window_seconds = 2.5
    import dataclasses, json

    data = dataclasses.asdict(cfg)
    del data["plots"]  # simulate a pre-v2 settings file
    del data["history"]
    path = tmp_path / "old.json"
    path.write_text(json.dumps(data), encoding="utf-8")
    loaded = ScopeConfig.load(path)
    assert loaded.plots[0].cells[0] == [1, 5]
    assert loaded.plots[0].x_mode == "2.5"
    assert loaded.history.mode == "ram"
