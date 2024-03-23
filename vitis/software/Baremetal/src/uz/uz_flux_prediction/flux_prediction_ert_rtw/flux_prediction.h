/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: flux_prediction.h
 *
 * Code generated for Simulink model 'flux_prediction'.
 *
 * Model version                  : 7.7
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Mar 23 12:17:55 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_flux_prediction_h_
#define RTW_HEADER_flux_prediction_h_
#ifndef flux_prediction_COMMON_INCLUDES_
#define flux_prediction_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* flux_prediction_COMMON_INCLUDES_ */

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

#define flux_prediction_M              (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T i_d;                        /* '<Root>/i_d' */
  real32_T i_q;                        /* '<Root>/i_q' */
  real32_T omega_ell;                  /* '<Root>/omega_ell' */
  real32_T u_d_k1;                     /* '<Root>/u_d_k1' */
  real32_T u_q_k1;                     /* '<Root>/u_q_k1' */
  real32_T u_d_k0;                     /* '<Root>/u_d_k0' */
  real32_T u_q_k0;                     /* '<Root>/u_q_k0' */
  real32_T flux_q;                     /* '<Root>/flux_q' */
  real32_T flux_d;                     /* '<Root>/flux_d' */
  real32_T r_1;                        /* '<Root>/r_1' */
  real32_T ts_regler;                  /* '<Root>/ts_regler' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T flux_d_pre;                 /* '<Root>/flux_d_pre' */
  real32_T flux_q_pre;                 /* '<Root>/flux_q_pre' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
};

/* Model entry point functions */
extern void flux_prediction_initialize(RT_MODEL *const rtM);
extern void flux_prediction_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_flux_prediction/flux_prediction')    - opens subsystem uz_flux_prediction/flux_prediction
 * hilite_system('uz_flux_prediction/flux_prediction/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_flux_prediction'
 * '<S1>'   : 'uz_flux_prediction/flux_prediction'
 */

/*-
 * Requirements for '<Root>': flux_prediction

 */
#endif                                 /* RTW_HEADER_flux_prediction_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
