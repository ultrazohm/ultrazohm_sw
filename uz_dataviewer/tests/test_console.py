"""Headless render test for the console (selectable body + autoscroll + input)."""

from __future__ import annotations

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.state import AppState  # noqa: E402


def test_console_renders_and_logs_commands():
    from imgui_bundle import imgui, implot

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1000, 600)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures

    state = AppState()
    for i in range(50):
        state.console.command(f"set_x_lim(plot_1, {i}, {i + 1})")
    state.console.error("boom")

    try:
        for _ in range(3):
            imgui.new_frame()
            imgui.begin("Console")
            state.console.render(state)  # selectable multiline body, no checkboxes
            imgui.end()
            imgui.render()
    finally:
        implot.destroy_context()
        imgui.destroy_context()

    # The plain-text view used by the selectable body includes every line.
    text = state.console.as_text()
    assert "set_x_lim(plot_1, 49, 50)" in text
    assert "boom" in text


def test_console_follows_new_lines_but_preserves_history_scroll(app_state, gui_frame, monkeypatch):
    from imgui_bundle import imgui
    positions = []
    last_line_positions = []
    scroll_up = [False]
    begin_child = imgui.begin_child

    def capture(name, *args, **kwargs):
        result = begin_child(name, *args, **kwargs)
        if name == 'console_scroll':
            positions.append((imgui.get_scroll_y(), imgui.get_scroll_max_y()))
            if scroll_up[0]:
                imgui.set_scroll_y(0)
                scroll_up[0] = False
        return result

    monkeypatch.setattr(imgui, 'begin_child', capture)
    multiline = imgui.input_text_multiline

    def capture_text(label, text, *args, **kwargs):
        last_y = (imgui.get_cursor_screen_pos().y + imgui.get_style().frame_padding.y
                  + text.count('\n') * imgui.get_text_line_height())
        top = imgui.get_window_pos().y
        bottom = top + imgui.get_window_size().y
        last_line_positions.append((last_y, top, bottom))
        return multiline(label, text, *args, **kwargs)

    monkeypatch.setattr(imgui, 'input_text_multiline', capture_text)
    console = app_state.console
    for i in range(200):
        console.info(f'Initial message {i}')
    for _ in range(4):
        gui_frame(console, app_state)
    assert positions[-1][1] > 0
    assert positions[-1][0] >= positions[-1][1] - 2
    last_y, top, bottom = last_line_positions[-1]
    assert top <= last_y < bottom
    for i in range(20):
        console.info(f'New message {i}')
        gui_frame(console, app_state)
    for _ in range(2):
        gui_frame(console, app_state)
    assert positions[-1][0] >= positions[-1][1] - 2
    last_y, top, bottom = last_line_positions[-1]
    assert top <= last_y < bottom
    scroll_up[0] = True
    for _ in range(3):
        gui_frame(console, app_state)
    console.info('Stay in history')
    for _ in range(3):
        gui_frame(console, app_state)
    assert positions[-1][0] == 0
