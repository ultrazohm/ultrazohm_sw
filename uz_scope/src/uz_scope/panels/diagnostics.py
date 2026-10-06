"""Developer diagnostics: link stats, lifecheck, rate detection, command trace."""

from __future__ import annotations

import time

from imgui_bundle import imgui

from ..state import ScopeAppState

_GREEN = imgui.ImVec4(0.20, 0.85, 0.25, 1.0)
_RED = imgui.ImVec4(0.90, 0.25, 0.20, 1.0)


class DiagnosticsPanel:
    def render(self, state: ScopeAppState) -> None:
        self._connection(state)
        imgui.separator()
        self._lifecheck(state)
        imgui.separator()
        self._history(state)
        imgui.separator()
        self._rate(state)
        imgui.separator()
        self._trace(state)

    def _connection(self, state: ScopeAppState) -> None:
        imgui.text_disabled("Connection")
        client = state.client
        if client is None:
            imgui.text("not connected")
        else:
            stats = client.stats
            imgui.text(
                f"received {stats.bytes_received / 1e6:,.1f} MB in "
                f"{stats.frames:,} frames ({stats.samples:,} samples), "
                f"{stats.connects} connect(s)"
            )
            imgui.text(
                f"commands sent {stats.commands_sent:,}, "
                f"pending {client.pending_commands()}"
            )
            if stats.last_error:
                imgui.text_colored(_RED, f"last error: {stats.last_error}")
        changed, pacing = imgui.checkbox("Ack pacing", state.config.ack_pacing)
        if changed:
            state.commands.execute(state, "ack_pacing", [pacing])
        if state.single_instance is False:
            imgui.text_colored(
                _RED, "another uz_scope instance appears to be running"
            )

    def _lifecheck(self, state: ScopeAppState) -> None:
        imgui.text_disabled("Lifecheck (sample continuity)")
        if state._lifecheck_slot is None:
            imgui.text("select JSO_lifecheck on a channel to monitor for drops")
            return
        lc = state.lifecheck
        imgui.text(
            f"monitoring CH{state._lifecheck_slot + 1}: "
            f"{lc.checked:,} samples checked"
        )
        color = _GREEN if lc.gaps == 0 else _RED
        imgui.text_colored(
            color, f"{lc.gaps} gaps, {lc.missing:,} samples missing"
        )
        if imgui.small_button("Reset counters"):
            lc.reset()

    def _history(self, state: ScopeAppState) -> None:
        imgui.text_disabled("Session history")
        hist = state.history
        imgui.text(f"mode: {hist.mode}")
        pyramid = hist.pyramid
        if pyramid is not None:
            covered = pyramid.total * state.timestep_s
            imgui.text(
                f"envelope: {covered:,.0f} s covered, "
                f"{pyramid.base} samples/bucket, "
                f"{pyramid.nbytes / 2**20:,.1f} MiB"
            )
        spill = hist.spill
        if spill is not None:
            imgui.text(
                f"disk spill: {spill.flushed_rows:,} rows in {spill.directory}"
            )
            color = _GREEN if spill.chunks_dropped == 0 else _RED
            imgui.text_colored(
                color,
                f"{spill.chunks_dropped} chunks "
                f"({spill.samples_dropped:,} samples) dropped",
            )

    def _rate(self, state: ScopeAppState) -> None:
        imgui.text_disabled("Sample rate")
        nominal = 1e6 / state.config.timestep_usec
        imgui.text(f"configured: {nominal:,.0f} Hz")
        if state.detected_rate is not None:
            match = abs(state.detected_rate - nominal) < 1e-6
            imgui.text_colored(
                _GREEN if match else _RED,
                f"detected: {state.detected_rate:,.0f} Hz",
            )
        elif state._rate_probe is not None:
            imgui.text("measuring...")
        imgui.begin_disabled(not state.connected)
        if imgui.small_button("Detect now"):
            state.commands.execute(state, "detect_rate", [])
        imgui.end_disabled()

    def _trace(self, state: ScopeAppState) -> None:
        imgui.text_disabled("Sent commands (newest first)")
        if not state.cmd_trace:
            imgui.text("none yet")
            return
        if not imgui.begin_table(
            "##trace", 4,
            imgui.TableFlags_.row_bg
            | imgui.TableFlags_.scroll_y
            | imgui.TableFlags_.sizing_stretch_prop,
        ):
            return
        imgui.table_setup_column("age", imgui.TableColumnFlags_.width_fixed, 60)
        imgui.table_setup_column("id", imgui.TableColumnFlags_.width_fixed, 40)
        imgui.table_setup_column("value", imgui.TableColumnFlags_.width_fixed, 90)
        imgui.table_setup_column("command")
        imgui.table_setup_scroll_freeze(0, 1)
        imgui.table_headers_row()
        now = time.monotonic()
        for cmd in list(state.cmd_trace)[::-1][:50]:
            imgui.table_next_row()
            imgui.table_next_column()
            imgui.text(f"{now - cmd.timestamp:.1f}s")
            imgui.table_next_column()
            imgui.text(str(cmd.cmd_id))
            imgui.table_next_column()
            imgui.text(f"{cmd.value:g}")
            imgui.table_next_column()
            imgui.text(cmd.label)
        imgui.end_table()
