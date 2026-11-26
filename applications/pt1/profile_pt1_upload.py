"""Measure upload phases using an existing, idle acquisition service.

Example: python applications/pt1/profile_pt1_upload.py path/to/export
The service must already have the five NN update feedback channels assigned.
No firmware is flashed. Each upload leaves the controller stopped.
"""

import argparse
import csv
import json
from datetime import datetime, timezone
from pathlib import Path
from statistics import mean

from ultrazohm_cli import Client
from update_parameters_prototype import (
    ROOT,
    network_info,
    read_parameters_from_csv,
    uz_nn_update_weights,
)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directory", type=Path)
    parser.add_argument("--endpoint", default="127.0.0.1:19740")
    parser.add_argument("--intervals-ms", type=float, nargs="+", default=[0.1, 0.2])
    parser.add_argument("--repeats", type=int, default=3)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    if args.repeats < 1 or any(not 0.1 <= n <= 100 for n in args.intervals_ms):
        parser.error("repeats must be positive and intervals must be 0.1–100 ms")
    parameters = read_parameters_from_csv(args.directory)
    info = network_info("dqn")
    output = args.output or ROOT / "artifacts" / (
        "pt1-upload-timing-" + datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S.%fZ")
    )
    output.mkdir(parents=True, exist_ok=False)
    rows = []
    client = Client(args.endpoint)
    try:
        status = client.status()
        if not status["state"]["connected"]:
            raise RuntimeError("Acquisition service is not connected to the board")
        if any(
            v["phase"] not in {"idle", "complete"} for v in status["logging"].values()
        ):
            raise RuntimeError("Finish existing recordings before profiling")
        (output / "settings.json").write_text(
            json.dumps(
                {
                    "weights": str(args.directory.resolve()),
                    "intervals_ms": args.intervals_ms,
                    "repeats": args.repeats,
                    "service": status,
                },
                indent=2,
            )
            + "\n"
        )
        for repeat in range(1, args.repeats + 1):
            for interval in args.intervals_ms:
                timings = {}
                result = uz_nn_update_weights(
                    client,
                    parameters,
                    info,
                    command_interval=interval / 1000,
                    assign_feedback=False,
                    timings=timings,
                )
                row = {
                    "repeat": repeat,
                    "interval_ms": interval,
                    **timings,
                    "received": result["received"],
                    "error": result["error"],
                }
                rows.append(row)
                with (output / "measurements.jsonl").open(
                    "a", encoding="utf-8"
                ) as file:
                    file.write(json.dumps(row) + "\n")
    finally:
        client.close()
    with (output / "measurements.csv").open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(file, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    for interval in args.intervals_ms:
        subset = [row for row in rows if row["interval_ms"] == interval]
        print(
            json.dumps(
                {
                    "interval_ms": interval,
                    **{key: mean(row[key] for row in subset) for key in timings},
                }
            )
        )
    print(f"Timing measurements: {output}")


if __name__ == "__main__":
    main()
