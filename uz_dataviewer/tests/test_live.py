"""Bounded live snapshots, worker recovery, and real ImGui panel rendering."""
from dataclasses import replace
from types import SimpleNamespace
import time

import numpy as np
import polars as pl
import pytest

from uz_dataviewer.live import LiveController, LiveSource, LiveUpdate, fuzzy_names
from uz_dataviewer.panels.live import LiveWorkspace
from uz_dataviewer.sources import TimeShift, shift_time


def frame(start, stop):
    t = np.arange(start, stop, dtype=np.float64) * .001
    return pl.DataFrame({'time': t, 'status': np.ones(len(t), np.uint32),
                         'a': np.sin(t).astype(np.float32), 'b': np.cos(t).astype(np.float32)})


def wait_for(function, seconds=4):
    deadline = time.monotonic() + seconds
    while time.monotonic() < deadline:
        result = function()
        if result:
            return result
        time.sleep(.01)
    raise AssertionError('condition timed out')


class FakeClient:
    def __init__(self):
        self.stop = 30
        self.generation = 0
        self.connected = True
        self.calls = []

    def status(self):
        return {'state': {'connected': self.connected, 'platform_state': 'idle'},
                'data_options': {'buffer_samples': 100}, 'logging': {}}

    def catalog(self):
        return {'profile': {'observables': {'a': 1, 'b': 2}, 'variables': {'setpoint': 4},
                            'sample_period_us': 1000}}

    def observables(self):
        return {'channels': [{'channel': 1, 'name': 'a'}, {'channel': 2, 'name': 'b'}]}

    def read_since(self, cursor=None, limit=100):
        first = max(0, self.stop - 100)
        if cursor and (cursor['generation'] != self.generation or cursor['next_sample'] < first):
            raise RuntimeError('expired cursor')
        start = cursor['next_sample'] if cursor else first
        stop = min(start + limit, self.stop)
        return SimpleNamespace(data=frame(start, stop),
            cursor={'next_sample': stop, 'generation': self.generation},
            info={'run_id': 'fake', 'generation': self.generation})

    def set_variable(self, name, value):
        self.calls.append(('variable', name, value))
        raise RuntimeError('variable rejected')

    def set_observable(self, name, channel):
        self.calls.append(('observable', name, channel))
        self.generation += 1


def test_live_source_visible_downsampling_preserves_extrema():
    f = frame(0, 10000).with_columns(pl.when(pl.int_range(pl.len()) == 6543)
                                    .then(50.).otherwise(pl.col('a')).cast(pl.Float32).alias('a'))
    source = LiveSource(f)
    data = source.read_plot('a', 6., 7., 100)
    assert data.raw_count < 1100
    assert data.values.max() == 50
    assert len(data.time) <= 150
    shift = TimeShift(0., 10.)
    shifted = source.read_plot('a', 16., 17., 100, offset=shift)
    np.testing.assert_array_equal(shifted.values, data.values)
    np.testing.assert_allclose(shift_time(shifted.time, shift), data.time + 10.)
    assert source.metadata.identity != LiveSource(f).metadata.identity


def test_worker_incremental_bound_recovery_and_persistent_command_error():
    client = FakeClient()
    controller = LiveController(lambda endpoint: client, hz=100)
    try:
        controller.submit('attach', endpoint='127.0.0.1:19740')
        first = wait_for(lambda: controller.latest().source)
        assert first.metadata.rows == 30
        client.stop = 80
        second = wait_for(lambda: (s if (s := controller.latest().source).metadata.rows == 80 else None))
        assert first.metadata.rows == 30  # old display/analysis readers stay immutable
        assert second.time[-1] == pytest.approx(.079)
        client.stop = 500  # Advance beyond the retained window.
        recovered = wait_for(lambda: (s if (s := controller.latest().source).time[-1] > .4 else None))
        assert recovered.metadata.rows == 100
        assert 'resynchronized' in controller.latest().notice
        controller.submit('set_variable', name='setpoint', value=3.)
        wait_for(lambda: 'variable rejected' in controller.latest().error)
        revision = controller.latest().revision
        wait_for(lambda: controller.latest().revision >= revision + 4)
        assert 'variable rejected' in controller.latest().error
        controller.submit('set_observable', name='b', channel=1)
        wait_for(lambda: controller.latest().epoch == ('fake', 1))
        assert not controller.latest().error
        controller.submit('detach')
        wait_for(lambda: not controller.latest().attached)
        assert client.connected  # detaching never sends device Stop or shutdown
    finally:
        controller.close()
    assert not controller.thread.is_alive()


