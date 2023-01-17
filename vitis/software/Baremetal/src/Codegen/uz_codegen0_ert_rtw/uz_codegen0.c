/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 4.8
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Jan 17 15:19:36 2023
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
#include <float.h>
#include <string.h>
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */
extern real32_T rt_modf(real32_T u0, real32_T u1);
static uint32_T plook_u32u16u64n48_even8c_gf(uint16_T u, uint16_T bp0, uint32_T
  maxIndex, uint64_T *fraction);
static int16_T intrp1d_s16s32s32u32u64n48l_f(uint32_T bpIndex, uint64_T frac,
  const int16_T table[]);
static void SwitchCaseActionSubsystem3(real32_T *rty_Out1);
static void MATLABFunction(real32_T rtu_i_im, real32_T rtu_w, boolean_T
  *rty_Betrieb);
static void MATLABFunction_i(creal32_T rtu_Psi_PM_U, creal32_T rtu_Psi_PM_V,
  creal32_T rtu_Psi_PM_W, real32_T rtu_I_re, real32_T rtu_I_im, real32_T
  rtu_omega_el, uint8_T rtu_enable, real32_T *rty_I_re_mit, real32_T
  *rty_I_im_mit, real32_T *rty_I_re_gegen, real32_T *rty_I_im_gegen, real32_T
  *rty_I_re_null, real32_T *rty_I_im_null, DW_MATLABFunction_m *localDW);
static void cos_lookup_table(real32_T rtu_theta_el, real32_T *rty_cos2piu,
  real32_T *rty_sin2piu);
static void Subsystem(real32_T rtu_theta_el, real32_T *rty_costheta_el, real32_T
                      *rty_sintheta_el);
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
  rtu_Psi_PM_n, creal32_T rtu_Psi_PM_k, uint8_T rtu_fl_lookup_table, real32_T
  *rty_a, real32_T *rty_I_ref1, real32_T rtp_Offset_S, real32_T rtp_Offset_gegen,
  real32_T rtp_Offset_null, DW_Strangstromregler_asymetrisc *localDW);
static void SwitchCaseActionSubsystem(real32_T *rty_a, real32_T *rty_Iref);
static void sin_lookup_table(real32_T rtu_theta_el, real32_T *rty_sin2piu);
static void Subsystem_d(real32_T rtu_theta_el, real32_T *rty_sintheta_el);
static uint32_T plook_u32u16u64n48_even8c_gf(uint16_T u, uint16_T bp0, uint32_T
  maxIndex, uint64_T *fraction)
{
  uint32_T bpIndex;
  uint16_T fbpIndex;
  uint16_T uAdjust;

  /* Prelookup - Index and Fraction
     Index Search method: 'even'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'on'
     Rounding mode: 'floor'
   */
  uAdjust = (uint16_T)((uint32_T)u - bp0);
  fbpIndex = (uint16_T)((uint32_T)uAdjust >> 8U);
  if (fbpIndex < maxIndex) {
    bpIndex = fbpIndex;
    *fraction = (uint64_T)(uint16_T)(uAdjust & 255) << 40;
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = 281474976710656ULL;
  }

  return bpIndex;
}

static int16_T intrp1d_s16s32s32u32u64n48l_f(uint32_T bpIndex, uint64_T frac,
  const int16_T table[])
{
  int16_T yL_0d0;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Rounding mode: 'floor'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[bpIndex];
  return (int16_T)((int16_T)(((table[bpIndex + 1U] - yL_0d0) * (int64_T)frac) >>
    48) + yL_0d0);
}

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
 *    '<S140>/MATLAB Function'
 *    '<S250>/MATLAB Function'
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

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/Referenzstromerzeugung_asymetrisch/MATLAB Function': '<S35>:1' */
  /*  Up = Polradspannung, induced Voltage, back emf (als komplexen Vektor) */
  /*  i_q =  referenz q-Strom (als reeler Wert) */
  /* '<S35>:1:4' if enable == 1 */
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

    /* '<S35>:1:5' p=18; */
    /*  Polpaarzahl */
    /*     %% Matrizen für symetrische Komponenten */
    /*  */
    /* '<S35>:1:8' a=single(exp(1i*(2*pi/3))); */
    /* '<S35>:1:9' T=single([1   1   1;  a^2 a   1; a   a^2 1]); */
    /*     %% Eingangsvektoren */
    /* '<S35>:1:11' U=[Psi_PM_U; Psi_PM_V;Psi_PM_W].*omega_el; */
    /* '<S35>:1:12' I_U=single(I_im*exp(1i*(-0*pi/3))); */
    /* '<S35>:1:13' I_V=single(I_im*exp(1i*(-2*pi/3))); */
    I_V_re_tmp = rtu_I_im * -0.5F;
    I_V_im = rtu_I_im * -0.866025388F;

    /* '<S35>:1:14' I_W=single(I_im*exp(1i*(-4*pi/3))); */
    I_W_im = rtu_I_im * 0.866025388F;

    /* '<S35>:1:15' I=single([I_U;I_V;I_W]); */
    /*  Symetrische Komponenten von Spannung */
    /*  Komponenten (1. Dimensoin -> Mit.-,Gegen-,Nullkomponente; 2. Dimension -> */
    /*  Phase 1,2,3 */
    /*  */
    /* '<S35>:1:20' U_sym_komp_hilf=single((inv(T)*U)); */
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
    /* '<S35>:1:21' U_sym_komp=single(zeros(3,3)*(0+0i)); */
    /*  Mitkomponente */
    /* '<S35>:1:23' U_sym_komp(1,1)=single(U_sym_komp_hilf(1)*1); */
    /* '<S35>:1:24' U_sym_komp(1,2)=single(U_sym_komp_hilf(1)*a^2); */
    /* '<S35>:1:25' U_sym_komp(1,3)=single(U_sym_komp_hilf(1)*a); */
    /*  Gegenkomponente */
    /* '<S35>:1:27' U_sym_komp(2,1)=single(U_sym_komp_hilf(2)*1); */
    /* '<S35>:1:28' U_sym_komp(2,2)=single(U_sym_komp_hilf(2)*a); */
    rtu_Psi_PM_U_idx_0_im = localDW->U_sym_komp_hilf[1].re * -0.5F;
    U_sym_komp_idx_4_re = rtu_Psi_PM_U_idx_0_im - localDW->U_sym_komp_hilf[1].im
      * 0.866025388F;
    rtu_Psi_PM_U_idx_0_re = localDW->U_sym_komp_hilf[1].im * -0.5F;
    U_sym_komp_idx_4_im = localDW->U_sym_komp_hilf[1].re * 0.866025388F +
      rtu_Psi_PM_U_idx_0_re;

    /* '<S35>:1:29' U_sym_komp(2,3)=single(U_sym_komp_hilf(2)*a^2); */
    U_sym_komp_idx_7_re = rtu_Psi_PM_U_idx_0_im - localDW->U_sym_komp_hilf[1].im
      * -0.866025388F;
    U_sym_komp_idx_7_im = localDW->U_sym_komp_hilf[1].re * -0.866025388F +
      rtu_Psi_PM_U_idx_0_re;

    /*  Nullkomponente */
    /* '<S35>:1:31' U_sym_komp(3,1)=single(U_sym_komp_hilf(3)*1); */
    /* '<S35>:1:32' U_sym_komp(3,2)=single(U_sym_komp_hilf(3)*1); */
    /* '<S35>:1:33' U_sym_komp(3,3)=single(U_sym_komp_hilf(3)*1); */
    /*     %% Kompensation von U_g+U_0 */
    /* '<S35>:1:35' I_Gegen_U=single(-(I_U*(U_sym_komp(2,1)+U_sym_komp(3,1)))/(U_sym_komp(1,1)+U_sym_komp(2,1)+U_sym_komp(3,1))); */
    /* '<S35>:1:36' I_Gegen_V=single(-(I_V*(U_sym_komp(2,2)+U_sym_komp(3,2)))/(U_sym_komp(1,2)+U_sym_komp(2,2)+U_sym_komp(3,2))); */
    /* '<S35>:1:37' I_Gegen_W=single(-(I_W*(U_sym_komp(2,3)+U_sym_komp(3,3)))/(U_sym_komp(1,3)+U_sym_komp(2,3)+U_sym_komp(3,3))); */
    /* '<S35>:1:38' I_Mit=single(I); */
    /*  */
    /* '<S35>:1:40' I_Gegen=single([I_Gegen_U; I_Gegen_V; I_Gegen_W]); */
    /* '<S35>:1:41' I_compensation=single((I_Gegen+I_Mit)); */
    /* '<S35>:1:42' I_compensation_sym_components=single((inv(T)*I_compensation)); */
    /* .*[1 a^2 a; 1 a a^2;1 1 1])); */
    /* '<S35>:1:43' I_compensation_sym_components=single(I_compensation_sym_components.*exp(1i*(pi/2))); */
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
    /* '<S35>:1:47' I_re_mit=single(real(I_compensation_sym_components(1,1))); */
    *rty_I_re_mit = localDW->U_sym_komp_hilf[0].re;

    /* '<S35>:1:48' I_im_mit=single(imag(I_compensation_sym_components(1,1))); */
    *rty_I_im_mit = localDW->U_sym_komp_hilf[0].im;

    /* '<S35>:1:49' I_re_gegen=single(real(I_compensation_sym_components(2,1))); */
    *rty_I_re_gegen = localDW->U_sym_komp_hilf[1].re;

    /* '<S35>:1:50' I_im_gegen=single(imag(I_compensation_sym_components(2,1))); */
    *rty_I_im_gegen = localDW->U_sym_komp_hilf[1].im;

    /* '<S35>:1:51' I_re_null=single(real(I_compensation_sym_components(3,1))); */
    *rty_I_re_null = localDW->U_sym_komp_hilf[2].re;

    /* '<S35>:1:52' I_im_null=single(imag(I_compensation_sym_components(3,1))); */
    *rty_I_im_null = localDW->U_sym_komp_hilf[2].im;

    /*  */
  } else {
    /* '<S35>:1:54' else */
    /*     %% Output as single */
    /* '<S35>:1:56' I_re_mit=single(I_re); */
    *rty_I_re_mit = rtu_I_re;

    /* '<S35>:1:57' I_im_mit=single(I_im); */
    *rty_I_im_mit = rtu_I_im;

    /* '<S35>:1:58' I_re_gegen=single(0); */
    *rty_I_re_gegen = 0.0F;

    /* '<S35>:1:59' I_im_gegen=single(0); */
    *rty_I_im_gegen = 0.0F;

    /* '<S35>:1:60' I_re_null=single(0); */
    *rty_I_re_null = 0.0F;

    /* '<S35>:1:61' I_im_null=single(0); */
    *rty_I_im_null = 0.0F;
  }
}

real32_T rt_modf(real32_T u0, real32_T u1)
{
  real32_T y;
  y = u0;
  if (u1 == 0.0F) {
    if (u0 == 0.0F) {
      y = u1;
    }
  } else if (u0 == 0.0F) {
    y = 0.0F / u1;
  } else {
    boolean_T yEq;
    y = fmodf(u0, u1);
    yEq = (y == 0.0F);
    if ((!yEq) && (u1 > floorf(u1))) {
      real32_T q;
      q = fabsf(u0 / u1);
      yEq = (fabsf(q - floorf(q + 0.5F)) <= FLT_EPSILON * q);
    }

    if (yEq) {
      y = 0.0F;
    } else if ((u0 < 0.0F) != (u1 < 0.0F)) {
      y += u1;
    }
  }

  return y;
}

