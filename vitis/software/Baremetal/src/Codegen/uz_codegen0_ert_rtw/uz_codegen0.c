/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 10.2
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Mon Jul 27 15:43:14 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "uz_codegen0.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>

/* Named constants for Chart: '<S4>/state_chart' */
#define IN_Error                       ((uint8_T)1U)
#define IN_Idle                        ((uint8_T)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_NoError                     ((uint8_T)2U)
#define IN_Ready                       ((uint8_T)2U)
#define IN_Run                         ((uint8_T)3U)
#define IN_Run_j                       ((uint8_T)1U)
#define IN_Stromregelung               ((uint8_T)1U)
#define IN_Trapez                      ((uint8_T)2U)
#define IN_Warten                      ((uint8_T)2U)
#define IN_nCtrl                       ((uint8_T)3U)

const Bus_ZM_Out uz_codegen0_rtZBus_ZM_Out = {
  false,                               /* En_Traj */
  false,                               /* Pulsfreigabe */
  Error_Status,                        /* Ist_Status */
  Error,                               /* Ist_Regelungsart */
  0.0F,                                /* Soll_Drehzahl */
  0.0F,                                /* Soll_id */
  0.0F,                                /* Soll_iq */
  false,                               /* pwr_en */
  false,                               /* board_en */
  false                                /* reset */
};                                     /* Bus_ZM_Out ground */

/* Exported block parameters */
Bus_Ctrl_Config struct_Ctrl_Config = {
  5.0e-5F,
  5.0e-5F,
  0.004F,
  92.0F,
  0.0001F,
  0.0004F,
  57.4889374F,
  0.15121232F,
  -0.15121232F,
  0.2F,
  5.0e-6F,
  5.0e-7F
} ;                                    /* Variable: struct_Ctrl_Config
                                        * Referenced by:
                                        *   '<S5>/Constant'
                                        *   '<S5>/Constant2'
                                        *   '<S5>/Switch1'
                                        *   '<S5>/Switch2'
                                        *   '<S5>/Switch3'
                                        *   '<S5>/Switch4'
                                        *   '<S9>/Constant3'
                                        *   '<S12>/Constant'
                                        *   '<S12>/Constant3'
                                        *   '<S14>/Constant3'
                                        *   '<S26>/Constant'
                                        *   '<S26>/Constant3'
                                        *   '<S27>/Constant'
                                        *   '<S27>/Constant3'
                                        */

Bus_PMSM_Config struct_PMSM_Config = {
  1.8F,
  0.1423F,
  0.0072F,
  0.0072F,
  4.0F,
  0.000875F,
  5700.0F,
  4.3F,
  20.9F,
  0.1F,
  0.001F
} ;                                    /* Variable: struct_PMSM_Config
                                        * Referenced by:
                                        *   '<S9>/Constant2'
                                        *   '<S11>/Constant'
                                        *   '<S20>/Constant'
                                        *   '<S22>/Gain'
                                        *   '<S24>/Constant'
                                        *   '<S25>/Constant'
                                        *   '<S25>/Constant1'
                                        */

Bus_Inv_Config struct_Inv_Config = {
  PT1,
  678.0F,
  1.0F,
  40000.0F,
  false
} ;                                    /* Variable: struct_Inv_Config
                                        * Referenced by:
                                        *   '<S2>/Constant'
                                        *   '<S19>/Constant2'
                                        */

static void MinimaleSchaltzeit(const real32_T rtu_Dutycycle[3], real32_T
  rty_Out1[3]);
static void raumzeigermodulation(real32_T rtu_Ualpha, real32_T rtu_Ubeta,
  real32_T rtu_Udc, real32_T *rty_Dutycycle_A, real32_T *rty_Dutycycle_B,
  real32_T *rty_Dutycycle_C, real32_T *rty_Sektor, real32_T *rty_Quadrant);
static void Raumzeigermodulation(real32_T rtu_Ualpha, real32_T rtu_Ubeta,
  real32_T rty_Dutycycle_A[3]);
static real32_T Drehzahlregelung(real32_T rtu_Soll_Drehzahl, real32_T rtu_omega,
  DW_Drehzahlregelung_i *localDW);
static void Drehzahlregelung_k_Init(boolean_T *rty_Dis);
static void Drehzahlregelung_j(boolean_T rtu_Enable, real32_T rtu_omega, const
  Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_2, boolean_T *rty_Dis, real32_T
  *rty_Soll_Moment, DW_Drehzahlregelung *localDW);
static void IDQCtrl(real32_T rtu_ID, real32_T rtu_IQ, real32_T rtu_IDRef,
                    real32_T rtu_IQRef, real32_T rtu_OmegaMech, real32_T *rty_UD,
                    real32_T *rty_UQ, DW_IDQCtrl *localDW);
static boolean_T Ueberstromabschaltung(real32_T rtu_Iu, real32_T rtu_Iv,
  real32_T rtu_Iw);
static void abc_zu_dq(real32_T rtu_theta, real32_T rtu_pmsm_Iu, real32_T
                      rtu_pmsm_Iv, real32_T rtu_pmsm_Iw, real32_T *rty_ctrl_Id,
                      real32_T *rty_ctrl_Iq);
static void dq_zu_alphabeta(real32_T rtu_theta, real32_T rtu_valD, real32_T
  rtu_valQ, real32_T *rty_valAlpha, real32_T *rty_valBeta);
static void Stromregelung(real32_T rtu_Soll_Moment, const Bus_PMSM_Out
  *rtu_Bus_Live_Out_PMSM_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  real32_T *rty_Ualpha, real32_T *rty_Ubeta, DW_Stromregelung *localDW);
static void Regelung_Init(boolean_T *rty_Dis);
static void Regelung(boolean_T rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_2, real32_T *rty_Ualpha, real32_T
                     *rty_Ubeta, boolean_T *rty_Dis, DW_Regelung *localDW);
static void state_chart_Init(Bus_ZM_Out *rty_Bus_ZM_Out, DW_state_chart *localDW);
static void state_chart(const Bus_ZM_In *rtu_Bus_ZM_In, boolean_T rtu_Dis,
  Bus_ZM_Out *rty_Bus_ZM_Out, DW_state_chart *localDW);
static void Zustandsmaschine_Init(Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1,
  DW_Zustandsmaschine *localDW);
static void Zustandsmaschine(const Bus_ZM_In *rtu_Bus_ZM_In_Inport_1, boolean_T
  rtu_ZM_In_Dis_Traj, Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1, DW_Zustandsmaschine *
  localDW);
const Bus_Ctrl_Out uz_codegen0_rtZBus_Ctrl_Out = { { 0.0F, 0.0F, 0.0F },/* Dutycycle */
  false,                               /* act_pwm */
  0.0F,                                /* ctrl_Ualpha */
  0.0F,                                /* ctrl_Ubeta */
  false,                               /* pwr_en */
  false,                               /* board_en */
  false                                /* reset */
};

const Bus_ZM_In uz_codegen0_rtZBus_ZM_In = { 0.0F,/* Soll_Drehzahl */
  0.0F,                                /* Soll_id */
  0.0F,                                /* Soll_iq */
  false,                               /* Start_Traj */
  false,                               /* Fehlermeldung */
  Error_Status,                        /* Soll_Status */
  Error,                               /* Soll_Regelungsart */
  false,                               /* Inv_Ready */
  idle_state,                          /* UZ_Platform_State */
  false                                /* IGBT_desat */
};

