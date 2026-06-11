from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

import pandas as pd

from .flux_map import FluxMap


CANONICAL_DIFFERENTIAL_INDUCTANCE_COLUMNS = (
    "operating_point",
    "i_d_A",
    "i_q_A",
    "L_dd_H",
    "L_dq_H",
    "L_qd_H",
    "L_qq_H",
)


@dataclass
class DifferentialInductanceMap:
    """Differential inductance maps stored as a canonical long-form table."""

    data: pd.DataFrame
    source_flux_map: FluxMap | None = None
    name: str = "default"

    @classmethod
    def from_flux_map(
        cls,
        flux_map: FluxMap,
        *,
        name: str = "default",
        edge_order: int = 2,
    ) -> "DifferentialInductanceMap":
        psi_d = flux_map.psi_d
        psi_q = flux_map.psi_q
        _validate_complete_grid(psi_d, "psi_d")
        _validate_complete_grid(psi_q, "psi_q")

        i_d_A = psi_d.columns.to_numpy(dtype=float)
        i_q_A = psi_d.index.to_numpy(dtype=float)
        effective_edge_order = _effective_edge_order(edge_order, len(i_d_A), len(i_q_A))

        L_dq_H, L_dd_H = _gradient(
            psi_d.to_numpy(dtype=float),
            i_q_A,
            i_d_A,
            edge_order=effective_edge_order,
        )
        L_qq_H, L_qd_H = _gradient(
            psi_q.to_numpy(dtype=float),
            i_q_A,
            i_d_A,
            edge_order=effective_edge_order,
        )

        table = _maps_to_table(
            i_d_A=i_d_A,
            i_q_A=i_q_A,
            L_dd_H=L_dd_H,
            L_dq_H=L_dq_H,
            L_qd_H=L_qd_H,
            L_qq_H=L_qq_H,
        )
        return cls(data=table, source_flux_map=flux_map, name=name)

    @property
    def L_dd(self) -> pd.DataFrame:
        return self.data.pivot(index="i_q_A", columns="i_d_A", values="L_dd_H")

    @property
    def L_dq(self) -> pd.DataFrame:
        return self.data.pivot(index="i_q_A", columns="i_d_A", values="L_dq_H")

    @property
    def L_qd(self) -> pd.DataFrame:
        return self.data.pivot(index="i_q_A", columns="i_d_A", values="L_qd_H")

    @property
    def L_qq(self) -> pd.DataFrame:
        return self.data.pivot(index="i_q_A", columns="i_d_A", values="L_qq_H")

    def to_csv(self, csv_path: str | Path) -> None:
        self.data.to_csv(csv_path, index=False)


def _gradient(values, i_q_A, i_d_A, *, edge_order: int):
    import numpy as np

    return np.gradient(values, i_q_A, i_d_A, edge_order=edge_order)


def _effective_edge_order(edge_order: int, i_d_count: int, i_q_count: int) -> int:
    if edge_order not in (1, 2):
        raise ValueError("edge_order must be 1 or 2")
    if min(i_d_count, i_q_count) < 2:
        raise ValueError("Differential inductance calculation needs at least two grid points per axis")
    if edge_order == 2 and min(i_d_count, i_q_count) < 3:
        return 1
    return edge_order


def _maps_to_table(
    *,
    i_d_A,
    i_q_A,
    L_dd_H,
    L_dq_H,
    L_qd_H,
    L_qq_H,
) -> pd.DataFrame:
    import numpy as np

    mesh_i_d, mesh_i_q = np.meshgrid(i_d_A, i_q_A)
    table = pd.DataFrame(
        {
            "i_d_A": mesh_i_d.ravel(),
            "i_q_A": mesh_i_q.ravel(),
            "L_dd_H": L_dd_H.ravel(),
            "L_dq_H": L_dq_H.ravel(),
            "L_qd_H": L_qd_H.ravel(),
            "L_qq_H": L_qq_H.ravel(),
        }
    )
    table.insert(0, "operating_point", range(len(table)))
    return table.loc[:, list(CANONICAL_DIFFERENTIAL_INDUCTANCE_COLUMNS)]


def _validate_complete_grid(values: pd.DataFrame, map_name: str) -> None:
    if values.isna().to_numpy().any():
        raise ValueError(
            f"{map_name} does not form a complete rectangular i_d/i_q grid"
        )
