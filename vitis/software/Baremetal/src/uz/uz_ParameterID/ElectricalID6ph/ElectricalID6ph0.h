/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID6ph0.h
 *
 * Code generated for Simulink model 'ElectricalID6ph0'.
 *
 * Model version                  : 2.679
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Nov 21 09:26:17 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_ElectricalID6ph0_h_
#define RTW_HEADER_ElectricalID6ph0_h_
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "uz_PMSM_config.h"
#include "uz_Transformation.h"
#include <stddef.h>
#ifndef ElectricalID6ph0_COMMON_INCLUDES_
#define ElectricalID6ph0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ElectricalID6ph0_COMMON_INCLUDES_ */

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

#define ElectricalID6ph0_M             (rtElectricalID6ph0_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_ElectricalID6ph0_t RT_MODEL_ElectricalID6ph0_t;

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_GlobalConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_GlobalConfig_t_

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
  uz_3ph_dq_t i_dq_ref;
  real32_T n_ref;
} uz_ParaID_GlobalConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_ControlFlags_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_ControlFlags_t_

typedef struct {
  boolean_T startFrictionID;
  boolean_T startElectricalID;
  boolean_T startTwoMassID;
  boolean_T startFluxMapID;
  uint16_T transNr;
  boolean_T enableOnlineID;
  boolean_T finished_all_Offline_states;
} uz_ParaID_ControlFlags_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalIDConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalIDConfig_t_

typedef struct {
  real32_T goertzlFreq;
  real32_T dutyCyc;
  real32_T n_ref_measurement;
  boolean_T identLq;
  real32_T goertzlAmp;
  real32_T min_n_ratio;
} uz_ParaID_ElectricalIDConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID6ph_ActualValues_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID6ph_ActualValues_t_

typedef struct {
  uz_6ph_abc_t V_abc;
  uz_6ph_abc_t I_abc;
  uz_6ph_dq_t i_dq;
  uz_6ph_dq_t v_dq;
  real32_T omega_m;
  real32_T omega_el;
  real32_T theta_m;
  real32_T theta_el;
  real32_T V_DC;
} uz_ParaID6ph_ActualValues_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_Controller_Parameters_output_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_Controller_Parameters_output_t_

typedef struct {
  uz_3ph_dq_t i_dq_ref;
  uint16_T activeState;
  real32_T n_ref_FOC;
  boolean_T enableFOC_speed;
  boolean_T enableFOC_current;
  boolean_T resetIntegrator;
  real32_T Kp_id_out;
  real32_T Kp_iq_out;
  real32_T Kp_n_out;
  real32_T Ki_id_out;
  real32_T Ki_iq_out;
  real32_T Ki_n_out;
} uz_ParaID_Controller_Parameters_output_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalID6ph_output_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalID6ph_output_t_

