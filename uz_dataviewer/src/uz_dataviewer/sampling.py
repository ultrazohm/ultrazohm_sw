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
