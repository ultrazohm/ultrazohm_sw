"""Round-trip tests for JSON session save/restore."""

from __future__ import annotations

import json

import numpy as np
import pytest



from uz_dataviewer import session
from uz_dataviewer.commands import CommandError
from uz_dataviewer.session import apply_dict, to_dict
from uz_dataviewer.state import AppState, PlotType
from uz_dataviewer.panels.plots import PlotsPanel


SAMPLE = (
    "time;CH8=8)ia;CH9=9)ib;\n"
    "0.0;0.1;1.0;\n"
    "0.1;0.2;1.1;\n"
    "0.2;0.3;1.2;\n"
)


def test_ensure_extension():
    assert session.ensure_extension("session", ".json") == "session.json"
    assert session.ensure_extension("session.json", ".json") == "session.json"
    assert session.ensure_extension("SESSION.JSON", ".json") == "SESSION.JSON"  # case-insensitive
    assert session.ensure_extension("a/b/plot_1", ".csv") == "a/b/plot_1.csv"
    assert session.ensure_extension("", ".json") == ""  # no path -> unchanged


@pytest.mark.parametrize('consumed', [False, True])
def test_analysis_view_limits_survive_json_roundtrip(app_state, tmp_path, consumed,
                                                    gui_frame, monkeypatch, recording_csv):
    from imgui_bundle import implot
    from uz_dataviewer.panels.fft import FftPanel
    from uz_dataviewer.panels.histogram import HistogramPanel
    run = app_state.load_sync(str(recording_csv))
    for prefix in ('fft', 'hist'):
        app_state.commands.execute(app_state, f'{prefix}_source', [run.id, 'a'])
        app_state.commands.execute(app_state, f'{prefix}_xlim', [10, 20])
    if consumed:
        app_state.fft.pending_x_lim = app_state.histogram.pending_x_lim = None
    path = tmp_path / 'session.json'
    session.save_state(app_state, str(path))
    session.load_state(app_state, str(path))
    app_state.services.analysis_jobs.synchronous = True
    for cfg, panel in ((app_state.fft, FftPanel()), (app_state.histogram, HistogramPanel())):
        assert cfg.x_lim == cfg.pending_x_lim == (10., 20.)
        drawn_limits = []

        def capture(state):
            limits = implot.get_plot_limits()
            drawn_limits.append((limits.x.min, limits.x.max))

        monkeypatch.setattr(panel, '_draw', capture)
        for _ in range(3):
            gui_frame(panel, app_state)
        assert drawn_limits and all(limits == (10., 20.) for limits in drawn_limits)
        assert cfg.pending_x_lim is None and cfg.x_lim == (10., 20.)


@pytest.mark.parametrize('config', ['fft', 'histogram'])
@pytest.mark.parametrize('limits', [[2, 1], [1, 1], [0, float('nan')], [0, float('inf')]])
def test_invalid_analysis_view_limits_leave_session_intact(app_state, config, limits):
    token = app_state.session_token
    saved = to_dict(app_state)
    saved[config]['x_lim'] = limits
    with pytest.raises(ValueError):
        apply_dict(app_state, saved)
    assert app_state.session_token is token


def _populated_state(csv_path):
    state = AppState()
    state.commands.dispatch(state, f'load({json.dumps(str(csv_path))})')
    state.commands.dispatch(state, "set_grid(2, 1)")
    state.commands.dispatch(state, "add_signal(plot_1, Log_test.csv, ia)")
    state.commands.dispatch(state, "set_plot_type(plot_2, Scatter)")
    state.commands.dispatch(state, "add_signal(plot_2, Log_test.csv, ib)")
    state.commands.dispatch(state, "show_samples(plot_1, on)")
    state.commands.dispatch(state, "set_max_points(750)")
    return state


