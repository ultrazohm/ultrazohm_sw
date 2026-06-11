from __future__ import annotations

from dataclasses import dataclass
from typing import Literal

import numpy as np
import pandas as pd
from scipy.optimize import NonlinearConstraint, minimize

from .parameters import PMSMParameters

Modulation = Literal["svpwm", "block"]


@dataclass
class OperationArea:
    """PMSM operation-area data for one DC-link voltage and current limit."""

    i_d_A: np.ndarray
    i_q_A: np.ndarray
    torque_Nm: np.ndarray
    v_dq_V: np.ndarray
    current_limit_A: float
    v_dc_V: float
    v_max_V: float
    speed_rpm: float
    speed_el_rad_per_sec: float
    modulation: Modulation
    max_torque: pd.DataFrame | None = None

    def to_table(self) -> pd.DataFrame:
        return pd.DataFrame(
            {
                "i_d_A": self.i_d_A.ravel(),
                "i_q_A": self.i_q_A.ravel(),
                "torque_Nm": self.torque_Nm.ravel(),
                "v_dq_V": self.v_dq_V.ravel(),
            }
        )


def modulation_voltage_limit(v_dc_V: float, modulation: Modulation = "svpwm") -> float:
    if modulation == "svpwm":
        return v_dc_V / np.sqrt(3.0)
    if modulation == "block":
        return v_dc_V * 2.0 / np.pi
    raise ValueError(f"Unknown modulation '{modulation}'. Use 'svpwm' or 'block'.")


def calculate_torque(parameters: PMSMParameters, i_d_A, i_q_A):
    _require_linear_pmsm_parameters(parameters)
    return (
        1.5
        * parameters.polePairs
        * (
            parameters.Psi_PM_Vs * i_q_A
            + (parameters.Ld_Henry - parameters.Lq_Henry) * i_d_A * i_q_A
        )
    )


