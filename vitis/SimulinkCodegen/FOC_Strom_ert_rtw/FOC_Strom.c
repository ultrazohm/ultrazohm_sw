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
 * C/C++ source code generated on : Wed Jul 14 12:08:25 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "FOC_Strom.h"

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
   *  Inport: '<Root>/Act_Iu'
   *  Inport: '<Root>/Act_Iv'
   *  Inport: '<Root>/Act_Iw'
   *  Sum: '<S5>/Add'
   */
  rtDW->alpha_b = ((rtP.Gain2_Gain_g * rtU->Act_Iu - rtU->Act_Iv) - rtU->Act_Iw)
    * rtP.Gain_Gain_c;

  /* Outputs for IfAction SubSystem: '<S1>/Subsystem' incorporates:
   *  ActionPort: '<S3>/Action Port'
   */
  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Inport: '<Root>/Act_theta_el'
   *  Trigonometry: '<S111>/Cos'
   *  Trigonometry: '<S111>/Sin'
   *  Trigonometry: '<S6>/Cos'
   *  Trigonometry: '<S6>/Sin'
   */
  rtb_Cos_tmp = cos(rtU->Act_theta_el);
  rtb_Sin_tmp = sin(rtU->Act_theta_el);

  /* End of Outputs for SubSystem: '<S1>/Subsystem' */

  /* Gain: '<S5>/Gain1' incorporates:
   *  Inport: '<Root>/Act_Iv'
   *  Inport: '<Root>/Act_Iw'
   *  Sum: '<S5>/Add1'
   */
  rtb_beta_k = (rtU->Act_Iv - rtU->Act_Iw) * rtP.Gain1_Gain_e;

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
   *  Inport: '<Root>/fl_power'
   */
  rtPrevAction = rtDW->SwitchCase_ActiveSubsystem;
  if ((int32_T)rtU->fl_power == 1) {
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
      rtDW->Integrator_DSTATE = rtP.PI_d_InitialConditionForIntegra;
      rtDW->Integrator_DSTATE_a = rtP.PI_q_InitialConditionForIntegra;

      /* End of InitializeConditions for SubSystem: '<S1>/Subsystem' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/Subsystem' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    /* Sum: '<S3>/Sum1' incorporates:
     *  Inport: '<Root>/Ref_Id'
     */
    rtDW->alpha_b = rtU->Ref_Id - rtb_d;

    /* DiscreteIntegrator: '<S45>/Integrator' incorporates:
     *  Gain: '<S42>/Integral Gain'
     */
    rtb_beta_k = rtP.K_R_id * rtDW->alpha_b * rtP.Integrator_gainval +
      rtDW->Integrator_DSTATE;

    /* Sum: '<S54>/Sum' */
    rtb_Sum = rtDW->alpha_b + rtb_beta_k;

    /* SwitchCase: '<S7>/Switch Case' incorporates:
     *  Inport: '<Root>/fl_decoupling'
     */
    if ((int32_T)rtU->fl_decoupling == 1) {
      /* Outputs for IfAction SubSystem: '<S7>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S12>/Action Port'
       */
      /* Product: '<S12>/Product1' incorporates:
       *  Constant: '<S12>/Constant'
       *  Gain: '<S12>/Gain1'
       *  Inport: '<Root>/Act_w_el'
       *  Sum: '<S12>/Add'
       */
      rtb_d = (rtP.L_d * rtb_d + rtP.Psi_PM) * rtU->Act_w_el;

      /* Product: '<S12>/Product' incorporates:
       *  Gain: '<S12>/Gain'
       *  Inport: '<Root>/Act_w_el'
       */
      rtDW->alpha_b = rtP.L_q * rtb_q * rtU->Act_w_el;

      /* End of Outputs for SubSystem: '<S7>/Switch Case Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S7>/Switch Case Action Subsystem1' incorporates:
       *  ActionPort: '<S13>/Action Port'
       */
      /* SignalConversion generated from: '<S13>/U_hd_default' incorporates:
       *  Constant: '<S13>/Constant'
       */
      rtDW->alpha_b = rtP.Constant_Value;

      /* SignalConversion generated from: '<S13>/U_hq_default' incorporates:
       *  Constant: '<S13>/Constant1'
       */
      rtb_d = rtP.Constant1_Value;

      /* End of Outputs for SubSystem: '<S7>/Switch Case Action Subsystem1' */
    }

    /* End of SwitchCase: '<S7>/Switch Case' */

    /* Sum: '<S3>/Sum2' incorporates:
     *  Gain: '<S43>/Proportional Gain'
     */
    rtDW->alpha_b = rtP.P_R_id * rtb_Sum - rtDW->alpha_b;

    /* Sum: '<S3>/Sum' incorporates:
     *  Inport: '<Root>/Ref_Iq'
     */
    rtb_q = rtU->Ref_Iq - rtb_q;

    /* DiscreteIntegrator: '<S93>/Integrator' incorporates:
     *  Gain: '<S90>/Integral Gain'
     */
    rtb_Sum = rtP.K_R_iq * rtb_q * rtP.Integrator_gainval_p +
      rtDW->Integrator_DSTATE_a;

    /* Sum: '<S3>/Sum3' incorporates:
     *  Gain: '<S91>/Proportional Gain'
     *  Sum: '<S102>/Sum'
     */
    rtb_d += (rtb_q + rtb_Sum) * rtP.P_R_iq;

    /* Gain: '<S110>/Gain' incorporates:
     *  Product: '<S111>/Product'
     *  Product: '<S111>/Product1'
     *  Sum: '<S111>/Add'
     */
    rtb_Gain_g = (rtDW->alpha_b * rtb_Cos_tmp - rtb_d * rtb_Sin_tmp) *
      rtP.Gain_Gain;

    /* Gain: '<S110>/Gain1' incorporates:
     *  Product: '<S111>/Product2'
     *  Product: '<S111>/Product3'
     *  Sum: '<S111>/Add1'
     */
    rtb_q = (rtDW->alpha_b * rtb_Sin_tmp + rtb_d * rtb_Cos_tmp) * rtP.Gain1_Gain;

    /* Outport: '<Root>/a_V' incorporates:
     *  Constant: '<S11>/Constant2'
     *  Inport: '<Root>/Act_U_ZK'
     *  Product: '<S11>/Divide1'
     *  Sum: '<S110>/Add'
     *  Sum: '<S11>/Add1'
     */
    rtY->a_V = (rtb_q - rtb_Gain_g) / rtU->Act_U_ZK + rtP.Constant2_Value;

    /* Outport: '<Root>/a_W' incorporates:
     *  Constant: '<S11>/Constant3'
     *  Inport: '<Root>/Act_U_ZK'
     *  Product: '<S11>/Divide2'
     *  Sum: '<S110>/Add1'
     *  Sum: '<S11>/Add2'
     */
    rtY->a_W = ((0.0 - rtb_Gain_g) - rtb_q) / rtU->Act_U_ZK +
      rtP.Constant3_Value;

    /* Outport: '<Root>/a_U' incorporates:
     *  Constant: '<S11>/Constant1'
     *  Gain: '<S110>/Gain2'
     *  Inport: '<Root>/Act_U_ZK'
     *  Product: '<S11>/Divide'
     *  Sum: '<S11>/Add'
     */
    rtY->a_U = rtP.Gain2_Gain * rtb_Gain_g / rtU->Act_U_ZK +
      rtP.Constant1_Value_i;

    /* Update for DiscreteIntegrator: '<S45>/Integrator' */
    rtDW->Integrator_DSTATE = rtb_beta_k;

    /* Update for DiscreteIntegrator: '<S93>/Integrator' */
    rtDW->Integrator_DSTATE_a = rtb_Sum;

    /* End of Outputs for SubSystem: '<S1>/Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S1>/Switch Case Action Subsystem' incorporates:
     *  ActionPort: '<S4>/Action Port'
     */
    /* Outport: '<Root>/a_U' incorporates:
     *  Constant: '<S4>/Constant'
     *  SignalConversion generated from: '<S4>/U_default'
     */
    rtY->a_U = rtP.Constant_Value_p;

    /* Outport: '<Root>/a_V' incorporates:
     *  Constant: '<S4>/Constant'
     *  SignalConversion generated from: '<S4>/V_default'
     */
    rtY->a_V = rtP.Constant_Value_p;

    /* Outport: '<Root>/a_W' incorporates:
     *  Constant: '<S4>/Constant'
     *  SignalConversion generated from: '<S4>/W_default'
     */
    rtY->a_W = rtP.Constant_Value_p;

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
  rtDW->Integrator_DSTATE = rtP.PI_d_InitialConditionForIntegra;

  /* InitializeConditions for DiscreteIntegrator: '<S93>/Integrator' */
  rtDW->Integrator_DSTATE_a = rtP.PI_q_InitialConditionForIntegra;

  /* End of SystemInitialize for SubSystem: '<S1>/Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
