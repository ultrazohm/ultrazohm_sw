/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: impl_modul_mpc.c
 *
 * Code generated for Simulink model 'impl_modul_mpc'.
 *
 * Model version                  : 2.3
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Apr  8 09:55:37 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "impl_modul_mpc.h"

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
static void P_omega(const real32_T z[4], real32_T Ts, real32_T w[4], DW *rtDW);
static void GradProj(const real32_T H[16], const real32_T f[4], const real32_T
                     x0[4], real32_T alpha0, real32_T tol, real32_T max_iter,
                     const real32_T M[32], const real32_T r[8], real32_T Ts,
                     real32_T x[4], real32_T *iter, real32_T *J, DW *rtDW);

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
  /* MATLAB Function 'impl_modul_mpc/detect_unsuited_sequence_1': '<S3>:1' */
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

  /* MATLAB Function 'impl_modul_mpc/formulate_qp_1': '<S9>:1' */
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

  /* MATLAB Function 'impl_modul_mpc/state_space_mdl_1': '<S18>:1' */
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

/*
 * Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq'
 * function w = P_omega(z,Ts)
 */
static void P_omega(const real32_T z[4], real32_T Ts, real32_T w[4], DW *rtDW)
{
  boolean_T lambda_ref_done;

  /* '<S16>:1:90' f_lambda_tilde_j = [0 0 0 0]'; */
  /*      z_tilde = sort(z,'descend'); */
  /* '<S16>:1:92' z_tilde = sort_descending(z); */
  rtDW->x[0] = z[0];
  rtDW->f_lambda_tilde_j[1] = 0.0;
  rtDW->x[1] = z[1];
  rtDW->f_lambda_tilde_j[2] = 0.0;
  rtDW->x[2] = z[2];
  rtDW->f_lambda_tilde_j[3] = 0.0;
  rtDW->x[3] = z[3];

  /*  sort input array elemnts in descending order */
  /*  x is of dimension 4 */
  /* '<S16>:1:122' for(i = (1:4) */
  /* '<S16>:1:123' for(j = (i+1):4 */
  rtDW->c_j = 0;
  while (rtDW->c_j <= 2) {
    /* '<S16>:1:124' if(x(i) < x(j)) */
    rtDW->y = rtDW->x[rtDW->c_j + 1];
    if (rtDW->x[0] < rtDW->y) {
      /* '<S16>:1:125' tmp = x(i); */
      rtDW->tmp = rtDW->x[0];

      /* '<S16>:1:126' x(i) = x(j); */
      rtDW->x[0] = rtDW->y;

      /* '<S16>:1:127' x(j) = tmp; */
      rtDW->x[rtDW->c_j + 1] = rtDW->tmp;
    }

    rtDW->c_j++;
  }

  /* '<S16>:1:123' for(j = (i+1):4 */
  rtDW->c_j = 0;
  while (rtDW->c_j <= 1) {
    /* '<S16>:1:124' if(x(i) < x(j)) */
    rtDW->y = rtDW->x[rtDW->c_j + 2];
    if (rtDW->x[1] < rtDW->y) {
      /* '<S16>:1:125' tmp = x(i); */
      rtDW->tmp = rtDW->x[1];

      /* '<S16>:1:126' x(i) = x(j); */
      rtDW->x[1] = rtDW->y;

      /* '<S16>:1:127' x(j) = tmp; */
      rtDW->x[rtDW->c_j + 2] = rtDW->tmp;
    }

    rtDW->c_j++;
  }

  /* '<S16>:1:123' for(j = (i+1):4 */
  /* '<S16>:1:124' if(x(i) < x(j)) */
  if (rtDW->x[2] < rtDW->x[3]) {
    /* '<S16>:1:125' tmp = x(i); */
    rtDW->tmp = rtDW->x[2];

    /* '<S16>:1:126' x(i) = x(j); */
    rtDW->x[2] = rtDW->x[3];

    /* '<S16>:1:127' x(j) = tmp; */
    rtDW->x[3] = rtDW->tmp;
  }

  /* '<S16>:1:123' for(j = (i+1):4 */
  /* '<S16>:1:131' z = x; */
  /* '<S16>:1:93' lambda_tilde = -z_tilde; */
  rtDW->lambda_tilde[0] = -rtDW->x[0];
  rtDW->lambda_tilde[1] = -rtDW->x[1];
  rtDW->lambda_tilde[2] = -rtDW->x[2];
  rtDW->lambda_tilde[3] = -rtDW->x[3];

  /* '<S16>:1:94' lambda_ref = single(0); */
  rtDW->tmp = 0.0F;

  /* '<S16>:1:95' f_lambda_tilde_j(1) = 0; */
  rtDW->f_lambda_tilde_j[0] = 0.0;

  /* '<S16>:1:96' lambda_ref_done = false; */
  lambda_ref_done = false;

  /* '<S16>:1:97' for j=2:4 */
  for (rtDW->i_c = 0; rtDW->i_c < 3; rtDW->i_c++) {
    /* '<S16>:1:98' f_lambda_tilde_j(j) = sum(z_tilde(1:j))+j*lambda_tilde(j); */
    rtDW->y = rtDW->x[0];
    rtDW->c_j = 2;
    while (rtDW->c_j <= rtDW->i_c + 2) {
      rtDW->y += rtDW->x[rtDW->c_j - 1];
      rtDW->c_j++;
    }

    rtDW->f_lambda_tilde_j_tmp = rtDW->lambda_tilde[rtDW->i_c + 1];
    rtDW->f_lambda_tilde_j[rtDW->i_c + 1] = ((real32_T)rtDW->i_c + 2.0F) *
      rtDW->f_lambda_tilde_j_tmp + rtDW->y;

    /* '<S16>:1:99' if (f_lambda_tilde_j(j) >= Ts) */
    rtDW->d = rtDW->f_lambda_tilde_j[rtDW->i_c + 1];
    if (rtDW->d >= Ts) {
      /* '<S16>:1:100' if (lambda_ref_done == false) */
      if (!lambda_ref_done) {
        /* '<S16>:1:101' lambda_ref = lambda_tilde(j-1) + (lambda_tilde(j)-lambda_tilde(j-1))*(Ts-f_lambda_tilde_j(j-1))/(f_lambda_tilde_j(j)-f_lambda_tilde_j(j-1)); */
        rtDW->tmp = (rtDW->f_lambda_tilde_j_tmp - rtDW->lambda_tilde[rtDW->i_c])
          * (Ts - (real32_T)rtDW->f_lambda_tilde_j[rtDW->i_c]) / (real32_T)
          (rtDW->d - rtDW->f_lambda_tilde_j[rtDW->i_c]) + rtDW->
          lambda_tilde[rtDW->i_c];

        /*              break */
        /* '<S16>:1:103' lambda_ref_done = true; */
        lambda_ref_done = true;
      }

      /* '<S16>:1:105' else */
      /* '<S16>:1:106' if j == 4 */
    } else if ((rtDW->i_c + 2 == 4) && (!lambda_ref_done)) {
      /* '<S16>:1:107' if (lambda_ref_done == false) */
      /* '<S16>:1:108' lambda_ref = (Ts-sum(z_tilde)) * 0.25; */
      rtDW->tmp = (Ts - (((rtDW->x[0] + rtDW->x[1]) + rtDW->x[2]) + rtDW->x[3]))
        * 0.25F;

      /*                  break */
      /* '<S16>:1:110' lambda_ref_done = true; */
      lambda_ref_done = true;
    }
  }

  /*      w = max(zeros(4,1), z+lambda_ref.*ones(4,1)); */
  /* '<S16>:1:116' w = max_largest_element_compare(zeros(4,1), z+lambda_ref.*ones(4,1)); */
  /*  compare every element of A and B and take the ones where A > B */
  /* '<S16>:1:136' w_tmp = single(zeros(4,1)); */
  /* '<S16>:1:137' for i=1:4 */
  rtDW->y = z[0] + rtDW->tmp;

  /* '<S16>:1:138' if(B(i) < A(i)) */
  if (rtDW->y < 0.0F) {
    /* '<S16>:1:139' w_tmp(i) = A(i); */
    w[0] = 0.0F;
  } else {
    /* '<S16>:1:140' else */
    /* '<S16>:1:141' w_tmp(i) = B(i); */
    w[0] = rtDW->y;
  }

  rtDW->y = z[1] + rtDW->tmp;

  /* '<S16>:1:138' if(B(i) < A(i)) */
  if (rtDW->y < 0.0F) {
    /* '<S16>:1:139' w_tmp(i) = A(i); */
    w[1] = 0.0F;
  } else {
    /* '<S16>:1:140' else */
    /* '<S16>:1:141' w_tmp(i) = B(i); */
    w[1] = rtDW->y;
  }

  rtDW->y = z[2] + rtDW->tmp;

  /* '<S16>:1:138' if(B(i) < A(i)) */
  if (rtDW->y < 0.0F) {
    /* '<S16>:1:139' w_tmp(i) = A(i); */
    w[2] = 0.0F;
  } else {
    /* '<S16>:1:140' else */
    /* '<S16>:1:141' w_tmp(i) = B(i); */
    w[2] = rtDW->y;
  }

  rtDW->y = z[3] + rtDW->tmp;

  /* '<S16>:1:138' if(B(i) < A(i)) */
  if (rtDW->y < 0.0F) {
    /* '<S16>:1:139' w_tmp(i) = A(i); */
    w[3] = 0.0F;
  } else {
    /* '<S16>:1:140' else */
    /* '<S16>:1:141' w_tmp(i) = B(i); */
    w[3] = rtDW->y;
  }

  /* '<S16>:1:144' w= w_tmp; */
}

