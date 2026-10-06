from __future__ import annotations

import struct

import numpy as np

from uz_scope2.slowdata import SlowDataStore

NAMES = ["JSSD_ZEROVALUE", "JSSD_FLOAT_Seconds", "JSSD_Counter", "JSSD_FLOAT_Error_Code"]


def float_bits(value: float) -> int:
    return struct.unpack("<I", struct.pack("<f", value))[0]


def test_typed_decode_and_latest_value():
    store = SlowDataStore(NAMES)
    ids = np.array([[1, 2, 1]], dtype=np.int32)
    raw = np.array([[float_bits(1.5), 42, float_bits(2.5)]], dtype=np.uint32)
    store.on_block(ids, raw)
    assert store.get(1) == 2.5  # latest of the two id-1 samples, decoded as float
    assert store.get(2) == 42   # non-FLOAT name -> integer
    assert isinstance(store.get(2), int)
    assert store.get_by_name("JSSD_FLOAT_Seconds") == 2.5
    assert store.get(3) is None


def test_items_and_unknown_id():
    store = SlowDataStore(NAMES)
    store.on_block(
        np.array([[3, 9]], dtype=np.int32),
        np.array([[float_bits(-7.0), 123]], dtype=np.uint32),
    )
    items = dict((i, v) for i, _, v in store.items())
    assert items[3] == -7.0
    # Unknown id 9 has no name -> falls back to integer decode, still stored.
    assert items[9] == 123
    assert store.name(9) == "slowdata_9"


def test_rename_resets():
    store = SlowDataStore(NAMES)
    store.on_block(np.array([[1]], dtype=np.int32), np.array([[1]], dtype=np.uint32))
    store.rename(["A", "B"])
    assert store.values == {}