/* Output and update for atomic system: '<S2>/MinimaleSchaltzeit' */
static void MinimaleSchaltzeit(const real32_T rtu_Dutycycle[3], real32_T
  rty_Out1[3])
{
  real32_T rtb_Switch1_idx_0;
  real32_T rtb_Switch1_idx_1;
  real32_T rtb_Switch1_idx_2;
  real32_T tmp;

  /* Switch: '<S5>/Switch2' */
  tmp = struct_Ctrl_Config.IGBT_dc_min / 2.0F;

  /* Switch: '<S5>/Switch1' incorporates:
   *  Constant: '<S5>/Constant1'
   *  Switch: '<S5>/Switch2'
   */
  if (rtu_Dutycycle[0] >= struct_Ctrl_Config.IGBT_dc_min) {
    rtb_Switch1_idx_0 = rtu_Dutycycle[0];
  } else if (rtu_Dutycycle[0] >= tmp) {
    /* Switch: '<S5>/Switch2' incorporates:
     *  Constant: '<S5>/Constant'
     */
    rtb_Switch1_idx_0 = struct_Ctrl_Config.IGBT_dc_min;
  } else {
    rtb_Switch1_idx_0 = 0.0F;
  }

  if (rtu_Dutycycle[1] >= struct_Ctrl_Config.IGBT_dc_min) {
    rtb_Switch1_idx_1 = rtu_Dutycycle[1];
  } else if (rtu_Dutycycle[1] >= tmp) {
    /* Switch: '<S5>/Switch2' incorporates:
     *  Constant: '<S5>/Constant'
     */
    rtb_Switch1_idx_1 = struct_Ctrl_Config.IGBT_dc_min;
  } else {
    rtb_Switch1_idx_1 = 0.0F;
  }

  if (rtu_Dutycycle[2] >= struct_Ctrl_Config.IGBT_dc_min) {
    rtb_Switch1_idx_2 = rtu_Dutycycle[2];
  } else if (rtu_Dutycycle[2] >= tmp) {
    /* Switch: '<S5>/Switch2' incorporates:
     *  Constant: '<S5>/Constant'
     */
    rtb_Switch1_idx_2 = struct_Ctrl_Config.IGBT_dc_min;
  } else {
    rtb_Switch1_idx_2 = 0.0F;
  }

  /* End of Switch: '<S5>/Switch1' */

  /* Switch: '<S5>/Switch4' incorporates:
   *  Constant: '<S5>/Constant2'
   *  Constant: '<S5>/Constant3'
   */
  tmp = 1.0F - tmp;
  if (rtb_Switch1_idx_0 >= tmp) {
    rty_Out1[0] = 1.0F;
  } else {
    rty_Out1[0] = 1.0F - struct_Ctrl_Config.IGBT_dc_min;
  }

  if (rtb_Switch1_idx_1 >= tmp) {
    rty_Out1[1] = 1.0F;
  } else {
    rty_Out1[1] = 1.0F - struct_Ctrl_Config.IGBT_dc_min;
  }

  if (rtb_Switch1_idx_2 >= tmp) {
    rty_Out1[2] = 1.0F;
  } else {
    rty_Out1[2] = 1.0F - struct_Ctrl_Config.IGBT_dc_min;
  }

  /* End of Switch: '<S5>/Switch4' */

  /* Switch: '<S5>/Switch3' */
  if (rtb_Switch1_idx_0 <= 1.0F - struct_Ctrl_Config.IGBT_dc_min) {
    rty_Out1[0] = rtb_Switch1_idx_0;
  }

  if (rtb_Switch1_idx_1 <= 1.0F - struct_Ctrl_Config.IGBT_dc_min) {
    rty_Out1[1] = rtb_Switch1_idx_1;
  }

  if (rtb_Switch1_idx_2 <= 1.0F - struct_Ctrl_Config.IGBT_dc_min) {
    rty_Out1[2] = rtb_Switch1_idx_2;
  }

  /* End of Switch: '<S5>/Switch3' */
}

