"""Live controller lifecycle: Stop priority, flash and shutdown ordering."""

import threading

import pytest


def test_stop_bypasses_read_and_invalidates_queued_enable():
    from ultrazohm_dataviewer.app import DataViewerApp

    app = DataViewerApp(use_live=True)
    entered, release, stopped = (threading.Event() for _ in range(3))

    class Client:
        def __init__(self, endpoint):
            pass

        def status(self):
            entered.set()
            assert release.wait(5)

        def stop(self):
            stopped.set()

    reader = threading.Thread(target=Client("test").status)
    try:
        app.live.available = True
        controller = app.live.controller
        controller.endpoint = "test"
        controller.client_factory = Client
        reader.start()
        assert entered.wait(2)
        controller.commands.put((controller._command_generation, "enable_system", {}))
        app.live.send("stop")
        assert stopped.wait(2)
        assert controller.commands.empty()
    finally:
        release.set()
        reader.join(timeout=2)
        app._shutdown()


@pytest.mark.parametrize("shutdown_fails", [False, True])
def test_next_flash_waits_for_pending_shutdown(shutdown_fails):
    from live_support import wait_for

    from ultrazohm_dataviewer.live import LiveController

    entered, release, finish_first, started_second = (
        threading.Event() for _ in range(4)
    )

    class Client:
        def __init__(self, endpoint):
            self.endpoint = endpoint

        def shutdown(self):
            entered.set()
            assert release.wait(5)
            if shutdown_fails:
                raise RuntimeError("Shutdown rejected")

        def status(self):
            return {"firmware_available": True, "device_target": "localhost:1"}

        def firmware(self, *args, **kwargs):
            if self.endpoint == "second":
                started_second.set()
            return {"id": 1}

        def job(self, *args):
            finished = self.endpoint == "first" and finish_first.is_set()
            return {
                "log": "",
                "next_offset": 0,
                "job": {
                    "phase": "build",
                    "state": "succeeded" if finished else "running",
                },
            }

    controller = LiveController(client_factory=Client)
    controller._poll = lambda: None

    def flash(endpoint):
        controller.submit(
            "flash", endpoint=endpoint, output="unused", ip="localhost", port=1
        )

    try:
        flash("first")
        wait_for(lambda: controller.attached)
        controller.submit("shutdown", endpoint="first")
        assert entered.wait(2)
        finish_first.set()
        wait_for(lambda: not controller.flashing)
        with pytest.raises(RuntimeError, match="pending Stop or shutdown"):
            flash("second")
        assert not started_second.is_set()
        release.set()
        wait_for(lambda: controller._pending_controls == 0)
        flash("second")
        assert started_second.wait(2)
        assert controller.endpoint == "second"
        assert controller.attached
        assert controller.flashing
        assert not controller._flash_shutdown.is_set()
    finally:
        release.set()
        controller.stop_event.set()
        for thread in (
            controller.thread,
            controller.control_thread,
            controller.poll_thread,
        ):
            if thread is not None:
                thread.join(2)
                assert not thread.is_alive()


def test_shutdown_keeps_next_output_separate_from_service_output(tmp_path, monkeypatch):
    from dataclasses import replace
    from pathlib import Path

    from ultrazohm_dataviewer.live import LiveController
    from ultrazohm_dataviewer.panels.live import LiveWorkspace

    controller = LiveController()
    workspace = LiveWorkspace(controller)
    old = tmp_path / "old-run"
    old.mkdir()
    workspace.output = str(old)
    controller.update = replace(
        controller.update, attached=True, status={"output": str(old)}
    )
    workspace.update = controller.update
    monkeypatch.setattr(controller, "submit", lambda *args, **kwargs: None)
    try:
        workspace.send("shutdown")
        next_output = workspace.output
        assert next_output != str(old)
        workspace.pump()  # The service is still reporting its old directory.
        assert workspace.output == next_output
        controller.update = replace(
            controller.update, attached=False, status={}, revision=1
        )
        workspace.pump()
        assert workspace.output == next_output
        assert not Path(next_output).exists()
        # Attaching to a remote service must not change local startup preferences.
        controller.update = replace(
            controller.update,
            attached=True,
            status={"output": "/remote/session"},
            revision=2,
        )
        workspace.pump()
        assert workspace.output == next_output
    finally:
        workspace.close()


def test_old_poll_cannot_replace_new_service_catalog():
    from ultrazohm_dataviewer.live import LiveController

    entered, release = threading.Event(), threading.Event()

    class Client:
        def __init__(self, endpoint):
            self.endpoint = endpoint

        def status(self):
            return {"session_id": self.endpoint, "state": {"connected": False}}

        def observables(self):
            return {"channels": []}

        def catalog(self):
            if self.endpoint == "old":
                entered.set()
                assert release.wait(5)
            return {"profile": {"service": self.endpoint}}

    controller = LiveController(client_factory=Client)
    controller._make_client("old")
    controller.attached = True
    poll = threading.Thread(target=controller._poll)
    poll.start()
    try:
        assert entered.wait(2)
        controller._command("attach", {"endpoint": "new"})
        assert controller._catalog == {"service": "new"}
        release.set()
        poll.join(2)
        assert not poll.is_alive()
        assert controller._catalog == {"service": "new"}
        controller._status_at = 0
        controller._poll()
        assert controller._catalog == {"service": "new"}
        assert controller._status["session_id"] == "new"
    finally:
        release.set()
        poll.join(2)
        controller.stop_event.set()


