#!/usr/bin/env python3
"""Non-lock-step firehose server emulating the APU stream, for benchmarks.

Unlike ``javascope/test_server.py`` (which waits for one command per frame and
therefore caps throughput at the client's ack rate), this server streams at a
paced target rate and drains client commands on a separate thread — like the
real FreeRTOS APU does.

Channel 0 carries a wrapping sample counter (the lifecheck ground truth),
channel 1 a sine, all higher channels their own index as a constant.

Example (the 200 ch x 100 kHz soak target)::

    python uz_scope2/tools/bench_server.py --channels 200 --rate 100000
"""

from __future__ import annotations

import argparse
import socket
import sys
import threading
import time
from pathlib import Path

import numpy as np

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "src"))

from uz_scope2.lifecheck import DEFAULT_MODULO  # noqa: E402
from uz_scope2.protocol import FrameGeometry  # noqa: E402


def make_block(geom: FrameGeometry, burst_frames: int):
    """Preallocated (burst_frames, words) uint32 block + fast per-burst updater."""
    words = geom.words
    n = geom.samples_per_packet
    c = geom.channels
    block = np.zeros((burst_frames, words), dtype="<u4")
    fblock = block.view("<f4")
    fblock[:, 0] = 0.0
    block[:, 0] = 0b0011  # status: Ready | Running
    samples = fblock[:, 1 + n : 1 + n + c * n].reshape(burst_frames, c, n)
    if c > 2:
        samples[:, 2:, :] = np.arange(2, c, dtype=np.float32)[None, :, None]
    # slow ids cycle through a tiny enum, slow_raw = float bits of the id
    ids = (np.arange(burst_frames * n, dtype=np.int64) % 6).reshape(burst_frames, n)
    fblock[:, 1 + n + c * n :] = ids.astype(np.float32)
    slow_raw_f = block[:, 1 : 1 + n].view("<f4")
    slow_raw_f[:] = ids.astype(np.float32)

    burst_samples = burst_frames * n

    def update(counter_start: int) -> None:
        counters = (np.arange(burst_samples, dtype=np.int64) + counter_start) % DEFAULT_MODULO
        counters = counters.reshape(burst_frames, n).astype(np.float32)
        samples[:, 0, :] = counters
        if c > 1:
            samples[:, 1, :] = np.sin(counters * np.float32(2 * np.pi / 1000.0))

    return block, update, burst_samples


def drain_commands(sock: socket.socket, counters: dict) -> None:
    try:
        while True:
            data = sock.recv(65536)
            if not data:
                return
            counters["bytes"] += len(data)
            counters["commands"] += len(data) // 8
    except OSError:
        return


def serve_client(sock: socket.socket, args: argparse.Namespace) -> None:
    geom = FrameGeometry(args.channels, args.samples_per_packet)
    block, update, burst_samples = make_block(geom, args.burst_frames)
    sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
    try:
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, 4 * 1024 * 1024)
    except OSError:
        pass
    counters = {"bytes": 0, "commands": 0}
    drainer = threading.Thread(
        target=drain_commands, args=(sock, counters), daemon=True
    )
    drainer.start()

    frame_mb = geom.frame_bytes * args.rate / geom.samples_per_packet / 1e6
    print(
        f"streaming {geom.channels} ch x {args.rate} Hz "
        f"({geom.frame_bytes} B/frame, target {frame_mb:.1f} MB/s)"
    )
    sent_samples = 0
    counter = 0
    t0 = time.perf_counter()
    t_report = t0
    sent_report = 0
    try:
        while True:
            if args.seconds and time.perf_counter() - t0 >= args.seconds:
                break
            update(counter)
            sock.sendall(block)
            counter += burst_samples
            sent_samples += burst_samples
            # Pacing: never run ahead of the target sample clock.
            ahead = sent_samples / args.rate - (time.perf_counter() - t0)
            if ahead > 0.002:
                time.sleep(ahead)
            now = time.perf_counter()
            if now - t_report >= 5.0:
                rate = (sent_samples - sent_report) / (now - t_report)
                print(
                    f"  tx {rate:,.0f} samples/s "
                    f"({rate * geom.frame_bytes / geom.samples_per_packet / 1e6:.1f} MB/s), "
                    f"rx {counters['commands']} commands"
                )
                t_report, sent_report = now, sent_samples
    except OSError as exc:
        print(f"client gone: {exc}")
    finally:
        elapsed = time.perf_counter() - t0
        print(
            f"done: {sent_samples:,} samples in {elapsed:.1f} s "
            f"({sent_samples / max(elapsed, 1e-9):,.0f} samples/s), "
            f"received {counters['commands']} commands"
        )
        sock.close()


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=5001)
    parser.add_argument("--channels", type=int, default=20)
    parser.add_argument("--samples-per-packet", type=int, default=15)
    parser.add_argument("--rate", type=float, default=10000.0, help="samples/s")
    parser.add_argument(
        "--seconds", type=float, default=0.0, help="stop after N seconds (0 = forever)"
    )
    parser.add_argument("--burst-frames", type=int, default=64)
    parser.add_argument(
        "--once", action="store_true", help="exit after the first client disconnects"
    )
    args = parser.parse_args(argv)

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((args.host, args.port))
    server.listen(1)
    print(f"bench_server listening on {args.host}:{args.port}")
    try:
        while True:
            sock, addr = server.accept()
            print(f"client {addr[0]}:{addr[1]} connected")
            serve_client(sock, args)
            if args.once:
                return 0
    except KeyboardInterrupt:
        return 0
    finally:
        server.close()


if __name__ == "__main__":
    raise SystemExit(main())
