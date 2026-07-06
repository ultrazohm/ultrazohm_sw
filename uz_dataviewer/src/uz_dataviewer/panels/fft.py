"""FFT window: amplitude spectra of one or more signals over a time window.

Drag signals in; the window follows a chosen subplot, the full record, or a manual
range. The transform runs on demand only. Built on the shared
:class:`~uz_dataviewer.panels.analysis.AnalysisPanel`; every control is routed
through commands (``fft_*``).
"""

from __future__ import annotations

import numpy as np
from imgui_bundle import imgui, implot

from ..analysis import compute_fft
from ..downsample import PYRAMID_MIN_POINTS, Pyramid
from ..state import AppState
from .analysis import AnalysisPanel, follow_combo  # noqa: F401 - re-exported for callers


class FftPanel(AnalysisPanel):
    prefix = "fft"
    compute_command = "fft"
    x_label = "frequency in Hz"
    y_label = "amplitude"

    def __init__(self) -> None:
        super().__init__()
        # (label, freqs, mag, pyramid-or-None) -- pyramid decimates a huge spectrum.
        self._results: list[tuple[str, np.ndarray, np.ndarray, object]] = []

    def config(self, state: AppState):
        return state.fft

    def _options_key(self, cfg) -> tuple:
        return (cfg.remove_dc, cfg.window)  # log axes are view-only -> not stale

    def _extra_controls(self, state: AppState, cfg) -> None:
        changed, on = imgui.checkbox("Remove DC", cfg.remove_dc)
        if changed:
            self._emit(state, "fft_remove_dc", on)
        imgui.same_line()
        changed, on = imgui.checkbox("Hann window", cfg.window)
        if changed:
            self._emit(state, "fft_hann", on)
        imgui.same_line()
        changed, on = imgui.checkbox("log x", cfg.log_x)
        if changed:
            self._emit(state, "fft_logx", on)
        imgui.same_line()
        changed, on = imgui.checkbox("log y", cfg.log_y)
        if changed:
            self._emit(state, "fft_logy", on)
        imgui.same_line()

    def _setup_axes(self, state: AppState) -> None:
        cfg = state.fft
        implot.setup_axis_scale(
            implot.ImAxis_.x1, implot.Scale_.log10 if cfg.log_x else implot.Scale_.linear
        )
        implot.setup_axis_scale(
            implot.ImAxis_.y1, implot.Scale_.log10 if cfg.log_y else implot.Scale_.linear
        )

    def _compute(self, state: AppState, cfg, x_min: float, x_max: float) -> None:
        results = []
        info = ""
        for ref in cfg.sources:
            run = state.registry.get(ref[0])
            signal = state.registry.get_signal(ref[0], ref[1])
            if run is None or signal is None:
                continue
            result = compute_fft(
                run.time, signal.y, x_min, x_max,
                remove_dc=cfg.remove_dc, window=cfg.window,
            )
            if result.ok:
                pyramid = Pyramid.build(result.mag) if result.mag.size > PYRAMID_MIN_POINTS else None
                results.append((state.signal_label(ref), result.freqs, result.mag, pyramid))
            info = result.info
        self._results = results
        self._info = info or "Drag signals here to analyse them."

    def _draw(self, state: AppState) -> None:
        for label, freqs, mag, pyramid in self._results:
            self._plot_decimated(state, label, freqs, mag, pyramid)

    def _result_labels(self) -> list[str]:
        return [label for label, _, _, _ in self._results]
