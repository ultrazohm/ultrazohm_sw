from __future__ import annotations

from pathlib import Path

import pytest

from pyuzlib import flux_map_catalog
from pyuzlib.flux_map_catalog import flux_map_catalog_default_paths
from pyuzlib.pmsm import DifferentialInductanceMap


def _dummy_entry():
    paths = flux_map_catalog_default_paths(__file__)
    entries = flux_map_catalog.discover_flux_map_catalog(paths["uz_pmsm_dir"])
    by_id = {entry.catalog_id: entry for entry in entries}
    assert "DUMMY_MOTOR_NOMINAL_V1" in by_id
    return by_id["DUMMY_MOTOR_NOMINAL_V1"]


def _dummy_diffind_entry():
    paths = flux_map_catalog_default_paths(__file__)
    entries = flux_map_catalog.discover_differential_inductance_catalog(paths["uz_pmsm_dir"])
    by_id = {entry.catalog_id: entry for entry in entries}
    assert "DUMMY_MOTOR_NOMINAL_V1" in by_id
    return by_id["DUMMY_MOTOR_NOMINAL_V1"]


def test_discover_flux_map_catalog_reads_dummy_grid():
    entry = _dummy_entry()
    assert entry.i_d_breakpoints_A == (-10.0, 0.0, 10.0)
    assert entry.i_q_breakpoints_A == (-10.0, 0.0, 10.0)
    # 3x3 grid -> 9 values each.
    assert len(entry.psi_d_Vs) == 3 * 3
    assert len(entry.psi_q_Vs) == 3 * 3


def test_flux_map_arrays_are_row_major_with_i_d_fastest():
    entry = _dummy_entry()
    # dummy is linear: psi_d = 0.002*i_d + 0.042 (independent of i_q),
    # psi_q = 0.003*i_q (independent of i_d).
    # Row-major, i_d fastest -> the first row (i_q = -10) repeats the i_d sweep for psi_d.
    assert entry.psi_d_Vs[0:3] == pytest.approx((0.022, 0.042, 0.062))
    assert entry.psi_d_Vs[3:6] == pytest.approx((0.022, 0.042, 0.062))
    # psi_q is constant within an i_q row and steps between rows.
    assert entry.psi_q_Vs[0:3] == pytest.approx((-0.03, -0.03, -0.03))
    assert entry.psi_q_Vs[3:6] == pytest.approx((0.0, 0.0, 0.0))
    assert entry.psi_q_Vs[6:9] == pytest.approx((0.03, 0.03, 0.03))


def test_render_flux_map_header_emits_expected_macros():
    paths = flux_map_catalog_default_paths(__file__)
    entries = flux_map_catalog.discover_flux_map_catalog(paths["uz_pmsm_dir"])
    text = flux_map_catalog.render_flux_map_header(
        entries, source_root=paths["uz_pmsm_dir"], generator_script="pyuzlib.flux_map_catalog"
    )
    assert "#define UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_D_LENGTH 3" in text
    assert "#define UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_Q_LENGTH 3" in text
    assert "#define UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_D_BREAKPOINTS_A { -10.0f, 0.0f, 10.0f }" in text
    assert "#define UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_PSI_D_VS \\" in text
    # Names line up with the scalar catalog macro prefix.
    assert "UZ_FLUXMAP_BECKHOFF_AM8141_0J00_000_MEASURED_PSI_DQ_AVERAGED_800_RPM_PSI_Q_VS" in text


def test_committed_flux_map_header_is_in_sync(tmp_path):
    paths = flux_map_catalog_default_paths(__file__)
    committed = Path(paths["flux_map_header_output"])
    assert committed.exists(), "run `make auto_generate_flux_maps` and commit the header"
    regenerated = tmp_path / "uz_pmsm_flux_maps_auto_generated.h"
    flux_map_catalog.generate_flux_map_header(
        uz_pmsm_dir=paths["uz_pmsm_dir"],
        header_output=regenerated,
        generator_script="pyuzlib.flux_map_catalog",
    )
    assert regenerated.read_text(encoding="utf-8") == committed.read_text(encoding="utf-8")


