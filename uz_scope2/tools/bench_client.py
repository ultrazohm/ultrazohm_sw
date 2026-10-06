#!/usr/bin/env python3
"""Soak client: full ingest hot path (recv -> parse -> ring -> lifecheck).

Run against ``bench_server.py`` and check that the client sustains the target
rate with zero lifecheck gaps.  The Phase-2 acceptance run::

    python uz_scope2/tools/bench_server.py --channels 200 --rate 100000 &
    python uz_scope2/tools/bench_client.py --channels 200 --rate 100000 --seconds 60

Exit code 0 iff average ingest >= --min-fraction of the nominal rate and the
lifecheck counter (channel 0) never skipped.
"""

from __future__ import annotations

import argparse
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "src"))

from uz_scope2.lifecheck import Lifecheck  # noqa: E402
from uz_scope2.netclient import ClientCallbacks, ScopeClient  # noqa: E402
from uz_scope2.protocol import FrameGeometry  # noqa: E402
from uz_scope2.ring import ChannelRing, ring_capacity  # noqa: E402


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=5001)
    parser.add_argument("--channels", type=int, default=20)
    parser.add_argument("--samples-per-packet", type=int, default=15)
    parser.add_argument("--rate", type=float, default=10000.0, help="nominal samples/s")
    parser.add_argument("--seconds", type=float, default=30.0)
    parser.add_argument("--ring-seconds", type=float, default=2.0)
    parser.add_argument("--min-fraction", type=float, default=0.98)
    parser.add_argument(
        "--ack-pacing", action="store_true", help="one 8-byte ack per frame (lock-step)"
    )
    args = parser.parse_args(argv)

    geom = FrameGeometry(args.channels, args.samples_per_packet)
    capacity = ring_capacity(
        geom.channels, args.rate, args.ring_seconds, 512 * 1024 * 1024
    )
    ring = ChannelRing(geom.channels, capacity)
    lifecheck = Lifecheck()

    def on_frames(parsed) -> None:
        ring.append_frames(parsed.samples)
        lifecheck.update(parsed.samples[:, 0, :].reshape(-1))

    client = ScopeClient(
        geom,
        args.host,
        args.port,
        ack_pacing=args.ack_pacing,
        callbacks=ClientCallbacks(on_frames=on_frames),
        reconnect=False,
    )
    client.start()
    if not client.connected.wait(5.0):
        print("ERROR: could not connect", file=sys.stderr)
        client.stop()
        return 2

    expected_mb_s = args.rate * geom.frame_bytes / geom.samples_per_packet / 1e6
    print(
        f"connected; nominal {args.rate:,.0f} samples/s = {expected_mb_s:.1f} MB/s, "
        f"ring {capacity:,} samples/ch ({ring.data.nbytes / 1e6:.0f} MB)"
    )

    t0 = time.perf_counter()
    last_t, last_bytes, last_samples = t0, 0, 0
    worst_mb_s = float("inf")
    try:
        while time.perf_counter() - t0 < args.seconds:
            time.sleep(1.0)
            if not client.connected.is_set():
                print("ERROR: connection lost", file=sys.stderr)
                break
            now = time.perf_counter()
            stats = client.stats
            mb_s = (stats.bytes_received - last_bytes) / (now - last_t) / 1e6
            sps = (stats.samples - last_samples) / (now - last_t)
            worst_mb_s = min(worst_mb_s, mb_s)
            print(
                f"  {now - t0:5.1f}s  {mb_s:7.2f} MB/s  {sps:12,.0f} samples/s  "
                f"gaps={lifecheck.gaps}"
            )
            last_t, last_bytes, last_samples = now, stats.bytes_received, stats.samples
    except KeyboardInterrupt:
        pass

    elapsed = time.perf_counter() - t0
    stats = client.stats
    client.stop()

    avg_sps = stats.samples / max(elapsed, 1e-9)
    avg_mb_s = stats.bytes_received / max(elapsed, 1e-9) / 1e6
    ok_rate = avg_sps >= args.min_fraction * args.rate
    ok_gaps = lifecheck.gaps == 0 and lifecheck.checked > 0
    print(
        f"\nsummary: {elapsed:.1f} s, {stats.bytes_received / 1e6:,.1f} MB, "
        f"avg {avg_mb_s:.2f} MB/s ({avg_sps:,.0f} samples/s, "
        f"{100 * avg_sps / args.rate:.1f}% of nominal), worst 1s window "
        f"{worst_mb_s:.2f} MB/s"
    )
    print(
        f"lifecheck: {lifecheck.checked:,} samples checked, "
        f"{lifecheck.gaps} gaps, {lifecheck.missing} samples missing"
    )
    if ok_rate and ok_gaps:
        print("PASS")
        return 0
    print("FAIL")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
