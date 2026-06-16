#pragma once
/******************************************************************************
 * Motor / machine configuration
 *
 * Select the active machine by changing MOTOR_CONFIG_SELECT below.
 * To support a new machine, define a new MOTOR_CONFIG_<NAME> constant and
 * add a corresponding #if block with all required parameters.
 *
 * Parameters collected here are those that differ between machines:
 *   - Electrical nameplate (Rs, Rr, Lm, leakage inductances, pole pairs)
 *   - Mechanical (inertia J)
 *   - Rated operating point (Psi_rated, control current limit)
 *   - Protection limits (v_dc_min_v, vdc_max_v, phase-current trip limit, Speed_max)
 *   - Control tuning (Speed PI gains, resonant gain scale, KF noise defaults)
 *   - U/f open-loop parameters (V/f ratio, boost, frequency limits)
 *
 * ALL electrical parameters are STAR-EQUIVALENT (per-phase, referred to neutral).
 * The firmware drives line-to-neutral voltages and measures line currents; the
 * Clarke/Park transforms and the observer operate in the star-equivalent domain.
 *
 *   Star-connected motor  — use nameplate values directly.
 *   Delta-connected motor — convert: R_star = R_delta / 3,  L_star = L_delta / 3.
 *
 *   If you use identify_motor_params.py to extract Rs/Lm/Rr from JavaScope logs
 *   the result is already star-equivalent regardless of motor connection.
 *
 *   Psi_rated (rotor flux at rated operating point):
 *     Psi_rated ≈ V_rated_line_to_line / (sqrt(3) * 2*pi * f_rated)
 *   This formula is the same for both star and delta motor connections because
 *   the inverter always presents line-to-neutral voltage to the star-equivalent model.
 *
 * Hardware-specific settings (PWM frequency, encoder resolution, deadtime,
 * IP instance counts) remain in uz_global_configuration.h.
 ******************************************************************************/

/* ===== Available configurations ===== */
#define MOTOR_CONFIG_LINDNER_3KW        1
#define MOTOR_CONFIG_SIEMENS_1LA7073    2   /* Siemens 1LA7073-4AB10-Z, 0.37 kW, delta 230V / star 400V */
#define MOTOR_CONFIG_SIEMENS_1C4164B    3

/* ===== Select active motor configuration ===== */
#define MOTOR_CONFIG_SELECT  MOTOR_CONFIG_SIEMENS_1C4164B

/* VA hardware protection limits are board-specific and independent of the IM under test. */
#define VA_VDC_MAX_V              52.0f
#define VA_IPHASE_MAX_A           15.0f

/* Preliminary IM DC-link undervoltage threshold for test bench protection. */
#define v_dc_min_v                100.0f


/* ============================================================
 * Lindner 3 kW IM — Wolfspeed adapter board testbed
 * ============================================================ */
#if (MOTOR_CONFIG_SELECT == MOTOR_CONFIG_LINDNER_3KW)

/* Electrical nameplate */
#define MOTOR_Rs_Ohm              2.1f
#define MOTOR_Rr_Ohm              2.4f
#define MOTOR_Lm_H                0.350f        /* magnetizing inductance */
#define MOTOR_Lsigma_s_H          8.5e-3f       /* stator leakage inductance */
#define MOTOR_Lsigma_r_H          8.5e-3f       /* rotor leakage — assumed equal to stator leakage */
#define MOTOR_PolePairs           1.0f

/* Mechanical */
#define MOTOR_J_kgm2              0.01f         /* rotor inertia [kg·m²] */

/* Rated operating point */
#define MOTOR_Psi_rated_Vs                0.85f   /* rated rotor flux magnitude [Vs] */
#define MOTOR_Control_current_max_A      10.0f   /* soft limit used by IM control and speed-loop output saturation */

/* Protection limits — hardware-level fault thresholds */
#define vdc_max_v                          700.0f
#define MOTOR_Protection_phase_max_A       20.0f   /* hard trip threshold checked against measured phase currents */
#define MOTOR_Speed_max_rpm               3300.0f

/* Current PI gains — scaling factors applied on top of the symmetric-optimum base:
 *   kp_base = sigma_ls / (2*Ts),  ki_base = Rs / (2*Ts)
 * Reduce these factors if current overshoots; increase for faster response. */
#define MOTOR_Current_Kp_scale    0.1f
#define MOTOR_Current_Ki_scale    0.2f

/* Speed PI gains — re-tune for your load inertia and bandwidth requirement */
#define MOTOR_Speed_Kp            0.005f
#define MOTOR_Speed_Ki            0.05f

/* Resonant (6th harmonic) controller gain as a fraction of the current PI kp */
#define MOTOR_Resonant_gain_scale 0.3f

/* Default Kalman filter noise matrices (overridable at runtime via JavaScope SF9/SF7/SF8) */
#define MOTOR_KF_Q_i              1.0e-5f       /* process noise — stator current states */
#define MOTOR_KF_Q_psi            1.0e-7f       /* process noise — rotor flux states */
#define MOTOR_KF_R_i              5.0e-2f       /* measurement noise — stator current */

