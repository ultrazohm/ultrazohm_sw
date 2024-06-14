/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: impl_modul_mpc_all_and_deadbeat.c
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

#include "impl_modul_mpc_all_and_deadbeat.h"

static void detect_unsuited_sequence_1(const real32_T rtu_H[16], const real32_T
  rtu_f[4], boolean_T *rty_unsuited);
static void formulate_qp_1(const real32_T rtu_m0[2], const real32_T rtu_m1[2],
  const real32_T rtu_m2[2], const real32_T rtu_m3[2], real32_T rtu_id0, real32_T
  rtu_iq0, real32_T rtu_id_ref, real32_T rtu_iq_ref, real32_T rtu_lambda,
  real32_T rty_H[16], real32_T rty_f[4], real32_T rty_M[32], real32_T rty_r[8],
  DW_formulate_qp_1 *localDW);
static void state_space_mdl_1(real32_T rtu_Ts_times_ZB_over_Ld, real32_T
  rtu_Ts_times_ZB_over_Lq, real32_T rtu_Rs_over_ZB, real32_T rtu_Ld_over_LB,
  real32_T rtu_Lq_over_LB, real32_T rtu_psi_pm_over_psiB, real32_T rtu_id_pu,
  real32_T rtu_iq_pu, real32_T rtu_w_e_pu, real32_T rtu_vd_1_pu, real32_T
  rtu_vq_1_pu, real32_T rtu_vd_2_pu, real32_T rtu_vq_2_pu, real32_T rty_m0[2],
  real32_T rty_m1[2], real32_T rty_m2[2], real32_T rty_m3[2],
  DW_state_space_mdl_1 *localDW);

/* Forward declaration for local functions */
static void trisolve(const real32_T A_data[], const int32_T A_size[2], real32_T
                     B_data[], const int32_T B_size[2], DW *rtDW);
static void Unconstrained(const real32_T Hinv_data[], const int32_T Hinv_size[2],
  const real32_T f[4], real32_T x_data[], int16_T n);
static real32_T norm(const real32_T x_data[], const int32_T *x_size, DW *rtDW);
static void abs_d(const real32_T x[4], real32_T y[4]);
static real32_T maximum(const real32_T x[4]);
static void maximum2(const real32_T x[5], real32_T ex[5]);
static real32_T xnrm2(int32_T n, const real32_T x_data[], int32_T ix0, DW *rtDW);
static real32_T rt_hypotf_p(real32_T u0, real32_T u1, DW *rtDW);
static void xgemv(int32_T m, int32_T n, const real32_T A_data[], int32_T ia0,
                  int32_T lda, const real32_T x_data[], int32_T ix0, real32_T
                  y_data[], DW *rtDW);
static void xgerc(int32_T m, int32_T n, real32_T alpha1, int32_T ix0, const
                  real32_T y_data[], real32_T A_data[], int32_T ia0, int32_T lda,
                  DW *rtDW);
static void xgeqrf(real32_T A_data[], const int32_T A_size[2], real32_T
                   tau_data[], int32_T *tau_size, DW *rtDW);
static void xorgqr(int32_T m, int32_T n, int32_T k, real32_T A_data[], const
                   int32_T A_size[2], int32_T lda, const real32_T tau_data[], DW
                   *rtDW);
static void mtimes(const real32_T A_data[], const int32_T A_size[2], const
                   real32_T B_0[4], real32_T C_data[], int32_T *C_size, DW *rtDW);
static real32_T KWIKfactor(const int16_T iC[5], int16_T nA, const real32_T
  Linv_data[], const int32_T Linv_size[2], real32_T RLinv_data[], const int32_T
  RLinv_size[2], real32_T D_data[], const int32_T D_size[2], real32_T H_data[],
  const int32_T H_size[2], int16_T n, DW *rtDW);
static real32_T mtimes_m(const real32_T A_data[], const real32_T B_1[4]);
static void DropConstraint(int16_T kDrop, int16_T iA[5], int16_T *nA, int16_T
  iC[5], DW *rtDW);
static void ResetToColdStart(int16_T iA[5], int16_T iC[5]);
static void qpkwik(const real32_T Linv_data[], const int32_T Linv_size[2], const
                   real32_T Hinv_data[], const int32_T Hinv_size[2], const
                   real32_T f[4], int16_T maxiter, int16_T n, real32_T x_data[],
                   int32_T *x_size, real32_T lambda[5], real32_T *status,
                   int16_T iA[5], DW *rtDW);
static int32_T cholesky(real32_T A_data[], int32_T A_size[2], DW *rtDW);
static void linsolve(const real32_T A_data[], const int32_T A_size[2], const
                     real_T B_data[], const int32_T B_size[2], real32_T C_data[],
                     int32_T C_size[2], DW *rtDW);
static void mpcActiveSetSolver(const real32_T H_data[], const int32_T H_size[2],
  const real32_T f[4], real32_T options_MaxIterations, real32_T x_data[],
  int32_T *x_size, real32_T *exitflag, DW *rtDW);

/*
 * Output and update for atomic system:
 *    '<S3>/detect_unsuited_sequence_1'
 *    '<S3>/detect_unsuited_sequence_2'
 *    '<S3>/detect_unsuited_sequence_3'
 *    '<S3>/detect_unsuited_sequence_4'
 *    '<S3>/detect_unsuited_sequence_5'
 *    '<S3>/detect_unsuited_sequence_6'
 */
static void detect_unsuited_sequence_1(const real32_T rtu_H[16], const real32_T
  rtu_f[4], boolean_T *rty_unsuited)
{
  int32_T i;
  real32_T z[4];
  real32_T lambda_ref;
  static const real32_T b[4] = { 0.5F, 0.0F, 0.0F, 0.5F };

  /*  pre calculations */
  /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/all/detect_unsuited_sequence_1': '<S8>:1' */
  /* '<S8>:1:4' t0 = [0.5 0 0 0.5]'; */
  /* '<S8>:1:5' g0 = H*t0-f; */
  /*  gradient vector g0=Hessian*initialpoint-f */
  /* '<S8>:1:7' z = t0-g0; */
  for (i = 0; i < 4; i++) {
    z[i] = b[i] - ((rtu_H[i + 12] * 0.5F + rtu_H[i] * 0.5F) - rtu_f[i]);
  }

  /* '<S8>:1:8' lambda_ref = (1-sum(z)) * 0.25; */
  lambda_ref = (1.0F - (((z[0] + z[1]) + z[2]) + z[3])) * 0.25F;

  /* '<S8>:1:9' tau_ref = lambda_ref*ones(4,1)+z; */
  /* '<S8>:1:10' unsuited = false; */
  *rty_unsuited = false;

  /* '<S8>:1:11' if (tau_ref(2) < 0 || tau_ref(3) < 0) */
  if (lambda_ref + z[1] < 0.0F) {
    /* '<S8>:1:12' unsuited = true; */
    *rty_unsuited = true;
  } else if (lambda_ref + z[2] < 0.0F) {
    /* '<S8>:1:12' unsuited = true; */
    *rty_unsuited = true;
  }
}

/*
 * Output and update for atomic system:
 *    '<S3>/formulate_qp_1'
 *    '<S3>/formulate_qp_2'
 *    '<S3>/formulate_qp_3'
 *    '<S3>/formulate_qp_4'
 *    '<S3>/formulate_qp_5'
 *    '<S3>/formulate_qp_6'
 *    '<S4>/formulate_qp_deadbeat'
 */
static void formulate_qp_1(const real32_T rtu_m0[2], const real32_T rtu_m1[2],
  const real32_T rtu_m2[2], const real32_T rtu_m3[2], real32_T rtu_id0, real32_T
  rtu_iq0, real32_T rtu_id_ref, real32_T rtu_iq_ref, real32_T rtu_lambda,
  real32_T rty_H[16], real32_T rty_f[4], real32_T rty_M[32], real32_T rty_r[8],
  DW_formulate_qp_1 *localDW)
{
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  int32_T tmp;
  real32_T e_i_idx_0;
  real32_T e_i_idx_1;
  real32_T lam;
  real32_T lam_0;
  real32_T lam_1;
  real32_T lam_idx_0;
  real32_T lam_idx_0_0;
  real32_T lam_idx_0_1;

  /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/all/formulate_qp_1': '<S14>:1' */
  /* '<S14>:1:4' lam = [lambda 0; 0 lambda]; */
  /* '<S14>:1:6' i_t0 = [id0 iq0]'; */
  /* '<S14>:1:7' i_ref = [id_ref iq_ref]'; */
  /* '<S14>:1:8' e_i = i_ref - i_t0; */
  e_i_idx_0 = rtu_id_ref - rtu_id0;
  e_i_idx_1 = rtu_iq_ref - rtu_iq0;

  /* '<S14>:1:10' r = [e_i; e_i; e_i; lam*e_i]; */
  rty_r[0] = e_i_idx_0;
  rty_r[2] = e_i_idx_0;
  rty_r[4] = e_i_idx_0;
  rty_r[6] = rtu_lambda * e_i_idx_0;
  rty_r[1] = e_i_idx_1;
  rty_r[3] = e_i_idx_1;
  rty_r[5] = e_i_idx_1;
  rty_r[7] = rtu_lambda * e_i_idx_1;

  /* '<S14>:1:12' zer = zeros(2,1); */
  /* '<S14>:1:13' m0_lam = lam*m0; */
  /* '<S14>:1:14' m1_lam = lam*m1; */
  /* '<S14>:1:15' m2_lam = lam*m2; */
  /* '<S14>:1:16' m3_lam = lam*m3; */
  /* '<S14>:1:18' M = [m0     zer     zer     zer     ; */
  /* '<S14>:1:19'      m0     m1      zer     zer     ; */
  /* '<S14>:1:20'      m0     m1      m2      zer     ; */
  /* '<S14>:1:21'      m0_lam m1_lam  m2_lam  m3_lam ]; */
  e_i_idx_0 = rtu_lambda * rtu_m0[0];
  e_i_idx_1 = rtu_lambda * rtu_m0[1];
  lam_idx_0 = rtu_lambda * rtu_m1[0];
  lam = rtu_lambda * rtu_m1[1];
  lam_idx_0_0 = rtu_lambda * rtu_m2[0];
  lam_0 = rtu_lambda * rtu_m2[1];
  lam_idx_0_1 = rtu_lambda * rtu_m3[0];
  lam_1 = rtu_lambda * rtu_m3[1];
  rty_M[0] = rtu_m0[0];
  rty_M[1] = rtu_m0[1];
  rty_M[8] = 0.0F;
  rty_M[16] = 0.0F;
  rty_M[24] = 0.0F;
  rty_M[9] = 0.0F;
  rty_M[17] = 0.0F;
  rty_M[25] = 0.0F;
  rty_M[2] = rtu_m0[0];
  rty_M[3] = rtu_m0[1];
  rty_M[10] = rtu_m1[0];
  rty_M[11] = rtu_m1[1];
  rty_M[18] = 0.0F;
  rty_M[26] = 0.0F;
  rty_M[19] = 0.0F;
  rty_M[27] = 0.0F;
  rty_M[4] = rtu_m0[0];
  rty_M[5] = rtu_m0[1];
  rty_M[12] = rtu_m1[0];
  rty_M[13] = rtu_m1[1];
  rty_M[20] = rtu_m2[0];
  rty_M[21] = rtu_m2[1];
  rty_M[28] = 0.0F;
  rty_M[6] = e_i_idx_0;
  rty_M[14] = lam_idx_0;
  rty_M[22] = lam_idx_0_0;
  rty_M[30] = lam_idx_0_1;
  rty_M[29] = 0.0F;
  rty_M[7] = e_i_idx_1;
  rty_M[15] = lam;
  rty_M[23] = lam_0;
  rty_M[31] = lam_1;

  /* '<S14>:1:23' H = 2*(M'*M); */
  for (i = 0; i < 8; i++) {
    i_1 = i << 2;
    localDW->fv[i_1] = rty_M[i];
    localDW->fv[i_1 + 1] = rty_M[i + 8];
    localDW->fv[i_1 + 2] = rty_M[i + 16];
    localDW->fv[i_1 + 3] = rty_M[i + 24];
  }

  for (i = 0; i < 4; i++) {
    for (i_1 = 0; i_1 < 4; i_1++) {
      tmp = i_1 + (i << 2);
      localDW->fv1[tmp] = 0.0F;
      for (i_0 = 0; i_0 < 8; i_0++) {
        localDW->fv1[tmp] += localDW->fv[(i_0 << 2) + i_1] * rty_M[(i << 3) +
          i_0];
      }
    }
  }

  for (i = 0; i < 16; i++) {
    rty_H[i] = 2.0F * localDW->fv1[i];
  }

  /* '<S14>:1:24' f = 2*M'*r; */
  for (i = 0; i < 4; i++) {
    rty_f[i] = 0.0F;
    for (i_1 = 0; i_1 < 8; i_1++) {
      rty_f[i] += localDW->fv[(i_1 << 2) + i] * 2.0F * rty_r[i_1];
    }
  }
}

/*
 * Output and update for atomic system:
 *    '<S3>/state_space_mdl_1'
 *    '<S3>/state_space_mdl_2'
 *    '<S3>/state_space_mdl_3'
 *    '<S3>/state_space_mdl_4'
 *    '<S3>/state_space_mdl_5'
 *    '<S3>/state_space_mdl_6'
 *    '<S4>/state_space_mdl_deadbeat'
 */
