"""Real GUI regressions for matching channels from independent recordings."""
import time

import numpy as np
import pytest
from imgui_bundle import imgui, implot

from uz_dataviewer.panels.navigation import NavigationPanel
from uz_dataviewer.panels.plots import PlotsPanel


def load_logs(state, tmp_path, mode, offset):
    state.backend = 'pyarrow'
    state.loading_mode = mode
    for index in range(2):
        # Identical filenames and channels must still identify distinct runs.
        path = tmp_path / str(index) / 'log.csv'
        path.parent.mkdir()
        path.write_text('time;a\n' + ''.join(
            f'{i + index * offset};{i + index * 100}\n' for i in range(10)))
        state.load_sync(str(path))


@pytest.mark.parametrize('mode', ['memory', 'lazy'])
def test_drag_matching_csv_signals_into_both_cells(app_state, gui_frame, monkeypatch, tmp_path, mode):
    state = app_state
    state.set_grid(2, 1)
    load_logs(state, tmp_path, mode, 0)
    navigation, plots = NavigationPanel(), PlotsPanel()
    rows, geometry, drawn = {}, {}, {}
    original_selectable = imgui.selectable

    def selectable(label, *args, **kwargs):
        result = original_selectable(label, *args, **kwargs)
        if label == 'a':
            start, end = imgui.get_item_rect_min(), imgui.get_item_rect_max()
            rows[len(rows)] = (start.x + 20, (start.y + end.y) / 2)
        return result

    monkeypatch.setattr(imgui, 'selectable', selectable)
    original_tree = imgui.tree_node_ex

    def tree(*args, **kwargs):
        imgui.set_next_item_open(True)
        return original_tree(*args, **kwargs)

    monkeypatch.setattr(imgui, 'tree_node_ex', tree)
    current_cell = [None]

    def capture_geometry(state, index, cell, lo, hi):
        current_cell[0] = index
        geometry[index] = (implot.get_plot_pos(), implot.get_plot_size())

    plots._time_series_input = capture_geometry
    original_line = implot.plot_line

    def line(label, xs, ys, *args, **kwargs):
        drawn[current_cell[0], label] = (xs.copy(), ys.copy())
        return original_line(label, xs, ys, *args, **kwargs)

    monkeypatch.setattr(implot, 'plot_line', line)
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1600, 1000)

    def frame():
        rows.clear()
        imgui.new_frame()
        imgui.set_next_window_pos(imgui.ImVec2(0, 0))
        imgui.set_next_window_size(imgui.ImVec2(350, 900))
        imgui.begin('Navigation')
        navigation.render(state)
        imgui.end()
        imgui.set_next_window_pos(imgui.ImVec2(350, 0))
        imgui.set_next_window_size(imgui.ImVec2(1200, 900))
        imgui.begin('Plots')
        plots.render(state)
        imgui.end()
        imgui.render()

    for _ in range(4):
        frame()
    for run, cell in [(0, 0), (1, 1), (1, 0), (0, 1)]:
        x, y = rows[run]
        io.add_mouse_pos_event(x, y)
        frame()
        io.add_mouse_button_event(0, True)
        frame()
        io.add_mouse_pos_event(x + 20, y)
        frame()
        position, size = geometry[cell]
        io.add_mouse_pos_event(position.x + size.x / 2, position.y + size.y / 2)
        frame()
        frame()
        io.add_mouse_button_event(0, False)
        frame()
        frame()
        assert (run + 1, 'a') in state.cells[cell].signals

    deadline = time.monotonic() + 5
    while len(drawn) < 4 and time.monotonic() < deadline:
        frame()
        time.sleep(.01)
    assert len(drawn) == 4
    for cell in range(2):
        for run in range(1, 3):
            xs, ys = drawn[cell, state.signal_label((run, 'a'))]
            np.testing.assert_array_equal(xs, np.arange(10.))
            np.testing.assert_array_equal(ys, np.arange(10.) + (run - 1) * 100)
    state.commands.execute(state, 'remove_signal', [1, 1, 'a'])
    assert state.cells[0].signals == [(2, 'a')]
    assert set(state.cells[1].signals) == {(1, 'a'), (2, 'a')}


@pytest.mark.parametrize('mode', ['memory', 'lazy'])
@pytest.mark.parametrize('linked', [True, False])
def test_add_and_reset_fit_disjoint_recordings(app_state, gui_frame, tmp_path, mode, linked):
    state = app_state
    state.services.display.synchronous = True
    state.set_grid(2, 1)
    state.set_link_x(linked)
    load_logs(state, tmp_path, mode, 100)
    panel = PlotsPanel()

    def frames():
        for _ in range(4):
            gui_frame(panel, state)

    state.commands.execute(state, 'add_signal', [1, 1, 'a'])
    frames()
    state.set_plot_x_limits(1, 0, 9)
    frames()
    state.commands.execute(state, 'add_signal', [2, 2, 'a'])
    frames()

    def assert_visible():
        for index, cell in enumerate(state.cells):
            expected = (0, 109) if linked else (index * 100, index * 100 + 9)
            assert cell.x_lim == pytest.approx(expected)
            assert state.plot_time_range(index + 1) == pytest.approx(expected)
            assert cell.y_lim[0] <= index * 100
            assert cell.y_lim[1] >= index * 100 + 9

    assert_visible()
    for target in (1, 2):
        state.set_plot_x_limits(target, 2, 4)
        frames()
        state.commands.execute(state, 'reset_view', [target])
        frames()
        assert_visible()
