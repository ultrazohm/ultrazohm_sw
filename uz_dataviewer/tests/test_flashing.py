"""Managed flashing sequence and confirmation, without programming real hardware."""
from copy import deepcopy
import json
from pathlib import Path
import threading
import time
from types import SimpleNamespace

import pytest
from imgui_bundle import imgui

from uz_dataviewer.live import LiveController, LiveUpdate
from uz_dataviewer.panels.live import LiveWorkspace
from uz_dataviewer import flashing, live_mapping


@pytest.fixture
def workflow(tmp_path, monkeypatch):
    root = tmp_path/'repo'
    monkeypatch.setattr(flashing, 'xsct_available', lambda: True)
    header = root/live_mapping.HEADER
    header.parent.mkdir(parents=True)
    header.touch()
    monkeypatch.setattr(flashing, 'default_profile', lambda: {
        'name': 'standard', 'sample_period_us': 100., 'initial_channels': {'1': 'JSO_keep'}})
    events, starts = [], []
    mapping = {'api_version': 1, 'channels': 20, 'samples_per_packet': 15,
               'observables': {'JSO_ZEROVALUE': 0, 'JSO_keep': 1, 'JSO_added': 3},
               'variables': {}, 'commands': {}, 'slow_signals': {}, 'platform_state': {}}
    class Client:
        def __init__(self):
            self.gone = False
            self.retry = 0
            self.finalizing_reads = 0
            self.profile = dict(mapping, name='custom', sample_period_us=50., initial_channels={})
            self.value = {'state': {'connected': True, 'device': '192.168.1.233:1000'},
                          'logging': {'fast': {'phase': 'recording'}, 'slow': {'phase': 'recording'}},
                          'send_ack': True, 'data_options': {'buffer_samples': 123, 'segment_rows': 999,
                                                           'flush_interval_ms': 500, 'recording_backend': 'parquet'}}
        def status(self):
            if self.gone:
                raise ConnectionRefusedError('not running')
            if any(v['phase'] == 'finalizing' for v in self.value['logging'].values()):
                self.finalizing_reads += 1
                if self.finalizing_reads >= 2:
                    for v in self.value['logging'].values(): v['phase'] = 'complete'
                    events.append('finalized')
            return deepcopy(self.value)
        def catalog(self): return {'profile': self.profile}
        def observables(self): return {'channels': [{'channel': 1, 'name': 'JSO_keep'},
                                                   {'channel': 2, 'name': 'JSO_removed'}]}
        def stop(self): events.append('stop')
        def stop_logging(self):
            events.append('stop_fast')
            self.value['logging']['fast']['phase'] = 'finalizing'
        def stop_logging_slow_data(self):
            events.append('stop_slow')
            self.value['logging']['slow']['phase'] = 'finalizing'
        def shutdown(self):
            assert all(v['phase'] == 'complete' for v in self.value['logging'].values())
            events.append('shutdown')
            self.gone = True
        def connect(self, ip, port):
            if self.retry:
                self.retry -= 1
                raise ConnectionRefusedError('board starting')
            events.append(('connect', ip, port))
            self.value['state']['connected'] = True
    client = Client()
    controller = LiveController(lambda _: client)
    path = root/'cached.json'
    def generate(repo, *, overwrite=False):
        assert repo == root and overwrite
        events.append('mapping')
        path.write_text(json.dumps(mapping))
        return path
    def program(repo, endpoint, stop_event, emit):
        events.append('flash')
        emit('info', 'Programming output')
        return True
    def start(output, selected_mapping, profile, options, ack):
        events.append('start')
        starts.append((options, ack))
        assert not Path(output).exists()
        assert Path(selected_mapping) == path
        client.profile = dict(mapping, **json.loads(Path(profile).read_text()))
        client.gone = False
        client.value['state']['connected'] = False
        for v in client.value['logging'].values(): v['phase'] = 'idle'
        return None
    monkeypatch.setattr(live_mapping, 'generate_mapping', generate)
    monkeypatch.setattr(flashing, 'run_flash_cli', program)
    monkeypatch.setattr(controller, '_start_service', start)
    request = {'repo': str(root), 'endpoint': '127.0.0.1:19740', 'ip': '192.168.9.9',
               'port': 2000, 'output': str(tmp_path/'measurements'/'previous')}
    try:
        yield SimpleNamespace(controller=controller, client=client, events=events, root=root,
                              request=request, mapping=mapping, starts=starts)
    finally:
        controller.close()


