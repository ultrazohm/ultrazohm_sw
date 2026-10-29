"""Backend selection is independent of storage policy and survives session restore."""

from uz_dataviewer import runtime

import json
import subprocess
import sys

import numpy as np
import pyarrow as pa
import pyarrow.parquet as pq
import pytest

from uz_dataviewer import api
from uz_dataviewer.commands import CommandError
from uz_dataviewer.loader import convert_csv_to_parquet, open_file
from uz_dataviewer.model import DataRegistry
from uz_dataviewer.session import SCHEMA_VERSION, apply_dict, export_data, to_dict
from uz_dataviewer.sources import ByteCache, SourceColumn
from uz_dataviewer.state import AppState


@pytest.fixture
def logs(tmp_path):
    paths = [tmp_path / 'a.parquet', tmp_path / 'b.parquet']
    t = np.arange(150000, dtype=np.float64) / 1000
    for path in paths:
        pq.write_table(pa.table({'time': t, 'a': np.sin(t).astype(np.float32)}), path, row_group_size=7777)
    return paths


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy'])
def test_backend_and_mode_are_independent(logs, tmp_path, backend, mode):
    run = open_file(str(logs[0]), mode, cache_dir=tmp_path/'cache',
                    backend=backend).register(DataRegistry())
    assert run.backend == backend
    assert isinstance(run.time, SourceColumn) == (mode != 'memory')
    assert run.signals['a'].y[100] == np.float32(np.sin(.1))


def test_mixed_backends_share_cache_without_index_collisions(logs, tmp_path):
    cache = ByteCache()
    sources = [open_file(str(logs[0]), 'lazy', cache, tmp_path/'cache', backend=b).source
               for b in ['pyarrow', 'polars']]
    assert sources[0].metadata.identity != sources[1].metadata.identity
    for lo, hi in [(70., 71.), (130., 132.), (2., 5.)]:
        expected = sources[0].bounds(lo, hi)
        assert sources[1].bounds(lo, hi) == expected
        for source in sources:
            t, _ = source.read_rows(['a'], *expected)
            np.testing.assert_array_equal(t, np.arange(*expected)/1000)


def test_queued_load_captures_backend(logs, tmp_path):
    state = AppState()
    state.cache_dir = tmp_path/'cache'
    try:
        state.backend = 'polars'
        state.disk_cache = True
        state.request_load(str(logs[0]), loading_mode='lazy')
        state.backend = 'pyarrow'
        state.disk_cache = False
        state.request_load(str(logs[1]), loading_mode='memory')
        for future, _ in state.services.pending:
            future.result(timeout=10)
        state.poll_pending_loads()
        assert [r.backend for r in state.registry.runs] == ['polars', 'pyarrow']
        assert isinstance(state.registry.runs[0].time, SourceColumn)
        assert state.registry.runs[0].source.disk_cache
        assert isinstance(state.registry.runs[1].time, np.ndarray)
    finally:
        state.shutdown()


def test_json_keeps_backend_per_file(logs, tmp_path):
    state, restored = AppState(), AppState()
    try:
        for s in [state, restored]:
            s.cache_dir = tmp_path/'cache'
        state.backend, state.loading_mode = 'polars', 'lazy'
        state.load_sync(str(logs[0]))
        state.backend, state.loading_mode = 'pyarrow', 'memory'
        state.load_sync(str(logs[1]))
        saved = json.loads(json.dumps(to_dict(state)))
        apply_dict(restored, saved)
        for s in [restored]:
            assert [r.backend for r in s.registry.runs] == ['polars', 'pyarrow']
            assert isinstance(s.registry.runs[0].time, SourceColumn)
            assert isinstance(s.registry.runs[1].time, np.ndarray)
            assert s.backend == 'pyarrow' and s.loading_mode == 'memory'
    finally:
        for s in [state, restored]: s.shutdown()


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
def test_conversion_export_and_library(tmp_path, backend):
    path = tmp_path/'input.csv'
    path.write_text('time;a;\n0;1;\n1;2;\n2;3;\n3;4;\n')
    parquet = convert_csv_to_parquet(str(path), backend=backend)
    data = api.read(parquet, backend=backend)
    frame = data.to_dataframe()
    assert type(frame).__module__.startswith('polars' if backend == 'polars' else 'pandas')
    state = AppState()
    try:
        state.backend = backend
        run = state.load_sync(parquet)
        state.cells[0].add((run.id, 'a'))
        export_data(state, 0, str(tmp_path/'export.csv'))
        actual = api.read(tmp_path/'export.csv', backend=backend)
        np.testing.assert_array_equal(actual['a'], data['a'])
    finally:
        state.shutdown()


def test_web_uses_pyarrow_for_polars_session(logs, monkeypatch):
    state = AppState()
    monkeypatch.setattr(runtime, 'IS_WEB', True)
    try:
        with pytest.raises(CommandError, match='desktop'):
            state.commands.execute(state, 'backend', ['polars'])
        apply_dict(state, {'version':SCHEMA_VERSION, 'backend':'polars', 'runs':[{'key':'run:1', 'path':str(logs[0]), 'backend':'polars', 'mode':'memory', 'disk_cache':False}]})
        assert state.backend == 'pyarrow'
        assert state.registry.runs[0].backend == 'pyarrow'
    finally:
        state.shutdown()


