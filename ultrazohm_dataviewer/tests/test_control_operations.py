"""Exercise real data and session lifecycle through the local client."""

import json
import os
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import pytest

from ultrazohm_dataviewer import Client, ViewerError
from ultrazohm_dataviewer.control_server import ControlServer
from ultrazohm_dataviewer.operations import Operations


def test_conversion_does_not_block_dispatch_and_waits_for_output(
    app_state, tmp_path, monkeypatch
):
    import threading

    from ultrazohm_dataviewer import loader

    csv = tmp_path / "recording.csv"
    csv.write_text("time,y\n0,1\n0.001,2\n")
    output = tmp_path / "recording.parquet"
    started, release = threading.Event(), threading.Event()
    original = loader.convert_csv_to_parquet

    def convert(*args, **kwargs):
        started.set()
        assert release.wait(3)
        return original(*args, **kwargs)

    monkeypatch.setattr(loader, "convert_csv_to_parquet", convert)
    operations = Operations(app_state)
    try:
        future = operations.dispatch(
            "convert", {"src": str(csv), "dst": str(output)}, None
        )
        assert started.wait(2)
        assert not future.done()
        assert not output.exists()
        operations.dispatch("set_grid", {"rows": 2, "cols": 2}, None)
        assert app_state.rows == 2
        release.set()
        deadline = time.monotonic() + 3
        while not future.done() and time.monotonic() < deadline:
            operations.poll()
            time.sleep(0.001)
        assert future.result()["result"] == str(output)
        assert output.exists()
    finally:
        release.set()
        operations.close()


def test_client_builds_and_restores_workspace(app_state, tmp_path):
    csv = tmp_path / "recording.csv"
    csv.write_text("time,y\n0,1\n0.001,2\n0.002,3\n")
    snapshot = tmp_path / "workspace.json"
    operations = Operations(app_state)
    server = ControlServer("127.0.0.1:0")
    workers = ThreadPoolExecutor(1)
    client = Client(server.endpoint, timeout=5)

    def invoke(function, *args):
        future = workers.submit(function, *args)
        deadline = time.monotonic() + 10
        while not future.done() and time.monotonic() < deadline:
            operations.poll()
            server.poll(operations.dispatch)
            time.sleep(0.001)
        return future.result(timeout=0.1)

    try:
        handle = invoke(client.load, csv)
        invoke(client.set_grid, 3, 2)
        invoke(client.add_signal, 1, handle, "y")
        invoke(client.show_samples, 1, True)
        assert app_state.cells[0].show_samples
        source = invoke(client.node_source, handle, "y")
        invoke(client.node_rename, source, "source-y")
        assert app_state.nodes.get(source.id).name == "source-y"
        transform = invoke(client.node_add, "math")
        invoke(client.node_link, source, transform)
        invoke(client.node_eval)
        output = invoke(client.node_output, transform)
        invoke(client.add_signal, 2, output, "out")
        assert len(invoke(client.list_nodes)) == 2
        assert invoke(client.list_plots)[1]["signals"][0]["signal"] == "out"
        invoke(client.export_data, 1, tmp_path / "export.csv")
        assert (tmp_path / "export.csv").exists()
        invoke(client.save_session, snapshot)
        assert json.loads(snapshot.read_text())["runs"][0]["path"] == "recording.csv"
        invoke(client.clear_session)
        assert not app_state.registry.runs
        with pytest.raises(ViewerError, match="another session"):
            invoke(client.add_signal, 1, handle, "y")
        invoke(client.load_session, snapshot)
        assert app_state.cell_count == 6
        assert app_state.cells[0].signals[0][1] == "y"
        token = app_state.session_token
        with pytest.raises(ViewerError):
            invoke(client.load_session, tmp_path / "missing.json")
        assert app_state.session_token is token
        assert invoke(client.status)["runs"] >= 2
    finally:
        server.close()
        operations.close()
        workers.shutdown(wait=True)
        client.close()


