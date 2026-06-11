from __future__ import annotations

from pathlib import Path
from typing import TYPE_CHECKING

import pandas as pd

from .fitting import fit_linear_flux_model_assuming_no_saturation
from .flux_map import FluxMap
from .parameters import PMSMParameters

if TYPE_CHECKING:
    import plotly.graph_objects as go


class PMSM:
    """User-facing PMSM object for data import, fitting, plotting, and export."""

    def __init__(self, parameters: PMSMParameters | None = None) -> None:
        self.parameters = parameters or PMSMParameters()
        self.flux_maps: dict[str, FluxMap] = {}
        self.results: dict[str, pd.DataFrame] = {}

    def load_parameters_csv(self, csv_path: str | Path) -> PMSMParameters:
        self.parameters = PMSMParameters.from_csv(csv_path)
        return self.parameters

    def update_parameters(self, **values: float) -> PMSMParameters:
        self.parameters.update(**values)
        return self.parameters

    def load_flux_map_csv(
        self,
        csv_path: str | Path,
        *,
        name: str = "default",
        columns: dict[str, str] | None = None,
        i_d_col: str | None = None,
        i_q_col: str | None = None,
        psi_d_col: str | None = None,
        psi_q_col: str | None = None,
    ) -> FluxMap:
        loaded_flux_map = FluxMap.from_csv(
            csv_path,
            name=name,
            columns=columns,
            i_d_col=i_d_col,
            i_q_col=i_q_col,
            psi_d_col=psi_d_col,
            psi_q_col=psi_q_col,
        )
        self.flux_maps[name] = loaded_flux_map
        return loaded_flux_map

    def get_flux_map(self, name: str = "default") -> FluxMap:
        try:
            return self.flux_maps[name]
        except KeyError as exc:
            available_maps = list(self.flux_maps)
            raise KeyError(f"Unknown flux map '{name}'. Available maps: {available_maps}") from exc

    def fit_linear_flux_model(
        self,
        *,
        flux_map: str = "default",
        name: str = "linear_no_saturation",
        fit_name: str = "Linear Fit",
    ) -> pd.DataFrame:
        result = fit_linear_flux_model_assuming_no_saturation(
            self.get_flux_map(flux_map),
            fit_name=fit_name,
        )
        self.results[name] = result
        return result

    def plot_flux_map(self, flux_map: str = "default") -> None:
        from .plotting import plot_flux_map

        plot_flux_map(self.get_flux_map(flux_map))

    def plot_flux_map_plotly(self, flux_map: str = "default") -> "go.Figure":
        from .plotting import plot_flux_map_plotly

        return plot_flux_map_plotly(self.get_flux_map(flux_map))

    def export_parameters_csv(
        self,
        csv_path: str | Path,
        *,
        include_additional: bool = True,
    ) -> None:
        self.parameters.to_csv(csv_path, include_additional=include_additional)

    def export_flux_map_csv(self, csv_path: str | Path, *, flux_map: str = "default") -> None:
        self.get_flux_map(flux_map).to_csv(csv_path)

    def export_result_csv(self, result: str, csv_path: str | Path) -> None:
        try:
            data = self.results[result]
        except KeyError as exc:
            available_results = list(self.results)
            raise KeyError(
                f"Unknown result '{result}'. Available results: {available_results}"
            ) from exc
        data.to_csv(csv_path, index=False)
