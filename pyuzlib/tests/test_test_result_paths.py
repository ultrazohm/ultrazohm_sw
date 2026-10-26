from pathlib import Path
import runpy

import pytest

from pyuzlib.docs.test_results import pmsm_swmodel_result_paths
from pyuzlib.docs import test_results


def create_results(root):
    directory = root / "uz/uz_pmsm_swmodel"
    directory.mkdir(parents=True)
    paths = (
        directory / "uz_pmsm_swmodel_results.csv",
        directory / "uz_pmsm_swmodel_config.csv",
    )
    for path in paths:
        path.write_text("example\n", encoding="utf-8")
    return paths


def test_default_directory_is_owned_by_ceedling(tmp_path, monkeypatch):
    monkeypatch.delenv("UZ_TEST_DATA_DIR", raising=False)
    monkeypatch.setattr(test_results, "repo_root_from", lambda _: tmp_path)
    paths = create_results(tmp_path / "vitis/software/Baremetal/build/artifacts/test-data")
    assert pmsm_swmodel_result_paths() == paths


def test_environment_override_works_outside_repository(tmp_path, monkeypatch):
    paths = create_results(tmp_path / "artifacts")
    monkeypatch.setenv("UZ_TEST_DATA_DIR", str(tmp_path / "artifacts"))
    monkeypatch.chdir(tmp_path)
    assert pmsm_swmodel_result_paths() == paths


def test_explicit_directory_overrides_environment(tmp_path, monkeypatch):
    paths = create_results(tmp_path / "explicit")
    monkeypatch.setenv("UZ_TEST_DATA_DIR", str(tmp_path / "not-used"))
    assert pmsm_swmodel_result_paths(tmp_path / "explicit") == paths


def test_relative_override_is_relative_to_working_directory(tmp_path, monkeypatch):
    paths = create_results(tmp_path / "relative")
    monkeypatch.chdir(tmp_path)
    monkeypatch.setenv("UZ_TEST_DATA_DIR", "relative")
    assert pmsm_swmodel_result_paths() == paths


def test_missing_results_are_actionable_and_do_not_create_directories(tmp_path):
    root = tmp_path / "missing"
    with pytest.raises(FileNotFoundError, match="--mixin=config/csv_export.yml") as error:
        pmsm_swmodel_result_paths(root)
    assert "uz_pmsm_swmodel_results.csv" in str(error.value)
    assert "uz_pmsm_swmodel_config.csv" in str(error.value)
    assert "CEEDLING_GLOBAL_CSV_EXPORT" in str(error.value)
    assert not root.exists()


def test_missing_config_is_not_silently_ignored(tmp_path):
    paths = create_results(tmp_path)
    paths[1].unlink()
    with pytest.raises(FileNotFoundError, match="uz_pmsm_swmodel_config.csv"):
        pmsm_swmodel_result_paths(tmp_path)


def test_reading_paths_does_not_write_files(tmp_path, monkeypatch):
    paths = create_results(tmp_path)

    def fail(*args, **kwargs):
        pytest.fail("Plot path resolution attempted a filesystem write")

    monkeypatch.setattr(Path, "mkdir", fail)
    monkeypatch.setattr(Path, "write_text", fail)
    monkeypatch.setattr(Path, "write_bytes", fail)
    assert pmsm_swmodel_result_paths(tmp_path) == paths


@pytest.mark.parametrize("suffix", ["", "_interactive", "_bokeh"])
def test_plot_scripts_consume_current_csv_schema(tmp_path, monkeypatch, suffix):
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    monkeypatch.setattr(plt, "show", lambda: None)
    if suffix == "_bokeh":
        plotting = pytest.importorskip("bokeh.plotting")
        monkeypatch.setattr(plotting, "show", lambda *args, **kwargs: None)
    paths = create_results(tmp_path)
    # The exporter names dq struct fields d/q, prefixed with input_/output_.
    paths[0].write_text(
        "time;input_d;input_q;input_omega_mech_1_s;input_load_torque;"
        "output_d;output_q;output_torque_Nm;output_omega_mech_1_s\n"
        "0;1;0.5;0;0;0.1;0.03;0.01;0\n",
        encoding="utf-8",
    )
    monkeypatch.setenv("UZ_TEST_DATA_DIR", str(tmp_path))
    script = (
        test_results.repo_root_from(__file__)
        / "docs/source/software/control/uz_pmsm_swmodel"
        / f"view_pmsm_model_test_results{suffix}.py"
    )
    try:
        namespace = runpy.run_path(str(script))
        assert namespace["CSV_PATH"] == paths[0]
        assert len(namespace["df"]) == 1
    finally:
        plt.close("all")
