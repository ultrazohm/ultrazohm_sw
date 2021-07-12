/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_Strom_einfach.c
 *
 * Code generated for Simulink model 'FOC_Strom_einfach'.
 *
 * Model version                  : 2.2
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Jul 12 17:04:00 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "FOC_Strom_einfach.h"

/* Exported block parameters */
real_T P_R_id = 0.043563418129778458;  /* Variable: P_R_id
                                        * Referenced by: '<S39>/Proportional Gain'
                                        */
real_T P_R_iq = 0.043563418129778458;  /* Variable: P_R_iq
                                        * Referenced by: '<S87>/Proportional Gain'
                                        */
real_T T_R_id = 0.00039999999999999996;/* Variable: T_R_id
                                        * Referenced by: '<S38>/Integral Gain'
                                        */
real_T T_R_iq = 0.00039999999999999996;/* Variable: T_R_iq
                                        * Referenced by: '<S86>/Integral Gain'
                                        */
real_T U_ZK = 46.0;                    /* Variable: U_ZK
                                        * Referenced by: '<S9>/Constant'
                                        */
real_T T_sample = 1/(10*10e+3)         /* Sampletime for Integrator manually added
                                        */

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
   *  Inport: '<Root>/Iu'
   *  Inport: '<Root>/Iv'
   *  Inport: '<Root>/Iw'
   *  Sum: '<S4>/Add'
   */
  rtb_alpha_g = ((2.0 * rtU->Iu - rtU->Iv) - rtU->Iw) * 0.33333333333333331;

  /* Trigonometry: '<S5>/Cos' incorporates:
   *  Inport: '<Root>/theta_el'
   *  Trigonometry: '<S107>/Cos'
   */
  rtb_Gain1 = cos(rtU->theta_el);

  /* Trigonometry: '<S5>/Sin' incorporates:
   *  Inport: '<Root>/theta_el'
   *  Trigonometry: '<S107>/Sin'
   */
  rtb_Sin_tmp = sin(rtU->theta_el);

  /* Gain: '<S4>/Gain1' incorporates:
   *  Inport: '<Root>/Iv'
   *  Inport: '<Root>/Iw'
   *  Sum: '<S4>/Add1'
   */
  rtb_ProportionalGain_e = (rtU->Iv - rtU->Iw) * 0.57735026918962573;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Inport: '<Root>/Id'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product1'
   *  Sum: '<S5>/Add'
   *  Trigonometry: '<S5>/Cos'
   *  Trigonometry: '<S5>/Sin'
   */
  rtb_ProportionalGain = rtU->Id - (rtb_alpha_g * rtb_Gain1 + rtb_Sin_tmp *
    rtb_ProportionalGain_e);

  /* DiscreteIntegrator: '<S41>/Integrator' incorporates:
   *  Gain: '<S38>/Integral Gain'
   */
  Integrator = 1.0 / T_R_id * rtb_ProportionalGain * T_sample +
    rtDW->Integrator_DSTATE;

  /* Gain: '<S39>/Proportional Gain' incorporates:
   *  Sum: '<S50>/Sum'
   */
  rtb_ProportionalGain = (rtb_ProportionalGain + Integrator) * P_R_id;

  /* Sum: '<S3>/Sum' incorporates:
   *  Inport: '<Root>/Iq'
   *  Product: '<S5>/Product2'
   *  Product: '<S5>/Product3'
   *  Sum: '<S5>/Add1'
   *  Trigonometry: '<S5>/Cos'
   *  Trigonometry: '<S5>/Sin'
   */
  rtb_ProportionalGain_e = rtU->Iq - (rtb_Gain1 * rtb_ProportionalGain_e -
    rtb_alpha_g * rtb_Sin_tmp);

  /* DiscreteIntegrator: '<S89>/Integrator' incorporates:
   *  Gain: '<S86>/Integral Gain'
   */
  rtb_alpha_g = 1.0 / T_R_iq * rtb_ProportionalGain_e * T_sample +
    rtDW->Integrator_DSTATE_h;

  /* Gain: '<S87>/Proportional Gain' incorporates:
   *  Sum: '<S98>/Sum'
   */
  rtb_ProportionalGain_e = (rtb_ProportionalGain_e + rtb_alpha_g) * P_R_iq;

  /* Gain: '<S106>/Gain' incorporates:
   *  Product: '<S107>/Product'
   *  Product: '<S107>/Product1'
   *  Sum: '<S107>/Add'
   */
  rtb_Gain = (rtb_ProportionalGain * rtb_Gain1 - rtb_ProportionalGain_e *
              rtb_Sin_tmp) * 0.5;

  /* Outport: '<Root>/U' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Gain: '<S106>/Gain2'
   *  Product: '<S9>/Divide'
   *  Sum: '<S9>/Add'
   */
  rtY->U = 2.0 * rtb_Gain / U_ZK + 0.5;

  /* Gain: '<S106>/Gain1' incorporates:
   *  Product: '<S107>/Product2'
   *  Product: '<S107>/Product3'
   *  Sum: '<S107>/Add1'
   */
  rtb_Gain1 = (rtb_ProportionalGain * rtb_Sin_tmp + rtb_ProportionalGain_e *
               rtb_Gain1) * 0.8660254037844386;

  /* Outport: '<Root>/V' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant2'
   *  Product: '<S9>/Divide1'
   *  Sum: '<S106>/Add'
   *  Sum: '<S9>/Add1'
   */
  rtY->V = (rtb_Gain1 - rtb_Gain) / U_ZK + 0.5;

  /* Outport: '<Root>/W' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant3'
   *  Product: '<S9>/Divide2'
   *  Sum: '<S106>/Add1'
   *  Sum: '<S9>/Add2'
   */
  rtY->W = ((0.0 - rtb_Gain) - rtb_Gain1) / U_ZK + 0.5;

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
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
