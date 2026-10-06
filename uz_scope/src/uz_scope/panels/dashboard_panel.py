"""Dashboard: a free canvas of widgets bound to slowdata / fields / buttons.

Palette on the left (Edit mode): drag an entry onto the canvas to create a
widget at the drop position with a sensible default kind.  Edit mode overlays
each widget with an invisible button — drag moves it (``dash_move`` echoed on
release), double-click opens the config popup, right-click offers remove.
Run mode makes the widgets live: send sliders/knobs commit on release,
buttons fire the regular commands, readouts/gauges/LEDs follow the device.
"""

from __future__ import annotations

from imgui_bundle import imgui, imgui_knobs, imgui_toggle

from .. import dashboard
from ..config import DashboardWidget
from ..state import ScopeAppState

DND_BINDING = "UZ_DASH_BINDING"

_LED_ON = imgui.ImVec4(0.20, 0.85, 0.25, 1.0)
_LED_OFF = imgui.ImVec4(0.35, 0.38, 0.40, 1.0)
_PALETTE_W = 210.0


def _led_dot(on: bool, radius: float = 6.0) -> None:
    """Draw-list LED circle (the '●' glyph is missing from some fonts)."""
    pos = imgui.get_cursor_screen_pos()
    size = imgui.get_frame_height()
    center = imgui.ImVec2(pos.x + radius + 2.0, pos.y + size * 0.5)
    color = imgui.color_convert_float4_to_u32(_LED_ON if on else _LED_OFF)
    imgui.get_window_draw_list().add_circle_filled(center, radius, color)
    imgui.dummy(imgui.ImVec2(2.0 * radius + 6.0, size))


