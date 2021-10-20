/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_6ph0.c
 *
 * Code generated for Simulink model 'FOC_6ph0'.
 *
 * Model version                  : 7.38
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Tue Oct 12 10:37:02 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_6ph0.h"

/* Named constants for Chart: '<Root>/FOC_6ph' */
#define FOC_6ph0_IN_Init               ((uint8_T)2U)
#define FOC_6ph0_IN_NO_ACTIVE_CHILD    ((uint8_T)0U)
#define FOC_6ph_IN_FieldOrientedControl ((uint8_T)1U)

/* Exported block parameters */
real_T Kpd = 0.075398223686155036*0.5;     /* Variable: Kpd
                                        * Referenced by:
                                        *   '<S96>/Proportional Gain'
                                        *   '<S102>/P Copy'
                                        */
real_T Kpn = 1.224610768327322;        /* Variable: Kpn
                                        * Referenced by:
                                        *   '<S46>/Proportional Gain'
                                        *   '<S52>/P Copy'
                                        */
real_T Kpq = 0.12566370614359174*0.5;      /* Variable: Kpq
                                        * Referenced by:
                                        *   '<S146>/Proportional Gain'
                                        *   '<S152>/P Copy'
                                        */
real_T PERIOD = 500.0;                 /* Variable: PERIOD
                                        * Referenced by:
                                        *   '<S2>/Gain2'
                                        *   '<S2>/Gain3'
                                        *   '<S2>/Gain4'
                                        *   '<S2>/Gain5'
                                        *   '<S2>/Gain6'
                                        *   '<S2>/Gain7'
                                        */
real_T Tnd = 9999;/*0.0013043478260869566;    /* Variable: Tnd
                                        * Referenced by: '<S95>/Integral Gain'
                                        */
real_T Tnn = 0.039788735772973829;     /* Variable: Tnn
                                        * Referenced by: '<S45>/Integral Gain'
                                        */
real_T Tnq = 9999;/*0.0021739130434782609;    /* Variable: Tnq
                                        * Referenced by: '<S145>/Integral Gain'
                                        */
real_T u_dc = 36.0;                    /* Variable: u_dc
                                        * Referenced by:
                                        *   '<S105>/Saturation'
                                        *   '<S155>/Saturation'
                                        *   '<S91>/DeadZone'
                                        *   '<S141>/DeadZone'
                                        */
static void FOC_6ph0_RZM_Traegerbasiert(real_T rtu_u_alpha, real_T rtu_u_beta,
  real_T rtu_U_ZK, real_T rtu_CMP_Period_max_val, real_T *rty_CMP_U, real_T
  *rty_CMP_V, real_T *rty_CMP_W, real_T *rty_sector);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

/*
 * Output and update for atomic system:
 *    '<S2>/RZM_Traegerbasiert'
 *    '<S2>/RZM_Traegerbasiert1'
 */
