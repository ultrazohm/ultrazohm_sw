/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_Strom.c
 *
 * Code generated for Simulink model 'FOC_Strom'.
 *
 * Model version                  : 2.2
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Jul 12 16:40:10 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "FOC_Strom.h"

/* Exported block parameters */
real_T L_d = 3.0E-5;                   /* Variable: L_d
                                        * Referenced by: '<S12>/Gain1'
                                        */
real_T L_q = 5.0E-5;                   /* Variable: L_q
                                        * Referenced by: '<S12>/Gain'
                                        */
real_T P_R_id = 0.043563418129778458;  /* Variable: P_R_id
                                        * Referenced by: '<S43>/Proportional Gain'
                                        */
real_T P_R_iq = 0.043563418129778458;   /* Variable: P_R_iq
                                        * Referenced by: '<S91>/Proportional Gain'
                                        */
real_T Psi_PM = 0.007;                 /* Variable: Psi_PM
                                        * Referenced by: '<S12>/Constant'
                                        */
real_T T_R_id = 0.00039999999999999996;/* Variable: T_R_id
                                        * Referenced by: '<S42>/Integral Gain'
                                        */
real_T T_R_iq = 0.00039999999999999996;/* Variable: T_R_iq
                                        * Referenced by: '<S90>/Integral Gain'
                                        */
real_T U_ZK = 12.0;                    /* Variable: U_ZK
                                        * Referenced by: '<S11>/Constant'
                                        */
real_T T_sample = 1/(10*10e+3)         /* Sampletime for Integrator manually added
                                        */

