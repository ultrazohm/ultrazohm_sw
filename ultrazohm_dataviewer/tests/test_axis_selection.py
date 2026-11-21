"""Import meaning survives conversion, caching, sessions and API boundaries."""

import time

import numpy as np
import pytest

from ultrazohm_dataviewer.api import read
from ultrazohm_dataviewer.axis import AxisSelectionRequired
from ultrazohm_dataviewer.loader import convert_csv_to_parquet, open_file
from ultrazohm_dataviewer.session import apply_dict, to_dict


@pytest.mark.parametrize("backend", ["pyarrow", "polars"])
@pytest.mark.parametrize(
    "mode,cache", [("memory", False), ("lazy", False), ("lazy", True)]
)
@pytest.mark.parametrize("extension", ["csv", "parquet"])
def test_spectrum_roundtrip(tmp_path, states, backend, mode, cache, extension):
    csv = tmp_path / "fft.csv"
    csv.write_text("frequency,out\n0,1\n125,2\n250,3\n")
    path = (
        str(csv)
        if extension == "csv"
        else convert_csv_to_parquet(str(csv), backend=backend)
    )
    state = states()
    state.backend, state.loading_mode, state.disk_cache = backend, mode, cache
    run = state.load_sync(path)
    assert run.axis_domain == "frequency"
    assert run.axis_column == "frequency"
    restored = states()
    apply_dict(restored, to_dict(state))
    assert restored.registry.runs[0].axis_domain == "frequency"
    with pytest.raises(ValueError):
        run.set_time_origin(0)


@pytest.mark.parametrize("backend", ["pyarrow", "polars"])
@pytest.mark.parametrize(
    "mode,cache", [("memory", False), ("lazy", False), ("lazy", True)]
)
def test_explicit_axis_and_conversion(tmp_path, states, backend, mode, cache):
    csv = tmp_path / "custom.csv"
    csv.write_text("sample,seconds,value\n1,1700000000.001,3\n2,1700000000.002,4\n")
    state = states()
    state.backend, state.loading_mode, state.disk_cache = backend, mode, cache
    with pytest.raises(AxisSelectionRequired):
        open_file(str(csv), mode, backend=backend, disk_cache=cache)
    run = state.load_sync(str(csv), axis_column="seconds", axis_domain="time")
    assert run is not None
    np.testing.assert_array_equal(
        np.asarray(run.time), [1700000000.001, 1700000000.002]
    )
    snapshot = to_dict(state)
    restored = states()
    apply_dict(restored, snapshot)
    assert restored.registry.runs[0].axis_column == "seconds"
    path = convert_csv_to_parquet(str(csv), backend=backend, axis_column="seconds")
    data = read(path, backend=backend)
    assert data.axis_column == "seconds"
    np.testing.assert_array_equal(data.time, [1700000000.001, 1700000000.002])
    assert "sample" in data.signals


def test_gui_selection_captures_request_and_cancel(tmp_path, app_state):
    path = tmp_path / "unknown.csv"
    path.write_text("hz,amplitude\n0,1\n1,2\n")
    app_state.request_load(str(path))

    def finish():
        deadline = time.monotonic() + 10
        while app_state.services.pending:
            app_state.poll_pending_loads()
            assert time.monotonic() < deadline
            time.sleep(0.001)

    finish()
    assert app_state.is_loading
    app_state.backend = "pyarrow"
    app_state.resolve_axis("hz", "frequency")
    finish()
    assert app_state.registry.runs[0].axis_domain == "frequency"
    app_state.request_load(str(path))
    finish()
    app_state.resolve_axis()
    assert not app_state.is_loading
    assert len(app_state.registry.runs) == 1


def test_axis_changes_do_not_share_conversion_cache(tmp_path, states):
    csv = tmp_path / "custom.csv"
    csv.write_text("a,b,c\n1,10,4\n2,20,5\n")
    state = states()
    state.loading_mode, state.disk_cache = "lazy", True
    first = state.load_sync(str(csv), axis_column="a")
    second = state.load_sync(str(csv), axis_column="b")
    assert first.source.path != second.source.path


