"""Tests for the multi-resolution min/max pyramid (large-log decimation)."""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.downsample import Pyramid, decimate_range, visible_slice  # noqa: E402


def test_pyramid_envelope_bounds_the_signal():
    n = 2_000_000
    t = np.linspace(0.0, 100.0, n)
    y = np.sin(t * 7.0).astype(np.float32)
    pyr = Pyramid.build(y)

    # Full window, modest budget -> the envelope must contain the true extremes.
    start, stop = 0, n
    xs, ys = pyr.query(t, 2000, start, stop)
    assert xs.shape == ys.shape
    assert xs.shape[0] <= 4000  # ~2 points per bucket, bounded by the budget
    assert ys.min() <= y.min() + 1e-3
    assert ys.max() >= y.max() - 1e-3
    # X stays within the queried window and is non-decreasing.
    assert xs.min() >= t[0] - 1e-6 and xs.max() <= t[-1] + 1e-6
    assert bool(np.all(np.diff(xs) >= 0))


def test_pyramid_preserves_a_spike():
    n = 1_000_000
    t = np.linspace(0.0, 10.0, n)
    y = np.zeros(n, dtype=np.float32)
    y[123_456] = 42.0  # a single one-sample spike
    pyr = Pyramid.build(y)
    _, ys = pyr.query(t, 2000, 0, n)
    assert ys.max() >= 42.0 - 1e-3  # min/max envelope keeps the spike


def test_pyramid_zoom_reveals_detail():
    n = 1_000_000
    t = np.linspace(0.0, 10.0, n)
    y = np.sin(t * 50.0).astype(np.float32)
    pyr = Pyramid.build(y)
    # A narrow window resolves to a finer level (more points per unit time).
    start, stop = visible_slice(t, 5.0, 5.01)
    xs, _ = pyr.query(t, 2000, start, stop)
    assert xs.min() >= 4.9 and xs.max() <= 5.11  # confined to the zoom window


def test_decimate_range_passthrough_when_small():
    t = np.linspace(0.0, 1.0, 500)
    y = np.cos(t).astype(np.float32)
    xs, ys = decimate_range(t, y, None, 2000, 0, 500)  # window <= n_out
    np.testing.assert_array_equal(xs, t)
    np.testing.assert_array_equal(ys, y)


def test_decimate_range_uses_pyramid_when_present():
    n = 500_000
    t = np.linspace(0.0, 10.0, n)
    y = np.sin(t).astype(np.float32)
    pyr = Pyramid.build(y)
    xs, ys = decimate_range(t, y, pyr, 1000, 0, n)
    assert xs.shape[0] <= 2200          # bounded by the budget, not n
    assert xs.shape[0] == ys.shape[0]
