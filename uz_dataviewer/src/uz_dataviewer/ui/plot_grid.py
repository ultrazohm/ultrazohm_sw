"""Main view: toolbar + runtime-settable grid of plot cells.

Each cell hosts either a time-series plot or an FFT plot (switchable at
runtime). Cells keep their configuration when the grid shrinks and grows.
"""

from __future__ import annotations

from imgui_bundle import imgui, implot

from uz_dataviewer.ui.app_state import (
    GRID_PRESETS,
    PLOT_TYPE_TIME,
    PLOT_TYPES,
    AppState,
)
from uz_dataviewer.ui.fft_panel import FftPanel
from uz_dataviewer.ui.plot_panel import TimeSeriesPanel


class PlotGrid:
    def __init__(self, state: AppState):
        self.state = state
        self.time_panel = TimeSeriesPanel(state)
        self.fft_panel = FftPanel(state)

    def render(self) -> None:
        self._render_toolbar()
        imgui.separator()
        self._render_grid()

    def _render_toolbar(self) -> None:
        state = self.state

        imgui.text("Grid")
        imgui.same_line()
        imgui.set_next_item_width(80)
        rows, cols = state.grid
        if imgui.begin_combo("##grid", f"{rows} x {cols}"):
            for index, (r, c) in enumerate(GRID_PRESETS):
                if imgui.selectable(f"{r} x {c}", index == state.grid_preset_index)[0]:
                    state.grid_preset_index = index
            imgui.end_combo()

        imgui.same_line()
        changed, state.link_time_axes = imgui.checkbox(
            "Lock time axes", state.link_time_axes
        )
        if changed and not state.link_time_axes:
            state.shared_x_range = None
        if imgui.is_item_hovered():
            imgui.set_tooltip("Pan/zoom of one time plot is applied to all time plots")

        imgui.same_line()
        imgui.text_disabled("|")
        imgui.same_line()
        imgui.text("Detail")
        imgui.same_line()
        imgui.set_next_item_width(100)
        target = state.downsampler.target_points
        if imgui.begin_combo("##detail", f"{target} pts"):
            for points in (1000, 2000, 4000, 8000, 16000):
                if imgui.selectable(f"{points} pts", points == target)[0]:
                    state.downsampler.target_points = points
                    state.downsampler.invalidate()
            imgui.end_combo()
        if imgui.is_item_hovered():
            imgui.set_tooltip(
                "Maximum points drawn per signal and viewport "
                "(MinMaxLTTB downsampling keeps peaks visible)"
            )

    def _render_grid(self) -> None:
        state = self.state
        rows, cols = state.grid
        spacing = imgui.get_style().item_spacing
        avail = imgui.get_content_region_avail()
        cell_width = max((avail.x - spacing.x * (cols - 1)) / cols, 120.0)
        cell_height = max((avail.y - spacing.y * (rows - 1)) / rows, 120.0)

        for row in range(rows):
            for col in range(cols):
                if col > 0:
                    imgui.same_line()
                index = row * cols + col
                imgui.begin_child(
                    f"plot_cell_{index}",
                    imgui.ImVec2(cell_width, cell_height),
                    imgui.ChildFlags_.borders,
                )
                self._render_cell(index)
                imgui.end_child()

    def _render_cell(self, index: int) -> None:
        state = self.state
        plot = state.plots[index]

        imgui.push_id(index)
        imgui.set_next_item_width(110)
        if imgui.begin_combo("##plot_type", plot.plot_type):
            for plot_type in PLOT_TYPES:
                if imgui.selectable(plot_type, plot_type == plot.plot_type)[0]:
                    plot.plot_type = plot_type
            imgui.end_combo()
        imgui.same_line()

        if plot.plot_type == PLOT_TYPE_TIME:
            self.time_panel.render_header(index, plot)
        else:
            self.fft_panel.render_header(index, plot)

        plot_size = imgui.get_content_region_avail()
        if plot.plot_type == PLOT_TYPE_TIME:
            self.time_panel.render_plot(index, plot, plot_size)
            if not plot.series:
                self._empty_hint()
        else:
            # Reserve one info line below the FFT plot.
            plot_size = imgui.ImVec2(
                plot_size.x,
                max(plot_size.y - imgui.get_text_line_height_with_spacing(), 80.0),
            )
            self.fft_panel.render_plot(index, plot, plot_size)
        imgui.pop_id()

    @staticmethod
    def _empty_hint() -> None:
        # Overlay a hint over the empty plot we just drew.
        rect_min = imgui.get_item_rect_min()
        rect_max = imgui.get_item_rect_max()
        text = "Drop a signal here"
        text_size = imgui.calc_text_size(text)
        position = imgui.ImVec2(
            (rect_min.x + rect_max.x - text_size.x) * 0.5,
            (rect_min.y + rect_max.y - text_size.y) * 0.5,
        )
        imgui.get_window_draw_list().add_text(
            position, imgui.get_color_u32(imgui.Col_.text_disabled), text
        )
