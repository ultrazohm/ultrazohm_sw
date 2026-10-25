"""Shared validation for user-supplied view coordinates."""
import math


def finite_float(value):
    value = float(value)
    if not math.isfinite(value):
        raise ValueError("Coordinate must be finite")
    return value


def axis_limits(lo, hi):
    lo, hi = finite_float(lo), finite_float(hi)
    if hi <= lo:
        raise ValueError("Axis limits must be finite and increasing")
    return lo, hi


def expanded_range(lo, hi, intervals=1):
    """Expand degenerate data ranges enough for distinct float64 bin centers.

    Preserve ordinary nonconstant ranges. The ULP-based floor leaves room for
    rounding both edges and centers at large magnitudes.
    """
    lo, hi = finite_float(lo), finite_float(hi)
    if hi < lo or intervals < 1:
        raise ValueError("Data range must be ordered and interval count positive")
    width = math.ulp(max(abs(lo), abs(hi))) * intervals * 8
    if hi == lo:
        width = max(1., width)
    if hi - lo < width:
        upper = lo + width
        if math.isfinite(upper):
            hi = upper
        else:
            lo = hi - width
    return axis_limits(lo, hi)
