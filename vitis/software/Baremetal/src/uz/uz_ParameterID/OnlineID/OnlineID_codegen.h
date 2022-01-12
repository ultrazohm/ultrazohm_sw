/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OnlineID.h
 *
 * Code generated for Simulink model 'OnlineID'.
 *
 * Model version                  : 2.371
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Dec 20 12:50:35 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_ACTIVE > 0U
#include "../../uz_PMSM_config/uz_PMSM_config.h"
#include "../../uz_Transformation/uz_Transformation.h"

#ifndef RTW_HEADER_OnlineID_h_
#define RTW_HEADER_OnlineID_h_
#include "../rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef OnlineID_COMMON_INCLUDES_
#define OnlineID_COMMON_INCLUDES_
#include "../rtwtypes.h"
#endif                                 /* OnlineID_COMMON_INCLUDES_ */

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

#define OnlineID_M                     (rtOnlineID_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_OnlineID_t RT_MODEL_OnlineID_t;

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_OnlineIDConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_OnlineIDConfig_t_

typedef struct {
  boolean_T OnlineID_Reset;
  real32_T Temp_ref;
  real32_T dev_omega;
  real32_T dev_curr;
  real32_T identRAmp;
  boolean_T AverageTransParams;
  real32_T nom_factor;
  real32_T Rs_time;
  boolean_T allowPsiCalcOutside;
  real32_T min_n_ratio;
  real32_T max_n_ratio;
	boolean_T array_cleaned;
} uz_PID_OnlineIDConfig_t;

#endif

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
  real32_T thetaOffset;
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

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_OnlineID_output_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_OnlineID_output_t_