/*
 * Output and update for action system:
 *    '<S36>/cos_lookup_table'
 *    '<S37>/cos_lookup_table'
 *    '<S38>/cos_lookup_table'
 *    '<S64>/cos_lookup_table'
 *    '<S65>/cos_lookup_table'
 *    '<S83>/cos_lookup_table'
 *    '<S84>/cos_lookup_table'
 *    '<S102>/cos_lookup_table'
 *    '<S103>/cos_lookup_table'
 *    '<S121>/cos_lookup_table'
 *    ...
 */
static void cos_lookup_table(real32_T rtu_theta_el, real32_T *rty_cos2piu,
  real32_T *rty_sin2piu)
{
  uint64_T frac;
  uint32_T bpIdx;
  int16_T rtb_SignCorrected_n;
  uint16_T rtb_CastU16En16_c;
  uint16_T rtb_CastU16En16_i;
  boolean_T rtb_GTEp75;
  boolean_T rtb_LTEp25_a;

  /* DataTypeConversion: '<S44>/CastU16En16' incorporates:
   *  Constant: '<S40>/Constant'
   *  DataTypeConversion: '<S46>/CastU16En16'
   *  Gain: '<S40>/Gain4'
   *  Math: '<S40>/Mod'
   */
  rtb_CastU16En16_i = (uint16_T)(0.159154937F * rt_modf(rtu_theta_el,
    6.28318548F) * 65536.0F);

  /* RelationalOperator: '<S44>/LTEp25' incorporates:
   *  DataTypeConversion: '<S44>/CastU16En16'
   */
  rtb_LTEp25_a = (rtb_CastU16En16_i <= 16384);

  /* RelationalOperator: '<S44>/GTEp75' incorporates:
   *  DataTypeConversion: '<S44>/CastU16En16'
   */
  rtb_GTEp75 = (rtb_CastU16En16_i >= 49152);

  /* Switch: '<S44>/QuadHandle2' incorporates:
   *  Constant: '<S44>/Point75'
   *  DataTypeConversion: '<S44>/CastU16En16'
   *  RelationalOperator: '<S44>/LTEp50'
   *  Sum: '<S44>/p75mA'
   *  Switch: '<S44>/QuadHandle1b'
   */
  if (rtb_CastU16En16_i <= 32768) {
    /* Switch: '<S44>/QuadHandle1a' incorporates:
     *  Constant: '<S44>/Point25'
     *  Sum: '<S44>/Amp25'
     *  Sum: '<S44>/p25mA'
     */
    if (rtb_LTEp25_a) {
      rtb_CastU16En16_c = (uint16_T)(16384 - rtb_CastU16En16_i);
    } else {
      rtb_CastU16En16_c = (uint16_T)(rtb_CastU16En16_i - 16384);
    }

    /* End of Switch: '<S44>/QuadHandle1a' */
  } else if (rtb_GTEp75) {
    /* Switch: '<S44>/QuadHandle1b' incorporates:
     *  Constant: '<S44>/Point75'
     *  Sum: '<S44>/Amp75'
     */
    rtb_CastU16En16_c = (uint16_T)(rtb_CastU16En16_i - 49152);
  } else {
    rtb_CastU16En16_c = (uint16_T)(49152 - rtb_CastU16En16_i);
  }

  /* End of Switch: '<S44>/QuadHandle2' */

  /* Lookup_n-D: '<S43>/Look-Up Table' */
  bpIdx = plook_u32u16u64n48_even8c_gf(rtb_CastU16En16_c, 0U, 64U, &frac);

  /* Switch: '<S44>/SignCorrected' incorporates:
   *  Logic: '<S44>/1st or 4th Quad'
   *  Lookup_n-D: '<S43>/Look-Up Table'
   *  Switch: '<S46>/SignCorrected'
   *  UnaryMinus: '<S44>/Negate'
   */
  if (rtb_LTEp25_a || rtb_GTEp75) {
    rtb_SignCorrected_n = intrp1d_s16s32s32u32u64n48l_f(bpIdx, frac,
      rtConstP.pooled16);
  } else {
    rtb_SignCorrected_n = (int16_T)-intrp1d_s16s32s32u32u64n48l_f(bpIdx, frac,
      rtConstP.pooled16);
  }

  /* End of Switch: '<S44>/SignCorrected' */

  /* DataTypeConversion: '<S40>/Data Type Conversion' incorporates:
   *  Switch: '<S46>/SignCorrected'
   */
  *rty_cos2piu = (real32_T)rtb_SignCorrected_n * 6.10351562E-5F;

  /* RelationalOperator: '<S46>/LTEp50' */
  rtb_LTEp25_a = (rtb_CastU16En16_i <= 32768);

  /* Switch: '<S46>/QuadHandle1' incorporates:
   *  Constant: '<S46>/Point50'
   *  Sum: '<S46>/Amp50'
   */
  if (!rtb_LTEp25_a) {
    rtb_CastU16En16_i = (uint16_T)(rtb_CastU16En16_i - 32768);
  }

  /* End of Switch: '<S46>/QuadHandle1' */

  /* Switch: '<S46>/QuadHandle2' incorporates:
   *  Constant: '<S46>/Point50'
   *  RelationalOperator: '<S46>/LTEp25'
   *  Sum: '<S46>/p50mA'
   *  Switch: '<S46>/QuadHandle1'
   */
  if (rtb_CastU16En16_i > 16384) {
    rtb_CastU16En16_i = (uint16_T)(32768 - rtb_CastU16En16_i);
  }

  /* End of Switch: '<S46>/QuadHandle2' */

  /* Lookup_n-D: '<S45>/Look-Up Table' incorporates:
   *  Switch: '<S46>/QuadHandle2'
   */
  bpIdx = plook_u32u16u64n48_even8c_gf(rtb_CastU16En16_i, 0U, 64U, &frac);

  /* Switch: '<S46>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S45>/Look-Up Table'
   *  UnaryMinus: '<S46>/Negate'
   */
  if (rtb_LTEp25_a) {
    rtb_SignCorrected_n = intrp1d_s16s32s32u32u64n48l_f(bpIdx, frac,
      rtConstP.pooled16);
  } else {
    rtb_SignCorrected_n = (int16_T)-intrp1d_s16s32s32u32u64n48l_f(bpIdx, frac,
      rtConstP.pooled16);
  }

  /* End of Switch: '<S46>/SignCorrected' */

  /* DataTypeConversion: '<S40>/Data Type Conversion1' incorporates:
   *  Switch: '<S46>/SignCorrected'
   */
  *rty_sin2piu = (real32_T)rtb_SignCorrected_n * 6.10351562E-5F;
}

/*
 * Output and update for action system:
 *    '<S36>/Subsystem'
 *    '<S37>/Subsystem'
 *    '<S38>/Subsystem'
 *    '<S64>/Subsystem'
 *    '<S65>/Subsystem'
 *    '<S83>/Subsystem'
 *    '<S84>/Subsystem'
 *    '<S102>/Subsystem'
 *    '<S103>/Subsystem'
 *    '<S121>/Subsystem'
 *    ...
 */
static void Subsystem(real32_T rtu_theta_el, real32_T *rty_costheta_el, real32_T
                      *rty_sintheta_el)
{
  /* DataTypeConversion: '<S39>/Data Type Conversion' incorporates:
   *  Trigonometry: '<S39>/Cos'
   */
  *rty_costheta_el = cosf(rtu_theta_el);

  /* DataTypeConversion: '<S39>/Data Type Conversion1' incorporates:
   *  Trigonometry: '<S39>/Sin'
   */
  *rty_sintheta_el = sinf(rtu_theta_el);
}

/*
 * Output and update for atomic system:
 *    '<S31>/MATLAB Function'
 *    '<S32>/MATLAB Function'
 *    '<S33>/MATLAB Function'
 *    '<S34>/MATLAB Function'
 *    '<S141>/MATLAB Function'
 *    '<S142>/MATLAB Function'
 *    '<S143>/MATLAB Function'
 *    '<S144>/MATLAB Function'
 *    '<S251>/MATLAB Function'
 *    '<S252>/MATLAB Function'
 *    ...
 */
