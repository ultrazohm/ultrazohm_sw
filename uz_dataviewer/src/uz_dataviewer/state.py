"""Central application state shared across panels."""

from __future__ import annotations

import enum
import math
import os
from concurrent.futures import Future
from .loading import LoadExecutor
from dataclasses import dataclass, field

from . import webbridge
from .commands import CommandRegistry
from .console import Console
from .loader import ParsedRun, open_file
from .requests import Requests
from .model import DataRegistry, Run, Signal
from .nodes import NodeGraph
from .validation import axis_limits

# Identifies a signal across runs: (run_id, signal_name).
LARGE_CSV_BYTES = 1024**3


@dataclass(frozen=True)
class LoadRequest:
    path: str
    mode: str
    backend: str
    disk_cache: bool


SignalRef = tuple[int, str]


class PlotType(enum.Enum):
    LINE = "Line"
    SCATTER = "Scatter"
    STAIRS = "Stairs"
    XY = "XY"

    @classmethod
    def labels(cls) -> list[str]:
        return [t.value for t in cls]


class XyStyle(enum.Enum):
    """How an XY (signal-vs-signal) cell is drawn."""

    LINE = "Line"  # connected line, no markers (the original behaviour)
    MARKERS = "Markers"  # markers only, no connecting line (scatter)
    BOTH = "Both"  # connected line with a marker at every sample

    @classmethod
    def labels(cls) -> list[str]:
        return [s.value for s in cls]


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

    xy_style: XyStyle = XyStyle.LINE
    """How an XY cell draws its series (line / markers / both)."""

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

    y_lim: tuple[float, float] | None = None
    """Last rendered primary Y range; persists after pending limits are consumed."""

    x_lim: tuple[float, float] | None = None
    """Last rendered X range, including XY coordinates (never linked as time)."""

    def add(self, ref: SignalRef) -> bool:
        if ref not in self.signals:
            self.signals.append(ref)
            self.fit_pending = True
            return True
        return False

    def clear(self) -> None:
        self.signals.clear()
        self.y2_signals.clear()
        self.fit_pending = True

    def set_secondary(self, ref: SignalRef, secondary: bool) -> None:
        if ref not in self.signals:
            raise ValueError(f"{ref[1]!r} is not assigned to this plot")
        if secondary and ref not in self.y2_signals:
            self.y2_signals.append(ref)
        elif not secondary and ref in self.y2_signals:
            self.y2_signals.remove(ref)
        self.fit_pending = True

    def set_limits(self, axis: str, lo: float, hi: float) -> None:
        if axis not in ('x', 'y'):
            raise ValueError(f"Unknown axis: {axis}")
        limits = axis_limits(lo, hi)
        setattr(self, f'pending_{axis}_lim', limits)
        setattr(self, f'{axis}_lim', limits)

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


def default_data_settings():
    """The browser cannot use the native Polars runtime."""
    return ("pyarrow", "memory") if webbridge.IS_WEB else ("polars", "lazy")


