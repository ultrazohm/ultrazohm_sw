/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CurrentControl_Kp_iq_adjustment.h
 *
 * Code generated for Simulink model 'CurrentControl_Kp_iq_adjustment'.
 *
 * Model version                  : 7.8
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Thu Feb 15 15:30:56 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_CurrentControl_Kp_iq_adjustment_h_
#define RTW_HEADER_CurrentControl_Kp_iq_adjustment_h_
#ifndef CurrentControl_Kp_iq_adjustment_COMMON_INCLUDES_
#define CurrentControl_Kp_iq_adjustment_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                    /* CurrentControl_Kp_iq_adjustment_COMMON_INCLUDES_ */

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

#define CurrentControl_Kp_iq_adjustment_M (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T dead_time_reciprocal;     /* '<Root>/dead_time_reciprocal' */
  real32_T psiq_ref;                   /* '<Root>/psiq_ref' */
  real32_T psiq_mea;                   /* '<Root>/psiq_mea' */
  real32_T iq_ref;                     /* '<Root>/iq_ref' */
  real32_T iq_mea;                     /* '<Root>/iq_mea' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T Kp_iq;                      /* '<Root>/Kp_iq' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
};

/* Model entry point functions */
extern void CurrentControl_Kp_iq_adjustment_initialize(RT_MODEL *const rtM);
extern void CurrentControl_Kp_iq_adjustment_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_CurrentControl_Kp_iq_adjustment/CurrentControl_Kp_iq_adjustment')    - opens subsystem uz_CurrentControl_Kp_iq_adjustment/CurrentControl_Kp_iq_adjustment
 * hilite_system('uz_CurrentControl_Kp_iq_adjustment/CurrentControl_Kp_iq_adjustment/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_CurrentControl_Kp_iq_adjustment'
 * '<S1>'   : 'uz_CurrentControl_Kp_iq_adjustment/CurrentControl_Kp_iq_adjustment'
 */

/*-
 * Requirements for '<Root>': CurrentControl_Kp_iq_adjustment

 */
#endif                       /* RTW_HEADER_CurrentControl_Kp_iq_adjustment_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
