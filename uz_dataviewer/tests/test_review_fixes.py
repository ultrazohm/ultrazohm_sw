"""Regressions for signal identity, session restoration and node lifecycle."""
import importlib.util
from pathlib import Path
import shutil
import subprocess
import numpy as np
import pytest
from uz_dataviewer import api, nodes, webbridge
from uz_dataviewer.commands import CommandError, parse_call
from uz_dataviewer.loader import open_file
from uz_dataviewer.session import (
    apply_dict, to_dict, export_script, run_script, export_fft, export_histogram, save_state,
)
from uz_dataviewer.state import AppState


@pytest.fixture
def states():
    created = []

    def make():
        state = AppState()
        created.append(state)
        return state
    yield make
    for state in created:
        state.shutdown()


@pytest.fixture
def recording(tmp_path):
    path = tmp_path / 'recording.csv'
    path.write_text('time;a\n' + ''.join((f'{i};{i + 1}\n' for i in range(8))))
    return path


def execute(state, *lines):
    for line in lines:
        state.commands.execute(state, *parse_call(line))


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy'])
@pytest.mark.parametrize('extension', ['csv', 'parquet'])
def test_colliding_channels_preserve_raw_columns(tmp_path, states, backend, mode, extension):
    import pyarrow as pa
    import pyarrow.parquet as pq
    path = tmp_path / f'collision.{extension}'
    names = ['time', 'CH1=1)a', 'a', 'a [2]', 'CH2=2)time']
    arrays = [np.array([i, i + 1.0]) for i in (0, 10, 20, 30, 40)]
    if extension == 'csv':
        path.write_text(';'.join(names) + '\n' + '\n'.join((';'.join(map(str, row)) for row in zip(*arrays))))
    else:
        pq.write_table(pa.table(dict(zip(names, arrays))), path)
    run = open_file(str(path), mode, backend=backend).register(states().registry)
    assert len(run.signals) == 4 and 'time' not in run.signals
    _, values = run.read_window(list(run.signals), 0, 1)
    for actual, expected in zip(values.values(), arrays[1:]):
        np.testing.assert_array_equal(actual, expected)


def test_script_partial_evaluation_uses_node_identity(states, recording, tmp_path):
    state = states()
    state.load_sync(str(recording))
    execute(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)',
            'node_set(node_2,k,2)', 'node_add(math)', 'node_link(node_1,node_3)',
            'node_set(node_3,k,3)', 'node_eval(node_3)', 'add_signal(plot_1,run_2,out)')
    path = tmp_path / 'partial.uzscript'
    export_script(state, str(path))
    restored = states()
    run_script(restored, str(path))
    ref = restored.cells[0].signals[0]
    assert restored.registry.get(ref[0]).label == 'node_3'
    assert restored.registry.get_signal(*ref).y[0] == 3


@pytest.mark.parametrize('exporter,config,axis', [
    (export_fft, 'fft', 'frequency'), (export_histogram, 'histogram', 'bin_center'),
])
def test_exports_preserve_duplicate_recordings(states, tmp_path, exporter, config, axis):
    import pandas as pd
    state = states()
    for i in range(3):
        path = tmp_path / str(i) / 'same.csv'
        path.parent.mkdir()
        path.write_text('time;a\n' + ''.join((f'{j};{(i + 1) * (j + 1)}\n' for j in range(8))))
        run = state.load_sync(str(path))
        getattr(state, config).sources.append((run.id, 'a'))
    getattr(state, config).follow_plot = -1
    path = tmp_path / 'analysis.csv'
    exporter(state, str(path))
    frame = pd.read_csv(path)
    assert frame.columns[0] == axis and len(frame.columns) == 4 and frame.columns.is_unique
    assert len({state.signal_label(ref) for ref in getattr(state, config).sources}) == 3
    if config == 'fft':
        np.testing.assert_allclose(frame.iloc[:, 2], 2 * frame.iloc[:, 1], rtol=1e-6, atol=1e-6)
        np.testing.assert_allclose(frame.iloc[:, 3], 3 * frame.iloc[:, 1], rtol=1e-6, atol=1e-6)
    else:
        np.testing.assert_array_equal(frame.iloc[:, 1:].sum(axis=0), [8, 8, 8])


def test_analysis_remove_uses_reference_after_rename(states, recording):
    from uz_dataviewer.panels.fft import FftPanel
    state = states()
    for _ in range(3):
        run = state.load_sync(str(recording))
        state.fft.sources.append((run.id, 'a'))
    panel = FftPanel()
    panel._compute(state, state.fft, 0, 7)
    state.registry.get(2).label = 'renamed'
    panel._remove(state, panel._result_refs()[1])
    assert state.fft.sources == [(1, 'a'), (3, 'a')]


