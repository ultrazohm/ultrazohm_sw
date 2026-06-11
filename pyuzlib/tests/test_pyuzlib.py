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


def test_pmsm_parameters_load_string_metadata_and_ignore_appended_table(tmp_path):
    csv_path = tmp_path / "machine_parameters.csv"
    csv_path.write_text(
        "parameter,value\n"
        "machine_name,beckhoff_AM8141-0j00-000\n"
        "R_ph_Ohm,0.51\n"
        "Ld_Henry,0.00175\n"
        "Lq_Henry,0.00175\n"
        "Psi_PM_Vs,0.042\n"
        "polePairs,4\n"
        "J_kg_m_squared,0.000108\n"
        "I_max_Ampere,12\n"
        "\n"
        "Inenn,Imax,Udc,nnenn,Ld,Lq,Rs,p,PsiPm,Umax,KPd,KPq,KId,KIq,machine\n"
        "8,12,48,1000,0.00175,0.00175,0.45,4,0.042,27.71,8.75,8.75,2250,2250,M5\n",
        encoding="utf-8",
    )

    parameters = PMSMParameters.from_csv(csv_path)

    assert parameters.additional_parameters["machine_name"] == "beckhoff_AM8141-0j00-000"
    assert parameters.to_c_dict()["Ld_Henry"] == 0.00175


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