def test_terminal_commands_control_existing_state(app_state, tmp_path):
    operations = Operations(app_state)
    server = ControlServer("127.0.0.1:0")
    env = dict(os.environ, PYTHONPATH=str(Path(__file__).resolve().parents[1] / "src"))

    def command(*args):
        process = subprocess.Popen(
            [
                sys.executable,
                "-m",
                "ultrazohm_dataviewer",
                "--json",
                "--endpoint",
                server.endpoint,
                *args,
            ],
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )
        try:
            deadline = time.monotonic() + 10
            while process.poll() is None and time.monotonic() < deadline:
                operations.poll()
                server.poll(operations.dispatch)
                time.sleep(0.002)
            stdout, stderr = process.communicate(timeout=0.5)
            return process.returncode, stdout, stderr
        finally:
            if process.poll() is None:
                process.kill()
            process.wait()

    try:
        code, output, error = command("set-grid", "2", "3")
        assert code == 0, error
        assert app_state.cell_count == 6
        code, output, error = command("status")
        assert code == 0, error
        assert json.loads(output)["grid"] == [2, 3]
        for operation, config in (
            ("fft-follow", app_state.fft),
            ("hist-follow", app_state.histogram),
        ):
            for target, expected in (
                ("full", -1),
                ("custom", 0),
                ("plot_2", 2),
                ("-1", -1),
                ("0", 0),
                ("2", 2),
            ):
                code, output, error = command(operation, target)
                assert code == 0, error
                assert config.follow_plot == expected
            code, output, error = command(operation, "invalid")
            assert code == 1
            assert (
                "Expected custom/full/plot_N" in json.loads(error)["error"]["message"]
            )
            assert config.follow_plot == 2
        code, output, error = command("load", str(tmp_path / "missing.csv"))
        assert code == 1
        assert json.loads(error)["error"]["message"]
    finally:
        server.close()
        operations.close()


def test_cli_import_does_not_load_gui_or_numpy():
    env = dict(os.environ, PYTHONPATH=str(Path(__file__).resolve().parents[1] / "src"))
    subprocess.run(
        [
            sys.executable,
            "-S",
            "-c",
            "import sys; from ultrazohm_dataviewer.cli import parser; parser(); "
            'assert not {"numpy", "imgui_bundle"} & sys.modules.keys()',
        ],
        env=env,
        check=True,
    )


def test_additional_views_survive_session_restore(app_state, tmp_path):
    from ultrazohm_dataviewer.session import load_state, save_state

    csv = tmp_path / "source.csv"
    csv.write_text("time,a\n0,1\n1,2\n")
    run = app_state.load_sync(str(csv))
    view = app_state.create_plot_view()
    view.set_grid(2, 2)
    view.set_grid_ratios([0.3, 0.7], [0.4, 0.6])
    view.cells[2].add((run.id, "a"))
    view.set_plot_x_limits(3, 0.2, 0.8)
    snapshot = tmp_path / "session.json"
    save_state(app_state, snapshot)
    load_state(app_state, snapshot)
    restored = app_state.plot_views[2]
    assert restored is not view
    assert view.services is None
    assert restored.registry is app_state.registry
    assert restored.cell_count == 4
    assert restored.row_ratios == [0.3, 0.7]
    assert restored.cells[2].signals[0][1] == "a"
    assert restored.plot_time_range(3) == (0.2, 0.8)
    assert app_state.create_plot_view().plot_window_id == 3


def test_client_targets_explicit_plot_views(control_session, tmp_path):
    state, client, workers, pump = control_session
    csv = tmp_path / "recording.csv"
    csv.write_text("time,a\n0,1\n1,2\n")

    def script():
        run = client.load(csv)
        view = client.create_view()
        client.set_grid(2, 2, view=view)
        client.add_signal(3, run, "a", view=view)
        client.show_samples(3, True, view=view)
        assert len(client.list_plots(view=view)) == 4
        assert len(client.list_views()) == 2
        assert len(client.list_plots()) == 1
        client.close_view(view)
        with pytest.raises(ViewerError, match="no longer open"):
            client.set_grid(1, 1, view=view)
        assert client.create_view().id > view.id

    future = workers.submit(script)
    pump(future.done)
    future.result()
    assert state.cell_count == 1
