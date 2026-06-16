"""Unit tests for the GUI-free node transforms (math + filter)."""

from __future__ import annotations

import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.transforms import filter_node, math_node  # noqa: E402


def _sine(f, n=4000, dur=1.0):
    t = np.linspace(0.0, dur, n)
    return t, np.sin(2 * np.pi * f * t).astype(np.float32)


def test_math_scale_and_offset():
    t, y = _sine(5)
    _, ys, _ = math_node([(t, y)], {"op": "scale", "k": "3"})
    np.testing.assert_allclose(ys, y * 3, rtol=1e-5)
    _, yo, _ = math_node([(t, y)], {"op": "offset", "k": "2"})
    np.testing.assert_allclose(yo, y + 2, rtol=1e-5)


def test_math_derivative_amplitude():
    f = 5.0
    t, y = _sine(f)
    _, dy, _ = math_node([(t, y)], {"op": "derivative"})
    # d/dt sin(2*pi*f*t) = 2*pi*f*cos(...), so peak ~ 2*pi*f.
    assert abs(dy[10:-10].max() - 2 * np.pi * f) < 0.05 * 2 * np.pi * f


def test_math_integral_is_inverse_of_derivative():
    t, y = _sine(5)
    _, dy, _ = math_node([(t, y)], {"op": "derivative"})
    _, yi, _ = math_node([(t, dy)], {"op": "integral"})
    # integral of the derivative recovers the signal (up to a constant ~0 here).
    assert np.std((yi - y)[20:-20]) < 0.05


def test_math_binary_requires_equal_length():
    t1, y1 = _sine(5, n=1000)
    t2, y2 = _sine(5, n=900)
    with pytest.raises(ValueError):
        math_node([(t1, y1), (t2, y2)], {"op": "sub"})


def test_math_sub():
    t, y = _sine(5)
    _, d, _ = math_node([(t, y), (t, y)], {"op": "sub"})
    assert np.allclose(d, 0.0)


def test_math_add():
    t, y = _sine(5)
    _, d, _ = math_node([(t, y), (t, y)], {"op": "add"})
    np.testing.assert_allclose(d, 2.0 * y, rtol=1e-5)


def test_filter_lowpass_removes_high_freq():
    t = np.linspace(0.0, 1.0, 4000)  # fs = 4000 Hz
    low = np.sin(2 * np.pi * 5 * t)
    sig = (low + np.sin(2 * np.pi * 400 * t)).astype(np.float32)
    _, out, _ = filter_node(t, sig, {"type": "low", "cutoff": "40", "taps": "201"})
    interior = slice(300, -300)
    # The 400 Hz term (std contribution ~0.707) is gone -> close to the 5 Hz term.
    assert np.std(out[interior]) < 0.8
    assert np.corrcoef(out[interior], low[interior])[0, 1] > 0.99


def test_filter_highpass_keeps_high_freq():
    t = np.linspace(0.0, 1.0, 4000)
    high = np.sin(2 * np.pi * 400 * t)
    sig = (np.sin(2 * np.pi * 5 * t) + high).astype(np.float32)
    _, out, _ = filter_node(t, sig, {"type": "high", "cutoff": "100", "taps": "201"})
    interior = slice(300, -300)
    assert np.corrcoef(out[interior], high[interior])[0, 1] > 0.95


def test_filter_requires_positive_cutoff():
    t, y = _sine(5)
    with pytest.raises(ValueError):
        filter_node(t, y, {"type": "low", "cutoff": "0"})
