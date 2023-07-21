/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Oct 13 09:55:19 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */
#ifdef TEST

#include "uz_codegen0.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T rtb_Sum;

  /* Sum: '<S1>/Sum' */
  rtb_Sum = (rtU->summand1 + rtU->summand2) + rtU->summand3;

  /* Outport: '<Root>/sum' */
  rtY->sum = rtb_Sum;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  if ((rtU->reset_SumIntegrator != 0.0F) ||
      (rtDW->DiscreteTimeIntegrator_PrevRese != 0)) {
    rtDW->DiscreteTimeIntegrator_DSTATE = 0.0F;
  }

  /* Outport: '<Root>/IntegrationOfSum' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  rtY->IntegrationOfSum = rtDW->DiscreteTimeIntegrator_DSTATE;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator2' */
  if ((rtU->reset_TimeIntegrator != 0.0F) ||
      (rtDW->DiscreteTimeIntegrator2_PrevRes != 0)) {
    rtDW->DiscreteTimeIntegrator2_DSTATE = 0.0F;
  }

  /* Outport: '<Root>/ChirpSine' incorporates:
   *  Constant: '<S1>/Constant'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator2'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Sum: '<S1>/Sum3'
   *  Trigonometry: '<S1>/Trigonometric Function'
   */
  rtY->ChirpSine = sinf(6.28318548F * rtDW->DiscreteTimeIntegrator2_DSTATE) *
    0.5F + 0.5F;

  /* Outport: '<Root>/fb_summand1' */
  rtY->fb_summand1 = rtU->summand1;

  /* Outport: '<Root>/fb_time' */
  rtY->fb_time = rtU->time;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE += 0.0001F * rtb_Sum;
  if (rtU->reset_SumIntegrator > 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = 1;
  } else if (rtU->reset_SumIntegrator < 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = -1;
  } else if (rtU->reset_SumIntegrator == 0.0F) {
    rtDW->DiscreteTimeIntegrator_PrevRese = 0;
  } else {
    rtDW->DiscreteTimeIntegrator_PrevRese = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator2' */
  rtDW->DiscreteTimeIntegrator2_DSTATE += 0.0001F * rtU->time;
  if (rtU->reset_TimeIntegrator > 0.0F) {
    rtDW->DiscreteTimeIntegrator2_PrevRes = 1;
  } else if (rtU->reset_TimeIntegrator < 0.0F) {
    rtDW->DiscreteTimeIntegrator2_PrevRes = -1;
  } else if (rtU->reset_TimeIntegrator == 0.0F) {
    rtDW->DiscreteTimeIntegrator2_PrevRes = 0;
  } else {
    rtDW->DiscreteTimeIntegrator2_PrevRes = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator2' */
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
  (void)memset(rtY, 0, sizeof(ExtY));

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_PrevRese = 0;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator2' */
  rtDW->DiscreteTimeIntegrator2_PrevRes = 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
#endif
