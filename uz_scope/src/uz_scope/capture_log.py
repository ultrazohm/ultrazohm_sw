"""Streaming capture logger: Parquet (default), CSV, or raw-binary spill.

The reader thread calls :meth:`CaptureLogger.submit` with each parsed block;
encoding and disk I/O happen on the logger's own thread behind a bounded
queue, so a slow disk can never stall ingest — the logger drops whole chunks
instead and reports it (``stats.chunks_dropped``).

Formats:

- ``parquet`` — ``pyarrow.parquet.ParquetWriter``, LZ4, float64 ``time`` +
  float32 channel columns.  Directly openable in uz_dataviewer.
- ``csv`` — same schema through ``pyarrow.csv.CSVWriter`` (C++ formatting).
  Openable in uz_dataviewer / Excel / MATLAB.  Text encoding costs ~4x the
  bytes of Parquet — fine at 20 ch x 10 kHz, expect drops near the
  200 ch x 100 kHz design target; use parquet or bin there.
- ``bin`` — raw sample-major float32 + a JSON sidecar, the guaranteed-rate
  fallback; convert to Parquet afterwards with :func:`convert_bin`.

Time is reconstructed from absolute int64 sample indices times the configured
timestep — never stored as float32 (precision), never trusted from the wire
(the protocol carries no clock).
"""

from __future__ import annotations

import json
import queue
import threading
import time as _time
from dataclasses import dataclass, field
from pathlib import Path

import numpy as np
import pyarrow as pa
import pyarrow.csv as pa_csv
import pyarrow.parquet as pq

FORMATS = ("parquet", "csv", "bin")

# Rows buffered before a Parquet row group is flushed (~2 MB/channel-100 at f32).
PARQUET_ROWGROUP_ROWS = 262_144


def make_column_names(observable_names: list[str]) -> list[str]:
    """Column names for the logged channels: strip the ``JSO_`` prefix, dedup.

    Duplicate selections (the same observable on two scope slots) get a
    ``_chN`` suffix so Parquet/CSV columns stay unique.
    """
    names: list[str] = []
    seen: set[str] = set()
    for slot, raw in enumerate(observable_names):
        name = raw.removeprefix("JSO_") or f"ch{slot + 1}"
        if name in seen:
            name = f"{name}_ch{slot + 1}"
        seen.add(name)
        names.append(name)
    return names


@dataclass
class LoggerStats:
    rows_written: int = 0
    chunks_dropped: int = 0
    samples_dropped: int = 0
    bytes_written: int = 0  # bin only (other writers own the file handle)


@dataclass
class _Chunk:
    samples: np.ndarray  # (C, m) float32, already strided
    indices: np.ndarray  # (m,) int64 absolute sample indices


