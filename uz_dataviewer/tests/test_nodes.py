"""Node graph engine + command + session round-trip tests (no GUI window)."""

from __future__ import annotations

import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import nodes, nodes as nodemod
from uz_dataviewer.commands import CommandError
from uz_dataviewer.session import apply_dict, to_dict
from uz_dataviewer.state import AppState


def _state_with_sine(freq=50.0, n=2000):
    state = AppState()
    t = np.linspace(0.0, 1.0, n)
    y = np.sin(2 * np.pi * freq * t).astype(np.float32)
    state.registry.add_run("Log.csv", "Log.csv", t, {"ia": y}, {"ia": ""})
    return state


def _run(state, *lines):
    for line in lines:
        state.commands.execute(state, *_parse(line))


def _parse(line):
    from uz_dataviewer.commands import parse_call

    return parse_call(line)


def _derived(state, name):
    for run in state.registry.runs:
        if run.derived and run.label == name:
            return run
    return None


# -- engine via commands ------------------------------------------------------
def test_fft_node_materializes_derived_run():
    state = _state_with_sine(50.0)
    _run(state, "node_source(run_1, ia)", "node_add(fft)",
         "node_link(node_1, node_2)", "node_eval()")
    run = _derived(state, "node_2")
    assert run is not None and run.derived
    peak = run.time[int(np.argmax(run.signals["out"].y))]
    assert abs(float(peak) - 50.0) < 1.0  # spectrum peaks at the sine frequency
    assert run.time[0] == 0.0  # x axis is frequency


def test_filter_then_fft_chain():
    state = _state_with_sine(5.0, n=4000)
    # add a 400 Hz component so the low-pass has something to remove
    sig = state.registry.get_signal(1, "ia")
    t = state.registry.get(1).time
    sig.y = (sig.y + np.sin(2 * np.pi * 400 * t)).astype(np.float32)
    _run(state, "node_source(run_1, ia)", "node_add(filter)",
         "node_set(node_2, cutoff, 40)", "node_set(node_2, taps, 201)",
         "node_link(node_1, node_2)", "node_add(fft)",
         "node_link(node_2, node_3)", "node_eval()")
    filt = _derived(state, "node_2")
    spec = _derived(state, "node_3")
    assert filt is not None and spec is not None
    # the filtered-signal spectrum should peak at 5 Hz, not 400 Hz
    peak = spec.time[int(np.argmax(spec.signals["out"].y))]
    assert abs(float(peak) - 5.0) < 2.0


def test_stale_after_param_change():
    state = _state_with_sine()
    _run(state, "node_source(run_1, ia)", "node_add(fft)",
         "node_link(node_1, node_2)", "node_eval()")
    node = state.nodes.get(2)
    assert not nodemod.is_stale(state.registry, state.nodes, node)
    state.commands.execute(state, "node_set", [2, "window", "false"])
    assert nodemod.is_stale(state.registry, state.nodes, node)
    state.commands.execute(state, "node_eval", [])
    assert not nodemod.is_stale(state.registry, state.nodes, node)


def test_shared_upstream_validation_is_linear_and_observes_edits(app_state, monkeypatch):
    run = app_state.registry.add_run('test', 'test', np.arange(8.), {'a': np.ones(8)}, {})
    previous = app_state.nodes.add('source', ref=(run.id, 'a'))
    transforms = []
    for _ in range(20):
        node = app_state.nodes.add('math')
        node.params['op'] = 'add'
        app_state.nodes.link(previous.id, node.id, 0)
        app_state.nodes.link(previous.id, node.id, 1)
        transforms.append(node)
        previous = node
    assert nodes.evaluate(app_state) == len(transforms)
    original = nodes.node_key
    checked = []

    def counted(state, graph, node):
        checked.append(node.id)
        return original(state, graph, node)

    monkeypatch.setattr(nodes, 'node_key', counted)
    assert not nodes.is_stale(app_state.registry, app_state.nodes, previous)
    assert len(checked) == len(set(checked)) == len(transforms)
    transforms[0].params['op'] = 'sub'
    assert nodes.is_stale(app_state.registry, app_state.nodes, previous)
    with pytest.raises(ValueError, match='not current'):
        app_state.registry.get(previous.out_run_id).data_source().validate()
    assert nodes.evaluate(app_state) == len(transforms)
    assert not nodes.is_stale(app_state.registry, app_state.nodes, previous)
    np.testing.assert_array_equal(previous.out_y, np.zeros(8))


