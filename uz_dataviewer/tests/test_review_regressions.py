import numpy as np
import pytest
from uz_dataviewer import nodes, session
from uz_dataviewer.commands import CommandError
from uz_dataviewer.panels.nodes import NodesPanel
from uz_dataviewer.panels.plots import PlotsPanel


@pytest.mark.parametrize("backend", ["pyarrow", "polars"])
def test_normalized_full_window_preserves_all_samples(tmp_path, backend):
    p = tmp_path / "log.csv"
    p.write_text("time;a\n" + "".join(f"{i / 10};{i}\n" for i in range(1, 9)))
    from uz_dataviewer.loader import open_file
    from uz_dataviewer.model import DataRegistry

    results = []
    for mode in ("memory", "lazy"):
        run = open_file(str(p), mode, backend=backend).register(DataRegistry())
        run.set_time_origin(100)
        limits = (float(run.time[0]), float(run.time[-1]))
        results.append(run.read_window(["a"], *limits)[1]["a"].tolist())
    assert results == [list(range(1, 9)), list(range(1, 9))]


def test_node_pos_moves_existing_canvas(app_state, gui_frame):
    from imgui_bundle import imgui_node_editor as ed

    node = app_state.nodes.add("math")
    node.pos = (100.0, 100.0)
    panel = NodesPanel()
    for _ in range(3):
        gui_frame(panel, app_state)
    app_state.commands.execute(app_state, "node_pos", [node.id, 600, 400])
    for _ in range(3):
        gui_frame(panel, app_state)
    pos = ed.get_node_position(ed.NodeId(node.id * 4))
    assert node.pos == (600.0, 400.0) and (pos.x, pos.y) == (600.0, 400.0)


def test_link_enable_syncs_driver(app_state, gui_frame):
    s = app_state
    s.services.display.synchronous = True
    s.registry.add_run("a", "a", np.arange(100.0), {"a": np.arange(100.0)}, {})
    s.set_grid(1, 2)
    for c in s.cells:
        c.add((1, "a"))
    panel = PlotsPanel()
    s.set_plot_x_limits(1, 10, 20)
    for _ in range(3):
        gui_frame(panel, s)
    panel._driver = 0
    s.commands.execute(s, "link_x", [False])
    s.set_plot_x_limits(1, 30, 40)
    for _ in range(3):
        gui_frame(panel, s)
    s.commands.execute(s, "link_x", [True])
    for _ in range(3):
        gui_frame(panel, s)
    assert s.cells[0].x_lim == s.cells[1].x_lim
    assert s.plot_time_range(1) == s.cells[0].x_lim


def test_plugin_bad_dtype_does_not_abort_siblings(app_state, monkeypatch):
    s = app_state
    s.registry.add_run("a", "a", np.arange(8.0), {"a": np.ones(8)}, {})
    src = s.nodes.add("source", ref=(1, "a"))
    monkeypatch.setitem(
        nodes.REGISTRY,
        "bad_dtype",
        nodes.TransformSpec("bad_dtype", lambda i, p: (i[0][0], ["bad"] * 8, "")),
    )
    bad = s.nodes.add("bad_dtype")
    good = s.nodes.add("math")
    s.nodes.link(src.id, bad.id)
    s.nodes.link(src.id, good.id)
    assert nodes.evaluate(s) == 1
    assert bad.error and good.out_y is not None


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


def test_plugin_cannot_mutate_recording(app_state, monkeypatch):
    s = app_state
    run = s.registry.add_run("a", "a", np.arange(8.0), {"a": np.ones(8)}, {})
    src = s.nodes.add("source", ref=(1, "a"))
    cached = s.nodes.add("math")
    s.nodes.link(src.id, cached.id)
    assert nodes.evaluate(s) == 1

    def mutate(inputs, params):
        t, y = inputs[0]
        y *= 10
        return t, y, "mutated"

    monkeypatch.setitem(nodes.REGISTRY, "mutate", nodes.TransformSpec("mutate", mutate))
    mut = s.nodes.add("mutate")
    s.nodes.link(src.id, mut.id)
    assert nodes.evaluate(s) == 0
    assert "read-only" in mut.error
    assert np.all(run.signals["a"].y == 1) and np.all(cached.out_y == 1)
    assert not nodes.is_stale(s.registry, s.nodes, cached)


