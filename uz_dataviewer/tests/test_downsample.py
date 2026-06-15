import numpy as np

from uz_dataviewer.core import downsample


def test_small_input_passthrough():
    x = np.arange(10.0)
    y = np.sin(x)
    indices = downsample.downsample_indices(x, y, 100)
    np.testing.assert_array_equal(indices, np.arange(10))


def test_output_size_bounded():
    x = np.arange(1_000_000, dtype=np.float64)
    y = np.sin(x * 0.001)
    indices = downsample.downsample_indices(x, y, 2000)
    assert len(indices) <= 2100  # minmax may add first/last on top
    assert len(indices) >= 1000


def test_spikes_are_preserved():
    """Min/max-based downsampling must keep isolated extreme samples."""
    n = 500_000
    x = np.arange(n, dtype=np.float64)
    y = np.zeros(n)
    y[123_456] = 100.0
    y[400_000] = -50.0
    indices = downsample.downsample_indices(x, y, 1000)
    sampled = y[indices]
    assert sampled.max() == 100.0
    assert sampled.min() == -50.0


def test_numpy_fallback_spikes():
    n = 100_000
    y = np.zeros(n)
    y[55_555] = 42.0
    indices = downsample._minmax_indices_numpy(y, 500)
    assert 42.0 in y[indices]
    assert indices[0] == 0 and indices[-1] == n - 1
    assert np.all(np.diff(indices) > 0)


def test_numpy_fallback_with_nans():
    y = np.sin(np.linspace(0, 100, 50_000))
    y[1000:2000] = np.nan
    indices = downsample._minmax_indices_numpy(y, 400)
    assert len(indices) <= 500
    sampled = y[indices]
    finite = sampled[~np.isnan(sampled)]
    assert finite.max() <= 1.0 and finite.min() >= -1.0


def test_viewport_downsampler_caches():
    ds = downsample.ViewportDownsampler(target_points=1000)
    x = np.linspace(0, 100, 1_000_000)
    y = np.sin(x)
    xs1, ys1 = ds.get("key", x, y, 10.0, 20.0)
    xs2, ys2 = ds.get("key", x, y, 10.5, 20.5)  # small pan: stays cached
    assert xs1 is xs2
    xs3, _ = ds.get("key", x, y, 0.0, 100.0)  # big zoom out: recompute
    assert xs3 is not xs1
    assert xs3[0] <= 1e-6 and xs3[-1] >= 100.0 - 1e-6


def test_viewport_downsampler_restricts_to_view():
    ds = downsample.ViewportDownsampler(target_points=500)
    x = np.linspace(0, 100, 200_000)
    y = np.cos(x)
    xs, ys = ds.get("k", x, y, 40.0, 42.0)
    # padded by one viewport width each side
    assert xs[0] >= 38.0 - 1e-6 and xs[-1] <= 44.0 + 1e-6
    assert len(xs) <= 600


def test_invalidate_prefix():
    ds = downsample.ViewportDownsampler(target_points=100)
    x = np.linspace(0, 1, 10_000)
    y = x.copy()
    ds.get((1, "a"), x, y, 0.0, 1.0)
    ds.get((2, "a"), x, y, 0.0, 1.0)
    ds.invalidate(key_prefix=1)
    assert (1, "a") not in ds._cache
    assert (2, "a") in ds._cache
