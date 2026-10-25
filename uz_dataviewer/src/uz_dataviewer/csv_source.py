"""Streaming PyArrow CSV source without a persistent conversion or index."""

import numpy as np

from .sources import IndexedFileSource, Metadata, check


class CsvSource(IndexedFileSource):
    def __init__(self, path, cache=None, cache_dir=None, cancel=None, *, disk_cache=False):
        from .loader import _read_header, _sniff_delimiter, _split_time_columns, _named_signals
        identity = self._initialize(path, cache, cache_dir, False, 'csv')
        self.delimiter = _sniff_delimiter(str(self.path))
        columns = _read_header(str(self.path), self.delimiter)
        self.time_col, columns = _split_time_columns(columns)
        named, self.units = _named_signals(columns, lambda c: np.empty(0, np.float32))
        self.columns = dict(zip(named, columns))
        self._ensure_index(cancel)
        self.metadata = Metadata(identity, int(self.index_offsets[-1]), tuple(self.columns),
                                 (float(self.first[0]), float(self.last[-1])))
        self.validate()

    def _time_batches(self, cancel):
        for t, _ in self._batches([], cancel):
            yield t

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
