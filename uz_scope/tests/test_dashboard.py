"""Dashboard model: dash_* commands, bindings, persistence round-trip."""

from __future__ import annotations

import pytest

from uz_scope import dashboard
from uz_scope.config import ScopeConfig
from uz_scope.javascope_header import parse_header
from uz_scope.state import ScopeAppState


class FakeClient:
    def __init__(self) -> None:
        self.sent: list[tuple[int, float]] = []
        self.ack_pacing = True

        class _Ev:
            @staticmethod
            def is_set() -> bool:
                return True

        self.connected = _Ev()

    def send_command(self, data: bytes) -> None:
        from uz_scope.protocol import decode_command

        self.sent.append(decode_command(data))

    def stop(self, timeout: float = 0.0) -> None:
        pass


@pytest.fixture
def state(real_header_path, tmp_path):
    st = ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings.json",
    )
    st.client = FakeClient()
    return st


def run(state, line: str) -> None:
    state.commands.dispatch(state, line)


def errors(state) -> list[str]:
    return [e.message for e in state.console._entries if e.level == "ERROR"]


def test_add_uses_default_kind_and_label(state):
    run(state, "dash_add(auto, slowdata, JSSD_FLOAT_Milliseconds, 10, 20)")
    widgets = state.config.dashboard.widgets
    assert len(widgets) == 1
    w = widgets[0]
    assert w.id == 1 and w.kind == "readout"
    assert w.label == "Milliseconds"
    assert (w.x, w.y) == (10.0, 20.0)
    run(state, "dash_add(auto, send_field, 3, 0, 0)")
    assert state.config.dashboard.widgets[1].kind == "slider_send"
    run(state, "dash_add(auto, my_button, 2, 0, 0)")
    assert state.config.dashboard.widgets[2].kind == "button"
    run(state, "dash_add(auto, status_bit, 2, 0, 0)")
    assert state.config.dashboard.widgets[3].kind == "led"


def test_add_validates_binding_and_kind(state):
    run(state, "dash_add(auto, bogus, x, 0, 0)")
    assert any("binding must be" in e for e in errors(state))
    run(state, "dash_add(hologram, slowdata, x, 0, 0)")
    assert any("kind must be" in e for e in errors(state))
    assert not state.config.dashboard.widgets


def test_move_config_remove(state):
    run(state, "dash_add(gauge, slowdata, JSSD_FLOAT_Milliseconds, 0, 0)")
    run(state, "dash_move(1, 100, 50)")
    w = dashboard.widget_by_id(state, 1)
    assert (w.x, w.y) == (100.0, 50.0)
    run(state, "dash_config(1, max, 3000)")
    run(state, "dash_config(1, label, Speed)")
    run(state, "dash_config(1, fmt, %.0f rpm)")
    assert w.vmax == 3000.0 and w.label == "Speed" and w.fmt == "%.0f rpm"
    run(state, "dash_config(1, kind, progress)")
    assert w.kind == "progress"
    run(state, "dash_size(1, 200, 90)")
    assert (w.w, w.h) == (200.0, 90.0)
    run(state, "dash_remove(1)")
    assert not state.config.dashboard.widgets
    run(state, "dash_move(1, 0, 0)")
    assert any("no dashboard widget" in e for e in errors(state))


def test_read_value_and_indicator(state):
    import numpy as np

    idx = state.header.slowdata.index("JSSD_FLOAT_Milliseconds")
    raw = np.float32(1500.0).view(np.uint32)
    state.slowdata.on_block(
        np.array([[idx]], dtype=np.int32), np.array([[raw]], dtype=np.uint32)
    )
    run(state, "dash_add(readout, slowdata, JSSD_FLOAT_Milliseconds, 0, 0)")
    w = dashboard.widget_by_id(state, 1)
    assert dashboard.read_value(state, w) == pytest.approx(1500.0)

    run(state, "dash_add(led, status_bit, 2, 0, 0)")
    led = dashboard.widget_by_id(state, 2)
    state.last_status = 1 << 2
    assert dashboard.read_value(state, led) == 1.0

    run(state, "dash_add(button, my_button, 3, 0, 0)")
    btn = dashboard.widget_by_id(state, 3)
    state.last_status = 1 << (4 + 3 - 1)
    assert dashboard.indicator(state, btn) is True


def test_press_routes_through_commands(state):
    run(state, "dash_add(button, my_button, 2, 0, 0)")
    run(state, "dash_add(button, sys_button, Error_Reset, 0, 0)")
    dashboard.press(state, dashboard.widget_by_id(state, 1))
    dashboard.press(state, dashboard.widget_by_id(state, 2))
    sent_ids = [cmd_id for cmd_id, _ in state.client.sent]
    assert state.header.button_id["My_Button_2"] in sent_ids
    assert state.header.button_id["Error_Reset"] in sent_ids


