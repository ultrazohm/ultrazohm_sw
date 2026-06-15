"""File loading for the UltraZohm data viewer.

Supports the JavaScope ``.csv`` (``;`` separated) and ``.parquet`` log formats.
CSV parsing uses Apache Arrow's multi-threaded reader which keeps memory and
load time reasonable even for multi-gigabyte logs; the JavaScope writes a
trailing ``;`` that produces an empty column, which is dropped here.

Channel headers look like ``CH8=8)ia`` -- the ``CHn=n)`` bookkeeping prefix is
stripped to leave the friendly signal name, and a trailing unit token
(``_rpm``, ``_us`` ...) is extracted for axis labels.
"""

from __future__ import annotations

import os
import re

import numpy as np
import pyarrow as pa
import pyarrow.csv as pa_csv
import pyarrow.parquet as pq

from .model import DataRegistry, Run

_CHANNEL_PREFIX = re.compile(r"^CH\d+\s*=\s*\d+\s*\)\s*(.*)$")
# Units commonly appended to JavaScope channel names.
_KNOWN_UNITS = ("us", "ms", "rpm", "deg", "rad", "Hz", "V", "A", "W", "Nm", "C", "K")


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


def _table_to_run(table: pa.Table, registry: DataRegistry, path: str) -> Run:
    columns = [c for c in table.column_names if c.strip() != ""]
    if not columns:
        raise ValueError("File does not contain any named columns.")

    time_col = "time" if "time" in columns else columns[0]
    data_columns = [c for c in columns if c != time_col]
    if not data_columns:
        raise ValueError("File does not contain any signal columns besides time.")

    time = table.column(time_col).to_numpy(zero_copy_only=False).astype(np.float64)

    signals: dict[str, np.ndarray] = {}
    units: dict[str, str] = {}
    for raw in data_columns:
        name, unit = parse_channel_name(raw)
        # Guard against duplicate friendly names by falling back to the raw header.
        if name in signals:
            name = raw.strip()
        values = table.column(raw).to_numpy(zero_copy_only=False).astype(np.float32)
        signals[name] = values
        units[name] = unit

    label = os.path.basename(path)
    return registry.add_run(label, path, time, signals, units)


def _sniff_delimiter(path: str) -> str:
    """Pick the CSV delimiter from the header row.

    JavaScope logs are ``;``-separated; CSVs exported by this viewer (and most
    other tools) are ``,``-separated. Choosing by the header makes export -> import
    round-trip, and we default to ``;`` (the native format) on a tie.
    """
    with open(path, encoding="utf-8", errors="replace") as fh:
        header = fh.readline()
    return "," if header.count(",") > header.count(";") else ";"


def load_csv(path: str, registry: DataRegistry) -> Run:
    table = pa_csv.read_csv(
        path,
        parse_options=pa_csv.ParseOptions(delimiter=_sniff_delimiter(path)),
        read_options=pa_csv.ReadOptions(use_threads=True),
        convert_options=pa_csv.ConvertOptions(strings_can_be_null=True),
    )
    return _table_to_run(table, registry, path)


def load_parquet(path: str, registry: DataRegistry) -> Run:
    table = pq.read_table(path)
    return _table_to_run(table, registry, path)


def load_file(path: str, registry: DataRegistry) -> Run:
    """Load ``path`` into ``registry`` and return the created :class:`Run`."""
    ext = os.path.splitext(path)[1].lower()
    if ext == ".csv":
        return load_csv(path, registry)
    if ext == ".parquet":
        return load_parquet(path, registry)
    raise ValueError(f'Unsupported file type "{ext}". Expected .csv or .parquet.')
