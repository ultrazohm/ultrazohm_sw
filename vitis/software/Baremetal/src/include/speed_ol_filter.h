#pragma once
/* Speed Outlier-Rejection Gate for the IM mechanical rotor speed IIR filter
 * ==========================================================================
 *
 * The analog speed sensor produces two distinct noise regimes:
 *
 *   0–1400 RPM (ramp):   moderate symmetric noise, σ ≈ 40 RPM — plain IIR sufficient
 *   1400–1520 RPM (rated): heavy negative spike tail, bias ≈ −148 RPM, spikes ±500 RPM
 *
 * A plain 1 Hz IIR tracks the arithmetic mean of the raw signal. At rated speed
 * the mean is ~148 RPM below truth — no linear filter can remove this because it
 * is a distributional property, not a cutoff-frequency issue.
 *
 * Gate logic (runs every ISR step, before the IIR):
 *
 *   threshold = max(THR_MIN_RPM, THR_SCALE * |y_prev|)
 *
 *   if |raw − y_prev| ≤ threshold:  pass raw to IIR
 *   else:                            pass y_prev  (hold last estimate)
 *
 * THR_SCALE makes the acceptance window proportional to the current speed
 * estimate: 0.10 → ±10 % of |y_prev| (e.g. ±150 RPM at 1500 RPM).
 * Increasing it accepts noisier samples; decreasing it rejects more aggressively.
 *
 * THR_MIN_RPM prevents the window from collapsing to zero at standstill, which
 * would freeze the filter (lock-up). Keep THR_MIN_RPM ≥ 80 RPM.
 *
 * Default values (MOTOR_SPEED_OL_THR_SCALE / MOTOR_SPEED_OL_THR_MIN_RPM from
 * motor_config.h) can be overridden at runtime via JavaScope SF12/SF13.
 *
 * Offline validation on log u_f_1703_04 (SIEMENS_1C4164B, 750 V, no load):
 *   rated speed RMSE  14 RPM   (plain 1 Hz IIR: 150 RPM)
 *   ramp 0–1400 RPM   unchanged (noise std < floor, gate is transparent)
 *
 * Lock-up safety: the filter state is reset to 0 in reset_im(), which is called
 * on every motor stop. Since the motor always starts from standstill the initial
 * y_prev = 0 is always correct, and the ramp rate (~25 RPM/s) keeps each new
 * sample within the 100 RPM floor — no lock-up possible during normal ramp-up.
 */

/* Runtime-configurable gate parameters (defined in isr.c, initialised from
 * MOTOR_SPEED_OL_THR_SCALE / MOTOR_SPEED_OL_THR_MIN_RPM in motor_config.h).
 * Writable via JavaScope SF12 / SF13. */
extern float speed_ol_thr_scale;     /* window half-width as fraction of |y_prev| */
extern float speed_ol_thr_min_rpm;   /* minimum window half-width [RPM], must be >= 80 */

/* Set to false via JavaScope My_Button_1 (Toggle_SpeedOL) to bypass the gate
 * and feed raw samples directly to the IIR — useful for A/B comparison. */
extern bool enable_speed_outlier_rejection;
