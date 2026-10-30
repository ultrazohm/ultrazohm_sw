"""Prefix routing and asynchronous, shell-free execution of debug CLI commands."""
from dataclasses import replace
import subprocess
import sys
import time
from types import SimpleNamespace

import pytest

from uz_dataviewer.app import DataViewerApp
from uz_dataviewer.cli_console import CliConsole, arguments
from uz_dataviewer.console import Console


@pytest.fixture(autouse=True)
def supported_console_platform(monkeypatch):
    # These routing tests exercise platforms that expose the feature. Windows
    # exclusion is tested separately in test_user_settings.py.
    monkeypatch.setattr('uz_dataviewer.console.CLI_SUPPORTED', True)


def submit(state, text):
    state.console._input = text
    state.console._submit(state)


def test_only_exact_uz_prefix_bypasses_viewer_parser(app_state, monkeypatch):
    forwarded, viewer = [], []
    app_state.console.cli_handler = forwarded.append
    monkeypatch.setattr(app_state.commands, 'dispatch', lambda state, text: viewer.append(text))
    for text in ('uz status', '  uz\tset-variable send_field_1 5', 'uz', 'uz_example', 'help'):
        submit(app_state, text)
    assert forwarded == ['status', 'set-variable send_field_1 5', '']
    assert viewer == ['uz_example', 'help']
    assert app_state.console._input == ''
    assert app_state.console._history[-1] == 'help'
    app_state.console._input = 'uz --help'
    assert app_state.console._completions(app_state) == []


@pytest.mark.parametrize('use_live', [False, True])
def test_inactive_live_or_missing_wheel_reports_console_message(use_live):
    app = DataViewerApp(use_live=use_live)
    try:
        if app.live is not None:
            app.live.available = False
        submit(app.state, 'uz status')
        assert 'Live is not activated.' in app.state.console.as_text()
        assert app._cli_console is None
    finally:
        app._shutdown()


def test_attached_endpoint_is_used_and_detached_input_can_choose_another(monkeypatch):
    calls = []
    class Runner:
        def __init__(self, console): pass
        def submit(self, text, endpoint): calls.append((text, endpoint))
        def close(self): pass
    monkeypatch.setattr('uz_dataviewer.cli_console.CliConsole', Runner)
    app = DataViewerApp(use_live=True)
    try:
        app.live.available = True
        app.live.endpoint = '127.0.0.1:20111'
        app.live.controller.endpoint = '127.0.0.1:20222'
        app.live.update = replace(app.live.update, attached=True)
        submit(app.state, 'uz status')
        app.live.update = replace(app.live.update, attached=False)
        submit(app.state, 'uz status')
        assert calls == [('status', '127.0.0.1:20222'), ('status', '127.0.0.1:20111')]
    finally:
        app._shutdown()


@pytest.mark.parametrize('text,windows,expected', [
    ('build --repo "/tmp/repo with spaces"', False, ['build', '--repo', '/tmp/repo with spaces']),
    (r'build --repo "C:\My Projects\uz"', True, ['build', '--repo', r'C:\My Projects\uz']),
    (r'build --repo C:\work\uz', True, ['build', '--repo', r'C:\work\uz']),
])
def test_quoted_paths_and_windows_backslashes(text, windows, expected):
    assert arguments(text, windows=windows) == expected


def test_cli_arguments_output_exit_errors_and_explicit_endpoint(tmp_path, monkeypatch):
    console = Console()
    runner = CliConsole(console, tmp_path/'logs')
    calls = []
    monkeypatch.setattr('uz_dataviewer.cli_console.importlib.util.find_spec', lambda _: object())
    def launch(args, **kwargs):
        calls.append((args, kwargs))
        kwargs['stdout'].write('hello ✓\nparser error\n'.encode())
        return SimpleNamespace(poll=lambda: 2)
    monkeypatch.setattr('uz_dataviewer.cli_console.subprocess.Popen', launch)
    try:
        runner.submit('set-variable send_field_1 5', '127.0.0.1:20333')
        assert calls[0][0] == [sys.executable, '-u', '-m', 'uz_dataviewer.process_launcher', 'cli', '--endpoint',
                              '127.0.0.1:20333', 'set-variable', 'send_field_1', '5']
        assert not calls[0][1].get('shell', False)
        assert calls[0][1]['stdin'] == subprocess.DEVNULL
        runner.poll()
        assert 'hello ✓' in console.as_text()
        assert 'exited with code 2' in console.as_text()
        assert not runner.jobs
        runner.submit('--endpoint=127.0.0.1:20444 status', '127.0.0.1:20333')
        assert calls[-1][0][5:] == ['--endpoint=127.0.0.1:20444', 'status']
        runner.poll()
        runner.submit('', '127.0.0.1:20333')
        assert calls[-1][0][-1] == '--help'
        runner.poll()
        with pytest.raises(ValueError):
            runner.submit('build --repo "unfinished', '127.0.0.1:20333')
    finally:
        runner.close()