def test_deleted_output_recreated_and_indirect_source_rejected(states, recording):
    state = states()
    state.load_sync(str(recording))
    execute(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)', 'node_eval()')
    node = state.nodes.get(2)
    with pytest.raises(CommandError, match='node_link'):
        execute(state, f'node_source(run_{node.out_run_id},out)')
    state.remove_run(node.out_run_id)
    assert nodes.evaluate(state, 2) == 1 and state.registry.get(node.out_run_id) is not None


def test_source_version_invalidates_downstream(states, recording):
    from uz_dataviewer.model import Signal
    state = states()
    state.loading_mode = 'memory'
    run = state.load_sync(str(recording))
    execute(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)', 'node_eval()')
    run.signals['a'] = Signal('a', '', np.full(8, 42, dtype=np.float32), run.id)
    assert nodes.is_stale(state, state.nodes, state.nodes.get(2))
    nodes.evaluate(state)
    np.testing.assert_array_equal(state.nodes.get(2).out_y, np.full(8, 42))


@pytest.mark.parametrize('script', [False, True])
def test_failed_restore_preserves_current_session(states, recording, tmp_path, script):
    state = states()
    run = state.load_sync(str(recording))
    state.cells[0].add((run.id, 'a'))
    if script:
        path = tmp_path / 'broken.uzscript'
        export_script(state, str(path))
        path.write_text(path.read_text().replace(str(recording), str(tmp_path / 'missing.csv')))
        restore = lambda: run_script(state, str(path))
    else:
        data = to_dict(state)
        data['runs'][0]['path'] = str(tmp_path / 'missing.csv')
        restore = lambda: apply_dict(state, data)
    with pytest.raises((ValueError, CommandError)):
        restore()
    assert state.registry.get(run.id) is run and state.cells[0].signals == [(run.id, 'a')]
    np.testing.assert_array_equal(run.read_window(['a'], 0, 7)[1]['a'], np.arange(1, 9))


@pytest.mark.parametrize('script', [False, True])
def test_roundtrip_preserves_windows_precision_and_active(states, recording, tmp_path, script):
    state = states()
    run = state.load_sync(str(recording))
    run.active = False
    state.cells[0].add((run.id, 'a'))
    state.plot_x_ranges[1] = (2.0, 4.0)
    state.fft.sources = [(run.id, 'a')]
    state.histogram.sources = [(run.id, 'a')]
    state.histogram.follow_plot = 0
    state.histogram.x_min, state.histogram.x_max = (100.0001, 100.0002)
    restored = states()
    if script:
        path = tmp_path / 'state.uzscript'
        export_script(state, str(path))
        run_script(restored, str(path))
    else:
        apply_dict(restored, to_dict(state))
    assert not restored.registry.get(1).active
    assert restored.resolve_x_window(1, (0, 0), restored.fft.sources) == (2.0, 4.0)
    assert (restored.histogram.x_min, restored.histogram.x_max) == (100.0001, 100.0002)
    assert restored.cells[0].pending_x_lim == (2.0, 4.0)


def test_streamed_session_save_fails_without_truncating_file(states, tmp_path):
    state = states()
    webbridge.register_state(state)
    try:
        webbridge.load_columns('stream.csv', ['a'], [np.arange(8, dtype=np.float32)], np.arange(8.0))
        for save, name in [(save_state, 'state.json'), (export_script, 'state.uzscript')]:
            path = tmp_path / name
            path.write_text('existing')
            with pytest.raises(ValueError, match='backing file'):
                save(state, str(path))
            assert path.read_text() == 'existing'
        assert len(state.registry) == 1
    finally:
        webbridge.register_state(None)


def test_public_node_api_shares_validation(monkeypatch):
    spec = nodes.TransformSpec('bad', lambda inputs, params: (np.arange(2.0), np.arange(3.0), ''))
    monkeypatch.setitem(nodes.REGISTRY, 'bad', spec)
    with pytest.raises(ValueError, match='needs 1 input'):
        api.node('bad')
    with pytest.raises(ValueError, match='equal-length'):
        api.node('bad', (np.arange(4.0), np.arange(4.0)))


