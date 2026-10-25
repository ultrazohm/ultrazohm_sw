"""Lazy/eager contract, persisted caches, raw-analysis parity and cancellation."""
import os
import sys
import threading
import time
from pathlib import Path

import numpy as np
import pyarrow as pa
import pyarrow.parquet as pq
import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'src'))
from uz_dataviewer.sources import ArraySource, ParquetSource, ByteCache, SourceColumn, Cancelled
from uz_dataviewer.requests import Requests
from uz_dataviewer.loader import open_file
from uz_dataviewer.model import DataRegistry
from uz_dataviewer.state import AppState
from uz_dataviewer.analysis import compute_fft
from uz_dataviewer.session import to_dict, apply_dict, export_data, export_fft, export_histogram


@pytest.fixture(params=["pyarrow", "polars"], autouse=True)
def source_backend(request, monkeypatch):
    """Exercise the same source contract and GUI regressions with both engines."""
    if request.param == "polars":
        from uz_dataviewer.polars_source import PolarsParquetSource
        module = sys.modules[__name__]
        monkeypatch.setattr(module, "ParquetSource", PolarsParquetSource)
        original_open = open_file
        monkeypatch.setattr(module, "open_file", lambda *args, **kwargs:
                            original_open(*args, **kwargs, backend="polars"))
    original_state = AppState
    class BackendState(original_state):
        def __init__(self):
            super().__init__()
            self.backend = request.param
    monkeypatch.setattr(sys.modules[__name__], "AppState", BackendState)



@pytest.fixture
def recording(tmp_path):
    t = np.arange(180123, dtype=np.float64) * .001 + 3
    t[65534:65540] = t[65534]  # duplicates spanning timestamp-index batch boundary
    y = np.sin(t).astype(np.float32)
    y[1011], y[40001], y[120011] = 17, -23, 31
    y[70001:70006] = np.nan
    path = tmp_path / 'samples.parquet'
    pq.write_table(pa.table({'time': t, 'a': y, 'b': y * 2}), path, row_group_size=70000)
    return path, t, y


def test_raw_ranges_duplicates_and_normalization(recording, tmp_path):
    path, t, y = recording
    cache = ByteCache(2 * 1024**2)
    source = ParquetSource(path, cache, tmp_path / 'cache', disk_cache=True)
    eager = ArraySource(t, {'a': y})
    for lo, hi in [(t[0], t[-1]), (t[65534], t[65534]), (t[500] + .0002, t[503]), (-10, -9), (999, 1000)]:
        a, b = source.bounds(lo, hi)
        assert (a, b) == eager.bounds(lo, hi)
        ts, ys = source.read_rows(['a'], a, b)
        np.testing.assert_array_equal(ts, t[a:b])
        np.testing.assert_array_equal(ys['a'], y[a:b])
    assert cache.bytes <= cache.limit
    registry = DataRegistry()
    run = registry.add_source('samples', str(path), source)
    run.set_time_origin(0)
    assert isinstance(run.time, SourceColumn)
    ts, ys = run.read_window(['a'], .1, .2)
    a, b = source.bounds(t[0] + .1, t[0] + .2)
    np.testing.assert_allclose(ts, t[a:b] - t[0])
    np.testing.assert_array_equal(ys['a'], y[a:b])
    run.set_time_origin(None)
    assert run.time[0] == t[0]


def test_summary_extrema_gaps_boundaries_and_reopen(recording, tmp_path, monkeypatch):
    path, t, y = recording
    root = tmp_path / 'cache'
    source = ParquetSource(path, cache_dir=root, disk_cache=True)
    result = source.read_plot('a', t[0], t[-1], 200)
    assert np.nanmin(result.values) == -23
    assert np.nanmax(result.values) == 31
    assert np.isnan(result.values).any()
    assert len(result.values) <= 300
    assert np.all(np.diff(result.time) >= 0)
    for start, stop in [(1023, 120003), (1012, 40000), (70001, 70002), (180000, 180122)]:
        lo, hi = t[start], t[stop]
        a, b = source.bounds(lo, hi)
        result = source.read_plot('a', lo, hi, 100)
        assert result.time.min() >= t[a]
        assert result.time.max() <= t[b - 1]
        if np.isfinite(y[a:b]).any():
            assert np.nanmin(result.values) == np.nanmin(y[a:b])
            assert np.nanmax(result.values) == np.nanmax(y[a:b])
    reopened = ParquetSource(path, cache_dir=root, disk_cache=True)
    def no_build(*args, **kwargs):
        raise AssertionError('Summary rebuilt on reopen')
    monkeypatch.setattr(reopened, 'iter_raw', no_build)
    assert reopened._summary('a', None)[0].dtype.names == ('i', 't', 'y')


