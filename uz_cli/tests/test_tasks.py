"""Task orchestration and CI release versions; no packages are built or installed."""
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import tasks
from tasks import release_version


class ReleaseVersionTest(unittest.TestCase):
    def test_versions_order_by_run_and_mark_prereleases(self):
        self.assertEqual(release_version("0.2.0", "main", 42), "0.2.42")
        self.assertEqual(release_version("0.2.0", "develop", 43), "0.2.43.dev0")
        self.assertEqual(release_version("0.2.0", "feature/x", 44), "0.2.44.dev0")

    def test_versions_sort_above_the_former_post_releases(self):
        from packaging.version import Version
        newest_old = Version("0.1.0.post999999")
        self.assertGreater(Version(release_version("0.1.0", "main", 1)), newest_old)
        self.assertGreater(Version(release_version("0.1.0", "develop", 1)), newest_old)
        self.assertLess(Version(release_version("0.1.0", "develop", 5)),
                        Version(release_version("0.1.0", "main", 5)))

    def test_invalid_input(self):
        for base, run in (("0.2", 1), ("0.2.0", 0)):
            with self.assertRaises(ValueError):
                release_version(base, "main", run)


class StartTest(unittest.TestCase):
    def test_install_and_launch_both_modes_on_both_platforms(self):
        for windows in (False, True):
            for source in ('local', 'release', 'prerelease'):
                with self.subTest(windows=windows, source=source), tempfile.TemporaryDirectory() as root:
                    root = Path(root)
                    project = root / 'checkout with spaces' / 'uz_cli'
                    project.mkdir(parents=True)
                    (project.parent / '.python-version').write_text('3.12\n')
                    calls = []
                    def run(*command, _calls=calls, **kwargs):
                        _calls.append((list(command), kwargs))
                        if 'build' in command:
                            output = Path(command[-1])
                            output.mkdir(parents=True)
                            (output / 'ultrazohm_cli-0.1.0-test.whl').touch()
                    with patch.multiple(tasks, HERE=project, ROOT=project.parent,
                                        TARGET=project / 'target', WINDOWS=windows), \
                            patch.object(tasks, 'run', side_effect=run), \
                            patch.object(tasks, 'maturin', return_value=['maturin']):
                        tasks.main(['start', source, '--', '--endpoint', '127.0.0.1:1234', 'status'])
                        python = tasks.venv_bin(project / '.venv', 'python')
                        install = next(cmd for cmd, _ in calls if cmd[:3] == ['uv', 'pip', 'install'])
                        self.assertIn(python, install)
                        self.assertIn('--reinstall-package', install)
                        if source == 'local':
                            self.assertEqual(calls[0][0][:4], ['maturin', 'build', '--release', '--locked'])
                            self.assertIsInstance(install[-1], Path)
                        else:
                            self.assertFalse(any('maturin' in cmd for cmd, _ in calls))
                            self.assertEqual(install[-5:], ['--upgrade-package', 'ultrazohm_cli',
                                                           '--prerelease', 'allow' if source == 'prerelease' else 'disallow', 'ultrazohm_cli'])
                        self.assertEqual(calls[-1], ([tasks.venv_bin(project / '.venv', 'ultrazohm_cli'),
                            '--endpoint', '127.0.0.1:1234', 'status'], {'cwd': Path.cwd()}))
                        # Subsequent launches reuse the environment, but reinstall the CLI.
                        python.parent.mkdir(parents=True)
                        python.touch()
                        calls.clear()
                        tasks.main(['start', source])
                        self.assertFalse(any(cmd[:2] == ['uv', 'venv'] for cmd, _ in calls))
                        self.assertTrue(any(cmd[:3] == ['uv', 'pip', 'install'] for cmd, _ in calls))

    def test_failed_build_stops_before_install_or_launch(self):
        with patch.object(tasks, 'local_wheel', side_effect=subprocess.CalledProcessError(7, 'maturin')), \
                patch.object(tasks, 'run') as run:
            with self.assertRaises(SystemExit) as stopped:
                tasks.main(['start'])
            self.assertEqual(stopped.exception.code, 7)
            run.assert_not_called()

    def test_prerelease_option_controls_install_and_is_not_forwarded(self):
        for option in (['--prerelease=allow'], ['--prerelease', 'allow']):
            with self.subTest(option=option), patch.object(tasks, 'run') as run:
                tasks.main(['start', 'release', *option, '--', '--help'])
                install = next(call.args for call in run.call_args_list
                               if call.args[:3] == ('uv', 'pip', 'install'))
                self.assertEqual(install[-3:], ('--prerelease', 'allow', 'ultrazohm_cli'))
                self.assertEqual(run.call_args.args[1:], ('--help',))

    @unittest.skipUnless(shutil.which('make'), 'make is optional on Windows')
    def test_make_passes_mode_and_cli_arguments_once(self):
        for source in ('local', 'release', 'prerelease'):
            result = subprocess.run(['make', '-n', '-C', str(tasks.HERE), 'start', source,
                                     'ARGS=-- --help'], capture_output=True, text=True, check=True)
            self.assertEqual(result.stdout.count('tasks.py'), 1)
            self.assertIn(f'tasks.py start {source} -- --help', result.stdout)
        result = subprocess.run(['make', '-n', '-C', str(tasks.HERE), 'start', 'local', 'release'],
                                capture_output=True, text=True, check=False)
        self.assertNotEqual(result.returncode, 0)


if __name__ == "__main__":
    unittest.main()
