"""Exercise updater failure handling and cache reuse with a local wheel index."""
import importlib.util
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
import zipfile

spec = importlib.util.spec_from_file_location('updater', os.environ.get('UZ_TEST_UPDATE_SCRIPT', Path(__file__).resolve().parents[1] / 'update-packages.py'))
updater = importlib.util.module_from_spec(spec)
spec.loader.exec_module(updater)


class UpdateTest(unittest.TestCase):
    def test_failure_stops_before_other_environments(self):
        with patch.object(sys, 'argv', ['update', '--uv', 'uv', '--channel', 'stable', '--requirements', 'requirements.txt']), patch.object(updater.subprocess, 'run', side_effect=subprocess.CalledProcessError(7, 'uv')) as run:
            self.assertEqual(updater.main(), 7)
            self.assertEqual(run.call_count, 1)
            self.assertIn('disallow', run.call_args.args[0])

    @unittest.skipUnless(os.environ.get('UZ_TEST_UV'), 'requires bundled uv and Python')
    def test_normal_launches_use_updated_cached_environments(self):
        uv = os.environ['UZ_TEST_UV']
        with tempfile.TemporaryDirectory(prefix='uz-update-test-') as temp:
            root = Path(temp)
            wheels = root / 'wheels'
            wheels.mkdir()
            requirements = root / 'requirements.txt'
            requirements.write_text('matplotlib\n')
            env = {**os.environ, 'UV_CACHE_DIR': str(root / 'cache'), 'UV_NO_INDEX': '1', 'UV_FIND_LINKS': str(wheels)}

            def wheel(name, version, dependency=None):
                module = name.replace('-', '_')
                info = f'{module}-{version}.dist-info'
                with zipfile.ZipFile(wheels / f'{module}-{version}-py3-none-any.whl', 'w') as archive:
                    archive.writestr(module + '.py', f'def main(): print("{version}")\n')
                    metadata = f'Metadata-Version: 2.1\nName: {name}\nVersion: {version}\n'
                    if dependency:
                        metadata += f'Requires-Dist: ultrazohm-cli=={dependency}\n'
                    archive.writestr(info + '/METADATA', metadata)
                    archive.writestr(info + '/WHEEL', 'Wheel-Version: 1.0\nGenerator: test\nRoot-Is-Purelib: true\nTag: py3-none-any\n')
                    archive.writestr(info + '/entry_points.txt', f'[console_scripts]\n{name} = {module}:main\n')
                    archive.writestr(info + '/RECORD', '')

            def run(args):
                args = [*args[:3], '--no-index', *args[3:]]
                return subprocess.check_output(args, env=env, text=True, timeout=120).strip()

            for name in ['ultrazohm-cli', 'ultrazohm-dataviewer', 'matplotlib']:
                wheel(name, '1.0.0', '1.0.0' if name == 'ultrazohm-dataviewer' else None)
            normal = [uv, 'tool', 'run', '--isolated', '--python', '3.12', '--prerelease', 'allow']
            for name in ['ultrazohm-cli', 'ultrazohm-dataviewer']:
                self.assertEqual(run([*normal, name]), '1.0.0')
            old_shell = updater.commands(uv, 'prerelease', str(requirements))[-1][1]
            old_shell.remove('--refresh')
            self.assertIn('matplotlib==1.0.0', run(old_shell))
            for name in ['ultrazohm-cli', 'ultrazohm-dataviewer', 'matplotlib']:
                wheel(name, '2.0.0', '2.0.0' if name == 'ultrazohm-dataviewer' else None)
            for _, command in updater.commands(uv, 'prerelease', str(requirements)):
                self.assertIn('2.0.0', run(command))
            for name in ['ultrazohm-cli', 'ultrazohm-dataviewer']:
                self.assertEqual(run([*normal, name]), '2.0.0')
            shell = updater.commands(uv, 'prerelease', str(requirements))[-1][1]
            shell.remove('--refresh')
            self.assertIn('matplotlib==2.0.0', run(shell))


if __name__ == '__main__':
    unittest.main()
