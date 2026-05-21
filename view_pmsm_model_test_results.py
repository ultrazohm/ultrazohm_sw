

import pandas as pd
import matplotlib.pyplot as plt
import os

# Constants
SAMPLE_TIME = 1.0 / 10000.0
CSV_PATH = "uz_pmsm_swmodel_results.csv"
SIGNAL_GROUPS = [
    {
        "title": "d-axis",
        "signals": [
            ("output_i_d_A", "i_d [A]", "tab:blue"),
            ("input_v_d_V", "v_d [V]", "tab:orange"),
        ],
        "ylabel": "A / V",
    },
    {
        "title": "q-axis",
        "signals": [
            ("output_i_q_A", "i_q [A]", "tab:green"),
            ("input_v_q_V", "v_q [V]", "tab:red"),
        ],
        "ylabel": "A / V",
    },
    {
        "title": "Torque",
        "signals": [
            ("output_torque_Nm", "torque [Nm]", "tab:purple"),
            ("input_load_torque", "load torque [Nm]", "tab:brown"),
        ],
        "ylabel": "Nm",
    },
    {
        "title": "Speed",
        "signals": [
            ("output_omega_mech_1_s", "output speed [1/s]", "tab:cyan"),
            ("input_omega_mech_1_s", "input speed [1/s]", "tab:gray"),
        ],
        "ylabel": "1/s",
    },
]

def main():
    if not os.path.exists(CSV_PATH):
        print(f"Error: File '{CSV_PATH}' not found.")
        return
    try:
        df = pd.read_csv(CSV_PATH)
    except Exception as e:
        print(f"Error reading '{CSV_PATH}': {e}")
        return
    if df.empty:
        print(f"Error: '{CSV_PATH}' is empty.")
        return
    t = df.index * SAMPLE_TIME

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
