/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_slowCTRL.c
 *
 * Code generated for Simulink model 'FOC_slowCTRL'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Aug 24 12:54:27 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_slowCTRL.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include <string.h>
#include "FOC_slowCTRL_private.h"
#include <stdbool.h>

/* Exported block signals */
real_T Udc_scf;                        /* '<S1>/Switch1' */
real_T Test_Torqu_Request;             /* '<S8>/Switch' */
real_T Torq_Ref_PGAIN;                 /* '<S9>/FOC_TORQ_REDUC_PGAIN' */
real_T Id_Ref_raw;                     /* '<S5>/Multiport Switch' */
real_T Iq_Ref_raw;                     /* '<S6>/Multiport Switch' */
real_T Torq_Ref_PSM;                   /* '<S9>/Gain' */
real_T Torq_Ref_IqDiff;                /* '<S9>/FOC_IQ_DIFF_REDUC_GAIN' */
real_T M_est;                          /* '<S4>/TorqEst_Nm' */
real_T FOC_MotTemp_PSM;                /* '<S8>/Gain1' */
boolean_T Temp_Derating_aktiv;         /* '<S25>/Compare' */

/* Exported block parameters */
real_T FOC_ENABLE_Idq_Ref = 1.0;       /* Variable: FOC_ENABLE_Idq_Ref
                                        * Referenced by: '<S2>/FOC_ENABLE_Idq_Ref'
                                        */
real_T FOC_IQ_DIFF_REDUC_GAIN = 0.002; /* Variable: FOC_IQ_DIFF_REDUC_GAIN
                                        * Referenced by: '<S9>/FOC_IQ_DIFF_REDUC_GAIN'
                                        */
real_T FOC_LIMIT_I_PHASE_PEAK_MAX = 197.989899;/* Variable: FOC_LIMIT_I_PHASE_PEAK_MAX
                                                * Referenced by: '<S15>/Constant'
                                                */
real_T FOC_LIMIT_Idq_Ref_SlewRate_Down = -1000.0;
                                    /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Down
                                     * Referenced by:
                                     *   '<S11>/Constant7'
                                     *   '<S17>/Constant7'
                                     */
real_T FOC_LIMIT_Idq_Ref_SlewRate_Up = 1000.0;
                                      /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Up
                                       * Referenced by:
                                       *   '<S11>/Constant6'
                                       *   '<S17>/Constant6'
                                       */
real_T FOC_LIMIT_Motor_Torque_MAX = 205.0;/* Variable: FOC_LIMIT_Motor_Torque_MAX
                                           * Referenced by: '<S8>/Maximum_Torque_Maschine'
                                           */
real_T FOC_LIMIT_Torque_Derating_Temp = 120.0;
                                     /* Variable: FOC_LIMIT_Torque_Derating_Temp
                                      * Referenced by: '<S26>/Constant'
                                      */
real_T FOC_LIMIT_Torque_Ref_MAX = 110.0;/* Variable: FOC_LIMIT_Torque_Ref_MAX
                                         * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
                                         */
real_T FOC_LIMIT_Torque_Ref_MIN = -110.0;/* Variable: FOC_LIMIT_Torque_Ref_MIN
                                          * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
                                          */
real_T FOC_LIMIT_Torque_Ref_SlewRate_Down = -100.0;
                                 /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Down
                                  * Referenced by: '<S7>/Constant7'
                                  */
real_T FOC_LIMIT_Torque_Ref_SlewRate_Up = 100.0;
                                   /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Up
                                    * Referenced by: '<S7>/Constant6'
                                    */
real_T FOC_LIMIT_n_Ref_SlewRate_Down = -500.0;
                                      /* Variable: FOC_LIMIT_n_Ref_SlewRate_Down
                                       * Referenced by: '<S27>/Constant7'
                                       */
real_T FOC_LIMIT_n_Ref_SlewRate_InitVal = 0.0;
                                   /* Variable: FOC_LIMIT_n_Ref_SlewRate_InitVal
                                    * Referenced by: '<S29>/Delay Input2'
                                    */
real_T FOC_LIMIT_n_Ref_SlewRate_Up = 500.0;/* Variable: FOC_LIMIT_n_Ref_SlewRate_Up
                                            * Referenced by: '<S27>/Constant6'
                                            */
real_T FOC_MANUAL_Id_Ref = 0.0;        /* Variable: FOC_MANUAL_Id_Ref
                                        * Referenced by: '<S5>/Constant5'
                                        */
real_T FOC_MANUAL_Iq_Ref = 0.0;        /* Variable: FOC_MANUAL_Iq_Ref
                                        * Referenced by: '<S6>/Constant3'
                                        */
real_T FOC_MANUAL_Torque_Request = 0.0;/* Variable: FOC_MANUAL_Torque_Request
                                        * Referenced by: '<S1>/Constant'
                                        */
real_T FOC_SELECT_ExtTrqReq = 1.0;     /* Variable: FOC_SELECT_ExtTrqReq
                                        * Referenced by: '<S1>/Constant2'
                                        */
real_T FOC_SELECT_Id_Ref = 4.0;        /* Variable: FOC_SELECT_Id_Ref
                                        * Referenced by: '<S5>/Constant3'
                                        */
real_T FOC_SELECT_Idq_Ref_Ramp = 1.0;  /* Variable: FOC_SELECT_Idq_Ref_Ramp
                                        * Referenced by:
                                        *   '<S11>/Constant5'
                                        *   '<S17>/Constant5'
                                        */
real_T FOC_SELECT_Iq_Ref = 4.0;        /* Variable: FOC_SELECT_Iq_Ref
                                        * Referenced by: '<S6>/Constant5'
                                        */
real_T FOC_SELECT_Temp_Derating = 0.0; /* Variable: FOC_SELECT_Temp_Derating
                                        * Referenced by: '<S2>/Temp_Derating_Selector'
                                        */
