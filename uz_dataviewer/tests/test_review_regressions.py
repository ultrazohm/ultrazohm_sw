"""Regressions found by the source/session/lifecycle review."""
import threading
import time
import weakref
from types import SimpleNamespace

import numpy as np
import pytest

from uz_dataviewer.analysis import compute_fft, histogram_sources
from uz_dataviewer.commands import _fmt_str, parse_call, CommandError
from uz_dataviewer.loading import LoadExecutor
from uz_dataviewer.session import to_dict, apply_dict, to_script
from uz_dataviewer.sources import ArraySource, Metadata, Cancelled, check
from uz_dataviewer.state import AppState, PlotType
from uz_dataviewer.transforms import filter_node


@pytest.mark.parametrize('script', [False, True])
def test_sessions_preserve_duplicate_names_and_instances(tmp_path, script):
    states = [AppState(), AppState()]
    source, restored = states
    try:
        for directory, value in [('one', 1), ('two', 10)]:
            path = tmp_path / directory / 'log.csv'
            path.parent.mkdir()
            path.write_text(f'time;a\n0;{value}\n1;{value+1}\n')
            source.load_sync(str(path))
        source.loading_mode = 'memory'
        source.load_sync(str(tmp_path/'one/log.csv'))
        source.registry.runs[2].set_time_origin(5)
        source.cells[0].signals = [(r.id, 'a') for r in source.registry.runs]
        # A restore must replace, rather than reuse, an existing recording.
        restored.load_sync(str(tmp_path/'two/log.csv'))
        if script:
            for line in to_script(source):
                if not line.startswith('#'):
                    name, args = parse_call(line)
                    restored.commands.execute(restored, name, args)
        else:
            apply_dict(restored, to_dict(source))
        runs = restored.registry.runs
        assert len(runs) == 3
        assert [float(r.signals['a'].y[0]) for r in runs] == [1, 10, 1]
        assert [r.id for r in runs] == [ref[0] for ref in restored.cells[0].signals]
        assert runs[2].time_origin == 5
        assert isinstance(runs[2].time, np.ndarray)
    finally:
        for s in states:
            s.shutdown()


def test_histogram_exact_window():
    source = ArraySource(np.arange(3.), {'a':np.arange(3.,dtype=np.float32)})
    assert histogram_sources([('a',source,'a',0)], .9, 1.1, 5)[1] == 1
    assert histogram_sources([('a',source,'a',0)], 10, 11, 5)[1] == 0


@pytest.mark.parametrize('timestamps', [[0,0,0,100], [0,1,2,4], [0,1,np.nan,3]])
def test_fft_rejects_irregular_time(timestamps):
    assert not compute_fft(np.array(timestamps,dtype=float), np.arange(4.), 0,100).ok


def test_short_filter_keeps_length():
    t = np.arange(10.)
    out_t, out_y, _ = filter_node(t, t, {'type':'low', 'cutoff':.1})
    assert out_t.shape == out_y.shape == (10,)


@pytest.mark.parametrize('value', ['a"b.csv', '', "a'b.csv", ' leading ', r'C:\logs\a.csv', 'comma,name'])
def test_script_string_roundtrip(value):
    assert parse_call('load('+_fmt_str(value)+')')[1] == [value]


def test_unterminated_quote_rejected():
    with pytest.raises(CommandError):
        parse_call('load("incomplete)')


def test_load_shutdown_cancels_active_and_queued_work():
    worker = LoadExecutor()
    started = threading.Event()
    stopped = threading.Event()
    def work(cancel):
        started.set()
        try:
            while True:
                check(cancel)
                time.sleep(.005)
        finally:
            stopped.set()
    active = worker.submit(work)
    assert started.wait(2)
    queued = worker.submit(work)
    worker.shutdown()
    assert stopped.wait(2)
    with pytest.raises(Cancelled):
        active.result()
    assert queued.cancelled()
    assert worker.thread.daemon


