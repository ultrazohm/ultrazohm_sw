"""Measurement scripts use real process isolation and the same service API."""
from pathlib import Path
from types import SimpleNamespace
import subprocess
import sys
import time

import pytest
from functools import partial
from live_support import ports, wait_for as wait_for_condition

wait_for = partial(wait_for_condition, seconds=8)

from uz_dataviewer.live import LiveController
from uz_dataviewer.panels.live import LiveWorkspace
from uz_dataviewer.scripting import ScriptRunner, TEMPLATES


def test_generic_script_arguments_directory_and_endpoints(tmp_path):
    import json
    script_dir = tmp_path / 'scripts'
    script_dir.mkdir()
    working = tmp_path / 'working directory'
    working.mkdir()
    script = script_dir / 'inspect.py'
    script.write_text('import json, os, sys\n'
                      'from uz_dataviewer import Client\n'
                      'print(json.dumps([sys.argv[1:], os.getcwd(), '
                      'os.environ["UZ_DATAVIEWER_ENDPOINT"], '
                      'os.environ["UZ_ACQUISITION_ENDPOINT"]]))\n')
    runner = ScriptRunner(device_control=False)
    try:
        runner.start(script, '127.0.0.1:19740', viewer_endpoint='127.0.0.1:19742',
                     args=['recording with spaces.csv', '--literal=$(echo nope)'], cwd=working)
        def finished():
            runner.poll()
            return not runner.busy
        wait_for(finished)
        assert runner.exit_code == 0, runner.output
        assert json.loads(runner.output) == [
            ['recording with spaces.csv', '--literal=$(echo nope)'], str(working),
            '127.0.0.1:19742', '127.0.0.1:19740']
    finally:
        runner.close()


def test_script_rejects_missing_working_directory_before_start(tmp_path):
    runner = ScriptRunner(device_control=False)
    with pytest.raises(ValueError, match='Working directory'):
        runner.start(tmp_path / 'script.py', cwd=tmp_path / 'missing')
    assert not runner.busy


def test_combined_template_controls_both_existing_services(tmp_path, service, control_session):
    _, acquisition_endpoint = service
    _, viewer, _, pump = control_session
    path = tmp_path / 'combined.py'
    path.write_text(TEMPLATES['Viewer and device status'])
    runner = ScriptRunner(device_control=False)
    try:
        runner.start(path, acquisition_endpoint, viewer_endpoint=viewer.endpoint)
        def finished():
            runner.poll()
            return not runner.busy
        pump(finished)
        assert runner.exit_code == 0, runner.output
        assert 'Viewer:' in runner.output
        assert 'Device:' in runner.output
    finally:
        runner.close()




