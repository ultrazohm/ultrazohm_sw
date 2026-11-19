"""LiveRing: bounded O(page) appends with immutable published snapshots."""
import numpy as np
import polars as pl
import pytest

from ultrazohm_dataviewer.live import LiveRing, LiveSource, cursor_invalid


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


# -- incremental display summaries ------------------------------------------------
from ultrazohm_dataviewer.live import LIVE_BUCKET, bucket_size  # noqa: E402


def noisy_page(start, stop, rng, nan_rate=.002):
    values = rng.standard_normal(stop - start).astype(np.float32)
    values[rng.random(len(values)) < nan_rate] = np.nan
    values[rng.random(len(values)) < nan_rate / 2] = np.inf
    return pl.DataFrame({'time': np.arange(start, stop, dtype=np.float64) * 1e-3,
                         'status': np.zeros(stop - start, np.uint32), 'a': values})


def expected_bucket(y):
    finite = np.isfinite(y)
    if finite.any():
        low, high = y[finite].min(), y[finite].max()
        first_min = int(np.flatnonzero(finite & (y == low))[0])
        last_max = int(np.flatnonzero(finite & (y == high))[-1])
    else:
        first_min = last_max = -1
    gaps = np.flatnonzero(~finite)
    return first_min, last_max, int(gaps[0]) if len(gaps) else -1


def assert_summary_matches(snapshot):
    y = snapshot['a']
    offset, valid_end = snapshot.offset, snapshot.valid_end
    for level, arrays in enumerate(snapshot.summary['a']):
        size = bucket_size(level)
        first = -(-offset // size)
        for bucket in range(first, valid_end // size):
            lo = bucket * size - offset
            expected = expected_bucket(y[lo:lo + size])
            actual = tuple(int(v[bucket]) - offset if v[bucket] >= 0 else -1 for v in arrays)
            actual = tuple(a - lo if a >= 0 else -1 for a in actual)
            assert actual == expected, (level, bucket)


def test_bucket_summaries_match_brute_force_across_appends_and_compaction():
    rng = np.random.default_rng(3)
    ring = LiveRing(20_000)
    start = 0
    for _ in range(40):  # several compactions; pages straddle bucket edges
        size = int(rng.integers(1, 3_000))
        ring.append(noisy_page(start, start + size, rng))
        start += size
        assert_summary_matches(ring.snapshot())


def test_only_newly_completed_buckets_are_reduced(monkeypatch):
    """Small polls must not repeatedly reduce the same coarse partial buckets."""
    from ultrazohm_dataviewer import live
    reduced, merged = [], []
    extrema, merge = live.bucket_extrema, live.merge_extrema

    def track_extrema(y):
        reduced.append(len(y))
        return extrema(y)

    def track_merge(y, mins, maxs, gaps):
        merged.append(len(mins))
        return merge(y, mins, maxs, gaps)

    monkeypatch.setattr(live, 'bucket_extrema', track_extrema)
    monkeypatch.setattr(live, 'merge_extrema', track_merge)
    ring = LiveRing(100_000)
    # Cross boundaries at all three levels, but leave a partial bucket at each.
    stop = 9_009
    for start in range(0, stop, 33):
        ring.append(page(start, start + 33))
    assert sum(reduced) == stop // LIVE_BUCKET * LIVE_BUCKET
    assert all(n % LIVE_BUCKET == 0 for n in reduced)
    levels = len(ring.summary['a'])
    assert sum(merged) == sum(stop // bucket_size(k) * live.LIVE_FACTOR for k in range(1, levels))
    assert all(n % live.LIVE_FACTOR == 0 for n in merged)
    assert_summary_matches(ring.snapshot())
    # The unfinished tail still contributes its newest extreme to display.
    source = LiveSource(ring.snapshot())
    result = source.read_plot('a', 0., stop - 1, 16)
    assert result.values.max() == stop - 1


def test_frozen_snapshot_summaries_are_never_modified():
    rng = np.random.default_rng(4)
    ring = LiveRing(10_000)
    ring.append(noisy_page(0, 7_000, rng))
    frozen = ring.snapshot()
    # Only complete buckets inside the snapshot are ever read through it; later
    # appends may fill the shared arrays beyond its end.
    def used(snapshot):
        return [[values[:snapshot.valid_end // bucket_size(level)].copy() for values in arrays]
                for level, arrays in enumerate(snapshot.summary['a'])]
    copies = used(frozen)
    for start in range(7_000, 60_000, 1_111):
        ring.append(noisy_page(start, start + 1_111, rng))
    for level, saved in zip(used(frozen), copies):
        for values, copy in zip(level, saved):
            np.testing.assert_array_equal(values, copy)
    assert_summary_matches(frozen)


@pytest.mark.parametrize('budget', [64, 400, 2000])
def test_wide_window_from_buckets_keeps_extrema_gaps_and_samples(budget):
    rng = np.random.default_rng(5)
    ring = LiveRing(300_000)
    ring.append(noisy_page(0, 250_000, rng, nan_rate=1e-5))
    ring.append(noisy_page(250_000, 410_000, rng, nan_rate=1e-5))
    snapshot = ring.snapshot()
    source = LiveSource(snapshot)
    t, y = snapshot['time'], snapshot['a']
    for lo, hi in [(t[0], t[-1]), (t[1_000] + 1e-4, t[-5_000]), (t[77_777], t[290_000])]:
        a, b = source.bounds(lo, hi)
        assert (b - a) >= LIVE_BUCKET * (budget // 2), 'window must use the bucket path'
        assert source._candidates('a', a, b, budget) is not None
        data = source.read_plot('a', lo, hi, budget)
        window = y[a:b]
        finite = window[np.isfinite(window)]
        assert np.nanmax(data.values) == finite.max()
        assert np.nanmin(data.values) == finite.min()
        assert np.isnan(data.values).any() == (~np.isfinite(window)).any()
        assert len(data.time) <= budget + budget // 2 + 2
        assert np.all(np.diff(data.time) > 0)
        # Every displayed point is an original sample (non-finite shown as NaN gaps).
        rows = np.searchsorted(t, data.time)
        np.testing.assert_array_equal(t[rows], data.time)
        original = y[rows].astype(np.float64)
        original[~np.isfinite(original)] = np.nan
        np.testing.assert_array_equal(original, data.values)
        assert data.raw_count == b - a


def test_narrow_window_and_plain_frames_use_raw_samples():
    rng = np.random.default_rng(6)
    ring = LiveRing(50_000)
    ring.append(noisy_page(0, 50_000, rng))
    source = LiveSource(ring.snapshot())
    a, b = source.bounds(1., 2.)
    assert source._candidates('a', a, b, 2000) is None
    frame_source = LiveSource(noisy_page(0, 50_000, rng))
    assert frame_source._candidates('a', 0, 50_000, 64) is None
