"""File loading for the UltraZohm data viewer.

Supports the JavaScope ``.csv`` (``;`` separated) and ``.parquet`` log formats.
CSV parsing uses Apache Arrow's multi-threaded reader which keeps memory and
load time reasonable; the JavaScope writes a trailing ``;`` that produces an
empty column, which is dropped here.

Channel headers look like ``CH8=8)ia`` -- the ``CHn=n)`` bookkeeping prefix is
stripped to leave the friendly signal name, and a trailing unit token
(``_rpm``, ``_us`` ...) is extracted for axis labels.

Large logs (see ``uz_dataviewer_architecture.rst``) are handled leanly on native:

* channels parse **directly to float32** (time stays float64), avoiding a
  float64 intermediate copy at load;
* a **size guard** refuses a CSV that would not fit comfortably in RAM during
  materialization, and points the user at :func:`convert_csv_to_parquet`;
* large Parquet files are **stream-loaded** into preallocated arrays (peak ~= the
  resident dataset + one row-group), instead of materialising the whole table.
"""

from __future__ import annotations

from . import runtime

import os
import re
import csv
from dataclasses import dataclass
from typing import Callable

import numpy as np
import pyarrow as pa
import pyarrow.csv as pa_csv
import pyarrow.parquet as pq

from .model import DataRegistry, Run
from .sources import IndexedFileSource, check
from .csv_policy import NULL_VALUES


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
    backend: str = "pyarrow"

    def register(self, registry: DataRegistry) -> Run:
        run = registry.add_run(self.label, self.path, self.time, self.signals, self.units)
        run.backend = self.backend
        return run

_CHANNEL_PREFIX = re.compile(r"^CH\d+\s*=\s*\d+\s*\)\s*(.*)$")
# Units commonly appended to JavaScope channel names.
_KNOWN_UNITS = ("us", "ms", "rpm", "deg", "rad", "Hz", "V", "A", "W", "Nm", "C", "K")

# -- large-log tuning (see uz_dataviewer_architecture.rst) ----------------------------
# CSV materialization checks both the estimated footprint and actual numeric
# buffer capacity. Parser batches and temporary growth copies are additional
# memory; use lazy loading when the recording cannot comfortably fit in RAM.
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


def unique_name(name: str, used: set[str]) -> str:
    """Allocate a deterministic name without overwriting an existing column."""
    base, number = name, 2
    while name in used:
        name = f"{base} [{number}]"
        number += 1
    used.add(name)
    return name


def _named_signals(
    data_columns: list[str], get_values: Callable[[str], np.ndarray]
) -> tuple[dict[str, np.ndarray], dict[str, str]]:
    """Map raw headers to ``{friendly_name: float32 array}`` plus units.

    Shared by all loaders. Prefer a raw-header fallback on collisions, then
    allocate a numbered suffix. Reserve time for exported timestamp columns.
    """
    signals: dict[str, np.ndarray] = {}
    units: dict[str, str] = {}
    used = {"time"}
    for raw in data_columns:
        name, unit = parse_channel_name(raw)
        if name in used:
            name = raw.strip()
        name = unique_name(name, used)
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
    with open(path, encoding="utf-8-sig", errors="replace") as fh:
        header = fh.readline()
    counts = {",": 0, ";": 0}
    quoted = False
    for char in header:
        if char == '"':
            quoted = not quoted
        elif not quoted and char in counts:
            counts[char] += 1
    return "," if counts[","] > counts[";"] else ";"


def _read_header(path: str, delimiter: str) -> list[str]:
    """Return the non-empty column names from the CSV header row."""
    with open(path, encoding="utf-8-sig", newline="") as fh:
        header = next(csv.reader(fh, delimiter=delimiter, strict=True), [])
    if len(set(header)) != len(header):
        raise ValueError("CSV header contains duplicate column names")
    return [c for c in header if c.strip() != ""]


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
            f"CSV too large (~{est_rows / 1e6:.0f}M rows, ~{gb:.1f} GB resident in RAM). "
            "CSV materialization retains the full record, which must "
            "fit in memory. Use lazy loading or convert to Parquet:\n"
            f'    convert("{path}")'
        )


def _grow(arr: np.ndarray, new_cap: int, used: int) -> np.ndarray:
    """Return a copy of ``arr`` resized to ``new_cap``, preserving ``arr[:used]``."""
    out = np.empty(new_cap, dtype=arr.dtype)
    out[:used] = arr[:used]
    return out


