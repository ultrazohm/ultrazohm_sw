/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'foc_ts'.
 *
 * Model version                  : 6.11
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Thu Oct  1 16:09:58 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Passed (11), Warnings (2), Error (0)
 */

#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "foc_ts.h"                    /* Model's header file */
#include "rtwtypes.h"

static RT_MODEL_foc_ts_T foc_ts_M_;
static RT_MODEL_foc_ts_T *const foc_ts_MPtr = &foc_ts_M_;/* Real-time model */
static DW_foc_ts_T foc_ts_DW;          /* Observable states */

/* '<Root>/d_u_dc' */
static real_T foc_ts_U_d_u_dc;

/* '<Root>/d_nSoll' */
static real_T foc_ts_U_d_nSoll;

/* '<Root>/d_omega_mech' */
static real_T foc_ts_U_d_omega_mech;

/* '<Root>/d_theta_mech' */
static real_T foc_ts_U_d_theta_mech;

/* '<Root>/d_i_a' */
static real_T foc_ts_U_d_i_a;

/* '<Root>/d_i_b' */
static real_T foc_ts_U_d_i_b;

/* '<Root>/d_i_c' */
static real_T foc_ts_U_d_i_c;

/* '<Root>/d_K_p_d' */
static real_T foc_ts_U_d_K_p_d;

/* '<Root>/d_K_i_d' */
static real_T foc_ts_U_d_K_i_d;

/* '<Root>/d_K_p_q' */
static real_T foc_ts_U_d_K_p_q;

/* '<Root>/d_K_i_q' */
static real_T foc_ts_U_d_K_i_q;

/* '<Root>/d_K_p_n' */
static real_T foc_ts_U_d_K_p_n;

/* '<Root>/d_K_i_n' */
static real_T foc_ts_U_d_K_i_n;

/* '<Root>/i_d_soll' */
static real_T foc_ts_U_i_d_soll;

/* '<Root>/i_q_soll' */
static real_T foc_ts_U_i_q_soll;

/* '<Root>/d_u_1_nom' */
static real_T foc_ts_Y_d_u_1_nom;

/* '<Root>/d_u_2_nom' */
static real_T foc_ts_Y_d_u_2_nom;

/* '<Root>/d_u_3_nom' */
static real_T foc_ts_Y_d_u_3_nom;

/* '<Root>/d_u_d' */
static real_T foc_ts_Y_d_u_d;

/* '<Root>/d_u_q' */
static real_T foc_ts_Y_d_u_q;

/* '<Root>/iqSollFB' */
static real_T foc_ts_Y_iqSollFB;

/* '<Root>/id_ist' */
static real_T foc_ts_Y_id_ist;

/* '<Root>/iq_ist' */
static real_T foc_ts_Y_iq_ist;

/* '<Root>/theta_mech_out' */
static real_T foc_ts_Y_theta_mech_out;
