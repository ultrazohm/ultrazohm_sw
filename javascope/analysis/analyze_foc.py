"""
FOC cross-coupling and steady-state analysis for UltraZohm JavaScope logs.

Run:
    python analyze_foc.py <path_to_csv> [--scan-iq-steps]

Outputs:
- Operating point summary
- d/q tracking statistics
- Cross-correlation r(id_error, iq) at key lags
- DFT of id_error: top harmonics + energy at key motor frequencies
- U_d vs iq steady-state check (sigma_ls verification)
- psi_r_alpha / psi_r_beta oscillation (if logged) -> angle noise diagnosis
- iq step detection and id transient (if --scan-iq-steps)
"""

import sys
import os
import math
import argparse
sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')

# Allow running from any directory
sys.path.insert(0, os.path.dirname(__file__))
from load_log import load_log, mean, std, rms, autocorr, crosscorr, dft_amp, stats_summary


def _section(title):
    print()
    print('=' * 60)
    print(f'  {title}')
    print('=' * 60)


def analyze_operating_point(data, fs):
    _section("OPERATING POINT")
    t = data['time']
    print(f"  Duration : {t[-1]-t[0]:.2f} s   N={len(t)}   fs={fs:.0f} Hz")
    for sig in ['Speed_rpm', 'U_DC', 'omega_s_rad_s', 'torque']:
        if sig not in data:
            continue
        mu, sd, mn, mx = stats_summary(data[sig])
        print(f"  {sig:20s}: mean={mu:9.4f}  std={sd:7.4f}  [{mn:.3f}, {mx:.3f}]")


def analyze_dq_tracking(data, fs):
    _section("D/Q CURRENT TRACKING")
    if 'id' not in data or 'id_cmd' not in data:
        print("  id / id_cmd not available")
        return
    id_err = [a - b for a, b in zip(data['id'], data['id_cmd'])]
    iq_err = [a - b for a, b in zip(data['iq'], data['iq_cmd'])]

    mu, sd, mn, mx = stats_summary(id_err)
    print(f"  id_error : mean={mu:+.4f} A  std={sd:.4f} A  peak={max(abs(mn),abs(mx)):.4f} A")
    mu, sd, mn, mx = stats_summary(iq_err)
    print(f"  iq_error : mean={mu:+.4f} A  std={sd:.4f} A  peak={max(abs(mn),abs(mx)):.4f} A")

    print()
    print("  Cross-correlation r(id_error, iq) [lags in samples]:")
    for lag in [0, 1, 2, 5, 10, 25]:
        r = crosscorr(id_err, data['iq'], lag)
        print(f"    lag={lag:3d} ({lag/fs*1000:.2f} ms) : r={r:+.4f}")

    return id_err, iq_err


