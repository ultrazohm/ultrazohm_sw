"""Sample-preserving min/max reduction shared by file summaries, live rings and
display sampling.

Every reduction keeps original samples: per bucket the first finite minimum,
the last finite maximum (so a constant bucket keeps both ends) and the first
non-finite sample (a gap marker). Positions are indices into the input.
"""

import numpy as np


def bucket_extremes(y, starts):
    """Positions of each bucket's extremes and first gap; -1 where absent.

    ``starts`` are the ascending first positions of consecutive buckets that
    together cover ``y``.
    """
    n = len(y)
    lengths = np.diff(np.r_[starts, n])
    finite = np.isfinite(y)
    pos = np.arange(n)
    low = np.minimum.reduceat(np.where(finite, y, np.inf), starts)
    high = np.maximum.reduceat(np.where(finite, y, -np.inf), starts)
    mins = np.minimum.reduceat(
        np.where(finite & (y == np.repeat(low, lengths)), pos, n), starts
    )
    maxs = np.maximum.reduceat(
        np.where(finite & (y == np.repeat(high, lengths)), pos, -1), starts
    )
    gaps = np.minimum.reduceat(np.where(~finite, pos, n), starts)
    mins[mins == n] = -1
    gaps[gaps == n] = -1
    return mins, maxs, gaps


def selected(y, starts):
    """Sorted unique positions of all bucket extremes and gap markers."""
    positions = np.unique(np.r_[bucket_extremes(y, starts)])
    return positions[positions >= 0]


def group_starts(groups):
    """First positions of runs of equal values in an ascending group array."""
    return np.r_[0, np.flatnonzero(np.diff(groups)) + 1]


def merge_extremes(y, mins, maxs, gaps, factor):
    """Combine ``factor`` consecutive child buckets into parents (positions in ``y``)."""
    groups = -(-len(mins) // factor)
    pad = groups * factor - len(mins)

    def grouped(values):
        return np.r_[values, np.full(pad, -1, np.int64)].reshape(groups, factor)

    mins, maxs, gaps = grouped(mins), grouped(maxs), grouped(gaps)
    low = np.where(mins >= 0, y[np.maximum(mins, 0)], np.inf)
    high = np.where(maxs >= 0, y[np.maximum(maxs, 0)], -np.inf)
    rows = np.arange(groups)
    # Children are ordered: argmin picks the first minimum, reversed argmax the last maximum.
    parent_min = mins[rows, low.argmin(axis=1)]
    parent_max = maxs[rows, factor - 1 - high[:, ::-1].argmax(axis=1)]
    parent_min[~np.isfinite(low.min(axis=1))] = -1
    parent_max[~np.isfinite(high.max(axis=1))] = -1
    parent_gap = np.where(gaps >= 0, gaps, np.iinfo(np.int64).max).min(axis=1)
    parent_gap[parent_gap == np.iinfo(np.int64).max] = -1
    return parent_min, parent_max, parent_gap


def envelope(t, y, indices, budget):
    """Ordered min/max plus a gap marker per bucket, using original samples.

    Budget targets finite extrema; gap markers can add up to half that count.
    """
    if len(y) <= budget:
        return np.ascontiguousarray(t, dtype=np.float64), np.ascontiguousarray(
            y, dtype=np.float64
        )
    groups = max(1, budget // 2)
    # Sample-space buckets keep summaries and raw refinement on the same axis.
    span = max(1, int(indices[-1]) - int(indices[0]) + 1)
    chosen = selected(y, group_starts((indices - indices[0]) * groups // span))
    values = np.asarray(y[chosen], dtype=np.float64).copy()
    values[~np.isfinite(values)] = np.nan
    return np.ascontiguousarray(t[chosen], dtype=np.float64), values
