"""Log 10 seconds each in running, control, and stopped mode, then plot lifecheck.

Install from the repository root:
    python -m pip install "./uz_cli[examples]"
Run (without a separate `ultrazohm serve` process):
    python uz_cli/example_python_usage.py

Set PROFILE for startup selections. Firmware names/IDs are generated from the
checkout headers at startup. Run from the repository or pass a generated mapping.
Enable commands request state changes; firmware interlocks still apply.
After each 10-second phase, print the latest reported platform state.
Before closing, return the latest 20 samples as a DataFrame and print them.
"""

import time
from datetime import datetime
from pathlib import Path

import matplotlib.pyplot as plt
import polars as pl
import ultrazohm

DEVICE = "192.168.1.233:1000"
PROFILE = Path(__file__).parent / "profiles" / "standard.json"
# Resolve from this script so the destination does not depend on the working directory.
LOG_ROOT = Path(__file__).resolve().parents[1] / "artifacts" / "live_logs"
LOG_ROOT.mkdir(parents=True, exist_ok=True)
OUTPUT = LOG_ROOT / ("lifecheck-" + datetime.now().strftime("%Y%m%d-%H%M%S-%f"))

# Construction waits for the service and device connection; logging starts below.
acquisition = ultrazohm.Acquisition(
    DEVICE, profile=str(PROFILE),
    output=str(OUTPUT), format="parquet"
)
uz = ultrazohm.Client()

# Startup applies PROFILE["initial_channels"]. Names come from the checkout headers.
# Override a selection before starting any logging if desired.
uz.set_observable("JSO_lifecheck", 1)
# If implemented in your firmware and listed in your custom channel mapping:
# uz.set_observable("JSO_MY_NEW_OBSERVABLE", 5)
uz.start_logging()  # Fast channels only; slow logging is independently optional.

print("Running for 10 seconds...")
uz.enable_system()
time.sleep(1)
print("Reported platform state:", uz.status()["state"]["platform_state"])
time.sleep(9)

print("Control for 10 seconds...")
uz.enable_control()
time.sleep(1)
print("Reported platform state:", uz.status()["state"]["platform_state"])
time.sleep(10)

print("Stopped for 10 seconds (still logging)...")
uz.stop()
time.sleep(1)
print("Reported platform state:", uz.status()["state"]["platform_state"])
time.sleep(9)
latest = uz.get_live_data(last_n_samples=20)  # Independent Polars DataFrame from RAM.
print("Latest 20 samples:")
with pl.Config(tbl_rows=20, tbl_cols=-1):
    print(latest)
uz.stop_logging()  # Finalizes in the background; close() below waits for it.
acquisition.close()  # Wait until data.parquet is complete.

# Nominal sample time uses the profile sampling period (default: 100 microseconds).
data = acquisition.read_recording()
seconds = data["time"]
plt.plot(seconds.to_numpy(), data["JSO_lifecheck"].to_numpy())
plt.xlabel("Time since acquisition started [s]")
plt.ylabel("Lifecheck")
plt.title("UltraZohm lifecheck")
plt.grid(True)
plt.tight_layout()
print(f"Recording saved to {OUTPUT / 'data.parquet'}")
plt.show()
