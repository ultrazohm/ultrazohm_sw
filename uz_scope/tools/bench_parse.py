#!/usr/bin/env python3
"""Offline parse/ring micro-benchmark (no sockets).

Measures the pure CPU cost of the ingest hot path — parse_frames + ring
append — on synthetic frames, reported as MB/s and as headroom over the
80.8 MB/s design target (200 ch x 100 kHz).
"""

from __future__ import annotations

import argparse
import sys
import time
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "src"))

from uz_scope.protocol import FrameGeometry, parse_frames  # noqa: E402
from uz_scope.ring import ChannelRing  # noqa: E402

TARGET_MB_S = 80.8


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--channels", type=int, default=200)
    parser.add_argument("--samples-per-packet", type=int, default=15)
    parser.add_argument("--burst-frames", type=int, default=64)
    parser.add_argument("--seconds", type=float, default=5.0)
    args = parser.parse_args(argv)

    geom = FrameGeometry(args.channels, args.samples_per_packet)
    rng = np.random.default_rng(0)
    chunk = rng.integers(
        1, 2**31, size=args.burst_frames * geom.words, dtype=np.uint32
    ).astype("<u4").tobytes()
    ring = ChannelRing(geom.channels, 1_000_000 // max(1, geom.channels // 200))

    # warmup
    for _ in range(10):
        ring.append_frames(parse_frames(chunk, geom).samples)

    t0 = time.perf_counter()
    nbytes = 0
    iters = 0
    while time.perf_counter() - t0 < args.seconds:
        parsed = parse_frames(chunk, geom)
        ring.append_frames(parsed.samples)
        nbytes += len(chunk)
        iters += 1
    elapsed = time.perf_counter() - t0

    mb_s = nbytes / elapsed / 1e6
    print(
        f"{geom.channels} ch x {geom.samples_per_packet} samples/frame, "
        f"burst {args.burst_frames} frames ({len(chunk)} B)"
    )
    print(
        f"parse+ring: {mb_s:,.0f} MB/s ({iters / elapsed:,.0f} bursts/s) — "
        f"{mb_s / TARGET_MB_S:,.1f}x the {TARGET_MB_S} MB/s target"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
