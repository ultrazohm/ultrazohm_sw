"""Conversion publishes complete recordings without overwriting existing files."""

from uz_dataviewer import runtime
import threading

import pytest

from uz_dataviewer import loader
from uz_dataviewer.sources import Cancelled


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
def test_existing_destination_is_never_overwritten(tmp_path, backend):
    source = tmp_path / 'input.csv'
    source.write_text('time;a\n0;1\n1;2\n')
    destination = source.with_suffix('.parquet')
    destination.write_bytes(b'existing recording')
    with pytest.raises(FileExistsError):
        loader.convert_csv_to_parquet(str(source), backend=backend)
    assert destination.read_bytes() == b'existing recording'
    assert not list(tmp_path.glob('.uz-convert-*'))


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
def test_late_parse_failure_leaves_no_output(tmp_path, backend):
    source = tmp_path / 'input.csv'
    source.write_text('time;a\n' + '1;2\n' * 700_000 + '2;bad\n')
    original = source.read_bytes()
    with pytest.raises(Exception, match='bad'):
        loader.convert_csv_to_parquet(str(source), backend=backend)
    assert source.read_bytes() == original
    assert not source.with_suffix('.parquet').exists()
    assert not list(tmp_path.glob('.uz-convert-*'))


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
def test_empty_conversion_fails_without_output(tmp_path, backend):
    source = tmp_path / 'empty.csv'
    source.write_text('time;a\n')
    with pytest.raises(ValueError, match='empty'):
        loader.convert_csv_to_parquet(str(source), backend=backend)
    assert not source.with_suffix('.parquet').exists()
    assert not list(tmp_path.glob('.uz-convert-*'))


def test_destination_created_during_conversion_is_preserved(tmp_path, monkeypatch):
    source = tmp_path / 'input.csv'
    source.write_text('time;a\n0;1\n1;2\n')
    destination = source.with_suffix('.parquet')
    write = loader._write_csv_to_parquet

    def concurrent_writer(*args, **kwargs):
        write(*args, **kwargs)
        destination.write_bytes(b'concurrent recording')

    monkeypatch.setattr(loader, '_write_csv_to_parquet', concurrent_writer)
    with pytest.raises(FileExistsError):
        loader.convert_csv_to_parquet(str(source))
    assert destination.read_bytes() == b'concurrent recording'
    assert not list(tmp_path.glob('.uz-convert-*'))


def test_cancellation_before_publication_cleans_output(tmp_path, monkeypatch):
    import uz_dataviewer.loading as loading
    source = tmp_path / 'input.csv'
    source.write_text('time;a\n0;1\n1;2\n')
    cancel = threading.Event()

    def cancelled_writer(src, dst, backend, event):
        loader._write_csv_to_parquet(src, dst, backend=backend)
        event.set()

    monkeypatch.setattr(loading, 'convert_cancellable', cancelled_writer)
    with pytest.raises(Cancelled):
        loader.convert_csv_to_parquet(str(source), cancel=cancel)
    assert not source.with_suffix('.parquet').exists()
    assert not list(tmp_path.glob('.uz-convert-*'))


def test_browser_conversion_uses_rename_without_hard_links(tmp_path, monkeypatch):
    monkeypatch.setattr(runtime, 'IS_WEB', True)

    def unsupported(*args):
        raise AssertionError('Browser conversion must not require hard links')

    monkeypatch.setattr(loader.os, 'link', unsupported)
    source = tmp_path / 'input.csv'
    source.write_text('time;a\n0;1\n1;2\n')
    destination = loader.convert_csv_to_parquet(str(source))
    parsed = loader.parse_parquet(destination)
    assert parsed.signals['a'].tolist() == [1, 2]
    with pytest.raises(FileExistsError):
        loader.convert_csv_to_parquet(str(source))
    assert not list(tmp_path.glob('.uz-convert-*'))
