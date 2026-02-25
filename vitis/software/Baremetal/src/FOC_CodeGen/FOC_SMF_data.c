/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SMF_data.c
 *
 * Code generated for Simulink model 'FOC_SMF'.
 *
 * Model version                  : 5.74
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Feb 25 11:45:13 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_SMF.h"

/* Block parameters (default storage) */
P_FOC_SMF_T FOC_SMF_P = {
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
  1U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