/* Output and update for atomic system: '<S2>/raumzeigermodulation' */
static void raumzeigermodulation(real32_T rtu_Ualpha, real32_T rtu_Ubeta,
  real32_T rtu_Udc, real32_T *rty_Dutycycle_A, real32_T *rty_Dutycycle_B,
  real32_T *rty_Dutycycle_C, real32_T *rty_Sektor, real32_T *rty_Quadrant)
{
  int32_T Quadrant;
  int32_T Sektor;
  real32_T Dutycycle_A;
  real32_T a;
  real32_T abs_Ualpha;
  real32_T abs_Ubeta;
  real32_T c;

  /* MATLAB Function 'uz_codegen/Raumzeigermodulation/raumzeigermodulation': '<S6>:1' */
  /* '<S6>:1:2' DIVIDE_ONE_BY_SQRT_THREE = single(single(1) / sqrt(3)); */
  /* '<S6>:1:3' DIVIDE_ONE_BY_TWO_THIRDS = single(single(1) / (2/3)); */
  /* '<S6>:1:4' DIVIDE_TWO_BY_TWO_THIRDS = single(2 / (2/3)); */
  /* '<S6>:1:5' Sektor = single(0); */
  /* '<S6>:1:6' Quadrant = single(0); */
  /* '<S6>:1:7' Dutycycle_A = single(0); */
  /* '<S6>:1:8' Dutycycle_B = single(0); */
  /* '<S6>:1:9' Dutycycle_C = single(0); */
  /* '<S6>:1:11' abs_Ualpha = abs(Ualpha); */
  abs_Ualpha = fabsf(rtu_Ualpha);

  /* '<S6>:1:12' abs_Ubeta = abs(Ubeta); */
  /*  Parameter a,b und c berechnen */
  /* '<S6>:1:15' a = single(((abs_Ualpha + abs_Ubeta*DIVIDE_ONE_BY_SQRT_THREE)*DIVIDE_ONE_BY_TWO_THIRDS)/Udc); */
  abs_Ubeta = fabsf(rtu_Ubeta) * 0.577350259F;
  a = (abs_Ubeta + abs_Ualpha) * 1.5F / rtu_Udc;

  /* '<S6>:1:16' b = single(((abs_Ualpha - abs_Ubeta*DIVIDE_ONE_BY_SQRT_THREE)*DIVIDE_ONE_BY_TWO_THIRDS)/Udc); */
  abs_Ualpha = (abs_Ualpha - abs_Ubeta) * 1.5F / rtu_Udc;

  /* '<S6>:1:17' c = single((abs_Ubeta*DIVIDE_ONE_BY_SQRT_THREE*DIVIDE_TWO_BY_TWO_THIRDS)/Udc); */
  c = abs_Ubeta * 3.0F / rtu_Udc;

  /*  Sektor bestimmen */
  /* '<S6>:1:20' if Ubeta < 0 */
  if (rtu_Ubeta < 0.0F) {
    /* '<S6>:1:21' if Ualpha < 0.0 */
    if (rtu_Ualpha < 0.0F) {
      /* '<S6>:1:22' Quadrant = single(3); */
      Quadrant = 3;

      /* '<S6>:1:23' if b < 0 */
      if (abs_Ualpha < 0.0F) {
        /* '<S6>:1:24' Sektor = single(5); */
        Sektor = 5;
      } else {
        /* '<S6>:1:25' else */
        /* '<S6>:1:26' Sektor = single(4); */
        Sektor = 4;
      }
    } else {
      /* '<S6>:1:28' else */
      /* '<S6>:1:29' Quadrant = single(4); */
      Quadrant = 4;

      /* '<S6>:1:30' if b < 0 */
      if (abs_Ualpha < 0.0F) {
        /* '<S6>:1:31' Sektor = single(5); */
        Sektor = 5;
      } else {
        /* '<S6>:1:32' else */
        /* '<S6>:1:33' Sektor = single(6); */
        Sektor = 6;
      }
    }

    /* '<S6>:1:36' else */
    /* '<S6>:1:37' if Ualpha < 0 */
  } else if (rtu_Ualpha < 0.0F) {
    /* '<S6>:1:38' Quadrant = single(2); */
    Quadrant = 2;

    /* '<S6>:1:39' if b < 0 */
    if (abs_Ualpha < 0.0F) {
      /* '<S6>:1:40' Sektor = single(2); */
      Sektor = 2;
    } else {
      /* '<S6>:1:41' else */
      /* '<S6>:1:42' Sektor = single(3); */
      Sektor = 3;
    }
  } else {
    /* '<S6>:1:44' else */
    /* '<S6>:1:45' Quadrant = single(1); */
    Quadrant = 1;

    /* '<S6>:1:46' if b < 0 */
    if (abs_Ualpha < 0.0F) {
      /* '<S6>:1:47' Sektor = single(2); */
      Sektor = 2;
    } else {
      /* '<S6>:1:48' else */
      /* '<S6>:1:49' Sektor = single(1); */
      Sektor = 1;
    }
  }

  /* Dutycycle berechnen */
  /* '<S6>:1:55' switch Sektor */
  switch (Sektor) {
   case 1:
    /* '<S6>:1:57' case single(1) */
    /* '<S6>:1:58' Dutycycle_A = (single(1) + b + c); */
    Dutycycle_A = (abs_Ualpha + 1.0F) + c;

    /* '<S6>:1:59' Dutycycle_B = (single(1) - b + c); */
    abs_Ubeta = (1.0F - abs_Ualpha) + c;

    /* '<S6>:1:60' Dutycycle_C = (single(1) - b - c); */
    a = (1.0F - abs_Ualpha) - c;
    break;

   case 2:
    /* '<S6>:1:62' case 2 */
    /* '<S6>:1:63' if Quadrant == single(1) */
    if (Quadrant == 1) {
      /* '<S6>:1:64' Dutycycle_A = (single(1) + a + b); */
      Dutycycle_A = (a + 1.0F) + abs_Ualpha;

      /* '<S6>:1:65' Dutycycle_B = (single(1) + a - b); */
      abs_Ubeta = (a + 1.0F) - abs_Ualpha;

      /* '<S6>:1:66' Dutycycle_C = (single(1) - a + b); */
      a = (1.0F - a) + abs_Ualpha;
    } else {
      /* '<S6>:1:67' else */
      /* '<S6>:1:68' Dutycycle_A = (single(1) - a - b); */
      Dutycycle_A = (1.0F - a) - abs_Ualpha;

      /* '<S6>:1:69' Dutycycle_B = (single(1) + a - b); */
      abs_Ubeta = (a + 1.0F) - abs_Ualpha;

      /* '<S6>:1:70' Dutycycle_C = (single(1) - a + b); */
      a = (1.0F - a) + abs_Ualpha;
    }
    break;

   case 3:
    /* '<S6>:1:73' case 3 */
    /* '<S6>:1:74' Dutycycle_A = (single(1) - b - c); */
    Dutycycle_A = (1.0F - abs_Ualpha) - c;

    /* '<S6>:1:75' Dutycycle_B = (single(1) + b + c); */
    abs_Ubeta = (abs_Ualpha + 1.0F) + c;

    /* '<S6>:1:76' Dutycycle_C = (single(1) + b - c); */
    a = (abs_Ualpha + 1.0F) - c;
    break;

   case 4:
    /* '<S6>:1:78' case 4 */
    /* '<S6>:1:79' Dutycycle_A = (single(1) - b - c); */
    Dutycycle_A = (1.0F - abs_Ualpha) - c;

    /* '<S6>:1:80' Dutycycle_B = (single(1) + b - c); */
    abs_Ubeta = (abs_Ualpha + 1.0F) - c;

    /* '<S6>:1:81' Dutycycle_C = (single(1) + b + c); */
    a = (abs_Ualpha + 1.0F) + c;
    break;

   case 5:
    /* '<S6>:1:83' case 5 */
    /* '<S6>:1:84' if Quadrant == 3 */
    if (Quadrant == 3) {
      /* '<S6>:1:85' Dutycycle_A = (single(1) - a - b); */
      Dutycycle_A = (1.0F - a) - abs_Ualpha;

      /* '<S6>:1:86' Dutycycle_B = (single(1) - a + b); */
      abs_Ubeta = (1.0F - a) + abs_Ualpha;

      /* '<S6>:1:87' Dutycycle_C = (single(1) + a - b); */
      a = (a + 1.0F) - abs_Ualpha;
    } else {
      /* '<S6>:1:88' else */
      /* '<S6>:1:89' Dutycycle_A = (single(1) + b + a); */
      Dutycycle_A = (abs_Ualpha + 1.0F) + a;

      /* '<S6>:1:90' Dutycycle_B = (single(1) + b - a); */
      abs_Ubeta = (abs_Ualpha + 1.0F) - a;

      /* '<S6>:1:91' Dutycycle_C = (single(1) - b + a); */
      a += 1.0F - abs_Ualpha;
    }
    break;

   default:
    /* '<S6>:1:94' case 6 */
    /* '<S6>:1:95' Dutycycle_A = (single(1) + b + c); */
    Dutycycle_A = (abs_Ualpha + 1.0F) + c;

    /* '<S6>:1:96' Dutycycle_B = (single(1) - b - c); */
    abs_Ubeta = (1.0F - abs_Ualpha) - c;

    /* '<S6>:1:97' Dutycycle_C = (single(1) - b + c); */
    a = (1.0F - abs_Ualpha) + c;
    break;
  }

  /* '<S6>:1:101' Dutycycle_A =  Dutycycle_A * single(0.5); */
  *rty_Dutycycle_A = Dutycycle_A * 0.5F;

  /* '<S6>:1:102' Dutycycle_B =  Dutycycle_B * single(0.5); */
  *rty_Dutycycle_B = abs_Ubeta * 0.5F;

  /* '<S6>:1:103' Dutycycle_C =  Dutycycle_C * single(0.5); */
  *rty_Dutycycle_C = a * 0.5F;
  *rty_Sektor = (real32_T)Sektor;
  *rty_Quadrant = (real32_T)Quadrant;
}

/* Output and update for atomic system: '<S1>/Raumzeigermodulation' */
static void Raumzeigermodulation(real32_T rtu_Ualpha, real32_T rtu_Ubeta,
  real32_T rty_Dutycycle_A[3])
{
  real32_T rtb_TmpSignalConversionAtMinima[3];
  real32_T rtb_Quadrant;
  real32_T rtb_Sektor;

  /* SignalConversion generated from: '<S2>/MinimaleSchaltzeit' incorporates:
   *  Constant: '<S2>/Constant'
   *  MATLAB Function: '<S2>/raumzeigermodulation'
   */
  raumzeigermodulation(rtu_Ualpha, rtu_Ubeta, struct_Inv_Config.Udc,
                       &rtb_TmpSignalConversionAtMinima[0],
                       &rtb_TmpSignalConversionAtMinima[1],
                       &rtb_TmpSignalConversionAtMinima[2], &rtb_Sektor,
                       &rtb_Quadrant);

  /* Outputs for Atomic SubSystem: '<S2>/MinimaleSchaltzeit' */
  MinimaleSchaltzeit(rtb_TmpSignalConversionAtMinima, rty_Dutycycle_A);

  /* End of Outputs for SubSystem: '<S2>/MinimaleSchaltzeit' */
}

