"""Optional Polars IO adapter; imported only when that backend is selected."""
from __future__ import annotations
import os
import numpy as np
import polars as pl
from .sources import check
from .csv_policy import NULL_VALUES
from .loader import (ParsedRun, _split_time_columns, _named_signals,
                     _sniff_delimiter, _read_header, _guard_csv_size, validate_time_axis)


def _csv_column_types(columns):
    time_col, _ = _split_time_columns(columns)
    return {c: pl.Float64 if c == time_col else pl.Float32 for c in columns}


def _scan_csv(path):
    delimiter = _sniff_delimiter(path)
    columns = _read_header(path, delimiter)
    return pl.scan_csv(path, separator=delimiter, schema_overrides=_csv_column_types(columns),
                       glob=False, null_values=NULL_VALUES).select(columns)


def _numeric_scan(scan):
    time_col, columns = _split_time_columns(scan.collect_schema().names())
    return scan.select(pl.col(time_col).cast(pl.Float64),
                       *[pl.col(c).cast(pl.Float32) for c in columns])


def parse_csv(path: str, cancel=None) -> ParsedRun:
    _guard_csv_size(path, _read_header(path, _sniff_delimiter(path)))
    from .loader import collect_csv_batches
    scan = _scan_csv(path)
    columns = scan.collect_schema().names()
    time_col, data_columns = _split_time_columns(columns)
    reader = scan.collect_batches(chunk_size=65536, maintain_order=True, engine="streaming")
    try:
        batches = ((batch[time_col].to_numpy(), {c: batch[c].to_numpy() for c in data_columns})
                   for batch in reader)
        return collect_csv_batches(path, columns, batches, cancel, backend="polars")
    finally:
        del reader


def parse_parquet(path: str, cancel=None) -> ParsedRun:
    scan = _numeric_scan(pl.scan_parquet(path, glob=False))
    rows = scan.select(pl.len()).collect().item()
    time_col, columns = _split_time_columns(scan.collect_schema().names())
    # ImPlot/analysis require contiguous NumPy arrays. Fill them from batches
    # instead of retaining a full chunked frame plus a second contiguous copy.
    time = np.empty(rows, dtype=np.float64)
    arrays = {column: np.empty(rows, dtype=np.float32) for column in columns}
    offset = 0
    for batch in scan.collect_batches(chunk_size=65536, maintain_order=True, engine="streaming"):
        check(cancel)
        end = offset + batch.height
        time[offset:end] = batch[time_col].to_numpy()
        for column in columns:
            arrays[column][offset:end] = batch[column].to_numpy()
        offset = end
    if offset != rows:
        raise ValueError('Parquet row count changed during loading')
    validate_time_axis(time, path)
    signals, units = _named_signals(columns, arrays.__getitem__)
    return ParsedRun(os.path.basename(path), path, time, signals, units, backend="polars")


def _write_csv_to_parquet(src: str, dst: str) -> str:
    """Stream to an unpublished temporary file; loader owns validation/publication."""
    _scan_csv(src).sink_parquet(dst, compression="snappy", row_group_size=65536,
                                maintain_order=True, engine="streaming")
    return dst
