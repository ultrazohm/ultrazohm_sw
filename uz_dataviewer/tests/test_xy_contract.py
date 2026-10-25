"""XY alignment, coordinate ranges and asynchronous export lifetime."""

from types import SimpleNamespace
import time
import weakref

import numpy as np
import pytest

from uz_dataviewer import session
from uz_dataviewer.panels.plots import PlotsPanel
from uz_dataviewer.sampling import sample_xy
from uz_dataviewer.sources import ArraySource, Metadata, check
from uz_dataviewer.state import AppState, PlotType


@pytest.mark.parametrize('right_time', [np.arange(8.)+100, np.arange(8.)*2, np.arange(7.)])
def test_xy_rejects_unaligned_inputs(right_time):
    left = ArraySource(np.arange(8.), {'x':np.arange(8.)})
    right = ArraySource(right_time, {'y':np.arange(len(right_time))})
    with pytest.raises(ValueError, match='XY needs'):
        sample_xy(left, right, 'x', 'y', 0, 0, 2)


def test_xy_validates_unsampled_timestamps_across_different_batches():
    class Batches(ArraySource):
        def __init__(self, time, size):
            super().__init__(time, {'value':np.arange(len(time))})
            self.size = size
        def iter_raw(self, channels, start=0, stop=None, cancel=None):
            for i in range(0, len(self.time), self.size):
                yield self.read_rows(channels, i, i+self.size, cancel)
    left = Batches(np.arange(17.), 3)
    right = Batches(np.arange(17.)+100, 5)
    x, y = sample_xy(left, right, 'value', 'value', 0, -100, 4)
    np.testing.assert_array_equal(x, np.arange(17.)[::4])
    np.testing.assert_array_equal(x, y)
    right.time[7] += .25  # not selected by display stride
    with pytest.raises(ValueError, match='not time-aligned'):
        sample_xy(left, right, 'value', 'value', 0, -100, 4)


@pytest.mark.parametrize('gesture', [False, True])
def test_xy_ranges_render_and_roundtrip_without_linking_time(app_state, gui_frame, tmp_path, monkeypatch, gesture):
    from imgui_bundle import implot
    s = app_state
    s.backend, s.loading_mode = 'pyarrow', 'memory'
    path = tmp_path/'xy.csv'
    path.write_text('time;x;y\n'+''.join(f'{i};{i};{i*2}\n' for i in range(8)))
    s.load_sync(str(path))
    s.set_grid(1, 2)
    s.commands.execute(s, 'set_xy', [2, 1, 'x'])
    s.commands.execute(s, 'add_signal', [2, 1, 'y'])
    s.shared_x = (100, 200)
    panel = PlotsPanel()
    for _ in range(3): gui_frame(panel, s)
    if gesture:
        setup = implot.setup_axes
        def zoom(*args):
            setup(*args)
            if args[0] != 'time':
                implot.setup_axis_limits(implot.ImAxis_.x1, 2., 4., implot.Cond_.always)
                implot.setup_axis_limits(implot.ImAxis_.y1, 5., 7., implot.Cond_.always)
        with monkeypatch.context() as patch:
            patch.setattr(implot, 'setup_axes', zoom)
            for _ in range(3): gui_frame(panel, s)
    else:
        s.commands.execute(s, 'set_x_lim', [2, 2., 4.])
        s.commands.execute(s, 'set_y_lim', [2, 5., 7.])
        for _ in range(3): gui_frame(panel, s)
    cell = s.cells[1]
    assert cell.pending_x_lim is None and cell.pending_y_lim is None
    assert cell.x_lim == (2., 4.) and cell.y_lim == (5., 7.)
    assert s.shared_x == (100, 200) and 2 not in s.plot_x_ranges
    session.apply_dict(s, session.to_dict(s))
    for _ in range(4): gui_frame(panel, s)
    assert s.cells[1].x_lim == (2., 4.) and s.cells[1].y_lim == (5., 7.)
    assert 2 not in s.plot_x_ranges


def test_export_dialog_cancels_when_original_cell_is_gone(app_state, tmp_path):
    class Dialog:
        def ready(self): return True
        def result(self): return str(tmp_path/'export.csv')
    s = app_state
    s.set_grid(2, 2)
    panel = PlotsPanel()
    panel._export_dialog = (Dialog(), s.cells[3])
    s.set_grid(1, 1)
    s.set_grid(2, 2)  # same index must not select a different cell
    panel._poll_export(s)
    assert panel._export_dialog is None
    assert not (tmp_path/'export.csv').exists()
    assert any('subplot was removed' in e.message for e in s.console._entries)


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
