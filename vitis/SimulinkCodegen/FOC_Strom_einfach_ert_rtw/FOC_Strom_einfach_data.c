/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_Strom_einfach_data.c
 *
 * Code generated for Simulink model 'FOC_Strom_einfach'.
 *
 * Model version                  : 2.3
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jul 14 12:21:52 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "FOC_Strom_einfach.h"

/* Block parameters (default storage) */
P rtP = {
  /* Variable: K_R_id
   * Referenced by: '<S38>/Integral Gain'
   */
  2500.0,

  /* Variable: K_R_iq
   * Referenced by: '<S86>/Integral Gain'
   */
  2500.0,

  /* Variable: P_R_id
   * Referenced by: '<S39>/Proportional Gain'
   */
  0.043563418129778458,

  /* Variable: P_R_iq
   * Referenced by: '<S87>/Proportional Gain'
   */
  0.043563418129778458,

  /* Mask Parameter: PI_d_InitialConditionForIntegra
   * Referenced by: '<S41>/Integrator'
   */
  0.0,

  /* Mask Parameter: PI_q_InitialConditionForIntegra
   * Referenced by: '<S89>/Integrator'
   */
  0.0,

  /* Expression: 2
   * Referenced by: '<S4>/Gain2'
   */
  2.0,

  /* Expression: 1/3
   * Referenced by: '<S4>/Gain'
   */
  0.33333333333333331,

  /* Expression: 1/3*sqrt(3)
   * Referenced by: '<S4>/Gain1'
   */
  0.57735026918962573,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S41>/Integrator'
   */
  0.0001,

  /* Computed Parameter: Integrator_gainval_p
   * Referenced by: '<S89>/Integrator'
   */
  0.0001,

  /* Expression: 1/2
   * Referenced by: '<S106>/Gain'
   */
  0.5,

  /* Expression: 2
   * Referenced by: '<S106>/Gain2'
   */
  2.0,

  /* Expression: 1/2
   * Referenced by: '<S9>/Constant1'
   */
  0.5,

  /* Expression: 1/2*sqrt(3)
   * Referenced by: '<S106>/Gain1'
   */
  0.8660254037844386,

  /* Expression: 1/2
   * Referenced by: '<S9>/Constant2'
   */
  0.5,

  /* Expression: 1/2
   * Referenced by: '<S9>/Constant3'
   */
  0.5
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
