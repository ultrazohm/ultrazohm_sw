/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: impl_modul_mpc_all_and_deadbeat.h
 *
 * Code generated for Simulink model 'impl_modul_mpc_all_and_deadbeat'.
 *
 * Model version                  : 2.16
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Fri Jun 14 18:19:30 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warnings (3), Error (0)
 */

#ifndef RTW_HEADER_impl_modul_mpc_all_and_deadbeat_h_
#define RTW_HEADER_impl_modul_mpc_all_and_deadbeat_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef impl_modul_mpc_all_and_deadbeat_COMMON_INCLUDES_
#define impl_modul_mpc_all_and_deadbeat_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                    /* impl_modul_mpc_all_and_deadbeat_COMMON_INCLUDES_ */

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

#define impl_modul_mpc_all_and_deadbeat_M (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S3>/formulate_qp_1' */
typedef struct {
  real32_T fv[32];
  real32_T fv1[16];
} DW_formulate_qp_1;

/* Block signals and states (default storage) for system '<S3>/state_space_mdl_1' */
typedef struct {
  real32_T B_m[6];
} DW_state_space_mdl_1;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_state_space_mdl_1 sf_state_space_mdl_deadbeat;/* '<S4>/state_space_mdl_deadbeat' */
  DW_formulate_qp_1 sf_formulate_qp_deadbeat;/* '<S4>/formulate_qp_deadbeat' */
  DW_state_space_mdl_1 sf_state_space_mdl_6;/* '<S3>/state_space_mdl_6' */
  DW_state_space_mdl_1 sf_state_space_mdl_5;/* '<S3>/state_space_mdl_5' */
  DW_state_space_mdl_1 sf_state_space_mdl_4;/* '<S3>/state_space_mdl_4' */
  DW_state_space_mdl_1 sf_state_space_mdl_3;/* '<S3>/state_space_mdl_3' */
  DW_state_space_mdl_1 sf_state_space_mdl_2;/* '<S3>/state_space_mdl_2' */
  DW_state_space_mdl_1 sf_state_space_mdl_1;/* '<S3>/state_space_mdl_1' */
  DW_formulate_qp_1 sf_formulate_qp_6; /* '<S3>/formulate_qp_6' */
  DW_formulate_qp_1 sf_formulate_qp_5; /* '<S3>/formulate_qp_5' */
  DW_formulate_qp_1 sf_formulate_qp_4; /* '<S3>/formulate_qp_4' */
  DW_formulate_qp_1 sf_formulate_qp_3; /* '<S3>/formulate_qp_3' */
  DW_formulate_qp_1 sf_formulate_qp_2; /* '<S3>/formulate_qp_2' */
  DW_formulate_qp_1 sf_formulate_qp_1; /* '<S3>/formulate_qp_1' */
  real_T b_I_data[16];
  real_T sector_ref;                   /* '<S4>/deadbeat_solution' */
  real_T Switch1;                      /* '<S1>/Switch1' */
  real32_T x1[4];                      /* '<S4>/qp_solver_for_deadbeat' */
  real32_T x_opt[4];                   /* '<S3>/min_Costs' */
  real32_T M_h[32];                    /* '<S3>/formulate_qp_2' */
  real32_T M_l[32];                    /* '<S3>/formulate_qp_3' */
  real32_T M_ny[32];                   /* '<S3>/formulate_qp_4' */
  real32_T M_o[32];                    /* '<S3>/formulate_qp_5' */
  real32_T M_n[32];                    /* '<S3>/formulate_qp_6' */
  real32_T M[32];                      /* '<S4>/formulate_qp_deadbeat' */
  real32_T rtb_x1_m[24];
  real32_T Linv_data[16];
  real32_T H_l[16];                    /* '<S3>/formulate_qp_2' */
  real32_T H_p[16];                    /* '<S3>/formulate_qp_3' */
  real32_T H_m[16];                    /* '<S3>/formulate_qp_4' */
  real32_T H_n[16];                    /* '<S3>/formulate_qp_5' */
  real32_T H_c[16];                    /* '<S3>/formulate_qp_6' */
  real32_T H[16];                      /* '<S4>/formulate_qp_deadbeat' */
  real32_T Hinv_data[16];
  real32_T RLinv_data[16];
  real32_T D_data[16];
  real32_T H_data[16];
  real32_T U_data[16];
  real32_T TL_data[16];
  real32_T Q_data[16];
  real32_T R_data[16];
  real32_T A_data[16];
  real32_T r_ff[8];                    /* '<S3>/formulate_qp_2' */
  real32_T r_b[8];                     /* '<S3>/formulate_qp_3' */
  real32_T r_j[8];                     /* '<S3>/formulate_qp_4' */
  real32_T r_g[8];                     /* '<S3>/formulate_qp_5' */
  real32_T r_f[8];                     /* '<S3>/formulate_qp_6' */
  real32_T r[8];                       /* '<S4>/formulate_qp_deadbeat' */
  real32_T Opt_data[8];
  real32_T Rhs_data[8];
  real32_T vd_1_pu[6];                 /* '<S1>/act_sw_2_dq_volts_all' */
  real32_T lam[5];
  real32_T lam_c[5];
  real32_T cTol[5];
  real32_T x_data[4];
  real32_T f_gy[4];                    /* '<S3>/formulate_qp_2' */
  real32_T f_h[4];                     /* '<S3>/formulate_qp_3' */
  real32_T f_f[4];                     /* '<S3>/formulate_qp_4' */
  real32_T f_g[4];                     /* '<S3>/formulate_qp_5' */
  real32_T f_m[4];                     /* '<S3>/formulate_qp_6' */
  real32_T IndexVector[4];             /* '<S4>/Index Vector' */
  real32_T x1_k[4];                    /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T x2[4];                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T x3[4];                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T x4[4];                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T x5[4];                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T x6[4];                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T rtb_IndexVector_c[4];
  real32_T r_data[4];
  real32_T AcRow[4];
  real32_T z_data[4];
  real32_T tau_data[4];
  real32_T Ac[4];
  real32_T work_data[4];
  real32_T tz[3];                      /* '<S1>/tz' */
  real32_T m0[2];                      /* '<S4>/state_space_mdl_deadbeat' */
  real32_T m1[2];                      /* '<S4>/state_space_mdl_deadbeat' */
  real32_T m2[2];                      /* '<S4>/state_space_mdl_deadbeat' */
  real32_T m3[2];                      /* '<S4>/state_space_mdl_deadbeat' */
  real32_T RLinv_data_b[16];
  real32_T D_data_p[16];
  real32_T H_data_c[16];
  real32_T U_data_f[16];
  real32_T Opt_data_g[8];
  real32_T Rhs_data_g[8];
  real32_T cTol_m[5];
  real32_T r_data_n[4];
  real32_T AcRow_p[4];
  real32_T z_data_l[4];
  real32_T work_data_j[4];
  real32_T TL_data_d[16];
  real32_T Q_data_g[16];
  real32_T R_data_l[16];
  real32_T A_data_d[16];
  real32_T tau_data_d[4];
  real32_T Ac_l[4];
  real32_T b_A_data[16];
  real32_T work_data_o[4];
  real32_T iter1_o;                    /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T iter2;                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T iter3;                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T iter4;                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T iter5;                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T iter6;                      /* '<S3>/qp_solver_for_suited_seq_AS' */
  real32_T idx_opt;                    /* '<S3>/min_Costs' */
  real32_T q;
  real32_T SinCos1_o1;                 /* '<S1>/SinCos1' */
  real32_T SinCos1_o2;                 /* '<S1>/SinCos1' */
  real32_T rtb_vd_2_pu_idx_0_tmp;
  real32_T rtb_vq_2_pu_idx_0_tmp;
  real32_T rtb_vd_1_pu_tmp;
  real32_T rtb_vq_1_pu_idx_1_tmp;
  real32_T rtb_vd_2_pu_idx_2_tmp;
  real32_T rtb_vq_2_pu_idx_2_tmp;
  real32_T rtb_vd_1_pu_tmp_b;
  real32_T rtb_vd_1_pu_tmp_n;
  real32_T rtb_vq_1_pu_idx_0_tmp;
  real32_T rtb_vd_2_pu_idx_4_tmp;
  real32_T rtb_vq_1_pu_idx_1_tmp_tmp;
  real32_T rtb_vq_2_pu_idx_0_tmp_tmp;
  real32_T bkj;
  real32_T rMin;
  real32_T Xnorm0;
  real32_T cMin;
  real32_T cVal;
  real32_T t;
  real32_T Linv;
  real32_T b_atmp;
  real32_T beta1;
  real32_T temp;
  real32_T rMin_b;
  real32_T Xnorm0_l;
  real32_T cMin_h;
  real32_T cVal_b;
  real32_T t_d;
  real32_T ssq;
  real32_T b_c;
  real32_T c;
  real32_T scale;
  real32_T absxk;
  real32_T t_e;
  real32_T scale_b;
  real32_T absxk_j;
  real32_T t_f;
  real32_T a;
  real32_T b;
  int32_T b_I_size[2];
  int32_T Linv_size[2];
  int32_T Hinv_size[2];
  int32_T Hinv_size_a[2];
  int32_T RLinv_size[2];
  int32_T D_size[2];
  int32_T H_size[2];
  int32_T U_size[2];
  int32_T Q_size[2];
  int32_T A_size[2];
  int32_T RLinv_size_j[2];
  int32_T D_size_j[2];
  int32_T H_size_o[2];
  int32_T U_size_n[2];
  int32_T Q_size_i[2];
  int32_T A_size_o[2];
  int32_T d;
  int32_T jmax;
  int32_T idxAjj;
  int32_T iy;
  int32_T e;
  int32_T ia;
  int32_T b_ix;
  int32_T b_iy;
  int32_T b_d;
  int32_T x_size;
  int32_T m;
  int32_T coffset;
  int32_T boffset;
  int32_T j;
  int32_T i;
  int32_T b_i;
  int32_T i_n;
  int32_T i_m;
  int32_T H_cz;
  int32_T loop_ub;
  int32_T i1;
  int32_T i2;
  int32_T lambda_tmp_tmp;
  int32_T z_size;
  int32_T m_m;
  int32_T b_n;
  int32_T h_j;
  int32_T RLinv;
  int32_T tau_size;
  int32_T R_size_idx_0;
  int32_T TL_size_idx_0;
  int32_T m_m3;
  int32_T n;
  int32_T minmana;
  int32_T minmn;
  int32_T ii;
  int32_T mmi;
  int32_T mmip1;
  int32_T i_j;
  int32_T knt;
  int32_T b_k;
  int32_T c_k;
  int32_T jA;
  int32_T jy;
  int32_T ix;
  int32_T j_h;
  int32_T b_c0;
  int32_T ijA;
  int32_T i_c;
  int32_T H_px;
  int32_T loop_ub_p;
  int32_T i3;
  int32_T i4;
  int32_T lambda_tmp_tmp_a;
  int32_T z_size_e;
  int32_T i_a;
  int32_T itau;
  int32_T iaii;
  int32_T c_c;
  int32_T m_a;
  int32_T b_n_i;
  int32_T h_j_l;
  int32_T RLinv_o;
  int32_T jmax_o;
  int32_T idxAjj_i;
  int32_T iy_f;
  int32_T e_i;
  int32_T ia_f;
  int32_T b_ix_g;
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T ia_c;
  int32_T ix_o;
  int32_T b_iy_l;
  int32_T b_m;
  int32_T iac;
  int32_T d_m;
  int32_T ia_cn;
  int32_T j_f;
  int32_T i_p;
  int32_T y;
  int32_T mB;
  int32_T nB;
  int32_T n_e;
  int32_T jBcol;
  int32_T kAcol;
  int32_T j_o;
  int32_T k;
  int32_T i_h;
  int32_T m_l;
  int32_T n_h;
  int32_T kend;
  int32_T k_m;
  int32_T m_mc;
  int32_T aoffset;
  int32_T i_h3;
  int32_T b_i_c;
  int32_T i5;
  int16_T iA1[5];
  int16_T iA1_k[5];
  int16_T iC[5];
  int16_T iC_p[5];
  int16_T i6;
  int16_T i7;
  int16_T nA;
  int16_T kDrop;
  int16_T kNext;
  int16_T i8;
  int8_T b_I_data_p[16];
  int8_T ifdeadbeattrue_ActiveSubsystem;/* '<S1>/if deadbeat true' */
  int8_T ifalltrue_ActiveSubsystem;    /* '<S1>/if all true' */
  boolean_T unsuited;                  /* '<S3>/detect_unsuited_sequence_6' */
  boolean_T unsuited_j;                /* '<S3>/detect_unsuited_sequence_5' */
  boolean_T unsuited_i;                /* '<S3>/detect_unsuited_sequence_4' */
  boolean_T unsuited_f;                /* '<S3>/detect_unsuited_sequence_3' */
  boolean_T unsuited_k;                /* '<S3>/detect_unsuited_sequence_2' */
  boolean_T unsuited_h;                /* '<S3>/detect_unsuited_sequence_1' */
  boolean_T icLoad;                    /* '<S4>/Delay2' */
  boolean_T icLoad_a;                  /* '<S3>/Delay1' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T v_DC_pu;                    /* '<Root>/v_DC_pu' */
  real32_T theta_el;                   /* '<Root>/theta_el' */
  real32_T Ts_times_ZB_over_Ld;        /* '<Root>/Ts_times_ZB_over_Ld' */
  real32_T Ts_times_ZB_over_Lq;        /* '<Root>/Ts_times_ZB_over_Lq' */
  real32_T Rs_over_ZB;                 /* '<Root>/Rs_over_ZB' */
  real32_T Ld_over_LB;                 /* '<Root>/Ld_over_LB' */
  real32_T Lq_over_LB;                 /* '<Root>/Lq_over_LB' */
  real32_T psi_pm_over_psiB;           /* '<Root>/psi_pm_over_psiB' */
  real32_T omega_el_pu;                /* '<Root>/omega_el_pu' */
  real32_T i_dq_pu[2];                 /* '<Root>/i_dq_pu' */
  real32_T i_d_ref_pu;                 /* '<Root>/i_d_ref_pu' */
  real32_T i_q_ref_pu;                 /* '<Root>/i_q_ref_pu' */
  real32_T lambda;                     /* '<Root>/lambda' */
  real32_T alpha0;                     /* '<Root>/alpha0' */
  real32_T tolerance;                  /* '<Root>/tolerance' */
  real32_T max_iter;                   /* '<Root>/max_iter' */
  real32_T all_or_deadbeat;            /* '<Root>/all_or_deadbeat' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T CMPA_opt[3];                /* '<Root>/CMPA_opt' */
  real32_T iterations_qp[6];           /* '<Root>/iterations_qp' */
  boolean_T unsuited_qp[6];            /* '<Root>/unsuited_qp' */
  real32_T iterations_deadbeat;        /* '<Root>/iterations_deadbeat' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Model entry point functions */
