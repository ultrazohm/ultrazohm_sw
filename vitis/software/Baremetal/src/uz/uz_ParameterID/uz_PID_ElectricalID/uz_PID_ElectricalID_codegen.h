/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID.h
 *
 * Code generated for Simulink model 'ElectricalID'.
 *
 * Model version                  : 2.17
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Nov 22 16:19:12 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U

#ifndef RTW_HEADER_ElectricalID_h_
#define RTW_HEADER_ElectricalID_h_
#include "../rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef ElectricalID_COMMON_INCLUDES_
#define ElectricalID_COMMON_INCLUDES_
#include "../rtwtypes.h"
#endif                                 /* ElectricalID_COMMON_INCLUDES_ */

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

#define ElectricalID_M                 (rtElectricalID_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_ElectricalID_t RT_MODEL_ElectricalID_t;

#ifndef DEFINED_TYPEDEF_FOR_ElectricalIDConfig_
#define DEFINED_TYPEDEF_FOR_ElectricalIDConfig_

typedef struct {
  real32_T dutyCyc;
  real32_T n_ref_measurement;
  boolean_T identLq;
  real32_T goertzlAmp;
  real32_T min_n_ratio;
} ElectricalIDConfig;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ActualValues_
#define DEFINED_TYPEDEF_FOR_ActualValues_

typedef struct {
  real32_T i_a;
  real32_T i_b;
  real32_T i_c;
  real32_T omega_m;
  real32_T omega_el;
  real32_T theta_m;
  real32_T u_a;
  real32_T u_b;
  real32_T u_c;
  real32_T U_zk;
  real32_T u_d;
  real32_T u_q;
  real32_T i_d;
  real32_T i_q;
} ActualValues;

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

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T H[4];                       /* '<Root>/ElectricalID' */
  real32_T omega_register[5];          /* '<Root>/ElectricalID' */
  real32_T d[2048];                    /* '<Root>/ElectricalID' */
  real32_T i_est[2048];                /* '<Root>/ElectricalID' */
  real32_T J[4096];                    /* '<Root>/ElectricalID' */
  real32_T Ustep[205];                 /* '<Root>/ElectricalID' */
  real32_T measArray1[1024];           /* '<Root>/ElectricalID' */
  real32_T fv[2048];
  real32_T fv1[2048];
	real32_T fv2[4];
	real32_T fv3[2];
	real32_T fv4[4];
	real32_T fv5[2];
  real32_T e;                          /* '<Root>/ElectricalID' */
  real32_T lambda;                     /* '<Root>/ElectricalID' */
  real32_T U0;                         /* '<Root>/ElectricalID' */
  real32_T R_corr;                     /* '<Root>/ElectricalID' */
  real32_T bandwidthCurrentControl;    /* '<Root>/ElectricalID' */
  real32_T dampingFactor;              /* '<Root>/ElectricalID' */
  real32_T psiOverJ;                   /* '<Root>/ElectricalID' */
  real32_T Kp_n_loc;                   /* '<Root>/ElectricalID' */
  real32_T Ki_n_loc;                   /* '<Root>/ElectricalID' */
  real32_T Kp_iq_loc;                  /* '<Root>/ElectricalID' */
  real32_T omega_sum;                  /* '<Root>/ElectricalID' */
  real32_T ia_sum;                     /* '<Root>/ElectricalID' */
  real32_T DutyCycle;                  /* '<Root>/ElectricalID' */
	int32_T i;
  uint32_T counter;                    /* '<Root>/ElectricalID' */
  uint32_T wait_count;                 /* '<Root>/ElectricalID' */
  uint16_T n_iters;                    /* '<Root>/ElectricalID' */
  uint16_T z;                          /* '<Root>/ElectricalID' */
  uint16_T temporalCounter_i1;         /* '<Root>/ElectricalID' */
	uint8_T is_active_c3_ElectricalID; /* '<Root>/ElectricalID' */
	uint8_T is_c3_ElectricalID; /* '<Root>/ElectricalID' */
	uint8_T is_ElectricalID; /* '<Root>/ElectricalID' */
	boolean_T updateJ; /* '<Root>/ElectricalID' */
	boolean_T om_con; /* '<Root>/ElectricalID' */
	boolean_T ia_valid; /* '<Root>/ElectricalID' */
	boolean_T DC_manual; /* '<Root>/ElectricalID' */
} DW_ElectricalID_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
	ElectricalIDConfig ElectricalIDConfig_l;/* '<Root>/ElectricalIDConfig' */
	ActualValues ActualValues_i; /* '<Root>/ActualValues' */
  GlobalConfig GlobalConfig_out;       /* '<Root>/GlobalConfig' */
	ControlFlags ControlFlags_o; /* '<Root>/ControlFlags' */
} ExtU_ElectricalID_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T enteredElectricalID;       /* '<Root>/enteredElectricalID' */
  boolean_T finishedElectricalID;      /* '<Root>/finishedElectricalID' */
  State_FOC_output ElectricalID_FOC_output;/* '<Root>/ElectricalID_FOC_output' */
	ElectricalID_output ElectricalID_output_o;/* '<Root>/ElectricalID_output' */
} ExtY_ElectricalID_t;

/* Real-time Model Data Structure */
struct tag_RTM_ElectricalID_t {
	ExtU_ElectricalID_t *inputs;
	ExtY_ElectricalID_t *outputs;
	DW_ElectricalID_t *dwork;
};

/* Model entry point functions */
extern void ElectricalID_initialize(RT_MODEL_ElectricalID_t * const rtElectricalID_M);
extern void ElectricalID_step(RT_MODEL_ElectricalID_t * const rtElectricalID_M);

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
 * hilite_system('uz_ParameterID/ElectricalID')    - opens subsystem uz_ParameterID/ElectricalID
 * hilite_system('uz_ParameterID/ElectricalID/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID'
 * '<S1>'   : 'uz_ParameterID/ElectricalID'
 */

/*-
 * Requirements for '<Root>': ElectricalID
 */
#endif                                 /* RTW_HEADER_ElectricalID_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