def test_live_panels_follow_pause_freeze_and_generation(gui_frame, app_state):
    controller = LiveController(lambda endpoint: None)
    workspace = LiveWorkspace(controller)
    workspace.available = True
    try:
        source = LiveSource(frame(0, 5000))
        controller.update = LiveUpdate(1, status={'state': {'connected': True, 'platform_state': 'idle'},
                                      'data_options': {'buffer_samples': 100000},
                                      'logging': {'fast': {'phase': 'idle'}, 'slow': {'phase': 'idle'}}},
            source=source, epoch=('run', 0), attached=True,
            catalog={'sample_period_us': 100., 'observables': {'a': 1, 'b': 2}, 'variables': {'setpoint': 4}},
            assignments=({'channel': 1, 'name': 'a'}, {'channel': 2, 'name': 'b'}))
        workspace.pump()
        run = workspace.run
        workspace.state.cells[0].add((run.id, 'a'))
        workspace.state.services.display.synchronous = True
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
        gui_frame(SimpleNamespace(render=lambda state: workspace.render_control()), app_state)
        for _ in range(3):
            gui_frame(SimpleNamespace(render=workspace.render_plots), app_state)
        lo, hi = workspace.state.cells[0].x_lim
        assert hi == pytest.approx(4.999)
        assert hi - lo == pytest.approx(2.)
        assert workspace.plots._last_points[0] > 0
        workspace.freeze(app_state)
        frozen = app_state.registry.runs[0]
        assert 1990 < frozen.n_rows < 2010
        old = frozen.time.copy()
        workspace.paused = True
        controller.update = replace(controller.update, revision=2, source=LiveSource(frame(1000, 6000)))
        workspace.pump()
        assert workspace.run.source is source
        workspace.paused = False
        controller.update = replace(controller.update, revision=3)
        workspace.pump()
        assert workspace.run.source is not source
        np.testing.assert_array_equal(frozen.time, old)
        controller.update = replace(controller.update, revision=4, epoch=('run', 1))
        workspace.pump()
        assert workspace.run.id != run.id
        assert workspace.state.cells[0].signals == []
    finally:
        workspace.close()


def test_fuzzy_observable_names():
    names = ['JSO_ISR_Period_us', 'JSO_lifecheck', 'JSO_ISR_ExecTime_us']
    assert fuzzy_names(names, 'isrper') == ['JSO_ISR_Period_us']
    assert fuzzy_names(names, 'LiFe') == ['JSO_lifecheck']
    assert fuzzy_names(names, 'xyz') == []


