/*
 * Classroom License -- for classroom instructional use only.  Not for
 * government, commercial, academic research, or other organizational use.
 *
 * File: CCS_Speed_o_V7.c
 *
 * Code generated for Simulink model 'CCS_Speed_o_V7'.
 *
 * Model version                  : 1.1177
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri May 25 11:16:52 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Emulation hardware selection:
 *    Differs from embedded hardware (Custom Processor->MATLAB Host Computer)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CCS_Speed_o_V7.h"
#include "CCS_Speed_o_V7_private.h"

/* Model step function */
void CCS_Speed_o_V7_step(RT_MODEL_CCS_Speed_o_V7_T *const CCS_Speed_o_V7_M,
  real_T CCS_Speed_o_V7_U_d_n_ref, real_T CCS_Speed_o_V7_U_d_n_meas, real_T
  CCS_Speed_o_V7_U_d_delta_theta, real_T CCS_Speed_o_V7_U_d_n_L_meas, real_T
  *CCS_Speed_o_V7_Y_d_i_q_ref)
{
  P_CCS_Speed_o_V7_T *CCS_Speed_o_V7_P = ((P_CCS_Speed_o_V7_T *)
    CCS_Speed_o_V7_M->defaultParam);
  DW_CCS_Speed_o_V7_T *CCS_Speed_o_V7_DW = ((DW_CCS_Speed_o_V7_T *)
    CCS_Speed_o_V7_M->dwork);
  real_T rtb_Gain13;
  real_T d_x[5];
  real_T tmp[5];
  real_T tmp_0[30];
  real_T d_x_0[5];
  int32_T i;
  int32_T i_0;
  real_T tmp_1[6];
  real_T d_x_idx_0;
  real_T d_x_idx_2;

  /* Gain: '<S1>/Gain13' incorporates:
   *  Inport: '<Root>/d_n_L_meas'
   */
  rtb_Gain13 = CCS_Speed_o_V7_P->Gain13_Gain * CCS_Speed_o_V7_U_d_n_L_meas;

  /* MATLAB Function: '<S1>/CCS-MPC Drehzahlregler' incorporates:
   *  Gain: '<S1>/Gain8'
   *  Gain: '<S1>/Gain9'
   *  Inport: '<Root>/d_delta_theta'
   *  Inport: '<Root>/d_n_meas'
   *  Inport: '<Root>/d_n_ref'
   */
  /*  CCS-MPC nach den Methoden von L. Wang "Model Predictive Control System Design and Implementation Using MATLAB" */
  /* MATLAB Function 'CCS_Speed_o_V7/CCS-MPC Drehzahlregler': '<S2>:1' */
  /*  Speicher um das Stellsignal abzuspeichern */
  /*  Es wird die benötigte Änderung DeltaU berechnet die hinzu addiert wird. */
  /* '<S2>:1:8' if isempty(d_up) */
  /*  Speicher um die Zustände der vorherigen Samplezeit abzuspeichern */
  /* '<S2>:1:14' if isempty(d_x_old) */
  /*  Ist-Werte des Zustandsvektors x */
  /* '<S2>:1:19' d_x =[d_omega_ist; d_delta_theta; d_omega_l_ist]; */
  d_x_idx_0 = CCS_Speed_o_V7_P->Gain9_Gain * CCS_Speed_o_V7_U_d_n_meas;
  d_x_idx_2 = rtb_Gain13;

  /*  Zustandsvektor des augmented Zustandsraummodell */
  /* '<S2>:1:22' d_Xf=[d_x-d_x_old; d_delta_theta; d_omega_l_ist]; */
  /*  Berechnung DeltaU in verschiedenen Detailierungsgraden */
  /* deltaU1=inv(d_phi_phi+d_rw*eye(size(d_phi_phi)))*(d_phi_R*[0; omega_soll]-d_phi_F*Xf); */
  /* deltaU1 = d_invOmegaPhi_R*[0;omega_soll]+d_invOmegaPhi_F*Xf; */
  /* '<S2>:1:27' d_deltaU1=-d_invOmegaPhi_F*(d_Xf-[0;0;0;0; d_omega_soll]); */
  /* '<S2>:1:29' d_DeltaU1 = d_deltaU1(1,1); */
  /*  neues Stellsignal berechnen */
  /* '<S2>:1:32' u= d_up+ d_DeltaU1; */
  d_x[0] = d_x_idx_0 - CCS_Speed_o_V7_DW->d_x_old[0];
  d_x[1] = CCS_Speed_o_V7_U_d_delta_theta - CCS_Speed_o_V7_DW->d_x_old[1];
  d_x[2] = rtb_Gain13 - CCS_Speed_o_V7_DW->d_x_old[2];
  d_x[3] = CCS_Speed_o_V7_U_d_delta_theta;
  d_x[4] = rtb_Gain13;
  tmp[0] = 0.0;
  tmp[1] = 0.0;
  tmp[2] = 0.0;
  tmp[3] = 0.0;
  tmp[4] = CCS_Speed_o_V7_P->Gain8_Gain * CCS_Speed_o_V7_U_d_n_ref;
  for (i_0 = 0; i_0 < 5; i_0++) {
    for (i = 0; i < 6; i++) {
      tmp_0[i + 6 * i_0] = -CCS_Speed_o_V7_P->d_invOmegaPhi_F[6 * i_0 + i];
    }

    d_x_0[i_0] = d_x[i_0] - tmp[i_0];
  }

  for (i_0 = 0; i_0 < 6; i_0++) {
    tmp_1[i_0] = 0.0;
    for (i = 0; i < 5; i++) {
      tmp_1[i_0] += tmp_0[6 * i + i_0] * d_x_0[i];
    }
  }

  rtb_Gain13 = CCS_Speed_o_V7_DW->d_up + tmp_1[0];

  /*  Stellsignal Begrenzen (Anti Windup) */
  /* '<S2>:1:35' if (u(1,1)>d_M_max) */
  if (rtb_Gain13 > CCS_Speed_o_V7_P->d_M_max) {
    /* '<S2>:1:35' u(1,1)=d_M_max; */
    rtb_Gain13 = CCS_Speed_o_V7_P->d_M_max;
  }

  /* '<S2>:1:36' if (u(1,1)<-d_M_max) */
  if (rtb_Gain13 < -CCS_Speed_o_V7_P->d_M_max) {
    /* '<S2>:1:36' u(1,1)=-d_M_max; */
    rtb_Gain13 = -CCS_Speed_o_V7_P->d_M_max;
  }

  /*  Abspeichern der Werte für die folgende Samplezeit */
  /* '<S2>:1:40' d_up=u; */
  CCS_Speed_o_V7_DW->d_up = rtb_Gain13;

  /* '<S2>:1:41' d_x_old = d_x; */
  CCS_Speed_o_V7_DW->d_x_old[0] = d_x_idx_0;
  CCS_Speed_o_V7_DW->d_x_old[1] = CCS_Speed_o_V7_U_d_delta_theta;
  CCS_Speed_o_V7_DW->d_x_old[2] = d_x_idx_2;

  /* Outport: '<Root>/d_i_q_ref' incorporates:
   *  Gain: '<S1>/Gain11'
   *  MATLAB Function: '<S1>/CCS-MPC Drehzahlregler'
   */
  /*  Stellsignal ausgeben */
  /* '<S2>:1:44' d_T_el_soll = u(1,1); */
  *CCS_Speed_o_V7_Y_d_i_q_ref = 2.0 / (3.0 * CCS_Speed_o_V7_P->ui8_p *
    CCS_Speed_o_V7_P->d_psi_pm) * rtb_Gain13;
}

