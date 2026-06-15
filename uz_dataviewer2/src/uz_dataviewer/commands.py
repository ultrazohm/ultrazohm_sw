"""Unified command layer shared by the GUI and the console.

Every discrete user action -- changing the grid, dropping a signal, picking a
plot type, zooming -- is expressed as a *command*. Running a command mutates the
:class:`~uz_dataviewer.state.AppState` **and** echoes its canonical call (e.g.
``add_signal(plot_1, run_1, ia)``) to the console. The console therefore doubles
as a live, replayable log of the session: the same calls can be typed into the
console input or replayed from a saved ``.uzscript`` file.

A command has a name, a typed parameter list and a handler. Parameters of kind
``plot``/``run`` accept the friendly ``plot_1`` / ``run_2`` forms (or bare
integers); ``run`` also resolves a run *label* (file name) so scripts written
against ``load("Log.csv")`` keep working. The grammar is a single function call::

    name(arg1, arg2, ...)        # or just  name   for a no-arg command

This module owns the registry, the parser and the built-in command set. It must
not import GUI modules at run time (only :mod:`state` lazily) so it stays usable
from headless tests.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from typing import TYPE_CHECKING, Callable

if TYPE_CHECKING:  # pragma: no cover - typing only
    from .state import AppState


class CommandError(Exception):
    """Raised when a command cannot be parsed, resolved or executed."""


# -- model --------------------------------------------------------------------
@dataclass
class Param:
    name: str
    kind: str  # 'int' | 'float' | 'bool' | 'str' | 'plot' | 'run'
    optional: bool = False

    def display(self) -> str:
        return f"[{self.name}]" if self.optional else self.name


@dataclass
class Command:
    name: str
    params: list[Param]
    handler: Callable[["AppState", list], str | None]
    help: str = ""

    def signature(self) -> str:
        return f"{self.name}({', '.join(p.display() for p in self.params)})"


Handler = Callable[["AppState", list], "str | None"]


# -- parsing ------------------------------------------------------------------
_CALL_RE = re.compile(r"^\s*([A-Za-z_]\w*)\s*(?:\((.*)\))?\s*$", re.DOTALL)
_BARE_STR_RE = re.compile(r"^[\w./+\-:]+$")


def _split_args(argstr: str) -> list[str]:
    """Split a comma-separated argument string, honouring quotes."""
    args: list[str] = []
    cur: list[str] = []
    quote: str | None = None
    for ch in argstr:
        if quote is not None:
            if ch == quote:
                quote = None
            else:
                cur.append(ch)
        elif ch in ("'", '"'):
            quote = ch
        elif ch == ",":
            args.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    args.append("".join(cur).strip())
    return [a for a in args if a != ""]


def parse_call(text: str) -> tuple[str, list[str]]:
    """Parse ``name(a, b, ...)`` into ``(name, [a, b, ...])`` (raw string args)."""
    match = _CALL_RE.match(text)
    if not match:
        raise CommandError(f"Cannot parse command: {text!r}")
    name = match.group(1)
    argstr = match.group(2)
    args = _split_args(argstr) if argstr and argstr.strip() else []
    return name, args


# -- coercion -----------------------------------------------------------------
_TRUE = {"1", "true", "on", "yes"}
_FALSE = {"0", "false", "off", "no"}


def _parse_bool(raw) -> bool:
    if isinstance(raw, bool):
        return raw
    s = str(raw).strip().lower()
    if s in _TRUE:
        return True
    if s in _FALSE:
        return False
    raise CommandError(f"Expected a boolean (on/off), got {raw!r}")


def _parse_fwindow(raw) -> int:
    """Analysis time-source: ``custom`` -> 0, ``full`` -> -1, ``plot_N`` -> N."""
    if isinstance(raw, int):
        return raw
    s = str(raw).strip().lower()
    if s == "custom":
        return 0
    if s == "full":
        return -1
    if s.startswith("plot_"):
        s = s[len("plot_"):]
    try:
        return int(s)
    except ValueError as exc:  # noqa: TRY003
        raise CommandError(f"Expected custom/full/plot_N, got {raw!r}") from exc


def _plot_number(raw) -> int:
    if isinstance(raw, int):
        return raw
    s = str(raw).strip()
    if s.startswith("plot_"):
        s = s[len("plot_"):]
    try:
        return int(s)
    except ValueError as exc:  # noqa: TRY003
        raise CommandError(f"Expected a plot reference (plot_1), got {raw!r}") from exc


def _resolve_run(state: "AppState", raw) -> int:
    if isinstance(raw, int):
        run_id = raw
    else:
        s = str(raw).strip()
        if s.startswith("run_"):
            s = s[len("run_"):]
        if s.lstrip("-").isdigit():
            run_id = int(s)
        else:
            for run in state.registry.runs:
                if run.label == s:
                    return run.id
            raise CommandError(f"No loaded run named {s!r}")
    if state.registry.get(run_id) is None:
        raise CommandError(f"run_{run_id} is not loaded")
    return run_id


def _coerce_one(state: "AppState", param: Param, raw):
    kind = param.kind
    if kind == "int":
        return int(str(raw).strip())
    if kind == "float":
        return float(str(raw).strip())
    if kind == "bool":
        return _parse_bool(raw)
    if kind == "str":
        return str(raw)
    if kind == "plot":
        n = _plot_number(raw)
        if not 1 <= n <= state.cell_count:
            raise CommandError(f"plot_{n} out of range (1..{state.cell_count})")
        return n
    if kind == "run":
        return _resolve_run(state, raw)
    if kind == "fwindow":
        return _parse_fwindow(raw)
    raise CommandError(f"Unknown parameter kind: {kind}")


def _coerce_args(state: "AppState", cmd: Command, args: list) -> list:
    required = [p for p in cmd.params if not p.optional]
    if len(args) < len(required):
        raise CommandError(f"{cmd.name} expects {cmd.signature()}")
    if len(args) > len(cmd.params):
        raise CommandError(f"{cmd.name} takes at most {len(cmd.params)} argument(s): {cmd.signature()}")
    out = []
    for i, param in enumerate(cmd.params):
        if i < len(args):
            out.append(_coerce_one(state, param, args[i]))
        else:
            out.append(None)
    return out


# -- canonical formatting (for the echo / script export) ----------------------
def _fmt_float(v: float) -> str:
    return f"{float(v):.6g}"


def _fmt_str(s: str) -> str:
    return s if _BARE_STR_RE.match(s) else '"' + s.replace('"', '\\"') + '"'


def format_call(cmd: Command, values: list) -> str:
    parts: list[str] = []
    for param, value in zip(cmd.params, values):
        if value is None:
            continue
        if param.kind == "plot":
            parts.append(f"plot_{int(value)}")
        elif param.kind == "run":
            parts.append(f"run_{int(value)}")
        elif param.kind == "fwindow":
            v = int(value)
            parts.append("custom" if v == 0 else "full" if v == -1 else f"plot_{v}")
        elif param.kind == "bool":
            parts.append("true" if value else "false")
        elif param.kind == "float":
            parts.append(_fmt_float(value))
        elif param.kind == "int":
            parts.append(str(int(value)))
        else:
            parts.append(_fmt_str(str(value)))
    return f"{cmd.name}({', '.join(parts)})"


# -- registry -----------------------------------------------------------------
class CommandRegistry:
    """Holds the command set and dispatches calls against an :class:`AppState`."""

    def __init__(self) -> None:
        self._commands: dict[str, Command] = {}
        register_builtins(self)

    def add(self, name: str, params: list[Param], handler: Handler, help: str = "") -> None:
        self._commands[name] = Command(name, params, handler, help)

    def get(self, name: str) -> Command | None:
        return self._commands.get(name)

    def names(self) -> list[str]:
        return sorted(self._commands)

    def all(self) -> list[Command]:
        return [self._commands[n] for n in self.names()]

    def complete(self, prefix: str) -> list[str]:
        """Command names that start with the (head of the) given prefix."""
        head = prefix.split("(", 1)[0].strip()
        if not head:
            return []
        return [n for n in self.names() if n.startswith(head)]

    def execute(self, state: "AppState", name: str, args: list, *, echo: bool = True) -> str | None:
        cmd = self._commands.get(name)
        if cmd is None:
            raise CommandError(f"Unknown command: {name}")
        values = _coerce_args(state, cmd, args)
        if echo:
            state.console.command(format_call(cmd, values))
        message = cmd.handler(state, values)
        if message:
            state.console.ok(message)
        return message

    def dispatch(self, state: "AppState", text: str) -> None:
        """Parse and run a line of text typed into the console. Errors are logged."""
        text = text.strip()
        if not text or text.startswith("#"):
            return
        try:
            name, args = parse_call(text)
            self.execute(state, name, args)
        except CommandError as exc:
            state.console.error(str(exc))
        except Exception as exc:  # noqa: BLE001 - surface unexpected errors
            state.console.error(f"{text}: {exc}")

    def echo(self, state: "AppState", name: str, values: list) -> None:
        """Log a command without executing it (gesture already applied by ImPlot)."""
        cmd = self._commands.get(name)
        if cmd is not None:
            state.console.command(format_call(cmd, values))


# -- built-in commands --------------------------------------------------------
def register_builtins(reg: CommandRegistry) -> None:
    # Imported lazily inside handlers to avoid a GUI/state import cycle.
    from .state import PlotType

    def _cell(state, plot_n):
        return state.cells[plot_n - 1]

    def _resolve_plot_type(token: str) -> "PlotType":
        for t in PlotType:
            if t.value.lower() == str(token).lower() or t.name.lower() == str(token).lower():
                return t
        raise CommandError(f"Unknown plot type {token!r}; one of {PlotType.labels()}")

    # -- data / layout ----------------------------------------------------
    def load(state, a):
        path, start = a
        run = state.load_sync(path)
        if run is not None and start is not None:
            run.set_time_origin(float(start))

    reg.add("load", [Param("path", "str"), Param("start", "float", optional=True)], load,
            "Load a .csv/.parquet log; the optional start normalises the time origin.")

    def normalize_time(state, a):
        run_id, start = a
        run = state.registry.get(run_id)
        if run is None:
            raise CommandError(f"run_{run_id} is not loaded")
        run.set_time_origin(0.0 if start is None else float(start))

    reg.add("normalize_time", [Param("run", "run"), Param("start", "float", optional=True)],
            normalize_time, "Shift a run so its first sample sits at start (default 0).")

    def reset_time(state, a):
        run = state.registry.get(a[0])
        if run is None:
            raise CommandError(f"run_{a[0]} is not loaded")
        run.set_time_origin(None)

    reg.add("reset_time", [Param("run", "run")], reset_time,
            "Restore a run's original (un-normalised) timestamps.")

    def set_grid(state, a):
        state.set_grid(max(1, a[0]), max(1, a[1]))

    reg.add("set_grid", [Param("rows", "int"), Param("cols", "int")], set_grid,
            "Set the subplot grid to rows x cols.")

    def link_x(state, a):
        state.link_x = a[0]

    reg.add("link_x", [Param("on", "bool")], link_x, "Link/unlink the X axes across subplots.")

    def set_max_points(state, a):
        state.max_points = max(100, a[0])

    reg.add("set_max_points", [Param("n", "int")], set_max_points,
            "Max points drawn per signal (downsample budget).")

    def remove_run(state, a):
        state.remove_run(a[0])

    reg.add("remove_run", [Param("run", "run")], remove_run, "Remove a loaded run and its plots.")

    def set_active(state, a):
        run = state.registry.get(a[0])
        if run is not None:
            run.active = a[1]

    reg.add("set_active", [Param("run", "run"), Param("on", "bool")], set_active,
            "Show/hide a run without removing it.")

    # -- per-plot ---------------------------------------------------------
    def add_signal(state, a):
        plot_n, run_id, name = a
        if state.registry.get_signal(run_id, name) is None:
            raise CommandError(f"run_{run_id} has no signal {name!r}")
        _cell(state, plot_n).add((run_id, name))

    reg.add("add_signal", [Param("plot", "plot"), Param("run", "run"), Param("signal", "str")],
            add_signal, "Add a signal to a subplot.")

    def remove_signal(state, a):
        plot_n, run_id, name = a
        _cell(state, plot_n).remove((run_id, name))

    reg.add("remove_signal", [Param("plot", "plot"), Param("run", "run"), Param("signal", "str")],
            remove_signal, "Remove a signal from a subplot.")

    def clear_plot(state, a):
        _cell(state, a[0]).signals.clear()

    reg.add("clear_plot", [Param("plot", "plot")], clear_plot, "Remove all signals from a subplot.")

    def set_plot_type(state, a):
        _cell(state, a[0]).plot_type = _resolve_plot_type(a[1])

    reg.add("set_plot_type", [Param("plot", "plot"), Param("type", "str")], set_plot_type,
            "Set a subplot's type (line/scatter/stairs/xy).")

    def set_x_lim(state, a):
        plot_n, lo, hi = a
        cell = _cell(state, plot_n)
        cell.pending_x_lim = (lo, hi)
        if state.link_x:
            state.shared_x = (lo, hi)

    reg.add("set_x_lim", [Param("plot", "plot"), Param("min", "float"), Param("max", "float")],
            set_x_lim, "Set a subplot's X-axis limits.")

    def set_y_lim(state, a):
        plot_n, lo, hi = a
        _cell(state, plot_n).pending_y_lim = (lo, hi)

    reg.add("set_y_lim", [Param("plot", "plot"), Param("min", "float"), Param("max", "float")],
            set_y_lim, "Set a subplot's Y-axis limits.")

    def reset_view(state, a):
        _cell(state, a[0]).fit_pending = True

    reg.add("reset_view", [Param("plot", "plot")], reset_view, "Auto-fit a subplot to its data extent.")

    def show_samples(state, a):
        _cell(state, a[0]).show_samples = a[1]

    reg.add("show_samples", [Param("plot", "plot"), Param("on", "bool")], show_samples,
            "Toggle per-sample markers on a subplot.")

    def spy(state, a):
        _cell(state, a[0]).spy = a[1]

    reg.add("spy", [Param("plot", "plot"), Param("on", "bool")], spy,
            "Toggle the spy (drag-rect zoom inset) on a subplot.")

    def set_spy_rect(state, a):
        plot_n, xmin, ymin, xmax, ymax = a
        cell = _cell(state, plot_n)
        cell.spy = True
        cell.spy_rect = (xmin, ymin, xmax, ymax)

    reg.add("set_spy_rect",
            [Param("plot", "plot"), Param("xmin", "float"), Param("ymin", "float"),
             Param("xmax", "float"), Param("ymax", "float")],
            set_spy_rect, "Position the spy rectangle (enables spy).")

    def set_xy(state, a):
        plot_n, run_id, name = a
        if state.registry.get_signal(run_id, name) is None:
            raise CommandError(f"run_{run_id} has no signal {name!r}")
        cell = _cell(state, plot_n)
        cell.xy_source = (run_id, name)
        cell.plot_type = PlotType.XY
        cell.fit_pending = True

    reg.add("set_xy", [Param("plot", "plot"), Param("run", "run"), Param("signal", "str")],
            set_xy, "Use a signal as the X axis (XY plot) for a subplot.")

    def cursors(state, a):
        _cell(state, a[0]).cursors = a[1]

    reg.add("cursors", [Param("plot", "plot"), Param("on", "bool")], cursors,
            "Toggle two measurement cursors (Δx / frequency readout) on a subplot.")

    def set_cursors(state, a):
        plot_n, x1, x2 = a
        cell = _cell(state, plot_n)
        cell.cursors = True
        cell.cursor_x = (x1, x2)

    reg.add("set_cursors", [Param("plot", "plot"), Param("x1", "float"), Param("x2", "float")],
            set_cursors, "Place the two cursors at x1 and x2 (enables cursors).")

    def set_axis(state, a):
        plot_n, run_id, name, side = a
        ref = (run_id, name)
        cell = _cell(state, plot_n)
        if ref not in cell.signals:
            raise CommandError(f"{name!r} is not in plot_{plot_n}")
        side = str(side).lower()
        if side in ("right", "y2", "secondary"):
            if ref not in cell.y2_signals:
                cell.y2_signals.append(ref)
        elif side in ("left", "y1", "primary"):
            if ref in cell.y2_signals:
                cell.y2_signals.remove(ref)
        else:
            raise CommandError("side must be 'left' or 'right'")
        cell.fit_pending = True

    reg.add("set_axis", [Param("plot", "plot"), Param("run", "run"), Param("signal", "str"), Param("side", "str")],
            set_axis, "Assign a signal to the left or right Y axis of a subplot.")

    def export_data(state, a):
        from .session import export_data as _export
        plot_n, path, relative = a
        n = _export(state, plot_n - 1, path, bool(relative))
        return f"Exported {n} column(s) to {path}"

    reg.add("export_data", [Param("plot", "plot"), Param("path", "str"), Param("relative", "bool", optional=True)],
            export_data, "Export a subplot's signals to CSV (relative=true zeroes the start time).")

    def set_export_relative(state, a):
        _cell(state, a[0]).export_relative = a[1]

    reg.add("set_export_relative", [Param("plot", "plot"), Param("on", "bool")], set_export_relative,
            "Toggle 'start time at 0' for a subplot's CSV export.")

    # -- analysis windows (FFT, Histogram) --------------------------------
    # The two windows share a control surface, so their common commands are
    # registered from one factory; the transform-specific options (DC/Hann/log,
    # bins) and the compute/export handlers are added per window below.
    def _register_analysis_common(prefix: str, attr: str, noun: str) -> None:
        def _cfg(state):
            return getattr(state, attr)

        def source(state, a):
            run_id, name = a
            if state.registry.get_signal(run_id, name) is None:
                raise CommandError(f"run_{run_id} has no signal {name!r}")
            cfg = _cfg(state)
            ref = (run_id, name)
            if ref not in cfg.sources:
                cfg.sources.append(ref)
            cfg.compute_requested = True

        reg.add(f"{prefix}_source", [Param("run", "run"), Param("signal", "str")], source,
                f"Add a signal to the {noun} window (it can show several at once).")

        def clear(state, a):
            _cfg(state).sources.clear()

        reg.add(f"{prefix}_clear", [], clear, f"Remove all signals from the {noun} window.")

        def remove(state, a):
            cfg = _cfg(state)
            ref = (a[0], a[1])
            if ref in cfg.sources:
                cfg.sources.remove(ref)
            cfg.compute_requested = True

        reg.add(f"{prefix}_remove", [Param("run", "run"), Param("signal", "str")], remove,
                f"Remove a signal from the {noun} window.")

        def follow(state, a):
            cfg = _cfg(state)
            old = cfg.follow_plot
            cfg.follow_plot = a[0]
            if a[0] == 0:  # Custom: seed t-range from the window we were just on
                cfg.x_min, cfg.x_max = state.resolve_x_window(old, (cfg.x_min, cfg.x_max), cfg.sources)
            elif a[0] >= 1:  # following a plot -> compute it; custom/full do not
                cfg.compute_requested = True

        reg.add(f"{prefix}_follow", [Param("target", "fwindow")], follow,
                f"Set the {noun} time window source (custom / full / plot_N).")

        def rng(state, a):
            cfg = _cfg(state)
            cfg.x_min, cfg.x_max = a[0], a[1]

        reg.add(f"{prefix}_range", [Param("min", "float"), Param("max", "float")], rng,
                f"Set the {noun} custom time window.")

        def xlim(state, a):
            _cfg(state).pending_x_lim = (a[0], a[1])

        reg.add(f"{prefix}_xlim", [Param("min", "float"), Param("max", "float")], xlim,
                f"Set the {noun} plot's X-axis view limits.")

    _register_analysis_common("fft", "fft", "FFT")
    _register_analysis_common("hist", "histogram", "Histogram")

    def fft(state, a):
        state.fft.compute_requested = True
        state.focus_fft = True

    reg.add("fft", [], fft, "Recompute and focus the FFT window.")

    def fft_remove_dc(state, a):
        state.fft.remove_dc = a[0]
        state.fft.compute_requested = True

    reg.add("fft_remove_dc", [Param("on", "bool")], fft_remove_dc, "Toggle FFT DC removal.")

    def fft_hann(state, a):
        state.fft.window = a[0]
        state.fft.compute_requested = True

    reg.add("fft_hann", [Param("on", "bool")], fft_hann, "Toggle the FFT Hann window.")

    def fft_logx(state, a):
        state.fft.log_x = a[0]

    reg.add("fft_logx", [Param("on", "bool")], fft_logx, "Toggle the FFT log X axis.")

    def fft_logy(state, a):
        state.fft.log_y = a[0]

    reg.add("fft_logy", [Param("on", "bool")], fft_logy, "Toggle the FFT log Y axis.")

    def fft_export(state, a):
        from .session import export_fft
        n = export_fft(state, a[0])
        return f"Exported {n} column(s) to {a[0]}"

    reg.add("fft_export", [Param("path", "str")], fft_export, "Export the FFT spectra to CSV.")

    def histogram(state, a):
        state.histogram.compute_requested = True
        state.focus_histogram = True

    reg.add("histogram", [], histogram, "Recompute and focus the Histogram window.")

    def hist_bins(state, a):
        state.histogram.bins = max(1, a[0])
        state.histogram.compute_requested = True

    reg.add("hist_bins", [Param("n", "int")], hist_bins, "Set the Histogram bin count.")

    def hist_export(state, a):
        from .session import export_histogram
        n = export_histogram(state, a[0])
        return f"Exported {n} column(s) to {a[0]}"

    reg.add("hist_export", [Param("path", "str")], hist_export, "Export the histogram bins to CSV.")

    # -- session ----------------------------------------------------------
    def save_state(state, a):
        from .session import save_state as _save
        _save(state, a[0])
        return f"Saved state to {a[0]}"

    reg.add("save_state", [Param("path", "str")], save_state, "Save the GUI state to a JSON file.")

    def load_state(state, a):
        from .session import load_state as _load
        _load(state, a[0])
        return f"Restored state from {a[0]}"

    reg.add("load_state", [Param("path", "str")], load_state, "Restore the GUI state from a JSON file.")

    def export_script(state, a):
        from .session import export_script as _export
        _export(state, a[0])
        return f"Exported session script to {a[0]}"

    reg.add("export_script", [Param("path", "str")], export_script,
            "Write the session as a replayable .uzscript.")

    def run_script(state, a):
        from .session import run_script as _run
        n = _run(state, a[0])
        return f"Ran {n} command(s) from {a[0]}"

    reg.add("run_script", [Param("path", "str")], run_script, "Replay commands from a .uzscript file.")

    # -- console / help ---------------------------------------------------
    def clear_console(state, a):
        state.console.clear()

    reg.add("clear_console", [], clear_console, "Clear the console log.")

    def help_cmd(state, a):
        name = a[0]
        if name:
            cmd = reg.get(str(name))
            if cmd is None:
                raise CommandError(f"Unknown command: {name}")
            state.console.info(f"{cmd.signature()} -- {cmd.help}")
        else:
            for cmd in reg.all():
                state.console.info(f"{cmd.signature()} -- {cmd.help}")

    reg.add("help", [Param("name", "str", optional=True)], help_cmd,
            "List commands, or show help for one.")
