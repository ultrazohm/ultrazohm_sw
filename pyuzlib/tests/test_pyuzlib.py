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


def test_pmsm_parameters_rejects_torque_min_not_less_than_torque_max(tmp_path):
    csv_path = tmp_path / "machine_parameters.csv"
    csv_path.write_text(
        "parameter,value\nmachine_id,1\nR_ph_Ohm,0.51\nLd_Henry,0.002\nLq_Henry,0.003\n"
        "Psi_PM_Vs,0.042\npolePairs,4\nJ_kg_m_squared,0.000108\nI_max_Ampere,12\n"
        "I_rated_Ampere,8\nTorque_rated_Nm,1.2\nTorque_max_Nm,2\n"
        "Torque_min_Nm,2\n"  # positive — must be <= 0
        "speed_rated_rpm,1000\nspeed_max_rpm,1500\nspeed_min_rpm,-1500\n"
        "V_dc_nominal_V,24\nI_d_max_A,10\nI_d_min_A,-10\nI_q_max_A,10\nI_q_min_A,-10\n",
        encoding="utf-8",
    )
    with pytest.raises(ValueError, match="Torque_min_Nm"):
        PMSMParameters.from_csv(csv_path).validate_for_c()


def test_pmsm_parameters_rejects_speed_min_positive(tmp_path):
    csv_path = tmp_path / "machine_parameters.csv"
    csv_path.write_text(
        "parameter,value\nmachine_id,1\nR_ph_Ohm,0.51\nLd_Henry,0.002\nLq_Henry,0.003\n"
        "Psi_PM_Vs,0.042\npolePairs,4\nJ_kg_m_squared,0.000108\nI_max_Ampere,12\n"
        "I_rated_Ampere,8\nTorque_rated_Nm,1.2\nTorque_max_Nm,2\nTorque_min_Nm,-2\n"
        "speed_rated_rpm,1000\nspeed_max_rpm,1500\n"
        "speed_min_rpm,500\n"  # positive — must be <= 0
        "V_dc_nominal_V,24\nI_d_max_A,10\nI_d_min_A,-10\nI_q_max_A,10\nI_q_min_A,-10\n",
        encoding="utf-8",
    )
    with pytest.raises(ValueError, match="speed_min_rpm"):
        PMSMParameters.from_csv(csv_path).validate_for_c()


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


