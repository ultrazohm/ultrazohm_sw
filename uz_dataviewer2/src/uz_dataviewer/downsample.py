"""Range-aware downsampling for large logs.

Two layers:

* :func:`downsample_xy` -- a one-shot decimation of a visible slice via
  ``tsdownsample`` (MinMax-LTTB), with a pure-NumPy fallback. Cost is *O(visible
  points)*, fine for moderate windows but expensive when the whole of a
  multi-gigabyte signal is on screen (it re-scans tens of millions of points).

* :class:`Pyramid` -- a precomputed **multi-resolution min/max pyramid** built
  once per signal. Querying it for a window is *O(output points)*, independent of
  the total sample count, so a 5 GB log pans at full frame rate. This is the
  primary path for large signals; ``downsample_xy`` remains the fast path for
  small ones and the fallback where no pyramid exists.

The legacy ``dataviewer.py`` used ``plotly_resampler.FigureResampler`` (tied to
Plotly); only its decimation engine, the standalone ``tsdownsample``, was
reusable with ImPlot -- which is what the one-shot path uses.
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


# -- multi-resolution min/max pyramid -----------------------------------------
# Signals with more than this many samples get a pyramid; smaller ones are cheap
# to decimate directly.
PYRAMID_MIN_POINTS = 200_000


class Pyramid:
    """Precomputed min/max levels of one signal, for O(output) decimation.

    Level ``k`` stores, for buckets of ``base * factor**k`` consecutive samples,
    the per-bucket ``min`` and ``max`` (``float32``). To draw a window we pick the
    finest level whose bucket density fits the output budget, slice it, and expand
    each bucket into two points (min, max) -- a faithful envelope that preserves
    spikes. Per-query cost depends only on the output size, not the signal length.

    X is *not* stored: bucket positions map to raw sample indices (``bucket_size``
    apart), so query reads X from the run's ``time`` axis. The pyramid is thus
    independent of time normalisation and reusable across runs of equal length.
    """

    __slots__ = ("levels", "n")

    def __init__(self, levels: list[tuple[int, np.ndarray, np.ndarray]], n: int) -> None:
        self.levels = levels  # [(bucket_size, ymin, ymax), ...] coarsening
        self.n = n

    @classmethod
    def build(cls, y: np.ndarray, base: int = 64, factor: int = 8, min_buckets: int = 512) -> "Pyramid":
        y = np.ascontiguousarray(y, dtype=np.float32)
        n = int(y.shape[0])
        bucket = base
        nb = (n + bucket - 1) // bucket
        pad = nb * bucket - n
        src = np.concatenate([y, np.full(pad, y[-1], np.float32)]) if pad else y
        block = src.reshape(nb, bucket)
        ymin = block.min(axis=1)
        ymax = block.max(axis=1)
        levels: list[tuple[int, np.ndarray, np.ndarray]] = [(bucket, ymin, ymax)]
        # Coarser levels are aggregated from the previous level (min-of-mins,
        # max-of-maxes), so the whole build is O(n).
        while ymin.shape[0] > min_buckets:
            bucket *= factor
            pnb = ymin.shape[0]
            nb = (pnb + factor - 1) // factor
            pad = nb * factor - pnb
            if pad:
                ymin = np.concatenate([ymin, np.full(pad, ymin[-1], np.float32)])
                ymax = np.concatenate([ymax, np.full(pad, ymax[-1], np.float32)])
            ymin = ymin.reshape(nb, factor).min(axis=1)
            ymax = ymax.reshape(nb, factor).max(axis=1)
            levels.append((bucket, ymin, ymax))
        return cls(levels, n)

    def query(self, time: np.ndarray, n_out: int, start: int, stop: int) -> tuple[np.ndarray, np.ndarray]:
        count = max(stop - start, 1)
        target_buckets = max(n_out // 2, 1)  # two output points per bucket
        # Finest level whose bucket count over the window fits the budget.
        bucket, ymin, ymax = self.levels[-1]
        for lvl_bucket, lvl_min, lvl_max in self.levels:
            if count / lvl_bucket <= target_buckets:
                bucket, ymin, ymax = lvl_bucket, lvl_min, lvl_max
                break
        b0 = start // bucket
        b1 = min((stop + bucket - 1) // bucket, ymin.shape[0])
        if b1 <= b0:
            b1 = min(b0 + 1, ymin.shape[0])
        nb = b1 - b0
        centers = np.minimum(np.arange(b0, b1) * bucket + bucket // 2, self.n - 1)
        out_x = np.repeat(time[centers], 2)
        out_y = np.empty(2 * nb, dtype=np.float32)
        out_y[0::2] = ymin[b0:b1]
        out_y[1::2] = ymax[b0:b1]
        return out_x, out_y


def decimate_range(
    time: np.ndarray,
    y: np.ndarray,
    pyramid: "Pyramid | None",
    n_out: int,
    start: int,
    stop: int,
) -> tuple[np.ndarray, np.ndarray]:
    """Decimate ``[start, stop)`` to ~``n_out`` points (caller supplies the slice).

    Uses the precomputed :class:`Pyramid` when present (O(output)); otherwise
    falls back to a one-shot ``tsdownsample`` of the slice.
    """
    n_out = max(int(n_out), 2)
    if stop - start <= n_out:
        return time[start:stop], y[start:stop]
    if pyramid is not None:
        return pyramid.query(time, n_out, start, stop)
    xs = time[start:stop]
    ys = y[start:stop]
    if _DOWNSAMPLER is not None:
        idx = _DOWNSAMPLER.downsample(xs, ys, n_out=n_out)
    else:
        idx = _minmax_indices(ys, n_out)
    return xs[idx], ys[idx]
