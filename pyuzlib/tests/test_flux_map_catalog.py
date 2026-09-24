from __future__ import annotations

from pathlib import Path
from dataclasses import replace
import os
import shlex
import shutil
import subprocess

import numpy as np
import pandas as pd
import pytest

from pyuzlib import flux_map_catalog, machine_catalog
from pyuzlib.flux_map_catalog import flux_map_catalog_default_paths
from pyuzlib.pmsm import DifferentialInductanceMap, FluxMap


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


@pytest.fixture(params=["flux", "inductance"])
def catalog_kind(request):
    if request.param == "flux":
        return (
            "flux_map.csv", ("psi_d_Vs", "psi_q_Vs"), FluxMap.from_csv,
            flux_map_catalog.discover_flux_map_catalog,
        )
    return (
        "differential_inductances.csv", ("L_dd_H", "L_dq_H", "L_qd_H", "L_qq_H"),
        DifferentialInductanceMap.from_csv,
        flux_map_catalog.discover_differential_inductance_catalog,
    )


@pytest.mark.parametrize("axis", ["i_d_A", "i_q_A"])
@pytest.mark.parametrize("points, message", [
    ([0.0], "at least two breakpoints"),
    ([1.0, 1.0 + 1e-8], "strictly increasing after C float conversion"),
    ([0.0, 1e39], "out of range"),
    ([0.0, 1e-50], "underflows"),
])
def test_c_export_rejects_invalid_axes_but_analysis_can_load_them(
    tmp_path, catalog_kind, axis, points, message,
):
    filename, fields, load, discover = catalog_kind
    axes = {"i_d_A": [0.0, 1.0], "i_q_A": [0.0, 1.0]}
    axes[axis] = points
    rows = [
        {"i_d_A": d, "i_q_A": q, **dict.fromkeys(fields, 0.002)}
        for q in axes["i_q_A"] for d in axes["i_d_A"]
    ]
    csv_path = tmp_path / "motor" / "dataset" / filename
    csv_path.parent.mkdir(parents=True)
    pd.DataFrame(rows).to_csv(csv_path, index=False)
    load(csv_path)  # C-export restrictions must not leak into the analysis importer.
    with pytest.raises(ValueError, match=message) as error:
        discover(tmp_path)
    assert filename in str(error.value)


@pytest.mark.parametrize("bad_value", [1e39, -1e39, 1e-50])
def test_c_export_checks_every_grid_value(tmp_path, catalog_kind, bad_value):
    filename, fields, load, discover = catalog_kind
    csv_path = tmp_path / "motor" / "dataset" / filename
    csv_path.parent.mkdir(parents=True)
    for field in fields:
        rows = [
            {"i_d_A": d, "i_q_A": q, **dict.fromkeys(fields, 0.002)}
            for q in [0.0, 1.0] for d in [0.0, 1.0]
        ]
        rows[-1][field] = bad_value
        pd.DataFrame(rows).to_csv(csv_path, index=False)
        load(csv_path)
        with pytest.raises(ValueError, match=field):
            discover(tmp_path)


@pytest.mark.parametrize("kind", ["flux", "inductance"])
@pytest.mark.parametrize("problem", ["length", "nan", "inf", "descending"])
def test_header_rendering_validates_directly_supplied_entries(kind, problem):
    paths = flux_map_catalog_default_paths(__file__)
    if kind == "flux":
        entry = _dummy_entry()
        field = "psi_q_Vs"
        render = flux_map_catalog.render_flux_map_header
    else:
        entry = _dummy_diffind_entry()
        field = "L_qd_H"
        render = flux_map_catalog.render_differential_inductance_header
    if problem == "descending":
        entry = replace(entry, i_d_breakpoints_A=tuple(reversed(entry.i_d_breakpoints_A)))
        message = "strictly increasing"
    else:
        values = getattr(entry, field)
        values = values[:-1] if problem == "length" else (*values[:-1], float(problem))
        entry = replace(entry, **{field: values})
        message = "expected 9" if problem == "length" else "non-finite"
    with pytest.raises(ValueError, match=message):
        render([entry], source_root=paths["uz_pmsm_dir"], generator_script="test")


