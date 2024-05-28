/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Oct 13 09:55:19 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */
#ifdef TEST
#ifndef RTW_HEADER_uz_codegen0_h_
#define RTW_HEADER_uz_codegen0_h_
#ifndef uz_codegen0_COMMON_INCLUDES_
#define uz_codegen0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* uz_codegen0_COMMON_INCLUDES_ */

#include <stddef.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetRootDWork
#define rtmGetRootDWork(rtm)           ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
#define rtmSetRootDWork(rtm, val)      ((rtm)->dwork = (val))
#endif

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

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator2_DSTATE;/* '<S1>/Discrete-Time Integrator2' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S1>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator2_PrevRes;/* '<S1>/Discrete-Time Integrator2' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T summand1;                   /* '<Root>/summand1' */
  real32_T summand2;                   /* '<Root>/summand2' */
  real32_T reset_SumIntegrator;        /* '<Root>/reset_SumIntegrator' */
  real32_T time;                       /* '<Root>/time' */
  real32_T summand3;                   /* '<Root>/summand3' */
  real32_T reset_TimeIntegrator;       /* '<Root>/reset_TimeIntegrator' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T sum;                        /* '<Root>/sum' */
  real32_T IntegrationOfSum;           /* '<Root>/IntegrationOfSum' */
  real32_T ChirpSine;                  /* '<Root>/ChirpSine' */
  real32_T fb_summand1;                /* '<Root>/fb_summand1' */
  real32_T fb_time;                    /* '<Root>/fb_time' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

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
#endif
