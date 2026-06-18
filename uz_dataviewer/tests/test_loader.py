"""Tests for file loading and channel-name parsing (no GUI required)."""

from __future__ import annotations

import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.loader import load_file, parse_channel_name  # noqa: E402
from uz_dataviewer.model import DataRegistry  # noqa: E402

SAMPLE = (
    "time;CH1=1)ISR_ExecTime_us;CH8=8)ia;CH15=15)Speed_rpm;\n"
    "0.0;15.8;0.1;100.0;\n"
    "0.1;15.9;0.2;101.0;\n"
    "0.2;16.0;0.3;102.0;\n"
)


def test_parse_channel_name():
    assert parse_channel_name("CH8=8)ia") == ("ia", "")
    assert parse_channel_name("CH15=15)Speed_rpm") == ("Speed_rpm", "rpm")
    assert parse_channel_name("CH1=1)ISR_ExecTime_us") == ("ISR_ExecTime_us", "us")
    assert parse_channel_name("plain") == ("plain", "")


def test_load_csv(tmp_path):
    path = tmp_path / "Log_test.csv"
    path.write_text(SAMPLE)
    registry = DataRegistry()
    run = load_file(str(path), registry)

    assert run.n_rows == 3
    assert set(run.signals) == {"ISR_ExecTime_us", "ia", "Speed_rpm"}
    assert run.signals["Speed_rpm"].unit == "rpm"
    np.testing.assert_allclose(run.time, [0.0, 0.1, 0.2])
    np.testing.assert_allclose(run.signals["ia"].y, [0.1, 0.2, 0.3], rtol=1e-5)
    assert run.signals["ia"].y.dtype == np.float32


def test_load_parquet(tmp_path):
    import pandas as pd

    df = pd.DataFrame({"time": [0.0, 1.0, 2.0], "ia": [1.0, 2.0, 3.0]})
    path = tmp_path / "Log_test.parquet"
    df.to_parquet(path)

    registry = DataRegistry()
    run = load_file(str(path), registry)
    assert run.n_rows == 3
    assert "ia" in run.signals


def test_sniff_delimiter(tmp_path):
    from uz_dataviewer.loader import _sniff_delimiter

    semi = tmp_path / "javascope.csv"
    semi.write_text("time;CH8=8)ia;CH9=9)ib;\n0.0;1.0;2.0;\n")
    comma = tmp_path / "exported.csv"
    comma.write_text("time,ia,ib\n0.0,1.0,2.0\n")
    assert _sniff_delimiter(str(semi)) == ";"
    assert _sniff_delimiter(str(comma)) == ","


def test_load_comma_separated_csv(tmp_path):
    path = tmp_path / "comma.csv"
    path.write_text("time,ia,ib\n0.0,0.1,1.0\n0.1,0.2,1.1\n")
    run = load_file(str(path), DataRegistry())
    assert run.n_rows == 2
    assert set(run.signals) == {"ia", "ib"}


def test_validate_time_axis_rejects_bad_axes():
    from uz_dataviewer.loader import validate_time_axis

    with pytest.raises(ValueError, match="empty"):
        validate_time_axis(np.array([], dtype=np.float64), "x.csv")
    with pytest.raises(ValueError, match="non-finite"):
        validate_time_axis(np.array([0.0, np.nan, 1.0]), "x.csv")
    with pytest.raises(ValueError, match="non-decreasing"):
        validate_time_axis(np.array([0.0, 0.2, 0.1]), "x.csv")
    validate_time_axis(np.array([0.0, 0.1, 0.1, 0.2]), "x.csv")  # duplicates allowed


def test_load_rejects_decreasing_time(tmp_path):
    path = tmp_path / "Log_back.csv"
    path.write_text("time;CH8=8)ia;\n0.0;1.0;\n0.2;2.0;\n0.1;3.0;\n")
    with pytest.raises(ValueError, match="non-decreasing"):
        load_file(str(path), DataRegistry())


def test_unsupported_extension(tmp_path):
    path = tmp_path / "data.txt"
    path.write_text("nope")
    with pytest.raises(ValueError):
        load_file(str(path), DataRegistry())


def test_csv_channels_are_float32_time_float64(tmp_path):
    path = tmp_path / "Log_dtypes.csv"
    path.write_text(SAMPLE)
    run = load_file(str(path), DataRegistry())
    assert run.time.dtype == np.float64
    assert all(sig.y.dtype == np.float32 for sig in run.signals.values())


def test_csv_size_guard_refuses_with_guidance(tmp_path, monkeypatch):
    from uz_dataviewer import loader

    path = tmp_path / "Log_big.csv"
    path.write_text(SAMPLE)
    # A tiny file trips the guard once the budget is lowered below its footprint.
    monkeypatch.setattr(loader, "MAX_CSV_NUMERIC_BYTES", 1)
    with pytest.raises(ValueError) as exc:
        load_file(str(path), DataRegistry())
    assert "convert(" in str(exc.value)


def test_convert_csv_to_parquet_round_trips(tmp_path):
    from uz_dataviewer.loader import convert_csv_to_parquet

    csv_path = tmp_path / "Log_conv.csv"
    csv_path.write_text(SAMPLE)

    # Loading the CSV directly is the reference.
    ref = load_file(str(csv_path), DataRegistry())

    dst = convert_csv_to_parquet(str(csv_path))
    assert dst.endswith(".parquet") and os.path.exists(dst)
    via_parquet = load_file(dst, DataRegistry())

    assert set(via_parquet.signals) == set(ref.signals)
    np.testing.assert_allclose(via_parquet.time, ref.time)
    for name, sig in ref.signals.items():
        assert via_parquet.signals[name].unit == sig.unit
        np.testing.assert_allclose(via_parquet.signals[name].y, sig.y, rtol=1e-5)


def test_parquet_streaming_matches_bulk(tmp_path, monkeypatch):
    import pandas as pd

    from uz_dataviewer import loader

    n = 5000
    df = pd.DataFrame(
        {
            "time": np.linspace(0.0, 1.0, n),
            "ia": np.sin(np.linspace(0.0, 10.0, n)).astype(np.float32),
            "ib": np.cos(np.linspace(0.0, 10.0, n)).astype(np.float32),
        }
    )
    path = tmp_path / "Log_stream.parquet"
    # Many small row groups so iter_batches yields multiple batches.
    df.to_parquet(path, row_group_size=512)

    bulk = load_file(str(path), DataRegistry())  # n < threshold -> bulk path

    # Force the streaming path and confirm it fills exactly n_rows and agrees.
    monkeypatch.setattr(loader, "PARQUET_STREAM_MIN_ROWS", 0)
    streamed = load_file(str(path), DataRegistry())

    assert streamed.n_rows == n == bulk.n_rows
    np.testing.assert_allclose(streamed.time, bulk.time)
    for name in bulk.signals:
        np.testing.assert_array_equal(streamed.signals[name].y, bulk.signals[name].y)
