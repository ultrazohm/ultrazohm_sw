"""Compare a JavaScope FastData recording of PT1 replay with a Ceedling CSV."""

import argparse
import csv
import math
import re


def compare(capture_path, expected_path, actor):
    fields = {
        "time": 0.0,
        "episode": 0.0,
        "episode_k": 0.0,
        "y": 2e-4,
        "reference": 1e-7,
        "error": 2e-4,
        "action_value": 2e-4,
        "reward": 1e-3,
        "done": 0.0,
    }
    if actor == "dqn":
        fields.update(
            action_index=0.0, q_action_minus_1=2e-3,
            q_action_0=2e-3, q_action_plus_1=2e-3,
        )
    actor_id = {"dqn": 1, "ddpg": 2}[actor]

    with open(expected_path, newline="", encoding="utf-8-sig") as expected_file:
        expected = list(csv.DictReader(expected_file, delimiter=";"))
    if len(expected) != 3000:
        raise ValueError(f"Expected 3000 Ceedling rows, found {len(expected)}")

    with open(capture_path, newline="", encoding="utf-8-sig") as capture_file:
        capture = csv.DictReader(capture_file, delimiter=";")
        channels = {}
        for label in capture.fieldnames or ():
            match = re.search(r"pt1_([a-z0-9_]+)$", label.strip())
            if match:
                channels[match.group(1)] = label
        missing = (fields.keys() | {"actor"}) - channels.keys()
        if missing:
            raise ValueError("Missing JavaScope channels: " +
                             ", ".join(f"pt1_{name}" for name in sorted(missing)))

        sample = 0
        for row in capture:
            actor_value = row[channels["actor"]]
            if not actor_value or float(actor_value) != actor_id:
                continue
            if sample >= len(expected):
                raise ValueError(f"Extra {actor} data after sample {sample - 1}; record one replay")
            for field, tolerance in fields.items():
                try:
                    actual = float(row[channels[field]])
                    reference = float(expected[sample][field])
                except (TypeError, ValueError, KeyError) as error:
                    raise ValueError(f"Missing or invalid {field} at sample {sample}") from error
                if not math.isfinite(actual) or not math.isfinite(reference) or (
                    abs(actual - reference) > tolerance
                ):
                    raise ValueError(
                        f"Sample {sample}, {field}: JavaScope {actual}, Ceedling {reference} "
                        f"(absolute tolerance {tolerance})"
                    )
            sample += 1
    if sample != len(expected):
        raise ValueError(f"Expected {len(expected)} {actor} samples, captured {sample}")
    print(f"Matched {sample} PT1 {actor.upper()} samples against Ceedling")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("actor", choices=("dqn", "ddpg"))
    parser.add_argument("capture", help="JavaScope Log_*.csv")
    parser.add_argument("expected", help="Ceedling pt1_dqn_eval.csv or pt1_ddpg_eval.csv")
    args = parser.parse_args()
    try:
        compare(args.capture, args.expected, args.actor)
    except (OSError, ValueError) as error:
        parser.exit(1, f"{error}\n")


if __name__ == "__main__":
    main()
