"""Tests for file loading and channel-name parsing (no GUI required)."""

from __future__ import annotations

import os
import sys
import numpy as np
import pytest
from pathlib import Path


sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.loader import open_file, parse_channel_name
from uz_dataviewer.model import DataRegistry
from uz_dataviewer import loader


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
    run = open_file(str(path)).register(registry)

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
    run = open_file(str(path)).register(registry)
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
    run = open_file(str(path)).register(DataRegistry())
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
        open_file(str(path)).register(DataRegistry())


def test_unsupported_extension(tmp_path):
    path = tmp_path / "data.txt"
    path.write_text("nope")
    with pytest.raises(ValueError):
        open_file(str(path)).register(DataRegistry())


def test_csv_channels_are_float32_time_float64(tmp_path):
    path = tmp_path / "Log_dtypes.csv"
    path.write_text(SAMPLE)
    run = open_file(str(path)).register(DataRegistry())
    assert run.time.dtype == np.float64
    assert all(sig.y.dtype == np.float32 for sig in run.signals.values())


def test_csv_size_guard_refuses_with_guidance(tmp_path, monkeypatch):
    from uz_dataviewer import loader

    path = tmp_path / "Log_big.csv"
    path.write_text(SAMPLE)
    # A tiny file trips the guard once the budget is lowered below its footprint.
    monkeypatch.setattr(loader, "MAX_CSV_NUMERIC_BYTES", 1)
    with pytest.raises(ValueError) as exc:
        open_file(str(path)).register(DataRegistry())
    assert "convert(" in str(exc.value)


def test_convert_csv_to_parquet_round_trips(tmp_path):
    from uz_dataviewer.loader import convert_csv_to_parquet

    csv_path = tmp_path / "Log_conv.csv"
    csv_path.write_text(SAMPLE)

    # Loading the CSV directly is the reference.
    ref = open_file(str(csv_path)).register(DataRegistry())

    dst = convert_csv_to_parquet(str(csv_path))
    assert dst.endswith(".parquet") and os.path.exists(dst)
    via_parquet = open_file(dst).register(DataRegistry())

    assert set(via_parquet.signals) == set(ref.signals)
    np.testing.assert_allclose(via_parquet.time, ref.time)
    for name, sig in ref.signals.items():
        assert via_parquet.signals[name].unit == sig.unit
        np.testing.assert_allclose(via_parquet.signals[name].y, sig.y, rtol=1e-5)


def _javascope_csv(n: int) -> str:
    """A JavaScope-style ``;``-separated CSV (trailing ``;`` -> empty column) with n rows."""
    t = np.linspace(0.0, 1.0, n)
    ia = np.sin(np.linspace(0.0, 10.0, n))
    rpm = 100.0 + np.cos(np.linspace(0.0, 10.0, n))
    lines = ["time;CH8=8)ia;CH15=15)Speed_rpm;"]
    lines += [f"{t[i]:.6f};{ia[i]:.6f};{rpm[i]:.6f};" for i in range(n)]
    return "\n".join(lines) + "\n"


def test_csv_streaming_growth_preserves_samples(tmp_path, monkeypatch):
    from uz_dataviewer import loader

    n = 2500
    path = tmp_path / "Log_stream.csv"
    path.write_text(_javascope_csv(n))

    baseline = open_file(str(path)).register(DataRegistry())

    # Seed a deliberately low row estimate so the preallocated
    # arrays must grow at least once (exercises _grow).
    monkeypatch.setattr(loader, "_estimate_csv_rows_and_bytes", lambda p, c: (10, 10))
    streamed = open_file(str(path)).register(DataRegistry())

    assert streamed.n_rows == n == baseline.n_rows
    # Trailing ';' empty column is dropped -- only the three named signals remain.
    assert set(streamed.signals) == {"ia", "Speed_rpm"} == set(baseline.signals)
    assert streamed.signals["Speed_rpm"].unit == "rpm"
    np.testing.assert_allclose(streamed.time, baseline.time)
    for name in baseline.signals:
        np.testing.assert_array_equal(streamed.signals[name].y, baseline.signals[name].y)
        assert streamed.signals[name].y.dtype == np.float32
    assert streamed.time.dtype == np.float64


def test_csv_streaming_rejects_decreasing_time(tmp_path):
    path = tmp_path / "Log_back_stream.csv"
    path.write_text("time;CH8=8)ia;\n0.0;1.0;\n0.2;2.0;\n0.1;3.0;\n")
    with pytest.raises(ValueError, match="non-decreasing"):
        open_file(str(path)).register(DataRegistry())


def test_parquet_streaming_preserves_all_row_groups(tmp_path):
    import pandas as pd


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

    streamed = open_file(str(path)).register(DataRegistry())
    assert streamed.n_rows == n
    np.testing.assert_array_equal(streamed.time, df['time'].to_numpy())
    for name in ('ia', 'ib'):
        np.testing.assert_array_equal(streamed.signals[name].y, df[name].to_numpy())


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy'])
@pytest.mark.parametrize('extension', ['csv', 'parquet'])
def test_colliding_channels_preserve_raw_columns(tmp_path, states, backend, mode, extension):
    import pyarrow as pa
    import pyarrow.parquet as pq
    path = tmp_path / f'collision.{extension}'
    names = ['time', 'CH1=1)a', 'a', 'a [2]', 'CH2=2)time']
    arrays = [np.array([i, i + 1.0]) for i in (0, 10, 20, 30, 40)]
    if extension == 'csv':
        path.write_text(';'.join(names) + '\n' + '\n'.join((';'.join(map(str, row)) for row in zip(*arrays))))
    else:
        pq.write_table(pa.table(dict(zip(names, arrays))), path)
    run = open_file(str(path), mode, backend=backend).register(states().registry)
    assert len(run.signals) == 4 and 'time' not in run.signals
    _, values = run.read_window(list(run.signals), 0, 1)
    for actual, expected in zip(values.values(), arrays[1:]):
        np.testing.assert_array_equal(actual, expected)


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy'])
def test_native_quoted_csv_headers(tmp_path, states, backend, mode):
    path = tmp_path / 'quoted.csv'
    path.write_text('time;"a,b,c";\n0;10;\n1;20;\n')
    run = open_file(str(path), mode, backend=backend).register(states().registry)
    assert list(run.signals) == ['a,b,c']
    np.testing.assert_array_equal(run.read_window(['a,b,c'], 0, 1)[1]['a,b,c'], [10, 20])


@pytest.mark.parametrize('backend', ['pyarrow', 'polars'])
@pytest.mark.parametrize('mode', ['memory', 'lazy', 'converted'])
def test_csv_missing_values_have_one_policy(tmp_path, backend, mode):
    from uz_dataviewer.csv_policy import NULL_VALUES
    import csv
    path = tmp_path / 'missing.csv'
    with path.open('w', newline='') as fh:
        writer = csv.writer(fh)
        writer.writerow(['time', 'y'])
        writer.writerows(enumerate(NULL_VALUES))
    if mode == 'converted':
        path = Path(loader.convert_csv_to_parquet(str(path), backend=backend))
    run = loader.open_file(str(path), 'lazy' if mode == 'lazy' else 'memory', backend=backend).register(DataRegistry())
    t, values = run.read_window(['y'], 0, len(NULL_VALUES))
    assert len(t) == len(NULL_VALUES)
    assert np.isnan(values['y']).all()
