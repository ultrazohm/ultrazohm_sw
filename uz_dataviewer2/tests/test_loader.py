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


def test_unsupported_extension(tmp_path):
    path = tmp_path / "data.txt"
    path.write_text("nope")
    with pytest.raises(ValueError):
        load_file(str(path), DataRegistry())