def test_shift_node_offsets_time():
    state = _state_with_sine(50.0)
    _run(state, "node_source(run_1, ia)", "node_add(shift)", "node_set(node_2, by, 5)",
         "node_link(node_1, node_2)", "node_eval()")
    run = _derived(state, "node_2")
    assert abs(float(run.time[0]) - 5.0) < 1e-6  # whole axis shifted +5 s


def test_source_crop_limits_window():
    state = _state_with_sine(50.0, n=1000)  # t in [0, 1]
    _run(state, "node_source(run_1, ia)", "node_set(node_1, tmin, 0.2)",
         "node_set(node_1, tmax, 0.4)", "node_add(shift)", "node_set(node_2, by, 0)",
         "node_link(node_1, node_2)", "node_eval()")
    run = _derived(state, "node_2")
    assert run.n_rows < 1000  # cropped
    assert run.time[0] >= 0.19 and run.time[-1] <= 0.41
    # widening the crop restales the downstream node
    assert not nodemod.is_stale(state.registry, state.nodes, state.nodes.get(2))
    state.commands.execute(state, "node_set", [1, "tmax", "0.6"])
    assert nodemod.is_stale(state.registry, state.nodes, state.nodes.get(2))


def test_stale_propagates_downstream():
    """Editing an upstream node must mark everything downstream stale too, even
    before the upstream is re-evaluated (else a chained node shows fresh while
    displaying results from the old input)."""
    state = _state_with_sine(5.0, n=4000)
    _run(state, "node_source(run_1, ia)", "node_add(filter)",
         "node_set(node_2, cutoff, 40)", "node_link(node_1, node_2)",
         "node_add(fft)", "node_link(node_2, node_3)", "node_eval()")
    filt, fft = state.nodes.get(2), state.nodes.get(3)
    assert not nodemod.is_stale(state.registry, state.nodes, fft)
    state.commands.execute(state, "node_set", [2, "cutoff", "80"])  # change upstream
    assert nodemod.is_stale(state.registry, state.nodes, filt)
    assert nodemod.is_stale(state.registry, state.nodes, fft)  # propagated
    state.commands.execute(state, "node_eval", [])
    assert not nodemod.is_stale(state.registry, state.nodes, fft)


def test_link_cycle_is_rejected():
    state = _state_with_sine()
    _run(state, "node_add(math)", "node_add(math)", "node_link(node_1, node_2)")
    with pytest.raises(ValueError):
        state.commands.execute(state, "node_link", [2, 1])


def test_remove_node_drops_derived_run():
    state = _state_with_sine()
    _run(state, "node_source(run_1, ia)", "node_add(fft)",
         "node_link(node_1, node_2)", "node_eval()")
    assert _derived(state, "node_2") is not None
    state.commands.execute(state, "node_remove", [2])
    assert _derived(state, "node_2") is None
    assert state.nodes.get(2) is None


def test_rename_relabels_derived_run():
    state = _state_with_sine()
    _run(state, "node_source(run_1, ia)", "node_add(fft)",
         "node_link(node_1, node_2)", "node_eval()", "node_rename(node_2, spectrum)")
    assert _derived(state, "node_2") is None
    assert _derived(state, "spectrum") is not None


# -- session round-trip -------------------------------------------------------
def test_json_round_trip_rebuilds_graph_and_derived_run(tmp_path):
    state = _state_with_sine(50.0)
    _run(state, "node_source(run_1, ia)", "node_add(fft)",
         "node_link(node_1, node_2)", "node_eval()",
         "add_signal(plot_1, node_2, out)")
    source = state.registry.runs[0]
    source.path = str(tmp_path / 'Log.csv')
    np.savetxt(source.path, np.column_stack([source.time, source.signals['ia'].y]), delimiter=';', header='time;ia', comments='')
    data = to_dict(state)

    # Fresh state with the same source run already present (simulates reload).
    state2 = _state_with_sine(50.0)
    apply_dict(state2, data)

    assert state2.nodes.get(1).kind == "source"
    assert state2.nodes.get(2).inputs == [1]
    spec = _derived(state2, "node_2")
    assert spec is not None
    # the restored plot still resolves the derived signal
    assert any(ref[1] == "out" for ref in state2.cells[0].signals)


