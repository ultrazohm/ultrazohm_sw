"""Mutable UI state shared between the panels (single-threaded UI access)."""

from __future__ import annotations

from dataclasses import dataclass, field

from uz_dataviewer.core.console import Console
from uz_dataviewer.core.data_store import DataStore, SignalRef
from uz_dataviewer.core.downsample import ViewportDownsampler

PLOT_TYPE_TIME = "Time series"
PLOT_TYPE_FFT = "FFT"
PLOT_TYPES = (PLOT_TYPE_TIME, PLOT_TYPE_FFT)

GRID_PRESETS = ((1, 1), (1, 2), (2, 1), (2, 2), (2, 3), (3, 3))
MAX_PLOTS = max(r * c for r, c in GRID_PRESETS)

SIGNAL_PAYLOAD_TYPE = "UZ_SIGNAL"


@dataclass
class PlotConfig:
    plot_type: str = PLOT_TYPE_TIME
    series: list[SignalRef] = field(default_factory=list)

    # Cursor (region selection) state for time-series plots.
    show_cursors: bool = False
    cursor_a: float | None = None
    cursor_b: float | None = None

    # Visible x-range of the last rendered frame (time plots only).
    last_x_range: tuple[float, float] | None = None

    # FFT plot settings.
    fft_source_plot: int = -1
    fft_series_index: int = 0
    fft_window: str = "hann"
    fft_use_cursors: bool = True
    fft_log_x: bool = False
    fft_log_y: bool = False

    def cursor_range(self) -> tuple[float, float] | None:
        if self.cursor_a is None or self.cursor_b is None:
            return None
        low, high = sorted((self.cursor_a, self.cursor_b))
        return (low, high)


class AppState:
    def __init__(self) -> None:
        self.console = Console()
        self.store = DataStore(self.console)
        self.downsampler = ViewportDownsampler()

        self.grid_preset_index = 3  # 2x2 like the plotly dataviewer default
        self.plots: list[PlotConfig] = [PlotConfig() for _ in range(MAX_PLOTS)]

        self.link_time_axes = False
        self.shared_x_range: tuple[float, float] | None = None

        self._last_store_revision = -1

    @property
    def grid(self) -> tuple[int, int]:
        return GRID_PRESETS[self.grid_preset_index]

    @property
    def visible_plot_count(self) -> int:
        rows, cols = self.grid
        return rows * cols

    def on_new_frame(self) -> None:
        """Per-frame housekeeping: fold async loads, prune stale series."""
        self.store.poll()
        if self.store.revision != self._last_store_revision:
            self._last_store_revision = self.store.revision
            self.downsampler.invalidate()
            valid = set()
            for run_id, run in self.store.runs.items():
                for signal in run.signals:
                    valid.add(SignalRef(run_id, signal))
            for plot in self.plots:
                plot.series = [ref for ref in plot.series if ref in valid]

    def series_label(self, ref: SignalRef) -> str:
        run = self.store.runs.get(ref.run_id)
        if run is None:
            return ref.signal
        multiple_runs = len(self.store.runs) > 1
        return f"{ref.signal} ({run.name})" if multiple_runs else ref.signal

    def add_series(self, plot_index: int, ref: SignalRef) -> None:
        plot = self.plots[plot_index]
        if ref not in plot.series:
            plot.series.append(ref)
            self.console.info(
                f"Added '{self.series_label(ref)}' to plot {plot_index + 1}."
            )
