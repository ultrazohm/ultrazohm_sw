"""Bounded live snapshots, worker recovery, and real ImGui panel rendering."""
from dataclasses import replace
from types import SimpleNamespace
import time

import numpy as np
import polars as pl
import pytest

from live_support import ports, wait_for

from uz_dataviewer.live import LiveController, LiveSource, LiveUpdate, fuzzy_names
from uz_dataviewer.panels.live import LiveWorkspace
from uz_dataviewer.sources import TimeShift, shift_time


def frame(start, stop):
    t = np.arange(start, stop, dtype=np.float64) * .001
    return pl.DataFrame({'time': t, 'status': np.ones(len(t), np.uint32),
                         'a': np.sin(t).astype(np.float32), 'b': np.cos(t).astype(np.float32)})




class FakeClient:
    def __init__(self):
        self.end = 30
        self.generation = 0
        self.connected = True
        self.calls = []

    def status(self):
        return {'state': {'connected': self.connected, 'platform_state': 'idle',
                          'device': '192.168.1.233:1000'},
                'data_options': {'buffer_samples': 100}, 'logging': {}}

    def catalog(self):
        return {'profile': {'observables': {'a': 1, 'b': 2}, 'variables': {'setpoint': 4},
                            'sample_period_us': 1000}}

    def observables(self):
        return {'channels': [{'channel': 1, 'name': 'a'}, {'channel': 2, 'name': 'b'}]}

    def read_since(self, cursor=None, limit=100):
        first = max(0, self.end - 100)
        if cursor and (cursor['generation'] != self.generation or cursor['next_sample'] < first):
            raise RuntimeError('expired cursor')
        start = cursor['next_sample'] if cursor else first
        stop = min(start + limit, self.end)
        return SimpleNamespace(data=frame(start, stop),
            cursor={'next_sample': stop, 'generation': self.generation},
            info={'run_id': 'fake', 'generation': self.generation})

    def shutdown(self):
        self.calls.append(('shutdown',))

    def stop(self):
        self.calls.append(('stop',))

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
        client.end = 80
        second = wait_for(lambda: (s if (s := controller.latest().source).metadata.rows == 80 else None))
        assert first.metadata.rows == 30  # old display/analysis readers stay immutable
        assert second.time[-1] == pytest.approx(.079)
        client.end = 500  # Advance beyond the retained window.
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


def test_variable_send_feedback_only_follows_successful_command():
    class Client(FakeClient):
        def set_variable(self, name, value):
            if value < 0:
                raise RuntimeError('send failed')
    controller = LiveController(lambda _: Client(), hz=100)
    try:
        controller.submit('attach', endpoint='fake')
        wait_for(lambda: controller.latest().attached)
        controller.submit('set_variable', name='setpoint', value=3.)
        sent = wait_for(lambda: controller.latest().variable_sends.get('setpoint'))
        assert sent[1] == 3.
        previous = controller.latest()
        controller.submit('set_variable', name='setpoint', value=-1.)
        wait_for(lambda: 'send failed' in controller.latest().error)
        assert controller.latest().variable_sends['setpoint'] == sent
        controller.submit('set_variable', name='setpoint', value=4.)
        wait_for(lambda: controller.latest().variable_sends.get('setpoint', (0, 0))[1] == 4.)
        assert previous.variable_sends['setpoint'] == sent
    finally:
        controller.close()


def test_attach_reports_mapping_mismatch_without_reconfiguring_service(tmp_path):
    import json
    client = FakeClient()
    controller = LiveController(lambda _: client)
    path = tmp_path/'generated.json'
    path.write_text(json.dumps({'observables': {'new_signal': 42}}))
    try:
        controller._command('attach', {'endpoint': 'fake', 'mapping': str(path)})
        assert controller.attached
        assert 'different channel mapping' in controller._notice
        assert client.calls == []
        path.write_text(json.dumps(client.catalog()['profile']))
        controller._command('attach', {'endpoint': 'fake', 'mapping': str(path)})
        assert 'different channel mapping' not in controller._notice
    finally:
        controller.close()


@pytest.mark.parametrize('device,ip,port,matches', [
    ('192.168.1.233:1000', '192.168.1.233', 1000, True),
    ('192.168.1.111:1000', '192.168.1.233', 1000, False),
    ('192.168.1.233:2000', '192.168.1.233', 1000, False),
    ('[::1]:1000', '0:0:0:0:0:0:0:1', 1000, True),
    ('', '192.168.1.233', 1000, False),
])
def test_connect_verifies_existing_device(device, ip, port, matches):
    class Client(FakeClient):
        def status(self):
            value = super().status()
            value['state']['device'] = device
            return value
    controller = LiveController(lambda _: Client())
    try:
        controller.owned.endpoint = 'fake'
        controller.owned.process = SimpleNamespace(poll=lambda: None, wait=lambda: 0)
        request = {'endpoint': 'fake', 'ip': ip, 'port': port}
        if matches:
            controller._command('connect', request)
            assert controller.attached
        else:
            with pytest.raises(RuntimeError, match='Service is already connected'):
                controller._command('connect', request)
            assert not controller.attached
    finally:
        controller.close()


