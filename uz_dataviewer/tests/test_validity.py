"""Source changes and invalid derived data must never look like current results."""
import numpy as np
import pytest

from uz_dataviewer.loader import open_file
from uz_dataviewer.model import DataRegistry
from uz_dataviewer.nodes import evaluate, is_stale
from uz_dataviewer.panels.plots import PlotsPanel
from uz_dataviewer.session import export_data, export_fft, export_histogram


def write_csv(path, value=1):
    path.write_text('time;y\n' + ''.join(f'{i};{value+i}\n' for i in range(8)))


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('disk_cache', [False, True])
def test_changed_csv_invalidates_all_reads(tmp_path, backend, disk_cache):
    path = tmp_path / 'data.csv'
    write_csv(path)
    run = open_file(str(path), 'lazy', cache_dir=tmp_path/'cache', backend=backend,
                    disk_cache=disk_cache).register(DataRegistry())
    run.read_window(['y'], 0, 7)
    write_csv(path, 99)
    with pytest.raises(ValueError, match='Source changed'):
        run.data_source().validate()
    with pytest.raises(ValueError, match='Source changed'):
        run.read_window(['y'], 0, 7)
    reopened = open_file(str(path), 'lazy', cache_dir=tmp_path/'cache', backend=backend,
                         disk_cache=disk_cache).register(DataRegistry())
    assert reopened.read_window(['y'], 0, 7)[1]['y'][0] == 99


def test_conversion_does_not_publish_cache_if_original_changed(tmp_path, monkeypatch):
    from uz_dataviewer import loader
    path, cache = tmp_path/'data.csv', tmp_path/'cache'
    write_csv(path)
    convert = loader.convert_csv_to_parquet
    def changing(*args, **kwargs):
        result = convert(*args, **kwargs)
        write_csv(path, 99)
        return result
    monkeypatch.setattr(loader, 'convert_csv_to_parquet', changing)
    with pytest.raises(ValueError, match='Source changed'):
        open_file(str(path), 'lazy', cache_dir=cache, disk_cache=True)
    assert not list(cache.glob('*.parquet'))


def graph(state, run):
    src = state.nodes.add('source', ref=(run.id, 'y'))
    a, b = state.nodes.add('math'), state.nodes.add('math')
    state.nodes.link(src.id, a.id)
    state.nodes.link(a.id, b.id)
    assert evaluate(state) == 2
    return a, b


def test_nodes_validate_source_before_reusing_results(app_state, tmp_path):
    state = app_state
    state.backend, state.loading_mode = 'pyarrow', 'lazy'
    path = tmp_path/'data.csv'
    write_csv(path)
    a, b = graph(state, state.load_sync(str(path)))
    write_csv(path, 99)
    assert is_stale(state, state.nodes, a) and is_stale(state, state.nodes, b)
    assert evaluate(state) == 0
    assert 'Source changed' in a.error and b.error
    for node in (a, b):
        with pytest.raises(ValueError, match='not current'):
            state.registry.get(node.out_run_id).read_window(['out'], 0, 7)


@pytest.mark.parametrize('exporter', [export_data, export_fft, export_histogram])
def test_failed_nodes_block_exports_and_recover_in_place(app_state, tmp_path, exporter):
    state = app_state
    run = state.registry.add_run('input', 'input', np.arange(8.), {'y':np.arange(8.)}, {})
    a, b = graph(state, run)
    output = state.registry.get(b.out_run_id)
    ref = (output.id, 'out')
    state.cells[0].signals = state.fft.sources = state.histogram.sources = [ref]
    state.fft.follow_plot = state.histogram.follow_plot = -1
    a.params['k'] = 'bad'
    assert evaluate(state) == 0
    path = tmp_path/'export.csv'
    path.write_text('existing')
    args = (state, 0, str(path)) if exporter is export_data else (state, str(path))
    with pytest.raises(ValueError, match='not current'):
        exporter(*args)
    assert path.read_text() == 'existing'
    a.params['k'] = '2'
    assert evaluate(state) == 2
    assert state.registry.get(b.out_run_id) is output
    np.testing.assert_array_equal(output.read_window(['out'], 0, 7)[1]['out'], np.arange(8.)*2)
    exporter(*args)
    assert path.read_text() != 'existing'
    assert state.cells[0].signals == [ref]


def test_invalid_output_clears_cached_plots_and_analysis(app_state, gui_frame, monkeypatch):
    from imgui_bundle import implot
    from uz_dataviewer.panels.fft import FftPanel
    state = app_state
    state.analysis_jobs.synchronous = True
    run = state.registry.add_run('input', 'input', np.arange(8.), {'y':np.arange(8.)}, {})
    a, b = graph(state, run)
    ref = (b.out_run_id, 'out')
    state.cells[0].signals = state.fft.sources = [ref]
    state.fft.follow_plot, state.fft.compute_requested = -1, True
    plots, fft = PlotsPanel(), FftPanel()
    for _ in range(3):
        gui_frame(plots, state)
        gui_frame(fft, state)
    assert fft._results
    drawn = []
    monkeypatch.setattr(implot, 'plot_line', lambda *args: drawn.append(args))
    a.params['k'] = 'bad'
    evaluate(state)
    gui_frame(plots, state)
    gui_frame(fft, state)
    assert not drawn and not fft._results and not state.display.results
    assert 'not current' in fft._info
