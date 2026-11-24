"""Startup ordering and application-owned status rendering."""

import pytest

from ultrazohm_dataviewer.app import DataViewerApp


@pytest.mark.parametrize("failure", ["bind", "run"])
def test_main_releases_resources_after_startup_failure(monkeypatch, failure):
    from ultrazohm_dataviewer import app

    closed = []

    class Viewer:
        def __init__(self, **kwargs):
            pass

        def enable_control(self, endpoint):
            if failure == "bind":
                raise OSError("address in use")

        def run(self):
            raise RuntimeError("renderer failed")

        def _shutdown(self):
            closed.append(True)

    monkeypatch.setattr(app, "DataViewerApp", Viewer)
    with pytest.raises((OSError, RuntimeError)):
        app.main([])
    assert closed == [True]


def test_session_menu_uses_background_transactional_operations(tmp_path, monkeypatch):
    import threading
    import time
    from types import SimpleNamespace

    from ultrazohm_dataviewer import session

    app = DataViewerApp()
    snapshot = tmp_path / "session.json"
    started, release = threading.Event(), threading.Event()
    stopped = []
    monkeypatch.setattr(app.python_panel, "stop_owned", lambda: stopped.append(True))
    original = session.read_snapshot

    def read(path):
        started.set()
        assert release.wait(3)
        return original(path)

    def choose(operation, path):
        dialog = SimpleNamespace(ready=lambda: True, result=lambda: str(path))
        app._session_dialog = (dialog, operation, False, "")
        app._poll_session_dialog()

    def finish():
        deadline = time.monotonic() + 3
        while app._session_action is not None and time.monotonic() < deadline:
            app.operations.poll()
            app._poll_session_dialog()
            time.sleep(0.001)
        assert app._session_action is None

    try:
        app.state.set_grid(3, 2)
        choose("save_session", snapshot)
        finish()
        assert not stopped
        app.state.set_grid(1, 1)
        token = app.state.session_token
        monkeypatch.setattr(session, "read_snapshot", read)
        choose("load_session", snapshot)
        assert stopped == [True]
        assert started.wait(2)
        assert app.state.session_token is token
        assert app.state.rows == 1
        release.set()
        finish()
        assert app.state.rows == 3
        assert app.state.cols == 2
        token = app.state.session_token
        choose("load_session", tmp_path / "missing.json")
        finish()
        assert app.state.session_token is token
    finally:
        release.set()
        app._shutdown()


@pytest.mark.parametrize(
    "platform,session,expected",
    [
        ("win32", None, True),
        ("linux", "x11", True),
        ("linux", "wayland", False),
        ("linux", None, False),
        ("darwin", None, False),
    ],
)
def test_detached_windows_supported_platforms(monkeypatch, platform, session, expected):
    from imgui_bundle import hello_imgui, immapp

    monkeypatch.setattr(
        "ultrazohm_dataviewer.plugins.load_plugins", lambda **kwargs: None
    )
    captured = []
    monkeypatch.setattr(immapp, "run", lambda params, addons: captured.append(params))
    app = DataViewerApp()
    try:
        monkeypatch.setattr("sys.platform", platform)
        # DISPLAY alone must not enable viewports on Wayland or unknown sessions.
        monkeypatch.setenv("DISPLAY", ":0")
        if session is None:
            monkeypatch.delenv("XDG_SESSION_TYPE", raising=False)
        else:
            monkeypatch.setenv("XDG_SESSION_TYPE", session)
        app.run()
        assert captured[0].imgui_window_params.enable_viewports is expected
        assert (
            captured[0].app_window_params.window_geometry.window_size_state
            == hello_imgui.WindowSizeState.maximized
        )
        assert not captured[0].app_window_params.restore_previous_geometry
    finally:
        app._shutdown()


@pytest.mark.parametrize("use_live", [False, True])
def test_live_panels_are_opt_in(use_live, monkeypatch):
    monkeypatch.setattr(
        "ultrazohm_dataviewer.plugins.load_plugins", lambda **kwargs: None
    )
    app = DataViewerApp(use_live=use_live, live_mapping="cached-mapping.json")
    try:
        windows = app._dockable_windows()
        labels = {window.label for window in windows}
        if use_live:
            assert all(w.is_visible == (w.label != "Python") for w in windows)
        live_labels = {"Live Data", "Live Plots", "Control"}
        assert "Python" in labels
        assert labels & live_labels == (live_labels if use_live else set())
        assert (app.live is not None) == use_live
        if app.live is not None:
            assert app.live.controller.thread is None
            from pathlib import Path

            assert app.live.mapping == str(Path("cached-mapping.json").resolve())
            assert app.live.mapping_is_explicit
    finally:
        app._shutdown()


