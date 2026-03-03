/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF_types.h
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

#ifndef FOC_FCF_types_h_
#define FOC_FCF_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_bus_BSW_FCF_t_
#define DEFINED_TYPEDEF_FOR_bus_BSW_FCF_t_

/* Basis Software Signals of Fast Control Function */
typedef struct {
  real32_T ADC_U_DC;
  real32_T ADC_I_ph[9];
  real32_T phi;
  uint32_T Gate_Driver_Status_RDY;
  uint32_T Gate_Driver_Status_FLT;
} bus_BSW_FCF_t;

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

#ifndef DEFINED_TYPEDEF_FOR_bus_SMF_t_
#define DEFINED_TYPEDEF_FOR_bus_SMF_t_

/* Statemachine Function Output Signals */
typedef struct {
  uint8_T SysStateAct;
  uint8_T FOC_Mode;
  uint8_T StateFOC;
  boolean_T FOC_Enable_PWM;
  boolean_T global_reset_errors;
  boolean_T SPEED_CTRL_Enable;
  real32_T MaxMotTemp;
  boolean_T Collective_Over_Temp_Error;
} bus_SMF_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_bus_FCF_t_
#define DEFINED_TYPEDEF_FOR_bus_FCF_t_

/* Fast Control Function Output Signals */
typedef struct {
  real32_T DutyCycles[9];
  real32_T U_DC;
  real32_T I_dq_Act[6];
  real32_T ModInd[3];
  real32_T w_el;
  boolean_T FOC_Enable_PWM[3];
  boolean_T FCF_Error;
} bus_FCF_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_bus_InvStatus_t_
#define DEFINED_TYPEDEF_FOR_bus_InvStatus_t_

/* Inverter Status Signals */
typedef struct {
  boolean_T U1_HS_FLT;
  boolean_T U1_LS_FLT;
  boolean_T V1_HS_FLT;
  boolean_T V1_LS_FLT;
  boolean_T W1_HS_FLT;
  boolean_T W1_LS_FLT;
  boolean_T FLT_Error_Sys1;
  boolean_T U1_HS_RDY;
  boolean_T U1_LS_RDY;
  boolean_T V1_HS_RDY;
  boolean_T V1_LS_RDY;
  boolean_T W1_HS_RDY;
  boolean_T W1_LS_RDY;
  boolean_T RDY_Error_Sys1;
  boolean_T U2_HS_FLT;
  boolean_T U2_LS_FLT;
  boolean_T V2_HS_FLT;
  boolean_T V2_LS_FLT;
  boolean_T W2_HS_FLT;
  boolean_T W2_LS_FLT;
  boolean_T FLT_Error_Sys2;
  boolean_T U2_HS_RDY;
  boolean_T U2_LS_RDY;
  boolean_T V2_HS_RDY;
  boolean_T V2_LS_RDY;
  boolean_T W2_HS_RDY;
  boolean_T W2_LS_RDY;
  boolean_T RDY_Error_Sys2;
  boolean_T U3_HS_FLT;
  boolean_T U3_LS_FLT;
  boolean_T V3_HS_FLT;
  boolean_T V3_LS_FLT;
  boolean_T W3_HS_FLT;
  boolean_T W3_LS_FLT;
  boolean_T FLT_Error_Sys3;
  boolean_T U3_HS_RDY;
  boolean_T U3_LS_RDY;
  boolean_T V3_HS_RDY;
  boolean_T V3_LS_RDY;
  boolean_T W3_HS_RDY;
  boolean_T W3_LS_RDY;
  boolean_T RDY_Error_Sys3;
} bus_InvStatus_t;

#endif

/* Parameters (default storage) */
typedef struct P_FOC_FCF_T_ P_FOC_FCF_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_FOC_FCF_T RT_MODEL_FOC_FCF_T;

#endif                                 /* FOC_FCF_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