real_T FOC_SELECT_TorqEstMdl = 1.0;    /* Variable: FOC_SELECT_TorqEstMdl
                                        * Referenced by: '<S4>/Constant4'
                                        */
real_T FOC_SELECT_Torque_Ref_Ramp = 1.0;/* Variable: FOC_SELECT_Torque_Ref_Ramp
                                         * Referenced by: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
                                         */
real_T FOC_SELECT_n_Ref_Ramp = 1.0;    /* Variable: FOC_SELECT_n_Ref_Ramp
                                        * Referenced by: '<S27>/Constant5'
                                        */
real_T FOC_TORQ_REDUC_GAIN = 0.04;     /* Variable: FOC_TORQ_REDUC_GAIN
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_GAIN'
                                        */
real_T FOC_TORQ_REDUC_PGAIN = 0.15;    /* Variable: FOC_TORQ_REDUC_PGAIN
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_PGAIN'
                                        */
real_T FOC_TORQ_REDUC_START = 1.2;     /* Variable: FOC_TORQ_REDUC_START
                                        * Referenced by: '<S9>/FOC_TORQ_REDUC_START'
                                        */
real_T FOC_Torque_Derating_Temp_Gain = 0.1;
                                      /* Variable: FOC_Torque_Derating_Temp_Gain
                                       * Referenced by: '<S23>/Constant1'
                                       */
real_T FOC_z_P = 4.0;                  /* Variable: FOC_z_P
                                        * Referenced by:
                                        *   '<S3>/RPM => w_el'
                                        *   '<S31>/3*Z_p//2'
                                        *   '<S14>/Gain'
                                        */
real_T SCF_MANUAL_U_DC = 0.0;          /* Variable: SCF_MANUAL_U_DC
                                        * Referenced by: '<S1>/Udc2'
                                        */
real_T SCF_SELECT_U_DC_INPUT = 1.0;    /* Variable: SCF_SELECT_U_DC_INPUT
                                        * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
                                        */
real_T SPEED_CTRL_K_AWU = 1.0;         /* Variable: SPEED_CTRL_K_AWU
                                        * Referenced by: '<S3>/Gain1'
                                        */
real_T SPEED_CTRL_LIMIT_n_Ref_MAX = 7000.0;/* Variable: SPEED_CTRL_LIMIT_n_Ref_MAX
                                            * Referenced by: '<S3>/limit T2'
                                            */
real_T SPEED_CTRL_LIMIT_n_Ref_MIN = 0.0;/* Variable: SPEED_CTRL_LIMIT_n_Ref_MIN
                                         * Referenced by: '<S3>/limit T2'
                                         */
real_T SPEED_CTRL_MANUAL_n_RPM = 0.0;  /* Variable: SPEED_CTRL_MANUAL_n_RPM
                                        * Referenced by: '<S3>/OmegaRot2'
                                        */
real_T SPEED_CTRL_SELECT_TorqLimit = 1.0;/* Variable: SPEED_CTRL_SELECT_TorqLimit
                                          * Referenced by: '<S3>/OmegaRot3'
                                          */
real_T SPEED_CTRL_SELECT_n_Ref = 1.0;  /* Variable: SPEED_CTRL_SELECT_n_Ref
                                        * Referenced by: '<S3>/OmegaRot1'
                                        */
real_T SPEED_CTRL_TORQLIMNEG = -205.0; /* Variable: SPEED_CTRL_TORQLIMNEG
                                        * Referenced by: '<S3>/Constant5'
                                        */
real_T SPEED_CTRL_TORQLIMPOS = 205.0;  /* Variable: SPEED_CTRL_TORQLIMPOS
                                        * Referenced by: '<S3>/Constant4'
                                        */
real_T SPEED_CTRL_T_N = 0.5;           /* Variable: SPEED_CTRL_T_N
                                        * Referenced by: '<S3>/Constant'
                                        */