def test_documented_moving_average_handles_short_input(monkeypatch):
    import runpy
    from uz_dataviewer import api

    with monkeypatch.context() as patch:
        patch.setattr(nodes, "REGISTRY", dict(nodes.REGISTRY))
        import uz_dataviewer.plugins as plugins

        patch.setattr(plugins, "REGISTRY", nodes.REGISTRY)
        from pathlib import Path

        runpy.run_path(
            str(Path(__file__).parents[1] / "examples/plugins/moving_average.py")
        )
        t, y, _ = api.node("movavg", (np.arange(8.0), np.ones(8)))
        assert len(t) == len(y) == 8


@pytest.mark.parametrize("backend", ["pyarrow", "polars"])
@pytest.mark.parametrize("origin", [100.0, 1e16, -100.0, 0.1])
@pytest.mark.parametrize("raw_origin", [0.0, 1e16])
def test_displayed_selection_matches_resident_mask(
    tmp_path, backend, origin, raw_origin
):
    from uz_dataviewer.loader import open_file
    from uz_dataviewer.model import DataRegistry
    from uz_dataviewer.analysis import AnalysisInput, histogram_sources
    from uz_dataviewer.sources import displayed_bounds

    path = tmp_path / "samples.csv"
    raw = raw_origin + np.array([0.1, 0.2, 0.2, 0.3, 0.8])
    path.write_text("time,a\n" + "".join(f"{t},{i}\n" for i, t in enumerate(raw)))
    displayed = (raw - raw[0]) + origin
    for mode in ("memory", "lazy"):
        run = open_file(str(path), mode, backend=backend).register(DataRegistry())
        run.set_time_origin(origin)
        assert run.time[0] == origin
        selected = AnalysisInput.capture(DataRegistryWithRun(run), [(run.id, "a")])[0]
        for lo, hi in [
            (displayed[0], displayed[-1]),
            (displayed[1], displayed[1]),
            (displayed[1], displayed[-1]),
            (origin - 10, origin - 5),
        ]:
            mask = (displayed >= lo) & (displayed <= hi)
            t, y = selected.read_window(lo, hi, None)
            np.testing.assert_array_equal(t, displayed[mask])
            np.testing.assert_array_equal(y, np.arange(len(raw))[mask])
            a, b = displayed_bounds(run.data_source(), lo, hi, run.time_offset)
            assert b - a == mask.sum()
            plot = run.data_source().read_plot(
                "a", lo, hi, 100, padding=False, offset=run.time_offset
            )
            assert plot.raw_count == mask.sum()
            _, count, dropped = histogram_sources(
                [("a", run.data_source(), "a", run.time_offset)], lo, hi, 5
            )
            assert count == mask.sum() and dropped == 0


class DataRegistryWithRun:
    def __init__(self, run):
        self.run = run

    def get(self, run_id):
        return self.run if run_id == self.run.id else None


def test_plugin_output_owns_its_buffers(app_state, monkeypatch):
    t, y = np.arange(8.0), np.ones(8, dtype=np.float32)
    monkeypatch.setitem(
        nodes.REGISTRY,
        "retained",
        nodes.TransformSpec("retained", lambda i, p: (t, y, ""), inputs=(0, 0)),
    )
    node = app_state.nodes.add("retained")
    assert nodes.evaluate(app_state) == 1
    t[:] = -1
    y[:] = 99
    np.testing.assert_array_equal(node.out_time, np.arange(8.0))
    np.testing.assert_array_equal(node.out_y, np.ones(8))


