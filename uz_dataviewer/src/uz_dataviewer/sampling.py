"""Sampling contracts shared by FFT and node transforms; no resampling."""
from __future__ import annotations

import numpy as np

_BLOCK = 65536


def regular_sample_interval(time, operation: str) -> float:
    """Validate a regular grid (100 ppm plus timestamp roundoff), returning dt."""
    if time.ndim != 1 or len(time) < 2:
        raise ValueError(f"{operation} needs at least two timestamps")
    dt = (float(time[-1]) - float(time[0])) / (len(time) - 1)
    if not np.isfinite(dt) or dt <= 0:
        raise ValueError(f"{operation} needs finite, strictly increasing timestamps")
    tolerance = max(abs(dt) * 1e-4,
                    np.finfo(np.float64).eps * max(1., abs(float(time[0])), abs(float(time[-1]))) * 8)
    for start in range(0, len(time) - 1, _BLOCK):
        block = time[start:min(len(time), start + _BLOCK + 1)]
        intervals = np.diff(block)
        if not np.isfinite(block).all() or np.any(intervals <= 0):
            raise ValueError(f"{operation} needs finite, strictly increasing timestamps")
        if np.any(np.abs(intervals - dt) > tolerance):
            raise ValueError(f"{operation} needs uniformly spaced timestamps; selected window is irregular")
    return dt


def require_matching_time(left, right) -> None:
    """Compare every timestamp, allowing only floating-point roundoff."""
    if left.ndim != 1 or left.shape != right.shape:
        raise ValueError("Binary math needs matching time axes")
    for start in range(0, len(left), _BLOCK):
        a, b = left[start:start + _BLOCK], right[start:start + _BLOCK]
        if not np.isfinite(a).all() or not np.isfinite(b).all():
            raise ValueError("Binary math needs finite timestamps")
        tolerance = np.finfo(np.float64).eps * max(1., float(np.max(np.abs(a))), float(np.max(np.abs(b)))) * 8
        if np.any(np.abs(a - b) > tolerance):
            raise ValueError("Binary math needs matching time axes; inputs are not time-aligned")


def sample_xy(left, right, x_channel, y_channel, x_offset, y_offset, stride, cancel=None):
    """Validate every displayed timestamp while sampling aligned raw batches."""
    from .sources import check
    if left.metadata.rows != right.metadata.rows:
        raise ValueError('XY needs matching time axes and equal-length inputs')
    xs, ys, offset = [], [], 0
    x_batches = iter(left.iter_raw([x_channel], cancel=cancel))
    y_batches = iter(right.iter_raw([y_channel], cancel=cancel))
    xt = yt = np.empty(0)
    try:
        while True:
            check(cancel)
            if not len(xt):
                batch = next(x_batches, None)
                if batch is not None:
                    xt, values = batch
                    xv = values[x_channel]
            if not len(yt):
                batch = next(y_batches, None)
                if batch is not None:
                    yt, values = batch
                    yv = values[y_channel]
            if not len(xt) or not len(yt):
                if len(xt) or len(yt) or offset != left.metadata.rows:
                    raise ValueError('XY needs equal-length inputs')
                break
            n = min(len(xt), len(yt))
            try:
                require_matching_time(xt[:n] + x_offset, yt[:n] + y_offset)
            except ValueError as exc:
                raise ValueError('XY needs matching displayed timestamps; inputs are not time-aligned') from exc
            start = (-offset) % stride
            xs.append(xv[start:n:stride].copy())
            ys.append(yv[start:n:stride].copy())
            offset += n
            xt, xv = xt[n:], xv[n:]
            yt, yv = yt[n:], yv[n:]
    finally:
        x_batches.close()
        y_batches.close()
    return (np.ascontiguousarray(np.concatenate(xs) if xs else [], dtype=np.float64),
            np.ascontiguousarray(np.concatenate(ys) if ys else [], dtype=np.float64))
