/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 1.19
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Fri Nov 27 18:10:59 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warning (1), Errors (2)
 */

#include "uz_codegen0.h"

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM, ExtU *rtU, ExtY *rtY)
{
  DW *rtDW = rtM->dwork;
  real32_T rtb_Sum;

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/Sum1'
   *  Inport: '<Root>/Sum2'
   *  Inport: '<Root>/Sum4'
   */
  rtb_Sum = (rtU->Sum1 + rtU->Sum2) + rtU->Sum4;

  /* Outport: '<Root>/SumOut' incorporates:
   *  Gain: '<S1>/Gain'
   */
  rtY->SumOut = 5.0F * rtb_Sum;

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

  /* Outport: '<Root>/integrator' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  rtY->integrator = rtDW->DiscreteTimeIntegrator_DSTATE;

  /* Outport: '<Root>/sineOut' incorporates:
   *  Constant: '<S1>/Constant'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Sum: '<S1>/Sum3'
   *  Trigonometry: '<S1>/Trigonometric Function'
   */
  rtY->sineOut = sinf(6.28318548F * rtDW->DiscreteTimeIntegrator1_DSTATE) * 0.5F
    + 0.5F;

  /* Outport: '<Root>/SumOut1' incorporates:
   *  Inport: '<Root>/Sum1'
   */
  rtY->SumOut1 = rtU->Sum1;

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
  if (rtDW->DiscreteTimeIntegrator1_DSTATE >= 500.0F) {
    rtDW->DiscreteTimeIntegrator1_DSTATE = 500.0F;
  } else {
    if (rtDW->DiscreteTimeIntegrator1_DSTATE <= -100.0F) {
      rtDW->DiscreteTimeIntegrator1_DSTATE = -100.0F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM, ExtU *rtU, ExtY *rtY)
{
  DW *rtDW = rtM->dwork;

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
