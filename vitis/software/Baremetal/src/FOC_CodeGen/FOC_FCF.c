/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF.c
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.21
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Jan 16 11:31:17 2026
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
  real32_T Sum1_lz;
  real32_T TrafoMatrixuvwalphabeta;
  real32_T tmp_0;
  boolean_T tmp_1;
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

  /* RelationalOperator: '<S42>/Compare' incorporates:
   *  Constant: '<S42>/Constant'
   */
  FOC_FCF_B->Compare_b = (FOC_FCF_B->U_DC_fcf <
    FOC_FCF_P.FOC_LIMIT_Undervoltage_U_DC);

  /* Logic: '<S1>/Logical Operator1' incorporates:
   *  Constant: '<S1>/Enable'
   */
  FOC_FCF_B->LogicalOperator1 = ((FOC_FCF_P.FOC_Enable != 0.0F) &&
    (FOC_FCF_U->FOC_Enable != 0.0F));

  /* Logic: '<S9>/Logical Operator2' */
  FOC_FCF_B->LogicalOperator2 = (FOC_FCF_B->Compare_b &&
    FOC_FCF_B->LogicalOperator1);

  /* MultiPortSwitch: '<S9>/Selectphicalc3' incorporates:
   *  Constant: '<S9>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Undervoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S9>/Selectphicalc3' incorporates:
     *  Constant: '<S9>/Constant2'
     */
    FOC_FCF_B->Selectphicalc3 = FOC_FCF_P.Constant2_Value_j;
  } else {
    /* Logic: '<S9>/Logical Operator1' */
    FOC_FCF_B->LogicalOperator1_o = !FOC_FCF_B->LogicalOperator1;

    /* MultiPortSwitch: '<S9>/Selectphicalc3' */
    FOC_FCF_B->Selectphicalc3 = FOC_FCF_B->LogicalOperator1_o;
  }

  /* End of MultiPortSwitch: '<S9>/Selectphicalc3' */

  /* Memory: '<S45>/Memory' */
  FOC_FCF_B->Memory = FOC_FCF_DW->Memory_PreviousInput;

  /* CombinatorialLogic: '<S45>/Logic' */
  tmp_1 = FOC_FCF_B->LogicalOperator2;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc3;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic[0U] = FOC_FCF_P.Logic_table[(uint32_T)i];
  FOC_FCF_B->Logic[1U] = FOC_FCF_P.Logic_table[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S9>/Selectphicalc1' incorporates:
   *  Constant: '<S9>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Undervoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S9>/Selectphicalc1' incorporates:
     *  Constant: '<S9>/Constant3'
     */
    FOC_FCF_B->Selectphicalc1 = FOC_FCF_P.Constant3_Value_i;
  } else {
    /* MultiPortSwitch: '<S9>/Selectphicalc1' */
    FOC_FCF_B->Selectphicalc1 = FOC_FCF_B->Logic[1];
  }

  /* End of MultiPortSwitch: '<S9>/Selectphicalc1' */

  /* RelationalOperator: '<S43>/Compare' incorporates:
   *  Constant: '<S43>/Constant'
   */
  FOC_FCF_B->Compare_br = (FOC_FCF_B->U_DC_fcf >
    FOC_FCF_P.FOC_LIMIT_Overvoltage_U_DC);

  /* RelationalOperator: '<S47>/Compare' incorporates:
   *  Constant: '<S47>/Constant'
   *  Constant: '<S9>/Reset_OV_Error'
   */
  FOC_FCF_B->Compare_n = (FOC_FCF_P.FOC_RESET_OV_Error >
    FOC_FCF_P.Constant_Value_o);

  /* UnitDelay: '<S44>/Delay Input1'
   *
   * Block description for '<S44>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1 = FOC_FCF_DW->DelayInput1_DSTATE;

  /* MultiPortSwitch: '<S9>/Selectphicalc4' incorporates:
   *  Constant: '<S9>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overvoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S9>/Selectphicalc4' incorporates:
     *  Constant: '<S9>/Constant4'
     */
    FOC_FCF_B->Selectphicalc4 = FOC_FCF_P.Constant4_Value_b;
  } else {
    /* RelationalOperator: '<S44>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator = ((int32_T)FOC_FCF_B->Compare_n >
      (int32_T)FOC_FCF_B->Uk1);

    /* MultiPortSwitch: '<S9>/Selectphicalc4' */
    FOC_FCF_B->Selectphicalc4 = FOC_FCF_B->FixPtRelationalOperator;
  }

  /* End of MultiPortSwitch: '<S9>/Selectphicalc4' */

  /* Memory: '<S46>/Memory' */
  FOC_FCF_B->Memory_k = FOC_FCF_DW->Memory_PreviousInput_o;

  /* CombinatorialLogic: '<S46>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_br;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc4;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_k;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_g[0U] = FOC_FCF_P.Logic_table_m[(uint32_T)i];
  FOC_FCF_B->Logic_g[1U] = FOC_FCF_P.Logic_table_m[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S9>/Selectphicalc2' incorporates:
   *  Constant: '<S9>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overvoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S9>/Selectphicalc2' incorporates:
     *  Constant: '<S9>/Constant1'
     */
    FOC_FCF_B->Selectphicalc2_m = FOC_FCF_P.Constant1_Value_j;
  } else {
    /* MultiPortSwitch: '<S9>/Selectphicalc2' */
    FOC_FCF_B->Selectphicalc2_m = FOC_FCF_B->Logic_g[1];
  }

  /* End of MultiPortSwitch: '<S9>/Selectphicalc2' */

  /* Logic: '<S9>/Logical Operator' */
  FOC_FCF_B->LogicalOperator = (FOC_FCF_B->Selectphicalc1 &&
    FOC_FCF_B->Selectphicalc2_m);
  for (i = 0; i < 9; i++) {
    /* Abs: '<S8>/Abs' */
    FOC_FCF_B->Abs[i] = fabsf(FOC_FCF_U->I_phA[i]);
  }

  /* MinMax: '<S8>/MinMax' incorporates:
   *  Abs: '<S8>/Abs'
   */
  tmp_0 = FOC_FCF_B->Abs[0];
  for (i = 0; i < 8; i++) {
    tmp_0 = fmaxf(tmp_0, FOC_FCF_B->Abs[i + 1]);
  }

  /* MinMax: '<S8>/MinMax' */
  FOC_FCF_B->MinMax = tmp_0;

  /* RelationalOperator: '<S38>/Compare' incorporates:
   *  Constant: '<S38>/Constant'
   */
  FOC_FCF_B->Compare_a = (FOC_FCF_B->MinMax >=
    FOC_FCF_P.FOC_LIMIT_Overcurrent_I_uvw);

  /* RelationalOperator: '<S41>/Compare' incorporates:
   *  Constant: '<S41>/Constant'
   *  Constant: '<S8>/Reset_OC_Error'
   */
  FOC_FCF_B->Compare_l = (FOC_FCF_P.FOC_RESET_OC_Error >
    FOC_FCF_P.Constant_Value);

  /* UnitDelay: '<S39>/Delay Input1'
   *
   * Block description for '<S39>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1_k = FOC_FCF_DW->DelayInput1_DSTATE_c;

  /* MultiPortSwitch: '<S8>/Selectphicalc2' incorporates:
   *  Constant: '<S8>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overcurrent_I_uvw == 0) {
    /* MultiPortSwitch: '<S8>/Selectphicalc2' incorporates:
     *  Constant: '<S8>/Constant1'
     */
    FOC_FCF_B->Selectphicalc2_i = FOC_FCF_P.Constant1_Value_gm;
  } else {
    /* RelationalOperator: '<S39>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator_e = ((int32_T)FOC_FCF_B->Compare_l >
      (int32_T)FOC_FCF_B->Uk1_k);

    /* MultiPortSwitch: '<S8>/Selectphicalc2' */
    FOC_FCF_B->Selectphicalc2_i = FOC_FCF_B->FixPtRelationalOperator_e;
  }

  /* End of MultiPortSwitch: '<S8>/Selectphicalc2' */

  /* Memory: '<S40>/Memory' */
  FOC_FCF_B->Memory_p = FOC_FCF_DW->Memory_PreviousInput_p;

  /* CombinatorialLogic: '<S40>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_a;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_i;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_p;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_gq[0U] = FOC_FCF_P.Logic_table_f[(uint32_T)i];
  FOC_FCF_B->Logic_gq[1U] = FOC_FCF_P.Logic_table_f[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S8>/Selectphicalc1' incorporates:
   *  Constant: '<S8>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overcurrent_I_uvw == 0) {
    /* MultiPortSwitch: '<S8>/Selectphicalc1' incorporates:
     *  Constant: '<S8>/Constant2'
     */
    FOC_FCF_B->Selectphicalc1_j = FOC_FCF_P.Constant2_Value_o;
  } else {
    /* MultiPortSwitch: '<S8>/Selectphicalc1' */
    FOC_FCF_B->Selectphicalc1_j = FOC_FCF_B->Logic_gq[1];
  }

  /* End of MultiPortSwitch: '<S8>/Selectphicalc1' */

  /* Logic: '<S1>/Logical Operator' */
  FOC_FCF_B->LogicalOperator_n = (FOC_FCF_B->LogicalOperator &&
    FOC_FCF_B->LogicalOperator1 && FOC_FCF_B->Selectphicalc1_j);

  /* Switch: '<S1>/Switch' */
  if (FOC_FCF_B->LogicalOperator_n) {
    /* Switch: '<S1>/Switch' */
    FOC_FCF_B->FOC_Mode_after_checks = FOC_FCF_B->ModeSwitch;
  } else {
    /* Switch: '<S1>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    FOC_FCF_B->FOC_Mode_after_checks = FOC_FCF_P.Constant1_Value;
  }

  /* End of Switch: '<S1>/Switch' */

  /* DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn' */
  tmp_0 = FOC_FCF_P.DiscreteTransferFcn_NumCoef *
    FOC_FCF_DW->DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn' */
  FOC_FCF_B->DiscreteTransferFcn = tmp_0;

  /* Gain: '<S11>/f_2_w_el' incorporates:
   *  Constant: '<S11>/Uf_w_el'
   */
  FOC_FCF_B->f_2_w_el = FOC_FCF_P.f_2_w_el_Gain * FOC_FCF_P.FOC_Uf_f_el;

  /* Product: '<S48>/Product' incorporates:
   *  Constant: '<S48>/FOC_T_fast'
   */
  FOC_FCF_B->Product = FOC_FCF_B->f_2_w_el * FOC_FCF_P.FOC_T_fast_Value;

  /* UnitDelay: '<S48>/Unit Delay' */
  FOC_FCF_B->UnitDelay = FOC_FCF_DW->UnitDelay_DSTATE;

  /* Sum: '<S48>/Add' */
  FOC_FCF_B->Add = FOC_FCF_B->Product + FOC_FCF_B->UnitDelay;

  /* Gain: '<S22>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[0];
  I_phA = FOC_FCF_U->I_phA[1];
  I_phA_0 = FOC_FCF_U->I_phA[2];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S22>/TrafoMatrix uvw->alphabeta' */
    TrafoMatrixuvwalphabeta = FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i_0] *
      tmp_0;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i_0 + 2] *
      I_phA;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i_0 + 4] *
      I_phA_0;
    FOC_FCF_B->TrafoMatrixuvwalphabeta[i_0] = TrafoMatrixuvwalphabeta;
  }

  /* RelationalOperator: '<S6>/Compare' incorporates:
   *  Constant: '<S6>/Constant'
   */
  FOC_FCF_B->Compare_lu = (FOC_FCF_B->ModeSwitch == FOC_FCF_P.enumState_FOC_IF);

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

  /* UnitDelay: '<S16>/Unit Delay1' */
  FOC_FCF_B->w_el = FOC_FCF_DW->UnitDelay1_DSTATE;

  /* Gain: '<S13>/DeadTimeCompensation' */
  FOC_FCF_B->DeadTimeCompensation = FOC_FCF_P.FOC_PhiSensorTdead *
    FOC_FCF_B->w_el;

  /* Sum: '<S13>/Sum3' */
  FOC_FCF_B->Sum3 = FOC_FCF_B->Sum1 + FOC_FCF_B->DeadTimeCompensation;

  /* UnitDelay: '<S15>/Unit Delay' */
  FOC_FCF_B->UnitDelay_l = FOC_FCF_DW->UnitDelay_DSTATE_h;

  /* Sum: '<S15>/Sum' */
  FOC_FCF_B->Sum = FOC_FCF_B->Sum3 - FOC_FCF_B->UnitDelay_l;

  /* RelationalOperator: '<S15>/Sprung?' incorporates:
   *  Constant: '<S15>/Constant3'
   */
  FOC_FCF_B->Sprung = (FOC_FCF_B->Sum < FOC_FCF_P.Constant3_Value);

  /* Switch: '<S15>/Switch' */
  if (FOC_FCF_B->Sprung) {
    /* Switch: '<S15>/Switch' incorporates:
     *  Constant: '<S15>/Constant2'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant2_Value;
  } else {
    /* Switch: '<S15>/Switch' incorporates:
     *  Constant: '<S15>/Constant4'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant4_Value;
  }

  /* End of Switch: '<S15>/Switch' */

  /* RelationalOperator: '<S15>/Sprung?1' incorporates:
   *  Constant: '<S15>/Constant1'
   */
  FOC_FCF_B->Sprung1 = (FOC_FCF_B->Sum > FOC_FCF_P.Constant1_Value_ep);

  /* Switch: '<S15>/Switch1' */
  if (FOC_FCF_B->Sprung1) {
    /* Switch: '<S15>/Switch1' incorporates:
     *  Constant: '<S15>/Constant5'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant5_Value;
  } else {
    /* Switch: '<S15>/Switch1' incorporates:
     *  Constant: '<S15>/Constant6'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant6_Value;
  }

  /* End of Switch: '<S15>/Switch1' */

  /* Sum: '<S15>/Sum2' */
  FOC_FCF_B->Sum2 = FOC_FCF_B->Switch + FOC_FCF_B->Switch1;

  /* UnitDelay: '<S13>/Unit Delay3' */
  FOC_FCF_B->UnitDelay3 = FOC_FCF_DW->UnitDelay3_DSTATE;

  /* Sum: '<S13>/Sum7' */
  FOC_FCF_B->phi_el_observer = FOC_FCF_B->UnitDelay3 - FOC_FCF_B->Sum2;

  /* Product: '<S10>/Product' incorporates:
   *  Constant: '<S10>/FOC_T_fast'
   */
  FOC_FCF_B->Product_e = FOC_FCF_U->w_el_Ref_IfStarter *
    FOC_FCF_P.FOC_T_fast_Value_d;

  /* UnitDelay: '<S10>/Unit Delay' */
  FOC_FCF_B->UnitDelay_a = FOC_FCF_DW->UnitDelay_DSTATE_p;

  /* Sum: '<S10>/Add' */
  FOC_FCF_B->Add_m = FOC_FCF_B->Product_e + FOC_FCF_B->UnitDelay_a;

  /* Gain: '<S7>/f_2_w_el' incorporates:
   *  Constant: '<S7>/If_f_el'
   */
  FOC_FCF_B->f_2_w_el_b = FOC_FCF_P.f_2_w_el_Gain_j * FOC_FCF_P.FOC_If_f_el;

  /* Product: '<S37>/Product' incorporates:
   *  Constant: '<S37>/FOC_T_fast'
   */
  FOC_FCF_B->Product_h = FOC_FCF_B->f_2_w_el_b * FOC_FCF_P.FOC_T_fast_Value_f;

  /* UnitDelay: '<S37>/Unit Delay' */
  FOC_FCF_B->UnitDelay_j = FOC_FCF_DW->UnitDelay_DSTATE_f;

  /* Sum: '<S37>/Add' */
  FOC_FCF_B->Add_mp = FOC_FCF_B->Product_h + FOC_FCF_B->UnitDelay_j;

  /* MultiPortSwitch: '<S1>/Use_If_Mode' */
  if (!FOC_FCF_B->Compare_lu) {
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

      /* Switch: '<S14>/Switch1' */
      if (FOC_FCF_B->Selectphicalc2 > FOC_FCF_P.Switch1_Threshold) {
        /* Sum: '<S14>/Sum2' incorporates:
         *  Constant: '<S14>/Constant'
         */
        FOC_FCF_B->Sum2_l = FOC_FCF_B->Selectphicalc2 -
          FOC_FCF_P.Constant_Value_e;

        /* Switch: '<S14>/Switch1' */
        FOC_FCF_B->Switch1_d = FOC_FCF_B->Sum2_l;
      } else {
        /* Switch: '<S14>/Switch1' */
        FOC_FCF_B->Switch1_d = FOC_FCF_B->Selectphicalc2;
      }

      /* End of Switch: '<S14>/Switch1' */

      /* Switch: '<S14>/Switch2' */
      if (FOC_FCF_B->Switch1_d > FOC_FCF_P.Switch2_Threshold) {
        /* Switch: '<S14>/Switch2' */
        FOC_FCF_B->Switch2_f = FOC_FCF_B->Switch1_d;
      } else {
        /* Sum: '<S14>/Sum3' incorporates:
         *  Constant: '<S14>/Constant1'
         */
        FOC_FCF_B->Sum3_h = FOC_FCF_B->Switch1_d + FOC_FCF_P.Constant1_Value_g;

        /* Switch: '<S14>/Switch2' */
        FOC_FCF_B->Switch2_f = FOC_FCF_B->Sum3_h;
      }

      /* End of Switch: '<S14>/Switch2' */

      /* MultiPortSwitch: '<S1>/Use_If_Starter' */
      FOC_FCF_B->Use_If_Starter = FOC_FCF_B->Switch2_f;
    } else {
      /* MultiPortSwitch: '<S1>/Use_If_Starter' */
      FOC_FCF_B->Use_If_Starter = FOC_FCF_B->Add_m;
    }

    /* End of MultiPortSwitch: '<S1>/Use_If_Starter' */

    /* MultiPortSwitch: '<S1>/Use_If_Mode' */
    FOC_FCF_B->Use_If_Mode[0] = FOC_FCF_B->Use_If_Starter;
    FOC_FCF_B->Use_If_Mode[1] = FOC_FCF_B->w_el;
  } else {
    /* MultiPortSwitch: '<S1>/Use_If_Mode' */
    FOC_FCF_B->Use_If_Mode[0] = FOC_FCF_B->Add_mp;
    FOC_FCF_B->Use_If_Mode[1] = FOC_FCF_B->f_2_w_el_b;
  }

  /* End of MultiPortSwitch: '<S1>/Use_If_Mode' */

  /* Trigonometry: '<S22>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1 = cosf(FOC_FCF_B->Use_If_Mode[0]);

  /* Product: '<S22>/TrafoProd' */
  FOC_FCF_B->TrafoProd = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction1;

  /* Trigonometry: '<S22>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction = sinf(FOC_FCF_B->Use_If_Mode[0]);

  /* Product: '<S22>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3 = FOC_FCF_B->TrigonometricFunction *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Sum: '<S22>/I_d1_Act' */
  FOC_FCF_B->I_d1_Act = FOC_FCF_B->TrafoProd + FOC_FCF_B->TrafoProd3;

  /* Product: '<S22>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1 = FOC_FCF_B->TrigonometricFunction1 *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Product: '<S22>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2 = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction;

  /* Sum: '<S22>/I_q1_Act' */
  FOC_FCF_B->I_q1_Act = FOC_FCF_B->TrafoProd1 - FOC_FCF_B->TrafoProd2;

  /* SignalConversion generated from: '<S22>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0] = FOC_FCF_B->I_d1_Act;
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1] = FOC_FCF_B->I_q1_Act;

  /* Sum: '<S19>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S26>/KP*e[k]1' incorporates:
   *  Constant: '<S26>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S26>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[0] = FOC_FCF_DW->IntegDelay1_DSTATE[0];

  /* Sum: '<S19>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S26>/KP*e[k]1' incorporates:
   *  Constant: '<S26>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S26>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[1] = FOC_FCF_DW->IntegDelay1_DSTATE[1];

  /* Product: '<S26>/Product1' incorporates:
   *  Constant: '<S26>/FOC_KI'
   *  Constant: '<S26>/FOC_T_fast'
   */
  FOC_FCF_B->Product1 = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_n;

  /* Switch: '<S26>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Product: '<S26>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1[0] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[0] = tmp_0;

    /* Sum: '<S26>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1[0];
    FOC_FCF_B->IntSum1_p[0] = tmp_0;

    /* Switch: '<S26>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1[0] = tmp_0;

    /* Product: '<S26>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1[1] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[1] = tmp_0;

    /* Sum: '<S26>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1[1];
    FOC_FCF_B->IntSum1_p[1] = tmp_0;

    /* Switch: '<S26>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1[1] = tmp_0;
  } else {
    /* Switch: '<S26>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S26>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1[0] = FOC_FCF_P.Zero_Value;
    FOC_FCF_B->IntegEnaSwitch1[1] = FOC_FCF_P.Zero_Value;
  }

  /* End of Switch: '<S26>/IntegEnaSwitch1' */

  /* Gain: '<S23>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[3];
  I_phA = FOC_FCF_U->I_phA[4];
  I_phA_0 = FOC_FCF_U->I_phA[5];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S23>/TrafoMatrix uvw->alphabeta' */
    TrafoMatrixuvwalphabeta = FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i_0] *
      tmp_0;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i_0 + 2]
      * I_phA;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i_0 + 4]
      * I_phA_0;
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[i_0] = TrafoMatrixuvwalphabeta;
  }

  /* Sum: '<S5>/Sum1' incorporates:
   *  Constant: '<S5>/FOC_9ph_AngleShift'
   */
  FOC_FCF_B->Sum1_d = FOC_FCF_B->Use_If_Mode[0] + FOC_FCF_P.FOC_9ph_AngleShift;

  /* Trigonometry: '<S23>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_b = cosf(FOC_FCF_B->Sum1_d);

  /* Product: '<S23>/TrafoProd' */
  FOC_FCF_B->TrafoProd_a = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction1_b;

  /* Trigonometry: '<S23>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_l = sinf(FOC_FCF_B->Sum1_d);

  /* Product: '<S23>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3_i = FOC_FCF_B->TrigonometricFunction_l *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Sum: '<S23>/TrafoSum' */
  FOC_FCF_B->TrafoSum = FOC_FCF_B->TrafoProd_a + FOC_FCF_B->TrafoProd3_i;

  /* Product: '<S23>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1_b = FOC_FCF_B->TrigonometricFunction1_b *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Product: '<S23>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2_b = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction_l;

  /* Sum: '<S23>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1 = FOC_FCF_B->TrafoProd1_b - FOC_FCF_B->TrafoProd2_b;

  /* SignalConversion generated from: '<S23>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0] = FOC_FCF_B->TrafoSum;
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1] = FOC_FCF_B->TrafoSum1;

  /* Sum: '<S20>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S30>/KP*e[k]1' incorporates:
   *  Constant: '<S30>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S30>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[0] = FOC_FCF_DW->IntegDelay1_DSTATE_p[0];

  /* Sum: '<S20>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S30>/KP*e[k]1' incorporates:
   *  Constant: '<S30>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S30>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[1] = FOC_FCF_DW->IntegDelay1_DSTATE_p[1];

  /* Product: '<S30>/Product1' incorporates:
   *  Constant: '<S30>/FOC_KI'
   *  Constant: '<S30>/FOC_T_fast'
   */
  FOC_FCF_B->Product1_k = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_e;

  /* Switch: '<S30>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Product: '<S30>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[0] * FOC_FCF_B->Product1_k;
    FOC_FCF_B->Product2_b[0] = tmp_0;

    /* Sum: '<S30>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1_l[0];
    FOC_FCF_B->IntSum1_l[0] = tmp_0;

    /* Switch: '<S30>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_n[0] = tmp_0;

    /* Product: '<S30>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[1] * FOC_FCF_B->Product1_k;
    FOC_FCF_B->Product2_b[1] = tmp_0;

    /* Sum: '<S30>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1_l[1];
    FOC_FCF_B->IntSum1_l[1] = tmp_0;

    /* Switch: '<S30>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_n[1] = tmp_0;
  } else {
    /* Switch: '<S30>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S30>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1_n[0] = FOC_FCF_P.Zero_Value_o;
    FOC_FCF_B->IntegEnaSwitch1_n[1] = FOC_FCF_P.Zero_Value_o;
  }

  /* End of Switch: '<S30>/IntegEnaSwitch1' */

  /* Gain: '<S24>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[6];
  I_phA = FOC_FCF_U->I_phA[7];
  I_phA_0 = FOC_FCF_U->I_phA[8];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S24>/TrafoMatrix uvw->alphabeta' */
    TrafoMatrixuvwalphabeta = FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_j[i_0] *
      tmp_0;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_j[i_0 + 2]
      * I_phA;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_j[i_0 + 4]
      * I_phA_0;
    FOC_FCF_B->TrafoMatrixuvwalphabeta_m[i_0] = TrafoMatrixuvwalphabeta;
  }

  /* Sum: '<S5>/Sum2' incorporates:
   *  Constant: '<S5>/FOC_9ph_AngleShift'
   */
  FOC_FCF_B->Sum2_m = FOC_FCF_B->Sum1_d + FOC_FCF_P.FOC_9ph_AngleShift;

  /* Trigonometry: '<S24>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_k = cosf(FOC_FCF_B->Sum2_m);

  /* Product: '<S24>/TrafoProd' */
  FOC_FCF_B->TrafoProd_n = FOC_FCF_B->TrafoMatrixuvwalphabeta_m[0] *
    FOC_FCF_B->TrigonometricFunction1_k;

  /* Trigonometry: '<S24>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_k = sinf(FOC_FCF_B->Sum2_m);

  /* Product: '<S24>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3_o = FOC_FCF_B->TrigonometricFunction_k *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_m[1];

  /* Sum: '<S24>/TrafoSum' */
  FOC_FCF_B->TrafoSum_n = FOC_FCF_B->TrafoProd_n + FOC_FCF_B->TrafoProd3_o;

  /* Product: '<S24>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1_e = FOC_FCF_B->TrigonometricFunction1_k *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_m[1];

  /* Product: '<S24>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2_h = FOC_FCF_B->TrafoMatrixuvwalphabeta_m[0] *
    FOC_FCF_B->TrigonometricFunction_k;

  /* Sum: '<S24>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1_p = FOC_FCF_B->TrafoProd1_e - FOC_FCF_B->TrafoProd2_h;

  /* SignalConversion generated from: '<S24>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0] = FOC_FCF_B->TrafoSum_n;
  FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1] = FOC_FCF_B->TrafoSum1_p;

  /* Sum: '<S21>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_e[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S34>/KP*e[k]1' incorporates:
   *  Constant: '<S34>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_h[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S34>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_d[0] = FOC_FCF_DW->IntegDelay1_DSTATE_h[0];

  /* Sum: '<S21>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_e[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S34>/KP*e[k]1' incorporates:
   *  Constant: '<S34>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_h[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S34>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_d[1] = FOC_FCF_DW->IntegDelay1_DSTATE_h[1];

  /* Product: '<S34>/Product1' incorporates:
   *  Constant: '<S34>/FOC_KI'
   *  Constant: '<S34>/FOC_T_fast'
   */
  FOC_FCF_B->Product1_b = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_er;

  /* Switch: '<S34>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Product: '<S34>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1_d[0] * FOC_FCF_B->Product1_b;
    FOC_FCF_B->Product2_e[0] = tmp_0;

    /* Sum: '<S34>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1_h[0];
    FOC_FCF_B->IntSum1[0] = tmp_0;

    /* Switch: '<S34>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_h[0] = tmp_0;

    /* Product: '<S34>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1_d[1] * FOC_FCF_B->Product1_b;
    FOC_FCF_B->Product2_e[1] = tmp_0;

    /* Sum: '<S34>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1_h[1];
    FOC_FCF_B->IntSum1[1] = tmp_0;

    /* Switch: '<S34>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_h[1] = tmp_0;
  } else {
    /* Switch: '<S34>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S34>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1_h[0] = FOC_FCF_P.Zero_Value_n;
    FOC_FCF_B->IntegEnaSwitch1_h[1] = FOC_FCF_P.Zero_Value_n;
  }

  /* End of Switch: '<S34>/IntegEnaSwitch1' */

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S4>/FOC_T_fast'
   *  Constant: '<S4>/FOC_output_trafo_delay'
   */
  FOC_FCF_B->Product_c = FOC_FCF_P.FOC_output_trafo_delay *
    FOC_FCF_B->Use_If_Mode[1] * FOC_FCF_P.FOC_T_fast_Value_m;

  /* Sum: '<S4>/Sum' */
  FOC_FCF_B->Sum_k = FOC_FCF_B->Use_If_Mode[0] + FOC_FCF_B->Product_c;

  /* Switch: '<S18>/Switch1' */
  if (FOC_FCF_B->Sum_k > FOC_FCF_P.Switch1_Threshold_a) {
    /* Sum: '<S18>/Sum2' incorporates:
     *  Constant: '<S18>/Constant'
     */
    FOC_FCF_B->Sum2_ez = FOC_FCF_B->Sum_k - FOC_FCF_P.Constant_Value_n;

    /* Switch: '<S18>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum2_ez;
  } else {
    /* Switch: '<S18>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum_k;
  }

  /* End of Switch: '<S18>/Switch1' */

  /* Switch: '<S18>/Switch2' */
  if (FOC_FCF_B->Switch1_k > FOC_FCF_P.Switch2_Threshold_o) {
    /* Switch: '<S18>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Switch1_k;
  } else {
    /* Sum: '<S18>/Sum3' incorporates:
     *  Constant: '<S18>/Constant1'
     */
    FOC_FCF_B->Sum3_d = FOC_FCF_B->Switch1_k + FOC_FCF_P.Constant1_Value_d;

    /* Switch: '<S18>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Sum3_d;
  }

  /* End of Switch: '<S18>/Switch2' */

  /* Sum: '<S4>/Sum2' incorporates:
   *  Constant: '<S4>/FOC_9ph_AngleShift'
   */
  FOC_FCF_B->Sum2_p = FOC_FCF_B->Switch2 + FOC_FCF_P.FOC_9ph_AngleShift;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Constant: '<S4>/FOC_9ph_AngleShift'
   */
  FOC_FCF_B->Sum1_l = FOC_FCF_B->Sum2_p + FOC_FCF_P.FOC_9ph_AngleShift;

  /* MultiPortSwitch: '<S1>/SelectControlMode' */
  switch ((int32_T)FOC_FCF_B->FOC_Mode_after_checks) {
   case 0:
    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S1>/Null'
     */
    for (i = 0; i < 9; i++) {
      FOC_FCF_B->SelectControlMode[i] = FOC_FCF_P.Null_Value[i];
    }
    break;

   case 1:
    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S1>/Null'
     */
    for (i = 0; i < 9; i++) {
      FOC_FCF_B->SelectControlMode[i] = FOC_FCF_P.Null_Value[i];
    }
    break;

   case 2:
    /* Gain: '<S49>/Gain' */
    FOC_FCF_B->Gain_fw = FOC_FCF_P.FOC_Uf_m * FOC_FCF_B->DiscreteTransferFcn;

    /* Signum: '<S49>/Sign' */
    tmp_0 = FOC_FCF_B->Gain_fw;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S49>/Sign' */
      FOC_FCF_B->Sign_p = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S49>/Sign' */
      FOC_FCF_B->Sign_p = -1.0F;
    } else {
      /* Signum: '<S49>/Sign' */
      FOC_FCF_B->Sign_p = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S49>/Sign' */

    /* Abs: '<S49>/Abs' */
    FOC_FCF_B->Abs_d = fabsf(FOC_FCF_B->Gain_fw);

    /* Saturate: '<S49>/Saturation1' */
    if (FOC_FCF_B->Abs_d > FOC_FCF_P.FOC_Uf_U_max) {
      /* Saturate: '<S49>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_max;
    } else if (FOC_FCF_B->Abs_d < FOC_FCF_P.FOC_Uf_U_min) {
      /* Saturate: '<S49>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_min;
    } else {
      /* Saturate: '<S49>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_B->Abs_d;
    }

    /* End of Saturate: '<S49>/Saturation1' */

    /* Product: '<S49>/Product' */
    FOC_FCF_B->Product_j = FOC_FCF_B->Saturation1 * FOC_FCF_B->Sign_p;

    /* Sum: '<S11>/Sum1' incorporates:
     *  Constant: '<S11>/FOC_9ph_AngleShift'
     */
    FOC_FCF_B->Sum1_n = FOC_FCF_B->Add + FOC_FCF_P.FOC_9ph_AngleShift;

    /* Sum: '<S11>/Sum2' incorporates:
     *  Constant: '<S11>/FOC_9ph_AngleShift'
     */
    FOC_FCF_B->Sum2_d = FOC_FCF_B->Sum1_n + FOC_FCF_P.FOC_9ph_AngleShift;

    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S11>/Uf_Ud'
     */
    FOC_FCF_B->SelectControlMode[0] = FOC_FCF_P.FOC_Uf_Ud;
    FOC_FCF_B->SelectControlMode[1] = FOC_FCF_B->Product_j;
    FOC_FCF_B->SelectControlMode[2] = FOC_FCF_P.FOC_Uf_Ud;
    FOC_FCF_B->SelectControlMode[3] = FOC_FCF_B->Product_j;
    FOC_FCF_B->SelectControlMode[4] = FOC_FCF_P.FOC_Uf_Ud;
    FOC_FCF_B->SelectControlMode[5] = FOC_FCF_B->Product_j;
    FOC_FCF_B->SelectControlMode[6] = FOC_FCF_B->Add;
    FOC_FCF_B->SelectControlMode[7] = FOC_FCF_B->Sum1_n;
    FOC_FCF_B->SelectControlMode[8] = FOC_FCF_B->Sum2_d;
    break;

   case 3:
    /* MultiPortSwitch: '<S1>/SelectControlMode' */
    FOC_FCF_B->SelectControlMode[0] = FOC_FCF_B->IntegEnaSwitch1[0];
    FOC_FCF_B->SelectControlMode[2] = FOC_FCF_B->IntegEnaSwitch1_n[0];
    FOC_FCF_B->SelectControlMode[4] = FOC_FCF_B->IntegEnaSwitch1_h[0];
    FOC_FCF_B->SelectControlMode[1] = FOC_FCF_B->IntegEnaSwitch1[1];
    FOC_FCF_B->SelectControlMode[3] = FOC_FCF_B->IntegEnaSwitch1_n[1];
    FOC_FCF_B->SelectControlMode[5] = FOC_FCF_B->IntegEnaSwitch1_h[1];
    FOC_FCF_B->SelectControlMode[6] = FOC_FCF_B->Switch2;
    FOC_FCF_B->SelectControlMode[7] = FOC_FCF_B->Sum2_p;
    FOC_FCF_B->SelectControlMode[8] = FOC_FCF_B->Sum1_l;
    break;

   case 4:
    /* MultiPortSwitch: '<S1>/SelectControlMode' */
    FOC_FCF_B->SelectControlMode[0] = FOC_FCF_B->IntegEnaSwitch1[0];
    FOC_FCF_B->SelectControlMode[2] = FOC_FCF_B->IntegEnaSwitch1_n[0];
    FOC_FCF_B->SelectControlMode[4] = FOC_FCF_B->IntegEnaSwitch1_h[0];
    FOC_FCF_B->SelectControlMode[1] = FOC_FCF_B->IntegEnaSwitch1[1];
    FOC_FCF_B->SelectControlMode[3] = FOC_FCF_B->IntegEnaSwitch1_n[1];
    FOC_FCF_B->SelectControlMode[5] = FOC_FCF_B->IntegEnaSwitch1_h[1];
    FOC_FCF_B->SelectControlMode[6] = FOC_FCF_B->Switch2;
    FOC_FCF_B->SelectControlMode[7] = FOC_FCF_B->Sum2_p;
    FOC_FCF_B->SelectControlMode[8] = FOC_FCF_B->Sum1_l;
    break;

   default:
    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S1>/Null'
     */
    for (i = 0; i < 9; i++) {
      FOC_FCF_B->SelectControlMode[i] = FOC_FCF_P.Null_Value[i];
    }
    break;
  }

  /* End of MultiPortSwitch: '<S1>/SelectControlMode' */

  /* Trigonometry: '<S58>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_n = sinf(FOC_FCF_B->SelectControlMode[6]);

  /* Trigonometry: '<S58>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_j = cosf(FOC_FCF_B->SelectControlMode[6]);

  /* Gain: '<S58>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[0] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S58>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[0] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S58>/Sum1' incorporates:
   *  Gain: '<S58>/Gain'
   *  Gain: '<S58>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S58>/Product' incorporates:
   *  Sum: '<S58>/Sum1'
   */
  I_phA_0 = Sum1_lz;

  /* Gain: '<S58>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[1] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S58>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[1] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S58>/Sum1' incorporates:
   *  Gain: '<S58>/Gain'
   *  Gain: '<S58>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S58>/Product' incorporates:
   *  Sum: '<S58>/Sum1'
   */
  tmp_0 = Sum1_lz;

  /* Gain: '<S58>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[2] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S58>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[2] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S58>/Sum1' incorporates:
   *  Gain: '<S58>/Gain'
   *  Gain: '<S58>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S58>/Product' incorporates:
   *  Sum: '<S58>/Sum1'
   */
  I_phA = Sum1_lz;

  /* Gain: '<S58>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[3] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S58>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[3] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S58>/Sum1' incorporates:
   *  Gain: '<S58>/Gain'
   *  Gain: '<S58>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S58>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[0];
  Gain = FOC_FCF_B->SelectControlMode[1];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S58>/Product' */
  FOC_FCF_B->Product_c0[0] = I_phA_0;

  /* Product: '<S58>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_lz * Gain;

  /* Product: '<S58>/Product' */
  FOC_FCF_B->Product_c0[1] = I_phA_0;

  /* Product: '<S55>/Product' incorporates:
   *  Constant: '<S55>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_d[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_c0[0];
  Gain = FOC_FCF_B->Product_c0[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    I_phA_0 = tmp[i_0] * TrafoMatrixuvwalphabeta;
    I_phA_0 += tmp[i_0 + 3] * Gain;

    /* Product: '<S55>/Product' */
    FOC_FCF_B->U_uvw1[i_0] = I_phA_0;
  }

  /* End of Product: '<S55>/Product' */

  /* Trigonometry: '<S59>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_j = sinf(FOC_FCF_B->SelectControlMode[7]);

  /* Trigonometry: '<S59>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_h = cosf(FOC_FCF_B->SelectControlMode[7]);

  /* Gain: '<S59>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[0] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S59>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[0] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S59>/Sum1' incorporates:
   *  Gain: '<S59>/Gain'
   *  Gain: '<S59>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S59>/Product' incorporates:
   *  Sum: '<S59>/Sum1'
   */
  I_phA_0 = Sum1_lz;

  /* Gain: '<S59>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[1] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S59>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[1] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S59>/Sum1' incorporates:
   *  Gain: '<S59>/Gain'
   *  Gain: '<S59>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S59>/Product' incorporates:
   *  Sum: '<S59>/Sum1'
   */
  tmp_0 = Sum1_lz;

  /* Gain: '<S59>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[2] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S59>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[2] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S59>/Sum1' incorporates:
   *  Gain: '<S59>/Gain'
   *  Gain: '<S59>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S59>/Product' incorporates:
   *  Sum: '<S59>/Sum1'
   */
  I_phA = Sum1_lz;

  /* Gain: '<S59>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[3] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S59>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[3] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S59>/Sum1' incorporates:
   *  Gain: '<S59>/Gain'
   *  Gain: '<S59>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S59>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[2];
  Gain = FOC_FCF_B->SelectControlMode[3];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S59>/Product' */
  FOC_FCF_B->Product_f[0] = I_phA_0;

  /* Product: '<S59>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_lz * Gain;

  /* Product: '<S59>/Product' */
  FOC_FCF_B->Product_f[1] = I_phA_0;

  /* Product: '<S56>/Product' incorporates:
   *  Constant: '<S56>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_g[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_f[0];
  Gain = FOC_FCF_B->Product_f[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    I_phA_0 = tmp[i_0] * TrafoMatrixuvwalphabeta;
    I_phA_0 += tmp[i_0 + 3] * Gain;

    /* Product: '<S56>/Product' */
    FOC_FCF_B->Product_f3[i_0] = I_phA_0;
  }

  /* End of Product: '<S56>/Product' */

  /* Trigonometry: '<S60>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_h = sinf(FOC_FCF_B->SelectControlMode[8]);

  /* Trigonometry: '<S60>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_hh = cosf(FOC_FCF_B->SelectControlMode[8]);

  /* Gain: '<S60>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[0] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S60>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_j[0] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S60>/Sum1' incorporates:
   *  Gain: '<S60>/Gain'
   *  Gain: '<S60>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S60>/Product' incorporates:
   *  Sum: '<S60>/Sum1'
   */
  I_phA_0 = Sum1_lz;

  /* Gain: '<S60>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[1] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S60>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_j[1] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S60>/Sum1' incorporates:
   *  Gain: '<S60>/Gain'
   *  Gain: '<S60>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S60>/Product' incorporates:
   *  Sum: '<S60>/Sum1'
   */
  tmp_0 = Sum1_lz;

  /* Gain: '<S60>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[2] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S60>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_j[2] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S60>/Sum1' incorporates:
   *  Gain: '<S60>/Gain'
   *  Gain: '<S60>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S60>/Product' incorporates:
   *  Sum: '<S60>/Sum1'
   */
  I_phA = Sum1_lz;

  /* Gain: '<S60>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[3] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S60>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_j[3] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S60>/Sum1' incorporates:
   *  Gain: '<S60>/Gain'
   *  Gain: '<S60>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S60>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[4];
  Gain = FOC_FCF_B->SelectControlMode[5];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S60>/Product' */
  FOC_FCF_B->Product_i[0] = I_phA_0;

  /* Product: '<S60>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_lz * Gain;

  /* Product: '<S60>/Product' */
  FOC_FCF_B->Product_i[1] = I_phA_0;

  /* Product: '<S57>/Product' incorporates:
   *  Constant: '<S57>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_oq[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_i[0];
  Gain = FOC_FCF_B->Product_i[1];

  /* Outputs for Atomic SubSystem: '<S12>/NormalizedVoltage' */
  /* Gain: '<S52>/U_DC//2' */
  FOC_FCF_B->U_DC2 = FOC_FCF_P.U_DC2_Gain_p * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S52>/AvoidDivBy0' incorporates:
   *  Constant: '<S52>/Constant2'
   */
  tmp_0 = fmaxf(FOC_FCF_P.Constant2_Value_g, FOC_FCF_B->U_DC2);

  /* MinMax: '<S52>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0 = tmp_0;
  for (i = 0; i < 3; i++) {
    /* Product: '<S57>/Product' */
    tmp_0 = tmp[i] * TrafoMatrixuvwalphabeta;
    tmp_0 += tmp[i + 3] * Gain;

    /* Product: '<S57>/Product' */
    FOC_FCF_B->Product_fb[i] = tmp_0;

    /* Product: '<S52>/DutyCycle_normalized' */
    FOC_FCF_B->DutyCycle_normed[i] = FOC_FCF_B->U_uvw1[i] /
      FOC_FCF_B->AvoidDivBy0;
    FOC_FCF_B->DutyCycle_normed[i + 3] = FOC_FCF_B->Product_f3[i] /
      FOC_FCF_B->AvoidDivBy0;
    FOC_FCF_B->DutyCycle_normed[i + 6] = tmp_0 / FOC_FCF_B->AvoidDivBy0;
  }

  /* End of Outputs for SubSystem: '<S12>/NormalizedVoltage' */

  /* Outputs for Atomic SubSystem: '<S12>/Super_Sinus_Modulation' */
  /* MinMax: '<S54>/MinMax2' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[0];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[1]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S54>/MinMax2' */
  FOC_FCF_B->MinMax2 = tmp_0;

  /* MinMax: '<S54>/MinMax3' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[0];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[1]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S54>/MinMax3' */
  FOC_FCF_B->MinMax3 = tmp_0;

  /* Sum: '<S54>/Sum1' */
  FOC_FCF_B->Sum1_o = FOC_FCF_B->MinMax2 + FOC_FCF_B->MinMax3;

  /* Gain: '<S54>/Factor' */
  FOC_FCF_B->Factor = FOC_FCF_P.Factor_Gain * FOC_FCF_B->Sum1_o;

  /* Sum: '<S54>/DutyCycle_SuperSinus_1' */
  FOC_FCF_B->DutyCycle_SuperSinus_1[0] = FOC_FCF_B->DutyCycle_normed[0] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[1] = FOC_FCF_B->DutyCycle_normed[1] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[2] = FOC_FCF_B->DutyCycle_normed[2] -
    FOC_FCF_B->Factor;

  /* MinMax: '<S54>/MinMax1' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[3];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[4]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S54>/MinMax1' */
  FOC_FCF_B->MinMax1 = tmp_0;

  /* MinMax: '<S54>/MinMax4' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[3];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[4]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S54>/MinMax4' */
  FOC_FCF_B->MinMax4 = tmp_0;

  /* Sum: '<S54>/Sum2' */
  FOC_FCF_B->Sum2_i = FOC_FCF_B->MinMax1 + FOC_FCF_B->MinMax4;

  /* Gain: '<S54>/Factor1' */
  FOC_FCF_B->Factor1 = FOC_FCF_P.Factor1_Gain * FOC_FCF_B->Sum2_i;

  /* Sum: '<S54>/DutyCycle_SuperSinus_2' */
  FOC_FCF_B->DutyCycle_SuperSinus_2[0] = FOC_FCF_B->DutyCycle_normed[3] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[1] = FOC_FCF_B->DutyCycle_normed[4] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[2] = FOC_FCF_B->DutyCycle_normed[5] -
    FOC_FCF_B->Factor1;

  /* MinMax: '<S54>/MinMax5' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[6];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[7]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[8]);

  /* MinMax: '<S54>/MinMax5' */
  FOC_FCF_B->MinMax5 = tmp_0;

  /* MinMax: '<S54>/MinMax6' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[6];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[7]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[8]);

  /* MinMax: '<S54>/MinMax6' */
  FOC_FCF_B->MinMax6 = tmp_0;

  /* Sum: '<S54>/Sum3' */
  FOC_FCF_B->Sum3_k = FOC_FCF_B->MinMax5 + FOC_FCF_B->MinMax6;

  /* Gain: '<S54>/Factor2' */
  FOC_FCF_B->Factor2 = FOC_FCF_P.Factor2_Gain * FOC_FCF_B->Sum3_k;

  /* Sum: '<S54>/DutyCycle_SuperSinus_3' */
  FOC_FCF_B->DutyCycle_SuperSinus_3[0] = FOC_FCF_B->DutyCycle_normed[6] -
    FOC_FCF_B->Factor2;
  FOC_FCF_B->DutyCycle_SuperSinus_3[1] = FOC_FCF_B->DutyCycle_normed[7] -
    FOC_FCF_B->Factor2;
  FOC_FCF_B->DutyCycle_SuperSinus_3[2] = FOC_FCF_B->DutyCycle_normed[8] -
    FOC_FCF_B->Factor2;

  /* End of Outputs for SubSystem: '<S12>/Super_Sinus_Modulation' */

  /* MultiPortSwitch: '<S12>/SelectModulation' incorporates:
   *  Constant: '<S12>/Enable_SuperSinMod'
   */
  if (FOC_FCF_P.FOC_SELECT_Modulation == 0) {
    /* MultiPortSwitch: '<S12>/SelectModulation' */
    for (i = 0; i < 9; i++) {
      FOC_FCF_B->SelMod_DutyCycles[i] = FOC_FCF_B->DutyCycle_normed[i];
    }
  } else {
    /* MultiPortSwitch: '<S12>/SelectModulation' */
    FOC_FCF_B->SelMod_DutyCycles[0] = FOC_FCF_B->DutyCycle_SuperSinus_1[0];
    FOC_FCF_B->SelMod_DutyCycles[3] = FOC_FCF_B->DutyCycle_SuperSinus_2[0];
    FOC_FCF_B->SelMod_DutyCycles[6] = FOC_FCF_B->DutyCycle_SuperSinus_3[0];
    FOC_FCF_B->SelMod_DutyCycles[1] = FOC_FCF_B->DutyCycle_SuperSinus_1[1];
    FOC_FCF_B->SelMod_DutyCycles[4] = FOC_FCF_B->DutyCycle_SuperSinus_2[1];
    FOC_FCF_B->SelMod_DutyCycles[7] = FOC_FCF_B->DutyCycle_SuperSinus_3[1];
    FOC_FCF_B->SelMod_DutyCycles[2] = FOC_FCF_B->DutyCycle_SuperSinus_1[2];
    FOC_FCF_B->SelMod_DutyCycles[5] = FOC_FCF_B->DutyCycle_SuperSinus_2[2];
    FOC_FCF_B->SelMod_DutyCycles[8] = FOC_FCF_B->DutyCycle_SuperSinus_3[2];
  }

  /* End of MultiPortSwitch: '<S12>/SelectModulation' */
  for (i = 0; i < 9; i++) {
    /* Bias: '<S50>/Scale [0..2]' */
    tmp_0 = FOC_FCF_B->SelMod_DutyCycles[i] + FOC_FCF_P.Scale02_Bias;
    FOC_FCF_B->Scale02[i] = tmp_0;

    /* Gain: '<S50>/Scale  [0..1]' */
    tmp_0 *= FOC_FCF_P.Scale01_Gain;
    FOC_FCF_B->Scale01[i] = tmp_0;

    /* Saturate: '<S50>/Limit [0..1]' */
    if (tmp_0 > FOC_FCF_P.Limit01_UpperSat) {
      tmp_0 = FOC_FCF_P.Limit01_UpperSat;
    } else if (tmp_0 < FOC_FCF_P.Limit01_LowerSat) {
      tmp_0 = FOC_FCF_P.Limit01_LowerSat;
    }

    /* Saturate: '<S50>/Limit [0..1]' */
    FOC_FCF_B->Limit01[i] = tmp_0;
  }

  /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_1' incorporates:
   *  Constant: '<S53>/Constant6'
   */
  switch ((int32_T)FOC_FCF_P.FOC_SELECT_Voltage_Assignment_UVW) {
   case 1:
    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[2];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[5];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[8];
    break;

   case 2:
    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[1];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[4];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[7];
    break;

   case 3:
    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[2];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[5];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[8];
    break;

   case 4:
    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[0];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[3];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[6];
    break;

   case 5:
    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[1];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[4];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[7];
    break;

   default:
    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[0];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[3];

    /* MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[6];
    break;
  }

  /* End of MultiPortSwitch: '<S53>/Select_GateDriver_Assignment_1' */

  /* Sum: '<S13>/Deviation' */
  FOC_FCF_B->Deviation = FOC_FCF_B->Sum3 - FOC_FCF_B->phi_el_observer;

  /* Product: '<S13>/Product2' incorporates:
   *  Constant: '<S13>/Constant'
   *  Constant: '<S13>/Constant1'
   */
  FOC_FCF_B->Product2 = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_D * FOC_FCF_B->Deviation;

  /* Gain: '<S13>/Gain' */
  FOC_FCF_B->Gain_g = FOC_FCF_P.Gain_Gain_k * FOC_FCF_B->Product2;

  /* Gain: '<S13>/Gain4' */
  FOC_FCF_B->winkelimpuls = FOC_FCF_P.FOC_OmegaObs3 * FOC_FCF_B->Deviation;

  /* Sum: '<S13>/Sum1' */
  FOC_FCF_B->Sum1_g4 = FOC_FCF_B->Gain_g + FOC_FCF_B->w_el;

  /* Product: '<S13>/Product' incorporates:
   *  Constant: '<S13>/FOC_T_fast'
   */
  FOC_FCF_B->Product_o = FOC_FCF_B->Sum1_g4 * FOC_FCF_P.FOC_T_fast_Value_df;

  /* Product: '<S13>/Product1' incorporates:
   *  Constant: '<S13>/Constant'
   */
  FOC_FCF_B->Product1_bi = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_w0 * FOC_FCF_B->Deviation;

  /* UnitDelay: '<S17>/Unit Delay1' */
  FOC_FCF_B->UnitDelay1 = FOC_FCF_DW->UnitDelay1_DSTATE_i;

  /* Sum: '<S13>/Sum2' */
  FOC_FCF_B->Sum2_mq = FOC_FCF_B->Product1_bi + FOC_FCF_B->UnitDelay1;

  /* Sum: '<S13>/Sum6' */
  FOC_FCF_B->Sum6 = FOC_FCF_B->Product_o + FOC_FCF_B->phi_el_observer;

  /* Product: '<S16>/Product' incorporates:
   *  Constant: '<S16>/FOC_T_fast'
   */
  FOC_FCF_B->Product_n = FOC_FCF_B->Sum2_mq * FOC_FCF_P.FOC_T_fast_Value_c;

  /* Sum: '<S16>/Sum2' */
  FOC_FCF_B->Sum2_e = FOC_FCF_B->Product_n + FOC_FCF_B->w_el;

  /* Product: '<S17>/Product' incorporates:
   *  Constant: '<S17>/FOC_T_fast'
   */
  FOC_FCF_B->Product_cd = FOC_FCF_B->winkelimpuls * FOC_FCF_P.FOC_T_fast_Value_k;

  /* Sum: '<S17>/Sum2' */
  FOC_FCF_B->Sum2_j = FOC_FCF_B->Product_cd + FOC_FCF_B->UnitDelay1;

  /* Gain: '<S4>/Gain1' */
  FOC_FCF_B->phi_el_U_trafo[0] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Switch2;
  FOC_FCF_B->phi_el_U_trafo[1] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Sum2_p;
  FOC_FCF_B->phi_el_U_trafo[2] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Sum1_l;

  /* Outputs for Atomic SubSystem: '<S12>/Calc_Modulation_Index' */
  /* Gain: '<S51>/U_DC//2' */
  FOC_FCF_B->U_DC2_l = FOC_FCF_P.U_DC2_Gain * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S51>/AvoidDivBy0' incorporates:
   *  Constant: '<S51>/Constant2'
   */
  tmp_0 = fmaxf(FOC_FCF_P.Constant2_Value_d, FOC_FCF_B->U_DC2_l);

  /* MinMax: '<S51>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0_f = tmp_0;

  /* Math: '<S51>/Square' */
  tmp_0 = FOC_FCF_B->Product_c0[0];

  /* Math: '<S51>/Square' */
  FOC_FCF_B->Square[0] = tmp_0 * tmp_0;

  /* Math: '<S51>/Square' */
  tmp_0 = FOC_FCF_B->Product_c0[1];

  /* Math: '<S51>/Square' */
  FOC_FCF_B->Square[1] = tmp_0 * tmp_0;

  /* Sum: '<S51>/Sum' */
  tmp_0 = FOC_FCF_B->Square[0];

  /* Math: '<S51>/Square1' */
  I_phA = FOC_FCF_B->Product_f[0];

  /* Math: '<S51>/Square1' */
  FOC_FCF_B->Square1[0] = I_phA * I_phA;

  /* Sum: '<S51>/Sum' */
  tmp_0 += FOC_FCF_B->Square[1];

  /* Math: '<S51>/Square1' */
  I_phA = FOC_FCF_B->Product_f[1];

  /* Math: '<S51>/Square1' */
  FOC_FCF_B->Square1[1] = I_phA * I_phA;

  /* Sum: '<S51>/Sum' */
  FOC_FCF_B->Sum_kr = tmp_0;

  /* Sqrt: '<S51>/Sqrt' */
  FOC_FCF_B->Sqrt = sqrtf(FOC_FCF_B->Sum_kr);

  /* Sum: '<S51>/Sum1' */
  tmp_0 = FOC_FCF_B->Square1[0];

  /* Math: '<S51>/Square2' */
  I_phA = FOC_FCF_B->Product_i[0];

  /* Math: '<S51>/Square2' */
  FOC_FCF_B->Square2[0] = I_phA * I_phA;

  /* Sum: '<S51>/Sum1' */
  tmp_0 += FOC_FCF_B->Square1[1];

  /* Math: '<S51>/Square2' */
  I_phA = FOC_FCF_B->Product_i[1];

  /* Math: '<S51>/Square2' */
  FOC_FCF_B->Square2[1] = I_phA * I_phA;

  /* Sum: '<S51>/Sum1' */
  FOC_FCF_B->Sum1_a = tmp_0;

  /* Sqrt: '<S51>/Sqrt1' */
  FOC_FCF_B->Sqrt1 = sqrtf(FOC_FCF_B->Sum1_a);

  /* Sum: '<S51>/Sum2' */
  tmp_0 = FOC_FCF_B->Square2[0];
  tmp_0 += FOC_FCF_B->Square2[1];

  /* Sum: '<S51>/Sum2' */
  FOC_FCF_B->Sum2_iq = tmp_0;

  /* Sqrt: '<S51>/Sqrt2' */
  FOC_FCF_B->Sqrt2 = sqrtf(FOC_FCF_B->Sum2_iq);

  /* Product: '<S51>/Divide3' */
  FOC_FCF_B->ModInd[0] = FOC_FCF_B->Sqrt / FOC_FCF_B->AvoidDivBy0_f;
  FOC_FCF_B->ModInd[1] = FOC_FCF_B->Sqrt1 / FOC_FCF_B->AvoidDivBy0_f;
  FOC_FCF_B->ModInd[2] = FOC_FCF_B->Sqrt2 / FOC_FCF_B->AvoidDivBy0_f;

  /* End of Outputs for SubSystem: '<S12>/Calc_Modulation_Index' */

  /* Switch: '<S2>/ASC_Switch' incorporates:
   *  Switch: '<S26>/IntegStopSwitch2'
   *  Switch: '<S30>/IntegStopSwitch2'
   *  Switch: '<S34>/IntegStopSwitch2'
   */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Outport: '<Root>/DutyCycles [0..1]' */
    FOC_FCF_Y->DutyCycles01[0] = FOC_FCF_B->Select_GateDriver_Assignment_1[0];
    FOC_FCF_Y->DutyCycles01[3] = FOC_FCF_B->Select_GateDriver_Assignment_2[0];
    FOC_FCF_Y->DutyCycles01[6] = FOC_FCF_B->Select_GateDriver_Assignment_3[0];
    FOC_FCF_Y->DutyCycles01[1] = FOC_FCF_B->Select_GateDriver_Assignment_1[1];
    FOC_FCF_Y->DutyCycles01[4] = FOC_FCF_B->Select_GateDriver_Assignment_2[1];
    FOC_FCF_Y->DutyCycles01[7] = FOC_FCF_B->Select_GateDriver_Assignment_3[1];
    FOC_FCF_Y->DutyCycles01[2] = FOC_FCF_B->Select_GateDriver_Assignment_1[2];
    FOC_FCF_Y->DutyCycles01[5] = FOC_FCF_B->Select_GateDriver_Assignment_2[2];
    FOC_FCF_Y->DutyCycles01[8] = FOC_FCF_B->Select_GateDriver_Assignment_3[2];

    /* RelationalOperator: '<S25>/AntiWindupLE' incorporates:
     *  Constant: '<S25>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE_l = (FOC_FCF_B->ModInd[0] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S26>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1[0];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S26>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S26>/IntegStopSwitch3' incorporates:
       *  Constant: '<S26>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value[0];
    }

    /* Switch: '<S26>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[0] = I_phA;

    /* Sum: '<S26>/IntSum2' */
    FOC_FCF_B->IntSum2_j[0] = FOC_FCF_B->KPek1[0] + I_phA;

    /* Gain: '<S26>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S25>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[0] = FOC_FCF_B->IdqErr[0] * tmp_0;

    /* Switch: '<S26>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1[1];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S26>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S26>/IntegStopSwitch3' incorporates:
       *  Constant: '<S26>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value[1];
    }

    /* Switch: '<S26>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[1] = I_phA;

    /* Sum: '<S26>/IntSum2' */
    FOC_FCF_B->IntSum2_j[1] = FOC_FCF_B->KPek1[1] + I_phA;

    /* Gain: '<S26>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S25>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[1] = FOC_FCF_B->IdqErr[1] * tmp_0;

    /* RelationalOperator: '<S28>/Compare' incorporates:
     *  Constant: '<S28>/Constant'
     */
    FOC_FCF_B->Compare_o = (uint8_T)(FOC_FCF_B->antiWindupProd_o[1] <
      FOC_FCF_P.AntiWindupGT_q_const);

    /* Logic: '<S25>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q_o = (FOC_FCF_B->AntiWindupLE_l ||
      (FOC_FCF_B->Compare_o != 0));

    /* RelationalOperator: '<S27>/Compare' incorporates:
     *  Constant: '<S27>/Constant'
     */
    FOC_FCF_B->Compare_f = (uint8_T)(FOC_FCF_B->antiWindupProd_o[0] <
      FOC_FCF_P.AntiWindupGT_d_const);

    /* Logic: '<S25>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d_e = ((FOC_FCF_B->Compare_f != 0) ||
      FOC_FCF_B->AntiWindupLE_l);

    /* Switch: '<S26>/IntegStopSwitch1' */
    tmp_1 = FOC_FCF_B->AntiWindupOR_d_e;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q_o;
    if (tmp_1) {
      tmp_0 = FOC_FCF_B->IntSum2_j[0];

      /* Switch: '<S26>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_c[0];

      /* Switch: '<S26>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = tmp_0;
    }

    /* Switch: '<S26>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[0] = tmp_0;

    /* Switch: '<S26>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2_j[1];

      /* Switch: '<S26>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_c[1];

      /* Switch: '<S26>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = tmp_0;
    }

    /* Switch: '<S26>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[1] = tmp_0;

    /* RelationalOperator: '<S29>/AntiWindupLE' incorporates:
     *  Constant: '<S29>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE_f = (FOC_FCF_B->ModInd[1] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S30>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[0];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S30>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S30>/IntegStopSwitch3' incorporates:
       *  Constant: '<S30>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_l[0];
    }

    /* Switch: '<S30>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_n[0] = I_phA;

    /* Sum: '<S30>/IntSum2' */
    FOC_FCF_B->IntSum2_f[0] = FOC_FCF_B->KPek1_l[0] + I_phA;

    /* Gain: '<S30>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_g[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S29>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_d[0] = FOC_FCF_B->IdqErr_l[0] * tmp_0;

    /* Switch: '<S30>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[1];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S30>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S30>/IntegStopSwitch3' incorporates:
       *  Constant: '<S30>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_l[1];
    }

    /* Switch: '<S30>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_n[1] = I_phA;

    /* Sum: '<S30>/IntSum2' */
    FOC_FCF_B->IntSum2_f[1] = FOC_FCF_B->KPek1_l[1] + I_phA;

    /* Gain: '<S30>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_g[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S29>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_d[1] = FOC_FCF_B->IdqErr_l[1] * tmp_0;

    /* RelationalOperator: '<S32>/Compare' incorporates:
     *  Constant: '<S32>/Constant'
     */
    FOC_FCF_B->Compare_g = (uint8_T)(FOC_FCF_B->antiWindupProd_d[1] <
      FOC_FCF_P.AntiWindupGT_q_const_h);

    /* Logic: '<S29>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q_l = (FOC_FCF_B->AntiWindupLE_f ||
      (FOC_FCF_B->Compare_g != 0));

    /* RelationalOperator: '<S31>/Compare' incorporates:
     *  Constant: '<S31>/Constant'
     */
    FOC_FCF_B->Compare_i = (uint8_T)(FOC_FCF_B->antiWindupProd_d[0] <
      FOC_FCF_P.AntiWindupGT_d_const_n);

    /* Logic: '<S29>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d_m = ((FOC_FCF_B->Compare_i != 0) ||
      FOC_FCF_B->AntiWindupLE_f);

    /* Switch: '<S30>/IntegStopSwitch1' */
    tmp_1 = FOC_FCF_B->AntiWindupOR_d_m;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q_l;
    if (tmp_1) {
      tmp_0 = FOC_FCF_B->IntSum2_f[0];

      /* Switch: '<S30>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_g[0];

      /* Switch: '<S30>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[0] = tmp_0;
    }

    /* Switch: '<S30>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[0] = tmp_0;

    /* Switch: '<S30>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2_f[1];

      /* Switch: '<S30>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_g[1];

      /* Switch: '<S30>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[1] = tmp_0;
    }

    /* Switch: '<S30>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[1] = tmp_0;

    /* RelationalOperator: '<S33>/AntiWindupLE' incorporates:
     *  Constant: '<S33>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE = (FOC_FCF_B->ModInd[2] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S34>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_d[0];
    if (FOC_FCF_B->Product1_b > FOC_FCF_P.IntegStopSwitch3_Threshold_ad) {
      /* Switch: '<S34>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S34>/IntegStopSwitch3' incorporates:
       *  Constant: '<S34>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_o[0];
    }

    /* Switch: '<S34>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[0] = I_phA;

    /* Sum: '<S34>/IntSum2' */
    FOC_FCF_B->IntSum2[0] = FOC_FCF_B->KPek1_h[0] + I_phA;

    /* Gain: '<S34>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S33>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[0] = FOC_FCF_B->IdqErr_e[0] * tmp_0;

    /* Switch: '<S34>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_d[1];
    if (FOC_FCF_B->Product1_b > FOC_FCF_P.IntegStopSwitch3_Threshold_ad) {
      /* Switch: '<S34>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S34>/IntegStopSwitch3' incorporates:
       *  Constant: '<S34>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_o[1];
    }

    /* Switch: '<S34>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[1] = I_phA;

    /* Sum: '<S34>/IntSum2' */
    FOC_FCF_B->IntSum2[1] = FOC_FCF_B->KPek1_h[1] + I_phA;

    /* Gain: '<S34>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S33>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[1] = FOC_FCF_B->IdqErr_e[1] * tmp_0;

    /* RelationalOperator: '<S36>/Compare' incorporates:
     *  Constant: '<S36>/Constant'
     */
    FOC_FCF_B->Compare = (uint8_T)(FOC_FCF_B->antiWindupProd[1] <
      FOC_FCF_P.AntiWindupGT_q_const_l);

    /* Logic: '<S33>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q = (FOC_FCF_B->AntiWindupLE || (FOC_FCF_B->Compare
      != 0));

    /* RelationalOperator: '<S35>/Compare' incorporates:
     *  Constant: '<S35>/Constant'
     */
    FOC_FCF_B->Compare_k = (uint8_T)(FOC_FCF_B->antiWindupProd[0] <
      FOC_FCF_P.AntiWindupGT_d_const_f);

    /* Logic: '<S33>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d = ((FOC_FCF_B->Compare_k != 0) ||
      FOC_FCF_B->AntiWindupLE);

    /* Switch: '<S34>/IntegStopSwitch1' */
    tmp_1 = FOC_FCF_B->AntiWindupOR_d;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q;
    if (tmp_1) {
      tmp_0 = FOC_FCF_B->IntSum2[0];

      /* Switch: '<S34>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp[0];

      /* Switch: '<S34>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = tmp_0;
    }

    /* Switch: '<S34>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_h[0] = tmp_0;

    /* Switch: '<S34>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2[1];

      /* Switch: '<S34>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp[1];

      /* Switch: '<S34>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = tmp_0;
    }

    /* Switch: '<S34>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_h[1] = tmp_0;
  } else {
    /* MultiPortSwitch: '<S2>/ASC Switch' incorporates:
     *  Constant: '<S2>/FOC_AKS_Mode'
     */
    switch ((int32_T)FOC_FCF_P.FOC_ASC_Mode) {
     case 1:
      /* MultiPortSwitch: '<S2>/ASC Switch' incorporates:
       *  Constant: '<S2>/ASC_LS'
       */
      for (i = 0; i < 9; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_LS_Value[i];
      }
      break;

     case 2:
      /* MultiPortSwitch: '<S2>/ASC Switch' incorporates:
       *  Constant: '<S2>/ASC_HS'
       */
      for (i = 0; i < 9; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_HS_Value[i];
      }
      break;

     default:
      /* MultiPortSwitch: '<S2>/ASC Switch' incorporates:
       *  Constant: '<S2>/ASC_LSHS'
       */
      for (i = 0; i < 9; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_LSHS_Value[i];
      }
      break;
    }

    /* End of MultiPortSwitch: '<S2>/ASC Switch' */

    /* Outport: '<Root>/DutyCycles [0..1]' */
    for (i = 0; i < 9; i++) {
      FOC_FCF_Y->DutyCycles01[i] = FOC_FCF_B->ASCSwitch[i];
    }

    /* Switch: '<S26>/IntegStopSwitch2' incorporates:
     *  Constant: '<S26>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2[0] = FOC_FCF_P.Zero1_Value[0];
    FOC_FCF_B->IntegStopSwitch2[1] = FOC_FCF_P.Zero1_Value[1];

    /* Switch: '<S30>/IntegStopSwitch2' incorporates:
     *  Constant: '<S30>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2_o[0] = FOC_FCF_P.Zero1_Value_l[0];
    FOC_FCF_B->IntegStopSwitch2_o[1] = FOC_FCF_P.Zero1_Value_l[1];

    /* Switch: '<S34>/IntegStopSwitch2' incorporates:
     *  Constant: '<S34>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2_h[0] = FOC_FCF_P.Zero1_Value_o[0];
    FOC_FCF_B->IntegStopSwitch2_h[1] = FOC_FCF_P.Zero1_Value_o[1];
  }

  /* End of Switch: '<S2>/ASC_Switch' */

  /* Gain: '<S19>/Gain1' */
  FOC_FCF_B->U_d1_CC = FOC_FCF_P.Gain1_Gain_cs * FOC_FCF_B->IntegEnaSwitch1[0];

  /* Gain: '<S19>/Gain2' */
  FOC_FCF_B->U_q1_CC = FOC_FCF_P.Gain2_Gain * FOC_FCF_B->IntegEnaSwitch1[1];

  /* DiscreteFir: '<S22>/Discrete FIR Filter 20th order' */
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

  /* End of DiscreteFir: '<S22>/Discrete FIR Filter 20th order' */

  /* DiscreteFir: '<S23>/Discrete FIR Filter 20th order' */
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

  /* End of DiscreteFir: '<S23>/Discrete FIR Filter 20th order' */

  /* DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
  i = 1;
  tmp_0 = FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0] *
    FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[0];
  for (i_0 = FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c; i_0 < 19; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i_0] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[i];
    tmp_0 += I_phA;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i_0] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[i];
    tmp_0 += I_phA;
    i++;
  }

  FOC_FCF_B->DiscreteFIRFilter20thorder_l[0] = tmp_0;
  i = 1;
  tmp_0 = FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[0] *
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1];
  for (i_0 = FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c; i_0 < 19; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i_0 + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[i];
    tmp_0 += I_phA;
    i++;
  }

  for (i_0 = 0; i_0 < FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c; i_0++) {
    I_phA = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i_0 + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[i];
    tmp_0 += I_phA;
    i++;
  }

  FOC_FCF_B->DiscreteFIRFilter20thorder_l[1] = tmp_0;

  /* End of DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */

  /* Abs: '<S37>/Abs' */
  FOC_FCF_B->Abs_e = fabsf(FOC_FCF_B->Add_mp);

  /* Switch: '<S37>/Switch' */
  if (FOC_FCF_B->Abs_e >= FOC_FCF_P.Switch_Threshold) {
    /* Signum: '<S37>/Sign' */
    tmp_0 = FOC_FCF_B->Product_h;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S37>/Sign' */
      FOC_FCF_B->Sign_d = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S37>/Sign' */
      FOC_FCF_B->Sign_d = -1.0F;
    } else {
      /* Signum: '<S37>/Sign' */
      FOC_FCF_B->Sign_d = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S37>/Sign' */

    /* Gain: '<S37>/Gain1' */
    FOC_FCF_B->Gain1_j = FOC_FCF_P.Gain1_Gain * FOC_FCF_B->Sign_d;

    /* Switch: '<S37>/Switch' */
    FOC_FCF_B->Switch_d = FOC_FCF_B->Gain1_j;
  } else {
    /* Switch: '<S37>/Switch' incorporates:
     *  Constant: '<S37>/Constant1'
     */
    FOC_FCF_B->Switch_d = FOC_FCF_P.Constant1_Value_c;
  }

  /* End of Switch: '<S37>/Switch' */

  /* Sum: '<S37>/Add1' */
  FOC_FCF_B->Add1 = FOC_FCF_B->Add_mp - FOC_FCF_B->Switch_d;

  /* DataTypeConversion: '<S8>/Data Type Conversion' */
  FOC_FCF_B->DataTypeConversion = FOC_FCF_B->Logic_gq[0];

  /* Gain: '<S8>/Gain1' */
  FOC_FCF_B->FOC_Overcurrent_I_uvw = FOC_FCF_P.Gain1_Gain_f *
    FOC_FCF_B->DataTypeConversion;

  /* DataTypeConversion: '<S9>/Data Type Conversion' */
  FOC_FCF_B->DataTypeConversion_i = FOC_FCF_B->Logic[0];

  /* DataTypeConversion: '<S9>/Data Type Conversion1' */
  FOC_FCF_B->DataTypeConversion1 = FOC_FCF_B->Logic_g[0];

  /* Gain: '<S9>/Gain1' */
  FOC_FCF_B->FOC_Undervoltage_U_DC = FOC_FCF_P.Gain1_Gain_g *
    FOC_FCF_B->DataTypeConversion_i;

  /* Gain: '<S9>/Gain2' */
  FOC_FCF_B->FOC_Overvoltage_U_DC = FOC_FCF_P.Gain2_Gain_n *
    FOC_FCF_B->DataTypeConversion1;

  /* Abs: '<S10>/Abs' */
  FOC_FCF_B->Abs_b = fabsf(FOC_FCF_B->Add_m);

  /* Switch: '<S10>/Switch' */
  if (FOC_FCF_B->Abs_b >= FOC_FCF_P.Switch_Threshold_b) {
    /* Signum: '<S10>/Sign' */
    tmp_0 = FOC_FCF_B->Product_e;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S10>/Sign' */
      FOC_FCF_B->Sign_n = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S10>/Sign' */
      FOC_FCF_B->Sign_n = -1.0F;
    } else {
      /* Signum: '<S10>/Sign' */
      FOC_FCF_B->Sign_n = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S10>/Sign' */

    /* Gain: '<S10>/Gain1' */
    FOC_FCF_B->Gain1_h = FOC_FCF_P.Gain1_Gain_c * FOC_FCF_B->Sign_n;

    /* Switch: '<S10>/Switch' */
    FOC_FCF_B->Switch_l = FOC_FCF_B->Gain1_h;
  } else {
    /* Switch: '<S10>/Switch' incorporates:
     *  Constant: '<S10>/Constant1'
     */
    FOC_FCF_B->Switch_l = FOC_FCF_P.Constant1_Value_k;
  }

  /* End of Switch: '<S10>/Switch' */

  /* Sum: '<S10>/Add1' */
  FOC_FCF_B->Add1_j = FOC_FCF_B->Add_m - FOC_FCF_B->Switch_l;

  /* Abs: '<S48>/Abs' */
  FOC_FCF_B->Abs_f = fabsf(FOC_FCF_B->Add);

  /* Switch: '<S48>/Switch' */
  if (FOC_FCF_B->Abs_f >= FOC_FCF_P.Switch_Threshold_c) {
    /* Signum: '<S48>/Sign' */
    tmp_0 = FOC_FCF_B->Product;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S48>/Sign' */
      FOC_FCF_B->Sign = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S48>/Sign' */
      FOC_FCF_B->Sign = -1.0F;
    } else {
      /* Signum: '<S48>/Sign' */
      FOC_FCF_B->Sign = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S48>/Sign' */

    /* Gain: '<S48>/Gain1' */
    FOC_FCF_B->Gain1_o = FOC_FCF_P.Gain1_Gain_a * FOC_FCF_B->Sign;

    /* Switch: '<S48>/Switch' */
    FOC_FCF_B->Switch_n = FOC_FCF_B->Gain1_o;
  } else {
    /* Switch: '<S48>/Switch' incorporates:
     *  Constant: '<S48>/Constant1'
     */
    FOC_FCF_B->Switch_n = FOC_FCF_P.Constant1_Value_e;
  }

  /* End of Switch: '<S48>/Switch' */

  /* Sum: '<S48>/Add1' */
  FOC_FCF_B->Add1_c = FOC_FCF_B->Add - FOC_FCF_B->Switch_n;

  /* Gain: '<S12>/Gain' */
  FOC_FCF_B->U_d1 = FOC_FCF_P.Gain_Gain_jm * FOC_FCF_B->SelectControlMode[0];

  /* Gain: '<S12>/Gain1' */
  FOC_FCF_B->U_q1 = FOC_FCF_P.Gain1_Gain_e * FOC_FCF_B->SelectControlMode[1];

  /* Gain: '<S12>/Gain2' */
  FOC_FCF_B->U_alpha1 = FOC_FCF_P.Gain2_Gain_f * FOC_FCF_B->Product_c0[0];

  /* Gain: '<S12>/Gain3' */
  FOC_FCF_B->U_beta1 = FOC_FCF_P.Gain3_Gain * FOC_FCF_B->Product_c0[1];

  /* Gain: '<S53>/DutyCycle_u1' */
  FOC_FCF_B->DutyCycle_u1 = FOC_FCF_P.DutyCycle_u1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[0];

  /* Gain: '<S53>/DutyCycle_u2' */
  FOC_FCF_B->DutyCycle_u2 = FOC_FCF_P.DutyCycle_u2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[0];

  /* Gain: '<S53>/DutyCycle_u3' */
  FOC_FCF_B->DutyCycle_u3 = FOC_FCF_P.DutyCycle_u3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[0];

  /* Gain: '<S53>/DutyCycle_v1' */
  FOC_FCF_B->DutyCycle_v1 = FOC_FCF_P.DutyCycle_v1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[1];

  /* Gain: '<S53>/DutyCycle_v2' */
  FOC_FCF_B->DutyCycle_v2 = FOC_FCF_P.DutyCycle_v2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[1];

  /* Gain: '<S53>/DutyCycle_v3' */
  FOC_FCF_B->DutyCycle_v3 = FOC_FCF_P.DutyCycle_v3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[1];

  /* Gain: '<S53>/DutyCycle_w1' */
  FOC_FCF_B->DutyCycle_w1 = FOC_FCF_P.DutyCycle_w1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[2];

  /* Gain: '<S53>/DutyCycle_w2' */
  FOC_FCF_B->DutyCycle_w2 = FOC_FCF_P.DutyCycle_w2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[2];

  /* Gain: '<S53>/DutyCycle_w3' */
  FOC_FCF_B->DutyCycle_w3 = FOC_FCF_P.DutyCycle_w3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[2];

  /* UnitDelay: '<S1>/FCF_Cnt' */
  FOC_FCF_B->FCF_Cnt = FOC_FCF_DW->FCF_Cnt_DSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Counter_Start'
   */
  FOC_FCF_B->Sum_o = FOC_FCF_P.Counter_Start_Value + FOC_FCF_B->FCF_Cnt;

  /* Update for Memory: '<S45>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput = FOC_FCF_B->Logic[0];

  /* Update for UnitDelay: '<S44>/Delay Input1'
   *
   * Block description for '<S44>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE = FOC_FCF_B->Compare_n;

  /* Update for Memory: '<S46>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_o = FOC_FCF_B->Logic_g[0];

  /* Update for UnitDelay: '<S39>/Delay Input1'
   *
   * Block description for '<S39>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE_c = FOC_FCF_B->Compare_l;

  /* Update for Memory: '<S40>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_p = FOC_FCF_B->Logic_gq[0];

  /* Update for DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn' */
  tmp_0 = FOC_FCF_B->f_2_w_el;
  tmp_0 -= FOC_FCF_P.DiscreteTransferFcn_DenCoef[1] *
    FOC_FCF_DW->DiscreteTransferFcn_states;
  tmp_0 /= FOC_FCF_P.DiscreteTransferFcn_DenCoef[0];
  FOC_FCF_DW->DiscreteTransferFcn_states = tmp_0;

  /* Update for UnitDelay: '<S48>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_B->Add1_c;

  /* Update for UnitDelay: '<S16>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_B->Sum2_e;

  /* Update for UnitDelay: '<S15>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_B->Sum3;

  /* Update for UnitDelay: '<S13>/Unit Delay3' */
  FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_B->Sum6;

  /* Update for UnitDelay: '<S10>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_B->Add1_j;

  /* Update for UnitDelay: '<S37>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_f = FOC_FCF_B->Add1;

  /* Update for UnitDelay: '<S26>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_B->IntegStopSwitch2[0];

  /* Update for UnitDelay: '<S30>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[0] = FOC_FCF_B->IntegStopSwitch2_o[0];

  /* Update for UnitDelay: '<S34>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_h[0] = FOC_FCF_B->IntegStopSwitch2_h[0];

  /* Update for UnitDelay: '<S26>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_B->IntegStopSwitch2[1];

  /* Update for UnitDelay: '<S30>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[1] = FOC_FCF_B->IntegStopSwitch2_o[1];

  /* Update for UnitDelay: '<S34>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_h[1] = FOC_FCF_B->IntegStopSwitch2_h[1];

  /* Update for UnitDelay: '<S17>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_B->Sum2_j;

  /* Update for DiscreteFir: '<S22>/Discrete FIR Filter 20th order' */
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

  /* End of Update for DiscreteFir: '<S22>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S23>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m--;
  if (FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m < 0) {
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m = 18;
  }

  /* Update circular buffer */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0];
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m + 19] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];

  /* End of Update for DiscreteFir: '<S23>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c--;
  if (FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c < 0) {
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c = 18;
  }

  /* Update for UnitDelay: '<S1>/FCF_Cnt' */
  /* Update circular buffer */
  FOC_FCF_DW->FCF_Cnt_DSTATE = FOC_FCF_B->Sum_o;

  /* Update for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */

  /* Outport: '<Root>/I_dq_Act [A]' */
  FOC_FCF_Y->I_dq_ActA[0] = FOC_FCF_B->I_dq1_Act_filt[0];
  FOC_FCF_Y->I_dq_ActA[2] = FOC_FCF_B->DiscreteFIRFilter20thorder[0];
  FOC_FCF_Y->I_dq_ActA[4] = FOC_FCF_B->DiscreteFIRFilter20thorder_l[0];

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Update for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c + 19] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */

  /* Outport: '<Root>/I_dq_Act [A]' */
  FOC_FCF_Y->I_dq_ActA[1] = FOC_FCF_B->I_dq1_Act_filt[1];
  FOC_FCF_Y->I_dq_ActA[3] = FOC_FCF_B->DiscreteFIRFilter20thorder[1];
  FOC_FCF_Y->I_dq_ActA[5] = FOC_FCF_B->DiscreteFIRFilter20thorder_l[1];

  /* Outport: '<Root>/ModInd' */
  FOC_FCF_Y->ModInd[0] = FOC_FCF_B->ModInd[0];
  FOC_FCF_Y->ModInd[1] = FOC_FCF_B->ModInd[1];
  FOC_FCF_Y->ModInd[2] = FOC_FCF_B->ModInd[2];

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
    /* InitializeConditions for Memory: '<S45>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput = FOC_FCF_P.SRFlipFlop_initial_condition;

    /* InitializeConditions for UnitDelay: '<S44>/Delay Input1'
     *
     * Block description for '<S44>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE = FOC_FCF_P.DetectRisePositive_vinit;

    /* InitializeConditions for Memory: '<S46>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_o = FOC_FCF_P.SRFlipFlop1_initial_condition;

    /* InitializeConditions for UnitDelay: '<S39>/Delay Input1'
     *
     * Block description for '<S39>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE_c = FOC_FCF_P.DetectRisePositive_vinit_o;

    /* InitializeConditions for Memory: '<S40>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_p =
      FOC_FCF_P.SRFlipFlop_initial_condition_a;

    /* InitializeConditions for DiscreteTransferFcn: '<S11>/Discrete Transfer Fcn' */
    FOC_FCF_DW->DiscreteTransferFcn_states =
      FOC_FCF_P.DiscreteTransferFcn_InitialStat;

    /* InitializeConditions for UnitDelay: '<S48>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_P.UnitDelay_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S16>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_P.FOC_AngleObs_w_InitVal;

    /* InitializeConditions for UnitDelay: '<S15>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_P.UnitDelay_InitialCondition_b;

    /* InitializeConditions for UnitDelay: '<S13>/Unit Delay3' */
    FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_P.UnitDelay3_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S10>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_P.UnitDelay_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S37>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_f = FOC_FCF_P.UnitDelay_InitialCondition_d;

    /* InitializeConditions for UnitDelay: '<S26>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S30>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[0] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S34>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_h[0] =
      FOC_FCF_P.IntegDelay1_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S26>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S30>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[1] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S34>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_h[1] =
      FOC_FCF_P.IntegDelay1_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S17>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_P.UnitDelay1_InitialCondition;

    /* InitializeConditions for DiscreteFir: '<S22>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_circ = 0;

    /* InitializeConditions for DiscreteFir: '<S23>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m = 0;

    /* InitializeConditions for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c = 0;
    for (i = 0; i < 38; i++) {
      /* InitializeConditions for DiscreteFir: '<S22>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_Init;

      /* InitializeConditions for DiscreteFir: '<S23>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_In_k;

      /* InitializeConditions for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_In_n;
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
