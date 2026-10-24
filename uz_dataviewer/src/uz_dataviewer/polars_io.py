"""Optional Polars IO adapter; imported only when that backend is selected."""
from __future__ import annotations
import os
import numpy as np
import polars as pl
from .loader import (ParsedRun, _split_time_columns, _named_signals,
                     _sniff_delimiter, _read_header, _guard_csv_size, validate_time_axis)


def _table_to_parsed(table, path):
    time_col, columns = _split_time_columns(table.columns)
    time = table[time_col].cast(pl.Float64).to_numpy()
    validate_time_axis(time, path)
    signals, units = _named_signals(columns, lambda c: table[c].cast(pl.Float32).to_numpy())
    return ParsedRun(os.path.basename(path), path, time, signals, units, backend="polars")


def _csv_column_types(columns):
    time_col, _ = _split_time_columns(columns)
    return {c: pl.Float64 if c == time_col else pl.Float32 for c in columns}


def _scan_csv(path):
    delimiter = _sniff_delimiter(path)
    columns = _read_header(path, delimiter)
    return pl.scan_csv(path, separator=delimiter, schema_overrides=_csv_column_types(columns),
                       glob=False).select(columns)


def _numeric_scan(scan):
    time_col, columns = _split_time_columns(scan.collect_schema().names())
    return scan.select(pl.col(time_col).cast(pl.Float64),
                       *[pl.col(c).cast(pl.Float32) for c in columns])


def parse_csv(path: str) -> ParsedRun:
    _guard_csv_size(path, _read_header(path, _sniff_delimiter(path)))
    # Streaming execution still materializes the final frame for in-memory mode.
    return _table_to_parsed(_scan_csv(path).collect(engine="streaming"), path)


def parse_parquet(path: str) -> ParsedRun:
    scan = _numeric_scan(pl.scan_parquet(path, glob=False))
    rows = scan.select(pl.len()).collect().item()
    time_col, columns = _split_time_columns(scan.collect_schema().names())
    # ImPlot/analysis require contiguous NumPy arrays. Fill them from batches
    # instead of retaining a full chunked frame plus a second contiguous copy.
    time = np.empty(rows, dtype=np.float64)
    arrays = {column: np.empty(rows, dtype=np.float32) for column in columns}
    offset = 0
    for batch in scan.collect_batches(chunk_size=65536, maintain_order=True, engine="streaming"):
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


def convert_csv_to_parquet(src: str, dst: str | None = None) -> str:
    """Native streaming sink: never collect the complete CSV before writing."""
    if not src.lower().endswith(".csv"):
        raise ValueError(f"convert expects a .csv file, got {src!r}")
    if dst is None:
        dst = os.path.splitext(src)[0] + ".parquet"
    _scan_csv(src).sink_parquet(dst, compression="snappy", row_group_size=65536,
                                maintain_order=True, engine="streaming")
    return dst
