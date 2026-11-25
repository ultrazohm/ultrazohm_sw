"""Independent-axis selection shared by loaders, conversions and sessions."""

import json
import os
from dataclasses import dataclass

KEY = "ultrazohm.axis"


@dataclass(frozen=True)
class SignalMetadata:
    """Computational meaning and provenance of one signal's sample arrays."""

    domain: str
    unit: str
    timestamp_resolution: float
    source_identity: object

    def __post_init__(self):
        if self.domain not in ("time", "frequency"):
            raise ValueError("axis domain must be time or frequency")


class AxisSelectionRequired(ValueError):
    code = "axis_selection_required"

    def __init__(self, columns):
        self.columns = tuple(columns)
        super().__init__(
            "Choose an axis_column and axis_domain (time or frequency); "
            "no unambiguous time/frequency column was found. Columns: "
            + ", ".join(columns)
        )


def select_column(columns, axis_column=None):
    columns = [c for c in columns if c.strip()]
    if not columns:
        raise ValueError("File does not contain any named columns.")
    if axis_column is not None:
        if not isinstance(axis_column, str) or axis_column not in columns:
            raise ValueError(f"Unknown axis column: {axis_column!r}")
        return axis_column
    known = [c for c in columns if c in ("time", "frequency")]
    if len(known) != 1:
        raise AxisSelectionRequired(columns)
    return known[0]


@dataclass(frozen=True)
class Axis:
    column: str
    domain: str

    def metadata(self):
        return {KEY: json.dumps({"column": self.column, "domain": self.domain})}


def inspect_axis(path, axis_column=None, axis_domain=None):
    from .loader import _read_header, _sniff_delimiter

    path = os.fspath(path)
    saved = {}
    if path.lower().endswith(".parquet"):
        import polars as pl

        columns = pl.scan_parquet(path, glob=False).collect_schema().names()
        metadata = pl.read_parquet_metadata(path)
        if raw := metadata.get(KEY):
            saved = json.loads(raw)
            if not isinstance(saved, dict):
                raise ValueError("Invalid Parquet axis metadata")
    elif path.lower().endswith(".csv"):
        columns = _read_header(path, _sniff_delimiter(path))
    else:
        raise ValueError("Expected a .csv or .parquet file")
    if axis_column is None:
        axis_column = saved.get("column")
    column = select_column(columns, axis_column)
    domain = (
        axis_domain
        if axis_domain is not None
        else (saved.get("domain") if column == saved.get("column") else None)
    )
    if domain is None:
        domain = "frequency" if column == "frequency" else "time"
    if domain not in ("time", "frequency"):
        raise ValueError("axis_domain must be time or frequency")
    return Axis(column, domain)
