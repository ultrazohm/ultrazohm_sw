import pyuzlib
import numpy as np
import pytest
from pyuzlib import machine_catalog
from pyuzlib._repo_paths import machine_catalog_default_paths
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


def test_pyuzlib_exposes_machine_catalog_api():
    assert pyuzlib.machine_catalog.parse_uz_pmsm_struct_fields
    assert pyuzlib.machine_catalog.generate_machine_catalog


def test_pmsm_parameters_load_c_values_and_additional_values():
    parameters = PMSMParameters.from_csv(
        "docs/source/software/control/uz_pmsm/dummy_motor/nominal_v1/machine_parameters.csv"
    )

    assert parameters.R_ph_Ohm == 0.51
    assert parameters.Ld_Henry == 0.002
    assert parameters.I_rated_Ampere == 8.0
    assert parameters.machine_id == 2
    assert parameters.to_c_dict()["I_max_Ampere"] == 12.0


def test_pmsm_parameters_c_field_names_follow_dataclass_order():
    assert tuple(
        (field_spec.ctype, field_spec.name)
        for field_spec in PMSMParameters.C_PARAMETER_FIELDS
    ) == (
        ("uint32_t", "machine_id"),
        ("float", "R_ph_Ohm"),
        ("float", "Ld_Henry"),
        ("float", "Lq_Henry"),
        ("float", "Psi_PM_Vs"),
        ("float", "polePairs"),
        ("float", "J_kg_m_squared"),
        ("float", "I_max_Ampere"),
        ("float", "I_rated_Ampere"),
        ("float", "Torque_rated_Nm"),
        ("float", "Torque_max_Nm"),
        ("float", "Torque_min_Nm"),
        ("float", "speed_rated_rpm"),
        ("float", "speed_max_rpm"),
        ("float", "speed_min_rpm"),
        ("float", "V_dc_nominal_V"),
        ("float", "I_d_max_A"),
        ("float", "I_d_min_A"),
        ("float", "I_q_max_A"),
        ("float", "I_q_min_A"),
    )
    assert PMSMParameters.C_PARAMETER_NAMES == (
        "machine_id",
        "R_ph_Ohm",
        "Ld_Henry",
        "Lq_Henry",
        "Psi_PM_Vs",
        "polePairs",
        "J_kg_m_squared",
        "I_max_Ampere",
        "I_rated_Ampere",
        "Torque_rated_Nm",
        "Torque_max_Nm",
        "Torque_min_Nm",
        "speed_rated_rpm",
        "speed_max_rpm",
        "speed_min_rpm",
        "V_dc_nominal_V",
        "I_d_max_A",
        "I_d_min_A",
        "I_q_max_A",
        "I_q_min_A",
    )


def test_machine_catalog_parses_uz_pmsm_fields_from_c_header():
    header_path = "vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h"

    c_fields = machine_catalog.parse_uz_pmsm_struct_fields(header_path)

    assert c_fields == PMSMParameters.C_PARAMETER_FIELDS


def test_machine_catalog_rejects_unsupported_c_struct_declarations(tmp_path):
    header_path = tmp_path / "uz_PMSM_config.h"
    header_path.write_text(
        "typedef struct uz_PMSM_t{\n"
        "    float R_ph_Ohm;\n"
        "    char unsupported_name[16];\n"
        "}uz_PMSM_t;\n",
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="Unsupported uz_PMSM_t field declaration"):
        machine_catalog.parse_uz_pmsm_struct_fields(header_path)


def test_machine_catalog_parses_future_uint32_c_struct_field(tmp_path):
    header_path = tmp_path / "uz_PMSM_config.h"
    header_path.write_text(
        "typedef struct uz_PMSM_t{\n"
        "    float R_ph_Ohm;\n"
        "    uint32_t machine_id;\n"
        "}uz_PMSM_t;\n",
        encoding="utf-8",
    )

    c_fields = machine_catalog.parse_uz_pmsm_struct_fields(header_path)

    assert c_fields == (
        machine_catalog.CParameterField(ctype="float", name="R_ph_Ohm"),
        machine_catalog.CParameterField(ctype="uint32_t", name="machine_id"),
    )


def test_machine_catalog_rejects_unsupported_c_struct_field_types(tmp_path):
    header_path = tmp_path / "uz_PMSM_config.h"
    header_path.write_text(
        "typedef struct uz_PMSM_t{\n"
        "    double R_ph_Ohm;\n"
        "}uz_PMSM_t;\n",
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="Unsupported uz_PMSM_t field type"):
        machine_catalog.parse_uz_pmsm_struct_fields(header_path)


def test_machine_catalog_formats_uint32_c_values():
    assert machine_catalog.format_c_value(42, "uint32_t") == "42u"
    assert machine_catalog.format_c_value(42.0, "uint32_t") == "42u"
    with pytest.raises(ValueError, match="Cannot render non-integer"):
        machine_catalog.format_c_value(42.5, "uint32_t")


