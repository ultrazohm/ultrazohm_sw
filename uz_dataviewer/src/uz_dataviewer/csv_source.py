"""Streaming PyArrow CSV source without a persistent conversion or index."""
import hashlib
import threading
from pathlib import Path

import numpy as np

from .sources import ParquetSource, ByteCache, Metadata, check


class CsvSource(ParquetSource):
    def __init__(self, path, cache=None, cache_dir=None, cancel=None, *, disk_cache=False):
        from .loader import _read_header, _sniff_delimiter, _split_time_columns, _named_signals
        self.path = Path(path).resolve()
        self.signature = self._signature()
        self.disk_cache = False
        self.cache = cache if cache is not None else ByteCache()
        self.summary_lock = threading.Lock()
        self.delimiter = _sniff_delimiter(str(self.path))
        columns = _read_header(str(self.path), self.delimiter)
        self.time_col, columns = _split_time_columns(columns)
        named, self.units = _named_signals(columns, lambda c: np.empty(0, np.float32))
        self.columns = dict(zip(named, columns))
        first, last, offsets = [], [], [0]
        previous = -np.inf
        for t, _ in self._batches([], cancel):
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
        identity = hashlib.sha256(repr(('csv', str(self.path), self.signature)).encode()).hexdigest()
        self.metadata = Metadata(identity, offsets[-1], tuple(self.columns), (first[0], last[-1]))
        self.validate()

    def _ensure_index(self, cancel=None):
        check(cancel)

    def _batches(self, channels, cancel):
        import pyarrow.csv as csv
        from .loader import _csv_column_types
        columns = [self.time_col] + [self.columns[c] for c in channels]
        with csv.open_csv(str(self.path), parse_options=csv.ParseOptions(delimiter=self.delimiter),
                          convert_options=csv.ConvertOptions(include_columns=columns,
                              column_types=_csv_column_types(columns))) as reader:
            for batch in reader:
                check(cancel)
                yield np.asarray(batch.column(0), dtype=np.float64), {
                    c: np.asarray(batch.column(i + 1), dtype=np.float32)
                    for i, c in enumerate(channels)}

    def iter_raw(self, channels, start=0, stop=None, cancel=None):
        self.validate()
        stop = self.metadata.rows if stop is None else min(stop, self.metadata.rows)
        offset = 0
        for t, ys in self._batches(channels, cancel):
            end = offset + len(t)
            a, b = max(0, start - offset), min(len(t), stop - offset)
            if a < b:
                yield t[a:b], {c: y[a:b] for c, y in ys.items()}
            offset = end
            if offset >= stop:
                break
        self.validate()
