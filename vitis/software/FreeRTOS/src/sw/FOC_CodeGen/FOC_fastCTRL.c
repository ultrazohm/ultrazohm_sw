/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_fastCTRL.c
 *
 * Code generated for Simulink model 'FOC_fastCTRL'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Aug 22 14:14:27 2023
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
static real_T Phi_AngleEst_AutoSwitch;        /* '<S5>/Selectphicalc3' */
static real_T FOC_AngleEst_w_el;              /* '<S13>/Switch_speed' */
static real_T Phi_est;                        /* '<S10>/Sum1' */
static real_T Phi_Observer;                   /* '<S26>/Sum7' */
static real_T Phi_el_I_Transformation;        /* '<S28>/Switch2' */
static real_T Phi_el_U_Transformation;        /* '<S29>/Switch2' */
static real_T FOC_U_DC;                       /* '<S1>/Switch1' */
static real_T Phi_est_error_I_Trafo;          /* '<S5>/phi_est_error2' */
static real_T Phi_est_error;                  /* '<S5>/phi_est_error' */
static real_T FOC_AngleEst_Psi_PM_alpha;      /* '<S3>/Gain3' */
static real_T FOC_AngleEst_Psi_PM_beta;       /* '<S3>/Gain4' */
static real_T w_el;                           /* '<S5>/dummy_gain' */
static real_T Phi_Measured_Raw;               /* '<S5>/dummy_gain3' */

/* Exported block parameters */
static real_T FOC_6ph_AngleShift = 0.0;       /* Variable: FOC_6ph_AngleShift
                                        * Referenced by:
                                        *   '<S5>/FOC_6ph_AngleShift'
                                        *   '<S6>/FOC_6ph_AngleShift'
                                        *   '<S7>/FOC_6ph_AngleShift'
                                        */
static real_T FOC_AKS_Mode = 1.0;             /* Variable: FOC_AKS_Mode
                                        * Referenced by: '<S2>/FOC_AKS_Mode'
                                        */
static real_T FOC_AngleEst_AutoSwitch_wel_off = 785.0;
                                    /* Variable: FOC_AngleEst_AutoSwitch_wel_off
                                     * Referenced by: '<S5>/AutoSwitchHysteresis'
                                     */
static real_T FOC_AngleEst_AutoSwitch_wel_on = 942.0;
                                     /* Variable: FOC_AngleEst_AutoSwitch_wel_on
                                      * Referenced by: '<S5>/AutoSwitchHysteresis'
                                      */
static real_T FOC_AngleEst_Delay1 = 1.0;      /* Variable: FOC_AngleEst_Delay1
                                        * Referenced by: '<S14>/FOC_AngleEst_Delay1'
                                        */
static real_T FOC_AngleEst_Delay2 = 0.0;      /* Variable: FOC_AngleEst_Delay2
                                        * Referenced by: '<S14>/FOC_AngleEst_Delay2'
                                        */
static real_T FOC_AngleEst_Komp_KP = 500.0;   /* Variable: FOC_AngleEst_Komp_KP
                                        * Referenced by: '<S3>/komp_kp'
                                        */
static real_T FOC_AngleEst_Lq = 0.0008;       /* Variable: FOC_AngleEst_Lq
                                        * Referenced by: '<S3>/FOC_AngleEst_Lq'
                                        */
static real_T FOC_AngleEst_Psi_InitVal = 0.0; /* Variable: FOC_AngleEst_Psi_InitVal
                                        * Referenced by: '<S15>/Unit Delay'
                                        */
static real_T FOC_AngleEst_Rs = 0.066;        /* Variable: FOC_AngleEst_Rs
                                        * Referenced by: '<S3>/FOC_AngleEst_Rs'
                                        */
static real_T FOC_AngleEst_w_el_filtered_Tau = 0.0005;
                                     /* Variable: FOC_AngleEst_w_el_filtered_Tau
                                      * Referenced by: '<S12>/Tau'
                                      */
static real_T FOC_AngleObs_w_InitVal = 0.0;   /* Variable: FOC_AngleObs_w_InitVal
                                        * Referenced by: '<S33>/Unit Delay1'
                                        */
static real_T FOC_AngleObserver_D = 1.0;      /* Variable: FOC_AngleObserver_D
                                        * Referenced by: '<S26>/Constant1'
                                        */
static real_T FOC_AngleObserver_w0 = 200.0;   /* Variable: FOC_AngleObserver_w0
                                        * Referenced by: '<S26>/Constant'
                                        */
static real_T FOC_Enable = 1.0;               /* Variable: FOC_Enable
                                        * Referenced by: '<S1>/Enable'
                                        */
static real_T FOC_IntegDamp = 0.995;          /* Variable: FOC_IntegDamp
                                        * Referenced by:
                                        *   '<S41>/FOC_IntegDamp'
                                        *   '<S45>/FOC_IntegDamp'
                                        */
static real_T FOC_KI = 1000.0;                /* Variable: FOC_KI
                                        * Referenced by:
                                        *   '<S41>/FOC_KI'
                                        *   '<S45>/FOC_KI'
                                        */
static real_T FOC_KP = 1.0;                   /* Variable: FOC_KP
                                        * Referenced by:
                                        *   '<S41>/FOC_KP1'
                                        *   '<S45>/FOC_KP1'
                                        */
static real_T FOC_MANUAL_U_DC = 0.0;          /* Variable: FOC_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc1'
                                        */
static real_T FOC_MaxModInd = 1.1;            /* Variable: FOC_MaxModInd
                                        * Referenced by:
                                        *   '<S40>/FOC_MaxModInd'
                                        *   '<S44>/FOC_MaxModInd'
                                        */
static real_T FOC_OmegaObs3 = 0.0;            /* Variable: FOC_OmegaObs3
                                        * Referenced by: '<S26>/Gain4'
                                        */
static real_T FOC_PhiSensorTdead = 0.0;       /* Variable: FOC_PhiSensorTdead
                                        * Referenced by: '<S26>/Constant2'
                                        */
static real_T FOC_PhiSensorTdead_AngleEst = 5.0E-6;/* Variable: FOC_PhiSensorTdead_AngleEst
                                             * Referenced by: '<S26>/Constant3'
                                             */
static real_T FOC_SELECT_AngleAdaption2PolePairs = 0.0;
                                 /* Variable: FOC_SELECT_AngleAdaption2PolePairs
                                  * Referenced by: '<S5>/Constant2'
                                  */
static real_T FOC_SELECT_AngleAdaptionRange = 0.0;
                                      /* Variable: FOC_SELECT_AngleAdaptionRange
                                       * Referenced by: '<S5>/Constant4'
                                       */
static real_T FOC_SELECT_AngleEst = 0.0;      /* Variable: FOC_SELECT_AngleEst
                                        * Referenced by: '<S5>/Constant1'
                                        */
static real_T FOC_SELECT_AngleEst_AutoSwitch = 0.0;
                                     /* Variable: FOC_SELECT_AngleEst_AutoSwitch
                                      * Referenced by: '<S5>/Constant5'
                                      */
static real_T FOC_SELECT_AngleEst_w_el_filtered = 1.0;
                                  /* Variable: FOC_SELECT_AngleEst_w_el_filtered
                                   * Referenced by: '<S3>/useFilteredCorrection'
                                   */
static real_T FOC_SELECT_InvertAngle = 1.0;   /* Variable: FOC_SELECT_InvertAngle
                                        * Referenced by: '<S5>/FOC_Invert_Encoder'
                                        */
static real_T FOC_SELECT_Modulation = 1.0;    /* Variable: FOC_SELECT_Modulation
                                        * Referenced by: '<S8>/Enable_SuperSinMod'
                                        */
static real_T FOC_SELECT_U_DC_INPUT = 1.0;    /* Variable: FOC_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
static real_T FOC_SELECT_phi = 2.0;           /* Variable: FOC_SELECT_phi
                                        * Referenced by: '<S5>/Constant3'
                                        */
static real_T FOC_Uf_U_max = 0.0;             /* Variable: FOC_Uf_U_max
                                        * Referenced by: '<S49>/Saturation1'
                                        */
static real_T FOC_Uf_U_min = 0.0;             /* Variable: FOC_Uf_U_min
                                        * Referenced by: '<S49>/Saturation1'
                                        */
static real_T FOC_Uf_Ud = 0.0;                /* Variable: FOC_Uf_Ud
                                        * Referenced by: '<S7>/Uf_Ud'
                                        */
static real_T FOC_Uf_f_el = 0.0;              /* Variable: FOC_Uf_f_el
                                        * Referenced by: '<S7>/Uf_w_el'
                                        */
static real_T FOC_Uf_m = 0.0;                 /* Variable: FOC_Uf_m
                                        * Referenced by: '<S49>/Gain'
                                        */
static real_T FOC_f_fastCTRL = 10000.0;       /* Variable: FOC_f_fastCTRL
                                        * Referenced by:
                                        *   '<S5>/FOC_T_fast'
                                        *   '<S12>/FOC_f_fast'
                                        *   '<S13>/FOC_f_fastCTRL'
                                        *   '<S13>/FOC_f_fastCTRL1'
                                        *   '<S15>/FOC_T_fast'
                                        *   '<S26>/FOC_T_fast'
                                        *   '<S48>/FOC_T_fast'
                                        *   '<S33>/FOC_T_fast'
                                        *   '<S34>/FOC_T_fast'
                                        *   '<S41>/FOC_T_fast'
                                        *   '<S45>/FOC_T_fast'
                                        */
