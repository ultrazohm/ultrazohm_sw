/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.h
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 2.18
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Oct 16 15:52:20 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_uz_codegen0_h_
#define RTW_HEADER_uz_codegen0_h_
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef uz_codegen0_COMMON_INCLUDES_
#define uz_codegen0_COMMON_INCLUDES_
#include <stdio.h>
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

/* Custom Type definition for MATLAB Function: '<S1>/qp_solver' */
#ifndef struct_tag_svV6yPD1e8CTJu8b18IprLB
#define struct_tag_svV6yPD1e8CTJu8b18IprLB

struct tag_svV6yPD1e8CTJu8b18IprLB
{
  real_T xstar[8];
  real_T fstar;
  real_T firstorderopt;
  real_T lambda[9];
  int32_T state;
  real_T maxConstr;
  int32_T iterations;
  real_T searchDir[8];
};

#endif                                 /* struct_tag_svV6yPD1e8CTJu8b18IprLB */

#ifndef typedef_svV6yPD1e8CTJu8b18IprLB
#define typedef_svV6yPD1e8CTJu8b18IprLB

typedef struct tag_svV6yPD1e8CTJu8b18IprLB svV6yPD1e8CTJu8b18IprLB;

#endif                                 /* typedef_svV6yPD1e8CTJu8b18IprLB */

#ifndef struct_tag_shohwUBaOGHF036TMzc1KEH
#define struct_tag_shohwUBaOGHF036TMzc1KEH

struct tag_shohwUBaOGHF036TMzc1KEH
{
  real_T grad[8];
  real_T Hx[7];
  boolean_T hasLinear;
  int32_T nvar;
  int32_T maxVar;
  real_T beta;
  real_T rho;
  int32_T objtype;
  int32_T prev_objtype;
  int32_T prev_nvar;
  boolean_T prev_hasLinear;
  real_T gammaScalar;
};

#endif                                 /* struct_tag_shohwUBaOGHF036TMzc1KEH */

#ifndef typedef_shohwUBaOGHF036TMzc1KEH
#define typedef_shohwUBaOGHF036TMzc1KEH

typedef struct tag_shohwUBaOGHF036TMzc1KEH shohwUBaOGHF036TMzc1KEH;

#endif                                 /* typedef_shohwUBaOGHF036TMzc1KEH */

#ifndef struct_tag_s1hK3o0EyOqKKjEgDlbhqfF
#define struct_tag_s1hK3o0EyOqKKjEgDlbhqfF

struct tag_s1hK3o0EyOqKKjEgDlbhqfF
{
  real_T FMat[64];
  int32_T ldm;
  int32_T ndims;
  int32_T info;
  real_T scaleFactor;
  boolean_T ConvexCheck;
  real_T regTol_;
  real_T workspace_[384];
  real_T workspace2_[384];
};

#endif                                 /* struct_tag_s1hK3o0EyOqKKjEgDlbhqfF */

#ifndef typedef_s1hK3o0EyOqKKjEgDlbhqfF
#define typedef_s1hK3o0EyOqKKjEgDlbhqfF

typedef struct tag_s1hK3o0EyOqKKjEgDlbhqfF s1hK3o0EyOqKKjEgDlbhqfF;

#endif                                 /* typedef_s1hK3o0EyOqKKjEgDlbhqfF */

#ifndef struct_tag_swcr9qLPQBiG4lNhaNdYq5G
#define struct_tag_swcr9qLPQBiG4lNhaNdYq5G

struct tag_swcr9qLPQBiG4lNhaNdYq5G
{
  int32_T mConstr;
  int32_T mConstrOrig;
  int32_T mConstrMax;
  int32_T nVar;
  int32_T nVarOrig;
  int32_T nVarMax;
  int32_T ldA;
  real_T Aineq[56];
  real_T bineq[7];
  real_T Aeq[8];
  real_T beq;
  real_T lb[8];
  real_T ub[8];
  int32_T indexLB[8];
  int32_T indexUB[8];
  int32_T indexFixed[8];
  int32_T mEqRemoved;
  int32_T indexEqRemoved;
  real_T ATwset[72];
  real_T bwset[9];
  int32_T nActiveConstr;
  real_T maxConstrWorkspace[9];
  int32_T sizes[5];
  int32_T sizesNormal[5];
  int32_T sizesPhaseOne[5];
  int32_T sizesRegularized[5];
  int32_T sizesRegPhaseOne[5];
  int32_T isActiveIdx[6];
  int32_T isActiveIdxNormal[6];
  int32_T isActiveIdxPhaseOne[6];
  int32_T isActiveIdxRegularized[6];
  int32_T isActiveIdxRegPhaseOne[6];
  boolean_T isActiveConstr[9];
  int32_T Wid[9];
  int32_T Wlocalidx[9];
  int32_T nWConstr[5];
  int32_T probType;
  real_T SLACK0;
};

