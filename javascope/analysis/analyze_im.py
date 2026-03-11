"""
Induction Motor FOC + observer analysis for UltraZohm JavaScope logs.

Usage:
    python analyze_im.py <log.csv>                    # single log
    python analyze_im.py <det.csv> <kf.csv>           # det vs KF comparison

Replaces: analyze_foc.py, analyze_kf.py, analyze_kf_observer.py

Motor constants (edit to match your machine):
    Rs=2.1 Ohm, Rr=2.4 Ohm, Lsigma_s=Lsigma_r=8.5 mH, Lm=340 mH, p=1
    -> sigma_ls=16.80 mH, tau_r=0.1452 s
"""

import sys, os, math, argparse
import numpy as np

sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')
sys.path.insert(0, os.path.dirname(__file__))
from load_log import load_log
from parse_motor_config import load_motor_config
from jso_channels import parse_jso_enum, print_ini_section

# Channels for full FOC + observer commissioning log
_CHANNELS_COMMISSIONING = [
    'ia', 'ib', 'ic',
    'id', 'iq',
    'id_cmd', 'iq_cmd',
    'psi_r_mag',
    'Theta_el',
    'Speed_rpm',
    'omega_s_rad_s',
    'omega_slip_rad_s',
    'ud_pi', 'uq_pi',
    'ud_decoup',
    'kf_innov_alpha', 'kf_innov_beta',
    'kf_K_00',
    'det_psi_r_alpha',
    'det_psi_r_beta',
]

# Machine constants for analysis (must match motor_config.h / isr.c)
# These defaults are for the Lindner 3 kW motor tested with the Wolfspeed adapter board.
# Override at runtime with --motor-config path/to/motor_config.h
RS_OHM   = 2.1
LM_H     = 0.340
LR_H     = 0.3485   # Lsigma_r + Lm
SIGMA_LS = 0.01680  # sigma * Ls  (sigma = 1 - Lm²/(Ls*Lr))


# ---------------------------------------------------------------------------
# Spectral helpers
# ---------------------------------------------------------------------------

def _fft(arr, fs):
    """Return (freqs [Hz], two-sided-peak amplitudes) via real FFT."""
    x = np.asarray(arr, dtype=float)
    x -= x.mean()
    N = len(x)
    A = np.abs(np.fft.rfft(x)) * 2.0 / N
    F = np.fft.rfftfreq(N, d=1.0 / fs)
    return F, A


def _amp_at(arr_np, freq, fs):
    """Single-bin DFT amplitude (two-sided peak) at one frequency."""
    x = arr_np - arr_np.mean()
    n = len(x)
    t = np.arange(n) / fs
    re = np.mean(x * np.cos(2 * math.pi * freq * t)) * 2
    im = np.mean(x * np.sin(2 * math.pi * freq * t)) * 2
    return float(math.sqrt(re**2 + im**2))


def _ac1(arr_np):
    """Lag-1 autocorrelation."""
    if len(arr_np) < 3:
        return 0.0
    return float(np.corrcoef(arr_np[:-1], arr_np[1:])[0, 1])


def _pct_var(amp, total_var):
    return (amp / math.sqrt(2))**2 / total_var * 100 if total_var > 0 else 0.0


def _top_peaks(F, A, n=5, f_min=2.0):
    mask = F >= f_min
    Fm, Am = F[mask], A[mask]
    idx = np.argsort(Am)[-n:][::-1]
    return list(zip(Fm[idx], Am[idx]))


# ---------------------------------------------------------------------------
# Section header
# ---------------------------------------------------------------------------

def _sec(title):
    print(f"\n{'='*60}\n  {title}\n{'='*60}")


# ---------------------------------------------------------------------------
# Per-log analysis — returns a dict of key metrics for comparison
# ---------------------------------------------------------------------------

