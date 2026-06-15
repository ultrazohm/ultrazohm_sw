"""Central application state shared across panels."""

from __future__ import annotations

import enum
import math
import os
from concurrent.futures import Future, ThreadPoolExecutor
from dataclasses import dataclass, field

from . import webbridge
from .commands import CommandRegistry
from .console import Console
from .loader import load_file
from .model import DataRegistry, Run, Signal
from .nodes import NodeGraph

# Identifies a signal across runs: (run_id, signal_name).
SignalRef = tuple[int, str]


class PlotType(enum.Enum):
    LINE = "Line"
    SCATTER = "Scatter"
    STAIRS = "Stairs"
    XY = "XY"

    @classmethod
    def labels(cls) -> list[str]:
        return [t.value for t in cls]


@dataclass
class SubplotCell:
    """One cell of the plot grid and the signals dropped into it."""

    signals: list[SignalRef] = field(default_factory=list)
    plot_type: PlotType = PlotType.LINE
    fit_pending: bool = True
    """Request a one-shot auto-fit to the data extent on the next render.

    Set whenever the signal set changes so the X axis snaps to the real time
    range instead of ImPlot's default ``(0, 1)`` window.
    """

    show_samples: bool = False
    """Draw a marker at every sample (line plots)."""

    spy: bool = False
    """Show a drag-rect zoom inset below the main plot (the 'spy' tool)."""

    spy_rect: tuple[float, float, float, float] | None = None
    """Persisted spy rectangle as ``(x_min, y_min, x_max, y_max)``."""

    xy_source: SignalRef | None = None
    """Signal used as the X axis when ``plot_type`` is :attr:`PlotType.XY`."""

    y2_signals: list[SignalRef] = field(default_factory=list)
    """Signals drawn against the secondary (right) Y axis."""

    cursors: bool = False
    """Show two draggable vertical cursors with a Δx / frequency readout."""

    cursor_x: tuple[float, float] | None = None
    """Persisted cursor X positions as ``(x1, x2)``."""

    export_relative: bool = False
    """When exporting this cell, rebase the time column to start at 0."""

    pending_x_lim: tuple[float, float] | None = None
    """One-shot X-axis limits to apply next render (from ``set_x_lim``)."""

    pending_y_lim: tuple[float, float] | None = None
    """One-shot Y-axis limits to apply next render (from ``set_y_lim``)."""

    def add(self, ref: SignalRef) -> bool:
        if ref not in self.signals:
            self.signals.append(ref)
            self.fit_pending = True
            return True
        return False

    def remove(self, ref: SignalRef) -> None:
        if ref in self.signals:
            self.signals.remove(ref)
        if ref in self.y2_signals:
            self.y2_signals.remove(ref)


# Grid presets offered in the toolbar, as (rows, cols).
GRID_PRESETS: list[tuple[int, int]] = [(1, 1), (1, 2), (2, 1), (2, 2), (1, 3), (3, 1)]


@dataclass
class AnalysisConfig:
    """Shared state for an analysis window (FFT, histogram, ...).

    Each holds a set of source signals (dragged in from the tree or plots) and a
    time window that either follows a chosen subplot or is entered manually.
    """

    sources: list[SignalRef] = field(default_factory=list)
    follow_plot: int = 1
    """Which subplot's X range to use as the window. ``0`` = *Custom*
    (use ``x_min``/``x_max``); ``N`` = follow ``plot_N``."""
    x_min: float = 0.0
    x_max: float = 0.0
    compute_requested: bool = False
    """Set by drag-drop / a command so the window recomputes next frame."""
    pending_x_lim: tuple[float, float] | None = None
    """One-shot X-axis view limits to apply next render (from ``*_xlim``)."""


@dataclass
class FftConfig(AnalysisConfig):
    """FFT window: amplitude spectra of several signals at once."""

    remove_dc: bool = True
    window: bool = True
    log_x: bool = False
    log_y: bool = False


@dataclass
class HistogramConfig(AnalysisConfig):
    """Histogram window: value distributions of several signals at once."""

    bins: int = 50


