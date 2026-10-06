"""Footer: connection, alive, throughput, sample rate, log state."""

from __future__ import annotations

import time

from imgui_bundle import imgui

from ..state import ScopeAppState

_GREEN = imgui.ImVec4(0.20, 0.85, 0.25, 1.0)
_RED = imgui.ImVec4(0.90, 0.25, 0.20, 1.0)
_GRAY = imgui.ImVec4(0.45, 0.48, 0.50, 1.0)


class StatusBar:
    def __init__(self) -> None:
        self._last_t = 0.0
        self._last_bytes = 0
        self._mb_s = 0.0

    def render(self, state: ScopeAppState) -> None:
        client = state.client
        now = time.monotonic()
        if client is not None and now - self._last_t >= 1.0:
            if self._last_t:
                self._mb_s = (
                    (client.stats.bytes_received - self._last_bytes)
                    / (now - self._last_t) / 1e6
                )
            self._last_t = now
            self._last_bytes = client.stats.bytes_received
        elif client is None:
            self._last_t, self._last_bytes, self._mb_s = 0.0, 0, 0.0

        if state.connected:
            alive = state.alive()
            imgui.text_colored(_GREEN if alive else _RED, "●")
            imgui.same_line()
            imgui.text(f"{state.config.ip}:{state.config.port}")
            imgui.same_line(0, 20)
            geom = state.config.geometry
            nominal = state.sample_rate * geom.frame_bytes / geom.samples_per_packet / 1e6
            percent = 100.0 * self._mb_s / nominal if nominal else 0.0
            color = _GREEN if percent >= 95.0 else _RED
            imgui.text(f"{self._mb_s:.2f} MB/s")
            imgui.same_line()
            imgui.text_colored(color, f"({percent:.0f}%)")
            imgui.same_line(0, 20)
            imgui.text(f"{state.sample_rate / 1e3:g} kHz x {geom.channels} ch")
            imgui.same_line(0, 20)
            if imgui.small_button("Disconnect"):
                state.commands.execute(state, "disconnect", [])
        else:
            imgui.text_colored(_GRAY, "●")
            imgui.same_line()
            if client is not None:
                imgui.text(f"connecting to {state.config.ip}:{state.config.port}...")
            else:
                imgui.text("disconnected")
            imgui.same_line(0, 20)
            label = "Cancel" if client is not None else "Connect"
            if imgui.small_button(label):
                state.commands.execute(
                    state, "disconnect" if client is not None else "connect", []
                )

        if state.logger is not None:
            imgui.same_line(0, 24)
            imgui.text_colored(_RED, "REC")
            imgui.same_line()
            imgui.text(f"{state.logger.stats.rows_written:,} rows")
