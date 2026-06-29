from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path

import pandas as pd


CANONICAL_FLUX_MAP_COLUMNS = ("i_d_A", "i_q_A", "psi_d_Vs", "psi_q_Vs")
DEFAULT_FLUX_MAP_COLUMNS = {
    "i_d": "i_d_A",
    "i_q": "i_q_A",
    "psi_d": "psi_d_Vs",
    "psi_q": "psi_q_Vs",
}


def resolve_csv_path(csv_path: str | Path) -> Path:
    csv_path = Path(csv_path)
    candidates = [
        csv_path,
        Path.cwd() / csv_path,
        Path(__file__).resolve().parents[4] / csv_path,
    ]

    for candidate in candidates:
        if candidate.exists():
            return candidate.resolve()

    raise FileNotFoundError(f"Could not locate CSV file: {csv_path}")


@dataclass
class FluxMap:
    """Flux map stored as a canonical long-form table."""

    data: pd.DataFrame
    source_path: Path | None = None
    name: str = "default"
    metadata: dict[str, str] = field(default_factory=dict)

    @classmethod
    def from_csv(
        cls,
        csv_path: str | Path,
        *,
        name: str = "default",
        columns: dict[str, str] | None = None,
        i_d_col: str | None = None,
        i_q_col: str | None = None,
        psi_d_col: str | None = None,
        psi_q_col: str | None = None,
    ) -> "FluxMap":
        csv_path = resolve_csv_path(csv_path)
        data = pd.read_csv(csv_path)
        column_mapping = DEFAULT_FLUX_MAP_COLUMNS.copy()
        if columns is not None:
            column_mapping.update(columns)
        explicit_columns = {
            "i_d": i_d_col,
            "i_q": i_q_col,
            "psi_d": psi_d_col,
            "psi_q": psi_q_col,
        }
        column_mapping.update(
            {key: value for key, value in explicit_columns.items() if value is not None}
        )

        missing_source_columns = set(column_mapping.values()) - set(data.columns)
        if missing_source_columns:
            raise ValueError(f"Missing flux-map CSV columns: {sorted(missing_source_columns)}")

        canonical_data = data.rename(
            columns={
                column_mapping["i_d"]: "i_d_A",
                column_mapping["i_q"]: "i_q_A",
                column_mapping["psi_d"]: "psi_d_Vs",
                column_mapping["psi_q"]: "psi_q_Vs",
            }
        )
        canonical_data = canonical_data.loc[:, list(CANONICAL_FLUX_MAP_COLUMNS)]
        canonical_data = (
            canonical_data.astype(float)
            .sort_values(["i_q_A", "i_d_A"])
            .reset_index(drop=True)
        )
        cls._validate(canonical_data)
        return cls(data=canonical_data, source_path=csv_path, name=name)

    @staticmethod
    def _validate(data: pd.DataFrame) -> None:
        missing_columns = set(CANONICAL_FLUX_MAP_COLUMNS) - set(data.columns)
        if missing_columns:
            raise ValueError(f"Missing canonical flux-map columns: {sorted(missing_columns)}")
        duplicated_points = data.duplicated(subset=["i_d_A", "i_q_A"])
        if duplicated_points.any():
            raise ValueError("Flux map contains duplicate i_d/i_q operating points")

    @property
    def psi_d(self) -> pd.DataFrame:
        return self.data.pivot(index="i_q_A", columns="i_d_A", values="psi_d_Vs")

    @property
    def psi_q(self) -> pd.DataFrame:
        return self.data.pivot(index="i_q_A", columns="i_d_A", values="psi_q_Vs")

    def to_csv(self, csv_path: str | Path) -> None:
        out = self.data.copy()
        out.insert(0, "operating_point", range(len(out)))
        out.to_csv(csv_path, index=False)
