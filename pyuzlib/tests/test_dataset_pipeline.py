import json

import pandas as pd
import pytest

from pyuzlib import dataset_pipeline


def test_prepare_and_check_dataset_from_source(tmp_path, capsys):
    dataset = tmp_path / "motor" / "measurement"
    dataset.mkdir(parents=True)
    (dataset / "flux_map_source.csv").write_text(
        "Id,Iq,PsiD,PsiQ\n"
        "1,1,3,2\n0,1,1,2\n1,0,3,0\n0,0,1,0\n",
        encoding="utf-8",
    )
    (dataset / "dataset.json").write_text(
        json.dumps({
            "columns": {"i_d": "Id", "i_q": "Iq", "psi_d": "PsiD", "psi_q": "PsiQ"},
            "edge_order": 2,
        }),
        encoding="utf-8",
    )

    args = ["--uz-pmsm-dir", str(tmp_path)]
    assert dataset_pipeline.main(args) == 0
    flux_path = dataset / "flux_map.csv"
    inductance_path = dataset / "differential_inductances.csv"
    flux = pd.read_csv(flux_path)
    inductance = pd.read_csv(inductance_path)
    assert list(flux.columns) == ["operating_point", "i_d_A", "i_q_A", "psi_d_Vs", "psi_q_Vs"]
    assert flux["operating_point"].tolist() == [0, 1, 2, 3]
    assert flux["i_d_A"].tolist() == [0, 1, 0, 1]
    assert inductance["L_dd_H"].tolist() == [2, 2, 2, 2]
    assert inductance["L_qq_H"].tolist() == [2, 2, 2, 2]
    assert dataset_pipeline.main(["--check", *args]) == 0

    before = flux_path.read_bytes()
    (dataset / "flux_map_source.csv").write_text(
        (dataset / "flux_map_source.csv").read_text(encoding="utf-8").replace("1,0,3,0", "1,0,4,0"),
        encoding="utf-8",
    )
    capsys.readouterr()
    assert dataset_pipeline.main(["--check", *args]) == 1
    assert "Stale generated artifact" in capsys.readouterr().out
    assert flux_path.read_bytes() == before


def test_source_and_recipe_are_both_required(tmp_path):
    dataset = tmp_path / "motor" / "measurement"
    dataset.mkdir(parents=True)
    (dataset / "flux_map_source.csv").write_text("i_d_A,i_q_A,psi_d_Vs,psi_q_Vs\n", encoding="utf-8")
    with pytest.raises(ValueError, match="missing dataset.json"):
        dataset_pipeline.collect_dataset_outputs(tmp_path)
    (dataset / "dataset.json").write_text(
        json.dumps({
            "columns": {"i_d": "i_d_A", "i_q": "i_q_A", "psi_d": "psi_d_Vs", "psi_q": "psi_q_Vs"},
            "edge_order": 2,
        }),
        encoding="utf-8",
    )
    (dataset / "flux_map_source.csv").unlink()
    with pytest.raises(FileNotFoundError, match="flux_map_source.csv"):
        dataset_pipeline.collect_dataset_outputs(tmp_path)


def test_recipe_cannot_disable_differential_generation(tmp_path):
    dataset = tmp_path / "motor" / "measurement"
    dataset.mkdir(parents=True)
    (dataset / "dataset.json").write_text(
        json.dumps({"differential_inductances": None}), encoding="utf-8"
    )
    with pytest.raises(ValueError, match="columns and edge_order are required"):
        dataset_pipeline.collect_dataset_outputs(tmp_path)


@pytest.mark.parametrize("recipe", [
    {"columns": {}, "edge_order": 2},
    {"columns": {"i_d": "i_d_A", "i_q": "i_q_A", "psi_d": "psi_d_Vs"}, "edge_order": 2},
    {"columns": {"i_d": "i_d_A", "i_q": "i_q_A", "psi_d": "psi_d_Vs", "psi_q": "psi_q_Vs"}},
])
def test_partial_recipes_are_rejected(tmp_path, recipe):
    dataset = tmp_path / "motor" / "measurement"
    dataset.mkdir(parents=True)
    (dataset / "dataset.json").write_text(json.dumps(recipe), encoding="utf-8")
    with pytest.raises(ValueError, match="columns and edge_order are required|columns must map"):
        dataset_pipeline.collect_dataset_outputs(tmp_path)