static void MATLABFunction_a(real32_T rtu_re, real32_T rtu_U_lim, boolean_T
  rtu_Betrieb, real32_T rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim)
{
  real32_T re_lim;
  real32_T rtu_im_0;
  real32_T tmp;

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/resonater-PI-Regler/MATLAB Function': '<S63>:1' */
  /* '<S63>:1:2' if (re^2 + im^2)<=U_lim^2 */
  tmp = rtu_U_lim * rtu_U_lim;
  if (rtu_re * rtu_re + rtu_im * rtu_im <= tmp) {
    /* '<S63>:1:3' re_lim = re; */
    re_lim = rtu_re;

    /* '<S63>:1:4' im_lim = im; */
    rtu_im_0 = rtu_im;
  } else if (!rtu_Betrieb) {
    /* '<S63>:1:5' elseif Betrieb == 0 */
    /* Generator */
    /* '<S63>:1:7' if abs(im)>0.95*U_lim */
    if (fabsf(rtu_im) > 0.95F * rtu_U_lim) {
      /* '<S63>:1:8' im_lim = sign(im)*0.95*U_lim; */
      if (rtu_im < 0.0F) {
        rtu_im_0 = -1.0F;
      } else {
        rtu_im_0 = (real32_T)(rtu_im > 0.0F);
      }

      rtu_im_0 = rtu_im_0 * 0.95F * rtu_U_lim;
    } else {
      /* '<S63>:1:9' else */
      /* '<S63>:1:10' im_lim = im; */
      rtu_im_0 = rtu_im;
    }

    /* '<S63>:1:12' re_lim = sign(re)*sqrt(U_lim^2 - im_lim^2); */
    if (rtu_re < 0.0F) {
      re_lim = -1.0F;
    } else {
      re_lim = (real32_T)(rtu_re > 0.0F);
    }

    re_lim *= sqrtf(tmp - rtu_im_0 * rtu_im_0);
  } else {
    /* '<S63>:1:13' else */
    /* Motor */
    /* '<S63>:1:15' if abs(re)>0.95*U_lim */
    if (fabsf(rtu_re) > 0.95F * rtu_U_lim) {
      /* '<S63>:1:16' re_lim = sign(re)*0.95*U_lim; */
      if (rtu_re < 0.0F) {
        re_lim = -1.0F;
      } else {
        re_lim = (real32_T)(rtu_re > 0.0F);
      }

      re_lim = re_lim * 0.95F * rtu_U_lim;
    } else {
      /* '<S63>:1:17' else */
      /* '<S63>:1:18' re_lim = re; */
      re_lim = rtu_re;
    }

    /* '<S63>:1:20' im_lim = sign(im)*sqrt(U_lim^2 - re_lim^2); */
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
  /* InitializeConditions for Delay: '<S31>/Delay1' */
  localDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S31>/Delay' */
  localDW->Delay_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S32>/Delay1' */
  localDW->Delay1_DSTATE_m = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_d = 0.0F;

  /* InitializeConditions for Delay: '<S32>/Delay' */
  localDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_m = 0.0F;

  /* InitializeConditions for Delay: '<S33>/Delay1' */
  localDW->Delay1_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_i = 0.0F;

  /* InitializeConditions for Delay: '<S33>/Delay' */
  localDW->Delay_DSTATE_b = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_k = 0.0F;

  /* InitializeConditions for Delay: '<S34>/Delay1' */
  localDW->Delay1_DSTATE_i = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_if = 0.0F;

  /* InitializeConditions for Delay: '<S34>/Delay' */
  localDW->Delay_DSTATE_h = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
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
  /* InitializeConditions for Delay: '<S31>/Delay1' */
  localDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S31>/Delay' */
  localDW->Delay_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S32>/Delay1' */
  localDW->Delay1_DSTATE_m = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_d = 0.0F;

  /* InitializeConditions for Delay: '<S32>/Delay' */
  localDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_m = 0.0F;

  /* InitializeConditions for Delay: '<S33>/Delay1' */
  localDW->Delay1_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_i = 0.0F;

  /* InitializeConditions for Delay: '<S33>/Delay' */
  localDW->Delay_DSTATE_b = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_k = 0.0F;

  /* InitializeConditions for Delay: '<S34>/Delay1' */
  localDW->Delay1_DSTATE_i = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_if = 0.0F;

  /* InitializeConditions for Delay: '<S34>/Delay' */
  localDW->Delay_DSTATE_h = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
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
  rtu_Psi_PM_n, creal32_T rtu_Psi_PM_k, uint8_T rtu_fl_lookup_table, real32_T
  *rty_a, real32_T *rty_I_ref1, real32_T rtp_Offset_S, real32_T rtp_Offset_gegen,
  real32_T rtp_Offset_null, DW_Strangstromregler_asymetrisc *localDW)
{
  /* Sum: '<S23>/Sum1' incorporates:
   *  Constant: '<S23>/Constant'
   */
  localDW->Delay1_g = rtu_Theta_u_back + rtp_Offset_S;

  /* SwitchCase: '<S65>/Switch Case' incorporates:
   *  Product: '<S31>/Product4'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S65>/cos_lookup_table' incorporates:
     *  ActionPort: '<S75>/Action Port'
     */
    cos_lookup_table(localDW->Delay1_g, &localDW->re_lim_i, &localDW->Add1_l);

    /* End of Outputs for SubSystem: '<S65>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S65>/Subsystem' incorporates:
     *  ActionPort: '<S74>/Action Port'
     */
    Subsystem(localDW->Delay1_g, &localDW->re_lim_i, &localDW->Add1_l);

    /* End of Outputs for SubSystem: '<S65>/Subsystem' */
  }

  /* End of SwitchCase: '<S65>/Switch Case' */

  /* Sum: '<S23>/Sum' incorporates:
   *  Constant: '<S23>/Constant'
   */
  localDW->theta_e = rtu_Theta_u + rtp_Offset_S;

  /* SwitchCase: '<S64>/Switch Case' incorporates:
   *  Product: '<S31>/Product5'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S64>/cos_lookup_table' incorporates:
     *  ActionPort: '<S67>/Action Port'
     */
    cos_lookup_table(localDW->theta_e, &localDW->Product1_a, &localDW->im_lim_l);

    /* End of Outputs for SubSystem: '<S64>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S64>/Subsystem' incorporates:
     *  ActionPort: '<S66>/Action Port'
     */
    Subsystem(localDW->theta_e, &localDW->Product1_a, &localDW->im_lim_l);

    /* End of Outputs for SubSystem: '<S64>/Subsystem' */
  }

  /* End of SwitchCase: '<S64>/Switch Case' */

  /* SwitchCase: '<S36>/Switch Case' */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S36>/cos_lookup_table' incorporates:
     *  ActionPort: '<S40>/Action Port'
     */
    cos_lookup_table(localDW->theta_e, &localDW->Merge_oy, &localDW->Merge1_h);

    /* End of Outputs for SubSystem: '<S36>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S36>/Subsystem' incorporates:
     *  ActionPort: '<S39>/Action Port'
     */
    Subsystem(localDW->theta_e, &localDW->Merge_oy, &localDW->Merge1_h);

    /* End of Outputs for SubSystem: '<S36>/Subsystem' */
  }

  /* End of SwitchCase: '<S36>/Switch Case' */

  /* SwitchCase: '<S37>/Switch Case' incorporates:
   *  Constant: '<S23>/Constant2'
   *  Sum: '<S23>/Add2'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S37>/cos_lookup_table' incorporates:
     *  ActionPort: '<S48>/Action Port'
     */
    cos_lookup_table(localDW->theta_e + rtp_Offset_gegen, &localDW->im_lim_mv,
                     &localDW->re_lim_l);

    /* End of Outputs for SubSystem: '<S37>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S37>/Subsystem' incorporates:
     *  ActionPort: '<S47>/Action Port'
     */
    Subsystem(localDW->theta_e + rtp_Offset_gegen, &localDW->im_lim_mv,
              &localDW->re_lim_l);

    /* End of Outputs for SubSystem: '<S37>/Subsystem' */
  }

  /* End of SwitchCase: '<S37>/Switch Case' */

  /* SwitchCase: '<S38>/Switch Case' incorporates:
   *  Constant: '<S23>/Constant3'
   *  Sum: '<S23>/Add3'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S38>/cos_lookup_table' incorporates:
     *  ActionPort: '<S56>/Action Port'
     */
    cos_lookup_table(localDW->theta_e + rtp_Offset_null, &localDW->Product_am,
                     &localDW->Strom_kompensiert_l);

    /* End of Outputs for SubSystem: '<S38>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S38>/Subsystem' incorporates:
     *  ActionPort: '<S55>/Action Port'
     */
    Subsystem(localDW->theta_e + rtp_Offset_null, &localDW->Product_am,
              &localDW->Strom_kompensiert_l);

    /* End of Outputs for SubSystem: '<S38>/Subsystem' */
  }

  /* End of SwitchCase: '<S38>/Switch Case' */

  /* SwitchCase: '<S83>/Switch Case' incorporates:
   *  Constant: '<S32>/Constant1'
   *  Product: '<S32>/Product5'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S83>/cos_lookup_table' incorporates:
     *  ActionPort: '<S86>/Action Port'
     */
    cos_lookup_table(localDW->theta_e * 2.0F, &localDW->Delay1_c,
                     &localDW->im_lim_k);

    /* End of Outputs for SubSystem: '<S83>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S83>/Subsystem' incorporates:
     *  ActionPort: '<S85>/Action Port'
     */
    Subsystem(localDW->theta_e * 2.0F, &localDW->Delay1_c, &localDW->im_lim_k);

    /* End of Outputs for SubSystem: '<S83>/Subsystem' */
  }

  /* End of SwitchCase: '<S83>/Switch Case' */

  /* SwitchCase: '<S84>/Switch Case' incorporates:
   *  Constant: '<S32>/Constant1'
   *  Product: '<S32>/Product4'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S84>/cos_lookup_table' incorporates:
     *  ActionPort: '<S94>/Action Port'
     */
    cos_lookup_table(localDW->Delay1_g * 2.0F, &localDW->Merge_gt,
                     &localDW->Sum_j);

    /* End of Outputs for SubSystem: '<S84>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S84>/Subsystem' incorporates:
     *  ActionPort: '<S93>/Action Port'
     */
    Subsystem(localDW->Delay1_g * 2.0F, &localDW->Merge_gt, &localDW->Sum_j);

    /* End of Outputs for SubSystem: '<S84>/Subsystem' */
  }

  /* End of SwitchCase: '<S84>/Switch Case' */

  /* SwitchCase: '<S102>/Switch Case' incorporates:
   *  Constant: '<S33>/Constant1'
   *  Product: '<S33>/Product5'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S102>/cos_lookup_table' incorporates:
     *  ActionPort: '<S105>/Action Port'
     */
    cos_lookup_table(localDW->theta_e * 4.0F, &localDW->re_lim_b,
                     &localDW->Delay1_m);

    /* End of Outputs for SubSystem: '<S102>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S102>/Subsystem' incorporates:
     *  ActionPort: '<S104>/Action Port'
     */
    Subsystem(localDW->theta_e * 4.0F, &localDW->re_lim_b, &localDW->Delay1_m);

    /* End of Outputs for SubSystem: '<S102>/Subsystem' */
  }

  /* End of SwitchCase: '<S102>/Switch Case' */

  /* SwitchCase: '<S103>/Switch Case' incorporates:
   *  Constant: '<S33>/Constant1'
   *  Product: '<S33>/Product4'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S103>/cos_lookup_table' incorporates:
     *  ActionPort: '<S113>/Action Port'
     */
    cos_lookup_table(localDW->Delay1_g * 4.0F, &localDW->Merge_ac,
                     &localDW->Sum_o);

    /* End of Outputs for SubSystem: '<S103>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S103>/Subsystem' incorporates:
     *  ActionPort: '<S112>/Action Port'
     */
    Subsystem(localDW->Delay1_g * 4.0F, &localDW->Merge_ac, &localDW->Sum_o);

    /* End of Outputs for SubSystem: '<S103>/Subsystem' */
  }

  /* End of SwitchCase: '<S103>/Switch Case' */

  /* SwitchCase: '<S121>/Switch Case' incorporates:
   *  Constant: '<S34>/Constant1'
   *  Product: '<S34>/Product5'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S121>/cos_lookup_table' incorporates:
     *  ActionPort: '<S124>/Action Port'
     */
    cos_lookup_table(localDW->theta_e * 6.0F, &localDW->im_lim_o,
                     &localDW->re_lim_g);

    /* End of Outputs for SubSystem: '<S121>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S121>/Subsystem' incorporates:
     *  ActionPort: '<S123>/Action Port'
     */
    Subsystem(localDW->theta_e * 6.0F, &localDW->im_lim_o, &localDW->re_lim_g);

    /* End of Outputs for SubSystem: '<S121>/Subsystem' */
  }

  /* End of SwitchCase: '<S121>/Switch Case' */

  /* SwitchCase: '<S122>/Switch Case' incorporates:
   *  Constant: '<S34>/Constant1'
   *  Product: '<S34>/Product4'
   */
  if (rtu_fl_lookup_table == 1) {
    /* Outputs for IfAction SubSystem: '<S122>/cos_lookup_table' incorporates:
     *  ActionPort: '<S132>/Action Port'
     */
    cos_lookup_table(localDW->Delay1_g * 6.0F, &localDW->theta_e,
                     &localDW->Sum_d);

    /* End of Outputs for SubSystem: '<S122>/cos_lookup_table' */
  } else {
    /* Outputs for IfAction SubSystem: '<S122>/Subsystem' incorporates:
     *  ActionPort: '<S131>/Action Port'
     */
    Subsystem(localDW->Delay1_g * 6.0F, &localDW->theta_e, &localDW->Sum_d);

    /* End of Outputs for SubSystem: '<S122>/Subsystem' */
  }

  /* End of SwitchCase: '<S122>/Switch Case' */

  /* MATLAB Function: '<S30>/MATLAB Function' */
  MATLABFunction_i(rtu_Psi_PM, rtu_Psi_PM_n, rtu_Psi_PM_k, rtu_I_re, rtu_I_im,
                   rtu_w1, rtu_enable_compensation_current, &localDW->Delay1_g,
                   &localDW->I_im_mit_e, &localDW->I_re_gegen_e,
                   &localDW->I_im_gegen_g, &localDW->I_re_null_k,
                   &localDW->I_im_null_n, &localDW->sf_MATLABFunction_i);

  /* Sum: '<S30>/Strom_kompensiert' incorporates:
   *  Gain: '<S30>/Gain'
   *  Gain: '<S30>/Gain1'
   *  Gain: '<S30>/Gain2'
   *  Product: '<S30>/Product'
   *  Product: '<S30>/Product1'
   *  Product: '<S30>/Product2'
   *  Product: '<S30>/Product3'
   *  Product: '<S30>/Product4'
   *  Product: '<S30>/Product5'
   *  Sum: '<S30>/Add'
   */
  localDW->Strom_kompensiert_l = (((((rtu_I_im_CT + localDW->I_im_mit_e) *
    -localDW->Merge1_h + localDW->Delay1_g * localDW->Merge_oy) +
    localDW->I_re_gegen_e * localDW->im_lim_mv) + localDW->I_im_gegen_g *
    -localDW->re_lim_l) + localDW->I_re_null_k * localDW->Product_am) +
    localDW->I_im_null_n * -localDW->Strom_kompensiert_l;

  /* Gain: '<S31>/Gain6' incorporates:
   *  Gain: '<S32>/Gain6'
   *  Gain: '<S33>/Gain6'
   *  Gain: '<S34>/Gain6'
   *  Sum: '<S23>/Sum2'
   */
  localDW->Product_am = (localDW->Strom_kompensiert_l - rtu_I_S) * rtP.Kp;

  /* Product: '<S31>/Product1' incorporates:
   *  Gain: '<S31>/Gain6'
   */
  localDW->Product1_a *= localDW->Product_am;

  /* Gain: '<S31>/Gain1' incorporates:
   *  Delay: '<S31>/Delay1'
   *  Sum: '<S31>/Sum4'
   */
  localDW->Merge_oy = 2.5E-5F * rtP.K1 * (localDW->Delay1_DSTATE +
    localDW->Product1_a);

  /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->Merge1_h = 0.5F * localDW->Merge_oy +
    localDW->DiscreteTimeIntegrator_DSTATE;

  /* Sum: '<S31>/Sum5' */
  localDW->Product1_a += localDW->Merge1_h;

  /* MATLAB Function: '<S23>/MATLAB Function' */
  MATLABFunction(rtu_I_im, rtu_w1, &localDW->Betrieb_n);

  /* Product: '<S31>/Product' incorporates:
   *  Gain: '<S31>/Gain'
   *  Gain: '<S31>/Gain6'
   */
  localDW->re_lim_l = localDW->Product_am * -localDW->im_lim_l;

  /* Gain: '<S31>/Gain2' incorporates:
   *  Delay: '<S31>/Delay'
   *  Sum: '<S31>/Sum2'
   */
  localDW->Delay1_g = 2.5E-5F * rtP.K1 * (localDW->re_lim_l +
    localDW->Delay_DSTATE);

  /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->I_im_mit_e = 0.5F * localDW->Delay1_g +
    localDW->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S31>/Sum6' */
  localDW->I_re_gegen_e = localDW->re_lim_l + localDW->I_im_mit_e;

  /* MATLAB Function: '<S31>/MATLAB Function' incorporates:
   *  Product: '<S31>/Product6'
   */
  MATLABFunction_a(localDW->Product1_a, rtu_U_ZK1, localDW->Betrieb_n,
                   localDW->I_re_gegen_e, &localDW->re_lim_l,
                   &localDW->im_lim_mv);

  /* Product: '<S31>/Product3' */
  localDW->Product3_h = localDW->re_lim_i * localDW->re_lim_l;

  /* Product: '<S32>/Product1' */
  localDW->Delay1_c *= localDW->Product_am;

  /* Delay: '<S32>/Delay1' */
  localDW->im_lim_l = localDW->Delay1_DSTATE_m;

  /* Gain: '<S32>/Gain1' incorporates:
   *  Delay: '<S32>/Delay1'
   *  Sum: '<S32>/Sum4'
   */
  localDW->I_im_gegen_g = 2.5E-5F * rtP.K2 * (localDW->Delay1_DSTATE_m +
    localDW->Delay1_c);

  /* DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->I_re_null_k = 0.5F * localDW->I_im_gegen_g +
    localDW->DiscreteTimeIntegrator_DSTATE_d;

  /* Sum: '<S32>/Sum5' */
  localDW->Delay1_c += localDW->I_re_null_k;

  /* Product: '<S32>/Product' incorporates:
   *  Gain: '<S32>/Gain'
   */
  localDW->re_lim_i = localDW->Product_am * -localDW->im_lim_k;

  /* Gain: '<S32>/Gain2' incorporates:
   *  Delay: '<S32>/Delay'
   *  Sum: '<S32>/Sum2'
   */
  localDW->I_im_null_n = 2.5E-5F * rtP.K2 * (localDW->re_lim_i +
    localDW->Delay_DSTATE_a);

  /* DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_f = 0.5F * localDW->I_im_null_n +
    localDW->DiscreteTimeIntegrator1_DSTAT_m;

  /* Sum: '<S32>/Sum6' */
  localDW->U_im_pl = localDW->re_lim_i + localDW->DiscreteTimeIntegrator1_f;

  /* MATLAB Function: '<S32>/MATLAB Function' incorporates:
   *  Constant: '<S32>/Constant2'
   *  Product: '<S32>/Product6'
   */
  MATLABFunction_a(localDW->Delay1_c, 0.05F * rtu_U_ZK1, localDW->Betrieb_n,
                   localDW->U_im_pl, &localDW->re_lim_i, &localDW->im_lim_l);

  /* Product: '<S33>/Product1' */
  localDW->re_lim_b *= localDW->Product_am;

  /* Gain: '<S33>/Gain1' incorporates:
   *  Delay: '<S33>/Delay1'
   *  Sum: '<S33>/Sum4'
   */
  localDW->Gain1_n = 2.5E-5F * rtP.K4 * (localDW->Delay1_DSTATE_g +
    localDW->re_lim_b);

  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_j = 0.5F * localDW->Gain1_n +
    localDW->DiscreteTimeIntegrator_DSTATE_i;

  /* Sum: '<S33>/Sum5' */
  localDW->U_re_j = localDW->DiscreteTimeIntegrator_j + localDW->re_lim_b;

  /* Product: '<S33>/Product' incorporates:
   *  Gain: '<S33>/Gain'
   */
  localDW->im_lim_k = localDW->Product_am * -localDW->Delay1_m;

  /* Gain: '<S33>/Gain2' incorporates:
   *  Delay: '<S33>/Delay'
   *  Sum: '<S33>/Sum2'
   */
  localDW->Delay1_m = 2.5E-5F * rtP.K4 * (localDW->im_lim_k +
    localDW->Delay_DSTATE_b);

  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_e = 0.5F * localDW->Delay1_m +
    localDW->DiscreteTimeIntegrator1_DSTAT_k;

  /* Sum: '<S33>/Sum6' */
  localDW->U_im_pt = localDW->im_lim_k + localDW->DiscreteTimeIntegrator1_e;

  /* MATLAB Function: '<S33>/MATLAB Function' incorporates:
   *  Constant: '<S33>/Constant2'
   *  Product: '<S33>/Product6'
   */
  MATLABFunction_a(localDW->U_re_j, 0.02F * rtu_U_ZK1, localDW->Betrieb_n,
                   localDW->U_im_pt, &localDW->re_lim_b, &localDW->im_lim_k);

  /* Product: '<S34>/Product1' */
  localDW->im_lim_o *= localDW->Product_am;

  /* Gain: '<S34>/Gain1' incorporates:
   *  Delay: '<S34>/Delay1'
   *  Sum: '<S34>/Sum4'
   */
  localDW->Gain1_a = 2.5E-5F * rtP.K6 * (localDW->Delay1_DSTATE_i +
    localDW->im_lim_o);

  /* DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_h = 0.5F * localDW->Gain1_a +
    localDW->DiscreteTimeIntegrator_DSTAT_if;

  /* Sum: '<S34>/Sum5' */
  localDW->U_re_b = localDW->DiscreteTimeIntegrator_h + localDW->im_lim_o;

  /* Product: '<S34>/Product' incorporates:
   *  Gain: '<S34>/Gain'
   */
  localDW->Product_am *= -localDW->re_lim_g;

  /* Delay: '<S34>/Delay' */
  localDW->re_lim_g = localDW->Delay_DSTATE_h;

  /* Gain: '<S34>/Gain2' incorporates:
   *  Delay: '<S34>/Delay'
   *  Sum: '<S34>/Sum2'
   */
  localDW->Gain2_m = 2.5E-5F * rtP.K6 * (localDW->Product_am +
    localDW->Delay_DSTATE_h);

  /* DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_h = 0.5F * localDW->Gain2_m +
    localDW->DiscreteTimeIntegrator1_DSTAT_a;

  /* Sum: '<S34>/Sum6' */
  localDW->Product_am += localDW->DiscreteTimeIntegrator1_h;

  /* MATLAB Function: '<S34>/MATLAB Function' incorporates:
   *  Constant: '<S34>/Constant2'
   *  Product: '<S34>/Product6'
   */
  MATLABFunction_a(localDW->U_re_b, 0.01F * rtu_U_ZK1, localDW->Betrieb_n,
                   localDW->Product_am, &localDW->re_lim_g, &localDW->im_lim_o);

  /* Sum: '<S23>/Add' incorporates:
   *  Constant: '<S23>/Constant1'
   *  Gain: '<S31>/Gain3'
   *  Gain: '<S32>/Gain3'
   *  Gain: '<S33>/Gain3'
   *  Gain: '<S34>/Gain3'
   *  Product: '<S23>/Divide'
   *  Product: '<S31>/Product2'
   *  Product: '<S32>/Product2'
   *  Product: '<S32>/Product3'
   *  Product: '<S33>/Product2'
   *  Product: '<S33>/Product3'
   *  Product: '<S34>/Product2'
   *  Product: '<S34>/Product3'
   *  Sum: '<S23>/Add1'
   *  Sum: '<S31>/Sum'
   *  Sum: '<S32>/Sum'
   *  Sum: '<S33>/Sum'
   *  Sum: '<S34>/Sum'
   */
  *rty_a = ((((localDW->im_lim_mv * -localDW->Add1_l + localDW->Product3_h) +
              (localDW->Merge_gt * localDW->re_lim_i + localDW->im_lim_l *
               -localDW->Sum_j)) + (localDW->Merge_ac * localDW->re_lim_b +
              localDW->im_lim_k * -localDW->Sum_o)) + (localDW->theta_e *
             localDW->re_lim_g + localDW->im_lim_o * -localDW->Sum_d)) /
    rtu_U_ZK1 + 0.5F;

  /* SignalConversion generated from: '<S23>/I_ref1' */
  *rty_I_ref1 = localDW->Strom_kompensiert_l;

  /* Update for Delay: '<S31>/Delay1' incorporates:
   *  Sum: '<S31>/Sum3'
   */
  localDW->Delay1_DSTATE = localDW->re_lim_l - localDW->Product1_a;

  /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.5F * localDW->Merge_oy +
    localDW->Merge1_h;

  /* Update for Delay: '<S31>/Delay' incorporates:
   *  Sum: '<S31>/Sum1'
   */
  localDW->Delay_DSTATE = localDW->im_lim_mv - localDW->I_re_gegen_e;

  /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = 0.5F * localDW->Delay1_g +
    localDW->I_im_mit_e;

  /* Update for Delay: '<S32>/Delay1' incorporates:
   *  Sum: '<S32>/Sum3'
   */
  localDW->Delay1_DSTATE_m = localDW->re_lim_i - localDW->Delay1_c;

  /* Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_d = 0.5F * localDW->I_im_gegen_g +
    localDW->I_re_null_k;

  /* Update for Delay: '<S32>/Delay' incorporates:
   *  Sum: '<S32>/Sum1'
   */
  localDW->Delay_DSTATE_a = localDW->im_lim_l - localDW->U_im_pl;

  /* Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_m = 0.5F * localDW->I_im_null_n +
    localDW->DiscreteTimeIntegrator1_f;

  /* Update for Delay: '<S33>/Delay1' incorporates:
   *  Sum: '<S33>/Sum3'
   */
  localDW->Delay1_DSTATE_g = localDW->re_lim_b - localDW->U_re_j;

  /* Update for DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_i = 0.5F * localDW->Gain1_n +
    localDW->DiscreteTimeIntegrator_j;

  /* Update for Delay: '<S33>/Delay' incorporates:
   *  Sum: '<S33>/Sum1'
   */
  localDW->Delay_DSTATE_b = localDW->im_lim_k - localDW->U_im_pt;

  /* Update for DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_k = 0.5F * localDW->Delay1_m +
    localDW->DiscreteTimeIntegrator1_e;

  /* Update for Delay: '<S34>/Delay1' incorporates:
   *  Sum: '<S34>/Sum3'
   */
  localDW->Delay1_DSTATE_i = localDW->re_lim_g - localDW->U_re_b;

  /* Update for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_if = 0.5F * localDW->Gain1_a +
    localDW->DiscreteTimeIntegrator_h;

  /* Update for Delay: '<S34>/Delay' incorporates:
   *  Sum: '<S34>/Sum1'
   */
  localDW->Delay_DSTATE_h = localDW->im_lim_o - localDW->Product_am;

  /* Update for DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_a = 0.5F * localDW->Gain2_m +
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

/*
 * Output and update for action system:
 *    '<S361>/sin_lookup_table'
 *    '<S362>/sin_lookup_table'
 *    '<S363>/sin_lookup_table'
 *    '<S364>/sin_lookup_table'
 */
