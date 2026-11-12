"""Polars scans with projection/slice pushdown and shared sample-preserving summaries."""
import numpy as np
import polars as pl
from .sources import IndexedFileSource, Metadata, check


class PolarsSource(IndexedFileSource):
    def __init__(self, path, cache=None, cache_dir=None, cancel=None, *, disk_cache=False):
        from .loader import _split_time_columns, _named_signals, timestamp_resolution
        identity = self._initialize(path, cache, cache_dir, disk_cache, 'polars')
        if self.path.suffix.lower() == ".csv":
            from .polars_io import _scan_csv
            self.scan = _scan_csv(str(self.path))
        else:
            self.scan = pl.scan_parquet(self.path, glob=False)
        self.time_col, columns = _split_time_columns(self.scan.collect_schema().names())
        named, self.units = _named_signals(columns, lambda c: np.empty(0, np.float32))
        self.timestamp_resolution = timestamp_resolution(columns)
        self.columns = dict(zip(named, columns))
        self._rows = self.scan.select(pl.len()).collect(engine="streaming").item()
        check(cancel)
        if not self._rows:
            raise ValueError('time column is empty')
        if self._restore_index():
            extent = (float(self.first[0]), float(self.last[-1]))
        else:
            # Two slice-pushed queries avoid scanning the full timestamp column on open.
            first = self.scan.select(self.time_col).head(1).collect().item()
            last = self.scan.select(self.time_col).slice(self._rows - 1, 1).collect().item()
            extent = (float(first), float(last))
            if not np.isfinite(extent).all():
                raise ValueError('time must be finite')
        check(cancel)
        self.metadata = Metadata(identity, self._rows, tuple(self.columns), extent)

    def _time_batches(self, cancel):
        batches = self.scan.select(pl.col(self.time_col).cast(pl.Float64)).collect_batches(
            chunk_size=65536, maintain_order=True, engine="streaming")
        try:
            for batch in batches:
                check(cancel)
                yield batch[self.time_col].to_numpy()
        finally:
            del batches

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