def test_machine_catalog_detects_drift_between_c_header_and_python_model(monkeypatch):
    monkeypatch.setattr(
        PMSMParameters,
        "C_PARAMETER_FIELDS",
        PMSMParameters.C_PARAMETER_FIELDS
        + (machine_catalog.CParameterField(ctype="float", name="new_parameter"),),
    )

    with pytest.raises(ValueError, match="pyuzlib.PMSMParameters and uz_PMSM_t differ"):
        machine_catalog.discover_machine_catalog(
            uz_pmsm_dir="docs/source/software/control/uz_pmsm",
            c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        )


def test_machine_catalog_rejects_duplicate_numeric_machine_id(tmp_path):
    machine_a_dir = tmp_path / "machine_a" / "dataset_v1"
    machine_b_dir = tmp_path / "machine_b" / "dataset_v1"
    machine_a_dir.mkdir(parents=True)
    machine_b_dir.mkdir(parents=True)
    csv_content = (
        "parameter,value\n"
        "machine_id,1\n"
        "R_ph_Ohm,0.51\n"
        "Ld_Henry,0.002\n"
        "Lq_Henry,0.003\n"
        "Psi_PM_Vs,0.042\n"
        "polePairs,4\n"
        "J_kg_m_squared,0.000108\n"
        "I_max_Ampere,12\n"
        "I_rated_Ampere,8\n"
        "Torque_rated_Nm,1.2\n"
        "Torque_max_Nm,2\n"
        "Torque_min_Nm,-2\n"
        "speed_rated_rpm,1000\n"
        "speed_max_rpm,1500\n"
        "speed_min_rpm,-1500\n"
        "V_dc_nominal_V,24\n"
        "I_d_max_A,10\n"
        "I_d_min_A,-10\n"
        "I_q_max_A,10\n"
        "I_q_min_A,-10\n"
    )
    (machine_a_dir / "machine_parameters.csv").write_text(csv_content, encoding="utf-8")
    (machine_b_dir / "machine_parameters.csv").write_text(csv_content, encoding="utf-8")

    with pytest.raises(ValueError, match="Duplicate numeric machine_id 1.*Next unused machine_id is 2"):
        machine_catalog.discover_machine_catalog(
            uz_pmsm_dir=tmp_path,
            c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        )


def test_machine_catalog_generates_inventory_and_header(tmp_path):
    inventory_output = tmp_path / "available_machines.csv"
    header_output = tmp_path / "uz_available_machines_auto_generated.h"

    entries = machine_catalog.generate_machine_catalog(
        uz_pmsm_dir="docs/source/software/control/uz_pmsm",
        c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        inventory_output=inventory_output,
        generated_header_output=header_output,
        generator_script="pyuzlib.machine_catalog",
    )

    assert len(entries) == 4
    assert "DUMMY_MOTOR_NOMINAL_V1" in inventory_output.read_text(encoding="utf-8")
    header_text = header_output.read_text(encoding="utf-8")
    assert "#define UZ_PMSM_DUMMY_MOTOR_NOMINAL_V1_INIT" in header_text
    assert ".machine_id = 2u" in header_text
    assert ".R_ph_Ohm = 0.51f" in header_text


def test_machine_catalog_default_paths_point_to_repo_layout():
    defaults = machine_catalog_default_paths("pyuzlib/src/pyuzlib/machine_catalog.py")

    assert defaults["uz_pmsm_dir"].as_posix().endswith("docs/source/software/control/uz_pmsm")
    assert defaults["c_header_path"].as_posix().endswith(
        "vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h"
    )


def test_pmsm_parameters_load_string_metadata_and_ignore_appended_table(tmp_path):
    csv_path = tmp_path / "machine_parameters.csv"
    csv_path.write_text(
        "parameter,value\n"
        "machine_name,beckhoff_AM8141-0j00-000\n"
        "machine_id,1\n"
        "R_ph_Ohm,0.51\n"
        "Ld_Henry,0.00175\n"
        "Lq_Henry,0.00175\n"
        "Psi_PM_Vs,0.042\n"
        "polePairs,4\n"
        "J_kg_m_squared,0.000108\n"
        "I_max_Ampere,12\n"
        "I_rated_Ampere,8\n"
        "Torque_rated_Nm,1.2\n"
        "Torque_max_Nm,2\n"
        "Torque_min_Nm,-2\n"
        "speed_rated_rpm,1000\n"
        "speed_max_rpm,1500\n"
        "speed_min_rpm,-1500\n"
        "V_dc_nominal_V,48\n"
        "I_d_max_A,10\n"
        "I_d_min_A,-10\n"
        "I_q_max_A,10\n"
        "I_q_min_A,-10\n"
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