def test_export_relative_flag(tmp_path):
    """'start at 0' must rebase only when on; toggling on then off keeps real time."""
    import pandas as pd

    csv = tmp_path / "Log_export.csv"
    csv.write_text("time;CH8=8)ia;\n100.0;1.0;\n100.1;2.0;\n100.2;3.0;\n")
    state = AppState()
    state.commands.dispatch(state, f'load({json.dumps(str(csv))})')
    state.commands.dispatch(state, "add_signal(plot_1, Log_export.csv, ia)")
    out = tmp_path / "out.csv"

    # relative off -> keeps the real start time
    state.commands.dispatch(state, f'export_data(plot_1, {json.dumps(str(out))}, false)')
    assert float(pd.read_csv(out)["time"].iloc[0]) == 100.0

    # toggling the flag on then off must NOT leave the export rebased
    state.commands.dispatch(state, "set_export_relative(plot_1, on)")
    state.commands.dispatch(state, "set_export_relative(plot_1, off)")
    assert state.cells[0].export_relative is False
    state.commands.dispatch(state, f'export_data(plot_1, {json.dumps(str(out))}, false)')
    assert float(pd.read_csv(out)["time"].iloc[0]) == 100.0

    # relative on -> rebased to 0
    state.commands.dispatch(state, f'export_data(plot_1, {json.dumps(str(out))}, true)')
    assert float(pd.read_csv(out)["time"].iloc[0]) == 0.0


def test_json_roundtrip(tmp_path):
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = _populated_state(str(csv))

    out = tmp_path / "session.json"
    session.save_state(state, str(out))

    restored = AppState()
    session.load_state(restored, str(out))

    assert (restored.rows, restored.cols) == (2, 1)
    assert restored.max_points == 750
    assert restored.cells[0].plot_type is PlotType.LINE
    assert restored.cells[0].show_samples is True
    assert restored.cells[1].plot_type is PlotType.SCATTER
    # Signals resolve back to the reloaded run by label.
    assert [r[1] for r in restored.cells[0].signals] == ["ia"]
    assert [r[1] for r in restored.cells[1].signals] == ["ib"]


def test_xy_style_roundtrip(tmp_path):
    from uz_dataviewer.state import XyStyle

    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = AppState()
    state.commands.dispatch(state, f'load({json.dumps(str(csv))})')
    state.commands.dispatch(state, "set_xy(plot_1, Log_test.csv, ia)")
    state.commands.dispatch(state, "add_signal(plot_1, Log_test.csv, ib)")
    state.commands.dispatch(state, "set_xy_style(plot_1, both)")

    # JSON round-trip.
    out = tmp_path / "session.json"
    session.save_state(state, str(out))
    restored = AppState()
    session.load_state(restored, str(out))
    assert restored.cells[0].plot_type is PlotType.XY
    assert restored.cells[0].xy_style is XyStyle.BOTH

def test_json_restore_flags_analysis_recompute(tmp_path):
    """Restoring a session with FFT/Histogram sources must request a recompute,
    so the windows draw their results without a manual Compute click."""
    csv = tmp_path / "Log_test.csv"
    csv.write_text(SAMPLE)
    state = _populated_state(str(csv))
    state.commands.dispatch(state, "fft_source(Log_test.csv, ia)")
    state.commands.dispatch(state, "hist_source(Log_test.csv, ib)")

    out = tmp_path / "session.json"
    session.save_state(state, str(out))

    restored = AppState()
    assert restored.fft.compute_requested is False  # fresh state
    session.load_state(restored, str(out))
    assert [r[1] for r in restored.fft.sources] == ["ia"]
    assert [r[1] for r in restored.histogram.sources] == ["ib"]
    assert restored.fft.compute_requested is True
    assert restored.histogram.compute_requested is True

    # No analysis sources -> no recompute requested.
    plain = _populated_state(str(csv))
    plain_out = tmp_path / "plain.json"
    session.save_state(plain, str(plain_out))
    restored_plain = AppState()
    session.load_state(restored_plain, str(plain_out))
    assert restored_plain.fft.compute_requested is False


def test_clear_and_replace_share_lifecycle(app_state):
    from uz_dataviewer.session import clear_session, to_dict, apply_dict
    from uz_dataviewer.panels.plots import PlotsPanel
    from uz_dataviewer.panels.navigation import NavigationPanel
    state = app_state
    commands, console, token = state.commands, state.console, state.session_token
    plots, navigation = PlotsPanel(), NavigationPanel()
    for panel in (plots, navigation):
        panel._sync_session(state)
    plots._last_logged_x[0] = (3., 5.)
    navigation._norm_target[1] = 42.
    state.dragged_ref = (1, 'a')
    state.registry.cache.limit = 123 * 1024**2
    clear_session(state)
    assert state.session_token is not token and state.dragged_ref is None
    assert state.registry.cache.limit == 123 * 1024**2
    assert state.commands is commands and state.console is console
    for panel in (plots, navigation):
        assert panel._sync_session(state)
    assert not plots._last_logged_x and not navigation._norm_target
    token = state.session_token
    apply_dict(state, to_dict(state))
    assert state.session_token is not token
    assert state.commands is commands and state.console is console


