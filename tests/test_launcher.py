"""Shared setup, dispatch and bootstrap regressions; no network or native builds."""
import importlib.util
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

REPO = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('repository_tasks', REPO / 'tasks.py')
tasks = importlib.util.module_from_spec(spec)
spec.loader.exec_module(tasks)


class SetupTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='uz setup ')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for name in ('tasks.py', '.python-version', 'ultrazohm_dataviewer/pyproject.toml', 'ultrazohm_dataviewer/uv.lock'):
            target = self.root / name
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(REPO / name, target)
        self.calls = []
        for patcher in (patch.object(tasks, 'ROOT', self.root),
                        patch.object(tasks, 'run', side_effect=self.record),
                        patch.object(tasks.subprocess, 'check_output', return_value='{}')):
            patcher.start()
            self.addCleanup(patcher.stop)

    def record(self, *command, **kwargs):
        self.calls.append(command)
        if '--out' in command:
            Path(command[command.index('--out') + 1], 'ultrazohm_cli-0.1.0-test.whl').touch()
        if command[:2] == ('uv', 'venv'):
            tasks.scripts().mkdir(parents=True, exist_ok=True)
        if command[:3] == ('uv', 'pip', 'install'):
            for name in ('python', 'ultrazohm-cli', 'ultrazohm-dataviewer'):
                tasks.executable(name).touch()

    def test_all_application_source_combinations(self):
        for source in tasks.SOURCES:
            for app in ('cli', 'viewer'):
                with self.subTest(source=source, app=app):
                    self.calls.clear()
                    tasks.setup(source, app=app)
                    install = next(c for c in self.calls if c[:3] == ('uv', 'pip', 'install'))
                    if source == 'local':
                        self.assertTrue(any(str(c).endswith('.whl') for c in install))
                        self.assertEqual('--editable' in install, app == 'viewer')
                        self.assertIn('--no-sources', install)
                        self.assertNotIn('--no-build-package', install)
                    else:
                        self.assertEqual(install[-1], 'ultrazohm-cli' if app == 'cli' else 'ultrazohm-dataviewer')
                        self.assertNotIn('--editable', install)
                        self.assertEqual(install[install.index('--prerelease') + 1],
                                         'allow' if source == 'prerelease' else 'disallow')
                    self.assertTrue(any(c[:3] == ('uv', 'pip', 'check') for c in self.calls))
                    state = tasks.saved_setup()
                    self.assertEqual((state['source'], state['app']), (source, app))
                    self.assertIn('fingerprint', state)

    def test_shell_reuses_completed_setup_and_refreshes_missing_command(self):
        tasks.setup('stable', app='cli')
        self.calls.clear()
        tasks.setup(reuse=True)
        self.assertEqual(self.calls, [])
        tasks.executable('ultrazohm-cli').unlink()
        tasks.setup(reuse=True)
        self.assertTrue(self.calls)

    def test_switch_recreates_environment(self):
        tasks.setup('local', app='viewer')
        self.calls.clear()
        tasks.setup('stable', app='cli')
        self.assertTrue(any(c[:3] == ('uv', 'venv', '--clear') for c in self.calls))
        self.assertEqual(tasks.saved_setup()['app'], 'cli')

    def test_failure_is_not_marked_ready(self):
        tasks.setup('stable', app='cli')
        original = self.record
        def failing(*command, **kwargs):
            if command[:3] == ('uv', 'pip', 'install'):
                raise subprocess.CalledProcessError(1, command)
            original(*command, **kwargs)
        with patch.object(tasks, 'run', side_effect=failing):
            with self.assertRaises(subprocess.CalledProcessError):
                tasks.setup('prerelease', app='viewer')
        self.assertNotIn('fingerprint', tasks.saved_setup())

    def test_no_release_alias(self):
        with self.assertRaises(SystemExit):
            tasks.main(['setup', 'release'])


