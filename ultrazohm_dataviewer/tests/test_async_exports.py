import threading
import time

import numpy as np
import pytest

from ultrazohm_dataviewer import session
from ultrazohm_dataviewer.state import AppState


@pytest.mark.parametrize("command", ["export_data", "hist_export", "fft_export"])
def test_queued_export_keeps_window_when_unlinked_plot_moves(
    app_state, tmp_path, command
):
    state = app_state
    state.async_exports = True
    state.link_x = False
    t = np.arange(100.0) / 10
    run = state.registry.add_run("run", "", t, {"a": t.copy()}, {})
    state.cells[0].add((run.id, "a"))
    state.cells[0].x_lim = state.plot_x_ranges[1] = (2.0, 4.0)
    state.fft.sources = state.histogram.sources = [(run.id, "a")]
    state.fft.follow_plot = state.histogram.follow_plot = 1
    # An ongoing file load can keep the shared IO executor busy after Export.
    entered, release = threading.Event(), threading.Event()

    def load(cancel):
        entered.set()
        assert release.wait(5)

    state.services.executor.submit(load)
    assert entered.wait(2)
    target = tmp_path / "queued.csv"
    expected = tmp_path / "expected.csv"
    handler = {
        "export_data": lambda path: session.export_data(state, 0, str(path)),
        "hist_export": lambda path: session.export_histogram(state, str(path)),
        "fft_export": lambda path: session.export_fft(state, str(path)),
    }[command]
    handler(expected)
    try:
        args = [1, str(target)] if command == "export_data" else [str(target)]
        state.commands.execute(state, command, args)
        state.cells[0].x_lim = state.plot_x_ranges[1] = (6.0, 8.0)
        release.set()
        state.services.exports[0][0].result(timeout=5)
        assert target.read_bytes() == expected.read_bytes()
    finally:
        release.set()


def test_export_captures_settings_and_does_not_block_controls(tmp_path, monkeypatch):
    state = AppState()
    state.async_exports = True
    entered, release = threading.Event(), threading.Event()
    original = session._write_csv

    def blocked(*args):
        entered.set()
        assert release.wait(5)
        return original(*args)

    monkeypatch.setattr(session, "_write_csv", blocked)
    try:
        run = state.registry.add_run(
            "run", "", np.arange(3.0), {"a": np.arange(3.0)}, {}
        )
        state.cells[0].add((run.id, "a"))
        target = tmp_path / "export.csv"
        assert (
            state.commands.execute(state, "export_data", [1, str(target)])
            == "Export started"
        )
        assert entered.wait(2)
        state.cells[0].signals.clear()
        state.registry.remove_run(run.id)
        assert not target.exists()
        release.set()
        deadline = time.monotonic() + 5
        while state.services.exports:
            state.poll_pending_loads()
            assert time.monotonic() < deadline
            time.sleep(0.01)
        assert "a" in target.read_text().splitlines()[0]
        assert len(target.read_text().splitlines()) == 4
    finally:
        release.set()
        state.shutdown()


def test_python_waits_for_export_before_loading_existing_file(
    control_session, tmp_path, monkeypatch
):
    state, client, workers, pump = control_session
    state.loading_mode = "memory"
    entered, release = threading.Event(), threading.Event()
    original = session._write_csv

    def blocked(*args):
        entered.set()
        assert release.wait(5)
        return original(*args)

    monkeypatch.setattr(session, "_write_csv", blocked)
    run = state.registry.add_run(
        "new", "", np.arange(3.0), {"a": np.array([10.0, 20.0, 30.0])}, {}
    )
    state.cells[0].add((run.id, "a"))
    target = tmp_path / "export.csv"
    target.write_text("time,a\n0,-1\n1,-2\n2,-3\n")

    def script():
        client.export_data(1, target)
        client.load(target)

    future = workers.submit(script)
    try:
        pump(entered.is_set)
        assert len(state.registry.runs) == 1
        assert not future.done()
        release.set()
        pump(future.done)
        future.result()
        np.testing.assert_array_equal(
            state.registry.runs[-1].signals["a"].y, [10, 20, 30]
        )
    finally:
        release.set()


def test_python_aborts_after_failed_export(control_session, tmp_path, monkeypatch):
    from ultrazohm_dataviewer import ViewerError

    state, client, workers, pump = control_session

    def fail(*args):
        raise OSError("disk full")

    monkeypatch.setattr(session, "_write_csv", fail)
    run = state.registry.add_run("new", "", np.arange(3.0), {"a": np.arange(3.0)}, {})
    state.cells[0].add((run.id, "a"))
    target = tmp_path / "old.csv"
    target.write_text("time,a\n0,-1\n1,-2\n")

    def script():
        client.export_data(1, target)
        client.load(target)

    future = workers.submit(script)
    pump(future.done)
    with pytest.raises(ViewerError, match="disk full"):
        future.result()
    assert len(state.registry.runs) == 1
    assert "-1" in target.read_text()
