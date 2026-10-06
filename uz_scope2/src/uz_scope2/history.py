"""Bounded-RAM sample history built from incremental min/max envelopes.

The raw ring keeps the configured full-resolution tail.  This module keeps a
coarsening min/max pyramid under a fixed byte cap so active signals can still
be inspected at wide time scales without an unbounded raw stream or disk-backed
history.  Absolute int64 sample indices are converted to seconds only at query
time.
"""

from __future__ import annotations

import threading

import numpy as np

from .config import HistorySettings

# A new coarser level is appended once the top level exceeds this, keeping the
# full-session query O(output)-ish at any zoom.
TOP_LEVEL_MAX_BUCKETS = 4096
LEVEL_FACTOR = 8


def _auto_base(channels: int, sample_rate: float, max_ram_bytes: int) -> int:
    """Finest bucket size so one hour of pyramid fits well under the cap.

    Memory is ~``2 * 4 B * channels / base`` per sample plus the ~8/7 level
    overhead; solve for base against cap/hour, floor 64, rounded to a power
    of two so bucket edges stay divisible across coarsen steps.
    """
    per_hour = 2 * 4 * channels * sample_rate * 3600.0 * (8.0 / 7.0)
    base = 64
    while base < 1 << 20 and per_hour / base > max_ram_bytes:
        base *= 2
    return base


class _Level:
    """One pyramid level: growable ``(C, cap)`` min/max value arrays.

    ``count`` buckets are in use; the last one may be *partial* (covers fewer
    than ``bucket`` samples) and is updated in place as samples arrive —
    running min/max needs no raw carry buffer and keeps every bucket aligned
    to ``i * bucket`` absolute indices, which :meth:`LivePyramid.coarsen`
    relies on.
    """

    __slots__ = ("bucket", "vmin", "vmax", "count")

    def __init__(self, channels: int, bucket: int, cap: int = 256) -> None:
        self.bucket = bucket
        self.vmin = np.empty((channels, cap), dtype=np.float32)
        self.vmax = np.empty((channels, cap), dtype=np.float32)
        self.count = 0

    def ensure(self, buckets: int) -> None:
        cap = self.vmin.shape[1]
        if buckets <= cap:
            return
        new_cap = max(cap * 2, buckets)
        for name in ("vmin", "vmax"):
            old = getattr(self, name)
            grown = np.empty((old.shape[0], new_cap), dtype=np.float32)
            grown[:, : self.count] = old[:, : self.count]
            setattr(self, name, grown)

    def shrink_to(self, count: int) -> None:
        """Reallocate to ~``count`` buckets (frees memory after coarsen)."""
        cap = max(256, count)
        self.vmin = np.ascontiguousarray(self.vmin[:, :cap])
        self.vmax = np.ascontiguousarray(self.vmax[:, :cap])

    @property
    def nbytes(self) -> int:
        return self.vmin.nbytes + self.vmax.nbytes


