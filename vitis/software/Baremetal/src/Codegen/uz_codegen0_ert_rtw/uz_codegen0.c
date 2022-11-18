/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 4.5
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Fri Nov 18 14:14:24 2022
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
static uint32_T plook_u32u32u64n32_even20c_gf(uint32_T u, uint32_T bp0, uint32_T
  maxIndex, uint64_T *fraction);
static int32_T intrp1d_s32s64s64u32u64n32l_f(uint32_T bpIndex, uint64_T frac,
  const int32_T table[]);
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
static uint32_T plook_u32u32u64n32_even20c_gf(uint32_T u, uint32_T bp0, uint32_T
  maxIndex, uint64_T *fraction)
{
  uint32_T bpIndex;
  uint32_T uAdjust;

  /* Prelookup - Index and Fraction
     Index Search method: 'even'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'on'
     Rounding mode: 'floor'
   */
  uAdjust = u - bp0;
  bpIndex = uAdjust >> 20U;
  if (bpIndex < maxIndex) {
    *fraction = (uint64_T)(uAdjust & 1048575U) << 12;
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = 4294967296ULL;
  }

  return bpIndex;
}

static int32_T intrp1d_s32s64s64u32u64n32l_f(uint32_T bpIndex, uint64_T frac,
  const int32_T table[])
{
  int32_T yL_0d0;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Rounding mode: 'floor'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[bpIndex];
  return (int32_T)((((int64_T)table[bpIndex + 1U] - yL_0d0) * (int64_T)frac) >>
                   32) + yL_0d0;
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
 *    '<S121>/MATLAB Function'
 *    '<S212>/MATLAB Function'
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

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/Referenzstromerzeugung_asymetrisch/MATLAB Function': '<S39>:1' */
  /*  Up = Polradspannung, induced Voltage, back emf (als komplexen Vektor) */
  /*  i_q =  referenz q-Strom (als reeler Wert) */
  /* '<S39>:1:4' if enable == 1 */
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

    /* '<S39>:1:5' p=18; */
    /*  Polpaarzahl */
    /*     %% Matrizen für symetrische Komponenten */
    /*  */
    /* '<S39>:1:8' a=single(exp(1i*(2*pi/3))); */
    /* '<S39>:1:9' T=single([1   1   1;  a^2 a   1; a   a^2 1]); */
    /*     %% Eingangsvektoren */
    /* '<S39>:1:11' U=[Psi_PM_U; Psi_PM_V;Psi_PM_W].*omega_el; */
    /* '<S39>:1:12' I_U=single(I_im*exp(1i*(-0*pi/3))); */
    /* '<S39>:1:13' I_V=single(I_im*exp(1i*(-2*pi/3))); */
    I_V_re_tmp = rtu_I_im * -0.5F;
    I_V_im = rtu_I_im * -0.866025388F;

    /* '<S39>:1:14' I_W=single(I_im*exp(1i*(-4*pi/3))); */
    I_W_im = rtu_I_im * 0.866025388F;

    /* '<S39>:1:15' I=single([I_U;I_V;I_W]); */
    /*  Symetrische Komponenten von Spannung */
    /*  Komponenten (1. Dimensoin -> Mit.-,Gegen-,Nullkomponente; 2. Dimension -> */
    /*  Phase 1,2,3 */
    /*  */
    /* '<S39>:1:20' U_sym_komp_hilf=single((inv(T)*U)); */
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
    /* '<S39>:1:21' U_sym_komp=single(zeros(3,3)*(0+0i)); */
    /*  Mitkomponente */
    /* '<S39>:1:23' U_sym_komp(1,1)=single(U_sym_komp_hilf(1)*1); */
    /* '<S39>:1:24' U_sym_komp(1,2)=single(U_sym_komp_hilf(1)*a^2); */
    /* '<S39>:1:25' U_sym_komp(1,3)=single(U_sym_komp_hilf(1)*a); */
    /*  Gegenkomponente */
    /* '<S39>:1:27' U_sym_komp(2,1)=single(U_sym_komp_hilf(2)*1); */
    /* '<S39>:1:28' U_sym_komp(2,2)=single(U_sym_komp_hilf(2)*a); */
    rtu_Psi_PM_U_idx_0_im = localDW->U_sym_komp_hilf[1].re * -0.5F;
    U_sym_komp_idx_4_re = rtu_Psi_PM_U_idx_0_im - localDW->U_sym_komp_hilf[1].im
      * 0.866025388F;
    rtu_Psi_PM_U_idx_0_re = localDW->U_sym_komp_hilf[1].im * -0.5F;
    U_sym_komp_idx_4_im = localDW->U_sym_komp_hilf[1].re * 0.866025388F +
      rtu_Psi_PM_U_idx_0_re;

    /* '<S39>:1:29' U_sym_komp(2,3)=single(U_sym_komp_hilf(2)*a^2); */
    U_sym_komp_idx_7_re = rtu_Psi_PM_U_idx_0_im - localDW->U_sym_komp_hilf[1].im
      * -0.866025388F;
    U_sym_komp_idx_7_im = localDW->U_sym_komp_hilf[1].re * -0.866025388F +
      rtu_Psi_PM_U_idx_0_re;

    /*  Nullkomponente */
    /* '<S39>:1:31' U_sym_komp(3,1)=single(U_sym_komp_hilf(3)*1); */
    /* '<S39>:1:32' U_sym_komp(3,2)=single(U_sym_komp_hilf(3)*1); */
    /* '<S39>:1:33' U_sym_komp(3,3)=single(U_sym_komp_hilf(3)*1); */
    /*     %% Kompensation von U_g+U_0 */
    /* '<S39>:1:35' I_Gegen_U=single(-(I_U*(U_sym_komp(2,1)+U_sym_komp(3,1)))/(U_sym_komp(1,1)+U_sym_komp(2,1)+U_sym_komp(3,1))); */
    /* '<S39>:1:36' I_Gegen_V=single(-(I_V*(U_sym_komp(2,2)+U_sym_komp(3,2)))/(U_sym_komp(1,2)+U_sym_komp(2,2)+U_sym_komp(3,2))); */
    /* '<S39>:1:37' I_Gegen_W=single(-(I_W*(U_sym_komp(2,3)+U_sym_komp(3,3)))/(U_sym_komp(1,3)+U_sym_komp(2,3)+U_sym_komp(3,3))); */
    /* '<S39>:1:38' I_Mit=single(I); */
    /*  */
    /* '<S39>:1:40' I_Gegen=single([I_Gegen_U; I_Gegen_V; I_Gegen_W]); */
    /* '<S39>:1:41' I_compensation=single((I_Gegen+I_Mit)); */
    /* '<S39>:1:42' I_compensation_sym_components=single((inv(T)*I_compensation)); */
    /* .*[1 a^2 a; 1 a a^2;1 1 1])); */
    /* '<S39>:1:43' I_compensation_sym_components=single(I_compensation_sym_components.*exp(1i*(pi/2))); */
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
    /* '<S39>:1:47' I_re_mit=single(real(I_compensation_sym_components(1,1))); */
    *rty_I_re_mit = localDW->U_sym_komp_hilf[0].re;

    /* '<S39>:1:48' I_im_mit=single(imag(I_compensation_sym_components(1,1))); */
    *rty_I_im_mit = localDW->U_sym_komp_hilf[0].im;

    /* '<S39>:1:49' I_re_gegen=single(real(I_compensation_sym_components(2,1))); */
    *rty_I_re_gegen = localDW->U_sym_komp_hilf[1].re;

    /* '<S39>:1:50' I_im_gegen=single(imag(I_compensation_sym_components(2,1))); */
    *rty_I_im_gegen = localDW->U_sym_komp_hilf[1].im;

    /* '<S39>:1:51' I_re_null=single(real(I_compensation_sym_components(3,1))); */
    *rty_I_re_null = localDW->U_sym_komp_hilf[2].re;

    /* '<S39>:1:52' I_im_null=single(imag(I_compensation_sym_components(3,1))); */
    *rty_I_im_null = localDW->U_sym_komp_hilf[2].im;

    /*  */
  } else {
    /* '<S39>:1:54' else */
    /*     %% Output as single */
    /* '<S39>:1:56' I_re_mit=single(I_re); */
    *rty_I_re_mit = rtu_I_re;

    /* '<S39>:1:57' I_im_mit=single(I_im); */
    *rty_I_im_mit = rtu_I_im;

    /* '<S39>:1:58' I_re_gegen=single(0); */
    *rty_I_re_gegen = 0.0F;

    /* '<S39>:1:59' I_im_gegen=single(0); */
    *rty_I_im_gegen = 0.0F;

    /* '<S39>:1:60' I_re_null=single(0); */
    *rty_I_re_null = 0.0F;

    /* '<S39>:1:61' I_im_null=single(0); */
    *rty_I_im_null = 0.0F;
  }
}

/*
 * Output and update for atomic system:
 *    '<S31>/MATLAB Function'
 *    '<S122>/MATLAB Function'
 *    '<S213>/MATLAB Function'
 */
static void MATLABFunction_c(real32_T rtu_re, real32_T rtu_U_lim, real32_T
  rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim)
{
  real32_T U_rel;

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/resonater-I-Regler/MATLAB Function': '<S57>:1' */
  /* '<S57>:1:2' U_abs = sqrt(re^2+im^2); */
  /* '<S57>:1:3' U_rel = U_abs/U_lim; */
  U_rel = sqrtf(rtu_re * rtu_re + rtu_im * rtu_im) / rtu_U_lim;

  /* '<S57>:1:4' if U_rel>=1 */
  if (U_rel >= 1.0F) {
    /* '<S57>:1:5' re_lim = re/U_rel; */
    *rty_re_lim = rtu_re / U_rel;

    /* '<S57>:1:6' im_lim = im/U_rel; */
    *rty_im_lim = rtu_im / U_rel;
  } else {
    /* '<S57>:1:7' else */
    /* '<S57>:1:8' re_lim = re; */
    *rty_re_lim = rtu_re;

    /* '<S57>:1:9' im_lim = im; */
    *rty_im_lim = rtu_im;
  }
}

/*
 * Output and update for atomic system:
 *    '<S32>/MATLAB Function'
 *    '<S33>/MATLAB Function'
 *    '<S34>/MATLAB Function'
 *    '<S35>/MATLAB Function'
 *    '<S123>/MATLAB Function'
 *    '<S124>/MATLAB Function'
 *    '<S125>/MATLAB Function'
 *    '<S126>/MATLAB Function'
 *    '<S214>/MATLAB Function'
 *    '<S215>/MATLAB Function'
 *    ...
 */
