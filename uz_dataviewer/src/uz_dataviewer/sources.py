"""Sample sources: raw access is separate from display-only summaries.

Parquet sources retain metadata only. Raw batches, summaries and display results
have independent lifetimes; requesting an array explicitly may use substantial RAM.
"""
from __future__ import annotations

from collections import OrderedDict
from dataclasses import dataclass
from pathlib import Path
from typing import Iterator, Protocol, Sequence
import hashlib
import json
import os
import tempfile
import uuid
import threading
import time
from zipfile import BadZipFile

import numpy as np


class Cancelled(Exception):
    pass


def check(cancel=None):
    if cancel is not None and cancel.is_set():
        raise Cancelled()


@dataclass(frozen=True)
class TimeShift:
    """Rebase before adding the target to preserve small normalized origins."""
    origin: float
    target: float


def shift_time(values, shift):
    if isinstance(shift, TimeShift):
        return (values - shift.origin) + shift.target
    return values + shift if shift else values


def displayed_bounds(source, lo, hi, offset=0., cancel=None, *, padding=False):
    """Select by displayed float64 timestamps, including rounded duplicates.

    Subtracting an offset from the window is not an inverse of floating-point
    addition. Binary search the displayed values so lazy and resident sources
    agree even when normalization collapses several raw timestamps together.
    """
    if not offset:
        return source.bounds(lo, hi, cancel, padding=padding)
    return source.bounds(lo, hi, cancel, padding=padding, offset=offset)


@dataclass(frozen=True)
class FileIdentity:
    path: Path
    signature: tuple

    @staticmethod
    def capture(path):
        path = Path(path).resolve()
        s = path.stat()
        return FileIdentity(path, (s.st_size, s.st_mtime_ns, s.st_ctime_ns, s.st_ino))

    def validate(self):
        try:
            current = FileIdentity.capture(self.path)
        except OSError as exc:
            raise ValueError(f'Source unavailable; reopen {self.path.name}') from exc
        if current != self:
            raise ValueError(f'Source changed; reopen {self.path.name}')


def validation_error(sources):
    """One validity contract for cached displays, analyses and node outputs."""
    try:
        for source in sources:
            source.validate()
    except (ValueError, OSError) as exc:
        return str(exc)
    return None


class ByteCache:
    """Thread-safe, shared LRU; oversized entries are returned but not retained."""
    def __init__(self, limit=1024 * 1024**2):
        self.limit = limit
        self.bytes = 0
        self.entries = OrderedDict()
        self.lock = threading.RLock()
        self.evictions = 0
        self.oversized = 0
        self.last_limit_hit = None

    def status(self):
        """Snapshot for the UI; highlight pressure for five seconds after a miss in capacity."""
        with self.lock:
            return dict(bytes=self.bytes, limit=self.limit, evictions=self.evictions,
                        oversized=self.oversized,
                        limit_hit=self.last_limit_hit is not None and time.monotonic() - self.last_limit_hit < 5)

    def get(self, key):
        with self.lock:
            item = self.entries.get(key)
            if item is not None:
                self.entries.move_to_end(key)
                return item[0]

    def put(self, key, value, size):
        with self.lock:
            old = self.entries.pop(key, None)
            if old:
                self.bytes -= old[1]
            if size <= self.limit:
                self.entries[key] = (value, size)
                self.bytes += size
            else:
                self.oversized += 1
                self.last_limit_hit = time.monotonic()
            self.trim()
        return value

    def trim(self):
        with self.lock:
            while self.bytes > self.limit and self.entries:
                _, (_, size) = self.entries.popitem(last=False)
                self.bytes -= size
                self.evictions += 1
                self.last_limit_hit = time.monotonic()

    def clear(self):
        with self.lock:
            self.entries.clear()
            self.bytes = 0
            self.evictions = 0
            self.oversized = 0
            self.last_limit_hit = None


@dataclass(frozen=True)
class Metadata:
    identity: str
    rows: int
    channels: tuple[str, ...]
    time_range: tuple[float, float]


@dataclass
class PlotData:
    time: np.ndarray
    values: np.ndarray
    raw_count: int


