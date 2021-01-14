/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 1.26
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Thu Jan 14 15:55:30 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "uz_codegen0.h"

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real_T rtb_Product1;
  int32_T i;
  real32_T rtb_Sum;
  real32_T rtb_Sum3;

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/Sum1'
   *  Inport: '<Root>/Sum2'
   *  Inport: '<Root>/Sum4'
   */
  rtb_Sum = (rtU->Sum1 + rtU->Sum2) + rtU->Sum4;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/reset_integrator'
   */
  if ((rtU->reset_integrator != 0.0F) || (rtDW->DiscreteTimeIntegrator_PrevRese
       != 0)) {
    rtDW->DiscreteTimeIntegrator_DSTATE = 0.0F;
  }

  if (rtDW->DiscreteTimeIntegrator_DSTATE >= 1000.0F) {
    rtDW->DiscreteTimeIntegrator_DSTATE = 1000.0F;
  } else {
    if (rtDW->DiscreteTimeIntegrator_DSTATE <= -1000.0F) {
      rtDW->DiscreteTimeIntegrator_DSTATE = -1000.0F;
    }
  }

  /* Sum: '<S1>/Sum3' incorporates:
   *  Constant: '<S1>/Constant'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Trigonometry: '<S1>/Trigonometric Function'
   */
  rtb_Sum3 = sinf(6.28318548F * rtDW->DiscreteTimeIntegrator1_DSTATE) * 0.5F +
    0.5F;
  for (i = 0; i < 100; i++) {
    /* Product: '<S1>/Product1' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    rtb_Product1 = rtConstP.Constant1_Value[i] * rtb_Sum3;

    /* Outport: '<Root>/matrixOut' incorporates:
     *  Product: '<S1>/Product'
     */
    rtY->matrixOut[i] = rtb_Product1 * rtb_Product1;
  }

  /* Outport: '<Root>/sineOut' */
  rtY->sineOut = rtb_Sum3;

  /* Outport: '<Root>/integrator' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  rtY->integrator = rtDW->DiscreteTimeIntegrator_DSTATE;

  /* Outport: '<Root>/SumOut' incorporates:
   *  Gain: '<S1>/Gain'
   */
  rtY->SumOut = 5.0F * rtb_Sum;

  /* Outport: '<Root>/SumOut1' incorporates:
   *  Inport: '<Root>/Sum1'
   */
  rtY->SumOut1 = rtU->Sum1;

  /* Outport: '<Root>/timeFeedback' incorporates:
   *  Inport: '<Root>/time'
   */
  rtY->timeFeedback = rtU->time;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/reset_integrator'
   */
  rtDW->DiscreteTimeIntegrator_DSTATE += 0.0001F * rtb_Sum;
  if (rtDW->DiscreteTimeIntegrator_DSTATE >= 1000.0F) {
    rtDW->DiscreteTimeIntegrator_DSTATE = 1000.0F;
  } else {
    if (rtDW->DiscreteTimeIntegrator_DSTATE <= -1000.0F) {
      rtDW->DiscreteTimeIntegrator_DSTATE = -1000.0F;
    }
  }

  if (rtU->reset_integrator > 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = 1;
  } else if (rtU->reset_integrator < 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = -1;
  } else if (rtU->reset_integrator == 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = 0;
  } else {
    rtDW->DiscreteTimeIntegrator_PrevRese = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/time'
   */
  rtDW->DiscreteTimeIntegrator1_DSTATE += 0.0001F * rtU->time;
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_PrevRese = 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