@pytest.mark.parametrize('gesture', [False, True])
def test_rendered_y_limits_survive_round_trip(app_state, gui_frame, tmp_path, monkeypatch, gesture):
    from imgui_bundle import implot
    from uz_dataviewer.panels.plots import PlotsPanel
    state = app_state
    state.backend, state.loading_mode = 'pyarrow', 'memory'
    path = tmp_path / 'limits.csv'
    path.write_text('time;a\n' + ''.join(f'{i};{i+10}\n' for i in range(8)))
    state.load_sync(str(path))
    state.cells[0].signals = [(1, 'a')]
    panel = PlotsPanel()
    for _ in range(3):
        gui_frame(panel, state)
    if gesture:
        # Change the actual plot viewport without issuing a command, like a mouse zoom.
        setup = implot.setup_axes
        def zoom(*args):
            setup(*args)
            implot.setup_axis_limits(implot.ImAxis_.y1, 12., 14., implot.Cond_.always)
        with monkeypatch.context() as patch:
            patch.setattr(implot, 'setup_axes', zoom)
            for _ in range(3):
                gui_frame(panel, state)
    else:
        state.commands.execute(state, 'set_y_lim', [1, 12., 14.])
        for _ in range(3):
            gui_frame(panel, state)
    assert state.cells[0].pending_y_lim is None
    assert state.cells[0].y_lim == (12., 14.)
    saved = session.to_dict(state)
    assert saved['cells'][0]['y_lim'] == (12., 14.)
    session.apply_dict(state, saved)
    for _ in range(3):
        gui_frame(panel, state)
    assert state.cells[0].y_lim == (12., 14.)
    state.commands.execute(state, 'reset_view', [1])
    for _ in range(3):
        gui_frame(panel, state)
    assert state.cells[0].y_lim == (10., 17.)


def test_restore_rejects_nonexistent_analysis_plot_transactionally(app_state):
    state = app_state
    token = state.session_token
    saved = session.to_dict(state)
    saved['fft']['follow_plot'] = 2
    with pytest.raises(ValueError, match='FFT follow plot'):
        session.apply_dict(state, saved)
    assert state.session_token is token


def test_json_preserves_hidden_view_and_analysis_settings(app_state, tmp_path):
    """Inactive controls survive restoration, including a former XY source."""
    import json
    state = app_state
    state.backend, state.loading_mode = 'pyarrow', 'memory'
    path = tmp_path/'data.csv'
    path.write_text(SAMPLE)
    state.load_sync(str(path))
    state.commands.execute(state, 'set_xy', [1, 1, 'ia'])
    state.commands.execute(state, 'add_signal', [1, 1, 'ib'])
    state.commands.execute(state, 'set_plot_type', [1, 'Line'])
    state.link_x = False
    cell = state.cells[0]
    cell.pending_x_lim, cell.pending_y_lim = (.05, .15), (1.05, 1.15)
    cell.spy_rect, cell.cursor_x = (.06, 1.06, .14, 1.14), (.07, .13)
    cell.spy = cell.cursors = False
    state.fft.follow_plot, state.histogram.follow_plot = -1, -1
    state.fft.x_min, state.fft.x_max = .01, .19
    state.histogram.x_min, state.histogram.x_max = .02, .18
    state.fft.remove_dc, state.fft.window, state.fft.log_y = False, False, True
    state.histogram.bins = 17
    saved = session.to_dict(state)
    session.apply_dict(state, saved)
    assert json.loads(json.dumps(session.to_dict(state))) == json.loads(json.dumps(saved))


