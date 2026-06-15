"""Time-series plot cell: drop target, viewport downsampling, cursors,
secondary y-axis, cursor readout and CSV export of the cursor region."""

from __future__ import annotations

import os

import numpy as np
from imgui_bundle import imgui, implot

from uz_dataviewer.core.data_store import SignalRef
from uz_dataviewer.ui.app_state import SIGNAL_PAYLOAD_TYPE, AppState, PlotConfig

try:
    from imgui_bundle import portable_file_dialogs as pfd

    HAS_FILE_DIALOG = True
except ImportError:  # pragma: no cover
    HAS_FILE_DIALOG = False

CURSOR_COLOR_A = imgui.ImVec4(0.84, 0.16, 0.16, 1.0)
CURSOR_COLOR_B = imgui.ImVec4(0.12, 0.47, 0.71, 1.0)


class TimeSeriesPanel:
    def __init__(self, state: AppState):
        self.state = state
        # plot_index -> set of SignalRef drawn on the right (y2) axis
        self.y2_series: dict[int, set[SignalRef]] = {}
        # plot_index -> request to fit axes on the next frame
        self.pending_fit: set[int] = set()
        # plot_index -> hovered state of the previous frame (for axis linking)
        self.last_hovered: dict[int, bool] = {}
        self.export_relative_time: bool = False
        self._save_dialog = None
        self._save_request: tuple[int, float, float] | None = None

    # ----------------------------------------------------------------- header

    def render_header(self, plot_index: int, plot: PlotConfig) -> None:
        changed, plot.show_cursors = imgui.checkbox("Cursors", plot.show_cursors)
        if changed and not plot.show_cursors:
            plot.cursor_a = plot.cursor_b = None

        imgui.same_line()
        if imgui.button("Fit"):
            self.pending_fit.add(plot_index)

        imgui.same_line()
        if imgui.button("Options"):
            imgui.open_popup("plot_options")
        if imgui.begin_popup("plot_options"):
            if imgui.menu_item_simple("Clear plot", enabled=bool(plot.series)):
                plot.series.clear()
                self.y2_series.pop(plot_index, None)
            imgui.separator()
            _, self.export_relative_time = imgui.checkbox(
                "Export: start time at 0", self.export_relative_time
            )
            export_possible = bool(plot.series) and plot.cursor_range() is not None
            if imgui.menu_item_simple(
                "Export cursor region to CSV ...", enabled=export_possible
            ):
                self._begin_export(plot_index, plot)
            if not export_possible and imgui.is_item_hovered():
                imgui.set_tooltip("Enable cursors and add signals first")
            imgui.end_popup()

        self._poll_export(plot)

    # ------------------------------------------------------------------- plot

    def render_plot(self, plot_index: int, plot: PlotConfig, size: imgui.ImVec2) -> None:
        state = self.state

        readout_lines = self._cursor_readout(plot) if plot.show_cursors else []
        if readout_lines:
            reserved = imgui.get_text_line_height_with_spacing() * len(readout_lines)
            size = imgui.ImVec2(size.x, max(size.y - reserved, 80.0))

        if plot_index in self.pending_fit:
            implot.set_next_axes_to_fit()
            self.pending_fit.discard(plot_index)

        if not implot.begin_plot(f"##time_plot_{plot_index}", size, implot.Flags_.no_title):
            return

        y2_refs = self.y2_series.get(plot_index, set())
        use_y2 = any(ref in y2_refs for ref in plot.series)

        implot.setup_axes("time [s]", "")
        if use_y2:
            implot.setup_axis(implot.ImAxis_.y2, "", implot.AxisFlags_.aux_default)
        implot.setup_legend(implot.Location_.north_west, implot.LegendFlags_.none)

        link = state.link_time_axes and state.shared_x_range is not None
        if link and not self.last_hovered.get(plot_index, False):
            implot.setup_axis_limits(
                implot.ImAxis_.x1,
                state.shared_x_range[0],
                state.shared_x_range[1],
                implot.Cond_.always,
            )

        limits = implot.get_plot_limits()
        view_min, view_max = limits.x.min, limits.x.max
        plot.last_x_range = (view_min, view_max)

        plot_width_px = max(int(implot.get_plot_size().x), 200)
        n_out = min(max(plot_width_px * 4, 1000), 8000)

        for ref in list(plot.series):
            resolved = state.store.get_signal(ref)
            if resolved is None:
                continue
            run, time, values = resolved
            if not run.active:
                continue
            label = state.series_label(ref)
            xs, ys = state.downsampler.get(
                (plot_index, ref.run_id, ref.signal),
                time,
                values,
                view_min,
                view_max,
                n_out,
            )
            on_y2 = ref in y2_refs
            implot.set_axes(implot.ImAxis_.x1, implot.ImAxis_.y2 if on_y2 else implot.ImAxis_.y1)
            implot.plot_line(label, xs, ys)

            if implot.begin_legend_popup(label):
                axis_changed, on_y2_new = imgui.checkbox("Right y-axis", on_y2)
                if axis_changed:
                    refs = self.y2_series.setdefault(plot_index, set())
                    refs.add(ref) if on_y2_new else refs.discard(ref)
                if imgui.menu_item_simple("Remove from plot"):
                    plot.series.remove(ref)
                    self.y2_series.get(plot_index, set()).discard(ref)
                implot.end_legend_popup()
        implot.set_axes(implot.ImAxis_.x1, implot.ImAxis_.y1)

        if plot.show_cursors:
            self._render_cursors(plot, view_min, view_max)

        self._accept_drop(plot_index)

        hovered = implot.is_plot_hovered()
        end_limits = implot.get_plot_limits()
        implot.end_plot()

        self.last_hovered[plot_index] = hovered
        if state.link_time_axes and hovered:
            state.shared_x_range = (end_limits.x.min, end_limits.x.max)

        for line in readout_lines:
            imgui.text(line)

    # ----------------------------------------------------------------- pieces

    def _accept_drop(self, plot_index: int) -> None:
        if implot.begin_drag_drop_target_plot():
            payload = imgui.accept_drag_drop_payload_py_id(SIGNAL_PAYLOAD_TYPE)
            if payload is not None:
                ref = self.state.store.resolve_payload(payload.data_id)
                if ref is not None:
                    if not self.state.plots[plot_index].series:
                        self.pending_fit.add(plot_index)
                    self.state.add_series(plot_index, ref)
            implot.end_drag_drop_target()

    def _render_cursors(self, plot: PlotConfig, view_min: float, view_max: float) -> None:
        span = view_max - view_min
        if plot.cursor_a is None or plot.cursor_b is None:
            plot.cursor_a = view_min + 0.25 * span
            plot.cursor_b = view_min + 0.75 * span

        _, plot.cursor_a, _, _, _ = implot.drag_line_x(
            0, plot.cursor_a, CURSOR_COLOR_A, 1.5, implot.DragToolFlags_.no_fit
        )
        _, plot.cursor_b, _, _, _ = implot.drag_line_x(
            1, plot.cursor_b, CURSOR_COLOR_B, 1.5, implot.DragToolFlags_.no_fit
        )

    def _cursor_readout(self, plot: PlotConfig) -> list[str]:
        cursors = plot.cursor_range()
        if cursors is None:
            return []
        low, high = plot.cursor_a, plot.cursor_b  # keep A/B order, not sorted
        lines = [f"A: {low:.6g}   B: {high:.6g}   dX: {high - low:.6g}"]
        for ref in plot.series:
            resolved = self.state.store.get_signal(ref)
            if resolved is None:
                continue
            run, time, values = resolved
            if not run.active or len(time) == 0:
                continue
            ya = values[_nearest_index(time, low)]
            yb = values[_nearest_index(time, high)]
            lines.append(
                f"{self.state.series_label(ref)}: A={ya:.6g}  B={yb:.6g}  d={yb - ya:.6g}"
            )
        return lines

    # ----------------------------------------------------------------- export

    def _begin_export(self, plot_index: int, plot: PlotConfig) -> None:
        cursors = plot.cursor_range()
        if cursors is None or not HAS_FILE_DIALOG:
            return
        self._save_request = (plot_index, cursors[0], cursors[1])
        self._save_dialog = pfd.save_file(
            "Export cursor region",
            f"plot_{plot_index + 1}_cursor_export.csv",
            ["CSV files", "*.csv"],
            pfd.opt.force_overwrite,
        )

    def _poll_export(self, plot: PlotConfig) -> None:
        if self._save_dialog is None or not self._save_dialog.ready(0):
            return
        path = self._save_dialog.result()
        self._save_dialog = None
        request = self._save_request
        self._save_request = None
        if not path or request is None:
            return
        plot_index, t_low, t_high = request
        try:
            written = self._write_export(self.state.plots[plot_index], path, t_low, t_high)
            if written:
                self.state.console.info(f"Exported cursor region to '{written}'.")
            else:
                self.state.console.warning("Export skipped: no data between cursors.")
        except Exception as exc:
            self.state.console.error(f"Export failed: {exc}")

    def _write_export(self, plot: PlotConfig, path: str, t_low: float, t_high: float) -> str | None:
        state = self.state
        # Group the plot's series by run: each run keeps its own time base.
        by_run: dict[int, list[SignalRef]] = {}
        for ref in plot.series:
            by_run.setdefault(ref.run_id, []).append(ref)

        written_path = None
        base, extension = os.path.splitext(path)
        for position, (run_id, refs) in enumerate(by_run.items()):
            run = state.store.runs.get(run_id)
            if run is None:
                continue
            start = int(np.searchsorted(run.time, t_low, "left"))
            stop = int(np.searchsorted(run.time, t_high, "right"))
            if stop <= start:
                continue
            time = run.time[start:stop]
            if self.export_relative_time:
                time = time - time[0]
            columns = [time] + [run.signals[r.signal][start:stop] for r in refs]
            header = ";".join(["time"] + [r.signal for r in refs])
            target = path if len(by_run) == 1 else f"{base}_{run.name}{extension or '.csv'}"
            np.savetxt(
                target,
                np.column_stack(columns),
                delimiter=";",
                header=header,
                comments="",
                fmt="%.12g",
            )
            written_path = target if position == 0 else written_path
        return written_path


def _nearest_index(time: np.ndarray, x: float) -> int:
    index = int(np.searchsorted(time, x))
    if index <= 0:
        return 0
    if index >= len(time):
        return len(time) - 1
    return index if abs(time[index] - x) < abs(time[index - 1] - x) else index - 1
