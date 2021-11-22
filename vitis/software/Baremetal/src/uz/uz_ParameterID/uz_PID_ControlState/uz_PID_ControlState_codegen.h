/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ControlState.h
 *
 * Code generated for Simulink model 'ControlState'.
 *
 * Model version                  : 2.11
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Nov 22 08:30:00 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */
#include "../../uz_global_configuration.h"
#if UZ_PID_CONTROLSTATE_ACTIVE > 0U

#ifndef RTW_HEADER_ControlState_h_
#define RTW_HEADER_ControlState_h_
#include "../rtwtypes.h"
#include <string.h>
#ifndef ControlState_COMMON_INCLUDES_
#define ControlState_COMMON_INCLUDES_
#include "../rtwtypes.h"
#endif                                 /* ControlState_COMMON_INCLUDES_ */

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

#define ControlState_M                 (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_ElectricalID_output_
#define DEFINED_TYPEDEF_FOR_ElectricalID_output_

typedef struct {
  real32_T PWM_Switch_0;
  real32_T PWM_Switch_1;
  real32_T PWM_Switch_2;
  real32_T PWM_Switch_3;
  real32_T PWM_Switch_4;
  real32_T PWM_Switch_5;
  boolean_T outputMode[3];
  real32_T R_s;
  real32_T L_d;
  real32_T L_q;
  real32_T psiPM;
  real32_T rotorInertia;
  real32_T thetaOffset;
  uint16_T p;
  real32_T TrainInertia;
} ElectricalID_output;

#endif

#ifndef DEFINED_TYPEDEF_FOR_State_FOC_output_
#define DEFINED_TYPEDEF_FOR_State_FOC_output_

typedef struct {
  uint16_T activeState;
  real32_T n_ref_FOC;
  real32_T i_d_ref_out;
  real32_T i_q_ref_out;
  boolean_T enableFOC_speed;
  boolean_T enableFOC_current;
  boolean_T VibOn_out;
  real32_T VibAmp_out;
  uint16_T VibFreq_out;
  boolean_T resetIntegrator;
  real32_T PRBS_out;
  real32_T Kp_id_out;
  real32_T Kp_iq_out;
  real32_T Kp_n_out;
  real32_T Ki_id_out;
  real32_T Ki_iq_out;
  real32_T Ki_n_out;
} State_FOC_output;

#endif

#ifndef DEFINED_TYPEDEF_FOR_GlobalConfig_
#define DEFINED_TYPEDEF_FOR_GlobalConfig_

typedef struct {
  boolean_T controlType;
  boolean_T Reset;
  real32_T Kp_id;
  real32_T Kp_iq;
  real32_T Kp_n;
  real32_T Ki_id;
  real32_T Ki_iq;
  real32_T Ki_n;
  boolean_T ElectricalID;
  boolean_T FrictionID;
  boolean_T TwoMassID;
  boolean_T FluxMapID;
  boolean_T OnlineID;
  real32_T thetaOffset;
  boolean_T ACCEPT;
  real32_T sampleTimeISR;
  real32_T polePairs;
  real32_T ratCurrent;
  real32_T ratSpeed;
  real32_T L_d;
  real32_T L_q;
  real32_T R_ph;
  real32_T psi_pm;
  real32_T VibAmp;
  boolean_T VibOn;
  uint16_T VibFreq;
} GlobalConfig;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ControlFlags_
#define DEFINED_TYPEDEF_FOR_ControlFlags_

typedef struct {
  boolean_T startFrictionID;
  boolean_T startElectricalID;
  boolean_T startTwoMassID;
  boolean_T startFluxMapID;
  uint16_T transNr;
  boolean_T enableFOCcurrentState;
  boolean_T enableFOCspeedState;
  boolean_T enableOnlineID;
} ControlFlags;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c8_ControlState;   /* '<Root>/ControlState' */
  uint8_T is_ControlState;             /* '<Root>/ControlState' */
  boolean_T finishedElectricalID_loc;  /* '<Root>/ControlState' */
  boolean_T finishedFrictionID_loc;    /* '<Root>/ControlState' */
  boolean_T finishedTwoMassID_loc;     /* '<Root>/ControlState' */
  boolean_T finishedFluxMapID_loc;     /* '<Root>/ControlState' */
} DW;

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
  ElectricalID_output ElectricalID_output_n;/* '<Root>/ElectricalID_output' */
  State_FOC_output ElectricalID_FOC_output;/* '<Root>/ElectricalID_FOC_output' */
  GlobalConfig GlobalConfig_in;        /* '<Root>/GlobalConfig_in' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T thetaOffset;                /* '<Root>/thetaOffset' */
  GlobalConfig GlobalConfig_out;       /* '<Root>/GlobalConfig_out' */
  ControlFlags ControlFlags_p;         /* '<Root>/ControlFlags' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Model entry point functions */
extern void ControlState_initialize(RT_MODEL *const rtM);
extern void ControlState_step(RT_MODEL *const rtM);

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
 * hilite_system('uz_ParameterID/ControlState')    - opens subsystem uz_ParameterID/ControlState
 * hilite_system('uz_ParameterID/ControlState/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID'
 * '<S1>'   : 'uz_ParameterID/ControlState'
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

#endif