#endif                                 /* struct_tag_swcr9qLPQBiG4lNhaNdYq5G */

#ifndef typedef_swcr9qLPQBiG4lNhaNdYq5G
#define typedef_swcr9qLPQBiG4lNhaNdYq5G

typedef struct tag_swcr9qLPQBiG4lNhaNdYq5G swcr9qLPQBiG4lNhaNdYq5G;

#endif                                 /* typedef_swcr9qLPQBiG4lNhaNdYq5G */

#ifndef struct_tag_sL9bDKomAYkxZSVrG9w6En
#define struct_tag_sL9bDKomAYkxZSVrG9w6En

struct tag_sL9bDKomAYkxZSVrG9w6En
{
  int32_T MaxIterations;
  real_T ConstrRelTolFactor;
  real_T ProbRelTolFactor;
  boolean_T RemainFeasible;
};

#endif                                 /* struct_tag_sL9bDKomAYkxZSVrG9w6En */

#ifndef typedef_sL9bDKomAYkxZSVrG9w6En
#define typedef_sL9bDKomAYkxZSVrG9w6En

typedef struct tag_sL9bDKomAYkxZSVrG9w6En sL9bDKomAYkxZSVrG9w6En;

#endif                                 /* typedef_sL9bDKomAYkxZSVrG9w6En */

#ifndef struct_tag_sQyCFUyu0YXOk1LARsZMzaD
#define struct_tag_sQyCFUyu0YXOk1LARsZMzaD

struct tag_sQyCFUyu0YXOk1LARsZMzaD
{
  int32_T ldq;
  real_T QR[72];
  real_T Q[64];
  int32_T jpvt[9];
  int32_T mrows;
  int32_T ncols;
  real_T tau[8];
  int32_T minRowCol;
  boolean_T usedPivoting;
};

#endif                                 /* struct_tag_sQyCFUyu0YXOk1LARsZMzaD */

#ifndef typedef_sQyCFUyu0YXOk1LARsZMzaD
#define typedef_sQyCFUyu0YXOk1LARsZMzaD

typedef struct tag_sQyCFUyu0YXOk1LARsZMzaD sQyCFUyu0YXOk1LARsZMzaD;

#endif                                 /* typedef_sQyCFUyu0YXOk1LARsZMzaD */

#ifndef struct_tag_s9NoAX0P67ji2P1ZBafS3UG
#define struct_tag_s9NoAX0P67ji2P1ZBafS3UG

struct tag_s9NoAX0P67ji2P1ZBafS3UG
{
  real_T workspace_double[72];
  int32_T workspace_int[9];
  int32_T workspace_sort[9];
};

#endif                                 /* struct_tag_s9NoAX0P67ji2P1ZBafS3UG */

#ifndef typedef_s9NoAX0P67ji2P1ZBafS3UG
#define typedef_s9NoAX0P67ji2P1ZBafS3UG

typedef struct tag_s9NoAX0P67ji2P1ZBafS3UG s9NoAX0P67ji2P1ZBafS3UG;

#endif                                 /* typedef_s9NoAX0P67ji2P1ZBafS3UG */

#ifndef struct_tag_s4lHOiXA0GHbse0IgoBY6ZF
#define struct_tag_s4lHOiXA0GHbse0IgoBY6ZF

struct tag_s4lHOiXA0GHbse0IgoBY6ZF
{
  real_T InitDamping;
  char_T FiniteDifferenceType[7];
  boolean_T SpecifyObjectiveGradient;
  boolean_T ScaleProblem;
  boolean_T SpecifyConstraintGradient;
  boolean_T NonFiniteSupport;
  boolean_T IterDisplaySQP;
  real_T FiniteDifferenceStepSize;
  real_T MaxFunctionEvaluations;
  boolean_T IterDisplayQP;
  real_T PricingTolerance;
  char_T Algorithm[10];
  real_T ObjectiveLimit;
  real_T ConstraintTolerance;
  real_T OptimalityTolerance;
  real_T StepTolerance;
  real_T MaxIterations;
  real_T FunctionTolerance;
  char_T SolverName[8];
  boolean_T CheckGradients;
  char_T Diagnostics[3];
  real_T DiffMaxChange;
  real_T DiffMinChange;
  char_T Display[5];
  char_T FunValCheck[3];
  boolean_T UseParallel;
  char_T LinearSolver[4];
  char_T SubproblemAlgorithm[2];
};

