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
        self.temp = tempfile.TemporaryDirectory(prefix='uz test ')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / 'uz_dataviewer').mkdir()
        for name in ('tasks.py', '.python-version', 'uz_dataviewer/pyproject.toml', 'uz_dataviewer/uv.lock'):
            shutil.copyfile(REPO / name, self.root / name)
        self.calls = []
        self.root_patch = patch.object(tasks, 'ROOT', self.root)
        self.root_patch.start()
        self.addCleanup(self.root_patch.stop)
        self.run_patch = patch.object(tasks, 'run', side_effect=self.record)
        self.run_patch.start()
        self.addCleanup(self.run_patch.stop)

    def record(self, *command, **kwargs):
        self.calls.append((list(command), kwargs))
        if '--out' in command:
            out = Path(command[command.index('--out') + 1])
            (out / 'ultrazohm_cli-0.1.0-test.whl').touch()
        if command[:2] == ('uv', 'sync'):
            tasks.scripts().mkdir(parents=True, exist_ok=True)
            for name in ('python', 'ultrazohm_cli', 'uz-dataviewer'):
                tasks.executable(name).touch()

    def install(self):
        return next(cmd for cmd, _ in self.calls if cmd[:3] == ['uv', 'pip', 'install'])

    def test_source_selection_shared_venv_and_platform_paths(self):
        for windows in (False, True):
            for source in ('local', 'stable', 'prerelease'):
                with self.subTest(windows=windows, source=source), patch.object(tasks, 'WINDOWS', windows):
                    self.calls.clear()
                    tasks.setup(source)
                    sync, options = next((cmd, kw) for cmd, kw in self.calls if cmd[:2] == ['uv', 'sync'])
                    self.assertEqual(options['env']['UV_PROJECT_ENVIRONMENT'], str(self.root / '.venv'))
                    self.assertIn('--locked', sync)
                    self.assertIn('--no-install-package', sync)
                    self.assertIn(tasks.executable('python'), self.install())
                    self.assertIn('--no-deps', self.install())
                    if source == 'local':
                        self.assertIn('--out', self.calls[0][0])
                        self.assertTrue(str(self.install()[-1]).endswith('.whl'))
                    else:
                        self.assertFalse(any('--out' in cmd for cmd, _ in self.calls))
                        self.assertIn('--only-binary', self.install())
                        self.assertEqual(self.install()[-3:-1], ['--prerelease',
                                         'allow' if source == 'prerelease' else 'disallow'])
                        self.assertTrue(self.install()[-1].startswith('ultrazohm_cli>='))
                    self.assertEqual(tasks.saved_setup()['source'], source)
                    self.assertEqual([c[0][0] for c in self.calls[-2:]],
                                     [tasks.executable('ultrazohm_cli'), tasks.executable('uz-dataviewer')])

    def test_shell_reuses_selection_but_refreshes_changed_setup(self):
        tasks.setup('local')
        self.calls.clear()
        tasks.main(['shell'])
        self.assertEqual(self.calls, [([tasks.executable('python'), '-m', 'uz_dataviewer.env_shell'], {'interactive': True})])
        (self.root / 'uz_dataviewer/uv.lock').write_text('changed')
        self.calls.clear()
        tasks.main(['shell'])
        self.assertIn('--out', self.calls[0][0])  # Still local, not silently changed to stable.
        self.calls.clear()
        tasks.main(['shell', 'stable'])
        self.assertFalse(any('--out' in cmd for cmd, _ in self.calls))
        self.assertEqual(tasks.saved_setup()['source'], 'stable')

    def test_default_and_release_alias(self):
        tasks.main(['setup'])
        self.assertEqual(tasks.saved_setup()['source'], 'stable')
        tasks.main(['setup', 'release'])
        self.assertEqual(tasks.saved_setup()['source'], 'stable')

    def test_missing_executable_forces_setup(self):
        tasks.setup('stable')
        tasks.executable('ultrazohm_cli').unlink()
        self.calls.clear()
        tasks.setup(reuse=True)
        self.assertTrue(self.install())

    def test_failed_install_does_not_open_shell_or_mark_setup_complete(self):
        tasks.setup('stable')
        self.calls.clear()
        def fail(*command, **kwargs):
            if command[:3] == ('uv', 'pip', 'install'):
                raise subprocess.CalledProcessError(7, command)
            self.record(*command, **kwargs)
        with patch.object(tasks, 'run', side_effect=fail), self.assertRaises(SystemExit) as stopped:
            tasks.main(['shell', 'prerelease'])
        self.assertEqual(stopped.exception.code, 7)
        self.assertEqual(tasks.saved_setup(), {})
        self.assertFalse(any('uz_dataviewer.env_shell' in cmd for cmd, _ in self.calls))

    def test_failed_build_preserves_previous_setup(self):
        tasks.setup('stable')
        previous = tasks.saved_setup()
        with patch.object(tasks, 'project_task', side_effect=subprocess.CalledProcessError(9, 'build')):
            with self.assertRaises(subprocess.CalledProcessError):
                tasks.setup('local')
        self.assertEqual(tasks.saved_setup(), previous)

    def test_dispatch_preserves_arguments_and_caller_directory(self):
        tasks.main(['build', 'viewer', '--cli-wheel', 'a directory/cli.whl'])
        self.assertEqual(self.calls, [([sys.executable, self.root / 'uz_dataviewer/tasks.py',
                                       'bundle', '--cli-wheel', 'a directory/cli.whl'], {})])
        self.calls.clear()
        tasks.main(['task', 'cli', 'stamp', '0.1.42.dev0'])
        self.assertEqual(self.calls[0][0][-2:], ['stamp', '0.1.42.dev0'])
        self.calls.clear()
        tasks.main(['check', 'cli'])
        self.assertIn('unittest', self.calls[0][0])
        self.assertEqual(self.calls[-1][0][-1], 'check')

    def test_invalid_command_never_installs(self):
        with self.assertRaises(SystemExit):
            tasks.main(['setup', 'typo'])
        self.assertEqual(self.calls, [])


@unittest.skipUnless(os.name == 'posix' and shutil.which('bash'), 'POSIX Bash required')
class BashBootstrapTest(unittest.TestCase):
    def test_existing_and_missing_uv_preserve_arguments_cwd_and_exit_code(self):
        for missing in (False, True):
            with self.subTest(missing=missing), tempfile.TemporaryDirectory(prefix='uz bootstrap ') as directory:
                root = Path(directory)
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
                root = Path(directory)
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