class CaptureLogger:
    """One log file per instance; create a new instance per start."""

    def __init__(
        self,
        directory: str | Path,
        fmt: str,
        column_names: list[str],
        timestep_s: float,
        *,
        every_n: int = 1,
        base_name: str | None = None,
        queue_chunks: int = 256,
        autostart: bool = True,
    ) -> None:
        if fmt not in FORMATS:
            raise ValueError(f"format must be one of {FORMATS}, got {fmt!r}")
        if every_n < 1:
            raise ValueError(f"every_n must be >= 1, got {every_n}")
        if timestep_s <= 0:
            raise ValueError(f"timestep_s must be > 0, got {timestep_s}")
        self.fmt = fmt
        self.column_names = list(column_names)
        self.timestep_s = float(timestep_s)
        self.every_n = every_n
        self.stats = LoggerStats()
        self.directory = Path(directory)
        self.directory.mkdir(parents=True, exist_ok=True)
        if base_name is None:
            base_name = "Scope_" + _time.strftime("%Y-%m-%d_%H-%M-%S")
        self.path = self.directory / f"{base_name}.{fmt}"
        suffix = 1
        while self.path.exists():  # e.g. two logs within the same second
            self.path = self.directory / f"{base_name}_{suffix}.{fmt}"
            suffix += 1
        self._queue: queue.Queue[_Chunk | None] = queue.Queue(maxsize=queue_chunks)
        self._thread = threading.Thread(
            target=self._run, name="uz_scope-logger", daemon=True
        )
        self._first_index: int | None = None
        self._closed = False
        self._inline = False
        self._error: str | None = None
        if autostart:
            self._thread.start()

    # --- producer side (reader thread) -----------------------------------

    def submit(self, samples: np.ndarray, start_index: int) -> None:
        """Enqueue a channel-major ``(C, m)`` block starting at ``start_index``.

        Never blocks: drops the chunk (and counts it) when the writer is
        behind.  ``samples`` must already be a private copy.
        """
        if self._closed:
            return
        c, m = samples.shape
        if c != len(self.column_names):
            raise ValueError(
                f"expected {len(self.column_names)} channels, got {c}"
            )
        indices = np.arange(start_index, start_index + m, dtype=np.int64)
        if self.every_n > 1:
            mask = indices % self.every_n == 0
            samples = samples[:, mask]
            indices = indices[mask]
            if indices.size == 0:
                return
        try:
            self._queue.put_nowait(_Chunk(samples, indices))
        except queue.Full:
            self.stats.chunks_dropped += 1
            self.stats.samples_dropped += int(indices.size)

    def close(self) -> Path:
        """Flush, close the file, and return its path."""
        if not self._closed:
            self._closed = True
            if not self._thread.is_alive() and not self._thread.ident:
                self._drain_inline()
            else:
                self._queue.put(None)
                self._thread.join()
        if self._error:
            raise RuntimeError(f"logger failed: {self._error}")
        return self.path

    @property
    def error(self) -> str | None:
        return self._error

    # --- writer thread ----------------------------------------------------

    def _drain_inline(self) -> None:
        """autostart=False path (tests): process the queue synchronously.

        No sentinel — the queue may already be full; _iter_chunks stops on
        empty instead.
        """
        self._inline = True
        self._run()

    def _run(self) -> None:
        try:
            if self.fmt == "parquet":
                self._run_parquet()
            elif self.fmt == "csv":
                self._run_csv()
            else:
                self._run_bin()
        except Exception as exc:  # surfaced via close()
            self._error = f"{type(exc).__name__}: {exc}"
            # Keep draining so close() never hangs on a full queue.
            try:
                while self._queue.get(timeout=0.5) is not None:
                    pass
            except queue.Empty:
                pass

    def _iter_chunks(self):
        """Yield chunks, or ``None`` as a ~0.5 s idle tick (worker mode) so
        writers can do time-based flushing while the stream is quiet."""
        while True:
            if self._inline:
                try:
                    chunk = self._queue.get_nowait()
                except queue.Empty:
                    return
            else:
                try:
                    chunk = self._queue.get(timeout=0.5)
                except queue.Empty:
                    yield None
                    continue
            if chunk is None:
                return
            if self._first_index is None:
                self._first_index = int(chunk.indices[0])
            yield chunk

    def _chunk_table(self, chunk: _Chunk, schema: pa.Schema) -> pa.Table:
        arrays = [pa.array(chunk.indices * self.timestep_s, type=pa.float64())]
        arrays += [pa.array(row, type=pa.float32()) for row in chunk.samples]
        return pa.Table.from_arrays(arrays, schema=schema)

    def _schema(self) -> pa.Schema:
        return pa.schema(
            [pa.field("time", pa.float64())]
            + [pa.field(name, pa.float32()) for name in self.column_names]
        )

    def _run_parquet(self) -> None:
        schema = self._schema()
        writer = pq.ParquetWriter(self.path, schema, compression="lz4")
        pending: list[pa.Table] = []
        pending_rows = 0
        last_write = _time.monotonic()

        def flush() -> None:
            nonlocal pending, pending_rows, last_write
            if pending:
                writer.write_table(pa.concat_tables(pending))
                pending, pending_rows = [], 0
            last_write = _time.monotonic()

        try:
            for chunk in self._iter_chunks():
                if chunk is not None:
                    pending.append(self._chunk_table(chunk, schema))
                    pending_rows += chunk.indices.size
                    # Live feedback: count rows when accepted, not only per
                    # 262k-row group — at low rates the panel would show
                    # "0 rows" (and a 0-byte file) for minutes otherwise.
                    self.stats.rows_written += int(chunk.indices.size)
                if pending_rows >= PARQUET_ROWGROUP_ROWS or (
                    pending and _time.monotonic() - last_write >= 5.0
                ):
                    flush()
            flush()
        finally:
            writer.close()

    def _run_csv(self) -> None:
        schema = self._schema()
        with pa_csv.CSVWriter(str(self.path), schema) as writer:
            for chunk in self._iter_chunks():
                if chunk is None:
                    continue
                writer.write_table(self._chunk_table(chunk, schema))
                self.stats.rows_written += int(chunk.indices.size)

    def _run_bin(self) -> None:
        with open(self.path, "wb") as f:
            for chunk in self._iter_chunks():
                if chunk is None:
                    f.flush()
                    continue
                # Sample-major (m, C): the file is a flat row matrix.
                data = np.ascontiguousarray(chunk.samples.T)
                f.write(data)
                self.stats.rows_written += int(chunk.indices.size)
                self.stats.bytes_written += data.nbytes
        sidecar = {
            "format": "uz_scope-bin-v1",
            "columns": self.column_names,
            "dtype": "<f4",
            "timestep_s": self.timestep_s,
            "every_n": self.every_n,
            "first_index": self._first_index or 0,
            "rows": self.stats.rows_written,
            "chunks_dropped": self.stats.chunks_dropped,
            "samples_dropped": self.stats.samples_dropped,
        }
        self.path.with_suffix(".json").write_text(
            json.dumps(sidecar, indent=2) + "\n", encoding="utf-8"
        )