def test_startup_recording_precedes_script(tmp_path, monkeypatch):
    monkeypatch.setattr(
        "ultrazohm_dataviewer.plugins.load_plugins", lambda **kwargs: None
    )
    recording = tmp_path / "log.csv"
    recording.write_text("time;a\n0;1\n1;2\n")
    script = tmp_path / "setup.py"
    script.write_text(
        'from ultrazohm_dataviewer import Client, RunHandle\nv = Client()\nv.status()\nv.add_signal(1, RunHandle(v.session, 1), "a")\n'
    )
    app = DataViewerApp(
        [str(recording), str(script)], backend="pyarrow", loading_mode="memory"
    )
    try:
        _finish_startup(app)
        assert app.state.cells[0].signals == [(1, "a")]
        assert not app.state.is_loading
    finally:
        app._shutdown()


def test_startup_failure_is_reported_and_stops_following_scripts(tmp_path, monkeypatch):
    monkeypatch.setattr(
        "ultrazohm_dataviewer.plugins.load_plugins", lambda **kwargs: None
    )
    first = tmp_path / "bad.py"
    first.write_text('raise RuntimeError("stop here")\n')
    second = tmp_path / "next.py"
    second.write_text(
        "from ultrazohm_dataviewer import Client\nClient().set_grid(2, 2)\n"
    )
    app = DataViewerApp([str(first), str(second)])
    try:
        _finish_startup(app)
        assert app.state.cell_count == 1
        assert "Startup stopped" in app.state.console.as_text()
        assert app.state.services.executor.thread is None
    finally:
        app._shutdown()


def test_status_owns_fps_even_after_framework_toggle(monkeypatch, gui_frame):
    from imgui_bundle import immapp

    monkeypatch.setattr(
        "ultrazohm_dataviewer.plugins.load_plugins", lambda **kwargs: None
    )
    captured = []
    monkeypatch.setattr(immapp, "run", lambda params, addons: captured.append(params))
    app = DataViewerApp()
    try:
        app.run()
        params = captured[0]
        assert not params.imgui_window_params.remember_status_bar_settings
        params.imgui_window_params.show_status_fps = True

        class Status:
            def render(self, state):
                app._show_status()

        gui_frame(Status(), app.state)
        assert not params.imgui_window_params.show_status_fps
    finally:
        app._shutdown()


def test_open_mode_menu_uses_real_imgui_binding(monkeypatch, gui_frame):
    from types import SimpleNamespace

    from imgui_bundle import imgui

    app = DataViewerApp()
    try:
        # Exercise actual menu_item bindings, including the Analysis item that
        # previously raised TypeError only after opening the Mode menu.
        monkeypatch.setattr(imgui, "begin_menu", lambda label: label == "Mode")
        monkeypatch.setattr(imgui, "end_menu", lambda: None)
        gui_frame(SimpleNamespace(render=lambda state: app._show_menus()), app.state)
    finally:
        app._shutdown()


def test_selected_workspace_owns_user_data(tmp_path, monkeypatch):
    from ultrazohm_dataviewer.live import new_output_directory
    from ultrazohm_dataviewer.user_paths import HEADER

    monkeypatch.delenv("UZ_DATAVIEWER_CACHE", raising=False)
    header = tmp_path / "workspace" / HEADER
    header.parent.mkdir(parents=True)
    header.touch()
    mapping = tmp_path / "workspace" / "artifacts" / "_user" / "mapping.json"
    monkeypatch.setattr(
        "ultrazohm_dataviewer.plugins.load_plugins", lambda **kwargs: None
    )
    app = DataViewerApp(use_live=True, live_mapping=str(mapping))
    try:
        assert app.live.repo == str(tmp_path / "workspace")
        assert app.artifacts == tmp_path / "workspace" / "artifacts" / "_user"
        assert app.state.cache_dir == str(app.artifacts / "viewer_cache")
        assert app.live.output.startswith(str(app.artifacts / "logs"))
        assert new_output_directory(app.live.repo).startswith(
            str(app.artifacts / "logs")
        )
    finally:
        app._shutdown()


def test_mode_only_focuses_targets_and_preserves_other_windows(monkeypatch):
    from types import SimpleNamespace

    monkeypatch.setattr(
        "ultrazohm_dataviewer.plugins.load_plugins", lambda **kwargs: None
    )
    app = DataViewerApp(use_live=True)
    try:
        app.live.available = True
        windows = app._dockable_windows()
        focused = []
        app._runner_params = SimpleNamespace(
            docking_params=SimpleNamespace(
                dockable_windows=windows, focus_dockable_window=focused.append
            )
        )
        app._apply_window_mode(True)
        assert focused == ["Live Data", "Control", "Live Plots"]
        assert all(
            w.is_visible
            for w in windows
            if w.label not in {"Python", "Application log"}
        )
        # User choices outside the selected group survive subsequent switches.
        next(w for w in windows if w.label == "FFT").is_visible = False
        app._apply_window_mode(False)
        assert focused[-3:] == ["Navigation", "Log Browser", "Plots"]
        assert all(
            w.is_visible
            for w in windows
            if w.label in {"Live Data", "Control", "Live Plots"}
        )
        assert not next(w for w in windows if w.label == "FFT").is_visible
    finally:
        app._shutdown()


