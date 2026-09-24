import pandas as pd
import pytest

from pyuzlib._repo_paths import repo_root_from
from smoke_pmsm_plot import check_and_render


@pytest.fixture
def exported_results(tmp_path, monkeypatch):
    directory = tmp_path / "test-data/uz/uz_pmsm_swmodel"
    directory.mkdir(parents=True)
    results = pd.DataFrame({
        "time": [0.0, 0.01],
        "input_d": [1.0, 1.0],
        "input_q": [0.5, 0.5],
        "input_omega_mech_1_s": [0.0, 0.0],
        "input_load_torque": [0.0, 0.0],
        "output_d": [0.1, 0.2],
        "output_q": [0.03, 0.06],
        "output_torque_Nm": [0.01, 0.02],
        "output_omega_mech_1_s": [0.0, 0.0],
    })
    config = pd.DataFrame({"output_sample_time": [0.01]})
    results_path = directory / "uz_pmsm_swmodel_results.csv"
    config_path = directory / "uz_pmsm_swmodel_config.csv"
    results.to_csv(results_path, sep=";", index=False)
    config.to_csv(config_path, sep=";", index=False)
    monkeypatch.setenv("UZ_TEST_DATA_DIR", str(tmp_path / "test-data"))
    return results_path, config_path


def render(tmp_path):
    check_and_render(
        tmp_path / "test-data",
        repo_root_from(__file__)
        / "docs/source/software/control/uz_pmsm_swmodel/view_pmsm_model_test_results.py",
        tmp_path / "plot.png",
    )


def test_smoke_validation_renders_real_plot(tmp_path, exported_results):
    render(tmp_path)
    assert (tmp_path / "plot.png").read_bytes().startswith(b"\x89PNG\r\n\x1a\n")


@pytest.mark.parametrize("problem, message", [
    ("missing_column", "lack plot columns"),
    ("nonfinite", "non-finite"),
    ("timestamps", "timestamps"),
    ("empty", "at least two"),
    ("missing_sample_time", "lacks output_sample_time"),
])
def test_smoke_validation_rejects_bad_export(tmp_path, exported_results, problem, message):
    results_path, config_path = exported_results
    results = pd.read_csv(results_path, sep=";")
    if problem == "missing_column":
        results = results.drop(columns="output_d")
    elif problem == "nonfinite":
        results.loc[0, "output_d"] = float("inf")
    elif problem == "timestamps":
        results.loc[1, "time"] = 0.02
    elif problem == "empty":
        results = results.iloc[:0]
    else:
        pd.DataFrame({"wrong_column": [0.01]}).to_csv(config_path, sep=";", index=False)
    results.to_csv(results_path, sep=";", index=False)
    with pytest.raises(ValueError, match=message):
        render(tmp_path)
    assert not (tmp_path / "plot.png").exists()


def test_smoke_validation_cannot_use_missing_exports(tmp_path):
    with pytest.raises(FileNotFoundError, match="Missing PMSM test artifacts"):
        render(tmp_path)
    assert not (tmp_path / "test-data").exists()


def test_smoke_plot_must_use_the_validated_directory(tmp_path, exported_results, monkeypatch):
    other = tmp_path / "other/uz/uz_pmsm_swmodel"
    other.mkdir(parents=True)
    for path in exported_results:
        (other / path.name).write_bytes(path.read_bytes())
    monkeypatch.setenv("UZ_TEST_DATA_DIR", str(tmp_path / "other"))
    with pytest.raises(ValueError, match="fresh artifacts"):
        render(tmp_path)
