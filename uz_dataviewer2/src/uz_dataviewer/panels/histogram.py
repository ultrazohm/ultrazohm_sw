"""Histogram window: value distributions of one or more signals over a window.

Drag signals in; each signal's samples within the chosen time window are binned.
Built on the shared :class:`~uz_dataviewer.panels.analysis.AnalysisPanel`; every
control is routed through commands (``hist_*``).
"""

from __future__ import annotations

import numpy as np
from imgui_bundle import imgui, implot

from ..downsample import visible_slice
from ..state import AppState
from .analysis import AnalysisPanel


class HistogramPanel(AnalysisPanel):
    prefix = "hist"
    compute_command = "histogram"
    x_label = "value"
    y_label = "count"

    def __init__(self) -> None:
        super().__init__()
        self._results: list[tuple[str, np.ndarray]] = []

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

    def _compute(self, state: AppState, cfg, x_min: float, x_max: float) -> None:
        results = []
        total = 0
        for ref in cfg.sources:
            run = state.registry.get(ref[0])
            signal = state.registry.get_signal(ref[0], ref[1])
            if run is None or signal is None:
                continue
            start, stop = visible_slice(run.time, x_min, x_max)
            values = np.ascontiguousarray(signal.y[start:stop], dtype=np.float64)
            if values.size:
                results.append((state.signal_label(ref), values))
                total += values.size
        self._results = results
        self._info = (
            f"{len(results)} signal(s), {total:,} samples, window [{x_min:.4f}, {x_max:.4f}] s"
            if results else "Drag signals here to histogram them."
        )

    def _draw(self, state: AppState) -> None:
        bins = max(1, state.histogram.bins)
        for label, values in self._results:
            implot.plot_histogram(label, values, bins)

    def _result_labels(self) -> list[str]:
        return [label for label, _ in self._results]
