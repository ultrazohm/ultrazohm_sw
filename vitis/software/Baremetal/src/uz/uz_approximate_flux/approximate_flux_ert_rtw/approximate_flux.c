/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: approximate_flux.c
 *
 * Code generated for Simulink model 'approximate_flux'.
 *
 * Model version                  : 7.3
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Feb 21 16:05:24 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "approximate_flux.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void approximate_flux_step(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T psid_approx_tmp;
  real32_T psid_approx_tmp_0;
  real32_T psid_approx_tmp_1;
  real32_T rtb_psidself;
  real32_T rtb_psidself_tmp;

  /* Product: '<S2>/Product' incorporates:
   *  Product: '<S3>/Product7'
   *  Sum: '<S2>/Sum'
   */
  rtb_psidself_tmp = (rtU->id - rtU->fitting_parameters[2]) *
    rtU->fitting_parameters[1];

  /* Product: '<S2>/Product1' incorporates:
   *  Product: '<S2>/Product'
   *  Trigonometry: '<S2>/Tanh'
   */
  rtb_psidself = tanhf(rtb_psidself_tmp) * rtU->fitting_parameters[0];

  /* Product: '<S2>/Product4' incorporates:
   *  Product: '<S3>/Product'
   */
  psid_approx_tmp = rtU->iq * rtU->fitting_parameters[7];

  /* Product: '<S2>/Product5' incorporates:
   *  Product: '<S3>/Product2'
   */
  psid_approx_tmp_0 = rtU->iq * rtU->fitting_parameters[10];

  /* Product: '<S2>/Product2' incorporates:
   *  Product: '<S3>/Product10'
   *  Sum: '<S2>/Sum1'
   */
  psid_approx_tmp_1 = (rtU->id - rtU->fitting_parameters[5]) *
    rtU->fitting_parameters[4];

  /* Outport: '<Root>/psid_approx' incorporates:
   *  Math: '<S2>/Log'
   *  Math: '<S2>/Log1'
   *  Product: '<S2>/Product10'
   *  Product: '<S2>/Product12'
   *  Product: '<S2>/Product2'
   *  Product: '<S2>/Product3'
   *  Product: '<S2>/Product4'
   *  Product: '<S2>/Product5'
   *  Product: '<S2>/Product6'
   *  Product: '<S2>/Product7'
   *  Product: '<S2>/Product8'
   *  Sum: '<S2>/Sum2'
   *  Sum: '<S2>/Sum3'
   *  Sum: '<S2>/Sum7'
   *  Trigonometry: '<S2>/Tanh1'
   *  Trigonometry: '<S2>/Tanh2'
   *  Trigonometry: '<S2>/Tanh3'
   *
   * About '<S2>/Log':
   *  Operator: log
   *
   * About '<S2>/Log1':
   *  Operator: log
   */
  rtY->psid_approx = rtb_psidself - ((rtU->iq * rtU->iq *
    rtU->fitting_parameters[22] + logf(coshf(psid_approx_tmp)) *
    rtU->fitting_parameters[19]) - logf(coshf(psid_approx_tmp_0)) *
    rtU->fitting_parameters[18]) * (rtb_psidself - tanhf(psid_approx_tmp_1) *
    rtU->fitting_parameters[3]) * rtU->fitting_parameters[12];

  /* Sum: '<S3>/Sum4' incorporates:
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product5'
   *  Trigonometry: '<S3>/Tanh'
   */
  rtb_psidself = tanhf(psid_approx_tmp) * rtU->fitting_parameters[6] + rtU->iq *
    rtU->fitting_parameters[8];

  /* Outport: '<Root>/psiq_approx' incorporates:
   *  Math: '<S3>/Log1'
   *  Math: '<S3>/Log2'
   *  Product: '<S3>/Product20'
   *  Product: '<S3>/Product3'
   *  Product: '<S3>/Product4'
   *  Product: '<S3>/Product6'
   *  Product: '<S3>/Product9'
   *  Sum: '<S3>/Sum1'
   *  Sum: '<S3>/Sum10'
   *  Sum: '<S3>/Sum2'
   *  Sum: '<S3>/Sum5'
   *  Trigonometry: '<S3>/Tanh1'
   *  Trigonometry: '<S3>/Tanh2'
   *  Trigonometry: '<S3>/Tanh4'
   *
   * About '<S3>/Log1':
   *  Operator: log
   *
   * About '<S3>/Log2':
   *  Operator: log
   */
  rtY->psiq_approx = rtb_psidself - (rtb_psidself - (tanhf(psid_approx_tmp_0) *
    rtU->fitting_parameters[9] + rtU->iq * rtU->fitting_parameters[11])) * (logf
    (coshf(rtb_psidself_tmp)) * rtU->fitting_parameters[21] - logf(coshf
    (psid_approx_tmp_1)) * rtU->fitting_parameters[20]) *
    rtU->fitting_parameters[13];
}

/* Model initialize function */
void approximate_flux_initialize(RT_MODEL *const rtM)
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
