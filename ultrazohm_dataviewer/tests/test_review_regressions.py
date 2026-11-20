import threading
import time

import pytest

from ultrazohm_dataviewer.loader import numeric_columns
from ultrazohm_dataviewer.requests import Requests
from ultrazohm_dataviewer.user_paths import publish_new


def test_first_timestamp_column_cannot_be_filtered_out():
    with pytest.raises(ValueError, match="timestamp"):
        numeric_columns([("timestamp", False), ("current", True), ("voltage", True)])


def test_continuous_display_publishes_before_producer_stops():
    requests = Requests()
    started, release, release_next = (threading.Event() for _ in range(3))

    def compute(cancel):
        started.set()
        release.wait(2)
        return "first"

    try:
        requests.request("plot", 1, "recording", compute, continuous=True)
        assert started.wait(2)
        requests.request(
            "plot", 2, "recording", lambda cancel: release_next.wait(2), continuous=True
        )
        release.set()
        deadline = time.monotonic() + 2
        while not requests.results and time.monotonic() < deadline:
            time.sleep(0.005)
        assert requests.results["plot"] == (1, "recording", "first")
    finally:
        release.set()
        release_next.set()
        requests.close()


def test_exclusive_publication_fallback_preserves_existing_file(tmp_path, monkeypatch):
    source, target = tmp_path / "temporary", tmp_path / "complete"
    source.write_text("new")
    target.write_text("existing")
    monkeypatch.setattr(
        "os.link", lambda *args: (_ for _ in ()).throw(OSError("unsupported"))
    )
    with pytest.raises(FileExistsError):
        publish_new(source, target)
    assert target.read_text() == "existing"
    target.unlink()
    publish_new(source, target)
    assert target.read_text() == "new"


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


def test_gui_file_validation_is_background_but_raw_validation_is_strict(
    tmp_path, monkeypatch
):
    from ultrazohm_dataviewer.sources import FileIdentity, validation_error

    path = tmp_path / "recording"
    path.write_text("original")
    identity = FileIdentity.capture(path)
    jobs = Requests()
    entered, release = threading.Event(), threading.Event()
    original = FileIdentity._validate

    def slow_validate(self):
        entered.set()
        assert release.wait(2)
        original(self)

    monkeypatch.setattr(FileIdentity, "_validate", slow_validate)
    try:
        assert validation_error([identity], jobs) is None
        assert entered.wait(2)
        path.write_text("changed recording")
        release.set()
        deadline = time.monotonic() + 2
        while not jobs.results and time.monotonic() < deadline:
            time.sleep(0.005)
        assert "Source changed" in validation_error([identity], jobs)
        with pytest.raises(ValueError, match="Source changed"):
            identity.validate()
    finally:
        release.set()
        jobs.close()


@pytest.mark.parametrize("forget", [False, True])
def test_continuous_display_discards_canceled_identity(forget):
    jobs = Requests()
    entered, release, next_entered, next_release = (threading.Event() for _ in range(4))

    def old(cancel):
        entered.set()
        assert release.wait(2)
        return "obsolete"

    def new(cancel):
        next_entered.set()
        assert next_release.wait(2)
        return "current"

    try:
        jobs.request("plot", 1, "old", old, continuous=True)
        assert entered.wait(2)
        if forget:
            jobs.forget("plot")
        jobs.request("plot", 2, "new", new, continuous=True)
        release.set()
        assert next_entered.wait(2)
        assert not jobs.results
    finally:
        release.set()
        next_release.set()
        jobs.close()


def test_publication_race_has_exactly_one_winner(tmp_path, monkeypatch):
    import os
    from concurrent.futures import ThreadPoolExecutor

    source_a, source_b, target = (tmp_path / name for name in ("a", "b", "target"))
    source_a.write_text("a")
    source_b.write_text("b")
    monkeypatch.setattr(
        os, "link", lambda *args: (_ for _ in ()).throw(OSError("unsupported"))
    )
    # Expose the former check-then-rename race deterministically. Exclusive OS
    # publication needs no check and never enters this replacing rename on POSIX.
    rename = os.rename
    barrier = threading.Barrier(2)

    def racing_rename(source, destination):
        barrier.wait(timeout=2)
        rename(source, destination)

    monkeypatch.setattr(os, "rename", racing_rename)

    def publish(source):
        try:
            publish_new(source, target)
            return source.name
        except FileExistsError:
            return None

    with ThreadPoolExecutor(max_workers=2) as executor:
        winners = list(executor.map(publish, [source_a, source_b]))
    winners = [winner for winner in winners if winner is not None]
    assert len(winners) == 1
    assert target.read_text() == winners[0]


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
