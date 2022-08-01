/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Resonanz_Regler_1.c
 *
 * Code generated for Simulink model 'Resonanz_Regler_1'.
 *
 * Model version                  : 3.0
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Jul 27 10:02:54 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "Resonanz_Regler_1.h"

/* Model step function */
void Resonanz_Regler_1_step(RT_MODEL_Resonanz_Regler_1_T *const
  Resonanz_Regler_1_M)
{
  DW_Resonanz_Regler_1_T *Resonanz_Regler_1_DW = Resonanz_Regler_1_M->dwork;
  ExtU_Resonanz_Regler_1_T *Resonanz_Regler_1_U = (ExtU_Resonanz_Regler_1_T *)
    Resonanz_Regler_1_M->inputs;
  ExtY_Resonanz_Regler_1_T *Resonanz_Regler_1_Y = (ExtY_Resonanz_Regler_1_T *)
    Resonanz_Regler_1_M->outputs;
  real_T rtb_Cos;
  real_T rtb_Cos1;
  real_T rtb_Product2;
  real_T rtb_UnitDelay5;

  /* Product: '<S1>/Product' incorporates:
   *  Inport: '<Root>/T_sw'
   *  Inport: '<Root>/h'
   *  Inport: '<Root>/omega_el'
   *  Product: '<S1>/Product3'
   */
  rtb_Cos = Resonanz_Regler_1_U->omega_el * Resonanz_Regler_1_U->h *
    Resonanz_Regler_1_U->T_sw;

  /* Trigonometry: '<S1>/Cos1' incorporates:
   *  Gain: '<S1>/Gain'
   */
  rtb_Cos1 = cos(2.0 * rtb_Cos);

  /* Product: '<S1>/Product2' incorporates:
   *  Inport: '<Root>/T_sw'
   *  Inport: '<Root>/VR'
   *  Inport: '<Root>/in_m'
   *  Inport: '<Root>/in_ref'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Subtract'
   */
  rtb_Product2 = (Resonanz_Regler_1_U->in_ref - Resonanz_Regler_1_U->in_m) *
    Resonanz_Regler_1_U->VR * Resonanz_Regler_1_U->T_sw;

  /* Trigonometry: '<S1>/Cos' */
  rtb_Cos = cos(rtb_Cos);

  /* UnitDelay: '<S1>/Unit Delay5' */
  rtb_UnitDelay5 = Resonanz_Regler_1_DW->UnitDelay5_DSTATE;

  /* Sum: '<S1>/Sum2' incorporates:
   *  Gain: '<S1>/-a2'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Product: '<S1>/-a1'
   *  Product: '<S1>/b0'
   *  Product: '<S1>/b1'
   *  Sum: '<S1>/Sum3'
   *  UnitDelay: '<S1>/Unit Delay3'
   *  UnitDelay: '<S1>/Unit Delay6'
   */
  rtb_Cos = ((-rtb_Cos * Resonanz_Regler_1_DW->UnitDelay3_DSTATE +
              -Resonanz_Regler_1_DW->UnitDelay6_DSTATE) + 2.0 * rtb_Cos *
             rtb_UnitDelay5) + rtb_Cos1 * rtb_Product2;

  /* Outport: '<Root>/out' */
  Resonanz_Regler_1_Y->out = rtb_Cos;

  /* Update for UnitDelay: '<S1>/Unit Delay3' */
  Resonanz_Regler_1_DW->UnitDelay3_DSTATE = rtb_Product2;

  /* Update for UnitDelay: '<S1>/Unit Delay6' */
  Resonanz_Regler_1_DW->UnitDelay6_DSTATE = rtb_UnitDelay5;

  /* Update for UnitDelay: '<S1>/Unit Delay5' */
  Resonanz_Regler_1_DW->UnitDelay5_DSTATE = rtb_Cos;
}

/* Model initialize function */
void Resonanz_Regler_1_initialize(RT_MODEL_Resonanz_Regler_1_T *const
  Resonanz_Regler_1_M)
{
  DW_Resonanz_Regler_1_T *Resonanz_Regler_1_DW = Resonanz_Regler_1_M->dwork;
  ExtU_Resonanz_Regler_1_T *Resonanz_Regler_1_U = (ExtU_Resonanz_Regler_1_T *)
    Resonanz_Regler_1_M->inputs;
  ExtY_Resonanz_Regler_1_T *Resonanz_Regler_1_Y = (ExtY_Resonanz_Regler_1_T *)
    Resonanz_Regler_1_M->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)Resonanz_Regler_1_DW, 0,
                sizeof(DW_Resonanz_Regler_1_T));

  /* external inputs */
  (void)memset(Resonanz_Regler_1_U, 0, sizeof(ExtU_Resonanz_Regler_1_T));

  /* external outputs */
  Resonanz_Regler_1_Y->out = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
