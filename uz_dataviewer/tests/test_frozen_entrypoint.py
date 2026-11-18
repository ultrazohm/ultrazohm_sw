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
