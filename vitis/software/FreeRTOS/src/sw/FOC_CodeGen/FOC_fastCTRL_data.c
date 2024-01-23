/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_fastCTRL_data.c
 *
 * Code generated for Simulink model 'FOC_fastCTRL'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Wed Jan 10 21:30:06 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_fastCTRL.h"

/* Block parameters (default storage) */
P_FOC_fastCTRL_T FOC_fastCTRL_P = {
  /* Variable: DutyCycle_1
   * Referenced by: '<S2>/DutyCycle1_ManualMode'
   */
  0.0,

  /* Variable: DutyCycle_2
   * Referenced by: '<S2>/DutyCycle2_ManualMode'
   */
  0.0,

  /* Variable: DutyCycle_3
   * Referenced by: '<S2>/DutyCycle3_ManualMode'
   */
  0.0,

  /* Variable: DutyCycle_4
   * Referenced by: '<S2>/DutyCycle4_ManualMode'
   */
  0.0,

  /* Variable: DutyCycle_5
   * Referenced by: '<S2>/DutyCycle5_ManualMode'
   */
  0.0,

  /* Variable: DutyCycle_6
   * Referenced by: '<S2>/DutyCycle6_ManualMode'
   */
  0.0,

  /* Variable: FOC_6ph_AngleShift
   * Referenced by:
   *   '<S5>/FOC_6ph_AngleShift'
   *   '<S6>/FOC_6ph_AngleShift'
   *   '<S7>/FOC_6ph_AngleShift'
   */
  0.0,

  /* Variable: FOC_AKS_Mode
   * Referenced by: '<S2>/FOC_AKS_Mode'
   */
  1.0,

  /* Variable: FOC_AngleEst_AutoSwitch_wel_off
   * Referenced by: '<S5>/AutoSwitchHysteresis'
   */
  785.0,

  /* Variable: FOC_AngleEst_AutoSwitch_wel_on
   * Referenced by: '<S5>/AutoSwitchHysteresis'
   */
  942.0,

  /* Variable: FOC_AngleEst_Delay1
   * Referenced by:
   *   '<S14>/FOC_AngleEst_Delay1'
   *   '<S21>/FOC_AngleEst_Delay1'
   */
  1.0,

  /* Variable: FOC_AngleEst_Delay2
   * Referenced by:
   *   '<S14>/FOC_AngleEst_Delay2'
   *   '<S21>/FOC_AngleEst_Delay2'
   */
  0.0,

  /* Variable: FOC_AngleEst_Komp_KP
   * Referenced by:
   *   '<S3>/komp_kp'
   *   '<S4>/komp_kp'
   */
  500.0,

  /* Variable: FOC_AngleEst_Lq
   * Referenced by:
   *   '<S3>/FOC_AngleEst_Lq'
   *   '<S4>/FOC_AngleEst_Lq'
   */
  0.0008,

  /* Variable: FOC_AngleEst_Psi_InitVal
   * Referenced by:
   *   '<S15>/Unit Delay'
   *   '<S22>/Unit Delay'
   */
  0.0,

  /* Variable: FOC_AngleEst_Rs
   * Referenced by:
   *   '<S3>/FOC_AngleEst_Rs'
   *   '<S4>/FOC_AngleEst_Rs'
   */
  0.066,

  /* Variable: FOC_AngleEst_w_el_filtered_Tau
   * Referenced by:
   *   '<S12>/Tau'
   *   '<S19>/Tau'
   */
  0.0005,

  /* Variable: FOC_AngleObs_w_InitVal
   * Referenced by: '<S33>/Unit Delay1'
   */
  0.0,

  /* Variable: FOC_AngleObserver_D
   * Referenced by: '<S26>/Constant1'
   */
  1.0,

  /* Variable: FOC_AngleObserver_w0
   * Referenced by: '<S26>/Constant'
   */
  200.0,

  /* Variable: FOC_Enable
   * Referenced by: '<S1>/Enable'
   */
  1.0,

  /* Variable: FOC_IntegDamp
   * Referenced by:
   *   '<S41>/FOC_IntegDamp'
   *   '<S45>/FOC_IntegDamp'
   */
  0.995,

  /* Variable: FOC_KI
   * Referenced by:
   *   '<S41>/FOC_KI'
   *   '<S45>/FOC_KI'
   */
  1000.0,

  /* Variable: FOC_KP
   * Referenced by:
   *   '<S41>/FOC_KP1'
   *   '<S45>/FOC_KP1'
   */
  1.0,

  /* Variable: FOC_MANUAL_U_DC
   * Referenced by: '<S1>/Udc1'
   */
  0.0,

  /* Variable: FOC_MaxModInd
   * Referenced by:
   *   '<S40>/FOC_MaxModInd'
   *   '<S44>/FOC_MaxModInd'
   */
  1.1,

  /* Variable: FOC_Mode_Intern
   * Referenced by: '<S1>/FOC_Mode_Intern'
   */
  3.0,

  /* Variable: FOC_OmegaObs3
   * Referenced by: '<S26>/Gain4'
   */
  0.0,

  /* Variable: FOC_PhiSensorTdead
   * Referenced by: '<S26>/Constant2'
   */
  0.0,

  /* Variable: FOC_PhiSensorTdead_AngleEst
   * Referenced by: '<S26>/Constant3'
   */
  5.0E-6,

  /* Variable: FOC_SELECT_AngleAdaption2PolePairs
   * Referenced by: '<S5>/Constant2'
   */
  0.0,

  /* Variable: FOC_SELECT_AngleAdaptionRange
   * Referenced by: '<S5>/Constant4'
   */
  0.0,

  /* Variable: FOC_SELECT_AngleEst
   * Referenced by: '<S5>/Constant1'
   */
  0.0,

  /* Variable: FOC_SELECT_AngleEst_AutoSwitch
   * Referenced by: '<S5>/Constant5'
   */
  0.0,

  /* Variable: FOC_SELECT_AngleEst_w_el_filtered
   * Referenced by:
   *   '<S3>/useFilteredCorrection'
   *   '<S4>/useFilteredCorrection'
   */
  1.0,

  /* Variable: FOC_SELECT_InvertAngle
   * Referenced by: '<S5>/FOC_Invert_Encoder'
   */
  1.0,

  /* Variable: FOC_SELECT_Mode_Intern
   * Referenced by: '<S1>/FOC_SELECT_Mode_Intern'
   */
  0.0,

  /* Variable: FOC_SELECT_Modulation
   * Referenced by: '<S8>/Enable_SuperSinMod'
   */
  1.0,

  /* Variable: FOC_SELECT_U_DC_INPUT
   * Referenced by: '<S1>/0: P_Udc 1: Udc_measured'
   */
  1.0,

  /* Variable: FOC_SELECT_phi
   * Referenced by: '<S5>/Constant3'
   */
  2.0,

  /* Variable: FOC_Uf_U_max
   * Referenced by: '<S49>/Saturation1'
   */
  0.0,

  /* Variable: FOC_Uf_U_min
   * Referenced by: '<S49>/Saturation1'
   */
  0.0,

  /* Variable: FOC_Uf_Ud
   * Referenced by: '<S7>/Uf_Ud'
   */
  0.0,

  /* Variable: FOC_Uf_f_el
   * Referenced by: '<S7>/Uf_w_el'
   */
  0.0,

  /* Variable: FOC_Uf_m
   * Referenced by: '<S49>/Gain'
   */
  0.0,

  /* Variable: FOC_f_fastCTRL
   * Referenced by:
   *   '<S5>/FOC_T_fast'
   *   '<S12>/FOC_f_fast'
   *   '<S13>/FOC_f_fastCTRL'
   *   '<S13>/FOC_f_fastCTRL1'
   *   '<S15>/FOC_T_fast'
   *   '<S19>/FOC_f_fast'
   *   '<S20>/FOC_f_fastCTRL'
   *   '<S20>/FOC_f_fastCTRL1'
   *   '<S22>/FOC_T_fast'
   *   '<S26>/FOC_T_fast'
   *   '<S48>/FOC_T_fast'
   *   '<S33>/FOC_T_fast'
   *   '<S34>/FOC_T_fast'
   *   '<S41>/FOC_T_fast'
   *   '<S45>/FOC_T_fast'
   */
  10000.0,

  /* Variable: FOC_output_trafo_delay
   * Referenced by: '<S5>/FOC_output_trafo_delay'
   */
  1.5,

  /* Variable: FOC_phi_offset
   * Referenced by: '<S5>/Constant'
   */
  1.794,

  /* Variable: FOC_z_P
   * Referenced by: '<S25>/Anpassung der Signalfrequenz an Polpaarzahl'
   */
  4.0,

  /* Variable: Factor_OmegaRot
   * Referenced by: '<S26>/Gain5'
   */
  1.0,

  /* Variable: Par1
   * Referenced by: '<S1>/Par1'
   */
  0.0,

  /* Variable: Par2
   * Referenced by: '<S1>/Par2'
   */
  0.0,

  /* Variable: Par3
   * Referenced by: '<S1>/Par3'
   */
  0.0,

  /* Variable: Par4
   * Referenced by: '<S1>/Par4'
   */
  0.0,

  /* Variable: Par5
   * Referenced by: '<S1>/Par5'
   */
  0.0,

  /* Variable: Par6
   * Referenced by: '<S1>/Par6'
   */
  0.0,

  /* Variable: Par7
   * Referenced by: '<S1>/Par7'
   */
  0.0,

  /* Variable: Par8
   * Referenced by: '<S1>/Par8'
   */
  0.0,

  /* Mask Parameter: AntiWindupGT_d_const
   * Referenced by: '<S42>/Constant'
   */
  0.0,

  /* Mask Parameter: AntiWindupGT_q_const
   * Referenced by: '<S43>/Constant'
   */
  0.0,

  /* Mask Parameter: AntiWindupGT_d_const_m
   * Referenced by: '<S46>/Constant'
   */
  0.0,

  /* Mask Parameter: AntiWindupGT_q_const_h
   * Referenced by: '<S47>/Constant'
   */
  0.0,

  /* Expression: 1/2
   * Referenced by: '<S53>/Factor'
   */
  0.5,

  /* Expression: 1/2
   * Referenced by: '<S53>/Factor1'
   */
  0.5,

  /* Expression: 1
   * Referenced by: '<S50>/[0..2]'
   */
  1.0,

  /* Expression: 1/2
   * Referenced by: '<S50>/[0..1]'
   */
  0.5,

  /* Expression: 1
   * Referenced by: '<S50>/Limit [0..1]'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S50>/Limit [0..1]'
   */
  0.0,

  /* Expression: [0 0 0 0 0 0]
   * Referenced by: '<S2>/AKS_LS'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: [1 1 1 1 1 1]
   * Referenced by: '<S2>/AKS_HS'
   */
  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

  /* Expression: [0.5 0.5 0.5 0.5 0.5 0.5]
   * Referenced by: '<S2>/AKS_LSHS'
   */
  { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 },

  /* Expression: 0
   * Referenced by: '<S10>/Constant2'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S10>/Constant3'
   */
  6.2831853071795862,

  /* Expression: -2*pi
   * Referenced by: '<S10>/Constant1'
   */
  -6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S10>/Constant'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S11>/Constant'
   */
  6.2831853071795862,

  /* Expression: -2*pi
   * Referenced by: '<S13>/Bias'
   */
  -6.2831853071795862,

  /* Expression: 1
   * Referenced by: '<S3>/Constant1'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S3>/Constant2'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S17>/Constant2'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S17>/Constant3'
   */
  6.2831853071795862,

  /* Expression: -2*pi
   * Referenced by: '<S17>/Constant1'
   */
  -6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S17>/Constant'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S18>/Constant'
   */
  6.2831853071795862,

  /* Expression: -2*pi
   * Referenced by: '<S20>/Bias'
   */
  -6.2831853071795862,

  /* Expression: 1
   * Referenced by: '<S4>/Constant1'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S4>/Constant2'
   */
  -1.0,

  /* Expression: 2*pi
   * Referenced by: '<S31>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S31>/Constant1'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S31>/Switch1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S31>/Switch2'
   */
  0.0,

  /* Expression: -2*pi
   * Referenced by: '<S32>/Constant5'
   */
  -6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S32>/Constant6'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S32>/Constant2'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S32>/Constant4'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S27>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S28>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S28>/Constant1'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S29>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S29>/Constant1'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S30>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S30>/Constant1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S41>/IntegStopSwitch3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S45>/IntegStopSwitch3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S41>/Zero'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S45>/Zero'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S48>/Gain1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S48>/Constant1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S51>/Constant2'
   */
  1.0,

  /* Expression: 1/2
   * Referenced by: '<S51>/U_DC//2'
   */
  0.5,

  /* Expression: 1
   * Referenced by: '<S51>/ModInd_1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S51>/ModInd_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S52>/Constant2'
   */
  1.0,

  /* Expression: 1/2
   * Referenced by: '<S52>/U_DC//2'
   */
  0.5,

  /* Expression: [1,0;-0.5,sqrt(3)/2;-0.5,-sqrt(3)/2]
   * Referenced by: '<S54>/Constant'
   */
  { 1.0, -0.5, -0.5, 0.0, 0.8660254037844386, -0.8660254037844386 },

  /* Expression: [0;0;0;0;0;0]
   * Referenced by: '<S1>/Null'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: [1-0.995]
   * Referenced by: '<S7>/Discrete Transfer Fcn'
   */
  0.0050000000000000044,

  /* Expression: [1 -0.995]
   * Referenced by: '<S7>/Discrete Transfer Fcn'
   */
  { 1.0, -0.995 },

  /* Expression: 0
   * Referenced by: '<S7>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S7>/f_2_w_el'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S48>/Unit Delay'
   */
  0.0,

  /* Expression: [1 -0.5 -0.5;0 sqrt(3)/2 -sqrt(3)/2]*2/3
   * Referenced by: '<S38>/TrafoMatrix uvw->alphabeta'
   */
  { 0.66666666666666663, 0.0, -0.33333333333333331, 0.57735026918962573,
    -0.33333333333333331, -0.57735026918962573 },

  /* Expression: 1
   * Referenced by: '<S5>/AutoSwitchHysteresis'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S5>/AutoSwitchHysteresis'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S25>/Switch'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S5>/ResolverOffsetLimitation'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S5>/ResolverOffsetLimitation'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S11>/Switch_Phi'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S12>/Unit Delay'
   */
  0.0,

  /* Expression: [1 -1]
   * Referenced by: '<S13>/Discrete Transfer Fcn'
   */
  { 1.0, -1.0 },

  /* Expression: [1 0]
   * Referenced by: '<S13>/Discrete Transfer Fcn'
   */
  { 1.0, 0.0 },

  /* Expression: 0
   * Referenced by: '<S13>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 3/2*pi
   * Referenced by: '<S13>/Constant'
   */
  4.71238898038469,

  /* Expression: 1/2*pi
   * Referenced by: '<S13>/Constant1'
   */
  1.5707963267948966,

  /* Expression: pi
   * Referenced by: '<S13>/Constant2'
   */
  3.1415926535897931,

  /* Expression: [1 -1]
   * Referenced by: '<S13>/Discrete Transfer Fcn1'
   */
  { 1.0, -1.0 },

  /* Expression: [1 0]
   * Referenced by: '<S13>/Discrete Transfer Fcn1'
   */
  { 1.0, 0.0 },

  /* Expression: 0
   * Referenced by: '<S13>/Discrete Transfer Fcn1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/Switch'
   */
  0.0,

  /* Expression: pi/2
   * Referenced by: '<S3>/Constant'
   */
  1.5707963267948966,

  /* Expression: 2*pi
   * Referenced by: '<S10>/Switch2'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S10>/Switch1'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S30>/Switch1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S30>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S32>/Unit Delay'
   */
  0.0,

  /* Expression: -pi
   * Referenced by: '<S32>/Constant3'
   */
  -3.1415926535897931,

  /* Expression: pi
   * Referenced by: '<S32>/Constant1'
   */
  3.1415926535897931,

  /* Expression: 0
   * Referenced by: '<S26>/Unit Delay3'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S28>/Switch1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S28>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S41>/IntegDelay1'
   */
  0.0,

  /* Expression: [1 -0.5 -0.5;0 sqrt(3)/2 -sqrt(3)/2]*2/3
   * Referenced by: '<S39>/TrafoMatrix uvw->alphabeta'
   */
  { 0.66666666666666663, 0.0, -0.33333333333333331, 0.57735026918962573,
    -0.33333333333333331, -0.57735026918962573 },

  /* Expression: 0
   * Referenced by: '<S45>/IntegDelay1'
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S29>/Switch1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S29>/Switch2'
   */
  0.0,

  /* Expression: [0,-1;1,0]
   * Referenced by: '<S56>/Gain1'
   */
  { 0.0, 1.0, -1.0, 0.0 },

  /* Expression: [1,0;0,1]
   * Referenced by: '<S56>/Gain'
   */
  { 1.0, 0.0, 0.0, 1.0 },

  /* Expression: [1,0;-0.5,sqrt(3)/2;-0.5,-sqrt(3)/2]
   * Referenced by: '<S55>/Constant'
   */
  { 1.0, -0.5, -0.5, 0.0, 0.8660254037844386, -0.8660254037844386 },

  /* Expression: [0,-1;1,0]
   * Referenced by: '<S57>/Gain1'
   */
  { 0.0, 1.0, -1.0, 0.0 },

  /* Expression: [1,0;0,1]
   * Referenced by: '<S57>/Gain'
   */
  { 1.0, 0.0, 0.0, 1.0 },

  /* Expression: 0
   * Referenced by: '<S1>/Switch1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S3>/Gain2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S3>/Gain3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S3>/Gain4'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S12>/Constant'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S14>/Unit Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S14>/Unit Delay1'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<S14>/Switch4'
   */
  0.5,

  /* Expression: 0.5
   * Referenced by: '<S14>/Switch3'
   */
  0.5,

  /* Expression: 0
   * Referenced by: '<S18>/Switch_Phi'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S19>/Unit Delay'
   */
  0.0,

  /* Expression: [1 -1]
   * Referenced by: '<S20>/Discrete Transfer Fcn'
   */
  { 1.0, -1.0 },

  /* Expression: [1 0]
   * Referenced by: '<S20>/Discrete Transfer Fcn'
   */
  { 1.0, 0.0 },

  /* Expression: 0
   * Referenced by: '<S20>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 3/2*pi
   * Referenced by: '<S20>/Constant'
   */
  4.71238898038469,

  /* Expression: 1/2*pi
   * Referenced by: '<S20>/Constant1'
   */
  1.5707963267948966,

  /* Expression: pi
   * Referenced by: '<S20>/Constant2'
   */
  3.1415926535897931,

  /* Expression: [1 -1]
   * Referenced by: '<S20>/Discrete Transfer Fcn1'
   */
  { 1.0, -1.0 },

  /* Expression: [1 0]
   * Referenced by: '<S20>/Discrete Transfer Fcn1'
   */
  { 1.0, 0.0 },

  /* Expression: 0
   * Referenced by: '<S20>/Discrete Transfer Fcn1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/Switch'
   */
  0.0,

  /* Expression: pi/2
   * Referenced by: '<S4>/Constant'
   */
  1.5707963267948966,

  /* Expression: 2*pi
   * Referenced by: '<S17>/Switch2'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S17>/Switch1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S19>/Constant'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S21>/Unit Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S21>/Unit Delay1'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<S21>/Switch4'
   */
  0.5,

  /* Expression: 0.5
   * Referenced by: '<S21>/Switch3'
   */
  0.5,

  /* Expression: 1
   * Referenced by: '<S4>/phi_est_2'
   */
  1.0,

  /* Expression: 2*pi
   * Referenced by: '<S25>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2
   * Referenced by: '<S26>/Gain'
   */
  2.0,

  /* Expression: 0
   * Referenced by: '<S34>/Unit Delay1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain4'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain5'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain6'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S5>/dummy_gain7'
   */
  1.0,

  /* Expression: 1/sqrt(2)
   * Referenced by: '<S35>/I_ph_RMS'
   */
  0.70710678118654746,

  /* Expression: [0,0]
   * Referenced by: '<S41>/Zero1'
   */
  { 0.0, 0.0 },

  /* Expression: 1
   * Referenced by: '<S36>/I_d_Ref'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S36>/I_q_Ref'
   */
  1.0,

  /* Expression: [0,0]
   * Referenced by: '<S45>/Zero1'
   */
  { 0.0, 0.0 },

  /* Expression: 1
   * Referenced by: '<S38>/I_d_Act_1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S38>/I_q_Act_1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S38>/I_u_1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S38>/I_v_1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S38>/I_w_1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S38>/Discrete FIR Filter 20th order'
   */
  0.0,

  /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
   * Referenced by: '<S38>/Discrete FIR Filter 20th order'
   */
  { 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
    0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05 },

  /* Expression: 1
   * Referenced by: '<S38>/Gain5'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S38>/Gain6'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S39>/Discrete FIR Filter 20th order'
   */
  0.0,

  /* Expression: 1/20*[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
   * Referenced by: '<S39>/Discrete FIR Filter 20th order'
   */
  { 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
    0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05 },

  /* Expression: 1
   * Referenced by: '<S39>/I_d_Act_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S39>/I_d_Act_filt_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S39>/I_q_Act_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S39>/I_q_Act_filt_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S39>/I_u_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S39>/I_v_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S39>/I_w_2'
   */
  1.0,

  /* Expression: 2*pi
   * Referenced by: '<S48>/Switch'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S1>/Unit Delay'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S56>/U_d_1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S56>/U_q_1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S57>/U_d_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S57>/U_q_2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S9>/Discrete FIR Filter 10th order'
   */
  0.0,

  /* Expression: 1/10*[1 1 1 1 1 1 1 1 1 1]
   * Referenced by: '<S9>/Discrete FIR Filter 10th order'
   */
  { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 },

  /* Expression: 0
   * Referenced by: '<S1>/Manipulate_FOC_Error'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Cnt_State'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S1>/Cnt_1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Cnt_2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Cnt_3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Cnt_4'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Cnt_5'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Cnt_6'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Cnt_7'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Cnt_8'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Constant1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Counter_Start'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S1>/FCF_Cnt'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S1>/Sig1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Sig2'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Sig3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Sig4'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Sig5'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Sig6'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Sig7'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/Sig8'
   */
  1.0
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
