"""Window selection and array adapter for the shared source downsampler."""

from __future__ import annotations

import numpy as np


def visible_slice(time: np.ndarray, x_min: float, x_max: float, *, padding: bool = True) -> tuple[int, int]:
    """Return ``(start, stop)`` indices covering ``[x_min, x_max]`` (inclusive-ish).

    One sample of padding is added on each side so lines reach the plot edges.
    ``time`` is assumed monotonically increasing.

    The search scalars are cast to ``time``'s dtype first: ``np.searchsorted`` on a
    float32 array with a Python (float64) scalar **up-casts the whole array** to
    float64 every call -- ~31 ms on the 7.5 M-bin FFT ``freqs`` array, i.e. the
    per-frame killer behind a sluggish spectrum (the same landmine as ``np.interp``
    for cursors). A matching-dtype scalar keeps it O(log n).
    """
    from .sources import SourceColumn
    if isinstance(time, SourceColumn):
        return time.source.bounds(x_min - time.offset, x_max - time.offset, padding=padding)
    lo = time.dtype.type(x_min)
    hi = time.dtype.type(x_max)
    start = int(np.searchsorted(time, lo, side="left"))
    stop = int(np.searchsorted(time, hi, side="right"))
    if x_max < x_min:
        return start, start
    if padding:
        start = max(0, start - 1)
        stop = min(time.shape[0], stop + 1)
    return start, stop


def decimate_range(time, y, source, n_out, start, stop):
    """Sample a resident array window using the same engine as CSV/Parquet plots."""
    from .sources import ArraySource
    if stop <= start:
        return time[:0], y[:0]
    source = source if source is not None else ArraySource(time, {'value': y})
    result = source.read_plot('value', float(time[start]), float(time[stop - 1]), n_out, padding=False)
    return result.time, result.values