class AppState:
    def __init__(self) -> None:
        self.session_token = object()
        self.registry = DataRegistry()
        self.backend, self.loading_mode = default_data_settings()
        self.cache_dir = None
        self.disk_cache = False
        self.large_csv_requests: list[LoadRequest] = []
        self.display = Requests(synchronous=webbridge.IS_WEB)
        self.analysis_jobs = Requests(synchronous=webbridge.IS_WEB)
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
        self.dragged_log_path: str | None = None

        self._executor = LoadExecutor()
        # Worker parses into a ParsedRun (no registry touch); the main thread registers
        # it in poll_pending_loads, so DataRegistry stays single-threaded.
        self._pending: list[tuple[Future[ParsedRun], str]] = []

        # Signal that the docking layout should focus an analysis window this frame.
        self.focus_fft = False
        self.focus_histogram = False

    def replace_session(self, replacement: "AppState") -> None:
        """Take ownership of a fully prepared session; retain command/console UI.

        All other fields, including the unique session token, belong to the new
        session. Panels observe the token before using their caches. The caller
        must not use or shut down the consumed replacement afterwards.
        """
        self.console.extend_from(replacement.console)
        self.shutdown()
        attributes = vars(replacement).copy()
        attributes.update(console=self.console, commands=self.commands)
        self.__dict__ = attributes

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
        self.plot_x_ranges = {i: limits for i, limits in self.plot_x_ranges.items()
                              if 1 <= i <= len(new_cells)}
        for cfg in (self.fft, self.histogram):
            if cfg.follow_plot > len(new_cells):
                cfg.follow_plot = -1  # removed plot: use the full recording
                cfg.compute_requested = bool(cfg.sources)

    def validate_follow_plot(self, target: int) -> int:
        if not -1 <= target <= self.cell_count:
            raise ValueError(f"Analysis window must be custom, full, or plot_1..plot_{self.cell_count}")
        return target

    def plot_time_range(self, plot_n: int):
        """Effective time window, independent of whether a GUI frame has run."""
        cell = self.cells[plot_n - 1]
        if cell.plot_type is PlotType.XY:
            return None
        if self.link_x and self.shared_x is not None:
            return self.shared_x
        return cell.pending_x_lim or self.plot_x_ranges.get(plot_n) or cell.x_lim

    def set_plot_x_limits(self, plot_n: int, lo: float, hi: float) -> None:
        cell = self.cells[plot_n - 1]
        cell.set_limits('x', lo, hi)
        if cell.plot_type is not PlotType.XY:
            self.plot_x_ranges[plot_n] = cell.pending_x_lim
            if self.link_x:
                self.shared_x = cell.pending_x_lim
                # Explicit commands must also move the last hovered driver,
                # whose axis is otherwise left free for interactive panning.
                for index, linked in enumerate(self.cells, 1):
                    if linked.plot_type is not PlotType.XY:
                        linked.set_limits('x', lo, hi)
                        self.plot_x_ranges[index] = linked.pending_x_lim

    def reset_plot_view(self, plot_n: int) -> None:
        cell = self.cells[plot_n - 1]
        cell.pending_x_lim = cell.pending_y_lim = None
        cell.x_lim = cell.y_lim = None
        cell.fit_pending = True
        if cell.plot_type is PlotType.XY:
            return
        self.plot_x_ranges.pop(plot_n, None)
        runs = [self.registry.get(ref[0]) for ref in cell.signals]
        runs = [run for run in runs if run is not None and run.active and run.n_rows]
        if runs:
            lo = min(float(run.time[0]) for run in runs)
            hi = max(float(run.time[-1]) for run in runs)
            if hi > lo:
                self.set_plot_x_limits(plot_n, lo, hi)

    # -- file loading (async on desktop, synchronous in the browser) -------
    def request_load(self, path: str, loading_mode: str | None = None) -> None:
        """Open a file, optionally overriding the mode for this request only."""
        mode = self.loading_mode if loading_mode is None else loading_mode
        if mode not in {"memory", "lazy"}:
            raise ValueError(f"Unknown loading mode: {mode}")
        backend = self.backend
        from .loader import validate_backend
        validate_backend(backend)
        path = os.path.abspath(path)
        request = LoadRequest(path, mode, backend, self.disk_cache)
        if not webbridge.IS_WEB and path.lower().endswith(".csv"):
            try:
                if os.path.getsize(path) > LARGE_CSV_BYTES:
                    self.large_csv_requests.append(request)
                    return
            except OSError:
                pass  # The normal loader reports missing or unreadable files.
        self._submit_load(request)

    def resolve_large_csv(self, choice: str) -> None:
        """Resolve the oldest GUI prompt using the settings captured at selection."""
        if choice not in {"csv", "convert", "existing", "cancel"}:
            raise ValueError(f"Unknown large CSV action: {choice}")
        request = self.large_csv_requests.pop(0)
        if choice == "cancel":
            return
        if choice == "csv":
            # Explicitly opening CSV bypasses automatic cached conversion.
            self._submit_load(LoadRequest(request.path, request.mode, request.backend, False))
            return
        destination = os.path.splitext(request.path)[0] + ".parquet"
        target = LoadRequest(destination, request.mode, request.backend, request.disk_cache)
        self._submit_load(target, convert_from=request.path if choice == "convert" else None)

    def _submit_load(self, request: LoadRequest, convert_from=None) -> None:
        path = request.path
        self.commands.echo(self, "load", [path])
        self.console.info(f"{'Converting and loading' if convert_from else 'Loading'} {os.path.basename(path)} ...")
        if webbridge.IS_WEB:
            try:
                parsed = self._open_background(path, request.mode, request.backend, request.disk_cache)
                self._report_loaded(parsed.register(self.registry))
            except Exception as exc:
                self.console.error(f"Failed to load {os.path.basename(path)}: {exc}")
            return
        if convert_from:
            future = self._executor.submit(self._convert_and_open, convert_from, request)
        else:
            future = self._executor.submit(self._open_background, path, request.mode,
                                           request.backend, request.disk_cache)
        self._pending.append((future, path))

    def _convert_and_open(self, source: str, request: LoadRequest, cancel=None):
        from .loader import convert_csv_to_parquet
        convert_csv_to_parquet(source, request.path, backend=request.backend, cancel=cancel)
        return self._open_background(request.path, request.mode, request.backend, request.disk_cache, cancel=cancel)

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
            run = open_file(path, self.loading_mode, self.registry.cache, self.cache_dir, backend=self.backend, disk_cache=self.disk_cache).register(self.registry)
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
        import numpy as np

        from .loader import validate_time_axis

        time = np.ascontiguousarray(time, dtype=np.float64)
        validate_time_axis(time, path)  # same monotonic contract as the native loaders
        run = self.registry.add_run(label, path, time, signals, units)
        self._report_loaded(run)
        return run

    def upsert_derived_run(self, label: str, time, signal_y, unit: str = "", *, run_id=None) -> int:
        """Create or refresh the single-channel derived run a node materializes.

        Refreshing *in place* (rather than remove + re-add) keeps the run id stable
        so plots/analysis windows referencing this derived signal survive a
        re-evaluation. Returns the derived run's id.
        """
        import numpy as np

        time = np.ascontiguousarray(time, dtype=np.float64)
        y = np.ascontiguousarray(signal_y, dtype=np.float32)
        run = self.registry.get(run_id) if run_id is not None else None
        if run is not None:
            if not run.derived:
                raise ValueError("Cannot overwrite a recording with a derived output")
            run.label = label
            run.time = time
            run.time_raw = time
            run.set_time_origin(run.time_origin)
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
                node.eval_key = None
        for cell in self.cells:
            for ref in list(cell.signals):
                if ref[0] == run_id:
                    cell.remove(ref)
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
        """Finalise completed background loads; call once per frame.

        The worker only *parsed*; the registry mutation (``register``) happens here on
        the main thread, so the UI never reads a registry mid-write.
        """
        still_pending: list[tuple[Future[ParsedRun], str]] = []
        for future, path in self._pending:
            if not future.done():
                still_pending.append((future, path))
                continue
            try:
                parsed = future.result()
                run = parsed.register(self.registry)
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
            rng = self.plot_time_range(follow_plot)
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
        return f"{ref[1]} @ {run.label} [run_{run.id}]"

    def _open_background(self, path, mode, backend, disk_cache, cancel=None):
        return open_file(path, mode, self.registry.cache, self.cache_dir, backend=backend, disk_cache=disk_cache, cancel=cancel)

    def shutdown(self) -> None:
        self.display.close()
        self.analysis_jobs.close()
        self.registry.cache.clear()
        self._executor.shutdown()
        self._pending.clear()
        self.large_csv_requests.clear()