def test_sequence_finalizes_then_flashes_and_reconnects_with_new_profile(workflow):
    w = workflow
    w.client.retry = 1
    w.controller._command('flash', w.request)
    assert w.events == ['stop', 'stop_fast', 'stop_slow', 'finalized', 'shutdown',
                        'mapping', 'flash', 'start', ('connect', '192.168.1.233', 1000)]
    assert w.controller.attached
    assert w.client.profile['initial_channels'] == {'1': 'JSO_keep'}
    assert w.client.profile['sample_period_us'] == 50.
    assert w.starts == [({'buffer_samples': 123, 'segment_rows': 999,
                         'flush_interval_ms': 500, 'recording_backend': 'parquet'}, True)]
    assert w.client.value['logging']['fast']['phase'] == 'idle'
    path, output = w.controller._flash_config
    assert Path(path).is_file()
    assert Path(output).parent == Path(w.request['output']).parent
    messages = []
    while not w.controller.messages.empty(): messages.append(w.controller.messages.get_nowait())
    assert any('JSO_removed' in text for _, text in messages)
    assert any('Programming output' in text for _, text in messages)


def test_no_running_service_can_flash_and_start_acquisition(workflow):
    w = workflow
    w.client.gone = True
    w.controller._command('flash', w.request)
    assert w.events[:3] == ['mapping', 'flash', 'start']
    assert w.client.profile['sample_period_us'] == 100.
    assert w.controller.attached


def test_flash_preserves_saved_user_settings(workflow):
    w = workflow
    saved = w.root/'settings.json'
    original = '{"schema_version":1,"name":"preferences","sample_period_us":75,"initial_channels":{}}\n'
    saved.write_text(original)
    before = saved.stat().st_mtime_ns
    w.controller._command('flash', w.request)
    assert saved.read_text() == original
    assert saved.stat().st_mtime_ns == before
    assert w.client.profile['sample_period_us'] == 50.  # Effective reconnect preserves the live service.


@pytest.mark.parametrize('stage', ['stop', 'finalize', 'mapping', 'flash'])
def test_failures_abort_later_stages(workflow, monkeypatch, stage):
    w = workflow
    def fail(*args, **kwargs): raise RuntimeError(stage+' failed')
    if stage == 'stop': monkeypatch.setattr(w.client, 'stop', fail)
    elif stage == 'finalize': monkeypatch.setattr(w.controller, '_wait_for', fail)
    elif stage == 'mapping': monkeypatch.setattr(live_mapping, 'generate_mapping', fail)
    else: monkeypatch.setattr(flashing, 'run_flash_cli', fail)
    with pytest.raises(RuntimeError, match=stage+' failed'):
        w.controller._command('flash', w.request)
    assert 'start' not in w.events
    if stage != 'flash': assert 'flash' not in w.events
    if stage in ('stop', 'finalize'): assert 'shutdown' not in w.events


def test_worker_clears_flash_lock_after_failure():
    controller = LiveController()
    def fail(kwargs): raise RuntimeError('test failure')
    controller._flash = fail
    try:
        controller.submit('flash')
        deadline = time.monotonic()+3
        while controller.latest().completed_commands == 0 and time.monotonic()<deadline:
            time.sleep(.01)
        assert 'test failure' in controller.latest().error
        assert not controller.flashing
    finally:
        controller.close()