def test_cache_corruption_rebuild_and_changed_file(recording, tmp_path):
    path, t, y = recording
    root = tmp_path / 'cache'
    source = ParquetSource(path, cache_dir=root, disk_cache=True)
    source.read_plot('a', t[0], t[-1], 200)
    source.summary_path('a').write_bytes(b'broken')
    (source.directory / 'time.npz').write_bytes(b'broken')
    reopened = ParquetSource(path, cache_dir=root, disk_cache=True)
    assert np.nanmax(reopened.read_plot('a', t[0], t[-1], 200).values) == 31
    stat = path.stat()
    os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns + 1000))
    with pytest.raises(ValueError, match='Source changed'):
        source.read_plot('a', t[0], t[-1], 200)


def test_raw_fft_export_and_session_parity(tmp_path):
    t = np.arange(8192) / 1024.
    y = np.sin(2 * np.pi * 32 * t).astype(np.float32)
    path = tmp_path / 'tone.parquet'
    pq.write_table(pa.table({'time': t, 'a': y}), path, row_group_size=777)
    states = []
    for mode in ('memory', 'lazy'):
        state = AppState()
        state.cache_dir = tmp_path / 'cache'
        state.loading_mode = mode
        run = state.load_sync(str(path))
        assert run is not None
        state.cells[0].add((run.id, 'a'))
        state.plot_x_ranges[1] = (1., 2.)
        state.fft.sources = [(run.id, 'a')]
        state.histogram.sources = [(run.id, 'a')]
        states.append(state)
        result = compute_fft(run.time, run.signals['a'].y, 1., 2.)
        assert result.ok
        if mode == 'memory':
            expected = result
        else:
            np.testing.assert_array_equal(result.mag, expected.mag)
        export_data(state, 0, str(tmp_path / f'{mode}-data.csv'))
        export_fft(state, str(tmp_path / f'{mode}-fft.csv'))
        export_histogram(state, str(tmp_path / f'{mode}-hist.csv'))
    for kind in ('data', 'fft', 'hist'):
        assert (tmp_path / f'memory-{kind}.csv').read_bytes() == (tmp_path / f'lazy-{kind}.csv').read_bytes()
    restored = AppState()
    restored.cache_dir = tmp_path / 'cache'
    apply_dict(restored, to_dict(states[1]))
    assert restored.loading_mode == 'lazy'
    assert isinstance(restored.registry.runs[0].time, SourceColumn)
    for state in states + [restored]:
        state.shutdown()


def test_memory_and_lazy_csv_cache(tmp_path):
    path = tmp_path / 'input.csv'
    path.write_text('time;a\n0;1\n1;2\n2;3\n')
    registry = DataRegistry()
    run = open_file(str(path), 'lazy', cache_dir=tmp_path / 'cache').register(registry)
    assert isinstance(run.time, SourceColumn)
    np.testing.assert_array_equal(run.signals['a'].y[:], [1, 2, 3])
    run = open_file(str(path), 'memory').register(registry)
    assert isinstance(run.time, np.ndarray)
    run = open_file(str(path), 'lazy', cache_dir=tmp_path / 'cache').register(registry)
    assert isinstance(run.time, SourceColumn)


def test_requests_coalesce_discard_stale_and_release():
    requests = Requests()
    started = threading.Event()
    release = threading.Event()
    def old(cancel):
        started.set()
        release.wait(3)
        return 'old'
    try:
        requests.request('plot', 0, 'source', old)
        assert started.wait(2)
        for n in range(1, 100):
            requests.request('plot', n, 'source', lambda cancel, n=n: n)
        assert len(requests.jobs) == 1
        release.set()
        deadline = time.monotonic() + 3
        while not requests.ready('plot', 99):
            assert time.monotonic() < deadline
            time.sleep(.001)
        assert requests.request('plot', 99, 'source', None) == 99
        requests.retain(set())
        assert not requests.results
    finally:
        release.set()
        requests.close()


def test_cancellation_and_budget(recording, tmp_path):
    path, t, y = recording
    cache = ByteCache(10)
    cache.put('x', np.zeros(5), 40)
    assert cache.bytes == 0
    source = ParquetSource(path, cache, tmp_path / 'cache', disk_cache=True)
    cancel = threading.Event()
    cancel.set()
    with pytest.raises(Cancelled):
        source.read_plot('a', t[0], t[-1], 200, cancel)
    assert not source.summary_path('a').exists()


