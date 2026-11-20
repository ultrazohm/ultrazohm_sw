"""Live preferences persist independently of recording/session identities."""

import json
from dataclasses import replace
from types import SimpleNamespace

import numpy as np
import polars as pl

from ultrazohm_dataviewer.live import LiveController, LiveSource, LiveUpdate
from ultrazohm_dataviewer.live_settings import save
from ultrazohm_dataviewer.panels.live import LiveWorkspace


def workspace(root):
    panel = LiveWorkspace(LiveController(lambda _: None), repo=root)
    directory = panel.user_directory()
    panel.mapping = str(directory / "mapping.json")
    if not (directory / "mapping.json").exists():
        (directory / "mapping.json").write_text(
            json.dumps({"channels": 20, "observables": {"a": 1, "b": 2}})
        )
        (directory / "settings.json").write_text(
            json.dumps(
                {
                    "schema_version": 1,
                    "name": "test",
                    "sample_period_us": 100.0,
                    "initial_channels": {"1": "a"},
                }
            )
        )
    return panel


def publish(panel, run_id="first"):
    source = LiveSource(
        pl.DataFrame(
            {"time": np.arange(10.0) / 1000, "a": np.arange(10.0), "b": np.arange(10.0)}
        )
    )
    panel.controller.update = LiveUpdate(
        1,
        source=source,
        epoch=(run_id, 0),
        attached=True,
        catalog={
            "sample_period_us": 50.0,
            "channels": 20,
            "observables": {"a": 1, "b": 2},
        },
        assignments=({"channel": 1, "name": "b"}, {"channel": 2, "name": "a"}),
    )
    panel.pump()


def test_save_and_restore_live_settings_without_sending_commands(tmp_path):
    first = workspace(tmp_path)
    second = None
    try:
        publish(first)
        first.state.set_grid(2, 1)
        first.state.set_grid_ratios([1, 3], [1])
        cell = first.state.cells[1]
        cell.add((first.run.id, "b"))
        cell.set_secondary((first.run.id, "b"), True)
        cell.set_limits("y2", -2.0, 8.0)
        cell.show_samples = True
        cell.cursors = True
        cell.cursor_x = (0.001, 0.005)
        first.window_seconds = 4.0
        first.ip = "192.168.1.42"
        first.port = 1001
        first.variable_values = {"setpoint": "3.5"}
        directory = save(first)
        assert json.loads((directory / "settings.json").read_text())[
            "initial_channels"
        ] == {"1": "b", "2": "a"}
        assert (
            json.loads((directory / "settings.json").read_text())["sample_period_us"]
            == 50.0
        )
        second = workspace(tmp_path)
        second.load_live_settings()
        assert second.ip == "192.168.1.42"
        assert second.port == 1001
        assert second.window_seconds == 4.0
        assert second.variable_values == {"setpoint": "3.5"}
        assert not second.update.attached
        assert second.controller.commands.empty()
        # A disconnected save must retain the pending layout and saved channels.
        before = (directory / "settings.json").read_text()
        save(second)
        assert (directory / "settings.json").read_text() == before
        publish(second, "another-service")
        assert second.state.rows == 2
        assert second.state.row_ratios == [0.25, 0.75]
        restored = second.state.cells[1]
        assert restored.signals == [(second.run.id, "b")]
        assert restored.y2_signals == restored.signals
        assert restored.y2_lim == (-2.0, 8.0)
        assert restored.show_samples and restored.cursors
        assert restored.cursor_x == (0.001, 0.005)
    finally:
        first.close()
        if second:
            second.close()


def test_invalid_view_does_not_partially_apply_preferences(tmp_path):
    panel = workspace(tmp_path)
    try:
        save(panel)
        path = panel.user_directory() / "live_view.json"
        data = json.loads(path.read_text())
        data["ip"] = "changed"
        data["plots"]["grid"] = [0, 1]
        path.write_text(json.dumps(data))
        panel.load_live_settings()
        assert panel.ip == "192.168.1.233"
        assert "Could not load live settings" in panel.settings_notice
        assert panel._pending_plot_setup is None
    finally:
        panel.close()


