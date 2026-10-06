"""Command layer for uz_scope2, built on uz_dataviewer's registry machinery.

Every UI action routes through a command: it mutates the
:class:`~uz_scope2.state.ScopeAppState`, echoes its canonical call to the
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
    from .workspace_commands import register_workspace_commands

    register_workspace_commands(reg)
    # --- connection -------------------------------------------------------
    def _connect(state: "ScopeAppState", args) -> str:
        ip = args[0].strip() if args and args[0] else ""
        if ip:
            # An explicit ip becomes the new default (same as set_ip + connect).
            state.config.ip = ip
        state.connect()
        return f"connecting to {state.config.ip}:{state.config.port}"

    reg.add(
        "connect",
        [Param("ip", "str", optional=True)],
        _connect,
        "Connect to the UltraZohm (or the test server); an ip argument overrides and updates the saved address",
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
        return f"visible window {seconds:g} s"

    reg.add("set_window", [Param("seconds", "float")], _set_window,
            "Set the visible time window of the rolling display")

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
        state.config.channel_settings[slot].visible = bool(args[1])
        return f"CH{slot + 1} {'shown' if args[1] else 'hidden'}"

    reg.add("ch_visible", [Param("channel", "int"), Param("visible", "bool")],
            _ch_visible, "Show/hide a channel in the plot")

    def _ch_scale(state, args) -> str:
        slot = _slot(state, args[0])
        scale = float(args[1])
        if scale == 0:
            raise CommandError("scale must be non-zero")
        state.config.channel_settings[slot].scale = scale
        state.segments.update_style(slot, scale=scale)
        return None

    reg.add("ch_scale", [Param("channel", "int"), Param("scale", "float")],
            _ch_scale, "Set a channel's display scale divisor")

    def _ch_offset(state, args) -> str:
        slot = _slot(state, args[0])
        state.config.channel_settings[slot].offset = float(args[1])
        state.segments.update_style(slot, offset=float(args[1]))
        return None

    reg.add("ch_offset", [Param("channel", "int"), Param("offset", "float")],
            _ch_offset, "Set a channel's display offset")

    def _enable_all(state, args) -> str:
        show = bool(args[0])
        for ch in state.config.channel_settings:
            ch.visible = show
        return f"all channels {'shown' if show else 'hidden'}"

    reg.add("enable_all", [Param("visible", "bool")], _enable_all,
            "Show or hide all channels")

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
        }[mode]
        return f"history mode {mode} — {detail} (restarts the session history)"

    reg.add("history_mode", [Param("mode", "str")], _history_mode,
            "Bounded history backend: off or ram envelope")

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

    def _history_clear(state, _args) -> str:
        state.history.clear()
        state.segments.clear()
        for slot, ch in enumerate(state.config.channel_settings):
            if ch.observable != 0:
                state.segments.start(slot, ch.observable, state.observable_name(ch.observable), state.ring.total_written, scale=ch.scale, offset=ch.offset, color=ch.color)
        return "bounded history cleared"

    reg.add("history_clear", [], _history_clear,
            "Forget the collected session history (ring is untouched)")

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
        from .session import save_state
        save_state(state, args[0])
        return f"session saved to {args[0]}"

    reg.add("save_state", [Param("path", "str")], _save_state,
            "Save all settings to a JSON snapshot")

    def _load_state(state, args) -> str:
        from .session import load_state
        load_state(state, args[0])
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

        report = import_properties(args[0], state.config)
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
