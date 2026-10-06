"""Command dispatch against a ScopeAppState with a fake client (no sockets)."""

from __future__ import annotations

import numpy as np
import pytest

from uz_scope.config import ScopeConfig
from uz_scope.javascope_header import parse_header
from uz_scope.protocol import decode_command
from uz_scope.state import ScopeAppState


class FakeClient:
    def __init__(self) -> None:
        from uz_scope.netclient import NetStats

        self.sent: list[tuple[int, float]] = []
        self.ack_pacing = True
        self.stats = NetStats()

        class _Ev:
            @staticmethod
            def is_set() -> bool:
                return True

        self.connected = _Ev()

    def send_command(self, data: bytes) -> None:
        self.sent.append(decode_command(data))

    def stop(self, timeout: float = 0.0) -> None:
        pass


@pytest.fixture
def state(real_header_path, tmp_path):
    cfg = ScopeConfig()
    st = ScopeAppState(
        config=cfg,
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings.json",
    )
    st.client = FakeClient()
    return st


def run(state, line: str) -> None:
    state.commands.dispatch(state, line)


def errors(state) -> list[str]:
    return [e.message for e in state.console._entries if e.level == "ERROR"]


def test_connect_arguments_are_one_off(state, monkeypatch):
    state.client = None
    calls = []
    monkeypatch.setattr(
        state, "connect", lambda ip=None, port=None: calls.append((ip, port))
    )

    run(state, "connect(10.0.0.9, 5555)")
    # An explicit target must NOT clobber the saved UltraZohm default.
    assert state.config.ip == "192.168.1.233"
    assert state.config.port == 1000
    assert calls == [("10.0.0.9", 5555)]

    run(state, "connect")  # bare connect -> the saved default
    assert calls[-1] == (None, None)
    assert not errors(state)

    # set_ip remains the way to change the saved default.
    run(state, "set_ip(10.1.1.1)")
    assert state.config.ip == "10.1.1.1"


def test_cli_override_is_session_only(state):
    state.client = None
    state.ip_override = "127.0.0.1"
    state.port_override = 5555

    captured = {}

    class FakeScopeClient:
        def __init__(self, geometry, ip, port, **kw):
            captured["target"] = (ip, port)
            self.ip, self.port = ip, port

        def start(self):
            pass

        def stop(self, timeout=0.0):
            pass

    import uz_scope.state as state_mod

    orig = state_mod.ScopeClient
    state_mod.ScopeClient = FakeScopeClient
    try:
        state.connect()
        assert captured["target"] == ("127.0.0.1", 5555)  # override used...
        assert state.config.ip == "192.168.1.233"  # ...but never persisted
    finally:
        state_mod.ScopeClient = orig
        state.client = None


def test_state_machine_commands_use_header_ids(state):
    run(state, "enable_system")
    run(state, "enable_control")
    run(state, "stop_system")
    run(state, "error_reset")
    assert state.client.sent == [(1, 1.0), (2, 1.0), (3, 1.0), (32, 1.0)]


def test_my_button_and_send_field(state):
    run(state, "my_button(2)")
    run(state, "send_field(1, 42.5)")
    run(state, "send_field(20, -1)")
    assert state.client.sent == [(25, 1.0), (4, 42.5), (23, -1.0)]


def test_my_button_range_checked(state):
    run(state, "my_button(9)")
    assert state.client.sent == []
    assert errors(state)


def test_ch_select_by_name_and_index(state):
    run(state, "ch_select(1, JSO_lifecheck)")
    assert state.config.channel_settings[0].observable == 3
    run(state, "ch_select(2, lifecheck)")  # JSO_ prefix optional
    assert state.config.channel_settings[1].observable == 3
    run(state, "ch_select(3, 4)")
    assert state.config.channel_settings[2].observable == 4
    # channel-select wire ids are 201-based
    assert state.client.sent == [(201, 3.0), (202, 3.0), (203, 4.0)]


def test_ch_select_unknown_observable(state):
    run(state, "ch_select(1, JSO_NOPE)")
    assert errors(state)
    assert state.client.sent == []


def test_visibility_scale_offset(state):
    run(state, "ch_visible(5, on)")
    run(state, "ch_scale(5, 2.5)")
    run(state, "ch_offset(5, -1.5)")
    ch = state.config.channel_settings[4]
    assert ch.visible is True and ch.scale == 2.5 and ch.offset == -1.5
    run(state, "enable_all(false)")
    assert not any(c.visible for c in state.config.channel_settings)


def test_display_commands(state):
    run(state, "stop_scope")
    assert state.frozen is True
    run(state, "run")
    assert state.frozen is False
    run(state, "set_window(2.5)")
    assert state.config.window_seconds == 2.5
    run(state, "fix_axis(on)")
    assert state.fix_axis is True


def test_geometry_requires_disconnect(state):
    run(state, "set_geometry(200, 15)")
    assert errors(state)  # still "connected" via the fake
    state.client = None
    run(state, "set_geometry(200, 15)")
    assert state.config.channels == 200
    assert len(state.config.channel_settings) == 200
    assert state.ring.channels == 200


def test_timestep_and_ring(state):
    run(state, "set_timestep(10)")  # rejected: still connected
    assert errors(state)
    assert state.sample_rate == pytest.approx(1e4)
    state.client = None
    run(state, "set_timestep(10)")  # 100 kHz
    assert state.sample_rate == pytest.approx(1e5)
    assert state.ring.capacity > 0


