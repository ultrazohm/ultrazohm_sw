"""Signal transforms used by the FFT window.

Kept GUI-free so it is unit-testable and reusable from other analysis windows.
"""

from __future__ import annotations

import numpy as np

from .downsample import visible_slice


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
    ys = y[start:stop].astype(np.float64)
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
        ys = ys - ys.mean()
    if window:
        ys = ys * np.hanning(n)

    spectrum = np.fft.rfft(ys)
    freqs = np.fft.rfftfreq(n, d=dt)
    mag = (2.0 / n) * np.abs(spectrum)
    info = f"{n:,} samples, fs = {1.0 / dt:,.1f} Hz, window [{x_min:.4f}, {x_max:.4f}] s"
    return FftResult(freqs.astype(np.float32), mag.astype(np.float32), info)
