/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_Strom_einfach.c
 *
 * Code generated for Simulink model 'FOC_Strom_einfach'.
 *
 * Model version                  : 2.3
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jul 14 12:21:52 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "FOC_Strom_einfach.h"

/* Model step function */
void FOC_Strom_einfach_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real_T Integrator;
  real_T rtb_Gain;
  real_T rtb_Gain1;
  real_T rtb_ProportionalGain;
  real_T rtb_ProportionalGain_e;
  real_T rtb_Sin_tmp;
  real_T rtb_alpha_g;

  /* Gain: '<S4>/Gain' incorporates:
   *  Gain: '<S4>/Gain2'
   *  Inport: '<Root>/Act_Iu'
   *  Inport: '<Root>/Act_Iv'
   *  Inport: '<Root>/Act_Iw'
   *  Sum: '<S4>/Add'
   */
  rtb_alpha_g = ((rtP.Gain2_Gain * rtU->Act_Iu - rtU->Act_Iv) - rtU->Act_Iw) *
    rtP.Gain_Gain;

  /* Trigonometry: '<S5>/Cos' incorporates:
   *  Inport: '<Root>/Act_theta_el'
   *  Trigonometry: '<S107>/Cos'
   */
  rtb_Gain1 = cos(rtU->Act_theta_el);

  /* Trigonometry: '<S5>/Sin' incorporates:
   *  Inport: '<Root>/Act_theta_el'
   *  Trigonometry: '<S107>/Sin'
   */
  rtb_Sin_tmp = sin(rtU->Act_theta_el);

  /* Gain: '<S4>/Gain1' incorporates:
   *  Inport: '<Root>/Act_Iv'
   *  Inport: '<Root>/Act_Iw'
   *  Sum: '<S4>/Add1'
   */
  rtb_ProportionalGain_e = (rtU->Act_Iv - rtU->Act_Iw) * rtP.Gain1_Gain;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Inport: '<Root>/Ref_Id'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product1'
   *  Sum: '<S5>/Add'
   *  Trigonometry: '<S5>/Cos'
   *  Trigonometry: '<S5>/Sin'
   */
  rtb_ProportionalGain = rtU->Ref_Id - (rtb_alpha_g * rtb_Gain1 + rtb_Sin_tmp *
    rtb_ProportionalGain_e);

  /* DiscreteIntegrator: '<S41>/Integrator' incorporates:
   *  Gain: '<S38>/Integral Gain'
   */
  Integrator = rtP.K_R_id * rtb_ProportionalGain * rtP.Integrator_gainval +
    rtDW->Integrator_DSTATE;

  /* Gain: '<S39>/Proportional Gain' incorporates:
   *  Sum: '<S50>/Sum'
   */
  rtb_ProportionalGain = (rtb_ProportionalGain + Integrator) * rtP.P_R_id;

  /* Sum: '<S3>/Sum' incorporates:
   *  Inport: '<Root>/Ref_Iq'
   *  Product: '<S5>/Product2'
   *  Product: '<S5>/Product3'
   *  Sum: '<S5>/Add1'
   *  Trigonometry: '<S5>/Cos'
   *  Trigonometry: '<S5>/Sin'
   */
  rtb_ProportionalGain_e = rtU->Ref_Iq - (rtb_Gain1 * rtb_ProportionalGain_e -
    rtb_alpha_g * rtb_Sin_tmp);

  /* DiscreteIntegrator: '<S89>/Integrator' incorporates:
   *  Gain: '<S86>/Integral Gain'
   */
  rtb_alpha_g = rtP.K_R_iq * rtb_ProportionalGain_e * rtP.Integrator_gainval_p +
    rtDW->Integrator_DSTATE_h;

  /* Gain: '<S87>/Proportional Gain' incorporates:
   *  Sum: '<S98>/Sum'
   */
  rtb_ProportionalGain_e = (rtb_ProportionalGain_e + rtb_alpha_g) * rtP.P_R_iq;

  /* Gain: '<S106>/Gain' incorporates:
   *  Product: '<S107>/Product'
   *  Product: '<S107>/Product1'
   *  Sum: '<S107>/Add'
   */
  rtb_Gain = (rtb_ProportionalGain * rtb_Gain1 - rtb_ProportionalGain_e *
              rtb_Sin_tmp) * rtP.Gain_Gain_m;

  /* Outport: '<Root>/a_U' incorporates:
   *  Constant: '<S9>/Constant1'
   *  Gain: '<S106>/Gain2'
   *  Inport: '<Root>/Act_U_ZK'
   *  Product: '<S9>/Divide'
   *  Sum: '<S9>/Add'
   */
  rtY->a_U = rtP.Gain2_Gain_i * rtb_Gain / rtU->Act_U_ZK + rtP.Constant1_Value;

  /* Gain: '<S106>/Gain1' incorporates:
   *  Product: '<S107>/Product2'
   *  Product: '<S107>/Product3'
   *  Sum: '<S107>/Add1'
   */
  rtb_Gain1 = (rtb_ProportionalGain * rtb_Sin_tmp + rtb_ProportionalGain_e *
               rtb_Gain1) * rtP.Gain1_Gain_d;

  /* Outport: '<Root>/a_V' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Inport: '<Root>/Act_U_ZK'
   *  Product: '<S9>/Divide1'
   *  Sum: '<S106>/Add'
   *  Sum: '<S9>/Add1'
   */
  rtY->a_V = (rtb_Gain1 - rtb_Gain) / rtU->Act_U_ZK + rtP.Constant2_Value;

  /* Outport: '<Root>/a_W' incorporates:
   *  Constant: '<S9>/Constant3'
   *  Inport: '<Root>/Act_U_ZK'
   *  Product: '<S9>/Divide2'
   *  Sum: '<S106>/Add1'
   *  Sum: '<S9>/Add2'
   */
  rtY->a_W = ((0.0 - rtb_Gain) - rtb_Gain1) / rtU->Act_U_ZK +
    rtP.Constant3_Value;

  /* Update for DiscreteIntegrator: '<S41>/Integrator' */
  rtDW->Integrator_DSTATE = Integrator;

  /* Update for DiscreteIntegrator: '<S89>/Integrator' */
  rtDW->Integrator_DSTATE_h = rtb_alpha_g;
}

/* Model initialize function */
void FOC_Strom_einfach_initialize(RT_MODEL *const rtM)
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

  /* InitializeConditions for DiscreteIntegrator: '<S41>/Integrator' */
  rtDW->Integrator_DSTATE = rtP.PI_d_InitialConditionForIntegra;

  /* InitializeConditions for DiscreteIntegrator: '<S89>/Integrator' */
  rtDW->Integrator_DSTATE_h = rtP.PI_q_InitialConditionForIntegra;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
