import pyuzlib
import numpy as np
from pyuzlib.pmsm import (
    DifferentialInductanceMap,
    FluxMap,
    OperationArea,
    PMSM,
    PMSMParameters,
)


def test_pyuzlib_has_version():
    assert pyuzlib.__version__


def test_pyuzlib_exposes_docs_pmsm_helpers():
    assert pyuzlib.docs.pmsm.plot_flux_map
    assert pyuzlib.docs.pmsm.plot_flux_map_plotly
    assert pyuzlib.docs.pmsm.plot_linear_flux_model_comparison
    assert pyuzlib.docs.pmsm.plot_differential_inductances
    assert pyuzlib.docs.pmsm.plot_operation_area
    assert pyuzlib.docs.pmsm.plot_max_torque_curve


def test_pyuzlib_exposes_pmsm_api():
    assert pyuzlib.pmsm.PMSM
    assert pyuzlib.pmsm.PMSMParameters
    assert pyuzlib.pmsm.FluxMap
    assert pyuzlib.pmsm.DifferentialInductanceMap
    assert pyuzlib.pmsm.OperationArea


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


def test_pmsm_object_compares_linear_model_to_flux_map_samples():
    motor = PMSM()
    motor.load_flux_map_csv(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv"
    )
    comparison = motor.compare_linear_flux_model()

    assert "linear_no_saturation_comparison" in motor.results
    assert "psi_d_linear_Vs" in comparison
    assert "psi_q_linear_Vs" in comparison
    assert "psi_d_error_Vs" in comparison
    assert "psi_q_error_Vs" in comparison
    assert comparison["psi_d_error_Vs"].abs().max() < 1e-12
    assert comparison["psi_q_error_Vs"].abs().max() < 1e-12


def test_pmsm_object_calculates_and_exports_differential_inductance_maps(tmp_path):
    motor = PMSM()
    motor.load_flux_map_csv(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv"
    )

    differential_inductances = motor.calculate_differential_inductances()
    export_path = tmp_path / "differential_inductances.csv"
    motor.export_differential_inductances_csv(export_path)

    assert isinstance(differential_inductances, DifferentialInductanceMap)
    assert list(differential_inductances.data.columns) == [
        "operating_point",
        "i_d_A",
        "i_q_A",
        "L_dd_H",
        "L_dq_H",
        "L_qd_H",
        "L_qq_H",
    ]
    assert differential_inductances.L_dd.shape == (3, 3)
    assert np.allclose(differential_inductances.data["L_dd_H"], 0.002)
    assert np.allclose(differential_inductances.data["L_qq_H"], 0.003)
    assert np.allclose(differential_inductances.data["L_dq_H"], 0.0)
    assert np.allclose(differential_inductances.data["L_qd_H"], 0.0)
    assert export_path.read_text(encoding="utf-8").startswith(
        "operating_point,i_d_A,i_q_A,L_dd_H,L_dq_H,L_qd_H,L_qq_H"
    )


def test_docs_helper_uses_new_linear_fit_implementation():
    fit = pyuzlib.docs.pmsm.L_dd_L_qq_from_flux_map_assuming_no_saturation(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv"
    )

    assert abs(fit.loc[0, "L_dd"] - 0.002) < 1e-12
    assert abs(fit.loc[0, "L_qq"] - 0.003) < 1e-12


def test_pmsm_operation_area_calculates_grid_and_max_torque_curve():
    motor = PMSM(
        PMSMParameters(
            R_ph_Ohm=0.51,
            Ld_Henry=0.002,
            Lq_Henry=0.003,
            Psi_PM_Vs=0.042,
            polePairs=4,
            J_kg_m_squared=0.000108,
            I_max_Ampere=12,
        )
    )

    operation_area = motor.calculate_operation_area(
        v_dc_V=48.0,
        speed_rpm=1000.0,
        grid_points=12,
        speeds_rpm=np.array([0.0, 1000.0]),
    )

    assert isinstance(operation_area, OperationArea)
    assert operation_area.torque_Nm.shape == (12, 12)
    assert operation_area.v_max_V == 48.0 / np.sqrt(3.0)
    assert operation_area.max_torque is not None
    assert set(operation_area.max_torque["strategy"]) == {"optimal", "id_zero"}
    assert "operation_area_grid" in motor.results
    assert "operation_area_max_torque" in motor.results


def test_docs_operation_area_helpers_smoke():
    import matplotlib

    matplotlib.use("Agg")
    machine_parameters_csv = (
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/machine_parameters.csv"
    )

    pyuzlib.docs.pmsm.plot_operation_area(
        machine_parameters_csv,
        v_dc_V=24.0,
        speed_rpm=1000.0,
        grid_points=12,
    )
    pyuzlib.docs.pmsm.plot_max_torque_curve(
        machine_parameters_csv,
        v_dc_V=24.0,
        speeds_rpm=np.array([0.0, 500.0]),
    )


def test_docs_linear_flux_model_comparison_helper_smoke():
    import matplotlib

    matplotlib.use("Agg")
    pyuzlib.docs.pmsm.plot_linear_flux_model_comparison(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv",
        grid_points=5,
    )


def test_docs_differential_inductance_plot_helper_smoke():
    import matplotlib

    matplotlib.use("Agg")
    pyuzlib.docs.pmsm.plot_differential_inductances(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/flux_map.csv"
    )
