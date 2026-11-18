"""start.sh/start.ps1 bootstrap uv and run tasks.py start; tasks.py owns start and shell."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
from types import SimpleNamespace

import pytest

SOURCE = Path(__file__).resolve().parents[1]


@pytest.fixture
def launcher(tmp_path):
    if os.name != 'posix' or shutil.which('bash') is None:
        pytest.skip('Bash launcher test requires a POSIX host')
    root = tmp_path/'checkout with spaces'
    project = root/'uz_dataviewer'
    tools = tmp_path/'tools'
    for directory in (project, tools):
        directory.mkdir(parents=True)
    (root/'.python-version').write_text('3.12\n')
    shutil.copyfile(SOURCE/'start.sh', project/'start.sh')
    shutil.copyfile(SOURCE/'tasks.py', project/'tasks.py')
    log = tmp_path/'calls.jsonl'
    # A stand-in for uv and for the programs in .venv: it records each call.
    # `uv run --no-project --python X script ...` really runs the script.
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
'''
    (tools/'uv').write_text(stub)
    (tools/'uv').chmod(0o755)
    # Stand-in for uz_cli/tasks.py: "wheel --out DIR" writes one wheel, or fails.
    (root/'uz_cli').mkdir()
    (root/'uz_cli'/'tasks.py').write_text(
        'import os, sys\nfrom pathlib import Path\n'
        'if os.environ.get("FAIL_BUILD"): raise SystemExit(7)\n'
        'out = Path(sys.argv[sys.argv.index("--out") + 1]); out.mkdir(parents=True)\n'
        '(out / "ultrazohm_cli-0.0.0-py3-none-any.whl").touch()\n')
    environment = {**os.environ, 'PATH': str(tools)+os.pathsep+os.environ['PATH'], 'LAUNCH_LOG': str(log)}

    def calls():
        return [json.loads(line) for line in log.read_text().splitlines()] if log.exists() else []

    def start(*args, **extra_env):
        result = subprocess.run(['bash', str(project/'start.sh'), *args], cwd=tmp_path,
                                env={**environment, **extra_env}, text=True, capture_output=True)
        return result, calls()

    def task(*args, **extra_env):
        result = subprocess.run([sys.executable, str(project/'tasks.py'), *args], cwd=tmp_path,
                                env={**environment, **extra_env}, text=True, capture_output=True)
        return result, calls()
    return SimpleNamespace(start=start, task=task, project=project, root=root, tmp=tmp_path)


def test_start_script_runs_the_locked_environment(launcher):
    result, calls = launcher.start('a recording.csv', '--backend', 'polars')
    assert result.returncode == 0, result.stderr
    assert [c['name'] for c in calls] == ['uv']
    assert calls[0]['args'][0] == 'run'
    assert calls[0]['args'][-7:] == ['uz-dataviewer', 'gui', '--live-repo', str(launcher.root),
                                     'a recording.csv', '--backend', 'polars']
    # Relative recording paths stay valid: the caller's directory is kept.
    assert calls[0]['cwd'] == str(launcher.tmp)


def test_dev_cli_builds_the_checkout_cli_before_launch(launcher):
    result, calls = launcher.start('--dev-cli', 'a recording.csv')
    assert result.returncode == 0, result.stderr
    assert [c['name'] for c in calls] == ['uv', 'uv', 'uz-dataviewer']
    assert calls[0]['args'][0] == 'sync' and '--inexact' in calls[0]['args']
    assert '--frozen' in calls[0]['args']
    assert calls[0]['args'][calls[0]['args'].index('--no-install-package') + 1] == 'ultrazohm-cli'
    wheel = launcher.root/'uz_cli'/'target'/'wheels-dev'/'ultrazohm_cli-0.0.0-py3-none-any.whl'
    assert calls[1]['args'][:2] == ['pip', 'install']
    assert calls[1]['args'][-3:] == ['--no-deps', '--reinstall', str(wheel)]
    assert calls[2]['args'] == ['gui', '--live-repo', str(launcher.root), 'a recording.csv']
    assert calls[2]['cwd'] == str(launcher.tmp)


def test_develop_task_equals_start_with_dev_cli(launcher):
    result, calls = launcher.task('develop', 'a recording.csv')
    assert result.returncode == 0, result.stderr
    assert [c['name'] for c in calls] == ['uv', 'uv', 'uz-dataviewer']
    assert calls[2]['args'] == ['gui', '--live-repo', str(launcher.root), 'a recording.csv']


@pytest.mark.parametrize('via_make', [False, True])
def test_overview_lists_tasks_as_they_are_called(launcher, via_make):
    result, calls = launcher.task(**({'UZ_TASKS_VIA_MAKE': '1'} if via_make else {}))
    assert result.returncode == 0 and calls == []
    assert 'develop' in result.stdout and 'positional arguments' not in result.stdout
    expected = 'make start ARGS="log.parquet"' if via_make else 'uv run uz_dataviewer/tasks.py start log.parquet'
    assert expected in result.stdout


def test_failed_dev_cli_build_never_opens_viewer(launcher):
    result, calls = launcher.start('--dev-cli', FAIL_BUILD='1')
    assert result.returncode != 0
    assert calls == []  # A failed build must not sync or modify the viewer environment.


def test_viewer_help_passes_through(launcher):
    result, calls = launcher.start('--', '--help')
    assert result.returncode == 0, result.stderr
    assert calls[0]['args'][-3:] == ['--live-repo', str(launcher.root), '--help']


@pytest.mark.parametrize('dev_cli', [False, True])
def test_shell_task_sets_up_environment_without_starting_gui(launcher, dev_cli):
    result, calls = launcher.task('shell', *(['--dev-cli'] if dev_cli else []))
    assert result.returncode == 0, result.stderr
    assert calls[-1]['name'] == 'python'
    assert calls[-1]['args'] == ['-m', 'uz_dataviewer.env_shell']
    assert all(c['name'] != 'uz-dataviewer' for c in calls)
    assert '--inexact' in calls[0]['args']  # Preserve an installed development CLI.
    assert any(c['args'][:2] == ['pip', 'install'] for c in calls) == dev_cli


@pytest.mark.parametrize('args', [('shell', 'measurement.csv'), ('no-such-task',)])
def test_invalid_tasks_do_not_set_up_anything(launcher, args):
    result, calls = launcher.task(*args)
    assert result.returncode != 0
    assert calls == []


@pytest.mark.parametrize('exit_code', [0, 7])
def test_powershell_wrapper_forwards_arguments_and_exit_code(tmp_path, exit_code):
    shell = shutil.which('pwsh') or shutil.which('powershell')
    if shell is None:
        pytest.skip('PowerShell is unavailable on this host')
    project = tmp_path / 'checkout with spaces'
    project.mkdir()
    (tmp_path/'.python-version').write_text('3.12\n')
    shutil.copyfile(SOURCE / 'start.ps1', project / 'start.ps1')
    report = tmp_path / 'arguments.json'
    stub = project / 'uv.ps1'
    stub.write_text('$args | ConvertTo-Json -Compress | Set-Content -LiteralPath $env:LAUNCH_LOG\n'
                    f'exit {exit_code}\n')
    bootstrap = project / 'test.ps1'
    bootstrap.write_text('function Get-Command { [pscustomobject]@{ Source = $env:TEST_UV } }\n'
                         '$viewerBefore = $env:PATH\n& $env:TEST_START @args\n'
                         '$viewerExit = $LASTEXITCODE\n'
                         'if ($env:PATH -ne $viewerBefore) { throw "Caller PATH changed" }\n'
                         'exit $viewerExit\n')
    args = ['--dev-cli', 'a recording.csv']
    result = subprocess.run([shell, '-NoProfile', '-File', str(bootstrap), *args],
        env={**os.environ, 'TEST_UV': str(stub), 'TEST_START': str(project / 'start.ps1'),
             'LAUNCH_LOG': str(report)}, capture_output=True, text=True)
    assert result.returncode == exit_code, result.stderr
    assert json.loads(report.read_text(encoding='utf-8-sig')) == [
        'run', '--no-project', '--python', '3.12', str(project / 'tasks.py'), 'start', *args]


@pytest.mark.parametrize('platform', ['nt', 'posix'])
@pytest.mark.parametrize('task', ['start', 'shell'])
def test_tasks_platform_paths(tmp_path, monkeypatch, platform, task):
    import importlib.util
    spec = importlib.util.spec_from_file_location('viewer_tasks', SOURCE / 'tasks.py')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    project = tmp_path / 'checkout with spaces' / 'uz_dataviewer'
    monkeypatch.setattr(module, 'HERE', project)
    monkeypatch.setattr(module, 'CLI', project.parent / 'uz_cli')
    monkeypatch.setattr(module, 'PYTHON', '3.12')
    monkeypatch.setattr(module, 'WINDOWS', platform == 'nt')
    wheels = project.parent / 'uz_cli' / 'target' / 'wheels-dev'
    calls = []

    def run(args, **kwargs):
        calls.append([str(arg) for arg in args])
        if 'tasks.py' in str(args[1]):
            wheels.mkdir(parents=True)
            (wheels / 'ultrazohm_cli-0.0.0-py3-none-any.whl').touch()
    monkeypatch.setattr(module.subprocess, 'run', run)
    monkeypatch.setattr(module.subprocess, 'call', lambda args: calls.append([str(a) for a in args]) or 7)
    with pytest.raises(SystemExit) as stopped:
        module.main([task, '--dev-cli'])
    assert stopped.value.code == 7
    scripts = project / '.venv' / ('Scripts' if platform == 'nt' else 'bin')
    python = str(scripts / ('python.exe' if platform == 'nt' else 'python'))
    assert calls[0][1:] == [str(project.parent / 'uz_cli' / 'tasks.py'), 'wheel', '--out', str(wheels)]
    assert calls[1][0:2] == ['uv', 'sync']
    assert '--frozen' in calls[1]
    assert calls[1][calls[1].index('--no-install-package') + 1] == 'ultrazohm-cli'
    assert calls[2] == ['uv', 'pip', 'install', '--quiet', '--python', python, '--no-deps', '--reinstall',
                        str(wheels / 'ultrazohm_cli-0.0.0-py3-none-any.whl')]
    if task == 'shell':
        assert calls[3] == [python, '-m', 'uz_dataviewer.env_shell']
    else:
        executable = str(scripts / ('uz-dataviewer.exe' if platform == 'nt' else 'uz-dataviewer'))
        assert calls[3] == [executable, 'gui', '--live-repo', str(project.parent)]
