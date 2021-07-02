/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Basic_FOC.c
 *
 * Code generated for Simulink model 'Basic_FOC'.
 *
 * Model version                  : 2.28
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Fri Jul  2 16:27:32 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */

#include "Basic_FOC.h"

/* Named constants for Chart: '<Root>/Basic_FOC' */
#define IN_CurrentControl              ((uint8_T)1U)
#define IN_InProcess                   ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_SpeedControl                ((uint8_T)2U)
#define IN_Start                       ((uint8_T)2U)

static void CurrentController_Init(DW_CurrentController *localDW);
static void CurrentController_Enable(DW_CurrentController *localDW);
static void CurrentController(RT_MODEL * const rtM, real_T rtu_ia, real_T rtu_ib,
  real_T rtu_ic, real_T rtu_w_el, real_T rtu_flg_PreCtrl, real_T rtu_theta_el,
  real_T rtu_U_IC, real_T rtu_id_ref, real_T rtu_iq_ref, real_T
  rtu_flg_LimitUdUq, real_T *rty_ua, real_T *rty_ub, real_T *rty_uc, real_T
  rty_Iq_ist[2], real_T *rty_Id_ist, real_T *rty_ud_soll, real_T *rty_uq_soll,
  DW_CurrentController *localDW);
static void SpeedController_Init(DW_SpeedController *localDW);
static void SpeedController_Enable(DW_SpeedController *localDW);
static void SpeedController(RT_MODEL * const rtM, real_T rtu_id_ref, real_T
  rtu_iq_ref, real_T rtu_n_soll, real_T rtu_n_ist, real_T rtu_flg_fieldWeakening,
  real_T rtu_flg_UseMMPA, real_T rtu_flg_SpeedControl, real_T *rty_id_soll,
  real_T *rty_iq_soll, DW_SpeedController *localDW);

/* Forward declaration for local functions */
static void enter_atomic_SpeedControl(real_T *id_ref_h, real_T *iq_ref_e, real_T
  *n_soll, real_T *n_ist, real_T *flg_fieldWeakening, real_T *flg_UseMMPA, ExtU *
  rtU, ExtY *rtY, RT_MODEL *rtM, DW *rtDW);

/* System initialize for function-call system: '<S1>/CurrentController' */
static void CurrentController_Init(DW_CurrentController *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S45>/Integrator' */
  localDW->Integrator_PREV_U = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_PREV_U_f = 0.0;
}

