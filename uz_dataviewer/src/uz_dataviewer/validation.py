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


def bounded_int(value, minimum, maximum, label):
    if isinstance(value, bool):
        raise ValueError(f"{label} must be an integer")
    try:
        number = int(value)
    except (TypeError, ValueError, OverflowError) as exc:
        raise ValueError(f"{label} must be an integer") from exc
    if number != float(value) or not minimum <= number <= maximum:
        raise ValueError(f"{label} must be an integer from {minimum} to {maximum}")
    return number


def histogram_bins(value):
    # Bound both native integer widgets and per-signal bin allocations.
    return bounded_int(value, 1, 100_000, "Histogram bins")


def coordinates(value, length):
    if not isinstance(value, (list, tuple)) or len(value) != length:
        raise ValueError(f"Expected {length} coordinates")
    return tuple(finite_float(v) for v in value)


def spy_rectangle(value):
    xmin, ymin, xmax, ymax = coordinates(value, 4)
    axis_limits(xmin, xmax)
    axis_limits(ymin, ymax)
    return xmin, ymin, xmax, ymax


def display_budget(value):
    return bounded_int(value, 2, 1_000_000, "Display points")


def cache_budget_mb(value):
    return bounded_int(value, 1, 1_048_576, "Cache MiB")


def boolean(value):
    if not isinstance(value, bool):
        raise ValueError("Expected a JSON boolean")
    return value
