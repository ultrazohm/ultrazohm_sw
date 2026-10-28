"""Launcher handoff, one shared environment, argument forwarding and failure stops."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
from types import SimpleNamespace

import pytest

from uz_dataviewer.check_live import main as check_live


@pytest.fixture
def launcher(tmp_path):
    if os.name != 'posix' or shutil.which('bash') is None:
        pytest.skip('Bash launcher test requires a POSIX host')
    root = tmp_path/'checkout with spaces'
    project = root/'uz_dataviewer'
    cli = root/'uz_cli'
    tools = tmp_path/'tools'
    for directory in (project, cli, tools):
        directory.mkdir(parents=True)
    shutil.copyfile(Path(__file__).parents[1]/'start.sh', project/'start.sh')
    log = tmp_path/'calls.jsonl'
    stub = '#!' + sys.executable + '\n' + r'''
import json, os, sys
from pathlib import Path
name = Path(sys.argv[0]).name
with open(os.environ['LAUNCH_LOG'], 'a') as log:
    log.write(json.dumps({'name': name, 'args': sys.argv[1:], 'cwd': os.getcwd()})+'\n')
if name == 'uv' and sys.argv[1] == 'sync':
    project = Path(sys.argv[sys.argv.index('--project')+1])
    scripts = project/'.venv/bin'
    scripts.mkdir(parents=True, exist_ok=True)
    for child in ('python', 'uz-dataviewer'):
        target = scripts/child
        target.write_text(Path(sys.argv[0]).read_text())
        target.chmod(0o755)
if name == 'run.sh':
    raise SystemExit(int(os.environ.get('FAIL_BACKEND', '0')))
if name == 'python':
    raise SystemExit(int(os.environ.get('FAIL_CHECK', '0')))
'''
    for executable in (tools/'uv', cli/'run.sh'):
        executable.write_text(stub)
        executable.chmod(0o755)
    environment = {**os.environ, 'PATH': str(tools)+os.pathsep+os.environ['PATH'], 'LAUNCH_LOG': str(log)}
    def run(*args, **extra_env):
        result = subprocess.run(['bash', str(project/'start.sh'), *args], cwd=tmp_path,
                                env={**environment, **extra_env}, text=True, capture_output=True)
        calls = [json.loads(line) for line in log.read_text().splitlines()] if log.exists() else []
        return result, calls
    return SimpleNamespace(run=run, project=project, root=root)


def test_offline_launch_does_not_setup_cli(launcher):
    result, calls = launcher.run('a recording.csv', '--backend', 'polars')
    assert result.returncode == 0, result.stderr
    assert [c['name'] for c in calls] == ['uv']
    assert calls[0]['args'][-4:] == ['uz-dataviewer', 'a recording.csv', '--backend', 'polars']


def test_use_live_installs_cli_in_viewer_env_before_launch(launcher):
    result, calls = launcher.run('--use-live', '--live-channel', 'testing', 'a recording.csv')
    assert result.returncode == 0, result.stderr
    assert [c['name'] for c in calls] == ['uv', 'run.sh', 'python', 'uz-dataviewer']
    assert calls[0]['args'][0] == 'sync'
    assert '--inexact' in calls[0]['args']
    assert calls[1]['args'] == ['--venv', str(launcher.project/'.venv'), '--launch', 'none',
                               '--no-examples', '--channel', 'testing']
    assert calls[2]['args'] == ['-m', 'uz_dataviewer.check_live']
    assert calls[3]['args'] == ['--use-live', '--live-repo', str(launcher.project/'..'), 'a recording.csv']
    assert len({c['cwd'] for c in calls}) == 1


def test_explicit_live_wheel_uses_same_setup_flow(launcher):
    wheel = launcher.root/'ultrazohm-test wheel.whl'
    wheel.touch()
    result, calls = launcher.run('--live-wheel', str(wheel), '--help')
    assert result.returncode == 0, result.stderr
    assert calls[1]['name'] == 'run.sh'
    assert calls[1]['args'][-2:] == ['--wheel', str(wheel)]
    assert calls[-1]['args'] == ['--use-live', '--live-repo', str(launcher.project/'..'), '--help']


@pytest.mark.parametrize('variable,expected', [('FAIL_BACKEND', ['uv', 'run.sh']),
                                              ('FAIL_CHECK', ['uv', 'run.sh', 'python'])])
def test_failed_live_setup_never_opens_viewer(launcher, variable, expected):
    result, calls = launcher.run('--use-live', **{variable: '7'})
    assert result.returncode != 0
    assert [c['name'] for c in calls] == expected


def test_invalid_live_channel_fails_before_setup(launcher):
    result, calls = launcher.run('--use-live', '--live-channel', 'wrong')
    assert result.returncode != 0
    assert 'stable or testing' in result.stderr
    assert calls == []


def test_live_api_check_rejects_old_backend(monkeypatch, capsys):
    monkeypatch.setitem(sys.modules, 'ultrazohm', SimpleNamespace(Client=object))
    assert check_live() == 1
    assert 'lacks live-viewer APIs' in capsys.readouterr().err


def test_live_api_check_accepts_backend_without_connecting(monkeypatch, capsys):
    class Client:
        def __init__(self):
            raise AssertionError('Setup must not connect to anything')
        def catalog(self): pass
        def read_since(self): pass
    monkeypatch.setitem(sys.modules, 'ultrazohm', SimpleNamespace(Client=Client))
    assert check_live() == 0
    assert 'Live backend ready' in capsys.readouterr().out
