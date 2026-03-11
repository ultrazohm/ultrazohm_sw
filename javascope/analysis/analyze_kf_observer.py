"""
Kalman filter observer stability analysis for UltraZohm JavaScope logs.

Checks whether the KF output (psi_r_mag, theta_el, omega_s_rad_s) is stable
enough for the resonant controller to track 6*omega_s.

Run:
    python analyze_kf_observer.py <path_to_csv>
"""

import sys
import os
import math
import numpy as np

sys.path.insert(0, os.path.dirname(__file__))
from load_log import load_log


def _sep():
    print("=" * 60)


def _top_peaks(freqs, amp, n=8):
    idx = np.argsort(amp)[-n:][::-1]
    return [(freqs[i], amp[i]) for i in idx]


def _spectrum(arr, fs):
    x = np.asarray(arr, dtype=float)
    x = x - x.mean()
    N = len(x)
    A = np.abs(np.fft.rfft(x)) * 2.0 / N
    F = np.fft.rfftfreq(N, d=1.0 / fs)
    return F, A


def _dft_at(arr, freq, fs):
    x = np.asarray(arr, dtype=float)
    mu = x.mean()
    n = len(x)
    t = np.arange(n) / fs
    re = np.mean((x - mu) * np.cos(2 * math.pi * freq * t)) * 2
    im = np.mean((x - mu) * np.sin(2 * math.pi * freq * t)) * 2
    return math.sqrt(re**2 + im**2)


