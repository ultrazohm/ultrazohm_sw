/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_FCF_data.c
 *
 * Code generated for Simulink model 'FOC_FCF'.
 *
 * Model version                  : 5.72
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Feb 19 21:00:25 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_FCF.h"

/* Block parameters (default storage) */
P_FOC_FCF_T FOC_FCF_P = {
  /* Variable: ENABLE_GateDriver_FLT_Error_Sys1
   * Referenced by: '<S42>/ENABLE_GateDriver_FLT_Error_Sys1'
   */
  1.0F,

  /* Variable: ENABLE_GateDriver_FLT_Error_Sys2
   * Referenced by: '<S42>/ENABLE_GateDriver_FLT_Error_Sys2'
   */
  1.0F,

  /* Variable: ENABLE_GateDriver_FLT_Error_Sys3
   * Referenced by: '<S42>/ENABLE_GateDriver_FLT_Error_Sys3'
   */
  1.0F,

  /* Variable: ENABLE_GateDriver_RDY_Error_Sys1
   * Referenced by: '<S42>/ENABLE_GateDriver_RDY_Error_Sys1'
   */
  0.0F,

  /* Variable: ENABLE_GateDriver_RDY_Error_Sys2
   * Referenced by: '<S42>/ENABLE_GateDriver_RDY_Error_Sys2'
   */
  0.0F,

  /* Variable: ENABLE_GateDriver_RDY_Error_Sys3
   * Referenced by: '<S42>/ENABLE_GateDriver_RDY_Error_Sys3'
   */
  0.0F,

  /* Variable: FOC_9ph_AngleShift
   * Referenced by:
   *   '<S5>/FOC_9ph_AngleShift'
   *   '<S6>/FOC_9ph_AngleShift'
   *   '<S14>/FOC_9ph_AngleShift'
   */
  0.0F,

  /* Variable: FOC_ASC_Mode
   * Referenced by: '<S3>/FOC_AKS_Mode'
   */
  1.0F,

  /* Variable: FOC_AngleObs_w_InitVal
   * Referenced by: '<S21>/Unit Delay1'
   */
  0.0F,

  /* Variable: FOC_AngleObserver_D
   * Referenced by: '<S18>/Constant1'
   */
  1.0F,

  /* Variable: FOC_AngleObserver_w0
   * Referenced by: '<S18>/Constant'
   */
  200.0F,

  /* Variable: FOC_ENABLE_Overcurrent_I_uvw
   * Referenced by: '<S56>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  1.0F,

  /* Variable: FOC_ENABLE_Overspeed
   * Referenced by: '<S12>/FOC_ENABLE_Overcurrent_I_uvw1'
   */
  1.0F,

  /* Variable: FOC_ENABLE_Overvoltage_U_DC
   * Referenced by: '<S57>/FOC_ENABLE_Overvoltage_U_DC1'
   */
  1.0F,

  /* Variable: FOC_ENABLE_Undervoltage_U_DC
   * Referenced by: '<S57>/FOC_ENABLE_Undervoltage_U_DC1'
   */
  0.0F,

  /* Variable: FOC_Enable
   * Referenced by: '<S1>/Enable'
   */
  1.0F,

  /* Variable: FOC_Enable_Sys1
   * Referenced by: '<S6>/FOC_Enable_Sys1'
   */
  1.0F,

  /* Variable: FOC_Enable_Sys2
   * Referenced by: '<S6>/FOC_Enable_Sys2'
   */
  0.0F,

  /* Variable: FOC_Enable_Sys3
   * Referenced by: '<S6>/FOC_Enable_Sys3'
   */
  0.0F,

  /* Variable: FOC_If_f_el
   * Referenced by: '<S10>/If_f_el'
   */
  0.0F,

  /* Variable: FOC_IntegDamp
   * Referenced by:
   *   '<S31>/FOC_IntegDamp'
   *   '<S35>/FOC_IntegDamp'
   *   '<S39>/FOC_IntegDamp'
   */
  0.995F,

  /* Variable: FOC_KI
   * Referenced by:
   *   '<S31>/FOC_KI'
   *   '<S35>/FOC_KI'
   *   '<S39>/FOC_KI'
   */
  100.0F,

  /* Variable: FOC_KP
   * Referenced by:
   *   '<S31>/FOC_KP1'
   *   '<S35>/FOC_KP1'
   *   '<S39>/FOC_KP1'
   */
  1.0F,

  /* Variable: FOC_LIMIT_Overcurrent_I_uvw
   * Referenced by:
   *   '<S58>/Constant'
   *   '<S59>/Constant'
   */
  10.0F,

  /* Variable: FOC_LIMIT_Overvoltage_U_DC
   * Referenced by: '<S74>/Constant'
   */
  900.0F,

  /* Variable: FOC_LIMIT_Undervoltage_U_DC
   * Referenced by: '<S73>/Constant'
   */
  50.0F,

  /* Variable: FOC_MANUAL_Error
   * Referenced by: '<S1>/FOC_MANUAL_Error'
   */
  0.0F,

  /* Variable: FOC_MANUAL_U_DC
   * Referenced by: '<S17>/Udc1'
   */
  0.0F,

  /* Variable: FOC_MaxModInd
   * Referenced by:
   *   '<S30>/FOC_MaxModInd'
   *   '<S34>/FOC_MaxModInd'
   *   '<S38>/FOC_MaxModInd'
   */
  1.1F,

  /* Variable: FOC_Mode_Intern
   * Referenced by: '<S1>/FOC_Mode_Intern'
   */
  3.0F,

  /* Variable: FOC_OmegaObs3
   * Referenced by: '<S18>/Gain4'
   */
  0.0F,

  /* Variable: FOC_PhiSensorTdead
   * Referenced by: '<S18>/DeadTimeCompensation'
   */
  0.0F,

  /* Variable: FOC_RESET_OC_Error
   * Referenced by: '<S56>/Reset_OC_Error'
   */
  0.0F,

  /* Variable: FOC_RESET_OS_Error
   * Referenced by: '<S12>/Reset_OS_Error'
   */
  0.0F,

  /* Variable: FOC_RESET_OV_Error
   * Referenced by: '<S57>/Reset_OV_Error'
   */
  0.0F,

  /* Variable: FOC_RESET_UV_Error
   * Referenced by: '<S57>/Reset_UV_Error'
   */
  0.0F,

  /* Variable: FOC_SELECT_Voltage_Assignment_UVW
   * Referenced by: '<S90>/Constant6'
   */
  1.0F,

  /* Variable: FOC_Uf_U_max
   * Referenced by: '<S86>/Saturation1'
   */
  0.0F,

  /* Variable: FOC_Uf_U_min
   * Referenced by: '<S86>/Saturation1'
   */
  0.0F,

  /* Variable: FOC_Uf_Ud
   * Referenced by: '<S14>/Uf_Ud'
   */
  0.0F,

  /* Variable: FOC_Uf_f_el
   * Referenced by: '<S14>/Uf_w_el'
   */
  0.0F,

  /* Variable: FOC_Uf_m
   * Referenced by: '<S86>/Gain'
   */
  0.0F,

  /* Variable: FOC_output_trafo_delay
   * Referenced by: '<S5>/FOC_output_trafo_delay'
   */
  1.5F,

  /* Variable: FOC_phi_offset
   * Referenced by: '<S4>/Constant'
   */
  1.794F,

  /* Variable: LIMIT_MAX_Overspeed
   * Referenced by: '<S81>/Constant'
   */
  8000.0F,

  /* Variable: enumState_FOC_IF
   * Referenced by: '<S7>/Constant'
   */
  33.0F,

  /* Variable: FOC_SELECT_MANUAL_DutyCycles
   * Referenced by: '<S3>/FOC_SELECT_MANUAL_DutyCycles'
   */
  0U,

  /* Variable: FOC_SELECT_Mode_Intern
   * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
   */
  0U,

  /* Variable: FOC_SELECT_Modulation
   * Referenced by: '<S15>/Enable_SuperSinMod'
   */
  1U,

  /* Variable: FOC_SELECT_U_DC_INPUT
   * Referenced by: '<S17>/0: P_Udc 1: Udc_measured'
   */
  1U,

  /* Variable: FOC_SELECT_phi
   * Referenced by: '<S4>/Constant3'
   */
  2U,

  /* Mask Parameter: AntiWindupGT_d_const
   * Referenced by: '<S32>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const
   * Referenced by: '<S33>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_d_const_n
   * Referenced by: '<S36>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const_h
   * Referenced by: '<S37>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_d_const_f
   * Referenced by: '<S40>/Constant'
   */
  0.0F,

  /* Mask Parameter: AntiWindupGT_q_const_l
   * Referenced by: '<S41>/Constant'
   */
  0.0F,

  /* Mask Parameter: Mask_6Bits_Inv1_FLT_BitMask
   * Referenced by: '<S9>/Mask_6Bits_Inv1_FLT'
   */
  63U,

  /* Mask Parameter: MaskBit0_BitMask
   * Referenced by: '<S43>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask
   * Referenced by: '<S43>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask
   * Referenced by: '<S43>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask
   * Referenced by: '<S43>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask
   * Referenced by: '<S43>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask
   * Referenced by: '<S43>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv1_RDY_BitMask
   * Referenced by: '<S9>/Mask_6Bits_Inv1_RDY'
   */
  63U,

  /* Mask Parameter: MaskBit0_BitMask_b
   * Referenced by: '<S44>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_j
   * Referenced by: '<S44>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_m
   * Referenced by: '<S44>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_i
   * Referenced by: '<S44>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_d
   * Referenced by: '<S44>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_a
   * Referenced by: '<S44>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv2_FLT_BitMask
   * Referenced by: '<S9>/Mask_6Bits_Inv2_FLT'
   */
  4032U,

  /* Mask Parameter: MaskBit0_BitMask_g
   * Referenced by: '<S45>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_n
   * Referenced by: '<S45>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_n
   * Referenced by: '<S45>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_c
   * Referenced by: '<S45>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_o
   * Referenced by: '<S45>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_h
   * Referenced by: '<S45>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv2_RDY_BitMask
   * Referenced by: '<S9>/Mask_6Bits_Inv2_RDY'
   */
  4032U,

  /* Mask Parameter: MaskBit0_BitMask_bn
   * Referenced by: '<S46>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_a
   * Referenced by: '<S46>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_o
   * Referenced by: '<S46>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_h
   * Referenced by: '<S46>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_e
   * Referenced by: '<S46>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_l
   * Referenced by: '<S46>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv3_FLT_BitMask
   * Referenced by: '<S9>/Mask_6Bits_Inv3_FLT'
   */
  258048U,

  /* Mask Parameter: MaskBit0_BitMask_m
   * Referenced by: '<S47>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_d
   * Referenced by: '<S47>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_b
   * Referenced by: '<S47>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_l
   * Referenced by: '<S47>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_b
   * Referenced by: '<S47>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_e
   * Referenced by: '<S47>/MaskBit5'
   */
  32U,

  /* Mask Parameter: Mask_6Bits_Inv3_RDY_BitMask
   * Referenced by: '<S9>/Mask_6Bits_Inv3_RDY'
   */
  258048U,

  /* Mask Parameter: MaskBit0_BitMask_l
   * Referenced by: '<S48>/MaskBit0'
   */
  1U,

  /* Mask Parameter: MaskBit1_BitMask_dr
   * Referenced by: '<S48>/MaskBit1'
   */
  2U,

  /* Mask Parameter: MaskBit2_BitMask_bx
   * Referenced by: '<S48>/MaskBit2'
   */
  4U,

  /* Mask Parameter: MaskBit3_BitMask_it
   * Referenced by: '<S48>/MaskBit3'
   */
  8U,

  /* Mask Parameter: MaskBit4_BitMask_a
   * Referenced by: '<S48>/MaskBit4'
   */
  16U,

  /* Mask Parameter: MaskBit5_BitMask_b
   * Referenced by: '<S48>/MaskBit5'
   */
  32U,

  /* Mask Parameter: CompareToConstant_const
   * Referenced by: '<S50>/Constant'
   */
  63U,

  /* Mask Parameter: CompareToConstant_const_n
   * Referenced by: '<S52>/Constant'
   */
  63U,

  /* Mask Parameter: CompareToConstant_const_h
   * Referenced by: '<S54>/Constant'
   */
  63U,

  /* Mask Parameter: SRFlipFlop_initial_condition
   * Referenced by: '<S77>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop1_initial_condition
   * Referenced by: '<S78>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop_initial_condition_d
   * Referenced by: '<S62>/Memory'
   */
  false,

  /* Mask Parameter: SRFlipFlop_initial_condition_k
   * Referenced by: '<S83>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_1_initial_con
   * Referenced by: '<S64>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_2_initial_con
   * Referenced by: '<S65>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_3_initial_con
   * Referenced by: '<S66>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_4_initial_con
   * Referenced by: '<S67>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_5_initial_con
   * Referenced by: '<S68>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_6_initial_con
   * Referenced by: '<S69>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_7_initial_con
   * Referenced by: '<S70>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_8_initial_con
   * Referenced by: '<S71>/Memory'
   */
  false,

  /* Mask Parameter: OverTemp_Latching_9_initial_con
   * Referenced by: '<S72>/Memory'
   */
  false,

  /* Mask Parameter: DetectRisePositive1_vinit
   * Referenced by: '<S76>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit
   * Referenced by: '<S75>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit_g
   * Referenced by: '<S60>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit_f
   * Referenced by: '<S82>/Delay Input1'
   */
  false,

  /* Expression: MM_U_DC.OFFSET
   * Referenced by: '<S17>/bias_udc'
   */
  55.0F,

  /* Expression: MM_U_DC.FACTOR
   * Referenced by: '<S17>/gain_udc'
   */
  0.0972762629F,

  /* Computed Parameter: ASC_LS_Value
   * Referenced by: '<S3>/ASC_LS'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: ASC_HS_Value
   * Referenced by: '<S3>/ASC_HS'
   */
  { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F },

  /* Computed Parameter: ASC_LSHS_Value
   * Referenced by: '<S3>/ASC_LSHS'
   */
  { 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F },

  /* Computed Parameter: FOC_Manual_DutyCycles_Value
   * Referenced by: '<S3>/FOC_Manual_DutyCycles'
   */
  { 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F, 0.5F },

  /* Computed Parameter: Constant5_Value
   * Referenced by: '<S20>/Constant5'
   */
  -6.28318548F,

  /* Computed Parameter: Constant6_Value
   * Referenced by: '<S20>/Constant6'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S20>/Constant2'
   */
  6.28318548F,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S20>/Constant4'
   */
  0.0F,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S23>/Constant'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<S23>/Constant1'
   */
  6.28318548F,

  /* Computed Parameter: Zero_Value
   * Referenced by: '<S31>/Zero'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold
   * Referenced by: '<S31>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: Zero_Value_o
   * Referenced by: '<S35>/Zero'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold_a
   * Referenced by: '<S35>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: Zero_Value_n
   * Referenced by: '<S39>/Zero'
   */
  0.0F,

  /* Computed Parameter: IntegStopSwitch3_Threshold_ad
   * Referenced by: '<S39>/IntegStopSwitch3'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S55>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_c
   * Referenced by: '<S55>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S57>/Constant3'
   */
  0.0F,

  /* Computed Parameter: Constant1_Value_b
   * Referenced by: '<S57>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_c
   * Referenced by: '<S13>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_k
   * Referenced by: '<S13>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant1_Value_bt
   * Referenced by: '<S1>/Constant1'
   */
  1.0F,

  /* Computed Parameter: Constant_Value_e
   * Referenced by: '<S19>/Constant'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_g
   * Referenced by: '<S19>/Constant1'
   */
  6.28318548F,

  /* Computed Parameter: Switch1_Threshold
   * Referenced by: '<S19>/Switch1'
   */
  6.28318548F,

  /* Computed Parameter: Switch2_Threshold
   * Referenced by: '<S19>/Switch2'
   */
  0.0F,

  /* Computed Parameter: SMF_IfStarter_Active_Value
   * Referenced by: '<S1>/SMF_IfStarter_Active'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_a
   * Referenced by: '<S85>/Gain1'
   */
  6.28318548F,

  /* Computed Parameter: Constant1_Value_e
   * Referenced by: '<S85>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant2_Value_d
   * Referenced by: '<S88>/Constant2'
   */
  1.0F,

  /* Computed Parameter: U_DC2_Gain
   * Referenced by: '<S88>/U_DC//2'
   */
  0.5F,

  /* Computed Parameter: Constant2_Value_g
   * Referenced by: '<S89>/Constant2'
   */
  1.0F,

  /* Computed Parameter: U_DC2_Gain_p
   * Referenced by: '<S89>/U_DC//2'
   */
  0.5F,

  /* Computed Parameter: Factor_Gain
   * Referenced by: '<S91>/Factor'
   */
  0.5F,

  /* Computed Parameter: Factor1_Gain
   * Referenced by: '<S91>/Factor1'
   */
  0.5F,

  /* Computed Parameter: Factor2_Gain
   * Referenced by: '<S91>/Factor2'
   */
  0.5F,

  /* Expression: MM_U_DC.OFFSET
   * Referenced by: '<S16>/bias_udc'
   */
  55.0F,

  /* Expression: MM_U_DC.FACTOR
   * Referenced by: '<S16>/gain_udc'
   */
  0.0972762629F,

  /* Computed Parameter: Constant_Value_d
   * Referenced by: '<S92>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Null_Value
   * Referenced by: '<S1>/Null'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: DiscreteTransferFcn_NumCoef
   * Referenced by: '<S14>/Discrete Transfer Fcn'
   */
  0.005F,

  /* Computed Parameter: DiscreteTransferFcn_DenCoef
   * Referenced by: '<S14>/Discrete Transfer Fcn'
   */
  { 1.0F, -0.995F },

  /* Computed Parameter: DiscreteTransferFcn_InitialStat
   * Referenced by: '<S14>/Discrete Transfer Fcn'
   */
  0.0F,

  /* Computed Parameter: f_2_w_el_Gain
   * Referenced by: '<S14>/f_2_w_el'
   */
  6.28318548F,

  /* Computed Parameter: FOC_T_fast_Value
   * Referenced by: '<S85>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition
   * Referenced by: '<S85>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain
   * Referenced by: '<S27>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: ResolverOffsetLimitation_UpperS
   * Referenced by: '<S4>/ResolverOffsetLimitation'
   */
  6.28318548F,

  /* Computed Parameter: ResolverOffsetLimitation_LowerS
   * Referenced by: '<S4>/ResolverOffsetLimitation'
   */
  0.0F,

  /* Computed Parameter: UnitDelay_InitialCondition_b
   * Referenced by: '<S20>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value_l
   * Referenced by: '<S20>/Constant3'
   */
  -3.14159274F,

  /* Computed Parameter: Constant1_Value_ep
   * Referenced by: '<S20>/Constant1'
   */
  3.14159274F,

  /* Computed Parameter: UnitDelay3_InitialCondition
   * Referenced by: '<S18>/Unit Delay3'
   */
  0.0F,

  /* Computed Parameter: SMF_w_el_Ref_IfStarter_Value
   * Referenced by: '<S1>/SMF_w_el_Ref_IfStarter'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_d
   * Referenced by: '<S13>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition_p
   * Referenced by: '<S13>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: f_2_w_el_Gain_j
   * Referenced by: '<S10>/f_2_w_el'
   */
  6.28318548F,

  /* Computed Parameter: FOC_T_fast_Value_f
   * Referenced by: '<S55>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: UnitDelay_InitialCondition_d
   * Referenced by: '<S55>/Unit Delay'
   */
  0.0F,

  /* Computed Parameter: IntegDelay1_InitialCondition
   * Referenced by: '<S31>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_n
   * Referenced by: '<S31>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_p
   * Referenced by: '<S28>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: IntegDelay1_InitialCondition_m
   * Referenced by: '<S35>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_e
   * Referenced by: '<S35>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: TrafoMatrixuvwalphabeta_Gain_j
   * Referenced by: '<S29>/TrafoMatrix uvw->alphabeta'
   */
  { 0.666666687F, 0.0F, -0.333333343F, 0.577350259F, -0.333333343F,
    -0.577350259F },

  /* Computed Parameter: IntegDelay1_InitialCondition_p
   * Referenced by: '<S39>/IntegDelay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_er
   * Referenced by: '<S39>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: FOC_T_fast_Value_m
   * Referenced by: '<S5>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Switch1_Threshold_a
   * Referenced by: '<S23>/Switch1'
   */
  6.28318548F,

  /* Computed Parameter: Switch2_Threshold_o
   * Referenced by: '<S23>/Switch2'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_h
   * Referenced by: '<S95>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S95>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S93>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Gain1_Gain_ck
   * Referenced by: '<S96>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain_l
   * Referenced by: '<S96>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant_Value_o
   * Referenced by: '<S94>/Constant'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F },

  /* Computed Parameter: Gain1_Gain_k
   * Referenced by: '<S97>/Gain1'
   */
  { 0.0F, 1.0F, -1.0F, 0.0F },

  /* Computed Parameter: Gain_Gain_j
   * Referenced by: '<S97>/Gain'
   */
  { 1.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Scale02_Bias
   * Referenced by: '<S87>/Scale [0..2]'
   */
  1.0F,

  /* Computed Parameter: Scale01_Gain
   * Referenced by: '<S87>/Scale  [0..1]'
   */
  0.5F,

  /* Computed Parameter: Limit01_UpperSat
   * Referenced by: '<S87>/Limit [0..1]'
   */
  1.0F,

  /* Computed Parameter: Limit01_LowerSat
   * Referenced by: '<S87>/Limit [0..1]'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_df
   * Referenced by: '<S18>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Gain_Gain_k
   * Referenced by: '<S18>/Gain'
   */
  2.0F,

  /* Computed Parameter: UnitDelay1_InitialCondition
   * Referenced by: '<S22>/Unit Delay1'
   */
  0.0F,

  /* Computed Parameter: FOC_T_fast_Value_c
   * Referenced by: '<S21>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: FOC_T_fast_Value_k
   * Referenced by: '<S22>/FOC_T_fast'
   */
  0.0001F,

  /* Computed Parameter: Gain1_Gain_kl
   * Referenced by: '<S5>/Gain1'
   */
  1.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Init
   * Referenced by: '<S27>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Coef
   * Referenced by: '<S27>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_In_k
   * Referenced by: '<S28>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Co_a
   * Referenced by: '<S28>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: DiscreteFIRFilter20thorder_In_n
   * Referenced by: '<S29>/Discrete FIR Filter 20th order'
   */
  0.0F,

  /* Computed Parameter: DiscreteFIRFilter20thorder_Co_l
   * Referenced by: '<S29>/Discrete FIR Filter 20th order'
   */
  { 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F,
    0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F, 0.05F },

  /* Computed Parameter: usrpm_Gain
   * Referenced by: '<S12>/[1//s] => [rpm]'
   */
  2.38732409F,

  /* Computed Parameter: NO_ERROR_Value
   * Referenced by: '<S42>/NO_ERROR'
   */
  0.0F,

  /* Computed Parameter: Zero1_Value
   * Referenced by: '<S31>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: Gain1_Gain_cs
   * Referenced by: '<S24>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S24>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Zero1_Value_l
   * Referenced by: '<S35>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: Zero1_Value_o
   * Referenced by: '<S39>/Zero1'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<S55>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Switch_Threshold_b
   * Referenced by: '<S13>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Switch_Threshold_c
   * Referenced by: '<S85>/Switch'
   */
  6.28318548F,

  /* Computed Parameter: Gain_Gain_jm
   * Referenced by: '<S15>/Gain'
   */
  1.0F,

  /* Computed Parameter: Gain1_Gain_e
   * Referenced by: '<S15>/Gain1'
   */
  1.0F,

  /* Computed Parameter: Gain2_Gain_f
   * Referenced by: '<S15>/Gain2'
   */
  1.0F,

  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S15>/Gain3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u1_Gain
   * Referenced by: '<S90>/DutyCycle_u1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u2_Gain
   * Referenced by: '<S90>/DutyCycle_u2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_u3_Gain
   * Referenced by: '<S90>/DutyCycle_u3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v1_Gain
   * Referenced by: '<S90>/DutyCycle_v1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v2_Gain
   * Referenced by: '<S90>/DutyCycle_v2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_v3_Gain
   * Referenced by: '<S90>/DutyCycle_v3'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w1_Gain
   * Referenced by: '<S90>/DutyCycle_w1'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w2_Gain
   * Referenced by: '<S90>/DutyCycle_w2'
   */
  1.0F,

  /* Computed Parameter: DutyCycle_w3_Gain
   * Referenced by: '<S90>/DutyCycle_w3'
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

  /* Computed Parameter: Constant_Value_l
   * Referenced by: '<S49>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_eg
   * Referenced by: '<S51>/Constant'
   */
  0U,

  /* Computed Parameter: Constant_Value_f
   * Referenced by: '<S53>/Constant'
   */
  0U,

  /* Computed Parameter: NoError_Manual_Value
   * Referenced by: '<S8>/NoError_Manual'
   */
  false,

  /* Computed Parameter: Constant2_Value_f
   * Referenced by: '<S56>/Constant2'
   */
  false,

  /* Computed Parameter: Constant1_Value_d
   * Referenced by: '<S56>/Constant1'
   */
  true,

  /* Computed Parameter: Constant2_Value_c
   * Referenced by: '<S57>/Constant2'
   */
  true,

  /* Computed Parameter: Constant4_Value_f
   * Referenced by: '<S57>/Constant4'
   */
  true,

  /* Computed Parameter: Constant2_Value_gw
   * Referenced by: '<S12>/Constant2'
   */
  false,

  /* Computed Parameter: Constant1_Value_n
   * Referenced by: '<S12>/Constant1'
   */
  true,

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S63>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_dc
   * Referenced by: '<S79>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_eo
   * Referenced by: '<S80>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_ep
   * Referenced by: '<S84>/Constant'
   */
  false,

  /* Computed Parameter: Logic_table
   * Referenced by: '<S77>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_l
   * Referenced by: '<S78>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_o
   * Referenced by: '<S62>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_lc
   * Referenced by: '<S83>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: SELECT_DataSource_Value
   * Referenced by: '<S8>/SELECT_DataSource'
   */
  true,

  /* Computed Parameter: Logic_table_l5
   * Referenced by: '<S64>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_p
   * Referenced by: '<S65>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_j
   * Referenced by: '<S66>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_o1
   * Referenced by: '<S67>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_i
   * Referenced by: '<S68>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_c
   * Referenced by: '<S69>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_ij
   * Referenced by: '<S70>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_pd
   * Referenced by: '<S71>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false },

  /* Computed Parameter: Logic_table_a
   * Referenced by: '<S72>/Logic'
   */
  { false, true, false, false, true, true, false, false, true, false, true, true,
    false, false, false, false }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
