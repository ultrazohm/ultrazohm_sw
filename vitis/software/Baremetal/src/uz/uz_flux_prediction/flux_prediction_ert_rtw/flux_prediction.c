/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: flux_prediction.c
 *
 * Code generated for Simulink model 'flux_prediction'.
 *
 * Model version                  : 7.7
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Mar 23 12:17:55 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "flux_prediction.h"
#include <string.h>

/* Model step function */
void flux_prediction_step(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Outport: '<Root>/flux_d_pre' incorporates:
   *  Gain: '<S1>/Gain5'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product2'
   *  Product: '<S1>/Product5'
   *  Product: '<S1>/Product6'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S1>/Sum2'
   *  Sum: '<S1>/Sum4'
   *  Sum: '<S1>/Sum6'
   */
  rtY->flux_d_pre = (((rtU->i_d * rtU->r_1 - rtU->u_d_k0) + rtU->flux_q *
                      rtU->omega_ell) * rtU->ts_regler + rtU->flux_d) +
    rtU->u_d_k1 * rtU->ts_regler * 0.5F;

  /* Outport: '<Root>/flux_q_pre' incorporates:
   *  Gain: '<S1>/Gain6'
   *  Product: '<S1>/Product'
   *  Product: '<S1>/Product3'
   *  Product: '<S1>/Product4'
   *  Product: '<S1>/Product7'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum3'
   *  Sum: '<S1>/Sum5'
   *  Sum: '<S1>/Sum7'
   */
  rtY->flux_q_pre = (((rtU->u_q_k0 - rtU->i_q * rtU->r_1) - rtU->omega_ell *
                      rtU->flux_d) * rtU->ts_regler + rtU->flux_q) + rtU->u_q_k1
    * rtU->ts_regler * 0.5F;
}

/* Model initialize function */
void flux_prediction_initialize(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void)memset(rtY, 0, sizeof(ExtY));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
