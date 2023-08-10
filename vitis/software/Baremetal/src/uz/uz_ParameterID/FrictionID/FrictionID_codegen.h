/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FrictionID.h
 *
 * Code generated for Simulink model 'FrictionID'.
 *
 * Model version                  : 2.349
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Dec 16 11:56:52 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "../uz_ParameterID_data.h"

#ifndef RTW_HEADER_FrictionID_h_
#define RTW_HEADER_FrictionID_h_
#ifndef FrictionID_COMMON_INCLUDES_
#define FrictionID_COMMON_INCLUDES_
#include "../rtwtypes.h"
#endif                                 /* FrictionID_COMMON_INCLUDES_ */
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

#define FrictionID_M                   (rtFrictionID_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_FrictionID_t RT_MODEL_FrictionID_t;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T measArray2[6144];           /* '<Root>/FrictionID' */
  real32_T Ustep[103];                 /* '<Root>/FrictionID' */
  real32_T meas_sum[3];                /* '<Root>/FrictionID' */
  real32_T b_line[2];
  real32_T b_line_m[2];
  real32_T M_Brk;                      /* '<Root>/FrictionID' */
  real32_T M_eva;                      /* '<Root>/FrictionID' */
  real32_T M_eva_step;                 /* '<Root>/FrictionID' */
  real32_T mean_count;                 /* '<Root>/FrictionID' */
  real32_T omega_Brk;                  /* '<Root>/FrictionID' */
  real32_T n_eva_step;                 /* '<Root>/FrictionID' */
  real32_T n_eva;                      /* '<Root>/FrictionID' */
  real32_T ex;
  int32_T i;
  uint32_T counter;                    /* '<Root>/FrictionID' */
  uint32_T one_sec_transition_counter; /* '<Root>/FrictionID' */
  uint32_T delay_transition_counter;   /* '<Root>/FrictionID' */
  uint32_T counter2;                   /* '<Root>/FrictionID' */
  uint32_T ten_sec_transition_counter; /* '<Root>/FrictionID' */
  uint32_T switch_count;               /* '<Root>/FrictionID' */
  uint32_T qY;
  uint16_T meas_count;                 /* '<Root>/FrictionID' */
  uint16_T nextstate;                  /* '<Root>/FrictionID' */
  uint8_T is_c7_FrictionID;            /* '<Root>/FrictionID' */
  uint8_T is_frictionID;               /* '<Root>/FrictionID' */
  uint8_T is_CoulombFrictionTorqueEstimat;/* '<Root>/FrictionID' */
  uint8_T is_BreakawayTorqueEstimation;/* '<Root>/FrictionID' */
  uint8_T is_active_c7_FrictionID;     /* '<Root>/FrictionID' */
  boolean_T switcher;                  /* '<Root>/FrictionID' */
} DW_FrictionID_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_ParaID_FrictionIDConfig_t FrictionIDConfig;/* '<Root>/FrictionIDConfig' */
  uz_ParaID_ActualValues_t ActualValues;/* '<Root>/ActualValues' */
  uz_ParaID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_ParaID_ControlFlags_t ControlFlags;/* '<Root>/ControlFlags' */
} ExtU_FrictionID_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T finishedFrictionID;        /* '<Root>/finishedFrictionID' */
  boolean_T enteredFrictionID;         /* '<Root>/enteredFrictionID' */
  uz_ParaID_Controller_Parameters_output_t FrictionID_FOC_output;/* '<Root>/FrictionID_FOC_output' */
  uz_ParaID_FrictionID_output_t FrictionID_state_output;/* '<Root>/FrictionID_state_output' */
} ExtY_FrictionID_t;

/* Real-time Model Data Structure */
struct tag_RTM_FrictionID_t {
  ExtU_FrictionID_t *inputs;
  ExtY_FrictionID_t *outputs;
  DW_FrictionID_t *dwork;
};

/* Model entry point functions */
extern void FrictionID_initialize(RT_MODEL_FrictionID_t *const rtFrictionID_M);
extern void FrictionID_step(RT_MODEL_FrictionID_t *const rtFrictionID_M);

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
 * hilite_system('FrictionID_ref/FrictionID')    - opens subsystem FrictionID_ref/FrictionID
 * hilite_system('FrictionID_ref/FrictionID/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FrictionID_ref'
 * '<S1>'   : 'FrictionID_ref/FrictionID'
 */

/*-
 * Requirements for '<Root>': FrictionID

 */
#endif                                 /* RTW_HEADER_FrictionID_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
