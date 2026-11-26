"""File loading for the UltraZohm data viewer.

Supports the JavaScope ``.csv`` (``;`` separated) and ``.parquet`` log formats.
All file IO uses Polars streaming scans; the JavaScope writes a trailing ``;``
that produces an empty column, which is dropped here.

Channel headers look like ``CH8=8)ia`` -- the ``CHn=n)`` bookkeeping prefix is
stripped to leave the friendly signal name, and a trailing unit token
(``_rpm``, ``_us`` ...) is extracted for axis labels.

Large logs (see ``ultrazohm_dataviewer_architecture.rst``) are handled leanly on native:

* channels parse **directly to float32** (time stays float64), avoiding a
  float64 intermediate copy at load;
* a **size guard** refuses a CSV that would not fit comfortably in RAM during
  materialization, and points the user at :func:`convert_csv_to_parquet`;
* large Parquet files are **stream-loaded** into preallocated arrays (peak ~= the
  resident dataset + one row-group), instead of materialising the whole table.
"""

from __future__ import annotations

import csv
import os
import re
from collections.abc import Callable
from dataclasses import dataclass

import numpy as np
import polars as pl

from .axis import inspect_axis, select_column
from .csv_policy import NULL_VALUES
from .model import DataRegistry, Run
from .sources import IndexedFileSource, check


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
    timestamp_resolution: float = 0.0
    skipped_columns: tuple[str, ...] = ()
    axis_column: str | None = None
    axis_domain: str = "time"

    def register(self, registry: DataRegistry) -> Run:
        run = registry.add_run(
            self.label, self.path, self.time, self.signals, self.units
        )
        run.axis_column = self.axis_column
        run.axis_domain = self.axis_domain
        run.timestamp_resolution = self.timestamp_resolution
        run.skipped_columns = self.skipped_columns
        return run


_CHANNEL_PREFIX = re.compile(r"^CH\d+\s*=\s*\d+\s*\)\s*(.*)$")


def timestamp_resolution(columns):
    """JavaScope rounds timestamps to 10 ns; generic tables retain strict checks.

    Raw CHn=n) headers survive CSV-to-Parquet conversion. They identify the
    JavaScope format; friendly signal names alone do not establish precision.
    """
    return 1e-8 if any(_CHANNEL_PREFIX.fullmatch(c.strip()) for c in columns) else 0.0


# Units commonly appended to JavaScope channel names.
_KNOWN_UNITS = ("us", "ms", "rpm", "deg", "rad", "Hz", "V", "A", "W", "Nm", "C", "K")

# -- large-log tuning (see ultrazohm_dataviewer_architecture.rst) ----------------------------
# CSV materialization checks both the estimated footprint and actual numeric
# buffer capacity. Parser batches and temporary growth copies are additional
# memory; use lazy loading when the recording cannot comfortably fit in RAM.
MAX_CSV_NUMERIC_BYTES = 10_000_000_000  # ~10 GB resident (~110M rows at 20 channels)
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


def numeric_columns(fields, axis_column=None) -> tuple[list[str], tuple[str, ...]]:
    """Split ``(name, is_numeric)`` pairs into plottable and skipped column names.

    Signals are numeric samples; text or nested columns (for example the
    observable names of a raw slow-data history) are skipped instead of
    failing the whole file. The selected independent-axis column must be numeric.
    """
    fields = list(fields)
    names = [name for name, _ in fields if name.strip()]
    time_column = select_column(names, axis_column)
    kept, skipped = [], []
    for name, numeric in fields:
        (kept if numeric or name.strip() == "" else skipped).append(name)
    if time_column in skipped:
        raise ValueError(f"time column {time_column!r} is not numeric")
    return kept, tuple(skipped)


def numeric_scan_columns(scan, axis_column=None):
    """Plottable and skipped columns of a Polars scan."""
    return numeric_columns(
        (
            (name, dtype.is_numeric() or dtype == pl.Boolean)
            for name, dtype in scan.collect_schema().items()
        ),
        axis_column,
    )


def _split_time_columns(
    column_names: list[str], axis_column=None
) -> tuple[str, list[str]]:
    """Pick the independent-axis column and the data columns.

    Empty-named columns (e.g. JavaScope's trailing ``;``) are ignored.
    """
    columns = [c for c in column_names if c.strip() != ""]
    if not columns:
        raise ValueError("File does not contain any named columns.")
    time_col = select_column(columns, axis_column)
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
        raise ValueError(
            f"{name}: time column is not non-decreasing (timestamps go backwards)."
        )


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


def _csv_column_types(columns: list[str], axis_column=None) -> dict:
    """Parse channels straight to float32 (time float64), avoiding a cast copy."""
    time_col, _ = _split_time_columns(columns, axis_column)
    return {c: pl.Float64 if c == time_col else pl.Float32 for c in columns}


