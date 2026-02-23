/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SCF_types.h
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

#ifndef FOC_SCF_types_h_
#define FOC_SCF_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_bus_FCF_t_
#define DEFINED_TYPEDEF_FOR_bus_FCF_t_

/* Fast Control Function Output Signals */
typedef struct {
  real32_T DutyCycles[9];
  real32_T U_DC;
  real32_T I_dq_Act[6];
  real32_T ModInd[3];
  real32_T w_el;
  boolean_T FOC_Enable_PWM;
  boolean_T FCF_Error;
} bus_FCF_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_bus_SMF_t_
#define DEFINED_TYPEDEF_FOR_bus_SMF_t_

/* Statemachine Function Output Signals */
typedef struct {
  real32_T SysStateAct;
  real32_T FOC_Mode;
  real32_T StateFOC;
  real32_T FOC_Enable_PWM;
  real32_T global_reset_errors;
  real32_T SPEED_CTRL_Enable;
  real32_T MaxMotTemp;
  boolean_T Collective_Over_Temp_Error;
} bus_SMF_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_bus_BSW_SMF_t_
#define DEFINED_TYPEDEF_FOR_bus_BSW_SMF_t_

/* Basis Software Signals of Statemachine Function */
typedef struct {
  real32_T EXT_State_Request;
  real32_T EXT_Torque_Request;
  real32_T EXT_Speed_Request;
  real32_T EXT_Torque_Limit_Pos;
  real32_T EXT_Torque_Limit_Neg;
  real32_T EXT_Shutdown_Request;
  boolean_T EXT_KL15_PG;
  real32_T MotTemp[7];
  real32_T InvTemp[9];
} bus_BSW_SMF_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_bus_SCF_t_
#define DEFINED_TYPEDEF_FOR_bus_SCF_t_

/* Slow Control Function Output Signals */
typedef struct {
  real32_T I_dq_Ref[2];
  real32_T TorqueEst;
  real32_T TorqueRefDerated;
  real32_T n_Act;
} bus_SCF_t;

#endif

/* Parameters (default storage) */
typedef struct P_FOC_SCF_T_ P_FOC_SCF_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_FOC_SCF_T RT_MODEL_FOC_SCF_T;

#endif                                 /* FOC_SCF_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
