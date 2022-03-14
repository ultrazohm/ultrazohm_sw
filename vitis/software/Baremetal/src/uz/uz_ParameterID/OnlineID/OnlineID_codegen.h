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
#if UZ_PARAMETERID_MAX_INSTANCES > 0U
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


/**
 * @brief configuration struct for TwoMassID specific settings
 * 
 */
typedef struct {
  boolean_T OnlineID_Reset; /**< flag to reset the OnlineID state*/
  real32_T Temp_ref; /**< reference temperature for identification of the winding temperature of the motor */
  real32_T dev_omega; /**< scale factor to determine the tolerance band for the speed during steady-state detection. Default value is 0.05.*/
  real32_T dev_curr; /**< scale factor to determine the tolerance band for the dq-currents during steady-state detection. Default value is 0.05.*/
  real32_T identRAmp; /**< amplitude for d-current injection signal for identification of linear parameters */
  boolean_T AverageTransParams; /**< flag to enable the averaging of identified linear parameters */
  real32_T nom_factor; /**< eactor for rated current,to determine in which interval the linear Parameters will be identified. i.e. 0.5*I_n */
  real32_T Rs_time; /**< enter value in seconds. Determines, after which time the linear Parameters have to be identified again, even if the currents are outside the interval determined by nom_factor. */
  boolean_T allowPsiCalcOutside; /**< false: Flux maps will only be calculated, if linear parameters have been identified inside the valid range. Flux maps will only be calculated again, if the machine is in the valid range. \n
               true:Flux maps will always be calculated, even if the linear parameters were identified outside of range. */
  real32_T min_n_ratio; /**< factor for rated speed to determine the lower end in which interval the linear Parameters will be identified. i.e. 0.1*n_n. */
  real32_T max_n_ratio; /**< factor for rated speed to determine the upper end in which interval the linear Parameters will be identified. i.e. 0.9*n_n. */
	boolean_T array_cleaned; /**< flag to signal, that the flux map array has been cleaned */
} uz_PID_OnlineIDConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_PID_ActualValues_t_
#define DEFINED_TYPEDEF_FOR_uz_PID_ActualValues_t_

typedef struct {
  uz_3ph_abc_t V_abc;
  uz_3ph_abc_t I_abc;
  uz_3ph_dq_t i_dq;
  uz_3ph_dq_t v_dq;
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
  uz_3ph_dq_t i_dq_ref;
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

/**
 * @brief output struct for OnlineID
 * 
 */
typedef struct {
  real32_T id_out; /**< output for the d-current injection signal */
  real32_T Rph_out; /**< identified online resistance */
  real32_T Wtemp; /**< identified online winding temperature */
  real32_T psi_array[600]; /**< array storing all the measured flux map for each unique operating point of the motor */
  boolean_T IdControlFlag; /**< flag to signal, if the injection d-current is active */
  real32_T delta_psi[200]; /**< array storing the temperature dependent psi_pm values for all the operating points */
  uint16_T activeState; /**< activeState output of the OnlineID state */
  real32_T psi_pm_out; /**< identified Psi_PM */
  real32_T Ld_out; /**< identified Lq */
  real32_T Lq_out; /**< identified Ld */
	boolean_T clean_array; /**< flag to signal, that a new flux measurement point got saved in the array and it needs to be cleaned */
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
  real32_T cleaned_psi_array[600];     /* '<Root>/cleaned_psi_array' */
  uz_PID_OnlineIDConfig_t OnlineIDConfig;/* '<Root>/OnlineIDConfig' */
  uz_PID_ActualValues_t ActualValues;  /* '<Root>/ActualValues' */
  uz_PID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_PID_ControlFlags_t ControlFlags;  /* '<Root>/ControlFlags' */
} ExtU_OnlineID_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uz_PID_OnlineID_output_t OnlineID_output;/* '<Root>/OnlineID_output' */
  boolean_T enteredOnlineID;           /* '<Root>/enteredOnlineID' */
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
