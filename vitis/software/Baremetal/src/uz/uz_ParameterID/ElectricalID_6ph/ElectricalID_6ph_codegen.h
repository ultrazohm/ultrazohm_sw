/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID_6ph_codegen.h
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 5.4
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Wed Jan 11 10:19:48 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (12), Warning (1), Error (0)
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



/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  uz_ParaID_ElectricalID_output_t ElectricalID_output;/* '<Root>/ElectricalID_6ph_codegen' */
  uz_ParaID_Controller_Parameters_output_t FOC_out_old;
  real32_T d[2048];                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T measArray1[1024];           /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T i_est[2048];                /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T Vstep[205];         /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T inv_VSD[36];        /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T current_meas_array[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T d_f[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T J[4096];            /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T Vstep_h[205];       /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T inv_VSD_a[36];      /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T current_meas_array_g[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T d_j[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T J_n[4096];          /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T Vstep_n[205];       /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T inv_VSD_f[36];      /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T current_meas_array_b[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T d_p[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T J_d[4096];          /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T Vstep_g[205];       /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T inv_VSD_b[36];      /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T current_meas_array_f[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T d_d[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T J_no[4096];         /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T Vstep_m[205];       /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T inv_VSD_ad[36];     /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T current_meas_array_h[1024];
                               /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T d_i[2048];          /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T J_dy[4096];         /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T Vstep_a[205];        /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T inv_VSD_c[36];       /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T current_meas_array_m[1024];
                                /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T d_e[2048];           /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T J_b[4096];           /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T i_est_j[2048];
  real32_T setp_abc[6];
  real32_T setp_dq[6];
  real32_T H_g[4];
  real32_T R_est;              /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T L_est;              /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T R_est_b;            /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T L_est_a;            /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T R_est_i;            /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T L_est_o;            /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T R_est_e;            /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T L_est_ov;           /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T R_est_if;           /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T L_est_n;            /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T R_est_g;             /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T L_est_e;             /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T bandwidthCurrentControl;    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T dampingFactor;              /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T psiOverJ;                   /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T Kp_iq_loc;                  /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T ia_sum;                     /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T DutyCycle;                  /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T L_est_m;                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T R_est_c;                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T ref_amplitude;              /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T V0;                 /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T V0_c;               /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  real32_T V0_cn;              /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  real32_T V0_l;               /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  real32_T V0_c2;              /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  real32_T V0_p;                /* '<S1>/ElectricalID.Subchart_Step_Response' */
  real32_T lambda_fh;
  real32_T e_c;
  int32_T i;
  int32_T i_k;
  uint32_T counter;                    /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T wait_count;                 /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter; /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T sineCounter;                /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T counter_h;          /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint32_T counter_m;          /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint32_T counter_c;          /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint32_T counter_a;          /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint32_T counter_e;          /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint32_T counter_k;           /* '<S1>/ElectricalID.Subchart_Step_Response' */
  uint32_T qY;
  uint16_T activeState;        /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint16_T activeState_g;      /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint16_T activeState_d;      /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint16_T activeState_dp;     /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint16_T activeState_e;      /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint16_T activeState_l;       /* '<S1>/ElectricalID.Subchart_Step_Response' */
  uint16_T z;                  /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint16_T z_k;                /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint16_T z_b;                /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint16_T z_o;                /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint16_T z_h;                /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint16_T z_d;                 /* '<S1>/ElectricalID.Subchart_Step_Response' */
  uint8_T is_c3_ElectricalID_6ph_codegen;/* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_ElectricalID;             /* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_active_c3_ElectricalID_6ph_c;/* '<Root>/ElectricalID_6ph_codegen' */
  uint8_T is_c14_snPFyo8RP1FEmAhdK88Ic8B_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint8_T is_c14_shbzAwr1BhhrUlaDmVVwCdC_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint8_T is_c14_s2t7IWOBNsHtsCBXqI6F4T_S;
                               /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint8_T is_c14_sxuT7fETqDc5tO7NOEs1UnB_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint8_T is_c14_sLRD80LRGyIIG51knr61Gw_S;
                               /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint8_T is_c14_sZECgD7DKQ40NqV5neBFKO_S;
                                /* '<S1>/ElectricalID.Subchart_Step_Response' */
  boolean_T finished_flag;     /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  boolean_T finished_flag_a;   /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  boolean_T finished_flag_h;   /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  boolean_T finished_flag_l;   /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  boolean_T finished_flag_g;   /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  boolean_T finished_flag_e;    /* '<S1>/ElectricalID.Subchart_Step_Response' */
  boolean_T DC_valid;                  /* '<Root>/ElectricalID_6ph_codegen' */
  boolean_T finish_subsystem;          /* '<Root>/ElectricalID_6ph_codegen' */
} DW_ElectricalID_6ph_codegen_t;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uz_ParaID_ElectricalIDConfig_t ElectricalIDConfig;/* '<Root>/ElectricalIDConfig' */
  uz_ParaID_ActualValues_t ActualValues;/* '<Root>/ActualValues' */
  uz_ParaID_GlobalConfig_t GlobalConfig_out;/* '<Root>/GlobalConfig' */
  uz_ParaID_ControlFlags_t ControlFlags;/* '<Root>/ControlFlags' */
} ExtU_ElectricalID_6ph_codegen_t;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T enteredElectricalID;       /* '<Root>/enteredElectricalID' */
  boolean_T finishedElectricalID;      /* '<Root>/finishedElectricalID' */
  uz_ParaID_Controller_Parameters_output_t ElectricalID_FOC_output;/* '<Root>/ElectricalID_FOC_output' */
  uz_ParaID_ElectricalID_output_t ElectricalID_output;/* '<Root>/ElectricalID_output' */
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
 * hilite_system('uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen')    - opens subsystem uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen
 * hilite_system('uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_ParameterID6ph/ElectricalID6ph'
 * '<S1>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen'
 * '<S2>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response'
 * '<S3>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response1'
 * '<S4>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response2'
 * '<S5>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response3'
 * '<S6>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response4'
 * '<S7>'   : 'uz_ParameterID6ph/ElectricalID6ph/ElectricalID_6ph_codegen/ElectricalID.Subchart_Step_Response5'
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
