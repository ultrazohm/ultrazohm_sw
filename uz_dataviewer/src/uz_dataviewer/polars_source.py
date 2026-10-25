"""Polars scans with projection/slice pushdown and shared sample-preserving summaries."""
import hashlib
import json
import os
from pathlib import Path
import threading
from zipfile import BadZipFile
import numpy as np
import polars as pl
from .sources import ParquetSource, ByteCache, CACHE_VERSION, Metadata, atomic_npz, check


class PolarsParquetSource(ParquetSource):
    def __init__(self, path, cache=None, cache_dir=None, cancel=None, *, disk_cache=False):
        self.disk_cache = disk_cache
        from .loader import _split_time_columns, _named_signals
        self.path = Path(path).resolve()
        self.signature = self._signature()
        identity = hashlib.sha256(json.dumps(["polars", str(self.path), self.signature, CACHE_VERSION]).encode()).hexdigest()
        root = Path(cache_dir or os.environ.get('UZ_DATAVIEWER_CACHE', Path.home() / '.cache' / 'uz_dataviewer'))
        self.directory = root / "polars" / identity
        self.cache = cache if cache is not None else ByteCache()
        self.summary_lock = threading.Lock()
        self.index_lock = threading.Lock()
        self._index_ready = False
        if self.path.suffix.lower() == ".csv":
            from .polars_io import _scan_csv
            self.scan = _scan_csv(str(self.path))
        else:
            self.scan = pl.scan_parquet(self.path, glob=False)
        self.time_col, columns = _split_time_columns(self.scan.collect_schema().names())
        named, self.units = _named_signals(columns, lambda c: np.empty(0, np.float32))
        self.columns = dict(zip(named, columns))
        self._rows = self.scan.select(pl.len()).collect(engine="streaming").item()
        if not self._rows:
            raise ValueError('time column is empty')
        try:
            if not self.disk_cache:
                raise FileNotFoundError('Disk cache disabled')
            with np.load(self.directory / 'time.npz', allow_pickle=False) as data:
                self.first, self.last, self.index_offsets = data['first'], data['last'], data['offsets']
            if (self.first.ndim != 1 or self.last.ndim != 1 or self.index_offsets.ndim != 1
                    or not len(self.first) or len(self.first) != len(self.last)
                    or len(self.index_offsets) != len(self.first) + 1
                    or self.index_offsets[0] != 0 or self.index_offsets[-1] != self._rows
                    or np.any(np.diff(self.index_offsets) <= 0)
                    or not np.isfinite(self.first).all() or not np.isfinite(self.last).all()
                    or np.any(self.first > self.last) or np.any(self.first[1:] < self.last[:-1])):
                raise ValueError('Invalid timestamp index')
            self._index_ready = True
            extent = (float(self.first[0]), float(self.last[-1]))
        except (OSError, ValueError, KeyError, EOFError, BadZipFile):
            # Two slice-pushed queries avoid scanning the full timestamp column on open.
            first = self.scan.select(self.time_col).head(1).collect().item()
            last = self.scan.select(self.time_col).slice(self._rows - 1, 1).collect().item()
            extent = (float(first), float(last))
            if not np.isfinite(extent).all():
                raise ValueError('time must be finite')
        self.metadata = Metadata(identity, self._rows, tuple(self.columns), extent)

    def _ensure_index(self, cancel=None):
        if self._index_ready:
            return
        with self.index_lock:
            if self._index_ready:
                return
            first, last, offsets = [], [], [0]
            previous = -np.inf
            batches = self.scan.select(pl.col(self.time_col).cast(pl.Float64)).collect_batches(
                chunk_size=65536, maintain_order=True, engine="streaming")
            try:
                for batch in batches:
                    check(cancel)
                    t = batch[self.time_col].to_numpy()
                    if not len(t):
                        continue
                    if not np.isfinite(t).all() or np.any(t[1:] < t[:-1]) or t[0] < previous:
                        raise ValueError('time must be finite and non-decreasing')
                    first.append(float(t[0]))
                    previous = float(t[-1])
                    last.append(previous)
                    offsets.append(offsets[-1] + len(t))
            finally:
                del batches
            self.first, self.last = np.array(first), np.array(last)
            self.index_offsets = np.array(offsets, dtype=np.int64)
            self.validate()
            check(cancel)
            try:
                if self.disk_cache:
                    atomic_npz(self.directory / 'time.npz', first=self.first, last=self.last, offsets=self.index_offsets)
            except OSError:
                pass
            self._index_ready = True

    def _signature(self):
        s = self.path.stat()
        return (s.st_size, s.st_mtime_ns, s.st_ctime_ns, s.st_ino)

    def validate(self):
        if self._signature() != self.signature:
            raise ValueError(f'Source changed; reopen {self.path.name}')

    def summary_path(self, channel):
        return self.directory / (hashlib.sha256(channel.encode()).hexdigest() + '.npz') if self.disk_cache else None

    def iter_raw(self, channels, start=0, stop=None, cancel=None):
        self.validate()
        self._ensure_index(cancel)
        stop = self.metadata.rows if stop is None else min(stop, self.metadata.rows)
        if start >= stop:
            return
        query = self.scan.slice(start, stop - start).select(
            pl.col(self.time_col).cast(pl.Float64),
            *[pl.col(self.columns[c]).cast(pl.Float32) for c in channels])
        batches = query.collect_batches(chunk_size=65536, maintain_order=True, engine="streaming")
        try:
            for batch in batches:
                check(cancel)
                yield batch[self.time_col].to_numpy(), {
                    c: batch[self.columns[c]].to_numpy() for c in channels}
        finally:
            del batches
        self.validate()