def analyze_dft(data, fs, id_err, iq_err):
    _section("FREQUENCY ANALYSIS (id_error)")
    if 'omega_s_rad_s' in data:
        f_el = mean(data['omega_s_rad_s']) / (2 * math.pi)
    else:
        f_el = 45.0
    f_mech = mean(data['Speed_rpm']) / 60.0 if 'Speed_rpm' in data else f_el
    f_slip = f_el - f_mech
    print(f"  f_el  = {f_el:.3f} Hz  (stator field frequency)")
    print(f"  f_mech= {f_mech:.3f} Hz  (rotor mechanical = {f_mech*60:.1f} RPM)")
    print(f"  f_slip= {f_slip:.3f} Hz  (= f_el - f_mech)")

    # Brute-force DFT at integer Hz from 1 to 500
    best = []
    for freq in range(1, 501):
        a = dft_amp(id_err, freq, fs)
        best.append((a, freq))
    best.sort(reverse=True)

    print(f"\n  Top 8 frequency components in id_error:")
    for amp, freq in best[:8]:
        # Show ratios to all relevant base frequencies
        r_el   = freq / f_el   if f_el   > 0 else 0
        r_mech = freq / f_mech if f_mech > 0 else 0
        r_slip = freq / f_slip if f_slip > 0 else 0
        # Sideband check: n*f_el + m*f_slip (n,m small integers)
        sb = ""
        for n in range(1, 13):
            for m in range(-3, 4):
                val = n * f_el + m * f_slip
                if val > 0 and abs(freq - val) < 1.5:
                    sb = f"  ≈ {n}*f_el{m:+d}*f_slip"
                    break
            if sb:
                break
        print(f"    f={freq:4d} Hz  ({r_el:.2f}*f_el  {r_mech:.2f}*f_mech  {r_slip:.1f}*f_slip){sb}  amp={amp:.5f} A")

    print()
    print("  Energy at motor harmonics (id_error):")
    total_var = std(id_err) ** 2
    for k in [1, 4, 5, 6, 7]:
        f = k * f_el
        a = dft_amp(id_err, f, fs)
        power = (a / math.sqrt(2)) ** 2
        pct = power / total_var * 100 if total_var > 0 else 0
        print(f"    {k}*f_el = {f:6.2f} Hz: amp={a:.5f} A  ({pct:.1f}% of variance)")
    # Also check sideband candidates explicitly
    print()
    print("  Sideband check (n*f_el ± m*f_slip) in id_error:")
    for n, m in [(5, 1), (5, 2), (10, 2), (10, 4)]:
        for sign in [1, -1]:
            f = n * f_el + sign * m * f_slip
            if 1 < f < fs / 2:
                a = dft_amp(id_err, f, fs)
                lbl = f"{n}*f_el{sign*m:+d}*f_slip"
                print(f"    {lbl:20s} = {f:7.2f} Hz: amp={a:.5f} A")

    return f_el, f_mech, f_slip


def analyze_speed_spectrum(data, fs, f_el, f_mech, f_slip):
    """
    DFT of the measured rotor speed signal.
    A 437 Hz component here would confirm the disturbance is injected from the
    mechanical side (load machine oscillation / encoder artifact) rather than
    being generated inside the current control loop.
    Physical mechanical oscillations above ~100 Hz are implausible for a motor
    shaft; electrical/encoder artifacts are the more likely source.
    """
    _section("ROTOR SPEED SPECTRUM (mechanical coupling check)")
    if 'Speed_rpm' not in data:
        print("  Speed_rpm not available")
        return

    spd = data['Speed_rpm']
    mu_spd = mean(spd)
    sd_spd = std(spd)
    print(f"  Speed: mean={mu_spd:.2f} RPM  std={sd_spd:.4f} RPM  ({sd_spd/mu_spd*100:.4f}%)")

    total_var = sd_spd ** 2 if sd_spd > 0 else 1e-10
    check_freqs = [f_mech, 6*f_mech, 13*f_mech, f_el, 219.0, 437.0]
    labels      = ["f_mech", "6*f_mech", "13*f_mech", "f_el", "219 Hz", "437 Hz"]
    print(f"  DFT of Speed_rpm at key frequencies:")
    for freq, lbl in zip(check_freqs, labels):
        a_rpm = dft_amp(spd, freq, fs)
        pct = (a_rpm / math.sqrt(2)) ** 2 / total_var * 100
        # Convert speed amplitude to omega amplitude (rad/s electrical)
        a_rads = a_rpm * 2 * math.pi / 60.0
        print(f"    {lbl:12s} = {freq:7.2f} Hz: amp={a_rpm:.5f} RPM  "
              f"({a_rads:.5f} rad/s)  ({pct:.3f}% of speed variance)")

    # Top spectral peaks in speed
    best = []
    for freq in range(1, min(501, int(fs / 2))):
        a = dft_amp(spd, freq, fs)
        best.append((a, freq))
    best.sort(reverse=True)
    print()
    print("  Top 5 speed spectral peaks:")
    for amp, freq in best[:5]:
        r_mech = freq / f_mech if f_mech > 0 else 0
        print(f"    f={freq:4d} Hz ({r_mech:.2f}*f_mech): amp={amp:.5f} RPM")


