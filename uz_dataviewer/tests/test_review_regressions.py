"""Cross-layer regressions from the current-state review."""
import importlib.util
from pathlib import Path
import threading

import numpy as np
import pytest

from uz_dataviewer import loader
from uz_dataviewer.analysis import compute_fft
from uz_dataviewer.model import DataRegistry
from uz_dataviewer.nodes import evaluate
from uz_dataviewer.panels.fft import FftPanel
from uz_dataviewer.panels.histogram import HistogramPanel
from uz_dataviewer.panels.nodes import NodesPanel
from uz_dataviewer.requests import Requests
from uz_dataviewer.transforms import math_node


@pytest.mark.parametrize('operation', ['div', 'reciprocal'])
def test_undefined_math_stays_invalid_through_analysis(operation):
    t = np.arange(8.)
    y = np.ones(8)
    y[2] = 0
    inputs = [(t, y)] if operation == 'reciprocal' else [(t, np.ones(8)), (t, y)]
    _, result, _ = math_node(inputs, {'op': operation})
    assert np.isnan(result[2])
    np.testing.assert_array_equal(result[np.arange(8) != 2], np.ones(7))
    fft = compute_fft(t, result, 0, 7)
    assert not fft.ok and 'non-finite' in fft.info


@pytest.mark.parametrize('value', ['inf', 'nan', '1e309', '2147483648', '1.5', 'bad'])
def test_invalid_integer_parameter_is_rejected_and_legacy_value_renders(app_state, gui_frame, value):
    state = app_state
    state.commands.execute(state, 'node_add', ['filter'])
    node = state.nodes.get(1)
    before = dict(node.params)
    with pytest.raises(ValueError):
        state.commands.execute(state, 'node_set', [1, 'taps', value])
    assert node.params == before
    # Session data is intentionally preserved for repair; its editor must survive.
    node.params['taps'] = value
    from uz_dataviewer.session import apply_dict, to_dict
    apply_dict(state, to_dict(state))
    node = state.nodes.get(1)
    panel = NodesPanel()
    gui_frame(panel, state)
    gui_frame(panel, state)
    evaluate(state)
    assert node.error


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
def test_actual_csv_budget_checked_before_overallocation(tmp_path, monkeypatch, backend):
    path = tmp_path / 'short.csv'
    path.write_text('time,y\n' + ''.join(f'{i},0\n' for i in range(100)))
    monkeypatch.setattr(loader, 'MAX_CSV_NUMERIC_BYTES', 500)
    assert loader._estimate_csv_rows_and_bytes(str(path), ['time', 'y'])[1] < 500
    allocations = []
    original = loader.np.empty
    def empty(size, *args, **kwargs):
        result = original(size, *args, **kwargs)
        allocations.append(result.nbytes)
        return result
    monkeypatch.setattr(loader.np, 'empty', empty)
    with pytest.raises(ValueError, match='numeric memory budget'):
        loader.parse_file(str(path), backend=backend)
    assert max(allocations) <= 500
    # The lazy path still supports the same file without resident materialization.
    run = loader.open_file(str(path), 'lazy', backend=backend).register(DataRegistry())
    assert run.n_rows == 100


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy', 'converted'])
def test_csv_missing_values_have_one_policy(tmp_path, backend, mode):
    from uz_dataviewer.csv_policy import NULL_VALUES
    import csv
    path = tmp_path / 'missing.csv'
    with path.open('w', newline='') as fh:
        writer = csv.writer(fh)
        writer.writerow(['time', 'y'])
        writer.writerows(enumerate(NULL_VALUES))
    if mode == 'converted':
        path = Path(loader.convert_csv_to_parquet(str(path), backend=backend))
    run = loader.open_file(str(path), 'lazy' if mode == 'lazy' else 'memory', backend=backend).register(DataRegistry())
    t, values = run.read_window(['y'], 0, len(NULL_VALUES))
    assert len(t) == len(NULL_VALUES)
    assert np.isnan(values['y']).all()


