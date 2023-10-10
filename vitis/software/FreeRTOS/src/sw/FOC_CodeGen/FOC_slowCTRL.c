/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_slowCTRL.c
 *
 * Code generated for Simulink model 'FOC_slowCTRL'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Oct  9 23:28:30 2023
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

/* Exported block signals */
real_T Test_Torqu_Request;             /* '<S8>/Switch' */
real_T Id_Ref_raw;                     /* '<S5>/Multiport Switch' */
real_T Iq_Ref_raw;                     /* '<S6>/Multiport Switch' */
real_T FOC_MotTemp_PSM;                /* '<S8>/Gain1' */
real_T Torq_Ref_PSM;                   /* '<S9>/Gain' */
real_T Torq_Ref_IqDiff;                /* '<S9>/Gain1' */
real_T Torq_Ref_PGAIN;                 /* '<S9>/Gain2' */
real_T Udc_scf;                        /* '<S1>/Switch1' */
real_T M_est;                          /* '<S4>/TorqEst_Nm' */
real_T SCF_Cnt;                        /* '<S1>/SCF_Cnt' */
boolean_T Temp_Derating_aktiv;         /* '<S25>/Compare' */
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
  real_T u0;
  real_T u1;
  real_T u2;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_slowCTRL' */
  /* Bias: '<S5>/Bias' incorporates:
   *  Constant: '<S2>/FOC_ENABLE_Idq_Ref'
   */
  FOC_slowCTRL_B->Bias = FOC_slowCTRL_P.FOC_ENABLE_Idq_Ref +
    FOC_slowCTRL_P.Bias_Bias;

  /* UnitDelay: '<S23>/Unit Delay' */
  FOC_slowCTRL_B->UnitDelay = FOC_slowCTRL_DW->UnitDelay_DSTATE;

  /* Saturate: '<S23>/Saturation' */
  u0 = FOC_slowCTRL_B->UnitDelay;
  u1 = FOC_slowCTRL_P.Saturation_LowerSat;
  u2 = FOC_slowCTRL_P.Saturation_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<S23>/Saturation' */
    FOC_slowCTRL_B->Saturation = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S23>/Saturation' */
    FOC_slowCTRL_B->Saturation = u1;
  } else {
    /* Saturate: '<S23>/Saturation' */
    FOC_slowCTRL_B->Saturation = u0;
  }

  /* End of Saturate: '<S23>/Saturation' */

  /* Sum: '<S23>/Sum2' incorporates:
   *  Constant: '<S23>/Constant2'
   */
  FOC_slowCTRL_B->Sum2 = FOC_slowCTRL_P.Constant2_Value -
    FOC_slowCTRL_B->Saturation;

  /* Product: '<S8>/Product1' incorporates:
   *  Constant: '<S8>/Maximum_Torque_Maschine'
   */
  FOC_slowCTRL_B->Product1 = FOC_slowCTRL_P.FOC_LIMIT_Motor_Torque_MAX *
    FOC_slowCTRL_B->Sum2;

  /* Product: '<S20>/delta rise limit' incorporates:
   *  Constant: '<S20>/Constant6'
   *  Constant: '<S7>/Constant6'
   */
  FOC_slowCTRL_B->deltariselimit =
    FOC_slowCTRL_P.FOC_LIMIT_Torque_Ref_SlewRate_Up * FOC_slowCTRL_P.FOC_T_slow;

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
      FOC_slowCTRL_DW->DelayInput2_DSTATE_d =
        FOC_slowCTRL_P.FOC_LIMIT_n_Ref_SlewRate_InitVal;

      /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
      FOC_slowCTRL_DW->UnitDelay_DSTATE_a =
        FOC_slowCTRL_P.UnitDelay_InitialCondition;
      FOC_slowCTRL_DW->SPEED_CONTROLLER_MODE = true;
    }

    /* Product: '<S29>/delta rise limit' incorporates:
     *  Constant: '<S27>/Constant6'
     *  Constant: '<S29>/FOC_T_slow'
     */
    FOC_slowCTRL_B->deltariselimit_c =
      FOC_slowCTRL_P.FOC_LIMIT_n_Ref_SlewRate_Up * FOC_slowCTRL_P.FOC_T_slow;

    /* MultiPortSwitch: '<S3>/n_Ref_Source' incorporates:
     *  Constant: '<S3>/OmegaRot1'
     */
    if ((int32_T)FOC_slowCTRL_P.SPEED_CTRL_SELECT_n_Ref == 0) {
      /* MultiPortSwitch: '<S3>/n_Ref_Source' incorporates:
       *  Constant: '<S3>/OmegaRot2'
       */
      FOC_slowCTRL_B->n_Ref_Source = FOC_slowCTRL_P.SPEED_CTRL_MANUAL_n_RPM;
    } else {
      /* MultiPortSwitch: '<S3>/n_Ref_Source' incorporates:
       *  Inport: '<Root>/ExtSpeedReq [rpm]'
       */
      FOC_slowCTRL_B->n_Ref_Source = FOC_slowCTRL_U->ExtSpeedReqrpm;
    }

    /* End of MultiPortSwitch: '<S3>/n_Ref_Source' */

    /* Saturate: '<S3>/limit T2' */
    u0 = FOC_slowCTRL_B->n_Ref_Source;
    u1 = FOC_slowCTRL_P.SPEED_CTRL_LIMIT_n_Ref_MIN;
    u2 = FOC_slowCTRL_P.SPEED_CTRL_LIMIT_n_Ref_MAX;
    if (u0 > u2) {
      /* Saturate: '<S3>/limit T2' */
      FOC_slowCTRL_B->limitT2 = u2;
    } else if (u0 < u1) {
      /* Saturate: '<S3>/limit T2' */
      FOC_slowCTRL_B->limitT2 = u1;
    } else {
      /* Saturate: '<S3>/limit T2' */
      FOC_slowCTRL_B->limitT2 = u0;
    }

    /* End of Saturate: '<S3>/limit T2' */

    /* UnitDelay: '<S29>/Delay Input2'
     *
     * Block description for '<S29>/Delay Input2':
     *
     *  Store in Global RAM
     */
    FOC_slowCTRL_B->Yk1_g = FOC_slowCTRL_DW->DelayInput2_DSTATE_d;

    /* Sum: '<S29>/Difference Inputs1'
     *
     * Block description for '<S29>/Difference Inputs1':
     *
     *  Add in CPU
     */
    FOC_slowCTRL_B->UkYk1_d = FOC_slowCTRL_B->limitT2 - FOC_slowCTRL_B->Yk1_g;

    /* RelationalOperator: '<S30>/LowerRelop1' */
    FOC_slowCTRL_B->LowerRelop1_c = (FOC_slowCTRL_B->UkYk1_d >
      FOC_slowCTRL_B->deltariselimit_c);

    /* Product: '<S29>/delta fall limit' incorporates:
     *  Constant: '<S27>/Constant7'
     *  Constant: '<S29>/FOC_T_slow'
     */
    FOC_slowCTRL_B->deltafalllimit_m =
      FOC_slowCTRL_P.FOC_LIMIT_n_Ref_SlewRate_Down * FOC_slowCTRL_P.FOC_T_slow;

    /* RelationalOperator: '<S30>/UpperRelop' */
    FOC_slowCTRL_B->UpperRelop_l = (FOC_slowCTRL_B->UkYk1_d <
      FOC_slowCTRL_B->deltafalllimit_m);

    /* Switch: '<S30>/Switch' */
    if (FOC_slowCTRL_B->UpperRelop_l) {
      /* Switch: '<S30>/Switch' */
      FOC_slowCTRL_B->Switch_jn = FOC_slowCTRL_B->deltafalllimit_m;
    } else {
      /* Switch: '<S30>/Switch' */
      FOC_slowCTRL_B->Switch_jn = FOC_slowCTRL_B->UkYk1_d;
    }

    /* End of Switch: '<S30>/Switch' */

    /* Switch: '<S30>/Switch2' */
    if (FOC_slowCTRL_B->LowerRelop1_c) {
      /* Switch: '<S30>/Switch2' */
      FOC_slowCTRL_B->Switch2_n = FOC_slowCTRL_B->deltariselimit_c;
    } else {
      /* Switch: '<S30>/Switch2' */
      FOC_slowCTRL_B->Switch2_n = FOC_slowCTRL_B->Switch_jn;
    }

    /* End of Switch: '<S30>/Switch2' */

    /* Sum: '<S29>/Difference Inputs2'
     *
     * Block description for '<S29>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_slowCTRL_B->DifferenceInputs2_j = FOC_slowCTRL_B->Switch2_n +
      FOC_slowCTRL_B->Yk1_g;

    /* Switch: '<S27>/Switch2' incorporates:
     *  Constant: '<S27>/Constant5'
     */
    if (FOC_slowCTRL_P.FOC_SELECT_n_Ref_Ramp > FOC_slowCTRL_P.Switch2_Threshold)
    {
      /* Switch: '<S27>/Switch2' */
      FOC_slowCTRL_B->Switch2_a = FOC_slowCTRL_B->DifferenceInputs2_j;
    } else {
      /* Switch: '<S27>/Switch2' */
      FOC_slowCTRL_B->Switch2_a = FOC_slowCTRL_B->limitT2;
    }

    /* End of Switch: '<S27>/Switch2' */

    /* Gain: '<S3>/RPM => w_el' */
    u1 = 6.2831853071795862 * FOC_slowCTRL_P.FOC_z_P / 60.0;

    /* Gain: '<S3>/RPM => w_el' */
    FOC_slowCTRL_B->w_el_Ref_SPEED_CTRL = u1 * FOC_slowCTRL_B->Switch2_a;

    /* Sum: '<S3>/Add' incorporates:
     *  Inport: '<Root>/w_el [rad//s]'
     */
    FOC_slowCTRL_B->Add_h = FOC_slowCTRL_B->w_el_Ref_SPEED_CTRL -
      FOC_slowCTRL_U->w_elrads;

    /* Product: '<S3>/Product6' incorporates:
     *  Constant: '<S3>/Constant14'
     */
    FOC_slowCTRL_B->Product6 = FOC_slowCTRL_B->Add_h *
      FOC_slowCTRL_P.SPEED_CTRL_V_R;

    /* UnitDelay: '<S3>/Unit Delay' */
    FOC_slowCTRL_B->UnitDelay_l = FOC_slowCTRL_DW->UnitDelay_DSTATE_a;

    /* Sum: '<S3>/Add2' */
    FOC_slowCTRL_B->Add2 = FOC_slowCTRL_B->Product6 +
      FOC_slowCTRL_B->UnitDelay_l;

    /* MultiPortSwitch: '<S3>/TorqLimitSource' incorporates:
     *  Constant: '<S3>/OmegaRot3'
     */
    switch ((int32_T)FOC_slowCTRL_P.SPEED_CTRL_SELECT_TorqLimit) {
     case 0:
      /* MultiPortSwitch: '<S3>/TorqLimitSource' incorporates:
       *  Constant: '<S3>/Constant4'
       *  Constant: '<S3>/Constant5'
       */
      FOC_slowCTRL_B->TorqLimitSource[0] = FOC_slowCTRL_P.SPEED_CTRL_TORQLIMPOS;
      FOC_slowCTRL_B->TorqLimitSource[1] = FOC_slowCTRL_P.SPEED_CTRL_TORQLIMNEG;
      break;

     case 1:
      /* MultiPortSwitch: '<S3>/TorqLimitSource' incorporates:
       *  Inport: '<Root>/ExtTorqLim [Nm]'
       */
      FOC_slowCTRL_B->TorqLimitSource[0] = FOC_slowCTRL_U->ExtTorqLimNm[0];
      FOC_slowCTRL_B->TorqLimitSource[1] = FOC_slowCTRL_U->ExtTorqLimNm[1];
      break;

     default:
      /* MultiPortSwitch: '<S3>/TorqLimitSource' incorporates:
       *  Constant: '<S3>/ZeroTorq1'
       *  Constant: '<S3>/ZeroTorq2'
       */
      FOC_slowCTRL_B->TorqLimitSource[0] = FOC_slowCTRL_P.ZeroTorq1_Value;
      FOC_slowCTRL_B->TorqLimitSource[1] = FOC_slowCTRL_P.ZeroTorq2_Value;
      break;
    }

    /* End of MultiPortSwitch: '<S3>/TorqLimitSource' */

    /* Saturate: '<S3>/limit T1' */
    u0 = FOC_slowCTRL_B->TorqLimitSource[0];
    u1 = FOC_slowCTRL_P.limitT1_LowerSat;
    u2 = FOC_slowCTRL_P.FOC_M_peak_max;
    if (u0 > u2) {
      /* Saturate: '<S3>/limit T1' */
      FOC_slowCTRL_B->limitT1 = u2;
    } else if (u0 < u1) {
      /* Saturate: '<S3>/limit T1' */
      FOC_slowCTRL_B->limitT1 = u1;
    } else {
      /* Saturate: '<S3>/limit T1' */
      FOC_slowCTRL_B->limitT1 = u0;
    }

    /* End of Saturate: '<S3>/limit T1' */

    /* RelationalOperator: '<S28>/LowerRelop1' */
    FOC_slowCTRL_B->LowerRelop1_c1 = (FOC_slowCTRL_B->Add2 >
      FOC_slowCTRL_B->limitT1);

    /* Saturate: '<S3>/limit T3' */
    u1 = -FOC_slowCTRL_P.FOC_M_peak_max;
    u0 = FOC_slowCTRL_B->TorqLimitSource[1];
    u2 = FOC_slowCTRL_P.limitT3_UpperSat;
    if (u0 > u2) {
      /* Saturate: '<S3>/limit T3' */
      FOC_slowCTRL_B->limitT3 = u2;
    } else if (u0 < u1) {
      /* Saturate: '<S3>/limit T3' */
      FOC_slowCTRL_B->limitT3 = u1;
    } else {
      /* Saturate: '<S3>/limit T3' */
      FOC_slowCTRL_B->limitT3 = u0;
    }

    /* End of Saturate: '<S3>/limit T3' */

    /* RelationalOperator: '<S28>/UpperRelop' */
    FOC_slowCTRL_B->UpperRelop_jt = (FOC_slowCTRL_B->Add2 <
      FOC_slowCTRL_B->limitT3);

    /* Switch: '<S28>/Switch' */
    if (FOC_slowCTRL_B->UpperRelop_jt) {
      /* Switch: '<S28>/Switch' */
      FOC_slowCTRL_B->Switch_k = FOC_slowCTRL_B->limitT3;
    } else {
      /* Switch: '<S28>/Switch' */
      FOC_slowCTRL_B->Switch_k = FOC_slowCTRL_B->Add2;
    }

    /* End of Switch: '<S28>/Switch' */

    /* Switch: '<S28>/Switch2' */
    if (FOC_slowCTRL_B->LowerRelop1_c1) {
      /* Switch: '<S28>/Switch2' */
      FOC_slowCTRL_B->Switch2_l = FOC_slowCTRL_B->limitT1;
    } else {
      /* Switch: '<S28>/Switch2' */
      FOC_slowCTRL_B->Switch2_l = FOC_slowCTRL_B->Switch_k;
    }

    /* End of Switch: '<S28>/Switch2' */

    /* Sum: '<S3>/Subtract' */
    FOC_slowCTRL_B->Subtract_p = FOC_slowCTRL_B->Switch2_l -
      FOC_slowCTRL_B->Add2;

    /* Gain: '<S3>/Gain1' */
    FOC_slowCTRL_B->Gain1 = FOC_slowCTRL_P.SPEED_CTRL_K_AWU *
      FOC_slowCTRL_B->Subtract_p;

    /* Sum: '<S3>/Sum' */
    FOC_slowCTRL_B->Sum_d = FOC_slowCTRL_B->Product6 + FOC_slowCTRL_B->Gain1;

    /* Product: '<S3>/Product5' incorporates:
     *  Constant: '<S3>/FOC_T_slow'
     */
    FOC_slowCTRL_B->Product5 = FOC_slowCTRL_B->Sum_d * FOC_slowCTRL_P.FOC_T_slow;

    /* MinMax: '<S3>/avoid_div_by_0' incorporates:
     *  Constant: '<S3>/Constant'
     *  Constant: '<S3>/Constant3'
     */
    u1 = fmax(FOC_slowCTRL_P.Constant3_Value, FOC_slowCTRL_P.SPEED_CTRL_T_N);

    /* MinMax: '<S3>/avoid_div_by_0' */
    FOC_slowCTRL_B->avoid_div_by_0 = u1;

    /* Product: '<S3>/Divide' */
    FOC_slowCTRL_B->Divide = FOC_slowCTRL_B->Product5 /
      FOC_slowCTRL_B->avoid_div_by_0;

    /* Sum: '<S3>/Add1' */
    FOC_slowCTRL_B->Add1 = FOC_slowCTRL_B->Divide + FOC_slowCTRL_B->UnitDelay_l;

    /* DataTypeConversion: '<S3>/Data Type Conversion' */
    FOC_slowCTRL_B->DataTypeConversion = FOC_slowCTRL_U->SpeedCtrl_Enable;

    /* Product: '<S3>/Product' */
    FOC_slowCTRL_B->Product_k = FOC_slowCTRL_B->Add1 *
      FOC_slowCTRL_B->DataTypeConversion;

    /* Switch: '<S3>/Switch1' */
    if (FOC_slowCTRL_B->DataTypeConversion > FOC_slowCTRL_P.Switch1_Threshold) {
      /* Switch: '<S3>/Switch1' */
      FOC_slowCTRL_B->Switch1 = FOC_slowCTRL_B->Switch2_l;
    } else {
      /* Switch: '<S3>/Switch1' incorporates:
       *  Constant: '<S3>/ZeroTorq'
       */
      FOC_slowCTRL_B->Switch1 = FOC_slowCTRL_P.ZeroTorq_Value;
    }

    /* End of Switch: '<S3>/Switch1' */

    /* Update for UnitDelay: '<S29>/Delay Input2'
     *
     * Block description for '<S29>/Delay Input2':
     *
     *  Store in Global RAM
     */
    FOC_slowCTRL_DW->DelayInput2_DSTATE_d = FOC_slowCTRL_B->DifferenceInputs2_j;

    /* Update for UnitDelay: '<S3>/Unit Delay' */
    FOC_slowCTRL_DW->UnitDelay_DSTATE_a = FOC_slowCTRL_B->Product_k;
  } else {
    FOC_slowCTRL_DW->SPEED_CONTROLLER_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/SPEED_CONTROLLER' */

  /* MultiPortSwitch: '<S1>/TorqRef_Source' incorporates:
   *  Inport: '<Root>/SpeedCtrl_Enable'
   */
  if ((int32_T)FOC_slowCTRL_U->SpeedCtrl_Enable == 0) {
    /* Switch: '<S1>/Switch2' incorporates:
     *  Constant: '<S1>/Constant2'
     */
    if (FOC_slowCTRL_P.FOC_SELECT_ExtTrqReq > FOC_slowCTRL_P.Switch2_Threshold_h)
    {
      /* Switch: '<S1>/Switch2' incorporates:
       *  Inport: '<Root>/ExtTorqReq [Nm]'
       */
      FOC_slowCTRL_B->Switch2_o = FOC_slowCTRL_U->ExtTorqReqNm;
    } else {
      /* Switch: '<S1>/Switch2' incorporates:
       *  Constant: '<S1>/Constant'
       */
      FOC_slowCTRL_B->Switch2_o = FOC_slowCTRL_P.FOC_MANUAL_Torque_Request;
    }

    /* End of Switch: '<S1>/Switch2' */

    /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
    u0 = FOC_slowCTRL_B->Switch2_o;
    u1 = FOC_slowCTRL_P.FOC_LIMIT_Torque_Ref_MIN;
    u2 = FOC_slowCTRL_P.FOC_LIMIT_Torque_Ref_MAX;
    if (u0 > u2) {
      /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
      FOC_slowCTRL_B->TORQUE_REQ_LIMIT = u2;
    } else if (u0 < u1) {
      /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
      FOC_slowCTRL_B->TORQUE_REQ_LIMIT = u1;
    } else {
      /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
      FOC_slowCTRL_B->TORQUE_REQ_LIMIT = u0;
    }

    /* End of Saturate: '<S1>/TORQUE_REQ_LIMIT' */

    /* MultiPortSwitch: '<S1>/TorqRef_Source' */
    FOC_slowCTRL_B->TorqRef_Source = FOC_slowCTRL_B->TORQUE_REQ_LIMIT;
  } else {
    /* MultiPortSwitch: '<S1>/TorqRef_Source' */
    FOC_slowCTRL_B->TorqRef_Source = FOC_slowCTRL_B->Switch1;
  }

  /* End of MultiPortSwitch: '<S1>/TorqRef_Source' */

  /* UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_B->Yk1 = FOC_slowCTRL_DW->DelayInput2_DSTATE;

  /* Sum: '<S20>/Difference Inputs1'
   *
   * Block description for '<S20>/Difference Inputs1':
   *
   *  Add in CPU
   */
  FOC_slowCTRL_B->UkYk1 = FOC_slowCTRL_B->TorqRef_Source - FOC_slowCTRL_B->Yk1;

  /* RelationalOperator: '<S21>/LowerRelop1' */
  FOC_slowCTRL_B->LowerRelop1 = (FOC_slowCTRL_B->UkYk1 >
    FOC_slowCTRL_B->deltariselimit);

  /* Product: '<S20>/delta fall limit' incorporates:
   *  Constant: '<S20>/Constant6'
   *  Constant: '<S7>/Constant7'
   */
  FOC_slowCTRL_B->deltafalllimit =
    FOC_slowCTRL_P.FOC_LIMIT_Torque_Ref_SlewRate_Down *
    FOC_slowCTRL_P.FOC_T_slow;

  /* RelationalOperator: '<S21>/UpperRelop' */
  FOC_slowCTRL_B->UpperRelop = (FOC_slowCTRL_B->UkYk1 <
    FOC_slowCTRL_B->deltafalllimit);

  /* Switch: '<S21>/Switch' */
  if (FOC_slowCTRL_B->UpperRelop) {
    /* Switch: '<S21>/Switch' */
    FOC_slowCTRL_B->Switch = FOC_slowCTRL_B->deltafalllimit;
  } else {
    /* Switch: '<S21>/Switch' */
    FOC_slowCTRL_B->Switch = FOC_slowCTRL_B->UkYk1;
  }

  /* End of Switch: '<S21>/Switch' */

  /* Switch: '<S21>/Switch2' */
  if (FOC_slowCTRL_B->LowerRelop1) {
    /* Switch: '<S21>/Switch2' */
    FOC_slowCTRL_B->Switch2 = FOC_slowCTRL_B->deltariselimit;
  } else {
    /* Switch: '<S21>/Switch2' */
    FOC_slowCTRL_B->Switch2 = FOC_slowCTRL_B->Switch;
  }

  /* End of Switch: '<S21>/Switch2' */

  /* Sum: '<S20>/Difference Inputs2'
   *
   * Block description for '<S20>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_slowCTRL_B->DifferenceInputs2 = FOC_slowCTRL_B->Switch2 +
    FOC_slowCTRL_B->Yk1;

  /* Switch: '<S7>/Switch4' incorporates:
   *  Constant: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
   */
  if (FOC_slowCTRL_P.FOC_SELECT_Torque_Ref_Ramp >
      FOC_slowCTRL_P.Switch4_Threshold) {
    /* Switch: '<S7>/Switch4' */
    FOC_slowCTRL_B->Switch4 = FOC_slowCTRL_B->DifferenceInputs2;
  } else {
    /* Switch: '<S7>/Switch4' */
    FOC_slowCTRL_B->Switch4 = FOC_slowCTRL_B->TorqRef_Source;
  }

  /* End of Switch: '<S7>/Switch4' */

  /* Abs: '<S8>/Abs' */
  FOC_slowCTRL_B->Abs = fabs(FOC_slowCTRL_B->Switch4);

  /* MinMax: '<S22>/MinMax' */
  u1 = fmin(FOC_slowCTRL_B->Product1, FOC_slowCTRL_B->Abs);

  /* MinMax: '<S22>/MinMax' */
  FOC_slowCTRL_B->MinMax = u1;

  /* Abs: '<S22>/Abs1' */
  FOC_slowCTRL_B->Abs1 = fabs(FOC_slowCTRL_B->Product1);

  /* Abs: '<S22>/Abs' */
  FOC_slowCTRL_B->Abs_h = FOC_slowCTRL_B->Abs;

  /* Sum: '<S22>/Subtract' */
  FOC_slowCTRL_B->Subtract = FOC_slowCTRL_B->Abs1 - FOC_slowCTRL_B->Abs_h;

  /* RelationalOperator: '<S25>/Compare' incorporates:
   *  Constant: '<S25>/Constant'
   */
  Temp_Derating_aktiv = (FOC_slowCTRL_B->Subtract <
    FOC_slowCTRL_P.Constant_Value_n);

  /* Switch: '<S8>/Switch' */
  if (Temp_Derating_aktiv) {
    /* RelationalOperator: '<S24>/Compare' incorporates:
     *  Constant: '<S24>/Constant'
     */
    FOC_slowCTRL_B->Compare_m = (uint8_T)(FOC_slowCTRL_B->Switch4 <=
      FOC_slowCTRL_P.CompareToConstant_const);

    /* Switch: '<S22>/Switch1' */
    if (FOC_slowCTRL_B->Compare_m > FOC_slowCTRL_P.Switch1_Threshold_n) {
      /* Gain: '<S22>/Gain' */
      FOC_slowCTRL_B->Gain = FOC_slowCTRL_P.Gain_Gain_n * FOC_slowCTRL_B->MinMax;

      /* Switch: '<S22>/Switch1' */
      FOC_slowCTRL_B->Switch1_o = FOC_slowCTRL_B->Gain;
    } else {
      /* Gain: '<S22>/Gain1' */
      FOC_slowCTRL_B->Gain1_g = FOC_slowCTRL_P.Gain1_Gain *
        FOC_slowCTRL_B->MinMax;

      /* Switch: '<S22>/Switch1' */
      FOC_slowCTRL_B->Switch1_o = FOC_slowCTRL_B->Gain1_g;
    }

    /* End of Switch: '<S22>/Switch1' */

    /* Switch: '<S8>/Switch' */
    Test_Torqu_Request = FOC_slowCTRL_B->Switch1_o;
  } else {
    /* Switch: '<S8>/Switch' */
    Test_Torqu_Request = FOC_slowCTRL_B->Switch4;
  }

  /* End of Switch: '<S8>/Switch' */

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Temp_Derating_Selector'
   */
  if (FOC_slowCTRL_P.FOC_SELECT_Temp_Derating > FOC_slowCTRL_P.Switch_Threshold)
  {
    /* Switch: '<S2>/Switch' */
    FOC_slowCTRL_B->Switch_i = Test_Torqu_Request;
  } else {
    /* Switch: '<S2>/Switch' */
    FOC_slowCTRL_B->Switch_i = FOC_slowCTRL_B->Switch4;
  }

  /* End of Switch: '<S2>/Switch' */

  /* UnitDelay: '<S9>/TorqCtrlDelay' */
  FOC_slowCTRL_B->TorqCtrlDelay = FOC_slowCTRL_DW->TorqCtrlDelay_DSTATE;

  /* MinMax: '<S2>/MinMax' incorporates:
   *  Inport: '<Root>/ModInd'
   */
  u1 = FOC_slowCTRL_U->ModInd[0];
  u1 = fmax(u1, FOC_slowCTRL_U->ModInd[1]);

  /* MinMax: '<S2>/MinMax' */
  FOC_slowCTRL_B->MinMax_d = u1;

  /* Sum: '<S9>/Sum1' incorporates:
   *  Constant: '<S9>/FOC_TORQ_REDUC_START'
   */
  FOC_slowCTRL_B->Sum1 = FOC_slowCTRL_P.FOC_TORQ_REDUC_START -
    FOC_slowCTRL_B->MinMax_d;

  /* Gain: '<S9>/FOC_TORQ_REDUC_PGAIN' */
  FOC_slowCTRL_B->FOC_TORQ_REDUC_PGAIN = FOC_slowCTRL_P.FOC_TORQ_REDUC_PGAIN *
    FOC_slowCTRL_B->Sum1;

  /* Sum: '<S9>/TorqCtrlSum3' */
  FOC_slowCTRL_B->TorqCtrlSum3 = FOC_slowCTRL_B->TorqCtrlDelay +
    FOC_slowCTRL_B->FOC_TORQ_REDUC_PGAIN;

  /* Saturate: '<S9>/Saturation' */
  u0 = FOC_slowCTRL_B->TorqCtrlSum3;
  u1 = FOC_slowCTRL_P.Saturation_LowerSat_a;
  u2 = FOC_slowCTRL_P.Saturation_UpperSat_d;
  if (u0 > u2) {
    /* Saturate: '<S9>/Saturation' */
    FOC_slowCTRL_B->Saturation_j = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S9>/Saturation' */
    FOC_slowCTRL_B->Saturation_j = u1;
  } else {
    /* Saturate: '<S9>/Saturation' */
    FOC_slowCTRL_B->Saturation_j = u0;
  }

  /* End of Saturate: '<S9>/Saturation' */

  /* Outport: '<Root>/TorqueRefDerated [Nm]' incorporates:
   *  Product: '<S9>/TorqCtrlProduct'
   */
  FOC_slowCTRL_Y->TorqueRefDeratedNm = FOC_slowCTRL_B->Switch_i *
    FOC_slowCTRL_B->Saturation_j;

  /* UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_B->Yk1_o = FOC_slowCTRL_DW->DelayInput2_DSTATE_f;

  /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
   *  Constant: '<S5>/Constant3'
   */
  switch ((int32_T)FOC_slowCTRL_P.FOC_SELECT_Id_Ref) {
   case 1:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/Constant5'
     */
    Id_Ref_raw = FOC_slowCTRL_P.FOC_MANUAL_Id_Ref;
    break;

   case 2:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    Id_Ref_raw = FOC_slowCTRL_P.IdRefZero1_Value;
    break;

   case 3:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    Id_Ref_raw = FOC_slowCTRL_P.IdRefZero1_Value;
    break;

   case 4:
    /* Gain: '<S5>/Gain' incorporates:
     *  Outport: '<Root>/TorqueRefDerated [Nm]'
     */
    FOC_slowCTRL_B->Gain_m = FOC_slowCTRL_P.Gain_Gain *
      FOC_slowCTRL_Y->TorqueRefDeratedNm;

    /* Abs: '<S10>/Abs2' */
    FOC_slowCTRL_B->Abs2_b = fabs(FOC_slowCTRL_B->Gain_m);

    /* Lookup_n-D: '<S10>/Id_Ref_M_MTPC' incorporates:
     *  Abs: '<S10>/Abs2'
     */
    FOC_slowCTRL_B->Id_Ref_M_MTPC = look1_binlxpw(FOC_slowCTRL_B->Abs2_b,
      FOC_slowCTRL_P.Id_Ref_M_MTPC_bp01Data,
      FOC_slowCTRL_P.Id_Ref_M_MTPC_tableData, 19U);

    /* MultiPortSwitch: '<S5>/Multiport Switch' */
    Id_Ref_raw = FOC_slowCTRL_B->Id_Ref_M_MTPC;
    break;

   case 5:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    Id_Ref_raw = FOC_slowCTRL_P.IdRefZero1_Value;
    break;

   default:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    Id_Ref_raw = FOC_slowCTRL_P.IdRefZero1_Value;
    break;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch' */

  /* MultiPortSwitch: '<S5>/Multiport Switch1' */
  if ((int32_T)FOC_slowCTRL_B->Bias == 1) {
    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Constant: '<S5>/zero_Current'
     */
    FOC_slowCTRL_B->MultiportSwitch1 = FOC_slowCTRL_P.zero_Current_Value;
  } else {
    /* MultiPortSwitch: '<S5>/Multiport Switch1' */
    FOC_slowCTRL_B->MultiportSwitch1 = Id_Ref_raw;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch1' */

  /* Sum: '<S12>/Difference Inputs1'
   *
   * Block description for '<S12>/Difference Inputs1':
   *
   *  Add in CPU
   */
  FOC_slowCTRL_B->UkYk1_a = FOC_slowCTRL_B->MultiportSwitch1 -
    FOC_slowCTRL_B->Yk1_o;

  /* Product: '<S12>/delta rise limit' incorporates:
   *  Constant: '<S11>/Constant6'
   *  Constant: '<S12>/Constant6'
   */
  FOC_slowCTRL_B->deltariselimit_k =
    FOC_slowCTRL_P.FOC_LIMIT_Idq_Ref_SlewRate_Up * FOC_slowCTRL_P.FOC_T_slow;

  /* RelationalOperator: '<S13>/LowerRelop1' */
  FOC_slowCTRL_B->LowerRelop1_n = (FOC_slowCTRL_B->UkYk1_a >
    FOC_slowCTRL_B->deltariselimit_k);

  /* Product: '<S12>/delta fall limit' incorporates:
   *  Constant: '<S11>/Constant7'
   *  Constant: '<S12>/Constant6'
   */
  FOC_slowCTRL_B->deltafalllimit_b =
    FOC_slowCTRL_P.FOC_LIMIT_Idq_Ref_SlewRate_Down * FOC_slowCTRL_P.FOC_T_slow;

  /* RelationalOperator: '<S13>/UpperRelop' */
  FOC_slowCTRL_B->UpperRelop_j = (FOC_slowCTRL_B->UkYk1_a <
    FOC_slowCTRL_B->deltafalllimit_b);

  /* Switch: '<S13>/Switch' */
  if (FOC_slowCTRL_B->UpperRelop_j) {
    /* Switch: '<S13>/Switch' */
    FOC_slowCTRL_B->Switch_n = FOC_slowCTRL_B->deltafalllimit_b;
  } else {
    /* Switch: '<S13>/Switch' */
    FOC_slowCTRL_B->Switch_n = FOC_slowCTRL_B->UkYk1_a;
  }

  /* End of Switch: '<S13>/Switch' */

  /* Switch: '<S13>/Switch2' */
  if (FOC_slowCTRL_B->LowerRelop1_n) {
    /* Switch: '<S13>/Switch2' */
    FOC_slowCTRL_B->Switch2_h = FOC_slowCTRL_B->deltariselimit_k;
  } else {
    /* Switch: '<S13>/Switch2' */
    FOC_slowCTRL_B->Switch2_h = FOC_slowCTRL_B->Switch_n;
  }

  /* End of Switch: '<S13>/Switch2' */

  /* Sum: '<S12>/Difference Inputs2'
   *
   * Block description for '<S12>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_slowCTRL_B->DifferenceInputs2_f = FOC_slowCTRL_B->Switch2_h +
    FOC_slowCTRL_B->Yk1_o;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Constant: '<S11>/Constant5'
   */
  if (FOC_slowCTRL_P.FOC_SELECT_Idq_Ref_Ramp >
      FOC_slowCTRL_P.Switch2_Threshold_m) {
    /* Switch: '<S11>/Switch2' */
    FOC_slowCTRL_B->Switch2_p = FOC_slowCTRL_B->DifferenceInputs2_f;
  } else {
    /* Switch: '<S11>/Switch2' */
    FOC_slowCTRL_B->Switch2_p = FOC_slowCTRL_B->MultiportSwitch1;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Bias: '<S6>/Bias' incorporates:
   *  Constant: '<S2>/FOC_ENABLE_Idq_Ref'
   */
  FOC_slowCTRL_B->Bias_h = FOC_slowCTRL_P.FOC_ENABLE_Idq_Ref +
    FOC_slowCTRL_P.Bias_Bias_f;

  /* Product: '<S18>/delta rise limit' incorporates:
   *  Constant: '<S17>/Constant6'
   *  Constant: '<S18>/Constant6'
   */
  FOC_slowCTRL_B->deltariselimit_o =
    FOC_slowCTRL_P.FOC_LIMIT_Idq_Ref_SlewRate_Up * FOC_slowCTRL_P.FOC_T_slow;

  /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
   *  Constant: '<S6>/Constant5'
   */
  switch ((int32_T)FOC_slowCTRL_P.FOC_SELECT_Iq_Ref) {
   case 1:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/Constant3'
     */
    Iq_Ref_raw = FOC_slowCTRL_P.FOC_MANUAL_Iq_Ref;
    break;

   case 2:
    /* Gain: '<S14>/Gain' */
    u1 = 1.0 / (1.5 * FOC_slowCTRL_P.FOC_z_P);

    /* Gain: '<S14>/Gain' incorporates:
     *  Outport: '<Root>/TorqueRefDerated [Nm]'
     */
    FOC_slowCTRL_B->Gain_g = u1 * FOC_slowCTRL_Y->TorqueRefDeratedNm;

    /* Sum: '<S14>/Add' incorporates:
     *  Constant: '<S14>/Constant1'
     *  Constant: '<S14>/Constant2'
     */
    FOC_slowCTRL_B->Add_p = FOC_slowCTRL_P.FOC_L_sd - FOC_slowCTRL_P.FOC_L_sq;

    /* Product: '<S14>/Product' */
    FOC_slowCTRL_B->Product_l = FOC_slowCTRL_B->Add_p *
      FOC_slowCTRL_B->Switch2_p;

    /* Sum: '<S14>/Add1' incorporates:
     *  Constant: '<S14>/Constant4'
     */
    FOC_slowCTRL_B->Add1_d = FOC_slowCTRL_B->Product_l +
      FOC_slowCTRL_P.FOC_Psi_PM;

    /* Product: '<S14>/Divide' incorporates:
     *  Constant: '<S14>/Constant'
     */
    FOC_slowCTRL_B->Divide_k = FOC_slowCTRL_P.Constant_Value /
      FOC_slowCTRL_B->Add1_d;

    /* Product: '<S14>/IqRefRaw_PSM' */
    FOC_slowCTRL_B->IqRefRaw_PSM = FOC_slowCTRL_B->Divide_k *
      FOC_slowCTRL_B->Gain_g;

    /* MultiPortSwitch: '<S6>/Multiport Switch' */
    Iq_Ref_raw = FOC_slowCTRL_B->IqRefRaw_PSM;
    break;

   case 3:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    Iq_Ref_raw = FOC_slowCTRL_P.IqRefZero_Value;
    break;

   case 4:
    /* Gain: '<S6>/Gain' incorporates:
     *  Outport: '<Root>/TorqueRefDerated [Nm]'
     */
    FOC_slowCTRL_B->Gain_k = FOC_slowCTRL_P.Gain_Gain_o *
      FOC_slowCTRL_Y->TorqueRefDeratedNm;

    /* Signum: '<S16>/Sign' */
    u0 = FOC_slowCTRL_B->Gain_k;
    if (rtIsNaN(u0)) {
      /* Signum: '<S16>/Sign' */
      FOC_slowCTRL_B->Sign = u0;
    } else if (u0 < 0.0) {
      /* Signum: '<S16>/Sign' */
      FOC_slowCTRL_B->Sign = -1.0;
    } else {
      /* Signum: '<S16>/Sign' */
      FOC_slowCTRL_B->Sign = (u0 > 0.0);
    }

    /* End of Signum: '<S16>/Sign' */

    /* Abs: '<S16>/Abs2' */
    FOC_slowCTRL_B->Abs2 = fabs(FOC_slowCTRL_B->Gain_k);

    /* Lookup_n-D: '<S16>/Iq_Ref_M_MTPC' incorporates:
     *  Abs: '<S16>/Abs2'
     */
    FOC_slowCTRL_B->Iq_Ref_M_MTPC = look1_binlxpw(FOC_slowCTRL_B->Abs2,
      FOC_slowCTRL_P.Iq_Ref_M_MTPC_bp01Data,
      FOC_slowCTRL_P.Iq_Ref_M_MTPC_tableData, 19U);

    /* Product: '<S16>/Product1' */
    FOC_slowCTRL_B->Product1_b = FOC_slowCTRL_B->Iq_Ref_M_MTPC *
      FOC_slowCTRL_B->Sign;

    /* MultiPortSwitch: '<S6>/Multiport Switch' */
    Iq_Ref_raw = FOC_slowCTRL_B->Product1_b;
    break;

   case 5:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    Iq_Ref_raw = FOC_slowCTRL_P.IqRefZero_Value;
    break;

   default:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    Iq_Ref_raw = FOC_slowCTRL_P.IqRefZero_Value;
    break;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch' */

  /* MultiPortSwitch: '<S6>/Multiport Switch1' */
  if ((int32_T)FOC_slowCTRL_B->Bias_h == 1) {
    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Constant: '<S6>/zero_Current'
     */
    FOC_slowCTRL_B->MultiportSwitch1_f = FOC_slowCTRL_P.zero_Current_Value_c;
  } else {
    /* MultiPortSwitch: '<S6>/Multiport Switch1' */
    FOC_slowCTRL_B->MultiportSwitch1_f = Iq_Ref_raw;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch1' */

  /* UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_B->Yk1_h = FOC_slowCTRL_DW->DelayInput2_DSTATE_e;

  /* Sum: '<S18>/Difference Inputs1'
   *
   * Block description for '<S18>/Difference Inputs1':
   *
   *  Add in CPU
   */
  FOC_slowCTRL_B->UkYk1_f = FOC_slowCTRL_B->MultiportSwitch1_f -
    FOC_slowCTRL_B->Yk1_h;

  /* RelationalOperator: '<S19>/LowerRelop1' */
  FOC_slowCTRL_B->LowerRelop1_k = (FOC_slowCTRL_B->UkYk1_f >
    FOC_slowCTRL_B->deltariselimit_o);

  /* Product: '<S18>/delta fall limit' incorporates:
   *  Constant: '<S17>/Constant7'
   *  Constant: '<S18>/Constant6'
   */
  FOC_slowCTRL_B->deltafalllimit_f =
    FOC_slowCTRL_P.FOC_LIMIT_Idq_Ref_SlewRate_Down * FOC_slowCTRL_P.FOC_T_slow;

  /* RelationalOperator: '<S19>/UpperRelop' */
  FOC_slowCTRL_B->UpperRelop_o = (FOC_slowCTRL_B->UkYk1_f <
    FOC_slowCTRL_B->deltafalllimit_f);

  /* Switch: '<S19>/Switch' */
  if (FOC_slowCTRL_B->UpperRelop_o) {
    /* Switch: '<S19>/Switch' */
    FOC_slowCTRL_B->Switch_j = FOC_slowCTRL_B->deltafalllimit_f;
  } else {
    /* Switch: '<S19>/Switch' */
    FOC_slowCTRL_B->Switch_j = FOC_slowCTRL_B->UkYk1_f;
  }

  /* End of Switch: '<S19>/Switch' */

  /* Switch: '<S19>/Switch2' */
  if (FOC_slowCTRL_B->LowerRelop1_k) {
    /* Switch: '<S19>/Switch2' */
    FOC_slowCTRL_B->Switch2_pl = FOC_slowCTRL_B->deltariselimit_o;
  } else {
    /* Switch: '<S19>/Switch2' */
    FOC_slowCTRL_B->Switch2_pl = FOC_slowCTRL_B->Switch_j;
  }

  /* End of Switch: '<S19>/Switch2' */

  /* Sum: '<S18>/Difference Inputs2'
   *
   * Block description for '<S18>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_slowCTRL_B->DifferenceInputs2_fc = FOC_slowCTRL_B->Switch2_pl +
    FOC_slowCTRL_B->Yk1_h;

  /* Switch: '<S17>/Switch2' incorporates:
   *  Constant: '<S17>/Constant5'
   */
  if (FOC_slowCTRL_P.FOC_SELECT_Idq_Ref_Ramp >
      FOC_slowCTRL_P.Switch2_Threshold_j) {
    /* Switch: '<S17>/Switch2' */
    FOC_slowCTRL_B->Switch2_e = FOC_slowCTRL_B->DifferenceInputs2_fc;
  } else {
    /* Switch: '<S17>/Switch2' */
    FOC_slowCTRL_B->Switch2_e = FOC_slowCTRL_B->MultiportSwitch1_f;
  }

  /* End of Switch: '<S17>/Switch2' */

  /* Product: '<S15>/Product' incorporates:
   *  Constant: '<S15>/Constant'
   */
  FOC_slowCTRL_B->Product = FOC_slowCTRL_P.FOC_LIMIT_I_PHASE_PEAK_MAX *
    FOC_slowCTRL_P.FOC_LIMIT_I_PHASE_PEAK_MAX;

  /* Product: '<S15>/Product1' */
  FOC_slowCTRL_B->Product1_e = FOC_slowCTRL_B->Switch2_p *
    FOC_slowCTRL_B->Switch2_p;

  /* Sum: '<S15>/Subtract1' */
  FOC_slowCTRL_B->Subtract1 = FOC_slowCTRL_B->Product -
    FOC_slowCTRL_B->Product1_e;

  /* Sqrt: '<S15>/Sqrt' */
  FOC_slowCTRL_B->Sqrt = sqrt(FOC_slowCTRL_B->Subtract1);

  /* MinMax: '<S15>/mcrPsiRef1' */
  u1 = fmin(FOC_slowCTRL_B->Switch2_e, FOC_slowCTRL_B->Sqrt);

  /* MinMax: '<S15>/mcrPsiRef1' */
  FOC_slowCTRL_B->mcrPsiRef1 = u1;

  /* Gain: '<S15>/PsiReduceGain1' */
  FOC_slowCTRL_B->PsiReduceGain1 = FOC_slowCTRL_P.PsiReduceGain1_Gain *
    FOC_slowCTRL_B->Sqrt;

  /* MinMax: '<S15>/MinMax1' */
  u1 = fmax(FOC_slowCTRL_B->mcrPsiRef1, FOC_slowCTRL_B->PsiReduceGain1);

  /* MinMax: '<S15>/MinMax1' */
  FOC_slowCTRL_B->IqRef = u1;

  /* Sum: '<S15>/Subtract' */
  FOC_slowCTRL_B->FOC_IqDiff = FOC_slowCTRL_B->Switch2_e - FOC_slowCTRL_B->IqRef;

  /* UnitDelay: '<S15>/Unit Delay' */
  FOC_slowCTRL_B->UnitDelay_f = FOC_slowCTRL_DW->UnitDelay_DSTATE_b;

  /* Gain: '<S8>/Gain1' incorporates:
   *  Inport: '<Root>/MotTemp [degC]'
   */
  FOC_MotTemp_PSM = FOC_slowCTRL_P.Gain1_Gain_d * FOC_slowCTRL_U->MotTempdegC;

  /* RelationalOperator: '<S26>/Compare' incorporates:
   *  Constant: '<S26>/Constant'
   *  Inport: '<Root>/MotTemp [degC]'
   */
  FOC_slowCTRL_B->Compare = (uint8_T)(FOC_slowCTRL_U->MotTempdegC <=
    FOC_slowCTRL_P.FOC_LIMIT_Torque_Derating_Temp);

  /* Sum: '<S23>/Sum' incorporates:
   *  Constant: '<S23>/Constant'
   */
  FOC_slowCTRL_B->Sum = FOC_slowCTRL_P.Constant_Value_j - (real_T)
    FOC_slowCTRL_B->Compare;

  /* Product: '<S23>/Product' incorporates:
   *  Constant: '<S23>/Constant1'
   */
  FOC_slowCTRL_B->Product_m = FOC_slowCTRL_B->Sum *
    FOC_slowCTRL_P.FOC_Torque_Derating_Temp_Gain;

  /* Sum: '<S23>/Sum1' */
  FOC_slowCTRL_B->Sum1_a = FOC_slowCTRL_B->Product_m +
    FOC_slowCTRL_B->Saturation;

  /* UnitDelay: '<S9>/UnitDelay' */
  FOC_slowCTRL_B->UnitDelay_i = FOC_slowCTRL_DW->UnitDelay_DSTATE_m;

  /* Gain: '<S9>/FOC_IQ_DIFF_REDUC_GAIN' */
  FOC_slowCTRL_B->FOC_IQ_DIFF_REDUC_GAIN = FOC_slowCTRL_P.FOC_IQ_DIFF_REDUC_GAIN
    * FOC_slowCTRL_B->UnitDelay_i;

  /* Gain: '<S9>/FOC_TORQ_REDUC_GAIN' */
  FOC_slowCTRL_B->FOC_TORQ_REDUC_GAIN = FOC_slowCTRL_P.FOC_TORQ_REDUC_GAIN *
    FOC_slowCTRL_B->Sum1;

  /* Gain: '<S9>/Gain' incorporates:
   *  Outport: '<Root>/TorqueRefDerated [Nm]'
   */
  Torq_Ref_PSM = FOC_slowCTRL_P.Gain_Gain_a * FOC_slowCTRL_Y->TorqueRefDeratedNm;

  /* Gain: '<S9>/Gain1' */
  Torq_Ref_IqDiff = FOC_slowCTRL_P.Gain1_Gain_j *
    FOC_slowCTRL_B->FOC_IQ_DIFF_REDUC_GAIN;

  /* Gain: '<S9>/Gain2' */
  Torq_Ref_PGAIN = FOC_slowCTRL_P.Gain2_Gain *
    FOC_slowCTRL_B->FOC_TORQ_REDUC_PGAIN;

  /* Switch: '<S9>/TorqCtrlSwitch1' */
  if (FOC_slowCTRL_B->Switch_i >= FOC_slowCTRL_P.TorqCtrlSwitch1_Threshold) {
    /* Gain: '<S9>/TorqCtrlMinusOne' */
    FOC_slowCTRL_B->TorqCtrlMinusOne = FOC_slowCTRL_P.TorqCtrlMinusOne_Gain *
      FOC_slowCTRL_B->FOC_IQ_DIFF_REDUC_GAIN;

    /* Switch: '<S9>/TorqCtrlSwitch1' */
    FOC_slowCTRL_B->TorqCtrlSwitch1 = FOC_slowCTRL_B->TorqCtrlMinusOne;
  } else {
    /* Switch: '<S9>/TorqCtrlSwitch1' */
    FOC_slowCTRL_B->TorqCtrlSwitch1 = FOC_slowCTRL_B->FOC_IQ_DIFF_REDUC_GAIN;
  }

  /* End of Switch: '<S9>/TorqCtrlSwitch1' */

  /* Switch: '<S9>/TorqCtrlSwitch3' */
  if (FOC_slowCTRL_B->TorqCtrlSwitch1 >=
      FOC_slowCTRL_P.TorqCtrlSwitch3_Threshold) {
    /* Switch: '<S9>/TorqCtrlSwitch3' */
    FOC_slowCTRL_B->TorqCtrlSwitch3 = FOC_slowCTRL_B->FOC_TORQ_REDUC_GAIN;
  } else {
    /* MinMax: '<S9>/TorqCtrlMin2' */
    u1 = fmin(FOC_slowCTRL_B->TorqCtrlSwitch1,
              FOC_slowCTRL_B->FOC_TORQ_REDUC_GAIN);

    /* MinMax: '<S9>/TorqCtrlMin2' */
    FOC_slowCTRL_B->TorqCtrlMin2 = u1;

    /* Switch: '<S9>/TorqCtrlSwitch3' */
    FOC_slowCTRL_B->TorqCtrlSwitch3 = FOC_slowCTRL_B->TorqCtrlMin2;
  }

  /* End of Switch: '<S9>/TorqCtrlSwitch3' */

  /* Sum: '<S9>/TorqCtrlSum4' */
  FOC_slowCTRL_B->TorqCtrlSum4 = FOC_slowCTRL_B->Saturation_j -
    FOC_slowCTRL_B->FOC_TORQ_REDUC_PGAIN;

  /* Sum: '<S9>/TorqCtrlSum1' */
  FOC_slowCTRL_B->TorqCtrlSum1 = FOC_slowCTRL_B->TorqCtrlSwitch3 +
    FOC_slowCTRL_B->TorqCtrlSum4;

  /* Gain: '<S2>/[1//s] => [rpm]' */
  u1 = 60.0 / (6.2831853071795862 * FOC_slowCTRL_P.FOC_z_P);

  /* Gain: '<S2>/[1//s] => [rpm]' incorporates:
   *  Inport: '<Root>/w_el [rad//s]'
   */
  FOC_slowCTRL_B->usrpm = u1 * FOC_slowCTRL_U->w_elrads;

  /* Switch: '<S1>/Switch1' incorporates:
   *  Constant: '<S1>/0: P_Udc 1: Udc_measured'
   */
  if (FOC_slowCTRL_P.SCF_SELECT_U_DC_INPUT > FOC_slowCTRL_P.Switch1_Threshold_h)
  {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Inport: '<Root>/U_DC [V]'
     */
    Udc_scf = FOC_slowCTRL_U->U_DCV;
  } else {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Constant: '<S1>/Udc2'
     */
    Udc_scf = FOC_slowCTRL_P.SCF_MANUAL_U_DC;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Product: '<S4>/Product' incorporates:
   *  Inport: '<Root>/I_dq_Act [A]'
   */
  FOC_slowCTRL_B->Product_j[0] = FOC_slowCTRL_U->I_dq_ActA[0] *
    FOC_slowCTRL_U->I_dq_ActA[0];
  FOC_slowCTRL_B->Product_j[1] = FOC_slowCTRL_U->I_dq_ActA[1] *
    FOC_slowCTRL_U->I_dq_ActA[1];
  FOC_slowCTRL_B->Product_j[2] = FOC_slowCTRL_U->I_dq_ActA[2] *
    FOC_slowCTRL_U->I_dq_ActA[2];
  FOC_slowCTRL_B->Product_j[3] = FOC_slowCTRL_U->I_dq_ActA[3] *
    FOC_slowCTRL_U->I_dq_ActA[3];

  /* Sum: '<S4>/Subtract2' */
  u1 = FOC_slowCTRL_B->Product_j[0];
  u1 += FOC_slowCTRL_B->Product_j[1];
  u1 += FOC_slowCTRL_B->Product_j[2];
  u1 += FOC_slowCTRL_B->Product_j[3];

  /* Sum: '<S4>/Subtract2' */
  FOC_slowCTRL_B->Subtract2 = u1;

  /* Sqrt: '<S4>/Sqrt' */
  FOC_slowCTRL_B->Sqrt_b = sqrt(FOC_slowCTRL_B->Subtract2);

  /* Gain: '<S4>/I_ph_peak' */
  FOC_slowCTRL_B->I_ph_peak = FOC_slowCTRL_P.I_ph_peak_Gain *
    FOC_slowCTRL_B->Sqrt_b;

  /* Gain: '<S4>/I_ph_rms' */
  FOC_slowCTRL_B->I_ph_rms = FOC_slowCTRL_P.I_ph_rms_Gain *
    FOC_slowCTRL_B->Sqrt_b;

  /* MultiPortSwitch: '<S4>/Selectphicalc1' incorporates:
   *  Constant: '<S4>/Constant4'
   */
  switch ((int32_T)FOC_slowCTRL_P.FOC_SELECT_TorqEstMdl) {
   case 0:
    /* Outport: '<Root>/TorqueEst [Nm]' incorporates:
     *  Constant: '<S4>/Constant'
     */
    FOC_slowCTRL_Y->TorqueEstNm = FOC_slowCTRL_P.Constant_Value_p;
    break;

   case 1:
    /* Sum: '<S31>/Sum' incorporates:
     *  Constant: '<S31>/FOC_L_sd'
     *  Constant: '<S31>/FOC_L_sq'
     */
    FOC_slowCTRL_B->Sum_e = FOC_slowCTRL_P.FOC_L_sd - FOC_slowCTRL_P.FOC_L_sq;

    /* Product: '<S31>/Product2' incorporates:
     *  Inport: '<Root>/I_dq_Act [A]'
     */
    FOC_slowCTRL_B->Product2 = FOC_slowCTRL_U->I_dq_ActA[3] *
      FOC_slowCTRL_B->Sum_e;

    /* Product: '<S31>/product_2' incorporates:
     *  Inport: '<Root>/I_dq_Act [A]'
     */
    FOC_slowCTRL_B->product_2 = FOC_slowCTRL_B->Sum_e *
      FOC_slowCTRL_U->I_dq_ActA[2] * FOC_slowCTRL_U->I_dq_ActA[3];

    /* Sum: '<S31>/add2' */
    FOC_slowCTRL_B->add2 = FOC_slowCTRL_B->product_2 + FOC_slowCTRL_B->Product2;

    /* Product: '<S31>/Product1' incorporates:
     *  Constant: '<S31>/FOC_Psi_PM'
     *  Inport: '<Root>/I_dq_Act [A]'
     */
    FOC_slowCTRL_B->Product1_eh = FOC_slowCTRL_U->I_dq_ActA[1] *
      FOC_slowCTRL_P.FOC_Psi_PM;

    /* Product: '<S31>/product' incorporates:
     *  Inport: '<Root>/I_dq_Act [A]'
     */
    FOC_slowCTRL_B->product = FOC_slowCTRL_B->Sum_e * FOC_slowCTRL_U->I_dq_ActA
      [0] * FOC_slowCTRL_U->I_dq_ActA[1];

    /* Sum: '<S31>/add1' */
    FOC_slowCTRL_B->add1 = FOC_slowCTRL_B->product + FOC_slowCTRL_B->Product1_eh;

    /* Sum: '<S31>/Add' */
    FOC_slowCTRL_B->Add = FOC_slowCTRL_B->add1 + FOC_slowCTRL_B->add2;

    /* Gain: '<S31>/3*Z_p//2' */
    u1 = 3.0 * FOC_slowCTRL_P.FOC_z_P / 2.0;

    /* Gain: '<S31>/3*Z_p//2' */
    FOC_slowCTRL_B->uZ_p2 = u1 * FOC_slowCTRL_B->Add;

    /* Gain: '<S4>/3ph_to_6ph_factor' */
    FOC_slowCTRL_B->uph_to_6ph_factor = FOC_slowCTRL_P.uph_to_6ph_factor_Gain *
      FOC_slowCTRL_B->uZ_p2;

    /* Outport: '<Root>/TorqueEst [Nm]' */
    FOC_slowCTRL_Y->TorqueEstNm = FOC_slowCTRL_B->uph_to_6ph_factor;
    break;

   case 2:
    /* Outport: '<Root>/TorqueEst [Nm]' */
    FOC_slowCTRL_Y->TorqueEstNm = 0.0;
    break;

   default:
    /* Outport: '<Root>/TorqueEst [Nm]' */
    FOC_slowCTRL_Y->TorqueEstNm = 0.0;
    break;
  }

  /* End of MultiPortSwitch: '<S4>/Selectphicalc1' */

  /* Gain: '<S4>/TorqEst_Nm' incorporates:
   *  Outport: '<Root>/TorqueEst [Nm]'
   */
  M_est = FOC_slowCTRL_P.TorqEst_Nm_Gain * FOC_slowCTRL_Y->TorqueEstNm;

  /* UnitDelay: '<S1>/SCF_Cnt' */
  SCF_Cnt = FOC_slowCTRL_DW->SCF_Cnt_DSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Counter_Start'
   */
  FOC_slowCTRL_B->Sum_k = FOC_slowCTRL_P.Counter_Start_Value + SCF_Cnt;

  /* Update for UnitDelay: '<S23>/Unit Delay' */
  FOC_slowCTRL_DW->UnitDelay_DSTATE = FOC_slowCTRL_B->Sum1_a;

  /* Update for UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE = FOC_slowCTRL_B->DifferenceInputs2;

  /* Update for UnitDelay: '<S9>/TorqCtrlDelay' */
  FOC_slowCTRL_DW->TorqCtrlDelay_DSTATE = FOC_slowCTRL_B->TorqCtrlSum1;

  /* Update for UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE_f = FOC_slowCTRL_B->DifferenceInputs2_f;

  /* Update for UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE_e = FOC_slowCTRL_B->DifferenceInputs2_fc;

  /* Update for UnitDelay: '<S15>/Unit Delay' */
  FOC_slowCTRL_DW->UnitDelay_DSTATE_b = FOC_slowCTRL_B->FOC_IqDiff;

  /* Update for UnitDelay: '<S9>/UnitDelay' */
  FOC_slowCTRL_DW->UnitDelay_DSTATE_m = FOC_slowCTRL_B->UnitDelay_f;

  /* Update for UnitDelay: '<S1>/SCF_Cnt' */
  FOC_slowCTRL_DW->SCF_Cnt_DSTATE = FOC_slowCTRL_B->Sum_k;

  /* End of Outputs for SubSystem: '<Root>/FOC_slowCTRL' */

  /* Outport: '<Root>/I_dq_Ref [A]' */
  FOC_slowCTRL_Y->I_dq_RefA[0] = FOC_slowCTRL_B->Switch2_p;
  FOC_slowCTRL_Y->I_dq_RefA[1] = FOC_slowCTRL_B->IqRef;
}

/* Model initialize function */
void FOC_slowCTRL_initialize(RT_MODEL_FOC_slowCTRL_T *const FOC_slowCTRL_M)
{
  B_FOC_slowCTRL_T *FOC_slowCTRL_B = FOC_slowCTRL_M->blockIO;
  DW_FOC_slowCTRL_T *FOC_slowCTRL_DW = FOC_slowCTRL_M->dwork;
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
  Test_Torqu_Request = 0.0;
  Id_Ref_raw = 0.0;
  Iq_Ref_raw = 0.0;
  FOC_MotTemp_PSM = 0.0;
  Torq_Ref_PSM = 0.0;
  Torq_Ref_IqDiff = 0.0;
  Torq_Ref_PGAIN = 0.0;
  Udc_scf = 0.0;
  M_est = 0.0;
  SCF_Cnt = 0.0;
  Temp_Derating_aktiv = false;

  /* states (dwork) */
  (void) memset((void *)FOC_slowCTRL_DW, 0,
                sizeof(DW_FOC_slowCTRL_T));

  /* external inputs */
  (void)memset(FOC_slowCTRL_U, 0, sizeof(ExtU_FOC_slowCTRL_T));

  /* external outputs */
  (void)memset(FOC_slowCTRL_Y, 0, sizeof(ExtY_FOC_slowCTRL_T));

  /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_slowCTRL' */
  /* InitializeConditions for UnitDelay: '<S23>/Unit Delay' */
  FOC_slowCTRL_DW->UnitDelay_DSTATE =
    FOC_slowCTRL_P.UnitDelay_InitialCondition_j;

  /* InitializeConditions for UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE =
    FOC_slowCTRL_P.DelayInput2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S9>/TorqCtrlDelay' */
  FOC_slowCTRL_DW->TorqCtrlDelay_DSTATE =
    FOC_slowCTRL_P.TorqCtrlDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE_f =
    FOC_slowCTRL_P.DelayInput2_InitialCondition_p;

  /* InitializeConditions for UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE_e =
    FOC_slowCTRL_P.DelayInput2_InitialCondition_l;

  /* InitializeConditions for UnitDelay: '<S15>/Unit Delay' */
  FOC_slowCTRL_DW->UnitDelay_DSTATE_b =
    FOC_slowCTRL_P.UnitDelay_InitialCondition_k;

  /* InitializeConditions for UnitDelay: '<S9>/UnitDelay' */
  FOC_slowCTRL_DW->UnitDelay_DSTATE_m =
    FOC_slowCTRL_P.UnitDelay_InitialCondition_h;

  /* InitializeConditions for UnitDelay: '<S1>/SCF_Cnt' */
  FOC_slowCTRL_DW->SCF_Cnt_DSTATE = FOC_slowCTRL_P.SCF_Cnt_InitialCondition;

  /* SystemInitialize for Enabled SubSystem: '<S1>/SPEED_CONTROLLER' */
  /* InitializeConditions for UnitDelay: '<S29>/Delay Input2'
   *
   * Block description for '<S29>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_slowCTRL_DW->DelayInput2_DSTATE_d =
    FOC_slowCTRL_P.FOC_LIMIT_n_Ref_SlewRate_InitVal;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
  FOC_slowCTRL_DW->UnitDelay_DSTATE_a =
    FOC_slowCTRL_P.UnitDelay_InitialCondition;

  /* SystemInitialize for Switch: '<S3>/Switch1' incorporates:
   *  Outport: '<S3>/TorqReq [Nm]'
   */
  FOC_slowCTRL_B->Switch1 = FOC_slowCTRL_P.TorqReqNm_Y0;

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
