/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF_data.c
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.38
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Feb 10 16:30:06 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_FCF.h"

/* Block parameters (default storage) */
P_FOC_FCF_T FOC_FCF_P = {
  /* Variable: ENABLE_GateDriver_FLT_Error
   * Referenced by: '<S7>/ENABLE_GateDriver_FLT_Error'
   */
  1.0F,

  /* Variable: ENABLE_GateDriver_RDY_Error
   * Referenced by: '<S7>/ENABLE_GateDriver_RDY_Error'
   */
  0.0F,

  /* Variable: FOC_9ph_AngleShift
   * Referenced by:
   *   '<S4>/FOC_9ph_AngleShift'
   *   '<S5>/FOC_9ph_AngleShift'
   *   '<S13>/FOC_9ph_AngleShift'
   */
  0.0F,

  /* Variable: FOC_ASC_Mode
   * Referenced by: '<S2>/FOC_AKS_Mode'
   */
  1.0F,

  /* Variable: FOC_AngleObs_w_InitVal
   * Referenced by: '<S18>/Unit Delay1'
   */
  0.0F,

  /* Variable: FOC_AngleObserver_D
   * Referenced by: '<S15>/Constant1'
   */
  1.0F,

  /* Variable: FOC_AngleObserver_w0
   * Referenced by: '<S15>/Constant'
   */
  200.0F,

  /* Variable: FOC_ENABLE_Overcurrent_I_uvw
   * Referenced by: '<S48>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  1.0F,

  /* Variable: FOC_ENABLE_Overspeed
   * Referenced by: '<S11>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  1.0F,

  /* Variable: FOC_ENABLE_Overvoltage_U_DC
   * Referenced by: '<S49>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  1.0F,

  /* Variable: FOC_ENABLE_Undervoltage_U_DC
   * Referenced by: '<S49>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  0.0F,

  /* Variable: FOC_Enable
   * Referenced by: '<S1>/Enable'
   */
  1.0F,

  /* Variable: FOC_If_f_el
   * Referenced by: '<S9>/If_f_el'
   */
  0.0F,

  /* Variable: FOC_IntegDamp
   * Referenced by:
   *   '<S28>/FOC_IntegDamp'
   *   '<S32>/FOC_IntegDamp'
   *   '<S36>/FOC_IntegDamp'
   */
  0.995F,

  /* Variable: FOC_KI
   * Referenced by:
   *   '<S28>/FOC_KI'
   *   '<S32>/FOC_KI'
   *   '<S36>/FOC_KI'
   */
  100.0F,

  /* Variable: FOC_KP
   * Referenced by:
   *   '<S28>/FOC_KP1'
   *   '<S32>/FOC_KP1'
   *   '<S36>/FOC_KP1'
   */
  1.0F,

  /* Variable: FOC_LIMIT_Overcurrent_I_uvw
   * Referenced by:
   *   '<S50>/Constant'
   *   '<S51>/Constant'
   */
  10.0F,

  /* Variable: FOC_LIMIT_Overvoltage_U_DC
   * Referenced by: '<S66>/Constant'
   */
  900.0F,

  /* Variable: FOC_LIMIT_Undervoltage_U_DC
   * Referenced by: '<S65>/Constant'
   */
  50.0F,

  /* Variable: FOC_MANUAL_Error
   * Referenced by: '<S1>/FOC_MANUAL_Error'
   */
  0.0F,

  /* Variable: FOC_MANUAL_U_DC
   * Referenced by: '<S1>/Udc1'
   */
  0.0F,

  /* Variable: FOC_MaxModInd
   * Referenced by:
   *   '<S27>/FOC_MaxModInd'
   *   '<S31>/FOC_MaxModInd'
   *   '<S35>/FOC_MaxModInd'
   */
  1.1F,

  /* Variable: FOC_Mode_Intern
   * Referenced by: '<S1>/FOC_Mode_Intern'
   */
  3.0F,

  /* Variable: FOC_OmegaObs3
   * Referenced by: '<S15>/Gain4'
   */
  0.0F,

  /* Variable: FOC_PhiSensorTdead
   * Referenced by: '<S15>/DeadTimeCompensation'
   */
  0.0F,

  /* Variable: FOC_RESET_OC_Error
   * Referenced by: '<S48>/Reset_OC_Error'
   */
  0.0F,

  /* Variable: FOC_RESET_OS_Error
   * Referenced by: '<S11>/Reset_OS_Error'
   */
  0.0F,

  /* Variable: FOC_RESET_OV_Error
   * Referenced by: '<S49>/Reset_OV_Error'
   */
  0.0F,

  /* Variable: FOC_RESET_UV_Error
   * Referenced by: '<S49>/Reset_UV_Error'
   */
  0.0F,

  /* Variable: FOC_SELECT_Voltage_Assignment_UVW
   * Referenced by: '<S82>/Constant6'
   */
  1.0F,

  /* Variable: FOC_Uf_U_max
   * Referenced by: '<S78>/Saturation1'
   */
  0.0F,

  /* Variable: FOC_Uf_U_min
   * Referenced by: '<S78>/Saturation1'
   */
  0.0F,

  /* Variable: FOC_Uf_Ud
   * Referenced by: '<S13>/Uf_Ud'
   */
  0.0F,

  /* Variable: FOC_Uf_f_el
   * Referenced by: '<S13>/Uf_w_el'
   */
  0.0F,

  /* Variable: FOC_Uf_m
   * Referenced by: '<S78>/Gain'
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

  /* Variable: LIMIT_MAX_Overspeed
   * Referenced by: '<S73>/Constant'
   */
  8000.0F,

  /* Variable: enumState_FOC_IF
   * Referenced by: '<S6>/Constant'
   */
  33.0F,

  /* Variable: FOC_SELECT_Mode_Intern
   * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
   */
  0U,

  /* Variable: FOC_SELECT_Modulation
   * Referenced by: '<S14>/Enable_SuperSinMod'
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
   * Referenced by: '<S29>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const
   * Referenced by: '<S30>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_d_const_n
   * Referenced by: '<S33>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const_h
   * Referenced by: '<S34>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_d_const_f
   * Referenced by: '<S37>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const_l
   * Referenced by: '<S38>/Constant'
   */
  0.0F,

  /* Mask Parameter: Mask_6Bits_Inv1_FLT_BitMask
   * Referenced by: '<S8>/Mask_6Bits_Inv1_FLT'
   */
  63U,

  /* Mask Parameter: MaskBit0_BitMask
   * Referenced by: '<S41>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask
   * Referenced by: '<S41>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask
   * Referenced by: '<S41>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask
   * Referenced by: '<S41>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask
   * Referenced by: '<S41>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask
   * Referenced by: '<S41>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv1_RDY_BitMask
   * Referenced by: '<S8>/Mask_6Bits_Inv1_RDY'
   */
  63U,

  /* Mask Parameter: MaskBit0_BitMask_b
   * Referenced by: '<S42>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_j
   * Referenced by: '<S42>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_m
   * Referenced by: '<S42>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_i
   * Referenced by: '<S42>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_d
   * Referenced by: '<S42>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_a
   * Referenced by: '<S42>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv2_FLT_BitMask
   * Referenced by: '<S8>/Mask_6Bits_Inv2_FLT'
   */
  4032U,

  /* Mask Parameter: MaskBit0_BitMask_g
   * Referenced by: '<S43>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_n
   * Referenced by: '<S43>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_n
   * Referenced by: '<S43>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_c
   * Referenced by: '<S43>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_o
   * Referenced by: '<S43>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_h
   * Referenced by: '<S43>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv2_RDY_BitMask
   * Referenced by: '<S8>/Mask_6Bits_Inv2_RDY'
   */
  4032U,

  /* Mask Parameter: MaskBit0_BitMask_bn
   * Referenced by: '<S44>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_a
   * Referenced by: '<S44>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_o
   * Referenced by: '<S44>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_h
   * Referenced by: '<S44>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_e
   * Referenced by: '<S44>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_l
   * Referenced by: '<S44>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv3_FLT_BitMask
   * Referenced by: '<S8>/Mask_6Bits_Inv3_FLT'
   */
  258048U,

  /* Mask Parameter: MaskBit0_BitMask_m
   * Referenced by: '<S45>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_d
   * Referenced by: '<S45>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_b
   * Referenced by: '<S45>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_l
   * Referenced by: '<S45>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_b
   * Referenced by: '<S45>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_e
   * Referenced by: '<S45>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv3_RDY_BitMask
   * Referenced by: '<S8>/Mask_6Bits_Inv3_RDY'
   */
  258048U,

  /* Mask Parameter: MaskBit0_BitMask_l
   * Referenced by: '<S46>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_dr
   * Referenced by: '<S46>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_bx
   * Referenced by: '<S46>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_it
   * Referenced by: '<S46>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_a
   * Referenced by: '<S46>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_b
   * Referenced by: '<S46>/MaskBit5'
   */
  32U,

  /* Mask Parameter: SRFlipFlop_initial_condition
   * Referenced by: '<S69>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop1_initial_condition
   * Referenced by: '<S70>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop_initial_condition_d
   * Referenced by: '<S54>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop_initial_condition_k
   * Referenced by: '<S75>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_1_initial_con
   * Referenced by: '<S56>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_2_initial_con
   * Referenced by: '<S57>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_3_initial_con
   * Referenced by: '<S58>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_4_initial_con
   * Referenced by: '<S59>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_5_initial_con
   * Referenced by: '<S60>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_6_initial_con
   * Referenced by: '<S61>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_7_initial_con
   * Referenced by: '<S62>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_8_initial_con
   * Referenced by: '<S63>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_9_initial_con
   * Referenced by: '<S64>/Memory'
   */
  false,

  /* Mask Parameter: DetectRisePositive1_vinit
   * Referenced by: '<S68>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit
   * Referenced by: '<S67>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit_g
   * Referenced by: '<S52>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit_f
   * Referenced by: '<S74>/Delay Input1'
   */
  false,

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
   * Referenced by: '<S17>/Constant5'
   */
  -6.28318548F,

  /* Computed Parameter: Constant6_Value
   * Referenced by: '<S17>/Constant6'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S17>/Constant2'
   */
  6.28318548F,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S17>/Constant4'
   */
  0.0F,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S20>/Constant'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<S20>/Constant1'
   */
  6.28318548F,

  /* Computed Parameter: Zero_Value
   * Referenced by: '<S28>/Zero'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold
   * Referenced by: '<S28>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: Zero_Value_o
   * Referenced by: '<S32>/Zero'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold_a
   * Referenced by: '<S32>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: Zero_Value_n
   * Referenced by: '<S36>/Zero'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold_ad
   * Referenced by: '<S36>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S47>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_c
   * Referenced by: '<S47>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S49>/Constant3'
   */
  0.0F,

  /* Computed Parameter: Constant1_Value_b
   * Referenced by: '<S49>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_c
   * Referenced by: '<S12>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_k
   * Referenced by: '<S12>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant1_Value_bt
   * Referenced by: '<S1>/Constant1'
   */
  1.0F,

  /* Computed Parameter: Constant_Value_e
   * Referenced by: '<S16>/Constant'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_g
   * Referenced by: '<S16>/Constant1'
   */
  6.28318548F,

  /* Computed Parameter: Switch1_Threshold
   * Referenced by: '<S16>/Switch1'
   */
  6.28318548F,

  /* Computed Parameter: Switch2_Threshold
   * Referenced by: '<S16>/Switch2'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_a
   * Referenced by: '<S77>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_e
   * Referenced by: '<S77>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value_d
   * Referenced by: '<S80>/Constant2'
   */
  1.0F,

  /* Computed Parameter: U_DC2_Gain
   * Referenced by: '<S80>/U_DC//2'
   */
  0.5F,

  /* Computed Parameter: Constant2_Value_g
   * Referenced by: '<S81>/Constant2'
   */
  1.0F,

  /* Computed Parameter: U_DC2_Gain_p
   * Referenced by: '<S81>/U_DC//2'
   */
  0.5F,

  /* Computed Parameter: Factor_Gain
   * Referenced by: '<S83>/Factor'
   */
  0.5F,

  /* Computed Parameter: Factor1_Gain
   * Referenced by: '<S83>/Factor1'
   */
  0.5F,

  /* Computed Parameter: Factor2_Gain
   * Referenced by: '<S83>/Factor2'
   */
  0.5F,

  /* Computed Parameter: Constant_Value_d
   * Referenced by: '<S84>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Null_Value
   * Referenced by: '<S1>/Null'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: DiscreteTransferFcn_NumCoef
   * Referenced by: '<S13>/Discrete Transfer Fcn'
   */
  0.005F,

  /* Computed Parameter: DiscreteTransferFcn_DenCoef
   * Referenced by: '<S13>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.995F },

  /* Computed Parameter: DiscreteTransferFcn_InitialStat
   * Referenced by: '<S13>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: f_2_w_el_Gain
   * Referenced by: '<S13>/f_2_w_el'
   */
  6.28318548F,

  /* Computed Parameter: FOC_T_fast_Value
   * Referenced by: '<S77>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition
   * Referenced by: '<S77>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain
   * Referenced by: '<S24>/TrafoMatrix uvw->alphabeta'
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
   * Referenced by: '<S17>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value_l
   * Referenced by: '<S17>/Constant3'
   */
  -3.14159274F,

  /* Computed Parameter: Constant1_Value_ep
   * Referenced by: '<S17>/Constant1'
   */
  3.14159274F,

  /* Computed Parameter: UnitDelay3_InitialCondition
   * Referenced by: '<S15>/Unit Delay3'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_d
   * Referenced by: '<S12>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition_p
   * Referenced by: '<S12>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: f_2_w_el_Gain_j
   * Referenced by: '<S9>/f_2_w_el'
   */
  6.28318548F,

  /* Computed Parameter: FOC_T_fast_Value_f
   * Referenced by: '<S47>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition_d
   * Referenced by: '<S47>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: IntegDelay1_InitialCondition
   * Referenced by: '<S28>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_n
   * Referenced by: '<S28>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_p
   * Referenced by: '<S25>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: IntegDelay1_InitialCondition_m
   * Referenced by: '<S32>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_e
   * Referenced by: '<S32>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_j
   * Referenced by: '<S26>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: IntegDelay1_InitialCondition_p
   * Referenced by: '<S36>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_er
   * Referenced by: '<S36>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: FOC_T_fast_Value_m
   * Referenced by: '<S4>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Switch1_Threshold_a
   * Referenced by: '<S20>/Switch1'
   */
  6.28318548F,

  /* Computed Parameter: Switch2_Threshold_o
   * Referenced by: '<S20>/Switch2'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_h
   * Referenced by: '<S87>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S87>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S85>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Gain1_Gain_ck
   * Referenced by: '<S88>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain_l
   * Referenced by: '<S88>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant_Value_o
   * Referenced by: '<S86>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Gain1_Gain_k
   * Referenced by: '<S89>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain_j
   * Referenced by: '<S89>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Scale02_Bias
   * Referenced by: '<S79>/Scale [0..2]'
   */
  1.0F,

  /* Computed Parameter: Scale01_Gain
   * Referenced by: '<S79>/Scale  [0..1]'
   */
  0.5F,

  /* Computed Parameter: Limit01_UpperSat
   * Referenced by: '<S79>/Limit [0..1]'
   */
  1.0F,

  /* Computed Parameter: Limit01_LowerSat
   * Referenced by: '<S79>/Limit [0..1]'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_df
   * Referenced by: '<S15>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Gain_Gain_k
   * Referenced by: '<S15>/Gain'
   */
  2.0F,

  /* Computed Parameter: UnitDelay1_InitialCondition
   * Referenced by: '<S19>/Unit Delay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_c
   * Referenced by: '<S18>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: FOC_T_fast_Value_k
   * Referenced by: '<S19>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Gain1_Gain_kl
   * Referenced by: '<S4>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Zero1_Value
   * Referenced by: '<S28>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: Gain1_Gain_cs
   * Referenced by: '<S21>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S21>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Zero1_Value_l
   * Referenced by: '<S32>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: Zero1_Value_o
   * Referenced by: '<S36>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_Init
   * Referenced by: '<S24>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Coef
   * Referenced by: '<S24>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_In_k
   * Referenced by: '<S25>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Co_a
   * Referenced by: '<S25>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_In_n
   * Referenced by: '<S26>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Co_l
   * Referenced by: '<S26>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: NO_ERROR_Value
   * Referenced by: '<S7>/NO_ERROR'
   */
  0.0F,

  /* Computed Parameter: usrpm_Gain
   * Referenced by: '<S11>/[1//s] => [rpm]'
   */
  2.38732409F,

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<S47>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Switch_Threshold_b
   * Referenced by: '<S12>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Switch_Threshold_c
   * Referenced by: '<S77>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Gain_Gain_jm
   * Referenced by: '<S14>/Gain'
   */
  1.0F,

  /* Computed Parameter: Gain1_Gain_e
   * Referenced by: '<S14>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain_f
   * Referenced by: '<S14>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S14>/Gain3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u1_Gain
   * Referenced by: '<S82>/DutyCycle_u1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u2_Gain
   * Referenced by: '<S82>/DutyCycle_u2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u3_Gain
   * Referenced by: '<S82>/DutyCycle_u3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v1_Gain
   * Referenced by: '<S82>/DutyCycle_v1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v2_Gain
   * Referenced by: '<S82>/DutyCycle_v2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v3_Gain
   * Referenced by: '<S82>/DutyCycle_v3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w1_Gain
   * Referenced by: '<S82>/DutyCycle_w1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w2_Gain
   * Referenced by: '<S82>/DutyCycle_w2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w3_Gain
   * Referenced by: '<S82>/DutyCycle_w3'
   */
  1.0F,

  /* Computed Parameter: Counter_Start_Value
   * Referenced by: '<S1>/Counter_Start'
   */
  1.0F,

  /* Computed Parameter: FCF_Cnt_InitialCondition
   * Referenced by: '<S1>/FCF_Cnt'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_d2
   * Referenced by: '<S39>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_a
   * Referenced by: '<S40>/Constant'
   */
  0U,

  /* Computed Parameter: NoError_Manual_Value
   * Referenced by: '<S7>/NoError_Manual'
   */
  false,

  /* Computed Parameter: Constant2_Value_f
   * Referenced by: '<S48>/Constant2'
   */
  false,

  /* Computed Parameter: Constant1_Value_d
   * Referenced by: '<S48>/Constant1'
   */
  true,

  /* Computed Parameter: Constant2_Value_c
   * Referenced by: '<S49>/Constant2'
   */
  true,

  /* Computed Parameter: Constant4_Value_f
   * Referenced by: '<S49>/Constant4'
   */
  true,

  /* Computed Parameter: Constant2_Value_gw
   * Referenced by: '<S11>/Constant2'
   */
  false,

  /* Computed Parameter: Constant1_Value_n
   * Referenced by: '<S11>/Constant1'
   */
  true,

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S55>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_dc
   * Referenced by: '<S71>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_eo
   * Referenced by: '<S72>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_ep
   * Referenced by: '<S76>/Constant'
   */
  false,

  /* Computed Parameter: Logic_table
   * Referenced by: '<S69>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_l
   * Referenced by: '<S70>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_o
   * Referenced by: '<S54>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: SELECT_DataSource_Value
   * Referenced by: '<S7>/SELECT_DataSource'
   */
  true,

  /* Computed Parameter: Logic_table_lc
   * Referenced by: '<S75>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_l5
   * Referenced by: '<S56>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_p
   * Referenced by: '<S57>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_j
   * Referenced by: '<S58>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_o1
   * Referenced by: '<S59>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_i
   * Referenced by: '<S60>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_c
   * Referenced by: '<S61>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_ij
   * Referenced by: '<S62>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_pd
   * Referenced by: '<S63>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_a
   * Referenced by: '<S64>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
