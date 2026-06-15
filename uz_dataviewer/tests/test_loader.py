import numpy as np
import pytest

from uz_dataviewer.core import loader


def test_load_csv(javascope_csv):
    run = loader.load_file(javascope_csv)
    assert run.has_real_time
    assert set(run.signals) == {"ch1", "ch2"}
    assert run.n_samples == 1000
    assert run.time[0] == pytest.approx(0.0)
    np.testing.assert_allclose(run.signals["ch2"], 2 * run.signals["ch1"], rtol=1e-6)


def test_csv_trailing_separator_column_is_dropped(javascope_csv):
    run = loader.load_file(javascope_csv)
    assert "" not in run.signals
    assert all(name.strip() for name in run.signals)


def test_load_parquet(javascope_parquet):
    run = loader.load_file(javascope_parquet)
    assert set(run.signals) == {"ch1", "ch2"}
    assert run.n_samples == 10_000
    assert run.sample_rate == pytest.approx(10_000, rel=1e-3)


def test_csv_and_parquet_agree(javascope_csv, javascope_parquet):
    run_csv = loader.load_file(javascope_csv)
    run_parquet = loader.load_file(javascope_parquet)
    # The CSV fixture stores 9 decimals, so allow that as absolute tolerance.
    np.testing.assert_allclose(
        run_csv.signals["ch1"], run_parquet.signals["ch1"][:1000], rtol=1e-6, atol=1e-9
    )


def test_unsupported_extension(tmp_path):
    path = tmp_path / "log.txt"
    path.write_text("nope")
    with pytest.raises(loader.LoaderError, match="Unsupported file type"):
        loader.load_file(str(path))


def test_missing_time_column(tmp_path):
    path = tmp_path / "no_time.csv"
    path.write_text("a;b;\n1;2;\n3;4;\n")
    run = loader.load_file(str(path))
    assert not run.has_real_time
    assert run.warnings
    np.testing.assert_array_equal(run.time, [0.0, 1.0])


def test_non_numeric_column_skipped(tmp_path):
    path = tmp_path / "mixed.csv"
    path.write_text("time;ch1;note;\n0.0;1.0;hello;\n0.1;2.0;world;\n")
    run = loader.load_file(str(path))
    assert "note" not in run.signals
    assert any("note" in w for w in run.warnings)


def test_empty_file_raises(tmp_path):
    path = tmp_path / "empty.csv"
    path.write_text("time;ch1;\n")
    with pytest.raises(loader.LoaderError):
        loader.load_file(str(path))
