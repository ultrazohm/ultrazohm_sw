"""Benchmark live buffer and plot preparation without a device or GPU.

Run with the viewer's Python environment. Results are CPU timings, not GUI FPS
or a measurement of the CLI/network path. Simulated time runs without sleeping.
"""
import argparse
import json
import platform
from pathlib import Path
import sys
import time

import numpy as np
import polars as pl

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'src'))
from uz_dataviewer.live import LiveRing, LiveSource  # noqa: E402


def positive(value):
    value = int(value)
    if value < 1:
        raise argparse.ArgumentTypeError('must be positive')
    return value


def timings(values):
    if not values:
        return None
    return dict(zip(('p50_ms', 'p95_ms', 'max_ms'),
                    np.percentile(values, [50, 95, 100]).round(3).tolist()))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--sample-rate', type=positive, default=10_000)
    parser.add_argument('--channels', type=positive, default=20)
    parser.add_argument('--traces', type=positive, default=3)
    parser.add_argument('--buffer-seconds', type=positive, default=30)
    parser.add_argument('--window-seconds', type=positive, default=2)
    parser.add_argument('--points', type=positive, default=2000)
    args = parser.parse_args()
    if args.traces > args.channels:
        parser.error('--traces must not exceed --channels')
    capacity = args.sample_rate * args.buffer_seconds
    page_rows = max(1, round(args.sample_rate / 30))
    ring = LiveRing(capacity)
    channels = [f'channel_{i}' for i in range(args.channels)]
    # Reusable signals keep test-data generation outside the measured operations.
    local_time = np.arange(page_rows, dtype=np.float64) / args.sample_rate
    values = {name: np.sin(local_time * (i + 1) * 100).astype(np.float32)
              for i, name in enumerate(channels)}
    status = np.zeros(page_rows, np.uint32)
    append = {'filling': [], 'full': [], 'compaction': []}
    display = {'filling': [], 'full': []}
    largest_buffer_bytes = 0
    # Exercise both filling and at least one rollover of the double buffer.
    for start in range(0, 3 * capacity, page_rows):
        page = pl.DataFrame({'time': local_time + start / args.sample_rate,
                             'status': status, **values})
        phase = 'filling' if ring.length < capacity else 'full'
        previous = ring.columns
        began = time.perf_counter()
        ring.append(page)
        elapsed = (time.perf_counter() - began) * 1000
        compacted = previous is not None and ring.columns is not previous
        append['compaction' if compacted else phase].append(elapsed)
        previous = None
        source = LiveSource(ring.snapshot())
        lo, hi = source.time[-1] - args.window_seconds, source.time[-1]
        began = time.perf_counter()
        for name in channels[:args.traces]:
            source.read_plot(name, lo, hi, args.points)
        display[phase].append((time.perf_counter() - began) * 1000)
        buffer_bytes = sum(a.nbytes for a in ring.columns.values())
        buffer_bytes += sum(a.nbytes for levels in ring.summary.values()
                            for level in levels for a in level)
        largest_buffer_bytes = max(largest_buffer_bytes, buffer_bytes)
    print(json.dumps({
        'platform': platform.platform(), 'python': platform.python_version(),
        'numpy': np.__version__, 'polars': pl.__version__, 'settings': vars(args),
        'append': {phase: timings(values) for phase, values in append.items()},
        'prepare_all_traces': {phase: timings(values) for phase, values in display.items()},
        'ring_allocation_mib': round(largest_buffer_bytes / 1024**2, 2),
        'note': 'CPU stages only; excludes GUI, GPU, CLI, network and thread contention. '
                'Ring allocation excludes older snapshots retained by readers.',
    }, indent=2))


if __name__ == '__main__':
    main()
