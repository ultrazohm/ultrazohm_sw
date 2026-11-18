"""Tests for the range-aware downsampler (no GUI required)."""

from __future__ import annotations


import numpy as np
import pytest


from uz_dataviewer.sources import ArraySource
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
    xs, ys = decimate_range(time, y, ArraySource(time, {'value': y}), 1000, 0, time.shape[0])
    assert xs.shape[0] <= 1000
    assert xs.shape == ys.shape


def test_downsample_respects_range():
    time = np.linspace(0.0, 100.0, 1_000_000)
    y = np.sin(time).astype(np.float32)
    start, stop = visible_slice(time, 10.0, 20.0)
    xs, ys = decimate_range(time, y, ArraySource(time, {'value': y}), 500, start, stop)
    assert xs.min() <= 10.1
    assert xs.max() >= 19.9
    assert xs.max() <= 20.2


def test_downsample_small_series_passthrough():
    time = np.array([0.0, 1.0, 2.0])
    y = np.array([1.0, 2.0, 3.0], dtype=np.float32)
    xs, ys = decimate_range(time, y, ArraySource(time, {'value': y}), 1000, 0, time.shape[0])  # window <= n_out
    np.testing.assert_array_equal(xs, time)
    np.testing.assert_array_equal(ys, y)


def test_downsample_budget_is_max_points_not_pixel_width():
    # The sampler honors its supplied budget. The plot panel separately caps
    # that budget by pixel width and trace count before calling the sampler.
    time = np.linspace(0.0, 50.0, 5_000_000)
    y = np.sin(time).astype(np.float32)
    max_points = 20_000

    start, stop = 1_000_000, 1_005_500  # 5500 raw samples, well under the budget
    xs, ys = decimate_range(time, y, ArraySource(time, {'value': y}), max_points, start, stop)
    assert xs.shape[0] == stop - start  # raw, untouched
    np.testing.assert_array_equal(xs, time[start:stop])
    np.testing.assert_array_equal(ys, y[start:stop])

    start, stop = 0, 5_000_000  # far more than the budget -> envelope to ~max_points
    xs, ys = decimate_range(time, y, ArraySource(time, {'value': y}), max_points, start, stop)
    assert xs.shape[0] <= max_points
    assert xs.shape[0] >= max_points // 2  # lands near the budget, not far below it


@pytest.mark.parametrize('dtype', [np.int32, np.int64, np.uint64])
@pytest.mark.parametrize('window,expected', [((.2, 1.2), (1, 2)), ((.8, .9), (1, 1)), ((-.8, -.2), (0, 0))])
def test_integer_time_preserves_fractional_bounds(dtype, window, expected):
    assert visible_slice(np.arange(4, dtype=dtype), *window, padding=False) == expected
