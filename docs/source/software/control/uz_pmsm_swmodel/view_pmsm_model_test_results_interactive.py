from pathlib import Path

import pandas as pd
import plotly.graph_objects as go
import plotly.io as pio
from plotly.subplots import make_subplots

pio.templates.default = "plotly_white"

FIGURE_HEIGHT_PX = 900

try:
    _SCRIPT_PATH = Path(__file__).resolve()
except NameError:
    # Sphinx executes plot directives via exec(), where __file__ may be missing.
    _SCRIPT_PATH = Path.cwd()

SCRIPT_DIR = _SCRIPT_PATH.parent if _SCRIPT_PATH.is_file() else _SCRIPT_PATH
REPO_ROOT = next(path for path in (SCRIPT_DIR, *SCRIPT_DIR.parents) if (path / "README.MD").is_file())
CSV_PATH = REPO_ROOT / "docs" / "ceedling_test_output" / "uz" / "uz_pmsm_swmodel" / "uz_pmsm_swmodel_results.csv"
CONFIG_CSV_PATH = REPO_ROOT / "docs" / "ceedling_test_output" / "uz" / "uz_pmsm_swmodel" / "uz_pmsm_swmodel_config.csv"

config_df = pd.read_csv(CONFIG_CSV_PATH, sep=";")
df = pd.read_csv(CSV_PATH, sep=";")
t = df['time']

fig = make_subplots(
	rows=4,
	cols=1,
	shared_xaxes=True,
	subplot_titles=["d-axis", "q-axis", "Torque", "Speed"],
	vertical_spacing=0.04,
)

fig.add_trace(go.Scattergl(x=t, y=df["output_i_d_A"], mode="lines", name="i_d (A)"), row=1, col=1)
fig.add_trace(go.Scattergl(x=t, y=df["input_v_d_V"], mode="lines", name="v_d (V)"), row=1, col=1)
fig.add_trace(go.Scattergl(x=t, y=df["output_i_q_A"], mode="lines", name="i_q (A)"), row=2, col=1)
fig.add_trace(go.Scattergl(x=t, y=df["input_v_q_V"], mode="lines", name="v_q (V)"), row=2, col=1)
fig.add_trace(go.Scattergl(x=t, y=df["output_torque_Nm"], mode="lines", name="torque (Nm)"), row=3, col=1)
fig.add_trace(go.Scattergl(x=t, y=df["input_load_torque"], mode="lines", name="load torque (Nm)"), row=3, col=1)
fig.add_trace(go.Scattergl(x=t, y=df["output_omega_mech_1_s"], mode="lines", name="output speed (1/s)"), row=4, col=1)
fig.add_trace(go.Scattergl(x=t, y=df["input_omega_mech_1_s"], mode="lines", name="input speed (1/s)"), row=4, col=1)

fig.update_yaxes(title_text="A / V", row=1, col=1)
fig.update_yaxes(title_text="A / V", row=2, col=1)
fig.update_yaxes(title_text="Nm", row=3, col=1)
fig.update_yaxes(title_text="1/s", row=4, col=1)
fig.update_xaxes(title_text="Time [s]", row=4, col=1)
fig.update_layout(
	title="PMSM model test results (interactive)",
	hovermode="x unified",
	height=FIGURE_HEIGHT_PX,
	margin={"l": 70, "r": 30, "t": 70, "b": 50},
)

fig