@pytest.mark.parametrize('action', ['OK', 'Cancel'])
def test_confirmation_only_submits_after_ok(gui_frame, app_state, monkeypatch, action):
    workspace = LiveWorkspace(LiveController())
    workspace.available = True
    workspace.flash_available = True
    workspace.update = LiveUpdate(attached=True, status={'state': {'connected': True}})
    calls = []
    monkeypatch.setattr(workspace, 'send', lambda op, **kwargs: calls.append((op, kwargs)))
    clicked = set()
    original = imgui.button
    def button(label, *args, **kwargs):
        original(label, *args, **kwargs)
        if label in ('Flash UZ', action) and label not in clicked:
            clicked.add(label)
            return True
        return False
    monkeypatch.setattr(imgui, 'button', button)
    try:
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
        if action == 'OK':
            assert len(calls) == 1 and calls[0][0] == 'flash'
        else:
            assert calls == []
        assert workspace.controller.thread is None
    finally:
        workspace.close()


@pytest.mark.parametrize('code', [0, 2])
def test_shared_cli_runner_streams_and_checks_exit(monkeypatch, tmp_path, code):
    calls, messages = [], []
    class Runner:
        def __init__(self, output): self.output = output
        def submit_arguments(self, args, endpoint):
            calls.append((args, endpoint))
            self.job = SimpleNamespace(returncode=None)
            return self.job
        def poll(self):
            self.output.info('JTAG progress')
            self.job.returncode = code
        def close(self): pass
    monkeypatch.setattr(flashing, 'CliConsole', Runner)
    if code:
        with pytest.raises(RuntimeError, match='Flashing failed'):
            flashing.run_flash_cli(tmp_path, '127.0.0.1:19740', threading.Event(), lambda *x: messages.append(x))
    else:
        assert flashing.run_flash_cli(tmp_path, '127.0.0.1:19740', threading.Event(), lambda *x: messages.append(x))
    assert calls == [(['flash', '--repo', str(tmp_path)], '127.0.0.1:19740')]
    assert ('info', 'JTAG progress') in messages


def test_retry_after_programming_failure_retains_previous_profile(workflow, monkeypatch):
    w = workflow
    def failed(*args): raise RuntimeError('build failed')
    monkeypatch.setattr(flashing, 'run_flash_cli', failed)
    with pytest.raises(RuntimeError, match='build failed'):
        w.controller._command('flash', w.request)
    assert w.client.gone
    monkeypatch.setattr(flashing, 'run_flash_cli', lambda *args: True)
    w.controller._command('flash', w.request)
    assert w.client.profile['sample_period_us'] == 50.
    assert w.client.profile['initial_channels'] == {'1': 'JSO_keep'}
    assert w.controller._flash_context is None


def test_closed_viewer_does_not_start_a_new_flash(monkeypatch, tmp_path):
    monkeypatch.setattr(flashing, 'CliConsole', lambda *args: pytest.fail('Must not launch'))
    closed = threading.Event()
    closed.set()
    assert not flashing.run_flash_cli(tmp_path, '127.0.0.1:19740', closed, lambda *args: None)


@pytest.mark.parametrize('present', [False, True])
def test_xsct_detection_and_disabled_flash_button(gui_frame, app_state, monkeypatch, present):
    monkeypatch.setattr(flashing.shutil, 'which', lambda name: '/tools/xsct' if present else None)
    assert flashing.xsct_available() is present
    workspace = LiveWorkspace(LiveController())
    workspace.available = True
    workspace.flash_available = present
    disabled = {}
    original = imgui.button
    def button(label, *args, **kwargs):
        result = original(label, *args, **kwargs)
        if label in ('Flash UZ', 'Connect', 'Attach'):
            disabled[label] = bool(imgui.get_item_flags() & imgui.ItemFlags_.disabled)
        return result
    monkeypatch.setattr(imgui, 'button', button)
    try:
        gui_frame(SimpleNamespace(render=workspace.render_data), app_state)
        assert disabled == {'Connect': False, 'Flash UZ': not present}
    finally:
        workspace.close()


def test_missing_xsct_aborts_before_device_or_logging_changes(monkeypatch):
    monkeypatch.setattr(flashing, 'xsct_available', lambda: False)
    controller = LiveController(lambda _: pytest.fail('Must not contact the service'))
    try:
        with pytest.raises(RuntimeError, match='XSCT.*not on PATH'):
            controller._command('flash', {})
        assert controller.client is None
    finally:
        controller.close()
