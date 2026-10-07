#!/usr/bin/env python3
"""Evaluate a JavaScope CSV recorded with the IM observer validation profile.

The tool uses only Python's standard library. If matplotlib is installed it
also writes an overview PNG. It compares deterministic (0), full Kalman (1)
and simplified Kalman plus Tustin (2) at identical stationary U/f plateaus.
"""

from __future__ import annotations

import argparse
import csv
import math
import re
from collections import defaultdict
from pathlib import Path
from statistics import fmean


MODE_NAMES = {0: "deterministic", 1: "full_kalman", 2: "simplified"}
# Non-zero stationary reference points supported by the current validation
# profile and the compact legacy documentation example. Zero-frequency
# intervals initialize/reset the observers and are deliberately excluded from
# the accuracy metrics.
PLATEAUS_HZ = (-5.0, -4.0, -2.5, -2.0, 1.0, 2.0, 2.5, 4.0, 5.0, 6.0)

ALIASES = {
    "time": ("IMVALIDATIONPROFILEELAPSEDS", "TIME"),
    "mode": ("IMVALIDATIONOBSERVERMODE",),
    "stage": ("IMVALIDATIONPROFILESTAGE",),
    "frequency_ref": ("IMFREQUENCYHZ",),
    "speed_rpm": ("IMSPEEDRPM",),
    "i_a": ("IMIA",),
    "i_b": ("IMIB",),
    "i_c": ("IMIC",),
    "flux_magnitude": ("IMFLUXVS",),
    "flux_angle": ("IMFLUXANGLERAD",),
    "stator_frequency": ("IMSTATORFREQUENCYHZ",),
    "rotor_frequency": ("IMROTORELECTRICALFREQUENCYHZ",),
    "slip_frequency": ("IMSLIPFREQUENCYHZ",),
    "innovation_alpha": ("IMKALMANINNOVATIONALPHAA",),
    "innovation_beta": ("IMKALMANINNOVATIONBETAA",),
    "i_d": ("IMID",),
    "i_q": ("IMIQ",),
    "flux_valid": ("IMROTORFLUXVALID",),
    "flux_angle_step": ("IMFLUXANGLESTEPRAD",),
    "phase_current_sum": ("IMPHASECURRENTSUMA",),
}


def normalized(text: str) -> str:
    return re.sub(r"[^A-Z0-9]", "", text.upper())


def identify_columns(headers: list[str]) -> dict[str, str]:
    normalized_headers = {header: normalized(header) for header in headers}
    result: dict[str, str] = {}
    for signal, aliases in ALIASES.items():
        for alias in aliases:
            matches = [header for header, value in normalized_headers.items() if alias in value]
            if matches:
                result[signal] = min(matches, key=len)
                break
    required = ("time", "mode", "frequency_ref", "flux_magnitude", "flux_angle", "stator_frequency")
    missing = [name for name in required if name not in result]
    if missing:
        available = "\n  ".join(headers)
        raise ValueError(f"Missing required JavaScope signals: {', '.join(missing)}\nAvailable columns:\n  {available}")
    return result


def read_log(path: Path) -> tuple[list[dict[str, float]], dict[str, str]]:
    sample = path.read_text(encoding="utf-8-sig", errors="replace")[:8192]
    try:
        dialect = csv.Sniffer().sniff(sample, delimiters=",;\t")
    except csv.Error:
        dialect = csv.excel
    rows: list[dict[str, float]] = []
    with path.open("r", encoding="utf-8-sig", errors="replace", newline="") as handle:
        reader = csv.DictReader(handle, dialect=dialect)
        if reader.fieldnames is None:
            raise ValueError("CSV has no header")
        columns = identify_columns(reader.fieldnames)
        for source in reader:
            parsed: dict[str, float] = {}
            valid = True
            for signal, column in columns.items():
                value = (source.get(column) or "").strip()
                if dialect.delimiter != ",":
                    value = value.replace(",", ".")
                try:
                    parsed[signal] = float(value)
                except ValueError:
                    valid = False
                    break
            if valid and all(math.isfinite(value) for value in parsed.values()):
                rows.append(parsed)
    if not rows:
        raise ValueError("CSV contains no finite numeric data rows")
    return rows, columns


def rms(values: list[float]) -> float:
    return math.sqrt(fmean(value * value for value in values)) if values else math.nan


def mean(values: list[float]) -> float:
    return fmean(values) if values else math.nan


def wrapped_delta(new: float, old: float) -> float:
    return math.atan2(math.sin(new - old), math.cos(new - old))


