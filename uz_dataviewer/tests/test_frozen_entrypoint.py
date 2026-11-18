"""Windowed self-test failures must exit, not open a modal error dialog in CI."""
import json
from pathlib import Path
import runpy
import sys
from types import SimpleNamespace

import pytest


def test_self_test_failure_writes_traceback_without_unhandled_exception(tmp_path, monkeypatch):
    report = tmp_path / 'failure.json'
    def fail(_report):
        raise AssertionError('native smoke failure')
    monkeypatch.setitem(sys.modules, 'frozen_self_test', SimpleNamespace(run=fail))
    monkeypatch.setattr(sys, 'argv', ['viewer', '--self-test', str(report)])
    with pytest.raises(SystemExit) as exit_info:
        runpy.run_path(str(Path(__file__).resolve().parents[1] / 'build/entrypoint.py'), run_name='__main__')
    assert exit_info.value.code == 1
    result = json.loads(report.read_text())
    assert result['ok'] is False
    assert 'AssertionError: native smoke failure' in result['error']


def test_terminal_help_survives_windows_legacy_encoding():
    import os
    import subprocess
    result = subprocess.run([sys.executable, '-m', 'uz_dataviewer.cli', '--help'],
                            env={**os.environ, 'PYTHONIOENCODING': 'cp1252:strict'},
                            capture_output=True, timeout=10)
    assert result.returncode == 0, result.stderr.decode('cp1252')
    output = result.stdout.decode('cp1252')
    assert 'usage:' in output
    assert '\\u0394' in output  # Δ in generated command help has a readable fallback.
