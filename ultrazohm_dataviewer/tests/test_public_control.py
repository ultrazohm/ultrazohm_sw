"""Public API parity across independent offline and live recording registries."""

import numpy as np
import polars as pl
import pytest

from ultrazohm_dataviewer import ViewerError
from ultrazohm_dataviewer.live import LiveController, LiveSource, LiveUpdate
from ultrazohm_dataviewer.panels.live import LiveWorkspace


@pytest.fixture
def live_control(control_session, tmp_path):
    state, client, workers, pump = control_session
    workspace = LiveWorkspace(LiveController(lambda _: None), repo=tmp_path)
    state.viewer_operations.bind_live(workspace)

    def publish(epoch="first"):
        workspace.controller.update = LiveUpdate(
            workspace.update.revision + 1,
            source=LiveSource(
                pl.DataFrame({"time": np.arange(10.0) / 10, "a": np.arange(10.0)})
            ),
            epoch=(epoch, 0),
        )
        workspace.pump()

    def invoke(method, *args, **kwargs):
        future = workers.submit(method, *args, **kwargs)
        pump(future.done)
        return future.result()

    try:
        yield state, workspace, client, invoke, publish
    finally:
        workspace.close()


def test_live_plot_routing_and_registry_isolation(live_control, tmp_path):
    state, live, client, call, publish = live_control
    publish()
    path = tmp_path / "offline.csv"
    path.write_text("time,a\n0,1\n1,2\n")
    offline = call(client.load, path)
    view = call(client.live_view)
    run = call(client.list_runs, view=view)[0]["handle"]
    assert run.id == offline.id and run.view != offline.view
    call(client.set_grid, 2, 1, view=view)
    call(client.set_grid_ratios, [1, 3], [1], view=view)
    call(client.add_signal, 2, run, "a", view=view)
    call(client.set_axis, 2, run, "a", "right", view=view)
    call(client.set_y2_lim, 2, -2, 12, view=view)
    call(client.set_cursors, 2, 0.2, 0.4, view=view)
    assert state.cell_count == 1 and not state.cells[0].signals
    assert call(client.get_view, view=view)["row_ratios"] == [0.25, 0.75]
    plots = call(client.list_plots, view=view)
    assert plots[1]["signals"][0]["run"] == run
    assert plots[1]["y2_lim"] == [-2, 12]
    assert plots[1]["cursor_x"] == [0.2, 0.4]
    assert any(v["kind"] == "live" for v in call(client.list_views))
    for method, args, kwargs in (
        (client.add_signal, (1, run, "a"), {}),
        (client.add_signal, (1, offline, "a"), {"view": view}),
        (client.remove_signal, (2, offline, "a"), {"view": view}),
        (client.fft_source, (run, "a"), {}),
        (client.remove_run, (run,), {}),
    ):
        with pytest.raises(ViewerError, match="registry"):
            call(method, *args, **kwargs)
    with pytest.raises(ViewerError, match="cannot be closed"):
        call(client.close_view, view)
    call(client.export_data, 2, tmp_path / "live.csv", view=view)
    assert (tmp_path / "live.csv").exists()
    publish("replacement")
    with pytest.raises(ViewerError, match="no longer loaded"):
        call(client.add_signal, 1, run, "a", view=view)


def test_live_presentation_freeze_and_preferences(live_control):
    state, live, client, call, publish = live_control
    publish()
    view = call(client.live_view)
    run = call(client.list_runs, view=view)[0]["handle"]
    call(client.add_signal, 1, run, "a", view=view)
    call(client.live_time_depth, 0.5)
    call(client.set_x_lim, 1, 0.2, 0.7, view=view)
    assert call(client.live_status)["paused"]
    frozen = call(client.live_freeze)
    assert frozen.view == 1
    np.testing.assert_allclose(state.registry.get(frozen.id).time, np.arange(2, 8) / 10)
    call(client.reset_view, 1, view=view)
    assert call(client.live_status)["follow"]
    call(client.live_follow, False)
    assert live.paused
    call(client.set_grid, 2, 1, view=view)
    call(client.save_live_view)
    call(client.set_grid, 1, 1, view=view)
    call(client.load_live_view)
    assert call(client.get_view, view=view)["grid"] == [2, 1]
    assert call(client.live_status)["paused"]
    assert live.state.cells[0].signals == [(live.run.id, "a")]
    before = live.window_seconds
    for bad in (0, -1, live.maximum_depth() + 1):
        with pytest.raises(ViewerError):
            call(client.live_time_depth, bad)
        assert live.window_seconds == before


def test_pending_live_preferences_and_invalid_edits(live_control):
    _, live, client, call, publish = live_control
    view = call(client.live_view)
    call(client.set_grid, 2, 1, view=view)
    call(client.save_live_view)
    call(client.set_grid, 1, 1, view=view)
    call(client.load_live_view)
    assert live._pending_plot_setup is not None
    with pytest.raises(ViewerError):
        call(client.set_grid_ratios, [0, 1], [1], view=view)
    assert live._pending_plot_setup is not None
    call(client.set_grid, 3, 1, view=view)
    publish()
    assert live.state.rows == 3


def test_restore_inspect_waits_for_first_snapshot(live_control):
    _, live, client, call, publish = live_control
    call(client.live_follow, False)
    call(client.save_live_view)
    call(client.load_live_view)
    assert not live.paused  # No snapshot exists yet.
    publish()
    assert live.paused and live.run is not None
    source = live.run.source
    publish("newer")
    assert live.run.source is source