@unittest.skipUnless(os.name == 'posix' and shutil.which('bash'), 'POSIX Bash required')
class BashBootstrapTest(unittest.TestCase):
    def test_existing_and_missing_uv_preserve_arguments_cwd_and_exit_code(self):
        for missing in (False, True):
            with self.subTest(missing=missing), tempfile.TemporaryDirectory(prefix='uz bootstrap ') as directory:
                root = Path(directory).resolve()
                checkout = root / 'checkout with spaces'
                checkout.mkdir()
                shutil.copyfile(REPO / 'uz', checkout / 'uz')
                (checkout / '.python-version').write_text('3.12\n')
                tools = root / 'tools'
                tools.mkdir()
                # Deliberately exclude host Python/uv from PATH.
                for name in ('bash', 'dirname', 'cat', 'mktemp', 'rm', 'sh'):
                    (tools / name).symlink_to(shutil.which(name))
                stub = '#!' + sys.executable + '\n' + '''import json, os, sys
from pathlib import Path
Path(os.environ['REPORT']).write_text(json.dumps([sys.argv[1:], os.getcwd()]))
sys.exit(7)
'''
                if missing:
                    payload = root / 'uv-payload'
                    payload.write_text(stub)
                    # Fake the official installer download, including a path with spaces.
                    curl = tools / 'curl'
                    curl.write_text('#!' + sys.executable + '\n' + '''import sys
from pathlib import Path
Path(sys.argv[sys.argv.index('-o')+1]).write_text(
    'mkdir -p "$UV_INSTALL_DIR"\\ncp "$PAYLOAD" "$UV_INSTALL_DIR/uv"\\nchmod +x "$UV_INSTALL_DIR/uv"\\n')
''')
                    curl.chmod(0o755)
                    for name in ('mkdir', 'cp', 'chmod'):
                        (tools / name).symlink_to(shutil.which(name))
                else:
                    (tools / 'uv').write_text(stub)
                    (tools / 'uv').chmod(0o755)
                report = root / 'report.json'
                env = {**os.environ, 'PATH': str(tools), 'REPORT': str(report),
                       'UV_UNMANAGED_INSTALL': str(root / 'installed uv'),
                       'PAYLOAD': str(root / 'uv-payload')}
                arguments = ['build', 'viewer', '--cli-wheel', 'a recording $file.whl']
                result = subprocess.run([shutil.which('bash'), str(checkout / 'uz'), *arguments],
                                        cwd=root, env=env, capture_output=True, text=True)
                self.assertEqual(result.returncode, 7, result.stderr)
                received, cwd = json.loads(report.read_text())
                self.assertEqual(received, ['run', '--no-project', '--isolated', '--python', '3.12',
                                            str(checkout / 'tasks.py'), *arguments])
                self.assertEqual(cwd, str(root))


@unittest.skipUnless(shutil.which('pwsh') or shutil.which('powershell'), 'PowerShell unavailable')
class PowerShellBootstrapTest(unittest.TestCase):
    def test_arguments_exit_code_and_parent_path(self):
        shell = shutil.which('pwsh') or shutil.which('powershell')
        for code in (0, 7):
            with self.subTest(code=code), tempfile.TemporaryDirectory(prefix='uz ps ') as directory:
                root = Path(directory).resolve()
                shutil.copyfile(REPO / 'uz.ps1', root / 'uz.ps1')
                (root / '.python-version').write_text('3.12\n')
                stub = root / 'stub.ps1'
                stub.write_text('$args | ConvertTo-Json -Compress | Set-Content -LiteralPath $env:REPORT\n'
                                f'exit {code}\n')
                bootstrap = root / 'test.ps1'
                bootstrap.write_text('function Get-Command { [pscustomobject]@{ Source = $env:TEST_UV } }\n'
                                     '$before = $env:PATH\n& $env:TEST_LAUNCHER @args\n'
                                     '$result = $LASTEXITCODE\n'
                                     'if ($env:PATH -ne $before) { throw "Caller PATH changed" }\n'
                                     'exit $result\n')
                report = root / 'report.json'
                args = ['build', 'viewer', '--cli-wheel', 'a recording.whl']
                result = subprocess.run([shell, '-NoProfile', '-ExecutionPolicy', 'Bypass', '-File',
                                         str(bootstrap), *args], capture_output=True, text=True,
                                        env={**os.environ, 'TEST_UV': str(stub),
                                             'TEST_LAUNCHER': str(root / 'uz.ps1'), 'REPORT': str(report)})
                self.assertEqual(result.returncode, code, result.stderr)
                self.assertEqual(json.loads(report.read_text(encoding='utf-8-sig')),
                                 ['run', '--no-project', '--isolated', '--python', '3.12', str(root / 'tasks.py'), *args])


if __name__ == '__main__':
    unittest.main()
