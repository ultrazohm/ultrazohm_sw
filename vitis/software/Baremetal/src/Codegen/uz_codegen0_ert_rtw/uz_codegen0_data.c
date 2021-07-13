/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0_data.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.29
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jul 13 14:13:32 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "uz_codegen0.h"

/* Invariant block signals (default storage) */
const ConstB rtConstB = {
  /* Start of '<S1>/CurrentController' */
  {
    0U,                                /* '<S26>/Compare' */
    0U                                 /* '<S32>/Compare' */
  }
  /* End of '<S1>/CurrentController' */
};

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Expression: [ 1   0   1; -1/2  sqrt(3)/2   1; -1/2  -sqrt(3)/2  1 ]
   * Referenced by: '<S23>/Gain3'
   */
  { 1.0, -0.5, -0.5, 0.0, 0.8660254037844386, -0.8660254037844386, 1.0, 1.0, 1.0
  },

  /* Expression: [ 1   -1/2   -1/2; 0   sqrt(3)/2   -sqrt(3)/2; 1/2  1/2  1/2 ]
   * Referenced by: '<S15>/Gain3'
   */
  { 1.0, 0.0, 0.5, -0.5, 0.8660254037844386, 0.5, -0.5, -0.8660254037844386, 0.5
  }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
