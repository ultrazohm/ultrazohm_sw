"""Keep persisted indexes and lazy CSV conversions out of the user's cache."""

import os
import sys
from pathlib import Path

import pytest


@pytest.fixture
def control_session(app_state):
    from concurrent.futures import ThreadPoolExecutor
    import time
    from ultrazohm_dataviewer import Client
    from ultrazohm_dataviewer.operations import Operations
    from ultrazohm_dataviewer.control_server import ControlServer
    operations = Operations(app_state)
    server = ControlServer('127.0.0.1:0')
    client = Client(server.endpoint, timeout=5)
    workers = ThreadPoolExecutor(1)
    app_state.async_exports = True
    def pump(predicate):
        deadline = time.monotonic() + 10
        while not predicate():
            operations.poll()
            app_state.poll_pending_loads()
            server.poll(operations.dispatch)
            assert time.monotonic() < deadline, 'Viewer operation timed out'
            time.sleep(.001)
    try:
        yield app_state, client, workers, pump
    finally:
        server.close()
        operations.close()
        workers.shutdown(wait=True)
        client.close()

if not os.environ.get("UZ_TEST_INSTALLED"):
    sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "src"))


@pytest.fixture(autouse=True)
def isolated_app_cache(tmp_path, monkeypatch):
    monkeypatch.setenv('UZ_DATAVIEWER_CACHE', str(tmp_path / 'app-cache'))
    # Never write into the real per-user data directory.
    monkeypatch.setenv('XDG_DATA_HOME', str(tmp_path / 'user-data'))
    monkeypatch.setenv('LOCALAPPDATA', str(tmp_path / 'user-data'))


@pytest.fixture
def app_state():
    from ultrazohm_dataviewer.state import AppState
    state = AppState()
    yield state
    state.shutdown()


@pytest.fixture
def gui_frame():
    """Render real panel frames without a GPU or persistent editor settings."""
    from imgui_bundle import imgui, implot, imgui_node_editor as ed
    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.set_ini_filename(None)
    io.display_size = imgui.ImVec2(1000, 800)
    io.delta_time = 1 / 60
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    config = ed.Config()
    config.settings_file = ''
    editor = ed.create_editor(config)
    ed.set_current_editor(editor)

    def frame(panel, state, name='Review test'):
        imgui.new_frame()
        imgui.set_next_window_size(imgui.ImVec2(1000, 800))
        imgui.begin(name)
        panel.render(state)
        imgui.end()
        imgui.render()

    yield frame
    ed.destroy_editor(editor)
    implot.destroy_context()
    imgui.destroy_context()


@pytest.fixture
def states():
    from ultrazohm_dataviewer.state import AppState
    created = []

    def make():
        state = AppState()
        created.append(state)
        return state
    yield make
    for state in created:
        state.shutdown()


@pytest.fixture
def recording_csv(tmp_path):
    path = tmp_path / 'recording.csv'
    path.write_text('time;a\n' + ''.join((f'{i};{i + 1}\n' for i in range(8))))
    return path


@pytest.fixture
def execute_commands():

    def execute(state, *lines):
        for line in lines:
            state.commands.execute(state, *line)
    return execute


@pytest.fixture
def compute_panel():
    """Seed a panel using the same independent request used by its worker."""
    def compute(panel, state, cfg, lo, hi):
        panel._sync_session(state)
        result = panel._make_request(state, cfg, lo, hi).compute()
        panel._results, panel._info = result.series, result.info
    return compute