static real_T FOC_output_trafo_delay = 1.5;   /* Variable: FOC_output_trafo_delay
                                        * Referenced by: '<S5>/FOC_output_trafo_delay'
                                        */
static real_T FOC_phi_offset = 1.794;         /* Variable: FOC_phi_offset
                                        * Referenced by: '<S5>/Constant'
                                        */
static real_T Factor_OmegaRot = 1.0;          /* Variable: Factor_OmegaRot
                                        * Referenced by: '<S26>/Gain5'
                                        */
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T u0_0;
    int32_T u1_0;
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
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
  real_T rtb_SelectControlMode[6];
  real_T rtb_Sum3_f_0[6];
  real_T TmpSignalConversionAtDiscreteFI[2];
  real_T rtb_IdqErr[2];
  real_T rtb_KPek1[2];
  real_T rtb_TrafoMatrixuvwalphabeta[2];
  real_T rtb_TrafoMatrixuvwalphabeta_a[2];
  real_T TmpSignalConversionAtDiscrete_m;
  real_T f_2_w_el;
  real_T rtb_Add;
  real_T rtb_Gain1_idx_1;
  real_T rtb_Gain1_idx_2;
  real_T rtb_Gain_b;
  real_T rtb_Gain_i_tmp;
  real_T rtb_IntegEnaSwitch1_m_idx_0;
  real_T rtb_KPek1_a_idx_0;
  real_T rtb_Product;
  real_T rtb_Product1_f_tmp;
  real_T rtb_Sqrt1;
  real_T rtb_Sum3;
  real_T rtb_Switch1_j;
  real_T rtb_Switch_Phi_0;
  real_T rtb_Switch_o;
  real_T rtb_TrafoMatrixuvwalphabeta_i;
  real_T rtb_TrigonometricFunction;
  real_T rtb_UnitDelay1_g;
  int32_T i;
  boolean_T rtb_AntiWindupLE;
  boolean_T rtb_LogicalOperator1;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_fastCTRL' */
  /* Logic: '<S1>/Logical Operator1' incorporates:
   *  Constant: '<S1>/Enable'
   *  Inport: '<Root>/FOC_Enable'
   */
  rtb_LogicalOperator1 = ((FOC_Enable != 0.0) && (FOC_fastCTRL_U->FOC_Enable_i
    != 0.0));

  /* Gain: '<S7>/f_2_w_el' incorporates:
   *  Constant: '<S7>/Uf_w_el'
   */
  f_2_w_el = 6.2831853071795862 * FOC_Uf_f_el;

  /* Product: '<S48>/Product' incorporates:
   *  Constant: '<S48>/FOC_T_fast'
   */
  rtb_Product = 1.0 / FOC_f_fastCTRL * f_2_w_el;

  /* Sum: '<S48>/Add' incorporates:
   *  UnitDelay: '<S48>/Unit Delay'
   */
  rtb_Add = rtb_Product + FOC_fastCTRL_DW->UnitDelay_DSTATE;

  /* Gain: '<S38>/TrafoMatrix uvw->alphabeta' incorporates:
   *  Inport: '<Root>/I_ph [A]'
   */
  for (i = 0; i < 2; i++) {
    rtb_TrafoMatrixuvwalphabeta[i] = (FOC_fastCTRL_ConstP.pooled9[i + 2] *
      FOC_fastCTRL_U->I_phA[1] + FOC_fastCTRL_ConstP.pooled9[i] *
      FOC_fastCTRL_U->I_phA[0]) + FOC_fastCTRL_ConstP.pooled9[i + 4] *
      FOC_fastCTRL_U->I_phA[2];
  }

  /* End of Gain: '<S38>/TrafoMatrix uvw->alphabeta' */

  /* Gain: '<S26>/Gain5' incorporates:
   *  UnitDelay: '<S33>/Unit Delay1'
   */
  w_el = Factor_OmegaRot * FOC_fastCTRL_DW->UnitDelay1_DSTATE;

  /* Relay: '<S5>/AutoSwitchHysteresis' */
  FOC_fastCTRL_DW->AutoSwitchHysteresis_Mode = ((w_el >=
    FOC_AngleEst_AutoSwitch_wel_on) || ((!(w_el <=
    FOC_AngleEst_AutoSwitch_wel_off)) &&
    FOC_fastCTRL_DW->AutoSwitchHysteresis_Mode));

  /* MultiPortSwitch: '<S5>/Selectphicalc3' incorporates:
   *  Constant: '<S5>/Constant5'
   */
  if ((int32_T)FOC_SELECT_AngleEst_AutoSwitch == 0) {
    /* MultiPortSwitch: '<S5>/Selectphicalc3' incorporates:
     *  Constant: '<S5>/Constant1'
     */
    Phi_AngleEst_AutoSwitch = FOC_SELECT_AngleEst;
  } else {
    /* MultiPortSwitch: '<S5>/Selectphicalc3' incorporates:
     *  Relay: '<S5>/AutoSwitchHysteresis'
     */
    Phi_AngleEst_AutoSwitch = FOC_fastCTRL_DW->AutoSwitchHysteresis_Mode;
  }

  /* End of MultiPortSwitch: '<S5>/Selectphicalc3' */

  /* Switch: '<S25>/Switch' incorporates:
   *  Constant: '<S5>/Constant2'
   *  Constant: '<S5>/Constant4'
   *  Switch: '<S24>/Switch'
   */
  if (FOC_SELECT_AngleAdaption2PolePairs > 0.0) {
    rtb_Switch1_j = 0.0;
  } else if (FOC_SELECT_AngleAdaptionRange != 0.0) {
    /* Switch: '<S31>/Switch1' incorporates:
     *  Constant: '<S31>/Constant'
     *  Inport: '<Root>/phi_el [rad]'
     *  Sum: '<S31>/Sum2'
     *  Switch: '<S24>/Switch'
     */
    if (FOC_fastCTRL_U->phi_elrad > 6.2831853071795862) {
      rtb_Switch1_j = FOC_fastCTRL_U->phi_elrad - 6.2831853071795862;
    } else {
      rtb_Switch1_j = FOC_fastCTRL_U->phi_elrad;
    }

    /* End of Switch: '<S31>/Switch1' */

    /* Switch: '<S31>/Switch2' incorporates:
     *  Constant: '<S31>/Constant1'
     *  Sum: '<S31>/Sum3'
     *  Switch: '<S24>/Switch'
     */
    if (!(rtb_Switch1_j > 0.0)) {
      rtb_Switch1_j += 6.2831853071795862;
    }

    /* End of Switch: '<S31>/Switch2' */
  } else {
    /* Switch: '<S24>/Switch' incorporates:
     *  Inport: '<Root>/phi_el [rad]'
     */
    rtb_Switch1_j = FOC_fastCTRL_U->phi_elrad;
  }

  /* End of Switch: '<S25>/Switch' */

  /* Switch: '<S27>/Switch' incorporates:
   *  Constant: '<S27>/Constant'
   *  Constant: '<S5>/FOC_Invert_Encoder'
   *  Sum: '<S27>/PhiInverted'
   */
  if (FOC_SELECT_InvertAngle != 0.0) {
    rtb_Switch1_j = 6.2831853071795862 - rtb_Switch1_j;
  }

  /* End of Switch: '<S27>/Switch' */

  /* Saturate: '<S5>/ResolverOffsetLimitation' */
  if (FOC_phi_offset > 6.2831853071795862) {
    rtb_Switch_o = 6.2831853071795862;
  } else if (FOC_phi_offset < 0.0) {
    rtb_Switch_o = 0.0;
  } else {
    rtb_Switch_o = FOC_phi_offset;
  }

  /* End of Saturate: '<S5>/ResolverOffsetLimitation' */

  /* Sum: '<S5>/Sum3' */
  rtb_Sum3 = rtb_Switch1_j + rtb_Switch_o;

  /* Trigonometry: '<S11>/Trigonometric Function' incorporates:
   *  Constant: '<S3>/FOC_AngleEst_Lq'
   *  Product: '<S3>/Product3'
   *  Sum: '<S3>/Sum1'
   *  UnitDelay: '<S15>/Unit Delay'
   */
  FOC_AngleEst_Psi_PM_alpha = FOC_fastCTRL_DW->UnitDelay_DSTATE_m[0] -
    FOC_AngleEst_Lq * rtb_TrafoMatrixuvwalphabeta[0];
  FOC_AngleEst_Psi_PM_beta = FOC_fastCTRL_DW->UnitDelay_DSTATE_m[1] -
    FOC_AngleEst_Lq * rtb_TrafoMatrixuvwalphabeta[1];
  rtb_TrigonometricFunction = rt_atan2d_snf(FOC_AngleEst_Psi_PM_beta,
    FOC_AngleEst_Psi_PM_alpha);

  /* Switch: '<S11>/Switch_Phi' incorporates:
   *  Constant: '<S11>/Constant'
   *  Sum: '<S11>/Sum1'
   */
  if (!(rtb_TrigonometricFunction > 0.0)) {
    rtb_TrigonometricFunction += 6.2831853071795862;
  }

  /* End of Switch: '<S11>/Switch_Phi' */

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' incorporates:
   *  Constant: '<S13>/FOC_f_fastCTRL'
   *  Product: '<S13>/Product'
   */
  rtb_Switch1_j = rtb_TrigonometricFunction * FOC_f_fastCTRL - 0.0 *
    FOC_fastCTRL_DW->DiscreteTransferFcn_states_o;

  /* Switch: '<S13>/Switch1' incorporates:
   *  Bias: '<S13>/Bias'
   *  Constant: '<S13>/Constant2'
   *  RelationalOperator: '<S13>/Relational Operator2'
   */
  if (rtb_TrigonometricFunction < 3.1415926535897931) {
    rtb_Switch_Phi_0 = rtb_TrigonometricFunction;
  } else {
    rtb_Switch_Phi_0 = rtb_TrigonometricFunction + -6.2831853071795862;
  }

  /* End of Switch: '<S13>/Switch1' */

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn1' incorporates:
   *  Constant: '<S13>/FOC_f_fastCTRL1'
   *  Product: '<S13>/Product1'
   */
  rtb_Switch_Phi_0 = rtb_Switch_Phi_0 * FOC_f_fastCTRL - 0.0 *
    FOC_fastCTRL_DW->DiscreteTransferFcn1_states;

  /* Switch: '<S13>/Switch_speed' incorporates:
   *  Constant: '<S13>/Constant'
   *  Constant: '<S13>/Constant1'
   *  Logic: '<S13>/Logical Operator'
   *  RelationalOperator: '<S13>/Relational Operator'
   *  RelationalOperator: '<S13>/Relational Operator1'
   */
  if ((rtb_TrigonometricFunction < 4.71238898038469) &&
      (rtb_TrigonometricFunction > 1.5707963267948966)) {
    /* Switch: '<S13>/Switch_speed' incorporates:
     *  DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn'
     */
    FOC_AngleEst_w_el = rtb_Switch1_j +
      -FOC_fastCTRL_DW->DiscreteTransferFcn_states_o;
  } else {
    /* Switch: '<S13>/Switch_speed' incorporates:
     *  DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn1'
     */
    FOC_AngleEst_w_el = rtb_Switch_Phi_0 +
      -FOC_fastCTRL_DW->DiscreteTransferFcn1_states;
  }

  /* End of Switch: '<S13>/Switch_speed' */

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S3>/useFilteredCorrection'
   *  UnitDelay: '<S12>/Unit Delay'
   */
  if (FOC_SELECT_AngleEst_w_el_filtered > 0.0) {
    rtb_Sqrt1 = FOC_fastCTRL_DW->UnitDelay_DSTATE_n;
  } else {
    rtb_Sqrt1 = FOC_AngleEst_w_el;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Switch: '<S3>/Switch' incorporates:
   *  Constant: '<S3>/Constant1'
   *  Constant: '<S3>/Constant2'
   */
  if (rtb_Sqrt1 > 0.0) {
    i = 1;
  } else {
    i = -1;
  }

  /* End of Switch: '<S3>/Switch' */

  /* Sum: '<S3>/Sum2' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/komp_kp'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Sum: '<S3>/Sum3'
   *  Trigonometry: '<S3>/Trigonometric Function'
   */
  rtb_Sqrt1 = rtb_TrigonometricFunction - (1.5707963267948966 - atan(1.0 /
    FOC_AngleEst_Komp_KP * fabs(rtb_Sqrt1))) * (real_T)i;

  /* Switch: '<S10>/Switch2' incorporates:
   *  Constant: '<S10>/Constant'
   *  Constant: '<S10>/Constant1'
   */
  if (rtb_Sqrt1 >= 6.2831853071795862) {
    rtb_TrigonometricFunction = -6.2831853071795862;
  } else {
    rtb_TrigonometricFunction = 0.0;
  }

  /* End of Switch: '<S10>/Switch2' */

  /* Switch: '<S10>/Switch1' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant3'
   */
  if (rtb_Sqrt1 >= 0.0) {
    TmpSignalConversionAtDiscrete_m = 0.0;
  } else {
    TmpSignalConversionAtDiscrete_m = 6.2831853071795862;
  }

  /* End of Switch: '<S10>/Switch1' */

  /* Sum: '<S10>/Sum1' */
  Phi_est = (rtb_TrigonometricFunction + rtb_Sqrt1) +
    TmpSignalConversionAtDiscrete_m;

  /* MultiPortSwitch: '<S5>/Selectphicalc1' */
  if ((int32_T)Phi_AngleEst_AutoSwitch == 0) {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' */
    Phi_el_I_Transformation = rtb_Sum3;
  } else {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' */
    Phi_el_I_Transformation = Phi_est;
  }

  /* End of MultiPortSwitch: '<S5>/Selectphicalc1' */

  /* Switch: '<S30>/Switch1' */
  if (Phi_el_I_Transformation > 6.2831853071795862) {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' incorporates:
     *  Constant: '<S30>/Constant'
     *  Sum: '<S30>/Sum2'
     */
    Phi_el_I_Transformation -= 6.2831853071795862;
  }

  /* End of Switch: '<S30>/Switch1' */

  /* Switch: '<S30>/Switch2' */
  if (!(Phi_el_I_Transformation > 0.0)) {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' incorporates:
     *  Constant: '<S30>/Constant1'
     *  Sum: '<S30>/Sum3'
     */
    Phi_el_I_Transformation += 6.2831853071795862;
  }

  /* End of Switch: '<S30>/Switch2' */

  /* MultiPortSwitch: '<S26>/Selectphicalc3' incorporates:
   *  Constant: '<S26>/Constant2'
   *  Constant: '<S26>/Constant3'
   */
  if ((int32_T)Phi_AngleEst_AutoSwitch == 0) {
    rtb_Switch_o = FOC_PhiSensorTdead;
  } else {
    rtb_Switch_o = FOC_PhiSensorTdead_AngleEst;
  }

  /* End of MultiPortSwitch: '<S26>/Selectphicalc3' */

  /* Sum: '<S26>/Sum3' incorporates:
   *  Product: '<S26>/Product3'
   *  UnitDelay: '<S33>/Unit Delay1'
   */
  rtb_TrigonometricFunction = FOC_fastCTRL_DW->UnitDelay1_DSTATE * rtb_Switch_o
    + Phi_el_I_Transformation;

  /* Sum: '<S32>/Sum' incorporates:
   *  UnitDelay: '<S32>/Unit Delay'
   */
  rtb_UnitDelay1_g = rtb_TrigonometricFunction -
    FOC_fastCTRL_DW->UnitDelay_DSTATE_g;

  /* Switch: '<S32>/Switch' incorporates:
   *  Constant: '<S32>/Constant2'
   *  Constant: '<S32>/Constant3'
   *  Constant: '<S32>/Constant4'
   *  RelationalOperator: '<S32>/Sprung?'
   */
  if (rtb_UnitDelay1_g < -3.1415926535897931) {
    rtb_Sqrt1 = 6.2831853071795862;
  } else {
    rtb_Sqrt1 = 0.0;
  }

  /* End of Switch: '<S32>/Switch' */

  /* Switch: '<S32>/Switch1' incorporates:
   *  Constant: '<S32>/Constant1'
   *  Constant: '<S32>/Constant5'
   *  Constant: '<S32>/Constant6'
   *  RelationalOperator: '<S32>/Sprung?1'
   */
  if (rtb_UnitDelay1_g > 3.1415926535897931) {
    rtb_UnitDelay1_g = -6.2831853071795862;
  } else {
    rtb_UnitDelay1_g = 0.0;
  }

  /* End of Switch: '<S32>/Switch1' */

  /* Sum: '<S26>/Sum7' incorporates:
   *  Sum: '<S32>/Sum2'
   *  UnitDelay: '<S26>/Unit Delay3'
   */
  Phi_Observer = FOC_fastCTRL_DW->UnitDelay3_DSTATE - (rtb_Sqrt1 +
    rtb_UnitDelay1_g);

  /* MultiPortSwitch: '<S5>/Selectphicalc2' incorporates:
   *  Constant: '<S5>/Constant3'
   */
  if ((int32_T)FOC_SELECT_phi != 1) {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' */
    Phi_el_I_Transformation = Phi_Observer;
  }

  /* End of MultiPortSwitch: '<S5>/Selectphicalc2' */

  /* Switch: '<S28>/Switch1' */
  if (Phi_el_I_Transformation > 6.2831853071795862) {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' incorporates:
     *  Constant: '<S28>/Constant'
     *  Sum: '<S28>/Sum2'
     */
    Phi_el_I_Transformation -= 6.2831853071795862;
  }

  /* End of Switch: '<S28>/Switch1' */

  /* Switch: '<S28>/Switch2' */
  if (!(Phi_el_I_Transformation > 0.0)) {
    /* MultiPortSwitch: '<S5>/Selectphicalc1' incorporates:
     *  Constant: '<S28>/Constant1'
     *  Sum: '<S28>/Sum3'
     *  Switch: '<S28>/Switch2'
     */
    Phi_el_I_Transformation += 6.2831853071795862;
  }

  /* End of Switch: '<S28>/Switch2' */

  /* Trigonometry: '<S38>/Trigonometric Function1' */
  rtb_UnitDelay1_g = cos(Phi_el_I_Transformation);

  /* Trigonometry: '<S38>/Trigonometric Function' */
  rtb_Sqrt1 = sin(Phi_el_I_Transformation);

  /* SignalConversion generated from: '<S38>/Discrete FIR Filter 20th order' incorporates:
   *  Product: '<S38>/TrafoProd'
   *  Product: '<S38>/TrafoProd1'
   *  Product: '<S38>/TrafoProd2'
   *  Product: '<S38>/TrafoProd3'
   *  Sum: '<S38>/TrafoSum'
   *  Sum: '<S38>/TrafoSum1'
   */
  TmpSignalConversionAtDiscreteFI[0] = rtb_TrafoMatrixuvwalphabeta[0] *
    rtb_UnitDelay1_g + rtb_Sqrt1 * rtb_TrafoMatrixuvwalphabeta[1];
  TmpSignalConversionAtDiscreteFI[1] = rtb_UnitDelay1_g *
    rtb_TrafoMatrixuvwalphabeta[1] - rtb_TrafoMatrixuvwalphabeta[0] * rtb_Sqrt1;

  /* Product: '<S41>/Product1' incorporates:
   *  Constant: '<S41>/FOC_KI'
   *  Constant: '<S41>/FOC_T_fast'
   *  Product: '<S45>/Product1'
   */
  rtb_Product1_f_tmp = 1.0 / FOC_f_fastCTRL * FOC_KI;
  for (i = 0; i < 2; i++) {
    /* Sum: '<S36>/IdqErr' incorporates:
     *  Inport: '<Root>/I_dq_Ref [A]'
     *  SignalConversion generated from: '<S1>/I_dq_Ref [A]'
     */
    rtb_Sqrt1 = FOC_fastCTRL_U->I_dq_RefA[i] - TmpSignalConversionAtDiscreteFI[i];

    /* Product: '<S41>/KP*e[k]1' incorporates:
     *  Constant: '<S41>/FOC_KP1'
     */
    rtb_KPek1[i] = rtb_Sqrt1 * FOC_KP;

    /* Sum: '<S36>/IdqErr' */
    rtb_IdqErr[i] = rtb_Sqrt1;

    /* Gain: '<S39>/TrafoMatrix uvw->alphabeta' incorporates:
     *  Inport: '<Root>/I_ph [A]'
     */
    rtb_TrafoMatrixuvwalphabeta_a[i] = (FOC_fastCTRL_ConstP.pooled9[i + 2] *
      FOC_fastCTRL_U->I_phA[4] + FOC_fastCTRL_ConstP.pooled9[i] *
      FOC_fastCTRL_U->I_phA[3]) + FOC_fastCTRL_ConstP.pooled9[i + 4] *
      FOC_fastCTRL_U->I_phA[5];
  }

  /* Sum: '<S6>/Sum1' incorporates:
   *  Constant: '<S6>/FOC_6ph_AngleShift'
   */
  rtb_Switch_o = Phi_el_I_Transformation + FOC_6ph_AngleShift;

  /* Trigonometry: '<S39>/Trigonometric Function1' */
  rtb_UnitDelay1_g = cos(rtb_Switch_o);

  /* Trigonometry: '<S39>/Trigonometric Function' */
  rtb_Switch_o = sin(rtb_Switch_o);

  /* SignalConversion generated from: '<S39>/Discrete FIR Filter 20th order' incorporates:
   *  Product: '<S39>/TrafoProd'
   *  Product: '<S39>/TrafoProd1'
   *  Product: '<S39>/TrafoProd2'
   *  Product: '<S39>/TrafoProd3'
   *  Sum: '<S39>/TrafoSum'
   *  Sum: '<S39>/TrafoSum1'
   */
  rtb_Sqrt1 = rtb_TrafoMatrixuvwalphabeta_a[0] * rtb_UnitDelay1_g + rtb_Switch_o
    * rtb_TrafoMatrixuvwalphabeta_a[1];
  TmpSignalConversionAtDiscrete_m = rtb_UnitDelay1_g *
    rtb_TrafoMatrixuvwalphabeta_a[1] - rtb_TrafoMatrixuvwalphabeta_a[0] *
    rtb_Switch_o;

  /* Sum: '<S37>/IdqErr' incorporates:
   *  Inport: '<Root>/I_dq_Ref [A]'
   *  SignalConversion generated from: '<S1>/I_dq_Ref [A]'
   */
  rtb_TrafoMatrixuvwalphabeta_i = FOC_fastCTRL_U->I_dq_RefA[0] - rtb_Sqrt1;

  /* Product: '<S45>/KP*e[k]1' incorporates:
   *  Constant: '<S45>/FOC_KP1'
   */
  rtb_KPek1_a_idx_0 = rtb_TrafoMatrixuvwalphabeta_i * FOC_KP;

  /* Sum: '<S37>/IdqErr' incorporates:
   *  Inport: '<Root>/I_dq_Ref [A]'
   *  SignalConversion generated from: '<S1>/I_dq_Ref [A]'
   */
  rtb_TrafoMatrixuvwalphabeta_a[0] = rtb_TrafoMatrixuvwalphabeta_i;
  rtb_TrafoMatrixuvwalphabeta_i = FOC_fastCTRL_U->I_dq_RefA[1] -
    TmpSignalConversionAtDiscrete_m;

  /* Product: '<S45>/KP*e[k]1' incorporates:
   *  Constant: '<S45>/FOC_KP1'
   */
  rtb_UnitDelay1_g = rtb_TrafoMatrixuvwalphabeta_i * FOC_KP;

  /* Sum: '<S5>/Sum' incorporates:
   *  Constant: '<S5>/FOC_T_fast'
   *  Constant: '<S5>/FOC_output_trafo_delay'
   *  Product: '<S5>/Product'
   */
  Phi_el_U_Transformation = FOC_output_trafo_delay * w_el * (1.0 /
    FOC_f_fastCTRL) + Phi_el_I_Transformation;

  /* Switch: '<S29>/Switch1' */
  if (Phi_el_U_Transformation > 6.2831853071795862) {
    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S29>/Constant'
     *  Sum: '<S29>/Sum2'
     */
    Phi_el_U_Transformation -= 6.2831853071795862;
  }

  /* End of Switch: '<S29>/Switch1' */

  /* Switch: '<S29>/Switch2' */
  if (!(Phi_el_U_Transformation > 0.0)) {
    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S29>/Constant1'
     *  Sum: '<S29>/Sum3'
     *  Switch: '<S29>/Switch2'
     */
    Phi_el_U_Transformation += 6.2831853071795862;
  }

  /* End of Switch: '<S29>/Switch2' */

  /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
   *  Constant: '<S5>/FOC_6ph_AngleShift'
   *  Constant: '<S7>/FOC_6ph_AngleShift'
   *  Constant: '<S7>/Uf_Ud'
   *  Inport: '<Root>/FOC_Mode'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S7>/Sum1'
   */
  switch ((int32_T)FOC_fastCTRL_U->FOC_Mode) {
   case 0:
    for (i = 0; i < 6; i++) {
      rtb_SelectControlMode[i] = 0.0;
    }
    break;

   case 1:
    for (i = 0; i < 6; i++) {
      rtb_SelectControlMode[i] = 0.0;
    }
    break;

   case 2:
    /* Gain: '<S49>/Gain' incorporates:
     *  DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn'
     */
    rtb_Gain_b = 0.0050000000000000044 *
      FOC_fastCTRL_DW->DiscreteTransferFcn_states * FOC_Uf_m;

    /* Abs: '<S49>/Abs' */
    rtb_Gain1_idx_1 = fabs(rtb_Gain_b);

    /* Saturate: '<S49>/Saturation1' */
    if (rtb_Gain1_idx_1 > FOC_Uf_U_max) {
      rtb_Gain1_idx_1 = FOC_Uf_U_max;
    } else if (rtb_Gain1_idx_1 < FOC_Uf_U_min) {
      rtb_Gain1_idx_1 = FOC_Uf_U_min;
    }

    /* End of Saturate: '<S49>/Saturation1' */

    /* Signum: '<S49>/Sign' */
    if (!rtIsNaN(rtb_Gain_b)) {
      if (rtb_Gain_b < 0.0) {
        rtb_Gain_b = -1.0;
      } else {
        rtb_Gain_b = (rtb_Gain_b > 0.0);
      }
    }

    /* End of Signum: '<S49>/Sign' */

    /* Product: '<S49>/Product' */
    rtb_Gain_b *= rtb_Gain1_idx_1;
    rtb_SelectControlMode[0] = FOC_Uf_Ud;
    rtb_SelectControlMode[1] = rtb_Gain_b;
    rtb_SelectControlMode[2] = FOC_Uf_Ud;
    rtb_SelectControlMode[3] = rtb_Gain_b;
    rtb_SelectControlMode[4] = rtb_Add;
    rtb_SelectControlMode[5] = rtb_Add + FOC_6ph_AngleShift;
    break;

   default:
    /* Switch: '<S41>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S41>/Zero'
     *  Constant: '<S45>/Zero'
     *  Product: '<S41>/Product1'
     *  Product: '<S41>/Product2'
     *  Product: '<S45>/Product2'
     *  Sum: '<S41>/IntSum1'
     *  Sum: '<S45>/IntSum1'
     *  Switch: '<S45>/IntegEnaSwitch1'
     *  UnitDelay: '<S41>/IntegDelay1'
     *  UnitDelay: '<S45>/IntegDelay1'
     */
    if (rtb_LogicalOperator1) {
      rtb_SelectControlMode[0] = FOC_fastCTRL_DW->IntegDelay1_DSTATE[0] *
        rtb_Product1_f_tmp + rtb_KPek1[0];
      rtb_SelectControlMode[2] = FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0] *
        rtb_Product1_f_tmp + rtb_KPek1_a_idx_0;
      rtb_SelectControlMode[1] = FOC_fastCTRL_DW->IntegDelay1_DSTATE[1] *
        rtb_Product1_f_tmp + rtb_KPek1[1];
      rtb_SelectControlMode[3] = FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1] *
        rtb_Product1_f_tmp + rtb_UnitDelay1_g;
    } else {
      rtb_SelectControlMode[0] = 0.0;
      rtb_SelectControlMode[2] = 0.0;
      rtb_SelectControlMode[1] = 0.0;
      rtb_SelectControlMode[3] = 0.0;
    }

    /* End of Switch: '<S41>/IntegEnaSwitch1' */
    rtb_SelectControlMode[4] = Phi_el_U_Transformation;
    rtb_SelectControlMode[5] = Phi_el_U_Transformation + FOC_6ph_AngleShift;
    break;
  }

  /* End of MultiPortSwitch: '<S1>/SelectControlMode' */

  /* Trigonometry: '<S56>/Trigonometric Function' */
  rtb_Switch_o = sin(rtb_SelectControlMode[4]);

  /* Gain: '<S56>/Gain1' */
  rtb_IntegEnaSwitch1_m_idx_0 = 0.0 * rtb_Switch_o;
  rtb_Gain1_idx_1 = rtb_Switch_o;
  rtb_Gain1_idx_2 = -rtb_Switch_o;

  /* Trigonometry: '<S56>/Trigonometric Function1' */
  rtb_Switch_o = cos(rtb_SelectControlMode[4]);

  /* Sum: '<S56>/Sum1' incorporates:
   *  Gain: '<S56>/Gain'
   *  Gain: '<S56>/Gain1'
   */
  rtb_Gain_i_tmp = rtb_IntegEnaSwitch1_m_idx_0 + rtb_Switch_o;

  /* Product: '<S56>/Product' incorporates:
   *  Gain: '<S56>/Gain'
   *  Gain: '<S56>/Gain1'
   *  Sum: '<S56>/Sum1'
   */
  rtb_Gain_b = (0.0 * rtb_Switch_o + rtb_Gain1_idx_2) * rtb_SelectControlMode[1]
    + rtb_Gain_i_tmp * rtb_SelectControlMode[0];
  rtb_Gain_i_tmp = (0.0 * rtb_Switch_o + rtb_Gain1_idx_1) *
    rtb_SelectControlMode[0] + rtb_Gain_i_tmp * rtb_SelectControlMode[1];

  /* Trigonometry: '<S57>/Trigonometric Function' */
  rtb_Switch_o = sin(rtb_SelectControlMode[5]);

  /* Gain: '<S57>/Gain1' */
  rtb_IntegEnaSwitch1_m_idx_0 = 0.0 * rtb_Switch_o;
  rtb_Gain1_idx_1 = rtb_Switch_o;
  rtb_Gain1_idx_2 = -rtb_Switch_o;

  /* Trigonometry: '<S57>/Trigonometric Function1' */
  rtb_Switch_o = cos(rtb_SelectControlMode[5]);

  /* Sum: '<S57>/Sum1' incorporates:
   *  Gain: '<S57>/Gain'
   *  Gain: '<S57>/Gain1'
   */
  rtb_IntegEnaSwitch1_m_idx_0 += rtb_Switch_o;

  /* Product: '<S57>/Product' incorporates:
   *  Gain: '<S57>/Gain'
   *  Gain: '<S57>/Gain1'
   *  Sum: '<S57>/Sum1'
   */
  rtb_Gain1_idx_2 = (0.0 * rtb_Switch_o + rtb_Gain1_idx_2) *
    rtb_SelectControlMode[3] + rtb_IntegEnaSwitch1_m_idx_0 *
    rtb_SelectControlMode[2];
  rtb_IntegEnaSwitch1_m_idx_0 = (0.0 * rtb_Switch_o + rtb_Gain1_idx_1) *
    rtb_SelectControlMode[2] + rtb_IntegEnaSwitch1_m_idx_0 *
    rtb_SelectControlMode[3];

  /* Switch: '<S1>/Switch1' incorporates:
   *  Constant: '<S1>/0: P_Udc 1: Udc_measured'
   */
  if (FOC_SELECT_U_DC_INPUT > 0.0) {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Inport: '<Root>/U_DC [V]'
     */
    FOC_U_DC = FOC_fastCTRL_U->U_DCV;
  } else {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Udc1'
     */
    FOC_U_DC = FOC_MANUAL_U_DC;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Outputs for Atomic SubSystem: '<S8>/Calc_Modulation_Index' */
  /* Outputs for Atomic SubSystem: '<S8>/NormalizedVoltage' */
  /* MinMax: '<S52>/AvoidDivBy0' incorporates:
   *  Constant: '<S52>/Constant2'
   *  Gain: '<S52>/U_DC//2'
   *  MinMax: '<S51>/AvoidDivBy0'
   */
  rtb_Switch_o = fmax(1.0, 0.5 * FOC_U_DC);

  /* End of Outputs for SubSystem: '<S8>/Calc_Modulation_Index' */

  /* Product: '<S52>/Divide3' incorporates:
   *  Constant: '<S54>/Constant'
   *  Constant: '<S55>/Constant'
   *  MinMax: '<S52>/AvoidDivBy0'
   *  Product: '<S54>/Product'
   *  Product: '<S55>/Product'
   */
  for (i = 0; i < 3; i++) {
    /* Product: '<S54>/Product' incorporates:
     *  Constant: '<S54>/Constant'
     *  Constant: '<S55>/Constant'
     *  Product: '<S55>/Product'
     */
    rtb_Gain1_idx_1 = FOC_fastCTRL_ConstP.pooled8[i + 3];
    rtb_SelectControlMode[i] = (rtb_Gain1_idx_1 * rtb_Gain_i_tmp +
      FOC_fastCTRL_ConstP.pooled8[i] * rtb_Gain_b) / rtb_Switch_o;
    rtb_SelectControlMode[i + 3] = (rtb_Gain1_idx_1 *
      rtb_IntegEnaSwitch1_m_idx_0 + FOC_fastCTRL_ConstP.pooled8[i] *
      rtb_Gain1_idx_2) / rtb_Switch_o;
  }

  /* End of Product: '<S52>/Divide3' */
  /* End of Outputs for SubSystem: '<S8>/NormalizedVoltage' */

  /* Switch: '<S2>/AKS_Switch' */
  if (rtb_LogicalOperator1) {
    /* MultiPortSwitch: '<S8>/SelectModulation' incorporates:
     *  Constant: '<S8>/Enable_SuperSinMod'
     *  Sum: '<S53>/Sum4'
     */
    if ((int32_T)FOC_SELECT_Modulation != 0) {
      /* Outputs for Atomic SubSystem: '<S8>/Super_Sinus_Modulation' */
      /* Gain: '<S53>/Factor' incorporates:
       *  MinMax: '<S53>/MinMax2'
       *  MinMax: '<S53>/MinMax3'
       *  Sum: '<S53>/Sum1'
       */
      rtb_Gain1_idx_1 = (fmin(fmin(rtb_SelectControlMode[0],
        rtb_SelectControlMode[1]), rtb_SelectControlMode[2]) + fmax(fmax
        (rtb_SelectControlMode[0], rtb_SelectControlMode[1]),
        rtb_SelectControlMode[2])) * 0.5;

      /* Sum: '<S53>/Sum3' */
      rtb_Sum3_f_0[0] = rtb_SelectControlMode[0] - rtb_Gain1_idx_1;
      rtb_Sum3_f_0[1] = rtb_SelectControlMode[1] - rtb_Gain1_idx_1;
      rtb_Sum3_f_0[2] = rtb_SelectControlMode[2] - rtb_Gain1_idx_1;

      /* Gain: '<S53>/Factor1' incorporates:
       *  MinMax: '<S53>/MinMax1'
       *  MinMax: '<S53>/MinMax4'
       *  Sum: '<S53>/Sum2'
       */
      rtb_Gain1_idx_1 = (fmin(fmin(rtb_SelectControlMode[3],
        rtb_SelectControlMode[4]), rtb_SelectControlMode[5]) + fmax(fmax
        (rtb_SelectControlMode[3], rtb_SelectControlMode[4]),
        rtb_SelectControlMode[5])) * 0.5;
      rtb_Sum3_f_0[3] = rtb_SelectControlMode[3] - rtb_Gain1_idx_1;
      rtb_Sum3_f_0[4] = rtb_SelectControlMode[4] - rtb_Gain1_idx_1;
      rtb_Sum3_f_0[5] = rtb_SelectControlMode[5] - rtb_Gain1_idx_1;

      /* End of Outputs for SubSystem: '<S8>/Super_Sinus_Modulation' */
      for (i = 0; i < 6; i++) {
        rtb_SelectControlMode[i] = rtb_Sum3_f_0[i];
      }
    }

    /* End of MultiPortSwitch: '<S8>/SelectModulation' */

    /* Outport: '<Root>/DutyCycles [0..1]' */
    for (i = 0; i < 6; i++) {
      /* Gain: '<S50>/[0..1]' incorporates:
       *  Bias: '<S50>/[0..2]'
       */
      rtb_Gain1_idx_1 = (rtb_SelectControlMode[i] + 1.0) * 0.5;

      /* Saturate: '<S50>/Limit [0..1]' */
      if (rtb_Gain1_idx_1 > 1.0) {
        FOC_fastCTRL_Y->DutyCycles01[i] = 1.0;
      } else if (rtb_Gain1_idx_1 < 0.0) {
        FOC_fastCTRL_Y->DutyCycles01[i] = 0.0;
      } else {
        FOC_fastCTRL_Y->DutyCycles01[i] = rtb_Gain1_idx_1;
      }

      /* End of Saturate: '<S50>/Limit [0..1]' */
    }
  } else {
    /* MultiPortSwitch: '<S2>/AKS Switch' incorporates:
     *  Constant: '<S2>/FOC_AKS_Mode'
     */
    switch ((int32_T)FOC_AKS_Mode) {
     case 1:
      /* Outport: '<Root>/DutyCycles [0..1]' */
      for (i = 0; i < 6; i++) {
        FOC_fastCTRL_Y->DutyCycles01[i] = 0.0;
      }
      break;

     case 2:
      /* Outport: '<Root>/DutyCycles [0..1]' */
      for (i = 0; i < 6; i++) {
        FOC_fastCTRL_Y->DutyCycles01[i] = 1.0;
      }
      break;

     default:
      /* Outport: '<Root>/DutyCycles [0..1]' */
      for (i = 0; i < 6; i++) {
        FOC_fastCTRL_Y->DutyCycles01[i] = 0.5;
      }
      break;
    }

    /* End of MultiPortSwitch: '<S2>/AKS Switch' */
  }

  /* End of Switch: '<S2>/AKS_Switch' */

  /* Outputs for Atomic SubSystem: '<S8>/Calc_Modulation_Index' */
  /* Product: '<S51>/Divide3' incorporates:
   *  Math: '<S51>/Square'
   *  Math: '<S51>/Square1'
   *  Sqrt: '<S51>/Sqrt'
   *  Sqrt: '<S51>/Sqrt1'
   *  Sum: '<S51>/Sum'
   *  Sum: '<S51>/Sum1'
   */
  FOC_fastCTRL_Y->ModInd[0] = sqrt(rtb_Gain_b * rtb_Gain_b + rtb_Gain_i_tmp *
    rtb_Gain_i_tmp) / rtb_Switch_o;
  FOC_fastCTRL_Y->ModInd[1] = sqrt(rtb_Gain1_idx_2 * rtb_Gain1_idx_2 +
    rtb_IntegEnaSwitch1_m_idx_0 * rtb_IntegEnaSwitch1_m_idx_0) / rtb_Switch_o;

  /* End of Outputs for SubSystem: '<S8>/Calc_Modulation_Index' */

  /* Switch: '<S14>/Switch3' incorporates:
   *  Constant: '<S14>/FOC_AngleEst_Delay2'
   */
  rtb_AntiWindupLE = (FOC_AngleEst_Delay2 > 0.5);

  /* Product: '<S15>/Product' incorporates:
   *  Constant: '<S15>/FOC_T_fast'
   */
  rtb_Switch_o = 1.0 / FOC_f_fastCTRL;

  /* Switch: '<S14>/Switch4' incorporates:
   *  Constant: '<S14>/FOC_AngleEst_Delay1'
   *  UnitDelay: '<S14>/Unit Delay1'
   */
  if (FOC_AngleEst_Delay1 > 0.5) {
    rtb_Gain1_idx_2 = FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[0];
  } else {
    rtb_Gain1_idx_2 = rtb_Gain_b;
  }

  /* UnitDelay: '<S14>/Unit Delay' incorporates:
   *  UnitDelay: '<S14>/Unit Delay1'
   */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[0] = FOC_fastCTRL_DW->UnitDelay_DSTATE_o
    [0];

  /* Switch: '<S14>/Switch3' incorporates:
   *  UnitDelay: '<S14>/Unit Delay1'
   */
  if (!rtb_AntiWindupLE) {
    FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[0] = rtb_Gain1_idx_2;
  }

  /* Sum: '<S15>/Sum4' incorporates:
   *  Constant: '<S3>/FOC_AngleEst_Rs'
   *  Constant: '<S3>/komp_kp'
   *  Product: '<S15>/Product'
   *  Product: '<S16>/Product'
   *  Product: '<S3>/Product2'
   *  Sum: '<S3>/Sum'
   *  UnitDelay: '<S14>/Unit Delay1'
   *  UnitDelay: '<S15>/Unit Delay'
   */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_m[0] +=
    ((FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[0] - FOC_AngleEst_Psi_PM_alpha *
      FOC_AngleEst_Komp_KP) - FOC_AngleEst_Rs * rtb_TrafoMatrixuvwalphabeta[0]) *
    rtb_Switch_o;

  /* Switch: '<S14>/Switch4' incorporates:
   *  Constant: '<S14>/FOC_AngleEst_Delay1'
   *  UnitDelay: '<S14>/Unit Delay1'
   */
  rtb_IntegEnaSwitch1_m_idx_0 = rtb_Gain1_idx_2;
  if (FOC_AngleEst_Delay1 > 0.5) {
    rtb_Gain1_idx_2 = FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[1];
  } else {
    rtb_Gain1_idx_2 = rtb_Gain_i_tmp;
  }

  /* UnitDelay: '<S14>/Unit Delay' incorporates:
   *  UnitDelay: '<S14>/Unit Delay1'
   */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[1] = FOC_fastCTRL_DW->UnitDelay_DSTATE_o
    [1];

  /* Switch: '<S14>/Switch3' incorporates:
   *  UnitDelay: '<S14>/Unit Delay1'
   */
  if (!rtb_AntiWindupLE) {
    FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[1] = rtb_Gain1_idx_2;
  }

  /* Sum: '<S15>/Sum4' incorporates:
   *  Constant: '<S3>/FOC_AngleEst_Rs'
   *  Constant: '<S3>/komp_kp'
   *  Product: '<S15>/Product'
   *  Product: '<S16>/Product'
   *  Product: '<S3>/Product2'
   *  Sum: '<S3>/Sum'
   *  UnitDelay: '<S14>/Unit Delay1'
   *  UnitDelay: '<S15>/Unit Delay'
   */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_m[1] +=
    ((FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[1] - FOC_AngleEst_Psi_PM_beta *
      FOC_AngleEst_Komp_KP) - FOC_AngleEst_Rs * rtb_TrafoMatrixuvwalphabeta[1]) *
    rtb_Switch_o;

  /* Switch: '<S45>/IntegStopSwitch2' incorporates:
   *  Constant: '<S45>/Zero1'
   *  UnitDelay: '<S45>/IntegDelay1'
   */
  if (rtb_LogicalOperator1) {
    /* Switch: '<S45>/IntegStopSwitch3' incorporates:
     *  Constant: '<S45>/Zero1'
     *  UnitDelay: '<S45>/IntegDelay1'
     */
    if (rtb_Product1_f_tmp > 0.0) {
      rtb_Switch_o = FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0];
      rtb_Gain1_idx_1 = FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1];
    } else {
      rtb_Switch_o = 0.0;
      rtb_Gain1_idx_1 = 0.0;
    }

    /* End of Switch: '<S45>/IntegStopSwitch3' */

    /* RelationalOperator: '<S44>/AntiWindupLE' incorporates:
     *  Constant: '<S44>/FOC_MaxModInd'
     */
    rtb_AntiWindupLE = (FOC_fastCTRL_Y->ModInd[1] <= FOC_MaxModInd);

    /* Switch: '<S45>/IntegStopSwitch1' incorporates:
     *  Constant: '<S46>/Constant'
     *  Constant: '<S47>/Constant'
     *  Gain: '<S45>/FOC_IntegDamp'
     *  Logic: '<S44>/AntiWindupOR_d'
     *  Logic: '<S44>/AntiWindupOR_q'
     *  Product: '<S44>/antiWindupProd'
     *  RelationalOperator: '<S46>/Compare'
     *  RelationalOperator: '<S47>/Compare'
     *  Sum: '<S45>/IntSum2'
     *  UnitDelay: '<S45>/IntegDelay1'
     */
    if ((rtb_TrafoMatrixuvwalphabeta_a[0] *
         FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0] < 0.0) || rtb_AntiWindupLE) {
      FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0] = rtb_KPek1_a_idx_0 +
        rtb_Switch_o;
    } else {
      FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0] = FOC_IntegDamp * rtb_Switch_o;
    }

    if (rtb_AntiWindupLE || (rtb_TrafoMatrixuvwalphabeta_i *
         FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1] < 0.0)) {
      FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1] = rtb_UnitDelay1_g +
        rtb_Gain1_idx_1;
    } else {
      FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1] = FOC_IntegDamp * rtb_Gain1_idx_1;
    }

    /* End of Switch: '<S45>/IntegStopSwitch1' */
  } else {
    FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[0] = 0.0;
    FOC_fastCTRL_DW->IntegDelay1_DSTATE_g[1] = 0.0;
  }

  /* End of Switch: '<S45>/IntegStopSwitch2' */

  /* DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
  rtb_TrafoMatrixuvwalphabeta_i = rtb_Sqrt1 * 0.05;
  for (i = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ; i < 19; i++) {
    rtb_TrafoMatrixuvwalphabeta_i +=
      FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i] * 0.05;
  }

  for (i = 0; i < FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ; i++) {
    rtb_TrafoMatrixuvwalphabeta_i +=
      FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i] * 0.05;
  }

  /* Outport: '<Root>/I_dq_Act [A]' incorporates:
   *  DiscreteFir: '<S39>/Discrete FIR Filter 20th order'
   */
  FOC_fastCTRL_Y->I_dq_ActA[2] = rtb_TrafoMatrixuvwalphabeta_i;

  /* DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
  rtb_TrafoMatrixuvwalphabeta_i = TmpSignalConversionAtDiscrete_m * 0.05;
  for (i = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ; i < 19; i++) {
    rtb_TrafoMatrixuvwalphabeta_i +=
      FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i + 19] * 0.05;
  }

  for (i = 0; i < FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ; i++) {
    rtb_TrafoMatrixuvwalphabeta_i +=
      FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[i + 19] * 0.05;
  }

  /* Switch: '<S41>/IntegStopSwitch2' incorporates:
   *  Constant: '<S41>/Zero1'
   *  UnitDelay: '<S41>/IntegDelay1'
   */
  if (rtb_LogicalOperator1) {
    /* Switch: '<S41>/IntegStopSwitch3' incorporates:
     *  Constant: '<S41>/Zero1'
     *  Product: '<S41>/Product1'
     *  UnitDelay: '<S41>/IntegDelay1'
     */
    if (rtb_Product1_f_tmp > 0.0) {
      rtb_TrafoMatrixuvwalphabeta_a[0] = FOC_fastCTRL_DW->IntegDelay1_DSTATE[0];
      rtb_TrafoMatrixuvwalphabeta_a[1] = FOC_fastCTRL_DW->IntegDelay1_DSTATE[1];
    } else {
      rtb_TrafoMatrixuvwalphabeta_a[0] = 0.0;
      rtb_TrafoMatrixuvwalphabeta_a[1] = 0.0;
    }

    /* End of Switch: '<S41>/IntegStopSwitch3' */

    /* RelationalOperator: '<S40>/AntiWindupLE' incorporates:
     *  Constant: '<S40>/FOC_MaxModInd'
     */
    rtb_LogicalOperator1 = (FOC_fastCTRL_Y->ModInd[0] <= FOC_MaxModInd);

    /* Switch: '<S41>/IntegStopSwitch1' incorporates:
     *  Constant: '<S42>/Constant'
     *  Constant: '<S43>/Constant'
     *  Gain: '<S41>/FOC_IntegDamp'
     *  Logic: '<S40>/AntiWindupOR_d'
     *  Logic: '<S40>/AntiWindupOR_q'
     *  Product: '<S40>/antiWindupProd'
     *  RelationalOperator: '<S42>/Compare'
     *  RelationalOperator: '<S43>/Compare'
     *  Sum: '<S41>/IntSum2'
     *  UnitDelay: '<S41>/IntegDelay1'
     */
    if ((rtb_IdqErr[0] * FOC_fastCTRL_DW->IntegDelay1_DSTATE[0] < 0.0) ||
        rtb_LogicalOperator1) {
      FOC_fastCTRL_DW->IntegDelay1_DSTATE[0] = rtb_KPek1[0] +
        rtb_TrafoMatrixuvwalphabeta_a[0];
    } else {
      FOC_fastCTRL_DW->IntegDelay1_DSTATE[0] = FOC_IntegDamp *
        rtb_TrafoMatrixuvwalphabeta_a[0];
    }

    if (rtb_LogicalOperator1 || (rtb_IdqErr[1] *
         FOC_fastCTRL_DW->IntegDelay1_DSTATE[1] < 0.0)) {
      FOC_fastCTRL_DW->IntegDelay1_DSTATE[1] = rtb_KPek1[1] +
        rtb_TrafoMatrixuvwalphabeta_a[1];
    } else {
      FOC_fastCTRL_DW->IntegDelay1_DSTATE[1] = FOC_IntegDamp *
        rtb_TrafoMatrixuvwalphabeta_a[1];
    }

    /* End of Switch: '<S41>/IntegStopSwitch1' */
  } else {
    FOC_fastCTRL_DW->IntegDelay1_DSTATE[0] = 0.0;
    FOC_fastCTRL_DW->IntegDelay1_DSTATE[1] = 0.0;
  }

  /* End of Switch: '<S41>/IntegStopSwitch2' */

  /* DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
  rtb_Product1_f_tmp = TmpSignalConversionAtDiscreteFI[0] * 0.05;
  for (i = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a; i < 19; i++) {
    rtb_Product1_f_tmp += FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_h[i] *
      0.05;
  }

  for (i = 0; i < FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a; i++) {
    rtb_Product1_f_tmp += FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_h[i] *
      0.05;
  }

  /* Outport: '<Root>/I_dq_Act [A]' incorporates:
   *  DiscreteFir: '<S38>/Discrete FIR Filter 20th order'
   */
  FOC_fastCTRL_Y->I_dq_ActA[0] = rtb_Product1_f_tmp;

  /* DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
  rtb_Product1_f_tmp = TmpSignalConversionAtDiscreteFI[1] * 0.05;
  for (i = FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a; i < 19; i++) {
    rtb_Product1_f_tmp += FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_h[i +
      19] * 0.05;
  }

  for (i = 0; i < FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a; i++) {
    rtb_Product1_f_tmp += FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_h[i +
      19] * 0.05;
  }

  /* Trigonometry: '<S9>/Trigonometric Function' incorporates:
   *  Sum: '<S9>/Sum2'
   *  Trigonometry: '<S58>/Trigonometric Function'
   *  Trigonometry: '<S59>/Trigonometric Function'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  rtb_KPek1_a_idx_0 = cos(rt_atan2d_snf(rtb_TrafoMatrixuvwalphabeta[1],
    rtb_TrafoMatrixuvwalphabeta[0]) - rt_atan2d_snf
    (FOC_fastCTRL_DW->UnitDelay_DSTATE_b[1], FOC_fastCTRL_DW->
     UnitDelay_DSTATE_b[0]));

  /* DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */
  FOC_fastCTRL_B->DiscreteFIRFilter10thorder = rtb_KPek1_a_idx_0 * 0.1;
  for (i = FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ; i < 9; i++) {
    FOC_fastCTRL_B->DiscreteFIRFilter10thorder +=
      FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_stat[i] * 0.1;
  }

  for (i = 0; i < FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ; i++) {
    FOC_fastCTRL_B->DiscreteFIRFilter10thorder +=
      FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_stat[i] * 0.1;
  }

  /* End of DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */

  /* Sum: '<S5>/phi_est_error2' */
  Phi_est_error_I_Trafo = Phi_el_I_Transformation - Phi_est;

  /* Sum: '<S26>/Deviation' */
  rtb_Switch_o = rtb_TrigonometricFunction - Phi_Observer;

  /* Sum: '<S26>/Sum6' incorporates:
   *  Constant: '<S26>/Constant'
   *  Constant: '<S26>/Constant1'
   *  Constant: '<S26>/FOC_T_fast'
   *  Gain: '<S26>/Gain'
   *  Product: '<S26>/Product'
   *  Product: '<S26>/Product2'
   *  Sum: '<S26>/Sum1'
   *  UnitDelay: '<S26>/Unit Delay3'
   *  UnitDelay: '<S33>/Unit Delay1'
   */
  FOC_fastCTRL_DW->UnitDelay3_DSTATE = (FOC_AngleObserver_w0 *
    FOC_AngleObserver_D * rtb_Switch_o * 2.0 +
    FOC_fastCTRL_DW->UnitDelay1_DSTATE) * (1.0 / FOC_f_fastCTRL) + Phi_Observer;

  /* UnitDelay: '<S34>/Unit Delay1' */
  rtb_UnitDelay1_g = FOC_fastCTRL_DW->UnitDelay1_DSTATE_he;

  /* Sum: '<S34>/Sum2' incorporates:
   *  Constant: '<S34>/FOC_T_fast'
   *  Gain: '<S26>/Gain4'
   *  Product: '<S34>/Product'
   *  UnitDelay: '<S34>/Unit Delay1'
   */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_he += FOC_OmegaObs3 * rtb_Switch_o * (1.0 /
    FOC_f_fastCTRL);

  /* Sum: '<S33>/Sum2' incorporates:
   *  Constant: '<S26>/Constant'
   *  Constant: '<S33>/FOC_T_fast'
   *  Product: '<S26>/Product1'
   *  Product: '<S33>/Product'
   *  Sum: '<S26>/Sum2'
   *  UnitDelay: '<S33>/Unit Delay1'
   */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE += (FOC_AngleObserver_w0 *
    FOC_AngleObserver_w0 * rtb_Switch_o + rtb_UnitDelay1_g) * (1.0 /
    FOC_f_fastCTRL);

  /* Sum: '<S5>/phi_est_error' */
  Phi_est_error = rtb_Sum3 - Phi_est;

  /* Product: '<S12>/T_ab' incorporates:
   *  Constant: '<S12>/Constant'
   *  Constant: '<S12>/FOC_f_fast'
   */
  rtb_Switch_o = 1.0 / FOC_f_fastCTRL;

  /* Product: '<S12>/Product3' incorporates:
   *  Constant: '<S12>/Tau'
   *  Product: '<S12>/Divide2'
   */
  rtb_Sum3 = rtb_Switch_o / FOC_AngleEst_w_el_filtered_Tau * FOC_AngleEst_w_el;

  /* Product: '<S12>/Divide' incorporates:
   *  Constant: '<S12>/Tau'
   *  Sum: '<S12>/Sum1'
   *  UnitDelay: '<S12>/Unit Delay'
   */
  rtb_UnitDelay1_g = (FOC_AngleEst_w_el_filtered_Tau - rtb_Switch_o) *
    FOC_fastCTRL_DW->UnitDelay_DSTATE_n / FOC_AngleEst_w_el_filtered_Tau;

  /* Switch: '<S48>/Switch' incorporates:
   *  Abs: '<S48>/Abs'
   *  Constant: '<S48>/Constant1'
   *  Gain: '<S48>/Gain1'
   */
  if (fabs(rtb_Add) >= 6.2831853071795862) {
    /* Signum: '<S48>/Sign' */
    if (!rtIsNaN(rtb_Product)) {
      if (rtb_Product < 0.0) {
        rtb_Product = -1.0;
      } else {
        rtb_Product = (rtb_Product > 0.0);
      }
    }

    /* End of Signum: '<S48>/Sign' */
    rtb_Switch_o = 6.2831853071795862 * rtb_Product;
  } else {
    rtb_Switch_o = 0.0;
  }

  /* End of Switch: '<S48>/Switch' */

  /* Sum: '<S48>/Add1' incorporates:
   *  UnitDelay: '<S48>/Unit Delay'
   */
  FOC_fastCTRL_DW->UnitDelay_DSTATE = rtb_Add - rtb_Switch_o;

  /* Gain: '<S5>/dummy_gain3' incorporates:
   *  Inport: '<Root>/phi_el [rad]'
   */
  Phi_Measured_Raw = FOC_fastCTRL_U->phi_elrad;

  /* Update for DiscreteTransferFcn: '<S7>/Discrete Transfer Fcn' */
  FOC_fastCTRL_DW->DiscreteTransferFcn_states = f_2_w_el - -0.995 *
    FOC_fastCTRL_DW->DiscreteTransferFcn_states;

  /* Update for UnitDelay: '<S12>/Unit Delay' incorporates:
   *  Sum: '<S12>/Sum'
   */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_n = rtb_Sum3 + rtb_UnitDelay1_g;

  /* Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  FOC_fastCTRL_DW->DiscreteTransferFcn_states_o = rtb_Switch1_j;

  /* Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn1' */
  FOC_fastCTRL_DW->DiscreteTransferFcn1_states = rtb_Switch_Phi_0;

  /* Update for UnitDelay: '<S32>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_g = rtb_TrigonometricFunction;

  /* Update for UnitDelay: '<S14>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[0] = rtb_Gain_b;

  /* Update for UnitDelay: '<S14>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_o[0] = rtb_IntegEnaSwitch1_m_idx_0;

  /* Update for UnitDelay: '<S14>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE_h[1] = rtb_Gain_i_tmp;

  /* Update for UnitDelay: '<S14>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_o[1] = rtb_Gain1_idx_2;

  /* Update for DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ--;
  if (FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ < 0) {
    FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ = 18;
  }

  /* Update circular buffer */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat
    [FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ] = rtb_Sqrt1;
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat
    [FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ + 19] =
    TmpSignalConversionAtDiscrete_m;

  /* End of Update for DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a--;
  if (FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a < 0) {
    FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a = 18;
  }

  /* Update circular buffer */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_h
    [FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a] =
    TmpSignalConversionAtDiscreteFI[0];

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_b[0] = rtb_Gain_b;

  /* Update for DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_h
    [FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a + 19] =
    TmpSignalConversionAtDiscreteFI[1];

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_b[1] = rtb_Gain_i_tmp;

  /* Update for DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */
  /* Update circular buffer index */
  FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ--;
  if (FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ < 0) {
    FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ = 8;
  }

  /* Update circular buffer */
  FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_stat
    [FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ] = rtb_KPek1_a_idx_0;

  /* End of Update for DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */

  /* Outport: '<Root>/I_dq_Ref_out [A]' incorporates:
   *  Inport: '<Root>/I_dq_Ref [A]'
   *  SignalConversion generated from: '<S1>/I_dq_Ref [A]'
   */
  FOC_fastCTRL_Y->I_dq_Ref_outA[0] = FOC_fastCTRL_U->I_dq_RefA[0];

  /* Outport: '<Root>/I_dq_Act [A]' incorporates:
   *  DiscreteFir: '<S38>/Discrete FIR Filter 20th order'
   *  DiscreteFir: '<S39>/Discrete FIR Filter 20th order'
   */
  FOC_fastCTRL_Y->I_dq_ActA[1] = rtb_Product1_f_tmp;
  FOC_fastCTRL_Y->I_dq_ActA[3] = rtb_TrafoMatrixuvwalphabeta_i;

  /* Outport: '<Root>/I_dq_Ref_out [A]' incorporates:
   *  Inport: '<Root>/I_dq_Ref [A]'
   *  SignalConversion generated from: '<S1>/I_dq_Ref [A]'
   */
  FOC_fastCTRL_Y->I_dq_Ref_outA[1] = FOC_fastCTRL_U->I_dq_RefA[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_fastCTRL' */

  /* Outport: '<Root>/w_el [rad//s]' */
  FOC_fastCTRL_Y->w_elrads = w_el;
}