def analyze_log(path):
    data, fs = load_log(path)
    name = os.path.basename(path)

    if 'time' not in data or len(data.get('time', [])) < 100:
        print(f"ERROR: {name} — too few samples")
        return None

    t    = data['time']
    N    = len(t)
    dur  = t[-1] - t[0]

    has_kf_diag = 'kf_innov_alpha' in data and 'kf_K_00' in data
    # Guess active observer from psi_r vs rated: KF typically closer to rated (0.85 Vs)
    psi_check = float(np.asarray(data.get('psi_r_mag', [0.9])).mean())
    tag = '[KF]' if psi_check < 0.87 else '[det]'

    # --- numpy arrays for all signals ---
    omega_s = np.asarray(data.get('omega_s_rad_s', np.zeros(N)))
    speed   = np.asarray(data.get('Speed_rpm',     np.zeros(N)))
    psi_mag = np.asarray(data.get('psi_r_mag',     np.zeros(N)))
    id_arr  = np.asarray(data.get('id',            np.zeros(N)))
    iq_arr  = np.asarray(data.get('iq',            np.zeros(N)))
    id_cmd  = np.asarray(data.get('id_cmd',        np.zeros(N)))
    iq_cmd  = np.asarray(data.get('iq_cmd',        np.zeros(N)))
    ud_arr  = np.asarray(data.get('ud',            np.zeros(N)))

    id_err  = id_arr - id_cmd
    iq_err  = iq_arr - iq_cmd

    f_el   = float(omega_s.mean()) / (2 * math.pi)
    f_mech = float(speed.mean()) / 60.0
    f_slip = f_el - f_mech

    # --- harmonic amplitudes ---
    def ha(arr, k): return _amp_at(arr, k * f_el, fs) if f_el > 1.0 else 0.0

    # ===== HEADER =====
    _sec(f"{name}  {tag}")
    print(f"  Duration: {dur:.2f} s   N={N}   fs={fs:.0f} Hz")
    print(f"  Speed:    {speed.mean():.1f} ± {speed.std():.1f} RPM")
    print(f"  omega_s:  {omega_s.mean():.3f} ± {omega_s.std():.3f} rad/s  "
          f"(f_el={f_el:.2f} Hz,  f_slip={f_slip:.3f} Hz)")
    print(f"  psi_r:    {psi_mag.mean():.4f} Vs  std={psi_mag.std()/psi_mag.mean()*100:.3f}%  "
          f"[{psi_mag.min():.4f}, {psi_mag.max():.4f}]")

    # ===== D/Q TRACKING =====
    _sec("D/Q TRACKING")
    print(f"  id_error: mean={id_err.mean():+.4f} A  std={id_err.std():.4f} A  "
          f"peak={np.abs(id_err).max():.4f} A")
    print(f"  iq_error: mean={iq_err.mean():+.4f} A  std={iq_err.std():.4f} A  "
          f"peak={np.abs(iq_err).max():.4f} A")
    if id_err.std() > 0 and iq_arr.std() > 1e-3:
        r0 = float(np.corrcoef(id_err, iq_arr)[0, 1])
        note = "[high → coupling; check sigma_ls / psi_r]" if abs(r0) > 0.4 else "[OK]"
        print(f"  r(id_err, iq, lag=0): {r0:+.3f}  {note}")
    else:
        print(f"  iq constant — cross-correlation not applicable")

    # ===== HARMONIC ANALYSIS =====
    _sec("HARMONIC ANALYSIS")
    print(f"  f_el={f_el:.2f} Hz   f_mech={f_mech:.2f} Hz   f_slip={f_slip:.3f} Hz\n")

    # id_error and iq_error side by side (iq_error == iq when iq_cmd is constant)
    id_var = float(id_err.var())
    iq_var = float(iq_err.var())
    print(f"  {'Harmonic':18s}  {'freq':7s}   id_err [A] (%var)   iq_err [A] (%var)")
    print(f"  " + "-" * 62)
    for k in [1, 3, 5, 6, 7, 12]:
        aid = ha(id_err, k)
        aiq = ha(iq_err, k)
        pid = _pct_var(aid, id_var)
        piq = _pct_var(aiq, iq_var)
        flag = "  ← deadtime" if k == 6 and pid > 30 else ""
        print(f"  {k}×f_el = {k*f_el:6.1f} Hz:   "
              f"{aid:.5f}  ({pid:5.1f}%)   {aiq:.5f}  ({piq:5.1f}%){flag}")

    # Top 5 peaks in id_error and iq_error via FFT
    F_id, A_id = _fft(id_err, fs)
    F_iq, A_iq = _fft(iq_err, fs)
    peaks_id = _top_peaks(F_id, A_id)
    peaks_iq = _top_peaks(F_iq, A_iq)
    print(f"\n  Top 5 peaks:   id_error                   iq_error")
    for i in range(5):
        fi, ai = peaks_id[i]
        fq, aq = peaks_iq[i]
        print(f"    {fi:6.1f} Hz ({fi/f_el:.2f}×f_el): {ai:.5f} A   "
              f"{fq:6.1f} Hz ({fq/f_el:.2f}×f_el): {aq:.5f} A")

    # Note: iq_error harmonics identical to iq when iq_cmd is constant
    if iq_cmd.std() < 0.01:
        print(f"  (iq_cmd constant → iq_error harmonics = iq harmonics)")

    if 'ud_pi' in data:
        ud_pi = np.asarray(data['ud_pi'])
        ud_pi_dc = float(ud_pi.mean())
        ud_pi_var = float(ud_pi.var())
        id_mean = float(id_cmd.mean())
        rs_id = RS_OHM * id_mean
        deficit = ud_pi_dc - rs_id
        a6_ud = ha(ud_pi, 6)
        pct6_ud = _pct_var(a6_ud, ud_pi_var)
        print(f"\n  ud_pi:  DC={ud_pi_dc:+.3f} V   Rs×id_cmd={rs_id:.2f} V   "
              f"deficit={deficit:+.3f} V  std={ud_pi.std():.4f} V")
        print(f"          6×f_el = {6*f_el:.1f} Hz:  {a6_ud:.4f} V  ({pct6_ud:.1f}% of ud_pi variance)")

    # ===== DECOUPLING CHECK =====
    _sec("DECOUPLING CHECK")
    if ud_arr.std() > 0.01 and iq_arr.std() > 1e-3:
        r_ud_iq = float(np.corrcoef(ud_arr, iq_arr)[0, 1])
        note = "[high → sigma_ls or psi_r error]" if abs(r_ud_iq) > 0.3 else "[OK]"
        print(f"  r(Ud, iq) = {r_ud_iq:+.4f}  {note}")
    else:
        print(f"  iq constant — r(Ud, iq) not informative")
    # Expected steady-state Ud = Rs*id; any excess offset is integration error in PI
    id_mean = float(id_arr.mean())
    iq_mean = float(iq_arr.mean())
    ud_mean = float(ud_arr.mean())
    expected_ud_decoup = -omega_s.mean() * SIGMA_LS * iq_mean
    if 'ud_decoup' in data:
        ud_dec = float(np.asarray(data['ud_decoup']).mean())
        ud_pi_est = ud_mean - ud_dec
        print(f"  Mean Ud={ud_mean:.3f} V   ud_decoup={ud_dec:.3f} V   "
              f"ud_PI_est={ud_pi_est:.3f} V   (Rs×id={RS_OHM*id_mean:.2f} V)")
    else:
        ud_pi_est = ud_mean - expected_ud_decoup
        print(f"  Mean Ud={ud_mean:.3f} V   ud_decoup_est={expected_ud_decoup:.3f} V   "
              f"ud_PI_est={ud_pi_est:.3f} V   (Rs×id={RS_OHM*id_mean:.2f} V)")

    # ===== OBSERVER QUALITY =====
    _sec("OBSERVER QUALITY")
    print(f"  psi_r_mag: {psi_mag.mean():.4f} Vs  std={psi_mag.std():.5f} Vs  "
          f"({psi_mag.std()/psi_mag.mean()*100:.3f}%)")
    theta_err_std_deg = float('nan')
    if 'det_psi_r_alpha' in data:
        pa = np.asarray(data['det_psi_r_alpha'])
        pb = np.asarray(data['det_psi_r_beta'])
        raw = np.arctan2(pb, pa)
        unwrapped = np.unwrap(raw)
        t_arr = np.linspace(0, dur, N)
        p = np.polyfit(t_arr, unwrapped, 1)
        th_err = np.degrees(unwrapped - np.polyval(p, t_arr))
        theta_err_std_deg = float(th_err.std())
        a1_th = _amp_at(np.radians(th_err), f_el, fs)
        a6_th = _amp_at(np.radians(th_err), 6 * f_el, fs)
        print(f"  theta_err (det observer): std={th_err.std():.3f} deg  "
              f"peak={np.abs(th_err).max():.3f} deg   omega_fit={p[0]:.3f} rad/s")
        print(f"    1×f_el: {math.degrees(a1_th):.4f} deg   "
              f"6×f_el: {math.degrees(a6_th):.4f} deg")

    # ===== RESONANT CONTROLLER DIAGNOSTICS =====
    has_resonant = ('ud_res' in data and float(np.asarray(data['ud_res']).std()) > 0.01)
    if has_resonant:
        _sec("RESONANT CONTROLLER DIAGNOSTICS")
        for sig, lbl in [('ud_res', 'ud_res'), ('uq_res', 'uq_res')]:
            if sig not in data:
                continue
            r = np.asarray(data[sig])
            a6 = ha(r, 6)
            a3 = ha(r, 3)
            r_var = float(r.var())
            pct6 = _pct_var(a6, r_var)
            pct3 = _pct_var(a3, r_var)
            # Convergence check: split into 25 ms blocks, compute RMS per block
            block = max(1, int(0.025 * fs))
            n_blocks = len(r) // block
            if n_blocks >= 4:
                block_rms = np.array([np.sqrt(np.mean(r[i*block:(i+1)*block]**2))
                                      for i in range(n_blocks)])
                cv = float(block_rms.std() / block_rms.mean()) if block_rms.mean() > 0 else 0
                settled = "SETTLED" if cv < 0.10 else ("SETTLING" if cv < 0.25 else "OSCILLATING")
                print(f"  {lbl}: DC={r.mean():+.3f} V  std={r.std():.3f} V  "
                      f"amp@6f={a6:.3f} V ({pct6:.0f}%)  amp@3f={a3:.3f} V ({pct3:.0f}%)")
                print(f"         block-RMS: mean={block_rms.mean():.3f} V  "
                      f"std={block_rms.std():.3f} V  CV={cv*100:.1f}%  [{settled}]")
            else:
                print(f"  {lbl}: DC={r.mean():+.3f} V  std={r.std():.3f} V  "
                      f"amp@6f={a6:.3f} V ({pct6:.0f}%)")

        # Check omega_s stability as seen by the resonant controller
        # (determines how much the resonant center frequency drifts)
        omega_std = float(omega_s.std())
        f6_drift = 6 * omega_std / (2 * math.pi)
        print(f"\n  omega_s std = {omega_std:.3f} rad/s → 6th harmonic center drifts ±{f6_drift:.2f} Hz")
        # Resonant controller LPF time constant: alpha=0.002 at 25kHz → tau≈20ms, fc≈8Hz
        print(f"  Resonant LPF: alpha=0.002 → fc≈8 Hz, tau≈20 ms")
        if f6_drift > 0.5:
            print(f"  WARNING: ±{f6_drift:.2f} Hz drift at 6th harmonic — resonant may not settle")
            print(f"           Consider reducing alpha_res or using KF-derived f_el with PLL smoothing")
        else:
            print(f"  Frequency drift OK for resonant controller")

        # FFT of ud_res to check if energy is at 6*f_el or spread
        Fr, Ar = _fft(np.asarray(data['ud_res']), fs)
        peaks_r = _top_peaks(Fr, Ar, n=3)
        print(f"\n  ud_res top 3 peaks (concentrated = settled, spread = drifting):")
        for fp, ap in peaks_r:
            print(f"    {fp:6.1f} Hz ({fp/f_el:.2f}×f_el):  {ap:.4f} V")
        # Concentration metric: ratio of peak bin to total std
        conc = peaks_r[0][1] / np.asarray(data['ud_res']).std() if np.asarray(data['ud_res']).std() > 0 else 0
        print(f"  Peak/std ratio = {conc:.2f}  (>1.0 = concentrated at 6f, well-settled)")

    # ===== KF DIAGNOSTICS =====
    if has_kf_diag:
        _sec("KF DIAGNOSTICS")
        ac1_alpha = None
        for ch, lbl in [('kf_innov_alpha', 'innov_α'), ('kf_innov_beta', 'innov_β')]:
            y = np.asarray(data[ch])
            ac = _ac1(y)
            a6 = ha(y, 6)
            a6_norm = a6 / y.std() if y.std() > 0 else 0
            if abs(ac) < 0.10:
                verdict = "[WHITE — OK]"
            elif ac > 0.90:
                verdict = "[strongly correlated — persistent disturbance; tuning Q_i alone won't help]"
            elif ac > 0.10:
                verdict = ("[unmodeled harmonic dominant — enable resonant controller]" if a6_norm > 0.3
                           else f"[increase Q_i ×{1+4*ac:.2f}]")
            else:
                verdict = f"[decrease Q_i ×{1/(1+4*abs(ac)):.2f}]"
            print(f"  {lbl}: mean={y.mean():+.5f} A  std={y.std():.5f} A  "
                  f"AC(1)={ac:+.3f}  amp@6f={a6:.5f} A  {verdict}")
            if ch == 'kf_innov_alpha':
                ac1_alpha = ac

        for ch, lbl in [('kf_K_00', 'K[0][0]'), ('kf_K_11', 'K[1][1]')]:
            if ch not in data:
                continue
            k = np.asarray(data[ch])
            conv = 'CONVERGED' if k.std() / abs(k.mean()) < 0.01 else 'DRIFTING'
            print(f"  {lbl}: mean={k.mean():.5f}  std/mean={k.std()/abs(k.mean())*100:.2f}%  [{conv}]")

        if 'kf_S_00' in data:
            S = float(np.asarray(data['kf_S_00']).mean())
            K = float(np.asarray(data['kf_K_00']).mean())
            R_eff = S * (1.0 - K)
            print(f"  R_eff = {R_eff:.6f} A²   √R_eff = {math.sqrt(max(R_eff, 0)):.5f} A")

    # ===== SUMMARY =====
    _sec("SUMMARY")
    a6_id = ha(id_err, 6)
    pct6_id = _pct_var(a6_id, id_var)
    print(f"  Observer:    {tag}  omega_s={omega_s.mean():.2f} rad/s  "
          f"f_slip={f_slip:.3f} Hz  psi_r={psi_mag.mean():.4f} Vs")
    print(f"  Tracking:    id_std={id_err.std():.4f} A   iq_std={iq_err.std():.4f} A")
    print(f"  6th harmonic (deadtime): {a6_id:.4f} A  ({pct6_id:.0f}% of id variance)")
    if 'ud_pi' in data:
        ud_pi = np.asarray(data['ud_pi'])
        a6_ud = ha(ud_pi, 6)
        print(f"  ud_pi DC={ud_pi.mean():+.3f} V  (Rs*id={RS_OHM*float(id_cmd.mean()):.2f} V)   "
              f"6th harmonic={a6_ud:.4f} V")
    if has_kf_diag:
        y_a = np.asarray(data['kf_innov_alpha'])
        k00 = float(np.asarray(data['kf_K_00']).mean())
        print(f"  KF innov:    AC(1)={_ac1(y_a):+.3f}   K[0][0]={k00:.5f}")
    if not math.isnan(theta_err_std_deg):
        print(f"  Angle noise: theta_err std={theta_err_std_deg:.3f} deg")

    # Build and return metrics dict for comparison
    metrics = {
        'name':        name,
        'tag':         tag,
        'omega_s':     float(omega_s.mean()),
        'psi_r':       float(psi_mag.mean()),
        'psi_r_std_pct': float(psi_mag.std() / psi_mag.mean() * 100),
        'f_slip':      f_slip,
        'id_err_std':  float(id_err.std()),
        'iq_err_std':  float(iq_err.std()),
        'id_6th_A':    a6_id,
        'id_6th_pct':  pct6_id,
        'ud_pi_dc':       float(np.asarray(data['ud_pi']).mean()) if 'ud_pi' in data else float('nan'),
        'ud_pi_deficit':  abs(float(np.asarray(data['ud_pi']).mean()) - RS_OHM * float(id_cmd.mean())) if 'ud_pi' in data else float('nan'),
        'ud_pi_6th':   ha(np.asarray(data['ud_pi']), 6) if 'ud_pi' in data else float('nan'),
        'theta_err_std_deg': theta_err_std_deg,
        'kf_ac1':      _ac1(np.asarray(data['kf_innov_alpha'])) if has_kf_diag else float('nan'),
        'kf_K00':      float(np.asarray(data['kf_K_00']).mean()) if has_kf_diag else float('nan'),
    }
    return metrics