@pytest.mark.parametrize('script_busy', [False, True])
def test_script_stop_discards_queued_commands_while_poll_is_blocked(script_busy):
    import threading
    entered, release, stopped = threading.Event(), threading.Event(), threading.Event()
    class Client(FakeClient):
        def read_since(self, *args, **kwargs):
            entered.set()
            assert release.wait(5)
            return super().read_since(*args, **kwargs)
        def enable_control(self): self.calls.append(('enable_control',))
        def stop(self):
            super().stop()
            stopped.set()
    client = Client()
    workspace = LiveWorkspace(LiveController(lambda _: client, hz=100))
    controller = workspace.controller
    # A running process is unnecessary: exercise the same busy Stop path while
    # preserving ScriptRunner's real independent Stop thread and callback.
    class Process:
        def poll(self): return 0
    if script_busy:
        workspace.scripts.process = Process()
        workspace.scripts.endpoint = 'fake'
    try:
        controller.submit('attach', endpoint='fake')
        assert entered.wait(3)
        controller.submit('enable_control')
        workspace.send('stop')
        assert stopped.wait(2)
        assert not release.is_set()
        release.set()
        wait_for(lambda: controller.latest().revision > 3)
        assert client.calls == [('stop',)]
        assert controller.commands.empty()
    finally:
        release.set()
        workspace.close()


def test_stop_follows_inflight_control_and_cancels_next_command():
    import threading
    entered, release, stopped = threading.Event(), threading.Event(), threading.Event()
    class Client(FakeClient):
        def enable_system(self):
            entered.set()
            assert release.wait(5)
            self.calls.append(('enable_system',))
        def enable_control(self): self.calls.append(('enable_control',))
        def stop(self):
            super().stop()
            stopped.set()
    client = Client()
    controller = LiveController(lambda _: client, hz=100)
    try:
        controller.submit('attach', endpoint='fake')
        wait_for(lambda: controller.latest().attached)
        controller.submit('enable_system')
        assert entered.wait(3)
        controller.submit('enable_control')
        controller.cancel_pending_commands()
        stopper = threading.Thread(target=controller.send_stop)
        stopper.start()
        assert not stopped.wait(.05)
        release.set()
        assert stopped.wait(2)
        stopper.join()
        assert client.calls == [('enable_system',), ('stop',)]
    finally:
        release.set()
        controller.close()


def test_script_start_cancels_queue_and_rejects_inflight_command(monkeypatch, tmp_path):
    controller = LiveController(lambda _: FakeClient())
    workspace = LiveWorkspace(controller)
    started = []
    monkeypatch.setattr(workspace.scripts, 'start', lambda *args: started.append(args))
    try:
        controller._command('attach', {'endpoint': 'fake'})
        controller._publish()
        workspace.pump()
        controller.commands.put((controller._command_generation, 'enable_system', {}))
        with controller._command_lock:
            workspace._start_script(tmp_path/'script.py', 'fake')
            assert not started
            assert 'still running' in workspace.document.error
            assert controller.commands.empty()
        workspace._start_script(tmp_path/'script.py', 'fake')
        assert len(started) == 1
    finally:
        workspace.close()


def test_close_waits_for_stop_without_script_or_logging_changes():
    import threading
    entered, release = threading.Event(), threading.Event()
    class Client(FakeClient):
        def stop(self):
            entered.set()
            assert release.wait(5)
            super().stop()
    client = Client()
    controller = LiveController(lambda _: client)
    controller._command('attach', {'endpoint': 'fake'})
    closer = threading.Thread(target=controller.close)
    closer.start()
    try:
        assert entered.wait(2)
        assert closer.is_alive()
    finally:
        release.set()
        closer.join(3)
    assert not closer.is_alive()
    assert client.calls == [('stop',)]
    controller.close()  # Idempotent shutdown sends Stop once.
    assert client.calls == [('stop',)]


