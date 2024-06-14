/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: impl_modul_mpc_allQP.c
 *
 * Code generated for Simulink model 'impl_modul_mpc_allQP'.
 *
 * Model version                  : 2.15
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Fri Jun  7 13:25:03 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "impl_modul_mpc_allQP.h"

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
static int32_T cholesky(real32_T A_data[], int32_T A_size[2], DW *rtDW);
static void trisolve(const real32_T A_data[], const int32_T A_size[2], real32_T
                     B_data[], const int32_T B_size[2], DW *rtDW);
static void linsolve(const real32_T A_data[], const int32_T A_size[2], const
                     real_T B_data[], const int32_T B_size[2], real32_T C_data[],
                     int32_T C_size[2], DW *rtDW);
static void Unconstrained(const real32_T Hinv_data[], const int32_T Hinv_size[2],
  const real32_T f[4], real32_T x_data[], int16_T n, DW *rtDW);
static real32_T norm(const real32_T x_data[], const int32_T *x_size, DW *rtDW);
static void abs_a(const real32_T x[4], real32_T y[4]);
static real32_T maximum(const real32_T x[4]);
static void maximum2(const real32_T x[5], real32_T ex[5], DW *rtDW);
static real32_T xnrm2(int32_T n, const real32_T x_data[], int32_T ix0, DW *rtDW);
static real32_T rt_hypotf_f(real32_T u0, real32_T u1, DW *rtDW);
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
static real32_T mtimes_g(const real32_T A_data[], const real32_T B_1[4]);
static void DropConstraint(int16_T kDrop, int16_T iA[5], int16_T *nA, int16_T
  iC[5], DW *rtDW);
static void ResetToColdStart(int16_T iA[5], int16_T iC[5], DW *rtDW);
static void qpkwik(const real32_T Linv_data[], const int32_T Linv_size[2], const
                   real32_T Hinv_data[], const int32_T Hinv_size[2], const
                   real32_T f[4], int16_T maxiter, int16_T n, real32_T x_data[],
                   int32_T *x_size, real32_T lambda[5], real32_T *status,
                   int16_T iA[5], DW *rtDW);
static void mpcActiveSetSolver(const real32_T H_data[], const int32_T H_size[2],
  const real32_T f[4], real32_T options_MaxIterations, real32_T x_data[],
  int32_T *x_size, real32_T *exitflag, DW *rtDW);

/*
 * Output and update for atomic system:
 *    '<S1>/detect_unsuited_sequence_1'
 *    '<S1>/detect_unsuited_sequence_2'
 *    '<S1>/detect_unsuited_sequence_3'
 *    '<S1>/detect_unsuited_sequence_4'
 *    '<S1>/detect_unsuited_sequence_5'
 *    '<S1>/detect_unsuited_sequence_6'
 */
static void detect_unsuited_sequence_1(const real32_T rtu_H[16], const real32_T
  rtu_f[4], boolean_T *rty_unsuited)
{
  int32_T i;
  real32_T z[4];
  real32_T lambda_ref;
  static const real32_T b[4] = { 0.5F, 0.0F, 0.0F, 0.5F };

  /*  pre calculations */
  /* MATLAB Function 'impl_modul_mpc_allQP/detect_unsuited_sequence_1': '<S3>:1' */
  /* '<S3>:1:4' t0 = [0.5 0 0 0.5]'; */
  /* '<S3>:1:5' g0 = H*t0-f; */
  /*  gradient vector g0=Hessian*initialpoint-f */
  /* '<S3>:1:7' z = t0-g0; */
  for (i = 0; i < 4; i++) {
    z[i] = b[i] - ((rtu_H[i + 12] * 0.5F + rtu_H[i] * 0.5F) - rtu_f[i]);
  }

  /* '<S3>:1:8' lambda_ref = (1-sum(z)) * 0.25; */
  lambda_ref = (1.0F - (((z[0] + z[1]) + z[2]) + z[3])) * 0.25F;

  /* '<S3>:1:9' tau_ref = lambda_ref*ones(4,1)+z; */
  /* '<S3>:1:10' unsuited = false; */
  *rty_unsuited = false;

  /* '<S3>:1:11' if (tau_ref(2) < 0 || tau_ref(3) < 0) */
  if (lambda_ref + z[1] < 0.0F) {
    /* '<S3>:1:12' unsuited = true; */
    *rty_unsuited = true;
  } else if (lambda_ref + z[2] < 0.0F) {
    /* '<S3>:1:12' unsuited = true; */
    *rty_unsuited = true;
  }
}

/*
 * Output and update for atomic system:
 *    '<S1>/formulate_qp_1'
 *    '<S1>/formulate_qp_2'
 *    '<S1>/formulate_qp_3'
 *    '<S1>/formulate_qp_4'
 *    '<S1>/formulate_qp_5'
 *    '<S1>/formulate_qp_6'
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

  /* MATLAB Function 'impl_modul_mpc_allQP/formulate_qp_1': '<S9>:1' */
  /* '<S9>:1:4' lam = [lambda 0; 0 lambda]; */
  /* '<S9>:1:6' i_t0 = [id0 iq0]'; */
  /* '<S9>:1:7' i_ref = [id_ref iq_ref]'; */
  /* '<S9>:1:8' e_i = i_ref - i_t0; */
  e_i_idx_0 = rtu_id_ref - rtu_id0;
  e_i_idx_1 = rtu_iq_ref - rtu_iq0;

  /* '<S9>:1:10' r = [e_i; e_i; e_i; lam*e_i]; */
  rty_r[0] = e_i_idx_0;
  rty_r[2] = e_i_idx_0;
  rty_r[4] = e_i_idx_0;
  rty_r[6] = rtu_lambda * e_i_idx_0;
  rty_r[1] = e_i_idx_1;
  rty_r[3] = e_i_idx_1;
  rty_r[5] = e_i_idx_1;
  rty_r[7] = rtu_lambda * e_i_idx_1;

  /* '<S9>:1:12' zer = zeros(2,1); */
  /* '<S9>:1:13' m0_lam = lam*m0; */
  /* '<S9>:1:14' m1_lam = lam*m1; */
  /* '<S9>:1:15' m2_lam = lam*m2; */
  /* '<S9>:1:16' m3_lam = lam*m3; */
  /* '<S9>:1:18' M = [m0     zer     zer     zer     ; */
  /* '<S9>:1:19'      m0     m1      zer     zer     ; */
  /* '<S9>:1:20'      m0     m1      m2      zer     ; */
  /* '<S9>:1:21'      m0_lam m1_lam  m2_lam  m3_lam ]; */
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

  /* '<S9>:1:23' H = 2*(M'*M); */
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

  /* '<S9>:1:24' f = 2*M'*r; */
  for (i = 0; i < 4; i++) {
    rty_f[i] = 0.0F;
    for (i_1 = 0; i_1 < 8; i_1++) {
      rty_f[i] += localDW->fv[(i_1 << 2) + i] * 2.0F * rty_r[i_1];
    }
  }
}