extern void impl_modul_mpc_all_and_deadbeat_initialize(RT_MODEL *const rtM);
extern void impl_modul_mpc_all_and_deadbeat_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Display' : Unused code path elimination
 * Block '<S3>/Display1' : Unused code path elimination
 * Block '<S3>/Display10' : Unused code path elimination
 * Block '<S3>/Display11' : Unused code path elimination
 * Block '<S3>/Display12' : Unused code path elimination
 * Block '<S3>/Display13' : Unused code path elimination
 * Block '<S3>/Display14' : Unused code path elimination
 * Block '<S3>/Display15' : Unused code path elimination
 * Block '<S3>/Display16' : Unused code path elimination
 * Block '<S3>/Display17' : Unused code path elimination
 * Block '<S3>/Display18' : Unused code path elimination
 * Block '<S3>/Display19' : Unused code path elimination
 * Block '<S3>/Display2' : Unused code path elimination
 * Block '<S3>/Display20' : Unused code path elimination
 * Block '<S3>/Display21' : Unused code path elimination
 * Block '<S3>/Display22' : Unused code path elimination
 * Block '<S3>/Display23' : Unused code path elimination
 * Block '<S3>/Display24' : Unused code path elimination
 * Block '<S3>/Display25' : Unused code path elimination
 * Block '<S3>/Display26' : Unused code path elimination
 * Block '<S3>/Display27' : Unused code path elimination
 * Block '<S3>/Display28' : Unused code path elimination
 * Block '<S3>/Display29' : Unused code path elimination
 * Block '<S3>/Display3' : Unused code path elimination
 * Block '<S3>/Display30' : Unused code path elimination
 * Block '<S3>/Display32' : Unused code path elimination
 * Block '<S3>/Display33' : Unused code path elimination
 * Block '<S3>/Display34' : Unused code path elimination
 * Block '<S3>/Display35' : Unused code path elimination
 * Block '<S3>/Display36' : Unused code path elimination
 * Block '<S3>/Display37' : Unused code path elimination
 * Block '<S3>/Display38' : Unused code path elimination
 * Block '<S3>/Display39' : Unused code path elimination
 * Block '<S3>/Display4' : Unused code path elimination
 * Block '<S3>/Display40' : Unused code path elimination
 * Block '<S3>/Display42' : Unused code path elimination
 * Block '<S3>/Display46' : Unused code path elimination
 * Block '<S3>/Display5' : Unused code path elimination
 * Block '<S3>/Display50' : Unused code path elimination
 * Block '<S3>/Display54' : Unused code path elimination
 * Block '<S3>/Display6' : Unused code path elimination
 * Block '<S3>/Display7' : Unused code path elimination
 * Block '<S3>/Display8' : Unused code path elimination
 * Block '<S3>/Display9' : Unused code path elimination
 * Block '<S3>/gradients_1' : Unused code path elimination
 * Block '<S3>/gradients_2' : Unused code path elimination
 * Block '<S3>/gradients_3' : Unused code path elimination
 * Block '<S3>/gradients_4' : Unused code path elimination
 * Block '<S3>/gradients_5' : Unused code path elimination
 * Block '<S3>/gradients_6' : Unused code path elimination
 * Block '<S3>/sum_of_unsuited' : Unused code path elimination
 * Block '<S4>/Display31' : Unused code path elimination
 * Block '<S4>/Display41' : Unused code path elimination
 * Block '<S4>/Display43' : Unused code path elimination
 * Block '<S4>/Display44' : Unused code path elimination
 * Block '<S4>/Display45' : Unused code path elimination
 * Block '<S4>/Display47' : Unused code path elimination
 * Block '<S4>/gradients_7' : Unused code path elimination
 * Block '<S3>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S4>/Data Type Conversion2' : Eliminate redundant data type conversion
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
 * hilite_system('uz_codegen/impl_modul_mpc_all_and_deadbeat')    - opens subsystem uz_codegen/impl_modul_mpc_all_and_deadbeat
 * hilite_system('uz_codegen/impl_modul_mpc_all_and_deadbeat/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat'
 * '<S2>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/act_sw_2_dq_volts_all'
 * '<S3>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all'
 * '<S4>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/deadbeat'
 * '<S5>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/seq_2_act_sw_all'
 * '<S6>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/tz'
 * '<S7>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/tz_2_tph'
 * '<S8>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/detect_unsuited_sequence_1'
 * '<S9>'   : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/detect_unsuited_sequence_2'
 * '<S10>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/detect_unsuited_sequence_3'
 * '<S11>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/detect_unsuited_sequence_4'
 * '<S12>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/detect_unsuited_sequence_5'
 * '<S13>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/detect_unsuited_sequence_6'
 * '<S14>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/formulate_qp_1'
 * '<S15>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/formulate_qp_2'
 * '<S16>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/formulate_qp_3'
 * '<S17>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/formulate_qp_4'
 * '<S18>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/formulate_qp_5'
 * '<S19>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/formulate_qp_6'
 * '<S20>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/min_Costs'
 * '<S21>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/qp_solver_for_suited_seq_AS'
 * '<S22>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/state_space_mdl_1'
 * '<S23>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/state_space_mdl_2'
 * '<S24>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/state_space_mdl_3'
 * '<S25>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/state_space_mdl_4'
 * '<S26>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/state_space_mdl_5'
 * '<S27>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/all/state_space_mdl_6'
 * '<S28>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/deadbeat/deadbeat_solution'
 * '<S29>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/deadbeat/formulate_qp_deadbeat'
 * '<S30>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/deadbeat/qp_solver_for_deadbeat'
 * '<S31>'  : 'uz_codegen/impl_modul_mpc_all_and_deadbeat/deadbeat/state_space_mdl_deadbeat'
 */

/*-
 * Requirements for '<Root>': impl_modul_mpc_all_and_deadbeat
 */
#endif                       /* RTW_HEADER_impl_modul_mpc_all_and_deadbeat_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
