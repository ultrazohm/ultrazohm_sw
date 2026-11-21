"""Explicit Python control methods. Metadata is verified against operation definitions."""

from __future__ import annotations

from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .client import NodeHandle, RunHandle, ViewHandle


class ViewerMethods:
    def backend(self, name: str):
        "IO backend for subsequent opens, exports and CSV conversion: pyarrow or polars (desktop only)."
        return self._invoke("backend", {"name": name})

    def cache_budget(self, mib: int):
        "Shared timestamp/summary RAM cache budget in MiB."
        return self._invoke("cache_budget", {"mib": mib})

    def clear_plot(self, plot: int, *, view: ViewHandle | None = None):
        "Remove all signals from a subplot."
        return self._invoke("clear_plot", {"plot": plot, "view": view})

    def convert(
        self,
        src: str,
        dst: str | None = None,
        *,
        axis_column: str | None = None,
        axis_domain: str | None = None,
    ):
        "Stream-convert CSV to Parquet using the selected backend; dst defaults to src with a .parquet extension. Existing destinations and empty inputs are rejected."
        return self._invoke(
            "convert",
            {
                "src": src,
                "dst": dst,
                "axis_column": axis_column,
                "axis_domain": axis_domain,
            },
        )

    def cursors(self, plot: int, on: bool, *, view: ViewHandle | None = None):
        "Toggle two measurement cursors (Δx / frequency readout) on a subplot."
        return self._invoke("cursors", {"plot": plot, "on": on, "view": view})

    def disk_cache(self, on: bool):
        "Persist indexes, summaries and CSV conversions for subsequent opens (default: false)."
        return self._invoke("disk_cache", {"on": on})

    def export_data(
        self,
        plot: int,
        path: str,
        relative: bool | None = None,
        *,
        view: ViewHandle | None = None,
    ):
        "Export a subplot's signals to CSV (relative=true zeroes the start time)."
        return self._invoke(
            "export_data",
            {"plot": plot, "path": path, "relative": relative, "view": view},
        )

    def fft(self):
        "Recompute and focus the FFT window."
        return self._invoke("fft", {})

    def fft_clear(self):
        "Remove all signals from the FFT window."
        return self._invoke("fft_clear", {})

    def fft_export(self, path: str):
        "Export the FFT spectra to CSV."
        return self._invoke("fft_export", {"path": path})

    def fft_follow(self, target: str | int):
        "Set the FFT time window source (custom / full / plot_N)."
        return self._invoke("fft_follow", {"target": target})

    def fft_hann(self, on: bool):
        "Toggle the FFT Hann window."
        return self._invoke("fft_hann", {"on": on})

    def fft_logx(self, on: bool):
        "Toggle the FFT log X axis."
        return self._invoke("fft_logx", {"on": on})

    def fft_logy(self, on: bool):
        "Toggle the FFT log Y axis."
        return self._invoke("fft_logy", {"on": on})

    def fft_range(self, min: float, max: float):
        "Set the FFT custom time window."
        return self._invoke("fft_range", {"min": min, "max": max})

    def fft_remove(self, run: RunHandle, signal: str):
        "Remove a signal from the FFT window."
        return self._invoke("fft_remove", {"run": run, "signal": signal})

    def fft_remove_dc(self, on: bool):
        "Toggle FFT DC removal."
        return self._invoke("fft_remove_dc", {"on": on})

    def fft_source(self, run: RunHandle, signal: str):
        "Add a signal to the FFT window (it can show several at once)."
        return self._invoke("fft_source", {"run": run, "signal": signal})

    def fft_xlim(self, min: float, max: float):
        "Set the FFT plot's X-axis view limits."
        return self._invoke("fft_xlim", {"min": min, "max": max})

    def hist_bins(self, n: int):
        "Set the Histogram bin count (1..100000)."
        return self._invoke("hist_bins", {"n": n})

    def hist_clear(self):
        "Remove all signals from the Histogram window."
        return self._invoke("hist_clear", {})

    def hist_export(self, path: str):
        "Export the histogram bins to CSV."
        return self._invoke("hist_export", {"path": path})

    def hist_follow(self, target: str | int):
        "Set the Histogram time window source (custom / full / plot_N)."
        return self._invoke("hist_follow", {"target": target})

    def hist_range(self, min: float, max: float):
        "Set the Histogram custom time window."
        return self._invoke("hist_range", {"min": min, "max": max})

    def hist_remove(self, run: RunHandle, signal: str):
        "Remove a signal from the Histogram window."
        return self._invoke("hist_remove", {"run": run, "signal": signal})

    def hist_source(self, run: RunHandle, signal: str):
        "Add a signal to the Histogram window (it can show several at once)."
        return self._invoke("hist_source", {"run": run, "signal": signal})

    def hist_xlim(self, min: float, max: float):
        "Set the Histogram plot's X-axis view limits."
        return self._invoke("hist_xlim", {"min": min, "max": max})

    def histogram(self):
        "Recompute and focus the Histogram window."
        return self._invoke("histogram", {})

    def load_plugins(self, dir: str | None = None):
        "Load external node plugins from a directory (or the configured defaults)."
        return self._invoke("load_plugins", {"dir": dir})

    def loading_mode(self, mode: str):
        "Storage policy for subsequent opens: memory or lazy."
        return self._invoke("loading_mode", {"mode": mode})

    def node_add(self, kind: str):
        "Add a transform node (fft, math, filter, shift, or an installed plugin kind)."
        return self._invoke("node_add", {"kind": kind})

    def node_eval(self, node: NodeHandle | None = None):
        "Evaluate the graph (or one node + its inputs), materializing derived signals."
        return self._invoke("node_eval", {"node": node})

    def node_link(self, src: NodeHandle, dst: NodeHandle, slot: int | None = None):
        "Connect to a zero-based input slot (default: first free slot)."
        return self._invoke("node_link", {"src": src, "dst": dst, "slot": slot})

    def node_pos(self, node: NodeHandle, x: float, y: float):
        "Set a node's canvas position."
        return self._invoke("node_pos", {"node": node, "x": x, "y": y})

    def node_remove(self, node: NodeHandle):
        "Remove a node (and its derived run, if any)."
        return self._invoke("node_remove", {"node": node})

    def node_rename(self, node: NodeHandle, name: str):
        "Rename a node (its derived run takes the new name)."
        return self._invoke("node_rename", {"node": node, "name": name})

    def node_set(self, node: NodeHandle, key: str, value: str):
        "Set a transform node parameter (e.g. node_set(node_2, cutoff, 1000))."
        return self._invoke("node_set", {"node": node, "key": key, "value": value})

    def node_source(self, run: RunHandle, signal: str):
        "Add a source node wrapping a loaded signal (the graph's input)."
        return self._invoke("node_source", {"run": run, "signal": signal})

    def node_unlink(self, src: NodeHandle, dst: NodeHandle, slot: int | None = None):
        "Disconnect a node link at a zero-based slot (default: all matching slots)."
        return self._invoke("node_unlink", {"src": src, "dst": dst, "slot": slot})

    def normalize_time(self, run: RunHandle, start: float | None = None):
        "Shift a run so its first sample sits at start (default 0)."
        return self._invoke("normalize_time", {"run": run, "start": start})

    def remove_run(self, run: RunHandle):
        "Remove a loaded run and its plots."
        return self._invoke("remove_run", {"run": run})

    def remove_signal(
        self, plot: int, run: RunHandle, signal: str, *, view: ViewHandle | None = None
    ):
        "Remove a signal from a subplot."
        return self._invoke(
            "remove_signal", {"plot": plot, "run": run, "signal": signal, "view": view}
        )

    def reset_time(self, run: RunHandle):
        "Restore a run's original (un-normalised) timestamps."
        return self._invoke("reset_time", {"run": run})

    def reset_view(self, plot: int, *, view: ViewHandle | None = None):
        "Auto-fit a subplot to its data extent."
        return self._invoke("reset_view", {"plot": plot, "view": view})

    def set_active(self, run: RunHandle, on: bool):
        "Show/hide a run without removing it."
        return self._invoke("set_active", {"run": run, "on": on})

    def set_axis(
        self,
        plot: int,
        run: RunHandle,
        signal: str,
        side: str,
        *,
        view: ViewHandle | None = None,
    ):
        "Assign a signal to the left or right Y axis of a subplot."
        return self._invoke(
            "set_axis",
            {"plot": plot, "run": run, "signal": signal, "side": side, "view": view},
        )

    def set_cursors(
        self, plot: int, x1: float, x2: float, *, view: ViewHandle | None = None
    ):
        "Place the two cursors at x1 and x2 (enables cursors)."
        return self._invoke(
            "set_cursors", {"plot": plot, "x1": x1, "x2": x2, "view": view}
        )

    def set_export_relative(
        self, plot: int, on: bool, *, view: ViewHandle | None = None
    ):
        "Toggle 'start time at 0' for a subplot's CSV export."
        return self._invoke(
            "set_export_relative", {"plot": plot, "on": on, "view": view}
        )

    def set_max_points(self, n: int, *, view: ViewHandle | None = None):
        "Max points drawn per signal (downsample budget)."
        return self._invoke("set_max_points", {"n": n, "view": view})

    def set_plot_type(self, plot: int, type: str, *, view: ViewHandle | None = None):
        "Set a subplot's type (line/scatter/stairs/xy)."
        return self._invoke("set_plot_type", {"plot": plot, "type": type, "view": view})

    def set_spy_rect(
        self,
        plot: int,
        xmin: float,
        ymin: float,
        xmax: float,
        ymax: float,
        *,
        view: ViewHandle | None = None,
    ):
        "Position the spy rectangle (enables spy)."
        return self._invoke(
            "set_spy_rect",
            {
                "plot": plot,
                "xmin": xmin,
                "ymin": ymin,
                "xmax": xmax,
                "ymax": ymax,
                "view": view,
            },
        )

    def set_x_lim(
        self, plot: int, min: float, max: float, *, view: ViewHandle | None = None
    ):
        "Set a subplot's X-axis limits."
        return self._invoke(
            "set_x_lim", {"plot": plot, "min": min, "max": max, "view": view}
        )

    def set_xy(
        self, plot: int, run: RunHandle, signal: str, *, view: ViewHandle | None = None
    ):
        "Use a signal as the X axis (XY plot) for a subplot."
        return self._invoke(
            "set_xy", {"plot": plot, "run": run, "signal": signal, "view": view}
        )

    def set_xy_style(self, plot: int, style: str, *, view: ViewHandle | None = None):
        "Set the XY plot draw style: Line, Markers, or Both."
        return self._invoke(
            "set_xy_style", {"plot": plot, "style": style, "view": view}
        )

    def set_y_lim(
        self, plot: int, min: float, max: float, *, view: ViewHandle | None = None
    ):
        "Set a subplot's Y-axis limits."
        return self._invoke(
            "set_y_lim", {"plot": plot, "min": min, "max": max, "view": view}
        )

    def show_samples(self, plot: int, on: bool, *, view: ViewHandle | None = None):
        "Toggle per-sample markers on a subplot."
        return self._invoke("show_samples", {"plot": plot, "on": on, "view": view})

    def spy(self, plot: int, on: bool, *, view: ViewHandle | None = None):
        "Toggle the spy (drag-rect zoom inset) on a subplot."
        return self._invoke("spy", {"plot": plot, "on": on, "view": view})
