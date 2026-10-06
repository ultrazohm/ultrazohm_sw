from __future__ import annotations

import numpy as np
import pytest

from uz_scope2.acquisition import (
    ARMED,
    AcquisitionEngine,
    STOPPED,
    TRIGGERED,
    WAIT_PRETRIGGER,
)
from uz_scope2.ring import ChannelRing


def feed(engine: AcquisitionEngine, ring: ChannelRing, values, block=7):
    """Push a 1-channel stream through ring + engine in `block`-sized chunks."""
    values = np.asarray(values, dtype=np.float32)
    for i in range(0, len(values), block):
        chunk = values[i : i + block]
        start = ring.total_written
        ring.append(chunk[None, :])
        engine.on_block(chunk, start)


def step_signal(n0: int, n1: int) -> np.ndarray:
    """0.0 for n0 samples, then 1.0 for n1 samples (one rising edge at n0)."""
    return np.concatenate([np.zeros(n0), np.ones(n1)]).astype(np.float32)


def test_rising_edge_exact_index():
    ring = ChannelRing(1, 1000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=0.0,
        window=10, mode="single",
    )
    eng.arm()
    feed(eng, ring, step_signal(50, 50))
    assert eng.state == STOPPED
    cap = eng.capture
    assert cap is not None
    # Three-point detector: first sample at/above level with two below before it.
    assert cap.trigger_index == 50
    assert cap.start_index == 50
    np.testing.assert_array_equal(cap.data[0], np.ones(10, dtype=np.float32))


def test_falling_edge():
    ring = ChannelRing(1, 1000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="falling", level=0.5, pretrigger=0.0,
        window=4, mode="single",
    )
    eng.arm()
    feed(eng, ring, 1.0 - step_signal(30, 30))
    assert eng.capture is not None
    assert eng.capture.trigger_index == 30


def test_edge_across_block_boundary():
    ring = ChannelRing(1, 1000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=0.0,
        window=4, mode="single",
    )
    eng.arm()
    # Block size 7, edge at sample 21 -> exactly at a block boundary; the
    # carried two samples must bridge it.
    feed(eng, ring, step_signal(21, 21), block=7)
    assert eng.capture is not None
    assert eng.capture.trigger_index == 21


def test_edge_detected_with_single_sample_blocks():
    # Regression: the carry must come from the combined stream, otherwise
    # 1-sample blocks lose one boundary sample and the edge is never seen.
    ring = ChannelRing(1, 1000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=0.0,
        window=4, mode="single",
    )
    eng.arm()
    feed(eng, ring, step_signal(10, 10), block=1)
    assert eng.capture is not None
    assert eng.capture.trigger_index == 10


def test_pretrigger_window_content():
    ring = ChannelRing(1, 1000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=0.5,
        window=11, mode="single",
    )
    eng.arm()
    feed(eng, ring, step_signal(100, 100))
    cap = eng.capture
    assert cap is not None
    assert cap.trigger_index == 100
    # pre = round(0.5 * 10) = 5 -> window [95, 106)
    assert cap.start_index == 95
    np.testing.assert_array_equal(
        cap.data[0], np.concatenate([np.zeros(5), np.ones(6)]).astype(np.float32)
    )


def test_trigger_before_pretrigger_history_is_skipped():
    ring = ChannelRing(1, 1000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=1.0,
        window=50, mode="single",  # needs 49 samples of history
    )
    eng.arm()
    # Edge at sample 10: too early for a full pretrigger, must NOT fire.
    feed(eng, ring, step_signal(10, 20))
    assert eng.capture is None
    assert eng.state in (ARMED, WAIT_PRETRIGGER, TRIGGERED)


def test_normal_mode_rearms():
    ring = ChannelRing(1, 10_000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=0.0,
        window=5, mode="normal",
    )
    eng.arm()
    pulse = np.concatenate([np.zeros(20), np.ones(20)])
    feed(eng, ring, np.tile(pulse, 3).astype(np.float32))
    cap = eng.capture
    assert cap is not None
    assert cap.sequence >= 2  # captured more than once
    assert eng.state == ARMED
    assert cap.trigger_index in (60, 100)  # a later pulse, not the first


def test_auto_mode_no_fake_captures_without_edges():
    # Auto mode hunts real edges only; a flat signal never produces a capture
    # (the plot keeps rolling instead — JavaScope parity).
    ring = ChannelRing(1, 10_000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=0.0,
        window=10, mode="auto", auto_timeout=50,
    )
    eng.arm()
    feed(eng, ring, np.zeros(200, dtype=np.float32))  # dead-flat signal
    assert eng.capture is None
    assert eng.state == ARMED
    assert not eng.capture_is_stale()  # no capture -> nothing to be stale


def test_auto_mode_capture_goes_stale_when_edges_stop():
    ring = ChannelRing(1, 10_000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=0.0,
        window=10, mode="auto", auto_timeout=50,
    )
    eng.arm()
    feed(eng, ring, step_signal(20, 30))  # one edge -> capture
    assert eng.capture is not None
    assert not eng.capture_is_stale()
    feed(eng, ring, np.ones(100, dtype=np.float32))  # edge source goes quiet
    assert eng.capture_is_stale()
    # normal mode never reports stale
    eng.mode = "normal"
    assert not eng.capture_is_stale()


def test_single_mode_stops_and_disarm():
    ring = ChannelRing(1, 1000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=0.5, pretrigger=0.0,
        window=5, mode="single",
    )
    eng.arm()
    feed(eng, ring, step_signal(20, 100))
    assert eng.state == STOPPED
    seq = eng.capture.sequence
    feed(eng, ring, step_signal(20, 100))  # further edges ignored
    assert eng.capture.sequence == seq
    eng.disarm()
    assert eng.state == "idle"


def test_window_larger_than_ring_rejected():
    ring = ChannelRing(1, 100)
    with pytest.raises(ValueError):
        AcquisitionEngine(ring, channel=0, window=200)


def test_level_crossing_slow_ramp():
    ring = ChannelRing(1, 1000)
    eng = AcquisitionEngine(
        ring, channel=0, edge="rising", level=5.0, pretrigger=0.0,
        window=4, mode="single",
    )
    eng.arm()
    ramp = np.arange(0, 20, 0.5, dtype=np.float32)  # crosses 5.0 at sample 10
    feed(eng, ring, ramp)
    assert eng.capture is not None
    # y[10] = 5.0 >= lvl, y[9] = 4.5 <= lvl, y[8] = 4.0 < lvl -> index 10
    assert eng.capture.trigger_index == 10
