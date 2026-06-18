"""File loading for the UltraZohm data viewer.

Supports the JavaScope ``.csv`` (``;`` separated) and ``.parquet`` log formats.
CSV parsing uses Apache Arrow's multi-threaded reader which keeps memory and
load time reasonable; the JavaScope writes a trailing ``;`` that produces an
empty column, which is dropped here.

Channel headers look like ``CH8=8)ia`` -- the ``CHn=n)`` bookkeeping prefix is
stripped to leave the friendly signal name, and a trailing unit token
(``_rpm``, ``_us`` ...) is extracted for axis labels.

Large logs (see ``docs/WEB_LARGE_LOGS.md``) are handled leanly on native:

* channels parse **directly to float32** (time stays float64), avoiding a
  float64 intermediate copy at load;
* a **size guard** refuses a CSV that would not fit comfortably in RAM during the
  bulk parse, and points the user at :func:`convert_csv_to_parquet`;
* large Parquet files are **stream-loaded** into preallocated arrays (peak ~= the
  resident dataset + one row-group), instead of materialising the whole table.
"""

from __future__ import annotations

import os
import re
from dataclasses import dataclass
from typing import Callable

import numpy as np
import pyarrow as pa
import pyarrow.csv as pa_csv
import pyarrow.parquet as pq

from .model import DataRegistry, Run


@dataclass
class ParsedRun:
    """A fully-parsed log not yet added to any registry.

    Parsing (the slow, allocation-heavy work) can run on a worker thread; registering
    -- the only step that mutates the shared :class:`DataRegistry` -- is then done on
    the main thread via :meth:`register`, keeping the registry single-threaded.
    """

    label: str
    path: str
    time: np.ndarray
    signals: dict[str, np.ndarray]
    units: dict[str, str]

    def register(self, registry: DataRegistry) -> Run:
        return registry.add_run(self.label, self.path, self.time, self.signals, self.units)

_CHANNEL_PREFIX = re.compile(r"^CH\d+\s*=\s*\d+\s*\)\s*(.*)$")
# Units commonly appended to JavaScope channel names.
_KNOWN_UNITS = ("us", "ms", "rpm", "deg", "rad", "Hz", "V", "A", "W", "Nm", "C", "K")

# -- large-log tuning (see docs/WEB_LARGE_LOGS.md) ----------------------------
# A CSV is bulk-parsed by Arrow, which holds the whole table in RAM *alongside*
# the output arrays, so the load peak is several times the resident numeric size.
# We refuse a CSV whose estimated resident footprint exceeds this budget and route
# the user to the streaming CSV->Parquet converter; Parquet then loads through the
# streaming path at a ~1.5x peak. Resident bytes ~= rows * (8 + 4*n_channels).
#
# NOTE: this budget is measured against the *resident* footprint, NOT the
# bulk-parse peak. Arrow's read_csv transiently uses ~2-3x the resident size, so a
# CSV just under this limit can still peak well above 10 GB during parsing. The
# value is therefore a deliberately high ceiling that only blocks extreme files;
# it is not a guarantee the bulk parse fits in 10 GB of RAM.
MAX_CSV_NUMERIC_BYTES = 10_000_000_000  # ~10 GB resident (~110M rows at 20 channels)
# Parquet files below this many rows use the simple bulk reader; larger ones stream.
PARQUET_STREAM_MIN_ROWS = 2_000_000
# Rough average characters per numeric text field, used *only* to turn a CSV file
# size into a row estimate for the size guard (and its message). Not exact.
_CSV_AVG_FIELD_CHARS = 8


def parse_channel_name(raw: str) -> tuple[str, str]:
    """Return ``(name, unit)`` for a raw column header.

    >>> parse_channel_name("CH8=8)ia")
    ('ia', '')
    >>> parse_channel_name("CH15=15)Speed_rpm")
    ('Speed_rpm', 'rpm')
    """
    name = raw.strip()
    match = _CHANNEL_PREFIX.match(name)
    if match:
        name = match.group(1).strip()
    unit = ""
    if "_" in name:
        candidate = name.rsplit("_", 1)[-1]
        if candidate in _KNOWN_UNITS:
            unit = candidate
    return name, unit


def _split_time_columns(column_names: list[str]) -> tuple[str, list[str]]:
    """Pick the time column (``"time"`` or the first) and the data columns.

    Empty-named columns (e.g. JavaScope's trailing ``;``) are ignored.
    """
    columns = [c for c in column_names if c.strip() != ""]
    if not columns:
        raise ValueError("File does not contain any named columns.")
    time_col = "time" if "time" in columns else columns[0]
    data_columns = [c for c in columns if c != time_col]
    if not data_columns:
        raise ValueError("File does not contain any signal columns besides time.")
    return time_col, data_columns