static void state_space_mdl_1(real32_T rtu_Ts_times_ZB_over_Ld, real32_T
  rtu_Ts_times_ZB_over_Lq, real32_T rtu_Rs_over_ZB, real32_T rtu_Ld_over_LB,
  real32_T rtu_Lq_over_LB, real32_T rtu_psi_pm_over_psiB, real32_T rtu_id_pu,
  real32_T rtu_iq_pu, real32_T rtu_w_e_pu, real32_T rtu_vd_1_pu, real32_T
  rtu_vq_1_pu, real32_T rtu_vd_2_pu, real32_T rtu_vq_2_pu, real32_T rty_m0[2],
  real32_T rty_m1[2], real32_T rty_m2[2], real32_T rty_m3[2],
  DW_state_space_mdl_1 *localDW)
{
  int32_T i;
  real32_T rtu_Ts_times_ZB_over_Ld_0[6];
  real32_T tmp[2];
  real32_T tmp_0[2];
  real32_T rty_m3_idx_0;
  real32_T rty_m3_idx_1;

  /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/all/state_space_mdl_1': '<S22>:1' */
  /* '<S22>:1:3' A = [ -Ts_times_ZB_over_Ld*Rs_over_ZB   Ts_times_ZB_over_Ld*Lq_over_LB*w_e_pu   0; */
  /* '<S22>:1:4'       -Ts_times_ZB_over_Lq*Ld_over_LB*w_e_pu  -Ts_times_ZB_over_Lq*Rs_over_ZB   -Ts_times_ZB_over_Lq*psi_pm_over_psiB]; */
  /* '<S22>:1:6' B = [Ts_times_ZB_over_Ld   0   0; */
  /* '<S22>:1:7'      0   Ts_times_ZB_over_Lq   0]; */
  localDW->B_m[0] = rtu_Ts_times_ZB_over_Ld;
  localDW->B_m[2] = 0.0F;
  localDW->B_m[4] = 0.0F;
  localDW->B_m[1] = 0.0F;
  localDW->B_m[3] = rtu_Ts_times_ZB_over_Lq;
  localDW->B_m[5] = 0.0F;

  /* '<S22>:1:9' C = [1 0; */
  /* '<S22>:1:10'      0 1]; */
  /* '<S22>:1:12' x0 = [id_pu; iq_pu; w_e_pu]; */
  /* '<S22>:1:14' u0 = [0;0;0]; */
  /*  zero voltage applied */
  /* '<S22>:1:15' u1 = [vd_1_pu; vq_1_pu; 0]; */
  /*  first active vector */
  /* '<S22>:1:16' u2 = [vd_2_pu; vq_2_pu; 0]; */
  /*  second active vector */
  /* '<S22>:1:18' m0 = C*(A*x0+B*u0); */
  rtu_Ts_times_ZB_over_Ld_0[0] = -rtu_Ts_times_ZB_over_Ld * rtu_Rs_over_ZB;
  rtu_Ts_times_ZB_over_Ld_0[2] = rtu_Ts_times_ZB_over_Ld * rtu_Lq_over_LB *
    rtu_w_e_pu;
  rtu_Ts_times_ZB_over_Ld_0[4] = 0.0F;
  rtu_Ts_times_ZB_over_Ld_0[1] = -rtu_Ts_times_ZB_over_Lq * rtu_Ld_over_LB *
    rtu_w_e_pu;
  rtu_Ts_times_ZB_over_Ld_0[3] = -rtu_Ts_times_ZB_over_Lq * rtu_Rs_over_ZB;
  rtu_Ts_times_ZB_over_Ld_0[5] = -rtu_Ts_times_ZB_over_Lq * rtu_psi_pm_over_psiB;
  for (i = 0; i < 2; i++) {
    rty_m3_idx_0 = rtu_Ts_times_ZB_over_Ld_0[i + 4] * rtu_w_e_pu +
      (rtu_Ts_times_ZB_over_Ld_0[i + 2] * rtu_iq_pu +
       rtu_Ts_times_ZB_over_Ld_0[i] * rtu_id_pu);
    tmp_0[i] = rty_m3_idx_0;
    tmp[i] = rty_m3_idx_0;
  }

  rty_m3[0] = 0.0F;
  rty_m3[0] += tmp_0[0];
  rty_m3[1] = 0.0F;
  rty_m3[1] += tmp_0[1];

  /* '<S22>:1:19' m1 = C*(A*x0+B*u1); */
  for (i = 0; i < 2; i++) {
    tmp_0[i] = (localDW->B_m[i + 2] * rtu_vq_1_pu + localDW->B_m[i] *
                rtu_vd_1_pu) + tmp[i];
  }

  rty_m1[0] = 0.0F;
  rty_m1[0] += tmp_0[0];
  rty_m1[1] = 0.0F;
  rty_m1[1] += tmp_0[1];

  /* '<S22>:1:20' m2 = C*(A*x0+B*u2); */
  for (i = 0; i < 2; i++) {
    tmp_0[i] = (localDW->B_m[i + 2] * rtu_vq_2_pu + localDW->B_m[i] *
                rtu_vd_2_pu) + tmp[i];
  }

  rty_m2[0] = 0.0F;
  rty_m2[0] += tmp_0[0];
  rty_m2[1] = 0.0F;
  rty_m2[1] += tmp_0[1];

  /* '<S22>:1:21' m3 = m0; */
  rty_m3_idx_0 = rty_m3[0];
  rty_m3_idx_1 = rty_m3[1];
  rty_m0[0] = rty_m3_idx_0;
  rty_m0[1] = rty_m3_idx_1;
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void trisolve(const real32_T A_data[], const int32_T A_size[2], real32_T
                     B_data[], const int32_T B_size[2], DW *rtDW)
{
  int32_T tmp;
  int32_T tmp_0;
  rtDW->mB = B_size[0];
  rtDW->nB = B_size[1] - 1;
  if (A_size[0] < A_size[1]) {
    rtDW->n_e = A_size[0];
  } else {
    rtDW->n_e = A_size[1];
  }

  if (rtDW->n_e >= B_size[0]) {
    rtDW->n_e = B_size[0];
  }

  if ((B_size[1] != 0) && ((B_size[0] != 0) && (B_size[1] != 0))) {
    rtDW->j_o = 0;
    while (rtDW->j_o <= rtDW->nB) {
      rtDW->jBcol = rtDW->mB * rtDW->j_o - 1;
      rtDW->k = 1;
      while (rtDW->k - 1 <= rtDW->n_e - 1) {
        rtDW->kAcol = (rtDW->k - 1) * A_size[0] - 1;
        tmp = rtDW->k + rtDW->jBcol;
        if (B_data[tmp] != 0.0F) {
          B_data[tmp] /= A_data[rtDW->k + rtDW->kAcol];
          rtDW->i_h = rtDW->k + 1;
          while (rtDW->i_h <= rtDW->n_e) {
            tmp_0 = rtDW->i_h + rtDW->jBcol;
            B_data[tmp_0] -= B_data[tmp] * A_data[rtDW->i_h + rtDW->kAcol];
            rtDW->i_h++;
          }
        }

        rtDW->k++;
      }

      rtDW->j_o++;
    }
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void Unconstrained(const real32_T Hinv_data[], const int32_T Hinv_size[2],
  const real32_T f[4], real32_T x_data[], int16_T n)
{
  int32_T i;
  for (i = 1; i - 1 < n; i++) {
    x_data[(int16_T)i - 1] = ((-Hinv_data[(int16_T)i - 1] * f[0] + -Hinv_data
      [((int16_T)i + Hinv_size[0]) - 1] * f[1]) + -Hinv_data[((int16_T)i +
      (Hinv_size[0] << 1)) - 1] * f[2]) + -Hinv_data[((int16_T)i + Hinv_size[0] *
      3) - 1] * f[3];
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static real32_T norm(const real32_T x_data[], const int32_T *x_size, DW *rtDW)
{
  int32_T k;
  real32_T y;
  if (*x_size == 0) {
    y = 0.0F;
  } else {
    y = 0.0F;
    if (*x_size == 1) {
      y = fabsf(x_data[0]);
    } else {
      rtDW->scale_b = 1.29246971E-26F;
      for (k = 0; k < *x_size; k++) {
        rtDW->absxk_j = fabsf(x_data[k]);
        if (rtDW->absxk_j > rtDW->scale_b) {
          rtDW->t_f = rtDW->scale_b / rtDW->absxk_j;
          y = y * rtDW->t_f * rtDW->t_f + 1.0F;
          rtDW->scale_b = rtDW->absxk_j;
        } else {
          rtDW->t_f = rtDW->absxk_j / rtDW->scale_b;
          y += rtDW->t_f * rtDW->t_f;
        }
      }

      y = rtDW->scale_b * sqrtf(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void abs_d(const real32_T x[4], real32_T y[4])
{
  y[0] = fabsf(x[0]);
  y[1] = fabsf(x[1]);
  y[2] = fabsf(x[2]);
  y[3] = fabsf(x[3]);
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static real32_T maximum(const real32_T x[4])
{
  real32_T ex;
  ex = x[0];
  if (x[0] < x[1]) {
    ex = x[1];
  }

  if (ex < x[2]) {
    ex = x[2];
  }

  if (ex < x[3]) {
    ex = x[3];
  }

  return ex;
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void maximum2(const real32_T x[5], real32_T ex[5])
{
  int32_T k;
  for (k = 0; k < 5; k++) {
    ex[k] = fmaxf(x[k], 1.0F);
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static real32_T xnrm2(int32_T n, const real32_T x_data[], int32_T ix0, DW *rtDW)
{
  real32_T y;
  y = 0.0F;
  if (n >= 1) {
    if (n == 1) {
      y = fabsf(x_data[ix0 - 1]);
    } else {
      rtDW->scale = 1.29246971E-26F;
      rtDW->kend = (ix0 + n) - 1;
      rtDW->k_m = ix0;
      while (rtDW->k_m <= rtDW->kend) {
        rtDW->absxk = fabsf(x_data[rtDW->k_m - 1]);
        if (rtDW->absxk > rtDW->scale) {
          rtDW->t_e = rtDW->scale / rtDW->absxk;
          y = y * rtDW->t_e * rtDW->t_e + 1.0F;
          rtDW->scale = rtDW->absxk;
        } else {
          rtDW->t_e = rtDW->absxk / rtDW->scale;
          y += rtDW->t_e * rtDW->t_e;
        }

        rtDW->k_m++;
      }

      y = rtDW->scale * sqrtf(y);
    }
  }

  return y;
}

static real32_T rt_hypotf_p(real32_T u0, real32_T u1, DW *rtDW)
{
  real32_T y;
  rtDW->a = fabsf(u0);
  rtDW->b = fabsf(u1);
  if (rtDW->a < rtDW->b) {
    rtDW->a /= rtDW->b;
    y = sqrtf(rtDW->a * rtDW->a + 1.0F) * rtDW->b;
  } else if (rtDW->a > rtDW->b) {
    rtDW->b /= rtDW->a;
    y = sqrtf(rtDW->b * rtDW->b + 1.0F) * rtDW->a;
  } else {
    y = rtDW->a * 1.41421354F;
  }

  return y;
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void xgemv(int32_T m, int32_T n, const real32_T A_data[], int32_T ia0,
                  int32_T lda, const real32_T x_data[], int32_T ix0, real32_T
                  y_data[], DW *rtDW)
{
  if (n != 0) {
    rtDW->b_iy_l = 0;
    while (rtDW->b_iy_l <= n - 1) {
      y_data[rtDW->b_iy_l] = 0.0F;
      rtDW->b_iy_l++;
    }

    rtDW->b_iy_l = 0;
    rtDW->b_m = (n - 1) * lda + ia0;
    rtDW->iac = ia0;
    while (((lda > 0) && (rtDW->iac <= rtDW->b_m)) || ((lda < 0) && (rtDW->iac >=
             rtDW->b_m))) {
      rtDW->ix_o = ix0;
      rtDW->c = 0.0F;
      rtDW->d_m = (rtDW->iac + m) - 1;
      rtDW->ia_cn = rtDW->iac;
      while (rtDW->ia_cn <= rtDW->d_m) {
        rtDW->c += A_data[rtDW->ia_cn - 1] * x_data[rtDW->ix_o - 1];
        rtDW->ix_o++;
        rtDW->ia_cn++;
      }

      y_data[rtDW->b_iy_l] += rtDW->c;
      rtDW->b_iy_l++;
      rtDW->iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void xgerc(int32_T m, int32_T n, real32_T alpha1, int32_T ix0, const
                  real32_T y_data[], real32_T A_data[], int32_T ia0, int32_T lda,
                  DW *rtDW)
{
  if (alpha1 != 0.0F) {
    rtDW->jA = ia0 - 1;
    rtDW->jy = 0;
    rtDW->j_h = 0;
    while (rtDW->j_h <= n - 1) {
      if (y_data[rtDW->jy] != 0.0F) {
        rtDW->temp = y_data[rtDW->jy] * alpha1;
        rtDW->ix = ix0;
        rtDW->b_c0 = m + rtDW->jA;
        rtDW->ijA = rtDW->jA;
        while (rtDW->ijA + 1 <= rtDW->b_c0) {
          A_data[rtDW->ijA] += A_data[rtDW->ix - 1] * rtDW->temp;
          rtDW->ix++;
          rtDW->ijA++;
        }
      }

      rtDW->jy++;
      rtDW->jA += lda;
      rtDW->j_h++;
    }
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void xgeqrf(real32_T A_data[], const int32_T A_size[2], real32_T
                   tau_data[], int32_T *tau_size, DW *rtDW)
{
  int32_T exitg1;
  boolean_T exitg2;
  rtDW->m_m3 = A_size[0];
  rtDW->n = A_size[1];
  if (A_size[0] < A_size[1]) {
    rtDW->minmana = A_size[0];
  } else {
    rtDW->minmana = A_size[1];
  }

  if (A_size[0] < A_size[1]) {
    rtDW->minmn = A_size[0];
  } else {
    rtDW->minmn = A_size[1];
  }

  *tau_size = rtDW->minmana;
  if (0 <= rtDW->minmana - 1) {
    memset(&tau_data[0], 0, rtDW->minmana * sizeof(real32_T));
  }

  if ((A_size[0] != 0) && (A_size[1] != 0) && (rtDW->minmn >= 1)) {
    *tau_size = rtDW->minmana;
    if (0 <= rtDW->minmana - 1) {
      memset(&tau_data[0], 0, rtDW->minmana * sizeof(real32_T));
    }

    rtDW->minmana = A_size[0];
    rtDW->ii = A_size[1];
    if (0 <= rtDW->ii - 1) {
      memset(&rtDW->work_data[0], 0, rtDW->ii * sizeof(real32_T));
    }

    rtDW->i_j = 0;
    while (rtDW->i_j <= rtDW->minmn - 1) {
      rtDW->ii = rtDW->i_j * rtDW->minmana + rtDW->i_j;
      rtDW->mmi = rtDW->m_m3 - rtDW->i_j;
      if (rtDW->i_j + 1 < rtDW->m_m3) {
        rtDW->b_atmp = A_data[rtDW->ii];
        tau_data[rtDW->i_j] = 0.0F;
        if (rtDW->mmi > 0) {
          rtDW->beta1 = xnrm2(rtDW->mmi - 1, A_data, rtDW->ii + 2, rtDW);
          if (rtDW->beta1 != 0.0F) {
            rtDW->beta1 = rt_hypotf_p(A_data[rtDW->ii], rtDW->beta1, rtDW);
            if (A_data[rtDW->ii] >= 0.0F) {
              rtDW->beta1 = -rtDW->beta1;
            }

            if (fabsf(rtDW->beta1) < 9.86076132E-32F) {
              rtDW->knt = -1;
              rtDW->b_k = rtDW->ii + rtDW->mmi;
              do {
                rtDW->knt++;
                rtDW->c_k = rtDW->ii + 1;
                while (rtDW->c_k + 1 <= rtDW->b_k) {
                  A_data[rtDW->c_k] *= 1.01412048E+31F;
                  rtDW->c_k++;
                }

                rtDW->beta1 *= 1.01412048E+31F;
                rtDW->b_atmp *= 1.01412048E+31F;
              } while (fabsf(rtDW->beta1) < 9.86076132E-32F);

              rtDW->beta1 = rt_hypotf_p(rtDW->b_atmp, xnrm2(rtDW->mmi - 1,
                A_data, rtDW->ii + 2, rtDW), rtDW);
              if (rtDW->b_atmp >= 0.0F) {
                rtDW->beta1 = -rtDW->beta1;
              }

              tau_data[rtDW->i_j] = (rtDW->beta1 - rtDW->b_atmp) / rtDW->beta1;
              rtDW->b_atmp = 1.0F / (rtDW->b_atmp - rtDW->beta1);
              rtDW->b_k = rtDW->ii + rtDW->mmi;
              rtDW->c_k = rtDW->ii + 1;
              while (rtDW->c_k + 1 <= rtDW->b_k) {
                A_data[rtDW->c_k] *= rtDW->b_atmp;
                rtDW->c_k++;
              }

              rtDW->c_k = 0;
              while (rtDW->c_k <= rtDW->knt) {
                rtDW->beta1 *= 9.86076132E-32F;
                rtDW->c_k++;
              }

              rtDW->b_atmp = rtDW->beta1;
            } else {
              tau_data[rtDW->i_j] = (rtDW->beta1 - A_data[rtDW->ii]) /
                rtDW->beta1;
              rtDW->b_atmp = 1.0F / (A_data[rtDW->ii] - rtDW->beta1);
              rtDW->knt = rtDW->ii + rtDW->mmi;
              rtDW->b_k = rtDW->ii + 1;
              while (rtDW->b_k + 1 <= rtDW->knt) {
                A_data[rtDW->b_k] *= rtDW->b_atmp;
                rtDW->b_k++;
              }

              rtDW->b_atmp = rtDW->beta1;
            }
          }
        }

        A_data[rtDW->ii] = rtDW->b_atmp;
      } else {
        tau_data[rtDW->i_j] = 0.0F;
      }

      if (rtDW->i_j + 1 < rtDW->n) {
        rtDW->b_atmp = A_data[rtDW->ii];
        A_data[rtDW->ii] = 1.0F;
        rtDW->c_k = (rtDW->ii + rtDW->minmana) + 1;
        if (tau_data[rtDW->i_j] != 0.0F) {
          rtDW->mmip1 = (rtDW->ii + rtDW->mmi) - 1;
          while ((rtDW->mmi > 0) && (A_data[rtDW->mmip1] == 0.0F)) {
            rtDW->mmi--;
            rtDW->mmip1--;
          }

          rtDW->mmip1 = (rtDW->n - rtDW->i_j) - 1;
          exitg2 = false;
          while ((!exitg2) && (rtDW->mmip1 > 0)) {
            rtDW->knt = (rtDW->mmip1 - 1) * rtDW->minmana + rtDW->c_k;
            rtDW->b_k = rtDW->knt;
            do {
              exitg1 = 0;
              if (rtDW->b_k <= (rtDW->knt + rtDW->mmi) - 1) {
                if (A_data[rtDW->b_k - 1] != 0.0F) {
                  exitg1 = 1;
                } else {
                  rtDW->b_k++;
                }
              } else {
                rtDW->mmip1--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          rtDW->mmi = 0;
          rtDW->mmip1 = 0;
        }

        if (rtDW->mmi > 0) {
          xgemv(rtDW->mmi, rtDW->mmip1, A_data, rtDW->c_k, rtDW->minmana, A_data,
                rtDW->ii + 1, rtDW->work_data, rtDW);
          xgerc(rtDW->mmi, rtDW->mmip1, -tau_data[rtDW->i_j], rtDW->ii + 1,
                rtDW->work_data, A_data, rtDW->c_k, rtDW->minmana, rtDW);
        }

        A_data[rtDW->ii] = rtDW->b_atmp;
      }

      rtDW->i_j++;
    }
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void xorgqr(int32_T m, int32_T n, int32_T k, real32_T A_data[], const
                   int32_T A_size[2], int32_T lda, const real32_T tau_data[], DW
                   *rtDW)
{
  int32_T exitg1;
  boolean_T exitg2;
  if (n >= 1) {
    rtDW->itau = k;
    while (rtDW->itau <= n - 1) {
      rtDW->i_a = rtDW->itau * lda;
      rtDW->iaii = 0;
      while (rtDW->iaii <= m - 1) {
        A_data[rtDW->i_a + rtDW->iaii] = 0.0F;
        rtDW->iaii++;
      }

      A_data[rtDW->i_a + rtDW->itau] = 1.0F;
      rtDW->itau++;
    }

    rtDW->itau = k - 1;
    rtDW->iaii = (int8_T)A_size[1];
    if (0 <= rtDW->iaii - 1) {
      memset(&rtDW->work_data_j[0], 0, rtDW->iaii * sizeof(real32_T));
    }

    rtDW->i_a = k;
    while (rtDW->i_a >= 1) {
      rtDW->iaii = (rtDW->i_a - 1) * lda + rtDW->i_a;
      if (rtDW->i_a < n) {
        A_data[rtDW->iaii - 1] = 1.0F;
        rtDW->lastc = (m - rtDW->i_a) - 1;
        rtDW->c_c = rtDW->iaii + lda;
        if (tau_data[rtDW->itau] != 0.0F) {
          rtDW->lastv = rtDW->lastc + 2;
          rtDW->lastc += rtDW->iaii;
          while ((rtDW->lastv > 0) && (A_data[rtDW->lastc] == 0.0F)) {
            rtDW->lastv--;
            rtDW->lastc--;
          }

          rtDW->lastc = n - rtDW->i_a;
          exitg2 = false;
          while ((!exitg2) && (rtDW->lastc > 0)) {
            rtDW->coltop = (rtDW->lastc - 1) * lda + rtDW->c_c;
            rtDW->ia_c = rtDW->coltop;
            do {
              exitg1 = 0;
              if (rtDW->ia_c <= (rtDW->coltop + rtDW->lastv) - 1) {
                if (A_data[rtDW->ia_c - 1] != 0.0F) {
                  exitg1 = 1;
                } else {
                  rtDW->ia_c++;
                }
              } else {
                rtDW->lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          rtDW->lastv = 0;
          rtDW->lastc = 0;
        }

        if (rtDW->lastv > 0) {
          xgemv(rtDW->lastv, rtDW->lastc, A_data, rtDW->c_c, lda, A_data,
                rtDW->iaii, rtDW->work_data_j, rtDW);
          xgerc(rtDW->lastv, rtDW->lastc, -tau_data[rtDW->itau], rtDW->iaii,
                rtDW->work_data_j, A_data, rtDW->c_c, lda, rtDW);
        }
      }

      if (rtDW->i_a < m) {
        rtDW->c_c = (rtDW->iaii + m) - rtDW->i_a;
        rtDW->lastv = rtDW->iaii;
        while (rtDW->lastv + 1 <= rtDW->c_c) {
          A_data[rtDW->lastv] *= -tau_data[rtDW->itau];
          rtDW->lastv++;
        }
      }

      A_data[rtDW->iaii - 1] = 1.0F - tau_data[rtDW->itau];
      rtDW->c_c = 0;
      while (rtDW->c_c <= rtDW->i_a - 2) {
        A_data[(rtDW->iaii - rtDW->c_c) - 2] = 0.0F;
        rtDW->c_c++;
      }

      rtDW->itau--;
      rtDW->i_a--;
    }
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void mtimes(const real32_T A_data[], const int32_T A_size[2], const
                   real32_T B_0[4], real32_T C_data[], int32_T *C_size, DW *rtDW)
{
  rtDW->m_mc = A_size[0] - 1;
  *C_size = A_size[0];
  rtDW->i_h3 = 0;
  while (rtDW->i_h3 <= rtDW->m_mc) {
    C_data[rtDW->i_h3] = 0.0F;
    rtDW->i_h3++;
  }

  rtDW->i_h3 = 0;
  while (rtDW->i_h3 <= A_size[1] - 1) {
    rtDW->aoffset = rtDW->i_h3 * A_size[0];
    rtDW->b_i_c = 0;
    while (rtDW->b_i_c <= rtDW->m_mc) {
      C_data[rtDW->b_i_c] += A_data[rtDW->aoffset + rtDW->b_i_c] * B_0
        [rtDW->i_h3];
      rtDW->b_i_c++;
    }

    rtDW->i_h3++;
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static real32_T KWIKfactor(const int16_T iC[5], int16_T nA, const real32_T
  Linv_data[], const int32_T Linv_size[2], real32_T RLinv_data[], const int32_T
  RLinv_size[2], real32_T D_data[], const int32_T D_size[2], real32_T H_data[],
  const int32_T H_size[2], int16_T n, DW *rtDW)
{
  real32_T Status;
  int16_T b_j;
  int16_T c_k;
  static const int8_T Ac[20] = { 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
    0, 0, 1, 1 };

  int32_T exitg1;
  rtDW->TL_size_idx_0 = Linv_size[0];
  Status = 1.0F;
  rtDW->b_n = RLinv_size[0];
  rtDW->RLinv = RLinv_size[1];
  for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
    for (rtDW->m_m = 0; rtDW->m_m < rtDW->b_n; rtDW->m_m++) {
      RLinv_data[rtDW->m_m + RLinv_size[0] * rtDW->h_j] = 0.0F;
    }
  }

  rtDW->m_m = 1;
  while (rtDW->m_m - 1 <= nA - 1) {
    rtDW->h_j = iC[(int16_T)rtDW->m_m - 1];
    rtDW->Ac[0] = Ac[rtDW->h_j - 1];
    rtDW->Ac[1] = Ac[rtDW->h_j + 4];
    rtDW->Ac[2] = Ac[rtDW->h_j + 9];
    rtDW->Ac[3] = Ac[rtDW->h_j + 14];
    mtimes(Linv_data, Linv_size, rtDW->Ac, rtDW->tau_data, &rtDW->tau_size, rtDW);
    rtDW->RLinv = rtDW->tau_size;
    for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
      RLinv_data[rtDW->h_j + RLinv_size[0] * ((int16_T)rtDW->m_m - 1)] =
        rtDW->tau_data[rtDW->h_j];
    }

    rtDW->m_m++;
  }

  rtDW->m_m = RLinv_size[0] - 1;
  rtDW->b_n = RLinv_size[1];
  rtDW->Q_size[0] = (int8_T)RLinv_size[0];
  rtDW->Q_size[1] = (int8_T)RLinv_size[0];
  rtDW->R_size_idx_0 = RLinv_size[0];
  if (RLinv_size[0] > RLinv_size[1]) {
    rtDW->h_j = 0;
    while (rtDW->h_j <= rtDW->b_n - 1) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m_m) {
        rtDW->Q_data[rtDW->RLinv + rtDW->Q_size[0] * rtDW->h_j] =
          RLinv_data[rtDW->RLinv + RLinv_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    rtDW->h_j = RLinv_size[1];
    while (rtDW->h_j + 1 <= rtDW->m_m + 1) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m_m) {
        rtDW->Q_data[rtDW->RLinv + rtDW->Q_size[0] * rtDW->h_j] = 0.0F;
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    xgeqrf(rtDW->Q_data, rtDW->Q_size, rtDW->tau_data, &rtDW->tau_size, rtDW);
    rtDW->h_j = 0;
    while (rtDW->h_j <= rtDW->b_n - 1) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->h_j) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] =
          rtDW->Q_data[rtDW->RLinv + rtDW->Q_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->RLinv = rtDW->h_j + 1;
      while (rtDW->RLinv + 1 <= rtDW->m_m + 1) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] = 0.0F;
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    xorgqr(RLinv_size[0], RLinv_size[0], RLinv_size[1], rtDW->Q_data,
           rtDW->Q_size, RLinv_size[0], rtDW->tau_data, rtDW);
  } else {
    rtDW->A_size[0] = RLinv_size[0];
    rtDW->A_size[1] = RLinv_size[1];
    rtDW->RLinv = RLinv_size[0] * RLinv_size[1];
    if (0 <= rtDW->RLinv - 1) {
      memcpy(&rtDW->A_data[0], &RLinv_data[0], rtDW->RLinv * sizeof(real32_T));
    }

    xgeqrf(rtDW->A_data, rtDW->A_size, rtDW->tau_data, &rtDW->tau_size, rtDW);
    rtDW->h_j = 0;
    while (rtDW->h_j <= rtDW->m_m) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->h_j) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] =
          rtDW->A_data[rtDW->RLinv + rtDW->A_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->RLinv = rtDW->h_j + 1;
      while (rtDW->RLinv + 1 <= rtDW->m_m + 1) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] = 0.0F;
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    rtDW->h_j = RLinv_size[0];
    while (rtDW->h_j + 1 <= rtDW->b_n) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m_m) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] =
          rtDW->A_data[rtDW->RLinv + rtDW->A_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    xorgqr(RLinv_size[0], RLinv_size[0], RLinv_size[0], rtDW->A_data,
           rtDW->A_size, RLinv_size[0], rtDW->tau_data, rtDW);
    rtDW->b_n = 0;
    while (rtDW->b_n <= rtDW->m_m) {
      rtDW->h_j = 0;
      while (rtDW->h_j <= rtDW->m_m) {
        rtDW->Q_data[rtDW->h_j + rtDW->Q_size[0] * rtDW->b_n] = rtDW->
          A_data[rtDW->h_j + rtDW->A_size[0] * rtDW->b_n];
        rtDW->h_j++;
      }

      rtDW->b_n++;
    }
  }

  rtDW->m_m = 1;
  do {
    exitg1 = 0;
    if (rtDW->m_m - 1 <= nA - 1) {
      if (fabsf(rtDW->R_data[((int16_T)rtDW->m_m + rtDW->R_size_idx_0 *
                              ((int16_T)rtDW->m_m - 1)) - 1]) < 1.0E-12F) {
        Status = -2.0F;
        exitg1 = 1;
      } else {
        rtDW->m_m++;
      }
    } else {
      rtDW->m_m = 1;
      while (rtDW->m_m - 1 <= n - 1) {
        rtDW->b_n = 1;
        while (rtDW->b_n - 1 <= n - 1) {
          rtDW->RLinv = Linv_size[0];
          rtDW->Linv = 0.0F;
          for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
            rtDW->Linv += Linv_data[rtDW->h_j + Linv_size[0] * ((int16_T)
              rtDW->m_m - 1)] * rtDW->Q_data[rtDW->h_j + rtDW->Q_size[0] *
              ((int16_T)rtDW->b_n - 1)];
          }

          rtDW->TL_data[((int16_T)rtDW->m_m + rtDW->TL_size_idx_0 * ((int16_T)
            rtDW->b_n - 1)) - 1] = rtDW->Linv;
          rtDW->b_n++;
        }

        rtDW->m_m++;
      }

      rtDW->b_n = RLinv_size[0];
      rtDW->RLinv = RLinv_size[1];
      for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
        for (rtDW->m_m = 0; rtDW->m_m < rtDW->b_n; rtDW->m_m++) {
          RLinv_data[rtDW->m_m + RLinv_size[0] * rtDW->h_j] = 0.0F;
        }
      }

      for (b_j = nA; b_j > 0; b_j--) {
        RLinv_data[(b_j + RLinv_size[0] * (b_j - 1)) - 1] = 1.0F;
        for (c_k = b_j; c_k <= nA; c_k++) {
          rtDW->RLinv = (b_j + RLinv_size[0] * (c_k - 1)) - 1;
          RLinv_data[rtDW->RLinv] /= rtDW->R_data[(b_j + rtDW->R_size_idx_0 *
            (b_j - 1)) - 1];
        }

        if (b_j > 1) {
          rtDW->m_m = 1;
          while (rtDW->m_m - 1 <= b_j - 2) {
            for (c_k = b_j; c_k <= nA; c_k++) {
              rtDW->RLinv = RLinv_size[0] * (c_k - 1);
              rtDW->h_j = ((int16_T)rtDW->m_m + rtDW->RLinv) - 1;
              RLinv_data[rtDW->h_j] -= rtDW->R_data[((int16_T)rtDW->m_m +
                rtDW->R_size_idx_0 * (b_j - 1)) - 1] * RLinv_data[(b_j +
                rtDW->RLinv) - 1];
            }

            rtDW->m_m++;
          }
        }
      }

      rtDW->m_m = 1;
      while (rtDW->m_m - 1 <= n - 1) {
        for (b_j = (int16_T)rtDW->m_m; b_j <= n; b_j++) {
          rtDW->RLinv = ((int16_T)rtDW->m_m + H_size[0] * (b_j - 1)) - 1;
          H_data[rtDW->RLinv] = 0.0F;
          rtDW->h_j = nA + 1;
          if (nA + 1 > 32767) {
            rtDW->h_j = 32767;
          }

          for (c_k = (int16_T)rtDW->h_j; c_k <= n; c_k++) {
            rtDW->h_j = rtDW->TL_size_idx_0 * (c_k - 1);
            H_data[rtDW->RLinv] -= rtDW->TL_data[((int16_T)rtDW->m_m + rtDW->h_j)
              - 1] * rtDW->TL_data[(b_j + rtDW->h_j) - 1];
          }

          H_data[(b_j + H_size[0] * ((int16_T)rtDW->m_m - 1)) - 1] = H_data
            [rtDW->RLinv];
        }

        rtDW->m_m++;
      }

      rtDW->m_m = 1;
      while (rtDW->m_m - 1 <= nA - 1) {
        rtDW->b_n = 1;
        while (rtDW->b_n - 1 <= n - 1) {
          rtDW->RLinv = ((int16_T)rtDW->b_n + D_size[0] * ((int16_T)rtDW->m_m -
            1)) - 1;
          D_data[rtDW->RLinv] = 0.0F;
          for (b_j = (int16_T)rtDW->m_m; b_j <= nA; b_j++) {
            D_data[rtDW->RLinv] += rtDW->TL_data[((int16_T)rtDW->b_n +
              rtDW->TL_size_idx_0 * (b_j - 1)) - 1] * RLinv_data[((int16_T)
              rtDW->m_m + RLinv_size[0] * (b_j - 1)) - 1];
          }

          rtDW->b_n++;
        }

        rtDW->m_m++;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static real32_T mtimes_m(const real32_T A_data[], const real32_T B_1[4])
{
  return ((A_data[0] * B_1[0] + A_data[1] * B_1[1]) + A_data[2] * B_1[2]) +
    A_data[3] * B_1[3];
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void DropConstraint(int16_T kDrop, int16_T iA[5], int16_T *nA, int16_T
  iC[5], DW *rtDW)
{
  int16_T i;
  iA[iC[kDrop - 1] - 1] = 0;
  if (kDrop < *nA) {
    rtDW->i5 = *nA - 1;
    if (*nA - 1 < -32768) {
      rtDW->i5 = -32768;
    }

    for (i = kDrop; i <= (int16_T)rtDW->i5; i++) {
      iC[i - 1] = iC[i];
    }
  }

  iC[*nA - 1] = 0;
  rtDW->i5 = *nA - 1;
  if (*nA - 1 < -32768) {
    rtDW->i5 = -32768;
  }

  *nA = (int16_T)rtDW->i5;
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void ResetToColdStart(int16_T iA[5], int16_T iC[5])
{
  int32_T i;
  for (i = 0; i < 5; i++) {
    iA[i] = 0;
    iC[i] = 0;
  }

  iA[4] = 1;
  iC[0] = 5;
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void qpkwik(const real32_T Linv_data[], const int32_T Linv_size[2], const
                   real32_T Hinv_data[], const int32_T Hinv_size[2], const
                   real32_T f[4], int16_T maxiter, int16_T n, real32_T x_data[],
                   int32_T *x_size, real32_T lambda[5], real32_T *status,
                   int16_T iA[5], DW *rtDW)
{
  int16_T tmp;
  boolean_T ColdReset;
  boolean_T DualFeasible;
  boolean_T cTolComputed;
  static const int8_T h[5] = { 0, 0, 0, 0, 1 };

  static const int8_T Ac[20] = { 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
    0, 0, 1, 1 };

  static const real32_T varargin_1[5] = { 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };

  int32_T exitg1;
  int32_T exitg3;
  boolean_T exitg2;
  boolean_T exitg4;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *status = 1.0F;
  for (rtDW->i_m = 0; rtDW->i_m < 5; rtDW->i_m++) {
    iA[rtDW->i_m] = h[rtDW->i_m];
    lambda[rtDW->i_m] = 0.0F;
  }

  *x_size = n;
  rtDW->loop_ub = n;
  if (0 <= rtDW->loop_ub - 1) {
    memset(&x_data[0], 0, rtDW->loop_ub * sizeof(real32_T));
  }

  rtDW->loop_ub = n;
  if (0 <= rtDW->loop_ub - 1) {
    memset(&rtDW->r_data[0], 0, rtDW->loop_ub * sizeof(real32_T));
  }

  rtDW->rMin = 0.0F;
  rtDW->RLinv_size[0] = Linv_size[0];
  rtDW->RLinv_size[1] = Linv_size[1];
  rtDW->D_size[0] = Linv_size[0];
  rtDW->D_size[1] = Linv_size[1];
  rtDW->H_size[0] = Linv_size[0];
  rtDW->H_size[1] = Linv_size[1];
  rtDW->U_size[0] = Linv_size[0];
  cTolComputed = false;
  for (rtDW->i_m = 0; rtDW->i_m < 5; rtDW->i_m++) {
    rtDW->cTol[rtDW->i_m] = 1.0F;
    rtDW->iC[rtDW->i_m] = 0;
  }

  rtDW->nA = 0;
  for (rtDW->i_m = 0; rtDW->i_m < 5; rtDW->i_m++) {
    if (iA[rtDW->i_m] == 1) {
      rtDW->lambda_tmp_tmp = rtDW->nA + 1;
      if (rtDW->nA + 1 > 32767) {
        rtDW->lambda_tmp_tmp = 32767;
      }

      rtDW->nA = (int16_T)rtDW->lambda_tmp_tmp;
      rtDW->iC[(int16_T)rtDW->lambda_tmp_tmp - 1] = (int16_T)(rtDW->i_m + 1);
    }
  }

  guard1 = false;
  if (rtDW->nA > 0) {
    if (n > 16383) {
      rtDW->i8 = MAX_int16_T;
    } else if (n <= -16384) {
      rtDW->i8 = MIN_int16_T;
    } else {
      rtDW->i8 = (int16_T)(n << 1);
    }

    rtDW->i_m = rtDW->i8;
    if (0 <= rtDW->i_m - 1) {
      memset(&rtDW->Opt_data[0], 0, rtDW->i_m * sizeof(real32_T));
    }

    rtDW->Rhs_data[0] = f[0];
    rtDW->Rhs_data[1] = f[1];
    rtDW->Rhs_data[2] = f[2];
    rtDW->Rhs_data[3] = f[3];
    rtDW->loop_ub = n;
    if (0 <= rtDW->loop_ub - 1) {
      memset(&rtDW->Rhs_data[4], 0, rtDW->loop_ub * sizeof(real32_T));
    }

    DualFeasible = false;
    ColdReset = false;
    do {
      exitg3 = 0;
      if ((!DualFeasible) && (rtDW->nA > 0) && ((int32_T)*status <= maxiter)) {
        rtDW->Xnorm0 = KWIKfactor(rtDW->iC, rtDW->nA, Linv_data, Linv_size,
          rtDW->RLinv_data, rtDW->RLinv_size, rtDW->D_data, rtDW->D_size,
          rtDW->H_data, rtDW->H_size, n, rtDW);
        if (rtDW->Xnorm0 < 0.0F) {
          if (ColdReset) {
            *status = -2.0F;
            exitg3 = 2;
          } else {
            ResetToColdStart(iA, rtDW->iC);
            rtDW->nA = 1;
            ColdReset = true;
          }
        } else {
          rtDW->i_m = 1;
          while (rtDW->i_m - 1 <= rtDW->nA - 1) {
            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_m;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->lambda_tmp_tmp = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->lambda_tmp_tmp = -32768;
            }

            rtDW->Rhs_data[rtDW->lambda_tmp_tmp - 1] = h[rtDW->iC[(int16_T)
              rtDW->i_m - 1] - 1];
            rtDW->kNext = (int16_T)rtDW->i_m;
            while (rtDW->kNext <= rtDW->nA) {
              rtDW->lambda_tmp_tmp = (rtDW->kNext + rtDW->U_size[0] * ((int16_T)
                rtDW->i_m - 1)) - 1;
              rtDW->U_data[rtDW->lambda_tmp_tmp] = 0.0F;
              rtDW->H_cz = 1;
              while (rtDW->H_cz - 1 <= rtDW->nA - 1) {
                rtDW->loop_ub = rtDW->RLinv_size[0] * ((int16_T)rtDW->H_cz - 1);
                rtDW->U_data[rtDW->lambda_tmp_tmp] += rtDW->RLinv_data
                  [(rtDW->kNext + rtDW->loop_ub) - 1] * rtDW->RLinv_data
                  [((int16_T)rtDW->i_m + rtDW->loop_ub) - 1];
                rtDW->H_cz++;
              }

              rtDW->U_data[((int16_T)rtDW->i_m + rtDW->U_size[0] * (rtDW->kNext
                - 1)) - 1] = rtDW->U_data[rtDW->lambda_tmp_tmp];
              rtDW->kNext++;
            }

            rtDW->i_m++;
          }

          rtDW->i_m = 1;
          while (rtDW->i_m - 1 <= n - 1) {
            rtDW->loop_ub = rtDW->H_size[1];
            rtDW->Xnorm0 = 0.0F;
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < rtDW->loop_ub;
                 rtDW->lambda_tmp_tmp++) {
              rtDW->Xnorm0 += rtDW->H_data[((int16_T)rtDW->i_m + rtDW->H_size[0]
                * rtDW->lambda_tmp_tmp) - 1] * rtDW->Rhs_data
                [rtDW->lambda_tmp_tmp];
            }

            rtDW->Opt_data[(int16_T)rtDW->i_m - 1] = rtDW->Xnorm0;
            rtDW->H_cz = 1;
            while (rtDW->H_cz - 1 <= rtDW->nA - 1) {
              rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->H_cz;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->lambda_tmp_tmp = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->lambda_tmp_tmp = -32768;
              }

              rtDW->Opt_data[(int16_T)rtDW->i_m - 1] += rtDW->D_data[((int16_T)
                rtDW->i_m + rtDW->D_size[0] * ((int16_T)rtDW->H_cz - 1)) - 1] *
                rtDW->Rhs_data[rtDW->lambda_tmp_tmp - 1];
              rtDW->H_cz++;
            }

            rtDW->i_m++;
          }

          rtDW->i_m = 1;
          while (rtDW->i_m - 1 <= rtDW->nA - 1) {
            rtDW->loop_ub = rtDW->D_size[0];
            rtDW->Xnorm0 = 0.0F;
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp < rtDW->loop_ub;
                 rtDW->lambda_tmp_tmp++) {
              rtDW->Xnorm0 += rtDW->D_data[rtDW->lambda_tmp_tmp + rtDW->D_size[0]
                * ((int16_T)rtDW->i_m - 1)] * rtDW->Rhs_data
                [rtDW->lambda_tmp_tmp];
            }

            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_m;
            rtDW->loop_ub = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub = -32768;
            }

            rtDW->Opt_data[rtDW->loop_ub - 1] = rtDW->Xnorm0;
            rtDW->H_cz = 1;
            while (rtDW->H_cz - 1 <= rtDW->nA - 1) {
              rtDW->loop_ub = rtDW->lambda_tmp_tmp;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->loop_ub = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->loop_ub = -32768;
              }

              rtDW->i1 = rtDW->lambda_tmp_tmp;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->i1 = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->i1 = -32768;
              }

              rtDW->i2 = n + (int16_T)rtDW->H_cz;
              if (rtDW->i2 > 32767) {
                rtDW->i2 = 32767;
              } else if (rtDW->i2 < -32768) {
                rtDW->i2 = -32768;
              }

              rtDW->Opt_data[rtDW->loop_ub - 1] = rtDW->U_data[((int16_T)
                rtDW->i_m + rtDW->U_size[0] * ((int16_T)rtDW->H_cz - 1)) - 1] *
                rtDW->Rhs_data[rtDW->i2 - 1] + rtDW->Opt_data[rtDW->i1 - 1];
              rtDW->H_cz++;
            }

            rtDW->i_m++;
          }

          rtDW->Xnorm0 = -1.0E-12F;
          rtDW->kDrop = 0;
          rtDW->i_m = 1;
          while (rtDW->i_m - 1 <= rtDW->nA - 1) {
            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_m;
            rtDW->loop_ub = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub = -32768;
            }

            lambda[rtDW->iC[(int16_T)rtDW->i_m - 1] - 1] = rtDW->Opt_data
              [rtDW->loop_ub - 1];
            rtDW->loop_ub = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub = -32768;
            }

            if ((rtDW->Opt_data[rtDW->loop_ub - 1] < rtDW->Xnorm0) && ((int16_T)
                 rtDW->i_m <= rtDW->nA - 1)) {
              rtDW->kDrop = (int16_T)rtDW->i_m;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->lambda_tmp_tmp = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->lambda_tmp_tmp = -32768;
              }

              rtDW->Xnorm0 = rtDW->Opt_data[rtDW->lambda_tmp_tmp - 1];
            }

            rtDW->i_m++;
          }

          if (rtDW->kDrop <= 0) {
            DualFeasible = true;
            if (1 > n) {
              rtDW->loop_ub = -1;
            } else {
              rtDW->loop_ub = n - 1;
            }

            *x_size = rtDW->loop_ub + 1;
            if (0 <= rtDW->loop_ub) {
              memcpy(&x_data[0], &rtDW->Opt_data[0], (rtDW->loop_ub + 1) *
                     sizeof(real32_T));
            }
          } else {
            (*status)++;
            if (*status > 5.0F) {
              ResetToColdStart(iA, rtDW->iC);
              rtDW->nA = 1;
              ColdReset = true;
            } else {
              lambda[rtDW->iC[rtDW->kDrop - 1] - 1] = 0.0F;
              DropConstraint(rtDW->kDrop, iA, &rtDW->nA, rtDW->iC, rtDW);
            }
          }
        }
      } else {
        if (rtDW->nA <= 0) {
          for (rtDW->i_m = 0; rtDW->i_m < 5; rtDW->i_m++) {
            lambda[rtDW->i_m] = 0.0F;
          }

          Unconstrained(Hinv_data, Hinv_size, f, x_data, n);
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    Unconstrained(Hinv_data, Hinv_size, f, x_data, n);
    guard1 = true;
  }

  if (guard1) {
    rtDW->Xnorm0 = norm(x_data, x_size, rtDW);
    exitg2 = false;
    while ((!exitg2) && ((int32_T)*status <= maxiter)) {
      rtDW->cMin = -1.0E-6F;
      rtDW->kNext = 0;
      for (rtDW->i_m = 0; rtDW->i_m < 4; rtDW->i_m++) {
        rtDW->t = rtDW->cTol[rtDW->i_m];
        if (!cTolComputed) {
          rtDW->AcRow[0] = (real32_T)Ac[rtDW->i_m] * x_data[0];
          rtDW->AcRow[1] = (real32_T)Ac[rtDW->i_m + 5] * x_data[1];
          rtDW->AcRow[2] = (real32_T)Ac[rtDW->i_m + 10] * x_data[2];
          rtDW->AcRow[3] = (real32_T)Ac[rtDW->i_m + 15] * x_data[3];
          abs_d(rtDW->AcRow, rtDW->z_data);
          rtDW->t = fmaxf(rtDW->t, maximum(rtDW->z_data));
        }

        if (iA[rtDW->i_m] == 0) {
          rtDW->cVal = ((((real32_T)Ac[rtDW->i_m] * x_data[0] + (real32_T)
                          Ac[rtDW->i_m + 5] * x_data[1]) + (real32_T)Ac
                         [rtDW->i_m + 10] * x_data[2]) + (real32_T)Ac[rtDW->i_m
                        + 15] * x_data[3]) / rtDW->t;
          if (rtDW->cVal < rtDW->cMin) {
            rtDW->cMin = rtDW->cVal;
            rtDW->kNext = (int16_T)(rtDW->i_m + 1);
          }
        }

        rtDW->cTol[rtDW->i_m] = rtDW->t;
      }

      cTolComputed = true;
      if (rtDW->kNext <= 0) {
        exitg2 = true;
      } else if ((int32_T)*status == maxiter) {
        *status = 0.0F;
        exitg2 = true;
      } else {
        do {
          exitg1 = 0;
          if ((rtDW->kNext > 0) && ((int32_T)*status <= maxiter)) {
            rtDW->AcRow[0] = Ac[rtDW->kNext - 1];
            rtDW->AcRow[1] = Ac[rtDW->kNext + 4];
            rtDW->AcRow[2] = Ac[rtDW->kNext + 9];
            rtDW->AcRow[3] = Ac[rtDW->kNext + 14];
            guard2 = false;
            if (rtDW->nA == 0) {
              mtimes(Hinv_data, Hinv_size, rtDW->AcRow, rtDW->z_data,
                     &rtDW->z_size, rtDW);
              guard2 = true;
            } else {
              rtDW->cMin = KWIKfactor(rtDW->iC, rtDW->nA, Linv_data, Linv_size,
                rtDW->RLinv_data, rtDW->RLinv_size, rtDW->D_data, rtDW->D_size,
                rtDW->H_data, rtDW->H_size, n, rtDW);
              if (rtDW->cMin <= 0.0F) {
                *status = -2.0F;
                exitg1 = 1;
              } else {
                rtDW->U_size[0] = rtDW->H_size[0];
                rtDW->U_size[1] = rtDW->H_size[1];
                rtDW->loop_ub = rtDW->H_size[0] * rtDW->H_size[1];
                for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                     rtDW->loop_ub; rtDW->lambda_tmp_tmp++) {
                  rtDW->U_data[rtDW->lambda_tmp_tmp] = -rtDW->H_data
                    [rtDW->lambda_tmp_tmp];
                }

                mtimes(rtDW->U_data, rtDW->U_size, rtDW->AcRow, rtDW->z_data,
                       &rtDW->z_size, rtDW);
                rtDW->i_m = 1;
                while (rtDW->i_m - 1 <= rtDW->nA - 1) {
                  rtDW->lambda_tmp_tmp = rtDW->D_size[0] * ((int16_T)rtDW->i_m -
                    1);
                  rtDW->r_data[(int16_T)rtDW->i_m - 1] = ((rtDW->D_data
                    [rtDW->lambda_tmp_tmp] * rtDW->AcRow[0] + rtDW->D_data[1 +
                    rtDW->lambda_tmp_tmp] * rtDW->AcRow[1]) + rtDW->D_data[2 +
                    rtDW->lambda_tmp_tmp] * rtDW->AcRow[2]) + rtDW->D_data[3 +
                    rtDW->lambda_tmp_tmp] * rtDW->AcRow[3];
                  rtDW->i_m++;
                }

                guard2 = true;
              }
            }

            if (guard2) {
              rtDW->kDrop = 0;
              rtDW->cMin = 0.0F;
              DualFeasible = true;
              ColdReset = true;
              if (rtDW->nA > 1) {
                rtDW->i_m = 0;
                exitg4 = false;
                while ((!exitg4) && (rtDW->i_m <= rtDW->nA - 2)) {
                  if (rtDW->r_data[rtDW->i_m] >= 1.0E-12F) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    rtDW->i_m++;
                  }
                }
              }

              if ((rtDW->nA != 1) && (!ColdReset)) {
                rtDW->lambda_tmp_tmp = rtDW->nA - 1;
                if (rtDW->nA - 1 < -32768) {
                  rtDW->lambda_tmp_tmp = -32768;
                }

                rtDW->i_m = 1;
                while (rtDW->i_m - 1 <= (int16_T)rtDW->lambda_tmp_tmp - 1) {
                  rtDW->cVal = rtDW->r_data[(int16_T)rtDW->i_m - 1];
                  if (rtDW->cVal > 1.0E-12F) {
                    rtDW->cVal = lambda[rtDW->iC[(int16_T)rtDW->i_m - 1] - 1] /
                      rtDW->cVal;
                    if ((rtDW->kDrop == 0) || (rtDW->cVal < rtDW->rMin)) {
                      rtDW->rMin = rtDW->cVal;
                      rtDW->kDrop = (int16_T)rtDW->i_m;
                    }
                  }

                  rtDW->i_m++;
                }

                if (rtDW->kDrop > 0) {
                  rtDW->cMin = rtDW->rMin;
                  DualFeasible = false;
                }
              }

              rtDW->cVal = mtimes_m(rtDW->z_data, rtDW->AcRow);
              if (rtDW->cVal <= 0.0F) {
                rtDW->cVal = 0.0F;
                ColdReset = true;
              } else {
                rtDW->cVal = (-0.0F - (((rtDW->AcRow[0] * x_data[0] +
                  rtDW->AcRow[1] * x_data[1]) + rtDW->AcRow[2] * x_data[2]) +
                  rtDW->AcRow[3] * x_data[3])) / rtDW->cVal;
                ColdReset = false;
              }

              if (DualFeasible && ColdReset) {
                *status = -1.0F;
                exitg1 = 1;
              } else {
                if (ColdReset) {
                  rtDW->t = rtDW->cMin;
                } else if (DualFeasible) {
                  rtDW->t = rtDW->cVal;
                } else {
                  rtDW->t = fminf(rtDW->cMin, rtDW->cVal);
                }

                rtDW->i_m = 1;
                while (rtDW->i_m - 1 <= rtDW->nA - 1) {
                  rtDW->lambda_tmp_tmp = rtDW->iC[(int16_T)rtDW->i_m - 1];
                  lambda[rtDW->lambda_tmp_tmp - 1] -= rtDW->r_data[(int16_T)
                    rtDW->i_m - 1] * rtDW->t;
                  if ((rtDW->lambda_tmp_tmp <= 4) && (lambda
                       [rtDW->lambda_tmp_tmp - 1] < 0.0F)) {
                    lambda[rtDW->lambda_tmp_tmp - 1] = 0.0F;
                  }

                  rtDW->i_m++;
                }

                lambda[rtDW->kNext - 1] += rtDW->t;
                if (rtDW->t == rtDW->cMin) {
                  DropConstraint(rtDW->kDrop, iA, &rtDW->nA, rtDW->iC, rtDW);
                }

                if (!ColdReset) {
                  rtDW->loop_ub = *x_size;
                  for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                       rtDW->loop_ub; rtDW->lambda_tmp_tmp++) {
                    x_data[rtDW->lambda_tmp_tmp] += rtDW->t * rtDW->z_data
                      [rtDW->lambda_tmp_tmp];
                  }

                  if (rtDW->t == rtDW->cVal) {
                    if (rtDW->nA == n) {
                      *status = -1.0F;
                      exitg1 = 1;
                    } else {
                      rtDW->lambda_tmp_tmp = rtDW->nA + 1;
                      if (rtDW->nA + 1 > 32767) {
                        rtDW->lambda_tmp_tmp = 32767;
                      }

                      rtDW->nA = (int16_T)rtDW->lambda_tmp_tmp;
                      rtDW->iC[(int16_T)rtDW->lambda_tmp_tmp - 1] = rtDW->kNext;
                      rtDW->kDrop = (int16_T)rtDW->lambda_tmp_tmp;
                      exitg4 = false;
                      while ((!exitg4) && (rtDW->kDrop > 1)) {
                        rtDW->i8 = rtDW->iC[rtDW->kDrop - 1];
                        tmp = rtDW->iC[rtDW->kDrop - 2];
                        if (rtDW->i8 > tmp) {
                          exitg4 = true;
                        } else {
                          rtDW->iC[rtDW->kDrop - 1] = tmp;
                          rtDW->iC[rtDW->kDrop - 2] = rtDW->i8;
                          rtDW->kDrop--;
                        }
                      }

                      iA[rtDW->kNext - 1] = 1;
                      rtDW->kNext = 0;
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                } else {
                  (*status)++;
                }
              }
            }
          } else {
            rtDW->cMin = norm(x_data, x_size, rtDW);
            if (fabsf(rtDW->cMin - rtDW->Xnorm0) > 0.001F) {
              rtDW->Xnorm0 = rtDW->cMin;
              maximum2(varargin_1, rtDW->cTol);
              cTolComputed = false;
            }

            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static int32_T cholesky(real32_T A_data[], int32_T A_size[2], DW *rtDW)
{
  int32_T b_iy;
  int32_T b_k;
  int32_T info;
  boolean_T exitg1;
  memcpy(&rtDW->b_A_data[0], &A_data[0], sizeof(real32_T) << 4U);
  info = 0;
  rtDW->jmax_o = 0;
  exitg1 = false;
  while ((!exitg1) && (rtDW->jmax_o < 4)) {
    rtDW->idxAjj_i = (rtDW->jmax_o << 2) + rtDW->jmax_o;
    rtDW->ssq = 0.0F;
    if (rtDW->jmax_o >= 1) {
      rtDW->b_ix_g = rtDW->jmax_o;
      b_iy = rtDW->jmax_o;
      for (b_k = 0; b_k < rtDW->jmax_o; b_k++) {
        rtDW->ssq += rtDW->b_A_data[rtDW->b_ix_g] * rtDW->b_A_data[b_iy];
        rtDW->b_ix_g += 4;
        b_iy += 4;
      }
    }

    rtDW->ssq = rtDW->b_A_data[rtDW->idxAjj_i] - rtDW->ssq;
    if (rtDW->ssq > 0.0F) {
      rtDW->ssq = sqrtf(rtDW->ssq);
      rtDW->b_A_data[rtDW->idxAjj_i] = rtDW->ssq;
      if (rtDW->jmax_o + 1 < 4) {
        if (rtDW->jmax_o != 0) {
          rtDW->b_ix_g = rtDW->jmax_o;
          b_iy = (((rtDW->jmax_o - 1) << 2) + rtDW->jmax_o) + 2;
          for (b_k = rtDW->jmax_o + 2; b_k <= b_iy; b_k += 4) {
            rtDW->b_c = -rtDW->b_A_data[rtDW->b_ix_g];
            rtDW->iy_f = rtDW->idxAjj_i + 1;
            rtDW->e_i = (b_k - rtDW->jmax_o) + 2;
            rtDW->ia_f = b_k;
            while (rtDW->ia_f <= rtDW->e_i) {
              rtDW->b_A_data[rtDW->iy_f] += rtDW->b_A_data[rtDW->ia_f - 1] *
                rtDW->b_c;
              rtDW->iy_f++;
              rtDW->ia_f++;
            }

            rtDW->b_ix_g += 4;
          }
        }

        rtDW->ssq = 1.0F / rtDW->ssq;
        rtDW->b_ix_g = (rtDW->idxAjj_i - rtDW->jmax_o) + 4;
        rtDW->idxAjj_i++;
        while (rtDW->idxAjj_i + 1 <= rtDW->b_ix_g) {
          rtDW->b_A_data[rtDW->idxAjj_i] *= rtDW->ssq;
          rtDW->idxAjj_i++;
        }
      }

      rtDW->jmax_o++;
    } else {
      rtDW->b_A_data[rtDW->idxAjj_i] = rtDW->ssq;
      info = rtDW->jmax_o + 1;
      exitg1 = true;
    }
  }

  A_size[0] = 4;
  A_size[1] = 4;
  for (rtDW->b_ix_g = 0; rtDW->b_ix_g < 4; rtDW->b_ix_g++) {
    rtDW->jmax_o = A_size[0] * rtDW->b_ix_g;
    A_data[rtDW->jmax_o] = rtDW->b_A_data[rtDW->b_ix_g << 2];
    A_data[1 + rtDW->jmax_o] = rtDW->b_A_data[1 + (rtDW->b_ix_g << 2)];
    A_data[2 + rtDW->jmax_o] = rtDW->b_A_data[2 + (rtDW->b_ix_g << 2)];
    A_data[3 + rtDW->jmax_o] = rtDW->b_A_data[3 + (rtDW->b_ix_g << 2)];
  }

  if (info == 0) {
    rtDW->jmax_o = 4;
  } else {
    rtDW->jmax_o = info - 1;
  }

  rtDW->idxAjj_i = 1;
  while (rtDW->idxAjj_i + 1 <= rtDW->jmax_o) {
    rtDW->b_ix_g = 0;
    while (rtDW->b_ix_g <= rtDW->idxAjj_i - 1) {
      A_data[rtDW->b_ix_g + A_size[0] * rtDW->idxAjj_i] = 0.0F;
      rtDW->b_ix_g++;
    }

    rtDW->idxAjj_i++;
  }

  if (1 > rtDW->jmax_o) {
    rtDW->b_ix_g = -1;
    rtDW->idxAjj_i = -1;
    b_k = -1;
  } else {
    rtDW->b_ix_g = rtDW->jmax_o - 1;
    rtDW->idxAjj_i = rtDW->jmax_o - 1;
    b_k = rtDW->jmax_o - 1;
  }

  b_iy = rtDW->idxAjj_i + 1;
  for (rtDW->idxAjj_i = 0; rtDW->idxAjj_i <= b_k; rtDW->idxAjj_i++) {
    for (rtDW->jmax_o = 0; rtDW->jmax_o < b_iy; rtDW->jmax_o++) {
      A_data[rtDW->jmax_o + (rtDW->b_ix_g + 1) * rtDW->idxAjj_i] = A_data
        [rtDW->jmax_o + A_size[0] * rtDW->idxAjj_i];
    }
  }

  A_size[0] = rtDW->b_ix_g + 1;
  A_size[1] = b_k + 1;
  return info;
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void linsolve(const real32_T A_data[], const int32_T A_size[2], const
                     real_T B_data[], const int32_T B_size[2], real32_T C_data[],
                     int32_T C_size[2], DW *rtDW)
{
  if (A_size[0] < A_size[1]) {
    rtDW->y = A_size[0];
  } else {
    rtDW->y = A_size[1];
  }

  C_size[0] = (int8_T)A_size[1];
  C_size[1] = (int8_T)B_size[1];
  rtDW->j_f = 0;
  while (rtDW->j_f <= B_size[1] - 1) {
    rtDW->i_p = 0;
    while (rtDW->i_p <= rtDW->y - 1) {
      C_data[rtDW->i_p + C_size[0] * rtDW->j_f] = (real32_T)B_data[rtDW->i_p +
        B_size[0] * rtDW->j_f];
      rtDW->i_p++;
    }

    rtDW->i_p = rtDW->y;
    while (rtDW->i_p + 1 <= A_size[1]) {
      C_data[rtDW->i_p + C_size[0] * rtDW->j_f] = 0.0F;
      rtDW->i_p++;
    }

    rtDW->j_f++;
  }

  trisolve(A_data, A_size, C_data, C_size, rtDW);
}

/* Function for MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' */
static void mpcActiveSetSolver(const real32_T H_data[], const int32_T H_size[2],
  const real32_T f[4], real32_T options_MaxIterations, real32_T x_data[],
  int32_T *x_size, real32_T *exitflag, DW *rtDW)
{
  rtDW->m = H_size[1];
  rtDW->Hinv_size_a[0] = H_size[1];
  rtDW->Hinv_size_a[1] = H_size[1];
  rtDW->j = 0;
  while (rtDW->j <= H_size[1] - 1) {
    rtDW->coffset = rtDW->j * rtDW->m;
    rtDW->boffset = rtDW->j * H_size[0];
    rtDW->i = 0;
    while (rtDW->i <= rtDW->m - 1) {
      rtDW->Hinv_data[rtDW->coffset + rtDW->i] = 0.0F;
      rtDW->i++;
    }

    rtDW->i = 0;
    while (rtDW->i <= H_size[0] - 1) {
      rtDW->bkj = H_data[rtDW->boffset + rtDW->i];
      rtDW->b_i = 0;
      while (rtDW->b_i <= rtDW->m - 1) {
        rtDW->i_n = rtDW->coffset + rtDW->b_i;
        rtDW->Hinv_data[rtDW->i_n] += H_data[rtDW->b_i * H_size[0] + rtDW->i] *
          rtDW->bkj;
        rtDW->b_i++;
      }

      rtDW->i++;
    }

    rtDW->j++;
  }

  rtDW->bkj = roundf(options_MaxIterations);
  if (rtDW->bkj < 32768.0F) {
    if (rtDW->bkj >= -32768.0F) {
      rtDW->i7 = (int16_T)rtDW->bkj;
    } else {
      rtDW->i7 = MIN_int16_T;
    }
  } else {
    rtDW->i7 = MAX_int16_T;
  }

  qpkwik(H_data, H_size, rtDW->Hinv_data, rtDW->Hinv_size_a, f, rtDW->i7,
         (int16_T)H_size[0], x_data, x_size, rtDW->lam_c, exitflag, rtDW->iA1_k,
         rtDW);
}

/* Model step function */
void impl_modul_mpc_all_and_deadbeat_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  int8_T rtAction;
  boolean_T rEQ0;
  static const int8_T a[12] = { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0 };

  static const int8_T seq_order_table[18] = { 1, 2, 3, 3, 2, 1, 2, 1, 1, 2, 3, 3,
    3, 3, 2, 1, 1, 2 };

  boolean_T exitg1;

  /* Trigonometry: '<S1>/SinCos1' incorporates:
   *  Inport: '<Root>/theta_el'
   */
  /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/seq_2_act_sw_all': '<S5>:1' */
  /* '<S5>:1:3' act_sw_1 = single(zeros(6,1)); */
  /* '<S5>:1:4' act_sw_2 = single(zeros(6,1)); */
  /*  columns=sequence, rows=active switch postion              */
  /* '<S5>:1:6' sequence_table = single([1 3;  */
  /* '<S5>:1:7'                   2 3; */
  /* '<S5>:1:8'                   2 6; */
  /* '<S5>:1:9'                   4 6; */
  /* '<S5>:1:10'                   4 5; */
  /* '<S5>:1:11'                   1 5]); */
  /* '<S5>:1:13' act_sw_1(1) = sequence_table(1,1); */
  /* '<S5>:1:14' act_sw_2(1) = sequence_table(1,2); */
  /* '<S5>:1:15' act_sw_1(2) = sequence_table(2,1); */
  /* '<S5>:1:16' act_sw_2(2) = sequence_table(2,2); */
  /* '<S5>:1:17' act_sw_1(3) = sequence_table(3,1); */
  /* '<S5>:1:18' act_sw_2(3) = sequence_table(3,2); */
  /* '<S5>:1:19' act_sw_1(4) = sequence_table(4,1); */
  /* '<S5>:1:20' act_sw_2(4) = sequence_table(4,2); */
  /* '<S5>:1:21' act_sw_1(5) = sequence_table(5,1); */
  /* '<S5>:1:22' act_sw_2(5) = sequence_table(5,2); */
  /* '<S5>:1:23' act_sw_1(6) = sequence_table(6,1); */
  /* '<S5>:1:24' act_sw_2(6) = sequence_table(6,2); */
  rtDW->SinCos1_o1 = sinf(rtU->theta_el);
  rtDW->SinCos1_o2 = cosf(rtU->theta_el);

  /* MATLAB Function: '<S1>/act_sw_2_dq_volts_all' incorporates:
   *  Inport: '<Root>/v_DC_pu'
   */
  /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/act_sw_2_dq_volts_all': '<S2>:1' */
  /* '<S2>:1:3' vd_1_pu = single(zeros(6,1)); */
  /* '<S2>:1:4' vd_2_pu = single(zeros(6,1)); */
  /* '<S2>:1:5' vq_1_pu = single(zeros(6,1)); */
  /* '<S2>:1:6' vq_2_pu = single(zeros(6,1)); */
  /*  voltage lookup factors alpha/beta */
  /* '<S2>:1:9' v_alpha_beta_pu = single([  0.666666666666667,0; */
  /* '<S2>:1:10'                     -0.333333333333334,0.577350269189626; */
  /* '<S2>:1:11'                      0.333333333333333,0.577350269189626; */
  /* '<S2>:1:12'                     -0.333333333333333,-0.577350269189626; */
  /* '<S2>:1:13'                      0.333333333333334,-0.577350269189626; */
  /* '<S2>:1:14'                     -0.666666666666667,0]); */
  /* '<S2>:1:16' vd_1_pu(1) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(1),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(1),2) * sin_angle); */
  rtDW->rtb_vd_1_pu_tmp_n = 0.666666687F * rtDW->SinCos1_o2 * rtU->v_DC_pu;

  /* '<S2>:1:17' vq_1_pu(1) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(1),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(1),2) * cos_angle); */
  rtDW->rtb_vq_1_pu_idx_0_tmp = 0.666666687F * -rtDW->SinCos1_o1 * rtU->v_DC_pu;

  /* '<S2>:1:19' vd_2_pu(1) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(1),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(1),2) * sin_angle); */
  rtDW->rtb_vd_2_pu_idx_0_tmp = (0.333333343F * rtDW->SinCos1_o2 + 0.577350259F *
    rtDW->SinCos1_o1) * rtU->v_DC_pu;

  /* '<S2>:1:20' vq_2_pu(1) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(1),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(1),2) * cos_angle); */
  rtDW->rtb_vq_2_pu_idx_0_tmp_tmp = 0.333333343F * -rtDW->SinCos1_o1;
  rtDW->rtb_vq_2_pu_idx_0_tmp = (rtDW->rtb_vq_2_pu_idx_0_tmp_tmp + 0.577350259F *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* '<S2>:1:23' vd_1_pu(2) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(2),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(2),2) * sin_angle); */
  rtDW->rtb_vd_1_pu_tmp = (-0.333333343F * rtDW->SinCos1_o2 + 0.577350259F *
    rtDW->SinCos1_o1) * rtU->v_DC_pu;

  /* '<S2>:1:24' vq_1_pu(2) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(2),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(2),2) * cos_angle); */
  rtDW->rtb_vq_1_pu_idx_1_tmp_tmp = -0.333333343F * -rtDW->SinCos1_o1;
  rtDW->rtb_vq_1_pu_idx_1_tmp = (rtDW->rtb_vq_1_pu_idx_1_tmp_tmp + 0.577350259F *
    rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* '<S2>:1:26' vd_2_pu(2) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(2),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(2),2) * sin_angle); */
  /* '<S2>:1:27' vq_2_pu(2) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(2),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(2),2) * cos_angle); */
  /* '<S2>:1:30' vd_1_pu(3) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(3),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(3),2) * sin_angle); */
  /* '<S2>:1:31' vq_1_pu(3) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(3),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(3),2) * cos_angle); */
  /* '<S2>:1:33' vd_2_pu(3) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(3),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(3),2) * sin_angle); */
  rtDW->rtb_vd_2_pu_idx_2_tmp = -0.666666687F * rtDW->SinCos1_o2 * rtU->v_DC_pu;

  /* '<S2>:1:34' vq_2_pu(3) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(3),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(3),2) * cos_angle); */
  rtDW->rtb_vq_2_pu_idx_2_tmp = -0.666666687F * -rtDW->SinCos1_o1 * rtU->v_DC_pu;

  /* '<S2>:1:37' vd_1_pu(4) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(4),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(4),2) * sin_angle); */
  rtDW->rtb_vd_1_pu_tmp_b = (-0.333333343F * rtDW->SinCos1_o2 + -0.577350259F *
    rtDW->SinCos1_o1) * rtU->v_DC_pu;

  /* '<S2>:1:38' vq_1_pu(4) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(4),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(4),2) * cos_angle); */
  rtDW->rtb_vq_1_pu_idx_1_tmp_tmp = (rtDW->rtb_vq_1_pu_idx_1_tmp_tmp +
    -0.577350259F * rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* '<S2>:1:40' vd_2_pu(4) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(4),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(4),2) * sin_angle); */
  /* '<S2>:1:41' vq_2_pu(4) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(4),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(4),2) * cos_angle); */
  /* '<S2>:1:44' vd_1_pu(5) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(5),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(5),2) * sin_angle); */
  /* '<S2>:1:45' vq_1_pu(5) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(5),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(5),2) * cos_angle); */
  /* '<S2>:1:47' vd_2_pu(5) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(5),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(5),2) * sin_angle); */
  rtDW->rtb_vd_2_pu_idx_4_tmp = (0.333333343F * rtDW->SinCos1_o2 + -0.577350259F
    * rtDW->SinCos1_o1) * rtU->v_DC_pu;

  /* '<S2>:1:48' vq_2_pu(5) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(5),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(5),2) * cos_angle); */
  rtDW->rtb_vq_2_pu_idx_0_tmp_tmp = (rtDW->rtb_vq_2_pu_idx_0_tmp_tmp +
    -0.577350259F * rtDW->SinCos1_o2) * rtU->v_DC_pu;

  /* If: '<S1>/if deadbeat true' incorporates:
   *  Inport: '<Root>/all_or_deadbeat'
   *  MATLAB Function: '<S4>/qp_solver_for_deadbeat'
   */
  /* '<S2>:1:51' vd_1_pu(6) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(6),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(6),2) * sin_angle); */
  /* '<S2>:1:52' vq_1_pu(6) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(6),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(6),2) * cos_angle); */
  /* '<S2>:1:54' vd_2_pu(6) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(6),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(6),2) * sin_angle); */
  /* '<S2>:1:55' vq_2_pu(6) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(6),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(6),2) * cos_angle); */
  rtAction = -1;
  if (rtU->all_or_deadbeat > 0.5F) {
    rtAction = 0;
  }

  rtDW->ifdeadbeattrue_ActiveSubsystem = rtAction;
  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S1>/deadbeat' incorporates:
     *  ActionPort: '<S4>/Action Port'
     */
    /* MATLAB Function: '<S4>/deadbeat_solution' incorporates:
     *  Inport: '<Root>/Ld_over_LB'
     *  Inport: '<Root>/Lq_over_LB'
     *  Inport: '<Root>/Rs_over_ZB'
     *  Inport: '<Root>/Ts_times_ZB_over_Ld'
     *  Inport: '<Root>/Ts_times_ZB_over_Lq'
     *  Inport: '<Root>/i_d_ref_pu'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_q_ref_pu'
     *  Inport: '<Root>/omega_el_pu'
     *  Inport: '<Root>/psi_pm_over_psiB'
     *  Inport: '<Root>/theta_el'
     */
    /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/deadbeat/deadbeat_solution': '<S28>:1' */
    /* '<S28>:1:4' v_d_ref_pu = (i_d_ref_pu-i_d_pu)/(Ts_times_ZB_over_Ld) + i_d_pu*Rs_over_ZB - omega_el*Lq_over_LB*i_q_pu; */
    /* '<S28>:1:5' v_q_ref_pu = (i_q_ref_pu-i_q_pu)/(Ts_times_ZB_over_Lq) + i_q_pu*Rs_over_ZB + omega_el*(Ld_over_LB*i_d_pu+psi_pm_over_psiB); */
    /* '<S28>:1:7' angle_ref = mod(atan2(v_q_ref_pu, v_d_ref_pu) + theta_el, 2*pi); */
    rtDW->SinCos1_o1 = atan2f(((rtU->i_q_ref_pu - rtU->i_dq_pu[1]) /
      rtU->Ts_times_ZB_over_Lq + rtU->i_dq_pu[1] * rtU->Rs_over_ZB) +
      (rtU->Ld_over_LB * rtU->i_dq_pu[0] + rtU->psi_pm_over_psiB) *
      rtU->omega_el_pu, ((rtU->i_d_ref_pu - rtU->i_dq_pu[0]) /
                         rtU->Ts_times_ZB_over_Ld + rtU->i_dq_pu[0] *
                         rtU->Rs_over_ZB) - rtU->omega_el_pu * rtU->Lq_over_LB *
      rtU->i_dq_pu[1]) + rtU->theta_el;
    if (rtDW->SinCos1_o1 == 0.0F) {
      rtDW->SinCos1_o2 = 0.0F;
    } else {
      rtDW->SinCos1_o2 = fmodf(rtDW->SinCos1_o1, 6.28318548F);
      rEQ0 = (rtDW->SinCos1_o2 == 0.0F);
      if (!rEQ0) {
        rtDW->q = fabsf(rtDW->SinCos1_o1 / 6.28318548F);
        rEQ0 = (fabsf(rtDW->q - floorf(rtDW->q + 0.5F)) <= 1.1920929E-7F *
                rtDW->q);
      }

      if (rEQ0) {
        rtDW->SinCos1_o2 = 0.0F;
      } else if (rtDW->SinCos1_o1 < 0.0F) {
        rtDW->SinCos1_o2 += 6.28318548F;
      }
    }

    /* '<S28>:1:9' sector_ref = 0.0; */
    rtDW->sector_ref = 0.0;

    /* '<S28>:1:10' if (angle_ref >= 0.0 && angle_ref < pi/180*60) */
    if ((rtDW->SinCos1_o2 >= 0.0F) && (rtDW->SinCos1_o2 < 1.0471975511965976)) {
      /* '<S28>:1:11' sector_ref = 1.0; */
      rtDW->sector_ref = 1.0;
    } else if ((rtDW->SinCos1_o2 >= 1.0471975511965976) && (rtDW->SinCos1_o2 <
                2.0943951023931953)) {
      /* '<S28>:1:12' elseif (angle_ref >= pi/180*60 && angle_ref < pi/180*120) */
      /* '<S28>:1:13' sector_ref = 2.0; */
      rtDW->sector_ref = 2.0;
    } else if ((rtDW->SinCos1_o2 >= 2.0943951023931953) && (rtDW->SinCos1_o2 <
                3.1415926535897931)) {
      /* '<S28>:1:14' elseif (angle_ref >= pi/180*120 && angle_ref < pi/180*180) */
      /* '<S28>:1:15' sector_ref = 3.0; */
      rtDW->sector_ref = 3.0;
    } else if ((rtDW->SinCos1_o2 >= 3.1415926535897931) && (rtDW->SinCos1_o2 <
                4.1887902047863905)) {
      /* '<S28>:1:16' elseif (angle_ref >= pi/180*180 && angle_ref < pi/180*240) */
      /* '<S28>:1:17' sector_ref = 4.0; */
      rtDW->sector_ref = 4.0;
    } else if ((rtDW->SinCos1_o2 >= 4.1887902047863905) && (rtDW->SinCos1_o2 <
                5.2359877559829888)) {
      /* '<S28>:1:18' elseif (angle_ref >= pi/180*240 && angle_ref < pi/180*300) */
      /* '<S28>:1:19' sector_ref = 5.0; */
      rtDW->sector_ref = 5.0;
    } else if ((rtDW->SinCos1_o2 >= 5.2359877559829888) && (rtDW->SinCos1_o2 <
                6.2831853071795862)) {
      /* '<S28>:1:20' elseif (angle_ref >= pi/180*300 && angle_ref < pi/180*360) */
      /* '<S28>:1:21' sector_ref = 6.0; */
      rtDW->sector_ref = 6.0;
    }

    /* End of MATLAB Function: '<S4>/deadbeat_solution' */

    /* MultiPortSwitch: '<S4>/Index Vector' incorporates:
     *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
     */
    switch ((int32_T)rtDW->sector_ref) {
     case 1:
      rtDW->IndexVector[0] = rtDW->rtb_vd_1_pu_tmp_n;
      rtDW->IndexVector[1] = rtDW->rtb_vq_1_pu_idx_0_tmp;
      rtDW->IndexVector[2] = rtDW->rtb_vd_2_pu_idx_0_tmp;
      rtDW->IndexVector[3] = rtDW->rtb_vq_2_pu_idx_0_tmp;
      break;

     case 2:
      rtDW->IndexVector[0] = rtDW->rtb_vd_1_pu_tmp;
      rtDW->IndexVector[1] = rtDW->rtb_vq_1_pu_idx_1_tmp;
      rtDW->IndexVector[2] = rtDW->rtb_vd_2_pu_idx_0_tmp;
      rtDW->IndexVector[3] = rtDW->rtb_vq_2_pu_idx_0_tmp;
      break;

     case 3:
      rtDW->IndexVector[0] = rtDW->rtb_vd_1_pu_tmp;
      rtDW->IndexVector[1] = rtDW->rtb_vq_1_pu_idx_1_tmp;
      rtDW->IndexVector[2] = rtDW->rtb_vd_2_pu_idx_2_tmp;
      rtDW->IndexVector[3] = rtDW->rtb_vq_2_pu_idx_2_tmp;
      break;

     case 4:
      rtDW->IndexVector[0] = rtDW->rtb_vd_1_pu_tmp_b;
      rtDW->IndexVector[1] = rtDW->rtb_vq_1_pu_idx_1_tmp_tmp;
      rtDW->IndexVector[2] = rtDW->rtb_vd_2_pu_idx_2_tmp;
      rtDW->IndexVector[3] = rtDW->rtb_vq_2_pu_idx_2_tmp;
      break;

     case 5:
      rtDW->IndexVector[0] = rtDW->rtb_vd_1_pu_tmp_b;
      rtDW->IndexVector[1] = rtDW->rtb_vq_1_pu_idx_1_tmp_tmp;
      rtDW->IndexVector[2] = rtDW->rtb_vd_2_pu_idx_4_tmp;
      rtDW->IndexVector[3] = rtDW->rtb_vq_2_pu_idx_0_tmp_tmp;
      break;

     default:
      rtDW->IndexVector[0] = rtDW->rtb_vd_1_pu_tmp_n;
      rtDW->IndexVector[1] = rtDW->rtb_vq_1_pu_idx_0_tmp;
      rtDW->IndexVector[2] = rtDW->rtb_vd_2_pu_idx_4_tmp;
      rtDW->IndexVector[3] = rtDW->rtb_vq_2_pu_idx_0_tmp_tmp;
      break;
    }

    /* End of MultiPortSwitch: '<S4>/Index Vector' */

    /* MATLAB Function: '<S4>/state_space_mdl_deadbeat' incorporates:
     *  Inport: '<Root>/Ld_over_LB'
     *  Inport: '<Root>/Lq_over_LB'
     *  Inport: '<Root>/Rs_over_ZB'
     *  Inport: '<Root>/Ts_times_ZB_over_Ld'
     *  Inport: '<Root>/Ts_times_ZB_over_Lq'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/omega_el_pu'
     *  Inport: '<Root>/psi_pm_over_psiB'
     */
    state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                      rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                      rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                      rtU->omega_el_pu, rtDW->IndexVector[0], rtDW->IndexVector
                      [1], rtDW->IndexVector[2], rtDW->IndexVector[3], rtDW->m0,
                      rtDW->m1, rtDW->m2, rtDW->m3,
                      &rtDW->sf_state_space_mdl_deadbeat);

    /* MATLAB Function: '<S4>/formulate_qp_deadbeat' incorporates:
     *  Inport: '<Root>/i_d_ref_pu'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_q_ref_pu'
     *  Inport: '<Root>/lambda'
     */
    formulate_qp_1(rtDW->m0, rtDW->m1, rtDW->m2, rtDW->m3, rtU->i_dq_pu[0],
                   rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu,
                   rtU->lambda, rtDW->H, rtDW->IndexVector, rtDW->M, rtDW->r,
                   &rtDW->sf_formulate_qp_deadbeat);

    /* MATLAB Function: '<S4>/qp_solver_for_deadbeat' */
    /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/deadbeat/qp_solver_for_deadbeat': '<S30>:1' */
    /* '<S30>:1:3' x1 = single([0.5 0 0 0.5]'); */
    /* '<S30>:1:5' iter1 = single(0); */
    /*  contraints */
    /*             t1 t2 t3 t4 */
    /* '<S30>:1:9' A = single([-1  0  0  0 ;   % t>=0 is converted to -1<=0 */
    /* '<S30>:1:10'              0 -1  0  0 ;   % no row=no of ineq constraints */
    /* '<S30>:1:11'              0  0 -1  0 ;   % no columns=no of optimization variables */
    /* '<S30>:1:12'              0  0  0 -1]); */
    /*  t>=0 is converted to -1<=0 */
    /*  no row=no of ineq constraints */
    /*  no columns=no of optimization variables */
    /* '<S30>:1:14' b = single(zeros(4,1)); */
    /* '<S30>:1:16' Aeq = single([1 1 1 1]); */
    /* '<S30>:1:17' beq =  single([1]); */
    /*  sum of all duration times  */
    /*  define cold start for active-set solver */
    /* '<S30>:1:20' iA0 = false(size(b)); */
    /* '<S30>:1:22' [x1,iter1] = mpc_solve(H1,f1,A,b,Aeq,beq,iA0,max_iter,tol); */
    /* '<S30>:1:27' x = single([0 0 0 0]'); */
    /* '<S30>:1:28' iter = single(0); */
    /*  set up solver */
    /* '<S30>:1:30' options = mpcActiveSetOptions('single'); */
    /* '<S30>:1:31' options.MaxIterations = max_iter; */
    /* '<S30>:1:32' options.ConstriantTolerance = tol; */
    /* '<S30>:1:33' options.UseHessianAsInput = false; */
    /* '<S30>:1:34' options.IntegrityChecks = false; */
    /* '<S30>:1:37' x_tmp = single([0.5 0 0 0.5]'); */
    /* '<S30>:1:38' exitflag = single(0); */
    /*  calculate inverse of H */
    /* '<S30>:1:40' [L,~] = chol(H,'lower'); */
    rtDW->b_d = 0;
    rtDW->jmax = 0;
    exitg1 = false;
    while ((!exitg1) && (rtDW->jmax < 4)) {
      rtDW->idxAjj = (rtDW->jmax << 2) + rtDW->jmax;
      rtDW->SinCos1_o1 = 0.0F;
      if (rtDW->jmax >= 1) {
        rtDW->b_ix = rtDW->jmax;
        rtDW->b_iy = rtDW->jmax;
        rtDW->d = 0;
        while (rtDW->d <= rtDW->jmax - 1) {
          rtDW->SinCos1_o1 += rtDW->H[rtDW->b_ix] * rtDW->H[rtDW->b_iy];
          rtDW->b_ix += 4;
          rtDW->b_iy += 4;
          rtDW->d++;
        }
      }

      rtDW->SinCos1_o1 = rtDW->H[rtDW->idxAjj] - rtDW->SinCos1_o1;
      if (rtDW->SinCos1_o1 > 0.0F) {
        rtDW->SinCos1_o1 = sqrtf(rtDW->SinCos1_o1);
        rtDW->H[rtDW->idxAjj] = rtDW->SinCos1_o1;
        if (rtDW->jmax + 1 < 4) {
          if (rtDW->jmax != 0) {
            rtDW->b_ix = rtDW->jmax;
            rtDW->d = (((rtDW->jmax - 1) << 2) + rtDW->jmax) + 2;
            rtDW->b_iy = rtDW->jmax + 2;
            while (rtDW->b_iy <= rtDW->d) {
              rtDW->SinCos1_o2 = -rtDW->H[rtDW->b_ix];
              rtDW->iy = rtDW->idxAjj + 1;
              rtDW->e = (rtDW->b_iy - rtDW->jmax) + 2;
              rtDW->ia = rtDW->b_iy;
              while (rtDW->ia <= rtDW->e) {
                rtDW->H[rtDW->iy] += rtDW->H[rtDW->ia - 1] * rtDW->SinCos1_o2;
                rtDW->iy++;
                rtDW->ia++;
              }

              rtDW->b_ix += 4;
              rtDW->b_iy += 4;
            }
          }

          rtDW->SinCos1_o1 = 1.0F / rtDW->SinCos1_o1;
          rtDW->d = (rtDW->idxAjj - rtDW->jmax) + 4;
          rtDW->idxAjj++;
          while (rtDW->idxAjj + 1 <= rtDW->d) {
            rtDW->H[rtDW->idxAjj] *= rtDW->SinCos1_o1;
            rtDW->idxAjj++;
          }
        }

        rtDW->jmax++;
      } else {
        rtDW->H[rtDW->idxAjj] = rtDW->SinCos1_o1;
        rtDW->b_d = rtDW->jmax + 1;
        exitg1 = true;
      }
    }

    if (rtDW->b_d == 0) {
      rtDW->jmax = 4;
    } else {
      rtDW->jmax = rtDW->b_d - 1;
    }

    rtDW->idxAjj = 1;
    while (rtDW->idxAjj + 1 <= rtDW->jmax) {
      rtDW->b_d = 0;
      while (rtDW->b_d <= rtDW->idxAjj - 1) {
        rtDW->H[rtDW->b_d + (rtDW->idxAjj << 2)] = 0.0F;
        rtDW->b_d++;
      }

      rtDW->idxAjj++;
    }

    if (1 > rtDW->jmax) {
      rtDW->iy = -1;
      rtDW->idxAjj = -1;
      rtDW->d = -1;
    } else {
      rtDW->iy = rtDW->jmax - 1;
      rtDW->idxAjj = rtDW->jmax - 1;
      rtDW->d = rtDW->jmax - 1;
    }

    rtDW->b_ix = rtDW->idxAjj + 1;
    for (rtDW->jmax = 0; rtDW->jmax <= rtDW->d; rtDW->jmax++) {
      for (rtDW->b_d = 0; rtDW->b_d < rtDW->b_ix; rtDW->b_d++) {
        rtDW->H[rtDW->b_d + (rtDW->iy + 1) * rtDW->jmax] = rtDW->H[rtDW->b_d +
          (rtDW->jmax << 2)];
      }
    }

    rtDW->Hinv_size[0] = rtDW->iy + 1;
    rtDW->Hinv_size[1] = rtDW->d + 1;

    /* '<S30>:1:41' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
    if ((int8_T)(rtDW->idxAjj + 1) < (int8_T)(rtDW->d + 1)) {
      rtDW->b_d = (int8_T)(rtDW->idxAjj + 1);
    } else {
      rtDW->b_d = (int8_T)(rtDW->d + 1);
    }

    rtDW->b_iy = (int8_T)(rtDW->iy + 1);
    rtDW->b_ix = (int8_T)(rtDW->iy + 1) * (int8_T)(rtDW->d + 1) - 1;
    if (0 <= rtDW->b_ix) {
      memset(&rtDW->b_I_data_p[0], 0, (rtDW->b_ix + 1) * sizeof(int8_T));
    }

    /* MATLAB Function: '<S4>/qp_solver_for_deadbeat' incorporates:
     *  Inport: '<Root>/max_iter'
     */
    if (rtDW->b_d > 0) {
      rtDW->jmax = 0;
      while (rtDW->jmax <= rtDW->b_d - 1) {
        rtDW->b_I_data_p[rtDW->jmax + (int8_T)(rtDW->iy + 1) * rtDW->jmax] = 1;
        rtDW->jmax++;
      }
    }

    if (rtDW->iy + 1 < rtDW->d + 1) {
      rtDW->iy++;
    } else {
      rtDW->iy = rtDW->d + 1;
    }

    rtDW->Linv_size[0] = (int8_T)(rtDW->d + 1);
    rtDW->Linv_size[1] = (int8_T)(rtDW->d + 1);
    rtDW->jmax = 0;
    while (rtDW->jmax <= (int8_T)(rtDW->d + 1) - 1) {
      rtDW->idxAjj = 0;
      while (rtDW->idxAjj <= rtDW->iy - 1) {
        rtDW->Linv_data[rtDW->idxAjj + (int8_T)(rtDW->d + 1) * rtDW->jmax] =
          rtDW->b_I_data_p[rtDW->idxAjj + rtDW->b_iy * rtDW->jmax];
        rtDW->idxAjj++;
      }

      rtDW->idxAjj = rtDW->iy;
      while (rtDW->idxAjj + 1 <= rtDW->d + 1) {
        rtDW->Linv_data[rtDW->idxAjj + (int8_T)(rtDW->d + 1) * rtDW->jmax] =
          0.0F;
        rtDW->idxAjj++;
      }

      rtDW->jmax++;
    }

    trisolve(rtDW->H, rtDW->Hinv_size, rtDW->Linv_data, rtDW->Linv_size, rtDW);

    /*  solve QP */
    /* '<S30>:1:43' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
    rtDW->b_d = rtDW->Linv_size[1];
    rtDW->Hinv_size[0] = rtDW->Linv_size[1];
    rtDW->Hinv_size[1] = rtDW->Linv_size[1];
    rtDW->jmax = 0;
    while (rtDW->jmax <= rtDW->Linv_size[1] - 1) {
      rtDW->d = rtDW->jmax * rtDW->b_d;
      rtDW->b_ix = rtDW->jmax * rtDW->Linv_size[0];
      rtDW->idxAjj = 0;
      while (rtDW->idxAjj <= rtDW->b_d - 1) {
        rtDW->H[rtDW->d + rtDW->idxAjj] = 0.0F;
        rtDW->idxAjj++;
      }

      rtDW->idxAjj = 0;
      while (rtDW->idxAjj <= rtDW->Linv_size[0] - 1) {
        rtDW->SinCos1_o1 = rtDW->Linv_data[rtDW->b_ix + rtDW->idxAjj];
        rtDW->b_iy = 0;
        while (rtDW->b_iy <= rtDW->b_d - 1) {
          rtDW->iy = rtDW->d + rtDW->b_iy;
          rtDW->H[rtDW->iy] += rtDW->Linv_data[rtDW->b_iy * rtDW->Linv_size[0] +
            rtDW->idxAjj] * rtDW->SinCos1_o1;
          rtDW->b_iy++;
        }

        rtDW->idxAjj++;
      }

      rtDW->jmax++;
    }

    rtDW->rtb_IndexVector_c[0] = -rtDW->IndexVector[0];
    rtDW->rtb_IndexVector_c[1] = -rtDW->IndexVector[1];
    rtDW->rtb_IndexVector_c[2] = -rtDW->IndexVector[2];
    rtDW->rtb_IndexVector_c[3] = -rtDW->IndexVector[3];
    rtDW->SinCos1_o2 = roundf(rtU->max_iter);
    if (rtDW->SinCos1_o2 < 32768.0F) {
      if (rtDW->SinCos1_o2 >= -32768.0F) {
        rtDW->i6 = (int16_T)rtDW->SinCos1_o2;
      } else {
        rtDW->i6 = MIN_int16_T;
      }
    } else {
      rtDW->i6 = MAX_int16_T;
    }

    /* Outport: '<Root>/iterations_deadbeat' incorporates:
     *  MATLAB Function: '<S4>/qp_solver_for_deadbeat'
     */
    qpkwik(rtDW->Linv_data, rtDW->Linv_size, rtDW->H, rtDW->Hinv_size,
           rtDW->rtb_IndexVector_c, rtDW->i6, (int16_T)rtDW->Linv_size[0],
           rtDW->x_data, &rtDW->x_size, rtDW->lam, &rtY->iterations_deadbeat,
           rtDW->iA1, rtDW);

    /* MATLAB Function: '<S4>/qp_solver_for_deadbeat' */
    /* '<S30>:1:44' x = single(x_tmp(1:4,1)); */
    /* '<S30>:1:45' iter = single(exitflag); */
    /*  J1 = x1'*(M1'*M1)*x1-2*r1'*M1*x1; */
    rtDW->x1[0] = rtDW->x_data[0];
    rtDW->x1[1] = rtDW->x_data[1];
    rtDW->x1[2] = rtDW->x_data[2];
    rtDW->x1[3] = rtDW->x_data[3];

    /* Update for Delay: '<S4>/Delay2' */
    rtDW->icLoad = false;

    /* End of Outputs for SubSystem: '<S1>/deadbeat' */
  }

  /* End of If: '<S1>/if deadbeat true' */

  /* If: '<S1>/if all true' incorporates:
   *  Inport: '<Root>/all_or_deadbeat'
   */
  rtAction = -1;
  if (rtU->all_or_deadbeat < 0.5F) {
    rtAction = 0;
  }

  rtDW->ifalltrue_ActiveSubsystem = rtAction;
  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S1>/all' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    /* MATLAB Function: '<S3>/state_space_mdl_1' incorporates:
     *  Inport: '<Root>/Ld_over_LB'
     *  Inport: '<Root>/Lq_over_LB'
     *  Inport: '<Root>/Rs_over_ZB'
     *  Inport: '<Root>/Ts_times_ZB_over_Ld'
     *  Inport: '<Root>/Ts_times_ZB_over_Lq'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/omega_el_pu'
     *  Inport: '<Root>/psi_pm_over_psiB'
     *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
     */
    state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                      rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                      rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                      rtU->omega_el_pu, rtDW->rtb_vd_1_pu_tmp_n,
                      rtDW->rtb_vq_1_pu_idx_0_tmp, rtDW->rtb_vd_2_pu_idx_0_tmp,
                      rtDW->rtb_vq_2_pu_idx_0_tmp, rtDW->m0, rtDW->m1, rtDW->m2,
                      rtDW->m3, &rtDW->sf_state_space_mdl_1);

    /* MATLAB Function: '<S3>/formulate_qp_1' incorporates:
     *  Inport: '<Root>/i_d_ref_pu'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_q_ref_pu'
     *  Inport: '<Root>/lambda'
     */
    formulate_qp_1(rtDW->m0, rtDW->m1, rtDW->m2, rtDW->m3, rtU->i_dq_pu[0],
                   rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu,
                   rtU->lambda, rtDW->H, rtDW->IndexVector, rtDW->M, rtDW->r,
                   &rtDW->sf_formulate_qp_1);

    /* MATLAB Function: '<S3>/state_space_mdl_2' incorporates:
     *  Inport: '<Root>/Ld_over_LB'
     *  Inport: '<Root>/Lq_over_LB'
     *  Inport: '<Root>/Rs_over_ZB'
     *  Inport: '<Root>/Ts_times_ZB_over_Ld'
     *  Inport: '<Root>/Ts_times_ZB_over_Lq'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/omega_el_pu'
     *  Inport: '<Root>/psi_pm_over_psiB'
     *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
     */
    state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                      rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                      rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                      rtU->omega_el_pu, rtDW->rtb_vd_1_pu_tmp,
                      rtDW->rtb_vq_1_pu_idx_1_tmp, rtDW->rtb_vd_2_pu_idx_0_tmp,
                      rtDW->rtb_vq_2_pu_idx_0_tmp, rtDW->m0, rtDW->m1, rtDW->m2,
                      rtDW->m3, &rtDW->sf_state_space_mdl_2);

    /* MATLAB Function: '<S3>/formulate_qp_2' incorporates:
     *  Inport: '<Root>/i_d_ref_pu'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_q_ref_pu'
     *  Inport: '<Root>/lambda'
     */
    formulate_qp_1(rtDW->m0, rtDW->m1, rtDW->m2, rtDW->m3, rtU->i_dq_pu[0],
                   rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu,
                   rtU->lambda, rtDW->H_l, rtDW->f_gy, rtDW->M_h, rtDW->r_ff,
                   &rtDW->sf_formulate_qp_2);

    /* MATLAB Function: '<S3>/state_space_mdl_3' incorporates:
     *  Inport: '<Root>/Ld_over_LB'
     *  Inport: '<Root>/Lq_over_LB'
     *  Inport: '<Root>/Rs_over_ZB'
     *  Inport: '<Root>/Ts_times_ZB_over_Ld'
     *  Inport: '<Root>/Ts_times_ZB_over_Lq'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/omega_el_pu'
     *  Inport: '<Root>/psi_pm_over_psiB'
     *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
     */
    state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                      rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                      rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                      rtU->omega_el_pu, rtDW->rtb_vd_1_pu_tmp,
                      rtDW->rtb_vq_1_pu_idx_1_tmp, rtDW->rtb_vd_2_pu_idx_2_tmp,
                      rtDW->rtb_vq_2_pu_idx_2_tmp, rtDW->m0, rtDW->m1, rtDW->m2,
                      rtDW->m3, &rtDW->sf_state_space_mdl_3);

    /* MATLAB Function: '<S3>/formulate_qp_3' incorporates:
     *  Inport: '<Root>/i_d_ref_pu'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_q_ref_pu'
     *  Inport: '<Root>/lambda'
     */
    formulate_qp_1(rtDW->m0, rtDW->m1, rtDW->m2, rtDW->m3, rtU->i_dq_pu[0],
                   rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu,
                   rtU->lambda, rtDW->H_p, rtDW->f_h, rtDW->M_l, rtDW->r_b,
                   &rtDW->sf_formulate_qp_3);

    /* MATLAB Function: '<S3>/state_space_mdl_4' incorporates:
     *  Inport: '<Root>/Ld_over_LB'
     *  Inport: '<Root>/Lq_over_LB'
     *  Inport: '<Root>/Rs_over_ZB'
     *  Inport: '<Root>/Ts_times_ZB_over_Ld'
     *  Inport: '<Root>/Ts_times_ZB_over_Lq'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/omega_el_pu'
     *  Inport: '<Root>/psi_pm_over_psiB'
     *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
     */
    state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                      rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                      rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                      rtU->omega_el_pu, rtDW->rtb_vd_1_pu_tmp_b,
                      rtDW->rtb_vq_1_pu_idx_1_tmp_tmp,
                      rtDW->rtb_vd_2_pu_idx_2_tmp, rtDW->rtb_vq_2_pu_idx_2_tmp,
                      rtDW->m0, rtDW->m1, rtDW->m2, rtDW->m3,
                      &rtDW->sf_state_space_mdl_4);

    /* MATLAB Function: '<S3>/formulate_qp_4' incorporates:
     *  Inport: '<Root>/i_d_ref_pu'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_q_ref_pu'
     *  Inport: '<Root>/lambda'
     */
    formulate_qp_1(rtDW->m0, rtDW->m1, rtDW->m2, rtDW->m3, rtU->i_dq_pu[0],
                   rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu,
                   rtU->lambda, rtDW->H_m, rtDW->f_f, rtDW->M_ny, rtDW->r_j,
                   &rtDW->sf_formulate_qp_4);

    /* MATLAB Function: '<S3>/state_space_mdl_5' incorporates:
     *  Inport: '<Root>/Ld_over_LB'
     *  Inport: '<Root>/Lq_over_LB'
     *  Inport: '<Root>/Rs_over_ZB'
     *  Inport: '<Root>/Ts_times_ZB_over_Ld'
     *  Inport: '<Root>/Ts_times_ZB_over_Lq'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/omega_el_pu'
     *  Inport: '<Root>/psi_pm_over_psiB'
     *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
     */
    state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                      rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                      rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                      rtU->omega_el_pu, rtDW->rtb_vd_1_pu_tmp_b,
                      rtDW->rtb_vq_1_pu_idx_1_tmp_tmp,
                      rtDW->rtb_vd_2_pu_idx_4_tmp,
                      rtDW->rtb_vq_2_pu_idx_0_tmp_tmp, rtDW->m0, rtDW->m1,
                      rtDW->m2, rtDW->m3, &rtDW->sf_state_space_mdl_5);

    /* MATLAB Function: '<S3>/formulate_qp_5' incorporates:
     *  Inport: '<Root>/i_d_ref_pu'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_q_ref_pu'
     *  Inport: '<Root>/lambda'
     */
    formulate_qp_1(rtDW->m0, rtDW->m1, rtDW->m2, rtDW->m3, rtU->i_dq_pu[0],
                   rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu,
                   rtU->lambda, rtDW->H_n, rtDW->f_g, rtDW->M_o, rtDW->r_g,
                   &rtDW->sf_formulate_qp_5);

    /* MATLAB Function: '<S3>/state_space_mdl_6' incorporates:
     *  Inport: '<Root>/Ld_over_LB'
     *  Inport: '<Root>/Lq_over_LB'
     *  Inport: '<Root>/Rs_over_ZB'
     *  Inport: '<Root>/Ts_times_ZB_over_Ld'
     *  Inport: '<Root>/Ts_times_ZB_over_Lq'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/omega_el_pu'
     *  Inport: '<Root>/psi_pm_over_psiB'
     */
    state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                      rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                      rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                      rtU->omega_el_pu, rtDW->rtb_vd_1_pu_tmp_n,
                      rtDW->rtb_vq_1_pu_idx_0_tmp, rtDW->rtb_vd_2_pu_idx_4_tmp,
                      rtDW->rtb_vq_2_pu_idx_0_tmp_tmp, rtDW->m3, rtDW->m2,
                      rtDW->m1, rtDW->m0, &rtDW->sf_state_space_mdl_6);

    /* MATLAB Function: '<S3>/formulate_qp_6' incorporates:
     *  Inport: '<Root>/i_d_ref_pu'
     *  Inport: '<Root>/i_dq_pu'
     *  Inport: '<Root>/i_q_ref_pu'
     *  Inport: '<Root>/lambda'
     */
    formulate_qp_1(rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0, rtU->i_dq_pu[0],
                   rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu,
                   rtU->lambda, rtDW->H_c, rtDW->f_m, rtDW->M_n, rtDW->r_f,
                   &rtDW->sf_formulate_qp_6);

    /* MATLAB Function: '<S3>/detect_unsuited_sequence_1' */
    detect_unsuited_sequence_1(rtDW->H, rtDW->IndexVector, &rtDW->unsuited_h);

    /* MATLAB Function: '<S3>/detect_unsuited_sequence_2' */
    detect_unsuited_sequence_1(rtDW->H_l, rtDW->f_gy, &rtDW->unsuited_k);

    /* MATLAB Function: '<S3>/detect_unsuited_sequence_3' */
    detect_unsuited_sequence_1(rtDW->H_p, rtDW->f_h, &rtDW->unsuited_f);

    /* MATLAB Function: '<S3>/detect_unsuited_sequence_4' */
    detect_unsuited_sequence_1(rtDW->H_m, rtDW->f_f, &rtDW->unsuited_i);

    /* MATLAB Function: '<S3>/detect_unsuited_sequence_5' */
    detect_unsuited_sequence_1(rtDW->H_n, rtDW->f_g, &rtDW->unsuited_j);

    /* MATLAB Function: '<S3>/detect_unsuited_sequence_6' */
    detect_unsuited_sequence_1(rtDW->H_c, rtDW->f_m, &rtDW->unsuited);

    /* MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS' incorporates:
     *  Inport: '<Root>/max_iter'
     *  SignalConversion generated from: '<S21>/ SFunction '
     */
    /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/all/qp_solver_for_suited_seq_AS': '<S21>:1' */
    /* '<S21>:1:3' x1 = single([0.5 0 0 0.5]'); */
    /* '<S21>:1:4' x2 = x1; */
    /* '<S21>:1:5' x3 = x2; */
    /* '<S21>:1:6' x4 = x3; */
    /* '<S21>:1:7' x5 = x4; */
    /* '<S21>:1:8' x6 = x5; */
    rtDW->x1_k[0] = 0.5F;
    rtDW->x2[0] = 0.5F;
    rtDW->x3[0] = 0.5F;
    rtDW->x4[0] = 0.5F;
    rtDW->x5[0] = 0.5F;
    rtDW->x6[0] = 0.5F;
    rtDW->x1_k[1] = 0.0F;
    rtDW->x2[1] = 0.0F;
    rtDW->x3[1] = 0.0F;
    rtDW->x4[1] = 0.0F;
    rtDW->x5[1] = 0.0F;
    rtDW->x6[1] = 0.0F;
    rtDW->x1_k[2] = 0.0F;
    rtDW->x2[2] = 0.0F;
    rtDW->x3[2] = 0.0F;
    rtDW->x4[2] = 0.0F;
    rtDW->x5[2] = 0.0F;
    rtDW->x6[2] = 0.0F;
    rtDW->x1_k[3] = 0.5F;
    rtDW->x2[3] = 0.5F;
    rtDW->x3[3] = 0.5F;
    rtDW->x4[3] = 0.5F;
    rtDW->x5[3] = 0.5F;
    rtDW->x6[3] = 0.5F;

    /* '<S21>:1:10' J1 = single(42); */
    rtDW->SinCos1_o1 = 42.0F;

    /* '<S21>:1:11' J2 = J1; */
    rtDW->vd_1_pu[1] = 42.0F;

    /* '<S21>:1:12' J3 = J2; */
    rtDW->vd_1_pu[2] = 42.0F;

    /* '<S21>:1:13' J4 = J3; */
    rtDW->vd_1_pu[3] = 42.0F;

    /* '<S21>:1:14' J5 = J4; */
    rtDW->vd_1_pu[4] = 42.0F;

    /* '<S21>:1:15' J6 = J5; */
    rtDW->vd_1_pu[5] = 42.0F;

    /* '<S21>:1:17' iter1 = single(0); */
    rtDW->iter1_o = 0.0F;

    /* '<S21>:1:18' iter2 = iter1; */
    rtDW->iter2 = 0.0F;

    /* '<S21>:1:19' iter3 = iter2; */
    rtDW->iter3 = 0.0F;

    /* '<S21>:1:20' iter4 = iter3; */
    rtDW->iter4 = 0.0F;

    /* '<S21>:1:21' iter5 = iter4; */
    rtDW->iter5 = 0.0F;

    /* '<S21>:1:22' iter6 = iter5; */
    rtDW->iter6 = 0.0F;

    /*  contraints */
    /*             t1 t2 t3 t4 */
    /* '<S21>:1:26' A = single([-1  0  0  0 ;   % t>=0 is converted to -1<=0 */
    /* '<S21>:1:27'              0 -1  0  0 ;   % no row=no of ineq constraints */
    /* '<S21>:1:28'              0  0 -1  0 ;   % no columns=no of optimization variables */
    /* '<S21>:1:29'              0  0  0 -1]); */
    /*  t>=0 is converted to -1<=0 */
    /*  no row=no of ineq constraints */
    /*  no columns=no of optimization variables */
    /* '<S21>:1:31' b = single(zeros(4,1)); */
    /* '<S21>:1:33' Aeq = single([1 1 1 1]); */
    /* '<S21>:1:34' beq =  single([1]); */
    /*  sum of all duration times  */
    /*  define cold start for active-set solver */
    /* '<S21>:1:37' iA0 = false(size(b)); */
    /*  if (sum_of_unsuited == 4 || sum_of_unsuited == 5) */
    /* '<S21>:1:41' if (unsuited(1) == false) */
    if (!rtDW->unsuited_h) {
      /* '<S21>:1:42' [x1,iter1] = mpc_solve(H1,f1,A,b,Aeq,beq,iA0,max_iter,tol); */
      /* '<S21>:1:70' x = single([0 0 0 0]'); */
      /* '<S21>:1:71' iter = single(0); */
      /*  set up solver */
      /* '<S21>:1:73' options = mpcActiveSetOptions('single'); */
      /* '<S21>:1:74' options.MaxIterations = max_iter; */
      /* '<S21>:1:75' options.ConstriantTolerance = tol; */
      /* '<S21>:1:76' options.UseHessianAsInput = false; */
      /* '<S21>:1:77' options.IntegrityChecks = false; */
      /* '<S21>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
      /* '<S21>:1:81' exitflag = single(0); */
      /*  calculate inverse of H */
      /* '<S21>:1:83' [L,~] = chol(H,'lower'); */
      rtDW->Hinv_size[0] = 4;
      rtDW->Hinv_size[1] = 4;
      cholesky(rtDW->H, rtDW->Hinv_size, rtDW);

      /* '<S21>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
      if ((int8_T)rtDW->Hinv_size[0] < (int8_T)rtDW->Hinv_size[1]) {
        rtDW->d = (int8_T)rtDW->Hinv_size[0];
      } else {
        rtDW->d = (int8_T)rtDW->Hinv_size[1];
      }

      rtDW->b_I_size[0] = (int8_T)rtDW->Hinv_size[0];
      rtDW->b_I_size[1] = (int8_T)rtDW->Hinv_size[1];
      rtDW->b_ix = (int8_T)rtDW->Hinv_size[0] * (int8_T)rtDW->Hinv_size[1] - 1;
      if (0 <= rtDW->b_ix) {
        memset(&rtDW->b_I_data[0], 0, (rtDW->b_ix + 1) * sizeof(real_T));
      }

      if (rtDW->d > 0) {
        rtDW->idxAjj = 0;
        while (rtDW->idxAjj <= rtDW->d - 1) {
          rtDW->b_I_data[rtDW->idxAjj + rtDW->b_I_size[0] * rtDW->idxAjj] = 1.0;
          rtDW->idxAjj++;
        }
      }

      linsolve(rtDW->H, rtDW->Hinv_size, rtDW->b_I_data, rtDW->b_I_size,
               rtDW->Linv_data, rtDW->Linv_size, rtDW);

      /*  solve QP */
      /* '<S21>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
      rtDW->rtb_IndexVector_c[0] = -rtDW->IndexVector[0];
      rtDW->rtb_IndexVector_c[1] = -rtDW->IndexVector[1];
      rtDW->rtb_IndexVector_c[2] = -rtDW->IndexVector[2];
      rtDW->rtb_IndexVector_c[3] = -rtDW->IndexVector[3];
      mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size,
                         rtDW->rtb_IndexVector_c, rtU->max_iter, rtDW->x_data,
                         &rtDW->x_size, &rtDW->iter1_o, rtDW);

      /* '<S21>:1:87' x = single(x_tmp(1:4,1)); */
      /* '<S21>:1:88' iter = single(exitflag); */
      /* '<S21>:1:43' J1 = x1'*(M1'*M1)*x1-2*r1'*M1*x1; */
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->x1_k[rtDW->iy] = rtDW->x_data[rtDW->iy];
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 4; rtDW->idxAjj++) {
          rtDW->b_d = rtDW->iy + (rtDW->idxAjj << 2);
          rtDW->H[rtDW->b_d] = 0.0F;
          for (rtDW->jmax = 0; rtDW->jmax < 8; rtDW->jmax++) {
            rtDW->H[rtDW->b_d] += rtDW->M[(rtDW->iy << 3) + rtDW->jmax] *
              rtDW->M[(rtDW->idxAjj << 3) + rtDW->jmax];
          }
        }
      }

      rtDW->rtb_vd_1_pu_tmp_n = 0.0F;
      rtDW->SinCos1_o2 = 0.0F;
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->jmax = rtDW->iy << 2;
        rtDW->rtb_vd_1_pu_tmp_n += (rtDW->H[rtDW->jmax + 3] * rtDW->x_data[3] +
          (rtDW->H[rtDW->jmax + 2] * rtDW->x_data[2] + (rtDW->H[rtDW->jmax + 1] *
          rtDW->x_data[1] + rtDW->H[rtDW->jmax] * rtDW->x_data[0]))) *
          rtDW->x_data[rtDW->iy];
        rtDW->IndexVector[rtDW->iy] = 0.0F;
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 8; rtDW->idxAjj++) {
          rtDW->IndexVector[rtDW->iy] += rtDW->M[(rtDW->iy << 3) + rtDW->idxAjj]
            * (2.0F * rtDW->r[rtDW->idxAjj]);
        }

        rtDW->SinCos1_o2 += rtDW->IndexVector[rtDW->iy] * rtDW->x_data[rtDW->iy];
      }

      rtDW->SinCos1_o1 = rtDW->rtb_vd_1_pu_tmp_n - rtDW->SinCos1_o2;
    }

    /* '<S21>:1:45' if (unsuited(2) == false) */
    if (!rtDW->unsuited_k) {
      /* '<S21>:1:46' [x2,iter2] = mpc_solve(H2,f2,A,b,Aeq,beq,iA0,max_iter,tol); */
      /* '<S21>:1:70' x = single([0 0 0 0]'); */
      /* '<S21>:1:71' iter = single(0); */
      /*  set up solver */
      /* '<S21>:1:73' options = mpcActiveSetOptions('single'); */
      /* '<S21>:1:74' options.MaxIterations = max_iter; */
      /* '<S21>:1:75' options.ConstriantTolerance = tol; */
      /* '<S21>:1:76' options.UseHessianAsInput = false; */
      /* '<S21>:1:77' options.IntegrityChecks = false; */
      /* '<S21>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
      /* '<S21>:1:81' exitflag = single(0); */
      /*  calculate inverse of H */
      /* '<S21>:1:83' [L,~] = chol(H,'lower'); */
      rtDW->Hinv_size[0] = 4;
      rtDW->Hinv_size[1] = 4;
      memcpy(&rtDW->H[0], &rtDW->H_l[0], sizeof(real32_T) << 4U);
      cholesky(rtDW->H, rtDW->Hinv_size, rtDW);

      /* '<S21>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
      if ((int8_T)rtDW->Hinv_size[0] < (int8_T)rtDW->Hinv_size[1]) {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[0];
      } else {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[1];
      }

      rtDW->b_I_size[0] = (int8_T)rtDW->Hinv_size[0];
      rtDW->b_I_size[1] = (int8_T)rtDW->Hinv_size[1];
      rtDW->b_ix = (int8_T)rtDW->Hinv_size[0] * (int8_T)rtDW->Hinv_size[1] - 1;
      if (0 <= rtDW->b_ix) {
        memset(&rtDW->b_I_data[0], 0, (rtDW->b_ix + 1) * sizeof(real_T));
      }

      if (rtDW->b_d > 0) {
        rtDW->d = 0;
        while (rtDW->d <= rtDW->b_d - 1) {
          rtDW->b_I_data[rtDW->d + rtDW->b_I_size[0] * rtDW->d] = 1.0;
          rtDW->d++;
        }
      }

      linsolve(rtDW->H, rtDW->Hinv_size, rtDW->b_I_data, rtDW->b_I_size,
               rtDW->Linv_data, rtDW->Linv_size, rtDW);

      /*  solve QP */
      /* '<S21>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
      rtDW->x2[0] = -rtDW->f_gy[0];
      rtDW->x2[1] = -rtDW->f_gy[1];
      rtDW->x2[2] = -rtDW->f_gy[2];
      rtDW->x2[3] = -rtDW->f_gy[3];
      mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x2,
                         rtU->max_iter, rtDW->x_data, &rtDW->x_size,
                         &rtDW->iter2, rtDW);

      /* '<S21>:1:87' x = single(x_tmp(1:4,1)); */
      /* '<S21>:1:88' iter = single(exitflag); */
      /* '<S21>:1:47' J2 = x2'*(M2'*M2)*x2-2*r2'*M2*x2; */
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->x2[rtDW->iy] = rtDW->x_data[rtDW->iy];
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 4; rtDW->idxAjj++) {
          rtDW->b_d = rtDW->iy + (rtDW->idxAjj << 2);
          rtDW->H_l[rtDW->b_d] = 0.0F;
          for (rtDW->jmax = 0; rtDW->jmax < 8; rtDW->jmax++) {
            rtDW->H_l[rtDW->b_d] += rtDW->M_h[(rtDW->iy << 3) + rtDW->jmax] *
              rtDW->M_h[(rtDW->idxAjj << 3) + rtDW->jmax];
          }
        }
      }

      rtDW->rtb_vd_1_pu_tmp_n = 0.0F;
      rtDW->SinCos1_o2 = 0.0F;
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->jmax = rtDW->iy << 2;
        rtDW->rtb_vd_1_pu_tmp_n += (rtDW->H_l[rtDW->jmax + 3] * rtDW->x_data[3]
          + (rtDW->H_l[rtDW->jmax + 2] * rtDW->x_data[2] + (rtDW->H_l[rtDW->jmax
          + 1] * rtDW->x_data[1] + rtDW->H_l[rtDW->jmax] * rtDW->x_data[0]))) *
          rtDW->x_data[rtDW->iy];
        rtDW->IndexVector[rtDW->iy] = 0.0F;
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 8; rtDW->idxAjj++) {
          rtDW->IndexVector[rtDW->iy] += rtDW->M_h[(rtDW->iy << 3) +
            rtDW->idxAjj] * (2.0F * rtDW->r_ff[rtDW->idxAjj]);
        }

        rtDW->SinCos1_o2 += rtDW->IndexVector[rtDW->iy] * rtDW->x_data[rtDW->iy];
      }

      rtDW->vd_1_pu[1] = rtDW->rtb_vd_1_pu_tmp_n - rtDW->SinCos1_o2;
    }

    /* '<S21>:1:49' if (unsuited(3) == false) */
    if (!rtDW->unsuited_f) {
      /* '<S21>:1:50' [x3,iter3] = mpc_solve(H3,f3,A,b,Aeq,beq,iA0,max_iter,tol); */
      /* '<S21>:1:70' x = single([0 0 0 0]'); */
      /* '<S21>:1:71' iter = single(0); */
      /*  set up solver */
      /* '<S21>:1:73' options = mpcActiveSetOptions('single'); */
      /* '<S21>:1:74' options.MaxIterations = max_iter; */
      /* '<S21>:1:75' options.ConstriantTolerance = tol; */
      /* '<S21>:1:76' options.UseHessianAsInput = false; */
      /* '<S21>:1:77' options.IntegrityChecks = false; */
      /* '<S21>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
      /* '<S21>:1:81' exitflag = single(0); */
      /*  calculate inverse of H */
      /* '<S21>:1:83' [L,~] = chol(H,'lower'); */
      rtDW->Hinv_size[0] = 4;
      rtDW->Hinv_size[1] = 4;
      memcpy(&rtDW->H[0], &rtDW->H_p[0], sizeof(real32_T) << 4U);
      cholesky(rtDW->H, rtDW->Hinv_size, rtDW);

      /* '<S21>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
      if ((int8_T)rtDW->Hinv_size[0] < (int8_T)rtDW->Hinv_size[1]) {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[0];
      } else {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[1];
      }

      rtDW->b_I_size[0] = (int8_T)rtDW->Hinv_size[0];
      rtDW->b_I_size[1] = (int8_T)rtDW->Hinv_size[1];
      rtDW->b_ix = (int8_T)rtDW->Hinv_size[0] * (int8_T)rtDW->Hinv_size[1] - 1;
      if (0 <= rtDW->b_ix) {
        memset(&rtDW->b_I_data[0], 0, (rtDW->b_ix + 1) * sizeof(real_T));
      }

      if (rtDW->b_d > 0) {
        rtDW->jmax = 0;
        while (rtDW->jmax <= rtDW->b_d - 1) {
          rtDW->b_I_data[rtDW->jmax + rtDW->b_I_size[0] * rtDW->jmax] = 1.0;
          rtDW->jmax++;
        }
      }

      linsolve(rtDW->H, rtDW->Hinv_size, rtDW->b_I_data, rtDW->b_I_size,
               rtDW->Linv_data, rtDW->Linv_size, rtDW);

      /*  solve QP */
      /* '<S21>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
      rtDW->x3[0] = -rtDW->f_h[0];
      rtDW->x3[1] = -rtDW->f_h[1];
      rtDW->x3[2] = -rtDW->f_h[2];
      rtDW->x3[3] = -rtDW->f_h[3];
      mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x3,
                         rtU->max_iter, rtDW->x_data, &rtDW->x_size,
                         &rtDW->iter3, rtDW);

      /* '<S21>:1:87' x = single(x_tmp(1:4,1)); */
      /* '<S21>:1:88' iter = single(exitflag); */
      /* '<S21>:1:51' J3 = x3'*(M3'*M3)*x3-2*r3'*M3*x3; */
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->x3[rtDW->iy] = rtDW->x_data[rtDW->iy];
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 4; rtDW->idxAjj++) {
          rtDW->b_d = rtDW->iy + (rtDW->idxAjj << 2);
          rtDW->H_p[rtDW->b_d] = 0.0F;
          for (rtDW->jmax = 0; rtDW->jmax < 8; rtDW->jmax++) {
            rtDW->H_p[rtDW->b_d] += rtDW->M_l[(rtDW->iy << 3) + rtDW->jmax] *
              rtDW->M_l[(rtDW->idxAjj << 3) + rtDW->jmax];
          }
        }
      }

      rtDW->rtb_vd_1_pu_tmp_n = 0.0F;
      rtDW->SinCos1_o2 = 0.0F;
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->jmax = rtDW->iy << 2;
        rtDW->rtb_vd_1_pu_tmp_n += (rtDW->H_p[rtDW->jmax + 3] * rtDW->x_data[3]
          + (rtDW->H_p[rtDW->jmax + 2] * rtDW->x_data[2] + (rtDW->H_p[rtDW->jmax
          + 1] * rtDW->x_data[1] + rtDW->H_p[rtDW->jmax] * rtDW->x_data[0]))) *
          rtDW->x_data[rtDW->iy];
        rtDW->IndexVector[rtDW->iy] = 0.0F;
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 8; rtDW->idxAjj++) {
          rtDW->IndexVector[rtDW->iy] += rtDW->M_l[(rtDW->iy << 3) +
            rtDW->idxAjj] * (2.0F * rtDW->r_b[rtDW->idxAjj]);
        }

        rtDW->SinCos1_o2 += rtDW->IndexVector[rtDW->iy] * rtDW->x_data[rtDW->iy];
      }

      rtDW->vd_1_pu[2] = rtDW->rtb_vd_1_pu_tmp_n - rtDW->SinCos1_o2;
    }

    /* '<S21>:1:53' if (unsuited(4) == false) */
    if (!rtDW->unsuited_i) {
      /* '<S21>:1:54' [x4,iter4] = mpc_solve(H4,f4,A,b,Aeq,beq,iA0,max_iter,tol); */
      /* '<S21>:1:70' x = single([0 0 0 0]'); */
      /* '<S21>:1:71' iter = single(0); */
      /*  set up solver */
      /* '<S21>:1:73' options = mpcActiveSetOptions('single'); */
      /* '<S21>:1:74' options.MaxIterations = max_iter; */
      /* '<S21>:1:75' options.ConstriantTolerance = tol; */
      /* '<S21>:1:76' options.UseHessianAsInput = false; */
      /* '<S21>:1:77' options.IntegrityChecks = false; */
      /* '<S21>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
      /* '<S21>:1:81' exitflag = single(0); */
      /*  calculate inverse of H */
      /* '<S21>:1:83' [L,~] = chol(H,'lower'); */
      rtDW->Hinv_size[0] = 4;
      rtDW->Hinv_size[1] = 4;
      memcpy(&rtDW->H[0], &rtDW->H_m[0], sizeof(real32_T) << 4U);
      cholesky(rtDW->H, rtDW->Hinv_size, rtDW);

      /* '<S21>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
      if ((int8_T)rtDW->Hinv_size[0] < (int8_T)rtDW->Hinv_size[1]) {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[0];
      } else {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[1];
      }

      rtDW->b_I_size[0] = (int8_T)rtDW->Hinv_size[0];
      rtDW->b_I_size[1] = (int8_T)rtDW->Hinv_size[1];
      rtDW->b_ix = (int8_T)rtDW->Hinv_size[0] * (int8_T)rtDW->Hinv_size[1] - 1;
      if (0 <= rtDW->b_ix) {
        memset(&rtDW->b_I_data[0], 0, (rtDW->b_ix + 1) * sizeof(real_T));
      }

      if (rtDW->b_d > 0) {
        rtDW->idxAjj = 0;
        while (rtDW->idxAjj <= rtDW->b_d - 1) {
          rtDW->b_I_data[rtDW->idxAjj + rtDW->b_I_size[0] * rtDW->idxAjj] = 1.0;
          rtDW->idxAjj++;
        }
      }

      linsolve(rtDW->H, rtDW->Hinv_size, rtDW->b_I_data, rtDW->b_I_size,
               rtDW->Linv_data, rtDW->Linv_size, rtDW);

      /*  solve QP */
      /* '<S21>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
      rtDW->x4[0] = -rtDW->f_f[0];
      rtDW->x4[1] = -rtDW->f_f[1];
      rtDW->x4[2] = -rtDW->f_f[2];
      rtDW->x4[3] = -rtDW->f_f[3];
      mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x4,
                         rtU->max_iter, rtDW->x_data, &rtDW->x_size,
                         &rtDW->iter4, rtDW);

      /* '<S21>:1:87' x = single(x_tmp(1:4,1)); */
      /* '<S21>:1:88' iter = single(exitflag); */
      /* '<S21>:1:55' J4 = x4'*(M4'*M4)*x4-2*r4'*M4*x4; */
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->x4[rtDW->iy] = rtDW->x_data[rtDW->iy];
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 4; rtDW->idxAjj++) {
          rtDW->b_d = rtDW->iy + (rtDW->idxAjj << 2);
          rtDW->H_m[rtDW->b_d] = 0.0F;
          for (rtDW->jmax = 0; rtDW->jmax < 8; rtDW->jmax++) {
            rtDW->H_m[rtDW->b_d] += rtDW->M_ny[(rtDW->iy << 3) + rtDW->jmax] *
              rtDW->M_ny[(rtDW->idxAjj << 3) + rtDW->jmax];
          }
        }
      }

      rtDW->rtb_vd_1_pu_tmp_n = 0.0F;
      rtDW->SinCos1_o2 = 0.0F;
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->jmax = rtDW->iy << 2;
        rtDW->rtb_vd_1_pu_tmp_n += (rtDW->H_m[rtDW->jmax + 3] * rtDW->x_data[3]
          + (rtDW->H_m[rtDW->jmax + 2] * rtDW->x_data[2] + (rtDW->H_m[rtDW->jmax
          + 1] * rtDW->x_data[1] + rtDW->H_m[rtDW->jmax] * rtDW->x_data[0]))) *
          rtDW->x_data[rtDW->iy];
        rtDW->IndexVector[rtDW->iy] = 0.0F;
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 8; rtDW->idxAjj++) {
          rtDW->IndexVector[rtDW->iy] += rtDW->M_ny[(rtDW->iy << 3) +
            rtDW->idxAjj] * (2.0F * rtDW->r_j[rtDW->idxAjj]);
        }

        rtDW->SinCos1_o2 += rtDW->IndexVector[rtDW->iy] * rtDW->x_data[rtDW->iy];
      }

      rtDW->vd_1_pu[3] = rtDW->rtb_vd_1_pu_tmp_n - rtDW->SinCos1_o2;
    }

    /* '<S21>:1:57' if (unsuited(5) == false) */
    if (!rtDW->unsuited_j) {
      /* '<S21>:1:58' [x5,iter5] = mpc_solve(H5,f5,A,b,Aeq,beq,iA0,max_iter,tol); */
      /* '<S21>:1:70' x = single([0 0 0 0]'); */
      /* '<S21>:1:71' iter = single(0); */
      /*  set up solver */
      /* '<S21>:1:73' options = mpcActiveSetOptions('single'); */
      /* '<S21>:1:74' options.MaxIterations = max_iter; */
      /* '<S21>:1:75' options.ConstriantTolerance = tol; */
      /* '<S21>:1:76' options.UseHessianAsInput = false; */
      /* '<S21>:1:77' options.IntegrityChecks = false; */
      /* '<S21>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
      /* '<S21>:1:81' exitflag = single(0); */
      /*  calculate inverse of H */
      /* '<S21>:1:83' [L,~] = chol(H,'lower'); */
      rtDW->Hinv_size[0] = 4;
      rtDW->Hinv_size[1] = 4;
      memcpy(&rtDW->H[0], &rtDW->H_n[0], sizeof(real32_T) << 4U);
      cholesky(rtDW->H, rtDW->Hinv_size, rtDW);

      /* '<S21>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
      if ((int8_T)rtDW->Hinv_size[0] < (int8_T)rtDW->Hinv_size[1]) {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[0];
      } else {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[1];
      }

      rtDW->b_I_size[0] = (int8_T)rtDW->Hinv_size[0];
      rtDW->b_I_size[1] = (int8_T)rtDW->Hinv_size[1];
      rtDW->b_ix = (int8_T)rtDW->Hinv_size[0] * (int8_T)rtDW->Hinv_size[1] - 1;
      if (0 <= rtDW->b_ix) {
        memset(&rtDW->b_I_data[0], 0, (rtDW->b_ix + 1) * sizeof(real_T));
      }

      if (rtDW->b_d > 0) {
        rtDW->jmax = 0;
        while (rtDW->jmax <= rtDW->b_d - 1) {
          rtDW->b_I_data[rtDW->jmax + rtDW->b_I_size[0] * rtDW->jmax] = 1.0;
          rtDW->jmax++;
        }
      }

      linsolve(rtDW->H, rtDW->Hinv_size, rtDW->b_I_data, rtDW->b_I_size,
               rtDW->Linv_data, rtDW->Linv_size, rtDW);

      /*  solve QP */
      /* '<S21>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
      rtDW->x5[0] = -rtDW->f_g[0];
      rtDW->x5[1] = -rtDW->f_g[1];
      rtDW->x5[2] = -rtDW->f_g[2];
      rtDW->x5[3] = -rtDW->f_g[3];
      mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x5,
                         rtU->max_iter, rtDW->x_data, &rtDW->x_size,
                         &rtDW->iter5, rtDW);

      /* '<S21>:1:87' x = single(x_tmp(1:4,1)); */
      /* '<S21>:1:88' iter = single(exitflag); */
      /* '<S21>:1:59' J5 = x5'*(M5'*M5)*x5-2*r5'*M5*x5; */
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->x5[rtDW->iy] = rtDW->x_data[rtDW->iy];
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 4; rtDW->idxAjj++) {
          rtDW->b_d = rtDW->iy + (rtDW->idxAjj << 2);
          rtDW->H_n[rtDW->b_d] = 0.0F;
          for (rtDW->jmax = 0; rtDW->jmax < 8; rtDW->jmax++) {
            rtDW->H_n[rtDW->b_d] += rtDW->M_o[(rtDW->iy << 3) + rtDW->jmax] *
              rtDW->M_o[(rtDW->idxAjj << 3) + rtDW->jmax];
          }
        }
      }

      rtDW->rtb_vd_1_pu_tmp_n = 0.0F;
      rtDW->SinCos1_o2 = 0.0F;
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->jmax = rtDW->iy << 2;
        rtDW->rtb_vd_1_pu_tmp_n += (rtDW->H_n[rtDW->jmax + 3] * rtDW->x_data[3]
          + (rtDW->H_n[rtDW->jmax + 2] * rtDW->x_data[2] + (rtDW->H_n[rtDW->jmax
          + 1] * rtDW->x_data[1] + rtDW->H_n[rtDW->jmax] * rtDW->x_data[0]))) *
          rtDW->x_data[rtDW->iy];
        rtDW->IndexVector[rtDW->iy] = 0.0F;
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 8; rtDW->idxAjj++) {
          rtDW->IndexVector[rtDW->iy] += rtDW->M_o[(rtDW->iy << 3) +
            rtDW->idxAjj] * (2.0F * rtDW->r_g[rtDW->idxAjj]);
        }

        rtDW->SinCos1_o2 += rtDW->IndexVector[rtDW->iy] * rtDW->x_data[rtDW->iy];
      }

      rtDW->vd_1_pu[4] = rtDW->rtb_vd_1_pu_tmp_n - rtDW->SinCos1_o2;
    }

    /* '<S21>:1:61' if (unsuited(6) == false) */
    if (!rtDW->unsuited) {
      /* '<S21>:1:62' [x6,iter6] = mpc_solve(H6,f6,A,b,Aeq,beq,iA0,max_iter,tol); */
      /* '<S21>:1:70' x = single([0 0 0 0]'); */
      /* '<S21>:1:71' iter = single(0); */
      /*  set up solver */
      /* '<S21>:1:73' options = mpcActiveSetOptions('single'); */
      /* '<S21>:1:74' options.MaxIterations = max_iter; */
      /* '<S21>:1:75' options.ConstriantTolerance = tol; */
      /* '<S21>:1:76' options.UseHessianAsInput = false; */
      /* '<S21>:1:77' options.IntegrityChecks = false; */
      /* '<S21>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
      /* '<S21>:1:81' exitflag = single(0); */
      /*  calculate inverse of H */
      /* '<S21>:1:83' [L,~] = chol(H,'lower'); */
      rtDW->Hinv_size[0] = 4;
      rtDW->Hinv_size[1] = 4;
      memcpy(&rtDW->H[0], &rtDW->H_c[0], sizeof(real32_T) << 4U);
      cholesky(rtDW->H, rtDW->Hinv_size, rtDW);

      /* '<S21>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
      if ((int8_T)rtDW->Hinv_size[0] < (int8_T)rtDW->Hinv_size[1]) {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[0];
      } else {
        rtDW->b_d = (int8_T)rtDW->Hinv_size[1];
      }

      rtDW->b_I_size[0] = (int8_T)rtDW->Hinv_size[0];
      rtDW->b_I_size[1] = (int8_T)rtDW->Hinv_size[1];
      rtDW->b_ix = (int8_T)rtDW->Hinv_size[0] * (int8_T)rtDW->Hinv_size[1] - 1;
      if (0 <= rtDW->b_ix) {
        memset(&rtDW->b_I_data[0], 0, (rtDW->b_ix + 1) * sizeof(real_T));
      }

      if (rtDW->b_d > 0) {
        rtDW->jmax = 0;
        while (rtDW->jmax <= rtDW->b_d - 1) {
          rtDW->b_I_data[rtDW->jmax + rtDW->b_I_size[0] * rtDW->jmax] = 1.0;
          rtDW->jmax++;
        }
      }

      linsolve(rtDW->H, rtDW->Hinv_size, rtDW->b_I_data, rtDW->b_I_size,
               rtDW->Linv_data, rtDW->Linv_size, rtDW);

      /*  solve QP */
      /* '<S21>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
      rtDW->f_g[0] = -rtDW->f_m[0];
      rtDW->f_g[1] = -rtDW->f_m[1];
      rtDW->f_g[2] = -rtDW->f_m[2];
      rtDW->f_g[3] = -rtDW->f_m[3];
      mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->f_g,
                         rtU->max_iter, rtDW->x_data, &rtDW->x_size,
                         &rtDW->iter6, rtDW);

      /* '<S21>:1:87' x = single(x_tmp(1:4,1)); */
      /* '<S21>:1:88' iter = single(exitflag); */
      /* '<S21>:1:63' J6 = x6'*(M6'*M6)*x6-2*r6'*M6*x6; */
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->x6[rtDW->iy] = rtDW->x_data[rtDW->iy];
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 4; rtDW->idxAjj++) {
          rtDW->b_d = rtDW->iy + (rtDW->idxAjj << 2);
          rtDW->H_c[rtDW->b_d] = 0.0F;
          for (rtDW->jmax = 0; rtDW->jmax < 8; rtDW->jmax++) {
            rtDW->H_c[rtDW->b_d] += rtDW->M_n[(rtDW->iy << 3) + rtDW->jmax] *
              rtDW->M_n[(rtDW->idxAjj << 3) + rtDW->jmax];
          }
        }
      }

      rtDW->rtb_vd_1_pu_tmp_n = 0.0F;
      rtDW->SinCos1_o2 = 0.0F;
      for (rtDW->iy = 0; rtDW->iy < 4; rtDW->iy++) {
        rtDW->jmax = rtDW->iy << 2;
        rtDW->rtb_vd_1_pu_tmp_n += (rtDW->H_c[rtDW->jmax + 3] * rtDW->x_data[3]
          + (rtDW->H_c[rtDW->jmax + 2] * rtDW->x_data[2] + (rtDW->H_c[rtDW->jmax
          + 1] * rtDW->x_data[1] + rtDW->H_c[rtDW->jmax] * rtDW->x_data[0]))) *
          rtDW->x_data[rtDW->iy];
        rtDW->IndexVector[rtDW->iy] = 0.0F;
        for (rtDW->idxAjj = 0; rtDW->idxAjj < 8; rtDW->idxAjj++) {
          rtDW->IndexVector[rtDW->iy] += rtDW->M_n[(rtDW->iy << 3) +
            rtDW->idxAjj] * (2.0F * rtDW->r_f[rtDW->idxAjj]);
        }

        rtDW->SinCos1_o2 += rtDW->IndexVector[rtDW->iy] * rtDW->x_data[rtDW->iy];
      }

      rtDW->vd_1_pu[5] = rtDW->rtb_vd_1_pu_tmp_n - rtDW->SinCos1_o2;
    }

    /* MATLAB Function: '<S3>/min_Costs' incorporates:
     *  MATLAB Function: '<S3>/qp_solver_for_suited_seq_AS'
     */
    /*  end */
    /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/all/min_Costs': '<S20>:1' */
    /* '<S20>:1:3' J_1to6 = single([J1,J2,J3,J4,J5,J6]); */
    rtDW->vd_1_pu[0] = rtDW->SinCos1_o1;

    /* '<S20>:1:4' x_1to6 = single([x1,x2,x3,x4,x5,x6]); */
    /*  [~,idx] = min(J_1to6); */
    /* '<S20>:1:6' [~,idx] = minimum(J_1to6); */
    /* '<S20>:1:12' min_tmp = X(1); */
    /* '<S20>:1:13' idx_tmp = single(1); */
    rtDW->jmax = 0;

    /* '<S20>:1:14' for i=1:6 */
    for (rtDW->b_d = 0; rtDW->b_d < 6; rtDW->b_d++) {
      rtDW->rtb_vd_1_pu_tmp_n = rtDW->vd_1_pu[rtDW->b_d];

      /* '<S20>:1:15' if(X(i) < min_tmp) */
      if (rtDW->rtb_vd_1_pu_tmp_n < rtDW->SinCos1_o1) {
        /* '<S20>:1:16' min_tmp = X(i); */
        rtDW->SinCos1_o1 = rtDW->rtb_vd_1_pu_tmp_n;

        /* '<S20>:1:17' idx_tmp = single(i); */
        rtDW->jmax = rtDW->b_d;
      }
    }

    /* '<S20>:1:20' min = min_tmp; */
    /* '<S20>:1:21' idx = idx_tmp; */
    /* '<S20>:1:7' x_opt = single(x_1to6(:,idx)); */
    rtDW->rtb_x1_m[0] = rtDW->x1_k[0];
    rtDW->rtb_x1_m[4] = rtDW->x2[0];
    rtDW->rtb_x1_m[8] = rtDW->x3[0];
    rtDW->rtb_x1_m[12] = rtDW->x4[0];
    rtDW->rtb_x1_m[16] = rtDW->x5[0];
    rtDW->rtb_x1_m[20] = rtDW->x6[0];
    rtDW->rtb_x1_m[1] = rtDW->x1_k[1];
    rtDW->rtb_x1_m[5] = rtDW->x2[1];
    rtDW->rtb_x1_m[9] = rtDW->x3[1];
    rtDW->rtb_x1_m[13] = rtDW->x4[1];
    rtDW->rtb_x1_m[17] = rtDW->x5[1];
    rtDW->rtb_x1_m[21] = rtDW->x6[1];
    rtDW->rtb_x1_m[2] = rtDW->x1_k[2];
    rtDW->rtb_x1_m[6] = rtDW->x2[2];
    rtDW->rtb_x1_m[10] = rtDW->x3[2];
    rtDW->rtb_x1_m[14] = rtDW->x4[2];
    rtDW->rtb_x1_m[18] = rtDW->x5[2];
    rtDW->rtb_x1_m[22] = rtDW->x6[2];
    rtDW->rtb_x1_m[3] = rtDW->x1_k[3];
    rtDW->rtb_x1_m[7] = rtDW->x2[3];
    rtDW->rtb_x1_m[11] = rtDW->x3[3];
    rtDW->rtb_x1_m[15] = rtDW->x4[3];
    rtDW->rtb_x1_m[19] = rtDW->x5[3];
    rtDW->rtb_x1_m[23] = rtDW->x6[3];
    rtDW->iy = rtDW->jmax << 2;
    rtDW->x_opt[0] = rtDW->rtb_x1_m[rtDW->iy];
    rtDW->x_opt[1] = rtDW->rtb_x1_m[rtDW->iy + 1];
    rtDW->x_opt[2] = rtDW->rtb_x1_m[rtDW->iy + 2];
    rtDW->x_opt[3] = rtDW->rtb_x1_m[rtDW->iy + 3];

    /* '<S20>:1:8' idx_opt = single(idx); */
    rtDW->idx_opt = (real32_T)rtDW->jmax + 1.0F;

    /* End of MATLAB Function: '<S3>/min_Costs' */

    /* Update for Delay: '<S3>/Delay1' */
    rtDW->icLoad_a = false;

    /* End of Outputs for SubSystem: '<S1>/all' */
  }

  /* End of If: '<S1>/if all true' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Inport: '<Root>/all_or_deadbeat'
   */
  /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/tz': '<S6>:1' */
  /* '<S6>:1:3' I = single([1 0 0; */
  /* '<S6>:1:4'      1 1 0; */
  /* '<S6>:1:5'      1 1 1]); */
  /* '<S6>:1:7' zer3 = single(zeros(3,1)); */
  /* '<S6>:1:9' T = single([I zer3]); */
  /* '<S6>:1:11' tz=single(T*x); */
  if (rtU->all_or_deadbeat > 0.5F) {
    rtDW->SinCos1_o1 = rtDW->x1[0];
    rtDW->rtb_vd_1_pu_tmp_n = rtDW->x1[1];
    rtDW->rtb_vq_1_pu_idx_0_tmp = rtDW->x1[2];
    rtDW->rtb_vd_2_pu_idx_0_tmp = rtDW->x1[3];
  } else {
    rtDW->SinCos1_o1 = rtDW->x_opt[0];
    rtDW->rtb_vd_1_pu_tmp_n = rtDW->x_opt[1];
    rtDW->rtb_vq_1_pu_idx_0_tmp = rtDW->x_opt[2];
    rtDW->rtb_vd_2_pu_idx_0_tmp = rtDW->x_opt[3];
  }

  /* End of Switch: '<S1>/Switch' */

  /* MATLAB Function: '<S1>/tz' */
  for (rtDW->iy = 0; rtDW->iy < 3; rtDW->iy++) {
    rtDW->tz[rtDW->iy] = (real32_T)a[rtDW->iy + 9] * rtDW->rtb_vd_2_pu_idx_0_tmp
      + ((real32_T)a[rtDW->iy + 6] * rtDW->rtb_vq_1_pu_idx_0_tmp + ((real32_T)
          a[rtDW->iy + 3] * rtDW->rtb_vd_1_pu_tmp_n + (real32_T)a[rtDW->iy] *
          rtDW->SinCos1_o1));
  }

  /* End of MATLAB Function: '<S1>/tz' */

  /* Switch: '<S1>/Switch1' incorporates:
   *  Inport: '<Root>/all_or_deadbeat'
   */
  if (rtU->all_or_deadbeat > 0.5F) {
    rtDW->Switch1 = rtDW->sector_ref;
  } else {
    rtDW->Switch1 = rtDW->idx_opt;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Outport: '<Root>/CMPA_opt' incorporates:
   *  MATLAB Function: '<S1>/tz_2_tph'
   */
  /* MATLAB Function 'impl_modul_mpc_all_and_deadbeat/tz_2_tph': '<S7>:1' */
  /* '<S7>:1:3' seq_order_table = single([1 2 3; */
  /* '<S7>:1:4'                    2 1 3; */
  /* '<S7>:1:5'                    3 1 2; */
  /* '<S7>:1:6'                    3 2 1; */
  /* '<S7>:1:7'                    2 3 1; */
  /* '<S7>:1:8'                    1 3 2]); */
  /* '<S7>:1:10' ta_1 = single(tz(seq_order_table(seq_no,1))); */
  /* '<S7>:1:11' tb_1 = single(tz(seq_order_table(seq_no,2))); */
  /* '<S7>:1:12' tc_1 = single(tz(seq_order_table(seq_no,3))); */
  rtY->CMPA_opt[0] = rtDW->tz[seq_order_table[(int32_T)rtDW->Switch1 - 1] - 1];
  rtY->CMPA_opt[1] = rtDW->tz[seq_order_table[(int32_T)rtDW->Switch1 + 5] - 1];
  rtY->CMPA_opt[2] = rtDW->tz[seq_order_table[(int32_T)rtDW->Switch1 + 11] - 1];

  /* Outport: '<Root>/iterations_qp' */
  rtY->iterations_qp[0] = rtDW->iter1_o;
  rtY->iterations_qp[1] = rtDW->iter2;
  rtY->iterations_qp[2] = rtDW->iter3;
  rtY->iterations_qp[3] = rtDW->iter4;
  rtY->iterations_qp[4] = rtDW->iter5;
  rtY->iterations_qp[5] = rtDW->iter6;

  /* Outport: '<Root>/unsuited_qp' */
  rtY->unsuited_qp[0] = rtDW->unsuited_h;
  rtY->unsuited_qp[1] = rtDW->unsuited_k;
  rtY->unsuited_qp[2] = rtDW->unsuited_f;
  rtY->unsuited_qp[3] = rtDW->unsuited_i;
  rtY->unsuited_qp[4] = rtDW->unsuited_j;
  rtY->unsuited_qp[5] = rtDW->unsuited;
}

/* Model initialize function */
void impl_modul_mpc_all_and_deadbeat_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));

  /* Start for If: '<S1>/if deadbeat true' */
  rtDW->ifdeadbeattrue_ActiveSubsystem = -1;

  /* Start for If: '<S1>/if all true' */
  rtDW->ifalltrue_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: '<S1>/deadbeat' */
  /* InitializeConditions for Delay: '<S4>/Delay2' */
  rtDW->icLoad = true;

  /* End of SystemInitialize for SubSystem: '<S1>/deadbeat' */

  /* SystemInitialize for IfAction SubSystem: '<S1>/all' */
  /* InitializeConditions for Delay: '<S3>/Delay1' */
  rtDW->icLoad_a = true;

  /* End of SystemInitialize for SubSystem: '<S1>/all' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