/* Model step function */
void FOC_Strom_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real_T rtb_Cos_tmp;
  real_T rtb_Gain_g;
  real_T rtb_Sin_tmp;
  real_T rtb_Sum;
  real_T rtb_beta_k;
  real_T rtb_d;
  real_T rtb_q;
  int8_T rtAction;
  int8_T rtPrevAction;

  /* Gain: '<S5>/Gain' incorporates:
   *  Gain: '<S5>/Gain2'
   *  Inport: '<Root>/Iu'
   *  Inport: '<Root>/Iv'
   *  Inport: '<Root>/Iw'
   *  Sum: '<S5>/Add'
   */
  rtDW->alpha_b = ((2.0 * rtU->Iu - rtU->Iv) - rtU->Iw) * 0.33333333333333331;

  /* Outputs for IfAction SubSystem: '<S1>/Subsystem' incorporates:
   *  ActionPort: '<S3>/Action Port'
   */
  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Inport: '<Root>/theta_el'
   *  Trigonometry: '<S111>/Cos'
   *  Trigonometry: '<S111>/Sin'
   *  Trigonometry: '<S6>/Cos'
   *  Trigonometry: '<S6>/Sin'
   */
  rtb_Cos_tmp = cos(rtU->theta_el);
  rtb_Sin_tmp = sin(rtU->theta_el);

  /* End of Outputs for SubSystem: '<S1>/Subsystem' */

  /* Gain: '<S5>/Gain1' incorporates:
   *  Inport: '<Root>/Iv'
   *  Inport: '<Root>/Iw'
   *  Sum: '<S5>/Add1'
   */
  rtb_beta_k = (rtU->Iv - rtU->Iw) * 0.57735026918962573;

  /* Sum: '<S6>/Add' incorporates:
   *  Product: '<S6>/Product'
   *  Product: '<S6>/Product1'
   *  Trigonometry: '<S6>/Cos'
   *  Trigonometry: '<S6>/Sin'
   */
  rtb_d = rtDW->alpha_b * rtb_Cos_tmp + rtb_Sin_tmp * rtb_beta_k;

  /* Sum: '<S6>/Add1' incorporates:
   *  Product: '<S6>/Product2'
   *  Product: '<S6>/Product3'
   *  Trigonometry: '<S6>/Cos'
   *  Trigonometry: '<S6>/Sin'
   */
  rtb_q = rtb_Cos_tmp * rtb_beta_k - rtDW->alpha_b * rtb_Sin_tmp;

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Inport: '<Root>/power'
   */
  rtPrevAction = rtDW->SwitchCase_ActiveSubsystem;
  if ((int32_T)rtU->power == 1) {
    rtAction = 0;
  } else {
    rtAction = 1;
  }

  rtDW->SwitchCase_ActiveSubsystem = rtAction;
  if (rtAction == 0) {
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/Subsystem' incorporates:
       *  ActionPort: '<S3>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  DiscreteIntegrator: '<S45>/Integrator'
       *  DiscreteIntegrator: '<S93>/Integrator'
       */
      rtDW->Integrator_DSTATE = 0.0;
      rtDW->Integrator_DSTATE_a = 0.0;

      /* End of InitializeConditions for SubSystem: '<S1>/Subsystem' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/Subsystem' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    /* Sum: '<S3>/Sum1' incorporates:
     *  Inport: '<Root>/Id'
     */
    rtDW->alpha_b = rtU->Id - rtb_d;

    /* DiscreteIntegrator: '<S45>/Integrator' incorporates:
     *  Gain: '<S42>/Integral Gain'
     */
    rtb_beta_k = 1.0 / T_R_id * rtDW->alpha_b * T_sample + rtDW->Integrator_DSTATE;

    /* Sum: '<S54>/Sum' */
    rtb_Sum = rtDW->alpha_b + rtb_beta_k;

    /* SwitchCase: '<S7>/Switch Case' incorporates:
     *  Inport: '<Root>/decoupling'
     */
    if ((int32_T)rtU->decoupling == 1) {
      /* Outputs for IfAction SubSystem: '<S7>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S12>/Action Port'
       */
      /* Product: '<S12>/Product1' incorporates:
       *  Constant: '<S12>/Constant'
       *  Gain: '<S12>/Gain1'
       *  Inport: '<Root>/w_el'
       *  Sum: '<S12>/Add'
       */
      rtb_d = (L_d * rtb_d + Psi_PM) * rtU->w_el;

      /* Product: '<S12>/Product' incorporates:
       *  Gain: '<S12>/Gain'
       *  Inport: '<Root>/w_el'
       */
      rtDW->alpha_b = L_q * rtb_q * rtU->w_el;

      /* End of Outputs for SubSystem: '<S7>/Switch Case Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S7>/Switch Case Action Subsystem1' incorporates:
       *  ActionPort: '<S13>/Action Port'
       */
      /* SignalConversion generated from: '<S13>/U_hd_default' incorporates:
       *  Constant: '<S13>/Constant'
       */
      rtDW->alpha_b = 0.0;

      /* SignalConversion generated from: '<S13>/U_hq_default' incorporates:
       *  Constant: '<S13>/Constant1'
       */
      rtb_d = 0.0;

      /* End of Outputs for SubSystem: '<S7>/Switch Case Action Subsystem1' */
    }

    /* End of SwitchCase: '<S7>/Switch Case' */

    /* Sum: '<S3>/Sum2' incorporates:
     *  Gain: '<S43>/Proportional Gain'
     */
    rtDW->alpha_b = P_R_id * rtb_Sum - rtDW->alpha_b;

    /* Sum: '<S3>/Sum' incorporates:
     *  Inport: '<Root>/Iq'
     */
    rtb_q = rtU->Iq - rtb_q;

    /* DiscreteIntegrator: '<S93>/Integrator' incorporates:
     *  Gain: '<S90>/Integral Gain'
     */
    rtb_Sum = 1.0 / T_R_iq * rtb_q * T_sample + rtDW->Integrator_DSTATE_a;

    /* Sum: '<S3>/Sum3' incorporates:
     *  Gain: '<S91>/Proportional Gain'
     *  Sum: '<S102>/Sum'
     */
    rtb_d += (rtb_q + rtb_Sum) * P_R_iq;

    /* Gain: '<S110>/Gain' incorporates:
     *  Product: '<S111>/Product'
     *  Product: '<S111>/Product1'
     *  Sum: '<S111>/Add'
     */
    rtb_Gain_g = (rtDW->alpha_b * rtb_Cos_tmp - rtb_d * rtb_Sin_tmp) * 0.5;

    /* Gain: '<S110>/Gain1' incorporates:
     *  Product: '<S111>/Product2'
     *  Product: '<S111>/Product3'
     *  Sum: '<S111>/Add1'
     */
    rtb_q = (rtDW->alpha_b * rtb_Sin_tmp + rtb_d * rtb_Cos_tmp) *
      0.8660254037844386;

    /* Outport: '<Root>/V' incorporates:
     *  Constant: '<S11>/Constant'
     *  Constant: '<S11>/Constant2'
     *  Product: '<S11>/Divide1'
     *  Sum: '<S110>/Add'
     *  Sum: '<S11>/Add1'
     */
    rtY->V = (rtb_q - rtb_Gain_g) / U_ZK + 0.5;

    /* Outport: '<Root>/U' incorporates:
     *  Constant: '<S11>/Constant'
     *  Constant: '<S11>/Constant1'
     *  Gain: '<S110>/Gain2'
     *  Product: '<S11>/Divide'
     *  Sum: '<S11>/Add'
     */
    rtY->U = 2.0 * rtb_Gain_g / U_ZK + 0.5;

    /* Outport: '<Root>/W' incorporates:
     *  Constant: '<S11>/Constant'
     *  Constant: '<S11>/Constant3'
     *  Product: '<S11>/Divide2'
     *  Sum: '<S110>/Add1'
     *  Sum: '<S11>/Add2'
     */
    rtY->W = ((0.0 - rtb_Gain_g) - rtb_q) / U_ZK + 0.5;

    /* Update for DiscreteIntegrator: '<S45>/Integrator' */
    rtDW->Integrator_DSTATE = rtb_beta_k;

    /* Update for DiscreteIntegrator: '<S93>/Integrator' */
    rtDW->Integrator_DSTATE_a = rtb_Sum;

    /* End of Outputs for SubSystem: '<S1>/Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S1>/Switch Case Action Subsystem' incorporates:
     *  ActionPort: '<S4>/Action Port'
     */
    /* Outport: '<Root>/U' incorporates:
     *  Constant: '<S4>/Constant'
     *  SignalConversion generated from: '<S4>/U_default'
     */
    rtY->U = 0.0;

    /* Outport: '<Root>/V' incorporates:
     *  Constant: '<S4>/Constant'
     *  SignalConversion generated from: '<S4>/V_default'
     */
    rtY->V = 0.0;

    /* Outport: '<Root>/W' incorporates:
     *  Constant: '<S4>/Constant'
     *  SignalConversion generated from: '<S4>/W_default'
     */
    rtY->W = 0.0;

    /* End of Outputs for SubSystem: '<S1>/Switch Case Action Subsystem' */
  }
}

/* Model initialize function */
void FOC_Strom_initialize(RT_MODEL *const rtM)
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

  /* Start for SwitchCase: '<S1>/Switch Case' */
  rtDW->SwitchCase_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: '<S1>/Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S45>/Integrator' */
  rtDW->Integrator_DSTATE = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S93>/Integrator' */
  rtDW->Integrator_DSTATE_a = 0.0;

  /* End of SystemInitialize for SubSystem: '<S1>/Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
