"""Exercise bundled native modules and lazy Parquet reads without a display."""
import json
from pathlib import Path
from tempfile import TemporaryDirectory

import numpy as np
import pyarrow as pa
import pyarrow.parquet as pq
from imgui_bundle import imgui, implot

from uz_dataviewer.loader import open_file, convert_csv_to_parquet
from uz_dataviewer.model import DataRegistry


def run(report_path):
    with TemporaryDirectory() as directory:
        root = Path(directory)
        t = np.arange(32768, dtype=np.float64) / 1024
        y = np.sin(t).astype(np.float32)
        y[1234], y[23456] = -17, 23
        path = root / "samples.parquet"
        pq.write_table(pa.table({"time": t, "signal": y}), path, row_group_size=4096)
        for backend in ("pyarrow", "polars"):
            for mode in ("memory", "lazy"):
                loaded = open_file(str(path), mode, cache_dir=root / "cache", backend=backend)
                source = loaded.register(DataRegistry()).data_source()
                times, channels = source.read_rows(["signal"], 4000, 4200)
                np.testing.assert_array_equal(times, t[4000:4200])
                np.testing.assert_array_equal(channels["signal"], y[4000:4200])
                points = source.read_plot("signal", t[0], t[-1], 200)
                assert 0 < len(points.values) < len(y)
                assert points.values.min() == -17 and points.values.max() == 23
                indices = np.searchsorted(t, points.time)
                np.testing.assert_array_equal(points.values, y[indices])
        # Exercise the spawned native conversion worker in the frozen executable.
        import threading
        csv = root / 'convert.csv'
        csv.write_text('time;signal\n0;1\n1;2\n')
        converted = root / 'converted.parquet'
        convert_csv_to_parquet(str(csv), str(converted), backend='polars', cancel=threading.Event())
        assert converted.exists()
        context = imgui.create_context()
        plot_context = implot.create_context()
        implot.destroy_context(plot_context)
        imgui.destroy_context(context)
    Path(report_path).write_text(json.dumps({"ok": True}), encoding="utf-8")
