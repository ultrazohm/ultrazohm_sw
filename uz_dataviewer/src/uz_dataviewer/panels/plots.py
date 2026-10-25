"""Center plot panel: a runtime-configurable grid of ImPlot subplots.

Signals are dropped in from the navigation tree. Each cell renders as a time
series (line / scatter / stairs) or an XY plot (one signal vs another), and the
time-series X axes can be linked so panning/zooming one subplot moves them all.
Spectra and value distributions live in the dedicated FFT / Histogram windows.
Series are decimated per visible range with a min/max pyramid so multi-gigabyte
logs stay interactive.

Every discrete interaction here is routed through the command registry
(``state.commands``) so it is echoed to the console and is equally reachable from
a typed command or a replayed script. Continuous pan/zoom gestures echo a
``set_x_lim(...)`` once they settle (mouse released), so even zooming is logged.
"""

from __future__ import annotations

from .. import runtime

import math

import numpy as np

from ..sources import shift_time
from imgui_bundle import imgui, implot

from .. import webbridge
from ..session import ensure_extension
from ..state import GRID_PRESETS, AppState, PlotType, SignalRef, SubplotCell, XyStyle
from .base import SessionPanel
from .navigation import SIGNAL_DND_TYPE

try:  # portable_file_dialogs is unavailable in the browser build
    from imgui_bundle import portable_file_dialogs as pfd
except Exception:  # pragma: no cover
    pfd = None

_TIME_SERIES = (PlotType.LINE, PlotType.SCATTER, PlotType.STAIRS)


def _is_finite_range(lo: float, hi: float) -> bool:
    return math.isfinite(lo) and math.isfinite(hi) and hi > lo


def _colored_spec(idx: int, *, marker: bool) -> "implot.Spec":
    """A draw Spec pinning a signal to colormap colour ``idx``.

    ImPlot's auto colours are assigned per ``begin_plot`` in draw order, so the same
    signal would get different colours in the main plot and the spy inset. Pinning the
    colour by the signal's index keeps the two in sync. Must be called inside a plot.
    """
    color = implot.get_colormap_color(idx % implot.get_colormap_size())
    spec = implot.Spec()
    spec.line_color = color
    spec.marker_fill_color = color
    spec.marker_line_color = color
    if marker:
        spec.marker = implot.Marker_.circle
    return spec


def _abbrev(n: int) -> str:
    """Human-readable count, e.g. 4_012_345 -> '4.0M'."""
    if n >= 1_000_000:
        return f"{n / 1_000_000:.1f}M"
    if n >= 1_000:
        return f"{n / 1_000:.1f}k"
    return str(n)