def orbit_axis_ratio(alpha: list[float], beta: list[float]) -> float:
    if len(alpha) < 3:
        return math.nan
    alpha_mean, beta_mean = mean(alpha), mean(beta)
    var_a = mean([(value - alpha_mean) ** 2 for value in alpha])
    var_b = mean([(value - beta_mean) ** 2 for value in beta])
    cov = mean([(a - alpha_mean) * (b - beta_mean) for a, b in zip(alpha, beta)])
    trace = var_a + var_b
    discriminant = math.sqrt(max(0.0, (var_a - var_b) ** 2 + 4.0 * cov * cov))
    lambda_max = 0.5 * (trace + discriminant)
    lambda_min = 0.5 * (trace - discriminant)
    return math.sqrt(max(0.0, lambda_min) / lambda_max) if lambda_max > 0.0 else math.nan


def summarize_group(mode: int, target_hz: float, occurrence: int,
                    rows: list[dict[str, float]]) -> dict[str, float | str]:
    rows.sort(key=lambda row: row["time"])
    flux = [row["flux_magnitude"] for row in rows]
    angle = [row["flux_angle"] for row in rows]
    alpha = [magnitude * math.cos(phi) for magnitude, phi in zip(flux, angle)]
    beta = [magnitude * math.sin(phi) for magnitude, phi in zip(flux, angle)]
    stator_error = [row["stator_frequency"] - row["frequency_ref"] for row in rows]
    angle_frequency_error: list[float] = []
    for previous, current in zip(rows, rows[1:]):
        dt = current["time"] - previous["time"]
        if dt > 0.0:
            angle_hz = wrapped_delta(current["flux_angle"], previous["flux_angle"]) / (2.0 * math.pi * dt)
            angle_frequency_error.append(angle_hz - current["frequency_ref"])
    result: dict[str, float | str] = {
        "observer_mode": mode,
        "observer_name": MODE_NAMES.get(mode, f"unknown_{mode}"),
        "target_frequency_Hz": target_hz,
        "plateau_occurrence": occurrence,
        "samples": len(rows),
        "duration_s": rows[-1]["time"] - rows[0]["time"],
        "stator_frequency_bias_Hz": mean(stator_error),
        "stator_frequency_rmse_Hz": rms(stator_error),
        "angle_frequency_rmse_Hz": rms(angle_frequency_error),
        "flux_mean_Vs": mean(flux),
        "flux_ripple_percent": 100.0 * (max(flux) - min(flux)) / abs(mean(flux)) if abs(mean(flux)) > 1e-12 else math.nan,
        "flux_center_alpha_Vs": mean(alpha),
        "flux_center_beta_Vs": mean(beta),
        "flux_orbit_axis_ratio": orbit_axis_ratio(alpha, beta),
    }
    for signal in ("innovation_alpha", "innovation_beta", "phase_current_sum", "flux_angle_step"):
        if signal in rows[0]:
            values = [row[signal] for row in rows]
            result[f"{signal}_mean"] = mean(values)
            result[f"{signal}_rms"] = rms(values)
    if all(signal in rows[0] for signal in ("i_a", "i_b", "i_c")):
        phase_rms = [rms([row[signal] for row in rows]) for signal in ("i_a", "i_b", "i_c")]
        result["phase_current_rms_mean_A"] = mean(phase_rms)
        result["phase_current_rms_spread_percent"] = (
            100.0 * (max(phase_rms) - min(phase_rms)) / mean(phase_rms) if mean(phase_rms) > 1e-12 else math.nan
        )
    if "flux_valid" in rows[0]:
        result["flux_valid_percent"] = 100.0 * mean([1.0 if row["flux_valid"] >= 0.5 else 0.0 for row in rows])
    return result


def select_plateaus(rows: list[dict[str, float]], settle_s: float) -> dict[tuple[int, float, int], list[dict[str, float]]]:
    groups: dict[tuple[int, float, int], list[dict[str, float]]] = defaultdict(list)
    occurrences: dict[tuple[int, float], int] = defaultdict(int)
    last_key: tuple[int, float] | None = None
    active_group: tuple[int, float, int] | None = None
    entered_at = 0.0
    for row in sorted(rows, key=lambda item: item["time"]):
        mode = int(round(row["mode"]))
        nearest = min(PLATEAUS_HZ, key=lambda value: abs(row["frequency_ref"] - value))
        key = (mode, nearest) if abs(row["frequency_ref"] - nearest) <= 0.05 else None
        if key != last_key:
            entered_at = row["time"]
            last_key = key
            active_group = None
            if key is not None:
                occurrences[key] += 1
                active_group = (key[0], key[1], occurrences[key])
        if active_group is not None and row["time"] - entered_at >= settle_s:
            groups[active_group].append(row)
    return groups


def write_summary(path: Path, summaries: list[dict[str, float | str]]) -> None:
    fields: list[str] = []
    for summary in summaries:
        for field in summary:
            if field not in fields:
                fields.append(field)
    with path.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields)
        writer.writeheader()
        writer.writerows(summaries)


