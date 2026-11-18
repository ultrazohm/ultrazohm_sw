"""Prepare a Data Viewer .uzscript overlaying UltraZohm and Ceedling PT1 logs.

Run this generator with Python, then open the resulting .uzscript in Data Viewer.
Both logs are aligned using the controller sample index at 100 microseconds/step.
"""

import argparse
import json
from pathlib import Path
import sys

from compare_pt1_logs import EXPECTED, read_capture


def main():
    import polars as pl

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("actor", choices=("dqn", "ddpg"))
    parser.add_argument("capture", type=Path, help="recorded data.parquet or capture CSV")
    parser.add_argument("--expected", type=Path, help="Ceedling evaluation CSV")
    parser.add_argument("--output", type=Path, required=True, help="new directory for viewer inputs and script")
    args = parser.parse_args()
    hardware = read_capture(args.capture, args.actor)
    if hardware.is_empty():
        parser.error("Capture contains no samples for the selected actor")
    expected = args.expected or EXPECTED / f"pt1_{args.actor}_eval.csv"
    reference = pl.read_csv(expected, separator=";", infer_schema_length=None)
    # Replace acquisition time by the controller's sample time for both sources.
    hardware = hardware.with_columns(pl.col("time").cast(pl.Float64) * 0.0001)
    reference = reference.with_columns(pl.col("time").cast(pl.Float64) * 0.0001)
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=False)
    hardware_path = output / f"pt1_{args.actor}_ultrazohm.csv"
    reference_path = output / f"pt1_{args.actor}_ceedling.csv"
    hardware.write_csv(hardware_path)
    reference.write_csv(reference_path)
    lines = [
        "clear_session()",
        f"load({json.dumps(str(hardware_path))})",
        f"load({json.dumps(str(reference_path))})",
        f"set_grid({3 if args.actor == 'dqn' else 2}, 2)",
        "link_x(on)",
    ]
    plots = [["y"], ["reference"], ["action_value"], ["reward"]]
    if args.actor == "dqn":
        plots += [["action_index"], ["q_action_minus_1", "q_action_0", "q_action_plus_1"]]
    for plot, signals in enumerate(plots, 1):
        for path in (hardware_path, reference_path):
            for signal in signals:
                lines.append(f"add_signal(plot_{plot}, {json.dumps(path.name)}, {json.dumps(signal)})")
    script = output / f"pt1_{args.actor}_comparison.uzscript"
    script.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"Open in Data Viewer: {script}")
    print("The script clears the current viewer session and overlays both logs. X is seconds.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError) as error:
        sys.exit(str(error))