def test_dashboard_config_roundtrip(state, tmp_path):
    run(state, "dash_add(gauge, slowdata, JSSD_FLOAT_Milliseconds, 15, 25)")
    run(state, "dash_config(1, max, 3000)")
    run(state, "dash_add(auto, send_field, 5, 40, 60)")
    path = tmp_path / "snap.json"
    state.config.save(path)
    loaded = ScopeConfig.load(path)
    assert loaded.dashboard.next_id == 3
    assert len(loaded.dashboard.widgets) == 2
    w = loaded.dashboard.widgets[0]
    assert w.kind == "gauge" and w.vmax == 3000.0 and (w.x, w.y) == (15.0, 25.0)
    assert loaded.dashboard.widgets[1].binding_key == "5"


def test_edit_overlay_receives_mouse_drag(real_header_path, tmp_path):
    """Field report: the edit overlay never got input because it sat in the
    parent window UNDER the widget child window.  Simulate a real drag."""
    from imgui_bundle import imgui, implot

    from uz_scope.panels.dashboard_panel import DashboardPanel

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1200, 800)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    try:
        state = ScopeAppState(
            config=ScopeConfig(),
            header=parse_header(real_header_path),
            settings_path=tmp_path / "settings.json",
        )
        state.commands.dispatch(
            state, "dash_add(readout, slowdata, JSSD_FLOAT_Milliseconds, 20, 20)"
        )
        panel = DashboardPanel()
        panel.edit_mode = True

        def frame():
            imgui.new_frame()
            imgui.set_next_window_pos(imgui.ImVec2(0, 0), imgui.Cond_.always)
            imgui.set_next_window_size(
                imgui.ImVec2(1100, 700), imgui.Cond_.always
            )
            imgui.begin("Dash")
            panel.render(state)
            imgui.end()
            imgui.render()

        frame()
        origin = panel._canvas_origin
        tx, ty = origin.x + 20 + 60, origin.y + 20 + 30  # inside the widget
        io.add_mouse_pos_event(tx, ty)
        frame()
        io.add_mouse_button_event(0, True)
        frame()
        for step in range(1, 6):  # 40 px right, past the drag threshold
            io.add_mouse_pos_event(tx + step * 8.0, ty)
            frame()
        io.add_mouse_button_event(0, False)
        frame()
        frame()

        w = state.config.dashboard.widgets[0]
        assert w.x > 25.0  # the overlay received the drag and moved it
        assert any(
            "dash_move" in e.message for e in state.console._entries
        )  # settled move echoed once
    finally:
        implot.destroy_context()
        imgui.destroy_context()


def test_headless_render_all_widget_kinds(real_header_path, tmp_path):
    from imgui_bundle import imgui, implot

    from uz_scope.config import WIDGET_KINDS
    from uz_scope.panels.dashboard_panel import DashboardPanel

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1500, 900)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    try:
        state = ScopeAppState(
            config=ScopeConfig(),
            header=parse_header(real_header_path),
            settings_path=tmp_path / "settings.json",
        )
        bindings = {
            "readout": ("slowdata", "JSSD_FLOAT_Milliseconds"),
            "gauge": ("slowdata", "JSSD_FLOAT_Milliseconds"),
            "progress": ("slowdata", "JSSD_FLOAT_Milliseconds"),
            "led": ("status_bit", "2"),
            "button": ("my_button", "1"),
            "toggle": ("my_button", "2"),
            "slider_send": ("send_field", "1"),
            "knob_send": ("send_field", "2"),
            "input_send": ("send_field", "3"),
        }
        for i, kind in enumerate(WIDGET_KINDS):
            btype, key = bindings[kind]
            state.commands.dispatch(
                state,
                f"dash_add({kind}, {btype}, {key}, {20 + 200 * (i % 4)}, "
                f"{20 + 110 * (i // 4)})",
            )
        panel = DashboardPanel()
        # With saved widgets the panel starts LIVE (Run mode) — starting in
        # Edit made all buttons dead after a restart (field report).
        imgui.new_frame()
        imgui.begin("Dashboard")
        panel.render(state)
        imgui.end()
        imgui.render()
        assert panel.edit_mode is False
        for edit in (True, False):  # both overlay and live paths
            panel.edit_mode = edit
            for _ in range(2):
                imgui.new_frame()
                imgui.begin("Dashboard")
                panel.render(state)
                imgui.end()
                imgui.render()
        assert len(state.config.dashboard.widgets) == len(WIDGET_KINDS)

        empty_panel = DashboardPanel()
        empty_state = ScopeAppState(
            config=ScopeConfig(),
            header=parse_header(real_header_path),
            settings_path=tmp_path / "settings_empty.json",
        )
        imgui.new_frame()
        imgui.begin("Dashboard2")
        empty_panel.render(empty_state)
        imgui.end()
        imgui.render()
        assert empty_panel.edit_mode is True  # empty canvas starts in Edit
    finally:
        implot.destroy_context()
        imgui.destroy_context()
