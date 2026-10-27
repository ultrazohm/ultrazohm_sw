"""Loading worker lifecycle and cancellation."""

import threading
import time

import pytest

from uz_dataviewer.workers import CancellableExecutor
from uz_dataviewer.sources import Cancelled, check
from uz_dataviewer.state import AppState


def test_load_shutdown_cancels_active_and_queued_work():
    worker = CancellableExecutor()
    started = threading.Event()
    stopped = threading.Event()
    def work(cancel):
        started.set()
        try:
            while True:
                check(cancel)
                time.sleep(.005)
        finally:
            stopped.set()
    active = worker.submit(work)
    assert started.wait(2)
    queued = worker.submit(work)
    worker.shutdown()
    assert stopped.wait(2)
    with pytest.raises(Cancelled):
        active.result()
    assert queued.cancelled()
    assert worker.thread.daemon


def _slow_native_conversion(source, destination, backend, connection):
    from pathlib import Path
    Path(destination).write_bytes(b'partial')
    time.sleep(30)


def test_cancel_conversion_stops_process_and_removes_temporary_file(tmp_path, monkeypatch):
    import uz_dataviewer.loading as loading
    monkeypatch.setattr(loading, '_convert_worker', _slow_native_conversion)
    monkeypatch.setattr('uz_dataviewer.state.LARGE_CSV_BYTES', 1)
    state = AppState()
    path = tmp_path / 'input.csv'
    path.write_text('time;a\n0;1\n1;2\n')
    try:
        state.request_load(str(path))
        state.resolve_large_csv('convert')
        future = state.services.pending[0][0]
        deadline = time.monotonic()+10
        while time.monotonic() < deadline:
            files = list(tmp_path.glob('.uz-convert-*'))
            if files and files[0].stat().st_size:
                break
            time.sleep(.01)
        else:
            pytest.fail('Conversion process did not start')
        state.shutdown()
        with pytest.raises(Cancelled):
            future.result(timeout=5)
        assert not list(tmp_path.glob('.uz-convert-*'))
        assert not path.with_suffix('.parquet').exists()
    finally:
        state.shutdown()


def _large_conversion_error(source, destination, backend, connection):
    connection.send((False, 'large error ' + 'x' * 1_000_000))
    connection.close()


def test_conversion_drains_large_error_before_worker_exits(monkeypatch):
    import uz_dataviewer.loading as loading
    monkeypatch.setattr(loading, '_convert_worker', _large_conversion_error)
    cancel = threading.Event()
    watchdog = threading.Timer(10, cancel.set)
    watchdog.start()
    try:
        with pytest.raises(ValueError, match='large error'):
            loading.convert_cancellable('unused', 'unused', 'pyarrow', cancel)
        assert not cancel.is_set()
    finally:
        watchdog.cancel()


def test_async_load_echo_preserves_captured_settings(states, tmp_path):
    from uz_dataviewer.state import LoadRequest

    state, replay = states(), states()
    path = tmp_path / "recording.csv"
    path.write_text("time,a\n0,10\n1,20\n")
    state.backend = replay.backend = "polars"
    state.loading_mode = replay.loading_mode = "lazy"
    state._submit_load(LoadRequest(str(path), "memory", "pyarrow", False))
    for entry in state.console._entries:
        if entry.level == "CMD":
            replay.commands.dispatch(replay, entry.message)
    run = replay.registry.runs[0]
    assert run.storage_mode == "memory" and run.backend == "pyarrow"
    assert replay.loading_mode == "lazy" and replay.backend == "polars"