static void MATLABFunction_a(real32_T rtu_re, real32_T rtu_U_lim, boolean_T
  rtu_Betrieb, real32_T rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim)
{
  real32_T re_lim;
  real32_T rtu_im_0;
  real32_T tmp;

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/resonater-PI-Regler/MATLAB Function': '<S70>:1' */
  /* '<S70>:1:2' if (re^2 + im^2)<=U_lim^2 */
  tmp = rtu_U_lim * rtu_U_lim;
  if (rtu_re * rtu_re + rtu_im * rtu_im <= tmp) {
    /* '<S70>:1:3' re_lim = re; */
    re_lim = rtu_re;

    /* '<S70>:1:4' im_lim = im; */
    rtu_im_0 = rtu_im;
  } else if (!rtu_Betrieb) {
    /* '<S70>:1:5' elseif Betrieb == 0 */
    /* Generator */
    /* '<S70>:1:7' if abs(im)>0.95*U_lim */
    if (fabsf(rtu_im) > 0.95F * rtu_U_lim) {
      /* '<S70>:1:8' im_lim = sign(im)*0.95*U_lim; */
      if (rtu_im < 0.0F) {
        rtu_im_0 = -1.0F;
      } else {
        rtu_im_0 = (real32_T)(rtu_im > 0.0F);
      }

      rtu_im_0 = rtu_im_0 * 0.95F * rtu_U_lim;
    } else {
      /* '<S70>:1:9' else */
      /* '<S70>:1:10' im_lim = im; */
      rtu_im_0 = rtu_im;
    }

    /* '<S70>:1:12' re_lim = sign(re)*sqrt(U_lim^2 - im_lim^2); */
    if (rtu_re < 0.0F) {
      re_lim = -1.0F;
    } else {
      re_lim = (real32_T)(rtu_re > 0.0F);
    }

    re_lim *= sqrtf(tmp - rtu_im_0 * rtu_im_0);
  } else {
    /* '<S70>:1:13' else */
    /* Motor */
    /* '<S70>:1:15' if abs(re)>0.95*U_lim */
    if (fabsf(rtu_re) > 0.95F * rtu_U_lim) {
      /* '<S70>:1:16' re_lim = sign(re)*0.95*U_lim; */
      if (rtu_re < 0.0F) {
        re_lim = -1.0F;
      } else {
        re_lim = (real32_T)(rtu_re > 0.0F);
      }

      re_lim = re_lim * 0.95F * rtu_U_lim;
    } else {
      /* '<S70>:1:17' else */
      /* '<S70>:1:18' re_lim = re; */
      re_lim = rtu_re;
    }

    /* '<S70>:1:20' im_lim = sign(im)*sqrt(U_lim^2 - re_lim^2); */
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
  localDW->theta_e = rtu_Theta_u_back + rtp_Offset_S;

  /* DataTypeConversion: '<S74>/CastU16En16' incorporates:
   *  DataTypeConversion: '<S80>/CastU16En16'
   *  Gain: '<S32>/Gain5'
   *  Product: '<S32>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp_c = (uint32_T)(0.159154937F * localDW->theta_e
    * 4.2949673E+9F);

  /* RelationalOperator: '<S74>/LTEp25' incorporates:
   *  DataTypeConversion: '<S74>/CastU16En16'
   */
  localDW->LTEp25_my = (localDW->rtb_CastU16En16_jv_tmp_c <= 1073741824U);

  /* RelationalOperator: '<S74>/GTEp75' incorporates:
   *  DataTypeConversion: '<S74>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c >= 3221225472U);

  /* Switch: '<S74>/QuadHandle2' incorporates:
   *  Constant: '<S74>/Point75'
   *  DataTypeConversion: '<S74>/CastU16En16'
   *  RelationalOperator: '<S74>/LTEp50'
   *  Sum: '<S74>/p75mA'
   *  Switch: '<S74>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U) {
    /* Switch: '<S74>/QuadHandle1a' incorporates:
     *  Constant: '<S74>/Point25'
     *  Sum: '<S74>/Amp25'
     *  Sum: '<S74>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp_c;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
        1073741824U;
    }

    /* End of Switch: '<S74>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S74>/QuadHandle1b' incorporates:
     *  Constant: '<S74>/Point75'
     *  Sum: '<S74>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp_c;
  }

  /* End of Switch: '<S74>/QuadHandle2' */

  /* Lookup_n-D: '<S73>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S74>/SignCorrected' incorporates:
   *  Logic: '<S74>/1st or 4th Quad'
   *  Lookup_n-D: '<S73>/Look-Up Table'
   *  UnaryMinus: '<S74>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_h = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_h = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S74>/SignCorrected' */

  /* Sum: '<S23>/Sum' incorporates:
   *  Constant: '<S23>/Constant'
   */
  localDW->theta_ep = rtu_Theta_u + rtp_Offset_S;

  /* Gain: '<S32>/Gain4' incorporates:
   *  Gain: '<S30>/Gain3'
   *  Product: '<S32>/Product5'
   */
  localDW->im_lim_k = 0.159154937F * localDW->theta_ep;

  /* DataTypeConversion: '<S76>/CastU16En16' incorporates:
   *  DataTypeConversion: '<S44>/CastU16En16'
   *  Gain: '<S32>/Gain4'
   */
  localDW->rtb_CastU16En16_jv_tmp_tmp = (uint32_T)(localDW->im_lim_k *
    4.2949673E+9F);

  /* RelationalOperator: '<S76>/LTEp25' incorporates:
   *  DataTypeConversion: '<S76>/CastU16En16'
   */
  localDW->LTEp25_my = (localDW->rtb_CastU16En16_jv_tmp_tmp <= 1073741824U);

  /* RelationalOperator: '<S76>/GTEp75' incorporates:
   *  DataTypeConversion: '<S76>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_tmp >= 3221225472U);

  /* Switch: '<S76>/QuadHandle2' incorporates:
   *  Constant: '<S76>/Point75'
   *  DataTypeConversion: '<S76>/CastU16En16'
   *  RelationalOperator: '<S76>/LTEp50'
   *  Sum: '<S76>/p75mA'
   *  Switch: '<S76>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_tmp <= 2147483648U) {
    /* Switch: '<S76>/QuadHandle1a' incorporates:
     *  Constant: '<S76>/Point25'
     *  Sum: '<S76>/Amp25'
     *  Sum: '<S76>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp_tmp;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_tmp -
        1073741824U;
    }

    /* End of Switch: '<S76>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S76>/QuadHandle1b' incorporates:
     *  Constant: '<S76>/Point75'
     *  Sum: '<S76>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_tmp -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp_tmp;
  }

  /* End of Switch: '<S76>/QuadHandle2' */

  /* Lookup_n-D: '<S75>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S76>/SignCorrected' incorporates:
   *  Logic: '<S76>/1st or 4th Quad'
   *  Lookup_n-D: '<S75>/Look-Up Table'
   *  Switch: '<S117>/SignCorrected'
   *  UnaryMinus: '<S76>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S76>/SignCorrected' */

  /* MATLAB Function: '<S30>/MATLAB Function' */
  MATLABFunction_i(rtu_Psi_PM, rtu_Psi_PM_n, rtu_Psi_PM_k, rtu_I_re, rtu_I_im,
                   rtu_w1, rtu_enable_compensation_current, &localDW->im_lim_d,
                   &localDW->re_lim_g, &localDW->im_lim_mv, &localDW->re_lim_l4,
                   &localDW->im_lim_lb, &localDW->re_lim_i,
                   &localDW->sf_MATLABFunction_i);

  /* RelationalOperator: '<S44>/LTEp25' */
  localDW->LTEp25_my = (localDW->rtb_CastU16En16_jv_tmp_tmp <= 1073741824U);

  /* RelationalOperator: '<S44>/GTEp75' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_tmp >= 3221225472U);

  /* Switch: '<S44>/QuadHandle2' incorporates:
   *  Constant: '<S44>/Point75'
   *  RelationalOperator: '<S44>/LTEp50'
   *  Sum: '<S44>/p75mA'
   *  Switch: '<S44>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_tmp <= 2147483648U) {
    /* Switch: '<S44>/QuadHandle1a' incorporates:
     *  Constant: '<S44>/Point25'
     *  Sum: '<S44>/Amp25'
     *  Sum: '<S44>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp_tmp;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_tmp -
        1073741824U;
    }

    /* End of Switch: '<S44>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S44>/QuadHandle1b' incorporates:
     *  Constant: '<S44>/Point75'
     *  Sum: '<S44>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_tmp -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp_tmp;
  }

  /* End of Switch: '<S44>/QuadHandle2' */

  /* Lookup_n-D: '<S43>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S44>/SignCorrected' incorporates:
   *  Logic: '<S44>/1st or 4th Quad'
   *  Lookup_n-D: '<S43>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S44>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S44>/SignCorrected' */

  /* Product: '<S30>/Product' incorporates:
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->Strom_kompensiert_l = (real32_T)localDW->SignCorrected_o *
    9.31322575E-10F * localDW->im_lim_d;

  /* DataTypeConversion: '<S50>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_tmp;

  /* RelationalOperator: '<S50>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_tmp <= 2147483648U);

  /* Switch: '<S50>/QuadHandle1' incorporates:
   *  Constant: '<S50>/Point50'
   *  Sum: '<S50>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_tmp -
      2147483648U;
  }

  /* End of Switch: '<S50>/QuadHandle1' */

  /* Switch: '<S50>/QuadHandle2' incorporates:
   *  Constant: '<S50>/Point50'
   *  RelationalOperator: '<S50>/LTEp25'
   *  Sum: '<S50>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S50>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S50>/QuadHandle2' */

  /* Lookup_n-D: '<S49>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S50>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S49>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S50>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S50>/SignCorrected' */

  /* Product: '<S30>/Product1' incorporates:
   *  Gain: '<S30>/Gain'
   *  Sum: '<S30>/Add'
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->Delay1_m = (real32_T)(-2147483648LL * localDW->SignCorrected_o) *
    4.33680869E-19F * (rtu_I_im_CT + localDW->re_lim_g);

  /* DataTypeConversion: '<S46>/CastU16En16' incorporates:
   *  Constant: '<S23>/Constant2'
   *  DataTypeConversion: '<S52>/CastU16En16'
   *  Gain: '<S30>/Gain4'
   *  Sum: '<S23>/Add2'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint32_T)((localDW->theta_ep +
    rtp_Offset_gegen) * 0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S46>/LTEp25' incorporates:
   *  DataTypeConversion: '<S46>/CastU16En16'
   */
  localDW->LTEp25_my = (localDW->rtb_CastU16En16_jv_tmp <= 1073741824U);

  /* RelationalOperator: '<S46>/GTEp75' incorporates:
   *  DataTypeConversion: '<S46>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp >= 3221225472U);

  /* Switch: '<S46>/QuadHandle2' incorporates:
   *  Constant: '<S46>/Point75'
   *  DataTypeConversion: '<S46>/CastU16En16'
   *  RelationalOperator: '<S46>/LTEp50'
   *  Sum: '<S46>/p75mA'
   *  Switch: '<S46>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U) {
    /* Switch: '<S46>/QuadHandle1a' incorporates:
     *  Constant: '<S46>/Point25'
     *  Sum: '<S46>/Amp25'
     *  Sum: '<S46>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
        1073741824U;
    }

    /* End of Switch: '<S46>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S46>/QuadHandle1b' incorporates:
     *  Constant: '<S46>/Point75'
     *  Sum: '<S46>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp;
  }

  /* End of Switch: '<S46>/QuadHandle2' */

  /* Lookup_n-D: '<S45>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S46>/SignCorrected' incorporates:
   *  Logic: '<S46>/1st or 4th Quad'
   *  Lookup_n-D: '<S45>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S46>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S46>/SignCorrected' */

  /* Product: '<S30>/Product2' incorporates:
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)localDW->SignCorrected_o * 9.31322575E-10F *
    localDW->im_lim_mv;

  /* DataTypeConversion: '<S52>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S52>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U);

  /* Switch: '<S52>/QuadHandle1' incorporates:
   *  Constant: '<S52>/Point50'
   *  Sum: '<S52>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      2147483648U;
  }

  /* End of Switch: '<S52>/QuadHandle1' */

  /* Switch: '<S52>/QuadHandle2' incorporates:
   *  Constant: '<S52>/Point50'
   *  RelationalOperator: '<S52>/LTEp25'
   *  Sum: '<S52>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S52>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S52>/QuadHandle2' */

  /* Lookup_n-D: '<S51>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S52>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S51>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S52>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S52>/SignCorrected' */

  /* Product: '<S30>/Product3' incorporates:
   *  Gain: '<S30>/Gain1'
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->im_lim_o4 = (real32_T)(-2147483648LL * localDW->SignCorrected_o) *
    4.33680869E-19F * localDW->re_lim_l4;

  /* DataTypeConversion: '<S48>/CastU16En16' incorporates:
   *  Constant: '<S23>/Constant3'
   *  DataTypeConversion: '<S54>/CastU16En16'
   *  Gain: '<S30>/Gain5'
   *  Sum: '<S23>/Add3'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint32_T)((localDW->theta_ep +
    rtp_Offset_null) * 0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S48>/LTEp25' incorporates:
   *  DataTypeConversion: '<S48>/CastU16En16'
   */
  localDW->LTEp25_my = (localDW->rtb_CastU16En16_jv_tmp <= 1073741824U);

  /* RelationalOperator: '<S48>/GTEp75' incorporates:
   *  DataTypeConversion: '<S48>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp >= 3221225472U);

  /* Switch: '<S48>/QuadHandle2' incorporates:
   *  Constant: '<S48>/Point75'
   *  DataTypeConversion: '<S48>/CastU16En16'
   *  RelationalOperator: '<S48>/LTEp50'
   *  Sum: '<S48>/p75mA'
   *  Switch: '<S48>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U) {
    /* Switch: '<S48>/QuadHandle1a' incorporates:
     *  Constant: '<S48>/Point25'
     *  Sum: '<S48>/Amp25'
     *  Sum: '<S48>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
        1073741824U;
    }

    /* End of Switch: '<S48>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S48>/QuadHandle1b' incorporates:
     *  Constant: '<S48>/Point75'
     *  Sum: '<S48>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp;
  }

  /* End of Switch: '<S48>/QuadHandle2' */

  /* Lookup_n-D: '<S47>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S48>/SignCorrected' incorporates:
   *  Logic: '<S48>/1st or 4th Quad'
   *  Lookup_n-D: '<S47>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S48>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S48>/SignCorrected' */

  /* Product: '<S30>/Product4' incorporates:
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->Product3_a = (real32_T)localDW->SignCorrected_o * 9.31322575E-10F *
    localDW->im_lim_lb;

  /* DataTypeConversion: '<S54>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S54>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U);

  /* Switch: '<S54>/QuadHandle1' incorporates:
   *  Constant: '<S54>/Point50'
   *  Sum: '<S54>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      2147483648U;
  }

  /* End of Switch: '<S54>/QuadHandle1' */

  /* Switch: '<S54>/QuadHandle2' incorporates:
   *  Constant: '<S54>/Point50'
   *  RelationalOperator: '<S54>/LTEp25'
   *  Sum: '<S54>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S54>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S54>/QuadHandle2' */

  /* Lookup_n-D: '<S53>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S54>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S53>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S54>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S54>/SignCorrected' */

  /* Sum: '<S30>/Strom_kompensiert' incorporates:
   *  Gain: '<S30>/Gain2'
   *  Product: '<S30>/Product5'
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->Strom_kompensiert_l = ((((localDW->Strom_kompensiert_l +
    localDW->Delay1_m) + localDW->re_lim_gw) + localDW->im_lim_o4) +
    localDW->Product3_a) + (real32_T)(-2147483648LL * localDW->SignCorrected_o) *
    4.33680869E-19F * localDW->re_lim_i;

  /* Sum: '<S23>/Sum2' */
  localDW->Product3_a = localDW->Strom_kompensiert_l - rtu_I_S;

  /* Gain: '<S32>/Gain6' incorporates:
   *  Gain: '<S33>/Gain6'
   *  Gain: '<S34>/Gain6'
   *  Gain: '<S35>/Gain6'
   */
  localDW->Gain2_m = 10.0530977F * localDW->Product3_a;

  /* Product: '<S32>/Product1' incorporates:
   *  Gain: '<S32>/Gain6'
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)localDW->SignCorrected_cw * 9.31322575E-10F *
    localDW->Gain2_m;

  /* Gain: '<S32>/Gain1' incorporates:
   *  Delay: '<S32>/Delay1'
   *  Sum: '<S32>/Sum4'
   */
  localDW->Gain1_h = (localDW->Delay1_DSTATE + localDW->re_lim_gw) *
    0.0138333309F;

  /* DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator = 0.5F * localDW->Gain1_h +
    localDW->DiscreteTimeIntegrator_DSTATE;

  /* Sum: '<S32>/Sum5' */
  localDW->U_re_o = localDW->DiscreteTimeIntegrator + localDW->re_lim_gw;

  /* MATLAB Function: '<S23>/MATLAB Function' */
  MATLABFunction(rtu_I_im, rtu_w1, &localDW->LTEp25_my);

  /* DataTypeConversion: '<S78>/CastU16En16' incorporates:
   *  DataTypeConversion: '<S76>/CastU16En16'
   */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_tmp;

  /* RelationalOperator: '<S78>/LTEp50' incorporates:
   *  DataTypeConversion: '<S76>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_tmp <= 2147483648U);

  /* Switch: '<S78>/QuadHandle1' incorporates:
   *  Constant: '<S78>/Point50'
   *  DataTypeConversion: '<S76>/CastU16En16'
   *  Sum: '<S78>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_tmp -
      2147483648U;
  }

  /* End of Switch: '<S78>/QuadHandle1' */

  /* Switch: '<S78>/QuadHandle2' incorporates:
   *  Constant: '<S78>/Point50'
   *  RelationalOperator: '<S78>/LTEp25'
   *  Sum: '<S78>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S78>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S78>/QuadHandle2' */

  /* Lookup_n-D: '<S77>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S78>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S77>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S78>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S78>/SignCorrected' */

  /* Product: '<S32>/Product' incorporates:
   *  Gain: '<S32>/Gain'
   *  Gain: '<S32>/Gain6'
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)(-2147483648LL * localDW->SignCorrected_o) *
    4.33680869E-19F * localDW->Gain2_m;

  /* Gain: '<S32>/Gain2' incorporates:
   *  Delay: '<S32>/Delay'
   *  Sum: '<S32>/Sum2'
   */
  localDW->Gain2_nl = (localDW->re_lim_gw + localDW->Delay_DSTATE) *
    0.0138333309F;

  /* DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1 = 0.5F * localDW->Gain2_nl +
    localDW->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S32>/Sum6' */
  localDW->U_im_i = localDW->re_lim_gw + localDW->DiscreteTimeIntegrator1;

  /* MATLAB Function: '<S32>/MATLAB Function' incorporates:
   *  Constant: '<S32>/Constant2'
   *  Product: '<S32>/Product6'
   */
  MATLABFunction_a(localDW->U_re_o, 0.92F * rtu_U_ZK1, localDW->LTEp25_my,
                   localDW->U_im_i, &localDW->re_lim_l4, &localDW->im_lim_mv);

  /* DataTypeConversion: '<S80>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c;

  /* RelationalOperator: '<S80>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U);

  /* Switch: '<S80>/QuadHandle1' incorporates:
   *  Constant: '<S80>/Point50'
   *  Sum: '<S80>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      2147483648U;
  }

  /* End of Switch: '<S80>/QuadHandle1' */

  /* Switch: '<S80>/QuadHandle2' incorporates:
   *  Constant: '<S80>/Point50'
   *  RelationalOperator: '<S80>/LTEp25'
   *  Sum: '<S80>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S80>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S80>/QuadHandle2' */

  /* Lookup_n-D: '<S79>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S80>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S79>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S80>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S80>/SignCorrected' */

  /* Sum: '<S32>/Sum' incorporates:
   *  Gain: '<S32>/Gain3'
   *  Product: '<S32>/Product2'
   *  Product: '<S32>/Product3'
   *  Switch: '<S119>/SignCorrected'
   *  Switch: '<S74>/SignCorrected'
   */
  localDW->Sum_pr = (real32_T)(-2147483648LL * localDW->SignCorrected_o) *
    4.33680869E-19F * localDW->im_lim_mv + (real32_T)localDW->SignCorrected_h *
    9.31322575E-10F * localDW->re_lim_l4;

  /* DataTypeConversion: '<S87>/CastU16En16' incorporates:
   *  Constant: '<S33>/Constant1'
   *  DataTypeConversion: '<S93>/CastU16En16'
   *  Gain: '<S33>/Gain5'
   *  Product: '<S33>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp_c = (uint32_T)(localDW->theta_e * 2.0F *
    0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S87>/LTEp25' incorporates:
   *  DataTypeConversion: '<S87>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 1073741824U);

  /* RelationalOperator: '<S87>/GTEp75' incorporates:
   *  DataTypeConversion: '<S87>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp_c >= 3221225472U);

  /* Switch: '<S87>/QuadHandle2' incorporates:
   *  Constant: '<S87>/Point75'
   *  DataTypeConversion: '<S87>/CastU16En16'
   *  RelationalOperator: '<S87>/LTEp50'
   *  Sum: '<S87>/p75mA'
   *  Switch: '<S87>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U) {
    /* Switch: '<S87>/QuadHandle1a' incorporates:
     *  Constant: '<S87>/Point25'
     *  Sum: '<S87>/Amp25'
     *  Sum: '<S87>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp_c;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
        1073741824U;
    }

    /* End of Switch: '<S87>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S87>/QuadHandle1b' incorporates:
     *  Constant: '<S87>/Point75'
     *  Sum: '<S87>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp_c;
  }

  /* End of Switch: '<S87>/QuadHandle2' */

  /* Lookup_n-D: '<S86>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S87>/SignCorrected' incorporates:
   *  Logic: '<S87>/1st or 4th Quad'
   *  Lookup_n-D: '<S86>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S87>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S87>/SignCorrected' */

  /* DataTypeConversion: '<S89>/CastU16En16' incorporates:
   *  Constant: '<S33>/Constant1'
   *  DataTypeConversion: '<S91>/CastU16En16'
   *  Gain: '<S33>/Gain4'
   *  Product: '<S33>/Product5'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint32_T)(localDW->theta_ep * 2.0F *
    0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S89>/LTEp25' incorporates:
   *  DataTypeConversion: '<S89>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 1073741824U);

  /* RelationalOperator: '<S89>/GTEp75' incorporates:
   *  DataTypeConversion: '<S89>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp >= 3221225472U);

  /* Switch: '<S89>/QuadHandle2' incorporates:
   *  Constant: '<S89>/Point75'
   *  DataTypeConversion: '<S89>/CastU16En16'
   *  RelationalOperator: '<S89>/LTEp50'
   *  Sum: '<S89>/p75mA'
   *  Switch: '<S89>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U) {
    /* Switch: '<S89>/QuadHandle1a' incorporates:
     *  Constant: '<S89>/Point25'
     *  Sum: '<S89>/Amp25'
     *  Sum: '<S89>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
        1073741824U;
    }

    /* End of Switch: '<S89>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S89>/QuadHandle1b' incorporates:
     *  Constant: '<S89>/Point75'
     *  Sum: '<S89>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp;
  }

  /* End of Switch: '<S89>/QuadHandle2' */

  /* Lookup_n-D: '<S88>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S89>/SignCorrected' incorporates:
   *  Logic: '<S89>/1st or 4th Quad'
   *  Lookup_n-D: '<S88>/Look-Up Table'
   *  Switch: '<S117>/SignCorrected'
   *  UnaryMinus: '<S89>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S89>/SignCorrected' */

  /* Product: '<S33>/Product1' incorporates:
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->Delay1_m = (real32_T)localDW->SignCorrected_cw * 9.31322575E-10F *
    localDW->Gain2_m;

  /* Gain: '<S33>/Gain1' incorporates:
   *  Delay: '<S33>/Delay1'
   *  Sum: '<S33>/Sum4'
   */
  localDW->Gain1_g = (localDW->Delay1_DSTATE_m + localDW->Delay1_m) *
    0.00138333312F;

  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_o = 0.5F * localDW->Gain1_g +
    localDW->DiscreteTimeIntegrator_DSTATE_d;

  /* Sum: '<S33>/Sum5' */
  localDW->U_re_h = localDW->DiscreteTimeIntegrator_o + localDW->Delay1_m;

  /* DataTypeConversion: '<S91>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S91>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U);

  /* Switch: '<S91>/QuadHandle1' incorporates:
   *  Constant: '<S91>/Point50'
   *  Sum: '<S91>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      2147483648U;
  }

  /* End of Switch: '<S91>/QuadHandle1' */

  /* Switch: '<S91>/QuadHandle2' incorporates:
   *  Constant: '<S91>/Point50'
   *  RelationalOperator: '<S91>/LTEp25'
   *  Sum: '<S91>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S91>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S91>/QuadHandle2' */

  /* Lookup_n-D: '<S90>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S91>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S90>/Look-Up Table'
   *  Switch: '<S117>/SignCorrected'
   *  UnaryMinus: '<S91>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S91>/SignCorrected' */

  /* Product: '<S33>/Product' incorporates:
   *  Gain: '<S33>/Gain'
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)(-2147483648LL * localDW->SignCorrected_cw) *
    4.33680869E-19F * localDW->Gain2_m;

  /* Gain: '<S33>/Gain2' incorporates:
   *  Delay: '<S33>/Delay'
   *  Sum: '<S33>/Sum2'
   */
  localDW->Gain2_d = (localDW->re_lim_gw + localDW->Delay_DSTATE_a) *
    0.00138333312F;

  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_f = 0.5F * localDW->Gain2_d +
    localDW->DiscreteTimeIntegrator1_DSTAT_m;

  /* Sum: '<S33>/Sum6' */
  localDW->U_im_pl = localDW->re_lim_gw + localDW->DiscreteTimeIntegrator1_f;

  /* MATLAB Function: '<S33>/MATLAB Function' incorporates:
   *  Constant: '<S33>/Constant2'
   *  Product: '<S33>/Product6'
   */
  MATLABFunction_a(localDW->U_re_h, 0.05F * rtu_U_ZK1, localDW->LTEp25_my,
                   localDW->U_im_pl, &localDW->re_lim_i, &localDW->im_lim_lb);

  /* Product: '<S33>/Product3' incorporates:
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)localDW->SignCorrected_o * 9.31322575E-10F *
    localDW->re_lim_i;

  /* DataTypeConversion: '<S93>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c;

  /* RelationalOperator: '<S93>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U);

  /* Switch: '<S93>/QuadHandle1' incorporates:
   *  Constant: '<S93>/Point50'
   *  Sum: '<S93>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      2147483648U;
  }

  /* End of Switch: '<S93>/QuadHandle1' */

  /* Switch: '<S93>/QuadHandle2' incorporates:
   *  Constant: '<S93>/Point50'
   *  RelationalOperator: '<S93>/LTEp25'
   *  Sum: '<S93>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S93>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S93>/QuadHandle2' */

  /* Lookup_n-D: '<S92>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S93>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S92>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S93>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S93>/SignCorrected' */

  /* Sum: '<S33>/Sum' incorporates:
   *  Gain: '<S33>/Gain3'
   *  Product: '<S33>/Product2'
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->Sum_j = (real32_T)(-2147483648LL * localDW->SignCorrected_o) *
    4.33680869E-19F * localDW->im_lim_lb + localDW->re_lim_gw;

  /* DataTypeConversion: '<S61>/CastU16En16' incorporates:
   *  Constant: '<S31>/Constant1'
   *  DataTypeConversion: '<S67>/CastU16En16'
   *  Gain: '<S31>/Gain6'
   *  Product: '<S31>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp_c = (uint32_T)(localDW->theta_e * 3.0F *
    0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S61>/LTEp25' incorporates:
   *  DataTypeConversion: '<S61>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 1073741824U);

  /* RelationalOperator: '<S61>/GTEp75' incorporates:
   *  DataTypeConversion: '<S61>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp_c >= 3221225472U);

  /* Switch: '<S61>/QuadHandle2' incorporates:
   *  Constant: '<S61>/Point75'
   *  DataTypeConversion: '<S61>/CastU16En16'
   *  RelationalOperator: '<S61>/LTEp50'
   *  Sum: '<S61>/p75mA'
   *  Switch: '<S61>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U) {
    /* Switch: '<S61>/QuadHandle1a' incorporates:
     *  Constant: '<S61>/Point25'
     *  Sum: '<S61>/Amp25'
     *  Sum: '<S61>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp_c;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
        1073741824U;
    }

    /* End of Switch: '<S61>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S61>/QuadHandle1b' incorporates:
     *  Constant: '<S61>/Point75'
     *  Sum: '<S61>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp_c;
  }

  /* End of Switch: '<S61>/QuadHandle2' */

  /* Lookup_n-D: '<S60>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S61>/SignCorrected' incorporates:
   *  Logic: '<S61>/1st or 4th Quad'
   *  Lookup_n-D: '<S60>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S61>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S61>/SignCorrected' */

  /* DataTypeConversion: '<S63>/CastU16En16' incorporates:
   *  Constant: '<S31>/Constant1'
   *  DataTypeConversion: '<S65>/CastU16En16'
   *  Gain: '<S31>/Gain5'
   *  Product: '<S31>/Product5'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint32_T)(localDW->theta_ep * 3.0F *
    0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S63>/LTEp25' incorporates:
   *  DataTypeConversion: '<S63>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 1073741824U);

  /* RelationalOperator: '<S63>/GTEp75' incorporates:
   *  DataTypeConversion: '<S63>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp >= 3221225472U);

  /* Switch: '<S63>/QuadHandle2' incorporates:
   *  Constant: '<S63>/Point75'
   *  DataTypeConversion: '<S63>/CastU16En16'
   *  RelationalOperator: '<S63>/LTEp50'
   *  Sum: '<S63>/p75mA'
   *  Switch: '<S63>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U) {
    /* Switch: '<S63>/QuadHandle1a' incorporates:
     *  Constant: '<S63>/Point25'
     *  Sum: '<S63>/Amp25'
     *  Sum: '<S63>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
        1073741824U;
    }

    /* End of Switch: '<S63>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S63>/QuadHandle1b' incorporates:
     *  Constant: '<S63>/Point75'
     *  Sum: '<S63>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp;
  }

  /* End of Switch: '<S63>/QuadHandle2' */

  /* Lookup_n-D: '<S62>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S63>/SignCorrected' incorporates:
   *  Logic: '<S63>/1st or 4th Quad'
   *  Lookup_n-D: '<S62>/Look-Up Table'
   *  Switch: '<S117>/SignCorrected'
   *  UnaryMinus: '<S63>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S63>/SignCorrected' */

  /* Gain: '<S31>/Gain4' */
  localDW->Delay1_m = 55.3333244F * localDW->Product3_a;

  /* Gain: '<S31>/Gain1' incorporates:
   *  Delay: '<S31>/Delay1'
   *  Product: '<S31>/Product1'
   *  Sum: '<S31>/Sum4'
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->Gain1_i = ((real32_T)localDW->SignCorrected_cw * 9.31322575E-10F *
                      localDW->Delay1_m + localDW->Delay1_DSTATE_l) * 2.5E-5F;

  /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->U_re = 0.5F * localDW->Gain1_i +
    localDW->DiscreteTimeIntegrator_DSTATE_m;

  /* DataTypeConversion: '<S65>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S65>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U);

  /* Switch: '<S65>/QuadHandle1' incorporates:
   *  Constant: '<S65>/Point50'
   *  Sum: '<S65>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      2147483648U;
  }

  /* End of Switch: '<S65>/QuadHandle1' */

  /* Switch: '<S65>/QuadHandle2' incorporates:
   *  Constant: '<S65>/Point50'
   *  RelationalOperator: '<S65>/LTEp25'
   *  Sum: '<S65>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S65>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S65>/QuadHandle2' */

  /* Lookup_n-D: '<S64>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S65>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S64>/Look-Up Table'
   *  Switch: '<S117>/SignCorrected'
   *  UnaryMinus: '<S65>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S65>/SignCorrected' */

  /* Gain: '<S31>/Gain2' incorporates:
   *  Delay: '<S31>/Delay'
   *  Gain: '<S31>/Gain'
   *  Product: '<S31>/Product'
   *  Sum: '<S31>/Sum2'
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->Gain2_io = ((real32_T)(-2147483648LL * localDW->SignCorrected_cw) *
                       4.33680869E-19F * localDW->Delay1_m +
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
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)localDW->SignCorrected_o * 9.31322575E-10F *
    localDW->re_lim_g;

  /* DataTypeConversion: '<S67>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c;

  /* RelationalOperator: '<S67>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U);

  /* Switch: '<S67>/QuadHandle1' incorporates:
   *  Constant: '<S67>/Point50'
   *  Sum: '<S67>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      2147483648U;
  }

  /* End of Switch: '<S67>/QuadHandle1' */

  /* Switch: '<S67>/QuadHandle2' incorporates:
   *  Constant: '<S67>/Point50'
   *  RelationalOperator: '<S67>/LTEp25'
   *  Sum: '<S67>/p50mA'
   *  Switch: '<S119>/QuadHandle2'
   *  Switch: '<S67>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S67>/QuadHandle2' */

  /* Lookup_n-D: '<S66>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S67>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S66>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S67>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S67>/SignCorrected' */

  /* Sum: '<S31>/Sum' incorporates:
   *  Gain: '<S31>/Gain3'
   *  Product: '<S31>/Product2'
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->Sum_i = (real32_T)(-2147483648LL * localDW->SignCorrected_o) *
    4.33680869E-19F * localDW->im_lim_d + localDW->re_lim_gw;

  /* DataTypeConversion: '<S100>/CastU16En16' incorporates:
   *  Constant: '<S34>/Constant1'
   *  DataTypeConversion: '<S106>/CastU16En16'
   *  Gain: '<S34>/Gain5'
   *  Product: '<S34>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp_c = (uint32_T)(localDW->theta_e * 4.0F *
    0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S100>/LTEp25' incorporates:
   *  DataTypeConversion: '<S100>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 1073741824U);

  /* RelationalOperator: '<S100>/GTEp75' incorporates:
   *  DataTypeConversion: '<S100>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp_c >= 3221225472U);

  /* Switch: '<S100>/QuadHandle2' incorporates:
   *  Constant: '<S100>/Point75'
   *  DataTypeConversion: '<S100>/CastU16En16'
   *  RelationalOperator: '<S100>/LTEp50'
   *  Sum: '<S100>/p75mA'
   *  Switch: '<S100>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U) {
    /* Switch: '<S100>/QuadHandle1a' incorporates:
     *  Constant: '<S100>/Point25'
     *  Sum: '<S100>/Amp25'
     *  Sum: '<S100>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp_c;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
        1073741824U;
    }

    /* End of Switch: '<S100>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S100>/QuadHandle1b' incorporates:
     *  Constant: '<S100>/Point75'
     *  Sum: '<S100>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp_c;
  }

  /* End of Switch: '<S100>/QuadHandle2' */

  /* Lookup_n-D: '<S99>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S100>/SignCorrected' incorporates:
   *  Logic: '<S100>/1st or 4th Quad'
   *  Lookup_n-D: '<S99>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S100>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S100>/SignCorrected' */

  /* DataTypeConversion: '<S102>/CastU16En16' incorporates:
   *  Constant: '<S34>/Constant1'
   *  DataTypeConversion: '<S104>/CastU16En16'
   *  Gain: '<S34>/Gain4'
   *  Product: '<S34>/Product5'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint32_T)(localDW->theta_ep * 4.0F *
    0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S102>/LTEp25' incorporates:
   *  DataTypeConversion: '<S102>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 1073741824U);

  /* RelationalOperator: '<S102>/GTEp75' incorporates:
   *  DataTypeConversion: '<S102>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp >= 3221225472U);

  /* Switch: '<S102>/QuadHandle2' incorporates:
   *  Constant: '<S102>/Point75'
   *  DataTypeConversion: '<S102>/CastU16En16'
   *  RelationalOperator: '<S102>/LTEp50'
   *  Sum: '<S102>/p75mA'
   *  Switch: '<S102>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U) {
    /* Switch: '<S102>/QuadHandle1a' incorporates:
     *  Constant: '<S102>/Point25'
     *  Sum: '<S102>/Amp25'
     *  Sum: '<S102>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
        1073741824U;
    }

    /* End of Switch: '<S102>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S102>/QuadHandle1b' incorporates:
     *  Constant: '<S102>/Point75'
     *  Sum: '<S102>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp;
  }

  /* End of Switch: '<S102>/QuadHandle2' */

  /* Lookup_n-D: '<S101>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S102>/SignCorrected' incorporates:
   *  Logic: '<S102>/1st or 4th Quad'
   *  Lookup_n-D: '<S101>/Look-Up Table'
   *  Switch: '<S117>/SignCorrected'
   *  UnaryMinus: '<S102>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S102>/SignCorrected' */

  /* Product: '<S34>/Product1' incorporates:
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->Delay1_m = (real32_T)localDW->SignCorrected_cw * 9.31322575E-10F *
    localDW->Gain2_m;

  /* Delay: '<S34>/Delay1' */
  localDW->re_lim_b = localDW->Delay1_DSTATE_g;

  /* Gain: '<S34>/Gain1' incorporates:
   *  Delay: '<S34>/Delay1'
   *  Sum: '<S34>/Sum4'
   */
  localDW->Gain1_n = (localDW->Delay1_DSTATE_g + localDW->Delay1_m) *
    0.00138333312F;

  /* DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_j = 0.5F * localDW->Gain1_n +
    localDW->DiscreteTimeIntegrator_DSTATE_i;

  /* Sum: '<S34>/Sum5' */
  localDW->Delay1_m += localDW->DiscreteTimeIntegrator_j;

  /* DataTypeConversion: '<S104>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S104>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U);

  /* Switch: '<S104>/QuadHandle1' incorporates:
   *  Constant: '<S104>/Point50'
   *  Sum: '<S104>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      2147483648U;
  }

  /* End of Switch: '<S104>/QuadHandle1' */

  /* Switch: '<S104>/QuadHandle2' incorporates:
   *  Constant: '<S104>/Point50'
   *  RelationalOperator: '<S104>/LTEp25'
   *  Sum: '<S104>/p50mA'
   *  Switch: '<S104>/QuadHandle1'
   *  Switch: '<S119>/QuadHandle2'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S104>/QuadHandle2' */

  /* Lookup_n-D: '<S103>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S104>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S103>/Look-Up Table'
   *  Switch: '<S117>/SignCorrected'
   *  UnaryMinus: '<S104>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S104>/SignCorrected' */

  /* Product: '<S34>/Product' incorporates:
   *  Gain: '<S34>/Gain'
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)(-2147483648LL * localDW->SignCorrected_cw) *
    4.33680869E-19F * localDW->Gain2_m;

  /* Gain: '<S34>/Gain2' incorporates:
   *  Delay: '<S34>/Delay'
   *  Sum: '<S34>/Sum2'
   */
  localDW->Gain2_e = (localDW->re_lim_gw + localDW->Delay_DSTATE_bz) *
    0.00138333312F;

  /* DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_e = 0.5F * localDW->Gain2_e +
    localDW->DiscreteTimeIntegrator1_DSTAT_k;

  /* Sum: '<S34>/Sum6' */
  localDW->U_im_pt = localDW->re_lim_gw + localDW->DiscreteTimeIntegrator1_e;

  /* MATLAB Function: '<S34>/MATLAB Function' incorporates:
   *  Constant: '<S34>/Constant2'
   *  Product: '<S34>/Product6'
   */
  MATLABFunction_a(localDW->Delay1_m, 0.025F * rtu_U_ZK1, localDW->LTEp25_my,
                   localDW->U_im_pt, &localDW->re_lim_b, &localDW->im_lim_k);

  /* Product: '<S34>/Product3' incorporates:
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)localDW->SignCorrected_o * 9.31322575E-10F *
    localDW->re_lim_b;

  /* DataTypeConversion: '<S106>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c;

  /* RelationalOperator: '<S106>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U);

  /* Switch: '<S106>/QuadHandle1' incorporates:
   *  Constant: '<S106>/Point50'
   *  Sum: '<S106>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      2147483648U;
  }

  /* End of Switch: '<S106>/QuadHandle1' */

  /* Switch: '<S106>/QuadHandle2' incorporates:
   *  Constant: '<S106>/Point50'
   *  RelationalOperator: '<S106>/LTEp25'
   *  Sum: '<S106>/p50mA'
   *  Switch: '<S106>/QuadHandle1'
   *  Switch: '<S119>/QuadHandle2'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S106>/QuadHandle2' */

  /* Lookup_n-D: '<S105>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S106>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S105>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S106>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S106>/SignCorrected' */

  /* Sum: '<S34>/Sum' incorporates:
   *  Gain: '<S34>/Gain3'
   *  Product: '<S34>/Product2'
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->Sum_o = (real32_T)(-2147483648LL * localDW->SignCorrected_o) *
    4.33680869E-19F * localDW->im_lim_k + localDW->re_lim_gw;

  /* DataTypeConversion: '<S113>/CastU16En16' incorporates:
   *  Constant: '<S35>/Constant1'
   *  DataTypeConversion: '<S119>/CastU16En16'
   *  Gain: '<S35>/Gain5'
   *  Product: '<S35>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp_c = (uint32_T)(localDW->theta_e * 6.0F *
    0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S113>/LTEp25' incorporates:
   *  DataTypeConversion: '<S113>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 1073741824U);

  /* RelationalOperator: '<S113>/GTEp75' incorporates:
   *  DataTypeConversion: '<S113>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp_c >= 3221225472U);

  /* Switch: '<S113>/QuadHandle2' incorporates:
   *  Constant: '<S113>/Point75'
   *  DataTypeConversion: '<S113>/CastU16En16'
   *  RelationalOperator: '<S113>/LTEp50'
   *  Sum: '<S113>/p75mA'
   *  Switch: '<S113>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U) {
    /* Switch: '<S113>/QuadHandle1a' incorporates:
     *  Constant: '<S113>/Point25'
     *  Sum: '<S113>/Amp25'
     *  Sum: '<S113>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp_c;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
        1073741824U;
    }

    /* End of Switch: '<S113>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S113>/QuadHandle1b' incorporates:
     *  Constant: '<S113>/Point75'
     *  Sum: '<S113>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp_c;
  }

  /* End of Switch: '<S113>/QuadHandle2' */

  /* Lookup_n-D: '<S112>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S113>/SignCorrected' incorporates:
   *  Logic: '<S113>/1st or 4th Quad'
   *  Lookup_n-D: '<S112>/Look-Up Table'
   *  Switch: '<S119>/SignCorrected'
   *  UnaryMinus: '<S113>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S113>/SignCorrected' */

  /* DataTypeConversion: '<S115>/CastU16En16' incorporates:
   *  Constant: '<S35>/Constant1'
   *  DataTypeConversion: '<S117>/CastU16En16'
   *  Gain: '<S35>/Gain4'
   *  Product: '<S35>/Product5'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint32_T)(localDW->theta_ep * 6.0F *
    0.159154937F * 4.2949673E+9F);

  /* RelationalOperator: '<S115>/LTEp25' incorporates:
   *  DataTypeConversion: '<S115>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 1073741824U);

  /* RelationalOperator: '<S115>/GTEp75' incorporates:
   *  DataTypeConversion: '<S115>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp >= 3221225472U);

  /* Switch: '<S115>/QuadHandle2' incorporates:
   *  Constant: '<S115>/Point75'
   *  DataTypeConversion: '<S115>/CastU16En16'
   *  RelationalOperator: '<S115>/LTEp50'
   *  Sum: '<S115>/p75mA'
   *  Switch: '<S115>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U) {
    /* Switch: '<S115>/QuadHandle1a' incorporates:
     *  Constant: '<S115>/Point25'
     *  Sum: '<S115>/Amp25'
     *  Sum: '<S115>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = 1073741824U -
        localDW->rtb_CastU16En16_jv_tmp;
    } else {
      localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
        1073741824U;
    }

    /* End of Switch: '<S115>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S115>/QuadHandle1b' incorporates:
     *  Constant: '<S115>/Point75'
     *  Sum: '<S115>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      3221225472U;
  } else {
    localDW->rtb_CastU16En16_jv_m = 3221225472U -
      localDW->rtb_CastU16En16_jv_tmp;
  }

  /* End of Switch: '<S115>/QuadHandle2' */

  /* Lookup_n-D: '<S114>/Look-Up Table' */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S115>/SignCorrected' incorporates:
   *  Logic: '<S115>/1st or 4th Quad'
   *  Lookup_n-D: '<S114>/Look-Up Table'
   *  Switch: '<S117>/SignCorrected'
   *  UnaryMinus: '<S115>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S115>/SignCorrected' */

  /* Product: '<S35>/Product1' incorporates:
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->im_lim_o4 = (real32_T)localDW->SignCorrected_cw * 9.31322575E-10F *
    localDW->Gain2_m;

  /* Gain: '<S35>/Gain1' incorporates:
   *  Delay: '<S35>/Delay1'
   *  Sum: '<S35>/Sum4'
   */
  localDW->theta_e = (localDW->Delay1_DSTATE_i + localDW->im_lim_o4) *
    0.00138333312F;

  /* DiscreteIntegrator: '<S35>/Discrete-Time Integrator' */
  localDW->theta_ep = 0.5F * localDW->theta_e +
    localDW->DiscreteTimeIntegrator_DSTAT_if;

  /* Sum: '<S35>/Sum5' */
  localDW->U_re_b = localDW->theta_ep + localDW->im_lim_o4;

  /* DataTypeConversion: '<S117>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S117>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 2147483648U);

  /* Switch: '<S117>/QuadHandle1' incorporates:
   *  Constant: '<S117>/Point50'
   *  Sum: '<S117>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp -
      2147483648U;
  }

  /* End of Switch: '<S117>/QuadHandle1' */

  /* Switch: '<S117>/QuadHandle2' incorporates:
   *  Constant: '<S117>/Point50'
   *  RelationalOperator: '<S117>/LTEp25'
   *  Sum: '<S117>/p50mA'
   *  Switch: '<S117>/QuadHandle1'
   *  Switch: '<S119>/QuadHandle2'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S117>/QuadHandle2' */

  /* Lookup_n-D: '<S116>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S117>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S116>/Look-Up Table'
   *  UnaryMinus: '<S117>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_cw = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S117>/SignCorrected' */

  /* Product: '<S35>/Product' incorporates:
   *  Gain: '<S35>/Gain'
   *  Switch: '<S117>/SignCorrected'
   */
  localDW->re_lim_gw = (real32_T)(-2147483648LL * localDW->SignCorrected_cw) *
    4.33680869E-19F * localDW->Gain2_m;

  /* Gain: '<S35>/Gain2' incorporates:
   *  Delay: '<S35>/Delay'
   *  Sum: '<S35>/Sum2'
   */
  localDW->Gain2_m = (localDW->re_lim_gw + localDW->Delay_DSTATE_h) *
    0.00138333312F;

  /* DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_h = 0.5F * localDW->Gain2_m +
    localDW->DiscreteTimeIntegrator1_DSTAT_a;

  /* Sum: '<S35>/Sum6' */
  localDW->U_im_f = localDW->re_lim_gw + localDW->DiscreteTimeIntegrator1_h;

  /* MATLAB Function: '<S35>/MATLAB Function' incorporates:
   *  Constant: '<S35>/Constant2'
   *  Product: '<S35>/Product6'
   */
  MATLABFunction_a(localDW->U_re_b, 0.01F * rtu_U_ZK1, localDW->LTEp25_my,
                   localDW->U_im_f, &localDW->re_lim_gw, &localDW->im_lim_o4);

  /* Product: '<S35>/Product3' incorporates:
   *  Switch: '<S119>/SignCorrected'
   */
  localDW->Product3_a = (real32_T)localDW->SignCorrected_o * 9.31322575E-10F *
    localDW->re_lim_gw;

  /* DataTypeConversion: '<S119>/CastU16En16' */
  localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c;

  /* RelationalOperator: '<S119>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_c <= 2147483648U);

  /* Switch: '<S119>/QuadHandle1' incorporates:
   *  Constant: '<S119>/Point50'
   *  Sum: '<S119>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->rtb_CastU16En16_jv_m = localDW->rtb_CastU16En16_jv_tmp_c -
      2147483648U;
  }

  /* End of Switch: '<S119>/QuadHandle1' */

  /* Switch: '<S119>/QuadHandle2' incorporates:
   *  Constant: '<S119>/Point50'
   *  RelationalOperator: '<S119>/LTEp25'
   *  Sum: '<S119>/p50mA'
   *  Switch: '<S119>/QuadHandle1'
   */
  if (localDW->rtb_CastU16En16_jv_m > 1073741824U) {
    localDW->rtb_CastU16En16_jv_m = 2147483648U - localDW->rtb_CastU16En16_jv_m;
  }

  /* End of Switch: '<S119>/QuadHandle2' */

  /* Lookup_n-D: '<S118>/Look-Up Table' incorporates:
   *  Switch: '<S119>/QuadHandle2'
   */
  localDW->rtb_CastU16En16_jv_m = plook_u32u32u64n32_even20c_gf
    (localDW->rtb_CastU16En16_jv_m, 0U, 1024U, &localDW->frac);

  /* Switch: '<S119>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S118>/Look-Up Table'
   *  UnaryMinus: '<S119>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  } else {
    localDW->SignCorrected_o = -intrp1d_s32s64s64u32u64n32l_f
      (localDW->rtb_CastU16En16_jv_m, localDW->frac, rtConstP.pooled3);
  }

  /* End of Switch: '<S119>/SignCorrected' */

  /* Sum: '<S23>/Add' incorporates:
   *  Constant: '<S23>/Constant1'
   *  Gain: '<S35>/Gain3'
   *  Product: '<S23>/Divide'
   *  Product: '<S35>/Product2'
   *  Sum: '<S23>/Add1'
   *  Sum: '<S35>/Sum'
   *  Switch: '<S119>/SignCorrected'
   */
  *rty_a = (((real32_T)(-2147483648LL * localDW->SignCorrected_o) *
             4.33680869E-19F * localDW->im_lim_o4 + localDW->Product3_a) +
            (((localDW->Sum_pr + localDW->Sum_j) + localDW->Sum_i) +
             localDW->Sum_o)) / rtu_U_ZK1 + 0.5F;

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
  localDW->Delay_DSTATE = localDW->im_lim_mv - localDW->U_im_i;

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
  localDW->Delay1_DSTATE_g = localDW->re_lim_b - localDW->Delay1_m;

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
  localDW->DiscreteTimeIntegrator_DSTAT_if = 0.5F * localDW->theta_e +
    localDW->theta_ep;

  /* Update for Delay: '<S35>/Delay' incorporates:
   *  Sum: '<S35>/Sum1'
   */
  localDW->Delay_DSTATE_h = localDW->im_lim_o4 - localDW->U_im_f;

  /* Update for DiscreteIntegrator: '<S35>/Discrete-Time Integrator1' */
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
      /* '<S17>:1:6' b = 2*Psi_PM*R*i_ref_max; */
      /* '<S17>:1:7' c = (R*i_ref_max)^2 - U_FA^2; */
      rtDW->c = 17.222496F - rtDW->c * rtDW->c;

      /* '<S17>:1:8' if -4*a*c >= single(0) */
      if (-0.0155696403F * rtDW->c >= 0.0F) {
        /* '<S17>:1:9' n_eck = single(30)/(p*pi) * (-b+sqrt(b^2 -4*a*c))/(2*a); */
        rtDW->c = (sqrtf(0.0201441254F - 0.0155696403F * rtDW->c) + -0.14193F) *
          0.530516505F / 0.00778482F;

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
        rtDW->a = fminf(3.0F * rtDW->c, 400.0F);
      } else {
        /* '<S17>:1:17' else */
        /* '<S17>:1:18' n_sat = min(n_eck, n_ref_max); */
        rtDW->a = fminf(rtDW->c, 400.0F);
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
      if (fabsf(rtDW->b) >= 47.5F) {
        /* '<S12>:1:16' I_re_soll = sign(I_re_soll)*0.95*I_ref_max; */
        if (rtDW->b < 0.0F) {
          rtDW->b = -1.0F;
        } else {
          rtDW->b = (real32_T)(rtDW->b > 0.0F);
        }

        rtDW->b = rtDW->b * 0.95F * 50.0F;
      }

      /* '<S12>:1:19' I_im_max = sqrt(I_ref_max^2-I_re_soll^2); */
      rtDW->c = sqrtf(2500.0F - rtDW->b * rtDW->b);

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
                rtU->Ref_I_im_ext_mit * rtU->Ref_I_im_ext_mit) > 50.0F) {
        /* '<S22>:1:6' if abs(I_re_soll_ext)>= 0.95*I_ref_max */
        if (fabsf(rtU->Ref_I_re_ext_mit) >= 47.5F) {
          /* '<S22>:1:7' I_re_soll = sign(I_re_soll_ext)*0.95*I_ref_max; */
          if (rtU->Ref_I_re_ext_mit < 0.0F) {
            rtDW->c = -1.0F;
          } else {
            rtDW->c = (real32_T)(rtU->Ref_I_re_ext_mit > 0.0F);
          }

          rtDW->b = rtDW->c * 0.95F * 50.0F;
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
        rtDW->I_im = sqrtf(2500.0F - rtDW->b * rtDW->b) * rtDW->c;
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
       *  ActionPort: '<S302>/Action Port'
       */
      /* DataTypeConversion: '<S311>/CastU16En16' incorporates:
       *  Gain: '<S302>/Gain1'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/ordnung_a'
       *  Inport: '<Root>/phase_a'
       *  Product: '<S302>/Product8'
       *  Sum: '<S302>/Add9'
       */
      rtDW->CastU16En16_h = (uint32_T)((rtU->ordnung_a * rtU->Act_theta_u_el +
        rtU->phase_a) * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S311>/LTEp50' incorporates:
       *  DataTypeConversion: '<S311>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 2147483648U);

      /* Switch: '<S311>/QuadHandle1' incorporates:
       *  Constant: '<S311>/Point50'
       *  DataTypeConversion: '<S311>/CastU16En16'
       *  Sum: '<S311>/Amp50'
       */
      if (!rtDW->LTEp50_j) {
        rtDW->CastU16En16_h -= 2147483648U;
      }

      /* End of Switch: '<S311>/QuadHandle1' */

      /* Switch: '<S311>/QuadHandle2' incorporates:
       *  Constant: '<S311>/Point50'
       *  RelationalOperator: '<S311>/LTEp25'
       *  Sum: '<S311>/p50mA'
       *  Switch: '<S311>/QuadHandle1'
       *  Switch: '<S315>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S311>/QuadHandle2' */

      /* Lookup_n-D: '<S310>/Look-Up Table' incorporates:
       *  Switch: '<S315>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S311>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S310>/Look-Up Table'
       *  Switch: '<S315>/SignCorrected'
       *  UnaryMinus: '<S311>/Negate'
       */
      if (rtDW->LTEp50_j) {
        rtDW->SignCorrected_a = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_a = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S311>/SignCorrected' */

      /* Product: '<S302>/Product7' incorporates:
       *  Inport: '<Root>/amplitude_a'
       *  Switch: '<S315>/SignCorrected'
       */
      rtDW->c = (real32_T)rtDW->SignCorrected_a * 9.31322575E-10F *
        rtU->amplitude_a;

      /* DataTypeConversion: '<S309>/CastU16En16' incorporates:
       *  Gain: '<S302>/Gain'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/ordnung_b'
       *  Inport: '<Root>/phase_b'
       *  Product: '<S302>/Product9'
       *  Sum: '<S302>/Add7'
       */
      rtDW->CastU16En16_h = (uint32_T)((rtU->ordnung_b * rtU->Act_theta_u_el +
        rtU->phase_b) * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S309>/LTEp50' incorporates:
       *  DataTypeConversion: '<S309>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 2147483648U);

      /* Switch: '<S309>/QuadHandle1' incorporates:
       *  Constant: '<S309>/Point50'
       *  DataTypeConversion: '<S309>/CastU16En16'
       *  Sum: '<S309>/Amp50'
       */
      if (!rtDW->LTEp50_j) {
        rtDW->CastU16En16_h -= 2147483648U;
      }

      /* End of Switch: '<S309>/QuadHandle1' */

      /* Switch: '<S309>/QuadHandle2' incorporates:
       *  Constant: '<S309>/Point50'
       *  RelationalOperator: '<S309>/LTEp25'
       *  Sum: '<S309>/p50mA'
       *  Switch: '<S309>/QuadHandle1'
       *  Switch: '<S315>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S309>/QuadHandle2' */

      /* Lookup_n-D: '<S308>/Look-Up Table' incorporates:
       *  Switch: '<S315>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S309>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S308>/Look-Up Table'
       *  Switch: '<S315>/SignCorrected'
       *  UnaryMinus: '<S309>/Negate'
       */
      if (rtDW->LTEp50_j) {
        rtDW->SignCorrected_a = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_a = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S309>/SignCorrected' */

      /* Product: '<S302>/Product4' incorporates:
       *  Inport: '<Root>/amplitude_b'
       *  Switch: '<S315>/SignCorrected'
       */
      rtDW->a = (real32_T)rtDW->SignCorrected_a * 9.31322575E-10F *
        rtU->amplitude_b;

      /* DataTypeConversion: '<S313>/CastU16En16' incorporates:
       *  Gain: '<S302>/Gain2'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/ordnung_c'
       *  Inport: '<Root>/phase_c'
       *  Product: '<S302>/Product10'
       *  Sum: '<S302>/Add8'
       */
      rtDW->CastU16En16_h = (uint32_T)((rtU->ordnung_c * rtU->Act_theta_u_el +
        rtU->phase_c) * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S313>/LTEp50' incorporates:
       *  DataTypeConversion: '<S313>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 2147483648U);

      /* Switch: '<S313>/QuadHandle1' incorporates:
       *  Constant: '<S313>/Point50'
       *  DataTypeConversion: '<S313>/CastU16En16'
       *  Sum: '<S313>/Amp50'
       */
      if (!rtDW->LTEp50_j) {
        rtDW->CastU16En16_h -= 2147483648U;
      }

      /* End of Switch: '<S313>/QuadHandle1' */

      /* Switch: '<S313>/QuadHandle2' incorporates:
       *  Constant: '<S313>/Point50'
       *  RelationalOperator: '<S313>/LTEp25'
       *  Sum: '<S313>/p50mA'
       *  Switch: '<S313>/QuadHandle1'
       *  Switch: '<S315>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S313>/QuadHandle2' */

      /* Lookup_n-D: '<S312>/Look-Up Table' incorporates:
       *  Switch: '<S315>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S313>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S312>/Look-Up Table'
       *  Switch: '<S315>/SignCorrected'
       *  UnaryMinus: '<S313>/Negate'
       */
      if (rtDW->LTEp50_j) {
        rtDW->SignCorrected_a = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_a = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S313>/SignCorrected' */

      /* Product: '<S302>/Product6' incorporates:
       *  Inport: '<Root>/amplitude_c'
       *  Switch: '<S315>/SignCorrected'
       */
      rtDW->b = (real32_T)rtDW->SignCorrected_a * 9.31322575E-10F *
        rtU->amplitude_c;

      /* DataTypeConversion: '<S315>/CastU16En16' incorporates:
       *  Gain: '<S302>/Gain3'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/ordnung_d'
       *  Inport: '<Root>/phase_d'
       *  Product: '<S302>/Product11'
       *  Sum: '<S302>/Add6'
       */
      rtDW->CastU16En16_h = (uint32_T)((rtU->ordnung_d * rtU->Act_theta_u_el +
        rtU->phase_d) * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S315>/LTEp50' incorporates:
       *  DataTypeConversion: '<S315>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 2147483648U);

      /* Switch: '<S315>/QuadHandle1' incorporates:
       *  Constant: '<S315>/Point50'
       *  DataTypeConversion: '<S315>/CastU16En16'
       *  Sum: '<S315>/Amp50'
       */
      if (!rtDW->LTEp50_j) {
        rtDW->CastU16En16_h -= 2147483648U;
      }

      /* End of Switch: '<S315>/QuadHandle1' */

      /* Switch: '<S315>/QuadHandle2' incorporates:
       *  Constant: '<S315>/Point50'
       *  RelationalOperator: '<S315>/LTEp25'
       *  Sum: '<S315>/p50mA'
       *  Switch: '<S315>/QuadHandle1'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S315>/QuadHandle2' */

      /* Lookup_n-D: '<S314>/Look-Up Table' incorporates:
       *  Switch: '<S315>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S315>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S314>/Look-Up Table'
       *  UnaryMinus: '<S315>/Negate'
       */
      if (rtDW->LTEp50_j) {
        rtDW->SignCorrected_a = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_a = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S315>/SignCorrected' */

      /* Sum: '<S302>/Add5' incorporates:
       *  Inport: '<Root>/amplitude_d'
       *  Product: '<S302>/Product5'
       *  Switch: '<S315>/SignCorrected'
       */
      rtDW->c = ((rtDW->c + rtDW->a) + rtDW->b) + (real32_T)
        rtDW->SignCorrected_a * 9.31322575E-10F * rtU->amplitude_d;

      /* End of Outputs for SubSystem: '<S11>/Rastmomentkompensation' */
    } else {
      /* Outputs for IfAction SubSystem: '<S11>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S303>/Action Port'
       */
      /* SignalConversion generated from: '<S303>/In1' incorporates:
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
       */
      Strangstromregler_asymetrisch(rtDW->I_re, rtDW->Add, rtU->Act_Iu,
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
      Strangstromregler_asymetrisch(rtDW->I_re, rtDW->Add, rtU->Act_Iv,
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
         *  Delay: '<S213>/Delay'
         *  Delay: '<S213>/Delay1'
         *  Delay: '<S214>/Delay'
         *  Delay: '<S214>/Delay1'
         *  Delay: '<S215>/Delay'
         *  Delay: '<S215>/Delay1'
         *  Delay: '<S216>/Delay'
         *  Delay: '<S216>/Delay1'
         *  Delay: '<S217>/Delay'
         *  Delay: '<S217>/Delay1'
         *  DiscreteIntegrator: '<S213>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S213>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S214>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S214>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S215>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S215>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S216>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S216>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S217>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S217>/Discrete-Time Integrator1'
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
      rtDW->theta_b = rtDW->c + -4.18879032F;

      /* Gain: '<S214>/Gain5' incorporates:
       *  Constant: '<S25>/Constant'
       *  Sum: '<S25>/Sum1'
       */
      rtDW->c = (rtDW->c + -4.18879032F) * 0.159154937F;

      /* DataTypeConversion: '<S256>/CastU16En16' */
      rtDW->CastU16En16_h = (uint32_T)(rtDW->c * 4.2949673E+9F);

      /* RelationalOperator: '<S256>/LTEp25' incorporates:
       *  DataTypeConversion: '<S256>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 1073741824U);

      /* RelationalOperator: '<S256>/GTEp75' incorporates:
       *  DataTypeConversion: '<S256>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h >= 3221225472U);

      /* Switch: '<S256>/QuadHandle2' incorporates:
       *  Constant: '<S256>/Point75'
       *  DataTypeConversion: '<S256>/CastU16En16'
       *  RelationalOperator: '<S256>/LTEp50'
       *  Sum: '<S256>/p75mA'
       *  Switch: '<S256>/QuadHandle1b'
       */
      if (rtDW->CastU16En16_h <= 2147483648U) {
        /* Switch: '<S256>/QuadHandle1a' incorporates:
         *  Constant: '<S256>/Point25'
         *  Sum: '<S256>/Amp25'
         *  Sum: '<S256>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->CastU16En16_h;
        } else {
          rtDW->CastU16En16_h -= 1073741824U;
        }

        /* End of Switch: '<S256>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S256>/QuadHandle1b' incorporates:
         *  Constant: '<S256>/Point75'
         *  Sum: '<S256>/Amp75'
         */
        rtDW->CastU16En16_h -= 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S256>/QuadHandle2' */

      /* Lookup_n-D: '<S255>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S256>/SignCorrected' incorporates:
       *  Logic: '<S256>/1st or 4th Quad'
       *  Lookup_n-D: '<S255>/Look-Up Table'
       *  UnaryMinus: '<S256>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_a = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_a = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S256>/SignCorrected' */

      /* DataTypeConversion: '<S258>/CastU16En16' incorporates:
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S226>/CastU16En16'
       *  Gain: '<S214>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Sum'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint32_T)((rtU->Act_theta_u_el +
        -4.18879032F) * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S258>/LTEp25' incorporates:
       *  DataTypeConversion: '<S258>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 1073741824U);

      /* RelationalOperator: '<S258>/GTEp75' incorporates:
       *  DataTypeConversion: '<S258>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 3221225472U);

      /* Switch: '<S258>/QuadHandle2' incorporates:
       *  Constant: '<S258>/Point75'
       *  DataTypeConversion: '<S258>/CastU16En16'
       *  RelationalOperator: '<S258>/LTEp50'
       *  Sum: '<S258>/p75mA'
       *  Switch: '<S258>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U) {
        /* Switch: '<S258>/QuadHandle1a' incorporates:
         *  Constant: '<S258>/Point25'
         *  Sum: '<S258>/Amp25'
         *  Sum: '<S258>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 1073741824U;
        }

        /* End of Switch: '<S258>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S258>/QuadHandle1b' incorporates:
         *  Constant: '<S258>/Point75'
         *  Sum: '<S258>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp_tmp;
      }

      /* End of Switch: '<S258>/QuadHandle2' */

      /* Lookup_n-D: '<S257>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S258>/SignCorrected' incorporates:
       *  Logic: '<S258>/1st or 4th Quad'
       *  Lookup_n-D: '<S257>/Look-Up Table'
       *  Switch: '<S299>/SignCorrected'
       *  UnaryMinus: '<S258>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S258>/SignCorrected' */

      /* MATLAB Function: '<S212>/MATLAB Function' incorporates:
       *  Inport: '<Root>/Act_w_el'
       *  Inport: '<Root>/Psi_PM_U'
       *  Inport: '<Root>/Psi_PM_V'
       *  Inport: '<Root>/Psi_PM_W'
       *  Inport: '<Root>/fl_enable_compensation_current'
       */
      MATLABFunction_i(rtU->Psi_PM_U, rtU->Psi_PM_V, rtU->Psi_PM_W, rtDW->I_re,
                       rtDW->Add, rtU->Act_w_el,
                       rtU->fl_enable_compensation_current, &rtDW->b,
                       &rtDW->Gain1, &rtDW->y_i, &rtDW->y, &rtDW->Switch2,
                       &rtDW->re_lim, &rtDW->sf_MATLABFunction_e);

      /* RelationalOperator: '<S226>/LTEp25' */
      rtDW->LTEp50_j = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 1073741824U);

      /* RelationalOperator: '<S226>/GTEp75' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 3221225472U);

      /* Switch: '<S226>/QuadHandle2' incorporates:
       *  Constant: '<S226>/Point75'
       *  RelationalOperator: '<S226>/LTEp50'
       *  Sum: '<S226>/p75mA'
       *  Switch: '<S226>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U) {
        /* Switch: '<S226>/QuadHandle1a' incorporates:
         *  Constant: '<S226>/Point25'
         *  Sum: '<S226>/Amp25'
         *  Sum: '<S226>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 1073741824U;
        }

        /* End of Switch: '<S226>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S226>/QuadHandle1b' incorporates:
         *  Constant: '<S226>/Point75'
         *  Sum: '<S226>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp_tmp;
      }

      /* End of Switch: '<S226>/QuadHandle2' */

      /* Lookup_n-D: '<S225>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S226>/SignCorrected' incorporates:
       *  Logic: '<S226>/1st or 4th Quad'
       *  Lookup_n-D: '<S225>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S226>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S226>/SignCorrected' */

      /* Product: '<S212>/Product' incorporates:
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Strom_kompensiert = (real32_T)rtDW->SignCorrected_d *
        9.31322575E-10F * rtDW->b;

      /* DataTypeConversion: '<S232>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S232>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U);

      /* Switch: '<S232>/QuadHandle1' incorporates:
       *  Constant: '<S232>/Point50'
       *  Sum: '<S232>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 2147483648U;
      }

      /* End of Switch: '<S232>/QuadHandle1' */

      /* Switch: '<S232>/QuadHandle2' incorporates:
       *  Constant: '<S232>/Point50'
       *  RelationalOperator: '<S232>/LTEp25'
       *  Sum: '<S232>/p50mA'
       *  Switch: '<S232>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S232>/QuadHandle2' */

      /* Lookup_n-D: '<S231>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S232>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S231>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S232>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S232>/SignCorrected' */

      /* Product: '<S212>/Product1' incorporates:
       *  Gain: '<S212>/Gain'
       *  Sum: '<S212>/Add'
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Delay1 = (real32_T)(-2147483648LL * rtDW->SignCorrected_d) *
        4.33680869E-19F * (rtDW->Merge + rtDW->Gain1);

      /* DataTypeConversion: '<S228>/CastU16En16' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S25>/Constant2'
       *  DataTypeConversion: '<S234>/CastU16En16'
       *  Gain: '<S212>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Add2'
       *  Sum: '<S25>/Sum'
       */
      rtDW->rtb_CastU16En16_h_tmp = (uint32_T)(((rtU->Act_theta_u_el +
        -4.18879032F) + -4.18879032F) * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S228>/LTEp25' incorporates:
       *  DataTypeConversion: '<S228>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->rtb_CastU16En16_h_tmp <= 1073741824U);

      /* RelationalOperator: '<S228>/GTEp75' incorporates:
       *  DataTypeConversion: '<S228>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp >= 3221225472U);

      /* Switch: '<S228>/QuadHandle2' incorporates:
       *  Constant: '<S228>/Point75'
       *  DataTypeConversion: '<S228>/CastU16En16'
       *  RelationalOperator: '<S228>/LTEp50'
       *  Sum: '<S228>/p75mA'
       *  Switch: '<S228>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U) {
        /* Switch: '<S228>/QuadHandle1a' incorporates:
         *  Constant: '<S228>/Point25'
         *  Sum: '<S228>/Amp25'
         *  Sum: '<S228>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 1073741824U;
        }

        /* End of Switch: '<S228>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S228>/QuadHandle1b' incorporates:
         *  Constant: '<S228>/Point75'
         *  Sum: '<S228>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp;
      }

      /* End of Switch: '<S228>/QuadHandle2' */

      /* Lookup_n-D: '<S227>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S228>/SignCorrected' incorporates:
       *  Logic: '<S228>/1st or 4th Quad'
       *  Lookup_n-D: '<S227>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S228>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S228>/SignCorrected' */

      /* Product: '<S212>/Product2' incorporates:
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)rtDW->SignCorrected_d * 9.31322575E-10F *
        rtDW->y_i;

      /* DataTypeConversion: '<S234>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp;

      /* RelationalOperator: '<S234>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U);

      /* Switch: '<S234>/QuadHandle1' incorporates:
       *  Constant: '<S234>/Point50'
       *  Sum: '<S234>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 2147483648U;
      }

      /* End of Switch: '<S234>/QuadHandle1' */

      /* Switch: '<S234>/QuadHandle2' incorporates:
       *  Constant: '<S234>/Point50'
       *  RelationalOperator: '<S234>/LTEp25'
       *  Sum: '<S234>/p50mA'
       *  Switch: '<S234>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S234>/QuadHandle2' */

      /* Lookup_n-D: '<S233>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S234>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S233>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S234>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S234>/SignCorrected' */

      /* Product: '<S212>/Product3' incorporates:
       *  Gain: '<S212>/Gain1'
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->im_lim_f = (real32_T)(-2147483648LL * rtDW->SignCorrected_d) *
        4.33680869E-19F * rtDW->y;

      /* DataTypeConversion: '<S230>/CastU16En16' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S25>/Constant3'
       *  DataTypeConversion: '<S236>/CastU16En16'
       *  Gain: '<S212>/Gain5'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Add3'
       *  Sum: '<S25>/Sum'
       */
      rtDW->rtb_CastU16En16_h_tmp = (uint32_T)(((rtU->Act_theta_u_el +
        -4.18879032F) + 4.18879032F) * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S230>/LTEp25' incorporates:
       *  DataTypeConversion: '<S230>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->rtb_CastU16En16_h_tmp <= 1073741824U);

      /* RelationalOperator: '<S230>/GTEp75' incorporates:
       *  DataTypeConversion: '<S230>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp >= 3221225472U);

      /* Switch: '<S230>/QuadHandle2' incorporates:
       *  Constant: '<S230>/Point75'
       *  DataTypeConversion: '<S230>/CastU16En16'
       *  RelationalOperator: '<S230>/LTEp50'
       *  Sum: '<S230>/p75mA'
       *  Switch: '<S230>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U) {
        /* Switch: '<S230>/QuadHandle1a' incorporates:
         *  Constant: '<S230>/Point25'
         *  Sum: '<S230>/Amp25'
         *  Sum: '<S230>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 1073741824U;
        }

        /* End of Switch: '<S230>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S230>/QuadHandle1b' incorporates:
         *  Constant: '<S230>/Point75'
         *  Sum: '<S230>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp;
      }

      /* End of Switch: '<S230>/QuadHandle2' */

      /* Lookup_n-D: '<S229>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S230>/SignCorrected' incorporates:
       *  Logic: '<S230>/1st or 4th Quad'
       *  Lookup_n-D: '<S229>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S230>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S230>/SignCorrected' */

      /* Product: '<S212>/Product4' incorporates:
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Product3 = (real32_T)rtDW->SignCorrected_d * 9.31322575E-10F *
        rtDW->Switch2;

      /* DataTypeConversion: '<S236>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp;

      /* RelationalOperator: '<S236>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U);

      /* Switch: '<S236>/QuadHandle1' incorporates:
       *  Constant: '<S236>/Point50'
       *  Sum: '<S236>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 2147483648U;
      }

      /* End of Switch: '<S236>/QuadHandle1' */

      /* Switch: '<S236>/QuadHandle2' incorporates:
       *  Constant: '<S236>/Point50'
       *  RelationalOperator: '<S236>/LTEp25'
       *  Sum: '<S236>/p50mA'
       *  Switch: '<S236>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S236>/QuadHandle2' */

      /* Lookup_n-D: '<S235>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S236>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S235>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S236>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S236>/SignCorrected' */

      /* Sum: '<S212>/Strom_kompensiert' incorporates:
       *  Gain: '<S212>/Gain2'
       *  Product: '<S212>/Product5'
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Strom_kompensiert = ((((rtDW->Strom_kompensiert + rtDW->Delay1) +
        rtDW->re_lim_e) + rtDW->im_lim_f) + rtDW->Product3) + (real32_T)
        (-2147483648LL * rtDW->SignCorrected_d) * 4.33680869E-19F * rtDW->re_lim;

      /* Sum: '<S25>/Sum2' incorporates:
       *  Inport: '<Root>/Act_Iw'
       */
      rtDW->Product3 = rtDW->Strom_kompensiert - rtU->Act_Iw;

      /* Gain: '<S214>/Gain6' incorporates:
       *  Gain: '<S215>/Gain6'
       *  Gain: '<S216>/Gain6'
       *  Gain: '<S217>/Gain6'
       */
      rtDW->Gain2_i = 10.0530977F * rtDW->Product3;

      /* Product: '<S214>/Product1' incorporates:
       *  Gain: '<S214>/Gain6'
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)rtDW->SignCorrected_c * 9.31322575E-10F *
        rtDW->Gain2_i;

      /* Gain: '<S214>/Gain1' incorporates:
       *  Delay: '<S214>/Delay1'
       *  Sum: '<S214>/Sum4'
       */
      rtDW->Gain1_k = (rtDW->Delay1_DSTATE + rtDW->re_lim_e) * 0.0138333309F;

      /* DiscreteIntegrator: '<S214>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_o = 0.5F * rtDW->Gain1_k +
        rtDW->DiscreteTimeIntegrator_DSTATE_o;

      /* Sum: '<S214>/Sum5' */
      rtDW->U_re = rtDW->DiscreteTimeIntegrator_o + rtDW->re_lim_e;

      /* MATLAB Function: '<S25>/MATLAB Function' incorporates:
       *  Inport: '<Root>/Act_w_el'
       */
      MATLABFunction(rtDW->Add, rtU->Act_w_el, &rtDW->LTEp50_j);

      /* DataTypeConversion: '<S260>/CastU16En16' incorporates:
       *  DataTypeConversion: '<S258>/CastU16En16'
       */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S260>/LTEp50' incorporates:
       *  DataTypeConversion: '<S258>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U);

      /* Switch: '<S260>/QuadHandle1' incorporates:
       *  Constant: '<S260>/Point50'
       *  DataTypeConversion: '<S258>/CastU16En16'
       *  Sum: '<S260>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 2147483648U;
      }

      /* End of Switch: '<S260>/QuadHandle1' */

      /* Switch: '<S260>/QuadHandle2' incorporates:
       *  Constant: '<S260>/Point50'
       *  RelationalOperator: '<S260>/LTEp25'
       *  Sum: '<S260>/p50mA'
       *  Switch: '<S260>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S260>/QuadHandle2' */

      /* Lookup_n-D: '<S259>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S260>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S259>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S260>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S260>/SignCorrected' */

      /* Product: '<S214>/Product' incorporates:
       *  Gain: '<S214>/Gain'
       *  Gain: '<S214>/Gain6'
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)(-2147483648LL * rtDW->SignCorrected_d) *
        4.33680869E-19F * rtDW->Gain2_i;

      /* Gain: '<S214>/Gain2' incorporates:
       *  Delay: '<S214>/Delay'
       *  Sum: '<S214>/Sum2'
       */
      rtDW->Add = (rtDW->re_lim_e + rtDW->Delay_DSTATE_l) * 0.0138333309F;

      /* DiscreteIntegrator: '<S214>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1 = 0.5F * rtDW->Add +
        rtDW->DiscreteTimeIntegrator1_DSTATE;

      /* Sum: '<S214>/Sum6' */
      rtDW->U_im = rtDW->re_lim_e + rtDW->DiscreteTimeIntegrator1;

      /* MATLAB Function: '<S214>/MATLAB Function' incorporates:
       *  Constant: '<S214>/Constant2'
       *  Product: '<S214>/Product6'
       */
      MATLABFunction_a(rtDW->U_re, 0.46F * rtDW->DiscreteTimeIntegrator,
                       rtDW->LTEp50_j, rtDW->U_im, &rtDW->y, &rtDW->y_i);

      /* DataTypeConversion: '<S262>/CastU16En16' */
      rtDW->CastU16En16_h = (uint32_T)(rtDW->c * 4.2949673E+9F);

      /* RelationalOperator: '<S262>/LTEp50' incorporates:
       *  DataTypeConversion: '<S262>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 2147483648U);

      /* Switch: '<S262>/QuadHandle1' incorporates:
       *  Constant: '<S262>/Point50'
       *  DataTypeConversion: '<S262>/CastU16En16'
       *  Sum: '<S262>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h -= 2147483648U;
      }

      /* End of Switch: '<S262>/QuadHandle1' */

      /* Switch: '<S262>/QuadHandle2' incorporates:
       *  Constant: '<S262>/Point50'
       *  RelationalOperator: '<S262>/LTEp25'
       *  Sum: '<S262>/p50mA'
       *  Switch: '<S262>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S262>/QuadHandle2' */

      /* Lookup_n-D: '<S261>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S262>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S261>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S262>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S262>/SignCorrected' */

      /* Sum: '<S214>/Sum' incorporates:
       *  Gain: '<S214>/Gain3'
       *  Product: '<S214>/Product2'
       *  Product: '<S214>/Product3'
       *  Switch: '<S256>/SignCorrected'
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Sum_cz = (real32_T)(-2147483648LL * rtDW->SignCorrected_d) *
        4.33680869E-19F * rtDW->y_i + (real32_T)rtDW->SignCorrected_a *
        9.31322575E-10F * rtDW->y;

      /* DataTypeConversion: '<S269>/CastU16En16' incorporates:
       *  Constant: '<S215>/Constant1'
       *  DataTypeConversion: '<S275>/CastU16En16'
       *  Gain: '<S215>/Gain5'
       *  Product: '<S215>/Product4'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint32_T)(rtDW->theta_b * 2.0F *
        0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S269>/LTEp25' incorporates:
       *  DataTypeConversion: '<S269>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 1073741824U);

      /* RelationalOperator: '<S269>/GTEp75' incorporates:
       *  DataTypeConversion: '<S269>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 3221225472U);

      /* Switch: '<S269>/QuadHandle2' incorporates:
       *  Constant: '<S269>/Point75'
       *  DataTypeConversion: '<S269>/CastU16En16'
       *  RelationalOperator: '<S269>/LTEp50'
       *  Sum: '<S269>/p75mA'
       *  Switch: '<S269>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U) {
        /* Switch: '<S269>/QuadHandle1a' incorporates:
         *  Constant: '<S269>/Point25'
         *  Sum: '<S269>/Amp25'
         *  Sum: '<S269>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 1073741824U;
        }

        /* End of Switch: '<S269>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S269>/QuadHandle1b' incorporates:
         *  Constant: '<S269>/Point75'
         *  Sum: '<S269>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp_tmp;
      }

      /* End of Switch: '<S269>/QuadHandle2' */

      /* Lookup_n-D: '<S268>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S269>/SignCorrected' incorporates:
       *  Logic: '<S269>/1st or 4th Quad'
       *  Lookup_n-D: '<S268>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S269>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S269>/SignCorrected' */

      /* DataTypeConversion: '<S271>/CastU16En16' incorporates:
       *  Constant: '<S215>/Constant1'
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S273>/CastU16En16'
       *  Gain: '<S215>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Product: '<S215>/Product5'
       *  Sum: '<S25>/Sum'
       */
      rtDW->rtb_CastU16En16_h_tmp = (uint32_T)((rtU->Act_theta_u_el +
        -4.18879032F) * 2.0F * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S271>/LTEp25' incorporates:
       *  DataTypeConversion: '<S271>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 1073741824U);

      /* RelationalOperator: '<S271>/GTEp75' incorporates:
       *  DataTypeConversion: '<S271>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp >= 3221225472U);

      /* Switch: '<S271>/QuadHandle2' incorporates:
       *  Constant: '<S271>/Point75'
       *  DataTypeConversion: '<S271>/CastU16En16'
       *  RelationalOperator: '<S271>/LTEp50'
       *  Sum: '<S271>/p75mA'
       *  Switch: '<S271>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U) {
        /* Switch: '<S271>/QuadHandle1a' incorporates:
         *  Constant: '<S271>/Point25'
         *  Sum: '<S271>/Amp25'
         *  Sum: '<S271>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 1073741824U;
        }

        /* End of Switch: '<S271>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S271>/QuadHandle1b' incorporates:
         *  Constant: '<S271>/Point75'
         *  Sum: '<S271>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp;
      }

      /* End of Switch: '<S271>/QuadHandle2' */

      /* Lookup_n-D: '<S270>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S271>/SignCorrected' incorporates:
       *  Logic: '<S271>/1st or 4th Quad'
       *  Lookup_n-D: '<S270>/Look-Up Table'
       *  Switch: '<S299>/SignCorrected'
       *  UnaryMinus: '<S271>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S271>/SignCorrected' */

      /* Product: '<S215>/Product1' incorporates:
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->Delay1 = (real32_T)rtDW->SignCorrected_c * 9.31322575E-10F *
        rtDW->Gain2_i;

      /* Gain: '<S215>/Gain1' incorporates:
       *  Delay: '<S215>/Delay1'
       *  Sum: '<S215>/Sum4'
       */
      rtDW->Gain1_e = (rtDW->Delay1_DSTATE_o + rtDW->Delay1) * 0.00138333312F;

      /* DiscreteIntegrator: '<S215>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_k = 0.5F * rtDW->Gain1_e +
        rtDW->DiscreteTimeIntegrator_DSTATE_m;

      /* Sum: '<S215>/Sum5' */
      rtDW->U_re_c = rtDW->DiscreteTimeIntegrator_k + rtDW->Delay1;

      /* DataTypeConversion: '<S273>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp;

      /* RelationalOperator: '<S273>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U);

      /* Switch: '<S273>/QuadHandle1' incorporates:
       *  Constant: '<S273>/Point50'
       *  Sum: '<S273>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 2147483648U;
      }

      /* End of Switch: '<S273>/QuadHandle1' */

      /* Switch: '<S273>/QuadHandle2' incorporates:
       *  Constant: '<S273>/Point50'
       *  RelationalOperator: '<S273>/LTEp25'
       *  Sum: '<S273>/p50mA'
       *  Switch: '<S273>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S273>/QuadHandle2' */

      /* Lookup_n-D: '<S272>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S273>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S272>/Look-Up Table'
       *  Switch: '<S299>/SignCorrected'
       *  UnaryMinus: '<S273>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S273>/SignCorrected' */

      /* Product: '<S215>/Product' incorporates:
       *  Gain: '<S215>/Gain'
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)(-2147483648LL * rtDW->SignCorrected_c) *
        4.33680869E-19F * rtDW->Gain2_i;

      /* Gain: '<S215>/Gain2' incorporates:
       *  Delay: '<S215>/Delay'
       *  Sum: '<S215>/Sum2'
       */
      rtDW->Gain2_n = (rtDW->re_lim_e + rtDW->Delay_DSTATE_nv) * 0.00138333312F;

      /* DiscreteIntegrator: '<S215>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_e = 0.5F * rtDW->Gain2_n +
        rtDW->DiscreteTimeIntegrator1_DSTAT_f;

      /* Sum: '<S215>/Sum6' */
      rtDW->U_im_k = rtDW->re_lim_e + rtDW->DiscreteTimeIntegrator1_e;

      /* MATLAB Function: '<S215>/MATLAB Function' incorporates:
       *  Constant: '<S215>/Constant2'
       *  Product: '<S215>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_c, 0.05F * rtDW->DiscreteTimeIntegrator,
                       rtDW->LTEp50_j, rtDW->U_im_k, &rtDW->re_lim,
                       &rtDW->Switch2);

      /* Product: '<S215>/Product3' incorporates:
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)rtDW->SignCorrected_d * 9.31322575E-10F *
        rtDW->re_lim;

      /* DataTypeConversion: '<S275>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S275>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U);

      /* Switch: '<S275>/QuadHandle1' incorporates:
       *  Constant: '<S275>/Point50'
       *  Sum: '<S275>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 2147483648U;
      }

      /* End of Switch: '<S275>/QuadHandle1' */

      /* Switch: '<S275>/QuadHandle2' incorporates:
       *  Constant: '<S275>/Point50'
       *  RelationalOperator: '<S275>/LTEp25'
       *  Sum: '<S275>/p50mA'
       *  Switch: '<S275>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S275>/QuadHandle2' */

      /* Lookup_n-D: '<S274>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S275>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S274>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S275>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S275>/SignCorrected' */

      /* Sum: '<S215>/Sum' incorporates:
       *  Gain: '<S215>/Gain3'
       *  Product: '<S215>/Product2'
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Sum_a = (real32_T)(-2147483648LL * rtDW->SignCorrected_d) *
        4.33680869E-19F * rtDW->Switch2 + rtDW->re_lim_e;

      /* DataTypeConversion: '<S243>/CastU16En16' incorporates:
       *  Constant: '<S213>/Constant1'
       *  DataTypeConversion: '<S249>/CastU16En16'
       *  Gain: '<S213>/Gain6'
       *  Product: '<S213>/Product4'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint32_T)(rtDW->theta_b * 3.0F *
        0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S243>/LTEp25' incorporates:
       *  DataTypeConversion: '<S243>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 1073741824U);

      /* RelationalOperator: '<S243>/GTEp75' incorporates:
       *  DataTypeConversion: '<S243>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 3221225472U);

      /* Switch: '<S243>/QuadHandle2' incorporates:
       *  Constant: '<S243>/Point75'
       *  DataTypeConversion: '<S243>/CastU16En16'
       *  RelationalOperator: '<S243>/LTEp50'
       *  Sum: '<S243>/p75mA'
       *  Switch: '<S243>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U) {
        /* Switch: '<S243>/QuadHandle1a' incorporates:
         *  Constant: '<S243>/Point25'
         *  Sum: '<S243>/Amp25'
         *  Sum: '<S243>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 1073741824U;
        }

        /* End of Switch: '<S243>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S243>/QuadHandle1b' incorporates:
         *  Constant: '<S243>/Point75'
         *  Sum: '<S243>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp_tmp;
      }

      /* End of Switch: '<S243>/QuadHandle2' */

      /* Lookup_n-D: '<S242>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S243>/SignCorrected' incorporates:
       *  Logic: '<S243>/1st or 4th Quad'
       *  Lookup_n-D: '<S242>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S243>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S243>/SignCorrected' */

      /* DataTypeConversion: '<S245>/CastU16En16' incorporates:
       *  Constant: '<S213>/Constant1'
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S247>/CastU16En16'
       *  Gain: '<S213>/Gain5'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Product: '<S213>/Product5'
       *  Sum: '<S25>/Sum'
       */
      rtDW->rtb_CastU16En16_h_tmp = (uint32_T)((rtU->Act_theta_u_el +
        -4.18879032F) * 3.0F * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S245>/LTEp25' incorporates:
       *  DataTypeConversion: '<S245>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 1073741824U);

      /* RelationalOperator: '<S245>/GTEp75' incorporates:
       *  DataTypeConversion: '<S245>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp >= 3221225472U);

      /* Switch: '<S245>/QuadHandle2' incorporates:
       *  Constant: '<S245>/Point75'
       *  DataTypeConversion: '<S245>/CastU16En16'
       *  RelationalOperator: '<S245>/LTEp50'
       *  Sum: '<S245>/p75mA'
       *  Switch: '<S245>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U) {
        /* Switch: '<S245>/QuadHandle1a' incorporates:
         *  Constant: '<S245>/Point25'
         *  Sum: '<S245>/Amp25'
         *  Sum: '<S245>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 1073741824U;
        }

        /* End of Switch: '<S245>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S245>/QuadHandle1b' incorporates:
         *  Constant: '<S245>/Point75'
         *  Sum: '<S245>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp;
      }

      /* End of Switch: '<S245>/QuadHandle2' */

      /* Lookup_n-D: '<S244>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S245>/SignCorrected' incorporates:
       *  Logic: '<S245>/1st or 4th Quad'
       *  Lookup_n-D: '<S244>/Look-Up Table'
       *  Switch: '<S299>/SignCorrected'
       *  UnaryMinus: '<S245>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S245>/SignCorrected' */

      /* Gain: '<S213>/Gain4' */
      rtDW->Delay1 = 55.3333244F * rtDW->Product3;

      /* Gain: '<S213>/Gain1' incorporates:
       *  Delay: '<S213>/Delay1'
       *  Product: '<S213>/Product1'
       *  Sum: '<S213>/Sum4'
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->Gain1_d = ((real32_T)rtDW->SignCorrected_c * 9.31322575E-10F *
                       rtDW->Delay1 + rtDW->Delay1_DSTATE_d) * 2.5E-5F;

      /* DiscreteIntegrator: '<S213>/Discrete-Time Integrator' */
      rtDW->U_re_m = 0.5F * rtDW->Gain1_d +
        rtDW->DiscreteTimeIntegrator_DSTAT_om;

      /* DataTypeConversion: '<S247>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp;

      /* RelationalOperator: '<S247>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U);

      /* Switch: '<S247>/QuadHandle1' incorporates:
       *  Constant: '<S247>/Point50'
       *  Sum: '<S247>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 2147483648U;
      }

      /* End of Switch: '<S247>/QuadHandle1' */

      /* Switch: '<S247>/QuadHandle2' incorporates:
       *  Constant: '<S247>/Point50'
       *  RelationalOperator: '<S247>/LTEp25'
       *  Sum: '<S247>/p50mA'
       *  Switch: '<S247>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S247>/QuadHandle2' */

      /* Lookup_n-D: '<S246>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S247>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S246>/Look-Up Table'
       *  Switch: '<S299>/SignCorrected'
       *  UnaryMinus: '<S247>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S247>/SignCorrected' */

      /* Gain: '<S213>/Gain2' incorporates:
       *  Delay: '<S213>/Delay'
       *  Gain: '<S213>/Gain'
       *  Product: '<S213>/Product'
       *  Sum: '<S213>/Sum2'
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->Gain2_c = ((real32_T)(-2147483648LL * rtDW->SignCorrected_c) *
                       4.33680869E-19F * rtDW->Delay1 + rtDW->Delay_DSTATE_j) *
        2.5E-5F;

      /* DiscreteIntegrator: '<S213>/Discrete-Time Integrator1' */
      rtDW->U_im_cl = 0.5F * rtDW->Gain2_c +
        rtDW->DiscreteTimeIntegrator1_DSTAT_a;

      /* MATLAB Function: '<S213>/MATLAB Function' incorporates:
       *  Constant: '<S213>/Constant'
       *  Product: '<S213>/Product6'
       */
      MATLABFunction_c(rtDW->U_re_m, 0.15F * rtDW->DiscreteTimeIntegrator,
                       rtDW->U_im_cl, &rtDW->Gain1, &rtDW->b);

      /* Product: '<S213>/Product3' incorporates:
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)rtDW->SignCorrected_d * 9.31322575E-10F *
        rtDW->Gain1;

      /* DataTypeConversion: '<S249>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S249>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U);

      /* Switch: '<S249>/QuadHandle1' incorporates:
       *  Constant: '<S249>/Point50'
       *  Sum: '<S249>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 2147483648U;
      }

      /* End of Switch: '<S249>/QuadHandle1' */

      /* Switch: '<S249>/QuadHandle2' incorporates:
       *  Constant: '<S249>/Point50'
       *  RelationalOperator: '<S249>/LTEp25'
       *  Sum: '<S249>/p50mA'
       *  Switch: '<S249>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S249>/QuadHandle2' */

      /* Lookup_n-D: '<S248>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S249>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S248>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S249>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S249>/SignCorrected' */

      /* Sum: '<S213>/Sum' incorporates:
       *  Gain: '<S213>/Gain3'
       *  Product: '<S213>/Product2'
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Sum_pq = (real32_T)(-2147483648LL * rtDW->SignCorrected_d) *
        4.33680869E-19F * rtDW->b + rtDW->re_lim_e;

      /* DataTypeConversion: '<S282>/CastU16En16' incorporates:
       *  Constant: '<S216>/Constant1'
       *  DataTypeConversion: '<S288>/CastU16En16'
       *  Gain: '<S216>/Gain5'
       *  Product: '<S216>/Product4'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint32_T)(rtDW->theta_b * 4.0F *
        0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S282>/LTEp25' incorporates:
       *  DataTypeConversion: '<S282>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 1073741824U);

      /* RelationalOperator: '<S282>/GTEp75' incorporates:
       *  DataTypeConversion: '<S282>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 3221225472U);

      /* Switch: '<S282>/QuadHandle2' incorporates:
       *  Constant: '<S282>/Point75'
       *  DataTypeConversion: '<S282>/CastU16En16'
       *  RelationalOperator: '<S282>/LTEp50'
       *  Sum: '<S282>/p75mA'
       *  Switch: '<S282>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U) {
        /* Switch: '<S282>/QuadHandle1a' incorporates:
         *  Constant: '<S282>/Point25'
         *  Sum: '<S282>/Amp25'
         *  Sum: '<S282>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 1073741824U;
        }

        /* End of Switch: '<S282>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S282>/QuadHandle1b' incorporates:
         *  Constant: '<S282>/Point75'
         *  Sum: '<S282>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp_tmp;
      }

      /* End of Switch: '<S282>/QuadHandle2' */

      /* Lookup_n-D: '<S281>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S282>/SignCorrected' incorporates:
       *  Logic: '<S282>/1st or 4th Quad'
       *  Lookup_n-D: '<S281>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S282>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S282>/SignCorrected' */

      /* DataTypeConversion: '<S284>/CastU16En16' incorporates:
       *  Constant: '<S216>/Constant1'
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S286>/CastU16En16'
       *  Gain: '<S216>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Product: '<S216>/Product5'
       *  Sum: '<S25>/Sum'
       */
      rtDW->rtb_CastU16En16_h_tmp = (uint32_T)((rtU->Act_theta_u_el +
        -4.18879032F) * 4.0F * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S284>/LTEp25' incorporates:
       *  DataTypeConversion: '<S284>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 1073741824U);

      /* RelationalOperator: '<S284>/GTEp75' incorporates:
       *  DataTypeConversion: '<S284>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp >= 3221225472U);

      /* Switch: '<S284>/QuadHandle2' incorporates:
       *  Constant: '<S284>/Point75'
       *  DataTypeConversion: '<S284>/CastU16En16'
       *  RelationalOperator: '<S284>/LTEp50'
       *  Sum: '<S284>/p75mA'
       *  Switch: '<S284>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U) {
        /* Switch: '<S284>/QuadHandle1a' incorporates:
         *  Constant: '<S284>/Point25'
         *  Sum: '<S284>/Amp25'
         *  Sum: '<S284>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 1073741824U;
        }

        /* End of Switch: '<S284>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S284>/QuadHandle1b' incorporates:
         *  Constant: '<S284>/Point75'
         *  Sum: '<S284>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp;
      }

      /* End of Switch: '<S284>/QuadHandle2' */

      /* Lookup_n-D: '<S283>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S284>/SignCorrected' incorporates:
       *  Logic: '<S284>/1st or 4th Quad'
       *  Lookup_n-D: '<S283>/Look-Up Table'
       *  Switch: '<S299>/SignCorrected'
       *  UnaryMinus: '<S284>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S284>/SignCorrected' */

      /* Product: '<S216>/Product1' incorporates:
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->Delay1 = (real32_T)rtDW->SignCorrected_c * 9.31322575E-10F *
        rtDW->Gain2_i;

      /* Delay: '<S216>/Delay1' */
      rtDW->a = rtDW->Delay1_DSTATE_g;

      /* Gain: '<S216>/Gain1' incorporates:
       *  Delay: '<S216>/Delay1'
       *  Sum: '<S216>/Sum4'
       */
      rtDW->Gain1_m = (rtDW->Delay1_DSTATE_g + rtDW->Delay1) * 0.00138333312F;

      /* DiscreteIntegrator: '<S216>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_a = 0.5F * rtDW->Gain1_m +
        rtDW->DiscreteTimeIntegrator_DSTATE_c;

      /* Sum: '<S216>/Sum5' */
      rtDW->Delay1 += rtDW->DiscreteTimeIntegrator_a;

      /* DataTypeConversion: '<S286>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp;

      /* RelationalOperator: '<S286>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U);

      /* Switch: '<S286>/QuadHandle1' incorporates:
       *  Constant: '<S286>/Point50'
       *  Sum: '<S286>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 2147483648U;
      }

      /* End of Switch: '<S286>/QuadHandle1' */

      /* Switch: '<S286>/QuadHandle2' incorporates:
       *  Constant: '<S286>/Point50'
       *  RelationalOperator: '<S286>/LTEp25'
       *  Sum: '<S286>/p50mA'
       *  Switch: '<S286>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S286>/QuadHandle2' */

      /* Lookup_n-D: '<S285>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S286>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S285>/Look-Up Table'
       *  Switch: '<S299>/SignCorrected'
       *  UnaryMinus: '<S286>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S286>/SignCorrected' */

      /* Product: '<S216>/Product' incorporates:
       *  Gain: '<S216>/Gain'
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)(-2147483648LL * rtDW->SignCorrected_c) *
        4.33680869E-19F * rtDW->Gain2_i;

      /* Gain: '<S216>/Gain2' incorporates:
       *  Delay: '<S216>/Delay'
       *  Sum: '<S216>/Sum2'
       */
      rtDW->Gain2_h = (rtDW->re_lim_e + rtDW->Delay_DSTATE_a) * 0.00138333312F;

      /* DiscreteIntegrator: '<S216>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_a = 0.5F * rtDW->Gain2_h +
        rtDW->DiscreteTimeIntegrator1_DSTAT_o;

      /* Sum: '<S216>/Sum6' */
      rtDW->U_im_p = rtDW->re_lim_e + rtDW->DiscreteTimeIntegrator1_a;

      /* MATLAB Function: '<S216>/MATLAB Function' incorporates:
       *  Constant: '<S216>/Constant2'
       *  Product: '<S216>/Product6'
       */
      MATLABFunction_a(rtDW->Delay1, 0.025F * rtDW->DiscreteTimeIntegrator,
                       rtDW->LTEp50_j, rtDW->U_im_p, &rtDW->a, &rtDW->c);

      /* Product: '<S216>/Product3' incorporates:
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)rtDW->SignCorrected_d * 9.31322575E-10F *
        rtDW->a;

      /* DataTypeConversion: '<S288>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S288>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U);

      /* Switch: '<S288>/QuadHandle1' incorporates:
       *  Constant: '<S288>/Point50'
       *  Sum: '<S288>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 2147483648U;
      }

      /* End of Switch: '<S288>/QuadHandle1' */

      /* Switch: '<S288>/QuadHandle2' incorporates:
       *  Constant: '<S288>/Point50'
       *  RelationalOperator: '<S288>/LTEp25'
       *  Sum: '<S288>/p50mA'
       *  Switch: '<S288>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S288>/QuadHandle2' */

      /* Lookup_n-D: '<S287>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S288>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S287>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S288>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S288>/SignCorrected' */

      /* Sum: '<S216>/Sum' incorporates:
       *  Gain: '<S216>/Gain3'
       *  Product: '<S216>/Product2'
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Sum_cr = (real32_T)(-2147483648LL * rtDW->SignCorrected_d) *
        4.33680869E-19F * rtDW->c + rtDW->re_lim_e;

      /* DataTypeConversion: '<S295>/CastU16En16' incorporates:
       *  Constant: '<S217>/Constant1'
       *  DataTypeConversion: '<S301>/CastU16En16'
       *  Gain: '<S217>/Gain5'
       *  Product: '<S217>/Product4'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint32_T)(rtDW->theta_b * 6.0F *
        0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S295>/LTEp25' incorporates:
       *  DataTypeConversion: '<S295>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 1073741824U);

      /* RelationalOperator: '<S295>/GTEp75' incorporates:
       *  DataTypeConversion: '<S295>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 3221225472U);

      /* Switch: '<S295>/QuadHandle2' incorporates:
       *  Constant: '<S295>/Point75'
       *  DataTypeConversion: '<S295>/CastU16En16'
       *  RelationalOperator: '<S295>/LTEp50'
       *  Sum: '<S295>/p75mA'
       *  Switch: '<S295>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U) {
        /* Switch: '<S295>/QuadHandle1a' incorporates:
         *  Constant: '<S295>/Point25'
         *  Sum: '<S295>/Amp25'
         *  Sum: '<S295>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 1073741824U;
        }

        /* End of Switch: '<S295>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S295>/QuadHandle1b' incorporates:
         *  Constant: '<S295>/Point75'
         *  Sum: '<S295>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp_tmp;
      }

      /* End of Switch: '<S295>/QuadHandle2' */

      /* Lookup_n-D: '<S294>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S295>/SignCorrected' incorporates:
       *  Logic: '<S295>/1st or 4th Quad'
       *  Lookup_n-D: '<S294>/Look-Up Table'
       *  Switch: '<S301>/SignCorrected'
       *  UnaryMinus: '<S295>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S295>/SignCorrected' */

      /* DataTypeConversion: '<S297>/CastU16En16' incorporates:
       *  Constant: '<S217>/Constant1'
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S299>/CastU16En16'
       *  Gain: '<S217>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Product: '<S217>/Product5'
       *  Sum: '<S25>/Sum'
       */
      rtDW->rtb_CastU16En16_h_tmp = (uint32_T)((rtU->Act_theta_u_el +
        -4.18879032F) * 6.0F * 0.159154937F * 4.2949673E+9F);

      /* RelationalOperator: '<S297>/LTEp25' incorporates:
       *  DataTypeConversion: '<S297>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 1073741824U);

      /* RelationalOperator: '<S297>/GTEp75' incorporates:
       *  DataTypeConversion: '<S297>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp >= 3221225472U);

      /* Switch: '<S297>/QuadHandle2' incorporates:
       *  Constant: '<S297>/Point75'
       *  DataTypeConversion: '<S297>/CastU16En16'
       *  RelationalOperator: '<S297>/LTEp50'
       *  Sum: '<S297>/p75mA'
       *  Switch: '<S297>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U) {
        /* Switch: '<S297>/QuadHandle1a' incorporates:
         *  Constant: '<S297>/Point25'
         *  Sum: '<S297>/Amp25'
         *  Sum: '<S297>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = 1073741824U - rtDW->rtb_CastU16En16_h_tmp;
        } else {
          rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 1073741824U;
        }

        /* End of Switch: '<S297>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S297>/QuadHandle1b' incorporates:
         *  Constant: '<S297>/Point75'
         *  Sum: '<S297>/Amp75'
         */
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 3221225472U;
      } else {
        rtDW->CastU16En16_h = 3221225472U - rtDW->rtb_CastU16En16_h_tmp;
      }

      /* End of Switch: '<S297>/QuadHandle2' */

      /* Lookup_n-D: '<S296>/Look-Up Table' */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S297>/SignCorrected' incorporates:
       *  Logic: '<S297>/1st or 4th Quad'
       *  Lookup_n-D: '<S296>/Look-Up Table'
       *  Switch: '<S299>/SignCorrected'
       *  UnaryMinus: '<S297>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S297>/SignCorrected' */

      /* Product: '<S217>/Product1' incorporates:
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->im_lim_f = (real32_T)rtDW->SignCorrected_c * 9.31322575E-10F *
        rtDW->Gain2_i;

      /* Gain: '<S217>/Gain1' incorporates:
       *  Delay: '<S217>/Delay1'
       *  Sum: '<S217>/Sum4'
       */
      rtDW->theta_b = (rtDW->Delay1_DSTATE_oi + rtDW->im_lim_f) * 0.00138333312F;

      /* DiscreteIntegrator: '<S217>/Discrete-Time Integrator' */
      rtDW->theta_m = 0.5F * rtDW->theta_b +
        rtDW->DiscreteTimeIntegrator_DSTATE_g;

      /* Sum: '<S217>/Sum5' */
      rtDW->U_re_d = rtDW->theta_m + rtDW->im_lim_f;

      /* DataTypeConversion: '<S299>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp;

      /* RelationalOperator: '<S299>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp <= 2147483648U);

      /* Switch: '<S299>/QuadHandle1' incorporates:
       *  Constant: '<S299>/Point50'
       *  Sum: '<S299>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp - 2147483648U;
      }

      /* End of Switch: '<S299>/QuadHandle1' */

      /* Switch: '<S299>/QuadHandle2' incorporates:
       *  Constant: '<S299>/Point50'
       *  RelationalOperator: '<S299>/LTEp25'
       *  Sum: '<S299>/p50mA'
       *  Switch: '<S299>/QuadHandle1'
       *  Switch: '<S301>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S299>/QuadHandle2' */

      /* Lookup_n-D: '<S298>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S299>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S298>/Look-Up Table'
       *  UnaryMinus: '<S299>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_c = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S299>/SignCorrected' */

      /* Product: '<S217>/Product' incorporates:
       *  Gain: '<S217>/Gain'
       *  Switch: '<S299>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)(-2147483648LL * rtDW->SignCorrected_c) *
        4.33680869E-19F * rtDW->Gain2_i;

      /* Gain: '<S217>/Gain2' incorporates:
       *  Delay: '<S217>/Delay'
       *  Sum: '<S217>/Sum2'
       */
      rtDW->Gain2_i = (rtDW->re_lim_e + rtDW->Delay_DSTATE_nm) * 0.00138333312F;

      /* DiscreteIntegrator: '<S217>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_g = 0.5F * rtDW->Gain2_i +
        rtDW->DiscreteTimeIntegrator1_DSTA_os;

      /* Sum: '<S217>/Sum6' */
      rtDW->U_im_c = rtDW->re_lim_e + rtDW->DiscreteTimeIntegrator1_g;

      /* MATLAB Function: '<S217>/MATLAB Function' incorporates:
       *  Constant: '<S217>/Constant2'
       *  Product: '<S217>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_d, 0.01F * rtDW->DiscreteTimeIntegrator,
                       rtDW->LTEp50_j, rtDW->U_im_c, &rtDW->re_lim_e,
                       &rtDW->im_lim_f);

      /* Product: '<S217>/Product3' incorporates:
       *  Switch: '<S301>/SignCorrected'
       */
      rtDW->Product3 = (real32_T)rtDW->SignCorrected_d * 9.31322575E-10F *
        rtDW->re_lim_e;

      /* DataTypeConversion: '<S301>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S301>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 2147483648U);

      /* Switch: '<S301>/QuadHandle1' incorporates:
       *  Constant: '<S301>/Point50'
       *  Sum: '<S301>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp - 2147483648U;
      }

      /* End of Switch: '<S301>/QuadHandle1' */

      /* Switch: '<S301>/QuadHandle2' incorporates:
       *  Constant: '<S301>/Point50'
       *  RelationalOperator: '<S301>/LTEp25'
       *  Sum: '<S301>/p50mA'
       *  Switch: '<S301>/QuadHandle1'
       */
      if (rtDW->CastU16En16_h > 1073741824U) {
        rtDW->CastU16En16_h = 2147483648U - rtDW->CastU16En16_h;
      }

      /* End of Switch: '<S301>/QuadHandle2' */

      /* Lookup_n-D: '<S300>/Look-Up Table' incorporates:
       *  Switch: '<S301>/QuadHandle2'
       */
      rtDW->CastU16En16_h = plook_u32u32u64n32_even20c_gf(rtDW->CastU16En16_h,
        0U, 1024U, &rtDW->frac);

      /* Switch: '<S301>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S300>/Look-Up Table'
       *  UnaryMinus: '<S301>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      } else {
        rtDW->SignCorrected_d = -intrp1d_s32s64s64u32u64n32l_f
          (rtDW->CastU16En16_h, rtDW->frac, rtConstP.pooled3);
      }

      /* End of Switch: '<S301>/SignCorrected' */

      /* Outport: '<Root>/a_W' incorporates:
       *  Constant: '<S25>/Constant1'
       *  Gain: '<S217>/Gain3'
       *  Product: '<S217>/Product2'
       *  Product: '<S25>/Divide'
       *  Sum: '<S217>/Sum'
       *  Sum: '<S25>/Add'
       *  Sum: '<S25>/Add1'
       *  Switch: '<S301>/SignCorrected'
       */
      rtY->a_W = (((real32_T)(-2147483648LL * rtDW->SignCorrected_d) *
                   4.33680869E-19F * rtDW->im_lim_f + rtDW->Product3) +
                  (((rtDW->Sum_cz + rtDW->Sum_a) + rtDW->Sum_pq) + rtDW->Sum_cr))
        / rtDW->DiscreteTimeIntegrator + 0.5F;

      /* Merge: '<S10>/Merge5' incorporates:
       *  SignalConversion generated from: '<S25>/I_ref1'
       */
      rtDW->Merge5 = rtDW->Strom_kompensiert;

      /* Update for Delay: '<S214>/Delay1' incorporates:
       *  Sum: '<S214>/Sum3'
       */
      rtDW->Delay1_DSTATE = rtDW->y - rtDW->U_re;

      /* Update for DiscreteIntegrator: '<S214>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.5F * rtDW->Gain1_k +
        rtDW->DiscreteTimeIntegrator_o;

      /* Update for Delay: '<S214>/Delay' incorporates:
       *  Sum: '<S214>/Sum1'
       */
      rtDW->Delay_DSTATE_l = rtDW->y_i - rtDW->U_im;

      /* Update for DiscreteIntegrator: '<S214>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTATE = 0.5F * rtDW->Add +
        rtDW->DiscreteTimeIntegrator1;

      /* Update for Delay: '<S215>/Delay1' incorporates:
       *  Sum: '<S215>/Sum3'
       */
      rtDW->Delay1_DSTATE_o = rtDW->re_lim - rtDW->U_re_c;

      /* Update for DiscreteIntegrator: '<S215>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.5F * rtDW->Gain1_e +
        rtDW->DiscreteTimeIntegrator_k;

      /* Update for Delay: '<S215>/Delay' incorporates:
       *  Sum: '<S215>/Sum1'
       */
      rtDW->Delay_DSTATE_nv = rtDW->Switch2 - rtDW->U_im_k;

      /* Update for DiscreteIntegrator: '<S215>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.5F * rtDW->Gain2_n +
        rtDW->DiscreteTimeIntegrator1_e;

      /* Update for Delay: '<S213>/Delay1' incorporates:
       *  Sum: '<S213>/Sum3'
       */
      rtDW->Delay1_DSTATE_d = rtDW->Gain1 - rtDW->U_re_m;

      /* Update for DiscreteIntegrator: '<S213>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTAT_om = 0.5F * rtDW->Gain1_d +
        rtDW->U_re_m;

      /* Update for Delay: '<S213>/Delay' incorporates:
       *  Sum: '<S213>/Sum1'
       */
      rtDW->Delay_DSTATE_j = rtDW->b - rtDW->U_im_cl;

      /* Update for DiscreteIntegrator: '<S213>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_a = 0.5F * rtDW->Gain2_c +
        rtDW->U_im_cl;

      /* Update for Delay: '<S216>/Delay1' incorporates:
       *  Sum: '<S216>/Sum3'
       */
      rtDW->Delay1_DSTATE_g = rtDW->a - rtDW->Delay1;

      /* Update for DiscreteIntegrator: '<S216>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.5F * rtDW->Gain1_m +
        rtDW->DiscreteTimeIntegrator_a;

      /* Update for Delay: '<S216>/Delay' incorporates:
       *  Sum: '<S216>/Sum1'
       */
      rtDW->Delay_DSTATE_a = rtDW->c - rtDW->U_im_p;

      /* Update for DiscreteIntegrator: '<S216>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.5F * rtDW->Gain2_h +
        rtDW->DiscreteTimeIntegrator1_a;

      /* Update for Delay: '<S217>/Delay1' incorporates:
       *  Sum: '<S217>/Sum3'
       */
      rtDW->Delay1_DSTATE_oi = rtDW->re_lim_e - rtDW->U_re_d;

      /* Update for DiscreteIntegrator: '<S217>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.5F * rtDW->theta_b +
        rtDW->theta_m;

      /* Update for Delay: '<S217>/Delay' incorporates:
       *  Sum: '<S217>/Sum1'
       */
      rtDW->Delay_DSTATE_nm = rtDW->im_lim_f - rtDW->U_im_c;

      /* Update for DiscreteIntegrator: '<S217>/Discrete-Time Integrator1' */
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
  rtY->fault_peak_current_u = (fabsf(rtU->Act_Iu) >= 50.0F);

  /* Math: '<S5>/Square' incorporates:
   *  Inport: '<Root>/Act_Iu'
   */
  rtDW->c = rtU->Act_Iu * rtU->Act_Iu;

  /* DiscreteIntegrator: '<S316>/Accumulator' incorporates:
   *  Delay: '<S316>/Delay'
   *  Sum: '<S316>/Sum'
   */
  rtDW->a = (rtDW->c - rtDW->Delay_DSTATE_k[0]) + rtDW->Accumulator_DSTATE;

  /* Outport: '<Root>/fault_rms_current_u' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Gain: '<S316>/Gain'
   *  RelationalOperator: '<S5>/Smaller1'
   *  Sqrt: '<S5>/Square Root'
   */
  rtY->fault_rms_current_u = (sqrtf(0.05F * rtDW->a) >= 50.0F);

  /* Outport: '<Root>/fault_peak_speed' incorporates:
   *  Constant: '<S5>/Constant2'
   *  Inport: '<Root>/Act_n'
   *  RelationalOperator: '<S5>/Smaller2'
   */
  rtY->fault_peak_speed = (rtU->Act_n >= 1500.0F);

  /* DiscreteIntegrator: '<S317>/Accumulator' incorporates:
   *  Delay: '<S317>/Delay'
   *  Inport: '<Root>/Act_n'
   *  Sum: '<S317>/Sum'
   */
  rtDW->b = (rtU->Act_n - rtDW->Delay_DSTATE_ki[0]) + rtDW->Accumulator_DSTATE_d;

  /* Outport: '<Root>/fault_max_speed' incorporates:
   *  Constant: '<S5>/Constant3'
   *  Gain: '<S317>/Gain'
   *  RelationalOperator: '<S5>/Smaller3'
   */
  rtY->fault_max_speed = (0.00833333377F * rtDW->b >= 600.0F);

  /* Math: '<S5>/Square1' incorporates:
   *  Inport: '<Root>/Act_Iv'
   */
  rtDW->Gain1 = rtU->Act_Iv * rtU->Act_Iv;

  /* DiscreteIntegrator: '<S318>/Accumulator' incorporates:
   *  Delay: '<S318>/Delay'
   *  Sum: '<S318>/Sum'
   */
  rtDW->y_i = (rtDW->Gain1 - rtDW->Delay_DSTATE_kl[0]) +
    rtDW->Accumulator_DSTATE_f;

  /* Outport: '<Root>/fault_rms_current_v' incorporates:
   *  Constant: '<S5>/Constant5'
   *  Gain: '<S318>/Gain'
   *  RelationalOperator: '<S5>/Smaller5'
   *  Sqrt: '<S5>/Square Root1'
   */
  rtY->fault_rms_current_v = (sqrtf(0.05F * rtDW->y_i) >= 50.0F);

  /* Math: '<S5>/Square2' incorporates:
   *  Inport: '<Root>/Act_Iw'
   */
  rtDW->y = rtU->Act_Iw * rtU->Act_Iw;

  /* DiscreteIntegrator: '<S319>/Accumulator' incorporates:
   *  Delay: '<S319>/Delay'
   *  Sum: '<S319>/Sum'
   */
  rtDW->Switch2 = (rtDW->y - rtDW->Delay_DSTATE_b[0]) +
    rtDW->Accumulator_DSTATE_n;

  /* Outport: '<Root>/fault_rms_current_w' incorporates:
   *  Constant: '<S5>/Constant7'
   *  Gain: '<S319>/Gain'
   *  RelationalOperator: '<S5>/Smaller7'
   *  Sqrt: '<S5>/Square Root2'
   */
  rtY->fault_rms_current_w = (sqrtf(0.05F * rtDW->Switch2) >= 50.0F);

  /* Outport: '<Root>/fault_peak_current_v' incorporates:
   *  Abs: '<S5>/Abs1'
   *  Constant: '<S5>/Constant4'
   *  Inport: '<Root>/Act_Iv'
   *  RelationalOperator: '<S5>/Smaller4'
   */
  rtY->fault_peak_current_v = (fabsf(rtU->Act_Iv) >= 50.0F);

  /* Outport: '<Root>/fault_peak_current_w' incorporates:
   *  Abs: '<S5>/Abs2'
   *  Constant: '<S5>/Constant6'
   *  Inport: '<Root>/Act_Iw'
   *  RelationalOperator: '<S5>/Smaller6'
   */
  rtY->fault_peak_current_w = (fabsf(rtU->Act_Iw) >= 50.0F);

  /* Update for Delay: '<S3>/Delay' */
  rtDW->Delay_DSTATE = rtDW->DiscreteTimeIntegrator;

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE = 0.5F * rtDW->Gain +
    rtDW->DiscreteTimeIntegrator;

  /* Update for Delay: '<S316>/Delay' */
  for (rtDW->SignCorrected_a = 0; rtDW->SignCorrected_a < 19;
       rtDW->SignCorrected_a++) {
    rtDW->Delay_DSTATE_k[rtDW->SignCorrected_a] = rtDW->Delay_DSTATE_k
      [rtDW->SignCorrected_a + 1];
  }

  rtDW->Delay_DSTATE_k[19] = rtDW->c;

  /* End of Update for Delay: '<S316>/Delay' */

  /* Update for DiscreteIntegrator: '<S316>/Accumulator' */
  rtDW->Accumulator_DSTATE = rtDW->a;

  /* Update for Delay: '<S317>/Delay' incorporates:
   *  Inport: '<Root>/Act_n'
   */
  for (rtDW->SignCorrected_a = 0; rtDW->SignCorrected_a < 119;
       rtDW->SignCorrected_a++) {
    rtDW->Delay_DSTATE_ki[rtDW->SignCorrected_a] = rtDW->Delay_DSTATE_ki
      [rtDW->SignCorrected_a + 1];
  }

  rtDW->Delay_DSTATE_ki[119] = rtU->Act_n;

  /* End of Update for Delay: '<S317>/Delay' */

  /* Update for DiscreteIntegrator: '<S317>/Accumulator' */
  rtDW->Accumulator_DSTATE_d = rtDW->b;

  /* Update for DiscreteIntegrator: '<S318>/Accumulator' */
  rtDW->Accumulator_DSTATE_f = rtDW->y_i;
  for (rtDW->SignCorrected_a = 0; rtDW->SignCorrected_a < 19;
       rtDW->SignCorrected_a++) {
    /* Update for Delay: '<S318>/Delay' */
    rtDW->Delay_DSTATE_kl[rtDW->SignCorrected_a] = rtDW->Delay_DSTATE_kl
      [rtDW->SignCorrected_a + 1];

    /* Update for Delay: '<S319>/Delay' */
    rtDW->Delay_DSTATE_b[rtDW->SignCorrected_a] = rtDW->Delay_DSTATE_b
      [rtDW->SignCorrected_a + 1];
  }

  /* Update for Delay: '<S318>/Delay' */
  rtDW->Delay_DSTATE_kl[19] = rtDW->Gain1;

  /* Update for Delay: '<S319>/Delay' */
  rtDW->Delay_DSTATE_b[19] = rtDW->y;

  /* Update for DiscreteIntegrator: '<S319>/Accumulator' */
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
  /* InitializeConditions for Delay: '<S214>/Delay1' */
  rtDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S214>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;

  /* InitializeConditions for Delay: '<S214>/Delay' */
  rtDW->Delay_DSTATE_l = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S214>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S215>/Delay1' */
  rtDW->Delay1_DSTATE_o = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S215>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.0F;

  /* InitializeConditions for Delay: '<S215>/Delay' */
  rtDW->Delay_DSTATE_nv = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S215>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.0F;

  /* InitializeConditions for Delay: '<S213>/Delay1' */
  rtDW->Delay1_DSTATE_d = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S213>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTAT_om = 0.0F;

  /* InitializeConditions for Delay: '<S213>/Delay' */
  rtDW->Delay_DSTATE_j = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S213>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_a = 0.0F;

  /* InitializeConditions for Delay: '<S216>/Delay1' */
  rtDW->Delay1_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S216>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.0F;

  /* InitializeConditions for Delay: '<S216>/Delay' */
  rtDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S216>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.0F;

  /* InitializeConditions for Delay: '<S217>/Delay1' */
  rtDW->Delay1_DSTATE_oi = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S217>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.0F;

  /* InitializeConditions for Delay: '<S217>/Delay' */
  rtDW->Delay_DSTATE_nm = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S217>/Discrete-Time Integrator1' */
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
