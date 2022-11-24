/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 4.6
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Nov 24 11:37:38 2022
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
static uint32_T plook_u32u16u64n48_even0c_gf(uint16_T u, uint16_T bp0, uint32_T
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
static uint32_T plook_u32u16u64n48_even0c_gf(uint16_T u, uint16_T bp0, uint32_T
  maxIndex, uint64_T *fraction)
{
  uint32_T bpIndex;
  uint16_T uAdjust;

  /* Prelookup - Index and Fraction
     Index Search method: 'even'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'on'
     Rounding mode: 'floor'
   */
  uAdjust = (uint16_T)((uint32_T)u - bp0);
  if (uAdjust < maxIndex) {
    bpIndex = uAdjust;
    *fraction = 0ULL;
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
 *    '<S107>/MATLAB Function'
 *    '<S184>/MATLAB Function'
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

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/Referenzstromerzeugung_asymetrisch/MATLAB Function': '<S38>:1' */
  /*  Up = Polradspannung, induced Voltage, back emf (als komplexen Vektor) */
  /*  i_q =  referenz q-Strom (als reeler Wert) */
  /* '<S38>:1:4' if enable == 1 */
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

    /* '<S38>:1:5' p=18; */
    /*  Polpaarzahl */
    /*     %% Matrizen für symetrische Komponenten */
    /*  */
    /* '<S38>:1:8' a=single(exp(1i*(2*pi/3))); */
    /* '<S38>:1:9' T=single([1   1   1;  a^2 a   1; a   a^2 1]); */
    /*     %% Eingangsvektoren */
    /* '<S38>:1:11' U=[Psi_PM_U; Psi_PM_V;Psi_PM_W].*omega_el; */
    /* '<S38>:1:12' I_U=single(I_im*exp(1i*(-0*pi/3))); */
    /* '<S38>:1:13' I_V=single(I_im*exp(1i*(-2*pi/3))); */
    I_V_re_tmp = rtu_I_im * -0.5F;
    I_V_im = rtu_I_im * -0.866025388F;

    /* '<S38>:1:14' I_W=single(I_im*exp(1i*(-4*pi/3))); */
    I_W_im = rtu_I_im * 0.866025388F;

    /* '<S38>:1:15' I=single([I_U;I_V;I_W]); */
    /*  Symetrische Komponenten von Spannung */
    /*  Komponenten (1. Dimensoin -> Mit.-,Gegen-,Nullkomponente; 2. Dimension -> */
    /*  Phase 1,2,3 */
    /*  */
    /* '<S38>:1:20' U_sym_komp_hilf=single((inv(T)*U)); */
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
    /* '<S38>:1:21' U_sym_komp=single(zeros(3,3)*(0+0i)); */
    /*  Mitkomponente */
    /* '<S38>:1:23' U_sym_komp(1,1)=single(U_sym_komp_hilf(1)*1); */
    /* '<S38>:1:24' U_sym_komp(1,2)=single(U_sym_komp_hilf(1)*a^2); */
    /* '<S38>:1:25' U_sym_komp(1,3)=single(U_sym_komp_hilf(1)*a); */
    /*  Gegenkomponente */
    /* '<S38>:1:27' U_sym_komp(2,1)=single(U_sym_komp_hilf(2)*1); */
    /* '<S38>:1:28' U_sym_komp(2,2)=single(U_sym_komp_hilf(2)*a); */
    rtu_Psi_PM_U_idx_0_im = localDW->U_sym_komp_hilf[1].re * -0.5F;
    U_sym_komp_idx_4_re = rtu_Psi_PM_U_idx_0_im - localDW->U_sym_komp_hilf[1].im
      * 0.866025388F;
    rtu_Psi_PM_U_idx_0_re = localDW->U_sym_komp_hilf[1].im * -0.5F;
    U_sym_komp_idx_4_im = localDW->U_sym_komp_hilf[1].re * 0.866025388F +
      rtu_Psi_PM_U_idx_0_re;

    /* '<S38>:1:29' U_sym_komp(2,3)=single(U_sym_komp_hilf(2)*a^2); */
    U_sym_komp_idx_7_re = rtu_Psi_PM_U_idx_0_im - localDW->U_sym_komp_hilf[1].im
      * -0.866025388F;
    U_sym_komp_idx_7_im = localDW->U_sym_komp_hilf[1].re * -0.866025388F +
      rtu_Psi_PM_U_idx_0_re;

    /*  Nullkomponente */
    /* '<S38>:1:31' U_sym_komp(3,1)=single(U_sym_komp_hilf(3)*1); */
    /* '<S38>:1:32' U_sym_komp(3,2)=single(U_sym_komp_hilf(3)*1); */
    /* '<S38>:1:33' U_sym_komp(3,3)=single(U_sym_komp_hilf(3)*1); */
    /*     %% Kompensation von U_g+U_0 */
    /* '<S38>:1:35' I_Gegen_U=single(-(I_U*(U_sym_komp(2,1)+U_sym_komp(3,1)))/(U_sym_komp(1,1)+U_sym_komp(2,1)+U_sym_komp(3,1))); */
    /* '<S38>:1:36' I_Gegen_V=single(-(I_V*(U_sym_komp(2,2)+U_sym_komp(3,2)))/(U_sym_komp(1,2)+U_sym_komp(2,2)+U_sym_komp(3,2))); */
    /* '<S38>:1:37' I_Gegen_W=single(-(I_W*(U_sym_komp(2,3)+U_sym_komp(3,3)))/(U_sym_komp(1,3)+U_sym_komp(2,3)+U_sym_komp(3,3))); */
    /* '<S38>:1:38' I_Mit=single(I); */
    /*  */
    /* '<S38>:1:40' I_Gegen=single([I_Gegen_U; I_Gegen_V; I_Gegen_W]); */
    /* '<S38>:1:41' I_compensation=single((I_Gegen+I_Mit)); */
    /* '<S38>:1:42' I_compensation_sym_components=single((inv(T)*I_compensation)); */
    /* .*[1 a^2 a; 1 a a^2;1 1 1])); */
    /* '<S38>:1:43' I_compensation_sym_components=single(I_compensation_sym_components.*exp(1i*(pi/2))); */
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
    /* '<S38>:1:47' I_re_mit=single(real(I_compensation_sym_components(1,1))); */
    *rty_I_re_mit = localDW->U_sym_komp_hilf[0].re;

    /* '<S38>:1:48' I_im_mit=single(imag(I_compensation_sym_components(1,1))); */
    *rty_I_im_mit = localDW->U_sym_komp_hilf[0].im;

    /* '<S38>:1:49' I_re_gegen=single(real(I_compensation_sym_components(2,1))); */
    *rty_I_re_gegen = localDW->U_sym_komp_hilf[1].re;

    /* '<S38>:1:50' I_im_gegen=single(imag(I_compensation_sym_components(2,1))); */
    *rty_I_im_gegen = localDW->U_sym_komp_hilf[1].im;

    /* '<S38>:1:51' I_re_null=single(real(I_compensation_sym_components(3,1))); */
    *rty_I_re_null = localDW->U_sym_komp_hilf[2].re;

    /* '<S38>:1:52' I_im_null=single(imag(I_compensation_sym_components(3,1))); */
    *rty_I_im_null = localDW->U_sym_komp_hilf[2].im;

    /*  */
  } else {
    /* '<S38>:1:54' else */
    /*     %% Output as single */
    /* '<S38>:1:56' I_re_mit=single(I_re); */
    *rty_I_re_mit = rtu_I_re;

    /* '<S38>:1:57' I_im_mit=single(I_im); */
    *rty_I_im_mit = rtu_I_im;

    /* '<S38>:1:58' I_re_gegen=single(0); */
    *rty_I_re_gegen = 0.0F;

    /* '<S38>:1:59' I_im_gegen=single(0); */
    *rty_I_im_gegen = 0.0F;

    /* '<S38>:1:60' I_re_null=single(0); */
    *rty_I_re_null = 0.0F;

    /* '<S38>:1:61' I_im_null=single(0); */
    *rty_I_im_null = 0.0F;
  }
}

/*
 * Output and update for atomic system:
 *    '<S31>/MATLAB Function'
 *    '<S32>/MATLAB Function'
 *    '<S33>/MATLAB Function'
 *    '<S34>/MATLAB Function'
 *    '<S108>/MATLAB Function'
 *    '<S109>/MATLAB Function'
 *    '<S110>/MATLAB Function'
 *    '<S111>/MATLAB Function'
 *    '<S185>/MATLAB Function'
 *    '<S186>/MATLAB Function'
 *    ...
 */
static void MATLABFunction_a(real32_T rtu_re, real32_T rtu_U_lim, boolean_T
  rtu_Betrieb, real32_T rtu_im, real32_T *rty_re_lim, real32_T *rty_im_lim)
{
  real32_T re_lim;
  real32_T rtu_im_0;
  real32_T tmp;

  /* MATLAB Function 'Strangstromregelung-Einzelne Blocks/resonater-PI-Regler/MATLAB Function': '<S56>:1' */
  /* '<S56>:1:2' if (re^2 + im^2)<=U_lim^2 */
  tmp = rtu_U_lim * rtu_U_lim;
  if (rtu_re * rtu_re + rtu_im * rtu_im <= tmp) {
    /* '<S56>:1:3' re_lim = re; */
    re_lim = rtu_re;

    /* '<S56>:1:4' im_lim = im; */
    rtu_im_0 = rtu_im;
  } else if (!rtu_Betrieb) {
    /* '<S56>:1:5' elseif Betrieb == 0 */
    /* Generator */
    /* '<S56>:1:7' if abs(im)>0.95*U_lim */
    if (fabsf(rtu_im) > 0.95F * rtu_U_lim) {
      /* '<S56>:1:8' im_lim = sign(im)*0.95*U_lim; */
      if (rtu_im < 0.0F) {
        rtu_im_0 = -1.0F;
      } else {
        rtu_im_0 = (real32_T)(rtu_im > 0.0F);
      }

      rtu_im_0 = rtu_im_0 * 0.95F * rtu_U_lim;
    } else {
      /* '<S56>:1:9' else */
      /* '<S56>:1:10' im_lim = im; */
      rtu_im_0 = rtu_im;
    }

    /* '<S56>:1:12' re_lim = sign(re)*sqrt(U_lim^2 - im_lim^2); */
    if (rtu_re < 0.0F) {
      re_lim = -1.0F;
    } else {
      re_lim = (real32_T)(rtu_re > 0.0F);
    }

    re_lim *= sqrtf(tmp - rtu_im_0 * rtu_im_0);
  } else {
    /* '<S56>:1:13' else */
    /* Motor */
    /* '<S56>:1:15' if abs(re)>0.95*U_lim */
    if (fabsf(rtu_re) > 0.95F * rtu_U_lim) {
      /* '<S56>:1:16' re_lim = sign(re)*0.95*U_lim; */
      if (rtu_re < 0.0F) {
        re_lim = -1.0F;
      } else {
        re_lim = (real32_T)(rtu_re > 0.0F);
      }

      re_lim = re_lim * 0.95F * rtu_U_lim;
    } else {
      /* '<S56>:1:17' else */
      /* '<S56>:1:18' re_lim = re; */
      re_lim = rtu_re;
    }

    /* '<S56>:1:20' im_lim = sign(im)*sqrt(U_lim^2 - re_lim^2); */
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
  rtu_Psi_PM_n, creal32_T rtu_Psi_PM_k, real32_T *rty_a, real32_T *rty_I_ref1,
  real32_T rtp_Offset_S, real32_T rtp_Offset_gegen, real32_T rtp_Offset_null,
  DW_Strangstromregler_asymetrisc *localDW)
{
  /* Sum: '<S23>/Sum1' incorporates:
   *  Constant: '<S23>/Constant'
   */
  localDW->theta_e = rtu_Theta_u_back + rtp_Offset_S;

  /* DataTypeConversion: '<S60>/CastU16En16' incorporates:
   *  DataTypeConversion: '<S66>/CastU16En16'
   *  Gain: '<S31>/Gain5'
   *  Product: '<S31>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint16_T)(0.159154937F * localDW->theta_e *
    65536.0F);

  /* RelationalOperator: '<S60>/LTEp25' incorporates:
   *  DataTypeConversion: '<S60>/CastU16En16'
   */
  localDW->LTEp25_my = (localDW->rtb_CastU16En16_jv_tmp <= 16384);

  /* RelationalOperator: '<S60>/GTEp75' incorporates:
   *  DataTypeConversion: '<S60>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp >= 49152);

  /* Switch: '<S60>/QuadHandle2' incorporates:
   *  Constant: '<S60>/Point75'
   *  DataTypeConversion: '<S60>/CastU16En16'
   *  RelationalOperator: '<S60>/LTEp50'
   *  Sum: '<S60>/p75mA'
   *  Switch: '<S60>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 32768) {
    /* Switch: '<S60>/QuadHandle1a' incorporates:
     *  Constant: '<S60>/Point25'
     *  Sum: '<S60>/Amp25'
     *  Sum: '<S60>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 -
        localDW->rtb_CastU16En16_jv_tmp);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp
        - 16384);
    }

    /* End of Switch: '<S60>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S60>/QuadHandle1b' incorporates:
     *  Constant: '<S60>/Point75'
     *  Sum: '<S60>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp -
      49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 -
      localDW->rtb_CastU16En16_jv_tmp);
  }

  /* End of Switch: '<S60>/QuadHandle2' */

  /* Lookup_n-D: '<S59>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S60>/SignCorrected' incorporates:
   *  Logic: '<S60>/1st or 4th Quad'
   *  Lookup_n-D: '<S59>/Look-Up Table'
   *  UnaryMinus: '<S60>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_h = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_h = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S60>/SignCorrected' */

  /* Sum: '<S23>/Sum' incorporates:
   *  Constant: '<S23>/Constant'
   */
  localDW->Delay1_m = rtu_Theta_u + rtp_Offset_S;

  /* DataTypeConversion: '<S62>/CastU16En16' incorporates:
   *  DataTypeConversion: '<S43>/CastU16En16'
   *  Gain: '<S31>/Gain4'
   *  Product: '<S31>/Product5'
   */
  localDW->rtb_CastU16En16_jv_tmp_tmp = (uint16_T)(0.159154937F *
    localDW->Delay1_m * 65536.0F);

  /* RelationalOperator: '<S62>/LTEp25' incorporates:
   *  DataTypeConversion: '<S62>/CastU16En16'
   */
  localDW->LTEp25_my = (localDW->rtb_CastU16En16_jv_tmp_tmp <= 16384);

  /* RelationalOperator: '<S62>/GTEp75' incorporates:
   *  DataTypeConversion: '<S62>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_tmp >= 49152);

  /* Switch: '<S62>/QuadHandle2' incorporates:
   *  Constant: '<S62>/Point75'
   *  DataTypeConversion: '<S62>/CastU16En16'
   *  RelationalOperator: '<S62>/LTEp50'
   *  Sum: '<S62>/p75mA'
   *  Switch: '<S62>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_tmp <= 32768) {
    /* Switch: '<S62>/QuadHandle1a' incorporates:
     *  Constant: '<S62>/Point25'
     *  Sum: '<S62>/Amp25'
     *  Sum: '<S62>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 -
        localDW->rtb_CastU16En16_jv_tmp_tmp);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)
        (localDW->rtb_CastU16En16_jv_tmp_tmp - 16384);
    }

    /* End of Switch: '<S62>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S62>/QuadHandle1b' incorporates:
     *  Constant: '<S62>/Point75'
     *  Sum: '<S62>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)
      (localDW->rtb_CastU16En16_jv_tmp_tmp - 49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 -
      localDW->rtb_CastU16En16_jv_tmp_tmp);
  }

  /* End of Switch: '<S62>/QuadHandle2' */

  /* Lookup_n-D: '<S61>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S62>/SignCorrected' incorporates:
   *  Logic: '<S62>/1st or 4th Quad'
   *  Lookup_n-D: '<S61>/Look-Up Table'
   *  Switch: '<S103>/SignCorrected'
   *  UnaryMinus: '<S62>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_cw = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S62>/SignCorrected' */

  /* MATLAB Function: '<S30>/MATLAB Function' */
  MATLABFunction_i(rtu_Psi_PM, rtu_Psi_PM_n, rtu_Psi_PM_k, rtu_I_re, rtu_I_im,
                   rtu_w1, rtu_enable_compensation_current, &localDW->im_lim_mv,
                   &localDW->re_lim_l, &localDW->im_lim_l, &localDW->re_lim_i,
                   &localDW->im_lim_k, &localDW->Sum_o,
                   &localDW->sf_MATLABFunction_i);

  /* DataTypeConversion: '<S43>/CastU16En16' incorporates:
   *  DataTypeConversion: '<S49>/CastU16En16'
   */
  localDW->CastU16En16_jv = localDW->rtb_CastU16En16_jv_tmp_tmp;

  /* RelationalOperator: '<S43>/LTEp25' */
  localDW->LTEp25_my = (localDW->rtb_CastU16En16_jv_tmp_tmp <= 16384);

  /* RelationalOperator: '<S43>/GTEp75' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_tmp >= 49152);

  /* Switch: '<S43>/QuadHandle2' incorporates:
   *  Constant: '<S43>/Point75'
   *  RelationalOperator: '<S43>/LTEp50'
   *  Sum: '<S43>/p75mA'
   *  Switch: '<S43>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp_tmp <= 32768) {
    /* Switch: '<S43>/QuadHandle1a' incorporates:
     *  Constant: '<S43>/Point25'
     *  Sum: '<S43>/Amp25'
     *  Sum: '<S43>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 -
        localDW->rtb_CastU16En16_jv_tmp_tmp);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)
        (localDW->rtb_CastU16En16_jv_tmp_tmp - 16384);
    }

    /* End of Switch: '<S43>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S43>/QuadHandle1b' incorporates:
     *  Constant: '<S43>/Point75'
     *  Sum: '<S43>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)
      (localDW->rtb_CastU16En16_jv_tmp_tmp - 49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 -
      localDW->rtb_CastU16En16_jv_tmp_tmp);
  }

  /* End of Switch: '<S43>/QuadHandle2' */

  /* Lookup_n-D: '<S42>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S43>/SignCorrected' incorporates:
   *  Logic: '<S43>/1st or 4th Quad'
   *  Lookup_n-D: '<S42>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S43>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S43>/SignCorrected' */

  /* Product: '<S30>/Product' incorporates:
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Strom_kompensiert_l = (real32_T)localDW->SignCorrected_o *
    6.10351562E-5F * localDW->im_lim_mv;

  /* RelationalOperator: '<S49>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_tmp <= 32768);

  /* Switch: '<S49>/QuadHandle1' incorporates:
   *  Constant: '<S49>/Point50'
   *  Sum: '<S49>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp_tmp -
      32768);
  }

  /* End of Switch: '<S49>/QuadHandle1' */

  /* Switch: '<S49>/QuadHandle2' incorporates:
   *  Constant: '<S49>/Point50'
   *  RelationalOperator: '<S49>/LTEp25'
   *  Sum: '<S49>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S49>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S49>/QuadHandle2' */

  /* Lookup_n-D: '<S48>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S49>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S48>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S49>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S49>/SignCorrected' */

  /* Product: '<S30>/Product1' incorporates:
   *  Gain: '<S30>/Gain'
   *  Sum: '<S30>/Add'
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->re_lim_g = (real32_T)(-32768 * localDW->SignCorrected_o) *
    1.86264515E-9F * (rtu_I_im_CT + localDW->re_lim_l);

  /* DataTypeConversion: '<S45>/CastU16En16' incorporates:
   *  Constant: '<S23>/Constant2'
   *  DataTypeConversion: '<S51>/CastU16En16'
   *  Gain: '<S30>/Gain4'
   *  Sum: '<S23>/Add2'
   */
  localDW->CastU16En16_jv = (uint16_T)((localDW->Delay1_m + rtp_Offset_gegen) *
    0.159154937F * 65536.0F);

  /* RelationalOperator: '<S45>/LTEp25' incorporates:
   *  DataTypeConversion: '<S45>/CastU16En16'
   */
  localDW->LTEp25_my = (localDW->CastU16En16_jv <= 16384);

  /* RelationalOperator: '<S45>/GTEp75' incorporates:
   *  DataTypeConversion: '<S45>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv >= 49152);

  /* Switch: '<S45>/QuadHandle2' incorporates:
   *  Constant: '<S45>/Point75'
   *  DataTypeConversion: '<S45>/CastU16En16'
   *  RelationalOperator: '<S45>/LTEp50'
   *  Sum: '<S45>/p75mA'
   *  Switch: '<S45>/QuadHandle1b'
   */
  if (localDW->CastU16En16_jv <= 32768) {
    /* Switch: '<S45>/QuadHandle1a' incorporates:
     *  Constant: '<S45>/Point25'
     *  Sum: '<S45>/Amp25'
     *  Sum: '<S45>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 - localDW->CastU16En16_jv);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 16384);
    }

    /* End of Switch: '<S45>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S45>/QuadHandle1b' incorporates:
     *  Constant: '<S45>/Point75'
     *  Sum: '<S45>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S45>/QuadHandle2' */

  /* Lookup_n-D: '<S44>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S45>/SignCorrected' incorporates:
   *  Logic: '<S45>/1st or 4th Quad'
   *  Lookup_n-D: '<S44>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S45>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S45>/SignCorrected' */

  /* Product: '<S30>/Product2' incorporates:
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->im_lim_mv = (real32_T)localDW->SignCorrected_o * 6.10351562E-5F *
    localDW->im_lim_l;

  /* RelationalOperator: '<S51>/LTEp50' */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv <= 32768);

  /* Switch: '<S51>/QuadHandle1' incorporates:
   *  Constant: '<S51>/Point50'
   *  Sum: '<S51>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->CastU16En16_jv - 32768);
  }

  /* End of Switch: '<S51>/QuadHandle1' */

  /* Switch: '<S51>/QuadHandle2' incorporates:
   *  Constant: '<S51>/Point50'
   *  RelationalOperator: '<S51>/LTEp25'
   *  Sum: '<S51>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S51>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S51>/QuadHandle2' */

  /* Lookup_n-D: '<S50>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S51>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S50>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S51>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S51>/SignCorrected' */

  /* Product: '<S30>/Product3' incorporates:
   *  Gain: '<S30>/Gain1'
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Sum_j = (real32_T)(-32768 * localDW->SignCorrected_o) *
    1.86264515E-9F * localDW->re_lim_i;

  /* DataTypeConversion: '<S47>/CastU16En16' incorporates:
   *  Constant: '<S23>/Constant3'
   *  DataTypeConversion: '<S53>/CastU16En16'
   *  Gain: '<S30>/Gain5'
   *  Sum: '<S23>/Add3'
   */
  localDW->CastU16En16_jv = (uint16_T)((localDW->Delay1_m + rtp_Offset_null) *
    0.159154937F * 65536.0F);

  /* RelationalOperator: '<S47>/LTEp25' incorporates:
   *  DataTypeConversion: '<S47>/CastU16En16'
   */
  localDW->LTEp25_my = (localDW->CastU16En16_jv <= 16384);

  /* RelationalOperator: '<S47>/GTEp75' incorporates:
   *  DataTypeConversion: '<S47>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv >= 49152);

  /* Switch: '<S47>/QuadHandle2' incorporates:
   *  Constant: '<S47>/Point75'
   *  DataTypeConversion: '<S47>/CastU16En16'
   *  RelationalOperator: '<S47>/LTEp50'
   *  Sum: '<S47>/p75mA'
   *  Switch: '<S47>/QuadHandle1b'
   */
  if (localDW->CastU16En16_jv <= 32768) {
    /* Switch: '<S47>/QuadHandle1a' incorporates:
     *  Constant: '<S47>/Point25'
     *  Sum: '<S47>/Amp25'
     *  Sum: '<S47>/p25mA'
     */
    if (localDW->LTEp25_my) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 - localDW->CastU16En16_jv);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 16384);
    }

    /* End of Switch: '<S47>/QuadHandle1a' */
  } else if (localDW->GTEp75_cz) {
    /* Switch: '<S47>/QuadHandle1b' incorporates:
     *  Constant: '<S47>/Point75'
     *  Sum: '<S47>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S47>/QuadHandle2' */

  /* Lookup_n-D: '<S46>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S47>/SignCorrected' incorporates:
   *  Logic: '<S47>/1st or 4th Quad'
   *  Lookup_n-D: '<S46>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S47>/Negate'
   */
  if (localDW->LTEp25_my || localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S47>/SignCorrected' */

  /* Product: '<S30>/Product4' incorporates:
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Sum_d = (real32_T)localDW->SignCorrected_o * 6.10351562E-5F *
    localDW->im_lim_k;

  /* RelationalOperator: '<S53>/LTEp50' */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv <= 32768);

  /* Switch: '<S53>/QuadHandle1' incorporates:
   *  Constant: '<S53>/Point50'
   *  Sum: '<S53>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->CastU16En16_jv - 32768);
  }

  /* End of Switch: '<S53>/QuadHandle1' */

  /* Switch: '<S53>/QuadHandle2' incorporates:
   *  Constant: '<S53>/Point50'
   *  RelationalOperator: '<S53>/LTEp25'
   *  Sum: '<S53>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S53>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S53>/QuadHandle2' */

  /* Lookup_n-D: '<S52>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S53>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S52>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S53>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S53>/SignCorrected' */

  /* Sum: '<S30>/Strom_kompensiert' incorporates:
   *  Gain: '<S30>/Gain2'
   *  Product: '<S30>/Product5'
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Strom_kompensiert_l = ((((localDW->Strom_kompensiert_l +
    localDW->re_lim_g) + localDW->im_lim_mv) + localDW->Sum_j) + localDW->Sum_d)
    + (real32_T)(-32768 * localDW->SignCorrected_o) * 1.86264515E-9F *
    localDW->Sum_o;

  /* Gain: '<S31>/Gain6' incorporates:
   *  Gain: '<S32>/Gain6'
   *  Gain: '<S33>/Gain6'
   *  Gain: '<S34>/Gain6'
   *  Sum: '<S23>/Sum2'
   */
  localDW->re_lim_g = (localDW->Strom_kompensiert_l - rtu_I_S) * rtP.Kp;

  /* Product: '<S31>/Product1' incorporates:
   *  Gain: '<S31>/Gain6'
   *  Switch: '<S103>/SignCorrected'
   */
  localDW->im_lim_mv = (real32_T)localDW->SignCorrected_cw * 6.10351562E-5F *
    localDW->re_lim_g;

  /* Gain: '<S31>/Gain1' incorporates:
   *  Delay: '<S31>/Delay1'
   *  Sum: '<S31>/Sum4'
   */
  localDW->Gain1_h = 2.5E-5F * rtP.K1 * (localDW->Delay1_DSTATE +
    localDW->im_lim_mv);

  /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator = 0.5F * localDW->Gain1_h +
    localDW->DiscreteTimeIntegrator_DSTATE;

  /* Sum: '<S31>/Sum5' */
  localDW->U_re_o = localDW->DiscreteTimeIntegrator + localDW->im_lim_mv;

  /* MATLAB Function: '<S23>/MATLAB Function' */
  MATLABFunction(rtu_I_im, rtu_w1, &localDW->LTEp25_my);

  /* DataTypeConversion: '<S64>/CastU16En16' incorporates:
   *  DataTypeConversion: '<S62>/CastU16En16'
   */
  localDW->CastU16En16_jv = localDW->rtb_CastU16En16_jv_tmp_tmp;

  /* RelationalOperator: '<S64>/LTEp50' incorporates:
   *  DataTypeConversion: '<S62>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp_tmp <= 32768);

  /* Switch: '<S64>/QuadHandle1' incorporates:
   *  Constant: '<S64>/Point50'
   *  DataTypeConversion: '<S62>/CastU16En16'
   *  Sum: '<S64>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp_tmp -
      32768);
  }

  /* End of Switch: '<S64>/QuadHandle1' */

  /* Switch: '<S64>/QuadHandle2' incorporates:
   *  Constant: '<S64>/Point50'
   *  RelationalOperator: '<S64>/LTEp25'
   *  Sum: '<S64>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S64>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S64>/QuadHandle2' */

  /* Lookup_n-D: '<S63>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S64>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S63>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S64>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S64>/SignCorrected' */

  /* Product: '<S31>/Product' incorporates:
   *  Gain: '<S31>/Gain'
   *  Gain: '<S31>/Gain6'
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->im_lim_mv = (real32_T)(-32768 * localDW->SignCorrected_o) *
    1.86264515E-9F * localDW->re_lim_g;

  /* Gain: '<S31>/Gain2' incorporates:
   *  Delay: '<S31>/Delay'
   *  Sum: '<S31>/Sum2'
   */
  localDW->Gain2_nl = 2.5E-5F * rtP.K1 * (localDW->im_lim_mv +
    localDW->Delay_DSTATE);

  /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1 = 0.5F * localDW->Gain2_nl +
    localDW->DiscreteTimeIntegrator1_DSTATE;

  /* Sum: '<S31>/Sum6' */
  localDW->U_im_i = localDW->im_lim_mv + localDW->DiscreteTimeIntegrator1;

  /* MATLAB Function: '<S31>/MATLAB Function' incorporates:
   *  Constant: '<S31>/Constant2'
   *  Product: '<S31>/Product6'
   */
  MATLABFunction_a(localDW->U_re_o, 0.9F * rtu_U_ZK1, localDW->LTEp25_my,
                   localDW->U_im_i, &localDW->re_lim_l, &localDW->im_lim_mv);

  /* DataTypeConversion: '<S66>/CastU16En16' */
  localDW->CastU16En16_jv = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S66>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 32768);

  /* Switch: '<S66>/QuadHandle1' incorporates:
   *  Constant: '<S66>/Point50'
   *  Sum: '<S66>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp - 32768);
  }

  /* End of Switch: '<S66>/QuadHandle1' */

  /* Switch: '<S66>/QuadHandle2' incorporates:
   *  Constant: '<S66>/Point50'
   *  RelationalOperator: '<S66>/LTEp25'
   *  Sum: '<S66>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S66>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S66>/QuadHandle2' */

  /* Lookup_n-D: '<S65>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S66>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S65>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S66>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S66>/SignCorrected' */

  /* Sum: '<S31>/Sum' incorporates:
   *  Gain: '<S31>/Gain3'
   *  Product: '<S31>/Product2'
   *  Product: '<S31>/Product3'
   *  Switch: '<S105>/SignCorrected'
   *  Switch: '<S60>/SignCorrected'
   */
  localDW->Add1_l = (real32_T)(-32768 * localDW->SignCorrected_o) *
    1.86264515E-9F * localDW->im_lim_mv + (real32_T)localDW->SignCorrected_h *
    6.10351562E-5F * localDW->re_lim_l;

  /* DataTypeConversion: '<S73>/CastU16En16' incorporates:
   *  Constant: '<S32>/Constant1'
   *  DataTypeConversion: '<S79>/CastU16En16'
   *  Gain: '<S32>/Gain5'
   *  Product: '<S32>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint16_T)(localDW->theta_e * 2.0F *
    0.159154937F * 65536.0F);

  /* RelationalOperator: '<S73>/LTEp25' incorporates:
   *  DataTypeConversion: '<S73>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 16384);

  /* RelationalOperator: '<S73>/GTEp75' incorporates:
   *  DataTypeConversion: '<S73>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp >= 49152);

  /* Switch: '<S73>/QuadHandle2' incorporates:
   *  Constant: '<S73>/Point75'
   *  DataTypeConversion: '<S73>/CastU16En16'
   *  RelationalOperator: '<S73>/LTEp50'
   *  Sum: '<S73>/p75mA'
   *  Switch: '<S73>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 32768) {
    /* Switch: '<S73>/QuadHandle1a' incorporates:
     *  Constant: '<S73>/Point25'
     *  Sum: '<S73>/Amp25'
     *  Sum: '<S73>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 -
        localDW->rtb_CastU16En16_jv_tmp);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp
        - 16384);
    }

    /* End of Switch: '<S73>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S73>/QuadHandle1b' incorporates:
     *  Constant: '<S73>/Point75'
     *  Sum: '<S73>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp -
      49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 -
      localDW->rtb_CastU16En16_jv_tmp);
  }

  /* End of Switch: '<S73>/QuadHandle2' */

  /* Lookup_n-D: '<S72>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S73>/SignCorrected' incorporates:
   *  Logic: '<S73>/1st or 4th Quad'
   *  Lookup_n-D: '<S72>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S73>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S73>/SignCorrected' */

  /* DataTypeConversion: '<S75>/CastU16En16' incorporates:
   *  Constant: '<S32>/Constant1'
   *  DataTypeConversion: '<S77>/CastU16En16'
   *  Gain: '<S32>/Gain4'
   *  Product: '<S32>/Product5'
   */
  localDW->CastU16En16_jv = (uint16_T)(localDW->Delay1_m * 2.0F * 0.159154937F *
    65536.0F);

  /* RelationalOperator: '<S75>/LTEp25' incorporates:
   *  DataTypeConversion: '<S75>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv <= 16384);

  /* RelationalOperator: '<S75>/GTEp75' incorporates:
   *  DataTypeConversion: '<S75>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->CastU16En16_jv >= 49152);

  /* Switch: '<S75>/QuadHandle2' incorporates:
   *  Constant: '<S75>/Point75'
   *  DataTypeConversion: '<S75>/CastU16En16'
   *  RelationalOperator: '<S75>/LTEp50'
   *  Sum: '<S75>/p75mA'
   *  Switch: '<S75>/QuadHandle1b'
   */
  if (localDW->CastU16En16_jv <= 32768) {
    /* Switch: '<S75>/QuadHandle1a' incorporates:
     *  Constant: '<S75>/Point25'
     *  Sum: '<S75>/Amp25'
     *  Sum: '<S75>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 - localDW->CastU16En16_jv);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 16384);
    }

    /* End of Switch: '<S75>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S75>/QuadHandle1b' incorporates:
     *  Constant: '<S75>/Point75'
     *  Sum: '<S75>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S75>/QuadHandle2' */

  /* Lookup_n-D: '<S74>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S75>/SignCorrected' incorporates:
   *  Logic: '<S75>/1st or 4th Quad'
   *  Lookup_n-D: '<S74>/Look-Up Table'
   *  Switch: '<S103>/SignCorrected'
   *  UnaryMinus: '<S75>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_cw = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_cw = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S75>/SignCorrected' */

  /* Product: '<S32>/Product1' incorporates:
   *  Switch: '<S103>/SignCorrected'
   */
  localDW->im_lim_o4 = (real32_T)localDW->SignCorrected_cw * 6.10351562E-5F *
    localDW->re_lim_g;

  /* Gain: '<S32>/Gain1' incorporates:
   *  Delay: '<S32>/Delay1'
   *  Sum: '<S32>/Sum4'
   */
  localDW->Gain1_g = 2.5E-5F * rtP.K2 * (localDW->Delay1_DSTATE_m +
    localDW->im_lim_o4);

  /* DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_o = 0.5F * localDW->Gain1_g +
    localDW->DiscreteTimeIntegrator_DSTATE_d;

  /* Sum: '<S32>/Sum5' */
  localDW->U_re_h = localDW->DiscreteTimeIntegrator_o + localDW->im_lim_o4;

  /* RelationalOperator: '<S77>/LTEp50' */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv <= 32768);

  /* Switch: '<S77>/QuadHandle1' incorporates:
   *  Constant: '<S77>/Point50'
   *  Sum: '<S77>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->CastU16En16_jv - 32768);
  }

  /* End of Switch: '<S77>/QuadHandle1' */

  /* Switch: '<S77>/QuadHandle2' incorporates:
   *  Constant: '<S77>/Point50'
   *  RelationalOperator: '<S77>/LTEp25'
   *  Sum: '<S77>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S77>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S77>/QuadHandle2' */

  /* Lookup_n-D: '<S76>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S77>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S76>/Look-Up Table'
   *  Switch: '<S103>/SignCorrected'
   *  UnaryMinus: '<S77>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_cw = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S77>/SignCorrected' */

  /* Product: '<S32>/Product' incorporates:
   *  Gain: '<S32>/Gain'
   *  Switch: '<S103>/SignCorrected'
   */
  localDW->Sum_j = (real32_T)(-32768 * localDW->SignCorrected_cw) *
    1.86264515E-9F * localDW->re_lim_g;

  /* Gain: '<S32>/Gain2' incorporates:
   *  Delay: '<S32>/Delay'
   *  Sum: '<S32>/Sum2'
   */
  localDW->Gain2_d = 2.5E-5F * rtP.K2 * (localDW->Sum_j +
    localDW->Delay_DSTATE_a);

  /* DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_f = 0.5F * localDW->Gain2_d +
    localDW->DiscreteTimeIntegrator1_DSTAT_m;

  /* Sum: '<S32>/Sum6' */
  localDW->U_im_pl = localDW->Sum_j + localDW->DiscreteTimeIntegrator1_f;

  /* MATLAB Function: '<S32>/MATLAB Function' incorporates:
   *  Constant: '<S32>/Constant2'
   *  Product: '<S32>/Product6'
   */
  MATLABFunction_a(localDW->U_re_h, 0.05F * rtu_U_ZK1, localDW->LTEp25_my,
                   localDW->U_im_pl, &localDW->re_lim_i, &localDW->im_lim_l);

  /* Product: '<S32>/Product3' incorporates:
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Sum_j = (real32_T)localDW->SignCorrected_o * 6.10351562E-5F *
    localDW->re_lim_i;

  /* DataTypeConversion: '<S79>/CastU16En16' */
  localDW->CastU16En16_jv = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S79>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 32768);

  /* Switch: '<S79>/QuadHandle1' incorporates:
   *  Constant: '<S79>/Point50'
   *  Sum: '<S79>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp - 32768);
  }

  /* End of Switch: '<S79>/QuadHandle1' */

  /* Switch: '<S79>/QuadHandle2' incorporates:
   *  Constant: '<S79>/Point50'
   *  RelationalOperator: '<S79>/LTEp25'
   *  Sum: '<S79>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S79>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S79>/QuadHandle2' */

  /* Lookup_n-D: '<S78>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S79>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S78>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S79>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S79>/SignCorrected' */

  /* Sum: '<S32>/Sum' incorporates:
   *  Gain: '<S32>/Gain3'
   *  Product: '<S32>/Product2'
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Sum_j += (real32_T)(-32768 * localDW->SignCorrected_o) *
    1.86264515E-9F * localDW->im_lim_l;

  /* DataTypeConversion: '<S86>/CastU16En16' incorporates:
   *  Constant: '<S33>/Constant1'
   *  DataTypeConversion: '<S92>/CastU16En16'
   *  Gain: '<S33>/Gain5'
   *  Product: '<S33>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint16_T)(localDW->theta_e * 4.0F *
    0.159154937F * 65536.0F);

  /* RelationalOperator: '<S86>/LTEp25' incorporates:
   *  DataTypeConversion: '<S86>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 16384);

  /* RelationalOperator: '<S86>/GTEp75' incorporates:
   *  DataTypeConversion: '<S86>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp >= 49152);

  /* Switch: '<S86>/QuadHandle2' incorporates:
   *  Constant: '<S86>/Point75'
   *  DataTypeConversion: '<S86>/CastU16En16'
   *  RelationalOperator: '<S86>/LTEp50'
   *  Sum: '<S86>/p75mA'
   *  Switch: '<S86>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 32768) {
    /* Switch: '<S86>/QuadHandle1a' incorporates:
     *  Constant: '<S86>/Point25'
     *  Sum: '<S86>/Amp25'
     *  Sum: '<S86>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 -
        localDW->rtb_CastU16En16_jv_tmp);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp
        - 16384);
    }

    /* End of Switch: '<S86>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S86>/QuadHandle1b' incorporates:
     *  Constant: '<S86>/Point75'
     *  Sum: '<S86>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp -
      49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 -
      localDW->rtb_CastU16En16_jv_tmp);
  }

  /* End of Switch: '<S86>/QuadHandle2' */

  /* Lookup_n-D: '<S85>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S86>/SignCorrected' incorporates:
   *  Logic: '<S86>/1st or 4th Quad'
   *  Lookup_n-D: '<S85>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S86>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S86>/SignCorrected' */

  /* DataTypeConversion: '<S88>/CastU16En16' incorporates:
   *  Constant: '<S33>/Constant1'
   *  DataTypeConversion: '<S90>/CastU16En16'
   *  Gain: '<S33>/Gain4'
   *  Product: '<S33>/Product5'
   */
  localDW->CastU16En16_jv = (uint16_T)(localDW->Delay1_m * 4.0F * 0.159154937F *
    65536.0F);

  /* RelationalOperator: '<S88>/LTEp25' incorporates:
   *  DataTypeConversion: '<S88>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv <= 16384);

  /* RelationalOperator: '<S88>/GTEp75' incorporates:
   *  DataTypeConversion: '<S88>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->CastU16En16_jv >= 49152);

  /* Switch: '<S88>/QuadHandle2' incorporates:
   *  Constant: '<S88>/Point75'
   *  DataTypeConversion: '<S88>/CastU16En16'
   *  RelationalOperator: '<S88>/LTEp50'
   *  Sum: '<S88>/p75mA'
   *  Switch: '<S88>/QuadHandle1b'
   */
  if (localDW->CastU16En16_jv <= 32768) {
    /* Switch: '<S88>/QuadHandle1a' incorporates:
     *  Constant: '<S88>/Point25'
     *  Sum: '<S88>/Amp25'
     *  Sum: '<S88>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 - localDW->CastU16En16_jv);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 16384);
    }

    /* End of Switch: '<S88>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S88>/QuadHandle1b' incorporates:
     *  Constant: '<S88>/Point75'
     *  Sum: '<S88>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S88>/QuadHandle2' */

  /* Lookup_n-D: '<S87>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S88>/SignCorrected' incorporates:
   *  Logic: '<S88>/1st or 4th Quad'
   *  Lookup_n-D: '<S87>/Look-Up Table'
   *  Switch: '<S103>/SignCorrected'
   *  UnaryMinus: '<S88>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_cw = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_cw = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S88>/SignCorrected' */

  /* Product: '<S33>/Product1' incorporates:
   *  Switch: '<S103>/SignCorrected'
   */
  localDW->re_lim_b = (real32_T)localDW->SignCorrected_cw * 6.10351562E-5F *
    localDW->re_lim_g;

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

  /* RelationalOperator: '<S90>/LTEp50' */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv <= 32768);

  /* Switch: '<S90>/QuadHandle1' incorporates:
   *  Constant: '<S90>/Point50'
   *  Sum: '<S90>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->CastU16En16_jv - 32768);
  }

  /* End of Switch: '<S90>/QuadHandle1' */

  /* Switch: '<S90>/QuadHandle2' incorporates:
   *  Constant: '<S90>/Point50'
   *  RelationalOperator: '<S90>/LTEp25'
   *  Sum: '<S90>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S90>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S90>/QuadHandle2' */

  /* Lookup_n-D: '<S89>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S90>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S89>/Look-Up Table'
   *  Switch: '<S103>/SignCorrected'
   *  UnaryMinus: '<S90>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_cw = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S90>/SignCorrected' */

  /* Product: '<S33>/Product' incorporates:
   *  Gain: '<S33>/Gain'
   *  Switch: '<S103>/SignCorrected'
   */
  localDW->Sum_o = (real32_T)(-32768 * localDW->SignCorrected_cw) *
    1.86264515E-9F * localDW->re_lim_g;

  /* Gain: '<S33>/Gain2' incorporates:
   *  Delay: '<S33>/Delay'
   *  Sum: '<S33>/Sum2'
   */
  localDW->Gain2_e = 2.5E-5F * rtP.K4 * (localDW->Sum_o +
    localDW->Delay_DSTATE_b);

  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_e = 0.5F * localDW->Gain2_e +
    localDW->DiscreteTimeIntegrator1_DSTAT_k;

  /* Sum: '<S33>/Sum6' */
  localDW->U_im_pt = localDW->Sum_o + localDW->DiscreteTimeIntegrator1_e;

  /* MATLAB Function: '<S33>/MATLAB Function' incorporates:
   *  Constant: '<S33>/Constant2'
   *  Product: '<S33>/Product6'
   */
  MATLABFunction_a(localDW->U_re_j, 0.02F * rtu_U_ZK1, localDW->LTEp25_my,
                   localDW->U_im_pt, &localDW->re_lim_b, &localDW->im_lim_k);

  /* Product: '<S33>/Product3' incorporates:
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Sum_o = (real32_T)localDW->SignCorrected_o * 6.10351562E-5F *
    localDW->re_lim_b;

  /* DataTypeConversion: '<S92>/CastU16En16' */
  localDW->CastU16En16_jv = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S92>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 32768);

  /* Switch: '<S92>/QuadHandle1' incorporates:
   *  Constant: '<S92>/Point50'
   *  Sum: '<S92>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp - 32768);
  }

  /* End of Switch: '<S92>/QuadHandle1' */

  /* Switch: '<S92>/QuadHandle2' incorporates:
   *  Constant: '<S92>/Point50'
   *  RelationalOperator: '<S92>/LTEp25'
   *  Sum: '<S92>/p50mA'
   *  Switch: '<S105>/QuadHandle2'
   *  Switch: '<S92>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S92>/QuadHandle2' */

  /* Lookup_n-D: '<S91>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S92>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S91>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S92>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S92>/SignCorrected' */

  /* Sum: '<S33>/Sum' incorporates:
   *  Gain: '<S33>/Gain3'
   *  Product: '<S33>/Product2'
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Sum_o += (real32_T)(-32768 * localDW->SignCorrected_o) *
    1.86264515E-9F * localDW->im_lim_k;

  /* DataTypeConversion: '<S99>/CastU16En16' incorporates:
   *  Constant: '<S34>/Constant1'
   *  DataTypeConversion: '<S105>/CastU16En16'
   *  Gain: '<S34>/Gain5'
   *  Product: '<S34>/Product4'
   */
  localDW->rtb_CastU16En16_jv_tmp = (uint16_T)(localDW->theta_e * 6.0F *
    0.159154937F * 65536.0F);

  /* RelationalOperator: '<S99>/LTEp25' incorporates:
   *  DataTypeConversion: '<S99>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 16384);

  /* RelationalOperator: '<S99>/GTEp75' incorporates:
   *  DataTypeConversion: '<S99>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->rtb_CastU16En16_jv_tmp >= 49152);

  /* Switch: '<S99>/QuadHandle2' incorporates:
   *  Constant: '<S99>/Point75'
   *  DataTypeConversion: '<S99>/CastU16En16'
   *  RelationalOperator: '<S99>/LTEp50'
   *  Sum: '<S99>/p75mA'
   *  Switch: '<S99>/QuadHandle1b'
   */
  if (localDW->rtb_CastU16En16_jv_tmp <= 32768) {
    /* Switch: '<S99>/QuadHandle1a' incorporates:
     *  Constant: '<S99>/Point25'
     *  Sum: '<S99>/Amp25'
     *  Sum: '<S99>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 -
        localDW->rtb_CastU16En16_jv_tmp);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp
        - 16384);
    }

    /* End of Switch: '<S99>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S99>/QuadHandle1b' incorporates:
     *  Constant: '<S99>/Point75'
     *  Sum: '<S99>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp -
      49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 -
      localDW->rtb_CastU16En16_jv_tmp);
  }

  /* End of Switch: '<S99>/QuadHandle2' */

  /* Lookup_n-D: '<S98>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S99>/SignCorrected' incorporates:
   *  Logic: '<S99>/1st or 4th Quad'
   *  Lookup_n-D: '<S98>/Look-Up Table'
   *  Switch: '<S105>/SignCorrected'
   *  UnaryMinus: '<S99>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S99>/SignCorrected' */

  /* DataTypeConversion: '<S101>/CastU16En16' incorporates:
   *  Constant: '<S34>/Constant1'
   *  DataTypeConversion: '<S103>/CastU16En16'
   *  Gain: '<S34>/Gain4'
   *  Product: '<S34>/Product5'
   */
  localDW->CastU16En16_jv = (uint16_T)(localDW->Delay1_m * 6.0F * 0.159154937F *
    65536.0F);

  /* RelationalOperator: '<S101>/LTEp25' incorporates:
   *  DataTypeConversion: '<S101>/CastU16En16'
   */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv <= 16384);

  /* RelationalOperator: '<S101>/GTEp75' incorporates:
   *  DataTypeConversion: '<S101>/CastU16En16'
   */
  localDW->GTEp75_o = (localDW->CastU16En16_jv >= 49152);

  /* Switch: '<S101>/QuadHandle2' incorporates:
   *  Constant: '<S101>/Point75'
   *  DataTypeConversion: '<S101>/CastU16En16'
   *  RelationalOperator: '<S101>/LTEp50'
   *  Sum: '<S101>/p75mA'
   *  Switch: '<S101>/QuadHandle1b'
   */
  if (localDW->CastU16En16_jv <= 32768) {
    /* Switch: '<S101>/QuadHandle1a' incorporates:
     *  Constant: '<S101>/Point25'
     *  Sum: '<S101>/Amp25'
     *  Sum: '<S101>/p25mA'
     */
    if (localDW->GTEp75_cz) {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(16384 - localDW->CastU16En16_jv);
    } else {
      localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 16384);
    }

    /* End of Switch: '<S101>/QuadHandle1a' */
  } else if (localDW->GTEp75_o) {
    /* Switch: '<S101>/QuadHandle1b' incorporates:
     *  Constant: '<S101>/Point75'
     *  Sum: '<S101>/Amp75'
     */
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(localDW->CastU16En16_jv - 49152);
  } else {
    localDW->rtb_CastU16En16_jv_m = (uint16_T)(49152 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S101>/QuadHandle2' */

  /* Lookup_n-D: '<S100>/Look-Up Table' */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->rtb_CastU16En16_jv_m,
    0U, 16384U, &localDW->frac);

  /* Switch: '<S101>/SignCorrected' incorporates:
   *  Logic: '<S101>/1st or 4th Quad'
   *  Lookup_n-D: '<S100>/Look-Up Table'
   *  Switch: '<S103>/SignCorrected'
   *  UnaryMinus: '<S101>/Negate'
   */
  if (localDW->GTEp75_cz || localDW->GTEp75_o) {
    localDW->SignCorrected_cw = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_cw = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S101>/SignCorrected' */

  /* Product: '<S34>/Product1' incorporates:
   *  Switch: '<S103>/SignCorrected'
   */
  localDW->im_lim_o4 = (real32_T)localDW->SignCorrected_cw * 6.10351562E-5F *
    localDW->re_lim_g;

  /* Gain: '<S34>/Gain1' incorporates:
   *  Delay: '<S34>/Delay1'
   *  Sum: '<S34>/Sum4'
   */
  localDW->theta_e = 2.5E-5F * rtP.K6 * (localDW->Delay1_DSTATE_i +
    localDW->im_lim_o4);

  /* DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->Delay1_m = 0.5F * localDW->theta_e +
    localDW->DiscreteTimeIntegrator_DSTAT_if;

  /* Sum: '<S34>/Sum5' */
  localDW->U_re_b = localDW->Delay1_m + localDW->im_lim_o4;

  /* RelationalOperator: '<S103>/LTEp50' */
  localDW->GTEp75_cz = (localDW->CastU16En16_jv <= 32768);

  /* Switch: '<S103>/QuadHandle1' incorporates:
   *  Constant: '<S103>/Point50'
   *  Sum: '<S103>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->CastU16En16_jv - 32768);
  }

  /* End of Switch: '<S103>/QuadHandle1' */

  /* Switch: '<S103>/QuadHandle2' incorporates:
   *  Constant: '<S103>/Point50'
   *  RelationalOperator: '<S103>/LTEp25'
   *  Sum: '<S103>/p50mA'
   *  Switch: '<S103>/QuadHandle1'
   *  Switch: '<S105>/QuadHandle2'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S103>/QuadHandle2' */

  /* Lookup_n-D: '<S102>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S103>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S102>/Look-Up Table'
   *  UnaryMinus: '<S103>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_cw = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_cw = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S103>/SignCorrected' */

  /* Product: '<S34>/Product' incorporates:
   *  Gain: '<S34>/Gain'
   *  Switch: '<S103>/SignCorrected'
   */
  localDW->re_lim_g *= (real32_T)(-32768 * localDW->SignCorrected_cw) *
    1.86264515E-9F;

  /* Gain: '<S34>/Gain2' incorporates:
   *  Delay: '<S34>/Delay'
   *  Sum: '<S34>/Sum2'
   */
  localDW->Gain2_m = 2.5E-5F * rtP.K6 * (localDW->re_lim_g +
    localDW->Delay_DSTATE_h);

  /* DiscreteIntegrator: '<S34>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_h = 0.5F * localDW->Gain2_m +
    localDW->DiscreteTimeIntegrator1_DSTAT_a;

  /* Sum: '<S34>/Sum6' */
  localDW->U_im_f = localDW->re_lim_g + localDW->DiscreteTimeIntegrator1_h;

  /* MATLAB Function: '<S34>/MATLAB Function' incorporates:
   *  Constant: '<S34>/Constant2'
   *  Product: '<S34>/Product6'
   */
  MATLABFunction_a(localDW->U_re_b, 0.01F * rtu_U_ZK1, localDW->LTEp25_my,
                   localDW->U_im_f, &localDW->re_lim_g, &localDW->im_lim_o4);

  /* Product: '<S34>/Product3' incorporates:
   *  Switch: '<S105>/SignCorrected'
   */
  localDW->Sum_d = (real32_T)localDW->SignCorrected_o * 6.10351562E-5F *
    localDW->re_lim_g;

  /* DataTypeConversion: '<S105>/CastU16En16' */
  localDW->CastU16En16_jv = localDW->rtb_CastU16En16_jv_tmp;

  /* RelationalOperator: '<S105>/LTEp50' */
  localDW->GTEp75_cz = (localDW->rtb_CastU16En16_jv_tmp <= 32768);

  /* Switch: '<S105>/QuadHandle1' incorporates:
   *  Constant: '<S105>/Point50'
   *  Sum: '<S105>/Amp50'
   */
  if (!localDW->GTEp75_cz) {
    localDW->CastU16En16_jv = (uint16_T)(localDW->rtb_CastU16En16_jv_tmp - 32768);
  }

  /* End of Switch: '<S105>/QuadHandle1' */

  /* Switch: '<S105>/QuadHandle2' incorporates:
   *  Constant: '<S105>/Point50'
   *  RelationalOperator: '<S105>/LTEp25'
   *  Sum: '<S105>/p50mA'
   *  Switch: '<S105>/QuadHandle1'
   */
  if (localDW->CastU16En16_jv > 16384) {
    localDW->CastU16En16_jv = (uint16_T)(32768 - localDW->CastU16En16_jv);
  }

  /* End of Switch: '<S105>/QuadHandle2' */

  /* Lookup_n-D: '<S104>/Look-Up Table' incorporates:
   *  Switch: '<S105>/QuadHandle2'
   */
  localDW->bpIdx = plook_u32u16u64n48_even0c_gf(localDW->CastU16En16_jv, 0U,
    16384U, &localDW->frac);

  /* Switch: '<S105>/SignCorrected' incorporates:
   *  Lookup_n-D: '<S104>/Look-Up Table'
   *  UnaryMinus: '<S105>/Negate'
   */
  if (localDW->GTEp75_cz) {
    localDW->SignCorrected_o = intrp1d_s16s32s32u32u64n48l_f(localDW->bpIdx,
      localDW->frac, rtConstP.pooled18);
  } else {
    localDW->SignCorrected_o = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
      (localDW->bpIdx, localDW->frac, rtConstP.pooled18);
  }

  /* End of Switch: '<S105>/SignCorrected' */

  /* Sum: '<S23>/Add' incorporates:
   *  Constant: '<S23>/Constant1'
   *  Gain: '<S34>/Gain3'
   *  Product: '<S23>/Divide'
   *  Product: '<S34>/Product2'
   *  Sum: '<S23>/Add1'
   *  Sum: '<S34>/Sum'
   *  Switch: '<S105>/SignCorrected'
   */
  *rty_a = (((real32_T)(-32768 * localDW->SignCorrected_o) * 1.86264515E-9F *
             localDW->im_lim_o4 + localDW->Sum_d) + ((localDW->Add1_l +
              localDW->Sum_j) + localDW->Sum_o)) / rtu_U_ZK1 + 0.5F;

  /* SignalConversion generated from: '<S23>/I_ref1' */
  *rty_I_ref1 = localDW->Strom_kompensiert_l;

  /* Update for Delay: '<S31>/Delay1' incorporates:
   *  Sum: '<S31>/Sum3'
   */
  localDW->Delay1_DSTATE = localDW->re_lim_l - localDW->U_re_o;

  /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = 0.5F * localDW->Gain1_h +
    localDW->DiscreteTimeIntegrator;

  /* Update for Delay: '<S31>/Delay' incorporates:
   *  Sum: '<S31>/Sum1'
   */
  localDW->Delay_DSTATE = localDW->im_lim_mv - localDW->U_im_i;

  /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = 0.5F * localDW->Gain2_nl +
    localDW->DiscreteTimeIntegrator1;

  /* Update for Delay: '<S32>/Delay1' incorporates:
   *  Sum: '<S32>/Sum3'
   */
  localDW->Delay1_DSTATE_m = localDW->re_lim_i - localDW->U_re_h;

  /* Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_d = 0.5F * localDW->Gain1_g +
    localDW->DiscreteTimeIntegrator_o;

  /* Update for Delay: '<S32>/Delay' incorporates:
   *  Sum: '<S32>/Sum1'
   */
  localDW->Delay_DSTATE_a = localDW->im_lim_l - localDW->U_im_pl;

  /* Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTAT_m = 0.5F * localDW->Gain2_d +
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
  localDW->DiscreteTimeIntegrator1_DSTAT_k = 0.5F * localDW->Gain2_e +
    localDW->DiscreteTimeIntegrator1_e;

  /* Update for Delay: '<S34>/Delay1' incorporates:
   *  Sum: '<S34>/Sum3'
   */
  localDW->Delay1_DSTATE_i = localDW->re_lim_g - localDW->U_re_b;

  /* Update for DiscreteIntegrator: '<S34>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_if = 0.5F * localDW->theta_e +
    localDW->Delay1_m;

  /* Update for Delay: '<S34>/Delay' incorporates:
   *  Sum: '<S34>/Sum1'
   */
  localDW->Delay_DSTATE_h = localDW->im_lim_o4 - localDW->U_im_f;

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

    /* SwitchCase: '<S11>/Switch Case' incorporates:
     *  Inport: '<Root>/fl_enable_compensation_cogging_torque'
     */
    if (rtU->fl_enable_compensation_cogging_ == 1) {
      /* Outputs for IfAction SubSystem: '<S11>/Rastmomentkompensation' incorporates:
       *  ActionPort: '<S260>/Action Port'
       */
      /* DataTypeConversion: '<S269>/CastU16En16' incorporates:
       *  Gain: '<S260>/Gain1'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/ordnung_a'
       *  Inport: '<Root>/phase_a'
       *  Product: '<S260>/Product8'
       *  Sum: '<S260>/Add9'
       */
      rtDW->CastU16En16_h = (uint16_T)((rtU->ordnung_a * rtU->Act_theta_u_el +
        rtU->phase_a) * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S269>/LTEp50' incorporates:
       *  DataTypeConversion: '<S269>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S269>/QuadHandle1' incorporates:
       *  Constant: '<S269>/Point50'
       *  DataTypeConversion: '<S269>/CastU16En16'
       *  Sum: '<S269>/Amp50'
       */
      if (!rtDW->LTEp50_j) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S269>/QuadHandle1' */

      /* Switch: '<S269>/QuadHandle2' incorporates:
       *  Constant: '<S269>/Point50'
       *  RelationalOperator: '<S269>/LTEp25'
       *  Sum: '<S269>/p50mA'
       *  Switch: '<S269>/QuadHandle1'
       *  Switch: '<S273>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S269>/QuadHandle2' */

      /* Lookup_n-D: '<S268>/Look-Up Table' incorporates:
       *  Switch: '<S273>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S269>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S268>/Look-Up Table'
       *  Switch: '<S273>/SignCorrected'
       *  UnaryMinus: '<S269>/Negate'
       */
      if (rtDW->LTEp50_j) {
        rtDW->SignCorrected_a = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_a = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S269>/SignCorrected' */

      /* Product: '<S260>/Product7' incorporates:
       *  Inport: '<Root>/amplitude_a'
       *  Switch: '<S273>/SignCorrected'
       */
      rtDW->c = (real32_T)rtDW->SignCorrected_a * 6.10351562E-5F *
        rtU->amplitude_a;

      /* DataTypeConversion: '<S267>/CastU16En16' incorporates:
       *  Gain: '<S260>/Gain'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/ordnung_b'
       *  Inport: '<Root>/phase_b'
       *  Product: '<S260>/Product9'
       *  Sum: '<S260>/Add7'
       */
      rtDW->CastU16En16_h = (uint16_T)((rtU->ordnung_b * rtU->Act_theta_u_el +
        rtU->phase_b) * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S267>/LTEp50' incorporates:
       *  DataTypeConversion: '<S267>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S267>/QuadHandle1' incorporates:
       *  Constant: '<S267>/Point50'
       *  DataTypeConversion: '<S267>/CastU16En16'
       *  Sum: '<S267>/Amp50'
       */
      if (!rtDW->LTEp50_j) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S267>/QuadHandle1' */

      /* Switch: '<S267>/QuadHandle2' incorporates:
       *  Constant: '<S267>/Point50'
       *  RelationalOperator: '<S267>/LTEp25'
       *  Sum: '<S267>/p50mA'
       *  Switch: '<S267>/QuadHandle1'
       *  Switch: '<S273>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S267>/QuadHandle2' */

      /* Lookup_n-D: '<S266>/Look-Up Table' incorporates:
       *  Switch: '<S273>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S267>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S266>/Look-Up Table'
       *  Switch: '<S273>/SignCorrected'
       *  UnaryMinus: '<S267>/Negate'
       */
      if (rtDW->LTEp50_j) {
        rtDW->SignCorrected_a = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_a = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S267>/SignCorrected' */

      /* Product: '<S260>/Product4' incorporates:
       *  Inport: '<Root>/amplitude_b'
       *  Switch: '<S273>/SignCorrected'
       */
      rtDW->a = (real32_T)rtDW->SignCorrected_a * 6.10351562E-5F *
        rtU->amplitude_b;

      /* DataTypeConversion: '<S271>/CastU16En16' incorporates:
       *  Gain: '<S260>/Gain2'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/ordnung_c'
       *  Inport: '<Root>/phase_c'
       *  Product: '<S260>/Product10'
       *  Sum: '<S260>/Add8'
       */
      rtDW->CastU16En16_h = (uint16_T)((rtU->ordnung_c * rtU->Act_theta_u_el +
        rtU->phase_c) * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S271>/LTEp50' incorporates:
       *  DataTypeConversion: '<S271>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S271>/QuadHandle1' incorporates:
       *  Constant: '<S271>/Point50'
       *  DataTypeConversion: '<S271>/CastU16En16'
       *  Sum: '<S271>/Amp50'
       */
      if (!rtDW->LTEp50_j) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S271>/QuadHandle1' */

      /* Switch: '<S271>/QuadHandle2' incorporates:
       *  Constant: '<S271>/Point50'
       *  RelationalOperator: '<S271>/LTEp25'
       *  Sum: '<S271>/p50mA'
       *  Switch: '<S271>/QuadHandle1'
       *  Switch: '<S273>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S271>/QuadHandle2' */

      /* Lookup_n-D: '<S270>/Look-Up Table' incorporates:
       *  Switch: '<S273>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S271>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S270>/Look-Up Table'
       *  Switch: '<S273>/SignCorrected'
       *  UnaryMinus: '<S271>/Negate'
       */
      if (rtDW->LTEp50_j) {
        rtDW->SignCorrected_a = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_a = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S271>/SignCorrected' */

      /* Product: '<S260>/Product6' incorporates:
       *  Inport: '<Root>/amplitude_c'
       *  Switch: '<S273>/SignCorrected'
       */
      rtDW->b = (real32_T)rtDW->SignCorrected_a * 6.10351562E-5F *
        rtU->amplitude_c;

      /* DataTypeConversion: '<S273>/CastU16En16' incorporates:
       *  Gain: '<S260>/Gain3'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Inport: '<Root>/ordnung_d'
       *  Inport: '<Root>/phase_d'
       *  Product: '<S260>/Product11'
       *  Sum: '<S260>/Add6'
       */
      rtDW->CastU16En16_h = (uint16_T)((rtU->ordnung_d * rtU->Act_theta_u_el +
        rtU->phase_d) * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S273>/LTEp50' incorporates:
       *  DataTypeConversion: '<S273>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S273>/QuadHandle1' incorporates:
       *  Constant: '<S273>/Point50'
       *  DataTypeConversion: '<S273>/CastU16En16'
       *  Sum: '<S273>/Amp50'
       */
      if (!rtDW->LTEp50_j) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S273>/QuadHandle1' */

      /* Switch: '<S273>/QuadHandle2' incorporates:
       *  Constant: '<S273>/Point50'
       *  RelationalOperator: '<S273>/LTEp25'
       *  Sum: '<S273>/p50mA'
       *  Switch: '<S273>/QuadHandle1'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S273>/QuadHandle2' */

      /* Lookup_n-D: '<S272>/Look-Up Table' incorporates:
       *  Switch: '<S273>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S273>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S272>/Look-Up Table'
       *  UnaryMinus: '<S273>/Negate'
       */
      if (rtDW->LTEp50_j) {
        rtDW->SignCorrected_a = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_a = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S273>/SignCorrected' */

      /* Sum: '<S260>/Add5' incorporates:
       *  Inport: '<Root>/amplitude_d'
       *  Product: '<S260>/Product5'
       *  Switch: '<S273>/SignCorrected'
       */
      rtDW->c = ((rtDW->c + rtDW->a) + rtDW->b) + (real32_T)
        rtDW->SignCorrected_a * 6.10351562E-5F * rtU->amplitude_d;

      /* End of Outputs for SubSystem: '<S11>/Rastmomentkompensation' */
    } else {
      /* Outputs for IfAction SubSystem: '<S11>/Switch Case Action Subsystem' incorporates:
       *  ActionPort: '<S261>/Action Port'
       */
      /* SignalConversion generated from: '<S261>/In1' incorporates:
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
         *  Delay: '<S185>/Delay'
         *  Delay: '<S185>/Delay1'
         *  Delay: '<S186>/Delay'
         *  Delay: '<S186>/Delay1'
         *  Delay: '<S187>/Delay'
         *  Delay: '<S187>/Delay1'
         *  Delay: '<S188>/Delay'
         *  Delay: '<S188>/Delay1'
         *  DiscreteIntegrator: '<S185>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S185>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S186>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S186>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S187>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S187>/Discrete-Time Integrator1'
         *  DiscreteIntegrator: '<S188>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S188>/Discrete-Time Integrator1'
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
      rtDW->theta_b = rtDW->c + -4.18879032F;

      /* Gain: '<S185>/Gain5' incorporates:
       *  Constant: '<S25>/Constant'
       *  Sum: '<S25>/Sum1'
       */
      rtDW->c = (rtDW->c + -4.18879032F) * 0.159154937F;

      /* DataTypeConversion: '<S214>/CastU16En16' */
      rtDW->CastU16En16_h = (uint16_T)(rtDW->c * 65536.0F);

      /* RelationalOperator: '<S214>/LTEp25' incorporates:
       *  DataTypeConversion: '<S214>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 16384);

      /* RelationalOperator: '<S214>/GTEp75' incorporates:
       *  DataTypeConversion: '<S214>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h >= 49152);

      /* Switch: '<S214>/QuadHandle2' incorporates:
       *  Constant: '<S214>/Point75'
       *  DataTypeConversion: '<S214>/CastU16En16'
       *  RelationalOperator: '<S214>/LTEp50'
       *  Sum: '<S214>/p75mA'
       *  Switch: '<S214>/QuadHandle1b'
       */
      if (rtDW->CastU16En16_h <= 32768) {
        /* Switch: '<S214>/QuadHandle1a' incorporates:
         *  Constant: '<S214>/Point25'
         *  Sum: '<S214>/Amp25'
         *  Sum: '<S214>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->CastU16En16_h = (uint16_T)(16384 - rtDW->CastU16En16_h);
        } else {
          rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 16384);
        }

        /* End of Switch: '<S214>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S214>/QuadHandle1b' incorporates:
         *  Constant: '<S214>/Point75'
         *  Sum: '<S214>/Amp75'
         */
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 49152);
      } else {
        rtDW->CastU16En16_h = (uint16_T)(49152 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S214>/QuadHandle2' */

      /* Lookup_n-D: '<S213>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S214>/SignCorrected' incorporates:
       *  Logic: '<S214>/1st or 4th Quad'
       *  Lookup_n-D: '<S213>/Look-Up Table'
       *  UnaryMinus: '<S214>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_a = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_a = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S214>/SignCorrected' */

      /* DataTypeConversion: '<S216>/CastU16En16' incorporates:
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S197>/CastU16En16'
       *  Gain: '<S185>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Sum'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint16_T)((rtU->Act_theta_u_el +
        -4.18879032F) * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S216>/LTEp25' incorporates:
       *  DataTypeConversion: '<S216>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 16384);

      /* RelationalOperator: '<S216>/GTEp75' incorporates:
       *  DataTypeConversion: '<S216>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 49152);

      /* Switch: '<S216>/QuadHandle2' incorporates:
       *  Constant: '<S216>/Point75'
       *  DataTypeConversion: '<S216>/CastU16En16'
       *  RelationalOperator: '<S216>/LTEp50'
       *  Sum: '<S216>/p75mA'
       *  Switch: '<S216>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768) {
        /* Switch: '<S216>/QuadHandle1a' incorporates:
         *  Constant: '<S216>/Point25'
         *  Sum: '<S216>/Amp25'
         *  Sum: '<S216>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->CastU16En16_h = (uint16_T)(16384 -
            rtDW->rtb_CastU16En16_h_tmp_tmp);
        } else {
          rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp -
            16384);
        }

        /* End of Switch: '<S216>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S216>/QuadHandle1b' incorporates:
         *  Constant: '<S216>/Point75'
         *  Sum: '<S216>/Amp75'
         */
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 49152);
      } else {
        rtDW->CastU16En16_h = (uint16_T)(49152 - rtDW->rtb_CastU16En16_h_tmp_tmp);
      }

      /* End of Switch: '<S216>/QuadHandle2' */

      /* Lookup_n-D: '<S215>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S216>/SignCorrected' incorporates:
       *  Logic: '<S216>/1st or 4th Quad'
       *  Lookup_n-D: '<S215>/Look-Up Table'
       *  Switch: '<S257>/SignCorrected'
       *  UnaryMinus: '<S216>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_c = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S216>/SignCorrected' */

      /* MATLAB Function: '<S184>/MATLAB Function' incorporates:
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
                       &rtDW->Sum_cr, &rtDW->sf_MATLABFunction_e);

      /* DataTypeConversion: '<S197>/CastU16En16' incorporates:
       *  DataTypeConversion: '<S203>/CastU16En16'
       */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S197>/LTEp25' */
      rtDW->LTEp50_j = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 16384);

      /* RelationalOperator: '<S197>/GTEp75' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 49152);

      /* Switch: '<S197>/QuadHandle2' incorporates:
       *  Constant: '<S197>/Point75'
       *  RelationalOperator: '<S197>/LTEp50'
       *  Sum: '<S197>/p75mA'
       *  Switch: '<S197>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768) {
        /* Switch: '<S197>/QuadHandle1a' incorporates:
         *  Constant: '<S197>/Point25'
         *  Sum: '<S197>/Amp25'
         *  Sum: '<S197>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(16384 -
            rtDW->rtb_CastU16En16_h_tmp_tmp);
        } else {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp
            - 16384);
        }

        /* End of Switch: '<S197>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S197>/QuadHandle1b' incorporates:
         *  Constant: '<S197>/Point75'
         *  Sum: '<S197>/Amp75'
         */
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp -
          49152);
      } else {
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(49152 -
          rtDW->rtb_CastU16En16_h_tmp_tmp);
      }

      /* End of Switch: '<S197>/QuadHandle2' */

      /* Lookup_n-D: '<S196>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->rtb_CastU16En16_h_m, 0U,
        16384U, &rtDW->frac);

      /* Switch: '<S197>/SignCorrected' incorporates:
       *  Logic: '<S197>/1st or 4th Quad'
       *  Lookup_n-D: '<S196>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S197>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S197>/SignCorrected' */

      /* Product: '<S184>/Product' incorporates:
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Strom_kompensiert = (real32_T)rtDW->SignCorrected_d * 6.10351562E-5F
        * rtDW->b;

      /* RelationalOperator: '<S203>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768);

      /* Switch: '<S203>/QuadHandle1' incorporates:
       *  Constant: '<S203>/Point50'
       *  Sum: '<S203>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 32768);
      }

      /* End of Switch: '<S203>/QuadHandle1' */

      /* Switch: '<S203>/QuadHandle2' incorporates:
       *  Constant: '<S203>/Point50'
       *  RelationalOperator: '<S203>/LTEp25'
       *  Sum: '<S203>/p50mA'
       *  Switch: '<S203>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S203>/QuadHandle2' */

      /* Lookup_n-D: '<S202>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S203>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S202>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S203>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S203>/SignCorrected' */

      /* Product: '<S184>/Product1' incorporates:
       *  Gain: '<S184>/Gain'
       *  Sum: '<S184>/Add'
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->re_lim_e = (real32_T)(-32768 * rtDW->SignCorrected_d) *
        1.86264515E-9F * (rtDW->Merge + rtDW->Gain1);

      /* DataTypeConversion: '<S199>/CastU16En16' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S25>/Constant2'
       *  DataTypeConversion: '<S205>/CastU16En16'
       *  Gain: '<S184>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Add2'
       *  Sum: '<S25>/Sum'
       */
      rtDW->CastU16En16_h = (uint16_T)(((rtU->Act_theta_u_el + -4.18879032F) +
        -4.18879032F) * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S199>/LTEp25' incorporates:
       *  DataTypeConversion: '<S199>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 16384);

      /* RelationalOperator: '<S199>/GTEp75' incorporates:
       *  DataTypeConversion: '<S199>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h >= 49152);

      /* Switch: '<S199>/QuadHandle2' incorporates:
       *  Constant: '<S199>/Point75'
       *  DataTypeConversion: '<S199>/CastU16En16'
       *  RelationalOperator: '<S199>/LTEp50'
       *  Sum: '<S199>/p75mA'
       *  Switch: '<S199>/QuadHandle1b'
       */
      if (rtDW->CastU16En16_h <= 32768) {
        /* Switch: '<S199>/QuadHandle1a' incorporates:
         *  Constant: '<S199>/Point25'
         *  Sum: '<S199>/Amp25'
         *  Sum: '<S199>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(16384 - rtDW->CastU16En16_h);
        } else {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 16384);
        }

        /* End of Switch: '<S199>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S199>/QuadHandle1b' incorporates:
         *  Constant: '<S199>/Point75'
         *  Sum: '<S199>/Amp75'
         */
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 49152);
      } else {
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(49152 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S199>/QuadHandle2' */

      /* Lookup_n-D: '<S198>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->rtb_CastU16En16_h_m, 0U,
        16384U, &rtDW->frac);

      /* Switch: '<S199>/SignCorrected' incorporates:
       *  Logic: '<S199>/1st or 4th Quad'
       *  Lookup_n-D: '<S198>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S199>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S199>/SignCorrected' */

      /* Product: '<S184>/Product2' incorporates:
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->b = (real32_T)rtDW->SignCorrected_d * 6.10351562E-5F * rtDW->y_i;

      /* RelationalOperator: '<S205>/LTEp50' */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S205>/QuadHandle1' incorporates:
       *  Constant: '<S205>/Point50'
       *  Sum: '<S205>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S205>/QuadHandle1' */

      /* Switch: '<S205>/QuadHandle2' incorporates:
       *  Constant: '<S205>/Point50'
       *  RelationalOperator: '<S205>/LTEp25'
       *  Sum: '<S205>/p50mA'
       *  Switch: '<S205>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S205>/QuadHandle2' */

      /* Lookup_n-D: '<S204>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S205>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S204>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S205>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S205>/SignCorrected' */

      /* Product: '<S184>/Product3' incorporates:
       *  Gain: '<S184>/Gain1'
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Sum_a5 = (real32_T)(-32768 * rtDW->SignCorrected_d) * 1.86264515E-9F
        * rtDW->y;

      /* DataTypeConversion: '<S201>/CastU16En16' incorporates:
       *  Constant: '<S25>/Constant'
       *  Constant: '<S25>/Constant3'
       *  DataTypeConversion: '<S207>/CastU16En16'
       *  Gain: '<S184>/Gain5'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Sum: '<S25>/Add3'
       *  Sum: '<S25>/Sum'
       */
      rtDW->CastU16En16_h = (uint16_T)(((rtU->Act_theta_u_el + -4.18879032F) +
        4.18879032F) * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S201>/LTEp25' incorporates:
       *  DataTypeConversion: '<S201>/CastU16En16'
       */
      rtDW->LTEp50_j = (rtDW->CastU16En16_h <= 16384);

      /* RelationalOperator: '<S201>/GTEp75' incorporates:
       *  DataTypeConversion: '<S201>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h >= 49152);

      /* Switch: '<S201>/QuadHandle2' incorporates:
       *  Constant: '<S201>/Point75'
       *  DataTypeConversion: '<S201>/CastU16En16'
       *  RelationalOperator: '<S201>/LTEp50'
       *  Sum: '<S201>/p75mA'
       *  Switch: '<S201>/QuadHandle1b'
       */
      if (rtDW->CastU16En16_h <= 32768) {
        /* Switch: '<S201>/QuadHandle1a' incorporates:
         *  Constant: '<S201>/Point25'
         *  Sum: '<S201>/Amp25'
         *  Sum: '<S201>/p25mA'
         */
        if (rtDW->LTEp50_j) {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(16384 - rtDW->CastU16En16_h);
        } else {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 16384);
        }

        /* End of Switch: '<S201>/QuadHandle1a' */
      } else if (rtDW->GTEp75) {
        /* Switch: '<S201>/QuadHandle1b' incorporates:
         *  Constant: '<S201>/Point75'
         *  Sum: '<S201>/Amp75'
         */
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 49152);
      } else {
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(49152 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S201>/QuadHandle2' */

      /* Lookup_n-D: '<S200>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->rtb_CastU16En16_h_m, 0U,
        16384U, &rtDW->frac);

      /* Switch: '<S201>/SignCorrected' incorporates:
       *  Logic: '<S201>/1st or 4th Quad'
       *  Lookup_n-D: '<S200>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S201>/Negate'
       */
      if (rtDW->LTEp50_j || rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S201>/SignCorrected' */

      /* Product: '<S184>/Product4' incorporates:
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Sum_a = (real32_T)rtDW->SignCorrected_d * 6.10351562E-5F *
        rtDW->Switch2;

      /* RelationalOperator: '<S207>/LTEp50' */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S207>/QuadHandle1' incorporates:
       *  Constant: '<S207>/Point50'
       *  Sum: '<S207>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S207>/QuadHandle1' */

      /* Switch: '<S207>/QuadHandle2' incorporates:
       *  Constant: '<S207>/Point50'
       *  RelationalOperator: '<S207>/LTEp25'
       *  Sum: '<S207>/p50mA'
       *  Switch: '<S207>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S207>/QuadHandle2' */

      /* Lookup_n-D: '<S206>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S207>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S206>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S207>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S207>/SignCorrected' */

      /* Sum: '<S184>/Strom_kompensiert' incorporates:
       *  Gain: '<S184>/Gain2'
       *  Product: '<S184>/Product5'
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Strom_kompensiert = ((((rtDW->Strom_kompensiert + rtDW->re_lim_e) +
        rtDW->b) + rtDW->Sum_a5) + rtDW->Sum_a) + (real32_T)(-32768 *
        rtDW->SignCorrected_d) * 1.86264515E-9F * rtDW->Sum_cr;

      /* Gain: '<S185>/Gain6' incorporates:
       *  Gain: '<S186>/Gain6'
       *  Gain: '<S187>/Gain6'
       *  Gain: '<S188>/Gain6'
       *  Inport: '<Root>/Act_Iw'
       *  Sum: '<S25>/Sum2'
       */
      rtDW->re_lim_e = (rtDW->Strom_kompensiert - rtU->Act_Iw) * rtP.Kp;

      /* Product: '<S185>/Product1' incorporates:
       *  Gain: '<S185>/Gain6'
       *  Switch: '<S257>/SignCorrected'
       */
      rtDW->b = (real32_T)rtDW->SignCorrected_c * 6.10351562E-5F *
        rtDW->re_lim_e;

      /* Gain: '<S185>/Gain1' incorporates:
       *  Delay: '<S185>/Delay1'
       *  Sum: '<S185>/Sum4'
       */
      rtDW->Gain1_k = 2.5E-5F * rtP.K1 * (rtDW->Delay1_DSTATE + rtDW->b);

      /* DiscreteIntegrator: '<S185>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_o = 0.5F * rtDW->Gain1_k +
        rtDW->DiscreteTimeIntegrator_DSTATE_o;

      /* Sum: '<S185>/Sum5' */
      rtDW->U_re = rtDW->DiscreteTimeIntegrator_o + rtDW->b;

      /* MATLAB Function: '<S25>/MATLAB Function' incorporates:
       *  Inport: '<Root>/Act_w_el'
       */
      MATLABFunction(rtDW->Add, rtU->Act_w_el, &rtDW->LTEp50_j);

      /* DataTypeConversion: '<S218>/CastU16En16' incorporates:
       *  DataTypeConversion: '<S216>/CastU16En16'
       */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S218>/LTEp50' incorporates:
       *  DataTypeConversion: '<S216>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768);

      /* Switch: '<S218>/QuadHandle1' incorporates:
       *  Constant: '<S218>/Point50'
       *  DataTypeConversion: '<S216>/CastU16En16'
       *  Sum: '<S218>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 32768);
      }

      /* End of Switch: '<S218>/QuadHandle1' */

      /* Switch: '<S218>/QuadHandle2' incorporates:
       *  Constant: '<S218>/Point50'
       *  RelationalOperator: '<S218>/LTEp25'
       *  Sum: '<S218>/p50mA'
       *  Switch: '<S218>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S218>/QuadHandle2' */

      /* Lookup_n-D: '<S217>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S218>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S217>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S218>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S218>/SignCorrected' */

      /* Product: '<S185>/Product' incorporates:
       *  Gain: '<S185>/Gain'
       *  Gain: '<S185>/Gain6'
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->b = (real32_T)(-32768 * rtDW->SignCorrected_d) * 1.86264515E-9F *
        rtDW->re_lim_e;

      /* Gain: '<S185>/Gain2' incorporates:
       *  Delay: '<S185>/Delay'
       *  Sum: '<S185>/Sum2'
       */
      rtDW->Add = 2.5E-5F * rtP.K1 * (rtDW->b + rtDW->Delay_DSTATE_l);

      /* DiscreteIntegrator: '<S185>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1 = 0.5F * rtDW->Add +
        rtDW->DiscreteTimeIntegrator1_DSTATE;

      /* Sum: '<S185>/Sum6' */
      rtDW->U_im = rtDW->b + rtDW->DiscreteTimeIntegrator1;

      /* MATLAB Function: '<S185>/MATLAB Function' incorporates:
       *  Constant: '<S185>/Constant2'
       *  Product: '<S185>/Product6'
       */
      MATLABFunction_a(rtDW->U_re, 0.46F * rtDW->DiscreteTimeIntegrator,
                       rtDW->LTEp50_j, rtDW->U_im, &rtDW->Gain1, &rtDW->b);

      /* DataTypeConversion: '<S220>/CastU16En16' */
      rtDW->CastU16En16_h = (uint16_T)(rtDW->c * 65536.0F);

      /* RelationalOperator: '<S220>/LTEp50' incorporates:
       *  DataTypeConversion: '<S220>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S220>/QuadHandle1' incorporates:
       *  Constant: '<S220>/Point50'
       *  DataTypeConversion: '<S220>/CastU16En16'
       *  Sum: '<S220>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S220>/QuadHandle1' */

      /* Switch: '<S220>/QuadHandle2' incorporates:
       *  Constant: '<S220>/Point50'
       *  RelationalOperator: '<S220>/LTEp25'
       *  Sum: '<S220>/p50mA'
       *  Switch: '<S220>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S220>/QuadHandle2' */

      /* Lookup_n-D: '<S219>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S220>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S219>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S220>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S220>/SignCorrected' */

      /* Sum: '<S185>/Sum' incorporates:
       *  Gain: '<S185>/Gain3'
       *  Product: '<S185>/Product2'
       *  Product: '<S185>/Product3'
       *  Switch: '<S214>/SignCorrected'
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Add1 = (real32_T)(-32768 * rtDW->SignCorrected_d) * 1.86264515E-9F *
        rtDW->b + (real32_T)rtDW->SignCorrected_a * 6.10351562E-5F * rtDW->Gain1;

      /* DataTypeConversion: '<S227>/CastU16En16' incorporates:
       *  Constant: '<S186>/Constant1'
       *  DataTypeConversion: '<S233>/CastU16En16'
       *  Gain: '<S186>/Gain5'
       *  Product: '<S186>/Product4'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint16_T)(rtDW->theta_b * 2.0F *
        0.159154937F * 65536.0F);

      /* RelationalOperator: '<S227>/LTEp25' incorporates:
       *  DataTypeConversion: '<S227>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 16384);

      /* RelationalOperator: '<S227>/GTEp75' incorporates:
       *  DataTypeConversion: '<S227>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 49152);

      /* Switch: '<S227>/QuadHandle2' incorporates:
       *  Constant: '<S227>/Point75'
       *  DataTypeConversion: '<S227>/CastU16En16'
       *  RelationalOperator: '<S227>/LTEp50'
       *  Sum: '<S227>/p75mA'
       *  Switch: '<S227>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768) {
        /* Switch: '<S227>/QuadHandle1a' incorporates:
         *  Constant: '<S227>/Point25'
         *  Sum: '<S227>/Amp25'
         *  Sum: '<S227>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = (uint16_T)(16384 -
            rtDW->rtb_CastU16En16_h_tmp_tmp);
        } else {
          rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp -
            16384);
        }

        /* End of Switch: '<S227>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S227>/QuadHandle1b' incorporates:
         *  Constant: '<S227>/Point75'
         *  Sum: '<S227>/Amp75'
         */
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 49152);
      } else {
        rtDW->CastU16En16_h = (uint16_T)(49152 - rtDW->rtb_CastU16En16_h_tmp_tmp);
      }

      /* End of Switch: '<S227>/QuadHandle2' */

      /* Lookup_n-D: '<S226>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S227>/SignCorrected' incorporates:
       *  Logic: '<S227>/1st or 4th Quad'
       *  Lookup_n-D: '<S226>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S227>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S227>/SignCorrected' */

      /* DataTypeConversion: '<S229>/CastU16En16' incorporates:
       *  Constant: '<S186>/Constant1'
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S231>/CastU16En16'
       *  Gain: '<S186>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Product: '<S186>/Product5'
       *  Sum: '<S25>/Sum'
       */
      rtDW->CastU16En16_h = (uint16_T)((rtU->Act_theta_u_el + -4.18879032F) *
        2.0F * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S229>/LTEp25' incorporates:
       *  DataTypeConversion: '<S229>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 16384);

      /* RelationalOperator: '<S229>/GTEp75' incorporates:
       *  DataTypeConversion: '<S229>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->CastU16En16_h >= 49152);

      /* Switch: '<S229>/QuadHandle2' incorporates:
       *  Constant: '<S229>/Point75'
       *  DataTypeConversion: '<S229>/CastU16En16'
       *  RelationalOperator: '<S229>/LTEp50'
       *  Sum: '<S229>/p75mA'
       *  Switch: '<S229>/QuadHandle1b'
       */
      if (rtDW->CastU16En16_h <= 32768) {
        /* Switch: '<S229>/QuadHandle1a' incorporates:
         *  Constant: '<S229>/Point25'
         *  Sum: '<S229>/Amp25'
         *  Sum: '<S229>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(16384 - rtDW->CastU16En16_h);
        } else {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 16384);
        }

        /* End of Switch: '<S229>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S229>/QuadHandle1b' incorporates:
         *  Constant: '<S229>/Point75'
         *  Sum: '<S229>/Amp75'
         */
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 49152);
      } else {
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(49152 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S229>/QuadHandle2' */

      /* Lookup_n-D: '<S228>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->rtb_CastU16En16_h_m, 0U,
        16384U, &rtDW->frac);

      /* Switch: '<S229>/SignCorrected' incorporates:
       *  Logic: '<S229>/1st or 4th Quad'
       *  Lookup_n-D: '<S228>/Look-Up Table'
       *  Switch: '<S257>/SignCorrected'
       *  UnaryMinus: '<S229>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_c = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_c = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S229>/SignCorrected' */

      /* Product: '<S186>/Product1' incorporates:
       *  Switch: '<S257>/SignCorrected'
       */
      rtDW->a = (real32_T)rtDW->SignCorrected_c * 6.10351562E-5F *
        rtDW->re_lim_e;

      /* Gain: '<S186>/Gain1' incorporates:
       *  Delay: '<S186>/Delay1'
       *  Sum: '<S186>/Sum4'
       */
      rtDW->Gain1_e = 2.5E-5F * rtP.K2 * (rtDW->Delay1_DSTATE_o + rtDW->a);

      /* DiscreteIntegrator: '<S186>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_k = 0.5F * rtDW->Gain1_e +
        rtDW->DiscreteTimeIntegrator_DSTATE_m;

      /* Sum: '<S186>/Sum5' */
      rtDW->U_re_c = rtDW->DiscreteTimeIntegrator_k + rtDW->a;

      /* RelationalOperator: '<S231>/LTEp50' */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S231>/QuadHandle1' incorporates:
       *  Constant: '<S231>/Point50'
       *  Sum: '<S231>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S231>/QuadHandle1' */

      /* Switch: '<S231>/QuadHandle2' incorporates:
       *  Constant: '<S231>/Point50'
       *  RelationalOperator: '<S231>/LTEp25'
       *  Sum: '<S231>/p50mA'
       *  Switch: '<S231>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S231>/QuadHandle2' */

      /* Lookup_n-D: '<S230>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S231>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S230>/Look-Up Table'
       *  Switch: '<S257>/SignCorrected'
       *  UnaryMinus: '<S231>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_c = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S231>/SignCorrected' */

      /* Product: '<S186>/Product' incorporates:
       *  Gain: '<S186>/Gain'
       *  Switch: '<S257>/SignCorrected'
       */
      rtDW->Sum_a5 = (real32_T)(-32768 * rtDW->SignCorrected_c) * 1.86264515E-9F
        * rtDW->re_lim_e;

      /* Gain: '<S186>/Gain2' incorporates:
       *  Delay: '<S186>/Delay'
       *  Sum: '<S186>/Sum2'
       */
      rtDW->Gain2_n = 2.5E-5F * rtP.K2 * (rtDW->Sum_a5 + rtDW->Delay_DSTATE_nv);

      /* DiscreteIntegrator: '<S186>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_e = 0.5F * rtDW->Gain2_n +
        rtDW->DiscreteTimeIntegrator1_DSTAT_f;

      /* Sum: '<S186>/Sum6' */
      rtDW->U_im_k = rtDW->Sum_a5 + rtDW->DiscreteTimeIntegrator1_e;

      /* MATLAB Function: '<S186>/MATLAB Function' incorporates:
       *  Constant: '<S186>/Constant2'
       *  Product: '<S186>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_c, 0.05F * rtDW->DiscreteTimeIntegrator,
                       rtDW->LTEp50_j, rtDW->U_im_k, &rtDW->y, &rtDW->y_i);

      /* Product: '<S186>/Product3' incorporates:
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Sum_a5 = (real32_T)rtDW->SignCorrected_d * 6.10351562E-5F * rtDW->y;

      /* DataTypeConversion: '<S233>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S233>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768);

      /* Switch: '<S233>/QuadHandle1' incorporates:
       *  Constant: '<S233>/Point50'
       *  Sum: '<S233>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 32768);
      }

      /* End of Switch: '<S233>/QuadHandle1' */

      /* Switch: '<S233>/QuadHandle2' incorporates:
       *  Constant: '<S233>/Point50'
       *  RelationalOperator: '<S233>/LTEp25'
       *  Sum: '<S233>/p50mA'
       *  Switch: '<S233>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S233>/QuadHandle2' */

      /* Lookup_n-D: '<S232>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S233>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S232>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S233>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S233>/SignCorrected' */

      /* Sum: '<S186>/Sum' incorporates:
       *  Gain: '<S186>/Gain3'
       *  Product: '<S186>/Product2'
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Sum_a5 += (real32_T)(-32768 * rtDW->SignCorrected_d) *
        1.86264515E-9F * rtDW->y_i;

      /* DataTypeConversion: '<S240>/CastU16En16' incorporates:
       *  Constant: '<S187>/Constant1'
       *  DataTypeConversion: '<S246>/CastU16En16'
       *  Gain: '<S187>/Gain5'
       *  Product: '<S187>/Product4'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint16_T)(rtDW->theta_b * 4.0F *
        0.159154937F * 65536.0F);

      /* RelationalOperator: '<S240>/LTEp25' incorporates:
       *  DataTypeConversion: '<S240>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 16384);

      /* RelationalOperator: '<S240>/GTEp75' incorporates:
       *  DataTypeConversion: '<S240>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 49152);

      /* Switch: '<S240>/QuadHandle2' incorporates:
       *  Constant: '<S240>/Point75'
       *  DataTypeConversion: '<S240>/CastU16En16'
       *  RelationalOperator: '<S240>/LTEp50'
       *  Sum: '<S240>/p75mA'
       *  Switch: '<S240>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768) {
        /* Switch: '<S240>/QuadHandle1a' incorporates:
         *  Constant: '<S240>/Point25'
         *  Sum: '<S240>/Amp25'
         *  Sum: '<S240>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = (uint16_T)(16384 -
            rtDW->rtb_CastU16En16_h_tmp_tmp);
        } else {
          rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp -
            16384);
        }

        /* End of Switch: '<S240>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S240>/QuadHandle1b' incorporates:
         *  Constant: '<S240>/Point75'
         *  Sum: '<S240>/Amp75'
         */
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 49152);
      } else {
        rtDW->CastU16En16_h = (uint16_T)(49152 - rtDW->rtb_CastU16En16_h_tmp_tmp);
      }

      /* End of Switch: '<S240>/QuadHandle2' */

      /* Lookup_n-D: '<S239>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S240>/SignCorrected' incorporates:
       *  Logic: '<S240>/1st or 4th Quad'
       *  Lookup_n-D: '<S239>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S240>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S240>/SignCorrected' */

      /* DataTypeConversion: '<S242>/CastU16En16' incorporates:
       *  Constant: '<S187>/Constant1'
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S244>/CastU16En16'
       *  Gain: '<S187>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Product: '<S187>/Product5'
       *  Sum: '<S25>/Sum'
       */
      rtDW->CastU16En16_h = (uint16_T)((rtU->Act_theta_u_el + -4.18879032F) *
        4.0F * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S242>/LTEp25' incorporates:
       *  DataTypeConversion: '<S242>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 16384);

      /* RelationalOperator: '<S242>/GTEp75' incorporates:
       *  DataTypeConversion: '<S242>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->CastU16En16_h >= 49152);

      /* Switch: '<S242>/QuadHandle2' incorporates:
       *  Constant: '<S242>/Point75'
       *  DataTypeConversion: '<S242>/CastU16En16'
       *  RelationalOperator: '<S242>/LTEp50'
       *  Sum: '<S242>/p75mA'
       *  Switch: '<S242>/QuadHandle1b'
       */
      if (rtDW->CastU16En16_h <= 32768) {
        /* Switch: '<S242>/QuadHandle1a' incorporates:
         *  Constant: '<S242>/Point25'
         *  Sum: '<S242>/Amp25'
         *  Sum: '<S242>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(16384 - rtDW->CastU16En16_h);
        } else {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 16384);
        }

        /* End of Switch: '<S242>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S242>/QuadHandle1b' incorporates:
         *  Constant: '<S242>/Point75'
         *  Sum: '<S242>/Amp75'
         */
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 49152);
      } else {
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(49152 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S242>/QuadHandle2' */

      /* Lookup_n-D: '<S241>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->rtb_CastU16En16_h_m, 0U,
        16384U, &rtDW->frac);

      /* Switch: '<S242>/SignCorrected' incorporates:
       *  Logic: '<S242>/1st or 4th Quad'
       *  Lookup_n-D: '<S241>/Look-Up Table'
       *  Switch: '<S257>/SignCorrected'
       *  UnaryMinus: '<S242>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_c = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_c = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S242>/SignCorrected' */

      /* Product: '<S187>/Product1' incorporates:
       *  Switch: '<S257>/SignCorrected'
       */
      rtDW->c = (real32_T)rtDW->SignCorrected_c * 6.10351562E-5F *
        rtDW->re_lim_e;

      /* Gain: '<S187>/Gain1' incorporates:
       *  Delay: '<S187>/Delay1'
       *  Sum: '<S187>/Sum4'
       */
      rtDW->Gain1_m = 2.5E-5F * rtP.K4 * (rtDW->Delay1_DSTATE_g + rtDW->c);

      /* DiscreteIntegrator: '<S187>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_a = 0.5F * rtDW->Gain1_m +
        rtDW->DiscreteTimeIntegrator_DSTATE_c;

      /* Sum: '<S187>/Sum5' */
      rtDW->U_re_n = rtDW->DiscreteTimeIntegrator_a + rtDW->c;

      /* RelationalOperator: '<S244>/LTEp50' */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S244>/QuadHandle1' incorporates:
       *  Constant: '<S244>/Point50'
       *  Sum: '<S244>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S244>/QuadHandle1' */

      /* Switch: '<S244>/QuadHandle2' incorporates:
       *  Constant: '<S244>/Point50'
       *  RelationalOperator: '<S244>/LTEp25'
       *  Sum: '<S244>/p50mA'
       *  Switch: '<S244>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S244>/QuadHandle2' */

      /* Lookup_n-D: '<S243>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S244>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S243>/Look-Up Table'
       *  Switch: '<S257>/SignCorrected'
       *  UnaryMinus: '<S244>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_c = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S244>/SignCorrected' */

      /* Product: '<S187>/Product' incorporates:
       *  Gain: '<S187>/Gain'
       *  Switch: '<S257>/SignCorrected'
       */
      rtDW->Sum_cr = (real32_T)(-32768 * rtDW->SignCorrected_c) * 1.86264515E-9F
        * rtDW->re_lim_e;

      /* Gain: '<S187>/Gain2' incorporates:
       *  Delay: '<S187>/Delay'
       *  Sum: '<S187>/Sum2'
       */
      rtDW->Gain2_h = 2.5E-5F * rtP.K4 * (rtDW->Sum_cr + rtDW->Delay_DSTATE_a);

      /* DiscreteIntegrator: '<S187>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_a = 0.5F * rtDW->Gain2_h +
        rtDW->DiscreteTimeIntegrator1_DSTAT_o;

      /* Sum: '<S187>/Sum6' */
      rtDW->U_im_p = rtDW->Sum_cr + rtDW->DiscreteTimeIntegrator1_a;

      /* MATLAB Function: '<S187>/MATLAB Function' incorporates:
       *  Constant: '<S187>/Constant2'
       *  Product: '<S187>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_n, 0.02F * rtDW->DiscreteTimeIntegrator,
                       rtDW->LTEp50_j, rtDW->U_im_p, &rtDW->c, &rtDW->Switch2);

      /* Product: '<S187>/Product3' incorporates:
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Sum_cr = (real32_T)rtDW->SignCorrected_d * 6.10351562E-5F * rtDW->c;

      /* DataTypeConversion: '<S246>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S246>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768);

      /* Switch: '<S246>/QuadHandle1' incorporates:
       *  Constant: '<S246>/Point50'
       *  Sum: '<S246>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 32768);
      }

      /* End of Switch: '<S246>/QuadHandle1' */

      /* Switch: '<S246>/QuadHandle2' incorporates:
       *  Constant: '<S246>/Point50'
       *  RelationalOperator: '<S246>/LTEp25'
       *  Sum: '<S246>/p50mA'
       *  Switch: '<S246>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S246>/QuadHandle2' */

      /* Lookup_n-D: '<S245>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S246>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S245>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S246>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S246>/SignCorrected' */

      /* Sum: '<S187>/Sum' incorporates:
       *  Gain: '<S187>/Gain3'
       *  Product: '<S187>/Product2'
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Sum_cr += (real32_T)(-32768 * rtDW->SignCorrected_d) *
        1.86264515E-9F * rtDW->Switch2;

      /* DataTypeConversion: '<S253>/CastU16En16' incorporates:
       *  Constant: '<S188>/Constant1'
       *  DataTypeConversion: '<S259>/CastU16En16'
       *  Gain: '<S188>/Gain5'
       *  Product: '<S188>/Product4'
       */
      rtDW->rtb_CastU16En16_h_tmp_tmp = (uint16_T)(rtDW->theta_b * 6.0F *
        0.159154937F * 65536.0F);

      /* RelationalOperator: '<S253>/LTEp25' incorporates:
       *  DataTypeConversion: '<S253>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 16384);

      /* RelationalOperator: '<S253>/GTEp75' incorporates:
       *  DataTypeConversion: '<S253>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->rtb_CastU16En16_h_tmp_tmp >= 49152);

      /* Switch: '<S253>/QuadHandle2' incorporates:
       *  Constant: '<S253>/Point75'
       *  DataTypeConversion: '<S253>/CastU16En16'
       *  RelationalOperator: '<S253>/LTEp50'
       *  Sum: '<S253>/p75mA'
       *  Switch: '<S253>/QuadHandle1b'
       */
      if (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768) {
        /* Switch: '<S253>/QuadHandle1a' incorporates:
         *  Constant: '<S253>/Point25'
         *  Sum: '<S253>/Amp25'
         *  Sum: '<S253>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->CastU16En16_h = (uint16_T)(16384 -
            rtDW->rtb_CastU16En16_h_tmp_tmp);
        } else {
          rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp -
            16384);
        }

        /* End of Switch: '<S253>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S253>/QuadHandle1b' incorporates:
         *  Constant: '<S253>/Point75'
         *  Sum: '<S253>/Amp75'
         */
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 49152);
      } else {
        rtDW->CastU16En16_h = (uint16_T)(49152 - rtDW->rtb_CastU16En16_h_tmp_tmp);
      }

      /* End of Switch: '<S253>/QuadHandle2' */

      /* Lookup_n-D: '<S252>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S253>/SignCorrected' incorporates:
       *  Logic: '<S253>/1st or 4th Quad'
       *  Lookup_n-D: '<S252>/Look-Up Table'
       *  Switch: '<S259>/SignCorrected'
       *  UnaryMinus: '<S253>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S253>/SignCorrected' */

      /* DataTypeConversion: '<S255>/CastU16En16' incorporates:
       *  Constant: '<S188>/Constant1'
       *  Constant: '<S25>/Constant'
       *  DataTypeConversion: '<S257>/CastU16En16'
       *  Gain: '<S188>/Gain4'
       *  Inport: '<Root>/Act_theta_u_el'
       *  Product: '<S188>/Product5'
       *  Sum: '<S25>/Sum'
       */
      rtDW->CastU16En16_h = (uint16_T)((rtU->Act_theta_u_el + -4.18879032F) *
        6.0F * 0.159154937F * 65536.0F);

      /* RelationalOperator: '<S255>/LTEp25' incorporates:
       *  DataTypeConversion: '<S255>/CastU16En16'
       */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 16384);

      /* RelationalOperator: '<S255>/GTEp75' incorporates:
       *  DataTypeConversion: '<S255>/CastU16En16'
       */
      rtDW->GTEp75_b = (rtDW->CastU16En16_h >= 49152);

      /* Switch: '<S255>/QuadHandle2' incorporates:
       *  Constant: '<S255>/Point75'
       *  DataTypeConversion: '<S255>/CastU16En16'
       *  RelationalOperator: '<S255>/LTEp50'
       *  Sum: '<S255>/p75mA'
       *  Switch: '<S255>/QuadHandle1b'
       */
      if (rtDW->CastU16En16_h <= 32768) {
        /* Switch: '<S255>/QuadHandle1a' incorporates:
         *  Constant: '<S255>/Point25'
         *  Sum: '<S255>/Amp25'
         *  Sum: '<S255>/p25mA'
         */
        if (rtDW->GTEp75) {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(16384 - rtDW->CastU16En16_h);
        } else {
          rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 16384);
        }

        /* End of Switch: '<S255>/QuadHandle1a' */
      } else if (rtDW->GTEp75_b) {
        /* Switch: '<S255>/QuadHandle1b' incorporates:
         *  Constant: '<S255>/Point75'
         *  Sum: '<S255>/Amp75'
         */
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(rtDW->CastU16En16_h - 49152);
      } else {
        rtDW->rtb_CastU16En16_h_m = (uint16_T)(49152 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S255>/QuadHandle2' */

      /* Lookup_n-D: '<S254>/Look-Up Table' */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->rtb_CastU16En16_h_m, 0U,
        16384U, &rtDW->frac);

      /* Switch: '<S255>/SignCorrected' incorporates:
       *  Logic: '<S255>/1st or 4th Quad'
       *  Lookup_n-D: '<S254>/Look-Up Table'
       *  Switch: '<S257>/SignCorrected'
       *  UnaryMinus: '<S255>/Negate'
       */
      if (rtDW->GTEp75 || rtDW->GTEp75_b) {
        rtDW->SignCorrected_c = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_c = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S255>/SignCorrected' */

      /* Product: '<S188>/Product1' incorporates:
       *  Switch: '<S257>/SignCorrected'
       */
      rtDW->a = (real32_T)rtDW->SignCorrected_c * 6.10351562E-5F *
        rtDW->re_lim_e;

      /* Gain: '<S188>/Gain1' incorporates:
       *  Delay: '<S188>/Delay1'
       *  Sum: '<S188>/Sum4'
       */
      rtDW->theta_b = 2.5E-5F * rtP.K6 * (rtDW->Delay1_DSTATE_oi + rtDW->a);

      /* DiscreteIntegrator: '<S188>/Discrete-Time Integrator' */
      rtDW->Delay1 = 0.5F * rtDW->theta_b +
        rtDW->DiscreteTimeIntegrator_DSTATE_g;

      /* Sum: '<S188>/Sum5' */
      rtDW->U_re_d = rtDW->Delay1 + rtDW->a;

      /* RelationalOperator: '<S257>/LTEp50' */
      rtDW->GTEp75 = (rtDW->CastU16En16_h <= 32768);

      /* Switch: '<S257>/QuadHandle1' incorporates:
       *  Constant: '<S257>/Point50'
       *  Sum: '<S257>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->CastU16En16_h - 32768);
      }

      /* End of Switch: '<S257>/QuadHandle1' */

      /* Switch: '<S257>/QuadHandle2' incorporates:
       *  Constant: '<S257>/Point50'
       *  RelationalOperator: '<S257>/LTEp25'
       *  Sum: '<S257>/p50mA'
       *  Switch: '<S257>/QuadHandle1'
       *  Switch: '<S259>/QuadHandle2'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S257>/QuadHandle2' */

      /* Lookup_n-D: '<S256>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S257>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S256>/Look-Up Table'
       *  UnaryMinus: '<S257>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_c = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_c = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S257>/SignCorrected' */

      /* Product: '<S188>/Product' incorporates:
       *  Gain: '<S188>/Gain'
       *  Switch: '<S257>/SignCorrected'
       */
      rtDW->re_lim_e *= (real32_T)(-32768 * rtDW->SignCorrected_c) *
        1.86264515E-9F;

      /* Gain: '<S188>/Gain2' incorporates:
       *  Delay: '<S188>/Delay'
       *  Sum: '<S188>/Sum2'
       */
      rtDW->Gain2_i = 2.5E-5F * rtP.K6 * (rtDW->re_lim_e + rtDW->Delay_DSTATE_nm);

      /* DiscreteIntegrator: '<S188>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_g = 0.5F * rtDW->Gain2_i +
        rtDW->DiscreteTimeIntegrator1_DSTA_os;

      /* Sum: '<S188>/Sum6' */
      rtDW->U_im_c = rtDW->re_lim_e + rtDW->DiscreteTimeIntegrator1_g;

      /* MATLAB Function: '<S188>/MATLAB Function' incorporates:
       *  Constant: '<S188>/Constant2'
       *  Product: '<S188>/Product6'
       */
      MATLABFunction_a(rtDW->U_re_d, 0.01F * rtDW->DiscreteTimeIntegrator,
                       rtDW->LTEp50_j, rtDW->U_im_c, &rtDW->re_lim_e, &rtDW->a);

      /* Product: '<S188>/Product3' incorporates:
       *  Switch: '<S259>/SignCorrected'
       */
      rtDW->Sum_a = (real32_T)rtDW->SignCorrected_d * 6.10351562E-5F *
        rtDW->re_lim_e;

      /* DataTypeConversion: '<S259>/CastU16En16' */
      rtDW->CastU16En16_h = rtDW->rtb_CastU16En16_h_tmp_tmp;

      /* RelationalOperator: '<S259>/LTEp50' */
      rtDW->GTEp75 = (rtDW->rtb_CastU16En16_h_tmp_tmp <= 32768);

      /* Switch: '<S259>/QuadHandle1' incorporates:
       *  Constant: '<S259>/Point50'
       *  Sum: '<S259>/Amp50'
       */
      if (!rtDW->GTEp75) {
        rtDW->CastU16En16_h = (uint16_T)(rtDW->rtb_CastU16En16_h_tmp_tmp - 32768);
      }

      /* End of Switch: '<S259>/QuadHandle1' */

      /* Switch: '<S259>/QuadHandle2' incorporates:
       *  Constant: '<S259>/Point50'
       *  RelationalOperator: '<S259>/LTEp25'
       *  Sum: '<S259>/p50mA'
       *  Switch: '<S259>/QuadHandle1'
       */
      if (rtDW->CastU16En16_h > 16384) {
        rtDW->CastU16En16_h = (uint16_T)(32768 - rtDW->CastU16En16_h);
      }

      /* End of Switch: '<S259>/QuadHandle2' */

      /* Lookup_n-D: '<S258>/Look-Up Table' incorporates:
       *  Switch: '<S259>/QuadHandle2'
       */
      rtDW->bpIdx = plook_u32u16u64n48_even0c_gf(rtDW->CastU16En16_h, 0U, 16384U,
        &rtDW->frac);

      /* Switch: '<S259>/SignCorrected' incorporates:
       *  Lookup_n-D: '<S258>/Look-Up Table'
       *  UnaryMinus: '<S259>/Negate'
       */
      if (rtDW->GTEp75) {
        rtDW->SignCorrected_d = intrp1d_s16s32s32u32u64n48l_f(rtDW->bpIdx,
          rtDW->frac, rtConstP.pooled18);
      } else {
        rtDW->SignCorrected_d = (int16_T)-intrp1d_s16s32s32u32u64n48l_f
          (rtDW->bpIdx, rtDW->frac, rtConstP.pooled18);
      }

      /* End of Switch: '<S259>/SignCorrected' */

      /* Outport: '<Root>/a_W' incorporates:
       *  Constant: '<S25>/Constant1'
       *  Gain: '<S188>/Gain3'
       *  Product: '<S188>/Product2'
       *  Product: '<S25>/Divide'
       *  Sum: '<S188>/Sum'
       *  Sum: '<S25>/Add'
       *  Sum: '<S25>/Add1'
       *  Switch: '<S259>/SignCorrected'
       */
      rtY->a_W = (((real32_T)(-32768 * rtDW->SignCorrected_d) * 1.86264515E-9F *
                   rtDW->a + rtDW->Sum_a) + ((rtDW->Add1 + rtDW->Sum_a5) +
        rtDW->Sum_cr)) / rtDW->DiscreteTimeIntegrator + 0.5F;

      /* Merge: '<S10>/Merge5' incorporates:
       *  SignalConversion generated from: '<S25>/I_ref1'
       */
      rtDW->Merge5 = rtDW->Strom_kompensiert;

      /* Update for Delay: '<S185>/Delay1' incorporates:
       *  Sum: '<S185>/Sum3'
       */
      rtDW->Delay1_DSTATE = rtDW->Gain1 - rtDW->U_re;

      /* Update for DiscreteIntegrator: '<S185>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.5F * rtDW->Gain1_k +
        rtDW->DiscreteTimeIntegrator_o;

      /* Update for Delay: '<S185>/Delay' incorporates:
       *  Sum: '<S185>/Sum1'
       */
      rtDW->Delay_DSTATE_l = rtDW->b - rtDW->U_im;

      /* Update for DiscreteIntegrator: '<S185>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTATE = 0.5F * rtDW->Add +
        rtDW->DiscreteTimeIntegrator1;

      /* Update for Delay: '<S186>/Delay1' incorporates:
       *  Sum: '<S186>/Sum3'
       */
      rtDW->Delay1_DSTATE_o = rtDW->y - rtDW->U_re_c;

      /* Update for DiscreteIntegrator: '<S186>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.5F * rtDW->Gain1_e +
        rtDW->DiscreteTimeIntegrator_k;

      /* Update for Delay: '<S186>/Delay' incorporates:
       *  Sum: '<S186>/Sum1'
       */
      rtDW->Delay_DSTATE_nv = rtDW->y_i - rtDW->U_im_k;

      /* Update for DiscreteIntegrator: '<S186>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.5F * rtDW->Gain2_n +
        rtDW->DiscreteTimeIntegrator1_e;

      /* Update for Delay: '<S187>/Delay1' incorporates:
       *  Sum: '<S187>/Sum3'
       */
      rtDW->Delay1_DSTATE_g = rtDW->c - rtDW->U_re_n;

      /* Update for DiscreteIntegrator: '<S187>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.5F * rtDW->Gain1_m +
        rtDW->DiscreteTimeIntegrator_a;

      /* Update for Delay: '<S187>/Delay' incorporates:
       *  Sum: '<S187>/Sum1'
       */
      rtDW->Delay_DSTATE_a = rtDW->Switch2 - rtDW->U_im_p;

      /* Update for DiscreteIntegrator: '<S187>/Discrete-Time Integrator1' */
      rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.5F * rtDW->Gain2_h +
        rtDW->DiscreteTimeIntegrator1_a;

      /* Update for Delay: '<S188>/Delay1' incorporates:
       *  Sum: '<S188>/Sum3'
       */
      rtDW->Delay1_DSTATE_oi = rtDW->re_lim_e - rtDW->U_re_d;

      /* Update for DiscreteIntegrator: '<S188>/Discrete-Time Integrator' */
      rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.5F * rtDW->theta_b +
        rtDW->Delay1;

      /* Update for Delay: '<S188>/Delay' incorporates:
       *  Sum: '<S188>/Sum1'
       */
      rtDW->Delay_DSTATE_nm = rtDW->a - rtDW->U_im_c;

      /* Update for DiscreteIntegrator: '<S188>/Discrete-Time Integrator1' */
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

  /* DiscreteIntegrator: '<S274>/Accumulator' incorporates:
   *  Delay: '<S274>/Delay'
   *  Sum: '<S274>/Sum'
   */
  rtDW->a = (rtDW->c - rtDW->Delay_DSTATE_k[0]) + rtDW->Accumulator_DSTATE;

  /* Outport: '<Root>/fault_rms_current_u' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Gain: '<S274>/Gain'
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

  /* DiscreteIntegrator: '<S275>/Accumulator' incorporates:
   *  Delay: '<S275>/Delay'
   *  Inport: '<Root>/Act_n'
   *  Sum: '<S275>/Sum'
   */
  rtDW->b = (rtU->Act_n - rtDW->Delay_DSTATE_ki[0]) + rtDW->Accumulator_DSTATE_d;

  /* Outport: '<Root>/fault_max_speed' incorporates:
   *  Constant: '<S5>/Constant3'
   *  Gain: '<S275>/Gain'
   *  RelationalOperator: '<S5>/Smaller3'
   */
  rtY->fault_max_speed = (rtP.n_max <= 0.00833333377F * rtDW->b);

  /* Math: '<S5>/Square1' incorporates:
   *  Inport: '<Root>/Act_Iv'
   */
  rtDW->Gain1 = rtU->Act_Iv * rtU->Act_Iv;

  /* DiscreteIntegrator: '<S276>/Accumulator' incorporates:
   *  Delay: '<S276>/Delay'
   *  Sum: '<S276>/Sum'
   */
  rtDW->y_i = (rtDW->Gain1 - rtDW->Delay_DSTATE_kl[0]) +
    rtDW->Accumulator_DSTATE_f;

  /* Outport: '<Root>/fault_rms_current_v' incorporates:
   *  Constant: '<S5>/Constant5'
   *  Gain: '<S276>/Gain'
   *  RelationalOperator: '<S5>/Smaller5'
   *  Sqrt: '<S5>/Square Root1'
   */
  rtY->fault_rms_current_v = (rtP.i_max_rms <= sqrtf(0.05F * rtDW->y_i));

  /* Math: '<S5>/Square2' incorporates:
   *  Inport: '<Root>/Act_Iw'
   */
  rtDW->y = rtU->Act_Iw * rtU->Act_Iw;

  /* DiscreteIntegrator: '<S277>/Accumulator' incorporates:
   *  Delay: '<S277>/Delay'
   *  Sum: '<S277>/Sum'
   */
  rtDW->Switch2 = (rtDW->y - rtDW->Delay_DSTATE_b[0]) +
    rtDW->Accumulator_DSTATE_n;

  /* Outport: '<Root>/fault_rms_current_w' incorporates:
   *  Constant: '<S5>/Constant7'
   *  Gain: '<S277>/Gain'
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

  /* Update for Delay: '<S274>/Delay' */
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 19; rtDW->idxDelay++) {
    rtDW->Delay_DSTATE_k[rtDW->idxDelay] = rtDW->Delay_DSTATE_k[rtDW->idxDelay +
      1];
  }

  rtDW->Delay_DSTATE_k[19] = rtDW->c;

  /* End of Update for Delay: '<S274>/Delay' */

  /* Update for DiscreteIntegrator: '<S274>/Accumulator' */
  rtDW->Accumulator_DSTATE = rtDW->a;

  /* Update for Delay: '<S275>/Delay' incorporates:
   *  Inport: '<Root>/Act_n'
   */
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 119; rtDW->idxDelay++) {
    rtDW->Delay_DSTATE_ki[rtDW->idxDelay] = rtDW->Delay_DSTATE_ki[rtDW->idxDelay
      + 1];
  }

  rtDW->Delay_DSTATE_ki[119] = rtU->Act_n;

  /* End of Update for Delay: '<S275>/Delay' */

  /* Update for DiscreteIntegrator: '<S275>/Accumulator' */
  rtDW->Accumulator_DSTATE_d = rtDW->b;

  /* Update for DiscreteIntegrator: '<S276>/Accumulator' */
  rtDW->Accumulator_DSTATE_f = rtDW->y_i;
  for (rtDW->idxDelay = 0; rtDW->idxDelay < 19; rtDW->idxDelay++) {
    /* Update for Delay: '<S276>/Delay' */
    rtDW->Delay_DSTATE_kl[rtDW->idxDelay] = rtDW->Delay_DSTATE_kl[rtDW->idxDelay
      + 1];

    /* Update for Delay: '<S277>/Delay' */
    rtDW->Delay_DSTATE_b[rtDW->idxDelay] = rtDW->Delay_DSTATE_b[rtDW->idxDelay +
      1];
  }

  /* Update for Delay: '<S276>/Delay' */
  rtDW->Delay_DSTATE_kl[19] = rtDW->Gain1;

  /* Update for Delay: '<S277>/Delay' */
  rtDW->Delay_DSTATE_b[19] = rtDW->y;

  /* Update for DiscreteIntegrator: '<S277>/Accumulator' */
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
  /* InitializeConditions for Delay: '<S185>/Delay1' */
  rtDW->Delay1_DSTATE = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S185>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_o = 0.0F;

  /* InitializeConditions for Delay: '<S185>/Delay' */
  rtDW->Delay_DSTATE_l = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S185>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;

  /* InitializeConditions for Delay: '<S186>/Delay1' */
  rtDW->Delay1_DSTATE_o = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S186>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_m = 0.0F;

  /* InitializeConditions for Delay: '<S186>/Delay' */
  rtDW->Delay_DSTATE_nv = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S186>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_f = 0.0F;

  /* InitializeConditions for Delay: '<S187>/Delay1' */
  rtDW->Delay1_DSTATE_g = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S187>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_c = 0.0F;

  /* InitializeConditions for Delay: '<S187>/Delay' */
  rtDW->Delay_DSTATE_a = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S187>/Discrete-Time Integrator1' */
  rtDW->DiscreteTimeIntegrator1_DSTAT_o = 0.0F;

  /* InitializeConditions for Delay: '<S188>/Delay1' */
  rtDW->Delay1_DSTATE_oi = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S188>/Discrete-Time Integrator' */
  rtDW->DiscreteTimeIntegrator_DSTATE_g = 0.0F;

  /* InitializeConditions for Delay: '<S188>/Delay' */
  rtDW->Delay_DSTATE_nm = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S188>/Discrete-Time Integrator1' */
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
