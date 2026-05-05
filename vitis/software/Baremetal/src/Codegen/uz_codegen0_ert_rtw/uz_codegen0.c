/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 9.111
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu Apr 16 10:52:55 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "uz_codegen0.h"
#include <math.h>
#include "rtwtypes.h"
#include <string.h>

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  real_T Ts_over_Ld;
  real_T Ts_over_Ld_tmp;
  real_T Ts_over_Lq;
  real_T ce;
  real_T se;
  real_T u_beta0;
  real_T u_beta0_tmp;
  real_T wrTs;

  /* MATLAB Function: '<S1>/Deadbeat Control' */
  /*  define persistent for storing the last-step modulating voltage */
  /* MATLAB Function 'uz_codegen/Deadbeat Control': '<S2>:1' */
  /* '<S2>:1:5' if isempty(u_a0) */
  /*  Clarke transforamtion */
  /* '<S2>:1:12' u_alpha0 = 0.667 * (u_a0 - 0.5*u_b0 - 0.5*u_c0); */
  rtDW->u_alpha0 = ((rtDW->u_a0 - 0.5 * rtDW->u_b0) - 0.5 * rtDW->u_c0) * 0.667;

  /* '<S2>:1:13' u_beta0 = 0.667 * (0.866*u_b0 - 0.866*u_c0); */
  u_beta0 = (0.866 * rtDW->u_b0 - 0.866 * rtDW->u_c0) * 0.667;

  /*  Park transforamtion */
  /* '<S2>:1:18' ce = cos(Theta_e); */
  ce = cos(rtU->theta_e);

  /* '<S2>:1:19' se = sin(Theta_e); */
  se = sin(rtU->theta_e);

  /* '<S2>:1:21' u_d0 = ce*u_alpha0 + se*u_beta0; */
  /* '<S2>:1:22' u_q0 = -se*u_alpha0 + ce*u_beta0; */
  /*  last-step voltage */
  /* '<S2>:1:25' v_d0 = u_d0*(V_dc_nom_PM*0.5); */
  /* '<S2>:1:26' v_q0 = u_q0*(V_dc_nom_PM*0.5); */
  /*  one step compensation for current measuremnt: from (k-1) to (k) */
  /* '<S2>:1:29' wrTs = w_r * T_s; */
  wrTs = rtU->w_e * rtU->Ts;

  /* '<S2>:1:30' Ts_over_Ld = T_s / Ld_PM; */
  Ts_over_Ld = rtU->Ts / rtU->Ld_PM;

  /* '<S2>:1:31' Ts_over_Lq = T_s / Lq_PM; */
  Ts_over_Lq = rtU->Ts / rtU->Lq_PM;

  /* '<S2>:1:32' id_k = Ts_over_Ld*v_d0 +(1- Ts_over_Ld *Rs_PM)*i_d + Lq_PM*w_r * Ts_over_Ld*i_q; */
  Ts_over_Ld_tmp = rtU->Lq_PM * rtU->w_e;
  Ts_over_Ld = ((ce * rtDW->u_alpha0 + se * u_beta0) * (rtU->V_dc_nom_PM * 0.5) *
                Ts_over_Ld + (1.0 - Ts_over_Ld * rtU->Rs_PM) * rtU->id) +
    Ts_over_Ld_tmp * Ts_over_Ld * rtU->iq;

  /* '<S2>:1:33' iq_k = Ts_over_Lq*v_q0 +(1- Ts_over_Lq *Rs_PM)*i_q - Ld_PM*w_r * Ts_over_Lq*i_d - Ts_over_Lq *w_r*Psi_PM; */
  u_beta0_tmp = rtU->Ld_PM * rtU->w_e;
  u_beta0 = (((-se * rtDW->u_alpha0 + ce * u_beta0) * (rtU->V_dc_nom_PM * 0.5) *
              Ts_over_Lq + (1.0 - Ts_over_Lq * rtU->Rs_PM) * rtU->iq) -
             u_beta0_tmp * Ts_over_Lq * rtU->id) - Ts_over_Lq * rtU->w_e *
    rtU->Psi_PM;

  /*  one step compensation for angle measuremnt */
  /* '<S2>:1:36' Theta_k = Theta_e + Comp_PM *wrTs; */
  /*  angle from (k-1) to (k) */
  /*  deadbeat solution: from (k) to (k+1) */
  /* '<S2>:1:39' Ld_over_Ts = Ld_PM / T_s; */
  /* '<S2>:1:40' Lq_over_Ts = Lq_PM / T_s; */
  /* '<S2>:1:41' vd_ref = Ld_over_Ts*(id_ref-id_k)+ Rs_PM *id_k - Lq_PM*w_r*iq_k; */
  rtDW->u_alpha0 = (rtU->Ld_PM / rtU->Ts * (rtU->id_ref - Ts_over_Ld) +
                    rtU->Rs_PM * Ts_over_Ld) - Ts_over_Ld_tmp * u_beta0;

  /*  reference voltage at (k+1) */
  /* '<S2>:1:42' vq_ref = Lq_over_Ts*(iq_ref-iq_k)+ Rs_PM *iq_k + Ld_PM*w_r *id_k + w_r* Psi_PM; */
  Ts_over_Ld = ((rtU->Lq_PM / rtU->Ts * (rtU->iq_ref - u_beta0) + rtU->Rs_PM *
                 u_beta0) + u_beta0_tmp * Ts_over_Ld) + rtU->w_e * rtU->Psi_PM;

  /*  reference voltage at (k+1) */
  /*  one step compensation for angle */
  /* '<S2>:1:45' Theta_k1 = Theta_k + wrTs; */
  wrTs += rtU->Comp_PM * wrTs + rtU->theta_e;

  /*  angle from (k) to (k+1) */
  /*  inverse Park transformation */
  /* '<S2>:1:49' ck1 = cos(Theta_k1); */
  u_beta0 = cos(wrTs);

  /* '<S2>:1:50' sk1 = sin(Theta_k1); */
  ce = sin(wrTs);

  /* '<S2>:1:52' v_alpha_ref = ck1*vd_ref - sk1*vq_ref; */
  /* '<S2>:1:53' v_beta_ref = sk1*vd_ref + ck1*vq_ref; */
  /*  transfer reference voltage into modulating voltage */
  /* '<S2>:1:57' inv_half_Vdc = 1 / (0.5*V_dc_nom_PM); */
  se = 1.0 / (0.5 * rtU->V_dc_nom_PM);

  /* '<S2>:1:58' u_alpha = v_alpha_ref*inv_half_Vdc; */
  wrTs = (u_beta0 * rtDW->u_alpha0 - ce * Ts_over_Ld) * se;

  /* '<S2>:1:59' u_beta =  v_beta_ref*inv_half_Vdc; */
  Ts_over_Ld = (ce * rtDW->u_alpha0 + u_beta0 * Ts_over_Ld) * se;

  /*  inverse clark transformation */
  /* '<S2>:1:63' u_a = u_alpha; */
  /* '<S2>:1:64' u_b = -0.5 * u_alpha + 0.866 * u_beta; */
  rtDW->u_alpha0 = -0.5 * wrTs + 0.866 * Ts_over_Ld;

  /* '<S2>:1:65' u_c = -0.5 * u_alpha - 0.866 * u_beta; */
  Ts_over_Ld = -0.5 * wrTs - 0.866 * Ts_over_Ld;

  /*  common-mode injection (SVM-Equivalent)      */
  /* '<S2>:1:69' u_min = min(u_a, min(u_b, u_c)); */
  /* '<S2>:1:70' u_max = max(u_a, max(u_b, u_c)); */
  /* '<S2>:1:71' u_com = -0.5 * (u_min + u_max); */
  u_beta0 = (fmin(wrTs, fmin(rtDW->u_alpha0, Ts_over_Ld)) + fmax(wrTs, fmax
              (rtDW->u_alpha0, Ts_over_Ld))) * -0.5;

  /* '<S2>:1:73' u_a = u_a + u_com; */
  /* '<S2>:1:74' u_b = u_b + u_com; */
  /* '<S2>:1:75' u_c = u_c + u_com; */
  /*  saturation */
  /* '<S2>:1:78' u_a = min(1, max(-1, u_a)); */
  wrTs = fmin(1.0, fmax(-1.0, wrTs + u_beta0));

  /* '<S2>:1:79' u_b = min(1, max(-1, u_b)); */
  rtDW->u_alpha0 = fmin(1.0, fmax(-1.0, rtDW->u_alpha0 + u_beta0));

  /* '<S2>:1:80' u_c = min(1, max(-1, u_c)); */
  Ts_over_Ld = fmin(1.0, fmax(-1.0, Ts_over_Ld + u_beta0));

  /*  duty cycle */
  /* '<S2>:1:83' d_a = 0.5*(u_a + 1); */
  /* '<S2>:1:84' d_b = 0.5*(u_b + 1); */
  /* '<S2>:1:85' d_c = 0.5*(u_c + 1); */
  /*  store modulating voltage */
  /* '<S2>:1:88' u_a0 = u_a; */
  rtDW->u_a0 = wrTs;

  /* '<S2>:1:89' u_b0 = u_b; */
  rtDW->u_b0 = rtDW->u_alpha0;

  /* '<S2>:1:90' u_c0 = u_c; */
  rtDW->u_c0 = Ts_over_Ld;

  /* Outport: '<Root>/da' incorporates:
   *  MATLAB Function: '<S1>/Deadbeat Control'
   */
  rtY->da = (wrTs + 1.0) * 0.5;

  /* Outport: '<Root>/db' incorporates:
   *  MATLAB Function: '<S1>/Deadbeat Control'
   */
  rtY->db = (rtDW->u_alpha0 + 1.0) * 0.5;

  /* Outport: '<Root>/dc' incorporates:
   *  MATLAB Function: '<S1>/Deadbeat Control'
   */
  rtY->dc = (Ts_over_Ld + 1.0) * 0.5;
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

  /* SystemInitialize for MATLAB Function: '<S1>/Deadbeat Control' */
  /* '<S2>:1:6' u_a0 = 0; */
  rtDW->u_a0 = 0.0;

  /* '<S2>:1:7' u_b0 = 0; */
  rtDW->u_b0 = 0.0;

  /* '<S2>:1:8' u_c0 = 0; */
  rtDW->u_c0 = 0.0;

  /* ConstCode for Outport: '<Root>/da_left' */
  rtY->da_left = 0.0;

  /* ConstCode for Outport: '<Root>/db_left' */
  rtY->db_left = 0.0;

  /* ConstCode for Outport: '<Root>/dc_left' */
  rtY->dc_left = 0.0;

  /* ConstCode for Outport: '<Root>/theta_e_est' */
  rtY->theta_e_est = 0.0;

  /* ConstCode for Outport: '<Root>/i_alpha' */
  rtY->i_alpha = 0.0;

  /* ConstCode for Outport: '<Root>/i_beta' */
  rtY->i_beta = 0.0;

  /* ConstCode for Outport: '<Root>/i_alpha_est' */
  rtY->i_alpha_est = 0.0;

  /* ConstCode for Outport: '<Root>/i_beta_est' */
  rtY->i_beta_est = 0.0;

  /* ConstCode for Outport: '<Root>/theta_unwrap' */
  rtY->theta_unwrap = 0.0;

  /* ConstCode for Outport: '<Root>/n_est' */
  rtY->n_est = 0.0;

  /* ConstCode for Outport: '<Root>/Te_est' */
  rtY->Te_est = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