/*
 * Function for MATLAB Function: '<S1>/qp_solver_for_suited_seq'
 * function [x,iter,J]= GradProj(H,f,x0,alpha0,tol,max_iter,M,r,Ts)
 */
static void GradProj(const real32_T H[16], const real32_T f[4], const real32_T
                     x0[4], real32_T alpha0, real32_T tol, real32_T max_iter,
                     const real32_T M[32], const real32_T r[8], real32_T Ts,
                     real32_T x[4], real32_T *iter, real32_T *J, DW *rtDW)
{
  boolean_T exitg1;
  boolean_T optim_done;
  boolean_T y;

  /* '<S16>:1:53' g0 = H*x0-f; */
  /* '<S16>:1:54' gk = g0; */
  /* '<S16>:1:55' xk = x0; */
  /* '<S16>:1:56' alphak = alpha0; */
  rtDW->alphak = alpha0;

  /* '<S16>:1:57' x = single([0 0 0 0]'); */
  for (rtDW->i = 0; rtDW->i < 4; rtDW->i++) {
    rtDW->gk[rtDW->i] = (((H[rtDW->i + 4] * x0[1] + H[rtDW->i] * x0[0]) + H
                          [rtDW->i + 8] * x0[2]) + H[rtDW->i + 12] * x0[3]) -
      f[rtDW->i];
    rtDW->xk[rtDW->i] = x0[rtDW->i];
    x[rtDW->i] = 0.0F;
  }

  /* '<S16>:1:58' iter = single(0); */
  *iter = 0.0F;

  /* '<S16>:1:59' J = single(42); */
  *J = 42.0F;

  /* '<S16>:1:60' optim_done = false; */
  optim_done = false;

  /* '<S16>:1:61' for k=0:max_iter */
  rtDW->k = 0;
  while (rtDW->k <= (int32_T)(max_iter + 1.0F) - 1) {
    /*      iter = k; */
    /* '<S16>:1:63' opt_criteria = abs(P_omega(xk-gk,Ts)-xk); */
    rtDW->xk_k[0] = rtDW->xk[0] - rtDW->gk[0];
    rtDW->xk_k[1] = rtDW->xk[1] - rtDW->gk[1];
    rtDW->xk_k[2] = rtDW->xk[2] - rtDW->gk[2];
    rtDW->xk_k[3] = rtDW->xk[3] - rtDW->gk[3];
    P_omega(rtDW->xk_k, Ts, rtDW->xkp1, rtDW);
    rtDW->opt_criteria[0] = fabsf(rtDW->xkp1[0] - rtDW->xk[0]);
    rtDW->opt_criteria[1] = fabsf(rtDW->xkp1[1] - rtDW->xk[1]);
    rtDW->opt_criteria[2] = fabsf(rtDW->xkp1[2] - rtDW->xk[2]);
    rtDW->opt_criteria[3] = fabsf(rtDW->xkp1[3] - rtDW->xk[3]);

    /* '<S16>:1:64' if (opt_criteria <= tol) */
    y = true;
    rtDW->b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (rtDW->b_k < 4)) {
      if (rtDW->opt_criteria[rtDW->b_k] > tol) {
        y = false;
        exitg1 = true;
      } else {
        rtDW->b_k++;
      }
    }

    if (y && (!optim_done)) {
      /* '<S16>:1:65' if (optim_done == false) */
      /* '<S16>:1:66' iter = k; */
      *iter = (real32_T)rtDW->k;

      /* '<S16>:1:67' x = xk; */
      /* '<S16>:1:68' J = x'*(M'*M)*x-2*r'*M*x; */
      for (rtDW->i = 0; rtDW->i < 4; rtDW->i++) {
        x[rtDW->i] = rtDW->xk[rtDW->i];
        for (rtDW->b_k = 0; rtDW->b_k < 4; rtDW->b_k++) {
          rtDW->M_tmp = rtDW->i + (rtDW->b_k << 2);
          rtDW->M_c[rtDW->M_tmp] = 0.0F;
          for (rtDW->i_p = 0; rtDW->i_p < 8; rtDW->i_p++) {
            rtDW->M_c[rtDW->M_tmp] += M[(rtDW->i << 3) + rtDW->i_p] * M
              [(rtDW->b_k << 3) + rtDW->i_p];
          }
        }
      }

      rtDW->xk_c = 0.0F;
      rtDW->opt_criteria_b = 0.0F;
      for (rtDW->b_k = 0; rtDW->b_k < 4; rtDW->b_k++) {
        rtDW->i = rtDW->b_k << 2;
        rtDW->xk_c += (rtDW->M_c[rtDW->i + 3] * rtDW->xk[3] + (rtDW->M_c[rtDW->i
          + 2] * rtDW->xk[2] + (rtDW->M_c[rtDW->i + 1] * rtDW->xk[1] + rtDW->
          M_c[rtDW->i] * rtDW->xk[0]))) * rtDW->xk[rtDW->b_k];
        rtDW->xkp1[rtDW->b_k] = 0.0F;
        for (rtDW->i_p = 0; rtDW->i_p < 8; rtDW->i_p++) {
          rtDW->xkp1[rtDW->b_k] += M[(rtDW->b_k << 3) + rtDW->i_p] * (2.0F *
            r[rtDW->i_p]);
        }

        rtDW->opt_criteria_b += rtDW->xkp1[rtDW->b_k] * rtDW->xk[rtDW->b_k];
      }

      *J = rtDW->xk_c - rtDW->opt_criteria_b;

      /*          break; */
      /* '<S16>:1:70' optim_done = true; */
      optim_done = true;
    }

    /* '<S16>:1:74' xkp1 = P_omega(xk-alphak*gk,Ts); */
    rtDW->xk_k[0] = rtDW->xk[0] - rtDW->alphak * rtDW->gk[0];
    rtDW->xk_k[1] = rtDW->xk[1] - rtDW->alphak * rtDW->gk[1];
    rtDW->xk_k[2] = rtDW->xk[2] - rtDW->alphak * rtDW->gk[2];
    rtDW->xk_k[3] = rtDW->xk[3] - rtDW->alphak * rtDW->gk[3];
    P_omega(rtDW->xk_k, Ts, rtDW->xkp1, rtDW);

    /* '<S16>:1:75' gkp1 = H*xkp1-f; */
    /* '<S16>:1:76' dxk = xkp1-xk; */
    /* '<S16>:1:77' dgk = gkp1-gk; */
    /* '<S16>:1:78' alphakp1 = (dxk'*dxk)/(dxk'*dgk); */
    /*  assign values for next iteration */
    /* '<S16>:1:80' xk = xkp1; */
    /* '<S16>:1:81' gk = gkp1; */
    /* '<S16>:1:82' alphak = alphakp1; */
    rtDW->alphak = 0.0F;
    rtDW->xk_c = 0.0F;
    for (rtDW->i = 0; rtDW->i < 4; rtDW->i++) {
      rtDW->opt_criteria_b = (((H[rtDW->i + 4] * rtDW->xkp1[1] + H[rtDW->i] *
        rtDW->xkp1[0]) + H[rtDW->i + 8] * rtDW->xkp1[2]) + H[rtDW->i + 12] *
        rtDW->xkp1[3]) - f[rtDW->i];
      rtDW->dxk = rtDW->xkp1[rtDW->i] - rtDW->xk[rtDW->i];
      rtDW->alphak += rtDW->dxk * rtDW->dxk;
      rtDW->xk_c += (rtDW->opt_criteria_b - rtDW->gk[rtDW->i]) * rtDW->dxk;
      rtDW->xk[rtDW->i] = rtDW->xkp1[rtDW->i];
      rtDW->gk[rtDW->i] = rtDW->opt_criteria_b;
    }

    rtDW->alphak /= rtDW->xk_c;
    rtDW->k++;
  }
}

