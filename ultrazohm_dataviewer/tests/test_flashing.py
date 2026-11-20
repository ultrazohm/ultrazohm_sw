"""Service-owned firmware jobs and viewer ownership policy, without hardware."""

from types import SimpleNamespace
from unittest.mock import Mock

import pytest
from imgui_bundle import imgui

from ultrazohm_dataviewer import flashing
from ultrazohm_dataviewer.live import LiveController, LiveUpdate
from ultrazohm_dataviewer.panels.live import LiveWorkspace


@pytest.mark.parametrize("success", [True, False])
def test_flash_uses_service_without_local_tools_or_restart(monkeypatch, success):
    client = Mock()
    client.status.return_value = {
        "firmware_available": True,
        "state": {"device": "192.168.1.233:1000"},
    }
    client.firmware.return_value = {"id": "job-1"}
    client.job.return_value = {
        "job": {
            "phase": "complete",
            "state": "succeeded" if success else "failed",
            "result": {"error": "build failed"},
        },
        "log": "",
        "next_offset": 0,
    }
    controller = LiveController(lambda _: client)
    monkeypatch.setattr(flashing, "xsct_available", lambda: False)
    start = Mock(side_effect=AssertionError("must not restart attached service"))
    monkeypatch.setattr(controller, "_start_service", start)
    try:
        if success:
            controller._flash({"endpoint": "127.0.0.1:19740"})
        else:
            with pytest.raises(RuntimeError, match="build failed"):
                controller._flash({"endpoint": "127.0.0.1:19740"})
        client.firmware.assert_called_once_with("flash", device="192.168.1.233:1000")
        client.shutdown.assert_not_called()
        start.assert_not_called()
    finally:
        controller.close()
    client.stop.assert_called_once()
    client.shutdown.assert_not_called()


def test_missing_service_capability_fails_before_submission():
    client = Mock()
    client.status.return_value = {"firmware_available": False}
    controller = LiveController(lambda _: client)
    try:
        with pytest.raises(RuntimeError, match="selected service"):
            controller._flash({"endpoint": "127.0.0.1:19740"})
        client.firmware.assert_not_called()
    finally:
        controller.close()


def test_closing_during_flash_stops_external_service_without_shutdown():
    client = Mock()
    client.status.return_value = {
        "firmware_available": True,
        "state": {"device": "192.168.1.233:1000"},
    }
    client.firmware.return_value = {"id": "job-1"}
    controller = LiveController(lambda _: client)

    def progress(*_):
        controller.stop_event.set()
        return {
            "job": {"phase": "flash", "state": "running"},
            "log": "",
            "next_offset": 0,
        }

    client.job.side_effect = progress
    controller._flash({"endpoint": "127.0.0.1:19740"})
    controller.stop_event.clear()
    controller.close()
    client.stop.assert_called_once()
    client.shutdown.assert_not_called()


@pytest.mark.parametrize("action", ["OK", "Cancel"])
def test_confirmation_only_submits_after_ok(gui_frame, app_state, monkeypatch, action):
    workspace = LiveWorkspace(LiveController())
    workspace.available = True
    workspace.flash_available = True
    workspace.update = LiveUpdate(attached=True, status={"state": {"connected": True}})
    calls = []
    monkeypatch.setattr(
        workspace, "send", lambda op, **kwargs: calls.append((op, kwargs))
    )
    clicked = set()
    original = imgui.button

    def button(label, *args, **kwargs):
        original(label, *args, **kwargs)
        if label in ("Flash UZ", action) and label not in clicked:
            clicked.add(label)
            return True
        return False

    monkeypatch.setattr(imgui, "button", button)
    try:
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
        if action == "OK":
            assert len(calls) == 1 and calls[0][0] == "flash"
        else:
            assert calls == []
        assert workspace.controller.thread is None
    finally:
        workspace.close()


@pytest.mark.parametrize("present", [False, True])
@pytest.mark.parametrize("prepared", [False, True])
def test_xsct_detection_and_disabled_flash_button(
    gui_frame, app_state, monkeypatch, present, prepared
):
    monkeypatch.setattr(
        flashing.shutil, "which", lambda name: "/tools/xsct" if present else None
    )
    assert flashing.xsct_available() is present
    workspace = LiveWorkspace(LiveController())
    workspace.available = True
    workspace.flash_available = present
    if prepared:
        workspace.repo, workspace.mapping = "/prepared", "mapping.json"
    disabled = {}
    original = imgui.button

    def button(label, *args, **kwargs):
        result = original(label, *args, **kwargs)
        if label in ("Flash UZ", "Connect", "Attach"):
            disabled[label] = bool(imgui.get_item_flags() & imgui.ItemFlags_.disabled)
        return result

    monkeypatch.setattr(imgui, "button", button)
    try:
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
        assert disabled == {
            "Connect": not prepared,
            "Flash UZ": not (present and prepared),
        }
    finally:
        workspace.close()


