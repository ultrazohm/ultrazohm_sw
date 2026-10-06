from __future__ import annotations

import numpy as np
import pytest

from uz_scope2.capture_log import CaptureLogger, convert_bin, make_column_names

loader = pytest.importorskip("uz_dataviewer.loader")

TIMESTEP = 1e-4  # 10 kHz
COLUMNS = ["current_A", "voltage_V", "speed_rpm"]


def make_block(start: int, m: int) -> np.ndarray:
    """(3, m) float32 block whose values encode channel and absolute index."""
    idx = np.arange(start, start + m, dtype=np.float32)
    return np.stack([idx, idx + 1000.0, idx + 2000.0])


def run_logger(tmp_path, fmt: str, every_n: int = 1):
    logger = CaptureLogger(
        tmp_path,
        fmt,
        COLUMNS,
        TIMESTEP,
        every_n=every_n,
        base_name="testlog",
        autostart=False,
    )
    logger.submit(make_block(0, 100), 0)
    logger.submit(make_block(100, 50), 100)
    return logger, logger.close()


def test_parquet_roundtrip_via_dataviewer_loader(tmp_path):
    logger, path = run_logger(tmp_path, "parquet")
    assert path.suffix == ".parquet"
    assert logger.stats.rows_written == 150

    run = loader.parse_file(str(path))
    assert set(run.signals) == {"current_A", "voltage_V", "speed_rpm"}
    assert run.units["current_A"] == "A"
    assert run.units["voltage_V"] == "V"
    assert run.units["speed_rpm"] == "rpm"
    np.testing.assert_allclose(run.time, np.arange(150) * TIMESTEP)
    assert run.time.dtype == np.float64
    np.testing.assert_array_equal(run.signals["current_A"], np.arange(150, dtype=np.float32))
    np.testing.assert_array_equal(
        run.signals["speed_rpm"], np.arange(150, dtype=np.float32) + 2000.0
    )
    assert run.signals["current_A"].dtype == np.float32


def test_csv_roundtrip_via_dataviewer_loader(tmp_path):
    logger, path = run_logger(tmp_path, "csv")
    assert path.suffix == ".csv"
    header = path.read_text().splitlines()[0]
    assert header.split(",")[0].strip('"') == "time"

    run = loader.parse_file(str(path))
    assert set(run.signals) == {"current_A", "voltage_V", "speed_rpm"}
    np.testing.assert_allclose(run.time, np.arange(150) * TIMESTEP)
    np.testing.assert_allclose(run.signals["voltage_V"], np.arange(150) + 1000.0)


def test_bin_spill_and_convert(tmp_path):
    logger, path = run_logger(tmp_path, "bin")
    assert path.suffix == ".bin"
    assert path.with_suffix(".json").exists()
    assert path.stat().st_size == 150 * 3 * 4

    parquet_path = convert_bin(path)
    run = loader.parse_file(str(parquet_path))
    np.testing.assert_allclose(run.time, np.arange(150) * TIMESTEP)
    np.testing.assert_array_equal(
        run.signals["current_A"], np.arange(150, dtype=np.float32)
    )


def test_every_n_stride_is_phase_stable_across_chunks(tmp_path):
    logger = CaptureLogger(
        tmp_path, "parquet", COLUMNS, TIMESTEP,
        every_n=3, base_name="strided", autostart=False,
    )
    # Chunk boundaries deliberately not multiples of 3.
    logger.submit(make_block(0, 7), 0)     # keeps indices 0, 3, 6
    logger.submit(make_block(7, 8), 7)     # keeps 9, 12
    path = logger.close()
    run = loader.parse_file(str(path))
    np.testing.assert_array_equal(run.signals["current_A"], [0, 3, 6, 9, 12])
    np.testing.assert_allclose(run.time, np.array([0, 3, 6, 9, 12]) * TIMESTEP)


def test_queue_full_drops_and_counts(tmp_path):
    logger = CaptureLogger(
        tmp_path, "parquet", COLUMNS, TIMESTEP,
        base_name="drops", queue_chunks=2, autostart=False,
    )
    logger.submit(make_block(0, 10), 0)
    logger.submit(make_block(10, 10), 10)
    logger.submit(make_block(20, 10), 20)  # queue full -> dropped
    assert logger.stats.chunks_dropped == 1
    assert logger.stats.samples_dropped == 10
    logger.close()
    assert logger.stats.rows_written == 20


def test_submit_after_close_is_ignored(tmp_path):
    logger = CaptureLogger(
        tmp_path, "parquet", COLUMNS, TIMESTEP, base_name="closed", autostart=False
    )
    logger.submit(make_block(0, 5), 0)
    logger.close()
    logger.submit(make_block(5, 5), 5)  # no-op, no exception
    assert logger.stats.rows_written == 5


def test_channel_count_mismatch(tmp_path):
    logger = CaptureLogger(
        tmp_path, "parquet", COLUMNS, TIMESTEP, base_name="bad", autostart=False
    )
    with pytest.raises(ValueError):
        logger.submit(np.zeros((2, 5), dtype=np.float32), 0)
    logger.close()


def test_invalid_format_rejected(tmp_path):
    with pytest.raises(ValueError):
        CaptureLogger(tmp_path, "xlsx", COLUMNS, TIMESTEP)


def test_make_column_names():
    names = make_column_names(
        ["JSO_DUT_I_A_A", "JSO_DUT_V_DC_V", "JSO_DUT_I_A_A", "JSO_lifecheck"]
    )
    assert names == ["DUT_I_A_A", "DUT_V_DC_V", "DUT_I_A_A_ch3", "lifecheck"]
