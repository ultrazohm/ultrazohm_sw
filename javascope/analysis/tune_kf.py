"""
Iterative KF Q/R tuner for UltraZohm induction motor observer.

Usage:
    python tune_kf.py <log.csv> [--motor-config path/to/motor_config.h]
                                [--q-i 1e-5] [--q-psi 1e-7] [--r-i 5e-2]

Workflow:
    1. Run a steady-state log with KF active (MB6 on) at your operating point.
    2. Run this script — it prints suggested SF9/SF7/SF8 values.
    3. Enter those values in JavaScope, log again, repeat.
    4. Stop when AC(1) < 0.10 (innovation is white noise) — copy final values to motor_config.h.

The tuning heuristic:
    AC(1) = lag-1 autocorrelation of kf_innov_alpha.
    - AC(1) >> 0: innovations are correlated → Q_i too small → increase Q_i
    - AC(1) << 0: innovations are over-driven → Q_i too large → decrease Q_i
    - |AC(1)| < 0.10: converged

    Q_i update: Q_i_new = Q_i_old * (1 + 4 * AC(1))    (clamped to [Q_i/10, Q_i*10])
    Q_psi: only touched if psi_r_mag drifts slowly (slow trend in psi_r_mag)
    R_i:   only touched if innovation std >> current noise floor (sensor noise level)
"""

import argparse
import math
import os
import sys

import numpy as np

sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')
sys.path.insert(0, os.path.dirname(__file__))
from load_log import load_log
from parse_motor_config import load_motor_config
from jso_channels import parse_jso_enum, print_ini_section

# Channels required for a KF tuning log
_CHANNELS_KF_TUNE = [
    'ia', 'ib', 'ic',
    'id', 'iq',
    'id_cmd', 'iq_cmd',
    'psi_r_mag',
    'omega_s_rad_s',
    'kf_innov_alpha', 'kf_innov_beta',
    'kf_S_00', 'kf_S_11',
    'kf_K_00', 'kf_K_11',
    'omega_slip_rad_s',
    'Speed_rpm',
    'ud_pi',
    'Theta_el',
    'det_psi_r_alpha',
]


def _ac1(arr):
    """Lag-1 autocorrelation."""
    if len(arr) < 3:
        return 0.0
    return float(np.corrcoef(arr[:-1], arr[1:])[0, 1])


def _amp_at(arr, freq, fs):
    """Single-bin DFT amplitude (two-sided peak) at one frequency."""
    x = arr - arr.mean()
    n = len(x)
    t = np.arange(n) / fs
    re = np.mean(x * np.cos(2 * math.pi * freq * t)) * 2
    im = np.mean(x * np.sin(2 * math.pi * freq * t)) * 2
    return float(math.sqrt(re**2 + im**2))


