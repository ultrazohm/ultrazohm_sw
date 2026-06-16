"""Range-aware downsampling for large logs (pure NumPy -- identical on native and web).

:func:`decimate_range` is the single entry point; it dispatches between two layers,
both of which emit a ~``n_out``-point **min/max envelope at the signal's true sample
positions** (so spikes/ripple survive and it looks like the waveform):

* **One-shot envelope** (:func:`_envelope_oneshot`) -- scans the visible slice and
  takes each bucket's argmin/argmax, *O(visible points)*. Used for windows up to
  :data:`PYRAMID_MIN_POINTS`, where a full scan is only a couple of ms.

* :class:`Pyramid` -- a precomputed **multi-resolution min/max pyramid** built once
  per signal. Querying it for a larger window is *O(output points)*, independent of
  the total sample count, so a multi-hundred-MB signal pans at full frame rate.

(The legacy viewer used ``plotly_resampler``/``tsdownsample`` MinMax-LTTB; that Rust
dependency has been dropped in favour of the pyramid, which keeps the native and
Pyodide/WASM builds on exactly the same code path.)
"""

from __future__ import annotations

import numpy as np


def visible_slice(time: np.ndarray, x_min: float, x_max: float) -> tuple[int, int]:
    """Return ``(start, stop)`` indices covering ``[x_min, x_max]`` (inclusive-ish).

    One sample of padding is added on each side so lines reach the plot edges.
    ``time`` is assumed monotonically increasing.

    The search scalars are cast to ``time``'s dtype first: ``np.searchsorted`` on a
    float32 array with a Python (float64) scalar **up-casts the whole array** to
    float64 every call -- ~31 ms on the 7.5 M-bin FFT ``freqs`` array, i.e. the
    per-frame killer behind a sluggish spectrum (the same landmine as ``np.interp``
    for cursors). A matching-dtype scalar keeps it O(log n).
    """
    lo = time.dtype.type(x_min)
    hi = time.dtype.type(x_max)
    start = int(np.searchsorted(time, lo, side="left"))
    stop = int(np.searchsorted(time, hi, side="right"))
    start = max(0, start - 1)
    stop = min(time.shape[0], stop + 1)
    return start, stop


# -- range-aware min/max envelope decimation ----------------------------------
# Both decimators below emit ~``n_out`` points as a min/max envelope at the
# signals' *true sample positions* (so it looks like the waveform, not a blocky
# bucket-centre grid) and produce a consistent point count at every zoom.
#
# Signals larger than this get a :class:`Pyramid`; the per-frame query then reads
# only a coarse level (O(output)). At or below it, the one-shot envelope scans the
# visible slice directly (vectorised, a couple of ms at this size).
PYRAMID_MIN_POINTS = 1_000_000


