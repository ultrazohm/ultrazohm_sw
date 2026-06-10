from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


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


def _add_subplot(ax: plt.Axes, values: pd.DataFrame, title: str) -> None:
    i_d_values = values.columns.to_numpy()
    i_q_values = values.index.to_numpy()
    mesh_i_d, mesh_i_q = np.meshgrid(i_d_values, i_q_values)
    surface = ax.plot_surface(mesh_i_d, mesh_i_q, values.to_numpy(), cmap="viridis")
    ax.set_title(title)
    ax.set_xlabel("i_d / A")
    ax.set_ylabel("i_q / A")
    ax.set_zlabel("Flux linkage / Vs")
    plt.colorbar(surface, ax=ax, label="Flux linkage / Vs", shrink=0.7)


def plot_flux_map(csv_path: str | Path) -> None:
    csv_path = _resolve_csv_path(csv_path)
    dataframe = pd.read_csv(csv_path).sort_values(["i_q_A", "i_d_A"])
    psi_d = dataframe.pivot(index="i_q_A", columns="i_d_A", values="psi_d_Vs")
    psi_q = dataframe.pivot(index="i_q_A", columns="i_d_A", values="psi_q_Vs")

    fig, axes = plt.subplots(
        1,
        2,
        figsize=(12, 5),
        subplot_kw={"projection": "3d"},
        constrained_layout=True,
    )
    _add_subplot(axes[0], psi_d, r"$\psi_d(i_d, i_q)$")
    _add_subplot(axes[1], psi_q, r"$\psi_q(i_d, i_q)$")
    fig.suptitle(f"Flux map: {csv_path.parent.name}")