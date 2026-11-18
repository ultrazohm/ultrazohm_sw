"""Preferences persistence, session precedence, and rendered Settings sections."""
from types import SimpleNamespace

import pytest

from uz_dataviewer.preferences import Preferences, DEFAULTS
from uz_dataviewer.app import DataViewerApp
from uz_dataviewer.session import to_dict, apply_dict


def test_preferences_roundtrip_and_session_precedence(app_state):
    preferences = Preferences(app_state)
    preferences.update({'loading_mode': 'memory', 'cache_budget': 32})
    assert app_state.loading_mode == 'memory'
    assert Preferences().values['cache_budget'] == 32
    snapshot = to_dict(app_state)
    snapshot['loading_mode'] = 'lazy'
    apply_dict(app_state, snapshot)
    assert app_state.loading_mode == 'lazy'
    assert Preferences().values['loading_mode'] == 'memory'
    before = preferences.path.read_bytes()
    with pytest.raises(ValueError):
        preferences.update({'cache_budget': 0})
    assert preferences.path.read_bytes() == before
    assert preferences.values['cache_budget'] == 32
    preferences.reset('Performance')
    assert app_state.registry.cache.limit == DEFAULTS['cache_budget'] * 1024**2
    assert preferences.values['loading_mode'] == 'memory'


def test_settings_restore_defaults_and_render_sections(gui_frame):
    preferences = Preferences()
    preferences.update({'loading_mode': 'memory', 'show_application_log': True, 'cache_budget': 16})
    app = DataViewerApp()
    try:
        assert app.state.loading_mode == 'memory'
        assert app.state.registry.cache.limit == 16 * 1024**2
        assert next(w for w in app._dockable_windows() if w.label == 'Application log').is_visible
        panel = app.settings_panel
        panel.visible = True
        for section in ('General', 'Data loading', 'Performance'):
            panel.section = section
            gui_frame(SimpleNamespace(render=lambda _: panel.render()), app.state)
            assert panel.visible
        app.preferences.update({'log_directory': '/tmp'})
        assert str(app.log_browser.directory) == '/tmp'
    finally:
        app._shutdown()


def test_invalid_preferences_do_not_prevent_startup():
    preferences = Preferences()
    preferences.path.parent.mkdir(parents=True, exist_ok=True)
    preferences.path.write_text('{broken')
    loaded = Preferences()
    assert loaded.values == DEFAULTS
    assert loaded.error


def test_settings_client_uses_shared_preferences(control_session):
    state, client, workers, pump = control_session
    def script():
        client.set_setting('cache_budget', 48)
        client.set_setting('show_application_log', True)
        assert client.get_settings()['cache_budget'] == 48
        assert client.get_settings()['show_application_log'] is True
    future = workers.submit(script)
    pump(future.done)
    future.result()
    assert state.registry.cache.limit == 48 * 1024**2
    assert Preferences().values['cache_budget'] == 48