def test_missing_live_signals_do_not_prevent_restoring_other_traces(tmp_path):
    panel = workspace(tmp_path)
    try:
        publish(panel)
        panel.state.cells[0].add((panel.run.id, "a"))
        panel.state.cells[0].add((panel.run.id, "missing"))
        save(panel)
        panel.load_live_settings()
        panel.controller.update = replace(panel.controller.update, revision=2)
        panel._source = None
        panel.pump()
        assert panel.state.cells[0].signals == [(panel.run.id, "a")]
    finally:
        panel.close()


def test_save_live_button_writes_settings(gui_frame, app_state, monkeypatch, tmp_path):
    from imgui_bundle import imgui

    panel = workspace(tmp_path)
    panel.available = True
    monkeypatch.setattr(
        imgui, "button", lambda label, *args, **kwargs: label == "Save live settings"
    )
    try:
        gui_frame(SimpleNamespace(render=panel.render_data), app_state)
        assert (panel.user_directory() / "live_view.json").is_file()
        assert "Live settings saved" in panel.settings_notice
    finally:
        panel.close()


def test_attached_service_cannot_save_incompatible_local_startup_channels(tmp_path):
    import pytest

    panel = workspace(tmp_path)
    try:
        directory = save(panel)
        paths = [directory / "settings.json", directory / "live_view.json"]
        before = [path.read_bytes() for path in paths]
        for assignment in (
            {"channel": 1, "name": "REMOTE_ONLY"},
            {"channel": 21, "name": "a"},
        ):
            panel.update = replace(
                panel.update,
                attached=True,
                catalog={
                    "channels": 32,
                    "observables": {"REMOTE_ONLY": 1, "a": 2},
                    "sample_period_us": 50.0,
                },
                assignments=(assignment,),
            )
            with pytest.raises(
                ValueError, match="absent from the selected firmware mapping"
            ):
                save(panel)
            assert [path.read_bytes() for path in paths] == before
    finally:
        panel.close()


def test_save_refreshes_local_repository_mapping_after_firmware_changes(
    tmp_path, monkeypatch
):
    from ultrazohm_dataviewer.settings import load_workspace_settings

    panel = workspace(tmp_path)
    try:
        panel._repository_settings = load_workspace_settings(
            panel.mapping, panel.user_directory()
        )
        assert "NEW_SIGNAL" not in panel._repository_settings.mapping["observables"]
        requested = []

        def read_mapping(repo):
            requested.append(repo)
            return {"channels": 20, "observables": {"NEW_SIGNAL": 1}}

        monkeypatch.setattr(
            "ultrazohm_dataviewer.live_mapping.read_mapping", read_mapping
        )
        panel.update = replace(
            panel.update,
            attached=True,
            catalog={
                "channels": 20,
                "observables": {"NEW_SIGNAL": 1},
                "sample_period_us": 50.0,
            },
            assignments=({"channel": 1, "name": "NEW_SIGNAL"},),
        )
        directory = save(panel)
        assert requested == [str(tmp_path)]
        assert json.loads((directory / "settings.json").read_text())[
            "initial_channels"
        ] == {"1": "NEW_SIGNAL"}
    finally:
        panel.close()


def test_local_mapping_timeout_preserves_saved_settings(tmp_path, monkeypatch):
    import subprocess

    from ultrazohm_dataviewer.settings import load_workspace_settings

    panel = workspace(tmp_path)
    try:
        directory = save(panel)
        paths = [directory / "settings.json", directory / "live_view.json"]
        before = [path.read_bytes() for path in paths]
        panel._repository_settings = load_workspace_settings(panel.mapping, directory)
        panel.update = replace(
            panel.update, attached=True, assignments=({"channel": 1, "name": "b"},)
        )

        def timeout(repo):
            raise subprocess.TimeoutExpired("channel-mapping", 60)

        monkeypatch.setattr("ultrazohm_dataviewer.live_mapping.read_mapping", timeout)
        panel.save_live_settings()
        assert (
            "Timed out validating the local firmware mapping" in panel.settings_notice
        )
        assert [path.read_bytes() for path in paths] == before
    finally:
        panel.close()
