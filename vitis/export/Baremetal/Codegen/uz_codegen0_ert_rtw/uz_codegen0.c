/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 1.28
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Thu Jan 14 18:26:20 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "uz_codegen0.h"

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
  /* (no initialization code required) */
  UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