typedef struct {
  real32_T PWM_Switch_a1;
  real32_T PWM_Switch_b1;
  real32_T PWM_Switch_c1;
  real32_T PWM_Switch_a2;
  real32_T PWM_Switch_b2;
  real32_T PWM_Switch_c2;
  boolean_T enable_TriState[3];
  real32_T thetaOffset;
  uz_PMSM_t PMSM_parameters;
} uz_ParaID_ElectricalID6ph_output_t;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  uz_ParaID6ph_ActualValues_t BusConversion_InsertedFor_Elect;
  uz_6ph_abc_t ActualVabc;             /* '<S1>/ElectricalID6ph' */
  uz_6ph_alphabeta_t current;          /* '<S1>/ElectricalID6ph' */
  uz_ParaID_ElectricalIDConfig_t BusConversion_InsertedFor_Ele_n;
  real32_T H[4];                       /* '<S1>/ElectricalID6ph' */
  real32_T omega_register[5];          /* '<S1>/ElectricalID6ph' */
  real32_T d[2048];                    /* '<S1>/ElectricalID6ph' */
  real32_T i_est[2048];                /* '<S1>/ElectricalID6ph' */
  real32_T J[4096];                    /* '<S1>/ElectricalID6ph' */
  real32_T Vstep[205];                 /* '<S1>/ElectricalID6ph' */
  real32_T measArray1[1024];           /* '<S1>/ElectricalID6ph' */
  real32_T fv[2048];
  real32_T fv1[2048];
  real32_T fv2[6];
  real32_T fv3[6];
  real32_T fv4[4];
  real32_T fv5[2];
  real32_T abc_vector[6];
  real32_T e;                          /* '<S1>/ElectricalID6ph' */
  real32_T lambda;                     /* '<S1>/ElectricalID6ph' */
  real32_T V0;                         /* '<S1>/ElectricalID6ph' */
  real32_T R_corr;                     /* '<S1>/ElectricalID6ph' */
  real32_T bandwidthCurrentControl;    /* '<S1>/ElectricalID6ph' */
  real32_T dampingFactor;              /* '<S1>/ElectricalID6ph' */
  real32_T psiOverJ;                   /* '<S1>/ElectricalID6ph' */
  real32_T Kp_iq_loc;                  /* '<S1>/ElectricalID6ph' */
  real32_T omega_sum;                  /* '<S1>/ElectricalID6ph' */
  real32_T ia_sum;                     /* '<S1>/ElectricalID6ph' */
  real32_T DutyCycle;                  /* '<S1>/ElectricalID6ph' */
  real32_T ref_amplitude;              /* '<S1>/ElectricalID6ph' */
  real32_T R_est;
  real32_T L_est;
  real32_T R_est_m;
  real32_T L_est_c;
  int32_T i;
  uint32_T counter;                    /* '<S1>/ElectricalID6ph' */
  uint32_T wait_count;                 /* '<S1>/ElectricalID6ph' */
  uint32_T one_sec_transition_counter; /* '<S1>/ElectricalID6ph' */
  uint32_T sineCounter;                /* '<S1>/ElectricalID6ph' */
  uint16_T n_iters;                    /* '<S1>/ElectricalID6ph' */
  uint16_T z;                          /* '<S1>/ElectricalID6ph' */
  uint8_T is_active_c3_ElectricalID6ph0;/* '<S1>/ElectricalID6ph' */
  uint8_T is_c3_ElectricalID6ph0;      /* '<S1>/ElectricalID6ph' */
  uint8_T is_ElectricalID;             /* '<S1>/ElectricalID6ph' */
  boolean_T updateJ;                   /* '<S1>/ElectricalID6ph' */
  boolean_T om_con;                    /* '<S1>/ElectricalID6ph' */
  boolean_T ia_valid;                  /* '<S1>/ElectricalID6ph' */
  boolean_T DC_manual;                 /* '<S1>/ElectricalID6ph' */
} DW_ElectricalID6ph0_t;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: VSD
   * Referenced by: '<S1>/ElectricalID6ph'
   */
  real32_T ElectricalID6ph_VSD[36];

  /* Expression: inv_VSD
   * Referenced by: '<S1>/ElectricalID6ph'
   */
  real32_T ElectricalID6ph_inv_VSD[36];
} ConstP_ElectricalID6ph0_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_ParaID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_ParaID_ControlFlags_t ControlFlags;/* '<Root>/ControlFlags' */
  real32_T goertzlFreq;                /* '<Root>/goertzlFreq' */
  real32_T dutyCyc;                    /* '<Root>/dutyCyc' */
  real32_T n_ref_measurement;          /* '<Root>/n_ref_measurement' */
  boolean_T identLq;                   /* '<Root>/identLq' */
  real32_T goertzlAmp;                 /* '<Root>/goertzlAmp' */
  real32_T min_n_ratio;                /* '<Root>/min_n_ratio' */
  real32_T a1;                         /* '<Root>/a1' */
  real32_T b1;                         /* '<Root>/b1' */
  real32_T c1;                         /* '<Root>/c1' */
  real32_T a2;                         /* '<Root>/a2' */
  real32_T b2;                         /* '<Root>/b2' */
  real32_T c2;                         /* '<Root>/c2' */
  real32_T a1_n;                       /* '<Root>/a1b' */
  real32_T b1_c;                       /* '<Root>/b1b' */
  real32_T c1_i;                       /* '<Root>/c1b' */
  real32_T a2_k;                       /* '<Root>/a2b' */
  real32_T b2_f;                       /* '<Root>/b2b' */
  real32_T c2_d;                       /* '<Root>/c2b' */
  real32_T d;                          /* '<Root>/d' */
  real32_T q;                          /* '<Root>/q' */
  real32_T x;                          /* '<Root>/x' */
  real32_T y;                          /* '<Root>/y' */
  real32_T z1;                         /* '<Root>/z1' */
  real32_T z2;                         /* '<Root>/z2' */
  real32_T d_b;                        /* '<Root>/db' */
  real32_T q_n;                        /* '<Root>/qb' */
  real32_T x_i;                        /* '<Root>/xb' */
  real32_T y_p;                        /* '<Root>/yb' */
  real32_T z1_f;                       /* '<Root>/z1b' */
  real32_T z2_i;                       /* '<Root>/z2b' */
  real32_T omega_m;                    /* '<Root>/omega_m' */
  real32_T omega_el;                   /* '<Root>/omega_el' */
  real32_T theta_m;                    /* '<Root>/theta_m' */
  real32_T theta_el;                   /* '<Root>/theta_el' */
  real32_T V_DC;                       /* '<Root>/V_DC' */
} ExtU_ElectricalID6ph0_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T enteredElectricalID;       /* '<Root>/enteredElectricalID' */
  boolean_T finishedElectricalID;      /* '<Root>/finishedElectricalID' */
  uz_ParaID_ElectricalID6ph_output_t ElectricalID_output;/* '<Root>/ElectricalID_output' */
  uz_ParaID_Controller_Parameters_output_t ElectricalID_FOC_output;/* '<Root>/ElectricalID_FOC_output' */
} ExtY_ElectricalID6ph0_t;

/* Real-time Model Data Structure */
struct tag_RTM_ElectricalID6ph0_t {
  ExtU_ElectricalID6ph0_t *inputs;
  ExtY_ElectricalID6ph0_t *outputs;
  DW_ElectricalID6ph0_t *dwork;
};

/* Constant parameters (default storage) */
extern const ConstP_ElectricalID6ph0_t rtElectricalID6ph0_ConstP;

/* Model entry point functions */
extern void ElectricalID6ph0_initialize(RT_MODEL_ElectricalID6ph0_t *const
  rtElectricalID6ph0_M);
extern void ElectricalID6ph0_step(RT_MODEL_ElectricalID6ph0_t *const
  rtElectricalID6ph0_M);

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
 * hilite_system('uz_ParameterID6ph/ElectricalID6ph')    - opens subsystem uz_ParameterID6ph/ElectricalID6ph
 * hilite_system('uz_ParameterID6ph/ElectricalID6ph/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID6ph'
 * '<S1>'   : 'uz_ParameterID6ph/ElectricalID6ph'
 * '<S2>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID6ph'
 */

/*-
 * Requirements for '<Root>': ElectricalID6ph0
 */
#endif                                 /* RTW_HEADER_ElectricalID6ph0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