def collect_csv_batches(path, columns, batches, cancel=None, *, backend="pyarrow"):
    """Materialize numeric batches with a checked, shared allocation policy.

    The limit bounds retained numeric capacity, not parser scratch or transient
    copies during growth. Check actual rows before allocating each larger buffer.
    """
    time_col, data_columns = _split_time_columns(columns)
    row_bytes = 8 + 4 * len(data_columns)
    max_rows = MAX_CSV_NUMERIC_BYTES // row_bytes
    if max_rows < 1:
        raise ValueError("CSV too large for numeric memory budget; use lazy loading")
    estimated, _ = _estimate_csv_rows_and_bytes(path, columns)
    cap = min(max_rows, max(1024, int(estimated * 1.1)))
    time = np.empty(cap, dtype=np.float64)
    arrays = {raw: np.empty(cap, dtype=np.float32) for raw in data_columns}
    off = 0
    for t, values in batches:
        check(cancel)
        needed = off + len(t)
        if needed > max_rows:
            raise ValueError("CSV too large for numeric memory budget; use lazy loading")
        if needed > cap:
            cap = min(max_rows, max(needed, int(cap * 1.5)))
            time = _grow(time, cap, off)
            arrays = {k: _grow(v, cap, off) for k, v in arrays.items()}
        time[off:needed] = t
        for name in data_columns:
            arrays[name][off:needed] = values[name]
        off = needed
    time = time[:off]
    validate_time_axis(time, path)
    signals, units = _named_signals(data_columns, lambda raw: arrays[raw][:off])
    return ParsedRun(os.path.basename(path), path, time, signals, units, backend=backend)


def parse_csv(path: str, cancel=None) -> ParsedRun:
    delimiter = _sniff_delimiter(path)
    columns = _read_header(path, delimiter)
    _guard_csv_size(path, columns)
    time_col, data_columns = _split_time_columns(columns)
    ordered = [time_col, *data_columns]
    with pa_csv.open_csv(
        path,
        parse_options=pa_csv.ParseOptions(delimiter=delimiter),
        read_options=pa_csv.ReadOptions(use_threads=True),
        convert_options=pa_csv.ConvertOptions(
            strings_can_be_null=True, null_values=NULL_VALUES,
            column_types=_csv_column_types(columns), include_columns=ordered,
        ),
    ) as reader:
        def batches():
            for batch in reader:
                check(cancel)
                yield batch.column(0).to_numpy(zero_copy_only=False), {
                    c: batch.column(i + 1).to_numpy(zero_copy_only=False)
                    for i, c in enumerate(data_columns)}
        return collect_csv_batches(path, columns, batches(), cancel)


def _parse_parquet_streaming(pf: pq.ParquetFile, path: str, n_rows: int, cancel=None) -> ParsedRun:
    """Stream a large Parquet into preallocated arrays (peak ~= resident + a batch)."""
    time_col, data_columns = _split_time_columns(pf.schema_arrow.names)
    ordered = [time_col, *data_columns]
    time = np.empty(n_rows, dtype=np.float64)
    arrays = {raw: np.empty(n_rows, dtype=np.float32) for raw in data_columns}

    off = 0
    for batch in pf.iter_batches(columns=ordered):
        check(cancel)
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


def parse_parquet(path: str, cancel=None) -> ParsedRun:
    pf = pq.ParquetFile(path)
    n_rows = pf.metadata.num_rows
    if n_rows < PARQUET_STREAM_MIN_ROWS:
        return _table_to_parsed(pf.read(), path)
    return _parse_parquet_streaming(pf, path, n_rows, cancel)


def convert_csv_to_parquet(src: str, dst: str | None = None, *, backend="pyarrow", cancel=None) -> str:
    """Stream-convert a CSV log to Parquet with bounded memory.

    Reads ``src`` in row-group batches (never the whole file at once), casts
    channels to float32 / time to float64, drops empty columns (JavaScope's
    trailing ``;``) and writes ``dst``. Raw headers (``CH8=8)ia``) are preserved so
    the resulting Parquet round-trips through the same name parsing on load.
    Rejects empty input and existing destinations. Publishes complete output only.
    Returns the output path (``src`` with a ``.parquet`` extension by default).
    """
    import tempfile

    src = os.fspath(src)
    dst = os.fspath(dst) if dst is not None else os.path.splitext(src)[0] + ".parquet"
    check(cancel)
    validate_backend(backend)
    if not src.lower().endswith(".csv"):
        raise ValueError(f"convert expects a .csv file, got {src!r}")
    if os.path.lexists(dst):
        raise FileExistsError(f"Parquet file already exists: {dst}")
    fd, temporary = tempfile.mkstemp(prefix=".uz-convert-", suffix=".parquet",
                                     dir=os.path.dirname(os.path.abspath(dst)))
    os.close(fd)
    try:
        if cancel is not None:
            from .loading import convert_cancellable
            convert_cancellable(src, temporary, backend, cancel)
        else:
            _write_csv_to_parquet(src, temporary, backend=backend)
        check(cancel)
        with pq.ParquetFile(temporary) as converted:
            if converted.metadata.num_rows == 0:
                raise ValueError("Cannot convert CSV: time column is empty")
        check(cancel)
        # Publish only complete output, and never overwrite a destination created
        # while conversion was running. The parent owns cleanup on cancellation.
        if runtime.IS_WEB:
            # The browser filesystem lacks hard links. Its synchronous, single-
            # threaded runtime cannot interleave a writer between check/rename.
            if os.path.lexists(dst):
                raise FileExistsError(f"Parquet file already exists: {dst}")
            os.rename(temporary, dst)
        else:
            os.link(temporary, dst)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)
    return dst


