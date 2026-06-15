"""The pure-python CSV path used when pyarrow is unavailable (web builds)."""

import numpy as np

from uz_dataviewer.core import loader


def test_python_csv_reader_matches_pyarrow(javascope_csv):
    run_arrow = loader.load_file(javascope_csv)
    table = loader._read_csv_python(javascope_csv)
    run_python = loader._table_to_run(table, javascope_csv, run_id=0)

    assert set(run_python.signals) == set(run_arrow.signals)
    np.testing.assert_allclose(run_python.time, run_arrow.time)
    np.testing.assert_allclose(run_python.signals["ch1"], run_arrow.signals["ch1"])


def test_python_csv_reader_handles_gaps(tmp_path):
    path = tmp_path / "gaps.csv"
    path.write_text("time;ch1;\n0.0;1.0;\n0.1;;\n0.2;3.0;\n")
    table = loader._read_csv_python(str(path))
    run = loader._table_to_run(table, str(path), run_id=0)
    assert run.n_samples == 3
    assert np.isnan(run.signals["ch1"][1])
