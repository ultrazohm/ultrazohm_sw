#!/usr/bin/env python3
"""Convert UltraZohm Ceedling binary exports to Parquet.

The binary format is produced by ``export_array_of_struct_to_binary`` and
``export_input_output_arrays_to_binary`` in ``test/helper/export_struct_to_csv.c``.
It is a flat little-endian dump with a self-describing header so that no field
layout has to be hard-coded on the Python side.

On-disk layout (all multi-byte integers little-endian)::

    Header
      char     magic[8]        = "UZBIN001"
      uint32   version         = 1
      uint64   row_count       number of rows that follow
      uint32   field_count     number of value fields (excludes the time column)
      uint8    has_time        1 if each row is prefixed with a float64 time value
      float64  sample_time     seconds between rows (0 if has_time == 0)

    Field descriptors (repeated field_count times, in column order)
      uint8    type_id         see TYPE_TO_DTYPE below
      uint16   name_length     length of name in bytes (UTF-8, no terminator)
      char     name[name_length]

    Rows (repeated row_count times)
      float64  time            present only if has_time == 1
      <value>  field_0 .. field_{field_count-1}   packed per its type_id

Values are written with native struct alignment removed (each field is written
with its exact width and no padding), so the row stride equals the sum of the
field widths plus 8 bytes when ``has_time`` is set.
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path

import numpy as np
import pyarrow as pa
import pyarrow.parquet as pq


MAGIC = b"UZBIN001"
VERSION = 1

TYPE_TO_DTYPE = {
    0: "<f4",  # CSV_FIELD_FLOAT
    1: "<f8",  # CSV_FIELD_DOUBLE
    2: "<u4",  # CSV_FIELD_UINT32
    3: "<i4",  # CSV_FIELD_INT32
    4: "<u2",  # CSV_FIELD_UINT16
    5: "<i2",  # CSV_FIELD_INT16
    6: "u1",   # CSV_FIELD_UINT8
    7: "i1",   # CSV_FIELD_INT8
}


def read_exact(file, size: int) -> bytes:
    data = file.read(size)
    if len(data) != size:
        raise ValueError("Unexpected end of binary export")
    return data


def unique_name(name: str, used_names: set[str]) -> str:
    if name not in used_names:
        used_names.add(name)
        return name

    suffix = 1
    while f"{name}_{suffix}" in used_names:
        suffix += 1
    unique = f"{name}_{suffix}"
    used_names.add(unique)
    return unique


def read_header(file):
    magic = read_exact(file, len(MAGIC))
    if magic != MAGIC:
        raise ValueError(f"Unsupported binary export magic: {magic!r}")

    version = struct.unpack("<I", read_exact(file, 4))[0]
    if version != VERSION:
        raise ValueError(f"Unsupported binary export version: {version}")

    row_count = struct.unpack("<Q", read_exact(file, 8))[0]
    field_count = struct.unpack("<I", read_exact(file, 4))[0]
    has_time = struct.unpack("<B", read_exact(file, 1))[0] != 0
    sample_time = struct.unpack("<d", read_exact(file, 8))[0]

    fields = []
    used_names: set[str] = set()
    if has_time:
        fields.append(("time", "<f8"))
        used_names.add("time")

    for _ in range(field_count):
        type_id = struct.unpack("<B", read_exact(file, 1))[0]
        name_length = struct.unpack("<H", read_exact(file, 2))[0]
        raw_name = read_exact(file, name_length).decode("utf-8")
        if type_id not in TYPE_TO_DTYPE:
            raise ValueError(f"Unsupported field type id: {type_id}")
        fields.append((unique_name(raw_name, used_names), TYPE_TO_DTYPE[type_id]))

    return row_count, has_time, sample_time, fields


def convert_binary_to_parquet(input_path: Path, output_path: Path, compression: str) -> None:
    with input_path.open("rb") as file:
        row_count, has_time, sample_time, fields = read_header(file)
        dtype = np.dtype(fields)
        data = np.fromfile(file, dtype=dtype, count=row_count)

    if data.shape[0] != row_count:
        raise ValueError(f"Expected {row_count} rows, got {data.shape[0]}")

    table = pa.Table.from_pydict({name: pa.array(data[name]) for name in data.dtype.names})
    table = table.replace_schema_metadata(
        {
            b"uz_binary_export_version": str(VERSION).encode("ascii"),
            b"uz_binary_export_has_time": str(has_time).encode("ascii"),
            b"uz_binary_export_sample_time": repr(sample_time).encode("ascii"),
        }
    )
    pq.write_table(table, output_path, compression=compression)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path, help="Input .bin file from export_array_of_struct_to_binary")
    parser.add_argument("output", nargs="?", type=Path, help="Output .parquet file, defaults to input with .parquet suffix")
    parser.add_argument("--compression", default="zstd", help="Parquet compression codec, e.g. zstd, snappy, none")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    input_path = args.input
    output_path = args.output if args.output is not None else input_path.with_suffix(".parquet")
    compression = None if args.compression == "none" else args.compression
    convert_binary_to_parquet(input_path, output_path, compression)
    print(f"Wrote {output_path}")


if __name__ == "__main__":
    main()