@pytest.fixture
def service(tmp_path):
    native = pytest.importorskip('ultrazohm_cli')
    device_port, service_port = ports()
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
            'import argparse\nfrom ultrazohm_cli import Client\n'
            'if __name__ == "__main__":\n'
            '    parser = argparse.ArgumentParser()\n'
            '    import os\n    parser.add_argument("--endpoint", default=os.environ["UZ_ACQUISITION_ENDPOINT"])\n'
            '    uz = Client(parser.parse_args().endpoint)\n'
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
        path.write_text('raise ValueError("example error")\n')
        runner.start(path, endpoint)
        wait_for(finished)
        assert 'failed' in runner.message
        assert 'ValueError: example error' in runner.output
        assert client.status()['logging']['fast']['phase'] == 'recording'
        assert client.status()['state']['commands_sent'] == commands
        path.write_text('import time\nprint("waiting", flush=True)\nwhile True:\n    time.sleep(.01)\n')
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
    from uz_dataviewer.panels.python import PythonPanel
    panel = PythonPanel(SimpleNamespace(live=workspace, control_server=SimpleNamespace(endpoint='127.0.0.1:19741')))
    panel.managed_device = True
    try:
        workspace.send('set_variable', name='send_field_1', value=1)
        assert 'locked' in workspace.error
        assert controller.commands.empty()
        workspace.send('stop')
        assert runner.stops == 1
        assert controller.commands.empty()
        workspace.update = SimpleNamespace(status={'state': {'connected': True}}, attached=True,
                                           catalog={}, error='')
        gui_frame(SimpleNamespace(render=lambda _: panel.render()), app_state)
        editor = panel.document.editor
        assert editor.get_language_name().lower() == 'python'
        assert editor.is_show_line_numbers_enabled()
        assert editor.is_auto_indent_enabled()
        assert editor.is_insert_spaces_on_tabs()
        assert editor.get_tab_size() == 4
        assert editor.is_read_only_enabled()
        gui_frame(SimpleNamespace(render=lambda _: workspace.render_control()), app_state)
        panel.document.path = str(tmp_path/'saved.py')
        panel.document.code = TEMPLATES['Timed recording']
        assert editor.get_text() == TEMPLATES['Timed recording']
        assert panel.document.save().read_text() == panel.document.code
        runner.busy = False
        gui_frame(SimpleNamespace(render=lambda _: panel.render()), app_state)
        assert not editor.is_read_only_enabled()
        original = panel.document.code
        editor.set_cursor(editor.DocPos(0, 0))
        editor.replace_text_in_current_cursor('# edited in the code editor\n')
        assert editor.can_undo()
        gui_frame(SimpleNamespace(render=lambda _: panel.render()), app_state)
        assert panel.document.editor is editor
        assert editor.can_undo()  # Rendering must preserve text, cursor, and undo history.
        assert panel.document.save().read_text().startswith('# edited in the code editor\n')
        editor.undo()
        assert panel.document.code == original
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
    path.write_text('import time\nprint("waiting", flush=True)\ntime.sleep(60)\n')
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


def test_managed_flash_restarts_real_service_and_preserves_recordings(service, tmp_path, monkeypatch):
    from pathlib import Path
    import json
    from uz_dataviewer import flashing
    client, endpoint = service
    old_assignments = client.observables()['channels']
    options = client.status()['data_options']
    client.start_logging()
    client.start_logging_slow_data()
    # Acquisition starts in the fixture, before logging is enabled. Its total
    # may already exceed 100: wait for fresh samples in both recording routes.
    baseline = client.status()['state']['samples']
    wait_for(lambda: client.status()['state']['samples'] > baseline + 100)
    # Handles are reported once each writer has created its index.
    def with_handles():
        logging = client.status()['logging']
        return logging if all(info['handle'] for info in logging.values()) else None
    recordings = wait_for(with_handles)
    controller = LiveController(hz=30)
    monkeypatch.setattr(flashing, 'run_flash_cli', lambda *args: True)
    monkeypatch.setattr(flashing, 'xsct_available', lambda: True)
    try:
        controller.submit('attach', endpoint=endpoint)
        wait_for(lambda: controller.latest().attached)
        controller.submit('flash', endpoint=endpoint, ip='127.0.0.1', port=1,
                          repo=str(Path(__file__).resolve().parents[2]), output=str(tmp_path/'initial'))
        def flash_completed():
            update = controller.latest()
            if update.error:
                raise AssertionError(f'Managed flash failed: {update.error}')
            return 'Flash completed' in update.notice
        try:
            wait_for(flash_completed, seconds=20)
        except AssertionError as exc:
            update = controller.latest()
            logs = '\n'.join(f'{path.name}:\n{path.read_text(encoding="utf-8", errors="replace")}'
                             for path in tmp_path.glob('*.service.log'))
            raise AssertionError(
                f'{exc}\nActivity: {update.activity}\nNotice: {update.notice}'
                f'\nController error: {update.error}\nService logs:\n{logs}'
            ) from exc
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
            # The recording summary is stored with its index.
            assert json.loads(Path(info['handle']).read_text())['metadata']['complete']
    finally:
        controller.close()
        try:
            client.shutdown()
        except (OSError, RuntimeError):
            pass
        if controller.owned.process is not None:
            try:
                controller.owned.process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                controller.owned.process.kill()
                controller.owned.process.wait()


