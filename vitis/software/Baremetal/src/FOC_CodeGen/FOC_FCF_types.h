/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF_types.h
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

#ifndef FOC_FCF_types_h_
#define FOC_FCF_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_bus_BSW_FCF_t_
#define DEFINED_TYPEDEF_FOR_bus_BSW_FCF_t_

/* Basis Software Signals from Fast Control Function */
typedef struct {
  uint32_T Gate_Driver_Status_RDY;
  uint32_T Gate_Driver_Status_FLT;
} bus_BSW_FCF_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_bus_InvStatus_t_
#define DEFINED_TYPEDEF_FOR_bus_InvStatus_t_

/* Inverter Status Signals */
typedef struct {
  boolean_T Gate_Driver_FLT_Error;
  boolean_T Gate_Driver_RDY_Error;
  boolean_T U1_HS_FLT;
  boolean_T U1_LS_FLT;
  boolean_T V1_HS_FLT;
  boolean_T V1_LS_FLT;
  boolean_T W1_HS_FLT;
  boolean_T W1_LS_FLT;
  boolean_T U1_HS_RDY;
  boolean_T U1_LS_RDY;
  boolean_T V1_HS_RDY;
  boolean_T V1_LS_RDY;
  boolean_T W1_HS_RDY;
  boolean_T W1_LS_RDY;
  boolean_T U2_HS_FLT;
  boolean_T U2_LS_FLT;
  boolean_T V2_HS_FLT;
  boolean_T V2_LS_FLT;
  boolean_T W2_HS_FLT;
  boolean_T W2_LS_FLT;
  boolean_T U2_HS_RDY;
  boolean_T U2_LS_RDY;
  boolean_T V2_HS_RDY;
  boolean_T V2_LS_RDY;
  boolean_T W2_HS_RDY;
  boolean_T W2_LS_RDY;
  boolean_T U3_HS_FLT;
  boolean_T U3_LS_FLT;
  boolean_T V3_HS_FLT;
  boolean_T V3_LS_FLT;
  boolean_T W3_HS_FLT;
  boolean_T W3_LS_FLT;
  boolean_T U3_HS_RDY;
  boolean_T U3_LS_RDY;
  boolean_T V3_HS_RDY;
  boolean_T V3_LS_RDY;
  boolean_T W3_HS_RDY;
  boolean_T W3_LS_RDY;
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
