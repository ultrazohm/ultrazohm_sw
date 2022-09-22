/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Resonant_Controller.c
 *
 * Code generated for Simulink model 'Resonant_Controller'.
 *
 * Model version                  : 4.1
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Wed Sep 14 13:32:43 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "Resonant_Controller.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void Resonant_Controller_step(RT_MODEL_Resonant_Controller_T *const
  Resonant_Controller_M)
{
  DW_Resonant_Controller_T *Resonant_Controller_DW =
    Resonant_Controller_M->dwork;
  ExtU_Resonant_Controller_T *Resonant_Controller_U =
    (ExtU_Resonant_Controller_T *) Resonant_Controller_M->inputs;
  ExtY_Resonant_Controller_T *Resonant_Controller_Y =
    (ExtY_Resonant_Controller_T *) Resonant_Controller_M->outputs;
  real_T rtb_Cos;
  real_T rtb_Cos1;
  real_T rtb_Product2;

  /* Product: '<S1>/Product' incorporates:
   *  Inport: '<Root>/T_sw'
   *  Inport: '<Root>/h'
   *  Inport: '<Root>/omega_el'
   *  Product: '<S1>/Product3'
   */
  rtb_Cos = Resonant_Controller_U->omega_el * Resonant_Controller_U->h *
    Resonant_Controller_U->T_sw;

  /* Trigonometry: '<S1>/Cos1' incorporates:
   *  Gain: '<S1>/Gain'
   */
  rtb_Cos1 = cos(2.0 * rtb_Cos);

  /* Delay: '<S1>/Delay' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Delay: '<S1>/Delay2'
   *  Delay: '<S1>/Delay3'
   *  Inport: '<Root>/Reset'
   */
  if (Resonant_Controller_U->Reset != 0.0) {
    Resonant_Controller_DW->Delay_DSTATE = 0.0;
    Resonant_Controller_DW->Delay3_DSTATE = 0.0;
    Resonant_Controller_DW->Delay1_DSTATE = 0.0;
    Resonant_Controller_DW->Delay2_DSTATE = 0.0;
  }

  /* Product: '<S1>/Product2' incorporates:
   *  Delay: '<S1>/Delay'
   *  Inport: '<Root>/Klim'
   *  Inport: '<Root>/T_sw'
   *  Inport: '<Root>/VR'
   *  Inport: '<Root>/in_m'
   *  Inport: '<Root>/in_ref'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product4'
   *  Sum: '<S1>/Subtract'
   *  Sum: '<S1>/Sum'
   */
  rtb_Product2 = ((Resonant_Controller_U->in_ref - Resonant_Controller_U->in_m)
                  - Resonant_Controller_U->Klim *
                  Resonant_Controller_DW->Delay_DSTATE) *
    Resonant_Controller_U->VR * Resonant_Controller_U->T_sw;

  /* Trigonometry: '<S1>/Cos' */
  rtb_Cos = cos(rtb_Cos);

  /* Sum: '<S1>/Sum2' incorporates:
   *  Delay: '<S1>/Delay1'
   *  Delay: '<S1>/Delay2'
   *  Delay: '<S1>/Delay3'
   *  Gain: '<S1>/-a2'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Product: '<S1>/-a1'
   *  Product: '<S1>/b0'
   *  Product: '<S1>/b1'
   *  Sum: '<S1>/Sum3'
   */
  rtb_Cos = ((-rtb_Cos * Resonant_Controller_DW->Delay3_DSTATE +
              -Resonant_Controller_DW->Delay1_DSTATE) + 2.0 * rtb_Cos *
             Resonant_Controller_DW->Delay2_DSTATE) + rtb_Cos1 * rtb_Product2;

  /* MATLAB Function: '<S1>/saturation' incorporates:
   *  Inport: '<Root>/lower_limit'
   *  Inport: '<Root>/upper_limit'
   */
  /* MATLAB Function 'Resonant_Controller/saturation': '<S2>:1' */
  /* '<S2>:1:3' output = input; */
  rtb_Cos1 = rtb_Cos;

  /* '<S2>:1:5' if (input > upper_limit) */
  if (rtb_Cos > Resonant_Controller_U->upper_limit) {
    /* '<S2>:1:6' output = upper_limit; */
    rtb_Cos1 = Resonant_Controller_U->upper_limit;
  }

  /* '<S2>:1:9' if (input < lower_limit) */
  if (rtb_Cos < Resonant_Controller_U->lower_limit) {
    /* '<S2>:1:10' output = lower_limit; */
    rtb_Cos1 = Resonant_Controller_U->lower_limit;
  }

  /* End of MATLAB Function: '<S1>/saturation' */

  /* Outport: '<Root>/out' */
  Resonant_Controller_Y->out = rtb_Cos1;

  /* Update for Delay: '<S1>/Delay' incorporates:
   *  Sum: '<S1>/Sum1'
   */
  Resonant_Controller_DW->Delay_DSTATE = rtb_Cos - rtb_Cos1;

  /* Update for Delay: '<S1>/Delay3' */
  Resonant_Controller_DW->Delay3_DSTATE = rtb_Product2;

  /* Update for Delay: '<S1>/Delay1' incorporates:
   *  Delay: '<S1>/Delay2'
   */
  Resonant_Controller_DW->Delay1_DSTATE = Resonant_Controller_DW->Delay2_DSTATE;

  /* Update for Delay: '<S1>/Delay2' */
  Resonant_Controller_DW->Delay2_DSTATE = rtb_Cos;
}

/* Model initialize function */
void Resonant_Controller_initialize(RT_MODEL_Resonant_Controller_T *const
  Resonant_Controller_M)
{
  DW_Resonant_Controller_T *Resonant_Controller_DW =
    Resonant_Controller_M->dwork;
  ExtU_Resonant_Controller_T *Resonant_Controller_U =
    (ExtU_Resonant_Controller_T *) Resonant_Controller_M->inputs;
  ExtY_Resonant_Controller_T *Resonant_Controller_Y =
    (ExtY_Resonant_Controller_T *) Resonant_Controller_M->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)Resonant_Controller_DW, 0,
                sizeof(DW_Resonant_Controller_T));

  /* external inputs */
  (void)memset(Resonant_Controller_U, 0, sizeof(ExtU_Resonant_Controller_T));

  /* external outputs */
  Resonant_Controller_Y->out = 0.0;

  /* InitializeConditions for Delay: '<S1>/Delay' */
  Resonant_Controller_DW->Delay_DSTATE = 0.0;

  /* InitializeConditions for Delay: '<S1>/Delay3' */
  Resonant_Controller_DW->Delay3_DSTATE = 0.0;

  /* InitializeConditions for Delay: '<S1>/Delay1' */
  Resonant_Controller_DW->Delay1_DSTATE = 0.0;

  /* InitializeConditions for Delay: '<S1>/Delay2' */
  Resonant_Controller_DW->Delay2_DSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
