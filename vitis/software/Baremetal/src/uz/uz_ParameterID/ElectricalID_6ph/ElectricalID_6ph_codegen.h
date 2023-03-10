/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID_6ph_codegen.h
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 3.67
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri Mar 10 10:35:35 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "../uz_ParameterID_data.h"

#ifndef RTW_HEADER_ElectricalID_6ph_codegen_h_
#define RTW_HEADER_ElectricalID_6ph_codegen_h_
#include "../rtwtypes.h"
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef ElectricalID_6ph_codegen_COMMON_INCLUDES_
#define ElectricalID_6ph_codegen_COMMON_INCLUDES_
#include "../rtwtypes.h"
#endif                      /* ElectricalID_6ph_codegen_COMMON_INCLUDES_ */

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

#define ElectricalID_6ph_codegen_M     (rtElectricalID_6ph_codegen_M)

/* Forward declaration for rtModel */
typedef struct tag_RTM_ElectricalID_6ph_code_t RT_MODEL_ElectricalID_6ph_cod_t;

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalIDConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalIDConfig_t_

typedef struct {
  real32_T goertzlFreq;
  real32_T dutyCyc;
  real32_T n_ref_measurement;
  boolean_T identLq;
  real32_T goertzlTorque;
  real32_T min_n_ratio;
} uz_ParaID_ElectricalIDConfig_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_ActualValues_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_ActualValues_t_

typedef struct {
  uz_3ph_abc_t V_abc;
  uz_3ph_abc_t I_abc;
  uz_3ph_dq_t i_dq;
  uz_3ph_dq_t v_dq;
  uz_6ph_abc_t v_abc_6ph;
  uz_6ph_abc_t i_abc_6ph;
  uz_6ph_dq_t i_dq_6ph;
  uz_6ph_dq_t v_dq_6ph;
  real32_T omega_m;
  real32_T omega_el;
  real32_T theta_m;
  real32_T theta_el;
  real32_T V_DC;
} uz_ParaID_ActualValues_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_GlobalConfig_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_GlobalConfig_t_

