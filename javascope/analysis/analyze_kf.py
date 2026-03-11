"""
Kalman Filter whiteness test and tuning analysis for UltraZohm JavaScope logs.

Run:
    python analyze_kf.py <path_to_csv>

Outputs:
- Innovation statistics and whiteness test (AC at multiple lags)
- S/K convergence check
- Back-calculated effective R
- Tuning recommendation (adjust Q_i to make AC(1) -> 0)
"""

import sys
import os
import math
import argparse

sys.path.insert(0, os.path.dirname(__file__))
from load_log import load_log, mean, std, autocorr, stats_summary


def _section(title):
    print()
    print('=' * 60)
    print(f'  {title}')
    print('=' * 60)


def analyze_kf_whiteness(data, fs):
    _section("KF INNOVATION WHITENESS TEST")

    for ch in ['kf_innov_alpha', 'kf_innov_beta']:
        if ch not in data:
            print(f"  {ch} not available in this log")
            continue
        arr = data[ch]
        mu, sd_val, mn, mx = stats_summary(arr)
        print(f"  {ch}:")
        print(f"    mean={mu:.6f} A  std={sd_val:.6f} A  (std/A ideal: set by R)")
        print(f"    Autocorrelation:")
        for lag in [1, 2, 5, 10, 25, 50]:
            ac = autocorr(arr, lag)
            verdict = ""
            if lag == 1:
                if abs(ac) < 0.1:
                    verdict = "  [WHITE - OK]"
                elif ac > 0:
                    verdict = "  [POSITIVE - Q too small, increase Q_i]"
                else:
                    verdict = "  [NEGATIVE - Q too large, decrease Q_i]"
            print(f"      AC(lag={lag:3d}): {ac:+.4f}{verdict}")
        print()


def analyze_kf_convergence(data, fs):
    _section("KF CONVERGENCE")
    for ch in ['kf_S_00', 'kf_S_11', 'kf_K_00', 'kf_K_11']:
        if ch not in data:
            continue
        mu, sd_val, mn, mx = stats_summary(data[ch])
        pct = sd_val / abs(mu) * 100 if abs(mu) > 1e-10 else float('nan')
        print(f"  {ch}: mean={mu:.6f}  std/mean={pct:.3f}%  [{mn:.6f}, {mx:.6f}]")

    # Back-calculate effective R from S and K
    # S00 = H*P*H' + R, K00 = P*H'*S00^{-1}
    # -> P[0,0] = K00 * S00, R_eff ≈ S00 - P[0,0] = S00 * (1 - K00)
    if 'kf_S_00' in data and 'kf_K_00' in data:
        S = mean(data['kf_S_00'])
        K = mean(data['kf_K_00'])
        R_eff = S * (1.0 - K)
        print()
        print(f"  Back-calculated R_eff = S00*(1-K00) = {S:.6f}*(1-{K:.4f}) = {R_eff:.6f} A^2")
        print(f"  sqrt(R_eff) = {math.sqrt(max(R_eff,0)):.5f} A  (= sigma_i noise std)")


def analyze_kf_tuning(data, fs):
    _section("KF TUNING RECOMMENDATION")

    for ch in ['kf_innov_alpha', 'kf_innov_beta']:
        if ch not in data:
            continue
        arr = data[ch]
        ac1 = autocorr(arr, 1)
        print(f"  {ch}: AC(1) = {ac1:+.4f}")
        if abs(ac1) < 0.10:
            print("    -> Filter is well-tuned (|AC(1)| < 0.10)")
        elif ac1 > 0.10:
            factor = 1.0 + 4.0 * ac1   # empirical: multiply Q by (1 + 4*AC1)
            print(f"    -> Positive correlation: Q_i likely too small")
            print(f"    -> Suggested Q_i multiplier: x{factor:.2f}")
        else:
            factor = 1.0 / (1.0 + 4.0 * abs(ac1))
            print(f"    -> Negative correlation: Q_i likely too large")
            print(f"    -> Suggested Q_i multiplier: x{factor:.2f}")
    print()


def main():
    parser = argparse.ArgumentParser(description='KF whiteness and tuning analysis')
    parser.add_argument('log', help='Path to JavaScope CSV log file')
    args = parser.parse_args()

    data, fs = load_log(args.log)
    t = data['time']
    print(f"Log: {os.path.basename(args.log)}")
    print(f"  {len(t)} samples,  {t[-1]-t[0]:.2f} s,  fs={fs:.0f} Hz")

    analyze_kf_whiteness(data, fs)
    analyze_kf_convergence(data, fs)
    analyze_kf_tuning(data, fs)


if __name__ == '__main__':
    main()
