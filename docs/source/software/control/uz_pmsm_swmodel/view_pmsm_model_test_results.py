

import pandas as pd
import matplotlib.pyplot as plt
import os
from pathlib import Path

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
SIGNAL_GROUPS = [
    {
        "title": "d-axis",
        "signals": [
            ("output_i_d_A", "i_d (A)", "tab:blue"),
            ("input_v_d_V", "v_d (V)", "tab:orange"),
        ],
        "ylabel": "A / V",
    },
    {
        "title": "q-axis",
        "signals": [
            ("output_i_q_A", "i_q (A)", "tab:green"),
            ("input_v_q_V", "v_q (V)", "tab:red"),
        ],
        "ylabel": "A / V",
    },
    {
        "title": "Torque",
        "signals": [
            ("output_torque_Nm", "torque (Nm)", "tab:purple"),
            ("input_load_torque", "load torque (Nm)", "tab:brown"),
        ],
        "ylabel": "Nm",
    },
    {
        "title": "Speed",
        "signals": [
            ("output_omega_mech_1_s", "output speed (1/s)", "tab:cyan"),
            ("input_omega_mech_1_s", "input speed (1/s)", "tab:gray"),
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


def build_interactive_figure():
    from plotly.subplots import make_subplots
    import plotly.graph_objects as go

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
        for col, label, _color in group["signals"]:
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
        height=320 * len(SIGNAL_GROUPS),
    )
    return fig

def main():
    try:
        t, df = _load_data()
    except Exception as e:
        print(f"Error loading PMSM model data: {e}")
        return

    fig, axes = plt.subplots(len(SIGNAL_GROUPS), 1, figsize=(12, 10), sharex=True)
    if len(SIGNAL_GROUPS) == 1:
        axes = [axes]

    for ax, group in zip(axes, SIGNAL_GROUPS):
        plotted = False
        for col, label, color in group["signals"]:
            if col in df:
                ax.plot(t, df[col], label=label, color=color, linewidth=1.5)
                plotted = True
        ax.set_title(group["title"])
        ax.set_ylabel(group["ylabel"])
        ax.grid(True, linestyle="--", linewidth=0.6, alpha=0.6)
        if plotted:
            ax.legend(loc="best")
        else:
            ax.text(0.5, 0.5, "No data", ha="center", va="center", transform=ax.transAxes, color="red")

    axes[-1].set_xlabel("Time [s]")
    fig.suptitle("PMSM model test results")
    fig.tight_layout(rect=(0, 0, 1, 0.97))
    plt.show()

if __name__ == "__main__":
    main()
