/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SCF.c
 *
 * Code generated for Simulink model 'FOC_SCF'.
 *
 * Model version                  : 5.72
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Feb 19 21:00:42 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_SCF.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FOC_SCF_types.h"
#include <string.h>
#include "FOC_SCF_private.h"

const bus_SCF_t FOC_SCF_rtZbus_SCF_t = { { 0.0F, 0.0F },/* I_dq_Ref */
  0.0F,                                /* TorqueEst */
  0.0F,                                /* TorqueRefDerated */
  0.0F                                 /* n_Act */
};

real32_T look1_iflf_binlxpw(real32_T u0, const real32_T bp0[], const real32_T
  table[], uint32_T maxIndex)
{
  real32_T frac;
  real32_T yL_0d0;
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
void FOC_SCF_step(RT_MODEL_FOC_SCF_T *const FOC_SCF_M)
{
  B_FOC_SCF_T *FOC_SCF_B = FOC_SCF_M->blockIO;
  DW_FOC_SCF_T *FOC_SCF_DW = FOC_SCF_M->dwork;
  ExtU_FOC_SCF_T *FOC_SCF_U = (ExtU_FOC_SCF_T *) FOC_SCF_M->inputs;
  ExtY_FOC_SCF_T *FOC_SCF_Y = (ExtY_FOC_SCF_T *) FOC_SCF_M->outputs;
  int32_T i;
  real32_T u0;
  real32_T u1;
  real32_T u2;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_SCF' */
  /* Product: '<S12>/delta rise limit' incorporates:
   *  Constant: '<S11>/Constant6'
   *  Constant: '<S12>/Constant6'
   */
  FOC_SCF_B->deltariselimit_m = (real32_T)
    (FOC_SCF_P.FOC_LIMIT_Idq_Ref_SlewRate_Up * FOC_SCF_P.Constant6_Value);

  /* Bias: '<S5>/Bias' incorporates:
   *  Constant: '<S2>/FOC_ENABLE_Idq_Ref'
   */
  FOC_SCF_B->Bias = FOC_SCF_P.FOC_ENABLE_Idq_Ref + FOC_SCF_P.Bias_Bias;

  /* UnitDelay: '<S23>/Unit Delay' */
  FOC_SCF_B->UnitDelay = FOC_SCF_DW->UnitDelay_DSTATE;

  /* Saturate: '<S23>/Saturation' */
  u0 = FOC_SCF_B->UnitDelay;
  u1 = FOC_SCF_P.Saturation_LowerSat;
  u2 = FOC_SCF_P.Saturation_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<S23>/Saturation' */
    FOC_SCF_B->Saturation = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S23>/Saturation' */
    FOC_SCF_B->Saturation = u1;
  } else {
    /* Saturate: '<S23>/Saturation' */
    FOC_SCF_B->Saturation = u0;
  }

  /* End of Saturate: '<S23>/Saturation' */

  /* Sum: '<S23>/Sum2' incorporates:
   *  Constant: '<S23>/Constant2'
   */
  FOC_SCF_B->Sum2 = FOC_SCF_P.Constant2_Value - FOC_SCF_B->Saturation;

  /* Product: '<S8>/Product1' incorporates:
   *  Constant: '<S8>/Maximum_Torque_Maschine'
   */
  FOC_SCF_B->Product1 = FOC_SCF_P.FOC_LIMIT_Motor_Torque_MAX * FOC_SCF_B->Sum2;

  /* Product: '<S20>/delta rise limit' incorporates:
   *  Constant: '<S20>/Constant6'
   *  Constant: '<S7>/Constant6'
   */
  FOC_SCF_B->deltariselimit_o = (real32_T)
    (FOC_SCF_P.FOC_LIMIT_Torque_Ref_SlewRate_Up * FOC_SCF_P.Constant6_Value_e);

  /* Outputs for Enabled SubSystem: '<S1>/SPEED_CONTROLLER' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (FOC_SCF_U->bus_SMF.SPEED_CTRL_Enable > 0.0F) {
    if (!FOC_SCF_DW->SPEED_CONTROLLER_MODE) {
      /* InitializeConditions for UnitDelay: '<S29>/Delay Input2'
       *
       * Block description for '<S29>/Delay Input2':
       *
       *  Store in Global RAM
       */
      FOC_SCF_DW->DelayInput2_DSTATE_m =
        FOC_SCF_P.FOC_LIMIT_n_Ref_SlewRate_InitVal;

      /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
      FOC_SCF_DW->UnitDelay_DSTATE_mg = FOC_SCF_P.UnitDelay_InitialCondition;
      FOC_SCF_DW->SPEED_CONTROLLER_MODE = true;
    }

    /* Product: '<S29>/delta rise limit' incorporates:
     *  Constant: '<S27>/Constant6'
     *  Constant: '<S29>/FOC_T_slow'
     */
    FOC_SCF_B->deltariselimit_h = (real32_T)
      (FOC_SCF_P.FOC_LIMIT_n_Ref_SlewRate_Up * FOC_SCF_P.FOC_T_slow_Value);

    /* MultiPortSwitch: '<S3>/n_Ref_Source' incorporates:
     *  Constant: '<S3>/OmegaRot1'
     */
    if (FOC_SCF_P.SPEED_CTRL_SELECT_n_Ref == 0) {
      /* MultiPortSwitch: '<S3>/n_Ref_Source' incorporates:
       *  Constant: '<S3>/OmegaRot2'
       */
      FOC_SCF_B->n_Ref_Source = FOC_SCF_P.SPEED_CTRL_MANUAL_n_RPM;
    } else {
      /* MultiPortSwitch: '<S3>/n_Ref_Source' */
      FOC_SCF_B->n_Ref_Source = FOC_SCF_U->bus_BSW_SMF.EXT_Speed_Request;
    }

    /* End of MultiPortSwitch: '<S3>/n_Ref_Source' */

    /* Saturate: '<S3>/limit T2' */
    u0 = FOC_SCF_B->n_Ref_Source;
    u1 = FOC_SCF_P.SPEED_CTRL_LIMIT_n_Ref_MIN;
    u2 = FOC_SCF_P.SPEED_CTRL_LIMIT_n_Ref_MAX;
    if (u0 > u2) {
      /* Saturate: '<S3>/limit T2' */
      FOC_SCF_B->limitT2 = u2;
    } else if (u0 < u1) {
      /* Saturate: '<S3>/limit T2' */
      FOC_SCF_B->limitT2 = u1;
    } else {
      /* Saturate: '<S3>/limit T2' */
      FOC_SCF_B->limitT2 = u0;
    }

    /* End of Saturate: '<S3>/limit T2' */

    /* UnitDelay: '<S29>/Delay Input2'
     *
     * Block description for '<S29>/Delay Input2':
     *
     *  Store in Global RAM
     */
    FOC_SCF_B->Yk1_e = FOC_SCF_DW->DelayInput2_DSTATE_m;

    /* Sum: '<S29>/Difference Inputs1'
     *
     * Block description for '<S29>/Difference Inputs1':
     *
     *  Add in CPU
     */
    FOC_SCF_B->UkYk1_d = FOC_SCF_B->limitT2 - FOC_SCF_B->Yk1_e;

    /* RelationalOperator: '<S30>/LowerRelop1' */
    FOC_SCF_B->LowerRelop1_i5 = (FOC_SCF_B->UkYk1_d >
      FOC_SCF_B->deltariselimit_h);

    /* Product: '<S29>/delta fall limit' incorporates:
     *  Constant: '<S27>/Constant7'
     *  Constant: '<S29>/FOC_T_slow'
     */
    FOC_SCF_B->deltafalllimit_ah = (real32_T)
      (FOC_SCF_P.FOC_LIMIT_n_Ref_SlewRate_Down * FOC_SCF_P.FOC_T_slow_Value);

    /* RelationalOperator: '<S30>/UpperRelop' */
    FOC_SCF_B->UpperRelop_i = (FOC_SCF_B->UkYk1_d < FOC_SCF_B->deltafalllimit_ah);

    /* Switch: '<S30>/Switch' */
    if (FOC_SCF_B->UpperRelop_i) {
      /* Switch: '<S30>/Switch' */
      FOC_SCF_B->Switch_g = FOC_SCF_B->deltafalllimit_ah;
    } else {
      /* Switch: '<S30>/Switch' */
      FOC_SCF_B->Switch_g = FOC_SCF_B->UkYk1_d;
    }

    /* End of Switch: '<S30>/Switch' */

    /* Switch: '<S30>/Switch2' */
    if (FOC_SCF_B->LowerRelop1_i5) {
      /* Switch: '<S30>/Switch2' */
      FOC_SCF_B->Switch2_f = FOC_SCF_B->deltariselimit_h;
    } else {
      /* Switch: '<S30>/Switch2' */
      FOC_SCF_B->Switch2_f = FOC_SCF_B->Switch_g;
    }

    /* End of Switch: '<S30>/Switch2' */

    /* Sum: '<S29>/Difference Inputs2'
     *
     * Block description for '<S29>/Difference Inputs2':
     *
     *  Add in CPU
     */
    FOC_SCF_B->DifferenceInputs2_m = FOC_SCF_B->Switch2_f + FOC_SCF_B->Yk1_e;

    /* Switch: '<S27>/Switch2' incorporates:
     *  Constant: '<S27>/Constant5'
     */
    if (FOC_SCF_P.FOC_SELECT_n_Ref_Ramp > FOC_SCF_P.Switch2_Threshold_l) {
      /* Switch: '<S27>/Switch2' */
      FOC_SCF_B->n_Ref = FOC_SCF_B->DifferenceInputs2_m;
    } else {
      /* Switch: '<S27>/Switch2' */
      FOC_SCF_B->n_Ref = FOC_SCF_B->limitT2;
    }

    /* End of Switch: '<S27>/Switch2' */

    /* Gain: '<S3>/RPM => w_el' */
    FOC_SCF_B->w_el_Ref_SpeedCtrl = FOC_SCF_P.RPMw_el_Gain * FOC_SCF_B->n_Ref;

    /* Sum: '<S3>/Add' */
    FOC_SCF_B->Add_e = FOC_SCF_B->w_el_Ref_SpeedCtrl - FOC_SCF_U->bus_FCF.w_el;

    /* Product: '<S3>/Product6' incorporates:
     *  Constant: '<S3>/Constant14'
     */
    FOC_SCF_B->Product6 = FOC_SCF_B->Add_e * FOC_SCF_P.SPEED_CTRL_V_R;

    /* UnitDelay: '<S3>/Unit Delay' */
    FOC_SCF_B->UnitDelay_k = FOC_SCF_DW->UnitDelay_DSTATE_mg;

    /* Sum: '<S3>/Add2' */
    FOC_SCF_B->Add2 = FOC_SCF_B->Product6 + FOC_SCF_B->UnitDelay_k;

    /* MultiPortSwitch: '<S3>/TorqLimitSource' incorporates:
     *  Constant: '<S3>/OmegaRot3'
     */
    switch (FOC_SCF_P.SPEED_CTRL_SELECT_TorqLimit) {
     case 0:
      /* MultiPortSwitch: '<S3>/TorqLimitSource' incorporates:
       *  Constant: '<S3>/Constant4'
       *  Constant: '<S3>/Constant5'
       */
      FOC_SCF_B->TorqLimitSource[0] = FOC_SCF_P.SPEED_CTRL_TORQLIMPOS;
      FOC_SCF_B->TorqLimitSource[1] = FOC_SCF_P.SPEED_CTRL_TORQLIMNEG;
      break;

     case 1:
      /* MultiPortSwitch: '<S3>/TorqLimitSource' */
      FOC_SCF_B->TorqLimitSource[0] =
        FOC_SCF_U->bus_BSW_SMF.EXT_Torque_Limit_Pos;
      FOC_SCF_B->TorqLimitSource[1] =
        FOC_SCF_U->bus_BSW_SMF.EXT_Torque_Limit_Neg;
      break;

     default:
      /* MultiPortSwitch: '<S3>/TorqLimitSource' incorporates:
       *  Constant: '<S3>/ZeroTorq1'
       *  Constant: '<S3>/ZeroTorq2'
       */
      FOC_SCF_B->TorqLimitSource[0] = FOC_SCF_P.ZeroTorq1_Value;
      FOC_SCF_B->TorqLimitSource[1] = FOC_SCF_P.ZeroTorq2_Value;
      break;
    }

    /* End of MultiPortSwitch: '<S3>/TorqLimitSource' */

    /* Saturate: '<S3>/limit T1' */
    u0 = FOC_SCF_B->TorqLimitSource[0];
    u1 = FOC_SCF_P.limitT1_LowerSat;
    u2 = FOC_SCF_P.FOC_M_peak_max;
    if (u0 > u2) {
      /* Saturate: '<S3>/limit T1' */
      FOC_SCF_B->limitT1 = u2;
    } else if (u0 < u1) {
      /* Saturate: '<S3>/limit T1' */
      FOC_SCF_B->limitT1 = u1;
    } else {
      /* Saturate: '<S3>/limit T1' */
      FOC_SCF_B->limitT1 = u0;
    }

    /* End of Saturate: '<S3>/limit T1' */

    /* RelationalOperator: '<S28>/LowerRelop1' */
    FOC_SCF_B->LowerRelop1_d = (FOC_SCF_B->Add2 > FOC_SCF_B->limitT1);

    /* Saturate: '<S3>/limit T3' */
    u0 = FOC_SCF_B->TorqLimitSource[1];
    u1 = FOC_SCF_P.limitT3_LowerSat;
    u2 = FOC_SCF_P.limitT3_UpperSat;
    if (u0 > u2) {
      /* Saturate: '<S3>/limit T3' */
      FOC_SCF_B->limitT3 = u2;
    } else if (u0 < u1) {
      /* Saturate: '<S3>/limit T3' */
      FOC_SCF_B->limitT3 = u1;
    } else {
      /* Saturate: '<S3>/limit T3' */
      FOC_SCF_B->limitT3 = u0;
    }

    /* End of Saturate: '<S3>/limit T3' */

    /* RelationalOperator: '<S28>/UpperRelop' */
    FOC_SCF_B->UpperRelop_id = (FOC_SCF_B->Add2 < FOC_SCF_B->limitT3);

    /* Switch: '<S28>/Switch' */
    if (FOC_SCF_B->UpperRelop_id) {
      /* Switch: '<S28>/Switch' */
      FOC_SCF_B->Switch_p = FOC_SCF_B->limitT3;
    } else {
      /* Switch: '<S28>/Switch' */
      FOC_SCF_B->Switch_p = FOC_SCF_B->Add2;
    }

    /* End of Switch: '<S28>/Switch' */

    /* Switch: '<S28>/Switch2' */
    if (FOC_SCF_B->LowerRelop1_d) {
      /* Switch: '<S28>/Switch2' */
      FOC_SCF_B->Switch2_b = FOC_SCF_B->limitT1;
    } else {
      /* Switch: '<S28>/Switch2' */
      FOC_SCF_B->Switch2_b = FOC_SCF_B->Switch_p;
    }

    /* End of Switch: '<S28>/Switch2' */

    /* Sum: '<S3>/Subtract' */
    FOC_SCF_B->Subtract_m = FOC_SCF_B->Switch2_b - FOC_SCF_B->Add2;

    /* Gain: '<S3>/Gain1' */
    FOC_SCF_B->Gain1 = FOC_SCF_P.SPEED_CTRL_K_AWU * FOC_SCF_B->Subtract_m;

    /* Sum: '<S3>/Sum' */
    FOC_SCF_B->Sum_b = FOC_SCF_B->Product6 + FOC_SCF_B->Gain1;

    /* Product: '<S3>/Product5' incorporates:
     *  Constant: '<S3>/FOC_T_slow'
     */
    FOC_SCF_B->Product5 = FOC_SCF_B->Sum_b * FOC_SCF_P.FOC_T_slow_Value_a;

    /* MinMax: '<S3>/avoid_div_by_0' incorporates:
     *  Constant: '<S3>/Constant'
     *  Constant: '<S3>/Constant3'
     */
    u0 = fmaxf(FOC_SCF_P.Constant3_Value, FOC_SCF_P.SPEED_CTRL_T_N);

    /* MinMax: '<S3>/avoid_div_by_0' */
    FOC_SCF_B->avoid_div_by_0 = u0;

    /* Product: '<S3>/Divide' */
    FOC_SCF_B->Divide = FOC_SCF_B->Product5 / FOC_SCF_B->avoid_div_by_0;

    /* Sum: '<S3>/Add1' */
    FOC_SCF_B->Add1 = FOC_SCF_B->Divide + FOC_SCF_B->UnitDelay_k;

    /* Product: '<S3>/Product' */
    FOC_SCF_B->Product_p = FOC_SCF_B->Add1 *
      FOC_SCF_U->bus_SMF.SPEED_CTRL_Enable;

    /* Switch: '<S3>/Switch1' */
    if (FOC_SCF_U->bus_SMF.SPEED_CTRL_Enable > FOC_SCF_P.Switch1_Threshold) {
      /* Switch: '<S3>/Switch1' */
      FOC_SCF_B->M_Ref_SpeedCtrl = FOC_SCF_B->Switch2_b;
    } else {
      /* Switch: '<S3>/Switch1' incorporates:
       *  Constant: '<S3>/ZeroTorq'
       */
      FOC_SCF_B->M_Ref_SpeedCtrl = FOC_SCF_P.ZeroTorq_Value;
    }

    /* End of Switch: '<S3>/Switch1' */

    /* Update for UnitDelay: '<S29>/Delay Input2'
     *
     * Block description for '<S29>/Delay Input2':
     *
     *  Store in Global RAM
     */
    FOC_SCF_DW->DelayInput2_DSTATE_m = FOC_SCF_B->DifferenceInputs2_m;

    /* Update for UnitDelay: '<S3>/Unit Delay' */
    FOC_SCF_DW->UnitDelay_DSTATE_mg = FOC_SCF_B->Product_p;
  } else {
    FOC_SCF_DW->SPEED_CONTROLLER_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/SPEED_CONTROLLER' */

  /* MultiPortSwitch: '<S1>/TorqRef_Source' */
  if ((int32_T)FOC_SCF_U->bus_SMF.SPEED_CTRL_Enable == 0) {
    /* Switch: '<S1>/Switch2' incorporates:
     *  Constant: '<S1>/Constant2'
     */
    if (FOC_SCF_P.FOC_SELECT_ExtTrqReq > FOC_SCF_P.Switch2_Threshold) {
      /* Switch: '<S1>/Switch2' */
      FOC_SCF_B->Switch2_d = FOC_SCF_U->bus_BSW_SMF.EXT_Torque_Request;
    } else {
      /* Switch: '<S1>/Switch2' incorporates:
       *  Constant: '<S1>/Constant'
       */
      FOC_SCF_B->Switch2_d = FOC_SCF_P.FOC_MANUAL_Torque_Request;
    }

    /* End of Switch: '<S1>/Switch2' */

    /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
    u0 = FOC_SCF_B->Switch2_d;
    u1 = FOC_SCF_P.FOC_LIMIT_Torque_Ref_MIN;
    u2 = FOC_SCF_P.FOC_LIMIT_Torque_Ref_MAX;
    if (u0 > u2) {
      /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
      FOC_SCF_B->TORQUE_REQ_LIMIT = u2;
    } else if (u0 < u1) {
      /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
      FOC_SCF_B->TORQUE_REQ_LIMIT = u1;
    } else {
      /* Saturate: '<S1>/TORQUE_REQ_LIMIT' */
      FOC_SCF_B->TORQUE_REQ_LIMIT = u0;
    }

    /* End of Saturate: '<S1>/TORQUE_REQ_LIMIT' */

    /* MultiPortSwitch: '<S1>/TorqRef_Source' */
    FOC_SCF_B->TorqRef_Source = FOC_SCF_B->TORQUE_REQ_LIMIT;
  } else {
    /* MultiPortSwitch: '<S1>/TorqRef_Source' */
    FOC_SCF_B->TorqRef_Source = FOC_SCF_B->M_Ref_SpeedCtrl;
  }

  /* End of MultiPortSwitch: '<S1>/TorqRef_Source' */

  /* UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_B->Yk1_n = FOC_SCF_DW->DelayInput2_DSTATE_i;

  /* Sum: '<S20>/Difference Inputs1'
   *
   * Block description for '<S20>/Difference Inputs1':
   *
   *  Add in CPU
   */
  FOC_SCF_B->UkYk1_k = FOC_SCF_B->TorqRef_Source - FOC_SCF_B->Yk1_n;

  /* RelationalOperator: '<S21>/LowerRelop1' */
  FOC_SCF_B->LowerRelop1 = (FOC_SCF_B->UkYk1_k > FOC_SCF_B->deltariselimit_o);

  /* Product: '<S20>/delta fall limit' incorporates:
   *  Constant: '<S20>/Constant6'
   *  Constant: '<S7>/Constant7'
   */
  FOC_SCF_B->deltafalllimit_a = (real32_T)
    (FOC_SCF_P.FOC_LIMIT_Torque_Ref_SlewRate_Down * FOC_SCF_P.Constant6_Value_e);

  /* RelationalOperator: '<S21>/UpperRelop' */
  FOC_SCF_B->UpperRelop = (FOC_SCF_B->UkYk1_k < FOC_SCF_B->deltafalllimit_a);

  /* Switch: '<S21>/Switch' */
  if (FOC_SCF_B->UpperRelop) {
    /* Switch: '<S21>/Switch' */
    FOC_SCF_B->Switch_k = FOC_SCF_B->deltafalllimit_a;
  } else {
    /* Switch: '<S21>/Switch' */
    FOC_SCF_B->Switch_k = FOC_SCF_B->UkYk1_k;
  }

  /* End of Switch: '<S21>/Switch' */

  /* Switch: '<S21>/Switch2' */
  if (FOC_SCF_B->LowerRelop1) {
    /* Switch: '<S21>/Switch2' */
    FOC_SCF_B->Switch2_a = FOC_SCF_B->deltariselimit_o;
  } else {
    /* Switch: '<S21>/Switch2' */
    FOC_SCF_B->Switch2_a = FOC_SCF_B->Switch_k;
  }

  /* End of Switch: '<S21>/Switch2' */

  /* Sum: '<S20>/Difference Inputs2'
   *
   * Block description for '<S20>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_SCF_B->DifferenceInputs2_n = FOC_SCF_B->Switch2_a + FOC_SCF_B->Yk1_n;

  /* Switch: '<S7>/Switch4' incorporates:
   *  Constant: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
   */
  if (FOC_SCF_P.FOC_SELECT_Torque_Ref_Ramp > FOC_SCF_P.Switch4_Threshold) {
    /* Switch: '<S7>/Switch4' */
    FOC_SCF_B->Switch4 = FOC_SCF_B->DifferenceInputs2_n;
  } else {
    /* Switch: '<S7>/Switch4' */
    FOC_SCF_B->Switch4 = FOC_SCF_B->TorqRef_Source;
  }

  /* End of Switch: '<S7>/Switch4' */

  /* Abs: '<S8>/Abs' */
  FOC_SCF_B->Abs = fabsf(FOC_SCF_B->Switch4);

  /* MinMax: '<S22>/MinMax' */
  u0 = fminf(FOC_SCF_B->Product1, FOC_SCF_B->Abs);

  /* MinMax: '<S22>/MinMax' */
  FOC_SCF_B->MinMax = u0;

  /* Abs: '<S22>/Abs1' */
  FOC_SCF_B->Abs1 = fabsf(FOC_SCF_B->Product1);

  /* Abs: '<S22>/Abs' */
  FOC_SCF_B->Abs_o = FOC_SCF_B->Abs;

  /* Sum: '<S22>/Subtract' */
  FOC_SCF_B->Subtract = FOC_SCF_B->Abs1 - FOC_SCF_B->Abs_o;

  /* RelationalOperator: '<S25>/Compare' incorporates:
   *  Constant: '<S25>/Constant'
   */
  FOC_SCF_B->Temp_Derating_aktiv = (FOC_SCF_B->Subtract <
    FOC_SCF_P.Constant_Value_g);

  /* Switch: '<S8>/Switch' */
  if (FOC_SCF_B->Temp_Derating_aktiv) {
    /* RelationalOperator: '<S24>/Compare' incorporates:
     *  Constant: '<S24>/Constant'
     */
    FOC_SCF_B->Compare_d = (uint8_T)(FOC_SCF_B->Switch4 <=
      FOC_SCF_P.CompareToConstant_const);

    /* Switch: '<S22>/Switch1' */
    if (FOC_SCF_B->Compare_d > FOC_SCF_P.Switch1_Threshold_k) {
      /* Gain: '<S22>/Gain' */
      FOC_SCF_B->Gain_n = FOC_SCF_P.Gain_Gain_l * FOC_SCF_B->MinMax;

      /* Switch: '<S22>/Switch1' */
      FOC_SCF_B->Switch1 = FOC_SCF_B->Gain_n;
    } else {
      /* Gain: '<S22>/Gain1' */
      FOC_SCF_B->Gain1_a = FOC_SCF_P.Gain1_Gain * FOC_SCF_B->MinMax;

      /* Switch: '<S22>/Switch1' */
      FOC_SCF_B->Switch1 = FOC_SCF_B->Gain1_a;
    }

    /* End of Switch: '<S22>/Switch1' */

    /* Switch: '<S8>/Switch' */
    FOC_SCF_B->Test_Torqu_Request = FOC_SCF_B->Switch1;
  } else {
    /* Switch: '<S8>/Switch' */
    FOC_SCF_B->Test_Torqu_Request = FOC_SCF_B->Switch4;
  }

  /* End of Switch: '<S8>/Switch' */

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Temp_Derating_Selector'
   */
  if (FOC_SCF_P.FOC_SELECT_Temp_Derating > FOC_SCF_P.Switch_Threshold) {
    /* Switch: '<S2>/Switch' */
    FOC_SCF_B->Switch_l = FOC_SCF_B->Test_Torqu_Request;
  } else {
    /* Switch: '<S2>/Switch' */
    FOC_SCF_B->Switch_l = FOC_SCF_B->Switch4;
  }

  /* End of Switch: '<S2>/Switch' */

  /* UnitDelay: '<S9>/TorqCtrlDelay' */
  FOC_SCF_B->TorqCtrlDelay = FOC_SCF_DW->TorqCtrlDelay_DSTATE;

  /* MinMax: '<S2>/MinMax' incorporates:
   *  Inport: '<Root>/bus_FCF'
   */
  u0 = FOC_SCF_U->bus_FCF.ModInd[0];
  u0 = fmaxf(u0, FOC_SCF_U->bus_FCF.ModInd[1]);
  u0 = fmaxf(u0, FOC_SCF_U->bus_FCF.ModInd[2]);

  /* MinMax: '<S2>/MinMax' */
  FOC_SCF_B->MinMax_n = u0;

  /* Sum: '<S9>/Sum1' incorporates:
   *  Constant: '<S9>/FOC_TORQ_REDUC_START'
   */
  FOC_SCF_B->Sum1 = FOC_SCF_P.FOC_TORQ_REDUC_START - FOC_SCF_B->MinMax_n;

  /* Gain: '<S9>/FOC_TORQ_REDUC_PGAIN' */
  FOC_SCF_B->FOC_TORQ_REDUC_PGAIN = FOC_SCF_P.FOC_TORQ_REDUC_PGAIN *
    FOC_SCF_B->Sum1;

  /* Sum: '<S9>/TorqCtrlSum3' */
  FOC_SCF_B->TorqCtrlSum3 = FOC_SCF_B->TorqCtrlDelay +
    FOC_SCF_B->FOC_TORQ_REDUC_PGAIN;

  /* Saturate: '<S9>/Saturation' */
  u0 = FOC_SCF_B->TorqCtrlSum3;
  u1 = FOC_SCF_P.Saturation_LowerSat_e;
  u2 = FOC_SCF_P.Saturation_UpperSat_h;
  if (u0 > u2) {
    /* Saturate: '<S9>/Saturation' */
    FOC_SCF_B->Saturation_d = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S9>/Saturation' */
    FOC_SCF_B->Saturation_d = u1;
  } else {
    /* Saturate: '<S9>/Saturation' */
    FOC_SCF_B->Saturation_d = u0;
  }

  /* End of Saturate: '<S9>/Saturation' */

  /* Product: '<S9>/TorqCtrlProduct' */
  FOC_SCF_B->TorqCtrlProduct = FOC_SCF_B->Switch_l * FOC_SCF_B->Saturation_d;

  /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
   *  Constant: '<S5>/Constant3'
   */
  switch ((int32_T)FOC_SCF_P.FOC_SELECT_Id_Ref) {
   case 1:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/Constant5'
     */
    FOC_SCF_B->Id_Ref_raw = FOC_SCF_P.FOC_MANUAL_Id_Ref;
    break;

   case 2:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    FOC_SCF_B->Id_Ref_raw = FOC_SCF_P.IdRefZero1_Value;
    break;

   case 3:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    FOC_SCF_B->Id_Ref_raw = FOC_SCF_P.IdRefZero1_Value;
    break;

   case 4:
    /* Gain: '<S5>/Gain' */
    FOC_SCF_B->Gain_i = FOC_SCF_P.Gain_Gain * FOC_SCF_B->TorqCtrlProduct;

    /* Abs: '<S10>/Abs2' */
    FOC_SCF_B->Abs2_l = fabsf(FOC_SCF_B->Gain_i);

    /* Lookup_n-D: '<S10>/Id_Ref_M_MTPC' incorporates:
     *  Abs: '<S10>/Abs2'
     */
    FOC_SCF_B->Id_Ref_M_MTPC = look1_iflf_binlxpw(FOC_SCF_B->Abs2_l,
      FOC_SCF_P.Id_Ref_M_MTPC_bp01Data, FOC_SCF_P.Id_Ref_M_MTPC_tableData, 19U);

    /* MultiPortSwitch: '<S5>/Multiport Switch' */
    FOC_SCF_B->Id_Ref_raw = FOC_SCF_B->Id_Ref_M_MTPC;
    break;

   case 5:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    FOC_SCF_B->Id_Ref_raw = FOC_SCF_P.IdRefZero1_Value;
    break;

   default:
    /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
     *  Constant: '<S5>/IdRefZero1'
     */
    FOC_SCF_B->Id_Ref_raw = FOC_SCF_P.IdRefZero1_Value;
    break;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch' */

  /* MultiPortSwitch: '<S5>/Multiport Switch1' */
  if ((int32_T)FOC_SCF_B->Bias == 1) {
    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Constant: '<S5>/zero_Current'
     */
    FOC_SCF_B->MultiportSwitch1_o = FOC_SCF_P.zero_Current_Value;
  } else {
    /* MultiPortSwitch: '<S5>/Multiport Switch1' */
    FOC_SCF_B->MultiportSwitch1_o = FOC_SCF_B->Id_Ref_raw;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch1' */

  /* UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_B->Yk1_b = FOC_SCF_DW->DelayInput2_DSTATE_h;

  /* Sum: '<S12>/Difference Inputs1'
   *
   * Block description for '<S12>/Difference Inputs1':
   *
   *  Add in CPU
   */
  FOC_SCF_B->UkYk1_l = FOC_SCF_B->MultiportSwitch1_o - FOC_SCF_B->Yk1_b;

  /* RelationalOperator: '<S13>/LowerRelop1' */
  FOC_SCF_B->LowerRelop1_i = (FOC_SCF_B->UkYk1_l > FOC_SCF_B->deltariselimit_m);

  /* Product: '<S12>/delta fall limit' incorporates:
   *  Constant: '<S11>/Constant7'
   *  Constant: '<S12>/Constant6'
   */
  FOC_SCF_B->deltafalllimit_o = (real32_T)
    (FOC_SCF_P.FOC_LIMIT_Idq_Ref_SlewRate_Down * FOC_SCF_P.Constant6_Value);

  /* RelationalOperator: '<S13>/UpperRelop' */
  FOC_SCF_B->UpperRelop_d = (FOC_SCF_B->UkYk1_l < FOC_SCF_B->deltafalllimit_o);

  /* Switch: '<S13>/Switch' */
  if (FOC_SCF_B->UpperRelop_d) {
    /* Switch: '<S13>/Switch' */
    FOC_SCF_B->Switch_m = FOC_SCF_B->deltafalllimit_o;
  } else {
    /* Switch: '<S13>/Switch' */
    FOC_SCF_B->Switch_m = FOC_SCF_B->UkYk1_l;
  }

  /* End of Switch: '<S13>/Switch' */

  /* Switch: '<S13>/Switch2' */
  if (FOC_SCF_B->LowerRelop1_i) {
    /* Switch: '<S13>/Switch2' */
    FOC_SCF_B->Switch2_e = FOC_SCF_B->deltariselimit_m;
  } else {
    /* Switch: '<S13>/Switch2' */
    FOC_SCF_B->Switch2_e = FOC_SCF_B->Switch_m;
  }

  /* End of Switch: '<S13>/Switch2' */

  /* Sum: '<S12>/Difference Inputs2'
   *
   * Block description for '<S12>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_SCF_B->DifferenceInputs2_f = FOC_SCF_B->Switch2_e + FOC_SCF_B->Yk1_b;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Constant: '<S11>/Constant5'
   */
  if (FOC_SCF_P.FOC_SELECT_Idq_Ref_Ramp > FOC_SCF_P.Switch2_Threshold_f) {
    /* Switch: '<S11>/Switch2' */
    FOC_SCF_B->Switch2_ae = FOC_SCF_B->DifferenceInputs2_f;
  } else {
    /* Switch: '<S11>/Switch2' */
    FOC_SCF_B->Switch2_ae = FOC_SCF_B->MultiportSwitch1_o;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Product: '<S18>/delta rise limit' incorporates:
   *  Constant: '<S17>/Constant6'
   *  Constant: '<S18>/Constant6'
   */
  FOC_SCF_B->deltariselimit = FOC_SCF_P.FOC_LIMIT_Idq_Ref_SlewRate_Up *
    FOC_SCF_P.Constant6_Value_f;

  /* Bias: '<S6>/Bias' incorporates:
   *  Constant: '<S2>/FOC_ENABLE_Idq_Ref'
   */
  FOC_SCF_B->Bias_h = FOC_SCF_P.FOC_ENABLE_Idq_Ref + FOC_SCF_P.Bias_Bias_k;

  /* Gain: '<S6>/Gain' */
  FOC_SCF_B->Gain = FOC_SCF_P.Gain_Gain_d * FOC_SCF_B->TorqCtrlProduct;

  /* Abs: '<S16>/Abs2' */
  FOC_SCF_B->Abs2 = fabsf(FOC_SCF_B->Gain);

  /* Lookup_n-D: '<S16>/Iq_Ref_M_MTPC' incorporates:
   *  Abs: '<S16>/Abs2'
   */
  FOC_SCF_B->Iq_Ref_M_MTPC = look1_iflf_binlxpw(FOC_SCF_B->Abs2,
    FOC_SCF_P.Iq_Ref_M_MTPC_bp01Data, FOC_SCF_P.Iq_Ref_M_MTPC_tableData, 19U);

  /* Signum: '<S16>/Sign' */
  u0 = FOC_SCF_B->Gain;
  if (rtIsNaNF(u0)) {
    /* Signum: '<S16>/Sign' */
    FOC_SCF_B->Sign = (rtNaNF);
  } else if (u0 < 0.0F) {
    /* Signum: '<S16>/Sign' */
    FOC_SCF_B->Sign = -1.0F;
  } else {
    /* Signum: '<S16>/Sign' */
    FOC_SCF_B->Sign = (real32_T)(u0 > 0.0F);
  }

  /* End of Signum: '<S16>/Sign' */

  /* Product: '<S16>/Product1' */
  FOC_SCF_B->I_q_Ref_MTPC = FOC_SCF_B->Iq_Ref_M_MTPC * FOC_SCF_B->Sign;

  /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
   *  Constant: '<S6>/Constant5'
   */
  switch ((int32_T)FOC_SCF_P.FOC_SELECT_Iq_Ref) {
   case 1:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/Constant3'
     */
    FOC_SCF_B->Iq_Ref_raw = FOC_SCF_P.FOC_MANUAL_Iq_Ref;
    break;

   case 2:
    /* Gain: '<S14>/Gain' */
    FOC_SCF_B->Gain_e = FOC_SCF_P.Gain_Gain_n * FOC_SCF_B->TorqCtrlProduct;

    /* Sum: '<S14>/Add' incorporates:
     *  Constant: '<S14>/Constant1'
     *  Constant: '<S14>/Constant2'
     */
    FOC_SCF_B->Add_h = FOC_SCF_P.FOC_L_sd - FOC_SCF_P.FOC_L_sq;

    /* Product: '<S14>/Product' */
    FOC_SCF_B->Product_n = FOC_SCF_B->Add_h * FOC_SCF_B->Switch2_ae;

    /* Sum: '<S14>/Add1' incorporates:
     *  Constant: '<S14>/Constant4'
     */
    FOC_SCF_B->Add1_o = FOC_SCF_B->Product_n + FOC_SCF_P.FOC_Psi_PM;

    /* Product: '<S14>/Divide' incorporates:
     *  Constant: '<S14>/Constant'
     */
    FOC_SCF_B->Divide_d = FOC_SCF_P.Constant_Value / FOC_SCF_B->Add1_o;

    /* Product: '<S14>/IqRefRaw_PSM' */
    FOC_SCF_B->IqRefRaw_PSM = FOC_SCF_B->Divide_d * FOC_SCF_B->Gain_e;

    /* MultiPortSwitch: '<S6>/Multiport Switch' */
    FOC_SCF_B->Iq_Ref_raw = FOC_SCF_B->IqRefRaw_PSM;
    break;

   case 3:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    FOC_SCF_B->Iq_Ref_raw = FOC_SCF_P.IqRefZero_Value;
    break;

   case 4:
    /* MultiPortSwitch: '<S6>/Multiport Switch' */
    FOC_SCF_B->Iq_Ref_raw = FOC_SCF_B->I_q_Ref_MTPC;
    break;

   case 5:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    FOC_SCF_B->Iq_Ref_raw = FOC_SCF_P.IqRefZero_Value;
    break;

   default:
    /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
     *  Constant: '<S6>/IqRefZero'
     */
    FOC_SCF_B->Iq_Ref_raw = FOC_SCF_P.IqRefZero_Value;
    break;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch' */

  /* MultiPortSwitch: '<S6>/Multiport Switch1' */
  if ((int32_T)FOC_SCF_B->Bias_h == 1) {
    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Constant: '<S6>/zero_Current'
     */
    FOC_SCF_B->MultiportSwitch1 = FOC_SCF_P.zero_Current_Value_l;
  } else {
    /* MultiPortSwitch: '<S6>/Multiport Switch1' */
    FOC_SCF_B->MultiportSwitch1 = FOC_SCF_B->Iq_Ref_raw;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch1' */

  /* UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_B->Yk1 = FOC_SCF_DW->DelayInput2_DSTATE;

  /* Sum: '<S18>/Difference Inputs1'
   *
   * Block description for '<S18>/Difference Inputs1':
   *
   *  Add in CPU
   */
  FOC_SCF_B->UkYk1 = FOC_SCF_B->MultiportSwitch1 - FOC_SCF_B->Yk1;

  /* RelationalOperator: '<S19>/LowerRelop1' */
  FOC_SCF_B->LowerRelop1_j = (FOC_SCF_B->UkYk1 > FOC_SCF_B->deltariselimit);

  /* Product: '<S18>/delta fall limit' incorporates:
   *  Constant: '<S17>/Constant7'
   *  Constant: '<S18>/Constant6'
   */
  FOC_SCF_B->deltafalllimit = FOC_SCF_P.FOC_LIMIT_Idq_Ref_SlewRate_Down *
    FOC_SCF_P.Constant6_Value_f;

  /* RelationalOperator: '<S19>/UpperRelop' */
  FOC_SCF_B->UpperRelop_o = (FOC_SCF_B->UkYk1 < FOC_SCF_B->deltafalllimit);

  /* Switch: '<S19>/Switch' */
  if (FOC_SCF_B->UpperRelop_o) {
    /* Switch: '<S19>/Switch' */
    FOC_SCF_B->Switch = FOC_SCF_B->deltafalllimit;
  } else {
    /* Switch: '<S19>/Switch' */
    FOC_SCF_B->Switch = FOC_SCF_B->UkYk1;
  }

  /* End of Switch: '<S19>/Switch' */

  /* Switch: '<S19>/Switch2' */
  if (FOC_SCF_B->LowerRelop1_j) {
    /* Switch: '<S19>/Switch2' */
    FOC_SCF_B->Switch2 = FOC_SCF_B->deltariselimit;
  } else {
    /* Switch: '<S19>/Switch2' */
    FOC_SCF_B->Switch2 = FOC_SCF_B->Switch;
  }

  /* End of Switch: '<S19>/Switch2' */

  /* Sum: '<S18>/Difference Inputs2'
   *
   * Block description for '<S18>/Difference Inputs2':
   *
   *  Add in CPU
   */
  FOC_SCF_B->DifferenceInputs2 = FOC_SCF_B->Switch2 + FOC_SCF_B->Yk1;

  /* Switch: '<S17>/Switch2' incorporates:
   *  Constant: '<S17>/Constant5'
   */
  if (FOC_SCF_P.FOC_SELECT_Idq_Ref_Ramp > FOC_SCF_P.Switch2_Threshold_n) {
    /* Switch: '<S17>/Switch2' */
    FOC_SCF_B->Switch2_i = (real32_T)FOC_SCF_B->DifferenceInputs2;
  } else {
    /* Switch: '<S17>/Switch2' */
    FOC_SCF_B->Switch2_i = (real32_T)FOC_SCF_B->MultiportSwitch1;
  }

  /* End of Switch: '<S17>/Switch2' */

  /* Product: '<S15>/Product' incorporates:
   *  Constant: '<S15>/Constant'
   */
  FOC_SCF_B->Product = FOC_SCF_P.FOC_LIMIT_I_PHASE_PEAK_MAX *
    FOC_SCF_P.FOC_LIMIT_I_PHASE_PEAK_MAX;

  /* Product: '<S15>/Product1' */
  FOC_SCF_B->Product1_d = FOC_SCF_B->Switch2_ae * FOC_SCF_B->Switch2_ae;

  /* Sum: '<S15>/Subtract1' */
  FOC_SCF_B->Subtract1 = FOC_SCF_B->Product - FOC_SCF_B->Product1_d;

  /* Sqrt: '<S15>/Sqrt' */
  FOC_SCF_B->Sqrt = sqrtf(FOC_SCF_B->Subtract1);

  /* MinMax: '<S15>/mcrPsiRef1' */
  u0 = fminf(FOC_SCF_B->Switch2_i, FOC_SCF_B->Sqrt);

  /* MinMax: '<S15>/mcrPsiRef1' */
  FOC_SCF_B->mcrPsiRef1 = u0;

  /* Gain: '<S15>/PsiReduceGain1' */
  FOC_SCF_B->PsiReduceGain1 = FOC_SCF_P.PsiReduceGain1_Gain * FOC_SCF_B->Sqrt;

  /* MinMax: '<S15>/MinMax1' */
  u0 = fmaxf(FOC_SCF_B->mcrPsiRef1, FOC_SCF_B->PsiReduceGain1);

  /* MinMax: '<S15>/MinMax1' */
  FOC_SCF_B->I_q_Ref_limited = u0;

  /* SignalConversion generated from: '<S1>/Bus Creator' */
  FOC_SCF_B->I_dq_Ref[0] = FOC_SCF_B->Switch2_ae;
  FOC_SCF_B->I_dq_Ref[1] = FOC_SCF_B->I_q_Ref_limited;

  /* MultiPortSwitch: '<S4>/Selectphicalc1' incorporates:
   *  Constant: '<S4>/Constant4'
   */
  switch (FOC_SCF_P.FOC_SELECT_TorqEstMdl) {
   case 0:
    /* MultiPortSwitch: '<S4>/Selectphicalc1' incorporates:
     *  Constant: '<S4>/Constant'
     */
    FOC_SCF_B->Selectphicalc1 = FOC_SCF_P.Constant_Value_n;
    break;

   case 1:
    /* Product: '<S31>/Product3' incorporates:
     *  Constant: '<S31>/FOC_Psi_PM'
     *  Inport: '<Root>/bus_FCF'
     */
    FOC_SCF_B->Product3 = FOC_SCF_U->bus_FCF.I_dq_Act[5] * FOC_SCF_P.FOC_Psi_PM;

    /* Sum: '<S31>/Sum' incorporates:
     *  Constant: '<S31>/FOC_L_sd'
     *  Constant: '<S31>/FOC_L_sq'
     */
    FOC_SCF_B->Sum_a = FOC_SCF_P.FOC_L_sd - FOC_SCF_P.FOC_L_sq;

    /* Product: '<S31>/product_1' incorporates:
     *  Inport: '<Root>/bus_FCF'
     */
    FOC_SCF_B->product_1 = FOC_SCF_B->Sum_a * FOC_SCF_U->bus_FCF.I_dq_Act[4] *
      FOC_SCF_U->bus_FCF.I_dq_Act[5];

    /* Sum: '<S31>/add3' */
    FOC_SCF_B->add3 = FOC_SCF_B->product_1 + FOC_SCF_B->Product3;

    /* Product: '<S31>/Product2' incorporates:
     *  Constant: '<S31>/FOC_Psi_PM'
     *  Inport: '<Root>/bus_FCF'
     */
    FOC_SCF_B->Product2 = FOC_SCF_U->bus_FCF.I_dq_Act[3] * FOC_SCF_P.FOC_Psi_PM;

    /* Product: '<S31>/product_2' incorporates:
     *  Inport: '<Root>/bus_FCF'
     */
    FOC_SCF_B->product_2 = FOC_SCF_B->Sum_a * FOC_SCF_U->bus_FCF.I_dq_Act[2] *
      FOC_SCF_U->bus_FCF.I_dq_Act[3];

    /* Sum: '<S31>/add2' */
    FOC_SCF_B->add2 = FOC_SCF_B->product_2 + FOC_SCF_B->Product2;

    /* Product: '<S31>/Product1' incorporates:
     *  Constant: '<S31>/FOC_Psi_PM'
     *  Inport: '<Root>/bus_FCF'
     */
    FOC_SCF_B->Product1_m = FOC_SCF_U->bus_FCF.I_dq_Act[1] *
      FOC_SCF_P.FOC_Psi_PM;

    /* Product: '<S31>/product' incorporates:
     *  Inport: '<Root>/bus_FCF'
     */
    FOC_SCF_B->product = FOC_SCF_B->Sum_a * FOC_SCF_U->bus_FCF.I_dq_Act[0] *
      FOC_SCF_U->bus_FCF.I_dq_Act[1];

    /* Sum: '<S31>/add1' */
    FOC_SCF_B->add1 = FOC_SCF_B->product + FOC_SCF_B->Product1_m;

    /* Sum: '<S31>/Add' */
    FOC_SCF_B->Add = (FOC_SCF_B->add1 + FOC_SCF_B->add2) + FOC_SCF_B->add3;

    /* Gain: '<S31>/3*Z_p//2' */
    FOC_SCF_B->uZ_p2 = FOC_SCF_P.uZ_p2_Gain * FOC_SCF_B->Add;

    /* MultiPortSwitch: '<S4>/Selectphicalc1' */
    FOC_SCF_B->Selectphicalc1 = FOC_SCF_B->uZ_p2;
    break;

   case 2:
    /* MultiPortSwitch: '<S4>/Selectphicalc1' */
    FOC_SCF_B->Selectphicalc1 = 0.0F;
    break;

   default:
    /* MultiPortSwitch: '<S4>/Selectphicalc1' */
    FOC_SCF_B->Selectphicalc1 = 0.0F;
    break;
  }

  /* End of MultiPortSwitch: '<S4>/Selectphicalc1' */

  /* Gain: '<S1>/[1//s] => [rpm]' */
  FOC_SCF_B->n_Act = FOC_SCF_P.usrpm_Gain * FOC_SCF_U->bus_FCF.w_el;

  /* BusCreator: '<S1>/Bus Creator' incorporates:
   *  Outport: '<Root>/bus_SCF'
   */
  FOC_SCF_Y->bus_SCF.I_dq_Ref[0] = FOC_SCF_B->I_dq_Ref[0];
  FOC_SCF_Y->bus_SCF.I_dq_Ref[1] = FOC_SCF_B->I_dq_Ref[1];
  FOC_SCF_Y->bus_SCF.TorqueEst = FOC_SCF_B->Selectphicalc1;
  FOC_SCF_Y->bus_SCF.TorqueRefDerated = FOC_SCF_B->TorqCtrlProduct;
  FOC_SCF_Y->bus_SCF.n_Act = FOC_SCF_B->n_Act;

  /* Sum: '<S15>/Subtract' */
  FOC_SCF_B->FOC_IqDiff = FOC_SCF_B->Switch2_i - FOC_SCF_B->I_q_Ref_limited;

  /* UnitDelay: '<S15>/Unit Delay' */
  FOC_SCF_B->UnitDelay_i = FOC_SCF_DW->UnitDelay_DSTATE_m;

  /* Gain: '<S8>/Gain1' */
  FOC_SCF_B->FOC_MotTemp_PSM = FOC_SCF_P.Gain1_Gain_i *
    FOC_SCF_U->bus_SMF.MaxMotTemp;

  /* RelationalOperator: '<S26>/Compare' incorporates:
   *  Constant: '<S26>/Constant'
   */
  FOC_SCF_B->Compare = (uint8_T)(FOC_SCF_U->bus_SMF.MaxMotTemp <=
    FOC_SCF_P.FOC_LIMIT_Torque_Derating_Temp);

  /* Sum: '<S23>/Sum' incorporates:
   *  Constant: '<S23>/Constant'
   */
  FOC_SCF_B->Sum = FOC_SCF_P.Constant_Value_gz - (real32_T)FOC_SCF_B->Compare;

  /* Product: '<S23>/Product' incorporates:
   *  Constant: '<S23>/Constant1'
   */
  FOC_SCF_B->Product_c = FOC_SCF_B->Sum *
    FOC_SCF_P.FOC_Torque_Derating_Temp_Gain;

  /* Sum: '<S23>/Sum1' */
  FOC_SCF_B->Sum1_i = FOC_SCF_B->Product_c + FOC_SCF_B->Saturation;

  /* UnitDelay: '<S9>/UnitDelay' */
  FOC_SCF_B->UnitDelay_o = FOC_SCF_DW->UnitDelay_DSTATE_j;

  /* Gain: '<S9>/FOC_IQ_DIFF_REDUC_GAIN' */
  FOC_SCF_B->FOC_IQ_DIFF_REDUC_GAIN = FOC_SCF_P.FOC_IQ_DIFF_REDUC_GAIN *
    FOC_SCF_B->UnitDelay_o;

  /* Gain: '<S9>/FOC_TORQ_REDUC_GAIN' */
  FOC_SCF_B->FOC_TORQ_REDUC_GAIN = FOC_SCF_P.FOC_TORQ_REDUC_GAIN *
    FOC_SCF_B->Sum1;

  /* Gain: '<S9>/Gain' */
  FOC_SCF_B->Torq_Ref_PSM = FOC_SCF_P.Gain_Gain_j * FOC_SCF_B->TorqCtrlProduct;

  /* Gain: '<S9>/Gain1' */
  FOC_SCF_B->Torq_Ref_IqDiff = FOC_SCF_P.Gain1_Gain_c *
    FOC_SCF_B->FOC_IQ_DIFF_REDUC_GAIN;

  /* Gain: '<S9>/Gain2' */
  FOC_SCF_B->Torq_Ref_PGAIN = FOC_SCF_P.Gain2_Gain *
    FOC_SCF_B->FOC_TORQ_REDUC_PGAIN;

  /* Switch: '<S9>/TorqCtrlSwitch1' */
  if (FOC_SCF_B->Switch_l >= FOC_SCF_P.TorqCtrlSwitch1_Threshold) {
    /* Gain: '<S9>/TorqCtrlMinusOne' */
    FOC_SCF_B->TorqCtrlMinusOne = FOC_SCF_P.TorqCtrlMinusOne_Gain *
      FOC_SCF_B->FOC_IQ_DIFF_REDUC_GAIN;

    /* Switch: '<S9>/TorqCtrlSwitch1' */
    FOC_SCF_B->TorqCtrlSwitch1 = FOC_SCF_B->TorqCtrlMinusOne;
  } else {
    /* Switch: '<S9>/TorqCtrlSwitch1' */
    FOC_SCF_B->TorqCtrlSwitch1 = FOC_SCF_B->FOC_IQ_DIFF_REDUC_GAIN;
  }

  /* End of Switch: '<S9>/TorqCtrlSwitch1' */

  /* Switch: '<S9>/TorqCtrlSwitch3' */
  if (FOC_SCF_B->TorqCtrlSwitch1 >= FOC_SCF_P.TorqCtrlSwitch3_Threshold) {
    /* Switch: '<S9>/TorqCtrlSwitch3' */
    FOC_SCF_B->TorqCtrlSwitch3 = FOC_SCF_B->FOC_TORQ_REDUC_GAIN;
  } else {
    /* MinMax: '<S9>/TorqCtrlMin2' */
    u0 = fminf(FOC_SCF_B->TorqCtrlSwitch1, FOC_SCF_B->FOC_TORQ_REDUC_GAIN);

    /* MinMax: '<S9>/TorqCtrlMin2' */
    FOC_SCF_B->TorqCtrlMin2 = u0;

    /* Switch: '<S9>/TorqCtrlSwitch3' */
    FOC_SCF_B->TorqCtrlSwitch3 = FOC_SCF_B->TorqCtrlMin2;
  }

  /* End of Switch: '<S9>/TorqCtrlSwitch3' */

  /* Sum: '<S9>/TorqCtrlSum4' */
  FOC_SCF_B->TorqCtrlSum4 = FOC_SCF_B->Saturation_d -
    FOC_SCF_B->FOC_TORQ_REDUC_PGAIN;

  /* Sum: '<S9>/TorqCtrlSum1' */
  FOC_SCF_B->TorqCtrlSum1 = FOC_SCF_B->TorqCtrlSwitch3 + FOC_SCF_B->TorqCtrlSum4;

  /* Sum: '<S4>/Subtract2' */
  u0 = -0.0F;
  for (i = 0; i < 6; i++) {
    /* Product: '<S4>/Product' incorporates:
     *  Inport: '<Root>/bus_FCF'
     */
    u1 = FOC_SCF_U->bus_FCF.I_dq_Act[i];

    /* Product: '<S4>/Product' */
    u1 *= u1;
    FOC_SCF_B->Product_h[i] = u1;

    /* Sum: '<S4>/Subtract2' */
    u0 += u1;
  }

  /* Sum: '<S4>/Subtract2' */
  FOC_SCF_B->Subtract2 = u0;

  /* Sqrt: '<S4>/Sqrt' */
  FOC_SCF_B->Sqrt_b = sqrtf(FOC_SCF_B->Subtract2);

  /* Gain: '<S4>/I_ph_peak' */
  FOC_SCF_B->I_ph_peak_Act = FOC_SCF_P.I_ph_peak_Gain * FOC_SCF_B->Sqrt_b;

  /* Gain: '<S4>/I_ph_rms' */
  FOC_SCF_B->I_ph_rms_Act = FOC_SCF_P.I_ph_rms_Gain * FOC_SCF_B->Sqrt_b;

  /* Gain: '<S4>/TorqEst_Nm' */
  FOC_SCF_B->M_est = FOC_SCF_P.TorqEst_Nm_Gain * FOC_SCF_B->Selectphicalc1;

  /* UnitDelay: '<S1>/SCF_Cnt' */
  FOC_SCF_B->SCF_Cnt = FOC_SCF_DW->SCF_Cnt_DSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Counter_Start'
   */
  FOC_SCF_B->Sum_o = FOC_SCF_P.Counter_Start_Value + FOC_SCF_B->SCF_Cnt;

  /* Update for UnitDelay: '<S23>/Unit Delay' */
  FOC_SCF_DW->UnitDelay_DSTATE = FOC_SCF_B->Sum1_i;

  /* Update for UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_DW->DelayInput2_DSTATE_i = FOC_SCF_B->DifferenceInputs2_n;

  /* Update for UnitDelay: '<S9>/TorqCtrlDelay' */
  FOC_SCF_DW->TorqCtrlDelay_DSTATE = FOC_SCF_B->TorqCtrlSum1;

  /* Update for UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_DW->DelayInput2_DSTATE_h = FOC_SCF_B->DifferenceInputs2_f;

  /* Update for UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_DW->DelayInput2_DSTATE = FOC_SCF_B->DifferenceInputs2;

  /* Update for UnitDelay: '<S15>/Unit Delay' */
  FOC_SCF_DW->UnitDelay_DSTATE_m = FOC_SCF_B->FOC_IqDiff;

  /* Update for UnitDelay: '<S9>/UnitDelay' */
  FOC_SCF_DW->UnitDelay_DSTATE_j = FOC_SCF_B->UnitDelay_i;

  /* Update for UnitDelay: '<S1>/SCF_Cnt' */
  FOC_SCF_DW->SCF_Cnt_DSTATE = FOC_SCF_B->Sum_o;

  /* End of Outputs for SubSystem: '<Root>/FOC_SCF' */
}

/* Model initialize function */
void FOC_SCF_initialize(RT_MODEL_FOC_SCF_T *const FOC_SCF_M)
{
  B_FOC_SCF_T *FOC_SCF_B = FOC_SCF_M->blockIO;
  DW_FOC_SCF_T *FOC_SCF_DW = FOC_SCF_M->dwork;
  ExtU_FOC_SCF_T *FOC_SCF_U = (ExtU_FOC_SCF_T *) FOC_SCF_M->inputs;
  ExtY_FOC_SCF_T *FOC_SCF_Y = (ExtY_FOC_SCF_T *) FOC_SCF_M->outputs;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) FOC_SCF_B), 0,
                sizeof(B_FOC_SCF_T));

  /* states (dwork) */
  (void) memset((void *)FOC_SCF_DW, 0,
                sizeof(DW_FOC_SCF_T));

  /* external inputs */
  (void)memset(FOC_SCF_U, 0, sizeof(ExtU_FOC_SCF_T));

  /* external outputs */
  FOC_SCF_Y->bus_SCF = FOC_SCF_rtZbus_SCF_t;

  /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_SCF' */
  /* InitializeConditions for UnitDelay: '<S23>/Unit Delay' */
  FOC_SCF_DW->UnitDelay_DSTATE = FOC_SCF_P.UnitDelay_InitialCondition_e;

  /* InitializeConditions for UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_DW->DelayInput2_DSTATE_i = FOC_SCF_P.DelayInput2_InitialCondition_l;

  /* InitializeConditions for UnitDelay: '<S9>/TorqCtrlDelay' */
  FOC_SCF_DW->TorqCtrlDelay_DSTATE = FOC_SCF_P.TorqCtrlDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S12>/Delay Input2'
   *
   * Block description for '<S12>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_DW->DelayInput2_DSTATE_h = FOC_SCF_P.DelayInput2_InitialCondition_g;

  /* InitializeConditions for UnitDelay: '<S18>/Delay Input2'
   *
   * Block description for '<S18>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_DW->DelayInput2_DSTATE = FOC_SCF_P.DelayInput2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S15>/Unit Delay' */
  FOC_SCF_DW->UnitDelay_DSTATE_m = FOC_SCF_P.UnitDelay_InitialCondition_l;

  /* InitializeConditions for UnitDelay: '<S9>/UnitDelay' */
  FOC_SCF_DW->UnitDelay_DSTATE_j = FOC_SCF_P.UnitDelay_InitialCondition_a;

  /* InitializeConditions for UnitDelay: '<S1>/SCF_Cnt' */
  FOC_SCF_DW->SCF_Cnt_DSTATE = FOC_SCF_P.SCF_Cnt_InitialCondition;

  /* SystemInitialize for Enabled SubSystem: '<S1>/SPEED_CONTROLLER' */
  /* InitializeConditions for UnitDelay: '<S29>/Delay Input2'
   *
   * Block description for '<S29>/Delay Input2':
   *
   *  Store in Global RAM
   */
  FOC_SCF_DW->DelayInput2_DSTATE_m = FOC_SCF_P.FOC_LIMIT_n_Ref_SlewRate_InitVal;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
  FOC_SCF_DW->UnitDelay_DSTATE_mg = FOC_SCF_P.UnitDelay_InitialCondition;

  /* SystemInitialize for Switch: '<S3>/Switch1' incorporates:
   *  Outport: '<S3>/TorqReq [Nm]'
   */
  FOC_SCF_B->M_Ref_SpeedCtrl = FOC_SCF_P.TorqReqNm_Y0;

  /* End of SystemInitialize for SubSystem: '<S1>/SPEED_CONTROLLER' */
  /* End of SystemInitialize for SubSystem: '<Root>/FOC_SCF' */
}

/* Model terminate function */
void FOC_SCF_terminate(RT_MODEL_FOC_SCF_T *const FOC_SCF_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(FOC_SCF_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
