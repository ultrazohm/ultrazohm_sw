"""Sampling contracts shared by FFT and node transforms; no resampling."""
from __future__ import annotations

import numpy as np

from .sources import shift_time

_BLOCK = 65536


def regular_sample_interval(time, operation: str, *, timestamp_resolution=0.0) -> float:
    """Return dt for a regular grid without resampling measurements.

    Known quantization permits +/- half a timestamp step around one fitted
    grid. Unspecified precision retains the existing 100 ppm interval check.
    """
    if not np.isfinite(timestamp_resolution) or timestamp_resolution < 0:
        raise ValueError("Timestamp resolution must be finite and nonnegative")
    if time.ndim != 1 or len(time) < 2:
        raise ValueError(f"{operation} needs at least two timestamps")
    dt = (float(time[-1]) - float(time[0])) / (len(time) - 1)
    if not np.isfinite(dt) or dt <= 0:
        raise ValueError(f"{operation} needs finite, strictly increasing timestamps")
    roundoff = np.finfo(np.float64).eps * max(abs(float(time[0])), abs(float(time[-1]))) * 8
    if roundoff > abs(dt) * .01:
        raise ValueError(f"{operation} timestamp precision is insufficient to establish uniform sampling")
    tolerance = max(abs(dt) * 1e-4, roundoff)
    for start in range(0, len(time) - 1, _BLOCK):
        block = time[start:min(len(time), start + _BLOCK + 1)]
        intervals = np.diff(block)
        if not np.isfinite(block).all() or np.any(intervals <= 0):
            raise ValueError(f"{operation} needs finite, strictly increasing timestamps")
        if not timestamp_resolution and np.any(np.abs(intervals - dt) > tolerance):
            raise ValueError(f"{operation} needs uniformly spaced timestamps; selected window is irregular")
    if timestamp_resolution:
        if timestamp_resolution > dt * .01:
            raise ValueError(f"{operation} timestamp precision is insufficient to establish uniform sampling")
        return _quantized_interval(time, timestamp_resolution, roundoff, operation)
    return dt


def _quantized_interval(time, quantum, roundoff, operation):
    """Find a grid whose timestamp residuals fit inside one quantization bin.

    For a given slope, residual max-min <= quantum means an intercept exists
    with every error <= quantum/2. Violating extrema bound the feasible slope;
    intersect these bounds until a grid is found or no slope remains. Work in
    blocks so even long recordings require only bounded temporary storage.
    """
    span = float(time[-1]) - float(time[0])
    width = quantum + 2 * roundoff
    lower, upper = (span - width) / (len(time) - 1), (span + width) / (len(time) - 1)
    for _ in range(64):
        dt = (lower + upper) / 2
        low, high, imin, imax = np.inf, -np.inf, 0, 0
        for start in range(0, len(time), _BLOCK):
            stop = min(start + _BLOCK, len(time))
            residual = (time[start:stop] - float(time[0])) - np.arange(start, stop, dtype=np.float64) * dt
            a, b = int(residual.argmin()), int(residual.argmax())
            if residual[a] < low:
                low, imin = float(residual[a]), start + a
            if residual[b] > high:
                high, imax = float(residual[b]), start + b
        if high - low <= width:
            return dt
        correction = (high - low - width) / (imax - imin)
        if imax > imin:
            lower = max(lower, dt + correction)
        else:
            upper = min(upper, dt + correction)
        if lower >= upper:
            break
    raise ValueError(f"{operation} needs uniformly spaced timestamps; selected window is irregular")


def require_matching_time(left, right) -> None:
    """Compare every timestamp, allowing only floating-point roundoff."""
    if left.ndim != 1 or left.shape != right.shape:
        raise ValueError("Binary math needs matching time axes")
    for start in range(0, len(left), _BLOCK):
        a, b = left[start:start + _BLOCK], right[start:start + _BLOCK]
        if not np.isfinite(a).all() or not np.isfinite(b).all():
            raise ValueError("Binary math needs finite timestamps")
        tolerance = np.finfo(np.float64).eps * max(float(np.max(np.abs(a))), float(np.max(np.abs(b)))) * 8
        # Roundoff must never permit a meaningful fraction of a sample period.
        steps = np.concatenate([np.diff(left[max(0, start - 1):start + _BLOCK]),
                                np.diff(right[max(0, start - 1):start + _BLOCK])])
        positive = steps[steps > 0]
        tolerance = min(tolerance, float(positive.min()) * .01) if len(positive) else 0.
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
                require_matching_time(shift_time(xt[:n], x_offset), shift_time(yt[:n], y_offset))
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
