"""The bottom console: a scrolling log *and* a command line.

Supported actions are echoed here as a command (level ``CMD``, rendered
``> add_signal(plot_1, run_1, ia)``), and the input box at the bottom runs the
same commands -- so the console is a log of replayable commands, not a complete GUI snapshot.
Lines beginning with the exact token ``uz`` instead launch debug CLI commands;
these are separate from the viewer's replayable command language.
The input offers name completion (matching commands listed below the box, Tab to
fill) and an Up/Down history.
"""

from __future__ import annotations

import time
from collections import deque
from dataclasses import dataclass
from typing import TYPE_CHECKING


if TYPE_CHECKING:  # pragma: no cover - typing only
    from .state import AppState

_MAX_COMPLETIONS = 6


@dataclass
class LogEntry:
    timestamp: str
    level: str
    message: str


class Console:
    """Ring buffer of log lines plus a command input, rendered in one panel."""

    def __init__(self, max_lines: int = 2000) -> None:
        self._entries: deque[LogEntry] = deque(maxlen=max_lines)
        self._scroll_to_bottom = False

        # Command line state.
        self._input = ""
        self._history: list[str] = []
        self._hist_idx = 0  # index into _history; == len means "current draft"
        self._focus_input = False
        self.cli_handler = None

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
        imgui.text_disabled("select to copy  |  help: viewer commands  |  uz --help: CLI")
        imgui.separator()

        # Reserve space for the input row (+ its completion hints) at the bottom.
        completions = self._completions(state)
        reserved = imgui.get_frame_height_with_spacing() * (1 + len(completions)) + 6.0
        self._render_body(reserved)

        imgui.separator()
        self._render_input(state, completions)

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

    def _completions(self, state: "AppState") -> list[str]:
        text = self._input
        if text.strip() and text.split(maxsplit=1)[0] == 'uz':
            return []
        if not text.strip() or "(" in text:
            return []
        return state.commands.complete(text)[:_MAX_COMPLETIONS]

    def _render_input(self, state: "AppState", completions: list[str]) -> None:
        from imgui_bundle import imgui
        imgui.text(">")
        imgui.same_line()
        imgui.set_next_item_width(-1.0)
        if self._focus_input:
            imgui.set_keyboard_focus_here()
            self._focus_input = False
        submitted, self._input = imgui.input_text(
            "##cmdinput", self._input, imgui.InputTextFlags_.enter_returns_true
        )
        focused = imgui.is_item_focused()

        if submitted:
            self._submit(state)
        elif focused:
            if imgui.is_key_pressed(imgui.Key.tab) and completions:
                self._input = completions[0] + "("
                self._focus_input = True
            elif imgui.is_key_pressed(imgui.Key.up_arrow):
                self._history_step(-1)
            elif imgui.is_key_pressed(imgui.Key.down_arrow):
                self._history_step(1)

        # Completion hints: click to fill, or read the signature while typing args.
        for name in completions:
            cmd = state.commands.get(name)
            label = cmd.signature() if cmd else name
            if imgui.selectable(f"  {label}", False)[0]:
                self._input = name + "("
                self._focus_input = True

    def _submit(self, state: "AppState") -> None:
        text = self._input.strip()
        if text:
            if not self._history or self._history[-1] != text:
                self._history.append(text)
            self._hist_idx = len(self._history)
            parts = text.split(maxsplit=1)
            if parts[0] == 'uz':
                self.command(text)
                if self.cli_handler is None:
                    self.error('Live is not activated.')
                else:
                    try:
                        self.cli_handler(parts[1] if len(parts) > 1 else '')
                    except Exception as exc:
                        self.error(str(exc))
            else:
                state.commands.dispatch(state, text)
        self._input = ""
        self._focus_input = True

    def _history_step(self, delta: int) -> None:
        if not self._history:
            return
        self._hist_idx = max(0, min(len(self._history), self._hist_idx + delta))
        if self._hist_idx >= len(self._history):
            self._input = ""
        else:
            self._input = self._history[self._hist_idx]
        self._focus_input = True
