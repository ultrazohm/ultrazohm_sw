/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: impl_modul_mpc_single.h
 *
 * Code generated for Simulink model 'impl_modul_mpc_single'.
 *
 * Model version                  : 2.14
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue May 21 13:38:13 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_impl_modul_mpc_single_h_
#define RTW_HEADER_impl_modul_mpc_single_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef impl_modul_mpc_single_COMMON_INCLUDES_
#define impl_modul_mpc_single_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                              /* impl_modul_mpc_single_COMMON_INCLUDES_ */

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

#define impl_modul_mpc_single_M        (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S1>/formulate_qp_1' */
typedef struct {
  real32_T fv[32];
  real32_T fv1[16];
} DW_formulate_qp_1;

/* Block signals and states (default storage) for system '<S1>/state_space_mdl_1' */
typedef struct {
  real32_T B_m[6];
} DW_state_space_mdl_1;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_state_space_mdl_1 sf_state_space_mdl_6;/* '<S1>/state_space_mdl_6' */
  DW_state_space_mdl_1 sf_state_space_mdl_5;/* '<S1>/state_space_mdl_5' */
  DW_state_space_mdl_1 sf_state_space_mdl_4;/* '<S1>/state_space_mdl_4' */
  DW_state_space_mdl_1 sf_state_space_mdl_3;/* '<S1>/state_space_mdl_3' */
  DW_state_space_mdl_1 sf_state_space_mdl_2;/* '<S1>/state_space_mdl_2' */
  DW_state_space_mdl_1 sf_state_space_mdl_1;/* '<S1>/state_space_mdl_1' */
  DW_formulate_qp_1 sf_formulate_qp_6; /* '<S1>/formulate_qp_6' */
  DW_formulate_qp_1 sf_formulate_qp_5; /* '<S1>/formulate_qp_5' */
  DW_formulate_qp_1 sf_formulate_qp_4; /* '<S1>/formulate_qp_4' */
  DW_formulate_qp_1 sf_formulate_qp_3; /* '<S1>/formulate_qp_3' */
  DW_formulate_qp_1 sf_formulate_qp_2; /* '<S1>/formulate_qp_2' */
  DW_formulate_qp_1 sf_formulate_qp_1; /* '<S1>/formulate_qp_1' */
  real_T b_I_data[16];
  real32_T M_i[32];                    /* '<S1>/formulate_qp_1' */
  real32_T M_lo[32];                   /* '<S1>/formulate_qp_2' */
  real32_T M_f[32];                    /* '<S1>/formulate_qp_3' */
  real32_T M_l[32];                    /* '<S1>/formulate_qp_4' */
  real32_T M_p[32];                    /* '<S1>/formulate_qp_5' */
  real32_T M[32];                      /* '<S1>/formulate_qp_6' */
  real32_T rtb_x1_m[24];
  real32_T Linv_data[16];
  real32_T H_g[16];                    /* '<S1>/formulate_qp_1' */
  real32_T H_o[16];                    /* '<S1>/formulate_qp_2' */
  real32_T H_n[16];                    /* '<S1>/formulate_qp_3' */
  real32_T H_hd[16];                   /* '<S1>/formulate_qp_4' */
  real32_T H_h[16];                    /* '<S1>/formulate_qp_5' */
  real32_T H[16];                      /* '<S1>/formulate_qp_6' */
  real32_T Hinv_data[16];
  real32_T RLinv_data[16];
  real32_T D_data[16];
  real32_T H_data[16];
  real32_T U_data[16];
  real32_T TL_data[16];
  real32_T Q_data[16];
  real32_T R_data[16];
  real32_T A_data[16];
  real32_T r_k[8];                     /* '<S1>/formulate_qp_1' */
  real32_T r_b[8];                     /* '<S1>/formulate_qp_2' */
  real32_T r_l[8];                     /* '<S1>/formulate_qp_3' */
  real32_T r_d[8];                     /* '<S1>/formulate_qp_4' */
  real32_T r_f[8];                     /* '<S1>/formulate_qp_5' */
  real32_T r[8];                       /* '<S1>/formulate_qp_6' */
  real32_T Opt_data[8];
  real32_T Rhs_data[8];
  real32_T J_1to6[6];
  real32_T lam[5];
  real32_T cTol[5];
  real32_T x_tmp_data[4];
  real32_T f_n[4];                     /* '<S1>/formulate_qp_1' */
  real32_T f_k[4];                     /* '<S1>/formulate_qp_2' */
  real32_T f_a[4];                     /* '<S1>/formulate_qp_3' */
  real32_T f_c[4];                     /* '<S1>/formulate_qp_4' */
  real32_T f_m[4];                     /* '<S1>/formulate_qp_5' */
  real32_T f[4];                       /* '<S1>/formulate_qp_6' */
  real32_T x1[4];                      /* '<S1>/qp_solver_for_suited_seq_AS' */
  real32_T x2[4];                      /* '<S1>/qp_solver_for_suited_seq_AS' */
  real32_T x3[4];                      /* '<S1>/qp_solver_for_suited_seq_AS' */
  real32_T x4[4];                      /* '<S1>/qp_solver_for_suited_seq_AS' */
  real32_T x5[4];                      /* '<S1>/qp_solver_for_suited_seq_AS' */
  real32_T x6[4];                      /* '<S1>/qp_solver_for_suited_seq_AS' */
  real32_T r_data[4];
  real32_T AcRow[4];
  real32_T z_data[4];
  real32_T tau_data[4];
  real32_T Ac[4];
  real32_T work_data[4];
  real32_T tz[3];                      /* '<S1>/tz' */
  real32_T m3[2];                      /* '<S1>/state_space_mdl_6' */
  real32_T m2[2];                      /* '<S1>/state_space_mdl_6' */
  real32_T m1[2];                      /* '<S1>/state_space_mdl_6' */
  real32_T m0[2];                      /* '<S1>/state_space_mdl_6' */
  real32_T b_A_data[16];
  real32_T work_data_c[4];
  real32_T SinCos1_o1;                 /* '<S1>/SinCos1' */
  real32_T SinCos1_o2;                 /* '<S1>/SinCos1' */
  real32_T f_kk;
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
  real32_T ssq;
  real32_T b_c;
  real32_T c;
  real32_T scale;
  real32_T absxk;
  real32_T t_c;
  real32_T scale_b;
  real32_T absxk_p;
  real32_T t_cv;
  real32_T a;
  real32_T b;
  int32_T Linv_size[2];
  int32_T B_size[2];
  int32_T b_I_size[2];
  int32_T Hinv_size[2];
  int32_T RLinv_size[2];
  int32_T D_size[2];
  int32_T H_size[2];
  int32_T U_size[2];
  int32_T Q_size[2];
  int32_T A_size[2];
  int32_T d;
  int32_T i;
  int32_T loop_ub;
  int32_T x_tmp_tmp;
  int32_T x_tmp_size;
  int32_T m;
  int32_T coffset;
  int32_T boffset;
  int32_T j;
  int32_T i_f;
  int32_T b_i;
  int32_T i1;
  int32_T i_g;
  int32_T H_g1;
  int32_T loop_ub_m;
  int32_T i2;
  int32_T i3;
  int32_T lambda_tmp_tmp;
  int32_T z_size;
  int32_T m_n;
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
  int32_T knt;
  int32_T b_k;
  int32_T c_k;
  int32_T jA;
  int32_T jy;
  int32_T ix;
  int32_T j_j;
  int32_T b_d;
  int32_T ijA;
  int32_T jmax;
  int32_T idxAjj;
  int32_T iy;
  int32_T e;
  int32_T ia;
  int32_T b_ix;
  int32_T b_iy;
  int32_T i_gu;
  int32_T itau;
  int32_T iaii;
  int32_T c_c;
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T ia_l;
  int32_T ix_d;
  int32_T b_iy_d;
  int32_T b_l;
  int32_T iac;
  int32_T d_o;
  int32_T ia_b;
  int32_T j_n;
  int32_T i_b;
  int32_T y;
  int32_T mB;
  int32_T nB;
  int32_T n_l;
  int32_T jBcol;
  int32_T kAcol;
  int32_T j_h;
  int32_T k;
  int32_T i_bn;
  int32_T i4;
  int32_T kend;
  int32_T k_d;
  int32_T m_e;
  int32_T aoffset;
  int32_T i_bj;
  int32_T b_i_j;
  int32_T k_f;
  int32_T i5;
  int32_T i_a;
  int32_T k_j;
  int32_T i_j;
  uint32_T u;
  int16_T iA1[5];
  int16_T iC[5];
  int16_T nA;
  int16_T kDrop;
  int16_T kNext;
  int16_T i6;
  int16_T i7;
  int16_T b_j;
  boolean_T tmpForInput_tmp[6];
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
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T CMPA_opt[3];                /* '<Root>/CMPA_opt' */
  real32_T iterations_qp[6];           /* '<Root>/iterations_qp' */
  boolean_T unsuited_qp[6];            /* '<Root>/unsuited_qp' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  ExtU *inputs;
  ExtY *outputs;
  DW *dwork;
};

/* Model entry point functions */
extern void impl_modul_mpc_single_initialize(RT_MODEL *const rtM);
extern void impl_modul_mpc_single_step(RT_MODEL *const rtM);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/CMPA' : Unused code path elimination
 * Block '<S1>/Display' : Unused code path elimination
 * Block '<S1>/Display1' : Unused code path elimination
 * Block '<S1>/Display10' : Unused code path elimination
 * Block '<S1>/Display11' : Unused code path elimination
 * Block '<S1>/Display12' : Unused code path elimination
 * Block '<S1>/Display13' : Unused code path elimination
 * Block '<S1>/Display14' : Unused code path elimination
 * Block '<S1>/Display15' : Unused code path elimination
 * Block '<S1>/Display16' : Unused code path elimination
 * Block '<S1>/Display17' : Unused code path elimination
 * Block '<S1>/Display18' : Unused code path elimination
 * Block '<S1>/Display19' : Unused code path elimination
 * Block '<S1>/Display2' : Unused code path elimination
 * Block '<S1>/Display20' : Unused code path elimination
 * Block '<S1>/Display21' : Unused code path elimination
 * Block '<S1>/Display22' : Unused code path elimination
 * Block '<S1>/Display23' : Unused code path elimination
 * Block '<S1>/Display24' : Unused code path elimination
 * Block '<S1>/Display25' : Unused code path elimination
 * Block '<S1>/Display26' : Unused code path elimination
 * Block '<S1>/Display27' : Unused code path elimination
 * Block '<S1>/Display28' : Unused code path elimination
 * Block '<S1>/Display29' : Unused code path elimination
 * Block '<S1>/Display3' : Unused code path elimination
 * Block '<S1>/Display30' : Unused code path elimination
 * Block '<S1>/Display32' : Unused code path elimination
 * Block '<S1>/Display33' : Unused code path elimination
 * Block '<S1>/Display34' : Unused code path elimination
 * Block '<S1>/Display35' : Unused code path elimination
 * Block '<S1>/Display36' : Unused code path elimination
 * Block '<S1>/Display37' : Unused code path elimination
 * Block '<S1>/Display38' : Unused code path elimination
 * Block '<S1>/Display39' : Unused code path elimination
 * Block '<S1>/Display4' : Unused code path elimination
 * Block '<S1>/Display40' : Unused code path elimination
 * Block '<S1>/Display42' : Unused code path elimination
 * Block '<S1>/Display46' : Unused code path elimination
 * Block '<S1>/Display5' : Unused code path elimination
 * Block '<S1>/Display50' : Unused code path elimination
 * Block '<S1>/Display54' : Unused code path elimination
 * Block '<S1>/Display6' : Unused code path elimination
 * Block '<S1>/Display7' : Unused code path elimination
 * Block '<S1>/Display8' : Unused code path elimination
 * Block '<S1>/Display9' : Unused code path elimination
 * Block '<S1>/gradients_1' : Unused code path elimination
 * Block '<S1>/gradients_2' : Unused code path elimination
 * Block '<S1>/gradients_3' : Unused code path elimination
 * Block '<S1>/gradients_4' : Unused code path elimination
 * Block '<S1>/gradients_5' : Unused code path elimination
 * Block '<S1>/gradients_6' : Unused code path elimination
 * Block '<S1>/sum_of_unsuited' : Unused code path elimination
 * Block '<S1>/Data Type Conversion1' : Eliminate redundant data type conversion
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
 * hilite_system('uz_codegen/impl_modul_mpc_single')    - opens subsystem uz_codegen/impl_modul_mpc_single
 * hilite_system('uz_codegen/impl_modul_mpc_single/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'uz_codegen'
 * '<S1>'   : 'uz_codegen/impl_modul_mpc_single'
 * '<S2>'   : 'uz_codegen/impl_modul_mpc_single/act_sw_2_dq_volts_all'
 * '<S3>'   : 'uz_codegen/impl_modul_mpc_single/detect_unsuited_sequence_1'
 * '<S4>'   : 'uz_codegen/impl_modul_mpc_single/detect_unsuited_sequence_2'
 * '<S5>'   : 'uz_codegen/impl_modul_mpc_single/detect_unsuited_sequence_3'
 * '<S6>'   : 'uz_codegen/impl_modul_mpc_single/detect_unsuited_sequence_4'
 * '<S7>'   : 'uz_codegen/impl_modul_mpc_single/detect_unsuited_sequence_5'
 * '<S8>'   : 'uz_codegen/impl_modul_mpc_single/detect_unsuited_sequence_6'
 * '<S9>'   : 'uz_codegen/impl_modul_mpc_single/formulate_qp_1'
 * '<S10>'  : 'uz_codegen/impl_modul_mpc_single/formulate_qp_2'
 * '<S11>'  : 'uz_codegen/impl_modul_mpc_single/formulate_qp_3'
 * '<S12>'  : 'uz_codegen/impl_modul_mpc_single/formulate_qp_4'
 * '<S13>'  : 'uz_codegen/impl_modul_mpc_single/formulate_qp_5'
 * '<S14>'  : 'uz_codegen/impl_modul_mpc_single/formulate_qp_6'
 * '<S15>'  : 'uz_codegen/impl_modul_mpc_single/min_Costs'
 * '<S16>'  : 'uz_codegen/impl_modul_mpc_single/qp_solver_for_suited_seq_AS'
 * '<S17>'  : 'uz_codegen/impl_modul_mpc_single/seq_2_act_sw_all'
 * '<S18>'  : 'uz_codegen/impl_modul_mpc_single/state_space_mdl_1'
 * '<S19>'  : 'uz_codegen/impl_modul_mpc_single/state_space_mdl_2'
 * '<S20>'  : 'uz_codegen/impl_modul_mpc_single/state_space_mdl_3'
 * '<S21>'  : 'uz_codegen/impl_modul_mpc_single/state_space_mdl_4'
 * '<S22>'  : 'uz_codegen/impl_modul_mpc_single/state_space_mdl_5'
 * '<S23>'  : 'uz_codegen/impl_modul_mpc_single/state_space_mdl_6'
 * '<S24>'  : 'uz_codegen/impl_modul_mpc_single/tz'
 * '<S25>'  : 'uz_codegen/impl_modul_mpc_single/tz_2_tph'
 */

/*-
 * Requirements for '<Root>': impl_modul_mpc_single
 */
#endif                                 /* RTW_HEADER_impl_modul_mpc_single_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
