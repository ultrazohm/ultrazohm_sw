"""XY alignment, coordinate ranges and asynchronous export lifetime."""
import numpy as np
import pytest
from uz_dataviewer import session
from uz_dataviewer.panels.plots import PlotsPanel
from uz_dataviewer.sampling import sample_xy
from uz_dataviewer.sources import ArraySource
from uz_dataviewer.state import PlotType


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


@pytest.mark.parametrize('script', [False, True])
@pytest.mark.parametrize('gesture', [False, True])
def test_xy_ranges_render_and_roundtrip_without_linking_time(app_state, gui_frame, tmp_path, monkeypatch, script, gesture):
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
    if script:
        path = tmp_path/'view.uzscript'
        session.export_script(s, str(path))
        session.run_script(s, str(path))
    else:
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
