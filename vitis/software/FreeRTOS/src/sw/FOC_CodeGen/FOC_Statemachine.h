/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_Statemachine.h
 *
 * Code generated for Simulink model 'FOC_Statemachine'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Aug 22 14:13:05 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_Statemachine_h_
#define RTW_HEADER_FOC_Statemachine_h_
#ifndef FOC_Statemachine_COMMON_INCLUDES_
#define FOC_Statemachine_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Statemachine_COMMON_INCLUDES_ */

#include "FOC_Statemachine_types.h"
#include <string.h>
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c1_FOC_Statemachine;/* '<Root>/FOC_Statemachine' */
  uint8_T is_c1_FOC_Statemachine;      /* '<Root>/FOC_Statemachine' */
  uint8_T is_RUN_MODE;                 /* '<Root>/FOC_Statemachine' */
} DW_FOC_Statemachine_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T StateReq;                     /* '<Root>/StateReq' */
  real_T TorqueReq;                    /* '<Root>/TorqueReq' */
  real_T SpeedReq;                     /* '<Root>/SpeedReq' */
  boolean_T FastCtrl_Error;            /* '<Root>/error' */
} ExtU_FOC_Statemachine_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T State;                        /* '<Root>/State' */
  real_T FOC_Mode;                     /* '<Root>/FOC_Mode' */
  real_T StateFOC;                     /* '<Root>/StateFOC' */
  real_T FOC_Enable_PWM;               /* '<Root>/FOC_Enable_PWM' */
  real_T global_reset_errors;          /* '<Root>/global_reset_errors' */
  real_T SPEED_CTRL_Enable;            /* '<Root>/SPEED_CTRL_Enable' */
} ExtY_FOC_Statemachine_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_Statemachine_T {
  const char_T * volatile errorStatus;
  ExtU_FOC_Statemachine_T *inputs;
  ExtY_FOC_Statemachine_T *outputs;
  DW_FOC_Statemachine_T *dwork;
};

/* Model entry point functions */
extern void FOC_Statemachine_initialize(RT_MODEL_FOC_Statemachine_T *const
  FOC_Statemachine_M);
extern void FOC_Statemachine_step(RT_MODEL_FOC_Statemachine_T *const
  FOC_Statemachine_M);
extern void FOC_Statemachine_terminate(RT_MODEL_FOC_Statemachine_T *const
  FOC_Statemachine_M);

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
 * hilite_system('MotorControl_HeadModel/Statemachine/FOC_Statemachine')    - opens subsystem MotorControl_HeadModel/Statemachine/FOC_Statemachine
 * hilite_system('MotorControl_HeadModel/Statemachine/FOC_Statemachine/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MotorControl_HeadModel/Statemachine'
 * '<S1>'   : 'MotorControl_HeadModel/Statemachine/FOC_Statemachine'
 */
#endif                                 /* RTW_HEADER_FOC_Statemachine_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
