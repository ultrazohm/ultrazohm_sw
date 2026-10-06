"""Channel table: visibility, observable mapping, scale/offset, color.

Discrete actions (visibility, observable select) execute commands directly;
continuous drags (scale/offset) apply live and echo one command when the drag
ends, keeping the console log replayable without a line per pixel.
"""

from __future__ import annotations

from imgui_bundle import imgui

from ..state import ScopeAppState

_FLAGS = (
    imgui.TableFlags_.row_bg
    | imgui.TableFlags_.borders_inner_v
    | imgui.TableFlags_.scroll_y
    | imgui.TableFlags_.sizing_stretch_prop
)


class ChannelsPanel:
    def __init__(self) -> None:
        self._filter = ""

    def render(self, state: ScopeAppState) -> None:
        if imgui.button("Show all"):
            state.commands.execute(state, "enable_all", [True])
        imgui.same_line()
        if imgui.button("Hide all"):
            state.commands.execute(state, "enable_all", [False])

        if not imgui.begin_table("##channels", 5, _FLAGS):
            return
        imgui.table_setup_column("", imgui.TableColumnFlags_.width_fixed, 22)
        imgui.table_setup_column("CH", imgui.TableColumnFlags_.width_fixed, 34)
        imgui.table_setup_column("Observable")
        imgui.table_setup_column("Scale", imgui.TableColumnFlags_.width_fixed, 64)
        imgui.table_setup_column("Offset", imgui.TableColumnFlags_.width_fixed, 64)
        imgui.table_setup_scroll_freeze(0, 1)
        imgui.table_headers_row()

        clipper = imgui.ListClipper()
        clipper.begin(len(state.config.channel_settings))
        while clipper.step():
            for slot in range(clipper.display_start, clipper.display_end):
                self._row(state, slot)
        imgui.end_table()

    def _row(self, state: ScopeAppState, slot: int) -> None:
        ch = state.config.channel_settings[slot]
        imgui.table_next_row()
        imgui.push_id(slot)

        imgui.table_next_column()
        changed, visible = imgui.checkbox("##vis", ch.visible)
        if changed:
            state.commands.execute(state, "ch_visible", [slot + 1, visible])

        imgui.table_next_column()
        imgui.text(f"{slot + 1}")

        imgui.table_next_column()
        name = state.observable_name(ch.observable).removeprefix("JSO_")
        imgui.set_next_item_width(-1)
        if imgui.begin_combo("##obs", name):
            imgui.set_next_item_width(-1)
            _, self._filter = imgui.input_text_with_hint(
                "##filter", "filter...", self._filter
            )
            needle = self._filter.lower()
            observables = state.header.observables if state.header else []
            for idx, obs in enumerate(observables):
                short = obs.removeprefix("JSO_")
                if needle and needle not in short.lower():
                    continue
                if imgui.selectable(short, idx == ch.observable)[0]:
                    state.commands.execute(state, "ch_select", [slot + 1, str(idx)])
            imgui.end_combo()

        imgui.table_next_column()
        imgui.set_next_item_width(-1)
        changed, scale = imgui.drag_float(
            "##scale", ch.scale, 0.01, 0.0, 0.0, "%.3g"
        )
        if changed and scale != 0.0:
            ch.scale = scale  # live; echoed once below
        if imgui.is_item_deactivated_after_edit():
            state.commands.echo(state, "ch_scale", [slot + 1, ch.scale])

        imgui.table_next_column()
        imgui.set_next_item_width(-1)
        changed, offset = imgui.drag_float(
            "##offset", ch.offset, 0.01, 0.0, 0.0, "%.3g"
        )
        if changed:
            ch.offset = offset
        if imgui.is_item_deactivated_after_edit():
            state.commands.echo(state, "ch_offset", [slot + 1, ch.offset])

        imgui.pop_id()