def scan_csv(path, axis_column=None):
    """Lazy CSV scan of the named columns (JavaScope's trailing ``;`` dropped)."""
    delimiter = _sniff_delimiter(path)
    columns = _read_header(path, delimiter)
    return pl.scan_csv(
        path,
        separator=delimiter,
        schema_overrides=_csv_column_types(columns, axis_column),
        glob=False,
        null_values=NULL_VALUES,
    ).select(columns)


def _numeric_scan(scan, axis_column=None):
    names, skipped = numeric_scan_columns(scan, axis_column)
    time_col, columns = _split_time_columns(names, axis_column)
    return scan.select(
        pl.col(time_col).cast(pl.Float64),
        *[pl.col(c).cast(pl.Float32) for c in columns],
    ), skipped


def _batches(scan, time_col, columns):
    reader = scan.collect_batches(
        chunk_size=65536, maintain_order=True, engine="streaming"
    )
    try:
        for batch in reader:
            yield batch[time_col].to_numpy(), {c: batch[c].to_numpy() for c in columns}
    finally:
        del reader


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


def collect_csv_batches(path, columns, batches, cancel=None, *, axis_column=None):
    """Materialize numeric batches with a checked, shared allocation policy.

    The limit bounds retained numeric capacity, not parser scratch or transient
    copies during growth. Check actual rows before allocating each larger buffer.
    """
    time_col, data_columns = _split_time_columns(columns, axis_column)
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
            raise ValueError(
                "CSV too large for numeric memory budget; use lazy loading"
            )
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
    return ParsedRun(
        os.path.basename(path),
        path,
        time,
        signals,
        units,
        timestamp_resolution=timestamp_resolution(data_columns),
    )


def parse_csv(path: str, cancel=None, *, axis_column=None) -> ParsedRun:
    _guard_csv_size(path, _read_header(path, _sniff_delimiter(path)))
    scan = scan_csv(path, axis_column)
    columns = scan.collect_schema().names()
    time_col, data_columns = _split_time_columns(columns, axis_column)
    return collect_csv_batches(
        path,
        columns,
        _batches(scan, time_col, data_columns),
        cancel,
        axis_column=axis_column,
    )


def collect_parquet_batches(
    path,
    columns,
    n_rows,
    batches,
    cancel=None,
    *,
    skipped_columns=(),
    axis_column=None,
):
    """Fill contiguous arrays from numeric batches of a known row count."""
    _, data_columns = _split_time_columns(columns, axis_column)
    time = np.empty(n_rows, dtype=np.float64)
    arrays = {raw: np.empty(n_rows, dtype=np.float32) for raw in data_columns}
    off = 0
    for t, values in batches:
        check(cancel)
        end = off + len(t)
        time[off:end] = t
        for name in data_columns:
            arrays[name][off:end] = values[name]
        off = end
    if off != n_rows:
        raise ValueError("Parquet row count changed during loading")
    validate_time_axis(time, path)
    signals, units = _named_signals(data_columns, arrays.__getitem__)
    return ParsedRun(
        os.path.basename(path),
        path,
        time,
        signals,
        units,
        timestamp_resolution=timestamp_resolution(data_columns),
        skipped_columns=tuple(skipped_columns),
    )


def parse_parquet(path: str, cancel=None, *, axis_column=None) -> ParsedRun:
    scan, skipped = _numeric_scan(pl.scan_parquet(path, glob=False), axis_column)
    rows = scan.select(pl.len()).collect().item()
    time_col, columns = _split_time_columns(scan.collect_schema().names(), axis_column)
    return collect_parquet_batches(
        path,
        [time_col, *columns],
        rows,
        _batches(scan, time_col, columns),
        cancel,
        axis_column=axis_column,
        skipped_columns=skipped,
    )


def parquet_rows(path) -> int:
    return pl.scan_parquet(path, glob=False).select(pl.len()).collect().item()


def convert_csv_to_parquet(
    src: str,
    dst: str | None = None,
    *,
    cancel=None,
    axis_column=None,
    axis_domain=None,
) -> str:
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
    if not src.lower().endswith(".csv"):
        raise ValueError(f"convert expects a .csv file, got {src!r}")
    if os.path.lexists(dst):
        raise FileExistsError(f"Parquet file already exists: {dst}")
    axis = inspect_axis(src, axis_column, axis_domain)
    fd, temporary = tempfile.mkstemp(
        prefix=".uz-convert-",
        suffix=".parquet",
        dir=os.path.dirname(os.path.abspath(dst)),
    )
    os.close(fd)
    try:
        if cancel is not None:
            from .loading import convert_cancellable

            convert_cancellable(src, temporary, cancel, axis=axis)
        else:
            _write_csv_to_parquet(src, temporary, axis=axis)
        check(cancel)
        if parquet_rows(temporary) == 0:
            raise ValueError("Cannot convert CSV: time column is empty")
        check(cancel)
        # Publish only complete output, and never overwrite a destination created
        # while conversion was running. The parent owns cleanup on cancellation.
        from .user_paths import publish_new

        publish_new(temporary, dst)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)
    return dst