/* Output and update for atomic system: '<S8>/Drehzahlregelung' */
static real32_T Drehzahlregelung(real32_T rtu_Soll_Drehzahl, real32_T rtu_omega,
  DW_Drehzahlregelung_i *localDW)
{
  real32_T rty_M_Soll_0;
  real32_T UnitDelay_DSTATE_tmp;
  real32_T rtb_Add1_f;
  real32_T rtb_Product_j0;

  /* Product: '<S12>/Product' incorporates:
   *  Constant: '<S12>/Constant'
   *  Gain: '<S11>/Gain'
   *  Sum: '<S12>/Subtract'
   *  UnitDelay: '<S14>/Unit Delay'
   */
  rtb_Product_j0 = (localDW->UnitDelay_DSTATE - GAIN_RADS_TO_HZ * rtu_omega) *
    struct_Ctrl_Config.KPn;

  /* Sum: '<S12>/Add1' incorporates:
   *  UnitDelay: '<S12>/Unit Delay'
   */
  rtb_Add1_f = rtb_Product_j0 + localDW->UnitDelay_DSTATE_l;

  /* Switch: '<S15>/Switch2' incorporates:
   *  Constant: '<S11>/Constant'
   *  Gain: '<S11>/Gain1'
   *  RelationalOperator: '<S15>/LowerRelop1'
   *  RelationalOperator: '<S15>/UpperRelop'
   *  Switch: '<S15>/Switch'
   */
  if (rtb_Add1_f > struct_PMSM_Config.mot_M_N) {
    rty_M_Soll_0 = struct_PMSM_Config.mot_M_N;
  } else if (rtb_Add1_f < -struct_PMSM_Config.mot_M_N) {
    /* Switch: '<S15>/Switch' incorporates:
     *  Gain: '<S11>/Gain1'
     */
    rty_M_Soll_0 = -struct_PMSM_Config.mot_M_N;
  } else {
    rty_M_Soll_0 = rtb_Add1_f;
  }

  /* End of Switch: '<S15>/Switch2' */

  /* Product: '<S14>/Product2' incorporates:
   *  Constant: '<S12>/Constant3'
   *  Constant: '<S14>/Constant3'
   *  Product: '<S12>/Product2'
   */
  UnitDelay_DSTATE_tmp = struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNn;

  /* Update for UnitDelay: '<S14>/Unit Delay' incorporates:
   *  Constant: '<S14>/Constant3'
   *  Product: '<S14>/Product2'
   *  Sum: '<S14>/Add'
   *  Sum: '<S14>/Add1'
   */
  localDW->UnitDelay_DSTATE += (rtu_Soll_Drehzahl - localDW->UnitDelay_DSTATE) *
    UnitDelay_DSTATE_tmp;

  /* Update for UnitDelay: '<S12>/Unit Delay' incorporates:
   *  Constant: '<S11>/Constant'
   *  Gain: '<S11>/Gain1'
   *  Logic: '<S12>/Logical Operator'
   *  Product: '<S12>/Product1'
   *  Product: '<S12>/Product2'
   *  RelationalOperator: '<S12>/Relational Operator'
   *  RelationalOperator: '<S12>/Relational Operator1'
   *  Sum: '<S12>/Add'
   */
  localDW->UnitDelay_DSTATE_l += ((rtb_Add1_f <= struct_PMSM_Config.mot_M_N) &&
    (rtb_Add1_f >= -struct_PMSM_Config.mot_M_N) ? rtb_Product_j0 : 0.0F) *
    UnitDelay_DSTATE_tmp;
  return rty_M_Soll_0;
}

/* System initialize for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_k_Init(boolean_T *rty_Dis)
{
  /* SystemInitialize for SignalConversion generated from: '<S8>/Dis' */
  *rty_Dis = false;
}

/* Output and update for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_j(boolean_T rtu_Enable, real32_T rtu_omega, const
  Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_2, boolean_T *rty_Dis, real32_T
  *rty_Soll_Moment, DW_Drehzahlregelung *localDW)
{
  real32_T tmp;

  /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (rtu_Enable) {
    /* SignalConversion generated from: '<S8>/Dis' */
    *rty_Dis = false;

    /* Switch: '<S8>/Switch' incorporates:
     *  Constant: '<S10>/Constant'
     *  Gain: '<S8>/Gain'
     *  RelationalOperator: '<S10>/Compare'
     */
    if (rtu_Bus_ZM_Out_Inport_2->Ist_Regelungsart == Trajektorie) {
      tmp = 0.0F;
    } else {
      tmp = GAIN_UMIN_TO_HZ * rtu_Bus_ZM_Out_Inport_2->Soll_Drehzahl;
    }

    /* Outputs for Atomic SubSystem: '<S8>/Drehzahlregelung' */
    *rty_Soll_Moment = Drehzahlregelung(tmp, rtu_omega,
      &localDW->Drehzahlregelung_p);

    /* End of Switch: '<S8>/Switch' */
    /* End of Outputs for SubSystem: '<S8>/Drehzahlregelung' */
  }

  /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */
}

/* Output and update for atomic system: '<S9>/IDQCtrl' */
static void IDQCtrl(real32_T rtu_ID, real32_T rtu_IQ, real32_T rtu_IDRef,
                    real32_T rtu_IQRef, real32_T rtu_OmegaMech, real32_T *rty_UD,
                    real32_T *rty_UQ, DW_IDQCtrl *localDW)
{
  real32_T rtb_Add1_k;
  real32_T rtb_Add1_p;
  real32_T rtb_Gain2;
  real32_T rtb_Product1_c;
  real32_T rtb_Product_b;
  real32_T rtb_Product_n4;
  real32_T rtb_Product_pj;

  /* Outputs for Atomic SubSystem: '<S19>/DecouplingQ' */
  /* Product: '<S25>/Product' incorporates:
   *  Constant: '<S25>/Constant'
   *  Constant: '<S25>/Constant1'
   *  Product: '<S25>/Product1'
   *  Sum: '<S25>/Add'
   */
  rtb_Product_b = (rtu_IDRef * struct_PMSM_Config.mot_Ld +
                   struct_PMSM_Config.mot_psi_pm) * rtu_OmegaMech;

  /* End of Outputs for SubSystem: '<S19>/DecouplingQ' */

  /* Gain: '<S19>/Gain2' incorporates:
   *  Constant: '<S19>/Constant2'
   */
  rtb_Gain2 = DIVIDE_TWO_BY_THREE * struct_Inv_Config.Udc;

  /* Product: '<S26>/Product' incorporates:
   *  Constant: '<S26>/Constant'
   *  Sum: '<S26>/Subtract'
   */
  rtb_Product_n4 = (rtu_IDRef - rtu_ID) * struct_Ctrl_Config.KPi;

  /* Sum: '<S26>/Add1' incorporates:
   *  UnitDelay: '<S26>/Unit Delay'
   */
  rtb_Add1_k = rtb_Product_n4 + localDW->UnitDelay_DSTATE;

  /* Switch: '<S29>/Switch2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  RelationalOperator: '<S29>/LowerRelop1'
   *  RelationalOperator: '<S29>/UpperRelop'
   *  Switch: '<S29>/Switch'
   */
  if (rtb_Add1_k > rtb_Gain2) {
    *rty_UD = rtb_Gain2;
  } else if (rtb_Add1_k < -rtb_Gain2) {
    /* Switch: '<S29>/Switch' incorporates:
     *  Gain: '<S19>/Gain1'
     */
    *rty_UD = -rtb_Gain2;
  } else {
    *rty_UD = rtb_Add1_k;
  }

  /* End of Switch: '<S29>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S19>/DecouplingD' */
  /* Sum: '<S19>/Add1' incorporates:
   *  Constant: '<S24>/Constant'
   *  Product: '<S24>/Product'
   *  Product: '<S24>/Product1'
   */
  *rty_UD -= rtu_OmegaMech * rtu_IQRef * struct_PMSM_Config.mot_Lq;

  /* End of Outputs for SubSystem: '<S19>/DecouplingD' */

  /* Sum: '<S28>/Add3' incorporates:
   *  Product: '<S28>/Product'
   *  Product: '<S28>/Product1'
   *  Sqrt: '<S28>/Sqrt'
   *  Sum: '<S28>/Add2'
   */
  rtb_Product1_c = sqrtf(rtb_Gain2 * rtb_Gain2 - *rty_UD * *rty_UD) -
    rtb_Product_b;

  /* Product: '<S27>/Product' incorporates:
   *  Constant: '<S27>/Constant'
   *  Sum: '<S27>/Subtract'
   */
  rtb_Product_pj = (rtu_IQRef - rtu_IQ) * struct_Ctrl_Config.KPi;

  /* Sum: '<S27>/Add1' incorporates:
   *  UnitDelay: '<S27>/Unit Delay'
   */
  rtb_Add1_p = rtb_Product_pj + localDW->UnitDelay_DSTATE_c;

  /* Switch: '<S30>/Switch2' incorporates:
   *  Gain: '<S28>/Gain1'
   *  RelationalOperator: '<S30>/LowerRelop1'
   *  RelationalOperator: '<S30>/UpperRelop'
   *  Switch: '<S30>/Switch'
   */
  if (rtb_Add1_p > rtb_Product1_c) {
    *rty_UQ = rtb_Product1_c;
  } else if (rtb_Add1_p < -rtb_Product1_c) {
    /* Switch: '<S30>/Switch' incorporates:
     *  Gain: '<S28>/Gain1'
     */
    *rty_UQ = -rtb_Product1_c;
  } else {
    *rty_UQ = rtb_Add1_p;
  }

  /* End of Switch: '<S30>/Switch2' */

  /* Sum: '<S19>/Add' */
  *rty_UQ += rtb_Product_b;

  /* Product: '<S26>/Product2' incorporates:
   *  Constant: '<S26>/Constant3'
   *  Constant: '<S27>/Constant3'
   *  Product: '<S27>/Product2'
   */
  rtb_Product_b = struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNi;

  /* Update for UnitDelay: '<S26>/Unit Delay' incorporates:
   *  Constant: '<S26>/Constant3'
   *  Gain: '<S19>/Gain1'
   *  Logic: '<S26>/Logical Operator'
   *  Product: '<S26>/Product1'
   *  Product: '<S26>/Product2'
   *  RelationalOperator: '<S26>/Relational Operator'
   *  RelationalOperator: '<S26>/Relational Operator1'
   *  Sum: '<S26>/Add'
   */
  localDW->UnitDelay_DSTATE += ((rtb_Add1_k <= rtb_Gain2) && (rtb_Add1_k >=
    -rtb_Gain2) ? rtb_Product_n4 : 0.0F) * rtb_Product_b;

  /* Update for UnitDelay: '<S27>/Unit Delay' incorporates:
   *  Gain: '<S28>/Gain1'
   *  Logic: '<S27>/Logical Operator'
   *  Product: '<S27>/Product1'
   *  Product: '<S27>/Product2'
   *  RelationalOperator: '<S27>/Relational Operator'
   *  RelationalOperator: '<S27>/Relational Operator1'
   *  Sum: '<S27>/Add'
   */
  localDW->UnitDelay_DSTATE_c += ((rtb_Add1_p <= rtb_Product1_c) && (rtb_Add1_p >=
    -rtb_Product1_c) ? rtb_Product_pj : 0.0F) * rtb_Product_b;
}