class DashboardPanel:
    def __init__(self) -> None:
        # Resolved on first render: Edit when the canvas is still empty,
        # Run when widgets were loaded from the settings (live controls).
        self.edit_mode: bool | None = None
        self._pending: dict[int, float] = {}  # send-widget staged values
        self._dragged_widget: int | None = None  # id currently being moved
        self._canvas_origin = imgui.ImVec2(0, 0)

    def render(self, state: ScopeAppState) -> None:
        if self.edit_mode is None:
            self.edit_mode = not state.config.dashboard.widgets
        _, self.edit_mode = imgui.checkbox("Edit", self.edit_mode)
        imgui.same_line()
        if self.edit_mode:
            imgui.text_disabled(
                "drag from the palette; drag to move, double-click to "
                "configure, right-click to remove"
            )
        else:
            imgui.text_disabled(
                f"{len(state.config.dashboard.widgets)} widgets live"
            )
        if self.edit_mode:
            imgui.begin_child(
                "##palette", imgui.ImVec2(_PALETTE_W, 0),
                imgui.ChildFlags_.borders,
            )
            self._palette(state)
            imgui.end_child()
            imgui.same_line()
        imgui.begin_child("##canvas", imgui.ImVec2(0, 0))
        self._canvas_origin = imgui.get_cursor_screen_pos()
        for w in list(state.config.dashboard.widgets):
            self._widget(state, w)
        if self.edit_mode and not state.config.dashboard.widgets:
            imgui.text_disabled("  <- drop palette entries here")
        imgui.end_child()
        self._accept_drop(state)

    # --- palette -----------------------------------------------------------

    def _palette_item(
        self, state: ScopeAppState, label: str, btype: str, key: str
    ) -> None:
        imgui.selectable(label, False)
        if imgui.begin_drag_drop_source():
            state.dragged_binding = (btype, key)
            imgui.set_drag_drop_payload_py_id(DND_BINDING, 0)
            imgui.text(label)
            imgui.end_drag_drop_source()

    def _palette(self, state: ScopeAppState) -> None:
        header = state.header
        if imgui.tree_node("Slowdata"):
            names = header.slowdata if header else []
            for name in names:
                short = name.removeprefix("JSSD_FLOAT_").removeprefix("JSSD_")
                if short in ("ZEROVALUE", "ENDMARKER"):
                    continue
                self._palette_item(state, short, "slowdata", name)
            imgui.tree_pop()
        if imgui.tree_node("Receive fields"):
            names = header.receive_field_names if header else []
            sources = header.slowdata_display if header else []
            for n in range(1, 21):
                if n >= len(sources) or sources[n] == "JSSD_FLOAT_ZEROVALUE":
                    continue
                label = names[n] if n < len(names) else f"receive_field_{n}"
                self._palette_item(state, label, "slowdata", sources[n])
            imgui.tree_pop()
        if imgui.tree_node("Send fields"):
            names = header.send_field_names if header else []
            for n in range(1, 21):
                label = names[n] if n < len(names) else f"send_field_{n}"
                self._palette_item(state, label, "send_field", str(n))
            imgui.tree_pop()
        if imgui.tree_node("Buttons"):
            labels = header.mybutton_labels if header else []
            for n in range(1, 9):
                label = labels[n] if n < len(labels) else f"MyButton {n}"
                self._palette_item(state, label, "my_button", str(n))
            imgui.separator()
            for name in dashboard.SYS_BUTTON_COMMANDS:
                self._palette_item(
                    state, name.replace("_", " "), "sys_button", name
                )
            imgui.tree_pop()
        if imgui.tree_node("Status bits"):
            names = {0: "Ready", 1: "Running", 2: "Error", 3: "User"}
            for bit in range(16):
                label = f"bit {bit}" + (
                    f" ({names[bit]})" if bit in names else ""
                )
                self._palette_item(state, label, "status_bit", str(bit))
            imgui.tree_pop()

    def _accept_drop(self, state: ScopeAppState) -> None:
        if imgui.begin_drag_drop_target():
            payload = imgui.accept_drag_drop_payload_py_id(DND_BINDING)
            if payload is not None and state.dragged_binding is not None:
                btype, key = state.dragged_binding
                mouse = imgui.get_mouse_pos()
                x = max(0.0, mouse.x - self._canvas_origin.x - 20.0)
                y = max(0.0, mouse.y - self._canvas_origin.y - 10.0)
                state.commands.execute(
                    state,
                    "dash_add",
                    ["auto", btype, key, round(x, 1), round(y, 1)],
                )
            imgui.end_drag_drop_target()

    # --- widgets -----------------------------------------------------------

    def _widget(self, state: ScopeAppState, w: DashboardWidget) -> None:
        imgui.set_cursor_pos(imgui.ImVec2(w.x, w.y))
        imgui.push_id(w.id)
        imgui.begin_child(
            "##w", imgui.ImVec2(w.w, w.h), imgui.ChildFlags_.borders
        )
        top = imgui.get_cursor_pos()
        if self.edit_mode:
            imgui.begin_disabled()
        self._content(state, w)
        if self.edit_mode:
            imgui.end_disabled()
            # The overlay must live INSIDE this child window: the child
            # captures all hover over its area, so a button placed in the
            # parent canvas underneath it would never receive input.
            # Submitted last, it wins hover over the (disabled) content.
            imgui.set_cursor_pos(top)
            self._edit_overlay(state, w)
        imgui.end_child()
        imgui.pop_id()

    def _edit_overlay(self, state: ScopeAppState, w: DashboardWidget) -> None:
        size = imgui.get_content_region_avail()
        imgui.invisible_button(
            "##hit", imgui.ImVec2(max(size.x, 8.0), max(size.y, 8.0))
        )
        if imgui.is_item_active() and imgui.is_mouse_dragging(0):
            delta = imgui.get_io().mouse_delta
            if delta.x or delta.y:
                w.x = max(0.0, w.x + delta.x)
                w.y = max(0.0, w.y + delta.y)
                self._dragged_widget = w.id
        if imgui.is_item_deactivated():
            if self._dragged_widget == w.id:  # echo only after a real move
                self._dragged_widget = None
                state.commands.echo(
                    state, "dash_move", [w.id, round(w.x, 1), round(w.y, 1)]
                )
        if imgui.is_item_hovered() and imgui.is_mouse_double_clicked(0):
            imgui.open_popup("##cfg")
        if imgui.begin_popup_context_item("##ctx"):
            if imgui.menu_item("Configure", "", False)[0]:
                imgui.close_current_popup()
                imgui.end_popup()
                imgui.open_popup("##cfg")
            else:
                if imgui.menu_item("Remove", "", False)[0]:
                    state.commands.execute(state, "dash_remove", [w.id])
                imgui.end_popup()
        self._config_popup(state, w)

    def _config_popup(self, state: ScopeAppState, w: DashboardWidget) -> None:
        if not imgui.begin_popup("##cfg"):
            return
        imgui.text_disabled(f"{w.binding_type}: {w.binding_key}")
        imgui.set_next_item_width(140)
        kinds = dashboard.kinds_for(w.binding_type)
        if imgui.begin_combo("kind", w.kind):
            for kind in kinds:
                if imgui.selectable(kind, kind == w.kind)[0]:
                    state.commands.execute(
                        state, "dash_config", [w.id, "kind", kind]
                    )
            imgui.end_combo()
        imgui.set_next_item_width(140)
        changed, label = imgui.input_text("label", w.label)
        if changed:
            w.label = label
        if imgui.is_item_deactivated_after_edit():
            state.commands.echo(state, "dash_config", [w.id, "label", w.label])
        for field, attr in (("min", "vmin"), ("max", "vmax")):
            imgui.set_next_item_width(140)
            changed, value = imgui.input_float(field, getattr(w, attr))
            if changed:
                setattr(w, attr, value)
            if imgui.is_item_deactivated_after_edit():
                state.commands.echo(
                    state, "dash_config", [w.id, field, f"{getattr(w, attr):g}"]
                )
        imgui.set_next_item_width(140)
        changed, fmt = imgui.input_text("format", w.fmt)
        if changed and fmt:
            w.fmt = fmt
        if imgui.is_item_deactivated_after_edit():
            state.commands.echo(state, "dash_config", [w.id, "fmt", w.fmt])
        if w.binding_type in ("my_button", "sys_button"):
            imgui.set_next_item_width(140)
            changed, bit = imgui.input_int("indicator bit", w.indicator_bit)
            if changed:
                w.indicator_bit = bit
            if imgui.is_item_deactivated_after_edit():
                state.commands.echo(
                    state, "dash_config", [w.id, "bit", str(w.indicator_bit)]
                )
        imgui.separator()
        imgui.set_next_item_width(140)
        changed, size = imgui.input_float2("size", [w.w, w.h])
        if changed:
            w.w, w.h = max(60.0, size[0]), max(40.0, size[1])
        # deactivated_after_edit implies an edit happened during this
        # widget's active session — echo the final value once.
        if imgui.is_item_deactivated_after_edit():
            state.commands.echo(state, "dash_size", [w.id, w.w, w.h])
        if imgui.button("Remove"):
            state.commands.execute(state, "dash_remove", [w.id])
            imgui.close_current_popup()
        imgui.end_popup()

    # --- widget content ------------------------------------------------------

    def _fmt(self, w: DashboardWidget, value: float | None) -> str:
        if value is None:
            return "..."
        try:
            return w.fmt % value
        except (TypeError, ValueError):
            return f"{value:g}"

    def _content(self, state: ScopeAppState, w: DashboardWidget) -> None:
        label = w.label or w.binding_key
        kind = w.kind
        if kind == "readout":
            imgui.text_disabled(label)
            imgui.push_font(None, imgui.get_font_size() * 1.5)
            imgui.text(self._fmt(w, dashboard.read_value(state, w)))
            imgui.pop_font()
        elif kind == "gauge":
            value = dashboard.read_value(state, w) or 0.0
            span = w.vmax - w.vmin if w.vmax > w.vmin else 1.0
            value = min(max(value, w.vmin), w.vmin + span)
            imgui.begin_disabled()
            imgui_knobs.knob(
                label, value, w.vmin, w.vmin + span, 0.0, w.fmt,
                imgui_knobs.ImGuiKnobVariant_.wiper_only,
                min(w.w, w.h) - 34.0,
            )
            imgui.end_disabled()
        elif kind == "progress":
            imgui.text_disabled(label)
            value = dashboard.read_value(state, w)
            span = w.vmax - w.vmin if w.vmax > w.vmin else 1.0
            frac = 0.0 if value is None else (value - w.vmin) / span
            imgui.progress_bar(
                min(max(frac, 0.0), 1.0),
                imgui.ImVec2(-1, 0),
                self._fmt(w, value),
            )
        elif kind == "led":
            value = dashboard.read_value(state, w)
            on = bool(value) if value is not None else False
            _led_dot(on, radius=8.0)
            imgui.same_line()
            imgui.text(label)
        elif kind in ("button", "toggle"):
            ind = dashboard.indicator(state, w)
            if ind is not None:
                _led_dot(bool(ind))
                imgui.same_line()
            imgui.begin_disabled(not state.connected)
            if kind == "button":
                if imgui.button(label, imgui.ImVec2(-1, 0)):
                    dashboard.press(state, w)
            else:
                changed, _on = imgui_toggle.toggle(label, bool(ind))
                if changed:
                    dashboard.press(state, w)
            imgui.end_disabled()
        elif kind in ("slider_send", "knob_send", "input_send"):
            self._send_widget(state, w, label, kind)

    def _send_widget(
        self, state: ScopeAppState, w: DashboardWidget, label: str, kind: str
    ) -> None:
        try:
            field_n = int(w.binding_key)
        except ValueError:
            imgui.text_disabled(f"bad send field: {w.binding_key}")
            return
        value = self._pending.get(w.id, 0.0)
        imgui.begin_disabled(not state.connected)
        if kind == "slider_send":
            imgui.text_disabled(label)
            imgui.set_next_item_width(-1)
            changed, value = imgui.slider_float(
                "##v", value, w.vmin, w.vmax, w.fmt
            )
            self._pending[w.id] = value
            if imgui.is_item_deactivated_after_edit():
                state.commands.execute(state, "send_field", [field_n, value])
        elif kind == "knob_send":
            span = w.vmax - w.vmin if w.vmax > w.vmin else 1.0
            changed, value = imgui_knobs.knob(
                label, min(max(value, w.vmin), w.vmin + span),
                w.vmin, w.vmin + span, 0.0, w.fmt,
                imgui_knobs.ImGuiKnobVariant_.wiper,
                min(w.w, w.h) - 34.0,
            )
            if changed:
                self._pending[w.id] = value
            if imgui.is_item_deactivated_after_edit():
                state.commands.execute(
                    state, "send_field", [field_n, self._pending.get(w.id, 0.0)]
                )
        else:  # input_send
            imgui.text_disabled(label)
            imgui.set_next_item_width(max(w.w - 70.0, 40.0))
            entered, value = imgui.input_float(
                "##v", value, 0.0, 0.0, "%.6g",
                imgui.InputTextFlags_.enter_returns_true,
            )
            self._pending[w.id] = value
            imgui.same_line()
            if imgui.button("Set") or entered:
                state.commands.execute(state, "send_field", [field_n, value])
        imgui.end_disabled()
