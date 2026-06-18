"""Signal transforms used by the FFT window.

Kept GUI-free so it is unit-testable and reusable from other analysis windows.
"""

from __future__ import annotations

from collections import OrderedDict

import numpy as np

from .downsample import visible_slice

# Hann windows are recomputed per FFT; cache by length (with the window sum, used
# for the amplitude correction below) since the same window is re-used across
# recomputes at the same span (cheap, avoids a cos over millions of samples each
# Compute). Bounded LRU: a long session computing FFTs at many distinct window
# lengths would otherwise retain a float32 window per length (~60 MB at 15 M
# samples) for the life of the process.
_HANN_CACHE_MAX = 8
_HANN_CACHE: "OrderedDict[int, tuple[np.ndarray, float]]" = OrderedDict()


def _hann(n: int) -> tuple[np.ndarray, float]:
    """Return the length-``n`` Hann window and its sum (coherent gain · n)."""
    cached = _HANN_CACHE.get(n)
    if cached is None:
        w = np.hanning(n).astype(np.float32)
        cached = (w, float(w.sum(dtype=np.float64)))
        _HANN_CACHE[n] = cached
        if len(_HANN_CACHE) > _HANN_CACHE_MAX:
            _HANN_CACHE.popitem(last=False)  # evict least-recently-used
    else:
        _HANN_CACHE.move_to_end(n)  # mark most-recently-used
    return cached


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
    if time.shape[0] == 0:
        return FftResult(None, None, "No samples in this run to transform.")
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
    # A single O(n) pass at Compute (not per frame): NaN/Inf in the window would
    # otherwise propagate through the whole spectrum. The transform assumes a
    # uniform time base, so masking would corrupt it -- reject instead.
    if not np.isfinite(ys).all():
        return FftResult(None, None, "Selected window has non-finite samples (NaN/Inf); cannot compute FFT.")

    # Logs are uniformly sampled (the rate can differ between logs), so the step is
    # exactly the span / interval count -- O(1), no full np.diff + median over the
    # window (which is costly on a multi-million-sample full-window FFT).
    dt = (float(ts[-1]) - float(ts[0])) / (n - 1)
    if not np.isfinite(dt) or dt <= 0:
        return FftResult(None, None, "Time axis is not increasing; cannot compute FFT.")

    if remove_dc:
        ys -= ys.mean(dtype=np.float64)  # accumulate the mean in float64, subtract in place
    # Amplitude normalisation is by the window's *coherent gain* (Σw): a tone of
    # amplitude A peaks at A/2·Σw, so 2/Σw recovers A. For the rectangular case
    # Σw = n, which is the plain 2/n. (Using 2/n with a Hann window under-reports
    # every amplitude by ~2x, since Σw ≈ n/2.)
    if window:
        w, wsum = _hann(n)
        ys *= w
        norm = 2.0 / wsum
    else:
        norm = 2.0 / n

    # Zero-pad to a 5-smooth length so rfft avoids the large-prime slow path; the
    # amplitude stays normalised by the *original* window (padding only interpolates bins).
    m = _next_fast_len(n)
    spectrum = np.fft.rfft(ys, n=m)
    freqs = np.fft.rfftfreq(m, d=dt)
    mag = norm * np.abs(spectrum)
    # The single-sided ×2 folds the negative-frequency twin onto each bin; the DC
    # bin (and the Nyquist bin at even length) has no twin, so halve it back.
    if mag.size:
        mag[0] *= 0.5
        if m % 2 == 0:
            mag[-1] *= 0.5
    info = f"{n:,} samples, fs = {1.0 / dt:,.1f} Hz, window [{x_min:.4f}, {x_max:.4f}] s"
    return FftResult(freqs.astype(np.float32), mag.astype(np.float32), info)