def analyze_ud_pi_spectrum(data, fs, f_el):
    """
    DFT of ud_pi (PI output before decoupling) at the known disturbance frequencies.
    If 437 Hz appears in ud_pi the PI is actively fighting the dead-time disturbance
    but is bandwidth-limited (error not fully corrected).
    If 437 Hz is absent from ud_pi but present in id_error, the disturbance is
    injected after the current measurement (unlikely for dead-time).
    """
    _section("UD_PI FREQUENCY ANALYSIS (PI output, 437 Hz check)")
    if 'ud_pi' not in data:
        print("  ud_pi not available in this log (select JSO 36 in properties.ini)")
        return

    ud_pi = data['ud_pi']
    print(f"  ud_pi: mean={mean(ud_pi):+.3f} V  std={std(ud_pi):.4f} V")

    check_freqs = [f_el, 6*f_el, 219.0, 437.0, 438.0]
    total_var = std(ud_pi) ** 2 if std(ud_pi) > 0 else 1e-10
    print(f"  DFT at key frequencies (f_el={f_el:.2f} Hz):")
    for freq in check_freqs:
        a = dft_amp(ud_pi, freq, fs)
        pct = (a / math.sqrt(2)) ** 2 / total_var * 100
        print(f"    f={freq:7.2f} Hz: amp={a:.4f} V  ({pct:.1f}% of variance)")

    best = []
    for freq in range(1, min(501, int(fs / 2))):
        a = dft_amp(ud_pi, freq, fs)
        best.append((a, freq))
    best.sort(reverse=True)
    print()
    print("  Top 5 ud_pi spectral peaks:")
    for amp, freq in best[:5]:
        print(f"    f={freq:4d} Hz ({freq/f_el:.2f}*f_el): amp={amp:.4f} V")


