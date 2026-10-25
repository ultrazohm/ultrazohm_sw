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
