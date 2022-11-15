/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 4.4
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Fri Nov 11 16:27:55 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (9), Warning (1), Errors (2)
 */

#include "uz_codegen0.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>

static void SwitchCaseActionSubsystem3(real32_T *rty_Out1);
static void MATLABFunction(real32_T rtu_i_im, real32_T rtu_w, boolean_T
  *rty_Betrieb);
static void MATLABFunction_i(creal32_T rtu_Psi_PM_U, creal32_T rtu_Psi_PM_V,
  creal32_T rtu_Psi_PM_W, real32_T rtu_I_re, real32_T rtu_I_im, real32_T
  rtu_omega_el, uint8_T rtu_enable, real32_T *rty_I_re_mit, real32_T
  *rty_I_im_mit, real32_T *rty_I_re_gegen, real32_T *rty_I_im_gegen, real32_T
  *rty_I_re_null, real32_T *rty_I_im_null, DW_MATLABFunction_m *localDW);
static void MATLABFunction_c(real32_T rtu_re, real32_T rtu_U_lim, real32_T
  rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim);
static void MATLABFunction_a(real32_T rtu_re, real32_T rtu_U_lim, boolean_T
  rtu_Betrieb, real32_T rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim);
static void Strangstromregler_asymetri_Init(DW_Strangstromregler_asymetrisc
  *localDW);
static void Strangstromregler_asymetr_Reset(DW_Strangstromregler_asymetrisc
  *localDW);
static void Strangstromregler_asymetrisch(real32_T rtu_I_re, real32_T rtu_I_im,
  real32_T rtu_I_S, real32_T rtu_w1, real32_T rtu_U_ZK1, uint8_T
  rtu_enable_compensation_current, real32_T rtu_Theta_u, real32_T
  rtu_Theta_u_back, real32_T rtu_I_im_CT, creal32_T rtu_Psi_PM, creal32_T
  rtu_Psi_PM_n, creal32_T rtu_Psi_PM_k, real32_T *rty_a, real32_T *rty_I_ref1,
  real32_T rtp_Offset_S, real32_T rtp_Offset_gegen, real32_T rtp_Offset_null,
  DW_Strangstromregler_asymetrisc *localDW);
static void SwitchCaseActionSubsystem(real32_T *rty_a, real32_T *rty_Iref);

/*
 * Output and update for action system:
 *    '<S8>/Switch Case Action Subsystem3'
 *    '<S8>/Switch Case Action Subsystem2'
 */