@pytest.mark.parametrize('failure', ['disconnected', 'invalid_parameter', 'missing_plugin'])
def test_failed_graph_restores_assignments_and_recovers(app_state, tmp_path, monkeypatch, gui_frame, failure):
    import numpy as np
    from uz_dataviewer import nodes
    from uz_dataviewer.panels.plots import PlotsPanel
    from uz_dataviewer.panels.fft import FftPanel
    from uz_dataviewer.panels.histogram import HistogramPanel

    state = app_state
    state.backend, state.loading_mode = 'pyarrow', 'memory'
    path = tmp_path / 'graph.csv'
    path.write_text('time;a\n' + ''.join(f'{i};{i+1}\n' for i in range(8)))
    state.load_sync(str(path))
    source = state.nodes.add('source', ref=(1, 'a'))
    transform = state.nodes.add('math')
    downstream = state.nodes.add('math')
    state.nodes.link(source.id, transform.id)
    state.nodes.link(transform.id, downstream.id)
    assert nodes.evaluate(state) == 2
    output = state.registry.get(downstream.out_run_id)
    output.set_time_origin(100.)
    ref = (output.id, 'out')
    state.cells[0].add(ref)
    state.cells[0].set_secondary(ref, True)
    state.cells[0].xy_source = ref
    state.fft.sources = state.histogram.sources = [ref]
    state.fft.follow_plot = state.histogram.follow_plot = -1
    spec = nodes.REGISTRY['math']
    if failure == 'disconnected':
        state.nodes.unlink(source.id, transform.id)
    elif failure == 'invalid_parameter':
        transform.params['k'] = 'bad'
    else:
        monkeypatch.delitem(nodes.REGISTRY, 'math')

    saved = tmp_path / 'graph.json'
    session.save_state(state, str(saved))
    session.load_state(state, str(saved))
    # A second save/restore must preserve unavailable outputs too.
    session.apply_dict(state, session.to_dict(state))
    node = state.nodes.get(downstream.id)
    output = state.registry.get(node.out_run_id)
    ref = (output.id, 'out')
    assert output.n_rows == 0 and output.time_origin == 100.
    assert state.cells[0].signals == state.cells[0].y2_signals == [ref]
    assert state.cells[0].xy_source == ref
    assert state.fft.sources == state.histogram.sources == [ref]
    with pytest.raises(ValueError, match='derived output is not current'):
        output.read_window(['out'], 0, 200)
    for exporter in (lambda path: session.export_data(state, 0, path),
                     lambda path: session.export_fft(state, path),
                     lambda path: session.export_histogram(state, path)):
        destination = tmp_path / 'existing.csv'
        destination.write_text('original')
        with pytest.raises(ValueError, match='derived output is not current'):
            exporter(str(destination))
        assert destination.read_text() == 'original'
    for panel in (PlotsPanel(), FftPanel(), HistogramPanel()):
        gui_frame(panel, state)

    if failure == 'disconnected':
        state.nodes.link(source.id, transform.id)
    elif failure == 'invalid_parameter':
        state.nodes.get(transform.id).params['k'] = '2'
    else:
        monkeypatch.setitem(nodes.REGISTRY, 'math', spec)
    assert nodes.evaluate(state) == 2
    assert state.nodes.get(downstream.id).out_run_id == output.id
    assert state.cells[0].signals == state.fft.sources == [ref]
    t, ys = output.read_window(['out'], 100, 107)
    np.testing.assert_array_equal(t, np.arange(100, 108))
    np.testing.assert_array_equal(ys['out'], np.arange(1, 9) * (2 if failure == 'invalid_parameter' else 1))
    output.data_source().validate()


def test_linked_range_survives_json_and_render(app_state, tmp_path, gui_frame):
    from uz_dataviewer.panels.plots import PlotsPanel
    state = app_state
    state.backend, state.loading_mode = 'pyarrow', 'memory'
    path = tmp_path / 'linked.csv'
    path.write_text('time;a\n' + ''.join(f'{i};{i}\n' for i in range(8)))
    state.load_sync(str(path))
    state.set_grid(1, 2)
    for cell in state.cells:
        cell.add((1, 'a'))
    state.commands.execute(state, 'set_x_lim', [2, 0., 1.])
    state.commands.execute(state, 'set_x_lim', [1, 2., 4.])
    session.apply_dict(state, session.to_dict(state))
    assert state.shared_x == (2., 4.)
    panel = PlotsPanel()
    for _ in range(3):
        gui_frame(panel, state)
    assert state.shared_x == (2., 4.)
    assert all(cell.x_lim == (2., 4.) for cell in state.cells)


