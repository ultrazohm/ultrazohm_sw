/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ControlReference.h
 *
 * Code generated for Simulink model 'ControlReference'.
 *
 * Model version                  : 2.410
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Jan 13 10:19:48 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "../../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U

#include "../../../uz_Transformation/uz_Transformation.h"
#include "../../../uz_PMSM_config/uz_PMSM_config.h"
#ifndef RTW_HEADER_AutoRefCurrents_h_
#define RTW_HEADER_AutoRefCurrents_h_
#include "../../rtwtypes.h"
#include <math.h>
#ifndef AutoRefCurrents_COMMON_INCLUDES_
#define AutoRefCurrents_COMMON_INCLUDES_
#include "../../rtwtypes.h"
#endif                                 /* AutoRefCurrents_COMMON_INCLUDES_ */

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

#define AutoRefCurrents_M              (rtAutoRefCurrents_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_AutoRefCurrents_t RT_MODEL_AutoRefCurrents_t;

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ActualValues_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ActualValues_t_

typedef struct {
  uz_UVW_t V_UVW;
  uz_UVW_t I_UVW;
  uz_dq_t i_dq;
  uz_dq_t v_dq;
  real32_T omega_m;
  real32_T omega_el;
  real32_T theta_m;
  real32_T theta_el;
  real32_T V_DC;
} uz_PID_ActualValues_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_GlobalConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_GlobalConfig_t_

typedef struct {
  uz_PMSM_t PMSM_config;
  boolean_T enableParameterID;
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
  boolean_T ACCEPT;
  real32_T sampleTimeISR;
  real32_T ratCurrent;
  real32_T ratSpeed;
  real32_T VibAmp;
  boolean_T VibOn;
  uint16_T VibFreq;
  uz_dq_t i_dq_ref;
  real32_T n_ref;
} uz_PID_GlobalConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_AutoRefCurrentsConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_AutoRefCurrentsConfig_t_

typedef struct {
  boolean_T enableCRS;
  boolean_T Reset;
  real32_T iq_points;
  real32_T id_points;
  real32_T max_current;
} uz_PID_AutoRefCurrentsConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ControlFlags_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ControlFlags_t_

typedef struct {
	boolean_T startFrictionID;
	boolean_T startElectricalID;
	boolean_T startTwoMassID;
	boolean_T startFluxMapID;
	uint16_T transNr;
	boolean_T enableOnlineID;
	boolean_T finished_all_Offline_states;
} uz_PID_ControlFlags_t;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
	real32_T iqcount; /* '<Root>/AutoRefCurrents' */
	real32_T idcount; /* '<Root>/AutoRefCurrents' */
	real32_T counter; /* '<Root>/AutoRefCurrents' */
	real32_T imax; /* '<Root>/AutoRefCurrents' */
	uint8_T is_active_c10_AutoRefCurrents;/* '<Root>/AutoRefCurrents' */
	uint8_T is_c10_AutoRefCurrents; /* '<Root>/AutoRefCurrents' */
	uint8_T is_superstate; /* '<Root>/AutoRefCurrents' */
} DW_AutoRefCurrents_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_PID_ActualValues_t ActualValues;  /* '<Root>/ActualValues' */
  uz_PID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_PID_AutoRefCurrentsConfig_t AutoRefCurrentsConfig;/* '<Root>/AutoRefCurrentsConfig' */
	uz_PID_ControlFlags_t ControlFlags; /* '<Root>/ControlFlags' */
} ExtU_AutoRefCurrents_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uz_dq_t i_dq_ref;                    /* '<Root>/i_dq_ref' */
} ExtY_AutoRefCurrents_t;

/* Real-time Model Data Structure */
struct tag_RTM_AutoRefCurrents_t {
	ExtU_AutoRefCurrents_t *inputs;
	ExtY_AutoRefCurrents_t *outputs;
	DW_AutoRefCurrents_t *dwork;
};

/* Model entry point functions */
extern void AutoRefCurrents_initialize(RT_MODEL_AutoRefCurrents_t * const rtAutoRefCurrents_M);
extern void AutoRefCurrents_step(RT_MODEL_AutoRefCurrents_t * const rtAutoRefCurrents_M);

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
 * hilite_system('uz_ParameterID/AutoRefCurrents')    - opens subsystem uz_ParameterID/AutoRefCurrents
 * hilite_system('uz_ParameterID/AutoRefCurrents/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID'
 * '<S1>'   : 'uz_ParameterID/AutoRefCurrents'
 */

/*-
 * Requirements for '<Root>': AutoRefCurrents
 */
#endif                                 /* RTW_HEADER_AutoRefCurrents_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
