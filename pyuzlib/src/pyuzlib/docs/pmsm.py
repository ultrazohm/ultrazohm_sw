from pathlib import Path

import pandas as pd
import plotly.graph_objects as go

from pyuzlib.pmsm import FluxMap
from pyuzlib.pmsm.fitting import fit_linear_flux_model_assuming_no_saturation


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
