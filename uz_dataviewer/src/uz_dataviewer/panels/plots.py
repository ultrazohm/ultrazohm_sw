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

import math

import numpy as np
from imgui_bundle import imgui, implot

from .. import webbridge
from ..downsample import PYRAMID_MIN_POINTS, Pyramid, decimate_range, visible_slice
from ..state import GRID_PRESETS, AppState, PlotType, SignalRef, SubplotCell, XyStyle
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


class PlotsPanel:
    def __init__(self) -> None:
        self._driver: int = -1  # cell index that currently drives linked X axes
        self._last_points: dict[int, int] = {}  # cell index -> samples drawn last frame
        self._last_raw: dict[int, int] = {}  # cell index -> raw samples in view last frame
        self._last_logged_x: dict[int, tuple[float, float]] = {}  # for zoom echo
        self._cursor_text: dict[int, str] = {}  # cell index -> cursor readout
        self._last_logged_cursor: dict[int, tuple[float, float]] = {}  # cursor echo
        self._last_logged_spy: dict[int, tuple] = {}  # spy-rect echo
        self._export_dialog: tuple | None = None  # (pfd dialog, plot_n)

    # -- helpers ------------------------------------------------------------
    def _emit(self, state: AppState, name: str, *args) -> None:
        """Run a command for a GUI action, logging any error to the console."""
        try:
            state.commands.execute(state, name, list(args))
        except Exception as exc:  # noqa: BLE001 - surfaced to the console
            state.console.error(str(exc))

    def _poll_export(self, state: AppState) -> None:
        if self._export_dialog is None:
            return
        dialog, plot_n = self._export_dialog
        if not dialog.ready():
            return
        path = dialog.result()
        self._export_dialog = None
        if path:
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
                    plot_n,
                )
            elif webbridge.IS_WEB:  # no OS dialog in a tab -> write to FS + download
                path = "/tmp/" + name
                self._emit(state, "export_data", plot_n, path, cell.export_relative)
                webbridge.download(path, name)
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
            implot.setup_axes("time", "")
            if cell.y2_signals:
                implot.setup_axis(implot.ImAxis_.y2, "", implot.AxisFlags_.aux_default)

            did_fit = self._apply_pending_limits(state, cell, data_min, data_max)
            if did_fit and cell.y2_signals:
                y2_lo, y2_hi = self._cell_y_extent(state, cell, cell.y2_signals)
                if y2_lo is not None:
                    implot.setup_axis_limits(implot.ImAxis_.y2, y2_lo, y2_hi, implot.Cond_.always)

            if state.link_x and state.shared_x is not None and index != self._driver:
                implot.setup_axis_limits(
                    implot.ImAxis_.x1, state.shared_x[0], state.shared_x[1], implot.Cond_.always
                )

            limits = implot.get_plot_limits()
            raw_lo, raw_hi = float(limits.x.min), float(limits.x.max)
            x_min, x_max = self._clamp_window(raw_lo, raw_hi, data_min, data_max)
            if did_fit:
                x_min, x_max = data_min, data_max
            # Publish this subplot's live X range so the FFT can explicitly follow it.
            if _is_finite_range(raw_lo, raw_hi):
                state.plot_x_ranges[index + 1] = (raw_lo, raw_hi)

            points_shown, raw_in_view = self._plot_signals(state, cell, x_min, x_max)
            self._last_points[index] = points_shown
            self._last_raw[index] = raw_in_view

            if cell.cursors:
                self._draw_cursors(state, index, cell)

            self._accept_drop(state, index, cell)

            if implot.is_plot_hovered():
                lo, hi = float(limits.x.min), float(limits.x.max)
                if _is_finite_range(lo, hi):
                    self._driver = index
                    state.shared_x = (lo, hi)
                    self._maybe_echo_zoom(state, index, lo, hi, suppress=did_fit)

            if cell.spy:
                self._spy_rect(state, index, cell)

            implot.end_plot()

        if cell.spy and cell.spy_rect is not None:
            self._render_spy_inset(state, index, cell, width, inset_h)

    def _plot_signals(
        self, state: AppState, cell: SubplotCell, x_min: float, x_max: float
    ) -> tuple[int, int]:
        n_out = max(state.max_points, 2)
        points_shown = 0
        raw_in_view = 0

        for i, ref in enumerate(list(cell.signals)):
            signal = state.registry.get_signal(ref[0], ref[1])
            run = state.registry.get(ref[0])
            if signal is None or run is None or not run.active:
                continue
            implot.set_axis(implot.ImAxis_.y2 if ref in cell.y2_signals else implot.ImAxis_.y1)
            label = state.signal_label(ref)
            # Build the per-signal min/max pyramid once (large signals only), then
            # decimate the visible window in O(output) so multi-GB logs pan smoothly.
            if signal.pyramid is None and signal.y.size > PYRAMID_MIN_POINTS:
                signal.pyramid = Pyramid.build(signal.y)
            start, stop = visible_slice(run.time, x_min, x_max)
            xs, ys = decimate_range(run.time, signal.y, signal.pyramid, n_out, start, stop)
            points_shown += xs.shape[0]
            # Raw samples in the window (densest signal), not a sum across signals.
            raw_in_view = max(raw_in_view, stop - start)
            if xs.shape[0] < (stop - start):
                state.downsampling_active = True

            # PlotLine is templated on one type T for both arrays: a dtype
            # mismatch reinterprets a buffer as the wrong type. Keep them equal.
            xs = np.ascontiguousarray(xs, dtype=np.float64)
            ys = np.ascontiguousarray(ys, dtype=np.float64)

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
            implot.set_next_axes_to_fit()  # must precede begin_plot
            cell.fit_pending = False
        if implot.begin_plot(f"##plot{index}", imgui.ImVec2(width, plot_h)):
            implot.setup_axes(x_label, "")
            if x_sig is not None:
                stride = self._xy_stride(state, x_sig.y.shape[0])
                xs = np.ascontiguousarray(x_sig.y[::stride], dtype=np.float64)
                want_marker = cell.xy_style in (XyStyle.MARKERS, XyStyle.BOTH)
                for i, ref in enumerate(list(cell.signals)):
                    sig = state.registry.get_signal(ref[0], ref[1])
                    run = state.registry.get(ref[0])
                    if sig is None or run is None or not run.active:
                        continue
                    n = min(xs.shape[0], sig.y[::stride].shape[0])
                    ys = np.ascontiguousarray(sig.y[::stride][:n], dtype=np.float64)
                    label = state.signal_label(ref)
                    spec = _colored_spec(i, marker=want_marker)
                    if cell.xy_style is XyStyle.MARKERS:
                        implot.plot_scatter(label, xs[:n], ys, spec)
                    else:  # LINE (no markers) or BOTH (line + markers)
                        implot.plot_line(label, xs[:n], ys, spec)
                    self._legend_popup(state, cell, ref, label)
            else:
                implot.plot_dummy("(pick an X source)")
            self._accept_drop(state, index, cell)
            implot.end_plot()
        self._last_points[index] = 0
        self._last_raw[index] = 0

    def _xy_stride(self, state: AppState, n: int) -> int:
        budget = max(state.max_points, 2)
        return max(1, n // budget)

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

    def _cursor_readout(self, state: AppState, cell: SubplotCell, x1: float, x2: float) -> str:
        dx = abs(x2 - x1)
        freq = (1.0 / dx) if dx > 0 else float("inf")
        parts = [f"Δx={dx:.4g}s", f"f={freq:.4g}Hz"]
        for ref in cell.signals[:3]:
            run = state.registry.get(ref[0])
            signal = state.registry.get_signal(ref[0], ref[1])
            if run is None or signal is None:
                continue
            y1 = self._value_at(run.time, signal.y, x1)
            y2 = self._value_at(run.time, signal.y, x2)
            parts.append(f"{ref[1]}: Δy={y2 - y1:.4g}")
        return "   ".join(parts)

    def _draw_cursors(self, state: AppState, index: int, cell: SubplotCell) -> None:
        if cell.cursor_x is None:
            # Centre the cursors: 50% of the visible width, symmetric (25% / 75%).
            lim = implot.get_plot_limits()
            xspan = lim.x.max - lim.x.min
            cell.cursor_x = (lim.x.min + 0.25 * xspan, lim.x.min + 0.75 * xspan)
        col = imgui.ImVec4(0.95, 0.85, 0.25, 1.0)
        x1 = implot.drag_line_x(1001, cell.cursor_x[0], col)[1]
        x2 = implot.drag_line_x(1002, cell.cursor_x[1], col)[1]
        moved = (x1, x2) != cell.cursor_x
        cell.cursor_x = (x1, x2)
        implot.tag_x(x1, col, True)
        implot.tag_x(x2, col, True)

        # The Δx / Δy readout only changes when a cursor moves, so cache it
        # instead of recomputing (and interpolating) every frame.
        if moved or index not in self._cursor_text:
            self._cursor_text[index] = self._cursor_readout(state, cell, x1, x2)
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
            n_out = max(state.max_points, 2)
            for i, ref in enumerate(list(cell.signals)):
                signal = state.registry.get_signal(ref[0], ref[1])
                run = state.registry.get(ref[0])
                if signal is None or run is None or not run.active:
                    continue
                if signal.pyramid is None and signal.y.size > PYRAMID_MIN_POINTS:
                    signal.pyramid = Pyramid.build(signal.y)
                start, stop = visible_slice(run.time, x1, x2)
                xs, ys = decimate_range(run.time, signal.y, signal.pyramid, n_out, start, stop)
                xs = np.ascontiguousarray(xs, dtype=np.float64)
                ys = np.ascontiguousarray(ys, dtype=np.float64)
                # Same colour index as the main plot so the inset matches.
                implot.plot_line(state.signal_label(ref), xs, ys, _colored_spec(i, marker=False))
            implot.end_plot()

    # -- shared bits --------------------------------------------------------
    def _apply_pending_limits(self, state: AppState, cell: SubplotCell, data_min, data_max) -> bool:
        """Apply one-shot fit / set_x_lim / set_y_lim requests. Returns did_fit."""
        did_fit = False
        if cell.pending_x_lim is not None:
            lo, hi = cell.pending_x_lim
            implot.setup_axis_limits(implot.ImAxis_.x1, lo, hi, implot.Cond_.always)
            cell.pending_x_lim = None
            did_fit = True
        elif cell.fit_pending and data_min is not None:
            implot.setup_axis_limits(implot.ImAxis_.x1, data_min, data_max, implot.Cond_.always)
            # Fit Y1 to the primary-axis signals only (the right axis is fit separately).
            primary = [r for r in cell.signals if r not in cell.y2_signals]
            y_lo, y_hi = self._cell_y_extent(state, cell, primary)
            if y_lo is not None:
                implot.setup_axis_limits(implot.ImAxis_.y1, y_lo, y_hi, implot.Cond_.always)
            did_fit = True
        if cell.pending_y_lim is not None:
            lo, hi = cell.pending_y_lim
            implot.setup_axis_limits(implot.ImAxis_.y1, lo, hi, implot.Cond_.always)
            cell.pending_y_lim = None
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
            y_lo = float(np.nanmin(signal.y))
            y_hi = float(np.nanmax(signal.y))
            lo = y_lo if lo is None else min(lo, y_lo)
            hi = y_hi if hi is None else max(hi, y_hi)
        if lo is None or hi is None:
            return None, None
        if hi <= lo:
            hi = lo + 1.0
        return lo, hi

    # -- panel --------------------------------------------------------------
    def render(self, state: AppState) -> None:
        self._poll_export(state)
        self._toolbar(state)
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


def cell_index_of(state: AppState, cell: SubplotCell) -> int:
    for i, c in enumerate(state.cells):
        if c is cell:
            return i
    return 0