@pytest.mark.parametrize('axis', ['x', 'y'])
@pytest.mark.parametrize('limits', [(5, 2), (1, 1), (float('nan'), 2), (0, float('inf'))])
def test_invalid_snapshot_limits_leave_current_state_intact(app_state, axis, limits):
    token = app_state.session_token
    data = session.to_dict(app_state)
    data['cells'][0][f'{axis}_lim'] = limits
    with pytest.raises(ValueError):
        session.apply_dict(app_state, data)
    assert app_state.session_token is token


def test_invalid_secondary_assignment_rejected(app_state, tmp_path):
    path = tmp_path / 'data.csv'
    path.write_text(SAMPLE)
    app_state.load_sync(str(path))
    saved = session.to_dict(app_state)
    saved['cells'][0]['y2'] = [['run:1', 'ia']]
    token = app_state.session_token
    with pytest.raises(ValueError, match='not assigned'):
        session.apply_dict(app_state, saved)
    assert app_state.session_token is token


def test_session_partial_evaluation_uses_node_identity(states, recording_csv, tmp_path, execute_commands):
    state = states()
    state.load_sync(str(recording_csv))
    execute_commands(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)',
            'node_set(node_2,k,2)', 'node_add(math)', 'node_link(node_1,node_3)',
            'node_set(node_3,k,3)', 'node_eval(node_3)', 'add_signal(plot_1,run_2,out)')
    restored = states()
    apply_dict(restored, to_dict(state))
    ref = restored.cells[0].signals[0]
    assert restored.registry.get(ref[0]).label == 'node_3'
    assert restored.registry.get_signal(*ref).y[0] == 3


def test_failed_restore_preserves_current_session(states, recording_csv, tmp_path):
    state = states()
    run = state.load_sync(str(recording_csv))
    state.cells[0].add((run.id, 'a'))
    data = to_dict(state)
    data['runs'][0]['path'] = str(tmp_path / 'missing.csv')
    restore = lambda: apply_dict(state, data)
    with pytest.raises((ValueError, CommandError)):
        restore()
    assert state.registry.get(run.id) is run and state.cells[0].signals == [(run.id, 'a')]
    np.testing.assert_array_equal(run.read_window(['a'], 0, 7)[1]['a'], np.arange(1, 9))


def test_roundtrip_preserves_windows_precision_and_active(states, recording_csv, tmp_path):
    state = states()
    run = state.load_sync(str(recording_csv))
    run.active = False
    state.cells[0].add((run.id, 'a'))
    state.plot_x_ranges[1] = (2.0, 4.0)
    state.fft.sources = [(run.id, 'a')]
    state.histogram.sources = [(run.id, 'a')]
    state.histogram.follow_plot = 0
    state.histogram.x_min, state.histogram.x_max = (100.0001, 100.0002)
    restored = states()
    apply_dict(restored, to_dict(state))
    assert not restored.registry.get(1).active
    assert restored.resolve_x_window(1, (0, 0), restored.fft.sources) == (2.0, 4.0)
    assert (restored.histogram.x_min, restored.histogram.x_max) == (100.0001, 100.0002)
    assert restored.cells[0].pending_x_lim == (2.0, 4.0)


def test_session_preserves_node_names_with_id_gaps(states, recording_csv, tmp_path, execute_commands):
    state = states()
    state.load_sync(str(recording_csv))
    execute_commands(state, 'node_add(math)', 'node_remove(node_1)', 'node_source(run_1,a)',
            'node_add(math)', 'node_link(node_2,node_3)', 'node_eval()',
            'add_signal(plot_1,node_output_3,out)')
    restored = states()
    apply_dict(restored, to_dict(state))
    assert [node.name for node in restored.nodes.ordered()] == ['node_2', 'node_3']
    assert restored.registry.get(restored.cells[0].signals[0][0]).label == 'node_3'


def test_bad_session_structure_is_transactional(states, recording_csv):
    state = states()
    original = state.load_sync(str(recording_csv))
    data = to_dict(state)
    data['cells'][0]['signals'] = [['run:1', 'missing']]
    with pytest.raises(ValueError, match='signal reference'):
        apply_dict(state, data)
    assert state.registry.get(original.id) is original
    data['cells'][0]['signals'] = []
    data['grid'] = [0, 1]
    with pytest.raises(ValueError, match='Grid rows'):
        apply_dict(state, data)
    assert state.registry.get(original.id) is original