@pytest.mark.parametrize("frozen", [False, True])
@pytest.mark.parametrize("via_mapping", [False, True])
def test_log_browser_uses_selected_workspace(
    tmp_path, monkeypatch, frozen, via_mapping
):
    import sys
    from pathlib import Path

    from ultrazohm_dataviewer.user_paths import HEADER

    workspace = tmp_path / "selected"
    header = workspace / HEADER
    header.parent.mkdir(parents=True)
    header.touch()
    log = workspace / "artifacts" / "_user" / "logs" / "run.csv"
    log.parent.mkdir(parents=True)
    log.touch()
    elsewhere = tmp_path / "elsewhere"
    elsewhere.mkdir()
    monkeypatch.chdir(elsewhere)
    monkeypatch.setattr(sys, "frozen", frozen, raising=False)
    monkeypatch.setattr(
        "ultrazohm_dataviewer.plugins.load_plugins", lambda **kwargs: None
    )
    kwargs = (
        {"live_mapping": str(workspace / "artifacts" / "mapping.json")}
        if via_mapping
        else {"live_repo": str(workspace)}
    )
    app = DataViewerApp(**kwargs)
    try:
        assert app.log_browser.directory == workspace / "artifacts"
        app.log_browser.refresh()
        files, errors = app.log_browser._future.result(timeout=5)
        assert files == [Path("_user/logs/run.csv")]
        assert not errors
    finally:
        app._shutdown()


def _finish_startup(app, on_frame=None):
    import time

    app.enable_control("127.0.0.1:0")
    deadline = time.monotonic() + 10
    while (
        app._startup_scripts or app._startup_script or app._startup_pending is not None
    ):
        app.python_panel.poll()
        app.operations.poll()
        app.state.poll_pending_loads()
        app.control_server.poll(app.operations.dispatch)
        app._poll_startup()
        if on_frame is not None:
            on_frame()
        assert time.monotonic() < deadline
        time.sleep(0.001)


@pytest.mark.parametrize("after_script", [False, True])
@pytest.mark.parametrize("outcome", ["success", "invalid", "cancel"])
def test_startup_axis_choice_waits_for_success(tmp_path, after_script, outcome):
    recording = tmp_path / "custom.csv"
    recording.write_text(
        "seconds,value\n0,1\n1,2\n"
        if outcome != "invalid"
        else "seconds,value\ninvalid,1\ninvalid,2\n"
    )
    marker = tmp_path / "script-ran"
    script = tmp_path / "next.py"
    script.write_text(f"from pathlib import Path\nPath({str(marker)!r}).touch()\n")
    prefix = tmp_path / "first.py"
    prefix.write_text("pass\n")
    files = ([str(prefix)] if after_script else []) + [str(recording), str(script)]
    app = DataViewerApp(files, backend="pyarrow", loading_mode="memory")
    choices = []

    def choose():
        if app.state.services.axis_requests:
            assert not marker.exists()
            assert not app._startup_pending.done()
            choices.append(True)
            app.state.resolve_axis() if outcome == "cancel" else app.state.resolve_axis(
                "seconds", "time"
            )

    try:
        _finish_startup(app, choose)
        assert choices == [True]
        assert marker.exists() == (outcome == "success")
        assert len(app.state.registry.runs) == (1 if outcome == "success" else 0)
        if outcome != "success":
            assert "Startup stopped" in app.state.console.as_text()
    finally:
        app._shutdown()


@pytest.mark.parametrize("choice", ["csv", "convert", "cancel"])
def test_startup_large_csv_choice_preserves_completion(tmp_path, monkeypatch, choice):
    monkeypatch.setattr("ultrazohm_dataviewer.state.LARGE_CSV_BYTES", 1)
    recording = tmp_path / "large.csv"
    recording.write_text("seconds,value\n0,1\n1,2\n")
    app = DataViewerApp([str(recording)], backend="pyarrow")
    choices = []
    completion = []

    def choose():
        if app.state.services.large_csv_requests:
            completion.append(app._startup_pending)
            app.state.resolve_large_csv(choice)
            choices.append("large")
        if app.state.services.axis_requests:
            assert app._startup_pending is completion[0]
            assert not completion[0].done()
            app.state.resolve_axis("seconds", "time")
            choices.append("axis")

    try:
        _finish_startup(app, choose)
        assert choices == (["large"] if choice == "cancel" else ["large", "axis"])
        if choice == "cancel":
            assert completion[0].cancelled()
        else:
            assert completion[0].result() is app.state.registry.runs[0]
    finally:
        app._shutdown()