def _grouped_extreme(values: np.ndarray, ratio: int, largest: bool) -> np.ndarray:
    """Reduce ``values`` (1-D or ``(C, n)``) by ``ratio``, padding the tail."""
    n = values.shape[-1]
    ng = -(-n // ratio)
    pad = ng * ratio - n
    if pad:
        fill = -np.inf if largest else np.inf
        pad_shape = values.shape[:-1] + (pad,)
        values = np.concatenate(
            [values, np.full(pad_shape, fill, dtype=values.dtype)], axis=-1
        )
    values = values.reshape(values.shape[:-1] + (ng, ratio))
    return values.max(axis=-1) if largest else values.min(axis=-1)


class LivePyramid:
    """Incremental multi-channel min/max envelope over the whole session.

    ``append`` runs on the reader thread (vectorized over all channels, no
    per-block allocations beyond tiny cascade scratch); ``query`` on the UI
    thread.  A short lock covers both — appends are ~66 Hz and queries are
    at most ``refresh_hz`` per visible cell, so contention is negligible.
    """

    def __init__(
        self,
        channels: int,
        base: int = 64,
        factor: int = LEVEL_FACTOR,
        max_bytes: int = 256 * 1024 * 1024,
    ) -> None:
        if channels < 1 or base < 1 or factor < 2:
            raise ValueError("channels >= 1, base >= 1, factor >= 2 required")
        self.channels = channels
        self.factor = factor
        self.max_bytes = max_bytes
        self.total = 0  # samples appended
        self.coarsen_events = 0  # UI polls this to report auto-coarsening
        self.levels: list[_Level] = [_Level(channels, base)]
        self._lock = threading.Lock()

    @property
    def base(self) -> int:
        return self.levels[0].bucket

    @property
    def nbytes(self) -> int:
        return sum(lvl.nbytes for lvl in self.levels)

    # --- append (reader thread) ------------------------------------------

    def append(self, block: np.ndarray) -> None:
        """Append a channel-major ``(channels, m)`` float32 block."""
        c, m = block.shape
        if c != self.channels:
            raise ValueError(f"expected {self.channels} channels, got {c}")
        if m == 0:
            return
        with self._lock:
            lvl = self.levels[0]
            b = lvl.bucket
            dirty0 = self.total // b  # first level-0 bucket touched
            new_total = self.total + m
            lvl.ensure(-(-new_total // b))

            i = 0
            bi = dirty0
            pos = self.total % b
            if pos:  # top up the existing partial bucket (running min/max)
                take = min(b - pos, m)
                seg = block[:, :take]
                np.minimum(lvl.vmin[:, bi], seg.min(axis=1), out=lvl.vmin[:, bi])
                np.maximum(lvl.vmax[:, bi], seg.max(axis=1), out=lvl.vmax[:, bi])
                i = take
                if pos + take == b:
                    bi += 1
            nfull = (m - i) // b
            if nfull:
                seg = block[:, i : i + nfull * b].reshape(c, nfull, b)
                lvl.vmin[:, bi : bi + nfull] = seg.min(axis=2)
                lvl.vmax[:, bi : bi + nfull] = seg.max(axis=2)
                bi += nfull
                i += nfull * b
            if i < m:  # start a new partial bucket
                seg = block[:, i:]
                lvl.vmin[:, bi] = seg.min(axis=1)
                lvl.vmax[:, bi] = seg.max(axis=1)
                bi += 1
            lvl.count = max(lvl.count, bi)
            self.total = new_total

            self._cascade(0, dirty0)
            self._maybe_add_level()
            while self.nbytes > self.max_bytes and self._coarsen_locked():
                self.coarsen_events += 1

    def _cascade(self, level: int, dirty_child: int) -> None:
        """Recompute parent buckets covering children >= ``dirty_child``."""
        for k in range(level, len(self.levels) - 1):
            child = self.levels[k]
            parent = self.levels[k + 1]
            ratio = parent.bucket // child.bucket
            j0 = dirty_child // ratio
            j1 = -(-child.count // ratio)
            parent.ensure(j1)
            c0 = j0 * ratio
            parent.vmin[:, j0:j1] = _grouped_extreme(
                child.vmin[:, c0 : child.count], ratio, largest=False
            )
            parent.vmax[:, j0:j1] = _grouped_extreme(
                child.vmax[:, c0 : child.count], ratio, largest=True
            )
            parent.count = j1
            dirty_child = j0

    def _maybe_add_level(self) -> None:
        while self.levels[-1].count > TOP_LEVEL_MAX_BUCKETS:
            top = self.levels[-1]
            self.levels.append(
                _Level(self.channels, top.bucket * self.factor)
            )
            self._cascade(len(self.levels) - 2, 0)

    # --- coarsen (memory cap) ---------------------------------------------

    def coarsen(self) -> bool:
        with self._lock:
            return self._coarsen_locked()

    def _coarsen_locked(self) -> bool:
        """Halve the finest level's resolution (fold buckets pairwise).

        Alignment survives because buckets are index-aligned and the last
        (possibly partial) bucket keeps accumulating via running min/max.
        When level 0 reaches level 1's bucket size it is simply dropped.
        Returns False when nothing can be coarsened further.
        """
        lvl = self.levels[0]
        if len(self.levels) > 1 and lvl.bucket * 2 >= self.levels[1].bucket:
            self.levels.pop(0)
            return True
        if lvl.count < 2:
            return False
        half = -(-lvl.count // 2)
        lvl.vmin[:, :half] = _grouped_extreme(
            lvl.vmin[:, : lvl.count], 2, largest=False
        )
        lvl.vmax[:, :half] = _grouped_extreme(
            lvl.vmax[:, : lvl.count], 2, largest=True
        )
        lvl.bucket *= 2
        lvl.count = half
        lvl.shrink_to(half)
        return True

    # --- query (UI thread) -------------------------------------------------

    def query(
        self, channel: int, start: int, stop: int, n_out: int, dt: float
    ) -> tuple[np.ndarray, np.ndarray]:
        """Min/max envelope of ``[start, stop)`` (local sample indices).

        Returns ``(x, y)`` with two points per output bucket (min and max at
        the bucket-center time), ~``n_out`` points total.  ``x`` is float64
        seconds, ``y`` float32.
        """
        target = max(int(n_out) // 2, 1)
        with self._lock:
            start = max(0, min(int(start), self.total))
            stop = max(start, min(int(stop), self.total))
            if stop == start:
                return np.empty(0, np.float64), np.empty(0, np.float32)
            level = self.levels[0]
            for lvl in self.levels:  # coarsest level still >= target buckets
                if (stop - start) / lvl.bucket >= target:
                    level = lvl
                else:
                    break
            b = level.bucket
            b0 = min(start // b, max(level.count - 1, 0))
            b1 = min(-(-stop // b), level.count)
            b1 = max(b1, b0 + 1)
            vmin = level.vmin[channel, b0:b1].copy()
            vmax = level.vmax[channel, b0:b1].copy()
        k = b1 - b0
        centers = (b0 + np.arange(k, dtype=np.float64) + 0.5) * b * dt
        if k > target:
            ratio = -(-k // target)
            vmin = _grouped_extreme(vmin, ratio, largest=False)
            vmax = _grouped_extreme(vmax, ratio, largest=True)
            # group center = mean of member centers (pad-safe: use edges)
            ng = vmin.shape[0]
            g0 = np.arange(ng, dtype=np.float64) * ratio
            g1 = np.minimum(g0 + ratio, k)
            centers = (b0 + (g0 + g1) / 2.0) * b * dt
        xs = np.repeat(centers, 2)
        ys = np.empty(2 * vmin.shape[0], dtype=np.float32)
        ys[0::2] = vmin
        ys[1::2] = vmax
        return xs, ys


class SessionHistory:
    """Facade the plot queries: stitches ring (full-res tail) and pyramid.

    ``on_block`` runs on the reader thread; ``query`` on the UI thread.
    Absolute sample indices everywhere — ``first_index`` anchors the pyramid
    to the ring's ``total_written`` clock (history can start/clear
    mid-session).
    """

    def __init__(
        self,
        settings: HistorySettings,
        channels: int,
        sample_rate: float,
    ) -> None:
        self.settings = settings
        self.channels = channels
        self.mode = settings.mode
        self.valid_from = [0] * channels  # per-slot epoch (channel reassignment)
        self.first_index: int | None = None
        self.pyramid: LivePyramid | None = None
        self.spill = None  # DiskSpill, disk mode (Phase 3)
        if self.mode != "off":
            base = max(settings.base, _auto_base(channels, sample_rate,
                                                 settings.max_ram_bytes))
            self.pyramid = LivePyramid(
                channels, base=base, max_bytes=settings.max_ram_bytes
            )

    # --- reader thread ----------------------------------------------------

    def on_block(self, block: np.ndarray, start_index: int) -> None:
        pyramid = self.pyramid
        if pyramid is None:
            return
        if self.first_index is None:
            self.first_index = start_index
        pyramid.append(block)
        spill = self.spill
        if spill is not None:
            spill.submit(block, start_index)

    # --- UI thread ----------------------------------------------------------

    def note_epoch(self, slot: int, start_index: int) -> None:
        if 0 <= slot < self.channels:
            self.valid_from[slot] = start_index

    @property
    def total_end(self) -> int:
        """Absolute index one past the newest sample in the pyramid."""
        if self.pyramid is None or self.first_index is None:
            return 0
        return self.first_index + self.pyramid.total

    def poll_notes(self) -> list[str]:
        """Drain UI-facing notices (auto-coarsen events) — call per frame."""
        notes: list[str] = []
        pyramid = self.pyramid
        if pyramid is not None and pyramid.coarsen_events:
            pyramid.coarsen_events = 0
            notes.append(
                f"history envelope coarsened to {pyramid.base} samples/bucket "
                f"to stay under {self.settings.max_ram_bytes // 2**20} MiB "
                "(history_limit to raise)"
            )
        return notes

    def query(
        self,
        ring,
        channel: int,
        start: int,
        stop: int,
        n_out: int,
        dt: float,
    ) -> tuple[np.ndarray, np.ndarray]:
        """Envelope/samples for absolute ``[start, stop)`` on one channel.

        The ring serves the resident tail at full resolution; the pyramid
        serves the evicted head.  Both are clamped to the slot's epoch.
        """
        from uz_dataviewer.downsample import decimate_range

        start = max(int(start), self.valid_from[channel], 0)
        stop = min(int(stop), ring.total_written)
        if stop <= start:
            return np.empty(0, np.float64), np.empty(0, np.float64)
        ring_oldest = ring.total_written - ring.filled
        boundary = min(max(start, ring_oldest), stop)

        span = stop - start
        parts_x: list[np.ndarray] = []
        parts_y: list[np.ndarray] = []
        pyramid = self.pyramid
        if boundary > start and pyramid is not None and self.first_index is not None:
            n_head = max(4, int(n_out * (boundary - start) / span))
            hx, hy = pyramid.query(
                channel,
                start - self.first_index,
                boundary - self.first_index,
                n_head,
                dt,
            )
            parts_x.append(hx + self.first_index * dt)
            parts_y.append(hy.astype(np.float64))
        if stop > boundary:
            data, s0 = ring.snapshot_range(boundary, stop - boundary, [channel])
            y = data[0]
            n = y.shape[0]
            if n:
                t = (s0 + np.arange(n, dtype=np.float64)) * dt
                n_tail = max(4, int(n_out * (stop - boundary) / span))
                tx, ty = decimate_range(t, y, None, n_tail, 0, n)
                parts_x.append(np.asarray(tx, dtype=np.float64))
                parts_y.append(np.asarray(ty, dtype=np.float64))
        if not parts_x:
            return np.empty(0, np.float64), np.empty(0, np.float64)
        return np.concatenate(parts_x), np.concatenate(parts_y)

    def clear(self) -> None:
        """Forget the session (pyramid restarts at the next block)."""
        if self.pyramid is not None:
            self.pyramid = LivePyramid(
                self.channels,
                base=self.pyramid.base,
                max_bytes=self.settings.max_ram_bytes,
            )
        self.first_index = None

    def close(self, keep: bool = False) -> None:
        spill, self.spill = self.spill, None
        if spill is not None:
            spill.close(keep=keep)
