/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: approximate_flux_q.c
 *
 * Code generated for Simulink model 'approximate_flux_q'.
 *
 * Model version                  : 7.3
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Feb  9 17:15:36 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "approximate_flux_q.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void approximate_flux_q_step(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T rtb_psiq_self;

  /* Sum: '<S1>/Sum4' incorporates:
   *  Product: '<S1>/Product'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product5'
   *  Trigonometry: '<S1>/Tanh'
   */
  rtb_psiq_self = tanhf(rtU->iq * rtU->fitting_parameters[7]) *
    rtU->fitting_parameters[6] + rtU->iq * rtU->fitting_parameters[8];

  /* Outport: '<Root>/psiq_approx' incorporates:
   *  Math: '<S1>/Log1'
   *  Math: '<S1>/Log2'
   *  Product: '<S1>/Product10'
   *  Product: '<S1>/Product2'
   *  Product: '<S1>/Product20'
   *  Product: '<S1>/Product3'
   *  Product: '<S1>/Product4'
   *  Product: '<S1>/Product6'
   *  Product: '<S1>/Product7'
   *  Product: '<S1>/Product9'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum10'
   *  Sum: '<S1>/Sum2'
   *  Sum: '<S1>/Sum3'
   *  Sum: '<S1>/Sum5'
   *  Sum: '<S1>/Sum6'
   *  Trigonometry: '<S1>/Tanh1'
   *  Trigonometry: '<S1>/Tanh2'
   *  Trigonometry: '<S1>/Tanh4'
   *
   * About '<S1>/Log1':
   *  Operator: log
   *
   * About '<S1>/Log2':
   *  Operator: log
   */
  rtY->psiq_approx = rtb_psiq_self - (rtb_psiq_self - (tanhf(rtU->iq *
    rtU->fitting_parameters[10]) * rtU->fitting_parameters[9] + rtU->iq *
    rtU->fitting_parameters[11])) * (logf(coshf((rtU->id -
    rtU->fitting_parameters[2]) * rtU->fitting_parameters[1])) *
    rtU->fitting_parameters[21] - logf(coshf((rtU->id - rtU->fitting_parameters
    [5]) * rtU->fitting_parameters[4])) * rtU->fitting_parameters[20]) *
    rtU->fitting_parameters[13];
}

/* Model initialize function */
void approximate_flux_q_initialize(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  rtY->psiq_approx = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
