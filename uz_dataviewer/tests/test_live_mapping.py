"""Fresh header mappings, cache provenance, and startup failure behavior."""
import json
from pathlib import Path
import re
import sys
from types import SimpleNamespace

import pytest

from uz_dataviewer import live_mapping


@pytest.fixture
def repo(tmp_path):
    root = tmp_path/'checkout with spaces'
    header = root/live_mapping.HEADER
    header.parent.mkdir(parents=True)
    header.touch()
    return root


def test_generate_mapping_calls_cli_and_publishes_timestamp_commit_cache(repo, monkeypatch):
    calls = []
    mapping = {'repository': {'commit': 'a'*40+'-dirty'}, 'observables': {'JSO_custom': 29}}
    def run(args, **kwargs):
        calls.append(args)
        Path(args[args.index('--output')+1]).write_text(json.dumps(mapping))
        return SimpleNamespace(returncode=0)
    monkeypatch.setattr(live_mapping.subprocess, 'run', run)
    first = live_mapping.generate_mapping(repo)
    second = live_mapping.generate_mapping(repo)
    assert first != second
    assert first.parent == repo/'uz_cli_channel_mappings'
    assert re.fullmatch(r'javascope_\d{8}T\d{6}\.\d{6}Z_a{40}-dirty\.json', first.name)
    assert json.loads(first.read_text()) == mapping
    assert calls[0][:6] == [sys.executable, '-m', 'ultrazohm', 'create-json-from-javascope-h', '--repo', str(repo)]
    assert sorted(first.parent.iterdir()) == sorted([first, second])


def test_generation_failure_keeps_old_cache_but_never_reuses_it(repo, monkeypatch):
    cache = repo/'uz_cli_channel_mappings'
    cache.mkdir()
    old = cache/'old.json'
    old.write_text('old mapping')
    monkeypatch.setattr(live_mapping.subprocess, 'run', lambda *a, **k:
                        SimpleNamespace(returncode=1, stderr='Invalid enum', stdout=''))
    with pytest.raises(RuntimeError, match='Invalid enum'):
        live_mapping.generate_mapping(repo)
    assert list(cache.iterdir()) == [old]
    assert old.read_text() == 'old mapping'


def test_repository_discovery_and_explicit_path_validation(repo, monkeypatch):
    child = repo/'some folder'
    child.mkdir()
    monkeypatch.chdir(child)
    assert live_mapping.repository() == repo
    with pytest.raises(ValueError, match='header not found'):
        live_mapping.repository(child)


def test_invalid_headers_abort_live_startup(monkeypatch):
    from uz_dataviewer import app
    def fail(repo): raise ValueError('Broken header')
    monkeypatch.setattr(live_mapping, 'generate_mapping', fail)
    monkeypatch.setattr(app.runtime, 'IS_WEB', False)
    monkeypatch.setattr(app, 'DataViewerApp', lambda **kwargs: pytest.fail('Viewer must not open'))
    with pytest.raises(SystemExit) as exc:
        app.main(['--use-live'])
    assert exc.value.code == 2


def test_real_cli_generates_mapping_from_headers(tmp_path):
    pytest.importorskip('ultrazohm')
    import shutil
    root = Path(__file__).resolve().parents[2]
    for name in (str(live_mapping.HEADER), 'vitis/software/Baremetal/src/include/javascope_status.h',
                 'vitis/software/shared/APU_RPU_shared.h', 'vitis/software/FreeRTOS/main.h',
                 'vitis/software/FreeRTOS/defines.h', 'tcl_scripts/vitis_headless.tcl'):
        target = tmp_path/name
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(root/name, target)
    path = live_mapping.generate_mapping(tmp_path)
    mapping = json.loads(path.read_text())
    assert mapping['observables']['JSO_lifecheck'] == 3
    assert mapping['channels'] == 20
    assert mapping['repository']['commit'] in path.name


def test_commit_cache_is_overwritten_with_fresh_headers(repo, monkeypatch):
    version = [1]
    def run(args, **kwargs):
        mapping = {'repository': {'commit': 'abc123-dirty'}, 'observables': {'changed': version[0]}}
        Path(args[args.index('--output')+1]).write_text(json.dumps(mapping))
        return SimpleNamespace(returncode=0)
    monkeypatch.setattr(live_mapping.subprocess, 'run', run)
    first = live_mapping.generate_mapping(repo, overwrite=True)
    version[0] = 2
    second = live_mapping.generate_mapping(repo, overwrite=True)
    assert first == second
    assert first.name == 'javascope_abc123-dirty.json'
    assert json.loads(second.read_text())['observables']['changed'] == 2
