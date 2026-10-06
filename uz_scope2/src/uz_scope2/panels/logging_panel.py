"""Capture logging: format selection, start/stop, live writer status."""

from __future__ import annotations

from imgui_bundle import imgui

from ..capture_log import FORMATS
from ..state import ScopeAppState


class LoggingPanel:
    def render(self, state: ScopeAppState) -> None:
        cfg = state.config.logging
        logging = state.logger is not None

        imgui.begin_disabled(logging)
        imgui.set_next_item_width(120)
        if imgui.begin_combo("Format", cfg.format):
            for fmt in FORMATS:
                if imgui.selectable(fmt, fmt == cfg.format)[0]:
                    state.commands.execute(state, "log_format", [fmt])
            imgui.end_combo()
        if cfg.format == "csv":
            imgui.same_line()
            imgui.text_disabled("(text format — not for high rates)")

        imgui.set_next_item_width(120)
        changed, every_n = imgui.input_int("Log every N-th sample", cfg.every_n)
        if changed and every_n >= 1:
            state.commands.execute(state, "log_every", [every_n])

        imgui.set_next_item_width(260)
        entered, directory = imgui.input_text(
            "Directory", cfg.directory, imgui.InputTextFlags_.enter_returns_true
        )
        if entered and directory:
            state.commands.execute(state, "log_dir", [directory])

        changed, ext = imgui.checkbox(
            "External trigger (device status bit 12)", cfg.ext_trigger
        )
        if changed:
            state.commands.execute(state, "ext_log", [ext])
        imgui.end_disabled()

        imgui.separator()
        if not logging:
            if imgui.button("Start logging", imgui.ImVec2(140, 0)):
                state.commands.execute(state, "log_start", [])
            if state.last_log_path is not None:
                imgui.same_line(0, 24)
                if imgui.button("Open last log in Data Viewer"):
                    state.commands.execute(state, "open_in_dataviewer", [])
        else:
            imgui.push_style_color(
                imgui.Col_.button, imgui.ImVec4(0.7, 0.15, 0.15, 1.0)
            )
            if imgui.button("Stop logging", imgui.ImVec2(140, 0)):
                state.commands.execute(state, "log_stop", [])
            imgui.pop_style_color()
            logger = state.logger
            if logger is not None:
                stats = logger.stats
                imgui.same_line()
                imgui.text(f"{logger.path.name}: {stats.rows_written:,} rows")
                if stats.chunks_dropped:
                    imgui.text_colored(
                        imgui.ImVec4(1.0, 0.4, 0.2, 1.0),
                        f"writer falling behind: {stats.samples_dropped:,} "
                        f"samples dropped — switch to bin format",
                    )
                if logger.error:
                    imgui.text_colored(
                        imgui.ImVec4(1.0, 0.2, 0.2, 1.0), f"error: {logger.error}"
                    )