#endif                                 /* struct_tag_s4lHOiXA0GHbse0IgoBY6ZF */

#ifndef typedef_s4lHOiXA0GHbse0IgoBY6ZF
#define typedef_s4lHOiXA0GHbse0IgoBY6ZF

typedef struct tag_s4lHOiXA0GHbse0IgoBY6ZF s4lHOiXA0GHbse0IgoBY6ZF;

#endif                                 /* typedef_s4lHOiXA0GHbse0IgoBY6ZF */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  s1hK3o0EyOqKKjEgDlbhqfF CholRegManager;
  swcr9qLPQBiG4lNhaNdYq5G WorkingSet;
  sQyCFUyu0YXOk1LARsZMzaD QRManager;
  s9NoAX0P67ji2P1ZBafS3UG memspace;
  svV6yPD1e8CTJu8b18IprLB solution;
  shohwUBaOGHF036TMzc1KEH QPObjective;
  s4lHOiXA0GHbse0IgoBY6ZF options;
  sL9bDKomAYkxZSVrG9w6En expl_temp;
  real_T B_m[72];
  real_T dv[49];
  real_T work[9];
  real_T x_tmp[7];
  real_T dv1[7];
  real_T dv2[7];
  real_T d[64];
  real_T work_c[9];
  real_T vn1[9];
  real_T vn2[9];
  real_T work_k[8];
  real_T fval;
  real_T exitflag;
  real_T output_iterations;
  real_T expl_temp_c;
  real_T expl_temp_b;
  real_T H_infnrm;
  real_T f_infnrm;
  real_T colSum;
  real_T b;
  real_T oldObjLim;
  real_T oldTolX;
  real_T tolDelta;
  real_T normDelta;
  real_T alpha;
  real_T n;
  real_T temp;
  real_T tempMaxConstr;
  real_T b_p;
  real_T constrViolation_basicX;
  real_T c;
  real_T b_atmp;
  real_T xnorm;
  real_T scale;
  real_T absxk;
  real_T t;
  real_T constrViolation;
  real_T tol;
  real_T qtb;
  real_T temp2;
  real_T smax;
  real_T c_c;
  real_T constrViolation_f;
  real_T d_c;
  real_T b_SCALED_REG_PRIMAL;
  real_T b_temp;
  real_T tol_g;
  real_T e;
  real_T c_c_g;
  real_T b_s;
  real_T b_temp_m;
  real_T roe;
  real_T absa;
  real_T absb;
  real_T p_max;
  real_T denomTol;
  real_T phaseOneCorrectionX;
  real_T phaseOneCorrectionP;
  real_T pk_corrected;
  real_T denomTol_n;
  real_T phaseOneCorrectionX_p;
  real_T phaseOneCorrectionP_l;
  real_T c_j;
  real_T c_d;
  real_T c_g;
  real_T c_l;
  real_T c_dh;
  real_T c_dy;
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
  real32_T Delay2_DSTATE[7];           /* '<S1>/Delay2' */
  real32_T x_e[8];                     /* '<S1>/Observer' */
  real32_T P_e[64];                    /* '<S1>/Observer' */
  real32_T M[196];                     /* '<S1>/formulate_qp' */
  real32_T A[64];
  real32_T A_l[64];
  real32_T A_o[64];
  real32_T rtb_M_b[49];
  real32_T b_A_tmp[32];
  real32_T r[28];                      /* '<S1>/formulate_qp' */
  real32_T A_n[16];
  real32_T B_b[16];
  real32_T fv[16];
  real32_T E[8];
  real32_T x_p[8];
  real32_T A_ln[8];
  real32_T x_opt[7];                   /* '<S1>/qp_solver' */
  real32_T t_h[6];
  real32_T tz[6];                      /* '<S1>/tz' */
  real32_T D[4];
  real32_T E_b[4];
  real32_T v_t0[4];                    /* '<S1>/v_dqxy' */
  real32_T m6[4];                      /* '<S1>/state_space_mdl' */
  real32_T m1[4];                      /* '<S1>/state_space_mdl' */
  real32_T m2[4];                      /* '<S1>/state_space_mdl' */
  real32_T m3[4];                      /* '<S1>/state_space_mdl' */
  real32_T m4[4];                      /* '<S1>/state_space_mdl' */
  real32_T E_d[4];
  real32_T E_e[4];
  real32_T w6theta_el;
  real32_T smax_b;
  real32_T q;
  real32_T SinCos1_o2;                 /* '<S1>/SinCos1' */
  real32_T SinCos2_o1;                 /* '<S1>/SinCos2' */
  real32_T rtb_v_t0_idx_2;
  real32_T rtb_v_t0_idx_3;
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
  real32_T A_tmp;
  int32_T jpvt[9];
  int32_T jpvt_j[9];
  int32_T jpvt_f[9];
  int32_T kBcol;
  int32_T d_j;
  int32_T ix;
  int32_T iy;
  int32_T c_ix;
  int32_T ijA;
  int32_T sector_ref;                  /* '<S1>/deadbeat_solution' */
  int32_T i;
  int32_T idx_row;
  int32_T i_a;
  int32_T i_j;
  int32_T PROBTYPE_ORIG;
  int32_T mConstr;
  int32_T b_TYPE;
  int32_T nVar_tmp;
  int32_T TYPE_tmp;
  int32_T activeSetChangeID;
  int32_T nVar;
  int32_T activeConstrChangedType;
  int32_T localActiveConstrIdx;
  int32_T globalActiveConstrIdx;
  int32_T workingIdx;
  int32_T TYPE;
  int32_T iQR0;
  int32_T Qk0;
  int32_T iyend;
  int32_T b_ix;
  int32_T c_iy;
  int32_T o;
  int32_T ia;
  int32_T b_k;
  int32_T nVar_tmp_tmp;
  int32_T mWConstr;
  int32_T nVar_j;
  int32_T ldq;
  int32_T ix_o;
  int32_T iy_n;
  int32_T b_i;
  int32_T jBcol;
  int32_T b_o;
  int32_T nVar_n;
  int32_T mTotalWorkingEq;
  int32_T offsetQR;
  int32_T offsetATw;
  int32_T idx_row_m;
  int32_T k;
  int32_T totalRank;
  int32_T ix_c;
  int32_T iy_m;
  int32_T k_m;
  int32_T nfxd;
  int32_T ii;
  int32_T nmi;
  int32_T pvt;
  int32_T b_ix_j;
  int32_T b_h;
  int32_T i_c;
  int32_T PROBTYPE_ORIG_c;
  int32_T b_TYPE_p;
  int32_T i_p;
  int32_T nVar_tmp_a;
  int32_T TYPE_tmp_e;
  int32_T nVar_a;
  int32_T mNull;
  int32_T nullStartIdx;
  int32_T b_A_maxDiag_idx;
  int32_T ix_a;
  int32_T iac;
  int32_T d_i;
  int32_T ia_l;
  int32_T b_ix_o;
  int32_T b_jjA;
  int32_T nFixedConstr;
  int32_T nVar_o;
  int32_T idxPosATwset;
  int32_T nDepIneq;
  int32_T k_i;
  int32_T i_f;
  int32_T ar;
  int32_T b_ia;
  int32_T iQR0_i;
  int32_T idxDiag;
  int8_T b_A_tmp_g[32];
  int8_T b_A_tmp_c[32];
  int8_T act_sw_1[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_2[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_3[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_4[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T act_sw_5[24];                 /* '<S1>/seq_2_act_sw_all' */
  int8_T rtb_m6_tmp[16];
  int8_T ipiv[4];
  boolean_T icLoad;                    /* '<S1>/Delay13' */
  boolean_T icLoad_m;                  /* '<S1>/Delay1' */
  boolean_T icLoad_l;                  /* '<S1>/Delay3' */
  boolean_T icLoad_lv;                 /* '<S1>/Delay4' */
  boolean_T icLoad_j;                  /* '<S1>/Delay5' */
  boolean_T icLoad_o;                  /* '<S1>/Delay6' */
  boolean_T icLoad_b;                  /* '<S1>/Delay7' */
  boolean_T icLoad_a;                  /* '<S1>/Delay8' */
  boolean_T icLoad_oa;                 /* '<S1>/Delay2' */
  char_T expl_temp_f[10];
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
  real32_T lambda_dq;                  /* '<Root>/lambda_dq' */
  real32_T lambda_xy;                  /* '<Root>/lambda_xy' */
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
  real32_T dob_error_estimate[4];      /* '<Root>/dob_error_estimate' */
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
 * Block '<S1>/duty_opt' : Unused code path elimination
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
