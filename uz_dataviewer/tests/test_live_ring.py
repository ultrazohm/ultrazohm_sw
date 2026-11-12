"""LiveRing: bounded O(page) appends with immutable published snapshots."""
import numpy as np
import polars as pl
import pytest

from uz_dataviewer.live import LiveRing, LiveSource, cursor_invalid


def page(start, stop):
    return pl.DataFrame({'time': np.arange(start, stop, dtype=np.float64),
                         'status': np.zeros(stop - start, np.uint32),
                         'a': np.arange(start, stop, dtype=np.float32)})


def test_ring_keeps_exactly_capacity_across_compactions():
    ring = LiveRing(10)
    for start in range(0, 100, 3):
        ring.append(page(start, start + 3))
        snap = ring.snapshot()
        expected = np.arange(max(0, start + 3 - 10), start + 3)
        np.testing.assert_array_equal(snap['time'], expected)
        np.testing.assert_array_equal(snap['a'], expected.astype(np.float32))
        assert snap['status'].dtype == np.uint32


def test_snapshots_are_never_modified_by_later_appends():
    ring = LiveRing(10)
    ring.append(page(0, 8))
    frozen = ring.snapshot()
    copy = {k: v.copy() for k, v in frozen.items()}
    for start in range(8, 200, 7):
        ring.append(page(start, start + 7))
    for name in frozen:
        np.testing.assert_array_equal(frozen[name], copy[name])


def test_large_page_and_reset_and_column_change():
    ring = LiveRing(5)
    assert ring.snapshot() is None
    ring.append(page(0, 12))
    np.testing.assert_array_equal(ring.snapshot()['time'], np.arange(7, 12))
    ring.append(page(12, 12))
    assert len(ring.snapshot()['time']) == 5
    ring.append(page(12, 14).rename({'a': 'b'}))
    snap = ring.snapshot()
    assert set(snap) == {'time', 'status', 'b'}
    np.testing.assert_array_equal(snap['time'], [12, 13])
    ring.reset()
    assert ring.snapshot() is None


def test_live_source_accepts_ring_snapshot():
    ring = LiveRing(100)
    ring.append(page(0, 50))
    source = LiveSource(ring.snapshot())
    assert source.metadata.channels == ('a',)
    assert source.metadata.rows == 50


def coded(code):
    error = RuntimeError('service error')
    error.code = code
    return error


@pytest.mark.parametrize('error, expected', [
    (coded('cursor_expired'), True),
    (coded('canceled_by_stop'), False),
    (coded(None), False),
    (RuntimeError('cursor expired, but uncoded'), False),
    (OSError('Connection refused'), False),
])
def test_only_cursor_errors_trigger_resynchronization(error, expected):
    assert cursor_invalid(error) is expected
