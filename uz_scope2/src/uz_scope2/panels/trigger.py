"""Trigger controls: arm, mode, source, edge, level, pretrigger."""

from __future__ import annotations

from imgui_bundle import imgui

from ..state import ScopeAppState

_MODES = ("auto", "normal", "single")
_EDGES = ("rising", "falling")


class TriggerPanel:
    def render(self, state: ScopeAppState) -> None:
        cfg = state.config.trigger

        changed, armed = imgui.checkbox("Armed", cfg.enabled)
        if changed:
            state.commands.dispatch(
                state, f"trig_arm({'on' if armed else 'off'})"
            )
        if state.engine is not None:
            imgui.same_line(0, 20)
            imgui.text_disabled(f"state: {state.engine.state}")
            cap = state.engine.capture
            if cap is not None:
                imgui.same_line(0, 20)
                imgui.text_disabled(f"capture #{cap.sequence}")

        imgui.set_next_item_width(120)
        if imgui.begin_combo("Mode", cfg.mode):
            for mode in _MODES:
                if imgui.selectable(mode, mode == cfg.mode)[0]:
                    state.commands.execute(state, "trig_mode", [mode])
            imgui.end_combo()

        imgui.set_next_item_width(120)
        source = "auto" if cfg.channel == 0 else f"CH{cfg.channel}"
        if imgui.begin_combo("Source", source):
            if imgui.selectable("auto", cfg.channel == 0)[0]:
                state.commands.execute(state, "trig_source", [0])
            for n in range(1, state.config.channels + 1):
                if imgui.selectable(f"CH{n}", cfg.channel == n)[0]:
                    state.commands.execute(state, "trig_source", [n])
            imgui.end_combo()

        imgui.set_next_item_width(120)
        if imgui.begin_combo("Edge", cfg.edge):
            for edge in _EDGES:
                if imgui.selectable(edge, edge == cfg.edge)[0]:
                    state.commands.execute(state, "trig_edge", [edge])
            imgui.end_combo()

        imgui.set_next_item_width(120)
        entered, level = imgui.input_float(
            "Level", cfg.level, 0.0, 0.0, "%.6g",
            imgui.InputTextFlags_.enter_returns_true,
        )
        if entered:
            state.commands.execute(state, "trig_level", [level])

        imgui.set_next_item_width(200)
        changed, pre = imgui.slider_float("Pretrigger", cfg.pretrigger, 0.0, 1.0)
        if changed:
            cfg.pretrigger = pre
        if imgui.is_item_deactivated_after_edit():
            state.commands.execute(state, "trig_pretrigger", [cfg.pretrigger])

        imgui.separator()
        has_capture = state.engine is not None and state.engine.capture is not None
        imgui.begin_disabled(not has_capture)
        if imgui.button("Export capture"):
            state.commands.execute(state, "export_capture", [])
        imgui.same_line()
        if imgui.button("Export && open in Data Viewer"):
            state.commands.execute(state, "export_capture", [])
            state.commands.execute(state, "open_in_dataviewer", [])
        imgui.end_disabled()