def test_source_node_crop_matches_eager(recording, tmp_path):
    from uz_dataviewer.commands import parse_call
    path, _, _ = recording
    outputs = []
    for mode in ('memory', 'lazy'):
        state = AppState()
        state.loading_mode, state.cache_dir = mode, tmp_path / 'cache'
        state.load_sync(str(path))
        for line in ('node_source(run_1, a)', 'node_set(node_1, tmin, 5)',
                     'node_set(node_1, tmax, 6)', 'node_add(math)',
                     'node_link(node_1, node_2)', 'node_eval()'):
            state.commands.execute(state, *parse_call(line))
        run = next(r for r in state.registry.runs if r.derived)
        outputs.append((run.time, run.signals['out'].y))
        state.shutdown()
    np.testing.assert_array_equal(outputs[0][0], outputs[1][0])
    np.testing.assert_array_equal(outputs[0][1], outputs[1][1])


def test_lazy_frame_does_not_read_raw_on_gui_thread(recording, tmp_path, monkeypatch):
    from imgui_bundle import imgui, implot
    from uz_dataviewer.panels.plots import PlotsPanel
    path, _, _ = recording
    state = AppState()
    state.loading_mode, state.cache_dir = 'lazy', tmp_path / 'cache'
    run = state.load_sync(str(path))
    source = run.data_source()
    original = source.read_rows
    gui_thread = threading.get_ident()
    def guarded(*args, **kwargs):
        assert threading.get_ident() != gui_thread, 'Raw read on the GUI thread'
        return original(*args, **kwargs)
    monkeypatch.setattr(source, 'read_rows', guarded)
    state.cells[0].add((run.id, 'a'))
    state.cells[0].spy = True
    state.cells[0].cursors = True
    panel = PlotsPanel()
    imgui.create_context()
    implot.create_context()
    io = imgui.get_io()
    io.display_size = imgui.ImVec2(1200, 800)
    io.delta_time = 1 / 60
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    try:
        deadline = time.monotonic() + 10
        for n in range(100):
            assert time.monotonic() < deadline
            imgui.new_frame()
            imgui.set_next_window_size(imgui.ImVec2(1000, 700))
            imgui.begin('lazy')
            panel.render(state)
            imgui.end()
            imgui.render()
            if n > 4 and not state.display.pending:
                break
            time.sleep(.005)
        assert not state.display.errors
        assert panel._last_points[0] > 0
    finally:
        state.shutdown()
        implot.destroy_context()
        imgui.destroy_context()


def test_auto_loading_is_rejected(tmp_path):
    with pytest.raises(ValueError, match="memory or lazy"):
        open_file(str(tmp_path / 'unused.parquet'), 'auto')
    state = AppState()
    try:
        with pytest.raises(ValueError, match="Unknown loading mode"):
            state.request_load('unused.parquet', loading_mode='auto')
    finally:
        state.shutdown()


def test_invalid_time_axis_is_rejected(tmp_path):
    for t in ([0., 1., .5], [0., float('nan'), 2.], []):
        path = tmp_path / 'bad.parquet'
        pq.write_table(pa.table({'time': np.asarray(t, dtype=np.float64),
                                 'a': np.zeros(len(t), dtype=np.float32)}), path)
        with pytest.raises(ValueError):
            source = ParquetSource(path, cache_dir=tmp_path / 'cache', disk_cache=True)
            source.bounds(0, 2)


def test_open_uses_footer_then_validates_on_first_query(recording, tmp_path):
    path, t, _ = recording
    source = ParquetSource(path, cache_dir=tmp_path / 'cache', disk_cache=True)
    assert source.metadata.rows == len(t)
    assert not source._index_ready
    assert not (source.directory / 'time.npz').exists()
    source.bounds(t[10], t[20])
    assert source._index_ready
    assert (source.directory / 'time.npz').exists()


def test_idle_worker_does_not_retain_source():
    import gc
    import weakref
    requests = Requests()
    source = ArraySource(np.arange(10.), {'a': np.ones(10, dtype=np.float32)})
    reference = weakref.ref(source)
    requests.request('plot', 'key', 'source', lambda cancel, src=source: src.metadata.rows)
    del source
    deadline = time.monotonic() + 3
    try:
        while requests.pending:
            assert time.monotonic() < deadline
            time.sleep(.001)
        gc.collect()
        assert reference() is None
    finally:
        requests.close()


