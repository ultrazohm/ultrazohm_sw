from __future__ import annotations

import plotly.graph_objects as go
from plotly.subplots import make_subplots

from .flux_map import FluxMap


def plot_flux_map(flux_map: FluxMap) -> None:
    import matplotlib.pyplot as plt
    import numpy as np

    fig, axes = plt.subplots(
        1,
        2,
        figsize=(12, 5),
        subplot_kw={"projection": "3d"},
        constrained_layout=True,
    )

    for ax, values, title in (
        (axes[0], flux_map.psi_d, r"$\psi_d(i_d, i_q)$"),
        (axes[1], flux_map.psi_q, r"$\psi_q(i_d, i_q)$"),
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

    title = flux_map.source_path.parent.name if flux_map.source_path is not None else flux_map.name
    fig.suptitle(f"Flux map: {title}")


def plot_flux_map_plotly(flux_map: FluxMap) -> go.Figure:
    import numpy as np

    psi_d = flux_map.psi_d
    psi_q = flux_map.psi_q
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
    title = flux_map.source_path.parent.name if flux_map.source_path is not None else flux_map.name
    fig.update_layout(title=f"Flux map: {title}")
    return fig