def calculate_v_dq(
    parameters: PMSMParameters,
    i_d_A,
    i_q_A,
    speed_el_rad_per_sec: float,
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    _require_linear_pmsm_parameters(parameters)
    v_d = parameters.R_ph_Ohm * i_d_A - speed_el_rad_per_sec * parameters.Lq_Henry * i_q_A
    v_q = parameters.R_ph_Ohm * i_q_A + speed_el_rad_per_sec * (
        parameters.Ld_Henry * i_d_A + parameters.Psi_PM_Vs
    )
    return v_d, v_q, np.sqrt(v_d**2 + v_q**2)


def calculate_operation_area(
    parameters: PMSMParameters,
    *,
    v_dc_V: float,
    speed_rpm: float,
    current_limit_A: float | None = None,
    modulation: Modulation = "svpwm",
    grid_points: int = 80,
    current_grid_factor: float = 1.2,
    speeds_rpm: np.ndarray | None = None,
    include_id_zero: bool = True,
) -> OperationArea:
    _require_linear_pmsm_parameters(parameters)
    if v_dc_V <= 0.0:
        raise ValueError("v_dc_V must be greater than zero")
    if grid_points < 2:
        raise ValueError("grid_points must be at least 2")
    if current_grid_factor <= 0.0:
        raise ValueError("current_grid_factor must be greater than zero")

    current_limit_A = _resolve_current_limit(parameters, current_limit_A)
    v_max_V = modulation_voltage_limit(v_dc_V, modulation)
    speed_el_rad_per_sec = mechanical_rpm_to_electrical_rad_per_sec(parameters, speed_rpm)

    current_span = current_grid_factor * current_limit_A
    i_d_values = np.linspace(-current_span, current_span, grid_points)
    i_q_values = np.linspace(-current_span, current_span, grid_points)
    i_d_grid, i_q_grid = np.meshgrid(i_d_values, i_q_values)
    torque_grid = calculate_torque(parameters, i_d_grid, i_q_grid)
    _, _, v_dq_grid = calculate_v_dq(parameters, i_d_grid, i_q_grid, speed_el_rad_per_sec)

    max_torque = None
    if speeds_rpm is not None:
        max_torque = calculate_max_torque_curve(
            parameters,
            speeds_rpm=speeds_rpm,
            v_dc_V=v_dc_V,
            current_limit_A=current_limit_A,
            modulation=modulation,
            include_id_zero=include_id_zero,
        )

    return OperationArea(
        i_d_A=i_d_grid,
        i_q_A=i_q_grid,
        torque_Nm=torque_grid,
        v_dq_V=v_dq_grid,
        current_limit_A=current_limit_A,
        v_dc_V=v_dc_V,
        v_max_V=v_max_V,
        speed_rpm=speed_rpm,
        speed_el_rad_per_sec=speed_el_rad_per_sec,
        modulation=modulation,
        max_torque=max_torque,
    )


def calculate_max_torque_curve(
    parameters: PMSMParameters,
    *,
    speeds_rpm: np.ndarray,
    v_dc_V: float,
    current_limit_A: float | None = None,
    modulation: Modulation = "svpwm",
    include_id_zero: bool = True,
) -> pd.DataFrame:
    _require_linear_pmsm_parameters(parameters)
    current_limit_A = _resolve_current_limit(parameters, current_limit_A)
    v_max_V = modulation_voltage_limit(v_dc_V, modulation)

    rows = []
    for speed_rpm in speeds_rpm:
        speed_el_rad_per_sec = mechanical_rpm_to_electrical_rad_per_sec(parameters, speed_rpm)
        optimal = maximize_torque_at_speed(
            parameters,
            speed_el_rad_per_sec=speed_el_rad_per_sec,
            v_max_V=v_max_V,
            current_limit_A=current_limit_A,
            force_id_zero=False,
        )
        optimal.update(
            {
                "speed_rpm": float(speed_rpm),
                "speed_el_rad_per_sec": float(speed_el_rad_per_sec),
                "modulation": modulation,
                "strategy": "optimal",
            }
        )
        rows.append(optimal)

        if include_id_zero:
            id_zero = maximize_torque_at_speed(
                parameters,
                speed_el_rad_per_sec=speed_el_rad_per_sec,
                v_max_V=v_max_V,
                current_limit_A=current_limit_A,
                force_id_zero=True,
            )
            id_zero.update(
                {
                    "speed_rpm": float(speed_rpm),
                    "speed_el_rad_per_sec": float(speed_el_rad_per_sec),
                    "modulation": modulation,
                    "strategy": "id_zero",
                }
            )
            rows.append(id_zero)

    data = pd.DataFrame(rows)
    data["current_angle_deg"] = np.degrees(np.arctan2(data["i_d_A"], data["i_q_A"]))
    return data[
        [
            "speed_rpm",
            "speed_el_rad_per_sec",
            "modulation",
            "strategy",
            "i_d_A",
            "i_q_A",
            "current_angle_deg",
            "max_torque_Nm",
            "v_dq_V",
            "current_A",
            "success",
        ]
    ]


def maximize_torque_at_speed(
    parameters: PMSMParameters,
    *,
    speed_el_rad_per_sec: float,
    v_max_V: float,
    current_limit_A: float,
    force_id_zero: bool = False,
) -> dict[str, float | bool]:
    _require_linear_pmsm_parameters(parameters)

    if force_id_zero:

        def objective(x):
            return -float(calculate_torque(parameters, 0.0, x[0]))

        def voltage_margin(x):
            _, _, v_dq = calculate_v_dq(parameters, 0.0, x[0], speed_el_rad_per_sec)
            return float(v_max_V - v_dq)

        constraints = [NonlinearConstraint(voltage_margin, 0.0, np.inf)]
        result = minimize(
            objective,
            x0=[0.9 * current_limit_A],
            bounds=[(-current_limit_A, current_limit_A)],
            constraints=constraints,
            method="SLSQP",
        )
        i_d_A = 0.0
        i_q_A = float(result.x[0]) if result.success else np.nan
    else:

        def objective(x):
            return -float(calculate_torque(parameters, x[0], x[1]))

        def voltage_margin(x):
            _, _, v_dq = calculate_v_dq(parameters, x[0], x[1], speed_el_rad_per_sec)
            return float(v_max_V - v_dq)

        def current_margin(x):
            return float(current_limit_A - np.hypot(x[0], x[1]))

        constraints = [
            NonlinearConstraint(voltage_margin, 0.0, np.inf),
            NonlinearConstraint(current_margin, 0.0, np.inf),
        ]
        result = minimize(
            objective,
            x0=[0.0, 0.9 * current_limit_A],
            bounds=[(-current_limit_A, current_limit_A), (-current_limit_A, current_limit_A)],
            constraints=constraints,
            method="SLSQP",
        )
        i_d_A = float(result.x[0]) if result.success else np.nan
        i_q_A = float(result.x[1]) if result.success else np.nan

    if result.success:
        torque_Nm = float(calculate_torque(parameters, i_d_A, i_q_A))
        _, _, v_dq = calculate_v_dq(parameters, i_d_A, i_q_A, speed_el_rad_per_sec)
        v_dq_V = float(v_dq)
        current_A = float(np.hypot(i_d_A, i_q_A))
    else:
        torque_Nm = np.nan
        v_dq_V = np.nan
        current_A = np.nan

    return {
        "i_d_A": i_d_A,
        "i_q_A": i_q_A,
        "max_torque_Nm": torque_Nm,
        "v_dq_V": v_dq_V,
        "current_A": current_A,
        "success": bool(result.success),
    }


def mechanical_rpm_to_electrical_rad_per_sec(
    parameters: PMSMParameters,
    speed_rpm: float,
) -> float:
    _require_linear_pmsm_parameters(parameters)
    return float(speed_rpm * parameters.polePairs * 2.0 * np.pi / 60.0)


def _resolve_current_limit(
    parameters: PMSMParameters,
    current_limit_A: float | None,
) -> float:
    current_limit_A = parameters.I_max_Ampere if current_limit_A is None else current_limit_A
    if current_limit_A is None or current_limit_A <= 0.0:
        raise ValueError("current_limit_A must be greater than zero")
    return float(current_limit_A)


def _require_linear_pmsm_parameters(parameters: PMSMParameters) -> None:
    required = (
        "R_ph_Ohm",
        "Ld_Henry",
        "Lq_Henry",
        "Psi_PM_Vs",
        "polePairs",
    )
    missing = [name for name in required if getattr(parameters, name) is None]
    if missing:
        raise ValueError(f"Missing PMSM parameters for operation-area calculation: {missing}")