/*
 * Output and update for atomic system:
 *    '<S1>/state_space_mdl_1'
 *    '<S1>/state_space_mdl_2'
 *    '<S1>/state_space_mdl_3'
 *    '<S1>/state_space_mdl_4'
 *    '<S1>/state_space_mdl_5'
 *    '<S1>/state_space_mdl_6'
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

  /* MATLAB Function 'impl_modul_mpc_allQP/state_space_mdl_1': '<S18>:1' */
  /* '<S18>:1:4' A = [ -Ts_times_ZB_over_Ld*Rs_over_ZB   Ts_times_ZB_over_Ld*Lq_over_LB*w_e_pu   0; */
  /* '<S18>:1:5'       -Ts_times_ZB_over_Lq*Ld_over_LB*w_e_pu  -Ts_times_ZB_over_Lq*Rs_over_ZB   -Ts_times_ZB_over_Lq*psi_pm_over_psiB]; */
  /* '<S18>:1:7' B = [Ts_times_ZB_over_Ld   0   0; */
  /* '<S18>:1:8'      0   Ts_times_ZB_over_Lq   0]; */
  localDW->B_m[0] = rtu_Ts_times_ZB_over_Ld;
  localDW->B_m[2] = 0.0F;
  localDW->B_m[4] = 0.0F;
  localDW->B_m[1] = 0.0F;
  localDW->B_m[3] = rtu_Ts_times_ZB_over_Lq;
  localDW->B_m[5] = 0.0F;

  /* '<S18>:1:10' C = [1 0; */
  /* '<S18>:1:11'      0 1]; */
  /* '<S18>:1:13' x0 = [id_pu; iq_pu; w_e_pu]; */
  /* '<S18>:1:15' u0 = [0;0;0]; */
  /*  zero voltage applied */
  /* '<S18>:1:16' u1 = [vd_1_pu; vq_1_pu; 0]; */
  /*  first active vector */
  /* '<S18>:1:17' u2 = [vd_2_pu; vq_2_pu; 0]; */
  /*  second active vector */
  /* '<S18>:1:19' m0 = C*(A*x0+B*u0); */
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

  /* '<S18>:1:20' m1 = C*(A*x0+B*u1); */
  for (i = 0; i < 2; i++) {
    tmp_0[i] = (localDW->B_m[i + 2] * rtu_vq_1_pu + localDW->B_m[i] *
                rtu_vd_1_pu) + tmp[i];
  }

  rty_m1[0] = 0.0F;
  rty_m1[0] += tmp_0[0];
  rty_m1[1] = 0.0F;
  rty_m1[1] += tmp_0[1];

  /* '<S18>:1:21' m2 = C*(A*x0+B*u2); */
  for (i = 0; i < 2; i++) {
    tmp_0[i] = (localDW->B_m[i + 2] * rtu_vq_2_pu + localDW->B_m[i] *
                rtu_vd_2_pu) + tmp[i];
  }

  rty_m2[0] = 0.0F;
  rty_m2[0] += tmp_0[0];
  rty_m2[1] = 0.0F;
  rty_m2[1] += tmp_0[1];

  /* '<S18>:1:22' m3 = m0; */
  rty_m3_idx_0 = rty_m3[0];
  rty_m3_idx_1 = rty_m3[1];
  rty_m0[0] = rty_m3_idx_0;
  rty_m0[1] = rty_m3_idx_1;
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static int32_T cholesky(real32_T A_data[], int32_T A_size[2], DW *rtDW)
{
  int32_T b_k;
  int32_T info;
  boolean_T exitg1;
  memcpy(&rtDW->b_A_data[0], &A_data[0], sizeof(real32_T) << 4U);
  info = 0;
  rtDW->jmax = 0;
  exitg1 = false;
  while ((!exitg1) && (rtDW->jmax < 4)) {
    rtDW->idxAjj = (rtDW->jmax << 2) + rtDW->jmax;
    rtDW->ssq = 0.0F;
    if (rtDW->jmax >= 1) {
      rtDW->b_ix = rtDW->jmax;
      rtDW->b_iy = rtDW->jmax;
      for (b_k = 0; b_k < rtDW->jmax; b_k++) {
        rtDW->ssq += rtDW->b_A_data[rtDW->b_ix] * rtDW->b_A_data[rtDW->b_iy];
        rtDW->b_ix += 4;
        rtDW->b_iy += 4;
      }
    }

    rtDW->ssq = rtDW->b_A_data[rtDW->idxAjj] - rtDW->ssq;
    if (rtDW->ssq > 0.0F) {
      rtDW->ssq = sqrtf(rtDW->ssq);
      rtDW->b_A_data[rtDW->idxAjj] = rtDW->ssq;
      if (rtDW->jmax + 1 < 4) {
        if (rtDW->jmax != 0) {
          rtDW->b_ix = rtDW->jmax;
          rtDW->b_iy = (((rtDW->jmax - 1) << 2) + rtDW->jmax) + 2;
          for (b_k = rtDW->jmax + 2; b_k <= rtDW->b_iy; b_k += 4) {
            rtDW->b_c = -rtDW->b_A_data[rtDW->b_ix];
            rtDW->iy = rtDW->idxAjj + 1;
            rtDW->e = (b_k - rtDW->jmax) + 2;
            rtDW->ia = b_k;
            while (rtDW->ia <= rtDW->e) {
              rtDW->b_A_data[rtDW->iy] += rtDW->b_A_data[rtDW->ia - 1] *
                rtDW->b_c;
              rtDW->iy++;
              rtDW->ia++;
            }

            rtDW->b_ix += 4;
          }
        }

        rtDW->ssq = 1.0F / rtDW->ssq;
        rtDW->b_ix = (rtDW->idxAjj - rtDW->jmax) + 4;
        rtDW->idxAjj++;
        while (rtDW->idxAjj + 1 <= rtDW->b_ix) {
          rtDW->b_A_data[rtDW->idxAjj] *= rtDW->ssq;
          rtDW->idxAjj++;
        }
      }

      rtDW->jmax++;
    } else {
      rtDW->b_A_data[rtDW->idxAjj] = rtDW->ssq;
      info = rtDW->jmax + 1;
      exitg1 = true;
    }
  }

  A_size[0] = 4;
  A_size[1] = 4;
  for (rtDW->b_ix = 0; rtDW->b_ix < 4; rtDW->b_ix++) {
    rtDW->jmax = A_size[0] * rtDW->b_ix;
    A_data[rtDW->jmax] = rtDW->b_A_data[rtDW->b_ix << 2];
    A_data[1 + rtDW->jmax] = rtDW->b_A_data[1 + (rtDW->b_ix << 2)];
    A_data[2 + rtDW->jmax] = rtDW->b_A_data[2 + (rtDW->b_ix << 2)];
    A_data[3 + rtDW->jmax] = rtDW->b_A_data[3 + (rtDW->b_ix << 2)];
  }

  if (info == 0) {
    rtDW->jmax = 4;
  } else {
    rtDW->jmax = info - 1;
  }

  rtDW->idxAjj = 1;
  while (rtDW->idxAjj + 1 <= rtDW->jmax) {
    rtDW->b_ix = 0;
    while (rtDW->b_ix <= rtDW->idxAjj - 1) {
      A_data[rtDW->b_ix + A_size[0] * rtDW->idxAjj] = 0.0F;
      rtDW->b_ix++;
    }

    rtDW->idxAjj++;
  }

  if (1 > rtDW->jmax) {
    rtDW->b_ix = -1;
    rtDW->idxAjj = -1;
    b_k = -1;
  } else {
    rtDW->b_ix = rtDW->jmax - 1;
    rtDW->idxAjj = rtDW->jmax - 1;
    b_k = rtDW->jmax - 1;
  }

  rtDW->b_iy = rtDW->idxAjj + 1;
  for (rtDW->idxAjj = 0; rtDW->idxAjj <= b_k; rtDW->idxAjj++) {
    for (rtDW->jmax = 0; rtDW->jmax < rtDW->b_iy; rtDW->jmax++) {
      A_data[rtDW->jmax + (rtDW->b_ix + 1) * rtDW->idxAjj] = A_data[rtDW->jmax +
        A_size[0] * rtDW->idxAjj];
    }
  }

  A_size[0] = rtDW->b_ix + 1;
  A_size[1] = b_k + 1;
  return info;
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void trisolve(const real32_T A_data[], const int32_T A_size[2], real32_T
                     B_data[], const int32_T B_size[2], DW *rtDW)
{
  int32_T tmp;
  rtDW->mB = B_size[0];
  rtDW->nB = B_size[1] - 1;
  if (A_size[0] < A_size[1]) {
    rtDW->n_l = A_size[0];
  } else {
    rtDW->n_l = A_size[1];
  }

  if (rtDW->n_l >= B_size[0]) {
    rtDW->n_l = B_size[0];
  }

  if ((B_size[1] != 0) && ((B_size[0] != 0) && (B_size[1] != 0))) {
    rtDW->j_h = 0;
    while (rtDW->j_h <= rtDW->nB) {
      rtDW->jBcol = rtDW->mB * rtDW->j_h - 1;
      rtDW->k_b = 1;
      while (rtDW->k_b - 1 <= rtDW->n_l - 1) {
        rtDW->kAcol = (rtDW->k_b - 1) * A_size[0] - 1;
        rtDW->i3 = rtDW->k_b + rtDW->jBcol;
        if (B_data[rtDW->i3] != 0.0F) {
          B_data[rtDW->i3] /= A_data[rtDW->k_b + rtDW->kAcol];
          rtDW->i_d = rtDW->k_b + 1;
          while (rtDW->i_d <= rtDW->n_l) {
            tmp = rtDW->i_d + rtDW->jBcol;
            B_data[tmp] -= B_data[rtDW->i3] * A_data[rtDW->i_d + rtDW->kAcol];
            rtDW->i_d++;
          }
        }

        rtDW->k_b++;
      }

      rtDW->j_h++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
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
  rtDW->j_n = 0;
  while (rtDW->j_n <= B_size[1] - 1) {
    rtDW->i_b = 0;
    while (rtDW->i_b <= rtDW->y - 1) {
      C_data[rtDW->i_b + C_size[0] * rtDW->j_n] = (real32_T)B_data[rtDW->i_b +
        B_size[0] * rtDW->j_n];
      rtDW->i_b++;
    }

    rtDW->i_b = rtDW->y;
    while (rtDW->i_b + 1 <= A_size[1]) {
      C_data[rtDW->i_b + C_size[0] * rtDW->j_n] = 0.0F;
      rtDW->i_b++;
    }

    rtDW->j_n++;
  }

  trisolve(A_data, A_size, C_data, C_size, rtDW);
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void Unconstrained(const real32_T Hinv_data[], const int32_T Hinv_size[2],
  const real32_T f[4], real32_T x_data[], int16_T n, DW *rtDW)
{
  rtDW->i_o = 1;
  while (rtDW->i_o - 1 <= n - 1) {
    x_data[(int16_T)rtDW->i_o - 1] = ((-Hinv_data[(int16_T)rtDW->i_o - 1] * f[0]
      + -Hinv_data[((int16_T)rtDW->i_o + Hinv_size[0]) - 1] * f[1]) +
      -Hinv_data[((int16_T)rtDW->i_o + (Hinv_size[0] << 1)) - 1] * f[2]) +
      -Hinv_data[((int16_T)rtDW->i_o + Hinv_size[0] * 3) - 1] * f[3];
    rtDW->i_o++;
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static real32_T norm(const real32_T x_data[], const int32_T *x_size, DW *rtDW)
{
  real32_T y;
  if (*x_size == 0) {
    y = 0.0F;
  } else {
    y = 0.0F;
    if (*x_size == 1) {
      y = fabsf(x_data[0]);
    } else {
      rtDW->scale_b = 1.29246971E-26F;
      rtDW->k_a = 0;
      while (rtDW->k_a <= *x_size - 1) {
        rtDW->absxk_p = fabsf(x_data[rtDW->k_a]);
        if (rtDW->absxk_p > rtDW->scale_b) {
          rtDW->t_cv = rtDW->scale_b / rtDW->absxk_p;
          y = y * rtDW->t_cv * rtDW->t_cv + 1.0F;
          rtDW->scale_b = rtDW->absxk_p;
        } else {
          rtDW->t_cv = rtDW->absxk_p / rtDW->scale_b;
          y += rtDW->t_cv * rtDW->t_cv;
        }

        rtDW->k_a++;
      }

      y = rtDW->scale_b * sqrtf(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void abs_a(const real32_T x[4], real32_T y[4])
{
  y[0] = fabsf(x[0]);
  y[1] = fabsf(x[1]);
  y[2] = fabsf(x[2]);
  y[3] = fabsf(x[3]);
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
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

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void maximum2(const real32_T x[5], real32_T ex[5], DW *rtDW)
{
  for (rtDW->k_j = 0; rtDW->k_j < 5; rtDW->k_j++) {
    ex[rtDW->k_j] = fmaxf(x[rtDW->k_j], 1.0F);
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
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
      rtDW->k_e = ix0;
      while (rtDW->k_e <= rtDW->kend) {
        rtDW->absxk = fabsf(x_data[rtDW->k_e - 1]);
        if (rtDW->absxk > rtDW->scale) {
          rtDW->t_c = rtDW->scale / rtDW->absxk;
          y = y * rtDW->t_c * rtDW->t_c + 1.0F;
          rtDW->scale = rtDW->absxk;
        } else {
          rtDW->t_c = rtDW->absxk / rtDW->scale;
          y += rtDW->t_c * rtDW->t_c;
        }

        rtDW->k_e++;
      }

      y = rtDW->scale * sqrtf(y);
    }
  }

  return y;
}

static real32_T rt_hypotf_f(real32_T u0, real32_T u1, DW *rtDW)
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

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void xgemv(int32_T m, int32_T n, const real32_T A_data[], int32_T ia0,
                  int32_T lda, const real32_T x_data[], int32_T ix0, real32_T
                  y_data[], DW *rtDW)
{
  if (n != 0) {
    rtDW->b_iy_d = 0;
    while (rtDW->b_iy_d <= n - 1) {
      y_data[rtDW->b_iy_d] = 0.0F;
      rtDW->b_iy_d++;
    }

    rtDW->b_iy_d = 0;
    rtDW->b_l = (n - 1) * lda + ia0;
    rtDW->iac = ia0;
    while (((lda > 0) && (rtDW->iac <= rtDW->b_l)) || ((lda < 0) && (rtDW->iac >=
             rtDW->b_l))) {
      rtDW->ix_d = ix0;
      rtDW->c = 0.0F;
      rtDW->d_o = (rtDW->iac + m) - 1;
      rtDW->ia_b = rtDW->iac;
      while (rtDW->ia_b <= rtDW->d_o) {
        rtDW->c += A_data[rtDW->ia_b - 1] * x_data[rtDW->ix_d - 1];
        rtDW->ix_d++;
        rtDW->ia_b++;
      }

      y_data[rtDW->b_iy_d] += rtDW->c;
      rtDW->b_iy_d++;
      rtDW->iac += lda;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void xgerc(int32_T m, int32_T n, real32_T alpha1, int32_T ix0, const
                  real32_T y_data[], real32_T A_data[], int32_T ia0, int32_T lda,
                  DW *rtDW)
{
  if (alpha1 != 0.0F) {
    rtDW->jA = ia0 - 1;
    rtDW->jy = 0;
    rtDW->j_j = 0;
    while (rtDW->j_j <= n - 1) {
      if (y_data[rtDW->jy] != 0.0F) {
        rtDW->temp = y_data[rtDW->jy] * alpha1;
        rtDW->ix = ix0;
        rtDW->b_d = m + rtDW->jA;
        rtDW->ijA = rtDW->jA;
        while (rtDW->ijA + 1 <= rtDW->b_d) {
          A_data[rtDW->ijA] += A_data[rtDW->ix - 1] * rtDW->temp;
          rtDW->ix++;
          rtDW->ijA++;
        }
      }

      rtDW->jy++;
      rtDW->jA += lda;
      rtDW->j_j++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void xgeqrf(real32_T A_data[], const int32_T A_size[2], real32_T
                   tau_data[], int32_T *tau_size, DW *rtDW)
{
  int32_T exitg1;
  boolean_T exitg2;
  rtDW->m_p = A_size[0];
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

    rtDW->i_l = 0;
    while (rtDW->i_l <= rtDW->minmn - 1) {
      rtDW->ii = rtDW->i_l * rtDW->minmana + rtDW->i_l;
      rtDW->mmi = rtDW->m_p - rtDW->i_l;
      if (rtDW->i_l + 1 < rtDW->m_p) {
        rtDW->b_atmp = A_data[rtDW->ii];
        tau_data[rtDW->i_l] = 0.0F;
        if (rtDW->mmi > 0) {
          rtDW->beta1 = xnrm2(rtDW->mmi - 1, A_data, rtDW->ii + 2, rtDW);
          if (rtDW->beta1 != 0.0F) {
            rtDW->beta1 = rt_hypotf_f(A_data[rtDW->ii], rtDW->beta1, rtDW);
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

              rtDW->beta1 = rt_hypotf_f(rtDW->b_atmp, xnrm2(rtDW->mmi - 1,
                A_data, rtDW->ii + 2, rtDW), rtDW);
              if (rtDW->b_atmp >= 0.0F) {
                rtDW->beta1 = -rtDW->beta1;
              }

              tau_data[rtDW->i_l] = (rtDW->beta1 - rtDW->b_atmp) / rtDW->beta1;
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
              tau_data[rtDW->i_l] = (rtDW->beta1 - A_data[rtDW->ii]) /
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
        tau_data[rtDW->i_l] = 0.0F;
      }

      if (rtDW->i_l + 1 < rtDW->n) {
        rtDW->b_atmp = A_data[rtDW->ii];
        A_data[rtDW->ii] = 1.0F;
        rtDW->c_k = (rtDW->ii + rtDW->minmana) + 1;
        if (tau_data[rtDW->i_l] != 0.0F) {
          rtDW->mmip1 = (rtDW->ii + rtDW->mmi) - 1;
          while ((rtDW->mmi > 0) && (A_data[rtDW->mmip1] == 0.0F)) {
            rtDW->mmi--;
            rtDW->mmip1--;
          }

          rtDW->mmip1 = (rtDW->n - rtDW->i_l) - 1;
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
          xgerc(rtDW->mmi, rtDW->mmip1, -tau_data[rtDW->i_l], rtDW->ii + 1,
                rtDW->work_data, A_data, rtDW->c_k, rtDW->minmana, rtDW);
        }

        A_data[rtDW->ii] = rtDW->b_atmp;
      }

      rtDW->i_l++;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void xorgqr(int32_T m, int32_T n, int32_T k, real32_T A_data[], const
                   int32_T A_size[2], int32_T lda, const real32_T tau_data[], DW
                   *rtDW)
{
  int32_T exitg1;
  boolean_T exitg2;
  if (n >= 1) {
    rtDW->itau = k;
    while (rtDW->itau <= n - 1) {
      rtDW->i_gu = rtDW->itau * lda;
      rtDW->iaii = 0;
      while (rtDW->iaii <= m - 1) {
        A_data[rtDW->i_gu + rtDW->iaii] = 0.0F;
        rtDW->iaii++;
      }

      A_data[rtDW->i_gu + rtDW->itau] = 1.0F;
      rtDW->itau++;
    }

    rtDW->itau = k - 1;
    rtDW->iaii = (int8_T)A_size[1];
    if (0 <= rtDW->iaii - 1) {
      memset(&rtDW->work_data_c[0], 0, rtDW->iaii * sizeof(real32_T));
    }

    rtDW->i_gu = k;
    while (rtDW->i_gu >= 1) {
      rtDW->iaii = (rtDW->i_gu - 1) * lda + rtDW->i_gu;
      if (rtDW->i_gu < n) {
        A_data[rtDW->iaii - 1] = 1.0F;
        rtDW->lastc = (m - rtDW->i_gu) - 1;
        rtDW->c_c = rtDW->iaii + lda;
        if (tau_data[rtDW->itau] != 0.0F) {
          rtDW->lastv = rtDW->lastc + 2;
          rtDW->lastc += rtDW->iaii;
          while ((rtDW->lastv > 0) && (A_data[rtDW->lastc] == 0.0F)) {
            rtDW->lastv--;
            rtDW->lastc--;
          }

          rtDW->lastc = n - rtDW->i_gu;
          exitg2 = false;
          while ((!exitg2) && (rtDW->lastc > 0)) {
            rtDW->coltop = (rtDW->lastc - 1) * lda + rtDW->c_c;
            rtDW->ia_l = rtDW->coltop;
            do {
              exitg1 = 0;
              if (rtDW->ia_l <= (rtDW->coltop + rtDW->lastv) - 1) {
                if (A_data[rtDW->ia_l - 1] != 0.0F) {
                  exitg1 = 1;
                } else {
                  rtDW->ia_l++;
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
                rtDW->iaii, rtDW->work_data_c, rtDW);
          xgerc(rtDW->lastv, rtDW->lastc, -tau_data[rtDW->itau], rtDW->iaii,
                rtDW->work_data_c, A_data, rtDW->c_c, lda, rtDW);
        }
      }

      if (rtDW->i_gu < m) {
        rtDW->c_c = (rtDW->iaii + m) - rtDW->i_gu;
        rtDW->lastv = rtDW->iaii;
        while (rtDW->lastv + 1 <= rtDW->c_c) {
          A_data[rtDW->lastv] *= -tau_data[rtDW->itau];
          rtDW->lastv++;
        }
      }

      A_data[rtDW->iaii - 1] = 1.0F - tau_data[rtDW->itau];
      rtDW->c_c = 0;
      while (rtDW->c_c <= rtDW->i_gu - 2) {
        A_data[(rtDW->iaii - rtDW->c_c) - 2] = 0.0F;
        rtDW->c_c++;
      }

      rtDW->itau--;
      rtDW->i_gu--;
    }
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void mtimes(const real32_T A_data[], const int32_T A_size[2], const
                   real32_T B_0[4], real32_T C_data[], int32_T *C_size, DW *rtDW)
{
  rtDW->m_b = A_size[0] - 1;
  *C_size = A_size[0];
  rtDW->i_j = 0;
  while (rtDW->i_j <= rtDW->m_b) {
    C_data[rtDW->i_j] = 0.0F;
    rtDW->i_j++;
  }

  rtDW->i_j = 0;
  while (rtDW->i_j <= A_size[1] - 1) {
    rtDW->aoffset = rtDW->i_j * A_size[0];
    rtDW->b_i_f = 0;
    while (rtDW->b_i_f <= rtDW->m_b) {
      C_data[rtDW->b_i_f] += A_data[rtDW->aoffset + rtDW->b_i_f] * B_0[rtDW->i_j];
      rtDW->b_i_f++;
    }

    rtDW->i_j++;
  }
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static real32_T KWIKfactor(const int16_T iC[5], int16_T nA, const real32_T
  Linv_data[], const int32_T Linv_size[2], real32_T RLinv_data[], const int32_T
  RLinv_size[2], real32_T D_data[], const int32_T D_size[2], real32_T H_data[],
  const int32_T H_size[2], int16_T n, DW *rtDW)
{
  real32_T Status;
  int16_T c_k;
  static const int8_T Ac[20] = { 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
    0, 0, 1, 1 };

  int32_T exitg1;
  rtDW->TL_size_idx_0 = Linv_size[0];
  Status = 1.0F;
  rtDW->b_n = RLinv_size[0];
  rtDW->RLinv = RLinv_size[1];
  for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
    for (rtDW->m_n = 0; rtDW->m_n < rtDW->b_n; rtDW->m_n++) {
      RLinv_data[rtDW->m_n + RLinv_size[0] * rtDW->h_j] = 0.0F;
    }
  }

  rtDW->m_n = 1;
  while (rtDW->m_n - 1 <= nA - 1) {
    rtDW->h_j = iC[(int16_T)rtDW->m_n - 1];
    rtDW->Ac[0] = Ac[rtDW->h_j - 1];
    rtDW->Ac[1] = Ac[rtDW->h_j + 4];
    rtDW->Ac[2] = Ac[rtDW->h_j + 9];
    rtDW->Ac[3] = Ac[rtDW->h_j + 14];
    mtimes(Linv_data, Linv_size, rtDW->Ac, rtDW->tau_data, &rtDW->tau_size, rtDW);
    rtDW->RLinv = rtDW->tau_size;
    for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
      RLinv_data[rtDW->h_j + RLinv_size[0] * ((int16_T)rtDW->m_n - 1)] =
        rtDW->tau_data[rtDW->h_j];
    }

    rtDW->m_n++;
  }

  rtDW->m_n = RLinv_size[0] - 1;
  rtDW->b_n = RLinv_size[1];
  rtDW->Q_size[0] = (int8_T)RLinv_size[0];
  rtDW->Q_size[1] = (int8_T)RLinv_size[0];
  rtDW->R_size_idx_0 = RLinv_size[0];
  if (RLinv_size[0] > RLinv_size[1]) {
    rtDW->h_j = 0;
    while (rtDW->h_j <= rtDW->b_n - 1) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m_n) {
        rtDW->Q_data[rtDW->RLinv + rtDW->Q_size[0] * rtDW->h_j] =
          RLinv_data[rtDW->RLinv + RLinv_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    rtDW->h_j = RLinv_size[1];
    while (rtDW->h_j + 1 <= rtDW->m_n + 1) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m_n) {
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
      while (rtDW->RLinv + 1 <= rtDW->m_n + 1) {
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
    while (rtDW->h_j <= rtDW->m_n) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->h_j) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] =
          rtDW->A_data[rtDW->RLinv + rtDW->A_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->RLinv = rtDW->h_j + 1;
      while (rtDW->RLinv + 1 <= rtDW->m_n + 1) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] = 0.0F;
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    rtDW->h_j = RLinv_size[0];
    while (rtDW->h_j + 1 <= rtDW->b_n) {
      rtDW->RLinv = 0;
      while (rtDW->RLinv <= rtDW->m_n) {
        rtDW->R_data[rtDW->RLinv + rtDW->R_size_idx_0 * rtDW->h_j] =
          rtDW->A_data[rtDW->RLinv + rtDW->A_size[0] * rtDW->h_j];
        rtDW->RLinv++;
      }

      rtDW->h_j++;
    }

    xorgqr(RLinv_size[0], RLinv_size[0], RLinv_size[0], rtDW->A_data,
           rtDW->A_size, RLinv_size[0], rtDW->tau_data, rtDW);
    rtDW->b_n = 0;
    while (rtDW->b_n <= rtDW->m_n) {
      rtDW->h_j = 0;
      while (rtDW->h_j <= rtDW->m_n) {
        rtDW->Q_data[rtDW->h_j + rtDW->Q_size[0] * rtDW->b_n] = rtDW->
          A_data[rtDW->h_j + rtDW->A_size[0] * rtDW->b_n];
        rtDW->h_j++;
      }

      rtDW->b_n++;
    }
  }

  rtDW->m_n = 1;
  do {
    exitg1 = 0;
    if (rtDW->m_n - 1 <= nA - 1) {
      if (fabsf(rtDW->R_data[((int16_T)rtDW->m_n + rtDW->R_size_idx_0 *
                              ((int16_T)rtDW->m_n - 1)) - 1]) < 1.0E-12F) {
        Status = -2.0F;
        exitg1 = 1;
      } else {
        rtDW->m_n++;
      }
    } else {
      rtDW->m_n = 1;
      while (rtDW->m_n - 1 <= n - 1) {
        rtDW->b_n = 1;
        while (rtDW->b_n - 1 <= n - 1) {
          rtDW->RLinv = Linv_size[0];
          rtDW->Linv = 0.0F;
          for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
            rtDW->Linv += Linv_data[rtDW->h_j + Linv_size[0] * ((int16_T)
              rtDW->m_n - 1)] * rtDW->Q_data[rtDW->h_j + rtDW->Q_size[0] *
              ((int16_T)rtDW->b_n - 1)];
          }

          rtDW->TL_data[((int16_T)rtDW->m_n + rtDW->TL_size_idx_0 * ((int16_T)
            rtDW->b_n - 1)) - 1] = rtDW->Linv;
          rtDW->b_n++;
        }

        rtDW->m_n++;
      }

      rtDW->b_n = RLinv_size[0];
      rtDW->RLinv = RLinv_size[1];
      for (rtDW->h_j = 0; rtDW->h_j < rtDW->RLinv; rtDW->h_j++) {
        for (rtDW->m_n = 0; rtDW->m_n < rtDW->b_n; rtDW->m_n++) {
          RLinv_data[rtDW->m_n + RLinv_size[0] * rtDW->h_j] = 0.0F;
        }
      }

      rtDW->b_j = nA;
      while (rtDW->b_j > 0) {
        RLinv_data[(rtDW->b_j + RLinv_size[0] * (rtDW->b_j - 1)) - 1] = 1.0F;
        for (c_k = rtDW->b_j; c_k <= nA; c_k++) {
          rtDW->RLinv = (rtDW->b_j + RLinv_size[0] * (c_k - 1)) - 1;
          RLinv_data[rtDW->RLinv] /= rtDW->R_data[(rtDW->b_j +
            rtDW->R_size_idx_0 * (rtDW->b_j - 1)) - 1];
        }

        if (rtDW->b_j > 1) {
          rtDW->m_n = 1;
          while (rtDW->m_n - 1 <= rtDW->b_j - 2) {
            for (c_k = rtDW->b_j; c_k <= nA; c_k++) {
              rtDW->RLinv = RLinv_size[0] * (c_k - 1);
              rtDW->h_j = ((int16_T)rtDW->m_n + rtDW->RLinv) - 1;
              RLinv_data[rtDW->h_j] -= rtDW->R_data[((int16_T)rtDW->m_n +
                rtDW->R_size_idx_0 * (rtDW->b_j - 1)) - 1] * RLinv_data
                [(rtDW->b_j + rtDW->RLinv) - 1];
            }

            rtDW->m_n++;
          }
        }

        rtDW->b_j--;
      }

      rtDW->m_n = 1;
      while (rtDW->m_n - 1 <= n - 1) {
        rtDW->b_j = (int16_T)rtDW->m_n;
        while (rtDW->b_j <= n) {
          rtDW->RLinv = ((int16_T)rtDW->m_n + H_size[0] * (rtDW->b_j - 1)) - 1;
          H_data[rtDW->RLinv] = 0.0F;
          rtDW->h_j = nA + 1;
          if (nA + 1 > 32767) {
            rtDW->h_j = 32767;
          }

          for (c_k = (int16_T)rtDW->h_j; c_k <= n; c_k++) {
            rtDW->h_j = rtDW->TL_size_idx_0 * (c_k - 1);
            H_data[rtDW->RLinv] -= rtDW->TL_data[((int16_T)rtDW->m_n + rtDW->h_j)
              - 1] * rtDW->TL_data[(rtDW->b_j + rtDW->h_j) - 1];
          }

          H_data[(rtDW->b_j + H_size[0] * ((int16_T)rtDW->m_n - 1)) - 1] =
            H_data[rtDW->RLinv];
          rtDW->b_j++;
        }

        rtDW->m_n++;
      }

      rtDW->m_n = 1;
      while (rtDW->m_n - 1 <= nA - 1) {
        rtDW->b_n = 1;
        while (rtDW->b_n - 1 <= n - 1) {
          rtDW->RLinv = ((int16_T)rtDW->b_n + D_size[0] * ((int16_T)rtDW->m_n -
            1)) - 1;
          D_data[rtDW->RLinv] = 0.0F;
          rtDW->b_j = (int16_T)rtDW->m_n;
          while (rtDW->b_j <= nA) {
            D_data[rtDW->RLinv] += rtDW->TL_data[((int16_T)rtDW->b_n +
              rtDW->TL_size_idx_0 * (rtDW->b_j - 1)) - 1] * RLinv_data[((int16_T)
              rtDW->m_n + RLinv_size[0] * (rtDW->b_j - 1)) - 1];
            rtDW->b_j++;
          }

          rtDW->b_n++;
        }

        rtDW->m_n++;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static real32_T mtimes_g(const real32_T A_data[], const real32_T B_1[4])
{
  return ((A_data[0] * B_1[0] + A_data[1] * B_1[1]) + A_data[2] * B_1[2]) +
    A_data[3] * B_1[3];
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void DropConstraint(int16_T kDrop, int16_T iA[5], int16_T *nA, int16_T
  iC[5], DW *rtDW)
{
  int16_T i;
  iA[iC[kDrop - 1] - 1] = 0;
  if (kDrop < *nA) {
    rtDW->i4 = *nA - 1;
    if (*nA - 1 < -32768) {
      rtDW->i4 = -32768;
    }

    for (i = kDrop; i <= (int16_T)rtDW->i4; i++) {
      iC[i - 1] = iC[i];
    }
  }

  iC[*nA - 1] = 0;
  rtDW->i4 = *nA - 1;
  if (*nA - 1 < -32768) {
    rtDW->i4 = -32768;
  }

  *nA = (int16_T)rtDW->i4;
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void ResetToColdStart(int16_T iA[5], int16_T iC[5], DW *rtDW)
{
  for (rtDW->i_ju = 0; rtDW->i_ju < 5; rtDW->i_ju++) {
    iA[rtDW->i_ju] = 0;
    iC[rtDW->i_ju] = 0;
  }

  iA[4] = 1;
  iC[0] = 5;
}

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void qpkwik(const real32_T Linv_data[], const int32_T Linv_size[2], const
                   real32_T Hinv_data[], const int32_T Hinv_size[2], const
                   real32_T f[4], int16_T maxiter, int16_T n, real32_T x_data[],
                   int32_T *x_size, real32_T lambda[5], real32_T *status,
                   int16_T iA[5], DW *rtDW)
{
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
  for (rtDW->i_g = 0; rtDW->i_g < 5; rtDW->i_g++) {
    iA[rtDW->i_g] = h[rtDW->i_g];
    lambda[rtDW->i_g] = 0.0F;
  }

  *x_size = n;
  rtDW->loop_ub_m = n;
  if (0 <= rtDW->loop_ub_m - 1) {
    memset(&x_data[0], 0, rtDW->loop_ub_m * sizeof(real32_T));
  }

  rtDW->loop_ub_m = n;
  if (0 <= rtDW->loop_ub_m - 1) {
    memset(&rtDW->r_data[0], 0, rtDW->loop_ub_m * sizeof(real32_T));
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
  for (rtDW->i_g = 0; rtDW->i_g < 5; rtDW->i_g++) {
    rtDW->cTol[rtDW->i_g] = 1.0F;
    rtDW->iC[rtDW->i_g] = 0;
  }

  rtDW->nA = 0;
  for (rtDW->i_g = 0; rtDW->i_g < 5; rtDW->i_g++) {
    if (iA[rtDW->i_g] == 1) {
      rtDW->lambda_tmp_tmp = rtDW->nA + 1;
      if (rtDW->nA + 1 > 32767) {
        rtDW->lambda_tmp_tmp = 32767;
      }

      rtDW->nA = (int16_T)rtDW->lambda_tmp_tmp;
      rtDW->iC[(int16_T)rtDW->lambda_tmp_tmp - 1] = (int16_T)(rtDW->i_g + 1);
    }
  }

  guard1 = false;
  if (rtDW->nA > 0) {
    if (n > 16383) {
      rtDW->i6 = MAX_int16_T;
    } else if (n <= -16384) {
      rtDW->i6 = MIN_int16_T;
    } else {
      rtDW->i6 = (int16_T)(n << 1);
    }

    rtDW->i_g = rtDW->i6;
    if (0 <= rtDW->i_g - 1) {
      memset(&rtDW->Opt_data[0], 0, rtDW->i_g * sizeof(real32_T));
    }

    rtDW->Rhs_data[0] = f[0];
    rtDW->Rhs_data[1] = f[1];
    rtDW->Rhs_data[2] = f[2];
    rtDW->Rhs_data[3] = f[3];
    rtDW->loop_ub_m = n;
    if (0 <= rtDW->loop_ub_m - 1) {
      memset(&rtDW->Rhs_data[4], 0, rtDW->loop_ub_m * sizeof(real32_T));
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
            ResetToColdStart(iA, rtDW->iC, rtDW);
            rtDW->nA = 1;
            ColdReset = true;
          }
        } else {
          rtDW->i_g = 1;
          while (rtDW->i_g - 1 <= rtDW->nA - 1) {
            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_g;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->lambda_tmp_tmp = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->lambda_tmp_tmp = -32768;
            }

            rtDW->Rhs_data[rtDW->lambda_tmp_tmp - 1] = h[rtDW->iC[(int16_T)
              rtDW->i_g - 1] - 1];
            rtDW->kNext = (int16_T)rtDW->i_g;
            while (rtDW->kNext <= rtDW->nA) {
              rtDW->lambda_tmp_tmp = (rtDW->kNext + rtDW->U_size[0] * ((int16_T)
                rtDW->i_g - 1)) - 1;
              rtDW->U_data[rtDW->lambda_tmp_tmp] = 0.0F;
              rtDW->H_g = 1;
              while (rtDW->H_g - 1 <= rtDW->nA - 1) {
                rtDW->loop_ub_m = rtDW->RLinv_size[0] * ((int16_T)rtDW->H_g - 1);
                rtDW->U_data[rtDW->lambda_tmp_tmp] += rtDW->RLinv_data
                  [(rtDW->kNext + rtDW->loop_ub_m) - 1] * rtDW->RLinv_data
                  [((int16_T)rtDW->i_g + rtDW->loop_ub_m) - 1];
                rtDW->H_g++;
              }

              rtDW->U_data[((int16_T)rtDW->i_g + rtDW->U_size[0] * (rtDW->kNext
                - 1)) - 1] = rtDW->U_data[rtDW->lambda_tmp_tmp];
              rtDW->kNext++;
            }

            rtDW->i_g++;
          }

          rtDW->i_g = 1;
          while (rtDW->i_g - 1 <= n - 1) {
            rtDW->loop_ub_m = rtDW->H_size[1];
            rtDW->Xnorm0 = 0.0F;
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                 rtDW->loop_ub_m; rtDW->lambda_tmp_tmp++) {
              rtDW->Xnorm0 += rtDW->H_data[((int16_T)rtDW->i_g + rtDW->H_size[0]
                * rtDW->lambda_tmp_tmp) - 1] * rtDW->Rhs_data
                [rtDW->lambda_tmp_tmp];
            }

            rtDW->Opt_data[(int16_T)rtDW->i_g - 1] = rtDW->Xnorm0;
            rtDW->H_g = 1;
            while (rtDW->H_g - 1 <= rtDW->nA - 1) {
              rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->H_g;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->lambda_tmp_tmp = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->lambda_tmp_tmp = -32768;
              }

              rtDW->Opt_data[(int16_T)rtDW->i_g - 1] += rtDW->D_data[((int16_T)
                rtDW->i_g + rtDW->D_size[0] * ((int16_T)rtDW->H_g - 1)) - 1] *
                rtDW->Rhs_data[rtDW->lambda_tmp_tmp - 1];
              rtDW->H_g++;
            }

            rtDW->i_g++;
          }

          rtDW->i_g = 1;
          while (rtDW->i_g - 1 <= rtDW->nA - 1) {
            rtDW->loop_ub_m = rtDW->D_size[0];
            rtDW->Xnorm0 = 0.0F;
            for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                 rtDW->loop_ub_m; rtDW->lambda_tmp_tmp++) {
              rtDW->Xnorm0 += rtDW->D_data[rtDW->lambda_tmp_tmp + rtDW->D_size[0]
                * ((int16_T)rtDW->i_g - 1)] * rtDW->Rhs_data
                [rtDW->lambda_tmp_tmp];
            }

            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_g;
            rtDW->loop_ub_m = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub_m = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub_m = -32768;
            }

            rtDW->Opt_data[rtDW->loop_ub_m - 1] = rtDW->Xnorm0;
            rtDW->H_g = 1;
            while (rtDW->H_g - 1 <= rtDW->nA - 1) {
              rtDW->loop_ub_m = rtDW->lambda_tmp_tmp;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->loop_ub_m = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->loop_ub_m = -32768;
              }

              rtDW->i1 = rtDW->lambda_tmp_tmp;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->i1 = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->i1 = -32768;
              }

              rtDW->i2 = n + (int16_T)rtDW->H_g;
              if (rtDW->i2 > 32767) {
                rtDW->i2 = 32767;
              } else if (rtDW->i2 < -32768) {
                rtDW->i2 = -32768;
              }

              rtDW->Opt_data[rtDW->loop_ub_m - 1] = rtDW->U_data[((int16_T)
                rtDW->i_g + rtDW->U_size[0] * ((int16_T)rtDW->H_g - 1)) - 1] *
                rtDW->Rhs_data[rtDW->i2 - 1] + rtDW->Opt_data[rtDW->i1 - 1];
              rtDW->H_g++;
            }

            rtDW->i_g++;
          }

          rtDW->Xnorm0 = -1.0E-12F;
          rtDW->kDrop = 0;
          rtDW->i_g = 1;
          while (rtDW->i_g - 1 <= rtDW->nA - 1) {
            rtDW->lambda_tmp_tmp = n + (int16_T)rtDW->i_g;
            rtDW->loop_ub_m = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub_m = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub_m = -32768;
            }

            lambda[rtDW->iC[(int16_T)rtDW->i_g - 1] - 1] = rtDW->Opt_data
              [rtDW->loop_ub_m - 1];
            rtDW->loop_ub_m = rtDW->lambda_tmp_tmp;
            if (rtDW->lambda_tmp_tmp > 32767) {
              rtDW->loop_ub_m = 32767;
            } else if (rtDW->lambda_tmp_tmp < -32768) {
              rtDW->loop_ub_m = -32768;
            }

            if ((rtDW->Opt_data[rtDW->loop_ub_m - 1] < rtDW->Xnorm0) &&
                ((int16_T)rtDW->i_g <= rtDW->nA - 1)) {
              rtDW->kDrop = (int16_T)rtDW->i_g;
              if (rtDW->lambda_tmp_tmp > 32767) {
                rtDW->lambda_tmp_tmp = 32767;
              } else if (rtDW->lambda_tmp_tmp < -32768) {
                rtDW->lambda_tmp_tmp = -32768;
              }

              rtDW->Xnorm0 = rtDW->Opt_data[rtDW->lambda_tmp_tmp - 1];
            }

            rtDW->i_g++;
          }

          if (rtDW->kDrop <= 0) {
            DualFeasible = true;
            if (1 > n) {
              rtDW->loop_ub_m = -1;
            } else {
              rtDW->loop_ub_m = n - 1;
            }

            *x_size = rtDW->loop_ub_m + 1;
            if (0 <= rtDW->loop_ub_m) {
              memcpy(&x_data[0], &rtDW->Opt_data[0], (rtDW->loop_ub_m + 1) *
                     sizeof(real32_T));
            }
          } else {
            (*status)++;
            if (*status > 5.0F) {
              ResetToColdStart(iA, rtDW->iC, rtDW);
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
          for (rtDW->i_g = 0; rtDW->i_g < 5; rtDW->i_g++) {
            lambda[rtDW->i_g] = 0.0F;
          }

          Unconstrained(Hinv_data, Hinv_size, f, x_data, n, rtDW);
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    Unconstrained(Hinv_data, Hinv_size, f, x_data, n, rtDW);
    guard1 = true;
  }

  if (guard1) {
    rtDW->Xnorm0 = norm(x_data, x_size, rtDW);
    exitg2 = false;
    while ((!exitg2) && ((int32_T)*status <= maxiter)) {
      rtDW->cMin = -1.0E-6F;
      rtDW->kNext = 0;
      for (rtDW->i_g = 0; rtDW->i_g < 4; rtDW->i_g++) {
        rtDW->t = rtDW->cTol[rtDW->i_g];
        if (!cTolComputed) {
          rtDW->AcRow[0] = (real32_T)Ac[rtDW->i_g] * x_data[0];
          rtDW->AcRow[1] = (real32_T)Ac[rtDW->i_g + 5] * x_data[1];
          rtDW->AcRow[2] = (real32_T)Ac[rtDW->i_g + 10] * x_data[2];
          rtDW->AcRow[3] = (real32_T)Ac[rtDW->i_g + 15] * x_data[3];
          abs_a(rtDW->AcRow, rtDW->z_data);
          rtDW->t = fmaxf(rtDW->t, maximum(rtDW->z_data));
        }

        if (iA[rtDW->i_g] == 0) {
          rtDW->cVal = ((((real32_T)Ac[rtDW->i_g] * x_data[0] + (real32_T)
                          Ac[rtDW->i_g + 5] * x_data[1]) + (real32_T)Ac
                         [rtDW->i_g + 10] * x_data[2]) + (real32_T)Ac[rtDW->i_g
                        + 15] * x_data[3]) / rtDW->t;
          if (rtDW->cVal < rtDW->cMin) {
            rtDW->cMin = rtDW->cVal;
            rtDW->kNext = (int16_T)(rtDW->i_g + 1);
          }
        }

        rtDW->cTol[rtDW->i_g] = rtDW->t;
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
                rtDW->loop_ub_m = rtDW->H_size[0] * rtDW->H_size[1];
                for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                     rtDW->loop_ub_m; rtDW->lambda_tmp_tmp++) {
                  rtDW->U_data[rtDW->lambda_tmp_tmp] = -rtDW->H_data
                    [rtDW->lambda_tmp_tmp];
                }

                mtimes(rtDW->U_data, rtDW->U_size, rtDW->AcRow, rtDW->z_data,
                       &rtDW->z_size, rtDW);
                rtDW->i_g = 1;
                while (rtDW->i_g - 1 <= rtDW->nA - 1) {
                  rtDW->lambda_tmp_tmp = rtDW->D_size[0] * ((int16_T)rtDW->i_g -
                    1);
                  rtDW->r_data[(int16_T)rtDW->i_g - 1] = ((rtDW->D_data
                    [rtDW->lambda_tmp_tmp] * rtDW->AcRow[0] + rtDW->D_data[1 +
                    rtDW->lambda_tmp_tmp] * rtDW->AcRow[1]) + rtDW->D_data[2 +
                    rtDW->lambda_tmp_tmp] * rtDW->AcRow[2]) + rtDW->D_data[3 +
                    rtDW->lambda_tmp_tmp] * rtDW->AcRow[3];
                  rtDW->i_g++;
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
                rtDW->i_g = 0;
                exitg4 = false;
                while ((!exitg4) && (rtDW->i_g <= rtDW->nA - 2)) {
                  if (rtDW->r_data[rtDW->i_g] >= 1.0E-12F) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    rtDW->i_g++;
                  }
                }
              }

              if ((rtDW->nA != 1) && (!ColdReset)) {
                rtDW->lambda_tmp_tmp = rtDW->nA - 1;
                if (rtDW->nA - 1 < -32768) {
                  rtDW->lambda_tmp_tmp = -32768;
                }

                rtDW->i_g = 1;
                while (rtDW->i_g - 1 <= (int16_T)rtDW->lambda_tmp_tmp - 1) {
                  rtDW->cVal = rtDW->r_data[(int16_T)rtDW->i_g - 1];
                  if (rtDW->cVal > 1.0E-12F) {
                    rtDW->cVal = lambda[rtDW->iC[(int16_T)rtDW->i_g - 1] - 1] /
                      rtDW->cVal;
                    if ((rtDW->kDrop == 0) || (rtDW->cVal < rtDW->rMin)) {
                      rtDW->rMin = rtDW->cVal;
                      rtDW->kDrop = (int16_T)rtDW->i_g;
                    }
                  }

                  rtDW->i_g++;
                }

                if (rtDW->kDrop > 0) {
                  rtDW->cMin = rtDW->rMin;
                  DualFeasible = false;
                }
              }

              rtDW->cVal = mtimes_g(rtDW->z_data, rtDW->AcRow);
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

                rtDW->i_g = 1;
                while (rtDW->i_g - 1 <= rtDW->nA - 1) {
                  rtDW->lambda_tmp_tmp = rtDW->iC[(int16_T)rtDW->i_g - 1];
                  lambda[rtDW->lambda_tmp_tmp - 1] -= rtDW->r_data[(int16_T)
                    rtDW->i_g - 1] * rtDW->t;
                  if ((rtDW->lambda_tmp_tmp <= 4) && (lambda
                       [rtDW->lambda_tmp_tmp - 1] < 0.0F)) {
                    lambda[rtDW->lambda_tmp_tmp - 1] = 0.0F;
                  }

                  rtDW->i_g++;
                }

                lambda[rtDW->kNext - 1] += rtDW->t;
                if (rtDW->t == rtDW->cMin) {
                  DropConstraint(rtDW->kDrop, iA, &rtDW->nA, rtDW->iC, rtDW);
                }

                if (!ColdReset) {
                  rtDW->loop_ub_m = *x_size;
                  for (rtDW->lambda_tmp_tmp = 0; rtDW->lambda_tmp_tmp <
                       rtDW->loop_ub_m; rtDW->lambda_tmp_tmp++) {
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
                        rtDW->i6 = rtDW->iC[rtDW->kDrop - 1];
                        rtDW->i7 = rtDW->iC[rtDW->kDrop - 2];
                        if (rtDW->i6 > rtDW->i7) {
                          exitg4 = true;
                        } else {
                          rtDW->iC[rtDW->kDrop - 1] = rtDW->i7;
                          rtDW->iC[rtDW->kDrop - 2] = rtDW->i6;
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
              maximum2(varargin_1, rtDW->cTol, rtDW);
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

/* Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
static void mpcActiveSetSolver(const real32_T H_data[], const int32_T H_size[2],
  const real32_T f[4], real32_T options_MaxIterations, real32_T x_data[],
  int32_T *x_size, real32_T *exitflag, DW *rtDW)
{
  rtDW->m = H_size[1];
  rtDW->Hinv_size[0] = H_size[1];
  rtDW->Hinv_size[1] = H_size[1];
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
        rtDW->i_f = rtDW->coffset + rtDW->b_i;
        rtDW->Hinv_data[rtDW->i_f] += H_data[rtDW->b_i * H_size[0] + rtDW->i] *
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
      rtDW->i5 = (int16_T)rtDW->bkj;
    } else {
      rtDW->i5 = MIN_int16_T;
    }
  } else {
    rtDW->i5 = MAX_int16_T;
  }

  qpkwik(H_data, H_size, rtDW->Hinv_data, rtDW->Hinv_size, f, rtDW->i5, (int16_T)
         H_size[0], x_data, x_size, rtDW->lam, exitflag, rtDW->iA1, rtDW);
}

/* Model step function */
void impl_modul_mpc_allQP_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  boolean_T rtb_unsuited;
  boolean_T rtb_unsuited_a;
  boolean_T rtb_unsuited_g;
  boolean_T rtb_unsuited_h;
  boolean_T rtb_unsuited_k;
  boolean_T rtb_unsuited_l;
  static const int8_T a[12] = { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0 };

  static const int8_T seq_order_table[18] = { 1, 2, 3, 3, 2, 1, 2, 1, 1, 2, 3, 3,
    3, 3, 2, 1, 1, 2 };

  /* Trigonometry: '<S1>/SinCos1' incorporates:
   *  Inport: '<Root>/theta_el'
   */
  rtDW->SinCos1_o1 = sinf(rtU->theta_el);
  rtDW->SinCos1_o2 = cosf(rtU->theta_el);

  /* MATLAB Function: '<S1>/state_space_mdl_1' incorporates:
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/v_DC_pu'
   *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
   */
  /* MATLAB Function 'impl_modul_mpc_allQP/seq_2_act_sw_all': '<S17>:1' */
  /* '<S17>:1:3' act_sw_1 = single(zeros(6,1)); */
  /* '<S17>:1:4' act_sw_2 = single(zeros(6,1)); */
  /*  columns=sequence, rows=active switch postion              */
  /* '<S17>:1:6' sequence_table = single([1 3;  */
  /* '<S17>:1:7'                   2 3; */
  /* '<S17>:1:8'                   2 6; */
  /* '<S17>:1:9'                   4 6; */
  /* '<S17>:1:10'                   4 5; */
  /* '<S17>:1:11'                   1 5]); */
  /* '<S17>:1:13' act_sw_1(1) = sequence_table(1,1); */
  /* '<S17>:1:14' act_sw_2(1) = sequence_table(1,2); */
  /* '<S17>:1:15' act_sw_1(2) = sequence_table(2,1); */
  /* '<S17>:1:16' act_sw_2(2) = sequence_table(2,2); */
  /* '<S17>:1:17' act_sw_1(3) = sequence_table(3,1); */
  /* '<S17>:1:18' act_sw_2(3) = sequence_table(3,2); */
  /* '<S17>:1:19' act_sw_1(4) = sequence_table(4,1); */
  /* '<S17>:1:20' act_sw_2(4) = sequence_table(4,2); */
  /* '<S17>:1:21' act_sw_1(5) = sequence_table(5,1); */
  /* '<S17>:1:22' act_sw_2(5) = sequence_table(5,2); */
  /* '<S17>:1:23' act_sw_1(6) = sequence_table(6,1); */
  /* '<S17>:1:24' act_sw_2(6) = sequence_table(6,2); */
  /* MATLAB Function 'impl_modul_mpc_allQP/act_sw_2_dq_volts_all': '<S2>:1' */
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
  /* '<S2>:1:17' vq_1_pu(1) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(1),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(1),2) * cos_angle); */
  /* '<S2>:1:19' vd_2_pu(1) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(1),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(1),2) * sin_angle); */
  /* '<S2>:1:20' vq_2_pu(1) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(1),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(1),2) * cos_angle); */
  /* '<S2>:1:23' vd_1_pu(2) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(2),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(2),2) * sin_angle); */
  /* '<S2>:1:24' vq_1_pu(2) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(2),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(2),2) * cos_angle); */
  /* '<S2>:1:26' vd_2_pu(2) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(2),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(2),2) * sin_angle); */
  /* '<S2>:1:27' vq_2_pu(2) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(2),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(2),2) * cos_angle); */
  /* '<S2>:1:30' vd_1_pu(3) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(3),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(3),2) * sin_angle); */
  /* '<S2>:1:31' vq_1_pu(3) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(3),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(3),2) * cos_angle); */
  /* '<S2>:1:33' vd_2_pu(3) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(3),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(3),2) * sin_angle); */
  /* '<S2>:1:34' vq_2_pu(3) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(3),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(3),2) * cos_angle); */
  /* '<S2>:1:37' vd_1_pu(4) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(4),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(4),2) * sin_angle); */
  /* '<S2>:1:38' vq_1_pu(4) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(4),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(4),2) * cos_angle); */
  /* '<S2>:1:40' vd_2_pu(4) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(4),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(4),2) * sin_angle); */
  /* '<S2>:1:41' vq_2_pu(4) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(4),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(4),2) * cos_angle); */
  /* '<S2>:1:44' vd_1_pu(5) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(5),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(5),2) * sin_angle); */
  /* '<S2>:1:45' vq_1_pu(5) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(5),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(5),2) * cos_angle); */
  /* '<S2>:1:47' vd_2_pu(5) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(5),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(5),2) * sin_angle); */
  /* '<S2>:1:48' vq_2_pu(5) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(5),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(5),2) * cos_angle); */
  /* '<S2>:1:51' vd_1_pu(6) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(6),1) *  cos_angle + v_alpha_beta_pu(act_sw_1(6),2) * sin_angle); */
  /* '<S2>:1:52' vq_1_pu(6) = v_DC_pu * (v_alpha_beta_pu(act_sw_1(6),1) * -sin_angle + v_alpha_beta_pu(act_sw_1(6),2) * cos_angle); */
  /* '<S2>:1:54' vd_2_pu(6) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(6),1) *  cos_angle + v_alpha_beta_pu(act_sw_2(6),2) * sin_angle); */
  /* '<S2>:1:55' vq_2_pu(6) = v_DC_pu * (v_alpha_beta_pu(act_sw_2(6),1) * -sin_angle + v_alpha_beta_pu(act_sw_2(6),2) * cos_angle); */
  state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                    rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                    rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                    rtU->omega_el_pu, rtU->v_DC_pu * (0.666666687F *
    rtDW->SinCos1_o2), rtU->v_DC_pu * (0.666666687F * -rtDW->SinCos1_o1),
                    rtU->v_DC_pu * (0.333333343F * rtDW->SinCos1_o2 +
    0.577350259F * rtDW->SinCos1_o1), rtU->v_DC_pu * (0.333333343F *
    -rtDW->SinCos1_o1 + 0.577350259F * rtDW->SinCos1_o2), rtDW->m3, rtDW->m2,
                    rtDW->m1, rtDW->m0, &rtDW->sf_state_space_mdl_1);

  /* MATLAB Function: '<S1>/formulate_qp_1' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/lambda'
   */
  formulate_qp_1(rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0, rtU->i_dq_pu[0],
                 rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu, rtU->lambda,
                 rtDW->H_k4, rtDW->f_a, rtDW->M_n, rtDW->r_bc,
                 &rtDW->sf_formulate_qp_1);

  /* MATLAB Function: '<S1>/state_space_mdl_2' incorporates:
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/v_DC_pu'
   *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
   */
  state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                    rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                    rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                    rtU->omega_el_pu, rtU->v_DC_pu * (-0.333333343F *
    rtDW->SinCos1_o2 + 0.577350259F * rtDW->SinCos1_o1), rtU->v_DC_pu *
                    (-0.333333343F * -rtDW->SinCos1_o1 + 0.577350259F *
                     rtDW->SinCos1_o2), rtU->v_DC_pu * (0.333333343F *
    rtDW->SinCos1_o2 + 0.577350259F * rtDW->SinCos1_o1), rtU->v_DC_pu *
                    (0.333333343F * -rtDW->SinCos1_o1 + 0.577350259F *
                     rtDW->SinCos1_o2), rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0,
                    &rtDW->sf_state_space_mdl_2);

  /* MATLAB Function: '<S1>/formulate_qp_2' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/lambda'
   */
  formulate_qp_1(rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0, rtU->i_dq_pu[0],
                 rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu, rtU->lambda,
                 rtDW->H_j, rtDW->f_ej, rtDW->M_eb, rtDW->r_eo,
                 &rtDW->sf_formulate_qp_2);

  /* MATLAB Function: '<S1>/state_space_mdl_3' incorporates:
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/v_DC_pu'
   *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
   */
  state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                    rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                    rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                    rtU->omega_el_pu, rtU->v_DC_pu * (-0.333333343F *
    rtDW->SinCos1_o2 + 0.577350259F * rtDW->SinCos1_o1), rtU->v_DC_pu *
                    (-0.333333343F * -rtDW->SinCos1_o1 + 0.577350259F *
                     rtDW->SinCos1_o2), rtU->v_DC_pu * (-0.666666687F *
    rtDW->SinCos1_o2), rtU->v_DC_pu * (-0.666666687F * -rtDW->SinCos1_o1),
                    rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0,
                    &rtDW->sf_state_space_mdl_3);

  /* MATLAB Function: '<S1>/formulate_qp_3' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/lambda'
   */
  formulate_qp_1(rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0, rtU->i_dq_pu[0],
                 rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu, rtU->lambda,
                 rtDW->H_o, rtDW->f_n, rtDW->M_e, rtDW->r_m,
                 &rtDW->sf_formulate_qp_3);

  /* MATLAB Function: '<S1>/state_space_mdl_4' incorporates:
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/v_DC_pu'
   *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
   */
  state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                    rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                    rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                    rtU->omega_el_pu, rtU->v_DC_pu * (-0.333333343F *
    rtDW->SinCos1_o2 + -0.577350259F * rtDW->SinCos1_o1), rtU->v_DC_pu *
                    (-0.333333343F * -rtDW->SinCos1_o1 + -0.577350259F *
                     rtDW->SinCos1_o2), rtU->v_DC_pu * (-0.666666687F *
    rtDW->SinCos1_o2), rtU->v_DC_pu * (-0.666666687F * -rtDW->SinCos1_o1),
                    rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0,
                    &rtDW->sf_state_space_mdl_4);

  /* MATLAB Function: '<S1>/formulate_qp_4' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/lambda'
   */
  formulate_qp_1(rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0, rtU->i_dq_pu[0],
                 rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu, rtU->lambda,
                 rtDW->H_kq, rtDW->f_e, rtDW->M_a, rtDW->r_e,
                 &rtDW->sf_formulate_qp_4);

  /* MATLAB Function: '<S1>/state_space_mdl_5' incorporates:
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/v_DC_pu'
   *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
   */
  state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                    rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                    rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                    rtU->omega_el_pu, rtU->v_DC_pu * (-0.333333343F *
    rtDW->SinCos1_o2 + -0.577350259F * rtDW->SinCos1_o1), rtU->v_DC_pu *
                    (-0.333333343F * -rtDW->SinCos1_o1 + -0.577350259F *
                     rtDW->SinCos1_o2), rtU->v_DC_pu * (0.333333343F *
    rtDW->SinCos1_o2 + -0.577350259F * rtDW->SinCos1_o1), rtU->v_DC_pu *
                    (0.333333343F * -rtDW->SinCos1_o1 + -0.577350259F *
                     rtDW->SinCos1_o2), rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0,
                    &rtDW->sf_state_space_mdl_5);

  /* MATLAB Function: '<S1>/formulate_qp_5' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/lambda'
   */
  formulate_qp_1(rtDW->m3, rtDW->m2, rtDW->m1, rtDW->m0, rtU->i_dq_pu[0],
                 rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu, rtU->lambda,
                 rtDW->H_k, rtDW->f_o, rtDW->M_h, rtDW->r_b,
                 &rtDW->sf_formulate_qp_5);

  /* MATLAB Function: '<S1>/state_space_mdl_6' incorporates:
   *  Inport: '<Root>/Ld_over_LB'
   *  Inport: '<Root>/Lq_over_LB'
   *  Inport: '<Root>/Rs_over_ZB'
   *  Inport: '<Root>/Ts_times_ZB_over_Ld'
   *  Inport: '<Root>/Ts_times_ZB_over_Lq'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/omega_el_pu'
   *  Inport: '<Root>/psi_pm_over_psiB'
   *  Inport: '<Root>/v_DC_pu'
   *  MATLAB Function: '<S1>/act_sw_2_dq_volts_all'
   */
  state_space_mdl_1(rtU->Ts_times_ZB_over_Ld, rtU->Ts_times_ZB_over_Lq,
                    rtU->Rs_over_ZB, rtU->Ld_over_LB, rtU->Lq_over_LB,
                    rtU->psi_pm_over_psiB, rtU->i_dq_pu[0], rtU->i_dq_pu[1],
                    rtU->omega_el_pu, rtU->v_DC_pu * (0.666666687F *
    rtDW->SinCos1_o2), rtU->v_DC_pu * (0.666666687F * -rtDW->SinCos1_o1),
                    rtU->v_DC_pu * (0.333333343F * rtDW->SinCos1_o2 +
    -0.577350259F * rtDW->SinCos1_o1), rtU->v_DC_pu * (0.333333343F *
    -rtDW->SinCos1_o1 + -0.577350259F * rtDW->SinCos1_o2), rtDW->m0, rtDW->m1,
                    rtDW->m2, rtDW->m3, &rtDW->sf_state_space_mdl_6);

  /* MATLAB Function: '<S1>/formulate_qp_6' incorporates:
   *  Inport: '<Root>/i_d_ref_pu'
   *  Inport: '<Root>/i_dq_pu'
   *  Inport: '<Root>/i_q_ref_pu'
   *  Inport: '<Root>/lambda'
   */
  formulate_qp_1(rtDW->m0, rtDW->m1, rtDW->m2, rtDW->m3, rtU->i_dq_pu[0],
                 rtU->i_dq_pu[1], rtU->i_d_ref_pu, rtU->i_q_ref_pu, rtU->lambda,
                 rtDW->H, rtDW->f, rtDW->M, rtDW->r, &rtDW->sf_formulate_qp_6);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_1' */
  detect_unsuited_sequence_1(rtDW->H_k4, rtDW->f_a, &rtb_unsuited_a);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_2' */
  detect_unsuited_sequence_1(rtDW->H_j, rtDW->f_ej, &rtb_unsuited_l);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_3' */
  detect_unsuited_sequence_1(rtDW->H_o, rtDW->f_n, &rtb_unsuited_g);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_4' */
  detect_unsuited_sequence_1(rtDW->H_kq, rtDW->f_e, &rtb_unsuited_k);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_5' */
  detect_unsuited_sequence_1(rtDW->H_k, rtDW->f_o, &rtb_unsuited_h);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_6' */
  detect_unsuited_sequence_1(rtDW->H, rtDW->f, &rtb_unsuited);

  /* MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' */
  /* MATLAB Function 'impl_modul_mpc_allQP/qp_solver_for_suited_seq_AS': '<S16>:1' */
  /* '<S16>:1:3' x1 = single([0.5 0 0 0.5]'); */
  /* '<S16>:1:4' x2 = x1; */
  /* '<S16>:1:5' x3 = x2; */
  /* '<S16>:1:6' x4 = x3; */
  /* '<S16>:1:7' x5 = x4; */
  /* '<S16>:1:8' x6 = x5; */
  rtDW->x1[0] = 0.5F;
  rtDW->x2[0] = 0.5F;
  rtDW->x3[0] = 0.5F;
  rtDW->x4[0] = 0.5F;
  rtDW->x5[0] = 0.5F;
  rtDW->x6[0] = 0.5F;
  rtDW->x1[1] = 0.0F;
  rtDW->x2[1] = 0.0F;
  rtDW->x3[1] = 0.0F;
  rtDW->x4[1] = 0.0F;
  rtDW->x5[1] = 0.0F;
  rtDW->x6[1] = 0.0F;
  rtDW->x1[2] = 0.0F;
  rtDW->x2[2] = 0.0F;
  rtDW->x3[2] = 0.0F;
  rtDW->x4[2] = 0.0F;
  rtDW->x5[2] = 0.0F;
  rtDW->x6[2] = 0.0F;
  rtDW->x1[3] = 0.5F;
  rtDW->x2[3] = 0.5F;
  rtDW->x3[3] = 0.5F;
  rtDW->x4[3] = 0.5F;
  rtDW->x5[3] = 0.5F;
  rtDW->x6[3] = 0.5F;

  /* '<S16>:1:10' J1 = single(42); */
  rtDW->SinCos1_o1 = 42.0F;

  /* MATLAB Function: '<S1>/min_Costs' incorporates:
   *  MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS'
   */
  /* '<S16>:1:11' J2 = J1; */
  rtDW->J_1to6[1] = 42.0F;

  /* '<S16>:1:12' J3 = J2; */
  rtDW->J_1to6[2] = 42.0F;

  /* '<S16>:1:13' J4 = J3; */
  rtDW->J_1to6[3] = 42.0F;

  /* '<S16>:1:14' J5 = J4; */
  rtDW->J_1to6[4] = 42.0F;

  /* '<S16>:1:15' J6 = J5; */
  rtDW->J_1to6[5] = 42.0F;

  /* Outport: '<Root>/iterations_qp' incorporates:
   *  MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS'
   */
  /* '<S16>:1:17' iter1 = single(0); */
  rtY->iterations_qp[0] = 0.0F;

  /* '<S16>:1:18' iter2 = iter1; */
  rtY->iterations_qp[1] = 0.0F;

  /* '<S16>:1:19' iter3 = iter2; */
  rtY->iterations_qp[2] = 0.0F;

  /* '<S16>:1:20' iter4 = iter3; */
  rtY->iterations_qp[3] = 0.0F;

  /* '<S16>:1:21' iter5 = iter4; */
  rtY->iterations_qp[4] = 0.0F;

  /* '<S16>:1:22' iter6 = iter5; */
  rtY->iterations_qp[5] = 0.0F;

  /* MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS' incorporates:
   *  SignalConversion generated from: '<S16>/ SFunction '
   */
  /*  contraints */
  /*             t1 t2 t3 t4 */
  /* '<S16>:1:26' A = single([-1  0  0  0 ;   % t>=0 is converted to -1<=0 */
  /* '<S16>:1:27'              0 -1  0  0 ;   % no row=no of ineq constraints */
  /* '<S16>:1:28'              0  0 -1  0 ;   % no columns=no of optimization variables */
  /* '<S16>:1:29'              0  0  0 -1]); */
  /*  t>=0 is converted to -1<=0 */
  /*  no row=no of ineq constraints */
  /*  no columns=no of optimization variables */
  /* '<S16>:1:31' b = single(zeros(4,1)); */
  /* '<S16>:1:33' Aeq = single([1 1 1 1]); */
  /* '<S16>:1:34' beq =  single([1]); */
  /*  sum of all duration times  */
  /*  define cold start for active-set solver */
  /* '<S16>:1:37' iA0 = false(size(b)); */
  /*  if (sum_of_unsuited == 4 || sum_of_unsuited == 5) */
  /* '<S16>:1:41' if (unsuited(1) == false) */
  if (!rtb_unsuited_a) {
    /* '<S16>:1:42' [x1,iter1] = mpc_solve(H1,f1,A,b,Aeq,beq,iA0,max_iter,tol); */
    /* '<S16>:1:70' x = single([0 0 0 0]'); */
    /* '<S16>:1:71' iter = single(0); */
    /*  set up solver */
    /* '<S16>:1:73' options = mpcActiveSetOptions('single'); */
    /* '<S16>:1:74' options.MaxIterations = max_iter; */
    /* '<S16>:1:75' options.ConstriantTolerance = tol; */
    /* '<S16>:1:76' options.UseHessianAsInput = false; */
    /* '<S16>:1:77' options.IntegrityChecks = false; */
    /* '<S16>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
    /* '<S16>:1:81' exitflag = single(0); */
    /*  calculate inverse of H */
    /* '<S16>:1:83' [L,~] = chol(H,'lower'); */
    rtDW->B_size[0] = 4;
    rtDW->B_size[1] = 4;
    cholesky(rtDW->H_k4, rtDW->B_size, rtDW);

    /* '<S16>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
    if ((int8_T)rtDW->B_size[0] < (int8_T)rtDW->B_size[1]) {
      rtDW->d = (int8_T)rtDW->B_size[0];
    } else {
      rtDW->d = (int8_T)rtDW->B_size[1];
    }

    rtDW->b_I_size[0] = (int8_T)rtDW->B_size[0];
    rtDW->b_I_size[1] = (int8_T)rtDW->B_size[1];
    rtDW->loop_ub = (int8_T)rtDW->B_size[0] * (int8_T)rtDW->B_size[1] - 1;
    if (0 <= rtDW->loop_ub) {
      memset(&rtDW->b_I_data[0], 0, (rtDW->loop_ub + 1) * sizeof(real_T));
    }

    if (rtDW->d > 0) {
      rtDW->k = 0;
      while (rtDW->k <= rtDW->d - 1) {
        rtDW->b_I_data[rtDW->k + rtDW->b_I_size[0] * rtDW->k] = 1.0;
        rtDW->k++;
      }
    }

    linsolve(rtDW->H_k4, rtDW->B_size, rtDW->b_I_data, rtDW->b_I_size,
             rtDW->Linv_data, rtDW->Linv_size, rtDW);

    /*  solve QP */
    /* '<S16>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
    rtDW->x1[0] = -rtDW->f_a[0];
    rtDW->x1[1] = -rtDW->f_a[1];
    rtDW->x1[2] = -rtDW->f_a[2];
    rtDW->x1[3] = -rtDW->f_a[3];

    /* Outport: '<Root>/iterations_qp' incorporates:
     *  Inport: '<Root>/max_iter'
     */
    mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x1, rtU->max_iter,
                       rtDW->x_tmp_data, &rtDW->x_tmp_size, &rtY->iterations_qp
                       [0], rtDW);

    /* '<S16>:1:87' x = single(x_tmp(1:4,1)); */
    /* '<S16>:1:88' iter = single(exitflag); */
    /* '<S16>:1:43' J1 = x1'*(M1'*M1)*x1-2*r1'*M1*x1; */
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->x1[rtDW->k] = rtDW->x_tmp_data[rtDW->k];
      for (rtDW->d = 0; rtDW->d < 4; rtDW->d++) {
        rtDW->rtb_M_n_tmp = rtDW->k + (rtDW->d << 2);
        rtDW->H_k4[rtDW->rtb_M_n_tmp] = 0.0F;
        for (rtDW->loop_ub = 0; rtDW->loop_ub < 8; rtDW->loop_ub++) {
          rtDW->H_k4[rtDW->rtb_M_n_tmp] += rtDW->M_n[(rtDW->k << 3) +
            rtDW->loop_ub] * rtDW->M_n[(rtDW->d << 3) + rtDW->loop_ub];
        }
      }
    }

    rtDW->SinCos1_o2 = 0.0F;
    rtDW->f_k = 0.0F;
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->d = rtDW->k << 2;
      rtDW->SinCos1_o2 += (rtDW->H_k4[rtDW->d + 3] * rtDW->x_tmp_data[3] +
                           (rtDW->H_k4[rtDW->d + 2] * rtDW->x_tmp_data[2] +
                            (rtDW->H_k4[rtDW->d + 1] * rtDW->x_tmp_data[1] +
        rtDW->H_k4[rtDW->d] * rtDW->x_tmp_data[0]))) * rtDW->x_tmp_data[rtDW->k];
      rtDW->f_a[rtDW->k] = 0.0F;
      for (rtDW->d = 0; rtDW->d < 8; rtDW->d++) {
        rtDW->f_a[rtDW->k] += rtDW->M_n[(rtDW->k << 3) + rtDW->d] * (2.0F *
          rtDW->r_bc[rtDW->d]);
      }

      rtDW->f_k += rtDW->f_a[rtDW->k] * rtDW->x_tmp_data[rtDW->k];
    }

    rtDW->SinCos1_o1 = rtDW->SinCos1_o2 - rtDW->f_k;
  }

  /* '<S16>:1:45' if (unsuited(2) == false) */
  if (!rtb_unsuited_l) {
    /* '<S16>:1:46' [x2,iter2] = mpc_solve(H2,f2,A,b,Aeq,beq,iA0,max_iter,tol); */
    /* '<S16>:1:70' x = single([0 0 0 0]'); */
    /* '<S16>:1:71' iter = single(0); */
    /*  set up solver */
    /* '<S16>:1:73' options = mpcActiveSetOptions('single'); */
    /* '<S16>:1:74' options.MaxIterations = max_iter; */
    /* '<S16>:1:75' options.ConstriantTolerance = tol; */
    /* '<S16>:1:76' options.UseHessianAsInput = false; */
    /* '<S16>:1:77' options.IntegrityChecks = false; */
    /* '<S16>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
    /* '<S16>:1:81' exitflag = single(0); */
    /*  calculate inverse of H */
    /* '<S16>:1:83' [L,~] = chol(H,'lower'); */
    rtDW->B_size[0] = 4;
    rtDW->B_size[1] = 4;
    memcpy(&rtDW->H_k4[0], &rtDW->H_j[0], sizeof(real32_T) << 4U);
    cholesky(rtDW->H_k4, rtDW->B_size, rtDW);

    /* '<S16>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
    if ((int8_T)rtDW->B_size[0] < (int8_T)rtDW->B_size[1]) {
      rtDW->d = (int8_T)rtDW->B_size[0];
    } else {
      rtDW->d = (int8_T)rtDW->B_size[1];
    }

    rtDW->b_I_size[0] = (int8_T)rtDW->B_size[0];
    rtDW->b_I_size[1] = (int8_T)rtDW->B_size[1];
    rtDW->loop_ub = (int8_T)rtDW->B_size[0] * (int8_T)rtDW->B_size[1] - 1;
    if (0 <= rtDW->loop_ub) {
      memset(&rtDW->b_I_data[0], 0, (rtDW->loop_ub + 1) * sizeof(real_T));
    }

    if (rtDW->d > 0) {
      rtDW->k = 0;
      while (rtDW->k <= rtDW->d - 1) {
        rtDW->b_I_data[rtDW->k + rtDW->b_I_size[0] * rtDW->k] = 1.0;
        rtDW->k++;
      }
    }

    linsolve(rtDW->H_k4, rtDW->B_size, rtDW->b_I_data, rtDW->b_I_size,
             rtDW->Linv_data, rtDW->Linv_size, rtDW);

    /*  solve QP */
    /* '<S16>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
    rtDW->x2[0] = -rtDW->f_ej[0];
    rtDW->x2[1] = -rtDW->f_ej[1];
    rtDW->x2[2] = -rtDW->f_ej[2];
    rtDW->x2[3] = -rtDW->f_ej[3];

    /* Outport: '<Root>/iterations_qp' incorporates:
     *  Inport: '<Root>/max_iter'
     */
    mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x2, rtU->max_iter,
                       rtDW->x_tmp_data, &rtDW->x_tmp_size, &rtY->iterations_qp
                       [1], rtDW);

    /* '<S16>:1:87' x = single(x_tmp(1:4,1)); */
    /* '<S16>:1:88' iter = single(exitflag); */
    /* '<S16>:1:47' J2 = x2'*(M2'*M2)*x2-2*r2'*M2*x2; */
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->x2[rtDW->k] = rtDW->x_tmp_data[rtDW->k];
      for (rtDW->d = 0; rtDW->d < 4; rtDW->d++) {
        rtDW->rtb_M_n_tmp = rtDW->k + (rtDW->d << 2);
        rtDW->H_j[rtDW->rtb_M_n_tmp] = 0.0F;
        for (rtDW->loop_ub = 0; rtDW->loop_ub < 8; rtDW->loop_ub++) {
          rtDW->H_j[rtDW->rtb_M_n_tmp] += rtDW->M_eb[(rtDW->k << 3) +
            rtDW->loop_ub] * rtDW->M_eb[(rtDW->d << 3) + rtDW->loop_ub];
        }
      }
    }

    rtDW->SinCos1_o2 = 0.0F;
    rtDW->f_k = 0.0F;
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->d = rtDW->k << 2;
      rtDW->SinCos1_o2 += (rtDW->H_j[rtDW->d + 3] * rtDW->x_tmp_data[3] +
                           (rtDW->H_j[rtDW->d + 2] * rtDW->x_tmp_data[2] +
                            (rtDW->H_j[rtDW->d + 1] * rtDW->x_tmp_data[1] +
        rtDW->H_j[rtDW->d] * rtDW->x_tmp_data[0]))) * rtDW->x_tmp_data[rtDW->k];
      rtDW->f_a[rtDW->k] = 0.0F;
      for (rtDW->d = 0; rtDW->d < 8; rtDW->d++) {
        rtDW->f_a[rtDW->k] += rtDW->M_eb[(rtDW->k << 3) + rtDW->d] * (2.0F *
          rtDW->r_eo[rtDW->d]);
      }

      rtDW->f_k += rtDW->f_a[rtDW->k] * rtDW->x_tmp_data[rtDW->k];
    }

    /* MATLAB Function: '<S1>/min_Costs' */
    rtDW->J_1to6[1] = rtDW->SinCos1_o2 - rtDW->f_k;
  }

  /* '<S16>:1:49' if (unsuited(3) == false) */
  if (!rtb_unsuited_g) {
    /* '<S16>:1:50' [x3,iter3] = mpc_solve(H3,f3,A,b,Aeq,beq,iA0,max_iter,tol); */
    /* '<S16>:1:70' x = single([0 0 0 0]'); */
    /* '<S16>:1:71' iter = single(0); */
    /*  set up solver */
    /* '<S16>:1:73' options = mpcActiveSetOptions('single'); */
    /* '<S16>:1:74' options.MaxIterations = max_iter; */
    /* '<S16>:1:75' options.ConstriantTolerance = tol; */
    /* '<S16>:1:76' options.UseHessianAsInput = false; */
    /* '<S16>:1:77' options.IntegrityChecks = false; */
    /* '<S16>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
    /* '<S16>:1:81' exitflag = single(0); */
    /*  calculate inverse of H */
    /* '<S16>:1:83' [L,~] = chol(H,'lower'); */
    rtDW->B_size[0] = 4;
    rtDW->B_size[1] = 4;
    memcpy(&rtDW->H_k4[0], &rtDW->H_o[0], sizeof(real32_T) << 4U);
    cholesky(rtDW->H_k4, rtDW->B_size, rtDW);

    /* '<S16>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
    if ((int8_T)rtDW->B_size[0] < (int8_T)rtDW->B_size[1]) {
      rtDW->d = (int8_T)rtDW->B_size[0];
    } else {
      rtDW->d = (int8_T)rtDW->B_size[1];
    }

    rtDW->b_I_size[0] = (int8_T)rtDW->B_size[0];
    rtDW->b_I_size[1] = (int8_T)rtDW->B_size[1];
    rtDW->loop_ub = (int8_T)rtDW->B_size[0] * (int8_T)rtDW->B_size[1] - 1;
    if (0 <= rtDW->loop_ub) {
      memset(&rtDW->b_I_data[0], 0, (rtDW->loop_ub + 1) * sizeof(real_T));
    }

    if (rtDW->d > 0) {
      rtDW->k = 0;
      while (rtDW->k <= rtDW->d - 1) {
        rtDW->b_I_data[rtDW->k + rtDW->b_I_size[0] * rtDW->k] = 1.0;
        rtDW->k++;
      }
    }

    linsolve(rtDW->H_k4, rtDW->B_size, rtDW->b_I_data, rtDW->b_I_size,
             rtDW->Linv_data, rtDW->Linv_size, rtDW);

    /*  solve QP */
    /* '<S16>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
    rtDW->x3[0] = -rtDW->f_n[0];
    rtDW->x3[1] = -rtDW->f_n[1];
    rtDW->x3[2] = -rtDW->f_n[2];
    rtDW->x3[3] = -rtDW->f_n[3];

    /* Outport: '<Root>/iterations_qp' incorporates:
     *  Inport: '<Root>/max_iter'
     */
    mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x3, rtU->max_iter,
                       rtDW->x_tmp_data, &rtDW->x_tmp_size, &rtY->iterations_qp
                       [2], rtDW);

    /* '<S16>:1:87' x = single(x_tmp(1:4,1)); */
    /* '<S16>:1:88' iter = single(exitflag); */
    /* '<S16>:1:51' J3 = x3'*(M3'*M3)*x3-2*r3'*M3*x3; */
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->x3[rtDW->k] = rtDW->x_tmp_data[rtDW->k];
      for (rtDW->d = 0; rtDW->d < 4; rtDW->d++) {
        rtDW->rtb_M_n_tmp = rtDW->k + (rtDW->d << 2);
        rtDW->H_o[rtDW->rtb_M_n_tmp] = 0.0F;
        for (rtDW->loop_ub = 0; rtDW->loop_ub < 8; rtDW->loop_ub++) {
          rtDW->H_o[rtDW->rtb_M_n_tmp] += rtDW->M_e[(rtDW->k << 3) +
            rtDW->loop_ub] * rtDW->M_e[(rtDW->d << 3) + rtDW->loop_ub];
        }
      }
    }

    rtDW->SinCos1_o2 = 0.0F;
    rtDW->f_k = 0.0F;
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->d = rtDW->k << 2;
      rtDW->SinCos1_o2 += (rtDW->H_o[rtDW->d + 3] * rtDW->x_tmp_data[3] +
                           (rtDW->H_o[rtDW->d + 2] * rtDW->x_tmp_data[2] +
                            (rtDW->H_o[rtDW->d + 1] * rtDW->x_tmp_data[1] +
        rtDW->H_o[rtDW->d] * rtDW->x_tmp_data[0]))) * rtDW->x_tmp_data[rtDW->k];
      rtDW->f_a[rtDW->k] = 0.0F;
      for (rtDW->d = 0; rtDW->d < 8; rtDW->d++) {
        rtDW->f_a[rtDW->k] += rtDW->M_e[(rtDW->k << 3) + rtDW->d] * (2.0F *
          rtDW->r_m[rtDW->d]);
      }

      rtDW->f_k += rtDW->f_a[rtDW->k] * rtDW->x_tmp_data[rtDW->k];
    }

    /* MATLAB Function: '<S1>/min_Costs' */
    rtDW->J_1to6[2] = rtDW->SinCos1_o2 - rtDW->f_k;
  }

  /* '<S16>:1:53' if (unsuited(4) == false) */
  if (!rtb_unsuited_k) {
    /* '<S16>:1:54' [x4,iter4] = mpc_solve(H4,f4,A,b,Aeq,beq,iA0,max_iter,tol); */
    /* '<S16>:1:70' x = single([0 0 0 0]'); */
    /* '<S16>:1:71' iter = single(0); */
    /*  set up solver */
    /* '<S16>:1:73' options = mpcActiveSetOptions('single'); */
    /* '<S16>:1:74' options.MaxIterations = max_iter; */
    /* '<S16>:1:75' options.ConstriantTolerance = tol; */
    /* '<S16>:1:76' options.UseHessianAsInput = false; */
    /* '<S16>:1:77' options.IntegrityChecks = false; */
    /* '<S16>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
    /* '<S16>:1:81' exitflag = single(0); */
    /*  calculate inverse of H */
    /* '<S16>:1:83' [L,~] = chol(H,'lower'); */
    rtDW->B_size[0] = 4;
    rtDW->B_size[1] = 4;
    memcpy(&rtDW->H_k4[0], &rtDW->H_kq[0], sizeof(real32_T) << 4U);
    cholesky(rtDW->H_k4, rtDW->B_size, rtDW);

    /* '<S16>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
    if ((int8_T)rtDW->B_size[0] < (int8_T)rtDW->B_size[1]) {
      rtDW->d = (int8_T)rtDW->B_size[0];
    } else {
      rtDW->d = (int8_T)rtDW->B_size[1];
    }

    rtDW->b_I_size[0] = (int8_T)rtDW->B_size[0];
    rtDW->b_I_size[1] = (int8_T)rtDW->B_size[1];
    rtDW->loop_ub = (int8_T)rtDW->B_size[0] * (int8_T)rtDW->B_size[1] - 1;
    if (0 <= rtDW->loop_ub) {
      memset(&rtDW->b_I_data[0], 0, (rtDW->loop_ub + 1) * sizeof(real_T));
    }

    if (rtDW->d > 0) {
      rtDW->k = 0;
      while (rtDW->k <= rtDW->d - 1) {
        rtDW->b_I_data[rtDW->k + rtDW->b_I_size[0] * rtDW->k] = 1.0;
        rtDW->k++;
      }
    }

    linsolve(rtDW->H_k4, rtDW->B_size, rtDW->b_I_data, rtDW->b_I_size,
             rtDW->Linv_data, rtDW->Linv_size, rtDW);

    /*  solve QP */
    /* '<S16>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
    rtDW->x4[0] = -rtDW->f_e[0];
    rtDW->x4[1] = -rtDW->f_e[1];
    rtDW->x4[2] = -rtDW->f_e[2];
    rtDW->x4[3] = -rtDW->f_e[3];

    /* Outport: '<Root>/iterations_qp' incorporates:
     *  Inport: '<Root>/max_iter'
     */
    mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x4, rtU->max_iter,
                       rtDW->x_tmp_data, &rtDW->x_tmp_size, &rtY->iterations_qp
                       [3], rtDW);

    /* '<S16>:1:87' x = single(x_tmp(1:4,1)); */
    /* '<S16>:1:88' iter = single(exitflag); */
    /* '<S16>:1:55' J4 = x4'*(M4'*M4)*x4-2*r4'*M4*x4; */
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->x4[rtDW->k] = rtDW->x_tmp_data[rtDW->k];
      for (rtDW->d = 0; rtDW->d < 4; rtDW->d++) {
        rtDW->rtb_M_n_tmp = rtDW->k + (rtDW->d << 2);
        rtDW->H_kq[rtDW->rtb_M_n_tmp] = 0.0F;
        for (rtDW->loop_ub = 0; rtDW->loop_ub < 8; rtDW->loop_ub++) {
          rtDW->H_kq[rtDW->rtb_M_n_tmp] += rtDW->M_a[(rtDW->k << 3) +
            rtDW->loop_ub] * rtDW->M_a[(rtDW->d << 3) + rtDW->loop_ub];
        }
      }
    }

    rtDW->SinCos1_o2 = 0.0F;
    rtDW->f_k = 0.0F;
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->d = rtDW->k << 2;
      rtDW->SinCos1_o2 += (rtDW->H_kq[rtDW->d + 3] * rtDW->x_tmp_data[3] +
                           (rtDW->H_kq[rtDW->d + 2] * rtDW->x_tmp_data[2] +
                            (rtDW->H_kq[rtDW->d + 1] * rtDW->x_tmp_data[1] +
        rtDW->H_kq[rtDW->d] * rtDW->x_tmp_data[0]))) * rtDW->x_tmp_data[rtDW->k];
      rtDW->f_a[rtDW->k] = 0.0F;
      for (rtDW->d = 0; rtDW->d < 8; rtDW->d++) {
        rtDW->f_a[rtDW->k] += rtDW->M_a[(rtDW->k << 3) + rtDW->d] * (2.0F *
          rtDW->r_e[rtDW->d]);
      }

      rtDW->f_k += rtDW->f_a[rtDW->k] * rtDW->x_tmp_data[rtDW->k];
    }

    /* MATLAB Function: '<S1>/min_Costs' */
    rtDW->J_1to6[3] = rtDW->SinCos1_o2 - rtDW->f_k;
  }

  /* '<S16>:1:57' if (unsuited(5) == false) */
  if (!rtb_unsuited_h) {
    /* '<S16>:1:58' [x5,iter5] = mpc_solve(H5,f5,A,b,Aeq,beq,iA0,max_iter,tol); */
    /* '<S16>:1:70' x = single([0 0 0 0]'); */
    /* '<S16>:1:71' iter = single(0); */
    /*  set up solver */
    /* '<S16>:1:73' options = mpcActiveSetOptions('single'); */
    /* '<S16>:1:74' options.MaxIterations = max_iter; */
    /* '<S16>:1:75' options.ConstriantTolerance = tol; */
    /* '<S16>:1:76' options.UseHessianAsInput = false; */
    /* '<S16>:1:77' options.IntegrityChecks = false; */
    /* '<S16>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
    /* '<S16>:1:81' exitflag = single(0); */
    /*  calculate inverse of H */
    /* '<S16>:1:83' [L,~] = chol(H,'lower'); */
    rtDW->B_size[0] = 4;
    rtDW->B_size[1] = 4;
    memcpy(&rtDW->H_k4[0], &rtDW->H_k[0], sizeof(real32_T) << 4U);
    cholesky(rtDW->H_k4, rtDW->B_size, rtDW);

    /* '<S16>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
    if ((int8_T)rtDW->B_size[0] < (int8_T)rtDW->B_size[1]) {
      rtDW->d = (int8_T)rtDW->B_size[0];
    } else {
      rtDW->d = (int8_T)rtDW->B_size[1];
    }

    rtDW->b_I_size[0] = (int8_T)rtDW->B_size[0];
    rtDW->b_I_size[1] = (int8_T)rtDW->B_size[1];
    rtDW->loop_ub = (int8_T)rtDW->B_size[0] * (int8_T)rtDW->B_size[1] - 1;
    if (0 <= rtDW->loop_ub) {
      memset(&rtDW->b_I_data[0], 0, (rtDW->loop_ub + 1) * sizeof(real_T));
    }

    if (rtDW->d > 0) {
      rtDW->k = 0;
      while (rtDW->k <= rtDW->d - 1) {
        rtDW->b_I_data[rtDW->k + rtDW->b_I_size[0] * rtDW->k] = 1.0;
        rtDW->k++;
      }
    }

    linsolve(rtDW->H_k4, rtDW->B_size, rtDW->b_I_data, rtDW->b_I_size,
             rtDW->Linv_data, rtDW->Linv_size, rtDW);

    /*  solve QP */
    /* '<S16>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
    rtDW->x5[0] = -rtDW->f_o[0];
    rtDW->x5[1] = -rtDW->f_o[1];
    rtDW->x5[2] = -rtDW->f_o[2];
    rtDW->x5[3] = -rtDW->f_o[3];

    /* Outport: '<Root>/iterations_qp' incorporates:
     *  Inport: '<Root>/max_iter'
     */
    mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->x5, rtU->max_iter,
                       rtDW->x_tmp_data, &rtDW->x_tmp_size, &rtY->iterations_qp
                       [4], rtDW);

    /* '<S16>:1:87' x = single(x_tmp(1:4,1)); */
    /* '<S16>:1:88' iter = single(exitflag); */
    /* '<S16>:1:59' J5 = x5'*(M5'*M5)*x5-2*r5'*M5*x5; */
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->x5[rtDW->k] = rtDW->x_tmp_data[rtDW->k];
      for (rtDW->d = 0; rtDW->d < 4; rtDW->d++) {
        rtDW->rtb_M_n_tmp = rtDW->k + (rtDW->d << 2);
        rtDW->H_k[rtDW->rtb_M_n_tmp] = 0.0F;
        for (rtDW->loop_ub = 0; rtDW->loop_ub < 8; rtDW->loop_ub++) {
          rtDW->H_k[rtDW->rtb_M_n_tmp] += rtDW->M_h[(rtDW->k << 3) +
            rtDW->loop_ub] * rtDW->M_h[(rtDW->d << 3) + rtDW->loop_ub];
        }
      }
    }

    rtDW->SinCos1_o2 = 0.0F;
    rtDW->f_k = 0.0F;
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->d = rtDW->k << 2;
      rtDW->SinCos1_o2 += (rtDW->H_k[rtDW->d + 3] * rtDW->x_tmp_data[3] +
                           (rtDW->H_k[rtDW->d + 2] * rtDW->x_tmp_data[2] +
                            (rtDW->H_k[rtDW->d + 1] * rtDW->x_tmp_data[1] +
        rtDW->H_k[rtDW->d] * rtDW->x_tmp_data[0]))) * rtDW->x_tmp_data[rtDW->k];
      rtDW->f_a[rtDW->k] = 0.0F;
      for (rtDW->d = 0; rtDW->d < 8; rtDW->d++) {
        rtDW->f_a[rtDW->k] += rtDW->M_h[(rtDW->k << 3) + rtDW->d] * (2.0F *
          rtDW->r_b[rtDW->d]);
      }

      rtDW->f_k += rtDW->f_a[rtDW->k] * rtDW->x_tmp_data[rtDW->k];
    }

    /* MATLAB Function: '<S1>/min_Costs' */
    rtDW->J_1to6[4] = rtDW->SinCos1_o2 - rtDW->f_k;
  }

  /* '<S16>:1:61' if (unsuited(6) == false) */
  if (!rtb_unsuited) {
    /* '<S16>:1:62' [x6,iter6] = mpc_solve(H6,f6,A,b,Aeq,beq,iA0,max_iter,tol); */
    /* '<S16>:1:70' x = single([0 0 0 0]'); */
    /* '<S16>:1:71' iter = single(0); */
    /*  set up solver */
    /* '<S16>:1:73' options = mpcActiveSetOptions('single'); */
    /* '<S16>:1:74' options.MaxIterations = max_iter; */
    /* '<S16>:1:75' options.ConstriantTolerance = tol; */
    /* '<S16>:1:76' options.UseHessianAsInput = false; */
    /* '<S16>:1:77' options.IntegrityChecks = false; */
    /* '<S16>:1:80' x_tmp = single([0.5 0 0 0.5]'); */
    /* '<S16>:1:81' exitflag = single(0); */
    /*  calculate inverse of H */
    /* '<S16>:1:83' [L,~] = chol(H,'lower'); */
    rtDW->B_size[0] = 4;
    rtDW->B_size[1] = 4;
    memcpy(&rtDW->H_k4[0], &rtDW->H[0], sizeof(real32_T) << 4U);
    cholesky(rtDW->H_k4, rtDW->B_size, rtDW);

    /* '<S16>:1:84' Linv = linsolve(L,eye(size(L)),struct('LT',true)); */
    if ((int8_T)rtDW->B_size[0] < (int8_T)rtDW->B_size[1]) {
      rtDW->d = (int8_T)rtDW->B_size[0];
    } else {
      rtDW->d = (int8_T)rtDW->B_size[1];
    }

    rtDW->b_I_size[0] = (int8_T)rtDW->B_size[0];
    rtDW->b_I_size[1] = (int8_T)rtDW->B_size[1];
    rtDW->loop_ub = (int8_T)rtDW->B_size[0] * (int8_T)rtDW->B_size[1] - 1;
    if (0 <= rtDW->loop_ub) {
      memset(&rtDW->b_I_data[0], 0, (rtDW->loop_ub + 1) * sizeof(real_T));
    }

    if (rtDW->d > 0) {
      rtDW->k = 0;
      while (rtDW->k <= rtDW->d - 1) {
        rtDW->b_I_data[rtDW->k + rtDW->b_I_size[0] * rtDW->k] = 1.0;
        rtDW->k++;
      }
    }

    linsolve(rtDW->H_k4, rtDW->B_size, rtDW->b_I_data, rtDW->b_I_size,
             rtDW->Linv_data, rtDW->Linv_size, rtDW);

    /*  solve QP */
    /* '<S16>:1:86' [x_tmp, exitflag] = mpcActiveSetSolver(Linv,-f,A,b,Aeq,beq,iA0,options); */
    rtDW->f_o[0] = -rtDW->f[0];
    rtDW->f_o[1] = -rtDW->f[1];
    rtDW->f_o[2] = -rtDW->f[2];
    rtDW->f_o[3] = -rtDW->f[3];

    /* Outport: '<Root>/iterations_qp' incorporates:
     *  Inport: '<Root>/max_iter'
     */
    mpcActiveSetSolver(rtDW->Linv_data, rtDW->Linv_size, rtDW->f_o,
                       rtU->max_iter, rtDW->x_tmp_data, &rtDW->x_tmp_size,
                       &rtY->iterations_qp[5], rtDW);

    /* '<S16>:1:87' x = single(x_tmp(1:4,1)); */
    /* '<S16>:1:88' iter = single(exitflag); */
    /* '<S16>:1:63' J6 = x6'*(M6'*M6)*x6-2*r6'*M6*x6; */
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->x6[rtDW->k] = rtDW->x_tmp_data[rtDW->k];
      for (rtDW->d = 0; rtDW->d < 4; rtDW->d++) {
        rtDW->rtb_M_n_tmp = rtDW->k + (rtDW->d << 2);
        rtDW->H[rtDW->rtb_M_n_tmp] = 0.0F;
        for (rtDW->loop_ub = 0; rtDW->loop_ub < 8; rtDW->loop_ub++) {
          rtDW->H[rtDW->rtb_M_n_tmp] += rtDW->M[(rtDW->k << 3) + rtDW->loop_ub] *
            rtDW->M[(rtDW->d << 3) + rtDW->loop_ub];
        }
      }
    }

    rtDW->SinCos1_o2 = 0.0F;
    rtDW->f_k = 0.0F;
    for (rtDW->k = 0; rtDW->k < 4; rtDW->k++) {
      rtDW->d = rtDW->k << 2;
      rtDW->SinCos1_o2 += (rtDW->H[rtDW->d + 3] * rtDW->x_tmp_data[3] + (rtDW->
        H[rtDW->d + 2] * rtDW->x_tmp_data[2] + (rtDW->H[rtDW->d + 1] *
        rtDW->x_tmp_data[1] + rtDW->H[rtDW->d] * rtDW->x_tmp_data[0]))) *
        rtDW->x_tmp_data[rtDW->k];
      rtDW->f_a[rtDW->k] = 0.0F;
      for (rtDW->d = 0; rtDW->d < 8; rtDW->d++) {
        rtDW->f_a[rtDW->k] += rtDW->M[(rtDW->k << 3) + rtDW->d] * (2.0F *
          rtDW->r[rtDW->d]);
      }

      rtDW->f_k += rtDW->f_a[rtDW->k] * rtDW->x_tmp_data[rtDW->k];
    }

    /* MATLAB Function: '<S1>/min_Costs' */
    rtDW->J_1to6[5] = rtDW->SinCos1_o2 - rtDW->f_k;
  }

  /* MATLAB Function: '<S1>/min_Costs' incorporates:
   *  MATLAB Function: '<S1>/qp_solver_for_suited_seq_AS'
   *  MATLAB Function: '<S1>/tz_2_tph'
   */
  /*  end */
  /* MATLAB Function 'impl_modul_mpc_allQP/min_Costs': '<S15>:1' */
  /* '<S15>:1:3' J_1to6 = single([J1,J2,J3,J4,J5,J6]); */
  rtDW->J_1to6[0] = rtDW->SinCos1_o1;

  /* '<S15>:1:4' x_1to6 = single([x1,x2,x3,x4,x5,x6]); */
  /*  [~,idx] = min(J_1to6); */
  /* '<S15>:1:6' [~,idx] = minimum(J_1to6); */
  /* '<S15>:1:12' min_tmp = X(1); */
  /* '<S15>:1:13' idx_tmp = 1; */
  rtDW->d = 1;

  /* '<S15>:1:14' for i=1:6 */
  for (rtDW->k = 0; rtDW->k < 6; rtDW->k++) {
    rtDW->SinCos1_o2 = rtDW->J_1to6[rtDW->k];

    /* '<S15>:1:15' if(X(i) < min_tmp) */
    if (rtDW->SinCos1_o2 < rtDW->SinCos1_o1) {
      /* '<S15>:1:16' min_tmp = X(i); */
      rtDW->SinCos1_o1 = rtDW->SinCos1_o2;

      /* '<S15>:1:17' idx_tmp = i; */
      rtDW->d = rtDW->k + 1;
    }
  }

  /* '<S15>:1:20' min = min_tmp; */
  /* '<S15>:1:21' idx = idx_tmp; */
  /* '<S15>:1:7' x_opt = single(x_1to6(:,idx)); */
  /* '<S15>:1:8' idx_opt = single(idx); */
  /* MATLAB Function 'impl_modul_mpc_allQP/tz': '<S24>:1' */
  /* '<S24>:1:3' I = single([1 0 0; */
  /* '<S24>:1:4'      1 1 0; */
  /* '<S24>:1:5'      1 1 1]); */
  /* '<S24>:1:7' zer3 = single(zeros(3,1)); */
  /* '<S24>:1:9' T = single([I zer3]); */
  /* '<S24>:1:11' tz=single(T*x); */
  rtDW->rtb_x1_m[0] = rtDW->x1[0];
  rtDW->rtb_x1_m[4] = rtDW->x2[0];
  rtDW->rtb_x1_m[8] = rtDW->x3[0];
  rtDW->rtb_x1_m[12] = rtDW->x4[0];
  rtDW->rtb_x1_m[16] = rtDW->x5[0];
  rtDW->rtb_x1_m[20] = rtDW->x6[0];
  rtDW->rtb_x1_m[1] = rtDW->x1[1];
  rtDW->rtb_x1_m[5] = rtDW->x2[1];
  rtDW->rtb_x1_m[9] = rtDW->x3[1];
  rtDW->rtb_x1_m[13] = rtDW->x4[1];
  rtDW->rtb_x1_m[17] = rtDW->x5[1];
  rtDW->rtb_x1_m[21] = rtDW->x6[1];
  rtDW->rtb_x1_m[2] = rtDW->x1[2];
  rtDW->rtb_x1_m[6] = rtDW->x2[2];
  rtDW->rtb_x1_m[10] = rtDW->x3[2];
  rtDW->rtb_x1_m[14] = rtDW->x4[2];
  rtDW->rtb_x1_m[18] = rtDW->x5[2];
  rtDW->rtb_x1_m[22] = rtDW->x6[2];
  rtDW->rtb_x1_m[3] = rtDW->x1[3];
  rtDW->rtb_x1_m[7] = rtDW->x2[3];
  rtDW->rtb_x1_m[11] = rtDW->x3[3];
  rtDW->rtb_x1_m[15] = rtDW->x4[3];
  rtDW->rtb_x1_m[19] = rtDW->x5[3];
  rtDW->rtb_x1_m[23] = rtDW->x6[3];

  /* MATLAB Function: '<S1>/tz' incorporates:
   *  MATLAB Function: '<S1>/min_Costs'
   */
  for (rtDW->k = 0; rtDW->k < 3; rtDW->k++) {
    /* MATLAB Function: '<S1>/min_Costs' incorporates:
     *  MATLAB Function: '<S1>/tz_2_tph'
     */
    rtDW->loop_ub = (rtDW->d - 1) << 2;
    rtDW->tz[rtDW->k] = rtDW->rtb_x1_m[rtDW->loop_ub + 3] * (real32_T)a[rtDW->k
      + 9] + (rtDW->rtb_x1_m[rtDW->loop_ub + 2] * (real32_T)a[rtDW->k + 6] +
              (rtDW->rtb_x1_m[rtDW->loop_ub + 1] * (real32_T)a[rtDW->k + 3] +
               rtDW->rtb_x1_m[rtDW->loop_ub] * (real32_T)a[rtDW->k]));
  }

  /* End of MATLAB Function: '<S1>/tz' */

  /* Outport: '<Root>/CMPA_opt' incorporates:
   *  MATLAB Function: '<S1>/min_Costs'
   *  MATLAB Function: '<S1>/tz_2_tph'
   */
  /* MATLAB Function 'impl_modul_mpc_allQP/tz_2_tph': '<S25>:1' */
  /* '<S25>:1:3' seq_order_table = single([1 2 3; */
  /* '<S25>:1:4'                    2 1 3; */
  /* '<S25>:1:5'                    3 1 2; */
  /* '<S25>:1:6'                    3 2 1; */
  /* '<S25>:1:7'                    2 3 1; */
  /* '<S25>:1:8'                    1 3 2]); */
  /* '<S25>:1:10' ta_1 = single(tz(seq_order_table(seq_no,1))); */
  /* '<S25>:1:11' tb_1 = single(tz(seq_order_table(seq_no,2))); */
  /* '<S25>:1:12' tc_1 = single(tz(seq_order_table(seq_no,3))); */
  rtY->CMPA_opt[0] = rtDW->tz[seq_order_table[rtDW->d - 1] - 1];
  rtY->CMPA_opt[1] = rtDW->tz[seq_order_table[rtDW->d + 5] - 1];
  rtY->CMPA_opt[2] = rtDW->tz[seq_order_table[rtDW->d + 11] - 1];

  /* Outport: '<Root>/unsuited_qp' */
  rtY->unsuited_qp[0] = rtb_unsuited_a;
  rtY->unsuited_qp[1] = rtb_unsuited_l;
  rtY->unsuited_qp[2] = rtb_unsuited_g;
  rtY->unsuited_qp[3] = rtb_unsuited_k;
  rtY->unsuited_qp[4] = rtb_unsuited_h;
  rtY->unsuited_qp[5] = rtb_unsuited;
}

/* Model initialize function */
void impl_modul_mpc_allQP_initialize(RT_MODEL *const rtM)
{
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
