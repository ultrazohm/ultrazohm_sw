"""Available observables, acquired hardware slots, and retained segments."""

from __future__ import annotations

from imgui_bundle import imgui

OBSERVABLE_DND = "UZ_SCOPE2_OBSERVABLE"
SIGNAL_DND = "UZ_SCOPE2_SIGNAL"


class SignalsPanel:
    def __init__(self) -> None:
        self.filter = ""

    @staticmethod
    def _emit(state, name, *args) -> None:
        state.commands.execute(state, name, list(args))

    def render(self, state) -> None:
        imgui.text("Available observables")
        _, self.filter = imgui.input_text_with_hint(
            "##observable_filter", "filter...", self.filter
        )
        needle = self.filter.lower()
        active_observables = {seg.observable for seg in state.segments.active()}
        observables = state.header.observables if state.header else []
        avail_h = max(100.0, imgui.get_content_region_avail().y * 0.38)
        if imgui.begin_child("##available", imgui.ImVec2(0, avail_h), True):
            for index, full_name in enumerate(observables):
                if index == 0 or index in active_observables:
                    continue
                name = full_name.removeprefix("JSO_")
                if needle and needle not in name.lower():
                    continue
                imgui.selectable(name, False)
                if imgui.begin_drag_drop_source():
                    state.dragged_observable = index
                    imgui.set_drag_drop_payload_py_id(OBSERVABLE_DND, 0)
                    imgui.text(f"Acquire {name}")
                    imgui.end_drag_drop_source()
                if imgui.begin_popup_context_item():
                    if imgui.menu_item("Acquire", "", False)[0]:
                        self._emit(state, "acquire", full_name)
                    imgui.end_popup()
        imgui.end_child()

        imgui.separator()
        imgui.text(
            f"Acquired signals ({len(state.segments.active())}/{state.config.channels})"
        )
        if imgui.begin_drag_drop_target():
            if imgui.accept_drag_drop_payload_py_id(OBSERVABLE_DND) is not None:
                observable = getattr(state, "dragged_observable", None)
                if observable is not None:
                    self._emit(state, "acquire", str(observable))
            imgui.end_drag_drop_target()

        for segment in state.segments.active():
            self._active_row(state, segment)

        archived = [seg for seg in state.retained_segments() if not seg.active]
        if archived and imgui.collapsing_header(
            f"Retained history ({len(archived)})"
        )[0]:
            for segment in archived:
                self._drag_row(state, segment, archived=True)

    def _active_row(self, state, segment) -> None:
        imgui.push_id(segment.id)
        ch = state.config.channel_settings[segment.slot]
        self._drag_row(state, segment, archived=False)
        imgui.same_line()
        if imgui.small_button("release"):
            self._emit(state, "release", segment.token)
            imgui.pop_id()
            return

        imgui.set_next_item_width(72)
        changed, scale = imgui.drag_float(
            "scale", ch.scale, 0.01, 0.0, 0.0, "%.3g"
        )
        if changed and scale != 0.0:
            ch.scale = scale
            state.segments.update_style(segment.slot, scale=scale)
        if imgui.is_item_deactivated_after_edit():
            state.commands.echo(state, "ch_scale", [segment.slot + 1, ch.scale])
        imgui.same_line()
        imgui.set_next_item_width(72)
        changed, offset = imgui.drag_float(
            "offset", ch.offset, 0.01, 0.0, 0.0, "%.3g"
        )
        if changed:
            ch.offset = offset
            state.segments.update_style(segment.slot, offset=offset)
        if imgui.is_item_deactivated_after_edit():
            state.commands.echo(state, "ch_offset", [segment.slot + 1, ch.offset])
        imgui.pop_id()

    @staticmethod
    def _drag_row(state, segment, archived: bool) -> None:
        suffix = " (history)" if archived else f"  CH{segment.slot + 1}"
        imgui.selectable(
            f"{segment.name.removeprefix('JSO_')}{suffix}##signal{segment.id}",
            False,
        )
        if imgui.begin_drag_drop_source():
            state.dragged_segment = segment.id
            imgui.set_drag_drop_payload_py_id(SIGNAL_DND, 0)
            imgui.text(segment.name.removeprefix("JSO_"))
            imgui.end_drag_drop_source()