def write_capture(
    path: str | Path,
    columns: list[str],
    data: np.ndarray,
    start_index: int,
    timestep_s: float,
) -> Path:
    """One-shot write of a ``(C, W)`` trigger capture; format by extension."""
    path = Path(path)
    c, w = data.shape
    if c != len(columns):
        raise ValueError(f"expected {len(columns)} channels, got {c}")
    time_col = (start_index + np.arange(w, dtype=np.int64)) * timestep_s
    schema = pa.schema(
        [pa.field("time", pa.float64())]
        + [pa.field(name, pa.float32()) for name in columns]
    )
    arrays = [pa.array(time_col, type=pa.float64())] + [
        pa.array(row, type=pa.float32()) for row in data
    ]
    table = pa.Table.from_arrays(arrays, schema=schema)
    if path.suffix.lower() == ".csv":
        pa_csv.write_csv(table, str(path))
    else:
        if path.suffix.lower() != ".parquet":
            path = path.with_suffix(".parquet")
        pq.write_table(table, path, compression="lz4")
    return path


def convert_bin(bin_path: str | Path, dst: str | Path | None = None) -> Path:
    """Convert a bin spill (+ JSON sidecar) to Parquet; returns the new path.

    Time is reconstructed as ``(first_index + k * every_n) * timestep_s`` — if
    chunks were dropped during logging the sidecar says so and the time axis
    is only piecewise correct; the drop counters are the authority.
    """
    bin_path = Path(bin_path)
    meta = json.loads(bin_path.with_suffix(".json").read_text(encoding="utf-8"))
    columns = meta["columns"]
    c = len(columns)
    dst = Path(dst) if dst is not None else bin_path.with_suffix(".parquet")

    schema = pa.schema(
        [pa.field("time", pa.float64())]
        + [pa.field(name, pa.float32()) for name in columns]
    )
    if bin_path.stat().st_size == 0:
        pq.write_table(schema.empty_table(), dst, compression="lz4")
        return dst
    data = np.memmap(bin_path, dtype="<f4", mode="r").reshape(-1, c)
    writer = pq.ParquetWriter(dst, schema, compression="lz4")
    try:
        step = PARQUET_ROWGROUP_ROWS
        for row0 in range(0, data.shape[0], step):
            block = np.asarray(data[row0 : row0 + step])
            k = np.arange(row0, row0 + block.shape[0], dtype=np.int64)
            t = (meta["first_index"] + k * meta["every_n"]) * meta["timestep_s"]
            arrays = [pa.array(t, type=pa.float64())] + [
                pa.array(block[:, i], type=pa.float32()) for i in range(c)
            ]
            writer.write_table(pa.Table.from_arrays(arrays, schema=schema))
    finally:
        writer.close()
    return dst
