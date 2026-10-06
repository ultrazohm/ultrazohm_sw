from __future__ import annotations

import numpy as np
import pytest

from uz_scope2.config import ScopeConfig
from uz_scope2.javascope_header import parse_header
from uz_scope2.session import export_script, export_script_lines, run_script
from uz_scope2.state import ScopeAppState

loader = pytest.importorskip("uz_dataviewer.loader")


@pytest.fixture
def state(real_header_path, tmp_path):
    return ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings.json",
    )


def test_script_roundtrip_reproduces_config(state, real_header_path, tmp_path):
    state.config.ip = "10.9.8.7"
    state.config.channel_settings[2].visible = True
    state.config.channel_settings[2].observable = 46
    state.config.channel_settings[2].scale = 4.0
    state.config.trigger.edge = "falling"
    state.config.trigger.level = 1.25
    state.config.logging.format = "csv"
    path = export_script(state, tmp_path / "session.uzscript")

    fresh = ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings2.json",
    )
    count = run_script(fresh, path)
    assert count > 10
    assert fresh.config.ip == "10.9.8.7"
    ch = fresh.config.channel_settings[2]
    assert ch.visible is True and ch.observable == 46 and ch.scale == 4.0
    assert fresh.config.trigger.edge == "falling"
    assert fresh.config.trigger.level == 1.25
    assert fresh.config.logging.format == "csv"
    # No errors surfaced during replay.
    assert not [e for e in fresh.console._entries if e.level == "ERROR"]


def test_script_contains_no_connect(state):
    lines = export_script_lines(state)
    assert not any(line.startswith("connect") for line in lines)


def test_save_and_load_state_commands(state, tmp_path):
    state.config.window_seconds = 2.5
    state.commands.dispatch(state, f"save_state({tmp_path / 'snap.json'})")
    state.config.window_seconds = 0.5
    state.commands.dispatch(state, f"load_state({tmp_path / 'snap.json'})")
    assert state.config.window_seconds == 2.5
    assert state.config.trigger.enabled is False


def test_load_state_requires_disconnect(state, tmp_path):
    state.config.save(tmp_path / "snap.json")

    class FakeClient:
        pass

    state.client = FakeClient()
    state.commands.dispatch(state, f"load_state({tmp_path / 'snap.json'})")
    assert [e for e in state.console._entries if e.level == "ERROR"]
    state.client = None


def test_export_capture_roundtrip(state, tmp_path):
    state.config.trigger.mode = "single"
    state.config.trigger.pretrigger = 0.0
    state.config.window_seconds = 0.005  # 50 samples at 10 kHz
    state.config.channel_settings[0].visible = True
    state.arm_trigger()
    step = np.concatenate([np.full(30, -1.0), np.ones(100)]).astype(np.float32)
    start = state.ring.total_written
    state.ring.append(np.tile(step, (20, 1)))
    state.engine.on_block(step, start)
    assert state.engine.capture is not None

    out = tmp_path / "cap.parquet"
    state.commands.dispatch(state, f"export_capture({out})")
    run = loader.parse_file(str(out))
    assert len(run.time) == state.engine.capture.data.shape[1]
    assert len(run.signals) == 20
    assert state.last_log_path == out


def test_export_capture_without_capture_errors(state, tmp_path):
    state.commands.dispatch(state, f"export_capture({tmp_path / 'x.parquet'})")
    assert [e for e in state.console._entries if e.level == "ERROR"]


def test_open_in_dataviewer_missing_file(state):
    state.commands.dispatch(state, "open_in_dataviewer(/nonexistent.parquet)")
    assert [e for e in state.console._entries if e.level == "ERROR"]