/* Output and update for atomic system: '<S9>/Ueberstromabschaltung' */
static boolean_T Ueberstromabschaltung(real32_T rtu_Iu, real32_T rtu_Iv,
  real32_T rtu_Iw)
{
  /* Logic: '<S20>/Logical Operator' incorporates:
   *  Abs: '<S20>/Abs'
   *  Abs: '<S20>/Abs1'
   *  Abs: '<S20>/Abs2'
   *  Constant: '<S20>/Constant'
   *  RelationalOperator: '<S20>/Relational Operator'
   *  RelationalOperator: '<S20>/Relational Operator1'
   *  RelationalOperator: '<S20>/Relational Operator2'
   */
  return (struct_PMSM_Config.mot_I_max < fabsf(rtu_Iu)) ||
    (struct_PMSM_Config.mot_I_max < fabsf(rtu_Iv)) ||
    (struct_PMSM_Config.mot_I_max < fabsf(rtu_Iw));
}

/* Output and update for atomic system: '<S9>/abc_zu_dq' */
static void abc_zu_dq(real32_T rtu_theta, real32_T rtu_pmsm_Iu, real32_T
                      rtu_pmsm_Iv, real32_T rtu_pmsm_Iw, real32_T *rty_ctrl_Id,
                      real32_T *rty_ctrl_Iq)
{
  real32_T rtb_Gain_g;
  real32_T rtb_TrigonometricFunction;
  real32_T rtb_TrigonometricFunction1;

  /* Gain: '<S31>/Gain' incorporates:
   *  Gain: '<S31>/Gain2'
   *  Gain: '<S31>/Gain7'
   *  Sum: '<S31>/Add'
   */
  rtb_Gain_g = ((-0.5F * rtu_pmsm_Iv + rtu_pmsm_Iu) + -0.5F * rtu_pmsm_Iw) *
    DIVIDE_TWO_BY_THREE;

  /* Trigonometry: '<S32>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = cosf(rtu_theta);

  /* Gain: '<S31>/sqrt(3)//2' */
  *rty_ctrl_Iq = -DIVIDE_SQRT_THREE_BY_TWO * rtu_pmsm_Iw;

  /* Gain: '<S31>/Gain1' incorporates:
   *  Gain: '<S31>/Gain5'
   *  Sum: '<S31>/Add1'
   */
  *rty_ctrl_Iq = (DIVIDE_SQRT_THREE_BY_TWO * rtu_pmsm_Iv + *rty_ctrl_Iq) *
    DIVIDE_TWO_BY_THREE;

  /* Trigonometry: '<S32>/Trigonometric Function' */
  rtb_TrigonometricFunction = sinf(rtu_theta);

  /* Sum: '<S32>/Add' incorporates:
   *  Product: '<S32>/Product'
   *  Product: '<S32>/Product1'
   */
  *rty_ctrl_Id = rtb_TrigonometricFunction1 * rtb_Gain_g +
    rtb_TrigonometricFunction * *rty_ctrl_Iq;

  /* Sum: '<S32>/Add1' incorporates:
   *  Product: '<S32>/Product2'
   *  Product: '<S32>/Product3'
   */
  *rty_ctrl_Iq = *rty_ctrl_Iq * rtb_TrigonometricFunction1 - rtb_Gain_g *
    rtb_TrigonometricFunction;
}

/* Output and update for atomic system: '<S9>/dq_zu_alphabeta' */
static void dq_zu_alphabeta(real32_T rtu_theta, real32_T rtu_valD, real32_T
  rtu_valQ, real32_T *rty_valAlpha, real32_T *rty_valBeta)
{
  real32_T rtb_TrigonometricFunction;
  real32_T rtb_TrigonometricFunction1;

  /* Trigonometry: '<S23>/Trigonometric Function1' incorporates:
   *  Gain: '<S23>/Gain1'
   */
  rtb_TrigonometricFunction1 = cosf(-rtu_theta);

  /* Trigonometry: '<S23>/Trigonometric Function' incorporates:
   *  Gain: '<S23>/Gain1'
   */
  rtb_TrigonometricFunction = sinf(-rtu_theta);

  /* Sum: '<S23>/Add' incorporates:
   *  Product: '<S23>/Product'
   *  Product: '<S23>/Product1'
   */
  *rty_valAlpha = rtu_valD * rtb_TrigonometricFunction1 + rtu_valQ *
    rtb_TrigonometricFunction;

  /* Sum: '<S23>/Add1' incorporates:
   *  Product: '<S23>/Product2'
   *  Product: '<S23>/Product3'
   */
  *rty_valBeta = rtu_valQ * rtb_TrigonometricFunction1 - rtu_valD *
    rtb_TrigonometricFunction;
}

