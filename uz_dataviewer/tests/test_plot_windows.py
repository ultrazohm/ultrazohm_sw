"""Additional grids share recordings, never view state or worker ownership."""
from types import SimpleNamespace

import numpy as np
import pytest
from imgui_bundle import hello_imgui, imgui

from uz_dataviewer.app import DataViewerApp
from uz_dataviewer.session import clear_session


@pytest.fixture
def app(monkeypatch):
    monkeypatch.setattr('uz_dataviewer.plugins.load_plugins', lambda **kwargs: None)
    monkeypatch.setattr(hello_imgui, 'add_dockable_window', lambda *args: None)
    monkeypatch.setattr(hello_imgui, 'remove_dockable_window', lambda *args: None)
    app = DataViewerApp()
    yield app
    app._shutdown()


def test_independent_grids_and_commands_share_recordings(app, gui_frame):
    run = app.state.registry.add_run('log', 'log', np.arange(20.),
                                     {'a': np.arange(20.)}, {'a': ''})
    first = app._new_plot_window()
    second = app._new_plot_window()
    assert first.registry is second.registry is app.state.registry
    first.commands.execute(first, 'set_grid', [2, 1])
    first.commands.execute(first, 'add_signal', [1, run.id, 'a'])
    second.commands.execute(second, 'add_signal', [1, run.id, 'a'])
    first.commands.execute(first, 'set_max_points', [500])
    first.set_plot_x_limits(1, 2, 5)
    second.set_plot_x_limits(1, 8, 12)
    assert app.state.cells[0].signals == []
    assert first.rows == 2 and second.rows == app.state.rows == 1
    assert first.max_points == 500 and second.max_points == 2000
    assert first.plot_time_range(1) == (2, 5)
    assert second.plot_time_range(1) == (8, 12)
    assert '[Plots 2]' in app.state.console.as_text()
    assert all(entry.level != 'CMD' for entry in app.state.console._entries)

    def render(_):
        for _, panel, window in app._plot_windows.values():
            imgui.begin(window.label)
            window.gui_function()
            imgui.end()
    gui_frame(SimpleNamespace(render=render), app.state)
    assert first.services.display.results
    assert second.services.display.results
    assert first.services.display is not second.services.display
    assert first.cells[0].x_lim == pytest.approx((2, 5))
    assert second.cells[0].x_lim == pytest.approx((8, 12))


def test_removal_and_domain_changes_prune_assignments(app):
    run = app.state.registry.add_run('log', 'log', np.arange(4.),
                                     {'a': np.arange(4.)}, {'a': ''})
    view = app._new_plot_window()
    view.cells[0].add((run.id, 'a'))
    view.cells[0].xy_source = (run.id, 'a')
    run.axis_domain = 'frequency'
    view.sync(app.state)
    assert view.cells[0].signals == []
    assert view.cells[0].xy_source is None
    view.cells[0].add((run.id, 'a'))
    app.state.remove_run(run.id)
    view.sync(app.state)
    assert view.cells[0].signals == []


def test_view_shutdown_does_not_clear_shared_cache(app, monkeypatch):
    view = app._new_plot_window()
    cleared = []
    monkeypatch.setattr(view.registry.cache, 'clear', lambda: cleared.append(True))
    services = view.services
    view.shutdown()
    assert services.display.closed
    assert not cleared
    assert not app.state.services.display.closed


def test_session_replacement_closes_extra_windows(app, monkeypatch):
    removed = []
    monkeypatch.setattr(hello_imgui, 'remove_dockable_window', removed.append)
    view = app._new_plot_window()
    clear_session(app.state)
    app._pre_new_frame()
    assert removed == ['Plots 2']
    assert not app._plot_windows
    assert view.services is None


def test_view_menu_spawns_window(app, monkeypatch, gui_frame):
    monkeypatch.setattr(imgui, 'begin_menu', lambda label: label == 'View##kdsflmkdflm')
    monkeypatch.setattr(imgui, 'end_menu', lambda: None)
    monkeypatch.setattr(imgui, 'menu_item', lambda label, *args: (label == 'New plot window', False))
    gui_frame(SimpleNamespace(render=lambda _: app._show_menus()), app.state)
    assert list(app._plot_windows) == [2]