typedef struct {
  real32_T id_out;
  real32_T Rph_out;
  real32_T Wtemp;
  real32_T psi_array[600];
  boolean_T IdControlFlag;
  real32_T iq_mean_out;
  real32_T id_mean_out;
  real32_T delta_psi[200];
  uint16_T activeState;
  real32_T psi_pm_out;
  real32_T Ld_out;
  real32_T Lq_out;
	boolean_T clean_array;
} uz_PID_OnlineID_output_t;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real32_T omega_register[5];          /* '<Root>/OnlineID' */
  real32_T vd_register[50];            /* '<Root>/OnlineID' */
  real32_T vq_register[50];            /* '<Root>/OnlineID' */
  real32_T id_register[50];            /* '<Root>/OnlineID' */
  real32_T iq_register[50];            /* '<Root>/OnlineID' */
  real32_T iq_register_alt[50];        /* '<Root>/OnlineID' */
  real32_T iq_register_neu[10];        /* '<Root>/OnlineID' */
  real32_T omega_register_alt[5];      /* '<Root>/OnlineID' */
  real32_T omega_register_neu[5];      /* '<Root>/OnlineID' */
  real32_T id_register_alt[50];        /* '<Root>/OnlineID' */
  real32_T id_register_neu[10];        /* '<Root>/OnlineID' */
  real32_T d_y[50];
  real32_T e_y[50];
  real32_T c_y[50];
  real32_T d_y_m[50];
  real32_T g_y[10];
  real32_T h_y[10];
  real32_T f_y[5];
  real32_T i_y[5];
  real32_T e_y_c[5];
  real32_T breakback;                  /* '<Root>/OnlineID' */
  real32_T i_d_R_online;               /* '<Root>/OnlineID' */
  real32_T omega_sum;                  /* '<Root>/OnlineID' */
  real32_T id_sum;                     /* '<Root>/OnlineID' */
  real32_T iq_sum;                     /* '<Root>/OnlineID' */
  real32_T vq_sum;                     /* '<Root>/OnlineID' */
  real32_T vd_sum;                     /* '<Root>/OnlineID' */
  real32_T id1counter;                 /* '<Root>/OnlineID' */
  real32_T id2counter;                 /* '<Root>/OnlineID' */
  real32_T iq1counter;                 /* '<Root>/OnlineID' */
  real32_T iq2counter;                 /* '<Root>/OnlineID' */
  real32_T omega1counter;              /* '<Root>/OnlineID' */
  real32_T omega2counter;              /* '<Root>/OnlineID' */
  real32_T Vd1counter;                 /* '<Root>/OnlineID' */
  real32_T Vd2counter;                 /* '<Root>/OnlineID' */
  real32_T Vq1counter;                 /* '<Root>/OnlineID' */
  real32_T Vq2counter;                 /* '<Root>/OnlineID' */
  real32_T R_old;                      /* '<Root>/OnlineID' */
  real32_T R_veryold;                  /* '<Root>/OnlineID' */
  real32_T PsiPm_old;                  /* '<Root>/OnlineID' */
  real32_T PsiPm_veryold;              /* '<Root>/OnlineID' */
  real32_T Ld_old;                     /* '<Root>/OnlineID' */
  real32_T Ld_veryold;                 /* '<Root>/OnlineID' */
  real32_T Lq_old;                     /* '<Root>/OnlineID' */
  real32_T Lq_veryold;                 /* '<Root>/OnlineID' */
  real32_T R_old_outside;              /* '<Root>/OnlineID' */
  real32_T Ld_old_outside;             /* '<Root>/OnlineID' */
  real32_T Lq_old_outside;             /* '<Root>/OnlineID' */
  real32_T PsiPm_old_outside;          /* '<Root>/OnlineID' */
  uint32_T counter;                    /* '<Root>/OnlineID' */
  uint32_T counter_time;               /* '<Root>/OnlineID' */
  uint16_T counter_ausserhalb;         /* '<Root>/OnlineID' */
  uint16_T counter_innerhalb;          /* '<Root>/OnlineID' */
  uint8_T is_active_c5_OnlineID;       /* '<Root>/OnlineID' */
  uint8_T is_c5_OnlineID;              /* '<Root>/OnlineID' */
  uint8_T is_OnlineIDSuperState;       /* '<Root>/OnlineID' */
  boolean_T omega_const;               /* '<Root>/OnlineID' */
  boolean_T iq_const;                  /* '<Root>/OnlineID' */
  boolean_T id_const;                  /* '<Root>/OnlineID' */
  boolean_T allow_meas;                /* '<Root>/OnlineID' */
  boolean_T i_valid;                   /* '<Root>/OnlineID' */
  boolean_T LinPara_ident_outside;     /* '<Root>/OnlineID' */
  boolean_T stop_ident;                /* '<Root>/OnlineID' */
} DW_OnlineID_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
	real32_T cleaned_psi_array[600]; /* '<Root>/cleaned_psi_array' */
  uz_PID_OnlineIDConfig_t OnlineIDConfig;/* '<Root>/OnlineIDConfig' */
  uz_PID_ActualValues_t ActualValues;  /* '<Root>/ActualValues' */
  uz_PID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_PID_ControlFlags_t ControlFlags;  /* '<Root>/ControlFlags' */
} ExtU_OnlineID_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uz_PID_OnlineID_output_t OnlineID_output;/* '<Root>/OnlineID_output' */
} ExtY_OnlineID_t;

/* Real-time Model Data Structure */
struct tag_RTM_OnlineID_t {
  ExtU_OnlineID_t *inputs;
  ExtY_OnlineID_t *outputs;
  DW_OnlineID_t *dwork;
};

/* Model entry point functions */
extern void OnlineID_initialize(RT_MODEL_OnlineID_t *const rtOnlineID_M);
extern void OnlineID_step(RT_MODEL_OnlineID_t *const rtOnlineID_M);

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
 * hilite_system('uz_ParameterID/OnlineID')    - opens subsystem uz_ParameterID/OnlineID
 * hilite_system('uz_ParameterID/OnlineID/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID'
 * '<S1>'   : 'uz_ParameterID/OnlineID'
 */

/*-
 * Requirements for '<Root>': OnlineID
 */
#endif                                 /* RTW_HEADER_OnlineID_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
