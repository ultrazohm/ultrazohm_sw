"""Measurement scripts use real process isolation and the same service API."""
from pathlib import Path
from types import SimpleNamespace
import socket
import subprocess
import sys
import time

import pytest

from uz_dataviewer.live import LiveController
from uz_dataviewer.panels.live import LiveWorkspace
from uz_dataviewer.scripting import ScriptRunner, TEMPLATES


def wait_for(fn, seconds=8):
    deadline = time.monotonic() + seconds
    while time.monotonic() < deadline:
        if value := fn():
            return value
        time.sleep(.01)
    raise AssertionError('condition timed out')


@pytest.fixture
def service(tmp_path):
    native = pytest.importorskip('ultrazohm')
    def port():
        with socket.socket() as sock:
            sock.bind(('127.0.0.1', 0))
            return sock.getsockname()[1]
    device_port, service_port = port(), port()
    root = Path(__file__).resolve().parents[2]
    simulator = subprocess.Popen([sys.executable, str(root/'javascope/test_server.py'),
        '--port', str(device_port), '--sample-rate', '1000'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    endpoint = f'127.0.0.1:{service_port}'
    acquisition = None
    try:
        acquisition = native.Acquisition(endpoint=endpoint, output=str(tmp_path/'recordings'), format='parquet')
        client = native.Client(endpoint)
        def connect():
            try:
                client.connect('127.0.0.1', device_port)
                return True
            except RuntimeError:
                return False
        wait_for(connect)
        yield client, endpoint
    finally:
        if acquisition is not None:
            acquisition.close()
        simulator.terminate()
        simulator.wait(timeout=5)


def test_script_import_completion_error_and_stop_preserve_logging(tmp_path, service):
    client, endpoint = service
    path = tmp_path/'sequence with spaces.py'
    (tmp_path/'helpers.py').write_text('def configure(uz):\n    uz.set_variable("send_field_1", 12.5)\n')
    runner = ScriptRunner()
    def finished():
        runner.poll()
        return not runner.busy
    try:
        path.write_text('from helpers import configure\n'
            'def run(uz):\n'
            '    configure(uz)\n'
            '    uz.enable_system()\n'
            '    uz.enable_control()\n'
            '    uz.start_logging()\n'
            '    print("sequence completed")\n')
        runner.start(path, endpoint)
        wait_for(finished)
        assert 'Completed' in runner.message
        assert 'sequence completed' in runner.output
        assert client.status()['logging']['fast']['phase'] == 'recording'
        commands = client.status()['state']['commands_sent']
        path.write_text('def run(uz):\n    raise ValueError("example error")\n')
        runner.start(path, endpoint)
        wait_for(finished)
        assert 'failed' in runner.message
        assert 'ValueError: example error' in runner.output
        assert client.status()['logging']['fast']['phase'] == 'recording'
        assert client.status()['state']['commands_sent'] == commands
        path.write_text('import time\ndef run(uz):\n    print("waiting", flush=True)\n    while True:\n        time.sleep(.01)\n')
        runner.start(path, endpoint)
        wait_for(lambda: (runner.poll(), 'waiting' in runner.output)[1])
        runner.stop()
        wait_for(finished)
        assert 'device Stop sent' in runner.message
        assert client.status()['state']['commands_sent'] == commands + 1
        assert client.status()['logging']['fast']['phase'] == 'recording'
    finally:
        runner.close()


def test_editor_and_manual_controls_lock(gui_frame, app_state, tmp_path):
    controller = LiveController(lambda _: None)
    workspace = LiveWorkspace(controller)
    class ActiveRunner:
        busy = True
        message = 'Running'
        output = 'hello'
        def __init__(self): self.stops = 0
        def stop(self): self.stops += 1
        def close(self): pass
    runner = ActiveRunner()
    workspace.scripts = runner
    try:
        workspace.send('set_variable', name='send_field_1', value=1)
        assert 'locked' in workspace.error
        assert controller.commands.empty()
        workspace.send('stop')
        assert runner.stops == 1
        assert controller.commands.empty()
        workspace.update = SimpleNamespace(status={'state': {'connected': True}}, attached=True,
                                           catalog={}, error='')
        gui_frame(SimpleNamespace(render=lambda _: workspace.render_python()), app_state)
        editor = workspace.script_editor
        assert editor.get_language_name().lower() == 'python'
        assert editor.is_show_line_numbers_enabled()
        assert editor.is_auto_indent_enabled()
        assert editor.is_insert_spaces_on_tabs()
        assert editor.get_tab_size() == 4
        assert editor.is_read_only_enabled()
        gui_frame(SimpleNamespace(render=lambda _: workspace.render_control()), app_state)
        workspace.script_path = str(tmp_path/'saved.py')
        workspace.script_code = TEMPLATES['Timed recording']
        assert editor.get_text() == TEMPLATES['Timed recording']
        assert workspace._save_script().read_text() == workspace.script_code
        runner.busy = False
        gui_frame(SimpleNamespace(render=lambda _: workspace.render_python()), app_state)
        assert not editor.is_read_only_enabled()
        original = workspace.script_code
        editor.set_cursor(editor.DocPos(0, 0))
        editor.replace_text_in_current_cursor('# edited in the code editor\n')
        assert editor.can_undo()
        gui_frame(SimpleNamespace(render=lambda _: workspace.render_python()), app_state)
        assert workspace.script_editor is editor
        assert editor.can_undo()  # Rendering must preserve text, cursor, and undo history.
        assert workspace._save_script().read_text().startswith('# edited in the code editor\n')
        editor.undo()
        assert workspace.script_code == original
    finally:
        workspace.close()


def test_stop_uses_independent_control_path_while_poll_blocks(tmp_path, service):
    import threading
    client, endpoint = service
    entered, release = threading.Event(), threading.Event()
    class BlockedPoll:
        def status(self):
            return {'state': {'connected': True}, 'data_options': {'buffer_samples': 100}}
        def stop(self): client.stop()
        def catalog(self): return {'profile': {}}
        def observables(self): return {'channels': []}
        def read_since(self, *args, **kwargs):
            entered.set()
            release.wait(8)
            raise OSError('closed test poll')
    controller = LiveController(lambda _: BlockedPoll())
    workspace = LiveWorkspace(controller)
    path = tmp_path/'wait.py'
    path.write_text('import time\ndef run(uz):\n    print("waiting", flush=True)\n    time.sleep(60)\n')
    try:
        controller.submit('attach', endpoint=endpoint)
        assert entered.wait(3)
        workspace.scripts.start(path, endpoint)
        def started():
            workspace.scripts.poll()
            return 'waiting' in workspace.scripts.output
        wait_for(started)
        before = client.status()['state']['commands_sent']
        workspace.send('stop')
        def stopped():
            workspace.scripts.poll()
            return not workspace.scripts.busy
        wait_for(stopped, seconds=3)
        assert not release.is_set()  # Poll remains blocked throughout the Stop.
        assert client.status()['state']['commands_sent'] == before + 1
        assert controller.commands.empty()
    finally:
        release.set()
        workspace.close()


def test_close_waits_for_inflight_script_stop():
    import threading
    entered, release, sent, closed = (threading.Event() for _ in range(4))
    class Client:
        def stop(self):
            entered.set()
            assert release.wait(5)
            sent.set()
    runner = ScriptRunner(lambda _: Client())
    runner.endpoint = 'fake'
    runner.stop()
    assert entered.wait(2)
    def close():
        runner.close()
        closed.set()
    closer = threading.Thread(target=close)
    closer.start()
    try:
        assert not sent.is_set()
        # Shutdown used to return after a one-second join, abandoning the
        # daemon Stop thread when the Python process exited.
        assert not closed.wait(1.1)
    finally:
        release.set()
        closer.join(3)
    assert sent.is_set()
    assert not closer.is_alive()
    assert not runner.busy


def test_sine_template_uses_wall_clock_ramps_and_exact_endpoints():
    namespace = {}
    exec(compile(TEMPLATES['Sine sweep (30 s)'], '<sine-template>', 'exec'), namespace)
    class Clock:
        now = 0.
        def monotonic(self): return self.now
        def sleep(self, duration):
            assert duration >= 0
            self.now += duration
    clock = Clock()
    class Device:
        def __init__(self):
            self.calls = []
            self.tail_calls = 0
        def catalog(self):
            return {'profile': {'observables': dict.fromkeys(
                ('JSO_SineDemo', 'JSO_SineDemoAmplitude', 'JSO_SineDemoFrequency_Hz'))}}
        def status(self): return {'logging': {'fast': {'phase': 'idle'}, 'slow': {'phase': 'idle'}}}
        def observables(self): return {'channels': []}
        def set_variable(self, name, value):
            self.calls.append((clock.now, name, value))
            clock.now += .003  # Command latency must not accumulate in the ramp duration.
        def set_observable(self, name, channel): self.calls.append(('observable', name, channel))
        def start_logging(self): self.started = clock.now
        def stop_logging(self): self.stopped = clock.now
        def tail(self, n, channels):
            self.tail_calls += 1
            return {'JSO_SineDemoAmplitude': [10.],
                    'JSO_SineDemoFrequency_Hz': [49. if self.tail_calls < 3 else 50.]}
    device = Device()
    namespace['time'] = clock
    namespace['run'](device)
    assert device.stopped - device.started == pytest.approx(30.02, abs=.01)
    assert device.tail_calls == 3
    amplitude = [(t, v) for t, n, v in device.calls if n == 'send_field_19']
    frequency = [(t, v) for t, n, v in device.calls if n == 'send_field_20']
    assert amplitude[0][1] == 0. and amplitude[-1][1] == 10.
    assert frequency[0][1] == 10. and frequency[-1][1] == 50.
    for t, value in amplitude[1:]:
        assert value == pytest.approx(min(10., (t - device.started) * 10. / 15.))
    for t, value in frequency[1:]:
        assert value == pytest.approx(min(50., 10. + (t - device.started - 15.) * 40. / 15.))
    clock = Clock()
    namespace['time'] = clock
    failed = Device()
    failed.tail = lambda n, channels: {'JSO_SineDemoAmplitude': [10.], 'JSO_SineDemoFrequency_Hz': [49.]}
    with pytest.raises(RuntimeError, match='logging remains active'):
        namespace['run'](failed)
    assert not hasattr(failed, 'stopped')


def test_managed_flash_restarts_real_service_and_preserves_recordings(service, tmp_path, monkeypatch):
    from pathlib import Path
    import json
    from uz_dataviewer import flashing
    client, endpoint = service
    old_assignments = client.observables()['channels']
    options = client.status()['data_options']
    client.start_logging()
    client.start_logging_slow_data()
    wait_for(lambda: client.status()['state']['samples'] > 100)
    recordings = client.status()['logging']
    controller = LiveController(hz=30)
    monkeypatch.setattr(flashing, 'run_flash_cli', lambda *args: True)
    monkeypatch.setattr(flashing, 'xsct_available', lambda: True)
    try:
        controller.submit('attach', endpoint=endpoint)
        wait_for(lambda: controller.latest().attached)
        controller.submit('flash', endpoint=endpoint, ip='127.0.0.1', port=1,
                          repo=str(Path(__file__).resolve().parents[2]), output=str(tmp_path/'initial'))
        wait_for(lambda: 'Flash completed' in controller.latest().notice, seconds=20)
        assert not controller.flashing
        status = client.status()
        assert status['state']['connected']
        assert all(v['phase'] == 'idle' for v in status['logging'].values())
        assert status['data_options'] == options
        assert client.observables()['channels'] == old_assignments
        mapping, output = controller.latest().flash_config
        assert client.catalog()['profile']['observables'] == json.loads(Path(mapping).read_text())['observables']
        assert Path(output).is_dir()
        for info in recordings.values():
            assert Path(info['parquet']).is_file()
            metadata = Path(info['parquet']).with_suffix('.json')
            assert json.loads(metadata.read_text())['complete']
    finally:
        controller.close()
        try:
            client.shutdown()
        except (OSError, RuntimeError):
            pass
        if controller.process is not None:
            try:
                controller.process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                controller.process.kill()
                controller.process.wait()
