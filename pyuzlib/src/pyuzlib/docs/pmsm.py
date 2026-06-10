from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from sklearn.linear_model import LinearRegression


def _resolve_csv_path(csv_path: str | Path) -> Path:
    csv_path = Path(csv_path)
    candidates = [
        csv_path,
        Path.cwd() / csv_path,
        Path(__file__).resolve().parents[4] / csv_path,
    ]

    for candidate in candidates:
        if candidate.exists():
            return candidate.resolve()

    raise FileNotFoundError(f"Could not locate flux map CSV: {csv_path}")


def _load_flux_map(csv_path: str | Path) -> tuple[Path, pd.DataFrame, pd.DataFrame, pd.DataFrame]:
    csv_path = _resolve_csv_path(csv_path)
    dataframe = pd.read_csv(csv_path).sort_values(["i_q_A", "i_d_A"])
    psi_d = dataframe.pivot(index="i_q_A", columns="i_d_A", values="psi_d_Vs")
    psi_q = dataframe.pivot(index="i_q_A", columns="i_d_A", values="psi_q_Vs")
    return csv_path, dataframe, psi_d, psi_q


def plot_flux_map(csv_path: str | Path) -> None:
    csv_path, _, psi_d, psi_q = _load_flux_map(csv_path)

    fig, axes = plt.subplots(
        1,
        2,
        figsize=(12, 5),
        subplot_kw={"projection": "3d"},
        constrained_layout=True,
    )

    for ax, values, title in (
        (axes[0], psi_d, r"$\psi_d(i_d, i_q)$"),
        (axes[1], psi_q, r"$\psi_q(i_d, i_q)$"),
    ):
        i_d_values = values.columns.to_numpy()
        i_q_values = values.index.to_numpy()
        mesh_i_d, mesh_i_q = np.meshgrid(i_d_values, i_q_values)
        surface = ax.plot_surface(mesh_i_d, mesh_i_q, values.to_numpy(), cmap="viridis")
        ax.set_title(title)
        ax.set_xlabel("i_d / A")
        ax.set_ylabel("i_q / A")
        ax.set_zlabel("Flux linkage / Vs")
        plt.colorbar(surface, ax=ax, label="Flux linkage / Vs", shrink=0.7)

    fig.suptitle(f"Flux map: {csv_path.parent.name}")


def plot_flux_map_plotly(csv_path: str | Path) -> go.Figure:
    csv_path, _, psi_d, psi_q = _load_flux_map(csv_path)
    mesh_i_d_d, mesh_i_q_d = np.meshgrid(psi_d.columns.to_numpy(), psi_d.index.to_numpy())
    mesh_i_d_q, mesh_i_q_q = np.meshgrid(psi_q.columns.to_numpy(), psi_q.index.to_numpy())

    fig = make_subplots(
        rows=1,
        cols=2,
        specs=[[{"type": "surface"}, {"type": "surface"}]],
        subplot_titles=(r"psi_d(i_d, i_q)", r"psi_q(i_d, i_q)"),
    )
    fig.add_trace(
        go.Surface(
            x=mesh_i_d_d,
            y=mesh_i_q_d,
            z=psi_d.to_numpy(),
            colorscale="Viridis",
            showscale=False,
        ),
        row=1,
        col=1,
    )
    fig.add_trace(
        go.Surface(
            x=mesh_i_d_q,
            y=mesh_i_q_q,
            z=psi_q.to_numpy(),
            colorscale="Viridis",
            showscale=False,
        ),
        row=1,
        col=2,
    )
    fig.update_layout(
        title=f"Flux map: {csv_path.parent.name}",
    )
    return fig

def L_dd_L_qq_from_flux_map_assuming_no_saturation(csv_path: str | Path, fit_name: str = "Linear Fit") -> pd.DataFrame:
    """
    Function to fit two linear regression models (one for psi_q and one for psi_d)
    and return a table with the coefficients for both fits in a single row.

    Parameters:
    csv_path (str | Path): Path to flux_map.csv.
    fit_name (str): Name of the fit to be added to the coefficients table.

    Returns:
    DataFrame: A table containing the fit name, coefficients, and R^2 values for the linear regression.
    """
    _, flux_map, _, _ = _load_flux_map(csv_path)

    X = flux_map[["i_q_A", "i_d_A"]]
    y_q = flux_map["psi_q_Vs"]

    # Fit the first linear regression model for psi_q
    model_q = LinearRegression()
    model_q.fit(X, y_q)

    # Extract the intercept and coefficients for psi_q
    intercept_q = model_q.intercept_
    coefficients_q = model_q.coef_
    r2_q = model_q.score(X, y_q)

    # Prepare the data for psi_d
    y_d = flux_map["psi_d_Vs"]

    # Fit the second linear regression model for psi_d
    model_d = LinearRegression()
    model_d.fit(X, y_d)

    # Extract the intercept and coefficients for psi_d
    intercept_d = model_d.intercept_
    coefficients_d = model_d.coef_
    r2_d = model_d.score(X, y_d)

    # Create a DataFrame for the coefficients table with custom column names
    coefficients_table = pd.DataFrame({
        "fit_name": [fit_name],
        "intercept_q": [intercept_q],
        "L_qq": [coefficients_q[0]],  # Gradient for i_q_A (psi_q_Vs)
        "L_qd": [coefficients_q[1]],  # Gradient for i_d_A (psi_q_Vs)
        "r2_q": [r2_q],
        "intercept_d": [intercept_d],
        "L_dd": [coefficients_d[1]],  # Gradient for i_d_A (psi_d_Vs)
        "L_dq": [coefficients_d[0]],  # Gradient for i_q_A (psi_d_Vs)
        "r2_d": [r2_d],
    })

    return coefficients_table