def test_pyarrow_startup_does_not_import_polars():
    code = 'import sys; from uz_dataviewer.state import AppState; s=AppState(); assert "polars" not in sys.modules; s.shutdown()'
    subprocess.run([sys.executable, '-c', code], check=True, timeout=20)


def test_default_cache_and_removed_auto_controls():
    state = AppState()
    try:
        assert state.registry.cache.limit == 1024 * 1024**2
        assert 'memory_budget' not in {command.name for command in state.commands.all()}
        with pytest.raises(CommandError, match='memory or lazy'):
            state.commands.execute(state, 'loading_mode', ['auto'])
        snapshot = to_dict(state)
        assert 'memory_budget_mb' not in snapshot
    finally:
        state.shutdown()


def test_obsolete_sessions_are_rejected():
    state = AppState()
    try:
        with pytest.raises(ValueError, match='Unsupported session version'):
            apply_dict(state, {'version':1, 'loading_mode':'auto'})
        with pytest.raises(CommandError):
            state.commands.execute(state, 'memory_budget', [512])
    finally:
        state.shutdown()


@pytest.mark.parametrize('online, expected', [(False, ('polars', 'lazy')), (True, ('pyarrow', 'memory'))])
def test_application_defaults_by_platform(monkeypatch, online, expected):
    from uz_dataviewer.app import DataViewerApp
    monkeypatch.setattr(runtime, 'IS_WEB', online)
    app = DataViewerApp()
    try:
        assert (app.state.backend, app.state.loading_mode) == expected
    finally:
        app._shutdown()


def test_cli_defaults_and_explicit_overrides(monkeypatch):
    from uz_dataviewer import app
    captured = []
    class Viewer:
        def __init__(self, **kwargs): captured.append(kwargs)
        def run(self): pass
    monkeypatch.setattr(app, 'DataViewerApp', Viewer)
    mapping_calls = []
    def generate(repo):
        mapping_calls.append(repo)
        return 'cached-mapping.json'
    monkeypatch.setattr('uz_dataviewer.live_mapping.generate_mapping', generate)
    settings_calls = []
    monkeypatch.setattr('uz_dataviewer.settings.initialize_user_settings', settings_calls.append)
    monkeypatch.setattr(runtime, 'IS_WEB', False)
    app.main([])
    assert captured[-1]['disk_cache'] is False
    assert captured[-1]['use_live'] is False
    assert not mapping_calls
    assert (captured[-1]['backend'], captured[-1]['loading_mode']) == ('polars', 'lazy')
    app.main(['--backend', 'pyarrow', '--loading-mode', 'memory', '--disk-cache'])
    assert captured[-1]['disk_cache'] is True
    assert (captured[-1]['backend'], captured[-1]['loading_mode']) == ('pyarrow', 'memory')
    from types import SimpleNamespace
    monkeypatch.setattr(app, 'pfd', SimpleNamespace(select_folder=lambda *a: SimpleNamespace(result=lambda: '/selected/workspace')))
    app.main(['--use-live'])
    assert captured[-1]['use_live'] is True
    assert captured[-1]['live_mapping'] == 'cached-mapping.json'
    assert mapping_calls == ['/selected/workspace']
    assert settings_calls == ['cached-mapping.json']
    app.main(['--use-live', '--live-repo', '/example/repository'])
    assert mapping_calls[-1] == '/example/repository'
    monkeypatch.setattr(runtime, 'IS_WEB', True)
    app.main([])
    assert (captured[-1]['backend'], captured[-1]['loading_mode']) == ('pyarrow', 'memory')


def test_disk_cache_session_settings(logs, tmp_path):
    states = [AppState(), AppState()]
    state, restored = states
    try:
        assert state.disk_cache is False
        state.cache_dir = tmp_path / 'cache'
        state.disk_cache = True
        run = state.load_sync(str(logs[0]))
        assert run is not None and run.source.disk_cache
        state.disk_cache = False
        apply_dict(restored, to_dict(state))
        for s in (restored,):
            assert not s.disk_cache
            assert s.registry.runs[0].source.disk_cache
    finally:
        for s in states:
            s.shutdown()


@pytest.mark.parametrize('backend', ['pyarrow','polars'])
@pytest.mark.parametrize('mode', ['lazy','memory'])
def test_exact_windows_and_exports_across_backends(tmp_path, backend, mode):
    from uz_dataviewer.session import export_data
    from uz_dataviewer.api import read
    state=AppState()
    try:
        path=tmp_path/'samples.csv'
        path.write_text('time;a\n0;1\n1;2\n2;3\n')
        state.backend, state.loading_mode = backend, mode
        run=state.load_sync(str(path))
        state.cells[0].signals=[(run.id,'a')]
        t, values=run.read_window(['a'],.9,1.1)
        np.testing.assert_array_equal(t,[1])
        np.testing.assert_array_equal(values['a'],[2])
        state.plot_x_ranges[1]=(.9,1.1)
        target=tmp_path/'export.csv'
        export_data(state,0,str(target))
        np.testing.assert_array_equal(read(target,backend=backend)['a'],[2])
        state.plot_x_ranges[1]=(10,11)
        export_data(state,0,str(target),relative=True)
        assert len(target.read_text().splitlines())==1  # Header, no samples outside window.
    finally:
        state.shutdown()