# ---------------------------------------------------------------------------
# Side-by-side comparison (only printed when 2 logs are given)
# ---------------------------------------------------------------------------

def print_comparison(m1, m2):
    _sec(f"COMPARISON:  {m1['tag']} {m1['name']}  vs  {m2['tag']} {m2['name']}")

    def row(label, v1, v2, fmt, better=""):
        """better: 'low'=smaller is better, 'high'=larger is better, ''=no verdict"""
        nan1, nan2 = math.isnan(v1), math.isnan(v2)
        diff = v2 - v1 if not (nan1 or nan2) else float('nan')
        v1s = f"{v1:{fmt}}" if not nan1 else "  n/a"
        v2s = f"{v2:{fmt}}" if not nan2 else "  n/a"
        diff_fmt = fmt.lstrip('+')
        ds = f"{diff:+{diff_fmt}}" if not math.isnan(diff) else ""
        if better and not math.isnan(diff):
            good = (diff < 0 and better == "low") or (diff > 0 and better == "high")
            verdict = "✓" if good else "✗"
        else:
            verdict = ""
        print(f"  {label:32s}  {v1s}   {v2s}   {ds:>10}  {verdict}")

    hdr = f"  {'Metric':32s}  {m1['tag']:>8}   {m2['tag']:>8}   {'change':>10}"
    print(hdr)
    print("  " + "-" * 66)
    # Diagnostic (no verdict)
    row("omega_s [rad/s]",          m1['omega_s'],       m2['omega_s'],       ".3f")
    row("f_slip [Hz]",              m1['f_slip'],        m2['f_slip'],        ".3f")
    row("psi_r [Vs]",               m1['psi_r'],         m2['psi_r'],         ".4f")
    print()
    # Tracking quality (lower is better)
    row("id_error std [A]",         m1['id_err_std'],    m2['id_err_std'],    ".4f", better="low")
    row("iq_error std [A]",         m1['iq_err_std'],    m2['iq_err_std'],    ".4f", better="low")
    row("id 6th harm [A]",          m1['id_6th_A'],      m2['id_6th_A'],      ".4f", better="low")
    row("id 6th harm [% id var]",   m1['id_6th_pct'],    m2['id_6th_pct'],    ".1f",  better="low")
    row("psi_r std [%]",            m1['psi_r_std_pct'], m2['psi_r_std_pct'], ".3f", better="low")
    print()
    # Decoupling quality (|deficit| = |ud_pi - Rs*id| lower is better)
    row("ud_pi DC [V]",             m1['ud_pi_dc'],      m2['ud_pi_dc'],      "+.3f")
    row("|ud_pi - Rs*id| [V]",      m1['ud_pi_deficit'], m2['ud_pi_deficit'], ".3f", better="low")
    row("ud_pi 6th harm [V]",       m1['ud_pi_6th'],     m2['ud_pi_6th'],     ".4f", better="low")
    print()
    # Observer / KF
    row("theta_err std [deg]",      m1['theta_err_std_deg'], m2['theta_err_std_deg'], ".3f", better="low")
    row("KF innov AC(1)",           m1['kf_ac1'],        m2['kf_ac1'],        "+.3f")
    row("KF K[0][0]",               m1['kf_K00'],        m2['kf_K00'],        ".5f")
    print()
    print(f"  ✓ = {m2['tag']} is better   ✗ = {m2['tag']} is worse   (blank = no clear verdict)")


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description='IM FOC + observer analysis (combined analyze_foc + analyze_kf)')
    parser.add_argument('logs', nargs='*',
                        help='1 or 2 JavaScope CSV log files (2 = det vs KF comparison). '
                             'Omit when using --print-channels.')
    parser.add_argument('--print-channels', action='store_true',
                        help='Print properties.ini channel preset for commissioning and exit')
    parser.add_argument('--motor-config', metavar='FILE',
                        help='Path to motor_config.h to load Rs, Lm, Lr, sigma_Ls. '
                             'Defaults to auto-detect in the repo. '
                             'Falls back to hardcoded Lindner 3kW values if not found.')
    args = parser.parse_args()

    # --- Print channel preset and exit ---------------------------------------
    if args.print_channels:
        try:
            jso = parse_jso_enum()
        except FileNotFoundError as e:
            print(f"ERROR: {e}", file=sys.stderr)
            sys.exit(1)
        print("Required GUI state for commissioning log:")
        print("  MB4 ON (FOC), MB6 ON for KF diagnostics (optional), MB8 ON for resonant")
        print("  Log at steady operating point (rated flux, any speed/load)")
        print()
        print_ini_section("analyze_im.py — commissioning / FOC analysis", _CHANNELS_COMMISSIONING, jso)
        return

    if not args.logs:
        parser.error("at least one log file is required (or use --print-channels)")

    global RS_OHM, LM_H, LR_H, SIGMA_LS
    try:
        cfg = load_motor_config(args.motor_config)
        RS_OHM   = cfg['Rs_Ohm']
        LM_H     = cfg['Lm_H']
        LR_H     = cfg['Lr_H']
        SIGMA_LS = cfg['sigma_Ls_H']
        print(f"[motor_config] {cfg['_source']}  [{cfg['_active_config']}]")
        print(f"  Rs={RS_OHM} Ω  Lm={LM_H*1e3:.3f} mH  Lr={LR_H*1e3:.3f} mH  "
              f"σLs={SIGMA_LS*1e3:.4f} mH")
    except FileNotFoundError:
        if args.motor_config:
            # User specified a path explicitly — this is an error
            print(f"ERROR: motor_config.h not found: {args.motor_config}", file=sys.stderr)
            sys.exit(1)
        print("[motor_config] not found — using hardcoded Lindner 3 kW defaults")

    results = []
    for path in args.logs[:2]:
        m = analyze_log(path)
        if m:
            results.append(m)
        print()

    if len(results) == 2:
        print_comparison(results[0], results[1])


if __name__ == '__main__':
    main()
