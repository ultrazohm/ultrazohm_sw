/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SCF_data.c
 *
 * Code generated for Simulink model 'FOC_SCF'.
 *
 * Model version                  : 5.64
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Feb 19 10:18:19 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_SCF.h"

/* Block parameters (default storage) */
P_FOC_SCF_T FOC_SCF_P = {
  /* Variable: FOC_ENABLE_Idq_Ref
   * Referenced by: '<S2>/FOC_ENABLE_Idq_Ref'
   */
  1.0F,

  /* Variable: FOC_IQ_DIFF_REDUC_GAIN
   * Referenced by: '<S9>/FOC_IQ_DIFF_REDUC_GAIN'
   */
  0.002F,

  /* Variable: FOC_LIMIT_I_PHASE_PEAK_MAX
   * Referenced by: '<S15>/Constant'
   */
  197.989899F,

  /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Down
   * Referenced by:
   *   '<S11>/Constant7'
   *   '<S17>/Constant7'
   */
  -1000.0F,

  /* Variable: FOC_LIMIT_Idq_Ref_SlewRate_Up
   * Referenced by:
   *   '<S11>/Constant6'
   *   '<S17>/Constant6'
   */
  1000.0F,

  /* Variable: FOC_LIMIT_Motor_Torque_MAX
   * Referenced by: '<S8>/Maximum_Torque_Maschine'
   */
  205.0F,

  /* Variable: FOC_LIMIT_Torque_Derating_Temp
   * Referenced by: '<S26>/Constant'
   */
  120.0F,

  /* Variable: FOC_LIMIT_Torque_Ref_MAX
   * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
   */
  110.0F,

  /* Variable: FOC_LIMIT_Torque_Ref_MIN
   * Referenced by: '<S1>/TORQUE_REQ_LIMIT'
   */
  -110.0F,

  /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Down
   * Referenced by: '<S7>/Constant7'
   */
  -100.0F,

  /* Variable: FOC_LIMIT_Torque_Ref_SlewRate_Up
   * Referenced by: '<S7>/Constant6'
   */
  100.0F,

  /* Variable: FOC_LIMIT_n_Ref_SlewRate_Down
   * Referenced by: '<S27>/Constant7'
   */
  -500.0F,

  /* Variable: FOC_LIMIT_n_Ref_SlewRate_InitVal
   * Referenced by: '<S29>/Delay Input2'
   */
  0.0F,

  /* Variable: FOC_LIMIT_n_Ref_SlewRate_Up
   * Referenced by: '<S27>/Constant6'
   */
  500.0F,

  /* Variable: FOC_L_sd
   * Referenced by:
   *   '<S31>/FOC_L_sd'
   *   '<S14>/Constant1'
   */
  0.00033F,

  /* Variable: FOC_L_sq
   * Referenced by:
   *   '<S31>/FOC_L_sq'
   *   '<S14>/Constant2'
   */
  0.0008F,

  /* Variable: FOC_MANUAL_Id_Ref
   * Referenced by: '<S5>/Constant5'
   */
  0.0F,

  /* Variable: FOC_MANUAL_Iq_Ref
   * Referenced by: '<S6>/Constant3'
   */
  0.0F,

  /* Variable: FOC_MANUAL_Torque_Request
   * Referenced by: '<S1>/Constant'
   */
  0.0F,

  /* Variable: FOC_M_peak_max
   * Referenced by: '<S3>/limit T1'
   */
  205.0F,

  /* Variable: FOC_Psi_PM
   * Referenced by:
   *   '<S31>/FOC_Psi_PM'
   *   '<S14>/Constant4'
   */
  0.07F,

  /* Variable: FOC_SELECT_ExtTrqReq
   * Referenced by: '<S1>/Constant2'
   */
  1.0F,

  /* Variable: FOC_SELECT_Id_Ref
   * Referenced by: '<S5>/Constant3'
   */
  4.0F,

  /* Variable: FOC_SELECT_Iq_Ref
   * Referenced by: '<S6>/Constant5'
   */
  4.0F,

  /* Variable: FOC_TORQ_REDUC_GAIN
   * Referenced by: '<S9>/FOC_TORQ_REDUC_GAIN'
   */
  0.04F,

  /* Variable: FOC_TORQ_REDUC_PGAIN
   * Referenced by: '<S9>/FOC_TORQ_REDUC_PGAIN'
   */
  0.15F,

  /* Variable: FOC_TORQ_REDUC_START
   * Referenced by: '<S9>/FOC_TORQ_REDUC_START'
   */
  1.2F,

  /* Variable: FOC_Torque_Derating_Temp_Gain
   * Referenced by: '<S23>/Constant1'
   */
  0.1F,

  /* Variable: SPEED_CTRL_K_AWU
   * Referenced by: '<S3>/Gain1'
   */
  1.0F,

  /* Variable: SPEED_CTRL_LIMIT_n_Ref_MAX
   * Referenced by: '<S3>/limit T2'
   */
  7000.0F,

  /* Variable: SPEED_CTRL_LIMIT_n_Ref_MIN
   * Referenced by: '<S3>/limit T2'
   */
  0.0F,

  /* Variable: SPEED_CTRL_MANUAL_n_RPM
   * Referenced by: '<S3>/OmegaRot2'
   */
  0.0F,

  /* Variable: SPEED_CTRL_TORQLIMNEG
   * Referenced by: '<S3>/Constant5'
   */
  -205.0F,

  /* Variable: SPEED_CTRL_TORQLIMPOS
   * Referenced by: '<S3>/Constant4'
   */
  205.0F,

  /* Variable: SPEED_CTRL_T_N
   * Referenced by: '<S3>/Constant'
   */
  0.5F,

  /* Variable: SPEED_CTRL_V_R
   * Referenced by: '<S3>/Constant14'
   */
  2.0F,

  /* Variable: FOC_SELECT_Idq_Ref_Ramp
   * Referenced by:
   *   '<S11>/Constant5'
   *   '<S17>/Constant5'
   */
  1U,

  /* Variable: FOC_SELECT_Temp_Derating
   * Referenced by: '<S2>/Temp_Derating_Selector'
   */
  0U,

  /* Variable: FOC_SELECT_TorqEstMdl
   * Referenced by: '<S4>/Constant4'
   */
  1U,

  /* Variable: FOC_SELECT_Torque_Ref_Ramp
   * Referenced by: '<S7>/0: ohne Drehmomentrampe 1: mit Drehmomentrampe'
   */
  1U,

  /* Variable: FOC_SELECT_n_Ref_Ramp
   * Referenced by: '<S27>/Constant5'
   */
  1U,

  /* Variable: SPEED_CTRL_SELECT_TorqLimit
   * Referenced by: '<S3>/OmegaRot3'
   */
  1U,

  /* Variable: SPEED_CTRL_SELECT_n_Ref
   * Referenced by: '<S3>/OmegaRot1'
   */
  1U,

  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S24>/Constant'
   */
  0.0F,

  /* Expression: FOC_T_slow
   * Referenced by: '<S29>/FOC_T_slow'
   */
  0.001,

  /* Expression: FOC_T_slow
   * Referenced by: '<S12>/Constant6'
   */
  0.001,

  /* Expression: FOC_T_slow
   * Referenced by: '<S20>/Constant6'
   */
  0.001,

  /* Expression: FOC_T_slow
   * Referenced by: '<S18>/Constant6'
   */
  0.001,

  /* Expression: 0
   * Referenced by: '<S6>/IqRefZero'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S18>/Delay Input2'
   */
  0.0,

  /* Computed Parameter: zero_Current_Value
   * Referenced by: '<S5>/zero_Current'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S5>/Gain'
   */
  0.5F,

  /* Computed Parameter: Id_Ref_M_MTPC_tableData
   * Referenced by: '<S10>/Id_Ref_M_MTPC'
   */
  { 0.0F, -6.00855064F, -18.6489582F, -34.0876961F, -51.3419304F, -69.4636459F,
    -89.1475F, -108.779228F, -130.074341F, -152.355057F, -175.75235F,
    -196.982727F, -216.247208F, -235.417313F, -254.675476F, -275.007843F,
    -293.418152F, -310.50119F, -330.435028F, -350.285706F },

  /* Computed Parameter: Id_Ref_M_MTPC_bp01Data
   * Referenced by: '<S10>/Id_Ref_M_MTPC'
   */
  { -0.00374402152F, 13.3595037F, 28.7598114F, 45.9291649F, 63.6041794F,
    81.6191483F, 99.7469635F, 117.703423F, 135.436905F, 152.716476F, 169.124191F,
    185.131531F, 200.403763F, 215.28064F, 229.630981F, 243.24057F, 255.660156F,
    265.91925F, 275.042145F, 283.534546F },

  /* Computed Parameter: zero_Current_Value_l
   * Referenced by: '<S6>/zero_Current'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain_n
   * Referenced by: '<S14>/Gain'
   */
  0.166666672F,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S14>/Constant'
   */
  1.0F,

  /* Computed Parameter: Gain_Gain_l
   * Referenced by: '<S22>/Gain'
   */
  -1.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S22>/Gain1'
   */
  1.0F,

  /* Computed Parameter: TorqCtrlMinusOne_Gain
   * Referenced by: '<S9>/TorqCtrlMinusOne'
   */
  -1.0F,

  /* Computed Parameter: ZeroTorq_Value
   * Referenced by: '<S3>/ZeroTorq'
   */
  0.0F,

  /* Computed Parameter: ZeroTorq1_Value
   * Referenced by: '<S3>/ZeroTorq1'
   */
  0.0F,

  /* Computed Parameter: ZeroTorq2_Value
   * Referenced by: '<S3>/ZeroTorq2'
   */
  0.0F,

  /* Computed Parameter: TorqReqNm_Y0
   * Referenced by: '<S3>/TorqReq [Nm]'
   */
  0.0F,

  /* Computed Parameter: RPMw_el_Gain
   * Referenced by: '<S3>/RPM => w_el'
   */
  0.418879032F,

  /* Computed Parameter: UnitDelay_InitialCondition
   * Referenced by: '<S3>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: limitT1_LowerSat
   * Referenced by: '<S3>/limit T1'
   */
  0.0F,

  /* Computed Parameter: limitT3_UpperSat
   * Referenced by: '<S3>/limit T3'
   */
  0.0F,

  /* Computed Parameter: limitT3_LowerSat
   * Referenced by: '<S3>/limit T3'
   */
  -205.0F,

  /* Expression: FOC_T_slow
   * Referenced by: '<S3>/FOC_T_slow'
   */
  0.001F,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S3>/Constant3'
   */
  0.0001F,

  /* Computed Parameter: Switch1_Threshold
   * Referenced by: '<S3>/Switch1'
   */
  0.0F,

  /* Computed Parameter: Switch2_Threshold
   * Referenced by: '<S1>/Switch2'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_n
   * Referenced by: '<S4>/Constant'
   */
  0.0F,

  /* Computed Parameter: uZ_p2_Gain
   * Referenced by: '<S31>/3*Z_p//2'
   */
  6.0F,

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S25>/Constant'
   */
  0.0F,

  /* Computed Parameter: Bias_Bias
   * Referenced by: '<S5>/Bias'
   */
  1.0F,

  /* Computed Parameter: IdRefZero1_Value
   * Referenced by: '<S5>/IdRefZero1'
   */
  0.0F,

  /* Computed Parameter: UnitDelay_InitialCondition_e
   * Referenced by: '<S23>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Saturation_UpperSat
   * Referenced by: '<S23>/Saturation'
   */
  1.0F,

  /* Computed Parameter: Saturation_LowerSat
   * Referenced by: '<S23>/Saturation'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S23>/Constant2'
   */
  1.0F,

  /* Computed Parameter: DelayInput2_InitialCondition_l
   * Referenced by: '<S20>/Delay Input2'
   */
  0.0F,

  /* Computed Parameter: TorqCtrlDelay_InitialCondition
   * Referenced by: '<S9>/TorqCtrlDelay'
   */
  1.0F,

  /* Computed Parameter: Saturation_UpperSat_h
   * Referenced by: '<S9>/Saturation'
   */
  1.0F,

  /* Computed Parameter: Saturation_LowerSat_e
   * Referenced by: '<S9>/Saturation'
   */
  0.0F,

  /* Computed Parameter: DelayInput2_InitialCondition_g
   * Referenced by: '<S12>/Delay Input2'
   */
  0.0F,

  /* Computed Parameter: Bias_Bias_k
   * Referenced by: '<S6>/Bias'
   */
  1.0F,

  /* Computed Parameter: Gain_Gain_d
   * Referenced by: '<S6>/Gain'
   */
  0.5F,

  /* Computed Parameter: Iq_Ref_M_MTPC_tableData
   * Referenced by: '<S16>/Iq_Ref_M_MTPC'
   */
  { 0.0F, 24.5382252F, 46.9587593F, 67.6910172F, 87.0381546F, 105.501091F,
    122.592422F, 139.428146F, 154.684204F, 168.773026F, 181.476791F, 196.018585F,
    212.466125F, 228.995804F, 245.423965F, 260.714F, 278.014282F, 296.709717F,
    312.407227F, 328.176666F },

  /* Computed Parameter: Iq_Ref_M_MTPC_bp01Data
   * Referenced by: '<S16>/Iq_Ref_M_MTPC'
   */
  { -0.00374402152F, 13.3595037F, 28.7598114F, 45.9291649F, 63.6041794F,
    81.6191483F, 99.7469635F, 117.703423F, 135.436905F, 152.716476F, 169.124191F,
    185.131531F, 200.403763F, 215.28064F, 229.630981F, 243.24057F, 255.660156F,
    265.91925F, 275.042145F, 283.534546F },

  /* Computed Parameter: PsiReduceGain1_Gain
   * Referenced by: '<S15>/PsiReduceGain1'
   */
  -1.0F,

  /* Computed Parameter: usrpm_Gain
   * Referenced by: '<S1>/[1//s] => [rpm]'
   */
  2.38732409F,

  /* Computed Parameter: UnitDelay_InitialCondition_l
   * Referenced by: '<S15>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_i
   * Referenced by: '<S8>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Constant_Value_gz
   * Referenced by: '<S23>/Constant'
   */
  0.5F,

  /* Computed Parameter: UnitDelay_InitialCondition_a
   * Referenced by: '<S9>/UnitDelay'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain_j
   * Referenced by: '<S9>/Gain'
   */
  1.0F,

  /* Computed Parameter: Gain1_Gain_c
   * Referenced by: '<S9>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S9>/Gain2'
   */
  1.0F,

  /* Computed Parameter: TorqCtrlSwitch1_Threshold
   * Referenced by: '<S9>/TorqCtrlSwitch1'
   */
  0.0F,

  /* Computed Parameter: TorqCtrlSwitch3_Threshold
   * Referenced by: '<S9>/TorqCtrlSwitch3'
   */
  0.0F,

  /* Computed Parameter: I_ph_peak_Gain
   * Referenced by: '<S4>/I_ph_peak'
   */
  1.0F,

  /* Computed Parameter: I_ph_rms_Gain
   * Referenced by: '<S4>/I_ph_rms'
   */
  0.707106769F,

  /* Computed Parameter: TorqEst_Nm_Gain
   * Referenced by: '<S4>/TorqEst_Nm'
   */
  1.0F,

  /* Computed Parameter: Counter_Start_Value
   * Referenced by: '<S1>/Counter_Start'
   */
  1.0F,

  /* Computed Parameter: SCF_Cnt_InitialCondition
   * Referenced by: '<S1>/SCF_Cnt'
   */
  0.0F,

  /* Computed Parameter: Switch1_Threshold_k
   * Referenced by: '<S22>/Switch1'
   */
  0U,

  /* Computed Parameter: Switch2_Threshold_l
   * Referenced by: '<S27>/Switch2'
   */
  0U,

  /* Computed Parameter: Switch4_Threshold
   * Referenced by: '<S7>/Switch4'
   */
  0U,

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<S2>/Switch'
   */
  0U,

  /* Computed Parameter: Switch2_Threshold_f
   * Referenced by: '<S11>/Switch2'
   */
  0U,

  /* Computed Parameter: Switch2_Threshold_n
   * Referenced by: '<S17>/Switch2'
   */
  0U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
