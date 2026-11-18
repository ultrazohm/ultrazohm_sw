"""Ordinary Python workflows retain sequential operation semantics."""
import pytest
from uz_dataviewer import session, ViewerError


def test_python_can_load_json_and_continue(control_session, tmp_path):
    state, client, workers, pump = control_session
    snapshot = tmp_path / 'state.json'
    state.set_grid(2, 1)
    session.save_state(state, str(snapshot))
    state.set_grid(1, 1)
    def script():
        client.load_session(snapshot)
        client.set_max_points(750)
    future = workers.submit(script)
    pump(future.done)
    future.result()
    assert (state.rows, state.cols) == (2, 1)
    assert state.max_points == 750


@pytest.mark.parametrize('replace', ['clear_session', 'load_session'])
def test_python_continues_after_session_replacement(control_session, tmp_path, replace):
    state, client, workers, pump = control_session
    snapshot = tmp_path / 'state.json'
    session.save_state(state, str(snapshot))
    csv = tmp_path / 'recording.csv'
    csv.write_text('time,y\n0,0\n0.0001,0.1\n')
    def script():
        if replace == 'clear_session':
            client.clear_session()
        else:
            client.load_session(snapshot)
        run = client.load(csv)
        client.set_grid(2, 1)
        client.add_signal(1, run, 'y')
    future = workers.submit(script)
    pump(future.done)
    future.result()
    assert len(state.registry.runs) == 1
    assert state.cell_count == 2
    assert state.cells[0].signals == [(state.registry.runs[0].id, 'y')]


def test_python_aborts_when_a_recording_cannot_load(control_session, tmp_path):
    state, client, workers, pump = control_session
    def script():
        client.load(tmp_path / 'missing.csv')
        client.set_grid(2, 2)
    future = workers.submit(script)
    pump(future.done)
    with pytest.raises(ViewerError):
        future.result()
    assert state.cell_count == 1
