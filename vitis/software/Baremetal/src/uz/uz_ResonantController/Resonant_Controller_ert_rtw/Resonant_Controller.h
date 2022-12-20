/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Resonant_Controller.h
 *
 * Code generated for Simulink model 'Resonant_Controller'.
 *
 * Model version                  : 4.4
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Wed Oct 12 11:19:47 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_Resonant_Controller_h_
#define RTW_HEADER_Resonant_Controller_h_
#ifndef Resonant_Controller_COMMON_INCLUDES_
#define Resonant_Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                /* Resonant_Controller_COMMON_INCLUDES_ */

#include <stddef.h>
#include <string.h>

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
typedef struct tag_RTM_Resonant_Controller_T RT_MODEL_Resonant_Controller_T;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T Delay_DSTATE;               /* '<S1>/Delay' */
  real32_T Delay3_DSTATE;              /* '<S1>/Delay3' */
  real32_T Delay1_DSTATE;              /* '<S1>/Delay1' */
  real32_T Delay2_DSTATE;              /* '<S1>/Delay2' */
} DW_Resonant_Controller_T;

/* External inputs (root inport signals with default storage) */
/**
 * @brief input struct of the resonant controller
 * 
 */
typedef struct {
	real32_T in_ref;                       /**< Reference value for the controller*/
	real32_T in_m;                         /**< Measured value for the controller*/
	real32_T omega_el;                     /**< Fundamental frequency in rad/s*/
	real32_T h;                            /**< Order of harmonic to be controlled*/
	real32_T T_sw;                         /**< Sampling time*/
	real32_T VR;                           /**< Gain of the controller*/
	real32_T Klim;                         /**< Gain of anti-windup feedback*/
	real32_T upper_limit;                  /**< Upper saturation limit*/
	real32_T lower_limit;                  /**< Lower saturation limit*/
	real32_T Reset;                        /**< Reset input of the controller*/
} ExtU_Resonant_Controller_T;

/* External outputs (root outports fed by signals with default storage) */
/**
 * @brief output struct of the resonant controller
 * 
 */
typedef struct {
  real32_T out;                         /**< Output of the controller*/
} ExtY_Resonant_Controller_T;

/* Real-time Model Data Structure */
struct tag_RTM_Resonant_Controller_T {
  ExtU_Resonant_Controller_T *inputs;
  ExtY_Resonant_Controller_T *outputs;
  DW_Resonant_Controller_T *dwork;
};

/* Model entry point functions */
extern void Resonant_Controller_initialize(RT_MODEL_Resonant_Controller_T *const
  Resonant_Controller_M);
extern void Resonant_Controller_step(RT_MODEL_Resonant_Controller_T *const
  Resonant_Controller_M);

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
#endif                                 /* RTW_HEADER_Resonant_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