def test_discover_flux_map_catalog_errors_when_no_datasets(tmp_path):
    with pytest.raises(ValueError, match="No flux_map.csv files found"):
        flux_map_catalog.discover_flux_map_catalog(tmp_path)


def test_differential_inductance_map_from_csv_reads_dummy_grid():
    paths = flux_map_catalog_default_paths(__file__)
    csv_path = paths["uz_pmsm_dir"] / "dummy_motor/nominal_v1/differential_inductances.csv"
    diff_ind = DifferentialInductanceMap.from_csv(csv_path)
    # dummy flux map is linear -> constant differential inductances.
    assert diff_ind.L_dd.to_numpy().ravel() == pytest.approx([0.002] * 9)
    assert diff_ind.L_dq.to_numpy().ravel() == pytest.approx([0.0] * 9)
    assert diff_ind.L_qd.to_numpy().ravel() == pytest.approx([0.0] * 9)
    assert diff_ind.L_qq.to_numpy().ravel() == pytest.approx([0.003] * 9)


def test_differential_inductance_map_from_csv_rejects_missing_columns(tmp_path):
    csv_path = tmp_path / "differential_inductances.csv"
    csv_path.write_text("i_d_A,i_q_A,L_dd_H\n0,0,0.002\n", encoding="utf-8")
    with pytest.raises(ValueError, match="Missing differential-inductance CSV columns"):
        DifferentialInductanceMap.from_csv(csv_path)


def test_discover_differential_inductance_catalog_reads_dummy_grid():
    entry = _dummy_diffind_entry()
    assert entry.i_d_breakpoints_A == (-10.0, 0.0, 10.0)
    assert entry.i_q_breakpoints_A == (-10.0, 0.0, 10.0)
    assert len(entry.L_dd_H) == 3 * 3
    assert entry.L_dd_H == pytest.approx((0.002,) * 9)
    assert entry.L_qq_H == pytest.approx((0.003,) * 9)
    assert entry.L_dq_H == pytest.approx((0.0,) * 9)
    assert entry.L_qd_H == pytest.approx((0.0,) * 9)


def test_render_differential_inductance_header_emits_expected_macros():
    paths = flux_map_catalog_default_paths(__file__)
    entries = flux_map_catalog.discover_differential_inductance_catalog(paths["uz_pmsm_dir"])
    text = flux_map_catalog.render_differential_inductance_header(
        entries, source_root=paths["uz_pmsm_dir"], generator_script="pyuzlib.flux_map_catalog"
    )
    assert "#define UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_I_D_LENGTH 3" in text
    assert "#define UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_DD_H \\" in text
    assert "#define UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_QQ_H \\" in text
    assert "UZ_DIFFIND_MH_PROTOTYPE_FEM_OVERAGED_OVER_ANGLE_L_QD_H" in text


def test_committed_differential_inductance_header_is_in_sync(tmp_path):
    paths = flux_map_catalog_default_paths(__file__)
    committed = Path(paths["differential_inductance_header_output"])
    assert committed.exists(), "run `make auto_generate_flux_maps` and commit the header"
    regenerated = tmp_path / "uz_pmsm_differential_inductances_auto_generated.h"
    flux_map_catalog.generate_differential_inductance_header(
        uz_pmsm_dir=paths["uz_pmsm_dir"],
        header_output=regenerated,
        generator_script="pyuzlib.flux_map_catalog",
    )
    assert regenerated.read_text(encoding="utf-8") == committed.read_text(encoding="utf-8")


def test_discover_differential_inductance_catalog_errors_when_no_datasets(tmp_path):
    with pytest.raises(ValueError, match="No differential_inductances.csv files found"):
        flux_map_catalog.discover_differential_inductance_catalog(tmp_path)