def _named_signals(
    data_columns: list[str], get_values: Callable[[str], np.ndarray]
) -> tuple[dict[str, np.ndarray], dict[str, str]]:
    """Map raw headers to ``{friendly_name: float32 array}`` plus units.

    Shared by the bulk and streaming loaders so they agree on naming and on the
    duplicate-name fallback (use the raw header when two channels clean to the
    same friendly name).
    """
    signals: dict[str, np.ndarray] = {}
    units: dict[str, str] = {}
    for raw in data_columns:
        name, unit = parse_channel_name(raw)
        if name in signals:
            name = raw.strip()
        signals[name] = np.asarray(get_values(raw), dtype=np.float32)
        units[name] = unit
    return signals, units


def validate_time_axis(time: np.ndarray, path: str) -> None:
    """Reject a log whose time axis breaks the app-wide monotonic contract.

    ``visible_slice`` -- and therefore plotting, cursors, FFT and export windows --
    assumes a non-empty, finite, non-decreasing time axis; a log that violates it
    would silently produce wrong slices and spectra. Fail the load with a clear
    message instead. Duplicates (equal timestamps) are allowed; only a *decreasing*
    step, NaN/Inf, or an empty axis is rejected. One pass over the time column only
    (not the channels), negligible against parse cost.
    """
    name = os.path.basename(path)
    if time.shape[0] == 0:
        raise ValueError(f"{name}: time column is empty.")
    if not np.isfinite(time).all():
        raise ValueError(f"{name}: time column contains non-finite values (NaN/Inf).")
    if time.shape[0] > 1 and np.any(time[1:] < time[:-1]):
        raise ValueError(f"{name}: time column is not non-decreasing (timestamps go backwards).")


def _table_to_parsed(table: pa.Table, path: str) -> ParsedRun:
    time_col, data_columns = _split_time_columns(table.column_names)
    time = table.column(time_col).to_numpy(zero_copy_only=False).astype(np.float64)
    validate_time_axis(time, path)
    signals, units = _named_signals(
        data_columns,
        lambda raw: table.column(raw).to_numpy(zero_copy_only=False),
    )
    return ParsedRun(os.path.basename(path), path, time, signals, units)


def _sniff_delimiter(path: str) -> str:
    """Pick the CSV delimiter from the header row.

    JavaScope logs are ``;``-separated; CSVs exported by this viewer (and most
    other tools) are ``,``-separated. Choosing by the header makes export -> import
    round-trip, and we default to ``;`` (the native format) on a tie.
    """
    with open(path, encoding="utf-8", errors="replace") as fh:
        header = fh.readline()
    return "," if header.count(",") > header.count(";") else ";"


def _read_header(path: str, delimiter: str) -> list[str]:
    """Return the non-empty column names from the CSV header row."""
    with open(path, encoding="utf-8", errors="replace") as fh:
        header = fh.readline()
    return [c.strip() for c in header.rstrip("\r\n").split(delimiter) if c.strip() != ""]


def _csv_column_types(columns: list[str]) -> dict[str, pa.DataType]:
    """Arrow ``column_types`` so channels parse straight to float32.

    The time column is read as float64; every other named column as float32. This
    avoids Arrow inferring float64 for the channels and a later float64->float32
    cast (a full extra copy) -- the dominant load-peak cost on big logs.
    """
    if not columns:
        return {}
    time_col = "time" if "time" in columns else columns[0]
    return {c: (pa.float64() if c == time_col else pa.float32()) for c in columns}


def _estimate_csv_rows_and_bytes(path: str, columns: list[str]) -> tuple[int, int]:
    """Rough ``(rows, resident_bytes)`` estimate for the size guard.

    ``resident_bytes`` is the in-RAM numeric footprint (time float64 + channels
    float32), estimated from the file size and column count -- not exact, but
    enough to refuse a CSV that would risk OOM during the bulk parse.
    """
    n_cols = max(1, len(columns))
    n_channels = max(0, len(columns) - 1)  # all but the time column
    est_rows = int(os.path.getsize(path) / (n_cols * _CSV_AVG_FIELD_CHARS))
    resident = est_rows * (8 + 4 * n_channels)
    return est_rows, resident


def _guard_csv_size(path: str, columns: list[str]) -> None:
    est_rows, resident = _estimate_csv_rows_and_bytes(path, columns)
    if resident > MAX_CSV_NUMERIC_BYTES:
        gb = resident / (1024**3)
        raise ValueError(
            f"CSV too large (~{est_rows / 1e6:.0f}M rows, ~{gb:.1f} GB in memory). "
            "Bulk CSV parsing risks running out of memory; convert it to Parquet "
            "first (Parquet streams in at a ~1.5x peak), then open the .parquet:\n"
            f'    convert("{path}")'
        )


