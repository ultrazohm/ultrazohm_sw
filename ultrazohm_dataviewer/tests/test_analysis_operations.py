"""Explicit analysis commands complete independently of panel visibility."""
import threading
import time

import numpy as np
import pytest

from ultrazohm_dataviewer import ViewerError
from ultrazohm_dataviewer.analysis import FftRequest, HistogramRequest
from ultrazohm_dataviewer.operations import Operations


@pytest.mark.parametrize('kind,request_type', [('fft', FftRequest), ('histogram', HistogramRequest)])
@pytest.mark.parametrize('edit', [False, True])
def test_analysis_completion_and_changed_inputs(app_state, gui_frame, monkeypatch, kind, request_type, edit):
    t = np.arange(1000) / 1000
    run = app_state.registry.add_run('signal', '', t, {'y': np.sin(t * 20)}, {})
    cfg = app_state.fft if kind == 'fft' else app_state.histogram
    cfg.sources = [(run.id, 'y')]
    cfg.follow_plot = -1
    operations = Operations(app_state)
    entered, release = threading.Event(), threading.Event()
    original = request_type.compute
    def compute(self, cancel=None):
        entered.set()
        assert release.wait(3)
        return original(self, cancel)
    monkeypatch.setattr(request_type, 'compute', compute)
    try:
        future = operations.dispatch(kind, {}, None)
        assert entered.wait(2)
        assert not future.done()
        assert not app_state.services.completed_analysis
        operations.dispatch('set_grid', {'rows': 2, 'cols': 1}, None)
        if edit:
            cfg.sources.clear()
        release.set()
        deadline = time.monotonic() + 3
        while not future.done() and time.monotonic() < deadline:
            operations.poll()
            time.sleep(.001)
        if edit:
            with pytest.raises(ViewerError) as error:
                future.result()
            assert error.value.code == 'inputs_changed'
            assert not app_state.services.completed_analysis
        else:
            assert future.result()['result']
            prefix = 'fft' if kind == 'fft' else 'hist'
            _, result = app_state.services.completed_analysis[prefix]
            assert len(result.series) == 1
            from ultrazohm_dataviewer.panels.fft import FftPanel
            from ultrazohm_dataviewer.panels.histogram import HistogramPanel
            panel = FftPanel() if kind == 'fft' else HistogramPanel()
            gui_frame(panel, app_state)
            assert len(panel._results) == 1
            assert prefix not in app_state.services.completed_analysis
    finally:
        release.set()
        operations.close()