def test_committed_inductances_match_flux_map_derivatives():
    paths = flux_map_catalog_default_paths(__file__)
    entries = flux_map_catalog.discover_differential_inductance_catalog(paths["uz_pmsm_dir"])
    for entry in entries:
        csv_path = paths["uz_pmsm_dir"] / entry.differential_inductances_csv
        actual = DifferentialInductanceMap.from_csv(csv_path)
        expected = DifferentialInductanceMap.from_flux_map(
            FluxMap.from_csv(csv_path.with_name("flux_map.csv")), edge_order=2,
        )
        np.testing.assert_array_equal(
            actual.data[["i_d_A", "i_q_A"]], expected.data[["i_d_A", "i_q_A"]],
        )
        for field in ("L_dd_H", "L_dq_H", "L_qd_H", "L_qq_H"):
            # Allow CSV serialization and numerical roundoff, including near-zero
            # cross derivatives. No symmetry or positive-definiteness assumption.
            np.testing.assert_allclose(
                actual.data[field], expected.data[field], rtol=1e-10, atol=1e-14,
                err_msg=f"{csv_path}: {field} is stale; regenerate from flux_map.csv",
            )


def test_generated_catalog_declarations_compile_as_c(tmp_path):
    compiler = shlex.split(os.environ.get("CC", "cc"))
    assert compiler and shutil.which(compiler[0]), "A C compiler is required; set CC to its command"
    paths = flux_map_catalog_default_paths(__file__)
    # Compile the actual public struct against freshly generated headers.
    header = tmp_path / paths["c_header_path"].name
    header.write_text(paths["c_header_path"].read_text(encoding="utf-8"), encoding="utf-8")
    machines = machine_catalog.generate_machine_catalog(
        uz_pmsm_dir=paths["uz_pmsm_dir"], c_header_path=header,
        inventory_output=tmp_path / "inventory.csv",
        generated_header_output=tmp_path / paths["generated_header_output"].name,
        generator_script="test",
    )
    flux = flux_map_catalog.generate_flux_map_header(
        uz_pmsm_dir=paths["uz_pmsm_dir"], header_output=tmp_path / "flux.h", generator_script="test",
    )
    inductance = flux_map_catalog.generate_differential_inductance_header(
        uz_pmsm_dir=paths["uz_pmsm_dir"], header_output=tmp_path / "inductance.h", generator_script="test",
    )
    lines = ['#include "uz_PMSM_config.h"', '#include "flux.h"', '#include "inductance.h"']
    for entry in machines:
        lines.append(f"uz_PMSM_t machine_{entry.catalog_id} = {entry.macro_name};")
    for entries, prefix, fields in (
        (flux, "UZ_FLUXMAP", ("PSI_D_VS", "PSI_Q_VS")),
        (inductance, "UZ_DIFFIND", ("L_DD_H", "L_DQ_H", "L_QD_H", "L_QQ_H")),
    ):
        for entry in entries:
            macro = f"{prefix}_{entry.catalog_id}"
            for suffix, count in (
                ("I_D_BREAKPOINTS_A", f"{macro}_I_D_LENGTH"),
                ("I_Q_BREAKPOINTS_A", f"{macro}_I_Q_LENGTH"),
                *((field, f"{macro}_I_D_LENGTH * {macro}_I_Q_LENGTH") for field in fields),
            ):
                name = f"{macro}_{suffix}"
                lines.append(f"float array_{name}[] = {name};")
                lines.append(
                    f'_Static_assert(sizeof(array_{name}) / sizeof(float) == {count}, "{name}");'
                )
    for index, value in enumerate([float(np.finfo(np.float32).max), float.fromhex("0x1p-149")]):
        lines.append(f"float boundary_{index} = {machine_catalog.format_c_float(value)};")
    source = tmp_path / "catalog.c"
    source.write_text("\n".join(lines) + "\n", encoding="utf-8")
    result = subprocess.run(
        [*compiler, "-std=c11", "-Wall", "-Wextra", "-Werror", "-pedantic", "-fsyntax-only", str(source)],
        capture_output=True, text=True, check=False,
    )
    assert result.returncode == 0, result.stdout + result.stderr
