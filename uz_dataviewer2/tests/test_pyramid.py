"""Tests for the range-aware min/max envelope decimation (large-log path)."""

from __future__ import annotations

import os
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.downsample import Pyramid, decimate_range, visible_slice  # noqa: E402


def test_pyramid_envelope_bounds_the_signal():
    n = 4_000_000
    t = np.linspace(0.0, 100.0, n)
    y = np.sin(t * 7.0).astype(np.float32)
    pyr = Pyramid.build(y)

    xs, ys = pyr.query(t, y, 4000, 0, n)
    assert xs.shape == ys.shape
    assert ys.min() <= y.min() + 1e-3  # envelope contains the true extremes
    assert ys.max() >= y.max() - 1e-3
    assert xs.min() >= t[0] - 1e-6 and xs.max() <= t[-1] + 1e-6
    assert bool(np.all(np.diff(xs) >= 0))  # x at true positions, in order


def test_output_count_is_consistent_across_zoom():
    """The bug we fixed: output must stay ~n_out at every zoom, not jump 8x."""
    n = 20_000_000
    t = np.linspace(0.0, 100.0, n)
    y = np.sin(t).astype(np.float32)
    pyr = Pyramid.build(y)
    n_out = 10_000
    counts = []
    for frac in (1.0, 0.5, 0.2, 0.07, 0.02):
        xs, _ = decimate_range(t, y, pyr, n_out, 0, int(n * frac))
        counts.append(xs.shape[0])
    # Every zoom yields between ~n_out/2 and n_out points -- never collapses.
    assert all(n_out // 2 <= c <= n_out + 4 for c in counts), counts


def test_spike_is_preserved():
    n = 5_000_000
    t = np.linspace(0.0, 10.0, n)
    y = np.zeros(n, dtype=np.float32)
    y[1_234_567] = 42.0
    pyr = Pyramid.build(y)
    _, ys = decimate_range(t, y, pyr, 2000, 0, n)
    assert ys.max() >= 42.0 - 1e-3


def test_oneshot_envelope_true_positions():
    # Below the pyramid threshold: one-shot path, still true-position envelope.
    n = 300_000
    t = np.linspace(0.0, 10.0, n)
    y = np.sin(t * 50.0).astype(np.float32)
    xs, ys = decimate_range(t, y, None, 2000, 0, n)
    assert 1000 <= xs.shape[0] <= 2000
    assert ys.min() <= y.min() + 1e-3 and ys.max() >= y.max() - 1e-3
    assert bool(np.all(np.diff(xs) >= 0))


def test_decimate_range_passthrough_when_small():
    t = np.linspace(0.0, 1.0, 500)
    y = np.cos(t).astype(np.float32)
    xs, ys = decimate_range(t, y, None, 2000, 0, 500)  # window <= n_out
    np.testing.assert_array_equal(xs, t)
    np.testing.assert_array_equal(ys, y)


def test_zoom_window_confines_x():
    n = 2_000_000
    t = np.linspace(0.0, 10.0, n)
    y = np.sin(t * 30.0).astype(np.float32)
    pyr = Pyramid.build(y)
    start, stop = visible_slice(t, 5.0, 5.1)
    xs, _ = decimate_range(t, y, pyr, 2000, start, stop)
    assert xs.min() >= 4.9 and xs.max() <= 5.2
