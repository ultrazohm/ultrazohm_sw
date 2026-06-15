"""Headless GUI smoke test - renders the full app for a number of frames.

Not collected by pytest (needs a display). Run with a real display or xvfb:

    xvfb-run -a python tests/smoke_gui.py

Generates sample data, loads it, populates time-series plots (with cursors
and downsampling active) and an FFT plot, renders 60 frames and exits.
Exit code 0 means every render path executed without raising.
"""

import sys
import tempfile
import time as time_module

import numpy as np


def make_sample_files(directory: str) -> tuple[str, str]:
    import pyarrow as pa
    import pyarrow.parquet as papq

    fs = 100_000
    t = np.arange(fs * 5) / fs
    ch1 = np.sin(2 * np.pi * 50 * t) + 0.2 * np.sin(2 * np.pi * 1000 * t)
    ch2 = np.sign(np.sin(2 * np.pi * 25 * t))
    parquet_path = f"{directory}/smoke.parquet"
    papq.write_table(pa.table({"time": t, "ch1": ch1, "ch2": ch2}), parquet_path)

    csv_path = f"{directory}/smoke.csv"
    with open(csv_path, "w") as f:
        f.write("time;ch1;\n")
        for i in range(50_000):
            f.write(f"{t[i]:.9f};{ch1[i]:.9f};\n")
    return parquet_path, csv_path


def main() -> int:
    from imgui_bundle import immapp

    from uz_dataviewer import app
    from uz_dataviewer.core.data_store import SignalRef
    from uz_dataviewer.ui.app_state import PLOT_TYPE_FFT, AppState

    with tempfile.TemporaryDirectory() as directory:
        parquet_path, csv_path = make_sample_files(directory)

        state = AppState()
        state.store.load_files_async([parquet_path, csv_path])
        deadline = time_module.time() + 30
        while time_module.time() < deadline and (
            state.store.loading or not state.store.runs
        ):
            state.store.poll()
            time_module.sleep(0.05)
        assert len(state.store.runs) == 2, "sample files did not load"

        run_ids = sorted(state.store.runs)
        plot0 = state.plots[0]
        plot0.series = [
            SignalRef(run_ids[0], "ch1"),
            SignalRef(run_ids[0], "ch2"),
            SignalRef(run_ids[1], "ch1"),
        ]
        plot0.show_cursors = True
        fft_plot = state.plots[2]
        fft_plot.plot_type = PLOT_TYPE_FFT
        fft_plot.fft_source_plot = 0
        fft_plot.fft_log_y = True
        state.link_time_axes = True
        state.shared_x_range = (0.0, 5.0)

        params = app._make_runner_params(state, smoke_frames=60)
        params.app_window_params.restore_previous_geometry = False
        immapp.run(params, immapp.AddOnsParams(with_implot=True))

        errors = [e for e in state.console.entries() if e.level >= 3]
        if errors:
            for entry in errors:
                print("CONSOLE ERROR:", entry.format(), file=sys.stderr)
            return 1
        print("smoke test OK: 60 frames rendered, no console errors")
        return 0


if __name__ == "__main__":
    sys.exit(main())
