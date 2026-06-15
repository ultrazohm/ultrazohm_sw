"""Data model for the UltraZohm data viewer.

A :class:`Run` corresponds to one loaded log file (CSV or Parquet). It owns a
shared ``time`` axis plus one :class:`Signal` per logged channel. Signal samples
are kept as contiguous NumPy arrays so they can be fed directly to ImPlot and to
the ``tsdownsample`` engine without per-frame copies.
"""

from __future__ import annotations

import itertools
from dataclasses import dataclass, field

import numpy as np

# Distinct, color-blind friendly palette cycled across runs in the navigation
# tree so the same run keeps a stable color hint everywhere in the UI.
_RUN_COLORS = [
    (0.26, 0.59, 0.98, 1.0),
    (0.95, 0.61, 0.07, 1.0),
    (0.18, 0.71, 0.49, 1.0),
    (0.84, 0.19, 0.25, 1.0),
    (0.58, 0.40, 0.74, 1.0),
    (0.55, 0.34, 0.29, 1.0),
    (0.89, 0.47, 0.76, 1.0),
    (0.50, 0.50, 0.50, 1.0),
]


@dataclass
class Signal:
    """A single logged channel within a run."""

    name: str
    """Human readable channel name, e.g. ``ia`` or ``Speed_rpm``."""

    unit: str
    """Unit guessed from the channel name (``rpm``, ``us``, ...) or ``""``."""

    y: np.ndarray
    """Sample values (``float32``) aligned with the parent run ``time`` axis."""

    run_id: int
    """Identifier of the owning :class:`Run`."""

    pyramid: object = field(default=None, repr=False, compare=False)
    """Lazily-built multi-resolution min/max pyramid (:class:`downsample.Pyramid`)
    for O(output) decimation of large signals. Built on first display."""

    @property
    def label(self) -> str:
        return f"{self.name} [{self.unit}]" if self.unit else self.name


@dataclass
class Run:
    """One loaded log file."""

    id: int
    label: str
    """Display name (the file name)."""

    path: str
    time: np.ndarray
    """Shared time axis (``float64``), assumed monotonically increasing.

    This is the *displayed* axis: it equals :attr:`time_raw` shifted so the first
    sample sits at :attr:`time_origin` (when normalisation is on).
    """

    signals: dict[str, Signal]
    active: bool = True
    """Whether the run is shown in the navigation / available for plotting."""

    color: tuple[float, float, float, float] = (1.0, 1.0, 1.0, 1.0)

    time_raw: np.ndarray | None = None
    """The original timestamps as loaded; ``time`` is derived from these."""

    time_origin: float | None = None
    """If set, ``time`` is shifted so the first sample equals this value
    (per-log time normalisation). ``None`` means the raw timestamps are used."""

    def set_time_origin(self, target: float | None) -> None:
        """Normalise so the first sample sits at ``target`` (or restore raw)."""
        raw = self.time_raw if self.time_raw is not None else self.time
        self.time_origin = target
        if target is None or raw.shape[0] == 0:
            self.time = raw
        else:
            self.time = (raw - raw[0] + float(target)).astype(np.float64)

    @property
    def n_rows(self) -> int:
        return int(self.time.shape[0])

    @property
    def duration(self) -> float:
        if self.n_rows < 2:
            return 0.0
        return float(self.time[-1] - self.time[0])


class DataRegistry:
    """Owns every loaded run and hands out stable integer ids."""

    def __init__(self) -> None:
        self._runs: dict[int, Run] = {}
        self._ids = itertools.count(1)

    def add_run(
        self,
        label: str,
        path: str,
        time: np.ndarray,
        signals: dict[str, np.ndarray],
        units: dict[str, str],
    ) -> Run:
        run_id = next(self._ids)
        color = _RUN_COLORS[(run_id - 1) % len(_RUN_COLORS)]
        time_arr = np.ascontiguousarray(time, dtype=np.float64)
        run = Run(
            id=run_id,
            label=label,
            path=path,
            time=time_arr,
            signals={},
            color=color,
            time_raw=time_arr,
        )
        for name, values in signals.items():
            run.signals[name] = Signal(
                name=name,
                unit=units.get(name, ""),
                y=np.ascontiguousarray(values, dtype=np.float32),
                run_id=run_id,
            )
        self._runs[run_id] = run
        return run

    def remove_run(self, run_id: int) -> None:
        self._runs.pop(run_id, None)

    def get(self, run_id: int) -> Run | None:
        return self._runs.get(run_id)

    def get_signal(self, run_id: int, name: str) -> Signal | None:
        run = self._runs.get(run_id)
        if run is None:
            return None
        return run.signals.get(name)

    @property
    def runs(self) -> list[Run]:
        return list(self._runs.values())

    def __len__(self) -> int:
        return len(self._runs)
