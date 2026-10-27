"""Histogram window: value distributions of one or more signals over a window.

Drag signals in; each signal's samples within the chosen time window are binned.
Built on the shared :class:`~uz_dataviewer.panels.analysis.AnalysisPanel`; every
control is routed through commands (``hist_*``).
"""

from __future__ import annotations

import numpy as np
from imgui_bundle import imgui, implot

from ..analysis import AnalysisInput, HistogramRequest
from ..state import AppState
from .analysis import AnalysisPanel


class HistogramPanel(AnalysisPanel):
    prefix = "hist"
    compute_command = "histogram"
    x_label = "value"
    y_label = "count"

    def __init__(self) -> None:
        super().__init__()
        # (signal reference, bin_centers, counts, bar_width) -- binned once at compute time.
        self._results: list[tuple[tuple[int, str], np.ndarray, np.ndarray, float]] = []

    def config(self, state: AppState):
        return state.histogram

    def _options_key(self, cfg) -> tuple:
        return (cfg.bins,)

    def _extra_controls(self, state: AppState, cfg) -> None:
        imgui.same_line()
        imgui.set_next_item_width(120)
        changed, n = imgui.input_int("bins", cfg.bins, 1, 10)
        if changed:
            self._emit(state, "hist_bins", max(1, n))
        imgui.same_line()

    def _make_request(self, state: AppState, cfg, x_min: float, x_max: float) -> HistogramRequest:
        return HistogramRequest(AnalysisInput.capture(state.registry, cfg.sources),
                          (x_min, x_max), cfg.bins)

    def _draw(self, state: AppState) -> None:
        for ref, centers, counts, width in self._results:
            implot.plot_bars(state.signal_label(ref), centers, counts, width)

    def _result_refs(self) -> list[tuple[int, str]]:
        return [ref for ref, _, _, _ in self._results]
