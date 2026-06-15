"""Viewport-aware downsampling for large signals.

The plotly dataviewer uses plotly-resampler, whose FigureResampler is tied to
plotly/Dash and cannot be reused here. Its actual aggregation core however is
the framework-agnostic 'tsdownsample' package (Rust MinMaxLTTB working on
plain numpy arrays) - that core IS reused here. When tsdownsample is not
available (e.g. on pyodide/web, where the Rust wheel does not exist), a
vectorized numpy min/max binning fallback is used.

Strategy (same dynamic-aggregation idea as plotly-resampler): every plot only
draws the points inside its visible x-range, downsampled to a few thousand
points. The visible slice is padded by one viewport width on each side so
panning stays smooth, and results are cached per (plot, signal) until the
view leaves the padded window or the target point count changes.
"""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np

try:
    from tsdownsample import MinMaxLTTBDownsampler, NaNMinMaxDownsampler

    HAS_TSDOWNSAMPLE = True
except ImportError:  # pragma: no cover - exercised on pyodide builds
    HAS_TSDOWNSAMPLE = False

DEFAULT_TARGET_POINTS = 4000


def downsample_indices(x: np.ndarray, y: np.ndarray, n_out: int) -> np.ndarray:
    """Return indices of a representative subset of (x, y), at most ~n_out."""
    n = len(y)
    if n <= n_out or n < 4:
        return np.arange(n)

    # MinMaxLTTB requires an even n_out; keep a sane lower bound.
    n_out = max(n_out - (n_out % 2), 4)

    if HAS_TSDOWNSAMPLE:
        try:
            if np.isnan(y).any():
                indices = NaNMinMaxDownsampler().downsample(x, y, n_out=n_out)
            else:
                indices = MinMaxLTTBDownsampler().downsample(x, y, n_out=n_out)
            return np.asarray(indices)
        except Exception:
            pass  # fall through to the numpy implementation

    return _minmax_indices_numpy(y, n_out)


def _minmax_indices_numpy(y: np.ndarray, n_out: int) -> np.ndarray:
    """Vectorized per-bin min/max selection (preserves spikes), pure numpy."""
    n = len(y)
    n_bins = max(n_out // 2, 2)
    bin_size = int(np.ceil(n / n_bins))
    padded_len = n_bins * bin_size

    y64 = y.astype(np.float64, copy=False)
    pad = np.full(padded_len - n, np.nan)

    y_min = np.concatenate([y64, pad]).reshape(n_bins, bin_size)
    y_max = y_min.copy()
    # NaNs (real gaps and padding) must never win the argmin/argmax.
    y_min[np.isnan(y_min)] = np.inf
    y_max[np.isnan(y_max)] = -np.inf

    offsets = np.arange(n_bins) * bin_size
    min_idx = np.argmin(y_min, axis=1) + offsets
    max_idx = np.argmax(y_max, axis=1) + offsets

    indices = np.unique(np.concatenate([[0], min_idx, max_idx, [n - 1]]))
    return np.clip(indices, 0, n - 1)


@dataclass
class _CacheEntry:
    slice_start: int
    slice_stop: int
    n_out: int
    xs: np.ndarray
    ys: np.ndarray
    view_min: float
    view_max: float


class ViewportDownsampler:
    """Caches one downsampled view per series key (e.g. (plot_id, run, signal))."""

    def __init__(self, target_points: int = DEFAULT_TARGET_POINTS):
        self.target_points = target_points
        self._cache: dict[object, _CacheEntry] = {}

    def get(
        self,
        key: object,
        x: np.ndarray,
        y: np.ndarray,
        view_min: float,
        view_max: float,
        n_out: int | None = None,
    ) -> tuple[np.ndarray, np.ndarray]:
        """Points to draw for the visible range [view_min, view_max]."""
        n_out = n_out or self.target_points
        if view_max <= view_min:
            view_min, view_max = float(x[0]), float(x[-1])

        cached = self._cache.get(key)
        if cached is not None and cached.n_out == n_out:
            pad = (cached.view_max - cached.view_min) * 0.5
            inside_pad = (
                view_min >= cached.view_min - pad and view_max <= cached.view_max + pad
            )
            same_zoom = (view_max - view_min) <= 2.0 * (
                cached.view_max - cached.view_min
            ) + 1e-300
            if inside_pad and same_zoom:
                return cached.xs, cached.ys

        # Pad by one viewport width on each side so panning does not retrigger.
        width = view_max - view_min
        slice_start = int(np.searchsorted(x, view_min - width, side="left"))
        slice_stop = int(np.searchsorted(x, view_max + width, side="right"))
        slice_start = max(slice_start, 0)
        slice_stop = min(max(slice_stop, slice_start + 1), len(x))

        x_slice = x[slice_start:slice_stop]
        y_slice = y[slice_start:slice_stop]
        indices = downsample_indices(x_slice, y_slice, n_out)

        entry = _CacheEntry(
            slice_start=slice_start,
            slice_stop=slice_stop,
            n_out=n_out,
            xs=np.ascontiguousarray(x_slice[indices]),
            ys=np.ascontiguousarray(y_slice[indices]),
            view_min=view_min,
            view_max=view_max,
        )
        self._cache[key] = entry
        return entry.xs, entry.ys

    def invalidate(self, key_prefix: object = None) -> None:
        """Drop cached views; with a prefix, only keys that are tuples starting with it."""
        if key_prefix is None:
            self._cache.clear()
            return
        stale = [
            k
            for k in self._cache
            if isinstance(k, tuple) and len(k) > 0 and k[0] == key_prefix
        ]
        for k in stale:
            del self._cache[k]