def write_report(path: Path, source: Path, summaries: list[dict[str, float | str]]) -> None:
    by_mode: dict[int, list[dict[str, float | str]]] = defaultdict(list)
    for summary in summaries:
        by_mode[int(summary["observer_mode"])].append(summary)
    lines = [
        "# IM observer validation report",
        "",
        f"Source: `{source}`",
        "",
        "This report checks repeatability and model consistency. Without an independent flux or torque reference it does **not** prove absolute estimator accuracy.",
        "",
        "| Observer | Plateaus | Frequency RMSE [Hz] | Angle-frequency RMSE [Hz] | Flux ripple [%] | Orbit axis ratio |",
        "|---|---:|---:|---:|---:|---:|",
    ]
    for mode in sorted(by_mode):
        values = by_mode[mode]
        lines.append(
            f"| {MODE_NAMES.get(mode, mode)} | {len(values)} | "
            f"{mean([float(item['stator_frequency_rmse_Hz']) for item in values]):.6g} | "
            f"{mean([float(item['angle_frequency_rmse_Hz']) for item in values]):.6g} | "
            f"{mean([float(item['flux_ripple_percent']) for item in values]):.6g} | "
            f"{mean([float(item['flux_orbit_axis_ratio']) for item in values]):.6g} |"
        )
    lines += [
        "",
        "Interpretation:",
        "",
        "- Lower frequency RMSE and flux ripple are preferable at identical plateaus.",
        "- An orbit axis ratio near 1 indicates a circular alpha/beta flux orbit; a low value indicates ellipticity or asymmetry.",
        "- Kalman innovations should be bounded and approximately zero-mean. A low innovation alone is not sufficient if the voltage or machine model is biased.",
        "- Compare positive and negative plateaus separately to expose sign and phase-order errors.",
    ]
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def write_plot(path: Path, rows: list[dict[str, float]]) -> bool:
    try:
        import matplotlib.pyplot as plt
    except ImportError:
        return False
    figure = plt.figure(figsize=(15, 9), constrained_layout=True)
    grid = figure.add_gridspec(2, 3, height_ratios=(1.0, 1.2))
    frequency_axis = figure.add_subplot(grid[0, :])
    orbit_axes = [figure.add_subplot(grid[1, index]) for index in range(3)]
    orbit_data: dict[int, tuple[list[float], list[float]]] = {}
    for mode, name in MODE_NAMES.items():
        selected = [row for row in rows if int(round(row["mode"])) == mode]
        if not selected:
            continue
        frequency_axis.plot(
            [row["time"] for row in selected],
            [row["stator_frequency"] for row in selected],
            label=name,
        )
        alpha = [row["flux_magnitude"] * math.cos(row["flux_angle"]) for row in selected]
        beta = [row["flux_magnitude"] * math.sin(row["flux_angle"]) for row in selected]
        orbit_data[mode] = (alpha, beta)

    maximum_flux = max(
        (abs(value) for components in orbit_data.values() for axis in components for value in axis),
        default=1.0,
    )
    orbit_limit = 1.05 * maximum_flux if maximum_flux > 0.0 else 1.0
    for orbit_axis, (mode, name) in zip(orbit_axes, MODE_NAMES.items()):
        if mode in orbit_data:
            alpha, beta = orbit_data[mode]
            orbit_axis.plot(alpha, beta, linewidth=0.6)
        else:
            orbit_axis.text(0.5, 0.5, "no samples", ha="center", va="center", transform=orbit_axis.transAxes)
        orbit_axis.set(
            title=name,
            xlabel="flux alpha [Vs]",
            ylabel="flux beta [Vs]",
            aspect="equal",
            xlim=(-orbit_limit, orbit_limit),
            ylim=(-orbit_limit, orbit_limit),
        )
        orbit_axis.grid(True)

    frequency_axis.set(xlabel="profile time [s]", ylabel="estimated stator frequency [Hz]")
    frequency_axis.grid(True)
    frequency_axis.legend()
    figure.savefig(path, dpi=160)
    plt.close(figure)
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("csv", type=Path, help="JavaScope FastData CSV")
    parser.add_argument("--output-dir", type=Path, default=Path("im_observer_validation_results"))
    parser.add_argument("--settle-s", type=float, default=1.0, help="discard this time after entering each plateau")
    args = parser.parse_args()
    rows, columns = read_log(args.csv)
    groups = select_plateaus(rows, args.settle_s)
    summaries = [summarize_group(mode, target, occurrence, values)
                 for (mode, target, occurrence), values in sorted(groups.items()) if len(values) >= 3]
    if not summaries:
        raise ValueError("No stationary profile plateaus found; check selected JavaScope channels and logging duration")
    args.output_dir.mkdir(parents=True, exist_ok=True)
    write_summary(args.output_dir / "plateau_metrics.csv", summaries)
    write_report(args.output_dir / "report.md", args.csv, summaries)
    plotted = write_plot(args.output_dir / "overview.png", rows)
    print("Detected columns:")
    for signal, column in columns.items():
        print(f"  {signal}: {column}")
    print(f"Wrote {len(summaries)} plateau summaries to {args.output_dir}")
    if not plotted:
        print("matplotlib not installed; skipped overview.png")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
