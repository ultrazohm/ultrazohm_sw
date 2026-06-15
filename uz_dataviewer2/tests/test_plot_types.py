"""Headless render smoke tests for every plot type and the spy inset.

Drives a few real ImGui/ImPlot frames (no window) to make sure each cell mode
renders without raising -- the begin_plot/end_plot pairing, Spec markers,
histogram, XY and FFT paths, and the drag-rect spy inset.
"""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.panels.plots import PlotsPanel  # noqa: E402
from uz_dataviewer.state import AppState, PlotType  # noqa: E402


def _state():
    state = AppState()
    time = np.linspace(2.0, 6.0, 2000)
    state.registry.add_run(
        "Log.csv", "Log.csv", time,
        {"ia": np.sin(time).astype(np.float32), "ib": np.cos(time).astype(np.float32)},
        {"ia": "", "ib": ""},
    )
    return state


def _drive(state, frames=3):
    from imgui_bundle import imgui, implot

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1400, 900)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures

    panel = PlotsPanel()
    try:
        for _ in range(frames):
            imgui.new_frame()
            imgui.begin("Plots")
            panel.render(state)
            imgui.end()
            imgui.render()
    finally:
        implot.destroy_context()
        imgui.destroy_context()


def test_render_every_plot_type():
    state = _state()
    state.set_grid(2, 3)
    types = [PlotType.LINE, PlotType.SCATTER, PlotType.STAIRS,
             PlotType.HISTOGRAM, PlotType.XY, PlotType.FFT]
    for i, t in enumerate(types):
        state.cells[i].plot_type = t
        state.cells[i].add((1, "ia"))
        if t is PlotType.XY:
            state.cells[i].xy_source = (1, "ib")
    state.cells[0].show_samples = True  # exercise the Spec marker path
    _drive(state)  # must not raise


def test_render_spy_inset():
    state = _state()
    state.set_grid(1, 1)
    state.cells[0].add((1, "ia"))
    state.cells[0].spy = True
    _drive(state, frames=4)  # initialises spy_rect then renders the inset
    assert state.cells[0].spy_rect is not None


def test_render_cursors_and_secondary_axis():
    state = _state()
    state.set_grid(1, 1)
    state.cells[0].add((1, "ia"))
    state.cells[0].add((1, "ib"))
    state.cells[0].y2_signals = [(1, "ib")]  # ib on the right axis
    state.cells[0].cursors = True
    _drive(state, frames=4)  # initialises cursor_x then renders cursors + y2
    assert state.cells[0].cursor_x is not None


def test_fft_cell_does_not_recompute_every_frame(monkeypatch):
    """With auto-calc off, an FFT cell computes once (structural change), not
    every frame -- the fix for the FFT performance problem."""
    import uz_dataviewer.panels.plots as plots_mod

    calls = {"n": 0}
    real = plots_mod.compute_fft

    def counting(*a, **k):
        calls["n"] += 1
        return real(*a, **k)

    monkeypatch.setattr(plots_mod, "compute_fft", counting)
    state = _state()
    state.set_grid(1, 1)
    state.cells[0].plot_type = PlotType.FFT
    state.cells[0].add((1, "ia"))
    _drive(state, frames=6)
    assert calls["n"] == 1  # one signal, computed once (structural) -- not 6x