/* ADC current scaling for IM phase current channels on the Wolfspeed v1.1 board */
#define MOTOR_CURRENT_2_SI            0.0242f

/* U/f open-loop parameters (all voltages in RMS line-to-line, nameplate convention) */
#define MOTOR_UF_ratio_V_per_Hz       8.0f      /* 400 V / 50 Hz — confirm rated voltage on nameplate */
#define MOTOR_UF_boost_voltage_V      5.0f
#define MOTOR_UF_max_voltage_V        400.0f    /* rated RMS L-L — caps voltage at any frequency */
#define MOTOR_UF_max_frequency_Hz     50.0f     /* rated frequency */
#define MOTOR_UF_frequency_ramp_Hz_per_s 5.0f  /* conservative ramp for commissioning */

/* Speed outlier-rejection gate defaults — see speed_ol_filter.h for full documentation. */
#define MOTOR_SPEED_OL_THR_SCALE      0.10f   /* window half-width as fraction of |y_prev| */
#define MOTOR_SPEED_OL_THR_MIN_RPM    100.0f  /* minimum window half-width [RPM] — must be >= 80 */

#endif /* MOTOR_CONFIG_SELECT == MOTOR_CONFIG_LINDNER_3KW */


/* ============================================================
 * Siemens 1LA7073-4AB10-Z  0.37 kW IM
 * Δ/Y: 230 V / 400 V,  50 Hz,  2 pole pairs
 * ============================================================
 *
 * Source: SINAMICS STARTER equivalent-circuit parameters (star-equivalent).
 *   Table 4 / English datasheet:  R1=7.05 Ω, R2=6.23 Ω, Lm=271 mH,
 *                                  L1σ=31.3 mH, L2σ=35.6 mH
 *   These are already star-equivalent values — use directly.
 *   (The German Tab. 15 lists delta-circuit values, which are ×3 larger.)
 *
 * Rated operating point:
 *   Rated line current (Δ at 230 V): 1.82 A (line current = Δ phase current × √3)
 *   Magnetising current I_μ: 1.26 A  (from STARTER table)
 *   Psi_rated = Lm × I_μ = 0.271 × 1.26 ≈ 0.341 Vs
 *     (preferred over voltage formula: large σLs = 62.7 mH causes
 *      significant stator-leakage voltage drop, making V_LL/√3·2πf inaccurate)
 *   id_ref = Psi_rated / Lm ≈ 1.26 A
 *
 * PI gains: run calc_pi_gains.py after setting MOTOR_CONFIG_SELECT = 2.
 * ============================================================ */
#if (MOTOR_CONFIG_SELECT == MOTOR_CONFIG_SIEMENS_1LA7073)

/* Electrical nameplate — all STAR-EQUIVALENT (from STARTER Table 4) */
#define MOTOR_Rs_Ohm              7.05f
#define MOTOR_Rr_Ohm              6.23f
#define MOTOR_Lm_H                0.271f        /* magnetizing inductance */
#define MOTOR_Lsigma_s_H          31.3e-3f      /* stator leakage inductance */
#define MOTOR_Lsigma_r_H          35.6e-3f      /* rotor leakage inductance */
#define MOTOR_PolePairs           2.0f

/* Mechanical */
#define MOTOR_J_kgm2              8.12e-4f      /* rotor inertia [kg·m²] (from datasheet) */

/* Rated operating point */
#define MOTOR_Psi_rated_Vs                0.341f  /* = Lm × I_mu = 0.271 × 1.26 A */
#define MOTOR_Control_current_max_A       6.0f    /* soft limit used by IM control and speed-loop output saturation */

/* Protection limits — hardware-level fault thresholds */
#define vdc_max_v                          400.0f
#define MOTOR_Protection_phase_max_A       6.0f    /* hard trip threshold checked against measured phase currents */
#define MOTOR_Speed_max_rpm               1800.0f /* 1.2× synchronous speed (1500 rpm) */

/* Current PI gains — run calc_pi_gains.py for best values; conservative start */
#define MOTOR_Current_Kp_scale    0.1f
#define MOTOR_Current_Ki_scale    0.2f

/* Speed PI gains — run calc_pi_gains.py; start very conservatively */
#define MOTOR_Speed_Kp            0.001f
#define MOTOR_Speed_Ki            0.05f

/* Resonant (6th harmonic) controller gain as a fraction of the current PI kp */
#define MOTOR_Resonant_gain_scale 0.3f

/* Default Kalman filter noise matrices (overridable at runtime via JavaScope SF9/SF7/SF8) */
#define MOTOR_KF_Q_i              1.0e-5f       /* process noise — stator current states */
#define MOTOR_KF_Q_psi            1.0e-7f       /* process noise — rotor flux states */
#define MOTOR_KF_R_i              5.0e-2f       /* measurement noise — stator current */

/* ADC current scaling for IM phase current channels on the Wolfspeed v2.0 board */
#define MOTOR_CURRENT_2_SI            0.03993f