def test_real_service_controls_and_logging_outlive_viewer(tmp_path):
    """Exercise the actual wheel/IPC and detached service against the simulator."""
    from pathlib import Path
    import socket
    import subprocess
    import sys
    native = pytest.importorskip('ultrazohm')
    root = Path(__file__).resolve().parents[2]
    def free_port():
        with socket.socket() as sock:
            sock.bind(('127.0.0.1', 0))
            return sock.getsockname()[1]
    device_port, service_port = free_port(), free_port()
    simulator = subprocess.Popen([sys.executable, str(root/'javascope/test_server.py'),
        '--host', '127.0.0.1', '--port', str(device_port), '--sample-rate', '10000'],
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    controller = LiveController(hz=30)
    client = native.Client(f'127.0.0.1:{service_port}')
    try:
        def ready():
            try:
                with socket.create_connection(('127.0.0.1', device_port), timeout=.1):
                    return True
            except OSError:
                return False
        wait_for(ready)
        controller.submit('connect', endpoint=client.endpoint, ip='127.0.0.1', port=device_port,
                          output=str(tmp_path/'recording'))
        wait_for(lambda: controller.latest().source, seconds=12)
        assert len(controller.latest().assignments) == 20
        assert len(controller.latest().catalog['observables']) > 20
        generation = controller.latest().epoch
        controller.submit('set_observable', name='JSO_lifecheck', channel=1)
        wait_for(lambda: controller.latest().epoch != generation and controller.latest().source)
        for operation in ('enable_system', 'enable_control', 'stop'):
            controller.submit(operation)
        controller.submit('button', number=1)
        variable = next(iter(controller.latest().catalog['variables']))
        controller.submit('set_variable', name=variable, value=1.25)
        controller.submit('start_logging')
        wait_for(lambda: controller.latest().status.get('logging', {}).get('fast', {}).get('phase') == 'recording')
        controller.submit('set_observable', name='JSO_lifecheck', channel=2)
        wait_for(lambda: 'logging' in controller.latest().error)
        # Closing the window/controller leaves the independent service recording.
        controller.close()
        before = client.status()['state']['samples']
        wait_for(lambda: client.status()['state']['samples'] > before + 1000)
        assert client.status()['logging']['fast']['phase'] == 'recording'
        client.stop_logging()
        wait_for(lambda: client.status()['logging']['fast']['phase'] == 'complete')
        status = client.status()
        recorded = pl.read_parquet(status['logging']['fast']['parquet'])
        assert recorded.height > 1000
        assert 'JSO_lifecheck' in recorded.columns
        import json
        events = [json.loads(line) for line in (tmp_path/'recording/commands.jsonl').read_text().splitlines()]
        text = json.dumps(events)
        for operation in ('enable_system', 'enable_control', 'stop', 'button', 'set_variable'):
            assert operation in text
    finally:
        controller.close()
        if controller.process is not None:
            try:
                client.shutdown()
                controller.process.wait(timeout=15)
            except (OSError, RuntimeError, subprocess.TimeoutExpired):
                controller.process.terminate()
                controller.process.wait(timeout=5)
        simulator.terminate()
        simulator.wait(timeout=5)


def test_follow_preserves_background_y_fit(gui_frame, app_state):
    workspace = LiveWorkspace(LiveController())
    try:
        source = LiveSource(frame(0, 5000).with_columns(pl.lit(100., dtype=pl.Float32).alias('b')))
        original = source.read_plot
        def slow_plot(*args, **kwargs):
            time.sleep(.03)
            return original(*args, **kwargs)
        source.read_plot = slow_plot
        workspace.controller.update = LiveUpdate(1, source=source, epoch=('run', 0))
        workspace.pump()
        workspace.state.cells[0].add((workspace.run.id, 'b'))
        for _ in range(14):
            gui_frame(SimpleNamespace(render=workspace.render_plots), app_state)
            time.sleep(.01)
        lo, hi = workspace.state.cells[0].y_lim
        assert lo <= 100 < hi
    finally:
        workspace.close()


def test_connect_click_reports_progress_and_completion(gui_frame, app_state, monkeypatch):
    import threading
    from imgui_bundle import imgui
    gate = threading.Event()
    class SlowClient(FakeClient):
        def catalog(self):
            gate.wait(timeout=3)
            return super().catalog()
    controller = LiveController(lambda endpoint: SlowClient())
    workspace = LiveWorkspace(controller)
    workspace.available = True
    try:
        # Exercise the actual panel's Connect handler, with slow startup IO.
        with monkeypatch.context() as patch:
            patch.setattr(imgui, 'button', lambda label, *args, **kwargs: label == 'Connect')
            gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
        assert workspace.pending_message == 'Connecting…'
        wait_for(lambda: controller.latest().activity == 'Reading service configuration…')
        workspace.pump(app_state)
        assert workspace.update.activity
        assert workspace.update.completed_commands == 0
        assert 'Reading service configuration' in app_state.console.as_text()
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
        gate.set()
        wait_for(lambda: controller.latest().completed_commands == 1 and controller.latest().source)
        workspace.pump(app_state)
        assert not workspace.pending_message
        assert not workspace.update.activity
        assert workspace.update.status['state']['connected']
        assert 'Attached to acquisition service' in app_state.console.as_text()
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
    finally:
        gate.set()
        workspace.close()


def test_connect_failure_clears_busy_and_reports_error(gui_frame, app_state):
    class BrokenClient(FakeClient):
        def catalog(self):
            raise RuntimeError('incompatible service version')
    workspace = LiveWorkspace(LiveController(lambda endpoint: BrokenClient()))
    workspace.available = True
    try:
        workspace.send('connect', endpoint=workspace.endpoint, ip=workspace.ip,
                       port=workspace.port, output=workspace.output)
        wait_for(lambda: workspace.controller.latest().completed_commands == 1)
        workspace.pump(app_state)
        assert not workspace.pending_message
        assert not workspace.update.activity
        assert 'incompatible service version' in workspace.update.error
        assert 'ERROR' in app_state.console.as_text()
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
    finally:
        workspace.close()


@pytest.mark.parametrize('capacity,period,maximum', [(300_000, 100., 30.), (3_000_000, 10., 30.), (5000, 100., .5)])
def test_time_depth_tracks_service_capacity(gui_frame, app_state, monkeypatch, capacity, period, maximum):
    from imgui_bundle import imgui
    workspace = LiveWorkspace(LiveController())
    try:
        workspace.controller.update = LiveUpdate(1, status={'data_options': {'buffer_samples': capacity}},
                                                catalog={'sample_period_us': period})
        workspace.pump()
        seen = []
        def slider(label, value, minimum, upper, *args, **kwargs):
            seen.append(upper)
            return False, value
        monkeypatch.setattr(imgui, 'slider_float', slider)
        workspace.window_seconds = 45.
        gui_frame(SimpleNamespace(render=workspace.render_plots), app_state)
        assert seen[-1] == pytest.approx(maximum)
        assert workspace.window_seconds == pytest.approx(maximum)
        workspace.window_seconds = .2
        gui_frame(SimpleNamespace(render=workspace.render_plots), app_state)
        assert workspace.window_seconds == pytest.approx(.2)
    finally:
        workspace.close()


def test_large_ring_uses_bounded_transfer_pages():
    class LargeRingClient(FakeClient):
        def __init__(self):
            super().__init__()
            self.limits = []
        def status(self):
            result = super().status()
            result['data_options']['buffer_samples'] = 3_000_000
            return result
        def read_since(self, cursor=None, limit=100):
            self.limits.append(limit)
            return super().read_since(cursor, limit)
    client = LargeRingClient()
    controller = LiveController(lambda endpoint: client)
    try:
        controller.submit('attach', endpoint='127.0.0.1:19740')
        wait_for(lambda: controller.latest().source)
        assert client.limits
        assert max(client.limits) == 100_000
    finally:
        controller.close()


def test_native_wheel_zoom_pan_inspect_and_resume(gui_frame, app_state):
    from imgui_bundle import imgui, implot
    workspace = LiveWorkspace(LiveController())
    workspace.state.services.display.synchronous = True
    geometry = {}
    original = workspace.plots._time_series_input
    def capture(state, index, cell, lo, hi):
        geometry['pos'] = implot.get_plot_pos()
        geometry['size'] = implot.get_plot_size()
        original(state, index, cell, lo, hi)
    workspace.plots._time_series_input = capture
    panel = SimpleNamespace(render=workspace.render_plots)
    def render():
        workspace.pump()
        gui_frame(panel, app_state)
    try:
        workspace.controller.update = LiveUpdate(1, source=LiveSource(frame(0, 10000)), epoch=('run', 0))
        workspace.pump()
        workspace.state.cells[0].add((workspace.run.id, 'a'))
        workspace.state.cells[0].add((workspace.run.id, 'b'))
        workspace.state.cells[0].set_secondary((workspace.run.id, 'b'), True)
        for _ in range(3): render()
        before = workspace.state.cells[0].x_lim
        before_y = workspace.state.cells[0].y_lim
        before_y2 = workspace.state.cells[0].y2_lim
        pos, size = geometry['pos'], geometry['size']
        x, y = pos.x + size.x * .6, pos.y + size.y * .5
        io = imgui.get_io()
        io.add_mouse_pos_event(x, y)
        render()
        io.add_mouse_wheel_event(0., 1.)
        render()
        assert workspace.follow and not workspace.paused
        assert workspace.window_seconds < before[1] - before[0]
        zoom_y = workspace.state.cells[0].y_lim
        zoom_y2 = workspace.state.cells[0].y2_lim
        assert zoom_y[1] - zoom_y[0] < before_y[1] - before_y[0]
        assert zoom_y2 == pytest.approx(before_y2)  # Native wheel acts on the primary Y axis.
        depth = workspace.window_seconds
        # New samples arrive; the zoomed duration stays fixed at the newest sample.
        workspace.controller.update = replace(workspace.controller.update, revision=2,
                                              source=LiveSource(frame(1000, 11000)))
        render()
        lo, hi = workspace.state.cells[0].x_lim
        assert hi == pytest.approx(10.999)
        assert hi - lo == pytest.approx(depth)
        io.add_mouse_button_event(implot.get_input_map().pan, True)
        render()
        io.add_mouse_pos_event(x + 140, y)
        render()
        io.add_mouse_button_event(implot.get_input_map().pan, False)
        render()
        assert not workspace.follow and workspace.paused
        held = workspace.run.source
        held_limits = workspace.state.cells[0].x_lim
        workspace.controller.update = replace(workspace.controller.update, revision=3,
                                              source=LiveSource(frame(2000, 12000)))
        render()
        assert workspace.run.source is held
        assert workspace.state.cells[0].x_lim == pytest.approx(held_limits)
        workspace.resume_live()
        render()
        assert workspace.follow and not workspace.paused
        assert workspace.run.source is not held
        assert workspace.state.cells[0].x_lim[1] == pytest.approx(11.999)
    finally:
        workspace.close()


def test_native_box_selection_enters_inspect(gui_frame, app_state):
    from imgui_bundle import imgui, implot
    workspace = LiveWorkspace(LiveController())
    workspace.state.services.display.synchronous = True
    geometry = {}
    original = workspace.plots._time_series_input
    def capture(state, index, cell, lo, hi):
        geometry['pos'], geometry['size'] = implot.get_plot_pos(), implot.get_plot_size()
        original(state, index, cell, lo, hi)
    workspace.plots._time_series_input = capture
    panel = SimpleNamespace(render=workspace.render_plots)
    try:
        workspace.controller.update = LiveUpdate(1, source=LiveSource(frame(0, 10000)), epoch=('run', 0))
        workspace.pump()
        workspace.state.cells[0].add((workspace.run.id, 'a'))
        for _ in range(3): gui_frame(panel, app_state)
        pos, size = geometry['pos'], geometry['size']
        io = imgui.get_io()
        io.add_mouse_pos_event(pos.x + size.x * .2, pos.y + size.y * .2)
        gui_frame(panel, app_state)
        io.add_mouse_wheel_event(0., 1.)
        gui_frame(panel, app_state)
        assert workspace.follow
        old_y = workspace.state.cells[0].y_lim
        io.add_key_event(imgui.Key.mod_shift, True)
        io.add_mouse_button_event(1, True)
        gui_frame(panel, app_state)
        io.add_mouse_pos_event(pos.x + size.x * .6, pos.y + size.y * .7)
        gui_frame(panel, app_state)
        io.add_mouse_button_event(1, False)
        io.add_key_event(imgui.Key.mod_shift, False)
        gui_frame(panel, app_state)
        gui_frame(panel, app_state)
        assert not workspace.follow and workspace.paused
        new_y = workspace.state.cells[0].y_lim
        assert new_y == pytest.approx(old_y)  # Preserve native Shift selection constraints.
        lo, hi = workspace.state.cells[0].x_lim
        assert hi - lo < 1.5
        assert workspace.window_seconds == pytest.approx(hi - lo)
        depth = workspace.window_seconds
        workspace.resume_live()
        gui_frame(panel, app_state)
        lo, hi = workspace.state.cells[0].x_lim
        assert hi - lo == pytest.approx(depth)
        assert hi == pytest.approx(workspace.run.source.metadata.time_range[1])
    finally:
        workspace.close()


def test_normal_box_zoom_keeps_follow_and_uses_normal_input_map(gui_frame, app_state):
    from imgui_bundle import imgui, implot
    workspace = LiveWorkspace(LiveController())
    workspace.state.services.display.synchronous = True
    fields = ('pan', 'select', 'select_mod', 'select_cancel', 'select_vert_mod', 'fit')
    original_mapping = {name: getattr(implot.get_input_map(), name) for name in fields}
    geometry = {}
    original = workspace.plots._time_series_input
    def capture(state, index, cell, lo, hi):
        geometry['pos'], geometry['size'] = implot.get_plot_pos(), implot.get_plot_size()
        assert {name: getattr(implot.get_input_map(), name) for name in fields} == original_mapping
        original(state, index, cell, lo, hi)
    workspace.plots._time_series_input = capture
    panel = SimpleNamespace(render=workspace.render_plots)
    def render():
        workspace.pump()
        gui_frame(panel, app_state)
        assert {name: getattr(implot.get_input_map(), name) for name in fields} == original_mapping
    try:
        workspace.controller.update = LiveUpdate(1, source=LiveSource(frame(0, 10000)), epoch=('run', 0))
        workspace.pump()
        workspace.state.cells[0].add((workspace.run.id, 'a'))
        for _ in range(3): render()
        cell = workspace.state.cells[0]
        before_x, before_y = cell.x_lim, cell.y_lim
        pos, size = geometry['pos'], geometry['size']
        io = imgui.get_io()
        io.add_mouse_pos_event(pos.x + size.x * .2, pos.y + size.y * .2)
        render()
        io.add_mouse_button_event(implot.get_input_map().select, True)
        render()
        io.add_mouse_pos_event(pos.x + size.x * .6, pos.y + size.y * .7)
        render()
        assert workspace.follow and not workspace.paused
        held = workspace.run.source
        workspace.controller.update = replace(workspace.controller.update, revision=2,
                                              source=LiveSource(frame(1000, 11000)))
        render()
        assert workspace.run.source is not held
        io.add_mouse_button_event(implot.get_input_map().select, False)
        render()
        render()
        assert workspace.follow and not workspace.paused
        assert cell.x_lim[1] - cell.x_lim[0] < .7 * (before_x[1] - before_x[0])
        assert cell.y_lim[1] - cell.y_lim[0] < .7 * (before_y[1] - before_y[0])
        assert cell.x_lim[1] == pytest.approx(10.999)
        depth = workspace.window_seconds
        workspace.controller.update = replace(workspace.controller.update, revision=3,
                                              source=LiveSource(frame(2000, 12000)))
        render()
        assert cell.x_lim[1] == pytest.approx(11.999)
        assert cell.x_lim[1] - cell.x_lim[0] == pytest.approx(depth)
    finally:
        workspace.close()


def test_shift_wheel_inspects_with_normal_mouse_controls(gui_frame, app_state):
    from imgui_bundle import imgui, implot
    workspace = LiveWorkspace(LiveController())
    workspace.state.services.display.synchronous = True
    geometry = {}
    original = workspace.plots._time_series_input
    def capture(state, index, cell, lo, hi):
        geometry['pos'], geometry['size'] = implot.get_plot_pos(), implot.get_plot_size()
        original(state, index, cell, lo, hi)
    workspace.plots._time_series_input = capture
    panel = SimpleNamespace(render=workspace.render_plots)
    try:
        workspace.controller.update = LiveUpdate(1, source=LiveSource(frame(0, 10000)), epoch=('run', 0))
        workspace.pump()
        workspace.state.cells[0].add((workspace.run.id, 'a'))
        for _ in range(3): gui_frame(panel, app_state)
        pos, size = geometry['pos'], geometry['size']
        io = imgui.get_io()
        io.add_mouse_pos_event(pos.x + size.x * .5, pos.y + size.y * .5)
        gui_frame(panel, app_state)
        io.add_key_event(imgui.Key.mod_shift, True)
        io.add_mouse_wheel_event(0., 1.)
        gui_frame(panel, app_state)
        io.add_key_event(imgui.Key.mod_shift, False)
        gui_frame(panel, app_state)
        assert not workspace.follow and workspace.paused
        held, limits = workspace.run.source, workspace.state.cells[0].x_lim
        workspace.controller.update = replace(workspace.controller.update, revision=2,
                                              source=LiveSource(frame(1000, 11000)))
        workspace.pump()
        gui_frame(panel, app_state)
        assert workspace.run.source is held
        assert workspace.state.cells[0].x_lim == pytest.approx(limits)
    finally:
        workspace.close()