typedef struct {
  uz_PMSM_t PMSM_config;
  uz_6ph_dq_t PMSM_6ph_inductances;
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
  real32_T voltage_measurement_C;
  real32_T voltage_measurement_Rp;
  real32_T voltage_measurement_Rs;
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

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalID_fft_in_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalID_fft_in_t_

typedef struct {
  boolean_T finished_flag;
  real32_T psi_pm_amplitude[5];
  real32_T psi_pm_angle[5];
} uz_ParaID_ElectricalID_fft_in_t;

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

#ifndef DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalID_output_t_
#define DEFINED_TYPEDEF_FOR_uz_ParaID_ElectricalID_output_t_

typedef struct {
  real32_T PWM_Switch_0;
  real32_T PWM_Switch_2;
  real32_T PWM_Switch_4;
  real32_T PWM_Switch_a2;
  real32_T PWM_Switch_b2;
  real32_T PWM_Switch_c2;
  boolean_T enable_TriState[3];
  boolean_T enable_TriState_set_2[3];
  real32_T thetaOffset;
  uz_PMSM_t PMSM_parameters;
  uz_6ph_dq_t inductances_6ph;
  uz_6ph_dq_t resistances_6ph;
  real32_T psi_pm[5];
  real32_T psi_pm_angle[5];
} uz_ParaID_ElectricalID_output_t;

#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  uz_ParaID_ElectricalID_output_t ElectricalID_output;/* '<Root>/ElectricalID_6ph_codegen' */
  uz_ParaID_Controller_Parameters_output_t FOC_out_old;
  real32_T d[2048];                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T measArray1[1024];           /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T i_est[2048];                /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T inv_VSD[36];                /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T Vstep[205];         /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T inv_VSD_n[36];      /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T current_meas_array[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T d_n[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T J[4096];            /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T Vstep_g[205];       /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T inv_VSD_i[36];      /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T current_meas_array_j[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T d_i[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T J_c[4096];          /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T Vstep_j[205];       /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T inv_VSD_a[36];      /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T current_meas_array_i[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T d_h[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T J_p[4096];          /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T Vstep_gw[205];      /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T inv_VSD_m[36];      /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T current_meas_array_n[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T d_l[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T J_cu[4096];         /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T Vstep_e[205];       /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T inv_VSD_l[36];      /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T current_meas_array_a[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T d_o[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T J_h[4096];          /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T Vstep_k[205];        /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T inv_VSD_p[36];       /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T current_meas_array_a4[1024];
                                /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T d_m[2048];           /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T J_o[4096];           /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T i_est_n[2048];
  real32_T setp_abc[6];
  real32_T setp_dq[6];
  real32_T setp_abc_c[6];
  real32_T setp_dq_b[6];
  real32_T H_bn[4];
  real32_T R_est;              /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T L_est;              /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T R_est_m;            /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T L_est_m;            /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T R_est_j;            /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T L_est_i;            /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T R_est_f;            /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T L_est_j;            /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T R_est_a;            /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T L_est_a;            /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T R_est_d;             /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T L_est_e;             /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T bandwidthCurrentControl;    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T dampingFactor;              /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T psiOverJ;                   /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T Kp_iq_loc;                  /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T ia_sum;                     /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T DutyCycle;                  /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T L_est_mb;                   /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T R_est_c;                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T ref_amplitude;              /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T V0;                 /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T V0_g;               /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T V0_k;               /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T V0_n;               /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T V0_nx;              /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T V0_a;                /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T lambda_c;
  real32_T e_h4;
  int32_T i;
  uint32_T one_sec_transition_counter; /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter_j;/* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter_a;/* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter_m;/* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter_l;/* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter_a1;/* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T counter;                    /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T wait_count;                 /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T sineCounter;                /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter_k;/* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T exitPortIndex_m;    /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint32_T counter_i;          /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint32_T exitPortIndex_d;    /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint32_T counter_j;          /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint32_T exitPortIndex_b5;   /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint32_T counter_g;          /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint32_T exitPortIndex_a;    /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint32_T counter_f;          /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint32_T exitPortIndex_ji;   /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint32_T counter_o;          /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint32_T exitPortIndex_p;     /* '<S1>/ElectricalID.Subchart_Step_Response' */
  uint32_T counter_n;           /* '<S1>/ElectricalID.Subchart_Step_Response' */
  uint32_T exitPortIndex;
  uint16_T activeState;        /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint16_T activeState_b;      /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint16_T activeState_d;      /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint16_T activeState_h;      /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint16_T activeState_k;      /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint16_T activeState_hw;      /* '<S1>/ElectricalID.Subchart_Step_Response' */
  uint16_T z;                  /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint16_T z_b;                /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint16_T z_k;                /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint16_T z_p;                /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint16_T z_bs;               /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint16_T z_c;                 /* '<S1>/ElectricalID.Subchart_Step_Response' */
  uint8_T is_active_c3_ElectricalID_6ph_c;/* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_c3_ElectricalID_6ph_codegen;/* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_ElectricalID;             /* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_c14_sfYtI3dVphCWj0yeGcQTjEC_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint8_T is_c14_sgw9yoTrZ3r553R29sM9SRG_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint8_T is_c14_sy7XjnHxVYbhMov5BLWtwrG_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint8_T is_c14_sGmfjfuJTpCF9MYHJTzBOhD_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint8_T is_c14_sl959dG5iVvEfF2XuoR7heD_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint8_T is_c14_sTmeVn9UMjbgIW9tERLCiND_;
                                /* '<S1>/ElectricalID.Subchart_Step_Response' */
  boolean_T DC_valid;                  /* '<Root>/ElectricalID_6ph_codegen' */
} DW_ElectricalID_6ph_codegen_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_ParaID_ElectricalIDConfig_t ElectricalIDConfig;/* '<Root>/ElectricalIDConfig' */
  uz_ParaID_ActualValues_t ActualValues;/* '<Root>/ActualValues' */
  uz_ParaID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_ParaID_ControlFlags_t ControlFlags;/* '<Root>/ControlFlags' */
  uz_ParaID_ElectricalID_fft_in_t ElectricalID_fft_in;/* '<Root>/ElectricalID_fft_in' */
} ExtU_ElectricalID_6ph_codegen_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T enteredElectricalID;       /* '<Root>/enteredElectricalID' */
  boolean_T finishedElectricalID;      /* '<Root>/finishedElectricalID' */
  uz_ParaID_Controller_Parameters_output_t ElectricalID_FOC_output;/* '<Root>/ElectricalID_FOC_output' */
  uz_ParaID_ElectricalID_output_t ElectricalID_output;/* '<Root>/ElectricalID_output' */
  real32_T voltage_meas_array[10000];  /* '<Root>/voltage_meas_array' */
  boolean_T finished_voltage_measurement;
                                     /* '<Root>/finished_voltage_measurement' */
} ExtY_ElectricalID_6ph_codegen_t;

/* Real-time Model Data Structure */
struct tag_RTM_ElectricalID_6ph_code_t {
  ExtU_ElectricalID_6ph_codegen_t *inputs;
  ExtY_ElectricalID_6ph_codegen_t *outputs;
  DW_ElectricalID_6ph_codegen_t *dwork;
};

/* Model entry point functions */
extern void ElectricalID_6ph_codegen_initialize(RT_MODEL_ElectricalID_6ph_cod_t *
  const rtElectricalID_6ph_codegen_M);
extern void ElectricalID_6ph_codegen_step(RT_MODEL_ElectricalID_6ph_cod_t *const
  rtElectricalID_6ph_codegen_M);

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
 * hilite_system('uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen')    - opens subsystem uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen
 * hilite_system('uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID_6ph/ElectricalID6ph'
 * '<S1>'   : 'uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen'
 * '<S2>'   : 'uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response'
 * '<S3>'   : 'uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response1'
 * '<S4>'   : 'uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response2'
 * '<S5>'   : 'uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response3'
 * '<S6>'   : 'uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response4'
 * '<S7>'   : 'uz_ParameterID_6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response5'
 */

/*-
 * Requirements for '<Root>': ElectricalID_6ph_codegen
 */
#endif                              /* RTW_HEADER_ElectricalID_6ph_codegen_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
