/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_fastCTRL_data.c
 *
 * Code generated for Simulink model 'FOC_fastCTRL'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Aug 28 08:46:54 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_fastCTRL.h"

/* Constant parameters (default storage) */
const ConstP_FOC_fastCTRL_T FOC_fastCTRL_ConstP = {
  /* Pooled Parameter (Expression: [1,0;-0.5,sqrt(3)/2;-0.5,-sqrt(3)/2])
   * Referenced by:
   *   '<S54>/Constant'
   *   '<S55>/Constant'
   */
  { 1.0, -0.5, -0.5, 0.0, 0.8660254037844386, -0.8660254037844386 },

  /* Pooled Parameter (Expression: [1 -0.5 -0.5;0 sqrt(3)/2 -sqrt(3)/2]*2/3)
   * Referenced by:
   *   '<S38>/TrafoMatrix uvw->alphabeta'
   *   '<S39>/TrafoMatrix uvw->alphabeta'
   */
  { 0.66666666666666663, 0.0, -0.33333333333333331, 0.57735026918962573,
    -0.33333333333333331, -0.57735026918962573 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
