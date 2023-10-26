/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ControlState.h
 *
 * Code generated for Simulink model 'ControlState'.
 *
 * Model version                  : 5.80
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Aug 17 17:44:10 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "../uz_ParameterID_data.h"

#ifndef RTW_HEADER_ControlState_h_
#define RTW_HEADER_ControlState_h_
#include "../lib/rtwtypes.h"
#include <string.h>
#ifndef ControlState_COMMON_INCLUDES_
#define ControlState_COMMON_INCLUDES_
#include "../lib/rtwtypes.h"
#endif                                 /* ControlState_COMMON_INCLUDES_ */

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

#define ControlState_M                 (rtControlState_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_ControlState_t RT_MODEL_ControlState_t;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  uint16_T finishedElectricalID_loc;   /* '<Root>/ControlState' */
  uint16_T finishedFrictionID_loc;     /* '<Root>/ControlState' */
  uint16_T finishedTwoMassID_loc;      /* '<Root>/ControlState' */
  uint16_T finishedFluxMapID_loc;      /* '<Root>/ControlState' */
  uint8_T is_c8_ControlState;          /* '<Root>/ControlState' */
  uint8_T is_ControlState;             /* '<Root>/ControlState' */
  uint8_T is_active_c8_ControlState;   /* '<Root>/ControlState' */
} DW_ControlState_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  boolean_T finishedFrictionID;        /* '<Root>/finishedFrictionID' */
  boolean_T finishedElectricalID;      /* '<Root>/finishedElectricalID' */
  boolean_T finishedTwoMassID;         /* '<Root>/finishedTwoMassID' */
  boolean_T finishedFluxMapID;         /* '<Root>/finishedFluxMapID' */
  boolean_T enteredFrictionID;         /* '<Root>/enteredFrictionID' */
  boolean_T enteredFluxMapID;          /* '<Root>/enteredFluxMapID' */
  boolean_T enteredTwoMassID;          /* '<Root>/enteredTwoMassID' */
  boolean_T enteredElectricalID;       /* '<Root>/enteredElectricalID' */
  uz_ParaID_ElectricalID_output_t ElectricalID_output;/* '<Root>/ElectricalID_output' */
  uz_ParaID_Controller_Parameters_output_t ElectricalID_FOC_output;/* '<Root>/ElectricalID_FOC_output' */
  uz_ParaID_GlobalConfig_t GlobalConfig_in;/* '<Root>/GlobalConfig_in' */
  boolean_T enteredOnlineID;           /* '<Root>/enteredOnlineID' */
} ExtU_ControlState_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uz_ParaID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig_out' */
  uz_ParaID_ControlFlags_t ControlFlags;/* '<Root>/ControlFlags' */
} ExtY_ControlState_t;

/* Real-time Model Data Structure */
struct tag_RTM_ControlState_t {
  ExtU_ControlState_t *inputs;
  ExtY_ControlState_t *outputs;
  DW_ControlState_t *dwork;
};

/* Model entry point functions */
extern void ControlState_initialize(RT_MODEL_ControlState_t *const
  rtControlState_M);
extern void ControlState_step(RT_MODEL_ControlState_t *const rtControlState_M);

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
 * hilite_system('uz_3ph_ParameterID/Subsystem Reference1/ControlState')    - opens subsystem uz_3ph_ParameterID/Subsystem Reference1/ControlState
 * hilite_system('uz_3ph_ParameterID/Subsystem Reference1/ControlState/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_3ph_ParameterID/Subsystem Reference1'
 * '<S1>'   : 'uz_3ph_ParameterID/Subsystem Reference1/ControlState'
 */

/*-
 * Requirements for '<Root>': ControlState

 */
#endif                                 /* RTW_HEADER_ControlState_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
