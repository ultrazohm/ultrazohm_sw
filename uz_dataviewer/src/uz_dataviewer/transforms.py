"""GUI-free signal transforms used by the node graph (:mod:`nodes`).

Each function takes plain NumPy arrays and returns ``(out_time, out_y, info)``;
keeping them window-free and import-light means they are trivially unit-testable
and reusable from headless tests. The FFT transform lives in :mod:`analysis`
(``compute_fft``); this module holds the **math** and **filter** nodes.

Everything here is pure NumPy -- no SciPy -- so the native and Pyodide/WASM builds
run identical code (the same reason the decimator dropped ``tsdownsample``).
"""

from __future__ import annotations

import numpy as np

# -- math node ----------------------------------------------------------------
MATH_UNARY = ("scale", "offset", "derivative", "integral", "reciprocal")
MATH_BINARY = ("add", "sub", "mul", "div")
MATH_OPS = MATH_UNARY + MATH_BINARY


def _require_increasing_time(time: np.ndarray, op: str) -> None:
    """``op`` differentiates/integrates/filters against ``time``; it needs a finite,
    strictly increasing axis. A zero or negative step divides by zero in
    ``np.gradient`` / ``1/median(dt)`` or integrates backwards. Loaded logs already
    satisfy this (the loader validates monotonicity), so this only catches hand-built
    or duplicate-timestamp axes."""
    if not np.isfinite(time).all():
        raise ValueError(f"{op} needs a finite time axis (NaN/Inf present)")
    if time.shape[0] > 1 and np.any(np.diff(time) <= 0):
        raise ValueError(f"{op} needs a strictly increasing time axis")


def _binary_time_note(t1: np.ndarray, t2: np.ndarray) -> str:
    """Binary math index-aligns its two inputs (v1 does not resample). If they come
    from different time bases the result is still index-aligned, but the shared axis
    (``t1``) no longer describes B -- flag it in the node info so the result isn't read
    as time-aligned. O(1) endpoint check, cheap on multi-million-sample signals."""
    if t1.shape != t2.shape or t1.shape[0] == 0:
        return ""
    span = abs(float(t1[-1] - t1[0])) or 1.0
    if abs(float(t1[0] - t2[0])) > 1e-6 * span or abs(float(t1[-1] - t2[-1])) > 1e-6 * span:
        return " (index-aligned; time bases differ)"
    return ""


def math_node(inputs: list[tuple[np.ndarray, np.ndarray]], params: dict
              ) -> tuple[np.ndarray, np.ndarray, str]:
    """Arithmetic on one or two input signals.

    Unary (one input): ``scale`` (×k), ``offset`` (+k), ``derivative`` (d/dt),
    ``integral`` (∫ dt), ``reciprocal`` (1/A). Binary (two inputs, same
    length/time base): ``add`` (A+B), ``sub`` (A−B), ``mul`` (A·B), ``div`` (A/B).
    """
    op = str(params.get("op", "scale")).lower()
    if op not in MATH_OPS:
        raise ValueError(f"Unknown math op {op!r}; one of {', '.join(MATH_OPS)}")

    if op in MATH_UNARY:
        if len(inputs) != 1:
            raise ValueError(f"math op {op!r} needs exactly 1 input, got {len(inputs)}")
        time, y = inputs[0]
        time = np.asarray(time, dtype=np.float64)
        y = np.asarray(y, dtype=np.float64)
        if op == "scale":
            k = float(params.get("k", 1.0))
            return time, y * k, f"scale x{k:g}"
        if op == "offset":
            k = float(params.get("k", 0.0))
            return time, y + k, f"offset +{k:g}"
        if op == "derivative":
            _require_increasing_time(time, "derivative")
            return time, np.gradient(y, time), "derivative d/dt"
        if op == "reciprocal":
            with np.errstate(divide="ignore", invalid="ignore"):
                out = np.where(y != 0.0, 1.0 / y, 0.0)
            return time, out, "1 / A"
        # integral: cumulative trapezoid, starting at 0
        _require_increasing_time(time, "integral")
        dt = np.diff(time)
        area = np.concatenate([[0.0], np.cumsum((y[1:] + y[:-1]) * 0.5 * dt)])
        return time, area, "integral dt"

    # binary
    if len(inputs) != 2:
        raise ValueError(f"math op {op!r} needs exactly 2 inputs, got {len(inputs)}")
    (t1, y1), (t2, y2) = inputs
    y1 = np.asarray(y1, dtype=np.float64)
    y2 = np.asarray(y2, dtype=np.float64)
    if y1.shape != y2.shape:
        raise ValueError(
            f"binary math needs equal-length inputs ({y1.shape[0]} vs {y2.shape[0]}); "
            "v1 does not resample"
        )
    time = np.asarray(t1, dtype=np.float64)
    note = _binary_time_note(time, np.asarray(t2, dtype=np.float64))
    if op == "add":
        return time, y1 + y2, "A + B" + note
    if op == "sub":
        return time, y1 - y2, "A - B" + note
    if op == "mul":
        return time, y1 * y2, "A * B" + note
    with np.errstate(divide="ignore", invalid="ignore"):
        out = np.where(y2 != 0.0, y1 / y2, 0.0)
    return time, out, "A / B" + note


