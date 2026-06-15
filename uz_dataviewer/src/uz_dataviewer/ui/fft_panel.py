"""FFT plot cell: pick a source time plot + one of its signals, compute the
amplitude spectrum of the cursor-selected region (or the visible range)."""

from __future__ import annotations

import numpy as np
from imgui_bundle import imgui, implot

from uz_dataviewer.analysis import fft
from uz_dataviewer.ui.app_state import PLOT_TYPE_TIME, AppState, PlotConfig


class FftPanel:
    def __init__(self, state: AppState):
        self.state = state
        # plot_index -> (cache_key, FftResult)
        self._cache: dict[int, tuple[tuple, fft.FftResult | None]] = {}

    # ----------------------------------------------------------------- header

    def render_header(self, plot_index: int, plot: PlotConfig) -> None:
        state = self.state
        source_indices = [
            i
            for i in range(state.visible_plot_count)
            if i != plot_index
            and state.plots[i].plot_type == PLOT_TYPE_TIME
            and state.plots[i].series
        ]

        if not source_indices:
            imgui.text_disabled("No time plot with signals to analyze.")
            return

        if plot.fft_source_plot not in source_indices:
            plot.fft_source_plot = source_indices[0]

        imgui.set_next_item_width(90)
        if imgui.begin_combo("##fft_src", f"Plot {plot.fft_source_plot + 1}"):
            for i in source_indices:
                if imgui.selectable(f"Plot {i + 1}", i == plot.fft_source_plot)[0]:
                    plot.fft_source_plot = i
            imgui.end_combo()

        source = state.plots[plot.fft_source_plot]
        if plot.fft_series_index >= len(source.series):
            plot.fft_series_index = 0
        current_ref = source.series[plot.fft_series_index]

        imgui.same_line()
        imgui.set_next_item_width(170)
        if imgui.begin_combo("##fft_sig", state.series_label(current_ref)):
            for i, ref in enumerate(source.series):
                if imgui.selectable(state.series_label(ref), i == plot.fft_series_index)[0]:
                    plot.fft_series_index = i
            imgui.end_combo()

        imgui.same_line()
        if imgui.button("Options##fft"):
            imgui.open_popup("fft_options")
        if imgui.begin_popup("fft_options"):
            imgui.set_next_item_width(120)
            if imgui.begin_combo("Window", plot.fft_window):
                for window_name in fft.WINDOWS:
                    if imgui.selectable(window_name, window_name == plot.fft_window)[0]:
                        plot.fft_window = window_name
                imgui.end_combo()
            _, plot.fft_use_cursors = imgui.checkbox(
                "Use source plot cursors", plot.fft_use_cursors
            )
            if imgui.is_item_hovered():
                imgui.set_tooltip(
                    "On: analyze the region between the source plot's cursors.\n"
                    "Off: analyze the source plot's visible time range."
                )
            _, plot.fft_log_x = imgui.checkbox("Log frequency axis", plot.fft_log_x)
            _, plot.fft_log_y = imgui.checkbox("Log amplitude axis", plot.fft_log_y)
            imgui.end_popup()

    # ------------------------------------------------------------------- plot

    def render_plot(self, plot_index: int, plot: PlotConfig, size: imgui.ImVec2) -> None:
        state = self.state
        result = self._compute(plot_index, plot)

        if not implot.begin_plot(f"##fft_plot_{plot_index}", size, implot.Flags_.no_title):
            return
        implot.setup_axes("frequency [Hz]", "amplitude")
        if plot.fft_log_x:
            implot.setup_axis_scale(implot.ImAxis_.x1, implot.Scale_.log10)
        if plot.fft_log_y:
            implot.setup_axis_scale(implot.ImAxis_.y1, implot.Scale_.log10)

        if result is not None:
            frequencies = result.frequencies
            amplitudes = result.amplitudes
            if plot.fft_log_x and len(frequencies) > 1:
                frequencies = frequencies[1:]  # log scale cannot show f=0
                amplitudes = amplitudes[1:]
            source_ref = self._source_ref(plot)
            label = state.series_label(source_ref) if source_ref else "FFT"
            implot.plot_line(f"FFT {label}", frequencies, amplitudes)
        implot.end_plot()

        if result is not None:
            imgui.text_disabled(
                f"region {result.t_start:.6g}..{result.t_stop:.6g} s, "
                f"{result.n_samples:,} samples @ {result.sample_rate:,.0f} Hz, "
                f"df={result.sample_rate / result.n_samples:.4g} Hz"
            )

    # ----------------------------------------------------------------- helpers

    def _source_ref(self, plot: PlotConfig):
        if not (0 <= plot.fft_source_plot < len(self.state.plots)):
            return None
        source = self.state.plots[plot.fft_source_plot]
        if plot.fft_source_plot >= self.state.visible_plot_count:
            return None
        if source.plot_type != PLOT_TYPE_TIME or not source.series:
            return None
        if plot.fft_series_index >= len(source.series):
            return None
        return source.series[plot.fft_series_index]

    def _compute(self, plot_index: int, plot: PlotConfig) -> fft.FftResult | None:
        state = self.state
        ref = self._source_ref(plot)
        if ref is None:
            return None
        resolved = state.store.get_signal(ref)
        if resolved is None:
            return None
        run, time, values = resolved

        source = state.plots[plot.fft_source_plot]
        region = None
        if plot.fft_use_cursors:
            region = source.cursor_range()
        if region is None:
            region = source.last_x_range
        if region is None:
            region = (float(time[0]), float(time[-1]))

        cache_key = (
            ref,
            round(region[0], 12),
            round(region[1], 12),
            plot.fft_window,
            state.store.revision,
        )
        cached = self._cache.get(plot_index)
        if cached is not None and cached[0] == cache_key:
            return cached[1]

        result = fft.compute_fft(
            time, values, t_start=region[0], t_stop=region[1], window=plot.fft_window
        )
        self._cache[plot_index] = (cache_key, result)
        return result