def test_live_attachment_completion_and_failure(live_control, monkeypatch):
    _, live, client, call, _ = live_control
    controller = live.controller
    monkeypatch.setattr(controller, "_poll_work", lambda: None)

    def command(operation, kwargs, **_):
        if kwargs.get("endpoint") == "bad":
            raise RuntimeError("attachment failed")
        controller.endpoint = kwargs.get("endpoint", controller.endpoint)
        controller.attached = operation == "attach"

    monkeypatch.setattr(controller, "_command", command)
    assert call(client.live_attach, "127.0.0.1:19740")["attached"]
    assert not call(client.live_detach)["attached"]
    with pytest.raises(ViewerError, match="attachment failed"):
        call(client.live_attach, "bad")


def test_superseded_attachment_completes_as_cancelled(monkeypatch):
    controller = LiveController(lambda _: None)
    calls = []
    monkeypatch.setattr(controller, "_poll_work", lambda: None)
    monkeypatch.setattr(controller, "_command", lambda op, kw, **_: calls.append(op))
    try:
        with controller._command_lock:
            first = controller.request_attachment("attach", endpoint="unused")
            second = controller.request_attachment("detach")
        second.result(timeout=3)
        assert first.cancelled()
        assert calls == ["detach"]
    finally:
        controller.close()


def test_readback_and_unavailable_live(control_session, tmp_path):
    state, client, workers, pump = control_session

    def script():
        with pytest.raises(ViewerError, match="not enabled"):
            client.live_view()
        path = tmp_path / "source.csv"
        path.write_text("time,a\n0,1\n1,2\n")
        run = client.load(path)
        client.fft_source(run, "a")
        client.fft_hann(False)
        client.hist_bins(17)
        assert client.get_analysis("fft")["sources"][0]["run"] == run
        assert client.get_analysis("fft")["window"] is False
        assert client.get_analysis("histogram")["bins"] == 17
        saved = client.get_settings()["max_points"]
        client.set_max_points(saved + 100)
        assert client.get_settings()["max_points"] == saved
        assert client.get_session_settings()["max_points"] == saved + 100
        with pytest.raises(ViewerError):
            client.get_analysis("other")

    future = workers.submit(script)
    pump(future.done)
    future.result()


def test_headless_facade_exports():
    import ultrazohm_dataviewer as package
    from ultrazohm_dataviewer import api

    for name in api.__all__:
        assert getattr(package, name) is getattr(api, name)


def test_terminal_grid_ratios_and_live_scope(monkeypatch, capsys):
    from ultrazohm_dataviewer import cli

    calls = []
    monkeypatch.setattr(
        cli.Client, "_call", lambda self, op, **kw: calls.append((op, kw))
    )
    assert cli.main(["set-grid-ratios", "[1, 3]", "[1]", "--view", "0"]) == 0
    assert calls[-1][1]["rows"] == [1, 3]
    assert calls[-1][1]["view"].id == 0
    assert cli.main(["add-signal", "1", "1", "a", "--view", "0"]) == 0
    assert calls[-1][1]["run"].view == 0


def test_reconnect_gap_preserves_bindings_and_user_clear(live_control):
    from dataclasses import replace

    _, live, client, call, publish = live_control
    publish()
    view = call(client.live_view)
    run = call(client.list_runs, view=view)[0]["handle"]
    call(client.set_grid, 2, 1, view=view)
    for plot in (1, 2):
        call(client.add_signal, plot, run, "a", view=view)
    call(client.set_axis, 1, run, "a", "right", view=view)
    live.controller.update = replace(
        live.update, revision=live.update.revision + 1, source=None, epoch=None
    )
    live.pump()
    call(client.clear_plot, 2, view=view)
    call(client.set_grid_ratios, [1, 3], [1], view=view)
    publish("new")
    assert live.state.cells[0].signals == [(live.run.id, "a")]
    assert live.state.cells[0].y2_signals == [(live.run.id, "a")]
    assert live.state.cells[1].signals == []
    assert live.state.row_ratios == [0.25, 0.75]


def test_reconnect_waits_for_samples_and_drops_absent_names(live_control):
    from dataclasses import replace

    _, live, client, call, publish = live_control
    publish()
    view = call(client.live_view)
    run = call(client.list_runs, view=view)[0]["handle"]
    call(client.add_signal, 1, run, "a", view=view)
    call(client.set_xy, 1, run, "a", view=view)
    live.controller.update = replace(
        live.update,
        revision=live.update.revision + 1,
        epoch=("replacement", 0),
        catalog={"observables": {"a": 1}},
        source=LiveSource(pl.DataFrame({"time": [0.0, 1.0], "other": [1.0, 2.0]})),
    )
    live.pump()
    assert live._reconnect_signals
    call(client.save_live_view)
    import json

    saved = json.loads((live.user_directory() / "live_view.json").read_text())
    assert saved["plots"]["cells"][0]["signals"] == ["a"]
    publish("replacement")
    assert live.state.cells[0].xy_source == (live.run.id, "a")
    assert not live._reconnect_signals
    live.controller.update = replace(
        live.update,
        revision=live.update.revision + 1,
        epoch=("removed", 0),
        catalog={"observables": {"other": 1}},
        source=LiveSource(pl.DataFrame({"time": [0.0, 1.0], "other": [1.0, 2.0]})),
    )
    live.pump()
    assert not live.state.cells[0].signals
    assert live.state.cells[0].xy_source is None
    assert not live._reconnect_signals