def test_script_main_and_arguments_match_terminal_execution(tmp_path):
    import json
    path = tmp_path / 'ordinary script.py'
    (tmp_path / 'helper.py').write_text('VALUE = 42\n')
    path.write_text('import argparse, json, sys\nfrom helper import VALUE\n'
        'assert "uz" not in globals()\n'
        'def run(uz):\n    raise AssertionError("must not be called automatically")\n'
        'if __name__ == "__main__":\n'
        '    p = argparse.ArgumentParser()\n'
        '    import os\n    p.add_argument("--endpoint", default=os.environ.get("UZ_ACQUISITION_ENDPOINT"))\n'
        '    print(json.dumps([p.parse_args().endpoint, VALUE, sys.argv[0]]))\n')
    endpoint = '127.0.0.1:23456'
    expected = subprocess.check_output([sys.executable, str(path), '--endpoint', endpoint], text=True)
    runner = ScriptRunner()
    try:
        runner.start(path, endpoint)
        def finished():
            runner.poll()
            return not runner.busy
        wait_for(finished)
        assert 'Completed' in runner.message
        assert json.loads(runner.output) == json.loads(expected)
    finally:
        runner.close()


def test_windows_bootstrap_preserves_main_and_exit_code(tmp_path):
    # Also runnable on Linux: containment is a no-op there, but argv/main/exit
    # behavior uses the same bootstrap that Windows executes.
    path = tmp_path / 'exit script.py'
    path.write_text('import sys\nassert __name__ == "__main__"\n'
                    'assert sys.argv[1:] == ["--endpoint", "127.0.0.1:23456"]\n'
                    'assert "uz" not in globals()\nsys.exit(7)\n')
    result = subprocess.run([sys.executable, '-m', 'uz_dataviewer.script_worker',
                             str(path), '--endpoint', '127.0.0.1:23456'], capture_output=True, text=True)
    assert result.returncode == 7, result.stderr


@pytest.mark.parametrize('name', ['Device status', 'Timed recording', 'Control sequence'])
def test_templates_are_standalone_scripts_with_endpoint(tmp_path, monkeypatch, name):
    import runpy
    calls = []
    class Client:
        def __init__(self, endpoint): calls.append(('endpoint', endpoint))
        def status(self): return {'connected': True}
        def start_logging(self): calls.append(('start',))
        def stop_logging(self): calls.append(('stop_logging',))
        def set_variable(self, name, value): calls.append(('variable', name, value))
        def enable_system(self): calls.append(('system',))
        def enable_control(self): calls.append(('control',))
    monkeypatch.setitem(sys.modules, 'ultrazohm_cli', SimpleNamespace(Client=Client))
    monkeypatch.setattr(time, 'sleep', lambda duration: None)
    path = tmp_path / 'measurement.py'
    path.write_text(TEMPLATES[name])
    monkeypatch.setattr(sys, 'argv', [str(path), '--endpoint', '127.0.0.1:23456'])
    runpy.run_path(str(path), run_name='__main__')
    assert calls[0] == ('endpoint', '127.0.0.1:23456')
    if name == 'Timed recording':
        assert calls[1:] == [('start',), ('stop_logging',)]
    if name == 'Control sequence':
        assert calls[1:] == [('variable', 'send_field_1', 0.0), ('system',), ('control',)]


def test_script_output_is_read_only_after_the_log_grows(tmp_path):
    runner = ScriptRunner()
    runner._log = tmp_path / 'output.log'
    runner._log.write_bytes(b'first\n')
    runner.poll()
    assert runner.output == 'first\n'
    runner.output = 'unchanged'  # A poll without new output must not re-read the file.
    runner.poll()
    assert runner.output == 'unchanged'
    with runner._log.open('ab') as log:
        log.write(b'x' * 70000 + b'\nlast\n')
    runner.poll()
    assert runner.output.endswith('last\n') and len(runner.output) == 65536
