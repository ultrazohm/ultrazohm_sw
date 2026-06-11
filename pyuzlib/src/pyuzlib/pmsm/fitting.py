from __future__ import annotations

import pandas as pd
from sklearn.linear_model import LinearRegression

from .flux_map import FluxMap


def predict_linear_flux_model_assuming_no_saturation(coefficients, i_d_A, i_q_A):
    """Predict dq flux linkage from the fitted linear no-saturation model."""

    coefficient_row = coefficients.iloc[0]
    psi_q = (
        coefficient_row["intercept_q"]
        + coefficient_row["L_qq"] * i_q_A
        + coefficient_row["L_qd"] * i_d_A
    )
    psi_d = (
        coefficient_row["intercept_d"]
        + coefficient_row["L_dq"] * i_q_A
        + coefficient_row["L_dd"] * i_d_A
    )
    return psi_d, psi_q


def fit_linear_flux_model_assuming_no_saturation(
    flux_map: FluxMap,
    fit_name: str = "Linear Fit",
) -> pd.DataFrame:
    """Fit linear flux-linkage maps in canonical dq notation."""

    data = flux_map.data
    x = data[["i_q_A", "i_d_A"]]

    model_q = LinearRegression()
    model_q.fit(x, data["psi_q_Vs"])
    intercept_q = model_q.intercept_
    coefficients_q = model_q.coef_
    r2_q = model_q.score(x, data["psi_q_Vs"])

    model_d = LinearRegression()
    model_d.fit(x, data["psi_d_Vs"])
    intercept_d = model_d.intercept_
    coefficients_d = model_d.coef_
    r2_d = model_d.score(x, data["psi_d_Vs"])

    return pd.DataFrame(
        {
            "fit_name": [fit_name],
            "intercept_q": [intercept_q],
            "L_qq": [coefficients_q[0]],
            "L_qd": [coefficients_q[1]],
            "r2_q": [r2_q],
            "intercept_d": [intercept_d],
            "L_dd": [coefficients_d[1]],
            "L_dq": [coefficients_d[0]],
            "r2_d": [r2_d],
        }
    )


def compare_linear_flux_model_assuming_no_saturation(
    flux_map: FluxMap,
    fit_name: str = "Linear Fit",
) -> pd.DataFrame:
    """Compare measured flux-map samples with the fitted linear flux model."""

    coefficients = fit_linear_flux_model_assuming_no_saturation(
        flux_map,
        fit_name=fit_name,
    )
    data = flux_map.data.copy()
    psi_d_linear, psi_q_linear = predict_linear_flux_model_assuming_no_saturation(
        coefficients,
        data["i_d_A"],
        data["i_q_A"],
    )

    data["psi_d_linear_Vs"] = psi_d_linear
    data["psi_q_linear_Vs"] = psi_q_linear
    data["psi_d_error_Vs"] = data["psi_d_Vs"] - data["psi_d_linear_Vs"]
    data["psi_q_error_Vs"] = data["psi_q_Vs"] - data["psi_q_linear_Vs"]
    data["fit_name"] = fit_name
    data["r2_d"] = coefficients.loc[0, "r2_d"]
    data["r2_q"] = coefficients.loc[0, "r2_q"]
    return data
