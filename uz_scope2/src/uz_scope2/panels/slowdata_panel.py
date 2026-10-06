"""SlowData table: every enum entry's latest value (copy via selectable)."""

from __future__ import annotations

from imgui_bundle import imgui

from ..state import ScopeAppState


class SlowDataPanel:
    def render(self, state: ScopeAppState) -> None:
        items = state.slowdata.items()
        if not items:
            imgui.text_disabled("no slowdata received yet")
            return
        if not imgui.begin_table(
            "##slowdata", 3,
            imgui.TableFlags_.row_bg
            | imgui.TableFlags_.borders_inner_v
            | imgui.TableFlags_.scroll_y
            | imgui.TableFlags_.sizing_stretch_prop,
        ):
            return
        imgui.table_setup_column("ID", imgui.TableColumnFlags_.width_fixed, 36)
        imgui.table_setup_column("Name")
        imgui.table_setup_column("Value", imgui.TableColumnFlags_.width_fixed, 130)
        imgui.table_setup_scroll_freeze(0, 1)
        imgui.table_headers_row()
        for slow_id, name, value in items:
            imgui.table_next_row()
            imgui.table_next_column()
            imgui.text(str(slow_id))
            imgui.table_next_column()
            imgui.text(name)
            imgui.table_next_column()
            text = f"{value:.6g}" if isinstance(value, float) else str(value)
            if imgui.selectable(f"{text}##v{slow_id}", False)[0]:
                imgui.set_clipboard_text(text)
        imgui.end_table()
