"""Dashboard model: widgets on a free canvas bound to device values.

Pure model + command helpers (no GUI): the view lives in
``panels/dashboard_panel.py``.  Widgets persist in ``config.dashboard`` and
every mutation routes through ``dash_*`` commands, so a session/script
round-trip recreates the canvas exactly (the nodes-panel pattern from
uz_dataviewer — positions in the model, never in an editor ini).

Bindings:

- ``slowdata``   — read a slowdata value by enum name (also used for the
                   receive-field display sources)
- ``send_field`` — writable field 1..20 (widget commits on release/Enter)
- ``my_button``  — MyButton "1".."8"; indicator = status bit 4+n-1
- ``sys_button`` — Enable_System / Enable_Control / Stop / Error_Reset
- ``status_bit`` — one bit of the status word (LEDs)
"""

from __future__ import annotations

from typing import TYPE_CHECKING

from .commands import CommandError
from .config import BINDING_TYPES, WIDGET_KINDS, DashboardWidget
from .protocol import STATUS_BIT_MYBUTTON_BASE, status_bit

if TYPE_CHECKING:  # pragma: no cover
    from .state import ScopeAppState

# sys_button binding_key -> command name
SYS_BUTTON_COMMANDS = {
    "Enable_System": "enable_system",
    "Enable_Control": "enable_control",
    "Stop": "stop_system",
    "Error_Reset": "error_reset",
}

# Config-popup fields accepted by ``dash_config``.
CONFIG_FIELDS = ("kind", "label", "min", "max", "fmt", "bit")


def default_kind(binding_type: str) -> str:
    return {
        "slowdata": "readout",
        "send_field": "slider_send",
        "my_button": "button",
        "sys_button": "button",
        "status_bit": "led",
    }[binding_type]


def kinds_for(binding_type: str) -> tuple[str, ...]:
    """Widget kinds that make sense for a binding (config-popup choices)."""
    if binding_type == "slowdata":
        return ("readout", "gauge", "progress", "led")
    if binding_type == "send_field":
        return ("slider_send", "knob_send", "input_send")
    if binding_type in ("my_button", "sys_button"):
        return ("button", "toggle")
    return ("led", "readout")  # status_bit


def widget_by_id(state: "ScopeAppState", wid: int) -> DashboardWidget:
    for w in state.config.dashboard.widgets:
        if w.id == wid:
            return w
    raise CommandError(f"no dashboard widget with id {wid}")


def add_widget(
    state: "ScopeAppState",
    kind: str,
    binding_type: str,
    binding_key: str,
    x: float,
    y: float,
    wid: int | None = None,
) -> DashboardWidget:
    if binding_type not in BINDING_TYPES:
        raise CommandError(
            f"binding must be one of {'/'.join(BINDING_TYPES)}: {binding_type}"
        )
    if kind == "auto":
        kind = default_kind(binding_type)
    if kind not in WIDGET_KINDS:
        raise CommandError(f"kind must be one of {'/'.join(WIDGET_KINDS)}: {kind}")
    dash = state.config.dashboard
    if wid is None:
        wid = dash.next_id
    elif any(w.id == wid for w in dash.widgets):
        # Explicit ids come from exported scripts (so later dash_config
        # lines address the right widget) — never silently reuse one.
        raise CommandError(f"dashboard widget id {wid} already exists")
    w = DashboardWidget(
        id=wid,
        kind=kind,
        binding_type=binding_type,
        binding_key=str(binding_key),
        x=float(x),
        y=float(y),
        label=default_label(state, binding_type, str(binding_key)),
    )
    dash.next_id = max(dash.next_id, wid + 1)
    dash.widgets.append(w)
    return w


def remove_widget(state: "ScopeAppState", wid: int) -> None:
    w = widget_by_id(state, wid)
    state.config.dashboard.widgets.remove(w)


def config_widget(state: "ScopeAppState", wid: int, name: str, value: str) -> None:
    w = widget_by_id(state, wid)
    if name == "kind":
        if value not in WIDGET_KINDS:
            raise CommandError(f"kind must be one of {'/'.join(WIDGET_KINDS)}")
        w.kind = value
    elif name == "label":
        w.label = value
    elif name == "min":
        w.vmin = float(value)
    elif name == "max":
        w.vmax = float(value)
    elif name == "fmt":
        w.fmt = value or "%.4g"
    elif name == "bit":
        w.indicator_bit = int(value)
    else:
        raise CommandError(
            f"field must be one of {'/'.join(CONFIG_FIELDS)}: {name}"
        )


def default_label(
    state: "ScopeAppState", binding_type: str, binding_key: str
) -> str:
    header = state.header
    if binding_type == "slowdata":
        return binding_key.removeprefix("JSSD_FLOAT_").removeprefix("JSSD_")
    if binding_type == "send_field":
        try:
            n = int(binding_key)
        except ValueError:
            return binding_key
        names = header.send_field_names if header else []
        return names[n] if n < len(names) else f"send_field_{n}"
    if binding_type == "my_button":
        try:
            n = int(binding_key)
        except ValueError:
            return binding_key
        labels = header.mybutton_labels if header else []
        return labels[n] if n < len(labels) else f"MyButton {n}"
    if binding_type == "sys_button":
        return binding_key.replace("_", " ")
    return f"status bit {binding_key}"


def read_value(state: "ScopeAppState", w: DashboardWidget) -> float | None:
    """Current bound value for display widgets (None while unknown)."""
    if w.binding_type == "slowdata":
        value = state.slowdata.get_by_name(w.binding_key)
        return float(value) if value is not None else None
    if w.binding_type == "status_bit":
        try:
            return float(status_bit(state.last_status, int(w.binding_key)))
        except ValueError:
            return None
    return None


def indicator(state: "ScopeAppState", w: DashboardWidget) -> bool | None:
    """Indicator LED state for button/toggle widgets (None = no LED)."""
    bit = w.indicator_bit
    if bit < 0 and w.binding_type == "my_button":
        try:
            bit = STATUS_BIT_MYBUTTON_BASE + int(w.binding_key) - 1
        except ValueError:
            return None
    if bit < 0:
        return None
    return status_bit(state.last_status, bit)


def press(state: "ScopeAppState", w: DashboardWidget) -> None:
    """Fire a button/toggle widget through the regular commands."""
    if w.binding_type == "my_button":
        state.commands.execute(state, "my_button", [int(w.binding_key)])
    elif w.binding_type == "sys_button":
        cmd = SYS_BUTTON_COMMANDS.get(w.binding_key)
        if cmd is None:
            raise CommandError(f"unknown system button: {w.binding_key}")
        state.commands.execute(state, cmd, [])