def test_generated_browser_stream_parser(tmp_path):
    node = shutil.which('node')
    if node is None:
        pytest.skip('Node.js required for generated browser parser')
    path = Path(__file__).parents[1] / 'build/gen_web.py'
    spec = importlib.util.spec_from_file_location('gen_web_review', path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    html = module.build_html()
    start = html.index('  async function loadStreamingCsv(file)')
    end = html.index('  function wireFileInput()', start)
    harness = r"""
const assert=require('node:assert/strict');
function pyRun(body){}
let loaded;
const pyodide={pyimport:()=>({load_columns:(name,names,columns,time)=>{
 loaded={names,columns:columns.map(x=>Array.from(x)),time:Array.from(time)};
},destroy:()=>{}})};
(async()=>{
 for(const d of [',',';']){
  const file=new Blob([`time${d}"a"\r\n0${d}10\r\n1${d}20\r\n`]);file.name='test.csv';
  await loadStreamingCsv(file);
  assert.deepEqual(loaded,{names:['a'],columns:[[10,20]],time:[0,1]});
 }
 for(const text of ['time\n0\n','time,a\n0,10oops\n','time,a,a\n0,1,2\n','time,a\n0\n']){
  const file=new Blob([text]);file.name='bad.csv';await assert.rejects(()=>loadStreamingCsv(file));
 }
})().catch(error=>{console.error(error);process.exitCode=1;});
"""
    target = tmp_path / 'parser.cjs'
    target.write_text(html[start:end] + harness)
    subprocess.run([node, str(target)], check=True, capture_output=True, text=True, timeout=15)


def test_script_preserves_node_names_with_id_gaps(states, recording, tmp_path):
    state = states()
    state.load_sync(str(recording))
    execute(state, 'node_add(math)', 'node_remove(node_1)', 'node_source(run_1,a)',
            'node_add(math)', 'node_link(node_2,node_3)', 'node_eval()',
            'add_signal(plot_1,node_output_3,out)')
    path = tmp_path / 'gaps.uzscript'
    export_script(state, str(path))
    restored = states()
    run_script(restored, str(path))
    assert [node.name for node in restored.nodes.ordered()] == ['node_2', 'node_3']
    assert restored.registry.get(restored.cells[0].signals[0][0]).label == 'node_3'


def test_bad_session_structure_is_transactional(states, recording):
    state = states()
    original = state.load_sync(str(recording))
    data = to_dict(state)
    data['cells'][0]['signals'] = [['run:1', 'missing']]
    with pytest.raises(ValueError, match='signal reference'):
        apply_dict(state, data)
    assert state.registry.get(original.id) is original
    data['cells'][0]['signals'] = []
    data['grid'] = [0, 1]
    with pytest.raises(ValueError, match='grid dimensions'):
        apply_dict(state, data)
    assert state.registry.get(original.id) is original


def test_lazy_column_requires_explicit_materialization(states, recording):
    state = states()
    run = state.load_sync(str(recording))
    column = run.signals['a'].y
    with pytest.raises(TypeError):
        column + 1
    with pytest.raises(TypeError, match='materialize'):
        column[[1, 3]]
    with pytest.raises(TypeError, match='materialize'):
        column[::-1]
    np.testing.assert_array_equal(column.read_rows(1, 3), [2, 3])
    np.testing.assert_array_equal(column.materialize(), np.arange(1, 9))
    np.testing.assert_array_equal(np.asarray(column), np.arange(1, 9))


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy'])
def test_native_quoted_csv_headers(tmp_path, states, backend, mode):
    path = tmp_path / 'quoted.csv'
    path.write_text('time;"a,b,c";\n0;10;\n1;20;\n')
    run = open_file(str(path), mode, backend=backend).register(states().registry)
    assert list(run.signals) == ['a,b,c']
    np.testing.assert_array_equal(run.read_window(['a,b,c'], 0, 1)[1]['a,b,c'], [10, 20])


@pytest.mark.parametrize('script', [False, True])
def test_roundtrip_preserves_derived_visibility_and_origin(states, recording, tmp_path, script):
    state = states()
    state.load_sync(str(recording))
    execute(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)',
            'node_eval()', 'set_active(node_output_2,false)',
            'normalize_time(node_output_2,100.000123456789)')
    restored = states()
    if script:
        path = tmp_path / 'derived.uzscript'
        export_script(state, str(path))
        run_script(restored, str(path))
    else:
        apply_dict(restored, to_dict(state))
    run = restored.registry.get(restored.nodes.get(2).out_run_id)
    assert not run.active
    assert run.time_origin == 100.000123456789


@pytest.mark.parametrize('script', [False, True])
def test_restored_plot_window_survives_rendering(states, recording, tmp_path, script):
    from imgui_bundle import imgui, implot
    from uz_dataviewer.panels.plots import PlotsPanel
    state = states()
    run = state.load_sync(str(recording))
    state.cells[0].add((run.id, 'a'))
    state.plot_x_ranges[1] = (2., 4.)
    restored = states()
    if script:
        path = tmp_path / 'render.uzscript'
        export_script(state, str(path))
        run_script(restored, str(path))
    else:
        apply_dict(restored, to_dict(state))
    restored.display.synchronous = True
    imgui.create_context()
    implot.create_context()
    try:
        io = imgui.get_io()
        io.set_ini_filename(None)
        io.display_size = imgui.ImVec2(1000, 800)
        io.delta_time = 1 / 60
        io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
        panel = PlotsPanel()
        for _ in range(3):
            imgui.new_frame()
            imgui.set_next_window_size(imgui.ImVec2(1000, 800))
            imgui.begin('Restored plot')
            panel.render(restored)
            imgui.end()
            imgui.render()
        np.testing.assert_allclose(restored.plot_x_ranges[1], (2., 4.))
        assert not restored.display.errors
    finally:
        implot.destroy_context()
        imgui.destroy_context()
