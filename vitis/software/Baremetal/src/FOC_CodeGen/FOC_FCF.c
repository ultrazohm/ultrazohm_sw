/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF.c
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.79
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Mar  2 11:37:36 2026
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
#include "FOC_FCF_types.h"
#include <string.h>

const bus_FCF_t FOC_FCF_rtZbus_FCF_t = { { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F },                /* DutyCycles */
  0.0F,                                /* U_DC */

  { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },/* I_dq_Act */

  { 0.0F, 0.0F, 0.0F },                /* ModInd */
  0.0F,                                /* w_el */

  { false, false, false },             /* FOC_Enable_PWM */
  false                                /* FCF_Error */
};

/* Model step function */
void FOC_FCF_step(RT_MODEL_FOC_FCF_T *const FOC_FCF_M)
{
  B_FOC_FCF_T *FOC_FCF_B = FOC_FCF_M->blockIO;
  DW_FOC_FCF_T *FOC_FCF_DW = FOC_FCF_M->dwork;
  ExtU_FOC_FCF_T *FOC_FCF_U = (ExtU_FOC_FCF_T *) FOC_FCF_M->inputs;
  ExtY_FOC_FCF_T *FOC_FCF_Y = (ExtY_FOC_FCF_T *) FOC_FCF_M->outputs;
  int32_T cff;
  int32_T i;
  real32_T tmp[6];
  real32_T Gain_a;
  real32_T Gain_l;
  real32_T I_ph;
  real32_T Sum1_lz;
  real32_T TrafoMatrixuvwalphabeta;
  real32_T UnitDelay1_p;
  boolean_T LogicalOperator2_a_tmp;
  boolean_T tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S20>/Sum' incorporates:
   *  Constant: '<S20>/Offset_ADC_bits_Ph1'
   *  Constant: '<S20>/Offset_ADC_bits_Ph2'
   *  Constant: '<S20>/Offset_ADC_bits_Ph3'
   *  Constant: '<S20>/Offset_ADC_bits_Ph4'
   *  Constant: '<S20>/Offset_ADC_bits_Ph5'
   *  Constant: '<S20>/Offset_ADC_bits_Ph6'
   *  Constant: '<S20>/Offset_ADC_bits_Ph7'
   *  Constant: '<S20>/Offset_ADC_bits_Ph8'
   *  Constant: '<S20>/Offset_ADC_bits_Ph9'
   *  Inport: '<Root>/bus_BSW_FCF'
   */
  FOC_FCF_B->Sum[0] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[0] -
    FOC_FCF_P.Offset_ADC_bits_Ph1_Value;
  FOC_FCF_B->Sum[1] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[1] -
    FOC_FCF_P.Offset_ADC_bits_Ph2_Value;
  FOC_FCF_B->Sum[2] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[2] -
    FOC_FCF_P.Offset_ADC_bits_Ph3_Value;
  FOC_FCF_B->Sum[3] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[3] -
    FOC_FCF_P.Offset_ADC_bits_Ph4_Value;
  FOC_FCF_B->Sum[4] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[4] -
    FOC_FCF_P.Offset_ADC_bits_Ph5_Value;
  FOC_FCF_B->Sum[5] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[5] -
    FOC_FCF_P.Offset_ADC_bits_Ph6_Value;
  FOC_FCF_B->Sum[6] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[6] -
    FOC_FCF_P.Offset_ADC_bits_Ph7_Value;
  FOC_FCF_B->Sum[7] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[7] -
    FOC_FCF_P.Offset_ADC_bits_Ph8_Value;
  FOC_FCF_B->Sum[8] = FOC_FCF_U->bus_BSW_FCF.ADC_I_ph[8] -
    FOC_FCF_P.Offset_ADC_bits_Ph9_Value;

  /* Outputs for Enabled SubSystem: '<S20>/Current_Sensor_Calibration' incorporates:
   *  EnablePort: '<S21>/Enable'
   */
  /* Constant: '<S20>/calibrateSensors' */
  if (FOC_FCF_P.FOC_Calibrate_I_ph > 0.0F) {
    /* Saturate: '<S22>/VermeidungDivisionDurchNull' incorporates:
     *  Constant: '<S22>/Tau'
     */
    if (FOC_FCF_P.Tau_Value > FOC_FCF_P.VermeidungDivisionDurchNull_Upp) {
      /* Saturate: '<S22>/VermeidungDivisionDurchNull' */
      FOC_FCF_B->VermeidungDivisionDurchNull =
        FOC_FCF_P.VermeidungDivisionDurchNull_Upp;
    } else if (FOC_FCF_P.Tau_Value < FOC_FCF_P.VermeidungDivisionDurchNull_Low)
    {
      /* Saturate: '<S22>/VermeidungDivisionDurchNull' */
      FOC_FCF_B->VermeidungDivisionDurchNull =
        FOC_FCF_P.VermeidungDivisionDurchNull_Low;
    } else {
      /* Saturate: '<S22>/VermeidungDivisionDurchNull' */
      FOC_FCF_B->VermeidungDivisionDurchNull = FOC_FCF_P.Tau_Value;
    }

    /* End of Saturate: '<S22>/VermeidungDivisionDurchNull' */
    for (i = 0; i < 9; i++) {
      /* UnitDelay: '<S23>/Unit Delay1' */
      UnitDelay1_p = FOC_FCF_DW->UnitDelay1_DSTATE_c[i];
      FOC_FCF_B->UnitDelay1_p[i] = UnitDelay1_p;

      /* Gain: '<S22>/Gain' */
      Gain_a = FOC_FCF_P.Gain_Gain * FOC_FCF_B->Sum[i];
      FOC_FCF_B->Gain_a[i] = Gain_a;

      /* Sum: '<S22>/Add' */
      Gain_a -= UnitDelay1_p;
      FOC_FCF_B->Add_p[i] = Gain_a;

      /* Product: '<S22>/Divide' */
      Gain_a /= FOC_FCF_B->VermeidungDivisionDurchNull;
      FOC_FCF_B->Divide[i] = Gain_a;

      /* Product: '<S23>/Product' incorporates:
       *  Constant: '<S23>/FOC_T_fast'
       */
      Gain_a *= FOC_FCF_P.FOC_T_fast_Value;
      FOC_FCF_B->Product_cdf[i] = Gain_a;

      /* Sum: '<S23>/Sum2' */
      UnitDelay1_p += Gain_a;
      FOC_FCF_B->Sum2_k[i] = UnitDelay1_p;

      /* Update for UnitDelay: '<S23>/Unit Delay1' */
      FOC_FCF_DW->UnitDelay1_DSTATE_c[i] = UnitDelay1_p;
    }
  }

  /* End of Constant: '<S20>/calibrateSensors' */
  /* End of Outputs for SubSystem: '<S20>/Current_Sensor_Calibration' */
  for (i = 0; i < 9; i++) {
    /* Sum: '<S20>/i_uvw_cal' */
    FOC_FCF_B->i_uvw_cal[i] = FOC_FCF_B->Sum[i] - FOC_FCF_B->UnitDelay1_p[i];
  }

  /* Gain: '<S20>/Gain' */
  FOC_FCF_B->Gain = FOC_FCF_P.gain_current1 * FOC_FCF_B->i_uvw_cal[0];

  /* Gain: '<S20>/Gain1' */
  FOC_FCF_B->Gain1 = FOC_FCF_P.gain_current2 * FOC_FCF_B->i_uvw_cal[1];

  /* Gain: '<S20>/Gain2' */
  FOC_FCF_B->Gain2 = FOC_FCF_P.gain_current3 * FOC_FCF_B->i_uvw_cal[2];

  /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_1' incorporates:
   *  Constant: '<S19>/Selektierung Phase'
   */
  switch ((int32_T)FOC_FCF_P.FOC_SELECT_Phase_Assignment_UVW) {
   case 1:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_1' */
    FOC_FCF_B->Select_CurrentSensor_Assignment[0] = FOC_FCF_B->Gain;
    FOC_FCF_B->Select_CurrentSensor_Assignment[1] = FOC_FCF_B->Gain1;
    FOC_FCF_B->Select_CurrentSensor_Assignment[2] = FOC_FCF_B->Gain2;
    break;

   case 2:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_1' */
    FOC_FCF_B->Select_CurrentSensor_Assignment[0] = FOC_FCF_B->Gain;
    FOC_FCF_B->Select_CurrentSensor_Assignment[1] = FOC_FCF_B->Gain2;
    FOC_FCF_B->Select_CurrentSensor_Assignment[2] = FOC_FCF_B->Gain1;
    break;

   case 3:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_1' */
    FOC_FCF_B->Select_CurrentSensor_Assignment[0] = FOC_FCF_B->Gain1;
    FOC_FCF_B->Select_CurrentSensor_Assignment[1] = FOC_FCF_B->Gain;
    FOC_FCF_B->Select_CurrentSensor_Assignment[2] = FOC_FCF_B->Gain2;
    break;

   case 4:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_1' */
    FOC_FCF_B->Select_CurrentSensor_Assignment[0] = FOC_FCF_B->Gain1;
    FOC_FCF_B->Select_CurrentSensor_Assignment[1] = FOC_FCF_B->Gain2;
    FOC_FCF_B->Select_CurrentSensor_Assignment[2] = FOC_FCF_B->Gain;
    break;

   case 5:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_1' */
    FOC_FCF_B->Select_CurrentSensor_Assignment[0] = FOC_FCF_B->Gain2;
    FOC_FCF_B->Select_CurrentSensor_Assignment[1] = FOC_FCF_B->Gain;
    FOC_FCF_B->Select_CurrentSensor_Assignment[2] = FOC_FCF_B->Gain1;
    break;

   default:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_1' */
    FOC_FCF_B->Select_CurrentSensor_Assignment[0] = FOC_FCF_B->Gain2;
    FOC_FCF_B->Select_CurrentSensor_Assignment[1] = FOC_FCF_B->Gain1;
    FOC_FCF_B->Select_CurrentSensor_Assignment[2] = FOC_FCF_B->Gain;
    break;
  }

  /* End of MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_1' */

  /* Gain: '<S20>/Gain3' */
  FOC_FCF_B->Gain3 = FOC_FCF_P.gain_current4 * FOC_FCF_B->i_uvw_cal[3];

  /* Gain: '<S20>/Gain4' */
  FOC_FCF_B->Gain4 = FOC_FCF_P.gain_current5 * FOC_FCF_B->i_uvw_cal[4];

  /* Gain: '<S20>/Gain5' */
  FOC_FCF_B->Gain5 = FOC_FCF_P.gain_current6 * FOC_FCF_B->i_uvw_cal[5];

  /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_2' incorporates:
   *  Constant: '<S19>/Selektierung Phase'
   */
  switch ((int32_T)FOC_FCF_P.FOC_SELECT_Phase_Assignment_UVW) {
   case 1:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_2' */
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[0] = FOC_FCF_B->Gain3;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[1] = FOC_FCF_B->Gain4;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[2] = FOC_FCF_B->Gain5;
    break;

   case 2:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_2' */
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[0] = FOC_FCF_B->Gain3;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[1] = FOC_FCF_B->Gain5;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[2] = FOC_FCF_B->Gain4;
    break;

   case 3:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_2' */
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[0] = FOC_FCF_B->Gain4;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[1] = FOC_FCF_B->Gain3;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[2] = FOC_FCF_B->Gain5;
    break;

   case 4:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_2' */
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[0] = FOC_FCF_B->Gain4;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[1] = FOC_FCF_B->Gain5;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[2] = FOC_FCF_B->Gain3;
    break;

   case 5:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_2' */
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[0] = FOC_FCF_B->Gain5;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[1] = FOC_FCF_B->Gain3;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[2] = FOC_FCF_B->Gain4;
    break;

   default:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_2' */
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[0] = FOC_FCF_B->Gain5;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[1] = FOC_FCF_B->Gain4;
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[2] = FOC_FCF_B->Gain3;
    break;
  }

  /* End of MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_2' */

  /* Gain: '<S20>/Gain6' */
  FOC_FCF_B->Gain6 = FOC_FCF_P.gain_current7 * FOC_FCF_B->i_uvw_cal[6];

  /* Gain: '<S20>/Gain7' */
  FOC_FCF_B->Gain7 = FOC_FCF_P.gain_current8 * FOC_FCF_B->i_uvw_cal[7];

  /* Gain: '<S20>/Gain8' */
  FOC_FCF_B->Gain8 = FOC_FCF_P.gain_current9 * FOC_FCF_B->i_uvw_cal[8];

  /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_3' incorporates:
   *  Constant: '<S19>/Selektierung Phase'
   */
  switch ((int32_T)FOC_FCF_P.FOC_SELECT_Phase_Assignment_UVW) {
   case 1:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_3' */
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[0] = FOC_FCF_B->Gain6;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[1] = FOC_FCF_B->Gain7;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[2] = FOC_FCF_B->Gain8;
    break;

   case 2:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_3' */
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[0] = FOC_FCF_B->Gain6;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[1] = FOC_FCF_B->Gain8;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[2] = FOC_FCF_B->Gain7;
    break;

   case 3:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_3' */
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[0] = FOC_FCF_B->Gain7;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[1] = FOC_FCF_B->Gain6;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[2] = FOC_FCF_B->Gain8;
    break;

   case 4:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_3' */
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[0] = FOC_FCF_B->Gain7;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[1] = FOC_FCF_B->Gain8;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[2] = FOC_FCF_B->Gain6;
    break;

   case 5:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_3' */
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[0] = FOC_FCF_B->Gain8;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[1] = FOC_FCF_B->Gain6;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[2] = FOC_FCF_B->Gain7;
    break;

   default:
    /* MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_3' */
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[0] = FOC_FCF_B->Gain8;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[1] = FOC_FCF_B->Gain7;
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[2] = FOC_FCF_B->Gain6;
    break;
  }

  /* End of MultiPortSwitch: '<S19>/Select_CurrentSensor_Assignment_3' */

  /* Gain: '<S2>/Gain' */
  FOC_FCF_B->I_ph[0] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignment[0];
  FOC_FCF_B->I_ph[3] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[0];
  FOC_FCF_B->I_ph[6] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[0];
  FOC_FCF_B->I_ph[1] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignment[1];
  FOC_FCF_B->I_ph[4] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[1];
  FOC_FCF_B->I_ph[7] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[1];
  FOC_FCF_B->I_ph[2] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignment[2];
  FOC_FCF_B->I_ph[5] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignme_o[2];
  FOC_FCF_B->I_ph[8] = FOC_FCF_P.Gain_Gain_k *
    FOC_FCF_B->Select_CurrentSensor_Assignm_on[2];

  /* MultiPortSwitch: '<S17>/U_DC_switch' incorporates:
   *  Constant: '<S17>/0: P_Udc 1: Udc_measured'
   */
  if (FOC_FCF_P.FOC_SELECT_U_DC_INPUT == 0) {
    /* Bias: '<S17>/bias_udc' */
    FOC_FCF_B->bias_udc = FOC_FCF_U->bus_BSW_FCF.ADC_U_DC +
      FOC_FCF_P.bias_udc_Bias;

    /* Gain: '<S17>/gain_udc' */
    FOC_FCF_B->gain_udc = FOC_FCF_P.gain_udc_Gain * FOC_FCF_B->bias_udc;

    /* MultiPortSwitch: '<S17>/U_DC_switch' */
    FOC_FCF_B->U_DC_fcf = FOC_FCF_B->gain_udc;
  } else {
    /* MultiPortSwitch: '<S17>/U_DC_switch' incorporates:
     *  Constant: '<S17>/Udc1'
     */
    FOC_FCF_B->U_DC_fcf = FOC_FCF_P.FOC_MANUAL_U_DC;
  }

  /* End of MultiPortSwitch: '<S17>/U_DC_switch' */

  /* MultiPortSwitch: '<S1>/ModeSwitch' incorporates:
   *  Constant: '<S1>/FOC_SELECT_Mode_Intern'
   */
  if (FOC_FCF_P.FOC_SELECT_Mode_Intern == 0) {
    /* MultiPortSwitch: '<S1>/ModeSwitch' */
    FOC_FCF_B->FOC_Mode_Request = FOC_FCF_U->bus_SMF.FOC_Mode;
  } else {
    /* MultiPortSwitch: '<S1>/ModeSwitch' incorporates:
     *  Constant: '<S1>/FOC_Mode_Intern'
     */
    FOC_FCF_B->FOC_Mode_Request = FOC_FCF_P.FOC_Mode_Intern;
  }

  /* End of MultiPortSwitch: '<S1>/ModeSwitch' */

  /* RelationalOperator: '<S79>/Compare' incorporates:
   *  Constant: '<S79>/Constant'
   */
  FOC_FCF_B->Compare_e = (FOC_FCF_B->U_DC_fcf <
    FOC_FCF_P.FOC_LIMIT_Undervoltage_U_DC);

  /* Logic: '<S63>/Logical Operator2' */
  FOC_FCF_B->LogicalOperator2 = (FOC_FCF_B->Compare_e &&
    FOC_FCF_U->bus_SMF.FOC_Enable_PWM);

  /* Logic: '<S63>/Logical Operator4' incorporates:
   *  Constant: '<S63>/Reset_UV_Error'
   */
  FOC_FCF_B->LogicalOperator4 = ((FOC_FCF_P.FOC_RESET_UV_Error != 0.0F) ||
    FOC_FCF_U->bus_SMF.global_reset_errors);

  /* RelationalOperator: '<S86>/Compare' incorporates:
   *  Constant: '<S86>/Constant'
   */
  FOC_FCF_B->Compare_d = ((int32_T)FOC_FCF_B->LogicalOperator4 > (int32_T)
    FOC_FCF_P.Constant_Value_eo);

  /* UnitDelay: '<S82>/Delay Input1'
   *
   * Block description for '<S82>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1 = FOC_FCF_DW->DelayInput1_DSTATE;

  /* MultiPortSwitch: '<S63>/Selectphicalc3' incorporates:
   *  Constant: '<S63>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Undervoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S63>/Selectphicalc3' incorporates:
     *  Constant: '<S63>/Constant2'
     */
    FOC_FCF_B->Selectphicalc3 = FOC_FCF_P.Constant2_Value_c;
  } else {
    /* RelationalOperator: '<S82>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator_j = ((int32_T)FOC_FCF_B->Compare_d >
      (int32_T)FOC_FCF_B->Uk1);

    /* MultiPortSwitch: '<S63>/Selectphicalc3' */
    FOC_FCF_B->Selectphicalc3 = FOC_FCF_B->FixPtRelationalOperator_j;
  }

  /* End of MultiPortSwitch: '<S63>/Selectphicalc3' */

  /* Memory: '<S83>/Memory' */
  FOC_FCF_B->Memory = FOC_FCF_DW->Memory_PreviousInput;

  /* CombinatorialLogic: '<S83>/Logic' */
  tmp_0 = FOC_FCF_B->LogicalOperator2;
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc3;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic[0U] = FOC_FCF_P.Logic_table[(uint32_T)i];
  FOC_FCF_B->Logic[1U] = FOC_FCF_P.Logic_table[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S63>/Selectphicalc1' incorporates:
   *  Constant: '<S63>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Undervoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S63>/Selectphicalc1' incorporates:
     *  Constant: '<S63>/Constant3'
     */
    FOC_FCF_B->U_DC_Undervoltage_Error = FOC_FCF_P.Constant3_Value;
  } else {
    /* MultiPortSwitch: '<S63>/Selectphicalc1' */
    FOC_FCF_B->U_DC_Undervoltage_Error = FOC_FCF_B->Logic[0];
  }

  /* End of MultiPortSwitch: '<S63>/Selectphicalc1' */

  /* RelationalOperator: '<S80>/Compare' incorporates:
   *  Constant: '<S80>/Constant'
   */
  FOC_FCF_B->Compare_n = (FOC_FCF_B->U_DC_fcf >
    FOC_FCF_P.FOC_LIMIT_Overvoltage_U_DC);

  /* Logic: '<S63>/Logical Operator3' incorporates:
   *  Constant: '<S63>/Reset_OV_Error'
   */
  FOC_FCF_B->LogicalOperator3 = ((FOC_FCF_P.FOC_RESET_OV_Error != 0.0F) ||
    FOC_FCF_U->bus_SMF.global_reset_errors);

  /* RelationalOperator: '<S85>/Compare' incorporates:
   *  Constant: '<S85>/Constant'
   */
  FOC_FCF_B->Compare_iz = ((int32_T)FOC_FCF_B->LogicalOperator3 > (int32_T)
    FOC_FCF_P.Constant_Value_dc);

  /* UnitDelay: '<S81>/Delay Input1'
   *
   * Block description for '<S81>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1_m = FOC_FCF_DW->DelayInput1_DSTATE_g;

  /* MultiPortSwitch: '<S63>/Selectphicalc4' incorporates:
   *  Constant: '<S63>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overvoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S63>/Selectphicalc4' incorporates:
     *  Constant: '<S63>/Constant4'
     */
    FOC_FCF_B->Selectphicalc4 = FOC_FCF_P.Constant4_Value_f;
  } else {
    /* RelationalOperator: '<S81>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator_m = ((int32_T)FOC_FCF_B->Compare_iz >
      (int32_T)FOC_FCF_B->Uk1_m);

    /* MultiPortSwitch: '<S63>/Selectphicalc4' */
    FOC_FCF_B->Selectphicalc4 = FOC_FCF_B->FixPtRelationalOperator_m;
  }

  /* End of MultiPortSwitch: '<S63>/Selectphicalc4' */

  /* Memory: '<S84>/Memory' */
  FOC_FCF_B->Memory_o = FOC_FCF_DW->Memory_PreviousInput_e;

  /* CombinatorialLogic: '<S84>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_n;
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc4;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_o;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_c[0U] = FOC_FCF_P.Logic_table_l[(uint32_T)i];
  FOC_FCF_B->Logic_c[1U] = FOC_FCF_P.Logic_table_l[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S63>/Selectphicalc2' incorporates:
   *  Constant: '<S63>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overvoltage_U_DC == 0) {
    /* MultiPortSwitch: '<S63>/Selectphicalc2' incorporates:
     *  Constant: '<S63>/Constant1'
     */
    FOC_FCF_B->U_DC_Overvoltage_Error = FOC_FCF_P.Constant1_Value_b;
  } else {
    /* MultiPortSwitch: '<S63>/Selectphicalc2' */
    FOC_FCF_B->U_DC_Overvoltage_Error = FOC_FCF_B->Logic_c[0];
  }

  /* End of MultiPortSwitch: '<S63>/Selectphicalc2' */
  for (i = 0; i < 9; i++) {
    /* Abs: '<S62>/Abs' */
    FOC_FCF_B->Abs[i] = fabsf(FOC_FCF_B->I_ph[i]);
  }

  /* MinMax: '<S62>/MinMax' incorporates:
   *  Abs: '<S62>/Abs'
   */
  UnitDelay1_p = FOC_FCF_B->Abs[0];
  for (i = 0; i < 8; i++) {
    UnitDelay1_p = fmaxf(UnitDelay1_p, FOC_FCF_B->Abs[i + 1]);
  }

  /* MinMax: '<S62>/MinMax' */
  FOC_FCF_B->MinMax = UnitDelay1_p;

  /* RelationalOperator: '<S64>/Compare' incorporates:
   *  Constant: '<S64>/Constant'
   */
  FOC_FCF_B->Compare_j = (FOC_FCF_B->MinMax >
    FOC_FCF_P.FOC_LIMIT_Overcurrent_I_uvw);

  /* Logic: '<S62>/Logical Operator3' incorporates:
   *  Constant: '<S62>/Reset_OC_Error'
   */
  FOC_FCF_B->LogicalOperator3_i = ((FOC_FCF_P.FOC_RESET_OC_Error != 0.0F) ||
    FOC_FCF_U->bus_SMF.global_reset_errors);

  /* RelationalOperator: '<S69>/Compare' incorporates:
   *  Constant: '<S69>/Constant'
   */
  FOC_FCF_B->Compare_in = ((int32_T)FOC_FCF_B->LogicalOperator3_i > (int32_T)
    FOC_FCF_P.Constant_Value_j);

  /* UnitDelay: '<S66>/Delay Input1'
   *
   * Block description for '<S66>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1_g = FOC_FCF_DW->DelayInput1_DSTATE_l;

  /* MultiPortSwitch: '<S62>/Selectphicalc2' incorporates:
   *  Constant: '<S62>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overcurrent_I_uvw == 0) {
    /* MultiPortSwitch: '<S62>/Selectphicalc2' incorporates:
     *  Constant: '<S62>/Constant1'
     */
    FOC_FCF_B->Selectphicalc2_m = FOC_FCF_P.Constant1_Value_d;
  } else {
    /* RelationalOperator: '<S66>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator_h = ((int32_T)FOC_FCF_B->Compare_in >
      (int32_T)FOC_FCF_B->Uk1_g);

    /* MultiPortSwitch: '<S62>/Selectphicalc2' */
    FOC_FCF_B->Selectphicalc2_m = FOC_FCF_B->FixPtRelationalOperator_h;
  }

  /* End of MultiPortSwitch: '<S62>/Selectphicalc2' */

  /* Memory: '<S68>/Memory' */
  FOC_FCF_B->Memory_n = FOC_FCF_DW->Memory_PreviousInput_j;

  /* CombinatorialLogic: '<S68>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_j;
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_n;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_a[0U] = FOC_FCF_P.Logic_table_o[(uint32_T)i];
  FOC_FCF_B->Logic_a[1U] = FOC_FCF_P.Logic_table_o[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S62>/Selectphicalc1' incorporates:
   *  Constant: '<S62>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overcurrent_I_uvw == 0) {
    /* MultiPortSwitch: '<S62>/Selectphicalc1' incorporates:
     *  Constant: '<S62>/Constant2'
     */
    FOC_FCF_B->I_ph_Overcurrent_Error = FOC_FCF_P.Constant2_Value_f;
  } else {
    /* MultiPortSwitch: '<S62>/Selectphicalc1' */
    FOC_FCF_B->I_ph_Overcurrent_Error = FOC_FCF_B->Logic_a[0];
  }

  /* End of MultiPortSwitch: '<S62>/Selectphicalc1' */

  /* Logic: '<S11>/Logical Operator' */
  FOC_FCF_B->OC_OV_UV_ERROR = ((FOC_FCF_B->U_DC_Undervoltage_Error != 0.0F) ||
    (FOC_FCF_B->U_DC_Overvoltage_Error != 0.0F) ||
    FOC_FCF_B->I_ph_Overcurrent_Error);

  /* Logic: '<S1>/Logical Operator2' incorporates:
   *  Logic: '<S8>/Logical Operator3'
   */
  LogicalOperator2_a_tmp = !FOC_FCF_B->OC_OV_UV_ERROR;

  /* Logic: '<S1>/Logical Operator2' */
  FOC_FCF_B->LogicalOperator2_a = LogicalOperator2_a_tmp;

  /* Logic: '<S1>/Logical Operator1' incorporates:
   *  Constant: '<S1>/Enable'
   */
  FOC_FCF_B->LogicalOperator1 = ((FOC_FCF_P.FOC_Enable != 0.0F) &&
    FOC_FCF_U->bus_SMF.FOC_Enable_PWM);

  /* Logic: '<S1>/Logical Operator' */
  FOC_FCF_B->LogicalOperator = (FOC_FCF_B->LogicalOperator2_a &&
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

  /* DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn' */
  UnitDelay1_p = FOC_FCF_P.DiscreteTransferFcn_NumCoef *
    FOC_FCF_DW->DiscreteTransferFcn_states;

  /* DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn' */
  FOC_FCF_B->DiscreteTransferFcn = UnitDelay1_p;

  /* Gain: '<S14>/f_2_w_el' incorporates:
   *  Constant: '<S14>/Uf_w_el'
   */
  FOC_FCF_B->f_2_w_el = FOC_FCF_P.f_2_w_el_Gain * FOC_FCF_P.FOC_Uf_f_el;

  /* Product: '<S91>/Product' incorporates:
   *  Constant: '<S91>/FOC_T_fast'
   */
  FOC_FCF_B->Product = FOC_FCF_B->f_2_w_el * FOC_FCF_P.FOC_T_fast_Value_l;

  /* UnitDelay: '<S91>/Unit Delay' */
  FOC_FCF_B->UnitDelay = FOC_FCF_DW->UnitDelay_DSTATE;

  /* Sum: '<S91>/Add' */
  FOC_FCF_B->Add = FOC_FCF_B->Product + FOC_FCF_B->UnitDelay;

  /* Gain: '<S33>/TrafoMatrix uvw->alphabeta' */
  UnitDelay1_p = FOC_FCF_B->I_ph[0];
  Gain_a = FOC_FCF_B->I_ph[1];
  I_ph = FOC_FCF_B->I_ph[2];
  for (i = 0; i < 2; i++) {
    /* Gain: '<S33>/TrafoMatrix uvw->alphabeta' */
    TrafoMatrixuvwalphabeta = FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i] *
      UnitDelay1_p;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i + 2] *
      Gain_a;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain[i + 4] *
      I_ph;
    FOC_FCF_B->TrafoMatrixuvwalphabeta[i] = TrafoMatrixuvwalphabeta;
  }

  /* RelationalOperator: '<S7>/Compare' incorporates:
   *  Constant: '<S7>/Constant'
   */
  FOC_FCF_B->Compare_l = (FOC_FCF_B->FOC_Mode_Request ==
    FOC_FCF_P.enumState_FOC_IF);

  /* Saturate: '<S4>/ResolverOffsetLimitation' */
  if (FOC_FCF_P.FOC_phi_offset > FOC_FCF_P.ResolverOffsetLimitation_UpperS) {
    /* Saturate: '<S4>/ResolverOffsetLimitation' */
    FOC_FCF_B->ResolverOffsetLimitation =
      FOC_FCF_P.ResolverOffsetLimitation_UpperS;
  } else if (FOC_FCF_P.FOC_phi_offset <
             FOC_FCF_P.ResolverOffsetLimitation_LowerS) {
    /* Saturate: '<S4>/ResolverOffsetLimitation' */
    FOC_FCF_B->ResolverOffsetLimitation =
      FOC_FCF_P.ResolverOffsetLimitation_LowerS;
  } else {
    /* Saturate: '<S4>/ResolverOffsetLimitation' */
    FOC_FCF_B->ResolverOffsetLimitation = FOC_FCF_P.FOC_phi_offset;
  }

  /* End of Saturate: '<S4>/ResolverOffsetLimitation' */

  /* Sum: '<S4>/Sum1' */
  FOC_FCF_B->Sum1 = FOC_FCF_B->ResolverOffsetLimitation +
    FOC_FCF_U->bus_BSW_FCF.phi;

  /* UnitDelay: '<S27>/Unit Delay1' */
  FOC_FCF_B->w_el = FOC_FCF_DW->UnitDelay1_DSTATE;

  /* Gain: '<S24>/DeadTimeCompensation' */
  FOC_FCF_B->DeadTimeCompensation = FOC_FCF_P.FOC_PhiSensorTdead *
    FOC_FCF_B->w_el;

  /* Sum: '<S24>/Sum3' */
  FOC_FCF_B->Sum3 = FOC_FCF_B->Sum1 + FOC_FCF_B->DeadTimeCompensation;

  /* UnitDelay: '<S26>/Unit Delay' */
  FOC_FCF_B->UnitDelay_l = FOC_FCF_DW->UnitDelay_DSTATE_h;

  /* Sum: '<S26>/Sum' */
  FOC_FCF_B->Sum_d = FOC_FCF_B->Sum3 - FOC_FCF_B->UnitDelay_l;

  /* RelationalOperator: '<S26>/Sprung?' incorporates:
   *  Constant: '<S26>/Constant3'
   */
  FOC_FCF_B->Sprung = (FOC_FCF_B->Sum_d < FOC_FCF_P.Constant3_Value_l);

  /* Switch: '<S26>/Switch' */
  if (FOC_FCF_B->Sprung) {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S26>/Constant2'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant2_Value;
  } else {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S26>/Constant4'
     */
    FOC_FCF_B->Switch = FOC_FCF_P.Constant4_Value;
  }

  /* End of Switch: '<S26>/Switch' */

  /* RelationalOperator: '<S26>/Sprung?1' incorporates:
   *  Constant: '<S26>/Constant1'
   */
  FOC_FCF_B->Sprung1 = (FOC_FCF_B->Sum_d > FOC_FCF_P.Constant1_Value_ep);

  /* Switch: '<S26>/Switch1' */
  if (FOC_FCF_B->Sprung1) {
    /* Switch: '<S26>/Switch1' incorporates:
     *  Constant: '<S26>/Constant5'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant5_Value;
  } else {
    /* Switch: '<S26>/Switch1' incorporates:
     *  Constant: '<S26>/Constant6'
     */
    FOC_FCF_B->Switch1 = FOC_FCF_P.Constant6_Value;
  }

  /* End of Switch: '<S26>/Switch1' */

  /* Sum: '<S26>/Sum2' */
  FOC_FCF_B->Sum2 = FOC_FCF_B->Switch + FOC_FCF_B->Switch1;

  /* UnitDelay: '<S24>/Unit Delay3' */
  FOC_FCF_B->UnitDelay3 = FOC_FCF_DW->UnitDelay3_DSTATE;

  /* Sum: '<S24>/Sum7' */
  FOC_FCF_B->phi_el_observer = FOC_FCF_B->UnitDelay3 - FOC_FCF_B->Sum2;

  /* Product: '<S13>/Product' incorporates:
   *  Constant: '<S13>/FOC_T_fast'
   *  Constant: '<S1>/SMF_w_el_Ref_IfStarter'
   */
  FOC_FCF_B->Product_e = FOC_FCF_P.SMF_w_el_Ref_IfStarter_Value *
    FOC_FCF_P.FOC_T_fast_Value_d;

  /* UnitDelay: '<S13>/Unit Delay' */
  FOC_FCF_B->UnitDelay_a = FOC_FCF_DW->UnitDelay_DSTATE_p;

  /* Sum: '<S13>/Add' */
  FOC_FCF_B->Add_m = FOC_FCF_B->Product_e + FOC_FCF_B->UnitDelay_a;

  /* Gain: '<S10>/f_2_w_el' incorporates:
   *  Constant: '<S10>/If_f_el'
   */
  FOC_FCF_B->f_2_w_el_b = FOC_FCF_P.f_2_w_el_Gain_j * FOC_FCF_P.FOC_If_f_el;

  /* Product: '<S61>/Product' incorporates:
   *  Constant: '<S61>/FOC_T_fast'
   */
  FOC_FCF_B->Product_h = FOC_FCF_B->f_2_w_el_b * FOC_FCF_P.FOC_T_fast_Value_f;

  /* UnitDelay: '<S61>/Unit Delay' */
  FOC_FCF_B->UnitDelay_j = FOC_FCF_DW->UnitDelay_DSTATE_f;

  /* Sum: '<S61>/Add' */
  FOC_FCF_B->Add_mp = FOC_FCF_B->Product_h + FOC_FCF_B->UnitDelay_j;

  /* MultiPortSwitch: '<S1>/Use_If_Mode' */
  if (!FOC_FCF_B->Compare_l) {
    /* MultiPortSwitch: '<S1>/Use_If_Starter' incorporates:
     *  Constant: '<S1>/SMF_IfStarter_Active'
     */
    if ((int32_T)FOC_FCF_P.SMF_IfStarter_Active_Value == 0) {
      /* MultiPortSwitch: '<S4>/Selectphicalc2' incorporates:
       *  Constant: '<S4>/Constant3'
       */
      if (FOC_FCF_P.FOC_SELECT_phi == 1) {
        /* MultiPortSwitch: '<S4>/Selectphicalc2' */
        FOC_FCF_B->Selectphicalc2 = FOC_FCF_B->Sum1;
      } else {
        /* MultiPortSwitch: '<S4>/Selectphicalc2' */
        FOC_FCF_B->Selectphicalc2 = FOC_FCF_B->phi_el_observer;
      }

      /* End of MultiPortSwitch: '<S4>/Selectphicalc2' */

      /* Switch: '<S25>/Switch1' */
      if (FOC_FCF_B->Selectphicalc2 > FOC_FCF_P.Switch1_Threshold) {
        /* Sum: '<S25>/Sum2' incorporates:
         *  Constant: '<S25>/Constant'
         */
        FOC_FCF_B->Sum2_l = FOC_FCF_B->Selectphicalc2 -
          FOC_FCF_P.Constant_Value_e;

        /* Switch: '<S25>/Switch1' */
        FOC_FCF_B->Switch1_d = FOC_FCF_B->Sum2_l;
      } else {
        /* Switch: '<S25>/Switch1' */
        FOC_FCF_B->Switch1_d = FOC_FCF_B->Selectphicalc2;
      }

      /* End of Switch: '<S25>/Switch1' */

      /* Switch: '<S25>/Switch2' */
      if (FOC_FCF_B->Switch1_d > FOC_FCF_P.Switch2_Threshold) {
        /* Switch: '<S25>/Switch2' */
        FOC_FCF_B->Switch2_f = FOC_FCF_B->Switch1_d;
      } else {
        /* Sum: '<S25>/Sum3' incorporates:
         *  Constant: '<S25>/Constant1'
         */
        FOC_FCF_B->Sum3_h = FOC_FCF_B->Switch1_d + FOC_FCF_P.Constant1_Value_g;

        /* Switch: '<S25>/Switch2' */
        FOC_FCF_B->Switch2_f = FOC_FCF_B->Sum3_h;
      }

      /* End of Switch: '<S25>/Switch2' */

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

  /* Trigonometry: '<S33>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1 = cosf(FOC_FCF_B->Use_If_Mode[0]);

  /* Product: '<S33>/TrafoProd' */
  FOC_FCF_B->TrafoProd = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction1;

  /* Trigonometry: '<S33>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction = sinf(FOC_FCF_B->Use_If_Mode[0]);

  /* Product: '<S33>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3 = FOC_FCF_B->TrigonometricFunction *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Sum: '<S33>/I_d1_Act' */
  FOC_FCF_B->I_d1_Act = FOC_FCF_B->TrafoProd + FOC_FCF_B->TrafoProd3;

  /* Product: '<S33>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1 = FOC_FCF_B->TrigonometricFunction1 *
    FOC_FCF_B->TrafoMatrixuvwalphabeta[1];

  /* Product: '<S33>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2 = FOC_FCF_B->TrafoMatrixuvwalphabeta[0] *
    FOC_FCF_B->TrigonometricFunction;

  /* Sum: '<S33>/I_q1_Act' */
  FOC_FCF_B->I_q1_Act = FOC_FCF_B->TrafoProd1 - FOC_FCF_B->TrafoProd2;

  /* SignalConversion generated from: '<S33>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0] = FOC_FCF_B->I_d1_Act;
  FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1] = FOC_FCF_B->I_q1_Act;

  /* Sum: '<S30>/IdqErr' incorporates:
   *  Inport: '<Root>/bus_SCF'
   */
  UnitDelay1_p = FOC_FCF_U->bus_SCF.I_dq_Ref[0] -
    FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[0] = UnitDelay1_p;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S37>/KP*e[k]1' incorporates:
   *  Constant: '<S37>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[0] = UnitDelay1_p * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S37>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[0] = FOC_FCF_DW->IntegDelay1_DSTATE[0];

  /* Sum: '<S30>/IdqErr' incorporates:
   *  Inport: '<Root>/bus_SCF'
   */
  UnitDelay1_p = FOC_FCF_U->bus_SCF.I_dq_Ref[1] -
    FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr[1] = UnitDelay1_p;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S37>/KP*e[k]1' incorporates:
   *  Constant: '<S37>/FOC_KP1'
   */
  FOC_FCF_B->KPek1[1] = UnitDelay1_p * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S37>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1[1] = FOC_FCF_DW->IntegDelay1_DSTATE[1];

  /* Product: '<S37>/Product1' incorporates:
   *  Constant: '<S37>/FOC_KI'
   *  Constant: '<S37>/FOC_T_fast'
   */
  FOC_FCF_B->Product1 = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_n;

  /* Logic: '<S6>/Logical Operator1' incorporates:
   *  Constant: '<S6>/FOC_Enable_Sys1'
   */
  FOC_FCF_B->LogicalOperator1_h = ((FOC_FCF_P.FOC_Enable_Sys1 != 0.0F) &&
    FOC_FCF_B->LogicalOperator1);

  /* Switch: '<S37>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator1_h) {
    /* Product: '<S37>/Product2' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1[0] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[0] = UnitDelay1_p;

    /* Sum: '<S37>/IntSum1' */
    UnitDelay1_p += FOC_FCF_B->KPek1[0];
    FOC_FCF_B->IntSum1_p[0] = UnitDelay1_p;

    /* Switch: '<S37>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1[0] = UnitDelay1_p;

    /* Product: '<S37>/Product2' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1[1] * FOC_FCF_B->Product1;
    FOC_FCF_B->Product2_j[1] = UnitDelay1_p;

    /* Sum: '<S37>/IntSum1' */
    UnitDelay1_p += FOC_FCF_B->KPek1[1];
    FOC_FCF_B->IntSum1_p[1] = UnitDelay1_p;

    /* Switch: '<S37>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1[1] = UnitDelay1_p;
  } else {
    /* Switch: '<S37>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S37>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1[0] = FOC_FCF_P.Zero_Value;
    FOC_FCF_B->IntegEnaSwitch1[1] = FOC_FCF_P.Zero_Value;
  }

  /* End of Switch: '<S37>/IntegEnaSwitch1' */

  /* Gain: '<S34>/TrafoMatrix uvw->alphabeta' */
  UnitDelay1_p = FOC_FCF_B->I_ph[3];
  Gain_a = FOC_FCF_B->I_ph[4];
  I_ph = FOC_FCF_B->I_ph[5];
  for (i = 0; i < 2; i++) {
    /* Gain: '<S34>/TrafoMatrix uvw->alphabeta' */
    TrafoMatrixuvwalphabeta = FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i] *
      UnitDelay1_p;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i + 2] *
      Gain_a;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_p[i + 4] *
      I_ph;
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[i] = TrafoMatrixuvwalphabeta;
  }

  /* Sum: '<S6>/Sum1' incorporates:
   *  Constant: '<S6>/FOC_9ph_AngleShift'
   */
  FOC_FCF_B->Sum1_d = FOC_FCF_B->Use_If_Mode[0] + FOC_FCF_P.FOC_9ph_AngleShift;

  /* Trigonometry: '<S34>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_b = cosf(FOC_FCF_B->Sum1_d);

  /* Product: '<S34>/TrafoProd' */
  FOC_FCF_B->TrafoProd_a = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction1_b;

  /* Trigonometry: '<S34>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_l = sinf(FOC_FCF_B->Sum1_d);

  /* Product: '<S34>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3_i = FOC_FCF_B->TrigonometricFunction_l *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Sum: '<S34>/TrafoSum' */
  FOC_FCF_B->TrafoSum = FOC_FCF_B->TrafoProd_a + FOC_FCF_B->TrafoProd3_i;

  /* Product: '<S34>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1_b = FOC_FCF_B->TrigonometricFunction1_b *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_h[1];

  /* Product: '<S34>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2_b = FOC_FCF_B->TrafoMatrixuvwalphabeta_h[0] *
    FOC_FCF_B->TrigonometricFunction_l;

  /* Sum: '<S34>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1 = FOC_FCF_B->TrafoProd1_b - FOC_FCF_B->TrafoProd2_b;

  /* SignalConversion generated from: '<S34>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0] = FOC_FCF_B->TrafoSum;
  FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1] = FOC_FCF_B->TrafoSum1;

  /* Sum: '<S31>/IdqErr' incorporates:
   *  Inport: '<Root>/bus_SCF'
   */
  UnitDelay1_p = FOC_FCF_U->bus_SCF.I_dq_Ref[0] -
    FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[0] = UnitDelay1_p;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S41>/KP*e[k]1' incorporates:
   *  Constant: '<S41>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[0] = UnitDelay1_p * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S41>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[0] = FOC_FCF_DW->IntegDelay1_DSTATE_p[0];

  /* Sum: '<S31>/IdqErr' incorporates:
   *  Inport: '<Root>/bus_SCF'
   */
  UnitDelay1_p = FOC_FCF_U->bus_SCF.I_dq_Ref[1] -
    FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_l[1] = UnitDelay1_p;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S41>/KP*e[k]1' incorporates:
   *  Constant: '<S41>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_l[1] = UnitDelay1_p * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S41>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_o[1] = FOC_FCF_DW->IntegDelay1_DSTATE_p[1];

  /* Product: '<S41>/Product1' incorporates:
   *  Constant: '<S41>/FOC_KI'
   *  Constant: '<S41>/FOC_T_fast'
   */
  FOC_FCF_B->Product1_k = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_e;

  /* Logic: '<S6>/Logical Operator2' incorporates:
   *  Constant: '<S6>/FOC_Enable_Sys2'
   */
  FOC_FCF_B->LogicalOperator2_n = ((FOC_FCF_P.FOC_Enable_Sys2 != 0.0F) &&
    FOC_FCF_B->LogicalOperator1);

  /* Switch: '<S41>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator2_n) {
    /* Product: '<S41>/Product2' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1_o[0] * FOC_FCF_B->Product1_k;
    FOC_FCF_B->Product2_b[0] = UnitDelay1_p;

    /* Sum: '<S41>/IntSum1' */
    UnitDelay1_p += FOC_FCF_B->KPek1_l[0];
    FOC_FCF_B->IntSum1_l[0] = UnitDelay1_p;

    /* Switch: '<S41>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_n[0] = UnitDelay1_p;

    /* Product: '<S41>/Product2' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1_o[1] * FOC_FCF_B->Product1_k;
    FOC_FCF_B->Product2_b[1] = UnitDelay1_p;

    /* Sum: '<S41>/IntSum1' */
    UnitDelay1_p += FOC_FCF_B->KPek1_l[1];
    FOC_FCF_B->IntSum1_l[1] = UnitDelay1_p;

    /* Switch: '<S41>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_n[1] = UnitDelay1_p;
  } else {
    /* Switch: '<S41>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S41>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1_n[0] = FOC_FCF_P.Zero_Value_o;
    FOC_FCF_B->IntegEnaSwitch1_n[1] = FOC_FCF_P.Zero_Value_o;
  }

  /* End of Switch: '<S41>/IntegEnaSwitch1' */

  /* Gain: '<S35>/TrafoMatrix uvw->alphabeta' */
  UnitDelay1_p = FOC_FCF_B->I_ph[6];
  Gain_a = FOC_FCF_B->I_ph[7];
  I_ph = FOC_FCF_B->I_ph[8];
  for (i = 0; i < 2; i++) {
    /* Gain: '<S35>/TrafoMatrix uvw->alphabeta' */
    TrafoMatrixuvwalphabeta = FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_j[i] *
      UnitDelay1_p;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_j[i + 2] *
      Gain_a;
    TrafoMatrixuvwalphabeta += FOC_FCF_P.TrafoMatrixuvwalphabeta_Gain_j[i + 4] *
      I_ph;
    FOC_FCF_B->TrafoMatrixuvwalphabeta_m[i] = TrafoMatrixuvwalphabeta;
  }

  /* Sum: '<S6>/Sum2' incorporates:
   *  Constant: '<S6>/FOC_9ph_AngleShift'
   */
  FOC_FCF_B->Sum2_m = FOC_FCF_B->Sum1_d + FOC_FCF_P.FOC_9ph_AngleShift;

  /* Trigonometry: '<S35>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_k = cosf(FOC_FCF_B->Sum2_m);

  /* Product: '<S35>/TrafoProd' */
  FOC_FCF_B->TrafoProd_n = FOC_FCF_B->TrafoMatrixuvwalphabeta_m[0] *
    FOC_FCF_B->TrigonometricFunction1_k;

  /* Trigonometry: '<S35>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_k = sinf(FOC_FCF_B->Sum2_m);

  /* Product: '<S35>/TrafoProd3' */
  FOC_FCF_B->TrafoProd3_o = FOC_FCF_B->TrigonometricFunction_k *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_m[1];

  /* Sum: '<S35>/TrafoSum' */
  FOC_FCF_B->TrafoSum_n = FOC_FCF_B->TrafoProd_n + FOC_FCF_B->TrafoProd3_o;

  /* Product: '<S35>/TrafoProd1' */
  FOC_FCF_B->TrafoProd1_e = FOC_FCF_B->TrigonometricFunction1_k *
    FOC_FCF_B->TrafoMatrixuvwalphabeta_m[1];

  /* Product: '<S35>/TrafoProd2' */
  FOC_FCF_B->TrafoProd2_h = FOC_FCF_B->TrafoMatrixuvwalphabeta_m[0] *
    FOC_FCF_B->TrigonometricFunction_k;

  /* Sum: '<S35>/TrafoSum1' */
  FOC_FCF_B->TrafoSum1_p = FOC_FCF_B->TrafoProd1_e - FOC_FCF_B->TrafoProd2_h;

  /* SignalConversion generated from: '<S35>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0] = FOC_FCF_B->TrafoSum_n;
  FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1] = FOC_FCF_B->TrafoSum1_p;

  /* Sum: '<S32>/IdqErr' incorporates:
   *  Inport: '<Root>/bus_SCF'
   */
  UnitDelay1_p = FOC_FCF_U->bus_SCF.I_dq_Ref[0] -
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_e[0] = UnitDelay1_p;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S45>/KP*e[k]1' incorporates:
   *  Constant: '<S45>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_h[0] = UnitDelay1_p * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S45>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_d[0] = FOC_FCF_DW->IntegDelay1_DSTATE_h[0];

  /* Sum: '<S32>/IdqErr' incorporates:
   *  Inport: '<Root>/bus_SCF'
   */
  UnitDelay1_p = FOC_FCF_U->bus_SCF.I_dq_Ref[1] -
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1];

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->IdqErr_e[1] = UnitDelay1_p;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S45>/KP*e[k]1' incorporates:
   *  Constant: '<S45>/FOC_KP1'
   */
  FOC_FCF_B->KPek1_h[1] = UnitDelay1_p * FOC_FCF_P.FOC_KP;

  /* UnitDelay: '<S45>/IntegDelay1' */
  FOC_FCF_B->IntegDelay1_d[1] = FOC_FCF_DW->IntegDelay1_DSTATE_h[1];

  /* Product: '<S45>/Product1' incorporates:
   *  Constant: '<S45>/FOC_KI'
   *  Constant: '<S45>/FOC_T_fast'
   */
  FOC_FCF_B->Product1_b = FOC_FCF_P.FOC_KI * FOC_FCF_P.FOC_T_fast_Value_er;

  /* Logic: '<S6>/Logical Operator3' incorporates:
   *  Constant: '<S6>/FOC_Enable_Sys3'
   */
  FOC_FCF_B->LogicalOperator3_e = ((FOC_FCF_P.FOC_Enable_Sys3 != 0.0F) &&
    FOC_FCF_B->LogicalOperator1);

  /* Switch: '<S45>/IntegEnaSwitch1' */
  if (FOC_FCF_B->LogicalOperator3_e) {
    /* Product: '<S45>/Product2' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1_d[0] * FOC_FCF_B->Product1_b;
    FOC_FCF_B->Product2_e[0] = UnitDelay1_p;

    /* Sum: '<S45>/IntSum1' */
    UnitDelay1_p += FOC_FCF_B->KPek1_h[0];
    FOC_FCF_B->IntSum1[0] = UnitDelay1_p;

    /* Switch: '<S45>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_h[0] = UnitDelay1_p;

    /* Product: '<S45>/Product2' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1_d[1] * FOC_FCF_B->Product1_b;
    FOC_FCF_B->Product2_e[1] = UnitDelay1_p;

    /* Sum: '<S45>/IntSum1' */
    UnitDelay1_p += FOC_FCF_B->KPek1_h[1];
    FOC_FCF_B->IntSum1[1] = UnitDelay1_p;

    /* Switch: '<S45>/IntegEnaSwitch1' */
    FOC_FCF_B->IntegEnaSwitch1_h[1] = UnitDelay1_p;
  } else {
    /* Switch: '<S45>/IntegEnaSwitch1' incorporates:
     *  Constant: '<S45>/Zero'
     */
    FOC_FCF_B->IntegEnaSwitch1_h[0] = FOC_FCF_P.Zero_Value_n;
    FOC_FCF_B->IntegEnaSwitch1_h[1] = FOC_FCF_P.Zero_Value_n;
  }

  /* End of Switch: '<S45>/IntegEnaSwitch1' */

  /* Product: '<S5>/Product' incorporates:
   *  Constant: '<S5>/FOC_T_fast'
   *  Constant: '<S5>/FOC_output_trafo_delay'
   */
  FOC_FCF_B->Product_c = FOC_FCF_P.FOC_output_trafo_delay *
    FOC_FCF_B->Use_If_Mode[1] * FOC_FCF_P.FOC_T_fast_Value_m;

  /* Sum: '<S5>/Sum' */
  FOC_FCF_B->Sum_k = FOC_FCF_B->Use_If_Mode[0] + FOC_FCF_B->Product_c;

  /* Switch: '<S29>/Switch1' */
  if (FOC_FCF_B->Sum_k > FOC_FCF_P.Switch1_Threshold_a) {
    /* Sum: '<S29>/Sum2' incorporates:
     *  Constant: '<S29>/Constant'
     */
    FOC_FCF_B->Sum2_ez = FOC_FCF_B->Sum_k - FOC_FCF_P.Constant_Value;

    /* Switch: '<S29>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum2_ez;
  } else {
    /* Switch: '<S29>/Switch1' */
    FOC_FCF_B->Switch1_k = FOC_FCF_B->Sum_k;
  }

  /* End of Switch: '<S29>/Switch1' */

  /* Switch: '<S29>/Switch2' */
  if (FOC_FCF_B->Switch1_k > FOC_FCF_P.Switch2_Threshold_o) {
    /* Switch: '<S29>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Switch1_k;
  } else {
    /* Sum: '<S29>/Sum3' incorporates:
     *  Constant: '<S29>/Constant1'
     */
    FOC_FCF_B->Sum3_d = FOC_FCF_B->Switch1_k + FOC_FCF_P.Constant1_Value;

    /* Switch: '<S29>/Switch2' */
    FOC_FCF_B->Switch2 = FOC_FCF_B->Sum3_d;
  }

  /* End of Switch: '<S29>/Switch2' */

  /* Sum: '<S5>/Sum2' incorporates:
   *  Constant: '<S5>/FOC_9ph_AngleShift'
   */
  FOC_FCF_B->Sum2_p = FOC_FCF_B->Switch2 + FOC_FCF_P.FOC_9ph_AngleShift;

  /* Sum: '<S5>/Sum1' incorporates:
   *  Constant: '<S5>/FOC_9ph_AngleShift'
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
    /* Gain: '<S92>/Gain' */
    FOC_FCF_B->Gain_fw = FOC_FCF_P.FOC_Uf_m * FOC_FCF_B->DiscreteTransferFcn;

    /* Signum: '<S92>/Sign' */
    UnitDelay1_p = FOC_FCF_B->Gain_fw;
    if (rtIsNaNF(UnitDelay1_p)) {
      /* Signum: '<S92>/Sign' */
      FOC_FCF_B->Sign_p = (rtNaNF);
    } else if (UnitDelay1_p < 0.0F) {
      /* Signum: '<S92>/Sign' */
      FOC_FCF_B->Sign_p = -1.0F;
    } else {
      /* Signum: '<S92>/Sign' */
      FOC_FCF_B->Sign_p = (real32_T)(UnitDelay1_p > 0.0F);
    }

    /* End of Signum: '<S92>/Sign' */

    /* Abs: '<S92>/Abs' */
    FOC_FCF_B->Abs_d3 = fabsf(FOC_FCF_B->Gain_fw);

    /* Saturate: '<S92>/Saturation1' */
    if (FOC_FCF_B->Abs_d3 > FOC_FCF_P.FOC_Uf_U_max) {
      /* Saturate: '<S92>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_max;
    } else if (FOC_FCF_B->Abs_d3 < FOC_FCF_P.FOC_Uf_U_min) {
      /* Saturate: '<S92>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_P.FOC_Uf_U_min;
    } else {
      /* Saturate: '<S92>/Saturation1' */
      FOC_FCF_B->Saturation1 = FOC_FCF_B->Abs_d3;
    }

    /* End of Saturate: '<S92>/Saturation1' */

    /* Product: '<S92>/Product' */
    FOC_FCF_B->Product_j = FOC_FCF_B->Saturation1 * FOC_FCF_B->Sign_p;

    /* Sum: '<S14>/Sum1' incorporates:
     *  Constant: '<S14>/FOC_9ph_AngleShift'
     */
    FOC_FCF_B->Sum1_n = FOC_FCF_B->Add + FOC_FCF_P.FOC_9ph_AngleShift;

    /* Sum: '<S14>/Sum2' incorporates:
     *  Constant: '<S14>/FOC_9ph_AngleShift'
     */
    FOC_FCF_B->Sum2_d = FOC_FCF_B->Sum1_n + FOC_FCF_P.FOC_9ph_AngleShift;

    /* MultiPortSwitch: '<S1>/SelectControlMode' incorporates:
     *  Constant: '<S14>/Uf_Ud'
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

  /* Trigonometry: '<S101>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_n = sinf(FOC_FCF_B->SelectControlMode[6]);

  /* Trigonometry: '<S101>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_j = cosf(FOC_FCF_B->SelectControlMode[6]);

  /* Gain: '<S101>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[0] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S101>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_f[0] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[0] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S101>/Sum1' incorporates:
   *  Gain: '<S101>/Gain'
   *  Gain: '<S101>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S101>/Product' incorporates:
   *  Sum: '<S101>/Sum1'
   */
  I_ph = Sum1_lz;

  /* Gain: '<S101>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[1] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S101>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_f[1] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[1] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S101>/Sum1' incorporates:
   *  Gain: '<S101>/Gain'
   *  Gain: '<S101>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S101>/Product' incorporates:
   *  Sum: '<S101>/Sum1'
   */
  UnitDelay1_p = Sum1_lz;

  /* Gain: '<S101>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[2] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S101>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_f[2] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[2] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S101>/Sum1' incorporates:
   *  Gain: '<S101>/Gain'
   *  Gain: '<S101>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S101>/Product' incorporates:
   *  Sum: '<S101>/Sum1'
   */
  Gain_a = Sum1_lz;

  /* Gain: '<S101>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_h[3] *
    FOC_FCF_B->TrigonometricFunction_n;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S101>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_f[3] * FOC_FCF_B->TrigonometricFunction1_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_l[3] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S101>/Sum1' incorporates:
   *  Gain: '<S101>/Gain'
   *  Gain: '<S101>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_g[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S101>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[0];
  Gain_l = FOC_FCF_B->SelectControlMode[1];
  I_ph *= TrafoMatrixuvwalphabeta;
  I_ph += Gain_a * Gain_l;

  /* Product: '<S101>/Product' */
  FOC_FCF_B->Product_c0[0] = I_ph;

  /* Product: '<S101>/Product' */
  I_ph = UnitDelay1_p * TrafoMatrixuvwalphabeta;
  I_ph += Sum1_lz * Gain_l;

  /* Product: '<S101>/Product' */
  FOC_FCF_B->Product_c0[1] = I_ph;

  /* Product: '<S98>/Product' incorporates:
   *  Constant: '<S98>/Constant'
   */
  for (i = 0; i < 6; i++) {
    tmp[i] = FOC_FCF_P.Constant_Value_d[i];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_c0[0];
  Gain_l = FOC_FCF_B->Product_c0[1];
  for (i = 0; i < 3; i++) {
    I_ph = tmp[i] * TrafoMatrixuvwalphabeta;
    I_ph += tmp[i + 3] * Gain_l;

    /* Product: '<S98>/Product' */
    FOC_FCF_B->U_uvw1[i] = I_ph;
  }

  /* End of Product: '<S98>/Product' */

  /* Trigonometry: '<S102>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_j = sinf(FOC_FCF_B->SelectControlMode[7]);

  /* Trigonometry: '<S102>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_h = cosf(FOC_FCF_B->SelectControlMode[7]);

  /* Gain: '<S102>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[0] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S102>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_l[0] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[0] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S102>/Sum1' incorporates:
   *  Gain: '<S102>/Gain'
   *  Gain: '<S102>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S102>/Product' incorporates:
   *  Sum: '<S102>/Sum1'
   */
  I_ph = Sum1_lz;

  /* Gain: '<S102>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[1] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S102>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_l[1] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[1] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S102>/Sum1' incorporates:
   *  Gain: '<S102>/Gain'
   *  Gain: '<S102>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S102>/Product' incorporates:
   *  Sum: '<S102>/Sum1'
   */
  UnitDelay1_p = Sum1_lz;

  /* Gain: '<S102>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[2] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S102>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_l[2] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[2] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S102>/Sum1' incorporates:
   *  Gain: '<S102>/Gain'
   *  Gain: '<S102>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S102>/Product' incorporates:
   *  Sum: '<S102>/Sum1'
   */
  Gain_a = Sum1_lz;

  /* Gain: '<S102>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_ck[3] *
    FOC_FCF_B->TrigonometricFunction_j;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_i[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S102>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_l[3] * FOC_FCF_B->TrigonometricFunction1_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_f[3] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S102>/Sum1' incorporates:
   *  Gain: '<S102>/Gain'
   *  Gain: '<S102>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_f[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S102>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[2];
  Gain_l = FOC_FCF_B->SelectControlMode[3];
  I_ph *= TrafoMatrixuvwalphabeta;
  I_ph += Gain_a * Gain_l;

  /* Product: '<S102>/Product' */
  FOC_FCF_B->Product_f[0] = I_ph;

  /* Product: '<S102>/Product' */
  I_ph = UnitDelay1_p * TrafoMatrixuvwalphabeta;
  I_ph += Sum1_lz * Gain_l;

  /* Product: '<S102>/Product' */
  FOC_FCF_B->Product_f[1] = I_ph;

  /* Product: '<S99>/Product' incorporates:
   *  Constant: '<S99>/Constant'
   */
  for (i = 0; i < 6; i++) {
    tmp[i] = FOC_FCF_P.Constant_Value_g[i];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_f[0];
  Gain_l = FOC_FCF_B->Product_f[1];
  for (i = 0; i < 3; i++) {
    I_ph = tmp[i] * TrafoMatrixuvwalphabeta;
    I_ph += tmp[i + 3] * Gain_l;

    /* Product: '<S99>/Product' */
    FOC_FCF_B->Product_f3[i] = I_ph;
  }

  /* End of Product: '<S99>/Product' */

  /* Trigonometry: '<S103>/Trigonometric Function' */
  FOC_FCF_B->TrigonometricFunction_h = sinf(FOC_FCF_B->SelectControlMode[8]);

  /* Trigonometry: '<S103>/Trigonometric Function1' */
  FOC_FCF_B->TrigonometricFunction1_hh = cosf(FOC_FCF_B->SelectControlMode[8]);

  /* Gain: '<S103>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[0] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n4[0] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S103>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_j[0] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_ld[0] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S103>/Sum1' incorporates:
   *  Gain: '<S103>/Gain'
   *  Gain: '<S103>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[0] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S103>/Product' incorporates:
   *  Sum: '<S103>/Sum1'
   */
  I_ph = Sum1_lz;

  /* Gain: '<S103>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[1] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n4[1] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S103>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_j[1] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_ld[1] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S103>/Sum1' incorporates:
   *  Gain: '<S103>/Gain'
   *  Gain: '<S103>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[1] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S103>/Product' incorporates:
   *  Sum: '<S103>/Sum1'
   */
  UnitDelay1_p = Sum1_lz;

  /* Gain: '<S103>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[2] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n4[2] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S103>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_j[2] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_ld[2] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S103>/Sum1' incorporates:
   *  Gain: '<S103>/Gain'
   *  Gain: '<S103>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[2] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S103>/Product' incorporates:
   *  Sum: '<S103>/Sum1'
   */
  Gain_a = Sum1_lz;

  /* Gain: '<S103>/Gain1' */
  TrafoMatrixuvwalphabeta = FOC_FCF_P.Gain1_Gain_k[3] *
    FOC_FCF_B->TrigonometricFunction_h;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain1_n4[3] = TrafoMatrixuvwalphabeta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Gain: '<S103>/Gain' */
  Gain_l = FOC_FCF_P.Gain_Gain_j[3] * FOC_FCF_B->TrigonometricFunction1_hh;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Gain_ld[3] = Gain_l;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Sum: '<S103>/Sum1' incorporates:
   *  Gain: '<S103>/Gain'
   *  Gain: '<S103>/Gain1'
   */
  Sum1_lz = TrafoMatrixuvwalphabeta + Gain_l;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
  FOC_FCF_B->Sum1_lz[3] = Sum1_lz;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_FCF' */
  /* Product: '<S103>/Product' */
  TrafoMatrixuvwalphabeta = FOC_FCF_B->SelectControlMode[4];
  Gain_l = FOC_FCF_B->SelectControlMode[5];
  I_ph *= TrafoMatrixuvwalphabeta;
  I_ph += Gain_a * Gain_l;

  /* Product: '<S103>/Product' */
  FOC_FCF_B->Product_i[0] = I_ph;

  /* Product: '<S103>/Product' */
  I_ph = UnitDelay1_p * TrafoMatrixuvwalphabeta;
  I_ph += Sum1_lz * Gain_l;

  /* Product: '<S103>/Product' */
  FOC_FCF_B->Product_i[1] = I_ph;

  /* Product: '<S100>/Product' incorporates:
   *  Constant: '<S100>/Constant'
   */
  for (i = 0; i < 6; i++) {
    tmp[i] = FOC_FCF_P.Constant_Value_o[i];
  }

  TrafoMatrixuvwalphabeta = FOC_FCF_B->Product_i[0];
  Gain_l = FOC_FCF_B->Product_i[1];

  /* Outputs for Atomic SubSystem: '<S15>/NormalizedVoltage' */
  /* Gain: '<S95>/U_DC//2' */
  FOC_FCF_B->U_DC2 = FOC_FCF_P.U_DC2_Gain_p * FOC_FCF_B->U_DC_fcf;

  /* MinMax: '<S95>/AvoidDivBy0' incorporates:
   *  Constant: '<S95>/Constant2'
   */
  UnitDelay1_p = fmaxf(FOC_FCF_P.Constant2_Value_g, FOC_FCF_B->U_DC2);

  /* MinMax: '<S95>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0 = UnitDelay1_p;
  for (i = 0; i < 3; i++) {
    /* Product: '<S100>/Product' */
    UnitDelay1_p = tmp[i] * TrafoMatrixuvwalphabeta;
    UnitDelay1_p += tmp[i + 3] * Gain_l;

    /* Product: '<S100>/Product' */
    FOC_FCF_B->Product_fb[i] = UnitDelay1_p;

    /* Product: '<S95>/DutyCycle_normalized' */
    FOC_FCF_B->DutyCycle_normed[i] = FOC_FCF_B->U_uvw1[i] /
      FOC_FCF_B->AvoidDivBy0;
    FOC_FCF_B->DutyCycle_normed[i + 3] = FOC_FCF_B->Product_f3[i] /
      FOC_FCF_B->AvoidDivBy0;
    FOC_FCF_B->DutyCycle_normed[i + 6] = UnitDelay1_p / FOC_FCF_B->AvoidDivBy0;
  }

  /* End of Outputs for SubSystem: '<S15>/NormalizedVoltage' */

  /* Outputs for Atomic SubSystem: '<S15>/Super_Sinus_Modulation' */
  /* MinMax: '<S97>/MinMax2' */
  UnitDelay1_p = FOC_FCF_B->DutyCycle_normed[0];
  UnitDelay1_p = fminf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[1]);
  UnitDelay1_p = fminf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S97>/MinMax2' */
  FOC_FCF_B->MinMax2 = UnitDelay1_p;

  /* MinMax: '<S97>/MinMax3' */
  UnitDelay1_p = FOC_FCF_B->DutyCycle_normed[0];
  UnitDelay1_p = fmaxf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[1]);
  UnitDelay1_p = fmaxf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[2]);

  /* MinMax: '<S97>/MinMax3' */
  FOC_FCF_B->MinMax3 = UnitDelay1_p;

  /* Sum: '<S97>/Sum1' */
  FOC_FCF_B->Sum1_o = FOC_FCF_B->MinMax2 + FOC_FCF_B->MinMax3;

  /* Gain: '<S97>/Factor' */
  FOC_FCF_B->Factor = FOC_FCF_P.Factor_Gain * FOC_FCF_B->Sum1_o;

  /* Sum: '<S97>/DutyCycle_SuperSinus_1' */
  FOC_FCF_B->DutyCycle_SuperSinus_1[0] = FOC_FCF_B->DutyCycle_normed[0] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[1] = FOC_FCF_B->DutyCycle_normed[1] -
    FOC_FCF_B->Factor;
  FOC_FCF_B->DutyCycle_SuperSinus_1[2] = FOC_FCF_B->DutyCycle_normed[2] -
    FOC_FCF_B->Factor;

  /* MinMax: '<S97>/MinMax1' */
  UnitDelay1_p = FOC_FCF_B->DutyCycle_normed[3];
  UnitDelay1_p = fminf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[4]);
  UnitDelay1_p = fminf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S97>/MinMax1' */
  FOC_FCF_B->MinMax1 = UnitDelay1_p;

  /* MinMax: '<S97>/MinMax4' */
  UnitDelay1_p = FOC_FCF_B->DutyCycle_normed[3];
  UnitDelay1_p = fmaxf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[4]);
  UnitDelay1_p = fmaxf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[5]);

  /* MinMax: '<S97>/MinMax4' */
  FOC_FCF_B->MinMax4 = UnitDelay1_p;

  /* Sum: '<S97>/Sum2' */
  FOC_FCF_B->Sum2_i = FOC_FCF_B->MinMax1 + FOC_FCF_B->MinMax4;

  /* Gain: '<S97>/Factor1' */
  FOC_FCF_B->Factor1 = FOC_FCF_P.Factor1_Gain * FOC_FCF_B->Sum2_i;

  /* Sum: '<S97>/DutyCycle_SuperSinus_2' */
  FOC_FCF_B->DutyCycle_SuperSinus_2[0] = FOC_FCF_B->DutyCycle_normed[3] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[1] = FOC_FCF_B->DutyCycle_normed[4] -
    FOC_FCF_B->Factor1;
  FOC_FCF_B->DutyCycle_SuperSinus_2[2] = FOC_FCF_B->DutyCycle_normed[5] -
    FOC_FCF_B->Factor1;

  /* MinMax: '<S97>/MinMax5' */
  UnitDelay1_p = FOC_FCF_B->DutyCycle_normed[6];
  UnitDelay1_p = fminf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[7]);
  UnitDelay1_p = fminf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[8]);

  /* MinMax: '<S97>/MinMax5' */
  FOC_FCF_B->MinMax5 = UnitDelay1_p;

  /* MinMax: '<S97>/MinMax6' */
  UnitDelay1_p = FOC_FCF_B->DutyCycle_normed[6];
  UnitDelay1_p = fmaxf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[7]);
  UnitDelay1_p = fmaxf(UnitDelay1_p, FOC_FCF_B->DutyCycle_normed[8]);

  /* MinMax: '<S97>/MinMax6' */
  FOC_FCF_B->MinMax6 = UnitDelay1_p;

  /* Sum: '<S97>/Sum3' */
  FOC_FCF_B->Sum3_k = FOC_FCF_B->MinMax5 + FOC_FCF_B->MinMax6;

  /* Gain: '<S97>/Factor2' */
  FOC_FCF_B->Factor2 = FOC_FCF_P.Factor2_Gain * FOC_FCF_B->Sum3_k;

  /* Sum: '<S97>/DutyCycle_SuperSinus_3' */
  FOC_FCF_B->DutyCycle_SuperSinus_3[0] = FOC_FCF_B->DutyCycle_normed[6] -
    FOC_FCF_B->Factor2;
  FOC_FCF_B->DutyCycle_SuperSinus_3[1] = FOC_FCF_B->DutyCycle_normed[7] -
    FOC_FCF_B->Factor2;
  FOC_FCF_B->DutyCycle_SuperSinus_3[2] = FOC_FCF_B->DutyCycle_normed[8] -
    FOC_FCF_B->Factor2;

  /* End of Outputs for SubSystem: '<S15>/Super_Sinus_Modulation' */

  /* MultiPortSwitch: '<S15>/SelectModulation' incorporates:
   *  Constant: '<S15>/Enable_SuperSinMod'
   */
  if (FOC_FCF_P.FOC_SELECT_Modulation == 0) {
    /* MultiPortSwitch: '<S15>/SelectModulation' */
    for (i = 0; i < 9; i++) {
      FOC_FCF_B->SelMod_DutyCycles[i] = FOC_FCF_B->DutyCycle_normed[i];
    }
  } else {
    /* MultiPortSwitch: '<S15>/SelectModulation' */
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

  /* End of MultiPortSwitch: '<S15>/SelectModulation' */
  for (i = 0; i < 9; i++) {
    /* Bias: '<S93>/Scale [0..2]' */
    UnitDelay1_p = FOC_FCF_B->SelMod_DutyCycles[i] + FOC_FCF_P.Scale02_Bias;
    FOC_FCF_B->Scale02[i] = UnitDelay1_p;

    /* Gain: '<S93>/Scale  [0..1]' */
    UnitDelay1_p *= FOC_FCF_P.Scale01_Gain;
    FOC_FCF_B->Scale01[i] = UnitDelay1_p;

    /* Saturate: '<S93>/Limit [0..1]' */
    if (UnitDelay1_p > FOC_FCF_P.Limit01_UpperSat) {
      UnitDelay1_p = FOC_FCF_P.Limit01_UpperSat;
    } else if (UnitDelay1_p < FOC_FCF_P.Limit01_LowerSat) {
      UnitDelay1_p = FOC_FCF_P.Limit01_LowerSat;
    }

    /* Saturate: '<S93>/Limit [0..1]' */
    FOC_FCF_B->Limit01[i] = UnitDelay1_p;
  }

  /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_1' incorporates:
   *  Constant: '<S96>/Constant6'
   */
  switch ((int32_T)FOC_FCF_P.FOC_SELECT_Voltage_Assignment_UVW) {
   case 1:
    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[2];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[5];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[8];
    break;

   case 2:
    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[1];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[4];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[7];
    break;

   case 3:
    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[2];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[5];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[8];
    break;

   case 4:
    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[0];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[3];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[6];
    break;

   case 5:
    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[0];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[1];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[3];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[4];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[6];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[7];
    break;

   default:
    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_1' */
    FOC_FCF_B->Select_GateDriver_Assignment_1[0] = FOC_FCF_B->Limit01[2];
    FOC_FCF_B->Select_GateDriver_Assignment_1[1] = FOC_FCF_B->Limit01[1];
    FOC_FCF_B->Select_GateDriver_Assignment_1[2] = FOC_FCF_B->Limit01[0];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_2' */
    FOC_FCF_B->Select_GateDriver_Assignment_2[0] = FOC_FCF_B->Limit01[5];
    FOC_FCF_B->Select_GateDriver_Assignment_2[1] = FOC_FCF_B->Limit01[4];
    FOC_FCF_B->Select_GateDriver_Assignment_2[2] = FOC_FCF_B->Limit01[3];

    /* MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_3' */
    FOC_FCF_B->Select_GateDriver_Assignment_3[0] = FOC_FCF_B->Limit01[8];
    FOC_FCF_B->Select_GateDriver_Assignment_3[1] = FOC_FCF_B->Limit01[7];
    FOC_FCF_B->Select_GateDriver_Assignment_3[2] = FOC_FCF_B->Limit01[6];
    break;
  }

  /* End of MultiPortSwitch: '<S96>/Select_GateDriver_Assignment_1' */

  /* MultiPortSwitch: '<S3>/Manual_DutyCycles_switch' incorporates:
   *  Constant: '<S3>/FOC_SELECT_MANUAL_DutyCycles'
   */
  if (FOC_FCF_P.FOC_SELECT_MANUAL_DutyCycles == 0) {
    /* MultiPortSwitch: '<S3>/Manual_DutyCycles_switch' */
    FOC_FCF_B->DutyCycles_switch[0] = FOC_FCF_B->Select_GateDriver_Assignment_1
      [0];
    FOC_FCF_B->DutyCycles_switch[3] = FOC_FCF_B->Select_GateDriver_Assignment_2
      [0];
    FOC_FCF_B->DutyCycles_switch[6] = FOC_FCF_B->Select_GateDriver_Assignment_3
      [0];
    FOC_FCF_B->DutyCycles_switch[1] = FOC_FCF_B->Select_GateDriver_Assignment_1
      [1];
    FOC_FCF_B->DutyCycles_switch[4] = FOC_FCF_B->Select_GateDriver_Assignment_2
      [1];
    FOC_FCF_B->DutyCycles_switch[7] = FOC_FCF_B->Select_GateDriver_Assignment_3
      [1];
    FOC_FCF_B->DutyCycles_switch[2] = FOC_FCF_B->Select_GateDriver_Assignment_1
      [2];
    FOC_FCF_B->DutyCycles_switch[5] = FOC_FCF_B->Select_GateDriver_Assignment_2
      [2];
    FOC_FCF_B->DutyCycles_switch[8] = FOC_FCF_B->Select_GateDriver_Assignment_3
      [2];
  } else {
    /* MultiPortSwitch: '<S3>/Manual_DutyCycles_switch' incorporates:
     *  Constant: '<S3>/FOC_Manual_DutyCycles'
     */
    for (i = 0; i < 9; i++) {
      FOC_FCF_B->DutyCycles_switch[i] = FOC_FCF_P.FOC_Manual_DutyCycles_Value[i];
    }
  }

  /* End of MultiPortSwitch: '<S3>/Manual_DutyCycles_switch' */

  /* Switch: '<S3>/ASC_Switch' */
  if (FOC_FCF_B->LogicalOperator1) {
    for (i = 0; i < 9; i++) {
      FOC_FCF_Y->bus_FCF.DutyCycles[i] = FOC_FCF_B->DutyCycles_switch[i];
    }
  } else {
    /* MultiPortSwitch: '<S3>/ASC Switch' incorporates:
     *  Constant: '<S3>/FOC_AKS_Mode'
     */
    switch ((int32_T)FOC_FCF_P.FOC_ASC_Mode) {
     case 1:
      /* MultiPortSwitch: '<S3>/ASC Switch' incorporates:
       *  Constant: '<S3>/ASC_LS'
       */
      for (i = 0; i < 9; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_LS_Value[i];
      }
      break;

     case 2:
      /* MultiPortSwitch: '<S3>/ASC Switch' incorporates:
       *  Constant: '<S3>/ASC_HS'
       */
      for (i = 0; i < 9; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_HS_Value[i];
      }
      break;

     default:
      /* MultiPortSwitch: '<S3>/ASC Switch' incorporates:
       *  Constant: '<S3>/ASC_LSHS'
       */
      for (i = 0; i < 9; i++) {
        FOC_FCF_B->ASCSwitch[i] = FOC_FCF_P.ASC_LSHS_Value[i];
      }
      break;
    }

    /* End of MultiPortSwitch: '<S3>/ASC Switch' */
    for (i = 0; i < 9; i++) {
      FOC_FCF_Y->bus_FCF.DutyCycles[i] = FOC_FCF_B->ASCSwitch[i];
    }
  }

  /* End of Switch: '<S3>/ASC_Switch' */

  /* Sum: '<S24>/Deviation' */
  FOC_FCF_B->Deviation = FOC_FCF_B->Sum3 - FOC_FCF_B->phi_el_observer;

  /* Product: '<S24>/Product2' incorporates:
   *  Constant: '<S24>/Constant'
   *  Constant: '<S24>/Constant1'
   */
  FOC_FCF_B->Product2 = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_D * FOC_FCF_B->Deviation;

  /* Gain: '<S24>/Gain' */
  FOC_FCF_B->Gain_g = FOC_FCF_P.Gain_Gain_kc * FOC_FCF_B->Product2;

  /* Gain: '<S24>/Gain4' */
  FOC_FCF_B->winkelimpuls = FOC_FCF_P.FOC_OmegaObs3 * FOC_FCF_B->Deviation;

  /* Sum: '<S24>/Sum1' */
  FOC_FCF_B->Sum1_g4 = FOC_FCF_B->Gain_g + FOC_FCF_B->w_el;

  /* Product: '<S24>/Product' incorporates:
   *  Constant: '<S24>/FOC_T_fast'
   */
  FOC_FCF_B->Product_o = FOC_FCF_B->Sum1_g4 * FOC_FCF_P.FOC_T_fast_Value_df;

  /* Product: '<S24>/Product1' incorporates:
   *  Constant: '<S24>/Constant'
   */
  FOC_FCF_B->Product1_bi = FOC_FCF_P.FOC_AngleObserver_w0 *
    FOC_FCF_P.FOC_AngleObserver_w0 * FOC_FCF_B->Deviation;

  /* UnitDelay: '<S28>/Unit Delay1' */
  FOC_FCF_B->UnitDelay1 = FOC_FCF_DW->UnitDelay1_DSTATE_i;

  /* Sum: '<S24>/Sum2' */
  FOC_FCF_B->Sum2_mq = FOC_FCF_B->Product1_bi + FOC_FCF_B->UnitDelay1;

  /* Sum: '<S24>/Sum6' */
  FOC_FCF_B->Sum6 = FOC_FCF_B->Product_o + FOC_FCF_B->phi_el_observer;

  /* Product: '<S27>/Product' incorporates:
   *  Constant: '<S27>/FOC_T_fast'
   */
  FOC_FCF_B->Product_n = FOC_FCF_B->Sum2_mq * FOC_FCF_P.FOC_T_fast_Value_c;

  /* Sum: '<S27>/Sum2' */
  FOC_FCF_B->Sum2_e = FOC_FCF_B->Product_n + FOC_FCF_B->w_el;

  /* Product: '<S28>/Product' incorporates:
   *  Constant: '<S28>/FOC_T_fast'
   */
  FOC_FCF_B->Product_cd = FOC_FCF_B->winkelimpuls * FOC_FCF_P.FOC_T_fast_Value_k;

  /* Sum: '<S28>/Sum2' */
  FOC_FCF_B->Sum2_j = FOC_FCF_B->Product_cd + FOC_FCF_B->UnitDelay1;

  /* Gain: '<S5>/Gain1' */
  FOC_FCF_B->phi_el_U_trafo[0] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Switch2;
  FOC_FCF_B->phi_el_U_trafo[1] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Sum2_p;
  FOC_FCF_B->phi_el_U_trafo[2] = FOC_FCF_P.Gain1_Gain_kl * FOC_FCF_B->Sum1_l;

  /* Gain: '<S5>/Gain2' */
  FOC_FCF_B->phi_el_I_trafo = FOC_FCF_P.Gain2_Gain * FOC_FCF_B->Use_If_Mode[0];

  /* DiscreteFir: '<S33>/Discrete FIR Filter 20th order' */
  cff = 1;
  UnitDelay1_p = FOC_FCF_B->TmpSignalConversionAtDiscreteFI[0] *
    FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[0];
  for (i = FOC_FCF_DW->DiscreteFIRFilter20thorder_circ; i < 19; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  for (i = 0; i < FOC_FCF_DW->DiscreteFIRFilter20thorder_circ; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  FOC_FCF_B->I_dq1_Act_filt[0] = UnitDelay1_p;
  cff = 1;
  UnitDelay1_p = FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[0] *
    FOC_FCF_B->TmpSignalConversionAtDiscreteFI[1];
  for (i = FOC_FCF_DW->DiscreteFIRFilter20thorder_circ; i < 19; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  for (i = 0; i < FOC_FCF_DW->DiscreteFIRFilter20thorder_circ; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Coef[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  FOC_FCF_B->I_dq1_Act_filt[1] = UnitDelay1_p;

  /* End of DiscreteFir: '<S33>/Discrete FIR Filter 20th order' */

  /* DiscreteFir: '<S34>/Discrete FIR Filter 20th order' */
  cff = 1;
  UnitDelay1_p = FOC_FCF_B->TmpSignalConversionAtDiscrete_k[0] *
    FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[0];
  for (i = FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m; i < 19; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  for (i = 0; i < FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  FOC_FCF_B->DiscreteFIRFilter20thorder[0] = UnitDelay1_p;
  cff = 1;
  UnitDelay1_p = FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[0] *
    FOC_FCF_B->TmpSignalConversionAtDiscrete_k[1];
  for (i = FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m; i < 19; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  for (i = 0; i < FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_a[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  FOC_FCF_B->DiscreteFIRFilter20thorder[1] = UnitDelay1_p;

  /* End of DiscreteFir: '<S34>/Discrete FIR Filter 20th order' */

  /* Outputs for Atomic SubSystem: '<S15>/Calc_Modulation_Index' */
  /* Gain: '<S94>/U_DC//2' */
  FOC_FCF_B->U_DC2_l = FOC_FCF_P.U_DC2_Gain * FOC_FCF_B->U_DC_fcf;

  /* End of Outputs for SubSystem: '<S15>/Calc_Modulation_Index' */

  /* DiscreteFir: '<S35>/Discrete FIR Filter 20th order' */
  cff = 1;
  UnitDelay1_p = FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0] *
    FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[0];
  for (i = FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c; i < 19; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  for (i = 0; i < FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  /* DiscreteFir: '<S35>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->DiscreteFIRFilter20thorder_l[0] = UnitDelay1_p;

  /* SignalConversion generated from: '<S1>/Bus Creator' */
  FOC_FCF_B->I_dq_Act[0] = FOC_FCF_B->I_dq1_Act_filt[0];
  FOC_FCF_B->I_dq_Act[2] = FOC_FCF_B->DiscreteFIRFilter20thorder[0];
  FOC_FCF_B->I_dq_Act[4] = UnitDelay1_p;

  /* Outputs for Atomic SubSystem: '<S15>/Calc_Modulation_Index' */
  /* Math: '<S94>/Square' */
  UnitDelay1_p = FOC_FCF_B->Product_c0[0];

  /* Math: '<S94>/Square' */
  FOC_FCF_B->Square[0] = UnitDelay1_p * UnitDelay1_p;

  /* End of Outputs for SubSystem: '<S15>/Calc_Modulation_Index' */

  /* DiscreteFir: '<S35>/Discrete FIR Filter 20th order' */
  cff = 1;
  UnitDelay1_p = FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[0] *
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1];
  for (i = FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c; i < 19; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  for (i = 0; i < FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c; i++) {
    Gain_a = FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i + 19] *
      FOC_FCF_P.DiscreteFIRFilter20thorder_Co_l[cff];
    UnitDelay1_p += Gain_a;
    cff++;
  }

  /* DiscreteFir: '<S35>/Discrete FIR Filter 20th order' */
  FOC_FCF_B->DiscreteFIRFilter20thorder_l[1] = UnitDelay1_p;

  /* SignalConversion generated from: '<S1>/Bus Creator' */
  FOC_FCF_B->I_dq_Act[1] = FOC_FCF_B->I_dq1_Act_filt[1];
  FOC_FCF_B->I_dq_Act[3] = FOC_FCF_B->DiscreteFIRFilter20thorder[1];
  FOC_FCF_B->I_dq_Act[5] = UnitDelay1_p;

  /* Outputs for Atomic SubSystem: '<S15>/Calc_Modulation_Index' */
  /* Math: '<S94>/Square' */
  UnitDelay1_p = FOC_FCF_B->Product_c0[1];

  /* Math: '<S94>/Square' */
  FOC_FCF_B->Square[1] = UnitDelay1_p * UnitDelay1_p;

  /* MinMax: '<S94>/AvoidDivBy0' incorporates:
   *  Constant: '<S94>/Constant2'
   */
  UnitDelay1_p = fmaxf(FOC_FCF_P.Constant2_Value_d, FOC_FCF_B->U_DC2_l);

  /* MinMax: '<S94>/AvoidDivBy0' */
  FOC_FCF_B->AvoidDivBy0_f = UnitDelay1_p;

  /* Sum: '<S94>/Sum' */
  UnitDelay1_p = FOC_FCF_B->Square[0];

  /* Math: '<S94>/Square1' */
  Gain_a = FOC_FCF_B->Product_f[0];

  /* Math: '<S94>/Square1' */
  FOC_FCF_B->Square1[0] = Gain_a * Gain_a;

  /* Sum: '<S94>/Sum' */
  UnitDelay1_p += FOC_FCF_B->Square[1];

  /* Math: '<S94>/Square1' */
  Gain_a = FOC_FCF_B->Product_f[1];

  /* Math: '<S94>/Square1' */
  FOC_FCF_B->Square1[1] = Gain_a * Gain_a;

  /* Sum: '<S94>/Sum' */
  FOC_FCF_B->Sum_kr = UnitDelay1_p;

  /* Sqrt: '<S94>/Sqrt' */
  FOC_FCF_B->Sqrt = sqrtf(FOC_FCF_B->Sum_kr);

  /* Sum: '<S94>/Sum1' */
  UnitDelay1_p = FOC_FCF_B->Square1[0];

  /* Math: '<S94>/Square2' */
  Gain_a = FOC_FCF_B->Product_i[0];

  /* Math: '<S94>/Square2' */
  FOC_FCF_B->Square2[0] = Gain_a * Gain_a;

  /* Sum: '<S94>/Sum1' */
  UnitDelay1_p += FOC_FCF_B->Square1[1];

  /* Math: '<S94>/Square2' */
  Gain_a = FOC_FCF_B->Product_i[1];

  /* Math: '<S94>/Square2' */
  FOC_FCF_B->Square2[1] = Gain_a * Gain_a;

  /* Sum: '<S94>/Sum1' */
  FOC_FCF_B->Sum1_a = UnitDelay1_p;

  /* Sqrt: '<S94>/Sqrt1' */
  FOC_FCF_B->Sqrt1 = sqrtf(FOC_FCF_B->Sum1_a);

  /* Sum: '<S94>/Sum2' */
  UnitDelay1_p = FOC_FCF_B->Square2[0];
  UnitDelay1_p += FOC_FCF_B->Square2[1];

  /* Sum: '<S94>/Sum2' */
  FOC_FCF_B->Sum2_iq = UnitDelay1_p;

  /* Sqrt: '<S94>/Sqrt2' */
  FOC_FCF_B->Sqrt2 = sqrtf(FOC_FCF_B->Sum2_iq);

  /* Product: '<S94>/Divide3' */
  FOC_FCF_B->ModInd[0] = FOC_FCF_B->Sqrt / FOC_FCF_B->AvoidDivBy0_f;
  FOC_FCF_B->ModInd[1] = FOC_FCF_B->Sqrt1 / FOC_FCF_B->AvoidDivBy0_f;
  FOC_FCF_B->ModInd[2] = FOC_FCF_B->Sqrt2 / FOC_FCF_B->AvoidDivBy0_f;

  /* End of Outputs for SubSystem: '<S15>/Calc_Modulation_Index' */

  /* Gain: '<S12>/[1//s] => [rpm]' */
  FOC_FCF_B->usrpm = FOC_FCF_P.usrpm_Gain * FOC_FCF_B->w_el;

  /* Abs: '<S12>/Abs' */
  FOC_FCF_B->Abs_d = fabsf(FOC_FCF_B->usrpm);

  /* RelationalOperator: '<S87>/Compare' incorporates:
   *  Constant: '<S87>/Constant'
   */
  FOC_FCF_B->Compare_c = (FOC_FCF_B->Abs_d > FOC_FCF_P.LIMIT_MAX_Overspeed);

  /* Logic: '<S12>/Logical Operator3' incorporates:
   *  Constant: '<S12>/Reset_OS_Error'
   */
  FOC_FCF_B->LogicalOperator3_p = ((FOC_FCF_P.FOC_RESET_OS_Error != 0.0F) ||
    FOC_FCF_U->bus_SMF.global_reset_errors);

  /* RelationalOperator: '<S90>/Compare' incorporates:
   *  Constant: '<S90>/Constant'
   */
  FOC_FCF_B->Compare_gt = ((int32_T)FOC_FCF_B->LogicalOperator3_p > (int32_T)
    FOC_FCF_P.Constant_Value_ep);

  /* UnitDelay: '<S88>/Delay Input1'
   *
   * Block description for '<S88>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_B->Uk1_h = FOC_FCF_DW->DelayInput1_DSTATE_e;

  /* MultiPortSwitch: '<S12>/Selectphicalc2' incorporates:
   *  Constant: '<S12>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overspeed == 0) {
    /* MultiPortSwitch: '<S12>/Selectphicalc2' incorporates:
     *  Constant: '<S12>/Constant1'
     */
    FOC_FCF_B->Selectphicalc2_d = FOC_FCF_P.Constant1_Value_n;
  } else {
    /* RelationalOperator: '<S88>/FixPt Relational Operator' */
    FOC_FCF_B->FixPtRelationalOperator = ((int32_T)FOC_FCF_B->Compare_gt >
      (int32_T)FOC_FCF_B->Uk1_h);

    /* MultiPortSwitch: '<S12>/Selectphicalc2' */
    FOC_FCF_B->Selectphicalc2_d = FOC_FCF_B->FixPtRelationalOperator;
  }

  /* End of MultiPortSwitch: '<S12>/Selectphicalc2' */

  /* Memory: '<S89>/Memory' */
  FOC_FCF_B->Memory_k = FOC_FCF_DW->Memory_PreviousInput_i;

  /* CombinatorialLogic: '<S89>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_c;
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_d;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_k;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_e[0U] = FOC_FCF_P.Logic_table_lc[(uint32_T)i];
  FOC_FCF_B->Logic_e[1U] = FOC_FCF_P.Logic_table_lc[(uint32_T)i + 8U];

  /* MultiPortSwitch: '<S12>/Selectphicalc1' incorporates:
   *  Constant: '<S12>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  if ((int32_T)FOC_FCF_P.FOC_ENABLE_Overspeed == 0) {
    /* MultiPortSwitch: '<S12>/Selectphicalc1' incorporates:
     *  Constant: '<S12>/Constant2'
     */
    FOC_FCF_B->Overspeed_Error = FOC_FCF_P.Constant2_Value_gw;
  } else {
    /* MultiPortSwitch: '<S12>/Selectphicalc1' */
    FOC_FCF_B->Overspeed_Error = FOC_FCF_B->Logic_e[0];
  }

  /* End of MultiPortSwitch: '<S12>/Selectphicalc1' */

  /* MultiPortSwitch: '<S8>/DataSourceSwitch' incorporates:
   *  Constant: '<S8>/SELECT_DataSource'
   */
  if (!FOC_FCF_P.SELECT_DataSource_Value) {
    /* MultiPortSwitch: '<S8>/DataSourceSwitch' */
    FOC_FCF_B->DataSourceSwitch = 0.0F;
  } else {
    /* MultiPortSwitch: '<S8>/DataSourceSwitch' incorporates:
     *  Constant: '<S8>/NoError_Manual'
     */
    FOC_FCF_B->DataSourceSwitch = FOC_FCF_P.NoError_Manual_Value;
  }

  /* End of MultiPortSwitch: '<S8>/DataSourceSwitch' */

  /* S-Function (sfix_bitop): '<S9>/Mask_6Bits_Inv1_FLT' */
  FOC_FCF_B->Mask_6Bits_Inv1_FLT = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_FLT
    & FOC_FCF_P.Mask_6Bits_Inv1_FLT_BitMask;

  /* S-Function (sfix_bitop): '<S49>/Bitwise NOT' */
  FOC_FCF_B->BitwiseNOT = ~FOC_FCF_B->Mask_6Bits_Inv1_FLT;

  /* S-Function (sfix_bitop): '<S49>/MaskBit0' */
  FOC_FCF_B->MaskBit0 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit0_BitMask;

  /* ArithShift: '<S49>/get_U_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S49>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_FLT = FOC_FCF_B->MaskBit0;

  /* DataTypeConversion: '<S9>/Data Type Conversion14' */
  FOC_FCF_B->bus_InvStatus.U1_HS_FLT = (FOC_FCF_B->get_U_HS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S49>/MaskBit1' */
  FOC_FCF_B->MaskBit1 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit1_BitMask;

  /* ArithShift: '<S49>/get_U_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S49>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_FLT = FOC_FCF_B->MaskBit1 >> 1;

  /* DataTypeConversion: '<S9>/Data Type Conversion17' */
  FOC_FCF_B->bus_InvStatus.U1_LS_FLT = (FOC_FCF_B->get_U_LS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S49>/MaskBit2' */
  FOC_FCF_B->MaskBit2 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit2_BitMask;

  /* ArithShift: '<S49>/get_V_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S49>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_FLT = FOC_FCF_B->MaskBit2 >> 2;

  /* DataTypeConversion: '<S9>/Data Type Conversion15' */
  FOC_FCF_B->bus_InvStatus.V1_HS_FLT = (FOC_FCF_B->get_V_HS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S49>/MaskBit3' */
  FOC_FCF_B->MaskBit3 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit3_BitMask;

  /* ArithShift: '<S49>/get_V_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S49>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_FLT = FOC_FCF_B->MaskBit3 >> 3;

  /* DataTypeConversion: '<S9>/Data Type Conversion18' */
  FOC_FCF_B->bus_InvStatus.V1_LS_FLT = (FOC_FCF_B->get_V_LS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S49>/MaskBit4' */
  FOC_FCF_B->MaskBit4 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit4_BitMask;

  /* ArithShift: '<S49>/get_W_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S49>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_FLT = FOC_FCF_B->MaskBit4 >> 4;

  /* DataTypeConversion: '<S9>/Data Type Conversion16' */
  FOC_FCF_B->bus_InvStatus.W1_HS_FLT = (FOC_FCF_B->get_W_HS_FLT != 0U);

  /* S-Function (sfix_bitop): '<S49>/MaskBit5' */
  FOC_FCF_B->MaskBit5 = FOC_FCF_B->BitwiseNOT & FOC_FCF_P.MaskBit5_BitMask;

  /* ArithShift: '<S49>/get_W_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S49>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_FLT = FOC_FCF_B->MaskBit5 >> 5;

  /* DataTypeConversion: '<S9>/Data Type Conversion19' */
  FOC_FCF_B->bus_InvStatus.W1_LS_FLT = (FOC_FCF_B->get_W_LS_FLT != 0U);

  /* RelationalOperator: '<S55>/Compare' incorporates:
   *  Constant: '<S55>/Constant'
   */
  FOC_FCF_B->Compare_lv = (FOC_FCF_B->BitwiseNOT != FOC_FCF_P.Constant_Value_l);

  /* DataTypeConversion: '<S9>/Data Type Conversion37' */
  FOC_FCF_B->bus_InvStatus.FLT_Error_Sys1 = FOC_FCF_B->Compare_lv;

  /* S-Function (sfix_bitop): '<S9>/Mask_6Bits_Inv1_RDY' */
  FOC_FCF_B->Mask_6Bits_Inv1_RDY = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_RDY
    & FOC_FCF_P.Mask_6Bits_Inv1_RDY_BitMask;

  /* S-Function (sfix_bitop): '<S50>/MaskBit0' */
  FOC_FCF_B->MaskBit0_c = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit0_BitMask_b;

  /* ArithShift: '<S50>/get_U_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S50>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_RDY = FOC_FCF_B->MaskBit0_c;

  /* DataTypeConversion: '<S9>/Data Type Conversion1' */
  FOC_FCF_B->bus_InvStatus.U1_HS_RDY = (FOC_FCF_B->get_U_HS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S50>/MaskBit1' */
  FOC_FCF_B->MaskBit1_b = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit1_BitMask_j;

  /* ArithShift: '<S50>/get_U_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S50>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_RDY = FOC_FCF_B->MaskBit1_b >> 1;

  /* DataTypeConversion: '<S9>/Data Type Conversion2' */
  FOC_FCF_B->bus_InvStatus.U1_LS_RDY = (FOC_FCF_B->get_U_LS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S50>/MaskBit2' */
  FOC_FCF_B->MaskBit2_n = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit2_BitMask_m;

  /* ArithShift: '<S50>/get_V_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S50>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_RDY = FOC_FCF_B->MaskBit2_n >> 2;

  /* DataTypeConversion: '<S9>/Data Type Conversion3' */
  FOC_FCF_B->bus_InvStatus.V1_HS_RDY = (FOC_FCF_B->get_V_HS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S50>/MaskBit3' */
  FOC_FCF_B->MaskBit3_a = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit3_BitMask_i;

  /* ArithShift: '<S50>/get_V_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S50>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_RDY = FOC_FCF_B->MaskBit3_a >> 3;

  /* DataTypeConversion: '<S9>/Data Type Conversion4' */
  FOC_FCF_B->bus_InvStatus.V1_LS_RDY = (FOC_FCF_B->get_V_LS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S50>/MaskBit4' */
  FOC_FCF_B->MaskBit4_c = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit4_BitMask_d;

  /* ArithShift: '<S50>/get_W_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S50>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_RDY = FOC_FCF_B->MaskBit4_c >> 4;

  /* DataTypeConversion: '<S9>/Data Type Conversion5' */
  FOC_FCF_B->bus_InvStatus.W1_HS_RDY = (FOC_FCF_B->get_W_HS_RDY != 0U);

  /* S-Function (sfix_bitop): '<S50>/MaskBit5' */
  FOC_FCF_B->MaskBit5_l = FOC_FCF_B->Mask_6Bits_Inv1_RDY &
    FOC_FCF_P.MaskBit5_BitMask_a;

  /* ArithShift: '<S50>/get_W_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S50>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_RDY = FOC_FCF_B->MaskBit5_l >> 5;

  /* DataTypeConversion: '<S9>/Data Type Conversion6' */
  FOC_FCF_B->bus_InvStatus.W1_LS_RDY = (FOC_FCF_B->get_W_LS_RDY != 0U);

  /* RelationalOperator: '<S56>/Compare' incorporates:
   *  Constant: '<S56>/Constant'
   */
  FOC_FCF_B->Compare_fp = (FOC_FCF_B->Mask_6Bits_Inv1_RDY !=
    FOC_FCF_P.CompareToConstant_const);

  /* DataTypeConversion: '<S9>/Data Type Conversion38' */
  FOC_FCF_B->bus_InvStatus.RDY_Error_Sys1 = FOC_FCF_B->Compare_fp;

  /* S-Function (sfix_bitop): '<S9>/Mask_6Bits_Inv2_FLT' */
  FOC_FCF_B->Mask_6Bits_Inv2_FLT = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_FLT
    & FOC_FCF_P.Mask_6Bits_Inv2_FLT_BitMask;

  /* S-Function (sfix_bitop): '<S51>/Bitwise NOT' */
  FOC_FCF_B->BitwiseNOT_j = ~FOC_FCF_B->Mask_6Bits_Inv2_FLT;

  /* S-Function (sfix_bitop): '<S51>/MaskBit0' */
  FOC_FCF_B->MaskBit0_o = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit0_BitMask_g;

  /* ArithShift: '<S51>/get_U_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S51>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_FLT_i = FOC_FCF_B->MaskBit0_o;

  /* DataTypeConversion: '<S9>/Data Type Conversion20' */
  FOC_FCF_B->bus_InvStatus.U2_HS_FLT = (FOC_FCF_B->get_U_HS_FLT_i != 0U);

  /* S-Function (sfix_bitop): '<S51>/MaskBit1' */
  FOC_FCF_B->MaskBit1_ba = FOC_FCF_B->BitwiseNOT_j &
    FOC_FCF_P.MaskBit1_BitMask_n;

  /* ArithShift: '<S51>/get_U_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S51>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_FLT_a = FOC_FCF_B->MaskBit1_ba >> 1;

  /* DataTypeConversion: '<S9>/Data Type Conversion23' */
  FOC_FCF_B->bus_InvStatus.U2_LS_FLT = (FOC_FCF_B->get_U_LS_FLT_a != 0U);

  /* S-Function (sfix_bitop): '<S51>/MaskBit2' */
  FOC_FCF_B->MaskBit2_d = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit2_BitMask_n;

  /* ArithShift: '<S51>/get_V_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S51>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_FLT_i = FOC_FCF_B->MaskBit2_d >> 2;

  /* DataTypeConversion: '<S9>/Data Type Conversion21' */
  FOC_FCF_B->bus_InvStatus.V2_HS_FLT = (FOC_FCF_B->get_V_HS_FLT_i != 0U);

  /* S-Function (sfix_bitop): '<S51>/MaskBit3' */
  FOC_FCF_B->MaskBit3_d = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit3_BitMask_c;

  /* ArithShift: '<S51>/get_V_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S51>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_FLT_c = FOC_FCF_B->MaskBit3_d >> 3;

  /* DataTypeConversion: '<S9>/Data Type Conversion24' */
  FOC_FCF_B->bus_InvStatus.V2_LS_FLT = (FOC_FCF_B->get_V_LS_FLT_c != 0U);

  /* S-Function (sfix_bitop): '<S51>/MaskBit4' */
  FOC_FCF_B->MaskBit4_p = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit4_BitMask_o;

  /* ArithShift: '<S51>/get_W_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S51>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_FLT_f = FOC_FCF_B->MaskBit4_p >> 4;

  /* DataTypeConversion: '<S9>/Data Type Conversion22' */
  FOC_FCF_B->bus_InvStatus.W2_HS_FLT = (FOC_FCF_B->get_W_HS_FLT_f != 0U);

  /* S-Function (sfix_bitop): '<S51>/MaskBit5' */
  FOC_FCF_B->MaskBit5_o = FOC_FCF_B->BitwiseNOT_j & FOC_FCF_P.MaskBit5_BitMask_h;

  /* ArithShift: '<S51>/get_W_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S51>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_FLT_l = FOC_FCF_B->MaskBit5_o >> 5;

  /* DataTypeConversion: '<S9>/Data Type Conversion25' */
  FOC_FCF_B->bus_InvStatus.W2_LS_FLT = (FOC_FCF_B->get_W_LS_FLT_l != 0U);

  /* RelationalOperator: '<S57>/Compare' incorporates:
   *  Constant: '<S57>/Constant'
   */
  FOC_FCF_B->Compare_g1 = (FOC_FCF_B->BitwiseNOT_j !=
    FOC_FCF_P.Constant_Value_eg);

  /* DataTypeConversion: '<S9>/Data Type Conversion39' */
  FOC_FCF_B->bus_InvStatus.FLT_Error_Sys2 = FOC_FCF_B->Compare_g1;

  /* S-Function (sfix_bitop): '<S9>/Mask_6Bits_Inv2_RDY' */
  FOC_FCF_B->Mask_6Bits_Inv2_RDY = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_RDY
    & FOC_FCF_P.Mask_6Bits_Inv2_RDY_BitMask;

  /* S-Function (sfix_bitop): '<S52>/MaskBit0' */
  FOC_FCF_B->MaskBit0_p = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit0_BitMask_bn;

  /* ArithShift: '<S52>/get_U_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S52>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_RDY_i = FOC_FCF_B->MaskBit0_p;

  /* DataTypeConversion: '<S9>/Data Type Conversion7' */
  FOC_FCF_B->bus_InvStatus.U2_HS_RDY = (FOC_FCF_B->get_U_HS_RDY_i != 0U);

  /* S-Function (sfix_bitop): '<S52>/MaskBit1' */
  FOC_FCF_B->MaskBit1_m = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit1_BitMask_a;

  /* ArithShift: '<S52>/get_U_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S52>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_RDY_f = FOC_FCF_B->MaskBit1_m >> 1;

  /* DataTypeConversion: '<S9>/Data Type Conversion26' */
  FOC_FCF_B->bus_InvStatus.U2_LS_RDY = (FOC_FCF_B->get_U_LS_RDY_f != 0U);

  /* S-Function (sfix_bitop): '<S52>/MaskBit2' */
  FOC_FCF_B->MaskBit2_g = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit2_BitMask_o;

  /* ArithShift: '<S52>/get_V_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S52>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_RDY_j = FOC_FCF_B->MaskBit2_g >> 2;

  /* DataTypeConversion: '<S9>/Data Type Conversion27' */
  FOC_FCF_B->bus_InvStatus.V2_HS_RDY = (FOC_FCF_B->get_V_HS_RDY_j != 0U);

  /* S-Function (sfix_bitop): '<S52>/MaskBit3' */
  FOC_FCF_B->MaskBit3_k = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit3_BitMask_h;

  /* ArithShift: '<S52>/get_V_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S52>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_RDY_a = FOC_FCF_B->MaskBit3_k >> 3;

  /* DataTypeConversion: '<S9>/Data Type Conversion28' */
  FOC_FCF_B->bus_InvStatus.V2_LS_RDY = (FOC_FCF_B->get_V_LS_RDY_a != 0U);

  /* S-Function (sfix_bitop): '<S52>/MaskBit4' */
  FOC_FCF_B->MaskBit4_l = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit4_BitMask_e;

  /* ArithShift: '<S52>/get_W_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S52>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_RDY_n = FOC_FCF_B->MaskBit4_l >> 4;

  /* DataTypeConversion: '<S9>/Data Type Conversion29' */
  FOC_FCF_B->bus_InvStatus.W2_HS_RDY = (FOC_FCF_B->get_W_HS_RDY_n != 0U);

  /* S-Function (sfix_bitop): '<S52>/MaskBit5' */
  FOC_FCF_B->MaskBit5_lb = FOC_FCF_B->Mask_6Bits_Inv2_RDY &
    FOC_FCF_P.MaskBit5_BitMask_l;

  /* ArithShift: '<S52>/get_W_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S52>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_RDY_l = FOC_FCF_B->MaskBit5_lb >> 5;

  /* DataTypeConversion: '<S9>/Data Type Conversion30' */
  FOC_FCF_B->bus_InvStatus.W2_LS_RDY = (FOC_FCF_B->get_W_LS_RDY_l != 0U);

  /* RelationalOperator: '<S58>/Compare' incorporates:
   *  Constant: '<S58>/Constant'
   */
  FOC_FCF_B->Compare_e0 = (FOC_FCF_B->Mask_6Bits_Inv2_RDY !=
    FOC_FCF_P.CompareToConstant_const_n);

  /* DataTypeConversion: '<S9>/Data Type Conversion40' */
  FOC_FCF_B->bus_InvStatus.RDY_Error_Sys2 = FOC_FCF_B->Compare_e0;

  /* S-Function (sfix_bitop): '<S9>/Mask_6Bits_Inv3_FLT' */
  FOC_FCF_B->Mask_6Bits_Inv3_FLT = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_FLT
    & FOC_FCF_P.Mask_6Bits_Inv3_FLT_BitMask;

  /* S-Function (sfix_bitop): '<S53>/Bitwise NOT' */
  FOC_FCF_B->BitwiseNOT_c = ~FOC_FCF_B->Mask_6Bits_Inv3_FLT;

  /* S-Function (sfix_bitop): '<S53>/MaskBit0' */
  FOC_FCF_B->MaskBit0_ph = FOC_FCF_B->BitwiseNOT_c &
    FOC_FCF_P.MaskBit0_BitMask_m;

  /* ArithShift: '<S53>/get_U_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S53>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_FLT_m = FOC_FCF_B->MaskBit0_ph;

  /* DataTypeConversion: '<S9>/Data Type Conversion8' */
  FOC_FCF_B->bus_InvStatus.U3_HS_FLT = (FOC_FCF_B->get_U_HS_FLT_m != 0U);

  /* S-Function (sfix_bitop): '<S53>/MaskBit1' */
  FOC_FCF_B->MaskBit1_k = FOC_FCF_B->BitwiseNOT_c & FOC_FCF_P.MaskBit1_BitMask_d;

  /* ArithShift: '<S53>/get_U_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S53>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_FLT_h = FOC_FCF_B->MaskBit1_k >> 1;

  /* DataTypeConversion: '<S9>/Data Type Conversion11' */
  FOC_FCF_B->bus_InvStatus.U3_LS_FLT = (FOC_FCF_B->get_U_LS_FLT_h != 0U);

  /* S-Function (sfix_bitop): '<S53>/MaskBit2' */
  FOC_FCF_B->MaskBit2_f = FOC_FCF_B->BitwiseNOT_c & FOC_FCF_P.MaskBit2_BitMask_b;

  /* ArithShift: '<S53>/get_V_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S53>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_FLT_h = FOC_FCF_B->MaskBit2_f >> 2;

  /* DataTypeConversion: '<S9>/Data Type Conversion9' */
  FOC_FCF_B->bus_InvStatus.V3_HS_FLT = (FOC_FCF_B->get_V_HS_FLT_h != 0U);

  /* S-Function (sfix_bitop): '<S53>/MaskBit3' */
  FOC_FCF_B->MaskBit3_a2 = FOC_FCF_B->BitwiseNOT_c &
    FOC_FCF_P.MaskBit3_BitMask_l;

  /* ArithShift: '<S53>/get_V_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S53>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_FLT_g = FOC_FCF_B->MaskBit3_a2 >> 3;

  /* DataTypeConversion: '<S9>/Data Type Conversion12' */
  FOC_FCF_B->bus_InvStatus.V3_LS_FLT = (FOC_FCF_B->get_V_LS_FLT_g != 0U);

  /* S-Function (sfix_bitop): '<S53>/MaskBit4' */
  FOC_FCF_B->MaskBit4_f = FOC_FCF_B->BitwiseNOT_c & FOC_FCF_P.MaskBit4_BitMask_b;

  /* ArithShift: '<S53>/get_W_HS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S53>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_FLT_m = FOC_FCF_B->MaskBit4_f >> 4;

  /* DataTypeConversion: '<S9>/Data Type Conversion10' */
  FOC_FCF_B->bus_InvStatus.W3_HS_FLT = (FOC_FCF_B->get_W_HS_FLT_m != 0U);

  /* S-Function (sfix_bitop): '<S53>/MaskBit5' */
  FOC_FCF_B->MaskBit5_h = FOC_FCF_B->BitwiseNOT_c & FOC_FCF_P.MaskBit5_BitMask_e;

  /* ArithShift: '<S53>/get_W_LS_FLT' incorporates:
   *  S-Function (sfix_bitop): '<S53>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_FLT_g = FOC_FCF_B->MaskBit5_h >> 5;

  /* DataTypeConversion: '<S9>/Data Type Conversion13' */
  FOC_FCF_B->bus_InvStatus.W3_LS_FLT = (FOC_FCF_B->get_W_LS_FLT_g != 0U);

  /* RelationalOperator: '<S59>/Compare' incorporates:
   *  Constant: '<S59>/Constant'
   */
  FOC_FCF_B->Compare_nd = (FOC_FCF_B->BitwiseNOT_c != FOC_FCF_P.Constant_Value_f);

  /* DataTypeConversion: '<S9>/Data Type Conversion41' */
  FOC_FCF_B->bus_InvStatus.FLT_Error_Sys3 = FOC_FCF_B->Compare_nd;

  /* S-Function (sfix_bitop): '<S9>/Mask_6Bits_Inv3_RDY' */
  FOC_FCF_B->Mask_6Bits_Inv3_RDY = FOC_FCF_U->bus_BSW_FCF.Gate_Driver_Status_RDY
    & FOC_FCF_P.Mask_6Bits_Inv3_RDY_BitMask;

  /* S-Function (sfix_bitop): '<S54>/MaskBit0' */
  FOC_FCF_B->MaskBit0_k = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit0_BitMask_l;

  /* ArithShift: '<S54>/get_U_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S54>/MaskBit0'
   */
  FOC_FCF_B->get_U_HS_RDY_e = FOC_FCF_B->MaskBit0_k;

  /* DataTypeConversion: '<S9>/Data Type Conversion36' */
  FOC_FCF_B->bus_InvStatus.U3_HS_RDY = (FOC_FCF_B->get_U_HS_RDY_e != 0U);

  /* S-Function (sfix_bitop): '<S54>/MaskBit1' */
  FOC_FCF_B->MaskBit1_o = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit1_BitMask_dr;

  /* ArithShift: '<S54>/get_U_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S54>/MaskBit1'
   */
  FOC_FCF_B->get_U_LS_RDY_l = FOC_FCF_B->MaskBit1_o >> 1;

  /* DataTypeConversion: '<S9>/Data Type Conversion31' */
  FOC_FCF_B->bus_InvStatus.U3_LS_RDY = (FOC_FCF_B->get_U_LS_RDY_l != 0U);

  /* S-Function (sfix_bitop): '<S54>/MaskBit2' */
  FOC_FCF_B->MaskBit2_a = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit2_BitMask_bx;

  /* ArithShift: '<S54>/get_V_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S54>/MaskBit2'
   */
  FOC_FCF_B->get_V_HS_RDY_e = FOC_FCF_B->MaskBit2_a >> 2;

  /* DataTypeConversion: '<S9>/Data Type Conversion32' */
  FOC_FCF_B->bus_InvStatus.V3_HS_RDY = (FOC_FCF_B->get_V_HS_RDY_e != 0U);

  /* S-Function (sfix_bitop): '<S54>/MaskBit3' */
  FOC_FCF_B->MaskBit3_kg = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit3_BitMask_it;

  /* ArithShift: '<S54>/get_V_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S54>/MaskBit3'
   */
  FOC_FCF_B->get_V_LS_RDY_k = FOC_FCF_B->MaskBit3_kg >> 3;

  /* DataTypeConversion: '<S9>/Data Type Conversion33' */
  FOC_FCF_B->bus_InvStatus.V3_LS_RDY = (FOC_FCF_B->get_V_LS_RDY_k != 0U);

  /* S-Function (sfix_bitop): '<S54>/MaskBit4' */
  FOC_FCF_B->MaskBit4_ch = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit4_BitMask_a;

  /* ArithShift: '<S54>/get_W_HS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S54>/MaskBit4'
   */
  FOC_FCF_B->get_W_HS_RDY_h = FOC_FCF_B->MaskBit4_ch >> 4;

  /* DataTypeConversion: '<S9>/Data Type Conversion34' */
  FOC_FCF_B->bus_InvStatus.W3_HS_RDY = (FOC_FCF_B->get_W_HS_RDY_h != 0U);

  /* S-Function (sfix_bitop): '<S54>/MaskBit5' */
  FOC_FCF_B->MaskBit5_p = FOC_FCF_B->Mask_6Bits_Inv3_RDY &
    FOC_FCF_P.MaskBit5_BitMask_b;

  /* ArithShift: '<S54>/get_W_LS_RDY' incorporates:
   *  S-Function (sfix_bitop): '<S54>/MaskBit5'
   */
  FOC_FCF_B->get_W_LS_RDY_m = FOC_FCF_B->MaskBit5_p >> 5;

  /* DataTypeConversion: '<S9>/Data Type Conversion35' */
  FOC_FCF_B->bus_InvStatus.W3_LS_RDY = (FOC_FCF_B->get_W_LS_RDY_m != 0U);

  /* RelationalOperator: '<S60>/Compare' incorporates:
   *  Constant: '<S60>/Constant'
   */
  FOC_FCF_B->Compare_cf = (FOC_FCF_B->Mask_6Bits_Inv3_RDY !=
    FOC_FCF_P.CompareToConstant_const_h);

  /* DataTypeConversion: '<S9>/Data Type Conversion42' */
  FOC_FCF_B->bus_InvStatus.RDY_Error_Sys3 = FOC_FCF_B->Compare_cf;

  /* MultiPortSwitch: '<S48>/EN_FLT_Switch_1' incorporates:
   *  Constant: '<S48>/ENABLE_GateDriver_FLT_Error_Sys1'
   */
  if ((int32_T)FOC_FCF_P.ENABLE_GateDriver_FLT_Error_Sys1 == 0) {
    /* MultiPortSwitch: '<S48>/EN_FLT_Switch_1' incorporates:
     *  Constant: '<S48>/NO_ERROR'
     */
    FOC_FCF_B->EN_FLT_Switch_1 = FOC_FCF_P.NO_ERROR_Value;
  } else {
    /* MultiPortSwitch: '<S48>/EN_FLT_Switch_1' */
    FOC_FCF_B->EN_FLT_Switch_1 = FOC_FCF_B->bus_InvStatus.FLT_Error_Sys1;
  }

  /* End of MultiPortSwitch: '<S48>/EN_FLT_Switch_1' */

  /* MultiPortSwitch: '<S48>/EN_FLT_Switch_2' incorporates:
   *  Constant: '<S48>/ENABLE_GateDriver_FLT_Error_Sys2'
   */
  if ((int32_T)FOC_FCF_P.ENABLE_GateDriver_FLT_Error_Sys2 == 0) {
    /* MultiPortSwitch: '<S48>/EN_FLT_Switch_2' incorporates:
     *  Constant: '<S48>/NO_ERROR'
     */
    FOC_FCF_B->EN_FLT_Switch_2 = FOC_FCF_P.NO_ERROR_Value;
  } else {
    /* MultiPortSwitch: '<S48>/EN_FLT_Switch_2' */
    FOC_FCF_B->EN_FLT_Switch_2 = FOC_FCF_B->bus_InvStatus.FLT_Error_Sys2;
  }

  /* End of MultiPortSwitch: '<S48>/EN_FLT_Switch_2' */

  /* MultiPortSwitch: '<S48>/EN_FLT_Switch_3' incorporates:
   *  Constant: '<S48>/ENABLE_GateDriver_FLT_Error_Sys3'
   */
  if ((int32_T)FOC_FCF_P.ENABLE_GateDriver_FLT_Error_Sys3 == 0) {
    /* MultiPortSwitch: '<S48>/EN_FLT_Switch_3' incorporates:
     *  Constant: '<S48>/NO_ERROR'
     */
    FOC_FCF_B->EN_FLT_Switch_3 = FOC_FCF_P.NO_ERROR_Value;
  } else {
    /* MultiPortSwitch: '<S48>/EN_FLT_Switch_3' */
    FOC_FCF_B->EN_FLT_Switch_3 = FOC_FCF_B->bus_InvStatus.FLT_Error_Sys3;
  }

  /* End of MultiPortSwitch: '<S48>/EN_FLT_Switch_3' */

  /* MultiPortSwitch: '<S48>/EN_RDY_Switch_1' incorporates:
   *  Constant: '<S48>/ENABLE_GateDriver_RDY_Error_Sys1'
   */
  if ((int32_T)FOC_FCF_P.ENABLE_GateDriver_RDY_Error_Sys1 == 0) {
    /* MultiPortSwitch: '<S48>/EN_RDY_Switch_1' incorporates:
     *  Constant: '<S48>/NO_ERROR'
     */
    FOC_FCF_B->EN_RDY_Switch_1 = FOC_FCF_P.NO_ERROR_Value;
  } else {
    /* MultiPortSwitch: '<S48>/EN_RDY_Switch_1' */
    FOC_FCF_B->EN_RDY_Switch_1 = FOC_FCF_B->bus_InvStatus.RDY_Error_Sys1;
  }

  /* End of MultiPortSwitch: '<S48>/EN_RDY_Switch_1' */

  /* MultiPortSwitch: '<S48>/EN_RDY_Switch_2' incorporates:
   *  Constant: '<S48>/ENABLE_GateDriver_RDY_Error_Sys2'
   */
  if ((int32_T)FOC_FCF_P.ENABLE_GateDriver_RDY_Error_Sys2 == 0) {
    /* MultiPortSwitch: '<S48>/EN_RDY_Switch_2' incorporates:
     *  Constant: '<S48>/NO_ERROR'
     */
    FOC_FCF_B->EN_RDY_Switch_2 = FOC_FCF_P.NO_ERROR_Value;
  } else {
    /* MultiPortSwitch: '<S48>/EN_RDY_Switch_2' */
    FOC_FCF_B->EN_RDY_Switch_2 = FOC_FCF_B->bus_InvStatus.RDY_Error_Sys2;
  }

  /* End of MultiPortSwitch: '<S48>/EN_RDY_Switch_2' */

  /* MultiPortSwitch: '<S48>/EN_RDY_Switch_3' incorporates:
   *  Constant: '<S48>/ENABLE_GateDriver_RDY_Error_Sys3'
   */
  if ((int32_T)FOC_FCF_P.ENABLE_GateDriver_RDY_Error_Sys3 == 0) {
    /* MultiPortSwitch: '<S48>/EN_RDY_Switch_3' incorporates:
     *  Constant: '<S48>/NO_ERROR'
     */
    FOC_FCF_B->EN_RDY_Switch_3 = FOC_FCF_P.NO_ERROR_Value;
  } else {
    /* MultiPortSwitch: '<S48>/EN_RDY_Switch_3' */
    FOC_FCF_B->EN_RDY_Switch_3 = FOC_FCF_B->bus_InvStatus.RDY_Error_Sys3;
  }

  /* End of MultiPortSwitch: '<S48>/EN_RDY_Switch_3' */

  /* Logic: '<S48>/Logical Operator3' */
  FOC_FCF_B->LogicalOperator3_c = ((!(FOC_FCF_B->EN_FLT_Switch_1 != 0.0F)) &&
    (!(FOC_FCF_B->EN_FLT_Switch_2 != 0.0F)) && (!(FOC_FCF_B->EN_FLT_Switch_3 !=
    0.0F)) && (!(FOC_FCF_B->EN_RDY_Switch_1 != 0.0F)) &&
    (!(FOC_FCF_B->EN_RDY_Switch_2 != 0.0F)) && (!(FOC_FCF_B->EN_RDY_Switch_3 !=
    0.0F)));

  /* Logic: '<S8>/Logical Operator3' incorporates:
   *  Constant: '<S1>/FOC_MANUAL_Error'
   */
  FOC_FCF_B->LogicalOperator3_pp = ((!(FOC_FCF_P.FOC_MANUAL_Error != 0.0F)) &&
    LogicalOperator2_a_tmp && (!FOC_FCF_B->Overspeed_Error) &&
    (!FOC_FCF_U->bus_SMF.Collective_Over_Temp_Error) &&
    (!(FOC_FCF_B->DataSourceSwitch != 0.0F)) && (!FOC_FCF_B->LogicalOperator3_c));

  /* Logic: '<S8>/Enable_PWM_' */
  FOC_FCF_B->Enable_PWM_ = (FOC_FCF_B->LogicalOperator3_pp &&
    FOC_FCF_U->bus_SMF.FOC_Enable_PWM);

  /* Logic: '<S8>/Logical Operator1' incorporates:
   *  Constant: '<S8>/FOC_Enable_PWM_Sys1'
   */
  FOC_FCF_B->LogicalOperator1_e = ((FOC_FCF_P.FOC_Enable_PWM_Sys1 != 0.0F) &&
    FOC_FCF_B->Enable_PWM_);

  /* Logic: '<S8>/Logical Operator2' incorporates:
   *  Constant: '<S8>/FOC_Enable_PWM_Sys2'
   */
  FOC_FCF_B->LogicalOperator2_f = ((FOC_FCF_P.FOC_Enable_PWM_Sys2 != 0.0F) &&
    FOC_FCF_B->Enable_PWM_);

  /* Logic: '<S8>/Logical Operator4' incorporates:
   *  Constant: '<S8>/FOC_Enable_PWM_Sys3'
   */
  FOC_FCF_B->LogicalOperator4_h = ((FOC_FCF_P.FOC_Enable_PWM_Sys3 != 0.0F) &&
    FOC_FCF_B->Enable_PWM_);

  /* SignalConversion generated from: '<S1>/Bus Creator' */
  FOC_FCF_B->FOC_Enable_PWM[0] = FOC_FCF_B->LogicalOperator1_e;
  FOC_FCF_B->FOC_Enable_PWM[1] = FOC_FCF_B->LogicalOperator2_f;
  FOC_FCF_B->FOC_Enable_PWM[2] = FOC_FCF_B->LogicalOperator4_h;

  /* Logic: '<S8>/Logical Operator6' */
  FOC_FCF_B->FCF_Error = !FOC_FCF_B->LogicalOperator3_pp;

  /* BusCreator: '<S1>/Bus Creator' incorporates:
   *  Outport: '<Root>/bus_FCF'
   */
  FOC_FCF_Y->bus_FCF.U_DC = FOC_FCF_B->U_DC_fcf;
  for (i = 0; i < 6; i++) {
    FOC_FCF_Y->bus_FCF.I_dq_Act[i] = FOC_FCF_B->I_dq_Act[i];
  }

  FOC_FCF_Y->bus_FCF.w_el = FOC_FCF_B->w_el;
  FOC_FCF_Y->bus_FCF.ModInd[0] = FOC_FCF_B->ModInd[0];
  FOC_FCF_Y->bus_FCF.FOC_Enable_PWM[0] = FOC_FCF_B->FOC_Enable_PWM[0];
  FOC_FCF_Y->bus_FCF.ModInd[1] = FOC_FCF_B->ModInd[1];
  FOC_FCF_Y->bus_FCF.FOC_Enable_PWM[1] = FOC_FCF_B->FOC_Enable_PWM[1];
  FOC_FCF_Y->bus_FCF.ModInd[2] = FOC_FCF_B->ModInd[2];
  FOC_FCF_Y->bus_FCF.FOC_Enable_PWM[2] = FOC_FCF_B->FOC_Enable_PWM[2];
  FOC_FCF_Y->bus_FCF.FCF_Error = FOC_FCF_B->FCF_Error;

  /* End of BusCreator: '<S1>/Bus Creator' */

  /* Switch: '<S37>/IntegStopSwitch2' */
  if (FOC_FCF_B->LogicalOperator1_h) {
    /* RelationalOperator: '<S36>/AntiWindupLE' incorporates:
     *  Constant: '<S36>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE_l = (FOC_FCF_B->ModInd[0] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S37>/IntegStopSwitch3' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1[0];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S37>/IntegStopSwitch3' */
      Gain_a = UnitDelay1_p;
    } else {
      /* Switch: '<S37>/IntegStopSwitch3' incorporates:
       *  Constant: '<S37>/Zero1'
       */
      Gain_a = FOC_FCF_P.Zero1_Value[0];
    }

    /* Switch: '<S37>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[0] = Gain_a;

    /* Sum: '<S37>/IntSum2' */
    FOC_FCF_B->IntSum2_j[0] = FOC_FCF_B->KPek1[0] + Gain_a;

    /* Gain: '<S37>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[0] = FOC_FCF_P.FOC_IntegDamp * Gain_a;

    /* Product: '<S36>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[0] = FOC_FCF_B->IdqErr[0] * UnitDelay1_p;

    /* Switch: '<S37>/IntegStopSwitch3' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1[1];
    if (FOC_FCF_B->Product1 > FOC_FCF_P.IntegStopSwitch3_Threshold) {
      /* Switch: '<S37>/IntegStopSwitch3' */
      Gain_a = UnitDelay1_p;
    } else {
      /* Switch: '<S37>/IntegStopSwitch3' incorporates:
       *  Constant: '<S37>/Zero1'
       */
      Gain_a = FOC_FCF_P.Zero1_Value[1];
    }

    /* Switch: '<S37>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_h[1] = Gain_a;

    /* Sum: '<S37>/IntSum2' */
    FOC_FCF_B->IntSum2_j[1] = FOC_FCF_B->KPek1[1] + Gain_a;

    /* Gain: '<S37>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_c[1] = FOC_FCF_P.FOC_IntegDamp * Gain_a;

    /* Product: '<S36>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_o[1] = FOC_FCF_B->IdqErr[1] * UnitDelay1_p;

    /* RelationalOperator: '<S39>/Compare' incorporates:
     *  Constant: '<S39>/Constant'
     */
    FOC_FCF_B->Compare_o = (uint8_T)(FOC_FCF_B->antiWindupProd_o[1] <
      FOC_FCF_P.AntiWindupGT_q_const);

    /* Logic: '<S36>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q_o = (FOC_FCF_B->AntiWindupLE_l ||
      (FOC_FCF_B->Compare_o != 0));

    /* RelationalOperator: '<S38>/Compare' incorporates:
     *  Constant: '<S38>/Constant'
     */
    FOC_FCF_B->Compare_f = (uint8_T)(FOC_FCF_B->antiWindupProd_o[0] <
      FOC_FCF_P.AntiWindupGT_d_const);

    /* Logic: '<S36>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d_e = ((FOC_FCF_B->Compare_f != 0) ||
      FOC_FCF_B->AntiWindupLE_l);

    /* Switch: '<S37>/IntegStopSwitch1' */
    LogicalOperator2_a_tmp = FOC_FCF_B->AntiWindupOR_d_e;
    tmp_0 = FOC_FCF_B->AntiWindupOR_q_o;
    if (LogicalOperator2_a_tmp) {
      UnitDelay1_p = FOC_FCF_B->IntSum2_j[0];

      /* Switch: '<S37>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = UnitDelay1_p;
    } else {
      UnitDelay1_p = FOC_FCF_B->FOC_IntegDamp_c[0];

      /* Switch: '<S37>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[0] = UnitDelay1_p;
    }

    /* Switch: '<S37>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[0] = UnitDelay1_p;

    /* Switch: '<S37>/IntegStopSwitch1' */
    if (tmp_0) {
      UnitDelay1_p = FOC_FCF_B->IntSum2_j[1];

      /* Switch: '<S37>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = UnitDelay1_p;
    } else {
      UnitDelay1_p = FOC_FCF_B->FOC_IntegDamp_c[1];

      /* Switch: '<S37>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_f[1] = UnitDelay1_p;
    }

    /* Switch: '<S37>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2[1] = UnitDelay1_p;
  } else {
    /* Switch: '<S37>/IntegStopSwitch2' incorporates:
     *  Constant: '<S37>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2[0] = FOC_FCF_P.Zero1_Value[0];
    FOC_FCF_B->IntegStopSwitch2[1] = FOC_FCF_P.Zero1_Value[1];
  }

  /* End of Switch: '<S37>/IntegStopSwitch2' */

  /* Gain: '<S30>/Gain1' */
  FOC_FCF_B->U_d1_CC = FOC_FCF_P.Gain1_Gain_cs * FOC_FCF_B->IntegEnaSwitch1[0];

  /* Gain: '<S30>/Gain2' */
  FOC_FCF_B->U_q1_CC = FOC_FCF_P.Gain2_Gain_f * FOC_FCF_B->IntegEnaSwitch1[1];

  /* Switch: '<S41>/IntegStopSwitch2' */
  if (FOC_FCF_B->LogicalOperator2_n) {
    /* RelationalOperator: '<S40>/AntiWindupLE' incorporates:
     *  Constant: '<S40>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE_f = (FOC_FCF_B->ModInd[1] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S41>/IntegStopSwitch3' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1_o[0];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S41>/IntegStopSwitch3' */
      Gain_a = UnitDelay1_p;
    } else {
      /* Switch: '<S41>/IntegStopSwitch3' incorporates:
       *  Constant: '<S41>/Zero1'
       */
      Gain_a = FOC_FCF_P.Zero1_Value_l[0];
    }

    /* Switch: '<S41>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_n[0] = Gain_a;

    /* Sum: '<S41>/IntSum2' */
    FOC_FCF_B->IntSum2_f[0] = FOC_FCF_B->KPek1_l[0] + Gain_a;

    /* Gain: '<S41>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_g[0] = FOC_FCF_P.FOC_IntegDamp * Gain_a;

    /* Product: '<S40>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_d[0] = FOC_FCF_B->IdqErr_l[0] * UnitDelay1_p;

    /* Switch: '<S41>/IntegStopSwitch3' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1_o[1];
    if (FOC_FCF_B->Product1_k > FOC_FCF_P.IntegStopSwitch3_Threshold_a) {
      /* Switch: '<S41>/IntegStopSwitch3' */
      Gain_a = UnitDelay1_p;
    } else {
      /* Switch: '<S41>/IntegStopSwitch3' incorporates:
       *  Constant: '<S41>/Zero1'
       */
      Gain_a = FOC_FCF_P.Zero1_Value_l[1];
    }

    /* Switch: '<S41>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3_n[1] = Gain_a;

    /* Sum: '<S41>/IntSum2' */
    FOC_FCF_B->IntSum2_f[1] = FOC_FCF_B->KPek1_l[1] + Gain_a;

    /* Gain: '<S41>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp_g[1] = FOC_FCF_P.FOC_IntegDamp * Gain_a;

    /* Product: '<S40>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd_d[1] = FOC_FCF_B->IdqErr_l[1] * UnitDelay1_p;

    /* RelationalOperator: '<S43>/Compare' incorporates:
     *  Constant: '<S43>/Constant'
     */
    FOC_FCF_B->Compare_g = (uint8_T)(FOC_FCF_B->antiWindupProd_d[1] <
      FOC_FCF_P.AntiWindupGT_q_const_h);

    /* Logic: '<S40>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q_l = (FOC_FCF_B->AntiWindupLE_f ||
      (FOC_FCF_B->Compare_g != 0));

    /* RelationalOperator: '<S42>/Compare' incorporates:
     *  Constant: '<S42>/Constant'
     */
    FOC_FCF_B->Compare_i = (uint8_T)(FOC_FCF_B->antiWindupProd_d[0] <
      FOC_FCF_P.AntiWindupGT_d_const_n);

    /* Logic: '<S40>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d_m = ((FOC_FCF_B->Compare_i != 0) ||
      FOC_FCF_B->AntiWindupLE_f);

    /* Switch: '<S41>/IntegStopSwitch1' */
    LogicalOperator2_a_tmp = FOC_FCF_B->AntiWindupOR_d_m;
    tmp_0 = FOC_FCF_B->AntiWindupOR_q_l;
    if (LogicalOperator2_a_tmp) {
      UnitDelay1_p = FOC_FCF_B->IntSum2_f[0];

      /* Switch: '<S41>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[0] = UnitDelay1_p;
    } else {
      UnitDelay1_p = FOC_FCF_B->FOC_IntegDamp_g[0];

      /* Switch: '<S41>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[0] = UnitDelay1_p;
    }

    /* Switch: '<S41>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[0] = UnitDelay1_p;

    /* Switch: '<S41>/IntegStopSwitch1' */
    if (tmp_0) {
      UnitDelay1_p = FOC_FCF_B->IntSum2_f[1];

      /* Switch: '<S41>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[1] = UnitDelay1_p;
    } else {
      UnitDelay1_p = FOC_FCF_B->FOC_IntegDamp_g[1];

      /* Switch: '<S41>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1_g[1] = UnitDelay1_p;
    }

    /* Switch: '<S41>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_o[1] = UnitDelay1_p;
  } else {
    /* Switch: '<S41>/IntegStopSwitch2' incorporates:
     *  Constant: '<S41>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2_o[0] = FOC_FCF_P.Zero1_Value_l[0];
    FOC_FCF_B->IntegStopSwitch2_o[1] = FOC_FCF_P.Zero1_Value_l[1];
  }

  /* End of Switch: '<S41>/IntegStopSwitch2' */

  /* Switch: '<S45>/IntegStopSwitch2' */
  if (FOC_FCF_B->LogicalOperator3_e) {
    /* RelationalOperator: '<S44>/AntiWindupLE' incorporates:
     *  Constant: '<S44>/FOC_MaxModInd'
     */
    FOC_FCF_B->AntiWindupLE = (FOC_FCF_B->ModInd[2] <= FOC_FCF_P.FOC_MaxModInd);

    /* Switch: '<S45>/IntegStopSwitch3' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1_d[0];
    if (FOC_FCF_B->Product1_b > FOC_FCF_P.IntegStopSwitch3_Threshold_ad) {
      /* Switch: '<S45>/IntegStopSwitch3' */
      Gain_a = UnitDelay1_p;
    } else {
      /* Switch: '<S45>/IntegStopSwitch3' incorporates:
       *  Constant: '<S45>/Zero1'
       */
      Gain_a = FOC_FCF_P.Zero1_Value_o[0];
    }

    /* Switch: '<S45>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[0] = Gain_a;

    /* Sum: '<S45>/IntSum2' */
    FOC_FCF_B->IntSum2[0] = FOC_FCF_B->KPek1_h[0] + Gain_a;

    /* Gain: '<S45>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[0] = FOC_FCF_P.FOC_IntegDamp * Gain_a;

    /* Product: '<S44>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[0] = FOC_FCF_B->IdqErr_e[0] * UnitDelay1_p;

    /* Switch: '<S45>/IntegStopSwitch3' */
    UnitDelay1_p = FOC_FCF_B->IntegDelay1_d[1];
    if (FOC_FCF_B->Product1_b > FOC_FCF_P.IntegStopSwitch3_Threshold_ad) {
      /* Switch: '<S45>/IntegStopSwitch3' */
      Gain_a = UnitDelay1_p;
    } else {
      /* Switch: '<S45>/IntegStopSwitch3' incorporates:
       *  Constant: '<S45>/Zero1'
       */
      Gain_a = FOC_FCF_P.Zero1_Value_o[1];
    }

    /* Switch: '<S45>/IntegStopSwitch3' */
    FOC_FCF_B->IntegStopSwitch3[1] = Gain_a;

    /* Sum: '<S45>/IntSum2' */
    FOC_FCF_B->IntSum2[1] = FOC_FCF_B->KPek1_h[1] + Gain_a;

    /* Gain: '<S45>/FOC_IntegDamp' */
    FOC_FCF_B->FOC_IntegDamp[1] = FOC_FCF_P.FOC_IntegDamp * Gain_a;

    /* Product: '<S44>/antiWindupProd' */
    FOC_FCF_B->antiWindupProd[1] = FOC_FCF_B->IdqErr_e[1] * UnitDelay1_p;

    /* RelationalOperator: '<S47>/Compare' incorporates:
     *  Constant: '<S47>/Constant'
     */
    FOC_FCF_B->Compare = (uint8_T)(FOC_FCF_B->antiWindupProd[1] <
      FOC_FCF_P.AntiWindupGT_q_const_l);

    /* Logic: '<S44>/AntiWindupOR_q' */
    FOC_FCF_B->AntiWindupOR_q = (FOC_FCF_B->AntiWindupLE || (FOC_FCF_B->Compare
      != 0));

    /* RelationalOperator: '<S46>/Compare' incorporates:
     *  Constant: '<S46>/Constant'
     */
    FOC_FCF_B->Compare_k = (uint8_T)(FOC_FCF_B->antiWindupProd[0] <
      FOC_FCF_P.AntiWindupGT_d_const_f);

    /* Logic: '<S44>/AntiWindupOR_d' */
    FOC_FCF_B->AntiWindupOR_d = ((FOC_FCF_B->Compare_k != 0) ||
      FOC_FCF_B->AntiWindupLE);

    /* Switch: '<S45>/IntegStopSwitch1' */
    LogicalOperator2_a_tmp = FOC_FCF_B->AntiWindupOR_d;
    tmp_0 = FOC_FCF_B->AntiWindupOR_q;
    if (LogicalOperator2_a_tmp) {
      UnitDelay1_p = FOC_FCF_B->IntSum2[0];

      /* Switch: '<S45>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = UnitDelay1_p;
    } else {
      UnitDelay1_p = FOC_FCF_B->FOC_IntegDamp[0];

      /* Switch: '<S45>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[0] = UnitDelay1_p;
    }

    /* Switch: '<S45>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_h[0] = UnitDelay1_p;

    /* Switch: '<S45>/IntegStopSwitch1' */
    if (tmp_0) {
      UnitDelay1_p = FOC_FCF_B->IntSum2[1];

      /* Switch: '<S45>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = UnitDelay1_p;
    } else {
      UnitDelay1_p = FOC_FCF_B->FOC_IntegDamp[1];

      /* Switch: '<S45>/IntegStopSwitch1' */
      FOC_FCF_B->IntegStopSwitch1[1] = UnitDelay1_p;
    }

    /* Switch: '<S45>/IntegStopSwitch2' */
    FOC_FCF_B->IntegStopSwitch2_h[1] = UnitDelay1_p;
  } else {
    /* Switch: '<S45>/IntegStopSwitch2' incorporates:
     *  Constant: '<S45>/Zero1'
     */
    FOC_FCF_B->IntegStopSwitch2_h[0] = FOC_FCF_P.Zero1_Value_o[0];
    FOC_FCF_B->IntegStopSwitch2_h[1] = FOC_FCF_P.Zero1_Value_o[1];
  }

  /* End of Switch: '<S45>/IntegStopSwitch2' */

  /* Abs: '<S61>/Abs' */
  FOC_FCF_B->Abs_e = fabsf(FOC_FCF_B->Add_mp);

  /* Switch: '<S61>/Switch' */
  if (FOC_FCF_B->Abs_e >= FOC_FCF_P.Switch_Threshold) {
    /* Signum: '<S61>/Sign' */
    UnitDelay1_p = FOC_FCF_B->Product_h;
    if (rtIsNaNF(UnitDelay1_p)) {
      /* Signum: '<S61>/Sign' */
      FOC_FCF_B->Sign_d = (rtNaNF);
    } else if (UnitDelay1_p < 0.0F) {
      /* Signum: '<S61>/Sign' */
      FOC_FCF_B->Sign_d = -1.0F;
    } else {
      /* Signum: '<S61>/Sign' */
      FOC_FCF_B->Sign_d = (real32_T)(UnitDelay1_p > 0.0F);
    }

    /* End of Signum: '<S61>/Sign' */

    /* Gain: '<S61>/Gain1' */
    FOC_FCF_B->Gain1_j = FOC_FCF_P.Gain1_Gain * FOC_FCF_B->Sign_d;

    /* Switch: '<S61>/Switch' */
    FOC_FCF_B->Switch_d = FOC_FCF_B->Gain1_j;
  } else {
    /* Switch: '<S61>/Switch' incorporates:
     *  Constant: '<S61>/Constant1'
     */
    FOC_FCF_B->Switch_d = FOC_FCF_P.Constant1_Value_c;
  }

  /* End of Switch: '<S61>/Switch' */

  /* Sum: '<S61>/Add1' */
  FOC_FCF_B->Add1 = FOC_FCF_B->Add_mp - FOC_FCF_B->Switch_d;
  for (i = 0; i < 9; i++) {
    /* RelationalOperator: '<S65>/Compare' incorporates:
     *  Constant: '<S65>/Constant'
     */
    FOC_FCF_B->Compare_gv[i] = (FOC_FCF_B->Abs[i] >
      FOC_FCF_P.FOC_LIMIT_Overcurrent_I_uvw);
  }

  /* Memory: '<S70>/Memory' */
  FOC_FCF_B->Memory_f = FOC_FCF_DW->Memory_PreviousInput_n;

  /* CombinatorialLogic: '<S70>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[0];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_f;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_g[0U] = FOC_FCF_P.Logic_table_l5[(uint32_T)i];
  FOC_FCF_B->Logic_g[1U] = FOC_FCF_P.Logic_table_l5[(uint32_T)i + 8U];

  /* Memory: '<S71>/Memory' */
  FOC_FCF_B->Memory_b = FOC_FCF_DW->Memory_PreviousInput_o;

  /* CombinatorialLogic: '<S71>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[1];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_b;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_i[0U] = FOC_FCF_P.Logic_table_p[(uint32_T)i];
  FOC_FCF_B->Logic_i[1U] = FOC_FCF_P.Logic_table_p[(uint32_T)i + 8U];

  /* Memory: '<S72>/Memory' */
  FOC_FCF_B->Memory_ok = FOC_FCF_DW->Memory_PreviousInput_nm;

  /* CombinatorialLogic: '<S72>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[2];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_ok;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_b[0U] = FOC_FCF_P.Logic_table_j[(uint32_T)i];
  FOC_FCF_B->Logic_b[1U] = FOC_FCF_P.Logic_table_j[(uint32_T)i + 8U];

  /* Memory: '<S73>/Memory' */
  FOC_FCF_B->Memory_c = FOC_FCF_DW->Memory_PreviousInput_ef;

  /* CombinatorialLogic: '<S73>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[3];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_c;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_p[0U] = FOC_FCF_P.Logic_table_o1[(uint32_T)i];
  FOC_FCF_B->Logic_p[1U] = FOC_FCF_P.Logic_table_o1[(uint32_T)i + 8U];

  /* Memory: '<S74>/Memory' */
  FOC_FCF_B->Memory_g = FOC_FCF_DW->Memory_PreviousInput_c;

  /* CombinatorialLogic: '<S74>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[4];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_g;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_d[0U] = FOC_FCF_P.Logic_table_i[(uint32_T)i];
  FOC_FCF_B->Logic_d[1U] = FOC_FCF_P.Logic_table_i[(uint32_T)i + 8U];

  /* Memory: '<S75>/Memory' */
  FOC_FCF_B->Memory_j = FOC_FCF_DW->Memory_PreviousInput_d;

  /* CombinatorialLogic: '<S75>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[5];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_j;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_ev[0U] = FOC_FCF_P.Logic_table_c[(uint32_T)i];
  FOC_FCF_B->Logic_ev[1U] = FOC_FCF_P.Logic_table_c[(uint32_T)i + 8U];

  /* Memory: '<S76>/Memory' */
  FOC_FCF_B->Memory_nb = FOC_FCF_DW->Memory_PreviousInput_os;

  /* CombinatorialLogic: '<S76>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[6];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_nb;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_bw[0U] = FOC_FCF_P.Logic_table_ij[(uint32_T)i];
  FOC_FCF_B->Logic_bw[1U] = FOC_FCF_P.Logic_table_ij[(uint32_T)i + 8U];

  /* Memory: '<S77>/Memory' */
  FOC_FCF_B->Memory_kp = FOC_FCF_DW->Memory_PreviousInput_f;

  /* CombinatorialLogic: '<S77>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[7];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_kp;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_ag[0U] = FOC_FCF_P.Logic_table_pd[(uint32_T)i];
  FOC_FCF_B->Logic_ag[1U] = FOC_FCF_P.Logic_table_pd[(uint32_T)i + 8U];

  /* Memory: '<S78>/Memory' */
  FOC_FCF_B->Memory_p = FOC_FCF_DW->Memory_PreviousInput_b;

  /* CombinatorialLogic: '<S78>/Logic' */
  tmp_0 = FOC_FCF_B->Compare_gv[8];
  i = tmp_0;
  tmp_0 = FOC_FCF_B->Selectphicalc2_m;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  tmp_0 = FOC_FCF_B->Memory_p;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  FOC_FCF_B->Logic_f[0U] = FOC_FCF_P.Logic_table_a[(uint32_T)i];
  FOC_FCF_B->Logic_f[1U] = FOC_FCF_P.Logic_table_a[(uint32_T)i + 8U];

  /* Abs: '<S13>/Abs' */
  FOC_FCF_B->Abs_b = fabsf(FOC_FCF_B->Add_m);

  /* Switch: '<S13>/Switch' */
  if (FOC_FCF_B->Abs_b >= FOC_FCF_P.Switch_Threshold_b) {
    /* Signum: '<S13>/Sign' */
    UnitDelay1_p = FOC_FCF_B->Product_e;
    if (rtIsNaNF(UnitDelay1_p)) {
      /* Signum: '<S13>/Sign' */
      FOC_FCF_B->Sign_n = (rtNaNF);
    } else if (UnitDelay1_p < 0.0F) {
      /* Signum: '<S13>/Sign' */
      FOC_FCF_B->Sign_n = -1.0F;
    } else {
      /* Signum: '<S13>/Sign' */
      FOC_FCF_B->Sign_n = (real32_T)(UnitDelay1_p > 0.0F);
    }

    /* End of Signum: '<S13>/Sign' */

    /* Gain: '<S13>/Gain1' */
    FOC_FCF_B->Gain1_h = FOC_FCF_P.Gain1_Gain_c * FOC_FCF_B->Sign_n;

    /* Switch: '<S13>/Switch' */
    FOC_FCF_B->Switch_l = FOC_FCF_B->Gain1_h;
  } else {
    /* Switch: '<S13>/Switch' incorporates:
     *  Constant: '<S13>/Constant1'
     */
    FOC_FCF_B->Switch_l = FOC_FCF_P.Constant1_Value_k;
  }

  /* End of Switch: '<S13>/Switch' */

  /* Sum: '<S13>/Add1' */
  FOC_FCF_B->Add1_j = FOC_FCF_B->Add_m - FOC_FCF_B->Switch_l;

  /* Abs: '<S91>/Abs' */
  FOC_FCF_B->Abs_f = fabsf(FOC_FCF_B->Add);

  /* Switch: '<S91>/Switch' */
  if (FOC_FCF_B->Abs_f >= FOC_FCF_P.Switch_Threshold_c) {
    /* Signum: '<S91>/Sign' */
    UnitDelay1_p = FOC_FCF_B->Product;
    if (rtIsNaNF(UnitDelay1_p)) {
      /* Signum: '<S91>/Sign' */
      FOC_FCF_B->Sign = (rtNaNF);
    } else if (UnitDelay1_p < 0.0F) {
      /* Signum: '<S91>/Sign' */
      FOC_FCF_B->Sign = -1.0F;
    } else {
      /* Signum: '<S91>/Sign' */
      FOC_FCF_B->Sign = (real32_T)(UnitDelay1_p > 0.0F);
    }

    /* End of Signum: '<S91>/Sign' */

    /* Gain: '<S91>/Gain1' */
    FOC_FCF_B->Gain1_o = FOC_FCF_P.Gain1_Gain_a * FOC_FCF_B->Sign;

    /* Switch: '<S91>/Switch' */
    FOC_FCF_B->Switch_n = FOC_FCF_B->Gain1_o;
  } else {
    /* Switch: '<S91>/Switch' incorporates:
     *  Constant: '<S91>/Constant1'
     */
    FOC_FCF_B->Switch_n = FOC_FCF_P.Constant1_Value_e;
  }

  /* End of Switch: '<S91>/Switch' */

  /* Sum: '<S91>/Add1' */
  FOC_FCF_B->Add1_c = FOC_FCF_B->Add - FOC_FCF_B->Switch_n;

  /* Gain: '<S15>/Gain' */
  FOC_FCF_B->U_d1 = FOC_FCF_P.Gain_Gain_jm * FOC_FCF_B->SelectControlMode[0];

  /* Gain: '<S15>/Gain1' */
  FOC_FCF_B->U_q1 = FOC_FCF_P.Gain1_Gain_e * FOC_FCF_B->SelectControlMode[1];

  /* Gain: '<S15>/Gain2' */
  FOC_FCF_B->U_alpha1 = FOC_FCF_P.Gain2_Gain_fg * FOC_FCF_B->Product_c0[0];

  /* Gain: '<S15>/Gain3' */
  FOC_FCF_B->U_beta1 = FOC_FCF_P.Gain3_Gain * FOC_FCF_B->Product_c0[1];

  /* Gain: '<S96>/DutyCycle_u1' */
  FOC_FCF_B->DutyCycle_u1 = FOC_FCF_P.DutyCycle_u1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[0];

  /* Gain: '<S96>/DutyCycle_u2' */
  FOC_FCF_B->DutyCycle_u2 = FOC_FCF_P.DutyCycle_u2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[0];

  /* Gain: '<S96>/DutyCycle_u3' */
  FOC_FCF_B->DutyCycle_u3 = FOC_FCF_P.DutyCycle_u3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[0];

  /* Gain: '<S96>/DutyCycle_v1' */
  FOC_FCF_B->DutyCycle_v1 = FOC_FCF_P.DutyCycle_v1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[1];

  /* Gain: '<S96>/DutyCycle_v2' */
  FOC_FCF_B->DutyCycle_v2 = FOC_FCF_P.DutyCycle_v2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[1];

  /* Gain: '<S96>/DutyCycle_v3' */
  FOC_FCF_B->DutyCycle_v3 = FOC_FCF_P.DutyCycle_v3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[1];

  /* Gain: '<S96>/DutyCycle_w1' */
  FOC_FCF_B->DutyCycle_w1 = FOC_FCF_P.DutyCycle_w1_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_1[2];

  /* Gain: '<S96>/DutyCycle_w2' */
  FOC_FCF_B->DutyCycle_w2 = FOC_FCF_P.DutyCycle_w2_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_2[2];

  /* Gain: '<S96>/DutyCycle_w3' */
  FOC_FCF_B->DutyCycle_w3 = FOC_FCF_P.DutyCycle_w3_Gain *
    FOC_FCF_B->Select_GateDriver_Assignment_3[2];

  /* UnitDelay: '<S1>/FCF_Cnt' */
  FOC_FCF_B->FCF_Cnt = FOC_FCF_DW->FCF_Cnt_DSTATE;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<S1>/Counter_Start'
   */
  FOC_FCF_B->Sum_o = FOC_FCF_P.Counter_Start_Value + FOC_FCF_B->FCF_Cnt;

  /* Update for UnitDelay: '<S82>/Delay Input1'
   *
   * Block description for '<S82>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE = FOC_FCF_B->Compare_d;

  /* Update for Memory: '<S83>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput = FOC_FCF_B->Logic[0];

  /* Update for UnitDelay: '<S81>/Delay Input1'
   *
   * Block description for '<S81>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE_g = FOC_FCF_B->Compare_iz;

  /* Update for Memory: '<S84>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_e = FOC_FCF_B->Logic_c[0];

  /* Update for UnitDelay: '<S66>/Delay Input1'
   *
   * Block description for '<S66>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE_l = FOC_FCF_B->Compare_in;

  /* Update for Memory: '<S68>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_j = FOC_FCF_B->Logic_a[0];

  /* Update for DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn' */
  UnitDelay1_p = FOC_FCF_B->f_2_w_el;
  UnitDelay1_p -= FOC_FCF_P.DiscreteTransferFcn_DenCoef[1] *
    FOC_FCF_DW->DiscreteTransferFcn_states;
  UnitDelay1_p /= FOC_FCF_P.DiscreteTransferFcn_DenCoef[0];
  FOC_FCF_DW->DiscreteTransferFcn_states = UnitDelay1_p;

  /* Update for UnitDelay: '<S91>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_B->Add1_c;

  /* Update for UnitDelay: '<S27>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_B->Sum2_e;

  /* Update for UnitDelay: '<S26>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_B->Sum3;

  /* Update for UnitDelay: '<S24>/Unit Delay3' */
  FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_B->Sum6;

  /* Update for UnitDelay: '<S13>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_B->Add1_j;

  /* Update for UnitDelay: '<S61>/Unit Delay' */
  FOC_FCF_DW->UnitDelay_DSTATE_f = FOC_FCF_B->Add1;

  /* Update for UnitDelay: '<S37>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_B->IntegStopSwitch2[0];

  /* Update for UnitDelay: '<S41>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[0] = FOC_FCF_B->IntegStopSwitch2_o[0];

  /* Update for UnitDelay: '<S45>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_h[0] = FOC_FCF_B->IntegStopSwitch2_h[0];

  /* Update for UnitDelay: '<S37>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_B->IntegStopSwitch2[1];

  /* Update for UnitDelay: '<S41>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_p[1] = FOC_FCF_B->IntegStopSwitch2_o[1];

  /* Update for UnitDelay: '<S45>/IntegDelay1' */
  FOC_FCF_DW->IntegDelay1_DSTATE_h[1] = FOC_FCF_B->IntegStopSwitch2_h[1];

  /* Update for UnitDelay: '<S28>/Unit Delay1' */
  FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_B->Sum2_j;

  /* Update for DiscreteFir: '<S33>/Discrete FIR Filter 20th order' */
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

  /* End of Update for DiscreteFir: '<S33>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S34>/Discrete FIR Filter 20th order' */
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

  /* End of Update for DiscreteFir: '<S34>/Discrete FIR Filter 20th order' */

  /* Update for DiscreteFir: '<S35>/Discrete FIR Filter 20th order' */
  /* Update circular buffer index */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c--;
  if (FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c < 0) {
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c = 18;
  }

  /* Update circular buffer */
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[0];
  FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p
    [FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c + 19] =
    FOC_FCF_B->TmpSignalConversionAtDiscrete_c[1];

  /* End of Update for DiscreteFir: '<S35>/Discrete FIR Filter 20th order' */

  /* Update for UnitDelay: '<S88>/Delay Input1'
   *
   * Block description for '<S88>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_FCF_DW->DelayInput1_DSTATE_e = FOC_FCF_B->Compare_gt;

  /* Update for Memory: '<S89>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_i = FOC_FCF_B->Logic_e[0];

  /* Update for Memory: '<S70>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_n = FOC_FCF_B->Logic_g[0];

  /* Update for Memory: '<S71>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_o = FOC_FCF_B->Logic_i[0];

  /* Update for Memory: '<S72>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_nm = FOC_FCF_B->Logic_b[0];

  /* Update for Memory: '<S73>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_ef = FOC_FCF_B->Logic_p[0];

  /* Update for Memory: '<S74>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_c = FOC_FCF_B->Logic_d[0];

  /* Update for Memory: '<S75>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_d = FOC_FCF_B->Logic_ev[0];

  /* Update for Memory: '<S76>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_os = FOC_FCF_B->Logic_bw[0];

  /* Update for Memory: '<S77>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_f = FOC_FCF_B->Logic_ag[0];

  /* Update for Memory: '<S78>/Memory' */
  FOC_FCF_DW->Memory_PreviousInput_b = FOC_FCF_B->Logic_f[0];

  /* Update for UnitDelay: '<S1>/FCF_Cnt' */
  FOC_FCF_DW->FCF_Cnt_DSTATE = FOC_FCF_B->Sum_o;

  /* End of Outputs for SubSystem: '<Root>/FOC_FCF' */
}

/* Model initialize function */
void FOC_FCF_initialize(RT_MODEL_FOC_FCF_T *const FOC_FCF_M)
{
  B_FOC_FCF_T *FOC_FCF_B = FOC_FCF_M->blockIO;
  DW_FOC_FCF_T *FOC_FCF_DW = FOC_FCF_M->dwork;
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
  FOC_FCF_Y->bus_FCF = FOC_FCF_rtZbus_FCF_t;

  {
    int32_T i;

    /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_FCF' */
    /* InitializeConditions for UnitDelay: '<S82>/Delay Input1'
     *
     * Block description for '<S82>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE = FOC_FCF_P.DetectRisePositive1_vinit;

    /* InitializeConditions for Memory: '<S83>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput = FOC_FCF_P.SRFlipFlop_initial_condition;

    /* InitializeConditions for UnitDelay: '<S81>/Delay Input1'
     *
     * Block description for '<S81>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE_g = FOC_FCF_P.DetectRisePositive_vinit;

    /* InitializeConditions for Memory: '<S84>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_e = FOC_FCF_P.SRFlipFlop1_initial_condition;

    /* InitializeConditions for UnitDelay: '<S66>/Delay Input1'
     *
     * Block description for '<S66>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE_l = FOC_FCF_P.DetectRisePositive_vinit_g;

    /* InitializeConditions for Memory: '<S68>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_j =
      FOC_FCF_P.SRFlipFlop_initial_condition_d;

    /* InitializeConditions for DiscreteTransferFcn: '<S14>/Discrete Transfer Fcn' */
    FOC_FCF_DW->DiscreteTransferFcn_states =
      FOC_FCF_P.DiscreteTransferFcn_InitialStat;

    /* InitializeConditions for UnitDelay: '<S91>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE = FOC_FCF_P.UnitDelay_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S27>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE = FOC_FCF_P.FOC_AngleObs_w_InitVal;

    /* InitializeConditions for UnitDelay: '<S26>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_h = FOC_FCF_P.UnitDelay_InitialCondition_b;

    /* InitializeConditions for UnitDelay: '<S24>/Unit Delay3' */
    FOC_FCF_DW->UnitDelay3_DSTATE = FOC_FCF_P.UnitDelay3_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S13>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_p = FOC_FCF_P.UnitDelay_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S61>/Unit Delay' */
    FOC_FCF_DW->UnitDelay_DSTATE_f = FOC_FCF_P.UnitDelay_InitialCondition_d;

    /* InitializeConditions for UnitDelay: '<S37>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[0] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S41>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[0] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S45>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_h[0] =
      FOC_FCF_P.IntegDelay1_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S37>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE[1] = FOC_FCF_P.IntegDelay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S41>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_p[1] =
      FOC_FCF_P.IntegDelay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S45>/IntegDelay1' */
    FOC_FCF_DW->IntegDelay1_DSTATE_h[1] =
      FOC_FCF_P.IntegDelay1_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S28>/Unit Delay1' */
    FOC_FCF_DW->UnitDelay1_DSTATE_i = FOC_FCF_P.UnitDelay1_InitialCondition;

    /* InitializeConditions for DiscreteFir: '<S33>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_circ = 0;

    /* InitializeConditions for DiscreteFir: '<S34>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_m = 0;

    /* InitializeConditions for DiscreteFir: '<S35>/Discrete FIR Filter 20th order' */
    FOC_FCF_DW->DiscreteFIRFilter20thorder_ci_c = 0;
    for (i = 0; i < 38; i++) {
      /* InitializeConditions for DiscreteFir: '<S33>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_stat[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_Init;

      /* InitializeConditions for DiscreteFir: '<S34>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_st_g[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_In_k;

      /* InitializeConditions for DiscreteFir: '<S35>/Discrete FIR Filter 20th order' */
      FOC_FCF_DW->DiscreteFIRFilter20thorder_st_p[i] =
        FOC_FCF_P.DiscreteFIRFilter20thorder_In_n;
    }

    /* InitializeConditions for UnitDelay: '<S88>/Delay Input1'
     *
     * Block description for '<S88>/Delay Input1':
     *
     *  Store in Global RAM
     */
    FOC_FCF_DW->DelayInput1_DSTATE_e = FOC_FCF_P.DetectRisePositive_vinit_f;

    /* InitializeConditions for Memory: '<S89>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_i =
      FOC_FCF_P.SRFlipFlop_initial_condition_k;

    /* InitializeConditions for Memory: '<S70>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_n =
      FOC_FCF_P.OverTemp_Latching_1_initial_con;

    /* InitializeConditions for Memory: '<S71>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_o =
      FOC_FCF_P.OverTemp_Latching_2_initial_con;

    /* InitializeConditions for Memory: '<S72>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_nm =
      FOC_FCF_P.OverTemp_Latching_3_initial_con;

    /* InitializeConditions for Memory: '<S73>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_ef =
      FOC_FCF_P.OverTemp_Latching_4_initial_con;

    /* InitializeConditions for Memory: '<S74>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_c =
      FOC_FCF_P.OverTemp_Latching_5_initial_con;

    /* InitializeConditions for Memory: '<S75>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_d =
      FOC_FCF_P.OverTemp_Latching_6_initial_con;

    /* InitializeConditions for Memory: '<S76>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_os =
      FOC_FCF_P.OverTemp_Latching_7_initial_con;

    /* InitializeConditions for Memory: '<S77>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_f =
      FOC_FCF_P.OverTemp_Latching_8_initial_con;

    /* InitializeConditions for Memory: '<S78>/Memory' */
    FOC_FCF_DW->Memory_PreviousInput_b =
      FOC_FCF_P.OverTemp_Latching_9_initial_con;

    /* InitializeConditions for UnitDelay: '<S1>/FCF_Cnt' */
    FOC_FCF_DW->FCF_Cnt_DSTATE = FOC_FCF_P.FCF_Cnt_InitialCondition;

    /* SystemInitialize for Enabled SubSystem: '<S20>/Current_Sensor_Calibration' */
    for (i = 0; i < 9; i++) {
      /* InitializeConditions for UnitDelay: '<S23>/Unit Delay1' */
      FOC_FCF_DW->UnitDelay1_DSTATE_c[i] = FOC_FCF_P.FOC_AngleObs_w_InitVal;

      /* SystemInitialize for UnitDelay: '<S23>/Unit Delay1' incorporates:
       *  Outport: '<S21>/cal_out'
       */
      FOC_FCF_B->UnitDelay1_p[i] = FOC_FCF_P.cal_out_Y0;
    }

    /* End of SystemInitialize for SubSystem: '<S20>/Current_Sensor_Calibration' */
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
