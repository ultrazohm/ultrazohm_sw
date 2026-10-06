"""Regression tests for the v2 review findings (state/command/session layer)."""

from __future__ import annotations

import json

import pytest

from uz_scope.config import ScopeConfig
from uz_scope.javascope_header import parse_header
from uz_scope.session import export_script, run_script
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


def test_import_properties_rebuilds_logged_list(state, real_properties_path):
    run(state, f"import_properties({real_properties_path})")
    assert not errors(state)
    used = [
        s
        for s, ch in enumerate(state.config.channel_settings)
        if ch.observable != 0 or ch.visible
    ]
    assert used  # the legacy file assigns channels
    assert state.config.logged_slots == used
    # log_add must not overwrite an imported assignment.
    before = state.config.channel_settings[0].observable
    run(state, "log_add(30)")
    assert state.config.channel_settings[0].observable == before


def test_import_properties_refused_while_connected(state, real_properties_path):
    class FakeClient:
        pass

    state.client = FakeClient()
    channels_before = state.config.channels
    ip_before = state.config.ip
    run(state, f"import_properties({real_properties_path})")
    assert any("disconnect" in e for e in errors(state))
    # Config untouched — no half-applied import.
    assert state.config.channels == channels_before
    assert state.config.ip == ip_before
    state.client = None


def test_set_geometry_rejects_nonsense(state):
    for line in ("set_geometry(-5, 15)", "set_geometry(0, 15)",
                 "set_geometry(20, 0)"):
        run(state, line)
    assert len(errors(state)) == 3
    assert state.config.channels == 20
    assert len(state.config.channel_settings) == 20


def test_corrupt_settings_file_falls_back_to_defaults(real_header_path, tmp_path):
    path = tmp_path / "settings.json"
    path.write_text('{"channels": "twenty", "trigger": {"level": ', "utf-8")
    st = ScopeAppState(header=parse_header(real_header_path), settings_path=path)
    assert st.config.channels == 20  # defaults, no exception
    assert any("could not load" in e for e in errors(st))


def test_malformed_values_in_settings_are_skipped(tmp_path):
    cfg = ScopeConfig()
    import dataclasses

    data = dataclasses.asdict(cfg)
    data["channels"] = "twenty"       # bad int -> skipped
    data["ack_pacing"] = "false"      # string bool -> False, not truthy-True
    data["logged_slots"] = [1, "x", 3]
    path = tmp_path / "s.json"
    path.write_text(json.dumps(data), "utf-8")
    loaded = ScopeConfig.load(path)
    assert loaded.channels == 20
    assert loaded.ack_pacing is False
    assert loaded.logged_slots == [1, 3]


def test_cell_slots_are_always_logged(state, tmp_path):
    """Invariant: any slot in a plot cell is a logged variable."""
    run(state, "plot_grid(1, 1, 2)")
    run(state, "plot_assign(1, 2, 7)")
    assert 6 in state.config.logged_slots
    run(state, "ch_visible(4, on)")
    assert 3 in state.config.logged_slots
    # ...and the invariant is restored on load for older settings files.
    cfg = ScopeConfig()
    cfg.plots[0].cells[0] = [5]
    cfg.logged_slots = []
    import dataclasses

    path = tmp_path / "s.json"
    path.write_text(json.dumps(dataclasses.asdict(cfg)), "utf-8")
    assert 5 in ScopeConfig.load(path).logged_slots


def test_history_dir_in_ram_mode_keeps_envelope(state):
    import numpy as np

    state.history.on_block(np.ones((20, 100), dtype=np.float32), 0)
    assert state.history.total_end == 100
    run(state, "history_dir(/tmp/somewhere)")
    assert state.history.total_end == 100  # envelope survived


def test_script_replay_onto_nonempty_dashboard_is_safe(
    state, real_header_path, tmp_path
):
    run(state, "dash_add(gauge, slowdata, JSSD_FLOAT_Milliseconds, 10, 10)")
    run(state, "dash_config(1, label, Original)")
    path = export_script(state, tmp_path / "s.uzscript")

    other = ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings2.json",
    )
    run(other, "dash_add(readout, slowdata, JSSD_FLOAT_Milliseconds, 0, 0)")
    run(other, "dash_config(1, label, Preexisting)")
    run_script(other, path)
    # Replay is deterministic: the script's dash_clear resets the canvas,
    # so the exported widget lands with its exact id/label — never a silent
    # reconfiguration of an unrelated pre-existing widget.
    assert not errors(other)
    assert len(other.config.dashboard.widgets) == 1
    w = other.config.dashboard.widgets[0]
    assert w.id == 1 and w.label == "Original" and w.kind == "gauge"


def test_script_quotes_in_labels_survive_replay(state, real_header_path, tmp_path):
    run(state, "dash_add(readout, slowdata, JSSD_FLOAT_Milliseconds, 0, 0)")
    state.config.dashboard.widgets[0].label = 'Torque "raw" (Nm)'
    state.config.plots[0].title = 'My "main" scope'
    path = export_script(state, tmp_path / "s.uzscript")

    fresh = ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings3.json",
    )
    run_script(fresh, path)
    assert not errors(fresh)  # every line parsed and executed
    assert fresh.config.dashboard.widgets[0].label == "Torque 'raw' (Nm)"


def test_export_includes_keep_and_autoconnect(state, tmp_path):
    state.config.history.keep_files = True
    state.config.auto_connect = True
    text = "\n".join(
        __import__("uz_scope.session", fromlist=["export_script_lines"])
        .export_script_lines(state)
    )
    assert "history_keep(true)" in text
    assert "auto_connect(true)" in text
    assert text.index("history_dir") < text.index("history_mode")
