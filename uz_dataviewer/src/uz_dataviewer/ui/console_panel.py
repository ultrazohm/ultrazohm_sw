"""Bottom console: filterable, auto-scrolling log of loader/UI events."""

from __future__ import annotations

from imgui_bundle import imgui

from uz_dataviewer.core.console import LogLevel
from uz_dataviewer.ui.app_state import AppState

LEVEL_FILTERS = (
    ("All", LogLevel.DEBUG),
    ("Info", LogLevel.INFO),
    ("Warnings", LogLevel.WARNING),
    ("Errors", LogLevel.ERROR),
)

LEVEL_COLORS = {
    LogLevel.DEBUG: imgui.ImVec4(0.6, 0.6, 0.6, 1.0),
    LogLevel.INFO: imgui.ImVec4(0.85, 0.85, 0.85, 1.0),
    LogLevel.WARNING: imgui.ImVec4(0.95, 0.75, 0.2, 1.0),
    LogLevel.ERROR: imgui.ImVec4(0.95, 0.35, 0.35, 1.0),
}


class ConsolePanel:
    def __init__(self, state: AppState):
        self.state = state
        self.filter_index = 0
        self.auto_scroll = True
        self._last_revision = -1

    def render(self) -> None:
        console = self.state.console

        imgui.set_next_item_width(110)
        if imgui.begin_combo("##level", LEVEL_FILTERS[self.filter_index][0]):
            for index, (label, _) in enumerate(LEVEL_FILTERS):
                if imgui.selectable(label, index == self.filter_index)[0]:
                    self.filter_index = index
            imgui.end_combo()
        imgui.same_line()
        _, self.auto_scroll = imgui.checkbox("Auto-scroll", self.auto_scroll)
        imgui.same_line()
        if imgui.button("Clear"):
            console.clear()

        imgui.separator()
        imgui.begin_child("console_scroll")
        min_level = LEVEL_FILTERS[self.filter_index][1]
        for entry in console.entries(min_level):
            imgui.push_style_color(imgui.Col_.text, LEVEL_COLORS[entry.level])
            imgui.text_unformatted(entry.format())
            imgui.pop_style_color()

        revision = console.revision
        if self.auto_scroll and revision != self._last_revision:
            imgui.set_scroll_here_y(1.0)
        self._last_revision = revision
        imgui.end_child()
