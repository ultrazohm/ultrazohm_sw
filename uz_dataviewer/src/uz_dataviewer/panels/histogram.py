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
        # (label, bin_centers, counts, bar_width) -- binned once at compute time.
        self._results: list[tuple[str, np.ndarray, np.ndarray, float]] = []

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
        bins = max(1, cfg.bins)
        # Collect the in-window slices first, then bin them all on a *shared* range so
        # the bars align across signals (and match the CSV from session.export_histogram,
        # which uses the same shared edges). Per-signal auto-range gave each signal a
        # different width/centre set -> overlapping, misaligned bars.
        slices: list[tuple[str, np.ndarray]] = []
        lo = hi = None
        for ref in cfg.sources:
            run = state.registry.get(ref[0])
            signal = state.registry.get_signal(ref[0], ref[1])
            if run is None or signal is None:
                continue
            start, stop = visible_slice(run.time, x_min, x_max)
            values = signal.y[start:stop]
            if values.size == 0:
                continue
            slices.append((state.signal_label(ref), values))
            vlo, vhi = float(values.min()), float(values.max())
            lo = vlo if lo is None else min(lo, vlo)
            hi = vhi if hi is None else max(hi, vhi)
        results = []
        total = 0
        if slices:
            if hi <= lo:
                hi = lo + 1.0
            # Shared edges: np.histogram accepts float32 directly (edges are float64
            # regardless), so no full-array float64 upcast of up to tens of millions
            # of samples. Bin once here (not every frame); plotting bars is O(bins).
            edges = np.linspace(lo, hi, bins + 1)
            width = float(edges[1] - edges[0])
            for label, values in slices:
                counts, _ = np.histogram(values, bins=edges)
                centers = (edges[:-1] + edges[1:]) / 2.0
                results.append((label, centers, counts.astype(np.float64), width))
                total += int(values.size)
        self._results = results
        self._info = (
            f"{len(results)} signal(s), {total:,} samples, window [{x_min:.4f}, {x_max:.4f}] s"
            if results else "Drag signals here to histogram them."
        )

    def _draw(self, state: AppState) -> None:
        for label, centers, counts, width in self._results:
            implot.plot_bars(label, centers, counts, width)

    def _result_labels(self) -> list[str]:
        return [label for label, _, _, _ in self._results]
