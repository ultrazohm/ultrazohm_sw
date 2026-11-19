"""Exercise bundled native modules and lazy Parquet reads without a display."""
import json
from pathlib import Path
from tempfile import TemporaryDirectory

import numpy as np
import pyarrow as pa
import pyarrow.parquet as pq
from imgui_bundle import imgui, implot

from ultrazohm_dataviewer.loader import open_file, convert_csv_to_parquet
from ultrazohm_dataviewer.model import DataRegistry


def check_python_control(root, recording):
    """Run an ordinary script through the bundled worker against a live server."""
    import time
    from ultrazohm_dataviewer.control_server import ControlServer
    from ultrazohm_dataviewer.operations import Operations
    from ultrazohm_dataviewer.scripting import ScriptRunner
    from ultrazohm_dataviewer.state import AppState
    state = AppState()
    operations = Operations(state)
    server = ControlServer('127.0.0.1:0')
    runner = ScriptRunner(device_control=False)
    script = root / 'control.py'
    script.write_text('''import sys
from pathlib import Path
from ultrazohm_dataviewer import Client, ViewerError
assert sys.argv[2] == 'argument with spaces'
with Client() as viewer:
    viewer.clear_session()
    run = viewer.load(sys.argv[1])
    viewer.set_grid(2, 1)
    viewer.add_signal(1, run, 'signal')
    source = viewer.node_source(run, 'signal')
    transform = viewer.node_add('math')
    viewer.node_link(source, transform)
    viewer.node_eval()
    viewer.add_signal(2, viewer.node_output(transform), 'out')
    viewer.fft_source(run, 'signal')
    viewer.fft()
    viewer.hist_source(run, 'signal')
    viewer.histogram()
    view = viewer.create_view()
    viewer.add_signal(1, run, 'signal', view=view)
    viewer.save_session('saved.json')
    viewer.clear_session()
    viewer.load_session('saved.json')
    assert viewer.status()['grid'] == [2, 1]
    assert len(viewer.list_runs()) == 2
    assert len(viewer.list_views()) == 2
    try:
        viewer.add_signal(1, run, 'signal')
    except ViewerError as error:
        assert error.code == 'stale_handle'
    else:
        raise AssertionError('old handle accepted')
Path('script-completed').write_text('ok')
''', encoding='utf-8')
    try:
        runner.start(script, viewer_endpoint=server.endpoint,
                     args=[str(recording), 'argument with spaces'], cwd=root)
        deadline = time.monotonic() + 30
        while runner.busy and time.monotonic() < deadline:
            operations.poll()
            server.poll(operations.dispatch)
            runner.poll()
            time.sleep(.001)
        assert not runner.busy, 'Bundled Python control script timed out'
        assert runner.exit_code == 0, runner.output
        assert (root / 'script-completed').read_text() == 'ok'
        import sys
        import subprocess
        if getattr(sys, 'frozen', False):
            terminal = Path(sys.executable)
            # The windowed Windows parent has no console stdin. Supply every
            # standard handle explicitly when starting the console executable.
            help_result = subprocess.run([str(terminal), '--cli', '--help'], stdin=subprocess.DEVNULL,
                                         capture_output=True, text=True, timeout=10)
            assert help_result.returncode == 0 and 'usage:' in help_result.stdout, repr(help_result)
            invalid = subprocess.run([str(terminal), '--cli', 'not-a-command'], stdin=subprocess.DEVNULL,
                                     capture_output=True, text=True, timeout=10)
            assert invalid.returncode != 0 and invalid.stderr, repr(invalid)
            for command in ('status', 'list-runs'):
                process = subprocess.Popen([str(terminal), '--cli', '--endpoint', server.endpoint, '--json', command],
                                           stdin=subprocess.DEVNULL,
                                           stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
                try:
                    deadline = time.monotonic() + 10
                    while process.poll() is None and time.monotonic() < deadline:
                        operations.poll()
                        server.poll(operations.dispatch)
                        time.sleep(.001)
                    stdout, stderr = process.communicate(timeout=1)
                    assert process.returncode == 0, stderr
                    result = json.loads(stdout)
                    if command == 'status':
                        assert result['grid'] == [2, 1]
                    else:
                        assert len(result) == 2 and result[0]['handle']['session']
                finally:
                    if process.poll() is None:
                        process.kill()
                    process.wait()

    finally:
        runner.close()
        server.close()
        operations.close()
        state.shutdown()


def check_plot_input():
    """Exercise packaged ImPlot mouse input on both platforms without a GPU."""
    from ultrazohm_dataviewer.panels.plots import PlotsPanel
    from ultrazohm_dataviewer.state import AppState
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
        check_python_control(root, path)
        context = imgui.create_context()
        plot_context = implot.create_context()
        try:
            check_plot_input()
        finally:
            implot.destroy_context(plot_context)
            imgui.destroy_context(context)
    Path(report_path).write_text(json.dumps({"ok": True}), encoding="utf-8")
