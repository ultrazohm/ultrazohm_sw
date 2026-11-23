"""Headless render test for the Nodes canvas (no GPU window).

Drives a few real frames of ``NodesPanel.render`` against an ImGui + node-editor
context so the editor calls (begin_node/pins/links, param widgets, create/delete)
are exercised without a window. The graph logic itself is covered by test_nodes.py.
"""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))


def test_nodes_panel_renders_a_graph():
    from imgui_bundle import imgui, implot
    from imgui_bundle import imgui_node_editor as ed

    from uz_dataviewer.panels.nodes import NodesPanel
    from uz_dataviewer.state import AppState

    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1400, 900)
    io.delta_time = 1.0 / 60.0
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    editor = ed.create_editor()
    ed.set_current_editor(editor)

    state = AppState()
    t = np.linspace(0.0, 1.0, 2000)
    state.registry.add_run(
        "Log.csv", "Log.csv", t, {"ia": np.sin(2 * np.pi * 50 * t).astype(np.float32)}, {"ia": ""}
    )
    for line in (
        "node_source(run_1, ia)", "node_add(filter)", "node_set(node_2, cutoff, 100)",
        "node_link(node_1, node_2)", "node_add(fft)", "node_link(node_2, node_3)", "node_eval()",
    ):
        state.commands.dispatch(state, line)

    panel = NodesPanel()
    try:
        for _ in range(3):  # first frame's begin returns False
            imgui.new_frame()
            imgui.begin("Nodes")
            panel.render(state)
            imgui.end()
            imgui.render()
    finally:
        ed.destroy_editor(editor)
        implot.destroy_context()
        imgui.destroy_context()

    # The chain materialized both transform outputs as derived runs.
    derived = {r.label for r in state.registry.runs if r.derived}
    assert {"node_2", "node_3"} <= derived
    assert [n.kind for n in state.nodes.ordered()] == ["source", "filter", "fft"]
