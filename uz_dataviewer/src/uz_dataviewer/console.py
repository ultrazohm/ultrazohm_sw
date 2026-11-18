"""Application activity log; execution belongs to Python scripts and the CLI."""

from __future__ import annotations

import time
from collections import deque
from dataclasses import dataclass
from typing import TYPE_CHECKING


if TYPE_CHECKING:  # pragma: no cover - typing only
    from .state import AppState



@dataclass
class LogEntry:
    timestamp: str
    level: str
    message: str


class Console:
    """Read-only ring buffer of application activity, rendered in one panel."""

    def __init__(self, max_lines: int = 2000) -> None:
        self._entries: deque[LogEntry] = deque(maxlen=max_lines)
        self._scroll_to_bottom = False

    # -- logging API --------------------------------------------------------
    def _log(self, level: str, message: str) -> None:
        stamp = time.strftime("%H:%M:%S")
        self._entries.append(LogEntry(stamp, level, message))
        self._scroll_to_bottom = True

    def info(self, message: str) -> None:
        self._log("INFO", message)

    def ok(self, message: str) -> None:
        self._log("OK", message)

    def warn(self, message: str) -> None:
        self._log("WARN", message)

    def error(self, message: str) -> None:
        self._log("ERROR", message)

    def command(self, message: str) -> None:
        """Echo an executed/issued command (rendered with a ``>`` prefix)."""
        self._log("CMD", message)

    def extend_from(self, other: "Console") -> None:
        """Append messages from a prepared session without replacing input/history."""
        self._entries.extend(other._entries)
        self._scroll_to_bottom = True

    def clear(self) -> None:
        self._entries.clear()

    def as_text(self) -> str:
        """The whole log as plain text (for copy / the selectable view)."""
        return "\n".join(self._line_text(e) for e in self._entries)

    @staticmethod
    def _line_text(entry: LogEntry) -> str:
        if entry.level == "CMD":
            return f"[{entry.timestamp}] > {entry.message}"
        return f"[{entry.timestamp}] {entry.level:<5} {entry.message}"

    # -- rendering ----------------------------------------------------------
    def render(self, state: "AppState") -> None:
        from imgui_bundle import imgui
        if imgui.button("Clear"):
            self.clear()
        imgui.same_line()
        imgui.text_disabled('Application activity — select to copy')
        imgui.separator()
        self._render_body(0)

    def _render_body(self, reserved: float) -> None:
        from imgui_bundle import imgui
        # The log body is always a read-only, mouse-selectable text box. To keep
        # it auto-scrolling (which a bare InputTextMultiline does not), the input
        # is sized to its full content height inside an outer scrolling child, and
        # we pin that child to the bottom -- but only when the user is already
        # there, so scrolling up to read history is not yanked back.
        imgui.begin_child("console_scroll", imgui.ImVec2(0.0, -reserved))
        # Inspect the current scroll position, not a previous-frame flag: a
        # queued scroll takes effect on the next frame, after content grows.
        at_bottom = imgui.get_scroll_y() >= imgui.get_scroll_max_y() - 2.0
        text = self.as_text()
        n_lines = text.count("\n") + 1
        # Multiline text uses font height, not the spacing between widgets.
        # Adding item spacing per line creates a large blank tail in long logs.
        body_h = n_lines * imgui.get_text_line_height() + 2 * imgui.get_style().frame_padding.y
        imgui.input_text_multiline(
            "##console_text", text, imgui.ImVec2(-1.0, body_h), imgui.InputTextFlags_.read_only
        )
        if self._scroll_to_bottom and at_bottom:
            imgui.set_scroll_here_y(1.0)
        self._scroll_to_bottom = False
        imgui.end_child()
