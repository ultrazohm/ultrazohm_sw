"""Sample-continuity monitor.

Watches a monotonically incrementing counter channel (firmware:
``JSO_lifecheck``; bench server: channel 0) and counts discontinuities —
the ground truth for "did we drop anything" at any ingest rate.

The firmware wraps the counter at 1000 (``javascope.c``:
``lifecheck = uz_SystemTime_GetInterruptCounter() % 1000``), so the check
runs modulo the same value — a wrap 999 -> 0 is continuity, not a gap.
``missing`` is therefore only known modulo 1000, but any real drop that is
not an exact multiple of the modulo still shows up as a gap.
"""

from __future__ import annotations

import numpy as np

DEFAULT_MODULO = 1000  # must match the producer's wrap (javascope.c % 1000)


class Lifecheck:
    def __init__(self, modulo: int = DEFAULT_MODULO) -> None:
        self.modulo = modulo
        self.gaps = 0            # number of non-+1 steps observed
        self.missing = 0         # total samples skipped over
        self.checked = 0
        self._last: int | None = None

    def update(self, counters: np.ndarray) -> None:
        """Feed the counter values of one received block (chronological)."""
        if counters.size == 0:
            return
        v = np.rint(counters.astype(np.float64)).astype(np.int64)
        steps = np.diff(v) % self.modulo
        if self._last is not None:
            first = int((v[0] - self._last) % self.modulo)
            if first != 1:
                self.gaps += 1
                self.missing += (first - 1) % self.modulo
        bad = steps != 1
        self.gaps += int(np.count_nonzero(bad))
        self.missing += int(((steps[bad] - 1) % self.modulo).sum())
        self._last = int(v[-1])
        self.checked += int(v.size)

    def reset(self) -> None:
        self.gaps = 0
        self.missing = 0
        self.checked = 0
        self._last = None
