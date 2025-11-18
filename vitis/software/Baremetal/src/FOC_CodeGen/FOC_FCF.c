/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF.c
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Nov 18 19:20:46 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_FCF.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void FOC_FCF_step(RT_MODEL_FOC_FCF_T *const FOC_FCF_M)
{
  B_FOC_FCF_T *FOC_FCF_B = FOC_FCF_M->blockIO;
  DW_FOC_FCF_T *FOC_FCF_DW = FOC_FCF_M->dwork;
  ExtU_FOC_FCF_T *FOC_FCF_U = (ExtU_FOC_FCF_T *) FOC_FCF_M->inputs;
  ExtY_FOC_FCF_T *FOC_FCF_Y = (ExtY_FOC_FCF_T *) FOC_FCF_M->outputs;
  int32_T i;
  int32_T i_0;
  real32_T tmp[6];
  real32_T Gain;
  real32_T I_phA;
  real32_T I_phA_0;
  real32_T Sum1_f;
  real32_T TrafoMatrixuvwalphabeta;
  real32_T tmp_0;
  boolean_T tmp_idx_0;
  boolean_T tmp_idx_1;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* MultiPortSwitch: '<S1>/ModeSwitch' incorporates:
   *  Constant: '<S1>/FOC_SELECT_Mode_Intern'
   */
  if (FOC_FCF_P.FOC_SELECT_Mode_Intern == 0) {
    /* MultiPortSwitch: '<S1>/ModeSwitch' */
    FOC_FCF_B->ModeSwitch = FOC_FCF_U->FOC_Mode;
  } else {
    /* MultiPortSwitch: '<S1>/ModeSwitch' incorporates:
     *  Constant: '<S1>/FOC_Mode_Intern'
     */
    FOC_FCF_B->ModeSwitch = FOC_FCF_P.FOC_Mode_Intern;
  }

  /* End of MultiPortSwitch: '<S1>/ModeSwitch' */

  /* DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
  tmp_0 = FOC_FCF_P.DiscreteTransferFcn_NumCoef *
    FOC_FCF_DW->DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
  FOC_FCF_B->DiscreteTransferFcn = tmp_0;

  /* Gain: '<S7>/f_2_w_el' incorporates:
   *  Constant: '<S7>/Uf_w_el'
   */
  FOC_FCF_B->f_2_w_el = FOC_FCF_P.f_2_w_el_Gain * FOC_FCF_P.FOC_Uf_f_el;

  /* Product: '<S27>/Product' incorporates:
   *  Constant: '<S27>/FOC_T_fast'
   */
  FOC_FCF_B->Product = FOC_FCF_B->f_2_w_el * FOC_FCF_P.FOC_T_fast_Value;

  /* UnitDelay: '<S27>/Unit Delay' */
  FOC_FCF_B->UnitDelay = FOC_FCF_DW->UnitDelay_DSTATE;

  /* Sum: '<S27>/Add' */
  FOC_FCF_B->Add = FOC_FCF_B->Product + FOC_FCF_B->UnitDelay;

  /* Gain: '<S17>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[0];
  I_phA = FOC_FCF_U->I_phA[1];
  I_phA_0 = FOC_FCF_U->I_phA[2];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S17>/TrafoMatrix uvw->alphabeta' */
    TrafoMatrixuvwalphabeta = FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i_0] *
      tmp_0;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i_0 + 2] *
      I_phA;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i_0 + 4] *
      I_phA_0;
    FOC_FCF_B->TrafoMatrixuvwalphabeta[i_0] = TrafoMatrixuvwalphabeta;
  }

  /* Saturate: '<S3>/ResolverOffsetLimitation' */
  if (FOC_FCF_P.FOC_phi_offset > FOC_FCF_P.ResolverOffsetLimitation_UpperS) {
    /* Saturate: '<S3>/ResolverOffsetLimitation' */
    FOC_FCF_B->ResolverOffsetLimitation =
      FOC_FCF_P.ResolverOffsetLimitation_UpperS;
  } else if (FOC_FCF_P.FOC_phi_offset <
             FOC_FCF_P.ResolverOffsetLimitation_LowerS) {
    /* Saturate: '<S3>/ResolverOffsetLimitation' */
    FOC_FCF_B->ResolverOffsetLimitation =
      FOC_FCF_P.ResolverOffsetLimitation_LowerS;
  } else {
    /* Saturate: '<S3>/ResolverOffsetLimitation' */
    FOC_FCF_B->ResolverOffsetLimitation = FOC_FCF_P.FOC_phi_offset;
  }

  /* End of Saturate: '<S3>/ResolverOffsetLimitation' */

  /* Sum: '<S3>/Sum1' */
  FOC_FCF_B->Sum1 = FOC_FCF_B->ResolverOffsetLimitation + FOC_FCF_U->phi_elrad;

  /* UnitDelay: '<S12>/Unit Delay1' */
  FOC_FCF_B->w_el = FOC_FCF_DW->UnitDelay1_DSTATE;

  /* Gain: '<S9>/DeadTimeCompensation' */
  FOC_FCF_B->DeadTimeCompensation = FOC_FCF_P.FOC_PhiSensorTdead *
    FOC_FCF_B->w_el;

  /* Sum: '<S9>/Sum3' */
  FOC_FCF_B->Sum3 = FOC_FCF_B->Sum1 + FOC_FCF_B->DeadTimeCompensation;

  /* UnitDelay: '<S11>/Unit Delay' */
  FOC_FCF_B->UnitDelay_l = FOC_FCF_DW->UnitDelay_DSTATE_h;

  /* Sum: '<S11>/Sum' */
  FOC_FCF_B->Sum = FOC_FCF_B->Sum3 - FOC_FCF_B->UnitDelay_l;

  /* RelationalOperator: '<S11>/Sprung?' incorporates:
   *  Constant: '<S11>/Constant3'
   */
  FOC_FCF_B->Sprung = (FOC_FCF_B->Sum < FOC_FCF_P.Constant3_Value);

  /* Switch: '<S11>/Switch' */
  if (FOC_FCF_B->Sprung) {
    /* Switch: '<S11>/Switch' incorporates:
     *  Constant: '<S11>/Constant2'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant2_Value;
  } else {
    /* Switch: '<S11>/Switch' incorporates:
     *  Constant: '<S11>/Constant4'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant4_Value;
  }

  /* End of Switch: '<S11>/Switch' */

  /* RelationalOperator: '<S11>/Sprung?1' incorporates:
   *  Constant: '<S11>/Constant1'
   */
  FOC_FCF_B->Sprung1 = (FOC_FCF_B->Sum > FOC_FCF_P.Constant1_Value_ep);

  /* Switch: '<S11>/Switch1' */
  if (FOC_FCF_B->Sprung1) {
    /* Switch: '<S11>/Switch1' incorporates:
     *  Constant: '<S11>/Constant5'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant5_Value;
  } else {
    /* Switch: '<S11>/Switch1' incorporates:
     *  Constant: '<S11>/Constant6'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant6_Value;
  }

  /* End of Switch: '<S11>/Switch1' */

  /* Sum: '<S11>/Sum2' */
  FOC_FCF_B->Sum2 = FOC_FCF_B->Switch + FOC_FCF_B->Switch1;

  /* UnitDelay: '<S9>/Unit Delay3' */
  FOC_FCF_B->UnitDelay3 = FOC_FCF_DW->UnitDelay3_DSTATE;

  /* Sum: '<S9>/Sum7' */
  FOC_FCF_B->phi_el_observer = FOC_FCF_B->UnitDelay3 - FOC_FCF_B->Sum2;

  /* Product: '<S6>/Product' incorporates:
   *  Constant: '<S6>/FOC_T_fast'
   */
  FOC_FCF_B->Product_e = FOC_FCF_U->w_el_Ref_IfStarter *
    FOC_FCF_P.FOC_T_fast_Value_d;

  /* UnitDelay: '<S6>/Unit Delay' */
  FOC_FCF_B->UnitDelay_a = FOC_FCF_DW->UnitDelay_DSTATE_p;

  /* Sum: '<S6>/Add' */
  FOC_FCF_B->Add_m = FOC_FCF_B->Product_e + FOC_FCF_B->UnitDelay_a;

  /* MultiPortSwitch: '<S1>/Use_If_Starter' */
  if ((int32_T)FOC_FCF_U->IfStarter_Active == 0) {
    /* MultiPortSwitch: '<S3>/Selectphicalc2' incorporates:
     *  Constant: '<S3>/Constant3'
     */
    if (FOC_FCF_P.FOC_SELECT_phi == 1) {
      /* MultiPortSwitch: '<S3>/Selectphicalc2' */
      FOC_FCF_B->Selectphicalc2 = FOC_FCF_B->Sum1;
    } else {
      /* MultiPortSwitch: '<S3>/Selectphicalc2' */
      FOC_FCF_B->Selectphicalc2 = FOC_FCF_B->phi_el_observer;
    }

    /* End of MultiPortSwitch: '<S3>/Selectphicalc2' */

    /* Switch: '<S10>/Switch1' */
    if (FOC_FCF_B->Selectphicalc2 > FOC_FCF_P.Switch1_Threshold) {
      /* Sum: '<S10>/Sum2' incorporates:
       *  Constant: '<S10>/Constant'
       */
      FOC_FCF_B->Sum2_l = FOC_FCF_B->Selectphicalc2 - FOC_FCF_P.Constant_Value_e;

      /* Switch: '<S10>/Switch1' */
      FOC_FCF_B->Switch1_d = FOC_FCF_B->Sum2_l;
    } else {
      /* Switch: '<S10>/Switch1' */
      FOC_FCF_B->Switch1_d = FOC_FCF_B->Selectphicalc2;
    }

    /* End of Switch: '<S10>/Switch1' */

    /* Switch: '<S10>/Switch2' */
    if (FOC_FCF_B->Switch1_d > FOC_FCF_P.Switch2_Threshold) {
      /* Switch: '<S10>/Switch2' */
      FOC_FCF_B->Switch2_f = FOC_FCF_B->Switch1_d;
    } else {
      /* Sum: '<S10>/Sum3' incorporates:
       *  Constant: '<S10>/Constant1'
       */
      FOC_FCF_B->Sum3_h = FOC_FCF_B->Switch1_d + FOC_FCF_P.Constant1_Value_g;

      /* Switch: '<S10>/Switch2' */
      FOC_FCF_B->Switch2_f = FOC_FCF_B->Sum3_h;
    }

    /* End of Switch: '<S10>/Switch2' */

    /* MultiPortSwitch: '<S1>/Use_If_Starter' */
    FOC_FCF_B->phi_el_I_trafo = FOC_FCF_B->Switch2_f;
  } else {
    /* MultiPortSwitch: '<S1>/Use_If_Starter' */
    FOC_FCF_B->phi_el_I_trafo = FOC_FCF_B->Add_m;
  }

  /* End of MultiPortSwitch: '<S1>/Use_If_Starter' */

  /* Trigonometry: '<S17>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1 = cosf(FOC_FCF_B->phi_el_I_trafo);

  /* Product: '<S17>/TrafoProd' */
  FOC_FCF_B->TrafoProd = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction1;

  /* Trigonometry: '<S17>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction = sinf(FOC_FCF_B->phi_el_I_trafo);

  /* Product: '<S17>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3 = FOC_FCF_B->TrigonometricFunction *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Sum: '<S17>/TrafoSum' */
  FOC_FCF_B->TrafoSum = FOC_FCF_B->TrafoProd + FOC_FCF_B->TrafoProd3;

  /* Product: '<S17>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1 = FOC_FCF_B->TrigonometricFunction1 *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Product: '<S17>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2 = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction;

  /* Sum: '<S17>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1 = FOC_FCF_B->TrafoProd1 - FOC_FCF_B->TrafoProd2;

  /* SignalConversion generated from: '<S17>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0] = FOC_FCF_B->TrafoSum;
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1] = FOC_FCF_B->TrafoSum1;

  /* Sum: '<S15>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S20>/KP*e[k]1' incorporates:
   *  Constant: '<S20>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S20>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[0] = FOC_FCF_DW->IntegDelay1_DSTATE[0];

  /* Sum: '<S15>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S20>/KP*e[k]1' incorporates:
   *  Constant: '<S20>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S20>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[1] = FOC_FCF_DW->IntegDelay1_DSTATE[1];

  /* Product: '<S20>/Product1' incorporates:
   *  Constant: '<S20>/FOC_KI'
   *  Constant: '<S20>/FOC_T_fast'
   */
  FOC_FCF_B->Product1 = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_n;

  /* Logic: '<S1>/Logical Operator1' incorporates:
   *  Constant: '<S1>/Enable'
   */
  FOC_FCF_B->LogicalOperator1 = ((FOC_FCF_P.FOC_Enable != 0.0F) &&
    (FOC_FCF_U->FOC_Enable != 0.0F));

  /* Switch: '<S20>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Product: '<S20>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1[0] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[0] = tmp_0;

    /* Sum: '<S20>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1[0];
    FOC_FCF_B->IntSum1_p[0] = tmp_0;

    /* Switch: '<S20>/IntegEnaSwitch1' */
    FOC_FCF_B->U_dq1_CC[0] = tmp_0;

    /* Product: '<S20>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1[1] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[1] = tmp_0;

    /* Sum: '<S20>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1[1];
    FOC_FCF_B->IntSum1_p[1] = tmp_0;

    /* Switch: '<S20>/IntegEnaSwitch1' */
    FOC_FCF_B->U_dq1_CC[1] = tmp_0;
  } else {
    /* Switch: '<S20>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S20>/Zero'
     */
    FOC_FCF_B->U_dq1_CC[0] = FOC_FCF_P.Zero_Value;
    FOC_FCF_B->U_dq1_CC[1] = FOC_FCF_P.Zero_Value;
  }

  /* End of Switch: '<S20>/IntegEnaSwitch1' */

  /* Gain: '<S18>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[3];
  I_phA = FOC_FCF_U->I_phA[4];
  I_phA_0 = FOC_FCF_U->I_phA[5];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S18>/TrafoMatrix uvw->alphabeta' */
    TrafoMatrixuvwalphabeta = FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i_0] *
      tmp_0;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i_0 + 2]
      * I_phA;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i_0 + 4]
      * I_phA_0;
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[i_0] = TrafoMatrixuvwalphabeta;
  }

  /* Sum: '<S5>/Sum1' incorporates:
   *  Constant: '<S5>/FOC_6ph_AngleShift'
   */
  FOC_FCF_B->Sum1_d = FOC_FCF_B->phi_el_I_trafo + FOC_FCF_P.FOC_6ph_AngleShift;

  /* Trigonometry: '<S18>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_b = cosf(FOC_FCF_B->Sum1_d);

  /* Product: '<S18>/TrafoProd' */
  FOC_FCF_B->TrafoProd_a = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction1_b;

  /* Trigonometry: '<S18>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_l = sinf(FOC_FCF_B->Sum1_d);

  /* Product: '<S18>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3_i = FOC_FCF_B->TrigonometricFunction_l *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Sum: '<S18>/TrafoSum' */
  FOC_FCF_B->TrafoSum_m = FOC_FCF_B->TrafoProd_a + FOC_FCF_B->TrafoProd3_i;

  /* Product: '<S18>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1_b = FOC_FCF_B->TrigonometricFunction1_b *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Product: '<S18>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2_b = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction_l;

  /* Sum: '<S18>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1_b = FOC_FCF_B->TrafoProd1_b - FOC_FCF_B->TrafoProd2_b;

  /* SignalConversion generated from: '<S18>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0] = FOC_FCF_B->TrafoSum_m;
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1] = FOC_FCF_B->TrafoSum1_b;

  /* Sum: '<S16>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S24>/KP*e[k]1' incorporates:
   *  Constant: '<S24>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S24>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[0] = FOC_FCF_DW->IntegDelay1_DSTATE_p[0];

  /* Sum: '<S16>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S24>/KP*e[k]1' incorporates:
   *  Constant: '<S24>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S24>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[1] = FOC_FCF_DW->IntegDelay1_DSTATE_p[1];

  /* Product: '<S24>/Product1' incorporates:
   *  Constant: '<S24>/FOC_KI'
   *  Constant: '<S24>/FOC_T_fast'
   */
  FOC_FCF_B->Product1_k = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_e;

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S4>/FOC_T_fast'
   *  Constant: '<S4>/FOC_output_trafo_delay'
   */
  FOC_FCF_B->Product_c = FOC_FCF_P.FOC_output_trafo_delay * FOC_FCF_B->w_el *
    FOC_FCF_P.FOC_T_fast_Value_m;

  /* Sum: '<S4>/Sum' */
  FOC_FCF_B->Sum_k = FOC_FCF_B->phi_el_I_trafo + FOC_FCF_B->Product_c;

  /* Switch: '<S14>/Switch1' */
  if (FOC_FCF_B->Sum_k > FOC_FCF_P.Switch1_Threshold_a) {
    /* Sum: '<S14>/Sum2' incorporates:
     *  Constant: '<S14>/Constant'
     */
    FOC_FCF_B->Sum2_ez = FOC_FCF_B->Sum_k - FOC_FCF_P.Constant_Value;

    /* Switch: '<S14>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum2_ez;
  } else {
    /* Switch: '<S14>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum_k;
  }

  /* End of Switch: '<S14>/Switch1' */

  /* Switch: '<S14>/Switch2' */
  if (FOC_FCF_B->Switch1_k > FOC_FCF_P.Switch2_Threshold_o) {
    /* Switch: '<S14>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Switch1_k;
  } else {
    /* Sum: '<S14>/Sum3' incorporates:
     *  Constant: '<S14>/Constant1'
     */
    FOC_FCF_B->Sum3_d = FOC_FCF_B->Switch1_k + FOC_FCF_P.Constant1_Value;

    /* Switch: '<S14>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Sum3_d;
  }

  /* End of Switch: '<S14>/Switch2' */

  /* Sum: '<S4>/Sum2' incorporates:
   *  Constant: '<S4>/FOC_6ph_AngleShift'
   */
  FOC_FCF_B->Sum2_p = FOC_FCF_B->Switch2 + FOC_FCF_P.FOC_6ph_AngleShift;

  /* MultiPortSwitch: '<S1>/SelectControlMode' */
  switch ((int32_T)FOC_FCF_B->ModeSwitch) {
   case 0:
    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S1>/Null'
     */
    for (i = 0; i < 6; i++) {
      FOC_FCF_B->SelectControlMode[i] = FOC_FCF_P.Null_Value[i];
    }
    break;

   case 1:
    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S1>/Null'
     */
    for (i = 0; i < 6; i++) {
      FOC_FCF_B->SelectControlMode[i] = FOC_FCF_P.Null_Value[i];
    }
    break;

   case 2:
    /* Gain: '<S28>/Gain' */
    FOC_FCF_B->Gain_fw = FOC_FCF_P.FOC_Uf_m * FOC_FCF_B->DiscreteTransferFcn;

    /* Signum: '<S28>/Sign' */
    tmp_0 = FOC_FCF_B->Gain_fw;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S28>/Sign' */
      FOC_FCF_B->Sign_p = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S28>/Sign' */
      FOC_FCF_B->Sign_p = -1.0F;
    } else {
      /* Signum: '<S28>/Sign' */
      FOC_FCF_B->Sign_p = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S28>/Sign' */

    /* Abs: '<S28>/Abs' */
    FOC_FCF_B->Abs_d = fabsf(FOC_FCF_B->Gain_fw);

    /* Saturate: '<S28>/Saturation1' */
    if (FOC_FCF_B->Abs_d > FOC_FCF_P.FOC_Uf_U_max) {
      /* Saturate: '<S28>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_max;
    } else if (FOC_FCF_B->Abs_d < FOC_FCF_P.FOC_Uf_U_min) {
      /* Saturate: '<S28>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_min;
    } else {
      /* Saturate: '<S28>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_B->Abs_d;
    }

    /* End of Saturate: '<S28>/Saturation1' */

    /* Product: '<S28>/Product' */
    FOC_FCF_B->Product_j = FOC_FCF_B->Saturation1 * FOC_FCF_B->Sign_p;

    /* Sum: '<S7>/Sum1' incorporates:
     *  Constant: '<S7>/FOC_6ph_AngleShift'
     */
    FOC_FCF_B->Sum1_n = FOC_FCF_B->Add + FOC_FCF_P.FOC_6ph_AngleShift;

    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S7>/Uf_Ud'
     */
    FOC_FCF_B->SelectControlMode[0] = FOC_FCF_P.FOC_Uf_Ud;
    FOC_FCF_B->SelectControlMode[1] = FOC_FCF_B->Product_j;
    FOC_FCF_B->SelectControlMode[2] = FOC_FCF_P.FOC_Uf_Ud;
    FOC_FCF_B->SelectControlMode[3] = FOC_FCF_B->Product_j;
    FOC_FCF_B->SelectControlMode[4] = FOC_FCF_B->Add;
    FOC_FCF_B->SelectControlMode[5] = FOC_FCF_B->Sum1_n;
    break;

   default:
    /* Switch: '<S24>/IntegEnaSwitch1' */
    if (FOC_FCF_B->LogicalOperator1) {
      /* Product: '<S24>/Product2' */
      tmp_0 = FOC_FCF_B->IntegDelay1_o[0] * FOC_FCF_B->Product1_k;
      FOC_FCF_B->Product2_b[0] = tmp_0;

      /* Sum: '<S24>/IntSum1' */
      tmp_0 += FOC_FCF_B->KPek1_l[0];
      FOC_FCF_B->IntSum1[0] = tmp_0;

      /* Switch: '<S24>/IntegEnaSwitch1' */
      FOC_FCF_B->IntegEnaSwitch1[0] = tmp_0;

      /* Product: '<S24>/Product2' */
      tmp_0 = FOC_FCF_B->IntegDelay1_o[1] * FOC_FCF_B->Product1_k;
      FOC_FCF_B->Product2_b[1] = tmp_0;

      /* Sum: '<S24>/IntSum1' */
      tmp_0 += FOC_FCF_B->KPek1_l[1];
      FOC_FCF_B->IntSum1[1] = tmp_0;

      /* Switch: '<S24>/IntegEnaSwitch1' */
      FOC_FCF_B->IntegEnaSwitch1[1] = tmp_0;
    } else {
      /* Switch: '<S24>/IntegEnaSwitch1' incorporates:
       *  Constant: '<S24>/Zero'
       */
      FOC_FCF_B->IntegEnaSwitch1[0] = FOC_FCF_P.Zero_Value_o;
      FOC_FCF_B->IntegEnaSwitch1[1] = FOC_FCF_P.Zero_Value_o;
    }

    /* End of Switch: '<S24>/IntegEnaSwitch1' */

    /* MultiPortSwitch: '<S1>/SelectControlMode' */
    FOC_FCF_B->SelectControlMode[0] = FOC_FCF_B->U_dq1_CC[0];
    FOC_FCF_B->SelectControlMode[2] = FOC_FCF_B->IntegEnaSwitch1[0];
    FOC_FCF_B->SelectControlMode[1] = FOC_FCF_B->U_dq1_CC[1];
    FOC_FCF_B->SelectControlMode[3] = FOC_FCF_B->IntegEnaSwitch1[1];
    FOC_FCF_B->SelectControlMode[4] = FOC_FCF_B->Switch2;
    FOC_FCF_B->SelectControlMode[5] = FOC_FCF_B->Sum2_p;
    break;
  }

  /* End of MultiPortSwitch: '<S1>/SelectControlMode' */

  /* Trigonometry: '<S35>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_n = sinf(FOC_FCF_B->SelectControlMode[4]);

  /* Trigonometry: '<S35>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_j = cosf(FOC_FCF_B->SelectControlMode[4]);

  /* Gain: '<S35>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[0] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S35>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[0] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S35>/Sum1' incorporates:
   *  Gain: '<S35>/Gain'
   *  Gain: '<S35>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[0] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S35>/Product' incorporates:
   *  Sum: '<S35>/Sum1'
   */
  I_phA_0 = Sum1_f;

  /* Gain: '<S35>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[1] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S35>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[1] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S35>/Sum1' incorporates:
   *  Gain: '<S35>/Gain'
   *  Gain: '<S35>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[1] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S35>/Product' incorporates:
   *  Sum: '<S35>/Sum1'
   */
  tmp_0 = Sum1_f;

  /* Gain: '<S35>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[2] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S35>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[2] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S35>/Sum1' incorporates:
   *  Gain: '<S35>/Gain'
   *  Gain: '<S35>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[2] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S35>/Product' incorporates:
   *  Sum: '<S35>/Sum1'
   */
  I_phA = Sum1_f;

  /* Gain: '<S35>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[3] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S35>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[3] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S35>/Sum1' incorporates:
   *  Gain: '<S35>/Gain'
   *  Gain: '<S35>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[3] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S35>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[0];
  Gain = FOC_FCF_B->SelectControlMode[1];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S35>/Product' */
  FOC_FCF_B->Product_c0[0] = I_phA_0;

  /* Product: '<S35>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_f * Gain;

  /* Product: '<S35>/Product' */
  FOC_FCF_B->Product_c0[1] = I_phA_0;

  /* Product: '<S33>/Product' incorporates:
   *  Constant: '<S33>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_d[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_c0[0];
  Gain = FOC_FCF_B->Product_c0[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    I_phA_0 = tmp[i_0] * TrafoMatrixuvwalphabeta;
    I_phA_0 += tmp[i_0 + 3] * Gain;

    /* Product: '<S33>/Product' */
    FOC_FCF_B->U_uvw1[i_0] = I_phA_0;
  }

  /* End of Product: '<S33>/Product' */

  /* Trigonometry: '<S36>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_j = sinf(FOC_FCF_B->SelectControlMode[5]);

  /* Trigonometry: '<S36>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_h = cosf(FOC_FCF_B->SelectControlMode[5]);

  /* Gain: '<S36>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_c[0] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S36>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[0] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S36>/Sum1' incorporates:
   *  Gain: '<S36>/Gain'
   *  Gain: '<S36>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[0] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S36>/Product' incorporates:
   *  Sum: '<S36>/Sum1'
   */
  I_phA_0 = Sum1_f;

  /* Gain: '<S36>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_c[1] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S36>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[1] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S36>/Sum1' incorporates:
   *  Gain: '<S36>/Gain'
   *  Gain: '<S36>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[1] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S36>/Product' incorporates:
   *  Sum: '<S36>/Sum1'
   */
  tmp_0 = Sum1_f;

  /* Gain: '<S36>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_c[2] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S36>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[2] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S36>/Sum1' incorporates:
   *  Gain: '<S36>/Gain'
   *  Gain: '<S36>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[2] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S36>/Product' incorporates:
   *  Sum: '<S36>/Sum1'
   */
  I_phA = Sum1_f;

  /* Gain: '<S36>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_c[3] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S36>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[3] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S36>/Sum1' incorporates:
   *  Gain: '<S36>/Gain'
   *  Gain: '<S36>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[3] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S36>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[2];
  Gain = FOC_FCF_B->SelectControlMode[3];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S36>/Product' */
  FOC_FCF_B->Product_f[0] = I_phA_0;

  /* Product: '<S36>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_f * Gain;

  /* Product: '<S36>/Product' */
  FOC_FCF_B->Product_f[1] = I_phA_0;

  /* Product: '<S34>/Product' incorporates:
   *  Constant: '<S34>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_g[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_f[0];
  Gain = FOC_FCF_B->Product_f[1];

  /* Switch: '<S1>/Switch1' incorporates:
   *  Constant: '<S1>/0: P_Udc 1: Udc_measured'
   */
  if (FOC_FCF_P.FOC_SELECT_U_DC_INPUT > FOC_FCF_P.Switch1_Threshold_m) {
    /* Switch: '<S1>/Switch1' */
    FOC_FCF_B->U_DC_fcf = FOC_FCF_U->U_DC;
  } else {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Udc1'
     */
    FOC_FCF_B->U_DC_fcf = FOC_FCF_P.FOC_MANUAL_U_DC;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Outputs for Atomic SubSystem: '<S8>/NormalizedVoltage' */
  /* Gain: '<S31>/U_DC//2' */
  FOC_FCF_B->U_DC2 = FOC_FCF_P.U_DC2_Gain_p * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S31>/AvoidDivBy0' incorporates:
   *  Constant: '<S31>/Constant2'
   */
  tmp_0 = fmaxf(FOC_FCF_P.Constant2_Value_g, FOC_FCF_B->U_DC2);

  /* MinMax: '<S31>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0 = tmp_0;
  for (i = 0; i < 3; i++) {
    /* Product: '<S34>/Product' */
    tmp_0 = tmp[i] * TrafoMatrixuvwalphabeta;
    tmp_0 += tmp[i + 3] * Gain;

    /* Product: '<S34>/Product' */
    FOC_FCF_B->Product_f3[i] = tmp_0;

    /* Product: '<S31>/DutyCycle_normalized' */
    FOC_FCF_B->DutyCycle_normed[i] = FOC_FCF_B->U_uvw1[i] /
      FOC_FCF_B->AvoidDivBy0;
    FOC_FCF_B->DutyCycle_normed[i + 3] = tmp_0 / FOC_FCF_B->AvoidDivBy0;
  }

  /* End of Outputs for SubSystem: '<S8>/NormalizedVoltage' */

  /* Outputs for Atomic SubSystem: '<S8>/Super_Sinus_Modulation' */
  /* MinMax: '<S32>/MinMax2' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[0];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[1]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S32>/MinMax2' */
  FOC_FCF_B->MinMax2 = tmp_0;

  /* MinMax: '<S32>/MinMax3' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[0];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[1]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S32>/MinMax3' */
  FOC_FCF_B->MinMax3 = tmp_0;

  /* Sum: '<S32>/Sum1' */
  FOC_FCF_B->Sum1_o = FOC_FCF_B->MinMax2 + FOC_FCF_B->MinMax3;

  /* Gain: '<S32>/Factor' */
  FOC_FCF_B->Factor = FOC_FCF_P.Factor_Gain * FOC_FCF_B->Sum1_o;

  /* Sum: '<S32>/DutyCycle_SuperSinus_1' */
  FOC_FCF_B->DutyCycle_SuperSinus_1[0] = FOC_FCF_B->DutyCycle_normed[0] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[1] = FOC_FCF_B->DutyCycle_normed[1] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[2] = FOC_FCF_B->DutyCycle_normed[2] -
    FOC_FCF_B->Factor;

  /* MinMax: '<S32>/MinMax1' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[3];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[4]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S32>/MinMax1' */
  FOC_FCF_B->MinMax1 = tmp_0;

  /* MinMax: '<S32>/MinMax4' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[3];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[4]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S32>/MinMax4' */
  FOC_FCF_B->MinMax4 = tmp_0;

  /* Sum: '<S32>/Sum2' */
  FOC_FCF_B->Sum2_i = FOC_FCF_B->MinMax1 + FOC_FCF_B->MinMax4;

  /* Gain: '<S32>/Factor1' */
  FOC_FCF_B->Factor1 = FOC_FCF_P.Factor1_Gain * FOC_FCF_B->Sum2_i;

  /* Sum: '<S32>/DutyCycle_SuperSinus_2' */
  FOC_FCF_B->DutyCycle_SuperSinus_2[0] = FOC_FCF_B->DutyCycle_normed[3] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[1] = FOC_FCF_B->DutyCycle_normed[4] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[2] = FOC_FCF_B->DutyCycle_normed[5] -
    FOC_FCF_B->Factor1;

  /* End of Outputs for SubSystem: '<S8>/Super_Sinus_Modulation' */

  /* MultiPortSwitch: '<S8>/SelectModulation' incorporates:
   *  Constant: '<S8>/Enable_SuperSinMod'
   */
  if (FOC_FCF_P.FOC_SELECT_Modulation == 0) {
    /* MultiPortSwitch: '<S8>/SelectModulation' */
    for (i = 0; i < 6; i++) {
      FOC_FCF_B->SelMod_DutyCycles[i] = FOC_FCF_B->DutyCycle_normed[i];
    }
  } else {
    /* MultiPortSwitch: '<S8>/SelectModulation' */
    FOC_FCF_B->SelMod_DutyCycles[0] = FOC_FCF_B->DutyCycle_SuperSinus_1[0];
    FOC_FCF_B->SelMod_DutyCycles[3] = FOC_FCF_B->DutyCycle_SuperSinus_2[0];
    FOC_FCF_B->SelMod_DutyCycles[1] = FOC_FCF_B->DutyCycle_SuperSinus_1[1];
    FOC_FCF_B->SelMod_DutyCycles[4] = FOC_FCF_B->DutyCycle_SuperSinus_2[1];
    FOC_FCF_B->SelMod_DutyCycles[2] = FOC_FCF_B->DutyCycle_SuperSinus_1[2];
    FOC_FCF_B->SelMod_DutyCycles[5] = FOC_FCF_B->DutyCycle_SuperSinus_2[2];
  }

  /* End of MultiPortSwitch: '<S8>/SelectModulation' */

  /* Switch: '<S2>/ASC_Switch' */
  if (FOC_FCF_B->LogicalOperator1) {
    for (i = 0; i < 6; i++) {
      /* Bias: '<S8>/Scale [0..2]' */
      tmp_0 = FOC_FCF_B->SelMod_DutyCycles[i] + FOC_FCF_P.Scale02_Bias;
      FOC_FCF_B->Scale02_p[i] = tmp_0;

      /* Gain: '<S8>/Scale  [0..1]' */
      tmp_0 *= FOC_FCF_P.Scale01_Gain;
      FOC_FCF_B->Scale01_b[i] = tmp_0;

      /* Saturate: '<S8>/Limit [0..1]' */
      if (tmp_0 > FOC_FCF_P.Limit01_UpperSat) {
        /* Saturate: '<S8>/Limit [0..1]' */
        tmp_0 = FOC_FCF_P.Limit01_UpperSat;
      } else if (tmp_0 < FOC_FCF_P.Limit01_LowerSat) {
        /* Saturate: '<S8>/Limit [0..1]' */
        tmp_0 = FOC_FCF_P.Limit01_LowerSat;
      }

      /* End of Saturate: '<S8>/Limit [0..1]' */

      /* Saturate: '<S8>/Limit [0..1]' */
      FOC_FCF_B->Limit01_e[i] = tmp_0;

      /* Outport: '<Root>/DutyCycles [0..1]' */
      FOC_FCF_Y->DutyCycles01[i] = tmp_0;
    }
  } else {
    /* MultiPortSwitch: '<S2>/ASC Switch' incorporates:
     *  Constant: '<S2>/FOC_AKS_Mode'
     */
    switch ((int32_T)FOC_FCF_P.FOC_ASC_Mode) {
     case 1:
      /* MultiPortSwitch: '<S2>/ASC Switch' incorporates:
       *  Constant: '<S2>/ASC_LS'
       */
      for (i = 0; i < 6; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_LS_Value[i];
      }
      break;

     case 2:
      /* MultiPortSwitch: '<S2>/ASC Switch' incorporates:
       *  Constant: '<S2>/ASC_HS'
       */
      for (i = 0; i < 6; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_HS_Value[i];
      }
      break;

     default:
      /* MultiPortSwitch: '<S2>/ASC Switch' incorporates:
       *  Constant: '<S2>/ASC_LSHS'
       */
      for (i = 0; i < 6; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_LSHS_Value[i];
      }
      break;
    }

    /* End of MultiPortSwitch: '<S2>/ASC Switch' */

    /* Outport: '<Root>/DutyCycles [0..1]' */
    for (i = 0; i < 6; i++) {
      FOC_FCF_Y->DutyCycles01[i] = FOC_FCF_B->ASCSwitch[i];
    }
  }

  /* End of Switch: '<S2>/ASC_Switch' */

  /* Sum: '<S9>/Deviation' */
  FOC_FCF_B->Deviation = FOC_FCF_B->Sum3 - FOC_FCF_B->phi_el_observer;

  /* Product: '<S9>/Product2' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   */
  FOC_FCF_B->Product2 = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_D * FOC_FCF_B->Deviation;

  /* Gain: '<S9>/Gain' */
  FOC_FCF_B->Gain_g = FOC_FCF_P.Gain_Gain_k * FOC_FCF_B->Product2;

  /* Gain: '<S9>/Gain4' */
  FOC_FCF_B->winkelimpuls = FOC_FCF_P.FOC_OmegaObs3 * FOC_FCF_B->Deviation;

  /* Sum: '<S9>/Sum1' */
  FOC_FCF_B->Sum1_g4 = FOC_FCF_B->Gain_g + FOC_FCF_B->w_el;

  /* Product: '<S9>/Product' incorporates:
   *  Constant: '<S9>/FOC_T_fast'
   */
  FOC_FCF_B->Product_o = FOC_FCF_B->Sum1_g4 * FOC_FCF_P.FOC_T_fast_Value_df;

  /* Product: '<S9>/Product1' incorporates:
   *  Constant: '<S9>/Constant'
   */
  FOC_FCF_B->Product1_b = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_w0 * FOC_FCF_B->Deviation;

  /* UnitDelay: '<S13>/Unit Delay1' */
  FOC_FCF_B->UnitDelay1 = FOC_FCF_DW->UnitDelay1_DSTATE_i;

  /* Sum: '<S9>/Sum2' */
  FOC_FCF_B->Sum2_m = FOC_FCF_B->Product1_b + FOC_FCF_B->UnitDelay1;

  /* Sum: '<S9>/Sum6' */
  FOC_FCF_B->Sum6 = FOC_FCF_B->Product_o + FOC_FCF_B->phi_el_observer;

  /* Product: '<S12>/Product' incorporates:
   *  Constant: '<S12>/FOC_T_fast'
   */
  FOC_FCF_B->Product_n = FOC_FCF_B->Sum2_m * FOC_FCF_P.FOC_T_fast_Value_c;

  /* Sum: '<S12>/Sum2' */
  FOC_FCF_B->Sum2_e = FOC_FCF_B->Product_n + FOC_FCF_B->w_el;

  /* Product: '<S13>/Product' incorporates:
   *  Constant: '<S13>/FOC_T_fast'
   */
  FOC_FCF_B->Product_cd = FOC_FCF_B->winkelimpuls * FOC_FCF_P.FOC_T_fast_Value_k;

  /* Sum: '<S13>/Sum2' */
  FOC_FCF_B->Sum2_j = FOC_FCF_B->Product_cd + FOC_FCF_B->UnitDelay1;

  /* Outputs for Atomic SubSystem: '<S8>/Calc_Modulation_Index' */
  /* Gain: '<S30>/U_DC//2' */
  FOC_FCF_B->U_DC2_l = FOC_FCF_P.U_DC2_Gain * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S30>/AvoidDivBy0' incorporates:
   *  Constant: '<S30>/Constant2'
   */
  tmp_0 = fmaxf(FOC_FCF_P.Constant2_Value_d, FOC_FCF_B->U_DC2_l);

  /* MinMax: '<S30>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0_f = tmp_0;

  /* Math: '<S30>/Square' */
  tmp_0 = FOC_FCF_B->Product_c0[0];

  /* Math: '<S30>/Square' */
  FOC_FCF_B->Square[0] = tmp_0 * tmp_0;

  /* Math: '<S30>/Square' */
  tmp_0 = FOC_FCF_B->Product_c0[1];

  /* Math: '<S30>/Square' */
  FOC_FCF_B->Square[1] = tmp_0 * tmp_0;

  /* Sum: '<S30>/Sum' */
  tmp_0 = FOC_FCF_B->Square[0];

  /* Math: '<S30>/Square1' */
  I_phA = FOC_FCF_B->Product_f[0];

  /* Math: '<S30>/Square1' */
  FOC_FCF_B->Square1[0] = I_phA * I_phA;

  /* Sum: '<S30>/Sum' */
  tmp_0 += FOC_FCF_B->Square[1];

  /* Math: '<S30>/Square1' */
  I_phA = FOC_FCF_B->Product_f[1];

  /* Math: '<S30>/Square1' */
  FOC_FCF_B->Square1[1] = I_phA * I_phA;

  /* Sum: '<S30>/Sum' */
  FOC_FCF_B->Sum_kr = tmp_0;

  /* Sqrt: '<S30>/Sqrt' */
  FOC_FCF_B->Sqrt = sqrtf(FOC_FCF_B->Sum_kr);

  /* Sum: '<S30>/Sum1' */
  tmp_0 = FOC_FCF_B->Square1[0];
  tmp_0 += FOC_FCF_B->Square1[1];

  /* Sum: '<S30>/Sum1' */
  FOC_FCF_B->Sum1_a = tmp_0;

  /* Sqrt: '<S30>/Sqrt1' */
  FOC_FCF_B->Sqrt1 = sqrtf(FOC_FCF_B->Sum1_a);

  /* Product: '<S30>/Divide3' */
  FOC_FCF_B->ModInd[0] = FOC_FCF_B->Sqrt / FOC_FCF_B->AvoidDivBy0_f;
  FOC_FCF_B->ModInd[1] = FOC_FCF_B->Sqrt1 / FOC_FCF_B->AvoidDivBy0_f;

  /* End of Outputs for SubSystem: '<S8>/Calc_Modulation_Index' */

  /* Switch: '<S20>/IntegStopSwitch2' incorporates:
   *  Switch: '<S24>/IntegStopSwitch2'
   */
  if (FOC_FCF_B->LogicalOperator1) {
    /* RelationalOperator: '<S19>/AntiWindupLE' incorporates:
     *  Constant: '<S19>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE_l = (FOC_FCF_B->ModInd[0] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S20>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1[0];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S20>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S20>/IntegStopSwitch3' incorporates:
       *  Constant: '<S20>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value[0];
    }

    /* Switch: '<S20>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[0] = I_phA;

    /* Sum: '<S20>/IntSum2' */
    FOC_FCF_B->IntSum2_j[0] = FOC_FCF_B->KPek1[0] + I_phA;

    /* Gain: '<S20>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S19>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[0] = FOC_FCF_B->IdqErr[0] * tmp_0;

    /* Switch: '<S20>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1[1];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S20>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S20>/IntegStopSwitch3' incorporates:
       *  Constant: '<S20>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value[1];
    }

    /* Switch: '<S20>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[1] = I_phA;

    /* Sum: '<S20>/IntSum2' */
    FOC_FCF_B->IntSum2_j[1] = FOC_FCF_B->KPek1[1] + I_phA;

    /* Gain: '<S20>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S19>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[1] = FOC_FCF_B->IdqErr[1] * tmp_0;

    /* RelationalOperator: '<S22>/Compare' incorporates:
     *  Constant: '<S22>/Constant'
     */
    FOC_FCF_B->Compare_o = (uint8_T)(FOC_FCF_B->antiWindupProd_o[1] <
      FOC_FCF_P.AntiWindupGT_q_const);

    /* Logic: '<S19>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q_o = (FOC_FCF_B->AntiWindupLE_l ||
      (FOC_FCF_B->Compare_o != 0));

    /* RelationalOperator: '<S21>/Compare' incorporates:
     *  Constant: '<S21>/Constant'
     */
    FOC_FCF_B->Compare_f = (uint8_T)(FOC_FCF_B->antiWindupProd_o[0] <
      FOC_FCF_P.AntiWindupGT_d_const);

    /* Logic: '<S19>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d_e = ((FOC_FCF_B->Compare_f != 0) ||
      FOC_FCF_B->AntiWindupLE_l);

    /* Switch: '<S20>/IntegStopSwitch1' */
    tmp_idx_0 = FOC_FCF_B->AntiWindupOR_d_e;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q_o;
    if (tmp_idx_0) {
      tmp_0 = FOC_FCF_B->IntSum2_j[0];

      /* Switch: '<S20>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_c[0];

      /* Switch: '<S20>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = tmp_0;
    }

    /* Switch: '<S20>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[0] = tmp_0;

    /* Switch: '<S20>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2_j[1];

      /* Switch: '<S20>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_c[1];

      /* Switch: '<S20>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = tmp_0;
    }

    /* Switch: '<S20>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[1] = tmp_0;

    /* RelationalOperator: '<S23>/AntiWindupLE' incorporates:
     *  Constant: '<S23>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE = (FOC_FCF_B->ModInd[1] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S24>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[0];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S24>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S24>/IntegStopSwitch3' incorporates:
       *  Constant: '<S24>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_l[0];
    }

    /* Switch: '<S24>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[0] = I_phA;

    /* Sum: '<S24>/IntSum2' */
    FOC_FCF_B->IntSum2[0] = FOC_FCF_B->KPek1_l[0] + I_phA;

    /* Gain: '<S24>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S23>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[0] = FOC_FCF_B->IdqErr_l[0] * tmp_0;

    /* Switch: '<S24>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[1];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S24>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S24>/IntegStopSwitch3' incorporates:
       *  Constant: '<S24>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_l[1];
    }

    /* Switch: '<S24>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[1] = I_phA;

    /* Sum: '<S24>/IntSum2' */
    FOC_FCF_B->IntSum2[1] = FOC_FCF_B->KPek1_l[1] + I_phA;

    /* Gain: '<S24>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S23>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[1] = FOC_FCF_B->IdqErr_l[1] * tmp_0;

    /* RelationalOperator: '<S26>/Compare' incorporates:
     *  Constant: '<S26>/Constant'
     */
    FOC_FCF_B->Compare = (uint8_T)(FOC_FCF_B->antiWindupProd[1] <
      FOC_FCF_P.AntiWindupGT_q_const_h);

    /* Logic: '<S23>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q = (FOC_FCF_B->AntiWindupLE || (FOC_FCF_B->Compare
      != 0));

    /* RelationalOperator: '<S25>/Compare' incorporates:
     *  Constant: '<S25>/Constant'
     */
    FOC_FCF_B->Compare_i = (uint8_T)(FOC_FCF_B->antiWindupProd[0] <
      FOC_FCF_P.AntiWindupGT_d_const_n);

    /* Logic: '<S23>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d = ((FOC_FCF_B->Compare_i != 0) ||
      FOC_FCF_B->AntiWindupLE);

    /* Switch: '<S24>/IntegStopSwitch1' */
    tmp_idx_0 = FOC_FCF_B->AntiWindupOR_d;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q;
    if (tmp_idx_0) {
      tmp_0 = FOC_FCF_B->IntSum2[0];

      /* Switch: '<S24>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp[0];

      /* Switch: '<S24>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = tmp_0;
    }

    /* Switch: '<S24>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[0] = tmp_0;

    /* Switch: '<S24>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2[1];

      /* Switch: '<S24>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp[1];

      /* Switch: '<S24>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = tmp_0;
    }

    /* Switch: '<S24>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[1] = tmp_0;
  } else {
    /* Switch: '<S20>/IntegStopSwitch2' incorporates:
     *  Constant: '<S20>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2[0] = FOC_FCF_P.Zero1_Value[0];
    FOC_FCF_B->IntegStopSwitch2[1] = FOC_FCF_P.Zero1_Value[1];

    /* Switch: '<S24>/IntegStopSwitch2' incorporates:
     *  Constant: '<S24>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2_o[0] = FOC_FCF_P.Zero1_Value_l[0];
    FOC_FCF_B->IntegStopSwitch2_o[1] = FOC_FCF_P.Zero1_Value_l[1];
  }

  /* End of Switch: '<S20>/IntegStopSwitch2' */

  /* DiscreteFir: '<S17>/Discrete FIR Filter 20th order' */
  i = 1;
  tmp_0 = FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0] *
    FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[0];
  for (i_0 = FOC_FCF_DW->DiscreteFIRFilter20thorder_circ; i_0 < 19; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i_0] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[i];
    tmp_0 += I_phA;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_FCF_DW->DiscreteFIRFilter20thorder_circ; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i_0] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[i];
    tmp_0 += I_phA;
    i++;
  }

  FOC_FCF_B->I_dq1_Act_filt[0] = tmp_0;
  i = 1;
  tmp_0 = FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[0] *
    FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1];
  for (i_0 = FOC_FCF_DW->DiscreteFIRFilter20thorder_circ; i_0 < 19; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i_0 + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[i];
    tmp_0 += I_phA;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_FCF_DW->DiscreteFIRFilter20thorder_circ; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i_0 + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[i];
    tmp_0 += I_phA;
    i++;
  }

  FOC_FCF_B->I_dq1_Act_filt[1] = tmp_0;

  /* End of DiscreteFir: '<S17>/Discrete FIR Filter 20th order' */

  /* DiscreteFir: '<S18>/Discrete FIR Filter 20th order' */
  i = 1;
  tmp_0 = FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0] *
    FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[0];
  for (i_0 = FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m; i_0 < 19; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i_0] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[i];
    tmp_0 += I_phA;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i_0] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[i];
    tmp_0 += I_phA;
    i++;
  }

  FOC_FCF_B->DiscreteFIRFilter20thorder[0] = tmp_0;
  i = 1;
  tmp_0 = FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[0] *
    FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];
  for (i_0 = FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m; i_0 < 19; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i_0 + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[i];
    tmp_0 += I_phA;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i_0 + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[i];
    tmp_0 += I_phA;
    i++;
  }

  FOC_FCF_B->DiscreteFIRFilter20thorder[1] = tmp_0;

  /* End of DiscreteFir: '<S18>/Discrete FIR Filter 20th order' */

  /* Abs: '<S6>/Abs' */
  FOC_FCF_B->Abs = fabsf(FOC_FCF_B->Add_m);

  /* Switch: '<S6>/Switch' */
  if (FOC_FCF_B->Abs >= FOC_FCF_P.Switch_Threshold) {
    /* Signum: '<S6>/Sign' */
    tmp_0 = FOC_FCF_B->Product_e;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S6>/Sign' */
      FOC_FCF_B->Sign_n = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S6>/Sign' */
      FOC_FCF_B->Sign_n = -1.0F;
    } else {
      /* Signum: '<S6>/Sign' */
      FOC_FCF_B->Sign_n = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S6>/Sign' */

    /* Gain: '<S6>/Gain1' */
    FOC_FCF_B->Gain1_h = FOC_FCF_P.Gain1_Gain * FOC_FCF_B->Sign_n;

    /* Switch: '<S6>/Switch' */
    FOC_FCF_B->Switch_l = FOC_FCF_B->Gain1_h;
  } else {
    /* Switch: '<S6>/Switch' incorporates:
     *  Constant: '<S6>/Constant1'
     */
    FOC_FCF_B->Switch_l = FOC_FCF_P.Constant1_Value_k;
  }

  /* End of Switch: '<S6>/Switch' */

  /* Sum: '<S6>/Add1' */
  FOC_FCF_B->Add1 = FOC_FCF_B->Add_m - FOC_FCF_B->Switch_l;

  /* Abs: '<S27>/Abs' */
  FOC_FCF_B->Abs_f = fabsf(FOC_FCF_B->Add);

  /* Switch: '<S27>/Switch' */
  if (FOC_FCF_B->Abs_f >= FOC_FCF_P.Switch_Threshold_c) {
    /* Signum: '<S27>/Sign' */
    tmp_0 = FOC_FCF_B->Product;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S27>/Sign' */
      FOC_FCF_B->Sign = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S27>/Sign' */
      FOC_FCF_B->Sign = -1.0F;
    } else {
      /* Signum: '<S27>/Sign' */
      FOC_FCF_B->Sign = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S27>/Sign' */

    /* Gain: '<S27>/Gain1' */
    FOC_FCF_B->Gain1_o = FOC_FCF_P.Gain1_Gain_a * FOC_FCF_B->Sign;

    /* Switch: '<S27>/Switch' */
    FOC_FCF_B->Switch_n = FOC_FCF_B->Gain1_o;
  } else {
    /* Switch: '<S27>/Switch' incorporates:
     *  Constant: '<S27>/Constant1'
     */
    FOC_FCF_B->Switch_n = FOC_FCF_P.Constant1_Value_e;
  }

  /* End of Switch: '<S27>/Switch' */

  /* Sum: '<S27>/Add1' */
  FOC_FCF_B->Add1_c = FOC_FCF_B->Add - FOC_FCF_B->Switch_n;
  for (i = 0; i < 6; i++) {
    /* Bias: '<S29>/Scale [0..2]' */
    tmp_0 = FOC_FCF_B->SelMod_DutyCycles[i] + FOC_FCF_P.Scale02_Bias_n;
    FOC_FCF_B->Scale02[i] = tmp_0;

    /* Gain: '<S29>/Scale  [0..1]' */
    tmp_0 *= FOC_FCF_P.Scale01_Gain_p;
    FOC_FCF_B->Scale01[i] = tmp_0;

    /* Saturate: '<S29>/Limit [0..1]' */
    if (tmp_0 > FOC_FCF_P.Limit01_UpperSat_d) {
      tmp_0 = FOC_FCF_P.Limit01_UpperSat_d;
    } else if (tmp_0 < FOC_FCF_P.Limit01_LowerSat_f) {
      tmp_0 = FOC_FCF_P.Limit01_LowerSat_f;
    }

    /* Saturate: '<S29>/Limit [0..1]' */
    FOC_FCF_B->Limit01[i] = tmp_0;
  }

  /* Gain: '<S8>/Gain' */
  FOC_FCF_B->U_d1 = FOC_FCF_P.Gain_Gain_j * FOC_FCF_B->SelectControlMode[0];

  /* Gain: '<S8>/Gain1' */
  FOC_FCF_B->U_q1 = FOC_FCF_P.Gain1_Gain_e * FOC_FCF_B->SelectControlMode[1];

  /* Gain: '<S8>/Gain2' */
  FOC_FCF_B->U_alpha1 = FOC_FCF_P.Gain2_Gain * FOC_FCF_B->Product_c0[0];

  /* Gain: '<S8>/Gain3' */
  FOC_FCF_B->U_beta1 = FOC_FCF_P.Gain3_Gain * FOC_FCF_B->Product_c0[1];

  /* UnitDelay: '<S1>/FCF_Cnt' */
  FOC_FCF_B->FCF_Cnt = FOC_FCF_DW->FCF_Cnt_DSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Counter_Start'
   */
  FOC_FCF_B->Sum_o = FOC_FCF_P.Counter_Start_Value + FOC_FCF_B->FCF_Cnt;

  /* Update for DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
  tmp_0 = FOC_FCF_B->f_2_w_el;
  tmp_0 -= FOC_FCF_P.DiscreteTransferFcn_DenCoef[1] *
    FOC_FCF_DW->DiscreteTransferFcn_states;
  tmp_0 /= FOC_FCF_P.DiscreteTransferFcn_DenCoef[0];
  FOC_FCF_DW->DiscreteTransferFcn_states = tmp_0;

  /* Update for UnitDelay: '<S27>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_B->Add1_c;

  /* Update for UnitDelay: '<S12>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_B->Sum2_e;

  /* Update for UnitDelay: '<S11>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_B->Sum3;

  /* Update for UnitDelay: '<S9>/Unit Delay3' */
  FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_B->Sum6;

  /* Update for UnitDelay: '<S6>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_B->Add1;

  /* Update for UnitDelay: '<S20>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_B->IntegStopSwitch2[0];

  /* Update for UnitDelay: '<S24>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[0] = FOC_FCF_B->IntegStopSwitch2_o[0];

  /* Update for UnitDelay: '<S20>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_B->IntegStopSwitch2[1];

  /* Update for UnitDelay: '<S24>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[1] = FOC_FCF_B->IntegStopSwitch2_o[1];

  /* Update for UnitDelay: '<S13>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_B->Sum2_j;

  /* Update for DiscreteFir: '<S17>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_circ--;
  if (FOC_FCF_DW->DiscreteFIRFilter20thorder_circ < 0) {
    FOC_FCF_DW->DiscreteFIRFilter20thorder_circ = 18;
  }

  /* Update circular buffer */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_stat
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_circ] =
    FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0];
  FOC_FCF_DW->DiscreteFIRFilter20thorder_stat
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_circ + 19] =
    FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1];

  /* End of Update for DiscreteFir: '<S17>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S18>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m--;
  if (FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m < 0) {
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m = 18;
  }

  /* Update for UnitDelay: '<S1>/FCF_Cnt' */
  /* Update circular buffer */
  FOC_FCF_DW->FCF_Cnt_DSTATE = FOC_FCF_B->Sum_o;

  /* Update for DiscreteFir: '<S18>/Discrete FIR Filter 20th order' */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */

  /* Outport: '<Root>/I_dq_Act [A]' */
  FOC_FCF_Y->I_dq_ActA[0] = FOC_FCF_B->I_dq1_Act_filt[0];
  FOC_FCF_Y->I_dq_ActA[2] = FOC_FCF_B->DiscreteFIRFilter20thorder[0];

  /* Outport: '<Root>/ModInd' */
  FOC_FCF_Y->ModInd[0] = FOC_FCF_B->ModInd[0];

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Update for DiscreteFir: '<S18>/Discrete FIR Filter 20th order' */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m + 19] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */

  /* Outport: '<Root>/I_dq_Act [A]' */
  FOC_FCF_Y->I_dq_ActA[1] = FOC_FCF_B->I_dq1_Act_filt[1];
  FOC_FCF_Y->I_dq_ActA[3] = FOC_FCF_B->DiscreteFIRFilter20thorder[1];

  /* Outport: '<Root>/ModInd' */
  FOC_FCF_Y->ModInd[1] = FOC_FCF_B->ModInd[1];

  /* Outport: '<Root>/w_el [rad//s]' */
  FOC_FCF_Y->w_elrads = FOC_FCF_B->w_el;

  /* Outport: '<Root>/FOC_Error' incorporates:
   *  Constant: '<S1>/Constant'
   */
  FOC_FCF_Y->FOC_Error = FOC_FCF_P.Constant_Value_e2;
}

