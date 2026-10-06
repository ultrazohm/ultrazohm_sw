"""Trigger engine: edge detection and windowed capture on the live stream.

Runs on the reader thread (fed one parsed block at a time); the UI polls
:attr:`AcquisitionEngine.capture`.  All positions are absolute int64 sample
indices — the ring wraps, indices don't.

Edge detection is the JavaScope's three-point test, vectorized (rising:
``y[k-2] < level <= y[k-1] <= level <= y[k]``  spelled exactly as
``y[k] >= level and y[k-1] <= level and y[k-2] < level``), with the last two
samples carried across block boundaries so no edge is lost between packets.

Capture: with window ``W`` and pretrigger fraction ``p``, a trigger at index
``T`` freezes ``[T - pre, T - pre + W)`` where ``pre = round(p * (W - 1))``.
Arming is gated until the stream has produced ``pre`` samples, and the window
is copied out of the ring as soon as its last sample arrives — the ring is
big enough that the tail cannot be overwritten first (enforced at arm time).
"""

from __future__ import annotations

import threading
from dataclasses import dataclass

import numpy as np

from .ring import ChannelRing

# States
IDLE = "idle"                # not armed
WAIT_PRETRIGGER = "filling"  # armed, waiting for `pre` samples of history
ARMED = "armed"              # hunting for an edge
TRIGGERED = "triggered"      # edge found, waiting for the window tail
STOPPED = "stopped"          # single-shot done


@dataclass
class Capture:
    data: np.ndarray        # (C, W) float32
    start_index: int        # absolute index of data[:, 0]
    trigger_index: int      # absolute index of the trigger sample
    sequence: int           # increments per capture (UI change detection)
    column_names: tuple[str, ...] | None = None


class AcquisitionEngine:
    def __init__(
        self,
        ring: ChannelRing,
        *,
        channel: int,
        edge: str = "rising",
        level: float = 0.0,
        pretrigger: float = 0.5,
        window: int = 1000,
        mode: str = "auto",
        auto_timeout: int | None = None,
        column_names: tuple[str, ...] | None = None,
    ) -> None:
        if edge not in ("rising", "falling"):
            raise ValueError(f"edge must be rising/falling, got {edge!r}")
        if mode not in ("auto", "normal", "single"):
            raise ValueError(f"mode must be auto/normal/single, got {mode!r}")
        if not 0.0 <= pretrigger <= 1.0:
            raise ValueError("pretrigger must be in [0, 1]")
        if window < 2:
            raise ValueError("window must be >= 2 samples")
        if window > ring.capacity:
            raise ValueError(
                f"window ({window}) exceeds ring capacity ({ring.capacity})"
            )
        self.ring = ring
        self.channel = channel
        self.edge = edge
        self.level = float(level)
        self.window = int(window)
        self.pre = int(round(pretrigger * (window - 1)))
        self.mode = mode
        # auto mode: the display falls back to rolling when the newest capture
        # is older than this many samples (the engine itself only ever
        # captures on real edges — JavaScope parity).
        self.auto_timeout = auto_timeout if auto_timeout else 2 * window
        self.column_names = column_names
        self.state = IDLE
        self.capture: Capture | None = None
        self._trigger_index: int | None = None
        self._carry = np.empty(0, dtype=np.float32)
        self._carry_start = 0
        self._armed_at = 0
        self._sequence = 0
        self._lock = threading.Lock()

    # --- control (UI thread) ---------------------------------------------

    def arm(self) -> None:
        with self._lock:
            self.state = WAIT_PRETRIGGER
            self._trigger_index = None
            self._carry = np.empty(0, dtype=np.float32)
            self._armed_at = self.ring.total_written

    def disarm(self) -> None:
        with self._lock:
            self.state = IDLE
            self._trigger_index = None

    def capture_is_stale(self) -> bool:
        """Auto mode only: the newest capture is older than ``auto_timeout``.

        The plot uses this to fall back to the rolling display when the edge
        source went quiet (classic scope auto behavior); normal/single hold
        their last capture indefinitely.
        """
        cap = self.capture
        if cap is None or self.mode != "auto":
            return False
        age = self.ring.total_written - (cap.start_index + cap.data.shape[1])
        return age > self.auto_timeout

    # --- ingest (reader thread) -------------------------------------------

    def on_block(self, values: np.ndarray, start_index: int) -> None:
        """Feed the trigger channel's samples of one parsed block."""
        with self._lock:
            if self.state in (IDLE, STOPPED):
                return
            if self.state == WAIT_PRETRIGGER:
                if self.ring.total_written - self._armed_at >= self.pre or (
                    self.ring.total_written >= self.pre
                ):
                    self.state = ARMED
                    self._armed_at = start_index
                else:
                    return
            if self.state == ARMED:
                trig = self._detect(values, start_index)
                if trig is not None:
                    self._trigger_index = trig
                    self.state = TRIGGERED
            if self.state == TRIGGERED:
                self._try_capture()

    def _detect(self, values: np.ndarray, start_index: int) -> int | None:
        y = np.concatenate([self._carry, values]) if self._carry.size else values
        first_abs = start_index - self._carry.size
        # Carry from the *combined* stream: with a 1-sample block, values[-2:]
        # would drop the older boundary sample and lose edges.
        self._carry = y[-2:].copy()
        if y.size < 3:
            return None
        lvl = self.level
        if self.edge == "rising":
            hits = (y[2:] >= lvl) & (y[1:-1] <= lvl) & (y[:-2] < lvl)
        else:
            hits = (y[2:] <= lvl) & (y[1:-1] >= lvl) & (y[:-2] > lvl)
        pos = np.flatnonzero(hits)
        for k in pos:
            trig = first_abs + int(k) + 2
            if trig - self.pre >= 0:  # need full pretrigger history
                return trig
        return None

    def _try_capture(self) -> None:
        trig = self._trigger_index
        assert trig is not None
        start = trig - self.pre
        if self.ring.total_written < start + self.window:
            return  # window tail not produced yet; try again next block
        data, got_start = self.ring.snapshot_range(start, self.window)
        self._sequence += 1
        self.capture = Capture(data, got_start, trig, self._sequence, self.column_names)
        self._trigger_index = None
        if self.mode == "single":
            self.state = STOPPED
        else:
            self.state = ARMED
            self._armed_at = start + self.window