def test_roundtrip_preserves_derived_visibility_and_origin(states, recording_csv, tmp_path, execute_commands):
    state = states()
    state.load_sync(str(recording_csv))
    execute_commands(state, 'node_source(run_1,a)', 'node_add(math)', 'node_link(node_1,node_2)',
            'node_eval()', 'set_active(node_output_2,false)',
            'normalize_time(node_output_2,100.000123456789)')
    restored = states()
    apply_dict(restored, to_dict(state))
    run = restored.registry.get(restored.nodes.get(2).out_run_id)
    assert not run.active
    assert run.time_origin == 100.000123456789


def test_restored_plot_window_survives_rendering(states, recording_csv, tmp_path):
    from imgui_bundle import imgui, implot
    from uz_dataviewer.panels.plots import PlotsPanel
    state = states()
    run = state.load_sync(str(recording_csv))
    state.cells[0].add((run.id, 'a'))
    state.plot_x_ranges[1] = (2., 4.)
    restored = states()
    apply_dict(restored, to_dict(state))
    restored.services.display.synchronous = True
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
        assert not restored.services.display.errors
    finally:
        implot.destroy_context()
        imgui.destroy_context()


def test_sessions_preserve_duplicate_names_and_instances(tmp_path):
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


def test_json_session_can_be_opened_at_startup(app_state, tmp_path, monkeypatch):
    from uz_dataviewer import plugins, webbridge
    from uz_dataviewer.app import DataViewerApp
    app_state.set_grid(2, 1)
    path = tmp_path / 'startup.json'
    session.save_state(app_state, str(path))
    monkeypatch.setattr(plugins, 'load_plugins', lambda **kwargs: None)
    app = DataViewerApp(initial_files=[str(path)])
    try:
        assert (app.state.rows, app.state.cols) == (2, 1)
        assert not app.state.is_loading
    finally:
        app.state.shutdown()
        webbridge.register_state(None)


@pytest.mark.parametrize('field,value', [
    ('cursor_x', [1]), ('cursor_x', [0, float('nan')]),
    ('spy_rect', [0, 1]), ('spy_rect', [2, 0, 1, 1]),
    ('type', 'obsolete'), ('xy_style', 'obsolete'), ('cursors', 'false'),
])
def test_bad_session_view_preserves_current_session(app_state, gui_frame, field, value):
    data = to_dict(app_state)
    data['cells'][0][field] = value
    token, cell = app_state.session_token, app_state.cells[0]
    with pytest.raises(ValueError):
        apply_dict(app_state, data)
    assert app_state.session_token is token
    assert app_state.cells[0] is cell
    gui_frame(PlotsPanel(), app_state)


@pytest.mark.parametrize('field,value', [
    ('max_points', 2147483648), ('grid', [1.5, 1]),
    ('shared_x', [0, float('inf')]), ('link_x', 'false'),
])
def test_invalid_session_settings_are_transactional(app_state, field, value):
    data = to_dict(app_state)
    data[field] = value
    token = app_state.session_token
    with pytest.raises(ValueError):
        apply_dict(app_state, data)
    assert app_state.session_token is token


def test_session_transfer_preserves_service_ownership(app_state):
    import threading
    state = app_state
    replacement = AppState()
    old_services = state.services
    started = threading.Event()
    def wait_for_cancellation(cancel):
        started.set()
        assert cancel.wait(5)
    old_services.analysis_jobs.request('pending', 1, 1, wait_for_cancellation)
    assert started.wait(2)
    commands, console = state.commands, state.console
    state.application_marker = object()
    marker = state.application_marker
    new_services, cache = replacement.services, replacement.registry.cache
    cache.put('test', np.ones(4), 32)
    try:
        state.replace_session(replacement)
        assert old_services.analysis_jobs.closed
        assert not old_services.analysis_jobs.thread.is_alive()
        assert state.services is new_services
        assert state.commands is commands and state.console is console
        assert state.application_marker is marker
        replacement.shutdown()  # consumed state no longer owns these resources
        assert not new_services.analysis_jobs.closed
        assert cache.get('test') is not None
        with pytest.raises(ValueError, match='live, distinct'):
            state.replace_session(replacement)
    finally:
        replacement.shutdown()