def _coded(code, message):
    error = RuntimeError(message)
    error.code = code
    return error


@pytest.mark.parametrize(
    "error, refused",
    [
        (_coded("connection_refused", "could not reach the service"), True),
        # A coded error is decided by its code, never by its text.
        (_coded("timeout", "connection refused while waiting"), False),
        (_coded("transport", "service closed the connection"), False),
        # Older CLI wheels report refusal only as text.
        (_coded(None, "Connection refused (os error 111)"), True),
        (
            RuntimeError(
                "No connection could be made because the target machine actively refused it"
            ),
            True,
        ),
        (ConnectionRefusedError(111, "Connection refused"), True),
        (RuntimeError("request timed out"), False),
    ],
)
def test_refused_connections_are_recognized_by_code(error, refused):
    assert flashing.connection_refused(error) is refused


def test_disconnected_flash_uses_service_target():
    client = Mock()
    client.status.return_value = {
        "firmware_available": True,
        "state": {"connected": False},
        "device_target": "192.168.55.233:1000",
    }
    client.firmware.return_value = {"id": "job"}
    client.job.return_value = {
        "job": {"state": "succeeded", "phase": "complete"},
        "log": "",
        "next_offset": 0,
    }
    controller = LiveController(lambda _: client)
    controller._flash(
        {"endpoint": "127.0.0.1:19740", "ip": "192.168.1.233", "port": 1000}
    )
    client.firmware.assert_called_once_with("flash", device="192.168.55.233:1000")
    controller.close()


def test_stop_and_shutdown_bypass_flash_monitor():
    from ultrazohm_dataviewer.live import action_block_reason

    client = Mock()
    controller = LiveController(lambda _: client)
    controller.endpoint = "127.0.0.1:19740"
    controller.flashing = True
    for action in ("stop", "shutdown"):
        assert not action_block_reason(action, flashing=True)
        controller.submit(action)
        from live_support import wait_for

        wait_for(lambda action=action: getattr(client, action).call_count == 1)
        getattr(client, action).assert_called_once()
    assert controller.commands.empty()
    controller.close()


@pytest.mark.parametrize("operation", ["stop", "shutdown"])
@pytest.mark.parametrize("fails", [False, True])
def test_flash_control_requests_do_not_block_gui(operation, fails):
    import threading

    from live_support import wait_for

    entered, release = threading.Event(), threading.Event()
    client = Mock()

    def request():
        entered.set()
        assert release.wait(3)
        if fails:
            raise RuntimeError("service unavailable")

    getattr(client, operation).side_effect = request
    controller = LiveController(lambda _: client)
    controller.endpoint = "127.0.0.1:19740"
    controller.flashing = True
    returned = threading.Event()
    caller = threading.Thread(
        target=lambda: (controller.submit(operation), returned.set())
    )
    try:
        caller.start()
        assert entered.wait(1)
        assert returned.wait(0.3), "submit blocked on network IO"
        release.set()
        wait_for(lambda: controller.latest().completed_commands == 1)
        if fails:
            assert "service unavailable" in controller.latest().error
        else:
            assert not controller.latest().error
    finally:
        release.set()
        caller.join(3)
        controller.close()
    assert not controller.control_thread.is_alive()


def test_flash_shutdown_detaches_and_marks_owned_service(monkeypatch):
    from live_support import wait_for

    client = Mock()
    controller = LiveController(lambda _: client)
    controller.endpoint = controller.owned.endpoint = "127.0.0.1:19740"
    controller.attached = controller.flashing = True
    controller._status = {"session_id": "old"}
    monkeypatch.setattr(controller, "_await_shutdown", lambda *a, **kw: True)
    try:
        controller.submit("shutdown")
        wait_for(lambda: controller.latest().completed_commands == 1)
        assert not controller.latest().attached
        assert controller.latest().status == {}
        assert controller.owned.shutdown_requested
        assert controller._flash_shutdown.is_set()
        assert "finalized" in controller.latest().notice
    finally:
        controller.close()
