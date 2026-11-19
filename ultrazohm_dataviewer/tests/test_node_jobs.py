"""Background evaluation preserves live edits and publishes only valid results."""
import threading
import time

import numpy as np
import pytest

from ultrazohm_dataviewer import nodes, ViewerError
from ultrazohm_dataviewer.operations import Operations


def finish(operations, future):
    deadline = time.monotonic() + 3
    while not future.done() and time.monotonic() < deadline:
        operations.poll()
        time.sleep(.001)
    return future.result(timeout=.1)


def graph(state):
    run = state.registry.add_run('input', '', np.arange(10.), {'y': np.arange(10.)}, {})
    source = state.nodes.add('source', ref=(run.id, 'y'))
    first = state.nodes.add('math')
    first.inputs = [source.id]
    first.params['k'] = '2'
    second = state.nodes.add('math')
    second.inputs = [first.id]
    second.params['k'] = '3'
    return run, first, second


def test_background_chain_publishes_on_application_thread(app_state):
    _, first, second = graph(app_state)
    operations = Operations(app_state)
    try:
        # The GUI command route also returns completion, rather than evaluating inline.
        future = app_state.commands.execute(app_state, 'node_eval', [])
        assert first.out_y is None
        finish(operations, future)
        np.testing.assert_array_equal(second.out_y, np.arange(10.) * 6)
        run = app_state.registry.get(second.out_run_id)
        assert not nodes.is_stale(app_state.registry, app_state.nodes, second)
        original_id = run.id
        run.set_time_origin(50)
        first.params['k'] = '4'
        finish(operations, operations.evaluate_nodes())
        assert second.out_run_id == original_id
        assert app_state.registry.get(original_id).time_origin == 50
        np.testing.assert_array_equal(second.out_y, np.arange(10.) * 12)
    finally:
        operations.close()


def test_evaluation_failure_is_reported_and_can_be_repaired(app_state):
    _, first, second = graph(app_state)
    first.params['k'] = 'invalid'
    operations = Operations(app_state)
    try:
        with pytest.raises(ViewerError) as error:
            finish(operations, operations.evaluate_nodes())
        assert error.value.code == 'evaluation_failed'
        assert first.error
        assert second.out_y is None
        first.params['k'] = '2'
        finish(operations, operations.evaluate_nodes())
        assert not first.error
        assert not second.error
        np.testing.assert_array_equal(second.out_y, np.arange(10.) * 6)
        unrelated = app_state.nodes.add('math')
        unrelated.error = 'unconnected unrelated node'
        finish(operations, operations.evaluate_nodes(second.id))
    finally:
        operations.close()


@pytest.mark.parametrize('change', ['parameter', 'source', 'cancel', 'session'])
def test_pending_evaluation_does_not_publish_after_change(app_state, monkeypatch, change):
    run, first, second = graph(app_state)
    operations = Operations(app_state)
    started, release = threading.Event(), threading.Event()
    original = nodes.compute_node
    def compute(*args, **kwargs):
        started.set()
        assert release.wait(3)
        return original(*args, **kwargs)
    monkeypatch.setattr(nodes, 'compute_node', compute)
    try:
        future = operations.evaluate_nodes()
        assert started.wait(2)
        # Manual plot interactions remain available while the transform is blocked.
        app_state.set_grid(2, 2)
        if change == 'parameter':
            first.params['k'] = '8'
        elif change == 'source':
            run.set_time_origin(10)
        elif change == 'cancel':
            future.cancel()
        else:
            operations.clear_session()
        release.set()
        if change == 'cancel':
            deadline = time.monotonic() + 3
            while operations.jobs and time.monotonic() < deadline:
                operations.poll()
                time.sleep(.001)
            assert not operations.jobs
        else:
            with pytest.raises(ViewerError) as error:
                finish(operations, future)
            assert error.value.code == ('session_replaced' if change == 'session' else 'inputs_changed')
        assert first.out_y is None
        assert second.out_y is None
        assert not any(run.derived for run in app_state.registry.runs)
    finally:
        release.set()
        operations.close()
