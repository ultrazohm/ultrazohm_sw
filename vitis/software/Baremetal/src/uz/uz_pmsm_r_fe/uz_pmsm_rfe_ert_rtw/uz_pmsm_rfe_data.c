/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_pmsm_rfe_data.c
 *
 * Code generated for Simulink model 'uz_pmsm_rfe'.
 *
 * Model version                  : 6.2
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Mon Feb  5 22:51:29 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "uz_pmsm_rfe.h"

/* Block parameters (default storage) */
P rtP = {
  /* Variable: Ld
   * Referenced by:
   *   '<S1>/L_d1'
   *   '<S1>/L_d2'
   *   '<S1>/L_d3'
   *   '<S1>/1//L_d'
   */
  3.0E-5,

  /* Variable: Lq
   * Referenced by:
   *   '<S1>/L_q1'
   *   '<S1>/L_q2'
   *   '<S1>/L_q3'
   *   '<S1>/1//L_q'
   */
  5.0E-5,

  /* Variable: PN
   * Referenced by:
   *   '<S1>/1.5*Z_p'
   *   '<S1>/1.5*Z_p1'
   */
  5.0,

  /* Variable: psi_pm
   * Referenced by:
   *   '<S1>/Gesamtfluss PM'
   *   '<S1>/Gesamtfluss PM1'
   */
  0.007,

  /* Variable: r_cd
   * Referenced by:
   *   '<S1>/q-Komponente Eisenwiderstand'
   *   '<S1>/Rs//Rc_d'
   */
  1.63543915748596,

  /* Variable: r_cq
   * Referenced by:
   *   '<S1>/d-Komponente Eisenwiderstand'
   *   '<S1>/Rs//Rc_q'
   */
  1.63543915748596,

  /* Variable: r_s
   * Referenced by:
   *   '<S1>/Rs//Rc_d'
   *   '<S1>/Rs//Rc_q'
   *   '<S1>/Statorwiderstand_d'
   *   '<S1>/Statorwiderstand_q'
   */
  0.023,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<S1>/Discrete-Time Integrator'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S1>/Discrete-Time Integrator'
   */
  0.0,

  /* Computed Parameter: DiscreteTimeIntegrator1_gainval
   * Referenced by: '<S1>/Discrete-Time Integrator1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S1>/Discrete-Time Integrator1'
   */
  0.0,

  /* Computed Parameter: uRc_d_Gain
   * Referenced by: '<S1>/1//Rc_d'
   */
  0.611456573F,

  /* Computed Parameter: uRc_q_Gain
   * Referenced by: '<S1>/1//Rc_q'
   */
  0.611456573F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