/* U/f open-loop parameters (all voltages in RMS line-to-line, nameplate convention)
 * Motor is delta-connected at 230 V / 50 Hz. */
#define MOTOR_UF_ratio_V_per_Hz       4.6f      /* 230 V / 50 Hz */
#define MOTOR_UF_boost_voltage_V      5.0f
#define MOTOR_UF_max_voltage_V        225.0f    /* rated RMS L-L (delta at 230 V) */
#define MOTOR_UF_max_frequency_Hz     50.0f     /* rated frequency */
#define MOTOR_UF_frequency_ramp_Hz_per_s 5.0f  /* conservative ramp for commissioning */

/* Speed outlier-rejection gate defaults — see speed_ol_filter.h for full documentation. */
#define MOTOR_SPEED_OL_THR_SCALE      0.10f   /* window half-width as fraction of |y_prev| */
#define MOTOR_SPEED_OL_THR_MIN_RPM    100.0f  /* minimum window half-width [RPM] — must be >= 80 */

#endif /* MOTOR_CONFIG_SELECT == MOTOR_CONFIG_SIEMENS_1LA7073 */

#if (MOTOR_CONFIG_SELECT == MOTOR_CONFIG_SIEMENS_1C4164B)

/* From Calculations */
#define MOTOR_Rs_Ohm              178.5e-3f
#define MOTOR_Rr_Ohm              122.4e-3f
#define MOTOR_Lm_H                52.1e-3f       /* magnetizing inductance */
#define MOTOR_Lsigma_s_H          1.48e-3f      /* stator leakage inductance */
#define MOTOR_Lsigma_r_H          2.23e-3f      /* rotor leakage inductance */
#define MOTOR_PolePairs           2.0f

/* Mechanical */
#define MOTOR_J_kgm2              0.0990      /* rotor inertia [kg·m²] (from datasheet) */

/* Rated operating point */
#define MOTOR_Psi_rated_Vs                1.0f    /* MOTOR_Lm_H* I_ma/I_D = 13.4A * sqrt(2) = 52.1e-3f* 19A */
#define MOTOR_Control_current_max_A      50.0f //50.0f

/* Protection limits — hardware-level fault thresholds */
#define vdc_max_v                          800.0f //800.0f
#define MOTOR_Protection_phase_max_A       50.0f //50.0f   /* hard trip threshold checked against measured phase currents */
#define MOTOR_Speed_max_rpm               5000.0f  /* 1.2× synchronous speed (1500 rpm) */

/* Current PI gains — run calc_pi_gains.py for best values; conservative start */
#define MOTOR_Current_Kp_scale    0.1f
#define MOTOR_Current_Ki_scale    0.2f

/* Speed PI gains — run calc_pi_gains.py; start very conservatively */
#define MOTOR_Speed_Kp            0.001f
#define MOTOR_Speed_Ki            0.05f

/* Resonant (6th harmonic) controller gain as a fraction of the current PI kp */
#define MOTOR_Resonant_gain_scale 0.3f

/* Default Kalman filter noise matrices (overridable at runtime via JavaScope SF9/SF7/SF8) */
#define MOTOR_KF_Q_i              1.0e-5f       /* process noise — stator current states */
#define MOTOR_KF_Q_psi            1.0e-7f       /* process noise — rotor flux states */
#define MOTOR_KF_R_i              5.0e-2f       /* measurement noise — stator current */

/* ADC current scaling for IM phase current channels on the Wolfspeed v2.0 board */
#define MOTOR_CURRENT_2_SI            0.03993f

/* U/f open-loop parameters (all voltages in RMS line-to-line, nameplate convention)
 * Motor is delta-connected at 230 V / 50 Hz. */
#define MOTOR_UF_ratio_V_per_Hz       8.0f      /* 400 V / 50 Hz */
#define MOTOR_UF_boost_voltage_V      1.0f
#define MOTOR_UF_max_voltage_V        399.0f    /* rated RMS L-L (star at 400 V, phase Voltage 230V) */
#define MOTOR_UF_max_frequency_Hz     50.0f     /* rated frequency */
#define MOTOR_UF_frequency_ramp_Hz_per_s 2.5f  /* conservative ramp for commissioning */

/* Speed outlier-rejection gate defaults — see speed_ol_filter.h for full documentation. */
#define MOTOR_SPEED_OL_THR_SCALE      0.10f   /* window half-width as fraction of |y_prev| */
#define MOTOR_SPEED_OL_THR_MIN_RPM    100.0f  /* minimum window half-width [RPM] — must be >= 80 */

#endif /* MOTOR_CONFIG_SELECT == MOTOR_CONFIG_SIEMENS_1C4164B */

#if (MOTOR_CONFIG_SELECT != MOTOR_CONFIG_LINDNER_3KW) && \
    (MOTOR_CONFIG_SELECT != MOTOR_CONFIG_SIEMENS_1LA7073) && \
    (MOTOR_CONFIG_SELECT != MOTOR_CONFIG_SIEMENS_1C4164B)
#error "Unknown MOTOR_CONFIG_SELECT in motor_config.h"
#endif
