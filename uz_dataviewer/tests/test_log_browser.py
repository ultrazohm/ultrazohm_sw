"""Local discovery and UI integration without loading log contents."""
from pathlib import Path
from threading import Event

from imgui_bundle import imgui

from uz_dataviewer.panels.log_browser import LogBrowserPanel, scan_logs
from uz_dataviewer.panels.navigation import NavigationPanel
from uz_dataviewer.state import AppState


def test_recursive_flat_listing(tmp_path):
    for name in ('a.csv', 'nested/a.csv', 'nested/B.PARQUET', 'other.txt', 'x.csv.bak'):
        path = tmp_path / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.touch()
    (tmp_path / 'directory.csv').mkdir()
    paths, errors = scan_logs(tmp_path, Event())
    assert paths == [Path('a.csv'), Path('nested/a.csv'), Path('nested/B.PARQUET')]
    assert errors == []
    cancel = Event()
    cancel.set()
    assert scan_logs(tmp_path, cancel) == ([], [])
    assert scan_logs(tmp_path / 'missing', Event())[1]


def test_switch_directory_and_render(tmp_path):
    first, second = tmp_path / 'first', tmp_path / 'second'
    first.mkdir()
    second.mkdir()
    (first / 'old.csv').touch()
    (second / 'new##log.parquet').touch()
    panel = LogBrowserPanel()
    state = AppState()
    context = imgui.create_context()
    io = imgui.get_io()
    io.set_ini_filename('')
    io.display_size = imgui.ImVec2(1200, 800)
    io.delta_time = 1 / 60
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    try:
        panel.refresh(first)
        panel.refresh(second)
        panel._future.result(timeout=5)
        for _ in range(3):
            imgui.new_frame()
            imgui.set_next_window_size(imgui.ImVec2(450, 600))
            imgui.begin('Log Browser')
            panel.render(state)
            imgui.end()
            imgui.begin('Navigation')
            NavigationPanel().render(state)
            imgui.end()
            imgui.render()
        assert panel.files == [Path('new##log.parquet')]
        assert not panel.errors
    finally:
        panel.shutdown()
        state.shutdown()
        imgui.destroy_context(context)


def test_log_drop_uses_existing_loader(monkeypatch):
    state = AppState()
    loaded = []
    state.dragged_log_path = '/logs/a.parquet'
    monkeypatch.setattr(state, 'request_load', loaded.append)
    monkeypatch.setattr(imgui, 'get_window_pos', lambda: imgui.ImVec2(10, 20))
    monkeypatch.setattr(imgui, 'get_window_size', lambda: imgui.ImVec2(400, 800))
    monkeypatch.setattr(imgui, 'get_id', lambda _: 123)
    def accept_navigation(bounds, target_id):
        assert (bounds.min.x, bounds.min.y) == (10, 20)
        assert (bounds.max.x, bounds.max.y) == (410, 820)
        assert target_id == 123
        return True
    monkeypatch.setattr(imgui.internal, 'begin_drag_drop_target_custom', accept_navigation)
    monkeypatch.setattr(imgui, 'accept_drag_drop_payload_py_id', lambda _: object())
    monkeypatch.setattr(imgui, 'end_drag_drop_target', lambda: None)
    try:
        panel = NavigationPanel()
        panel._accept_log_drop(state)
        panel._accept_log_drop(state)
        assert loaded == ['/logs/a.parquet']
        assert state.dragged_log_path is None
    finally:
        state.shutdown()