class SampleSource(Protocol):
    """Shared raw-data contract for recordings, derived outputs and analyses.

    Times are finite and non-decreasing. Row intervals are half-open; bounds
    include both time endpoints, with optional neighbouring display samples.
    Implementations validate source identity and honour cancellation on reads.
    """

    metadata: Metadata

    def validate(self) -> None: ...

    def bounds(self, lo: float, hi: float, cancel: threading.Event | None = None,
               *, padding: bool = True, offset: TimeShift | float = 0.) -> tuple[int, int]: ...

    def read_rows(self, channels: Sequence[str], start: int, stop: int,
                  cancel: threading.Event | None = None
                  ) -> tuple[np.ndarray, dict[str, np.ndarray]]: ...

    def iter_raw(self, channels: Sequence[str], start: int = 0, stop: int | None = None,
                 cancel: threading.Event | None = None
                 ) -> Iterator[tuple[np.ndarray, dict[str, np.ndarray]]]: ...


class DisplaySource(SampleSource, Protocol):
    """Display summaries are distinct from the raw-data analysis contract."""

    def read_plot(self, channel: str, lo: float, hi: float, budget: int,
                  cancel: threading.Event | None = None, *, padding: bool = True,
                  offset: TimeShift | float = 0.
                  ) -> PlotData: ...

    def prepare_summary(self, channel: str, cancel: threading.Event | None = None) -> None: ...


