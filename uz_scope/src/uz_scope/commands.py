"""Command layer for uz_scope, built on uz_dataviewer's registry machinery.

Every UI action routes through a command: it mutates the
:class:`~uz_scope.state.ScopeAppState`, echoes its canonical call to the
console, and is replayable from a script — the uz_dataviewer pattern.

``CommandRegistry.__init__`` hardcodes the dataviewer builtins, so the
subclass resets the table and registers the scope set instead.
"""

from __future__ import annotations

from typing import TYPE_CHECKING

from uz_dataviewer.commands import (  # noqa: F401 (re-exported for panels)
    Command,
    CommandError,
    CommandRegistry,
    Param,
    format_call,
    parse_call,
)

if TYPE_CHECKING:  # pragma: no cover
    from .state import ScopeAppState


class ScopeCommandRegistry(CommandRegistry):
    def __init__(self) -> None:
        self._commands = {}
        register_scope_builtins(self)


def _resolve_observable(state: "ScopeAppState", raw) -> int:
    """Observable by enum index or name (with or without the ``JSO_`` prefix)."""
    s = str(raw).strip()
    if s.lstrip("-").isdigit():
        idx = int(s)
    else:
        table = state.header.observable_index if state.header else {}
        idx = table.get(s, table.get("JSO_" + s, -1))
        if idx < 0:
            raise CommandError(f"Unknown observable: {s}")
    count = len(state.header.observables) if state.header else 2**31
    if not 0 <= idx < count:
        raise CommandError(f"Observable index out of range: {idx}")
    return idx


def _slot(state: "ScopeAppState", raw) -> int:
    """Scope channel slot, 1-based on the wire/UI, returned 0-based."""
    n = int(str(raw).strip())
    if not 1 <= n <= state.config.channels:
        raise CommandError(f"Channel out of range (1..{state.config.channels}): {n}")
    return n - 1


