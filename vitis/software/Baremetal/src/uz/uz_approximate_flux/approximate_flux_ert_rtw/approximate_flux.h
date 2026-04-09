/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: approximate_flux.h
 *
 * Code generated for Simulink model 'approximate_flux'.
 *
 * Model version                  : 7.3
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Feb 21 16:05:24 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_approximate_flux_h_
#define RTW_HEADER_approximate_flux_h_
#ifndef approximate_flux_COMMON_INCLUDES_
#define approximate_flux_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* approximate_flux_COMMON_INCLUDES_ */

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

#define approximate_flux_M             (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T id;                         /* '<Root>/id' */
  real32_T iq;                         /* '<Root>/iq' */
  real32_T fitting_parameters[23];     /* '<Root>/fitting_parameters' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T psid_approx;                /* '<Root>/psid_approx' */
  real32_T psiq_approx;                /* '<Root>/psiq_approx' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
};

/* Model entry point functions */
extern void approximate_flux_initialize(RT_MODEL *const rtM);
extern void approximate_flux_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_approximate_flux/approximate_flux')    - opens subsystem uz_approximate_flux/approximate_flux
 * hilite_system('uz_approximate_flux/approximate_flux/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_approximate_flux'
 * '<S1>'   : 'uz_approximate_flux/approximate_flux'
 * '<S2>'   : 'uz_approximate_flux/approximate_flux/approximate_flux_d'
 * '<S3>'   : 'uz_approximate_flux/approximate_flux/approximate_flux_q'
 */

/*-
 * Requirements for '<Root>': approximate_flux

 */
#endif                                 /* RTW_HEADER_approximate_flux_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