real_T SPEED_CTRL_V_R = 2.0;           /* Variable: SPEED_CTRL_V_R
                                        * Referenced by: '<S3>/Constant14'
                                        */
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/* Model step function */
void FOC_slowCTRL_step(RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_M)
{
  B_FOC_slowCTRL_T *FOC_slowCTRL_B = FOC_slowCTRL_M->blockIO;
  DW_FOC_slowCTRL_T *FOC_slowCTRL_DW = FOC_slowCTRL_M->dwork;
  ExtU_FOC_slowCTRL_T *FOC_slowCTRL_U = (ExtU_FOC_slowCTRL_T *)
    FOC_slowCTRL_M->inputs;
  ExtY_FOC_slowCTRL_T *FOC_slowCTRL_Y = (ExtY_FOC_slowCTRL_T *)
    FOC_slowCTRL_M->outputs;
  real_T rtb_PsiReduceGain1;
  real_T rtb_Sum1_j;
  real_T rtb_Switch_g;
  real_T rtb_TorqLimitSource_idx_1;
  real_T rtb_UkYk1;
  real_T rtb_UkYk1_ea;
  real_T rtb_UkYk1_g;
  real_T rtb_UkYk1_p;
  real_T rtb_deltafalllimit_m;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_slowCTRL' */
  /* Switch: '<S1>/Switch1' incorporates:
   *  Constant: '<S1>/0: P_Udc 1: Udc_measured'
   */
  if (SCF_SELECT_U_DC_INPUT > 0.0) {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Inport: '<Root>/U_DC [V]'
     */
    Udc_scf = FOC_slowCTRL_U->U_DCV;
  } else {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Udc2'
     */
    Udc_scf = SCF_MANUAL_U_DC;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Outputs for Enabled SubSystem: '<S1>/SPEED_CONTROLLER' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  /* Inport: '<Root>/SpeedCtrl_Enable' */
  if (FOC_slowCTRL_U->SpeedCtrl_Enable > 0.0) {
    if (!FOC_slowCTRL_DW->SPEED_CONTROLLER_MODE) {
      /* InitializeConditions for UnitDelay: '<S29>/Delay Input2'
       *
       * Block description for '<S29>/Delay Input2':
       *
       *  Store in Global RAM
       */
      FOC_slowCTRL_DW->DelayInput2_DSTATE_d = FOC_LIMIT_n_Ref_SlewRate_InitVal;

      /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
      FOC_slowCTRL_DW->UnitDelay_DSTATE_a = 0.0;
      FOC_slowCTRL_DW->SPEED_CONTROLLER_MODE = true;
    }

    /* MultiPortSwitch: '<S3>/TorqLimitSource' incorporates:
     *  Constant: '<S3>/Constant4'
     *  Constant: '<S3>/Constant5'
     *  Constant: '<S3>/OmegaRot3'
     *  Constant: '<S3>/ZeroTorq1'
     *  Constant: '<S3>/ZeroTorq2'
     *  Inport: '<Root>/ExtTorqLim [Nm]'
     */
    switch ((int32_T)SPEED_CTRL_SELECT_TorqLimit) {
     case 0:
      rtb_UkYk1 = SPEED_CTRL_TORQLIMPOS;
      rtb_TorqLimitSource_idx_1 = SPEED_CTRL_TORQLIMNEG;
      break;

     case 1:
      rtb_UkYk1 = FOC_slowCTRL_U->ExtTorqLimNm[0];
      rtb_TorqLimitSource_idx_1 = FOC_slowCTRL_U->ExtTorqLimNm[1];
      break;

     default:
      rtb_UkYk1 = 0.0;
      rtb_TorqLimitSource_idx_1 = 0.0;
      break;
    }

    /* End of MultiPortSwitch: '<S3>/TorqLimitSource' */

    /* Saturate: '<S3>/limit T1' */
    if (rtb_UkYk1 > 205.0) {
      rtb_UkYk1 = 205.0;
    } else if (rtb_UkYk1 < 0.0) {
      rtb_UkYk1 = 0.0;
    }

    /* End of Saturate: '<S3>/limit T1' */

    /* MultiPortSwitch: '<S3>/n_Ref_Source' incorporates:
     *  Constant: '<S3>/OmegaRot1'
     *  Constant: '<S3>/OmegaRot2'
     *  Inport: '<Root>/ExtSpeedReq [rpm]'
     */
    if ((int32_T)SPEED_CTRL_SELECT_n_Ref == 0) {
      rtb_PsiReduceGain1 = SPEED_CTRL_MANUAL_n_RPM;
    } else {
      rtb_PsiReduceGain1 = FOC_slowCTRL_U->ExtSpeedReqrpm;
    }

    /* End of MultiPortSwitch: '<S3>/n_Ref_Source' */

    /* Saturate: '<S3>/limit T2' */
    if (rtb_PsiReduceGain1 > SPEED_CTRL_LIMIT_n_Ref_MAX) {
      rtb_PsiReduceGain1 = SPEED_CTRL_LIMIT_n_Ref_MAX;
    } else if (rtb_PsiReduceGain1 < SPEED_CTRL_LIMIT_n_Ref_MIN) {
      rtb_PsiReduceGain1 = SPEED_CTRL_LIMIT_n_Ref_MIN;
    }

    /* End of Saturate: '<S3>/limit T2' */

    /* Product: '<S29>/delta rise limit' incorporates:
     *  Constant: '<S27>/Constant6'
     *  Constant: '<S29>/FOC_T_slow'
     */
    rtb_deltafalllimit_m = FOC_LIMIT_n_Ref_SlewRate_Up * 0.001;

    /* Sum: '<S29>/Difference Inputs1' incorporates:
     *  UnitDelay: '<S29>/Delay Input2'
     *
     * Block description for '<S29>/Difference Inputs1':
     *
     *  Add in CPU
     *
     * Block description for '<S29>/Delay Input2':
     *
     *  Store in Global RAM
     */
    rtb_UkYk1_ea = rtb_PsiReduceGain1 - FOC_slowCTRL_DW->DelayInput2_DSTATE_d;

    /* Switch: '<S30>/Switch2' incorporates:
     *  RelationalOperator: '<S30>/LowerRelop1'
     */
    if (!(rtb_UkYk1_ea > rtb_deltafalllimit_m)) {
      /* Product: '<S29>/delta fall limit' incorporates:
       *  Constant: '<S27>/Constant7'
       *  Constant: '<S29>/FOC_T_slow'
       */
      rtb_deltafalllimit_m = FOC_LIMIT_n_Ref_SlewRate_Down * 0.001;

      /* Switch: '<S30>/Switch' incorporates:
       *  RelationalOperator: '<S30>/UpperRelop'
       */
      if (!(rtb_UkYk1_ea < rtb_deltafalllimit_m)) {
        rtb_deltafalllimit_m = rtb_UkYk1_ea;
      }

      /* End of Switch: '<S30>/Switch' */
    }

    /* End of Switch: '<S30>/Switch2' */

    /* Sum: '<S29>/Difference Inputs2' incorporates:
     *  UnitDelay: '<S29>/Delay Input2'
     *
     * Block description for '<S29>/Difference Inputs2':
     *
     *  Add in CPU
     *
     * Block description for '<S29>/Delay Input2':
     *
     *  Store in Global RAM
     */
    FOC_slowCTRL_DW->DelayInput2_DSTATE_d += rtb_deltafalllimit_m;

    /* Switch: '<S27>/Switch2' incorporates:
     *  Constant: '<S27>/Constant5'
     *  UnitDelay: '<S29>/Delay Input2'
     *
     * Block description for '<S29>/Delay Input2':
     *
     *  Store in Global RAM
     */
    if (FOC_SELECT_n_Ref_Ramp > 0.0) {
      rtb_PsiReduceGain1 = FOC_slowCTRL_DW->DelayInput2_DSTATE_d;
    }

    /* End of Switch: '<S27>/Switch2' */

    /* Product: '<S3>/Product6' incorporates:
     *  Constant: '<S3>/Constant14'
     *  Gain: '<S3>/RPM => w_el'
     *  Inport: '<Root>/w_el [rad//s]'
     *  Sum: '<S3>/Add'
     */
    rtb_PsiReduceGain1 = (6.2831853071795862 * FOC_z_P / 60.0 *
                          rtb_PsiReduceGain1 - FOC_slowCTRL_U->w_elrads) *
      SPEED_CTRL_V_R;

    /* Sum: '<S3>/Add2' incorporates:
     *  UnitDelay: '<S3>/Unit Delay'
     */
    rtb_UkYk1_ea = rtb_PsiReduceGain1 + FOC_slowCTRL_DW->UnitDelay_DSTATE_a;

    /* Switch: '<S28>/Switch2' incorporates:
     *  RelationalOperator: '<S28>/LowerRelop1'
     */
    if (!(rtb_UkYk1_ea > rtb_UkYk1)) {
      /* Saturate: '<S3>/limit T3' */
      if (rtb_TorqLimitSource_idx_1 > 0.0) {
        rtb_TorqLimitSource_idx_1 = 0.0;
      } else if (rtb_TorqLimitSource_idx_1 < -205.0) {
        rtb_TorqLimitSource_idx_1 = -205.0;
      }

      /* End of Saturate: '<S3>/limit T3' */

      /* Switch: '<S28>/Switch' incorporates:
       *  RelationalOperator: '<S28>/UpperRelop'
       */
      if (rtb_UkYk1_ea < rtb_TorqLimitSource_idx_1) {
        rtb_UkYk1 = rtb_TorqLimitSource_idx_1;
      } else {
        rtb_UkYk1 = rtb_UkYk1_ea;
      }

      /* End of Switch: '<S28>/Switch' */
    }

    /* End of Switch: '<S28>/Switch2' */

    /* Product: '<S3>/Product' incorporates:
     *  Constant: '<S3>/Constant'
     *  Constant: '<S3>/Constant3'
     *  Constant: '<S3>/FOC_T_slow'
     *  Gain: '<S3>/Gain1'
     *  MinMax: '<S3>/avoid_div_by_0'
     *  Product: '<S3>/Divide'
     *  Product: '<S3>/Product5'
     *  Sum: '<S3>/Add1'
     *  Sum: '<S3>/Subtract'
     *  Sum: '<S3>/Sum'
     *  UnitDelay: '<S3>/Unit Delay'
     */
    FOC_slowCTRL_DW->UnitDelay_DSTATE_a = (((rtb_UkYk1 - rtb_UkYk1_ea) *
      SPEED_CTRL_K_AWU + rtb_PsiReduceGain1) * 0.001 / fmax(0.0001,
      SPEED_CTRL_T_N) + FOC_slowCTRL_DW->UnitDelay_DSTATE_a) *
      FOC_slowCTRL_U->SpeedCtrl_Enable;

    /* Switch: '<S3>/Switch1' */
    if (FOC_slowCTRL_U->SpeedCtrl_Enable > 0.0) {
      /* Switch: '<S3>/Switch1' */
      FOC_slowCTRL_B->Switch1 = rtb_UkYk1;
    } else {
      /* Switch: '<S3>/Switch1' incorporates:
       *  Constant: '<S3>/ZeroTorq'
       */
      FOC_slowCTRL_B->Switch1 = 0.0;
    }

    /* End of Switch: '<S3>/Switch1' */
  } else {
    FOC_slowCTRL_DW->SPEED_CONTROLLER_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/SPEED_CONTROLLER' */

  /* MultiPortSwitch: '<S1>/TorqRef_Source' incorporates:
   *  Inport: '<Root>/SpeedCtrl_Enable'
   */
  if ((int32_T)FOC_slowCTRL_U->SpeedCtrl_Enable == 0) {
    /* Switch: '<S1>/Switch2' incorporates:
     *  Constant: '<S1>/Constant'
     *  Constant: '<S1>/Constant2'
     *  Inport: '<Root>/ExtTorqReq [Nm]'
     */
    if (FOC_SELECT_ExtTrqReq > 0.0) {
      rtb_TorqLimitSource_idx_1 = FOC_slowCTRL_U->ExtTorqReqNm;
    } else {
      rtb_TorqLimitSource_idx_1 = FOC_MANUAL_Torque_Request;
    }

    /* End of Switch: '<S1>/Switch2' */

    /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
    if (rtb_TorqLimitSource_idx_1 > FOC_LIMIT_Torque_Ref_MAX) {
      rtb_TorqLimitSource_idx_1 = FOC_LIMIT_Torque_Ref_MAX;
    } else if (rtb_TorqLimitSource_idx_1 < FOC_LIMIT_Torque_Ref_MIN) {
      rtb_TorqLimitSource_idx_1 = FOC_LIMIT_Torque_Ref_MIN;
    }

    /* End of Saturate: '<S1>/TORQUE_REQ_LIMIT' */
  } else {
    rtb_TorqLimitSource_idx_1 = FOC_slowCTRL_B->Switch1;
  }

  /* End of MultiPortSwitch: '<S1>/TorqRef_Source' */

  /* Product: '<S20>/delta rise limit' incorporates:
   *  Constant: '<S20>/Constant6'
   *  Constant: '<S7>/Constant6'
   */
  rtb_UkYk1_ea = FOC_LIMIT_Torque_Ref_SlewRate_Up * 0.001;

  /* Sum: '<S20>/Difference Inputs1' incorporates:
   *  UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Difference Inputs1':
   *
   *  Add in CPU
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  rtb_UkYk1 = rtb_TorqLimitSource_idx_1 - FOC_slowCTRL_DW->DelayInput2_DSTATE;

  /* Switch: '<S21>/Switch2' incorporates:
   *  RelationalOperator: '<S21>/LowerRelop1'
   */
  if (!(rtb_UkYk1 > rtb_UkYk1_ea)) {
    /* Product: '<S20>/delta fall limit' incorporates:
     *  Constant: '<S20>/Constant6'
     *  Constant: '<S7>/Constant7'
     */
    rtb_UkYk1_ea = FOC_LIMIT_Torque_Ref_SlewRate_Down * 0.001;

    /* Switch: '<S21>/Switch' incorporates:
     *  RelationalOperator: '<S21>/UpperRelop'
     */
    if (!(rtb_UkYk1 < rtb_UkYk1_ea)) {
      rtb_UkYk1_ea = rtb_UkYk1;
    }

    /* End of Switch: '<S21>/Switch' */
  }

  /* End of Switch: '<S21>/Switch2' */

  /* Sum: '<S20>/Difference Inputs2' incorporates:
   *  UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE += rtb_UkYk1_ea;

  /* Switch: '<S7>/Switch4' incorporates:
   *  Constant: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
   *  UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  if (FOC_SELECT_Torque_Ref_Ramp > 0.0) {
    rtb_UkYk1 = FOC_slowCTRL_DW->DelayInput2_DSTATE;
  } else {
    rtb_UkYk1 = rtb_TorqLimitSource_idx_1;
  }

  /* End of Switch: '<S7>/Switch4' */

  /* Saturate: '<S23>/Saturation' incorporates:
   *  UnitDelay: '<S23>/Unit Delay'
   */
  if (FOC_slowCTRL_DW->UnitDelay_DSTATE > 1.0) {
    rtb_UkYk1_ea = 1.0;
  } else if (FOC_slowCTRL_DW->UnitDelay_DSTATE < 0.0) {
    rtb_UkYk1_ea = 0.0;
  } else {
    rtb_UkYk1_ea = FOC_slowCTRL_DW->UnitDelay_DSTATE;
  }

  /* End of Saturate: '<S23>/Saturation' */

  /* Product: '<S8>/Product1' incorporates:
   *  Constant: '<S23>/Constant2'
   *  Constant: '<S8>/Maximum_Torque_Maschine'
   *  Sum: '<S23>/Sum2'
   */
  rtb_Switch_g = (1.0 - rtb_UkYk1_ea) * FOC_LIMIT_Motor_Torque_MAX;

  /* Abs: '<S8>/Abs' */
  rtb_TorqLimitSource_idx_1 = fabs(rtb_UkYk1);

  /* RelationalOperator: '<S25>/Compare' incorporates:
   *  Abs: '<S22>/Abs'
   *  Abs: '<S22>/Abs1'
   *  Constant: '<S25>/Constant'
   *  Sum: '<S22>/Subtract'
   */
  Temp_Derating_aktiv = (fabs(rtb_Switch_g) - rtb_TorqLimitSource_idx_1 < 0.0);

  /* Switch: '<S8>/Switch' */
  if (Temp_Derating_aktiv) {
    /* Switch: '<S22>/Switch1' incorporates:
     *  Constant: '<S24>/Constant'
     *  RelationalOperator: '<S24>/Compare'
     */
    if (rtb_UkYk1 <= 0.0) {
      /* Switch: '<S8>/Switch' incorporates:
       *  Gain: '<S22>/Gain'
       *  MinMax: '<S22>/MinMax'
       */
      Test_Torqu_Request = -fmin(rtb_Switch_g, rtb_TorqLimitSource_idx_1);
    } else {
      /* Switch: '<S8>/Switch' incorporates:
       *  MinMax: '<S22>/MinMax'
       */
      Test_Torqu_Request = fmin(rtb_Switch_g, rtb_TorqLimitSource_idx_1);
    }

    /* End of Switch: '<S22>/Switch1' */
  } else {
    /* Switch: '<S8>/Switch' */
    Test_Torqu_Request = rtb_UkYk1;
  }

  /* End of Switch: '<S8>/Switch' */

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Temp_Derating_Selector'
   */
  if (FOC_SELECT_Temp_Derating > 0.0) {
    rtb_Switch_g = Test_Torqu_Request;
  } else {
    rtb_Switch_g = rtb_UkYk1;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Sum: '<S9>/Sum1' incorporates:
   *  Constant: '<S9>/FOC_TORQ_REDUC_START'
   *  Inport: '<Root>/ModInd'
   *  MinMax: '<S2>/MinMax'
   */
  rtb_Sum1_j = FOC_TORQ_REDUC_START - fmax(FOC_slowCTRL_U->ModInd[0],
    FOC_slowCTRL_U->ModInd[1]);

  /* Gain: '<S9>/FOC_TORQ_REDUC_PGAIN' */
  Torq_Ref_PGAIN = FOC_TORQ_REDUC_PGAIN * rtb_Sum1_j;

  /* Sum: '<S9>/TorqCtrlSum3' incorporates:
   *  UnitDelay: '<S9>/TorqCtrlDelay'
   */
  rtb_TorqLimitSource_idx_1 = FOC_slowCTRL_DW->TorqCtrlDelay_DSTATE +
    Torq_Ref_PGAIN;

  /* Saturate: '<S9>/Saturation' */
  if (rtb_TorqLimitSource_idx_1 > 1.0) {
    rtb_TorqLimitSource_idx_1 = 1.0;
  } else if (rtb_TorqLimitSource_idx_1 < 0.0) {
    rtb_TorqLimitSource_idx_1 = 0.0;
  }

  /* End of Saturate: '<S9>/Saturation' */

  /* Product: '<S9>/TorqCtrlProduct' */
  Torq_Ref_PSM = rtb_Switch_g * rtb_TorqLimitSource_idx_1;

  /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
   *  Constant: '<S5>/Constant3'
   */
  switch ((int32_T)FOC_SELECT_Id_Ref) {
   case 1:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/Constant5'
     */
    Id_Ref_raw = FOC_MANUAL_Id_Ref;
    break;

   case 2:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    Id_Ref_raw = 0.0;
    break;

   case 3:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    Id_Ref_raw = 0.0;
    break;

   case 4:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Abs: '<S10>/Abs2'
     *  Gain: '<S5>/Gain'
     *  Lookup_n-D: '<S10>/Id_Ref_M_MTPC'
     */
    Id_Ref_raw = look1_binlxpw(fabs(0.5 * Torq_Ref_PSM),
      FOC_slowCTRL_ConstP.pooled2, FOC_slowCTRL_ConstP.Id_Ref_M_MTPC_tableData,
      19U);
    break;

   case 5:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    Id_Ref_raw = 0.0;
    break;

   default:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    Id_Ref_raw = 0.0;
    break;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch' */

  /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
   *  Bias: '<S5>/Bias'
   *  Constant: '<S2>/FOC_ENABLE_Idq_Ref'
   *  Constant: '<S5>/zero_Current'
   */
  if ((int32_T)(FOC_ENABLE_Idq_Ref + 1.0) == 1) {
    rtb_deltafalllimit_m = 0.0;
  } else {
    rtb_deltafalllimit_m = Id_Ref_raw;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch1' */

  /* Product: '<S12>/delta rise limit' incorporates:
   *  Constant: '<S11>/Constant6'
   *  Constant: '<S12>/Constant6'
   *  Product: '<S18>/delta rise limit'
   */
  rtb_PsiReduceGain1 = FOC_LIMIT_Idq_Ref_SlewRate_Up * 0.001;
  rtb_UkYk1 = rtb_PsiReduceGain1;

  /* Sum: '<S12>/Difference Inputs1' incorporates:
   *  UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Difference Inputs1':
   *
   *  Add in CPU
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  rtb_UkYk1_g = rtb_deltafalllimit_m - FOC_slowCTRL_DW->DelayInput2_DSTATE_f;

  /* Switch: '<S13>/Switch2' incorporates:
   *  Product: '<S12>/delta rise limit'
   *  RelationalOperator: '<S13>/LowerRelop1'
   */
  if (!(rtb_UkYk1_g > rtb_PsiReduceGain1)) {
    /* Product: '<S12>/delta fall limit' incorporates:
     *  Constant: '<S11>/Constant7'
     *  Constant: '<S12>/Constant6'
     */
    rtb_UkYk1 = FOC_LIMIT_Idq_Ref_SlewRate_Down * 0.001;

    /* Switch: '<S13>/Switch' incorporates:
     *  RelationalOperator: '<S13>/UpperRelop'
     */
    if (!(rtb_UkYk1_g < rtb_UkYk1)) {
      rtb_UkYk1 = rtb_UkYk1_g;
    }

    /* End of Switch: '<S13>/Switch' */
  }

  /* End of Switch: '<S13>/Switch2' */

  /* Sum: '<S12>/Difference Inputs2' incorporates:
   *  UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE_f += rtb_UkYk1;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Constant: '<S11>/Constant5'
   *  UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  if (FOC_SELECT_Idq_Ref_Ramp > 0.0) {
    rtb_UkYk1_g = FOC_slowCTRL_DW->DelayInput2_DSTATE_f;
  } else {
    rtb_UkYk1_g = rtb_deltafalllimit_m;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
   *  Constant: '<S6>/Constant5'
   */
  switch ((int32_T)FOC_SELECT_Iq_Ref) {
   case 1:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/Constant3'
     */
    Iq_Ref_raw = FOC_MANUAL_Iq_Ref;
    break;

   case 2:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S14>/Constant'
     *  Constant: '<S14>/Constant4'
     *  Gain: '<S14>/Gain'
     *  Product: '<S14>/Divide'
     *  Product: '<S14>/IqRefRaw_PSM'
     *  Product: '<S14>/Product'
     *  Sum: '<S14>/Add1'
     */
    Iq_Ref_raw = 1.0 / (FOC_slowCTRL_ConstB.Add * rtb_UkYk1_g + 0.07) * (1.0 /
      (1.5 * FOC_z_P) * Torq_Ref_PSM);
    break;

   case 3:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    Iq_Ref_raw = 0.0;
    break;

   case 4:
    /* Gain: '<S6>/Gain' */
    rtb_UkYk1 = 0.5 * Torq_Ref_PSM;

    /* Signum: '<S16>/Sign' */
    if (rtIsNaN(rtb_UkYk1)) {
      rtb_deltafalllimit_m = rtb_UkYk1;
    } else if (rtb_UkYk1 < 0.0) {
      rtb_deltafalllimit_m = -1.0;
    } else {
      rtb_deltafalllimit_m = (rtb_UkYk1 > 0.0);
    }

    /* End of Signum: '<S16>/Sign' */

    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Abs: '<S16>/Abs2'
     *  Lookup_n-D: '<S16>/Iq_Ref_M_MTPC'
     *  Product: '<S16>/Product1'
     */
    Iq_Ref_raw = look1_binlxpw(fabs(rtb_UkYk1), FOC_slowCTRL_ConstP.pooled2,
      FOC_slowCTRL_ConstP.Iq_Ref_M_MTPC_tableData, 19U) * rtb_deltafalllimit_m;
    break;

   case 5:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    Iq_Ref_raw = 0.0;
    break;

   default:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    Iq_Ref_raw = 0.0;
    break;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch' */

  /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
   *  Bias: '<S6>/Bias'
   *  Constant: '<S2>/FOC_ENABLE_Idq_Ref'
   *  Constant: '<S6>/zero_Current'
   */
  if ((int32_T)(FOC_ENABLE_Idq_Ref + 1.0) == 1) {
    rtb_UkYk1 = 0.0;
  } else {
    rtb_UkYk1 = Iq_Ref_raw;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch1' */

  /* Product: '<S18>/delta rise limit' */
  rtb_deltafalllimit_m = rtb_PsiReduceGain1;

  /* Sum: '<S18>/Difference Inputs1' incorporates:
   *  UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Difference Inputs1':
   *
   *  Add in CPU
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  rtb_UkYk1_p = rtb_UkYk1 - FOC_slowCTRL_DW->DelayInput2_DSTATE_e;

  /* Switch: '<S19>/Switch2' incorporates:
   *  RelationalOperator: '<S19>/LowerRelop1'
   */
  if (!(rtb_UkYk1_p > rtb_PsiReduceGain1)) {
    /* Product: '<S18>/delta fall limit' incorporates:
     *  Constant: '<S17>/Constant7'
     *  Constant: '<S18>/Constant6'
     */
    rtb_deltafalllimit_m = FOC_LIMIT_Idq_Ref_SlewRate_Down * 0.001;

    /* Switch: '<S19>/Switch' incorporates:
     *  RelationalOperator: '<S19>/UpperRelop'
     */
    if (!(rtb_UkYk1_p < rtb_deltafalllimit_m)) {
      rtb_deltafalllimit_m = rtb_UkYk1_p;
    }

    /* End of Switch: '<S19>/Switch' */
  }

  /* End of Switch: '<S19>/Switch2' */

  /* Sum: '<S18>/Difference Inputs2' incorporates:
   *  UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE_e += rtb_deltafalllimit_m;

  /* Switch: '<S17>/Switch2' incorporates:
   *  Constant: '<S17>/Constant5'
   *  UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  if (FOC_SELECT_Idq_Ref_Ramp > 0.0) {
    rtb_UkYk1 = FOC_slowCTRL_DW->DelayInput2_DSTATE_e;
  }

  /* End of Switch: '<S17>/Switch2' */

  /* Sqrt: '<S15>/Sqrt' incorporates:
   *  Constant: '<S15>/Constant'
   *  Product: '<S15>/Product'
   *  Product: '<S15>/Product1'
   *  Sum: '<S15>/Subtract1'
   */
  rtb_PsiReduceGain1 = sqrt(FOC_LIMIT_I_PHASE_PEAK_MAX *
    FOC_LIMIT_I_PHASE_PEAK_MAX - rtb_UkYk1_g * rtb_UkYk1_g);

  /* MinMax: '<S15>/MinMax1' incorporates:
   *  Gain: '<S15>/PsiReduceGain1'
   *  MinMax: '<S15>/mcrPsiRef1'
   */
  rtb_deltafalllimit_m = fmax(fmin(rtb_UkYk1, rtb_PsiReduceGain1),
    -rtb_PsiReduceGain1);

  /* Gain: '<S9>/FOC_IQ_DIFF_REDUC_GAIN' incorporates:
   *  UnitDelay: '<S9>/UnitDelay'
   */
  Torq_Ref_IqDiff = FOC_IQ_DIFF_REDUC_GAIN * FOC_slowCTRL_DW->UnitDelay_DSTATE_m;

  /* Switch: '<S9>/TorqCtrlSwitch1' incorporates:
   *  Gain: '<S9>/TorqCtrlMinusOne'
   */
  if (rtb_Switch_g >= 0.0) {
    rtb_Switch_g = -Torq_Ref_IqDiff;
  } else {
    rtb_Switch_g = Torq_Ref_IqDiff;
  }

  /* End of Switch: '<S9>/TorqCtrlSwitch1' */

  /* Switch: '<S9>/TorqCtrlSwitch3' incorporates:
   *  Gain: '<S9>/FOC_TORQ_REDUC_GAIN'
   *  MinMax: '<S9>/TorqCtrlMin2'
   */
  if (rtb_Switch_g >= 0.0) {
    rtb_Switch_g = FOC_TORQ_REDUC_GAIN * rtb_Sum1_j;
  } else {
    rtb_Switch_g = fmin(rtb_Switch_g, FOC_TORQ_REDUC_GAIN * rtb_Sum1_j);
  }

  /* End of Switch: '<S9>/TorqCtrlSwitch3' */

  /* Sum: '<S9>/TorqCtrlSum1' incorporates:
   *  Sum: '<S9>/TorqCtrlSum4'
   *  UnitDelay: '<S9>/TorqCtrlDelay'
   */
  FOC_slowCTRL_DW->TorqCtrlDelay_DSTATE = (rtb_TorqLimitSource_idx_1 -
    Torq_Ref_PGAIN) + rtb_Switch_g;

  /* Sum: '<S23>/Sum1' incorporates:
   *  Constant: '<S23>/Constant'
   *  Constant: '<S23>/Constant1'
   *  Constant: '<S26>/Constant'
   *  Inport: '<Root>/MotTemp [degC]'
   *  Product: '<S23>/Product'
   *  RelationalOperator: '<S26>/Compare'
   *  Sum: '<S23>/Sum'
   *  UnitDelay: '<S23>/Unit Delay'
   */
  FOC_slowCTRL_DW->UnitDelay_DSTATE = (0.5 - (real_T)
    (FOC_slowCTRL_U->MotTempdegC <= FOC_LIMIT_Torque_Derating_Temp)) *
    FOC_Torque_Derating_Temp_Gain + rtb_UkYk1_ea;

  /* MultiPortSwitch: '<S4>/Selectphicalc1' incorporates:
   *  Constant: '<S4>/Constant4'
   */
  switch ((int32_T)FOC_SELECT_TorqEstMdl) {
   case 0:
    /* MultiPortSwitch: '<S4>/Selectphicalc1' incorporates:
     *  Constant: '<S4>/Constant'
     */
    M_est = 0.0;
    break;

   case 1:
    /* MultiPortSwitch: '<S4>/Selectphicalc1' incorporates:
     *  Constant: '<S31>/FOC_Psi_PM'
     *  Gain: '<S31>/3*Z_p//2'
     *  Gain: '<S4>/3ph_to_6ph_factor'
     *  Inport: '<Root>/I_dq_Act [A]'
     *  Product: '<S31>/Product1'
     *  Product: '<S31>/Product2'
     *  Product: '<S31>/product'
     *  Product: '<S31>/product_2'
     *  Sum: '<S31>/Add'
     *  Sum: '<S31>/add1'
     *  Sum: '<S31>/add2'
     */
    M_est = ((-0.00047000000000000004 * FOC_slowCTRL_U->I_dq_ActA[0] *
              FOC_slowCTRL_U->I_dq_ActA[1] + FOC_slowCTRL_U->I_dq_ActA[1] * 0.07)
             + (-0.00047000000000000004 * FOC_slowCTRL_U->I_dq_ActA[2] *
                FOC_slowCTRL_U->I_dq_ActA[3] + FOC_slowCTRL_U->I_dq_ActA[3] *
                -0.00047000000000000004)) * (3.0 * FOC_z_P / 2.0) * 2.0;
    break;

   case 2:
    /* MultiPortSwitch: '<S4>/Selectphicalc1' */
    M_est = 0.0;
    break;

   default:
    /* MultiPortSwitch: '<S4>/Selectphicalc1' */
    M_est = 0.0;
    break;
  }

  /* End of MultiPortSwitch: '<S4>/Selectphicalc1' */

  /* Gain: '<S8>/Gain1' incorporates:
   *  Inport: '<Root>/MotTemp [degC]'
   */
  FOC_MotTemp_PSM = FOC_slowCTRL_U->MotTempdegC;

  /* Update for UnitDelay: '<S9>/UnitDelay' incorporates:
   *  UnitDelay: '<S15>/Unit Delay'
   */
  FOC_slowCTRL_DW->UnitDelay_DSTATE_m = FOC_slowCTRL_DW->UnitDelay_DSTATE_b;

  /* Update for UnitDelay: '<S15>/Unit Delay' incorporates:
   *  Sum: '<S15>/Subtract'
   */
  FOC_slowCTRL_DW->UnitDelay_DSTATE_b = rtb_UkYk1 - rtb_deltafalllimit_m;

  /* End of Outputs for SubSystem: '<Root>/FOC_slowCTRL' */

  /* Outport: '<Root>/I_dq_Ref [A]' */
  FOC_slowCTRL_Y->I_dq_RefA[0] = rtb_UkYk1_g;
  FOC_slowCTRL_Y->I_dq_RefA[1] = rtb_deltafalllimit_m;

  /* Outport: '<Root>/TorqueEst [Nm]' */
  FOC_slowCTRL_Y->TorqueEstNm = M_est;

  /* Outport: '<Root>/TorqueRefDerated [Nm]' */
  FOC_slowCTRL_Y->TorqueRefDeratedNm = Torq_Ref_PSM;
}

/* Model initialize function */
void FOC_slowCTRL_initialize(RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_M)
{
  DW_FOC_slowCTRL_T *FOC_slowCTRL_DW = FOC_slowCTRL_M->dwork;
  B_FOC_slowCTRL_T *FOC_slowCTRL_B = FOC_slowCTRL_M->blockIO;
  ExtU_FOC_slowCTRL_T *FOC_slowCTRL_U = (ExtU_FOC_slowCTRL_T *)
    FOC_slowCTRL_M->inputs;
  ExtY_FOC_slowCTRL_T *FOC_slowCTRL_Y = (ExtY_FOC_slowCTRL_T *)
    FOC_slowCTRL_M->outputs;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void) memset(((void *) FOC_slowCTRL_B), 0,
                sizeof(B_FOC_slowCTRL_T));

  /* exported global signals */
  Udc_scf = 0.0;
  Test_Torqu_Request = 0.0;
  Torq_Ref_PGAIN = 0.0;
  Id_Ref_raw = 0.0;
  Iq_Ref_raw = 0.0;
  Torq_Ref_PSM = 0.0;
  Torq_Ref_IqDiff = 0.0;
  M_est = 0.0;
  FOC_MotTemp_PSM = 0.0;
  Temp_Derating_aktiv = false;

  /* states (dwork) */
  (void) memset((void *)FOC_slowCTRL_DW, 0,
                sizeof(DW_FOC_slowCTRL_T));

  /* external inputs */
  (void)memset(FOC_slowCTRL_U, 0, sizeof(ExtU_FOC_slowCTRL_T));

  /* external outputs */
  (void)memset(FOC_slowCTRL_Y, 0, sizeof(ExtY_FOC_slowCTRL_T));

  /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_slowCTRL' */
  /* InitializeConditions for UnitDelay: '<S9>/TorqCtrlDelay' */
  FOC_slowCTRL_DW->TorqCtrlDelay_DSTATE = 1.0;

  /* SystemInitialize for Enabled SubSystem: '<S1>/SPEED_CONTROLLER' */
  /* InitializeConditions for UnitDelay: '<S29>/Delay Input2'
   *
   * Block description for '<S29>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE_d = FOC_LIMIT_n_Ref_SlewRate_InitVal;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
  FOC_slowCTRL_DW->UnitDelay_DSTATE_a = 0.0;

  /* End of SystemInitialize for SubSystem: '<S1>/SPEED_CONTROLLER' */
  /* End of SystemInitialize for SubSystem: '<Root>/FOC_slowCTRL' */
}

/* Model terminate function */
void FOC_slowCTRL_terminate(RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(FOC_slowCTRL_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
