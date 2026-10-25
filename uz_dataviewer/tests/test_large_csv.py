"""GUI large-CSV prompts, captured settings, and safe sibling conversion."""
from pathlib import Path

import numpy as np
import pytest

from uz_dataviewer.state import AppState, LARGE_CSV_BYTES
from uz_dataviewer.sources import SourceColumn


@pytest.fixture
def state():
    state = AppState()
    yield state
    state.shutdown()


def finish(state):
    for future, _ in state._pending:
        future.result(timeout=20)
    state.poll_pending_loads()


def test_threshold_and_queue(state, tmp_path, monkeypatch):
    submitted = []
    monkeypatch.setattr(state, '_submit_load', submitted.append)
    path = tmp_path / 'large.CSV'
    with path.open('wb') as f:
        f.truncate(LARGE_CSV_BYTES)
    state.request_load(str(path))
    assert len(submitted) == 1  # Exactly one GiB does not prompt.
    with path.open('ab') as f:
        f.write(b'0')
    state.request_load(str(path), loading_mode='memory')
    state.request_load(str(path), loading_mode='lazy')
    assert len(submitted) == 1
    assert [r.mode for r in state.large_csv_requests] == ['memory', 'lazy']
    state.resolve_large_csv('cancel')
    state.backend = 'pyarrow'
    state.resolve_large_csv('csv')
    assert submitted[-1].backend == 'polars'
    assert submitted[-1].mode == 'lazy'
    assert not state.large_csv_requests


@pytest.mark.parametrize('backend', ['polars', 'pyarrow'])
@pytest.mark.parametrize('mode', ['memory', 'lazy'])
def test_convert_sibling_and_open(state, tmp_path, monkeypatch, backend, mode):
    monkeypatch.setattr('uz_dataviewer.state.LARGE_CSV_BYTES', 1)
    path = tmp_path / 'large log.csv'
    path.write_text('time;a;\n0;1;\n1;2;\n2;3;\n')
    original = path.read_bytes()
    state.backend, state.loading_mode = backend, mode
    state.request_load(str(path))
    state.backend = 'pyarrow' if backend == 'polars' else 'polars'
    state.loading_mode = 'lazy' if mode == 'memory' else 'memory'
    state.resolve_large_csv('convert')
    finish(state)
    run = state.registry.runs[0]
    assert run.path == str(path.with_suffix('.parquet'))
    assert run.backend == backend
    assert isinstance(run.time, SourceColumn) == (mode == 'lazy')
    np.testing.assert_array_equal(run.signals['a'].y[:], [1, 2, 3])
    assert path.read_bytes() == original
    assert not list(tmp_path.glob('.uz-convert-*'))


def test_open_csv_overrides_disk_conversion(state, tmp_path, monkeypatch):
    monkeypatch.setattr('uz_dataviewer.state.LARGE_CSV_BYTES', 1)
    path = tmp_path / 'input.csv'
    path.write_text('time;a\n0;1\n1;2\n')
    state.disk_cache = True
    state.cache_dir = tmp_path / 'cache'
    state.request_load(str(path))
    state.resolve_large_csv('csv')
    finish(state)
    assert state.registry.runs[0].path == str(path)
    assert not state.registry.runs[0].source.disk_cache
    assert not state.cache_dir.exists()
    assert not path.with_suffix('.parquet').exists()


def test_existing_destination_is_protected(state, tmp_path, monkeypatch):
    monkeypatch.setattr('uz_dataviewer.state.LARGE_CSV_BYTES', 1)
    path = tmp_path / 'input.csv'
    path.write_text('time;a\n0;1\n1;2\n')
    state.request_load(str(path))
    target = path.with_suffix('.parquet')
    target.write_bytes(b'existing data')  # Created after the prompt was queued.
    state.resolve_large_csv('convert')
    with pytest.raises(FileExistsError):
        finish(state)
    assert target.read_bytes() == b'existing data'
    assert not list(tmp_path.glob('.uz-convert-*'))


def test_failed_conversion_cleans_partial_file(state, tmp_path, monkeypatch):
    monkeypatch.setattr('uz_dataviewer.state.LARGE_CSV_BYTES', 1)
    path = tmp_path / 'input.csv'
    path.write_text('time;a\n0;1\n1;2\n')
    def fail(src, dst, **kwargs):
        Path(dst).write_bytes(b'partial')
        raise ValueError('invalid CSV')
    monkeypatch.setattr('uz_dataviewer.loader.convert_csv_to_parquet', fail)
    state.request_load(str(path))
    state.resolve_large_csv('convert')
    with pytest.raises(ValueError, match='invalid CSV'):
        finish(state)
    assert not path.with_suffix('.parquet').exists()
    assert not list(tmp_path.glob('.uz-convert-*'))
