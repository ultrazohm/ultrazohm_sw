/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF_data.c
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Nov 18 19:20:46 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_FCF.h"

/* Block parameters (default storage) */
P_FOC_FCF_T FOC_FCF_P = {
  /* Variable: FOC_6ph_AngleShift
   * Referenced by:
   *   '<S4>/FOC_6ph_AngleShift'
   *   '<S5>/FOC_6ph_AngleShift'
   *   '<S7>/FOC_6ph_AngleShift'
   */
  0.0F,

  /* Variable: FOC_ASC_Mode
   * Referenced by: '<S2>/FOC_AKS_Mode'
   */
  1.0F,

  /* Variable: FOC_AngleObs_w_InitVal
   * Referenced by: '<S12>/Unit Delay1'
   */
  0.0F,

  /* Variable: FOC_AngleObserver_D
   * Referenced by: '<S9>/Constant1'
   */
  1.0F,

  /* Variable: FOC_AngleObserver_w0
   * Referenced by: '<S9>/Constant'
   */
  200.0F,

  /* Variable: FOC_Enable
   * Referenced by: '<S1>/Enable'
   */
  1.0F,

  /* Variable: FOC_IntegDamp
   * Referenced by:
   *   '<S20>/FOC_IntegDamp'
   *   '<S24>/FOC_IntegDamp'
   */
  0.995F,

  /* Variable: FOC_KI
   * Referenced by:
   *   '<S20>/FOC_KI'
   *   '<S24>/FOC_KI'
   */
  1000.0F,

  /* Variable: FOC_KP
   * Referenced by:
   *   '<S20>/FOC_KP1'
   *   '<S24>/FOC_KP1'
   */
  1.0F,

  /* Variable: FOC_MANUAL_U_DC
   * Referenced by: '<S1>/Udc1'
   */
  0.0F,

  /* Variable: FOC_MaxModInd
   * Referenced by:
   *   '<S19>/FOC_MaxModInd'
   *   '<S23>/FOC_MaxModInd'
   */
  1.1F,

  /* Variable: FOC_Mode_Intern
   * Referenced by: '<S1>/FOC_Mode_Intern'
   */
  3.0F,

  /* Variable: FOC_OmegaObs3
   * Referenced by: '<S9>/Gain4'
   */
  0.0F,

  /* Variable: FOC_PhiSensorTdead
   * Referenced by: '<S9>/DeadTimeCompensation'
   */
  0.0F,

  /* Variable: FOC_Uf_U_max
   * Referenced by: '<S28>/Saturation1'
   */
  0.0F,

  /* Variable: FOC_Uf_U_min
   * Referenced by: '<S28>/Saturation1'
   */
  0.0F,

  /* Variable: FOC_Uf_Ud
   * Referenced by: '<S7>/Uf_Ud'
   */
  0.0F,

  /* Variable: FOC_Uf_f_el
   * Referenced by: '<S7>/Uf_w_el'
   */
  0.0F,

  /* Variable: FOC_Uf_m
   * Referenced by: '<S28>/Gain'
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
   * Referenced by: '<S8>/Enable_SuperSinMod'
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
   * Referenced by: '<S21>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const
   * Referenced by: '<S22>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_d_const_n
   * Referenced by: '<S25>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const_h
   * Referenced by: '<S26>/Constant'
   */
  0.0F,

  /* Computed Parameter: Scale02_Bias
   * Referenced by: '<S8>/Scale [0..2]'
   */
  1.0F,

  /* Computed Parameter: Scale01_Gain
   * Referenced by: '<S8>/Scale  [0..1]'
   */
  0.5F,

  /* Computed Parameter: Limit01_UpperSat
   * Referenced by: '<S8>/Limit [0..1]'
   */
  1.0F,

  /* Computed Parameter: Limit01_LowerSat
   * Referenced by: '<S8>/Limit [0..1]'
   */
  0.0F,

  /* Computed Parameter: ASC_LS_Value
   * Referenced by: '<S2>/ASC_LS'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: ASC_HS_Value
   * Referenced by: '<S2>/ASC_HS'
   */
  { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F },

  /* Computed Parameter: ASC_LSHS_Value
   * Referenced by: '<S2>/ASC_LSHS'
   */
  { 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F },

  /* Computed Parameter: Constant5_Value
   * Referenced by: '<S11>/Constant5'
   */
  -6.28318548F,

  /* Computed Parameter: Constant6_Value
   * Referenced by: '<S11>/Constant6'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S11>/Constant2'
   */
  6.28318548F,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S11>/Constant4'
   */
  0.0F,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S14>/Constant'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<S14>/Constant1'
   */
  6.28318548F,

  /* Computed Parameter: Zero_Value
   * Referenced by: '<S20>/Zero'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold
   * Referenced by: '<S20>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold_a
   * Referenced by: '<S24>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S6>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_k
   * Referenced by: '<S6>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Zero_Value_o
   * Referenced by: '<S24>/Zero'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_e
   * Referenced by: '<S10>/Constant'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_g
   * Referenced by: '<S10>/Constant1'
   */
  6.28318548F,

  /* Computed Parameter: Switch1_Threshold
   * Referenced by: '<S10>/Switch1'
   */
  6.28318548F,

  /* Computed Parameter: Switch2_Threshold
   * Referenced by: '<S10>/Switch2'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_a
   * Referenced by: '<S27>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_e
   * Referenced by: '<S27>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value_d
   * Referenced by: '<S30>/Constant2'
   */
  1.0F,

  /* Computed Parameter: U_DC2_Gain
   * Referenced by: '<S30>/U_DC//2'
   */
  0.5F,

  /* Computed Parameter: Constant2_Value_g
   * Referenced by: '<S31>/Constant2'
   */
  1.0F,

  /* Computed Parameter: U_DC2_Gain_p
   * Referenced by: '<S31>/U_DC//2'
   */
  0.5F,

  /* Computed Parameter: Factor_Gain
   * Referenced by: '<S32>/Factor'
   */
  0.5F,

  /* Computed Parameter: Factor1_Gain
   * Referenced by: '<S32>/Factor1'
   */
  0.5F,

  /* Computed Parameter: Constant_Value_d
   * Referenced by: '<S33>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Null_Value
   * Referenced by: '<S1>/Null'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: DiscreteTransferFcn_NumCoef
   * Referenced by: '<S7>/Discrete Transfer Fcn'
   */
  0.005F,

  /* Computed Parameter: DiscreteTransferFcn_DenCoef
   * Referenced by: '<S7>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.995F },

  /* Computed Parameter: DiscreteTransferFcn_InitialStat
   * Referenced by: '<S7>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: f_2_w_el_Gain
   * Referenced by: '<S7>/f_2_w_el'
   */
  6.28318548F,

  /* Computed Parameter: FOC_T_fast_Value
   * Referenced by: '<S27>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition
   * Referenced by: '<S27>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain
   * Referenced by: '<S17>/TrafoMatrix uvw->alphabeta'
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
   * Referenced by: '<S11>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S11>/Constant3'
   */
  -3.14159274F,

  /* Computed Parameter: Constant1_Value_ep
   * Referenced by: '<S11>/Constant1'
   */
  3.14159274F,

  /* Computed Parameter: UnitDelay3_InitialCondition
   * Referenced by: '<S9>/Unit Delay3'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_d
   * Referenced by: '<S6>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition_p
   * Referenced by: '<S6>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: IntegDelay1_InitialCondition
   * Referenced by: '<S20>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_n
   * Referenced by: '<S20>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_p
   * Referenced by: '<S18>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: IntegDelay1_InitialCondition_m
   * Referenced by: '<S24>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_e
   * Referenced by: '<S24>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: FOC_T_fast_Value_m
   * Referenced by: '<S4>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Switch1_Threshold_a
   * Referenced by: '<S14>/Switch1'
   */
  6.28318548F,

  /* Computed Parameter: Switch2_Threshold_o
   * Referenced by: '<S14>/Switch2'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_h
   * Referenced by: '<S35>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S35>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S34>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Gain1_Gain_c
   * Referenced by: '<S36>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain_l
   * Referenced by: '<S36>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: FOC_T_fast_Value_df
   * Referenced by: '<S9>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Gain_Gain_k
   * Referenced by: '<S9>/Gain'
   */
  2.0F,

  /* Computed Parameter: UnitDelay1_InitialCondition
   * Referenced by: '<S13>/Unit Delay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_c
   * Referenced by: '<S12>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: FOC_T_fast_Value_k
   * Referenced by: '<S13>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Zero1_Value
   * Referenced by: '<S20>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: Zero1_Value_l
   * Referenced by: '<S24>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_Init
   * Referenced by: '<S17>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Coef
   * Referenced by: '<S17>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_In_k
   * Referenced by: '<S18>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Co_a
   * Referenced by: '<S18>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<S6>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Switch_Threshold_c
   * Referenced by: '<S27>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Scale02_Bias_n
   * Referenced by: '<S29>/Scale [0..2]'
   */
  1.0F,

  /* Computed Parameter: Scale01_Gain_p
   * Referenced by: '<S29>/Scale  [0..1]'
   */
  0.5F,

  /* Computed Parameter: Limit01_UpperSat_d
   * Referenced by: '<S29>/Limit [0..1]'
   */
  1.0F,

  /* Computed Parameter: Limit01_LowerSat_f
   * Referenced by: '<S29>/Limit [0..1]'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain_j
   * Referenced by: '<S8>/Gain'
   */
  1.0F,

  /* Computed Parameter: Gain1_Gain_e
   * Referenced by: '<S8>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S8>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S8>/Gain3'
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
