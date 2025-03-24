/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Resonant_Controller.c
 *
 * Code generated for Simulink model 'Resonant_Controller'.
 *
 * Model version                  : 4.8
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Mar 13 16:04:09 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#include "Resonant_Controller.h"
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
void Resonant_Controller_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real32_T rtb_Cos;
  real32_T rtb_Cos1;
  real32_T rtb_Product2;

  /* Product: '<S1>/Product' incorporates:
   *  Product: '<S1>/Product3'
   */
  rtb_Cos = rtU->omega_el * rtU->h * rtU->T_sw;

  /* Trigonometry: '<S1>/Cos1' incorporates:
   *  Gain: '<S1>/Gain'
   */
  rtb_Cos1 = cosf(2.0F * rtb_Cos);

  /* Delay: '<S1>/Delay' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Delay: '<S1>/Delay2'
   *  Delay: '<S1>/Delay3'
   */
  if (rtU->Reset != 0.0F) {
    rtDW->Delay_DSTATE = 0.0F;
    rtDW->Delay3_DSTATE = 0.0F;
    rtDW->Delay1_DSTATE = 0.0F;
    rtDW->Delay2_DSTATE = 0.0F;
  }

  /* Product: '<S1>/Product2' incorporates:
   *  Delay: '<S1>/Delay'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product4'
   *  Sum: '<S1>/Subtract'
   *  Sum: '<S1>/Sum'
   */
  rtb_Product2 = ((rtU->in_ref - rtU->in_m) - rtU->Klim * rtDW->Delay_DSTATE) *
    rtU->VR * rtU->T_sw;

  /* Trigonometry: '<S1>/Cos' */
  rtb_Cos = cosf(rtb_Cos);

  /* Sum: '<S1>/Sum2' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Delay: '<S1>/Delay2'
   *  Delay: '<S1>/Delay3'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Product: '<S1>/-a1'
   *  Product: '<S1>/b0'
   *  Product: '<S1>/b1'
   *  Sum: '<S1>/Sum3'
   */
  rtb_Cos = ((-rtb_Cos * rtDW->Delay3_DSTATE - rtDW->Delay1_DSTATE) + 2.0F *
             rtb_Cos * rtDW->Delay2_DSTATE) + rtb_Cos1 * rtb_Product2;

  /* MATLAB Function: '<S1>/saturation' */
  rtb_Cos1 = rtb_Cos;
  if (rtb_Cos > rtU->upper_limit) {
    rtb_Cos1 = rtU->upper_limit;
  }

  if (rtb_Cos < rtU->lower_limit) {
    rtb_Cos1 = rtU->lower_limit;
  }

  /* End of MATLAB Function: '<S1>/saturation' */

  /* Outport: '<Root>/out' */
  rtY->out = rtb_Cos1;

  /* Update for Delay: '<S1>/Delay' incorporates:
   *  Sum: '<S1>/Sum1'
   */
  rtDW->Delay_DSTATE = rtb_Cos - rtb_Cos1;

  /* Update for Delay: '<S1>/Delay3' */
  rtDW->Delay3_DSTATE = rtb_Product2;

  /* Update for Delay: '<S1>/Delay1' incorporates:
   *  Delay: '<S1>/Delay2'
   */
  rtDW->Delay1_DSTATE = rtDW->Delay2_DSTATE;

  /* Update for Delay: '<S1>/Delay2' */
  rtDW->Delay2_DSTATE = rtb_Cos;
}

/* Model initialize function */
void Resonant_Controller_initialize(RT_MODEL *const rtM)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
