#!/usr/bin/env python3
import argparse
import csv
import glob
import os
import sys


def find_latest_log():
    candidates = glob.glob("Log_*.csv")
    if not candidates:
        return None
    return max(candidates, key=os.path.getmtime)


def trim_row(row):
    while row and row[-1] == "":
        row.pop()
    return row


def parse_int(value):
    try:
        return int(float(value))
    except (ValueError, TypeError):
        return None


def is_repeated_header_row(row, header):
    if len(row) < len(header):
        return False
    for i, name in enumerate(header):
        if row[i].strip() != name.strip():
            return False
    return True


def select_lifecheck_columns(header, selector):
    indices = []
    if selector is None:
        for i, name in enumerate(header):
            if "lifecheck" in name.lower():
                indices.append(i)
        return indices

    # If selector is numeric, treat as index
    try:
        idx = int(selector)
        if idx < 0 or idx >= len(header):
            raise ValueError
        return [idx]
    except ValueError:
        pass

    # Otherwise treat as substring match
    sel = selector.lower()
    for i, name in enumerate(header):
        if sel in name.lower():
            indices.append(i)
    return indices


def analyze(path, selector=None, max_report=10):
    with open(path, newline="", encoding="utf-8") as handle:
        reader = csv.reader(handle, delimiter=";")

        header = None
        for row in reader:
            if not row or all(not cell.strip() for cell in row):
                continue
            header = trim_row(row)
            break

        if not header:
            raise RuntimeError("No header row found.")

        life_indices = select_lifecheck_columns(header, selector)
        if not life_indices:
            raise RuntimeError("No lifecheck columns found in header.")

        prev = {idx: None for idx in life_indices}
        errors = {idx: [] for idx in life_indices}
        total_rows = 0
        processed_rows = 0
        pending_row = None
        pending_row_num = None

        for row in reader:
            if not row or all(not cell.strip() for cell in row):
                continue
            row = trim_row(row)
            total_rows += 1

            # Process the previous row so the last row is always ignored.
            if pending_row is not None:
                processed_rows += 1
                time_val = pending_row[0] if pending_row else ""
                for idx in life_indices:
                    if idx >= len(pending_row):
                        errors[idx].append((pending_row_num, time_val, "missing", None, None, None))
                        continue

                    val = parse_int(pending_row[idx].strip())
                    if val is None:
                        errors[idx].append((pending_row_num, time_val, "non-numeric", None, pending_row[idx], None))
                        continue

                    if val < 0 or val > 1000:
                        errors[idx].append((pending_row_num, time_val, "out-of-range", None, val, None))
                        prev[idx] = val
                        continue

                    prev_val = prev[idx]
                    if prev_val is None:
                        prev[idx] = val
                        continue

                    # Accept wrap at 999->0 or 1000->0 (logs show 0..999 in practice).
                    if (prev_val in (999, 1000)) and val == 0:
                        prev[idx] = val
                        continue

                    expected = prev_val + 1
                    if val != expected:
                        if prev_val in (999, 1000):
                            lost = val
                        elif val > prev_val:
                            lost = val - prev_val - 1
                        else:
                            lost = (1000 - prev_val) + val
                        errors[idx].append((pending_row_num, time_val, "jump", prev_val, val, lost))

                    prev[idx] = val

            # Some logs may contain the CSV header again after logging restarts.
            # Treat that as a segment boundary and reset continuity checks.
            if is_repeated_header_row(row, header):
                for idx in life_indices:
                    prev[idx] = None
                pending_row = None
                pending_row_num = None
                continue

            pending_row = row
            pending_row_num = total_rows

    return header, life_indices, processed_rows, errors


def main():
    parser = argparse.ArgumentParser(
        description="Check lifecheck counter increments in JavaScope logs."
    )
    parser.add_argument(
        "logfile",
        nargs="?",
        help="Path to log CSV. Defaults to latest Log_*.csv in the current directory.",
    )
    parser.add_argument(
        "--column",
        help="Column index or substring match (defaults to all 'lifecheck' columns).",
    )
    parser.add_argument(
        "--max-report",
        type=int,
        default=10,
        help="Max number of error samples to show per column (default: 10).",
    )
    args = parser.parse_args()

    path = args.logfile or find_latest_log()
    if not path:
        print("No Log_*.csv files found.", file=sys.stderr)
        return 2

    try:
        header, life_indices, rows, errors = analyze(
            path, selector=args.column, max_report=args.max_report
        )
    except RuntimeError as err:
        print(f"File: {path}")
        if str(err) == "No header row found.":
            print("Log is empty (or only contains blank lines). Nothing to analyze.")
        else:
            print(f"Could not analyze log: {err}")
        return 2

    print(f"File: {path}")
    print(f"Rows: {rows} (last row ignored)")
    print("Lifecheck columns:")
    for idx in life_indices:
        print(f"  [{idx}] {header[idx]}")

    had_error = False
    for idx in life_indices:
        col_errors = errors[idx]
        if not col_errors:
            print(f"\nColumn [{idx}] OK (no jumps detected).")
            continue

        had_error = True
        print(f"\nColumn [{idx}] {header[idx]}: {len(col_errors)} issues")
        for sample in col_errors[: args.max_report]:
            row_num, time_val, kind, prev_val, val, lost = sample
            if kind == "jump":
                print(
                    f"  row {row_num}, time={time_val}, prev={prev_val}, val={val}, lost≈{lost}"
                )
            elif kind == "missing":
                print(f"  row {row_num}, time={time_val}, missing column")
            elif kind == "non-numeric":
                print(f"  row {row_num}, time={time_val}, non-numeric value '{val}'")
            elif kind == "out-of-range":
                print(f"  row {row_num}, time={time_val}, out-of-range value {val}")

        if len(col_errors) > args.max_report:
            print(f"  ... {len(col_errors) - args.max_report} more")

    if had_error:
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
