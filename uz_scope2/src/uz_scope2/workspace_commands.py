"""Command surface for acquired signals and dynamic plot windows."""

from __future__ import annotations

from uz_dataviewer.commands import CommandError, Param

from .workspace import PlotType, XyStyle


def _prefixed(value, prefix: str) -> int:
    token = str(value).strip().lower()
    if token.startswith(prefix + "_"):
        token = token[len(prefix) + 1 :]
    try:
        return int(token)
    except ValueError as exc:
        raise CommandError(f"expected {prefix}_N, got {value!r}") from exc


def _observable(state, value) -> int:
    token = str(value).strip()
    try:
        result = int(token)
    except ValueError:
        if state.header is None:
            raise CommandError("javascope.h is unavailable; use an observable index")
        candidates = (token, f"JSO_{token}" if not token.startswith("JSO_") else token)
        result = next(
            (state.header.observable_index[name] for name in candidates
             if name in state.header.observable_index),
            -1,
        )
    count = len(state.header.observables) if state.header else 2**31
    if not 0 <= result < count:
        raise CommandError(f"unknown observable: {value}")
    return result


def _window(state, value):
    wid = _prefixed(value, "window")
    window = state.workspace.get(wid)
    if window is None:
        raise CommandError(f"window_{wid} does not exist")
    return window


def _cell(state, window_value, plot_value):
    window = _window(state, window_value)
    number = _prefixed(plot_value, "plot")
    if not 1 <= number <= len(window.cells):
        raise CommandError(
            f"plot_{number} out of range for {window.token} (1..{len(window.cells)})"
        )
    return window, window.cells[number - 1], number


def _segment(state, value):
    sid = _prefixed(value, "signal")
    segment = state.segments.get(sid)
    if segment is None:
        raise CommandError(f"signal_{sid} is unavailable or has expired")
    return segment


