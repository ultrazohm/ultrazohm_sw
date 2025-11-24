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
 * C/C++ source code generated on : Mon Nov 24 14:15:51 2025
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
  boolean_T tmp_1;
  boolean_T tmp_idx_1;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
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

  /* RelationalOperator: '<S33>/Compare' incorporates:
   *  Constant: '<S33>/Constant'
   */
  FOC_FCF_B->Compare_b = (FOC_FCF_B->U_DC_fcf <
    FOC_FCF_P.FOC_LIMIT_Undervoltage_U_DC);

  /* Logic: '<S1>/Logical Operator1' incorporates:
   *  Constant: '<S1>/Enable'
   */
  FOC_FCF_B->LogicalOperator1 = ((FOC_FCF_P.FOC_Enable != 0.0F) &&
    (FOC_FCF_U->FOC_Enable != 0.0F));

  /* Logic: '<S7>/Logical Operator2' */
  FOC_FCF_B->LogicalOperator2 = (FOC_FCF_B->Compare_b &&
    FOC_FCF_B->LogicalOperator1);

  /* MultiPortSwitch: '<S7>/Selectphicalc3' incorporates:
   *  Constant: '<S7>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Undervoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S7>/Selectphicalc3' incorporates:
     *  Constant: '<S7>/Constant2'
     */
    FOC_FCF_B->Selectphicalc3 = FOC_FCF_P.Constant2_Value_j;
  } else {
    /* Logic: '<S7>/Logical Operator1' */
    FOC_FCF_B->LogicalOperator1_o = !FOC_FCF_B->LogicalOperator1;

    /* MultiPortSwitch: '<S7>/Selectphicalc3' */
    FOC_FCF_B->Selectphicalc3 = FOC_FCF_B->LogicalOperator1_o;
  }

  /* End of MultiPortSwitch: '<S7>/Selectphicalc3' */

  /* Memory: '<S36>/Memory' */
  FOC_FCF_B->Memory = FOC_FCF_DW->Memory_PreviousInput;

  /* CombinatorialLogic: '<S36>/Logic' */
  tmp_1 = FOC_FCF_B->LogicalOperator2;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc3;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic[0U] = FOC_FCF_P.Logic_table[(uint32_T)i];
  FOC_FCF_B->Logic[1U] = FOC_FCF_P.Logic_table[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S7>/Selectphicalc1' incorporates:
   *  Constant: '<S7>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Undervoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S7>/Selectphicalc1' incorporates:
     *  Constant: '<S7>/Constant3'
     */
    FOC_FCF_B->Selectphicalc1 = FOC_FCF_P.Constant3_Value_i;
  } else {
    /* MultiPortSwitch: '<S7>/Selectphicalc1' */
    FOC_FCF_B->Selectphicalc1 = FOC_FCF_B->Logic[1];
  }

  /* End of MultiPortSwitch: '<S7>/Selectphicalc1' */

  /* RelationalOperator: '<S34>/Compare' incorporates:
   *  Constant: '<S34>/Constant'
   */
  FOC_FCF_B->Compare_br = (FOC_FCF_B->U_DC_fcf >
    FOC_FCF_P.FOC_LIMIT_Overvoltage_U_DC);

  /* RelationalOperator: '<S38>/Compare' incorporates:
   *  Constant: '<S38>/Constant'
   *  Constant: '<S7>/Reset_OV_Error'
   */
  FOC_FCF_B->Compare_n = (FOC_FCF_P.FOC_RESET_OV_Error >
    FOC_FCF_P.Constant_Value_o);

  /* UnitDelay: '<S35>/Delay Input1'
   *
   * Block description for '<S35>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1 = FOC_FCF_DW->DelayInput1_DSTATE;

  /* MultiPortSwitch: '<S7>/Selectphicalc4' incorporates:
   *  Constant: '<S7>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overvoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S7>/Selectphicalc4' incorporates:
     *  Constant: '<S7>/Constant4'
     */
    FOC_FCF_B->Selectphicalc4 = FOC_FCF_P.Constant4_Value_b;
  } else {
    /* RelationalOperator: '<S35>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator = ((int32_T)FOC_FCF_B->Compare_n >
      (int32_T)FOC_FCF_B->Uk1);

    /* MultiPortSwitch: '<S7>/Selectphicalc4' */
    FOC_FCF_B->Selectphicalc4 = FOC_FCF_B->FixPtRelationalOperator;
  }

  /* End of MultiPortSwitch: '<S7>/Selectphicalc4' */

  /* Memory: '<S37>/Memory' */
  FOC_FCF_B->Memory_k = FOC_FCF_DW->Memory_PreviousInput_o;

  /* CombinatorialLogic: '<S37>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_br;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc4;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_k;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_g[0U] = FOC_FCF_P.Logic_table_m[(uint32_T)i];
  FOC_FCF_B->Logic_g[1U] = FOC_FCF_P.Logic_table_m[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S7>/Selectphicalc2' incorporates:
   *  Constant: '<S7>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overvoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S7>/Selectphicalc2' incorporates:
     *  Constant: '<S7>/Constant1'
     */
    FOC_FCF_B->Selectphicalc2_m = FOC_FCF_P.Constant1_Value_j;
  } else {
    /* MultiPortSwitch: '<S7>/Selectphicalc2' */
    FOC_FCF_B->Selectphicalc2_m = FOC_FCF_B->Logic_g[1];
  }

  /* End of MultiPortSwitch: '<S7>/Selectphicalc2' */

  /* Logic: '<S7>/Logical Operator' */
  FOC_FCF_B->LogicalOperator = (FOC_FCF_B->Selectphicalc1 &&
    FOC_FCF_B->Selectphicalc2_m);
  for (i = 0; i < 6; i++) {
    /* Abs: '<S6>/Abs' */
    FOC_FCF_B->Abs[i] = fabsf(FOC_FCF_U->I_phA[i]);
  }

  /* MinMax: '<S6>/MinMax' incorporates:
   *  Abs: '<S6>/Abs'
   */
  tmp_0 = FOC_FCF_B->Abs[0];
  for (i = 0; i < 5; i++) {
    tmp_0 = fmaxf(tmp_0, FOC_FCF_B->Abs[i + 1]);
  }

  /* MinMax: '<S6>/MinMax' */
  FOC_FCF_B->MinMax = tmp_0;

  /* RelationalOperator: '<S29>/Compare' incorporates:
   *  Constant: '<S29>/Constant'
   */
  FOC_FCF_B->Compare_a = (FOC_FCF_B->MinMax >=
    FOC_FCF_P.FOC_LIMIT_Overcurrent_I_uvw);

  /* RelationalOperator: '<S32>/Compare' incorporates:
   *  Constant: '<S32>/Constant'
   *  Constant: '<S6>/Reset_OC_Error'
   */
  FOC_FCF_B->Compare_l = (FOC_FCF_P.FOC_RESET_OC_Error >
    FOC_FCF_P.Constant_Value);

  /* UnitDelay: '<S30>/Delay Input1'
   *
   * Block description for '<S30>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1_k = FOC_FCF_DW->DelayInput1_DSTATE_c;

  /* MultiPortSwitch: '<S6>/Selectphicalc2' incorporates:
   *  Constant: '<S6>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overcurrent_I_uvw == 0) {
    /* MultiPortSwitch: '<S6>/Selectphicalc2' incorporates:
     *  Constant: '<S6>/Constant1'
     */
    FOC_FCF_B->Selectphicalc2_i = FOC_FCF_P.Constant1_Value_gm;
  } else {
    /* RelationalOperator: '<S30>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator_e = ((int32_T)FOC_FCF_B->Compare_l >
      (int32_T)FOC_FCF_B->Uk1_k);

    /* MultiPortSwitch: '<S6>/Selectphicalc2' */
    FOC_FCF_B->Selectphicalc2_i = FOC_FCF_B->FixPtRelationalOperator_e;
  }

  /* End of MultiPortSwitch: '<S6>/Selectphicalc2' */

  /* Memory: '<S31>/Memory' */
  FOC_FCF_B->Memory_p = FOC_FCF_DW->Memory_PreviousInput_p;

  /* CombinatorialLogic: '<S31>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_a;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_i;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_p;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_gq[0U] = FOC_FCF_P.Logic_table_f[(uint32_T)i];
  FOC_FCF_B->Logic_gq[1U] = FOC_FCF_P.Logic_table_f[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S6>/Selectphicalc1' incorporates:
   *  Constant: '<S6>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overcurrent_I_uvw == 0) {
    /* MultiPortSwitch: '<S6>/Selectphicalc1' incorporates:
     *  Constant: '<S6>/Constant2'
     */
    FOC_FCF_B->Selectphicalc1_j = FOC_FCF_P.Constant2_Value_o;
  } else {
    /* MultiPortSwitch: '<S6>/Selectphicalc1' */
    FOC_FCF_B->Selectphicalc1_j = FOC_FCF_B->Logic_gq[1];
  }

  /* End of MultiPortSwitch: '<S6>/Selectphicalc1' */

  /* Logic: '<S1>/Logical Operator' */
  FOC_FCF_B->LogicalOperator_n = (FOC_FCF_B->LogicalOperator &&
    FOC_FCF_B->LogicalOperator1 && FOC_FCF_B->Selectphicalc1_j);

  /* Switch: '<S1>/Switch' */
  if (FOC_FCF_B->LogicalOperator_n) {
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

    /* Switch: '<S1>/Switch' */
    FOC_FCF_B->FOC_Mode_after_checks = FOC_FCF_B->ModeSwitch;
  } else {
    /* Switch: '<S1>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    FOC_FCF_B->FOC_Mode_after_checks = FOC_FCF_P.Constant1_Value;
  }

  /* End of Switch: '<S1>/Switch' */

  /* DiscreteTransferFcn: '<S9>/Discrete Transfer Fcn' */
  tmp_0 = FOC_FCF_P.DiscreteTransferFcn_NumCoef *
    FOC_FCF_DW->DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S9>/Discrete Transfer Fcn' */
  FOC_FCF_B->DiscreteTransferFcn = tmp_0;

  /* Gain: '<S9>/f_2_w_el' incorporates:
   *  Constant: '<S9>/Uf_w_el'
   */
  FOC_FCF_B->f_2_w_el = FOC_FCF_P.f_2_w_el_Gain * FOC_FCF_P.FOC_Uf_f_el;

  /* Product: '<S39>/Product' incorporates:
   *  Constant: '<S39>/FOC_T_fast'
   */
  FOC_FCF_B->Product = FOC_FCF_B->f_2_w_el * FOC_FCF_P.FOC_T_fast_Value;

  /* UnitDelay: '<S39>/Unit Delay' */
  FOC_FCF_B->UnitDelay = FOC_FCF_DW->UnitDelay_DSTATE;

  /* Sum: '<S39>/Add' */
  FOC_FCF_B->Add = FOC_FCF_B->Product + FOC_FCF_B->UnitDelay;

  /* Gain: '<S19>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[0];
  I_phA = FOC_FCF_U->I_phA[1];
  I_phA_0 = FOC_FCF_U->I_phA[2];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S19>/TrafoMatrix uvw->alphabeta' */
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

  /* UnitDelay: '<S14>/Unit Delay1' */
  FOC_FCF_B->w_el = FOC_FCF_DW->UnitDelay1_DSTATE;

  /* Gain: '<S11>/DeadTimeCompensation' */
  FOC_FCF_B->DeadTimeCompensation = FOC_FCF_P.FOC_PhiSensorTdead *
    FOC_FCF_B->w_el;

  /* Sum: '<S11>/Sum3' */
  FOC_FCF_B->Sum3 = FOC_FCF_B->Sum1 + FOC_FCF_B->DeadTimeCompensation;

  /* UnitDelay: '<S13>/Unit Delay' */
  FOC_FCF_B->UnitDelay_l = FOC_FCF_DW->UnitDelay_DSTATE_h;

  /* Sum: '<S13>/Sum' */
  FOC_FCF_B->Sum = FOC_FCF_B->Sum3 - FOC_FCF_B->UnitDelay_l;

  /* RelationalOperator: '<S13>/Sprung?' incorporates:
   *  Constant: '<S13>/Constant3'
   */
  FOC_FCF_B->Sprung = (FOC_FCF_B->Sum < FOC_FCF_P.Constant3_Value);

  /* Switch: '<S13>/Switch' */
  if (FOC_FCF_B->Sprung) {
    /* Switch: '<S13>/Switch' incorporates:
     *  Constant: '<S13>/Constant2'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant2_Value;
  } else {
    /* Switch: '<S13>/Switch' incorporates:
     *  Constant: '<S13>/Constant4'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant4_Value;
  }

  /* End of Switch: '<S13>/Switch' */

  /* RelationalOperator: '<S13>/Sprung?1' incorporates:
   *  Constant: '<S13>/Constant1'
   */
  FOC_FCF_B->Sprung1 = (FOC_FCF_B->Sum > FOC_FCF_P.Constant1_Value_ep);

  /* Switch: '<S13>/Switch1' */
  if (FOC_FCF_B->Sprung1) {
    /* Switch: '<S13>/Switch1' incorporates:
     *  Constant: '<S13>/Constant5'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant5_Value;
  } else {
    /* Switch: '<S13>/Switch1' incorporates:
     *  Constant: '<S13>/Constant6'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant6_Value;
  }

  /* End of Switch: '<S13>/Switch1' */

  /* Sum: '<S13>/Sum2' */
  FOC_FCF_B->Sum2 = FOC_FCF_B->Switch + FOC_FCF_B->Switch1;

  /* UnitDelay: '<S11>/Unit Delay3' */
  FOC_FCF_B->UnitDelay3 = FOC_FCF_DW->UnitDelay3_DSTATE;

  /* Sum: '<S11>/Sum7' */
  FOC_FCF_B->phi_el_observer = FOC_FCF_B->UnitDelay3 - FOC_FCF_B->Sum2;

  /* Product: '<S8>/Product' incorporates:
   *  Constant: '<S8>/FOC_T_fast'
   */
  FOC_FCF_B->Product_e = FOC_FCF_U->w_el_Ref_IfStarter *
    FOC_FCF_P.FOC_T_fast_Value_d;

  /* UnitDelay: '<S8>/Unit Delay' */
  FOC_FCF_B->UnitDelay_a = FOC_FCF_DW->UnitDelay_DSTATE_p;

  /* Sum: '<S8>/Add' */
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

    /* Switch: '<S12>/Switch1' */
    if (FOC_FCF_B->Selectphicalc2 > FOC_FCF_P.Switch1_Threshold) {
      /* Sum: '<S12>/Sum2' incorporates:
       *  Constant: '<S12>/Constant'
       */
      FOC_FCF_B->Sum2_l = FOC_FCF_B->Selectphicalc2 - FOC_FCF_P.Constant_Value_e;

      /* Switch: '<S12>/Switch1' */
      FOC_FCF_B->Switch1_d = FOC_FCF_B->Sum2_l;
    } else {
      /* Switch: '<S12>/Switch1' */
      FOC_FCF_B->Switch1_d = FOC_FCF_B->Selectphicalc2;
    }

    /* End of Switch: '<S12>/Switch1' */

    /* Switch: '<S12>/Switch2' */
    if (FOC_FCF_B->Switch1_d > FOC_FCF_P.Switch2_Threshold) {
      /* Switch: '<S12>/Switch2' */
      FOC_FCF_B->Switch2_f = FOC_FCF_B->Switch1_d;
    } else {
      /* Sum: '<S12>/Sum3' incorporates:
       *  Constant: '<S12>/Constant1'
       */
      FOC_FCF_B->Sum3_h = FOC_FCF_B->Switch1_d + FOC_FCF_P.Constant1_Value_g;

      /* Switch: '<S12>/Switch2' */
      FOC_FCF_B->Switch2_f = FOC_FCF_B->Sum3_h;
    }

    /* End of Switch: '<S12>/Switch2' */

    /* MultiPortSwitch: '<S1>/Use_If_Starter' */
    FOC_FCF_B->phi_el_I_trafo = FOC_FCF_B->Switch2_f;
  } else {
    /* MultiPortSwitch: '<S1>/Use_If_Starter' */
    FOC_FCF_B->phi_el_I_trafo = FOC_FCF_B->Add_m;
  }

  /* End of MultiPortSwitch: '<S1>/Use_If_Starter' */

  /* Trigonometry: '<S19>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1 = cosf(FOC_FCF_B->phi_el_I_trafo);

  /* Product: '<S19>/TrafoProd' */
  FOC_FCF_B->TrafoProd = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction1;

  /* Trigonometry: '<S19>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction = sinf(FOC_FCF_B->phi_el_I_trafo);

  /* Product: '<S19>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3 = FOC_FCF_B->TrigonometricFunction *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Sum: '<S19>/I_d1_Act' */
  FOC_FCF_B->I_d1_Act = FOC_FCF_B->TrafoProd + FOC_FCF_B->TrafoProd3;

  /* Product: '<S19>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1 = FOC_FCF_B->TrigonometricFunction1 *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Product: '<S19>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2 = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction;

  /* Sum: '<S19>/TrafoSum1' */
  FOC_FCF_B->I_q1_Act = FOC_FCF_B->TrafoProd1 - FOC_FCF_B->TrafoProd2;

  /* SignalConversion generated from: '<S19>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0] = FOC_FCF_B->I_d1_Act;
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1] = FOC_FCF_B->I_q1_Act;

  /* Sum: '<S17>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S22>/KP*e[k]1' incorporates:
   *  Constant: '<S22>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S22>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[0] = FOC_FCF_DW->IntegDelay1_DSTATE[0];

  /* Sum: '<S17>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S22>/KP*e[k]1' incorporates:
   *  Constant: '<S22>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S22>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[1] = FOC_FCF_DW->IntegDelay1_DSTATE[1];

  /* Product: '<S22>/Product1' incorporates:
   *  Constant: '<S22>/FOC_KI'
   *  Constant: '<S22>/FOC_T_fast'
   */
  FOC_FCF_B->Product1 = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_n;

  /* Switch: '<S22>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Product: '<S22>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1[0] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[0] = tmp_0;

    /* Sum: '<S22>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1[0];
    FOC_FCF_B->IntSum1_p[0] = tmp_0;

    /* Switch: '<S22>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1[0] = tmp_0;

    /* Product: '<S22>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1[1] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[1] = tmp_0;

    /* Sum: '<S22>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1[1];
    FOC_FCF_B->IntSum1_p[1] = tmp_0;

    /* Switch: '<S22>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1[1] = tmp_0;
  } else {
    /* Switch: '<S22>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S22>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1[0] = FOC_FCF_P.Zero_Value;
    FOC_FCF_B->IntegEnaSwitch1[1] = FOC_FCF_P.Zero_Value;
  }

  /* End of Switch: '<S22>/IntegEnaSwitch1' */

  /* Gain: '<S20>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[3];
  I_phA = FOC_FCF_U->I_phA[4];
  I_phA_0 = FOC_FCF_U->I_phA[5];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S20>/TrafoMatrix uvw->alphabeta' */
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

  /* Trigonometry: '<S20>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_b = cosf(FOC_FCF_B->Sum1_d);

  /* Product: '<S20>/TrafoProd' */
  FOC_FCF_B->TrafoProd_a = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction1_b;

  /* Trigonometry: '<S20>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_l = sinf(FOC_FCF_B->Sum1_d);

  /* Product: '<S20>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3_i = FOC_FCF_B->TrigonometricFunction_l *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Sum: '<S20>/TrafoSum' */
  FOC_FCF_B->TrafoSum = FOC_FCF_B->TrafoProd_a + FOC_FCF_B->TrafoProd3_i;

  /* Product: '<S20>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1_b = FOC_FCF_B->TrigonometricFunction1_b *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Product: '<S20>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2_b = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction_l;

  /* Sum: '<S20>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1 = FOC_FCF_B->TrafoProd1_b - FOC_FCF_B->TrafoProd2_b;

  /* SignalConversion generated from: '<S20>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0] = FOC_FCF_B->TrafoSum;
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1] = FOC_FCF_B->TrafoSum1;

  /* Sum: '<S18>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S26>/KP*e[k]1' incorporates:
   *  Constant: '<S26>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S26>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[0] = FOC_FCF_DW->IntegDelay1_DSTATE_p[0];

  /* Sum: '<S18>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S26>/KP*e[k]1' incorporates:
   *  Constant: '<S26>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S26>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[1] = FOC_FCF_DW->IntegDelay1_DSTATE_p[1];

  /* Product: '<S26>/Product1' incorporates:
   *  Constant: '<S26>/FOC_KI'
   *  Constant: '<S26>/FOC_T_fast'
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

  /* Switch: '<S16>/Switch1' */
  if (FOC_FCF_B->Sum_k > FOC_FCF_P.Switch1_Threshold_a) {
    /* Sum: '<S16>/Sum2' incorporates:
     *  Constant: '<S16>/Constant'
     */
    FOC_FCF_B->Sum2_ez = FOC_FCF_B->Sum_k - FOC_FCF_P.Constant_Value_n;

    /* Switch: '<S16>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum2_ez;
  } else {
    /* Switch: '<S16>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum_k;
  }

  /* End of Switch: '<S16>/Switch1' */

  /* Switch: '<S16>/Switch2' */
  if (FOC_FCF_B->Switch1_k > FOC_FCF_P.Switch2_Threshold_o) {
    /* Switch: '<S16>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Switch1_k;
  } else {
    /* Sum: '<S16>/Sum3' incorporates:
     *  Constant: '<S16>/Constant1'
     */
    FOC_FCF_B->Sum3_d = FOC_FCF_B->Switch1_k + FOC_FCF_P.Constant1_Value_d;

    /* Switch: '<S16>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Sum3_d;
  }

  /* End of Switch: '<S16>/Switch2' */

  /* Sum: '<S4>/Sum2' incorporates:
   *  Constant: '<S4>/FOC_6ph_AngleShift'
   */
  FOC_FCF_B->Sum2_p = FOC_FCF_B->Switch2 + FOC_FCF_P.FOC_6ph_AngleShift;

  /* MultiPortSwitch: '<S1>/SelectControlMode' */
  switch ((int32_T)FOC_FCF_B->FOC_Mode_after_checks) {
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
    /* Gain: '<S40>/Gain' */
    FOC_FCF_B->Gain_fw = FOC_FCF_P.FOC_Uf_m * FOC_FCF_B->DiscreteTransferFcn;

    /* Signum: '<S40>/Sign' */
    tmp_0 = FOC_FCF_B->Gain_fw;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S40>/Sign' */
      FOC_FCF_B->Sign_p = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S40>/Sign' */
      FOC_FCF_B->Sign_p = -1.0F;
    } else {
      /* Signum: '<S40>/Sign' */
      FOC_FCF_B->Sign_p = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S40>/Sign' */

    /* Abs: '<S40>/Abs' */
    FOC_FCF_B->Abs_d = fabsf(FOC_FCF_B->Gain_fw);

    /* Saturate: '<S40>/Saturation1' */
    if (FOC_FCF_B->Abs_d > FOC_FCF_P.FOC_Uf_U_max) {
      /* Saturate: '<S40>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_max;
    } else if (FOC_FCF_B->Abs_d < FOC_FCF_P.FOC_Uf_U_min) {
      /* Saturate: '<S40>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_min;
    } else {
      /* Saturate: '<S40>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_B->Abs_d;
    }

    /* End of Saturate: '<S40>/Saturation1' */

    /* Product: '<S40>/Product' */
    FOC_FCF_B->Product_j = FOC_FCF_B->Saturation1 * FOC_FCF_B->Sign_p;

    /* Sum: '<S9>/Sum1' incorporates:
     *  Constant: '<S9>/FOC_6ph_AngleShift'
     */
    FOC_FCF_B->Sum1_n = FOC_FCF_B->Add + FOC_FCF_P.FOC_6ph_AngleShift;

    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S9>/Uf_Ud'
     */
    FOC_FCF_B->SelectControlMode[0] = FOC_FCF_P.FOC_Uf_Ud;
    FOC_FCF_B->SelectControlMode[1] = FOC_FCF_B->Product_j;
    FOC_FCF_B->SelectControlMode[2] = FOC_FCF_P.FOC_Uf_Ud;
    FOC_FCF_B->SelectControlMode[3] = FOC_FCF_B->Product_j;
    FOC_FCF_B->SelectControlMode[4] = FOC_FCF_B->Add;
    FOC_FCF_B->SelectControlMode[5] = FOC_FCF_B->Sum1_n;
    break;

   default:
    /* Switch: '<S26>/IntegEnaSwitch1' */
    if (FOC_FCF_B->LogicalOperator1) {
      /* Product: '<S26>/Product2' */
      tmp_0 = FOC_FCF_B->IntegDelay1_o[0] * FOC_FCF_B->Product1_k;
      FOC_FCF_B->Product2_b[0] = tmp_0;

      /* Sum: '<S26>/IntSum1' */
      tmp_0 += FOC_FCF_B->KPek1_l[0];
      FOC_FCF_B->IntSum1[0] = tmp_0;

      /* Switch: '<S26>/IntegEnaSwitch1' */
      FOC_FCF_B->IntegEnaSwitch1_n[0] = tmp_0;

      /* Product: '<S26>/Product2' */
      tmp_0 = FOC_FCF_B->IntegDelay1_o[1] * FOC_FCF_B->Product1_k;
      FOC_FCF_B->Product2_b[1] = tmp_0;

      /* Sum: '<S26>/IntSum1' */
      tmp_0 += FOC_FCF_B->KPek1_l[1];
      FOC_FCF_B->IntSum1[1] = tmp_0;

      /* Switch: '<S26>/IntegEnaSwitch1' */
      FOC_FCF_B->IntegEnaSwitch1_n[1] = tmp_0;
    } else {
      /* Switch: '<S26>/IntegEnaSwitch1' incorporates:
       *  Constant: '<S26>/Zero'
       */
      FOC_FCF_B->IntegEnaSwitch1_n[0] = FOC_FCF_P.Zero_Value_o;
      FOC_FCF_B->IntegEnaSwitch1_n[1] = FOC_FCF_P.Zero_Value_o;
    }

    /* End of Switch: '<S26>/IntegEnaSwitch1' */

    /* MultiPortSwitch: '<S1>/SelectControlMode' */
    FOC_FCF_B->SelectControlMode[0] = FOC_FCF_B->IntegEnaSwitch1[0];
    FOC_FCF_B->SelectControlMode[2] = FOC_FCF_B->IntegEnaSwitch1_n[0];
    FOC_FCF_B->SelectControlMode[1] = FOC_FCF_B->IntegEnaSwitch1[1];
    FOC_FCF_B->SelectControlMode[3] = FOC_FCF_B->IntegEnaSwitch1_n[1];
    FOC_FCF_B->SelectControlMode[4] = FOC_FCF_B->Switch2;
    FOC_FCF_B->SelectControlMode[5] = FOC_FCF_B->Sum2_p;
    break;
  }

  /* End of MultiPortSwitch: '<S1>/SelectControlMode' */

  /* Trigonometry: '<S47>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_n = sinf(FOC_FCF_B->SelectControlMode[4]);

  /* Trigonometry: '<S47>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_j = cosf(FOC_FCF_B->SelectControlMode[4]);

  /* Gain: '<S47>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[0] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S47>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[0] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S47>/Sum1' incorporates:
   *  Gain: '<S47>/Gain'
   *  Gain: '<S47>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[0] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S47>/Product' incorporates:
   *  Sum: '<S47>/Sum1'
   */
  I_phA_0 = Sum1_f;

  /* Gain: '<S47>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[1] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S47>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[1] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S47>/Sum1' incorporates:
   *  Gain: '<S47>/Gain'
   *  Gain: '<S47>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[1] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S47>/Product' incorporates:
   *  Sum: '<S47>/Sum1'
   */
  tmp_0 = Sum1_f;

  /* Gain: '<S47>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[2] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S47>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[2] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S47>/Sum1' incorporates:
   *  Gain: '<S47>/Gain'
   *  Gain: '<S47>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[2] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S47>/Product' incorporates:
   *  Sum: '<S47>/Sum1'
   */
  I_phA = Sum1_f;

  /* Gain: '<S47>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[3] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S47>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[3] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S47>/Sum1' incorporates:
   *  Gain: '<S47>/Gain'
   *  Gain: '<S47>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[3] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S47>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[0];
  Gain = FOC_FCF_B->SelectControlMode[1];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S47>/Product' */
  FOC_FCF_B->Product_c0[0] = I_phA_0;

  /* Product: '<S47>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_f * Gain;

  /* Product: '<S47>/Product' */
  FOC_FCF_B->Product_c0[1] = I_phA_0;

  /* Product: '<S45>/Product' incorporates:
   *  Constant: '<S45>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_d[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_c0[0];
  Gain = FOC_FCF_B->Product_c0[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    I_phA_0 = tmp[i_0] * TrafoMatrixuvwalphabeta;
    I_phA_0 += tmp[i_0 + 3] * Gain;

    /* Product: '<S45>/Product' */
    FOC_FCF_B->U_uvw1[i_0] = I_phA_0;
  }

  /* End of Product: '<S45>/Product' */

  /* Trigonometry: '<S48>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_j = sinf(FOC_FCF_B->SelectControlMode[5]);

  /* Trigonometry: '<S48>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_h = cosf(FOC_FCF_B->SelectControlMode[5]);

  /* Gain: '<S48>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_c[0] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S48>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[0] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S48>/Sum1' incorporates:
   *  Gain: '<S48>/Gain'
   *  Gain: '<S48>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[0] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S48>/Product' incorporates:
   *  Sum: '<S48>/Sum1'
   */
  I_phA_0 = Sum1_f;

  /* Gain: '<S48>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_c[1] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S48>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[1] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S48>/Sum1' incorporates:
   *  Gain: '<S48>/Gain'
   *  Gain: '<S48>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[1] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S48>/Product' incorporates:
   *  Sum: '<S48>/Sum1'
   */
  tmp_0 = Sum1_f;

  /* Gain: '<S48>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_c[2] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S48>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[2] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S48>/Sum1' incorporates:
   *  Gain: '<S48>/Gain'
   *  Gain: '<S48>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[2] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S48>/Product' incorporates:
   *  Sum: '<S48>/Sum1'
   */
  I_phA = Sum1_f;

  /* Gain: '<S48>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_c[3] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S48>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[3] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S48>/Sum1' incorporates:
   *  Gain: '<S48>/Gain'
   *  Gain: '<S48>/Gain1'
   */
  Sum1_f = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[3] = Sum1_f;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S48>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[2];
  Gain = FOC_FCF_B->SelectControlMode[3];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S48>/Product' */
  FOC_FCF_B->Product_f[0] = I_phA_0;

  /* Product: '<S48>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_f * Gain;

  /* Product: '<S48>/Product' */
  FOC_FCF_B->Product_f[1] = I_phA_0;

  /* Product: '<S46>/Product' incorporates:
   *  Constant: '<S46>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_g[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_f[0];
  Gain = FOC_FCF_B->Product_f[1];

  /* Outputs for Atomic SubSystem: '<S10>/NormalizedVoltage' */
  /* Gain: '<S43>/U_DC//2' */
  FOC_FCF_B->U_DC2 = FOC_FCF_P.U_DC2_Gain_p * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S43>/AvoidDivBy0' incorporates:
   *  Constant: '<S43>/Constant2'
   */
  tmp_0 = fmaxf(FOC_FCF_P.Constant2_Value_g, FOC_FCF_B->U_DC2);

  /* MinMax: '<S43>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0 = tmp_0;
  for (i = 0; i < 3; i++) {
    /* Product: '<S46>/Product' */
    tmp_0 = tmp[i] * TrafoMatrixuvwalphabeta;
    tmp_0 += tmp[i + 3] * Gain;

    /* Product: '<S46>/Product' */
    FOC_FCF_B->Product_f3[i] = tmp_0;

    /* Product: '<S43>/DutyCycle_normalized' */
    FOC_FCF_B->DutyCycle_normed[i] = FOC_FCF_B->U_uvw1[i] /
      FOC_FCF_B->AvoidDivBy0;
    FOC_FCF_B->DutyCycle_normed[i + 3] = tmp_0 / FOC_FCF_B->AvoidDivBy0;
  }

  /* End of Outputs for SubSystem: '<S10>/NormalizedVoltage' */

  /* Outputs for Atomic SubSystem: '<S10>/Super_Sinus_Modulation' */
  /* MinMax: '<S44>/MinMax2' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[0];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[1]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S44>/MinMax2' */
  FOC_FCF_B->MinMax2 = tmp_0;

  /* MinMax: '<S44>/MinMax3' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[0];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[1]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S44>/MinMax3' */
  FOC_FCF_B->MinMax3 = tmp_0;

  /* Sum: '<S44>/Sum1' */
  FOC_FCF_B->Sum1_o = FOC_FCF_B->MinMax2 + FOC_FCF_B->MinMax3;

  /* Gain: '<S44>/Factor' */
  FOC_FCF_B->Factor = FOC_FCF_P.Factor_Gain * FOC_FCF_B->Sum1_o;

  /* Sum: '<S44>/DutyCycle_SuperSinus_1' */
  FOC_FCF_B->DutyCycle_SuperSinus_1[0] = FOC_FCF_B->DutyCycle_normed[0] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[1] = FOC_FCF_B->DutyCycle_normed[1] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[2] = FOC_FCF_B->DutyCycle_normed[2] -
    FOC_FCF_B->Factor;

  /* MinMax: '<S44>/MinMax1' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[3];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[4]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S44>/MinMax1' */
  FOC_FCF_B->MinMax1 = tmp_0;

  /* MinMax: '<S44>/MinMax4' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[3];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[4]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S44>/MinMax4' */
  FOC_FCF_B->MinMax4 = tmp_0;

  /* Sum: '<S44>/Sum2' */
  FOC_FCF_B->Sum2_i = FOC_FCF_B->MinMax1 + FOC_FCF_B->MinMax4;

  /* Gain: '<S44>/Factor1' */
  FOC_FCF_B->Factor1 = FOC_FCF_P.Factor1_Gain * FOC_FCF_B->Sum2_i;

  /* Sum: '<S44>/DutyCycle_SuperSinus_2' */
  FOC_FCF_B->DutyCycle_SuperSinus_2[0] = FOC_FCF_B->DutyCycle_normed[3] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[1] = FOC_FCF_B->DutyCycle_normed[4] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[2] = FOC_FCF_B->DutyCycle_normed[5] -
    FOC_FCF_B->Factor1;

  /* End of Outputs for SubSystem: '<S10>/Super_Sinus_Modulation' */

  /* MultiPortSwitch: '<S10>/SelectModulation' incorporates:
   *  Constant: '<S10>/Enable_SuperSinMod'
   */
  if (FOC_FCF_P.FOC_SELECT_Modulation == 0) {
    /* MultiPortSwitch: '<S10>/SelectModulation' */
    for (i = 0; i < 6; i++) {
      FOC_FCF_B->SelMod_DutyCycles[i] = FOC_FCF_B->DutyCycle_normed[i];
    }
  } else {
    /* MultiPortSwitch: '<S10>/SelectModulation' */
    FOC_FCF_B->SelMod_DutyCycles[0] = FOC_FCF_B->DutyCycle_SuperSinus_1[0];
    FOC_FCF_B->SelMod_DutyCycles[3] = FOC_FCF_B->DutyCycle_SuperSinus_2[0];
    FOC_FCF_B->SelMod_DutyCycles[1] = FOC_FCF_B->DutyCycle_SuperSinus_1[1];
    FOC_FCF_B->SelMod_DutyCycles[4] = FOC_FCF_B->DutyCycle_SuperSinus_2[1];
    FOC_FCF_B->SelMod_DutyCycles[2] = FOC_FCF_B->DutyCycle_SuperSinus_1[2];
    FOC_FCF_B->SelMod_DutyCycles[5] = FOC_FCF_B->DutyCycle_SuperSinus_2[2];
  }

  /* End of MultiPortSwitch: '<S10>/SelectModulation' */

  /* Switch: '<S2>/ASC_Switch' */
  if (FOC_FCF_B->LogicalOperator1) {
    for (i = 0; i < 6; i++) {
      /* Bias: '<S41>/Scale [0..2]' */
      tmp_0 = FOC_FCF_B->SelMod_DutyCycles[i] + FOC_FCF_P.Scale02_Bias;
      FOC_FCF_B->Scale02[i] = tmp_0;

      /* Gain: '<S41>/Scale  [0..1]' */
      tmp_0 *= FOC_FCF_P.Scale01_Gain;
      FOC_FCF_B->Scale01[i] = tmp_0;

      /* Saturate: '<S41>/Limit [0..1]' */
      if (tmp_0 > FOC_FCF_P.Limit01_UpperSat) {
        /* Saturate: '<S41>/Limit [0..1]' */
        tmp_0 = FOC_FCF_P.Limit01_UpperSat;
      } else if (tmp_0 < FOC_FCF_P.Limit01_LowerSat) {
        /* Saturate: '<S41>/Limit [0..1]' */
        tmp_0 = FOC_FCF_P.Limit01_LowerSat;
      }

      /* End of Saturate: '<S41>/Limit [0..1]' */

      /* Saturate: '<S41>/Limit [0..1]' */
      FOC_FCF_B->Limit01[i] = tmp_0;

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

  /* Sum: '<S11>/Deviation' */
  FOC_FCF_B->Deviation = FOC_FCF_B->Sum3 - FOC_FCF_B->phi_el_observer;

  /* Product: '<S11>/Product2' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S11>/Constant1'
   */
  FOC_FCF_B->Product2 = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_D * FOC_FCF_B->Deviation;

  /* Gain: '<S11>/Gain' */
  FOC_FCF_B->Gain_g = FOC_FCF_P.Gain_Gain_k * FOC_FCF_B->Product2;

  /* Gain: '<S11>/Gain4' */
  FOC_FCF_B->winkelimpuls = FOC_FCF_P.FOC_OmegaObs3 * FOC_FCF_B->Deviation;

  /* Sum: '<S11>/Sum1' */
  FOC_FCF_B->Sum1_g4 = FOC_FCF_B->Gain_g + FOC_FCF_B->w_el;

  /* Product: '<S11>/Product' incorporates:
   *  Constant: '<S11>/FOC_T_fast'
   */
  FOC_FCF_B->Product_o = FOC_FCF_B->Sum1_g4 * FOC_FCF_P.FOC_T_fast_Value_df;

  /* Product: '<S11>/Product1' incorporates:
   *  Constant: '<S11>/Constant'
   */
  FOC_FCF_B->Product1_b = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_w0 * FOC_FCF_B->Deviation;

  /* UnitDelay: '<S15>/Unit Delay1' */
  FOC_FCF_B->UnitDelay1 = FOC_FCF_DW->UnitDelay1_DSTATE_i;

  /* Sum: '<S11>/Sum2' */
  FOC_FCF_B->Sum2_m = FOC_FCF_B->Product1_b + FOC_FCF_B->UnitDelay1;

  /* Sum: '<S11>/Sum6' */
  FOC_FCF_B->Sum6 = FOC_FCF_B->Product_o + FOC_FCF_B->phi_el_observer;

  /* Product: '<S14>/Product' incorporates:
   *  Constant: '<S14>/FOC_T_fast'
   */
  FOC_FCF_B->Product_n = FOC_FCF_B->Sum2_m * FOC_FCF_P.FOC_T_fast_Value_c;

  /* Sum: '<S14>/Sum2' */
  FOC_FCF_B->Sum2_e = FOC_FCF_B->Product_n + FOC_FCF_B->w_el;

  /* Product: '<S15>/Product' incorporates:
   *  Constant: '<S15>/FOC_T_fast'
   */
  FOC_FCF_B->Product_cd = FOC_FCF_B->winkelimpuls * FOC_FCF_P.FOC_T_fast_Value_k;

  /* Sum: '<S15>/Sum2' */
  FOC_FCF_B->Sum2_j = FOC_FCF_B->Product_cd + FOC_FCF_B->UnitDelay1;

  /* Gain: '<S4>/Gain1' */
  FOC_FCF_B->phi_el_U_trafo[0] = FOC_FCF_P.Gain1_Gain_k * FOC_FCF_B->Switch2;
  FOC_FCF_B->phi_el_U_trafo[1] = FOC_FCF_P.Gain1_Gain_k * FOC_FCF_B->Sum2_p;

  /* Outputs for Atomic SubSystem: '<S10>/Calc_Modulation_Index' */
  /* Gain: '<S42>/U_DC//2' */
  FOC_FCF_B->U_DC2_l = FOC_FCF_P.U_DC2_Gain * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S42>/AvoidDivBy0' incorporates:
   *  Constant: '<S42>/Constant2'
   */
  tmp_0 = fmaxf(FOC_FCF_P.Constant2_Value_d, FOC_FCF_B->U_DC2_l);

  /* MinMax: '<S42>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0_f = tmp_0;

  /* Math: '<S42>/Square' */
  tmp_0 = FOC_FCF_B->Product_c0[0];

  /* Math: '<S42>/Square' */
  FOC_FCF_B->Square[0] = tmp_0 * tmp_0;

  /* Math: '<S42>/Square' */
  tmp_0 = FOC_FCF_B->Product_c0[1];

  /* Math: '<S42>/Square' */
  FOC_FCF_B->Square[1] = tmp_0 * tmp_0;

  /* Sum: '<S42>/Sum' */
  tmp_0 = FOC_FCF_B->Square[0];

  /* Math: '<S42>/Square1' */
  I_phA = FOC_FCF_B->Product_f[0];

  /* Math: '<S42>/Square1' */
  FOC_FCF_B->Square1[0] = I_phA * I_phA;

  /* Sum: '<S42>/Sum' */
  tmp_0 += FOC_FCF_B->Square[1];

  /* Math: '<S42>/Square1' */
  I_phA = FOC_FCF_B->Product_f[1];

  /* Math: '<S42>/Square1' */
  FOC_FCF_B->Square1[1] = I_phA * I_phA;

  /* Sum: '<S42>/Sum' */
  FOC_FCF_B->Sum_kr = tmp_0;

  /* Sqrt: '<S42>/Sqrt' */
  FOC_FCF_B->Sqrt = sqrtf(FOC_FCF_B->Sum_kr);

  /* Sum: '<S42>/Sum1' */
  tmp_0 = FOC_FCF_B->Square1[0];
  tmp_0 += FOC_FCF_B->Square1[1];

  /* Sum: '<S42>/Sum1' */
  FOC_FCF_B->Sum1_a = tmp_0;

  /* Sqrt: '<S42>/Sqrt1' */
  FOC_FCF_B->Sqrt1 = sqrtf(FOC_FCF_B->Sum1_a);

  /* Product: '<S42>/Divide3' */
  FOC_FCF_B->ModInd[0] = FOC_FCF_B->Sqrt / FOC_FCF_B->AvoidDivBy0_f;
  FOC_FCF_B->ModInd[1] = FOC_FCF_B->Sqrt1 / FOC_FCF_B->AvoidDivBy0_f;

  /* End of Outputs for SubSystem: '<S10>/Calc_Modulation_Index' */

  /* Switch: '<S22>/IntegStopSwitch2' incorporates:
   *  Switch: '<S26>/IntegStopSwitch2'
   */
  if (FOC_FCF_B->LogicalOperator1) {
    /* RelationalOperator: '<S21>/AntiWindupLE' incorporates:
     *  Constant: '<S21>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE_l = (FOC_FCF_B->ModInd[0] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S22>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1[0];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S22>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S22>/IntegStopSwitch3' incorporates:
       *  Constant: '<S22>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value[0];
    }

    /* Switch: '<S22>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[0] = I_phA;

    /* Sum: '<S22>/IntSum2' */
    FOC_FCF_B->IntSum2_j[0] = FOC_FCF_B->KPek1[0] + I_phA;

    /* Gain: '<S22>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S21>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[0] = FOC_FCF_B->IdqErr[0] * tmp_0;

    /* Switch: '<S22>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1[1];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S22>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S22>/IntegStopSwitch3' incorporates:
       *  Constant: '<S22>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value[1];
    }

    /* Switch: '<S22>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[1] = I_phA;

    /* Sum: '<S22>/IntSum2' */
    FOC_FCF_B->IntSum2_j[1] = FOC_FCF_B->KPek1[1] + I_phA;

    /* Gain: '<S22>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S21>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[1] = FOC_FCF_B->IdqErr[1] * tmp_0;

    /* RelationalOperator: '<S24>/Compare' incorporates:
     *  Constant: '<S24>/Constant'
     */
    FOC_FCF_B->Compare_o = (uint8_T)(FOC_FCF_B->antiWindupProd_o[1] <
      FOC_FCF_P.AntiWindupGT_q_const);

    /* Logic: '<S21>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q_o = (FOC_FCF_B->AntiWindupLE_l ||
      (FOC_FCF_B->Compare_o != 0));

    /* RelationalOperator: '<S23>/Compare' incorporates:
     *  Constant: '<S23>/Constant'
     */
    FOC_FCF_B->Compare_f = (uint8_T)(FOC_FCF_B->antiWindupProd_o[0] <
      FOC_FCF_P.AntiWindupGT_d_const);

    /* Logic: '<S21>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d_e = ((FOC_FCF_B->Compare_f != 0) ||
      FOC_FCF_B->AntiWindupLE_l);

    /* Switch: '<S22>/IntegStopSwitch1' */
    tmp_1 = FOC_FCF_B->AntiWindupOR_d_e;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q_o;
    if (tmp_1) {
      tmp_0 = FOC_FCF_B->IntSum2_j[0];

      /* Switch: '<S22>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_c[0];

      /* Switch: '<S22>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = tmp_0;
    }

    /* Switch: '<S22>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[0] = tmp_0;

    /* Switch: '<S22>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2_j[1];

      /* Switch: '<S22>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_c[1];

      /* Switch: '<S22>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = tmp_0;
    }

    /* Switch: '<S22>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[1] = tmp_0;

    /* RelationalOperator: '<S25>/AntiWindupLE' incorporates:
     *  Constant: '<S25>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE = (FOC_FCF_B->ModInd[1] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S26>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[0];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S26>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S26>/IntegStopSwitch3' incorporates:
       *  Constant: '<S26>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_l[0];
    }

    /* Switch: '<S26>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[0] = I_phA;

    /* Sum: '<S26>/IntSum2' */
    FOC_FCF_B->IntSum2[0] = FOC_FCF_B->KPek1_l[0] + I_phA;

    /* Gain: '<S26>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S25>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[0] = FOC_FCF_B->IdqErr_l[0] * tmp_0;

    /* Switch: '<S26>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[1];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S26>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S26>/IntegStopSwitch3' incorporates:
       *  Constant: '<S26>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_l[1];
    }

    /* Switch: '<S26>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[1] = I_phA;

    /* Sum: '<S26>/IntSum2' */
    FOC_FCF_B->IntSum2[1] = FOC_FCF_B->KPek1_l[1] + I_phA;

    /* Gain: '<S26>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S25>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[1] = FOC_FCF_B->IdqErr_l[1] * tmp_0;

    /* RelationalOperator: '<S28>/Compare' incorporates:
     *  Constant: '<S28>/Constant'
     */
    FOC_FCF_B->Compare = (uint8_T)(FOC_FCF_B->antiWindupProd[1] <
      FOC_FCF_P.AntiWindupGT_q_const_h);

    /* Logic: '<S25>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q = (FOC_FCF_B->AntiWindupLE || (FOC_FCF_B->Compare
      != 0));

    /* RelationalOperator: '<S27>/Compare' incorporates:
     *  Constant: '<S27>/Constant'
     */
    FOC_FCF_B->Compare_i = (uint8_T)(FOC_FCF_B->antiWindupProd[0] <
      FOC_FCF_P.AntiWindupGT_d_const_n);

    /* Logic: '<S25>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d = ((FOC_FCF_B->Compare_i != 0) ||
      FOC_FCF_B->AntiWindupLE);

    /* Switch: '<S26>/IntegStopSwitch1' */
    tmp_1 = FOC_FCF_B->AntiWindupOR_d;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q;
    if (tmp_1) {
      tmp_0 = FOC_FCF_B->IntSum2[0];

      /* Switch: '<S26>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp[0];

      /* Switch: '<S26>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = tmp_0;
    }

    /* Switch: '<S26>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[0] = tmp_0;

    /* Switch: '<S26>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2[1];

      /* Switch: '<S26>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp[1];

      /* Switch: '<S26>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = tmp_0;
    }

    /* Switch: '<S26>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[1] = tmp_0;
  } else {
    /* Switch: '<S22>/IntegStopSwitch2' incorporates:
     *  Constant: '<S22>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2[0] = FOC_FCF_P.Zero1_Value[0];
    FOC_FCF_B->IntegStopSwitch2[1] = FOC_FCF_P.Zero1_Value[1];

    /* Switch: '<S26>/IntegStopSwitch2' incorporates:
     *  Constant: '<S26>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2_o[0] = FOC_FCF_P.Zero1_Value_l[0];
    FOC_FCF_B->IntegStopSwitch2_o[1] = FOC_FCF_P.Zero1_Value_l[1];
  }

  /* End of Switch: '<S22>/IntegStopSwitch2' */

  /* Gain: '<S17>/Gain1' */
  FOC_FCF_B->U_d1_CC = FOC_FCF_P.Gain1_Gain_cs * FOC_FCF_B->IntegEnaSwitch1[0];

  /* Gain: '<S17>/Gain2' */
  FOC_FCF_B->U_q1_CC = FOC_FCF_P.Gain2_Gain * FOC_FCF_B->IntegEnaSwitch1[1];

  /* DiscreteFir: '<S19>/Discrete FIR Filter 20th order' */
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

  /* End of DiscreteFir: '<S19>/Discrete FIR Filter 20th order' */

  /* DiscreteFir: '<S20>/Discrete FIR Filter 20th order' */
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

  /* End of DiscreteFir: '<S20>/Discrete FIR Filter 20th order' */

  /* DataTypeConversion: '<S6>/Data Type Conversion' */
  FOC_FCF_B->DataTypeConversion = FOC_FCF_B->Logic_gq[0];

  /* Gain: '<S6>/Gain1' */
  FOC_FCF_B->FOC_Overcurrent_I_uvw = FOC_FCF_P.Gain1_Gain_f *
    FOC_FCF_B->DataTypeConversion;

  /* DataTypeConversion: '<S7>/Data Type Conversion' */
  FOC_FCF_B->DataTypeConversion_i = FOC_FCF_B->Logic[0];

  /* DataTypeConversion: '<S7>/Data Type Conversion1' */
  FOC_FCF_B->DataTypeConversion1 = FOC_FCF_B->Logic_g[0];

  /* Gain: '<S7>/Gain1' */
  FOC_FCF_B->FOC_Undervoltage_U_DC = FOC_FCF_P.Gain1_Gain_g *
    FOC_FCF_B->DataTypeConversion_i;

  /* Gain: '<S7>/Gain2' */
  FOC_FCF_B->FOC_Overvoltage_U_DC = FOC_FCF_P.Gain2_Gain_n *
    FOC_FCF_B->DataTypeConversion1;

  /* Abs: '<S8>/Abs' */
  FOC_FCF_B->Abs_b = fabsf(FOC_FCF_B->Add_m);

  /* Switch: '<S8>/Switch' */
  if (FOC_FCF_B->Abs_b >= FOC_FCF_P.Switch_Threshold) {
    /* Signum: '<S8>/Sign' */
    tmp_0 = FOC_FCF_B->Product_e;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S8>/Sign' */
      FOC_FCF_B->Sign_n = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S8>/Sign' */
      FOC_FCF_B->Sign_n = -1.0F;
    } else {
      /* Signum: '<S8>/Sign' */
      FOC_FCF_B->Sign_n = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S8>/Sign' */

    /* Gain: '<S8>/Gain1' */
    FOC_FCF_B->Gain1_h = FOC_FCF_P.Gain1_Gain * FOC_FCF_B->Sign_n;

    /* Switch: '<S8>/Switch' */
    FOC_FCF_B->Switch_l = FOC_FCF_B->Gain1_h;
  } else {
    /* Switch: '<S8>/Switch' incorporates:
     *  Constant: '<S8>/Constant1'
     */
    FOC_FCF_B->Switch_l = FOC_FCF_P.Constant1_Value_k;
  }

  /* End of Switch: '<S8>/Switch' */

  /* Sum: '<S8>/Add1' */
  FOC_FCF_B->Add1 = FOC_FCF_B->Add_m - FOC_FCF_B->Switch_l;

  /* Abs: '<S39>/Abs' */
  FOC_FCF_B->Abs_f = fabsf(FOC_FCF_B->Add);

  /* Switch: '<S39>/Switch' */
  if (FOC_FCF_B->Abs_f >= FOC_FCF_P.Switch_Threshold_c) {
    /* Signum: '<S39>/Sign' */
    tmp_0 = FOC_FCF_B->Product;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S39>/Sign' */
      FOC_FCF_B->Sign = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S39>/Sign' */
      FOC_FCF_B->Sign = -1.0F;
    } else {
      /* Signum: '<S39>/Sign' */
      FOC_FCF_B->Sign = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S39>/Sign' */

    /* Gain: '<S39>/Gain1' */
    FOC_FCF_B->Gain1_o = FOC_FCF_P.Gain1_Gain_a * FOC_FCF_B->Sign;

    /* Switch: '<S39>/Switch' */
    FOC_FCF_B->Switch_n = FOC_FCF_B->Gain1_o;
  } else {
    /* Switch: '<S39>/Switch' incorporates:
     *  Constant: '<S39>/Constant1'
     */
    FOC_FCF_B->Switch_n = FOC_FCF_P.Constant1_Value_e;
  }

  /* End of Switch: '<S39>/Switch' */

  /* Sum: '<S39>/Add1' */
  FOC_FCF_B->Add1_c = FOC_FCF_B->Add - FOC_FCF_B->Switch_n;

  /* Gain: '<S10>/Gain' */
  FOC_FCF_B->U_d1 = FOC_FCF_P.Gain_Gain_j * FOC_FCF_B->SelectControlMode[0];

  /* Gain: '<S10>/Gain1' */
  FOC_FCF_B->U_q1 = FOC_FCF_P.Gain1_Gain_e * FOC_FCF_B->SelectControlMode[1];

  /* Gain: '<S10>/Gain2' */
  FOC_FCF_B->U_alpha1 = FOC_FCF_P.Gain2_Gain_f * FOC_FCF_B->Product_c0[0];

  /* Gain: '<S10>/Gain3' */
  FOC_FCF_B->U_beta1 = FOC_FCF_P.Gain3_Gain * FOC_FCF_B->Product_c0[1];

  /* UnitDelay: '<S1>/FCF_Cnt' */
  FOC_FCF_B->FCF_Cnt = FOC_FCF_DW->FCF_Cnt_DSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Counter_Start'
   */
  FOC_FCF_B->Sum_o = FOC_FCF_P.Counter_Start_Value + FOC_FCF_B->FCF_Cnt;

  /* Update for Memory: '<S36>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput = FOC_FCF_B->Logic[0];

  /* Update for UnitDelay: '<S35>/Delay Input1'
   *
   * Block description for '<S35>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE = FOC_FCF_B->Compare_n;

  /* Update for Memory: '<S37>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_o = FOC_FCF_B->Logic_g[0];

  /* Update for UnitDelay: '<S30>/Delay Input1'
   *
   * Block description for '<S30>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE_c = FOC_FCF_B->Compare_l;

  /* Update for Memory: '<S31>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_p = FOC_FCF_B->Logic_gq[0];

  /* Update for DiscreteTransferFcn: '<S9>/Discrete Transfer Fcn' */
  tmp_0 = FOC_FCF_B->f_2_w_el;
  tmp_0 -= FOC_FCF_P.DiscreteTransferFcn_DenCoef[1] *
    FOC_FCF_DW->DiscreteTransferFcn_states;
  tmp_0 /= FOC_FCF_P.DiscreteTransferFcn_DenCoef[0];
  FOC_FCF_DW->DiscreteTransferFcn_states = tmp_0;

  /* Update for UnitDelay: '<S39>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_B->Add1_c;

  /* Update for UnitDelay: '<S14>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_B->Sum2_e;

  /* Update for UnitDelay: '<S13>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_B->Sum3;

  /* Update for UnitDelay: '<S11>/Unit Delay3' */
  FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_B->Sum6;

  /* Update for UnitDelay: '<S8>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_B->Add1;

  /* Update for UnitDelay: '<S22>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_B->IntegStopSwitch2[0];

  /* Update for UnitDelay: '<S26>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[0] = FOC_FCF_B->IntegStopSwitch2_o[0];

  /* Update for UnitDelay: '<S22>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_B->IntegStopSwitch2[1];

  /* Update for UnitDelay: '<S26>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[1] = FOC_FCF_B->IntegStopSwitch2_o[1];

  /* Update for UnitDelay: '<S15>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_B->Sum2_j;

  /* Update for DiscreteFir: '<S19>/Discrete FIR Filter 20th order' */
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

  /* End of Update for DiscreteFir: '<S19>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S20>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m--;
  if (FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m < 0) {
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m = 18;
  }

  /* Update for UnitDelay: '<S1>/FCF_Cnt' */
  /* Update circular buffer */
  FOC_FCF_DW->FCF_Cnt_DSTATE = FOC_FCF_B->Sum_o;

  /* Update for DiscreteFir: '<S20>/Discrete FIR Filter 20th order' */
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
  /* Update for DiscreteFir: '<S20>/Discrete FIR Filter 20th order' */
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
    /* InitializeConditions for Memory: '<S36>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput = FOC_FCF_P.SRFlipFlop_initial_condition;

    /* InitializeConditions for UnitDelay: '<S35>/Delay Input1'
     *
     * Block description for '<S35>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE = FOC_FCF_P.DetectRisePositive_vinit;

    /* InitializeConditions for Memory: '<S37>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_o = FOC_FCF_P.SRFlipFlop1_initial_condition;

    /* InitializeConditions for UnitDelay: '<S30>/Delay Input1'
     *
     * Block description for '<S30>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE_c = FOC_FCF_P.DetectRisePositive_vinit_o;

    /* InitializeConditions for Memory: '<S31>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_p =
      FOC_FCF_P.SRFlipFlop_initial_condition_a;

    /* InitializeConditions for DiscreteTransferFcn: '<S9>/Discrete Transfer Fcn' */
    FOC_FCF_DW->DiscreteTransferFcn_states =
      FOC_FCF_P.DiscreteTransferFcn_InitialStat;

    /* InitializeConditions for UnitDelay: '<S39>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_P.UnitDelay_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S14>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_P.FOC_AngleObs_w_InitVal;

    /* InitializeConditions for UnitDelay: '<S13>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_P.UnitDelay_InitialCondition_b;

    /* InitializeConditions for UnitDelay: '<S11>/Unit Delay3' */
    FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_P.UnitDelay3_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S8>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_P.UnitDelay_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S22>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S26>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[0] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S22>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S26>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[1] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S15>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_P.UnitDelay1_InitialCondition;

    /* InitializeConditions for DiscreteFir: '<S19>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_circ = 0;

    /* InitializeConditions for DiscreteFir: '<S20>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m = 0;
    for (i = 0; i < 38; i++) {
      /* InitializeConditions for DiscreteFir: '<S19>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_Init;

      /* InitializeConditions for DiscreteFir: '<S20>/Discrete FIR Filter 20th order' */
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