@pytest.mark.parametrize("cancel", ["stop", "shutdown", "cancel_pending"])
def test_canceling_queued_flash_releases_busy_state(monkeypatch, cancel):
    from live_support import wait_for

    from ultrazohm_dataviewer.live import LiveController

    release, executed = threading.Event(), threading.Event()

    class Client:
        def __init__(self, endpoint):
            pass

        def stop(self):
            pass

        def shutdown(self):
            pass

    controller = LiveController(client_factory=Client)
    controller.endpoint = "test"
    controller.attached = True
    original_work = controller._work

    def delayed_work():
        assert release.wait(5)
        original_work()

    calls = []

    def command(operation, kwargs, **options):
        calls.append(operation)
        executed.set()

    monkeypatch.setattr(controller, "_work", delayed_work)
    monkeypatch.setattr(controller, "_command", command)
    monkeypatch.setattr(controller, "_poll", lambda: None)
    try:
        controller.submit("flash", endpoint="test")
        if cancel == "cancel_pending":
            controller.cancel_pending_commands()  # GUI Stop takes this path.
        else:
            controller.submit(cancel)
        wait_for(lambda: controller._pending_controls == 0)
        assert controller.commands.empty()
        assert not controller.flashing
        assert not calls
        controller.submit("flash", endpoint="test")
        release.set()
        assert executed.wait(2)
        wait_for(lambda: not controller.flashing)
        assert calls == ["flash"]
    finally:
        release.set()
        controller.stop_event.set()
        for thread in (
            controller.thread,
            controller.control_thread,
            controller.poll_thread,
        ):
            if thread is not None:
                thread.join(2)
                assert not thread.is_alive()


def test_stop_reaches_service_during_running_flash_and_busy_script():
    """GUI Stop and a script's Stop are delivered while Flash UZ follows its job."""
    from unittest.mock import Mock

    from live_support import wait_for

    from ultrazohm_dataviewer.live import LiveController

    release = threading.Event()
    polled = threading.Event()
    client = Mock()
    client.status.return_value = {
        "firmware_available": True,
        "state": {"device": "127.0.0.1:1000"},
    }
    client.firmware.return_value = {"id": "job"}

    def job(job_id, offset):
        polled.set()
        state = "succeeded" if release.is_set() else "running"
        return {
            "log": "",
            "next_offset": offset,
            "job": {"state": state, "phase": "programming", "result": None},
        }

    client.job.side_effect = job
    controller = LiveController(lambda _: client)
    try:
        controller.submit(
            "flash",
            endpoint="127.0.0.1:19740",
            ip="127.0.0.1",
            port=1000,
            output="unused",
        )
        assert polled.wait(5)
        assert controller.flashing
        controller.submit("stop")  # GUI button: bypasses the flash monitor
        script = threading.Thread(target=controller.send_stop)  # script runner
        script.start()
        script.join(5)
        assert not script.is_alive(), "script Stop waited for the flash job"
        wait_for(lambda: client.stop.call_count == 2)
        assert controller.flashing, "Stops must not wait for the flash to finish"
        release.set()
        wait_for(lambda: not controller.flashing)
    finally:
        release.set()
        controller.close()


def _attached_controller(client):
    from ultrazohm_dataviewer.live import LiveController

    controller = LiveController(lambda endpoint: client)
    controller.endpoint = "127.0.0.1:19740"
    controller.client = client
    controller.attached = True
    return controller


def test_gui_stop_without_flash_uses_the_control_path():
    from unittest.mock import Mock

    from live_support import wait_for

    client = Mock()
    controller = _attached_controller(client)
    try:
        controller.submit("stop")
        wait_for(lambda: client.stop.called)
        wait_for(lambda: controller.latest().completed_commands == 1)
        # Never queued on the command worker.
        assert controller.thread is None
        assert controller.control_thread is not None
        assert "stop: request sent" in controller.latest().notice
        assert not controller.latest().error
    finally:
        controller.close()


def test_shutdown_releases_the_attachment():
    from unittest.mock import Mock

    from live_support import wait_for

    client = Mock()
    client.shutdown.return_value = {"service_id": "external-service"}
    controller = _attached_controller(client)
    try:
        controller.submit("shutdown")
        wait_for(lambda: not controller.latest().attached)
        wait_for(lambda: "finalization continues" in controller.latest().notice)
        client.shutdown.assert_called_once_with()
    finally:
        controller.close()


@pytest.mark.parametrize("operation", ["stop", "shutdown"])
def test_lifecycle_request_without_attachment_reports_an_error(operation):
    from unittest.mock import Mock

    from live_support import wait_for

    from ultrazohm_dataviewer.live import LiveController

    client = Mock()
    controller = LiveController(lambda endpoint: client)
    controller.endpoint = "127.0.0.1:19740"
    try:
        controller.submit(operation)
        wait_for(lambda: "Attach to a service first" in controller.latest().error)
        getattr(client, operation).assert_not_called()
    finally:
        controller.close()