def test_old_session_keeps_first_column_selection(tmp_path, states):
    csv = tmp_path / "custom.csv"
    csv.write_text("stamp,value\n0,1\n1,2\n")
    state = states()
    state.load_sync(str(csv), axis_column="stamp")
    snapshot = to_dict(state)
    del snapshot["runs"][0]["axis_column"]
    del snapshot["runs"][0]["axis_domain"]
    restored = states()
    apply_dict(restored, snapshot)
    assert restored.registry.runs[0].axis_column == "stamp"


def test_control_load_axis_and_failed_normalization(control_session, tmp_path):
    state, client, workers, pump = control_session
    path = tmp_path / "custom.csv"
    path.write_text("hz,value\n0,1\n1,2\n")
    job = workers.submit(
        client.load, str(path), axis_column="hz", axis_domain="frequency"
    )
    pump(job.done)
    assert job.result().id == state.registry.runs[0].id
    listing = workers.submit(client.list_runs)
    pump(listing.done)
    assert listing.result()[0]["axis_domain"] == "frequency"
    assert listing.result()[0]["axis_column"] == "hz"
    job = workers.submit(
        client.load, str(path), start=0, axis_column="hz", axis_domain="frequency"
    )
    pump(job.done)
    with pytest.raises(Exception, match="time-domain"):
        job.result()
    assert len(state.registry.runs) == 1


def test_cli_axis_options():
    from ultrazohm_dataviewer.cli import parser

    for flag in ("--axis-column", "--axis_column"):
        args = parser().parse_args(
            ["load", "file.csv", flag, "hz", "--axis-domain", "frequency"]
        )
        assert args.axis_column == "hz"
        assert args.axis_domain == "frequency"


def test_axis_dialog_renders(gui_frame, app_state, tmp_path):
    from types import SimpleNamespace

    from ultrazohm_dataviewer.app import DataViewerApp
    from ultrazohm_dataviewer.state import LoadRequest

    app_state.services.axis_requests.append(
        (
            LoadRequest(str(tmp_path / "custom.csv"), "lazy", "polars", False),
            ("hz", "value"),
            None,
        )
    )
    app = object.__new__(DataViewerApp)
    app.state = app_state
    gui_frame(SimpleNamespace(render=lambda state: app._show_axis_dialog()), app_state)


def test_control_ambiguous_axis_returns_actionable_error(control_session, tmp_path):
    from ultrazohm_dataviewer.client import ViewerError

    state, client, workers, pump = control_session
    path = tmp_path / "unknown.csv"
    path.write_text("stamp,value\n0,1\n1,2\n")
    job = workers.submit(client.load, str(path))
    pump(job.done)
    with pytest.raises(ViewerError) as error:
        job.result()
    assert error.value.code == "axis_selection_required"
    assert "stamp" in str(error.value)
    assert not state.registry.runs


def test_old_frequency_named_session_preserves_time_normalization(tmp_path, states):
    csv = tmp_path / "legacy.csv"
    csv.write_text("frequency,value\n10,1\n20,2\n")
    state = states()
    run = state.load_sync(str(csv), axis_domain="time")
    run.set_time_origin(0)
    snapshot = to_dict(state)
    del snapshot["runs"][0]["axis_column"]
    del snapshot["runs"][0]["axis_domain"]
    restored = states()
    apply_dict(restored, snapshot)
    run = restored.registry.runs[0]
    assert run.axis_domain == "time"
    np.testing.assert_array_equal(np.asarray(run.time), [0, 10])


def test_custom_axis_does_not_overwrite_frequency_signal(tmp_path, states):
    from ultrazohm_dataviewer.session import export_data

    csv = tmp_path / "custom.csv"
    csv.write_text("hz,frequency\n0,10\n1,20\n")
    data = read(csv, axis_column="hz", axis_domain="frequency")
    frame = data.to_dataframe()
    assert list(frame.columns) == ["hz", "frequency"]
    np.testing.assert_array_equal(frame["hz"], [0, 1])
    state = states()
    run = state.load_sync(str(csv), axis_column="hz", axis_domain="frequency")
    state.cells[0].add((run.id, "frequency"))
    destination = tmp_path / "export.csv"
    with pytest.raises(ValueError, match="conflicts"):
        export_data(state, 0, str(destination))
    assert not destination.exists()