def test_browser_generator_embeds_shared_null_policy():
    import json
    from uz_dataviewer.csv_policy import NULL_VALUES
    path = Path(__file__).parents[1] / 'build' / 'gen_web.py'
    spec = importlib.util.spec_from_file_location('review_gen_web', path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    html = module.build_html()
    assert json.dumps(NULL_VALUES) + '.includes(text)' in html


def analysis_setup(state, panel_type):
    state.analysis_jobs.close()
    state.analysis_jobs = Requests(synchronous=True)
    for label in ('a', 'b'):
        state.registry.add_run(label, label, np.arange(64.) / 64,
                               {'y': np.sin(np.arange(64.))}, {})
    panel = panel_type()
    cfg = panel.config(state)
    cfg.sources = [(1, 'y'), (2, 'y')]
    cfg.follow_plot = -1
    cfg.compute_requested = True
    return panel, cfg


@pytest.mark.parametrize('panel_type', [FftPanel, HistogramPanel])
def test_removed_analysis_trace_disappears_while_worker_is_blocked(app_state, gui_frame, panel_type):
    state = app_state
    panel, cfg = analysis_setup(state, panel_type)
    for _ in range(3):
        gui_frame(panel, state)
    assert len(panel._result_refs()) == 2
    state.analysis_jobs.close()
    state.analysis_jobs = Requests()
    started, release = threading.Event(), threading.Event()
    def block(cancel):
        started.set()
        assert release.wait(5)
    state.analysis_jobs.request('block', 1, 1, block)
    assert started.wait(2)
    try:
        state.remove_run(1)
        gui_frame(panel, state)
        assert (1, 'y') not in panel._result_refs()
        assert cfg.sources == [(2, 'y')]
    finally:
        release.set()


@pytest.mark.parametrize('panel_type,prefix', [(FftPanel, 'fft'), (HistogramPanel, 'hist')])
def test_explicit_analysis_zoom_survives_recompute(app_state, gui_frame, monkeypatch, panel_type, prefix):
    from imgui_bundle import implot
    state = app_state
    panel, cfg = analysis_setup(state, panel_type)
    for _ in range(3):
        gui_frame(panel, state)
    state.commands.execute(state, prefix + '_xlim', [2, 5])
    # First consume the zoom in a frame, then complete another computation.
    gui_frame(panel, state)
    assert cfg.pending_x_lim is None
    cfg.compute_requested = True
    applied = []
    original = implot.setup_axis_limits
    def capture(axis, lo, hi, *args):
        applied.append((axis, lo, hi))
        return original(axis, lo, hi, *args)
    monkeypatch.setattr(implot, 'setup_axis_limits', capture)
    gui_frame(panel, state)
    assert (implot.ImAxis_.x1, 2, 5) in applied
    assert cfg.x_lim == (2, 5)


@pytest.mark.parametrize('panel_type,prefix', [(FftPanel, 'fft'), (HistogramPanel, 'hist')])
def test_zoom_issued_during_computation_survives_completion(app_state, gui_frame, monkeypatch, panel_type, prefix):
    import time
    from imgui_bundle import implot
    state = app_state
    panel, cfg = analysis_setup(state, panel_type)
    for _ in range(3):
        gui_frame(panel, state)
    state.analysis_jobs.close()
    state.analysis_jobs = Requests()
    started, release = threading.Event(), threading.Event()
    original_compute = panel_type._compute
    def blocked_compute(self, *args):
        started.set()
        assert release.wait(5)
        return original_compute(self, *args)
    monkeypatch.setattr(panel_type, '_compute', blocked_compute)
    cfg.compute_requested = True
    gui_frame(panel, state)
    assert started.wait(2)
    applied = []
    original_limits = implot.setup_axis_limits
    def capture(axis, lo, hi, *args):
        applied.append((axis, lo, hi))
        return original_limits(axis, lo, hi, *args)
    monkeypatch.setattr(implot, 'setup_axis_limits', capture)
    try:
        state.commands.execute(state, prefix + '_xlim', [2, 5])
        gui_frame(panel, state)
        assert (implot.ImAxis_.x1, 2, 5) in applied
        applied.clear()
    finally:
        release.set()
    deadline = time.monotonic() + 3
    while panel._analysis_pending is not None and time.monotonic() < deadline:
        gui_frame(panel, state)
        time.sleep(.01)
    assert panel._analysis_pending is None
    assert (implot.ImAxis_.x1, 2, 5) in applied