def _write_csv_to_parquet(src, dst, *, backend="pyarrow"):
    """Backend writer for an unpublished temporary file owned by the caller."""
    if backend == "polars":
        from .polars_io import _write_csv_to_parquet as write
        return write(src, dst)
    delimiter = _sniff_delimiter(src)
    columns = _read_header(src, delimiter)
    reader = pa_csv.open_csv(
        src,
        parse_options=pa_csv.ParseOptions(delimiter=delimiter),
        read_options=pa_csv.ReadOptions(use_threads=True),
        convert_options=pa_csv.ConvertOptions(
            strings_can_be_null=True,
            null_values=NULL_VALUES,
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
    if writer is None:
        raise ValueError("Cannot convert CSV: time column is empty")
    return dst


def _drop_empty_columns(batch: pa.RecordBatch) -> pa.RecordBatch:
    keep = [i for i, name in enumerate(batch.schema.names) if name.strip() != ""]
    if len(keep) == batch.num_columns:
        return batch
    return batch.select(keep)


def _release_arrow_pool() -> None:
    """Hand Arrow's freed-but-retained buffers back to the OS after a parse.

    Arrow's default memory pool keeps freed parse scratch around for reuse rather than
    returning it, so process RSS stays at the parse high-water mark (measured ~2.9 GB on
    the 0.71 GB 9M-row CSV) long after the table is gone. ``release_unused`` reclaims it
    (~1.2 GB back there, ~10 GB on the 75M log). Only buffers with no live references are
    freed, so the numpy arrays we just built are untouched.
    """
    pa.default_memory_pool().release_unused()


def parse_file(path: str, *, backend="pyarrow", cancel=None) -> ParsedRun:
    """Parse ``path`` into a :class:`ParsedRun` without touching any registry.

    Safe to call off the main thread; the caller registers the result later.
    """
    check(cancel)
    validate_backend(backend)
    if backend == "polars":
        from . import polars_io
        ext = os.path.splitext(path)[1].lower()
        if ext == ".csv":
            return polars_io.parse_csv(path, cancel=cancel)
        if ext == ".parquet":
            return polars_io.parse_parquet(path, cancel=cancel)
        raise ValueError(f'Unsupported file type "{ext}". Expected .csv or .parquet.')
    ext = os.path.splitext(path)[1].lower()
    if ext == ".csv":
        parsed = parse_csv(path, cancel=cancel)
    elif ext == ".parquet":
        parsed = parse_parquet(path, cancel=cancel)
    else:
        raise ValueError(f'Unsupported file type "{ext}". Expected .csv or .parquet.')
    check(cancel)
    _release_arrow_pool()
    return parsed


@dataclass
class OpenedSource:
    path: str
    source: IndexedFileSource
    backend: str = "pyarrow"

    def register(self, registry):
        run = registry.add_source(os.path.basename(self.path), self.path, self.source)
        run.backend = self.backend
        return run


def validate_backend(backend):
    if backend not in ("pyarrow", "polars"):
        raise ValueError("backend must be pyarrow or polars")
    if runtime.IS_WEB and backend == "polars":
        raise ValueError("Polars is available only in the desktop viewer; use pyarrow in the browser")


def open_file(path, mode="memory", cache=None, cache_dir=None, *, backend="pyarrow", disk_cache=False, cancel=None):
    """Open using a selected storage policy. Existing parse_file stays eager."""
    check(cancel)
    validate_backend(backend)
    if mode not in ("memory", "lazy"):
        raise ValueError("loading mode must be memory or lazy")
    if mode == "memory":
        return parse_file(path, backend=backend, cancel=cancel)
    if backend == "polars":
        from .polars_source import PolarsSource as SourceClass
    else:
        from .sources import ParquetSource as SourceClass
    original = path
    origin = None
    if path.lower().endswith(".csv") and not disk_cache:
        if backend == "pyarrow":
            from .csv_source import CsvSource as SourceClass
        return OpenedSource(original, SourceClass(path, cache, cache_dir, cancel=cancel, disk_cache=False), backend=backend)
    if path.lower().endswith(".csv"):
        from pathlib import Path
        import hashlib
        import tempfile
        from .sources import FileIdentity
        origin = FileIdentity.capture(path)
        identity = hashlib.sha256(repr(origin).encode()).hexdigest()
        root = Path(cache_dir or os.environ.get("UZ_DATAVIEWER_CACHE", Path.home() / ".cache" / "uz_dataviewer"))
        if backend == "polars":
            root = root / "polars"
        root.mkdir(parents=True, exist_ok=True)
        destination = root / (identity + ".parquet")
        if not destination.exists():
            with tempfile.TemporaryDirectory(dir=root) as directory:
                temp = str(Path(directory) / "converted.parquet")
                convert_csv_to_parquet(path, temp, backend=backend, cancel=cancel)
                check(cancel)
                origin.validate()
                os.replace(temp, destination)
        path = str(destination)
    elif not path.lower().endswith(".parquet"):
        return parse_file(path, backend=backend, cancel=cancel)
    source = SourceClass(path, cache, cache_dir, cancel=cancel, disk_cache=disk_cache)
    source.origin = origin
    source.validate()
    return OpenedSource(original, source, backend=backend)
