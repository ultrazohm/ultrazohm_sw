import os
from pathlib import Path

import pandas as pd
from bokeh.layouts import column
from bokeh.models import HoverTool
from bokeh.plotting import figure, show

def _find_repo_root(start_path):
    start_dir = Path(start_path).resolve().parent
    for candidate in (start_dir, *start_dir.parents):
        if (candidate / "README.MD").is_file() and (candidate / "docs").is_dir():
            return str(candidate)
    raise RuntimeError("Could not locate the repository root from this script")


REPO_ROOT = _find_repo_root(__file__)
CSV_PATH = os.path.join("docs", "ceedling_test_output", "uz", "uz_pmsm_swmodel", "uz_pmsm_swmodel_results.csv")
CONFIG_CSV_PATH = os.path.join("docs", "ceedling_test_output", "uz", "uz_pmsm_swmodel", "uz_pmsm_swmodel_config.csv")
CSV_PATH = os.path.join(REPO_ROOT, CSV_PATH)
CONFIG_CSV_PATH = os.path.join(REPO_ROOT, CONFIG_CSV_PATH)
SUBPLOT_HEIGHT_PX = 210
SIGNAL_GROUPS = [
    {
        "title": "d-axis",
        "signals": [
            ("output_i_d_A", "i_d (A)", "#1f77b4"),
            ("input_v_d_V", "v_d (V)", "#ff7f0e"),
        ],
        "ylabel": "A / V",
    },
    {
        "title": "q-axis",
        "signals": [
            ("output_i_q_A", "i_q (A)", "#2ca02c"),
            ("input_v_q_V", "v_q (V)", "#d62728"),
        ],
        "ylabel": "A / V",
    },
    {
        "title": "Torque",
        "signals": [
            ("output_torque_Nm", "torque (Nm)", "#9467bd"),
            ("input_load_torque", "load torque (Nm)", "#8c564b"),
        ],
        "ylabel": "Nm",
    },
    {
        "title": "Speed",
        "signals": [
            ("output_omega_mech_1_s", "output speed (1/s)", "#17becf"),
            ("input_omega_mech_1_s", "input speed (1/s)", "#7f7f7f"),
        ],
        "ylabel": "1/s",
    },
]

def _load_data():
    if not os.path.exists(CONFIG_CSV_PATH):
        raise FileNotFoundError(f"Config file '{CONFIG_CSV_PATH}' not found.")
    if not os.path.exists(CSV_PATH):
        raise FileNotFoundError(f"Results file '{CSV_PATH}' not found.")

    config_df = pd.read_csv(CONFIG_CSV_PATH)
    if "sample_time" in config_df.columns:
        sample_time_column = "sample_time"
    elif "output_sample_time" in config_df.columns:
        sample_time_column = "output_sample_time"
    else:
        raise KeyError("Expected 'sample_time' or 'output_sample_time' in config CSV")
    sample_time = float(config_df[sample_time_column].iloc[0])
    df = pd.read_csv(CSV_PATH)
    if df.empty:
        raise ValueError(f"'{CSV_PATH}' is empty.")

    t = df.index * sample_time
    return t, df


t, df = _load_data()
plots = []
shared_x_range = None

for idx, group in enumerate(SIGNAL_GROUPS):
    figure_kwargs = {
        "title": group["title"],
        "height": SUBPLOT_HEIGHT_PX,
        "sizing_mode": "stretch_width",
        "x_axis_label": "Time [s]" if idx == len(SIGNAL_GROUPS) - 1 else "",
        "y_axis_label": group["ylabel"],
        "tools": "pan,wheel_zoom,box_zoom,reset,save",
        "active_scroll": "wheel_zoom",
    }
    if shared_x_range is not None:
        figure_kwargs["x_range"] = shared_x_range

    p = figure(
        **figure_kwargs,
    )

    plotted = False
    for col, label, color in group["signals"]:
        if col in df:
            renderer = p.line(t, df[col], line_width=2, color=color, legend_label=label)
            p.add_tools(HoverTool(renderers=[renderer], tooltips=[("signal", label), ("x", "$x"), ("y", "$y")]))
            plotted = True

    if not plotted:
        p.text(x=[0], y=[0], text=["No data"], text_color="red")

    p.grid.grid_line_alpha = 0.35
    p.legend.click_policy = "hide"
    p.legend.location = "top_right"

    if shared_x_range is None:
        shared_x_range = p.x_range

    plots.append(p)

layout = column(*plots, sizing_mode="stretch_width")
show(layout)
