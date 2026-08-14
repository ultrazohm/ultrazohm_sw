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
