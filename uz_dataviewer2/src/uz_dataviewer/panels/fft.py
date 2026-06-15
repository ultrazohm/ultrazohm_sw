"""FFT panel: spectra of one or more signals over a selectable time window.

Drag signals in from the navigation tree (like the plot panel) to overlay several
spectra. The time window either follows a chosen subplot's X range or is entered
manually (*Custom*). The transform is expensive on large windows, so it runs only
on demand -- the *Compute* button, or once whenever the inputs change -- never
unconditionally every frame.
"""

from __future__ import annotations

import numpy as np
from imgui_bundle import imgui, implot

from ..analysis import compute_fft
from ..state import AppState
from .navigation import SIGNAL_DND_TYPE


def follow_combo(label: str, follow_plot: int, n_plots: int) -> tuple[bool, int]:
    """A 'Custom / plot_N' selector. Returns ``(changed, new_follow_plot)``.

    ``0`` is *Custom*; ``1..n_plots`` follow that subplot's X range.
    """
    labels = ["Custom"] + [f"plot_{i}" for i in range(1, n_plots + 1)]
    cur = follow_plot if 0 <= follow_plot <= n_plots else 0
    imgui.set_next_item_width(110)
    changed, cur = imgui.combo(label, cur, labels)
    return changed, cur


class FftPanel:
    def __init__(self) -> None:
        self._results: list[tuple[str, np.ndarray, np.ndarray]] = []
        self._info: str = ""

    def _compute(self, state: AppState) -> None:
        sources = list(state.fft.sources)
        if not sources:
            self._results = []
            self._info = "Drag signals here to analyse them."
            return

        x_min, x_max = state.resolve_x_window(
            state.fft.follow_plot, (state.fft.x_min, state.fft.x_max), sources
        )

        results = []
        info = ""
        for ref in sources:
            run = state.registry.get(ref[0])
            signal = state.registry.get_signal(ref[0], ref[1])
            if run is None or signal is None:
                continue
            result = compute_fft(
                run.time, signal.y, x_min, x_max,
                remove_dc=state.fft.remove_dc, window=state.fft.window,
            )
            if result.ok:
                results.append((state.signal_label(ref), result.freqs, result.mag))
            info = result.info
        self._results = results
        self._info = info or "No spectra computed."

    def render(self, state: AppState) -> None:
        # Drag-drop / `fft` command, or any control edit below, request a compute.
        recompute = state.fft.compute_requested
        state.fft.compute_requested = False

        changed, state.fft.follow_plot = follow_combo("Window", state.fft.follow_plot, state.cell_count)
        recompute = recompute or changed
        if state.fft.follow_plot == 0:
            imgui.same_line()
            imgui.set_next_item_width(110)
            c1, state.fft.x_min = imgui.input_float("t min", state.fft.x_min)
            imgui.same_line()
            imgui.set_next_item_width(110)
            c2, state.fft.x_max = imgui.input_float("t max", state.fft.x_max)
            recompute = recompute or c1 or c2

        c1, state.fft.remove_dc = imgui.checkbox("Remove DC", state.fft.remove_dc)
        imgui.same_line()
        c2, state.fft.window = imgui.checkbox("Hann window", state.fft.window)
        imgui.same_line()
        if imgui.button("Compute FFT"):
            recompute = True
        imgui.same_line()
        if imgui.button("Clear") and state.fft.sources:
            state.commands.execute(state, "fft_clear", [])
            self._results = []
        recompute = recompute or c1 or c2

        if recompute:
            self._compute(state)

        if self._info:
            imgui.text_disabled(self._info)
        imgui.separator()

        if implot.begin_plot("##fft", imgui.ImVec2(-1, -1)):
            implot.setup_axes("frequency [Hz]", "amplitude")
            for label, freqs, mag in self._results:
                implot.plot_line(label, freqs, mag)
                if implot.begin_legend_popup(label):
                    imgui.text_disabled(label)
                    if imgui.menu_item("Remove", "", False)[0]:
                        self._remove(state, label)
                    implot.end_legend_popup()
            if implot.begin_drag_drop_target_plot():
                payload = imgui.accept_drag_drop_payload_py_id(SIGNAL_DND_TYPE)
                if payload is not None:
                    ref = getattr(state, "dragged_ref", None)
                    if ref is not None:
                        state.commands.execute(state, "fft_source", [ref[0], ref[1]])
                implot.end_drag_drop_target()
            implot.end_plot()

    def _remove(self, state: AppState, label: str) -> None:
        for ref in list(state.fft.sources):
            if state.signal_label(ref) == label:
                state.fft.sources.remove(ref)
        state.fft.compute_requested = True
