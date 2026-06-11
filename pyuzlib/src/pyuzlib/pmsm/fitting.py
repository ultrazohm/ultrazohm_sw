from __future__ import annotations

import pandas as pd
from sklearn.linear_model import LinearRegression

from .flux_map import FluxMap


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
