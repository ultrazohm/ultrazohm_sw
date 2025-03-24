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
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Mar 13 14:57:33 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "uz_codegen0.h"
#include <math.h>
#include "rtwtypes.h"

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

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
  /* (no initialization code required) */
  UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