@pytest.mark.parametrize('budget', [128, 512, 2000])
@pytest.mark.parametrize('backend', ['memory', 'parquet'])
def test_close_zoom_uses_raw_window_when_finest_summary_is_too_coarse(recording, tmp_path, monkeypatch, budget, backend):
    from uz_dataviewer.sources import envelope
    path, t, y = recording
    source = (ArraySource(t, {'a': y}) if backend == 'memory'
              else ParquetSource(path, cache_dir=tmp_path / 'cache', disk_cache=True))
    # Reproduce the ~13k-sample screenshot window, offset from summary boundaries.
    lo, hi = t[40013], t[53013]
    start, stop = source.bounds(lo, hi)
    expected_t, expected_y = envelope(t[start:stop], y[start:stop], np.arange(start, stop), budget)
    def no_coarse_summary(*args, **kwargs):
        raise AssertionError('Close zoom must read raw samples, not the coarse summary')
    monkeypatch.setattr(source, '_summary', no_coarse_summary)
    result = source.read_plot('a', lo, hi, budget)
    assert result.raw_count == stop - start
    np.testing.assert_array_equal(result.time, expected_t)
    np.testing.assert_array_equal(result.values, expected_y)
    middle = (result.time > lo + (hi - lo) / 4) & (result.time < hi - (hi - lo) / 4)
    assert middle.sum() >= budget // 3


def test_summary_zoom_transition_keeps_interior_detail():
    from uz_dataviewer.sources import BASE
    n = 1_100_000
    t = np.arange(n, dtype=np.float64) * .0001
    y = np.sin(np.arange(n) * 1.7).astype(np.float32)
    source = ArraySource(t, {'a': y})
    budget = 2000
    for count in (BASE * (budget // 2) - 10, BASE * (budget // 2) + 10):
        start = 503
        result = source.read_plot('a', t[start], t[start + count], budget)
        middle = (result.time > t[start + count // 4]) & (result.time < t[start + 3 * count // 4])
        assert middle.sum() >= budget // 3
        assert np.diff(result.time).max() < (t[start + count] - t[start]) / 100


def test_per_file_loading_mode_does_not_change_default(tmp_path):
    path = tmp_path / 'mode.parquet'
    pq.write_table(pa.table({'time': np.arange(10, dtype=np.float64),
                            'a': np.ones(10, dtype=np.float32)}), path)
    state = AppState()
    state.cache_dir = tmp_path / 'cache'
    state.loading_mode = 'memory'
    try:
        state.request_load(str(path), loading_mode='lazy')
        state.request_load(str(path), loading_mode='memory')
        for future, _ in state._pending:
            future.result(timeout=10)
        state.poll_pending_loads()
        assert isinstance(state.registry.runs[0].time, SourceColumn)
        assert isinstance(state.registry.runs[1].time, np.ndarray)
        assert state.loading_mode == 'memory'
    finally:
        state.shutdown()


@pytest.mark.parametrize('format', ['csv', 'parquet'])
@pytest.mark.parametrize('persistent', [False, True])
def test_optional_disk_cache_parity(recording, tmp_path, format, persistent):
    path, t, y = recording
    if format == 'csv':
        path = tmp_path / 'input.csv'
        # Round-trip float32 signal values, including gaps and extrema.
        np.savetxt(path, np.column_stack([t, y, y * 2]), delimiter=';',
                   header='time;a;b', comments='', fmt='%.17g')
    root = tmp_path / 'optional-cache'
    source = open_file(str(path), 'lazy', cache_dir=root, disk_cache=persistent).source
    raw_t, raw_y = source.read_rows(['a'], 65530, 65550)
    np.testing.assert_array_equal(raw_t, t[65530:65550])
    np.testing.assert_allclose(raw_y['a'], y[65530:65550], equal_nan=True)
    plot = source.read_plot('a', t[0], t[-1], 200)
    assert np.nanmin(plot.values) == -23
    assert np.nanmax(plot.values) == 31
    if persistent:
        assert list(root.rglob('*.npz'))
        assert bool(list(root.rglob('*.parquet'))) == (format == 'csv')
    else:
        assert not root.exists()
    # Raw windows remain available after summary/timestamp eviction.
    source.cache.clear()
    np.testing.assert_allclose(source.read_rows(['a'], 70000, 70010)[1]['a'],
                               y[70000:70010], equal_nan=True)
    if not persistent:
        assert not root.exists()


def test_disabled_disk_cache_ignores_existing_files(recording, tmp_path):
    path, t, _ = recording
    root = tmp_path / 'existing-cache'
    source = open_file(str(path), 'lazy', cache_dir=root, disk_cache=True).source
    source.read_plot('a', t[0], t[-1], 200)
    for file in root.rglob('*.npz'):
        file.write_bytes(b'existing cache must remain untouched')
    before = {p: p.read_bytes() for p in root.rglob('*') if p.is_file()}
    source = open_file(str(path), 'lazy', cache_dir=root).source
    assert source.summary_path('a') is None
    source.read_plot('a', t[0], t[-1], 200)
    assert {p: p.read_bytes() for p in root.rglob('*') if p.is_file()} == before