static void sin_lookup_table(real32_T rtu_theta_el, real32_T *rty_sin2piu)
{
  uint64_T frac;
  uint32_T bpIdx;
  int16_T rtb_SignCorrected;
  uint16_T rtb_CastU16En16;
  boolean_T rtb_LTEp50;

  /* DataTypeConversion: '<S369>/CastU16En16' incorporates:
   *  Constant: '<S366>/Constant'
   *  Gain: '<S366>/Gain4'
   *  Math: '<S366>/Mod'
   */
  rtb_CastU16En16 = (uint16_T)(0.159154937F * rt_modf(rtu_theta_el, 6.28318548F)
    * 65536.0F);

  /* RelationalOperator: '<S369>/LTEp50' incorporates:
   *  DataTypeConversion: '<S369>/CastU16En16'
   */
  rtb_LTEp50 = (rtb_CastU16En16 <= 32768);

  /* Switch: '<S369>/QuadHandle1' incorporates:
   *  Constant: '<S369>/Point50'
   *  DataTypeConversion: '<S369>/CastU16En16'
   *  Sum: '<S369>/Amp50'
   */
  if (!rtb_LTEp50) {
    rtb_CastU16En16 = (uint16_T)(rtb_CastU16En16 - 32768);
  }

  /* End of Switch: '<S369>/QuadHandle1' */

  /* Switch: '<S369>/QuadHandle2' incorporates:
   *  Constant: '<S369>/Point50'
   *  RelationalOperator: '<S369>/LTEp25'
   *  Sum: '<S369>/p50mA'
   *  Switch: '<S369>/QuadHandle1'
   */
  if (rtb_CastU16En16 > 16384) {
    rtb_CastU16En16 = (uint16_T)(32768 - rtb_CastU16En16);
  }

  /* End of Switch: '<S369>/QuadHandle2' */

  /* Lookup_n-D: '<S368>/Look-Up Table' incorporates:
   *  Switch: '<S369>/QuadHandle2'
   */
  bpIdx = plook_u32u16u64n48_even8c_gf(rtb_CastU16En16, 0U, 64U, &frac);

  /* Switch: '<S369>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S368>/Look-Up Table'
   *  UnaryMinus: '<S369>/Negate'
   */
  if (rtb_LTEp50) {
    rtb_SignCorrected = intrp1d_s16s32s32u32u64n48l_f(bpIdx, frac,
      rtConstP.pooled16);
  } else {
    rtb_SignCorrected = (int16_T)-intrp1d_s16s32s32u32u64n48l_f(bpIdx, frac,
      rtConstP.pooled16);
  }

  /* End of Switch: '<S369>/SignCorrected' */

  /* DataTypeConversion: '<S366>/Data Type Conversion' incorporates:
   *  Switch: '<S369>/SignCorrected'
   */
  *rty_sin2piu = (real32_T)rtb_SignCorrected * 6.10351562E-5F;
}

