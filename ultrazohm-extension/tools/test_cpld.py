"""CPLD diagnostics must run both checks and propagate failures."""
import importlib.util
from pathlib import Path
import sys
import unittest
from unittest.mock import Mock, patch

spec = importlib.util.spec_from_file_location('cpld_check', Path(__file__).resolve().parents[1] / 'cpld-check.py')
cpld_check = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cpld_check)


class CpldCheckTest(unittest.TestCase):
    def test_checks_run_in_order_and_report_either_failure(self):
        for codes in [(0, 0), (7, 0), (0, 8), (7, 8)]:
            with self.subTest(codes=codes), patch.object(sys, 'argv', ['check', '--uv', '/private runtime/uv', '--channel', 'prerelease']), patch.object(cpld_check.subprocess, 'run', side_effect=[Mock(returncode=code) for code in codes]) as run:
                self.assertEqual(cpld_check.main(), codes[0] or codes[1])
                commands = [call.args[0] for call in run.call_args_list]
                self.assertEqual(commands[0][-1], 'doctor')
                self.assertEqual(commands[1][-2:], ['programmer_gui', '--check'])
                self.assertTrue(all(command[0] == '/private runtime/uv' and 'allow' in command for command in commands))


if __name__ == '__main__':
    unittest.main()
