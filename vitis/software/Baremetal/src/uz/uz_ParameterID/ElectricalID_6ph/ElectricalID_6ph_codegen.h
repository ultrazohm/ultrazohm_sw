/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ElectricalID_6ph_codegen.h
 *
 * Code generated for Simulink model 'ElectricalID_6ph_codegen'.
 *
 * Model version                  : 3.15
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri Jan 27 14:51:38 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warnings (3), Error (0)
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

struct internal_psi_analysis {
	real32_T analysis;      /* '<Root>/ElectricalID_6ph_codegen' */
	real32_T r;
	real32_T r1;
};


/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  internal_psi_analysis analysis;      /* '<Root>/ElectricalID_6ph_codegen' */
  internal_psi_analysis r;
  internal_psi_analysis r1;
  uz_ParaID_ElectricalID_output_t ElectricalID_output;/* '<Root>/ElectricalID_6ph_codegen' */
  uz_ParaID_Controller_Parameters_output_t c;
  creal32_T Y[10000];
  creal32_T wwc[9999];
  creal32_T ytmp[5000];
  creal32_T reconVar1[5000];
  creal32_T reconVar2[5000];
  creal32_T fy[16384];
  creal32_T fv[16384];
  creal32_T fy_k[16384];
  creal32_T Y_c;
  creal32_T y;
  real32_T d[2048];                    /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T measArray1[1024];           /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T i_est[2048];                /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T voltage_meas_array[10000];  /* '<Root>/ElectricalID_6ph_codegen' */
  real32_T Vstep[205];         /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  real32_T inv_VSD[36];        /* '<S1>/ElectricalID.Subchart_Step_Response5' */
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
  real32_T P2[10000];
  real32_T sintabinv[16385];
  real32_T costab1q[8193];
  real32_T costab[16385];
  real32_T sintab[16385];
  real32_T hcostab[8192];
  real32_T hsintab[8192];
  real32_T hcostabinv[8192];
  real32_T hsintabinv[8192];
  real32_T costab1q_b[5001];
  real32_T costable[10001];
  real32_T sintable[10001];
  real32_T setp_abc[6];
  real32_T setp_dq[6];
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
  real32_T x_re;
  real32_T x_im;
  real32_T nt_im;
  real32_T sintabinv_tmp;
  real32_T temp_re;
  real32_T temp_im;
  real32_T twid_re;
  real32_T twid_im;
  real32_T reconVar1_im;
  real32_T costable_tmp;
  real32_T ytmp_re_tmp;
  real32_T ytmp_im_tmp;
  int32_T i;
  int32_T i_p;
  int32_T idx;
  int32_T rt;
  int32_T y_c;
  int32_T idx_f;
  int32_T b_idx;
  int32_T ix;
  int32_T iy;
  int32_T h_i;
  int32_T b_istart;
  int32_T b_j;
  int32_T b_ihi;
  int32_T i_g;
  int32_T ix_g;
  int32_T iy_m;
  uint32_T counter;                    /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T wait_count;                 /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T one_sec_transition_counter; /* '<Root>/ElectricalID_6ph_codegen' */
  uint32_T sineCounter;                /* '<Root>/ElectricalID_6ph_codegen' */
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
  uint8_T is_c14_sQ4F4aYAfnRuwrnP5W0JnuE_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response5' */
  uint8_T is_c14_sTK5oN2u41FtyrTT3M4LBvD_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response4' */
  uint8_T is_c14_sei0wtTtu3rWzJvdVkbw0IB_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response3' */
  uint8_T is_c14_sm7bGqwGrGWaAT4sjTM7K5B_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response2' */
  uint8_T is_c14_sJ2fckg9tfxlA3RfEdiBHFB_;
                               /* '<S1>/ElectricalID.Subchart_Step_Response1' */
  uint8_T is_c14_s3sY6TQNXW104EzFIbsrQcG_;
                                /* '<S1>/ElectricalID.Subchart_Step_Response' */
  boolean_T DC_valid;                  /* '<Root>/ElectricalID_6ph_codegen' */
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