def test_missing_backend_never_launches_a_process(tmp_path, monkeypatch):
    console = Console()
    runner = CliConsole(console, tmp_path/'logs')
    monkeypatch.setattr('uz_dataviewer.cli_console.importlib.util.find_spec', lambda _: None)
    runner.submit('flash', '127.0.0.1:19740')
    assert 'Live is not activated.' in console.as_text()
    assert not runner.jobs
    assert not (tmp_path/'logs').exists()
    runner.close()


def test_output_streams_before_exit_and_active_commands_survive_close(tmp_path, monkeypatch):
    console = Console()
    runner = CliConsole(console, tmp_path/'logs')
    original = subprocess.Popen
    monkeypatch.setattr('uz_dataviewer.cli_console.importlib.util.find_spec', lambda _: object())
    marker = tmp_path/'finished.txt'
    code = ('import sys,time; from pathlib import Path; '
            'print("streaming",flush=True); time.sleep(.4); '
            f'Path({str(marker)!r}).write_text("finished"); print("done",flush=True)')
    monkeypatch.setattr('uz_dataviewer.cli_console.subprocess.Popen',
                        lambda args, **kwargs: original([sys.executable, '-u', '-c', code], **kwargs))
    try:
        runner.submit('build', '127.0.0.1:19740')
        process = runner.jobs[0].process
        deadline = time.monotonic()+3
        while 'streaming' not in console.as_text() and time.monotonic()<deadline:
            runner.poll()
            time.sleep(.01)
        assert 'streaming' in console.as_text()
        assert process.poll() is None
        runner.close()
        runner.close()  # Closing twice must not delete an active command's log.
        assert (tmp_path/'logs/command-1.log').exists()
        assert process.wait(timeout=3) == 0
        assert marker.read_text() == 'finished'
    finally:
        runner.close()
        if 'process' in locals() and process.poll() is None:
            process.kill()
            process.wait()


def test_actual_installed_cli_help_and_parse_error(tmp_path):
    pytest.importorskip('ultrazohm')
    console = Console()
    runner = CliConsole(console, tmp_path/'logs')
    try:
        runner.submit('--help', '127.0.0.1:19740')
        runner.submit('not-a-cli-command', '127.0.0.1:19740')
        deadline = time.monotonic()+5
        while runner.jobs and time.monotonic()<deadline:
            runner.poll()
            time.sleep(.01)
        assert not runner.jobs
        text = console.as_text()
        assert 'Usage:' in text
        assert 'unrecognized subcommand' in text
        assert 'uz #1 finished' in text
        assert 'uz #2 exited with code 2' in text
    finally:
        runner.close()


def test_concurrent_jobs_and_large_output_are_bounded(tmp_path, monkeypatch):
    console = Console(max_lines=20)
    runner = CliConsole(console, tmp_path/'logs')
    monkeypatch.setattr('uz_dataviewer.cli_console.importlib.util.find_spec', lambda _: object())
    finished = [False]
    def launch(args, **kwargs):
        kwargs['stdout'].write(b'x'*200000+b'\n')
        return SimpleNamespace(poll=lambda: 0 if finished[0] else None)
    monkeypatch.setattr('uz_dataviewer.cli_console.subprocess.Popen', launch)
    try:
        for _ in range(4):
            runner.submit('build', '127.0.0.1:19740')
        with pytest.raises(RuntimeError, match='Four CLI commands'):
            runner.submit('status', '127.0.0.1:19740')
        runner.poll()
        assert all(len(job.pending) <= 16384 for job in runner.jobs)
        finished[0] = True
        for _ in range(4):
            runner.poll()
        assert not runner.jobs
        assert len(console._entries) <= 20
    finally:
        runner.close()
