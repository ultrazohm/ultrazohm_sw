"""Device control: state machine, LEDs, MyButtons, send fields."""

from __future__ import annotations

from imgui_bundle import imgui

from ..protocol import STATUS_BIT_MYBUTTON_BASE, status_bit
from ..state import ScopeAppState

_LED_ON = imgui.ImVec4(0.20, 0.85, 0.25, 1.0)
_LED_ERR = imgui.ImVec4(0.90, 0.20, 0.20, 1.0)
_LED_OFF = imgui.ImVec4(0.35, 0.38, 0.40, 1.0)


def _led(label: str, on: bool, on_color=_LED_ON) -> None:
    imgui.text_colored(on_color if on else _LED_OFF, "●")
    imgui.same_line()
    imgui.text(label)


class ControlPanel:
    def __init__(self) -> None:
        self._field_values: dict[int, float] = {}

    def render(self, state: ScopeAppState) -> None:
        status = state.last_status
        _led("Ready", status_bit(status, 0))
        imgui.same_line(0, 18)
        _led("Running", status_bit(status, 1))
        imgui.same_line(0, 18)
        _led("Error", status_bit(status, 2), _LED_ERR)
        imgui.same_line(0, 18)
        _led("User", status_bit(status, 3))

        imgui.separator()
        imgui.begin_disabled(not state.connected)
        if imgui.button("Enable System"):
            state.commands.execute(state, "enable_system", [])
        imgui.same_line()
        if imgui.button("Enable Control"):
            state.commands.execute(state, "enable_control", [])
        imgui.same_line()
        imgui.push_style_color(imgui.Col_.button, imgui.ImVec4(0.7, 0.15, 0.15, 1.0))
        if imgui.button("STOP"):
            state.commands.execute(state, "stop_system", [])
        imgui.pop_style_color()
        imgui.same_line(0, 24)
        if imgui.button("Error Reset"):
            state.commands.execute(state, "error_reset", [])

        imgui.separator()
        self._my_buttons(state, status)
        imgui.end_disabled()
        imgui.separator()
        avail = imgui.get_content_region_avail().x
        imgui.begin_group()
        imgui.begin_child("##send", imgui.ImVec2(avail * 0.5, 0))
        imgui.text_disabled("Send fields")
        imgui.begin_disabled(not state.connected)
        self._send_fields(state)
        imgui.end_disabled()
        imgui.end_child()
        imgui.end_group()
        imgui.same_line()
        imgui.begin_child("##recv", imgui.ImVec2(0, 0))
        imgui.text_disabled("Receive fields")
        self._receive_fields(state)
        imgui.end_child()

    def _my_buttons(self, state: ScopeAppState, status: int) -> None:
        labels = state.header.mybutton_labels if state.header else []
        for n in range(1, 9):
            label = labels[n] if n < len(labels) else f"MyButton{n}"
            on = status_bit(status, STATUS_BIT_MYBUTTON_BASE + n - 1)
            imgui.text_colored(_LED_ON if on else _LED_OFF, "●")
            imgui.same_line()
            if imgui.button(f"{label}##mybtn{n}", imgui.ImVec2(160, 0)):
                state.commands.execute(state, "my_button", [n])
            if n % 2 == 1:
                imgui.same_line(0, 24)
        imgui.new_line()

    def _send_fields(self, state: ScopeAppState) -> None:
        names = state.header.send_field_names if state.header else []
        units = state.header.send_field_units if state.header else []
        if not imgui.begin_table(
            "##sendfields", 4,
            imgui.TableFlags_.row_bg | imgui.TableFlags_.sizing_stretch_prop,
        ):
            return
        imgui.table_setup_column("Field")
        imgui.table_setup_column("Value", imgui.TableColumnFlags_.width_fixed, 110)
        imgui.table_setup_column("", imgui.TableColumnFlags_.width_fixed, 44)
        imgui.table_setup_column("Unit", imgui.TableColumnFlags_.width_fixed, 44)
        for n in range(1, 21):
            name = names[n] if n < len(names) else f"send_field_{n}"
            unit = units[n] if n < len(units) else "-"
            imgui.table_next_row()
            imgui.push_id(n)
            imgui.table_next_column()
            imgui.text(name)
            imgui.table_next_column()
            imgui.set_next_item_width(-1)
            value = self._field_values.get(n, 0.0)
            entered, value = imgui.input_float(
                "##val", value, 0.0, 0.0, "%.6g",
                imgui.InputTextFlags_.enter_returns_true,
            )
            self._field_values[n] = value
            imgui.table_next_column()
            if imgui.button("Set") or entered:
                state.commands.execute(state, "send_field", [n, value])
            imgui.table_next_column()
            imgui.text(unit)
            imgui.pop_id()
        imgui.end_table()

    def _receive_fields(self, state: ScopeAppState) -> None:
        header = state.header
        if header is None:
            imgui.text_disabled("javascope.h not loaded")
            return
        names = header.receive_field_names
        units = header.receive_field_units
        sources = header.slowdata_display
        if not imgui.begin_table(
            "##recvfields", 3,
            imgui.TableFlags_.row_bg | imgui.TableFlags_.sizing_stretch_prop,
        ):
            return
        imgui.table_setup_column("Field")
        imgui.table_setup_column("Value", imgui.TableColumnFlags_.width_fixed, 110)
        imgui.table_setup_column("Unit", imgui.TableColumnFlags_.width_fixed, 44)

        def value_text(source: str) -> str:
            if source == "JSSD_FLOAT_ZEROVALUE":
                return "-"
            value = state.slowdata.get_by_name(source)
            if value is None:
                return "..."
            return f"{value:.6g}" if isinstance(value, float) else str(value)

        for n in range(1, 21):
            imgui.table_next_row()
            imgui.table_next_column()
            imgui.text(names[n] if n < len(names) else f"receive_field_{n}")
            imgui.table_next_column()
            imgui.text(value_text(sources[n]) if n < len(sources) else "-")
            imgui.table_next_column()
            imgui.text(units[n] if n < len(units) else "-")

        # Row 21 of the display mapping is the error-code source.
        if len(sources) > 21:
            imgui.table_next_row()
            imgui.table_next_column()
            imgui.text("Error code")
            imgui.table_next_column()
            text = value_text(sources[21])
            error = text not in ("-", "...", "0")
            color = (
                imgui.ImVec4(1.0, 0.25, 0.2, 1.0)
                if error
                else imgui.ImVec4(0.2, 0.85, 0.25, 1.0)
            )
            imgui.text_colored(color, text)
            imgui.table_next_column()
            imgui.text("-")
        imgui.end_table()
