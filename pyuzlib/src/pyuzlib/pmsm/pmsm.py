from __future__ import annotations

from pathlib import Path
from typing import TYPE_CHECKING

import pandas as pd

from .differential_inductance import DifferentialInductanceMap
from .fitting import (
    compare_linear_flux_model_assuming_no_saturation,
    fit_linear_flux_model_assuming_no_saturation,
)
from .flux_map import FluxMap
from .operation_area import Modulation, OperationArea, calculate_operation_area
from .parameters import PMSMParameters

if TYPE_CHECKING:
    import plotly.graph_objects as go


class PMSM:
    """User-facing PMSM object for data import, fitting, plotting, and export."""

    def __init__(self, parameters: PMSMParameters | None = None) -> None:
        self.parameters = parameters or PMSMParameters()
        self.flux_maps: dict[str, FluxMap] = {}
        self.differential_inductance_maps: dict[str, DifferentialInductanceMap] = {}
        self.results: dict[str, pd.DataFrame] = {}

    def load_parameters_csv(self, csv_path: str | Path) -> PMSMParameters:
        self.parameters = PMSMParameters.from_csv(csv_path)
        return self.parameters

    def update_parameters(self, **values) -> PMSMParameters:
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

    def compare_linear_flux_model(
        self,
        *,
        flux_map: str = "default",
        name: str = "linear_no_saturation_comparison",
        fit_name: str = "Linear Fit",
    ) -> pd.DataFrame:
        result = compare_linear_flux_model_assuming_no_saturation(
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

    def plot_linear_flux_model_comparison(
        self,
        *,
        flux_map: str = "default",
        grid_points: int = 20,
        fit_name: str = "Linear Fit",
    ) -> None:
        from .plotting import plot_linear_flux_model_comparison

        plot_linear_flux_model_comparison(
            self.get_flux_map(flux_map),
            grid_points=grid_points,
            fit_name=fit_name,
        )

    def calculate_differential_inductances(
        self,
        *,
        flux_map: str = "default",
        name: str = "default",
        edge_order: int = 2,
    ) -> DifferentialInductanceMap:
        differential_inductances = DifferentialInductanceMap.from_flux_map(
            self.get_flux_map(flux_map),
            name=name,
            edge_order=edge_order,
        )
        self.differential_inductance_maps[name] = differential_inductances
        self.results[f"{name}_differential_inductances"] = differential_inductances.data
        return differential_inductances

    def get_differential_inductances(
        self,
        name: str = "default",
    ) -> DifferentialInductanceMap:
        try:
            return self.differential_inductance_maps[name]
        except KeyError as exc:
            available_maps = list(self.differential_inductance_maps)
            raise KeyError(
                f"Unknown differential inductance map '{name}'. "
                f"Available maps: {available_maps}"
            ) from exc

    def plot_differential_inductances(
        self,
        differential_inductances: str | DifferentialInductanceMap = "default",
    ) -> None:
        from .plotting import plot_differential_inductances

        if isinstance(differential_inductances, str):
            differential_inductances = self.get_differential_inductances(
                differential_inductances
            )
        plot_differential_inductances(differential_inductances)

    def calculate_operation_area(
        self,
        *,
        v_dc_V: float,
        speed_rpm: float,
        current_limit_A: float | None = None,
        modulation: Modulation = "svpwm",
        grid_points: int = 80,
        current_grid_factor: float = 1.2,
        speeds_rpm=None,
        include_id_zero: bool = True,
        name: str = "operation_area",
    ) -> OperationArea:
        operation_area = calculate_operation_area(
            self.parameters,
            v_dc_V=v_dc_V,
            speed_rpm=speed_rpm,
            current_limit_A=current_limit_A,
            modulation=modulation,
            grid_points=grid_points,
            current_grid_factor=current_grid_factor,
            speeds_rpm=speeds_rpm,
            include_id_zero=include_id_zero,
        )
        self.results[f"{name}_grid"] = operation_area.to_table()
        if operation_area.max_torque is not None:
            self.results[f"{name}_max_torque"] = operation_area.max_torque
        return operation_area

    def plot_operation_area(
        self,
        operation_area: OperationArea,
        *,
        torque_isoline_levels=None,
    ) -> None:
        from .plotting import plot_operation_area

        plot_operation_area(
            operation_area,
            torque_isoline_levels=torque_isoline_levels,
        )

    def plot_max_torque_curve(self, max_torque: pd.DataFrame) -> None:
        from .plotting import plot_max_torque_curve

        plot_max_torque_curve(max_torque)

    def export_parameters_csv(
        self,
        csv_path: str | Path,
        *,
        include_additional: bool = True,
    ) -> None:
        self.parameters.to_csv(csv_path, include_additional=include_additional)

    def export_flux_map_csv(self, csv_path: str | Path, *, flux_map: str = "default") -> None:
        self.get_flux_map(flux_map).to_csv(csv_path)

    def export_differential_inductances_csv(
        self,
        csv_path: str | Path,
        *,
        differential_inductances: str = "default",
    ) -> None:
        self.get_differential_inductances(differential_inductances).to_csv(csv_path)

    def export_result_csv(self, result: str, csv_path: str | Path) -> None:
        try:
            data = self.results[result]
        except KeyError as exc:
            available_results = list(self.results)
            raise KeyError(
                f"Unknown result '{result}'. Available results: {available_results}"
            ) from exc
        data.to_csv(csv_path, index=False)
