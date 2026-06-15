"""Tests for the range-aware downsampler (no GUI required)."""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.downsample import downsample_xy, visible_slice  # noqa: E402


def test_visible_slice_pads_edges():
    time = np.linspace(0.0, 10.0, 101)  # step 0.1
    start, stop = visible_slice(time, 5.0, 6.0)
    assert time[start] <= 5.0
    assert time[stop - 1] >= 6.0


def test_downsample_reduces_point_count():
    time = np.linspace(0.0, 100.0, 1_000_000)
    y = np.sin(time).astype(np.float32)
    xs, ys = downsample_xy(time, y, n_out=1000)
    assert xs.shape[0] <= 1000
    assert xs.shape == ys.shape


def test_downsample_respects_range():
    time = np.linspace(0.0, 100.0, 1_000_000)
    y = np.sin(time).astype(np.float32)
    xs, ys = downsample_xy(time, y, n_out=500, x_min=10.0, x_max=20.0)
    assert xs.min() <= 10.1
    assert xs.max() >= 19.9
    assert xs.max() <= 20.2


def test_downsample_small_series_passthrough():
    time = np.array([0.0, 1.0, 2.0])
    y = np.array([1.0, 2.0, 3.0], dtype=np.float32)
    xs, ys = downsample_xy(time, y, n_out=1000)
    np.testing.assert_array_equal(xs, time)
    np.testing.assert_array_equal(ys, y)
