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
 * C/C++ source code generated on : Wed Jul 21 16:23:06 2021
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
  6.2831860F,

  /* Variable: Kp_id
   * Referenced by: '<S20>/Gain'
   */
  0.0402124F,

  /* Variable: Kp_iq
   * Referenced by: '<S21>/Gain'
   */
  0.0402124F,

  /* Variable: Kp_n
   * Referenced by: '<S13>/Gain'
   */
  0.2175839F,

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
  5.0E-5F,

  /* Variable: T_VF_n
   * Referenced by: '<S14>/Gain'
   */
  0.3978873F,

  /* Variable: i_max
   * Referenced by: '<S5>/Constant1'
   */
  //252.0F,
  50.0F,

  /* Variable: i_max_peak
   * Referenced by: '<S5>/Constant'
   */
  //420.0F,
  75.0F,

  /* Variable: i_ref_max
   * Referenced by:
   *   '<S8>/function_Eckdrehzahl'
   *   '<S8>/Constant'
   *   '<S10>/Constant'
   */
  //210.0F,
  20.0F,

  /* Variable: n_max
   * Referenced by: '<S5>/Constant3'
   */
  //5625.0F,
  400.0F,

  /* Variable: n_max_peak
   * Referenced by: '<S5>/Constant2'
   */
  //6750.0F,
  500.0F,

  /* Variable: n_ref_max
   * Referenced by: '<S8>/function_Eckdrehzahl'
   */
  //4500.0F,
  300.0F,

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
