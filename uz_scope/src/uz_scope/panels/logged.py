"""Logged variables: the observables currently streaming on channel slots.

Replaces the per-slot Channels table.  Rows are drag sources for the plot
windows (``UZ_SIGNAL``); the panel body accepts ``UZ_OBSERVABLE`` drops from
the browser.  Discrete actions execute commands; continuous drags
(scale/offset) apply live and echo one command when the drag ends.
"""

from __future__ import annotations

from imgui_bundle import imgui

from ..state import ScopeAppState
from .observables import DND_OBSERVABLE
from .plot_windows import DND_SLOT, _parse_color

_FLAGS = (
    imgui.TableFlags_.row_bg
    | imgui.TableFlags_.borders_inner_v
    | imgui.TableFlags_.scroll_y
    | imgui.TableFlags_.sizing_stretch_prop
)


class LoggedVariablesPanel:
    def render(self, state: ScopeAppState) -> None:
        if imgui.button("Show all"):
            state.commands.execute(state, "enable_all", [True])
        imgui.same_line()
        if imgui.button("Hide all"):
            state.commands.execute(state, "enable_all", [False])
        imgui.same_line()
        imgui.text_disabled(
            f"{len(state.config.logged_slots)}/{state.config.channels} slots"
        )

        avail = imgui.get_content_region_avail()
        imgui.begin_child("##logged_body", imgui.ImVec2(0, avail.y))
        if state.config.logged_slots:
            self._table(state)
        else:
            imgui.text_disabled(
                "drag observables here (or right-click them) to start logging"
            )
        imgui.end_child()
        self._accept_observable_drop(state)

    def _accept_observable_drop(self, state: ScopeAppState) -> None:
        if imgui.begin_drag_drop_target():
            payload = imgui.accept_drag_drop_payload_py_id(DND_OBSERVABLE)
            if payload is not None and state.dragged_observable is not None:
                state.commands.execute(
                    state, "log_add", [str(state.dragged_observable)]
                )
            imgui.end_drag_drop_target()

    def _table(self, state: ScopeAppState) -> None:
        if not imgui.begin_table("##logged", 6, _FLAGS):
            return
        imgui.table_setup_column("", imgui.TableColumnFlags_.width_fixed, 22)
        imgui.table_setup_column("CH", imgui.TableColumnFlags_.width_fixed, 34)
        imgui.table_setup_column("Variable")
        imgui.table_setup_column("Scale", imgui.TableColumnFlags_.width_fixed, 60)
        imgui.table_setup_column("Offset", imgui.TableColumnFlags_.width_fixed, 60)
        imgui.table_setup_column("", imgui.TableColumnFlags_.width_fixed, 26)
        imgui.table_setup_scroll_freeze(0, 1)
        imgui.table_headers_row()
        for slot in list(state.config.logged_slots):
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
        imgui.selectable(name, False)
        if imgui.begin_drag_drop_source():
            state.dragged_slot = slot
            imgui.set_drag_drop_payload_py_id(DND_SLOT, 0)
            imgui.text(f"CH{slot + 1} {name} -> plot")
            imgui.end_drag_drop_source()
        if imgui.begin_popup_context_item("##ctx"):
            if imgui.menu_item("Remove from logged", "", False)[0]:
                state.commands.execute(state, "log_remove", [slot + 1])
            imgui.end_popup()

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

        imgui.table_next_column()
        color = _parse_color(ch.color) or imgui.ImVec4(0.6, 0.6, 0.6, 1.0)
        if imgui.color_button("##color", color, 0, imgui.ImVec2(18, 18)):
            imgui.open_popup("##pick")
        if imgui.begin_popup("##pick"):
            current = _parse_color(ch.color)
            rgb = [current.x, current.y, current.z] if current else [0.6, 0.6, 0.6]
            changed, rgb = imgui.color_picker3("##picker", rgb)
            if changed:
                ch.color = "#%02x%02x%02x" % tuple(
                    int(max(0.0, min(1.0, v)) * 255) for v in rgb
                )
            if imgui.is_item_deactivated_after_edit():
                state.commands.echo(state, "ch_color", [slot + 1, ch.color])
            if imgui.small_button("auto"):
                ch.color = None
                state.commands.echo(state, "ch_color", [slot + 1, "auto"])
            imgui.end_popup()

        imgui.pop_id()
