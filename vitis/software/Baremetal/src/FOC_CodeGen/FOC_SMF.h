/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SMF.h
 *
 * Code generated for Simulink model 'FOC_SMF'.
 *
 * Model version                  : 5.37
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Feb 10 14:30:58 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef FOC_SMF_h_
#define FOC_SMF_h_
#ifndef FOC_SMF_COMMON_INCLUDES_
#define FOC_SMF_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* FOC_SMF_COMMON_INCLUDES_ */

#include "FOC_SMF_types.h"
#include <string.h>
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real32_T DataSourceSwitch[3];        /* '<S1>/DataSourceSwitch' */
  boolean_T KL15_PG_SourceSwitch;      /* '<S1>/KL15_PG_SourceSwitch' */
} B_FOC_SMF_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c1_FOC_SMF;        /* '<S1>/FOC_Statemachine' */
  uint8_T is_c1_FOC_SMF;               /* '<S1>/FOC_Statemachine' */
  uint8_T is_RUN_MODE;                 /* '<S1>/FOC_Statemachine' */
} DW_FOC_SMF_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T EXT_State_Request;          /* '<Root>/<EXT_State_Request>' */
  real32_T EXT_Torque_Request;         /* '<Root>/<EXT_Torque_Request>' */
  real32_T EXT_Speed_Request;          /* '<Root>/<EXT_Speed_Request>' */
  boolean_T FastCtrl_Error;            /* '<Root>/<FastCtrl_Error>' */
  boolean_T EXT_KL15_PG;               /* '<Root>/EXT_KL15_PG' */
} ExtU_FOC_SMF_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T SysStateAct;                /* '<Root>/SysStateAct' */
  real32_T FOC_Mode;                   /* '<Root>/FOC_Mode' */
  real32_T StateFOC;                   /* '<Root>/StateFOC' */
  real32_T FOC_Enable_PWM;             /* '<Root>/FOC_Enable_PWM' */
  real32_T global_reset_errors;        /* '<Root>/global_reset_errors' */
  real32_T SPEED_CTRL_Enable;          /* '<Root>/SPEED_CTRL_Enable' */
} ExtY_FOC_SMF_T;

/* Parameters (default storage) */
struct P_FOC_SMF_T_ {
  real32_T FOC_MANUAL_State_Request;   /* Variable: FOC_MANUAL_State_Request
                                        * Referenced by: '<S1>/MANUAL_StateReq'
                                        */
  real32_T FOC_MANUAL_Torque_Request;  /* Variable: FOC_MANUAL_Torque_Request
                                        * Referenced by: '<S1>/Constant'
                                        */
  real32_T SPEED_CTRL_MANUAL_n_RPM;    /* Variable: SPEED_CTRL_MANUAL_n_RPM
                                        * Referenced by: '<S1>/OmegaRot2'
                                        */
  real32_T enumState_CTRL_IDLE;        /* Variable: enumState_CTRL_IDLE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_CTRL_INIT;        /* Variable: enumState_CTRL_INIT
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_ERROR_MODE;       /* Variable: enumState_ERROR_MODE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_IDLE;         /* Variable: enumState_FOC_IDLE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_OFF;          /* Variable: enumState_FOC_OFF
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_SPEED;        /* Variable: enumState_FOC_SPEED
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_STANDBY;      /* Variable: enumState_FOC_STANDBY
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_FOC_TORQUE;       /* Variable: enumState_FOC_TORQUE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_RUN_MODE;         /* Variable: enumState_RUN_MODE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_SPEED_MODE;       /* Variable: enumState_SPEED_MODE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_SYS_INIT;         /* Variable: enumState_SYS_INIT
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  real32_T enumState_TORQUE_MODE;      /* Variable: enumState_TORQUE_MODE
                                        * Referenced by: '<S1>/FOC_Statemachine'
                                        */
  boolean_T FOC_MANUAL_KL15_PG;        /* Variable: FOC_MANUAL_KL15_PG
                                        * Referenced by: '<S1>/FOC_MANUAL_KL15_PG'
                                        */
  uint8_T SELECT_DataSource;           /* Variable: SELECT_DataSource
                                        * Referenced by: '<S1>/SELECT_DataSource'
                                        */
  uint8_T SELECT_KL15_PG;              /* Variable: SELECT_KL15_PG
                                        * Referenced by: '<S1>/SELECT_KL15_PG'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_FOC_SMF_T {
  const char_T * volatile errorStatus;
  B_FOC_SMF_T *blockIO;
  ExtU_FOC_SMF_T *inputs;
  ExtY_FOC_SMF_T *outputs;
  DW_FOC_SMF_T *dwork;
};

/* Block parameters (default storage) */
extern P_FOC_SMF_T FOC_SMF_P;

/* Model entry point functions */
extern void FOC_SMF_initialize(RT_MODEL_FOC_SMF_T *const FOC_SMF_M);
extern void FOC_SMF_step(RT_MODEL_FOC_SMF_T *const FOC_SMF_M);
extern void FOC_SMF_terminate(RT_MODEL_FOC_SMF_T *const FOC_SMF_M);

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
 * hilite_system('MotorControl_HeadModel/Statemachine/FOC_SMF')    - opens subsystem MotorControl_HeadModel/Statemachine/FOC_SMF
 * hilite_system('MotorControl_HeadModel/Statemachine/FOC_SMF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MotorControl_HeadModel/Statemachine'
 * '<S1>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF'
 * '<S2>'   : 'MotorControl_HeadModel/Statemachine/FOC_SMF/FOC_Statemachine'
 */
#endif                                 /* FOC_SMF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