def register_workspace_commands(reg) -> None:
    def acquire(state, args):
        segment = state.acquire_observable(_observable(state, args[0]))
        return f"acquired {segment.name} as {segment.token} on CH{segment.slot + 1}"

    reg.add("acquire", [Param("observable", "str")], acquire,
            "Acquire an observable in the first free hardware slot")

    def release(state, args):
        segment = _segment(state, args[0])
        slot = state.release_signal(segment.id)
        return f"released {segment.token} from CH{slot + 1}; history retained"

    reg.add("release", [Param("signal", "str")], release,
            "Release an active signal and map its slot to JSO_ZEROVALUE")

    def new_window(state, args):
        window = state.workspace.create(args[0] if args and args[0] else None)
        return f"created {window.token}"

    reg.add("new_plot_window", [Param("title", "str", optional=True)], new_window,
            "Create a dockable plot window")

    def close_window(state, args):
        window = _window(state, args[0])
        state.workspace.close(window.id)
        return f"closed {window.token}"

    reg.add("close_plot_window", [Param("window", "str")], close_window,
            "Close a plot window")

    def rename_window(state, args):
        window = _window(state, args[0])
        window.title = str(args[1])
        return f"renamed {window.token} to {window.title}"

    reg.add("rename_plot_window",
            [Param("window", "str"), Param("title", "str")], rename_window,
            "Rename a plot window")

    def set_grid(state, args):
        window = _window(state, args[0])
        window.set_grid(int(args[1]), int(args[2]))
        return f"{window.token} grid {window.rows}x{window.cols}"

    reg.add("set_grid",
            [Param("window", "str"), Param("rows", "int"), Param("cols", "int")],
            set_grid, "Set a plot window's subplot grid")

    def add_signal(state, args):
        _, cell, number = _cell(state, args[0], args[1])
        segment = _segment(state, args[2])
        cell.add(segment.id)
        return f"added {segment.token} to plot_{number}"

    reg.add("add_signal",
            [Param("window", "str"), Param("plot", "str"), Param("signal", "str")],
            add_signal, "Add a retained signal segment to a subplot")

    def add_observable(state, args):
        observable = _observable(state, args[2])
        segment = next((seg for seg in state.segments.active() if seg.observable == observable), None)
        if segment is None:
            raise CommandError(f"{state.observable_name(observable)} is not acquired")
        _, cell, number = _cell(state, args[0], args[1])
        cell.add(segment.id)
        return f"added {segment.name} to plot_{number}"

    reg.add("add_observable",
            [Param("window", "str"), Param("plot", "str"), Param("observable", "str")],
            add_observable, "Add the active segment for an observable to a subplot")

    def set_xy_observable(state, args):
        observable = _observable(state, args[2])
        segment = next((seg for seg in state.segments.active() if seg.observable == observable), None)
        if segment is None:
            raise CommandError(f"{state.observable_name(observable)} is not acquired")
        _, cell, _ = _cell(state, args[0], args[1])
        cell.xy_source = segment.id
        cell.plot_type = PlotType.XY
        cell.fit_pending = True

    reg.add("set_xy_observable",
            [Param("window", "str"), Param("plot", "str"), Param("observable", "str")],
            set_xy_observable, "Use an acquired observable as the XY X source")

    def set_axis_observable(state, args):
        observable = _observable(state, args[2])
        segment = next((seg for seg in state.segments.active() if seg.observable == observable), None)
        if segment is None:
            raise CommandError(f"{state.observable_name(observable)} is not acquired")
        _, cell, _ = _cell(state, args[0], args[1])
        if segment.id not in cell.segments:
            raise CommandError(f"{segment.name} is not in this plot")
        if str(args[3]).lower() == "right":
            if segment.id not in cell.y2_segments:
                cell.y2_segments.append(segment.id)
        elif segment.id in cell.y2_segments:
            cell.y2_segments.remove(segment.id)

    reg.add("set_axis_observable",
            [Param("window", "str"), Param("plot", "str"), Param("observable", "str"), Param("side", "str")],
            set_axis_observable, "Assign an acquired observable to a Y axis")

    def remove_signal(state, args):
        _, cell, number = _cell(state, args[0], args[1])
        segment = _segment(state, args[2])
        cell.remove(segment.id)
        return f"removed {segment.token} from plot_{number}"

    reg.add("remove_signal",
            [Param("window", "str"), Param("plot", "str"), Param("signal", "str")],
            remove_signal, "Remove a signal from a subplot")

    def clear_plot(state, args):
        _, cell, number = _cell(state, args[0], args[1])
        cell.segments.clear()
        cell.y2_segments.clear()
        cell.xy_source = None
        return f"cleared plot_{number}"

    reg.add("clear_plot", [Param("window", "str"), Param("plot", "str")],
            clear_plot, "Remove every signal from a subplot")

    def follow_live(state, args):
        window = _window(state, args[0])
        window.follow_live = bool(args[1])
        if window.follow_live:
            window.shared_x = None
        return f"{window.token} live follow {'on' if window.follow_live else 'off'}"

    reg.add("follow_live", [Param("window", "str"), Param("on", "bool")],
            follow_live, "Follow newest data; manual pan/zoom turns this off")

    def link_x(state, args):
        window = _window(state, args[0])
        window.link_x = bool(args[1])
        return f"{window.token} linked X {'on' if window.link_x else 'off'}"

    reg.add("link_x", [Param("window", "str"), Param("on", "bool")],
            link_x, "Link X axes inside one plot window")

    def plot_type(state, args):
        _, cell, _ = _cell(state, args[0], args[1])
        token = str(args[2]).strip().lower()
        try:
            cell.plot_type = next(t for t in PlotType if t.value.lower() == token)
        except StopIteration as exc:
            raise CommandError("plot type must be line/scatter/stairs/xy") from exc
        cell.fit_pending = True

    reg.add("set_plot_type",
            [Param("window", "str"), Param("plot", "str"), Param("type", "str")],
            plot_type, "Set line/scatter/stairs/xy plot type")

    def set_xy(state, args):
        _, cell, _ = _cell(state, args[0], args[1])
        segment = _segment(state, args[2])
        cell.xy_source = segment.id
        cell.plot_type = PlotType.XY
        cell.fit_pending = True

    reg.add("set_xy",
            [Param("window", "str"), Param("plot", "str"), Param("signal", "str")],
            set_xy, "Use a signal as an XY plot's X source")

    def xy_style(state, args):
        _, cell, _ = _cell(state, args[0], args[1])
        token = str(args[2]).strip().lower()
        try:
            cell.xy_style = next(t for t in XyStyle if t.value.lower() == token)
        except StopIteration as exc:
            raise CommandError("XY style must be line/markers/both") from exc

    reg.add("set_xy_style",
            [Param("window", "str"), Param("plot", "str"), Param("style", "str")],
            xy_style, "Set XY style to line, markers, or both")

    def set_axis(state, args):
        _, cell, _ = _cell(state, args[0], args[1])
        segment = _segment(state, args[2])
        side = str(args[3]).lower()
        if segment.id not in cell.segments:
            raise CommandError(f"{segment.token} is not in this plot")
        if side == "right":
            if segment.id not in cell.y2_segments:
                cell.y2_segments.append(segment.id)
        elif side == "left":
            if segment.id in cell.y2_segments:
                cell.y2_segments.remove(segment.id)
        else:
            raise CommandError("axis must be left or right")

    reg.add("set_axis", [Param("window", "str"), Param("plot", "str"),
                         Param("signal", "str"), Param("side", "str")],
            set_axis, "Assign a signal to the left or right Y axis")

    def toggle(field):
        def handler(state, args):
            _, cell, _ = _cell(state, args[0], args[1])
            setattr(cell, field, bool(args[2]))
            if field in ("cursors", "spy") and not bool(args[2]):
                setattr(cell, "cursor_x" if field == "cursors" else "spy_rect", None)
        return handler

    for name, field, help_text in (
        ("show_samples", "show_samples", "Show markers at raw samples"),
        ("cursors", "cursors", "Toggle measurement cursors"),
        ("spy", "spy", "Toggle the zoom spy inset"),
    ):
        reg.add(name, [Param("window", "str"), Param("plot", "str"),
                       Param("on", "bool")], toggle(field), help_text)

    def reset_view(state, args):
        _, cell, _ = _cell(state, args[0], args[1])
        cell.fit_pending = True

    reg.add("reset_view", [Param("window", "str"), Param("plot", "str")],
            reset_view, "Fit a subplot to retained data")

    def xlim(state, args):
        window, cell, _ = _cell(state, args[0], args[1])
        lo, hi = float(args[2]), float(args[3])
        if hi <= lo:
            raise CommandError("x maximum must be greater than minimum")
        cell.pending_x = (lo, hi)
        window.follow_live = False

    reg.add("set_x_lim", [Param("window", "str"), Param("plot", "str"),
                           Param("min", "float"), Param("max", "float")],
            xlim, "Set subplot X limits and detach live follow")

    def ylim(state, args):
        _, cell, _ = _cell(state, args[0], args[1])
        lo, hi = float(args[2]), float(args[3])
        if hi <= lo:
            raise CommandError("y maximum must be greater than minimum")
        cell.pending_y = (lo, hi)

    reg.add("set_y_lim", [Param("window", "str"), Param("plot", "str"),
                           Param("min", "float"), Param("max", "float")],
            ylim, "Set subplot Y limits")

    def export_relative(state, args):
        _, cell, _ = _cell(state, args[0], args[1])
        cell.export_relative = bool(args[2])

    reg.add("export_relative",
            [Param("window", "str"), Param("plot", "str"), Param("on", "bool")],
            export_relative, "Use relative time for visible-range CSV export")

    def export_data(state, args):
        from .session import export_plot
        window = _window(state, args[0])
        plot = _prefixed(args[1], "plot")
        rows = export_plot(
            state, window.id, plot, args[2],
            bool(args[3]) if len(args) > 3 and args[3] is not None else False,
        )
        return f"exported {rows} rows to {args[2]}"

    reg.add("export_data", [Param("window", "str"), Param("plot", "str"),
                             Param("path", "str"),
                             Param("relative", "bool", optional=True)],
            export_data, "Export the visible subplot range to CSV")