def test_log_roundtrip_through_commands(state, tmp_path):
    state.config.logging.directory = str(tmp_path)
    run(state, "log_format(csv)")
    assert state.config.logging.format == "csv"
    run(state, "log_start")
    assert state.logger is not None
    # Push one parsed-like block through the reader-thread path.
    samples = np.zeros((2, 20, 15), dtype=np.float32)

    class P:
        pass

    parsed = P()
    parsed.samples = samples
    parsed.status = np.array([0, 5], dtype=np.uint32)
    parsed.slow_id = np.zeros((2, 15), dtype=np.int32)
    parsed.slow_raw = np.zeros((2, 15), dtype=np.uint32)
    state._on_frames(parsed)
    assert state.last_status == 5
    run(state, "log_stop")
    assert state.logger is None
    files = list(tmp_path.glob("*.csv"))
    assert len(files) == 1


def test_log_format_validation(state):
    run(state, "log_format(xlsx)")
    assert state.config.logging.format == "parquet"
    assert errors(state)


def make_parsed(status_value: int):
    class P:
        pass

    parsed = P()
    parsed.samples = np.zeros((1, 20, 15), dtype=np.float32)
    parsed.status = np.array([status_value], dtype=np.uint32)
    parsed.slow_id = np.zeros((1, 15), dtype=np.int32)
    parsed.slow_raw = np.zeros((1, 15), dtype=np.uint32)
    return parsed


def test_ext_log_trigger_on_status_bit_12(state, tmp_path):
    state.config.logging.directory = str(tmp_path)
    run(state, "ext_log(on)")
    state._on_frames(make_parsed(0))
    assert state.logger is None
    state._on_frames(make_parsed(1 << 12))  # rising edge -> start
    assert state.logger is not None
    state._on_frames(make_parsed(1 << 12))  # level, no change
    assert state.logger is not None
    state._on_frames(make_parsed(0))  # falling edge -> stop
    assert state.logger is None
    state.poll_events()
    assert list(tmp_path.glob("*.parquet"))


def test_trigger_commands_and_capture(state):
    state.config.channel_settings[0].visible = True
    run(state, "trig_mode(single)")
    run(state, "trig_level(0.5)")
    run(state, "trig_pretrigger(0)")
    run(state, "set_window(0.001)")  # 10 samples at 10 kHz
    run(state, "trig_arm(on)")
    assert state.engine is not None
    # Stream a step through the reader path: 30 zero samples then ones.
    for value, count in ((0.0, 2), (1.0, 4)):
        for _ in range(count):
            parsed = make_parsed(0)
            parsed.samples[:] = value
            state._on_frames(parsed)
    assert state.engine.capture is not None
    assert state.engine.capture.trigger_index == 30
    run(state, "trig_arm(off)")
    assert state.engine is None


def test_import_properties_command(state, real_properties_path):
    state.client = None
    run(state, f"import_properties({real_properties_path})")
    assert state.config.ack_pacing is False
    assert state.config.channel_settings[3].observable == 46


def test_rate_detection_snaps_and_rounds(state, monkeypatch):
    import uz_scope.state as state_mod

    # Shrink the probe windows so the test runs instantly.
    monkeypatch.setattr(state_mod, "RATE_DETECT_DELAY_S", 0.0)
    monkeypatch.setattr(state_mod, "RATE_DETECT_WINDOW_S", 0.0)
    client = state.client
    client.stats = type("S", (), {})()
    client.stats.connected_since = 0.0
    client.stats.samples = 0

    # Within 5% of nominal 10 kHz -> snapped to nominal.
    state._rate_probe = (0.0, 0)

    class Clock:
        now = 10.0

    monkeypatch.setattr(state_mod.time, "monotonic", lambda: Clock.now)
    client.stats.samples = 102_000  # 10.2 kHz measured over 10 s
    state._poll_rate_detect()
    assert state.detected_rate == pytest.approx(10_000.0)

    # Far off nominal -> rounded to the nearest kHz.
    state.detected_rate = None
    state._rate_probe = (10.0, 102_000)
    Clock.now = 20.0
    client.stats.samples = 102_000 + 872_000  # 87.2 kHz over 10 s
    state._poll_rate_detect()
    assert state.detected_rate == pytest.approx(87_000.0)

    # Clamped to 200 kHz.
    state.detected_rate = None
    state._rate_probe = (20.0, 974_000)
    Clock.now = 30.0
    client.stats.samples = 974_000 + 5_000_000  # 500 kHz over 10 s
    state._poll_rate_detect()
    assert state.detected_rate == pytest.approx(200_000.0)


def test_lifecheck_slot_follows_channel_select(state):
    # Header maps JSO_lifecheck to index 3; slot 2 of properties defaults isn't it.
    assert state.header.observable_index["JSO_lifecheck"] == 3
    run(state, "ch_select(7, JSO_lifecheck)")
    assert state._lifecheck_slot == 6
    run(state, "ch_select(7, JSO_ADC_A1_CH0)")
    assert state._lifecheck_slot is None


def test_settings_saved_on_shutdown(state, tmp_path):
    state.config.ip = "10.1.2.3"
    state.shutdown()
    assert state.settings_path.exists()
    from uz_scope.config import ScopeConfig as SC

    assert SC.load(state.settings_path).ip == "10.1.2.3"
