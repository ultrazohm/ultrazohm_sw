/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Regelung_data.c
 *
 * Code generated for Simulink model 'Regelung'.
 *
 * Model version                  : 2.26
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Sep 20 14:43:03 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "Regelung.h"

/* Block parameters (default storage) */
P rtP = {
  /* Variable: K1
   * Referenced by:
   *   '<S27>/Gain1'
   *   '<S27>/Gain2'
   *   '<S37>/Gain1'
   *   '<S37>/Gain2'
   *   '<S47>/Gain1'
   *   '<S47>/Gain2'
   */
  109.090904F,

  /* Variable: K2
   * Referenced by:
   *   '<S25>/Gain4'
   *   '<S35>/Gain4'
   *   '<S45>/Gain4'
   */
  10.90909F,

  /* Variable: K3
   * Referenced by:
   *   '<S26>/Gain4'
   *   '<S36>/Gain4'
   *   '<S46>/Gain4'
   */
  10.90909F,

  /* Variable: Kis_n
   * Referenced by: '<S10>/Gain1'
   */
  39.2699127F,

  /* Variable: Kp
   * Referenced by:
   *   '<S27>/Gain6'
   *   '<S37>/Gain6'
   *   '<S47>/Gain6'
   */
  2.76460195F,

  /* Variable: Kp_n
   * Referenced by: '<S10>/Gain'
   */
  0.170507073F,

  /* Variable: L
   * Referenced by:
   *   '<S6>/Function_Feldschwaeche'
   *   '<S6>/function_Eckdrehzahl'
   */
  0.0011F,

  /* Variable: Offset_V
   * Referenced by: '<S16>/Constant'
   */
  -2.09439516F,

  /* Variable: Offset_W
   * Referenced by: '<S17>/Constant'
   */
  -4.18879032F,

  /* Variable: Psi_PM
   * Referenced by:
   *   '<S6>/Function_Feldschwaeche'
   *   '<S6>/function_Eckdrehzahl'
   */
  0.01858F,

  /* Variable: R
   * Referenced by: '<S6>/function_Eckdrehzahl'
   */
  0.06F,

  /* Variable: T_R
   * Referenced by:
   *   '<S2>/Gain'
   *   '<S7>/Constant'
   *   '<S10>/Gain1'
   *   '<S11>/Gain'
   *   '<S25>/Gain1'
   *   '<S25>/Gain2'
   *   '<S26>/Gain1'
   *   '<S26>/Gain2'
   *   '<S27>/Gain1'
   *   '<S27>/Gain2'
   *   '<S35>/Gain1'
   *   '<S35>/Gain2'
   *   '<S36>/Gain1'
   *   '<S36>/Gain2'
   *   '<S37>/Gain1'
   *   '<S37>/Gain2'
   *   '<S45>/Gain1'
   *   '<S45>/Gain2'
   *   '<S46>/Gain1'
   *   '<S46>/Gain2'
   *   '<S47>/Gain1'
   *   '<S47>/Gain2'
   */
  5.0E-5F,

  /* Variable: T_VF_n
   * Referenced by: '<S11>/Gain'
   */
  0.012732394F,

  /* Variable: i_max_peak
   * Referenced by:
   *   '<S4>/Constant'
   *   '<S4>/Constant4'
   *   '<S4>/Constant6'
   */
  36.0F,

  /* Variable: i_max_rms
   * Referenced by:
   *   '<S4>/Constant1'
   *   '<S4>/Constant5'
   *   '<S4>/Constant7'
   */
  30.0F,

  /* Variable: i_ref_max
   * Referenced by:
   *   '<S6>/function_Eckdrehzahl'
   *   '<S6>/Constant'
   *   '<S8>/Constant'
   */
  25.0F,

  /* Variable: max_current_samplenumber
   * Referenced by:
   *   '<S52>/Gain'
   *   '<S54>/Gain'
   *   '<S55>/Gain'
   */
  20.0F,

  /* Variable: max_speed_samplenumber
   * Referenced by: '<S53>/Gain'
   */
  120.0F,

  /* Variable: n_max
   * Referenced by: '<S4>/Constant3'
   */
  600.0F,

  /* Variable: n_max_peak
   * Referenced by: '<S4>/Constant2'
   */
  1500.0F,

  /* Variable: n_ref_max
   * Referenced by: '<S6>/function_Eckdrehzahl'
   */
  500.0F,

  /* Variable: p
   * Referenced by: '<S6>/function_Eckdrehzahl'
   */
  18.0F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
