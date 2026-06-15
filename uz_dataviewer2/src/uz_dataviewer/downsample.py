"""Range-aware downsampling for large logs.

The legacy ``dataviewer.py`` relied on ``plotly_resampler.FigureResampler`` to
keep multi-gigabyte logs responsive. That wrapper is tied to Plotly figures and
cannot be reused with ImPlot, but the decimation engine underneath it --
``tsdownsample`` -- is a standalone package and *is* reusable. We use its
MinMax-LTTB downsampler, which preserves visual peaks (important for inspecting
ripple/spikes) while collapsing the series to roughly the pixel width of the
plot.
"""

from __future__ import annotations

import numpy as np

try:
    from tsdownsample import MinMaxLTTBDownsampler

    _DOWNSAMPLER = MinMaxLTTBDownsampler()
except ImportError:  # e.g. Pyodide/web where the Rust wheel is unavailable
    _DOWNSAMPLER = None


def _minmax_indices(y: np.ndarray, n_out: int) -> np.ndarray:
    """Pure-NumPy MinMax decimation fallback (preserves per-bucket extrema)."""
    n = y.shape[0]
    n_buckets = max(n_out // 2, 1)
    edges = np.linspace(0, n, n_buckets + 1, dtype=np.int64)
    idx = []
    for lo, hi in zip(edges[:-1], edges[1:]):
        if hi <= lo:
            continue
        seg = y[lo:hi]
        idx.append(lo + int(seg.argmin()))
        idx.append(lo + int(seg.argmax()))
    return np.unique(np.asarray(idx, dtype=np.int64))


def visible_slice(time: np.ndarray, x_min: float, x_max: float) -> tuple[int, int]:
    """Return ``(start, stop)`` indices covering ``[x_min, x_max]`` (inclusive-ish).

    One sample of padding is added on each side so lines reach the plot edges.
    ``time`` is assumed monotonically increasing.
    """
    start = int(np.searchsorted(time, x_min, side="left"))
    stop = int(np.searchsorted(time, x_max, side="right"))
    start = max(0, start - 1)
    stop = min(time.shape[0], stop + 1)
    return start, stop


def downsample_xy(
    time: np.ndarray,
    y: np.ndarray,
    n_out: int,
    x_min: float | None = None,
    x_max: float | None = None,
) -> tuple[np.ndarray, np.ndarray]:
    """Return ``(x, y)`` reduced to at most ``n_out`` points within the range.

    When ``x_min``/``x_max`` are given the series is first cropped to the visible
    window, so zooming in progressively reveals more detail (the same behaviour
    plotly-resampler provided).
    """
    n_out = max(int(n_out), 2)

    if x_min is not None and x_max is not None and x_max > x_min:
        start, stop = visible_slice(time, x_min, x_max)
    else:
        start, stop = 0, time.shape[0]

    xs = time[start:stop]
    ys = y[start:stop]

    if xs.shape[0] <= n_out:
        return xs, ys

    if _DOWNSAMPLER is not None:
        idx = _DOWNSAMPLER.downsample(xs, ys, n_out=n_out)
    else:
        idx = _minmax_indices(ys, n_out)
    return xs[idx], ys[idx]