@pytest.mark.parametrize('mode', ['memory', 'lazy'])
def test_secondary_axis_zoom_survives_restore_and_delayed_fit(app_state, gui_frame, tmp_path, monkeypatch, mode):
    import threading
    import time
    from imgui_bundle import implot
    state = app_state
    state.backend, state.loading_mode = 'pyarrow', mode
    path = tmp_path / 'axes.csv'
    path.write_text('time;a;b\n' + ''.join(f'{i};{i+10};{i+100}\n' for i in range(8)))
    run = state.load_sync(str(path))
    cell = state.cells[0]
    cell.signals = [(run.id, 'a'), (run.id, 'b')]
    cell.set_secondary((run.id, 'b'), True)
    panel = PlotsPanel()
    deadline = time.monotonic() + 5
    while time.monotonic() < deadline:
        gui_frame(panel, state)
        if cell.y2_lim == (100., 107.) and not panel._pending_fit:
            break
        time.sleep(.005)
    assert cell.y2_lim == (100., 107.)
    # Set the real ImPlot viewport after the secondary axis has been declared.
    setup = implot.setup_axis
    def zoom(axis, *args):
        setup(axis, *args)
        if axis == implot.ImAxis_.y2:
            implot.setup_axis_limits(axis, 102., 104., implot.Cond_.always)
    with monkeypatch.context() as patch:
        patch.setattr(implot, 'setup_axis', zoom)
        for _ in range(3):
            gui_frame(panel, state)
    assert cell.y2_lim == (102., 104.)
    saved = session.to_dict(state)
    assert saved['cells'][0]['y2_lim'] == (102., 104.)
    # Exercise restoring the right zoom while the left axis still needs fitting.
    saved['cells'][0]['y_lim'] = None
    session.apply_dict(state, saved)
    cell = state.cells[0]
    started, release = threading.Event(), threading.Event()
    def block(cancel):
        started.set()
        assert release.wait(5)
    state.services.display.request('block', 1, 1, block)
    assert started.wait(2)
    try:
        gui_frame(panel, state)
        assert cell.pending_y2_lim is None
        assert cell.y2_lim == (102., 104.)
        if mode == 'lazy':
            assert panel._pending_fit[id(cell)] == {'y'}
    finally:
        release.set()
    deadline = time.monotonic() + 5
    while time.monotonic() < deadline:
        gui_frame(panel, state)
        if not panel._pending_fit and not state.services.display.pending:
            break
        time.sleep(.005)
    assert not panel._pending_fit
    assert cell.y_lim == (10., 17.)
    assert cell.y2_lim == (102., 104.)
    state.reset_plot_view(1)
    deadline = time.monotonic() + 5
    while time.monotonic() < deadline:
        gui_frame(panel, state)
        if not panel._pending_fit:
            break
        time.sleep(.005)
    assert cell.y2_lim == (100., 107.)


@pytest.mark.parametrize('limits', [[1], [3, 2], [0, float('inf')]])
def test_invalid_secondary_axis_limits_preserve_session(app_state, limits):
    saved = session.to_dict(app_state)
    saved['cells'][0]['y2_lim'] = limits
    token = app_state.session_token
    with pytest.raises((ValueError, TypeError)):
        session.apply_dict(app_state, saved)
    assert app_state.session_token is token

@pytest.mark.parametrize('failure', ['serialization', 'write', 'replace'])
def test_failed_save_preserves_previous_snapshot(app_state, tmp_path, monkeypatch, failure):
    import uz_dataviewer.session as session
    path = tmp_path / 'session.json'
    session.save_state(app_state, path)
    original = path.read_bytes()

    def fail_write(data, fh, **kwargs):
        fh.write('{"version": ')
        raise OSError('write failed')

    def fail_replace(*args):
        raise OSError('replace failed')

    if failure == 'serialization':
        node = app_state.nodes.add('math')
        node.params['unserializable'] = object()
    elif failure == 'write':
        monkeypatch.setattr(session.json, 'dump', fail_write)
    else:
        monkeypatch.setattr(session.os, 'replace', fail_replace)
    with pytest.raises((TypeError, OSError)):
        session.save_state(app_state, path)
    assert path.read_bytes() == original
    assert sorted(p.name for p in tmp_path.iterdir()) == ['session.json']


