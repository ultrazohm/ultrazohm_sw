"""Preallocated channel-major ring buffer for the live sample stream.

Layout is ``(channels, capacity)`` float32 — one contiguous row per channel, so
both the hot append (strided memcpy) and per-channel display snapshots are
cache-friendly.  Time is never stored: the absolute int64 sample counter
``total_written`` converts to seconds only at the display/logging edges
(float32 would lose sample precision within minutes at 100 kHz).
"""

from __future__ import annotations

import threading

import numpy as np


class ChannelRing:
    def __init__(self, channels: int, capacity: int) -> None:
        if channels < 1 or capacity < 1:
            raise ValueError("channels and capacity must be >= 1")
        self.channels = channels
        self.capacity = capacity
        self.data = np.zeros((channels, capacity), dtype=np.float32)
        self.total_written = 0  # absolute sample count since start (int)
        self._lock = threading.Lock()

    @property
    def filled(self) -> int:
        return min(self.total_written, self.capacity)

    def append_frames(self, samples: np.ndarray) -> None:
        """Append a parsed block of shape ``(k, channels, n)`` (frame-major)."""
        k, c, n = samples.shape
        if c != self.channels:
            raise ValueError(f"expected {self.channels} channels, got {c}")
        # (k, C, N) -> (C, k*N); the reshape after transpose makes the one
        # contiguous copy this path is budgeted for.
        self.append(samples.transpose(1, 0, 2).reshape(c, k * n))

    def append(self, block: np.ndarray) -> None:
        """Append a channel-major block of shape ``(channels, m)``."""
        c, m = block.shape
        if c != self.channels:
            raise ValueError(f"expected {self.channels} channels, got {c}")
        if m > self.capacity:
            # Only the last `capacity` samples can survive anyway.
            block = block[:, m - self.capacity :]
            skipped = m - self.capacity
            m = self.capacity
        else:
            skipped = 0
        with self._lock:
            pos = (self.total_written + skipped) % self.capacity
            first = min(m, self.capacity - pos)
            self.data[:, pos : pos + first] = block[:, :first]
            if m > first:
                self.data[:, : m - first] = block[:, first:]
            self.total_written += m + skipped

    def snapshot(
        self, count: int, channels: list[int] | np.ndarray | None = None
    ) -> tuple[np.ndarray, int]:
        """Copy out the newest ``count`` samples (fewer if not filled yet).

        Returns ``(data, start_index)`` where ``data`` has shape
        ``(len(channels), count)`` in chronological order and ``start_index``
        is the absolute sample index of ``data[:, 0]``.
        """
        with self._lock:
            avail = self.filled
            count = min(count, avail)
            start = self.total_written - count
            return self._copy_out(start, count, channels), start

    def snapshot_range(
        self, start: int, count: int, channels: list[int] | np.ndarray | None = None
    ) -> tuple[np.ndarray, int]:
        """Copy out ``count`` samples beginning at absolute index ``start``.

        The range is clipped to what the ring still holds; the returned start
        index tells the caller how much was clipped away.
        """
        with self._lock:
            oldest = self.total_written - self.filled
            end = min(start + count, self.total_written)
            start = max(start, oldest)
            count = max(0, end - start)
            return self._copy_out(start, count, channels), start

    def _copy_out(self, start: int, count: int, channels) -> np.ndarray:
        """Copy ``count`` samples from absolute ``start`` (lock held).

        Copies row by row so a channel subset never fancy-indexes (and thereby
        copies) entire capacity-length rows — only the requested window.
        """
        rows = range(self.channels) if channels is None else list(channels)
        out = np.empty((len(rows), count), dtype=np.float32)
        if count == 0:
            return out
        pos = start % self.capacity
        first = min(count, self.capacity - pos)
        for i, ch in enumerate(rows):
            row = self.data[ch]
            out[i, :first] = row[pos : pos + first]
            if count > first:
                out[i, first:] = row[: count - first]
        return out


def ring_capacity(
    channels: int, sample_rate: float, ring_seconds: float, max_ring_bytes: int
) -> int:
    """Samples per channel for the configured history, clamped to the byte cap."""
    wanted = max(1, int(round(ring_seconds * sample_rate)))
    cap_by_bytes = max(1, max_ring_bytes // (4 * channels))
    return min(wanted, cap_by_bytes)