def test_frequency_outputs_keep_independent_axes(app_state, gui_frame, tmp_path):
    s = app_state
    s.services.display.synchronous = True
    t = np.arange(128.0) / 128
    run = s.registry.add_run("a", "a", t, {"a": np.sin(2 * np.pi * 8 * t)}, {})
    src = s.nodes.add("source", ref=(run.id, "a"))
    fft = s.nodes.add("fft")
    s.nodes.link(src.id, fft.id)
    assert nodes.evaluate(s) == 1
    spectrum = s.registry.get(fft.out_run_id)
    assert spectrum.axis_domain == "frequency"
    s.set_grid(1, 2)
    s.commands.execute(s, "add_signal", [1, run.id, "a"])
    s.commands.execute(s, "add_signal", [2, spectrum.id, "out"])
    s.set_plot_x_limits(1, 0.1, 0.5)
    s.set_plot_x_limits(2, 1, 40)
    assert s.shared_x == (0.1, 0.5)
    assert s.plot_time_range(2) == (1, 40)
    panel = PlotsPanel()
    for _ in range(3):
        gui_frame(panel, s)
    assert s.cells[1].x_lim == (1, 40)
    path = tmp_path / "spectrum.csv"
    session.export_data(s, 1, str(path))
    assert path.read_text().splitlines()[0] == "frequency,out"
    for command, args in [
        ("add_signal", [1, spectrum.id, "out"]),
        ("fft_source", [spectrum.id, "out"]),
        ("normalize_time", [spectrum.id, 0]),
        ("fft_follow", [2]),
    ]:
        with pytest.raises((ValueError, CommandError)):
            s.commands.execute(s, command, args)
    math = s.nodes.add("math")
    s.nodes.link(fft.id, math.id)
    assert nodes.evaluate(s) == 1
    assert s.registry.get(math.out_run_id).axis_domain == "frequency"
    filter_node = s.nodes.add("filter")
    s.nodes.link(fft.id, filter_node.id)
    assert nodes.evaluate(s) == 0
    assert "time-domain" in filter_node.error


def test_state_import_does_not_load_gui():
    import subprocess
    import sys

    subprocess.run(
        [
            sys.executable,
            "-c",
            "import sys; from uz_dataviewer.state import AppState; "
            's=AppState(); s.shutdown(); assert "imgui_bundle" not in sys.modules',
        ],
        check=True,
    )


@pytest.mark.parametrize("closing", [False, True])
def test_owned_upload_released_after_last_reference(app_state, tmp_path, closing):
    path = tmp_path / "upload.csv"
    path.write_text("time,a\n0,1\n1,2\n")
    app_state.backend = "pyarrow"
    app_state.loading_mode = "lazy"
    first = app_state.load_sync(str(path))
    second = app_state.load_sync(str(path))
    first.owned_upload = True
    first.reloadable = False
    app_state.remove_run(first.id)
    assert path.exists() and second.owned_upload and not second.reloadable
    if closing:
        app_state.shutdown()
    else:
        app_state.remove_run(second.id)
    assert not path.exists()


def test_node_position_zero_is_explicit(app_state, gui_frame):
    from imgui_bundle import imgui_node_editor as ed

    node = app_state.nodes.add("math")
    app_state.commands.execute(app_state, "node_pos", [node.id, 0, 0])
    panel = NodesPanel()
    for _ in range(3):
        gui_frame(panel, app_state)
    pos = ed.get_node_position(ed.NodeId(node.id * 4))
    assert (pos.x, pos.y) == node.pos == (0.0, 0.0)


def test_invalid_boolean_can_be_repaired_in_node_canvas(app_state, gui_frame):
    node = app_state.nodes.add("fft")
    node.params["window"] = "invalid"
    gui_frame(NodesPanel(), app_state)
    assert node.params["window"] == "invalid"
    app_state.commands.execute(app_state, "node_set", [node.id, "window", "true"])
    assert node.params["window"] == "true"


def test_async_load_echo_preserves_captured_settings(states, tmp_path):
    from uz_dataviewer.state import LoadRequest

    state, replay = states(), states()
    path = tmp_path / "recording.csv"
    path.write_text("time,a\n0,10\n1,20\n")
    state.backend = replay.backend = "polars"
    state.loading_mode = replay.loading_mode = "lazy"
    state._submit_load(LoadRequest(str(path), "memory", "pyarrow", False))
    for entry in state.console._entries:
        if entry.level == "CMD":
            replay.commands.dispatch(replay, entry.message)
    run = replay.registry.runs[0]
    assert run.storage_mode == "memory" and run.backend == "pyarrow"
    assert replay.loading_mode == "lazy" and replay.backend == "polars"
