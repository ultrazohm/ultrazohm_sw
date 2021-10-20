///*
// * Academic License - for use in teaching, academic research, and meeting
// * course requirements at degree granting institutions only.  Not for
// * government, commercial, or other organizational use.
// *
// * File: FOC0.c
// *
// * Code generated for Simulink model 'FOC0'.
// *
// * Model version                  : 6.2
// * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
// * C/C++ source code generated on : Tue May 25 15:31:25 2021
// *
// * Target selection: ert.tlc
// * Embedded hardware selection: ARM Compatible->ARM Cortex-R
// * Code generation objectives:
// *    1. Execution efficiency
// *    2. Traceability
// * Validation result: Passed (7), Warnings (3), Errors (2)
// */
//
//#include "FOC0.h"
//
///* Exported block parameters */
//real_T Kpd = 0.075398223686155036;     /* Variable: Kpd
//                                        * Referenced by:
//                                        *   '<S94>/Proportional Gain'
//                                        *   '<S100>/P Copy'
//                                        */
//real_T Kpn = 1.224610768327322;        /* Variable: Kpn
//                                        * Referenced by:
//                                        *   '<S44>/Proportional Gain'
//                                        *   '<S50>/P Copy'
//                                        */
//real_T Kpq = 0.12566370614359174;      /* Variable: Kpq
//                                        * Referenced by:
//                                        *   '<S144>/Proportional Gain'
//                                        *   '<S150>/P Copy'
//                                        */
//real_T Tnd = 0.0013043478260869566;    /* Variable: Tnd
//                                        * Referenced by: '<S93>/Integral Gain'
//                                        */
//real_T Tnn = 9999; /*0.039788735772973829;     /* Variable: Tnn
//                                        * Referenced by: '<S43>/Integral Gain'
//                                        */
//real_T Tnq = 0.0021739130434782609;    /* Variable: Tnq
//                                        * Referenced by: '<S143>/Integral Gain'
//                                        */
//
///*===========*
// * Constants *
// *===========*/
//#define RT_PI                          3.14159265358979323846
//#define RT_PIF                         3.1415927F
//#define RT_LN_10                       2.30258509299404568402
//#define RT_LN_10F                      2.3025851F
//#define RT_LOG10E                      0.43429448190325182765
//#define RT_LOG10EF                     0.43429449F
//#define RT_E                           2.7182818284590452354
//#define RT_EF                          2.7182817F
//
///*
// * UNUSED_PARAMETER(x)
// *   Used to specify that a function parameter (argument) is required but not
// *   accessed by the function body.
// */
//#ifndef UNUSED_PARAMETER
//#if defined(__LCC__)
//#define UNUSED_PARAMETER(x)                                      /* do nothing */
//#else
//
///*
// * This is the semi-ANSI standard way of indicating that an
// * unused function parameter is required.
// */
//#define UNUSED_PARAMETER(x)            (void) (x)
//#endif
//#endif
//
///* Model step function */
//void FOC0_step(RT_MODEL *const rtM)
//{
//  B *rtB = rtM->blockIO;
//  DW *rtDW = rtM->dwork;
//  ExtU *rtU = (ExtU *) rtM->inputs;
//  ExtY *rtY = (ExtY *) rtM->outputs;
//  real_T a;
//  real_T a_U_on;
//  real_T a_V_on;
//  real_T a_W_on;
//  real_T a_tmp;
//  real_T b;
//  real_T c;
//  real_T rtb_IntegralGain;
//  real_T rtb_Integrator_j;
//  real_T rtb_ProportionalGain;
//  real_T rtb_ProportionalGain_tmp;
//  real_T rtb_SignPreSat;
//  real_T rtb_SignPreSat_o;
//  real_T u2;
//  int32_T quadrant;
//  int32_T sector;
//  real32_T rtb_Gain1[3];
//  real32_T tmp[3];
//  real32_T rtb_Switch_hl_idx_0;
//  real32_T rtb_Switch_hl_idx_1;
//  real32_T rtb_Switch_n_idx_0;
//  real32_T rtb_Switch_n_idx_1;
//  boolean_T rtb_AND1;
//  boolean_T rtb_AND1_b;
//  boolean_T rtb_AND2;
//  boolean_T rtb_AND2_g;
//  boolean_T rtb_Equal1;
//  boolean_T rtb_Equal2;
//  boolean_T rtb_NotEqual;
//  boolean_T rtb_NotEqual_a;
//  boolean_T rtb_NotEqual_g;
//  for (quadrant = 0; quadrant < 3; quadrant++) {
//    /* Gain: '<S7>/Gain3' incorporates:
//     *  Inport: '<Root>/i1'
//     *  Inport: '<Root>/i2'
//     *  Inport: '<Root>/i3'
//     */
//    tmp[quadrant] = 0.0F;
//    tmp[quadrant] += rtConstP.Gain3_Gain[quadrant] * rtU->i1;
//    tmp[quadrant] += rtConstP.Gain3_Gain[quadrant + 3] * rtU->i2;
//    tmp[quadrant] += rtConstP.Gain3_Gain[quadrant + 6] * rtU->i3;
//
//    /* Gain: '<S7>/Gain1' incorporates:
//     *  Gain: '<S7>/Gain3'
//     */
//    rtb_Gain1[quadrant] = 0.666666687F * tmp[quadrant];
//  }
//
//  /* Outputs for Enabled SubSystem: '<S2>/Subsystem1' incorporates:
//   *  EnablePort: '<S12>/Enable'
//   */
//  if (rtConstB.Compare > 0) {
//    /* Fcn: '<S12>/Fcn' incorporates:
//     *  Fcn: '<S12>/Fcn1'
//     *  Inport: '<Root>/theta_el'
//     */
//    rtb_Switch_hl_idx_0 = (real32_T)sin(rtU->theta_el);
//    rtb_Switch_hl_idx_1 = (real32_T)cos(rtU->theta_el);
//
//    /* Fcn: '<S12>/Fcn' */
//    rtB->Fcn_h = rtb_Gain1[0] * rtb_Switch_hl_idx_1 + rtb_Gain1[1] *
//      rtb_Switch_hl_idx_0;
//
//    /* Fcn: '<S12>/Fcn1' */
//    rtB->Fcn1_o = -rtb_Gain1[0] * rtb_Switch_hl_idx_0 + rtb_Gain1[1] *
//      rtb_Switch_hl_idx_1;
//  }
//
//  /* End of Outputs for SubSystem: '<S2>/Subsystem1' */
//
//  /* Outputs for Enabled SubSystem: '<S2>/Subsystem - pi//2 delay' incorporates:
//   *  EnablePort: '<S11>/Enable'
//   */
//  if (rtConstB.Compare_o > 0) {
//    /* Fcn: '<S11>/Fcn' incorporates:
//     *  Inport: '<Root>/theta_el'
//     */
//    rtB->Fcn_ig = rtb_Gain1[0] * (real32_T)sin(rtU->theta_el) - rtb_Gain1[1] *
//      (real32_T)cos(rtU->theta_el);
//
//    /* Fcn: '<S11>/Fcn1' incorporates:
//     *  Inport: '<Root>/theta_el'
//     */
//    rtB->Fcn1_j = rtb_Gain1[0] * (real32_T)cos(rtU->theta_el) + rtb_Gain1[1] *
//      (real32_T)sin(rtU->theta_el);
//  }
//
//  /* End of Outputs for SubSystem: '<S2>/Subsystem - pi//2 delay' */
//
//  /* Switch: '<S2>/Switch' */
//  if (rtConstB.Compare != 0) {
//    rtb_Switch_n_idx_0 = rtB->Fcn_h;
//    rtb_Switch_n_idx_1 = rtB->Fcn1_o;
//  } else {
//    rtb_Switch_n_idx_0 = rtB->Fcn_ig;
//    rtb_Switch_n_idx_1 = rtB->Fcn1_j;
//  }
//
//  /* End of Switch: '<S2>/Switch' */
//
//  /* DataTypeConversion: '<S1>/Data Type Conversion8' incorporates:
//   *  Inport: '<Root>/id_ref'
//   *  Sum: '<S1>/Sum3'
//   */
//  rtb_IntegralGain = rtU->id_ref - rtb_Switch_n_idx_0;
//
//  /* Gain: '<S94>/Proportional Gain' incorporates:
//   *  DiscreteIntegrator: '<S96>/Integrator'
//   *  Sum: '<S105>/Sum'
//   */
//  rtb_SignPreSat = (rtb_IntegralGain + rtDW->Integrator_DSTATE) * Kpd;
//
//  /* DataTypeConversion: '<S1>/Data Type Conversion7' incorporates:
//   *  Inport: '<Root>/n_RPM'
//   *  Inport: '<Root>/n_ref_RPM'
//   *  Sum: '<S1>/Sum1'
//   */
//  rtb_ProportionalGain_tmp = rtU->n_ref_RPM - rtU->n_RPM;
//
//  /* Gain: '<S44>/Proportional Gain' incorporates:
//   *  DataTypeConversion: '<S1>/Data Type Conversion7'
//   *  DiscreteIntegrator: '<S46>/Integrator'
//   *  Sum: '<S55>/Sum'
//   */
//  rtb_ProportionalGain = (rtb_ProportionalGain_tmp + rtDW->Integrator_DSTATE_a) *
//    Kpn;
//
//  /* Switch: '<S1>/Switch1' incorporates:
//   *  Inport: '<Root>/currentORspeedControl'
//   *  Inport: '<Root>/iq_ref'
//   */
//  if (rtU->currentORspeedControl > 1) {
//    /* Saturate: '<S53>/Saturation' */
//    if (rtb_ProportionalGain > 10.0) {
//      rtb_Integrator_j = 10.0;
//    } else if (rtb_ProportionalGain < -10.0) {
//      rtb_Integrator_j = -10.0;
//    } else {
//      rtb_Integrator_j = rtb_ProportionalGain;
//    }
//
//    /* End of Saturate: '<S53>/Saturation' */
//  } else {
//    rtb_Integrator_j = rtU->iq_ref;
//  }
//
//  /* End of Switch: '<S1>/Switch1' */
//
//  /* Sum: '<S1>/Sum4' */
//  rtb_Integrator_j -= rtb_Switch_n_idx_1;
//
//  /* Gain: '<S144>/Proportional Gain' incorporates:
//   *  DiscreteIntegrator: '<S146>/Integrator'
//   *  Sum: '<S155>/Sum'
//   */
//  rtb_SignPreSat_o = (rtb_Integrator_j + rtDW->Integrator_DSTATE_k) * Kpq;
//
//  /* Saturate: '<S103>/Saturation' */
//  if (rtb_SignPreSat > 12.0) {
//    a_V_on = 12.0;
//  } else if (rtb_SignPreSat < -12.0) {
//    a_V_on = -12.0;
//  } else {
//    a_V_on = rtb_SignPreSat;
//  }
//
//  /* End of Saturate: '<S103>/Saturation' */
//
//  /* Saturate: '<S153>/Saturation' */
//  if (rtb_SignPreSat_o > 12.0) {
//    a_W_on = 12.0;
//  } else if (rtb_SignPreSat_o < -12.0) {
//    a_W_on = -12.0;
//  } else {
//    a_W_on = rtb_SignPreSat_o;
//  }
//
//  /* End of Saturate: '<S153>/Saturation' */
//
//  /* Outport: '<Root>/ud_ctrl' incorporates:
//   *  DataTypeConversion: '<S1>/Data Type Conversion'
//   */
//  rtY->ud_ctrl = (real32_T)a_V_on;
//
//  /* Outport: '<Root>/uq_ctrl' incorporates:
//   *  DataTypeConversion: '<S1>/Data Type Conversion'
//   */
//  rtY->uq_ctrl = (real32_T)a_W_on;
//
//  /* Outputs for Enabled SubSystem: '<S8>/Subsystem1' incorporates:
//   *  EnablePort: '<S166>/Enable'
//   */
//  if (rtConstB.Compare_b > 0) {
//    /* Fcn: '<S166>/Fcn' incorporates:
//     *  Fcn: '<S166>/Fcn1'
//     *  Inport: '<Root>/theta_el'
//     */
//    rtb_Switch_hl_idx_0 = (real32_T)sin(rtU->theta_el);
//    rtb_Switch_hl_idx_1 = (real32_T)cos(rtU->theta_el);
//
//    /* Fcn: '<S166>/Fcn' incorporates:
//     *  DataTypeConversion: '<S1>/Data Type Conversion'
//     */
//    rtB->Fcn = (real32_T)a_V_on * rtb_Switch_hl_idx_1 - (real32_T)a_W_on *
//      rtb_Switch_hl_idx_0;
//
//    /* Fcn: '<S166>/Fcn1' incorporates:
//     *  DataTypeConversion: '<S1>/Data Type Conversion'
//     */
//    rtB->Fcn1 = (real32_T)a_V_on * rtb_Switch_hl_idx_0 + (real32_T)a_W_on *
//      rtb_Switch_hl_idx_1;
//  }
//
//  /* End of Outputs for SubSystem: '<S8>/Subsystem1' */
//
//  /* Outputs for Enabled SubSystem: '<S8>/Subsystem - pi//2 delay' incorporates:
//   *  EnablePort: '<S165>/Enable'
//   */
//  if (rtConstB.Compare_c > 0) {
//    /* Fcn: '<S165>/Fcn' incorporates:
//     *  DataTypeConversion: '<S1>/Data Type Conversion'
//     *  Inport: '<Root>/theta_el'
//     */
//    rtB->Fcn_i = (real32_T)a_V_on * (real32_T)sin(rtU->theta_el) + (real32_T)
//      a_W_on * (real32_T)cos(rtU->theta_el);
//
//    /* Fcn: '<S165>/Fcn1' incorporates:
//     *  DataTypeConversion: '<S1>/Data Type Conversion'
//     *  Inport: '<Root>/theta_el'
//     */
//    rtB->Fcn1_e = -(real32_T)a_V_on * (real32_T)cos(rtU->theta_el) + (real32_T)
//      a_W_on * (real32_T)sin(rtU->theta_el);
//  }
//
//  /* End of Outputs for SubSystem: '<S8>/Subsystem - pi//2 delay' */
//
//  /* Switch: '<S8>/Switch' */
//  if (rtConstB.Compare_b != 0) {
//    rtb_Switch_hl_idx_0 = rtB->Fcn;
//    rtb_Switch_hl_idx_1 = rtB->Fcn1;
//  } else {
//    rtb_Switch_hl_idx_0 = rtB->Fcn_i;
//    rtb_Switch_hl_idx_1 = rtB->Fcn1_e;
//  }
//
//  /* End of Switch: '<S8>/Switch' */
//
//  /* Outport: '<Root>/id' */
//  rtY->id = rtb_Switch_n_idx_0;
//
//  /* Outport: '<Root>/iq' */
//  rtY->iq = rtb_Switch_n_idx_1;
//
//  /* MATLAB Function: '<S1>/RZM_Traegerbasiert' incorporates:
//   *  DataTypeConversion: '<S1>/Data Type Conversion1'
//   *  DataTypeConversion: '<S1>/Data Type Conversion2'
//   *  DataTypeConversion: '<S1>/Data Type Conversion3'
//   *  DataTypeConversion: '<S1>/Data Type Conversion5'
//   *  Inport: '<Root>/period'
//   *  Inport: '<Root>/u_dc'
//   */
//  /* MATLAB Function 'FOC/RZM_Traegerbasiert': '<S6>:1' */
//  /* '<S6>:1:4' a_U_on=0; */
//  a_U_on = 0.0;
//
//  /* '<S6>:1:5' a_V_on=0; */
//  a_V_on = 0.0;
//
//  /* '<S6>:1:6' a_W_on=0; */
//  a_W_on = 0.0;
//
//  /* '<S6>:1:7' CMP_U=0; */
//  /* '<S6>:1:8' CMP_V=0; */
//  /* '<S6>:1:9' CMP_W=0; */
//  /* __%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%_ */
//  /* Tr‰gerbasierte Raumzeigermodulation%% */
//  /* Eing‰nge: */
//  /* U_ZK       -- Zwischenkreisspannung */
//  /* u_alpha    -- alphakomponente des Sollspannungsraumzeigers */
//  /* u_beta     -- betakomponente des Sollspannungsraumzeigers */
//  /* CMP_Period_max_val  -- maximalwert des Dreiecks/S‰gezahnz‰hlers zum Gewichten der Aussteuergrade */
//  /* Ausg‰nge: */
//  /* CMP_U        -- Vergleichswert U */
//  /* CMP_V        -- Vergleichswert V */
//  /* CMP_W        -- Vergleichswert W */
//  /* sector       -- Ausgabe des Sektors des Spannungszeigers */
//  /* Berechnung von a, b, c nach Quang Dittrich S24 */
//  /* '<S6>:1:27' a = abs(u_alpha) + 0.5774*abs(u_beta); */
//  a_tmp = fabs(rtb_Switch_hl_idx_0);
//  c = fabs(rtb_Switch_hl_idx_1);
//  a = 0.5774 * c + a_tmp;
//
//  /* '<S6>:1:28' b = abs(u_alpha) - 0.5774*abs(u_beta); */
//  b = a_tmp - 0.5774 * fabs(rtb_Switch_hl_idx_1);
//
//  /* '<S6>:1:29' c = 1.1547*abs(u_beta); */
//  c *= 1.1547;
//
//  /* Sektor und Quadranten nach Quang Dittrich S32 */
//  /* '<S6>:1:33' if(u_beta < 0) */
//  if (rtb_Switch_hl_idx_1 < 0.0F) {
//    /* '<S6>:1:34' if (u_alpha <0) */
//    if (rtb_Switch_hl_idx_0 < 0.0F) {
//      /* '<S6>:1:35' quadrant=3; */
//      quadrant = 3;
//
//      /* '<S6>:1:36' if(b < 0) */
//      if (b < 0.0) {
//        /* '<S6>:1:37' sector = 5; */
//        sector = 5;
//      } else {
//        /* '<S6>:1:38' else */
//        /* '<S6>:1:39' sector = 4; */
//        sector = 4;
//      }
//    } else {
//      /* '<S6>:1:41' else */
//      /* '<S6>:1:42' quadrant=4; */
//      quadrant = 4;
//
//      /* '<S6>:1:43' if(b < 0) */
//      if (b < 0.0) {
//        /* '<S6>:1:44' sector = 5; */
//        sector = 5;
//      } else {
//        /* '<S6>:1:45' else */
//        /* '<S6>:1:46' sector = 6; */
//        sector = 6;
//      }
//    }
//  } else {
//    /* '<S6>:1:50' else */
//    /* '<S6>:1:51' if (u_alpha <0) */
//    if (rtb_Switch_hl_idx_0 < 0.0F) {
//      /* '<S6>:1:52' quadrant=2; */
//      quadrant = 2;
//
//      /* '<S6>:1:53' if(b < 0) */
//      if (b < 0.0) {
//        /* '<S6>:1:54' sector = 2; */
//        sector = 2;
//      } else {
//        /* '<S6>:1:55' else */
//        /* '<S6>:1:56' sector = 3; */
//        sector = 3;
//      }
//    } else {
//      /* '<S6>:1:58' else */
//      /* '<S6>:1:59' quadrant=1; */
//      quadrant = 1;
//
//      /* '<S6>:1:60' if(b < 0) */
//      if (b < 0.0) {
//        /* '<S6>:1:61' sector = 2; */
//        sector = 2;
//      } else {
//        /* '<S6>:1:62' else */
//        /* '<S6>:1:63' sector = 1; */
//        sector = 1;
//      }
//    }
//  }
//
//  /* '<S6>:1:68' sector = sector; */
//  /* Modulationsfunktionen f¸r Phasen U,V,W */
//  /* Erzeugung der Aussteuergrade f¸r die Halbbr¸cken */
//  /* --> Erzeugung einer "regulary Sampled SVM" erfolgt anschlieﬂend durch Abtastung */
//  /* mit Dreiecksz‰hlern in Hardware. */
//  /* '<S6>:1:75' if (sector == 1) */
//  if (sector == 1) {
//    /* '<S6>:1:77' u1 = b/(0.66667*U_ZK); */
//    a_V_on = 0.66667 * rtU->u_dc;
//    a_W_on = b / a_V_on;
//
//    /* '<S6>:1:78' u2 = c/(0.66667*U_ZK); */
//    u2 = c / a_V_on;
//
//    /* '<S6>:1:80' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
//    a_U_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
//
//    /* '<S6>:1:81' a_V_on = 0.5 - u1*0.5 + u2*0.5; */
//    a_W_on = 0.5 - a_W_on * 0.5;
//    a_V_on = a_W_on + u2 * 0.5;
//
//    /* '<S6>:1:82' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
//    a_W_on -= u2 * 0.5;
//  }
//
//  /* '<S6>:1:86' if ((sector == 2) && (quadrant == 1)) */
//  if ((sector == 2) && (quadrant == 1)) {
//    /* '<S6>:1:88' u1 = a/(0.66667*U_ZK); */
//    a_V_on = 0.66667 * rtU->u_dc;
//    a_W_on = a / a_V_on;
//
//    /* '<S6>:1:89' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(0.66667*U_ZK); */
//    u2 = (0.5774 * fabs(rtb_Switch_hl_idx_1) + -a_tmp) / a_V_on;
//
//    /* '<S6>:1:91' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
//    a_U_on = (a_W_on * 0.5 + 0.5) - u2 * 0.5;
//
//    /* '<S6>:1:92' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
//    a_V_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
//
//    /* '<S6>:1:93' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
//    a_W_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
//  }
//
//  /* '<S6>:1:97' if ((sector == 2) && (quadrant == 2)) */
//  if ((sector == 2) && (quadrant == 2)) {
//    /* '<S6>:1:99' u1 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(0.66667*U_ZK); */
//    a_W_on = (0.5774 * fabs(rtb_Switch_hl_idx_1) + -fabs(rtb_Switch_hl_idx_0)) /
//      (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:100' u2 = a/(0.66667*U_ZK); */
//    u2 = a / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:102' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
//    a_U_on = (a_W_on * 0.5 + 0.5) - u2 * 0.5;
//
//    /* '<S6>:1:103' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
//    a_V_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
//
//    /* '<S6>:1:104' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
//    a_W_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
//  }
//
//  /* '<S6>:1:108' if (sector == 3) */
//  if (sector == 3) {
//    /* '<S6>:1:110' u1 = c/(0.66667*U_ZK); */
//    a_W_on = c / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:111' u2 = b/(0.66667*U_ZK); */
//    u2 = b / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:113' a_U_on=  0.5 - u1*0.5 - u2*0.5; */
//    a_U_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
//
//    /* '<S6>:1:114' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
//    a_V_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
//
//    /* '<S6>:1:115' a_W_on = 0.5 - u1*0.5 + u2*0.5; */
//    a_W_on = (0.5 - a_W_on * 0.5) + u2 * 0.5;
//  }
//
//  /* '<S6>:1:118' if (sector == 4) */
//  if (sector == 4) {
//    /* '<S6>:1:120' u1 = b/(0.66667*U_ZK); */
//    a_W_on = b / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:121' u2 = c/(0.66667*U_ZK); */
//    u2 = c / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:123' a_U_on = 0.5 - u1*0.5 - u2*0.5; */
//    a_U_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
//
//    /* '<S6>:1:124' a_V_on = 0.5 + u1*0.5 - u2*0.5; */
//    a_W_on = a_W_on * 0.5 + 0.5;
//    a_V_on = a_W_on - u2 * 0.5;
//
//    /* '<S6>:1:125' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
//    a_W_on += u2 * 0.5;
//  }
//
//  /* '<S6>:1:129' if ((sector == 5) && (quadrant == 3)) */
//  if ((sector == 5) && (quadrant == 3)) {
//    /* '<S6>:1:131' u1 = a/(0.66667*U_ZK); */
//    a_W_on = a / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:132' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(0.66667*U_ZK); */
//    u2 = (0.5774 * fabs(rtb_Switch_hl_idx_1) + -fabs(rtb_Switch_hl_idx_0)) /
//      (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:134' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
//    a_U_on = (0.5 - a_W_on * 0.5) + u2 * 0.5;
//
//    /* '<S6>:1:135' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
//    a_V_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
//
//    /* '<S6>:1:136' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
//    a_W_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
//  }
//
//  /* '<S6>:1:140' if ((sector == 5) && (quadrant == 4)) */
//  if ((sector == 5) && (quadrant == 4)) {
//    /* '<S6>:1:142' u1 =(-abs(u_alpha) + 0.5774*abs(u_beta))/(0.66667*U_ZK); */
//    a_W_on = (0.5774 * fabs(rtb_Switch_hl_idx_1) + -fabs(rtb_Switch_hl_idx_0)) /
//      (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:143' u2 =  a/(0.66667*U_ZK); */
//    u2 = a / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:145' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
//    a_U_on = (0.5 - a_W_on * 0.5) + u2 * 0.5;
//
//    /* '<S6>:1:146' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
//    a_V_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
//
//    /* '<S6>:1:147' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
//    a_W_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
//  }
//
//  /* '<S6>:1:151' if (sector == 6) */
//  if (sector == 6) {
//    /* '<S6>:1:153' u1 = c/(0.66667*U_ZK); */
//    a_W_on = c / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:154' u2 = b/(0.66667*U_ZK); */
//    u2 = b / (0.66667 * rtU->u_dc);
//
//    /* '<S6>:1:156' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
//    a_U_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
//
//    /* '<S6>:1:157' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
//    a_V_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
//
//    /* '<S6>:1:158' a_W_on = 0.5 + u1*0.5 - u2*0.5; */
//    a_W_on = (a_W_on * 0.5 + 0.5) - u2 * 0.5;
//  }
//
//  /* Aussteuergrade auf Z‰hlregister normieren -> Comparewerte CMP */
//  /* '<S6>:1:163' CMP_U = a_U_on * CMP_Period_max_val; */
//  a_U_on *= (real_T)rtU->period;
//
//  /* '<S6>:1:164' CMP_V = a_V_on * CMP_Period_max_val; */
//  a_V_on *= (real_T)rtU->period;
//
//  /* '<S6>:1:165' CMP_W = a_W_on * CMP_Period_max_val; */
//  a_W_on *= (real_T)rtU->period;
//
//  /* Begrenzung */
//  /* '<S6>:1:168' if (CMP_U > CMP_Period_max_val) */
//  if (a_U_on > rtU->period) {
//    /* '<S6>:1:169' CMP_U = CMP_Period_max_val; */
//    a_U_on = rtU->period;
//  }
//
//  /* '<S6>:1:171' if (CMP_U < 0) */
//  if (a_U_on < 0.0) {
//    /* '<S6>:1:172' CMP_U = 0; */
//    a_U_on = 0.0;
//  }
//
//  /* '<S6>:1:175' if (CMP_V > CMP_Period_max_val) */
//  if (a_V_on > rtU->period) {
//    /* '<S6>:1:176' CMP_V = CMP_Period_max_val; */
//    a_V_on = rtU->period;
//  }
//
//  /* '<S6>:1:178' if (CMP_V < 0) */
//  if (a_V_on < 0.0) {
//    /* '<S6>:1:179' CMP_V = 0; */
//    a_V_on = 0.0;
//  }
//
//  /* '<S6>:1:182' if (CMP_W > CMP_Period_max_val) */
//  if (a_W_on > rtU->period) {
//    /* '<S6>:1:183' CMP_W = CMP_Period_max_val; */
//    a_W_on = rtU->period;
//  }
//
//  /* '<S6>:1:185' if (CMP_W < 0) */
//  if (a_W_on < 0.0) {
//    /* '<S6>:1:186' CMP_W = 0; */
//    a_W_on = 0.0;
//  }
//
//  /* DataTypeConversion: '<S1>/Data Type Conversion10' incorporates:
//   *  MATLAB Function: '<S1>/RZM_Traegerbasiert'
//   */
//  /* __%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%_ */
//  a_tmp = fmod(floor(a_U_on), 65536.0);
//
//  /* Outport: '<Root>/CMPA_1' incorporates:
//   *  DataTypeConversion: '<S1>/Data Type Conversion10'
//   */
//  rtY->CMPA_1 = (int16_T)(a_tmp < 0.0 ? (int32_T)(int16_T)-(int16_T)(uint16_T)
//    -a_tmp : (int32_T)(int16_T)(uint16_T)a_tmp);
//
//  /* DataTypeConversion: '<S1>/Data Type Conversion11' incorporates:
//   *  MATLAB Function: '<S1>/RZM_Traegerbasiert'
//   */
//  a_tmp = fmod(floor(a_V_on), 65536.0);
//
//  /* Outport: '<Root>/CMPA_2' incorporates:
//   *  DataTypeConversion: '<S1>/Data Type Conversion11'
//   */
//  rtY->CMPA_2 = (int16_T)(a_tmp < 0.0 ? (int32_T)(int16_T)-(int16_T)(uint16_T)
//    -a_tmp : (int32_T)(int16_T)(uint16_T)a_tmp);
//
//  /* DataTypeConversion: '<S1>/Data Type Conversion12' incorporates:
//   *  MATLAB Function: '<S1>/RZM_Traegerbasiert'
//   */
//  a_tmp = fmod(floor(a_W_on), 65536.0);
//
//  /* Outport: '<Root>/CMPA_3' incorporates:
//   *  DataTypeConversion: '<S1>/Data Type Conversion12'
//   */
//  rtY->CMPA_3 = (int16_T)(a_tmp < 0.0 ? (int32_T)(int16_T)-(int16_T)(uint16_T)
//    -a_tmp : (int32_T)(int16_T)(uint16_T)a_tmp);
//
//  /* Outport: '<Root>/sector' incorporates:
//   *  MATLAB Function: '<S1>/RZM_Traegerbasiert'
//   */
//  rtY->sector = sector;
//
//  /* DeadZone: '<S139>/DeadZone' */
//  if (rtb_SignPreSat_o > 12.0) {
//    rtb_SignPreSat_o -= 12.0;
//  } else if (rtb_SignPreSat_o >= -12.0) {
//    rtb_SignPreSat_o = 0.0;
//  } else {
//    rtb_SignPreSat_o -= -12.0;
//  }
//
//  /* End of DeadZone: '<S139>/DeadZone' */
//
//  /* RelationalOperator: '<S137>/NotEqual' */
//  rtb_NotEqual = (0.0 != rtb_SignPreSat_o);
//
//  /* Signum: '<S137>/SignPreSat' */
//  if (rtb_SignPreSat_o < 0.0) {
//    rtb_SignPreSat_o = -1.0;
//  } else {
//    if (rtb_SignPreSat_o > 0.0) {
//      rtb_SignPreSat_o = 1.0;
//    }
//  }
//
//  /* End of Signum: '<S137>/SignPreSat' */
//
//  /* Gain: '<S143>/Integral Gain' */
//  rtb_Integrator_j *= 1.0 / Tnq;
//
//  /* DataTypeConversion: '<S137>/DataTypeConv1' */
//  a_tmp = fmod(rtb_SignPreSat_o, 256.0);
//
//  /* Signum: '<S137>/SignPreIntegrator' */
//  if (rtb_Integrator_j < 0.0) {
//    rtb_SignPreSat_o = -1.0;
//  } else if (rtb_Integrator_j > 0.0) {
//    rtb_SignPreSat_o = 1.0;
//  } else {
//    rtb_SignPreSat_o = rtb_Integrator_j;
//  }
//
//  /* End of Signum: '<S137>/SignPreIntegrator' */
//
//  /* DataTypeConversion: '<S137>/DataTypeConv2' */
//  rtb_SignPreSat_o = fmod(rtb_SignPreSat_o, 256.0);
//
//  /* RelationalOperator: '<S137>/Equal1' incorporates:
//   *  DataTypeConversion: '<S137>/DataTypeConv1'
//   *  DataTypeConversion: '<S137>/DataTypeConv2'
//   */
//  rtb_Equal2 = ((a_tmp < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-a_tmp :
//                 (int32_T)(int8_T)(uint8_T)a_tmp) == (rtb_SignPreSat_o < 0.0 ?
//    (int32_T)(int8_T)-(int8_T)(uint8_T)-rtb_SignPreSat_o : (int32_T)(int8_T)
//    (uint8_T)rtb_SignPreSat_o));
//
//  /* Signum: '<S137>/SignP' incorporates:
//   *  Constant: '<S150>/P Copy'
//   */
//  if (Kpq < 0.0) {
//    a_tmp = -1.0;
//  } else if (Kpq > 0.0) {
//    a_tmp = 1.0;
//  } else {
//    a_tmp = Kpq;
//  }
//
//  /* End of Signum: '<S137>/SignP' */
//
//  /* DataTypeConversion: '<S137>/DataTypeConv4' */
//  a_tmp = fmod(a_tmp, 256.0);
//
//  /* RelationalOperator: '<S137>/Equal2' incorporates:
//   *  Constant: '<S137>/Constant'
//   *  DataTypeConversion: '<S137>/DataTypeConv4'
//   */
//  rtb_Equal1 = ((a_tmp < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-a_tmp :
//                 (int32_T)(int8_T)(uint8_T)a_tmp) == 1);
//
//  /* Logic: '<S137>/AND1' */
//  rtb_AND1 = (rtb_Equal2 && rtb_Equal1);
//
//  /* Logic: '<S137>/AND2' incorporates:
//   *  Logic: '<S137>/NOT1'
//   *  Logic: '<S137>/NOT2'
//   */
//  rtb_AND2 = ((!rtb_Equal2) && (!rtb_Equal1));
//
//  /* DeadZone: '<S39>/DeadZone' */
//  if (rtb_ProportionalGain > 10.0) {
//    rtb_SignPreSat_o = rtb_ProportionalGain - 10.0;
//  } else if (rtb_ProportionalGain >= -10.0) {
//    rtb_SignPreSat_o = 0.0;
//  } else {
//    rtb_SignPreSat_o = rtb_ProportionalGain - -10.0;
//  }
//
//  /* End of DeadZone: '<S39>/DeadZone' */
//
//  /* RelationalOperator: '<S37>/NotEqual' incorporates:
//   *  Gain: '<S37>/ZeroGain'
//   */
//  rtb_NotEqual_a = (0.0 != rtb_SignPreSat_o);
//
//  /* Signum: '<S37>/SignPreSat' */
//  if (rtb_SignPreSat_o < 0.0) {
//    rtb_SignPreSat_o = -1.0;
//  } else {
//    if (rtb_SignPreSat_o > 0.0) {
//      rtb_SignPreSat_o = 1.0;
//    }
//  }
//
//  /* End of Signum: '<S37>/SignPreSat' */
//
//  /* Gain: '<S43>/Integral Gain' */
//  rtb_ProportionalGain = 1.0 / Tnn * rtb_ProportionalGain_tmp;
//
//  /* DataTypeConversion: '<S37>/DataTypeConv1' */
//  a_tmp = fmod(rtb_SignPreSat_o, 256.0);
//
//  /* Signum: '<S37>/SignPreIntegrator' */
//  if (rtb_ProportionalGain < 0.0) {
//    rtb_ProportionalGain_tmp = -1.0;
//  } else if (rtb_ProportionalGain > 0.0) {
//    rtb_ProportionalGain_tmp = 1.0;
//  } else {
//    rtb_ProportionalGain_tmp = rtb_ProportionalGain;
//  }
//
//  /* End of Signum: '<S37>/SignPreIntegrator' */
//
//  /* DataTypeConversion: '<S37>/DataTypeConv2' */
//  rtb_SignPreSat_o = fmod(rtb_ProportionalGain_tmp, 256.0);
//
//  /* RelationalOperator: '<S37>/Equal1' incorporates:
//   *  DataTypeConversion: '<S37>/DataTypeConv1'
//   *  DataTypeConversion: '<S37>/DataTypeConv2'
//   */
//  rtb_Equal1 = ((a_tmp < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-a_tmp :
//                 (int32_T)(int8_T)(uint8_T)a_tmp) == (rtb_SignPreSat_o < 0.0 ?
//    (int32_T)(int8_T)-(int8_T)(uint8_T)-rtb_SignPreSat_o : (int32_T)(int8_T)
//    (uint8_T)rtb_SignPreSat_o));
//
//  /* Signum: '<S37>/SignP' incorporates:
//   *  Constant: '<S50>/P Copy'
//   */
//  if (Kpn < 0.0) {
//    a_tmp = -1.0;
//  } else if (Kpn > 0.0) {
//    a_tmp = 1.0;
//  } else {
//    a_tmp = Kpn;
//  }
//
//  /* End of Signum: '<S37>/SignP' */
//
//  /* DataTypeConversion: '<S37>/DataTypeConv4' */
//  a_tmp = fmod(a_tmp, 256.0);
//
//  /* RelationalOperator: '<S37>/Equal2' incorporates:
//   *  Constant: '<S37>/Constant'
//   *  DataTypeConversion: '<S37>/DataTypeConv4'
//   */
//  rtb_Equal2 = ((a_tmp < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-a_tmp :
//                 (int32_T)(int8_T)(uint8_T)a_tmp) == 1);
//
//  /* Logic: '<S37>/AND1' */
//  rtb_AND1_b = (rtb_Equal1 && rtb_Equal2);
//
//  /* Logic: '<S37>/AND2' incorporates:
//   *  Logic: '<S37>/NOT1'
//   *  Logic: '<S37>/NOT2'
//   */
//  rtb_AND2_g = ((!rtb_Equal1) && (!rtb_Equal2));
//
//  /* DeadZone: '<S89>/DeadZone' */
//  if (rtb_SignPreSat > 12.0) {
//    rtb_SignPreSat -= 12.0;
//  } else if (rtb_SignPreSat >= -12.0) {
//    rtb_SignPreSat = 0.0;
//  } else {
//    rtb_SignPreSat -= -12.0;
//  }
//
//  /* End of DeadZone: '<S89>/DeadZone' */
//
//  /* RelationalOperator: '<S87>/NotEqual' */
//  rtb_NotEqual_g = (0.0 != rtb_SignPreSat);
//
//  /* Signum: '<S87>/SignPreSat' */
//  if (rtb_SignPreSat < 0.0) {
//    rtb_SignPreSat = -1.0;
//  } else {
//    if (rtb_SignPreSat > 0.0) {
//      rtb_SignPreSat = 1.0;
//    }
//  }
//
//  /* End of Signum: '<S87>/SignPreSat' */
//
//  /* Gain: '<S93>/Integral Gain' */
//  rtb_IntegralGain *= 1.0 / Tnd;
//
//  /* DataTypeConversion: '<S87>/DataTypeConv1' */
//  a_tmp = fmod(rtb_SignPreSat, 256.0);
//
//  /* Signum: '<S87>/SignPreIntegrator' */
//  if (rtb_IntegralGain < 0.0) {
//    rtb_SignPreSat = -1.0;
//  } else if (rtb_IntegralGain > 0.0) {
//    rtb_SignPreSat = 1.0;
//  } else {
//    rtb_SignPreSat = rtb_IntegralGain;
//  }
//
//  /* End of Signum: '<S87>/SignPreIntegrator' */
//
//  /* DataTypeConversion: '<S87>/DataTypeConv2' */
//  rtb_SignPreSat_o = fmod(rtb_SignPreSat, 256.0);
//
//  /* RelationalOperator: '<S87>/Equal1' incorporates:
//   *  DataTypeConversion: '<S87>/DataTypeConv1'
//   *  DataTypeConversion: '<S87>/DataTypeConv2'
//   */
//  rtb_Equal1 = ((a_tmp < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-a_tmp :
//                 (int32_T)(int8_T)(uint8_T)a_tmp) == (rtb_SignPreSat_o < 0.0 ?
//    (int32_T)(int8_T)-(int8_T)(uint8_T)-rtb_SignPreSat_o : (int32_T)(int8_T)
//    (uint8_T)rtb_SignPreSat_o));
//
//  /* Signum: '<S87>/SignP' incorporates:
//   *  Constant: '<S100>/P Copy'
//   */
//  if (Kpd < 0.0) {
//    a_tmp = -1.0;
//  } else if (Kpd > 0.0) {
//    a_tmp = 1.0;
//  } else {
//    a_tmp = Kpd;
//  }
//
//  /* End of Signum: '<S87>/SignP' */
//
//  /* DataTypeConversion: '<S87>/DataTypeConv4' */
//  a_tmp = fmod(a_tmp, 256.0);
//
//  /* RelationalOperator: '<S87>/Equal2' incorporates:
//   *  Constant: '<S87>/Constant'
//   *  DataTypeConversion: '<S87>/DataTypeConv4'
//   */
//  rtb_Equal2 = ((a_tmp < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-a_tmp :
//                 (int32_T)(int8_T)(uint8_T)a_tmp) == 1);
//
//  /* Switch: '<S87>/Switch' incorporates:
//   *  Constant: '<S87>/Constant1'
//   *  Logic: '<S87>/AND1'
//   *  Logic: '<S87>/AND2'
//   *  Logic: '<S87>/AND3'
//   *  Logic: '<S87>/NOT1'
//   *  Logic: '<S87>/NOT2'
//   *  Logic: '<S87>/OR1'
//   */
//  if (rtb_NotEqual_g && ((rtb_Equal1 && rtb_Equal2) || ((!rtb_Equal1) &&
//        (!rtb_Equal2)))) {
//    rtb_IntegralGain = 0.0;
//  }
//
//  /* End of Switch: '<S87>/Switch' */
//
//  /* Update for DiscreteIntegrator: '<S96>/Integrator' */
//  rtDW->Integrator_DSTATE += 5.0E-5 * rtb_IntegralGain;
//  rtDW->Integrator_PrevResetState = 0;
//
//  /* Switch: '<S37>/Switch' incorporates:
//   *  Constant: '<S37>/Constant1'
//   *  Logic: '<S37>/AND3'
//   *  Logic: '<S37>/OR1'
//   */
//  if (rtb_NotEqual_a && (rtb_AND1_b || rtb_AND2_g)) {
//    rtb_ProportionalGain = 0.0;
//  }
//
//  /* End of Switch: '<S37>/Switch' */
//
//  /* Update for DiscreteIntegrator: '<S46>/Integrator' */
//  rtDW->Integrator_DSTATE_a += 5.0E-5 * rtb_ProportionalGain;
//
//  /* Switch: '<S137>/Switch' incorporates:
//   *  Constant: '<S137>/Constant1'
//   *  Logic: '<S137>/AND3'
//   *  Logic: '<S137>/OR1'
//   */
//  if (rtb_NotEqual && (rtb_AND1 || rtb_AND2)) {
//    rtb_Integrator_j = 0.0;
//  }
//
//  /* End of Switch: '<S137>/Switch' */
//
//  /* Update for DiscreteIntegrator: '<S146>/Integrator' */
//  rtDW->Integrator_DSTATE_k += 5.0E-5 * rtb_Integrator_j;
//  rtDW->Integrator_PrevResetState_c = 0;
//}
//
///* Model initialize function */
//void FOC0_initialize(RT_MODEL *const rtM)
//{
//  DW *rtDW = rtM->dwork;
//  B *rtB = rtM->blockIO;
//  ExtU *rtU = (ExtU *) rtM->inputs;
//  ExtY *rtY = (ExtY *) rtM->outputs;
//
//  /* Registration code */
//
//  /* block I/O */
//  (void) memset(((void *) rtB), 0,
//                sizeof(B));
//
//  /* states (dwork) */
//  (void) memset((void *)rtDW, 0,
//                sizeof(DW));
//
//  /* external inputs */
//  (void)memset(rtU, 0, sizeof(ExtU));
//
//  /* external outputs */
//  (void) memset((void *)rtY, 0,
//                sizeof(ExtY));
//
//  /* InitializeConditions for DiscreteIntegrator: '<S96>/Integrator' */
//  rtDW->Integrator_PrevResetState = 2;
//
//  /* InitializeConditions for DiscreteIntegrator: '<S146>/Integrator' */
//  rtDW->Integrator_PrevResetState_c = 2;
//}
//
///* Model terminate function */
//void FOC0_terminate(RT_MODEL *const rtM)
//{
//  /* (no terminate code required) */
//  UNUSED_PARAMETER(rtM);
//}
//
///*
// * File trailer for generated code.
// *
// * [EOF]
// */
