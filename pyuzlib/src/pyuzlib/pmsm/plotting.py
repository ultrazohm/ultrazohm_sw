from __future__ import annotations

import plotly.graph_objects as go
from plotly.subplots import make_subplots

from .flux_map import FluxMap
from .operation_area import OperationArea


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


def plot_operation_area(
    operation_area: OperationArea,
    *,
    torque_isoline_levels=None,
) -> None:
    import matplotlib.pyplot as plt
    import numpy as np

    fig, ax = plt.subplots(figsize=(8, 6), constrained_layout=True)
    torque_contour = ax.contourf(
        operation_area.i_d_A,
        operation_area.i_q_A,
        operation_area.torque_Nm,
        levels=50,
        cmap="viridis",
    )
    fig.colorbar(torque_contour, ax=ax, label="Torque / Nm")

    torque_isoline_levels = (
        _default_torque_isoline_levels(operation_area.torque_Nm)
        if torque_isoline_levels is None
        else torque_isoline_levels
    )
    if len(torque_isoline_levels) > 0:
        torque_isolines = ax.contour(
            operation_area.i_d_A,
            operation_area.i_q_A,
            operation_area.torque_Nm,
            levels=torque_isoline_levels,
            colors="white",
            linestyles="dashed",
            linewidths=0.8,
        )
        ax.clabel(torque_isolines, fmt="%g Nm", colors="white")

    theta = np.linspace(0.0, 2.0 * np.pi, 500)
    ax.plot(
        operation_area.current_limit_A * np.cos(theta),
        operation_area.current_limit_A * np.sin(theta),
        color="red",
        linewidth=2,
        label="Current limit",
    )

    voltage_contour = ax.contour(
        operation_area.i_d_A,
        operation_area.i_q_A,
        operation_area.v_dq_V,
        levels=[operation_area.v_max_V],
        colors="blue",
        linestyles="dashed",
    )
    ax.clabel(
        voltage_contour,
        fmt={operation_area.v_max_V: f"{operation_area.v_max_V:.2f} V"},
    )

    if operation_area.max_torque is not None:
        optimal = operation_area.max_torque[operation_area.max_torque["strategy"] == "optimal"]
        ax.plot(
            optimal["i_d_A"],
            optimal["i_q_A"],
            color="white",
            marker="o",
            linewidth=1.5,
            label="Optimal torque curve",
        )

    ax.set_xlabel("i_d / A")
    ax.set_ylabel("i_q / A")
    ax.set_title(
        f"PMSM operation area at {operation_area.speed_rpm:g} rpm, "
        f"{operation_area.v_dc_V:g} V DC ({operation_area.modulation})"
    )
    ax.grid(True)
    ax.legend()


def _default_torque_isoline_levels(torque_Nm) -> list[float]:
    import numpy as np

    torque_min = float(np.nanmin(torque_Nm))
    torque_max = float(np.nanmax(torque_Nm))
    if not np.isfinite(torque_min) or not np.isfinite(torque_max):
        return []
    if torque_min == torque_max:
        return []

    lower = np.ceil(torque_min)
    upper = np.floor(torque_max)
    if upper > lower and (upper - lower) <= 30.0:
        return np.arange(lower, upper + 1.0, 1.0).tolist()
    return np.linspace(torque_min, torque_max, 12).tolist()


def plot_max_torque_curve(max_torque) -> None:
    import matplotlib.pyplot as plt

    fig, axes = plt.subplots(3, 1, figsize=(8, 12), sharex=True, constrained_layout=True)
    successful = max_torque[max_torque["success"]]

    for (modulation, strategy), group in successful.groupby(["modulation", "strategy"]):
        label = f"{modulation} {strategy}"
        axes[0].plot(group["speed_rpm"], group["max_torque_Nm"], marker="o", label=label)
        axes[1].plot(group["speed_rpm"], group["i_d_A"], marker="o", label=f"{label} i_d")
        axes[1].plot(group["speed_rpm"], group["i_q_A"], marker="x", label=f"{label} i_q")
        axes[2].plot(group["speed_rpm"], group["current_angle_deg"], marker="o", label=label)

    axes[0].set_ylabel("Max torque / Nm")
    axes[0].set_title("Maximum torque over speed")
    axes[1].set_ylabel("Current / A")
    axes[1].set_title("Optimal dq currents")
    axes[2].set_xlabel("Mechanical speed / rpm")
    axes[2].set_ylabel("Current angle / degree")
    axes[2].set_title("Current angle")

    for axis in axes:
        axis.grid(True)
        axis.legend()
