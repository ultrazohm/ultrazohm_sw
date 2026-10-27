"""Setup-only mode must install into the destination without launching acquisition."""
import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
spec = importlib.util.spec_from_file_location('cli_setup_uv', ROOT/'setup_uv.py')
setup = importlib.util.module_from_spec(spec)
spec.loader.exec_module(setup)


class SetupOnlyTest(unittest.TestCase):
    def test_run_defaults_can_be_overridden_to_setup_only_without_examples(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            env = root/'viewer environment'
            scripts = env/('Scripts' if sys.platform == 'win32' else 'bin')
            scripts.mkdir(parents=True)
            (env/'pyvenv.cfg').touch()
            (scripts/('python.exe' if sys.platform == 'win32' else 'python')).touch()
            (scripts/('ultrazohm.exe' if sys.platform == 'win32' else 'ultrazohm')).touch()
            wheel = root/'ultrazohm-0.1.0-py3-none-any.whl'
            wheel.touch()
            argv = ['setup_uv.py', '--examples', '--launch', 'cli', '--venv', str(env),
                    '--launch', 'none', '--no-examples', '--wheel', str(wheel)]
            with patch.object(sys, 'argv', argv), \
                 patch.object(setup.shutil, 'which', return_value='/fake/uv'), \
                 patch.object(setup.subprocess, 'check_output', side_effect=[sys.executable, '3.12', '3.12']), \
                 patch.object(setup.subprocess, 'run') as run, \
                 patch.object(setup.subprocess, 'Popen') as popen, \
                 patch.object(setup, 'compatible_wheels', return_value=[wheel]), \
                 patch.object(setup, 'validate_cli_wheel'):
                setup.main()
            popen.assert_not_called()
            commands = [call.args[0] for call in run.call_args_list]
            installs = [cmd for cmd in commands if any('ultrazohm @' in str(arg) for arg in cmd)]
            self.assertEqual(len(installs), 1)
            self.assertNotIn('[examples]', installs[0][-1])
            self.assertIn(str(scripts/('python.exe' if sys.platform == 'win32' else 'python')), installs[0])
