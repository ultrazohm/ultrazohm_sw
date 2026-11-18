"""Exercise bundled native modules and lazy Parquet reads without a display."""
import json
from pathlib import Path
from tempfile import TemporaryDirectory

import numpy as np
import pyarrow as pa
import pyarrow.parquet as pq
from imgui_bundle import imgui, implot

from uz_dataviewer.loader import open_file, convert_csv_to_parquet
from uz_dataviewer.model import DataRegistry


def check_plot_input():
    """Exercise packaged ImPlot mouse input on both platforms without a GPU."""
    from uz_dataviewer.panels.plots import PlotsPanel
    from uz_dataviewer.state import AppState
    io = imgui.get_io()
    io.set_ini_filename(None)
    io.display_size = imgui.ImVec2(1200, 1000)
    io.delta_time = 1 / 60
    io.backend_flags |= imgui.BackendFlags_.renderer_has_textures
    state = AppState()
    state.services.display.synchronous = True
    state.set_grid(2, 1)
    t = np.linspace(0., 10., 1000)
    run = state.registry.add_run('smoke', '', t, {'signal': np.sin(t)}, {})
    for cell in state.cells:
        cell.add((run.id, 'signal'))
    state.set_plot_x_limits(1, 0., 10.)
    geometry = {}
    class Panel(PlotsPanel):
        def _time_series_input(self, state, index, cell, lo, hi):
            geometry[index] = (implot.get_plot_pos(), implot.get_plot_size())
    panel = Panel()
    def frame():
        imgui.new_frame()
        imgui.set_next_window_pos(imgui.ImVec2(0, 0))
        imgui.set_next_window_size(imgui.ImVec2(1000, 900))
        imgui.begin('Frozen plot input test')
        panel.render(state)
        imgui.end()
        imgui.render()
    try:
        for _ in range(3):
            frame()
        for target in (1, 0):
            before = state.cells[target].x_lim
            pos, size = geometry[target]
            io.add_mouse_pos_event(pos.x + size.x * .5, pos.y + size.y + 8)
            frame()
            io.add_mouse_wheel_event(0., 1.)
            frame()
            frame()
            window = state.cells[target].x_lim
            assert window[1] - window[0] < before[1] - before[0]
            for i, cell in enumerate(state.cells, 1):
                np.testing.assert_allclose(cell.x_lim, window)
                np.testing.assert_allclose(state.plot_time_range(i), window)
    finally:
        state.shutdown()


def run(report_path):
    with TemporaryDirectory() as directory:
        root = Path(directory)
        t = np.arange(32768, dtype=np.float64) / 1024
        y = np.sin(t).astype(np.float32)
        y[1234], y[23456] = -17, 23
        path = root / "samples.parquet"
        pq.write_table(pa.table({"time": t, "signal": y}), path, row_group_size=4096)
        for backend in ("pyarrow", "polars"):
            for mode in ("memory", "lazy"):
                loaded = open_file(str(path), mode, cache_dir=root / "cache", backend=backend)
                source = loaded.register(DataRegistry()).data_source()
                times, channels = source.read_rows(["signal"], 4000, 4200)
                np.testing.assert_array_equal(times, t[4000:4200])
                np.testing.assert_array_equal(channels["signal"], y[4000:4200])
                points = source.read_plot("signal", t[0], t[-1], 200)
                assert 0 < len(points.values) < len(y)
                assert points.values.min() == -17 and points.values.max() == 23
                indices = np.searchsorted(t, points.time)
                np.testing.assert_array_equal(points.values, y[indices])
        # Exercise the spawned native conversion worker in the frozen executable.
        import threading
        csv = root / 'convert.csv'
        csv.write_text('time;signal\n0;1\n1;2\n')
        converted = root / 'converted.parquet'
        convert_csv_to_parquet(str(csv), str(converted), backend='polars', cancel=threading.Event())
        assert converted.exists()
        context = imgui.create_context()
        plot_context = implot.create_context()
        try:
            check_plot_input()
        finally:
            implot.destroy_context(plot_context)
            imgui.destroy_context(context)
    Path(report_path).write_text(json.dumps({"ok": True}), encoding="utf-8")
