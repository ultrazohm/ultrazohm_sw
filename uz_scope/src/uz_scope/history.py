"""Session-long sample history: incremental min/max pyramid (+ disk spill).

The ring (:class:`~uz_scope.ring.ChannelRing`) keeps the last ``ring_seconds``
at full resolution; everything older is served by this module so the plot can
pan/zoom over the whole session ("cont" timebase).

Two backends, selected by ``config.history.mode``:

- ``ram`` — a :class:`LivePyramid`: per-channel min/max envelope buckets,
  appended incrementally on the reader thread.  Zooming past the ring shows
  the envelope (never individual samples), but memory stays tiny
  (~``9 * channels * rate / base`` bytes/s, auto-coarsened under a byte cap).
- ``disk`` — additionally spills the raw float32 stream to one flat file per
  channel, so full detail can be read back for any old region (Phase 3).

Unlike ``uz_dataviewer.downsample.Pyramid`` (which stores *sample indices*
and requires the raw array to stay resident), the levels here store bucket
min/max **values**, so they survive ring eviction and support append.

All positions are absolute int64 sample indices (the ring's
``total_written`` clock); time appears only at the query edge (``* dt``).
"""

from __future__ import annotations

import json
import queue
import shutil
import threading
import time as _time
from dataclasses import dataclass
from pathlib import Path

import numpy as np

from .config import HistorySettings

# A new coarser level is appended once the top level exceeds this, keeping the
# full-session query O(output)-ish at any zoom.
TOP_LEVEL_MAX_BUCKETS = 4096
LEVEL_FACTOR = 8

