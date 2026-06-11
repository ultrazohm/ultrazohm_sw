import pyuzlib
from pyuzlib.pmsm import FluxMap, PMSM, PMSMParameters


def test_pyuzlib_has_version():
    assert pyuzlib.__version__


def test_pyuzlib_exposes_docs_pmsm_helpers():
    assert pyuzlib.docs.pmsm.plot_flux_map
    assert pyuzlib.docs.pmsm.plot_flux_map_plotly


def test_pyuzlib_exposes_pmsm_api():
    assert pyuzlib.pmsm.PMSM
    assert pyuzlib.pmsm.PMSMParameters
    assert pyuzlib.pmsm.FluxMap


def test_pmsm_parameters_load_c_values_and_additional_values():
    parameters = PMSMParameters.from_csv(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/machine_parameters.csv"
    )

    assert parameters.R_ph_Ohm == 0.51
    assert parameters.Ld_Henry == 0.002
    assert parameters.additional_parameters["I_rated_Ampere"] == 8.0
    assert parameters.to_c_dict()["I_max_Ampere"] == 12.0


def test_flux_map_loads_default_columns_as_canonical_table():
    flux_map = FluxMap.from_csv(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv"
    )

    assert list(flux_map.data.columns) == ["i_d_A", "i_q_A", "psi_d_Vs", "psi_q_Vs"]
    assert flux_map.psi_d.shape == (3, 3)
    assert flux_map.psi_q.shape == (3, 3)


def test_flux_map_loads_with_explicit_column_mapping(tmp_path):
    csv_path = tmp_path / "odd_names.csv"
    csv_path.write_text(
        "id,iq,psid,psiq\n"
        "-1,0,0.01,0.02\n"
        "0,0,0.03,0.04\n",
        encoding="utf-8",
    )

    flux_map = FluxMap.from_csv(
        csv_path,
        i_d_col="id",
        i_q_col="iq",
        psi_d_col="psid",
        psi_q_col="psiq",
    )

    assert list(flux_map.data.columns) == ["i_d_A", "i_q_A", "psi_d_Vs", "psi_q_Vs"]
    assert flux_map.data["psi_d_Vs"].tolist() == [0.01, 0.03]


def test_pmsm_object_loads_flux_map_and_fits_linear_model():
    motor = PMSM()
    motor.load_flux_map_csv(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv"
    )
    fit = motor.fit_linear_flux_model()

    assert "linear_no_saturation" in motor.results
    assert abs(fit.loc[0, "L_dd"] - 0.002) < 1e-12
    assert abs(fit.loc[0, "L_qq"] - 0.003) < 1e-12


def test_docs_helper_uses_new_linear_fit_implementation():
    fit = pyuzlib.docs.pmsm.L_dd_L_qq_from_flux_map_assuming_no_saturation(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv"
    )

    assert abs(fit.loc[0, "L_dd"] - 0.002) < 1e-12
    assert abs(fit.loc[0, "L_qq"] - 0.003) < 1e-12
