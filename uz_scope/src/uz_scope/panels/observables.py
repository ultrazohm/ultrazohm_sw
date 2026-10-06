"""Observable browser: every variable the firmware exports, ready to log.

Drag a row onto the Logged variables list (or a plot cell) — or right-click
"Add to logged" — to put it on a free channel slot.  The firmware streams at
most ``channels`` (20) observables at a time; a badge shows which slot an
observable currently occupies.
"""

from __future__ import annotations

from imgui_bundle import imgui

from ..state import ScopeAppState

DND_OBSERVABLE = "UZ_OBSERVABLE"

_FLAGS = (
    imgui.TableFlags_.row_bg
    | imgui.TableFlags_.scroll_y
    | imgui.TableFlags_.sizing_stretch_prop
)


class ObservablesPanel:
    def __init__(self) -> None:
        self._filter = ""

    def render(self, state: ScopeAppState) -> None:
        if state.header is None:
            imgui.text_disabled("javascope.h not found — no observable names")
            return
        imgui.set_next_item_width(-1)
        _, self._filter = imgui.input_text_with_hint(
            "##filter", "filter observables...", self._filter
        )
        needle = self._filter.lower()
        # Slot occupancy for the badge column.
        slot_of = {
            state.config.channel_settings[s].observable: s
            for s in state.config.logged_slots
        }
        rows = [
            (idx, name.removeprefix("JSO_"))
            for idx, name in enumerate(state.header.observables)
            if not needle or needle in name.lower()
        ]
        imgui.text_disabled(
            f"{len(rows)} observables — drag or right-click to log "
            f"({len(state.config.logged_slots)}/{state.config.channels} slots)"
        )
        if not imgui.begin_table("##observables", 2, _FLAGS):
            return
        imgui.table_setup_column("Observable")
        imgui.table_setup_column("", imgui.TableColumnFlags_.width_fixed, 40)
        clipper = imgui.ListClipper()
        clipper.begin(len(rows))
        while clipper.step():
            for i in range(clipper.display_start, clipper.display_end):
                idx, short = rows[i]
                self._row(state, idx, short, slot_of.get(idx))
        imgui.end_table()

    def _row(
        self, state: ScopeAppState, idx: int, short: str, slot: int | None
    ) -> None:
        imgui.table_next_row()
        imgui.push_id(idx)
        imgui.table_next_column()
        imgui.selectable(
            short, False, imgui.SelectableFlags_.span_all_columns
        )
        if imgui.begin_drag_drop_source():
            state.dragged_observable = idx
            imgui.set_drag_drop_payload_py_id(DND_OBSERVABLE, 0)
            imgui.text(f"log {short}")
            imgui.end_drag_drop_source()
        if imgui.begin_popup_context_item("##ctx"):
            if slot is None:
                if imgui.menu_item("Add to logged", "", False)[0]:
                    state.commands.execute(state, "log_add", [str(idx)])
            else:
                if imgui.menu_item(f"Remove from logged (CH{slot + 1})", "", False)[0]:
                    state.commands.execute(state, "log_remove", [slot + 1])
            imgui.end_popup()
        imgui.table_next_column()
        if slot is not None:
            imgui.text_disabled(f"CH{slot + 1}")
        imgui.pop_id()