def _argminmax_buckets(values: np.ndarray, n_buckets: int) -> tuple[np.ndarray, np.ndarray]:
    """Per-(near-equal-)bucket argmin/argmax over ``values`` (local indices)."""
    count = values.shape[0]
    bucket = max(1, -(-count // n_buckets))  # ceil division
    nb = -(-count // bucket)
    pad = nb * bucket - count
    block = np.concatenate([values, np.full(pad, values[-1], values.dtype)]) if pad else values
    block = block.reshape(nb, bucket)
    base = np.arange(nb, dtype=np.int64) * bucket
    imin = np.minimum(base + block.argmin(axis=1), count - 1)
    imax = np.minimum(base + block.argmax(axis=1), count - 1)
    return imin, imax


def _envelope(time: np.ndarray, y: np.ndarray, indices_min: np.ndarray, indices_max: np.ndarray
              ) -> tuple[np.ndarray, np.ndarray]:
    """Interleave per-bucket min/max sample indices into an in-order (x, y) line."""
    lo = np.minimum(indices_min, indices_max)
    hi = np.maximum(indices_min, indices_max)
    nb = lo.shape[0]
    out = np.empty(2 * nb, dtype=np.int64)
    out[0::2] = lo
    out[1::2] = hi
    return time[out], y[out]


def _envelope_oneshot(time, y, n_out, start, stop):
    """Vectorised min/max envelope of ``y[start:stop]`` at true sample positions."""
    imin, imax = _argminmax_buckets(y[start:stop], max(n_out // 2, 1))
    return _envelope(time, y, imin + start, imax + start)


class Pyramid:
    """Precomputed min/max levels of one signal, for O(output) decimation.

    Level ``k`` stores, for buckets of ``base * factor**k`` consecutive samples,
    the **sample indices** of the per-bucket min and max. A query picks the
    coarsest level that still has at least the budget of buckets in the window,
    then groups those down to the budget (keeping the true min/max index of each
    group) -- so the output is ~``n_out`` points at their real positions, the same
    at every zoom. Per-query cost depends only on the output size, not the signal
    length. Storing indices (not values) lets the envelope use true X/Y read from
    the run's ``time``/``y`` arrays, so the pyramid is also normalisation-agnostic.
    """

    __slots__ = ("levels", "n")

    def __init__(self, levels: list[tuple[int, np.ndarray, np.ndarray]], n: int) -> None:
        self.levels = levels  # [(bucket_size, imin, imax), ...] coarsening
        self.n = n

    @classmethod
    def build(cls, y: np.ndarray, base: int = 64, factor: int = 8, min_buckets: int = 512) -> "Pyramid":
        y = np.ascontiguousarray(y, dtype=np.float32)
        n = int(y.shape[0])
        dtype = np.int32 if n < 2_000_000_000 else np.int64
        imin, imax = _argminmax_buckets(y, -(-n // base))
        imin = imin.astype(dtype)
        imax = imax.astype(dtype)
        levels: list[tuple[int, np.ndarray, np.ndarray]] = [(base, imin, imax)]
        bucket = base
        # Coarser levels aggregate the previous level's indices (pick the child
        # whose value is smallest for min / largest for max), so the build is O(n).
        while imin.shape[0] > min_buckets:
            bucket *= factor
            imin = cls._group(y, imin, factor, np.argmin).astype(dtype)
            imax = cls._group(y, imax, factor, np.argmax).astype(dtype)
            levels.append((bucket, imin, imax))
        return cls(levels, n)

    @staticmethod
    def _group(y: np.ndarray, idx: np.ndarray, factor: int, pick) -> np.ndarray:
        """Reduce ``idx`` (sample indices) by ``factor``, keeping the extreme child."""
        pnb = idx.shape[0]
        ng = -(-pnb // factor)
        pad = ng * factor - pnb
        cand = np.concatenate([idx, np.full(pad, idx[-1], idx.dtype)]) if pad else idx
        cand = cand.reshape(ng, factor)
        sel = pick(y[cand], axis=1)
        return cand[np.arange(ng), sel]

    def query(self, time: np.ndarray, y: np.ndarray, n_out: int, start: int, stop: int
              ) -> tuple[np.ndarray, np.ndarray]:
        count = max(stop - start, 1)
        target = max(n_out // 2, 1)
        # Coarsest level that still has >= `target` buckets over the window.
        bucket, imin, imax = self.levels[0]
        for lvl in self.levels:
            if count / lvl[0] >= target:
                bucket, imin, imax = lvl
            else:
                break
        b0 = start // bucket
        b1 = min((stop + bucket - 1) // bucket, imin.shape[0])
        if b1 <= b0:
            b1 = min(b0 + 1, imin.shape[0])
        a, b = imin[b0:b1], imax[b0:b1]
        if a.shape[0] > target:  # group down to the budget, keeping true extremes
            a = self._group(y, a, -(-a.shape[0] // target), np.argmin)
            b = self._group(y, b, -(-b.shape[0] // target), np.argmax)
        return _envelope(time, y, a.astype(np.int64), b.astype(np.int64))


def decimate_range(
    time: np.ndarray,
    y: np.ndarray,
    pyramid: "Pyramid | None",
    n_out: int,
    start: int,
    stop: int,
) -> tuple[np.ndarray, np.ndarray]:
    """Decimate ``[start, stop)`` to ~``n_out`` points (caller supplies the slice).

    Returns the raw slice when it already fits, the precomputed :class:`Pyramid`'s
    envelope for huge windows (O(output)), else a one-shot vectorised envelope of
    the slice. All paths produce a consistent ~``n_out``-point min/max envelope at
    the signals' true sample positions.
    """
    n_out = max(int(n_out), 2)
    if stop - start <= n_out:
        return time[start:stop], y[start:stop]
    if pyramid is not None and (stop - start) > PYRAMID_MIN_POINTS:
        return pyramid.query(time, y, n_out, start, stop)
    return _envelope_oneshot(time, y, n_out, start, stop)
