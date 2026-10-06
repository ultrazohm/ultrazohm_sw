"""Session history: incremental envelope pyramid + ring/pyramid stitching."""

from __future__ import annotations

import time

import numpy as np
import pytest

from uz_scope.config import HistorySettings
from uz_scope.history import LivePyramid, SessionHistory, _auto_base
from uz_scope.ring import ChannelRing

RNG = np.random.default_rng(42)


def make_block(channels: int, m: int) -> np.ndarray:
    return RNG.standard_normal((channels, m)).astype(np.float32)


def full_envelope(p: LivePyramid, channel: int, n_out: int = 10**9):
    return p.query(channel, 0, p.total, n_out, dt=1.0)


# --- LivePyramid -----------------------------------------------------------


def test_level0_matches_numpy_bucket_extremes():
    p = LivePyramid(channels=3, base=8)
    block = make_block(3, 8 * 40)
    p.append(block)
    ref = block.reshape(3, 40, 8)
    lvl = p.levels[0]
    assert lvl.count == 40
    np.testing.assert_array_equal(lvl.vmin[:, :40], ref.min(axis=2))
    np.testing.assert_array_equal(lvl.vmax[:, :40], ref.max(axis=2))


def test_chunked_append_equals_single_append():
    channels, base = 2, 16
    data = make_block(channels, 4321)
    whole = LivePyramid(channels, base=base)
    whole.append(data)
    chunked = LivePyramid(channels, base=base)
    pos = 0
    for size in (1, 15, 16, 17, 300, 4321 - 1 - 15 - 16 - 17 - 300):
        chunked.append(data[:, pos : pos + size])
        pos += size
    assert chunked.total == whole.total == 4321
    for ch in range(channels):
        xw, yw = full_envelope(whole, ch)
        xc, yc = full_envelope(chunked, ch)
        np.testing.assert_array_equal(xw, xc)
        np.testing.assert_array_equal(yw, yc)


def test_partial_bucket_running_minmax():
    p = LivePyramid(channels=1, base=10)
    p.append(make_block(1, 25))  # bucket 2 holds 5 samples so far
    tail = np.array([[100.0, -100.0, 0.0]], dtype=np.float32)
    p.append(tail)
    lvl = p.levels[0]
    assert p.total == 28 and lvl.count == 3
    assert lvl.vmax[0, 2] == 100.0
    assert lvl.vmin[0, 2] == -100.0


def test_global_extremes_survive_coarse_levels():
    p = LivePyramid(channels=1, base=4)
    data = make_block(1, 200_000)  # forces several cascade levels
    data[0, 123_456] = 50.0
    data[0, 3_333] = -50.0
    for pos in range(0, 200_000, 7777):
        p.append(data[:, pos : pos + 7777])
    assert len(p.levels) > 2
    _, ys = p.query(0, 0, p.total, n_out=64, dt=1.0)
    assert ys.max() == 50.0
    assert ys.min() == -50.0


def test_query_window_and_time_axis():
    p = LivePyramid(channels=1, base=10)
    data = np.arange(1000, dtype=np.float32).reshape(1, -1)
    p.append(data)
    xs, ys = p.query(0, 200, 400, n_out=10**9, dt=0.5)
    # Buckets 20..39 (aligned), min==first, max==last of each 10-wide bucket.
    assert ys[0] == 200.0 and ys[-1] == 399.0
    assert xs[0] == pytest.approx((20 + 0.5) * 10 * 0.5)
    assert np.all(np.diff(xs) >= 0)


