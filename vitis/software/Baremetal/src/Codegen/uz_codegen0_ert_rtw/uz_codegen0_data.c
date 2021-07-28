/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0_data.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.98
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jul 28 15:29:21 2021
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
    0U,                                /* '<S128>/Compare' */
    0U                                 /* '<S134>/Compare' */
  }
  /* End of '<S1>/CurrentController' */
};

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S125>/Gain3'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F, 1.0F, 1.0F, 1.0F },

  /* Computed Parameter: Gain3_Gain_i
   * Referenced by: '<S116>/Gain3'
   */
  { 1.0F, 0.0F, 0.5F, -0.5F, 0.866025388F, 0.5F, -0.5F, -0.866025388F, 0.5F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