/* Model initialize function */
void FOC_FCF_initialize(RT_MODEL_FOC_FCF_T *const FOC_FCF_M)
{
  DW_FOC_FCF_T *FOC_FCF_DW = FOC_FCF_M->dwork;
  B_FOC_FCF_T *FOC_FCF_B = FOC_FCF_M->blockIO;
  ExtU_FOC_FCF_T *FOC_FCF_U = (ExtU_FOC_FCF_T *) FOC_FCF_M->inputs;
  ExtY_FOC_FCF_T *FOC_FCF_Y = (ExtY_FOC_FCF_T *) FOC_FCF_M->outputs;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) FOC_FCF_B), 0,
                sizeof(B_FOC_FCF_T));

  /* states (dwork) */
  (void) memset((void *)FOC_FCF_DW, 0,
                sizeof(DW_FOC_FCF_T));

  /* external inputs */
  (void)memset(FOC_FCF_U, 0, sizeof(ExtU_FOC_FCF_T));

  /* external outputs */
  (void)memset(FOC_FCF_Y, 0, sizeof(ExtY_FOC_FCF_T));

  {
    int32_T i;

    /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_FCF' */
    /* InitializeConditions for DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
    FOC_FCF_DW->DiscreteTransferFcn_states =
      FOC_FCF_P.DiscreteTransferFcn_InitialStat;

    /* InitializeConditions for UnitDelay: '<S27>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_P.UnitDelay_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S12>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_P.FOC_AngleObs_w_InitVal;

    /* InitializeConditions for UnitDelay: '<S11>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_P.UnitDelay_InitialCondition_b;

    /* InitializeConditions for UnitDelay: '<S9>/Unit Delay3' */
    FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_P.UnitDelay3_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S6>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_P.UnitDelay_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S20>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S24>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[0] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S20>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S24>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[1] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S13>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_P.UnitDelay1_InitialCondition;

    /* InitializeConditions for DiscreteFir: '<S17>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_circ = 0;

    /* InitializeConditions for DiscreteFir: '<S18>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m = 0;
    for (i = 0; i < 38; i++) {
      /* InitializeConditions for DiscreteFir: '<S17>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_Init;

      /* InitializeConditions for DiscreteFir: '<S18>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_In_k;
    }

    /* InitializeConditions for UnitDelay: '<S1>/FCF_Cnt' */
    FOC_FCF_DW->FCF_Cnt_DSTATE = FOC_FCF_P.FCF_Cnt_InitialCondition;

    /* End of SystemInitialize for SubSystem: '<Root>/FOC_FCF' */
  }
}

/* Model terminate function */
void FOC_FCF_terminate(RT_MODEL_FOC_FCF_T *const FOC_FCF_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(FOC_FCF_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