static void SwitchCaseActionSubsystem3(real32_T *rty_Out1)
{
  /* SignalConversion generated from: '<S21>/Out1' incorporates:
   *  Constant: '<S21>/Constant'
   */
  *rty_Out1 = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S23>/MATLAB Function'
 *    '<S24>/MATLAB Function'
 *    '<S25>/MATLAB Function'
 */
static void MATLABFunction(real32_T rtu_i_im, real32_T rtu_w, boolean_T
  *rty_Betrieb)
{
  real32_T rtu_i_im_0;
  real32_T rtu_w_0;

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/Strangstromregler_asymetrisch/MATLAB Function': '<S29>:1' */
  /* '<S29>:1:2' if sign(i_im) == sign(w) */
  if (rtu_i_im < 0.0F) {
    rtu_i_im_0 = -1.0F;
  } else {
    rtu_i_im_0 = (real32_T)(rtu_i_im > 0.0F);
  }

  if (rtu_w < 0.0F) {
    rtu_w_0 = -1.0F;
  } else {
    rtu_w_0 = (real32_T)(rtu_w > 0.0F);
  }

  if (rtu_i_im_0 == rtu_w_0) {
    /* '<S29>:1:3' Betrieb = boolean(1); */
    *rty_Betrieb = true;

    /* Motorisch */
  } else {
    /* '<S29>:1:4' else */
    /* '<S29>:1:5' Betrieb = boolean(0); */
    *rty_Betrieb = false;

    /* Generatorisch */
  }
}

/*
 * Output and update for atomic system:
 *    '<S30>/MATLAB Function'
 *    '<S43>/MATLAB Function'
 *    '<S56>/MATLAB Function'
 */
static void MATLABFunction_i(creal32_T rtu_Psi_PM_U, creal32_T rtu_Psi_PM_V,
  creal32_T rtu_Psi_PM_W, real32_T rtu_I_re, real32_T rtu_I_im, real32_T
  rtu_omega_el, uint8_T rtu_enable, real32_T *rty_I_re_mit, real32_T
  *rty_I_im_mit, real32_T *rty_I_re_gegen, real32_T *rty_I_im_gegen, real32_T
  *rty_I_re_null, real32_T *rty_I_im_null, DW_MATLABFunction_m *localDW)
{
  static const creal32_T a[9] = { { 0.333333284F,/* re */
      0.0F                             /* im */
    }, { 0.333333343F,                 /* re */
      0.0F                             /* im */
    }, { 0.333333343F,                 /* re */
      0.0F                             /* im */
    }, { -0.166666672F,                /* re */
      0.288675129F                     /* im */
    }, { -0.166666672F,                /* re */
      -0.288675129F                    /* im */
    }, { 0.333333343F,                 /* re */
      0.0F                             /* im */
    }, { -0.166666672F,                /* re */
      -0.288675129F                    /* im */
    }, { -0.166666672F,                /* re */
      0.288675129F                     /* im */
    }, { 0.333333343F,                 /* re */
      0.0F                             /* im */
    } };

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/Referenzstromerzeugung_asymetrisch/MATLAB Function': '<S36>:1' */
  /*  Up = Polradspannung, induced Voltage, back emf (als komplexen Vektor) */
  /*  i_q =  referenz q-Strom (als reeler Wert) */
  /* '<S36>:1:4' if enable == 1 */
  if (rtu_enable == 1) {
    real32_T I_V_im;
    real32_T I_V_im_tmp;
    real32_T I_V_re_tmp;
    real32_T I_V_re_tmp_0;
    real32_T I_W_im;
    real32_T U_sym_komp_hilf_tmp;
    real32_T U_sym_komp_hilf_tmp_0;
    real32_T U_sym_komp_idx_4_im;
    real32_T U_sym_komp_idx_4_re;
    real32_T U_sym_komp_idx_7_im;
    real32_T U_sym_komp_idx_7_re;
    real32_T bi_tmp;
    real32_T bim;
    real32_T brm;
    real32_T rtu_Psi_PM_U_idx_0_im;
    real32_T rtu_Psi_PM_U_idx_0_re;

    /* '<S36>:1:5' p=18; */
    /*  Polpaarzahl */
    /*     %% Matrizen für symetrische Komponenten */
    /*  */
    /* '<S36>:1:8' a=single(exp(1i*(2*pi/3))); */
    /* '<S36>:1:9' T=single([1   1   1;  a^2 a   1; a   a^2 1]); */
    /*     %% Eingangsvektoren */
    /* '<S36>:1:11' U=[Psi_PM_U; Psi_PM_V;Psi_PM_W].*omega_el; */
    /* '<S36>:1:12' I_U=single(I_im*exp(1i*(-0*pi/3))); */
    /* '<S36>:1:13' I_V=single(I_im*exp(1i*(-2*pi/3))); */
    I_V_re_tmp = rtu_I_im * -0.5F;
    I_V_im = rtu_I_im * -0.866025388F;

    /* '<S36>:1:14' I_W=single(I_im*exp(1i*(-4*pi/3))); */
    I_W_im = rtu_I_im * 0.866025388F;

    /* '<S36>:1:15' I=single([I_U;I_V;I_W]); */
    /*  Symetrische Komponenten von Spannung */
    /*  Komponenten (1. Dimensoin -> Mit.-,Gegen-,Nullkomponente; 2. Dimension -> */
    /*  Phase 1,2,3 */
    /*  */
    /* '<S36>:1:20' U_sym_komp_hilf=single((inv(T)*U)); */
    rtu_Psi_PM_U_idx_0_re = rtu_omega_el * rtu_Psi_PM_U.re;
    rtu_Psi_PM_U_idx_0_im = rtu_omega_el * rtu_Psi_PM_U.im;
    U_sym_komp_idx_4_im = rtu_omega_el * rtu_Psi_PM_V.re;
    U_sym_komp_idx_7_re = rtu_omega_el * rtu_Psi_PM_V.im;
    U_sym_komp_idx_7_im = rtu_omega_el * rtu_Psi_PM_W.re;
    U_sym_komp_idx_4_re = rtu_omega_el * rtu_Psi_PM_W.im;
    for (localDW->i = 0; localDW->i < 3; localDW->i++) {
      U_sym_komp_hilf_tmp = a[localDW->i].re;
      U_sym_komp_hilf_tmp_0 = a[localDW->i].im;
      localDW->U_sym_komp_hilf_m.re = U_sym_komp_hilf_tmp *
        rtu_Psi_PM_U_idx_0_re - U_sym_komp_hilf_tmp_0 * rtu_Psi_PM_U_idx_0_im;
      localDW->U_sym_komp_hilf_m.im = U_sym_komp_hilf_tmp *
        rtu_Psi_PM_U_idx_0_im + U_sym_komp_hilf_tmp_0 * rtu_Psi_PM_U_idx_0_re;
      U_sym_komp_hilf_tmp = a[localDW->i + 3].re;
      U_sym_komp_hilf_tmp_0 = a[localDW->i + 3].im;
      localDW->U_sym_komp_hilf_m.re += U_sym_komp_hilf_tmp * U_sym_komp_idx_4_im
        - U_sym_komp_hilf_tmp_0 * U_sym_komp_idx_7_re;
      localDW->U_sym_komp_hilf_m.im += U_sym_komp_hilf_tmp * U_sym_komp_idx_7_re
        + U_sym_komp_hilf_tmp_0 * U_sym_komp_idx_4_im;
      U_sym_komp_hilf_tmp = a[localDW->i + 6].re;
      U_sym_komp_hilf_tmp_0 = a[localDW->i + 6].im;
      localDW->U_sym_komp_hilf_m.re += U_sym_komp_hilf_tmp * U_sym_komp_idx_7_im
        - U_sym_komp_hilf_tmp_0 * U_sym_komp_idx_4_re;
      localDW->U_sym_komp_hilf_m.im += U_sym_komp_hilf_tmp * U_sym_komp_idx_4_re
        + U_sym_komp_hilf_tmp_0 * U_sym_komp_idx_7_im;
      localDW->U_sym_komp_hilf[localDW->i] = localDW->U_sym_komp_hilf_m;
    }

    /* .*[1 a^2 a; 1 a a^2;1 1 1]); */
    /* '<S36>:1:21' U_sym_komp=single(zeros(3,3)*(0+0i)); */
    /*  Mitkomponente */
    /* '<S36>:1:23' U_sym_komp(1,1)=single(U_sym_komp_hilf(1)*1); */
    /* '<S36>:1:24' U_sym_komp(1,2)=single(U_sym_komp_hilf(1)*a^2); */
    /* '<S36>:1:25' U_sym_komp(1,3)=single(U_sym_komp_hilf(1)*a); */
    /*  Gegenkomponente */
    /* '<S36>:1:27' U_sym_komp(2,1)=single(U_sym_komp_hilf(2)*1); */
    /* '<S36>:1:28' U_sym_komp(2,2)=single(U_sym_komp_hilf(2)*a); */
    rtu_Psi_PM_U_idx_0_im = localDW->U_sym_komp_hilf[1].re * -0.5F;
    U_sym_komp_idx_4_re = rtu_Psi_PM_U_idx_0_im - localDW->U_sym_komp_hilf[1].im
      * 0.866025388F;
    rtu_Psi_PM_U_idx_0_re = localDW->U_sym_komp_hilf[1].im * -0.5F;
    U_sym_komp_idx_4_im = localDW->U_sym_komp_hilf[1].re * 0.866025388F +
      rtu_Psi_PM_U_idx_0_re;

    /* '<S36>:1:29' U_sym_komp(2,3)=single(U_sym_komp_hilf(2)*a^2); */
    U_sym_komp_idx_7_re = rtu_Psi_PM_U_idx_0_im - localDW->U_sym_komp_hilf[1].im
      * -0.866025388F;
    U_sym_komp_idx_7_im = localDW->U_sym_komp_hilf[1].re * -0.866025388F +
      rtu_Psi_PM_U_idx_0_re;

    /*  Nullkomponente */
    /* '<S36>:1:31' U_sym_komp(3,1)=single(U_sym_komp_hilf(3)*1); */
    /* '<S36>:1:32' U_sym_komp(3,2)=single(U_sym_komp_hilf(3)*1); */
    /* '<S36>:1:33' U_sym_komp(3,3)=single(U_sym_komp_hilf(3)*1); */
    /*     %% Kompensation von U_g+U_0 */
    /* '<S36>:1:35' I_Gegen_U=single(-(I_U*(U_sym_komp(2,1)+U_sym_komp(3,1)))/(U_sym_komp(1,1)+U_sym_komp(2,1)+U_sym_komp(3,1))); */
    /* '<S36>:1:36' I_Gegen_V=single(-(I_V*(U_sym_komp(2,2)+U_sym_komp(3,2)))/(U_sym_komp(1,2)+U_sym_komp(2,2)+U_sym_komp(3,2))); */
    /* '<S36>:1:37' I_Gegen_W=single(-(I_W*(U_sym_komp(2,3)+U_sym_komp(3,3)))/(U_sym_komp(1,3)+U_sym_komp(2,3)+U_sym_komp(3,3))); */
    /* '<S36>:1:38' I_Mit=single(I); */
    /*  */
    /* '<S36>:1:40' I_Gegen=single([I_Gegen_U; I_Gegen_V; I_Gegen_W]); */
    /* '<S36>:1:41' I_compensation=single((I_Gegen+I_Mit)); */
    /* '<S36>:1:42' I_compensation_sym_components=single((inv(T)*I_compensation)); */
    /* .*[1 a^2 a; 1 a a^2;1 1 1])); */
    /* '<S36>:1:43' I_compensation_sym_components=single(I_compensation_sym_components.*exp(1i*(pi/2))); */
    rtu_Psi_PM_U_idx_0_im = (localDW->U_sym_komp_hilf[1].re +
      localDW->U_sym_komp_hilf[2].re) * rtu_I_im;
    U_sym_komp_hilf_tmp = (localDW->U_sym_komp_hilf[1].im +
      localDW->U_sym_komp_hilf[2].im) * rtu_I_im;
    localDW->br = (localDW->U_sym_komp_hilf[0].re + localDW->U_sym_komp_hilf[1].
                   re) + localDW->U_sym_komp_hilf[2].re;
    U_sym_komp_hilf_tmp_0 = (localDW->U_sym_komp_hilf[0].im +
      localDW->U_sym_komp_hilf[1].im) + localDW->U_sym_komp_hilf[2].im;
    if (U_sym_komp_hilf_tmp_0 == 0.0F) {
      if (-U_sym_komp_hilf_tmp == 0.0F) {
        rtu_Psi_PM_U_idx_0_re = -rtu_Psi_PM_U_idx_0_im / localDW->br;
        rtu_Psi_PM_U_idx_0_im = 0.0F;
      } else if (-rtu_Psi_PM_U_idx_0_im == 0.0F) {
        rtu_Psi_PM_U_idx_0_re = 0.0F;
        rtu_Psi_PM_U_idx_0_im = -U_sym_komp_hilf_tmp / localDW->br;
      } else {
        rtu_Psi_PM_U_idx_0_re = -rtu_Psi_PM_U_idx_0_im / localDW->br;
        rtu_Psi_PM_U_idx_0_im = -U_sym_komp_hilf_tmp / localDW->br;
      }
    } else if (localDW->br == 0.0F) {
      if (-rtu_Psi_PM_U_idx_0_im == 0.0F) {
        rtu_Psi_PM_U_idx_0_re = -U_sym_komp_hilf_tmp / U_sym_komp_hilf_tmp_0;
        rtu_Psi_PM_U_idx_0_im = 0.0F;
      } else if (-U_sym_komp_hilf_tmp == 0.0F) {
        rtu_Psi_PM_U_idx_0_re = 0.0F;
        rtu_Psi_PM_U_idx_0_im = -(-rtu_Psi_PM_U_idx_0_im / U_sym_komp_hilf_tmp_0);
      } else {
        rtu_Psi_PM_U_idx_0_re = -U_sym_komp_hilf_tmp / U_sym_komp_hilf_tmp_0;
        rtu_Psi_PM_U_idx_0_im = -(-rtu_Psi_PM_U_idx_0_im / U_sym_komp_hilf_tmp_0);
      }
    } else {
      brm = fabsf(localDW->br);
      bim = fabsf(U_sym_komp_hilf_tmp_0);
      if (brm > bim) {
        brm = U_sym_komp_hilf_tmp_0 / localDW->br;
        U_sym_komp_hilf_tmp_0 = brm * U_sym_komp_hilf_tmp_0 + localDW->br;
        rtu_Psi_PM_U_idx_0_re = (brm * -U_sym_komp_hilf_tmp +
          -rtu_Psi_PM_U_idx_0_im) / U_sym_komp_hilf_tmp_0;
        rtu_Psi_PM_U_idx_0_im = (-U_sym_komp_hilf_tmp - brm *
          -rtu_Psi_PM_U_idx_0_im) / U_sym_komp_hilf_tmp_0;
      } else if (bim == brm) {
        localDW->br = localDW->br > 0.0F ? 0.5F : -0.5F;
        U_sym_komp_hilf_tmp_0 = U_sym_komp_hilf_tmp_0 > 0.0F ? 0.5F : -0.5F;
        rtu_Psi_PM_U_idx_0_re = (-rtu_Psi_PM_U_idx_0_im * localDW->br +
          -U_sym_komp_hilf_tmp * U_sym_komp_hilf_tmp_0) / brm;
        rtu_Psi_PM_U_idx_0_im = (-U_sym_komp_hilf_tmp * localDW->br -
          -rtu_Psi_PM_U_idx_0_im * U_sym_komp_hilf_tmp_0) / brm;
      } else {
        brm = localDW->br / U_sym_komp_hilf_tmp_0;
        U_sym_komp_hilf_tmp_0 += brm * localDW->br;
        rtu_Psi_PM_U_idx_0_re = (brm * -rtu_Psi_PM_U_idx_0_im +
          -U_sym_komp_hilf_tmp) / U_sym_komp_hilf_tmp_0;
        rtu_Psi_PM_U_idx_0_im = (brm * -U_sym_komp_hilf_tmp -
          (-rtu_Psi_PM_U_idx_0_im)) / U_sym_komp_hilf_tmp_0;
      }
    }

    U_sym_komp_hilf_tmp = U_sym_komp_idx_4_re + localDW->U_sym_komp_hilf[2].re;
    U_sym_komp_hilf_tmp_0 = U_sym_komp_idx_4_im + localDW->U_sym_komp_hilf[2].im;
    I_V_re_tmp_0 = I_V_re_tmp * U_sym_komp_hilf_tmp - I_V_im *
      U_sym_komp_hilf_tmp_0;
    I_V_im_tmp = I_V_re_tmp * U_sym_komp_hilf_tmp_0 + I_V_im *
      U_sym_komp_hilf_tmp;
    U_sym_komp_hilf_tmp = localDW->U_sym_komp_hilf[0].re * -0.5F;
    localDW->br = ((U_sym_komp_hilf_tmp - localDW->U_sym_komp_hilf[0].im *
                    -0.866025388F) + U_sym_komp_idx_4_re) +
      localDW->U_sym_komp_hilf[2].re;
    bi_tmp = localDW->U_sym_komp_hilf[0].im * -0.5F;
    U_sym_komp_hilf_tmp_0 = ((localDW->U_sym_komp_hilf[0].re * -0.866025388F +
      bi_tmp) + U_sym_komp_idx_4_im) + localDW->U_sym_komp_hilf[2].im;
    if (U_sym_komp_hilf_tmp_0 == 0.0F) {
      if (-I_V_im_tmp == 0.0F) {
        U_sym_komp_idx_4_im = -I_V_re_tmp_0 / localDW->br;
        U_sym_komp_idx_4_re = 0.0F;
      } else if (-I_V_re_tmp_0 == 0.0F) {
        U_sym_komp_idx_4_im = 0.0F;
        U_sym_komp_idx_4_re = -I_V_im_tmp / localDW->br;
      } else {
        U_sym_komp_idx_4_im = -I_V_re_tmp_0 / localDW->br;
        U_sym_komp_idx_4_re = -I_V_im_tmp / localDW->br;
      }
    } else if (localDW->br == 0.0F) {
      if (-I_V_re_tmp_0 == 0.0F) {
        U_sym_komp_idx_4_im = -I_V_im_tmp / U_sym_komp_hilf_tmp_0;
        U_sym_komp_idx_4_re = 0.0F;
      } else if (-I_V_im_tmp == 0.0F) {
        U_sym_komp_idx_4_im = 0.0F;
        U_sym_komp_idx_4_re = -(-I_V_re_tmp_0 / U_sym_komp_hilf_tmp_0);
      } else {
        U_sym_komp_idx_4_im = -I_V_im_tmp / U_sym_komp_hilf_tmp_0;
        U_sym_komp_idx_4_re = -(-I_V_re_tmp_0 / U_sym_komp_hilf_tmp_0);
      }
    } else {
      brm = fabsf(localDW->br);
      bim = fabsf(U_sym_komp_hilf_tmp_0);
      if (brm > bim) {
        brm = U_sym_komp_hilf_tmp_0 / localDW->br;
        U_sym_komp_hilf_tmp_0 = brm * U_sym_komp_hilf_tmp_0 + localDW->br;
        U_sym_komp_idx_4_im = (brm * -I_V_im_tmp + -I_V_re_tmp_0) /
          U_sym_komp_hilf_tmp_0;
        U_sym_komp_idx_4_re = (-I_V_im_tmp - brm * -I_V_re_tmp_0) /
          U_sym_komp_hilf_tmp_0;
      } else if (bim == brm) {
        localDW->br = localDW->br > 0.0F ? 0.5F : -0.5F;
        U_sym_komp_hilf_tmp_0 = U_sym_komp_hilf_tmp_0 > 0.0F ? 0.5F : -0.5F;
        U_sym_komp_idx_4_im = (-I_V_re_tmp_0 * localDW->br + -I_V_im_tmp *
          U_sym_komp_hilf_tmp_0) / brm;
        U_sym_komp_idx_4_re = (-I_V_im_tmp * localDW->br - -I_V_re_tmp_0 *
          U_sym_komp_hilf_tmp_0) / brm;
      } else {
        brm = localDW->br / U_sym_komp_hilf_tmp_0;
        U_sym_komp_hilf_tmp_0 += brm * localDW->br;
        U_sym_komp_idx_4_im = (brm * -I_V_re_tmp_0 + -I_V_im_tmp) /
          U_sym_komp_hilf_tmp_0;
        U_sym_komp_idx_4_re = (brm * -I_V_im_tmp - (-I_V_re_tmp_0)) /
          U_sym_komp_hilf_tmp_0;
      }
    }

    U_sym_komp_hilf_tmp_0 = U_sym_komp_idx_7_re + localDW->U_sym_komp_hilf[2].re;
    brm = U_sym_komp_idx_7_im + localDW->U_sym_komp_hilf[2].im;
    I_V_re_tmp_0 = I_V_re_tmp * U_sym_komp_hilf_tmp_0 - I_W_im * brm;
    I_V_im_tmp = I_V_re_tmp * brm + I_W_im * U_sym_komp_hilf_tmp_0;
    localDW->br = ((U_sym_komp_hilf_tmp - localDW->U_sym_komp_hilf[0].im *
                    0.866025388F) + U_sym_komp_idx_7_re) +
      localDW->U_sym_komp_hilf[2].re;
    U_sym_komp_hilf_tmp_0 = ((localDW->U_sym_komp_hilf[0].re * 0.866025388F +
      bi_tmp) + U_sym_komp_idx_7_im) + localDW->U_sym_komp_hilf[2].im;
    if (U_sym_komp_hilf_tmp_0 == 0.0F) {
      if (-I_V_im_tmp == 0.0F) {
        U_sym_komp_idx_7_re = -I_V_re_tmp_0 / localDW->br;
        U_sym_komp_idx_7_im = 0.0F;
      } else if (-I_V_re_tmp_0 == 0.0F) {
        U_sym_komp_idx_7_re = 0.0F;
        U_sym_komp_idx_7_im = -I_V_im_tmp / localDW->br;
      } else {
        U_sym_komp_idx_7_re = -I_V_re_tmp_0 / localDW->br;
        U_sym_komp_idx_7_im = -I_V_im_tmp / localDW->br;
      }
    } else if (localDW->br == 0.0F) {
      if (-I_V_re_tmp_0 == 0.0F) {
        U_sym_komp_idx_7_re = -I_V_im_tmp / U_sym_komp_hilf_tmp_0;
        U_sym_komp_idx_7_im = 0.0F;
      } else if (-I_V_im_tmp == 0.0F) {
        U_sym_komp_idx_7_re = 0.0F;
        U_sym_komp_idx_7_im = -(-I_V_re_tmp_0 / U_sym_komp_hilf_tmp_0);
      } else {
        U_sym_komp_idx_7_re = -I_V_im_tmp / U_sym_komp_hilf_tmp_0;
        U_sym_komp_idx_7_im = -(-I_V_re_tmp_0 / U_sym_komp_hilf_tmp_0);
      }
    } else {
      brm = fabsf(localDW->br);
      bim = fabsf(U_sym_komp_hilf_tmp_0);
      if (brm > bim) {
        brm = U_sym_komp_hilf_tmp_0 / localDW->br;
        U_sym_komp_hilf_tmp_0 = brm * U_sym_komp_hilf_tmp_0 + localDW->br;
        U_sym_komp_idx_7_re = (brm * -I_V_im_tmp + -I_V_re_tmp_0) /
          U_sym_komp_hilf_tmp_0;
        U_sym_komp_idx_7_im = (-I_V_im_tmp - brm * -I_V_re_tmp_0) /
          U_sym_komp_hilf_tmp_0;
      } else if (bim == brm) {
        localDW->br = localDW->br > 0.0F ? 0.5F : -0.5F;
        U_sym_komp_hilf_tmp_0 = U_sym_komp_hilf_tmp_0 > 0.0F ? 0.5F : -0.5F;
        U_sym_komp_idx_7_re = (-I_V_re_tmp_0 * localDW->br + -I_V_im_tmp *
          U_sym_komp_hilf_tmp_0) / brm;
        U_sym_komp_idx_7_im = (-I_V_im_tmp * localDW->br - -I_V_re_tmp_0 *
          U_sym_komp_hilf_tmp_0) / brm;
      } else {
        brm = localDW->br / U_sym_komp_hilf_tmp_0;
        U_sym_komp_hilf_tmp_0 += brm * localDW->br;
        U_sym_komp_idx_7_re = (brm * -I_V_re_tmp_0 + -I_V_im_tmp) /
          U_sym_komp_hilf_tmp_0;
        U_sym_komp_idx_7_im = (brm * -I_V_im_tmp - (-I_V_re_tmp_0)) /
          U_sym_komp_hilf_tmp_0;
      }
    }

    rtu_Psi_PM_U_idx_0_re += rtu_I_im;
    U_sym_komp_idx_4_im += I_V_re_tmp;
    U_sym_komp_idx_4_re += I_V_im;
    U_sym_komp_idx_7_re += I_V_re_tmp;
    U_sym_komp_idx_7_im += I_W_im;
    for (localDW->i = 0; localDW->i < 3; localDW->i++) {
      I_V_re_tmp = a[localDW->i].re;
      I_V_im = a[localDW->i].im;
      I_W_im = a[localDW->i + 3].re;
      U_sym_komp_hilf_tmp = a[localDW->i + 3].im;
      U_sym_komp_hilf_tmp_0 = a[localDW->i + 6].re;
      brm = a[localDW->i + 6].im;
      localDW->a.re = ((I_W_im * U_sym_komp_idx_4_im - U_sym_komp_hilf_tmp *
                        U_sym_komp_idx_4_re) + (I_V_re_tmp *
        rtu_Psi_PM_U_idx_0_re - I_V_im * rtu_Psi_PM_U_idx_0_im)) +
        (U_sym_komp_hilf_tmp_0 * U_sym_komp_idx_7_re - brm * U_sym_komp_idx_7_im);
      localDW->a.im = ((I_W_im * U_sym_komp_idx_4_re + U_sym_komp_hilf_tmp *
                        U_sym_komp_idx_4_im) + (I_V_re_tmp *
        rtu_Psi_PM_U_idx_0_im + I_V_im * rtu_Psi_PM_U_idx_0_re)) +
        (U_sym_komp_hilf_tmp_0 * U_sym_komp_idx_7_im + brm * U_sym_komp_idx_7_re);
      localDW->U_sym_komp_hilf[localDW->i].re = localDW->a.re * 6.12323426E-17F
        - localDW->a.im;
      localDW->U_sym_komp_hilf[localDW->i].im = localDW->a.im * 6.12323426E-17F
        + localDW->a.re;
    }

    /*  Drehung um 90°, damit realteil =  drehmomentbildend */
    /*  */
    /*     %% Output as single */
    /* '<S36>:1:47' I_re_mit=single(real(I_compensation_sym_components(1,1))); */
    *rty_I_re_mit = localDW->U_sym_komp_hilf[0].re;

    /* '<S36>:1:48' I_im_mit=single(imag(I_compensation_sym_components(1,1))); */
    *rty_I_im_mit = localDW->U_sym_komp_hilf[0].im;

    /* '<S36>:1:49' I_re_gegen=single(real(I_compensation_sym_components(2,1))); */
    *rty_I_re_gegen = localDW->U_sym_komp_hilf[1].re;

    /* '<S36>:1:50' I_im_gegen=single(imag(I_compensation_sym_components(2,1))); */
    *rty_I_im_gegen = localDW->U_sym_komp_hilf[1].im;

    /* '<S36>:1:51' I_re_null=single(real(I_compensation_sym_components(3,1))); */
    *rty_I_re_null = localDW->U_sym_komp_hilf[2].re;

    /* '<S36>:1:52' I_im_null=single(imag(I_compensation_sym_components(3,1))); */
    *rty_I_im_null = localDW->U_sym_komp_hilf[2].im;

    /*  */
  } else {
    /* '<S36>:1:54' else */
    /*     %% Output as single */
    /* '<S36>:1:56' I_re_mit=single(I_re); */
    *rty_I_re_mit = rtu_I_re;

    /* '<S36>:1:57' I_im_mit=single(I_im); */
    *rty_I_im_mit = rtu_I_im;

    /* '<S36>:1:58' I_re_gegen=single(0); */
    *rty_I_re_gegen = 0.0F;

    /* '<S36>:1:59' I_im_gegen=single(0); */
    *rty_I_im_gegen = 0.0F;

    /* '<S36>:1:60' I_re_null=single(0); */
    *rty_I_re_null = 0.0F;

    /* '<S36>:1:61' I_im_null=single(0); */
    *rty_I_im_null = 0.0F;
  }
}

/*
 * Output and update for atomic system:
 *    '<S31>/MATLAB Function'
 *    '<S44>/MATLAB Function'
 *    '<S57>/MATLAB Function'
 */
static void MATLABFunction_c(real32_T rtu_re, real32_T rtu_U_lim, real32_T
  rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim)
{
  real32_T U_rel;

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/resonater-I-Regler/MATLAB Function': '<S37>:1' */
  /* '<S37>:1:2' U_abs = sqrt(re^2+im^2); */
  /* '<S37>:1:3' U_rel = U_abs/U_lim; */
  U_rel = sqrtf(rtu_re * rtu_re + rtu_im * rtu_im) / rtu_U_lim;

  /* '<S37>:1:4' if U_rel>=1 */
  if (U_rel >= 1.0F) {
    /* '<S37>:1:5' re_lim = re/U_rel; */
    *rty_re_lim = rtu_re / U_rel;

    /* '<S37>:1:6' im_lim = im/U_rel; */
    *rty_im_lim = rtu_im / U_rel;
  } else {
    /* '<S37>:1:7' else */
    /* '<S37>:1:8' re_lim = re; */
    *rty_re_lim = rtu_re;

    /* '<S37>:1:9' im_lim = im; */
    *rty_im_lim = rtu_im;
  }
}

/*
 * Output and update for atomic system:
 *    '<S32>/MATLAB Function'
 *    '<S33>/MATLAB Function'
 *    '<S34>/MATLAB Function'
 *    '<S35>/MATLAB Function'
 *    '<S45>/MATLAB Function'
 *    '<S46>/MATLAB Function'
 *    '<S47>/MATLAB Function'
 *    '<S48>/MATLAB Function'
 *    '<S58>/MATLAB Function'
 *    '<S59>/MATLAB Function'
 *    ...
 */
static void MATLABFunction_a(real32_T rtu_re, real32_T rtu_U_lim, boolean_T
  rtu_Betrieb, real32_T rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim)
{
  real32_T re_lim;
  real32_T rtu_im_0;
  real32_T tmp;

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/resonater-PI-Regler/MATLAB Function': '<S38>:1' */
  /* '<S38>:1:2' if (re^2 + im^2)<=U_lim^2 */
  tmp = rtu_U_lim * rtu_U_lim;
  if (rtu_re * rtu_re + rtu_im * rtu_im <= tmp) {
    /* '<S38>:1:3' re_lim = re; */
    re_lim = rtu_re;

    /* '<S38>:1:4' im_lim = im; */
    rtu_im_0 = rtu_im;
  } else if (!rtu_Betrieb) {
    /* '<S38>:1:5' elseif Betrieb == 0 */
    /* Generator */
    /* '<S38>:1:7' if abs(im)>0.95*U_lim */
    if (fabsf(rtu_im) > 0.95F * rtu_U_lim) {
      /* '<S38>:1:8' im_lim = sign(im)*0.95*U_lim; */
      if (rtu_im < 0.0F) {
        rtu_im_0 = -1.0F;
      } else {
        rtu_im_0 = (real32_T)(rtu_im > 0.0F);
      }

      rtu_im_0 = rtu_im_0 * 0.95F * rtu_U_lim;
    } else {
      /* '<S38>:1:9' else */
      /* '<S38>:1:10' im_lim = im; */
      rtu_im_0 = rtu_im;
    }

    /* '<S38>:1:12' re_lim = sign(re)*sqrt(U_lim^2 - im_lim^2); */
    if (rtu_re < 0.0F) {
      re_lim = -1.0F;
    } else {
      re_lim = (real32_T)(rtu_re > 0.0F);
    }

    re_lim *= sqrtf(tmp - rtu_im_0 * rtu_im_0);
  } else {
    /* '<S38>:1:13' else */
    /* Motor */
    /* '<S38>:1:15' if abs(re)>0.95*U_lim */
    if (fabsf(rtu_re) > 0.95F * rtu_U_lim) {
      /* '<S38>:1:16' re_lim = sign(re)*0.95*U_lim; */
      if (rtu_re < 0.0F) {
        re_lim = -1.0F;
      } else {
        re_lim = (real32_T)(rtu_re > 0.0F);
      }

      re_lim = re_lim * 0.95F * rtu_U_lim;
    } else {
      /* '<S38>:1:17' else */
      /* '<S38>:1:18' re_lim = re; */
      re_lim = rtu_re;
    }

    /* '<S38>:1:20' im_lim = sign(im)*sqrt(U_lim^2 - re_lim^2); */
    if (rtu_im < 0.0F) {
      rtu_im_0 = -1.0F;
    } else {
      rtu_im_0 = (real32_T)(rtu_im > 0.0F);
    }

    rtu_im_0 *= sqrtf(tmp - re_lim * re_lim);
  }

  *rty_re_lim = re_lim;
  *rty_im_lim = rtu_im_0;
}

/*
 * System initialize for action system:
 *    '<S10>/Strangstromregler_asymetrisch'
 *    '<S10>/Strangstromregler_asymetrisch1'
 */
static void Strangstromregler_asymetri_Init(DW_Strangstromregler_asymetrisc
  *localDW)
{
  /* InitializeConditions for Delay: '<S32>/Delay1' */
  localDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S32>/Delay' */
  localDW->Delay_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S33>/Delay1' */
  localDW->Delay1_DSTATE_m = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_d = 0.0F;

  /* InitializeConditions for Delay: '<S33>/Delay' */
  localDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_m = 0.0F;

  /* InitializeConditions for Delay: '<S31>/Delay1' */
  localDW->Delay1_DSTATE_l = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_m = 0.0F;

  /* InitializeConditions for Delay: '<S31>/Delay' */
  localDW->Delay_DSTATE_b = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_l = 0.0F;

  /* InitializeConditions for Delay: '<S34>/Delay1' */
  localDW->Delay1_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_i = 0.0F;

  /* InitializeConditions for Delay: '<S34>/Delay' */
  localDW->Delay_DSTATE_bz = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_k = 0.0F;

  /* InitializeConditions for Delay: '<S35>/Delay1' */
  localDW->Delay1_DSTATE_i = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_if = 0.0F;

  /* InitializeConditions for Delay: '<S35>/Delay' */
  localDW->Delay_DSTATE_h = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_a = 0.0F;
}

/*
 * System reset for action system:
 *    '<S10>/Strangstromregler_asymetrisch'
 *    '<S10>/Strangstromregler_asymetrisch1'
 */
static void Strangstromregler_asymetr_Reset(DW_Strangstromregler_asymetrisc
  *localDW)
{
  /* InitializeConditions for Delay: '<S32>/Delay1' */
  localDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S32>/Delay' */
  localDW->Delay_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S33>/Delay1' */
  localDW->Delay1_DSTATE_m = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_d = 0.0F;

  /* InitializeConditions for Delay: '<S33>/Delay' */
  localDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_m = 0.0F;

  /* InitializeConditions for Delay: '<S31>/Delay1' */
  localDW->Delay1_DSTATE_l = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_m = 0.0F;

  /* InitializeConditions for Delay: '<S31>/Delay' */
  localDW->Delay_DSTATE_b = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_l = 0.0F;

  /* InitializeConditions for Delay: '<S34>/Delay1' */
  localDW->Delay1_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_i = 0.0F;

  /* InitializeConditions for Delay: '<S34>/Delay' */
  localDW->Delay_DSTATE_bz = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_k = 0.0F;

  /* InitializeConditions for Delay: '<S35>/Delay1' */
  localDW->Delay1_DSTATE_i = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_if = 0.0F;

  /* InitializeConditions for Delay: '<S35>/Delay' */
  localDW->Delay_DSTATE_h = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_a = 0.0F;
}

/*
 * Output and update for action system:
 *    '<S10>/Strangstromregler_asymetrisch'
 *    '<S10>/Strangstromregler_asymetrisch1'
 */
static void Strangstromregler_asymetrisch(real32_T rtu_I_re, real32_T rtu_I_im,
  real32_T rtu_I_S, real32_T rtu_w1, real32_T rtu_U_ZK1, uint8_T
  rtu_enable_compensation_current, real32_T rtu_Theta_u, real32_T
  rtu_Theta_u_back, real32_T rtu_I_im_CT, creal32_T rtu_Psi_PM, creal32_T
  rtu_Psi_PM_n, creal32_T rtu_Psi_PM_k, real32_T *rty_a, real32_T *rty_I_ref1,
  real32_T rtp_Offset_S, real32_T rtp_Offset_gegen, real32_T rtp_Offset_null,
  DW_Strangstromregler_asymetrisc *localDW)
{
  /* Sum: '<S23>/Sum1' incorporates:
   *  Constant: '<S23>/Constant'
   */
  localDW->Product4_i = rtu_Theta_u_back + rtp_Offset_S;

  /* Product: '<S32>/Product4' */
  localDW->Delay1_c = localDW->Product4_i;

  /* Sum: '<S23>/Sum' incorporates:
   *  Constant: '<S23>/Constant'
   */
  localDW->Product5_h = rtu_Theta_u + rtp_Offset_S;

  /* MATLAB Function: '<S30>/MATLAB Function' */
  MATLABFunction_i(rtu_Psi_PM, rtu_Psi_PM_n, rtu_Psi_PM_k, rtu_I_re, rtu_I_im,
                   rtu_w1, rtu_enable_compensation_current, &localDW->im_lim_d,
                   &localDW->re_lim_g, &localDW->im_lim_m, &localDW->re_lim_l4,
                   &localDW->im_lim_lb, &localDW->re_lim_i,
                   &localDW->sf_MATLABFunction_i);

  /* Sum: '<S23>/Add2' incorporates:
   *  Constant: '<S23>/Constant2'
   */
  localDW->Strom_kompensiert_l = localDW->Product5_h + rtp_Offset_gegen;

  /* Trigonometry: '<S30>/Cos2' */
  localDW->Cos2_k = cosf(localDW->Strom_kompensiert_l);

  /* Gain: '<S30>/Gain1' incorporates:
   *  Trigonometry: '<S30>/Cos3'
   */
  localDW->Gain1_p4 = -sinf(localDW->Strom_kompensiert_l);

  /* Sum: '<S23>/Add3' incorporates:
   *  Constant: '<S23>/Constant3'
   */
  localDW->Strom_kompensiert_l = localDW->Product5_h + rtp_Offset_null;

  /* Trigonometry: '<S30>/Cos' incorporates:
   *  Trigonometry: '<S32>/Cos'
   */
  localDW->Gain1_h = cosf(localDW->Product5_h);

  /* Gain: '<S30>/Gain' incorporates:
   *  Gain: '<S32>/Gain'
   *  Trigonometry: '<S30>/Cos1'
   */
  localDW->Gain2_nl = -sinf(localDW->Product5_h);

  /* Sum: '<S30>/Strom_kompensiert' incorporates:
   *  Gain: '<S30>/Gain'
   *  Gain: '<S30>/Gain2'
   *  Product: '<S30>/Product'
   *  Product: '<S30>/Product1'
   *  Product: '<S30>/Product2'
   *  Product: '<S30>/Product3'
   *  Product: '<S30>/Product4'
   *  Product: '<S30>/Product5'
   *  Sum: '<S30>/Add'
   *  Trigonometry: '<S30>/Cos'
   *  Trigonometry: '<S30>/Cos4'
   *  Trigonometry: '<S30>/Cos5'
   */
  localDW->Strom_kompensiert_l = (((((rtu_I_im_CT + localDW->re_lim_g) *
    localDW->Gain2_nl + localDW->im_lim_d * localDW->Gain1_h) +
    localDW->im_lim_m * localDW->Cos2_k) + localDW->re_lim_l4 *
    localDW->Gain1_p4) + localDW->im_lim_lb * cosf(localDW->Strom_kompensiert_l))
    + localDW->re_lim_i * -sinf(localDW->Strom_kompensiert_l);

  /* Sum: '<S23>/Sum2' */
  localDW->Product_am = localDW->Strom_kompensiert_l - rtu_I_S;

  /* Gain: '<S32>/Gain6' incorporates:
   *  Gain: '<S33>/Gain6'
   *  Gain: '<S34>/Gain6'
   *  Gain: '<S35>/Gain6'
   */
  localDW->DiscreteTimeIntegrator1_h = rtP.Kp * localDW->Product_am;

  /* Product: '<S32>/Product1' incorporates:
   *  Gain: '<S32>/Gain6'
   */
  localDW->Gain1_p4 = localDW->Gain1_h * localDW->DiscreteTimeIntegrator1_h;

  /* Gain: '<S32>/Gain1' incorporates:
   *  Delay: '<S32>/Delay1'
   *  Sum: '<S32>/Sum4'
   */
  localDW->Gain1_h = 2.5E-5F * rtP.K1 * (localDW->Delay1_DSTATE +
    localDW->Gain1_p4);

  /* DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator = 0.5F * localDW->Gain1_h +
    localDW->DiscreteTimeIntegrator_DSTATE;

  /* Sum: '<S32>/Sum5' */
  localDW->U_re_o = localDW->DiscreteTimeIntegrator + localDW->Gain1_p4;

  /* MATLAB Function: '<S23>/MATLAB Function' */
  MATLABFunction(rtu_I_im, rtu_w1, &localDW->Betrieb_n);

  /* Product: '<S32>/Product' incorporates:
   *  Gain: '<S32>/Gain6'
   */
  localDW->Cos2_k = localDW->DiscreteTimeIntegrator1_h * localDW->Gain2_nl;

  /* Gain: '<S32>/Gain2' incorporates:
   *  Delay: '<S32>/Delay'
   *  Sum: '<S32>/Sum2'
   */
  localDW->Gain2_nl = 2.5E-5F * rtP.K1 * (localDW->Cos2_k +
    localDW->Delay_DSTATE);

  /* DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1 = 0.5F * localDW->Gain2_nl +
    localDW->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S32>/Sum6' */
  localDW->U_im_i = localDW->Cos2_k + localDW->DiscreteTimeIntegrator1;

  /* MATLAB Function: '<S32>/MATLAB Function' incorporates:
   *  Constant: '<S32>/Constant2'
   *  Product: '<S32>/Product6'
   */
  MATLABFunction_a(localDW->U_re_o, 0.92F * rtu_U_ZK1, localDW->Betrieb_n,
                   localDW->U_im_i, &localDW->re_lim_l4, &localDW->im_lim_m);

  /* Product: '<S33>/Product4' incorporates:
   *  Constant: '<S33>/Constant1'
   */
  localDW->re_lim_gw = localDW->Product4_i * 2.0F;

  /* Product: '<S33>/Product5' incorporates:
   *  Constant: '<S33>/Constant1'
   */
  localDW->Gain1_p4 = localDW->Product5_h * 2.0F;

  /* Product: '<S33>/Product1' incorporates:
   *  Trigonometry: '<S33>/Cos'
   */
  localDW->im_lim_k = cosf(localDW->Gain1_p4) *
    localDW->DiscreteTimeIntegrator1_h;

  /* Gain: '<S33>/Gain1' incorporates:
   *  Delay: '<S33>/Delay1'
   *  Sum: '<S33>/Sum4'
   */
  localDW->Gain1_g = 2.5E-5F * rtP.K2 * (localDW->Delay1_DSTATE_m +
    localDW->im_lim_k);

  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_o = 0.5F * localDW->Gain1_g +
    localDW->DiscreteTimeIntegrator_DSTATE_d;

  /* Sum: '<S33>/Sum5' */
  localDW->U_re_h = localDW->DiscreteTimeIntegrator_o + localDW->im_lim_k;

  /* Product: '<S33>/Product' incorporates:
   *  Gain: '<S33>/Gain'
   *  Trigonometry: '<S33>/Sin'
   */
  localDW->Cos2_k = localDW->DiscreteTimeIntegrator1_h * -sinf(localDW->Gain1_p4);

  /* Gain: '<S33>/Gain2' incorporates:
   *  Delay: '<S33>/Delay'
   *  Sum: '<S33>/Sum2'
   */
  localDW->Gain2_d = 2.5E-5F * rtP.K2 * (localDW->Cos2_k +
    localDW->Delay_DSTATE_a);

  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_f = 0.5F * localDW->Gain2_d +
    localDW->DiscreteTimeIntegrator1_DSTAT_m;

  /* Sum: '<S33>/Sum6' */
  localDW->U_im_pl = localDW->Cos2_k + localDW->DiscreteTimeIntegrator1_f;

  /* MATLAB Function: '<S33>/MATLAB Function' incorporates:
   *  Constant: '<S33>/Constant2'
   *  Product: '<S33>/Product6'
   */
  MATLABFunction_a(localDW->U_re_h, 0.05F * rtu_U_ZK1, localDW->Betrieb_n,
                   localDW->U_im_pl, &localDW->re_lim_i, &localDW->im_lim_lb);

  /* Product: '<S33>/Product3' incorporates:
   *  Trigonometry: '<S33>/Cos1'
   */
  localDW->Product3_o = cosf(localDW->re_lim_gw) * localDW->re_lim_i;

  /* Product: '<S33>/Product2' incorporates:
   *  Gain: '<S33>/Gain3'
   *  Trigonometry: '<S33>/Sin1'
   */
  localDW->Product2_b3 = localDW->im_lim_lb * -sinf(localDW->re_lim_gw);

  /* Product: '<S31>/Product4' incorporates:
   *  Constant: '<S31>/Constant1'
   */
  localDW->re_lim_gw = localDW->Product4_i * 3.0F;

  /* Product: '<S31>/Product5' incorporates:
   *  Constant: '<S31>/Constant1'
   */
  localDW->Cos2_k = localDW->Product5_h * 3.0F;

  /* Gain: '<S31>/Gain4' */
  localDW->im_lim_k = rtP.K3 * localDW->Product_am;

  /* Gain: '<S31>/Gain1' incorporates:
   *  Delay: '<S31>/Delay1'
   *  Product: '<S31>/Product1'
   *  Sum: '<S31>/Sum4'
   *  Trigonometry: '<S31>/Cos'
   */
  localDW->Gain1_i = (cosf(localDW->Cos2_k) * localDW->im_lim_k +
                      localDW->Delay1_DSTATE_l) * 2.5E-5F;

  /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->U_re = 0.5F * localDW->Gain1_i +
    localDW->DiscreteTimeIntegrator_DSTATE_m;

  /* Gain: '<S31>/Gain2' incorporates:
   *  Delay: '<S31>/Delay'
   *  Gain: '<S31>/Gain'
   *  Product: '<S31>/Product'
   *  Sum: '<S31>/Sum2'
   *  Trigonometry: '<S31>/Sin'
   */
  localDW->Gain2_io = (localDW->im_lim_k * -sinf(localDW->Cos2_k) +
                       localDW->Delay_DSTATE_b) * 2.5E-5F;

  /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->U_im = 0.5F * localDW->Gain2_io +
    localDW->DiscreteTimeIntegrator1_DSTAT_l;

  /* MATLAB Function: '<S31>/MATLAB Function' incorporates:
   *  Constant: '<S31>/Constant'
   *  Product: '<S31>/Product6'
   */
  MATLABFunction_c(localDW->U_re, 0.15F * rtu_U_ZK1, localDW->U_im,
                   &localDW->re_lim_g, &localDW->im_lim_d);

  /* Product: '<S31>/Product3' incorporates:
   *  Trigonometry: '<S31>/Cos1'
   */
  localDW->Product3_a = cosf(localDW->re_lim_gw) * localDW->re_lim_g;

  /* Product: '<S31>/Product2' incorporates:
   *  Gain: '<S31>/Gain3'
   *  Trigonometry: '<S31>/Sin1'
   */
  localDW->Product2_p = localDW->im_lim_d * -sinf(localDW->re_lim_gw);

  /* Product: '<S34>/Product4' incorporates:
   *  Constant: '<S34>/Constant1'
   */
  localDW->re_lim_gw = localDW->Product4_i * 4.0F;

  /* Product: '<S34>/Product5' incorporates:
   *  Constant: '<S34>/Constant1'
   */
  localDW->Gain1_p4 = localDW->Product5_h * 4.0F;

  /* Product: '<S34>/Product1' incorporates:
   *  Trigonometry: '<S34>/Cos'
   */
  localDW->im_lim_k = cosf(localDW->Gain1_p4) *
    localDW->DiscreteTimeIntegrator1_h;

  /* Gain: '<S34>/Gain1' incorporates:
   *  Delay: '<S34>/Delay1'
   *  Sum: '<S34>/Sum4'
   */
  localDW->Gain1_n = 2.5E-5F * rtP.K4 * (localDW->Delay1_DSTATE_g +
    localDW->im_lim_k);

  /* DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_j = 0.5F * localDW->Gain1_n +
    localDW->DiscreteTimeIntegrator_DSTATE_i;

  /* Sum: '<S34>/Sum5' */
  localDW->U_re_j = localDW->DiscreteTimeIntegrator_j + localDW->im_lim_k;

  /* Product: '<S34>/Product' incorporates:
   *  Gain: '<S34>/Gain'
   *  Trigonometry: '<S34>/Sin'
   */
  localDW->Cos2_k = localDW->DiscreteTimeIntegrator1_h * -sinf(localDW->Gain1_p4);

  /* Gain: '<S34>/Gain2' incorporates:
   *  Delay: '<S34>/Delay'
   *  Sum: '<S34>/Sum2'
   */
  localDW->Gain2_e = 2.5E-5F * rtP.K4 * (localDW->Cos2_k +
    localDW->Delay_DSTATE_bz);

  /* DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_e = 0.5F * localDW->Gain2_e +
    localDW->DiscreteTimeIntegrator1_DSTAT_k;

  /* Sum: '<S34>/Sum6' */
  localDW->U_im_pt = localDW->Cos2_k + localDW->DiscreteTimeIntegrator1_e;

  /* MATLAB Function: '<S34>/MATLAB Function' incorporates:
   *  Constant: '<S34>/Constant2'
   *  Product: '<S34>/Product6'
   */
  MATLABFunction_a(localDW->U_re_j, 0.025F * rtu_U_ZK1, localDW->Betrieb_n,
                   localDW->U_im_pt, &localDW->Cos2_k, &localDW->im_lim_k);

  /* Product: '<S34>/Product3' incorporates:
   *  Trigonometry: '<S34>/Cos1'
   */
  localDW->Product3_lj = cosf(localDW->re_lim_gw) * localDW->Cos2_k;

  /* Product: '<S34>/Product2' incorporates:
   *  Gain: '<S34>/Gain3'
   *  Trigonometry: '<S34>/Sin1'
   */
  localDW->Product2_c = localDW->im_lim_k * -sinf(localDW->re_lim_gw);

  /* Product: '<S35>/Product4' incorporates:
   *  Constant: '<S35>/Constant1'
   */
  localDW->Product4_i *= 6.0F;

  /* Product: '<S35>/Product5' incorporates:
   *  Constant: '<S35>/Constant1'
   */
  localDW->Product5_h *= 6.0F;

  /* Product: '<S35>/Product1' incorporates:
   *  Trigonometry: '<S35>/Cos'
   */
  localDW->re_lim_gw = cosf(localDW->Product5_h) *
    localDW->DiscreteTimeIntegrator1_h;

  /* Delay: '<S35>/Delay1' */
  localDW->Gain1_p4 = localDW->Delay1_DSTATE_i;

  /* Gain: '<S35>/Gain1' incorporates:
   *  Delay: '<S35>/Delay1'
   *  Sum: '<S35>/Sum4'
   */
  localDW->Gain1_a = 2.5E-5F * rtP.K6 * (localDW->Delay1_DSTATE_i +
    localDW->re_lim_gw);

  /* DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_h = 0.5F * localDW->Gain1_a +
    localDW->DiscreteTimeIntegrator_DSTAT_if;

  /* Sum: '<S35>/Sum5' */
  localDW->U_re_b = localDW->DiscreteTimeIntegrator_h + localDW->re_lim_gw;

  /* Product: '<S35>/Product' incorporates:
   *  Gain: '<S35>/Gain'
   *  Trigonometry: '<S35>/Sin'
   */
  localDW->Product_am = localDW->DiscreteTimeIntegrator1_h * -sinf
    (localDW->Product5_h);

  /* Delay: '<S35>/Delay' */
  localDW->re_lim_gw = localDW->Delay_DSTATE_h;

  /* Gain: '<S35>/Gain2' incorporates:
   *  Delay: '<S35>/Delay'
   *  Sum: '<S35>/Sum2'
   */
  localDW->Product5_h = 2.5E-5F * rtP.K6 * (localDW->Product_am +
    localDW->Delay_DSTATE_h);

  /* DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_h = 0.5F * localDW->Product5_h +
    localDW->DiscreteTimeIntegrator1_DSTAT_a;

  /* Sum: '<S35>/Sum6' */
  localDW->Product_am += localDW->DiscreteTimeIntegrator1_h;

  /* MATLAB Function: '<S35>/MATLAB Function' incorporates:
   *  Constant: '<S35>/Constant2'
   *  Product: '<S35>/Product6'
   */
  MATLABFunction_a(localDW->U_re_b, 0.01F * rtu_U_ZK1, localDW->Betrieb_n,
                   localDW->Product_am, &localDW->re_lim_gw, &localDW->Gain1_p4);

  /* Sum: '<S23>/Add' incorporates:
   *  Constant: '<S23>/Constant1'
   *  Gain: '<S32>/Gain3'
   *  Gain: '<S35>/Gain3'
   *  Product: '<S23>/Divide'
   *  Product: '<S32>/Product2'
   *  Product: '<S32>/Product3'
   *  Product: '<S35>/Product2'
   *  Product: '<S35>/Product3'
   *  Sum: '<S23>/Add1'
   *  Sum: '<S31>/Sum'
   *  Sum: '<S32>/Sum'
   *  Sum: '<S33>/Sum'
   *  Sum: '<S34>/Sum'
   *  Sum: '<S35>/Sum'
   *  Trigonometry: '<S32>/Cos1'
   *  Trigonometry: '<S32>/Sin1'
   *  Trigonometry: '<S35>/Cos1'
   *  Trigonometry: '<S35>/Sin1'
   */
  *rty_a = (((((cosf(localDW->Delay1_c) * localDW->re_lim_l4 + localDW->im_lim_m
                * -sinf(localDW->Delay1_c)) + (localDW->Product3_o +
    localDW->Product2_b3)) + (localDW->Product3_a + localDW->Product2_p)) +
             (localDW->Product3_lj + localDW->Product2_c)) + (cosf
             (localDW->Product4_i) * localDW->re_lim_gw + localDW->Gain1_p4 *
             -sinf(localDW->Product4_i))) / rtu_U_ZK1 + 0.5F;

  /* SignalConversion generated from: '<S23>/I_ref1' */
  *rty_I_ref1 = localDW->Strom_kompensiert_l;

  /* Update for Delay: '<S32>/Delay1' incorporates:
   *  Sum: '<S32>/Sum3'
   */
  localDW->Delay1_DSTATE = localDW->re_lim_l4 - localDW->U_re_o;

  /* Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.5F * localDW->Gain1_h +
    localDW->DiscreteTimeIntegrator;

  /* Update for Delay: '<S32>/Delay' incorporates:
   *  Sum: '<S32>/Sum1'
   */
  localDW->Delay_DSTATE = localDW->im_lim_m - localDW->U_im_i;

  /* Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = 0.5F * localDW->Gain2_nl +
    localDW->DiscreteTimeIntegrator1;

  /* Update for Delay: '<S33>/Delay1' incorporates:
   *  Sum: '<S33>/Sum3'
   */
  localDW->Delay1_DSTATE_m = localDW->re_lim_i - localDW->U_re_h;

  /* Update for DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_d = 0.5F * localDW->Gain1_g +
    localDW->DiscreteTimeIntegrator_o;

  /* Update for Delay: '<S33>/Delay' incorporates:
   *  Sum: '<S33>/Sum1'
   */
  localDW->Delay_DSTATE_a = localDW->im_lim_lb - localDW->U_im_pl;

  /* Update for DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_m = 0.5F * localDW->Gain2_d +
    localDW->DiscreteTimeIntegrator1_f;

  /* Update for Delay: '<S31>/Delay1' incorporates:
   *  Sum: '<S31>/Sum3'
   */
  localDW->Delay1_DSTATE_l = localDW->re_lim_g - localDW->U_re;

  /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_m = 0.5F * localDW->Gain1_i +
    localDW->U_re;

  /* Update for Delay: '<S31>/Delay' incorporates:
   *  Sum: '<S31>/Sum1'
   */
  localDW->Delay_DSTATE_b = localDW->im_lim_d - localDW->U_im;

  /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_l = 0.5F * localDW->Gain2_io +
    localDW->U_im;

  /* Update for Delay: '<S34>/Delay1' incorporates:
   *  Sum: '<S34>/Sum3'
   */
  localDW->Delay1_DSTATE_g = localDW->Cos2_k - localDW->U_re_j;

  /* Update for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_i = 0.5F * localDW->Gain1_n +
    localDW->DiscreteTimeIntegrator_j;

  /* Update for Delay: '<S34>/Delay' incorporates:
   *  Sum: '<S34>/Sum1'
   */
  localDW->Delay_DSTATE_bz = localDW->im_lim_k - localDW->U_im_pt;

  /* Update for DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_k = 0.5F * localDW->Gain2_e +
    localDW->DiscreteTimeIntegrator1_e;

  /* Update for Delay: '<S35>/Delay1' incorporates:
   *  Sum: '<S35>/Sum3'
   */
  localDW->Delay1_DSTATE_i = localDW->re_lim_gw - localDW->U_re_b;

  /* Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_if = 0.5F * localDW->Gain1_a +
    localDW->DiscreteTimeIntegrator_h;

  /* Update for Delay: '<S35>/Delay' incorporates:
   *  Sum: '<S35>/Sum1'
   */
  localDW->Delay_DSTATE_h = localDW->Gain1_p4 - localDW->Product_am;

  /* Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_a = 0.5F * localDW->Product5_h +
    localDW->DiscreteTimeIntegrator1_h;
}

/*
 * Output and update for action system:
 *    '<S10>/Switch Case Action Subsystem'
 *    '<S10>/Switch Case Action Subsystem1'
 *    '<S10>/Switch Case Action Subsystem2'
 */
static void SwitchCaseActionSubsystem(real32_T *rty_a, real32_T *rty_Iref)
{
  /* SignalConversion generated from: '<S26>/a' incorporates:
   *  Constant: '<S26>/Constant1'
   */
  *rty_a = 0.5F;

  /* SignalConversion generated from: '<S26>/Iref' incorporates:
   *  Constant: '<S26>/Constant2'
   */
  *rty_Iref = 0.0F;
}

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Gain: '<S3>/Gain' incorporates:
   *  Delay: '<S3>/Delay'
   *  Inport: '<Root>/Act_U_ZK'
   *  Sum: '<S3>/Sum'
   */
  rtDW->Gain = (rtU->Act_U_ZK - rtDW->Delay_DSTATE) * 0.0025F;

  /* DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator = 0.5F * rtDW->Gain +
    rtDW->DiscreteTimeIntegrator_DSTATE;

  /* SwitchCase: '<S2>/switch_case_power' incorporates:
   *  Inport: '<Root>/fl_power'
   */
  rtDW->rtPrevAction = rtDW->switch_case_power_ActiveSubsyst;
  switch (rtU->fl_power) {
   case 1:
   case 2:
   case 3:
    rtDW->rtAction = 0;
    break;

   default:
    rtDW->rtAction = 1;
    break;
  }

  rtDW->switch_case_power_ActiveSubsyst = rtDW->rtAction;
  if ((rtDW->rtPrevAction != rtDW->rtAction) && (rtDW->rtPrevAction == 0)) {
    /* Disable for SwitchCase: '<S4>/Switch Case' */
    rtDW->SwitchCase_ActiveSubsystem = -1;

    /* Disable for SwitchCase: '<S10>/Switch Case' */
    rtDW->SwitchCase_ActiveSubsystem_o = -1;

    /* Disable for SwitchCase: '<S10>/Switch Case1' */
    rtDW->SwitchCase1_ActiveSubsystem = -1;

    /* Disable for SwitchCase: '<S10>/Switch Case2' */
    rtDW->SwitchCase2_ActiveSubsystem = -1;
  }

  if (rtDW->rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S2>/Regelung_asymetrisch' incorporates:
     *  ActionPort: '<S4>/Action Port'
     */
    /* SwitchCase: '<S4>/Switch Case' incorporates:
     *  Inport: '<Root>/fl_control_type'
     */
    rtDW->rtPrevAction = rtDW->SwitchCase_ActiveSubsystem;
    if (rtU->fl_control_type != 1) {
      rtDW->rtAction = 1;
    }

    rtDW->SwitchCase_ActiveSubsystem = rtDW->rtAction;
    if (rtDW->rtAction == 0) {
      if (rtDW->rtPrevAction != 0) {
        /* InitializeConditions for IfAction SubSystem: '<S4>/Drehzahlregler' incorporates:
         *  ActionPort: '<S7>/Action Port'
         */
        /* InitializeConditions for SwitchCase: '<S4>/Switch Case' incorporates:
         *  Delay: '<S14>/Delay'
         *  Delay: '<S7>/Delay'
         *  DiscreteIntegrator: '<S13>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S14>/Discrete-Time Integrator'
         */
        rtDW->Delay_DSTATE_n = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_n = 0.0F;
        rtDW->Delay_DSTATE_h = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_f = 0.0F;

        /* End of InitializeConditions for SubSystem: '<S4>/Drehzahlregler' */
      }

      /* Outputs for IfAction SubSystem: '<S4>/Drehzahlregler' incorporates:
       *  ActionPort: '<S7>/Action Port'
       */
      /* MATLAB Function: '<S7>/function_Eckdrehzahl' incorporates:
       *  Inport: '<Root>/fl_field_weakening'
       */
      /* MATLAB Function 'Regelung-Einzelstrang/Regelung/Drehzahlregler/function_Eckdrehzahl': '<S17>:1' */
      /* '<S17>:1:4' U_FA = 0.95*U_ZK/2; */
      rtDW->c = 0.95F * rtDW->DiscreteTimeIntegrator / 2.0F;

      /* '<S17>:1:5' a = Psi_PM^2 + (L*i_ref_max)^2; */
      rtDW->a = 0.0012F * rtP.i_ref_max;
      rtDW->a = rtDW->a * rtDW->a + 0.000292410026F;

      /* '<S17>:1:6' b = 2*Psi_PM*R*i_ref_max; */
      rtDW->b = 0.0028386F * rtP.i_ref_max;

      /* '<S17>:1:7' c = (R*i_ref_max)^2 - U_FA^2; */
      rtDW->Gain1 = 0.083F * rtP.i_ref_max;
      rtDW->c = rtDW->Gain1 * rtDW->Gain1 - rtDW->c * rtDW->c;

      /* '<S17>:1:8' if -4*a*c >= single(0) */
      if (-4.0F * rtDW->a * rtDW->c >= 0.0F) {
        /* '<S17>:1:9' n_eck = single(30)/(p*pi) * (-b+sqrt(b^2 -4*a*c))/(2*a); */
        rtDW->c = (sqrtf(rtDW->b * rtDW->b - 4.0F * rtDW->a * rtDW->c) +
                   -rtDW->b) * 0.530516505F / (2.0F * rtDW->a);

        /* '<S17>:1:10' error_speed_limit = uint8(0); */
        rtDW->error_speed_limit = 0U;
      } else {
        /* '<S17>:1:11' else */
        /* '<S17>:1:12' n_eck = single(0); */
        rtDW->c = 0.0F;

        /* '<S17>:1:13' error_speed_limit = uint8(1); */
        rtDW->error_speed_limit = 1U;
      }

      /* '<S17>:1:15' if (flag_id == 1) && (error_speed_limit == 0) */
      if ((rtU->fl_field_weakening == 1) && (rtDW->error_speed_limit == 0)) {
        /* '<S17>:1:16' n_sat = min(3*n_eck, n_ref_max); */
        rtDW->a = fminf(3.0F * rtDW->c, rtP.n_ref_max);
      } else {
        /* '<S17>:1:17' else */
        /* '<S17>:1:18' n_sat = min(n_eck, n_ref_max); */
        rtDW->a = fminf(rtDW->c, rtP.n_ref_max);
      }

      /* Outport: '<Root>/error_speed_limit' incorporates:
       *  MATLAB Function: '<S7>/function_Eckdrehzahl'
       */
      rtY->error_speed_limit = rtDW->error_speed_limit;

      /* MATLAB Function: '<S7>/Function_Feldschwaeche' incorporates:
       *  Constant: '<S7>/Constant'
       *  Inport: '<Root>/Act_n'
       *  Inport: '<Root>/fl_field_weakening'
       *  MATLAB Function: '<S7>/function_Eckdrehzahl'
       */
      /* MATLAB Function 'Regelung-Einzelstrang/Regelung/Drehzahlregler/Function_Feldschwaeche': '<S12>:1' */
      /* '<S12>:1:3' switch flag_id */
      if (rtU->fl_field_weakening == 1) {
        /* '<S12>:1:4' case uint8(1) */
        /* '<S12>:1:5' if n_ist>n_eck */
        if (rtU->Act_n > rtDW->c) {
          /* I_d_soll = (Psi_PM*(n_eck-n_ist))/L_d; */
          /* '<S12>:1:7' I_re_soll = Psi_PM/L * (n_eck/n_ist - single(1)); */
          rtDW->b = (rtDW->c / rtU->Act_n - 1.0F) * 14.25F;
        } else {
          /* '<S12>:1:8' else */
          /* '<S12>:1:9' I_re_soll = single(0); */
          rtDW->b = 0.0F;
        }
      } else {
        /* '<S12>:1:11' otherwise */
        /* '<S12>:1:12' I_re_soll = single(0); */
        rtDW->b = 0.0F;
      }

      /* '<S12>:1:15' if abs(I_re_soll)>= 0.95*I_ref_max */
      if (fabsf(rtDW->b) >= 0.95F * rtP.i_ref_max) {
        /* '<S12>:1:16' I_re_soll = sign(I_re_soll)*0.95*I_ref_max; */
        if (rtDW->b < 0.0F) {
          rtDW->b = -1.0F;
        } else {
          rtDW->b = (real32_T)(rtDW->b > 0.0F);
        }

        rtDW->b = rtDW->b * 0.95F * rtP.i_ref_max;
      }

      /* '<S12>:1:19' I_im_max = sqrt(I_ref_max^2-I_re_soll^2); */
      rtDW->c = sqrtf(rtP.i_ref_max * rtP.i_ref_max - rtDW->b * rtDW->b);

      /* Merge: '<S4>/Merge3' incorporates:
       *  MATLAB Function: '<S7>/Function_Feldschwaeche'
       *  SignalConversion generated from: '<S7>/I_re_soll [A]'
       */
      rtDW->I_re = rtDW->b;

      /* Switch: '<S16>/Switch2' incorporates:
       *  Inport: '<Root>/Ref_n'
       *  RelationalOperator: '<S16>/LowerRelop1'
       */
      if (rtU->Ref_n <= rtDW->a) {
        /* Gain: '<S7>/Gain3' */
        rtDW->a = -rtDW->a;

        /* Switch: '<S16>/Switch' incorporates:
         *  RelationalOperator: '<S16>/UpperRelop'
         */
        if (rtU->Ref_n >= rtDW->a) {
          rtDW->a = rtU->Ref_n;
        }

        /* End of Switch: '<S16>/Switch' */
      }

      /* End of Switch: '<S16>/Switch2' */

      /* Gain: '<S14>/Gain' incorporates:
       *  Delay: '<S14>/Delay'
       *  Sum: '<S14>/Sum'
       */
      rtDW->a = (rtDW->a - rtDW->Delay_DSTATE_n) * 0.000372336945F;

      /* DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
      rtDW->b = 0.5F * rtDW->a + rtDW->DiscreteTimeIntegrator_DSTATE_n;

      /* Gain: '<S13>/Gain' incorporates:
       *  DataTypeConversion: '<S4>/Data Type Conversion'
       *  Gain: '<S7>/Gain'
       *  Inport: '<Root>/Act_n'
       *  Product: '<S7>/Divide'
       *  Sum: '<S7>/Sum'
       */
      rtDW->Switch2 = (rtDW->b - rtU->Act_n) / (real32_T)rtU->fl_power * 3.0F *
        1.53278565F;

      /* Gain: '<S13>/Gain1' incorporates:
       *  Delay: '<S7>/Delay'
       *  Sum: '<S13>/Sum1'
       */
      rtDW->Gain1 = (rtDW->Switch2 + rtDW->Delay_DSTATE_h) * 0.000930842303F;

      /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator' incorporates:
       *  Inport: '<Root>/fl_integrator_reset'
       */
      if (rtU->fl_integrator_reset != 0) {
        rtDW->DiscreteTimeIntegrator_DSTATE_f = 0.0F;
      }

      /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
      rtDW->y_i = 0.5F * rtDW->Gain1 + rtDW->DiscreteTimeIntegrator_DSTATE_f;

      /* Sum: '<S13>/Sum' */
      rtDW->y = rtDW->Switch2 + rtDW->y_i;

      /* Switch: '<S15>/Switch2' incorporates:
       *  Gain: '<S7>/Gain2'
       *  RelationalOperator: '<S15>/LowerRelop1'
       *  RelationalOperator: '<S15>/UpperRelop'
       *  Switch: '<S15>/Switch'
       */
      if (rtDW->y > rtDW->c) {
        rtDW->Switch2 = rtDW->c;
      } else if (rtDW->y < -rtDW->c) {
        /* Switch: '<S15>/Switch' incorporates:
         *  Gain: '<S7>/Gain2'
         */
        rtDW->Switch2 = -rtDW->c;
      } else {
        rtDW->Switch2 = rtDW->y;
      }

      /* End of Switch: '<S15>/Switch2' */

      /* Merge: '<S4>/Merge4' incorporates:
       *  SignalConversion generated from: '<S7>/I_im_soll [A]'
       */
      rtDW->I_im = rtDW->Switch2;

      /* Update for Delay: '<S14>/Delay' */
      rtDW->Delay_DSTATE_n = rtDW->b;

      /* Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_n = 0.5F * rtDW->a + rtDW->b;

      /* Update for Delay: '<S7>/Delay' incorporates:
       *  Sum: '<S7>/Sum1'
       */
      rtDW->Delay_DSTATE_h = rtDW->Switch2 - rtDW->y;

      /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_f = 0.5F * rtDW->Gain1 + rtDW->y_i;

      /* End of Outputs for SubSystem: '<S4>/Drehzahlregler' */
    } else {
      /* Outputs for IfAction SubSystem: '<S4>/Stromvorgabe_extern' incorporates:
       *  ActionPort: '<S9>/Action Port'
       */
      /* MATLAB Function: '<S9>/Function_I_limit' incorporates:
       *  Constant: '<S9>/Constant'
       *  Inport: '<Root>/Ref_I_im_ext_mit'
       *  Inport: '<Root>/Ref_I_re_ext_mit'
       */
      /* MATLAB Function 'Regelung-Einzelstrang/Regelung/Stromvorgabe_extern/Function_I_limit': '<S22>:1' */
      /* '<S22>:1:4' I_abs_ext = sqrt(I_re_soll_ext^2+I_im_soll_ext^2); */
      /* '<S22>:1:5' if I_abs_ext > I_ref_max */
      if (sqrtf(rtU->Ref_I_re_ext_mit * rtU->Ref_I_re_ext_mit +
                rtU->Ref_I_im_ext_mit * rtU->Ref_I_im_ext_mit) > rtP.i_ref_max)
      {
        /* '<S22>:1:6' if abs(I_re_soll_ext)>= 0.95*I_ref_max */
        if (fabsf(rtU->Ref_I_re_ext_mit) >= 0.95F * rtP.i_ref_max) {
          /* '<S22>:1:7' I_re_soll = sign(I_re_soll_ext)*0.95*I_ref_max; */
          if (rtU->Ref_I_re_ext_mit < 0.0F) {
            rtDW->c = -1.0F;
          } else {
            rtDW->c = (real32_T)(rtU->Ref_I_re_ext_mit > 0.0F);
          }

          rtDW->b = rtDW->c * 0.95F * rtP.i_ref_max;
        } else {
          /* '<S22>:1:8' else */
          /* '<S22>:1:9' I_re_soll = I_re_soll_ext; */
          rtDW->b = rtU->Ref_I_re_ext_mit;
        }

        /* '<S22>:1:11' I_im_soll = sign(I_im_soll_ext)*sqrt(I_ref_max^2-I_re_soll^2); */
        if (rtU->Ref_I_im_ext_mit < 0.0F) {
          rtDW->c = -1.0F;
        } else {
          rtDW->c = (real32_T)(rtU->Ref_I_im_ext_mit > 0.0F);
        }

        /* Merge: '<S4>/Merge4' */
        rtDW->I_im = sqrtf(rtP.i_ref_max * rtP.i_ref_max - rtDW->b * rtDW->b) *
          rtDW->c;
      } else {
        /* '<S22>:1:12' else */
        /* '<S22>:1:13' I_re_soll = I_re_soll_ext; */
        rtDW->b = rtU->Ref_I_re_ext_mit;

        /* Merge: '<S4>/Merge4' */
        /* '<S22>:1:14' I_im_soll = I_im_soll_ext; */
        rtDW->I_im = rtU->Ref_I_im_ext_mit;
      }

      /* Merge: '<S4>/Merge3' incorporates:
       *  MATLAB Function: '<S9>/Function_I_limit'
       *  SignalConversion generated from: '<S9>/I_re_soll'
       */
      rtDW->I_re = rtDW->b;

      /* End of Outputs for SubSystem: '<S4>/Stromvorgabe_extern' */
    }

    /* End of SwitchCase: '<S4>/Switch Case' */

    /* SwitchCase: '<S8>/Switch Case2' incorporates:
     *  Inport: '<Root>/fl_compensat_CT_current'
     *  Inport: '<Root>/fl_enable_compensation_cogging_torque'
     *  SwitchCase: '<S11>/Switch Case'
     */
    if (rtU->fl_compensat_CT_current == 1) {
      /* SwitchCase: '<S11>/Switch Case' incorporates:
       *  Inport: '<Root>/fl_enable_compensation_cogging_torque'
       */
      if (rtU->fl_enable_compensation_cogging_ == 1) {
        /* Outputs for IfAction SubSystem: '<S8>/Switch Case Action Subsystem1' incorporates:
         *  ActionPort: '<S19>/Action Port'
         */
        /* Outputs for IfAction SubSystem: '<S11>/Rastmomentkompensation' incorporates:
         *  ActionPort: '<S68>/Action Port'
         */
        /* Merge: '<S8>/Merge1' incorporates:
         *  Inport: '<Root>/Act_theta_u_el'
         *  Inport: '<Root>/amplitude_a'
         *  Inport: '<Root>/amplitude_b'
         *  Inport: '<Root>/amplitude_c'
         *  Inport: '<Root>/amplitude_d'
         *  Inport: '<Root>/ordnung_a'
         *  Inport: '<Root>/ordnung_b'
         *  Inport: '<Root>/ordnung_c'
         *  Inport: '<Root>/ordnung_d'
         *  Inport: '<Root>/phase_a'
         *  Inport: '<Root>/phase_b'
         *  Inport: '<Root>/phase_c'
         *  Inport: '<Root>/phase_d'
         *  Product: '<S68>/Product10'
         *  Product: '<S68>/Product11'
         *  Product: '<S68>/Product4'
         *  Product: '<S68>/Product5'
         *  Product: '<S68>/Product6'
         *  Product: '<S68>/Product7'
         *  Product: '<S68>/Product8'
         *  Product: '<S68>/Product9'
         *  SignalConversion generated from: '<S19>/In1'
         *  Sum: '<S68>/Add5'
         *  Sum: '<S68>/Add6'
         *  Sum: '<S68>/Add7'
         *  Sum: '<S68>/Add8'
         *  Sum: '<S68>/Add9'
         *  Trigonometry: '<S68>/Sin4'
         *  Trigonometry: '<S68>/Sin5'
         *  Trigonometry: '<S68>/Sin6'
         *  Trigonometry: '<S68>/Sin7'
         */
        rtDW->Merge1 = ((sinf(rtU->ordnung_a * rtU->Act_theta_u_el +
                              rtU->phase_a) * rtU->amplitude_a + sinf
                         (rtU->ordnung_b * rtU->Act_theta_u_el + rtU->phase_b) *
                         rtU->amplitude_b) + sinf(rtU->ordnung_c *
          rtU->Act_theta_u_el + rtU->phase_c) * rtU->amplitude_c) + sinf
          (rtU->ordnung_d * rtU->Act_theta_u_el + rtU->phase_d) *
          rtU->amplitude_d;

        /* End of Outputs for SubSystem: '<S11>/Rastmomentkompensation' */
        /* End of Outputs for SubSystem: '<S8>/Switch Case Action Subsystem1' */
      } else {
        /* Outputs for IfAction SubSystem: '<S8>/Switch Case Action Subsystem1' incorporates:
         *  ActionPort: '<S19>/Action Port'
         */
        /* Outputs for IfAction SubSystem: '<S11>/Switch Case Action Subsystem' incorporates:
         *  ActionPort: '<S69>/Action Port'
         */
        /* Merge: '<S8>/Merge1' incorporates:
         *  Constant: '<S11>/Constant3'
         *  SignalConversion generated from: '<S19>/In1'
         *  SignalConversion generated from: '<S69>/In1'
         */
        rtDW->Merge1 = 0.0F;

        /* End of Outputs for SubSystem: '<S11>/Switch Case Action Subsystem' */
        /* End of Outputs for SubSystem: '<S8>/Switch Case Action Subsystem1' */
      }
    } else if (rtU->fl_enable_compensation_cogging_ == 1) {
      /* Outputs for IfAction SubSystem: '<S8>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      /* Outputs for IfAction SubSystem: '<S11>/Rastmomentkompensation' incorporates:
       *  ActionPort: '<S68>/Action Port'
       */
      /* SwitchCase: '<S11>/Switch Case' incorporates:
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/amplitude_a'
       *  Inport: '<Root>/amplitude_b'
       *  Inport: '<Root>/amplitude_c'
       *  Inport: '<Root>/amplitude_d'
       *  Inport: '<Root>/ordnung_a'
       *  Inport: '<Root>/ordnung_b'
       *  Inport: '<Root>/ordnung_c'
       *  Inport: '<Root>/ordnung_d'
       *  Inport: '<Root>/phase_a'
       *  Inport: '<Root>/phase_b'
       *  Inport: '<Root>/phase_c'
       *  Inport: '<Root>/phase_d'
       *  Merge: '<S8>/Merge'
       *  Product: '<S68>/Product10'
       *  Product: '<S68>/Product11'
       *  Product: '<S68>/Product4'
       *  Product: '<S68>/Product5'
       *  Product: '<S68>/Product6'
       *  Product: '<S68>/Product7'
       *  Product: '<S68>/Product8'
       *  Product: '<S68>/Product9'
       *  SignalConversion generated from: '<S18>/i_CT_out'
       *  Sum: '<S68>/Add5'
       *  Sum: '<S68>/Add6'
       *  Sum: '<S68>/Add7'
       *  Sum: '<S68>/Add8'
       *  Sum: '<S68>/Add9'
       *  Trigonometry: '<S68>/Sin4'
       *  Trigonometry: '<S68>/Sin5'
       *  Trigonometry: '<S68>/Sin6'
       *  Trigonometry: '<S68>/Sin7'
       */
      rtDW->Merge = ((sinf(rtU->ordnung_a * rtU->Act_theta_u_el + rtU->phase_a) *
                      rtU->amplitude_a + sinf(rtU->ordnung_b *
        rtU->Act_theta_u_el + rtU->phase_b) * rtU->amplitude_b) + sinf
                     (rtU->ordnung_c * rtU->Act_theta_u_el + rtU->phase_c) *
                     rtU->amplitude_c) + sinf(rtU->ordnung_d *
        rtU->Act_theta_u_el + rtU->phase_d) * rtU->amplitude_d;

      /* End of Outputs for SubSystem: '<S11>/Rastmomentkompensation' */
      /* End of Outputs for SubSystem: '<S8>/Switch Case Action Subsystem' */
    } else {
      /* Outputs for IfAction SubSystem: '<S8>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      /* Outputs for IfAction SubSystem: '<S11>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S69>/Action Port'
       */
      /* SwitchCase: '<S11>/Switch Case' incorporates:
       *  Constant: '<S11>/Constant3'
       *  Merge: '<S8>/Merge'
       *  SignalConversion generated from: '<S18>/i_CT_out'
       *  SignalConversion generated from: '<S69>/In1'
       */
      rtDW->Merge = 0.0F;

      /* End of Outputs for SubSystem: '<S11>/Switch Case Action Subsystem' */
      /* End of Outputs for SubSystem: '<S8>/Switch Case Action Subsystem' */
    }

    /* End of SwitchCase: '<S8>/Switch Case2' */

    /* SwitchCase: '<S8>/Switch Case1' incorporates:
     *  Inport: '<Root>/fl_compensat_CT_current'
     */
    if (rtU->fl_compensat_CT_current == 0) {
      /* Outputs for IfAction SubSystem: '<S8>/Switch Case Action Subsystem3' incorporates:
       *  ActionPort: '<S21>/Action Port'
       */
      SwitchCaseActionSubsystem3(&rtDW->Merge1);

      /* End of Outputs for SubSystem: '<S8>/Switch Case Action Subsystem3' */
    } else {
      /* Outputs for IfAction SubSystem: '<S8>/Switch Case Action Subsystem2' incorporates:
       *  ActionPort: '<S20>/Action Port'
       */
      SwitchCaseActionSubsystem3(&rtDW->Merge);

      /* End of Outputs for SubSystem: '<S8>/Switch Case Action Subsystem2' */
    }

    /* End of SwitchCase: '<S8>/Switch Case1' */

    /* Sum: '<S4>/Add' */
    rtDW->a = rtDW->I_im + rtDW->Merge1;

    /* Sum: '<S10>/Add' incorporates:
     *  Inport: '<Root>/Act_theta_u_el'
     *  Inport: '<Root>/Act_w_el'
     *  Product: '<S10>/Product'
     */
    rtDW->c = rtU->Act_w_el * rtConstB.Gain + rtU->Act_theta_u_el;

    /* SwitchCase: '<S10>/Switch Case' */
    rtDW->rtPrevAction = rtDW->SwitchCase_ActiveSubsystem_o;
    switch (rtU->fl_power) {
     case 1:
     case 2:
     case 3:
      rtDW->rtAction = 0;
      break;

     default:
      rtDW->rtAction = 1;
      break;
    }

    rtDW->SwitchCase_ActiveSubsystem_o = rtDW->rtAction;
    if (rtDW->rtAction == 0) {
      if (rtDW->rtPrevAction != 0) {
        /* SystemReset for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch' incorporates:
         *  ActionPort: '<S23>/Action Port'
         */
        /* SystemReset for SwitchCase: '<S10>/Switch Case' */
        Strangstromregler_asymetr_Reset(&rtDW->Strangstromregler_asymetrisch_h);

        /* End of SystemReset for SubSystem: '<S10>/Strangstromregler_asymetrisch' */
      }

      /* Outputs for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch' incorporates:
       *  ActionPort: '<S23>/Action Port'
       */
      /* Outport: '<Root>/a_U' incorporates:
       *  Inport: '<Root>/Act_Iu'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/Act_w_el'
       *  Inport: '<Root>/Psi_PM_U'
       *  Inport: '<Root>/Psi_PM_V'
       *  Inport: '<Root>/Psi_PM_W'
       *  Inport: '<Root>/fl_enable_compensation_current'
       */
      Strangstromregler_asymetrisch(rtDW->I_re, rtDW->a, rtU->Act_Iu,
        rtU->Act_w_el, rtDW->DiscreteTimeIntegrator,
        rtU->fl_enable_compensation_current, rtU->Act_theta_u_el, rtDW->c,
        rtDW->Merge, rtU->Psi_PM_U, rtU->Psi_PM_V, rtU->Psi_PM_W, &rtY->a_U,
        &rtDW->Merge3, 0.0F, 0.0F, 0.0F, &rtDW->Strangstromregler_asymetrisch_h);

      /* End of Outputs for SubSystem: '<S10>/Strangstromregler_asymetrisch' */
    } else {
      /* Outputs for IfAction SubSystem: '<S10>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S26>/Action Port'
       */
      /* Outport: '<Root>/a_U' */
      SwitchCaseActionSubsystem(&rtY->a_U, &rtDW->Merge3);

      /* End of Outputs for SubSystem: '<S10>/Switch Case Action Subsystem' */
    }

    /* End of SwitchCase: '<S10>/Switch Case' */

    /* SwitchCase: '<S10>/Switch Case1' */
    rtDW->rtPrevAction = rtDW->SwitchCase1_ActiveSubsystem;
    switch (rtU->fl_power) {
     case 2:
     case 3:
      rtDW->rtAction = 0;
      break;

     default:
      rtDW->rtAction = 1;
      break;
    }

    rtDW->SwitchCase1_ActiveSubsystem = rtDW->rtAction;
    if (rtDW->rtAction == 0) {
      if (rtDW->rtPrevAction != 0) {
        /* SystemReset for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch1' incorporates:
         *  ActionPort: '<S24>/Action Port'
         */
        /* SystemReset for SwitchCase: '<S10>/Switch Case1' */
        Strangstromregler_asymetr_Reset(&rtDW->Strangstromregler_asymetrisch1);

        /* End of SystemReset for SubSystem: '<S10>/Strangstromregler_asymetrisch1' */
      }

      /* Outputs for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch1' incorporates:
       *  ActionPort: '<S24>/Action Port'
       */
      /* Outport: '<Root>/a_V' incorporates:
       *  Inport: '<Root>/Act_Iv'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/Act_w_el'
       *  Inport: '<Root>/Psi_PM_U'
       *  Inport: '<Root>/Psi_PM_V'
       *  Inport: '<Root>/Psi_PM_W'
       *  Inport: '<Root>/fl_enable_compensation_current'
       */
      Strangstromregler_asymetrisch(rtDW->I_re, rtDW->a, rtU->Act_Iv,
        rtU->Act_w_el, rtDW->DiscreteTimeIntegrator,
        rtU->fl_enable_compensation_current, rtU->Act_theta_u_el, rtDW->c,
        rtDW->Merge, rtU->Psi_PM_U, rtU->Psi_PM_V, rtU->Psi_PM_W, &rtY->a_V,
        &rtDW->Merge4, -2.09439516F, -2.09439516F, 2.09439516F,
        &rtDW->Strangstromregler_asymetrisch1);

      /* End of Outputs for SubSystem: '<S10>/Strangstromregler_asymetrisch1' */
    } else {
      /* Outputs for IfAction SubSystem: '<S10>/Switch Case Action Subsystem1' incorporates:
       *  ActionPort: '<S27>/Action Port'
       */
      /* Outport: '<Root>/a_V' */
      SwitchCaseActionSubsystem(&rtY->a_V, &rtDW->Merge4);

      /* End of Outputs for SubSystem: '<S10>/Switch Case Action Subsystem1' */
    }

    /* End of SwitchCase: '<S10>/Switch Case1' */

    /* SwitchCase: '<S10>/Switch Case2' */
    rtDW->rtPrevAction = rtDW->SwitchCase2_ActiveSubsystem;
    if (rtU->fl_power == 3) {
      rtDW->rtAction = 0;
    } else {
      rtDW->rtAction = 1;
    }

    rtDW->SwitchCase2_ActiveSubsystem = rtDW->rtAction;
    if (rtDW->rtAction == 0) {
      if (rtDW->rtPrevAction != 0) {
        /* InitializeConditions for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch2' incorporates:
         *  ActionPort: '<S25>/Action Port'
         */
        /* InitializeConditions for SwitchCase: '<S10>/Switch Case2' incorporates:
         *  Delay: '<S57>/Delay'
         *  Delay: '<S57>/Delay1'
         *  Delay: '<S58>/Delay'
         *  Delay: '<S58>/Delay1'
         *  Delay: '<S59>/Delay'
         *  Delay: '<S59>/Delay1'
         *  Delay: '<S60>/Delay'
         *  Delay: '<S60>/Delay1'
         *  Delay: '<S61>/Delay'
         *  Delay: '<S61>/Delay1'
         *  DiscreteIntegrator: '<S57>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S57>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S58>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S58>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S59>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S59>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S60>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S60>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S61>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S61>/Discrete-Time Integrator1'
         */
        rtDW->Delay1_DSTATE = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;
        rtDW->Delay_DSTATE_l = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;
        rtDW->Delay1_DSTATE_o = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.0F;
        rtDW->Delay_DSTATE_nv = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.0F;
        rtDW->Delay1_DSTATE_d = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTAT_om = 0.0F;
        rtDW->Delay_DSTATE_j = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_a = 0.0F;
        rtDW->Delay1_DSTATE_g = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.0F;
        rtDW->Delay_DSTATE_a = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.0F;
        rtDW->Delay1_DSTATE_oi = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.0F;
        rtDW->Delay_DSTATE_nm = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTA_os = 0.0F;

        /* End of InitializeConditions for SubSystem: '<S10>/Strangstromregler_asymetrisch2' */
      }

      /* Outputs for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch2' incorporates:
       *  ActionPort: '<S25>/Action Port'
       */
      /* Sum: '<S25>/Sum1' incorporates:
       *  Constant: '<S25>/Constant'
       */
      rtDW->c_k = rtDW->c + -4.18879032F;

      /* MATLAB Function: '<S56>/MATLAB Function' incorporates:
       *  Inport: '<Root>/Act_w_el'
       *  Inport: '<Root>/Psi_PM_U'
       *  Inport: '<Root>/Psi_PM_V'
       *  Inport: '<Root>/Psi_PM_W'
       *  Inport: '<Root>/fl_enable_compensation_current'
       */
      MATLABFunction_i(rtU->Psi_PM_U, rtU->Psi_PM_V, rtU->Psi_PM_W, rtDW->I_re,
                       rtDW->a, rtU->Act_w_el,
                       rtU->fl_enable_compensation_current, &rtDW->Gain1,
                       &rtDW->y_i, &rtDW->y, &rtDW->Switch2, &rtDW->im_lim,
                       &rtDW->re_lim, &rtDW->sf_MATLABFunction_e);

      /* Trigonometry: '<S56>/Cos' incorporates:
       *  Constant: '<S25>/Constant'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Sum'
       *  Trigonometry: '<S58>/Cos'
       */
      rtDW->Gain1_p = cosf(rtU->Act_theta_u_el + -4.18879032F);

      /* Gain: '<S56>/Gain' incorporates:
       *  Constant: '<S25>/Constant'
       *  Gain: '<S58>/Gain'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Sum'
       *  Trigonometry: '<S56>/Cos1'
       */
      rtDW->b = -sinf(rtU->Act_theta_u_el + -4.18879032F);

      /* Sum: '<S56>/Strom_kompensiert' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S25>/Constant2'
       *  Constant: '<S25>/Constant3'
       *  Gain: '<S56>/Gain'
       *  Gain: '<S56>/Gain1'
       *  Gain: '<S56>/Gain2'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Product: '<S56>/Product'
       *  Product: '<S56>/Product1'
       *  Product: '<S56>/Product2'
       *  Product: '<S56>/Product3'
       *  Product: '<S56>/Product4'
       *  Product: '<S56>/Product5'
       *  Sum: '<S25>/Add2'
       *  Sum: '<S25>/Add3'
       *  Sum: '<S25>/Sum'
       *  Sum: '<S56>/Add'
       *  Trigonometry: '<S56>/Cos'
       *  Trigonometry: '<S56>/Cos2'
       *  Trigonometry: '<S56>/Cos3'
       *  Trigonometry: '<S56>/Cos4'
       *  Trigonometry: '<S56>/Cos5'
       */
      rtDW->Strom_kompensiert = (((((rtDW->Merge + rtDW->y_i) * rtDW->b +
        rtDW->Gain1_p * rtDW->Gain1) + cosf((rtU->Act_theta_u_el + -4.18879032F)
        + -4.18879032F) * rtDW->y) + -sinf((rtU->Act_theta_u_el + -4.18879032F)
        + -4.18879032F) * rtDW->Switch2) + cosf((rtU->Act_theta_u_el +
        -4.18879032F) + 4.18879032F) * rtDW->im_lim) + -sinf
        ((rtU->Act_theta_u_el + -4.18879032F) + 4.18879032F) * rtDW->re_lim;

      /* Sum: '<S25>/Sum2' incorporates:
       *  Inport: '<Root>/Act_Iw'
       */
      rtDW->Product_d = rtDW->Strom_kompensiert - rtU->Act_Iw;

      /* Gain: '<S58>/Gain6' incorporates:
       *  Gain: '<S59>/Gain6'
       *  Gain: '<S60>/Gain6'
       *  Gain: '<S61>/Gain6'
       */
      rtDW->DiscreteTimeIntegrator1_g = rtP.Kp * rtDW->Product_d;

      /* Product: '<S58>/Product1' incorporates:
       *  Gain: '<S58>/Gain6'
       */
      rtDW->Gain1_p *= rtDW->DiscreteTimeIntegrator1_g;

      /* Gain: '<S58>/Gain1' incorporates:
       *  Delay: '<S58>/Delay1'
       *  Sum: '<S58>/Sum4'
       */
      rtDW->Gain1_k = 2.5E-5F * rtP.K1 * (rtDW->Delay1_DSTATE + rtDW->Gain1_p);

      /* DiscreteIntegrator: '<S58>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_o = 0.5F * rtDW->Gain1_k +
        rtDW->DiscreteTimeIntegrator_DSTATE_o;

      /* Sum: '<S58>/Sum5' */
      rtDW->U_re = rtDW->DiscreteTimeIntegrator_o + rtDW->Gain1_p;

      /* MATLAB Function: '<S25>/MATLAB Function' incorporates:
       *  Inport: '<Root>/Act_w_el'
       */
      MATLABFunction(rtDW->a, rtU->Act_w_el, &rtDW->Betrieb);

      /* Product: '<S58>/Product' incorporates:
       *  Gain: '<S58>/Gain6'
       */
      rtDW->Cos2 = rtDW->b * rtDW->DiscreteTimeIntegrator1_g;

      /* Gain: '<S58>/Gain2' incorporates:
       *  Delay: '<S58>/Delay'
       *  Sum: '<S58>/Sum2'
       */
      rtDW->a = 2.5E-5F * rtP.K1 * (rtDW->Cos2 + rtDW->Delay_DSTATE_l);

      /* DiscreteIntegrator: '<S58>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1 = 0.5F * rtDW->a +
        rtDW->DiscreteTimeIntegrator1_DSTATE;

      /* Sum: '<S58>/Sum6' */
      rtDW->U_im = rtDW->Cos2 + rtDW->DiscreteTimeIntegrator1;

      /* MATLAB Function: '<S58>/MATLAB Function' incorporates:
       *  Constant: '<S58>/Constant2'
       *  Product: '<S58>/Product6'
       */
      MATLABFunction_a(rtDW->U_re, 0.46F * rtDW->DiscreteTimeIntegrator,
                       rtDW->Betrieb, rtDW->U_im, &rtDW->Switch2, &rtDW->y);

      /* Product: '<S59>/Product4' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S59>/Constant1'
       *  Sum: '<S25>/Sum1'
       */
      rtDW->re_lim_e = (rtDW->c + -4.18879032F) * 2.0F;

      /* Product: '<S59>/Product5' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S59>/Constant1'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Sum'
       */
      rtDW->Gain1_p = (rtU->Act_theta_u_el + -4.18879032F) * 2.0F;

      /* Product: '<S59>/Product1' incorporates:
       *  Trigonometry: '<S59>/Cos'
       */
      rtDW->b = cosf(rtDW->Gain1_p) * rtDW->DiscreteTimeIntegrator1_g;

      /* Gain: '<S59>/Gain1' incorporates:
       *  Delay: '<S59>/Delay1'
       *  Sum: '<S59>/Sum4'
       */
      rtDW->Gain1_e = 2.5E-5F * rtP.K2 * (rtDW->Delay1_DSTATE_o + rtDW->b);

      /* DiscreteIntegrator: '<S59>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_k = 0.5F * rtDW->Gain1_e +
        rtDW->DiscreteTimeIntegrator_DSTATE_m;

      /* Sum: '<S59>/Sum5' */
      rtDW->U_re_c = rtDW->DiscreteTimeIntegrator_k + rtDW->b;

      /* Product: '<S59>/Product' incorporates:
       *  Gain: '<S59>/Gain'
       *  Trigonometry: '<S59>/Sin'
       */
      rtDW->Cos2 = rtDW->DiscreteTimeIntegrator1_g * -sinf(rtDW->Gain1_p);

      /* Gain: '<S59>/Gain2' incorporates:
       *  Delay: '<S59>/Delay'
       *  Sum: '<S59>/Sum2'
       */
      rtDW->Gain2_n = 2.5E-5F * rtP.K2 * (rtDW->Cos2 + rtDW->Delay_DSTATE_nv);

      /* DiscreteIntegrator: '<S59>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_e = 0.5F * rtDW->Gain2_n +
        rtDW->DiscreteTimeIntegrator1_DSTAT_f;

      /* Sum: '<S59>/Sum6' */
      rtDW->U_im_k = rtDW->Cos2 + rtDW->DiscreteTimeIntegrator1_e;

      /* MATLAB Function: '<S59>/MATLAB Function' incorporates:
       *  Constant: '<S59>/Constant2'
       *  Product: '<S59>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_c, 0.05F * rtDW->DiscreteTimeIntegrator,
                       rtDW->Betrieb, rtDW->U_im_k, &rtDW->re_lim, &rtDW->im_lim);

      /* Product: '<S59>/Product3' incorporates:
       *  Trigonometry: '<S59>/Cos1'
       */
      rtDW->Product3_m = cosf(rtDW->re_lim_e) * rtDW->re_lim;

      /* Product: '<S59>/Product2' incorporates:
       *  Gain: '<S59>/Gain3'
       *  Trigonometry: '<S59>/Sin1'
       */
      rtDW->Product2_i = rtDW->im_lim * -sinf(rtDW->re_lim_e);

      /* Product: '<S57>/Product4' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S57>/Constant1'
       *  Sum: '<S25>/Sum1'
       */
      rtDW->re_lim_e = (rtDW->c + -4.18879032F) * 3.0F;

      /* Product: '<S57>/Product5' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S57>/Constant1'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Sum'
       */
      rtDW->Cos2 = (rtU->Act_theta_u_el + -4.18879032F) * 3.0F;

      /* Gain: '<S57>/Gain4' */
      rtDW->b = rtP.K3 * rtDW->Product_d;

      /* Gain: '<S57>/Gain1' incorporates:
       *  Delay: '<S57>/Delay1'
       *  Product: '<S57>/Product1'
       *  Sum: '<S57>/Sum4'
       *  Trigonometry: '<S57>/Cos'
       */
      rtDW->Gain1_d = (cosf(rtDW->Cos2) * rtDW->b + rtDW->Delay1_DSTATE_d) *
        2.5E-5F;

      /* DiscreteIntegrator: '<S57>/Discrete-Time Integrator' */
      rtDW->U_re_m = 0.5F * rtDW->Gain1_d +
        rtDW->DiscreteTimeIntegrator_DSTAT_om;

      /* Gain: '<S57>/Gain2' incorporates:
       *  Delay: '<S57>/Delay'
       *  Gain: '<S57>/Gain'
       *  Product: '<S57>/Product'
       *  Sum: '<S57>/Sum2'
       *  Trigonometry: '<S57>/Sin'
       */
      rtDW->Gain2_c = (rtDW->b * -sinf(rtDW->Cos2) + rtDW->Delay_DSTATE_j) *
        2.5E-5F;

      /* DiscreteIntegrator: '<S57>/Discrete-Time Integrator1' */
      rtDW->U_im_c = 0.5F * rtDW->Gain2_c +
        rtDW->DiscreteTimeIntegrator1_DSTAT_a;

      /* MATLAB Function: '<S57>/MATLAB Function' incorporates:
       *  Constant: '<S57>/Constant'
       *  Product: '<S57>/Product6'
       */
      MATLABFunction_c(rtDW->U_re_m, 0.15F * rtDW->DiscreteTimeIntegrator,
                       rtDW->U_im_c, &rtDW->y_i, &rtDW->Gain1);

      /* Product: '<S57>/Product3' incorporates:
       *  Trigonometry: '<S57>/Cos1'
       */
      rtDW->Product3_h = cosf(rtDW->re_lim_e) * rtDW->y_i;

      /* Product: '<S57>/Product2' incorporates:
       *  Gain: '<S57>/Gain3'
       *  Trigonometry: '<S57>/Sin1'
       */
      rtDW->Product2_o = rtDW->Gain1 * -sinf(rtDW->re_lim_e);

      /* Product: '<S60>/Product4' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S60>/Constant1'
       *  Sum: '<S25>/Sum1'
       */
      rtDW->re_lim_e = (rtDW->c + -4.18879032F) * 4.0F;

      /* Product: '<S60>/Product5' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S60>/Constant1'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Sum'
       */
      rtDW->Gain1_p = (rtU->Act_theta_u_el + -4.18879032F) * 4.0F;

      /* Product: '<S60>/Product1' incorporates:
       *  Trigonometry: '<S60>/Cos'
       */
      rtDW->b = cosf(rtDW->Gain1_p) * rtDW->DiscreteTimeIntegrator1_g;

      /* Gain: '<S60>/Gain1' incorporates:
       *  Delay: '<S60>/Delay1'
       *  Sum: '<S60>/Sum4'
       */
      rtDW->Gain1_m = 2.5E-5F * rtP.K4 * (rtDW->Delay1_DSTATE_g + rtDW->b);

      /* DiscreteIntegrator: '<S60>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_a = 0.5F * rtDW->Gain1_m +
        rtDW->DiscreteTimeIntegrator_DSTATE_c;

      /* Sum: '<S60>/Sum5' */
      rtDW->U_re_n = rtDW->DiscreteTimeIntegrator_a + rtDW->b;

      /* Product: '<S60>/Product' incorporates:
       *  Gain: '<S60>/Gain'
       *  Trigonometry: '<S60>/Sin'
       */
      rtDW->Cos2 = rtDW->DiscreteTimeIntegrator1_g * -sinf(rtDW->Gain1_p);

      /* Gain: '<S60>/Gain2' incorporates:
       *  Delay: '<S60>/Delay'
       *  Sum: '<S60>/Sum2'
       */
      rtDW->Gain2_h = 2.5E-5F * rtP.K4 * (rtDW->Cos2 + rtDW->Delay_DSTATE_a);

      /* DiscreteIntegrator: '<S60>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_a = 0.5F * rtDW->Gain2_h +
        rtDW->DiscreteTimeIntegrator1_DSTAT_o;

      /* Sum: '<S60>/Sum6' */
      rtDW->U_im_p = rtDW->Cos2 + rtDW->DiscreteTimeIntegrator1_a;

      /* MATLAB Function: '<S60>/MATLAB Function' incorporates:
       *  Constant: '<S60>/Constant2'
       *  Product: '<S60>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_n, 0.025F * rtDW->DiscreteTimeIntegrator,
                       rtDW->Betrieb, rtDW->U_im_p, &rtDW->Cos2, &rtDW->b);

      /* Product: '<S60>/Product3' incorporates:
       *  Trigonometry: '<S60>/Cos1'
       */
      rtDW->Product3_l = cosf(rtDW->re_lim_e) * rtDW->Cos2;

      /* Product: '<S60>/Product2' incorporates:
       *  Gain: '<S60>/Gain3'
       *  Trigonometry: '<S60>/Sin1'
       */
      rtDW->Product2_l = rtDW->b * -sinf(rtDW->re_lim_e);

      /* Product: '<S61>/Product4' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S61>/Constant1'
       *  Sum: '<S25>/Sum1'
       */
      rtDW->c = (rtDW->c + -4.18879032F) * 6.0F;

      /* Product: '<S61>/Product5' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S61>/Constant1'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Sum'
       */
      rtDW->Product5_ju = (rtU->Act_theta_u_el + -4.18879032F) * 6.0F;

      /* Product: '<S61>/Product1' incorporates:
       *  Trigonometry: '<S61>/Cos'
       */
      rtDW->re_lim_e = cosf(rtDW->Product5_ju) * rtDW->DiscreteTimeIntegrator1_g;

      /* Delay: '<S61>/Delay1' */
      rtDW->Gain1_p = rtDW->Delay1_DSTATE_oi;

      /* Gain: '<S61>/Gain1' incorporates:
       *  Delay: '<S61>/Delay1'
       *  Sum: '<S61>/Sum4'
       */
      rtDW->Gain1_j = 2.5E-5F * rtP.K6 * (rtDW->Delay1_DSTATE_oi +
        rtDW->re_lim_e);

      /* DiscreteIntegrator: '<S61>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_n = 0.5F * rtDW->Gain1_j +
        rtDW->DiscreteTimeIntegrator_DSTATE_g;

      /* Sum: '<S61>/Sum5' */
      rtDW->U_re_d = rtDW->DiscreteTimeIntegrator_n + rtDW->re_lim_e;

      /* Product: '<S61>/Product' incorporates:
       *  Gain: '<S61>/Gain'
       *  Trigonometry: '<S61>/Sin'
       */
      rtDW->Product_d = rtDW->DiscreteTimeIntegrator1_g * -sinf
        (rtDW->Product5_ju);

      /* Delay: '<S61>/Delay' */
      rtDW->re_lim_e = rtDW->Delay_DSTATE_nm;

      /* Gain: '<S61>/Gain2' incorporates:
       *  Delay: '<S61>/Delay'
       *  Sum: '<S61>/Sum2'
       */
      rtDW->Product5_ju = 2.5E-5F * rtP.K6 * (rtDW->Product_d +
        rtDW->Delay_DSTATE_nm);

      /* DiscreteIntegrator: '<S61>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_g = 0.5F * rtDW->Product5_ju +
        rtDW->DiscreteTimeIntegrator1_DSTA_os;

      /* Sum: '<S61>/Sum6' */
      rtDW->Product_d += rtDW->DiscreteTimeIntegrator1_g;

      /* MATLAB Function: '<S61>/MATLAB Function' incorporates:
       *  Constant: '<S61>/Constant2'
       *  Product: '<S61>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_d, 0.01F * rtDW->DiscreteTimeIntegrator,
                       rtDW->Betrieb, rtDW->Product_d, &rtDW->re_lim_e,
                       &rtDW->Gain1_p);

      /* Outport: '<Root>/a_W' incorporates:
       *  Constant: '<S25>/Constant1'
       *  Gain: '<S58>/Gain3'
       *  Gain: '<S61>/Gain3'
       *  Product: '<S25>/Divide'
       *  Product: '<S58>/Product2'
       *  Product: '<S58>/Product3'
       *  Product: '<S58>/Product4'
       *  Product: '<S61>/Product2'
       *  Product: '<S61>/Product3'
       *  Sum: '<S25>/Add'
       *  Sum: '<S25>/Add1'
       *  Sum: '<S57>/Sum'
       *  Sum: '<S58>/Sum'
       *  Sum: '<S59>/Sum'
       *  Sum: '<S60>/Sum'
       *  Sum: '<S61>/Sum'
       *  Trigonometry: '<S58>/Cos1'
       *  Trigonometry: '<S58>/Sin1'
       *  Trigonometry: '<S61>/Cos1'
       *  Trigonometry: '<S61>/Sin1'
       */
      rtY->a_W = (((((cosf(rtDW->c_k) * rtDW->Switch2 + rtDW->y * -sinf
                      (rtDW->c_k)) + (rtDW->Product3_m + rtDW->Product2_i)) +
                    (rtDW->Product3_h + rtDW->Product2_o)) + (rtDW->Product3_l +
        rtDW->Product2_l)) + (cosf(rtDW->c) * rtDW->re_lim_e + rtDW->Gain1_p *
        -sinf(rtDW->c))) / rtDW->DiscreteTimeIntegrator + 0.5F;

      /* Merge: '<S10>/Merge5' incorporates:
       *  SignalConversion generated from: '<S25>/I_ref1'
       */
      rtDW->Merge5 = rtDW->Strom_kompensiert;

      /* Update for Delay: '<S58>/Delay1' incorporates:
       *  Sum: '<S58>/Sum3'
       */
      rtDW->Delay1_DSTATE = rtDW->Switch2 - rtDW->U_re;

      /* Update for DiscreteIntegrator: '<S58>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.5F * rtDW->Gain1_k +
        rtDW->DiscreteTimeIntegrator_o;

      /* Update for Delay: '<S58>/Delay' incorporates:
       *  Sum: '<S58>/Sum1'
       */
      rtDW->Delay_DSTATE_l = rtDW->y - rtDW->U_im;

      /* Update for DiscreteIntegrator: '<S58>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTATE = 0.5F * rtDW->a +
        rtDW->DiscreteTimeIntegrator1;

      /* Update for Delay: '<S59>/Delay1' incorporates:
       *  Sum: '<S59>/Sum3'
       */
      rtDW->Delay1_DSTATE_o = rtDW->re_lim - rtDW->U_re_c;

      /* Update for DiscreteIntegrator: '<S59>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.5F * rtDW->Gain1_e +
        rtDW->DiscreteTimeIntegrator_k;

      /* Update for Delay: '<S59>/Delay' incorporates:
       *  Sum: '<S59>/Sum1'
       */
      rtDW->Delay_DSTATE_nv = rtDW->im_lim - rtDW->U_im_k;

      /* Update for DiscreteIntegrator: '<S59>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.5F * rtDW->Gain2_n +
        rtDW->DiscreteTimeIntegrator1_e;

      /* Update for Delay: '<S57>/Delay1' incorporates:
       *  Sum: '<S57>/Sum3'
       */
      rtDW->Delay1_DSTATE_d = rtDW->y_i - rtDW->U_re_m;

      /* Update for DiscreteIntegrator: '<S57>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTAT_om = 0.5F * rtDW->Gain1_d +
        rtDW->U_re_m;

      /* Update for Delay: '<S57>/Delay' incorporates:
       *  Sum: '<S57>/Sum1'
       */
      rtDW->Delay_DSTATE_j = rtDW->Gain1 - rtDW->U_im_c;

      /* Update for DiscreteIntegrator: '<S57>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_a = 0.5F * rtDW->Gain2_c +
        rtDW->U_im_c;

      /* Update for Delay: '<S60>/Delay1' incorporates:
       *  Sum: '<S60>/Sum3'
       */
      rtDW->Delay1_DSTATE_g = rtDW->Cos2 - rtDW->U_re_n;

      /* Update for DiscreteIntegrator: '<S60>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.5F * rtDW->Gain1_m +
        rtDW->DiscreteTimeIntegrator_a;

      /* Update for Delay: '<S60>/Delay' incorporates:
       *  Sum: '<S60>/Sum1'
       */
      rtDW->Delay_DSTATE_a = rtDW->b - rtDW->U_im_p;

      /* Update for DiscreteIntegrator: '<S60>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.5F * rtDW->Gain2_h +
        rtDW->DiscreteTimeIntegrator1_a;

      /* Update for Delay: '<S61>/Delay1' incorporates:
       *  Sum: '<S61>/Sum3'
       */
      rtDW->Delay1_DSTATE_oi = rtDW->re_lim_e - rtDW->U_re_d;

      /* Update for DiscreteIntegrator: '<S61>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.5F * rtDW->Gain1_j +
        rtDW->DiscreteTimeIntegrator_n;

      /* Update for Delay: '<S61>/Delay' incorporates:
       *  Sum: '<S61>/Sum1'
       */
      rtDW->Delay_DSTATE_nm = rtDW->Gain1_p - rtDW->Product_d;

      /* Update for DiscreteIntegrator: '<S61>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTA_os = 0.5F * rtDW->Product5_ju +
        rtDW->DiscreteTimeIntegrator1_g;

      /* End of Outputs for SubSystem: '<S10>/Strangstromregler_asymetrisch2' */
    } else {
      /* Outputs for IfAction SubSystem: '<S10>/Switch Case Action Subsystem2' incorporates:
       *  ActionPort: '<S28>/Action Port'
       */
      /* Outport: '<Root>/a_W' */
      SwitchCaseActionSubsystem(&rtY->a_W, &rtDW->Merge5);

      /* End of Outputs for SubSystem: '<S10>/Switch Case Action Subsystem2' */
    }

    /* End of SwitchCase: '<S10>/Switch Case2' */
    /* End of Outputs for SubSystem: '<S2>/Regelung_asymetrisch' */
  } else {
    /* Outputs for IfAction SubSystem: '<S2>/aus' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    /* Outport: '<Root>/a_U' incorporates:
     *  Constant: '<S6>/Constant'
     *  SignalConversion generated from: '<S6>/a_U'
     */
    rtY->a_U = 0.5F;

    /* Outport: '<Root>/a_V' incorporates:
     *  Constant: '<S6>/Constant'
     *  SignalConversion generated from: '<S6>/a_V'
     */
    rtY->a_V = 0.5F;

    /* Outport: '<Root>/a_W' incorporates:
     *  Constant: '<S6>/Constant'
     *  SignalConversion generated from: '<S6>/a_W'
     */
    rtY->a_W = 0.5F;

    /* End of Outputs for SubSystem: '<S2>/aus' */
  }

  /* End of SwitchCase: '<S2>/switch_case_power' */

  /* Outport: '<Root>/I_re_Ref' */
  rtY->I_re_Ref = rtDW->I_re;

  /* Outport: '<Root>/I_im_Ref' */
  rtY->I_im_Ref = rtDW->I_im;

  /* Outport: '<Root>/Iu_ref' */
  rtY->Iu_ref = rtDW->Merge3;

  /* Outport: '<Root>/Iv_ref' */
  rtY->Iv_ref = rtDW->Merge4;

  /* Outport: '<Root>/Iw_ref' */
  rtY->Iw_ref = rtDW->Merge5;

  /* Outport: '<Root>/fault_peak_current_u' incorporates:
   *  Abs: '<S5>/Abs'
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/Act_Iu'
   *  RelationalOperator: '<S5>/Smaller'
   */
  rtY->fault_peak_current_u = (rtP.i_max_peak <= fabsf(rtU->Act_Iu));

  /* Math: '<S5>/Square' incorporates:
   *  Inport: '<Root>/Act_Iu'
   */
  rtDW->c = rtU->Act_Iu * rtU->Act_Iu;

  /* DiscreteIntegrator: '<S70>/Accumulator' incorporates:
   *  Delay: '<S70>/Delay'
   *  Sum: '<S70>/Sum'
   */
  rtDW->a = (rtDW->c - rtDW->Delay_DSTATE_k[0]) + rtDW->Accumulator_DSTATE;

  /* Outport: '<Root>/fault_rms_current_u' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Gain: '<S70>/Gain'
   *  RelationalOperator: '<S5>/Smaller1'
   *  Sqrt: '<S5>/Square Root'
   */
  rtY->fault_rms_current_u = (rtP.i_max_rms <= sqrtf(0.05F * rtDW->a));

  /* Outport: '<Root>/fault_peak_speed' incorporates:
   *  Constant: '<S5>/Constant2'
   *  Inport: '<Root>/Act_n'
   *  RelationalOperator: '<S5>/Smaller2'
   */
  rtY->fault_peak_speed = (rtP.n_max_peak <= rtU->Act_n);

  /* DiscreteIntegrator: '<S71>/Accumulator' incorporates:
   *  Delay: '<S71>/Delay'
   *  Inport: '<Root>/Act_n'
   *  Sum: '<S71>/Sum'
   */
  rtDW->b = (rtU->Act_n - rtDW->Delay_DSTATE_ki[0]) + rtDW->Accumulator_DSTATE_d;

  /* Outport: '<Root>/fault_max_speed' incorporates:
   *  Constant: '<S5>/Constant3'
   *  Gain: '<S71>/Gain'
   *  RelationalOperator: '<S5>/Smaller3'
   */
  rtY->fault_max_speed = (rtP.n_max <= 0.00833333377F * rtDW->b);

  /* Math: '<S5>/Square1' incorporates:
   *  Inport: '<Root>/Act_Iv'
   */
  rtDW->Gain1 = rtU->Act_Iv * rtU->Act_Iv;

  /* DiscreteIntegrator: '<S72>/Accumulator' incorporates:
   *  Delay: '<S72>/Delay'
   *  Sum: '<S72>/Sum'
   */
  rtDW->y_i = (rtDW->Gain1 - rtDW->Delay_DSTATE_kl[0]) +
    rtDW->Accumulator_DSTATE_f;

  /* Outport: '<Root>/fault_rms_current_v' incorporates:
   *  Constant: '<S5>/Constant5'
   *  Gain: '<S72>/Gain'
   *  RelationalOperator: '<S5>/Smaller5'
   *  Sqrt: '<S5>/Square Root1'
   */
  rtY->fault_rms_current_v = (rtP.i_max_rms <= sqrtf(0.05F * rtDW->y_i));

  /* Math: '<S5>/Square2' incorporates:
   *  Inport: '<Root>/Act_Iw'
   */
  rtDW->y = rtU->Act_Iw * rtU->Act_Iw;

  /* DiscreteIntegrator: '<S73>/Accumulator' incorporates:
   *  Delay: '<S73>/Delay'
   *  Sum: '<S73>/Sum'
   */
  rtDW->Switch2 = (rtDW->y - rtDW->Delay_DSTATE_b[0]) +
    rtDW->Accumulator_DSTATE_n;

  /* Outport: '<Root>/fault_rms_current_w' incorporates:
   *  Constant: '<S5>/Constant7'
   *  Gain: '<S73>/Gain'
   *  RelationalOperator: '<S5>/Smaller7'
   *  Sqrt: '<S5>/Square Root2'
   */
  rtY->fault_rms_current_w = (rtP.i_max_rms <= sqrtf(0.05F * rtDW->Switch2));

  /* Outport: '<Root>/fault_peak_current_v' incorporates:
   *  Abs: '<S5>/Abs1'
   *  Constant: '<S5>/Constant4'
   *  Inport: '<Root>/Act_Iv'
   *  RelationalOperator: '<S5>/Smaller4'
   */
  rtY->fault_peak_current_v = (rtP.i_max_peak <= fabsf(rtU->Act_Iv));

  /* Outport: '<Root>/fault_peak_current_w' incorporates:
   *  Abs: '<S5>/Abs2'
   *  Constant: '<S5>/Constant6'
   *  Inport: '<Root>/Act_Iw'
   *  RelationalOperator: '<S5>/Smaller6'
   */
  rtY->fault_peak_current_w = (rtP.i_max_peak <= fabsf(rtU->Act_Iw));

  /* Update for Delay: '<S3>/Delay' */
  rtDW->Delay_DSTATE = rtDW->DiscreteTimeIntegrator;

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE = 0.5F * rtDW->Gain +
    rtDW->DiscreteTimeIntegrator;

  /* Update for Delay: '<S70>/Delay' */
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 19; rtDW->idxDelay++) {
    rtDW->Delay_DSTATE_k[rtDW->idxDelay] = rtDW->Delay_DSTATE_k[rtDW->idxDelay +
      1];
  }

  rtDW->Delay_DSTATE_k[19] = rtDW->c;

  /* End of Update for Delay: '<S70>/Delay' */

  /* Update for DiscreteIntegrator: '<S70>/Accumulator' */
  rtDW->Accumulator_DSTATE = rtDW->a;

  /* Update for Delay: '<S71>/Delay' incorporates:
   *  Inport: '<Root>/Act_n'
   */
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 119; rtDW->idxDelay++) {
    rtDW->Delay_DSTATE_ki[rtDW->idxDelay] = rtDW->Delay_DSTATE_ki[rtDW->idxDelay
      + 1];
  }

  rtDW->Delay_DSTATE_ki[119] = rtU->Act_n;

  /* End of Update for Delay: '<S71>/Delay' */

  /* Update for DiscreteIntegrator: '<S71>/Accumulator' */
  rtDW->Accumulator_DSTATE_d = rtDW->b;

  /* Update for DiscreteIntegrator: '<S72>/Accumulator' */
  rtDW->Accumulator_DSTATE_f = rtDW->y_i;
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 19; rtDW->idxDelay++) {
    /* Update for Delay: '<S72>/Delay' */
    rtDW->Delay_DSTATE_kl[rtDW->idxDelay] = rtDW->Delay_DSTATE_kl[rtDW->idxDelay
      + 1];

    /* Update for Delay: '<S73>/Delay' */
    rtDW->Delay_DSTATE_b[rtDW->idxDelay] = rtDW->Delay_DSTATE_b[rtDW->idxDelay +
      1];
  }

  /* Update for Delay: '<S72>/Delay' */
  rtDW->Delay_DSTATE_kl[19] = rtDW->Gain1;

  /* Update for Delay: '<S73>/Delay' */
  rtDW->Delay_DSTATE_b[19] = rtDW->y;

  /* Update for DiscreteIntegrator: '<S73>/Accumulator' */
  rtDW->Accumulator_DSTATE_n = rtDW->Switch2;
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtY *rtY = (ExtY *) rtM->outputs;
  ExtU *rtU = (ExtU *) rtM->inputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void)memset(rtY, 0, sizeof(ExtY));

  /* Start for SwitchCase: '<S2>/switch_case_power' */
  rtDW->switch_case_power_ActiveSubsyst = -1;

  /* SystemInitialize for IfAction SubSystem: '<S2>/Regelung_asymetrisch' */
  /* Start for SwitchCase: '<S4>/Switch Case' */
  rtDW->SwitchCase_ActiveSubsystem = -1;

  /* Start for SwitchCase: '<S10>/Switch Case' */
  rtDW->SwitchCase_ActiveSubsystem_o = -1;

  /* Start for SwitchCase: '<S10>/Switch Case1' */
  rtDW->SwitchCase1_ActiveSubsystem = -1;

  /* Start for SwitchCase: '<S10>/Switch Case2' */
  rtDW->SwitchCase2_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: '<S4>/Drehzahlregler' */
  /* InitializeConditions for Delay: '<S14>/Delay' */
  rtDW->Delay_DSTATE_n = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_n = 0.0F;

  /* InitializeConditions for Delay: '<S7>/Delay' */
  rtDW->Delay_DSTATE_h = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_f = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S4>/Drehzahlregler' */

  /* SystemInitialize for Merge: '<S4>/Merge4' */
  rtDW->I_im = 0.0F;

  /* SystemInitialize for Merge: '<S8>/Merge1' */
  rtDW->Merge1 = 0.0F;

  /* SystemInitialize for Merge: '<S4>/Merge3' */
  rtDW->I_re = 0.0F;

  /* SystemInitialize for Merge: '<S8>/Merge' */
  rtDW->Merge = 0.0F;

  /* SystemInitialize for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch' */
  Strangstromregler_asymetri_Init(&rtDW->Strangstromregler_asymetrisch_h);

  /* End of SystemInitialize for SubSystem: '<S10>/Strangstromregler_asymetrisch' */

  /* SystemInitialize for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch1' */
  Strangstromregler_asymetri_Init(&rtDW->Strangstromregler_asymetrisch1);

  /* End of SystemInitialize for SubSystem: '<S10>/Strangstromregler_asymetrisch1' */

  /* SystemInitialize for IfAction SubSystem: '<S10>/Strangstromregler_asymetrisch2' */
  /* InitializeConditions for Delay: '<S58>/Delay1' */
  rtDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S58>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;

  /* InitializeConditions for Delay: '<S58>/Delay' */
  rtDW->Delay_DSTATE_l = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S58>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S59>/Delay1' */
  rtDW->Delay1_DSTATE_o = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S59>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.0F;

  /* InitializeConditions for Delay: '<S59>/Delay' */
  rtDW->Delay_DSTATE_nv = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S59>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.0F;

  /* InitializeConditions for Delay: '<S57>/Delay1' */
  rtDW->Delay1_DSTATE_d = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S57>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTAT_om = 0.0F;

  /* InitializeConditions for Delay: '<S57>/Delay' */
  rtDW->Delay_DSTATE_j = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S57>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_a = 0.0F;

  /* InitializeConditions for Delay: '<S60>/Delay1' */
  rtDW->Delay1_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S60>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.0F;

  /* InitializeConditions for Delay: '<S60>/Delay' */
  rtDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S60>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.0F;

  /* InitializeConditions for Delay: '<S61>/Delay1' */
  rtDW->Delay1_DSTATE_oi = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S61>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.0F;

  /* InitializeConditions for Delay: '<S61>/Delay' */
  rtDW->Delay_DSTATE_nm = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S61>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTA_os = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S10>/Strangstromregler_asymetrisch2' */

  /* SystemInitialize for Merge: '<S10>/Merge5' */
  rtDW->Merge5 = 0.0F;

  /* SystemInitialize for Merge: '<S10>/Merge4' */
  rtDW->Merge4 = 0.0F;

  /* SystemInitialize for Merge: '<S10>/Merge3' */
  rtDW->Merge3 = 0.0F;

  /* End of SystemInitialize for SubSystem: '<S2>/Regelung_asymetrisch' */

  /* SystemInitialize for Outport: '<Root>/I_re_Ref' */
  rtY->I_re_Ref = 0.0F;

  /* SystemInitialize for Outport: '<Root>/I_im_Ref' */
  rtY->I_im_Ref = 0.0F;

  /* SystemInitialize for Outport: '<Root>/Iu_ref' */
  rtY->Iu_ref = 0.0F;

  /* SystemInitialize for Outport: '<Root>/Iv_ref' */
  rtY->Iv_ref = 0.0F;

  /* SystemInitialize for Outport: '<Root>/Iw_ref' */
  rtY->Iw_ref = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