/* Model step function */
void impl_modul_mpc_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  boolean_T rtb_unsuited;
  boolean_T rtb_unsuited_c;
  boolean_T rtb_unsuited_f;
  boolean_T rtb_unsuited_k;
  boolean_T rtb_unsuited_m;
  boolean_T rtb_unsuited_o;
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
  /* MATLAB Function 'impl_modul_mpc/seq_2_act_sw_all': '<S17>:1' */
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
  /* MATLAB Function 'impl_modul_mpc/act_sw_2_dq_volts_all': '<S2>:1' */
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
                 rtDW->H_a, rtDW->f_o, rtDW->M_k, rtDW->r_g,
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
                 rtDW->H_j, rtDW->f_j, rtDW->M_f, rtDW->r_im,
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
                 rtDW->H_l, rtDW->f_kb, rtDW->M_h, rtDW->r_i,
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
                 rtDW->H_b, rtDW->f_b, rtDW->M_l, rtDW->r_h,
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
                 rtDW->H_n, rtDW->f_k, rtDW->M_p, rtDW->r_e,
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
  detect_unsuited_sequence_1(rtDW->H_a, rtDW->f_o, &rtb_unsuited_k);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_2' */
  detect_unsuited_sequence_1(rtDW->H_j, rtDW->f_j, &rtb_unsuited_o);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_3' */
  detect_unsuited_sequence_1(rtDW->H_l, rtDW->f_kb, &rtb_unsuited_f);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_4' */
  detect_unsuited_sequence_1(rtDW->H_b, rtDW->f_b, &rtb_unsuited_m);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_5' */
  detect_unsuited_sequence_1(rtDW->H_n, rtDW->f_k, &rtb_unsuited_c);

  /* MATLAB Function: '<S1>/detect_unsuited_sequence_6' */
  detect_unsuited_sequence_1(rtDW->H, rtDW->f, &rtb_unsuited);

  /* Sum: '<S1>/Sum of Elements' incorporates:
   *  MATLAB Function: '<S1>/qp_solver_for_suited_seq'
   *  SignalConversion generated from: '<S16>/ SFunction '
   */
  rtDW->tmpForInput_tmp[0] = rtb_unsuited_k;
  rtDW->tmpForInput_tmp[1] = rtb_unsuited_o;
  rtDW->tmpForInput_tmp[2] = rtb_unsuited_f;
  rtDW->tmpForInput_tmp[3] = rtb_unsuited_m;
  rtDW->tmpForInput_tmp[4] = rtb_unsuited_c;
  rtDW->tmpForInput_tmp[5] = rtb_unsuited;
  rtDW->u = 0U;
  for (rtDW->rtb_f_o_tmp = 0; rtDW->rtb_f_o_tmp < 6; rtDW->rtb_f_o_tmp++) {
    rtDW->u += rtDW->tmpForInput_tmp[rtDW->rtb_f_o_tmp];
  }

  /* Delay: '<S1>/Delay4' */
  if (rtDW->icLoad) {
    rtDW->Delay4_DSTATE[0] = 0.25F;
    rtDW->Delay4_DSTATE[1] = 0.25F;
    rtDW->Delay4_DSTATE[2] = 0.25F;
    rtDW->Delay4_DSTATE[3] = 0.25F;
  }

  /* MATLAB Function: '<S1>/qp_solver_for_suited_seq' */
  /* MATLAB Function 'impl_modul_mpc/qp_solver_for_suited_seq': '<S16>:1' */
  /* '<S16>:1:3' j=zeros(1); */
  /* '<S16>:1:5' x1 = single([0.5 0 0 0.5]'); */
  /* '<S16>:1:6' x2 = x1; */
  /* '<S16>:1:7' x3 = x2; */
  /* '<S16>:1:8' x4 = x3; */
  /* '<S16>:1:9' x5 = x4; */
  /* '<S16>:1:10' x6 = x5; */
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

  /* '<S16>:1:12' J1 = single(42); */
  rtDW->SinCos1_o1 = 42.0F;

  /* MATLAB Function: '<S1>/min_Costs' incorporates:
   *  MATLAB Function: '<S1>/qp_solver_for_suited_seq'
   */
  /* '<S16>:1:13' J2 = J1; */
  rtDW->J_1to6[1] = 42.0F;

  /* '<S16>:1:14' J3 = J2; */
  rtDW->J_1to6[2] = 42.0F;

  /* '<S16>:1:15' J4 = J3; */
  rtDW->J_1to6[3] = 42.0F;

  /* '<S16>:1:16' J5 = J4; */
  rtDW->J_1to6[4] = 42.0F;

  /* '<S16>:1:17' J6 = J5; */
  rtDW->J_1to6[5] = 42.0F;

  /* Outport: '<Root>/iterations_qp' incorporates:
   *  MATLAB Function: '<S1>/qp_solver_for_suited_seq'
   */
  /* '<S16>:1:19' iter1 = single(0); */
  rtY->iterations_qp[0] = 0.0F;

  /* '<S16>:1:20' iter2 = iter1; */
  rtY->iterations_qp[1] = 0.0F;

  /* '<S16>:1:21' iter3 = iter2; */
  rtY->iterations_qp[2] = 0.0F;

  /* '<S16>:1:22' iter4 = iter3; */
  rtY->iterations_qp[3] = 0.0F;

  /* '<S16>:1:23' iter5 = iter4; */
  rtY->iterations_qp[4] = 0.0F;

  /* '<S16>:1:24' iter6 = iter5; */
  rtY->iterations_qp[5] = 0.0F;

  /* MATLAB Function: '<S1>/qp_solver_for_suited_seq' incorporates:
   *  Sum: '<S1>/Sum of Elements'
   */
  /* '<S16>:1:27' if (sum_of_unsuited == 4 || sum_of_unsuited == 5) */
  if (((uint8_T)rtDW->u == 4) || ((uint8_T)rtDW->u == 5)) {
    /* '<S16>:1:28' if (unsuited(1) == false) */
    if (!rtb_unsuited_k) {
      /* Outport: '<Root>/iterations_qp' incorporates:
       *  Constant: '<S1>/Constant1'
       *  Delay: '<S1>/Delay4'
       *  Inport: '<Root>/alpha0'
       *  Inport: '<Root>/max_iter'
       *  Inport: '<Root>/tolerance'
       */
      /* '<S16>:1:29' [x1,iter1,J1] = GradProj(H1,f1,x0,alpha0,tol,max_iter,M1,r1,Ts); */
      GradProj(rtDW->H_a, rtDW->f_o, rtDW->Delay4_DSTATE, rtU->alpha0,
               rtU->tolerance, rtU->max_iter, rtDW->M_k, rtDW->r_g, 1.0F,
               rtDW->x1, &rtY->iterations_qp[0], &rtDW->SinCos1_o1, rtDW);
    }

    /* '<S16>:1:31' if (unsuited(2) == false) */
    if (!rtb_unsuited_o) {
      /* Outport: '<Root>/iterations_qp' incorporates:
       *  Constant: '<S1>/Constant1'
       *  Delay: '<S1>/Delay4'
       *  Inport: '<Root>/alpha0'
       *  Inport: '<Root>/max_iter'
       *  Inport: '<Root>/tolerance'
       *  MATLAB Function: '<S1>/min_Costs'
       */
      /* '<S16>:1:32' [x2,iter2,J2] = GradProj(H2,f2,x0,alpha0,tol,max_iter,M2,r2,Ts); */
      GradProj(rtDW->H_j, rtDW->f_j, rtDW->Delay4_DSTATE, rtU->alpha0,
               rtU->tolerance, rtU->max_iter, rtDW->M_f, rtDW->r_im, 1.0F,
               rtDW->x2, &rtY->iterations_qp[1], &rtDW->J_1to6[1], rtDW);
    }

    /* '<S16>:1:34' if (unsuited(3) == false) */
    if (!rtb_unsuited_f) {
      /* Outport: '<Root>/iterations_qp' incorporates:
       *  Constant: '<S1>/Constant1'
       *  Delay: '<S1>/Delay4'
       *  Inport: '<Root>/alpha0'
       *  Inport: '<Root>/max_iter'
       *  Inport: '<Root>/tolerance'
       *  MATLAB Function: '<S1>/min_Costs'
       */
      /* '<S16>:1:35' [x3,iter3,J3] = GradProj(H3,f3,x0,alpha0,tol,max_iter,M3,r3,Ts); */
      GradProj(rtDW->H_l, rtDW->f_kb, rtDW->Delay4_DSTATE, rtU->alpha0,
               rtU->tolerance, rtU->max_iter, rtDW->M_h, rtDW->r_i, 1.0F,
               rtDW->x3, &rtY->iterations_qp[2], &rtDW->J_1to6[2], rtDW);
    }

    /* '<S16>:1:37' if (unsuited(4) == false) */
    if (!rtb_unsuited_m) {
      /* Outport: '<Root>/iterations_qp' incorporates:
       *  Constant: '<S1>/Constant1'
       *  Delay: '<S1>/Delay4'
       *  Inport: '<Root>/alpha0'
       *  Inport: '<Root>/max_iter'
       *  Inport: '<Root>/tolerance'
       *  MATLAB Function: '<S1>/min_Costs'
       */
      /* '<S16>:1:38' [x4,iter4,J4] = GradProj(H4,f4,x0,alpha0,tol,max_iter,M4,r4,Ts); */
      GradProj(rtDW->H_b, rtDW->f_b, rtDW->Delay4_DSTATE, rtU->alpha0,
               rtU->tolerance, rtU->max_iter, rtDW->M_l, rtDW->r_h, 1.0F,
               rtDW->x4, &rtY->iterations_qp[3], &rtDW->J_1to6[3], rtDW);
    }

    /* '<S16>:1:40' if (unsuited(5) == false) */
    if (!rtb_unsuited_c) {
      /* Outport: '<Root>/iterations_qp' incorporates:
       *  Constant: '<S1>/Constant1'
       *  Delay: '<S1>/Delay4'
       *  Inport: '<Root>/alpha0'
       *  Inport: '<Root>/max_iter'
       *  Inport: '<Root>/tolerance'
       *  MATLAB Function: '<S1>/min_Costs'
       */
      /* '<S16>:1:41' [x5,iter5,J5] = GradProj(H5,f5,x0,alpha0,tol,max_iter,M5,r5,Ts); */
      GradProj(rtDW->H_n, rtDW->f_k, rtDW->Delay4_DSTATE, rtU->alpha0,
               rtU->tolerance, rtU->max_iter, rtDW->M_p, rtDW->r_e, 1.0F,
               rtDW->x5, &rtY->iterations_qp[4], &rtDW->J_1to6[4], rtDW);
    }

    /* '<S16>:1:43' if (unsuited(6) == false) */
    if (!rtb_unsuited) {
      /* Outport: '<Root>/iterations_qp' incorporates:
       *  Constant: '<S1>/Constant1'
       *  Delay: '<S1>/Delay4'
       *  Inport: '<Root>/alpha0'
       *  Inport: '<Root>/max_iter'
       *  Inport: '<Root>/tolerance'
       *  MATLAB Function: '<S1>/min_Costs'
       */
      /* '<S16>:1:44' [x6,iter6,J6] = GradProj(H6,f6,x0,alpha0,tol,max_iter,M6,r6,Ts); */
      GradProj(rtDW->H, rtDW->f, rtDW->Delay4_DSTATE, rtU->alpha0,
               rtU->tolerance, rtU->max_iter, rtDW->M, rtDW->r, 1.0F, rtDW->x6,
               &rtY->iterations_qp[5], &rtDW->J_1to6[5], rtDW);
    }
  }

  /* MATLAB Function: '<S1>/min_Costs' incorporates:
   *  MATLAB Function: '<S1>/tz_2_tph'
   */
  /* MATLAB Function 'impl_modul_mpc/min_Costs': '<S15>:1' */
  /* '<S15>:1:3' J_1to6 = single([J1,J2,J3,J4,J5,J6]); */
  rtDW->J_1to6[0] = rtDW->SinCos1_o1;

  /* '<S15>:1:4' x_1to6 = single([x1,x2,x3,x4,x5,x6]); */
  /*  [~,idx] = min(J_1to6); */
  /* '<S15>:1:6' [~,idx] = minimum(J_1to6); */
  /* '<S15>:1:12' min_tmp = X(1); */
  /* '<S15>:1:13' idx_tmp = 1; */
  rtDW->idx_tmp = 1;

  /* '<S15>:1:14' for i=1:6 */
  for (rtDW->rtb_f_o_tmp = 0; rtDW->rtb_f_o_tmp < 6; rtDW->rtb_f_o_tmp++) {
    rtDW->SinCos1_o2 = rtDW->J_1to6[rtDW->rtb_f_o_tmp];

    /* '<S15>:1:15' if(X(i) < min_tmp) */
    if (rtDW->SinCos1_o2 < rtDW->SinCos1_o1) {
      /* '<S15>:1:16' min_tmp = X(i); */
      rtDW->SinCos1_o1 = rtDW->SinCos1_o2;

      /* '<S15>:1:17' idx_tmp = i; */
      rtDW->idx_tmp = rtDW->rtb_f_o_tmp + 1;
    }
  }

  /* '<S15>:1:20' min = min_tmp; */
  /* '<S15>:1:21' idx = idx_tmp; */
  /* '<S15>:1:7' x_opt = single(x_1to6(:,idx)); */
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
  rtDW->rtb_f_o_tmp = (rtDW->idx_tmp - 1) << 2;
  rtDW->f_o[0] = rtDW->rtb_x1_m[rtDW->rtb_f_o_tmp];
  rtDW->f_o[1] = rtDW->rtb_x1_m[rtDW->rtb_f_o_tmp + 1];
  rtDW->f_o[2] = rtDW->rtb_x1_m[rtDW->rtb_f_o_tmp + 2];
  rtDW->f_o[3] = rtDW->rtb_x1_m[rtDW->rtb_f_o_tmp + 3];

  /* MATLAB Function: '<S1>/tz' */
  /* '<S15>:1:8' idx_opt = single(idx); */
  /* MATLAB Function 'impl_modul_mpc/tz': '<S24>:1' */
  /* '<S24>:1:3' I = single([1 0 0; */
  /* '<S24>:1:4'      1 1 0; */
  /* '<S24>:1:5'      1 1 1]); */
  /* '<S24>:1:7' zer3 = single(zeros(3,1)); */
  /* '<S24>:1:9' T = single([I zer3]); */
  /* '<S24>:1:11' tz=single(T*x); */
  for (rtDW->rtb_f_o_tmp = 0; rtDW->rtb_f_o_tmp < 3; rtDW->rtb_f_o_tmp++) {
    rtDW->tz[rtDW->rtb_f_o_tmp] = (real32_T)a[rtDW->rtb_f_o_tmp + 9] * rtDW->
      f_o[3] + ((real32_T)a[rtDW->rtb_f_o_tmp + 6] * rtDW->f_o[2] + ((real32_T)
      a[rtDW->rtb_f_o_tmp + 3] * rtDW->f_o[1] + (real32_T)a[rtDW->rtb_f_o_tmp] *
      rtDW->f_o[0]));
  }

  /* End of MATLAB Function: '<S1>/tz' */

  /* Outport: '<Root>/CMPA_opt' incorporates:
   *  MATLAB Function: '<S1>/min_Costs'
   *  MATLAB Function: '<S1>/tz_2_tph'
   */
  /* MATLAB Function 'impl_modul_mpc/tz_2_tph': '<S25>:1' */
  /* '<S25>:1:3' seq_order_table = single([1 2 3; */
  /* '<S25>:1:4'                    2 1 3; */
  /* '<S25>:1:5'                    3 1 2; */
  /* '<S25>:1:6'                    3 2 1; */
  /* '<S25>:1:7'                    2 3 1; */
  /* '<S25>:1:8'                    1 3 2]); */
  /* '<S25>:1:10' ta_1 = single(tz(seq_order_table(seq_no,1))); */
  /* '<S25>:1:11' tb_1 = single(tz(seq_order_table(seq_no,2))); */
  /* '<S25>:1:12' tc_1 = single(tz(seq_order_table(seq_no,3))); */
  rtY->CMPA_opt[0] = rtDW->tz[seq_order_table[rtDW->idx_tmp - 1] - 1];
  rtY->CMPA_opt[1] = rtDW->tz[seq_order_table[rtDW->idx_tmp + 5] - 1];
  rtY->CMPA_opt[2] = rtDW->tz[seq_order_table[rtDW->idx_tmp + 11] - 1];

  /* Outport: '<Root>/unsuited_qp' */
  rtY->unsuited_qp[0] = rtb_unsuited_k;
  rtY->unsuited_qp[1] = rtb_unsuited_o;
  rtY->unsuited_qp[2] = rtb_unsuited_f;
  rtY->unsuited_qp[3] = rtb_unsuited_m;
  rtY->unsuited_qp[4] = rtb_unsuited_c;
  rtY->unsuited_qp[5] = rtb_unsuited;

  /* Update for Delay: '<S1>/Delay4' */
  rtDW->icLoad = false;
  rtDW->Delay4_DSTATE[0] = rtDW->f_o[0];
  rtDW->Delay4_DSTATE[1] = rtDW->f_o[1];
  rtDW->Delay4_DSTATE[2] = rtDW->f_o[2];
  rtDW->Delay4_DSTATE[3] = rtDW->f_o[3];
}

/* Model initialize function */
void impl_modul_mpc_initialize(RT_MODEL *const rtM)
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

  /* InitializeConditions for Delay: '<S1>/Delay4' */
  rtDW->icLoad = true;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