def analyze_ud_vs_iq(data, fs):
    """
    Test for sigma_ls error: at steady state with perfect decoupling,
    U_d = Rs * id_ref  (independent of iq).
    If U_d shifts with iq, sigma_ls is wrong.
    """
    _section("SIGMA_LS CHECK: U_d vs iq (Test 2)")
    if 'ud' not in data or 'iq' not in data:
        print("  ud / iq not available in this log")
        return

    ud = data['ud']
    iq = data['iq']
    id_arr = data.get('id', [0]*len(ud))
    omega_s = data.get('omega_s_rad_s', [285.0]*len(ud))

    mu_ud = mean(ud)
    mu_iq = mean(iq)
    mu_id = mean(id_arr)
    mu_om = mean(omega_s)

    print(f"  Mean U_d = {mu_ud:.3f} V   (expected = Rs*id_cmd if decoupling perfect)")
    print(f"  Mean iq  = {mu_iq:.3f} A")
    print(f"  omega_s  = {mu_om:.2f} rad/s")

    # Instantaneous estimate of sigma_ls error from U_d residual
    # U_d_residual = U_d - Rs*id  (should be ~0 if decoupling OK)
    # The PI handles the Rs*id part; the decoupling should handle the cross term.
    # Since PI integrates away static errors, look at variance instead.
    # Correlation between U_d and iq at steady state reveals coupling.
    if std(iq) > 0.01:
        r_ud_iq = crosscorr(ud, iq)
        print(f"  r(U_d, iq)  = {r_ud_iq:+.4f}  (near 0 = good decoupling)")
    else:
        print("  iq variance too low for correlation test")

    # Bin U_d, omega_s by iq quartiles: estimate ud_PI = U_d - ud_decoup_used per bin
    # ud_decoup_used = -omega_s * sigma_ls_used * iq
    # sigma_ls = sigma * Ls = (1 - Lm^2/(Ls*Lr)) * Ls
    # With Lsigma_s=Lsigma_r=8.5mH, Lm=340mH: Ls=Lr=348.5mH, sigma=0.04822, sigma_ls=16.80mH
    sigma_ls_used = 0.01680  # H (Lsigma_s=Lsigma_r=8.5mH, Lm=340mH -> sigma_ls=16.80mH)
    Rs_used = 2.1           # Ohm
    id_ref_expected = mean(id_arr)

    # Use logged ud_decoup directly if available (more accurate than recomputing)
    ud_decoup_logged = data.get('ud_decoup', None)

    iq_range = max(iq) - min(iq)
    if iq_range > 0.3:
        print()
        if ud_decoup_logged:
            print(f"  Steady-state ud_PI check (using LOGGED ud_decoup, expected ~Rs*id={Rs_used*id_ref_expected:.2f} V):")
            print(f"  {'iq_bin':18s}  {'mean_iq':7s}  {'mean_om':8s}  {'U_d':8s}  {'ud_decoup':10s}  {'ud_PI':8s}  {'ud_PI_excess':12s}")
        else:
            print(f"  Steady-state ud_PI check (ud_PI = U_d - ud_decoup_computed, expected ~Rs*id={Rs_used*id_ref_expected:.2f} V):")
            print(f"  {'iq_bin':18s}  {'mean_iq':7s}  {'mean_om':8s}  {'U_d':8s}  {'ud_decoup':10s}  {'ud_PI':8s}  {'ud_PI_excess':12s}")
        iq_min = min(iq)
        n_bins = 5
        bin_width = iq_range / n_bins
        # collect per-bin: ud, iq, omega_s, ud_decoup
        bins_ud = [[] for _ in range(n_bins)]
        bins_iq = [[] for _ in range(n_bins)]
        bins_om = [[] for _ in range(n_bins)]
        bins_decoup = [[] for _ in range(n_bins)]
        for i in range(len(iq)):
            b = min(int((iq[i] - iq_min) / bin_width), n_bins - 1)
            bins_ud[b].append(ud[i])
            bins_iq[b].append(iq[i])
            bins_om[b].append(omega_s[i])
            if ud_decoup_logged:
                bins_decoup[b].append(ud_decoup_logged[i])
        for b in range(n_bins):
            if len(bins_ud[b]) < 10:
                continue
            mu_iq_b  = mean(bins_iq[b])
            mu_om_b  = mean(bins_om[b])
            mu_ud_b  = mean(bins_ud[b])
            if ud_decoup_logged and bins_decoup[b]:
                decoup = mean(bins_decoup[b])
            else:
                decoup = -mu_om_b * sigma_ls_used * mu_iq_b
            ud_pi_b  = mu_ud_b - decoup
            excess   = ud_pi_b - Rs_used * id_ref_expected
            iq_lo = iq_min + b * bin_width
            iq_hi = iq_lo + bin_width
            print(f"  iq=[{iq_lo:5.2f},{iq_hi:5.2f}] A  "
                  f"{mu_iq_b:7.3f} A  {mu_om_b:8.2f} r/s  "
                  f"{mu_ud_b:8.3f} V  {decoup:10.3f} V  "
                  f"{ud_pi_b:8.3f} V  {excess:+.3f} V")

        # Estimate delta_sigma_ls from the excess across iq range (only when not using logged decoup)
        if not ud_decoup_logged:
            valid_bins = [(mean(bins_iq[b]), mean(bins_om[b]),
                           mean(bins_ud[b]) - (-mean(bins_om[b])*sigma_ls_used*mean(bins_iq[b])) - Rs_used*id_ref_expected)
                          for b in range(n_bins) if len(bins_ud[b]) >= 10 and abs(mean(bins_iq[b])) > 0.5]
            if len(valid_bins) >= 2:
                # Linear regression: excess = a * (omega_s * iq)
                xy = [(om * iq_b, exc) for iq_b, om, exc in valid_bins]
                mu_x = mean([x for x, _ in xy])
                mu_y = mean([y for _, y in xy])
                cov = mean([(x-mu_x)*(y-mu_y) for x, y in xy])
                var = mean([(x-mu_x)**2 for x, _ in xy])
                if abs(var) > 1e-10:
                    delta_sigma = cov / var
                    print(f"\n  Estimated delta_sigma_ls = {delta_sigma*1000:.2f} mH  "
                          f"(sigma_ls_used={sigma_ls_used*1000:.1f} mH  "
                          f"-> sigma_ls_actual ≈ {(sigma_ls_used-delta_sigma)*1000:.1f} mH)")


