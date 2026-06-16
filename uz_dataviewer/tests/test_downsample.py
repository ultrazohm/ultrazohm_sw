"""Tests for the range-aware downsampler (no GUI required)."""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.downsample import decimate_range, visible_slice  # noqa: E402


def test_visible_slice_pads_edges():
    time = np.linspace(0.0, 10.0, 101)  # step 0.1
    start, stop = visible_slice(time, 5.0, 6.0)
    assert time[start] <= 5.0
    assert time[stop - 1] >= 6.0


def test_visible_slice_is_fast_on_float32():
    """Regression: searchsorted on a float32 array with a Python-float scalar
    up-casts the whole array (~31 ms on 7.5 M points) -> the FFT-display FPS bug.
    visible_slice must coerce the scalar to the array dtype and stay O(log n)."""
    import time as _time

    freqs = np.linspace(0.0, 5e5, 7_500_001).astype(np.float32)  # FFT freqs are float32
    start, stop = visible_slice(freqs, 1.0e5, 2.0e5)
    assert freqs[start] <= 1.0e5 and freqs[stop - 1] >= 2.0e5
    t0 = _time.perf_counter()
    for _ in range(50):
        visible_slice(freqs, 1.0e5, 2.0e5)
    per_call_ms = (_time.perf_counter() - t0) / 50 * 1e3
    # An up-cast is ~30 ms/call; a dtype-matched search is microseconds. 1 ms is
    # a generous ceiling that still fails loudly if the up-cast ever returns.
    assert per_call_ms < 1.0, f"visible_slice too slow ({per_call_ms:.2f} ms) -- float32 up-cast?"


def test_downsample_reduces_point_count():
    time = np.linspace(0.0, 100.0, 1_000_000)
    y = np.sin(time).astype(np.float32)
    xs, ys = decimate_range(time, y, None, 1000, 0, time.shape[0])
    assert xs.shape[0] <= 1000
    assert xs.shape == ys.shape


def test_downsample_respects_range():
    time = np.linspace(0.0, 100.0, 1_000_000)
    y = np.sin(time).astype(np.float32)
    start, stop = visible_slice(time, 10.0, 20.0)
    xs, ys = decimate_range(time, y, None, 500, start, stop)
    assert xs.min() <= 10.1
    assert xs.max() >= 19.9
    assert xs.max() <= 20.2


def test_downsample_small_series_passthrough():
    time = np.array([0.0, 1.0, 2.0])
    y = np.array([1.0, 2.0, 3.0], dtype=np.float32)
    xs, ys = decimate_range(time, y, None, 1000, 0, time.shape[0])  # window <= n_out
    np.testing.assert_array_equal(xs, time)
    np.testing.assert_array_equal(ys, y)
