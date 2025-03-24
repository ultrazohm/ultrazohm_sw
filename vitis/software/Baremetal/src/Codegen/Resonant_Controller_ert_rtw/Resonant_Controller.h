/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Resonant_Controller.h
 *
 * Code generated for Simulink model 'Resonant_Controller'.
 *
 * Model version                  : 4.8
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Mar 13 16:04:09 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef Resonant_Controller_h_
#define Resonant_Controller_h_
#ifndef Resonant_Controller_COMMON_INCLUDES_
#define Resonant_Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                /* Resonant_Controller_COMMON_INCLUDES_ */

#include <stddef.h>

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

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define Resonant_Controller_M          (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T Delay_DSTATE;               /* '<S1>/Delay' */
  real32_T Delay3_DSTATE;              /* '<S1>/Delay3' */
  real32_T Delay1_DSTATE;              /* '<S1>/Delay1' */
  real32_T Delay2_DSTATE;              /* '<S1>/Delay2' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T in_ref;                     /* '<Root>/in_ref' */
  real32_T in_m;                       /* '<Root>/in_m' */
  real32_T omega_el;                   /* '<Root>/omega_el' */
  real32_T h;                          /* '<Root>/h' */
  real32_T T_sw;                       /* '<Root>/T_sw' */
  real32_T VR;                         /* '<Root>/VR' */
  real32_T Klim;                       /* '<Root>/Klim' */
  real32_T upper_limit;                /* '<Root>/upper_limit' */
  real32_T lower_limit;                /* '<Root>/lower_limit' */
  real32_T Reset;                      /* '<Root>/Reset' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T out;                        /* '<Root>/out' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Model entry point functions */
extern void Resonant_Controller_initialize(RT_MODEL *const rtM);
extern void Resonant_Controller_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_ResonantController/Resonant_Controller')    - opens subsystem uz_ResonantController/Resonant_Controller
 * hilite_system('uz_ResonantController/Resonant_Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ResonantController'
 * '<S1>'   : 'uz_ResonantController/Resonant_Controller'
 * '<S2>'   : 'uz_ResonantController/Resonant_Controller/saturation'
 */

/*-
 * Requirements for '<Root>': Resonant_Controller

 */
#endif                                 /* Resonant_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
