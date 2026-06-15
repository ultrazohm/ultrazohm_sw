"""Readers for javascope log files (.csv with ';' separator, .parquet).

Files can exceed 1 GB, so loading favors pyarrow (multi-threaded C++ readers)
and converts each channel to a contiguous numpy array exactly once.
Loading runs on worker threads (see DataStore.load_files_async) so the UI
never blocks.
"""

from __future__ import annotations

import os
from dataclasses import dataclass, field

import numpy as np

TIME_COLUMN = "time"
CSV_SEPARATOR = ";"


class LoaderError(Exception):
    """Raised when a log file cannot be parsed."""


@dataclass
class Run:
    """One loaded log file: a shared time base plus named signal arrays."""

    run_id: int
    name: str
    path: str
    time: np.ndarray
    signals: dict[str, np.ndarray]
    has_real_time: bool
    warnings: list[str] = field(default_factory=list)
    active: bool = True

    @property
    def n_samples(self) -> int:
        return int(self.time.shape[0])

    @property
    def duration(self) -> float:
        if self.n_samples < 2:
            return 0.0
        return float(self.time[-1] - self.time[0])

    @property
    def sample_rate(self) -> float:
        """Median sampling rate in Hz (robust against single dropped packets)."""
        if self.n_samples < 2:
            return 0.0
        dt = np.median(np.diff(self.time[: min(self.n_samples, 100_000)]))
        return 1.0 / float(dt) if dt > 0 else 0.0


def supported_extensions() -> tuple[str, ...]:
    return (".csv", ".parquet")


def load_file(path: str, run_id: int = 0) -> Run:
    """Load a javascope log file into a Run. Raises LoaderError on failure."""
    extension = os.path.splitext(path)[1].lower()
    if extension == ".csv":
        table = _read_csv(path)
    elif extension == ".parquet":
        table = _read_parquet(path)
    else:
        raise LoaderError(
            f"Unsupported file type '{extension}' for '{path}'. "
            f"Supported: {', '.join(supported_extensions())}"
        )
    return _table_to_run(table, path, run_id)


def _read_csv(path: str):
    try:
        import pyarrow.csv as pacsv
    except ImportError:
        # e.g. web/pyodide builds without pyarrow
        return _read_csv_python(path)

    try:
        return pacsv.read_csv(
            path,
            parse_options=pacsv.ParseOptions(delimiter=CSV_SEPARATOR),
            convert_options=pacsv.ConvertOptions(strings_can_be_null=True),
        )
    except Exception as exc:
        raise LoaderError(f"Failed to read CSV '{path}': {exc}") from exc


def _read_csv_python(path: str):
    """Slow but dependency-free CSV reader returning a pyarrow-table-like shim."""
    import csv

    try:
        with open(path, newline="") as f:
            reader = csv.reader(f, delimiter=CSV_SEPARATOR)
            header = next(reader, None)
            if header is None:
                raise LoaderError(f"'{os.path.basename(path)}' is empty.")
            rows = [row for row in reader if row]
    except LoaderError:
        raise
    except Exception as exc:
        raise LoaderError(f"Failed to read CSV '{path}': {exc}") from exc

    columns = []
    for index, name in enumerate(header):
        cells = [row[index] if index < len(row) else "" for row in rows]
        columns.append((name, cells))
    return _PythonTable(columns)


class _PythonTable:
    """Minimal stand-in for a pyarrow.Table used by the pure-python CSV path."""

    def __init__(self, columns: list[tuple[str, list[str]]]):
        self._columns = dict(columns)
        self.column_names = [name for name, _ in columns]
        self.num_rows = len(columns[0][1]) if columns else 0

    def column(self, name: str) -> "_PythonColumn":
        return _PythonColumn(self._columns[name])


class _PythonColumn:
    def __init__(self, cells: list[str]):
        self._cells = cells

    def __len__(self) -> int:
        return len(self._cells)

    @property
    def null_count(self) -> int:
        return sum(1 for cell in self._cells if not cell.strip())

    def to_float_array(self) -> np.ndarray | None:
        try:
            return np.array(
                [float(cell) if cell.strip() else np.nan for cell in self._cells],
                dtype=np.float64,
            )
        except ValueError:
            return None


def _read_parquet(path: str):
    import pyarrow.parquet as papq

    try:
        return papq.read_table(path)
    except Exception as exc:
        raise LoaderError(f"Failed to read parquet '{path}': {exc}") from exc


def _table_to_run(table, path: str, run_id: int) -> Run:
    if table.num_rows == 0:
        raise LoaderError(f"'{os.path.basename(path)}' does not contain any rows.")

    warnings: list[str] = []
    signals: dict[str, np.ndarray] = {}
    time_array: np.ndarray | None = None

    for column_name in table.column_names:
        clean_name = column_name.strip()
        column = table.column(column_name)

        # The javascope writer terminates every line with ';', which yields a
        # trailing unnamed, all-null column. Skip those silently.
        if not clean_name and column.null_count == len(column):
            continue

        array = _to_float_array(column)
        if array is None:
            if clean_name:
                warnings.append(f"Skipped non-numeric column '{clean_name}'.")
            continue

        if clean_name == TIME_COLUMN:
            time_array = array
        else:
            signals[clean_name] = array

    if not signals and time_array is None:
        raise LoaderError(
            f"'{os.path.basename(path)}' does not contain any numeric columns."
        )

    has_real_time = time_array is not None
    if time_array is None:
        n = table.num_rows
        time_array = np.arange(n, dtype=np.float64)
        warnings.append(
            f"No '{TIME_COLUMN}' column found - using the sample index as x-axis."
        )

    return Run(
        run_id=run_id,
        name=os.path.basename(path),
        path=path,
        time=time_array,
        signals=signals,
        has_real_time=has_real_time,
        warnings=warnings,
    )


def _to_float_array(column) -> np.ndarray | None:
    """Convert a pyarrow column to a float64 numpy array, or None if not numeric."""
    if isinstance(column, _PythonColumn):
        return column.to_float_array()

    import pyarrow as pa
    import pyarrow.compute as pacompute

    if not (
        pa.types.is_floating(column.type)
        or pa.types.is_integer(column.type)
        or pa.types.is_boolean(column.type)
    ):
        try:
            column = pacompute.cast(column, pa.float64())
        except Exception:
            return None

    if column.null_count:
        column = pacompute.fill_null(column, np.nan)

    array = column.to_numpy(zero_copy_only=False)
    return np.ascontiguousarray(array, dtype=np.float64)
