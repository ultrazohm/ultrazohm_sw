/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_komplex_data.c
 *
 * Code generated for Simulink model 'FOC_komplex'.
 *
 * Model version                  : 2.22
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Aug 10 10:14:27 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "FOC_komplex.h"

/* Block parameters (default storage) */
P rtP = {
  /* Variable: T_VF_n
   * Referenced by: '<S14>/Gain'
   */
  0.001,

  /* Variable: Kis_id
   * Referenced by: '<S20>/Gain1'
   */
  2500.0F,

  /* Variable: Kis_iq
   * Referenced by: '<S21>/Gain1'
   */
  2500.0F,

  /* Variable: Kis_n
   * Referenced by: '<S13>/Gain1'
   */
  69.813179F,

  /* Variable: Kp_id
   * Referenced by: '<S20>/Gain'
   */
  0.160849556F,

  /* Variable: Kp_iq
   * Referenced by: '<S21>/Gain'
   */
  0.160849556F,

  /* Variable: Kp_n
   * Referenced by: '<S13>/Gain'
   */
  1.45055914F,

  /* Variable: L_d
   * Referenced by:
   *   '<S8>/Function_Feldschwaeche'
   *   '<S22>/Gain1'
   */
  1.6E-5F,

  /* Variable: L_q
   * Referenced by:
   *   '<S8>/function_Eckdrehzahl'
   *   '<S22>/Gain'
   */
  1.6E-5F,

  /* Variable: Psi_PM
   * Referenced by:
   *   '<S8>/Function_Feldschwaeche'
   *   '<S8>/function_Eckdrehzahl'
   *   '<S22>/Constant'
   */
  0.0048F,

  /* Variable: R
   * Referenced by: '<S8>/function_Eckdrehzahl'
   */
  0.04F,

  /* Variable: T_R
   * Referenced by:
   *   '<S3>/Gain'
   *   '<S11>/Winkelwahl'
   *   '<S13>/Gain1'
   *   '<S14>/Gain'
   *   '<S20>/Gain1'
   *   '<S21>/Gain1'
   */
  2.5E-5F,

  /* Variable: i_max
   * Referenced by: '<S5>/Constant1'
   */
  70.0F,

  /* Variable: i_max_peak
   * Referenced by: '<S5>/Constant'
   */
  74.0F,

  /* Variable: i_ref_max
   * Referenced by:
   *   '<S8>/function_Eckdrehzahl'
   *   '<S8>/Constant'
   *   '<S10>/Constant'
   */
  60.0F,

  /* Variable: n_max
   * Referenced by: '<S5>/Constant3'
   */
  2200.0F,

  /* Variable: n_max_peak
   * Referenced by: '<S5>/Constant2'
   */
  2400.0F,

  /* Variable: n_ref_max
   * Referenced by: '<S8>/function_Eckdrehzahl'
   */
  2000.0F,

  /* Variable: p
   * Referenced by: '<S8>/function_Eckdrehzahl'
   */
  21.0F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
