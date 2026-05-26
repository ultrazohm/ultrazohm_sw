from pathlib import Path

import pandas as pd
from bokeh.layouts import column
from bokeh.plotting import figure, show

SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = next(path for path in (SCRIPT_DIR, *SCRIPT_DIR.parents) if (path / "README.MD").is_file())
CSV_PATH = REPO_ROOT / "docs" / "ceedling_test_output" / "uz" / "uz_pmsm_swmodel" / "uz_pmsm_swmodel_results.csv"
CONFIG_CSV_PATH = REPO_ROOT / "docs" / "ceedling_test_output" / "uz" / "uz_pmsm_swmodel" / "uz_pmsm_swmodel_config.csv"
SUBPLOT_HEIGHT_PX = 210

config_df = pd.read_csv(CONFIG_CSV_PATH, sep=";")
df = pd.read_csv(CSV_PATH, sep=";")
t = df['time']

TOOLS = "pan,wheel_zoom,box_zoom,reset,save"

p_d = figure(
    title="d-axis",
    height=SUBPLOT_HEIGHT_PX,
    sizing_mode="stretch_width",
    x_axis_label="",
    y_axis_label="A / V",
    tools=TOOLS,
)
p_d.line(t, df["output_i_d_A"], line_width=2, color="#26597e", legend_label="i_d (A)")
p_d.line(t, df["input_v_d_V"], line_width=2, color="#ff7f0e", legend_label="v_d (V)")

p_q = figure(
    title="q-axis",
    height=SUBPLOT_HEIGHT_PX,
    sizing_mode="stretch_width",
    x_axis_label="",
    y_axis_label="A / V",
    tools=TOOLS,
    x_range=p_d.x_range,
)
p_q.line(t, df["output_i_q_A"], line_width=2, color="#2ca02c", legend_label="i_q (A)")
p_q.line(t, df["input_v_q_V"], line_width=2, color="#d62728", legend_label="v_q (V)")

p_torque = figure(
    title="Torque",
    height=SUBPLOT_HEIGHT_PX,
    sizing_mode="stretch_width",
    x_axis_label="",
    y_axis_label="Nm",
    tools=TOOLS,
    x_range=p_d.x_range,
)
p_torque.line(t, df["output_torque_Nm"], line_width=2, color="#9467bd", legend_label="torque (Nm)")
p_torque.line(t, df["input_load_torque"], line_width=2, color="#8c564b", legend_label="load torque (Nm)")

p_speed = figure(
    title="Speed",
    height=SUBPLOT_HEIGHT_PX,
    sizing_mode="stretch_width",
    x_axis_label="Time [s]",
    y_axis_label="1/s",
    tools=TOOLS,
    x_range=p_d.x_range,
)
p_speed.line(t, df["output_omega_mech_1_s"], line_width=2, color="#17becf", legend_label="output speed (1/s)")
p_speed.line(t, df["input_omega_mech_1_s"], line_width=2, color="#7f7f7f", legend_label="input speed (1/s)")

layout = column(p_d, p_q, p_torque, p_speed, sizing_mode="stretch_width")
show(layout)