def test_successful_save_replaces_snapshot(app_state, tmp_path):
    import json
    from uz_dataviewer.session import save_state
    path = tmp_path / 'session.json'
    save_state(app_state, path)
    app_state.set_grid(2, 2)
    save_state(app_state, path)
    assert json.loads(path.read_text())['grid'] == [2, 2]
    assert sorted(p.name for p in tmp_path.iterdir()) == ['session.json']


@pytest.mark.parametrize('normalized', [False, True])
def test_stale_domain_transition_roundtrip_clears_incompatible_consumers(app_state, recording_csv, normalized):
    from uz_dataviewer import nodes
    s = app_state
    run = s.load_sync(str(recording_csv))
    src = s.nodes.add('source', ref=(run.id, 'a'))
    fft, math = s.nodes.add('fft'), s.nodes.add('math')
    s.nodes.link(src.id, fft.id)
    s.nodes.link(src.id, math.id)
    nodes.evaluate(s)
    output = s.registry.get(math.out_run_id)
    if normalized:
        output.set_time_origin(100)
    s.cells[0].signals = [(run.id, 'a'), (output.id, 'out')]
    s.cells[0].xy_source = (output.id, 'out')
    s.fft.sources = s.histogram.sources = [(output.id, 'out')]
    s.nodes.unlink(src.id, math.id)
    s.nodes.link(fft.id, math.id)
    apply_dict(s, to_dict(s))
    output = s.registry.get(s.nodes.get(math.id).out_run_id)
    assert output.axis_domain == 'frequency' and output.time_origin is None
    assert s.cells[0].signals == [(1, 'a')] and s.cells[0].xy_source is None
    assert not s.fft.sources and not s.histogram.sources
    apply_dict(s, to_dict(s))
    assert s.registry.get(s.nodes.get(math.id).out_run_id).axis_domain == 'frequency'


def test_csv_export_preserves_existing_file_on_failure(
    app_state, tmp_path, monkeypatch
):
    s = app_state
    s.backend = "pyarrow"
    s.registry.add_run("a", "a", np.arange(8.0), {"a": np.ones(8)}, {})
    s.cells[0].add((1, "a"))
    path = tmp_path / "previous.csv"
    path.write_text("previous successful export")
    import pandas as pd

    def fail(self, path, **kw):
        with open(path, "w") as f:
            f.write("time,a\n")
        raise OSError("disk full")

    monkeypatch.setattr(pd.DataFrame, "to_csv", fail)
    with pytest.raises(OSError):
        session.export_data(s, 0, str(path))
    assert path.read_text() == "previous successful export"
    assert sorted(p.name for p in tmp_path.iterdir()) == ["previous.csv"]


def test_failed_mixed_domain_graph_preserves_saved_placeholder(app_state, recording_csv):
    from uz_dataviewer import nodes
    s = app_state
    run = s.load_sync(str(recording_csv))
    source = s.nodes.add('source', ref=(run.id, 'a'))
    fft, math = s.nodes.add('fft'), s.nodes.add('math')
    s.nodes.link(source.id, fft.id)
    s.nodes.link(source.id, math.id)
    nodes.evaluate(s)
    output = s.registry.get(math.out_run_id)
    output.set_time_origin(10)
    s.cells[0].add((output.id, 'out'))
    math.params['op'] = 'add'
    s.nodes.link(fft.id, math.id, 1)
    apply_dict(s, to_dict(s))
    output = s.registry.get(s.nodes.get(math.id).out_run_id)
    assert output.axis_domain == 'time' and output.time_origin == 10
    assert output.n_rows == 0 and s.cells[0].signals == [(output.id, 'out')]
    with pytest.raises(ValueError, match='not current'):
        output.data_source().validate()


def test_old_session_without_domain_contract_is_rejected_atomically(app_state):
    data = to_dict(app_state)
    data['version'] = 4
    token = app_state.session_token
    with pytest.raises(ValueError, match='Unsupported session version'):
        apply_dict(app_state, data)
    assert app_state.session_token is token