def register_scope_builtins(reg: ScopeCommandRegistry) -> None:
    # --- connection -------------------------------------------------------
    def _connect(state: "ScopeAppState", args) -> str:
        ip = args[0].strip() if args and args[0] else ""
        port = int(args[1]) if len(args) > 1 and args[1] else None
        # Explicit arguments are a one-off target (test server etc.) and do
        # NOT touch the saved default — a bare `connect` always goes back to
        # the configured UltraZohm address (set_ip/set_port to change it).
        state.connect(ip=ip or None, port=port)
        client = state.client
        target = f"{client.ip}:{client.port}" if client else "?"
        note = " (one-off; saved default unchanged)" if ip or port else ""
        return f"connecting to {target}{note}"

    reg.add(
        "connect",
        [Param("ip", "str", optional=True), Param("port", "int", optional=True)],
        _connect,
        "Connect to the saved UltraZohm address; explicit ip/port are a one-off target",
    )

    def _disconnect(state, _args) -> str:
        state.disconnect()
        return "disconnected"

    reg.add("disconnect", [], _disconnect, "Close the connection")

    def _set_ip(state, args) -> str:
        state.config.ip = args[0]
        return f"device address set to {args[0]} (takes effect on next connect)"

    reg.add("set_ip", [Param("ip", "str")], _set_ip, "Set the device IP address")

    def _set_port(state, args) -> str:
        state.config.port = int(args[0])
        return f"device port set to {args[0]} (takes effect on next connect)"

    reg.add("set_port", [Param("port", "int")], _set_port, "Set the device TCP port")

    def _ack_pacing(state, args) -> str:
        state.config.ack_pacing = bool(args[0])
        if state.client:
            state.client.ack_pacing = state.config.ack_pacing
        return f"ack pacing {'on' if args[0] else 'off'}"

    reg.add(
        "ack_pacing",
        [Param("enabled", "bool")],
        _ack_pacing,
        "Send one 8-byte (zero-)ack per received frame (needed by lock-step servers)",
    )

    def _auto_connect(state, args) -> str:
        state.config.auto_connect = bool(args[0])
        return f"auto-connect {'on' if args[0] else 'off'}"

    reg.add("auto_connect", [Param("enabled", "bool")], _auto_connect,
            "Connect automatically on startup")

    # --- geometry / timing ------------------------------------------------
    def _set_geometry(state, args) -> str:
        state.set_geometry(int(args[0]), int(args[1]))
        return f"frame geometry: {args[0]} channels x {args[1]} samples/packet"

    reg.add(
        "set_geometry",
        [Param("channels", "int"), Param("samples_per_packet", "int")],
        _set_geometry,
        "Set the wire frame geometry (must match the firmware build)",
    )

    def _set_timestep(state, args) -> str:
        usec = float(args[0])
        if usec <= 0:
            raise CommandError("timestep must be > 0")
        if state.client is not None:
            # The reader thread holds ring/engine references; swapping the
            # ring under it would desync logger/trigger indices.
            raise CommandError("disconnect before changing the timestep")
        state.config.timestep_usec = usec
        state.detected_rate = None
        state.rebuild_ring()
        return f"sample timestep {usec:g} us ({1e6 / usec:,.0f} Hz)"

    reg.add("set_timestep", [Param("usec", "float")], _set_timestep,
            "Set the implicit sample timestep in microseconds")

    # --- display ----------------------------------------------------------
    def _run(state, _args) -> str:
        state.frozen = False
        return "display running"

    reg.add("run", [], _run, "Resume the rolling display")

    def _stop_scope(state, _args) -> str:
        state.frozen = True
        return "display frozen (ingest continues)"

    reg.add("stop_scope", [], _stop_scope, "Freeze the display (ingest continues)")

    def _set_window(state, args) -> str:
        seconds = float(args[0])
        if seconds <= 0:
            raise CommandError("window must be > 0 seconds")
        state.config.window_seconds = seconds
        state.config.plots[0].x_mode = f"{seconds:g}"
        state.plot_view(1).attached = True
        return f"visible window {seconds:g} s"

    reg.add("set_window", [Param("seconds", "float")], _set_window,
            "Set the visible time window of plot window 1 (alias of plot_xmode)")

    def _set_refresh(state, args) -> str:
        hz = float(args[0])
        if not 1 <= hz <= 120:
            raise CommandError("refresh must be 1..120 Hz")
        state.config.refresh_hz = hz
        return f"plot refresh {hz:g} Hz"

    reg.add("set_refresh", [Param("hz", "float")], _set_refresh,
            "Set the plot data refresh rate")

    def _fix_axis(state, args) -> str:
        state.fix_axis = bool(args[0])
        return f"fixed y-axis {'on' if args[0] else 'off'}"

    reg.add("fix_axis", [Param("enabled", "bool")], _fix_axis,
            "Freeze the y-axis instead of auto-fitting")

    # --- plot windows -----------------------------------------------------
    def _plot_add(state, args) -> str:
        from .config import PlotWindowSettings

        title = args[0].strip() if args and args[0] else ""
        state.config.plots.append(PlotWindowSettings(title=title))
        state.config.ensure_plots()
        n = len(state.config.plots)
        return f"plot window {n} added ({state.config.plots[-1].title})"

    reg.add("plot_add", [Param("title", "str", optional=True)], _plot_add,
            "Open another independent plot window")

    def _plot_remove(state, args) -> str:
        win = int(args[0])
        state.plot_window(win)  # validate
        if win == 1:
            raise CommandError("plot window 1 cannot be removed")
        state.config.plots.pop(win - 1)
        state.plot_views.pop(win, None)
        # Views above the removed window shift down by one.
        for i in sorted(k for k in state.plot_views if k > win):
            state.plot_views[i - 1] = state.plot_views.pop(i)
        return f"plot window {win} removed"

    reg.add("plot_remove", [Param("window", "int")], _plot_remove,
            "Remove a plot window (window 1 stays)")

    def _plot_grid(state, args) -> str:
        win, rows, cols = int(args[0]), int(args[1]), int(args[2])
        from .config import MAX_PLOT_GRID

        if not (1 <= rows <= MAX_PLOT_GRID and 1 <= cols <= MAX_PLOT_GRID):
            raise CommandError(f"rows/cols must be 1..{MAX_PLOT_GRID}")
        window = state.plot_window(win)
        window.rows, window.cols = rows, cols
        window.ensure_cells(state.config.channels)
        return f"plot window {win} grid {rows}x{cols}"

    reg.add(
        "plot_grid",
        [Param("window", "int"), Param("rows", "int"), Param("cols", "int")],
        _plot_grid,
        "Set a plot window's subplot grid (extra cells merge into the last)",
    )

    def _plot_xmode(state, args) -> str:
        from .config import X_MODE_CONT

        win = int(args[0])
        mode = str(args[1]).strip().lower()
        window = state.plot_window(win)
        if mode == X_MODE_CONT:
            window.x_mode = X_MODE_CONT
            detail = "full session, growing"
        else:
            try:
                seconds = float(mode)
            except ValueError:
                raise CommandError("mode must be seconds or 'cont'") from None
            if seconds <= 0:
                raise CommandError("window must be > 0 seconds")
            window.x_mode = f"{seconds:g}"
            detail = f"last {seconds:g} s"
            if win == 1:
                state.config.window_seconds = seconds
        state.plot_view(win).attached = True
        return f"plot window {win} timebase: {detail}"

    reg.add(
        "plot_xmode",
        [Param("window", "int"), Param("mode", "str")],
        _plot_xmode,
        "Timebase of a plot window: seconds (rolling) or 'cont' (whole session)",
    )

    def _plot_link_x(state, args) -> str:
        window = state.plot_window(int(args[0]))
        window.link_x = bool(args[1])
        return f"plot window {args[0]} x-link {'on' if args[1] else 'off'}"

    reg.add("plot_link_x", [Param("window", "int"), Param("linked", "bool")],
            _plot_link_x, "Link the x-axes of all cells in a plot window")

    def _plot_follow(state, args) -> str:
        win = int(args[0])
        state.plot_window(win)  # validate
        view = state.plot_view(win)
        view.attached = bool(args[1])
        if view.attached:
            view.pending_x = None
            view.fit_pending = False
        return (
            f"plot window {win} {'follows the live edge' if view.attached else 'detached'}"
        )

    reg.add("plot_follow", [Param("window", "int"), Param("on", "bool")],
            _plot_follow, "Re-attach a plot window to the live edge (or detach it)")

    def _x_lim(state, args) -> str:
        win, lo, hi = int(args[0]), float(args[1]), float(args[2])
        if hi <= lo:
            raise CommandError("x_lim needs lo < hi")
        state.plot_window(win)  # validate
        view = state.plot_view(win)
        view.attached = False
        view.pending_x = (lo, hi)
        return None

    reg.add(
        "x_lim",
        [Param("window", "int"), Param("lo", "float"), Param("hi", "float")],
        _x_lim,
        "Detach a plot window and set its visible x-range (echoed on pan/zoom)",
    )

    def _plot_fit(state, args) -> str:
        win = int(args[0])
        state.plot_window(win)  # validate
        view = state.plot_view(win)
        view.attached = False
        view.fit_pending = True
        return f"plot window {win} fit to data"

    reg.add("plot_fit", [Param("window", "int")], _plot_fit,
            "Fit a plot window's x-axis to the whole session once")

    def _plot_assign(state, args) -> str:
        win, cell = int(args[0]), int(args[1])
        slot = _slot(state, args[2])
        state.plot_assign_slot(win, cell, slot)
        return f"CH{slot + 1} -> plot window {win} cell {cell}"

    reg.add(
        "plot_assign",
        [Param("window", "int"), Param("cell", "int"), Param("channel", "int")],
        _plot_assign,
        "Show a channel in a plot cell (cells are 1-based, row-major)",
    )

    def _plot_unassign(state, args) -> str:
        win, cell = int(args[0]), int(args[1])
        slot = _slot(state, args[2])
        state.plot_unassign_slot(win, cell, slot)
        return f"CH{slot + 1} removed from plot window {win} cell {cell}"

    reg.add(
        "plot_unassign",
        [Param("window", "int"), Param("cell", "int"), Param("channel", "int")],
        _plot_unassign,
        "Remove a channel from a plot cell",
    )

    # --- channels ---------------------------------------------------------
    def _ch_select(state, args) -> str:
        slot = _slot(state, args[0])
        obs = _resolve_observable(state, args[1])
        state.select_observable(slot, obs)
        name = state.observable_name(obs)
        return f"CH{slot + 1} observes {name} ({obs})"

    reg.add(
        "ch_select",
        [Param("channel", "int"), Param("observable", "str")],
        _ch_select,
        "Map an observable (index or name) onto a scope channel slot",
    )

    def _ch_visible(state, args) -> str:
        slot = _slot(state, args[0])
        state.set_slot_visible(slot, bool(args[1]))
        return f"CH{slot + 1} {'shown' if args[1] else 'hidden'}"

    reg.add("ch_visible", [Param("channel", "int"), Param("visible", "bool")],
            _ch_visible, "Show/hide a channel in plot window 1, cell 1")

    def _ch_scale(state, args) -> str:
        slot = _slot(state, args[0])
        scale = float(args[1])
        if scale == 0:
            raise CommandError("scale must be non-zero")
        state.config.channel_settings[slot].scale = scale
        return None

    reg.add("ch_scale", [Param("channel", "int"), Param("scale", "float")],
            _ch_scale, "Set a channel's display scale divisor")

    def _ch_offset(state, args) -> str:
        slot = _slot(state, args[0])
        state.config.channel_settings[slot].offset = float(args[1])
        return None

    reg.add("ch_offset", [Param("channel", "int"), Param("offset", "float")],
            _ch_offset, "Set a channel's display offset")

    def _ch_color(state, args) -> str:
        slot = _slot(state, args[0])
        color = str(args[1]).strip()
        if color.lower() in ("auto", "none", ""):
            state.config.channel_settings[slot].color = None
            return f"CH{slot + 1} color auto"
        if not (color.startswith("#") and len(color) == 7):
            raise CommandError("color must be #RRGGBB or auto")
        int(color[1:], 16)  # validates hex
        state.config.channel_settings[slot].color = color
        return f"CH{slot + 1} color {color}"

    reg.add("ch_color", [Param("channel", "int"), Param("color", "str")],
            _ch_color, "Set a channel's plot color (#RRGGBB or auto)")

    def _log_add(state, args) -> str:
        obs = _resolve_observable(state, args[0])
        already = [
            s for s in state.config.logged_slots
            if state.config.channel_settings[s].observable == obs
        ]
        slot = state.logged_add(obs)
        name = state.observable_name(obs)
        if already:
            return f"{name} is already logged on CH{slot + 1}"
        return f"{name} -> CH{slot + 1} (logged)"

    reg.add(
        "log_add",
        [Param("observable", "str")],
        _log_add,
        "Add an observable to the logged variables (first free channel slot)",
    )

    def _log_remove(state, args) -> str:
        slot = _slot(state, args[0])
        state.logged_remove(slot)
        return f"CH{slot + 1} removed from the logged variables"

    reg.add("log_remove", [Param("channel", "int")], _log_remove,
            "Remove a channel from the logged variables (frees the slot)")

    def _enable_all(state, args) -> str:
        show = bool(args[0])
        slots = state.config.logged_slots if show else range(state.config.channels)
        for slot in slots:
            state.set_slot_visible(slot, show)
        return f"all logged channels {'shown' if show else 'hidden'}"

    reg.add("enable_all", [Param("visible", "bool")], _enable_all,
            "Show or hide all logged channels in plot window 1")

    # --- session history --------------------------------------------------
    def _history_mode(state, args) -> str:
        from .config import HISTORY_MODES

        mode = str(args[0]).strip().lower()
        if mode not in HISTORY_MODES:
            raise CommandError(f"mode must be one of {'/'.join(HISTORY_MODES)}")
        state.config.history.mode = mode
        state.rebuild_history()
        detail = {
            "off": "old data only lives in the ring",
            "ram": "session envelope in RAM; zoom past the ring shows min/max",
            "disk": "raw spill to disk; full detail for the whole session",
        }[mode]
        return f"history mode {mode} — {detail} (restarts the session history)"

    reg.add("history_mode", [Param("mode", "str")], _history_mode,
            "Session history backend: off, ram (envelope) or disk (full detail)")

    def _history_dir(state, args) -> str:
        state.config.history.directory = args[0]
        if state.config.history.mode == "disk":
            # Only disk mode uses the directory; a ram-mode rebuild would
            # needlessly discard the collected session envelope.
            state.rebuild_history()
        return f"history spill directory {args[0]}"

    reg.add("history_dir", [Param("path", "str")], _history_dir,
            "Set the disk-mode history spill directory")

    def _history_limit(state, args) -> str:
        mb = int(args[0])
        if mb < 1:
            raise CommandError("limit must be >= 1 MiB")
        state.config.history.max_ram_bytes = mb * 1024 * 1024
        pyramid = state.history.pyramid
        if pyramid is not None:
            pyramid.max_bytes = state.config.history.max_ram_bytes
        return f"history envelope RAM limit {mb} MiB"

    reg.add("history_limit", [Param("mb", "int")], _history_limit,
            "Cap the session envelope pyramid RAM (MiB); coarsens when exceeded")

    def _history_keep(state, args) -> str:
        state.config.history.keep_files = bool(args[0])
        return (
            "history spill files are kept after exit"
            if args[0]
            else "history spill files are deleted on exit"
        )

    reg.add("history_keep", [Param("keep", "bool")], _history_keep,
            "Keep the disk-mode spill files (+ sidecar) after exit")

    def _history_clear(state, _args) -> str:
        state.history.clear()
        return "session history cleared"

    reg.add("history_clear", [], _history_clear,
            "Forget the collected session history (ring is untouched)")

    # --- dashboard --------------------------------------------------------
    def _dash_add(state, args) -> str:
        from . import dashboard

        kind, btype, key = str(args[0]), str(args[1]), str(args[2])
        wid = int(args[5]) if len(args) > 5 and args[5] else None
        w = dashboard.add_widget(
            state, kind, btype, key, float(args[3]), float(args[4]), wid=wid
        )
        return f"dashboard widget {w.id}: {w.kind} for {btype} {key}"

    reg.add(
        "dash_add",
        [Param("kind", "str"), Param("binding", "str"), Param("key", "str"),
         Param("x", "float"), Param("y", "float"),
         Param("id", "int", optional=True)],
        _dash_add,
        "Add a dashboard widget (kind 'auto' picks a default for the binding)",
    )

    def _dash_move(state, args) -> str:
        from . import dashboard

        w = dashboard.widget_by_id(state, int(args[0]))
        w.x, w.y = max(0.0, float(args[1])), max(0.0, float(args[2]))
        return None

    reg.add(
        "dash_move",
        [Param("id", "int"), Param("x", "float"), Param("y", "float")],
        _dash_move,
        "Move a dashboard widget (echoed when a drag ends)",
    )

    def _dash_size(state, args) -> str:
        from . import dashboard

        w = dashboard.widget_by_id(state, int(args[0]))
        w.w = max(60.0, float(args[1]))
        w.h = max(40.0, float(args[2]))
        return None

    reg.add(
        "dash_size",
        [Param("id", "int"), Param("w", "float"), Param("h", "float")],
        _dash_size,
        "Resize a dashboard widget",
    )

    def _dash_config(state, args) -> str:
        from . import dashboard

        dashboard.config_widget(state, int(args[0]), str(args[1]), str(args[2]))
        return f"widget {args[0]}: {args[1]} = {args[2]}"

    reg.add(
        "dash_config",
        [Param("id", "int"), Param("field", "str"), Param("value", "str")],
        _dash_config,
        "Configure a widget: kind, label, min, max, fmt or bit",
    )

    def _dash_remove(state, args) -> str:
        from . import dashboard

        dashboard.remove_widget(state, int(args[0]))
        return f"dashboard widget {args[0]} removed"

    reg.add("dash_remove", [Param("id", "int")], _dash_remove,
            "Remove a dashboard widget")

    def _dash_clear(state, _args) -> str:
        n = len(state.config.dashboard.widgets)
        state.config.dashboard.widgets.clear()
        state.config.dashboard.next_id = 1
        return f"dashboard cleared ({n} widgets removed)"

    reg.add("dash_clear", [], _dash_clear,
            "Remove all dashboard widgets (exported scripts start with this)")

    # --- device state machine / buttons -----------------------------------
    def _wire_button(name: str, help_text: str):
        def handler(state: "ScopeAppState", _args) -> str:
            state.send_button(name)
            return f"sent {name}"

        reg.add(name.lower(), [], handler, help_text)

    _wire_button("Enable_System", "Device state machine: idle -> running")
    _wire_button("Enable_Control", "Device state machine: running -> control")
    _wire_button("Error_Reset", "Reset the device error state")

    def _stop_system(state, _args) -> str:
        state.send_button("Stop")
        return "sent Stop"

    reg.add("stop_system", [], _stop_system,
            "Device state machine STOP (wire command 3)")

    def _my_button(state, args) -> str:
        n = int(args[0])
        if not 1 <= n <= 8:
            raise CommandError("MyButton index must be 1..8")
        state.send_button(f"My_Button_{n}")
        return f"sent My_Button_{n}"

    reg.add("my_button", [Param("n", "int")], _my_button, "Press MyButton 1..8")

    def _send_field(state, args) -> str:
        n = int(args[0])
        if not 1 <= n <= 20:
            raise CommandError("send field index must be 1..20")
        value = float(args[1])
        state.send_field(n, value)
        return f"send field {n} = {value:g}"

    reg.add("send_field", [Param("n", "int"), Param("value", "float")],
            _send_field, "Transmit a send-field value to the device")

    # --- trigger ----------------------------------------------------------
    def _trig_arm(state, args) -> str:
        if bool(args[0]):
            state.arm_trigger()
            return "trigger armed"
        state.disarm_trigger()
        return "trigger disarmed"

    reg.add("trig_arm", [Param("armed", "bool")], _trig_arm,
            "Arm/disarm the trigger")

    def _trig_mode(state, args) -> str:
        mode = str(args[0]).strip().lower()
        if mode not in ("auto", "normal", "single"):
            raise CommandError("mode must be auto, normal or single")
        state.config.trigger.mode = mode
        state.rearm_if_armed()
        return f"trigger mode {mode}"

    reg.add("trig_mode", [Param("mode", "str")], _trig_mode,
            "Trigger mode: auto, normal or single")

    def _trig_source(state, args) -> str:
        n = int(args[0])
        if not 0 <= n <= state.config.channels:
            raise CommandError(
                f"source must be 0 (auto) or 1..{state.config.channels}"
            )
        state.config.trigger.channel = n
        state.rearm_if_armed()
        return f"trigger source {'auto' if n == 0 else f'CH{n}'}"

    reg.add("trig_source", [Param("channel", "int")], _trig_source,
            "Trigger source channel (0 = first visible)")

    def _trig_edge(state, args) -> str:
        edge = str(args[0]).strip().lower()
        if edge not in ("rising", "falling"):
            raise CommandError("edge must be rising or falling")
        state.config.trigger.edge = edge
        state.rearm_if_armed()
        return f"trigger edge {edge}"

    reg.add("trig_edge", [Param("edge", "str")], _trig_edge,
            "Trigger edge: rising or falling")

    def _trig_level(state, args) -> str:
        state.config.trigger.level = float(args[0])
        state.rearm_if_armed()
        return f"trigger level {args[0]:g}"

    reg.add("trig_level", [Param("level", "float")], _trig_level,
            "Trigger level threshold")

    def _trig_pretrigger(state, args) -> str:
        p = float(args[0])
        if not 0.0 <= p <= 1.0:
            raise CommandError("pretrigger must be in 0..1")
        state.config.trigger.pretrigger = p
        state.rearm_if_armed()
        return f"pretrigger {p:g}"

    reg.add("trig_pretrigger", [Param("fraction", "float")], _trig_pretrigger,
            "Fraction of the window before the trigger (0..1)")

    # --- logging ----------------------------------------------------------
    def _log_start(state, _args) -> str:
        path = state.start_log()
        return f"logging to {path}"

    reg.add("log_start", [], _log_start, "Start a new capture log file")

    def _log_stop(state, _args) -> str:
        return state.stop_log()

    reg.add("log_stop", [], _log_stop, "Stop and close the capture log")

    def _log_format(state, args) -> str:
        from .capture_log import FORMATS

        fmt = str(args[0]).strip().lower()
        if fmt not in FORMATS:
            raise CommandError(f"format must be one of {'/'.join(FORMATS)}")
        state.config.logging.format = fmt
        return f"log format {fmt}"

    reg.add("log_format", [Param("format", "str")], _log_format,
            "Set the log file format: parquet, csv or bin")

    def _log_every(state, args) -> str:
        n = int(args[0])
        if n < 1:
            raise CommandError("every_n must be >= 1")
        state.config.logging.every_n = n
        return f"logging every {n}. sample"

    reg.add("log_every", [Param("n", "int")], _log_every,
            "Log only every N-th sample")

    def _log_dir(state, args) -> str:
        state.config.logging.directory = args[0]
        return f"log directory {args[0]}"

    reg.add("log_dir", [Param("path", "str")], _log_dir, "Set the log directory")

    def _ext_log(state, args) -> str:
        state.config.logging.ext_trigger = bool(args[0])
        return f"external log trigger (status bit 12) {'armed' if args[0] else 'off'}"

    reg.add("ext_log", [Param("armed", "bool")], _ext_log,
            "Start/stop logging on the device's status bit 12")

    def _detect_rate(state, _args) -> str:
        if state.client is None:
            raise CommandError("connect first")
        state.start_rate_probe()
        return "measuring the sample rate over the next 5 s..."

    reg.add("detect_rate", [], _detect_rate,
            "Measure the actual sample rate from the packet rate")

    def _export_capture(state, args) -> str:
        path = state.export_capture(args[0] if args and args[0] else None)
        return f"capture written to {path}"

    reg.add("export_capture", [Param("path", "str", optional=True)],
            _export_capture, "Write the current trigger capture to parquet/csv")

    def _open_in_dataviewer(state, args) -> str:
        return state.open_in_dataviewer(args[0] if args and args[0] else None)

    reg.add("open_in_dataviewer", [Param("path", "str", optional=True)],
            _open_in_dataviewer,
            "Open a log (default: the last one) in uz_dataviewer")

    # --- session ----------------------------------------------------------
    def _save_state(state, args) -> str:
        state.config.save(args[0])
        return f"session saved to {args[0]}"

    reg.add("save_state", [Param("path", "str")], _save_state,
            "Save all settings to a JSON snapshot")

    def _load_state(state, args) -> str:
        state.load_config(args[0])
        return f"session loaded from {args[0]}"

    reg.add("load_state", [Param("path", "str")], _load_state,
            "Load a JSON settings snapshot (disconnect first)")

    def _export_script(state, args) -> str:
        from .session import export_script

        path = export_script(state, args[0])
        return f"script exported to {path}"

    reg.add("export_script", [Param("path", "str")], _export_script,
            "Export the session as a replayable .uzscript")

    def _run_script(state, args) -> str:
        from .session import run_script

        count = run_script(state, args[0])
        return f"executed {count} commands from {args[0]}"

    reg.add("run_script", [Param("path", "str")], _run_script,
            "Replay a .uzscript command file")

    # --- misc -------------------------------------------------------------
    def _import_properties(state, args) -> str:
        from .config import import_properties

        # Validate BEFORE the import mutates the config: set_geometry would
        # raise these afterwards and leave config.channels != ring.channels.
        if state.client is not None:
            raise CommandError("disconnect before importing properties")
        if state.logger is not None:
            raise CommandError("stop logging before importing properties")
        report = import_properties(args[0], state.config)
        # The import writes observables/visibility directly — rebuild the
        # logged list so the imported channels appear (and stay reserved).
        state.config.migrate_logged_slots()
        state.set_geometry(state.config.channels, state.config.samples_per_packet)
        ignored = f", ignored {len(report.ignored)}" if report.ignored else ""
        errors = f", {len(report.errors)} errors" if report.errors else ""
        return f"imported {len(report.applied)} settings from {args[0]}{ignored}{errors}"

    reg.add("import_properties", [Param("path", "str")], _import_properties,
            "Import a legacy JavaScope properties.ini")

    def _help(state, _args) -> None:
        for cmd in reg.all():
            state.console.info(f"{cmd.signature():44s} {cmd.help}")

    reg.add("help", [], _help, "List all commands")

    def _clear(state, _args) -> None:
        state.console.clear()

    reg.add("clear", [], _clear, "Clear the console")
