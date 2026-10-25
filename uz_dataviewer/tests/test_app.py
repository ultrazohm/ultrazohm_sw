"""Startup ordering and application-owned status rendering."""
from uz_dataviewer.app import DataViewerApp


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
        assert app.state._executor.thread is None
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
