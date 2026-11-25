"""Cancellation never publishes partial results or crashes polling."""

import threading
import time

from ultrazohm_dataviewer.operations import Operations


def test_cancel_during_commit_cannot_crash_poll(app_state):
    operations = Operations(app_state)
    entered, attempted = threading.Event(), threading.Event()
    cancelled = []

    def commit(value):
        entered.set()
        assert attempted.wait(2)
        return value

    future = operations._submit(lambda cancel: 42, commit)

    def disconnect():
        assert entered.wait(2)
        cancelled.append(future.cancel())
        attempted.set()

    thread = threading.Thread(target=disconnect)
    thread.start()
    try:
        deadline = time.monotonic() + 3
        while not future.done() and time.monotonic() < deadline:
            operations.poll()
            time.sleep(0.001)
        assert future.result()["result"] == 42
        assert cancelled == [False]
    finally:
        thread.join(2)
        operations.close()


def test_cancel_restore_skips_remaining_recordings(app_state, tmp_path, monkeypatch):
    from ultrazohm_dataviewer.session import save_state
    from ultrazohm_dataviewer.state import AppState

    path = tmp_path / "input.csv"
    path.write_text("time,y\n0,1\n1,2\n")
    app_state.load_sync(str(path))
    app_state.load_sync(str(path))
    saved = tmp_path / "session.json"
    save_state(app_state, saved)
    operations = Operations(app_state)
    entered, release = threading.Event(), threading.Event()
    calls = []
    original = AppState.load_sync

    def load(state, path, **kwargs):
        calls.append(path)
        entered.set()
        assert release.wait(3)
        return original(state, path, **kwargs)

    monkeypatch.setattr(AppState, "load_sync", load)
    token = app_state.session_token
    try:
        future = operations.load_session(str(saved))
        assert entered.wait(2)
        future.cancel()
        release.set()
        deadline = time.monotonic() + 3
        while operations.jobs and time.monotonic() < deadline:
            operations.poll()
            time.sleep(0.001)
        assert not operations.jobs
        assert len(calls) == 1
        assert app_state.session_token is token
    finally:
        release.set()
        operations.close()


def test_cancel_explicit_analysis_clears_panel_activity(
    app_state, gui_frame, monkeypatch
):
    import numpy as np

    from ultrazohm_dataviewer.analysis import FftRequest
    from ultrazohm_dataviewer.panels.fft import FftPanel

    run = app_state.registry.add_run(
        "x", "", np.arange(1000.0) / 1000, {"y": np.arange(1000.0)}, {}
    )
    app_state.fft.sources = [(run.id, "y")]
    app_state.fft.follow_plot = -1
    app_state.fft.compute_requested = True
    operations = Operations(app_state)
    panel = FftPanel()
    entered, release = threading.Event(), threading.Event()
    original = FftRequest.compute

    def compute(request, cancel=None):
        entered.set()
        assert release.wait(3)
        return original(request, cancel)

    monkeypatch.setattr(FftRequest, "compute", compute)
    try:
        gui_frame(panel, app_state)
        assert entered.wait(2)
        future = operations.dispatch("fft", {}, None)
        future.cancel()
        release.set()
        deadline = time.monotonic() + 3
        while operations.jobs and time.monotonic() < deadline:
            operations.poll()
            gui_frame(panel, app_state)
            time.sleep(0.001)
        assert not operations.jobs
        assert panel._analysis_pending is None
        assert app_state.services.analysis_operations["fft"].done()
        assert not app_state.services.analysis_jobs.pending
    finally:
        release.set()
        operations.close()
