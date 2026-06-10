from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots


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


def _load_flux_map(csv_path: str | Path) -> tuple[Path, pd.DataFrame, pd.DataFrame]:
    csv_path = _resolve_csv_path(csv_path)
    dataframe = pd.read_csv(csv_path).sort_values(["i_q_A", "i_d_A"])
    psi_d = dataframe.pivot(index="i_q_A", columns="i_d_A", values="psi_d_Vs")
    psi_q = dataframe.pivot(index="i_q_A", columns="i_d_A", values="psi_q_Vs")
    return csv_path, psi_d, psi_q


def plot_flux_map(csv_path: str | Path) -> None:
    csv_path, psi_d, psi_q = _load_flux_map(csv_path)

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
    csv_path, psi_d, psi_q = _load_flux_map(csv_path)
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