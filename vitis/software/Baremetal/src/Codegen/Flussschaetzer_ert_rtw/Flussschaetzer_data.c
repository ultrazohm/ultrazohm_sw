/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Flussschaetzer_data.c
 *
 * Code generated for Simulink model 'Flussschaetzer'.
 *
 * Model version                  : 9.9
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon Apr 14 16:27:27 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Flussschaetzer.h"

/* Block parameters (default storage) */
P_Flussschaetzer rtP = {
  /* Variable: Ls
   * Referenced by:
   *   '<S4>/Gain2'
   *   '<S4>/Gain3'
   */
  0.00024F,

  /* Variable: Rs
   * Referenced by:
   *   '<S4>/Gain'
   *   '<S4>/Gain1'
   */
  0.2715F,

  /* Variable: THP
   * Referenced by: '<S3>/Constant'
   */
  0.0318309888F,

  /* Variable: Ts
   * Referenced by: '<S2>/Constant3'
   */
  5.0E-5F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
