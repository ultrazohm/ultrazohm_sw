#!/usr/bin/env python3
"""Round-trip tests for convert_binary_export_to_parquet.

These tests fabricate a binary blob that matches the on-disk format written by
``export_array_of_struct_to_binary`` in ``test/helper/export_struct_to_csv.c``,
run the converter, and assert that the Parquet output preserves values, dtypes,
and metadata. This exercises the real decode path without needing the C build.
"""

from __future__ import annotations

import struct
import sys
from pathlib import Path

import numpy as np
import pyarrow.parquet as pq
import pytest

sys.path.insert(0, str(Path(__file__).resolve().parent))

import convert_binary_export_to_parquet as converter  # noqa: E402


# type_id -> struct pack format, mirroring csv_field_type_t / TYPE_TO_DTYPE.
_TYPE_PACK = {
    0: "<f",  # CSV_FIELD_FLOAT
    1: "<d",  # CSV_FIELD_DOUBLE
    2: "<I",  # CSV_FIELD_UINT32
    3: "<i",  # CSV_FIELD_INT32
    4: "<H",  # CSV_FIELD_UINT16
    5: "<h",  # CSV_FIELD_INT16
    6: "<B",  # CSV_FIELD_UINT8
    7: "<b",  # CSV_FIELD_INT8
}


def _write_binary(path: Path, fields, *, sample_time: float = 0.0) -> None:
    """Write a binary export. ``fields`` is a list of (name, type_id, values)."""
    row_count = len(fields[0][2])
    assert all(len(values) == row_count for _, _, values in fields)
    has_time = sample_time != 0.0

    with path.open("wb") as file:
        file.write(converter.MAGIC)
        file.write(struct.pack("<I", converter.VERSION))
        file.write(struct.pack("<Q", row_count))
        file.write(struct.pack("<I", len(fields)))
        file.write(struct.pack("<B", 1 if has_time else 0))
        file.write(struct.pack("<d", sample_time))

        for name, type_id, _ in fields:
            encoded = name.encode("utf-8")
            file.write(struct.pack("<B", type_id))
            file.write(struct.pack("<H", len(encoded)))
            file.write(encoded)

        for row_index in range(row_count):
            if has_time:
                file.write(struct.pack("<d", row_index * sample_time))
            for _, type_id, values in fields:
                file.write(struct.pack(_TYPE_PACK[type_id], values[row_index]))


def test_round_trip_mixed_types_with_time(tmp_path):
    bin_path = tmp_path / "export.bin"
    parquet_path = tmp_path / "export.parquet"
    fields = [
        ("i_d_A", 0, [1.5, -2.25, 0.0]),         # float
        ("speed_rpm", 1, [1000.0, -500.0, 0.0]),  # double
        ("machine_id", 2, [1, 2, 4294967295]),    # uint32
        ("counter", 3, [-1, 0, 2147483647]),      # int32
        ("flags", 5, [-32768, 0, 32767]),         # int16
        ("byte", 7, [-128, 0, 127]),              # int8
    ]
    _write_binary(bin_path, fields, sample_time=0.25)

    converter.convert_binary_to_parquet(bin_path, parquet_path, compression="zstd")

    table = pq.read_table(parquet_path)
    assert table.num_rows == 3
    # time column is injected first because has_time is set.
    assert table.column_names == ["time"] + [name for name, _, _ in fields]
    np.testing.assert_allclose(table.column("time").to_numpy(), [0.0, 0.25, 0.5])
    np.testing.assert_allclose(table.column("i_d_A").to_numpy(), [1.5, -2.25, 0.0])
    assert table.column("machine_id").to_pylist() == [1, 2, 4294967295]
    assert table.column("byte").to_pylist() == [-128, 0, 127]

    metadata = table.schema.metadata
    assert metadata[b"uz_binary_export_version"] == b"1"
    assert metadata[b"uz_binary_export_has_time"] == b"True"
    assert metadata[b"uz_binary_export_sample_time"] == b"0.25"


def test_round_trip_without_time(tmp_path):
    bin_path = tmp_path / "config.bin"
    parquet_path = tmp_path / "config.parquet"
    fields = [("v_dc_V", 0, [48.0]), ("pole_pairs", 6, [4])]
    _write_binary(bin_path, fields, sample_time=0.0)

    converter.convert_binary_to_parquet(bin_path, parquet_path, compression=None)

    table = pq.read_table(parquet_path)
    assert table.column_names == ["v_dc_V", "pole_pairs"]
    assert table.num_rows == 1
    assert table.schema.metadata[b"uz_binary_export_has_time"] == b"False"


def test_duplicate_field_names_are_deduplicated(tmp_path):
    bin_path = tmp_path / "dup.bin"
    parquet_path = tmp_path / "dup.parquet"
    fields = [("i_q_A", 0, [1.0]), ("i_q_A", 0, [2.0])]
    _write_binary(bin_path, fields)

    converter.convert_binary_to_parquet(bin_path, parquet_path, compression=None)

    table = pq.read_table(parquet_path)
    assert table.column_names == ["i_q_A", "i_q_A_1"]


def test_rejects_bad_magic(tmp_path):
    bin_path = tmp_path / "bad_magic.bin"
    bin_path.write_bytes(b"NOTUZBIN" + b"\x00" * 32)
    with pytest.raises(ValueError, match="magic"):
        converter.convert_binary_to_parquet(bin_path, tmp_path / "out.parquet", compression=None)


def test_rejects_unsupported_version(tmp_path):
    bin_path = tmp_path / "bad_version.bin"
    with bin_path.open("wb") as file:
        file.write(converter.MAGIC)
        file.write(struct.pack("<I", 999))
    with pytest.raises(ValueError, match="version"):
        converter.convert_binary_to_parquet(bin_path, tmp_path / "out.parquet", compression=None)


if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__, "-q"]))