def test_machine_catalog_rejects_multi_variable_declaration(tmp_path):
    # A single declaration listing several fields (float a, b;) is not representable as a
    # (name, value) CSV row and must be rejected loudly rather than silently mis-parsed.
    header_path = tmp_path / "uz_PMSM_config.h"
    header_path.write_text(
        "typedef struct uz_PMSM_t{\n"
        "    float R_ph_Ohm;\n"
        "    float Ld_Henry, Lq_Henry;\n"
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


def test_renumber_duplicate_machine_ids_resolves_collision(tmp_path):
    csv_content = (
        "parameter,value\n"
        "machine_id,1\n"
        "R_ph_Ohm,0.51\n"
        "Ld_Henry,0.002\n"
    )
    machine_a_dir = tmp_path / "machine_a" / "dataset_v1"
    machine_b_dir = tmp_path / "machine_b" / "dataset_v1"
    machine_a_dir.mkdir(parents=True)
    machine_b_dir.mkdir(parents=True)
    (machine_a_dir / "machine_parameters.csv").write_text(csv_content, encoding="utf-8")
    (machine_b_dir / "machine_parameters.csv").write_text(csv_content, encoding="utf-8")

    changes = machine_catalog.renumber_duplicate_machine_ids(tmp_path)

    # First dataset in sorted catalog order keeps id 1; the second is bumped to the next unused id.
    assert changes == [("machine_b/dataset_v1/machine_parameters.csv", 1, 2)]
    assert machine_catalog._read_machine_id_from_csv(machine_a_dir / "machine_parameters.csv") == 1
    assert machine_catalog._read_machine_id_from_csv(machine_b_dir / "machine_parameters.csv") == 2
    # Other rows are preserved untouched.
    assert "R_ph_Ohm,0.51" in (machine_b_dir / "machine_parameters.csv").read_text(encoding="utf-8")
    # Running again is a no-op once ids are unique.
    assert machine_catalog.renumber_duplicate_machine_ids(tmp_path) == []


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


def test_flux_map_rejects_incomplete_rectangular_grid(tmp_path):
    csv_path = tmp_path / "flux_map.csv"
    csv_path.write_text(
        "i_d_A,i_q_A,psi_d_Vs,psi_q_Vs\n"
        "-1,0,0.01,0.02\n"
        "0,0,0.03,0.04\n"
        "-1,1,0.05,0.06\n",
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="rectangular"):
        FluxMap.from_csv(csv_path)


def test_flux_map_rejects_non_finite_values(tmp_path):
    csv_path = tmp_path / "flux_map.csv"
    csv_path.write_text(
        "i_d_A,i_q_A,psi_d_Vs,psi_q_Vs\n"
        "-1,0,0.01,0.02\n"
        "0,0,nan,0.04\n",
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="non-finite"):
        FluxMap.from_csv(csv_path)


def test_flux_map_rejects_duplicate_operating_points(tmp_path):
    csv_path = tmp_path / "flux_map.csv"
    csv_path.write_text(
        "i_d_A,i_q_A,psi_d_Vs,psi_q_Vs\n"
        "-1,0,0.01,0.02\n"
        "-1,0,0.03,0.04\n",
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="duplicate"):
        FluxMap.from_csv(csv_path)


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


def test_add_machine_creates_template_and_prints_hints(tmp_path, capsys):
    csv_path, script_path, next_id = machine_catalog.create_machine_template(
        motor_name="test_motor",
        dataset_name="v1",
        uz_pmsm_dir=tmp_path,
    )

    assert csv_path.exists()
    assert script_path is None
    csv_text = csv_path.read_text(encoding="utf-8")
    assert "parameter,value" in csv_text
    assert "machine_id," in csv_text
    assert "R_ph_Ohm," in csv_text
    assert next_id == 1

    machine_catalog._print_parameter_hints(next_id)
    out = capsys.readouterr().out
    assert "R_ph_Ohm" in out
    assert "> 0" in out
    assert "pre-filled: 1" in out


def test_add_machine_with_raw_data_creates_preprocess_script(tmp_path):
    csv_path, script_path, next_id = machine_catalog.create_machine_template(
        motor_name="test_motor",
        dataset_name="v1",
        uz_pmsm_dir=tmp_path,
        with_raw_data=True,
    )

    assert csv_path.exists()
    assert script_path is not None
    assert script_path.exists()
    script_text = script_path.read_text(encoding="utf-8")
    assert "pyuzlib" in script_text
    assert "flux_map_raw.csv" in script_text
    assert "TODO" in script_text
    assert "export_flux_map_csv" in script_text


def test_add_machine_cli_without_raw_data(tmp_path):
    rc = machine_catalog.main(
        ["--uz-pmsm-dir", str(tmp_path), "add_machine", "my_motor", "nominal_v1"],
    )
    assert rc == 0
    assert (tmp_path / "my_motor" / "nominal_v1" / "machine_parameters.csv").exists()
    assert not (tmp_path / "my_motor" / "nominal_v1" / "preprocess_to_correct_data_format.py").exists()


def test_add_machine_cli_with_raw_data(tmp_path):
    rc = machine_catalog.main(
        ["--uz-pmsm-dir", str(tmp_path), "add_machine", "my_motor", "nominal_v1", "--with-raw-data"],
    )
    assert rc == 0
    assert (tmp_path / "my_motor" / "nominal_v1" / "machine_parameters.csv").exists()
    assert (tmp_path / "my_motor" / "nominal_v1" / "preprocess_to_correct_data_format.py").exists()


_VALID_MACHINE_CSV = (
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


_VALID_FLUX_MAP_CSV = (
    "operating_point,i_d_A,i_q_A,psi_d_Vs,psi_q_Vs\n"
    "0,-1,0,0.01,0.02\n"
    "1,0,0,0.03,0.04\n"
    "2,-1,1,0.05,0.06\n"
    "3,0,1,0.07,0.08\n"
)


_VALID_DIFFERENTIAL_INDUCTANCES_CSV = (
    "operating_point,i_d_A,i_q_A,L_dd_H,L_dq_H,L_qd_H,L_qq_H\n"
    "0,-1,0,0.001,0,0,0.002\n"
    "1,0,0,0.001,0,0,0.002\n"
    "2,-1,1,0.001,0,0,0.002\n"
    "3,0,1,0.001,0,0,0.002\n"
)


def test_machine_catalog_rejects_zero_machine_id(tmp_path):
    dataset_dir = tmp_path / "machine_a" / "dataset_v1"
    dataset_dir.mkdir(parents=True)
    (dataset_dir / "machine_parameters.csv").write_text(
        _VALID_MACHINE_CSV.replace("machine_id,1", "machine_id,0"),
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="machine_id must be a positive integer"):
        machine_catalog.discover_machine_catalog(
            uz_pmsm_dir=tmp_path,
            c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        )


def test_renumber_duplicate_machine_ids_replaces_zero_and_missing_ids(tmp_path):
    zero_dir = tmp_path / "machine_a" / "dataset_v1"
    missing_dir = tmp_path / "machine_b" / "dataset_v1"
    valid_dir = tmp_path / "machine_c" / "dataset_v1"
    zero_dir.mkdir(parents=True)
    missing_dir.mkdir(parents=True)
    valid_dir.mkdir(parents=True)
    (zero_dir / "machine_parameters.csv").write_text(
        _VALID_MACHINE_CSV.replace("machine_id,1", "machine_id,0"),
        encoding="utf-8",
    )
    (missing_dir / "machine_parameters.csv").write_text(
        _VALID_MACHINE_CSV.replace("machine_id,1\n", ""),
        encoding="utf-8",
    )
    (valid_dir / "machine_parameters.csv").write_text(
        _VALID_MACHINE_CSV,
        encoding="utf-8",
    )

    changes = machine_catalog.renumber_duplicate_machine_ids(tmp_path)

    assert changes == [
        ("machine_a/dataset_v1/machine_parameters.csv", 0, 2),
        ("machine_b/dataset_v1/machine_parameters.csv", 0, 3),
    ]
    assert machine_catalog._read_machine_id_from_csv(zero_dir / "machine_parameters.csv") == 2
    assert machine_catalog._read_machine_id_from_csv(missing_dir / "machine_parameters.csv") == 3
    assert machine_catalog._read_machine_id_from_csv(valid_dir / "machine_parameters.csv") == 1


def test_machine_catalog_rejects_mismatched_differential_inductance_grid(tmp_path):
    dataset_dir = tmp_path / "machine_a" / "dataset_v1"
    dataset_dir.mkdir(parents=True)
    (dataset_dir / "machine_parameters.csv").write_text(_VALID_MACHINE_CSV, encoding="utf-8")
    (dataset_dir / "flux_map.csv").write_text(_VALID_FLUX_MAP_CSV, encoding="utf-8")
    (dataset_dir / "differential_inductances.csv").write_text(
        _VALID_DIFFERENTIAL_INDUCTANCES_CSV.replace("3,0,1", "3,1,1"),
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="same operating_point, i_d_A, and i_q_A order"):
        machine_catalog.discover_machine_catalog(
            uz_pmsm_dir=tmp_path,
            c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        )


def test_machine_catalog_rejects_orphan_differential_inductances(tmp_path):
    # differential_inductances.csv without a sibling flux_map.csv cannot be validated or regenerated.
    dataset_dir = tmp_path / "machine_a" / "dataset_v1"
    dataset_dir.mkdir(parents=True)
    (dataset_dir / "machine_parameters.csv").write_text(_VALID_MACHINE_CSV, encoding="utf-8")
    (dataset_dir / "differential_inductances.csv").write_text(
        _VALID_DIFFERENTIAL_INDUCTANCES_CSV,
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="no sibling flux_map.csv"):
        machine_catalog.discover_machine_catalog(
            uz_pmsm_dir=tmp_path,
            c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        )


def test_machine_catalog_allows_flux_map_without_differential_inductances(tmp_path):
    # The differential-inductance map is optional; a flux map on its own must still validate.
    dataset_dir = tmp_path / "machine_a" / "dataset_v1"
    dataset_dir.mkdir(parents=True)
    (dataset_dir / "machine_parameters.csv").write_text(_VALID_MACHINE_CSV, encoding="utf-8")
    (dataset_dir / "flux_map.csv").write_text(_VALID_FLUX_MAP_CSV, encoding="utf-8")

    _c_fields, entries = machine_catalog.discover_machine_catalog(
        uz_pmsm_dir=tmp_path,
        c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
    )
    assert len(entries) == 1


def test_machine_catalog_rejects_unsorted_flux_map_file_order(tmp_path):
    dataset_dir = tmp_path / "machine_a" / "dataset_v1"
    dataset_dir.mkdir(parents=True)
    (dataset_dir / "machine_parameters.csv").write_text(_VALID_MACHINE_CSV, encoding="utf-8")
    (dataset_dir / "flux_map.csv").write_text(
        _VALID_FLUX_MAP_CSV.replace(
            "1,0,0,0.03,0.04\n2,-1,1,0.05,0.06",
            "2,-1,1,0.05,0.06\n1,0,0,0.03,0.04",
        ),
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="canonical row-major order"):
        machine_catalog.discover_machine_catalog(
            uz_pmsm_dir=tmp_path,
            c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        )


def test_pmsm_parameters_reject_malformed_row_with_path_and_row_number(tmp_path):
    csv_path = tmp_path / "machine_parameters.csv"
    csv_path.write_text(
        "parameter,value\n"
        "machine_id,1\n"
        "R_ph_Ohm,0.51,stray_cell\n"
        "Ld_Henry,0.002\n",
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match=r"Malformed row 3 in .*machine_parameters\.csv"):
        PMSMParameters.from_csv(csv_path)


def test_pmsm_parameters_reject_duplicate_parameter_rows(tmp_path):
    csv_path = tmp_path / "machine_parameters.csv"
    csv_path.write_text(
        "parameter,value\n"
        "machine_id,1\n"
        "R_ph_Ohm,0.51\n"
        "R_ph_Ohm,0.62\n",
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match=r"Duplicate parameter 'R_ph_Ohm' in .*machine_parameters\.csv"):
        PMSMParameters.from_csv(csv_path)


def test_pmsm_parameters_unparseable_value_error_names_the_parameter(tmp_path):
    csv_path = tmp_path / "machine_parameters.csv"
    csv_path.write_text(
        "parameter,value\n"
        "machine_id,1\n"
        "R_ph_Ohm,\n",
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match=r"Cannot parse value '' for parameter 'R_ph_Ohm'"):
        PMSMParameters.from_csv(csv_path)


def test_machine_catalog_error_for_unfilled_template_names_csv_and_parameter(tmp_path):
    machine_catalog.create_machine_template(
        motor_name="my_motor",
        dataset_name="nominal_v1",
        uz_pmsm_dir=tmp_path,
    )

    with pytest.raises(ValueError, match=r"Invalid PMSM parameter CSV .*machine_parameters\.csv.*'R_ph_Ohm'"):
        machine_catalog.discover_machine_catalog(
            uz_pmsm_dir=tmp_path,
            c_header_path="vitis/software/Baremetal/src/uz/uz_PMSM_config/uz_PMSM_config.h",
        )


@pytest.mark.parametrize("bad_value", ["inf", "-inf", "nan", "1e39"])
def test_pmsm_parameters_reject_non_finite_and_out_of_float_range_values(tmp_path, bad_value):
    csv_path = tmp_path / "machine_parameters.csv"
    csv_path.write_text(
        _VALID_MACHINE_CSV.replace("V_dc_nominal_V,24", f"V_dc_nominal_V,{bad_value}"),
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="V_dc_nominal_V"):
        PMSMParameters.from_csv(csv_path).validate_for_c()


def test_machine_catalog_format_c_float_rejects_non_finite_values():
    with pytest.raises(ValueError, match="non-finite"):
        machine_catalog.format_c_float(float("inf"))
    with pytest.raises(ValueError, match="non-finite"):
        machine_catalog.format_c_float(float("nan"))


def test_parameter_constraints_cover_every_c_parameter_field():
    constraint_names = {entry.name for entry in pyuzlib.pmsm.PMSM_PARAMETER_CONSTRAINTS}
    assert set(PMSMParameters.C_PARAMETER_NAMES) <= constraint_names


def _c_asserted_pmsm_fields() -> set[str]:
    """Field names referenced by the uz_assert() calls in the two uz_PMSM_config assert
    functions of uz_PMSM_config.c. This is the C side of the constraint contract."""
    import re

    paths = machine_catalog_default_paths(__file__)
    c_source = paths["c_header_path"].with_name("uz_PMSM_config.c")
    text = c_source.read_text(encoding="utf-8")
    # Isolate the two model/envelope assert functions (exclude the fitting-parameter assert).
    bodies = re.findall(
        r"void\s+uz_PMSM_config_assert(?:_model)?\s*\(\s*uz_PMSM_t\s+config\s*\)\s*\{(.*?)\}",
        text,
        re.DOTALL,
    )
    assert bodies, "Could not locate uz_PMSM_config_assert functions in uz_PMSM_config.c"
    combined = "\n".join(bodies)
    return set(re.findall(r"config\.([A-Za-z_][A-Za-z0-9_]*)", combined))


def test_c_and_python_pmsm_constraints_do_not_drift():
    """Guard against the C uz_PMSM_config_assert* checks and the Python
    PMSM_PARAMETER_CONSTRAINTS drifting apart. Field-level parity: every field the C code
    asserts must be a known parameter, every field Python constrains must be asserted in C,
    and every C field except machine_id must be validated somewhere in C."""
    asserted_fields = _c_asserted_pmsm_fields()
    c_field_names = set(PMSMParameters.C_PARAMETER_NAMES)
    python_checked = {
        entry.name
        for entry in pyuzlib.pmsm.PMSM_PARAMETER_CONSTRAINTS
        if entry.check is not None
    }

    # No stray/typo field names on the C side.
    assert asserted_fields <= c_field_names
    # Every field with a Python value-constraint is asserted on the C side.
    assert python_checked <= asserted_fields
    # machine_id is documented as intentionally not asserted in C.
    assert "machine_id" not in asserted_fields
    # Every other struct field is validated somewhere in the C asserts (directly or via a relation).
    assert c_field_names - {"machine_id"} <= asserted_fields
