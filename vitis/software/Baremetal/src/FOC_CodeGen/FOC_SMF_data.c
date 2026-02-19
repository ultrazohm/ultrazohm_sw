/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SMF_data.c
 *
 * Code generated for Simulink model 'FOC_SMF'.
 *
 * Model version                  : 5.64
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Feb 19 10:18:36 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_SMF.h"

/* Block parameters (default storage) */
P_FOC_SMF_T FOC_SMF_P = {
  /* Variable: FOC_RESET_OT_Error
   * Referenced by: '<S5>/Reset_OT_Error'
   */
  0.0,

  /* Variable: enumState_CTRL_RE_INIT
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  5.0,

  /* Variable: FOC_MANUAL_State_Request
   * Referenced by: '<S1>/MANUAL_StateReq'
   */
  20.0F,

  /* Variable: FOC_MANUAL_Torque_Request
   * Referenced by: '<S1>/Constant'
   */
  0.0F,

  /* Variable: LIMIT_EMotor_Over_Temp
   * Referenced by: '<S7>/Constant'
   */
  130.0F,

  /* Variable: LIMIT_EMotor_Warn_Temp
   * Referenced by: '<S5>/LIMIT_EMotor_Warn_Temp'
   */
  110.0F,

  /* Variable: LIMIT_Inverter_Over_Temp
   * Referenced by: '<S6>/Constant'
   */
  130.0F,

  /* Variable: LIMIT_Inverter_Warn_Temp
   * Referenced by: '<S5>/LIMIT_WARN_Inverter_Warn_Temp'
   */
  110.0F,

  /* Variable: SPEED_CTRL_MANUAL_n_RPM
   * Referenced by: '<S1>/OmegaRot2'
   */
  0.0F,

  /* Variable: enumState_CTRL_IDLE
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  20.0F,

  /* Variable: enumState_CTRL_INIT
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  10.0F,

  /* Variable: enumState_ERROR_MODE
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  128.0F,

  /* Variable: enumState_FOC_IDLE
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  41.0F,

  /* Variable: enumState_FOC_OFF
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  49.0F,

  /* Variable: enumState_FOC_SPEED
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  46.0F,

  /* Variable: enumState_FOC_STANDBY
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  42.0F,

  /* Variable: enumState_FOC_TORQUE
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  43.0F,

  /* Variable: enumState_RUN_MODE
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  40.0F,

  /* Variable: enumState_SPEED_MODE
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  42.0F,

  /* Variable: enumState_SYS_INIT
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  2.0F,

  /* Variable: enumState_TORQUE_MODE
   * Referenced by: '<S1>/FOC_Statemachine'
   */
  41.0F,

  /* Variable: FOC_MANUAL_KL15_PG
   * Referenced by: '<S1>/FOC_MANUAL_KL15_PG'
   */
  true,

  /* Variable: SELECT_DataSource
   * Referenced by: '<S1>/SELECT_DataSource'
   */
  1U,

  /* Variable: SELECT_KL15_PG
   * Referenced by: '<S1>/SELECT_KL15_PG'
   */
  1U,

  /* Mask Parameter: OverTemp_Latching_1_initial_con
   * Referenced by: '<S12>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_2_initial_con
   * Referenced by: '<S13>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_3_initial_con
   * Referenced by: '<S14>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_4_initial_con
   * Referenced by: '<S15>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_5_initial_con
   * Referenced by: '<S16>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_6_initial_con
   * Referenced by: '<S17>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_1_initial_c_c
   * Referenced by: '<S18>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_2_initial_c_i
   * Referenced by: '<S19>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_3_initial_c_j
   * Referenced by: '<S20>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_4_initial_c_e
   * Referenced by: '<S21>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_5_initial_c_l
   * Referenced by: '<S22>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_6_initial_c_g
   * Referenced by: '<S23>/Memory'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit
   * Referenced by: '<S8>/Delay Input1'
   */
  false,

  /* Computed Parameter: LIMIT_EMotor_Warn_Temp_OffVal
   * Referenced by: '<S5>/LIMIT_EMotor_Warn_Temp'
   */
  108.0F,

  /* Computed Parameter: LIMIT_EMotor_Warn_Temp_YOn
   * Referenced by: '<S5>/LIMIT_EMotor_Warn_Temp'
   */
  1.0F,

  /* Computed Parameter: LIMIT_EMotor_Warn_Temp_YOff
   * Referenced by: '<S5>/LIMIT_EMotor_Warn_Temp'
   */
  0.0F,

  /* Computed Parameter: LIMIT_WARN_Inverter_Warn_Temp_O
   * Referenced by: '<S5>/LIMIT_WARN_Inverter_Warn_Temp'
   */
  108.0F,

  /* Computed Parameter: LIMIT_WARN_Inverter_Warn_Temp_Y
   * Referenced by: '<S5>/LIMIT_WARN_Inverter_Warn_Temp'
   */
  1.0F,

  /* Computed Parameter: LIMIT_WARN_Inverter_Warn_Temp_p
   * Referenced by: '<S5>/LIMIT_WARN_Inverter_Warn_Temp'
   */
  0.0F,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S11>/Constant'
   */
  false,

  /* Computed Parameter: Logic_table
   * Referenced by: '<S12>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_l
   * Referenced by: '<S13>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_i
   * Referenced by: '<S14>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_k
   * Referenced by: '<S15>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_km
   * Referenced by: '<S16>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_h
   * Referenced by: '<S17>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_g
   * Referenced by: '<S18>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_gb
   * Referenced by: '<S19>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_e
   * Referenced by: '<S20>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_lq
   * Referenced by: '<S21>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_m
   * Referenced by: '<S22>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_g5
   * Referenced by: '<S23>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
