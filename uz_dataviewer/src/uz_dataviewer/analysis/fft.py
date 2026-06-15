"""Amplitude-spectrum FFT over a (cursor-)selected region of a signal."""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np

WINDOWS = ("hann", "hamming", "rectangular")


@dataclass
class FftResult:
    frequencies: np.ndarray
    amplitudes: np.ndarray
    sample_rate: float
    n_samples: int
    t_start: float
    t_stop: float


def compute_fft(
    time: np.ndarray,
    values: np.ndarray,
    t_start: float | None = None,
    t_stop: float | None = None,
    window: str = "hann",
    remove_dc: bool = True,
) -> FftResult | None:
    """Single-sided amplitude spectrum of values within [t_start, t_stop].

    Returns None if the region holds fewer than 8 samples. Amplitudes are
    corrected for the window's coherent gain, so a 1 V sine reads ~1 V.
    """
    if len(time) < 8:
        return None

    start_index = 0 if t_start is None else int(np.searchsorted(time, t_start, "left"))
    stop_index = (
        len(time) if t_stop is None else int(np.searchsorted(time, t_stop, "right"))
    )
    start_index = max(start_index, 0)
    stop_index = min(stop_index, len(time))
    if stop_index - start_index < 8:
        return None

    segment_time = time[start_index:stop_index]
    segment = np.asarray(values[start_index:stop_index], dtype=np.float64)

    if np.isnan(segment).any():
        segment = np.nan_to_num(segment, nan=float(np.nanmean(segment)))

    dt = float(np.median(np.diff(segment_time)))
    if dt <= 0:
        return None
    sample_rate = 1.0 / dt

    if remove_dc:
        segment = segment - segment.mean()

    n = len(segment)
    if window == "hann":
        win = np.hanning(n)
    elif window == "hamming":
        win = np.hamming(n)
    else:
        win = np.ones(n)
    coherent_gain = win.mean()

    spectrum = np.fft.rfft(segment * win)
    amplitudes = np.abs(spectrum) * 2.0 / (n * coherent_gain)
    amplitudes[0] /= 2.0  # DC bin is not doubled
    if n % 2 == 0 and len(amplitudes) > 1:
        amplitudes[-1] /= 2.0  # neither is Nyquist

    frequencies = np.fft.rfftfreq(n, d=dt)

    return FftResult(
        frequencies=frequencies,
        amplitudes=amplitudes,
        sample_rate=sample_rate,
        n_samples=n,
        t_start=float(segment_time[0]),
        t_stop=float(segment_time[-1]),
    )
