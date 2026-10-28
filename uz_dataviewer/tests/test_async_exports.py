import threading
import time
import numpy as np
from uz_dataviewer.state import AppState
from uz_dataviewer import session


def test_export_captures_settings_and_does_not_block_controls(tmp_path, monkeypatch):
    state = AppState()
    state.async_exports = True
    entered, release = threading.Event(), threading.Event()
    original = session._write_csv
    def blocked(*args):
        entered.set()
        assert release.wait(5)
        return original(*args)
    monkeypatch.setattr(session, '_write_csv', blocked)
    try:
        run = state.registry.add_run('run', '', np.arange(3.), {'a': np.arange(3.)}, {})
        state.cells[0].add((run.id, 'a'))
        target = tmp_path/'export.csv'
        assert state.commands.execute(state, 'export_data', [1, str(target)]) == 'Export started'
        assert entered.wait(2)
        state.cells[0].signals.clear()
        state.registry.remove_run(run.id)
        assert not target.exists()
        release.set()
        deadline = time.monotonic()+5
        while state.services.exports:
            state.poll_pending_loads()
            assert time.monotonic()<deadline
            time.sleep(.01)
        assert 'a' in target.read_text().splitlines()[0]
        assert len(target.read_text().splitlines()) == 4
    finally:
        release.set()
        state.shutdown()


def test_script_waits_for_export_before_loading_existing_file(tmp_path, monkeypatch):
    from uz_dataviewer import exports
    state = AppState()
    state.async_exports = True
    state.loading_mode = 'memory'
    entered, release = threading.Event(), threading.Event()
    original = session._write_csv
    def blocked(*args):
        entered.set()
        assert release.wait(5)
        return original(*args)
    monkeypatch.setattr(session, '_write_csv', blocked)
    try:
        run = state.registry.add_run('new', '', np.arange(3.), {'a': np.array([10., 20., 30.])}, {})
        state.cells[0].add((run.id, 'a'))
        target = tmp_path / 'export.csv'
        target.write_text('time,a\n0,-1\n1,-2\n2,-3\n')
        script = tmp_path / 'test.uzscript'
        import json
        script.write_text(f'export_data(plot_1, {json.dumps(str(target))})\nload({json.dumps(str(target))})\n')
        assert session.run_script(state, str(script)) is None
        exports.poll(state)
        assert entered.wait(2)
        exports.poll(state)
        assert len(state.registry.runs) == 1
        release.set()
        deadline = time.monotonic() + 5
        while state.services.replay is not None:
            exports.poll(state)
            assert time.monotonic() < deadline
            time.sleep(.01)
        np.testing.assert_array_equal(state.registry.runs[-1].signals['a'].y, [10, 20, 30])
    finally:
        release.set()
        state.shutdown()


def test_script_aborts_after_failed_export(tmp_path, monkeypatch):
    from uz_dataviewer import exports
    state = AppState()
    state.async_exports = True
    def fail(*args):
        raise OSError('disk full')
    monkeypatch.setattr(session, '_write_csv', fail)
    try:
        run = state.registry.add_run('new', '', np.arange(3.), {'a': np.arange(3.)}, {})
        state.cells[0].add((run.id, 'a'))
        target = tmp_path / 'old.csv'
        target.write_text('time,a\n0,-1\n1,-2\n')
        script = tmp_path / 'test.uzscript'
        import json
        script.write_text(f'export_data(plot_1, {json.dumps(str(target))})\nload({json.dumps(str(target))})\n')
        session.run_script(state, str(script))
        deadline = time.monotonic() + 5
        while state.services.replay is not None:
            exports.poll(state)
            assert time.monotonic() < deadline
            time.sleep(.01)
        assert len(state.registry.runs) == 1
        assert '-1' in target.read_text()
    finally:
        state.shutdown()