def test_async_xy_fits_and_releases_input_batches():
    from imgui_bundle import imgui, implot
    from uz_dataviewer.panels.plots import PlotsPanel
    state = AppState()
    references, alive, limits = [], [], []
    def batches(channels, start=0, stop=None, cancel=None):
        for i in range(20):
            check(cancel)
            values = np.linspace(100,200,20000,dtype=np.float32)
            if channels == ['b']:
                values += 200
                time.sleep(.002)
            references.append(weakref.ref(values))
            alive.append(sum(ref() is not None for ref in references))
            yield np.arange(20000), {name:values for name in channels}
    source = SimpleNamespace(metadata=Metadata('xy-review',400000,('a','b'),(0,400000)),
                             units={'a':'','b':''}, iter_raw=batches, validate=lambda: None)
    run=state.registry.add_source('test','test',source)
    cell=state.cells[0]
    cell.plot_type=PlotType.XY
    cell.xy_source=(run.id,'a')
    cell.add((run.id,'a'))
    cell.add((run.id,'b'))
    imgui.create_context(); implot.create_context()
    io=imgui.get_io(); io.set_ini_filename(None)
    io.display_size=imgui.ImVec2(1000,800); io.delta_time=1/60
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    panel=PlotsPanel()
    original_end=implot.end_plot
    def end():
        view=implot.get_plot_limits()
        limits.append((view.x.min,view.x.max,view.y.min,view.y.max))
        original_end()
    implot.end_plot=end
    try:
        for _ in range(40):
            imgui.new_frame(); imgui.set_next_window_size(imgui.ImVec2(1000,800))
            imgui.begin('XY regression'); panel.render(state); imgui.end(); imgui.render()
            time.sleep(.01)
        assert limits[-1][0] <= 100 and limits[-1][1] > 190
        assert limits[-1][3] > 390
        # Alignment keeps one batch per input, plus a transient replacement
        # batch while an iterator advances. Retention must stay bounded.
        assert max(alive) <= 3
        assert not state.display.errors
    finally:
        implot.end_plot=original_end
        state.shutdown(); implot.destroy_context(); imgui.destroy_context()


def test_script_aborts_when_a_recording_cannot_load(tmp_path):
    from uz_dataviewer.session import run_script
    state = AppState()
    script = tmp_path / 'missing.uzscript'
    script.write_text('load("missing.csv")\nset_grid(2,2)\n')
    try:
        with pytest.raises(CommandError, match='Failed to load'):
            run_script(state, str(script))
        assert state.cell_count == 1
    finally:
        state.shutdown()


def test_node_output_shape_validation():
    from uz_dataviewer.nodes import TransformSpec, Node, REGISTRY, _compute
    spec = TransformSpec('bad_shape', lambda inputs, params: (np.arange(2.), np.arange(3.), 'bad'))
    REGISTRY['bad_shape'] = spec
    try:
        with pytest.raises(ValueError, match='equal-length'):
            _compute(Node(1, 'bad_shape', 'bad'), [(np.arange(2.), np.arange(2.))])
    finally:
        REGISTRY.pop('bad_shape')


def _slow_native_conversion(source, destination, backend, connection):
    from pathlib import Path
    Path(destination).write_bytes(b'partial')
    time.sleep(30)


def test_cancel_conversion_stops_process_and_removes_temporary_file(tmp_path, monkeypatch):
    import uz_dataviewer.loading as loading
    from pathlib import Path
    monkeypatch.setattr(loading, '_convert_worker', _slow_native_conversion)
    monkeypatch.setattr('uz_dataviewer.state.LARGE_CSV_BYTES', 1)
    state = AppState()
    path = tmp_path / 'input.csv'
    path.write_text('time;a\n0;1\n1;2\n')
    try:
        state.request_load(str(path))
        state.resolve_large_csv('convert')
        future = state._pending[0][0]
        deadline = time.monotonic()+10
        while time.monotonic() < deadline:
            files = list(tmp_path.glob('.uz-convert-*'))
            if files and files[0].stat().st_size:
                break
            time.sleep(.01)
        else:
            pytest.fail('Conversion process did not start')
        state.shutdown()
        with pytest.raises(Cancelled):
            future.result(timeout=5)
        assert not list(tmp_path.glob('.uz-convert-*'))
        assert not path.with_suffix('.parquet').exists()
    finally:
        state.shutdown()


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
