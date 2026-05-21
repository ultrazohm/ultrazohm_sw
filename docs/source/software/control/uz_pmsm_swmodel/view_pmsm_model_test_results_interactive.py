import os

import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import plotly.io as pio
pio.templates.default = "plotly_white"

CSV_PATH = "uz_pmsm_swmodel_results.csv"
CONFIG_CSV_PATH = "uz_pmsm_swmodel_config.csv"
FIGURE_HEIGHT_PX = 900
SIGNAL_GROUPS = [
	{
		"title": "d-axis",
		"signals": [
			("output_i_d_A", "i_d (A)"),
			("input_v_d_V", "v_d (V)"),
		],
		"ylabel": "A / V",
	},
	{
		"title": "q-axis",
		"signals": [
			("output_i_q_A", "i_q (A)"),
			("input_v_q_V", "v_q (V)"),
		],
		"ylabel": "A / V",
	},
	{
		"title": "Torque",
		"signals": [
			("output_torque_Nm", "torque (Nm)"),
			("input_load_torque", "load torque (Nm)"),
		],
		"ylabel": "Nm",
	},
	{
		"title": "Speed",
		"signals": [
			("output_omega_mech_1_s", "output speed (1/s)"),
			("input_omega_mech_1_s", "input speed (1/s)"),
		],
		"ylabel": "1/s",
	},
]


def _load_data():
	if not os.path.exists(CONFIG_CSV_PATH):
		raise FileNotFoundError(f"Config file '{CONFIG_CSV_PATH}' not found.")
	if not os.path.exists(CSV_PATH):
		raise FileNotFoundError(f"File '{CSV_PATH}' not found.")

	config_df = pd.read_csv(CONFIG_CSV_PATH)
	sample_time = float(config_df["sample_time"].iloc[0])
	df = pd.read_csv(CSV_PATH)
	if df.empty:
		raise ValueError(f"'{CSV_PATH}' is empty.")
	t = df.index * sample_time
	return t, df


t, df = _load_data()
fig = make_subplots(
	rows=len(SIGNAL_GROUPS),
	cols=1,
	shared_xaxes=True,
	subplot_titles=[group["title"] for group in SIGNAL_GROUPS],
	vertical_spacing=0.04,
)

for row, group in enumerate(SIGNAL_GROUPS, start=1):
	plotted = False
	for col, label in group["signals"]:
		if col in df:
			fig.add_trace(
				go.Scattergl(
					x=t,
					y=df[col],
					mode="lines",
					name=label,
					legendgroup=group["title"],
					showlegend=(row == 1),
				),
				row=row,
				col=1,
			)
			plotted = True

	if not plotted:
		fig.add_annotation(
			x=0.5,
			y=0.5,
			xref=f"x{row} domain",
			yref=f"y{row} domain",
			text="No data",
			showarrow=False,
			font={"color": "red"},
			row=row,
			col=1,
		)

	fig.update_yaxes(title_text=group["ylabel"], row=row, col=1)

fig.update_xaxes(title_text="Time [s]", row=len(SIGNAL_GROUPS), col=1)
fig.update_layout(
	title="PMSM model test results (interactive)",
	hovermode="x unified",
	height=FIGURE_HEIGHT_PX,
	margin={"l": 70, "r": 30, "t": 70, "b": 50},
)

fig
