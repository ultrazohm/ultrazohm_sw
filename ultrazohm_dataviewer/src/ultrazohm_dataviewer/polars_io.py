"""Optional Polars IO adapter; imported only when that backend is selected."""

from __future__ import annotations

import polars as pl

from .csv_policy import NULL_VALUES
from .loader import (
    ParsedRun,
    _guard_csv_size,
    _read_header,
    _sniff_delimiter,
    _split_time_columns,
    collect_parquet_batches,
)


def _csv_column_types(columns, axis_column=None):
    time_col, _ = _split_time_columns(columns, axis_column)
    return {c: pl.Float64 if c == time_col else pl.Float32 for c in columns}


def _scan_csv(path, axis_column=None):
    delimiter = _sniff_delimiter(path)
    columns = _read_header(path, delimiter)
    return pl.scan_csv(
        path,
        separator=delimiter,
        schema_overrides=_csv_column_types(columns, axis_column),
        glob=False,
        null_values=NULL_VALUES,
    ).select(columns)


def numeric_scan_columns(scan, axis_column=None):
    """Plottable and skipped columns of a scan, as for the PyArrow loaders."""
    from .loader import numeric_columns

    return numeric_columns(
        (
            (name, dtype.is_numeric() or dtype == pl.Boolean)
            for name, dtype in scan.collect_schema().items()
        ),
        axis_column,
    )


def _numeric_scan(scan, axis_column=None):
    names, skipped = numeric_scan_columns(scan, axis_column)
    time_col, columns = _split_time_columns(names, axis_column)
    return scan.select(
        pl.col(time_col).cast(pl.Float64),
        *[pl.col(c).cast(pl.Float32) for c in columns],
    ), skipped


def parse_csv(path: str, cancel=None, *, axis_column=None) -> ParsedRun:
    _guard_csv_size(path, _read_header(path, _sniff_delimiter(path)))
    from .loader import collect_csv_batches

    scan = _scan_csv(path, axis_column)
    columns = scan.collect_schema().names()
    time_col, data_columns = _split_time_columns(columns, axis_column)
    reader = scan.collect_batches(
        chunk_size=65536, maintain_order=True, engine="streaming"
    )
    try:
        batches = (
            (batch[time_col].to_numpy(), {c: batch[c].to_numpy() for c in data_columns})
            for batch in reader
        )
        return collect_csv_batches(
            path, columns, batches, cancel, backend="polars", axis_column=axis_column
        )
    finally:
        del reader


def parse_parquet(path: str, cancel=None, *, axis_column=None) -> ParsedRun:
    scan, skipped = _numeric_scan(pl.scan_parquet(path, glob=False), axis_column)
    rows = scan.select(pl.len()).collect().item()
    time_col, columns = _split_time_columns(scan.collect_schema().names(), axis_column)
    reader = scan.collect_batches(
        chunk_size=65536, maintain_order=True, engine="streaming"
    )
    try:
        batches = (
            (batch[time_col].to_numpy(), {c: batch[c].to_numpy() for c in columns})
            for batch in reader
        )
        return collect_parquet_batches(
            path,
            [time_col, *columns],
            rows,
            batches,
            cancel,
            backend="polars",
            strict_rows=True,
            axis_column=axis_column,
            skipped_columns=skipped,
        )
    finally:
        del reader


def _write_csv_to_parquet(src: str, dst: str, *, axis) -> str:
    """Stream to an unpublished temporary file; loader owns validation/publication."""
    _scan_csv(src, axis.column).sink_parquet(
        dst,
        compression="snappy",
        metadata=axis.metadata(),
        row_group_size=65536,
        maintain_order=True,
        engine="streaming",
    )
    return dst