def envelope(t, y, indices, budget):
    """Ordered min/max plus a gap marker per bucket, using original samples.

    Budget targets finite extrema; gap markers can add up to half that count.
    """
    if len(y) <= budget:
        return np.ascontiguousarray(t, dtype=np.float64), np.ascontiguousarray(y, dtype=np.float64)
    groups = max(1, budget // 2)
    # Sample-space buckets keep summaries and raw refinement on the same axis.
    span = max(1, int(indices[-1]) - int(indices[0]) + 1)
    group = (indices - indices[0]) * groups // span
    starts = np.r_[0, np.flatnonzero(np.diff(group)) + 1]
    lengths = np.diff(np.r_[starts, len(y)])
    finite = np.isfinite(y)
    low = np.minimum.reduceat(np.where(finite, y, np.inf), starts)
    high = np.maximum.reduceat(np.where(finite, y, -np.inf), starts)
    pos = np.arange(len(y))
    mins = np.minimum.reduceat(np.where(finite & (y == np.repeat(low, lengths)), pos, len(y)), starts)
    # First minimum / last maximum retain both ends of constant buckets.
    maxs = np.maximum.reduceat(np.where(finite & (y == np.repeat(high, lengths)), pos, -1), starts)
    gaps = np.minimum.reduceat(np.where(~finite, pos, len(y)), starts)
    selected = np.unique(np.r_[mins, maxs, gaps])
    selected = selected[(selected >= 0) & (selected < len(y))]
    values = np.asarray(y[selected], dtype=np.float64).copy()
    values[~np.isfinite(values)] = np.nan
    return np.ascontiguousarray(t[selected], dtype=np.float64), values


class MemorySource:
    def __init__(self, time, channels):
        self.time = time
        self.channels = channels
        self.metadata = Metadata(f'memory:{uuid.uuid4().hex}', len(time), tuple(channels),
                                 (float(time[0]), float(time[-1])) if len(time) else (0., 0.))

    def read_rows(self, channels, start, stop, cancel=None):
        self.validate()
        check(cancel)
        return self.time[start:stop], {c: self.channels[c][start:stop] for c in channels}

    def iter_raw(self, channels, start=0, stop=None, cancel=None):
        stop = self.metadata.rows if stop is None else stop
        for i in range(start, stop, 65536):
            yield self.read_rows(channels, i, min(i + 65536, stop), cancel)

    def bounds(self, lo, hi, cancel=None, *, padding=True, offset=0.):
        self.validate()
        check(cancel)
        from .downsample import visible_slice
        return visible_slice(shift_time(self.time, offset), lo, hi, padding=padding)

    def validate(self):
        pass

# Each summary bucket keeps original extrema and a representative gap.
POINT = np.dtype([('i', '<i8'), ('t', '<f8'), ('y', '<f4')])
BASE = 1024
FACTOR = 8
CACHE_VERSION = 4


def summarize(points, bucket):
    if not len(points):
        return points
    group = points['i'] // bucket
    starts = np.r_[0, np.flatnonzero(np.diff(group)) + 1]
    lengths = np.diff(np.r_[starts, len(points)])
    y = points['y']
    finite = np.isfinite(y)
    low = np.minimum.reduceat(np.where(finite, y, np.inf), starts)
    high = np.maximum.reduceat(np.where(finite, y, -np.inf), starts)
    pos = np.arange(len(y))
    mins = np.minimum.reduceat(np.where(finite & (y == np.repeat(low, lengths)), pos, len(y)), starts)
    maxs = np.maximum.reduceat(np.where(finite & (y == np.repeat(high, lengths)), pos, -1), starts)
    gaps = np.minimum.reduceat(np.where(~finite, pos, len(y)), starts)
    select = np.unique(np.r_[mins, maxs, gaps])
    return points[select[(select >= 0) & (select < len(y))]]


def raw_summary(t, y, offset, finite=False):
    """Vectorised aligned blocks; avoid allocating one index per raw sample."""
    n = len(y)
    lead = min(n, (-offset) % BASE)
    end = lead + ((n - lead) // BASE) * BASE
    if not finite and not np.isfinite(y).all():
        # Preserve representative gaps and finite extrema, even mixed within a block.
        p = np.empty(n, dtype=POINT)
        p['i'], p['t'], p['y'] = np.arange(offset, offset + n), t, y
        return summarize(p, BASE)
    block = y[lead:end].reshape(-1, BASE)
    base = np.arange(len(block)) * BASE + lead
    indices = np.unique(np.r_[np.arange(lead), base + block.argmin(axis=1),
                              base + BASE - 1 - block[:, ::-1].argmax(axis=1), np.arange(end, n)])
    p = np.empty(len(indices), dtype=POINT)
    p['i'], p['t'], p['y'] = indices + offset, t[indices], y[indices]
    return summarize(p, BASE)


def atomic_npz(path, **arrays):
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, name = tempfile.mkstemp(dir=path.parent, suffix='.tmp')
    try:
        with os.fdopen(fd, 'wb') as f:
            np.savez(f, **arrays)
        os.replace(name, path)
    finally:
        if os.path.exists(name):
            os.unlink(name)


class SummarySource:
    """Mixin with bounded shared summary cache and optional durable summaries."""
    def prepare_summary(self, channel, cancel=None):
        """Warm the display cache without exposing its internal pyramid format."""
        self._summary(channel, cancel)

    def _summary(self, channel, cancel):
        self.validate()
        check(cancel)
        key = (self.metadata.identity, channel, 'summary')
        cached = self.cache.get(key)
        if cached is not None:
            return cached
        with self.summary_lock:
            check(cancel)
            cached = self.cache.get(key)
            if cached is not None:
                return cached
            path = self.summary_path(channel)
            levels = None
            if path is not None and path.exists():
                try:
                    with np.load(path, allow_pickle=False) as saved:
                        count = saved['count']
                        if count.ndim != 0 or count.dtype.kind not in "iu" or not 1 <= int(count) <= 64:
                            raise ValueError('Invalid summary count')
                        levels = [saved[f'l{i}'] for i in range(int(count))]
                    for level in levels:
                        if level.dtype != POINT or level.ndim != 1 or not len(level) or np.any(np.diff(level['i']) <= 0) or level['i'][0] < 0 or level['i'][-1] >= self.metadata.rows or not np.isfinite(level['t']).all():
                            raise ValueError('Invalid summary')
                except (ValueError, OSError, KeyError, EOFError, BadZipFile):
                    levels = None
            if levels is None:
                level = self._base_summary(channel, cancel)
                levels = [level]
                bucket = BASE
                while len(level) > 1024:
                    check(cancel)
                    bucket *= FACTOR
                    level = summarize(level, bucket)
                    levels.append(level)
                check(cancel)
                self.validate()
                if path is not None:
                    try:
                        atomic_npz(path, count=len(levels), **{f'l{i}': v for i, v in enumerate(levels)})
                    except OSError:
                        pass  # Read-only/full cache does not prevent viewing.
            return self.cache.put(key, levels, sum(v.nbytes for v in levels))

    def _base_summary(self, channel, cancel):
        chunks, offset = [], 0
        for t, ys in self.iter_raw([channel], cancel=cancel):
            check(cancel)
            chunks.append(raw_summary(t, ys[channel], offset))
            offset += len(t)
        return summarize(np.concatenate(chunks), BASE)

    def read_plot(self, channel, lo, hi, budget, cancel=None, *, padding=True, offset=0.):
        budget = max(2, int(budget))
        start, stop = displayed_bounds(self, lo, hi, offset, cancel, padding=padding)
        if stop <= start:
            return PlotData(np.empty(0), np.empty(0), 0)
        # A summary must have at least one bucket per requested extrema pair.
        # At close zoom even level zero (1,024 samples/bucket) is too coarse:
        # using it would leave sparse points in the interior while raw boundary
        # refinement densely fills the edges. Read the selected raw window instead.
        target_buckets = max(1, budget // 2)
        if stop - start < BASE * target_buckets or stop - start <= max(budget, BASE * 2):
            t, ys = self.read_rows([channel], start, stop, cancel)
            x, y = envelope(t, ys[channel], np.arange(start, stop), budget)
            return PlotData(x, y, stop - start)
        levels = self._summary(channel, cancel)
        level = 0
        while level + 1 < len(levels) and BASE * FACTOR**(level + 1) <= (stop - start) / target_buckets:
            level += 1

        def collect(a, b, k):
            check(cancel)
            if a >= b:
                return []
            if k < 0:
                t, ys = self.read_rows([channel], a, b, cancel)
                p = np.empty(len(t), dtype=POINT)
                p['i'], p['t'], p['y'] = np.arange(a, b), t, ys[channel]
                return [p]
            size = BASE * FACTOR**k
            left = min(b, ((a + size - 1) // size) * size)
            right = max(left, (b // size) * size)
            out = collect(a, left, k - 1)
            if right > left:
                p = levels[k]
                i, j = np.searchsorted(p['i'], [left, right])
                out.append(p[i:j])
            out.extend(collect(right, b, k - 1))
            return out

        points = np.concatenate(collect(start, stop, level))
        x, y = envelope(points['t'], points['y'], points['i'], budget)
        check(cancel)
        return PlotData(x, y, stop - start)


class ArraySource(SummarySource, MemorySource):
    def __init__(self, time, channels, cache=None):
        MemorySource.__init__(self, time, channels)
        self.cache = cache if cache is not None else ByteCache()
        self.summary_lock = threading.Lock()
        self.validator = None

    def _base_summary(self, channel, cancel):
        check(cancel)
        values = self.channels[channel]
        if not np.isfinite(values).all():
            return super()._base_summary(channel, cancel)
        result = raw_summary(self.time, values, 0, finite=True)
        check(cancel)
        return result

    def summary_path(self, channel):
        return None

    def validate(self):
        if self.validator is not None:
            self.validator()


class IndexedFileSource(SummarySource):
    """Backend-neutral file identity, timestamp index, raw windows and summaries."""
    def _initialize(self, path, cache, cache_dir, disk_cache, backend):
        self.path = Path(path).resolve()
        self.file_identity = FileIdentity.capture(self.path)
        self.signature = self.file_identity.signature
        self.origin = None
        self.disk_cache = disk_cache
        identity = hashlib.sha256(json.dumps([backend, str(self.path), self.signature, CACHE_VERSION]).encode()).hexdigest()
        root = Path(cache_dir or os.environ.get('UZ_DATAVIEWER_CACHE', Path.home() / '.cache' / 'uz_dataviewer'))
        self.directory = (root / 'polars' if backend == 'polars' else root) / identity
        self.cache = cache if cache is not None else ByteCache()
        self.summary_lock = threading.Lock()
        self.index_lock = threading.Lock()
        self._index_ready = False
        return identity

    def _restore_index(self):
        if not self.disk_cache:
            return False
        try:
            with np.load(self.directory / 'time.npz', allow_pickle=False) as data:
                first, last, offsets = data['first'], data['last'], data['offsets']
            if (first.ndim != 1 or last.ndim != 1 or offsets.ndim != 1
                    or not len(first) or len(first) != len(last) or len(offsets) != len(first) + 1
                    or offsets.dtype.kind not in 'iu' or offsets[0] != 0 or offsets[-1] != self._rows
                    or np.any(np.diff(offsets) <= 0) or not np.isfinite(first).all()
                    or not np.isfinite(last).all() or np.any(first > last) or np.any(first[1:] < last[:-1])):
                return False
            self.first, self.last, self.index_offsets = first, last, offsets
            self._index_ready = True
            return True
        except (OSError, ValueError, KeyError, EOFError, BadZipFile):
            return False

    def _ensure_index(self, cancel=None):
        if self._index_ready:
            return
        with self.index_lock:
            if self._index_ready:
                return
            first, last, offsets = [], [], [0]
            previous = -np.inf
            for t in self._time_batches(cancel):
                check(cancel)
                if not len(t):
                    continue
                if not np.isfinite(t).all() or np.any(t[1:] < t[:-1]) or t[0] < previous:
                    raise ValueError('time must be finite and non-decreasing')
                first.append(float(t[0]))
                previous = float(t[-1])
                last.append(previous)
                offsets.append(offsets[-1] + len(t))
            if not first:
                raise ValueError('time column is empty')
            self.first, self.last = np.array(first), np.array(last)
            self.index_offsets = np.array(offsets, dtype=np.int64)
            self.validate()
            check(cancel)
            if self.disk_cache:
                try:
                    atomic_npz(self.directory / 'time.npz', first=self.first, last=self.last, offsets=self.index_offsets)
                except OSError:
                    pass
            self._index_ready = True

    def validate(self):
        self.file_identity.validate()
        if self.origin is not None:
            self.origin.validate()

    def summary_path(self, channel):
        return self.directory / (hashlib.sha256(channel.encode()).hexdigest() + '.npz') if self.disk_cache else None

    def read_rows(self, channels, start, stop, cancel=None):
        start, stop = max(0, start), min(stop, self.metadata.rows)
        n = max(0, stop - start)
        time = np.empty(n, np.float64)
        values = {c: np.empty(n, np.float32) for c in channels}
        off = 0
        for t, ys in self.iter_raw(channels, start, stop, cancel):
            time[off:off + len(t)] = t
            for c in channels:
                values[c][off:off + len(t)] = ys[c]
            off += len(t)
        return time, values

    def _search(self, value, side, cancel, offset=0.):
        g = int(np.searchsorted(shift_time(self.last, offset), value, side=side))
        if g == len(self.last):
            return self.metadata.rows
        a, b = int(self.index_offsets[g]), int(self.index_offsets[g + 1])
        # Time-only row groups are cached under the same application budget.
        key = (self.metadata.identity, 'time', g)
        t = self.cache.get(key)
        if t is None:
            t, _ = self.read_rows([], a, b, cancel)
            self.cache.put(key, t, t.nbytes)
        return a + int(np.searchsorted(shift_time(t, offset), value, side=side))

    def bounds(self, lo, hi, cancel=None, *, padding=True, offset=0.):
        self.validate()
        check(cancel)
        self._ensure_index(cancel)
        start = self._search(lo, 'left', cancel, offset)
        stop = self._search(hi, 'right', cancel, offset)
        if hi < lo:
            return start, start
        return (max(0, start - 1), min(self.metadata.rows, stop + 1)) if padding else (start, stop)



class ParquetSource(IndexedFileSource):
    def __init__(self, path, cache=None, cache_dir=None, cancel=None, *, disk_cache=False):
        import pyarrow.parquet as pq
        from .loader import _split_time_columns, _named_signals, timestamp_resolution
        identity = self._initialize(path, cache, cache_dir, disk_cache, 'pyarrow')
        with pq.ParquetFile(self.path) as pf:
            self.time_col, columns = _split_time_columns(pf.schema_arrow.names)
            named, self.units = _named_signals(columns, lambda c: np.empty(0, np.float32))
            self.timestamp_resolution = timestamp_resolution(columns)
            self.columns = dict(zip(named, columns))
            self.offsets = np.r_[0, np.cumsum([pf.metadata.row_group(i).num_rows for i in range(pf.num_row_groups)])]
            self._rows = int(self.offsets[-1])
            if self._rows == 0:
                raise ValueError('time column is empty')
            if self._restore_index():
                extent = (float(self.first[0]), float(self.last[-1]))
            else:
                # Opening is metadata-only when Parquet has usable time statistics.
                # Validate actual sample order on the first raw/display request.
                index = pf.schema_arrow.names.index(self.time_col)
                stats = [pf.metadata.row_group(g).column(index).statistics
                         for g in range(pf.num_row_groups) if pf.metadata.row_group(g).num_rows]
                if all(v is not None and v.has_min_max and v.null_count == 0 for v in stats):
                    extent = (min(float(v.min) for v in stats), max(float(v.max) for v in stats))
                    if not np.isfinite(extent).all():
                        raise ValueError('time must be finite')
                else:
                    self._ensure_index(cancel)
                    extent = (float(self.first[0]), float(self.last[-1]))
        self.metadata = Metadata(identity, self._rows, tuple(self.columns), extent)

    def _time_batches(self, cancel):
        import pyarrow.parquet as pq
        with pq.ParquetFile(self.path) as pf:
            for batch in pf.iter_batches(columns=[self.time_col], batch_size=65536, use_threads=False):
                check(cancel)
                yield batch.column(0).to_numpy(zero_copy_only=False)

    def iter_raw(self, channels, start=0, stop=None, cancel=None):
        import pyarrow.parquet as pq
        self.validate()
        self._ensure_index(cancel)
        stop = self.metadata.rows if stop is None else min(stop, self.metadata.rows)
        if start >= stop:
            return
        first = max(0, int(np.searchsorted(self.offsets, start, side='right')) - 1)
        last = min(len(self.offsets) - 2, int(np.searchsorted(self.offsets, stop - 1, side='right')) - 1)
        columns = [self.time_col] + [self.columns[c] for c in channels]
        with pq.ParquetFile(self.path) as pf:
            for g in range(first, last + 1):
                offset = int(self.offsets[g])
                for batch in pf.iter_batches(row_groups=[g], columns=columns, batch_size=65536, use_threads=False):
                    check(cancel)
                    end = offset + len(batch)
                    a, b = max(start - offset, 0), min(stop - offset, len(batch))
                    if a < b:
                        batch = batch.slice(a, b - a)
                        t = np.asarray(batch.column(0).to_numpy(zero_copy_only=False), dtype=np.float64)
                        ys = {c: np.asarray(batch.column(i + 1).to_numpy(zero_copy_only=False), dtype=np.float32) for i, c in enumerate(channels)}
                        yield t, ys
                    offset = end
                    if offset >= stop:
                        break
        self.validate()


class SourceColumn:
    """A lazy column handle with bounded row reads and explicit materialization.

    GUI code uses the source directly. np.asarray(view) explicitly materializes one
    complete column. Arithmetic must operate on explicitly materialized arrays.
    """
    def __init__(self, source: SampleSource, channel=None, offset=0.):
        self.source, self.channel, self.offset = source, channel, offset
        self.shape = (source.metadata.rows,)
        self.size = source.metadata.rows
        self.ndim = 1
        self.dtype = np.dtype('float64' if channel is None else 'float32')

    def __len__(self):
        return self.size

    def __array__(self, dtype=None, copy=None):
        result = self.materialize()
        return np.array(result, dtype=dtype, copy=True) if copy else np.asarray(result, dtype=dtype)

    def materialize(self):
        """Read the full column; callers explicitly accept the allocation cost."""
        return self.read_rows(0, self.size)

    def read_rows(self, start, stop):
        """Read a contiguous row interval without NumPy compatibility dispatch."""
        t, ys = self.source.read_rows([] if self.channel is None else [self.channel], start, stop)
        if self.channel is not None:
            return ys[self.channel]
        return shift_time(t, self.offset)

    def __getitem__(self, item):
        if isinstance(item, (int, np.integer)):
            i = int(item)
            if i < 0:
                i += self.size
            if not 0 <= i < self.size:
                raise IndexError(i)
            if self.channel is None and i in (0, self.size - 1):
                return shift_time(self.source.metadata.time_range[0 if i == 0 else 1], self.offset)
            return self[i:i + 1][0]
        if not isinstance(item, slice):
            raise TypeError("Use materialize() before fancy indexing a lazy column")
        start, stop, step = item.indices(self.size)
        if step < 0:
            raise TypeError("Use materialize() before reversing a lazy column")
        return self.read_rows(start, stop)[::step]