/* Model initialize function */
void FOC_fastCTRL_initialize(RT_MODEL_FOC_fastCTRL_T *const FOC_fastCTRL_M)
{
  DW_FOC_fastCTRL_T *FOC_fastCTRL_DW = FOC_fastCTRL_M->dwork;
  ExtY_FOC_fastCTRL_T *FOC_fastCTRL_Y = (ExtY_FOC_fastCTRL_T *)
    FOC_fastCTRL_M->outputs;
  B_FOC_fastCTRL_T *FOC_fastCTRL_B = FOC_fastCTRL_M->blockIO;
  ExtU_FOC_fastCTRL_T *FOC_fastCTRL_U = (ExtU_FOC_fastCTRL_T *)
    FOC_fastCTRL_M->inputs;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void) memset(((void *) FOC_fastCTRL_B), 0,
                sizeof(B_FOC_fastCTRL_T));

  /* exported global signals */
  Phi_AngleEst_AutoSwitch = 0.0;
  FOC_AngleEst_w_el = 0.0;
  Phi_est = 0.0;
  Phi_Observer = 0.0;
  Phi_el_I_Transformation = 0.0;
  Phi_el_U_Transformation = 0.0;
  FOC_U_DC = 0.0;
  Phi_est_error_I_Trafo = 0.0;
  Phi_est_error = 0.0;
  FOC_AngleEst_Psi_PM_alpha = 0.0;
  FOC_AngleEst_Psi_PM_beta = 0.0;
  w_el = 0.0;
  Phi_Measured_Raw = 0.0;

  /* states (dwork) */
  (void) memset((void *)FOC_fastCTRL_DW, 0,
                sizeof(DW_FOC_fastCTRL_T));

  /* external inputs */
  (void)memset(FOC_fastCTRL_U, 0, sizeof(ExtU_FOC_fastCTRL_T));

  /* external outputs */
  (void)memset(FOC_fastCTRL_Y, 0, sizeof(ExtY_FOC_fastCTRL_T));

  /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_fastCTRL' */
  /* InitializeConditions for UnitDelay: '<S33>/Unit Delay1' */
  FOC_fastCTRL_DW->UnitDelay1_DSTATE = FOC_AngleObs_w_InitVal;

  /* InitializeConditions for UnitDelay: '<S15>/Unit Delay' */
  FOC_fastCTRL_DW->UnitDelay_DSTATE_m[0] = FOC_AngleEst_Psi_InitVal;
  FOC_fastCTRL_DW->UnitDelay_DSTATE_m[1] = FOC_AngleEst_Psi_InitVal;

  /* InitializeConditions for DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_circ = 0;

  /* InitializeConditions for DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
  FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_ci_a = 0;

  /* InitializeConditions for DiscreteFir: '<S39>/Discrete FIR Filter 20th order' */
  memset(&FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_stat[0], 0, 38U * sizeof
         (real_T));

  /* InitializeConditions for DiscreteFir: '<S38>/Discrete FIR Filter 20th order' */
  memset(&FOC_fastCTRL_DW->DiscreteFIRFilter20thorder_st_h[0], 0, 38U * sizeof
         (real_T));

  /* InitializeConditions for DiscreteFir: '<S9>/Discrete FIR Filter 10th order' */
  FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_circ = 0;
  memset(&FOC_fastCTRL_DW->DiscreteFIRFilter10thorder_stat[0], 0, 9U * sizeof
         (real_T));

  /* End of SystemInitialize for SubSystem: '<Root>/FOC_fastCTRL' */

  /* ConstCode for Outport: '<Root>/FOC_Error' incorporates:
   *  Constant: '<S1>/Constant'
   */
  FOC_fastCTRL_Y->FOC_Error = 0.0;
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
