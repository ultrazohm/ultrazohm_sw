"""Observable acquisition and bounded segment history for the live scope."""

from __future__ import annotations

import threading
from dataclasses import dataclass

import numpy as np

ZERO_OBSERVABLE = 0


@dataclass
class SignalSegment:
    """One uninterrupted observable-to-hardware-slot mapping."""

    id: int
    slot: int
    observable: int
    name: str
    start: int
    stop: int | None = None
    scale: float = 1.0
    offset: float = 0.0
    color: str | None = None

    @property
    def active(self) -> bool:
        return self.stop is None

    @property
    def token(self) -> str:
        return f"signal_{self.id}"


class SegmentRegistry:
    """Tracks current acquisitions and archived mappings until ring eviction."""

    def __init__(self, channels: int) -> None:
        self.channels = channels
        self._segments: dict[int, SignalSegment] = {}
        self._active_by_slot: dict[int, int] = {}
        self._next_id = 1
        self._lock = threading.RLock()

    def start(
        self,
        slot: int,
        observable: int,
        name: str,
        start: int,
        *,
        scale: float = 1.0,
        offset: float = 0.0,
        color: str | None = None,
    ) -> SignalSegment | None:
        with self._lock:
            self.close(slot, start)
            if observable == ZERO_OBSERVABLE:
                return None
            sid = self._next_id
            self._next_id += 1
            segment = SignalSegment(
                sid, slot, observable, name, int(start), None,
                float(scale), float(offset), color,
            )
            self._segments[sid] = segment
            self._active_by_slot[slot] = sid
            return segment

    def close(self, slot: int, stop: int) -> None:
        with self._lock:
            sid = self._active_by_slot.pop(slot, None)
            if sid is not None and sid in self._segments:
                seg = self._segments[sid]
                seg.stop = max(seg.start, int(stop))

    def close_all(self, stop: int) -> None:
        with self._lock:
            for slot in list(self._active_by_slot):
                self.close(slot, stop)

    def get(self, segment_id: int) -> SignalSegment | None:
        with self._lock:
            return self._segments.get(int(segment_id))

    def active_for_slot(self, slot: int) -> SignalSegment | None:
        with self._lock:
            sid = self._active_by_slot.get(slot)
            return self._segments.get(sid) if sid is not None else None

    def active(self) -> list[SignalSegment]:
        with self._lock:
            return [
                self._segments[sid]
                for _, sid in sorted(self._active_by_slot.items())
            ]

    def retained(self, ring) -> list[SignalSegment]:
        oldest = ring.total_written - ring.filled
        with self._lock:
            expired = [
                sid for sid, seg in self._segments.items()
                if seg.stop is not None and seg.stop <= oldest
            ]
            for sid in expired:
                self._segments.pop(sid, None)
            return sorted(self._segments.values(), key=lambda seg: seg.id)

    def update_style(
        self,
        slot: int,
        *,
        scale: float | None = None,
        offset: float | None = None,
        color: str | None = None,
    ) -> None:
        with self._lock:
            seg = self.active_for_slot(slot)
            if seg is None:
                return
            if scale is not None:
                seg.scale = float(scale)
            if offset is not None:
                seg.offset = float(offset)
            if color is not None:
                seg.color = color

    def clear(self) -> None:
        with self._lock:
            self._segments.clear()
            self._active_by_slot.clear()

    def query(
        self,
        history,
        ring,
        segment_id: int,
        start: int,
        stop: int,
        n_out: int,
        dt: float,
    ) -> tuple[np.ndarray, np.ndarray]:
        """Return a range without crossing a remap boundary or ring eviction."""
        seg = self.get(segment_id)
        if seg is None:
            return np.empty(0, np.float64), np.empty(0, np.float64)
        end = ring.total_written if seg.stop is None else seg.stop
        oldest = ring.total_written - ring.filled
        lo = max(int(start), seg.start, oldest)
        hi = min(int(stop), end, ring.total_written)
        if hi <= lo:
            return np.empty(0, np.float64), np.empty(0, np.float64)

        pyramid = history.pyramid
        if (
            pyramid is not None
            and history.first_index is not None
            and hi - lo > max(4 * n_out, pyramid.base * 4)
        ):
            xs, ys = pyramid.query(
                seg.slot,
                lo - history.first_index,
                hi - history.first_index,
                n_out,
                dt,
            )
            return xs + history.first_index * dt, ys.astype(np.float64)

        from uz_dataviewer.downsample import decimate_range

        data, got = ring.snapshot_range(lo, hi - lo, [seg.slot])
        if data.shape[1] == 0:
            return np.empty(0, np.float64), np.empty(0, np.float64)
        time_axis = (got + np.arange(data.shape[1], dtype=np.float64)) * dt
        xs, ys = decimate_range(time_axis, data[0], None, n_out, 0, data.shape[1])
        return np.asarray(xs, np.float64), np.asarray(ys, np.float64)

