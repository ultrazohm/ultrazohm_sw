"""Compare one recorded PT1 replay with its Ceedling evaluation CSV."""

import argparse
import importlib.util
from pathlib import Path
import re
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
EXPECTED = ROOT / "vitis/software/Baremetal/build/artifacts/test-data/uz_exported_actor"


def read_capture(path, actor):
    """Return only the replay samples, with the controller sample index as time."""
    import polars as pl

    path = Path(path)
    if path.suffix.lower() == ".parquet":
        data = pl.read_parquet(path)
    else:
        with path.open(encoding="utf-8-sig") as source:
            header = source.readline()
        data = pl.read_csv(path, separator=";" if ";" in header else ",",
                           infer_schema_length=None)
    columns = {}
    for name in data.columns:
        match = re.search(r"pt1_([a-z0-9_]+)$", name.strip())
        if match:
            columns[name] = match.group(1)
    if "actor" not in columns.values() or "time" not in columns.values():
        raise ValueError("Capture must contain pt1_actor and pt1_time channels")
    data = data.select([pl.col(name).alias(field) for name, field in columns.items()])
    return data.filter(pl.col("actor") == {"dqn": 1, "ddpg": 2}[actor])


def compare(capture, expected, actor):
    tool = ROOT / "vitis/software/Baremetal/test/uz/uz_exported_actor/compare_pt1_javascope.py"
    spec = importlib.util.spec_from_file_location("pt1_comparison", tool)
    comparison = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(comparison)
    data = read_capture(capture, actor)
    with tempfile.TemporaryDirectory(prefix="pt1-compare-") as temporary:
        normalized = Path(temporary) / "capture.csv"
        data.rename({name: f"JSO_pt1_{name}" for name in data.columns}).write_csv(
            normalized, separator=";")
        comparison.compare(normalized, expected, actor)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("actor", choices=("dqn", "ddpg"))
    parser.add_argument("capture", type=Path, help="recorded data.parquet or capture CSV")
    parser.add_argument("--expected", type=Path, help="Ceedling evaluation CSV")
    args = parser.parse_args()
    compare(args.capture, args.expected or EXPECTED / f"pt1_{args.actor}_eval.csv", args.actor)


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError) as error:
        sys.exit(str(error))
