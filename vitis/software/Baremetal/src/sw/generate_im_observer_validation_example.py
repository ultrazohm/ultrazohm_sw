#!/usr/bin/env python3
"""Generate a compact, deterministic JavaScope-style observer validation log."""

from __future__ import annotations

import argparse
import csv
import math
from pathlib import Path


MODES = ((0, "deterministic"), (1, "full Kalman"), (2, "simplified Kalman"))
FREQUENCIES_HZ = (-2.0, 2.0, 6.0)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "output",
        nargs="?",
        type=Path,
        default=Path("im_observer_validation_example.csv"),
    )
    args = parser.parse_args()
    args.output.parent.mkdir(parents=True, exist_ok=True)

    headers = [
        "time", "IM_VALIDATION_OBSERVER_MODE", "IM_VALIDATION_PROFILE_STAGE",
        "IM_FREQUENCY_HZ", "IM_SPEED_RPM", "IM_I_A", "IM_I_B", "IM_I_C",
        "IM_FLUX_VS", "IM_FLUX_ANGLE_RAD", "IM_STATOR_FREQUENCY_HZ",
        "IM_ROTOR_ELECTRICAL_FREQUENCY_HZ", "IM_SLIP_FREQUENCY_HZ",
        "IM_KALMAN_INNOVATION_ALPHA_A", "IM_KALMAN_INNOVATION_BETA_A",
        "IM_I_D", "IM_I_Q", "IM_ROTOR_FLUX_VALID", "IM_FLUX_ANGLE_STEP_RAD",
        "IM_PHASE_CURRENT_SUM_A",
    ]
    time_s = 0.0
    # 20 Hz is deliberately above twice the largest 6 Hz test
    # frequency. A lower logging rate would alias the angle derivative used
    # by the validation tool.
    dt_s = 0.05
    rows: list[dict[str, float]] = []
    for mode, _ in MODES:
        for frequency_hz in FREQUENCIES_HZ:
            # Four seconds per plateau leave three evaluated seconds after the
            # analyzer's default one-second settling interval.
            for sample in range(80):
                angle = 2.0 * math.pi * frequency_hz * time_s
                electrical_phase = 2.0 * math.pi * frequency_hz * time_s
                current_peak = 0.55 + 0.08 * abs(frequency_hz)
                mode_ripple = (0.010, 0.007, 0.005)[mode]
                ripple = mode_ripple * math.sin(6.0 * electrical_phase + 0.3 * mode)
                flux_mean = 0.30 + 0.025 * abs(frequency_hz)
                flux = flux_mean * (1.0 + ripple)
                frequency_noise = (0.020, 0.012, 0.026)[mode] * math.sin(0.37 * sample)
                innovation_scale = (0.0, 0.035, 0.020 + 0.008 * abs(frequency_hz))[mode]
                i_a = current_peak * math.sin(electrical_phase)
                i_b = current_peak * math.sin(electrical_phase - 2.0 * math.pi / 3.0)
                i_c = -i_a - i_b + 0.002 * math.sin(0.71 * sample)
                rows.append({
                    "time": time_s,
                    "IM_VALIDATION_OBSERVER_MODE": mode,
                    "IM_VALIDATION_PROFILE_STAGE": 3 if frequency_hz > 0.0 else 4,
                    "IM_FREQUENCY_HZ": frequency_hz,
                    "IM_SPEED_RPM": frequency_hz * 30.0 * 0.98,
                    "IM_I_A": i_a,
                    "IM_I_B": i_b,
                    "IM_I_C": i_c,
                    "IM_FLUX_VS": flux,
                    "IM_FLUX_ANGLE_RAD": math.atan2(math.sin(angle), math.cos(angle)),
                    "IM_STATOR_FREQUENCY_HZ": frequency_hz + frequency_noise,
                    "IM_ROTOR_ELECTRICAL_FREQUENCY_HZ": 0.98 * frequency_hz,
                    "IM_SLIP_FREQUENCY_HZ": 0.02 * frequency_hz,
                    "IM_KALMAN_INNOVATION_ALPHA_A": innovation_scale * math.sin(electrical_phase + 0.2),
                    "IM_KALMAN_INNOVATION_BETA_A": innovation_scale * math.cos(electrical_phase + 0.2),
                    "IM_I_D": current_peak,
                    "IM_I_Q": 0.03 * frequency_hz,
                    "IM_ROTOR_FLUX_VALID": 1.0,
                    "IM_FLUX_ANGLE_STEP_RAD": 2.0 * math.pi * frequency_hz * dt_s,
                    "IM_PHASE_CURRENT_SUM_A": i_a + i_b + i_c,
                })
                time_s += dt_s

    with args.output.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=headers)
        writer.writeheader()
        writer.writerows(rows)
    print(f"Wrote {len(rows)} samples to {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