class AppState:
    def __init__(self) -> None:
        self.registry = DataRegistry()
        self.console = Console()
        # The command registry routes every discrete GUI action and console
        # input through one place, so the console doubles as a replayable log.
        self.commands = CommandRegistry()

        self.rows = 1
        self.cols = 1
        self.cells: list[SubplotCell] = [SubplotCell() for _ in range(self.rows * self.cols)]

        self.link_x = True
        self.shared_x: tuple[float, float] | None = None
        # Current X range of each time-series subplot, keyed by 1-based plot
        # number, refreshed every frame. Lets the FFT explicitly follow a chosen
        # plot rather than "whichever was last hovered".
        self.plot_x_ranges: dict[int, tuple[float, float]] = {}

        # Downsampling target: max points drawn per signal. When the visible
        # window holds fewer samples than this, all raw points are shown.
        self.max_points = 2000
        # Set each frame: True if any signal was actually decimated.
        self.downsampling_active = False

        self.fft = FftConfig()
        self.histogram = HistogramConfig()

        # Dataflow node graph: transforms produce derived runs (see nodes.py).
        self.nodes = NodeGraph()

        # The signal currently being dragged from the navigation tree, picked up
        # by the plot panel on drop.
        self.dragged_ref: SignalRef | None = None

        self._executor = ThreadPoolExecutor(max_workers=2)
        self._pending: list[tuple[Future[Run], str]] = []

        # Signal that the docking layout should focus an analysis window this frame.
        self.focus_fft = False
        self.focus_histogram = False

    # -- grid management ----------------------------------------------------
    @property
    def cell_count(self) -> int:
        return self.rows * self.cols

    def set_grid(self, rows: int, cols: int) -> None:
        """Resize the grid, preserving the assignments of surviving cells."""
        new_cells = [SubplotCell() for _ in range(rows * cols)]
        for i in range(min(len(new_cells), len(self.cells))):
            new_cells[i] = self.cells[i]
        self.rows, self.cols, self.cells = rows, cols, new_cells

    # -- file loading (async on desktop, synchronous in the browser) -------
    def request_load(self, path: str) -> None:
        path = os.path.abspath(path)
        # Echo the equivalent command so GUI-triggered (async) loads appear in
        # the console transcript just like a typed/scripted `load(...)`.
        self.commands.echo(self, "load", [path])
        self.console.info(f"Loading {os.path.basename(path)} ...")
        if webbridge.IS_WEB:
            # Pyodide has no usable worker threads -- load on the main thread.
            try:
                self._report_loaded(load_file(path, self.registry))
            except Exception as exc:  # noqa: BLE001 - surfaced to the console
                self.console.error(f"Failed to load {os.path.basename(path)}: {exc}")
            return
        future = self._executor.submit(load_file, path, self.registry)
        self._pending.append((future, path))

    def load_sync(self, path: str) -> Run | None:
        """Load a file on the calling thread and report it.

        Used by the ``load`` command and by session restore/replay so that any
        commands that follow (``add_signal`` ...) can immediately resolve the
        run. Errors are raised as :class:`commands.CommandError`-compatible
        ``ValueError`` so the dispatcher logs them.
        """
        path = os.path.abspath(path)
        self.console.info(f"Loading {os.path.basename(path)} ...")
        try:
            run = load_file(path, self.registry)
        except Exception as exc:  # noqa: BLE001 - surfaced to the console
            self.console.error(f"Failed to load {os.path.basename(path)}: {exc}")
            return None
        self._report_loaded(run)
        return run

    def add_run_from_arrays(
        self,
        label: str,
        path: str,
        time: "np.ndarray",
        signals: dict,
        units: dict,
    ) -> Run:
        """Register a run that was already parsed into numpy arrays.

        Used by the web build, where the CSV is stream-parsed into typed arrays in
        the browser (full resolution) rather than handed to the Arrow reader -- so
        the multi-gigabyte text never has to be resident in 32-bit WASM memory.
        """
        run = self.registry.add_run(label, path, time, signals, units)
        self._report_loaded(run)
        return run

    def upsert_derived_run(self, label: str, time, signal_y, unit: str = "") -> int:
        """Create or refresh the single-channel derived run a node materializes.

        Refreshing *in place* (rather than remove + re-add) keeps the run id stable
        so plots/analysis windows referencing this derived signal survive a
        re-evaluation. Returns the derived run's id.
        """
        import numpy as np

        time = np.ascontiguousarray(time, dtype=np.float64)
        y = np.ascontiguousarray(signal_y, dtype=np.float32)
        for run in self.registry.runs:
            if run.derived and run.label == label:
                run.time = time
                run.time_raw = time
                run.time_origin = None
                run.signals = {"out": Signal("out", unit, y, run.id)}
                return run.id
        run = self.registry.add_run(label, f"<derived:{label}>", time, {"out": y}, {"out": unit})
        run.derived = True
        return run.id

    def remove_run(self, run_id: int) -> None:
        """Remove a run and drop any plot assignments that referenced it."""
        run = self.registry.get(run_id)
        if run is None:
            return
        # Detach any node that materialized this run so a later eval re-creates it.
        for node in self.nodes.nodes.values():
            if node.out_run_id == run_id:
                node.out_run_id = None
        for cell in self.cells:
            cell.signals = [s for s in cell.signals if s[0] != run_id]
            cell.y2_signals = [s for s in cell.y2_signals if s[0] != run_id]
            if cell.xy_source is not None and cell.xy_source[0] == run_id:
                cell.xy_source = None
        self.fft.sources = [s for s in self.fft.sources if s[0] != run_id]
        self.histogram.sources = [s for s in self.histogram.sources if s[0] != run_id]
        self.registry.remove_run(run_id)
        self.console.info(f"Removed run {run.label}")

    def _report_loaded(self, run: Run) -> None:
        self.console.ok(
            f"Loaded {run.label}: {run.n_rows:,} rows, "
            f"{len(run.signals)} signals, {run.duration:.3f} s span"
        )

    def poll_pending_loads(self) -> None:
        """Finalise completed background loads; call once per frame."""
        still_pending: list[tuple[Future[Run], str]] = []
        for future, path in self._pending:
            if not future.done():
                still_pending.append((future, path))
                continue
            try:
                run = future.result()
            except Exception as exc:  # noqa: BLE001 - surfaced to the console
                self.console.error(f"Failed to load {os.path.basename(path)}: {exc}")
                continue
            self._report_loaded(run)
        self._pending = still_pending

    @property
    def is_loading(self) -> bool:
        return bool(self._pending)

    def resolve_x_window(
        self, follow_plot: int, custom: tuple[float, float], signals: list[SignalRef]
    ) -> tuple[float, float]:
        """Resolve an FFT/analysis time window.

        ``follow_plot``: ``0`` uses the explicit ``custom`` ``(min, max)``; ``-1``
        (*Full*) uses the first signal's whole record; ``>= 1`` follows that
        subplot's live X range (falling back to the full record if that plot has
        no range yet).
        """
        if follow_plot == 0:  # Custom
            return custom

        if follow_plot >= 1:  # follow a specific plot, if it has a live range
            rng = self.plot_x_ranges.get(follow_plot)
            if rng is not None and math.isfinite(rng[0]) and math.isfinite(rng[1]) and rng[1] > rng[0]:
                return rng

        # Full (-1), or a followed plot with no range yet: the whole record.
        if signals:
            run = self.registry.get(signals[0][0])
            if run is not None and run.n_rows:
                return float(run.time[0]), float(run.time[-1])
        return custom

    # -- signal assignment helpers -----------------------------------------
    def signal_label(self, ref: SignalRef) -> str:
        run = self.registry.get(ref[0])
        if run is None:
            return ref[1]
        return f"{ref[1]} @ {run.label}"

    def shutdown(self) -> None:
        self._executor.shutdown(wait=False, cancel_futures=True)