def _write_csv_to_parquet(src, dst, *, axis=None):
    """Stream to an unpublished temporary file; the caller validates and publishes."""
    axis = axis or inspect_axis(src)
    scan_csv(src, axis.column).sink_parquet(
        dst,
        compression="snappy",
        metadata=axis.metadata(),
        row_group_size=65536,
        maintain_order=True,
        engine="streaming",
    )
    return dst


def parse_file(
    path: str, *, cancel=None, axis_column=None, axis_domain=None
) -> ParsedRun:
    axis = inspect_axis(path, axis_column, axis_domain)
    parsed = _parse_file(path, cancel=cancel, axis_column=axis.column)
    parsed.axis_column, parsed.axis_domain = axis.column, axis.domain
    return parsed


def _parse_file(path: str, *, cancel=None, axis_column=None) -> ParsedRun:
    """Parse ``path`` into a :class:`ParsedRun` without touching any registry.

    Safe to call off the main thread; the caller registers the result later.
    """
    check(cancel)
    ext = os.path.splitext(path)[1].lower()
    if ext == ".csv":
        return parse_csv(path, cancel=cancel, axis_column=axis_column)
    if ext == ".parquet":
        return parse_parquet(path, cancel=cancel, axis_column=axis_column)
    raise ValueError(f'Unsupported file type "{ext}". Expected .csv or .parquet.')


def mark_cache_directory(directory):
    """Tag a cache (https://bford.info/cachedir/) so backups and the log browser skip it."""
    tag = os.path.join(directory, "CACHEDIR.TAG")
    if not os.path.exists(tag):
        try:
            with open(tag, "w", encoding="utf-8") as output:
                output.write(
                    "Signature: 8a477f597d28d172789f06886806bc55\n"
                    "# Converted logs and display caches of the UltraZohm Data Viewer.\n"
                )
        except OSError:
            pass  # A read-only cache stays usable.


@dataclass
class OpenedSource:
    path: str
    source: IndexedFileSource
    axis_column: str | None = None
    axis_domain: str = "time"

    def register(self, registry):
        run = registry.add_source(os.path.basename(self.path), self.path, self.source)
        run.axis_column, run.axis_domain = self.axis_column, self.axis_domain
        run.timestamp_resolution = self.source.timestamp_resolution
        run.skipped_columns = getattr(self.source, "skipped_columns", ())
        return run


def open_file(
    path,
    mode="memory",
    cache=None,
    cache_dir=None,
    *,
    disk_cache=False,
    cancel=None,
    axis_column=None,
    axis_domain=None,
):
    """Open in memory (eager arrays) or lazily (bounded file reads)."""
    from .polars_source import PolarsSource

    check(cancel)
    if mode not in ("memory", "lazy"):
        raise ValueError("loading mode must be memory or lazy")
    axis = inspect_axis(path, axis_column, axis_domain)
    axis_column, axis_domain = axis.column, axis.domain
    if mode == "memory" or not path.lower().endswith((".csv", ".parquet")):
        return parse_file(
            path, cancel=cancel, axis_column=axis_column, axis_domain=axis_domain
        )
    original, origin = path, None
    if path.lower().endswith(".csv") and disk_cache:
        # Lazy CSV with a disk cache: read through a reusable Parquet conversion.
        import hashlib
        import tempfile
        from pathlib import Path

        from .sources import FileIdentity, cache_root

        origin = FileIdentity.capture(path)
        identity = hashlib.sha256(repr((origin, axis)).encode()).hexdigest()
        root = cache_root(cache_dir)
        root.mkdir(parents=True, exist_ok=True)
        mark_cache_directory(root)
        destination = root / (identity + ".parquet")
        if not destination.exists():
            with tempfile.TemporaryDirectory(dir=root) as directory:
                temp = str(Path(directory) / "converted.parquet")
                convert_csv_to_parquet(
                    path,
                    temp,
                    cancel=cancel,
                    axis_column=axis_column,
                    axis_domain=axis_domain,
                )
                check(cancel)
                origin.validate()
                os.replace(temp, destination)
        path = str(destination)
    source = PolarsSource(
        path,
        cache,
        cache_dir,
        cancel=cancel,
        disk_cache=disk_cache,
        axis_column=axis_column,
    )
    source.origin = origin
    source.validate()
    return OpenedSource(
        original, source, axis_column=axis_column, axis_domain=axis_domain
    )
