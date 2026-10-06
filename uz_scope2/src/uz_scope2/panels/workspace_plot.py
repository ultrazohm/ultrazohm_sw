"""Dynamic, bounded-history plot windows with Data Viewer interactions."""

from __future__ import annotations

import math
from pathlib import Path
import time

import numpy as np
from imgui_bundle import imgui, implot

try:
    from imgui_bundle import portable_file_dialogs as pfd
except Exception:  # pragma: no cover
    pfd = None

from .signals import SIGNAL_DND
from ..workspace import GRID_PRESETS, PlotType, XyStyle


def _color(value: str | None):
    if not value or len(value) != 7 or not value.startswith("#"):
        return None
    try:
        rgb = [int(value[i:i + 2], 16) / 255.0 for i in (1, 3, 5)]
    except ValueError:
        return None
    return imgui.ImVec4(*rgb, 1.0)


class WorkspacePlotPanel:
    def __init__(self) -> None:
        self._next_refresh = 0.0
        self._cache: dict[tuple[int, int, int, int, int], tuple[np.ndarray, np.ndarray]] = {}
        self._ranges: dict[tuple[int, int], tuple[float, float]] = {}
        self._cursor_text: dict[tuple[int, int], str] = {}
        self._export_dialog: tuple | None = None

    @staticmethod
    def _emit(state, name, *args) -> None:
        try:
            state.commands.execute(state, name, list(args))
        except Exception as exc:
            state.console.error(str(exc))

    def render(self, state, window) -> None:
        self._poll_export(state)
        self._toolbar(state, window)
        imgui.separator()
        now = time.monotonic()
        refresh = now >= self._next_refresh
        if refresh:
            self._next_refresh = now + 1.0 / max(state.config.refresh_hz, 1.0)
            self._cache.clear()
        self._trigger_window(state, window)

        region = imgui.get_content_region_avail()
        spacing = 4.0
        width = (region.x - spacing * (window.cols - 1)) / window.cols
        height = (region.y - spacing * (window.rows - 1)) / window.rows
        for row in range(window.rows):
            for col in range(window.cols):
                index = row * window.cols + col
                if index >= len(window.cells):
                    continue
                imgui.begin_group()
                self._cell(state, window, index, width, height)
                imgui.end_group()
                if col < window.cols - 1:
                    imgui.same_line(0.0, spacing)

    def _toolbar(self, state, window) -> None:
        if imgui.button("Run" if state.frozen else "Stop"):
            self._emit(state, "run" if state.frozen else "stop_scope")
        imgui.same_line()
        label = "Live" if window.follow_live else "Resume live"
        if imgui.button(label):
            self._emit(state, "follow_live", window.token, True)
        imgui.same_line()
        presets = [f"{r}x{c}" for r, c in GRID_PRESETS]
        current = f"{window.rows}x{window.cols}"
        try:
            selected = presets.index(current)
        except ValueError:
            selected = 0
        imgui.set_next_item_width(80)
        changed, selected = imgui.combo("##grid", selected, presets)
        if changed:
            rows, cols = GRID_PRESETS[selected]
            self._emit(state, "set_grid", window.token, rows, cols)
        imgui.same_line()
        changed, linked = imgui.checkbox("Link X", window.link_x)
        if changed:
            self._emit(state, "link_x", window.token, linked)
        imgui.same_line()
        if imgui.button("+ Plot window"):
            self._emit(state, "new_plot_window")
        if window.id != 1:
            imgui.same_line()
            if imgui.button("Close window"):
                self._emit(state, "close_plot_window", window.token)

    def _poll_export(self, state) -> None:
        if self._export_dialog is None:
            return
        dialog, window_token, plot_token, relative = self._export_dialog
        if not dialog.ready():
            return
        path = dialog.result()
        self._export_dialog = None
        if path:
            path = Path(path)
            if path.suffix.lower() != ".csv":
                path = path.with_suffix(".csv")
            self._emit(state, "export_data", window_token, plot_token, path, relative)

    def _cell_header(self, state, window, cell, index) -> None:
        plot_token = f"plot_{index + 1}"
        imgui.push_id(f"{window.id}_{index}")
        labels = [item.value for item in PlotType]
        selected = list(PlotType).index(cell.plot_type)
        imgui.set_next_item_width(90)
        changed, selected = imgui.combo("##type", selected, labels)
        if changed:
            self._emit(state, "set_plot_type", window.token, plot_token, labels[selected])
        imgui.same_line()
        if imgui.small_button("Reset"):
            self._emit(state, "reset_view", window.token, plot_token)
        imgui.same_line()
        if imgui.small_button("Clear"):
            self._emit(state, "clear_plot", window.token, plot_token)
        if cell.plot_type is not PlotType.XY:
            imgui.same_line()
            changed, value = imgui.checkbox("samples", cell.show_samples)
            if changed:
                self._emit(state, "show_samples", window.token, plot_token, value)
            imgui.same_line()
            changed, value = imgui.checkbox("spy", cell.spy)
            if changed:
                self._emit(state, "spy", window.token, plot_token, value)
            imgui.same_line()
            changed, value = imgui.checkbox("cursors", cell.cursors)
            if changed:
                self._emit(state, "cursors", window.token, plot_token, value)
        else:
            choices = [sid for sid in cell.segments if state.segments.get(sid)]
            if choices:
                imgui.same_line()
                names = [state.segments.get(sid).name.removeprefix("JSO_") for sid in choices]
                selected = choices.index(cell.xy_source) if cell.xy_source in choices else 0
                imgui.set_next_item_width(110)
                changed, selected = imgui.combo("##xsource", selected, names)
                if changed or cell.xy_source is None:
                    self._emit(state, "set_xy", window.token, plot_token, f"signal_{choices[selected]}")
            imgui.same_line()
            styles = [item.value for item in XyStyle]
            selected = list(XyStyle).index(cell.xy_style)
            imgui.set_next_item_width(85)
            changed, selected = imgui.combo("##xystyle", selected, styles)
            if changed:
                self._emit(state, "set_xy_style", window.token, plot_token, styles[selected])
        imgui.same_line()
        if imgui.small_button("Export") and cell.segments and pfd is not None and self._export_dialog is None:
            name = f"window_{window.id}_plot_{index + 1}.csv"
            self._export_dialog = (
                pfd.save_file("Export plot data", name, ["CSV (*.csv)", "*.csv"]),
                window.token, plot_token, cell.export_relative,
            )
        imgui.same_line()
        changed, value = imgui.checkbox("start at 0", cell.export_relative)
        if changed:
            self._emit(state, "export_relative", window.token, plot_token, value)
        imgui.pop_id()

    def _trigger_window(self, state, window) -> None:
        engine = state.engine
        capture = engine.capture if engine is not None else None
        if capture is None or not window.follow_live:
            return
        if capture.sequence != window.capture_sequence:
            window.capture_sequence = capture.sequence
            dt = state.timestep_s
            window.shared_x = (
                capture.start_index * dt,
                (capture.start_index + capture.data.shape[1]) * dt,
            )
        if engine.mode == "auto" and engine.capture_is_stale():
            window.shared_x = None

    def _target_range(self, state, window) -> tuple[float, float]:
        if window.follow_live and window.shared_x is not None:
            return window.shared_x
        end = state.ring.total_written * state.timestep_s
        return end - state.config.window_seconds, end

    def _cell(self, state, window, index: int, width: float, height: float) -> None:
        cell = window.cells[index]
        self._cell_header(state, window, cell, index)
        plot_h = max(100.0, height - 30.0 - (80.0 if cell.spy else 0.0))
        key = (window.id, index)
        target = self._target_range(state, window)
        if cell.pending_x is not None:
            target = cell.pending_x
            cell.pending_x = None
            window.follow_live = False
            window.shared_x = target
        elif not window.follow_live:
            target = self._ranges.get(key, window.shared_x or target)

        if cell.plot_type is PlotType.XY:
            self._xy_cell(state, window, cell, index, width, plot_h, target)
            return

        if cell.fit_pending:
            implot.set_next_axes_to_fit()
        if implot.begin_plot(f"##w{window.id}_p{index}", imgui.ImVec2(width, plot_h)):
            yflags = 0 if state.fix_axis else implot.AxisFlags_.auto_fit
            implot.setup_axes("time [s]", "", 0, yflags)
            if cell.y2_segments:
                implot.setup_axis(implot.ImAxis_.y2, "", implot.AxisFlags_.aux_default)
            if cell.pending_y is not None:
                implot.setup_axis_limits(
                    implot.ImAxis_.y1, cell.pending_y[0], cell.pending_y[1],
                    imgui.Cond_.always,
                )
                cell.pending_y = None
            if window.follow_live or cell.fit_pending:
                implot.setup_axis_limits(
                    implot.ImAxis_.x1, target[0], target[1], imgui.Cond_.always
                )
            elif window.link_x and window.shared_x is not None:
                implot.setup_axis_limits(
                    implot.ImAxis_.x1,
                    window.shared_x[0],
                    window.shared_x[1],
                    imgui.Cond_.always,
                )

            limits = implot.get_plot_limits()
            xlo, xhi = float(limits.x.min), float(limits.x.max)
            if not math.isfinite(xlo) or not math.isfinite(xhi) or xhi <= xlo:
                xlo, xhi = target
            self._plot_segments(state, window, cell, index, xlo, xhi, width)
            self._accept_drop(state, window, index)
            if cell.cursors:
                self._cursors(state, window, cell, index)
            if cell.spy:
                self._spy_rect(cell)
            self._trigger_guides(state, cell)
            limits = implot.get_plot_limits()
            current = (float(limits.x.min), float(limits.x.max))
            self._ranges[key] = current
            state.last_plot_ranges[key] = current
            self._interaction_follow(state, window, current)
            implot.end_plot()
        cell.fit_pending = False

        cursor_text = self._cursor_text.get(key)
        if cell.cursors and cursor_text:
            imgui.text_disabled(cursor_text)

        if cell.spy:
            self._spy(state, window, cell, index, width, max(60.0, height - plot_h))

    def _plot_segments(self, state, window, cell, index, xlo, xhi, width) -> None:
        start = math.floor(xlo / state.timestep_s)
        stop = math.ceil(xhi / state.timestep_s)
        budget = max(200, int(width) * 2)
        for order, sid in enumerate(list(cell.segments)):
            segment = state.segments.get(sid)
            if segment is None:
                continue
            cache_key = (window.id, index, sid, start, stop)
            series = self._cache.get(cache_key)
            if series is None:
                series = state.segments.query(
                    state.history, state.ring, sid, start, stop, budget,
                    state.timestep_s,
                )
                self._cache[cache_key] = series
            xs, ys = series
            if xs.size == 0:
                continue
            scale = segment.scale if abs(segment.scale) > 1e-12 else 1.0
            ys = (ys + segment.offset) / scale
            label = f"{segment.name.removeprefix('JSO_')}##{sid}"
            implot.set_axis(
                implot.ImAxis_.y2 if sid in cell.y2_segments else implot.ImAxis_.y1
            )
            spec = implot.Spec()
            custom = _color(segment.color)
            if custom is not None:
                spec.line_color = custom
            markers = cell.show_samples or cell.plot_type is PlotType.SCATTER
            if markers:
                spec.marker = implot.Marker_.circle
            if cell.plot_type is PlotType.LINE:
                implot.plot_line(label, xs, ys, spec)
            elif cell.plot_type is PlotType.SCATTER:
                implot.plot_scatter(label, xs, ys, spec)
            else:
                implot.plot_stairs(label, xs, ys, spec)
            self._legend_popup(state, window, index, cell, segment)

    def _xy_cell(self, state, window, cell, index, width, height, time_range) -> None:
        if cell.fit_pending:
            implot.set_next_axes_to_fit()
        if not implot.begin_plot(
            f"##w{window.id}_xy{index}", imgui.ImVec2(width, height)
        ):
            return
        xsegment = state.segments.get(cell.xy_source) if cell.xy_source else None
        xlabel = (
            xsegment.name.removeprefix("JSO_") if xsegment is not None else "X"
        )
        implot.setup_axes(xlabel, "")
        start = math.floor(time_range[0] / state.timestep_s)
        stop = math.ceil(time_range[1] / state.timestep_s)
        budget = max(200, int(width) * 2)
        if xsegment is not None:
            xt, xv = state.segments.query(
                state.history, state.ring, xsegment.id, start, stop, budget,
                state.timestep_s,
            )
            for order, sid in enumerate(cell.segments):
                segment = state.segments.get(sid)
                if segment is None or sid == xsegment.id:
                    continue
                yt, yv = state.segments.query(
                    state.history, state.ring, sid, start, stop, budget,
                    state.timestep_s,
                )
                if xt.size == 0 or yt.size == 0:
                    continue
                lo, hi = max(xt[0], yt[0]), min(xt[-1], yt[-1])
                mask = (xt >= lo) & (xt <= hi)
                xs = xv[mask]
                ys = np.interp(xt[mask], yt, yv)
                spec = implot.Spec()
                if cell.xy_style in (XyStyle.MARKERS, XyStyle.BOTH):
                    spec.marker = implot.Marker_.circle
                label = f"{segment.name.removeprefix('JSO_')}##{sid}"
                if cell.xy_style is XyStyle.MARKERS:
                    implot.plot_scatter(label, xs, ys, spec)
                else:
                    implot.plot_line(label, xs, ys, spec)
        self._accept_drop(state, window, index)
        implot.end_plot()
        cell.fit_pending = False

    def _interaction_follow(self, state, window, current) -> None:
        io = imgui.get_io()
        interacted = (
            implot.is_plot_hovered()
            and (imgui.is_mouse_dragging(0) or imgui.is_mouse_dragging(1)
                 or abs(io.mouse_wheel) > 0)
        )
        if interacted and window.follow_live:
            self._emit(state, "follow_live", window.token, False)
            window.shared_x = current
        elif not window.follow_live and window.link_x:
            window.shared_x = current

    def _accept_drop(self, state, window, index) -> None:
        if implot.begin_drag_drop_target_plot():
            if imgui.accept_drag_drop_payload_py_id(SIGNAL_DND) is not None:
                sid = getattr(state, "dragged_segment", None)
                if sid is not None:
                    self._emit(
                        state, "add_signal", window.token, f"plot_{index + 1}",
                        f"signal_{sid}",
                    )
            implot.end_drag_drop_target()

    def _legend_popup(self, state, window, index, cell, segment) -> None:
        label = f"{segment.name.removeprefix('JSO_')}##{segment.id}"
        if not implot.begin_legend_popup(label):
            return
        right = segment.id in cell.y2_segments
        if imgui.menu_item("Right axis", "", right)[0]:
            self._emit(
                state, "set_axis", window.token, f"plot_{index + 1}",
                segment.token, "left" if right else "right",
            )
        if imgui.menu_item("Remove from plot", "", False)[0]:
            self._emit(
                state, "remove_signal", window.token, f"plot_{index + 1}",
                segment.token,
            )
        implot.end_legend_popup()

    def _trigger_guides(self, state, cell) -> None:
        engine = state.engine
        if engine is None:
            return
        source = state.segments.active_for_slot(engine.channel)
        if source is None or source.id not in cell.segments:
            return
        scale = source.scale if abs(source.scale) > 1e-12 else 1.0
        level = (engine.level + source.offset) / scale
        spec = implot.Spec()
        spec.flags = implot.InfLinesFlags_.horizontal
        implot.plot_inf_lines(
            "##trigger_level", np.asarray([level], np.float64), spec
        )
        capture = engine.capture
        if capture is not None:
            implot.plot_inf_lines(
                "##trigger_time",
                np.asarray([capture.trigger_index * state.timestep_s], np.float64),
            )

    def _cursors(self, state, window, cell, index) -> None:
        if cell.cursor_x is None:
            limits = implot.get_plot_limits()
            span = limits.x.max - limits.x.min
            cell.cursor_x = (
                limits.x.min + span * 0.25, limits.x.min + span * 0.75
            )
        color = imgui.ImVec4(0.95, 0.85, 0.25, 1.0)
        x1 = implot.drag_line_x(1001, cell.cursor_x[0], color)[1]
        x2 = implot.drag_line_x(1002, cell.cursor_x[1], color)[1]
        cell.cursor_x = (x1, x2)
        dx = abs(x2 - x1)
        self._cursor_text[(window.id, index)] = (
            f"Δx={dx:.5g}s   f={(1.0 / dx if dx else math.inf):.5g}Hz"
        )
        implot.tag_x(x1, color, True)
        implot.tag_x(x2, color, True)

    
    @staticmethod
    def _spy_rect(cell) -> None:
        if cell.spy_rect is None:
            limits = implot.get_plot_limits()
            xspan = limits.x.max - limits.x.min
            yspan = limits.y.max - limits.y.min
            cell.spy_rect = (
                limits.x.min + 0.25 * xspan,
                limits.y.min + 0.25 * yspan,
                limits.x.min + 0.75 * xspan,
                limits.y.min + 0.75 * yspan,
            )
        x1, y1, x2, y2 = cell.spy_rect
        result = implot.drag_rect(
            0, x1, y1, x2, y2, imgui.ImVec4(1.0, 0.2, 1.0, 1.0)
        )
        cell.spy_rect = (result[1], result[2], result[3], result[4])

    def _spy(self, state, window, cell, index, width, height) -> None:
        if cell.spy_rect is None:
            rng = self._ranges.get((window.id, index))
            if rng is None:
                return
            x1, x2 = rng
            cell.spy_rect = (x1 + .25 * (x2 - x1), -1.0,
                             x1 + .75 * (x2 - x1), 1.0)
        x1, y1, x2, y2 = cell.spy_rect
        if implot.begin_plot(
            f"##spy_w{window.id}_p{index}",
            imgui.ImVec2(width, height),
            implot.Flags_.canvas_only,
        ):
            implot.setup_axes_limits(x1, x2, y1, y2, imgui.Cond_.always)
            self._plot_segments(state, window, cell, index, x1, x2, width)
            implot.end_plot()

