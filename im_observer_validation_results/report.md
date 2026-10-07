# IM observer validation report

Source: `javascope/kalman_3_versionen_teslog_v1_2809.csv`

This report checks repeatability and model consistency. Without an independent flux or torque reference it does **not** prove absolute estimator accuracy.

| Observer | Plateaus | Frequency RMSE [Hz] | Angle-frequency RMSE [Hz] | Flux ripple [%] | Orbit axis ratio |
|---|---:|---:|---:|---:|---:|
| deterministic | 7 | 0.0229805 | 0.0398 | 1.03063 | 0.986123 |
| full_kalman | 7 | 0.0200939 | 0.194741 | 1.00815 | 0.982863 |
| simplified | 7 | 0.0255692 | 0.0712487 | 0.951815 | 0.985444 |

Interpretation:

- Lower frequency RMSE and flux ripple are preferable at identical plateaus.
- An orbit axis ratio near 1 indicates a circular alpha/beta flux orbit; a low value indicates ellipticity or asymmetry.
- Kalman innovations should be bounded and approximately zero-mean. A low innovation alone is not sufficient if the voltage or machine model is biased.
- Compare positive and negative plateaus separately to expose sign and phase-order errors.
