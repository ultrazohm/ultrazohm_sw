/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 5.4
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Wed Mar 29 16:20:19 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_uz_codegen0_h_
#define RTW_HEADER_uz_codegen0_h_
#ifndef uz_codegen0_COMMON_INCLUDES_
#define uz_codegen0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* uz_codegen0_COMMON_INCLUDES_ */

#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetU
#define rtmGetU(rtm)                   ((rtm)->inputs)
#endif

#ifndef rtmSetU
#define rtmSetU(rtm, val)              ((rtm)->inputs = (val))
#endif

#ifndef rtmGetY
#define rtmGetY(rtm)                   ((rtm)->outputs)
#endif

#ifndef rtmSetY
#define rtmSetY(rtm, val)              ((rtm)->outputs = (val))
#endif

#define uz_codegen0_M                  (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: MEid_tableData
   * Referenced by: '<S1>/MEid'
   */
  real32_T MEid_tableData[287];

  /* Pooled Parameter (Expression: omega_ME)
   * Referenced by:
   *   '<S1>/MEid'
   *   '<S1>/MEiq'
   */
  real32_T pooled1[7];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/MEid'
   *   '<S1>/MEiq'
   *   '<S1>/MTPAid'
   *   '<S1>/MTPAiq'
   */
  real32_T pooled2[41];

  /* Computed Parameter: MEiq_tableData
   * Referenced by: '<S1>/MEiq'
   */
  real32_T MEiq_tableData[287];

  /* Computed Parameter: MTPAid_tableData
   * Referenced by: '<S1>/MTPAid'
   */
  real32_T MTPAid_tableData[41];

  /* Computed Parameter: MTPAiq_tableData
   * Referenced by: '<S1>/MTPAiq'
   */
  real32_T MTPAiq_tableData[41];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S1>/MEid'
   *   '<S1>/MEiq'
   */
  uint32_T pooled3[2];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T omega;                      /* '<Root>/omega' */
  real32_T torque;                     /* '<Root>/torque' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T ME_id;                      /* '<Root>/ME_id' */
  real32_T ME_iq;                      /* '<Root>/ME_iq' */
  real32_T MTPA_id;                    /* '<Root>/MTPA_id' */
  real32_T MTPA_iq;                    /* '<Root>/MTPA_iq' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
};

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void uz_codegen0_initialize(RT_MODEL *const rtM);
extern void uz_codegen0_step(RT_MODEL *const rtM);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('uz_codegen/uz_codegen')    - opens subsystem uz_codegen/uz_codegen
 * hilite_system('uz_codegen/uz_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/uz_codegen'
 */

/*-
 * Requirements for '<Root>': uz_codegen0

 */
#endif                                 /* RTW_HEADER_uz_codegen0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