/* Model initialize function */
void CCS_Speed_o_V7_initialize(RT_MODEL_CCS_Speed_o_V7_T *const CCS_Speed_o_V7_M,
  real_T *CCS_Speed_o_V7_U_d_n_ref, real_T *CCS_Speed_o_V7_U_d_i_q_meas, real_T *
  CCS_Speed_o_V7_U_d_n_meas, real_T *CCS_Speed_o_V7_U_d_M_L_meas, real_T
  *CCS_Speed_o_V7_U_d_delta_theta, real_T *CCS_Speed_o_V7_U_d_n_L_meas, real_T
  *CCS_Speed_o_V7_Y_d_i_q_ref)
{
  DW_CCS_Speed_o_V7_T *CCS_Speed_o_V7_DW = ((DW_CCS_Speed_o_V7_T *)
    CCS_Speed_o_V7_M->dwork);

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)CCS_Speed_o_V7_DW, 0,
                sizeof(DW_CCS_Speed_o_V7_T));

  /* external inputs */
  *CCS_Speed_o_V7_U_d_n_ref = 0.0;
  *CCS_Speed_o_V7_U_d_i_q_meas = 0.0;
  *CCS_Speed_o_V7_U_d_n_meas = 0.0;
  *CCS_Speed_o_V7_U_d_M_L_meas = 0.0;
  *CCS_Speed_o_V7_U_d_delta_theta = 0.0;
  *CCS_Speed_o_V7_U_d_n_L_meas = 0.0;

  /* external outputs */
  (*CCS_Speed_o_V7_Y_d_i_q_ref) = 0.0;

  /* SystemInitialize for MATLAB Function: '<S1>/CCS-MPC Drehzahlregler' */
  /* '<S2>:1:9' d_up=zeros(1,1); */
  CCS_Speed_o_V7_DW->d_up = 0.0;

  /* '<S2>:1:15' d_x_old=zeros(3,1); */
  CCS_Speed_o_V7_DW->d_x_old[0] = 0.0;
  CCS_Speed_o_V7_DW->d_x_old[1] = 0.0;
  CCS_Speed_o_V7_DW->d_x_old[2] = 0.0;
}

/* Model terminate function */
void CCS_Speed_o_V7_terminate(RT_MODEL_CCS_Speed_o_V7_T *const CCS_Speed_o_V7_M)
{
/* (no terminate code required) */ //  UNUSED_PARAMETER(CCS_Speed_o_V7_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
