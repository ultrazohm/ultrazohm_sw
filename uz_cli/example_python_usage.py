"""Log 10 seconds each in running, control, and stopped mode, then plot lifecheck.

Install from the repository root:
    python -m pip install "./uz_cli[examples]"
Run (without a separate `ultrazohm serve` process):
    python uz_cli/example_python_usage.py

Set PROFILE for startup selections and CHANNEL_MAPPING for firmware names/IDs.
The JSON is loaded at runtime; changing it does not require rebuilding Rust.
Enable commands request state changes; firmware interlocks still apply.
"""

import time
from datetime import datetime
from pathlib import Path

import matplotlib.pyplot as plt
import polars as pl
from ultrazohm import Acquisition, Client

DEVICE = "192.168.1.233:1000"
PROFILE = Path(__file__).parent / "profiles" / "standard.json"
CHANNEL_MAPPING = Path(__file__).parent / "channel_mappings" / "default.json"
# For your own firmware, point these to your two custom JSON files.
OUTPUT = Path("lifecheck-" + datetime.now().strftime("%Y%m%d-%H%M%S-%f"))

# Rust connects in the background; logging starts explicitly below.
acquisition = Acquisition(
    DEVICE, profile=str(PROFILE), channel_mapping=str(CHANNEL_MAPPING),
    output=str(OUTPUT), format="parquet"
)
uz = Client()
connected = False

try:
    # Startup is asynchronous: wait until the control API is ready.
    deadline = time.monotonic() + 10
    while True:
        if acquisition.is_finished():
            acquisition.close()  # Report a connection or logging error.
            raise RuntimeError("Acquisition ended during startup")
        try:
            uz.status()
            connected = True
            break
        except RuntimeError:
            if time.monotonic() >= deadline:
                raise TimeoutError("UltraZohm did not become ready")
            time.sleep(0.1)

    # Startup applies PROFILE["initial_channels"]. Names come from CHANNEL_MAPPING.
    # Override a selection before starting any logging if desired.
    uz.set_observable("JSO_lifecheck", 1)
    # If implemented in your firmware and listed in your custom channel mapping:
    # uz.set_observable("JSO_MY_NEW_OBSERVABLE", 5)
    uz.start_logging()  # Fast channels only; slow logging is independently optional.

    print("Running for 10 seconds...")
    uz.enable_system()
    time.sleep(10)

    print("Control for 10 seconds...")
    uz.enable_control()
    time.sleep(10)

    print("Stopped for 10 seconds (still logging)...")
    uz.stop()
    time.sleep(10)
    uz.stop_logging()  # Finalizes in the background; close() below waits for it.
finally:
    # Also request Stop if interrupted; always finish writing the log.
    try:
        if connected and not acquisition.is_finished():
            uz.stop()
    finally:
        acquisition.close()  # Wait until data.parquet is complete.

# Nominal sample time uses the profile sampling period (default: 100 microseconds).
data = pl.read_parquet(OUTPUT / "data.parquet")
seconds = data["time"]
plt.plot(seconds.to_numpy(), data["JSO_lifecheck"].to_numpy())
plt.xlabel("Time since acquisition started [s]")
plt.ylabel("Lifecheck")
plt.title("UltraZohm lifecheck")
plt.grid(True)
plt.tight_layout()
print(f"Recording saved to {OUTPUT / 'data.parquet'}")
plt.show()
