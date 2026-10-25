"""Unit tests for the GUI-free node transforms (math + filter)."""

from __future__ import annotations

import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

from uz_dataviewer.transforms import filter_node, math_node


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


@pytest.mark.parametrize('interior_only', [False, True])
def test_math_binary_rejects_time_base_mismatch(interior_only):
    t1, y1 = _sine(5, n=1000)
    t2 = t1.copy()
    if interior_only:
        t2[500] += .0001  # endpoints still match; index pairing is invalid
    else:
        t2 += 10.
    with pytest.raises(ValueError, match="matching time axes"):
        math_node([(t1, y1), (t2, y1)], {"op": "sub"})
    _, result, _ = math_node([(t1, y1), (t1.copy(), y1)], {"op": "sub"})
    np.testing.assert_array_equal(result, np.zeros(len(t1)))


def test_derivative_rejects_non_increasing_time():
    t = np.array([0.0, 0.1, 0.1, 0.2])  # duplicate timestamp -> dt = 0
    y = np.array([0.0, 1.0, 2.0, 3.0], dtype=np.float32)
    with pytest.raises(ValueError, match="strictly increasing"):
        math_node([(t, y)], {"op": "derivative"})


def test_math_sub():
    t, y = _sine(5)
    _, d, _ = math_node([(t, y), (t, y)], {"op": "sub"})
    assert np.allclose(d, 0.0)


def test_math_add():
    t, y = _sine(5)
    _, d, _ = math_node([(t, y), (t, y)], {"op": "add"})
    np.testing.assert_allclose(d, 2.0 * y, rtol=1e-5)


def test_math_mul():
    t, y = _sine(5)
    _, p, _ = math_node([(t, y), (t, y)], {"op": "mul"})
    np.testing.assert_allclose(p, np.asarray(y, float) ** 2, rtol=1e-5)


def test_math_reciprocal_guards_zero():
    t = np.linspace(0.0, 1.0, 5)
    y = np.array([2.0, 0.0, 4.0, 0.5, 0.0], dtype=np.float32)
    _, r, _ = math_node([(t, y)], {"op": "reciprocal"})
    np.testing.assert_allclose(r, [0.5, np.nan, 0.25, 2.0, np.nan], rtol=1e-6)


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


@pytest.mark.parametrize('ftype', ['low', 'high', 'band'])
def test_filter_rejects_irregular_sampling(ftype):
    t = np.array([0., .001, .002, 1.003, 1.004, 1.005, 1.006, 1.007])
    with pytest.raises(ValueError, match='uniformly spaced'):
        filter_node(t, np.arange(8.), {'type': ftype, 'cutoff': 100, 'cutoff2': 200})


@pytest.mark.parametrize('parameter', ['cutoff', 'cutoff2'])
@pytest.mark.parametrize('value', [np.nan, np.inf])
def test_filter_rejects_nonfinite_cutoffs(parameter, value):
    t, y = _sine(5)
    params = {'type': 'band', 'cutoff': 20, 'cutoff2': 40, parameter: value}
    with pytest.raises(ValueError, match='finite'):
        filter_node(t, y, params)


def test_sampling_roundoff_and_block_boundary_validation():
    # Timestamp roundoff at a large origin must not reject an otherwise regular grid.
    t = 1e6 + np.arange(65540) * .001
    y = np.sin(np.arange(len(t)))
    _, filtered, _ = filter_node(t, y, {'cutoff': 100, 'taps': 3})
    assert np.isfinite(filtered).all()
    rounded = np.nextafter(t, np.inf)
    _, difference, _ = math_node([(t, y), (rounded, y)], {'op': 'sub'})
    assert not difference.any()
    changed = t.copy()
    changed[65536] += .0001
    with pytest.raises(ValueError, match='matching time axes'):
        math_node([(t, y), (changed, y)], {'op': 'sub'})
    with pytest.raises(ValueError, match='uniformly spaced'):
        filter_node(changed, y, {'cutoff': 100, 'taps': 3})


def test_short_filter_keeps_length():
    t = np.arange(10.)
    out_t, out_y, _ = filter_node(t, t, {'type':'low', 'cutoff':.1})
    assert out_t.shape == out_y.shape == (10,)