def test_failed_parameter_revert_recovers_downstream(app_state):
    from uz_dataviewer.nodes import evaluate, is_stale
    state = app_state
    state.add_run_from_arrays('input', 'input', np.arange(8.), {'a': np.ones(8)}, {})
    _run(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)',
         'node_set(node_2,k,2)', 'node_eval()')
    # Invalid session/plugin state may still reach evaluation, even though the
    # command boundary now rejects it before mutation.
    state.nodes.get(2).params['k'] = 'bad'
    evaluate(state)
    _run(state, 'node_set(node_2,k,2)', 'node_add(math)', 'node_link(node_2,node_3)')
    assert is_stale(state.registry, state.nodes, state.nodes.get(2))
    assert evaluate(state) == 2
    assert not state.nodes.get(2).error and not state.nodes.get(3).error
    np.testing.assert_array_equal(state.nodes.get(3).out_y, np.full(8, 2))
    assert evaluate(state) == 0


def test_slots_preserve_holes_and_allow_same_source_twice(app_state):
    import pytest
    from uz_dataviewer.nodes import evaluate
    state = app_state
    state.add_run_from_arrays('input', 'input', np.arange(8.), {'a': np.full(8, 10)}, {})
    source = state.nodes.add('source', ref=(1, 'a'))
    node = state.nodes.add('math')
    node.params['op'] = 'sub'
    state.nodes.link(source.id, node.id, 1)
    assert node.inputs == [None, source.id]
    assert evaluate(state) == 0 and 'input slots' in node.error
    state.nodes.link(source.id, node.id, 0)
    assert evaluate(state) == 1
    np.testing.assert_array_equal(node.out_y, np.zeros(8))
    state.nodes.unlink(source.id, node.id, 0)
    assert node.inputs == [None, source.id]
    with pytest.raises(ValueError, match='input range'):
        state.nodes.link(source.id, node.id, 2)
    state.nodes.remove(source.id)
    assert node.inputs == []


def test_recomputed_output_preserves_normalization_and_consumers(app_state):
    from uz_dataviewer.nodes import evaluate
    state = app_state
    time = np.arange(8.) + 100
    values = np.arange(8.) + 1
    state.add_run_from_arrays('input', 'input', time, {'a': values}, {})
    _run(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)',
         'node_eval()', 'normalize_time(node_output_2,0)')
    node = state.nodes.get(2)
    run = state.registry.get(node.out_run_id)
    state.cells[0].signals = [(run.id, 'out')]
    state.fft.sources = [(run.id, 'out')]
    # Exercise replacement of an already constructed source too.
    run.data_source()
    version = run.time_version
    _run(state, 'node_set(node_2,k,2)')
    assert evaluate(state) == 1
    assert state.registry.get(node.out_run_id) is run and run.time_version != version
    assert run.time_origin == 0
    np.testing.assert_array_equal(run.time, np.arange(8.))
    np.testing.assert_array_equal(run.time_raw, time)
    actual_time, actual_values = run.read_window(['out'], 0, 7)
    np.testing.assert_array_equal(actual_time, np.arange(8.))
    np.testing.assert_array_equal(actual_values['out'], 2*values)
    assert state.cells[0].signals == state.fft.sources == [(run.id, 'out')]


def test_deleted_output_recreated_and_indirect_source_rejected(states, recording_csv, execute_commands):
    state = states()
    state.load_sync(str(recording_csv))
    execute_commands(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)', 'node_eval()')
    node = state.nodes.get(2)
    with pytest.raises(CommandError, match='node_link'):
        execute_commands(state, f'node_source(run_{node.out_run_id},out)')
    state.remove_run(node.out_run_id)
    assert nodes.evaluate(state, 2) == 1 and state.registry.get(node.out_run_id) is not None


def test_source_version_invalidates_downstream(states, recording_csv, execute_commands):
    from uz_dataviewer.model import Signal
    state = states()
    state.loading_mode = 'memory'
    run = state.load_sync(str(recording_csv))
    execute_commands(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)', 'node_eval()')
    run.signals['a'] = Signal('a', '', np.full(8, 42, dtype=np.float32), run.id)
    assert nodes.is_stale(state.registry, state.nodes, state.nodes.get(2))
    nodes.evaluate(state)
    np.testing.assert_array_equal(state.nodes.get(2).out_y, np.full(8, 42))


def test_node_output_shape_validation():
    from uz_dataviewer.nodes import TransformSpec, Node, REGISTRY, _compute
    spec = TransformSpec('bad_shape', lambda inputs, params: (np.arange(2.), np.arange(3.), 'bad'))
    REGISTRY['bad_shape'] = spec
    try:
        with pytest.raises(ValueError, match='equal-length'):
            _compute(Node(1, 'bad_shape', 'bad'), [(np.arange(2.), np.arange(2.))])
    finally:
        REGISTRY.pop('bad_shape')
