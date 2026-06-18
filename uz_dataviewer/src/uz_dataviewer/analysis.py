"""Signal transforms used by the FFT window.

Kept GUI-free so it is unit-testable and reusable from other analysis windows.
"""

from __future__ import annotations

import numpy as np

from .downsample import visible_slice

# Hann windows are recomputed per FFT; cache by length since the same window is
# re-used across recomputes at the same span (cheap memory, avoids a cos over
# millions of samples each Compute).
_HANN_CACHE: dict[int, np.ndarray] = {}


def _hann(n: int) -> np.ndarray:
    w = _HANN_CACHE.get(n)
    if w is None:
        w = np.hanning(n).astype(np.float32)
        _HANN_CACHE[n] = w
    return w


def _next_fast_len(n: int) -> int:
    """Smallest 5-smooth (2^a·3^b·5^c) integer >= ``n``.

    ``np.fft.rfft`` is dramatically faster on 5-smooth lengths than on lengths with
    a large prime factor -- a ~9x cliff at multi-million-sample windows -- so the
    transform zero-pads up to one. Pure-Python (no scipy) to keep the dependency
    list lean; the next power of two is always a valid upper bound.
    """
    if n <= 6:
        return n
    best = 1 << (n - 1).bit_length()  # next power of two >= n
    p5 = 1
    while p5 < best:
        p3 = p5
        while p3 < best:
            x = p3
            while x < n:
                x <<= 1
            if x < best:
                best = x
            p3 *= 3
        p5 *= 5
    return best


class FftResult:
    """Single-sided amplitude spectrum plus a human-readable status line."""

    def __init__(self, freqs: np.ndarray | None, mag: np.ndarray | None, info: str) -> None:
        self.freqs = freqs
        self.mag = mag
        self.info = info

    @property
    def ok(self) -> bool:
        return self.freqs is not None and self.mag is not None


def compute_fft(
    time: np.ndarray,
    y: np.ndarray,
    x_min: float,
    x_max: float,
    *,
    remove_dc: bool = True,
    window: bool = True,
) -> FftResult:
    """Single-sided amplitude spectrum of ``y`` over ``[x_min, x_max]``.

    The window is selected by time so zooming the source plot narrows the
    transform. Returns an empty :class:`FftResult` (with an ``info`` reason) when
    the slice is too short or the time axis is unusable.
    """
    if x_max <= x_min:
        x_min, x_max = float(time[0]), float(time[-1])

    start, stop = visible_slice(time, x_min, x_max)
    # Keep float32 (JavaScope data is float32): numpy's pocketfft preserves it as a
    # complex64 transform -- half the memory of the old float64 upcast (big on a
    # multi-million-sample full-window FFT, and on the WASM heap) and faster. A copy
    # so the demean/window can run in place.
    ys = np.array(y[start:stop], dtype=np.float32)
    ts = time[start:stop]
    n = ys.shape[0]
    if n < 4:
        return FftResult(None, None, "Selected window is too short for an FFT.")

    # Logs are uniformly sampled (the rate can differ between logs), so the step is
    # exactly the span / interval count -- O(1), no full np.diff + median over the
    # window (which is costly on a multi-million-sample full-window FFT).
    dt = (float(ts[-1]) - float(ts[0])) / (n - 1)
    if dt <= 0:
        return FftResult(None, None, "Time axis is not increasing; cannot compute FFT.")

    if remove_dc:
        ys -= ys.mean(dtype=np.float64)  # accumulate the mean in float64, subtract in place
    if window:
        ys *= _hann(n)

    # Zero-pad to a 5-smooth length so rfft avoids the large-prime slow path; the
    # amplitude stays normalised by the *original* n (padding only interpolates bins).
    m = _next_fast_len(n)
    spectrum = np.fft.rfft(ys, n=m)
    freqs = np.fft.rfftfreq(m, d=dt)
    mag = (2.0 / n) * np.abs(spectrum)
    info = f"{n:,} samples, fs = {1.0 / dt:,.1f} Hz, window [{x_min:.4f}, {x_max:.4f}] s"
    return FftResult(freqs.astype(np.float32), mag.astype(np.float32), info)
