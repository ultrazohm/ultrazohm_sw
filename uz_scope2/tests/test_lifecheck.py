from __future__ import annotations

import numpy as np

from uz_scope2.lifecheck import Lifecheck


def counters(*values):
    return np.array(values, dtype=np.float32)


def test_continuous_stream_no_gaps():
    lc = Lifecheck()
    lc.update(counters(0, 1, 2, 3))
    lc.update(counters(4, 5, 6))
    assert lc.gaps == 0
    assert lc.missing == 0
    assert lc.checked == 7


def test_gap_within_block():
    lc = Lifecheck()
    lc.update(counters(0, 1, 5, 6))
    assert lc.gaps == 1
    assert lc.missing == 3


def test_gap_across_blocks():
    lc = Lifecheck()
    lc.update(counters(0, 1))
    lc.update(counters(4, 5))
    assert lc.gaps == 1
    assert lc.missing == 2


def test_wraparound_is_not_a_gap():
    lc = Lifecheck(modulo=1000)
    lc.update(counters(997, 998, 999))
    lc.update(counters(0, 1))
    assert lc.gaps == 0


def test_firmware_wrap_at_1000_is_default():
    # Regression: javascope.c sends `interrupt_counter % 1000`; a clean
    # stream over several wraps must report zero gaps with the DEFAULT
    # monitor (a 2**24 default counted ~16.7M "missing" per wrap).
    lc = Lifecheck()
    stream = (np.arange(5000, dtype=np.int64) % 1000).astype(np.float32)
    for i in range(0, 5000, 30):
        lc.update(stream[i : i + 30])
    assert lc.gaps == 0
    assert lc.missing == 0
    assert lc.checked == 5000


def test_real_gap_still_detected_across_wrap():
    lc = Lifecheck()
    lc.update(counters(996, 997, 998))
    lc.update(counters(3, 4))  # dropped 999, 0, 1, 2
    assert lc.gaps == 1
    assert lc.missing == 4


def test_reset():
    lc = Lifecheck()
    lc.update(counters(0, 5))
    assert lc.gaps == 1
    lc.reset()
    lc.update(counters(100, 101))
    assert lc.gaps == 0
    assert lc.checked == 2