def main():
    parser = argparse.ArgumentParser(
        description='Iterative KF Q/R tuner from JavaScope log.')
    parser.add_argument('log', nargs='?',
                        help='JavaScope CSV log file (KF active, steady state). '
                             'Omit when using --print-channels.')
    parser.add_argument('--motor-config', metavar='FILE',
                        help='Path to motor_config.h (auto-detected if not supplied)')
    parser.add_argument('--print-channels', action='store_true',
                        help='Print properties.ini channel preset for KF tuning and exit')
    parser.add_argument('--q-i',   type=float, default=None,
                        help='Current Q_i used in this run (overrides motor_config.h default)')
    parser.add_argument('--q-psi', type=float, default=None,
                        help='Current Q_psi used in this run (overrides motor_config.h default)')
    parser.add_argument('--r-i',   type=float, default=None,
                        help='Current R_i used in this run (overrides motor_config.h default)')
    args = parser.parse_args()

    # --- Print channel preset and exit ---------------------------------------
    if args.print_channels:
        try:
            jso = parse_jso_enum()
        except FileNotFoundError as e:
            print(f"ERROR: {e}", file=sys.stderr)
            sys.exit(1)
        print("Required GUI state for KF tuning log:")
        print("  MB4 ON (FOC), MB6 ON (KF active), MB5 optional")
        print("  Run at steady speed with rated flux and some load (iq ≈ 0.3× rated)")
        print("  Log ≥ 10 s at steady state")
        print()
        print_ini_section("tune_kf.py — KF tuning log", _CHANNELS_KF_TUNE, jso)
        return

    if not args.log:
        parser.error("a log file is required (or use --print-channels)")

    # --- Load motor config for Q/R defaults ----------------------------------
    try:
        cfg = load_motor_config(args.motor_config)
        Q_i   = args.q_i   if args.q_i   is not None else cfg['KF_Q_i']
        Q_psi = args.q_psi if args.q_psi is not None else cfg['KF_Q_psi']
        R_i   = args.r_i   if args.r_i   is not None else cfg['KF_R_i']
        print(f"[motor_config] {cfg['_source']}  [{cfg['_active_config']}]")
    except FileNotFoundError:
        if args.motor_config:
            print(f"ERROR: motor_config.h not found: {args.motor_config}", file=sys.stderr)
            sys.exit(1)
        Q_i   = args.q_i   if args.q_i   is not None else 1e-5
        Q_psi = args.q_psi if args.q_psi is not None else 1e-7
        R_i   = args.r_i   if args.r_i   is not None else 5e-2
        print("[motor_config] not found — using CLI / hardcoded defaults")

    print(f"[Q/R current]  Q_i={Q_i:.3e}  Q_psi={Q_psi:.3e}  R_i={R_i:.3e}\n")

    # --- Load log ------------------------------------------------------------
    data, fs = load_log(args.log)
    name = os.path.basename(args.log)

    required = ['kf_innov_alpha', 'kf_innov_beta', 'kf_K_00', 'kf_K_11']
    missing  = [c for c in required if c not in data]
    if missing:
        print(f"ERROR: {name} is missing channels: {missing}", file=sys.stderr)
        print("       Was the KF active (MB6 on) during this recording?", file=sys.stderr)
        sys.exit(1)

    innov_a = np.asarray(data['kf_innov_alpha'])
    innov_b = np.asarray(data['kf_innov_beta'])
    K00     = np.asarray(data['kf_K_00'])
    K11     = np.asarray(data['kf_K_11'])
    N       = len(innov_a)

    omega_s  = np.asarray(data.get('omega_s_rad_s', np.zeros(N)))
    psi_mag  = np.asarray(data.get('psi_r_mag',     np.ones(N)))
    speed    = np.asarray(data.get('Speed_rpm',     np.zeros(N)))
    t        = np.asarray(data.get('time',          np.arange(N) / fs))
    dur      = t[-1] - t[0]

    f_el  = float(omega_s.mean()) / (2 * math.pi)
    f_mec = float(speed.mean()) / 60.0

    print(f"=== {name}  N={N}  dur={dur:.2f} s  fs={fs:.0f} Hz ===")
    print(f"    Speed={speed.mean():.1f} RPM   f_el={f_el:.2f} Hz")

    # --- Innovation statistics -----------------------------------------------
    ac1_a = _ac1(innov_a)
    ac1_b = _ac1(innov_b)
    ac1   = (ac1_a + ac1_b) / 2.0

    amp6_a = _amp_at(innov_a, 6 * f_el, fs) if f_el > 0.5 else 0.0
    amp6_b = _amp_at(innov_b, 6 * f_el, fs) if f_el > 0.5 else 0.0

    K00_mean = float(K00.mean())
    K11_mean = float(K11.mean())
    K_conv   = K00.std() / abs(K00_mean) < 0.01 if K00_mean != 0 else False

    print(f"\n--- Innovation analysis ---")
    print(f"  innov_α:  mean={innov_a.mean():+.5f} A  std={innov_a.std():.5f} A  AC(1)={ac1_a:+.3f}  amp@6f={amp6_a:.5f} A")
    print(f"  innov_β:  mean={innov_b.mean():+.5f} A  std={innov_b.std():.5f} A  AC(1)={ac1_b:+.3f}  amp@6f={amp6_b:.5f} A")
    print(f"  K[0][0]:  mean={K00_mean:.5f}  std/mean={K00.std()/abs(K00_mean)*100:.2f}%  "
          f"[{'CONVERGED' if K_conv else 'DRIFTING'}]")
    print(f"  K[1][1]:  mean={K11_mean:.5f}")

    # Dominant-6th fraction: is the 6th harmonic the main source of correlation?
    a6_norm_a = amp6_a / innov_a.std() if innov_a.std() > 0 else 0.0
    a6_norm_b = amp6_b / innov_b.std() if innov_b.std() > 0 else 0.0
    sixth_dominant = (a6_norm_a > 0.3 or a6_norm_b > 0.3)

    # --- psi_r drift check ---------------------------------------------------
    # Fit linear trend to psi_r_mag; if slope > 0.1 Vs/s, suggest increasing Q_psi
    p_psi = np.polyfit(t, psi_mag, 1)
    psi_drift_vs_per_s = p_psi[0]
    psi_drift_significant = abs(psi_drift_vs_per_s) > 0.1

    # --- R_i check -----------------------------------------------------------
    # R_eff = S*(1-K) ≈ measurement noise variance
    # If S is logged use it; otherwise estimate from innovation std
    if 'kf_S_00' in data:
        S00 = float(np.asarray(data['kf_S_00']).mean())
        R_eff = S00 * (1.0 - K00_mean)
        print(f"  R_eff = {R_eff:.6f} A²   √R_eff = {math.sqrt(max(R_eff, 0)):.5f} A  "
              f"(expected ≈ √R_i = {math.sqrt(R_i):.4f} A)")
    else:
        R_eff = None

    # --- Diagnosis -----------------------------------------------------------
    print(f"\n--- Diagnosis ---")

    if abs(ac1) < 0.10:
        print(f"  AC(1) = {ac1:+.3f} — innovations are WHITE NOISE. KF is well-tuned.")
        q_i_new   = Q_i
        q_psi_new = Q_psi
        r_i_new   = R_i
        converged = True
    else:
        converged = False
        if ac1 > 0.90 or sixth_dominant:
            print(f"  AC(1) = {ac1:+.3f} — strongly correlated.")
            if sixth_dominant:
                print(f"  6th harmonic dominant (amp/std ≈ {max(a6_norm_a, a6_norm_b):.2f}).")
                print(f"  → This is unmodeled deadtime disturbance. Enable resonant controller (MB8).")
                print(f"     Increasing Q_i alone will NOT fix this; it will just increase Kalman gain.")
            else:
                print(f"  → Persistent unknown disturbance. Increase Q_i moderately.")
        elif ac1 > 0.10:
            if sixth_dominant:
                print(f"  AC(1) = {ac1:+.3f}  6th harmonic contributing — enable resonant controller (MB8).")
            else:
                factor = 1.0 + 4.0 * ac1
                print(f"  AC(1) = {ac1:+.3f} — under-driven. Suggest Q_i × {factor:.2f}")
        else:
            factor = 1.0 / (1.0 + 4.0 * abs(ac1))
            print(f"  AC(1) = {ac1:+.3f} — over-driven (too noisy). Suggest Q_i × {factor:.2f}")

        # Compute new Q_i
        if abs(ac1) >= 0.10 and not (ac1 > 0.90 and not sixth_dominant):
            factor = 1.0 + 4.0 * ac1
        else:
            factor = 1.0 + 4.0 * ac1   # still apply, but note it may not help
        factor = max(0.1, min(10.0, factor))
        q_i_new = Q_i * factor

        # Q_psi
        if psi_drift_significant:
            psi_factor = 2.0 if psi_drift_vs_per_s > 0 else 0.5
            q_psi_new = Q_psi * psi_factor
            print(f"  psi_r drift {psi_drift_vs_per_s:+.3f} Vs/s → adjust Q_psi × {psi_factor}")
        else:
            q_psi_new = Q_psi

        # R_i
        if R_eff is not None:
            r_ratio = R_eff / R_i
            if r_ratio > 2.0:
                print(f"  R_eff/R_i = {r_ratio:.2f} > 2 → measurement noisier than expected; increase R_i × 2")
                r_i_new = R_i * 2.0
            elif r_ratio < 0.5:
                print(f"  R_eff/R_i = {r_ratio:.2f} < 0.5 → KF over-trusts model; decrease R_i × 0.5")
                r_i_new = R_i * 0.5
            else:
                r_i_new = R_i
        else:
            r_i_new = R_i

    # --- Suggested values ----------------------------------------------------
    print(f"\n--- Suggested next values ---")
    print(f"  SF9  (Q_i)   = {q_i_new:.3e}   (current: {Q_i:.3e})")
    print(f"  SF7  (Q_psi) = {q_psi_new:.3e}   (current: {Q_psi:.3e})")
    print(f"  SF8  (R_i)   = {r_i_new:.3e}   (current: {R_i:.3e})")

    if converged:
        print(f"\n--- Converged — paste into motor_config.h ---")
        print(f"  #define MOTOR_KF_Q_i              {Q_i:.2e}f")
        print(f"  #define MOTOR_KF_Q_psi            {Q_psi:.2e}f")
        print(f"  #define MOTOR_KF_R_i              {R_i:.2e}f")
    else:
        print(f"\n  → Enter SF9/SF7/SF8 in JavaScope, run another log, repeat.")
        print(f"    Target: |AC(1)| < 0.10")


if __name__ == '__main__':
    main()
