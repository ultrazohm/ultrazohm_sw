from __future__ import annotations

import numpy as np
import pytest

from uz_scope.ring import ChannelRing, ring_capacity


def naive_history(blocks, capacity):
    all_data = np.concatenate(blocks, axis=1)
    return all_data[:, -capacity:] if all_data.shape[1] > capacity else all_data


def test_append_and_snapshot_no_wrap():
    ring = ChannelRing(2, 10)
    block = np.arange(8, dtype=np.float32).reshape(2, 4)
    ring.append(block)
    data, start = ring.snapshot(4)
    assert start == 0
    np.testing.assert_array_equal(data, block)
    assert ring.total_written == 4
    assert ring.filled == 4


def test_wraparound_matches_naive_reference():
    rng = np.random.default_rng(1)
    ring = ChannelRing(3, 7)
    blocks = []
    for size in (3, 5, 2, 6, 4, 7, 1):
        block = rng.standard_normal((3, size)).astype(np.float32)
        blocks.append(block)
        ring.append(block)
        expect = naive_history(blocks, 7)
        got, start = ring.snapshot(7)
        np.testing.assert_array_equal(got, expect)
        assert start == ring.total_written - expect.shape[1]


def test_append_frames_flattens_in_order():
    ring = ChannelRing(2, 100)
    # 3 frames, 2 channels, 4 samples each; values encode (frame, channel, sample)
    frames = np.zeros((3, 2, 4), dtype=np.float32)
    for k in range(3):
        for c in range(2):
            frames[k, c] = [k * 100 + c * 10 + s for s in range(4)]
    ring.append_frames(frames)
    data, _ = ring.snapshot(12)
    np.testing.assert_array_equal(
        data[0], [0, 1, 2, 3, 100, 101, 102, 103, 200, 201, 202, 203]
    )
    np.testing.assert_array_equal(
        data[1], [10, 11, 12, 13, 110, 111, 112, 113, 210, 211, 212, 213]
    )


def test_snapshot_subset_and_clamp():
    ring = ChannelRing(4, 8)
    ring.append(np.arange(12, dtype=np.float32).reshape(4, 3))
    data, start = ring.snapshot(10, channels=[2, 0])
    assert data.shape == (2, 3)  # clamped to what's filled
    assert start == 0
    np.testing.assert_array_equal(data[0], [6, 7, 8])
    np.testing.assert_array_equal(data[1], [0, 1, 2])


def test_block_larger_than_capacity():
    ring = ChannelRing(1, 5)
    ring.append(np.arange(12, dtype=np.float32).reshape(1, 12))
    assert ring.total_written == 12
    data, start = ring.snapshot(5)
    assert start == 7
    np.testing.assert_array_equal(data[0], [7, 8, 9, 10, 11])


def test_snapshot_range_clips_to_available():
    ring = ChannelRing(1, 5)
    ring.append(np.arange(9, dtype=np.float32).reshape(1, 9))  # holds samples 4..8
    data, start = ring.snapshot_range(2, 4)
    assert start == 4  # samples 2..3 already overwritten
    np.testing.assert_array_equal(data[0], [4, 5])
    data, start = ring.snapshot_range(6, 100)
    assert start == 6
    np.testing.assert_array_equal(data[0], [6, 7, 8])


def test_snapshot_subset_across_wrap():
    ring = ChannelRing(3, 5)
    ring.append(np.arange(24, dtype=np.float32).reshape(3, 8))  # wraps: holds 3..7
    data, start = ring.snapshot(5, channels=[2, 0])
    assert start == 3
    np.testing.assert_array_equal(data[0], [19, 20, 21, 22, 23])  # channel 2
    np.testing.assert_array_equal(data[1], [3, 4, 5, 6, 7])       # channel 0


def test_snapshot_range_subset_across_wrap():
    ring = ChannelRing(2, 4)
    ring.append(np.arange(12, dtype=np.float32).reshape(2, 6))  # holds 2..5
    data, start = ring.snapshot_range(3, 2, channels=[1])
    assert start == 3
    np.testing.assert_array_equal(data[0], [9, 10])


def test_empty_snapshot():
    ring = ChannelRing(2, 4)
    data, start = ring.snapshot(4)
    assert data.shape == (2, 0)
    assert start == 0


def test_channel_mismatch_raises():
    ring = ChannelRing(2, 4)
    with pytest.raises(ValueError):
        ring.append(np.zeros((3, 2), dtype=np.float32))


def test_ring_capacity_clamps_to_byte_budget():
    # 10 s x 100 kHz x 200 ch x 4 B = 800 MB > 512 MB cap
    cap = ring_capacity(200, 100_000.0, 10.0, 512 * 1024 * 1024)
    assert cap == (512 * 1024 * 1024) // (4 * 200)
    # small config fits untouched
    assert ring_capacity(20, 10_000.0, 10.0, 512 * 1024 * 1024) == 100_000