class PlotsPanel(SessionPanel):
    def __init__(self) -> None:
        self._driver: int = -1  # cell index that currently drives linked X axes
        self._last_points: dict[int, int] = {}  # cell index -> samples drawn last frame
        self._last_raw: dict[int, int] = {}  # cell index -> raw samples in view last frame
        self._last_logged_x: dict[int, tuple[float, float]] = {}  # for zoom echo
        self._cursor_text: dict[int, str] = {}  # cell index -> cursor readout
        self._last_logged_cursor: dict[int, tuple[float, float]] = {}  # cursor echo
        self._last_logged_spy: dict[int, tuple] = {}  # spy-rect echo
        self._export_dialog: tuple | None = None  # (pfd dialog, cell)
        self._used_slots = set()
        self._pending_fit: dict[int, set[str]] = {}
        self._reported_errors = {}
        self._validated_sources = {}

    def _budget(self, state, traces):
        width = max(1., implot.get_plot_size().x)
        return max(2, min(state.max_points, int(width * 2), max(128, 32000 // max(1, traces))))

    def _request_data(self, state, slot, key, identity, sources, compute):
        """Validate sources even for cache hits; share scheduling and error handling."""
        from ..sources import ArraySource, validation_error
        self._used_slots.add(slot)
        for source in sources:
            source_id = source.metadata.identity
            if source_id not in self._validated_sources:
                self._validated_sources[source_id] = validation_error([source])
            error = self._validated_sources[source_id]
            if error:
                state.services.display.forget(slot)
                self._report_error(state, slot, error)
                return None
        immediate = all(isinstance(source, ArraySource) and source.metadata.rows <= 4096
                        for source in sources)
        value = state.services.display.request(slot, key, identity, compute, immediate=immediate)
        error = state.services.display.errors.get(slot)
        if error:
            self._report_error(state, slot, error)
            return None
        self._reported_errors.pop(slot, None)
        return value

    def _report_error(self, state, slot, error):
        if self._reported_errors.get(slot) != error:
            state.console.error(error)
            self._reported_errors[slot] = error

    def _display(self, state, slot, run, channel, lo, hi, budget):
        source = run.data_source()
        offset = run.time_offset
        identity = (source.metadata.identity, run.time_version, run.signals[channel].version)
        key = (identity, lo, hi, budget)
        def compute(cancel):
            result = source.read_plot(channel, lo, hi, budget, cancel, offset=offset)
            return shift_time(result.time, offset), result.values, result.raw_count
        return self._request_data(state, slot, key, identity, [source], compute)

    # -- helpers ------------------------------------------------------------
    def _poll_export(self, state: AppState) -> None:
        if self._export_dialog is None:
            return
        dialog, cell = self._export_dialog
        if not dialog.ready():
            return
        path = dialog.result()
        self._export_dialog = None
        if path:
            plot_n = next((i for i, current in enumerate(state.cells, 1) if current is cell), None)
            if plot_n is None:
                state.console.warn('Export cancelled: the subplot was removed.')
                return
            path = ensure_extension(path, ".csv")  # dialog may drop the extension
            relative = state.cells[plot_n - 1].export_relative
            self._emit(state, "export_data", plot_n, path, relative)

    # -- toolbar ------------------------------------------------------------
    def _toolbar(self, state: AppState) -> None:
        current = (state.rows, state.cols)
        preset_labels = [f"{r}x{c}" for r, c in GRID_PRESETS]
        try:
            idx = GRID_PRESETS.index(current)
        except ValueError:
            idx = 0
        imgui.text("Layout")
        imgui.same_line()
        imgui.set_next_item_width(80)
        changed, idx = imgui.combo("##layout", idx, preset_labels)
        if changed:
            r, c = GRID_PRESETS[idx]
            self._emit(state, "set_grid", r, c)

        imgui.same_line()
        changed, link = imgui.checkbox("Link X axes", state.link_x)
        if changed:
            self._emit(state, "link_x", link)

        imgui.same_line()
        imgui.text("Max points")
        imgui.same_line()
        imgui.set_next_item_width(90)
        changed, value = imgui.input_int("##maxpoints", state.max_points, 100, 1000)
        if changed:
            self._emit(state, "set_max_points", max(100, value))

        imgui.same_line()
        imgui.set_next_item_width(80)
        if imgui.begin_combo("##maxpoints_presets", "presets"):
            for preset in (2000, 5000, 10000, 20000):
                if imgui.selectable(f"{preset:,}", state.max_points == preset)[0]:
                    self._emit(state, "set_max_points", preset)
            imgui.end_combo()

        imgui.same_line()
        if state.downsampling_active:
            imgui.text_colored((0.95, 0.75, 0.25, 1.0), "downsampling: active")
        else:
            imgui.text_colored((0.45, 0.85, 0.50, 1.0), "downsampling: off (all samples)")
        if imgui.is_item_hovered():
            imgui.set_tooltip(
                "Min/max envelope at ~Max points per signal.\n"
                "Turns off (raw samples) once the visible window holds\n"
                "fewer raw samples than Max points."
            )

        imgui.same_line()
        imgui.text_disabled(f"({len(state.registry)} run(s) loaded)")

    # -- per-cell header ----------------------------------------------------
    def _cell_header(self, state: AppState, index: int, cell: SubplotCell) -> None:
        plot_n = index + 1
        imgui.set_next_item_width(95)
        type_labels = PlotType.labels()
        type_idx = type_labels.index(cell.plot_type.value)
        changed, type_idx = imgui.combo("##type", type_idx, type_labels)
        if changed:
            self._emit(state, "set_plot_type", plot_n, list(PlotType)[type_idx].value)

        imgui.same_line()
        if imgui.small_button("Reset view") and cell.signals:
            self._emit(state, "reset_view", plot_n)
        imgui.same_line()
        if imgui.small_button("Clear"):
            self._emit(state, "clear_plot", plot_n)

        # Line-plot toggles sit right next to Clear.
        if cell.plot_type in _TIME_SERIES:
            imgui.same_line()
            changed, samples = imgui.checkbox("samples", cell.show_samples)
            if changed:
                self._emit(state, "show_samples", plot_n, samples)
            imgui.same_line()
            changed, spy = imgui.checkbox("spy", cell.spy)
            if imgui.is_item_hovered():
                imgui.set_tooltip("Zoom primary (left) Y-axis signals; right-axis signals are excluded.")
            if changed:
                self._emit(state, "spy", plot_n, spy)
            imgui.same_line()
            changed, cursors = imgui.checkbox("cursors", cell.cursors)
            if changed:
                self._emit(state, "cursors", plot_n, cursors)

        imgui.same_line()
        if imgui.small_button("Export") and cell.signals:
            name = f"plot_{plot_n}.csv"
            if pfd is not None and self._export_dialog is None:
                self._export_dialog = (
                    pfd.save_file("Export plot data", name, ["CSV (*.csv)", "*.csv"]),
                    cell,
                )
            elif runtime.IS_WEB:  # no OS dialog in a tab -> write to FS + download
                webbridge.save_and_download(
                    state, name,
                    lambda path: self._emit(state, "export_data", plot_n, path, cell.export_relative),
                )
        imgui.same_line()
        changed, rel = imgui.checkbox("start at 0", cell.export_relative)
        if changed:
            self._emit(state, "set_export_relative", plot_n, rel)

        imgui.same_line()
        shown = self._last_points.get(index)
        raw = self._last_raw.get(index)
        if shown:
            suffix = f", ~{shown:,} pts shown"
            if raw:
                suffix += f" ({_abbrev(raw)} in view)"
        else:
            suffix = ""
        imgui.text_disabled(f"{len(cell.signals)} signal(s){suffix}")

        # Second row: cursor readout / XY source.
        if cell.plot_type in _TIME_SERIES:
            if cell.cursors and self._cursor_text.get(index):
                imgui.text_colored((0.95, 0.85, 0.25, 1.0), self._cursor_text[index])
        elif cell.plot_type is PlotType.XY:
            self._xy_source_combo(state, index, cell)
            imgui.same_line()
            self._xy_style_combo(state, index, cell)

    def _xy_style_combo(self, state: AppState, index: int, cell: SubplotCell) -> None:
        labels = XyStyle.labels()
        cur_idx = labels.index(cell.xy_style.value)
        imgui.text("style:")
        imgui.same_line()
        imgui.set_next_item_width(95)
        changed, cur_idx = imgui.combo("##xystyle", cur_idx, labels)
        if changed:
            self._emit(state, "set_xy_style", index + 1, list(XyStyle)[cur_idx].value)

    def _xy_source_combo(self, state: AppState, index: int, cell: SubplotCell) -> None:
        refs: list[SignalRef] = []
        labels: list[str] = []
        for run in state.registry.runs:
            for name in run.signals:
                refs.append((run.id, name))
                labels.append(state.signal_label((run.id, name)))
        if not labels:
            imgui.text_disabled("(load data for X source)")
            return
        cur = cell.xy_source
        cur_idx = refs.index(cur) if cur in refs else 0
        imgui.text("X:")
        imgui.same_line()
        imgui.set_next_item_width(180)
        changed, cur_idx = imgui.combo("##xysrc", cur_idx, labels)
        if changed or cell.xy_source is None:
            ref = refs[cur_idx]
            self._emit(state, "set_xy", index + 1, ref[0], ref[1])

    # -- a single cell ------------------------------------------------------
    def _render_cell(self, state: AppState, index: int, cell: SubplotCell, size: imgui.ImVec2) -> None:
        imgui.push_id(index)
        y0 = imgui.get_cursor_screen_pos().y
        self._cell_header(state, index, cell)
        header_h = imgui.get_cursor_screen_pos().y - y0

        plot_h = max(size.y - header_h - 4.0, 60.0)

        if cell.plot_type in _TIME_SERIES:
            self._render_time_series(state, index, cell, size.x, plot_h)
        elif cell.plot_type is PlotType.XY:
            self._render_xy(state, index, cell, size.x, plot_h)

        imgui.pop_id()

    # -- time-series (line / scatter / stairs) ------------------------------
    def _render_time_series(
        self, state: AppState, index: int, cell: SubplotCell, width: float, plot_h: float
    ) -> None:
        inset_h = plot_h * 0.38 if cell.spy else 0.0
        main_h = plot_h - inset_h - (4.0 if cell.spy else 0.0)
        plot_size = imgui.ImVec2(width, main_h)

        data_min, data_max = self._cell_x_extent(state, cell)

        if implot.begin_plot(f"##plot{index}", plot_size):
            implot.setup_axes("time (s)" if state.plot_domain(cell) == "time" else "frequency (Hz)", "")
            if cell.y2_signals:
                implot.setup_axis(implot.ImAxis_.y2, "", implot.AxisFlags_.aux_default)

            did_fit = self._apply_pending_limits(state, cell, data_min, data_max)
            if state.link_x and state.is_time_plot(cell) and state.shared_x is not None and index != self._driver:
                implot.setup_axis_limits(
                    implot.ImAxis_.x1, state.shared_x[0], state.shared_x[1], implot.Cond_.always
                )

            limits = implot.get_plot_limits()
            raw_lo, raw_hi = float(limits.x.min), float(limits.x.max)
            self._capture_limits(cell, limits)
            if cell.y2_signals:
                right = implot.get_plot_limits(implot.ImAxis_.x1, implot.ImAxis_.y2).y
                if _is_finite_range(float(right.min), float(right.max)):
                    cell.y2_lim = (float(right.min), float(right.max))
            x_min, x_max = self._clamp_window(raw_lo, raw_hi, data_min, data_max)
            if did_fit:
                x_min, x_max = data_min, data_max
            # Publish this subplot's live X range so the FFT can explicitly follow it.
            if _is_finite_range(raw_lo, raw_hi):
                state.plot_x_ranges[index + 1] = (raw_lo, raw_hi)

            points_shown, raw_in_view = self._plot_signals(state, index, cell, x_min, x_max)
            self._last_points[index] = points_shown
            self._last_raw[index] = raw_in_view

            if cell.cursors:
                self._draw_cursors(state, index, cell)

            self._accept_drop(state, index, cell)

            if implot.is_plot_hovered():
                lo, hi = float(limits.x.min), float(limits.x.max)
                if _is_finite_range(lo, hi):
                    self._driver = index
                    if state.link_x and state.is_time_plot(cell):
                        state.shared_x = (lo, hi)
                    self._maybe_echo_zoom(state, index, lo, hi, suppress=did_fit)

            if cell.spy:
                self._spy_rect(state, index, cell)

            implot.end_plot()

        if cell.spy and cell.spy_rect is not None:
            self._render_spy_inset(state, index, cell, width, inset_h)

    def _plot_signals(
        self, state: AppState, index: int, cell: SubplotCell, x_min: float, x_max: float
    ) -> tuple[int, int]:
        # Pixel width and total trace count also bound the finite-point budget.
        points_shown = 0
        raw_in_view = 0

        for i, ref in enumerate(list(cell.signals)):
            signal = state.registry.get_signal(ref[0], ref[1])
            run = state.registry.get(ref[0])
            if signal is None or run is None or not run.active:
                continue
            implot.set_axis(implot.ImAxis_.y2 if ref in cell.y2_signals else implot.ImAxis_.y1)
            label = state.signal_label(ref)
            result = self._display(state, ("plot", index, ref), run, ref[1], x_min, x_max,
                                   self._budget(state, len(cell.signals)))
            if result is None:
                implot.plot_dummy(label)
                continue
            xs, ys, raw = result
            points_shown += len(xs)
            raw_in_view = max(raw_in_view, raw)
            if len(xs) < raw:
                state.downsampling_active = True

            # Scatter is markers-only, so it always needs one; line/stairs show markers
            # only when "samples" is on. (A Spec defaults marker to none, which would
            # otherwise make a scatter plot draw nothing.)
            want_marker = cell.show_samples or cell.plot_type is PlotType.SCATTER
            spec = _colored_spec(i, marker=want_marker)
            if cell.plot_type is PlotType.LINE:
                implot.plot_line(label, xs, ys, spec)
            elif cell.plot_type is PlotType.SCATTER:
                implot.plot_scatter(label, xs, ys, spec)
            else:
                implot.plot_stairs(label, xs, ys, spec)

            self._legend_popup(state, cell, ref, label)
        return points_shown, raw_in_view

    # -- XY (signal vs signal) ----------------------------------------------
    def _render_xy(
        self, state: AppState, index: int, cell: SubplotCell, width: float, plot_h: float
    ) -> None:
        x_run = state.registry.get(cell.xy_source[0]) if cell.xy_source else None
        x_sig = (
            state.registry.get_signal(cell.xy_source[0], cell.xy_source[1])
            if cell.xy_source
            else None
        )
        x_label = state.signal_label(cell.xy_source) if cell.xy_source else "X"

        if cell.fit_pending:
            self._pending_fit[id(cell)] = {'x', 'y'}
        if id(cell) in self._pending_fit:
            implot.set_next_axes_to_fit()  # must precede begin_plot
            cell.fit_pending = False
        if implot.begin_plot(f"##plot{index}", imgui.ImVec2(width, plot_h)):
            implot.setup_axes(x_label, "")
            self._apply_explicit_limits(cell, consume=False)
            all_ready = False
            if x_sig is not None:
                stride = max(1, -(-x_sig.y.shape[0] // self._budget(state, len(cell.signals))))
                want_marker = cell.xy_style in (XyStyle.MARKERS, XyStyle.BOTH)
                all_ready = True
                for i, ref in enumerate(list(cell.signals)):
                    sig = state.registry.get_signal(ref[0], ref[1])
                    run = state.registry.get(ref[0])
                    if sig is None or run is None or not run.active:
                        continue
                    left, right = x_run.data_source(), run.data_source()
                    identity = (left.metadata.identity, right.metadata.identity, cell.xy_source[1], ref[1],
                                x_run.time_offset, run.time_offset, x_run.time_version, run.time_version)
                    slot = ("xy", index, ref)
                    def compute(cancel, left=left, right=right, xn=cell.xy_source[1], yn=ref[1],
                                stride=stride, xo=x_run.time_offset, yo=run.time_offset):
                        from ..sampling import sample_xy
                        return sample_xy(left, right, xn, yn, xo, yo, stride, cancel)
                    value = self._request_data(state, slot, (identity, stride), identity, [left, right], compute)
                    if not state.services.display.ready(slot, (identity, stride)):
                        all_ready = False
                    if value is None:
                        continue
                    xs, ys = value
                    n = len(xs)
                    label = state.signal_label(ref)
                    spec = _colored_spec(i, marker=want_marker)
                    if cell.xy_style is XyStyle.MARKERS:
                        implot.plot_scatter(label, xs[:n], ys, spec)
                    else:  # LINE (no markers) or BOTH (line + markers)
                        implot.plot_line(label, xs[:n], ys, spec)
                    self._legend_popup(state, cell, ref, label)
                if all_ready:
                    self._pending_fit.pop(id(cell), None)
            else:
                implot.plot_dummy("(pick an X source)")
            self._capture_limits(cell, implot.get_plot_limits())
            if all_ready:
                cell.pending_x_lim = cell.pending_y_lim = None
            self._accept_drop(state, index, cell)
            implot.end_plot()
        self._last_points[index] = 0
        self._last_raw[index] = 0

    # -- cursors ------------------------------------------------------------
    @staticmethod
    def _value_at(time: np.ndarray, y: np.ndarray, x: float) -> float:
        """Linear interpolation of ``y`` at ``x`` in O(log n).

        ``np.interp`` would up-cast the whole (float32) array to float64 on every
        call -- ruinous per frame on large logs -- so we bisect and touch only the
        two bracketing samples instead.
        """
        i = int(np.searchsorted(time, x))
        if i <= 0:
            return float(y[0])
        if i >= time.shape[0]:
            return float(y[-1])
        t0, t1 = float(time[i - 1]), float(time[i])
        if t1 <= t0:
            return float(y[i - 1])
        frac = (x - t0) / (t1 - t0)
        return float(y[i - 1] + frac * (float(y[i]) - float(y[i - 1])))

    def _draw_cursors(self, state: AppState, index: int, cell: SubplotCell) -> None:
        if cell.cursor_x is None:
            # Centre the cursors: 50% of the visible width, symmetric (25% / 75%).
            lim = implot.get_plot_limits()
            xspan = lim.x.max - lim.x.min
            cell.cursor_x = (lim.x.min + 0.25 * xspan, lim.x.min + 0.75 * xspan)
        col = imgui.ImVec4(0.95, 0.85, 0.25, 1.0)
        x1 = implot.drag_line_x(1001, cell.cursor_x[0], col)[1]
        x2 = implot.drag_line_x(1002, cell.cursor_x[1], col)[1]
        cell.cursor_x = (x1, x2)
        implot.tag_x(x1, col, True)
        implot.tag_x(x2, col, True)

        # The Δx / Δy readout only changes when a cursor moves, so cache it
        # instead of recomputing (and interpolating) every frame.
        sources = [(ref[1], state.registry.get(ref[0])) for ref in cell.signals[:3]]
        sources = [(name, run.data_source(), run.time_offset, run.time_version) for name, run in sources if run is not None]
        identity = tuple((name, src.metadata.identity, off, version) for name, src, off, version in sources)
        slot = ("cursor", index)
        domain = state.plot_domain(cell)
        def compute(cancel):
            dx = abs(x2 - x1)
            parts = ([f"Δx={dx:.4g}s", f"f={1 / dx if dx else float('inf'):.4g}Hz"]
                     if domain == "time" else [f"Δf={dx:.4g}Hz"])
            for name, src, off, _ in sources:
                vals = []
                for x in (x1, x2):
                    from ..sources import displayed_bounds
                    a, b = displayed_bounds(src, x, x, off, cancel, padding=True)
                    t, ys = src.read_rows([name], a, b, cancel)
                    vals.append(self._value_at(shift_time(t, off), ys[name], x))
                parts.append(f"{name}: Δy={vals[1] - vals[0]:.4g}")
            return "   ".join(parts)
        value = self._request_data(state, slot, (identity, x1, x2), identity,
                                   [src for _, src, _, _ in sources], compute)
        if value is not None:
            self._cursor_text[index] = value
        else:
            self._cursor_text.pop(index, None)
        self._maybe_echo_cursors(state, index, x1, x2)

    def _maybe_echo_cursors(self, state: AppState, index: int, x1: float, x2: float) -> None:
        if imgui.is_mouse_down(0):
            return
        span = abs(x2 - x1) or 1.0
        last = self._last_logged_cursor.get(index)
        if last is not None and abs(last[0] - x1) < 0.005 * span and abs(last[1] - x2) < 0.005 * span:
            return
        first = last is None
        self._last_logged_cursor[index] = (x1, x2)
        if not first:  # don't echo the initial placement
            state.commands.echo(state, "set_cursors", [index + 1, x1, x2])

    # -- spy / drag-rect ----------------------------------------------------
    def _spy_rect(self, state: AppState, index: int, cell: SubplotCell) -> None:
        # Spy coordinates always belong to the primary Y axis, independently
        # of the last trace drawn. The inset shows primary-axis traces only.
        implot.set_axis(implot.ImAxis_.y1)
        if cell.spy_rect is None:
            # Centre the rect: 50% of the visible width and height (25%..75%).
            lim = implot.get_plot_limits()
            xspan = lim.x.max - lim.x.min
            yspan = lim.y.max - lim.y.min
            cell.spy_rect = (
                lim.x.min + 0.25 * xspan,
                lim.y.min + 0.25 * yspan,
                lim.x.min + 0.75 * xspan,
                lim.y.min + 0.75 * yspan,
            )
        x1, y1, x2, y2 = cell.spy_rect
        result = implot.drag_rect(0, x1, y1, x2, y2, imgui.ImVec4(1.0, 0.2, 1.0, 1.0))
        # drag_rect -> (changed, x1, y1, x2, y2, clicked, hovered, held)
        cell.spy_rect = (result[1], result[2], result[3], result[4])
        self._maybe_echo_spy(state, index, cell.spy_rect)

    def _maybe_echo_spy(self, state: AppState, index: int, rect: tuple) -> None:
        if imgui.is_mouse_down(0):
            return
        x1, y1, x2, y2 = rect
        sx = abs(x2 - x1) or 1.0
        sy = abs(y2 - y1) or 1.0
        last = self._last_logged_spy.get(index)
        if last is not None and all(
            abs(a - b) < 0.005 * s for a, b, s in zip(last, rect, (sx, sy, sx, sy))
        ):
            return
        first = last is None
        self._last_logged_spy[index] = rect
        if not first:
            state.commands.echo(state, "set_spy_rect", [index + 1, x1, y1, x2, y2])

    def _render_spy_inset(
        self, state: AppState, index: int, cell: SubplotCell, width: float, height: float
    ) -> None:
        x1, y1, x2, y2 = cell.spy_rect
        if implot.begin_plot(f"##spy{index}", imgui.ImVec2(width, max(height, 50.0)), implot.Flags_.canvas_only):
            implot.setup_axes_limits(x1, x2, y1, y2, imgui.Cond_.always)
            for i, ref in enumerate(list(cell.signals)):
                if ref in cell.y2_signals:
                    continue
                signal = state.registry.get_signal(ref[0], ref[1])
                run = state.registry.get(ref[0])
                if signal is None or run is None or not run.active:
                    continue
                result = self._display(state, ("spy", index, ref), run, ref[1], x1, x2,
                                       self._budget(state, len(cell.signals)))
                if result is None:
                    continue
                xs, ys, _ = result
                # Same colour index as the main plot so the inset matches.
                implot.plot_line(state.signal_label(ref), xs, ys, _colored_spec(i, marker=False))
            implot.end_plot()

    # -- shared bits --------------------------------------------------------
    @staticmethod
    def _capture_limits(cell, limits):
        for field, axis in (('x_lim', limits.x), ('y_lim', limits.y)):
            lo, hi = float(axis.min), float(axis.max)
            if _is_finite_range(lo, hi):
                setattr(cell, field, (lo, hi))

    @staticmethod
    def _apply_explicit_limits(cell, *, consume=True):
        axes = [('pending_x_lim', implot.ImAxis_.x1), ('pending_y_lim', implot.ImAxis_.y1)]
        if cell.y2_signals and cell.plot_type in _TIME_SERIES:
            axes.append(('pending_y2_lim', implot.ImAxis_.y2))
        for field, axis in axes:
            limits = getattr(cell, field)
            if limits is not None:
                implot.setup_axis_limits(axis, *limits, implot.Cond_.always)
                if consume:
                    setattr(cell, field, None)

    def _apply_pending_limits(self, state: AppState, cell: SubplotCell, data_min, data_max) -> bool:
        """Apply one-shot fit / set_x_lim / set_y_lim requests. Returns did_fit."""
        did_fit = False
        if cell.fit_pending:
            self._pending_fit[id(cell)] = {'y', 'y2'}
            if cell.pending_x_lim is None and data_min is not None:
                implot.setup_axis_limits(implot.ImAxis_.x1, data_min, data_max, implot.Cond_.always)
                did_fit = True
        elif cell.pending_x_lim is not None:
            self._pending_fit.pop(id(cell), None)
        fitting = self._pending_fit.get(id(cell), set())
        # Explicit limits finish fitting only their own axis. The other axis
        # can continue waiting for lazy samples without overwriting this view.
        for axis in ('y', 'y2'):
            if getattr(cell, f'pending_{axis}_lim') is not None:
                fitting.discard(axis)
        if imgui.is_mouse_down(0) or imgui.get_io().mouse_wheel:
            fitting.clear()
        for axis, im_axis, refs in (
            ('y', implot.ImAxis_.y1, [r for r in cell.signals if r not in cell.y2_signals]),
            ('y2', implot.ImAxis_.y2, cell.y2_signals),
        ):
            if axis not in fitting:
                continue
            if not refs:
                fitting.discard(axis)
                continue
            lo, hi = self._cell_y_extent(state, cell, refs)
            if lo is not None:
                implot.setup_axis_limits(im_axis, lo, hi, implot.Cond_.always)
                fitting.discard(axis)
        if not fitting:
            self._pending_fit.pop(id(cell), None)
        self._apply_explicit_limits(cell)
        cell.fit_pending = False
        return did_fit

    def _clamp_window(self, x_min, x_max, data_min, data_max):
        if data_min is None:
            return x_min, x_max
        if not _is_finite_range(x_min, x_max):
            return data_min, data_max
        x_min = max(x_min, data_min)
        x_max = min(x_max, data_max)
        if x_max <= x_min:
            return data_min, data_max
        return x_min, x_max

    def _maybe_echo_zoom(self, state: AppState, index: int, lo: float, hi: float, *, suppress: bool) -> None:
        """Echo `set_x_lim(...)` once a pan/zoom gesture settles (mouse up)."""
        if suppress or imgui.is_mouse_down(0):
            return
        last = self._last_logged_x.get(index)
        span = hi - lo
        if last is not None:
            if abs(last[0] - lo) < 0.005 * span and abs(last[1] - hi) < 0.005 * span:
                return
        else:
            # Establish a baseline silently on first display.
            self._last_logged_x[index] = (lo, hi)
            return
        self._last_logged_x[index] = (lo, hi)
        state.commands.echo(state, "set_x_lim", [index + 1, lo, hi])

    def _accept_drop(self, state: AppState, index: int, cell: SubplotCell) -> None:
        if implot.begin_drag_drop_target_plot():
            payload = imgui.accept_drag_drop_payload_py_id(SIGNAL_DND_TYPE)
            if payload is not None:
                ref = getattr(state, "dragged_ref", None)
                if ref is not None and ref not in cell.signals:
                    self._emit(state, "add_signal", index + 1, ref[0], ref[1])
            implot.end_drag_drop_target()

    def _legend_popup(self, state: AppState, cell: SubplotCell, ref: SignalRef, label: str) -> None:
        if implot.begin_legend_popup(label):
            imgui.text_disabled(label)
            plot_n = cell_index_of(state, cell) + 1
            if cell.plot_type in _TIME_SERIES:
                on_right = ref in cell.y2_signals
                if imgui.menu_item("Right axis", "", on_right)[0]:
                    self._emit(state, "set_axis", plot_n, ref[0], ref[1],
                               "left" if on_right else "right")
            if imgui.menu_item("Remove from plot", "", False)[0]:
                self._emit(state, "remove_signal", plot_n, ref[0], ref[1])
            implot.end_legend_popup()

    def _cell_x_extent(self, state: AppState, cell: SubplotCell) -> tuple[float | None, float | None]:
        lo: float | None = None
        hi: float | None = None
        for ref in cell.signals:
            run = state.registry.get(ref[0])
            if run is None or not run.active or run.n_rows == 0:
                continue
            t0, t1 = float(run.time[0]), float(run.time[-1])
            lo = t0 if lo is None else min(lo, t0)
            hi = t1 if hi is None else max(hi, t1)
        if lo is None or hi is None or hi <= lo:
            return None, None
        return lo, hi

    def _cell_y_extent(
        self, state: AppState, cell: SubplotCell, refs: list[SignalRef] | None = None
    ) -> tuple[float | None, float | None]:
        lo: float | None = None
        hi: float | None = None
        for ref in (cell.signals if refs is None else refs):
            run = state.registry.get(ref[0])
            signal = state.registry.get_signal(ref[0], ref[1])
            if run is None or signal is None or not run.active or signal.y.size == 0:
                continue
            result = self._display(state, ("fit", id(cell), ref), run, ref[1],
                                   float(run.time[0]), float(run.time[-1]), 512)
            if result is None:
                return None, None
            finite = result[1][np.isfinite(result[1])]
            if not len(finite):
                continue
            y_lo, y_hi = float(finite.min()), float(finite.max())
            lo = y_lo if lo is None else min(lo, y_lo)
            hi = y_hi if hi is None else max(hi, y_hi)
        if lo is None or hi is None:
            return None, None
        from ..validation import expanded_range
        return expanded_range(lo, hi)

    # -- panel --------------------------------------------------------------
    def render(self, state: AppState) -> None:
        self._sync_session(state)
        live_cells = {id(cell) for cell in state.cells}
        self._pending_fit = {key: axes for key, axes in self._pending_fit.items() if key in live_cells}
        if self._driver >= state.cell_count:
            self._driver = -1
        for cache in (self._last_logged_x, self._last_logged_cursor, self._last_logged_spy,
                      self._cursor_text, self._last_points, self._last_raw):
            for index in list(cache):
                if index >= state.cell_count:
                    del cache[index]
        self._used_slots.clear()
        self._validated_sources.clear()
        self._poll_export(state)
        self._toolbar(state)
        if state.services.display.pending:
            imgui.same_line()
            imgui.text_disabled("Updating plots...")
        imgui.separator()
        state.downsampling_active = False

        region = imgui.get_content_region_avail()
        spacing = 4.0
        cell_w = (region.x - spacing * (state.cols - 1)) / state.cols
        cell_h = (region.y - spacing * (state.rows - 1)) / state.rows

        for r in range(state.rows):
            for c in range(state.cols):
                index = r * state.cols + c
                if index >= len(state.cells):
                    continue
                imgui.begin_group()
                self._render_cell(state, index, state.cells[index], imgui.ImVec2(cell_w, cell_h))
                imgui.end_group()
                if c < state.cols - 1:
                    imgui.same_line(0.0, spacing)

        state.services.display.retain(self._used_slots)


def cell_index_of(state: AppState, cell: SubplotCell) -> int:
    for i, c in enumerate(state.cells):
        if c is cell:
            return i
    return 0
