/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_komplex_data.c
 *
 * Code generated for Simulink model 'FOC_komplex'.
 *
 * Model version                  : 2.23
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Aug 17 14:08:55 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "FOC_komplex.h"

/* Block parameters (default storage) */
P rtP = {
  /* Variable: Kis_id
   * Referenced by: '<S20>/Gain1'
   */
  53.3333321F,

  /* Variable: Kis_iq
   * Referenced by: '<S21>/Gain1'
   */
  53.3333321F,

  /* Variable: Kis_n
   * Referenced by: '<S13>/Gain1'
   */
  680.678406F,

  /* Variable: Kp_id
   * Referenced by: '<S20>/Gain'
   */
  16.3362827F,

  /* Variable: Kp_iq
   * Referenced by: '<S21>/Gain'
   */
  16.3362827F,

  /* Variable: Kp_n
   * Referenced by: '<S13>/Gain'
   */
  1.19612432F,

  /* Variable: L_d
   * Referenced by:
   *   '<S8>/Function_Feldschwaeche'
   *   '<S22>/Gain1'
   */
  0.0015F,

  /* Variable: L_q
   * Referenced by:
   *   '<S8>/function_Eckdrehzahl'
   *   '<S22>/Gain'
   */
  0.0015F,

  /* Variable: Psi_PM
   * Referenced by:
   *   '<S8>/Function_Feldschwaeche'
   *   '<S8>/function_Eckdrehzahl'
   *   '<S22>/Constant'
   */
  0.01854F,

  /* Variable: R
   * Referenced by: '<S8>/function_Eckdrehzahl'
   */
  0.08F,

  /* Variable: T_R
   * Referenced by:
   *   '<S3>/Gain'
   *   '<S11>/Winkelwahl'
   *   '<S13>/Gain1'
   *   '<S14>/Gain'
   *   '<S20>/Gain1'
   *   '<S21>/Gain1'
   *   '<S25>/Gain'
   *   '<S26>/Gain'
   */
  2.5E-5F,

  /* Variable: T_VF_n
   * Referenced by: '<S14>/Gain'
   */
  0.00367280631F,

  /* Variable: i_max
   * Referenced by: '<S5>/Constant1'
   */
  28.5105438F,

  /* Variable: i_max_peak
   * Referenced by: '<S5>/Constant'
   */
  47.5175743F,

  /* Variable: i_ref_max
   * Referenced by:
   *   '<S8>/function_Eckdrehzahl'
   *   '<S8>/Constant'
   *   '<S10>/Constant'
   */
  23.7587872F,

  /* Variable: n_max
   * Referenced by: '<S5>/Constant3'
   */
  750.0F,

  /* Variable: n_max_peak
   * Referenced by: '<S5>/Constant2'
   */
  900.0F,

  /* Variable: n_ref_max
   * Referenced by: '<S8>/function_Eckdrehzahl'
   */
  600.0F,

  /* Variable: p
   * Referenced by: '<S8>/function_Eckdrehzahl'
   */
  18.0F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