def analyze_psi_oscillation(data, fs, f_el):
    """
    Analyze observer flux quality.
    psi_r_alpha/beta is a ROTATING VECTOR at f_el, so we must work in:
      - psi_r_mag = sqrt(alpha^2 + beta^2)  -> should be constant
      - theta_err = angle - linear_trend     -> residual angle noise
    """
    _section("OBSERVER ANGLE NOISE: psi_r magnitude + angle residual")
    if 'det_psi_r_alpha' not in data:
        print("  det_psi_r_alpha not available in this log")
        return

    psi_a = data['det_psi_r_alpha']
    psi_b = data['det_psi_r_beta']
    n = len(psi_a)
    t = data['time']

    # --- Magnitude noise ---
    psi_mag = [math.sqrt(psi_a[i]**2 + psi_b[i]**2) for i in range(n)]
    mu_mag, sd_mag, mn_mag, mx_mag = stats_summary(psi_mag)
    print(f"  |psi_r| mean={mu_mag:.4f} Vs  std={sd_mag:.5f} Vs  "
          f"(std/mean={sd_mag/mu_mag*100:.3f}%)")

    # --- Angle residual noise ---
    # Compute raw angle and unwrap
    raw_angle = [math.atan2(psi_b[i], psi_a[i]) for i in range(n)]
    # Unwrap: remove 2*pi jumps
    unwrapped = [raw_angle[0]]
    for i in range(1, n):
        delta = raw_angle[i] - raw_angle[i-1]
        if delta > math.pi:
            delta -= 2 * math.pi
        elif delta < -math.pi:
            delta += 2 * math.pi
        unwrapped.append(unwrapped[-1] + delta)

    # Fit linear trend (omega_s_est * t + phi0) and subtract
    # Linear fit via least-squares on (t, unwrapped)
    t0 = t[0]
    ts_rel = [ti - t0 for ti in t]
    mu_t = mean(ts_rel)
    mu_u = mean(unwrapped)
    cov_tu = sum((ts_rel[i] - mu_t) * (unwrapped[i] - mu_u) for i in range(n)) / n
    var_t  = sum((ti - mu_t) ** 2 for ti in ts_rel) / n
    omega_est = cov_tu / var_t if var_t > 0 else 0.0
    phi0 = mu_u - omega_est * mu_t
    theta_err = [unwrapped[i] - (omega_est * ts_rel[i] + phi0) for i in range(n)]

    mu_te, sd_te, mn_te, mx_te = stats_summary(theta_err)
    print(f"  omega_s_fit = {omega_est:.3f} rad/s  ({omega_est/(2*math.pi):.3f} Hz)")
    print(f"  theta_err (after linear detrend):")
    print(f"    mean={math.degrees(mu_te):.3f} deg  std={math.degrees(sd_te):.3f} deg  "
          f"peak={math.degrees(max(abs(mn_te), abs(mx_te))):.3f} deg")

    # --- DFT of theta_err ---
    print()
    print("  DFT of theta_err at key frequencies:")
    total_var = sd_te ** 2 if sd_te > 0 else 1e-10
    check_freqs = [f_el, 2*f_el, 4*f_el, 6*f_el, 218.0, 257.0]
    for freq in check_freqs:
        a = dft_amp(theta_err, freq, fs)
        pct = (a / math.sqrt(2)) ** 2 / total_var * 100
        a_deg = math.degrees(a)
        print(f"    f={freq:7.2f} Hz: amp={a_deg:.4f} deg  ({pct:.1f}% of variance)")

    # Top peaks (fast scan, integer Hz)
    best = []
    for freq in range(1, min(501, int(fs / 2))):
        a = dft_amp(theta_err, freq, fs)
        best.append((a, freq))
    best.sort(reverse=True)
    print()
    print("  Top 5 theta_err spectral peaks:")
    for amp, freq in best[:5]:
        print(f"    f={freq:4d} Hz ({freq/f_el:.2f}*f_el): "
              f"amp={math.degrees(amp):.4f} deg")


def detect_iq_steps(data, fs, threshold=0.5, min_gap_s=0.1):
    """Find indices where iq_cmd steps by more than threshold."""
    iq_cmd = data.get('iq_cmd', [])
    steps = []
    min_gap = int(min_gap_s * fs)
    last = -min_gap
    for i in range(1, len(iq_cmd)):
        delta = abs(iq_cmd[i] - iq_cmd[i-1])
        if delta > threshold and (i - last) > min_gap:
            steps.append((i, iq_cmd[i-1], iq_cmd[i]))
            last = i
    return steps


