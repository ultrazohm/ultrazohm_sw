"""Ergonomic, GUI-free public API for headless / scripting use.

This module is the supported way to use ``uz_dataviewer`` as a *library* -- loading
logs, computing FFTs and running the node transforms from a plain Python script or a
notebook, with no window and (importantly) **without importing the imgui GUI stack**.
It is a thin convenience layer over the existing pure-NumPy building blocks
(:mod:`loader`, :mod:`analysis`, :mod:`nodes`, :mod:`transforms`); it adds no new
compute logic.

    import uz_dataviewer as uz

    data = uz.read("Log.csv")          # -> Dataset (shared time axis + named signals)
    t, ia = data.time, data["ia"]

    spec = uz.fft(t, ia)               # -> FftResult (full span by default)
    df   = uz.fft_frame(t, ia)         # -> pandas DataFrame [frequency, amplitude]

    t2, y2, info = uz.node("filter", (t, ia), type="low", cutoff=40, taps=201)
    print(uz.kinds())                  # ('fft', 'math', 'filter', 'shift')

The node calculations are exactly those the GUI's node graph uses (they share
:data:`nodes.REGISTRY`); :func:`load_plugins` opts into any external plugin kinds.
"""

from __future__ import annotations

import numpy as np

from . import nodes
from .analysis import FftResult, compute_fft
from .loader import parse_file, validate_backend
from .plugins import load_plugins

__all__ = [
    "Dataset",
    "read",
    "fft",
    "fft_frame",
    "node",
    "filter",
    "math",
    "kinds",
    "load_plugins",
    "FftResult",
]


class Dataset:
    """A loaded log: a shared ``time`` axis plus named signal arrays.

    Thin read-friendly wrapper over ``loader.ParsedRun``. Index a signal by name
    (``data["ia"]``), test membership (``"ia" in data``), iterate names, or pull the
    whole thing into a DataFrame with :meth:`to_dataframe`.
    """

    __slots__ = ("label", "path", "time", "signals", "units", "backend")

    def __init__(self, parsed) -> None:
        self.backend: str = parsed.backend
        self.label: str = parsed.label
        self.path: str = parsed.path
        self.time: np.ndarray = parsed.time
        self.signals: dict[str, np.ndarray] = parsed.signals
        self.units: dict[str, str] = parsed.units

    @property
    def names(self) -> list[str]:
        """Ordered list of signal names in this dataset."""
        return list(self.signals)

    def __getitem__(self, name: str) -> np.ndarray:
        return self.signals[name]

    def __contains__(self, name: str) -> bool:
        return name in self.signals

    def __iter__(self):
        return iter(self.signals)

    def __len__(self) -> int:
        return len(self.signals)

    def __repr__(self) -> str:
        return f"Dataset(label={self.label!r}, n_rows={self.time.shape[0]}, signals={self.names})"

    def to_dataframe(self):
        """Return a backend-native DataFrame of time plus one column per signal."""
        if self.backend == "polars":
            import polars as pl
            return pl.DataFrame({"time": self.time, **self.signals})
        import pandas as pd

        return pd.DataFrame({"time": self.time, **self.signals})


def read(path, *, backend="pyarrow") -> Dataset:
    """Load a ``.csv``/``.parquet`` log and return its data as a :class:`Dataset`."""
    return Dataset(parse_file(str(path), backend=backend))


def fft(
    time,
    y,
    *,
    remove_dc: bool = True,
    window: bool = True,
    x_min: float | None = None,
    x_max: float | None = None,
) -> FftResult:
    """Single-sided amplitude spectrum of ``y``.

    With no ``x_min``/``x_max`` the whole record is transformed. Returns a
    ``uz_dataviewer.analysis.FftResult`` (``.freqs``, ``.mag``, ``.info``, ``.ok``).
    """
    t = np.asarray(time, dtype=np.float64)
    yy = np.asarray(y, dtype=np.float64)
    if t.ndim != 1 or yy.ndim != 1 or t.shape != yy.shape:
        return FftResult(None, None, "FFT needs equal-length one-dimensional time and value arrays.")
    lo = float(x_min) if x_min is not None else (float(t[0]) if len(t) else 0.)
    hi = float(x_max) if x_max is not None else (float(t[-1]) if len(t) else 0.)
    return compute_fft(t, yy, lo, hi, remove_dc=remove_dc, window=window)


def fft_frame(time, y, *, backend="pyarrow", **kwargs):
    """Like :func:`fft` but returns a backend-native frame [frequency, amplitude].

    PyArrow (default) returns pandas; backend="polars" returns a Polars DataFrame.

    Raises ``ValueError`` (with the reason) if the transform could not be computed.
    """
    validate_backend(backend)

    result = fft(time, y, **kwargs)
    if not result.ok:
        raise ValueError(result.info)
    columns = {"frequency": result.freqs, "amplitude": result.mag}
    if backend == "polars":
        import polars as pl
        return pl.DataFrame(columns)
    import pandas as pd
    return pd.DataFrame(columns)


def kinds() -> tuple[str, ...]:
    """The available node-transform kinds (builtins + any loaded plugins)."""
    return nodes.transform_kinds()


def node(kind: str, *signals, **params):
    """Run a node transform headlessly.

    ``signals`` are ``(time, y)`` tuples (one for unary kinds, two for binary math);
    ``params`` override the kind's defaults. Returns ``(out_time, out_y, info)`` --
    e.g. an ``fft`` node returns ``(freqs, mag, info)``. ``kind`` is one of
    :func:`kinds` (``fft``/``math``/``filter``/``shift`` plus any plugins).
    """
    spec = nodes.REGISTRY.get(kind)
    if spec is None:
        raise ValueError(f"unknown node kind {kind!r}; one of {kinds()}")
    merged = nodes.default_params(kind)
    merged.update({k: v for k, v in params.items()})
    inputs = [
        (np.asarray(t, dtype=np.float64), np.asarray(s, dtype=np.float64)) for t, s in signals
    ]
    time, values, info, _ = nodes.compute_node(nodes.Node(0, kind, kind, params=merged), inputs)
    return time, values, info


def filter(time, y, **params):
    """Validated ``node('filter', ...)`` convenience wrapper (FIR low/high/band-pass).

    Returns ``(time, filtered_y, info)``.
    """
    return node("filter", (time, y), **params)


def math(*signals, **params):
    """Validated ``node('math', ...)`` convenience wrapper (scale/offset/derivative/
    integral/reciprocal and binary add/sub/mul/div).

    ``signals`` are ``(time, y)`` tuples. Returns ``(time, y_out, info)``.
    """
    return node("math", *signals, **params)
