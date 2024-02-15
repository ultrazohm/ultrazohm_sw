/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CurrentControl_Kp_iq_adjustment.c
 *
 * Code generated for Simulink model 'CurrentControl_Kp_iq_adjustment'.
 *
 * Model version                  : 7.8
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Thu Feb 15 15:30:56 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "CurrentControl_Kp_iq_adjustment.h"
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void CurrentControl_Kp_iq_adjustment_step(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T rtb_Switch2;

  /* Sum: '<S1>/Sum2' */
  rtb_Switch2 = rtU->iq_ref - rtU->iq_mea;

  /* Switch: '<S1>/Switch2' incorporates:
   *  Constant: '<S1>/Constant4'
   */
  if (rtb_Switch2 == 0.0F) {
    rtb_Switch2 = 1.1920929E-7F;
  }

  /* Outport: '<Root>/Kp_iq' incorporates:
   *  Gain: '<S1>/Gain'
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Product'
   *  Sum: '<S1>/Sum4'
   *  Switch: '<S1>/Switch2'
   */
  rtY->Kp_iq = (rtU->psiq_ref - rtU->psiq_mea) / rtb_Switch2 * (0.5F *
    rtU->dead_time_reciprodical);
}

/* Model initialize function */
void CurrentControl_Kp_iq_adjustment_initialize(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  rtY->Kp_iq = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