/* Output and update for atomic system: '<S3>/Stromregelung' */
static void Stromregelung(real32_T rtu_Soll_Moment, const Bus_PMSM_Out
  *rtu_Bus_Live_Out_PMSM_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  real32_T *rty_Ualpha, real32_T *rty_Ubeta, DW_Stromregelung *localDW)
{
  real32_T rtb_Add1;
  real32_T rtb_Add_l;
  real32_T rtb_Add_o;
  real32_T rtb_IDRef;
  real32_T rtb_IQRef;
  real32_T rtb_Product1;
  real32_T rtb_Product2;
  boolean_T rtb_act_ab;

  /* Product: '<S9>/Product2' incorporates:
   *  Constant: '<S9>/Constant2'
   */
  rtb_Product2 = rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Omega_mech *
    struct_PMSM_Config.mot_p;

  /* Product: '<S9>/Product1' incorporates:
   *  Constant: '<S9>/Constant2'
   */
  rtb_Product1 = struct_PMSM_Config.mot_p *
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_phi_mech;

  /* Switch: '<S9>/Switch2' incorporates:
   *  Constant: '<S18>/Constant'
   *  Constant: '<S9>/Constant'
   *  Gain: '<S22>/Gain'
   *  RelationalOperator: '<S18>/Compare'
   *  Switch: '<S9>/Switch3'
   */
  if (rtu_Bus_ZM_Out_Inport_3->Ist_Regelungsart == Strom) {
    rtb_IDRef = rtu_Bus_ZM_Out_Inport_3->Soll_id;
    rtb_IQRef = rtu_Bus_ZM_Out_Inport_3->Soll_iq;
  } else {
    rtb_IDRef = 0.0F;

    /* Outputs for Atomic SubSystem: '<S9>/calcIq' */
    rtb_IQRef = 0.666666687F / struct_PMSM_Config.mot_psi_pm /
      struct_PMSM_Config.mot_p * rtu_Soll_Moment;

    /* End of Outputs for SubSystem: '<S9>/calcIq' */
  }

  /* End of Switch: '<S9>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S9>/abc_zu_dq' */
  abc_zu_dq(rtb_Product1, rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[0],
            rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[1],
            rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2], &rtb_Add1, &rtb_Add_l);

  /* End of Outputs for SubSystem: '<S9>/abc_zu_dq' */

  /* Outputs for Atomic SubSystem: '<S9>/IDQCtrl' */
  IDQCtrl(rtb_Add1, rtb_Add_l, rtb_IDRef, rtb_IQRef, rtb_Product2, &rtb_Add1,
          &rtb_Add_o, &localDW->IDQCtrl_f);

  /* End of Outputs for SubSystem: '<S9>/IDQCtrl' */

  /* Outputs for Atomic SubSystem: '<S9>/dq_zu_alphabeta' */
  /* Sum: '<S9>/Add' incorporates:
   *  Constant: '<S9>/Constant3'
   *  Product: '<S9>/Product'
   */
  dq_zu_alphabeta(struct_Ctrl_Config.Tsample * rtb_Product2 + rtb_Product1,
                  rtb_Add1, rtb_Add_o, &rtb_Add_l, &rtb_Add1);

  /* End of Outputs for SubSystem: '<S9>/dq_zu_alphabeta' */

  /* Outputs for Atomic SubSystem: '<S9>/Ueberstromabschaltung' */
  rtb_act_ab = Ueberstromabschaltung(rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[0],
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[1],
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2]);

  /* End of Outputs for SubSystem: '<S9>/Ueberstromabschaltung' */

  /* Logic: '<S9>/Logical Operator' incorporates:
   *  Constant: '<S16>/Constant'
   *  Constant: '<S17>/Constant'
   *  Logic: '<S9>/Logical Operator1'
   *  RelationalOperator: '<S16>/Compare'
   *  RelationalOperator: '<S17>/Compare'
   */
  rtb_act_ab = (((rtb_IQRef == 0.0F) && (rtb_IDRef == 0.0F)) || rtb_act_ab);

  /* Switch: '<S9>/Switch' incorporates:
   *  Constant: '<S9>/Constant1'
   *  Switch: '<S9>/Switch1'
   */
  if (rtb_act_ab) {
    *rty_Ualpha = 0.0F;
    *rty_Ubeta = 0.0F;
  } else {
    *rty_Ualpha = rtb_Add_l;
    *rty_Ubeta = rtb_Add1;
  }

  /* End of Switch: '<S9>/Switch' */
}

/* System initialize for enable system: '<S1>/Regelung' */
static void Regelung_Init(boolean_T *rty_Dis)
{
  /* SystemInitialize for Enabled SubSystem: '<S3>/Drehzahlregelung' */
  Drehzahlregelung_k_Init(rty_Dis);

  /* End of SystemInitialize for SubSystem: '<S3>/Drehzahlregelung' */
}

/* Output and update for enable system: '<S1>/Regelung' */
static void Regelung(boolean_T rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_2, real32_T *rty_Ualpha, real32_T
                     *rty_Ubeta, boolean_T *rty_Dis, DW_Regelung *localDW)
{
  /* Outputs for Enabled SubSystem: '<S1>/Regelung' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (rtu_Enable) {
    /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' */
    /* RelationalOperator: '<S7>/Compare' incorporates:
     *  Constant: '<S7>/Constant'
     */
    Drehzahlregelung_j((rtu_Bus_ZM_Out_Inport_2->Ist_Regelungsart <= Drehzahl),
                       rtu_Bus_Live_Out_PMSM_Inport_1->pmsm_Omega_mech,
                       rtu_Bus_ZM_Out_Inport_2, rty_Dis, &localDW->Switch2,
                       &localDW->Drehzahlregelung_jl);

    /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */

    /* Outputs for Atomic SubSystem: '<S3>/Stromregelung' */
    Stromregelung(localDW->Switch2, rtu_Bus_Live_Out_PMSM_Inport_1,
                  rtu_Bus_ZM_Out_Inport_2, rty_Ualpha, rty_Ubeta,
                  &localDW->Stromregelung_e);

    /* End of Outputs for SubSystem: '<S3>/Stromregelung' */
  }

  /* End of Outputs for SubSystem: '<S1>/Regelung' */
}

/* System initialize for atomic system: '<S4>/state_chart' */
static void state_chart_Init(Bus_ZM_Out *rty_Bus_ZM_Out, DW_state_chart *localDW)
{
  rty_Bus_ZM_Out->En_Traj = false;
  rty_Bus_ZM_Out->Pulsfreigabe = false;
  rty_Bus_ZM_Out->Ist_Status = Error_Status;
  rty_Bus_ZM_Out->Ist_Regelungsart = Error;
  rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;
  rty_Bus_ZM_Out->Soll_id = 0.0F;
  rty_Bus_ZM_Out->Soll_iq = 0.0F;
  rty_Bus_ZM_Out->pwr_en = false;
  rty_Bus_ZM_Out->board_en = false;
  rty_Bus_ZM_Out->reset = false;
  localDW->is_active_c3_uz_codegen0 = 0U;
  localDW->is_c3_uz_codegen0 = IN_NO_ACTIVE_CHILD;
  localDW->is_NoError = IN_NO_ACTIVE_CHILD;
  localDW->is_Run = IN_NO_ACTIVE_CHILD;
  localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
}

