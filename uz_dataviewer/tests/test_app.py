"""Startup ordering and application-owned status rendering."""
import pytest

from uz_dataviewer.app import DataViewerApp


@pytest.mark.parametrize('use_live', [False, True])
def test_live_panels_are_opt_in(use_live, monkeypatch):
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    app = DataViewerApp(use_live=use_live, live_mapping='cached-mapping.json')
    try:
        windows = app._dockable_windows()
        labels = {window.label for window in windows}
        if use_live:
            assert all(w.is_visible == (w.label != 'Python') for w in windows)
        live_labels = {'Live Data', 'Live Plots', 'Control', 'Python'}
        assert labels & live_labels == (live_labels if use_live else set())
        assert (app.live is not None) == use_live
        if app.live is not None:
            assert app.live.controller.thread is None
            assert app.live.mapping == 'cached-mapping.json'
    finally:
        app._shutdown()


def test_web_never_creates_live_workspace(monkeypatch):
    monkeypatch.setattr('uz_dataviewer.runtime.IS_WEB', True)
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    app = DataViewerApp(use_live=True)
    try:
        assert app.live is None
    finally:
        app._shutdown()


def test_startup_recording_precedes_script(tmp_path, monkeypatch):
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    recording = tmp_path / 'log.csv'
    recording.write_text('time;a\n0;1\n1;2\n')
    script = tmp_path / 'setup.uzscript'
    script.write_text('add_signal(plot_1, run_1, a)\n')
    app = DataViewerApp([str(recording), str(script)], backend='pyarrow', loading_mode='memory')
    try:
        assert app.state.cells[0].signals == [(1, 'a')]
        assert not app.state.is_loading
    finally:
        app.state.shutdown()


def test_startup_failure_is_reported_and_stops_following_scripts(tmp_path, monkeypatch):
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    first = tmp_path / 'bad.uzscript'
    first.write_text('add_signal(plot_1, run_1, missing)\n')
    second = tmp_path / 'next.uzscript'
    second.write_text('set_grid(2, 2)\n')
    app = DataViewerApp([str(first), str(second)])
    try:
        assert app.state.cell_count == 1
        assert 'Startup stopped' in app.state.console.as_text()
        assert app.state.services.executor.thread is None
    finally:
        app.state.shutdown()


def test_status_owns_fps_even_after_framework_toggle(monkeypatch, gui_frame):
    from imgui_bundle import immapp
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    captured = []
    monkeypatch.setattr(immapp, 'run', lambda params, addons: captured.append(params))
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
        app.state.shutdown()


def test_open_mode_menu_uses_real_imgui_binding(monkeypatch, gui_frame):
    from imgui_bundle import imgui
    from types import SimpleNamespace
    app = DataViewerApp()
    try:
        # Exercise actual menu_item bindings, including the Analysis item that
        # previously raised TypeError only after opening the Mode menu.
        monkeypatch.setattr(imgui, 'begin_menu', lambda label: label == 'Mode')
        monkeypatch.setattr(imgui, 'end_menu', lambda: None)
        gui_frame(SimpleNamespace(render=lambda state: app._show_menus()), app.state)
    finally:
        app._shutdown()


def test_selected_workspace_owns_user_data(tmp_path, monkeypatch):
    from uz_dataviewer.live import new_output_directory
    from uz_dataviewer.user_paths import HEADER
    monkeypatch.delenv('UZ_DATAVIEWER_CACHE', raising=False)
    header = tmp_path/'workspace'/HEADER
    header.parent.mkdir(parents=True)
    header.touch()
    mapping = tmp_path/'workspace'/'artifacts'/'_user'/'mapping.json'
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    app = DataViewerApp(use_live=True, live_mapping=str(mapping))
    try:
        assert app.live.repo == str(tmp_path/'workspace')
        assert app.artifacts == tmp_path/'workspace'/'artifacts'/'_user'
        assert app.state.cache_dir == str(app.artifacts/'viewer_cache')
        assert app.live.output.startswith(str(app.artifacts/'logs'))
        assert new_output_directory(app.live.repo).startswith(str(app.artifacts/'logs'))
    finally:
        app._shutdown()


def test_mode_only_focuses_targets_and_preserves_other_windows(monkeypatch):
    from types import SimpleNamespace
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    app = DataViewerApp(use_live=True)
    try:
        app.live.available = True
        windows = app._dockable_windows()
        focused = []
        app._runner_params = SimpleNamespace(docking_params=SimpleNamespace(
            dockable_windows=windows, focus_dockable_window=focused.append))
        app._apply_window_mode(True)
        assert focused == ['Live Data', 'Control', 'Live Plots']
        assert all(w.is_visible for w in windows if w.label != 'Python')
        # User choices outside the selected group survive subsequent switches.
        next(w for w in windows if w.label == 'FFT').is_visible = False
        app._apply_window_mode(False)
        assert focused[-3:] == ['Navigation', 'Log Browser', 'Plots']
        assert all(w.is_visible for w in windows if w.label in {'Live Data', 'Control', 'Live Plots'})
        assert not next(w for w in windows if w.label == 'FFT').is_visible
    finally:
        app._shutdown()


@pytest.mark.parametrize('frozen', [False, True])
@pytest.mark.parametrize('via_mapping', [False, True])
def test_log_browser_uses_selected_workspace(tmp_path, monkeypatch, frozen, via_mapping):
    import sys
    from pathlib import Path
    from uz_dataviewer.user_paths import HEADER
    workspace = tmp_path / 'selected'
    header = workspace / HEADER
    header.parent.mkdir(parents=True)
    header.touch()
    log = workspace / 'artifacts' / '_user_standalone' / 'logs' / 'run.csv'
    log.parent.mkdir(parents=True)
    log.touch()
    elsewhere = tmp_path / 'elsewhere'
    elsewhere.mkdir()
    monkeypatch.chdir(elsewhere)
    monkeypatch.setattr(sys, 'frozen', frozen, raising=False)
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    kwargs = ({'live_mapping': str(workspace / 'artifacts' / 'mapping.json')} if via_mapping
              else {'live_repo': str(workspace)})
    app = DataViewerApp(**kwargs)
    try:
        assert app.log_browser.directory == workspace
        app.log_browser.refresh()
        files, errors = app.log_browser._future.result(timeout=5)
        assert files == [Path('artifacts/_user_standalone/logs/run.csv')]
        assert not errors
    finally:
        app._shutdown()
