/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF_data.c
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.21
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Jan 15 19:21:22 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_FCF.h"

/* Block parameters (default storage) */
P_FOC_FCF_T FOC_FCF_P = {
  /* Variable: FOC_ENABLE_Overcurrent_I_uvw
   * Referenced by: '<S6>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  1.0,

  /* Variable: FOC_ENABLE_Overvoltage_U_DC
   * Referenced by: '<S7>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  1.0,

  /* Variable: FOC_ENABLE_Undervoltage_U_DC
   * Referenced by: '<S7>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  0.0,

  /* Variable: FOC_RESET_OC_Error
   * Referenced by: '<S6>/Reset_OC_Error'
   */
  0.0,

  /* Variable: FOC_RESET_OV_Error
   * Referenced by: '<S7>/Reset_OV_Error'
   */
  0.0,

  /* Variable: FOC_9ph_AngleShift
   * Referenced by:
   *   '<S4>/FOC_9ph_AngleShift'
   *   '<S5>/FOC_9ph_AngleShift'
   *   '<S9>/FOC_9ph_AngleShift'
   */
  0.34906584F,

  /* Variable: FOC_ASC_Mode
   * Referenced by: '<S2>/FOC_AKS_Mode'
   */
  1.0F,

  /* Variable: FOC_AngleObs_w_InitVal
   * Referenced by: '<S14>/Unit Delay1'
   */
  0.0F,

  /* Variable: FOC_AngleObserver_D
   * Referenced by: '<S11>/Constant1'
   */
  1.0F,

  /* Variable: FOC_AngleObserver_w0
   * Referenced by: '<S11>/Constant'
   */
  200.0F,

  /* Variable: FOC_Enable
   * Referenced by: '<S1>/Enable'
   */
  1.0F,

  /* Variable: FOC_IntegDamp
   * Referenced by:
   *   '<S24>/FOC_IntegDamp'
   *   '<S28>/FOC_IntegDamp'
   *   '<S32>/FOC_IntegDamp'
   */
  0.995F,

  /* Variable: FOC_KI
   * Referenced by:
   *   '<S24>/FOC_KI'
   *   '<S28>/FOC_KI'
   *   '<S32>/FOC_KI'
   */
  100.0F,

  /* Variable: FOC_KP
   * Referenced by:
   *   '<S24>/FOC_KP1'
   *   '<S28>/FOC_KP1'
   *   '<S32>/FOC_KP1'
   */
  1.0F,

  /* Variable: FOC_LIMIT_Overcurrent_I_uvw
   * Referenced by: '<S35>/Constant'
   */
  10.0F,

  /* Variable: FOC_LIMIT_Overvoltage_U_DC
   * Referenced by: '<S40>/Constant'
   */
  900.0F,

  /* Variable: FOC_LIMIT_Undervoltage_U_DC
   * Referenced by: '<S39>/Constant'
   */
  50.0F,

  /* Variable: FOC_MANUAL_U_DC
   * Referenced by: '<S1>/Udc1'
   */
  0.0F,

  /* Variable: FOC_MaxModInd
   * Referenced by:
   *   '<S23>/FOC_MaxModInd'
   *   '<S27>/FOC_MaxModInd'
   *   '<S31>/FOC_MaxModInd'
   */
  1.1F,

  /* Variable: FOC_Mode_Intern
   * Referenced by: '<S1>/FOC_Mode_Intern'
   */
  3.0F,

  /* Variable: FOC_OmegaObs3
   * Referenced by: '<S11>/Gain4'
   */
  0.0F,

  /* Variable: FOC_PhiSensorTdead
   * Referenced by: '<S11>/DeadTimeCompensation'
   */
  0.0F,

  /* Variable: FOC_SELECT_Voltage_Assignment_UVW
   * Referenced by: '<S50>/Constant6'
   */
  1.0F,

  /* Variable: FOC_Uf_U_max
   * Referenced by: '<S46>/Saturation1'
   */
  0.0F,

  /* Variable: FOC_Uf_U_min
   * Referenced by: '<S46>/Saturation1'
   */
  0.0F,

  /* Variable: FOC_Uf_Ud
   * Referenced by: '<S9>/Uf_Ud'
   */
  0.0F,

  /* Variable: FOC_Uf_f_el
   * Referenced by: '<S9>/Uf_w_el'
   */
  0.0F,

  /* Variable: FOC_Uf_m
   * Referenced by: '<S46>/Gain'
   */
  0.0F,

  /* Variable: FOC_output_trafo_delay
   * Referenced by: '<S4>/FOC_output_trafo_delay'
   */
  1.5F,

  /* Variable: FOC_phi_offset
   * Referenced by: '<S3>/Constant'
   */
  1.794F,

  /* Variable: FOC_SELECT_Mode_Intern
   * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
   */
  0U,

  /* Variable: FOC_SELECT_Modulation
   * Referenced by: '<S10>/Enable_SuperSinMod'
   */
  1U,

  /* Variable: FOC_SELECT_U_DC_INPUT
   * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
   */
  1U,

  /* Variable: FOC_SELECT_phi
   * Referenced by: '<S3>/Constant3'
   */
  2U,

  /* Mask Parameter: AntiWindupGT_d_const
   * Referenced by: '<S25>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const
   * Referenced by: '<S26>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_d_const_n
   * Referenced by: '<S29>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const_h
   * Referenced by: '<S30>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_d_const_f
   * Referenced by: '<S33>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const_l
   * Referenced by: '<S34>/Constant'
   */
  0.0F,

  /* Mask Parameter: SRFlipFlop_initial_condition
   * Referenced by: '<S42>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop1_initial_condition
   * Referenced by: '<S43>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop_initial_condition_a
   * Referenced by: '<S37>/Memory'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit
   * Referenced by: '<S41>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit_o
   * Referenced by: '<S36>/Delay Input1'
   */
  false,

  /* Expression: 1
   * Referenced by: '<S1>/Constant1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S38>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S44>/Constant'
   */
  0.0,

  /* Computed Parameter: ASC_LS_Value
   * Referenced by: '<S2>/ASC_LS'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: ASC_HS_Value
   * Referenced by: '<S2>/ASC_HS'
   */
  { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F },

  /* Computed Parameter: ASC_LSHS_Value
   * Referenced by: '<S2>/ASC_LSHS'
   */
  { 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F },

  /* Computed Parameter: Constant5_Value
   * Referenced by: '<S13>/Constant5'
   */
  -6.28318548F,

  /* Computed Parameter: Constant6_Value
   * Referenced by: '<S13>/Constant6'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S13>/Constant2'
   */
  6.28318548F,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S13>/Constant4'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_n
   * Referenced by: '<S16>/Constant'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_d
   * Referenced by: '<S16>/Constant1'
   */
  6.28318548F,

  /* Computed Parameter: Zero_Value
   * Referenced by: '<S24>/Zero'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold
   * Referenced by: '<S24>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold_a
   * Referenced by: '<S28>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold_ad
   * Referenced by: '<S32>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S8>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_k
   * Referenced by: '<S8>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Zero_Value_o
   * Referenced by: '<S28>/Zero'
   */
  0.0F,

  /* Computed Parameter: Zero_Value_n
   * Referenced by: '<S32>/Zero'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_e
   * Referenced by: '<S12>/Constant'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_g
   * Referenced by: '<S12>/Constant1'
   */
  6.28318548F,

  /* Computed Parameter: Switch1_Threshold
   * Referenced by: '<S12>/Switch1'
   */
  6.28318548F,

  /* Computed Parameter: Switch2_Threshold
   * Referenced by: '<S12>/Switch2'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_a
   * Referenced by: '<S45>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_e
   * Referenced by: '<S45>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value_d
   * Referenced by: '<S48>/Constant2'
   */
  1.0F,

  /* Computed Parameter: U_DC2_Gain
   * Referenced by: '<S48>/U_DC//2'
   */
  0.5F,

  /* Computed Parameter: Constant2_Value_g
   * Referenced by: '<S49>/Constant2'
   */
  1.0F,

  /* Computed Parameter: U_DC2_Gain_p
   * Referenced by: '<S49>/U_DC//2'
   */
  0.5F,

  /* Computed Parameter: Factor_Gain
   * Referenced by: '<S51>/Factor'
   */
  0.5F,

  /* Computed Parameter: Factor1_Gain
   * Referenced by: '<S51>/Factor1'
   */
  0.5F,

  /* Computed Parameter: Factor2_Gain
   * Referenced by: '<S51>/Factor2'
   */
  0.5F,

  /* Computed Parameter: Constant_Value_d
   * Referenced by: '<S52>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Null_Value
   * Referenced by: '<S1>/Null'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: DiscreteTransferFcn_NumCoef
   * Referenced by: '<S9>/Discrete Transfer Fcn'
   */
  0.005F,

  /* Computed Parameter: DiscreteTransferFcn_DenCoef
   * Referenced by: '<S9>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.995F },

  /* Computed Parameter: DiscreteTransferFcn_InitialStat
   * Referenced by: '<S9>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: f_2_w_el_Gain
   * Referenced by: '<S9>/f_2_w_el'
   */
  6.28318548F,

  /* Computed Parameter: FOC_T_fast_Value
   * Referenced by: '<S45>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition
   * Referenced by: '<S45>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain
   * Referenced by: '<S20>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: ResolverOffsetLimitation_UpperS
   * Referenced by: '<S3>/ResolverOffsetLimitation'
   */
  6.28318548F,

  /* Computed Parameter: ResolverOffsetLimitation_LowerS
   * Referenced by: '<S3>/ResolverOffsetLimitation'
   */
  0.0F,

  /* Computed Parameter: UnitDelay_InitialCondition_b
   * Referenced by: '<S13>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S13>/Constant3'
   */
  -3.14159274F,

  /* Computed Parameter: Constant1_Value_ep
   * Referenced by: '<S13>/Constant1'
   */
  3.14159274F,

  /* Computed Parameter: UnitDelay3_InitialCondition
   * Referenced by: '<S11>/Unit Delay3'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_d
   * Referenced by: '<S8>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition_p
   * Referenced by: '<S8>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: IntegDelay1_InitialCondition
   * Referenced by: '<S24>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_n
   * Referenced by: '<S24>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_p
   * Referenced by: '<S21>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: IntegDelay1_InitialCondition_m
   * Referenced by: '<S28>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_e
   * Referenced by: '<S28>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_j
   * Referenced by: '<S22>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: IntegDelay1_InitialCondition_p
   * Referenced by: '<S32>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_er
   * Referenced by: '<S32>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: FOC_T_fast_Value_m
   * Referenced by: '<S4>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Switch1_Threshold_a
   * Referenced by: '<S16>/Switch1'
   */
  6.28318548F,

  /* Computed Parameter: Switch2_Threshold_o
   * Referenced by: '<S16>/Switch2'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_h
   * Referenced by: '<S55>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S55>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S53>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Gain1_Gain_c
   * Referenced by: '<S56>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain_l
   * Referenced by: '<S56>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant_Value_oq
   * Referenced by: '<S54>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Gain1_Gain_k
   * Referenced by: '<S57>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain_j
   * Referenced by: '<S57>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Scale02_Bias
   * Referenced by: '<S47>/Scale [0..2]'
   */
  1.0F,

  /* Computed Parameter: Scale01_Gain
   * Referenced by: '<S47>/Scale  [0..1]'
   */
  0.5F,

  /* Computed Parameter: Limit01_UpperSat
   * Referenced by: '<S47>/Limit [0..1]'
   */
  1.0F,

  /* Computed Parameter: Limit01_LowerSat
   * Referenced by: '<S47>/Limit [0..1]'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_df
   * Referenced by: '<S11>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Gain_Gain_k
   * Referenced by: '<S11>/Gain'
   */
  2.0F,

  /* Computed Parameter: UnitDelay1_InitialCondition
   * Referenced by: '<S15>/Unit Delay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_c
   * Referenced by: '<S14>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: FOC_T_fast_Value_k
   * Referenced by: '<S15>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Gain1_Gain_kl
   * Referenced by: '<S4>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Zero1_Value
   * Referenced by: '<S24>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: Gain1_Gain_cs
   * Referenced by: '<S17>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S17>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Zero1_Value_l
   * Referenced by: '<S28>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: Zero1_Value_o
   * Referenced by: '<S32>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_Init
   * Referenced by: '<S20>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Coef
   * Referenced by: '<S20>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_In_k
   * Referenced by: '<S21>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Co_a
   * Referenced by: '<S21>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_In_n
   * Referenced by: '<S22>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Co_l
   * Referenced by: '<S22>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: Gain1_Gain_f
   * Referenced by: '<S6>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain1_Gain_g
   * Referenced by: '<S7>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain_n
   * Referenced by: '<S7>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<S8>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Switch_Threshold_c
   * Referenced by: '<S45>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Gain_Gain_jm
   * Referenced by: '<S10>/Gain'
   */
  1.0F,

  /* Computed Parameter: Gain1_Gain_e
   * Referenced by: '<S10>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain_f
   * Referenced by: '<S10>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S10>/Gain3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u1_Gain
   * Referenced by: '<S50>/DutyCycle_u1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u2_Gain
   * Referenced by: '<S50>/DutyCycle_u2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u3_Gain
   * Referenced by: '<S50>/DutyCycle_u3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v1_Gain
   * Referenced by: '<S50>/DutyCycle_v1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v2_Gain
   * Referenced by: '<S50>/DutyCycle_v2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v3_Gain
   * Referenced by: '<S50>/DutyCycle_v3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w1_Gain
   * Referenced by: '<S50>/DutyCycle_w1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w2_Gain
   * Referenced by: '<S50>/DutyCycle_w2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w3_Gain
   * Referenced by: '<S50>/DutyCycle_w3'
   */
  1.0F,

  /* Computed Parameter: Constant_Value_e2
   * Referenced by: '<S1>/Constant'
   */
  0.0F,

  /* Computed Parameter: Counter_Start_Value
   * Referenced by: '<S1>/Counter_Start'
   */
  1.0F,

  /* Computed Parameter: FCF_Cnt_InitialCondition
   * Referenced by: '<S1>/FCF_Cnt'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value_o
   * Referenced by: '<S6>/Constant2'
   */
  true,

  /* Computed Parameter: Constant1_Value_gm
   * Referenced by: '<S6>/Constant1'
   */
  true,

  /* Computed Parameter: Constant3_Value_i
   * Referenced by: '<S7>/Constant3'
   */
  true,

  /* Computed Parameter: Constant1_Value_j
   * Referenced by: '<S7>/Constant1'
   */
  true,

  /* Computed Parameter: Constant2_Value_j
   * Referenced by: '<S7>/Constant2'
   */
  true,

  /* Computed Parameter: Constant4_Value_b
   * Referenced by: '<S7>/Constant4'
   */
  true,

  /* Computed Parameter: Logic_table
   * Referenced by: '<S42>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_m
   * Referenced by: '<S43>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_f
   * Referenced by: '<S37>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Switch1_Threshold_m
   * Referenced by: '<S1>/Switch1'
   */
  0U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