/* Output and update for atomic system: '<S4>/state_chart' */
static void state_chart(const Bus_ZM_In *rtu_Bus_ZM_In, boolean_T rtu_Dis,
  Bus_ZM_Out *rty_Bus_ZM_Out, DW_state_chart *localDW)
{
  /* Chart: '<S4>/state_chart' */
  /* Gateway: uz_codegen/Zustandsmaschine/state_chart */
  /* During: uz_codegen/Zustandsmaschine/state_chart */
  if (localDW->is_active_c3_uz_codegen0 == 0) {
    /* Entry: uz_codegen/Zustandsmaschine/state_chart */
    localDW->is_active_c3_uz_codegen0 = 1U;

    /* Entry Internal: uz_codegen/Zustandsmaschine/state_chart */
    /* Transition: '<S33>:11' */
    localDW->is_c3_uz_codegen0 = IN_NoError;

    /* Entry Internal 'NoError': '<S33>:32' */
    /* Transition: '<S33>:45' */
    localDW->is_NoError = IN_Idle;
  } else if (localDW->is_c3_uz_codegen0 == IN_Error) {
    /* During 'Error': '<S33>:10' */
    /* '<S33>:14:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == false && Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state); */
    if ((!rtu_Bus_ZM_In->Fehlermeldung) && (rtu_Bus_ZM_In->UZ_Platform_State ==
         idle_state)) {
      /* Transition: '<S33>:14' */
      localDW->is_c3_uz_codegen0 = IN_NoError;

      /* Entry Internal 'NoError': '<S33>:32' */
      /* Transition: '<S33>:45' */
      localDW->is_NoError = IN_Idle;
    } else {
      /* '<S33>:10:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Error_Status; */
      rty_Bus_ZM_Out->Ist_Status = Error_Status;

      /* '<S33>:10:4' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S33>:10:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Error; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Error;

      /* '<S33>:10:6' Bus_ZM_Out.En_Traj = false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S33>:10:7' Bus_ZM_Out.Soll_Drehzahl = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

      /* '<S33>:10:8' Bus_ZM_Out.Soll_id = 0; */
      rty_Bus_ZM_Out->Soll_id = 0.0F;

      /* '<S33>:10:9' Bus_ZM_Out.Soll_iq = 0; */
      rty_Bus_ZM_Out->Soll_iq = 0.0F;

      /* '<S33>:10:10' Bus_ZM_Out.reset  = true; */
      rty_Bus_ZM_Out->reset = true;

      /* '<S33>:10:11' Bus_ZM_Out.pwr_en  = false; */
      rty_Bus_ZM_Out->pwr_en = false;

      /* '<S33>:10:12' Bus_ZM_Out.board_en  = false; */
      rty_Bus_ZM_Out->board_en = false;
    }

    /* During 'NoError': '<S33>:32' */
    /* '<S33>:15:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == true || Bus_ZM_In.UZ_Platform_State == platform_state_t.error_state || Bus_ZM_In.IGBT_desat == true); */
  } else if (rtu_Bus_ZM_In->Fehlermeldung || (rtu_Bus_ZM_In->UZ_Platform_State ==
              error_state) || rtu_Bus_ZM_In->IGBT_desat) {
    /* Transition: '<S33>:15' */
    /* Exit Internal 'NoError': '<S33>:32' */
    /* Exit Internal 'Run': '<S33>:20' */
    /* Exit Internal 'Trapez': '<S33>:54' */
    localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
    localDW->is_Run = IN_NO_ACTIVE_CHILD;
    localDW->is_NoError = IN_NO_ACTIVE_CHILD;
    localDW->is_c3_uz_codegen0 = IN_Error;
  } else {
    switch (localDW->is_NoError) {
     case IN_Idle:
      /* During 'Idle': '<S33>:103' */
      /* '<S33>:104:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.running_state); */
      if (rtu_Bus_ZM_In->UZ_Platform_State == running_state) {
        /* Transition: '<S33>:104' */
        localDW->is_NoError = IN_Ready;
      } else {
        /* '<S33>:103:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
        rty_Bus_ZM_Out->Ist_Status = Ready;

        /* '<S33>:103:4' Bus_ZM_Out.Pulsfreigabe = false; */
        rty_Bus_ZM_Out->Pulsfreigabe = false;

        /* '<S33>:103:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

        /* '<S33>:103:6' Bus_ZM_Out.En_Traj=false; */
        rty_Bus_ZM_Out->En_Traj = false;

        /* '<S33>:103:7' Bus_ZM_Out.Soll_Drehzahl = 0; */
        rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

        /* '<S33>:103:8' Bus_ZM_Out.Soll_id = 0; */
        rty_Bus_ZM_Out->Soll_id = 0.0F;

        /* '<S33>:103:9' Bus_ZM_Out.Soll_iq = 0; */
        rty_Bus_ZM_Out->Soll_iq = 0.0F;

        /* '<S33>:103:10' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S33>:103:11' Bus_ZM_Out.pwr_en  = false; */
        rty_Bus_ZM_Out->pwr_en = false;

        /* '<S33>:103:12' Bus_ZM_Out.board_en  = false; */
        rty_Bus_ZM_Out->board_en = false;
      }
      break;

     case IN_Ready:
      /* During 'Ready': '<S33>:19' */
      /* '<S33>:25:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.control_state && Bus_ZM_In.Inv_Ready == true); */
      if ((rtu_Bus_ZM_In->UZ_Platform_State == control_state) &&
          rtu_Bus_ZM_In->Inv_Ready) {
        /* Transition: '<S33>:25' */
        localDW->is_NoError = IN_Run;

        /* Entry Internal 'Run': '<S33>:20' */
        /* Transition: '<S33>:55' */
        localDW->is_Run = IN_nCtrl;

        /* '<S33>:105:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state); */
      } else if (rtu_Bus_ZM_In->UZ_Platform_State == idle_state) {
        /* Transition: '<S33>:105' */
        localDW->is_NoError = IN_Idle;
      } else {
        /* '<S33>:19:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
        rty_Bus_ZM_Out->Ist_Status = Ready;

        /* '<S33>:19:4' Bus_ZM_Out.Pulsfreigabe = false; */
        rty_Bus_ZM_Out->Pulsfreigabe = false;

        /* '<S33>:19:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

        /* '<S33>:19:6' Bus_ZM_Out.En_Traj=false; */
        rty_Bus_ZM_Out->En_Traj = false;

        /* '<S33>:19:7' Bus_ZM_Out.Soll_Drehzahl = 0; */
        rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

        /* '<S33>:19:8' Bus_ZM_Out.Soll_id = 0; */
        rty_Bus_ZM_Out->Soll_id = 0.0F;

        /* '<S33>:19:9' Bus_ZM_Out.Soll_iq = 0; */
        rty_Bus_ZM_Out->Soll_iq = 0.0F;

        /* '<S33>:19:10' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S33>:19:11' Bus_ZM_Out.pwr_en  = true; */
        rty_Bus_ZM_Out->pwr_en = true;

        /* '<S33>:19:12' Bus_ZM_Out.board_en  = true; */
        rty_Bus_ZM_Out->board_en = true;
      }
      break;

     default:
      /* During 'Run': '<S33>:20' */
      /* '<S33>:106:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state || Bus_ZM_In.Inv_Ready == false); */
      if ((rtu_Bus_ZM_In->UZ_Platform_State == idle_state) ||
          (!rtu_Bus_ZM_In->Inv_Ready)) {
        /* Transition: '<S33>:106' */
        /* Exit Internal 'Run': '<S33>:20' */
        /* Exit Internal 'Trapez': '<S33>:54' */
        localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
        localDW->is_Run = IN_NO_ACTIVE_CHILD;
        localDW->is_NoError = IN_Idle;
      } else {
        /* '<S33>:20:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Run; */
        rty_Bus_ZM_Out->Ist_Status = Run;

        /* '<S33>:20:4' Bus_ZM_Out.Pulsfreigabe = true; */
        rty_Bus_ZM_Out->Pulsfreigabe = true;

        /* '<S33>:20:5' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S33>:20:6' Bus_ZM_Out.pwr_en  = true; */
        rty_Bus_ZM_Out->pwr_en = true;

        /* '<S33>:20:7' Bus_ZM_Out.board_en  = true; */
        rty_Bus_ZM_Out->board_en = true;
        switch (localDW->is_Run) {
         case IN_Stromregelung:
          /* During 'Stromregelung': '<S33>:86' */
          /* '<S33>:92:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Strom); */
          if (rtu_Bus_ZM_In->Soll_Regelungsart != Strom) {
            /* Transition: '<S33>:92' */
            localDW->is_Run = IN_nCtrl;
          } else {
            /* '<S33>:86:3' Bus_ZM_Out.Soll_id = Bus_ZM_In.Soll_id; */
            rty_Bus_ZM_Out->Soll_id = rtu_Bus_ZM_In->Soll_id;

            /* '<S33>:86:4' Bus_ZM_Out.Soll_iq = Bus_ZM_In.Soll_iq; */
            rty_Bus_ZM_Out->Soll_iq = rtu_Bus_ZM_In->Soll_iq;

            /* '<S33>:86:5' Bus_ZM_Out.Soll_Drehzahl = 0; */
            rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

            /* '<S33>:86:6' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Strom; */
            rty_Bus_ZM_Out->Ist_Regelungsart = Strom;
          }
          break;

         case IN_Trapez:
          /* During 'Trapez': '<S33>:54' */
          /* '<S33>:90:1' sf_internal_predicateOutput = 0 | (Dis == 1 || Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Trajektorie); */
          if (rtu_Dis || (rtu_Bus_ZM_In->Soll_Regelungsart != Trajektorie)) {
            /* Transition: '<S33>:90' */
            /* Exit Internal 'Trapez': '<S33>:54' */
            localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
            localDW->is_Run = IN_nCtrl;
          } else {
            /* '<S33>:54:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Trajektorie; */
            rty_Bus_ZM_Out->Ist_Regelungsart = Trajektorie;

            /* '<S33>:54:4' Bus_ZM_Out.Soll_Drehzahl = Bus_ZM_In.Soll_Drehzahl; */
            rty_Bus_ZM_Out->Soll_Drehzahl = rtu_Bus_ZM_In->Soll_Drehzahl;

            /* '<S33>:54:5' Bus_ZM_Out.Soll_id = 0; */
            rty_Bus_ZM_Out->Soll_id = 0.0F;

            /* '<S33>:54:6' Bus_ZM_Out.Soll_iq = 0; */
            rty_Bus_ZM_Out->Soll_iq = 0.0F;
            if (localDW->is_Trapez == IN_Run_j) {
              /* During 'Run': '<S33>:68' */
              /* '<S33>:70:1' sf_internal_predicateOutput = 0 | (Dis == 1); */
              /* '<S33>:68:2' Bus_ZM_Out.En_Traj = true; */
              rty_Bus_ZM_Out->En_Traj = true;

              /* During 'Warten': '<S33>:66' */
              /* '<S33>:69:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Start_Traj == 1); */
            } else if (rtu_Bus_ZM_In->Start_Traj) {
              /* Transition: '<S33>:69' */
              localDW->is_Trapez = IN_Run_j;

              /* Entry 'Run': '<S33>:68' */
              /* '<S33>:68:2' Bus_ZM_Out.En_Traj = true; */
              rty_Bus_ZM_Out->En_Traj = true;
            } else {
              /* '<S33>:66:2' Bus_ZM_Out.En_Traj = false; */
              rty_Bus_ZM_Out->En_Traj = false;
            }
          }
          break;

         default:
          /* During 'nCtrl': '<S33>:56' */
          /* '<S33>:89:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Trajektorie); */
          switch (rtu_Bus_ZM_In->Soll_Regelungsart) {
           case Trajektorie:
            /* Transition: '<S33>:89' */
            localDW->is_Run = IN_Trapez;

            /* Entry Internal 'Trapez': '<S33>:54' */
            /* Transition: '<S33>:67' */
            localDW->is_Trapez = IN_Warten;

            /* Entry 'Warten': '<S33>:66' */
            /* '<S33>:66:2' Bus_ZM_Out.En_Traj = false; */
            rty_Bus_ZM_Out->En_Traj = false;
            break;

           case Strom:
            /* '<S33>:91:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Strom); */
            /* Transition: '<S33>:91' */
            localDW->is_Run = IN_Stromregelung;
            break;

           default:
            /* '<S33>:56:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
            rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

            /* '<S33>:56:4' Bus_ZM_Out.Soll_Drehzahl = Bus_ZM_In.Soll_Drehzahl; */
            rty_Bus_ZM_Out->Soll_Drehzahl = rtu_Bus_ZM_In->Soll_Drehzahl;

            /* '<S33>:56:5' Bus_ZM_Out.Soll_id = 0; */
            rty_Bus_ZM_Out->Soll_id = 0.0F;

            /* '<S33>:56:6' Bus_ZM_Out.Soll_iq = 0; */
            rty_Bus_ZM_Out->Soll_iq = 0.0F;
            break;
          }
          break;
        }
      }
      break;
    }
  }

  /* End of Chart: '<S4>/state_chart' */
}

