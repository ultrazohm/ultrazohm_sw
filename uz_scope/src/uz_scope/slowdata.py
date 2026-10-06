"""SlowData store: latest value per JS_SlowData entry, typed via the header.

One slowdata value arrives per sample, round-robin over the enum; the raw u32
is reinterpreted as float32 iff the enum name contains ``FLOAT_``.  Updated on
the reader thread (a few dozen distinct ids, tiny), read by the UI.
"""

from __future__ import annotations

import numpy as np

from .protocol import decode_slow_value


class SlowDataStore:
    def __init__(self, names: list[str]) -> None:
        self.names = list(names)
        self.values: dict[int, float | int] = {}
        self.updates = 0

    def rename(self, names: list[str]) -> None:
        self.names = list(names)
        self.values.clear()

    def name(self, slow_id: int) -> str:
        if 0 <= slow_id < len(self.names):
            return self.names[slow_id]
        return f"slowdata_{slow_id}"

    def on_block(self, slow_id: np.ndarray, slow_raw: np.ndarray) -> None:
        """Feed one parsed block: ``(k, N)`` ids and raw payload words."""
        ids = slow_id.reshape(-1)
        raw = slow_raw.reshape(-1)
        for uid in np.unique(ids):
            if uid < 0:
                continue
            last = int(np.flatnonzero(ids == uid)[-1])
            self.values[int(uid)] = decode_slow_value(
                self.name(int(uid)), int(raw[last])
            )
        self.updates += 1

    def get(self, slow_id: int, default=None):
        return self.values.get(slow_id, default)

    def get_by_name(self, name: str, default=None):
        try:
            return self.values.get(self.names.index(name), default)
        except ValueError:
            return default

    def items(self) -> list[tuple[int, str, float | int]]:
        return [(i, self.name(i), v) for i, v in sorted(self.values.items())]