@pytest.mark.parametrize('disconnect_first', [False, True])
def test_viewer_owned_service_finalizes_and_exits_on_close(tmp_path, disconnect_first):
    """Exercise the actual wheel/IPC and detached service against the simulator."""
    from pathlib import Path
    import socket
    import subprocess
    import sys
    native = pytest.importorskip('ultrazohm')
    root = Path(__file__).resolve().parents[2]
    device_port, service_port = ports()
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
            completed = controller.latest().completed_commands
            controller.submit(operation)
            wait_for(lambda: controller.latest().completed_commands > completed)
        controller.submit('button', number=1)
        variable = next(iter(controller.latest().catalog['variables']))
        controller.submit('set_variable', name=variable, value=1.25)
        controller.submit('start_logging')
        wait_for(lambda: controller.latest().status.get('logging', {}).get('fast', {}).get('phase') == 'recording')
        controller.submit('set_observable', name='JSO_lifecheck', channel=2)
        wait_for(lambda: 'logging' in controller.latest().error)
        before = client.status()['state']['samples']
        wait_for(lambda: client.status()['state']['samples'] > before + 1500)
        if disconnect_first:
            controller.submit('shutdown')
            wait_for(lambda: controller.owned.process.poll() == 0 and not controller.latest().activity)
            assert not controller.stop_event.is_set()
        else:
            controller.close()
        assert controller.owned.process.poll() == 0
        import json
        end = json.loads((tmp_path/'recording/end.json').read_text())
        assert end['complete']
        recorded = pl.read_parquet(tmp_path/'recording/data.parquet')
        assert recorded.height > 1000
        assert 'JSO_lifecheck' in recorded.columns
        import json
        events = [json.loads(line) for line in (tmp_path/'recording/commands.jsonl').read_text().splitlines()]
        text = json.dumps(events)
        for operation in ('enable_system', 'enable_control', 'stop', 'button', 'set_variable', 'shutdown'):
            assert operation in text
        if disconnect_first:
            controller.submit('connect', endpoint=client.endpoint, ip='127.0.0.1', port=device_port,
                              output=str(tmp_path/'second-recording'))
            wait_for(lambda: controller.latest().attached and controller.latest().source, seconds=12)
            controller.close()
            assert controller.owned.process.poll() == 0
    finally:
        controller.close()
        if controller.owned.process is not None:
            try:
                client.shutdown()
                controller.owned.process.wait(timeout=15)
            except (OSError, RuntimeError, subprocess.TimeoutExpired):
                controller.owned.process.terminate()
                controller.owned.process.wait(timeout=5)
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
    controller.owned.endpoint = '127.0.0.1:19740'
    controller.owned.process = SimpleNamespace(poll=lambda: None, wait=lambda: 0)
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
    workspace.controller.owned.endpoint = workspace.endpoint
    workspace.controller.owned.process = SimpleNamespace(poll=lambda: None, wait=lambda: 0)
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


@pytest.mark.parametrize('attached', [False, True])
def test_close_shuts_down_owned_service_even_when_detached(attached):
    calls = []
    class Client:
        def shutdown(self): calls.append('shutdown')
    class Process:
        def poll(self): return None
        def wait(self):
            calls.append('wait')
            return 0
    controller = LiveController(lambda endpoint: Client())
    controller.owned.process = Process()
    controller.endpoint = controller.owned.endpoint = '127.0.0.1:19740'
    controller.attached = attached
    controller._status = {'state': {'connected': True}}
    controller.close()
    assert calls == ['shutdown', 'wait']
    controller.close()
    assert calls == ['shutdown', 'wait']


def test_connect_rejects_external_service_without_changing_device():
    client = FakeClient()
    controller = LiveController(lambda _: client)
    with pytest.raises(RuntimeError, match='Existing service > Attach'):
        controller._command('connect', {'endpoint': 'external'})
    assert not controller.attached
    assert client.calls == []
    controller.close()


@pytest.mark.parametrize('fail_stop', [False, True])
def test_close_handles_both_services_independently(fail_stop):
    calls = []
    class Client:
        def __init__(self, endpoint): self.endpoint = endpoint
        def stop(self):
            calls.append((self.endpoint, 'stop'))
            if fail_stop:
                raise RuntimeError('stop failure')
        def shutdown(self): calls.append((self.endpoint, 'shutdown'))
    class Process:
        def poll(self): return None
        def wait(self):
            calls.append(('owned', 'wait'))
            return 1
    controller = LiveController(Client)
    controller.endpoint = 'external'
    controller.owned.endpoint = 'owned'
    controller.owned.process = Process()
    controller.attached = True
    controller._status = {'state': {'connected': True}}
    controller.close()
    assert calls == [('external', 'stop'), ('owned', 'shutdown'), ('owned', 'wait')]


def test_disconnect_button_requests_shutdown_and_keeps_viewer_open(gui_frame, app_state, monkeypatch):
    from imgui_bundle import imgui
    controller = LiveController(lambda _: FakeClient())
    workspace = LiveWorkspace(controller)
    workspace.available = True
    workspace.update = replace(workspace.update, attached=True, status={'state': {'connected': True}})
    sent = []
    monkeypatch.setattr(controller, 'submit', lambda operation, **kwargs: sent.append(operation))
    monkeypatch.setattr(imgui, 'button', lambda label, *args, **kwargs: label == 'Disconnect')
    old_output = workspace.output
    try:
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
        assert sent == ['shutdown']
        assert workspace.output != old_output
        assert not controller.stop_event.is_set()
    finally:
        workspace.close()


def test_unused_controller_closes_without_optional_cli_wheel(monkeypatch):
    import sys
    monkeypatch.setitem(sys.modules, 'ultrazohm', None)
    controller = LiveController()
    controller.close()
    controller.close()
    assert controller.stop_event.is_set()