def test_coarsen_preserves_extremes_and_alignment():
    p = LivePyramid(channels=1, base=8)
    data = make_block(1, 8 * 100 + 3)
    data[0, 555] = 77.0
    p.append(data)
    before_bytes = p.levels[0].nbytes
    assert p.coarsen()
    lvl = p.levels[0]
    assert lvl.bucket == 16
    assert lvl.nbytes <= before_bytes
    # Extremes survive, and appends after coarsening stay index-aligned.
    more = make_block(1, 500)
    more[0, 100] = -77.0
    p.append(more)
    _, ys = full_envelope(p, 0)
    assert ys.max() == 77.0 and ys.min() == -77.0
    ref = np.concatenate([data, more], axis=1)
    n_buckets = -(-ref.shape[1] // 16)
    pad = n_buckets * 16 - ref.shape[1]
    padded = np.pad(ref, ((0, 0), (0, pad)), constant_values=ref[0, -1])
    grouped = padded.reshape(1, n_buckets, 16)
    np.testing.assert_array_equal(p.levels[0].vmin[:, :n_buckets], grouped.min(axis=2))
    np.testing.assert_array_equal(p.levels[0].vmax[:, :n_buckets], grouped.max(axis=2))


def test_byte_cap_triggers_auto_coarsen():
    p = LivePyramid(channels=4, base=4, max_bytes=64 * 1024)
    for _ in range(50):
        p.append(make_block(4, 10_000))
    assert p.coarsen_events > 0
    assert p.levels[0].bucket > 4
    assert p.nbytes <= 2 * 64 * 1024  # allowed transient overshoot is small


def test_auto_base_scales_with_rate():
    assert _auto_base(20, 10_000, 256 * 2**20) == 64
    assert _auto_base(200, 100_000, 256 * 2**20) > 64


# --- SessionHistory --------------------------------------------------------


def make_history(channels=2, mode="ram", **kw) -> SessionHistory:
    settings = HistorySettings(mode=mode, **kw)
    return SessionHistory(settings, channels, sample_rate=1000.0)


def test_off_mode_is_inert():
    hist = make_history(mode="off")
    hist.on_block(make_block(2, 100), 0)
    assert hist.pyramid is None and hist.total_end == 0


def test_stitches_pyramid_head_with_ring_tail():
    ring = ChannelRing(channels=1, capacity=100)
    hist = make_history(channels=1, base=4)
    data = np.arange(500, dtype=np.float32).reshape(1, -1)
    for pos in range(0, 500, 50):
        block = data[:, pos : pos + 50]
        hist.on_block(block, ring.total_written)
        ring.append(block)
    dt = 0.001
    xs, ys = hist.query(ring, 0, 0, 500, n_out=400, dt=dt)
    assert xs.size > 0 and np.all(np.diff(xs) >= 0)
    # Head (evicted, samples 0..399) comes from the envelope, tail from the
    # ring at full resolution — the newest ring values must appear exactly.
    assert ys[-1] == 499.0
    assert xs[-1] == pytest.approx(499 * dt)
    assert xs[0] < 400 * dt  # envelope actually covers the evicted region
    assert ys.min() >= 0.0 and ys.max() <= 499.0


def test_ring_only_range_is_full_resolution():
    ring = ChannelRing(channels=1, capacity=1000)
    hist = make_history(channels=1)
    block = np.arange(300, dtype=np.float32).reshape(1, -1)
    hist.on_block(block, 0)
    ring.append(block)
    xs, ys = hist.query(ring, 0, 100, 200, n_out=10**9, dt=1.0)
    np.testing.assert_array_equal(ys, np.arange(100, 200, dtype=np.float64))
    np.testing.assert_array_equal(xs, np.arange(100, 200, dtype=np.float64))


def test_epoch_clamps_query():
    ring = ChannelRing(channels=2, capacity=1000)
    hist = make_history(channels=2)
    block = make_block(2, 400)
    hist.on_block(block, 0)
    ring.append(block)
    hist.note_epoch(0, 300)
    xs0, _ = hist.query(ring, 0, 0, 400, n_out=1000, dt=1.0)
    xs1, _ = hist.query(ring, 1, 0, 400, n_out=1000, dt=1.0)
    assert xs0.size and xs0[0] >= 300.0  # clamped to the reassignment
    assert xs1.size and xs1[0] < 300.0  # other slot unaffected


def test_first_index_anchor_after_clear():
    ring = ChannelRing(channels=1, capacity=50)
    hist = make_history(channels=1, base=4)
    first = np.zeros((1, 200), dtype=np.float32)
    hist.on_block(first, 0)
    ring.append(first)
    hist.clear()
    block = np.full((1, 200), 5.0, dtype=np.float32)
    hist.on_block(block, ring.total_written)
    ring.append(block)
    assert hist.first_index == 200
    assert hist.total_end == 400
    xs, ys = hist.query(ring, 0, 0, 400, n_out=100, dt=1.0)
    # Pre-clear data is gone; everything served starts at index 200.
    assert xs[0] >= 200.0
    assert np.all(ys == 5.0)


# --- DiskSpill / HistoryReader ---------------------------------------------


def test_disk_spill_roundtrip_per_channel(tmp_path):
    from uz_scope.history import DiskSpill

    spill = DiskSpill(tmp_path, channels=3, timestep_s=1e-4, autostart=False)
    data = make_block(3, 1000)
    spill.submit(data[:, :400], 0)
    spill.submit(data[:, 400:], 400)
    spill.drain_inline()
    assert spill.flushed_rows == 1000
    for ch in range(3):
        y, lo = spill.read(ch, 100, 900)
        assert lo == 100
        np.testing.assert_array_equal(y, data[ch, 100:900])
    spill.close(keep=True)
    assert (spill.directory / "session.json").is_file()
    assert (spill.directory / "ch00.f32").stat().st_size == 4000


def test_disk_spill_gap_backfills_nan(tmp_path):
    from uz_scope.history import DiskSpill

    spill = DiskSpill(tmp_path, channels=1, timestep_s=1e-4, autostart=False)
    spill.submit(np.ones((1, 100), dtype=np.float32), 0)
    spill.submit(np.full((1, 100), 2.0, dtype=np.float32), 150)  # 50 lost
    spill.drain_inline()
    y, lo = spill.read(0, 0, 250)
    assert lo == 0 and y.shape[0] == 250
    assert np.all(y[:100] == 1.0)
    assert np.all(np.isnan(y[100:150]))
    assert np.all(y[150:] == 2.0)
    spill.close(keep=False)
    assert not spill.directory.exists()  # keep_files off cleans up


def test_disk_spill_backpressure_drops_and_counts(tmp_path):
    from uz_scope.history import DiskSpill

    spill = DiskSpill(
        tmp_path, channels=1, timestep_s=1e-4, queue_chunks=2, autostart=False
    )
    for i in range(5):
        spill.submit(np.ones((1, 10), dtype=np.float32), i * 10)
    assert spill.chunks_dropped == 3
    assert spill.samples_dropped == 30
    spill.drain_inline()
    spill.close(keep=False)


def test_history_reader_serves_latest_request(tmp_path):
    from uz_scope.history import DiskSpill, HistoryReader

    spill = DiskSpill(tmp_path, channels=1, timestep_s=1.0, autostart=False)
    ramp = np.arange(10_000, dtype=np.float32).reshape(1, -1)
    spill.submit(ramp, 0)
    spill.drain_inline()
    reader = HistoryReader(spill)
    try:
        reader.request("cell0", 0, 1000, 2000, n_out=10**9, dt=1.0)
        for _ in range(200):
            detail = reader.poll("cell0")
            if detail is not None:
                break
            time.sleep(0.01)
        assert detail is not None
        assert detail.start == 1000 and detail.stop == 2000
        np.testing.assert_array_equal(
            detail.ys, np.arange(1000, 2000, dtype=np.float64)
        )
        np.testing.assert_array_equal(detail.xs, detail.ys)
    finally:
        reader.close()
        spill.close(keep=False)


def test_disk_mode_detail_swaps_in(tmp_path):
    ring = ChannelRing(channels=1, capacity=100)
    hist = make_history(
        channels=1, mode="disk", directory=str(tmp_path), base=4
    )
    try:
        data = np.arange(2000, dtype=np.float32).reshape(1, -1)
        for pos in range(0, 2000, 100):
            block = data[:, pos : pos + 100]
            hist.on_block(block, ring.total_written)
            ring.append(block)
        # Wait for the spill's idle flush to make the rows readable.
        for _ in range(500):
            if hist.spill.flushed_rows >= 2000:
                break
            time.sleep(0.01)
        assert hist.spill.flushed_rows >= 2000
        # [500, 1500) is fully evicted from the 100-sample ring, so the first
        # query serves the envelope and primes the async detail request...
        xs, ys = hist.query(ring, 0, 500, 1500, n_out=10**9, dt=1.0, key="c")
        assert xs.size
        got_detail = False
        for _ in range(300):
            xs, ys = hist.query(ring, 0, 500, 1500, n_out=10**9, dt=1.0, key="c")
            # ...until full detail swaps in: the exact consecutive ramp.
            if ys.size == 1000 and np.array_equal(
                ys, np.arange(500, 1500, dtype=np.float64)
            ):
                got_detail = True
                break
            time.sleep(0.01)
        assert got_detail
    finally:
        hist.close(keep=False)


def test_reader_retries_after_flush_clamped_read(tmp_path):
    """A read clamped short by unflushed data must not be deduped forever."""
    from uz_scope.history import DiskSpill, HistoryReader

    spill = DiskSpill(tmp_path, channels=1, timestep_s=1.0, autostart=False)
    ramp = np.arange(1000, dtype=np.float32).reshape(1, -1)
    spill.submit(ramp[:, :500], 0)
    spill.drain_inline()
    reader = HistoryReader(spill)
    try:
        reader.request("k", 0, 0, 1000, n_out=10**9, dt=1.0)
        for _ in range(200):
            detail = reader.poll("k")
            if detail is not None:
                break
            time.sleep(0.01)
        assert detail is not None and detail.stop == 500  # clamped
        # More data lands on disk; the identical request must run again.
        spill.submit(ramp[:, 500:], 500)
        spill.drain_inline()
        reader.request("k", 0, 0, 1000, n_out=10**9, dt=1.0)
        for _ in range(200):
            detail = reader.poll("k")
            if detail is not None and detail.stop == 1000:
                break
            time.sleep(0.01)
        assert detail.stop == 1000
        np.testing.assert_array_equal(
            detail.ys, np.arange(1000, dtype=np.float64)
        )
    finally:
        reader.close()
        spill.close(keep=False)


def test_reader_survives_vanished_spill(tmp_path):
    """Deleting the spill mid-read must not kill the worker thread."""
    import shutil

    from uz_scope.history import DiskSpill, HistoryReader

    spill = DiskSpill(tmp_path, channels=1, timestep_s=1.0, autostart=False)
    spill.submit(np.zeros((1, 100), dtype=np.float32), 0)
    spill.drain_inline()
    reader = HistoryReader(spill)
    try:
        shutil.rmtree(spill.directory)
        reader.request("k", 0, 0, 100, n_out=100, dt=1.0)
        deadline = time.monotonic() + 2.0
        while reader._requests and time.monotonic() < deadline:
            time.sleep(0.01)
        assert reader._thread.is_alive()  # worker survived the failed read
        assert reader.poll("k") is None
    finally:
        reader.close()


def test_spill_write_failure_never_raises_from_close(tmp_path):
    from uz_scope.history import DiskSpill

    spill = DiskSpill(tmp_path, channels=1, timestep_s=1.0, autostart=False)
    spill._files[0].close()  # simulate a dead file handle (disk full etc.)
    spill.submit(np.zeros((1, 100_000), dtype=np.float32), 0)
    spill.drain_inline()
    assert spill.error is not None
    spill.close(keep=True)  # must not raise despite the broken file


def test_epoch_boundary_bucket_hides_previous_observable():
    """A pyramid bucket straddling a reassignment must not leak old data."""
    ring = ChannelRing(channels=1, capacity=10)
    hist = make_history(channels=1, base=64)
    old = np.full((1, 100), 1000.0, dtype=np.float32)
    hist.on_block(old, 0)
    ring.append(old)
    hist.note_epoch(0, 100)  # reassigned mid-bucket (100 % 64 != 0)
    new = np.zeros((1, 900), dtype=np.float32)
    hist.on_block(new, 100)
    ring.append(new)
    _, ys = hist.query(ring, 0, 0, 1000, n_out=64, dt=1.0)
    assert ys.size and ys.max() < 1000.0  # pre-epoch spike not shown


# --- state wiring ----------------------------------------------------------


def test_state_feeds_history_and_epochs(real_header_path, tmp_path):
    from uz_scope.config import ScopeConfig
    from uz_scope.javascope_header import parse_header
    from uz_scope.state import ScopeAppState

    state = ScopeAppState(
        config=ScopeConfig(),
        header=parse_header(real_header_path),
        settings_path=tmp_path / "settings.json",
    )

    class P:
        pass

    parsed = P()
    parsed.samples = np.ones((2, 20, 15), dtype=np.float32)
    parsed.status = np.array([0, 0], dtype=np.uint32)
    parsed.slow_id = np.zeros((2, 15), dtype=np.int32)
    parsed.slow_raw = np.zeros((2, 15), dtype=np.uint32)
    state._on_frames(parsed)
    assert state.history.total_end == 30
    state.select_observable(3, 5)
    assert state.history.valid_from[3] == 30
    state.commands.dispatch(state, "history_mode(off)")
    assert state.history.pyramid is None
    state.commands.dispatch(state, "history_mode(ram)")
    assert state.history.pyramid is not None
    state.commands.dispatch(state, "history_limit(64)")
    assert state.history.pyramid.max_bytes == 64 * 1024 * 1024