def analyze(path):
    data, fs = load_log(path)
    if fs <= 0:
        print("ERROR: could not determine sample rate"); sys.exit(1)
    dt = 1.0 / fs
    N = len(data.get('time', []))

    print(f"Log: {os.path.basename(path)}")
    print(f"Channels available: {sorted(data.keys())}")
    print(f"N={N}  fs={fs:.0f} Hz  duration={N*dt:.2f} s\n")

    # ------------------------------------------------------------------ #
    #  1. omega_s_rad_s stability
    # ------------------------------------------------------------------ #
    _sep()
    print("  OMEGA_S (synchronous speed) STABILITY")
    _sep()
    if 'omega_s_rad_s' not in data:
        print("  omega_s_rad_s: NOT IN LOG")
    else:
        w = np.asarray(data['omega_s_rad_s'], dtype=float)
        w_mean = w.mean()
        w_std  = w.std()
        f_el   = w_mean / (2 * math.pi)
        print(f"  mean = {w_mean:.4f} rad/s  ({f_el:.3f} Hz)")
        print(f"  std  = {w_std:.4f} rad/s  ({w_std/w_mean*100:.3f}% of mean)")
        print(f"  peak-to-peak = {w.max()-w.min():.4f} rad/s")

        # Rate of change (delta per sample)
        dw = np.diff(w) * fs
        print(f"  dω/dt: mean={dw.mean():.2f} rad/s²  std={dw.std():.2f} rad/s²  "
              f"peak={np.abs(dw).max():.2f} rad/s²")

        # At 6*omega_s, a shift of delta_omega shifts resonant peak by 6*delta_omega
        # Resonant controller has -3dB bandwidth ~ Kr/2 (rough approximation).
        # Just report the detuning in terms of multiples of f_el.
        w_6th_shift = 6 * w_std
        print(f"\n  Resonant controller detuning estimate (6*std):")
        print(f"    ±{w_6th_shift:.3f} rad/s  (= ±{w_6th_shift/(2*math.pi):.3f} Hz at 6th harmonic)")

        # Spectrum of omega_s
        F, A = _spectrum(w, fs)
        peaks = _top_peaks(F, A, 8)
        print(f"\n  Top spectral peaks in omega_s:")
        for f, a in peaks:
            if a < 1e-6: continue
            print(f"    f={f:7.2f} Hz  amp={a:.5f} rad/s")

    # ------------------------------------------------------------------ #
    #  2. psi_r_mag stability
    # ------------------------------------------------------------------ #
    _sep()
    print("  PSI_R_MAG STABILITY")
    _sep()
    if 'psi_r_mag' not in data:
        print("  psi_r_mag: NOT IN LOG")
    else:
        psi = np.asarray(data['psi_r_mag'], dtype=float)
        psi_mean = psi.mean()
        psi_std  = psi.std()
        print(f"  mean = {psi_mean:.5f} Vs")
        print(f"  std  = {psi_std:.5f} Vs  ({psi_std/psi_mean*100:.3f}% of mean)")
        print(f"  min={psi.min():.5f}  max={psi.max():.5f} Vs")

        dpsi = np.diff(psi) * fs
        print(f"  d|ψ|/dt: mean={dpsi.mean():.4f} Vs/s  std={dpsi.std():.4f} Vs/s  "
              f"peak={np.abs(dpsi).max():.4f} Vs/s")

        F, A = _spectrum(psi, fs)
        peaks = _top_peaks(F, A, 8)
        if 'omega_s_rad_s' in data:
            f_el = np.asarray(data['omega_s_rad_s']).mean() / (2 * math.pi)
            print(f"\n  DFT of psi_r_mag at harmonic frequencies (f_el={f_el:.3f} Hz):")
            for h in [1, 2, 3, 6, 12]:
                a = _dft_at(psi, h * f_el, fs)
                print(f"    {h}*f_el = {h*f_el:.2f} Hz: amp={a:.5f} Vs")
        print(f"\n  Top spectral peaks in psi_r_mag:")
        for f, a in peaks:
            if a < 1e-6: continue
            print(f"    f={f:7.2f} Hz  amp={a:.5f} Vs")

    # ------------------------------------------------------------------ #
    #  3. theta_el: unwrap and compare derived omega_s to logged
    # ------------------------------------------------------------------ #
    _sep()
    print("  THETA_EL — ANGLE QUALITY")
    _sep()
    if 'theta_el' not in data:
        print("  theta_el: NOT IN LOG")
    else:
        theta = np.asarray(data['theta_el'], dtype=float)
        theta_uw = np.unwrap(theta)

        # Fit linear trend → extract omega_s_fit
        t = np.arange(len(theta_uw)) * dt
        p = np.polyfit(t, theta_uw, 1)
        omega_s_fit = p[0]
        theta_err = theta_uw - np.polyval(p, t)

        theta_err_deg = np.degrees(theta_err)
        print(f"  omega_s from linear fit: {omega_s_fit:.4f} rad/s  "
              f"({omega_s_fit/(2*math.pi):.3f} Hz)")
        print(f"  theta residual (after linear detrend):")
        print(f"    std={theta_err_deg.std():.4f} deg  "
              f"peak={np.abs(theta_err_deg).max():.4f} deg")

        # Check if derived omega_s matches logged
        if 'omega_s_rad_s' in data:
            w_logged = np.asarray(data['omega_s_rad_s']).mean()
            print(f"  omega_s logged={w_logged:.4f} vs fit={omega_s_fit:.4f} "
                  f"(diff={abs(w_logged-omega_s_fit):.4f} rad/s)")

        # Local omega_s from differentiation (sample-by-sample)
        omega_inst = np.diff(theta_uw) * fs
        print(f"\n  Instantaneous dθ/dt (= local omega_s):")
        print(f"    mean={omega_inst.mean():.4f} rad/s  std={omega_inst.std():.4f} rad/s")
        print(f"    This is the frequency actually seen by the resonant controller.")
        if omega_inst.std() > 0:
            print(f"    6*std = {6*omega_inst.std():.3f} rad/s detuning at 6th harmonic "
                  f"({6*omega_inst.std()/(2*math.pi):.3f} Hz)")

        # Spectrum of theta_err
        if 'omega_s_rad_s' in data:
            f_el = np.asarray(data['omega_s_rad_s']).mean() / (2 * math.pi)
            F, A = _spectrum(theta_err_deg, fs)
            print(f"\n  DFT of theta_err at harmonic frequencies (f_el={f_el:.3f} Hz):")
            for h in [1, 2, 3, 6, 12]:
                a = _dft_at(theta_err_deg, h * f_el, fs)
                print(f"    {h}*f_el = {h*f_el:.2f} Hz: amp={a:.5f} deg")
            peaks = _top_peaks(F, A, 5)
            print(f"  Top spectral peaks in theta_err:")
            for f, a in peaks:
                if a < 1e-6: continue
                print(f"    f={f:7.2f} Hz  amp={a:.5f} deg")

    # ------------------------------------------------------------------ #
    #  4. KF innovations
    # ------------------------------------------------------------------ #
    _sep()
    print("  KF INNOVATIONS (whiteness check)")
    _sep()
    for ch, label in [('kf_innov_alpha', 'innov_α'), ('kf_innov_beta', 'innov_β')]:
        if ch not in data:
            print(f"  {label}: NOT IN LOG"); continue
        y = np.asarray(data[ch], dtype=float)
        y_mean = y.mean()
        y_std  = y.std()
        # Autocorrelation at lag 1 (should be ~0 for white innovations)
        ac1 = np.corrcoef(y[:-1], y[1:])[0, 1]
        print(f"  {label}: mean={y_mean:+.4f} A  std={y_std:.4f} A  autocorr(lag1)={ac1:+.4f}")
        if 'omega_s_rad_s' in data:
            f_el = np.asarray(data['omega_s_rad_s']).mean() / (2 * math.pi)
            a6 = _dft_at(y, 6 * f_el, fs)
            print(f"           amp at 6*f_el={6*f_el:.1f} Hz: {a6:.5f} A")

    # ------------------------------------------------------------------ #
    #  5. KF gain convergence
    # ------------------------------------------------------------------ #
    _sep()
    print("  KF GAIN CONVERGENCE")
    _sep()
    for ch, label in [('kf_K_00', 'K[0][0]'), ('kf_K_11', 'K[1][1]')]:
        if ch not in data:
            print(f"  {label}: NOT IN LOG"); continue
        k = np.asarray(data[ch], dtype=float)
        dk = np.diff(k) * fs
        print(f"  {label}: mean={k.mean():.6f}  std={k.std():.6f}  "
              f"drift_rate={dk.std():.4f}/s  "
              f"{'CONVERGED' if k.std()/abs(k.mean()) < 0.01 else 'NOT CONVERGED'}")

    # ------------------------------------------------------------------ #
    #  6. Resonant controller readiness verdict
    # ------------------------------------------------------------------ #
    _sep()
    print("  RESONANT CONTROLLER READINESS VERDICT")
    _sep()
    if 'omega_s_rad_s' in data and 'theta_el' in data:
        w = np.asarray(data['omega_s_rad_s'])
        theta = np.asarray(data['theta_el'])
        theta_uw = np.unwrap(theta)
        omega_inst = np.diff(theta_uw) * fs

        w_std_pct = w.std() / w.mean() * 100
        omega_inst_std_pct = omega_inst.std() / omega_inst.mean() * 100 if omega_inst.mean() != 0 else 999

        print(f"  omega_s std:              {w.std():.4f} rad/s  ({w_std_pct:.3f}%)")
        print(f"  local dθ/dt std:          {omega_inst.std():.4f} rad/s  ({omega_inst_std_pct:.3f}%)")
        print(f"  6th harmonic detuning:    ±{6*omega_inst.std()/(2*math.pi):.3f} Hz")

        # Rough bandwidth of resonant controller: Kr*Ts/2 in Hz  (impulse-invariant)
        # We don't know Kr here, so just report the detuning and let the user judge
        if omega_inst_std_pct < 0.5:
            verdict = "GOOD — observer stable enough for resonant controller"
        elif omega_inst_std_pct < 2.0:
            verdict = "MARGINAL — resonant controller may be partially detuned"
        else:
            verdict = "POOR — observer too noisy; resonant controller will be detuned"
        print(f"\n  Verdict: {verdict}")
    else:
        print("  Cannot compute verdict: omega_s_rad_s or theta_el missing from log")
    print()


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python analyze_kf_observer.py <path_to_csv>")
        sys.exit(1)
    analyze(sys.argv[1])
