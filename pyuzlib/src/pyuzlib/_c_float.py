"""Conversion checks for the embedded target's IEEE-754 binary32 floats."""

import math
import struct


FLOAT32_MAX = float.fromhex("0x1.fffffep+127")


def as_c_float(value: float) -> float:
    """Round to binary32, rejecting overflow and nonzero values lost to underflow."""
    if not math.isfinite(value):
        raise ValueError(f"Cannot represent non-finite value {value!r} as C float")
    if abs(value) > FLOAT32_MAX:
        raise ValueError(f"Value {value!r} is out of range for C float")
    converted = struct.unpack("!f", struct.pack("!f", value))[0]
    if value != 0.0 and converted == 0.0:
        raise ValueError(f"Value {value!r} underflows to zero as C float")
    return converted
