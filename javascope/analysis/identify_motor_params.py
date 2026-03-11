"""
Motor parameter extraction from JavaScope logs.

All identified parameters are STAR-EQUIVALENT (per-phase, referred to neutral).
This holds regardless of whether the motor windings are physically star or delta
connected: the inverter drives line-to-neutral voltages and the ADC measures line
currents, so the terminal quantities used here already represent the star-equivalent
per-phase model. No Δ→Y conversion is needed after running these tests.

Three tests cover the unknown machine parameters:

  Test A — Rs (stator resistance)
    V/f mode at very low frequency (0.3–0.5 Hz), motor at standstill.
    At low omega_s the decoupling is negligible → ud_pi ≈ Rs × id.
    Rs = mean(ud_pi) / mean(id)
    Correction: Rs = (mean(ud_pi) + mean(omega_s) * sigma_Ls * mean(iq)) / mean(id)
    (the corrected form uses sigma_Ls from motor_config.h if available)

    Required GUI state:
      - MB4 OFF (V/f mode), MB5 OFF, MB6 OFF
      - SF1 = 0.3 Hz (slow enough to lock the rotor)
      - SF2 (id_ref) = rated value (motor must carry rated flux during test)
      - Log for ≥ 5 s once currents have settled

    Required channels (use --print-channels Rs for the ini preset):
      ia  ib  ic         — verify three-phase currents
      id  iq             — d/q currents at flux angle
      ud_pi              — d-axis PI output (≈ Rs × id at low omega_s)
      omega_s_rad_s      — stator frequency  (verify < 5 rad/s)
      Speed_rpm          — mechanical speed  (verify ≈ 0)
      ud  uq             — applied dq voltages (optional cross-check)

  Test B — Lm (magnetizing inductance)
    FOC active (MB4 ON), no load (iq ≈ 0, SF3 = 0), motor spinning at low speed.
    Measure psi_r_mag vs id at several id_ref steps.
    Lm = mean(psi_r_mag) / mean(id)   [linear region, id < 0.7 × rated]

    Required GUI state:
      - MB4 ON (FOC), MB5 OFF, MB6 OFF
      - SF3 = 0 (no torque)
      - Run at 2–3 Hz with SF2 varied from 0.3× to 1.0× rated id in steps
      - Log ≥ 3 s per step (or log one continuous ramp and let the script split it)

    Required channels (use --print-channels Lm for the ini preset):
      ia  ib  ic         — verify three-phase currents
      id  iq  id_cmd     — d-axis operating point
      psi_r_mag          — flux magnitude (key output)
      omega_s_rad_s      — stator frequency
      Speed_rpm          — mechanical speed

  Test C — Rr (rotor resistance)
    FOC active (MB4 ON), steady load (iq > 0) at a known operating point.
    Slip frequency: omega_slip = (Rr / Lr) × (iq / id)  → Rr = omega_slip × Lr × id / iq
    Lr comes from motor_config.h (Lm + Lsigma_r).

    Required GUI state:
      - MB4 ON (FOC), MB5 OFF, MB6 OFF
      - SF2 = rated id, SF3 = 0.3–0.5 × rated iq (load the motor mechanically or electrically)
      - Log ≥ 5 s at steady state (constant speed, constant currents)

    Required channels (use --print-channels Rr for the ini preset):
      ia  ib  ic              — verify three-phase currents
      id  iq  id_cmd  iq_cmd  — d/q operating point
      psi_r_mag               — flux magnitude
      omega_s_rad_s           — stator frequency
      omega_slip_rad_s        — slip frequency (key output; JSO_omega_slip_rad_s)
      Speed_rpm               — mechanical speed

Usage:
    python identify_motor_params.py --Rs  <standstill_log.csv>
                                    --Lm  <noload_log.csv>
                                    --Rr  <loaded_log.csv>
                                    [--motor-config path/to/motor_config.h]
                                    [--print-channels Rs|Lm|Rr|all]

    # Just print properties.ini presets without any log:
    python identify_motor_params.py --print-channels all
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

# ---- Channel sets for each test (ordered for 20-ch ini preset) --------------

_CHANNELS_Rs = [
    'ia', 'ib', 'ic',
    'id', 'iq',
    'ud_pi',
    'omega_s_rad_s',
    'Speed_rpm',
    'ud', 'uq',
]

_CHANNELS_Lm = [
    'ia', 'ib', 'ic',
    'id', 'iq', 'id_cmd',
    'psi_r_mag',
    'omega_s_rad_s',
    'Speed_rpm',
    'Theta_el',
]

_CHANNELS_Rr = [
    'ia', 'ib', 'ic',
    'id', 'iq', 'id_cmd', 'iq_cmd',
    'psi_r_mag',
    'omega_s_rad_s',
    'omega_slip_rad_s',
    'Speed_rpm',
]


# ---- Helpers ----------------------------------------------------------------

def _check_channels(data, required, test_name):
    missing = [c for c in required if c not in data]
    if missing:
        print(f"ERROR [{test_name}]: missing channels in log: {missing}", file=sys.stderr)
        print(f"  Was the scope configured with --print-channels {test_name}?", file=sys.stderr)
        return False
    return True


def _steady_slice(arr_dict, keys, fs, window_s=2.0):
    """
    Find the steadiest window_s window across all channels in keys.
    Returns a dict of numpy arrays trimmed to that window.
    Criterion: minimum sum of standard deviations.
    """
    n = len(arr_dict[keys[0]])
    w = max(1, int(window_s * fs))
    if n <= w:
        return {k: arr_dict[k] for k in keys}

    best_i, best_score = 0, float('inf')
    for i in range(0, n - w, max(1, w // 10)):
        score = sum(arr_dict[k][i:i + w].std() for k in keys)
        if score < best_score:
            best_score, best_i = score, i

    return {k: arr_dict[k][best_i:best_i + w] for k in keys}


# ---- Test A: Rs -------------------------------------------------------------

def identify_Rs(path, sigma_ls=None):
    """
    Estimate stator resistance Rs from a low-frequency V/f log.

    Returns
    -------
    dict with 'Rs_Ohm', 'Rs_corrected_Ohm', diagnostics
    """
    print(f"\n{'='*60}\n  Test A — Rs identification\n  Log: {os.path.basename(path)}\n{'='*60}")

    data, fs = load_log(path)
    if not _check_channels(data, ['id', 'ud_pi', 'omega_s_rad_s'], 'Rs'):
        return None

    np_data = {k: np.asarray(v) for k, v in data.items()}
    ss = _steady_slice(np_data, ['id', 'ud_pi'], fs)

    id_mean       = float(ss['id'].mean())
    ud_pi_mean    = float(ss['ud_pi'].mean())
    omega_s_mean  = float(np_data['omega_s_rad_s'].mean())

    if abs(id_mean) < 0.1:
        print(f"  WARNING: id ≈ {id_mean:.3f} A — is the motor carrying flux?")

    if omega_s_mean > 10.0:
        print(f"  WARNING: omega_s = {omega_s_mean:.2f} rad/s — too high for Rs test "
              f"(decoupling terms not negligible). Target < 5 rad/s (SF1 ≤ 0.5 Hz).")

    Rs_raw = ud_pi_mean / id_mean if abs(id_mean) > 0.01 else float('nan')

    # Corrected: Rs = (ud_pi + omega_s * sigma_ls * iq) / id
    iq_mean = float(ss['iq'].mean()) if 'iq' in ss else 0.0
    if sigma_ls is not None and omega_s_mean < 20.0:
        Rs_corr = (ud_pi_mean + omega_s_mean * sigma_ls * iq_mean) / id_mean \
                  if abs(id_mean) > 0.01 else float('nan')
    else:
        Rs_corr = Rs_raw

    print(f"  Steady-state window: {len(ss['id'])} samples  ({len(ss['id'])/fs:.2f} s)")
    print(f"  id = {id_mean:.4f} A    iq = {iq_mean:.4f} A")
    print(f"  ud_pi = {ud_pi_mean:.4f} V    omega_s = {omega_s_mean:.3f} rad/s")
    print(f"  Rs (raw)       = ud_pi / id          = {Rs_raw:.4f} Ω")
    if sigma_ls is not None:
        print(f"  Rs (corrected) = (ud_pi + ω×σLs×iq)/id = {Rs_corr:.4f} Ω  "
              f"(σLs = {sigma_ls*1e3:.3f} mH)")
    print(f"\n  → Rs ≈ {Rs_corr:.3f} Ω")

    if 'Speed_rpm' in np_data:
        spd = float(np_data['Speed_rpm'].mean())
        if abs(spd) > 10:
            print(f"  WARNING: Speed_rpm = {spd:.1f} RPM — motor should be at standstill for Rs test")

    return {'Rs_Ohm': Rs_corr, 'Rs_raw_Ohm': Rs_raw}


# ---- Test B: Lm -------------------------------------------------------------

def identify_Lm(path):
    """
    Estimate magnetizing inductance Lm from a no-load FOC log.

    Returns
    -------
    dict with 'Lm_H', diagnostics
    """
    print(f"\n{'='*60}\n  Test B — Lm identification\n  Log: {os.path.basename(path)}\n{'='*60}")

    data, fs = load_log(path)
    if not _check_channels(data, ['id', 'psi_r_mag'], 'Lm'):
        return None

    np_data = {k: np.asarray(v) for k, v in data.items()}
    ss = _steady_slice(np_data, ['id', 'psi_r_mag'], fs)

    id_mean    = float(ss['id'].mean())
    psi_mean   = float(ss['psi_r_mag'].mean())
    iq_mean    = float(ss['iq'].mean()) if 'iq' in ss else 0.0

    if abs(id_mean) < 0.1:
        print(f"  WARNING: id ≈ {id_mean:.3f} A — no flux current. Set SF2 to rated id.")

    if abs(iq_mean) > 0.2 * abs(id_mean):
        print(f"  WARNING: iq/id = {iq_mean/id_mean:.2f} — not a no-load condition. "
              f"Set SF3 = 0 and unload the motor.")

    Lm = psi_mean / id_mean if abs(id_mean) > 0.01 else float('nan')

    print(f"  Steady-state window: {len(ss['id'])} samples  ({len(ss['id'])/fs:.2f} s)")
    print(f"  id = {id_mean:.4f} A    iq = {iq_mean:.4f} A")
    print(f"  psi_r_mag = {psi_mean:.5f} Vs")
    print(f"  Lm = psi_r_mag / id = {Lm*1e3:.3f} mH = {Lm:.5f} H")
    print(f"\n  → Lm ≈ {Lm:.4f} H")

    # Saturation check: if there is a second log segment available, fit linearly
    print(f"  NOTE: measure at id ≤ 0.7× rated to stay in the linear (unsaturated) region.")

    return {'Lm_H': Lm}


# ---- Test C: Rr -------------------------------------------------------------

def identify_Rr(path, Lr_H):
    """
    Estimate rotor resistance Rr from a loaded FOC log.

    Formula: ω_slip = (Rr/Lr) × (iq/id)  →  Rr = ω_slip × Lr × id / iq

    Requires 'omega_slip_rad_s' channel in the log.
    """
    print(f"\n{'='*60}\n  Test C — Rr identification\n  Log: {os.path.basename(path)}\n{'='*60}")

    data, fs = load_log(path)
    if not _check_channels(data, ['id', 'iq', 'omega_slip_rad_s'], 'Rr'):
        return None

    np_data = {k: np.asarray(v) for k, v in data.items()}
    ss = _steady_slice(np_data, ['id', 'iq', 'omega_slip_rad_s'], fs)

    id_mean        = float(ss['id'].mean())
    iq_mean        = float(ss['iq'].mean())
    omega_slip_mean = float(ss['omega_slip_rad_s'].mean())

    if abs(iq_mean) < 0.1:
        print(f"  WARNING: iq ≈ {iq_mean:.3f} A — motor is not loaded. "
              f"Apply mechanical or electrical load (SF3 > 0).")

    Rr = omega_slip_mean * Lr_H * id_mean / iq_mean if abs(iq_mean) > 0.01 else float('nan')

    psi_mean  = float(ss['psi_r_mag'].mean()) if 'psi_r_mag' in ss else float('nan')
    spd_mean  = float(np_data['Speed_rpm'].mean()) if 'Speed_rpm' in np_data else float('nan')

    print(f"  Steady-state window: {len(ss['id'])} samples  ({len(ss['id'])/fs:.2f} s)")
    print(f"  id = {id_mean:.4f} A    iq = {iq_mean:.4f} A")
    print(f"  omega_slip = {omega_slip_mean:.4f} rad/s  ({omega_slip_mean/(2*math.pi):.4f} Hz)")
    print(f"  Speed_rpm = {spd_mean:.1f}")
    print(f"  psi_r_mag = {psi_mean:.4f} Vs")
    print(f"  Lr = {Lr_H*1e3:.3f} mH  (from motor_config.h)")
    print(f"  Rr = ω_slip × Lr × id / iq = {Rr:.4f} Ω")
    print(f"\n  → Rr ≈ {Rr:.4f} Ω")
    print(f"  NOTE: Rr rises ~50% from cold to hot. Identify at operating temperature.")

    return {'Rr_Ohm': Rr}


# ---- Summary output ---------------------------------------------------------

def print_motor_config_snippet(results, existing_cfg=None):
    """Print a motor_config.h snippet from combined test results."""
    print(f"\n{'='*60}\n  Identified parameters — paste into motor_config.h\n{'='*60}")

    def _v(key, fallback='???'):
        return results.get(key, existing_cfg.get(key, fallback) if existing_cfg else fallback)

    Rs  = _v('Rs_Ohm')
    Rr  = _v('Rr_Ohm')
    Lm  = _v('Lm_H')

    # Use existing leakage if not identified (can't be measured with these 3 tests alone)
    Lss = existing_cfg['Lsigma_s_H'] if existing_cfg else '???'
    Lsr = existing_cfg['Lsigma_r_H'] if existing_cfg else '???'
    pp  = existing_cfg['PolePairs']   if existing_cfg else '???'
    J   = existing_cfg['J_kgm2']      if existing_cfg else '???'

    def _fmt(v):
        if isinstance(v, float):
            return f'{v:.4g}f'
        return str(v)

    print(f"  #define MOTOR_Rs_Ohm          {_fmt(Rs)}")
    print(f"  #define MOTOR_Rr_Ohm          {_fmt(Rr)}")
    print(f"  #define MOTOR_Lm_H            {_fmt(Lm)}")
    print(f"  #define MOTOR_Lsigma_s_H      {_fmt(Lss)}   /* leakage — measure separately or use nameplate */")
    print(f"  #define MOTOR_Lsigma_r_H      {_fmt(Lsr)}   /* assume = Lsigma_s if unknown */")
    print(f"  #define MOTOR_PolePairs        {_fmt(pp)}")
    print(f"  #define MOTOR_J_kgm2          {_fmt(J)}")
    if isinstance(Lm, float) and isinstance(Lss, float):
        Ls = Lm + Lss
        Psi_rated = Lm * (existing_cfg['Psi_rated_Vs'] / existing_cfg['Lm_H']) \
                    if existing_cfg and not math.isnan(existing_cfg['Lm_H']) \
                    else '???'
        print(f"  /* Psi_rated = Lm × id_rated — recompute from nameplate if Lm changed */")
    print()


# ---- CLI --------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description='Extract Rs, Lm, Rr from JavaScope logs.',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__)
    parser.add_argument('--Rs',  metavar='CSV',
                        help='Log for Test A (standstill, low-frequency V/f)')
    parser.add_argument('--Lm',  metavar='CSV',
                        help='Log for Test B (no-load FOC, id sweep)')
    parser.add_argument('--Rr',  metavar='CSV',
                        help='Log for Test C (loaded FOC, steady state)')
    parser.add_argument('--motor-config', metavar='FILE',
                        help='Path to motor_config.h (auto-detected if not supplied)')
    parser.add_argument('--print-channels', metavar='TEST',
                        choices=['Rs', 'Lm', 'Rr', 'all'],
                        help='Print properties.ini channel preset for the given test and exit')
    args = parser.parse_args()

    # --- Load motor config ---------------------------------------------------
    existing_cfg = None
    try:
        existing_cfg = load_motor_config(args.motor_config)
        print(f"[motor_config] {existing_cfg['_source']}  [{existing_cfg['_active_config']}]")
    except FileNotFoundError:
        if args.motor_config:
            print(f"ERROR: motor_config.h not found: {args.motor_config}", file=sys.stderr)
            sys.exit(1)
        print("[motor_config] not found — proceeding without existing parameters")

    # --- Print channel presets -----------------------------------------------
    if args.print_channels:
        try:
            jso = parse_jso_enum()
        except FileNotFoundError as e:
            print(f"ERROR: {e}", file=sys.stderr)
            sys.exit(1)

        tests = ['Rs', 'Lm', 'Rr'] if args.print_channels == 'all' else [args.print_channels]
        ch_map = {'Rs': _CHANNELS_Rs, 'Lm': _CHANNELS_Lm, 'Rr': _CHANNELS_Rr}
        for t in tests:
            print_ini_section(f"Test {t} — identify_motor_params.py", ch_map[t], jso)
        return

    if not any([args.Rs, args.Lm, args.Rr]):
        parser.print_help()
        print("\nTip: run with --print-channels all to see required channel presets.", file=sys.stderr)
        sys.exit(0)

    # --- Run tests -----------------------------------------------------------
    results = {}
    sigma_ls = existing_cfg['sigma_Ls_H'] if existing_cfg else None
    Lr_H     = existing_cfg['Lr_H']       if existing_cfg else None

    if args.Rs:
        r = identify_Rs(args.Rs, sigma_ls=sigma_ls)
        if r:
            results.update(r)

    if args.Lm:
        r = identify_Lm(args.Lm)
        if r:
            results.update(r)

    if args.Rr:
        if Lr_H is None:
            print("ERROR: --Rr test requires Lr_H from motor_config.h. "
                  "Provide --motor-config or run Tests A+B first.", file=sys.stderr)
            sys.exit(1)
        r = identify_Rr(args.Rr, Lr_H)
        if r:
            results.update(r)

    if results:
        print_motor_config_snippet(results, existing_cfg)


if __name__ == '__main__':
    main()
