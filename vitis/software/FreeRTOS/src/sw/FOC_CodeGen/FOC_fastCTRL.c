/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_fastCTRL.c
 *
 * Code generated for Simulink model 'FOC_fastCTRL'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Oct  9 23:28:17 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_fastCTRL.h"
#include "rtwtypes.h"
#include "FOC_fastCTRL_private.h"
#include <math.h>
#include "rt_nonfinite.h"
#include <string.h>
#include "rt_defines.h"

/* Exported block signals */
real_T Phi_Observer;                   /* '<S26>/Sum7' */
real_T FOC_U_DC;                       /* '<S1>/Switch1' */
real_T FOC_AngleEst_w_el;              /* '<S3>/Gain2' */
real_T FOC_AngleEst_Psi_PM_alpha;      /* '<S3>/Gain3' */
real_T FOC_AngleEst_Psi_PM_beta;       /* '<S3>/Gain4' */
real_T w_el;                           /* '<S5>/dummy_gain' */
real_T Phi_el_I_Transformation;        /* '<S5>/dummy_gain1' */
real_T Phi_el_U_Transformation;        /* '<S5>/dummy_gain2' */
real_T Phi_Measured_Raw;               /* '<S5>/dummy_gain3' */
real_T Phi_est_error_I_Trafo;          /* '<S5>/dummy_gain4' */
real_T Phi_est;                        /* '<S5>/dummy_gain5' */
real_T Phi_AngleEst_AutoSwitch;        /* '<S5>/dummy_gain6' */
real_T Phi_est_error;                  /* '<S5>/dummy_gain7' */
real_T FCF_Cnt;                        /* '<S1>/FCF_Cnt' */
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u1 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u0 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(tmp_0, tmp);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void FOC_fastCTRL_step(RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_M)
{
  B_FOC_fastCTRL_T *FOC_fastCTRL_B = FOC_fastCTRL_M->blockIO;
  DW_FOC_fastCTRL_T *FOC_fastCTRL_DW = FOC_fastCTRL_M->dwork;
  ExtU_FOC_fastCTRL_T *FOC_fastCTRL_U = (ExtU_FOC_fastCTRL_T *)
    FOC_fastCTRL_M->inputs;
  ExtY_FOC_fastCTRL_T *FOC_fastCTRL_Y = (ExtY_FOC_fastCTRL_T *)
    FOC_fastCTRL_M->outputs;
  real_T tmp[6];
  real_T maxV;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_2;
  real_T tmp_3;
  real_T u;
  int32_T i;
  int32_T i_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_fastCTRL' */
  /* MultiPortSwitch: '<S1>/ModeSwitch' incorporates:
   *  Constant: '<S1>/FOC_SELECT_Mode_Intern'
   */
  if ((int32_T)FOC_fastCTRL_P.FOC_SELECT_Mode_Intern == 0) {
    /* MultiPortSwitch: '<S1>/ModeSwitch' incorporates:
     *  Inport: '<Root>/FOC_Mode'
     */
    FOC_fastCTRL_B->ModeSwitch = FOC_fastCTRL_U->FOC_Mode;
  } else {
    /* MultiPortSwitch: '<S1>/ModeSwitch' incorporates:
     *  Constant: '<S1>/FOC_Mode_Intern'
     */
    FOC_fastCTRL_B->ModeSwitch = FOC_fastCTRL_P.FOC_Mode_Intern;
  }

  /* End of MultiPortSwitch: '<S1>/ModeSwitch' */

  /* DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
  maxV = FOC_fastCTRL_P.DiscreteTransferFcn_NumCoef *
    FOC_fastCTRL_DW->DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
  FOC_fastCTRL_B->DiscreteTransferFcn = maxV;

  /* Gain: '<S7>/f_2_w_el' incorporates:
   *  Constant: '<S7>/Uf_w_el'
   */
  FOC_fastCTRL_B->f_2_w_el = FOC_fastCTRL_P.f_2_w_el_Gain *
    FOC_fastCTRL_P.FOC_Uf_f_el;

  /* Product: '<S48>/Product' incorporates:
   *  Constant: '<S48>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S48>/Product' */
  FOC_fastCTRL_B->Product = FOC_fastCTRL_B->f_2_w_el * maxV;

  /* UnitDelay: '<S48>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay = FOC_fastCTRL_DW->UnitDelay_DSTATE;

  /* Sum: '<S48>/Add' */
  FOC_fastCTRL_B->Add = FOC_fastCTRL_B->Product + FOC_fastCTRL_B->UnitDelay;
  for (i = 0; i < 2; i++) {
    /* Outport: '<Root>/I_dq_Ref_out [A]' incorporates:
     *  Inport: '<Root>/I_dq_Ref [A]'
     *  SignalConversion generated from: '<S1>/I_dq_Ref [A]'
     */
    FOC_fastCTRL_Y->I_dq_Ref_outA[i] = FOC_fastCTRL_U->I_dq_RefA[i];

    /* Gain: '<S38>/TrafoMatrix uvw->alphabeta' incorporates:
     *  Inport: '<Root>/I_ph [A]'
     */
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[i] = 0.0;
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[i] +=
      FOC_fastCTRL_P.TrafoMatrixuvwalphabeta_Gain[i] * FOC_fastCTRL_U->I_phA[0];
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[i] +=
      FOC_fastCTRL_P.TrafoMatrixuvwalphabeta_Gain[i + 2] * FOC_fastCTRL_U->
      I_phA[1];
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[i] +=
      FOC_fastCTRL_P.TrafoMatrixuvwalphabeta_Gain[i + 4] * FOC_fastCTRL_U->
      I_phA[2];
  }

  /* UnitDelay: '<S33>/Unit Delay1' */
  FOC_fastCTRL_B->UnitDelay1 = FOC_fastCTRL_DW->UnitDelay1_DSTATE;

  /* Outport: '<Root>/w_el [rad//s]' incorporates:
   *  Gain: '<S26>/Gain5'
   */
  FOC_fastCTRL_Y->w_elrads = FOC_fastCTRL_P.Factor_OmegaRot *
    FOC_fastCTRL_B->UnitDelay1;

  /* Relay: '<S5>/AutoSwitchHysteresis' incorporates:
   *  Outport: '<Root>/w_el [rad//s]'
   */
  maxV = FOC_fastCTRL_Y->w_elrads;
  FOC_fastCTRL_DW->AutoSwitchHysteresis_Mode = ((maxV >=
    FOC_fastCTRL_P.FOC_AngleEst_AutoSwitch_wel_on) || ((!(maxV <=
    FOC_fastCTRL_P.FOC_AngleEst_AutoSwitch_wel_off)) &&
    FOC_fastCTRL_DW->AutoSwitchHysteresis_Mode));
  if (FOC_fastCTRL_DW->AutoSwitchHysteresis_Mode) {
    /* Relay: '<S5>/AutoSwitchHysteresis' */
    FOC_fastCTRL_B->AutoSwitchHysteresis =
      FOC_fastCTRL_P.AutoSwitchHysteresis_YOn;
  } else {
    /* Relay: '<S5>/AutoSwitchHysteresis' */
    FOC_fastCTRL_B->AutoSwitchHysteresis =
      FOC_fastCTRL_P.AutoSwitchHysteresis_YOff;
  }

  /* End of Relay: '<S5>/AutoSwitchHysteresis' */

  /* MultiPortSwitch: '<S5>/Selectphicalc3' incorporates:
   *  Constant: '<S5>/Constant5'
   */
  if ((int32_T)FOC_fastCTRL_P.FOC_SELECT_AngleEst_AutoSwitch == 0) {
    /* MultiPortSwitch: '<S5>/Selectphicalc3' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    FOC_fastCTRL_B->Selectphicalc3 = FOC_fastCTRL_P.FOC_SELECT_AngleEst;
  } else {
    /* MultiPortSwitch: '<S5>/Selectphicalc3' */
    FOC_fastCTRL_B->Selectphicalc3 = FOC_fastCTRL_B->AutoSwitchHysteresis;
  }

  /* End of MultiPortSwitch: '<S5>/Selectphicalc3' */

  /* Switch: '<S24>/Switch' incorporates:
   *  Constant: '<S5>/Constant4'
   */
  if (FOC_fastCTRL_P.FOC_SELECT_AngleAdaptionRange != 0.0) {
    /* Switch: '<S31>/Switch1' incorporates:
     *  Inport: '<Root>/phi_el [rad]'
     */
    if (FOC_fastCTRL_U->phi_elrad > FOC_fastCTRL_P.Switch1_Threshold) {
      /* Sum: '<S31>/Sum2' incorporates:
       *  Constant: '<S31>/Constant'
       */
      FOC_fastCTRL_B->Sum2_m = FOC_fastCTRL_U->phi_elrad -
        FOC_fastCTRL_P.Constant_Value_k;

      /* Switch: '<S31>/Switch1' */
      FOC_fastCTRL_B->Switch1_p = FOC_fastCTRL_B->Sum2_m;
    } else {
      /* Switch: '<S31>/Switch1' */
      FOC_fastCTRL_B->Switch1_p = FOC_fastCTRL_U->phi_elrad;
    }

    /* End of Switch: '<S31>/Switch1' */

    /* Switch: '<S31>/Switch2' */
    if (FOC_fastCTRL_B->Switch1_p > FOC_fastCTRL_P.Switch2_Threshold) {
      /* Switch: '<S31>/Switch2' */
      FOC_fastCTRL_B->Switch2_d = FOC_fastCTRL_B->Switch1_p;
    } else {
      /* Sum: '<S31>/Sum3' incorporates:
       *  Constant: '<S31>/Constant1'
       */
      FOC_fastCTRL_B->Sum3_c = FOC_fastCTRL_B->Switch1_p +
        FOC_fastCTRL_P.Constant1_Value_b;

      /* Switch: '<S31>/Switch2' */
      FOC_fastCTRL_B->Switch2_d = FOC_fastCTRL_B->Sum3_c;
    }

    /* End of Switch: '<S31>/Switch2' */

    /* Switch: '<S24>/Switch' */
    FOC_fastCTRL_B->Switch = FOC_fastCTRL_B->Switch2_d;
  } else {
    /* Switch: '<S24>/Switch' incorporates:
     *  Inport: '<Root>/phi_el [rad]'
     */
    FOC_fastCTRL_B->Switch = FOC_fastCTRL_U->phi_elrad;
  }

  /* End of Switch: '<S24>/Switch' */

  /* Switch: '<S25>/Switch' incorporates:
   *  Constant: '<S5>/Constant2'
   */
  if (FOC_fastCTRL_P.FOC_SELECT_AngleAdaption2PolePairs >
      FOC_fastCTRL_P.Switch_Threshold) {
    /* Switch: '<S25>/Switch' */
    FOC_fastCTRL_B->Switch_j = 0.0;
  } else {
    /* Switch: '<S25>/Switch' */
    FOC_fastCTRL_B->Switch_j = FOC_fastCTRL_B->Switch;
  }

  /* End of Switch: '<S25>/Switch' */

  /* Switch: '<S27>/Switch' incorporates:
   *  Constant: '<S5>/FOC_Invert_Encoder'
   */
  if (FOC_fastCTRL_P.FOC_SELECT_InvertAngle != 0.0) {
    /* Sum: '<S27>/PhiInverted' incorporates:
     *  Constant: '<S27>/Constant'
     */
    FOC_fastCTRL_B->PhiInverted = FOC_fastCTRL_P.Constant_Value_n -
      FOC_fastCTRL_B->Switch_j;

    /* Switch: '<S27>/Switch' */
    FOC_fastCTRL_B->Switch_i = FOC_fastCTRL_B->PhiInverted;
  } else {
    /* Switch: '<S27>/Switch' */
    FOC_fastCTRL_B->Switch_i = FOC_fastCTRL_B->Switch_j;
  }

  /* End of Switch: '<S27>/Switch' */

  /* Saturate: '<S5>/ResolverOffsetLimitation' */
  if (FOC_fastCTRL_P.FOC_phi_offset >
      FOC_fastCTRL_P.ResolverOffsetLimitation_UpperS) {
    /* Saturate: '<S5>/ResolverOffsetLimitation' */
    FOC_fastCTRL_B->ResolverOffsetLimitation =
      FOC_fastCTRL_P.ResolverOffsetLimitation_UpperS;
  } else if (FOC_fastCTRL_P.FOC_phi_offset <
             FOC_fastCTRL_P.ResolverOffsetLimitation_LowerS) {
    /* Saturate: '<S5>/ResolverOffsetLimitation' */
    FOC_fastCTRL_B->ResolverOffsetLimitation =
      FOC_fastCTRL_P.ResolverOffsetLimitation_LowerS;
  } else {
    /* Saturate: '<S5>/ResolverOffsetLimitation' */
    FOC_fastCTRL_B->ResolverOffsetLimitation = FOC_fastCTRL_P.FOC_phi_offset;
  }

  /* End of Saturate: '<S5>/ResolverOffsetLimitation' */

  /* Sum: '<S5>/Sum3' */
  FOC_fastCTRL_B->Sum3 = FOC_fastCTRL_B->Switch_i +
    FOC_fastCTRL_B->ResolverOffsetLimitation;

  /* UnitDelay: '<S15>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_b[0] = FOC_fastCTRL_DW->UnitDelay_DSTATE_m[0];

  /* Product: '<S3>/Product3' incorporates:
   *  Constant: '<S3>/FOC_AngleEst_Lq'
   */
  FOC_fastCTRL_B->Product3[0] = FOC_fastCTRL_P.FOC_AngleEst_Lq *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[0];

  /* Sum: '<S3>/Sum1' */
  FOC_fastCTRL_B->psi_PM_alphabeta[0] = FOC_fastCTRL_B->UnitDelay_b[0] -
    FOC_fastCTRL_B->Product3[0];

  /* UnitDelay: '<S15>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_b[1] = FOC_fastCTRL_DW->UnitDelay_DSTATE_m[1];

  /* Product: '<S3>/Product3' incorporates:
   *  Constant: '<S3>/FOC_AngleEst_Lq'
   */
  FOC_fastCTRL_B->Product3[1] = FOC_fastCTRL_P.FOC_AngleEst_Lq *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[1];

  /* Sum: '<S3>/Sum1' */
  FOC_fastCTRL_B->psi_PM_alphabeta[1] = FOC_fastCTRL_B->UnitDelay_b[1] -
    FOC_fastCTRL_B->Product3[1];

  /* Trigonometry: '<S11>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction = rt_atan2d_snf
    (FOC_fastCTRL_B->psi_PM_alphabeta[1], FOC_fastCTRL_B->psi_PM_alphabeta[0]);

  /* Switch: '<S11>/Switch_Phi' */
  if (FOC_fastCTRL_B->TrigonometricFunction >
      FOC_fastCTRL_P.Switch_Phi_Threshold) {
    /* Switch: '<S11>/Switch_Phi' */
    FOC_fastCTRL_B->Switch_Phi = FOC_fastCTRL_B->TrigonometricFunction;
  } else {
    /* Sum: '<S11>/Sum1' incorporates:
     *  Constant: '<S11>/Constant'
     */
    FOC_fastCTRL_B->Sum1_bu = FOC_fastCTRL_B->TrigonometricFunction +
      FOC_fastCTRL_P.Constant_Value_p;

    /* Switch: '<S11>/Switch_Phi' */
    FOC_fastCTRL_B->Switch_Phi = FOC_fastCTRL_B->Sum1_bu;
  }

  /* End of Switch: '<S11>/Switch_Phi' */

  /* UnitDelay: '<S12>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_n = FOC_fastCTRL_DW->UnitDelay_DSTATE_n;

  /* Product: '<S13>/Product' incorporates:
   *  Constant: '<S13>/FOC_f_fastCTRL'
   */
  FOC_fastCTRL_B->Product_o = FOC_fastCTRL_B->Switch_Phi *
    FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  maxV = FOC_fastCTRL_B->Product_o;
  maxV -= FOC_fastCTRL_P.DiscreteTransferFcn_DenCoef_o[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn_states_o;
  maxV /= FOC_fastCTRL_P.DiscreteTransferFcn_DenCoef_o[0];
  FOC_fastCTRL_DW->DiscreteTransferFcn_tmp = maxV;
  maxV = FOC_fastCTRL_P.DiscreteTransferFcn_NumCoef_o[0] *
    FOC_fastCTRL_DW->DiscreteTransferFcn_tmp;
  maxV += FOC_fastCTRL_P.DiscreteTransferFcn_NumCoef_o[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn_states_o;

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  FOC_fastCTRL_B->DiscreteTransferFcn_e = maxV;

  /* RelationalOperator: '<S13>/Relational Operator' incorporates:
   *  Constant: '<S13>/Constant'
   */
  FOC_fastCTRL_B->RelationalOperator = (FOC_fastCTRL_B->Switch_Phi <
    FOC_fastCTRL_P.Constant_Value_h);

  /* RelationalOperator: '<S13>/Relational Operator1' incorporates:
   *  Constant: '<S13>/Constant1'
   */
  FOC_fastCTRL_B->RelationalOperator1 = (FOC_fastCTRL_B->Switch_Phi >
    FOC_fastCTRL_P.Constant1_Value_g);

  /* Logic: '<S13>/Logical Operator' */
  FOC_fastCTRL_B->LogicalOperator = (FOC_fastCTRL_B->RelationalOperator &&
    FOC_fastCTRL_B->RelationalOperator1);

  /* RelationalOperator: '<S13>/Relational Operator2' incorporates:
   *  Constant: '<S13>/Constant2'
   */
  FOC_fastCTRL_B->RelationalOperator2 = (FOC_fastCTRL_B->Switch_Phi <
    FOC_fastCTRL_P.Constant2_Value_ej);

  /* Switch: '<S13>/Switch1' */
  if (FOC_fastCTRL_B->RelationalOperator2) {
    /* Switch: '<S13>/Switch1' */
    FOC_fastCTRL_B->Switch1 = FOC_fastCTRL_B->Switch_Phi;
  } else {
    /* Bias: '<S13>/Bias' */
    FOC_fastCTRL_B->Bias_p = FOC_fastCTRL_B->Switch_Phi +
      FOC_fastCTRL_P.Bias_Bias;

    /* Switch: '<S13>/Switch1' */
    FOC_fastCTRL_B->Switch1 = FOC_fastCTRL_B->Bias_p;
  }

  /* End of Switch: '<S13>/Switch1' */

  /* Product: '<S13>/Product1' incorporates:
   *  Constant: '<S13>/FOC_f_fastCTRL1'
   */
  FOC_fastCTRL_B->Product1 = FOC_fastCTRL_B->Switch1 *
    FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn1' */
  maxV = FOC_fastCTRL_B->Product1;
  maxV -= FOC_fastCTRL_P.DiscreteTransferFcn1_DenCoef[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn1_states;
  maxV /= FOC_fastCTRL_P.DiscreteTransferFcn1_DenCoef[0];
  FOC_fastCTRL_DW->DiscreteTransferFcn1_tmp = maxV;
  maxV = FOC_fastCTRL_P.DiscreteTransferFcn1_NumCoef[0] *
    FOC_fastCTRL_DW->DiscreteTransferFcn1_tmp;
  maxV += FOC_fastCTRL_P.DiscreteTransferFcn1_NumCoef[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn1_states;

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn1' */
  FOC_fastCTRL_B->DiscreteTransferFcn1 = maxV;

  /* Switch: '<S13>/Switch_speed' */
  if (FOC_fastCTRL_B->LogicalOperator) {
    /* Switch: '<S13>/Switch_speed' */
    FOC_fastCTRL_B->Switch_speed = FOC_fastCTRL_B->DiscreteTransferFcn_e;
  } else {
    /* Switch: '<S13>/Switch_speed' */
    FOC_fastCTRL_B->Switch_speed = FOC_fastCTRL_B->DiscreteTransferFcn1;
  }

  /* End of Switch: '<S13>/Switch_speed' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S3>/useFilteredCorrection'
   */
  if (FOC_fastCTRL_P.FOC_SELECT_AngleEst_w_el_filtered >
      FOC_fastCTRL_P.Switch2_Threshold_b) {
    /* Switch: '<S3>/Switch2' */
    FOC_fastCTRL_B->Switch2 = FOC_fastCTRL_B->UnitDelay_n;
  } else {
    /* Switch: '<S3>/Switch2' */
    FOC_fastCTRL_B->Switch2 = FOC_fastCTRL_B->Switch_speed;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Switch: '<S3>/Switch' */
  if (FOC_fastCTRL_B->Switch2 > FOC_fastCTRL_P.Switch_Threshold_l) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    FOC_fastCTRL_B->Switch_ib = FOC_fastCTRL_P.Constant1_Value_i;
  } else {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S3>/Constant2'
     */
    FOC_fastCTRL_B->Switch_ib = FOC_fastCTRL_P.Constant2_Value_l;
  }

  /* End of Switch: '<S3>/Switch' */

  /* Abs: '<S3>/Abs' */
  FOC_fastCTRL_B->Abs = fabs(FOC_fastCTRL_B->Switch2);

  /* Product: '<S3>/Product' incorporates:
   *  Constant: '<S3>/komp_kp'
   */
  FOC_fastCTRL_B->Product_h = 1.0 / FOC_fastCTRL_P.FOC_AngleEst_Komp_KP *
    FOC_fastCTRL_B->Abs;

  /* Trigonometry: '<S3>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_m = atan(FOC_fastCTRL_B->Product_h);

  /* Sum: '<S3>/Sum3' incorporates:
   *  Constant: '<S3>/Constant'
   */
  FOC_fastCTRL_B->Sum3_l = FOC_fastCTRL_P.Constant_Value_b -
    FOC_fastCTRL_B->TrigonometricFunction_m;

  /* Product: '<S3>/Product1' */
  FOC_fastCTRL_B->Product1_d = FOC_fastCTRL_B->Switch_ib *
    FOC_fastCTRL_B->Sum3_l;

  /* Sum: '<S3>/Sum2' */
  FOC_fastCTRL_B->Sum2 = FOC_fastCTRL_B->Switch_Phi - FOC_fastCTRL_B->Product1_d;

  /* Switch: '<S10>/Switch2' */
  if (FOC_fastCTRL_B->Sum2 >= FOC_fastCTRL_P.Switch2_Threshold_g) {
    /* Switch: '<S10>/Switch2' incorporates:
     *  Constant: '<S10>/Constant1'
     */
    FOC_fastCTRL_B->Switch2_n = FOC_fastCTRL_P.Constant1_Value;
  } else {
    /* Switch: '<S10>/Switch2' incorporates:
     *  Constant: '<S10>/Constant'
     */
    FOC_fastCTRL_B->Switch2_n = FOC_fastCTRL_P.Constant_Value;
  }

  /* End of Switch: '<S10>/Switch2' */

  /* Switch: '<S10>/Switch1' */
  if (FOC_fastCTRL_B->Sum2 >= FOC_fastCTRL_P.Switch1_Threshold_m) {
    /* Switch: '<S10>/Switch1' incorporates:
     *  Constant: '<S10>/Constant2'
     */
    FOC_fastCTRL_B->Switch1_m = FOC_fastCTRL_P.Constant2_Value;
  } else {
    /* Switch: '<S10>/Switch1' incorporates:
     *  Constant: '<S10>/Constant3'
     */
    FOC_fastCTRL_B->Switch1_m = FOC_fastCTRL_P.Constant3_Value;
  }

  /* End of Switch: '<S10>/Switch1' */

  /* Sum: '<S10>/Sum1' */
  FOC_fastCTRL_B->Sum1 = (FOC_fastCTRL_B->Switch2_n + FOC_fastCTRL_B->Sum2) +
    FOC_fastCTRL_B->Switch1_m;

  /* MultiPortSwitch: '<S5>/Selectphicalc1' */
  if ((int32_T)FOC_fastCTRL_B->Selectphicalc3 == 0) {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' */
    FOC_fastCTRL_B->Selectphicalc1 = FOC_fastCTRL_B->Sum3;
  } else {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' */
    FOC_fastCTRL_B->Selectphicalc1 = FOC_fastCTRL_B->Sum1;
  }

  /* End of MultiPortSwitch: '<S5>/Selectphicalc1' */

  /* Switch: '<S30>/Switch1' */
  if (FOC_fastCTRL_B->Selectphicalc1 > FOC_fastCTRL_P.Switch1_Threshold_o) {
    /* Sum: '<S30>/Sum2' incorporates:
     *  Constant: '<S30>/Constant'
     */
    FOC_fastCTRL_B->Sum2_k = FOC_fastCTRL_B->Selectphicalc1 -
      FOC_fastCTRL_P.Constant_Value_f;

    /* Switch: '<S30>/Switch1' */
    FOC_fastCTRL_B->Switch1_j = FOC_fastCTRL_B->Sum2_k;
  } else {
    /* Switch: '<S30>/Switch1' */
    FOC_fastCTRL_B->Switch1_j = FOC_fastCTRL_B->Selectphicalc1;
  }

  /* End of Switch: '<S30>/Switch1' */

  /* Switch: '<S30>/Switch2' */
  if (FOC_fastCTRL_B->Switch1_j > FOC_fastCTRL_P.Switch2_Threshold_l) {
    /* Switch: '<S30>/Switch2' */
    FOC_fastCTRL_B->Switch2_k = FOC_fastCTRL_B->Switch1_j;
  } else {
    /* Sum: '<S30>/Sum3' incorporates:
     *  Constant: '<S30>/Constant1'
     */
    FOC_fastCTRL_B->Sum3_d = FOC_fastCTRL_B->Switch1_j +
      FOC_fastCTRL_P.Constant1_Value_c;

    /* Switch: '<S30>/Switch2' */
    FOC_fastCTRL_B->Switch2_k = FOC_fastCTRL_B->Sum3_d;
  }

  /* End of Switch: '<S30>/Switch2' */

  /* MultiPortSwitch: '<S26>/Selectphicalc3' */
  if ((int32_T)FOC_fastCTRL_B->Selectphicalc3 == 0) {
    /* MultiPortSwitch: '<S26>/Selectphicalc3' incorporates:
     *  Constant: '<S26>/Constant2'
     */
    FOC_fastCTRL_B->Selectphicalc3_c = FOC_fastCTRL_P.FOC_PhiSensorTdead;
  } else {
    /* MultiPortSwitch: '<S26>/Selectphicalc3' incorporates:
     *  Constant: '<S26>/Constant3'
     */
    FOC_fastCTRL_B->Selectphicalc3_c =
      FOC_fastCTRL_P.FOC_PhiSensorTdead_AngleEst;
  }

  /* End of MultiPortSwitch: '<S26>/Selectphicalc3' */

  /* Product: '<S26>/Product3' */
  FOC_fastCTRL_B->Product3_g = FOC_fastCTRL_B->UnitDelay1 *
    FOC_fastCTRL_B->Selectphicalc3_c;

  /* Sum: '<S26>/Sum3' */
  FOC_fastCTRL_B->Sum3_h = FOC_fastCTRL_B->Switch2_k +
    FOC_fastCTRL_B->Product3_g;

  /* UnitDelay: '<S32>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_c = FOC_fastCTRL_DW->UnitDelay_DSTATE_g;

  /* Sum: '<S32>/Sum' */
  FOC_fastCTRL_B->Sum = FOC_fastCTRL_B->Sum3_h - FOC_fastCTRL_B->UnitDelay_c;

  /* RelationalOperator: '<S32>/Sprung?' incorporates:
   *  Constant: '<S32>/Constant3'
   */
  FOC_fastCTRL_B->Sprung = (FOC_fastCTRL_B->Sum <
    FOC_fastCTRL_P.Constant3_Value_g);

  /* Switch: '<S32>/Switch' */
  if (FOC_fastCTRL_B->Sprung) {
    /* Switch: '<S32>/Switch' incorporates:
     *  Constant: '<S32>/Constant2'
     */
    FOC_fastCTRL_B->Switch_p = FOC_fastCTRL_P.Constant2_Value_m;
  } else {
    /* Switch: '<S32>/Switch' incorporates:
     *  Constant: '<S32>/Constant4'
     */
    FOC_fastCTRL_B->Switch_p = FOC_fastCTRL_P.Constant4_Value;
  }

  /* End of Switch: '<S32>/Switch' */

  /* RelationalOperator: '<S32>/Sprung?1' incorporates:
   *  Constant: '<S32>/Constant1'
   */
  FOC_fastCTRL_B->Sprung1 = (FOC_fastCTRL_B->Sum >
    FOC_fastCTRL_P.Constant1_Value_oz);

  /* Switch: '<S32>/Switch1' */
  if (FOC_fastCTRL_B->Sprung1) {
    /* Switch: '<S32>/Switch1' incorporates:
     *  Constant: '<S32>/Constant5'
     */
    FOC_fastCTRL_B->Switch1_g = FOC_fastCTRL_P.Constant5_Value;
  } else {
    /* Switch: '<S32>/Switch1' incorporates:
     *  Constant: '<S32>/Constant6'
     */
    FOC_fastCTRL_B->Switch1_g = FOC_fastCTRL_P.Constant6_Value;
  }

  /* End of Switch: '<S32>/Switch1' */

  /* Sum: '<S32>/Sum2' */
  FOC_fastCTRL_B->Sum2_n = FOC_fastCTRL_B->Switch_p + FOC_fastCTRL_B->Switch1_g;

  /* UnitDelay: '<S26>/Unit Delay3' */
  FOC_fastCTRL_B->UnitDelay3 = FOC_fastCTRL_DW->UnitDelay3_DSTATE;

  /* Sum: '<S26>/Sum7' */
  Phi_Observer = FOC_fastCTRL_B->UnitDelay3 - FOC_fastCTRL_B->Sum2_n;

  /* MultiPortSwitch: '<S5>/Selectphicalc2' incorporates:
   *  Constant: '<S5>/Constant3'
   */
  if ((int32_T)FOC_fastCTRL_P.FOC_SELECT_phi == 1) {
    /* MultiPortSwitch: '<S5>/Selectphicalc2' */
    FOC_fastCTRL_B->Selectphicalc2 = FOC_fastCTRL_B->Switch2_k;
  } else {
    /* MultiPortSwitch: '<S5>/Selectphicalc2' */
    FOC_fastCTRL_B->Selectphicalc2 = Phi_Observer;
  }

  /* End of MultiPortSwitch: '<S5>/Selectphicalc2' */

  /* Switch: '<S28>/Switch1' */
  if (FOC_fastCTRL_B->Selectphicalc2 > FOC_fastCTRL_P.Switch1_Threshold_a) {
    /* Sum: '<S28>/Sum2' incorporates:
     *  Constant: '<S28>/Constant'
     */
    FOC_fastCTRL_B->Sum2_i = FOC_fastCTRL_B->Selectphicalc2 -
      FOC_fastCTRL_P.Constant_Value_l;

    /* Switch: '<S28>/Switch1' */
    FOC_fastCTRL_B->Switch1_d = FOC_fastCTRL_B->Sum2_i;
  } else {
    /* Switch: '<S28>/Switch1' */
    FOC_fastCTRL_B->Switch1_d = FOC_fastCTRL_B->Selectphicalc2;
  }

  /* End of Switch: '<S28>/Switch1' */

  /* Switch: '<S28>/Switch2' */
  if (FOC_fastCTRL_B->Switch1_d > FOC_fastCTRL_P.Switch2_Threshold_gc) {
    /* Switch: '<S28>/Switch2' */
    FOC_fastCTRL_B->Switch2_nz = FOC_fastCTRL_B->Switch1_d;
  } else {
    /* Sum: '<S28>/Sum3' incorporates:
     *  Constant: '<S28>/Constant1'
     */
    FOC_fastCTRL_B->Sum3_n = FOC_fastCTRL_B->Switch1_d +
      FOC_fastCTRL_P.Constant1_Value_o;

    /* Switch: '<S28>/Switch2' */
    FOC_fastCTRL_B->Switch2_nz = FOC_fastCTRL_B->Sum3_n;
  }

  /* End of Switch: '<S28>/Switch2' */

  /* Trigonometry: '<S38>/Trigonometric Function1' */
  FOC_fastCTRL_B->TrigonometricFunction1 = cos(FOC_fastCTRL_B->Switch2_nz);

  /* Product: '<S38>/TrafoProd' */
  FOC_fastCTRL_B->TrafoProd = FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[0] *
    FOC_fastCTRL_B->TrigonometricFunction1;

  /* Trigonometry: '<S38>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_h = sin(FOC_fastCTRL_B->Switch2_nz);

  /* Product: '<S38>/TrafoProd3' */
  FOC_fastCTRL_B->TrafoProd3 = FOC_fastCTRL_B->TrigonometricFunction_h *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[1];

  /* Sum: '<S38>/TrafoSum' */
  FOC_fastCTRL_B->TrafoSum = FOC_fastCTRL_B->TrafoProd +
    FOC_fastCTRL_B->TrafoProd3;

  /* Product: '<S38>/TrafoProd1' */
  FOC_fastCTRL_B->TrafoProd1 = FOC_fastCTRL_B->TrigonometricFunction1 *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[1];

  /* Product: '<S38>/TrafoProd2' */
  FOC_fastCTRL_B->TrafoProd2 = FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[0] *
    FOC_fastCTRL_B->TrigonometricFunction_h;

  /* Sum: '<S38>/TrafoSum1' */
  FOC_fastCTRL_B->TrafoSum1 = FOC_fastCTRL_B->TrafoProd1 -
    FOC_fastCTRL_B->TrafoProd2;

  /* SignalConversion generated from: '<S35>/Math Function' */
  FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[0] = FOC_fastCTRL_B->TrafoSum;
  FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[1] = FOC_fastCTRL_B->TrafoSum1;

  /* Product: '<S41>/Product1' incorporates:
   *  Constant: '<S41>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S41>/Product1' incorporates:
   *  Constant: '<S41>/FOC_KI'
   */
  FOC_fastCTRL_B->Product1_f = FOC_fastCTRL_P.FOC_KI * maxV;

  /* Logic: '<S1>/Logical Operator1' incorporates:
   *  Constant: '<S1>/Enable'
   *  Inport: '<Root>/FOC_Enable'
   */
  FOC_fastCTRL_B->LogicalOperator1 = ((FOC_fastCTRL_P.FOC_Enable != 0.0) &&
    (FOC_fastCTRL_U->FOC_Enable != 0.0));
  for (i = 0; i < 2; i++) {
    /* Sum: '<S36>/IdqErr' incorporates:
     *  Outport: '<Root>/I_dq_Ref_out [A]'
     */
    FOC_fastCTRL_B->IdqErr[i] = FOC_fastCTRL_Y->I_dq_Ref_outA[i] -
      FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[i];

    /* Product: '<S41>/KP*e[k]1' incorporates:
     *  Constant: '<S41>/FOC_KP1'
     */
    FOC_fastCTRL_B->KPek1[i] = FOC_fastCTRL_B->IdqErr[i] * FOC_fastCTRL_P.FOC_KP;

    /* UnitDelay: '<S41>/IntegDelay1' */
    FOC_fastCTRL_B->IntegDelay1[i] = FOC_fastCTRL_DW->IntegDelay1_DSTATE[i];

    /* Gain: '<S39>/TrafoMatrix uvw->alphabeta' incorporates:
     *  Inport: '<Root>/I_ph [A]'
     */
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[i] = 0.0;
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[i] +=
      FOC_fastCTRL_P.TrafoMatrixuvwalphabeta_Gain_m[i] * FOC_fastCTRL_U->I_phA[3];
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[i] +=
      FOC_fastCTRL_P.TrafoMatrixuvwalphabeta_Gain_m[i + 2] *
      FOC_fastCTRL_U->I_phA[4];
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[i] +=
      FOC_fastCTRL_P.TrafoMatrixuvwalphabeta_Gain_m[i + 4] *
      FOC_fastCTRL_U->I_phA[5];
  }

  /* Sum: '<S6>/Sum1' incorporates:
   *  Constant: '<S6>/FOC_6ph_AngleShift'
   */
  FOC_fastCTRL_B->Sum1_f = FOC_fastCTRL_B->Switch2_nz +
    FOC_fastCTRL_P.FOC_6ph_AngleShift;

  /* Trigonometry: '<S39>/Trigonometric Function1' */
  FOC_fastCTRL_B->TrigonometricFunction1_c = cos(FOC_fastCTRL_B->Sum1_f);

  /* Product: '<S39>/TrafoProd' */
  FOC_fastCTRL_B->TrafoProd_d = FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[0] *
    FOC_fastCTRL_B->TrigonometricFunction1_c;

  /* Trigonometry: '<S39>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_j = sin(FOC_fastCTRL_B->Sum1_f);

  /* Product: '<S39>/TrafoProd3' */
  FOC_fastCTRL_B->TrafoProd3_o = FOC_fastCTRL_B->TrigonometricFunction_j *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[1];

  /* Sum: '<S39>/TrafoSum' */
  FOC_fastCTRL_B->TrafoSum_a = FOC_fastCTRL_B->TrafoProd_d +
    FOC_fastCTRL_B->TrafoProd3_o;

  /* Product: '<S39>/TrafoProd1' */
  FOC_fastCTRL_B->TrafoProd1_m = FOC_fastCTRL_B->TrigonometricFunction1_c *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[1];

  /* Product: '<S39>/TrafoProd2' */
  FOC_fastCTRL_B->TrafoProd2_e = FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[0] *
    FOC_fastCTRL_B->TrigonometricFunction_j;

  /* Sum: '<S39>/TrafoSum1' */
  FOC_fastCTRL_B->TrafoSum1_h = FOC_fastCTRL_B->TrafoProd1_m -
    FOC_fastCTRL_B->TrafoProd2_e;

  /* SignalConversion generated from: '<S39>/Discrete FIR Filter 20th order' */
  FOC_fastCTRL_B->TmpSignalConversionAtDiscreteFI[0] =
    FOC_fastCTRL_B->TrafoSum_a;
  FOC_fastCTRL_B->TmpSignalConversionAtDiscreteFI[1] =
    FOC_fastCTRL_B->TrafoSum1_h;

  /* Sum: '<S37>/IdqErr' incorporates:
   *  Outport: '<Root>/I_dq_Ref_out [A]'
   */
  FOC_fastCTRL_B->IdqErr_i[0] = FOC_fastCTRL_Y->I_dq_Ref_outA[0] -
    FOC_fastCTRL_B->TmpSignalConversionAtDiscreteFI[0];

  /* Product: '<S45>/KP*e[k]1' incorporates:
   *  Constant: '<S45>/FOC_KP1'
   */
  FOC_fastCTRL_B->KPek1_a[0] = FOC_fastCTRL_B->IdqErr_i[0] *
    FOC_fastCTRL_P.FOC_KP;

  /* UnitDelay: '<S45>/IntegDelay1' */
  FOC_fastCTRL_B->IntegDelay1_b[0] = FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0];

  /* Sum: '<S37>/IdqErr' incorporates:
   *  Outport: '<Root>/I_dq_Ref_out [A]'
   */
  FOC_fastCTRL_B->IdqErr_i[1] = FOC_fastCTRL_Y->I_dq_Ref_outA[1] -
    FOC_fastCTRL_B->TmpSignalConversionAtDiscreteFI[1];

  /* Product: '<S45>/KP*e[k]1' incorporates:
   *  Constant: '<S45>/FOC_KP1'
   */
  FOC_fastCTRL_B->KPek1_a[1] = FOC_fastCTRL_B->IdqErr_i[1] *
    FOC_fastCTRL_P.FOC_KP;

  /* UnitDelay: '<S45>/IntegDelay1' */
  FOC_fastCTRL_B->IntegDelay1_b[1] = FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1];

  /* Product: '<S45>/Product1' incorporates:
   *  Constant: '<S45>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S45>/Product1' incorporates:
   *  Constant: '<S45>/FOC_KI'
   */
  FOC_fastCTRL_B->Product1_p = FOC_fastCTRL_P.FOC_KI * maxV;

  /* Product: '<S5>/Product' incorporates:
   *  Constant: '<S5>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S5>/Product' incorporates:
   *  Constant: '<S5>/FOC_output_trafo_delay'
   *  Outport: '<Root>/w_el [rad//s]'
   */
  FOC_fastCTRL_B->Product_d = FOC_fastCTRL_P.FOC_output_trafo_delay *
    FOC_fastCTRL_Y->w_elrads * maxV;

  /* Sum: '<S5>/Sum' */
  FOC_fastCTRL_B->Sum_e = FOC_fastCTRL_B->Switch2_nz + FOC_fastCTRL_B->Product_d;

  /* Switch: '<S29>/Switch1' */
  if (FOC_fastCTRL_B->Sum_e > FOC_fastCTRL_P.Switch1_Threshold_p) {
    /* Sum: '<S29>/Sum2' incorporates:
     *  Constant: '<S29>/Constant'
     */
    FOC_fastCTRL_B->Sum2_op = FOC_fastCTRL_B->Sum_e -
      FOC_fastCTRL_P.Constant_Value_lk;

    /* Switch: '<S29>/Switch1' */
    FOC_fastCTRL_B->Switch1_b = FOC_fastCTRL_B->Sum2_op;
  } else {
    /* Switch: '<S29>/Switch1' */
    FOC_fastCTRL_B->Switch1_b = FOC_fastCTRL_B->Sum_e;
  }

  /* End of Switch: '<S29>/Switch1' */

  /* Switch: '<S29>/Switch2' */
  if (FOC_fastCTRL_B->Switch1_b > FOC_fastCTRL_P.Switch2_Threshold_d) {
    /* Switch: '<S29>/Switch2' */
    FOC_fastCTRL_B->Switch2_e = FOC_fastCTRL_B->Switch1_b;
  } else {
    /* Sum: '<S29>/Sum3' incorporates:
     *  Constant: '<S29>/Constant1'
     */
    FOC_fastCTRL_B->Sum3_a = FOC_fastCTRL_B->Switch1_b +
      FOC_fastCTRL_P.Constant1_Value_p;

    /* Switch: '<S29>/Switch2' */
    FOC_fastCTRL_B->Switch2_e = FOC_fastCTRL_B->Sum3_a;
  }

  /* End of Switch: '<S29>/Switch2' */

  /* MultiPortSwitch: '<S1>/SelectControlMode' */
  switch ((int32_T)FOC_fastCTRL_B->ModeSwitch) {
   case 0:
    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S1>/Null'
     */
    for (i = 0; i < 6; i++) {
      FOC_fastCTRL_B->SelectControlMode[i] = FOC_fastCTRL_P.Null_Value[i];
    }
    break;

   case 1:
    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S1>/Null'
     */
    for (i = 0; i < 6; i++) {
      FOC_fastCTRL_B->SelectControlMode[i] = FOC_fastCTRL_P.Null_Value[i];
    }
    break;

   case 2:
    /* Gain: '<S49>/Gain' */
    FOC_fastCTRL_B->Gain_i = FOC_fastCTRL_P.FOC_Uf_m *
      FOC_fastCTRL_B->DiscreteTransferFcn;

    /* Signum: '<S49>/Sign' */
    u = FOC_fastCTRL_B->Gain_i;
    if (rtIsNaN(u)) {
      /* Signum: '<S49>/Sign' */
      FOC_fastCTRL_B->Sign_m = u;
    } else if (u < 0.0) {
      /* Signum: '<S49>/Sign' */
      FOC_fastCTRL_B->Sign_m = -1.0;
    } else {
      /* Signum: '<S49>/Sign' */
      FOC_fastCTRL_B->Sign_m = (u > 0.0);
    }

    /* End of Signum: '<S49>/Sign' */

    /* Abs: '<S49>/Abs' */
    FOC_fastCTRL_B->Abs_e = fabs(FOC_fastCTRL_B->Gain_i);

    /* Saturate: '<S49>/Saturation1' */
    if (FOC_fastCTRL_B->Abs_e > FOC_fastCTRL_P.FOC_Uf_U_max) {
      /* Saturate: '<S49>/Saturation1' */
      FOC_fastCTRL_B->Saturation1 = FOC_fastCTRL_P.FOC_Uf_U_max;
    } else if (FOC_fastCTRL_B->Abs_e < FOC_fastCTRL_P.FOC_Uf_U_min) {
      /* Saturate: '<S49>/Saturation1' */
      FOC_fastCTRL_B->Saturation1 = FOC_fastCTRL_P.FOC_Uf_U_min;
    } else {
      /* Saturate: '<S49>/Saturation1' */
      FOC_fastCTRL_B->Saturation1 = FOC_fastCTRL_B->Abs_e;
    }

    /* End of Saturate: '<S49>/Saturation1' */

    /* Product: '<S49>/Product' */
    FOC_fastCTRL_B->Product_i4 = FOC_fastCTRL_B->Saturation1 *
      FOC_fastCTRL_B->Sign_m;

    /* Sum: '<S7>/Sum1' incorporates:
     *  Constant: '<S7>/FOC_6ph_AngleShift'
     */
    FOC_fastCTRL_B->Sum1_c = FOC_fastCTRL_B->Add +
      FOC_fastCTRL_P.FOC_6ph_AngleShift;

    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S7>/Uf_Ud'
     */
    FOC_fastCTRL_B->SelectControlMode[0] = FOC_fastCTRL_P.FOC_Uf_Ud;
    FOC_fastCTRL_B->SelectControlMode[1] = FOC_fastCTRL_B->Product_i4;
    FOC_fastCTRL_B->SelectControlMode[2] = FOC_fastCTRL_P.FOC_Uf_Ud;
    FOC_fastCTRL_B->SelectControlMode[3] = FOC_fastCTRL_B->Product_i4;
    FOC_fastCTRL_B->SelectControlMode[4] = FOC_fastCTRL_B->Add;
    FOC_fastCTRL_B->SelectControlMode[5] = FOC_fastCTRL_B->Sum1_c;
    break;

   default:
    /* Switch: '<S41>/IntegEnaSwitch1' incorporates:
     *  Switch: '<S45>/IntegEnaSwitch1'
     */
    if (FOC_fastCTRL_B->LogicalOperator1) {
      /* Product: '<S41>/Product2' */
      FOC_fastCTRL_B->Product2_b[0] = FOC_fastCTRL_B->IntegDelay1[0] *
        FOC_fastCTRL_B->Product1_f;

      /* Sum: '<S41>/IntSum1' */
      FOC_fastCTRL_B->IntSum1_f[0] = FOC_fastCTRL_B->KPek1[0] +
        FOC_fastCTRL_B->Product2_b[0];

      /* Switch: '<S41>/IntegEnaSwitch1' */
      FOC_fastCTRL_B->IntegEnaSwitch1[0] = FOC_fastCTRL_B->IntSum1_f[0];

      /* Product: '<S41>/Product2' */
      FOC_fastCTRL_B->Product2_b[1] = FOC_fastCTRL_B->IntegDelay1[1] *
        FOC_fastCTRL_B->Product1_f;

      /* Sum: '<S41>/IntSum1' */
      FOC_fastCTRL_B->IntSum1_f[1] = FOC_fastCTRL_B->KPek1[1] +
        FOC_fastCTRL_B->Product2_b[1];

      /* Switch: '<S41>/IntegEnaSwitch1' */
      FOC_fastCTRL_B->IntegEnaSwitch1[1] = FOC_fastCTRL_B->IntSum1_f[1];

      /* Product: '<S45>/Product2' */
      FOC_fastCTRL_B->Product2_e[0] = FOC_fastCTRL_B->IntegDelay1_b[0] *
        FOC_fastCTRL_B->Product1_p;

      /* Sum: '<S45>/IntSum1' */
      FOC_fastCTRL_B->IntSum1[0] = FOC_fastCTRL_B->KPek1_a[0] +
        FOC_fastCTRL_B->Product2_e[0];

      /* Switch: '<S45>/IntegEnaSwitch1' */
      FOC_fastCTRL_B->IntegEnaSwitch1_m[0] = FOC_fastCTRL_B->IntSum1[0];

      /* Product: '<S45>/Product2' */
      FOC_fastCTRL_B->Product2_e[1] = FOC_fastCTRL_B->IntegDelay1_b[1] *
        FOC_fastCTRL_B->Product1_p;

      /* Sum: '<S45>/IntSum1' */
      FOC_fastCTRL_B->IntSum1[1] = FOC_fastCTRL_B->KPek1_a[1] +
        FOC_fastCTRL_B->Product2_e[1];

      /* Switch: '<S45>/IntegEnaSwitch1' */
      FOC_fastCTRL_B->IntegEnaSwitch1_m[1] = FOC_fastCTRL_B->IntSum1[1];
    } else {
      /* Switch: '<S41>/IntegEnaSwitch1' incorporates:
       *  Constant: '<S41>/Zero'
       */
      FOC_fastCTRL_B->IntegEnaSwitch1[0] = FOC_fastCTRL_P.Zero_Value;
      FOC_fastCTRL_B->IntegEnaSwitch1[1] = FOC_fastCTRL_P.Zero_Value;

      /* Switch: '<S45>/IntegEnaSwitch1' incorporates:
       *  Constant: '<S45>/Zero'
       */
      FOC_fastCTRL_B->IntegEnaSwitch1_m[0] = FOC_fastCTRL_P.Zero_Value_j;
      FOC_fastCTRL_B->IntegEnaSwitch1_m[1] = FOC_fastCTRL_P.Zero_Value_j;
    }

    /* End of Switch: '<S41>/IntegEnaSwitch1' */

    /* Sum: '<S5>/Sum2' incorporates:
     *  Constant: '<S5>/FOC_6ph_AngleShift'
     */
    FOC_fastCTRL_B->Sum2_e = FOC_fastCTRL_B->Switch2_e +
      FOC_fastCTRL_P.FOC_6ph_AngleShift;

    /* MultiPortSwitch: '<S1>/SelectControlMode' */
    FOC_fastCTRL_B->SelectControlMode[0] = FOC_fastCTRL_B->IntegEnaSwitch1[0];
    FOC_fastCTRL_B->SelectControlMode[2] = FOC_fastCTRL_B->IntegEnaSwitch1_m[0];
    FOC_fastCTRL_B->SelectControlMode[1] = FOC_fastCTRL_B->IntegEnaSwitch1[1];
    FOC_fastCTRL_B->SelectControlMode[3] = FOC_fastCTRL_B->IntegEnaSwitch1_m[1];
    FOC_fastCTRL_B->SelectControlMode[4] = FOC_fastCTRL_B->Switch2_e;
    FOC_fastCTRL_B->SelectControlMode[5] = FOC_fastCTRL_B->Sum2_e;
    break;
  }

  /* End of MultiPortSwitch: '<S1>/SelectControlMode' */

  /* Trigonometry: '<S56>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_mr = sin
    (FOC_fastCTRL_B->SelectControlMode[4]);

  /* Trigonometry: '<S56>/Trigonometric Function1' */
  FOC_fastCTRL_B->TrigonometricFunction1_m = cos
    (FOC_fastCTRL_B->SelectControlMode[4]);

  /* Gain: '<S56>/Gain1' */
  FOC_fastCTRL_B->Gain1[0] = FOC_fastCTRL_P.Gain1_Gain_p[0] *
    FOC_fastCTRL_B->TrigonometricFunction_mr;

  /* Gain: '<S56>/Gain' */
  FOC_fastCTRL_B->Gain[0] = FOC_fastCTRL_P.Gain_Gain[0] *
    FOC_fastCTRL_B->TrigonometricFunction1_m;

  /* Sum: '<S56>/Sum1' incorporates:
   *  Gain: '<S56>/Gain'
   *  Gain: '<S56>/Gain1'
   */
  FOC_fastCTRL_B->Sum1_b[0] = FOC_fastCTRL_B->Gain1[0] + FOC_fastCTRL_B->Gain[0];

  /* Product: '<S56>/Product' incorporates:
   *  Sum: '<S56>/Sum1'
   */
  maxV = FOC_fastCTRL_B->Sum1_b[0];

  /* Gain: '<S56>/Gain1' */
  FOC_fastCTRL_B->Gain1[1] = FOC_fastCTRL_P.Gain1_Gain_p[1] *
    FOC_fastCTRL_B->TrigonometricFunction_mr;

  /* Gain: '<S56>/Gain' */
  FOC_fastCTRL_B->Gain[1] = FOC_fastCTRL_P.Gain_Gain[1] *
    FOC_fastCTRL_B->TrigonometricFunction1_m;

  /* Sum: '<S56>/Sum1' incorporates:
   *  Gain: '<S56>/Gain'
   *  Gain: '<S56>/Gain1'
   */
  FOC_fastCTRL_B->Sum1_b[1] = FOC_fastCTRL_B->Gain1[1] + FOC_fastCTRL_B->Gain[1];

  /* Product: '<S56>/Product' incorporates:
   *  Sum: '<S56>/Sum1'
   */
  tmp_2 = FOC_fastCTRL_B->Sum1_b[1];

  /* Gain: '<S56>/Gain1' */
  FOC_fastCTRL_B->Gain1[2] = FOC_fastCTRL_P.Gain1_Gain_p[2] *
    FOC_fastCTRL_B->TrigonometricFunction_mr;

  /* Gain: '<S56>/Gain' */
  FOC_fastCTRL_B->Gain[2] = FOC_fastCTRL_P.Gain_Gain[2] *
    FOC_fastCTRL_B->TrigonometricFunction1_m;

  /* Sum: '<S56>/Sum1' incorporates:
   *  Gain: '<S56>/Gain'
   *  Gain: '<S56>/Gain1'
   */
  FOC_fastCTRL_B->Sum1_b[2] = FOC_fastCTRL_B->Gain1[2] + FOC_fastCTRL_B->Gain[2];

  /* Product: '<S56>/Product' incorporates:
   *  Sum: '<S56>/Sum1'
   */
  tmp_1 = FOC_fastCTRL_B->Sum1_b[2];

  /* Gain: '<S56>/Gain1' */
  FOC_fastCTRL_B->Gain1[3] = FOC_fastCTRL_P.Gain1_Gain_p[3] *
    FOC_fastCTRL_B->TrigonometricFunction_mr;

  /* Gain: '<S56>/Gain' */
  FOC_fastCTRL_B->Gain[3] = FOC_fastCTRL_P.Gain_Gain[3] *
    FOC_fastCTRL_B->TrigonometricFunction1_m;

  /* Sum: '<S56>/Sum1' incorporates:
   *  Gain: '<S56>/Gain'
   *  Gain: '<S56>/Gain1'
   */
  FOC_fastCTRL_B->Sum1_b[3] = FOC_fastCTRL_B->Gain1[3] + FOC_fastCTRL_B->Gain[3];

  /* Product: '<S56>/Product' incorporates:
   *  Sum: '<S56>/Sum1'
   */
  tmp_3 = FOC_fastCTRL_B->Sum1_b[3];
  u = FOC_fastCTRL_B->SelectControlMode[0];
  tmp_0 = FOC_fastCTRL_B->SelectControlMode[1];
  maxV *= u;
  maxV += tmp_1 * tmp_0;

  /* Product: '<S56>/Product' */
  FOC_fastCTRL_B->Product_i[0] = maxV;

  /* Product: '<S56>/Product' */
  tmp_2 *= u;
  tmp_2 += tmp_3 * tmp_0;

  /* Product: '<S56>/Product' */
  FOC_fastCTRL_B->Product_i[1] = tmp_2;

  /* Product: '<S54>/Product' incorporates:
   *  Constant: '<S54>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_fastCTRL_P.Constant_Value_i[i_0];
  }

  u = FOC_fastCTRL_B->Product_i[0];
  tmp_0 = FOC_fastCTRL_B->Product_i[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    maxV = tmp[i_0] * u;
    maxV += tmp[i_0 + 3] * tmp_0;

    /* Product: '<S54>/Product' */
    FOC_fastCTRL_B->Product_hu[i_0] = maxV;
  }

  /* End of Product: '<S54>/Product' */

  /* Trigonometry: '<S57>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_o = sin
    (FOC_fastCTRL_B->SelectControlMode[5]);

  /* Trigonometry: '<S57>/Trigonometric Function1' */
  FOC_fastCTRL_B->TrigonometricFunction1_j = cos
    (FOC_fastCTRL_B->SelectControlMode[5]);

  /* Gain: '<S57>/Gain1' */
  FOC_fastCTRL_B->Gain1_j[0] = FOC_fastCTRL_P.Gain1_Gain_k[0] *
    FOC_fastCTRL_B->TrigonometricFunction_o;

  /* Gain: '<S57>/Gain' */
  FOC_fastCTRL_B->Gain_f[0] = FOC_fastCTRL_P.Gain_Gain_d[0] *
    FOC_fastCTRL_B->TrigonometricFunction1_j;

  /* Sum: '<S57>/Sum1' incorporates:
   *  Gain: '<S57>/Gain'
   *  Gain: '<S57>/Gain1'
   */
  FOC_fastCTRL_B->Sum1_bx[0] = FOC_fastCTRL_B->Gain1_j[0] +
    FOC_fastCTRL_B->Gain_f[0];

  /* Product: '<S57>/Product' incorporates:
   *  Sum: '<S57>/Sum1'
   */
  maxV = FOC_fastCTRL_B->Sum1_bx[0];

  /* Gain: '<S57>/Gain1' */
  FOC_fastCTRL_B->Gain1_j[1] = FOC_fastCTRL_P.Gain1_Gain_k[1] *
    FOC_fastCTRL_B->TrigonometricFunction_o;

  /* Gain: '<S57>/Gain' */
  FOC_fastCTRL_B->Gain_f[1] = FOC_fastCTRL_P.Gain_Gain_d[1] *
    FOC_fastCTRL_B->TrigonometricFunction1_j;

  /* Sum: '<S57>/Sum1' incorporates:
   *  Gain: '<S57>/Gain'
   *  Gain: '<S57>/Gain1'
   */
  FOC_fastCTRL_B->Sum1_bx[1] = FOC_fastCTRL_B->Gain1_j[1] +
    FOC_fastCTRL_B->Gain_f[1];

  /* Product: '<S57>/Product' incorporates:
   *  Sum: '<S57>/Sum1'
   */
  tmp_2 = FOC_fastCTRL_B->Sum1_bx[1];

  /* Gain: '<S57>/Gain1' */
  FOC_fastCTRL_B->Gain1_j[2] = FOC_fastCTRL_P.Gain1_Gain_k[2] *
    FOC_fastCTRL_B->TrigonometricFunction_o;

  /* Gain: '<S57>/Gain' */
  FOC_fastCTRL_B->Gain_f[2] = FOC_fastCTRL_P.Gain_Gain_d[2] *
    FOC_fastCTRL_B->TrigonometricFunction1_j;

  /* Sum: '<S57>/Sum1' incorporates:
   *  Gain: '<S57>/Gain'
   *  Gain: '<S57>/Gain1'
   */
  FOC_fastCTRL_B->Sum1_bx[2] = FOC_fastCTRL_B->Gain1_j[2] +
    FOC_fastCTRL_B->Gain_f[2];

  /* Product: '<S57>/Product' incorporates:
   *  Sum: '<S57>/Sum1'
   */
  tmp_1 = FOC_fastCTRL_B->Sum1_bx[2];

  /* Gain: '<S57>/Gain1' */
  FOC_fastCTRL_B->Gain1_j[3] = FOC_fastCTRL_P.Gain1_Gain_k[3] *
    FOC_fastCTRL_B->TrigonometricFunction_o;

  /* Gain: '<S57>/Gain' */
  FOC_fastCTRL_B->Gain_f[3] = FOC_fastCTRL_P.Gain_Gain_d[3] *
    FOC_fastCTRL_B->TrigonometricFunction1_j;

  /* Sum: '<S57>/Sum1' incorporates:
   *  Gain: '<S57>/Gain'
   *  Gain: '<S57>/Gain1'
   */
  FOC_fastCTRL_B->Sum1_bx[3] = FOC_fastCTRL_B->Gain1_j[3] +
    FOC_fastCTRL_B->Gain_f[3];

  /* Product: '<S57>/Product' incorporates:
   *  Sum: '<S57>/Sum1'
   */
  tmp_3 = FOC_fastCTRL_B->Sum1_bx[3];
  u = FOC_fastCTRL_B->SelectControlMode[2];
  tmp_0 = FOC_fastCTRL_B->SelectControlMode[3];
  maxV *= u;
  maxV += tmp_1 * tmp_0;

  /* Product: '<S57>/Product' */
  FOC_fastCTRL_B->Product_p[0] = maxV;

  /* Product: '<S57>/Product' */
  tmp_2 *= u;
  tmp_2 += tmp_3 * tmp_0;

  /* Product: '<S57>/Product' */
  FOC_fastCTRL_B->Product_p[1] = tmp_2;

  /* Product: '<S55>/Product' incorporates:
   *  Constant: '<S55>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_fastCTRL_P.Constant_Value_a[i_0];
  }

  u = FOC_fastCTRL_B->Product_p[0];
  tmp_0 = FOC_fastCTRL_B->Product_p[1];

  /* Switch: '<S1>/Switch1' incorporates:
   *  Constant: '<S1>/0: P_Udc 1: Udc_measured'
   */
  if (FOC_fastCTRL_P.FOC_SELECT_U_DC_INPUT > FOC_fastCTRL_P.Switch1_Threshold_l)
  {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Inport: '<Root>/U_DC [V]'
     */
    FOC_U_DC = FOC_fastCTRL_U->U_DCV;
  } else {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Udc1'
     */
    FOC_U_DC = FOC_fastCTRL_P.FOC_MANUAL_U_DC;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Outputs for Atomic SubSystem: '<S8>/NormalizedVoltage' */
  /* Gain: '<S52>/U_DC//2' */
  FOC_fastCTRL_B->U_DC2 = FOC_fastCTRL_P.U_DC2_Gain_k * FOC_U_DC;

  /* MinMax: '<S52>/AvoidDivBy0' incorporates:
   *  Constant: '<S52>/Constant2'
   */
  maxV = fmax(FOC_fastCTRL_P.Constant2_Value_mf, FOC_fastCTRL_B->U_DC2);

  /* MinMax: '<S52>/AvoidDivBy0' */
  FOC_fastCTRL_B->AvoidDivBy0 = maxV;
  for (i = 0; i < 3; i++) {
    /* Product: '<S55>/Product' */
    maxV = tmp[i] * u;
    maxV += tmp[i + 3] * tmp_0;

    /* Product: '<S55>/Product' */
    FOC_fastCTRL_B->Product_b[i] = maxV;

    /* Product: '<S52>/Divide3' */
    FOC_fastCTRL_B->Divide3[i] = FOC_fastCTRL_B->Product_hu[i] /
      FOC_fastCTRL_B->AvoidDivBy0;
    FOC_fastCTRL_B->Divide3[i + 3] = FOC_fastCTRL_B->Product_b[i] /
      FOC_fastCTRL_B->AvoidDivBy0;
  }

  /* End of Outputs for SubSystem: '<S8>/NormalizedVoltage' */

  /* Switch: '<S2>/AKS_Switch' */
  if (FOC_fastCTRL_B->LogicalOperator1) {
    /* MultiPortSwitch: '<S8>/SelectModulation' incorporates:
     *  Constant: '<S8>/Enable_SuperSinMod'
     */
    if ((int32_T)FOC_fastCTRL_P.FOC_SELECT_Modulation == 0) {
      /* MultiPortSwitch: '<S8>/SelectModulation' */
      for (i = 0; i < 6; i++) {
        FOC_fastCTRL_B->SelectModulation[i] = FOC_fastCTRL_B->Divide3[i];
      }
    } else {
      /* Outputs for Atomic SubSystem: '<S8>/Super_Sinus_Modulation' */
      /* MinMax: '<S53>/MinMax2' */
      maxV = FOC_fastCTRL_B->Divide3[0];
      maxV = fmin(maxV, FOC_fastCTRL_B->Divide3[1]);
      maxV = fmin(maxV, FOC_fastCTRL_B->Divide3[2]);

      /* MinMax: '<S53>/MinMax2' */
      FOC_fastCTRL_B->MinMax2 = maxV;

      /* MinMax: '<S53>/MinMax3' */
      maxV = FOC_fastCTRL_B->Divide3[0];
      maxV = fmax(maxV, FOC_fastCTRL_B->Divide3[1]);
      maxV = fmax(maxV, FOC_fastCTRL_B->Divide3[2]);

      /* MinMax: '<S53>/MinMax3' */
      FOC_fastCTRL_B->MinMax3 = maxV;

      /* Sum: '<S53>/Sum1' */
      FOC_fastCTRL_B->Sum1_nk = FOC_fastCTRL_B->MinMax2 +
        FOC_fastCTRL_B->MinMax3;

      /* Gain: '<S53>/Factor' */
      FOC_fastCTRL_B->Factor = FOC_fastCTRL_P.Factor_Gain *
        FOC_fastCTRL_B->Sum1_nk;

      /* MinMax: '<S53>/MinMax1' */
      maxV = FOC_fastCTRL_B->Divide3[3];
      maxV = fmin(maxV, FOC_fastCTRL_B->Divide3[4]);
      maxV = fmin(maxV, FOC_fastCTRL_B->Divide3[5]);

      /* MinMax: '<S53>/MinMax1' */
      FOC_fastCTRL_B->MinMax1 = maxV;

      /* MinMax: '<S53>/MinMax4' */
      maxV = FOC_fastCTRL_B->Divide3[3];
      maxV = fmax(maxV, FOC_fastCTRL_B->Divide3[4]);
      maxV = fmax(maxV, FOC_fastCTRL_B->Divide3[5]);

      /* MinMax: '<S53>/MinMax4' */
      FOC_fastCTRL_B->MinMax4 = maxV;

      /* Sum: '<S53>/Sum2' */
      FOC_fastCTRL_B->Sum2_b = FOC_fastCTRL_B->MinMax1 + FOC_fastCTRL_B->MinMax4;

      /* Gain: '<S53>/Factor1' */
      FOC_fastCTRL_B->Factor1 = FOC_fastCTRL_P.Factor1_Gain *
        FOC_fastCTRL_B->Sum2_b;

      /* Sum: '<S53>/Sum3' */
      FOC_fastCTRL_B->Sum3_f[0] = FOC_fastCTRL_B->Divide3[0] -
        FOC_fastCTRL_B->Factor;

      /* Sum: '<S53>/Sum4' */
      FOC_fastCTRL_B->Sum4_p[0] = FOC_fastCTRL_B->Divide3[3] -
        FOC_fastCTRL_B->Factor1;

      /* End of Outputs for SubSystem: '<S8>/Super_Sinus_Modulation' */

      /* MultiPortSwitch: '<S8>/SelectModulation' */
      FOC_fastCTRL_B->SelectModulation[0] = FOC_fastCTRL_B->Sum3_f[0];
      FOC_fastCTRL_B->SelectModulation[3] = FOC_fastCTRL_B->Sum4_p[0];

      /* Outputs for Atomic SubSystem: '<S8>/Super_Sinus_Modulation' */
      /* Sum: '<S53>/Sum3' */
      FOC_fastCTRL_B->Sum3_f[1] = FOC_fastCTRL_B->Divide3[1] -
        FOC_fastCTRL_B->Factor;

      /* Sum: '<S53>/Sum4' */
      FOC_fastCTRL_B->Sum4_p[1] = FOC_fastCTRL_B->Divide3[4] -
        FOC_fastCTRL_B->Factor1;

      /* End of Outputs for SubSystem: '<S8>/Super_Sinus_Modulation' */

      /* MultiPortSwitch: '<S8>/SelectModulation' */
      FOC_fastCTRL_B->SelectModulation[1] = FOC_fastCTRL_B->Sum3_f[1];
      FOC_fastCTRL_B->SelectModulation[4] = FOC_fastCTRL_B->Sum4_p[1];

      /* Outputs for Atomic SubSystem: '<S8>/Super_Sinus_Modulation' */
      /* Sum: '<S53>/Sum3' */
      FOC_fastCTRL_B->Sum3_f[2] = FOC_fastCTRL_B->Divide3[2] -
        FOC_fastCTRL_B->Factor;

      /* Sum: '<S53>/Sum4' */
      FOC_fastCTRL_B->Sum4_p[2] = FOC_fastCTRL_B->Divide3[5] -
        FOC_fastCTRL_B->Factor1;

      /* End of Outputs for SubSystem: '<S8>/Super_Sinus_Modulation' */

      /* MultiPortSwitch: '<S8>/SelectModulation' */
      FOC_fastCTRL_B->SelectModulation[2] = FOC_fastCTRL_B->Sum3_f[2];
      FOC_fastCTRL_B->SelectModulation[5] = FOC_fastCTRL_B->Sum4_p[2];
    }

    /* End of MultiPortSwitch: '<S8>/SelectModulation' */
    for (i = 0; i < 6; i++) {
      /* Bias: '<S50>/[0..2]' */
      FOC_fastCTRL_B->u2[i] = FOC_fastCTRL_B->SelectModulation[i] +
        FOC_fastCTRL_P.u2_Bias;

      /* Gain: '<S50>/[0..1]' */
      FOC_fastCTRL_B->u1[i] = FOC_fastCTRL_P.u1_Gain * FOC_fastCTRL_B->u2[i];

      /* Saturate: '<S50>/Limit [0..1]' */
      u = FOC_fastCTRL_B->u1[i];
      if (u > FOC_fastCTRL_P.Limit01_UpperSat) {
        u = FOC_fastCTRL_P.Limit01_UpperSat;
      } else if (u < FOC_fastCTRL_P.Limit01_LowerSat) {
        u = FOC_fastCTRL_P.Limit01_LowerSat;
      }

      /* Saturate: '<S50>/Limit [0..1]' */
      FOC_fastCTRL_B->Limit01[i] = u;

      /* Outport: '<Root>/DutyCycles [0..1]' */
      FOC_fastCTRL_Y->DutyCycles01[i] = FOC_fastCTRL_B->Limit01[i];
    }
  } else {
    /* MultiPortSwitch: '<S2>/AKS Switch' incorporates:
     *  Constant: '<S2>/FOC_AKS_Mode'
     */
    switch ((int32_T)FOC_fastCTRL_P.FOC_AKS_Mode) {
     case 1:
      /* MultiPortSwitch: '<S2>/AKS Switch' incorporates:
       *  Constant: '<S2>/AKS_LS'
       */
      for (i = 0; i < 6; i++) {
        FOC_fastCTRL_B->AKSSwitch[i] = FOC_fastCTRL_P.AKS_LS_Value[i];
      }
      break;

     case 2:
      /* MultiPortSwitch: '<S2>/AKS Switch' incorporates:
       *  Constant: '<S2>/AKS_HS'
       */
      for (i = 0; i < 6; i++) {
        FOC_fastCTRL_B->AKSSwitch[i] = FOC_fastCTRL_P.AKS_HS_Value[i];
      }
      break;

     case 3:
      /* MultiPortSwitch: '<S2>/AKS Switch' incorporates:
       *  Constant: '<S2>/AKS_LSHS'
       */
      for (i = 0; i < 6; i++) {
        FOC_fastCTRL_B->AKSSwitch[i] = FOC_fastCTRL_P.AKS_LSHS_Value[i];
      }
      break;

     default:
      /* MultiPortSwitch: '<S2>/AKS Switch' incorporates:
       *  Constant: '<S2>/DutyCycle1_ManualMode'
       *  Constant: '<S2>/DutyCycle2_ManualMode'
       *  Constant: '<S2>/DutyCycle3_ManualMode'
       *  Constant: '<S2>/DutyCycle4_ManualMode'
       *  Constant: '<S2>/DutyCycle5_ManualMode'
       *  Constant: '<S2>/DutyCycle6_ManualMode'
       */
      FOC_fastCTRL_B->AKSSwitch[0] = FOC_fastCTRL_P.DutyCycle_1;
      FOC_fastCTRL_B->AKSSwitch[1] = FOC_fastCTRL_P.DutyCycle_2;
      FOC_fastCTRL_B->AKSSwitch[2] = FOC_fastCTRL_P.DutyCycle_3;
      FOC_fastCTRL_B->AKSSwitch[3] = FOC_fastCTRL_P.DutyCycle_4;
      FOC_fastCTRL_B->AKSSwitch[4] = FOC_fastCTRL_P.DutyCycle_5;
      FOC_fastCTRL_B->AKSSwitch[5] = FOC_fastCTRL_P.DutyCycle_6;
      break;
    }

    /* End of MultiPortSwitch: '<S2>/AKS Switch' */

    /* Outport: '<Root>/DutyCycles [0..1]' */
    for (i = 0; i < 6; i++) {
      FOC_fastCTRL_Y->DutyCycles01[i] = FOC_fastCTRL_B->AKSSwitch[i];
    }
  }

  /* End of Switch: '<S2>/AKS_Switch' */

  /* Gain: '<S3>/Gain2' */
  FOC_AngleEst_w_el = FOC_fastCTRL_P.Gain2_Gain * FOC_fastCTRL_B->Switch_speed;

  /* Gain: '<S3>/Gain3' */
  FOC_AngleEst_Psi_PM_alpha = FOC_fastCTRL_P.Gain3_Gain *
    FOC_fastCTRL_B->psi_PM_alphabeta[0];

  /* Gain: '<S3>/Gain4' */
  FOC_AngleEst_Psi_PM_beta = FOC_fastCTRL_P.Gain4_Gain *
    FOC_fastCTRL_B->psi_PM_alphabeta[1];

  /* Product: '<S12>/T_ab' incorporates:
   *  Constant: '<S12>/Constant'
   *  Constant: '<S12>/FOC_f_fast'
   */
  FOC_fastCTRL_B->T_ab = FOC_fastCTRL_P.Constant_Value_e /
    FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Sum: '<S12>/Sum1' incorporates:
   *  Constant: '<S12>/Tau'
   */
  FOC_fastCTRL_B->Sum1_bh = FOC_fastCTRL_P.FOC_AngleEst_w_el_filtered_Tau -
    FOC_fastCTRL_B->T_ab;

  /* Product: '<S12>/Divide' incorporates:
   *  Constant: '<S12>/Tau'
   */
  FOC_fastCTRL_B->Divide = FOC_fastCTRL_B->UnitDelay_n * FOC_fastCTRL_B->Sum1_bh
    / FOC_fastCTRL_P.FOC_AngleEst_w_el_filtered_Tau;

  /* Product: '<S12>/Divide2' incorporates:
   *  Constant: '<S12>/Tau'
   */
  FOC_fastCTRL_B->Divide2 = FOC_fastCTRL_B->T_ab /
    FOC_fastCTRL_P.FOC_AngleEst_w_el_filtered_Tau;

  /* Product: '<S12>/Product3' */
  FOC_fastCTRL_B->Product3_h = FOC_fastCTRL_B->Switch_speed *
    FOC_fastCTRL_B->Divide2;

  /* Sum: '<S12>/Sum' */
  FOC_fastCTRL_B->Sum_p = FOC_fastCTRL_B->Product3_h + FOC_fastCTRL_B->Divide;

  /* Product: '<S3>/Product2' incorporates:
   *  Constant: '<S3>/FOC_AngleEst_Rs'
   */
  FOC_fastCTRL_B->Product2[0] = FOC_fastCTRL_P.FOC_AngleEst_Rs *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[0];
  FOC_fastCTRL_B->Product2[1] = FOC_fastCTRL_P.FOC_AngleEst_Rs *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[1];

  /* Product: '<S15>/Product' incorporates:
   *  Constant: '<S15>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S16>/Product' incorporates:
   *  Constant: '<S3>/komp_kp'
   */
  FOC_fastCTRL_B->Product_g[0] = FOC_fastCTRL_B->psi_PM_alphabeta[0] *
    FOC_fastCTRL_P.FOC_AngleEst_Komp_KP;

  /* UnitDelay: '<S14>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_l[0] = FOC_fastCTRL_DW->UnitDelay_DSTATE_o[0];

  /* UnitDelay: '<S14>/Unit Delay1' */
  FOC_fastCTRL_B->UnitDelay1_j[0] = FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[0];

  /* Switch: '<S14>/Switch4' incorporates:
   *  Constant: '<S14>/FOC_AngleEst_Delay1'
   */
  if (FOC_fastCTRL_P.FOC_AngleEst_Delay1 > FOC_fastCTRL_P.Switch4_Threshold) {
    /* Switch: '<S14>/Switch4' */
    FOC_fastCTRL_B->Switch4[0] = FOC_fastCTRL_B->UnitDelay1_j[0];
  } else {
    /* Switch: '<S14>/Switch4' */
    FOC_fastCTRL_B->Switch4[0] = FOC_fastCTRL_B->Product_i[0];
  }

  /* Switch: '<S14>/Switch3' incorporates:
   *  Constant: '<S14>/FOC_AngleEst_Delay2'
   */
  if (FOC_fastCTRL_P.FOC_AngleEst_Delay2 > FOC_fastCTRL_P.Switch3_Threshold) {
    /* Switch: '<S14>/Switch3' */
    FOC_fastCTRL_B->Switch3[0] = FOC_fastCTRL_B->UnitDelay_l[0];
  } else {
    /* Switch: '<S14>/Switch3' */
    FOC_fastCTRL_B->Switch3[0] = FOC_fastCTRL_B->Switch4[0];
  }

  /* Sum: '<S3>/Sum' */
  FOC_fastCTRL_B->Sum_ey[0] = (FOC_fastCTRL_B->Switch3[0] -
    FOC_fastCTRL_B->Product_g[0]) - FOC_fastCTRL_B->Product2[0];

  /* Product: '<S15>/Product' */
  FOC_fastCTRL_B->Product_bg[0] = FOC_fastCTRL_B->Sum_ey[0] * maxV;

  /* Sum: '<S15>/Sum4' */
  FOC_fastCTRL_B->Sum4[0] = FOC_fastCTRL_B->Product_bg[0] +
    FOC_fastCTRL_B->UnitDelay_b[0];

  /* UnitDelay: '<S22>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_lj[0] = FOC_fastCTRL_DW->UnitDelay_DSTATE_e[0];

  /* Product: '<S4>/Product3' incorporates:
   *  Constant: '<S4>/FOC_AngleEst_Lq'
   */
  FOC_fastCTRL_B->Product3_c[0] = FOC_fastCTRL_P.FOC_AngleEst_Lq *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[0];

  /* Sum: '<S4>/Sum1' */
  FOC_fastCTRL_B->psi_PM_alphabeta_n[0] = FOC_fastCTRL_B->UnitDelay_lj[0] -
    FOC_fastCTRL_B->Product3_c[0];

  /* Product: '<S16>/Product' incorporates:
   *  Constant: '<S3>/komp_kp'
   */
  FOC_fastCTRL_B->Product_g[1] = FOC_fastCTRL_B->psi_PM_alphabeta[1] *
    FOC_fastCTRL_P.FOC_AngleEst_Komp_KP;

  /* UnitDelay: '<S14>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_l[1] = FOC_fastCTRL_DW->UnitDelay_DSTATE_o[1];

  /* UnitDelay: '<S14>/Unit Delay1' */
  FOC_fastCTRL_B->UnitDelay1_j[1] = FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[1];

  /* Switch: '<S14>/Switch4' incorporates:
   *  Constant: '<S14>/FOC_AngleEst_Delay1'
   */
  if (FOC_fastCTRL_P.FOC_AngleEst_Delay1 > FOC_fastCTRL_P.Switch4_Threshold) {
    /* Switch: '<S14>/Switch4' */
    FOC_fastCTRL_B->Switch4[1] = FOC_fastCTRL_B->UnitDelay1_j[1];
  } else {
    /* Switch: '<S14>/Switch4' */
    FOC_fastCTRL_B->Switch4[1] = FOC_fastCTRL_B->Product_i[1];
  }

  /* Switch: '<S14>/Switch3' incorporates:
   *  Constant: '<S14>/FOC_AngleEst_Delay2'
   */
  if (FOC_fastCTRL_P.FOC_AngleEst_Delay2 > FOC_fastCTRL_P.Switch3_Threshold) {
    /* Switch: '<S14>/Switch3' */
    FOC_fastCTRL_B->Switch3[1] = FOC_fastCTRL_B->UnitDelay_l[1];
  } else {
    /* Switch: '<S14>/Switch3' */
    FOC_fastCTRL_B->Switch3[1] = FOC_fastCTRL_B->Switch4[1];
  }

  /* Sum: '<S3>/Sum' */
  FOC_fastCTRL_B->Sum_ey[1] = (FOC_fastCTRL_B->Switch3[1] -
    FOC_fastCTRL_B->Product_g[1]) - FOC_fastCTRL_B->Product2[1];

  /* Product: '<S15>/Product' */
  FOC_fastCTRL_B->Product_bg[1] = FOC_fastCTRL_B->Sum_ey[1] * maxV;

  /* Sum: '<S15>/Sum4' */
  FOC_fastCTRL_B->Sum4[1] = FOC_fastCTRL_B->Product_bg[1] +
    FOC_fastCTRL_B->UnitDelay_b[1];

  /* UnitDelay: '<S22>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_lj[1] = FOC_fastCTRL_DW->UnitDelay_DSTATE_e[1];

  /* Product: '<S4>/Product3' incorporates:
   *  Constant: '<S4>/FOC_AngleEst_Lq'
   */
  FOC_fastCTRL_B->Product3_c[1] = FOC_fastCTRL_P.FOC_AngleEst_Lq *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[1];

  /* Sum: '<S4>/Sum1' */
  FOC_fastCTRL_B->psi_PM_alphabeta_n[1] = FOC_fastCTRL_B->UnitDelay_lj[1] -
    FOC_fastCTRL_B->Product3_c[1];

  /* Trigonometry: '<S18>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_a = rt_atan2d_snf
    (FOC_fastCTRL_B->psi_PM_alphabeta_n[1], FOC_fastCTRL_B->psi_PM_alphabeta_n[0]);

  /* Switch: '<S18>/Switch_Phi' */
  if (FOC_fastCTRL_B->TrigonometricFunction_a >
      FOC_fastCTRL_P.Switch_Phi_Threshold_m) {
    /* Switch: '<S18>/Switch_Phi' */
    FOC_fastCTRL_B->Switch_Phi_a = FOC_fastCTRL_B->TrigonometricFunction_a;
  } else {
    /* Sum: '<S18>/Sum1' incorporates:
     *  Constant: '<S18>/Constant'
     */
    FOC_fastCTRL_B->Sum1_ce = FOC_fastCTRL_B->TrigonometricFunction_a +
      FOC_fastCTRL_P.Constant_Value_o;

    /* Switch: '<S18>/Switch_Phi' */
    FOC_fastCTRL_B->Switch_Phi_a = FOC_fastCTRL_B->Sum1_ce;
  }

  /* End of Switch: '<S18>/Switch_Phi' */

  /* UnitDelay: '<S19>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_h = FOC_fastCTRL_DW->UnitDelay_DSTATE_b;

  /* Product: '<S20>/Product' incorporates:
   *  Constant: '<S20>/FOC_f_fastCTRL'
   */
  FOC_fastCTRL_B->Product_e = FOC_fastCTRL_B->Switch_Phi_a *
    FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn' */
  maxV = FOC_fastCTRL_B->Product_e;
  maxV -= FOC_fastCTRL_P.DiscreteTransferFcn_DenCoef_a[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn_states_j;
  maxV /= FOC_fastCTRL_P.DiscreteTransferFcn_DenCoef_a[0];
  FOC_fastCTRL_DW->DiscreteTransferFcn_tmp_g = maxV;
  maxV = FOC_fastCTRL_P.DiscreteTransferFcn_NumCoef_i[0] *
    FOC_fastCTRL_DW->DiscreteTransferFcn_tmp_g;
  maxV += FOC_fastCTRL_P.DiscreteTransferFcn_NumCoef_i[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn_states_j;

  /* DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn' */
  FOC_fastCTRL_B->DiscreteTransferFcn_m = maxV;

  /* RelationalOperator: '<S20>/Relational Operator' incorporates:
   *  Constant: '<S20>/Constant'
   */
  FOC_fastCTRL_B->RelationalOperator_o = (FOC_fastCTRL_B->Switch_Phi_a <
    FOC_fastCTRL_P.Constant_Value_ip);

  /* RelationalOperator: '<S20>/Relational Operator1' incorporates:
   *  Constant: '<S20>/Constant1'
   */
  FOC_fastCTRL_B->RelationalOperator1_c = (FOC_fastCTRL_B->Switch_Phi_a >
    FOC_fastCTRL_P.Constant1_Value_e);

  /* Logic: '<S20>/Logical Operator' */
  FOC_fastCTRL_B->LogicalOperator_a = (FOC_fastCTRL_B->RelationalOperator_o &&
    FOC_fastCTRL_B->RelationalOperator1_c);

  /* RelationalOperator: '<S20>/Relational Operator2' incorporates:
   *  Constant: '<S20>/Constant2'
   */
  FOC_fastCTRL_B->RelationalOperator2_n = (FOC_fastCTRL_B->Switch_Phi_a <
    FOC_fastCTRL_P.Constant2_Value_eji);

  /* Switch: '<S20>/Switch1' */
  if (FOC_fastCTRL_B->RelationalOperator2_n) {
    /* Switch: '<S20>/Switch1' */
    FOC_fastCTRL_B->Switch1_n = FOC_fastCTRL_B->Switch_Phi_a;
  } else {
    /* Bias: '<S20>/Bias' */
    FOC_fastCTRL_B->Bias = FOC_fastCTRL_B->Switch_Phi_a +
      FOC_fastCTRL_P.Bias_Bias_m;

    /* Switch: '<S20>/Switch1' */
    FOC_fastCTRL_B->Switch1_n = FOC_fastCTRL_B->Bias;
  }

  /* End of Switch: '<S20>/Switch1' */

  /* Product: '<S20>/Product1' incorporates:
   *  Constant: '<S20>/FOC_f_fastCTRL1'
   */
  FOC_fastCTRL_B->Product1_i = FOC_fastCTRL_B->Switch1_n *
    FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn1' */
  maxV = FOC_fastCTRL_B->Product1_i;
  maxV -= FOC_fastCTRL_P.DiscreteTransferFcn1_DenCoef_f[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn1_states_c;
  maxV /= FOC_fastCTRL_P.DiscreteTransferFcn1_DenCoef_f[0];
  FOC_fastCTRL_DW->DiscreteTransferFcn1_tmp_l = maxV;
  maxV = FOC_fastCTRL_P.DiscreteTransferFcn1_NumCoef_b[0] *
    FOC_fastCTRL_DW->DiscreteTransferFcn1_tmp_l;
  maxV += FOC_fastCTRL_P.DiscreteTransferFcn1_NumCoef_b[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn1_states_c;

  /* DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn1' */
  FOC_fastCTRL_B->DiscreteTransferFcn1_l = maxV;

  /* Switch: '<S20>/Switch_speed' */
  if (FOC_fastCTRL_B->LogicalOperator_a) {
    /* Switch: '<S20>/Switch_speed' */
    FOC_fastCTRL_B->Switch_speed_m = FOC_fastCTRL_B->DiscreteTransferFcn_m;
  } else {
    /* Switch: '<S20>/Switch_speed' */
    FOC_fastCTRL_B->Switch_speed_m = FOC_fastCTRL_B->DiscreteTransferFcn1_l;
  }

  /* End of Switch: '<S20>/Switch_speed' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S4>/useFilteredCorrection'
   */
  if (FOC_fastCTRL_P.FOC_SELECT_AngleEst_w_el_filtered >
      FOC_fastCTRL_P.Switch2_Threshold_p) {
    /* Switch: '<S4>/Switch2' */
    FOC_fastCTRL_B->Switch2_kf = FOC_fastCTRL_B->UnitDelay_h;
  } else {
    /* Switch: '<S4>/Switch2' */
    FOC_fastCTRL_B->Switch2_kf = FOC_fastCTRL_B->Switch_speed_m;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Switch: '<S4>/Switch' */
  if (FOC_fastCTRL_B->Switch2_kf > FOC_fastCTRL_P.Switch_Threshold_j) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S4>/Constant1'
     */
    FOC_fastCTRL_B->Switch_pg = FOC_fastCTRL_P.Constant1_Value_l;
  } else {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S4>/Constant2'
     */
    FOC_fastCTRL_B->Switch_pg = FOC_fastCTRL_P.Constant2_Value_o;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Abs: '<S4>/Abs' */
  FOC_fastCTRL_B->Abs_f = fabs(FOC_fastCTRL_B->Switch2_kf);

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S4>/komp_kp'
   */
  FOC_fastCTRL_B->Product_n = 1.0 / FOC_fastCTRL_P.FOC_AngleEst_Komp_KP *
    FOC_fastCTRL_B->Abs_f;

  /* Trigonometry: '<S4>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_n = atan(FOC_fastCTRL_B->Product_n);

  /* Sum: '<S4>/Sum3' incorporates:
   *  Constant: '<S4>/Constant'
   */
  FOC_fastCTRL_B->Sum3_o = FOC_fastCTRL_P.Constant_Value_cr -
    FOC_fastCTRL_B->TrigonometricFunction_n;

  /* Product: '<S4>/Product1' */
  FOC_fastCTRL_B->Product1_a = FOC_fastCTRL_B->Switch_pg *
    FOC_fastCTRL_B->Sum3_o;

  /* Sum: '<S4>/Sum2' */
  FOC_fastCTRL_B->Sum2_p = FOC_fastCTRL_B->Switch_Phi_a -
    FOC_fastCTRL_B->Product1_a;

  /* Switch: '<S17>/Switch2' */
  if (FOC_fastCTRL_B->Sum2_p >= FOC_fastCTRL_P.Switch2_Threshold_f) {
    /* Switch: '<S17>/Switch2' incorporates:
     *  Constant: '<S17>/Constant1'
     */
    FOC_fastCTRL_B->Switch2_g = FOC_fastCTRL_P.Constant1_Value_f;
  } else {
    /* Switch: '<S17>/Switch2' incorporates:
     *  Constant: '<S17>/Constant'
     */
    FOC_fastCTRL_B->Switch2_g = FOC_fastCTRL_P.Constant_Value_c;
  }

  /* End of Switch: '<S17>/Switch2' */

  /* Switch: '<S17>/Switch1' */
  if (FOC_fastCTRL_B->Sum2_p >= FOC_fastCTRL_P.Switch1_Threshold_l3) {
    /* Switch: '<S17>/Switch1' incorporates:
     *  Constant: '<S17>/Constant2'
     */
    FOC_fastCTRL_B->Switch1_bk = FOC_fastCTRL_P.Constant2_Value_d;
  } else {
    /* Switch: '<S17>/Switch1' incorporates:
     *  Constant: '<S17>/Constant3'
     */
    FOC_fastCTRL_B->Switch1_bk = FOC_fastCTRL_P.Constant3_Value_b;
  }

  /* End of Switch: '<S17>/Switch1' */

  /* Sum: '<S17>/Sum1' */
  FOC_fastCTRL_B->Sum1_n = (FOC_fastCTRL_B->Switch2_g + FOC_fastCTRL_B->Sum2_p)
    + FOC_fastCTRL_B->Switch1_bk;

  /* Product: '<S19>/T_ab' incorporates:
   *  Constant: '<S19>/Constant'
   *  Constant: '<S19>/FOC_f_fast'
   */
  FOC_fastCTRL_B->T_ab_i = FOC_fastCTRL_P.Constant_Value_n2 /
    FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Sum: '<S19>/Sum1' incorporates:
   *  Constant: '<S19>/Tau'
   */
  FOC_fastCTRL_B->Sum1_a = FOC_fastCTRL_P.FOC_AngleEst_w_el_filtered_Tau -
    FOC_fastCTRL_B->T_ab_i;

  /* Product: '<S19>/Divide' incorporates:
   *  Constant: '<S19>/Tau'
   */
  FOC_fastCTRL_B->Divide_l = FOC_fastCTRL_B->UnitDelay_h *
    FOC_fastCTRL_B->Sum1_a / FOC_fastCTRL_P.FOC_AngleEst_w_el_filtered_Tau;

  /* Product: '<S19>/Divide2' incorporates:
   *  Constant: '<S19>/Tau'
   */
  FOC_fastCTRL_B->Divide2_p = FOC_fastCTRL_B->T_ab_i /
    FOC_fastCTRL_P.FOC_AngleEst_w_el_filtered_Tau;

  /* Product: '<S19>/Product3' */
  FOC_fastCTRL_B->Product3_hb = FOC_fastCTRL_B->Switch_speed_m *
    FOC_fastCTRL_B->Divide2_p;

  /* Sum: '<S19>/Sum' */
  FOC_fastCTRL_B->Sum_g = FOC_fastCTRL_B->Product3_hb + FOC_fastCTRL_B->Divide_l;

  /* Product: '<S4>/Product2' incorporates:
   *  Constant: '<S4>/FOC_AngleEst_Rs'
   */
  FOC_fastCTRL_B->Product2_i[0] = FOC_fastCTRL_P.FOC_AngleEst_Rs *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[0];
  FOC_fastCTRL_B->Product2_i[1] = FOC_fastCTRL_P.FOC_AngleEst_Rs *
    FOC_fastCTRL_B->TrafoMatrixuvwalphabeta_c[1];

  /* Product: '<S22>/Product' incorporates:
   *  Constant: '<S22>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S23>/Product' incorporates:
   *  Constant: '<S4>/komp_kp'
   */
  FOC_fastCTRL_B->Product_k[0] = FOC_fastCTRL_B->psi_PM_alphabeta_n[0] *
    FOC_fastCTRL_P.FOC_AngleEst_Komp_KP;

  /* UnitDelay: '<S21>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_k[0] = FOC_fastCTRL_DW->UnitDelay_DSTATE_k[0];

  /* UnitDelay: '<S21>/Unit Delay1' */
  FOC_fastCTRL_B->UnitDelay1_f[0] = FOC_fastCTRL_DW->UnitDelay1_DSTATE_e[0];

  /* Switch: '<S21>/Switch4' incorporates:
   *  Constant: '<S21>/FOC_AngleEst_Delay1'
   */
  if (FOC_fastCTRL_P.FOC_AngleEst_Delay1 > FOC_fastCTRL_P.Switch4_Threshold_a) {
    /* Switch: '<S21>/Switch4' */
    FOC_fastCTRL_B->Switch4_n[0] = FOC_fastCTRL_B->UnitDelay1_f[0];
  } else {
    /* Switch: '<S21>/Switch4' */
    FOC_fastCTRL_B->Switch4_n[0] = FOC_fastCTRL_B->Product_p[0];
  }

  /* Switch: '<S21>/Switch3' incorporates:
   *  Constant: '<S21>/FOC_AngleEst_Delay2'
   */
  if (FOC_fastCTRL_P.FOC_AngleEst_Delay2 > FOC_fastCTRL_P.Switch3_Threshold_o) {
    /* Switch: '<S21>/Switch3' */
    FOC_fastCTRL_B->Switch3_p[0] = FOC_fastCTRL_B->UnitDelay_k[0];
  } else {
    /* Switch: '<S21>/Switch3' */
    FOC_fastCTRL_B->Switch3_p[0] = FOC_fastCTRL_B->Switch4_n[0];
  }

  /* Sum: '<S4>/Sum' */
  FOC_fastCTRL_B->Sum_n[0] = (FOC_fastCTRL_B->Switch3_p[0] -
    FOC_fastCTRL_B->Product_k[0]) - FOC_fastCTRL_B->Product2_i[0];

  /* Product: '<S22>/Product' */
  FOC_fastCTRL_B->Product_f[0] = FOC_fastCTRL_B->Sum_n[0] * maxV;

  /* Sum: '<S22>/Sum4' */
  FOC_fastCTRL_B->Sum4_l[0] = FOC_fastCTRL_B->Product_f[0] +
    FOC_fastCTRL_B->UnitDelay_lj[0];

  /* Product: '<S23>/Product' incorporates:
   *  Constant: '<S4>/komp_kp'
   */
  FOC_fastCTRL_B->Product_k[1] = FOC_fastCTRL_B->psi_PM_alphabeta_n[1] *
    FOC_fastCTRL_P.FOC_AngleEst_Komp_KP;

  /* UnitDelay: '<S21>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_k[1] = FOC_fastCTRL_DW->UnitDelay_DSTATE_k[1];

  /* UnitDelay: '<S21>/Unit Delay1' */
  FOC_fastCTRL_B->UnitDelay1_f[1] = FOC_fastCTRL_DW->UnitDelay1_DSTATE_e[1];

  /* Switch: '<S21>/Switch4' incorporates:
   *  Constant: '<S21>/FOC_AngleEst_Delay1'
   */
  if (FOC_fastCTRL_P.FOC_AngleEst_Delay1 > FOC_fastCTRL_P.Switch4_Threshold_a) {
    /* Switch: '<S21>/Switch4' */
    FOC_fastCTRL_B->Switch4_n[1] = FOC_fastCTRL_B->UnitDelay1_f[1];
  } else {
    /* Switch: '<S21>/Switch4' */
    FOC_fastCTRL_B->Switch4_n[1] = FOC_fastCTRL_B->Product_p[1];
  }

  /* Switch: '<S21>/Switch3' incorporates:
   *  Constant: '<S21>/FOC_AngleEst_Delay2'
   */
  if (FOC_fastCTRL_P.FOC_AngleEst_Delay2 > FOC_fastCTRL_P.Switch3_Threshold_o) {
    /* Switch: '<S21>/Switch3' */
    FOC_fastCTRL_B->Switch3_p[1] = FOC_fastCTRL_B->UnitDelay_k[1];
  } else {
    /* Switch: '<S21>/Switch3' */
    FOC_fastCTRL_B->Switch3_p[1] = FOC_fastCTRL_B->Switch4_n[1];
  }

  /* Sum: '<S4>/Sum' */
  FOC_fastCTRL_B->Sum_n[1] = (FOC_fastCTRL_B->Switch3_p[1] -
    FOC_fastCTRL_B->Product_k[1]) - FOC_fastCTRL_B->Product2_i[1];

  /* Product: '<S22>/Product' */
  FOC_fastCTRL_B->Product_f[1] = FOC_fastCTRL_B->Sum_n[1] * maxV;

  /* Sum: '<S22>/Sum4' */
  FOC_fastCTRL_B->Sum4_l[1] = FOC_fastCTRL_B->Product_f[1] +
    FOC_fastCTRL_B->UnitDelay_lj[1];

  /* Gain: '<S4>/phi_est_2' */
  FOC_fastCTRL_B->phi_est_2 = FOC_fastCTRL_P.phi_est_2_Gain *
    FOC_fastCTRL_B->Sum1_n;

  /* Gain: '<S25>/Anpassung der Signalfrequenz an Polpaarzahl' */
  FOC_fastCTRL_B->AnpassungderSignalfrequenzanPol = FOC_fastCTRL_P.FOC_z_P *
    FOC_fastCTRL_B->Switch;

  /* Constant: '<S25>/Constant' */
  FOC_fastCTRL_B->Constant = FOC_fastCTRL_P.Constant_Value_nb;

  /* Sum: '<S26>/Deviation' */
  FOC_fastCTRL_B->Deviation = FOC_fastCTRL_B->Sum3_h - Phi_Observer;

  /* Product: '<S26>/Product2' incorporates:
   *  Constant: '<S26>/Constant'
   *  Constant: '<S26>/Constant1'
   */
  FOC_fastCTRL_B->Product2_n = FOC_fastCTRL_P.FOC_AngleObserver_w0 *
    FOC_fastCTRL_P.FOC_AngleObserver_D * FOC_fastCTRL_B->Deviation;

  /* Gain: '<S26>/Gain' */
  FOC_fastCTRL_B->Gain_e = FOC_fastCTRL_P.Gain_Gain_o *
    FOC_fastCTRL_B->Product2_n;

  /* Gain: '<S26>/Gain4' */
  FOC_fastCTRL_B->winkelimpuls = FOC_fastCTRL_P.FOC_OmegaObs3 *
    FOC_fastCTRL_B->Deviation;

  /* Sum: '<S26>/Sum1' */
  FOC_fastCTRL_B->Sum1_e = FOC_fastCTRL_B->Gain_e + FOC_fastCTRL_B->UnitDelay1;

  /* Product: '<S26>/Product' incorporates:
   *  Constant: '<S26>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S26>/Product' */
  FOC_fastCTRL_B->Product_fh = FOC_fastCTRL_B->Sum1_e * maxV;

  /* Product: '<S26>/Product1' incorporates:
   *  Constant: '<S26>/Constant'
   */
  FOC_fastCTRL_B->Product1_b = FOC_fastCTRL_P.FOC_AngleObserver_w0 *
    FOC_fastCTRL_P.FOC_AngleObserver_w0 * FOC_fastCTRL_B->Deviation;

  /* UnitDelay: '<S34>/Unit Delay1' */
  FOC_fastCTRL_B->UnitDelay1_i = FOC_fastCTRL_DW->UnitDelay1_DSTATE_he;

  /* Sum: '<S26>/Sum2' */
  FOC_fastCTRL_B->Sum2_o = FOC_fastCTRL_B->Product1_b +
    FOC_fastCTRL_B->UnitDelay1_i;

  /* Sum: '<S26>/Sum6' */
  FOC_fastCTRL_B->Sum6 = FOC_fastCTRL_B->Product_fh + Phi_Observer;

  /* Product: '<S33>/Product' incorporates:
   *  Constant: '<S33>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S33>/Product' */
  FOC_fastCTRL_B->Product_f4 = FOC_fastCTRL_B->Sum2_o * maxV;

  /* Sum: '<S33>/Sum2' */
  FOC_fastCTRL_B->Sum2_d = FOC_fastCTRL_B->Product_f4 +
    FOC_fastCTRL_B->UnitDelay1;

  /* Product: '<S34>/Product' incorporates:
   *  Constant: '<S34>/FOC_T_fast'
   */
  maxV = 1.0 / FOC_fastCTRL_P.FOC_f_fastCTRL;

  /* Product: '<S34>/Product' */
  FOC_fastCTRL_B->Product_dh = FOC_fastCTRL_B->winkelimpuls * maxV;

  /* Sum: '<S34>/Sum2' */
  FOC_fastCTRL_B->Sum2_on = FOC_fastCTRL_B->Product_dh +
    FOC_fastCTRL_B->UnitDelay1_i;

  /* Gain: '<S5>/dummy_gain' incorporates:
   *  Outport: '<Root>/w_el [rad//s]'
   */
  w_el = FOC_fastCTRL_P.dummy_gain_Gain * FOC_fastCTRL_Y->w_elrads;

  /* Gain: '<S5>/dummy_gain1' */
  Phi_el_I_Transformation = FOC_fastCTRL_P.dummy_gain1_Gain *
    FOC_fastCTRL_B->Switch2_nz;

  /* Gain: '<S5>/dummy_gain2' */
  Phi_el_U_Transformation = FOC_fastCTRL_P.dummy_gain2_Gain *
    FOC_fastCTRL_B->Switch2_e;

  /* Gain: '<S5>/dummy_gain3' incorporates:
   *  Inport: '<Root>/phi_el [rad]'
   */
  Phi_Measured_Raw = FOC_fastCTRL_P.dummy_gain3_Gain * FOC_fastCTRL_U->phi_elrad;

  /* Sum: '<S5>/phi_est_error2' */
  FOC_fastCTRL_B->phi_est_error2 = FOC_fastCTRL_B->Switch2_nz -
    FOC_fastCTRL_B->Sum1;

  /* Gain: '<S5>/dummy_gain4' */
  Phi_est_error_I_Trafo = FOC_fastCTRL_P.dummy_gain4_Gain *
    FOC_fastCTRL_B->phi_est_error2;

  /* Gain: '<S5>/dummy_gain5' */
  Phi_est = FOC_fastCTRL_P.dummy_gain5_Gain * FOC_fastCTRL_B->Sum1;

  /* Gain: '<S5>/dummy_gain6' */
  Phi_AngleEst_AutoSwitch = FOC_fastCTRL_P.dummy_gain6_Gain *
    FOC_fastCTRL_B->Selectphicalc3;

  /* Sum: '<S5>/phi_est_error' */
  FOC_fastCTRL_B->phi_est_error = FOC_fastCTRL_B->Sum3 - FOC_fastCTRL_B->Sum1;

  /* Gain: '<S5>/dummy_gain7' */
  Phi_est_error = FOC_fastCTRL_P.dummy_gain7_Gain *
    FOC_fastCTRL_B->phi_est_error;

  /* Math: '<S35>/Math Function' */
  FOC_fastCTRL_B->MathFunction[0] =
    FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[0] *
    FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[0];
  FOC_fastCTRL_B->MathFunction[1] =
    FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[1] *
    FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[1];

  /* Sum: '<S35>/Sum' */
  maxV = FOC_fastCTRL_B->MathFunction[0];
  maxV += FOC_fastCTRL_B->MathFunction[1];

  /* Sum: '<S35>/Sum' */
  FOC_fastCTRL_B->Sum_i = maxV;

  /* Sqrt: '<S35>/I_ph_peak' */
  FOC_fastCTRL_B->I_ph_peak = sqrt(FOC_fastCTRL_B->Sum_i);

  /* Gain: '<S35>/I_ph_RMS' */
  FOC_fastCTRL_B->I_ph_RMS = FOC_fastCTRL_P.I_ph_RMS_Gain *
    FOC_fastCTRL_B->I_ph_peak;

  /* Outputs for Atomic SubSystem: '<S8>/Calc_Modulation_Index' */
  /* Gain: '<S51>/U_DC//2' */
  FOC_fastCTRL_B->U_DC2_p = FOC_fastCTRL_P.U_DC2_Gain * FOC_U_DC;

  /* MinMax: '<S51>/AvoidDivBy0' incorporates:
   *  Constant: '<S51>/Constant2'
   */
  maxV = fmax(FOC_fastCTRL_P.Constant2_Value_e, FOC_fastCTRL_B->U_DC2_p);

  /* MinMax: '<S51>/AvoidDivBy0' */
  FOC_fastCTRL_B->AvoidDivBy0_d = maxV;

  /* Math: '<S51>/Square' */
  FOC_fastCTRL_B->Square[0] = FOC_fastCTRL_B->Product_i[0] *
    FOC_fastCTRL_B->Product_i[0];
  FOC_fastCTRL_B->Square[1] = FOC_fastCTRL_B->Product_i[1] *
    FOC_fastCTRL_B->Product_i[1];

  /* Sum: '<S51>/Sum' */
  maxV = FOC_fastCTRL_B->Square[0];

  /* Math: '<S51>/Square1' */
  FOC_fastCTRL_B->Square1[0] = FOC_fastCTRL_B->Product_p[0] *
    FOC_fastCTRL_B->Product_p[0];

  /* Sum: '<S51>/Sum' */
  maxV += FOC_fastCTRL_B->Square[1];

  /* Math: '<S51>/Square1' */
  FOC_fastCTRL_B->Square1[1] = FOC_fastCTRL_B->Product_p[1] *
    FOC_fastCTRL_B->Product_p[1];

  /* Sum: '<S51>/Sum' */
  FOC_fastCTRL_B->Sum_h = maxV;

  /* Sqrt: '<S51>/Sqrt' */
  FOC_fastCTRL_B->Sqrt = sqrt(FOC_fastCTRL_B->Sum_h);

  /* Sum: '<S51>/Sum1' */
  maxV = FOC_fastCTRL_B->Square1[0];
  maxV += FOC_fastCTRL_B->Square1[1];

  /* Sum: '<S51>/Sum1' */
  FOC_fastCTRL_B->Sum1_nn = maxV;

  /* Sqrt: '<S51>/Sqrt1' */
  FOC_fastCTRL_B->Sqrt1 = sqrt(FOC_fastCTRL_B->Sum1_nn);

  /* Outport: '<Root>/ModInd' incorporates:
   *  Product: '<S51>/Divide3'
   */
  FOC_fastCTRL_Y->ModInd[0] = FOC_fastCTRL_B->Sqrt /
    FOC_fastCTRL_B->AvoidDivBy0_d;
  FOC_fastCTRL_Y->ModInd[1] = FOC_fastCTRL_B->Sqrt1 /
    FOC_fastCTRL_B->AvoidDivBy0_d;

  /* Gain: '<S51>/ModInd_1' incorporates:
   *  Outport: '<Root>/ModInd'
   */
  FOC_fastCTRL_B->ModInd_1 = FOC_fastCTRL_P.ModInd_1_Gain *
    FOC_fastCTRL_Y->ModInd[0];

  /* Gain: '<S51>/ModInd_2' incorporates:
   *  Outport: '<Root>/ModInd'
   */
  FOC_fastCTRL_B->ModInd_2 = FOC_fastCTRL_P.ModInd_2_Gain *
    FOC_fastCTRL_Y->ModInd[1];

  /* End of Outputs for SubSystem: '<S8>/Calc_Modulation_Index' */

  /* Switch: '<S41>/IntegStopSwitch2' incorporates:
   *  Switch: '<S45>/IntegStopSwitch2'
   */
  if (FOC_fastCTRL_B->LogicalOperator1) {
    boolean_T tmp_idx_0;
    boolean_T tmp_idx_1;

    /* RelationalOperator: '<S40>/AntiWindupLE' incorporates:
     *  Constant: '<S40>/FOC_MaxModInd'
     *  Outport: '<Root>/ModInd'
     */
    FOC_fastCTRL_B->AntiWindupLE_k = (FOC_fastCTRL_Y->ModInd[0] <=
      FOC_fastCTRL_P.FOC_MaxModInd);

    /* Switch: '<S41>/IntegStopSwitch3' */
    if (FOC_fastCTRL_B->Product1_f > FOC_fastCTRL_P.IntegStopSwitch3_Threshold)
    {
      /* Switch: '<S41>/IntegStopSwitch3' */
      FOC_fastCTRL_B->IntegStopSwitch3_o[0] = FOC_fastCTRL_B->IntegDelay1[0];
    } else {
      /* Switch: '<S41>/IntegStopSwitch3' incorporates:
       *  Constant: '<S41>/Zero1'
       */
      FOC_fastCTRL_B->IntegStopSwitch3_o[0] = FOC_fastCTRL_P.Zero1_Value[0];
    }

    /* Sum: '<S41>/IntSum2' */
    FOC_fastCTRL_B->IntSum2_l[0] = FOC_fastCTRL_B->KPek1[0] +
      FOC_fastCTRL_B->IntegStopSwitch3_o[0];

    /* Gain: '<S41>/FOC_IntegDamp' */
    FOC_fastCTRL_B->FOC_IntegDamp_g[0] = FOC_fastCTRL_P.FOC_IntegDamp *
      FOC_fastCTRL_B->IntegStopSwitch3_o[0];

    /* Product: '<S40>/antiWindupProd' */
    FOC_fastCTRL_B->antiWindupProd_j[0] = FOC_fastCTRL_B->IdqErr[0] *
      FOC_fastCTRL_B->IntegDelay1[0];

    /* Switch: '<S41>/IntegStopSwitch3' */
    if (FOC_fastCTRL_B->Product1_f > FOC_fastCTRL_P.IntegStopSwitch3_Threshold)
    {
      /* Switch: '<S41>/IntegStopSwitch3' */
      FOC_fastCTRL_B->IntegStopSwitch3_o[1] = FOC_fastCTRL_B->IntegDelay1[1];
    } else {
      /* Switch: '<S41>/IntegStopSwitch3' incorporates:
       *  Constant: '<S41>/Zero1'
       */
      FOC_fastCTRL_B->IntegStopSwitch3_o[1] = FOC_fastCTRL_P.Zero1_Value[1];
    }

    /* Sum: '<S41>/IntSum2' */
    FOC_fastCTRL_B->IntSum2_l[1] = FOC_fastCTRL_B->KPek1[1] +
      FOC_fastCTRL_B->IntegStopSwitch3_o[1];

    /* Gain: '<S41>/FOC_IntegDamp' */
    FOC_fastCTRL_B->FOC_IntegDamp_g[1] = FOC_fastCTRL_P.FOC_IntegDamp *
      FOC_fastCTRL_B->IntegStopSwitch3_o[1];

    /* Product: '<S40>/antiWindupProd' */
    FOC_fastCTRL_B->antiWindupProd_j[1] = FOC_fastCTRL_B->IdqErr[1] *
      FOC_fastCTRL_B->IntegDelay1[1];

    /* RelationalOperator: '<S43>/Compare' incorporates:
     *  Constant: '<S43>/Constant'
     */
    FOC_fastCTRL_B->Compare_l = (uint8_T)(FOC_fastCTRL_B->antiWindupProd_j[1] <
      FOC_fastCTRL_P.AntiWindupGT_q_const);

    /* Logic: '<S40>/AntiWindupOR_q' */
    FOC_fastCTRL_B->AntiWindupOR_q_d = (FOC_fastCTRL_B->AntiWindupLE_k ||
      (FOC_fastCTRL_B->Compare_l != 0));

    /* RelationalOperator: '<S42>/Compare' incorporates:
     *  Constant: '<S42>/Constant'
     */
    FOC_fastCTRL_B->Compare_p = (uint8_T)(FOC_fastCTRL_B->antiWindupProd_j[0] <
      FOC_fastCTRL_P.AntiWindupGT_d_const);

    /* Logic: '<S40>/AntiWindupOR_d' */
    FOC_fastCTRL_B->AntiWindupOR_d_b = ((FOC_fastCTRL_B->Compare_p != 0) ||
      FOC_fastCTRL_B->AntiWindupLE_k);

    /* Switch: '<S41>/IntegStopSwitch1' */
    tmp_idx_0 = FOC_fastCTRL_B->AntiWindupOR_d_b;
    tmp_idx_1 = FOC_fastCTRL_B->AntiWindupOR_q_d;
    if (tmp_idx_0) {
      FOC_fastCTRL_B->IntegStopSwitch1_e[0] = FOC_fastCTRL_B->IntSum2_l[0];
    } else {
      FOC_fastCTRL_B->IntegStopSwitch1_e[0] = FOC_fastCTRL_B->FOC_IntegDamp_g[0];
    }

    /* Switch: '<S41>/IntegStopSwitch2' */
    FOC_fastCTRL_B->IntegStopSwitch2[0] = FOC_fastCTRL_B->IntegStopSwitch1_e[0];

    /* Switch: '<S41>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      FOC_fastCTRL_B->IntegStopSwitch1_e[1] = FOC_fastCTRL_B->IntSum2_l[1];
    } else {
      FOC_fastCTRL_B->IntegStopSwitch1_e[1] = FOC_fastCTRL_B->FOC_IntegDamp_g[1];
    }

    /* Switch: '<S41>/IntegStopSwitch2' */
    FOC_fastCTRL_B->IntegStopSwitch2[1] = FOC_fastCTRL_B->IntegStopSwitch1_e[1];

    /* RelationalOperator: '<S44>/AntiWindupLE' incorporates:
     *  Constant: '<S44>/FOC_MaxModInd'
     *  Outport: '<Root>/ModInd'
     */
    FOC_fastCTRL_B->AntiWindupLE = (FOC_fastCTRL_Y->ModInd[1] <=
      FOC_fastCTRL_P.FOC_MaxModInd);

    /* Switch: '<S45>/IntegStopSwitch3' */
    if (FOC_fastCTRL_B->Product1_p > FOC_fastCTRL_P.IntegStopSwitch3_Threshold_p)
    {
      /* Switch: '<S45>/IntegStopSwitch3' */
      FOC_fastCTRL_B->IntegStopSwitch3[0] = FOC_fastCTRL_B->IntegDelay1_b[0];
    } else {
      /* Switch: '<S45>/IntegStopSwitch3' incorporates:
       *  Constant: '<S45>/Zero1'
       */
      FOC_fastCTRL_B->IntegStopSwitch3[0] = FOC_fastCTRL_P.Zero1_Value_e[0];
    }

    /* Sum: '<S45>/IntSum2' */
    FOC_fastCTRL_B->IntSum2[0] = FOC_fastCTRL_B->KPek1_a[0] +
      FOC_fastCTRL_B->IntegStopSwitch3[0];

    /* Gain: '<S45>/FOC_IntegDamp' */
    FOC_fastCTRL_B->FOC_IntegDamp[0] = FOC_fastCTRL_P.FOC_IntegDamp *
      FOC_fastCTRL_B->IntegStopSwitch3[0];

    /* Product: '<S44>/antiWindupProd' */
    FOC_fastCTRL_B->antiWindupProd[0] = FOC_fastCTRL_B->IdqErr_i[0] *
      FOC_fastCTRL_B->IntegDelay1_b[0];

    /* Switch: '<S45>/IntegStopSwitch3' */
    if (FOC_fastCTRL_B->Product1_p > FOC_fastCTRL_P.IntegStopSwitch3_Threshold_p)
    {
      /* Switch: '<S45>/IntegStopSwitch3' */
      FOC_fastCTRL_B->IntegStopSwitch3[1] = FOC_fastCTRL_B->IntegDelay1_b[1];
    } else {
      /* Switch: '<S45>/IntegStopSwitch3' incorporates:
       *  Constant: '<S45>/Zero1'
       */
      FOC_fastCTRL_B->IntegStopSwitch3[1] = FOC_fastCTRL_P.Zero1_Value_e[1];
    }

    /* Sum: '<S45>/IntSum2' */
    FOC_fastCTRL_B->IntSum2[1] = FOC_fastCTRL_B->KPek1_a[1] +
      FOC_fastCTRL_B->IntegStopSwitch3[1];

    /* Gain: '<S45>/FOC_IntegDamp' */
    FOC_fastCTRL_B->FOC_IntegDamp[1] = FOC_fastCTRL_P.FOC_IntegDamp *
      FOC_fastCTRL_B->IntegStopSwitch3[1];

    /* Product: '<S44>/antiWindupProd' */
    FOC_fastCTRL_B->antiWindupProd[1] = FOC_fastCTRL_B->IdqErr_i[1] *
      FOC_fastCTRL_B->IntegDelay1_b[1];

    /* RelationalOperator: '<S47>/Compare' incorporates:
     *  Constant: '<S47>/Constant'
     */
    FOC_fastCTRL_B->Compare = (uint8_T)(FOC_fastCTRL_B->antiWindupProd[1] <
      FOC_fastCTRL_P.AntiWindupGT_q_const_h);

    /* Logic: '<S44>/AntiWindupOR_q' */
    FOC_fastCTRL_B->AntiWindupOR_q = (FOC_fastCTRL_B->AntiWindupLE ||
      (FOC_fastCTRL_B->Compare != 0));

    /* RelationalOperator: '<S46>/Compare' incorporates:
     *  Constant: '<S46>/Constant'
     */
    FOC_fastCTRL_B->Compare_h = (uint8_T)(FOC_fastCTRL_B->antiWindupProd[0] <
      FOC_fastCTRL_P.AntiWindupGT_d_const_m);

    /* Logic: '<S44>/AntiWindupOR_d' */
    FOC_fastCTRL_B->AntiWindupOR_d = ((FOC_fastCTRL_B->Compare_h != 0) ||
      FOC_fastCTRL_B->AntiWindupLE);

    /* Switch: '<S45>/IntegStopSwitch1' */
    tmp_idx_0 = FOC_fastCTRL_B->AntiWindupOR_d;
    tmp_idx_1 = FOC_fastCTRL_B->AntiWindupOR_q;
    if (tmp_idx_0) {
      FOC_fastCTRL_B->IntegStopSwitch1[0] = FOC_fastCTRL_B->IntSum2[0];
    } else {
      FOC_fastCTRL_B->IntegStopSwitch1[0] = FOC_fastCTRL_B->FOC_IntegDamp[0];
    }

    /* Switch: '<S45>/IntegStopSwitch2' */
    FOC_fastCTRL_B->IntegStopSwitch2_h[0] = FOC_fastCTRL_B->IntegStopSwitch1[0];

    /* Switch: '<S45>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      FOC_fastCTRL_B->IntegStopSwitch1[1] = FOC_fastCTRL_B->IntSum2[1];
    } else {
      FOC_fastCTRL_B->IntegStopSwitch1[1] = FOC_fastCTRL_B->FOC_IntegDamp[1];
    }

    /* Switch: '<S45>/IntegStopSwitch2' */
    FOC_fastCTRL_B->IntegStopSwitch2_h[1] = FOC_fastCTRL_B->IntegStopSwitch1[1];
  } else {
    /* Switch: '<S41>/IntegStopSwitch2' incorporates:
     *  Constant: '<S41>/Zero1'
     */
    FOC_fastCTRL_B->IntegStopSwitch2[0] = FOC_fastCTRL_P.Zero1_Value[0];
    FOC_fastCTRL_B->IntegStopSwitch2[1] = FOC_fastCTRL_P.Zero1_Value[1];

    /* Switch: '<S45>/IntegStopSwitch2' incorporates:
     *  Constant: '<S45>/Zero1'
     */
    FOC_fastCTRL_B->IntegStopSwitch2_h[0] = FOC_fastCTRL_P.Zero1_Value_e[0];
    FOC_fastCTRL_B->IntegStopSwitch2_h[1] = FOC_fastCTRL_P.Zero1_Value_e[1];
  }

  /* End of Switch: '<S41>/IntegStopSwitch2' */

  /* Gain: '<S36>/I_d_Ref' incorporates:
   *  Outport: '<Root>/I_dq_Ref_out [A]'
   */
  FOC_fastCTRL_B->I_d_Ref = FOC_fastCTRL_P.I_d_Ref_Gain *
    FOC_fastCTRL_Y->I_dq_Ref_outA[0];

  /* Gain: '<S36>/I_q_Ref' incorporates:
   *  Outport: '<Root>/I_dq_Ref_out [A]'
   */
  FOC_fastCTRL_B->I_q_Ref = FOC_fastCTRL_P.I_q_Ref_Gain *
    FOC_fastCTRL_Y->I_dq_Ref_outA[1];

  /* Gain: '<S38>/I_d_Act_1' */
  FOC_fastCTRL_B->I_d_Act_1 = FOC_fastCTRL_P.I_d_Act_1_Gain *
    FOC_fastCTRL_B->TrafoSum;

  /* Gain: '<S38>/I_q_Act_1' */
  FOC_fastCTRL_B->I_q_Act_1 = FOC_fastCTRL_P.I_q_Act_1_Gain *
    FOC_fastCTRL_B->TrafoSum1;

  /* Gain: '<S38>/I_u_1' incorporates:
   *  Inport: '<Root>/I_ph [A]'
   */
  FOC_fastCTRL_B->I_u_1 = FOC_fastCTRL_P.I_u_1_Gain * FOC_fastCTRL_U->I_phA[0];

  /* Gain: '<S38>/I_v_1' incorporates:
   *  Inport: '<Root>/I_ph [A]'
   */
  FOC_fastCTRL_B->I_v_1 = FOC_fastCTRL_P.I_v_1_Gain * FOC_fastCTRL_U->I_phA[1];

  /* Gain: '<S38>/I_w_1' incorporates:
   *  Inport: '<Root>/I_ph [A]'
   */
  FOC_fastCTRL_B->I_w_1 = FOC_fastCTRL_P.I_w_1_Gain * FOC_fastCTRL_U->I_phA[2];

  /* DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
  i = 1;
  maxV = FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[0] *
    FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Coef[0];
  for (i_0 = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ; i_0 < 19; i_0++)
  {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i_0] *
      FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Coef[i];
    maxV += u;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ; i_0++) {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i_0] *
      FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Coef[i];
    maxV += u;
    i++;
  }

  FOC_fastCTRL_B->DiscreteFIRFilter20thorder[0] = maxV;
  i = 1;
  maxV = FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Coef[0] *
    FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[1];
  for (i_0 = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ; i_0 < 19; i_0++)
  {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i_0 + 19] *
      FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Coef[i];
    maxV += u;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ; i_0++) {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i_0 + 19] *
      FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Coef[i];
    maxV += u;
    i++;
  }

  FOC_fastCTRL_B->DiscreteFIRFilter20thorder[1] = maxV;

  /* End of DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */

  /* Gain: '<S38>/Gain5' */
  FOC_fastCTRL_B->I_d_Act_filt_1 = FOC_fastCTRL_P.Gain5_Gain *
    FOC_fastCTRL_B->DiscreteFIRFilter20thorder[0];

  /* Gain: '<S38>/Gain6' */
  FOC_fastCTRL_B->I_q_Act_filt_1 = FOC_fastCTRL_P.Gain6_Gain *
    FOC_fastCTRL_B->DiscreteFIRFilter20thorder[1];

  /* DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
  i = 1;
  maxV = FOC_fastCTRL_B->TmpSignalConversionAtDiscreteFI[0] *
    FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Co_f[0];
  for (i_0 = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a; i_0 < 19; i_0++)
  {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_p[i_0] *
      FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Co_f[i];
    maxV += u;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a; i_0++) {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_p[i_0] *
      FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Co_f[i];
    maxV += u;
    i++;
  }

  FOC_fastCTRL_B->DiscreteFIRFilter20thorder_h[0] = maxV;
  i = 1;
  maxV = FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Co_f[0] *
    FOC_fastCTRL_B->TmpSignalConversionAtDiscreteFI[1];
  for (i_0 = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a; i_0 < 19; i_0++)
  {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_p[i_0 + 19] *
      FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Co_f[i];
    maxV += u;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a; i_0++) {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_p[i_0 + 19] *
      FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Co_f[i];
    maxV += u;
    i++;
  }

  FOC_fastCTRL_B->DiscreteFIRFilter20thorder_h[1] = maxV;

  /* End of DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */

  /* Gain: '<S39>/I_d_Act_2' */
  FOC_fastCTRL_B->I_d_Act_2 = FOC_fastCTRL_P.I_d_Act_2_Gain *
    FOC_fastCTRL_B->TrafoSum_a;

  /* Gain: '<S39>/I_d_Act_filt_2' */
  FOC_fastCTRL_B->I_d_Act_filt_2 = FOC_fastCTRL_P.I_d_Act_filt_2_Gain *
    FOC_fastCTRL_B->DiscreteFIRFilter20thorder_h[0];

  /* Gain: '<S39>/I_q_Act_2' */
  FOC_fastCTRL_B->I_q_Act_2 = FOC_fastCTRL_P.I_q_Act_2_Gain *
    FOC_fastCTRL_B->TrafoSum1_h;

  /* Gain: '<S39>/I_q_Act_filt_2' */
  FOC_fastCTRL_B->I_q_Act_filt_2 = FOC_fastCTRL_P.I_q_Act_filt_2_Gain *
    FOC_fastCTRL_B->DiscreteFIRFilter20thorder_h[1];

  /* Gain: '<S39>/I_u_2' incorporates:
   *  Inport: '<Root>/I_ph [A]'
   */
  FOC_fastCTRL_B->I_u_2 = FOC_fastCTRL_P.I_u_2_Gain * FOC_fastCTRL_U->I_phA[3];

  /* Gain: '<S39>/I_v_2' incorporates:
   *  Inport: '<Root>/I_ph [A]'
   */
  FOC_fastCTRL_B->I_v_2 = FOC_fastCTRL_P.I_v_2_Gain * FOC_fastCTRL_U->I_phA[4];

  /* Gain: '<S39>/I_w_2' incorporates:
   *  Inport: '<Root>/I_ph [A]'
   */
  FOC_fastCTRL_B->I_w_2 = FOC_fastCTRL_P.I_w_2_Gain * FOC_fastCTRL_U->I_phA[5];

  /* Abs: '<S48>/Abs' */
  FOC_fastCTRL_B->Abs_p = fabs(FOC_fastCTRL_B->Add);

  /* Switch: '<S48>/Switch' */
  if (FOC_fastCTRL_B->Abs_p >= FOC_fastCTRL_P.Switch_Threshold_e) {
    /* Signum: '<S48>/Sign' */
    u = FOC_fastCTRL_B->Product;
    if (rtIsNaN(u)) {
      /* Signum: '<S48>/Sign' */
      FOC_fastCTRL_B->Sign = u;
    } else if (u < 0.0) {
      /* Signum: '<S48>/Sign' */
      FOC_fastCTRL_B->Sign = -1.0;
    } else {
      /* Signum: '<S48>/Sign' */
      FOC_fastCTRL_B->Sign = (u > 0.0);
    }

    /* End of Signum: '<S48>/Sign' */

    /* Gain: '<S48>/Gain1' */
    FOC_fastCTRL_B->Gain1_k = FOC_fastCTRL_P.Gain1_Gain * FOC_fastCTRL_B->Sign;

    /* Switch: '<S48>/Switch' */
    FOC_fastCTRL_B->Switch_ip = FOC_fastCTRL_B->Gain1_k;
  } else {
    /* Switch: '<S48>/Switch' incorporates:
     *  Constant: '<S48>/Constant1'
     */
    FOC_fastCTRL_B->Switch_ip = FOC_fastCTRL_P.Constant1_Value_l0;
  }

  /* End of Switch: '<S48>/Switch' */

  /* Sum: '<S48>/Add1' */
  FOC_fastCTRL_B->Add1 = FOC_fastCTRL_B->Add - FOC_fastCTRL_B->Switch_ip;

  /* UnitDelay: '<S1>/Unit Delay' */
  FOC_fastCTRL_B->UnitDelay_c3[0] = FOC_fastCTRL_DW->UnitDelay_DSTATE_bs[0];
  FOC_fastCTRL_B->UnitDelay_c3[1] = FOC_fastCTRL_DW->UnitDelay_DSTATE_bs[1];

  /* Gain: '<S56>/U_d_1' */
  FOC_fastCTRL_B->U_d_1 = FOC_fastCTRL_P.U_d_1_Gain *
    FOC_fastCTRL_B->SelectControlMode[0];

  /* Gain: '<S56>/U_q_1' */
  FOC_fastCTRL_B->U_q_1 = FOC_fastCTRL_P.U_q_1_Gain *
    FOC_fastCTRL_B->SelectControlMode[1];

  /* Gain: '<S57>/U_d_2' */
  FOC_fastCTRL_B->U_d_2 = FOC_fastCTRL_P.U_d_2_Gain *
    FOC_fastCTRL_B->SelectControlMode[2];

  /* Gain: '<S57>/U_q_2' */
  FOC_fastCTRL_B->U_q_2 = FOC_fastCTRL_P.U_q_2_Gain *
    FOC_fastCTRL_B->SelectControlMode[3];

  /* Trigonometry: '<S59>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_c = rt_atan2d_snf
    (FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[1],
     FOC_fastCTRL_B->TrafoMatrixuvwalphabeta[0]);

  /* Trigonometry: '<S58>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_k = rt_atan2d_snf
    (FOC_fastCTRL_B->UnitDelay_c3[1], FOC_fastCTRL_B->UnitDelay_c3[0]);

  /* Sum: '<S9>/Sum2' */
  FOC_fastCTRL_B->Sum2_di = FOC_fastCTRL_B->TrigonometricFunction_c -
    FOC_fastCTRL_B->TrigonometricFunction_k;

  /* Trigonometry: '<S9>/Trigonometric Function' */
  FOC_fastCTRL_B->TrigonometricFunction_p = cos(FOC_fastCTRL_B->Sum2_di);

  /* DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */
  i = 1;
  maxV = FOC_fastCTRL_B->TrigonometricFunction_p *
    FOC_fastCTRL_P.DiscreteFIRFilter10thorder_Coef[0];
  for (i_0 = FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ; i_0 < 9; i_0++) {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_stat[i_0] *
      FOC_fastCTRL_P.DiscreteFIRFilter10thorder_Coef[i];
    maxV += u;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ; i_0++) {
    u = FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_stat[i_0] *
      FOC_fastCTRL_P.DiscreteFIRFilter10thorder_Coef[i];
    maxV += u;
    i++;
  }

  /* DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */
  FOC_fastCTRL_B->DiscreteFIRFilter10thorder = maxV;

  /* Outport: '<Root>/FOC_Error' incorporates:
   *  Constant: '<S1>/Manipulate_FOC_Error'
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   */
  FOC_fastCTRL_Y->FOC_Error = FOC_fastCTRL_P.Manipulate_FOC_Error_Value;

  /* UnitDelay: '<S1>/FCF_Cnt' */
  FCF_Cnt = FOC_fastCTRL_DW->FCF_Cnt_DSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Counter_Start'
   */
  FOC_fastCTRL_B->Sum_pl = FOC_fastCTRL_P.Counter_Start_Value + FCF_Cnt;

  /* Gain: '<S1>/Gain' incorporates:
   *  Constant: '<S1>/Par1'
   */
  FOC_fastCTRL_B->Sig1 = FOC_fastCTRL_P.Gain_Gain_m * FOC_fastCTRL_P.Par1;

  /* Gain: '<S1>/Gain1' incorporates:
   *  Constant: '<S1>/Par2'
   */
  FOC_fastCTRL_B->Sig2 = FOC_fastCTRL_P.Gain1_Gain_m * FOC_fastCTRL_P.Par2;

  /* Gain: '<S1>/Gain2' incorporates:
   *  Constant: '<S1>/Par3'
   */
  FOC_fastCTRL_B->Sig3 = FOC_fastCTRL_P.Gain2_Gain_i * FOC_fastCTRL_P.Par3;

  /* Gain: '<S1>/Gain3' incorporates:
   *  Constant: '<S1>/Par4'
   */
  FOC_fastCTRL_B->Sig4 = FOC_fastCTRL_P.Gain3_Gain_o * FOC_fastCTRL_P.Par4;

  /* Gain: '<S1>/Gain4' incorporates:
   *  Constant: '<S1>/Par5'
   */
  FOC_fastCTRL_B->Sig5 = FOC_fastCTRL_P.Gain4_Gain_l * FOC_fastCTRL_P.Par5;

  /* Gain: '<S1>/Gain5' incorporates:
   *  Constant: '<S1>/Par6'
   */
  FOC_fastCTRL_B->Sig6 = FOC_fastCTRL_P.Gain5_Gain_o * FOC_fastCTRL_P.Par6;

  /* Gain: '<S1>/Gain6' incorporates:
   *  Constant: '<S1>/Par7'
   */
  FOC_fastCTRL_B->Sig7 = FOC_fastCTRL_P.Gain6_Gain_o * FOC_fastCTRL_P.Par7;

  /* Gain: '<S1>/Gain7' incorporates:
   *  Constant: '<S1>/Par8'
   */
  FOC_fastCTRL_B->Sig8 = FOC_fastCTRL_P.Gain7_Gain * FOC_fastCTRL_P.Par8;

  /* Update for DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
  maxV = FOC_fastCTRL_B->f_2_w_el;
  maxV -= FOC_fastCTRL_P.DiscreteTransferFcn_DenCoef[1] *
    FOC_fastCTRL_DW->DiscreteTransferFcn_states;
  maxV /= FOC_fastCTRL_P.DiscreteTransferFcn_DenCoef[0];
  FOC_fastCTRL_DW->DiscreteTransferFcn_states = maxV;

  /* Update for UnitDelay: '<S48>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE = FOC_fastCTRL_B->Add1;

  /* Update for UnitDelay: '<S33>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE = FOC_fastCTRL_B->Sum2_d;

  /* Update for UnitDelay: '<S12>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_n = FOC_fastCTRL_B->Sum_p;

  /* Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  FOC_fastCTRL_DW->DiscreteTransferFcn_states_o =
    FOC_fastCTRL_DW->DiscreteTransferFcn_tmp;

  /* Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn1' */
  FOC_fastCTRL_DW->DiscreteTransferFcn1_states =
    FOC_fastCTRL_DW->DiscreteTransferFcn1_tmp;

  /* Update for UnitDelay: '<S32>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_g = FOC_fastCTRL_B->Sum3_h;

  /* Update for UnitDelay: '<S26>/Unit Delay3' */
  FOC_fastCTRL_DW->UnitDelay3_DSTATE = FOC_fastCTRL_B->Sum6;

  /* Update for UnitDelay: '<S19>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_b = FOC_fastCTRL_B->Sum_g;

  /* Update for DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn' */
  FOC_fastCTRL_DW->DiscreteTransferFcn_states_j =
    FOC_fastCTRL_DW->DiscreteTransferFcn_tmp_g;

  /* Update for DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn1' */
  FOC_fastCTRL_DW->DiscreteTransferFcn1_states_c =
    FOC_fastCTRL_DW->DiscreteTransferFcn1_tmp_l;

  /* Update for UnitDelay: '<S15>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_m[0] = FOC_fastCTRL_B->Sum4[0];

  /* Update for UnitDelay: '<S41>/IntegDelay1' */
  FOC_fastCTRL_DW->IntegDelay1_DSTATE[0] = FOC_fastCTRL_B->IntegStopSwitch2[0];

  /* Update for UnitDelay: '<S45>/IntegDelay1' */
  FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0] = FOC_fastCTRL_B->IntegStopSwitch2_h
    [0];

  /* Update for UnitDelay: '<S14>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_o[0] = FOC_fastCTRL_B->Switch4[0];

  /* Update for UnitDelay: '<S14>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[0] = FOC_fastCTRL_B->Product_i[0];

  /* Update for UnitDelay: '<S22>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_e[0] = FOC_fastCTRL_B->Sum4_l[0];

  /* Update for UnitDelay: '<S21>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_k[0] = FOC_fastCTRL_B->Switch4_n[0];

  /* Update for UnitDelay: '<S21>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_e[0] = FOC_fastCTRL_B->Product_p[0];

  /* Update for UnitDelay: '<S15>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_m[1] = FOC_fastCTRL_B->Sum4[1];

  /* Update for UnitDelay: '<S41>/IntegDelay1' */
  FOC_fastCTRL_DW->IntegDelay1_DSTATE[1] = FOC_fastCTRL_B->IntegStopSwitch2[1];

  /* Update for UnitDelay: '<S45>/IntegDelay1' */
  FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1] = FOC_fastCTRL_B->IntegStopSwitch2_h
    [1];

  /* Update for UnitDelay: '<S14>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_o[1] = FOC_fastCTRL_B->Switch4[1];

  /* Update for UnitDelay: '<S14>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[1] = FOC_fastCTRL_B->Product_i[1];

  /* Update for UnitDelay: '<S22>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_e[1] = FOC_fastCTRL_B->Sum4_l[1];

  /* Update for UnitDelay: '<S21>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_k[1] = FOC_fastCTRL_B->Switch4_n[1];

  /* Update for UnitDelay: '<S21>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_e[1] = FOC_fastCTRL_B->Product_p[1];

  /* Update for UnitDelay: '<S34>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_he = FOC_fastCTRL_B->Sum2_on;

  /* Update for DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ--;
  if (FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ < 0) {
    FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ = 18;
  }

  /* Update circular buffer */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat
    [FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ] =
    FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[0];
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat
    [FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ + 19] =
    FOC_fastCTRL_B->TmpSignalConversionAtMathFuncti[1];

  /* End of Update for DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a--;
  if (FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a < 0) {
    FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a = 18;
  }

  /* Update circular buffer */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_p
    [FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a] =
    FOC_fastCTRL_B->TmpSignalConversionAtDiscreteFI[0];

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_bs[0] = FOC_fastCTRL_B->Product_i[0];

  /* Update for DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_p
    [FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a + 19] =
    FOC_fastCTRL_B->TmpSignalConversionAtDiscreteFI[1];

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_bs[1] = FOC_fastCTRL_B->Product_i[1];

  /* Update for DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */
  /* Update circular buffer index */
  FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ--;
  if (FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ < 0) {
    FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ = 8;
  }

  /* Update circular buffer */
  FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_stat
    [FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ] =
    FOC_fastCTRL_B->TrigonometricFunction_p;

  /* End of Update for DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */

  /* Update for UnitDelay: '<S1>/FCF_Cnt' */
  FOC_fastCTRL_DW->FCF_Cnt_DSTATE = FOC_fastCTRL_B->Sum_pl;

  /* End of Outputs for SubSystem: '<Root>/FOC_fastCTRL' */

  /* Outport: '<Root>/I_dq_Act [A]' */
  FOC_fastCTRL_Y->I_dq_ActA[0] = FOC_fastCTRL_B->DiscreteFIRFilter20thorder[0];
  FOC_fastCTRL_Y->I_dq_ActA[2] = FOC_fastCTRL_B->DiscreteFIRFilter20thorder_h[0];
  FOC_fastCTRL_Y->I_dq_ActA[1] = FOC_fastCTRL_B->DiscreteFIRFilter20thorder[1];
  FOC_fastCTRL_Y->I_dq_ActA[3] = FOC_fastCTRL_B->DiscreteFIRFilter20thorder_h[1];
}

/* Model initialize function */
void FOC_fastCTRL_initialize(RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_M)
{
  DW_FOC_fastCTRL_T *FOC_fastCTRL_DW = FOC_fastCTRL_M->dwork;
  B_FOC_fastCTRL_T *FOC_fastCTRL_B = FOC_fastCTRL_M->blockIO;
  ExtU_FOC_fastCTRL_T *FOC_fastCTRL_U = (ExtU_FOC_fastCTRL_T *)
    FOC_fastCTRL_M->inputs;
  ExtY_FOC_fastCTRL_T *FOC_fastCTRL_Y = (ExtY_FOC_fastCTRL_T *)
    FOC_fastCTRL_M->outputs;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void) memset(((void *) FOC_fastCTRL_B), 0,
                sizeof(B_FOC_fastCTRL_T));

  /* exported global signals */
  Phi_Observer = 0.0;
  FOC_U_DC = 0.0;
  FOC_AngleEst_w_el = 0.0;
  FOC_AngleEst_Psi_PM_alpha = 0.0;
  FOC_AngleEst_Psi_PM_beta = 0.0;
  w_el = 0.0;
  Phi_el_I_Transformation = 0.0;
  Phi_el_U_Transformation = 0.0;
  Phi_Measured_Raw = 0.0;
  Phi_est_error_I_Trafo = 0.0;
  Phi_est = 0.0;
  Phi_AngleEst_AutoSwitch = 0.0;
  Phi_est_error = 0.0;
  FCF_Cnt = 0.0;

  /* states (dwork) */
  (void) memset((void *)FOC_fastCTRL_DW, 0,
                sizeof(DW_FOC_fastCTRL_T));

  /* external inputs */
  (void)memset(FOC_fastCTRL_U, 0, sizeof(ExtU_FOC_fastCTRL_T));

  /* external outputs */
  (void)memset(FOC_fastCTRL_Y, 0, sizeof(ExtY_FOC_fastCTRL_T));

  {
    int32_T i;

    /* InitializeConditions for DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
    FOC_fastCTRL_DW->DiscreteTransferFcn_states =
      FOC_fastCTRL_P.DiscreteTransferFcn_InitialStat;

    /* InitializeConditions for UnitDelay: '<S48>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE =
      FOC_fastCTRL_P.UnitDelay_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S33>/Unit Delay1' */
    FOC_fastCTRL_DW->UnitDelay1_DSTATE = FOC_fastCTRL_P.FOC_AngleObs_w_InitVal;

    /* InitializeConditions for UnitDelay: '<S12>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_n =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_g;

    /* InitializeConditions for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
    FOC_fastCTRL_DW->DiscreteTransferFcn_states_o =
      FOC_fastCTRL_P.DiscreteTransferFcn_InitialSt_b;

    /* InitializeConditions for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn1' */
    FOC_fastCTRL_DW->DiscreteTransferFcn1_states =
      FOC_fastCTRL_P.DiscreteTransferFcn1_InitialSta;

    /* InitializeConditions for UnitDelay: '<S32>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_g =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_n;

    /* InitializeConditions for UnitDelay: '<S26>/Unit Delay3' */
    FOC_fastCTRL_DW->UnitDelay3_DSTATE =
      FOC_fastCTRL_P.UnitDelay3_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S19>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_b =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_nf;

    /* InitializeConditions for DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn' */
    FOC_fastCTRL_DW->DiscreteTransferFcn_states_j =
      FOC_fastCTRL_P.DiscreteTransferFcn_InitialSt_o;

    /* InitializeConditions for DiscreteTransferFcn: '<S20>/Discrete Transfer Fcn1' */
    FOC_fastCTRL_DW->DiscreteTransferFcn1_states_c =
      FOC_fastCTRL_P.DiscreteTransferFcn1_InitialS_h;

    /* InitializeConditions for UnitDelay: '<S15>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_m[0] =
      FOC_fastCTRL_P.FOC_AngleEst_Psi_InitVal;

    /* InitializeConditions for UnitDelay: '<S41>/IntegDelay1' */
    FOC_fastCTRL_DW->IntegDelay1_DSTATE[0] =
      FOC_fastCTRL_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S45>/IntegDelay1' */
    FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0] =
      FOC_fastCTRL_P.IntegDelay1_InitialCondition_a;

    /* InitializeConditions for UnitDelay: '<S14>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_o[0] =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_a;

    /* InitializeConditions for UnitDelay: '<S14>/Unit Delay1' */
    FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[0] =
      FOC_fastCTRL_P.UnitDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S22>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_e[0] =
      FOC_fastCTRL_P.FOC_AngleEst_Psi_InitVal;

    /* InitializeConditions for UnitDelay: '<S21>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_k[0] =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_gn;

    /* InitializeConditions for UnitDelay: '<S21>/Unit Delay1' */
    FOC_fastCTRL_DW->UnitDelay1_DSTATE_e[0] =
      FOC_fastCTRL_P.UnitDelay1_InitialCondition_j;

    /* InitializeConditions for UnitDelay: '<S15>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_m[1] =
      FOC_fastCTRL_P.FOC_AngleEst_Psi_InitVal;

    /* InitializeConditions for UnitDelay: '<S41>/IntegDelay1' */
    FOC_fastCTRL_DW->IntegDelay1_DSTATE[1] =
      FOC_fastCTRL_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S45>/IntegDelay1' */
    FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1] =
      FOC_fastCTRL_P.IntegDelay1_InitialCondition_a;

    /* InitializeConditions for UnitDelay: '<S14>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_o[1] =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_a;

    /* InitializeConditions for UnitDelay: '<S14>/Unit Delay1' */
    FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[1] =
      FOC_fastCTRL_P.UnitDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S22>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_e[1] =
      FOC_fastCTRL_P.FOC_AngleEst_Psi_InitVal;

    /* InitializeConditions for UnitDelay: '<S21>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_k[1] =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_gn;

    /* InitializeConditions for UnitDelay: '<S21>/Unit Delay1' */
    FOC_fastCTRL_DW->UnitDelay1_DSTATE_e[1] =
      FOC_fastCTRL_P.UnitDelay1_InitialCondition_j;

    /* InitializeConditions for UnitDelay: '<S34>/Unit Delay1' */
    FOC_fastCTRL_DW->UnitDelay1_DSTATE_he =
      FOC_fastCTRL_P.UnitDelay1_InitialCondition_o;

    /* InitializeConditions for DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
    FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ = 0;

    /* InitializeConditions for DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
    FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a = 0;
    for (i = 0; i < 38; i++) {
      /* InitializeConditions for DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
      FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i] =
        FOC_fastCTRL_P.DiscreteFIRFilter20thorder_Init;

      /* InitializeConditions for DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
      FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_p[i] =
        FOC_fastCTRL_P.DiscreteFIRFilter20thorder_In_p;
    }

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
    FOC_fastCTRL_DW->UnitDelay_DSTATE_bs[0] =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_l;
    FOC_fastCTRL_DW->UnitDelay_DSTATE_bs[1] =
      FOC_fastCTRL_P.UnitDelay_InitialCondition_l;

    /* InitializeConditions for DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */
    FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ = 0;
    for (i = 0; i < 9; i++) {
      FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_stat[i] =
        FOC_fastCTRL_P.DiscreteFIRFilter10thorder_Init;
    }

    /* End of InitializeConditions for DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */

    /* InitializeConditions for UnitDelay: '<S1>/FCF_Cnt' */
    FOC_fastCTRL_DW->FCF_Cnt_DSTATE = FOC_fastCTRL_P.FCF_Cnt_InitialCondition;

    /* End of SystemInitialize for SubSystem: '<Root>/FOC_fastCTRL' */
  }
}

/* Model terminate function */
void FOC_fastCTRL_terminate(RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(FOC_fastCTRL_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
