/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Resonanz_Regler_1.h
 *
 * Code generated for Simulink model 'Resonanz_Regler_1'.
 *
 * Model version                  : 3.0
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Jul 27 10:02:54 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_Resonanz_Regler_1_h_
#define RTW_HEADER_Resonanz_Regler_1_h_
#include <math.h>
#include <string.h>
#ifndef Resonanz_Regler_1_COMMON_INCLUDES_
#define Resonanz_Regler_1_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Resonanz_Regler_1_COMMON_INCLUDES_ */

/* Model Code Variants */

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

/* Forward declaration for rtModel */
typedef struct tag_RTM_Resonanz_Regler_1_T RT_MODEL_Resonanz_Regler_1_T;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay3_DSTATE;            /* '<S1>/Unit Delay3' */
  real_T UnitDelay6_DSTATE;            /* '<S1>/Unit Delay6' */
  real_T UnitDelay5_DSTATE;            /* '<S1>/Unit Delay5' */
} DW_Resonanz_Regler_1_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T in_ref;                       /* '<Root>/in_ref' */
  real_T in_m;                         /* '<Root>/in_m' */
  real_T omega_el;                     /* '<Root>/omega_el' */
  real_T h;                            /* '<Root>/h' */
  real_T T_sw;                         /* '<Root>/T_sw' */
  real_T VR;                           /* '<Root>/VR' */
} ExtU_Resonanz_Regler_1_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T out;                          /* '<Root>/out' */
} ExtY_Resonanz_Regler_1_T;

/* Real-time Model Data Structure */
struct tag_RTM_Resonanz_Regler_1_T {
  ExtU_Resonanz_Regler_1_T *inputs;
  ExtY_Resonanz_Regler_1_T *outputs;
  DW_Resonanz_Regler_1_T *dwork;
};

/* Model entry point functions */
extern void Resonanz_Regler_1_initialize(RT_MODEL_Resonanz_Regler_1_T *const
  Resonanz_Regler_1_M);
extern void Resonanz_Regler_1_step(RT_MODEL_Resonanz_Regler_1_T *const
  Resonanz_Regler_1_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/a0' : Eliminated nontunable gain of 1
 */

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
 * hilite_system('Resonant_Controller_codegen/Resonanz_Regler_1')    - opens subsystem Resonant_Controller_codegen/Resonanz_Regler_1
 * hilite_system('Resonant_Controller_codegen/Resonanz_Regler_1/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Resonant_Controller_codegen'
 * '<S1>'   : 'Resonant_Controller_codegen/Resonanz_Regler_1'
 */

/*-
 * Requirements for '<Root>': Resonanz_Regler_1
 */
#endif                                 /* RTW_HEADER_Resonanz_Regler_1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
