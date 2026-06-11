from pathlib import Path

import numpy as np
import pandas as pd
import plotly.graph_objects as go

from pyuzlib.pmsm import FluxMap
from pyuzlib.pmsm.fitting import fit_linear_flux_model_assuming_no_saturation
from pyuzlib.pmsm.flux_map import resolve_csv_path
from pyuzlib.pmsm.operation_area import Modulation, calculate_max_torque_curve


def _load_flux_map(csv_path: str | Path) -> tuple[Path, pd.DataFrame, pd.DataFrame, pd.DataFrame]:
    flux_map = FluxMap.from_csv(csv_path)
    assert flux_map.source_path is not None
    return flux_map.source_path, flux_map.data, flux_map.psi_d, flux_map.psi_q


def plot_flux_map(csv_path: str | Path) -> None:
    from pyuzlib.pmsm.plotting import plot_flux_map as _plot_flux_map

    _plot_flux_map(FluxMap.from_csv(csv_path))


def plot_flux_map_plotly(csv_path: str | Path) -> go.Figure:
    from pyuzlib.pmsm.plotting import plot_flux_map_plotly as _plot_flux_map_plotly

    return _plot_flux_map_plotly(FluxMap.from_csv(csv_path))


def plot_operation_area(
    machine_parameters_csv_path: str | Path,
    *,
    v_dc_V: float,
    speed_rpm: float,
    current_limit_A: float | None = None,
    modulation: Modulation = "svpwm",
    grid_points: int = 80,
    current_grid_factor: float = 1.2,
    speeds_rpm=None,
    show_optimal_torque_curve: bool = True,
    include_id_zero: bool = True,
    torque_isoline_levels=None,
) -> None:
    import pyuzlib

    motor = pyuzlib.pmsm.PMSM()
    motor.load_parameters_csv(resolve_csv_path(machine_parameters_csv_path))
    if show_optimal_torque_curve and speeds_rpm is None:
        speeds_rpm = np.linspace(0.0, speed_rpm, 20)
    elif not show_optimal_torque_curve:
        speeds_rpm = None

    operation_area = motor.calculate_operation_area(
        v_dc_V=v_dc_V,
        speed_rpm=speed_rpm,
        current_limit_A=current_limit_A,
        modulation=modulation,
        grid_points=grid_points,
        current_grid_factor=current_grid_factor,
        speeds_rpm=speeds_rpm,
        include_id_zero=include_id_zero,
    )
    motor.plot_operation_area(
        operation_area,
        torque_isoline_levels=torque_isoline_levels,
    )


def plot_max_torque_curve(
    machine_parameters_csv_path: str | Path,
    *,
    v_dc_V: float,
    speeds_rpm,
    current_limit_A: float | None = None,
    modulation: Modulation = "svpwm",
    include_id_zero: bool = True,
) -> None:
    import pyuzlib

    motor = pyuzlib.pmsm.PMSM()
    motor.load_parameters_csv(resolve_csv_path(machine_parameters_csv_path))
    max_torque = calculate_max_torque_curve(
        motor.parameters,
        speeds_rpm=speeds_rpm,
        v_dc_V=v_dc_V,
        current_limit_A=current_limit_A,
        modulation=modulation,
        include_id_zero=include_id_zero,
    )
    motor.plot_max_torque_curve(max_torque)


def L_dd_L_qq_from_flux_map_assuming_no_saturation(
    csv_path: str | Path,
    fit_name: str = "Linear Fit",
) -> pd.DataFrame:
    """
    Function to fit two linear regression models (one for psi_q and one for psi_d)
    and return a table with the coefficients for both fits in a single row.

    Parameters:
    csv_path (str | Path): Path to flux_map.csv.
    fit_name (str): Name of the fit to be added to the coefficients table.

    Returns:
    DataFrame: A table containing the fit name, coefficients, and R^2 values for
    the linear regression.
    """
    return fit_linear_flux_model_assuming_no_saturation(
        FluxMap.from_csv(csv_path),
        fit_name=fit_name,
    )
