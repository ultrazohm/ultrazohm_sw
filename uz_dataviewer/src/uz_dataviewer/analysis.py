"""Signal transforms used by the FFT window.

Kept GUI-free so it is unit-testable and reusable from other analysis windows.
"""

from __future__ import annotations

import numpy as np

from .downsample import visible_slice

def _hann(n: int) -> tuple[np.ndarray, float]:
    """Return a computation-owned Hann window and its coherent-gain sum.

    Do not retain potentially large windows after their FFT completes.
    """
    w = np.hanning(n).astype(np.float32)
    return w, float(w.sum(dtype=np.float64))


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
    """Single-sided amplitude spectrum plus a human-readable status line.

    Attributes:
        freqs: Frequency axis (Hz), ``None`` on failure.
        mag: Amplitude (same units as input ``y``), ``None`` on failure.
        info: Human-readable description of the computation or the failure reason.
        ok: ``True`` when ``freqs`` and ``mag`` are populated.
    """

    def __init__(self, freqs: np.ndarray | None, mag: np.ndarray | None, info: str) -> None:
        self.freqs = freqs
        self.mag = mag
        self.info = info

    @property
    def ok(self) -> bool:
        """``True`` when the computation succeeded and ``freqs``/``mag`` are populated."""
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
    time, y = np.asarray(time), np.asarray(y)
    if time.ndim != 1 or y.ndim != 1 or time.shape != y.shape:
        return FftResult(None, None, "FFT needs equal-length one-dimensional time and value arrays.")
    if time.shape[0] == 0:
        return FftResult(None, None, "No samples in this run to transform.")
    if x_max <= x_min:
        return FftResult(None, None, "Selected window is too short for an FFT.")

    start, stop = visible_slice(time, x_min, x_max, padding=False)
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

    from .sampling import regular_sample_interval
    try:
        dt = regular_sample_interval(ts, "FFT")
    except ValueError as exc:
        return FftResult(None, None, str(exc))

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


def compute_signal_fft(run, channel, x_min, x_max, *, remove_dc=True, window=True,
                       cancel=None, label=None):
    """Read and validate one spectrum, reporting failures with the signal identity."""
    label = label or f"{channel} @ {run.label}"
    try:
        t, values = run.read_window([channel], x_min, x_max, cancel)
        result = compute_fft(t, values[channel], x_min, x_max,
                             remove_dc=remove_dc, window=window)
        if not result.ok:
            raise ValueError(result.info)
    except (ValueError, OSError) as exc:
        raise ValueError(f"Cannot compute FFT for {label}: {exc}") from exc
    return result


def histogram_sources(series, lo, hi, bins, cancel=None):
    """Two-pass histogram over raw batches with common edges for all sources.

    series: (label, source, channel, display_time_offset). Display summaries are
    never used here. Memory is proportional to one batch and the output bins.
    """
    from .sources import check
    ranges, minimum, maximum, dropped = [], None, None, 0
    for label, source, channel, offset in series:
        check(cancel)
        start, stop = source.bounds(lo - offset, hi - offset, cancel, padding=False)
        count = 0
        for _, values in source.iter_raw([channel], start, stop, cancel):
            y = values[channel]
            finite = np.isfinite(y)
            dropped += int(len(y) - finite.sum())
            y = y[finite]
            if len(y):
                low, high = float(y.min()), float(y.max())
                minimum = low if minimum is None else min(minimum, low)
                maximum = high if maximum is None else max(maximum, high)
                count += len(y)
        if count:
            ranges.append((label, source, channel, start, stop, count))
    if minimum is None:
        return [], 0, dropped
    from .validation import expanded_range
    bins = max(1, bins)
    minimum, maximum = expanded_range(minimum, maximum, bins)
    edges = np.linspace(minimum, maximum, bins + 1)
    centers = (edges[:-1] + edges[1:]) / 2
    results, total = [], 0
    for label, source, channel, start, stop, count in ranges:
        counts = np.zeros(len(centers), dtype=np.int64)
        for _, values in source.iter_raw([channel], start, stop, cancel):
            y = values[channel]
            counts += np.histogram(y[np.isfinite(y)], bins=edges)[0]
        results.append((label, centers, counts, float(edges[1] - edges[0])))
        total += count
    return results, total, dropped
