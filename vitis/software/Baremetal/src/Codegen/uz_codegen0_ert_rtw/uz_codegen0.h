/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.13
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Aug 28 17:00:06 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#ifndef RTW_HEADER_uz_codegen0_h_
#define RTW_HEADER_uz_codegen0_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef uz_codegen0_COMMON_INCLUDES_
#define uz_codegen0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* uz_codegen0_COMMON_INCLUDES_ */

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

#define uz_codegen0_M                  (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T d[64];
  real32_T Delay13_DSTATE[7];          /* '<S1>/Delay13' */
  real32_T Delay_DSTATE[4];            /* '<S1>/Delay' */
  real32_T Delay9_DSTATE[4];           /* '<S1>/Delay9' */
  real32_T Delay10_DSTATE[4];          /* '<S1>/Delay10' */
  real32_T Delay11_DSTATE[4];          /* '<S1>/Delay11' */
  real32_T Delay12_DSTATE[4];          /* '<S1>/Delay12' */
  real32_T Delay1_DSTATE[7];           /* '<S1>/Delay1' */
  real32_T Delay3_DSTATE[4];           /* '<S1>/Delay3' */
  real32_T Delay4_DSTATE[4];           /* '<S1>/Delay4' */
  real32_T Delay5_DSTATE[4];           /* '<S1>/Delay5' */
  real32_T Delay6_DSTATE[4];           /* '<S1>/Delay6' */
  real32_T Delay7_DSTATE[4];           /* '<S1>/Delay7' */
  real32_T Delay8_DSTATE[4];           /* '<S1>/Delay8' */
  real32_T x_e[8];                     /* '<S1>/Observer' */
  real32_T P_e[64];                    /* '<S1>/Observer' */
  real32_T M[196];                     /* '<S1>/formulate_qp' */
  real32_T A[64];
  real32_T A_m[64];
  real32_T A_c[64];
  real32_T Linv_data[49];
  real32_T Hinv_data[49];
  real32_T RLinv_data[49];
  real32_T D_data[49];
  real32_T H_data[49];
  real32_T U_data[49];
  real32_T TL_data[49];
  real32_T Q_data[49];
  real32_T R_data[49];
  real32_T A_data[49];
  real32_T b_A_tmp[32];
  real32_T r[28];                      /* '<S1>/formulate_qp' */
  real32_T A_k[16];
  real32_T B_c[16];
  real32_T fv[16];
  real32_T Opt_data[14];
  real32_T Rhs_data[14];
  real32_T x_p[8];
  real32_T A_b[8];
  real32_T fv1[8];
  real32_T cTol[8];
  real32_T x_data[7];
  real32_T fv2[7];
  real32_T r_data[7];
  real32_T AcRow[7];
  real32_T z_data[7];
  real32_T tau_data[7];
  real32_T Ac[7];
  real32_T work_data[7];
  real32_T t[6];
  real32_T tz[6];                      /* '<S1>/tz' */
  real32_T D[4];
  real32_T E[4];
  real32_T v_t0[4];                    /* '<S1>/v_dqxy' */
  real32_T m6[4];                      /* '<S1>/state_space_mdl' */
  real32_T m1[4];                      /* '<S1>/state_space_mdl' */
  real32_T m2[4];                      /* '<S1>/state_space_mdl' */
  real32_T m3[4];                      /* '<S1>/state_space_mdl' */
  real32_T m4[4];                      /* '<S1>/state_space_mdl' */
  real32_T E_p[4];
  real32_T E_c[4];
  real32_T work_data_f[7];
  real32_T w6theta_el;
  real32_T q;
  real32_T SinCos1_o2;                 /* '<S1>/SinCos1' */
  real32_T SinCos2_o1;                 /* '<S1>/SinCos2' */
  real32_T SinCos2_o2;                 /* '<S1>/SinCos2' */
  real32_T rtb_e_dq_obs_g;
  real32_T rtb_e_xy_obs_g;
  real32_T rtb_i_dq_obs_idx_0;
  real32_T rtb_e_dq_obs_idx_0;
  real32_T rtb_e_xy_obs_idx_0;
  real32_T rtb_v_1_idx_pu_idx_1;
  real32_T rtb_v_1_idx_pu_idx_3;
  real32_T rtb_v_2_idx_pu_idx_0;
  real32_T rtb_v_2_idx_pu_idx_1;
  real32_T rtb_v_2_idx_pu_idx_2;
  real32_T rtb_v_2_idx_pu_idx_3;
  real32_T rtb_v_3_idx_pu_idx_0;
  real32_T rtb_v_3_idx_pu_idx_1;
  real32_T rtb_v_3_idx_pu_idx_2;
  real32_T rtb_v_3_idx_pu_idx_3;
  real32_T rtb_v_4_idx_pu_idx_0;
  real32_T rtb_v_4_idx_pu_idx_1;
  real32_T rtb_v_4_idx_pu_idx_2;
  real32_T rtb_v_4_idx_pu_idx_3;
  real32_T rtb_v_5_idx_pu_idx_0;
  real32_T rtb_v_5_idx_pu_idx_1;
  real32_T rtb_v_5_idx_pu_idx_2;
  real32_T rtb_v_5_idx_pu_idx_3;
  real32_T x0_idx_0;
  real32_T x0_idx_1;
  real32_T x0_idx_2;
  real32_T x0_idx_3;
  real32_T rtb_SinCos2_o1_tmp;
  real32_T A_tmp;
  real32_T rtb_SinCos2_o2_tmp;
  real32_T rMin;
  real32_T Xnorm0;
  real32_T cMin;
  real32_T cVal;
  real32_T t_m;
  real32_T Linv;
  real32_T b_atmp;
  real32_T beta1;
  int32_T Linv_size[2];
  int32_T Hinv_size[2];
  int32_T RLinv_size[2];
  int32_T D_size[2];
  int32_T H_size[2];
  int32_T U_size[2];
  int32_T Q_size[2];
  int32_T A_size[2];
  int32_T kBcol;
  int32_T c;
  int32_T ix;
  int32_T b_ix;
  int32_T iy;
  int32_T c_ix;
  int32_T ijA;
  int32_T ia;
  int32_T sector_ref;                  /* '<S1>/deadbeat_solution' */
  int32_T i;
  int32_T x_size;
  int32_T i_n;
  int32_T H;
  int32_T loop_ub;
  int32_T i_p;
  int32_T i1;
  int32_T lambda_tmp_tmp;
  int32_T z_size;
  int32_T m;
  int32_T b_n;
  int32_T h_j;
  int32_T RLinv;
  int32_T tau_size;
  int32_T R_size_idx_0;
  int32_T TL_size_idx_0;
  int32_T m_l;
  int32_T n;
  int32_T minmana;
  int32_T minmn;
  int32_T ii;
  int32_T mmi;
  int32_T mmip1;
  int32_T i_j;
  int32_T i_d;
  int32_T itau;
  int32_T iaii;
  int32_T c_c;
  int32_T lastv;
  int16_T iA1[8];
  int16_T iC[8];
  int8_T b_I_data[49];
  int8_T b_A_tmp_g[32];
  int8_T b_A_tmp_l[32];
  int8_T act_sw_1[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_2[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_3[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_4[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_5[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T rtb_m6_tmp[16];
  int8_T ipiv[4];
  boolean_T icLoad;                    /* '<S1>/Delay13' */
  boolean_T icLoad_j;                  /* '<S1>/Delay1' */
  boolean_T icLoad_a;                  /* '<S1>/Delay3' */
  boolean_T icLoad_g;                  /* '<S1>/Delay4' */
  boolean_T icLoad_k;                  /* '<S1>/Delay5' */
  boolean_T icLoad_m;                  /* '<S1>/Delay6' */
  boolean_T icLoad_d;                  /* '<S1>/Delay7' */
  boolean_T icLoad_kw;                 /* '<S1>/Delay8' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T v_DC_pu;                    /* '<Root>/v_DC_pu' */
  real32_T theta_el_pos;               /* '<Root>/theta_el_pos' */
  real32_T theta_el_neg;               /* '<Root>/theta_el_neg' */
  real32_T Ts_times_ZB_over_Ld;        /* '<Root>/Ts_times_ZB_over_Ld' */
  real32_T Ts_times_ZB_over_Lq;        /* '<Root>/Ts_times_ZB_over_Lq' */
  real32_T Ts_times_ZB_over_Lx;        /* '<Root>/Ts_times_ZB_over_Lx' */
  real32_T Ts_times_ZB_over_Ly;        /* '<Root>/Ts_times_ZB_over_Ly' */
  real32_T Rs_over_ZB;                 /* '<Root>/Rs_over_ZB' */
  real32_T Ld_over_LB;                 /* '<Root>/Ld_over_LB' */
  real32_T Lq_over_LB;                 /* '<Root>/Lq_over_LB' */
  real32_T Lx_over_LB;                 /* '<Root>/Lx_over_LB' */
  real32_T Ly_over_LB;                 /* '<Root>/Ly_over_LB' */
  real32_T psi_pm_over_psiB;           /* '<Root>/psi_pm_over_psiB' */
  real32_T omega_el_pu;                /* '<Root>/omega_el_pu' */
  real32_T i_dq_pu[2];                 /* '<Root>/i_dq_pu' */
  real32_T i_xy_pu[2];                 /* '<Root>/i_xy_pu' */
  real32_T i_d_ref_pu;                 /* '<Root>/i_d_ref_pu' */
  real32_T i_q_ref_pu;                 /* '<Root>/i_q_ref_pu' */
  real32_T i_x_ref_pu;                 /* '<Root>/i_x_ref_pu' */
  real32_T i_y_ref_pu;                 /* '<Root>/i_y_ref_pu' */
  real32_T lambda;                     /* '<Root>/lambda' */
  real32_T tolerance;                  /* '<Root>/tolerance' */
  real32_T max_iter;                   /* '<Root>/max_iter' */
  real32_T psiPM_h_pu[2];              /* '<Root>/psiPM_h_pu' */
  real32_T phiPM_h[2];                 /* '<Root>/phiPM_h' */
  boolean_T HC_off_on;                 /* '<Root>/HC_off_on' */
  boolean_T kalman_off_on;             /* '<Root>/kalman_off_on' */
  real32_T kalman_R;                   /* '<Root>/kalman_R' */
  real32_T kalman_Q1;                  /* '<Root>/kalman_Q1' */
  real32_T kalman_Q2;                  /* '<Root>/kalman_Q2' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T d_opt[6];                   /* '<Root>/d_opt' */
  real32_T iterations_qp;              /* '<Root>/iterations_qp' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Model entry point functions */
extern void uz_codegen0_initialize(RT_MODEL *const rtM);
extern void uz_codegen0_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Kalman_Observer' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/e_obs' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion3' : Eliminate redundant data type conversion
 */

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
 * hilite_system('uz_codegen/uz_codegen')    - opens subsystem uz_codegen/uz_codegen
 * hilite_system('uz_codegen/uz_codegen/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/uz_codegen'
 * '<S2>'   : 'uz_codegen/uz_codegen/MATLAB Function'
 * '<S3>'   : 'uz_codegen/uz_codegen/Observer'
 * '<S4>'   : 'uz_codegen/uz_codegen/act_sw_2_dqxy_volts_all'
 * '<S5>'   : 'uz_codegen/uz_codegen/deadbeat_solution'
 * '<S6>'   : 'uz_codegen/uz_codegen/delay_compensation_currents'
 * '<S7>'   : 'uz_codegen/uz_codegen/formulate_qp'
 * '<S8>'   : 'uz_codegen/uz_codegen/qp_solver'
 * '<S9>'   : 'uz_codegen/uz_codegen/seq_2_act_sw_all'
 * '<S10>'  : 'uz_codegen/uz_codegen/state_space_mdl'
 * '<S11>'  : 'uz_codegen/uz_codegen/tz'
 * '<S12>'  : 'uz_codegen/uz_codegen/tz_2_tph'
 * '<S13>'  : 'uz_codegen/uz_codegen/v_dqxy'
 */

/*-
 * Requirements for '<Root>': uz_codegen0
 */
#endif                                 /* RTW_HEADER_uz_codegen0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