static void FOC_6ph0_RZM_Traegerbasiert(real_T rtu_u_alpha, real_T rtu_u_beta,
  real_T rtu_U_ZK, real_T rtu_CMP_Period_max_val, real_T *rty_CMP_U, real_T
  *rty_CMP_V, real_T *rty_CMP_W, real_T *rty_sector)
{
  real_T a;
  real_T a_U_on;
  real_T a_V_on;
  real_T a_W_on;
  real_T a_tmp;
  real_T b;
  real_T c;
  real_T u2;
  int32_T quadrant;
  int32_T sector;

  /* MATLAB Function 'FOC_6ph/superState.FOC/RZM_Traegerbasiert': '<S8>:1' */
  /* '<S8>:1:4' a_U_on=0; */
  a_U_on = 0.0;

  /* '<S8>:1:5' a_V_on=0; */
  a_V_on = 0.0;

  /* '<S8>:1:6' a_W_on=0; */
  a_W_on = 0.0;

  /* '<S8>:1:7' CMP_U=0; */
  /* '<S8>:1:8' CMP_V=0; */
  /* '<S8>:1:9' CMP_W=0; */
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
  /* '<S8>:1:27' a = abs(u_alpha) + 0.5774*abs(u_beta); */
  a_tmp = fabs(rtu_u_alpha);
  c = fabs(rtu_u_beta);
  a = 0.5774 * c + a_tmp;

  /* '<S8>:1:28' b = abs(u_alpha) - 0.5774*abs(u_beta); */
  b = a_tmp - 0.5774 * fabs(rtu_u_beta);

  /* '<S8>:1:29' c = 1.1547*abs(u_beta); */
  c *= 1.1547;

  /* Sektor und Quadranten nach Quang Dittrich S32 */
  /* '<S8>:1:33' if(u_beta < 0) */
  if (rtu_u_beta < 0.0) {
    /* '<S8>:1:34' if (u_alpha <0) */
    if (rtu_u_alpha < 0.0) {
      /* '<S8>:1:35' quadrant=3; */
      quadrant = 3;

      /* '<S8>:1:36' if(b < 0) */
      if (b < 0.0) {
        /* '<S8>:1:37' sector = 5; */
        sector = 5;
      } else {
        /* '<S8>:1:38' else */
        /* '<S8>:1:39' sector = 4; */
        sector = 4;
      }
    } else {
      /* '<S8>:1:41' else */
      /* '<S8>:1:42' quadrant=4; */
      quadrant = 4;

      /* '<S8>:1:43' if(b < 0) */
      if (b < 0.0) {
        /* '<S8>:1:44' sector = 5; */
        sector = 5;
      } else {
        /* '<S8>:1:45' else */
        /* '<S8>:1:46' sector = 6; */
        sector = 6;
      }
    }

    /* '<S8>:1:50' else */
    /* '<S8>:1:51' if (u_alpha <0) */
  } else if (rtu_u_alpha < 0.0) {
    /* '<S8>:1:52' quadrant=2; */
    quadrant = 2;

    /* '<S8>:1:53' if(b < 0) */
    if (b < 0.0) {
      /* '<S8>:1:54' sector = 2; */
      sector = 2;
    } else {
      /* '<S8>:1:55' else */
      /* '<S8>:1:56' sector = 3; */
      sector = 3;
    }
  } else {
    /* '<S8>:1:58' else */
    /* '<S8>:1:59' quadrant=1; */
    quadrant = 1;

    /* '<S8>:1:60' if(b < 0) */
    if (b < 0.0) {
      /* '<S8>:1:61' sector = 2; */
      sector = 2;
    } else {
      /* '<S8>:1:62' else */
      /* '<S8>:1:63' sector = 1; */
      sector = 1;
    }
  }

  /* '<S8>:1:68' sector = sector; */
  /* Modulationsfunktionen f¸r Phasen U,V,W */
  /* Erzeugung der Aussteuergrade f¸r die Halbbr¸cken */
  /* --> Erzeugung einer "regulary Sampled SVM" erfolgt anschlieﬂend durch Abtastung */
  /* mit Dreiecksz‰hlern in Hardware. */
  /* '<S8>:1:75' if (sector == 1) */
  if (sector == 1) {
    /* '<S8>:1:77' u1 = b/(0.66667*U_ZK); */
    a_W_on = b / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:78' u2 = c/(0.66667*U_ZK); */
    u2 = c / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:80' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
    a_U_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;

    /* '<S8>:1:81' a_V_on = 0.5 - u1*0.5 + u2*0.5; */
    a_W_on = 0.5 - a_W_on * 0.5;
    a_V_on = a_W_on + u2 * 0.5;

    /* '<S8>:1:82' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    a_W_on -= u2 * 0.5;
  }

  /* '<S8>:1:86' if ((sector == 2) && (quadrant == 1)) */
  if ((sector == 2) && (quadrant == 1)) {
    /* '<S8>:1:88' u1 = a/(0.66667*U_ZK); */
    a_W_on = a / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:89' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(0.66667*U_ZK); */
    u2 = (0.5774 * fabs(rtu_u_beta) + -a_tmp) / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:91' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
    a_U_on = (a_W_on * 0.5 + 0.5) - u2 * 0.5;

    /* '<S8>:1:92' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    a_V_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;

    /* '<S8>:1:93' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    a_W_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
  }

  /* '<S8>:1:97' if ((sector == 2) && (quadrant == 2)) */
  if ((sector == 2) && (quadrant == 2)) {
    /* '<S8>:1:99' u1 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(0.66667*U_ZK); */
    a_W_on = (0.5774 * fabs(rtu_u_beta) + -fabs(rtu_u_alpha)) / (0.66667 *
      rtu_U_ZK);

    /* '<S8>:1:100' u2 = a/(0.66667*U_ZK); */
    u2 = a / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:102' a_U_on = 0.5 + u1*0.5 - u2*0.5; */
    a_U_on = (a_W_on * 0.5 + 0.5) - u2 * 0.5;

    /* '<S8>:1:103' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    a_V_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;

    /* '<S8>:1:104' a_W_on = 0.5 - u1*0.5 - u2*0.5; */
    a_W_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;
  }

  /* '<S8>:1:108' if (sector == 3) */
  if (sector == 3) {
    /* '<S8>:1:110' u1 = c/(0.66667*U_ZK); */
    a_W_on = c / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:111' u2 = b/(0.66667*U_ZK); */
    u2 = b / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:113' a_U_on=  0.5 - u1*0.5 - u2*0.5; */
    a_U_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;

    /* '<S8>:1:114' a_V_on = 0.5 + u1*0.5 + u2*0.5; */
    a_V_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;

    /* '<S8>:1:115' a_W_on = 0.5 - u1*0.5 + u2*0.5; */
    a_W_on = (0.5 - a_W_on * 0.5) + u2 * 0.5;
  }

  /* '<S8>:1:118' if (sector == 4) */
  if (sector == 4) {
    /* '<S8>:1:120' u1 = b/(0.66667*U_ZK); */
    a_W_on = b / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:121' u2 = c/(0.66667*U_ZK); */
    u2 = c / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:123' a_U_on = 0.5 - u1*0.5 - u2*0.5; */
    a_U_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;

    /* '<S8>:1:124' a_V_on = 0.5 + u1*0.5 - u2*0.5; */
    a_W_on = a_W_on * 0.5 + 0.5;
    a_V_on = a_W_on - u2 * 0.5;

    /* '<S8>:1:125' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    a_W_on += u2 * 0.5;
  }

  /* '<S8>:1:129' if ((sector == 5) && (quadrant == 3)) */
  if ((sector == 5) && (quadrant == 3)) {
    /* '<S8>:1:131' u1 = a/(0.66667*U_ZK); */
    a_W_on = a / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:132' u2 = (-abs(u_alpha) + 0.5774*abs(u_beta))/(0.66667*U_ZK); */
    u2 = (0.5774 * fabs(rtu_u_beta) + -fabs(rtu_u_alpha)) / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:134' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
    a_U_on = (0.5 - a_W_on * 0.5) + u2 * 0.5;

    /* '<S8>:1:135' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    a_V_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;

    /* '<S8>:1:136' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    a_W_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
  }

  /* '<S8>:1:140' if ((sector == 5) && (quadrant == 4)) */
  if ((sector == 5) && (quadrant == 4)) {
    /* '<S8>:1:142' u1 =(-abs(u_alpha) + 0.5774*abs(u_beta))/(0.66667*U_ZK); */
    a_W_on = (0.5774 * fabs(rtu_u_beta) + -fabs(rtu_u_alpha)) / (0.66667 *
      rtu_U_ZK);

    /* '<S8>:1:143' u2 =  a/(0.66667*U_ZK); */
    u2 = a / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:145' a_U_on = 0.5 - u1*0.5 + u2*0.5; */
    a_U_on = (0.5 - a_W_on * 0.5) + u2 * 0.5;

    /* '<S8>:1:146' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    a_V_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;

    /* '<S8>:1:147' a_W_on = 0.5 + u1*0.5 + u2*0.5; */
    a_W_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;
  }

  /* '<S8>:1:151' if (sector == 6) */
  if (sector == 6) {
    /* '<S8>:1:153' u1 = c/(0.66667*U_ZK); */
    a_W_on = c / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:154' u2 = b/(0.66667*U_ZK); */
    u2 = b / (0.66667 * rtu_U_ZK);

    /* '<S8>:1:156' a_U_on = 0.5 + u1*0.5 + u2*0.5; */
    a_U_on = (a_W_on * 0.5 + 0.5) + u2 * 0.5;

    /* '<S8>:1:157' a_V_on = 0.5 - u1*0.5 - u2*0.5; */
    a_V_on = (0.5 - a_W_on * 0.5) - u2 * 0.5;

    /* '<S8>:1:158' a_W_on = 0.5 + u1*0.5 - u2*0.5; */
    a_W_on = (a_W_on * 0.5 + 0.5) - u2 * 0.5;
  }

  /* Aussteuergrade auf Z‰hlregister normieren -> Comparewerte CMP */
  /* '<S8>:1:163' CMP_U = a_U_on * CMP_Period_max_val; */
  a_U_on *= rtu_CMP_Period_max_val;

  /* '<S8>:1:164' CMP_V = a_V_on * CMP_Period_max_val; */
  a_V_on *= rtu_CMP_Period_max_val;

  /* '<S8>:1:165' CMP_W = a_W_on * CMP_Period_max_val; */
  a_W_on *= rtu_CMP_Period_max_val;

  /* Begrenzung */
  /* '<S8>:1:168' if (CMP_U > CMP_Period_max_val) */
  if (a_U_on > rtu_CMP_Period_max_val) {
    /* '<S8>:1:169' CMP_U = CMP_Period_max_val; */
    a_U_on = rtu_CMP_Period_max_val;
  }

  /* '<S8>:1:171' if (CMP_U < 0) */
  if (a_U_on < 0.0) {
    /* '<S8>:1:172' CMP_U = 0; */
    a_U_on = 0.0;
  }

  /* '<S8>:1:175' if (CMP_V > CMP_Period_max_val) */
  if (a_V_on > rtu_CMP_Period_max_val) {
    /* '<S8>:1:176' CMP_V = CMP_Period_max_val; */
    a_V_on = rtu_CMP_Period_max_val;
  }

  /* '<S8>:1:178' if (CMP_V < 0) */
  if (a_V_on < 0.0) {
    /* '<S8>:1:179' CMP_V = 0; */
    a_V_on = 0.0;
  }

  /* '<S8>:1:182' if (CMP_W > CMP_Period_max_val) */
  if (a_W_on > rtu_CMP_Period_max_val) {
    /* '<S8>:1:183' CMP_W = CMP_Period_max_val; */
    a_W_on = rtu_CMP_Period_max_val;
  }

  /* '<S8>:1:185' if (CMP_W < 0) */
  if (a_W_on < 0.0) {
    /* '<S8>:1:186' CMP_W = 0; */
    a_W_on = 0.0;
  }

  /* __%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%__%%_ */
  *rty_CMP_U = a_U_on;
  *rty_CMP_V = a_V_on;
  *rty_CMP_W = a_W_on;
  *rty_sector = sector;
}

/* Model step function */
void FOC_6ph0_step(RT_MODEL_FOC_6ph0_T *const FOC_6ph0_M)
{
  B_FOC_6ph0_T *FOC_6ph0_B = FOC_6ph0_M->blockIO;
  DW_FOC_6ph0_T *FOC_6ph0_DW = FOC_6ph0_M->dwork;
  ExtU_FOC_6ph0_T *FOC_6ph0_U = (ExtU_FOC_6ph0_T *) FOC_6ph0_M->inputs;
  ExtY_FOC_6ph0_T *FOC_6ph0_Y = (ExtY_FOC_6ph0_T *) FOC_6ph0_M->outputs;
  real_T Integrator;
  real_T Integrator_c;
  real_T Integrator_e;
  real_T rtb_CMP_U;
  real_T rtb_CMP_W;
  real_T rtb_IntegralGain;
  real_T rtb_IntegralGain_a;
  real_T rtb_IntegralGain_o;
  real_T rtb_ProportionalGain;
  real_T rtb_SignP;
  real_T rtb_SignP_0;
  real_T rtb_SignPreSat;
  real_T rtb_SignPreSat_i;
  real_T rtb_sector;
  real_T tmp_1;
  int32_T i;
  int32_T i_0;
  real32_T tmp[36];
  real32_T A[6];
  real32_T tmp_0[6];
  real32_T Switch_idx_0;
  real32_T Switch_idx_1;
  real32_T rtb_Switch_f_idx_0;
  real32_T rtb_Switch_f_idx_1;
  uint32_T superStateFOC_ELAPS_T;
  boolean_T rtb_AND1;
  boolean_T rtb_AND1_kl;
  boolean_T rtb_AND2;
  boolean_T rtb_AND2_a;
  boolean_T rtb_Equal1;
  boolean_T rtb_Equal2;
  static const real_T b[6] = { 1.0, -0.5, -0.5, 0.8660254037844386,
    -0.8660254037844386, 0.0 };

  static const real_T c[6] = { 0.0, 0.8660254037844386, -0.8660254037844386, 0.5,
    0.5, -1.0 };

  static const real_T d[6] = { 1.0, -0.5, -0.5, -0.8660254037844386,
    0.8660254037844386, 0.0 };

  static const real_T e[6] = { 0.0, -0.8660254037844386, 0.8660254037844386, 0.5,
    0.5, -1.0 };

  /* Chart: '<Root>/FOC_6ph' incorporates:
   *  Inport: '<Root>/NEXT'
   *  Inport: '<Root>/RESET'
   */
  /* Gateway: FOC_6ph */
  /* During: FOC_6ph */
  if (FOC_6ph0_DW->is_active_c33_FOC_6ph0 == 0U) {
    /* Entry: FOC_6ph */
    FOC_6ph0_DW->is_active_c33_FOC_6ph0 = 1U;

    /* Enable for Function Call SubSystem: '<S1>/superState.FOC' */
    /* Entry Internal: FOC_6ph */
    /* Entry 'superState': '<S1>:3' */
    FOC_6ph0_DW->superStateFOC_RESET_ELAPS_T = true;

    /* Enable for DiscreteIntegrator: '<S98>/Integrator' */
    FOC_6ph0_DW->Integrator_SYSTEM_ENABLE = 1U;

    /* Enable for DiscreteIntegrator: '<S48>/Integrator' */
    FOC_6ph0_DW->Integrator_SYSTEM_ENABLE_e = 1U;

    /* Enable for DiscreteIntegrator: '<S148>/Integrator' */
    FOC_6ph0_DW->Integrator_SYSTEM_ENABLE_m = 1U;

    /* End of Enable for SubSystem: '<S1>/superState.FOC' */
    /* Entry Internal 'superState': '<S1>:3' */
    /* Transition: '<S1>:2' */
    FOC_6ph0_DW->is_superState = FOC_6ph0_IN_Init;

    /* Outport: '<Root>/activeState' */
    /* Entry 'Init': '<S1>:1' */
    /* state 10 */
    /* '<S1>:1:4' activeState = 10; */
    FOC_6ph0_Y->activeState = 10U;

    /* Outport: '<Root>/CMPA_1' */
    /* '<S1>:1:5' CMPA_1 = 0; */
    FOC_6ph0_Y->CMPA_1 = 0.0;

    /* Outport: '<Root>/CMPA_2' */
    /* '<S1>:1:6' CMPA_2 = 0; */
    FOC_6ph0_Y->CMPA_2 = 0.0;

    /* Outport: '<Root>/CMPA_3' */
    /* '<S1>:1:7' CMPA_3 = 0; */
    FOC_6ph0_Y->CMPA_3 = 0.0;

    /* Outport: '<Root>/CMPA_4' */
    /* '<S1>:1:8' CMPA_4 = 0; */
    FOC_6ph0_Y->CMPA_4 = 0.0;

    /* Outport: '<Root>/CMPA_5' */
    /* '<S1>:1:9' CMPA_5 = 0; */
    FOC_6ph0_Y->CMPA_5 = 0.0;

    /* Outport: '<Root>/CMPA_6' */
    /* '<S1>:1:10' CMPA_6 = 0; */
    FOC_6ph0_Y->CMPA_6 = 0.0;

    /* During 'superState': '<S1>:3' */
    /* '<S1>:6:1' sf_internal_predicateOutput = RESET == 1; */
  } else if (FOC_6ph0_U->RESET) {
    /* Transition: '<S1>:6' */
    /* Exit Internal 'superState': '<S1>:3' */
    FOC_6ph0_DW->is_superState = FOC_6ph0_IN_Init;

    /* Outport: '<Root>/activeState' */
    /* Entry 'Init': '<S1>:1' */
    /* state 10 */
    /* '<S1>:1:4' activeState = 10; */
    FOC_6ph0_Y->activeState = 10U;

    /* Outport: '<Root>/CMPA_1' */
    /* '<S1>:1:5' CMPA_1 = 0; */
    FOC_6ph0_Y->CMPA_1 = 0.0;

    /* Outport: '<Root>/CMPA_2' */
    /* '<S1>:1:6' CMPA_2 = 0; */
    FOC_6ph0_Y->CMPA_2 = 0.0;

    /* Outport: '<Root>/CMPA_3' */
    /* '<S1>:1:7' CMPA_3 = 0; */
    FOC_6ph0_Y->CMPA_3 = 0.0;

    /* Outport: '<Root>/CMPA_4' */
    /* '<S1>:1:8' CMPA_4 = 0; */
    FOC_6ph0_Y->CMPA_4 = 0.0;

    /* Outport: '<Root>/CMPA_5' */
    /* '<S1>:1:9' CMPA_5 = 0; */
    FOC_6ph0_Y->CMPA_5 = 0.0;

    /* Outport: '<Root>/CMPA_6' */
    /* '<S1>:1:10' CMPA_6 = 0; */
    FOC_6ph0_Y->CMPA_6 = 0.0;
  } else if (FOC_6ph0_DW->is_superState == 1) {
    /* Outputs for Function Call SubSystem: '<S1>/superState.FOC' */
    /* During 'FieldOrientedControl': '<S1>:4' */
    /* '<S1>:4:6' [CMPA_1,CMPA_2,CMPA_3,CMPA_4,CMPA_5,CMPA_6,sector,id,iq,ud_ctrl,uq_ctrl] = FOC(u_dc,PERIOD,id_ref,iq_ref,i_a1,i_b1,i_c1,i_a2,i_b2,i_c2,u1,u2,u3,theta_el,currentORspeedControl, n_RPM, n_ref_RPM, activeState,Kr) */
    /* Simulink Function 'FOC': '<S1>:39' */
    if (FOC_6ph0_DW->superStateFOC_RESET_ELAPS_T) {
      superStateFOC_ELAPS_T = 0U;
    } else {
      superStateFOC_ELAPS_T = FOC_6ph0_M->Timing.clockTick0 -
        FOC_6ph0_DW->superStateFOC_PREV_T;
    }

    FOC_6ph0_DW->superStateFOC_PREV_T = FOC_6ph0_M->Timing.clockTick0;
    FOC_6ph0_DW->superStateFOC_RESET_ELAPS_T = false;

    /* MATLAB Function: '<S2>/6ph_PMSM_30deg_VSD1' incorporates:
     *  Constant: '<S2>/Constant10'
     *  Inport: '<Root>/i_a1'
     *  Inport: '<Root>/i_a2'
     *  Inport: '<Root>/i_b1'
     *  Inport: '<Root>/i_b2'
     *  Inport: '<Root>/i_c1'
     *  Inport: '<Root>/i_c2'
     */
    /* MATLAB Function 'FOC_6ph/superState.FOC/6ph_PMSM_30deg_VSD1': '<S3>:1' */
    /* '<S3>:1:3' A = [0 0 0 0 0 0]'; */
    /* '<S3>:1:5' A =    k6*[1    -0.5        -0.5        sqrt(3)/2   -sqrt(3)/2  0 ; */
    /* '<S3>:1:6'            0    sqrt(3)/2   -sqrt(3)/2  0.5         0.5         -1; */
    /* '<S3>:1:7'            1    -0.5        -0.5        -sqrt(3)/2  sqrt(3)/2   0 ; */
    /* '<S3>:1:8'            0    -sqrt(3)/2  sqrt(3)/2   0.5         0.5         -1; */
    /* '<S3>:1:9'            c6   c6          c6          0           0           0 ; */
    /* '<S3>:1:10'            0    0           0           c6          c6          c6] * [u1 u2 u3 u4 u5 u6]'; */
    tmp[4] = 0.333333343F;
    tmp[10] = 0.333333343F;
    tmp[16] = 0.333333343F;
    tmp[22] = 0.0F;
    tmp[28] = 0.0F;
    tmp[34] = 0.0F;
    tmp[5] = 0.0F;
    tmp[11] = 0.0F;
    tmp[17] = 0.0F;
    tmp[23] = 0.333333343F;
    tmp[29] = 0.333333343F;
    tmp[35] = 0.333333343F;
    tmp_0[0] = FOC_6ph0_U->i_a1;
    tmp_0[1] = FOC_6ph0_U->i_b1;
    tmp_0[2] = FOC_6ph0_U->i_c1;
    tmp_0[3] = FOC_6ph0_U->i_a2;
    tmp_0[4] = FOC_6ph0_U->i_b2;
    tmp_0[5] = FOC_6ph0_U->i_c2;
    for (i = 0; i < 6; i++) {
      tmp[6 * i] = (real32_T)(0.33333333333333331 * b[i]);
      tmp[6 * i + 1] = (real32_T)(0.33333333333333331 * c[i]);
      tmp[6 * i + 2] = (real32_T)(0.33333333333333331 * d[i]);
      tmp[6 * i + 3] = (real32_T)(0.33333333333333331 * e[i]);
      A[i] = 0.0F;
    }

    for (i = 0; i < 6; i++) {
      for (i_0 = 0; i_0 < 6; i_0++) {
        A[i] += tmp[6 * i_0 + i] * tmp_0[i_0];
      }
    }

    /* Outputs for Enabled SubSystem: '<S4>/Subsystem - pi//2 delay' incorporates:
     *  EnablePort: '<S13>/Enable'
     */
    /* '<S3>:1:12' y1 = A(1); */
    /* '<S3>:1:13' y2 = A(2); */
    /* '<S3>:1:14' y3 = A(3); */
    /* '<S3>:1:15' y4 = A(4); */
    /* '<S3>:1:16' y5 = A(5); */
    /* '<S3>:1:17' y6 = A(6); */
    if (FOC_6ph0_ConstB.Compare_m > 0) {
      /* Fcn: '<S13>/Fcn' incorporates:
       *  Fcn: '<S13>/Fcn1'
       *  Inport: '<Root>/theta_el'
       */
      rtb_Switch_f_idx_0 = (real32_T)cos(FOC_6ph0_U->theta_el);
      rtb_Switch_f_idx_1 = (real32_T)sin(FOC_6ph0_U->theta_el);

      /* Fcn: '<S13>/Fcn' incorporates:
       *  MATLAB Function: '<S2>/6ph_PMSM_30deg_VSD1'
       */
      FOC_6ph0_B->Fcn_lr = A[0] * rtb_Switch_f_idx_1 - A[1] * rtb_Switch_f_idx_0;

      /* Fcn: '<S13>/Fcn1' incorporates:
       *  MATLAB Function: '<S2>/6ph_PMSM_30deg_VSD1'
       */
      FOC_6ph0_B->Fcn1_k = A[0] * rtb_Switch_f_idx_0 + A[1] * rtb_Switch_f_idx_1;
    }

    /* End of Outputs for SubSystem: '<S4>/Subsystem - pi//2 delay' */

    /* Outputs for Enabled SubSystem: '<S4>/Subsystem1' incorporates:
     *  EnablePort: '<S14>/Enable'
     */
    if (FOC_6ph0_ConstB.Compare > 0) {
      /* Fcn: '<S14>/Fcn' incorporates:
       *  Fcn: '<S14>/Fcn1'
       *  Inport: '<Root>/theta_el'
       */
      Switch_idx_0 = (real32_T)sin(FOC_6ph0_U->theta_el);

      /* Fcn: '<S14>/Fcn' incorporates:
       *  Inport: '<Root>/theta_el'
       *  MATLAB Function: '<S2>/6ph_PMSM_30deg_VSD1'
       */
      FOC_6ph0_B->Fcn_l = A[0] * (real32_T)cos(FOC_6ph0_U->theta_el) + A[1] *
        Switch_idx_0;

      /* Fcn: '<S14>/Fcn1' incorporates:
       *  Inport: '<Root>/theta_el'
       *  MATLAB Function: '<S2>/6ph_PMSM_30deg_VSD1'
       */
      FOC_6ph0_B->Fcn1_a = -A[0] * Switch_idx_0 + A[1] * (real32_T)cos
        (FOC_6ph0_U->theta_el);
    }

    /* End of Outputs for SubSystem: '<S4>/Subsystem1' */

    /* Switch: '<S4>/Switch' */
    if (FOC_6ph0_ConstB.Compare != 0) {
      /* Switch: '<S4>/Switch' */
      Switch_idx_0 = FOC_6ph0_B->Fcn_l;
      Switch_idx_1 = FOC_6ph0_B->Fcn1_a;
    } else {
      /* Switch: '<S4>/Switch' */
      Switch_idx_0 = FOC_6ph0_B->Fcn_lr;
      Switch_idx_1 = FOC_6ph0_B->Fcn1_k;
    }

    /* End of Switch: '<S4>/Switch' */

    /* DataTypeConversion: '<S2>/Data Type Conversion8' incorporates:
     *  Inport: '<Root>/id_ref'
     *  Sum: '<S2>/Sum3'
     */
    rtb_IntegralGain = FOC_6ph0_U->id_ref - Switch_idx_0;

    /* DiscreteIntegrator: '<S98>/Integrator' */
    if (FOC_6ph0_DW->Integrator_SYSTEM_ENABLE != 0) {
      /* DiscreteIntegrator: '<S98>/Integrator' */
      Integrator = FOC_6ph0_DW->Integrator_DSTATE;
    } else {
      /* DiscreteIntegrator: '<S98>/Integrator' */
      Integrator = 5.0E-5 * (real_T)superStateFOC_ELAPS_T
        * FOC_6ph0_DW->Integrator_PREV_U + FOC_6ph0_DW->Integrator_DSTATE;
    }

    /* End of DiscreteIntegrator: '<S98>/Integrator' */

    /* Gain: '<S96>/Proportional Gain' incorporates:
     *  Sum: '<S107>/Sum'
     */
    rtb_SignPreSat = (rtb_IntegralGain + Integrator) * Kpd;

    /* Saturate: '<S105>/Saturation' */
    if (rtb_SignPreSat > u_dc) {
      rtb_CMP_W = u_dc;
    } else if (rtb_SignPreSat < -u_dc) {
      rtb_CMP_W = -u_dc;
    } else {
      rtb_CMP_W = rtb_SignPreSat;
    }

    /* End of Saturate: '<S105>/Saturation' */

    /* DataTypeConversion: '<S2>/Data Type Conversion7' incorporates:
     *  Inport: '<Root>/n_RPM'
     *  Inport: '<Root>/n_ref_RPM'
     *  Sum: '<S2>/Sum1'
     */
    rtb_IntegralGain_a = FOC_6ph0_U->n_ref_RPM - FOC_6ph0_U->n_RPM;

    /* DiscreteIntegrator: '<S48>/Integrator' */
    if (FOC_6ph0_DW->Integrator_SYSTEM_ENABLE_e != 0) {
      /* DiscreteIntegrator: '<S48>/Integrator' */
      Integrator_e = FOC_6ph0_DW->Integrator_DSTATE_m;
    } else {
      /* DiscreteIntegrator: '<S48>/Integrator' */
      Integrator_e = 5.0E-5 * (real_T)superStateFOC_ELAPS_T
        * FOC_6ph0_DW->Integrator_PREV_U_j + FOC_6ph0_DW->Integrator_DSTATE_m;
    }

    /* End of DiscreteIntegrator: '<S48>/Integrator' */

    /* Gain: '<S46>/Proportional Gain' incorporates:
     *  Sum: '<S57>/Sum'
     */
    rtb_ProportionalGain = (rtb_IntegralGain_a + Integrator_e) * Kpn;

    /* Switch: '<S2>/Switch1' incorporates:
     *  Inport: '<Root>/currentORspeedControl'
     *  Inport: '<Root>/iq_ref'
     */
    if (FOC_6ph0_U->currentORspeedControl) {
      /* Saturate: '<S55>/Saturation' */
      if (rtb_ProportionalGain > 20.0) {
        rtb_SignPreSat_i = 20.0;
      } else if (rtb_ProportionalGain < -20.0) {
        rtb_SignPreSat_i = -20.0;
      } else {
        rtb_SignPreSat_i = rtb_ProportionalGain;
      }

      /* End of Saturate: '<S55>/Saturation' */
    } else {
      rtb_SignPreSat_i = FOC_6ph0_U->iq_ref;
    }

    /* End of Switch: '<S2>/Switch1' */

    /* Sum: '<S2>/Sum4' */
    rtb_IntegralGain_o = rtb_SignPreSat_i - Switch_idx_1;

    /* DiscreteIntegrator: '<S148>/Integrator' */
    if (FOC_6ph0_DW->Integrator_SYSTEM_ENABLE_m != 0) {
      /* DiscreteIntegrator: '<S148>/Integrator' */
      Integrator_c = FOC_6ph0_DW->Integrator_DSTATE_e;
    } else {
      /* DiscreteIntegrator: '<S148>/Integrator' */
      Integrator_c = 5.0E-5 * (real_T)superStateFOC_ELAPS_T
        * FOC_6ph0_DW->Integrator_PREV_U_a + FOC_6ph0_DW->Integrator_DSTATE_e;
    }

    /* End of DiscreteIntegrator: '<S148>/Integrator' */

    /* Gain: '<S146>/Proportional Gain' incorporates:
     *  Sum: '<S157>/Sum'
     */
    rtb_SignPreSat_i = (rtb_IntegralGain_o + Integrator_c) * Kpq;

    /* Saturate: '<S155>/Saturation' */
    if (rtb_SignPreSat_i > u_dc) {
      rtb_SignP = u_dc;
    } else if (rtb_SignPreSat_i < -u_dc) {
      rtb_SignP = -u_dc;
    } else {
      rtb_SignP = rtb_SignPreSat_i;
    }

    /* End of Saturate: '<S155>/Saturation' */

    /* Outport: '<Root>/ud_ctrl' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion'
     */
    FOC_6ph0_Y->ud_ctrl = (real32_T)rtb_CMP_W;

    /* Outport: '<Root>/uq_ctrl' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion'
     */
    FOC_6ph0_Y->uq_ctrl = (real32_T)rtb_SignP;

    /* Outputs for Enabled SubSystem: '<S10>/Subsystem1' incorporates:
     *  EnablePort: '<S168>/Enable'
     */
    if (FOC_6ph0_ConstB.Compare_d > 0) {
      /* Fcn: '<S168>/Fcn' incorporates:
       *  Fcn: '<S168>/Fcn1'
       *  Inport: '<Root>/theta_el'
       */
      rtb_Switch_f_idx_0 = (real32_T)sin(FOC_6ph0_U->theta_el);
      rtb_Switch_f_idx_1 = (real32_T)cos(FOC_6ph0_U->theta_el);

      /* Fcn: '<S168>/Fcn' incorporates:
       *  DataTypeConversion: '<S2>/Data Type Conversion'
       */
      FOC_6ph0_B->Fcn = (real32_T)rtb_CMP_W * rtb_Switch_f_idx_1 - (real32_T)
        rtb_SignP * rtb_Switch_f_idx_0;

      /* Fcn: '<S168>/Fcn1' incorporates:
       *  DataTypeConversion: '<S2>/Data Type Conversion'
       */
      FOC_6ph0_B->Fcn1 = (real32_T)rtb_CMP_W * rtb_Switch_f_idx_0 + (real32_T)
        rtb_SignP * rtb_Switch_f_idx_1;
    }

    /* End of Outputs for SubSystem: '<S10>/Subsystem1' */

    /* Outputs for Enabled SubSystem: '<S10>/Subsystem - pi//2 delay' incorporates:
     *  EnablePort: '<S167>/Enable'
     */
    if (FOC_6ph0_ConstB.Compare_f > 0) {
      /* Fcn: '<S167>/Fcn' incorporates:
       *  DataTypeConversion: '<S2>/Data Type Conversion'
       *  Inport: '<Root>/theta_el'
       */
      FOC_6ph0_B->Fcn_o = (real32_T)rtb_CMP_W * (real32_T)sin
        (FOC_6ph0_U->theta_el) + (real32_T)rtb_SignP * (real32_T)cos
        (FOC_6ph0_U->theta_el);

      /* Fcn: '<S167>/Fcn1' incorporates:
       *  DataTypeConversion: '<S2>/Data Type Conversion'
       *  Inport: '<Root>/theta_el'
       */
      FOC_6ph0_B->Fcn1_h = -(real32_T)rtb_CMP_W * (real32_T)cos
        (FOC_6ph0_U->theta_el) + (real32_T)rtb_SignP * (real32_T)sin
        (FOC_6ph0_U->theta_el);
    }

    /* End of Outputs for SubSystem: '<S10>/Subsystem - pi//2 delay' */

    /* Switch: '<S10>/Switch' */
    if (FOC_6ph0_ConstB.Compare_d != 0) {
      rtb_Switch_f_idx_0 = FOC_6ph0_B->Fcn;
      rtb_Switch_f_idx_1 = FOC_6ph0_B->Fcn1;
    } else {
      rtb_Switch_f_idx_0 = FOC_6ph0_B->Fcn_o;
      rtb_Switch_f_idx_1 = FOC_6ph0_B->Fcn1_h;
    }

    /* End of Switch: '<S10>/Switch' */

    /* MATLAB Function: '<S2>/RZM_Traegerbasiert1' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion17'
     *  DataTypeConversion: '<S2>/Data Type Conversion18'
     *  DataTypeConversion: '<S2>/Data Type Conversion19'
     *  DataTypeConversion: '<S2>/Data Type Conversion4'
     *  Gain: '<S2>/Gain1'
     *  Inport: '<Root>/PERIOD'
     *  Inport: '<Root>/u_dc'
     *  RealImagToComplex: '<S2>/Real-Imag to Complex'
     */
    FOC_6ph0_RZM_Traegerbasiert((real_T)(0.866025388F * rtb_Switch_f_idx_0 -
      -0.5F * rtb_Switch_f_idx_1), (real_T)(0.866025388F * rtb_Switch_f_idx_1 +
      -0.5F * rtb_Switch_f_idx_0), (real_T)FOC_6ph0_U->u_dc_d, (real_T)
      FOC_6ph0_U->PERIOD_k, &rtb_SignP, &rtb_CMP_W, &rtb_CMP_U, &rtb_sector);

    /* Outport: '<Root>/CMPA_4' incorporates:
     *  Gain: '<S2>/Gain5'
     */
    FOC_6ph0_Y->CMPA_4 = 1.0 / PERIOD * rtb_SignP;

    /* Outport: '<Root>/CMPA_5' incorporates:
     *  Gain: '<S2>/Gain6'
     */
    FOC_6ph0_Y->CMPA_5 = 1.0 / PERIOD * rtb_CMP_W;

    /* Outport: '<Root>/CMPA_6' incorporates:
     *  Gain: '<S2>/Gain7'
     */
    FOC_6ph0_Y->CMPA_6 = 1.0 / PERIOD * rtb_CMP_U;

    /* MATLAB Function: '<S2>/RZM_Traegerbasiert' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion1'
     *  DataTypeConversion: '<S2>/Data Type Conversion2'
     *  DataTypeConversion: '<S2>/Data Type Conversion3'
     *  DataTypeConversion: '<S2>/Data Type Conversion5'
     *  Inport: '<Root>/PERIOD'
     *  Inport: '<Root>/u_dc'
     */
    FOC_6ph0_RZM_Traegerbasiert((real_T)rtb_Switch_f_idx_0, (real_T)
      rtb_Switch_f_idx_1, (real_T)FOC_6ph0_U->u_dc_d, (real_T)
      FOC_6ph0_U->PERIOD_k, &rtb_CMP_U, &rtb_SignP, &rtb_CMP_W, &rtb_sector);

    /* Outport: '<Root>/CMPA_2' incorporates:
     *  Gain: '<S2>/Gain3'
     */
    FOC_6ph0_Y->CMPA_2 = 1.0 / PERIOD * rtb_SignP;

    /* DeadZone: '<S141>/DeadZone' */
    if (rtb_SignPreSat_i > u_dc) {
      rtb_SignPreSat_i -= u_dc;
    } else if (rtb_SignPreSat_i >= -u_dc) {
      rtb_SignPreSat_i = 0.0;
    } else {
      rtb_SignPreSat_i -= -u_dc;
    }

    /* End of DeadZone: '<S141>/DeadZone' */

    /* Gain: '<S145>/Integral Gain' */
    rtb_IntegralGain_o *= 1.0 / Tnq;

    /* Signum: '<S139>/SignPreSat' */
    if (rtb_SignPreSat_i < 0.0) {
      rtb_SignP = -1.0;
    } else if (rtb_SignPreSat_i > 0.0) {
      rtb_SignP = 1.0;
    } else {
      rtb_SignP = rtb_SignPreSat_i;
    }

    /* End of Signum: '<S139>/SignPreSat' */

    /* DataTypeConversion: '<S139>/DataTypeConv1' */
    rtb_SignP_0 = fmod(rtb_SignP, 256.0);

    /* Signum: '<S139>/SignPreIntegrator' */
    if (rtb_IntegralGain_o < 0.0) {
      rtb_SignP = -1.0;
    } else if (rtb_IntegralGain_o > 0.0) {
      rtb_SignP = 1.0;
    } else {
      rtb_SignP = rtb_IntegralGain_o;
    }

    /* End of Signum: '<S139>/SignPreIntegrator' */

    /* DataTypeConversion: '<S139>/DataTypeConv2' */
    tmp_1 = fmod(rtb_SignP, 256.0);

    /* RelationalOperator: '<S139>/Equal1' incorporates:
     *  DataTypeConversion: '<S139>/DataTypeConv1'
     *  DataTypeConversion: '<S139>/DataTypeConv2'
     */
    rtb_Equal2 = ((rtb_SignP_0 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)
                   -rtb_SignP_0 : (int32_T)(int8_T)(uint8_T)rtb_SignP_0) ==
                  (tmp_1 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-tmp_1 :
                   (int32_T)(int8_T)(uint8_T)tmp_1));

    /* Signum: '<S139>/SignP' incorporates:
     *  Constant: '<S152>/P Copy'
     */
    if (Kpq < 0.0) {
      rtb_SignP_0 = -1.0;
    } else if (Kpq > 0.0) {
      rtb_SignP_0 = 1.0;
    } else {
      rtb_SignP_0 = Kpq;
    }

    /* End of Signum: '<S139>/SignP' */

    /* DataTypeConversion: '<S139>/DataTypeConv4' */
    rtb_SignP_0 = fmod(rtb_SignP_0, 256.0);

    /* RelationalOperator: '<S139>/Equal2' incorporates:
     *  Constant: '<S139>/Constant'
     *  DataTypeConversion: '<S139>/DataTypeConv4'
     */
    rtb_Equal1 = ((rtb_SignP_0 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)
                   -rtb_SignP_0 : (int32_T)(int8_T)(uint8_T)rtb_SignP_0) == 1);

    /* Logic: '<S139>/AND1' */
    rtb_AND1 = (rtb_Equal2 && rtb_Equal1);

    /* Logic: '<S139>/AND2' incorporates:
     *  Logic: '<S139>/NOT1'
     *  Logic: '<S139>/NOT2'
     */
    rtb_AND2 = ((!rtb_Equal2) && (!rtb_Equal1));

    /* DeadZone: '<S41>/DeadZone' */
    if (rtb_ProportionalGain > 20.0) {
      rtb_SignP = rtb_ProportionalGain - 20.0;
    } else if (rtb_ProportionalGain >= -20.0) {
      rtb_SignP = 0.0;
    } else {
      rtb_SignP = rtb_ProportionalGain - -20.0;
    }

    /* End of DeadZone: '<S41>/DeadZone' */

    /* Gain: '<S45>/Integral Gain' */
    rtb_IntegralGain_a *= 1.0 / Tnn;

    /* Signum: '<S39>/SignPreSat' */
    if (rtb_SignP < 0.0) {
      rtb_SignP_0 = -1.0;
    } else if (rtb_SignP > 0.0) {
      rtb_SignP_0 = 1.0;
    } else {
      rtb_SignP_0 = rtb_SignP;
    }

    /* End of Signum: '<S39>/SignPreSat' */

    /* DataTypeConversion: '<S39>/DataTypeConv1' */
    rtb_SignP_0 = fmod(rtb_SignP_0, 256.0);

    /* Signum: '<S39>/SignPreIntegrator' */
    if (rtb_IntegralGain_a < 0.0) {
      rtb_ProportionalGain = -1.0;
    } else if (rtb_IntegralGain_a > 0.0) {
      rtb_ProportionalGain = 1.0;
    } else {
      rtb_ProportionalGain = rtb_IntegralGain_a;
    }

    /* End of Signum: '<S39>/SignPreIntegrator' */

    /* DataTypeConversion: '<S39>/DataTypeConv2' */
    tmp_1 = fmod(rtb_ProportionalGain, 256.0);

    /* RelationalOperator: '<S39>/Equal1' incorporates:
     *  DataTypeConversion: '<S39>/DataTypeConv1'
     *  DataTypeConversion: '<S39>/DataTypeConv2'
     */
    rtb_Equal1 = ((rtb_SignP_0 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)
                   -rtb_SignP_0 : (int32_T)(int8_T)(uint8_T)rtb_SignP_0) ==
                  (tmp_1 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-tmp_1 :
                   (int32_T)(int8_T)(uint8_T)tmp_1));

    /* Signum: '<S39>/SignP' incorporates:
     *  Constant: '<S52>/P Copy'
     */
    if (Kpn < 0.0) {
      rtb_SignP_0 = -1.0;
    } else if (Kpn > 0.0) {
      rtb_SignP_0 = 1.0;
    } else {
      rtb_SignP_0 = Kpn;
    }

    /* End of Signum: '<S39>/SignP' */

    /* DataTypeConversion: '<S39>/DataTypeConv4' */
    rtb_SignP_0 = fmod(rtb_SignP_0, 256.0);

    /* RelationalOperator: '<S39>/Equal2' incorporates:
     *  Constant: '<S39>/Constant'
     *  DataTypeConversion: '<S39>/DataTypeConv4'
     */
    rtb_Equal2 = ((rtb_SignP_0 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)
                   -rtb_SignP_0 : (int32_T)(int8_T)(uint8_T)rtb_SignP_0) == 1);

    /* Logic: '<S39>/AND1' */
    rtb_AND1_kl = (rtb_Equal1 && rtb_Equal2);

    /* Logic: '<S39>/AND2' incorporates:
     *  Logic: '<S39>/NOT1'
     *  Logic: '<S39>/NOT2'
     */
    rtb_AND2_a = ((!rtb_Equal1) && (!rtb_Equal2));

    /* DeadZone: '<S91>/DeadZone' */
    if (rtb_SignPreSat > u_dc) {
      rtb_SignPreSat -= u_dc;
    } else if (rtb_SignPreSat >= -u_dc) {
      rtb_SignPreSat = 0.0;
    } else {
      rtb_SignPreSat -= -u_dc;
    }

    /* End of DeadZone: '<S91>/DeadZone' */

    /* Gain: '<S95>/Integral Gain' */
    rtb_IntegralGain *= 1.0 / Tnd;

    /* Signum: '<S89>/SignPreSat' */
    if (rtb_SignPreSat < 0.0) {
      rtb_SignP_0 = -1.0;
    } else if (rtb_SignPreSat > 0.0) {
      rtb_SignP_0 = 1.0;
    } else {
      rtb_SignP_0 = rtb_SignPreSat;
    }

    /* End of Signum: '<S89>/SignPreSat' */

    /* DataTypeConversion: '<S89>/DataTypeConv1' */
    rtb_SignP_0 = fmod(rtb_SignP_0, 256.0);

    /* Signum: '<S89>/SignPreIntegrator' */
    if (rtb_IntegralGain < 0.0) {
      rtb_ProportionalGain = -1.0;
    } else if (rtb_IntegralGain > 0.0) {
      rtb_ProportionalGain = 1.0;
    } else {
      rtb_ProportionalGain = rtb_IntegralGain;
    }

    /* End of Signum: '<S89>/SignPreIntegrator' */

    /* DataTypeConversion: '<S89>/DataTypeConv2' */
    tmp_1 = fmod(rtb_ProportionalGain, 256.0);

    /* RelationalOperator: '<S89>/Equal1' incorporates:
     *  DataTypeConversion: '<S89>/DataTypeConv1'
     *  DataTypeConversion: '<S89>/DataTypeConv2'
     */
    rtb_Equal1 = ((rtb_SignP_0 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)
                   -rtb_SignP_0 : (int32_T)(int8_T)(uint8_T)rtb_SignP_0) ==
                  (tmp_1 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-tmp_1 :
                   (int32_T)(int8_T)(uint8_T)tmp_1));

    /* Signum: '<S89>/SignP' incorporates:
     *  Constant: '<S102>/P Copy'
     */
    if (Kpd < 0.0) {
      rtb_SignP_0 = -1.0;
    } else if (Kpd > 0.0) {
      rtb_SignP_0 = 1.0;
    } else {
      rtb_SignP_0 = Kpd;
    }

    /* End of Signum: '<S89>/SignP' */

    /* DataTypeConversion: '<S89>/DataTypeConv4' */
    rtb_SignP_0 = fmod(rtb_SignP_0, 256.0);

    /* RelationalOperator: '<S89>/Equal2' incorporates:
     *  Constant: '<S89>/Constant'
     *  DataTypeConversion: '<S89>/DataTypeConv4'
     */
    rtb_Equal2 = ((rtb_SignP_0 < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)
                   -rtb_SignP_0 : (int32_T)(int8_T)(uint8_T)rtb_SignP_0) == 1);

    /* Update for DiscreteIntegrator: '<S98>/Integrator' */
    FOC_6ph0_DW->Integrator_SYSTEM_ENABLE = 0U;
    FOC_6ph0_DW->Integrator_DSTATE = Integrator;
    FOC_6ph0_DW->Integrator_PrevResetState = 0;

    /* Switch: '<S89>/Switch' incorporates:
     *  Logic: '<S89>/AND1'
     *  Logic: '<S89>/AND2'
     *  Logic: '<S89>/AND3'
     *  Logic: '<S89>/NOT1'
     *  Logic: '<S89>/NOT2'
     *  Logic: '<S89>/OR1'
     *  RelationalOperator: '<S89>/NotEqual'
     */
    if ((0.0 != rtb_SignPreSat) && ((rtb_Equal1 && rtb_Equal2) || ((!rtb_Equal1)
          && (!rtb_Equal2)))) {
      /* Update for DiscreteIntegrator: '<S98>/Integrator' incorporates:
       *  Constant: '<S89>/Constant1'
       */
      FOC_6ph0_DW->Integrator_PREV_U = 0.0;
    } else {
      /* Update for DiscreteIntegrator: '<S98>/Integrator' */
      FOC_6ph0_DW->Integrator_PREV_U = rtb_IntegralGain;
    }

    /* End of Switch: '<S89>/Switch' */

    /* Update for DiscreteIntegrator: '<S48>/Integrator' */
    FOC_6ph0_DW->Integrator_SYSTEM_ENABLE_e = 0U;
    FOC_6ph0_DW->Integrator_DSTATE_m = Integrator_e;

    /* Switch: '<S39>/Switch' incorporates:
     *  Gain: '<S39>/ZeroGain'
     *  Logic: '<S39>/AND3'
     *  Logic: '<S39>/OR1'
     *  RelationalOperator: '<S39>/NotEqual'
     */
    if ((0.0 != rtb_SignP) && (rtb_AND1_kl || rtb_AND2_a)) {
      /* Update for DiscreteIntegrator: '<S48>/Integrator' incorporates:
       *  Constant: '<S39>/Constant1'
       */
      FOC_6ph0_DW->Integrator_PREV_U_j = 0.0;
    } else {
      /* Update for DiscreteIntegrator: '<S48>/Integrator' */
      FOC_6ph0_DW->Integrator_PREV_U_j = rtb_IntegralGain_a;
    }

    /* End of Switch: '<S39>/Switch' */

    /* Update for DiscreteIntegrator: '<S148>/Integrator' */
    FOC_6ph0_DW->Integrator_SYSTEM_ENABLE_m = 0U;
    FOC_6ph0_DW->Integrator_DSTATE_e = Integrator_c;
    FOC_6ph0_DW->Integrator_PrevResetState_c = 0;

    /* Switch: '<S139>/Switch' incorporates:
     *  Logic: '<S139>/AND3'
     *  Logic: '<S139>/OR1'
     *  RelationalOperator: '<S139>/NotEqual'
     */
    if ((0.0 != rtb_SignPreSat_i) && (rtb_AND1 || rtb_AND2)) {
      /* Update for DiscreteIntegrator: '<S148>/Integrator' incorporates:
       *  Constant: '<S139>/Constant1'
       */
      FOC_6ph0_DW->Integrator_PREV_U_a = 0.0;
    } else {
      /* Update for DiscreteIntegrator: '<S148>/Integrator' */
      FOC_6ph0_DW->Integrator_PREV_U_a = rtb_IntegralGain_o;
    }

    /* End of Switch: '<S139>/Switch' */

    /* Outport: '<Root>/CMPA_1' incorporates:
     *  Gain: '<S2>/Gain2'
     */
    FOC_6ph0_Y->CMPA_1 = 1.0 / PERIOD * rtb_CMP_U;

    /* Outport: '<Root>/CMPA_3' incorporates:
     *  Gain: '<S2>/Gain4'
     */
    FOC_6ph0_Y->CMPA_3 = 1.0 / PERIOD * rtb_CMP_W;

    /* DataTypeConversion: '<S2>/Data Type Conversion13' */
    rtb_SignP_0 = fmod(floor(rtb_sector), 4.294967296E+9);

    /* Outport: '<Root>/sector' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion13'
     */
    FOC_6ph0_Y->sector = rtb_SignP_0 < 0.0 ? -(int32_T)(uint32_T)-rtb_SignP_0 :
      (int32_T)(uint32_T)rtb_SignP_0;

    /* End of Outputs for SubSystem: '<S1>/superState.FOC' */

    /* Outport: '<Root>/id' */
    FOC_6ph0_Y->id = Switch_idx_0;

    /* Outputs for Function Call SubSystem: '<S1>/superState.FOC' */
    /* Outport: '<Root>/iq' incorporates:
     *  SignalConversion generated from: '<S2>/iq'
     */
    FOC_6ph0_Y->iq = Switch_idx_1;

    /* End of Outputs for SubSystem: '<S1>/superState.FOC' */

    /* During 'Init': '<S1>:1' */
    /* '<S1>:8:1' sf_internal_predicateOutput = NEXT == 1; */
  } else if (FOC_6ph0_U->NEXT) {
    /* Transition: '<S1>:8' */
    /* Exit 'Init': '<S1>:1' */
    FOC_6ph0_DW->is_superState = FOC_6ph_IN_FieldOrientedControl;

    /* Outport: '<Root>/activeState' */
    /* Entry 'FieldOrientedControl': '<S1>:4' */
    /* state 20 */
    /* '<S1>:4:4' activeState = 20; */
    FOC_6ph0_Y->activeState = 20U;
  }

  /* End of Chart: '<Root>/FOC_6ph' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 5.0E-5, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  FOC_6ph0_M->Timing.clockTick0++;
}

/* Model initialize function */
void FOC_6ph0_initialize(RT_MODEL_FOC_6ph0_T *const FOC_6ph0_M)
{
  DW_FOC_6ph0_T *FOC_6ph0_DW = FOC_6ph0_M->dwork;
  ExtY_FOC_6ph0_T *FOC_6ph0_Y = (ExtY_FOC_6ph0_T *) FOC_6ph0_M->outputs;
  B_FOC_6ph0_T *FOC_6ph0_B = FOC_6ph0_M->blockIO;
  ExtU_FOC_6ph0_T *FOC_6ph0_U = (ExtU_FOC_6ph0_T *) FOC_6ph0_M->inputs;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) FOC_6ph0_B), 0,
                sizeof(B_FOC_6ph0_T));

  /* states (dwork) */
  (void) memset((void *)FOC_6ph0_DW, 0,
                sizeof(DW_FOC_6ph0_T));

  /* external inputs */
  (void)memset(FOC_6ph0_U, 0, sizeof(ExtU_FOC_6ph0_T));

  /* external outputs */
  (void) memset((void *)FOC_6ph0_Y, 0,
                sizeof(ExtY_FOC_6ph0_T));
  FOC_6ph0_DW->is_superState = FOC_6ph0_IN_NO_ACTIVE_CHILD;
  FOC_6ph0_DW->is_active_c33_FOC_6ph0 = 0U;

  /* SystemInitialize for Outport: '<Root>/activeState' */
  FOC_6ph0_Y->activeState = 0U;

  /* SystemInitialize for Outport: '<Root>/CMPA_1' */
  FOC_6ph0_Y->CMPA_1 = 0.0;

  /* SystemInitialize for Outport: '<Root>/CMPA_2' */
  FOC_6ph0_Y->CMPA_2 = 0.0;

  /* SystemInitialize for Outport: '<Root>/CMPA_3' */
  FOC_6ph0_Y->CMPA_3 = 0.0;

  /* SystemInitialize for Outport: '<Root>/sector' */
  FOC_6ph0_Y->sector = 0;

  /* SystemInitialize for Outport: '<Root>/CMPA_5' */
  FOC_6ph0_Y->CMPA_5 = 0.0;

  /* SystemInitialize for Outport: '<Root>/CMPA_6' */
  FOC_6ph0_Y->CMPA_6 = 0.0;

  /* SystemInitialize for Outport: '<Root>/CMPA_4' */
  FOC_6ph0_Y->CMPA_4 = 0.0;

  /* SystemInitialize for Outport: '<Root>/id' */
  FOC_6ph0_Y->id = 0.0F;

  /* SystemInitialize for Outport: '<Root>/iq' */
  FOC_6ph0_Y->iq = 0.0F;

  /* SystemInitialize for Outport: '<Root>/ud_ctrl' */
  FOC_6ph0_Y->ud_ctrl = 0.0F;

  /* SystemInitialize for Outport: '<Root>/uq_ctrl' */
  FOC_6ph0_Y->uq_ctrl = 0.0F;

  /* SystemInitialize for Chart: '<Root>/FOC_6ph' incorporates:
   *  SubSystem: '<S1>/superState.FOC'
   */
  /* InitializeConditions for DiscreteIntegrator: '<S98>/Integrator' */
  FOC_6ph0_DW->Integrator_PrevResetState = 2;
  FOC_6ph0_DW->Integrator_PREV_U = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S48>/Integrator' */
  FOC_6ph0_DW->Integrator_PREV_U_j = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S148>/Integrator' */
  FOC_6ph0_DW->Integrator_PrevResetState_c = 2;
  FOC_6ph0_DW->Integrator_PREV_U_a = 0.0;
}

/* Model terminate function */
void FOC_6ph0_terminate(RT_MODEL_FOC_6ph0_T *const FOC_6ph0_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(FOC_6ph0_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
