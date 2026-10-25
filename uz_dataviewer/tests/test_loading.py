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
    from pathlib import Path
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
