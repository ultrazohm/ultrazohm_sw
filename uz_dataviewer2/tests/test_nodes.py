"""Node graph engine + command + session round-trip tests (no GUI window)."""

from __future__ import annotations

import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer import nodes as nodemod  # noqa: E402
from uz_dataviewer.session import apply_dict, to_dict, to_script  # noqa: E402
from uz_dataviewer.state import AppState  # noqa: E402


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
    assert not nodemod.is_stale(state, state.nodes, node)
    state.commands.execute(state, "node_set", [2, "window", "false"])
    assert nodemod.is_stale(state, state.nodes, node)
    state.commands.execute(state, "node_eval", [])
    assert not nodemod.is_stale(state, state.nodes, node)


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
    assert not nodemod.is_stale(state, state.nodes, state.nodes.get(2))
    state.commands.execute(state, "node_set", [1, "tmax", "0.6"])
    assert nodemod.is_stale(state, state.nodes, state.nodes.get(2))


def test_stale_propagates_downstream():
    """Editing an upstream node must mark everything downstream stale too, even
    before the upstream is re-evaluated (else a chained node shows fresh while
    displaying results from the old input)."""
    state = _state_with_sine(5.0, n=4000)
    _run(state, "node_source(run_1, ia)", "node_add(filter)",
         "node_set(node_2, cutoff, 40)", "node_link(node_1, node_2)",
         "node_add(fft)", "node_link(node_2, node_3)", "node_eval()")
    filt, fft = state.nodes.get(2), state.nodes.get(3)
    assert not nodemod.is_stale(state, state.nodes, fft)
    state.commands.execute(state, "node_set", [2, "cutoff", "80"])  # change upstream
    assert nodemod.is_stale(state, state.nodes, filt)
    assert nodemod.is_stale(state, state.nodes, fft)  # propagated
    state.commands.execute(state, "node_eval", [])
    assert not nodemod.is_stale(state, state.nodes, fft)


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
def test_json_round_trip_rebuilds_graph_and_derived_run():
    state = _state_with_sine(50.0)
    _run(state, "node_source(run_1, ia)", "node_add(fft)",
         "node_link(node_1, node_2)", "node_eval()",
         "add_signal(plot_1, node_2, out)")
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


def test_script_round_trip():
    state = _state_with_sine(50.0)
    _run(state, "node_source(run_1, ia)", "node_add(fft)",
         "node_link(node_1, node_2)", "node_eval()")
    lines = to_script(state)

    state2 = _state_with_sine(50.0)
    for line in lines:
        if line.startswith("load(") or line.startswith("#"):
            continue  # source run is already present in state2
        state2.commands.dispatch(state2, line)

    assert state2.nodes.get(2) is not None and state2.nodes.get(2).kind == "fft"
    assert _derived(state2, "node_2") is not None