def parse_csv(path: str) -> ParsedRun:
    delimiter = _sniff_delimiter(path)
    columns = _read_header(path, delimiter)
    _guard_csv_size(path, columns)
    table = pa_csv.read_csv(
        path,
        parse_options=pa_csv.ParseOptions(delimiter=delimiter),
        read_options=pa_csv.ReadOptions(use_threads=True),
        convert_options=pa_csv.ConvertOptions(
            strings_can_be_null=True,
            column_types=_csv_column_types(columns),
        ),
    )
    return _table_to_parsed(table, path)


def _parse_parquet_streaming(pf: pq.ParquetFile, path: str, n_rows: int) -> ParsedRun:
    """Stream a large Parquet into preallocated arrays (peak ~= resident + a batch)."""
    time_col, data_columns = _split_time_columns(pf.schema_arrow.names)
    ordered = [time_col, *data_columns]
    time = np.empty(n_rows, dtype=np.float64)
    arrays = {raw: np.empty(n_rows, dtype=np.float32) for raw in data_columns}

    off = 0
    for batch in pf.iter_batches(columns=ordered):
        m = batch.num_rows
        for j, name in enumerate(ordered):
            values = batch.column(j).to_numpy(zero_copy_only=False)
            target = time if name == time_col else arrays[name]
            target[off : off + m] = values
        off += m
    if off != n_rows:  # metadata disagreed with the data; trim to what we read
        time = time[:off]
        arrays = {k: v[:off] for k, v in arrays.items()}

    validate_time_axis(time, path)
    signals, units = _named_signals(data_columns, lambda raw: arrays[raw])
    return ParsedRun(os.path.basename(path), path, time, signals, units)


def parse_parquet(path: str) -> ParsedRun:
    pf = pq.ParquetFile(path)
    n_rows = pf.metadata.num_rows
    if n_rows < PARQUET_STREAM_MIN_ROWS:
        return _table_to_parsed(pf.read(), path)
    return _parse_parquet_streaming(pf, path, n_rows)


def convert_csv_to_parquet(src: str, dst: str | None = None) -> str:
    """Stream-convert a CSV log to Parquet with bounded memory.

    Reads ``src`` in row-group batches (never the whole file at once), casts
    channels to float32 / time to float64, drops empty columns (JavaScope's
    trailing ``;``) and writes ``dst``. Raw headers (``CH8=8)ia``) are preserved so
    the resulting Parquet round-trips through the same name parsing on load.
    Returns the output path (``src`` with a ``.parquet`` extension by default).
    """
    if not src.lower().endswith(".csv"):
        raise ValueError(f"convert expects a .csv file, got {src!r}")
    if dst is None:
        dst = os.path.splitext(src)[0] + ".parquet"

    delimiter = _sniff_delimiter(src)
    columns = _read_header(src, delimiter)
    reader = pa_csv.open_csv(
        src,
        parse_options=pa_csv.ParseOptions(delimiter=delimiter),
        read_options=pa_csv.ReadOptions(use_threads=True),
        convert_options=pa_csv.ConvertOptions(
            strings_can_be_null=True,
            column_types=_csv_column_types(columns),
        ),
    )
    writer: pq.ParquetWriter | None = None
    try:
        for batch in reader:
            batch = _drop_empty_columns(batch)
            if writer is None:
                writer = pq.ParquetWriter(dst, batch.schema)
            writer.write_batch(batch)
    finally:
        if writer is not None:
            writer.close()
        reader.close()
    return dst


def _drop_empty_columns(batch: pa.RecordBatch) -> pa.RecordBatch:
    keep = [i for i, name in enumerate(batch.schema.names) if name.strip() != ""]
    if len(keep) == batch.num_columns:
        return batch
    return batch.select(keep)


def parse_file(path: str) -> ParsedRun:
    """Parse ``path`` into a :class:`ParsedRun` without touching any registry.

    Safe to call off the main thread; the caller registers the result later.
    """
    ext = os.path.splitext(path)[1].lower()
    if ext == ".csv":
        return parse_csv(path)
    if ext == ".parquet":
        return parse_parquet(path)
    raise ValueError(f'Unsupported file type "{ext}". Expected .csv or .parquet.')


def load_file(path: str, registry: DataRegistry) -> Run:
    """Parse ``path`` and register it into ``registry`` (single-threaded callers)."""
    return parse_file(path).register(registry)
