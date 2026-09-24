
import matplotlib.pyplot as plt
import pandas as pd
from pyuzlib.docs.test_results import pmsm_swmodel_result_paths

CSV_PATH, CONFIG_CSV_PATH = pmsm_swmodel_result_paths()

config_df = pd.read_csv(CONFIG_CSV_PATH, sep=";")
df = pd.read_csv(CSV_PATH, sep=";")
t = df['time']

fig, axes = plt.subplots(4, 1, figsize=(12, 10), sharex=True)

axes[0].plot(t, df["output_d"], label="i_d (A)", color="tab:blue", linewidth=1.5)
axes[0].plot(t, df["input_d"], label="v_d (V)", color="tab:orange", linewidth=1.5)
axes[0].set_title("d-axis")
axes[0].set_ylabel("A / V")
axes[0].grid(True, linestyle="--", linewidth=0.6, alpha=0.6)
axes[0].legend(loc="best")

axes[1].plot(t, df["output_q"], label="i_q (A)", color="tab:green", linewidth=1.5)
axes[1].plot(t, df["input_q"], label="v_q (V)", color="tab:red", linewidth=1.5)
axes[1].set_title("q-axis")
axes[1].set_ylabel("A / V")
axes[1].grid(True, linestyle="--", linewidth=0.6, alpha=0.6)
axes[1].legend(loc="best")

axes[2].plot(t, df["output_torque_Nm"], label="torque (Nm)", color="tab:purple", linewidth=1.5)
axes[2].plot(t, df["input_load_torque"], label="load torque (Nm)", color="tab:brown", linewidth=1.5)
axes[2].set_title("Torque")
axes[2].set_ylabel("Nm")
axes[2].grid(True, linestyle="--", linewidth=0.6, alpha=0.6)
axes[2].legend(loc="best")

axes[3].plot(t, df["output_omega_mech_1_s"], label="output speed (1/s)", color="tab:cyan", linewidth=1.5)
axes[3].plot(t, df["input_omega_mech_1_s"], label="input speed (1/s)", color="tab:gray", linewidth=1.5)
axes[3].set_title("Speed")
axes[3].set_ylabel("1/s")
axes[3].set_xlabel("Time [s]")
axes[3].grid(True, linestyle="--", linewidth=0.6, alpha=0.6)
axes[3].legend(loc="best")

fig.suptitle("PMSM model test results")
fig.tight_layout(rect=(0, 0, 1, 0.97))
plt.show()
