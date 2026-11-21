"""Regression coverage for cancellation publication and discovered handles."""

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


def test_discovered_handles_work(control_session):
    import numpy as np

    from ultrazohm_dataviewer import NodeHandle, RunHandle, ViewHandle

    state, client, workers, pump = control_session
    state.registry.add_run("manual", "", np.arange(3.0), {"y": np.arange(3.0)}, {})

    def script():
        run = client.list_runs()[0]["handle"]
        assert isinstance(run, RunHandle)
        client.add_signal(1, run, "y")
        client.node_source(run, "y")
        assert isinstance(client.list_nodes()[0]["handle"], NodeHandle)
        view = client.create_view()
        assert isinstance(client.list_views()[-1]["handle"], ViewHandle)
        client.close_view(view)

    future = workers.submit(script)
    pump(future.done)
    future.result()


def test_client_registry_contract():
    import inspect

    from ultrazohm_dataviewer.cli import parameter_kind
    from ultrazohm_dataviewer.client_methods import ViewerMethods
    from ultrazohm_dataviewer.commands import CommandRegistry

    registry = CommandRegistry()
    types = {"plot": "int", "run": "RunHandle", "node": "NodeHandle", "fwindow": "str"}
    for name, method in inspect.getmembers(ViewerMethods, inspect.isfunction):
        command = registry.get(name)
        assert command is not None, name
        params = [
            p
            for p in inspect.signature(method).parameters.values()
            if p.name not in ("self", "view")
        ]
        assert [p.name for p in params] == [p.name for p in command.params], name
        for actual, expected in zip(params, command.params, strict=False):
            assert parameter_kind(actual) == types.get(expected.kind, expected.kind), (
                name,
                actual.name,
            )
            assert (
                actual.default is not inspect.Parameter.empty
            ) == expected.optional, (name, actual.name)
        accepts_view = "view" in inspect.signature(method).parameters
        assert accepts_view == (
            any(p.kind == "plot" for p in command.params) or name == "set_max_points"
        ), name


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
