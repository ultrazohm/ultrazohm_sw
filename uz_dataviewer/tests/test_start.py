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
    shutil.copyfile(Path(__file__).parents[1]/'launch.py', project/'launch.py')
    log = tmp_path/'calls.jsonl'
    stub = '#!' + sys.executable + '\n' + r'''
import json, os, sys
from pathlib import Path
name = Path(sys.argv[0]).name
if name == 'uv' and '--no-project' in sys.argv:
    i = sys.argv.index('--python') + 2
    os.execv(sys.executable, [sys.executable, *sys.argv[i:]])
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
if name == 'setup_uv.py':
    raise SystemExit(int(os.environ.get('FAIL_BACKEND', '0')))
if name == 'python':
    raise SystemExit(int(os.environ.get('FAIL_CHECK', '0')))
'''
    for executable in (tools/'uv', cli/'setup_uv.py'):
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
    assert [c['name'] for c in calls] == ['uv', 'setup_uv.py', 'python', 'uz-dataviewer']
    assert calls[0]['args'][0] == 'sync'
    assert '--inexact' in calls[0]['args']
    assert calls[1]['args'] == ['--python', '3.12', '--venv', str(launcher.project/'.venv'), '--launch', 'none',
                               '--no-examples', '--channel', 'testing']
    assert calls[2]['args'] == ['-m', 'uz_dataviewer.check_live']
    assert calls[3]['args'] == ['--use-live', '--live-repo', str(launcher.root), 'a recording.csv']
    assert len({c['cwd'] for c in calls}) == 1


def test_explicit_live_wheel_uses_same_setup_flow(launcher):
    wheel = launcher.root/'ultrazohm-test wheel.whl'
    wheel.touch()
    result, calls = launcher.run('--live-wheel', str(wheel), '--help')
    assert result.returncode == 0, result.stderr
    assert calls[1]['name'] == 'setup_uv.py'
    assert calls[1]['args'][-2:] == ['--wheel', str(wheel)]
    assert calls[-1]['args'] == ['--use-live', '--live-repo', str(launcher.root), '--help']


@pytest.mark.parametrize('variable,expected', [('FAIL_BACKEND', ['uv', 'setup_uv.py']),
                                              ('FAIL_CHECK', ['uv', 'setup_uv.py', 'python'])])
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


@pytest.mark.parametrize('live', [False, True])
def test_shell_launch_sets_up_environment_without_starting_gui(launcher, live):
    args = ['--launch', 'shell'] + (['--use-live'] if live else [])
    result, calls = launcher.run(*args)
    assert result.returncode == 0, result.stderr
    assert calls[-1]['name'] == 'python'
    assert calls[-1]['args'] == ['-m', 'uz_dataviewer.env_shell']
    assert all(c['name'] != 'uz-dataviewer' for c in calls)
    assert '--inexact' in calls[0]['args']  # Preserve an already installed CLI wheel.
    assert any(c['name'] == 'setup_uv.py' for c in calls) == live


@pytest.mark.parametrize('args', [('--launch',), ('--launch', 'wrong'),
                                  ('--launch', 'shell', 'measurement.csv')])
def test_invalid_shell_arguments_do_not_setup_environment(launcher, args):
    result, calls = launcher.run(*args)
    assert result.returncode != 0
    assert calls == []


@pytest.mark.parametrize('exit_code', [0, 7])
def test_powershell_wrapper_forwards_arguments_and_exit_code(tmp_path, exit_code):
    shell = shutil.which('pwsh') or shutil.which('powershell')
    if shell is None:
        pytest.skip('PowerShell is unavailable on this host')
    project = tmp_path / 'checkout with spaces'
    project.mkdir()
    shutil.copyfile(Path(__file__).parents[1] / 'start.ps1', project / 'start.ps1')
    report = tmp_path / 'arguments.json'
    stub = project / 'uv.ps1'
    stub.write_text('$args | ConvertTo-Json -Compress | Set-Content -LiteralPath $env:LAUNCH_LOG\n'
                    f'exit {exit_code}\n')
    bootstrap = project / 'test.ps1'
    bootstrap.write_text('function Get-Command { [pscustomobject]@{ Source = $env:TEST_UV } }\n'
                         '& $env:TEST_START @args\nexit $LASTEXITCODE\n')
    args = ['--use-live', '--live-wheel', 'a wheel.whl', 'a recording.csv']
    result = subprocess.run([shell, '-NoProfile', '-File', str(bootstrap), *args],
        env={**os.environ, 'TEST_UV': str(stub), 'TEST_START': str(project / 'start.ps1'),
             'LAUNCH_LOG': str(report)}, capture_output=True, text=True)
    assert result.returncode == exit_code, result.stderr
    assert json.loads(report.read_text(encoding='utf-8-sig')) == [
        'run', '--no-project', '--python', '3.12', str(project / 'launch.py'), *args]
