/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: approximate_flux_d.c
 *
 * Code generated for Simulink model 'approximate_flux_d'.
 *
 * Model version                  : 7.0
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Thu Feb  8 11:40:23 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "approximate_flux_d.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void approximate_flux_d_step(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T rtb_psidself;

  /* Product: '<S1>/Product1' incorporates:
   *  Product: '<S1>/Product'
   *  Sum: '<S1>/Sum'
   *  Trigonometry: '<S1>/Tanh'
   */
  rtb_psidself = tanhf((rtU->id - rtU->fitting_parameters[2]) *
                       rtU->fitting_parameters[1]) * rtU->fitting_parameters[0];

  /* Outport: '<Root>/psid_approx' incorporates:
   *  Math: '<S1>/Log'
   *  Math: '<S1>/Log1'
   *  Product: '<S1>/Product10'
   *  Product: '<S1>/Product12'
   *  Product: '<S1>/Product2'
   *  Product: '<S1>/Product3'
   *  Product: '<S1>/Product4'
   *  Product: '<S1>/Product5'
   *  Product: '<S1>/Product6'
   *  Product: '<S1>/Product7'
   *  Product: '<S1>/Product8'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum2'
   *  Sum: '<S1>/Sum3'
   *  Sum: '<S1>/Sum7'
   *  Trigonometry: '<S1>/Tanh1'
   *  Trigonometry: '<S1>/Tanh2'
   *  Trigonometry: '<S1>/Tanh3'
   *
   * About '<S1>/Log':
   *  Operator: log
   *
   * About '<S1>/Log1':
   *  Operator: log
   */
  rtY->psid_approx = rtb_psidself - (rtb_psidself - tanhf((rtU->id -
    rtU->fitting_parameters[5]) * rtU->fitting_parameters[4]) *
    rtU->fitting_parameters[3]) * ((logf(coshf(rtU->iq * rtU->
    fitting_parameters[7])) * rtU->fitting_parameters[19] + rtU->iq * rtU->iq *
    rtU->fitting_parameters[22]) - logf(coshf(rtU->iq * rtU->fitting_parameters
    [10])) * rtU->fitting_parameters[18]) * rtU->fitting_parameters[12];
}

/* Model initialize function */
void approximate_flux_d_initialize(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  rtY->psid_approx = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