# Disk mode: full-detail read-back is only requested for visible spans up to
# this many samples (beyond that the envelope is visually identical and a raw
# scan would touch tens of MB per channel per pan step).
DETAIL_MAX_SAMPLES = 4_000_000
# Spill rows buffered per flush (~256 KiB per channel at float32).
SPILL_FLUSH_ROWS = 65_536


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
        self, channel: int, start: int, stop: int, n_out: int, dt: float,
        min_index: int = 0,
    ) -> tuple[np.ndarray, np.ndarray]:
        """Min/max envelope of ``[start, stop)`` (local sample indices).

        Returns ``(x, y)`` with two points per output bucket (min and max at
        the bucket-center time), ~``n_out`` points total.  ``x`` is float64
        seconds, ``y`` float32.  ``min_index`` excludes buckets that begin
        before it — the epoch clamp: a bucket straddling a channel
        reassignment would otherwise show the previous observable's min/max.
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
            b0 = start // b
            if min_index > 0:
                b0 = max(b0, -(-min_index // b))
            b0 = min(b0, max(level.count - 1, 0))
            b1 = min(-(-stop // b), level.count)
            if b1 <= b0:
                return np.empty(0, np.float64), np.empty(0, np.float32)
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


class DiskSpill:
    """Raw float32 spill of the whole session, one flat file per channel.

    One file per channel keeps read-back contiguous (a sample-major file
    would stride ``4*C`` bytes per value).  Writes run on this object's own
    thread behind a bounded queue — a slow disk drops whole chunks (counted)
    instead of stalling ingest; dropped ranges are backfilled with NaN so the
    file offset always maps 1:1 to the absolute sample index.
    """

    def __init__(
        self,
        directory: str | Path,
        channels: int,
        timestep_s: float,
        *,
        queue_chunks: int = 256,
        autostart: bool = True,
    ) -> None:
        stamp = _time.strftime("%Y-%m-%d_%H-%M-%S")
        self.directory = Path(directory) / f"session_{stamp}"
        suffix = 1
        while self.directory.exists():
            self.directory = Path(directory) / f"session_{stamp}_{suffix}"
            suffix += 1
        self.directory.mkdir(parents=True)
        self.channels = channels
        self.timestep_s = timestep_s
        self.paths = [
            self.directory / f"ch{ch:02d}.f32" for ch in range(channels)
        ]
        self.first_index: int | None = None
        self.flushed_rows = 0  # samples on disk (identical for every channel)
        self.chunks_dropped = 0
        self.samples_dropped = 0
        self.error: str | None = None  # first write failure (worker keeps draining)
        self.epochs: list[tuple[int, int]] = []  # (slot, start_index)
        self._files = [open(p, "wb") for p in self.paths]
        self._pending: list[np.ndarray] = []  # (C, m) blocks awaiting flush
        self._pending_rows = 0
        self._expected_next: int | None = None
        self._queue: queue.Queue = queue.Queue(maxsize=queue_chunks)
        self._closed = False
        self._inline = False
        self._thread = threading.Thread(
            target=self._run, name="uz_scope-history", daemon=True
        )
        if autostart:
            self._thread.start()

    # producer (reader thread)
    def submit(self, block: np.ndarray, start_index: int) -> None:
        if self._closed:
            return
        try:
            self._queue.put_nowait((block, start_index))
        except queue.Full:
            self.chunks_dropped += 1
            self.samples_dropped += int(block.shape[1])

    # writer thread
    def _run(self) -> None:
        last_flush = _time.monotonic()
        while True:
            if self._inline:
                try:
                    item = self._queue.get_nowait()
                except queue.Empty:
                    return
            else:
                try:
                    item = self._queue.get(timeout=0.5)
                except queue.Empty:
                    item = ()  # idle tick
            if item is None:
                return
            if self.error is not None:
                continue  # disk already failed: drain only, never stall close()
            try:
                if item:
                    self._ingest(*item)
                # Flush on size OR age: during continuous streaming the queue
                # never runs empty, so without the age trigger evicted-but-
                # unflushed data would stay unreadable for minutes.
                now = _time.monotonic()
                if self._pending_rows >= SPILL_FLUSH_ROWS or (
                    self._pending_rows and now - last_flush >= 0.5
                ):
                    self._flush()
                    last_flush = now
            except Exception as exc:  # surfaced via error / poll_notes
                self.error = f"{type(exc).__name__}: {exc}"
                self._pending = []
                self._pending_rows = 0

    def _ingest(self, block: np.ndarray, start_index: int) -> None:
        if self.first_index is None:
            self.first_index = start_index
            self._expected_next = start_index
        if start_index > self._expected_next:
            # Dropped chunk: NaN filler keeps offset == sample index.
            gap = start_index - self._expected_next
            self._pending.append(
                np.full((self.channels, gap), np.nan, dtype=np.float32)
            )
            self._pending_rows += gap
        elif start_index < self._expected_next:
            # Out-of-order block (shouldn't happen) — skip the overlap.
            skip = self._expected_next - start_index
            if skip >= block.shape[1]:
                return
            block = block[:, skip:]
            start_index += skip
        self._pending.append(block)
        self._pending_rows += block.shape[1]
        self._expected_next = start_index + block.shape[1]

    def _flush(self) -> None:
        if not self._pending:
            return
        big = (
            self._pending[0]
            if len(self._pending) == 1
            else np.concatenate(self._pending, axis=1)
        )
        for ch, f in enumerate(self._files):
            f.write(np.ascontiguousarray(big[ch]))
        for f in self._files:
            f.flush()
        self._pending = []
        rows = self._pending_rows
        self._pending_rows = 0
        self.flushed_rows += rows  # publish after the data is readable

    # reads (HistoryReader worker only — separate handles, flushed data only)
    def read(self, channel: int, start: int, stop: int) -> tuple[np.ndarray, int]:
        first = self.first_index if self.first_index is not None else 0
        lo = max(int(start), first)
        hi = min(int(stop), first + self.flushed_rows)
        if hi <= lo or not 0 <= channel < self.channels:
            return np.empty(0, np.float32), lo
        with open(self.paths[channel], "rb") as f:
            f.seek(4 * (lo - first))
            buf = f.read(4 * (hi - lo))
        return np.frombuffer(buf, dtype="<f4").copy(), lo

    def note_epoch(self, slot: int, start_index: int) -> None:
        self.epochs.append((slot, start_index))

    def drain_inline(self) -> None:
        """Test hook: process the queue synchronously and flush."""
        self._inline = True
        self._run()
        if self.error is None:
            self._flush()

    def close(self, keep: bool = False) -> None:
        """Stop, flush and clean up.  Never raises — a failing disk must not
        abort the caller (shutdown saves settings after this)."""
        if self._closed:
            return
        self._closed = True
        if self._thread.is_alive():
            self._queue.put(None)
            self._thread.join()
        try:
            if self.error is None:
                self._flush()
        except Exception as exc:
            self.error = f"{type(exc).__name__}: {exc}"
        for f in self._files:
            try:
                f.close()
            except OSError:
                pass
        try:
            if keep:
                sidecar = {
                    "format": "uz_scope-history-v1",
                    "channels": self.channels,
                    "dtype": "<f4",
                    "timestep_s": self.timestep_s,
                    "first_index": self.first_index or 0,
                    "rows": self.flushed_rows,
                    "chunks_dropped": self.chunks_dropped,
                    "samples_dropped": self.samples_dropped,
                    "error": self.error,
                    "epochs": [list(e) for e in self.epochs],
                    "files": [p.name for p in self.paths],
                }
                (self.directory / "session.json").write_text(
                    json.dumps(sidecar, indent=2) + "\n", encoding="utf-8"
                )
            else:
                shutil.rmtree(self.directory, ignore_errors=True)
        except OSError as exc:
            self.error = self.error or f"{type(exc).__name__}: {exc}"


@dataclass
class HistoryDetail:
    """A completed full-detail read: decimated raw data for [start, stop)."""

    start: int
    stop: int
    xs: np.ndarray
    ys: np.ndarray


class HistoryReader:
    """One worker serving full-detail reads; latest request per key wins.

    The UI never blocks: ``request`` stores the newest wanted range per key
    (a plot cell + slot), ``poll`` returns the last completed detail.  The
    plot shows the envelope until the detail swaps in (stale-while-
    revalidate).
    """

    def __init__(self, spill: DiskSpill) -> None:
        self.spill = spill
        self._cond = threading.Condition()
        self._requests: dict = {}
        self._results: dict = {}
        self._done: dict = {}
        self._stop = False
        self._thread = threading.Thread(
            target=self._run, name="uz_scope-history-read", daemon=True
        )
        self._thread.start()

    def request(
        self, key, channel: int, start: int, stop: int, n_out: int, dt: float
    ) -> None:
        params = (channel, int(start), int(stop), int(n_out), float(dt))
        with self._cond:
            if self._done.get(key) == params or self._requests.get(key) == params:
                return
            self._requests[key] = params
            self._cond.notify()

    def poll(self, key) -> HistoryDetail | None:
        with self._cond:
            return self._results.get(key)

    def _run(self) -> None:
        from uz_dataviewer.downsample import decimate_range

        while True:
            with self._cond:
                while not self._requests and not self._stop:
                    self._cond.wait()
                if self._stop:
                    return
                key, params = next(iter(self._requests.items()))
                del self._requests[key]
            channel, start, stop, n_out, dt = params
            detail = None
            failed = False
            try:
                y, lo = self.spill.read(channel, start, stop)
                n = y.shape[0]
                if n:
                    t = (lo + np.arange(n, dtype=np.float64)) * dt
                    xs, ys = decimate_range(t, y, None, n_out, 0, n)
                    detail = HistoryDetail(
                        lo, lo + n,
                        np.asarray(xs, dtype=np.float64),
                        np.asarray(ys, dtype=np.float64),
                    )
            except Exception:
                # E.g. the spill directory vanished under a clear()/close().
                # Never let a request kill the worker; mark it done so the
                # UI does not retry a poisoned read every refresh.
                failed = True
            with self._cond:
                if detail is not None:
                    self._results[key] = detail
                # A read clamped short by not-yet-flushed data must retry
                # once more rows land on disk, so only a fully-covered (or
                # failed) request is deduplicated.
                if failed or (detail is not None and detail.stop >= stop):
                    self._done[key] = params

    def close(self) -> None:
        with self._cond:
            self._stop = True
            self._cond.notify()
        self._thread.join(timeout=2.0)


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
        self.spill: DiskSpill | None = None
        self.reader: HistoryReader | None = None
        # Guards the (pyramid, spill, first_index) triple: on_block (reader
        # thread) vs clear()/close()/rebuild (UI thread).  RLock because
        # clear() calls close().  Held only for microseconds per block.
        self._swap_lock = threading.RLock()
        self._spill_error_shown = False
        if self.mode != "off":
            base = max(settings.base, _auto_base(channels, sample_rate,
                                                 settings.max_ram_bytes))
            self.pyramid = LivePyramid(
                channels, base=base, max_bytes=settings.max_ram_bytes
            )
        if self.mode == "disk":
            self.spill = DiskSpill(
                settings.directory, channels, 1.0 / sample_rate
            )
            self.reader = HistoryReader(self.spill)

    # --- reader thread ----------------------------------------------------

    def on_block(self, block: np.ndarray, start_index: int) -> None:
        with self._swap_lock:
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
            if self.spill is not None:
                self.spill.note_epoch(slot, start_index)

    @property
    def total_end(self) -> int:
        """Absolute index one past the newest sample in the pyramid."""
        if self.pyramid is None or self.first_index is None:
            return 0
        return self.first_index + self.pyramid.total

    def poll_notes(self) -> list[str]:
        """Drain UI-facing notices (coarsen/spill errors) — call per frame."""
        notes: list[str] = []
        pyramid = self.pyramid
        if pyramid is not None and pyramid.coarsen_events:
            pyramid.coarsen_events = 0
            notes.append(
                f"history envelope coarsened to {pyramid.base} samples/bucket "
                f"to stay under {self.settings.max_ram_bytes // 2**20} MiB "
                "(history_limit to raise)"
            )
        spill = self.spill
        if spill is not None and spill.error and not self._spill_error_shown:
            self._spill_error_shown = True
            notes.append(
                f"history disk spill failed and stopped: {spill.error} "
                "(envelope history continues; see Diagnostics)"
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
        key=None,
    ) -> tuple[np.ndarray, np.ndarray]:
        """Envelope/samples for absolute ``[start, stop)`` on one channel.

        The ring serves the resident tail at full resolution; the pyramid
        serves the evicted head.  Both are clamped to the slot's epoch.  In
        disk mode a ``key`` (stable per plot cell + slot) additionally
        requests a full-detail read of the head; the envelope is shown until
        the detail arrives (stale-while-revalidate).
        """
        from uz_dataviewer.downsample import decimate_range

        with self._swap_lock:  # consistent (pyramid, first_index) pair
            pyramid = self.pyramid
            first_index = self.first_index
        valid_from = self.valid_from[channel]
        start = max(int(start), valid_from, 0)
        stop = min(int(stop), ring.total_written)
        if stop <= start:
            return np.empty(0, np.float64), np.empty(0, np.float64)
        ring_oldest = ring.total_written - ring.filled
        boundary = min(max(start, ring_oldest), stop)

        span = stop - start
        parts_x: list[np.ndarray] = []
        parts_y: list[np.ndarray] = []
        if boundary > start and pyramid is not None and first_index is not None:
            n_head = max(4, int(n_out * (boundary - start) / span))
            head = self._head_detail(key, channel, start, boundary, n_head, dt)
            if head is None:
                hx, hy = pyramid.query(
                    channel,
                    start - first_index,
                    boundary - first_index,
                    n_head,
                    dt,
                    min_index=max(valid_from - first_index, 0),
                )
                hx = hx + first_index * dt
                # The last envelope bucket can straddle the ring boundary;
                # clamp its center so the stitched x stays monotonic.
                np.clip(hx, start * dt, boundary * dt, out=hx)
                head = (hx, hy.astype(np.float64))
            parts_x.append(head[0])
            parts_y.append(head[1])
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

    def _head_detail(
        self, key, channel: int, start: int, boundary: int, n_out: int, dt: float
    ) -> tuple[np.ndarray, np.ndarray] | None:
        """Disk mode: request/serve a full-detail read of the evicted head."""
        reader = self.reader
        if reader is None or key is None:
            return None
        span = boundary - start
        if span > DETAIL_MAX_SAMPLES:
            return None  # envelope is visually identical at this zoom
        reader.request((key, channel), channel, start, boundary, n_out, dt)
        detail = reader.poll((key, channel))
        if detail is None or detail.stop <= detail.start:
            return None
        overlap = min(detail.stop, boundary) - max(detail.start, start)
        if overlap < 0.9 * span:
            return None  # too stale after a big pan — keep the envelope
        xs, ys = detail.xs, detail.ys
        mask = (xs >= start * dt) & (xs <= boundary * dt)
        return xs[mask], ys[mask]

    def clear(self) -> None:
        """Forget the session (pyramid/spill restart at the next block)."""
        with self._swap_lock:
            if self.pyramid is not None:
                self.pyramid = LivePyramid(
                    self.channels,
                    base=self.pyramid.base,
                    max_bytes=self.settings.max_ram_bytes,
                )
            self.first_index = None
            if self.spill is not None:
                timestep_s = self.spill.timestep_s
                self.close(keep=self.settings.keep_files)
                self.spill = DiskSpill(
                    self.settings.directory, self.channels, timestep_s
                )
                self.reader = HistoryReader(self.spill)
                self._spill_error_shown = False

    def close(self, keep: bool = False) -> None:
        with self._swap_lock:
            reader, self.reader = self.reader, None
            spill, self.spill = self.spill, None
        # Join the workers outside opportunistic callers' hot path but not
        # under the swap lock contended by the reader thread.
        if reader is not None:
            reader.close()
        if spill is not None:
            spill.close(keep=keep)
