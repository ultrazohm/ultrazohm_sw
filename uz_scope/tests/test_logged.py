"""Logged-variables model: slot pool, cell purge, migration, script compat."""

from __future__ import annotations

import dataclasses
import json

import pytest

from uz_scope.config import ScopeConfig
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


def test_log_add_takes_first_free_slot(state):
    run(state, "log_add(lifecheck)")
    assert state.config.logged_slots == [0]
    idx = state.header.observable_index["JSO_lifecheck"]
    assert state.config.channel_settings[0].observable == idx
    run(state, "log_add(4)")
    assert state.config.logged_slots == [0, 1]
    assert state.config.channel_settings[1].observable == 4


def test_log_add_deduplicates(state):
    run(state, "log_add(4)")
    run(state, "log_add(4)")
    assert state.config.logged_slots == [0]  # no second slot burned


def test_log_add_errors_when_pool_full(state):
    for obs in range(1, 21):
        run(state, f"log_add({obs})")
    assert len(state.config.logged_slots) == 20
    run(state, "log_add(30)")
    assert any("slots are in use" in e for e in errors(state))
    assert len(state.config.logged_slots) == 20


def test_log_remove_frees_slot_and_purges_cells(state):
    run(state, "log_add(4)")
    run(state, "log_add(5)")
    run(state, "ch_visible(1, on)")
    run(state, "plot_add()")
    run(state, "plot_assign(2, 1, 1)")
    run(state, "log_remove(1)")
    assert state.config.logged_slots == [1]
    assert not state.config.channel_settings[0].visible
    for win in state.config.plots:
        for cell in win.cells:
            assert 0 not in cell
    # The freed slot is reused by the next add.
    run(state, "log_add(6)")
    assert state.config.logged_slots == [1, 0]


def test_log_remove_unknown_slot_errors(state):
    run(state, "log_remove(3)")
    assert any("not in the logged list" in e for e in errors(state))


def test_ch_select_scripts_recreate_logged_list(state):
    """Old ch_select scripts keep working and rebuild the logged list."""
    run(state, "ch_select(5, 7)")
    assert state.config.logged_slots == [4]
    assert state.history.valid_from[4] == 0  # epoch noted (empty session)


def test_logged_slots_config_roundtrip(state, tmp_path):
    run(state, "log_add(4)")
    run(state, "log_add(7)")
    path = tmp_path / "snap.json"
    state.config.save(path)
    loaded = ScopeConfig.load(path)
    assert loaded.logged_slots == [0, 1]


def test_legacy_settings_migrate_used_slots(tmp_path):
    cfg = ScopeConfig()
    cfg.channel_settings[2].observable = 9
    cfg.channel_settings[6].visible = True
    data = dataclasses.asdict(cfg)
    del data["logged_slots"]  # simulate a pre-v2 settings file
    path = tmp_path / "old.json"
    path.write_text(json.dumps(data), encoding="utf-8")
    loaded = ScopeConfig.load(path)
    assert loaded.logged_slots == [2, 6]


def test_ch_color_command(state):
    run(state, "ch_color(2, #ff8800)")
    assert state.config.channel_settings[1].color == "#ff8800"
    run(state, "ch_color(2, auto)")
    assert state.config.channel_settings[1].color is None
    run(state, "ch_color(2, red)")
    assert errors(state)
