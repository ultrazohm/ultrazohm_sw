"""Exercise the flash modal with real ImGui mouse input."""

from dataclasses import replace
from types import SimpleNamespace

import pytest

from ultrazohm_dataviewer.live import LiveController
from ultrazohm_dataviewer.panels.live import LiveWorkspace


@pytest.mark.parametrize(
    "action,busy", [("OK", False), ("Cancel", False), ("Cancel", True)]
)
def test_flash_dialog_layout_and_buttons(
    gui_frame, app_state, monkeypatch, action, busy
):
    from imgui_bundle import imgui

    controller = LiveController()
    controller.endpoint = "127.0.0.1:19742"
    workspace = LiveWorkspace(controller)
    workspace.available = workspace.flash_available = True
    workspace.update = replace(workspace.update, attached=True)
    sent, positions, opened, sizes = [], {}, [], []
    monkeypatch.setattr(controller, "submit", lambda op, **kw: sent.append((op, kw)))
    original_button = imgui.button

    def button(label, *args, **kwargs):
        result = original_button(label, *args, **kwargs)
        if label in ("Flash UZ", "OK", "Cancel"):
            lo, hi = imgui.get_item_rect_min(), imgui.get_item_rect_max()
            positions[label] = ((lo.x + hi.x) / 2, (lo.y + hi.y) / 2)
        if label == "Cancel":
            size = imgui.get_window_size()
            sizes.append((size.x, size.y))
        return result

    monkeypatch.setattr(imgui, "button", button)

    def render(state):
        imgui.begin_child("Live panel", imgui.ImVec2(320, 650))
        workspace.render_data(state)
        opened.append(imgui.is_popup_open("Flash UltraZohm?"))
        imgui.end_child()

    panel = SimpleNamespace(render=render)

    def frame():
        gui_frame(panel, app_state)

    def click(label):
        io = imgui.get_io()
        io.add_mouse_pos_event(*positions[label])
        frame()
        io.add_mouse_button_event(0, True)
        frame()
        io.add_mouse_button_event(0, False)
        frame()

    try:
        for _ in range(3):
            frame()
        click("Flash UZ")
        for _ in range(3):
            frame()
        assert opened[-1]
        width, height = sizes[-1]
        assert 300 <= width <= 900
        assert height < 400
        for label in ("OK", "Cancel"):
            x, y = positions[label]
            assert 0 < x < 1000 and 0 < y < 800
        if busy:
            monkeypatch.setattr(workspace, "block_reason", lambda *args: "Busy")
            frame()
        click(action)
        frame()
        assert not opened[-1]
        assert [op for op, _ in sent] == (["flash"] if action == "OK" else [])
        if sent:
            assert sent[0][1]["endpoint"] == controller.endpoint
    finally:
        workspace.close()
