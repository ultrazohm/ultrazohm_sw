"""Headless render test for the Nodes canvas (no GPU window).

Drives a few real frames of ``NodesPanel.render`` against an ImGui + node-editor
context so the editor calls (begin_node/pins/links, param widgets, create/delete)
are exercised without a window. The graph logic itself is covered by test_nodes.py.
"""

from __future__ import annotations

import numpy as np
import pytest



from uz_dataviewer.nodes import evaluate
from uz_dataviewer.panels.nodes import NodesPanel


def test_nodes_panel_renders_a_graph(app_state, gui_frame):
    state = app_state
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
    for _ in range(3):
        gui_frame(panel, state, 'Nodes')

    # The chain materialized both transform outputs as derived runs.
    derived = {r.label for r in state.registry.runs if r.derived}
    assert {"node_2", "node_3"} <= derived
    assert [n.kind for n in state.nodes.ordered()] == ["source", "filter", "fft"]


def test_binary_pins_honor_destination_and_round_trip(app_state, tmp_path):
    from uz_dataviewer.panels.nodes import NodesPanel, _out_pin, _in_pin
    from uz_dataviewer.nodes import evaluate
    from uz_dataviewer.session import to_dict, apply_dict
    state = app_state
    path = tmp_path / 'input.csv'
    path.write_text('time;a;b\n' + ''.join(f'{i};10;2\n' for i in range(8)))
    state.load_sync(str(path))
    a = state.nodes.add('source', ref=(1, 'a'))
    b = state.nodes.add('source', ref=(1, 'b'))
    node = state.nodes.add('math')
    node.params['op'] = 'sub'
    panel = NodesPanel()
    panel._try_link(state, _out_pin(b.id), _in_pin(node.id, 1))
    # Save an incomplete graph too: the second slot must not shift to the first.
    saved = to_dict(state)
    apply_dict(state, saved)
    assert state.nodes.get(node.id).inputs == [None, b.id]
    panel._try_link(state, _in_pin(node.id, 0), _out_pin(a.id))
    assert evaluate(state) == 1
    np.testing.assert_array_equal(state.nodes.get(node.id).out_y, np.full(8, 8))
    saved = to_dict(state)
    apply_dict(state, saved)
    np.testing.assert_array_equal(state.nodes.get(node.id).out_y, np.full(8, 8))
    assert state.nodes.get(node.id).inputs == [a.id, b.id]


def test_source_crop_and_float_edits_preserve_precision(app_state, monkeypatch):
    from imgui_bundle import imgui
    from uz_dataviewer.panels.nodes import NodesPanel
    from uz_dataviewer.nodes import evaluate
    state = app_state
    time = np.linspace(100.0001, 100.0002, 8)
    state.add_run_from_arrays('input', 'input', time, {'a': np.arange(8)}, {})
    source = state.nodes.add('source', ref=(1, 'a'))
    node = state.nodes.add('shift')
    state.nodes.link(source.id, node.id)
    panel = NodesPanel()
    monkeypatch.setattr(imgui, 'checkbox', lambda *args: (True, True))
    panel._source_window(state, source)
    assert (float(source.params['tmin']), float(source.params['tmax'])) == (time[0], time[-1])
    value = 0.1234567890123456
    monkeypatch.setattr(imgui, 'input_double', lambda *args: (True, value))
    panel._float(state, node, 'by', 'by')
    assert float(node.params['by']) == value
    assert evaluate(state) == 1
    np.testing.assert_array_equal(node.out_time, time + value)


def test_existing_canvas_applies_restored_positions(app_state, gui_frame):
    from imgui_bundle import imgui_node_editor as ed
    from uz_dataviewer.panels.nodes import NodesPanel
    from uz_dataviewer.session import to_dict, apply_dict
    state = app_state
    node = state.nodes.add('math')
    node.pos = (100., 100.)
    panel = NodesPanel()
    for _ in range(3):
        gui_frame(panel, state)
    saved = to_dict(state)
    saved['nodes'][0]['pos'] = [600., 400.]
    apply_dict(state, saved)
    for _ in range(3):
        gui_frame(panel, state)
    position = ed.get_node_position(ed.NodeId(node.id * 4))
    assert (position.x, position.y) == (600., 400.)
    assert state.nodes.get(node.id).pos == (600., 400.)


@pytest.mark.parametrize('value', ['inf', 'nan', '1e309', '2147483648', '1.5', 'bad'])
def test_invalid_integer_parameter_is_rejected_and_legacy_value_renders(app_state, gui_frame, value):
    state = app_state
    state.commands.execute(state, 'node_add', ['filter'])
    node = state.nodes.get(1)
    before = dict(node.params)
    with pytest.raises(ValueError):
        state.commands.execute(state, 'node_set', [1, 'taps', value])
    assert node.params == before
    # Session data is intentionally preserved for repair; its editor must survive.
    node.params['taps'] = value
    from uz_dataviewer.session import apply_dict, to_dict
    apply_dict(state, to_dict(state))
    node = state.nodes.get(1)
    panel = NodesPanel()
    gui_frame(panel, state)
    gui_frame(panel, state)
    evaluate(state)
    assert node.error


def test_node_pos_moves_existing_canvas(app_state, gui_frame):
    from imgui_bundle import imgui_node_editor as ed

    node = app_state.nodes.add("math")
    node.pos = (100.0, 100.0)
    panel = NodesPanel()
    for _ in range(3):
        gui_frame(panel, app_state)
    app_state.commands.execute(app_state, "node_pos", [node.id, 600, 400])
    for _ in range(3):
        gui_frame(panel, app_state)
    pos = ed.get_node_position(ed.NodeId(node.id * 4))
    assert node.pos == (600.0, 400.0) and (pos.x, pos.y) == (600.0, 400.0)


def test_node_position_zero_is_explicit(app_state, gui_frame):
    from imgui_bundle import imgui_node_editor as ed

    node = app_state.nodes.add("math")
    app_state.commands.execute(app_state, "node_pos", [node.id, 0, 0])
    panel = NodesPanel()
    for _ in range(3):
        gui_frame(panel, app_state)
    pos = ed.get_node_position(ed.NodeId(node.id * 4))
    assert (pos.x, pos.y) == node.pos == (0.0, 0.0)


def test_invalid_boolean_can_be_repaired_in_node_canvas(app_state, gui_frame):
    node = app_state.nodes.add("fft")
    node.params["window"] = "invalid"
    gui_frame(NodesPanel(), app_state)
    assert node.params["window"] == "invalid"
    app_state.commands.execute(app_state, "node_set", [node.id, "window", "true"])
    assert node.params["window"] == "true"
