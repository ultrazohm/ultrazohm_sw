from __future__ import annotations

import struct

import numpy as np
import pytest

from uz_scope import protocol
from uz_scope.protocol import (
    CHANNEL_SELECT_BASE,
    FrameGeometry,
    ZERO_ACK,
    complete_frames,
    decode_command,
    decode_slow_value,
    encode_channel_select,
    encode_command,
    mybutton_indicator,
    parse_frames,
    slow_is_float,
    status_bit,
)


def build_frame(status, slow_raw, channels, slow_id):
    """Golden-path frame builder: independent of the parser under test."""
    n = len(slow_raw)
    buf = struct.pack("<I", status)
    buf += struct.pack(f"<{n}I", *slow_raw)
    for ch in channels:
        assert len(ch) == n
        buf += struct.pack(f"<{n}f", *ch)
    buf += struct.pack(f"<{n}f", *[float(i) for i in slow_id])
    return buf


def test_geometry_sizes():
    assert FrameGeometry(20, 15).frame_bytes == 1324  # the current firmware frame
    assert FrameGeometry(200, 15).frame_bytes == 12124  # the 200-channel target
    assert FrameGeometry(2, 3).words == 13


def test_geometry_validation():
    with pytest.raises(ValueError):
        FrameGeometry(0, 15)
    with pytest.raises(ValueError):
        FrameGeometry(20, 0)


def test_parse_single_frame_exact_values():
    geom = FrameGeometry(channels=2, samples_per_packet=3)
    status = (1 << 0) | (1 << 12)
    slow_raw = [struct.unpack("<I", struct.pack("<f", 2.5))[0], 5, 7]
    ch1 = [1.5, -2.5, 3.25]
    ch2 = [10.0, 20.0, 30.0]
    slow_id = [1, 2, 0]
    buf = build_frame(status, slow_raw, [ch1, ch2], slow_id)
    assert len(buf) == geom.frame_bytes

    parsed = parse_frames(buf, geom)
    assert parsed.count == 1
    assert int(parsed.status[0]) == status
    assert parsed.slow_raw.tolist() == [slow_raw]
    assert parsed.samples.shape == (1, 2, 3)
    np.testing.assert_array_equal(parsed.samples[0, 0], np.float32(ch1))
    np.testing.assert_array_equal(parsed.samples[0, 1], np.float32(ch2))
    assert parsed.slow_id.tolist() == [slow_id]
    assert parsed.samples.dtype == np.float32
    assert parsed.status.dtype == np.uint32


def test_parse_multiple_frames():
    geom = FrameGeometry(channels=2, samples_per_packet=2)
    f1 = build_frame(1, [11, 12], [[1.0, 2.0], [3.0, 4.0]], [1, 2])
    f2 = build_frame(2, [21, 22], [[5.0, 6.0], [7.0, 8.0]], [3, 4])
    parsed = parse_frames(f1 + f2, geom)
    assert parsed.count == 2
    assert parsed.status.tolist() == [1, 2]
    np.testing.assert_array_equal(
        parsed.samples[1], np.float32([[5.0, 6.0], [7.0, 8.0]])
    )


def test_parse_default_geometry_frame():
    geom = FrameGeometry()  # 20 x 15
    rng = np.random.default_rng(42)
    channels = rng.standard_normal((20, 15)).astype(np.float32)
    buf = build_frame(0xABCD, list(range(15)), channels.tolist(), list(range(15)))
    assert len(buf) == 1324
    parsed = parse_frames(buf, geom)
    np.testing.assert_array_equal(parsed.samples[0], channels)


def test_parse_rejects_partial_buffer():
    geom = FrameGeometry(2, 3)
    with pytest.raises(ValueError):
        parse_frames(b"\x00" * (geom.frame_bytes + 4), geom)
    with pytest.raises(ValueError):
        parse_frames(b"", geom)


def test_complete_frames():
    geom = FrameGeometry()  # 1324 bytes
    assert complete_frames(2 * 1324 + 100, geom) == (2, 100)
    assert complete_frames(1323, geom) == (0, 1323)


def test_parse_accepts_memoryview_of_bytearray():
    geom = FrameGeometry(2, 2)
    frame = build_frame(3, [1, 2], [[1.0, 2.0], [3.0, 4.0]], [0, 1])
    buf = bytearray(frame + b"\xff" * 10)  # recv buffer with a partial tail
    parsed = parse_frames(memoryview(buf)[: geom.frame_bytes], geom)
    assert int(parsed.status[0]) == 3


def test_encode_command_roundtrip():
    data = encode_command(32, 0.0)  # Error_Reset
    assert len(data) == 8
    assert data == struct.pack("<If", 32, 0.0)
    assert decode_command(data) == (32, 0.0)


def test_zero_ack():
    assert ZERO_ACK == b"\x00" * 8
    assert decode_command(ZERO_ACK) == (0, 0.0)


def test_channel_select_encoding():
    # Slot 0 -> id 201, value = observable enum index as float (SendController.java).
    assert decode_command(encode_channel_select(0, 46)) == (201, 46.0)
    assert decode_command(encode_channel_select(19, 3)) == (220, 3.0)
    assert CHANNEL_SELECT_BASE == 201
    with pytest.raises(ValueError):
        encode_channel_select(-1, 0)


def test_slow_value_decode():
    bits = struct.unpack("<I", struct.pack("<f", -12.75))[0]
    assert decode_slow_value("JSSD_FLOAT_Error_Code", bits) == pytest.approx(-12.75)
    value = decode_slow_value("JSSD_Counter", 7)
    assert value == 7 and isinstance(value, int)
    assert slow_is_float("JSSD_FLOAT_Milliseconds")
    assert not slow_is_float("JSSD_ZEROVALUE")


def test_status_bits():
    status = (1 << 0) | (1 << 2) | (1 << 4) | (1 << 11) | (1 << 12)
    assert status_bit(status, protocol.STATUS_BIT_READY)
    assert not status_bit(status, protocol.STATUS_BIT_RUNNING)
    assert status_bit(status, protocol.STATUS_BIT_ERROR)
    assert status_bit(status, protocol.STATUS_BIT_EXT_LOG)
    assert mybutton_indicator(status, 1)
    assert mybutton_indicator(status, 8)
    assert not mybutton_indicator(status, 2)
    with pytest.raises(ValueError):
        mybutton_indicator(status, 9)
