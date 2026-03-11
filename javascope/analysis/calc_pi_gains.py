"""
PI gain calculator for induction motor FOC current and speed controllers.

Reads motor parameters directly from motor_config.h (no separate JSON needed).

Usage:
    python calc_pi_gains.py [--motor-config path/to/motor_config.h] [--Ts 40e-6]
    python calc_pi_gains.py --motor-config ../../vitis/.../motor_config.h --Ts 40e-6

Methods:
    Current PI:  Symmetric optimum
        kp_base = sigma_Ls / (2*Ts),  ki_base = Rs / (2*Ts)
        Firmware multiplies by MOTOR_Current_Kp_scale / MOTOR_Current_Ki_scale.

    Speed PI:    Asymmetric optimum
        tau_i  = sigma_Ls / (Rs * kp_scale)  [current closed-loop time constant]
        kp_spd = J / (2 * pole_pairs * tau_i)
        ki_spd = kp_spd / (4 * tau_i)

Output: motor_config.h snippet ready to paste.
"""

import argparse
import math
import sys

sys.stdout.reconfigure(encoding='utf-8')
sys.path.insert(0, __import__('os').path.dirname(__file__))
from parse_motor_config import load_motor_config


def main():
    parser = argparse.ArgumentParser(
        description='Compute IM FOC PI gains from motor_config.h parameters.')
    parser.add_argument('--motor-config', metavar='FILE',
                        help='Path to motor_config.h '
                             '(default: auto-detect relative to script location)')
    parser.add_argument('--Ts', type=float, default=None,
                        help='ISR sampling period [s] '
                             '(default: 1/UZ_PWM_FREQUENCY; reads from uz_global_configuration.h '
                             'if not supplied — fallback 40e-6 = 25 kHz)')
    parser.add_argument('--kp-scale', type=float, default=None,
                        help='Override MOTOR_Current_Kp_scale for BW estimation')
    parser.add_argument('--ki-scale', type=float, default=None,
                        help='Override MOTOR_Current_Ki_scale for BW estimation')
    args = parser.parse_args()

    # --- Load motor params ---------------------------------------------------
    try:
        cfg = load_motor_config(args.motor_config)
    except (FileNotFoundError, ValueError, KeyError) as e:
        print(f"ERROR: {e}", file=sys.stderr)
        sys.exit(1)

    print(f"[motor_config] {cfg['_source']}")
    print(f"[active]       {cfg['_active_config']}\n")

    rs       = cfg['Rs_Ohm']
    lr       = cfg['Lr_H']
    sigma_ls = cfg['sigma_Ls_H']
    tau_r    = cfg['tau_r_s']
    J        = cfg['J_kgm2']
    pp       = int(round(cfg['PolePairs']))

    kp_scale = args.kp_scale if args.kp_scale is not None else cfg['Current_Kp_scale']
    ki_scale = args.ki_scale if args.ki_scale is not None else cfg['Current_Ki_scale']

    # --- Sampling time -------------------------------------------------------
    Ts = args.Ts
    if Ts is None:
        # Try to read UZ_PWM_FREQUENCY from uz_global_configuration.h
        import os, re
        cfg_dir = os.path.dirname(cfg['_source'])
        uz_cfg  = os.path.normpath(os.path.join(cfg_dir, '..', 'uz', 'uz_global_configuration.h'))
        if os.path.isfile(uz_cfg):
            with open(uz_cfg) as f:
                for line in f:
                    m = re.match(r'\s*#define\s+UZ_PWM_FREQUENCY\s+([\d.e+\-]+)', line)
                    if m:
                        Ts = 1.0 / float(m.group(1))
                        print(f"[Ts] read from uz_global_configuration.h: "
                              f"UZ_PWM_FREQUENCY={1/Ts:.0f} Hz → Ts={Ts*1e6:.1f} µs")
                        break
        if Ts is None:
            Ts = 40e-6
            print(f"[Ts] uz_global_configuration.h not found; using default 40 µs (25 kHz)")

    # --- Current PI ----------------------------------------------------------
    kp_base    = sigma_ls / (2.0 * Ts)
    ki_base    = rs       / (2.0 * Ts)
    kp_actual  = kp_base * kp_scale
    ki_actual  = ki_base * ki_scale
    bw_rad     = kp_actual / sigma_ls
    bw_hz      = bw_rad / (2 * math.pi)
    tau_i      = 1.0 / bw_rad            # effective current loop time constant

    print(f"--- Motor derived parameters ---")
    print(f"  sigma_Ls = {sigma_ls*1e3:.4f} mH   tau_r = {tau_r*1e3:.2f} ms")
    print(f"  Ts       = {Ts*1e6:.1f} µs  ({1/Ts:.0f} Hz)")

    print(f"\n--- Current PI (symmetric optimum) ---")
    print(f"  kp_base = sigma_Ls / (2*Ts) = {kp_base:.4f}")
    print(f"  ki_base = Rs       / (2*Ts) = {ki_base:.4f}")
    print(f"  Active scales: Kp×{kp_scale}  Ki×{ki_scale}")
    print(f"  → kp_actual = {kp_actual:.5f}   ki_actual = {ki_actual:.5f}")
    print(f"  → approx current BW: {bw_hz:.1f} Hz  (τ_i ≈ {tau_i*1e3:.2f} ms)")

    # Sanity checks
    plant_tau = sigma_ls / rs
    if Ts > plant_tau:
        print(f"  WARNING: Ts ({Ts*1e6:.0f} µs) > plant τ ({plant_tau*1e6:.0f} µs) — "
              f"reduce kp_scale (try 0.01–0.05)")
    elif bw_hz > 1.0 / (4.0 * Ts) / (2 * math.pi):
        print(f"  WARNING: BW {bw_hz:.0f} Hz > quarter-ISR rule "
              f"({1/(4*Ts*2*math.pi):.0f} Hz) — reduce kp_scale")
    else:
        print(f"  Current BW within quarter-ISR rule — OK")

    # --- Speed PI (unit-aware) -----------------------------------------------
    # The firmware speed PI:
    #   input  = speed_ref_rpm − Speed_rpm  [RPM]
    #   output = iq_cmd_A                   [A]
    #
    # Plant: K_T [Nm/A] × (60/(2π)) [RPM·s/rad] / (J [kg·m²] × s)
    #   = K_plant [RPM/(A·s)]
    #
    # K_T = (3/2) × pp × (Lm/Lr) × Psi_rated   [Nm/A]
    psi_rated = cfg['Psi_rated_Vs']
    K_T       = 1.5 * pp * (cfg['Lm_H'] / lr) * psi_rated   # Nm/A
    K_plant   = K_T * (60.0 / (2.0 * math.pi)) / J           # RPM/(A·s)

    # Asymmetric optimum: kp = 1 / (2 × τ_i × K_plant) [A/RPM]
    #                     ki = kp / (4 × τ_i)            [A/(RPM·s)] (continuous)
    kp_spd_theory = 1.0 / (2.0 * tau_i * K_plant)
    ki_spd_theory = kp_spd_theory / (4.0 * tau_i)
    spd_bw_hz     = kp_spd_theory * K_plant / (2.0 * math.pi)

    # Recommend starting at 5 % of theoretical (motor inertia often underestimated,
    # digital implementation effects; increase empirically)
    kp_spd = kp_spd_theory * 0.05
    ki_spd = ki_spd_theory * 0.05

    print(f"\n--- Speed PI (asymmetric optimum, RPM→A unit system) ---")
    print(f"  J={J:.4f} kg·m²   pp={pp}   τ_i={tau_i*1e3:.2f} ms")
    print(f"  K_T   = (3/2)×pp×(Lm/Lr)×Ψ_rated = {K_T:.4f} Nm/A")
    print(f"  K_plant = K_T×(60/2π)/J           = {K_plant:.2f} RPM/(A·s)")
    print(f"  Theoretical:  kp = {kp_spd_theory:.5f} A/RPM   ki = {ki_spd_theory:.3f} A/(RPM·s)")
    print(f"  → approx speed BW (theoretical):  {spd_bw_hz:.2f} Hz")
    print(f"  Safe start (5% of theoretical): kp = {kp_spd:.6f}   ki = {ki_spd:.6f}")
    print(f"  Increase kp slowly (2× steps) watching Speed_rpm oscillation in JavaScope.")

    # --- motor_config.h snippet ----------------------------------------------
    print(f"\n--- Paste into motor_config.h ---")
    print(f"  #define MOTOR_Current_Kp_scale    {kp_scale}f")
    print(f"  #define MOTOR_Current_Ki_scale    {ki_scale}f")
    print(f"  #define MOTOR_Speed_Kp            {kp_spd:.6f}f   /* 5% of theoretical; increase empirically */")
    print(f"  #define MOTOR_Speed_Ki            {ki_spd:.6f}f")


if __name__ == '__main__':
    main()