/* Enable for function-call system: '<S1>/CurrentController' */
static void CurrentController_Enable(DW_CurrentController *localDW)
{
  localDW->CurrentController_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S45>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 1U;

  /* Enable for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE_n = 1U;
}

/* Output and update for function-call system: '<S1>/CurrentController' */
static void CurrentController(RT_MODEL * const rtM, real_T rtu_ia, real_T rtu_ib,
  real_T rtu_ic, real_T rtu_w_el, real_T rtu_flg_PreCtrl, real_T rtu_theta_el,
  real_T rtu_U_IC, real_T rtu_id_ref, real_T rtu_iq_ref, real_T
  rtu_flg_LimitUdUq, real_T *rty_ua, real_T *rty_ub, real_T *rty_uc, real_T
  rty_Iq_ist[2], real_T *rty_Id_ist, real_T *rty_ud_soll, real_T *rty_uq_soll,
  DW_CurrentController *localDW)
{
  real_T Integrator;
  real_T a_tmp;
  real_T rtb_SignPreSat_d;
  real_T rtb_Switch2;
  real_T rtb_Switch_idx_0;
  real_T rtb_Switch_idx_1;
  int32_T quadrant;
  int32_T sector;
  uint32_T CurrentController_ELAPS_T;
  if (localDW->CurrentController_RESET_ELAPS_T) {
    CurrentController_ELAPS_T = 0U;
  } else {
    CurrentController_ELAPS_T = rtM->Timing.clockTick0 -
      localDW->CurrentController_PREV_T;
  }

  localDW->CurrentController_PREV_T = rtM->Timing.clockTick0;
  localDW->CurrentController_RESET_ELAPS_T = false;
  for (quadrant = 0; quadrant < 3; quadrant++) {
    /* Gain: '<S116>/Gain1' incorporates:
     *  Gain: '<S116>/Gain3'
     *  SignalConversion generated from: '<S116>/Gain3'
     */
    localDW->Gain1[quadrant] = 0.66666666666666663 *
      (rtConstP.Gain3_Gain[quadrant + 6] * rtu_ic +
       (rtConstP.Gain3_Gain[quadrant + 3] * rtu_ib +
        rtConstP.Gain3_Gain[quadrant] * rtu_ia));
  }

  /* Outputs for Enabled SubSystem: '<S122>/Subsystem1' incorporates:
   *  EnablePort: '<S126>/Enable'
   */
  /* Outputs for Enabled SubSystem: '<S115>/Subsystem1' incorporates:
   *  EnablePort: '<S120>/Enable'
   */
  /* Fcn: '<S120>/Fcn' incorporates:
   *  Fcn: '<S120>/Fcn1'
   *  Fcn: '<S126>/Fcn'
   *  Fcn: '<S126>/Fcn1'
   */
  rtb_Switch_idx_1 = sin(rtu_theta_el);
  localDW->c = cos(rtu_theta_el);

  /* End of Outputs for SubSystem: '<S122>/Subsystem1' */

  /* Switch: '<S115>/Switch' incorporates:
   *  Fcn: '<S120>/Fcn'
   *  Fcn: '<S120>/Fcn1'
   */
  rty_Iq_ist[0] = localDW->Gain1[0] * localDW->c + localDW->Gain1[1] *
    rtb_Switch_idx_1;
  rty_Iq_ist[1] = -localDW->Gain1[0] * rtb_Switch_idx_1 + localDW->Gain1[1] *
    localDW->c;

  /* End of Outputs for SubSystem: '<S115>/Subsystem1' */

  /* Sum: '<S7>/Subtract' */
  localDW->IntegralGain = rtu_id_ref - rty_Iq_ist[0];

  /* DiscreteIntegrator: '<S45>/Integrator' */
  if (localDW->Integrator_SYSTEM_ENABLE != 0) {
    /* DiscreteIntegrator: '<S45>/Integrator' */
    Integrator = localDW->Integrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S45>/Integrator' */
    Integrator = 0.002 * (real_T)CurrentController_ELAPS_T
      * localDW->Integrator_PREV_U + localDW->Integrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S45>/Integrator' */

  /* Gain: '<S43>/Proportional Gain' incorporates:
   *  Sum: '<S54>/Sum'
   */
  localDW->SignPreSat = (localDW->IntegralGain + Integrator) *
    0.040212385965949352;

  /* Saturate: '<S52>/Saturation' */
  if (localDW->SignPreSat > 26.558112382722786) {
    localDW->Gain = 26.558112382722786;
  } else if (localDW->SignPreSat < -26.558112382722786) {
    localDW->Gain = -26.558112382722786;
  } else {
    localDW->Gain = localDW->SignPreSat;
  }

  /* End of Saturate: '<S52>/Saturation' */

  /* Switch: '<S4>/Switch1' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S6>/Gain1'
   *  Product: '<S6>/Product'
   */
  if (rtu_flg_PreCtrl > 0.0) {
    rtb_Switch_idx_0 = -1.6E-5 * rtu_iq_ref * rtu_w_el;
  } else {
    rtb_Switch_idx_0 = 0.0;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Sum: '<S4>/Add' */
  localDW->UdV = localDW->Gain + rtb_Switch_idx_0;

  /* Gain: '<S9>/Gain' */
  localDW->Gain = 0.5774 * rtu_U_IC;

  /* Switch: '<S113>/Switch2' incorporates:
   *  Gain: '<S9>/Gain1'
   *  RelationalOperator: '<S113>/LowerRelop1'
   *  RelationalOperator: '<S113>/UpperRelop'
   *  Switch: '<S113>/Switch'
   */
  if (localDW->UdV > localDW->Gain) {
    rtb_Switch2 = localDW->Gain;
  } else if (localDW->UdV < -localDW->Gain) {
    /* Switch: '<S113>/Switch' incorporates:
     *  Gain: '<S9>/Gain1'
     */
    rtb_Switch2 = -localDW->Gain;
  } else {
    rtb_Switch2 = localDW->UdV;
  }

  /* End of Switch: '<S113>/Switch2' */

  /* Switch: '<S4>/Switch2' */
  if (rtu_flg_LimitUdUq > 0.0) {
    *rty_ud_soll = rtb_Switch2;
  } else {
    *rty_ud_soll = localDW->UdV;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Sum: '<S8>/Subtract' */
  localDW->UdV = rtu_iq_ref - rty_Iq_ist[1];

  /* DiscreteIntegrator: '<S96>/Integrator' */
  if (localDW->Integrator_SYSTEM_ENABLE_n != 0) {
    /* DiscreteIntegrator: '<S96>/Integrator' */
    localDW->Gain1_p = localDW->Integrator_DSTATE_j;
  } else {
    /* DiscreteIntegrator: '<S96>/Integrator' */
    localDW->Gain1_p = 0.002 * (real_T)CurrentController_ELAPS_T
      * localDW->Integrator_PREV_U_f + localDW->Integrator_DSTATE_j;
  }

  /* End of DiscreteIntegrator: '<S96>/Integrator' */

  /* Gain: '<S94>/Proportional Gain' incorporates:
   *  Sum: '<S105>/Sum'
   */
  rtb_SignPreSat_d = (localDW->UdV + localDW->Gain1_p) * 0.040212385965949352;

  /* Switch: '<S4>/Switch' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S6>/Gain2'
   *  Product: '<S6>/Product1'
   *  Sum: '<S6>/Add'
   */
  if (rtu_flg_PreCtrl > 0.0) {
    rtb_Switch_idx_0 = (1.6E-5 * rtu_id_ref + 0.0048) * rtu_w_el;
  } else {
    rtb_Switch_idx_0 = 0.0;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Saturate: '<S103>/Saturation' */
  if (rtb_SignPreSat_d > 26.558112382722786) {
    localDW->Switch_ls = 26.558112382722786;
  } else if (rtb_SignPreSat_d < -26.558112382722786) {
    localDW->Switch_ls = -26.558112382722786;
  } else {
    localDW->Switch_ls = rtb_SignPreSat_d;
  }

  /* End of Saturate: '<S103>/Saturation' */

  /* Sum: '<S4>/Add1' */
  localDW->Switch_ls += rtb_Switch_idx_0;

  /* Switch: '<S4>/Switch3' */
  if (rtu_flg_LimitUdUq > 0.0) {
    /* Sqrt: '<S9>/Sqrt' incorporates:
     *  Math: '<S9>/Square'
     *  Math: '<S9>/Square1'
     *  Sum: '<S9>/Add'
     */
    localDW->Gain = sqrt(localDW->Gain * localDW->Gain - rtb_Switch2 *
                         rtb_Switch2);

    /* Switch: '<S114>/Switch2' incorporates:
     *  Gain: '<S9>/Gain2'
     *  RelationalOperator: '<S114>/LowerRelop1'
     *  RelationalOperator: '<S114>/UpperRelop'
     *  Switch: '<S114>/Switch'
     */
    if (localDW->Switch_ls > localDW->Gain) {
      *rty_uq_soll = localDW->Gain;
    } else if (localDW->Switch_ls < -localDW->Gain) {
      /* Switch: '<S114>/Switch' incorporates:
       *  Gain: '<S9>/Gain2'
       */
      *rty_uq_soll = -localDW->Gain;
    } else {
      *rty_uq_soll = localDW->Switch_ls;
    }

    /* End of Switch: '<S114>/Switch2' */
  } else {
    *rty_uq_soll = localDW->Switch_ls;
  }

  /* End of Switch: '<S4>/Switch3' */

  /* Outputs for Enabled SubSystem: '<S122>/Subsystem1' incorporates:
   *  EnablePort: '<S126>/Enable'
   */
  /* Switch: '<S122>/Switch' incorporates:
   *  Fcn: '<S126>/Fcn'
   *  Fcn: '<S126>/Fcn1'
   */
  rtb_Switch_idx_0 = *rty_ud_soll * localDW->c - *rty_uq_soll * rtb_Switch_idx_1;
  rtb_Switch_idx_1 = *rty_ud_soll * rtb_Switch_idx_1 + *rty_uq_soll * localDW->c;

  /* End of Outputs for SubSystem: '<S122>/Subsystem1' */

  /* MATLAB Function: '<S5>/SpaceVectorModulation' */
  /* MATLAB Function 'Basic_FOC/CurrentController/SpaceVectorModulation/SpaceVectorModulation': '<S121>:1' */
  /* '<S121>:1:3' a_U_on=0; */
  rtb_Switch2 = 0.0;

  /* '<S121>:1:4' a_V_on=0; */
  localDW->Gain = 0.0;

  /* '<S121>:1:5' a_W_on=0; */
  localDW->Switch_ls = 0.0;

  /* __%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%_ */
  /* Tr‰gerbasierte Raumzeigermodulation%% */
  /* Eing‰nge: */
  /* U_ZK       -- Zwischenkreisspannung */
  /* u_alpha    -- alphakomponente des Sollspannungsraumzeigers */
  /* u_beta     -- betakomponente des Sollspannungsraumzeigers */
  /* CMP_Period_max_val  -- maximalwert des Dreiecks/S‰gezahnz‰hlers zum Gewichten der Aussteuergrade */
  /* Ausg‰nge: */
  /* CMP_U        -- Vergleichswert U */
  /* CMP_V        -- Vergleichswert V */
  /* CMP_W        -- Vergleichswert W */
  /* sector       -- Ausgabe des Sektors des Spannungszeigers */
  /* Berechnung von a, b, c nach Quang Dittrich S24 */
  /* '<S121>:1:23' a = abs(u_alpha) + 0.5774*abs(u_beta); */
  a_tmp = fabs(rtb_Switch_idx_0);
  localDW->c = fabs(rtb_Switch_idx_1);
  localDW->a = 0.5774 * localDW->c + a_tmp;

  /* '<S121>:1:24' b = abs(u_alpha) - 0.5774*abs(u_beta); */
  localDW->b = a_tmp - 0.5774 * fabs(rtb_Switch_idx_1);

  /* '<S121>:1:25' c = 1.1547*abs(u_beta); */
  localDW->c *= 1.1547;

  /* '<S121>:1:27' U_max = 0.6667 * U_ZK; */
  localDW->U_max = 0.6667 * rtu_U_IC;

  /* Maximum Voltage U_ZL/sqrt(3) */
  /* Sektor und Quadranten nach Quang Dittrich S32 */
  /* '<S121>:1:31' if(u_beta < 0) */
  if (rtb_Switch_idx_1 < 0.0) {
    /* '<S121>:1:32' if (u_alpha <0) */
    if (rtb_Switch_idx_0 < 0.0) {
      /* '<S121>:1:33' quadrant=3; */
      quadrant = 3;

      /* '<S121>:1:34' if(b < 0) */
      if (localDW->b < 0.0) {
        /* '<S121>:1:35' sector = 5; */
        sector = 5;
      } else {
        /* '<S121>:1:36' else */
        /* '<S121>:1:37' sector = 4; */
        sector = 4;
      }
    } else {
      /* '<S121>:1:39' else */
      /* '<S121>:1:40' quadrant=4; */
      quadrant = 4;

      /* '<S121>:1:41' if(b < 0) */
      if (localDW->b < 0.0) {
        /* '<S121>:1:42' sector = 5; */
        sector = 5;
      } else {
        /* '<S121>:1:43' else */
        /* '<S121>:1:44' sector = 6; */
        sector = 6;
      }
    }

    /* '<S121>:1:48' else */
    /* '<S121>:1:49' if (u_alpha <0) */
  } else if (rtb_Switch_idx_0 < 0.0) {
    /* '<S121>:1:50' quadrant=2; */
    quadrant = 2;

    /* '<S121>:1:51' if(b < 0) */
    if (localDW->b < 0.0) {
      /* '<S121>:1:52' sector = 2; */
      sector = 2;
    } else {
      /* '<S121>:1:53' else */
      /* '<S121>:1:54' sector = 3; */
      sector = 3;
    }
  } else {
    /* '<S121>:1:56' else */
    /* '<S121>:1:57' quadrant=1; */
    quadrant = 1;

    /* '<S121>:1:58' if(b < 0) */
    if (localDW->b < 0.0) {
      /* '<S121>:1:59' sector = 2; */
      sector = 2;
    } else {
      /* '<S121>:1:60' else */
      /* '<S121>:1:61' sector = 1; */
      sector = 1;
    }
  }

  /* '<S121>:1:66' sector = sector; */
  /* Modulationsfunktionen f¸r Phasen U,V,W */
  /* Erzeugung der Aussteuergrade f¸r die Halbbr¸cken */
  /* --> Erzeugung einer "regulary Sampled SVM" erfolgt anschlieﬂend durch Abtastung */
  /* mit Dreiecksz‰hlern in Hardware. */
  /* '<S121>:1:73' if (sector == 1) */
  if (sector == 1) {
    /* Quang S.24 and normed to 2/3 U_DC */
    /* '<S121>:1:76' u1 = b/(U_max); */
    localDW->Switch_ls = localDW->b / localDW->U_max;

    /* '<S121>:1:77' u2 = c/(U_max); */
    localDW->u2 = localDW->c / localDW->U_max;

    /* Quang S.34 */
    /* '<S121>:1:80' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
    rtb_Switch2 = (localDW->Switch_ls * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S121>:1:81' a_V_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->Gain = (0.5 - localDW->Switch_ls * 0.5) + localDW->u2 * 0.5;

    /* '<S121>:1:82' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Switch_ls = (0.5 - localDW->Switch_ls * 0.5) - localDW->u2 * 0.5;
  }

  /* '<S121>:1:86' if ((sector == 2) && (quadrant == 1)) */
  if ((sector == 2) && (quadrant == 1)) {
    /* '<S121>:1:88' u1 = a/(U_max); */
    localDW->Switch_ls = localDW->a / localDW->U_max;

    /* '<S121>:1:89' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->u2 = (0.5774 * fabs(rtb_Switch_idx_1) + -a_tmp) / localDW->U_max;

    /* '<S121>:1:91' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
    rtb_Switch2 = (localDW->Switch_ls * 0.5 + 0.5) - localDW->u2 * 0.5;

    /* '<S121>:1:92' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Gain = (localDW->Switch_ls * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S121>:1:93' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Switch_ls = (0.5 - localDW->Switch_ls * 0.5) - localDW->u2 * 0.5;
  }

  /* '<S121>:1:97' if ((sector == 2) && (quadrant == 2)) */
  if ((sector == 2) && (quadrant == 2)) {
    /* '<S121>:1:99' u1 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->Switch_ls = (0.5774 * fabs(rtb_Switch_idx_1) + -fabs
                          (rtb_Switch_idx_0)) / localDW->U_max;

    /* '<S121>:1:100' u2 = a/(U_max); */
    localDW->u2 = localDW->a / localDW->U_max;

    /* '<S121>:1:102' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
    rtb_Switch2 = (localDW->Switch_ls * 0.5 + 0.5) - localDW->u2 * 0.5;

    /* '<S121>:1:103' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Gain = (localDW->Switch_ls * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S121>:1:104' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Switch_ls = (0.5 - localDW->Switch_ls * 0.5) - localDW->u2 * 0.5;
  }

  /* '<S121>:1:108' if (sector == 3) */
  if (sector == 3) {
    /* '<S121>:1:110' u1 = c/(U_max); */
    localDW->Switch_ls = localDW->c / localDW->U_max;

    /* '<S121>:1:111' u2 = b/(U_max); */
    localDW->u2 = localDW->b / localDW->U_max;

    /* '<S121>:1:113' a_U_on=  0.5 - u1*0.5 - u2*0.5; */
    rtb_Switch2 = (0.5 - localDW->Switch_ls * 0.5) - localDW->u2 * 0.5;

    /* '<S121>:1:114' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Gain = (localDW->Switch_ls * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S121>:1:115' a_W_on = 0.5 - u1*0.5 + u2*0.5; */
    localDW->Switch_ls = (0.5 - localDW->Switch_ls * 0.5) + localDW->u2 * 0.5;
  }

  /* '<S121>:1:118' if (sector == 4) */
  if (sector == 4) {
    /* '<S121>:1:120' u1 = b/(U_max); */
    localDW->Switch_ls = localDW->b / localDW->U_max;

    /* '<S121>:1:121' u2 = c/(U_max); */
    localDW->u2 = localDW->c / localDW->U_max;

    /* '<S121>:1:123' a_U_on = 0.5 - u1*0.5 - u2*0.5; */
    rtb_Switch2 = (0.5 - localDW->Switch_ls * 0.5) - localDW->u2 * 0.5;

    /* '<S121>:1:124' a_V_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->Switch_ls = localDW->Switch_ls * 0.5 + 0.5;
    localDW->Gain = localDW->Switch_ls - localDW->u2 * 0.5;

    /* '<S121>:1:125' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Switch_ls += localDW->u2 * 0.5;
  }

  /* '<S121>:1:129' if ((sector == 5) && (quadrant == 3)) */
  if ((sector == 5) && (quadrant == 3)) {
    /* '<S121>:1:131' u1 = a/(U_max); */
    localDW->Switch_ls = localDW->a / localDW->U_max;

    /* '<S121>:1:132' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->u2 = (0.5774 * fabs(rtb_Switch_idx_1) + -fabs(rtb_Switch_idx_0)) /
      localDW->U_max;

    /* '<S121>:1:134' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
    rtb_Switch2 = (0.5 - localDW->Switch_ls * 0.5) + localDW->u2 * 0.5;

    /* '<S121>:1:135' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Gain = (0.5 - localDW->Switch_ls * 0.5) - localDW->u2 * 0.5;

    /* '<S121>:1:136' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Switch_ls = (localDW->Switch_ls * 0.5 + 0.5) + localDW->u2 * 0.5;
  }

  /* '<S121>:1:140' if ((sector == 5) && (quadrant == 4)) */
  if ((sector == 5) && (quadrant == 4)) {
    /* '<S121>:1:142' u1 =(-abs(u_alpha) + 0.5774*abs(u_beta))/(U_max); */
    localDW->Switch_ls = (0.5774 * fabs(rtb_Switch_idx_1) + -fabs
                          (rtb_Switch_idx_0)) / localDW->U_max;

    /* '<S121>:1:143' u2 =  a/(U_max); */
    localDW->u2 = localDW->a / localDW->U_max;

    /* '<S121>:1:145' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
    rtb_Switch2 = (0.5 - localDW->Switch_ls * 0.5) + localDW->u2 * 0.5;

    /* '<S121>:1:146' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Gain = (0.5 - localDW->Switch_ls * 0.5) - localDW->u2 * 0.5;

    /* '<S121>:1:147' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    localDW->Switch_ls = (localDW->Switch_ls * 0.5 + 0.5) + localDW->u2 * 0.5;
  }

  /* '<S121>:1:151' if (sector == 6) */
  if (sector == 6) {
    /* '<S121>:1:153' u1 = c/(U_max); */
    localDW->Switch_ls = localDW->c / localDW->U_max;

    /* '<S121>:1:154' u2 = b/(U_max); */
    localDW->u2 = localDW->b / localDW->U_max;

    /* '<S121>:1:156' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
    rtb_Switch2 = (localDW->Switch_ls * 0.5 + 0.5) + localDW->u2 * 0.5;

    /* '<S121>:1:157' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    localDW->Gain = (0.5 - localDW->Switch_ls * 0.5) - localDW->u2 * 0.5;

    /* '<S121>:1:158' a_W_on = 0.5 + u1*0.5 - u2*0.5; */
    localDW->Switch_ls = (localDW->Switch_ls * 0.5 + 0.5) - localDW->u2 * 0.5;
  }

  /* '<S121>:1:161' if a_U_on > 1.0 */
  if (rtb_Switch2 > 1.0) {
    /* '<S121>:1:162' a_U_on = 1.0; */
    rtb_Switch2 = 1.0;
  }

  /* '<S121>:1:164' if a_V_on > 1.0 */
  if (localDW->Gain > 1.0) {
    /* '<S121>:1:165' a_V_on = 1.0; */
    localDW->Gain = 1.0;
  }

  /* '<S121>:1:167' if a_W_on > 1.0 */
  if (localDW->Switch_ls > 1.0) {
    /* '<S121>:1:168' a_W_on = 1.0; */
    localDW->Switch_ls = 1.0;
  }

  /* '<S121>:1:171' u_a = a_U_on; */
  *rty_ua = rtb_Switch2;

  /* '<S121>:1:172' u_b = a_V_on; */
  *rty_ub = localDW->Gain;

  /* '<S121>:1:173' u_c = a_W_on; */
  *rty_uc = localDW->Switch_ls;

  /* End of MATLAB Function: '<S5>/SpaceVectorModulation' */

  /* DeadZone: '<S89>/DeadZone' */
  if (rtb_SignPreSat_d > 26.558112382722786) {
    rtb_SignPreSat_d -= 26.558112382722786;
  } else if (rtb_SignPreSat_d >= -26.558112382722786) {
    rtb_SignPreSat_d = 0.0;
  } else {
    rtb_SignPreSat_d -= -26.558112382722786;
  }

  /* End of DeadZone: '<S89>/DeadZone' */

  /* Gain: '<S93>/Integral Gain' */
  localDW->UdV *= 2500.0;

  /* DeadZone: '<S38>/DeadZone' */
  if (localDW->SignPreSat > 26.558112382722786) {
    localDW->SignPreSat -= 26.558112382722786;
  } else if (localDW->SignPreSat >= -26.558112382722786) {
    localDW->SignPreSat = 0.0;
  } else {
    localDW->SignPreSat -= -26.558112382722786;
  }

  /* End of DeadZone: '<S38>/DeadZone' */

  /* Gain: '<S42>/Integral Gain' */
  localDW->IntegralGain *= 2500.0;

  /* SignalConversion generated from: '<S2>/Id_ist' */
  *rty_Id_ist = rty_Iq_ist[0];

  /* Update for DiscreteIntegrator: '<S45>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 0U;
  localDW->Integrator_DSTATE = Integrator;

  /* Signum: '<S36>/SignPreSat' */
  if (localDW->SignPreSat < 0.0) {
    localDW->Gain = -1.0;
  } else if (localDW->SignPreSat > 0.0) {
    localDW->Gain = 1.0;
  } else {
    localDW->Gain = localDW->SignPreSat;
  }

  /* End of Signum: '<S36>/SignPreSat' */

  /* Signum: '<S36>/SignPreIntegrator' */
  if (localDW->IntegralGain < 0.0) {
    Integrator = -1.0;
  } else if (localDW->IntegralGain > 0.0) {
    Integrator = 1.0;
  } else {
    Integrator = localDW->IntegralGain;
  }

  /* End of Signum: '<S36>/SignPreIntegrator' */

  /* Switch: '<S36>/Switch' incorporates:
   *  DataTypeConversion: '<S36>/DataTypeConv1'
   *  DataTypeConversion: '<S36>/DataTypeConv2'
   *  Logic: '<S36>/AND3'
   *  RelationalOperator: '<S36>/Equal1'
   *  RelationalOperator: '<S36>/NotEqual'
   */
  if ((0.0 != localDW->SignPreSat) && ((int8_T)localDW->Gain == (int8_T)
       Integrator)) {
    /* Update for DiscreteIntegrator: '<S45>/Integrator' incorporates:
     *  Constant: '<S36>/Constant1'
     */
    localDW->Integrator_PREV_U = 0.0;
  } else {
    /* Update for DiscreteIntegrator: '<S45>/Integrator' */
    localDW->Integrator_PREV_U = localDW->IntegralGain;
  }

  /* End of Switch: '<S36>/Switch' */

  /* Update for DiscreteIntegrator: '<S96>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE_n = 0U;
  localDW->Integrator_DSTATE_j = localDW->Gain1_p;

  /* Signum: '<S87>/SignPreSat' */
  if (rtb_SignPreSat_d < 0.0) {
    localDW->Switch_ls = -1.0;
  } else if (rtb_SignPreSat_d > 0.0) {
    localDW->Switch_ls = 1.0;
  } else {
    localDW->Switch_ls = rtb_SignPreSat_d;
  }

  /* End of Signum: '<S87>/SignPreSat' */

  /* Signum: '<S87>/SignPreIntegrator' */
  if (localDW->UdV < 0.0) {
    localDW->IntegralGain = -1.0;
  } else if (localDW->UdV > 0.0) {
    localDW->IntegralGain = 1.0;
  } else {
    localDW->IntegralGain = localDW->UdV;
  }

  /* End of Signum: '<S87>/SignPreIntegrator' */

  /* Switch: '<S87>/Switch' incorporates:
   *  DataTypeConversion: '<S87>/DataTypeConv1'
   *  DataTypeConversion: '<S87>/DataTypeConv2'
   *  Logic: '<S87>/AND3'
   *  RelationalOperator: '<S87>/Equal1'
   *  RelationalOperator: '<S87>/NotEqual'
   */
  if ((0.0 != rtb_SignPreSat_d) && ((int8_T)localDW->Switch_ls == (int8_T)
       localDW->IntegralGain)) {
    /* Update for DiscreteIntegrator: '<S96>/Integrator' incorporates:
     *  Constant: '<S87>/Constant1'
     */
    localDW->Integrator_PREV_U_f = 0.0;
  } else {
    /* Update for DiscreteIntegrator: '<S96>/Integrator' */
    localDW->Integrator_PREV_U_f = localDW->UdV;
  }

  /* End of Switch: '<S87>/Switch' */
}

/* System initialize for function-call system: '<S1>/SpeedController' */
static void SpeedController_Init(DW_SpeedController *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S163>/Integrator' */
  localDW->Integrator_PREV_U = 0.0;
}

/* Enable for function-call system: '<S1>/SpeedController' */
static void SpeedController_Enable(DW_SpeedController *localDW)
{
  localDW->SpeedController_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S163>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 1U;
}

/* Output and update for function-call system: '<S1>/SpeedController' */
static void SpeedController(RT_MODEL * const rtM, real_T rtu_id_ref, real_T
  rtu_iq_ref, real_T rtu_n_soll, real_T rtu_n_ist, real_T rtu_flg_fieldWeakening,
  real_T rtu_flg_UseMMPA, real_T rtu_flg_SpeedControl, real_T *rty_id_soll,
  real_T *rty_iq_soll, DW_SpeedController *localDW)
{
  real_T Integrator;
  real_T rtb_IntegralGain_e;
  real_T rtb_IntegralGain_p;
  real_T rtb_ProportionalGain;
  uint32_T SpeedController_ELAPS_T;
  if (localDW->SpeedController_RESET_ELAPS_T) {
    SpeedController_ELAPS_T = 0U;
  } else {
    SpeedController_ELAPS_T = rtM->Timing.clockTick0 -
      localDW->SpeedController_PREV_T;
  }

  localDW->SpeedController_PREV_T = rtM->Timing.clockTick0;
  localDW->SpeedController_RESET_ELAPS_T = false;

  /* Switch: '<S127>/Switch' incorporates:
   *  Constant: '<S127>/Constant'
   *  Switch: '<S128>/Switch'
   */
  if (rtu_flg_UseMMPA > 0.0) {
    *rty_id_soll = 0.0;
  } else if (rtu_flg_fieldWeakening > 0.0) {
    /* Switch: '<S128>/Switch' incorporates:
     *  Constant: '<S128>/Constant'
     */
    *rty_id_soll = 0.0;
  } else {
    *rty_id_soll = rtu_id_ref;
  }

  /* End of Switch: '<S127>/Switch' */

  /* Sum: '<S128>/Sum' */
  rtb_IntegralGain_p = rtu_n_soll - rtu_n_ist;

  /* DiscreteIntegrator: '<S163>/Integrator' */
  if (localDW->Integrator_SYSTEM_ENABLE != 0) {
    /* DiscreteIntegrator: '<S163>/Integrator' */
    Integrator = localDW->Integrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S163>/Integrator' */
    Integrator = 0.002 * (real_T)SpeedController_ELAPS_T
      * localDW->Integrator_PREV_U + localDW->Integrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S163>/Integrator' */

  /* Gain: '<S161>/Proportional Gain' incorporates:
   *  Sum: '<S172>/Sum'
   */
  rtb_ProportionalGain = (rtb_IntegralGain_p + Integrator) * 0.72527957092073492;

  /* Switch: '<S127>/Switch1' incorporates:
   *  Constant: '<S127>/Constant'
   *  Switch: '<S128>/Switch1'
   */
  if (rtu_flg_UseMMPA > 0.0) {
    *rty_iq_soll = 0.0;
  } else if (rtu_flg_SpeedControl > 0.0) {
    /* Saturate: '<S170>/Saturation' incorporates:
     *  Switch: '<S128>/Switch1'
     */
    if (rtb_ProportionalGain > 100.0) {
      *rty_iq_soll = 100.0;
    } else if (rtb_ProportionalGain < -100.0) {
      *rty_iq_soll = -100.0;
    } else {
      *rty_iq_soll = rtb_ProportionalGain;
    }

    /* End of Saturate: '<S170>/Saturation' */
  } else {
    /* Switch: '<S128>/Switch1' */
    *rty_iq_soll = rtu_iq_ref;
  }

  /* End of Switch: '<S127>/Switch1' */

  /* DeadZone: '<S156>/DeadZone' */
  if (rtb_ProportionalGain > 100.0) {
    rtb_ProportionalGain -= 100.0;
  } else if (rtb_ProportionalGain >= -100.0) {
    rtb_ProportionalGain = 0.0;
  } else {
    rtb_ProportionalGain -= -100.0;
  }

  /* End of DeadZone: '<S156>/DeadZone' */

  /* Gain: '<S160>/Integral Gain' */
  rtb_IntegralGain_p *= 69.813170079773172;

  /* Update for DiscreteIntegrator: '<S163>/Integrator' */
  localDW->Integrator_SYSTEM_ENABLE = 0U;
  localDW->Integrator_DSTATE = Integrator;

  /* Signum: '<S154>/SignPreSat' */
  if (rtb_ProportionalGain < 0.0) {
    Integrator = -1.0;
  } else if (rtb_ProportionalGain > 0.0) {
    Integrator = 1.0;
  } else {
    Integrator = rtb_ProportionalGain;
  }

  /* End of Signum: '<S154>/SignPreSat' */

  /* Signum: '<S154>/SignPreIntegrator' */
  if (rtb_IntegralGain_p < 0.0) {
    rtb_IntegralGain_e = -1.0;
  } else if (rtb_IntegralGain_p > 0.0) {
    rtb_IntegralGain_e = 1.0;
  } else {
    rtb_IntegralGain_e = rtb_IntegralGain_p;
  }

  /* End of Signum: '<S154>/SignPreIntegrator' */

  /* Switch: '<S154>/Switch' incorporates:
   *  DataTypeConversion: '<S154>/DataTypeConv1'
   *  DataTypeConversion: '<S154>/DataTypeConv2'
   *  Gain: '<S154>/ZeroGain'
   *  Logic: '<S154>/AND3'
   *  RelationalOperator: '<S154>/Equal1'
   *  RelationalOperator: '<S154>/NotEqual'
   */
  if ((0.0 != rtb_ProportionalGain) && ((int8_T)Integrator == (int8_T)
       rtb_IntegralGain_e)) {
    /* Update for DiscreteIntegrator: '<S163>/Integrator' incorporates:
     *  Constant: '<S154>/Constant1'
     */
    localDW->Integrator_PREV_U = 0.0;
  } else {
    /* Update for DiscreteIntegrator: '<S163>/Integrator' */
    localDW->Integrator_PREV_U = rtb_IntegralGain_p;
  }

  /* End of Switch: '<S154>/Switch' */
}

/* Function for Chart: '<Root>/Basic_FOC' */
static void enter_atomic_SpeedControl(real_T *id_ref_h, real_T *iq_ref_e, real_T
  *n_soll, real_T *n_ist, real_T *flg_fieldWeakening, real_T *flg_UseMMPA, ExtU *
  rtU, ExtY *rtY, RT_MODEL *rtM, DW *rtDW)
{
  /* Inport: '<Root>/id_ref' */
  /* Entry 'SpeedControl': '<S1>:90' */
  /* '<S1>:90:3' [id_soll,iq_soll] = SpeedController(id_ref,iq_ref,n_soll,n_ist,flg_fieldWeakening,flg_UseMMPA,flg_SpeedControl) */
  /* Simulink Function 'SpeedController': '<S1>:62' */
  *id_ref_h = rtU->id_ref;

  /* Inport: '<Root>/iq_ref' */
  *iq_ref_e = rtU->iq_ref;

  /* Inport: '<Root>/n_soll' */
  *n_soll = rtU->n_soll;

  /* Inport: '<Root>/n_ist' */
  *n_ist = rtU->n_ist;

  /* Inport: '<Root>/flg_fieldWeakening' */
  *flg_fieldWeakening = rtU->flg_fieldWeakening;

  /* Inport: '<Root>/flg_UseMMPA' */
  *flg_UseMMPA = rtU->flg_UseMMPA;

  /* Inport: '<Root>/flg_SpeedControl' */
  rtDW->flg_SpeedControl = rtU->flg_SpeedControl;

  /* Outputs for Function Call SubSystem: '<S1>/SpeedController' */
  SpeedController(rtM, *id_ref_h, *iq_ref_e, *n_soll, *n_ist,
                  *flg_fieldWeakening, *flg_UseMMPA, rtDW->flg_SpeedControl,
                  &rtDW->Switch, &rtDW->Switch1, &rtDW->SpeedController_j);

  /* End of Outputs for SubSystem: '<S1>/SpeedController' */
  rtDW->id_soll = rtDW->Switch;
  rtDW->iq_soll = rtDW->Switch1;

  /* Inport: '<Root>/ia' */
  /* '<S1>:90:4' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq) */
  /* Simulink Function 'CurrentController': '<S1>:72' */
  rtDW->ia = rtU->ia;

  /* Inport: '<Root>/ib' */
  rtDW->ib = rtU->ib;

  /* Inport: '<Root>/ic' */
  rtDW->ic = rtU->ic;

  /* Inport: '<Root>/w_el' */
  rtDW->w_el = rtU->w_el;

  /* Inport: '<Root>/flg_PreCntr' */
  rtDW->flg_PreCtrl = rtU->flg_PreCntr;

  /* Inport: '<Root>/theta_el' */
  rtDW->theta_el = rtU->theta_el;

  /* Inport: '<Root>/U_IC' */
  rtDW->U_IC = rtU->U_IC;
  rtDW->id_ref = rtDW->id_soll;
  rtDW->iq_ref = rtDW->iq_soll;

  /* Inport: '<Root>/flgLimitUdUq' */
  rtDW->flg_LimitUdUq = rtU->flgLimitUdUq;

  /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
  CurrentController(rtM, rtDW->ia, rtDW->ib, rtDW->ic, rtDW->w_el,
                    rtDW->flg_PreCtrl, rtDW->theta_el, rtDW->U_IC, rtDW->id_ref,
                    rtDW->iq_ref, rtDW->flg_LimitUdUq, &rtDW->u_a, &rtDW->u_b,
                    &rtDW->u_c, rtDW->Switch_j, &rtDW->OutportBufferForId_ist,
                    &rtDW->Switch2, &rtDW->Switch3, &rtDW->CurrentController_f);

  /* End of Outputs for SubSystem: '<S1>/CurrentController' */

  /* Outport: '<Root>/Ua_DutyCycle' */
  rtY->Ua_DutyCycle = rtDW->u_a;

  /* Outport: '<Root>/Ub_DutyCycle' */
  rtY->Ub_DutyCycle = rtDW->u_b;

  /* Outport: '<Root>/Uc_DutyCycle' */
  rtY->Uc_DutyCycle = rtDW->u_c;

  /* Outport: '<Root>/iq_ist' */
  rtY->iq_ist = rtDW->Switch_j[1];

  /* Outport: '<Root>/id_ist' */
  rtY->id_ist = rtDW->OutportBufferForId_ist;

  /* Outport: '<Root>/ud' */
  rtY->ud = rtDW->Switch2;

  /* Outport: '<Root>/uq' */
  rtY->uq = rtDW->Switch3;

  /* '<S1>:90:5' cnt_CurrentCtrl = 1 */
  rtDW->cnt_CurrentCtrl = 1.0;
}

/* Model step function */
void Basic_FOC_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Chart: '<Root>/Basic_FOC' incorporates:
   *  Inport: '<Root>/RESET'
   *  Inport: '<Root>/START'
   *  Inport: '<Root>/T_controller'
   *  Inport: '<Root>/T_speedController'
   *  Inport: '<Root>/U_IC'
   *  Inport: '<Root>/flgLimitUdUq'
   *  Inport: '<Root>/flg_PreCntr'
   *  Inport: '<Root>/flg_SpeedControl'
   *  Inport: '<Root>/flg_UseMMPA'
   *  Inport: '<Root>/flg_fieldWeakening'
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Inport: '<Root>/id_ref'
   *  Inport: '<Root>/iq_ref'
   *  Inport: '<Root>/n_ist'
   *  Inport: '<Root>/n_soll'
   *  Inport: '<Root>/theta_el'
   *  Inport: '<Root>/w_el'
   */
  /* Gateway: Basic_FOC */
  /* During: Basic_FOC */
  if (rtDW->is_active_c3_Basic_FOC == 0U) {
    /* Entry: Basic_FOC */
    rtDW->is_active_c3_Basic_FOC = 1U;

    /* Entry Internal: Basic_FOC */
    /* Transition: '<S1>:2' */
    rtDW->is_c3_Basic_FOC = IN_Start;

    /* Outport: '<Root>/activeState' */
    /* Entry 'Start': '<S1>:1' */
    /* '<S1>:1:3' activeState = 1; */
    rtY->activeState = 1.0;

    /* Outport: '<Root>/Ua_DutyCycle' */
    /* '<S1>:1:4' Ua_DutyCycle = 0; */
    rtY->Ua_DutyCycle = 0.0;

    /* Outport: '<Root>/Ub_DutyCycle' */
    /* '<S1>:1:5' Ub_DutyCycle = 0; */
    rtY->Ub_DutyCycle = 0.0;

    /* Outport: '<Root>/Uc_DutyCycle' */
    /* '<S1>:1:6' Uc_DutyCycle = 0; */
    rtY->Uc_DutyCycle = 0.0;
  } else if (rtDW->is_c3_Basic_FOC == IN_InProcess) {
    /* Outport: '<Root>/activeState' */
    rtY->activeState = 2.0;

    /* During 'InProcess': '<S1>:3' */
    /* '<S1>:18:1' sf_internal_predicateOutput = RESET==1; */
    if (rtU->RESET == 1.0F) {
      /* Transition: '<S1>:18' */
      /* Exit Internal 'InProcess': '<S1>:3' */
      rtDW->is_InProcess = IN_NO_ACTIVE_CHILD;
      rtDW->is_c3_Basic_FOC = IN_Start;

      /* Outport: '<Root>/activeState' */
      /* Entry 'Start': '<S1>:1' */
      /* '<S1>:1:3' activeState = 1; */
      rtY->activeState = 1.0;

      /* Outport: '<Root>/Ua_DutyCycle' */
      /* '<S1>:1:4' Ua_DutyCycle = 0; */
      rtY->Ua_DutyCycle = 0.0;

      /* Outport: '<Root>/Ub_DutyCycle' */
      /* '<S1>:1:5' Ub_DutyCycle = 0; */
      rtY->Ub_DutyCycle = 0.0;

      /* Outport: '<Root>/Uc_DutyCycle' */
      /* '<S1>:1:6' Uc_DutyCycle = 0; */
      rtY->Uc_DutyCycle = 0.0;
    } else if (rtDW->is_InProcess == IN_CurrentControl) {
      /* During 'CurrentControl': '<S1>:91' */
      /* '<S1>:102:1' sf_internal_predicateOutput = cnt_CurrentCtrl >= rat_freq; */
      if (rtDW->cnt_CurrentCtrl >= rtDW->rat_freq) {
        /* Transition: '<S1>:102' */
        rtDW->is_InProcess = IN_SpeedControl;
        enter_atomic_SpeedControl(&rtDW->id_ref_h, &rtDW->iq_ref_e,
          &rtDW->n_soll, &rtDW->n_ist, &rtDW->flg_fieldWeakening,
          &rtDW->flg_UseMMPA, rtU, rtY, rtM, rtDW);
      } else {
        /* '<S1>:91:6' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq) */
        /* Simulink Function 'CurrentController': '<S1>:72' */
        rtDW->ia = rtU->ia;
        rtDW->ib = rtU->ib;
        rtDW->ic = rtU->ic;
        rtDW->w_el = rtU->w_el;
        rtDW->flg_PreCtrl = rtU->flg_PreCntr;
        rtDW->theta_el = rtU->theta_el;
        rtDW->U_IC = rtU->U_IC;
        rtDW->id_ref = rtDW->id_soll;
        rtDW->iq_ref = rtDW->iq_soll;
        rtDW->flg_LimitUdUq = rtU->flgLimitUdUq;

        /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
        CurrentController(rtM, rtDW->ia, rtDW->ib, rtDW->ic, rtDW->w_el,
                          rtDW->flg_PreCtrl, rtDW->theta_el, rtDW->U_IC,
                          rtDW->id_ref, rtDW->iq_ref, rtDW->flg_LimitUdUq,
                          &rtDW->u_a, &rtDW->u_b, &rtDW->u_c, rtDW->Switch_j,
                          &rtDW->OutportBufferForId_ist, &rtDW->Switch2,
                          &rtDW->Switch3, &rtDW->CurrentController_f);

        /* End of Outputs for SubSystem: '<S1>/CurrentController' */

        /* Outport: '<Root>/Ua_DutyCycle' incorporates:
         *  Inport: '<Root>/U_IC'
         *  Inport: '<Root>/flgLimitUdUq'
         *  Inport: '<Root>/flg_PreCntr'
         *  Inport: '<Root>/ia'
         *  Inport: '<Root>/ib'
         *  Inport: '<Root>/ic'
         *  Inport: '<Root>/theta_el'
         *  Inport: '<Root>/w_el'
         */
        rtY->Ua_DutyCycle = rtDW->u_a;

        /* Outport: '<Root>/Ub_DutyCycle' */
        rtY->Ub_DutyCycle = rtDW->u_b;

        /* Outport: '<Root>/Uc_DutyCycle' */
        rtY->Uc_DutyCycle = rtDW->u_c;

        /* Outport: '<Root>/iq_ist' */
        rtY->iq_ist = rtDW->Switch_j[1];

        /* Outport: '<Root>/id_ist' */
        rtY->id_ist = rtDW->OutportBufferForId_ist;

        /* Outport: '<Root>/ud' */
        rtY->ud = rtDW->Switch2;

        /* Outport: '<Root>/uq' */
        rtY->uq = rtDW->Switch3;

        /* '<S1>:91:7' cnt_CurrentCtrl = cnt_CurrentCtrl +1; */
        rtDW->cnt_CurrentCtrl++;
      }

      /* During 'SpeedControl': '<S1>:90' */
      /* '<S1>:100:1' sf_internal_predicateOutput = rat_freq > 1; */
    } else if (rtDW->rat_freq > 1.0) {
      /* Transition: '<S1>:100' */
      rtDW->is_InProcess = IN_CurrentControl;

      /* Entry 'CurrentControl': '<S1>:91' */
      /* '<S1>:91:3' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq) */
      /* Simulink Function 'CurrentController': '<S1>:72' */
      rtDW->ia = rtU->ia;
      rtDW->ib = rtU->ib;
      rtDW->ic = rtU->ic;
      rtDW->w_el = rtU->w_el;
      rtDW->flg_PreCtrl = rtU->flg_PreCntr;
      rtDW->theta_el = rtU->theta_el;
      rtDW->U_IC = rtU->U_IC;
      rtDW->id_ref = rtDW->id_soll;
      rtDW->iq_ref = rtDW->iq_soll;
      rtDW->flg_LimitUdUq = rtU->flgLimitUdUq;

      /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
      CurrentController(rtM, rtDW->ia, rtDW->ib, rtDW->ic, rtDW->w_el,
                        rtDW->flg_PreCtrl, rtDW->theta_el, rtDW->U_IC,
                        rtDW->id_ref, rtDW->iq_ref, rtDW->flg_LimitUdUq,
                        &rtDW->u_a, &rtDW->u_b, &rtDW->u_c, rtDW->Switch_j,
                        &rtDW->OutportBufferForId_ist, &rtDW->Switch2,
                        &rtDW->Switch3, &rtDW->CurrentController_f);

      /* End of Outputs for SubSystem: '<S1>/CurrentController' */

      /* Outport: '<Root>/Ua_DutyCycle' incorporates:
       *  Inport: '<Root>/U_IC'
       *  Inport: '<Root>/flgLimitUdUq'
       *  Inport: '<Root>/flg_PreCntr'
       *  Inport: '<Root>/ia'
       *  Inport: '<Root>/ib'
       *  Inport: '<Root>/ic'
       *  Inport: '<Root>/theta_el'
       *  Inport: '<Root>/w_el'
       */
      rtY->Ua_DutyCycle = rtDW->u_a;

      /* Outport: '<Root>/Ub_DutyCycle' */
      rtY->Ub_DutyCycle = rtDW->u_b;

      /* Outport: '<Root>/Uc_DutyCycle' */
      rtY->Uc_DutyCycle = rtDW->u_c;

      /* Outport: '<Root>/iq_ist' */
      rtY->iq_ist = rtDW->Switch_j[1];

      /* Outport: '<Root>/id_ist' */
      rtY->id_ist = rtDW->OutportBufferForId_ist;

      /* Outport: '<Root>/ud' */
      rtY->ud = rtDW->Switch2;

      /* Outport: '<Root>/uq' */
      rtY->uq = rtDW->Switch3;

      /* '<S1>:91:4' cnt_CurrentCtrl = cnt_CurrentCtrl +1; */
      rtDW->cnt_CurrentCtrl++;
    } else {
      /* '<S1>:90:7' [id_soll,iq_soll] = SpeedController(id_ref,iq_ref,n_soll,n_ist,flg_fieldWeakening,flg_UseMMPA,flg_SpeedControl) */
      /* Simulink Function 'SpeedController': '<S1>:62' */
      rtDW->flg_SpeedControl = rtU->flg_SpeedControl;

      /* Outputs for Function Call SubSystem: '<S1>/SpeedController' */
      SpeedController(rtM, (real_T)rtU->id_ref, (real_T)rtU->iq_ref, (real_T)
                      rtU->n_soll, (real_T)rtU->n_ist, (real_T)
                      rtU->flg_fieldWeakening, (real_T)rtU->flg_UseMMPA,
                      rtDW->flg_SpeedControl, &rtDW->Switch, &rtDW->Switch1,
                      &rtDW->SpeedController_j);

      /* End of Outputs for SubSystem: '<S1>/SpeedController' */
      rtDW->id_soll = rtDW->Switch;
      rtDW->iq_soll = rtDW->Switch1;

      /* '<S1>:90:8' [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq) */
      /* Simulink Function 'CurrentController': '<S1>:72' */
      rtDW->ia = rtU->ia;
      rtDW->ib = rtU->ib;
      rtDW->ic = rtU->ic;
      rtDW->w_el = rtU->w_el;
      rtDW->flg_PreCtrl = rtU->flg_PreCntr;
      rtDW->theta_el = rtU->theta_el;
      rtDW->U_IC = rtU->U_IC;
      rtDW->id_ref = rtDW->id_soll;
      rtDW->iq_ref = rtDW->iq_soll;
      rtDW->flg_LimitUdUq = rtU->flgLimitUdUq;

      /* Outputs for Function Call SubSystem: '<S1>/CurrentController' */
      CurrentController(rtM, rtDW->ia, rtDW->ib, rtDW->ic, rtDW->w_el,
                        rtDW->flg_PreCtrl, rtDW->theta_el, rtDW->U_IC,
                        rtDW->id_ref, rtDW->iq_ref, rtDW->flg_LimitUdUq,
                        &rtDW->u_a, &rtDW->u_b, &rtDW->u_c, rtDW->Switch_j,
                        &rtDW->OutportBufferForId_ist, &rtDW->Switch2,
                        &rtDW->Switch3, &rtDW->CurrentController_f);

      /* End of Outputs for SubSystem: '<S1>/CurrentController' */

      /* Outport: '<Root>/Ua_DutyCycle' incorporates:
       *  Inport: '<Root>/U_IC'
       *  Inport: '<Root>/flgLimitUdUq'
       *  Inport: '<Root>/flg_PreCntr'
       *  Inport: '<Root>/flg_SpeedControl'
       *  Inport: '<Root>/flg_UseMMPA'
       *  Inport: '<Root>/flg_fieldWeakening'
       *  Inport: '<Root>/ia'
       *  Inport: '<Root>/ib'
       *  Inport: '<Root>/ic'
       *  Inport: '<Root>/id_ref'
       *  Inport: '<Root>/iq_ref'
       *  Inport: '<Root>/n_ist'
       *  Inport: '<Root>/n_soll'
       *  Inport: '<Root>/theta_el'
       *  Inport: '<Root>/w_el'
       */
      rtY->Ua_DutyCycle = rtDW->u_a;

      /* Outport: '<Root>/Ub_DutyCycle' */
      rtY->Ub_DutyCycle = rtDW->u_b;

      /* Outport: '<Root>/Uc_DutyCycle' */
      rtY->Uc_DutyCycle = rtDW->u_c;

      /* Outport: '<Root>/iq_ist' */
      rtY->iq_ist = rtDW->Switch_j[1];

      /* Outport: '<Root>/id_ist' */
      rtY->id_ist = rtDW->OutportBufferForId_ist;

      /* Outport: '<Root>/ud' */
      rtY->ud = rtDW->Switch2;

      /* Outport: '<Root>/uq' */
      rtY->uq = rtDW->Switch3;
    }
  } else {
    /* Outport: '<Root>/activeState' */
    rtY->activeState = 1.0;

    /* During 'Start': '<S1>:1' */
    /* '<S1>:17:1' sf_internal_predicateOutput = START==1 & RESET==0; */
    if ((rtU->START == 1.0F) && (rtU->RESET == 0.0F)) {
      /* Transition: '<S1>:17' */
      rtDW->is_c3_Basic_FOC = IN_InProcess;

      /* Outport: '<Root>/activeState' */
      /* Entry 'InProcess': '<S1>:3' */
      /* '<S1>:3:3' activeState = 2; */
      rtY->activeState = 2.0;

      /* '<S1>:3:4' id_soll = 0; */
      /* '<S1>:3:5' iq_soll = 0; */
      /* '<S1>:3:6' rat_freq = T_speedController/T_controller; */
      rtDW->rat_freq = rtU->T_speedController / rtU->T_controller;

      /* during: */
      /* [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = Controller(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC, iq_ref, id_ref, n_soll, n_ist, flg_fieldWeakening, flg_SpeedControl, flgLimitUdUq,flg_UseMMPA) */
      /* on every(T_speedController,sec): [id_soll,iq_soll] = SpeedController(id_ref,iq_ref,n_soll,n_ist,flg_fieldWeakening,flg_UseMMPA,flg_SpeedControl); */
      /* on every(T_controller,sec): [Ua_DutyCycle, Ub_DutyCycle, Uc_DutyCycle, iq_ist, id_ist, ud, uq] = CurrentController(ia, ib, ic, w_el, flg_PreCntr, theta_el, U_IC,id_soll,iq_soll,flgLimitUdUq); */
      /* Entry Internal 'InProcess': '<S1>:3' */
      /* Transition: '<S1>:101' */
      rtDW->is_InProcess = IN_SpeedControl;
      enter_atomic_SpeedControl(&rtDW->id_ref_h, &rtDW->iq_ref_e, &rtDW->n_soll,
        &rtDW->n_ist, &rtDW->flg_fieldWeakening, &rtDW->flg_UseMMPA, rtU, rtY,
        rtM, rtDW);
    }
  }

  /* End of Chart: '<Root>/Basic_FOC' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.002, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  rtM->Timing.clockTick0++;
}

/* Model initialize function */
void Basic_FOC_initialize(RT_MODEL *const rtM)
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
  (void) memset((void *)rtY, 0,
                sizeof(ExtY));
  rtDW->is_InProcess = IN_NO_ACTIVE_CHILD;
  rtDW->is_active_c3_Basic_FOC = 0U;
  rtDW->is_c3_Basic_FOC = IN_NO_ACTIVE_CHILD;
  rtDW->id_soll = 0.0;
  rtDW->iq_soll = 0.0;
  rtDW->rat_freq = 0.0;
  rtDW->cnt_CurrentCtrl = 0.0;

  /* SystemInitialize for Outport: '<Root>/Ua_DutyCycle' */
  rtY->Ua_DutyCycle = 0.0;

  /* SystemInitialize for Outport: '<Root>/activeState' */
  rtY->activeState = 0.0;

  /* SystemInitialize for Outport: '<Root>/Uc_DutyCycle' */
  rtY->Uc_DutyCycle = 0.0;

  /* SystemInitialize for Outport: '<Root>/Ub_DutyCycle' */
  rtY->Ub_DutyCycle = 0.0;

  /* SystemInitialize for Outport: '<Root>/iq_ist' */
  rtY->iq_ist = 0.0;

  /* SystemInitialize for Outport: '<Root>/id_ist' */
  rtY->id_ist = 0.0;

  /* SystemInitialize for Outport: '<Root>/uq' */
  rtY->uq = 0.0;

  /* SystemInitialize for Outport: '<Root>/ud' */
  rtY->ud = 0.0;

  /* SystemInitialize for Chart: '<Root>/Basic_FOC' incorporates:
   *  SubSystem: '<S1>/CurrentController'
   */
  CurrentController_Init(&rtDW->CurrentController_f);

  /* SystemInitialize for Chart: '<Root>/Basic_FOC' incorporates:
   *  SubSystem: '<S1>/SpeedController'
   */
  SpeedController_Init(&rtDW->SpeedController_j);

  /* Enable for Chart: '<Root>/Basic_FOC' incorporates:
   *  SubSystem: '<S1>/CurrentController'
   */
  CurrentController_Enable(&rtDW->CurrentController_f);

  /* Enable for Chart: '<Root>/Basic_FOC' incorporates:
   *  SubSystem: '<S1>/SpeedController'
   */
  SpeedController_Enable(&rtDW->SpeedController_j);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
