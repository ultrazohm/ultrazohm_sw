/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_slowCTRL_data.c
 *
 * Code generated for Simulink model 'FOC_slowCTRL'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Oct  9 23:28:30 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_slowCTRL.h"

/* Block parameters (default storage) */
P_FOC_slowCTRL_T FOC_slowCTRL_P = {
  /* Variable: FOC_ENABLE_Idq_Ref
   * Referenced by: '<S2>/FOC_ENABLE_Idq_Ref'
   */
  1.0,

  /* Variable: FOC_IQ_DIFF_REDUC_GAIN
   * Referenced by: '<S9>/FOC_IQ_DIFF_REDUC_GAIN'
   */
  0.002,

  /* Variable: FOC_LIMIT_I_PHASE_PEAK_MAX
   * Referenced by: '<S15>/Constant'
   */
  197.98989873223331,

  /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Down
   * Referenced by:
   *   '<S11>/Constant7'
   *   '<S17>/Constant7'
   */
  -1000.0,

  /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Up
   * Referenced by:
   *   '<S11>/Constant6'
   *   '<S17>/Constant6'
   */
  1000.0,

  /* Variable: FOC_LIMIT_Motor_Torque_MAX
   * Referenced by: '<S8>/Maximum_Torque_Maschine'
   */
  205.0,

  /* Variable: FOC_LIMIT_Torque_Derating_Temp
   * Referenced by: '<S26>/Constant'
   */
  120.0,

  /* Variable: FOC_LIMIT_Torque_Ref_MAX
   * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
   */
  110.0,

  /* Variable: FOC_LIMIT_Torque_Ref_MIN
   * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
   */
  -110.0,

  /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Down
   * Referenced by: '<S7>/Constant7'
   */
  -100.0,

  /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Up
   * Referenced by: '<S7>/Constant6'
   */
  100.0,

  /* Variable: FOC_LIMIT_n_Ref_SlewRate_Down
   * Referenced by: '<S27>/Constant7'
   */
  -500.0,

  /* Variable: FOC_LIMIT_n_Ref_SlewRate_InitVal
   * Referenced by: '<S29>/Delay Input2'
   */
  0.0,

  /* Variable: FOC_LIMIT_n_Ref_SlewRate_Up
   * Referenced by: '<S27>/Constant6'
   */
  500.0,

  /* Variable: FOC_L_sd
   * Referenced by:
   *   '<S31>/FOC_L_sd'
   *   '<S14>/Constant1'
   */
  0.00033,

  /* Variable: FOC_L_sq
   * Referenced by:
   *   '<S31>/FOC_L_sq'
   *   '<S14>/Constant2'
   */
  0.0008,

  /* Variable: FOC_MANUAL_Id_Ref
   * Referenced by: '<S5>/Constant5'
   */
  0.0,

  /* Variable: FOC_MANUAL_Iq_Ref
   * Referenced by: '<S6>/Constant3'
   */
  0.0,

  /* Variable: FOC_MANUAL_Torque_Request
   * Referenced by: '<S1>/Constant'
   */
  0.0,

  /* Variable: FOC_M_peak_max
   * Referenced by:
   *   '<S3>/limit T1'
   *   '<S3>/limit T3'
   */
  205.0,

  /* Variable: FOC_Psi_PM
   * Referenced by:
   *   '<S31>/FOC_Psi_PM'
   *   '<S14>/Constant4'
   */
  0.07,

  /* Variable: FOC_SELECT_ExtTrqReq
   * Referenced by: '<S1>/Constant2'
   */
  1.0,

  /* Variable: FOC_SELECT_Id_Ref
   * Referenced by: '<S5>/Constant3'
   */
  4.0,

  /* Variable: FOC_SELECT_Idq_Ref_Ramp
   * Referenced by:
   *   '<S11>/Constant5'
   *   '<S17>/Constant5'
   */
  1.0,

  /* Variable: FOC_SELECT_Iq_Ref
   * Referenced by: '<S6>/Constant5'
   */
  4.0,

  /* Variable: FOC_SELECT_Temp_Derating
   * Referenced by: '<S2>/Temp_Derating_Selector'
   */
  0.0,

  /* Variable: FOC_SELECT_TorqEstMdl
   * Referenced by: '<S4>/Constant4'
   */
  1.0,

  /* Variable: FOC_SELECT_Torque_Ref_Ramp
   * Referenced by: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
   */
  1.0,

  /* Variable: FOC_SELECT_n_Ref_Ramp
   * Referenced by: '<S27>/Constant5'
   */
  1.0,

  /* Variable: FOC_TORQ_REDUC_GAIN
   * Referenced by: '<S9>/FOC_TORQ_REDUC_GAIN'
   */
  0.04,

  /* Variable: FOC_TORQ_REDUC_PGAIN
   * Referenced by: '<S9>/FOC_TORQ_REDUC_PGAIN'
   */
  0.15,

  /* Variable: FOC_TORQ_REDUC_START
   * Referenced by: '<S9>/FOC_TORQ_REDUC_START'
   */
  1.2,

  /* Variable: FOC_T_slow
   * Referenced by:
   *   '<S3>/FOC_T_slow'
   *   '<S20>/Constant6'
   *   '<S29>/FOC_T_slow'
   *   '<S12>/Constant6'
   *   '<S18>/Constant6'
   */
  0.001,

  /* Variable: FOC_Torque_Derating_Temp_Gain
   * Referenced by: '<S23>/Constant1'
   */
  0.1,

  /* Variable: FOC_z_P
   * Referenced by:
   *   '<S2>/[1//s] => [rpm]'
   *   '<S3>/RPM => w_el'
   *   '<S31>/3*Z_p//2'
   *   '<S14>/Gain'
   */
  4.0,

  /* Variable: SCF_MANUAL_U_DC
   * Referenced by: '<S1>/Udc2'
   */
  0.0,

  /* Variable: SCF_SELECT_U_DC_INPUT
   * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
   */
  1.0,

  /* Variable: SPEED_CTRL_K_AWU
   * Referenced by: '<S3>/Gain1'
   */
  1.0,

  /* Variable: SPEED_CTRL_LIMIT_n_Ref_MAX
   * Referenced by: '<S3>/limit T2'
   */
  7000.0,

  /* Variable: SPEED_CTRL_LIMIT_n_Ref_MIN
   * Referenced by: '<S3>/limit T2'
   */
  0.0,

  /* Variable: SPEED_CTRL_MANUAL_n_RPM
   * Referenced by: '<S3>/OmegaRot2'
   */
  0.0,

  /* Variable: SPEED_CTRL_SELECT_TorqLimit
   * Referenced by: '<S3>/OmegaRot3'
   */
  1.0,

  /* Variable: SPEED_CTRL_SELECT_n_Ref
   * Referenced by: '<S3>/OmegaRot1'
   */
  1.0,

  /* Variable: SPEED_CTRL_TORQLIMNEG
   * Referenced by: '<S3>/Constant5'
   */
  -205.0,

  /* Variable: SPEED_CTRL_TORQLIMPOS
   * Referenced by: '<S3>/Constant4'
   */
  205.0,

  /* Variable: SPEED_CTRL_T_N
   * Referenced by: '<S3>/Constant'
   */
  0.5,

  /* Variable: SPEED_CTRL_V_R
   * Referenced by: '<S3>/Constant14'
   */
  2.0,

  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S24>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/zero_Current'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<S5>/Gain'
   */
  0.5,

  /* Expression: EMotor.FEM_data.I_d_M_MTPC.z
   * Referenced by: '<S10>/Id_Ref_M_MTPC'
   */
  { 0.0, -6.0085507565999023, -18.648957730588887, -34.087694712758278,
    -51.341930212302486, -69.463648350175035, -89.147496569685,
    -108.77923084485306, -130.07433517891718, -152.35506238888672,
    -175.7523467698949, -196.98273335018547, -216.24720550552323,
    -235.4173141375534, -254.67547233773774, -275.0078579954727,
    -293.41814944651691, -310.50118965849134, -330.43503338670251,
    -350.28571483439976 },

  /* Expression: EMotor.FEM_data.I_d_M_MTPC.x1
   * Referenced by: '<S10>/Id_Ref_M_MTPC'
   */
  { -0.0037440216292055259, 13.359503610375837, 28.759810625246441,
    45.929165491622321, 63.604180053639332, 81.619150254687, 99.746961563665309,
    117.70342630475001, 135.43690802915745, 152.71648178418585,
    169.1241970850904, 185.1315247301477, 200.40375682762257, 215.28064383481677,
    229.63097844075426, 243.24056984417842, 255.66015213399, 265.91923550417084,
    275.04214125891735, 283.53453237990743 },

  /* Expression: 0
   * Referenced by: '<S6>/zero_Current'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S14>/Constant'
   */
  1.0,

  /* Expression: 0.5
   * Referenced by: '<S6>/Gain'
   */
  0.5,

  /* Expression: EMotor.FEM_data.I_q_M_MTPC.z
   * Referenced by: '<S16>/Iq_Ref_M_MTPC'
   */
  { 0.0, 24.538224561279229, 46.958758105600779, 67.691014104528165,
    87.038155719807918, 105.50109112347292, 122.59241877325269,
    139.42815042418079, 154.68420967857253, 168.77302467054739,
    181.47679544866077, 196.01858974707645, 212.46612730580426,
    228.99579912281109, 245.42396901112454, 260.71399286187716,
    278.0142786978198, 296.70971782202292, 312.40724107900553,
    328.17665666977837 },

  /* Expression: EMotor.FEM_data.I_q_M_MTPC.x1
   * Referenced by: '<S16>/Iq_Ref_M_MTPC'
   */
  { -0.0037440216292055259, 13.359503610375837, 28.759810625246441,
    45.929165491622321, 63.604180053639332, 81.619150254687, 99.746961563665309,
    117.70342630475001, 135.43690802915745, 152.71648178418585,
    169.1241970850904, 185.1315247301477, 200.40375682762257, 215.28064383481677,
    229.63097844075426, 243.24056984417842, 255.66015213399, 265.91923550417084,
    275.04214125891735, 283.53453237990743 },

  /* Expression: -1
   * Referenced by: '<S22>/Gain'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<S22>/Gain1'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S9>/TorqCtrlMinusOne'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S3>/ZeroTorq'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/ZeroTorq1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/ZeroTorq2'
   */
  0.0,

  /* Computed Parameter: TorqReqNm_Y0
   * Referenced by: '<S3>/TorqReq [Nm]'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S27>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/Unit Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/limit T1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/limit T3'
   */
  0.0,

  /* Expression: 0.0001
   * Referenced by: '<S3>/Constant3'
   */
  0.0001,

  /* Expression: 0
   * Referenced by: '<S3>/Switch1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/Constant'
   */
  0.0,

  /* Expression: 2
   * Referenced by: '<S4>/3ph_to_6ph_factor'
   */
  2.0,

  /* Expression: 0
   * Referenced by: '<S25>/Constant'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S5>/Bias'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S23>/Unit Delay'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S23>/Saturation'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S23>/Saturation'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S23>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S20>/Delay Input2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S7>/Switch4'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Switch'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S9>/TorqCtrlDelay'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S9>/Saturation'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S9>/Saturation'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/IdRefZero1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S12>/Delay Input2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S11>/Switch2'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S6>/Bias'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S6>/IqRefZero'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S18>/Delay Input2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S17>/Switch2'
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<S15>/PsiReduceGain1'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S15>/Unit Delay'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S8>/Gain1'
   */
  1.0,

  /* Expression: 0.5
   * Referenced by: '<S23>/Constant'
   */
  0.5,

  /* Expression: 0
   * Referenced by: '<S9>/UnitDelay'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S9>/Gain'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S9>/Gain1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S9>/Gain2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S9>/TorqCtrlSwitch1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S9>/TorqCtrlSwitch3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Switch1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S4>/I_ph_peak'
   */
  1.0,

  /* Expression: 1/sqrt(2)
   * Referenced by: '<S4>/I_ph_rms'
   */
  0.70710678118654746,

  /* Expression: 1
   * Referenced by: '<S4>/TorqEst_Nm'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Counter_Start'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S1>/SCF_Cnt'
   */
  0.0,

  /* Computed Parameter: Switch1_Threshold_n
   * Referenced by: '<S22>/Switch1'
   */
  0U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