/* System initialize for atomic system: '<S1>/Zustandsmaschine' */
static void Zustandsmaschine_Init(Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1,
  DW_Zustandsmaschine *localDW)
{
  /* SystemInitialize for Chart: '<S4>/state_chart' */
  state_chart_Init(rty_Bus_ZM_Out_Outport_1, &localDW->sf_state_chart);
}

/* Output and update for atomic system: '<S1>/Zustandsmaschine' */
static void Zustandsmaschine(const Bus_ZM_In *rtu_Bus_ZM_In_Inport_1, boolean_T
  rtu_ZM_In_Dis_Traj, Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1, DW_Zustandsmaschine *
  localDW)
{
  /* Chart: '<S4>/state_chart' */
  state_chart(rtu_Bus_ZM_In_Inport_1, rtu_ZM_In_Dis_Traj,
              rty_Bus_ZM_Out_Outport_1, &localDW->sf_state_chart);
}

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Outputs for Atomic SubSystem: '<S1>/Zustandsmaschine' */

  /* UnitDelay: '<S1>/Unit Delay' */
  Zustandsmaschine(&rtU->Bus_ZM_In_c, rtDW->UnitDelay_DSTATE,
                   &rtDW->Bus_ZM_Out_g, &rtDW->Zustandsmaschine_a);

  /* End of Outputs for SubSystem: '<S1>/Zustandsmaschine' */

  /* Outputs for Enabled SubSystem: '<S1>/Regelung' */

  /* SignalConversion generated from: '<S3>/Enable' */
  Regelung(rtDW->Bus_ZM_Out_g.Pulsfreigabe, &rtU->Bus_PMSM_Out_c,
           &rtDW->Bus_ZM_Out_g, &rtDW->Switch, &rtDW->Switch1,
           &rtDW->OutportBufferForDis, &rtDW->Regelung_j);

  /* End of Outputs for SubSystem: '<S1>/Regelung' */

  /* Outputs for Atomic SubSystem: '<S1>/Raumzeigermodulation' */

  /* BusCreator generated from: '<S1>/Bus_Ctrl_Out_BusCreator' incorporates:
   *  Outport: '<Root>/Bus_Ctrl_Out'
   */
  Raumzeigermodulation(rtDW->Switch, rtDW->Switch1,
                       rtY->Bus_Ctrl_Out_e.Dutycycle);

  /* End of Outputs for SubSystem: '<S1>/Raumzeigermodulation' */
  rtY->Bus_Ctrl_Out_e.act_pwm = rtDW->Bus_ZM_Out_g.Pulsfreigabe;
  rtY->Bus_Ctrl_Out_e.ctrl_Ualpha = rtDW->Switch;
  rtY->Bus_Ctrl_Out_e.ctrl_Ubeta = rtDW->Switch1;
  rtY->Bus_Ctrl_Out_e.pwr_en = rtDW->Bus_ZM_Out_g.pwr_en;
  rtY->Bus_Ctrl_Out_e.board_en = rtDW->Bus_ZM_Out_g.board_en;
  rtY->Bus_Ctrl_Out_e.reset = rtDW->Bus_ZM_Out_g.reset;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  rtDW->UnitDelay_DSTATE = rtDW->OutportBufferForDis;
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  {
    rtDW->Bus_ZM_Out_g = uz_codegen0_rtZBus_ZM_Out;
  }

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));
  rtU->Bus_ZM_In_c = uz_codegen0_rtZBus_ZM_In;

  /* external outputs */
  rtY->Bus_Ctrl_Out_e = uz_codegen0_rtZBus_Ctrl_Out;

  /* SystemInitialize for Atomic SubSystem: '<S1>/Zustandsmaschine' */
  Zustandsmaschine_Init(&rtDW->Bus_ZM_Out_g, &rtDW->Zustandsmaschine_a);

  /* End of SystemInitialize for SubSystem: '<S1>/Zustandsmaschine' */

  /* SystemInitialize for Enabled SubSystem: '<S1>/Regelung' */
  Regelung_Init(&rtDW->OutportBufferForDis);

  /* End of SystemInitialize for SubSystem: '<S1>/Regelung' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
