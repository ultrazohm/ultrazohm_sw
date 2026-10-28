"""Exercise Enter-only variable writes using real ImGui keyboard/mouse events."""
from types import SimpleNamespace
from dataclasses import replace

import pytest
from imgui_bundle import imgui

from uz_dataviewer.live import LiveController, LiveUpdate
from uz_dataviewer.panels.live import LiveWorkspace


@pytest.fixture
def variable_table(gui_frame, app_state, monkeypatch):
    workspace = LiveWorkspace(LiveController(lambda _: None))
    workspace.update = LiveUpdate(attached=True, status={'state': {'connected': True}},
        catalog={'variables': {'send_field_10': 13, 'send_field_2': 5, 'send_field_1': 4}})
    calls, rects, colors = [], {}, {}
    monkeypatch.setattr(workspace, 'send', lambda op, **kwargs: calls.append((op, kwargs)))
    original = imgui.input_text
    def input_text(label, *args, **kwargs):
        result = original(label, *args, **kwargs)
        if label.startswith('##variable_value_'):
            name = label.removeprefix('##variable_value_')
            lo, hi = imgui.get_item_rect_min(), imgui.get_item_rect_max()
            rects[name] = ((lo.x + hi.x)/2, (lo.y + hi.y)/2)
            color = imgui.get_style().color_(imgui.Col_.frame_bg_active)
            colors[name] = (color.x, color.y, color.z, color.w)
        return result
    monkeypatch.setattr(imgui, 'input_text', input_text)
    def frame():
        rects.clear()
        gui_frame(SimpleNamespace(render=lambda _: workspace.render_control()), app_state, 'Variable table')
    def click(name):
        frame()
        imgui.get_io().add_mouse_pos_event(*rects[name])
        frame()
        imgui.get_io().add_mouse_button_event(0, True)
        frame()
        imgui.get_io().add_mouse_button_event(0, False)
        frame()
    def type_value(name, text):
        click(name)
        io = imgui.get_io()
        io.add_key_event(imgui.Key.mod_ctrl, True)
        io.add_key_event(imgui.Key.a, True)
        frame()
        io.add_key_event(imgui.Key.a, False)
        io.add_key_event(imgui.Key.mod_ctrl, False)
        frame()
        io.add_input_characters_utf8(text)
        frame()
    def enter():
        imgui.get_io().add_key_event(imgui.Key.enter, True)
        frame()
        imgui.get_io().add_key_event(imgui.Key.enter, False)
        frame()
    try:
        yield SimpleNamespace(workspace=workspace, calls=calls, rects=rects,
                              frame=frame, click=click, type=type_value, enter=enter, colors=colors)
    finally:
        workspace.close()


def test_variables_keep_separate_values_and_only_send_on_enter(variable_table):
    table = variable_table
    table.frame()
    assert list(table.rects) == ['send_field_1', 'send_field_2', 'send_field_10']
    table.type('send_field_1', '12.5')
    assert table.calls == []
    assert table.workspace.variable_values['send_field_1'] == '12.5'
    table.type('send_field_2', '-2e-3')
    assert table.calls == []  # Leaving the first input must not send either value.
    table.enter()
    assert table.calls == [('set_variable', {'name': 'send_field_2', 'value': -.002})]
    table.click('send_field_1')
    table.enter()
    assert table.calls[-1] == ('set_variable', {'name': 'send_field_1', 'value': 12.5})
    assert len(table.calls) == 2
    table.workspace.variable_query = 'field_1'
    table.frame()
    assert list(table.rects) == ['send_field_1', 'send_field_10']
    assert table.workspace.variable_values['send_field_2'] == '-2e-3'
    assert len(table.calls) == 2


@pytest.mark.parametrize('text', ['abc', 'nan', 'inf'])
def test_invalid_values_never_send(variable_table, text):
    table = variable_table
    table.type('send_field_1', text)
    table.enter()
    assert table.calls == []
    assert 'Invalid value for send_field_1' in table.workspace.error


def test_script_locks_variable_inputs(variable_table):
    table = variable_table
    table.workspace.scripts = SimpleNamespace(busy=True, close=lambda: None)
    table.type('send_field_1', '7')
    table.enter()
    assert table.calls == []
    assert table.workspace.variable_values['send_field_1'] == '0'


def test_success_highlights_only_matching_field_for_two_tenths_second(variable_table, monkeypatch):
    from uz_dataviewer.panels import live
    table = variable_table
    clock = SimpleNamespace(now=10.01)
    monkeypatch.setattr(live, 'time', SimpleNamespace(monotonic=lambda: clock.now))
    blue = (.12, .32, .65, 1.)
    table.workspace.variable_values['send_field_1'] = '12.5'
    table.frame()
    assert table.colors['send_field_1'] != pytest.approx(blue)  # No send completion yet.
    table.workspace.update = replace(table.workspace.update, variable_sends={'send_field_1': (10., 12.5)})
    table.frame()
    assert table.colors['send_field_1'] == pytest.approx(blue)
    assert table.colors['send_field_2'] != pytest.approx(blue)
    clock.now = 10.19
    table.frame()
    assert table.colors['send_field_1'] == pytest.approx(blue)
    clock.now = 10.21
    table.frame()
    assert table.colors['send_field_1'] != pytest.approx(blue)
    clock.now = 10.01
    table.workspace.variable_values['send_field_1'] = '9'
    table.frame()
    assert table.colors['send_field_1'] != pytest.approx(blue)  # A new draft is not the sent value.