/*
 * Output and update for action system:
 *    '<S361>/Subsystem'
 *    '<S362>/Subsystem'
 *    '<S363>/Subsystem'
 *    '<S364>/Subsystem'
 */
static void Subsystem_d(real32_T rtu_theta_el, real32_T *rty_sintheta_el)
{
  /* DataTypeConversion: '<S365>/Data Type Conversion' incorporates:
   *  Trigonometry: '<S365>/Sin'
   */
  *rty_sintheta_el = sinf(rtu_theta_el);
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
                   -rtDW->b) * (30.0F / (rtP.p * 3.14159274F)) / (2.0F * rtDW->a);

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
       *  RelationalOperator: '<S15>/LowerRelop1'
       */
      if (rtDW->y > rtDW->c) {
        rtDW->Switch2 = rtDW->c;
      } else {
        /* Gain: '<S7>/Gain2' */
        rtDW->c = -rtDW->c;

        /* Switch: '<S15>/Switch' incorporates:
         *  RelationalOperator: '<S15>/UpperRelop'
         */
        if (rtDW->y < rtDW->c) {
          rtDW->Switch2 = rtDW->c;
        } else {
          rtDW->Switch2 = rtDW->y;
        }

        /* End of Switch: '<S15>/Switch' */
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

    /* SwitchCase: '<S11>/Switch Case' incorporates:
     *  Inport: '<Root>/fl_enable_compensation_cogging_torque'
     */
    if (rtU->fl_enable_compensation_cogging_ == 1) {
      /* Outputs for IfAction SubSystem: '<S11>/Rastmomentkompensation' incorporates:
       *  ActionPort: '<S359>/Action Port'
       */
      /* SwitchCase: '<S361>/Switch Case' incorporates:
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/fl_lookup_table'
       *  Inport: '<Root>/ordnung_a'
       *  Inport: '<Root>/ordnung_b'
       *  Inport: '<Root>/ordnung_c'
       *  Inport: '<Root>/ordnung_d'
       *  Inport: '<Root>/phase_a'
       *  Inport: '<Root>/phase_b'
       *  Inport: '<Root>/phase_c'
       *  Inport: '<Root>/phase_d'
       *  Product: '<S359>/Product10'
       *  Product: '<S359>/Product11'
       *  Product: '<S359>/Product8'
       *  Product: '<S359>/Product9'
       *  Sum: '<S359>/Add6'
       *  Sum: '<S359>/Add7'
       *  Sum: '<S359>/Add8'
       *  Sum: '<S359>/Add9'
       *  SwitchCase: '<S362>/Switch Case'
       *  SwitchCase: '<S363>/Switch Case'
       *  SwitchCase: '<S364>/Switch Case'
       */
      if (rtU->fl_lookup_table == 1) {
        /* Outputs for IfAction SubSystem: '<S361>/sin_lookup_table' incorporates:
         *  ActionPort: '<S366>/Action Port'
         */
        sin_lookup_table(rtU->ordnung_a * rtU->Act_theta_u_el + rtU->phase_a,
                         &rtDW->c);

        /* End of Outputs for SubSystem: '<S361>/sin_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S362>/sin_lookup_table' incorporates:
         *  ActionPort: '<S371>/Action Port'
         */
        sin_lookup_table(rtU->ordnung_b * rtU->Act_theta_u_el + rtU->phase_b,
                         &rtDW->a);

        /* End of Outputs for SubSystem: '<S362>/sin_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S363>/sin_lookup_table' incorporates:
         *  ActionPort: '<S376>/Action Port'
         */
        sin_lookup_table(rtU->ordnung_c * rtU->Act_theta_u_el + rtU->phase_c,
                         &rtDW->b);

        /* End of Outputs for SubSystem: '<S363>/sin_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S364>/sin_lookup_table' incorporates:
         *  ActionPort: '<S381>/Action Port'
         */
        sin_lookup_table(rtU->ordnung_d * rtU->Act_theta_u_el + rtU->phase_d,
                         &rtDW->Gain1);

        /* End of Outputs for SubSystem: '<S364>/sin_lookup_table' */
      } else {
        /* Outputs for IfAction SubSystem: '<S361>/Subsystem' incorporates:
         *  ActionPort: '<S365>/Action Port'
         */
        Subsystem_d(rtU->ordnung_a * rtU->Act_theta_u_el + rtU->phase_a,
                    &rtDW->c);

        /* End of Outputs for SubSystem: '<S361>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S362>/Subsystem' incorporates:
         *  ActionPort: '<S370>/Action Port'
         */
        Subsystem_d(rtU->ordnung_b * rtU->Act_theta_u_el + rtU->phase_b,
                    &rtDW->a);

        /* End of Outputs for SubSystem: '<S362>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S363>/Subsystem' incorporates:
         *  ActionPort: '<S375>/Action Port'
         */
        Subsystem_d(rtU->ordnung_c * rtU->Act_theta_u_el + rtU->phase_c,
                    &rtDW->b);

        /* End of Outputs for SubSystem: '<S363>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S364>/Subsystem' incorporates:
         *  ActionPort: '<S380>/Action Port'
         */
        Subsystem_d(rtU->ordnung_d * rtU->Act_theta_u_el + rtU->phase_d,
                    &rtDW->Gain1);

        /* End of Outputs for SubSystem: '<S364>/Subsystem' */
      }

      /* End of SwitchCase: '<S361>/Switch Case' */

      /* Sum: '<S359>/Add5' incorporates:
       *  Inport: '<Root>/amplitude_a'
       *  Inport: '<Root>/amplitude_b'
       *  Inport: '<Root>/amplitude_c'
       *  Inport: '<Root>/amplitude_d'
       *  Product: '<S359>/Product4'
       *  Product: '<S359>/Product5'
       *  Product: '<S359>/Product6'
       *  Product: '<S359>/Product7'
       */
      rtDW->c = ((rtU->amplitude_a * rtDW->c + rtU->amplitude_b * rtDW->a) +
                 rtU->amplitude_c * rtDW->b) + rtU->amplitude_d * rtDW->Gain1;

      /* End of Outputs for SubSystem: '<S11>/Rastmomentkompensation' */
    } else {
      /* Outputs for IfAction SubSystem: '<S11>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S360>/Action Port'
       */
      /* SignalConversion generated from: '<S360>/In1' incorporates:
       *  Constant: '<S11>/Constant3'
       */
      rtDW->c = 0.0F;

      /* End of Outputs for SubSystem: '<S11>/Switch Case Action Subsystem' */
    }

    /* End of SwitchCase: '<S11>/Switch Case' */

    /* SwitchCase: '<S8>/Switch Case2' incorporates:
     *  Inport: '<Root>/fl_compensat_CT_current'
     */
    if (rtU->fl_compensat_CT_current == 1) {
      /* Outputs for IfAction SubSystem: '<S8>/Switch Case Action Subsystem1' incorporates:
       *  ActionPort: '<S19>/Action Port'
       */
      /* Merge: '<S8>/Merge1' incorporates:
       *  SignalConversion generated from: '<S19>/In1'
       */
      rtDW->Merge1 = rtDW->c;

      /* End of Outputs for SubSystem: '<S8>/Switch Case Action Subsystem1' */
    } else {
      /* Outputs for IfAction SubSystem: '<S8>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      /* Merge: '<S8>/Merge' incorporates:
       *  SignalConversion generated from: '<S18>/i_CT_out'
       */
      rtDW->Merge = rtDW->c;

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
    rtDW->Add = rtDW->I_im + rtDW->Merge1;

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
       *  Inport: '<Root>/fl_lookup_table'
       */
      Strangstromregler_asymetrisch(rtDW->I_re, rtDW->Add, rtU->Act_Iu,
        rtU->Act_w_el, rtDW->DiscreteTimeIntegrator,
        rtU->fl_enable_compensation_current, rtU->Act_theta_u_el, rtDW->c,
        rtDW->Merge, rtU->Psi_PM_U, rtU->Psi_PM_V, rtU->Psi_PM_W,
        rtU->fl_lookup_table, &rtY->a_U, &rtDW->Merge3, rtP.Offset_U_ideal,
        rtP.Offset_U_ideal, -0.0F, &rtDW->Strangstromregler_asymetrisch_h);

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
       *  Inport: '<Root>/fl_lookup_table'
       */
      Strangstromregler_asymetrisch(rtDW->I_re, rtDW->Add, rtU->Act_Iv,
        rtU->Act_w_el, rtDW->DiscreteTimeIntegrator,
        rtU->fl_enable_compensation_current, rtU->Act_theta_u_el, rtDW->c,
        rtDW->Merge, rtU->Psi_PM_U, rtU->Psi_PM_V, rtU->Psi_PM_W,
        rtU->fl_lookup_table, &rtY->a_V, &rtDW->Merge4, rtP.Offset_V_ideal,
        rtP.Offset_V_ideal, 2.09439516F, &rtDW->Strangstromregler_asymetrisch1);

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
         *  Delay: '<S251>/Delay'
         *  Delay: '<S251>/Delay1'
         *  Delay: '<S252>/Delay'
         *  Delay: '<S252>/Delay1'
         *  Delay: '<S253>/Delay'
         *  Delay: '<S253>/Delay1'
         *  Delay: '<S254>/Delay'
         *  Delay: '<S254>/Delay1'
         *  DiscreteIntegrator: '<S251>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S251>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S252>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S252>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S253>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S253>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S254>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S254>/Discrete-Time Integrator1'
         */
        rtDW->Delay1_DSTATE = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;
        rtDW->Delay_DSTATE_l = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;
        rtDW->Delay1_DSTATE_o = 0.0F;
        rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.0F;
        rtDW->Delay_DSTATE_nv = 0.0F;
        rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.0F;
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
      rtDW->Delay1 = rtDW->c + rtP.Offset_W_ideal;

      /* SwitchCase: '<S285>/Switch Case' incorporates:
       *  Inport: '<Root>/fl_lookup_table'
       *  Product: '<S251>/Product4'
       */
      if (rtU->fl_lookup_table == 1) {
        /* Outputs for IfAction SubSystem: '<S285>/cos_lookup_table' incorporates:
         *  ActionPort: '<S295>/Action Port'
         */
        cos_lookup_table(rtDW->Delay1, &rtDW->c, &rtDW->a);

        /* End of Outputs for SubSystem: '<S285>/cos_lookup_table' */
      } else {
        /* Outputs for IfAction SubSystem: '<S285>/Subsystem' incorporates:
         *  ActionPort: '<S294>/Action Port'
         */
        Subsystem(rtDW->Delay1, &rtDW->c, &rtDW->a);

        /* End of Outputs for SubSystem: '<S285>/Subsystem' */
      }

      /* End of SwitchCase: '<S285>/Switch Case' */

      /* Sum: '<S25>/Sum' incorporates:
       *  Constant: '<S25>/Constant'
       *  Inport: '<Root>/Act_theta_u_el'
       */
      rtDW->theta_m = rtU->Act_theta_u_el + rtP.Offset_W_ideal;

      /* SwitchCase: '<S284>/Switch Case' incorporates:
       *  Constant: '<S252>/Constant1'
       *  Constant: '<S253>/Constant1'
       *  Constant: '<S254>/Constant1'
       *  Constant: '<S25>/Constant2'
       *  Constant: '<S25>/Constant3'
       *  Inport: '<Root>/fl_lookup_table'
       *  Product: '<S251>/Product5'
       *  Product: '<S252>/Product4'
       *  Product: '<S252>/Product5'
       *  Product: '<S253>/Product4'
       *  Product: '<S253>/Product5'
       *  Product: '<S254>/Product4'
       *  Product: '<S254>/Product5'
       *  Sum: '<S25>/Add2'
       *  Sum: '<S25>/Add3'
       *  SwitchCase: '<S256>/Switch Case'
       *  SwitchCase: '<S257>/Switch Case'
       *  SwitchCase: '<S258>/Switch Case'
       *  SwitchCase: '<S303>/Switch Case'
       *  SwitchCase: '<S304>/Switch Case'
       *  SwitchCase: '<S322>/Switch Case'
       *  SwitchCase: '<S323>/Switch Case'
       *  SwitchCase: '<S341>/Switch Case'
       *  SwitchCase: '<S342>/Switch Case'
       */
      if (rtU->fl_lookup_table == 1) {
        /* Outputs for IfAction SubSystem: '<S284>/cos_lookup_table' incorporates:
         *  ActionPort: '<S287>/Action Port'
         */
        cos_lookup_table(rtDW->theta_m, &rtDW->Product1_d, &rtDW->b);

        /* End of Outputs for SubSystem: '<S284>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S256>/cos_lookup_table' incorporates:
         *  ActionPort: '<S260>/Action Port'
         */
        cos_lookup_table(rtDW->theta_m, &rtDW->Merge_a, &rtDW->Merge1_m);

        /* End of Outputs for SubSystem: '<S256>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S257>/cos_lookup_table' incorporates:
         *  ActionPort: '<S268>/Action Port'
         */
        cos_lookup_table(rtDW->theta_m + rtP.Offset_W_ideal, &rtDW->Gain1,
                         &rtDW->y_i);

        /* End of Outputs for SubSystem: '<S257>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S258>/cos_lookup_table' incorporates:
         *  ActionPort: '<S276>/Action Port'
         */
        cos_lookup_table(rtDW->theta_m + 4.18879032F, &rtDW->Product_d, &rtDW->y);

        /* End of Outputs for SubSystem: '<S258>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S303>/cos_lookup_table' incorporates:
         *  ActionPort: '<S306>/Action Port'
         */
        cos_lookup_table(rtDW->theta_m * 2.0F, &rtDW->Delay1_a, &rtDW->Switch2);

        /* End of Outputs for SubSystem: '<S303>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S304>/cos_lookup_table' incorporates:
         *  ActionPort: '<S314>/Action Port'
         */
        cos_lookup_table(rtDW->Delay1 * 2.0F, &rtDW->Merge_g, &rtDW->Sum_a);

        /* End of Outputs for SubSystem: '<S304>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S322>/cos_lookup_table' incorporates:
         *  ActionPort: '<S325>/Action Port'
         */
        cos_lookup_table(rtDW->theta_m * 4.0F, &rtDW->re_lim, &rtDW->Delay1_k);

        /* End of Outputs for SubSystem: '<S322>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S323>/cos_lookup_table' incorporates:
         *  ActionPort: '<S333>/Action Port'
         */
        cos_lookup_table(rtDW->Delay1 * 4.0F, &rtDW->Merge_dn, &rtDW->Sum_cr);

        /* End of Outputs for SubSystem: '<S323>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S341>/cos_lookup_table' incorporates:
         *  ActionPort: '<S344>/Action Port'
         */
        cos_lookup_table(rtDW->theta_m * 6.0F, &rtDW->im_lim_f, &rtDW->re_lim_e);

        /* End of Outputs for SubSystem: '<S341>/cos_lookup_table' */

        /* Outputs for IfAction SubSystem: '<S342>/cos_lookup_table' incorporates:
         *  ActionPort: '<S352>/Action Port'
         */
        cos_lookup_table(rtDW->Delay1 * 6.0F, &rtDW->theta_m, &rtDW->Sum_an);

        /* End of Outputs for SubSystem: '<S342>/cos_lookup_table' */
      } else {
        /* Outputs for IfAction SubSystem: '<S284>/Subsystem' incorporates:
         *  ActionPort: '<S286>/Action Port'
         */
        Subsystem(rtDW->theta_m, &rtDW->Product1_d, &rtDW->b);

        /* End of Outputs for SubSystem: '<S284>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S256>/Subsystem' incorporates:
         *  ActionPort: '<S259>/Action Port'
         */
        Subsystem(rtDW->theta_m, &rtDW->Merge_a, &rtDW->Merge1_m);

        /* End of Outputs for SubSystem: '<S256>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S257>/Subsystem' incorporates:
         *  ActionPort: '<S267>/Action Port'
         */
        Subsystem(rtDW->theta_m + rtP.Offset_W_ideal, &rtDW->Gain1, &rtDW->y_i);

        /* End of Outputs for SubSystem: '<S257>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S258>/Subsystem' incorporates:
         *  ActionPort: '<S275>/Action Port'
         */
        Subsystem(rtDW->theta_m + 4.18879032F, &rtDW->Product_d, &rtDW->y);

        /* End of Outputs for SubSystem: '<S258>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S303>/Subsystem' incorporates:
         *  ActionPort: '<S305>/Action Port'
         */
        Subsystem(rtDW->theta_m * 2.0F, &rtDW->Delay1_a, &rtDW->Switch2);

        /* End of Outputs for SubSystem: '<S303>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S304>/Subsystem' incorporates:
         *  ActionPort: '<S313>/Action Port'
         */
        Subsystem(rtDW->Delay1 * 2.0F, &rtDW->Merge_g, &rtDW->Sum_a);

        /* End of Outputs for SubSystem: '<S304>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S322>/Subsystem' incorporates:
         *  ActionPort: '<S324>/Action Port'
         */
        Subsystem(rtDW->theta_m * 4.0F, &rtDW->re_lim, &rtDW->Delay1_k);

        /* End of Outputs for SubSystem: '<S322>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S323>/Subsystem' incorporates:
         *  ActionPort: '<S332>/Action Port'
         */
        Subsystem(rtDW->Delay1 * 4.0F, &rtDW->Merge_dn, &rtDW->Sum_cr);

        /* End of Outputs for SubSystem: '<S323>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S341>/Subsystem' incorporates:
         *  ActionPort: '<S343>/Action Port'
         */
        Subsystem(rtDW->theta_m * 6.0F, &rtDW->im_lim_f, &rtDW->re_lim_e);

        /* End of Outputs for SubSystem: '<S341>/Subsystem' */

        /* Outputs for IfAction SubSystem: '<S342>/Subsystem' incorporates:
         *  ActionPort: '<S351>/Action Port'
         */
        Subsystem(rtDW->Delay1 * 6.0F, &rtDW->theta_m, &rtDW->Sum_an);

        /* End of Outputs for SubSystem: '<S342>/Subsystem' */
      }

      /* End of SwitchCase: '<S284>/Switch Case' */

      /* MATLAB Function: '<S250>/MATLAB Function' incorporates:
       *  Inport: '<Root>/Act_w_el'
       *  Inport: '<Root>/Psi_PM_U'
       *  Inport: '<Root>/Psi_PM_V'
       *  Inport: '<Root>/Psi_PM_W'
       *  Inport: '<Root>/fl_enable_compensation_current'
       */
      MATLABFunction_i(rtU->Psi_PM_U, rtU->Psi_PM_V, rtU->Psi_PM_W, rtDW->I_re,
                       rtDW->Add, rtU->Act_w_el,
                       rtU->fl_enable_compensation_current, &rtDW->Delay1,
                       &rtDW->I_im_mit, &rtDW->I_re_gegen, &rtDW->I_im_gegen,
                       &rtDW->I_re_null, &rtDW->I_im_null,
                       &rtDW->sf_MATLABFunction_e);

      /* Sum: '<S250>/Strom_kompensiert' incorporates:
       *  Gain: '<S250>/Gain'
       *  Gain: '<S250>/Gain1'
       *  Gain: '<S250>/Gain2'
       *  Product: '<S250>/Product'
       *  Product: '<S250>/Product1'
       *  Product: '<S250>/Product2'
       *  Product: '<S250>/Product3'
       *  Product: '<S250>/Product4'
       *  Product: '<S250>/Product5'
       *  Sum: '<S250>/Add'
       */
      rtDW->y = (((((rtDW->Merge + rtDW->I_im_mit) * -rtDW->Merge1_m +
                    rtDW->Delay1 * rtDW->Merge_a) + rtDW->I_re_gegen *
                   rtDW->Gain1) + rtDW->I_im_gegen * -rtDW->y_i) +
                 rtDW->I_re_null * rtDW->Product_d) + rtDW->I_im_null * -rtDW->y;

      /* Gain: '<S251>/Gain6' incorporates:
       *  Gain: '<S252>/Gain6'
       *  Gain: '<S253>/Gain6'
       *  Gain: '<S254>/Gain6'
       *  Inport: '<Root>/Act_Iw'
       *  Sum: '<S25>/Sum2'
       */
      rtDW->Product_d = (rtDW->y - rtU->Act_Iw) * rtP.Kp;

      /* Product: '<S251>/Product1' incorporates:
       *  Gain: '<S251>/Gain6'
       */
      rtDW->Product1_d *= rtDW->Product_d;

      /* Gain: '<S251>/Gain1' incorporates:
       *  Delay: '<S251>/Delay1'
       *  Sum: '<S251>/Sum4'
       */
      rtDW->Merge_a = 2.5E-5F * rtP.K1 * (rtDW->Delay1_DSTATE + rtDW->Product1_d);

      /* DiscreteIntegrator: '<S251>/Discrete-Time Integrator' */
      rtDW->Merge1_m = 0.5F * rtDW->Merge_a +
        rtDW->DiscreteTimeIntegrator_DSTATE_o;

      /* Sum: '<S251>/Sum5' */
      rtDW->Product1_d += rtDW->Merge1_m;

      /* MATLAB Function: '<S25>/MATLAB Function' incorporates:
       *  Inport: '<Root>/Act_w_el'
       */
      MATLABFunction(rtDW->Add, rtU->Act_w_el, &rtDW->Betrieb);

      /* Product: '<S251>/Product' incorporates:
       *  Gain: '<S251>/Gain'
       *  Gain: '<S251>/Gain6'
       */
      rtDW->y_i = rtDW->Product_d * -rtDW->b;

      /* Gain: '<S251>/Gain2' incorporates:
       *  Delay: '<S251>/Delay'
       *  Sum: '<S251>/Sum2'
       */
      rtDW->Add = 2.5E-5F * rtP.K1 * (rtDW->y_i + rtDW->Delay_DSTATE_l);

      /* DiscreteIntegrator: '<S251>/Discrete-Time Integrator1' */
      rtDW->Delay1 = 0.5F * rtDW->Add + rtDW->DiscreteTimeIntegrator1_DSTATE;

      /* Sum: '<S251>/Sum6' */
      rtDW->I_im_mit = rtDW->y_i + rtDW->Delay1;

      /* MATLAB Function: '<S251>/MATLAB Function' incorporates:
       *  Constant: '<S251>/Constant2'
       *  Product: '<S251>/Product6'
       */
      MATLABFunction_a(rtDW->Product1_d, 0.46F * rtDW->DiscreteTimeIntegrator,
                       rtDW->Betrieb, rtDW->I_im_mit, &rtDW->y_i, &rtDW->Gain1);

      /* Product: '<S251>/Product3' */
      rtDW->I_re_gegen = rtDW->c * rtDW->y_i;

      /* Product: '<S252>/Product1' */
      rtDW->Delay1_a *= rtDW->Product_d;

      /* Delay: '<S252>/Delay1' */
      rtDW->b = rtDW->Delay1_DSTATE_o;

      /* Gain: '<S252>/Gain1' incorporates:
       *  Delay: '<S252>/Delay1'
       *  Sum: '<S252>/Sum4'
       */
      rtDW->I_im_gegen = 2.5E-5F * rtP.K2 * (rtDW->Delay1_DSTATE_o +
        rtDW->Delay1_a);

      /* DiscreteIntegrator: '<S252>/Discrete-Time Integrator' */
      rtDW->I_re_null = 0.5F * rtDW->I_im_gegen +
        rtDW->DiscreteTimeIntegrator_DSTATE_m;

      /* Sum: '<S252>/Sum5' */
      rtDW->Delay1_a += rtDW->I_re_null;

      /* Product: '<S252>/Product' incorporates:
       *  Gain: '<S252>/Gain'
       */
      rtDW->c = rtDW->Product_d * -rtDW->Switch2;

      /* Gain: '<S252>/Gain2' incorporates:
       *  Delay: '<S252>/Delay'
       *  Sum: '<S252>/Sum2'
       */
      rtDW->I_im_null = 2.5E-5F * rtP.K2 * (rtDW->c + rtDW->Delay_DSTATE_nv);

      /* DiscreteIntegrator: '<S252>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_e = 0.5F * rtDW->I_im_null +
        rtDW->DiscreteTimeIntegrator1_DSTAT_f;

      /* Sum: '<S252>/Sum6' */
      rtDW->U_im_k = rtDW->c + rtDW->DiscreteTimeIntegrator1_e;

      /* MATLAB Function: '<S252>/MATLAB Function' incorporates:
       *  Constant: '<S252>/Constant2'
       *  Product: '<S252>/Product6'
       */
      MATLABFunction_a(rtDW->Delay1_a, 0.05F * rtDW->DiscreteTimeIntegrator,
                       rtDW->Betrieb, rtDW->U_im_k, &rtDW->c, &rtDW->b);

      /* Product: '<S253>/Product1' */
      rtDW->re_lim *= rtDW->Product_d;

      /* Gain: '<S253>/Gain1' incorporates:
       *  Delay: '<S253>/Delay1'
       *  Sum: '<S253>/Sum4'
       */
      rtDW->Gain1_m = 2.5E-5F * rtP.K4 * (rtDW->Delay1_DSTATE_g + rtDW->re_lim);

      /* DiscreteIntegrator: '<S253>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_a = 0.5F * rtDW->Gain1_m +
        rtDW->DiscreteTimeIntegrator_DSTATE_c;

      /* Sum: '<S253>/Sum5' */
      rtDW->U_re_n = rtDW->DiscreteTimeIntegrator_a + rtDW->re_lim;

      /* Product: '<S253>/Product' incorporates:
       *  Gain: '<S253>/Gain'
       */
      rtDW->Switch2 = rtDW->Product_d * -rtDW->Delay1_k;

      /* Gain: '<S253>/Gain2' incorporates:
       *  Delay: '<S253>/Delay'
       *  Sum: '<S253>/Sum2'
       */
      rtDW->Delay1_k = 2.5E-5F * rtP.K4 * (rtDW->Switch2 + rtDW->Delay_DSTATE_a);

      /* DiscreteIntegrator: '<S253>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_a = 0.5F * rtDW->Delay1_k +
        rtDW->DiscreteTimeIntegrator1_DSTAT_o;

      /* Sum: '<S253>/Sum6' */
      rtDW->U_im_p = rtDW->Switch2 + rtDW->DiscreteTimeIntegrator1_a;

      /* MATLAB Function: '<S253>/MATLAB Function' incorporates:
       *  Constant: '<S253>/Constant2'
       *  Product: '<S253>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_n, 0.02F * rtDW->DiscreteTimeIntegrator,
                       rtDW->Betrieb, rtDW->U_im_p, &rtDW->re_lim,
                       &rtDW->Switch2);

      /* Product: '<S254>/Product1' */
      rtDW->im_lim_f *= rtDW->Product_d;

      /* Gain: '<S254>/Gain1' incorporates:
       *  Delay: '<S254>/Delay1'
       *  Sum: '<S254>/Sum4'
       */
      rtDW->Gain1_j = 2.5E-5F * rtP.K6 * (rtDW->Delay1_DSTATE_oi +
        rtDW->im_lim_f);

      /* DiscreteIntegrator: '<S254>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_n = 0.5F * rtDW->Gain1_j +
        rtDW->DiscreteTimeIntegrator_DSTATE_g;

      /* Sum: '<S254>/Sum5' */
      rtDW->U_re_d = rtDW->DiscreteTimeIntegrator_n + rtDW->im_lim_f;

      /* Product: '<S254>/Product' incorporates:
       *  Gain: '<S254>/Gain'
       */
      rtDW->Product_d *= -rtDW->re_lim_e;

      /* Delay: '<S254>/Delay' */
      rtDW->re_lim_e = rtDW->Delay_DSTATE_nm;

      /* Gain: '<S254>/Gain2' incorporates:
       *  Delay: '<S254>/Delay'
       *  Sum: '<S254>/Sum2'
       */
      rtDW->Gain2_i = 2.5E-5F * rtP.K6 * (rtDW->Product_d +
        rtDW->Delay_DSTATE_nm);

      /* DiscreteIntegrator: '<S254>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_g = 0.5F * rtDW->Gain2_i +
        rtDW->DiscreteTimeIntegrator1_DSTA_os;

      /* Sum: '<S254>/Sum6' */
      rtDW->Product_d += rtDW->DiscreteTimeIntegrator1_g;

      /* MATLAB Function: '<S254>/MATLAB Function' incorporates:
       *  Constant: '<S254>/Constant2'
       *  Product: '<S254>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_d, 0.01F * rtDW->DiscreteTimeIntegrator,
                       rtDW->Betrieb, rtDW->Product_d, &rtDW->re_lim_e,
                       &rtDW->im_lim_f);

      /* Outport: '<Root>/a_W' incorporates:
       *  Constant: '<S25>/Constant1'
       *  Gain: '<S251>/Gain3'
       *  Gain: '<S252>/Gain3'
       *  Gain: '<S253>/Gain3'
       *  Gain: '<S254>/Gain3'
       *  Product: '<S251>/Product2'
       *  Product: '<S252>/Product2'
       *  Product: '<S252>/Product3'
       *  Product: '<S253>/Product2'
       *  Product: '<S253>/Product3'
       *  Product: '<S254>/Product2'
       *  Product: '<S254>/Product3'
       *  Product: '<S25>/Divide'
       *  Sum: '<S251>/Sum'
       *  Sum: '<S252>/Sum'
       *  Sum: '<S253>/Sum'
       *  Sum: '<S254>/Sum'
       *  Sum: '<S25>/Add'
       *  Sum: '<S25>/Add1'
       */
      rtY->a_W = ((((rtDW->Gain1 * -rtDW->a + rtDW->I_re_gegen) + (rtDW->Merge_g
        * rtDW->c + rtDW->b * -rtDW->Sum_a)) + (rtDW->Merge_dn * rtDW->re_lim +
        rtDW->Switch2 * -rtDW->Sum_cr)) + (rtDW->theta_m * rtDW->re_lim_e +
        rtDW->im_lim_f * -rtDW->Sum_an)) / rtDW->DiscreteTimeIntegrator + 0.5F;

      /* Merge: '<S10>/Merge5' incorporates:
       *  SignalConversion generated from: '<S25>/I_ref1'
       */
      rtDW->Merge5 = rtDW->y;

      /* Update for Delay: '<S251>/Delay1' incorporates:
       *  Sum: '<S251>/Sum3'
       */
      rtDW->Delay1_DSTATE = rtDW->y_i - rtDW->Product1_d;

      /* Update for DiscreteIntegrator: '<S251>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.5F * rtDW->Merge_a +
        rtDW->Merge1_m;

      /* Update for Delay: '<S251>/Delay' incorporates:
       *  Sum: '<S251>/Sum1'
       */
      rtDW->Delay_DSTATE_l = rtDW->Gain1 - rtDW->I_im_mit;

      /* Update for DiscreteIntegrator: '<S251>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTATE = 0.5F * rtDW->Add + rtDW->Delay1;

      /* Update for Delay: '<S252>/Delay1' incorporates:
       *  Sum: '<S252>/Sum3'
       */
      rtDW->Delay1_DSTATE_o = rtDW->c - rtDW->Delay1_a;

      /* Update for DiscreteIntegrator: '<S252>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.5F * rtDW->I_im_gegen +
        rtDW->I_re_null;

      /* Update for Delay: '<S252>/Delay' incorporates:
       *  Sum: '<S252>/Sum1'
       */
      rtDW->Delay_DSTATE_nv = rtDW->b - rtDW->U_im_k;

      /* Update for DiscreteIntegrator: '<S252>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.5F * rtDW->I_im_null +
        rtDW->DiscreteTimeIntegrator1_e;

      /* Update for Delay: '<S253>/Delay1' incorporates:
       *  Sum: '<S253>/Sum3'
       */
      rtDW->Delay1_DSTATE_g = rtDW->re_lim - rtDW->U_re_n;

      /* Update for DiscreteIntegrator: '<S253>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.5F * rtDW->Gain1_m +
        rtDW->DiscreteTimeIntegrator_a;

      /* Update for Delay: '<S253>/Delay' incorporates:
       *  Sum: '<S253>/Sum1'
       */
      rtDW->Delay_DSTATE_a = rtDW->Switch2 - rtDW->U_im_p;

      /* Update for DiscreteIntegrator: '<S253>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.5F * rtDW->Delay1_k +
        rtDW->DiscreteTimeIntegrator1_a;

      /* Update for Delay: '<S254>/Delay1' incorporates:
       *  Sum: '<S254>/Sum3'
       */
      rtDW->Delay1_DSTATE_oi = rtDW->re_lim_e - rtDW->U_re_d;

      /* Update for DiscreteIntegrator: '<S254>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.5F * rtDW->Gain1_j +
        rtDW->DiscreteTimeIntegrator_n;

      /* Update for Delay: '<S254>/Delay' incorporates:
       *  Sum: '<S254>/Sum1'
       */
      rtDW->Delay_DSTATE_nm = rtDW->im_lim_f - rtDW->Product_d;

      /* Update for DiscreteIntegrator: '<S254>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTA_os = 0.5F * rtDW->Gain2_i +
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

  /* DiscreteIntegrator: '<S385>/Accumulator' incorporates:
   *  Delay: '<S385>/Delay'
   *  Sum: '<S385>/Sum'
   */
  rtDW->a = (rtDW->c - rtDW->Delay_DSTATE_k[0]) + rtDW->Accumulator_DSTATE;

  /* Outport: '<Root>/fault_rms_current_u' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Gain: '<S385>/Gain'
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

  /* DiscreteIntegrator: '<S386>/Accumulator' incorporates:
   *  Delay: '<S386>/Delay'
   *  Inport: '<Root>/Act_n'
   *  Sum: '<S386>/Sum'
   */
  rtDW->b = (rtU->Act_n - rtDW->Delay_DSTATE_ki[0]) + rtDW->Accumulator_DSTATE_d;

  /* Outport: '<Root>/fault_max_speed' incorporates:
   *  Constant: '<S5>/Constant3'
   *  Gain: '<S386>/Gain'
   *  RelationalOperator: '<S5>/Smaller3'
   */
  rtY->fault_max_speed = (rtP.n_max <= 0.00833333377F * rtDW->b);

  /* Math: '<S5>/Square1' incorporates:
   *  Inport: '<Root>/Act_Iv'
   */
  rtDW->Gain1 = rtU->Act_Iv * rtU->Act_Iv;

  /* DiscreteIntegrator: '<S387>/Accumulator' incorporates:
   *  Delay: '<S387>/Delay'
   *  Sum: '<S387>/Sum'
   */
  rtDW->y_i = (rtDW->Gain1 - rtDW->Delay_DSTATE_kl[0]) +
    rtDW->Accumulator_DSTATE_f;

  /* Outport: '<Root>/fault_rms_current_v' incorporates:
   *  Constant: '<S5>/Constant5'
   *  Gain: '<S387>/Gain'
   *  RelationalOperator: '<S5>/Smaller5'
   *  Sqrt: '<S5>/Square Root1'
   */
  rtY->fault_rms_current_v = (rtP.i_max_rms <= sqrtf(0.05F * rtDW->y_i));

  /* Math: '<S5>/Square2' incorporates:
   *  Inport: '<Root>/Act_Iw'
   */
  rtDW->y = rtU->Act_Iw * rtU->Act_Iw;

  /* DiscreteIntegrator: '<S388>/Accumulator' incorporates:
   *  Delay: '<S388>/Delay'
   *  Sum: '<S388>/Sum'
   */
  rtDW->Switch2 = (rtDW->y - rtDW->Delay_DSTATE_b[0]) +
    rtDW->Accumulator_DSTATE_n;

  /* Outport: '<Root>/fault_rms_current_w' incorporates:
   *  Constant: '<S5>/Constant7'
   *  Gain: '<S388>/Gain'
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

  /* Update for Delay: '<S385>/Delay' */
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 19; rtDW->idxDelay++) {
    rtDW->Delay_DSTATE_k[rtDW->idxDelay] = rtDW->Delay_DSTATE_k[rtDW->idxDelay +
      1];
  }

  rtDW->Delay_DSTATE_k[19] = rtDW->c;

  /* End of Update for Delay: '<S385>/Delay' */

  /* Update for DiscreteIntegrator: '<S385>/Accumulator' */
  rtDW->Accumulator_DSTATE = rtDW->a;

  /* Update for Delay: '<S386>/Delay' incorporates:
   *  Inport: '<Root>/Act_n'
   */
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 119; rtDW->idxDelay++) {
    rtDW->Delay_DSTATE_ki[rtDW->idxDelay] = rtDW->Delay_DSTATE_ki[rtDW->idxDelay
      + 1];
  }

  rtDW->Delay_DSTATE_ki[119] = rtU->Act_n;

  /* End of Update for Delay: '<S386>/Delay' */

  /* Update for DiscreteIntegrator: '<S386>/Accumulator' */
  rtDW->Accumulator_DSTATE_d = rtDW->b;

  /* Update for DiscreteIntegrator: '<S387>/Accumulator' */
  rtDW->Accumulator_DSTATE_f = rtDW->y_i;
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 19; rtDW->idxDelay++) {
    /* Update for Delay: '<S387>/Delay' */
    rtDW->Delay_DSTATE_kl[rtDW->idxDelay] = rtDW->Delay_DSTATE_kl[rtDW->idxDelay
      + 1];

    /* Update for Delay: '<S388>/Delay' */
    rtDW->Delay_DSTATE_b[rtDW->idxDelay] = rtDW->Delay_DSTATE_b[rtDW->idxDelay +
      1];
  }

  /* Update for Delay: '<S387>/Delay' */
  rtDW->Delay_DSTATE_kl[19] = rtDW->Gain1;

  /* Update for Delay: '<S388>/Delay' */
  rtDW->Delay_DSTATE_b[19] = rtDW->y;

  /* Update for DiscreteIntegrator: '<S388>/Accumulator' */
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
  /* InitializeConditions for Delay: '<S251>/Delay1' */
  rtDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S251>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;

  /* InitializeConditions for Delay: '<S251>/Delay' */
  rtDW->Delay_DSTATE_l = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S251>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S252>/Delay1' */
  rtDW->Delay1_DSTATE_o = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S252>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.0F;

  /* InitializeConditions for Delay: '<S252>/Delay' */
  rtDW->Delay_DSTATE_nv = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S252>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.0F;

  /* InitializeConditions for Delay: '<S253>/Delay1' */
  rtDW->Delay1_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S253>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.0F;

  /* InitializeConditions for Delay: '<S253>/Delay' */
  rtDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S253>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.0F;

  /* InitializeConditions for Delay: '<S254>/Delay1' */
  rtDW->Delay1_DSTATE_oi = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S254>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.0F;

  /* InitializeConditions for Delay: '<S254>/Delay' */
  rtDW->Delay_DSTATE_nm = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S254>/Discrete-Time Integrator1' */
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
