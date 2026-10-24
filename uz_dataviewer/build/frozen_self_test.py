"""Exercise bundled native modules and lazy Parquet reads without a display."""
import json
from pathlib import Path
from tempfile import TemporaryDirectory

import numpy as np
import pyarrow as pa
import pyarrow.parquet as pq
from imgui_bundle import imgui, implot

from uz_dataviewer.sources import ParquetSource


def run(report_path):
    with TemporaryDirectory() as directory:
        root = Path(directory)
        t = np.arange(32768, dtype=np.float64) / 1024
        y = np.sin(t).astype(np.float32)
        y[1234], y[23456] = -17, 23
        path = root / "samples.parquet"
        pq.write_table(pa.table({"time": t, "signal": y}), path, row_group_size=4096)
        source = ParquetSource(path, cache_dir=root / "cache")
        times, channels = source.read_rows(["signal"], 4000, 4200)
        np.testing.assert_array_equal(times, t[4000:4200])
        np.testing.assert_array_equal(channels["signal"], y[4000:4200])
        points = source.read_plot("signal", t[0], t[-1], 200)
        assert 0 < len(points.values) < len(y)
        assert points.values.min() == -17 and points.values.max() == 23
        indices = np.searchsorted(t, points.time)
        np.testing.assert_array_equal(points.values, y[indices])
        context = imgui.create_context()
        plot_context = implot.create_context()
        implot.destroy_context(plot_context)
        imgui.destroy_context(context)
    Path(report_path).write_text(json.dumps({"ok": True}), encoding="utf-8")
