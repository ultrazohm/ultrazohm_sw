/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF.c
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.38
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Feb 10 16:30:06 2026
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
    FOC_FCF_B->FOC_Mode_Request = FOC_FCF_U->FOC_Mode;
  } else {
    /* MultiPortSwitch: '<S1>/ModeSwitch' incorporates:
     *  Constant: '<S1>/FOC_Mode_Intern'
     */
    FOC_FCF_B->FOC_Mode_Request = FOC_FCF_P.FOC_Mode_Intern;
  }

  /* End of MultiPortSwitch: '<S1>/ModeSwitch' */

  /* RelationalOperator: '<S65>/Compare' incorporates:
   *  Constant: '<S65>/Constant'
   */
  FOC_FCF_B->Compare_e = (FOC_FCF_U->U_DC <
    FOC_FCF_P.FOC_LIMIT_Undervoltage_U_DC);

  /* Logic: '<S49>/Logical Operator2' */
  FOC_FCF_B->LogicalOperator2 = (FOC_FCF_B->Compare_e &&
    (FOC_FCF_U->FOC_Enable_PWM != 0.0F));

  /* Logic: '<S49>/Logical Operator4' incorporates:
   *  Constant: '<S49>/Reset_UV_Error'
   */
  FOC_FCF_B->LogicalOperator4 = ((FOC_FCF_P.FOC_RESET_UV_Error != 0.0F) ||
    (FOC_FCF_U->global_reset_errors != 0.0F));

  /* RelationalOperator: '<S72>/Compare' incorporates:
   *  Constant: '<S72>/Constant'
   */
  FOC_FCF_B->Compare_d = ((int32_T)FOC_FCF_B->LogicalOperator4 > (int32_T)
    FOC_FCF_P.Constant_Value_eo);

  /* UnitDelay: '<S68>/Delay Input1'
   *
   * Block description for '<S68>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1 = FOC_FCF_DW->DelayInput1_DSTATE;

  /* MultiPortSwitch: '<S49>/Selectphicalc3' incorporates:
   *  Constant: '<S49>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Undervoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S49>/Selectphicalc3' incorporates:
     *  Constant: '<S49>/Constant2'
     */
    FOC_FCF_B->Selectphicalc3 = FOC_FCF_P.Constant2_Value_c;
  } else {
    /* RelationalOperator: '<S68>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator_j = ((int32_T)FOC_FCF_B->Compare_d >
      (int32_T)FOC_FCF_B->Uk1);

    /* MultiPortSwitch: '<S49>/Selectphicalc3' */
    FOC_FCF_B->Selectphicalc3 = FOC_FCF_B->FixPtRelationalOperator_j;
  }

  /* End of MultiPortSwitch: '<S49>/Selectphicalc3' */

  /* Memory: '<S69>/Memory' */
  FOC_FCF_B->Memory = FOC_FCF_DW->Memory_PreviousInput;

  /* CombinatorialLogic: '<S69>/Logic' */
  tmp_1 = FOC_FCF_B->LogicalOperator2;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc3;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic[0U] = FOC_FCF_P.Logic_table[(uint32_T)i];
  FOC_FCF_B->Logic[1U] = FOC_FCF_P.Logic_table[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S49>/Selectphicalc1' incorporates:
   *  Constant: '<S49>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Undervoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S49>/Selectphicalc1' incorporates:
     *  Constant: '<S49>/Constant3'
     */
    FOC_FCF_B->U_DC_Undervoltage_Error = FOC_FCF_P.Constant3_Value;
  } else {
    /* DataTypeConversion: '<S49>/Data Type Conversion' */
    FOC_FCF_B->DataTypeConversion_n = FOC_FCF_B->Logic[0];

    /* MultiPortSwitch: '<S49>/Selectphicalc1' */
    FOC_FCF_B->U_DC_Undervoltage_Error = FOC_FCF_B->DataTypeConversion_n;
  }

  /* End of MultiPortSwitch: '<S49>/Selectphicalc1' */

  /* RelationalOperator: '<S66>/Compare' incorporates:
   *  Constant: '<S66>/Constant'
   */
  FOC_FCF_B->Compare_n = (FOC_FCF_U->U_DC > FOC_FCF_P.FOC_LIMIT_Overvoltage_U_DC);

  /* Logic: '<S49>/Logical Operator3' incorporates:
   *  Constant: '<S49>/Reset_OV_Error'
   */
  FOC_FCF_B->LogicalOperator3 = ((FOC_FCF_P.FOC_RESET_OV_Error != 0.0F) ||
    (FOC_FCF_U->global_reset_errors != 0.0F));

  /* RelationalOperator: '<S71>/Compare' incorporates:
   *  Constant: '<S71>/Constant'
   */
  FOC_FCF_B->Compare_iz = ((int32_T)FOC_FCF_B->LogicalOperator3 > (int32_T)
    FOC_FCF_P.Constant_Value_dc);

  /* UnitDelay: '<S67>/Delay Input1'
   *
   * Block description for '<S67>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1_m = FOC_FCF_DW->DelayInput1_DSTATE_g;

  /* MultiPortSwitch: '<S49>/Selectphicalc4' incorporates:
   *  Constant: '<S49>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overvoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S49>/Selectphicalc4' incorporates:
     *  Constant: '<S49>/Constant4'
     */
    FOC_FCF_B->Selectphicalc4 = FOC_FCF_P.Constant4_Value_f;
  } else {
    /* RelationalOperator: '<S67>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator_m = ((int32_T)FOC_FCF_B->Compare_iz >
      (int32_T)FOC_FCF_B->Uk1_m);

    /* MultiPortSwitch: '<S49>/Selectphicalc4' */
    FOC_FCF_B->Selectphicalc4 = FOC_FCF_B->FixPtRelationalOperator_m;
  }

  /* End of MultiPortSwitch: '<S49>/Selectphicalc4' */

  /* Memory: '<S70>/Memory' */
  FOC_FCF_B->Memory_o = FOC_FCF_DW->Memory_PreviousInput_e;

  /* CombinatorialLogic: '<S70>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_n;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc4;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_o;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_c[0U] = FOC_FCF_P.Logic_table_l[(uint32_T)i];
  FOC_FCF_B->Logic_c[1U] = FOC_FCF_P.Logic_table_l[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S49>/Selectphicalc2' incorporates:
   *  Constant: '<S49>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overvoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S49>/Selectphicalc2' incorporates:
     *  Constant: '<S49>/Constant1'
     */
    FOC_FCF_B->U_DC_Overvoltage_Error = FOC_FCF_P.Constant1_Value_b;
  } else {
    /* DataTypeConversion: '<S49>/Data Type Conversion1' */
    FOC_FCF_B->DataTypeConversion1 = FOC_FCF_B->Logic_c[0];

    /* MultiPortSwitch: '<S49>/Selectphicalc2' */
    FOC_FCF_B->U_DC_Overvoltage_Error = FOC_FCF_B->DataTypeConversion1;
  }

  /* End of MultiPortSwitch: '<S49>/Selectphicalc2' */
  for (i = 0; i < 9; i++) {
    /* Abs: '<S48>/Abs' */
    FOC_FCF_B->Abs[i] = fabsf(FOC_FCF_U->I_phA[i]);
  }

  /* MinMax: '<S48>/MinMax' incorporates:
   *  Abs: '<S48>/Abs'
   */
  tmp_0 = FOC_FCF_B->Abs[0];
  for (i = 0; i < 8; i++) {
    tmp_0 = fmaxf(tmp_0, FOC_FCF_B->Abs[i + 1]);
  }

  /* MinMax: '<S48>/MinMax' */
  FOC_FCF_B->MinMax = tmp_0;

  /* RelationalOperator: '<S50>/Compare' incorporates:
   *  Constant: '<S50>/Constant'
   */
  FOC_FCF_B->Compare_j = (FOC_FCF_B->MinMax >
    FOC_FCF_P.FOC_LIMIT_Overcurrent_I_uvw);

  /* Logic: '<S48>/Logical Operator3' incorporates:
   *  Constant: '<S48>/Reset_OC_Error'
   */
  FOC_FCF_B->LogicalOperator3_i = ((FOC_FCF_P.FOC_RESET_OC_Error != 0.0F) ||
    (FOC_FCF_U->global_reset_errors != 0.0F));

  /* RelationalOperator: '<S55>/Compare' incorporates:
   *  Constant: '<S55>/Constant'
   */
  FOC_FCF_B->Compare_in = ((int32_T)FOC_FCF_B->LogicalOperator3_i > (int32_T)
    FOC_FCF_P.Constant_Value_j);

  /* UnitDelay: '<S52>/Delay Input1'
   *
   * Block description for '<S52>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1_g = FOC_FCF_DW->DelayInput1_DSTATE_l;

  /* MultiPortSwitch: '<S48>/Selectphicalc2' incorporates:
   *  Constant: '<S48>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overcurrent_I_uvw == 0) {
    /* MultiPortSwitch: '<S48>/Selectphicalc2' incorporates:
     *  Constant: '<S48>/Constant1'
     */
    FOC_FCF_B->Selectphicalc2_m = FOC_FCF_P.Constant1_Value_d;
  } else {
    /* RelationalOperator: '<S52>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator_h = ((int32_T)FOC_FCF_B->Compare_in >
      (int32_T)FOC_FCF_B->Uk1_g);

    /* MultiPortSwitch: '<S48>/Selectphicalc2' */
    FOC_FCF_B->Selectphicalc2_m = FOC_FCF_B->FixPtRelationalOperator_h;
  }

  /* End of MultiPortSwitch: '<S48>/Selectphicalc2' */

  /* Memory: '<S54>/Memory' */
  FOC_FCF_B->Memory_n = FOC_FCF_DW->Memory_PreviousInput_j;

  /* CombinatorialLogic: '<S54>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_j;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_n;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_a[0U] = FOC_FCF_P.Logic_table_o[(uint32_T)i];
  FOC_FCF_B->Logic_a[1U] = FOC_FCF_P.Logic_table_o[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S48>/Selectphicalc1' incorporates:
   *  Constant: '<S48>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overcurrent_I_uvw == 0) {
    /* MultiPortSwitch: '<S48>/Selectphicalc1' incorporates:
     *  Constant: '<S48>/Constant2'
     */
    FOC_FCF_B->I_ph_Overcurrent_Error = FOC_FCF_P.Constant2_Value_f;
  } else {
    /* MultiPortSwitch: '<S48>/Selectphicalc1' */
    FOC_FCF_B->I_ph_Overcurrent_Error = FOC_FCF_B->Logic_a[0];
  }

  /* End of MultiPortSwitch: '<S48>/Selectphicalc1' */

  /* Logic: '<S10>/Logical Operator' */
  FOC_FCF_B->OC_OV_UV_ERROR = ((FOC_FCF_B->U_DC_Undervoltage_Error != 0.0) ||
    (FOC_FCF_B->U_DC_Overvoltage_Error != 0.0) ||
    FOC_FCF_B->I_ph_Overcurrent_Error);

  /* Logic: '<S1>/Logical Operator1' incorporates:
   *  Constant: '<S1>/Enable'
   */
  FOC_FCF_B->LogicalOperator1 = ((FOC_FCF_P.FOC_Enable != 0.0F) &&
    (FOC_FCF_U->FOC_Enable_PWM != 0.0F));

  /* Logic: '<S1>/Logical Operator' */
  FOC_FCF_B->LogicalOperator = (FOC_FCF_B->OC_OV_UV_ERROR &&
    FOC_FCF_B->LogicalOperator1);

  /* Switch: '<S1>/Switch' */
  if (FOC_FCF_B->LogicalOperator) {
    /* Switch: '<S1>/Switch' */
    FOC_FCF_B->FOC_Mode_after_checks = FOC_FCF_B->FOC_Mode_Request;
  } else {
    /* Switch: '<S1>/Switch' incorporates:
     *  Constant: '<S1>/Constant1'
     */
    FOC_FCF_B->FOC_Mode_after_checks = FOC_FCF_P.Constant1_Value_bt;
  }

  /* End of Switch: '<S1>/Switch' */

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  tmp_0 = FOC_FCF_P.DiscreteTransferFcn_NumCoef *
    FOC_FCF_DW->DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  FOC_FCF_B->DiscreteTransferFcn = tmp_0;

  /* Gain: '<S13>/f_2_w_el' incorporates:
   *  Constant: '<S13>/Uf_w_el'
   */
  FOC_FCF_B->f_2_w_el = FOC_FCF_P.f_2_w_el_Gain * FOC_FCF_P.FOC_Uf_f_el;

  /* Product: '<S77>/Product' incorporates:
   *  Constant: '<S77>/FOC_T_fast'
   */
  FOC_FCF_B->Product = FOC_FCF_B->f_2_w_el * FOC_FCF_P.FOC_T_fast_Value;

  /* UnitDelay: '<S77>/Unit Delay' */
  FOC_FCF_B->UnitDelay = FOC_FCF_DW->UnitDelay_DSTATE;

  /* Sum: '<S77>/Add' */
  FOC_FCF_B->Add = FOC_FCF_B->Product + FOC_FCF_B->UnitDelay;

  /* Gain: '<S24>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[0];
  I_phA = FOC_FCF_U->I_phA[1];
  I_phA_0 = FOC_FCF_U->I_phA[2];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S24>/TrafoMatrix uvw->alphabeta' */
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
  FOC_FCF_B->Compare_l = (FOC_FCF_B->FOC_Mode_Request ==
    FOC_FCF_P.enumState_FOC_IF);

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

  /* UnitDelay: '<S18>/Unit Delay1' */
  FOC_FCF_B->w_el = FOC_FCF_DW->UnitDelay1_DSTATE;

  /* Gain: '<S15>/DeadTimeCompensation' */
  FOC_FCF_B->DeadTimeCompensation = FOC_FCF_P.FOC_PhiSensorTdead *
    FOC_FCF_B->w_el;

  /* Sum: '<S15>/Sum3' */
  FOC_FCF_B->Sum3 = FOC_FCF_B->Sum1 + FOC_FCF_B->DeadTimeCompensation;

  /* UnitDelay: '<S17>/Unit Delay' */
  FOC_FCF_B->UnitDelay_l = FOC_FCF_DW->UnitDelay_DSTATE_h;

  /* Sum: '<S17>/Sum' */
  FOC_FCF_B->Sum = FOC_FCF_B->Sum3 - FOC_FCF_B->UnitDelay_l;

  /* RelationalOperator: '<S17>/Sprung?' incorporates:
   *  Constant: '<S17>/Constant3'
   */
  FOC_FCF_B->Sprung = (FOC_FCF_B->Sum < FOC_FCF_P.Constant3_Value_l);

  /* Switch: '<S17>/Switch' */
  if (FOC_FCF_B->Sprung) {
    /* Switch: '<S17>/Switch' incorporates:
     *  Constant: '<S17>/Constant2'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant2_Value;
  } else {
    /* Switch: '<S17>/Switch' incorporates:
     *  Constant: '<S17>/Constant4'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant4_Value;
  }

  /* End of Switch: '<S17>/Switch' */

  /* RelationalOperator: '<S17>/Sprung?1' incorporates:
   *  Constant: '<S17>/Constant1'
   */
  FOC_FCF_B->Sprung1 = (FOC_FCF_B->Sum > FOC_FCF_P.Constant1_Value_ep);

  /* Switch: '<S17>/Switch1' */
  if (FOC_FCF_B->Sprung1) {
    /* Switch: '<S17>/Switch1' incorporates:
     *  Constant: '<S17>/Constant5'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant5_Value;
  } else {
    /* Switch: '<S17>/Switch1' incorporates:
     *  Constant: '<S17>/Constant6'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant6_Value;
  }

  /* End of Switch: '<S17>/Switch1' */

  /* Sum: '<S17>/Sum2' */
  FOC_FCF_B->Sum2 = FOC_FCF_B->Switch + FOC_FCF_B->Switch1;

  /* UnitDelay: '<S15>/Unit Delay3' */
  FOC_FCF_B->UnitDelay3 = FOC_FCF_DW->UnitDelay3_DSTATE;

  /* Sum: '<S15>/Sum7' */
  FOC_FCF_B->phi_el_observer = FOC_FCF_B->UnitDelay3 - FOC_FCF_B->Sum2;

  /* Product: '<S12>/Product' incorporates:
   *  Constant: '<S12>/FOC_T_fast'
   */
  FOC_FCF_B->Product_e = FOC_FCF_U->w_el_Ref_IfStarter *
    FOC_FCF_P.FOC_T_fast_Value_d;

  /* UnitDelay: '<S12>/Unit Delay' */
  FOC_FCF_B->UnitDelay_a = FOC_FCF_DW->UnitDelay_DSTATE_p;

  /* Sum: '<S12>/Add' */
  FOC_FCF_B->Add_m = FOC_FCF_B->Product_e + FOC_FCF_B->UnitDelay_a;

  /* Gain: '<S9>/f_2_w_el' incorporates:
   *  Constant: '<S9>/If_f_el'
   */
  FOC_FCF_B->f_2_w_el_b = FOC_FCF_P.f_2_w_el_Gain_j * FOC_FCF_P.FOC_If_f_el;

  /* Product: '<S47>/Product' incorporates:
   *  Constant: '<S47>/FOC_T_fast'
   */
  FOC_FCF_B->Product_h = FOC_FCF_B->f_2_w_el_b * FOC_FCF_P.FOC_T_fast_Value_f;

  /* UnitDelay: '<S47>/Unit Delay' */
  FOC_FCF_B->UnitDelay_j = FOC_FCF_DW->UnitDelay_DSTATE_f;

  /* Sum: '<S47>/Add' */
  FOC_FCF_B->Add_mp = FOC_FCF_B->Product_h + FOC_FCF_B->UnitDelay_j;

  /* MultiPortSwitch: '<S1>/Use_If_Mode' */
  if (!FOC_FCF_B->Compare_l) {
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

      /* Switch: '<S16>/Switch1' */
      if (FOC_FCF_B->Selectphicalc2 > FOC_FCF_P.Switch1_Threshold) {
        /* Sum: '<S16>/Sum2' incorporates:
         *  Constant: '<S16>/Constant'
         */
        FOC_FCF_B->Sum2_l = FOC_FCF_B->Selectphicalc2 -
          FOC_FCF_P.Constant_Value_e;

        /* Switch: '<S16>/Switch1' */
        FOC_FCF_B->Switch1_d = FOC_FCF_B->Sum2_l;
      } else {
        /* Switch: '<S16>/Switch1' */
        FOC_FCF_B->Switch1_d = FOC_FCF_B->Selectphicalc2;
      }

      /* End of Switch: '<S16>/Switch1' */

      /* Switch: '<S16>/Switch2' */
      if (FOC_FCF_B->Switch1_d > FOC_FCF_P.Switch2_Threshold) {
        /* Switch: '<S16>/Switch2' */
        FOC_FCF_B->Switch2_f = FOC_FCF_B->Switch1_d;
      } else {
        /* Sum: '<S16>/Sum3' incorporates:
         *  Constant: '<S16>/Constant1'
         */
        FOC_FCF_B->Sum3_h = FOC_FCF_B->Switch1_d + FOC_FCF_P.Constant1_Value_g;

        /* Switch: '<S16>/Switch2' */
        FOC_FCF_B->Switch2_f = FOC_FCF_B->Sum3_h;
      }

      /* End of Switch: '<S16>/Switch2' */

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

  /* Trigonometry: '<S24>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1 = cosf(FOC_FCF_B->Use_If_Mode[0]);

  /* Product: '<S24>/TrafoProd' */
  FOC_FCF_B->TrafoProd = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction1;

  /* Trigonometry: '<S24>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction = sinf(FOC_FCF_B->Use_If_Mode[0]);

  /* Product: '<S24>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3 = FOC_FCF_B->TrigonometricFunction *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Sum: '<S24>/I_d1_Act' */
  FOC_FCF_B->I_d1_Act = FOC_FCF_B->TrafoProd + FOC_FCF_B->TrafoProd3;

  /* Product: '<S24>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1 = FOC_FCF_B->TrigonometricFunction1 *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Product: '<S24>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2 = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction;

  /* Sum: '<S24>/I_q1_Act' */
  FOC_FCF_B->I_q1_Act = FOC_FCF_B->TrafoProd1 - FOC_FCF_B->TrafoProd2;

  /* SignalConversion generated from: '<S24>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0] = FOC_FCF_B->I_d1_Act;
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1] = FOC_FCF_B->I_q1_Act;

  /* Sum: '<S21>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S28>/KP*e[k]1' incorporates:
   *  Constant: '<S28>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S28>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[0] = FOC_FCF_DW->IntegDelay1_DSTATE[0];

  /* Sum: '<S21>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S28>/KP*e[k]1' incorporates:
   *  Constant: '<S28>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S28>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[1] = FOC_FCF_DW->IntegDelay1_DSTATE[1];

  /* Product: '<S28>/Product1' incorporates:
   *  Constant: '<S28>/FOC_KI'
   *  Constant: '<S28>/FOC_T_fast'
   */
  FOC_FCF_B->Product1 = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_n;

  /* Switch: '<S28>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Product: '<S28>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1[0] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[0] = tmp_0;

    /* Sum: '<S28>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1[0];
    FOC_FCF_B->IntSum1_p[0] = tmp_0;

    /* Switch: '<S28>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1[0] = tmp_0;

    /* Product: '<S28>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1[1] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[1] = tmp_0;

    /* Sum: '<S28>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1[1];
    FOC_FCF_B->IntSum1_p[1] = tmp_0;

    /* Switch: '<S28>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1[1] = tmp_0;
  } else {
    /* Switch: '<S28>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S28>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1[0] = FOC_FCF_P.Zero_Value;
    FOC_FCF_B->IntegEnaSwitch1[1] = FOC_FCF_P.Zero_Value;
  }

  /* End of Switch: '<S28>/IntegEnaSwitch1' */

  /* Gain: '<S25>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[3];
  I_phA = FOC_FCF_U->I_phA[4];
  I_phA_0 = FOC_FCF_U->I_phA[5];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S25>/TrafoMatrix uvw->alphabeta' */
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

  /* Trigonometry: '<S25>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_b = cosf(FOC_FCF_B->Sum1_d);

  /* Product: '<S25>/TrafoProd' */
  FOC_FCF_B->TrafoProd_a = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction1_b;

  /* Trigonometry: '<S25>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_l = sinf(FOC_FCF_B->Sum1_d);

  /* Product: '<S25>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3_i = FOC_FCF_B->TrigonometricFunction_l *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Sum: '<S25>/TrafoSum' */
  FOC_FCF_B->TrafoSum = FOC_FCF_B->TrafoProd_a + FOC_FCF_B->TrafoProd3_i;

  /* Product: '<S25>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1_b = FOC_FCF_B->TrigonometricFunction1_b *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Product: '<S25>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2_b = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction_l;

  /* Sum: '<S25>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1 = FOC_FCF_B->TrafoProd1_b - FOC_FCF_B->TrafoProd2_b;

  /* SignalConversion generated from: '<S25>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0] = FOC_FCF_B->TrafoSum;
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1] = FOC_FCF_B->TrafoSum1;

  /* Sum: '<S22>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S32>/KP*e[k]1' incorporates:
   *  Constant: '<S32>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S32>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[0] = FOC_FCF_DW->IntegDelay1_DSTATE_p[0];

  /* Sum: '<S22>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S32>/KP*e[k]1' incorporates:
   *  Constant: '<S32>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S32>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[1] = FOC_FCF_DW->IntegDelay1_DSTATE_p[1];

  /* Product: '<S32>/Product1' incorporates:
   *  Constant: '<S32>/FOC_KI'
   *  Constant: '<S32>/FOC_T_fast'
   */
  FOC_FCF_B->Product1_k = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_e;

  /* Switch: '<S32>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Product: '<S32>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[0] * FOC_FCF_B->Product1_k;
    FOC_FCF_B->Product2_b[0] = tmp_0;

    /* Sum: '<S32>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1_l[0];
    FOC_FCF_B->IntSum1_l[0] = tmp_0;

    /* Switch: '<S32>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_n[0] = tmp_0;

    /* Product: '<S32>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[1] * FOC_FCF_B->Product1_k;
    FOC_FCF_B->Product2_b[1] = tmp_0;

    /* Sum: '<S32>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1_l[1];
    FOC_FCF_B->IntSum1_l[1] = tmp_0;

    /* Switch: '<S32>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_n[1] = tmp_0;
  } else {
    /* Switch: '<S32>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S32>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1_n[0] = FOC_FCF_P.Zero_Value_o;
    FOC_FCF_B->IntegEnaSwitch1_n[1] = FOC_FCF_P.Zero_Value_o;
  }

  /* End of Switch: '<S32>/IntegEnaSwitch1' */

  /* Gain: '<S26>/TrafoMatrix uvw->alphabeta' */
  tmp_0 = FOC_FCF_U->I_phA[6];
  I_phA = FOC_FCF_U->I_phA[7];
  I_phA_0 = FOC_FCF_U->I_phA[8];
  for (i_0 = 0; i_0 < 2; i_0++) {
    /* Gain: '<S26>/TrafoMatrix uvw->alphabeta' */
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

  /* Trigonometry: '<S26>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_k = cosf(FOC_FCF_B->Sum2_m);

  /* Product: '<S26>/TrafoProd' */
  FOC_FCF_B->TrafoProd_n = FOC_FCF_B->TrafoMatrixuvwalphabeta_m[0] *
    FOC_FCF_B->TrigonometricFunction1_k;

  /* Trigonometry: '<S26>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_k = sinf(FOC_FCF_B->Sum2_m);

  /* Product: '<S26>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3_o = FOC_FCF_B->TrigonometricFunction_k *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_m[1];

  /* Sum: '<S26>/TrafoSum' */
  FOC_FCF_B->TrafoSum_n = FOC_FCF_B->TrafoProd_n + FOC_FCF_B->TrafoProd3_o;

  /* Product: '<S26>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1_e = FOC_FCF_B->TrigonometricFunction1_k *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_m[1];

  /* Product: '<S26>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2_h = FOC_FCF_B->TrafoMatrixuvwalphabeta_m[0] *
    FOC_FCF_B->TrigonometricFunction_k;

  /* Sum: '<S26>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1_p = FOC_FCF_B->TrafoProd1_e - FOC_FCF_B->TrafoProd2_h;

  /* SignalConversion generated from: '<S26>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0] = FOC_FCF_B->TrafoSum_n;
  FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1] = FOC_FCF_B->TrafoSum1_p;

  /* Sum: '<S23>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[0] - FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_e[0] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S36>/KP*e[k]1' incorporates:
   *  Constant: '<S36>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_h[0] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S36>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_d[0] = FOC_FCF_DW->IntegDelay1_DSTATE_h[0];

  /* Sum: '<S23>/IdqErr' */
  tmp_0 = FOC_FCF_U->I_dq_RefA[1] - FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_e[1] = tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S36>/KP*e[k]1' incorporates:
   *  Constant: '<S36>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_h[1] = tmp_0 * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S36>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_d[1] = FOC_FCF_DW->IntegDelay1_DSTATE_h[1];

  /* Product: '<S36>/Product1' incorporates:
   *  Constant: '<S36>/FOC_KI'
   *  Constant: '<S36>/FOC_T_fast'
   */
  FOC_FCF_B->Product1_b = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_er;

  /* Switch: '<S36>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1) {
    /* Product: '<S36>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1_d[0] * FOC_FCF_B->Product1_b;
    FOC_FCF_B->Product2_e[0] = tmp_0;

    /* Sum: '<S36>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1_h[0];
    FOC_FCF_B->IntSum1[0] = tmp_0;

    /* Switch: '<S36>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_h[0] = tmp_0;

    /* Product: '<S36>/Product2' */
    tmp_0 = FOC_FCF_B->IntegDelay1_d[1] * FOC_FCF_B->Product1_b;
    FOC_FCF_B->Product2_e[1] = tmp_0;

    /* Sum: '<S36>/IntSum1' */
    tmp_0 += FOC_FCF_B->KPek1_h[1];
    FOC_FCF_B->IntSum1[1] = tmp_0;

    /* Switch: '<S36>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_h[1] = tmp_0;
  } else {
    /* Switch: '<S36>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S36>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1_h[0] = FOC_FCF_P.Zero_Value_n;
    FOC_FCF_B->IntegEnaSwitch1_h[1] = FOC_FCF_P.Zero_Value_n;
  }

  /* End of Switch: '<S36>/IntegEnaSwitch1' */

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S4>/FOC_T_fast'
   *  Constant: '<S4>/FOC_output_trafo_delay'
   */
  FOC_FCF_B->Product_c = FOC_FCF_P.FOC_output_trafo_delay *
    FOC_FCF_B->Use_If_Mode[1] * FOC_FCF_P.FOC_T_fast_Value_m;

  /* Sum: '<S4>/Sum' */
  FOC_FCF_B->Sum_k = FOC_FCF_B->Use_If_Mode[0] + FOC_FCF_B->Product_c;

  /* Switch: '<S20>/Switch1' */
  if (FOC_FCF_B->Sum_k > FOC_FCF_P.Switch1_Threshold_a) {
    /* Sum: '<S20>/Sum2' incorporates:
     *  Constant: '<S20>/Constant'
     */
    FOC_FCF_B->Sum2_ez = FOC_FCF_B->Sum_k - FOC_FCF_P.Constant_Value;

    /* Switch: '<S20>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum2_ez;
  } else {
    /* Switch: '<S20>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum_k;
  }

  /* End of Switch: '<S20>/Switch1' */

  /* Switch: '<S20>/Switch2' */
  if (FOC_FCF_B->Switch1_k > FOC_FCF_P.Switch2_Threshold_o) {
    /* Switch: '<S20>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Switch1_k;
  } else {
    /* Sum: '<S20>/Sum3' incorporates:
     *  Constant: '<S20>/Constant1'
     */
    FOC_FCF_B->Sum3_d = FOC_FCF_B->Switch1_k + FOC_FCF_P.Constant1_Value;

    /* Switch: '<S20>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Sum3_d;
  }

  /* End of Switch: '<S20>/Switch2' */

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
    /* Gain: '<S78>/Gain' */
    FOC_FCF_B->Gain_fw = FOC_FCF_P.FOC_Uf_m * FOC_FCF_B->DiscreteTransferFcn;

    /* Signum: '<S78>/Sign' */
    tmp_0 = FOC_FCF_B->Gain_fw;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S78>/Sign' */
      FOC_FCF_B->Sign_p = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S78>/Sign' */
      FOC_FCF_B->Sign_p = -1.0F;
    } else {
      /* Signum: '<S78>/Sign' */
      FOC_FCF_B->Sign_p = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S78>/Sign' */

    /* Abs: '<S78>/Abs' */
    FOC_FCF_B->Abs_d3 = fabsf(FOC_FCF_B->Gain_fw);

    /* Saturate: '<S78>/Saturation1' */
    if (FOC_FCF_B->Abs_d3 > FOC_FCF_P.FOC_Uf_U_max) {
      /* Saturate: '<S78>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_max;
    } else if (FOC_FCF_B->Abs_d3 < FOC_FCF_P.FOC_Uf_U_min) {
      /* Saturate: '<S78>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_min;
    } else {
      /* Saturate: '<S78>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_B->Abs_d3;
    }

    /* End of Saturate: '<S78>/Saturation1' */

    /* Product: '<S78>/Product' */
    FOC_FCF_B->Product_j = FOC_FCF_B->Saturation1 * FOC_FCF_B->Sign_p;

    /* Sum: '<S13>/Sum1' incorporates:
     *  Constant: '<S13>/FOC_9ph_AngleShift'
     */
    FOC_FCF_B->Sum1_n = FOC_FCF_B->Add + FOC_FCF_P.FOC_9ph_AngleShift;

    /* Sum: '<S13>/Sum2' incorporates:
     *  Constant: '<S13>/FOC_9ph_AngleShift'
     */
    FOC_FCF_B->Sum2_d = FOC_FCF_B->Sum1_n + FOC_FCF_P.FOC_9ph_AngleShift;

    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S13>/Uf_Ud'
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

  /* Trigonometry: '<S87>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_n = sinf(FOC_FCF_B->SelectControlMode[6]);

  /* Trigonometry: '<S87>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_j = cosf(FOC_FCF_B->SelectControlMode[6]);

  /* Gain: '<S87>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[0] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S87>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[0] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S87>/Sum1' incorporates:
   *  Gain: '<S87>/Gain'
   *  Gain: '<S87>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S87>/Product' incorporates:
   *  Sum: '<S87>/Sum1'
   */
  I_phA_0 = Sum1_lz;

  /* Gain: '<S87>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[1] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S87>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[1] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S87>/Sum1' incorporates:
   *  Gain: '<S87>/Gain'
   *  Gain: '<S87>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S87>/Product' incorporates:
   *  Sum: '<S87>/Sum1'
   */
  tmp_0 = Sum1_lz;

  /* Gain: '<S87>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[2] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S87>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[2] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S87>/Sum1' incorporates:
   *  Gain: '<S87>/Gain'
   *  Gain: '<S87>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S87>/Product' incorporates:
   *  Sum: '<S87>/Sum1'
   */
  I_phA = Sum1_lz;

  /* Gain: '<S87>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[3] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S87>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain[3] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S87>/Sum1' incorporates:
   *  Gain: '<S87>/Gain'
   *  Gain: '<S87>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S87>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[0];
  Gain = FOC_FCF_B->SelectControlMode[1];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S87>/Product' */
  FOC_FCF_B->Product_c0[0] = I_phA_0;

  /* Product: '<S87>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_lz * Gain;

  /* Product: '<S87>/Product' */
  FOC_FCF_B->Product_c0[1] = I_phA_0;

  /* Product: '<S84>/Product' incorporates:
   *  Constant: '<S84>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_d[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_c0[0];
  Gain = FOC_FCF_B->Product_c0[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    I_phA_0 = tmp[i_0] * TrafoMatrixuvwalphabeta;
    I_phA_0 += tmp[i_0 + 3] * Gain;

    /* Product: '<S84>/Product' */
    FOC_FCF_B->U_uvw1[i_0] = I_phA_0;
  }

  /* End of Product: '<S84>/Product' */

  /* Trigonometry: '<S88>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_j = sinf(FOC_FCF_B->SelectControlMode[7]);

  /* Trigonometry: '<S88>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_h = cosf(FOC_FCF_B->SelectControlMode[7]);

  /* Gain: '<S88>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[0] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S88>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[0] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S88>/Sum1' incorporates:
   *  Gain: '<S88>/Gain'
   *  Gain: '<S88>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S88>/Product' incorporates:
   *  Sum: '<S88>/Sum1'
   */
  I_phA_0 = Sum1_lz;

  /* Gain: '<S88>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[1] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S88>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[1] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S88>/Sum1' incorporates:
   *  Gain: '<S88>/Gain'
   *  Gain: '<S88>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S88>/Product' incorporates:
   *  Sum: '<S88>/Sum1'
   */
  tmp_0 = Sum1_lz;

  /* Gain: '<S88>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[2] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S88>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[2] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S88>/Sum1' incorporates:
   *  Gain: '<S88>/Gain'
   *  Gain: '<S88>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S88>/Product' incorporates:
   *  Sum: '<S88>/Sum1'
   */
  I_phA = Sum1_lz;

  /* Gain: '<S88>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[3] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S88>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_l[3] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S88>/Sum1' incorporates:
   *  Gain: '<S88>/Gain'
   *  Gain: '<S88>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S88>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[2];
  Gain = FOC_FCF_B->SelectControlMode[3];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S88>/Product' */
  FOC_FCF_B->Product_f[0] = I_phA_0;

  /* Product: '<S88>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_lz * Gain;

  /* Product: '<S88>/Product' */
  FOC_FCF_B->Product_f[1] = I_phA_0;

  /* Product: '<S85>/Product' incorporates:
   *  Constant: '<S85>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_g[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_f[0];
  Gain = FOC_FCF_B->Product_f[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    I_phA_0 = tmp[i_0] * TrafoMatrixuvwalphabeta;
    I_phA_0 += tmp[i_0 + 3] * Gain;

    /* Product: '<S85>/Product' */
    FOC_FCF_B->Product_f3[i_0] = I_phA_0;
  }

  /* End of Product: '<S85>/Product' */

  /* Trigonometry: '<S89>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_h = sinf(FOC_FCF_B->SelectControlMode[8]);

  /* Trigonometry: '<S89>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_hh = cosf(FOC_FCF_B->SelectControlMode[8]);

  /* Gain: '<S89>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[0] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S89>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_j[0] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[0] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S89>/Sum1' incorporates:
   *  Gain: '<S89>/Gain'
   *  Gain: '<S89>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S89>/Product' incorporates:
   *  Sum: '<S89>/Sum1'
   */
  I_phA_0 = Sum1_lz;

  /* Gain: '<S89>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[1] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S89>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_j[1] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[1] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S89>/Sum1' incorporates:
   *  Gain: '<S89>/Gain'
   *  Gain: '<S89>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S89>/Product' incorporates:
   *  Sum: '<S89>/Sum1'
   */
  tmp_0 = Sum1_lz;

  /* Gain: '<S89>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[2] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S89>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_j[2] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[2] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S89>/Sum1' incorporates:
   *  Gain: '<S89>/Gain'
   *  Gain: '<S89>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S89>/Product' incorporates:
   *  Sum: '<S89>/Sum1'
   */
  I_phA = Sum1_lz;

  /* Gain: '<S89>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[3] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S89>/Gain' */
  Gain = FOC_FCF_P.Gain_Gain_j[3] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[3] = Gain;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S89>/Sum1' incorporates:
   *  Gain: '<S89>/Gain'
   *  Gain: '<S89>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S89>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[4];
  Gain = FOC_FCF_B->SelectControlMode[5];
  I_phA_0 *= TrafoMatrixuvwalphabeta;
  I_phA_0 += I_phA * Gain;

  /* Product: '<S89>/Product' */
  FOC_FCF_B->Product_i[0] = I_phA_0;

  /* Product: '<S89>/Product' */
  I_phA_0 = tmp_0 * TrafoMatrixuvwalphabeta;
  I_phA_0 += Sum1_lz * Gain;

  /* Product: '<S89>/Product' */
  FOC_FCF_B->Product_i[1] = I_phA_0;

  /* Product: '<S86>/Product' incorporates:
   *  Constant: '<S86>/Constant'
   */
  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp[i_0] = FOC_FCF_P.Constant_Value_o[i_0];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_i[0];
  Gain = FOC_FCF_B->Product_i[1];
  for (i_0 = 0; i_0 < 3; i_0++) {
    I_phA_0 = tmp[i_0] * TrafoMatrixuvwalphabeta;
    I_phA_0 += tmp[i_0 + 3] * Gain;

    /* Product: '<S86>/Product' */
    FOC_FCF_B->Product_fb[i_0] = I_phA_0;
  }

  /* End of Product: '<S86>/Product' */

  /* MultiPortSwitch: '<S1>/U_DC_switch' incorporates:
   *  Constant: '<S1>/0: P_Udc 1: Udc_measured'
   */
  if (FOC_FCF_P.FOC_SELECT_U_DC_INPUT == 0) {
    /* MultiPortSwitch: '<S1>/U_DC_switch' incorporates:
     *  Constant: '<S1>/Udc1'
     */
    FOC_FCF_B->U_DC_fcf = FOC_FCF_P.FOC_MANUAL_U_DC;
  } else {
    /* MultiPortSwitch: '<S1>/U_DC_switch' */
    FOC_FCF_B->U_DC_fcf = FOC_FCF_U->U_DC;
  }

  /* End of MultiPortSwitch: '<S1>/U_DC_switch' */

  /* Outputs for Atomic SubSystem: '<S14>/NormalizedVoltage' */
  /* Gain: '<S81>/U_DC//2' */
  FOC_FCF_B->U_DC2 = FOC_FCF_P.U_DC2_Gain_p * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S81>/AvoidDivBy0' incorporates:
   *  Constant: '<S81>/Constant2'
   */
  tmp_0 = fmaxf(FOC_FCF_P.Constant2_Value_g, FOC_FCF_B->U_DC2);

  /* MinMax: '<S81>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0 = tmp_0;

  /* Product: '<S81>/DutyCycle_normalized' */
  FOC_FCF_B->DutyCycle_normed[0] = FOC_FCF_B->U_uvw1[0] / FOC_FCF_B->AvoidDivBy0;
  FOC_FCF_B->DutyCycle_normed[3] = FOC_FCF_B->Product_f3[0] /
    FOC_FCF_B->AvoidDivBy0;
  FOC_FCF_B->DutyCycle_normed[6] = FOC_FCF_B->Product_fb[0] /
    FOC_FCF_B->AvoidDivBy0;
  FOC_FCF_B->DutyCycle_normed[1] = FOC_FCF_B->U_uvw1[1] / FOC_FCF_B->AvoidDivBy0;
  FOC_FCF_B->DutyCycle_normed[4] = FOC_FCF_B->Product_f3[1] /
    FOC_FCF_B->AvoidDivBy0;
  FOC_FCF_B->DutyCycle_normed[7] = FOC_FCF_B->Product_fb[1] /
    FOC_FCF_B->AvoidDivBy0;
  FOC_FCF_B->DutyCycle_normed[2] = FOC_FCF_B->U_uvw1[2] / FOC_FCF_B->AvoidDivBy0;
  FOC_FCF_B->DutyCycle_normed[5] = FOC_FCF_B->Product_f3[2] /
    FOC_FCF_B->AvoidDivBy0;
  FOC_FCF_B->DutyCycle_normed[8] = FOC_FCF_B->Product_fb[2] /
    FOC_FCF_B->AvoidDivBy0;

  /* End of Outputs for SubSystem: '<S14>/NormalizedVoltage' */

  /* Outputs for Atomic SubSystem: '<S14>/Super_Sinus_Modulation' */
  /* MinMax: '<S83>/MinMax2' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[0];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[1]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S83>/MinMax2' */
  FOC_FCF_B->MinMax2 = tmp_0;

  /* MinMax: '<S83>/MinMax3' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[0];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[1]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S83>/MinMax3' */
  FOC_FCF_B->MinMax3 = tmp_0;

  /* Sum: '<S83>/Sum1' */
  FOC_FCF_B->Sum1_o = FOC_FCF_B->MinMax2 + FOC_FCF_B->MinMax3;

  /* Gain: '<S83>/Factor' */
  FOC_FCF_B->Factor = FOC_FCF_P.Factor_Gain * FOC_FCF_B->Sum1_o;

  /* Sum: '<S83>/DutyCycle_SuperSinus_1' */
  FOC_FCF_B->DutyCycle_SuperSinus_1[0] = FOC_FCF_B->DutyCycle_normed[0] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[1] = FOC_FCF_B->DutyCycle_normed[1] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[2] = FOC_FCF_B->DutyCycle_normed[2] -
    FOC_FCF_B->Factor;

  /* MinMax: '<S83>/MinMax1' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[3];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[4]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S83>/MinMax1' */
  FOC_FCF_B->MinMax1 = tmp_0;

  /* MinMax: '<S83>/MinMax4' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[3];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[4]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S83>/MinMax4' */
  FOC_FCF_B->MinMax4 = tmp_0;

  /* Sum: '<S83>/Sum2' */
  FOC_FCF_B->Sum2_i = FOC_FCF_B->MinMax1 + FOC_FCF_B->MinMax4;

  /* Gain: '<S83>/Factor1' */
  FOC_FCF_B->Factor1 = FOC_FCF_P.Factor1_Gain * FOC_FCF_B->Sum2_i;

  /* Sum: '<S83>/DutyCycle_SuperSinus_2' */
  FOC_FCF_B->DutyCycle_SuperSinus_2[0] = FOC_FCF_B->DutyCycle_normed[3] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[1] = FOC_FCF_B->DutyCycle_normed[4] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[2] = FOC_FCF_B->DutyCycle_normed[5] -
    FOC_FCF_B->Factor1;

  /* MinMax: '<S83>/MinMax5' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[6];
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[7]);
  tmp_0 = fminf(tmp_0, FOC_FCF_B->DutyCycle_normed[8]);

  /* MinMax: '<S83>/MinMax5' */
  FOC_FCF_B->MinMax5 = tmp_0;

  /* MinMax: '<S83>/MinMax6' */
  tmp_0 = FOC_FCF_B->DutyCycle_normed[6];
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[7]);
  tmp_0 = fmaxf(tmp_0, FOC_FCF_B->DutyCycle_normed[8]);

  /* MinMax: '<S83>/MinMax6' */
  FOC_FCF_B->MinMax6 = tmp_0;

  /* Sum: '<S83>/Sum3' */
  FOC_FCF_B->Sum3_k = FOC_FCF_B->MinMax5 + FOC_FCF_B->MinMax6;

  /* Gain: '<S83>/Factor2' */
  FOC_FCF_B->Factor2 = FOC_FCF_P.Factor2_Gain * FOC_FCF_B->Sum3_k;

  /* Sum: '<S83>/DutyCycle_SuperSinus_3' */
  FOC_FCF_B->DutyCycle_SuperSinus_3[0] = FOC_FCF_B->DutyCycle_normed[6] -
    FOC_FCF_B->Factor2;
  FOC_FCF_B->DutyCycle_SuperSinus_3[1] = FOC_FCF_B->DutyCycle_normed[7] -
    FOC_FCF_B->Factor2;
  FOC_FCF_B->DutyCycle_SuperSinus_3[2] = FOC_FCF_B->DutyCycle_normed[8] -
    FOC_FCF_B->Factor2;

  /* End of Outputs for SubSystem: '<S14>/Super_Sinus_Modulation' */

  /* MultiPortSwitch: '<S14>/SelectModulation' incorporates:
   *  Constant: '<S14>/Enable_SuperSinMod'
   */
  if (FOC_FCF_P.FOC_SELECT_Modulation == 0) {
    /* MultiPortSwitch: '<S14>/SelectModulation' */
    for (i = 0; i < 9; i++) {
      FOC_FCF_B->SelMod_DutyCycles[i] = FOC_FCF_B->DutyCycle_normed[i];
    }
  } else {
    /* MultiPortSwitch: '<S14>/SelectModulation' */
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

  /* End of MultiPortSwitch: '<S14>/SelectModulation' */
  for (i = 0; i < 9; i++) {
    /* Bias: '<S79>/Scale [0..2]' */
    tmp_0 = FOC_FCF_B->SelMod_DutyCycles[i] + FOC_FCF_P.Scale02_Bias;
    FOC_FCF_B->Scale02[i] = tmp_0;

    /* Gain: '<S79>/Scale  [0..1]' */
    tmp_0 *= FOC_FCF_P.Scale01_Gain;
    FOC_FCF_B->Scale01[i] = tmp_0;

    /* Saturate: '<S79>/Limit [0..1]' */
    if (tmp_0 > FOC_FCF_P.Limit01_UpperSat) {
      tmp_0 = FOC_FCF_P.Limit01_UpperSat;
    } else if (tmp_0 < FOC_FCF_P.Limit01_LowerSat) {
      tmp_0 = FOC_FCF_P.Limit01_LowerSat;
    }

    /* Saturate: '<S79>/Limit [0..1]' */
    FOC_FCF_B->Limit01[i] = tmp_0;
  }

  /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_1' incorporates:
   *  Constant: '<S82>/Constant6'
   */
  switch ((int32_T)FOC_FCF_P.FOC_SELECT_Voltage_Assignment_UVW) {
   case 1:
    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[2];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[5];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[8];
    break;

   case 2:
    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[1];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[4];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[7];
    break;

   case 3:
    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[2];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[5];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[8];
    break;

   case 4:
    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[0];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[3];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[6];
    break;

   case 5:
    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[1];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[4];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[7];
    break;

   default:
    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[0];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[3];

    /* MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[6];
    break;
  }

  /* End of MultiPortSwitch: '<S82>/Select_GateDriver_Assignment_1' */

  /* Sum: '<S15>/Deviation' */
  FOC_FCF_B->Deviation = FOC_FCF_B->Sum3 - FOC_FCF_B->phi_el_observer;

  /* Product: '<S15>/Product2' incorporates:
   *  Constant: '<S15>/Constant'
   *  Constant: '<S15>/Constant1'
   */
  FOC_FCF_B->Product2 = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_D * FOC_FCF_B->Deviation;

  /* Gain: '<S15>/Gain' */
  FOC_FCF_B->Gain_g = FOC_FCF_P.Gain_Gain_k * FOC_FCF_B->Product2;

  /* Gain: '<S15>/Gain4' */
  FOC_FCF_B->winkelimpuls = FOC_FCF_P.FOC_OmegaObs3 * FOC_FCF_B->Deviation;

  /* Sum: '<S15>/Sum1' */
  FOC_FCF_B->Sum1_g4 = FOC_FCF_B->Gain_g + FOC_FCF_B->w_el;

  /* Product: '<S15>/Product' incorporates:
   *  Constant: '<S15>/FOC_T_fast'
   */
  FOC_FCF_B->Product_o = FOC_FCF_B->Sum1_g4 * FOC_FCF_P.FOC_T_fast_Value_df;

  /* Product: '<S15>/Product1' incorporates:
   *  Constant: '<S15>/Constant'
   */
  FOC_FCF_B->Product1_bi = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_w0 * FOC_FCF_B->Deviation;

  /* UnitDelay: '<S19>/Unit Delay1' */
  FOC_FCF_B->UnitDelay1 = FOC_FCF_DW->UnitDelay1_DSTATE_i;

  /* Sum: '<S15>/Sum2' */
  FOC_FCF_B->Sum2_mq = FOC_FCF_B->Product1_bi + FOC_FCF_B->UnitDelay1;

  /* Sum: '<S15>/Sum6' */
  FOC_FCF_B->Sum6 = FOC_FCF_B->Product_o + FOC_FCF_B->phi_el_observer;

  /* Product: '<S18>/Product' incorporates:
   *  Constant: '<S18>/FOC_T_fast'
   */
  FOC_FCF_B->Product_n = FOC_FCF_B->Sum2_mq * FOC_FCF_P.FOC_T_fast_Value_c;

  /* Sum: '<S18>/Sum2' */
  FOC_FCF_B->Sum2_e = FOC_FCF_B->Product_n + FOC_FCF_B->w_el;

  /* Product: '<S19>/Product' incorporates:
   *  Constant: '<S19>/FOC_T_fast'
   */
  FOC_FCF_B->Product_cd = FOC_FCF_B->winkelimpuls * FOC_FCF_P.FOC_T_fast_Value_k;

  /* Sum: '<S19>/Sum2' */
  FOC_FCF_B->Sum2_j = FOC_FCF_B->Product_cd + FOC_FCF_B->UnitDelay1;

  /* Gain: '<S4>/Gain1' */
  FOC_FCF_B->phi_el_U_trafo[0] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Switch2;
  FOC_FCF_B->phi_el_U_trafo[1] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Sum2_p;
  FOC_FCF_B->phi_el_U_trafo[2] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Sum1_l;

  /* Outputs for Atomic SubSystem: '<S14>/Calc_Modulation_Index' */
  /* Gain: '<S80>/U_DC//2' */
  FOC_FCF_B->U_DC2_l = FOC_FCF_P.U_DC2_Gain * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S80>/AvoidDivBy0' incorporates:
   *  Constant: '<S80>/Constant2'
   */
  tmp_0 = fmaxf(FOC_FCF_P.Constant2_Value_d, FOC_FCF_B->U_DC2_l);

  /* MinMax: '<S80>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0_f = tmp_0;

  /* Math: '<S80>/Square' */
  tmp_0 = FOC_FCF_B->Product_c0[0];

  /* Math: '<S80>/Square' */
  FOC_FCF_B->Square[0] = tmp_0 * tmp_0;

  /* Math: '<S80>/Square' */
  tmp_0 = FOC_FCF_B->Product_c0[1];

  /* Math: '<S80>/Square' */
  FOC_FCF_B->Square[1] = tmp_0 * tmp_0;

  /* Sum: '<S80>/Sum' */
  tmp_0 = FOC_FCF_B->Square[0];

  /* Math: '<S80>/Square1' */
  I_phA = FOC_FCF_B->Product_f[0];

  /* Math: '<S80>/Square1' */
  FOC_FCF_B->Square1[0] = I_phA * I_phA;

  /* Sum: '<S80>/Sum' */
  tmp_0 += FOC_FCF_B->Square[1];

  /* Math: '<S80>/Square1' */
  I_phA = FOC_FCF_B->Product_f[1];

  /* Math: '<S80>/Square1' */
  FOC_FCF_B->Square1[1] = I_phA * I_phA;

  /* Sum: '<S80>/Sum' */
  FOC_FCF_B->Sum_kr = tmp_0;

  /* Sqrt: '<S80>/Sqrt' */
  FOC_FCF_B->Sqrt = sqrtf(FOC_FCF_B->Sum_kr);

  /* Sum: '<S80>/Sum1' */
  tmp_0 = FOC_FCF_B->Square1[0];

  /* Math: '<S80>/Square2' */
  I_phA = FOC_FCF_B->Product_i[0];

  /* Math: '<S80>/Square2' */
  FOC_FCF_B->Square2[0] = I_phA * I_phA;

  /* Sum: '<S80>/Sum1' */
  tmp_0 += FOC_FCF_B->Square1[1];

  /* Math: '<S80>/Square2' */
  I_phA = FOC_FCF_B->Product_i[1];

  /* Math: '<S80>/Square2' */
  FOC_FCF_B->Square2[1] = I_phA * I_phA;

  /* Sum: '<S80>/Sum1' */
  FOC_FCF_B->Sum1_a = tmp_0;

  /* Sqrt: '<S80>/Sqrt1' */
  FOC_FCF_B->Sqrt1 = sqrtf(FOC_FCF_B->Sum1_a);

  /* Sum: '<S80>/Sum2' */
  tmp_0 = FOC_FCF_B->Square2[0];
  tmp_0 += FOC_FCF_B->Square2[1];

  /* Sum: '<S80>/Sum2' */
  FOC_FCF_B->Sum2_iq = tmp_0;

  /* Sqrt: '<S80>/Sqrt2' */
  FOC_FCF_B->Sqrt2 = sqrtf(FOC_FCF_B->Sum2_iq);

  /* Product: '<S80>/Divide3' */
  FOC_FCF_B->ModInd[0] = FOC_FCF_B->Sqrt / FOC_FCF_B->AvoidDivBy0_f;
  FOC_FCF_B->ModInd[1] = FOC_FCF_B->Sqrt1 / FOC_FCF_B->AvoidDivBy0_f;
  FOC_FCF_B->ModInd[2] = FOC_FCF_B->Sqrt2 / FOC_FCF_B->AvoidDivBy0_f;

  /* End of Outputs for SubSystem: '<S14>/Calc_Modulation_Index' */

  /* Switch: '<S2>/ASC_Switch' incorporates:
   *  Switch: '<S28>/IntegStopSwitch2'
   *  Switch: '<S32>/IntegStopSwitch2'
   *  Switch: '<S36>/IntegStopSwitch2'
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

    /* RelationalOperator: '<S27>/AntiWindupLE' incorporates:
     *  Constant: '<S27>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE_l = (FOC_FCF_B->ModInd[0] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S28>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1[0];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S28>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S28>/IntegStopSwitch3' incorporates:
       *  Constant: '<S28>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value[0];
    }

    /* Switch: '<S28>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[0] = I_phA;

    /* Sum: '<S28>/IntSum2' */
    FOC_FCF_B->IntSum2_j[0] = FOC_FCF_B->KPek1[0] + I_phA;

    /* Gain: '<S28>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S27>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[0] = FOC_FCF_B->IdqErr[0] * tmp_0;

    /* Switch: '<S28>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1[1];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S28>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S28>/IntegStopSwitch3' incorporates:
       *  Constant: '<S28>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value[1];
    }

    /* Switch: '<S28>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[1] = I_phA;

    /* Sum: '<S28>/IntSum2' */
    FOC_FCF_B->IntSum2_j[1] = FOC_FCF_B->KPek1[1] + I_phA;

    /* Gain: '<S28>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S27>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[1] = FOC_FCF_B->IdqErr[1] * tmp_0;

    /* RelationalOperator: '<S30>/Compare' incorporates:
     *  Constant: '<S30>/Constant'
     */
    FOC_FCF_B->Compare_o = (uint8_T)(FOC_FCF_B->antiWindupProd_o[1] <
      FOC_FCF_P.AntiWindupGT_q_const);

    /* Logic: '<S27>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q_o = (FOC_FCF_B->AntiWindupLE_l ||
      (FOC_FCF_B->Compare_o != 0));

    /* RelationalOperator: '<S29>/Compare' incorporates:
     *  Constant: '<S29>/Constant'
     */
    FOC_FCF_B->Compare_f = (uint8_T)(FOC_FCF_B->antiWindupProd_o[0] <
      FOC_FCF_P.AntiWindupGT_d_const);

    /* Logic: '<S27>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d_e = ((FOC_FCF_B->Compare_f != 0) ||
      FOC_FCF_B->AntiWindupLE_l);

    /* Switch: '<S28>/IntegStopSwitch1' */
    tmp_1 = FOC_FCF_B->AntiWindupOR_d_e;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q_o;
    if (tmp_1) {
      tmp_0 = FOC_FCF_B->IntSum2_j[0];

      /* Switch: '<S28>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_c[0];

      /* Switch: '<S28>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = tmp_0;
    }

    /* Switch: '<S28>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[0] = tmp_0;

    /* Switch: '<S28>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2_j[1];

      /* Switch: '<S28>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_c[1];

      /* Switch: '<S28>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = tmp_0;
    }

    /* Switch: '<S28>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[1] = tmp_0;

    /* RelationalOperator: '<S31>/AntiWindupLE' incorporates:
     *  Constant: '<S31>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE_f = (FOC_FCF_B->ModInd[1] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S32>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[0];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S32>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S32>/IntegStopSwitch3' incorporates:
       *  Constant: '<S32>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_l[0];
    }

    /* Switch: '<S32>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_n[0] = I_phA;

    /* Sum: '<S32>/IntSum2' */
    FOC_FCF_B->IntSum2_f[0] = FOC_FCF_B->KPek1_l[0] + I_phA;

    /* Gain: '<S32>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_g[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S31>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_d[0] = FOC_FCF_B->IdqErr_l[0] * tmp_0;

    /* Switch: '<S32>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_o[1];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S32>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S32>/IntegStopSwitch3' incorporates:
       *  Constant: '<S32>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_l[1];
    }

    /* Switch: '<S32>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_n[1] = I_phA;

    /* Sum: '<S32>/IntSum2' */
    FOC_FCF_B->IntSum2_f[1] = FOC_FCF_B->KPek1_l[1] + I_phA;

    /* Gain: '<S32>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_g[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S31>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_d[1] = FOC_FCF_B->IdqErr_l[1] * tmp_0;

    /* RelationalOperator: '<S34>/Compare' incorporates:
     *  Constant: '<S34>/Constant'
     */
    FOC_FCF_B->Compare_g = (uint8_T)(FOC_FCF_B->antiWindupProd_d[1] <
      FOC_FCF_P.AntiWindupGT_q_const_h);

    /* Logic: '<S31>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q_l = (FOC_FCF_B->AntiWindupLE_f ||
      (FOC_FCF_B->Compare_g != 0));

    /* RelationalOperator: '<S33>/Compare' incorporates:
     *  Constant: '<S33>/Constant'
     */
    FOC_FCF_B->Compare_i = (uint8_T)(FOC_FCF_B->antiWindupProd_d[0] <
      FOC_FCF_P.AntiWindupGT_d_const_n);

    /* Logic: '<S31>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d_m = ((FOC_FCF_B->Compare_i != 0) ||
      FOC_FCF_B->AntiWindupLE_f);

    /* Switch: '<S32>/IntegStopSwitch1' */
    tmp_1 = FOC_FCF_B->AntiWindupOR_d_m;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q_l;
    if (tmp_1) {
      tmp_0 = FOC_FCF_B->IntSum2_f[0];

      /* Switch: '<S32>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_g[0];

      /* Switch: '<S32>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[0] = tmp_0;
    }

    /* Switch: '<S32>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[0] = tmp_0;

    /* Switch: '<S32>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2_f[1];

      /* Switch: '<S32>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp_g[1];

      /* Switch: '<S32>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[1] = tmp_0;
    }

    /* Switch: '<S32>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[1] = tmp_0;

    /* RelationalOperator: '<S35>/AntiWindupLE' incorporates:
     *  Constant: '<S35>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE = (FOC_FCF_B->ModInd[2] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S36>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_d[0];
    if (FOC_FCF_B->Product1_b > FOC_FCF_P.IntegStopSwitch3_Threshold_ad) {
      /* Switch: '<S36>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S36>/IntegStopSwitch3' incorporates:
       *  Constant: '<S36>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_o[0];
    }

    /* Switch: '<S36>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[0] = I_phA;

    /* Sum: '<S36>/IntSum2' */
    FOC_FCF_B->IntSum2[0] = FOC_FCF_B->KPek1_h[0] + I_phA;

    /* Gain: '<S36>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[0] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S35>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[0] = FOC_FCF_B->IdqErr_e[0] * tmp_0;

    /* Switch: '<S36>/IntegStopSwitch3' */
    tmp_0 = FOC_FCF_B->IntegDelay1_d[1];
    if (FOC_FCF_B->Product1_b > FOC_FCF_P.IntegStopSwitch3_Threshold_ad) {
      /* Switch: '<S36>/IntegStopSwitch3' */
      I_phA = tmp_0;
    } else {
      /* Switch: '<S36>/IntegStopSwitch3' incorporates:
       *  Constant: '<S36>/Zero1'
       */
      I_phA = FOC_FCF_P.Zero1_Value_o[1];
    }

    /* Switch: '<S36>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[1] = I_phA;

    /* Sum: '<S36>/IntSum2' */
    FOC_FCF_B->IntSum2[1] = FOC_FCF_B->KPek1_h[1] + I_phA;

    /* Gain: '<S36>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[1] = FOC_FCF_P.FOC_IntegDamp * I_phA;

    /* Product: '<S35>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[1] = FOC_FCF_B->IdqErr_e[1] * tmp_0;

    /* RelationalOperator: '<S38>/Compare' incorporates:
     *  Constant: '<S38>/Constant'
     */
    FOC_FCF_B->Compare = (uint8_T)(FOC_FCF_B->antiWindupProd[1] <
      FOC_FCF_P.AntiWindupGT_q_const_l);

    /* Logic: '<S35>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q = (FOC_FCF_B->AntiWindupLE || (FOC_FCF_B->Compare
      != 0));

    /* RelationalOperator: '<S37>/Compare' incorporates:
     *  Constant: '<S37>/Constant'
     */
    FOC_FCF_B->Compare_k = (uint8_T)(FOC_FCF_B->antiWindupProd[0] <
      FOC_FCF_P.AntiWindupGT_d_const_f);

    /* Logic: '<S35>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d = ((FOC_FCF_B->Compare_k != 0) ||
      FOC_FCF_B->AntiWindupLE);

    /* Switch: '<S36>/IntegStopSwitch1' */
    tmp_1 = FOC_FCF_B->AntiWindupOR_d;
    tmp_idx_1 = FOC_FCF_B->AntiWindupOR_q;
    if (tmp_1) {
      tmp_0 = FOC_FCF_B->IntSum2[0];

      /* Switch: '<S36>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp[0];

      /* Switch: '<S36>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = tmp_0;
    }

    /* Switch: '<S36>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_h[0] = tmp_0;

    /* Switch: '<S36>/IntegStopSwitch1' */
    if (tmp_idx_1) {
      tmp_0 = FOC_FCF_B->IntSum2[1];

      /* Switch: '<S36>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = tmp_0;
    } else {
      tmp_0 = FOC_FCF_B->FOC_IntegDamp[1];

      /* Switch: '<S36>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = tmp_0;
    }

    /* Switch: '<S36>/IntegStopSwitch2' */
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

    /* Switch: '<S28>/IntegStopSwitch2' incorporates:
     *  Constant: '<S28>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2[0] = FOC_FCF_P.Zero1_Value[0];
    FOC_FCF_B->IntegStopSwitch2[1] = FOC_FCF_P.Zero1_Value[1];

    /* Switch: '<S32>/IntegStopSwitch2' incorporates:
     *  Constant: '<S32>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2_o[0] = FOC_FCF_P.Zero1_Value_l[0];
    FOC_FCF_B->IntegStopSwitch2_o[1] = FOC_FCF_P.Zero1_Value_l[1];

    /* Switch: '<S36>/IntegStopSwitch2' incorporates:
     *  Constant: '<S36>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2_h[0] = FOC_FCF_P.Zero1_Value_o[0];
    FOC_FCF_B->IntegStopSwitch2_h[1] = FOC_FCF_P.Zero1_Value_o[1];
  }

  /* End of Switch: '<S2>/ASC_Switch' */

  /* Gain: '<S21>/Gain1' */
  FOC_FCF_B->U_d1_CC = FOC_FCF_P.Gain1_Gain_cs * FOC_FCF_B->IntegEnaSwitch1[0];

  /* Gain: '<S21>/Gain2' */
  FOC_FCF_B->U_q1_CC = FOC_FCF_P.Gain2_Gain * FOC_FCF_B->IntegEnaSwitch1[1];

  /* DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
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

  /* End of DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */

  /* DiscreteFir: '<S25>/Discrete FIR Filter 20th order' */
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

  /* End of DiscreteFir: '<S25>/Discrete FIR Filter 20th order' */

  /* DiscreteFir: '<S26>/Discrete FIR Filter 20th order' */
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

  /* End of DiscreteFir: '<S26>/Discrete FIR Filter 20th order' */

  /* MultiPortSwitch: '<S7>/DataSourceSwitch' incorporates:
   *  Constant: '<S7>/SELECT_DataSource'
   */
  if (!FOC_FCF_P.SELECT_DataSource_Value) {
    /* MultiPortSwitch: '<S7>/DataSourceSwitch' */
    FOC_FCF_B->DataSourceSwitch = 0.0;
  } else {
    /* MultiPortSwitch: '<S7>/DataSourceSwitch' incorporates:
     *  Constant: '<S7>/NoError_Manual'
     */
    FOC_FCF_B->DataSourceSwitch = FOC_FCF_P.NoError_Manual_Value;
  }

  /* End of MultiPortSwitch: '<S7>/DataSourceSwitch' */

  /* RelationalOperator: '<S39>/Compare' incorporates:
   *  Constant: '<S39>/Constant'
   */
  FOC_FCF_B->bus_InvStatus.Gate_Driver_FLT_Error =
    (FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_FLT !=
     FOC_FCF_P.Constant_Value_d2);

  /* RelationalOperator: '<S40>/Compare' incorporates:
   *  Constant: '<S40>/Constant'
   */
  FOC_FCF_B->bus_InvStatus.Gate_Driver_RDY_Error =
    (FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_RDY != FOC_FCF_P.Constant_Value_a);

  /* S-Function (sfix_bitop): '<S8>/Mask_6Bits_Inv1_FLT' */
  FOC_FCF_B->Mask_6Bits_Inv1_FLT = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_FLT
    & FOC_FCF_P.Mask_6Bits_Inv1_FLT_BitMask;

  /* S-Function (sfix_bitop): '<S41>/Bitwise NOT' */
  FOC_FCF_B->BitwiseNOT = ~FOC_FCF_B->Mask_6Bits_Inv1_FLT;

  /* S-Function (sfix_bitop): '<S41>/MaskBit0' */
  FOC_FCF_B->MaskBit0 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit0_BitMask;

  /* ArithShift: '<S41>/get_U_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S41>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_FLT = FOC_FCF_B->MaskBit0;

  /* DataTypeConversion: '<S8>/Data Type Conversion14' */
  FOC_FCF_B->bus_InvStatus.U1_HS_FLT = (FOC_FCF_B->get_U_HS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S41>/MaskBit1' */
  FOC_FCF_B->MaskBit1 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit1_BitMask;

  /* ArithShift: '<S41>/get_U_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S41>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_FLT = FOC_FCF_B->MaskBit1 >> 1;

  /* DataTypeConversion: '<S8>/Data Type Conversion17' */
  FOC_FCF_B->bus_InvStatus.U1_LS_FLT = (FOC_FCF_B->get_U_LS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S41>/MaskBit2' */
  FOC_FCF_B->MaskBit2 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit2_BitMask;

  /* ArithShift: '<S41>/get_V_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S41>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_FLT = FOC_FCF_B->MaskBit2 >> 2;

  /* DataTypeConversion: '<S8>/Data Type Conversion15' */
  FOC_FCF_B->bus_InvStatus.V1_HS_FLT = (FOC_FCF_B->get_V_HS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S41>/MaskBit3' */
  FOC_FCF_B->MaskBit3 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit3_BitMask;

  /* ArithShift: '<S41>/get_V_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S41>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_FLT = FOC_FCF_B->MaskBit3 >> 3;

  /* DataTypeConversion: '<S8>/Data Type Conversion18' */
  FOC_FCF_B->bus_InvStatus.V1_LS_FLT = (FOC_FCF_B->get_V_LS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S41>/MaskBit4' */
  FOC_FCF_B->MaskBit4 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit4_BitMask;

  /* ArithShift: '<S41>/get_W_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S41>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_FLT = FOC_FCF_B->MaskBit4 >> 4;

  /* DataTypeConversion: '<S8>/Data Type Conversion16' */
  FOC_FCF_B->bus_InvStatus.W1_HS_FLT = (FOC_FCF_B->get_W_HS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S41>/MaskBit5' */
  FOC_FCF_B->MaskBit5 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit5_BitMask;

  /* ArithShift: '<S41>/get_W_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S41>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_FLT = FOC_FCF_B->MaskBit5 >> 5;

  /* DataTypeConversion: '<S8>/Data Type Conversion19' */
  FOC_FCF_B->bus_InvStatus.W1_LS_FLT = (FOC_FCF_B->get_W_LS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S8>/Mask_6Bits_Inv1_RDY' */
  FOC_FCF_B->Mask_6Bits_Inv1_RDY = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_RDY
    & FOC_FCF_P.Mask_6Bits_Inv1_RDY_BitMask;

  /* S-Function (sfix_bitop): '<S42>/MaskBit0' */
  FOC_FCF_B->MaskBit0_c = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit0_BitMask_b;

  /* ArithShift: '<S42>/get_U_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S42>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_RDY = FOC_FCF_B->MaskBit0_c;

  /* DataTypeConversion: '<S8>/Data Type Conversion1' */
  FOC_FCF_B->bus_InvStatus.U1_HS_RDY = (FOC_FCF_B->get_U_HS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S42>/MaskBit1' */
  FOC_FCF_B->MaskBit1_b = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit1_BitMask_j;

  /* ArithShift: '<S42>/get_U_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S42>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_RDY = FOC_FCF_B->MaskBit1_b >> 1;

  /* DataTypeConversion: '<S8>/Data Type Conversion2' */
  FOC_FCF_B->bus_InvStatus.U1_LS_RDY = (FOC_FCF_B->get_U_LS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S42>/MaskBit2' */
  FOC_FCF_B->MaskBit2_n = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit2_BitMask_m;

  /* ArithShift: '<S42>/get_V_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S42>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_RDY = FOC_FCF_B->MaskBit2_n >> 2;

  /* DataTypeConversion: '<S8>/Data Type Conversion3' */
  FOC_FCF_B->bus_InvStatus.V1_HS_RDY = (FOC_FCF_B->get_V_HS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S42>/MaskBit3' */
  FOC_FCF_B->MaskBit3_a = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit3_BitMask_i;

  /* ArithShift: '<S42>/get_V_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S42>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_RDY = FOC_FCF_B->MaskBit3_a >> 3;

  /* DataTypeConversion: '<S8>/Data Type Conversion4' */
  FOC_FCF_B->bus_InvStatus.V1_LS_RDY = (FOC_FCF_B->get_V_LS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S42>/MaskBit4' */
  FOC_FCF_B->MaskBit4_c = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit4_BitMask_d;

  /* ArithShift: '<S42>/get_W_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S42>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_RDY = FOC_FCF_B->MaskBit4_c >> 4;

  /* DataTypeConversion: '<S8>/Data Type Conversion5' */
  FOC_FCF_B->bus_InvStatus.W1_HS_RDY = (FOC_FCF_B->get_W_HS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S42>/MaskBit5' */
  FOC_FCF_B->MaskBit5_l = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit5_BitMask_a;

  /* ArithShift: '<S42>/get_W_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S42>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_RDY = FOC_FCF_B->MaskBit5_l >> 5;

  /* DataTypeConversion: '<S8>/Data Type Conversion6' */
  FOC_FCF_B->bus_InvStatus.W1_LS_RDY = (FOC_FCF_B->get_W_LS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S8>/Mask_6Bits_Inv2_FLT' */
  FOC_FCF_B->Mask_6Bits_Inv2_FLT = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_FLT
    & FOC_FCF_P.Mask_6Bits_Inv2_FLT_BitMask;

  /* S-Function (sfix_bitop): '<S43>/Bitwise NOT' */
  FOC_FCF_B->BitwiseNOT_j = ~FOC_FCF_B->Mask_6Bits_Inv2_FLT;

  /* S-Function (sfix_bitop): '<S43>/MaskBit0' */
  FOC_FCF_B->MaskBit0_o = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit0_BitMask_g;

  /* ArithShift: '<S43>/get_U_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S43>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_FLT_i = FOC_FCF_B->MaskBit0_o;

  /* DataTypeConversion: '<S8>/Data Type Conversion20' */
  FOC_FCF_B->bus_InvStatus.U2_HS_FLT = (FOC_FCF_B->get_U_HS_FLT_i != 0U);

  /* S-Function (sfix_bitop): '<S43>/MaskBit1' */
  FOC_FCF_B->MaskBit1_ba = FOC_FCF_B->BitwiseNOT_j &
    FOC_FCF_P.MaskBit1_BitMask_n;

  /* ArithShift: '<S43>/get_U_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S43>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_FLT_a = FOC_FCF_B->MaskBit1_ba >> 1;

  /* DataTypeConversion: '<S8>/Data Type Conversion23' */
  FOC_FCF_B->bus_InvStatus.U2_LS_FLT = (FOC_FCF_B->get_U_LS_FLT_a != 0U);

  /* S-Function (sfix_bitop): '<S43>/MaskBit2' */
  FOC_FCF_B->MaskBit2_d = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit2_BitMask_n;

  /* ArithShift: '<S43>/get_V_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S43>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_FLT_i = FOC_FCF_B->MaskBit2_d >> 2;

  /* DataTypeConversion: '<S8>/Data Type Conversion21' */
  FOC_FCF_B->bus_InvStatus.V2_HS_FLT = (FOC_FCF_B->get_V_HS_FLT_i != 0U);

  /* S-Function (sfix_bitop): '<S43>/MaskBit3' */
  FOC_FCF_B->MaskBit3_d = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit3_BitMask_c;

  /* ArithShift: '<S43>/get_V_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S43>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_FLT_c = FOC_FCF_B->MaskBit3_d >> 3;

  /* DataTypeConversion: '<S8>/Data Type Conversion24' */
  FOC_FCF_B->bus_InvStatus.V2_LS_FLT = (FOC_FCF_B->get_V_LS_FLT_c != 0U);

  /* S-Function (sfix_bitop): '<S43>/MaskBit4' */
  FOC_FCF_B->MaskBit4_p = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit4_BitMask_o;

  /* ArithShift: '<S43>/get_W_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S43>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_FLT_f = FOC_FCF_B->MaskBit4_p >> 4;

  /* DataTypeConversion: '<S8>/Data Type Conversion22' */
  FOC_FCF_B->bus_InvStatus.W2_HS_FLT = (FOC_FCF_B->get_W_HS_FLT_f != 0U);

  /* S-Function (sfix_bitop): '<S43>/MaskBit5' */
  FOC_FCF_B->MaskBit5_o = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit5_BitMask_h;

  /* ArithShift: '<S43>/get_W_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S43>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_FLT_l = FOC_FCF_B->MaskBit5_o >> 5;

  /* DataTypeConversion: '<S8>/Data Type Conversion25' */
  FOC_FCF_B->bus_InvStatus.W2_LS_FLT = (FOC_FCF_B->get_W_LS_FLT_l != 0U);

  /* S-Function (sfix_bitop): '<S8>/Mask_6Bits_Inv2_RDY' */
  FOC_FCF_B->Mask_6Bits_Inv2_RDY = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_RDY
    & FOC_FCF_P.Mask_6Bits_Inv2_RDY_BitMask;

  /* S-Function (sfix_bitop): '<S44>/MaskBit0' */
  FOC_FCF_B->MaskBit0_p = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit0_BitMask_bn;

  /* ArithShift: '<S44>/get_U_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S44>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_RDY_i = FOC_FCF_B->MaskBit0_p;

  /* DataTypeConversion: '<S8>/Data Type Conversion7' */
  FOC_FCF_B->bus_InvStatus.U2_HS_RDY = (FOC_FCF_B->get_U_HS_RDY_i != 0U);

  /* S-Function (sfix_bitop): '<S44>/MaskBit1' */
  FOC_FCF_B->MaskBit1_m = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit1_BitMask_a;

  /* ArithShift: '<S44>/get_U_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S44>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_RDY_f = FOC_FCF_B->MaskBit1_m >> 1;

  /* DataTypeConversion: '<S8>/Data Type Conversion26' */
  FOC_FCF_B->bus_InvStatus.U2_LS_RDY = (FOC_FCF_B->get_U_LS_RDY_f != 0U);

  /* S-Function (sfix_bitop): '<S44>/MaskBit2' */
  FOC_FCF_B->MaskBit2_g = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit2_BitMask_o;

  /* ArithShift: '<S44>/get_V_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S44>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_RDY_j = FOC_FCF_B->MaskBit2_g >> 2;

  /* DataTypeConversion: '<S8>/Data Type Conversion27' */
  FOC_FCF_B->bus_InvStatus.V2_HS_RDY = (FOC_FCF_B->get_V_HS_RDY_j != 0U);

  /* S-Function (sfix_bitop): '<S44>/MaskBit3' */
  FOC_FCF_B->MaskBit3_k = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit3_BitMask_h;

  /* ArithShift: '<S44>/get_V_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S44>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_RDY_a = FOC_FCF_B->MaskBit3_k >> 3;

  /* DataTypeConversion: '<S8>/Data Type Conversion28' */
  FOC_FCF_B->bus_InvStatus.V2_LS_RDY = (FOC_FCF_B->get_V_LS_RDY_a != 0U);

  /* S-Function (sfix_bitop): '<S44>/MaskBit4' */
  FOC_FCF_B->MaskBit4_l = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit4_BitMask_e;

  /* ArithShift: '<S44>/get_W_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S44>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_RDY_n = FOC_FCF_B->MaskBit4_l >> 4;

  /* DataTypeConversion: '<S8>/Data Type Conversion29' */
  FOC_FCF_B->bus_InvStatus.W2_HS_RDY = (FOC_FCF_B->get_W_HS_RDY_n != 0U);

  /* S-Function (sfix_bitop): '<S44>/MaskBit5' */
  FOC_FCF_B->MaskBit5_lb = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit5_BitMask_l;

  /* ArithShift: '<S44>/get_W_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S44>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_RDY_l = FOC_FCF_B->MaskBit5_lb >> 5;

  /* DataTypeConversion: '<S8>/Data Type Conversion30' */
  FOC_FCF_B->bus_InvStatus.W2_LS_RDY = (FOC_FCF_B->get_W_LS_RDY_l != 0U);

  /* S-Function (sfix_bitop): '<S8>/Mask_6Bits_Inv3_FLT' */
  FOC_FCF_B->Mask_6Bits_Inv3_FLT = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_FLT
    & FOC_FCF_P.Mask_6Bits_Inv3_FLT_BitMask;

  /* S-Function (sfix_bitop): '<S45>/Bitwise NOT' */
  FOC_FCF_B->BitwiseNOT_c = ~FOC_FCF_B->Mask_6Bits_Inv3_FLT;

  /* S-Function (sfix_bitop): '<S45>/MaskBit0' */
  FOC_FCF_B->MaskBit0_ph = FOC_FCF_B->BitwiseNOT_c &
    FOC_FCF_P.MaskBit0_BitMask_m;

  /* ArithShift: '<S45>/get_U_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S45>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_FLT_m = FOC_FCF_B->MaskBit0_ph;

  /* DataTypeConversion: '<S8>/Data Type Conversion8' */
  FOC_FCF_B->bus_InvStatus.U3_HS_FLT = (FOC_FCF_B->get_U_HS_FLT_m != 0U);

  /* S-Function (sfix_bitop): '<S45>/MaskBit1' */
  FOC_FCF_B->MaskBit1_k = FOC_FCF_B->BitwiseNOT_c & FOC_FCF_P.MaskBit1_BitMask_d;

  /* ArithShift: '<S45>/get_U_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S45>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_FLT_h = FOC_FCF_B->MaskBit1_k >> 1;

  /* DataTypeConversion: '<S8>/Data Type Conversion11' */
  FOC_FCF_B->bus_InvStatus.U3_LS_FLT = (FOC_FCF_B->get_U_LS_FLT_h != 0U);

  /* S-Function (sfix_bitop): '<S45>/MaskBit2' */
  FOC_FCF_B->MaskBit2_f = FOC_FCF_B->BitwiseNOT_c & FOC_FCF_P.MaskBit2_BitMask_b;

  /* ArithShift: '<S45>/get_V_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S45>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_FLT_h = FOC_FCF_B->MaskBit2_f >> 2;

  /* DataTypeConversion: '<S8>/Data Type Conversion9' */
  FOC_FCF_B->bus_InvStatus.V3_HS_FLT = (FOC_FCF_B->get_V_HS_FLT_h != 0U);

  /* S-Function (sfix_bitop): '<S45>/MaskBit3' */
  FOC_FCF_B->MaskBit3_a2 = FOC_FCF_B->BitwiseNOT_c &
    FOC_FCF_P.MaskBit3_BitMask_l;

  /* ArithShift: '<S45>/get_V_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S45>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_FLT_g = FOC_FCF_B->MaskBit3_a2 >> 3;

  /* DataTypeConversion: '<S8>/Data Type Conversion12' */
  FOC_FCF_B->bus_InvStatus.V3_LS_FLT = (FOC_FCF_B->get_V_LS_FLT_g != 0U);

  /* S-Function (sfix_bitop): '<S45>/MaskBit4' */
  FOC_FCF_B->MaskBit4_f = FOC_FCF_B->BitwiseNOT_c & FOC_FCF_P.MaskBit4_BitMask_b;

  /* ArithShift: '<S45>/get_W_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S45>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_FLT_m = FOC_FCF_B->MaskBit4_f >> 4;

  /* DataTypeConversion: '<S8>/Data Type Conversion10' */
  FOC_FCF_B->bus_InvStatus.W3_HS_FLT = (FOC_FCF_B->get_W_HS_FLT_m != 0U);

  /* S-Function (sfix_bitop): '<S45>/MaskBit5' */
  FOC_FCF_B->MaskBit5_h = FOC_FCF_B->BitwiseNOT_c & FOC_FCF_P.MaskBit5_BitMask_e;

  /* ArithShift: '<S45>/get_W_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S45>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_FLT_g = FOC_FCF_B->MaskBit5_h >> 5;

  /* DataTypeConversion: '<S8>/Data Type Conversion13' */
  FOC_FCF_B->bus_InvStatus.W3_LS_FLT = (FOC_FCF_B->get_W_LS_FLT_g != 0U);

  /* S-Function (sfix_bitop): '<S8>/Mask_6Bits_Inv3_RDY' */
  FOC_FCF_B->Mask_6Bits_Inv3_RDY = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_RDY
    & FOC_FCF_P.Mask_6Bits_Inv3_RDY_BitMask;

  /* S-Function (sfix_bitop): '<S46>/MaskBit0' */
  FOC_FCF_B->MaskBit0_k = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit0_BitMask_l;

  /* ArithShift: '<S46>/get_U_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S46>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_RDY_e = FOC_FCF_B->MaskBit0_k;

  /* DataTypeConversion: '<S8>/Data Type Conversion36' */
  FOC_FCF_B->bus_InvStatus.U3_HS_RDY = (FOC_FCF_B->get_U_HS_RDY_e != 0U);

  /* S-Function (sfix_bitop): '<S46>/MaskBit1' */
  FOC_FCF_B->MaskBit1_o = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit1_BitMask_dr;

  /* ArithShift: '<S46>/get_U_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S46>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_RDY_l = FOC_FCF_B->MaskBit1_o >> 1;

  /* DataTypeConversion: '<S8>/Data Type Conversion31' */
  FOC_FCF_B->bus_InvStatus.U3_LS_RDY = (FOC_FCF_B->get_U_LS_RDY_l != 0U);

  /* S-Function (sfix_bitop): '<S46>/MaskBit2' */
  FOC_FCF_B->MaskBit2_a = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit2_BitMask_bx;

  /* ArithShift: '<S46>/get_V_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S46>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_RDY_e = FOC_FCF_B->MaskBit2_a >> 2;

  /* DataTypeConversion: '<S8>/Data Type Conversion32' */
  FOC_FCF_B->bus_InvStatus.V3_HS_RDY = (FOC_FCF_B->get_V_HS_RDY_e != 0U);

  /* S-Function (sfix_bitop): '<S46>/MaskBit3' */
  FOC_FCF_B->MaskBit3_kg = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit3_BitMask_it;

  /* ArithShift: '<S46>/get_V_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S46>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_RDY_k = FOC_FCF_B->MaskBit3_kg >> 3;

  /* DataTypeConversion: '<S8>/Data Type Conversion33' */
  FOC_FCF_B->bus_InvStatus.V3_LS_RDY = (FOC_FCF_B->get_V_LS_RDY_k != 0U);

  /* S-Function (sfix_bitop): '<S46>/MaskBit4' */
  FOC_FCF_B->MaskBit4_ch = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit4_BitMask_a;

  /* ArithShift: '<S46>/get_W_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S46>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_RDY_h = FOC_FCF_B->MaskBit4_ch >> 4;

  /* DataTypeConversion: '<S8>/Data Type Conversion34' */
  FOC_FCF_B->bus_InvStatus.W3_HS_RDY = (FOC_FCF_B->get_W_HS_RDY_h != 0U);

  /* S-Function (sfix_bitop): '<S46>/MaskBit5' */
  FOC_FCF_B->MaskBit5_p = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit5_BitMask_b;

  /* ArithShift: '<S46>/get_W_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S46>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_RDY_m = FOC_FCF_B->MaskBit5_p >> 5;

  /* DataTypeConversion: '<S8>/Data Type Conversion35' */
  FOC_FCF_B->bus_InvStatus.W3_LS_RDY = (FOC_FCF_B->get_W_LS_RDY_m != 0U);

  /* MultiPortSwitch: '<S7>/EN_FLT_Switch1' incorporates:
   *  Constant: '<S7>/ENABLE_GateDriver_FLT_Error'
   */
  if ((int32_T)FOC_FCF_P.ENABLE_GateDriver_FLT_Error == 0) {
    /* MultiPortSwitch: '<S7>/EN_FLT_Switch1' incorporates:
     *  Constant: '<S7>/NO_ERROR'
     */
    FOC_FCF_B->EN_FLT_Switch1 = FOC_FCF_P.NO_ERROR_Value;
  } else {
    /* MultiPortSwitch: '<S7>/EN_FLT_Switch1' */
    FOC_FCF_B->EN_FLT_Switch1 = FOC_FCF_B->bus_InvStatus.Gate_Driver_FLT_Error;
  }

  /* End of MultiPortSwitch: '<S7>/EN_FLT_Switch1' */

  /* MultiPortSwitch: '<S7>/EN_RDY_Switch' incorporates:
   *  Constant: '<S7>/ENABLE_GateDriver_RDY_Error'
   */
  if ((int32_T)FOC_FCF_P.ENABLE_GateDriver_RDY_Error == 0) {
    /* MultiPortSwitch: '<S7>/EN_RDY_Switch' incorporates:
     *  Constant: '<S7>/NO_ERROR'
     */
    FOC_FCF_B->EN_RDY_Switch = FOC_FCF_P.NO_ERROR_Value;
  } else {
    /* MultiPortSwitch: '<S7>/EN_RDY_Switch' */
    FOC_FCF_B->EN_RDY_Switch = FOC_FCF_B->bus_InvStatus.Gate_Driver_RDY_Error;
  }

  /* End of MultiPortSwitch: '<S7>/EN_RDY_Switch' */

  /* Gain: '<S11>/[1//s] => [rpm]' */
  FOC_FCF_B->usrpm = FOC_FCF_P.usrpm_Gain * FOC_FCF_B->w_el;

  /* Abs: '<S11>/Abs' */
  FOC_FCF_B->Abs_d = fabsf(FOC_FCF_B->usrpm);

  /* RelationalOperator: '<S73>/Compare' incorporates:
   *  Constant: '<S73>/Constant'
   */
  FOC_FCF_B->Compare_c = (FOC_FCF_B->Abs_d > FOC_FCF_P.LIMIT_MAX_Overspeed);

  /* Logic: '<S11>/Logical Operator3' incorporates:
   *  Constant: '<S11>/Reset_OS_Error'
   */
  FOC_FCF_B->LogicalOperator3_p = ((FOC_FCF_P.FOC_RESET_OS_Error != 0.0F) ||
    (FOC_FCF_U->global_reset_errors != 0.0F));

  /* RelationalOperator: '<S76>/Compare' incorporates:
   *  Constant: '<S76>/Constant'
   */
  FOC_FCF_B->Compare_gt = ((int32_T)FOC_FCF_B->LogicalOperator3_p > (int32_T)
    FOC_FCF_P.Constant_Value_ep);

  /* UnitDelay: '<S74>/Delay Input1'
   *
   * Block description for '<S74>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1_h = FOC_FCF_DW->DelayInput1_DSTATE_e;

  /* MultiPortSwitch: '<S11>/Selectphicalc2' incorporates:
   *  Constant: '<S11>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overspeed == 0) {
    /* MultiPortSwitch: '<S11>/Selectphicalc2' incorporates:
     *  Constant: '<S11>/Constant1'
     */
    FOC_FCF_B->Selectphicalc2_d = FOC_FCF_P.Constant1_Value_n;
  } else {
    /* RelationalOperator: '<S74>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator = ((int32_T)FOC_FCF_B->Compare_gt >
      (int32_T)FOC_FCF_B->Uk1_h);

    /* MultiPortSwitch: '<S11>/Selectphicalc2' */
    FOC_FCF_B->Selectphicalc2_d = FOC_FCF_B->FixPtRelationalOperator;
  }

  /* End of MultiPortSwitch: '<S11>/Selectphicalc2' */

  /* Memory: '<S75>/Memory' */
  FOC_FCF_B->Memory_k = FOC_FCF_DW->Memory_PreviousInput_i;

  /* CombinatorialLogic: '<S75>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_c;
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_d;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_k;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_e[0U] = FOC_FCF_P.Logic_table_lc[(uint32_T)i];
  FOC_FCF_B->Logic_e[1U] = FOC_FCF_P.Logic_table_lc[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S11>/Selectphicalc1' incorporates:
   *  Constant: '<S11>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overspeed == 0) {
    /* MultiPortSwitch: '<S11>/Selectphicalc1' incorporates:
     *  Constant: '<S11>/Constant2'
     */
    FOC_FCF_B->Selectphicalc1 = FOC_FCF_P.Constant2_Value_gw;
  } else {
    /* MultiPortSwitch: '<S11>/Selectphicalc1' */
    FOC_FCF_B->Selectphicalc1 = FOC_FCF_B->Logic_e[0];
  }

  /* End of MultiPortSwitch: '<S11>/Selectphicalc1' */

  /* DataTypeConversion: '<S11>/Data Type Conversion' */
  FOC_FCF_B->Overspeed_Error = FOC_FCF_B->Selectphicalc1;

  /* Logic: '<S7>/Logical Operator3' incorporates:
   *  Constant: '<S1>/FOC_MANUAL_Error'
   */
  FOC_FCF_B->LogicalOperator3_pp = ((!(FOC_FCF_P.FOC_MANUAL_Error != 0.0F)) && (
    !FOC_FCF_B->OC_OV_UV_ERROR) && (!(FOC_FCF_B->Overspeed_Error != 0.0)) &&
    (!(FOC_FCF_B->DataSourceSwitch != 0.0)) && (!(FOC_FCF_B->EN_FLT_Switch1 !=
    0.0F)) && (!(FOC_FCF_B->EN_RDY_Switch != 0.0F)));

  /* Logic: '<S7>/Enable_PWM_' */
  FOC_FCF_B->FOC_Enable_PWM = (FOC_FCF_B->LogicalOperator3_pp &&
    (FOC_FCF_U->FOC_Enable_PWM != 0.0F));

  /* Logic: '<S7>/Logical Operator6' */
  FOC_FCF_B->FCF_Error = !FOC_FCF_B->LogicalOperator3_pp;

  /* Abs: '<S47>/Abs' */
  FOC_FCF_B->Abs_e = fabsf(FOC_FCF_B->Add_mp);

  /* Switch: '<S47>/Switch' */
  if (FOC_FCF_B->Abs_e >= FOC_FCF_P.Switch_Threshold) {
    /* Signum: '<S47>/Sign' */
    tmp_0 = FOC_FCF_B->Product_h;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S47>/Sign' */
      FOC_FCF_B->Sign_d = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S47>/Sign' */
      FOC_FCF_B->Sign_d = -1.0F;
    } else {
      /* Signum: '<S47>/Sign' */
      FOC_FCF_B->Sign_d = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S47>/Sign' */

    /* Gain: '<S47>/Gain1' */
    FOC_FCF_B->Gain1_j = FOC_FCF_P.Gain1_Gain * FOC_FCF_B->Sign_d;

    /* Switch: '<S47>/Switch' */
    FOC_FCF_B->Switch_d = FOC_FCF_B->Gain1_j;
  } else {
    /* Switch: '<S47>/Switch' incorporates:
     *  Constant: '<S47>/Constant1'
     */
    FOC_FCF_B->Switch_d = FOC_FCF_P.Constant1_Value_c;
  }

  /* End of Switch: '<S47>/Switch' */

  /* Sum: '<S47>/Add1' */
  FOC_FCF_B->Add1 = FOC_FCF_B->Add_mp - FOC_FCF_B->Switch_d;
  for (i = 0; i < 9; i++) {
    /* RelationalOperator: '<S51>/Compare' incorporates:
     *  Constant: '<S51>/Constant'
     */
    FOC_FCF_B->Compare_gv[i] = (FOC_FCF_B->Abs[i] >
      FOC_FCF_P.FOC_LIMIT_Overcurrent_I_uvw);
  }

  /* Memory: '<S56>/Memory' */
  FOC_FCF_B->Memory_f = FOC_FCF_DW->Memory_PreviousInput_n;

  /* CombinatorialLogic: '<S56>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[0];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_f;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_g[0U] = FOC_FCF_P.Logic_table_l5[(uint32_T)i];
  FOC_FCF_B->Logic_g[1U] = FOC_FCF_P.Logic_table_l5[(uint32_T)i + 8U];

  /* Memory: '<S57>/Memory' */
  FOC_FCF_B->Memory_b = FOC_FCF_DW->Memory_PreviousInput_o;

  /* CombinatorialLogic: '<S57>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[1];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_b;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_i[0U] = FOC_FCF_P.Logic_table_p[(uint32_T)i];
  FOC_FCF_B->Logic_i[1U] = FOC_FCF_P.Logic_table_p[(uint32_T)i + 8U];

  /* Memory: '<S58>/Memory' */
  FOC_FCF_B->Memory_ok = FOC_FCF_DW->Memory_PreviousInput_nm;

  /* CombinatorialLogic: '<S58>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[2];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_ok;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_b[0U] = FOC_FCF_P.Logic_table_j[(uint32_T)i];
  FOC_FCF_B->Logic_b[1U] = FOC_FCF_P.Logic_table_j[(uint32_T)i + 8U];

  /* Memory: '<S59>/Memory' */
  FOC_FCF_B->Memory_c = FOC_FCF_DW->Memory_PreviousInput_ef;

  /* CombinatorialLogic: '<S59>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[3];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_c;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_p[0U] = FOC_FCF_P.Logic_table_o1[(uint32_T)i];
  FOC_FCF_B->Logic_p[1U] = FOC_FCF_P.Logic_table_o1[(uint32_T)i + 8U];

  /* Memory: '<S60>/Memory' */
  FOC_FCF_B->Memory_g = FOC_FCF_DW->Memory_PreviousInput_c;

  /* CombinatorialLogic: '<S60>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[4];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_g;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_d[0U] = FOC_FCF_P.Logic_table_i[(uint32_T)i];
  FOC_FCF_B->Logic_d[1U] = FOC_FCF_P.Logic_table_i[(uint32_T)i + 8U];

  /* Memory: '<S61>/Memory' */
  FOC_FCF_B->Memory_j = FOC_FCF_DW->Memory_PreviousInput_d;

  /* CombinatorialLogic: '<S61>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[5];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_j;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_ev[0U] = FOC_FCF_P.Logic_table_c[(uint32_T)i];
  FOC_FCF_B->Logic_ev[1U] = FOC_FCF_P.Logic_table_c[(uint32_T)i + 8U];

  /* Memory: '<S62>/Memory' */
  FOC_FCF_B->Memory_nb = FOC_FCF_DW->Memory_PreviousInput_os;

  /* CombinatorialLogic: '<S62>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[6];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_nb;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_bw[0U] = FOC_FCF_P.Logic_table_ij[(uint32_T)i];
  FOC_FCF_B->Logic_bw[1U] = FOC_FCF_P.Logic_table_ij[(uint32_T)i + 8U];

  /* Memory: '<S63>/Memory' */
  FOC_FCF_B->Memory_kp = FOC_FCF_DW->Memory_PreviousInput_f;

  /* CombinatorialLogic: '<S63>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[7];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_kp;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_ag[0U] = FOC_FCF_P.Logic_table_pd[(uint32_T)i];
  FOC_FCF_B->Logic_ag[1U] = FOC_FCF_P.Logic_table_pd[(uint32_T)i + 8U];

  /* Memory: '<S64>/Memory' */
  FOC_FCF_B->Memory_p = FOC_FCF_DW->Memory_PreviousInput_b;

  /* CombinatorialLogic: '<S64>/Logic' */
  tmp_1 = FOC_FCF_B->Compare_gv[8];
  i = tmp_1;
  tmp_1 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  tmp_1 = FOC_FCF_B->Memory_p;
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_FCF_B->Logic_f[0U] = FOC_FCF_P.Logic_table_a[(uint32_T)i];
  FOC_FCF_B->Logic_f[1U] = FOC_FCF_P.Logic_table_a[(uint32_T)i + 8U];

  /* DataTypeConversion: '<S53>/Data Type Conversion' */
  FOC_FCF_B->DataTypeConversion[0] = FOC_FCF_B->Logic_g[0];
  FOC_FCF_B->DataTypeConversion[1] = FOC_FCF_B->Logic_i[0];
  FOC_FCF_B->DataTypeConversion[2] = FOC_FCF_B->Logic_b[0];
  FOC_FCF_B->DataTypeConversion[3] = FOC_FCF_B->Logic_p[0];
  FOC_FCF_B->DataTypeConversion[4] = FOC_FCF_B->Logic_d[0];
  FOC_FCF_B->DataTypeConversion[5] = FOC_FCF_B->Logic_ev[0];
  FOC_FCF_B->DataTypeConversion[6] = FOC_FCF_B->Logic_bw[0];
  FOC_FCF_B->DataTypeConversion[7] = FOC_FCF_B->Logic_ag[0];
  FOC_FCF_B->DataTypeConversion[8] = FOC_FCF_B->Logic_f[0];

  /* Abs: '<S12>/Abs' */
  FOC_FCF_B->Abs_b = fabsf(FOC_FCF_B->Add_m);

  /* Switch: '<S12>/Switch' */
  if (FOC_FCF_B->Abs_b >= FOC_FCF_P.Switch_Threshold_b) {
    /* Signum: '<S12>/Sign' */
    tmp_0 = FOC_FCF_B->Product_e;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S12>/Sign' */
      FOC_FCF_B->Sign_n = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S12>/Sign' */
      FOC_FCF_B->Sign_n = -1.0F;
    } else {
      /* Signum: '<S12>/Sign' */
      FOC_FCF_B->Sign_n = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S12>/Sign' */

    /* Gain: '<S12>/Gain1' */
    FOC_FCF_B->Gain1_h = FOC_FCF_P.Gain1_Gain_c * FOC_FCF_B->Sign_n;

    /* Switch: '<S12>/Switch' */
    FOC_FCF_B->Switch_l = FOC_FCF_B->Gain1_h;
  } else {
    /* Switch: '<S12>/Switch' incorporates:
     *  Constant: '<S12>/Constant1'
     */
    FOC_FCF_B->Switch_l = FOC_FCF_P.Constant1_Value_k;
  }

  /* End of Switch: '<S12>/Switch' */

  /* Sum: '<S12>/Add1' */
  FOC_FCF_B->Add1_j = FOC_FCF_B->Add_m - FOC_FCF_B->Switch_l;

  /* Abs: '<S77>/Abs' */
  FOC_FCF_B->Abs_f = fabsf(FOC_FCF_B->Add);

  /* Switch: '<S77>/Switch' */
  if (FOC_FCF_B->Abs_f >= FOC_FCF_P.Switch_Threshold_c) {
    /* Signum: '<S77>/Sign' */
    tmp_0 = FOC_FCF_B->Product;
    if (rtIsNaNF(tmp_0)) {
      /* Signum: '<S77>/Sign' */
      FOC_FCF_B->Sign = (rtNaNF);
    } else if (tmp_0 < 0.0F) {
      /* Signum: '<S77>/Sign' */
      FOC_FCF_B->Sign = -1.0F;
    } else {
      /* Signum: '<S77>/Sign' */
      FOC_FCF_B->Sign = (real32_T)(tmp_0 > 0.0F);
    }

    /* End of Signum: '<S77>/Sign' */

    /* Gain: '<S77>/Gain1' */
    FOC_FCF_B->Gain1_o = FOC_FCF_P.Gain1_Gain_a * FOC_FCF_B->Sign;

    /* Switch: '<S77>/Switch' */
    FOC_FCF_B->Switch_n = FOC_FCF_B->Gain1_o;
  } else {
    /* Switch: '<S77>/Switch' incorporates:
     *  Constant: '<S77>/Constant1'
     */
    FOC_FCF_B->Switch_n = FOC_FCF_P.Constant1_Value_e;
  }

  /* End of Switch: '<S77>/Switch' */

  /* Sum: '<S77>/Add1' */
  FOC_FCF_B->Add1_c = FOC_FCF_B->Add - FOC_FCF_B->Switch_n;

  /* Gain: '<S14>/Gain' */
  FOC_FCF_B->U_d1 = FOC_FCF_P.Gain_Gain_jm * FOC_FCF_B->SelectControlMode[0];

  /* Gain: '<S14>/Gain1' */
  FOC_FCF_B->U_q1 = FOC_FCF_P.Gain1_Gain_e * FOC_FCF_B->SelectControlMode[1];

  /* Gain: '<S14>/Gain2' */
  FOC_FCF_B->U_alpha1 = FOC_FCF_P.Gain2_Gain_f * FOC_FCF_B->Product_c0[0];

  /* Gain: '<S14>/Gain3' */
  FOC_FCF_B->U_beta1 = FOC_FCF_P.Gain3_Gain * FOC_FCF_B->Product_c0[1];

  /* Gain: '<S82>/DutyCycle_u1' */
  FOC_FCF_B->DutyCycle_u1 = FOC_FCF_P.DutyCycle_u1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[0];

  /* Gain: '<S82>/DutyCycle_u2' */
  FOC_FCF_B->DutyCycle_u2 = FOC_FCF_P.DutyCycle_u2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[0];

  /* Gain: '<S82>/DutyCycle_u3' */
  FOC_FCF_B->DutyCycle_u3 = FOC_FCF_P.DutyCycle_u3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[0];

  /* Gain: '<S82>/DutyCycle_v1' */
  FOC_FCF_B->DutyCycle_v1 = FOC_FCF_P.DutyCycle_v1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[1];

  /* Gain: '<S82>/DutyCycle_v2' */
  FOC_FCF_B->DutyCycle_v2 = FOC_FCF_P.DutyCycle_v2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[1];

  /* Gain: '<S82>/DutyCycle_v3' */
  FOC_FCF_B->DutyCycle_v3 = FOC_FCF_P.DutyCycle_v3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[1];

  /* Gain: '<S82>/DutyCycle_w1' */
  FOC_FCF_B->DutyCycle_w1 = FOC_FCF_P.DutyCycle_w1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[2];

  /* Gain: '<S82>/DutyCycle_w2' */
  FOC_FCF_B->DutyCycle_w2 = FOC_FCF_P.DutyCycle_w2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[2];

  /* Gain: '<S82>/DutyCycle_w3' */
  FOC_FCF_B->DutyCycle_w3 = FOC_FCF_P.DutyCycle_w3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[2];

  /* UnitDelay: '<S1>/FCF_Cnt' */
  FOC_FCF_B->FCF_Cnt = FOC_FCF_DW->FCF_Cnt_DSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Counter_Start'
   */
  FOC_FCF_B->Sum_o = FOC_FCF_P.Counter_Start_Value + FOC_FCF_B->FCF_Cnt;

  /* Update for UnitDelay: '<S68>/Delay Input1'
   *
   * Block description for '<S68>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE = FOC_FCF_B->Compare_d;

  /* Update for Memory: '<S69>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput = FOC_FCF_B->Logic[0];

  /* Update for UnitDelay: '<S67>/Delay Input1'
   *
   * Block description for '<S67>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE_g = FOC_FCF_B->Compare_iz;

  /* Update for Memory: '<S70>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_e = FOC_FCF_B->Logic_c[0];

  /* Update for UnitDelay: '<S52>/Delay Input1'
   *
   * Block description for '<S52>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE_l = FOC_FCF_B->Compare_in;

  /* Update for Memory: '<S54>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_j = FOC_FCF_B->Logic_a[0];

  /* Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
  tmp_0 = FOC_FCF_B->f_2_w_el;
  tmp_0 -= FOC_FCF_P.DiscreteTransferFcn_DenCoef[1] *
    FOC_FCF_DW->DiscreteTransferFcn_states;
  tmp_0 /= FOC_FCF_P.DiscreteTransferFcn_DenCoef[0];
  FOC_FCF_DW->DiscreteTransferFcn_states = tmp_0;

  /* Update for UnitDelay: '<S77>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_B->Add1_c;

  /* Update for UnitDelay: '<S18>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_B->Sum2_e;

  /* Update for UnitDelay: '<S17>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_B->Sum3;

  /* Update for UnitDelay: '<S15>/Unit Delay3' */
  FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_B->Sum6;

  /* Update for UnitDelay: '<S12>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_B->Add1_j;

  /* Update for UnitDelay: '<S47>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_f = FOC_FCF_B->Add1;

  /* Update for UnitDelay: '<S28>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_B->IntegStopSwitch2[0];

  /* Update for UnitDelay: '<S32>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[0] = FOC_FCF_B->IntegStopSwitch2_o[0];

  /* Update for UnitDelay: '<S36>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_h[0] = FOC_FCF_B->IntegStopSwitch2_h[0];

  /* Update for UnitDelay: '<S28>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_B->IntegStopSwitch2[1];

  /* Update for UnitDelay: '<S32>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[1] = FOC_FCF_B->IntegStopSwitch2_o[1];

  /* Update for UnitDelay: '<S36>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_h[1] = FOC_FCF_B->IntegStopSwitch2_h[1];

  /* Update for UnitDelay: '<S19>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_B->Sum2_j;

  /* Update for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
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

  /* End of Update for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S25>/Discrete FIR Filter 20th order' */
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

  /* End of Update for DiscreteFir: '<S25>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S26>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c--;
  if (FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c < 0) {
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c = 18;
  }

  /* Update for UnitDelay: '<S74>/Delay Input1'
   *
   * Block description for '<S74>/Delay Input1':
   *
   *  Store in Global RAM
   */
  /* Update circular buffer */
  FOC_FCF_DW->DelayInput1_DSTATE_e = FOC_FCF_B->Compare_gt;

  /* Update for Memory: '<S75>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_i = FOC_FCF_B->Logic_e[0];

  /* Update for Memory: '<S56>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_n = FOC_FCF_B->Logic_g[0];

  /* Update for Memory: '<S57>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_o = FOC_FCF_B->Logic_i[0];

  /* Update for Memory: '<S58>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_nm = FOC_FCF_B->Logic_b[0];

  /* Update for Memory: '<S59>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_ef = FOC_FCF_B->Logic_p[0];

  /* Update for Memory: '<S60>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_c = FOC_FCF_B->Logic_d[0];

  /* Update for Memory: '<S61>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_d = FOC_FCF_B->Logic_ev[0];

  /* Update for Memory: '<S62>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_os = FOC_FCF_B->Logic_bw[0];

  /* Update for Memory: '<S63>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_f = FOC_FCF_B->Logic_ag[0];

  /* Update for Memory: '<S64>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_b = FOC_FCF_B->Logic_f[0];

  /* Update for UnitDelay: '<S1>/FCF_Cnt' */
  FOC_FCF_DW->FCF_Cnt_DSTATE = FOC_FCF_B->Sum_o;

  /* Update for DiscreteFir: '<S26>/Discrete FIR Filter 20th order' */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */

  /* Outport: '<Root>/I_dq_Act [A]' */
  FOC_FCF_Y->I_dq_ActA[0] = FOC_FCF_B->I_dq1_Act_filt[0];
  FOC_FCF_Y->I_dq_ActA[2] = FOC_FCF_B->DiscreteFIRFilter20thorder[0];
  FOC_FCF_Y->I_dq_ActA[4] = FOC_FCF_B->DiscreteFIRFilter20thorder_l[0];

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Update for DiscreteFir: '<S26>/Discrete FIR Filter 20th order' */
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

  /* Outport: '<Root>/FOC_Error' */
  FOC_FCF_Y->FOC_Error = FOC_FCF_B->FCF_Error;
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
    /* InitializeConditions for UnitDelay: '<S68>/Delay Input1'
     *
     * Block description for '<S68>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE = FOC_FCF_P.DetectRisePositive1_vinit;

    /* InitializeConditions for Memory: '<S69>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput = FOC_FCF_P.SRFlipFlop_initial_condition;

    /* InitializeConditions for UnitDelay: '<S67>/Delay Input1'
     *
     * Block description for '<S67>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE_g = FOC_FCF_P.DetectRisePositive_vinit;

    /* InitializeConditions for Memory: '<S70>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_e = FOC_FCF_P.SRFlipFlop1_initial_condition;

    /* InitializeConditions for UnitDelay: '<S52>/Delay Input1'
     *
     * Block description for '<S52>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE_l = FOC_FCF_P.DetectRisePositive_vinit_g;

    /* InitializeConditions for Memory: '<S54>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_j =
      FOC_FCF_P.SRFlipFlop_initial_condition_d;

    /* InitializeConditions for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' */
    FOC_FCF_DW->DiscreteTransferFcn_states =
      FOC_FCF_P.DiscreteTransferFcn_InitialStat;

    /* InitializeConditions for UnitDelay: '<S77>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_P.UnitDelay_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S18>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_P.FOC_AngleObs_w_InitVal;

    /* InitializeConditions for UnitDelay: '<S17>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_P.UnitDelay_InitialCondition_b;

    /* InitializeConditions for UnitDelay: '<S15>/Unit Delay3' */
    FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_P.UnitDelay3_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S12>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_P.UnitDelay_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S47>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_f = FOC_FCF_P.UnitDelay_InitialCondition_d;

    /* InitializeConditions for UnitDelay: '<S28>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S32>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[0] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S36>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_h[0] =
      FOC_FCF_P.IntegDelay1_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S28>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S32>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[1] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S36>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_h[1] =
      FOC_FCF_P.IntegDelay1_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S19>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_P.UnitDelay1_InitialCondition;

    /* InitializeConditions for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_circ = 0;

    /* InitializeConditions for DiscreteFir: '<S25>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m = 0;

    /* InitializeConditions for DiscreteFir: '<S26>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c = 0;
    for (i = 0; i < 38; i++) {
      /* InitializeConditions for DiscreteFir: '<S24>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_Init;

      /* InitializeConditions for DiscreteFir: '<S25>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_In_k;

      /* InitializeConditions for DiscreteFir: '<S26>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_In_n;
    }

    /* InitializeConditions for UnitDelay: '<S74>/Delay Input1'
     *
     * Block description for '<S74>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE_e = FOC_FCF_P.DetectRisePositive_vinit_f;

    /* InitializeConditions for Memory: '<S75>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_i =
      FOC_FCF_P.SRFlipFlop_initial_condition_k;

    /* InitializeConditions for Memory: '<S56>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_n =
      FOC_FCF_P.OverTemp_Latching_1_initial_con;

    /* InitializeConditions for Memory: '<S57>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_o =
      FOC_FCF_P.OverTemp_Latching_2_initial_con;

    /* InitializeConditions for Memory: '<S58>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_nm =
      FOC_FCF_P.OverTemp_Latching_3_initial_con;

    /* InitializeConditions for Memory: '<S59>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_ef =
      FOC_FCF_P.OverTemp_Latching_4_initial_con;

    /* InitializeConditions for Memory: '<S60>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_c =
      FOC_FCF_P.OverTemp_Latching_5_initial_con;

    /* InitializeConditions for Memory: '<S61>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_d =
      FOC_FCF_P.OverTemp_Latching_6_initial_con;

    /* InitializeConditions for Memory: '<S62>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_os =
      FOC_FCF_P.OverTemp_Latching_7_initial_con;

    /* InitializeConditions for Memory: '<S63>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_f =
      FOC_FCF_P.OverTemp_Latching_8_initial_con;

    /* InitializeConditions for Memory: '<S64>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_b =
      FOC_FCF_P.OverTemp_Latching_9_initial_con;

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