def analyze_iq_step(data, fs):
    """Test 4: step iq and watch id transient -> sigma_ls verification."""
    _section("IQ STEP TRANSIENT ANALYSIS (Test 4)")
    if 'iq_cmd' not in data:
        print("  iq_cmd not available")
        return

    steps = detect_iq_steps(data, fs, threshold=0.3, min_gap_s=0.05)
    if not steps:
        print("  No iq steps detected (threshold 0.3 A)")
        # Try smaller threshold
        steps = detect_iq_steps(data, fs, threshold=0.1, min_gap_s=0.05)
        if steps:
            print(f"  Found {len(steps)} step(s) with threshold 0.1 A")
        else:
            print("  No iq steps found even at threshold 0.1 A")
            print("  iq_cmd range:", min(data['iq_cmd']), "to", max(data['iq_cmd']))
            return

    id_arr = data.get('id', [])
    id_cmd = data.get('id_cmd', [])

    window = int(0.010 * fs)  # 10 ms window around step
    print(f"  Found {len(steps)} iq step(s):")
    for idx, iq_before, iq_after in steps[:5]:
        delta_iq = iq_after - iq_before
        t_step = data['time'][idx]

        # id before and after step
        pre = id_arr[max(0, idx-window):idx]
        post = id_arr[idx:min(len(id_arr), idx+window)]
        pre_cmd = id_cmd[max(0, idx-window):idx] if id_cmd else []

        id_pre = mean(pre) if pre else float('nan')
        id_post_max = max(post) if post else float('nan')
        id_post_min = min(post) if post else float('nan')
        id_cmd_val = mean(pre_cmd) if pre_cmd else float('nan')

        # Peak deviation from reference
        if id_cmd:
            id_ref = id_cmd_val
            peak_dev = max(abs(id_post_max - id_ref), abs(id_post_min - id_ref))
        else:
            peak_dev = max(abs(id_post_max - id_pre), abs(id_post_min - id_pre))

        print(f"    t={t_step:.4f}s  delta_iq={delta_iq:+.2f}A  "
              f"id_pre={id_pre:.3f}A  id_peak_dev={peak_dev:.4f}A  "
              f"(id_ref={id_cmd_val:.3f}A)")

        # Estimate sigma_ls error from coupling
        # peak_dev ≈ |delta_sigma_ls| * omega_s * |delta_iq| / (sigma_ls * pi * bw)
        # Simpler: delta_ud_residual = omega_s * delta_sigma_ls * delta_iq
        # id_deviation ≈ delta_ud / (motor_Z * 2*pi*bw) ... rough
        if abs(delta_iq) > 0.05 and 'omega_s_rad_s' in data:
            om = mean(data['omega_s_rad_s'][max(0,idx-10):idx+10]) if idx >= 10 else 285.0
            print(f"      -> peak id/delta_iq = {peak_dev/abs(delta_iq):.4f} A/A  "
                  f"omega_s={om:.1f} rad/s")


def main():
    parser = argparse.ArgumentParser(description='FOC cross-coupling analysis')
    parser.add_argument('log', help='Path to JavaScope CSV log file')
    parser.add_argument('--test4', action='store_true',
                        help='Focus on iq step transient analysis (Test 4)')
    args = parser.parse_args()

    data, fs = load_log(args.log)
    print(f"Log: {os.path.basename(args.log)}")
    print(f"Channels available: {sorted(data.keys())}")

    if 'time' not in data or len(data['time']) < 2:
        print("  ERROR: Log file is empty or has insufficient data. Skipping analysis.")
        return

    analyze_operating_point(data, fs)
    result = analyze_dq_tracking(data, fs)
    f_mech = mean(data['Speed_rpm']) / 60.0 if 'Speed_rpm' in data else 0.0
    if result:
        id_err, iq_err = result
        f_el, f_mech, f_slip = analyze_dft(data, fs, id_err, iq_err)
    else:
        f_el = 45.0
        f_slip = 0.0

    analyze_speed_spectrum(data, fs, f_el, f_mech, f_slip)
    analyze_ud_pi_spectrum(data, fs, f_el)
    analyze_ud_vs_iq(data, fs)
    analyze_psi_oscillation(data, fs, f_el)
    analyze_iq_step(data, fs)
    print()


if __name__ == '__main__':
    main()