# -- filter node --------------------------------------------------------------
FILTER_TYPES = ("low", "high", "band")


def _fir_lowpass(fc_norm: float, taps: int) -> np.ndarray:
    """Windowed-sinc low-pass FIR. ``fc_norm`` is cutoff/fs in (0, 0.5)."""
    n_taps = taps if taps % 2 == 1 else taps + 1  # force odd -> integer delay
    n = np.arange(n_taps)
    mid = (n_taps - 1) / 2.0
    h = np.sinc(2.0 * fc_norm * (n - mid)) * np.hamming(n_taps)
    return h / h.sum()


def filter_node(time: np.ndarray, y: np.ndarray, params: dict
                ) -> tuple[np.ndarray, np.ndarray, str]:
    """Linear-phase windowed-sinc FIR filter (low/high/band-pass).

    ``cutoff`` (and ``cutoff2`` for band) are in Hz; the sample rate is inferred
    from the median time step. ``taps`` sets the kernel length (more = sharper).
    """
    ftype = str(params.get("type", "low")).lower()
    if ftype in ("lowpass", "bandpass", "highpass"):
        ftype = ftype.replace("pass", "")
    if ftype not in FILTER_TYPES:
        raise ValueError(f"Unknown filter type {ftype!r}; one of {', '.join(FILTER_TYPES)}")

    time = np.asarray(time, dtype=np.float64)
    y = np.asarray(y, dtype=np.float64)
    if time.shape[0] < 2:
        raise ValueError("filter needs at least 2 samples")
    _require_increasing_time(time, "filter")
    fs = 1.0 / float(np.median(np.diff(time)))
    taps = max(3, int(float(params.get("taps", 101))))
    fc = float(params.get("cutoff", 0.0))
    if fc <= 0.0:
        raise ValueError("filter 'cutoff' must be > 0 Hz")
    nyq = fs / 2.0
    fcn = min(fc / fs, 0.5 - 1e-6)
    lp = _fir_lowpass(fcn, taps)

    if ftype == "low":
        h, info = lp, f"low-pass {fc:g} Hz"
    elif ftype == "high":
        h = -lp.copy()
        h[len(lp) // 2] += 1.0  # spectral inversion
        info = f"high-pass {fc:g} Hz"
    else:  # band: low-pass(f2) - low-pass(f1)
        fc2 = float(params.get("cutoff2", 0.0))
        if fc2 <= fc:
            raise ValueError("band-pass needs cutoff2 > cutoff")
        h = _fir_lowpass(min(fc2 / fs, 0.5 - 1e-6), taps) - lp
        info = f"band-pass {fc:g}-{fc2:g} Hz"

    if fc >= nyq:
        info += f" (clamped; Nyquist {nyq:g} Hz)"
    out = np.convolve(y, h, mode="same")
    return time, out, f"{info}, {len(h)} taps"
