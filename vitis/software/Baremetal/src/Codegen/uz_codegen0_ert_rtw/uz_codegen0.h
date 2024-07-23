/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.2
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Jul 23 13:47:08 2024
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
  real32_T M[196];                     /* '<S1>/formulate_qp' */
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
  real32_T r[28];                      /* '<S1>/formulate_qp' */
  real32_T A[20];
  real32_T B_m[20];
  real32_T lam[16];
  real32_T Opt_data[14];
  real32_T Rhs_data[14];
  real32_T lam_c[8];
  real32_T cTol[8];
  real32_T x_data[7];
  real32_T fv[7];
  real32_T r_data[7];
  real32_T AcRow[7];
  real32_T z_data[7];
  real32_T tau_data[7];
  real32_T Ac[7];
  real32_T work_data[7];
  real32_T t[6];
  real32_T tz[6];                      /* '<S1>/tz' */
  real32_T x0[5];
  real32_T rtb_v_1_idx_pu_k[5];
  real32_T E[4];
  real32_T v_1_idx_pu[4];              /* '<S1>/act_sw_2_dqxy_volts_all' */
  real32_T v_2_idx_pu[4];              /* '<S1>/act_sw_2_dqxy_volts_all' */
  real32_T v_3_idx_pu[4];              /* '<S1>/act_sw_2_dqxy_volts_all' */
  real32_T v_4_idx_pu[4];              /* '<S1>/act_sw_2_dqxy_volts_all' */
  real32_T v_5_idx_pu[4];              /* '<S1>/act_sw_2_dqxy_volts_all' */
  real32_T m6[4];                      /* '<S1>/state_space_mdl' */
  real32_T m1[4];                      /* '<S1>/state_space_mdl' */
  real32_T E_c[4];
  real32_T B_b[4];
  real32_T A_p[4];
  real32_T E_cv[4];
  real32_T work_data_f[7];
  real32_T x;
  real32_T q;
  real32_T w6theta_el;
  real32_T SinCos1_o1;                 /* '<S1>/SinCos1' */
  real32_T SinCos1_o2;                 /* '<S1>/SinCos1' */
  real32_T x_tmp;
  real32_T x_tmp_g;
  real32_T rMin;
  real32_T Xnorm0;
  real32_T cMin;
  real32_T cVal;
  real32_T t_g;
  real32_T Linv;
  real32_T b_atmp;
  int32_T Linv_size[2];
  int32_T Hinv_size[2];
  int32_T RLinv_size[2];
  int32_T D_size[2];
  int32_T H_size[2];
  int32_T U_size[2];
  int32_T Q_size[2];
  int32_T A_size[2];
  int32_T idxAjj;
  int32_T b_j;
  int32_T iy;
  int32_T e;
  int32_T ia;
  int32_T b_ix;
  int32_T b_iy;
  int32_T b_k;
  int32_T sector_ref;                  /* '<S1>/deadbeat_solution' */
  int32_T i;
  int32_T x_size;
  int32_T i_m;
  int32_T H;
  int32_T loop_ub;
  int32_T i_n;
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
  int32_T m_p;
  int32_T n;
  int32_T minmana;
  int32_T minmn;
  int32_T ii;
  int32_T mmi;
  int32_T mmip1;
  int32_T i_l;
  int32_T i_j;
  int32_T itau;
  int32_T iaii;
  int32_T c_c;
  int16_T iA1[8];
  int16_T iC[8];
  int8_T b_I_data[49];
  int8_T act_sw_1[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_2[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_3[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_4[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_5[24];                 /* '<S1>/seq_2_act_sw_all' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T v_DC_pu;                    /* '<Root>/v_DC_pu' */
  real32_T theta_el;                   /* '<Root>/theta_el' */
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
 * Block '<S1>/Data Type Conversion2' : Eliminate redundant data type conversion
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
 * '<S2>'   : 'uz_codegen/uz_codegen/act_sw_2_dqxy_volts_all'
 * '<S3>'   : 'uz_codegen/uz_codegen/deadbeat_solution'
 * '<S4>'   : 'uz_codegen/uz_codegen/formulate_qp'
 * '<S5>'   : 'uz_codegen/uz_codegen/qp_solver'
 * '<S6>'   : 'uz_codegen/uz_codegen/seq_2_act_sw_all'
 * '<S7>'   : 'uz_codegen/uz_codegen/state_space_mdl'
 * '<S8>'   : 'uz_codegen/uz_codegen/tz'
 * '<S9>'   : 'uz_codegen/uz_codegen/tz_2_tph'
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
