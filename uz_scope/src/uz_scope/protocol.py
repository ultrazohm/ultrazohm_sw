"""Wire protocol of the UltraZohm JavaScope TCP stream (GUI-free).

The device (APU, FreeRTOS/lwIP, ``vitis/software/FreeRTOS/sw/ethernet.c``)
streams fixed-size frames with **no framing header**, little-endian.  With
``C`` scope channels and ``N`` samples per packet, one frame is::

    uint32  status              # state-machine / LED / MyButton / ext-log bits
    uint32  slow_raw[N]         # slowdata payload bits, one round-robin value per sample
    float32 ch[C][N]            # channel-major fast-sample block
    float32 slow_id[N]          # JS_SlowData enum index of each slow_raw entry (as float)

Frame size = ``4 * (1 + (C + 2) * N)`` bytes — 1324 bytes at C=20, N=15.

The uplink command is 8 bytes: ``<uint32 id><float32 value>`` (little-endian).
Command ids come from ``enum gui_button_mapping`` in
``vitis/software/Baremetal/src/include/javascope.h``; channel selection uses
the hardcoded id range ``CHANNEL_SELECT_BASE + slot`` with the observable enum
index as the value (see ``ipc_ARM.c`` cases 201..220).

A slowdata value is reinterpreted as float32 iff its ``JS_SlowData`` enum name
contains ``FLOAT_``; otherwise it is an unsigned integer.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass

import numpy as np

# --- status word bits (see docs/source/guide/gui/javascope.rst) ---
STATUS_BIT_READY = 0
STATUS_BIT_RUNNING = 1
STATUS_BIT_ERROR = 2
STATUS_BIT_USER = 3
STATUS_BIT_MYBUTTON_BASE = 4  # bits 4..11 -> MyButton 1..8 indicators
STATUS_BIT_EXT_LOG = 12       # rising edge starts, falling edge stops an armed log

# Channel-select command ids are hardcoded in the firmware (ipc_ARM.c) and the
# JavaScope (SendController.java): slot k (0-based) -> id CHANNEL_SELECT_BASE + k.
CHANNEL_SELECT_BASE = 201

ZERO_ACK_ID = 0

_COMMAND = struct.Struct("<If")
_U32 = struct.Struct("<I")
_F32 = struct.Struct("<f")


@dataclass(frozen=True)
class FrameGeometry:
    """Frame layout parameters. Not on the wire — must match the firmware."""

    channels: int = 20
    samples_per_packet: int = 15

    def __post_init__(self) -> None:
        if self.channels < 1:
            raise ValueError(f"channels must be >= 1, got {self.channels}")
        if self.samples_per_packet < 1:
            raise ValueError(
                f"samples_per_packet must be >= 1, got {self.samples_per_packet}"
            )

    @property
    def words(self) -> int:
        return 1 + (self.channels + 2) * self.samples_per_packet

    @property
    def frame_bytes(self) -> int:
        return 4 * self.words


@dataclass(frozen=True)
class ParsedFrames:
    """Vectorized view of ``k`` consecutive frames.

    ``status``, ``slow_raw`` and ``samples`` are zero-copy views into the
    buffer passed to :func:`parse_frames` — copy them out before reusing the
    receive buffer.  ``samples`` has shape ``(k, channels, samples_per_packet)``.
    """

    status: np.ndarray     # (k,)   uint32
    slow_raw: np.ndarray   # (k, N) uint32
    samples: np.ndarray    # (k, C, N) float32
    slow_id: np.ndarray    # (k, N) int32 (decoded from the on-wire float)

    @property
    def count(self) -> int:
        return int(self.status.shape[0])


def complete_frames(nbytes: int, geometry: FrameGeometry) -> tuple[int, int]:
    """Return ``(k, remainder)``: complete frames in ``nbytes`` and leftover bytes."""
    return divmod(nbytes, geometry.frame_bytes)


def parse_frames(buf, geometry: FrameGeometry) -> ParsedFrames:
    """Parse a buffer holding a whole number of frames. Zero per-value Python loops.

    ``buf`` may be ``bytes``, ``bytearray`` or ``memoryview``; its length must
    be a non-zero multiple of ``geometry.frame_bytes``.
    """
    nbytes = len(buf)
    k, rem = complete_frames(nbytes, geometry)
    if rem or k == 0:
        raise ValueError(
            f"buffer of {nbytes} bytes is not a non-zero multiple of the "
            f"{geometry.frame_bytes}-byte frame size"
        )
    words = geometry.words
    n = geometry.samples_per_packet
    c = geometry.channels

    u = np.frombuffer(buf, dtype="<u4").reshape(k, words)
    f = np.frombuffer(buf, dtype="<f4").reshape(k, words)

    status = u[:, 0]
    slow_raw = u[:, 1 : 1 + n]
    samples = f[:, 1 + n : 1 + n + c * n].reshape(k, c, n)
    with np.errstate(invalid="ignore"):
        # Garbage/NaN slow ids (possible on geometry mismatch) must not warn
        # on the hot path; they surface via range checks downstream.
        slow_id = f[:, 1 + n + c * n :].astype(np.int32)
    return ParsedFrames(status=status, slow_raw=slow_raw, samples=samples, slow_id=slow_id)


def encode_command(cmd_id: int, value: float = 0.0) -> bytes:
    """Encode one 8-byte uplink command ``<uint32 id><float32 value>``."""
    if not 0 <= cmd_id < 2**32:
        raise ValueError(f"command id out of uint32 range: {cmd_id}")
    return _COMMAND.pack(cmd_id, float(value))


def decode_command(data: bytes) -> tuple[int, float]:
    """Inverse of :func:`encode_command` (used by tests and bench tooling)."""
    cmd_id, value = _COMMAND.unpack(data)
    return cmd_id, value


def encode_channel_select(slot: int, observable_index: int) -> bytes:
    """Select observable ``observable_index`` for scope channel ``slot`` (0-based)."""
    if slot < 0:
        raise ValueError(f"slot must be >= 0, got {slot}")
    return encode_command(CHANNEL_SELECT_BASE + slot, float(observable_index))


ZERO_ACK = _COMMAND.pack(ZERO_ACK_ID, 0.0)


def slow_is_float(name: str) -> bool:
    """A slowdata value is float32 iff its enum name contains ``FLOAT_``."""
    return "FLOAT_" in name


def decode_slow_value(name: str, raw: int) -> float | int:
    """Decode one raw slowdata word according to its ``JS_SlowData`` name."""
    if slow_is_float(name):
        return _F32.unpack(_U32.pack(raw & 0xFFFFFFFF))[0]
    return int(raw)


def status_bit(status: int, bit: int) -> bool:
    return bool((int(status) >> bit) & 1)


def mybutton_indicator(status: int, button: int) -> bool:
    """Indicator state of MyButton ``button`` (1-based, 1..8)."""
    if not 1 <= button <= 8:
        raise ValueError(f"MyButton index must be 1..8, got {button}")
    return status_bit(status, STATUS_BIT_MYBUTTON_BASE + button - 1)
