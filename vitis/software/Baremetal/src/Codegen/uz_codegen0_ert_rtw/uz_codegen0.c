/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 10.5
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Thu May 14 14:56:45 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "uz_codegen0.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

/* Named constants for Chart: '<S4>/state_chart' */
#define IN_Error                       ((uint8_t)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_t)0U)
#define IN_NoError                     ((uint8_t)2U)
#define IN_Ready                       ((uint8_t)1U)
#define IN_Run                         ((uint8_t)2U)
#define IN_Run_c                       ((uint8_t)1U)
#define IN_Stromregelung               ((uint8_t)1U)
#define IN_Trapez                      ((uint8_t)2U)
#define IN_Warten                      ((uint8_t)2U)
#define IN_nCtrl                       ((uint8_t)3U)

const Bus_ZM_Out uz_codegen0_rtZBus_ZM_Out = {
  false,                               /* En_Traj */
  false,                               /* Pulsfreigabe */
  Error_Status,                        /* Ist_Status */
  Error,                               /* Ist_Regelungsart */
  0.0F,                                /* Soll_Drehzahl */
  0.0F,                                /* Soll_id */
  0.0F                                 /* Soll_iq */
};                                     /* Bus_ZM_Out ground */

/* Exported block parameters */
Bus_Ctrl_Config struct_Ctrl_Config = {
  0.0001F,
  0.0001F,
  0.004F,
  36.0F,
  0.0002F,
  0.0008F,
  13.7444677F,
  0.152709171F,
  -0.152709171F,
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
                                        *   '<S12>/Constant1'
                                        *   '<S13>/Constant'
                                        *   '<S13>/Constant3'
                                        *   '<S14>/Constant1'
                                        *   '<S14>/Constant2'
                                        *   '<S15>/Constant3'
                                        *   '<S17>/Constant'
                                        *   '<S18>/Constant'
                                        *   '<S32>/Constant'
                                        *   '<S32>/Constant3'
                                        *   '<S33>/Constant'
                                        *   '<S33>/Constant3'
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
  20.9F
} ;                                    /* Variable: struct_PMSM_Config
                                        * Referenced by:
                                        *   '<S9>/Constant2'
                                        *   '<S11>/Constant'
                                        *   '<S26>/Constant'
                                        *   '<S28>/Gain'
                                        *   '<S30>/Constant'
                                        *   '<S31>/Constant'
                                        *   '<S31>/Constant1'
                                        */

Bus_ZM_In struct_ZM_In = {
  2000.0F,
  0.0F,
  0.0F,
  0.0F,
  false,
  En,
  Drehzahl
} ;                                    /* Variable: struct_ZM_In
                                        * Referenced by:
                                        *   '<S12>/Saturation'
                                        *   '<S20>/Unit Delay2'
                                        */

Bus_Inv_Config struct_Inv_Config = {
  PT1,
  678.0F,
  1.0F,
  20000.0F,
  0.0F
} ;                                    /* Variable: struct_Inv_Config
                                        * Referenced by:
                                        *   '<S2>/Constant'
                                        *   '<S25>/Constant2'
                                        */

static void MinimaleSchaltzeit(const float rtu_Dutycycle[3], float rty_Out1[3]);
static void raumzeigermodulation(float rtu_Ualpha, float rtu_Ubeta, float
  rtu_Udc, float *rty_Dutycycle_A, float *rty_Dutycycle_B, float
  *rty_Dutycycle_C, float *rty_Sektor, float *rty_Quadrant);
static void Raumzeigermodulation(float rtu_Ualpha, float rtu_Ubeta, float
  rty_Dutycycle_A[3]);
static float Drehzahlregelung(float rtu_Soll_Drehzahl, float rtu_omega, const
  Bus_PMSM_In *rtu_PMSM_In_Inport_3, DW_Drehzahlregelung_f *localDW);
static void Trajektorie_Erzeugung_Init(DW_Trajektorie_Erzeugung *localDW);
static void Trajektorie_Erzeugung_Reset(DW_Trajektorie_Erzeugung *localDW);
static void Trajektorie_Erzeugung_Disable(DW_Trajektorie_Erzeugung *localDW);
static void Trajektorie_Erzeugung(bool rtu_En_Trapez, float rtu_Max_Drehzahl,
  float *rty_Soll_Drehzahl, bool rty_Dis[2], DW_Trajektorie_Erzeugung *localDW);
static void Drehzahlregelung_o_Init(DW_Drehzahlregelung *localDW);
static void Drehzahlregelung_Disable(DW_Drehzahlregelung *localDW);
static void Drehzahlregelung_h(bool rtu_Enable, float rtu_omega, const
  Bus_PMSM_In *rtu_PMSM_In_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  bool rty_Dis[2], float *rty_Soll_Moment, DW_Drehzahlregelung *localDW);
static void IDQCtrl(float rtu_ID, float rtu_IQ, float rtu_IDRef, float rtu_IQRef,
                    float rtu_OmegaMech, float *rty_UD, float *rty_UQ,
                    DW_IDQCtrl *localDW);
static bool Ueberstromabschaltung(float rtu_Iu, float rtu_Iv, float rtu_Iw);
static void abc_zu_dq(float rtu_theta, float rtu_pmsm_Iu, float rtu_pmsm_Iv,
                      float rtu_pmsm_Iw, float *rty_ctrl_Id, float *rty_ctrl_Iq);
static void dq_zu_alphabeta(float rtu_theta, float rtu_valD, float rtu_valQ,
  float *rty_valAlpha, float *rty_valBeta);
static void Stromregelung(float rtu_Soll_Moment, const Bus_PMSM_Out
  *rtu_Bus_Live_Out_PMSM_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  float *rty_Ualpha, float *rty_Ubeta, DW_Stromregelung *localDW);
static void Regelung_Init(DW_Regelung *localDW);
static void Regelung_Disable(DW_Regelung *localDW);
static void Regelung(bool rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_PMSM_In
                     *rtu_PMSM_In_Inport_2, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_3, float *rty_Ualpha, float
                     *rty_Ubeta, bool rty_Dis[2], DW_Regelung *localDW);
static void state_chart_Init(Bus_ZM_Out *rty_Bus_ZM_Out);
static void state_chart(const Bus_ZM_In *rtu_Bus_ZM_In, bool rtu_Dis, Bus_ZM_Out
  *rty_Bus_ZM_Out, DW_state_chart *localDW);
static void Zustandsmaschine_Init(Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1);
static void Zustandsmaschine(const Bus_ZM_In *rtu_Bus_ZM_In_Inport_1, bool
  rtu_ZM_In_Dis_Traj, Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1, DW_Zustandsmaschine *
  localDW);
const Bus_ZM_In uz_codegen0_rtZBus_ZM_In = { 0.0F,/* Soll_Drehzahl */
  0.0F,                                /* Soll_id */
  0.0F,                                /* Soll_iq */
  0.0F,                                /* Start_Traj */
  false,                               /* Fehlermeldung */
  Error_Status,                        /* Soll_Status */
  Error                                /* Soll_Regelungsart */
};

/* Output and update for atomic system: '<S2>/MinimaleSchaltzeit' */
static void MinimaleSchaltzeit(const float rtu_Dutycycle[3], float rty_Out1[3])
{
  float rtb_Switch1_idx_0;
  float rtb_Switch1_idx_1;
  float rtb_Switch1_idx_2;
  float tmp;

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
static void raumzeigermodulation(float rtu_Ualpha, float rtu_Ubeta, float
  rtu_Udc, float *rty_Dutycycle_A, float *rty_Dutycycle_B, float
  *rty_Dutycycle_C, float *rty_Sektor, float *rty_Quadrant)
{
  float Dutycycle_A;
  float a;
  float abs_Ualpha;
  float abs_Ubeta;
  float c;
  int32_t Quadrant;
  int32_t Sektor;

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
  *rty_Sektor = (float)Sektor;
  *rty_Quadrant = (float)Quadrant;
}

/* Output and update for atomic system: '<S1>/Raumzeigermodulation' */
static void Raumzeigermodulation(float rtu_Ualpha, float rtu_Ubeta, float
  rty_Dutycycle_A[3])
{
  float rtb_TmpSignalConversionAtMinima[3];
  float rtb_Quadrant;
  float rtb_Sektor;

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
static float Drehzahlregelung(float rtu_Soll_Drehzahl, float rtu_omega, const
  Bus_PMSM_In *rtu_PMSM_In_Inport_3, DW_Drehzahlregelung_f *localDW)
{
  float rty_M_Soll_0;
  float rtb_Add1_b;
  float rtb_Product_a_tmp;
  float rtb_Product_j;
  float rtb_Switch2;

  /* Sum: '<S13>/Subtract' incorporates:
   *  Gain: '<S11>/Gain'
   *  Sum: '<S11>/ctrl_n_diff'
   *  UnitDelay: '<S15>/Unit Delay'
   */
  rtb_Product_a_tmp = localDW->UnitDelay_DSTATE - GAIN_RADS_TO_HZ * rtu_omega;

  /* Product: '<S13>/Product' incorporates:
   *  Constant: '<S13>/Constant'
   *  Sum: '<S13>/Subtract'
   */
  rtb_Product_j = rtb_Product_a_tmp * struct_Ctrl_Config.KPn;

  /* Sum: '<S13>/Add1' incorporates:
   *  UnitDelay: '<S13>/Unit Delay'
   */
  rtb_Add1_b = rtb_Product_j + localDW->UnitDelay_DSTATE_j;

  /* Switch: '<S16>/Switch2' incorporates:
   *  Constant: '<S11>/Constant'
   *  Gain: '<S11>/Gain1'
   *  RelationalOperator: '<S16>/LowerRelop1'
   *  RelationalOperator: '<S16>/UpperRelop'
   *  Switch: '<S16>/Switch'
   */
  if (rtb_Add1_b > struct_PMSM_Config.mot_M_N) {
    rtb_Switch2 = struct_PMSM_Config.mot_M_N;
  } else if (rtb_Add1_b < -struct_PMSM_Config.mot_M_N) {
    /* Switch: '<S16>/Switch' incorporates:
     *  Gain: '<S11>/Gain1'
     */
    rtb_Switch2 = -struct_PMSM_Config.mot_M_N;
  } else {
    rtb_Switch2 = rtb_Add1_b;
  }

  /* End of Switch: '<S16>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S11>/n_Ctrl_hysterese' */
  /* Switch: '<S14>/Abschalten, wenn n_diff < 1.01% nN2' incorporates:
   *  Constant: '<S14>/Constant1'
   *  Constant: '<S14>/Constant2'
   *  Logic: '<S14>/AND'
   *  Logic: '<S14>/NOT'
   *  RelationalOperator: '<S14>/Relational Operator'
   *  RelationalOperator: '<S14>/Relational Operator1'
   */
  if ((rtb_Product_a_tmp > struct_Ctrl_Config.n_hyst_upperlimit) ||
      (rtb_Product_a_tmp < struct_Ctrl_Config.n_hyst_lowerlimit)) {
    /* Switch: '<S14>/Abschalten, wenn n_diff < 1.01% nN1' incorporates:
     *  RelationalOperator: '<S14>/Relational Operator2'
     *  Sum: '<S14>/Subtract1'
     *  Sum: '<S14>/Subtract2'
     */
    if (rtb_Product_a_tmp > struct_Ctrl_Config.n_hyst_upperlimit) {
      rty_M_Soll_0 = rtb_Switch2 - struct_Ctrl_Config.n_hyst_upperlimit;
    } else {
      rty_M_Soll_0 = rtb_Switch2 - struct_Ctrl_Config.n_hyst_lowerlimit;
    }

    /* End of Switch: '<S14>/Abschalten, wenn n_diff < 1.01% nN1' */
  } else {
    /* Switch: '<S14>/Abschalten, wenn n_diff < 1.01% nN' */
    rty_M_Soll_0 = rtu_PMSM_In_Inport_3->Last_M;
  }

  /* End of Switch: '<S14>/Abschalten, wenn n_diff < 1.01% nN2' */
  /* End of Outputs for SubSystem: '<S11>/n_Ctrl_hysterese' */

  /* Product: '<S15>/Product2' incorporates:
   *  Constant: '<S13>/Constant3'
   *  Constant: '<S15>/Constant3'
   *  Product: '<S13>/Product2'
   */
  rtb_Product_a_tmp = struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNn;

  /* Update for UnitDelay: '<S15>/Unit Delay' incorporates:
   *  Constant: '<S15>/Constant3'
   *  Product: '<S15>/Product2'
   *  Sum: '<S15>/Add'
   *  Sum: '<S15>/Add1'
   */
  localDW->UnitDelay_DSTATE += (rtu_Soll_Drehzahl - localDW->UnitDelay_DSTATE) *
    rtb_Product_a_tmp;

  /* Update for UnitDelay: '<S13>/Unit Delay' incorporates:
   *  Constant: '<S11>/Constant'
   *  Gain: '<S11>/Gain1'
   *  Logic: '<S13>/Logical Operator'
   *  Product: '<S13>/Product1'
   *  Product: '<S13>/Product2'
   *  RelationalOperator: '<S13>/Relational Operator'
   *  RelationalOperator: '<S13>/Relational Operator1'
   *  Sum: '<S13>/Add'
   */
  localDW->UnitDelay_DSTATE_j += ((rtb_Add1_b <= struct_PMSM_Config.mot_M_N) &&
    (rtb_Add1_b >= -struct_PMSM_Config.mot_M_N) ? rtb_Product_j : 0.0F) *
    rtb_Product_a_tmp;
  return rty_M_Soll_0;
}

/* System initialize for enable system: '<S8>/Trajektorie_Erzeugung' */
static void Trajektorie_Erzeugung_Init(DW_Trajektorie_Erzeugung *localDW)
{
  /* InitializeConditions for Memory: '<S19>/Memory' */
  localDW->Memory_PreviousInput = true;

  /* SystemInitialize for Atomic SubSystem: '<S12>/Subsystem' */
  /* InitializeConditions for UnitDelay: '<S20>/Unit Delay2' */
  localDW->UnitDelay2_DSTATE = struct_ZM_In.Soll_Drehzahl;
  if (localDW->UnitDelay2_DSTATE < 0.0F) {
    localDW->UnitDelay2_DSTATE = -1.0F;
  } else {
    localDW->UnitDelay2_DSTATE = (float)(localDW->UnitDelay2_DSTATE > 0.0F);
  }

  /* End of InitializeConditions for UnitDelay: '<S20>/Unit Delay2' */
  /* End of SystemInitialize for SubSystem: '<S12>/Subsystem' */
}

/* System reset for enable system: '<S8>/Trajektorie_Erzeugung' */
static void Trajektorie_Erzeugung_Reset(DW_Trajektorie_Erzeugung *localDW)
{
  /* InitializeConditions for UnitDelay: '<S12>/Unit Delay1' */
  localDW->UnitDelay1_DSTATE = 0.0F;

  /* InitializeConditions for Memory: '<S19>/Memory' */
  localDW->Memory_PreviousInput = true;

  /* InitializeConditions for UnitDelay: '<S12>/Unit Delay' */
  localDW->UnitDelay_DSTATE = 0.0F;

  /* SystemReset for Atomic SubSystem: '<S12>/Subsystem' */
  /* InitializeConditions for UnitDelay: '<S20>/Unit Delay2' */
  localDW->UnitDelay2_DSTATE = struct_ZM_In.Soll_Drehzahl;
  if (localDW->UnitDelay2_DSTATE < 0.0F) {
    localDW->UnitDelay2_DSTATE = -1.0F;
  } else {
    localDW->UnitDelay2_DSTATE = (float)(localDW->UnitDelay2_DSTATE > 0.0F);
  }

  /* End of InitializeConditions for UnitDelay: '<S20>/Unit Delay2' */

  /* InitializeConditions for Memory: '<S21>/Memory' */
  localDW->Memory_PreviousInput_n = false;

  /* End of SystemReset for SubSystem: '<S12>/Subsystem' */
}

/* Disable for enable system: '<S8>/Trajektorie_Erzeugung' */
static void Trajektorie_Erzeugung_Disable(DW_Trajektorie_Erzeugung *localDW)
{
  localDW->Trajektorie_Erzeugung_MODE = false;
}

/* Output and update for enable system: '<S8>/Trajektorie_Erzeugung' */
static void Trajektorie_Erzeugung(bool rtu_En_Trapez, float rtu_Max_Drehzahl,
  float *rty_Soll_Drehzahl, bool rty_Dis[2], DW_Trajektorie_Erzeugung *localDW)
{
  float rtb_Saturation;
  float rtb_Switch3_p;
  int32_t rtb_Sign1;
  uint32_t rowIdx;
  bool rtb_Logic_idx_0;

  /* Outputs for Enabled SubSystem: '<S8>/Trajektorie_Erzeugung' incorporates:
   *  EnablePort: '<S12>/En_Trapez'
   */
  if (rtu_En_Trapez) {
    if (!localDW->Trajektorie_Erzeugung_MODE) {
      Trajektorie_Erzeugung_Reset(localDW);
      localDW->Trajektorie_Erzeugung_MODE = true;
    }

    /* CombinatorialLogic: '<S19>/Logic' incorporates:
     *  Constant: '<S17>/Constant'
     *  Constant: '<S18>/Constant'
     *  Memory: '<S19>/Memory'
     *  RelationalOperator: '<S17>/Compare'
     *  RelationalOperator: '<S18>/Compare'
     *  UnitDelay: '<S12>/Unit Delay1'
     */
    rtb_Logic_idx_0 = rtConstP.pooled5[((((uint32_t)(localDW->UnitDelay1_DSTATE <
      struct_Ctrl_Config.t_traj) << 1) + (uint32_t)(localDW->UnitDelay1_DSTATE >=
      struct_Ctrl_Config.t_traj)) << 1) + localDW->Memory_PreviousInput];

    /* Switch: '<S12>/Switch3' incorporates:
     *  Signum: '<S12>/Sign'
     */
    if (rtb_Logic_idx_0) {
      /* Signum: '<S12>/Sign' */
      if (rtu_Max_Drehzahl < 0.0F) {
        rtb_Sign1 = -1;
      } else {
        rtb_Sign1 = (rtu_Max_Drehzahl > 0.0F);
      }

      /* Switch: '<S12>/Switch' incorporates:
       *  Constant: '<S12>/max. V_step'
       *  Signum: '<S12>/Sign'
       */
      if (rtb_Sign1 > 0) {
        rtb_Switch3_p = 0.05F;
      } else {
        rtb_Switch3_p = -0.05F;
      }
    } else {
      if (rtu_Max_Drehzahl < 0.0F) {
        /* Signum: '<S12>/Sign' */
        rtb_Sign1 = -1;
      } else {
        /* Signum: '<S12>/Sign' */
        rtb_Sign1 = (rtu_Max_Drehzahl > 0.0F);
      }

      /* Switch: '<S12>/Switch' incorporates:
       *  Constant: '<S12>/max. V_step'
       *  Gain: '<S12>/Gain1'
       *  Signum: '<S12>/Sign'
       */
      if (rtb_Sign1 > 0) {
        rtb_Switch3_p = -0.05F;
      } else {
        rtb_Switch3_p = 0.05F;
      }
    }

    /* End of Switch: '<S12>/Switch3' */

    /* Saturate: '<S12>/Saturation' incorporates:
     *  UnitDelay: '<S12>/Unit Delay'
     */
    rtb_Saturation = fabsf(struct_ZM_In.Soll_Drehzahl);
    if (localDW->UnitDelay_DSTATE <= rtb_Saturation) {
      if (localDW->UnitDelay_DSTATE < -rtb_Saturation) {
        rtb_Saturation = -rtb_Saturation;
      } else {
        rtb_Saturation = localDW->UnitDelay_DSTATE;
      }
    }

    /* End of Saturate: '<S12>/Saturation' */

    /* Outputs for Atomic SubSystem: '<S12>/Subsystem' */
    /* Signum: '<S20>/Sign1' */
    if (rtb_Saturation < 0.0F) {
      rtb_Sign1 = -1;
    } else {
      rtb_Sign1 = (rtb_Saturation > 0.0F);
    }

    /* End of Signum: '<S20>/Sign1' */

    /* CombinatorialLogic: '<S21>/Logic' incorporates:
     *  Memory: '<S21>/Memory'
     *  RelationalOperator: '<S20>/Relational Operator'
     *  UnitDelay: '<S20>/Unit Delay2'
     */
    rowIdx = ((((uint32_t)(localDW->UnitDelay2_DSTATE != rtb_Sign1) << 1) +
               rtb_Logic_idx_0) << 1) + localDW->Memory_PreviousInput_n;
    rty_Dis[0U] = rtConstP.pooled5[rowIdx];
    rty_Dis[1U] = rtConstP.pooled5[rowIdx + 8U];

    /* Update for UnitDelay: '<S20>/Unit Delay2' */
    localDW->UnitDelay2_DSTATE = (float)rtb_Sign1;

    /* Update for Memory: '<S21>/Memory' */
    localDW->Memory_PreviousInput_n = rty_Dis[0];

    /* End of Outputs for SubSystem: '<S12>/Subsystem' */

    /* Switch: '<S12>/Switch1' incorporates:
     *  Constant: '<S12>/Constant'
     */
    if (rty_Dis[0]) {
      *rty_Soll_Drehzahl = 0.0F;
    } else {
      *rty_Soll_Drehzahl = rtb_Saturation;
    }

    /* End of Switch: '<S12>/Switch1' */

    /* Update for UnitDelay: '<S12>/Unit Delay1' incorporates:
     *  Constant: '<S12>/Constant1'
     *  Sum: '<S12>/Add1'
     */
    localDW->UnitDelay1_DSTATE += struct_Ctrl_Config.Tsample;

    /* Update for Memory: '<S19>/Memory' */
    localDW->Memory_PreviousInput = rtb_Logic_idx_0;

    /* Update for UnitDelay: '<S12>/Unit Delay' incorporates:
     *  Sum: '<S12>/Add'
     */
    localDW->UnitDelay_DSTATE = rtb_Switch3_p + rtb_Saturation;
  } else if (localDW->Trajektorie_Erzeugung_MODE) {
    Trajektorie_Erzeugung_Disable(localDW);
  }

  /* End of Outputs for SubSystem: '<S8>/Trajektorie_Erzeugung' */
}

/* System initialize for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_o_Init(DW_Drehzahlregelung *localDW)
{
  /* SystemInitialize for Enabled SubSystem: '<S8>/Trajektorie_Erzeugung' */
  Trajektorie_Erzeugung_Init(&localDW->Trajektorie_Erzeugung_b);

  /* End of SystemInitialize for SubSystem: '<S8>/Trajektorie_Erzeugung' */
}

/* Disable for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_Disable(DW_Drehzahlregelung *localDW)
{
  /* Disable for Enabled SubSystem: '<S8>/Trajektorie_Erzeugung' */
  if (localDW->Trajektorie_Erzeugung_b.Trajektorie_Erzeugung_MODE) {
    Trajektorie_Erzeugung_Disable(&localDW->Trajektorie_Erzeugung_b);
  }

  /* End of Disable for SubSystem: '<S8>/Trajektorie_Erzeugung' */
  localDW->Drehzahlregelung_MODE = false;
}

/* Output and update for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_h(bool rtu_Enable, float rtu_omega, const
  Bus_PMSM_In *rtu_PMSM_In_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  bool rty_Dis[2], float *rty_Soll_Moment, DW_Drehzahlregelung *localDW)
{
  float rtb_Soll_Drehzahl;

  /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (rtu_Enable) {
    localDW->Drehzahlregelung_MODE = true;

    /* Gain: '<S8>/Gain' */
    rtb_Soll_Drehzahl = GAIN_UMIN_TO_HZ * rtu_Bus_ZM_Out_Inport_3->Soll_Drehzahl;

    /* Outputs for Enabled SubSystem: '<S8>/Trajektorie_Erzeugung' */
    /* SignalConversion generated from: '<S12>/En_Trapez' */
    Trajektorie_Erzeugung(rtu_Bus_ZM_Out_Inport_3->En_Traj, rtb_Soll_Drehzahl,
                          &localDW->Switch1, rty_Dis,
                          &localDW->Trajektorie_Erzeugung_b);

    /* End of Outputs for SubSystem: '<S8>/Trajektorie_Erzeugung' */

    /* Switch: '<S8>/Switch' incorporates:
     *  Constant: '<S10>/Constant'
     *  RelationalOperator: '<S10>/Compare'
     */
    if (rtu_Bus_ZM_Out_Inport_3->Ist_Regelungsart == Trajektorie) {
      rtb_Soll_Drehzahl = localDW->Switch1;
    }

    /* Outputs for Atomic SubSystem: '<S8>/Drehzahlregelung' */
    *rty_Soll_Moment = Drehzahlregelung(rtb_Soll_Drehzahl, rtu_omega,
      rtu_PMSM_In_Inport_2, &localDW->Drehzahlregelung_p);

    /* End of Switch: '<S8>/Switch' */
    /* End of Outputs for SubSystem: '<S8>/Drehzahlregelung' */
  } else if (localDW->Drehzahlregelung_MODE) {
    Drehzahlregelung_Disable(localDW);
  }

  /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */
}

/* Output and update for atomic system: '<S9>/IDQCtrl' */
static void IDQCtrl(float rtu_ID, float rtu_IQ, float rtu_IDRef, float rtu_IQRef,
                    float rtu_OmegaMech, float *rty_UD, float *rty_UQ,
                    DW_IDQCtrl *localDW)
{
  float UnitDelay_DSTATE_tmp;
  float rtb_Add1_g;
  float rtb_Add1_oe;
  float rtb_Add3;
  float rtb_Gain2;
  float rtb_Product_a;
  float rtb_Product_n;

  /* Product: '<S31>/Product' incorporates:
   *  Constant: '<S31>/Constant'
   *  Constant: '<S31>/Constant1'
   *  Product: '<S31>/Product1'
   *  Sum: '<S31>/Add'
   */
  *rty_UQ = (rtu_IDRef * struct_PMSM_Config.mot_Lq +
             struct_PMSM_Config.mot_psi_pm) * rtu_OmegaMech;

  /* Gain: '<S25>/Gain2' incorporates:
   *  Constant: '<S25>/Constant2'
   */
  rtb_Gain2 = DIVIDE_TWO_BY_THREE * struct_Inv_Config.Udc;

  /* Product: '<S32>/Product' incorporates:
   *  Constant: '<S32>/Constant'
   *  Sum: '<S32>/Subtract'
   */
  rtb_Product_n = (rtu_IDRef - rtu_ID) * struct_Ctrl_Config.KPi;

  /* Sum: '<S32>/Add1' incorporates:
   *  UnitDelay: '<S32>/Unit Delay'
   */
  rtb_Add1_g = rtb_Product_n + localDW->UnitDelay_DSTATE;

  /* Switch: '<S35>/Switch2' incorporates:
   *  Gain: '<S25>/Gain1'
   *  RelationalOperator: '<S35>/LowerRelop1'
   *  RelationalOperator: '<S35>/UpperRelop'
   *  Switch: '<S35>/Switch'
   */
  if (rtb_Add1_g > rtb_Gain2) {
    *rty_UD = rtb_Gain2;
  } else if (rtb_Add1_g < -rtb_Gain2) {
    /* Switch: '<S35>/Switch' incorporates:
     *  Gain: '<S25>/Gain1'
     */
    *rty_UD = -rtb_Gain2;
  } else {
    *rty_UD = rtb_Add1_g;
  }

  /* End of Switch: '<S35>/Switch2' */

  /* Sum: '<S25>/Add1' incorporates:
   *  Constant: '<S30>/Constant'
   *  Product: '<S30>/Product'
   *  Product: '<S30>/Product1'
   */
  *rty_UD -= rtu_OmegaMech * rtu_IQRef * struct_PMSM_Config.mot_Ld;

  /* Sum: '<S34>/Add3' incorporates:
   *  Product: '<S34>/Product'
   *  Product: '<S34>/Product1'
   *  Sqrt: '<S34>/Sqrt'
   *  Sum: '<S34>/Add2'
   */
  rtb_Add3 = sqrtf(rtb_Gain2 * rtb_Gain2 - *rty_UD * *rty_UD) - *rty_UQ;

  /* Product: '<S33>/Product' incorporates:
   *  Constant: '<S33>/Constant'
   *  Sum: '<S33>/Subtract'
   */
  rtb_Product_a = (rtu_IQRef - rtu_IQ) * struct_Ctrl_Config.KPi;

  /* Sum: '<S33>/Add1' incorporates:
   *  UnitDelay: '<S33>/Unit Delay'
   */
  rtb_Add1_oe = rtb_Product_a + localDW->UnitDelay_DSTATE_k;

  /* Switch: '<S36>/Switch2' incorporates:
   *  Gain: '<S34>/Gain1'
   *  RelationalOperator: '<S36>/LowerRelop1'
   *  RelationalOperator: '<S36>/UpperRelop'
   *  Switch: '<S36>/Switch'
   */
  if (rtb_Add1_oe > rtb_Add3) {
    UnitDelay_DSTATE_tmp = rtb_Add3;
  } else if (rtb_Add1_oe < -rtb_Add3) {
    /* Switch: '<S36>/Switch' incorporates:
     *  Gain: '<S34>/Gain1'
     */
    UnitDelay_DSTATE_tmp = -rtb_Add3;
  } else {
    UnitDelay_DSTATE_tmp = rtb_Add1_oe;
  }

  /* Sum: '<S25>/Add' incorporates:
   *  Switch: '<S36>/Switch2'
   */
  *rty_UQ += UnitDelay_DSTATE_tmp;

  /* Product: '<S32>/Product2' incorporates:
   *  Constant: '<S32>/Constant3'
   *  Constant: '<S33>/Constant3'
   *  Product: '<S33>/Product2'
   */
  UnitDelay_DSTATE_tmp = struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNi;

  /* Update for UnitDelay: '<S32>/Unit Delay' incorporates:
   *  Constant: '<S32>/Constant3'
   *  Gain: '<S25>/Gain1'
   *  Logic: '<S32>/Logical Operator'
   *  Product: '<S32>/Product1'
   *  Product: '<S32>/Product2'
   *  RelationalOperator: '<S32>/Relational Operator'
   *  RelationalOperator: '<S32>/Relational Operator1'
   *  Sum: '<S32>/Add'
   */
  localDW->UnitDelay_DSTATE += ((rtb_Add1_g <= rtb_Gain2) && (rtb_Add1_g >=
    -rtb_Gain2) ? rtb_Product_n : 0.0F) * UnitDelay_DSTATE_tmp;

  /* Update for UnitDelay: '<S33>/Unit Delay' incorporates:
   *  Gain: '<S34>/Gain1'
   *  Logic: '<S33>/Logical Operator'
   *  Product: '<S33>/Product1'
   *  Product: '<S33>/Product2'
   *  RelationalOperator: '<S33>/Relational Operator'
   *  RelationalOperator: '<S33>/Relational Operator1'
   *  Sum: '<S33>/Add'
   */
  localDW->UnitDelay_DSTATE_k += ((rtb_Add1_oe <= rtb_Add3) && (rtb_Add1_oe >=
    -rtb_Add3) ? rtb_Product_a : 0.0F) * UnitDelay_DSTATE_tmp;
}

/* Output and update for atomic system: '<S9>/Ueberstromabschaltung' */
static bool Ueberstromabschaltung(float rtu_Iu, float rtu_Iv, float rtu_Iw)
{
  /* Logic: '<S26>/Logical Operator' incorporates:
   *  Abs: '<S26>/Abs'
   *  Abs: '<S26>/Abs1'
   *  Abs: '<S26>/Abs2'
   *  Constant: '<S26>/Constant'
   *  RelationalOperator: '<S26>/Relational Operator'
   *  RelationalOperator: '<S26>/Relational Operator1'
   *  RelationalOperator: '<S26>/Relational Operator2'
   */
  return (struct_PMSM_Config.mot_I_max < fabsf(rtu_Iu)) ||
    (struct_PMSM_Config.mot_I_max < fabsf(rtu_Iv)) ||
    (struct_PMSM_Config.mot_I_max < fabsf(rtu_Iw));
}

/* Output and update for atomic system: '<S9>/abc_zu_dq' */
static void abc_zu_dq(float rtu_theta, float rtu_pmsm_Iu, float rtu_pmsm_Iv,
                      float rtu_pmsm_Iw, float *rty_ctrl_Id, float *rty_ctrl_Iq)
{
  float rtb_Gain_k;
  float rtb_TrigonometricFunction;
  float rtb_TrigonometricFunction1;

  /* Gain: '<S37>/Gain' incorporates:
   *  Gain: '<S37>/Gain2'
   *  Gain: '<S37>/Gain7'
   *  Sum: '<S37>/Add'
   */
  rtb_Gain_k = ((-0.5F * rtu_pmsm_Iv + rtu_pmsm_Iu) + -0.5F * rtu_pmsm_Iw) *
    DIVIDE_TWO_BY_THREE;

  /* Trigonometry: '<S38>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = cosf(rtu_theta);

  /* Gain: '<S37>/sqrt(3)//2' */
  *rty_ctrl_Iq = -DIVIDE_SQRT_THREE_BY_TWO * rtu_pmsm_Iw;

  /* Gain: '<S37>/Gain1' incorporates:
   *  Gain: '<S37>/Gain5'
   *  Sum: '<S37>/Add1'
   */
  *rty_ctrl_Iq = (DIVIDE_SQRT_THREE_BY_TWO * rtu_pmsm_Iv + *rty_ctrl_Iq) *
    DIVIDE_TWO_BY_THREE;

  /* Trigonometry: '<S38>/Trigonometric Function' */
  rtb_TrigonometricFunction = sinf(rtu_theta);

  /* Sum: '<S38>/Add' incorporates:
   *  Product: '<S38>/Product'
   *  Product: '<S38>/Product1'
   */
  *rty_ctrl_Id = rtb_TrigonometricFunction1 * rtb_Gain_k +
    rtb_TrigonometricFunction * *rty_ctrl_Iq;

  /* Sum: '<S38>/Add1' incorporates:
   *  Product: '<S38>/Product2'
   *  Product: '<S38>/Product3'
   */
  *rty_ctrl_Iq = *rty_ctrl_Iq * rtb_TrigonometricFunction1 - rtb_Gain_k *
    rtb_TrigonometricFunction;
}

/* Output and update for atomic system: '<S9>/dq_zu_alphabeta' */
static void dq_zu_alphabeta(float rtu_theta, float rtu_valD, float rtu_valQ,
  float *rty_valAlpha, float *rty_valBeta)
{
  float rtb_TrigonometricFunction;
  float rtb_TrigonometricFunction1;

  /* Trigonometry: '<S29>/Trigonometric Function1' incorporates:
   *  Gain: '<S29>/Gain1'
   */
  rtb_TrigonometricFunction1 = cosf(-rtu_theta);

  /* Trigonometry: '<S29>/Trigonometric Function' incorporates:
   *  Gain: '<S29>/Gain1'
   */
  rtb_TrigonometricFunction = sinf(-rtu_theta);

  /* Sum: '<S29>/Add' incorporates:
   *  Product: '<S29>/Product'
   *  Product: '<S29>/Product1'
   */
  *rty_valAlpha = rtu_valD * rtb_TrigonometricFunction1 + rtu_valQ *
    rtb_TrigonometricFunction;

  /* Sum: '<S29>/Add1' incorporates:
   *  Product: '<S29>/Product2'
   *  Product: '<S29>/Product3'
   */
  *rty_valBeta = rtu_valQ * rtb_TrigonometricFunction1 - rtu_valD *
    rtb_TrigonometricFunction;
}

/* Output and update for atomic system: '<S3>/Stromregelung' */
static void Stromregelung(float rtu_Soll_Moment, const Bus_PMSM_Out
  *rtu_Bus_Live_Out_PMSM_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  float *rty_Ualpha, float *rty_Ubeta, DW_Stromregelung *localDW)
{
  float rtb_Add1;
  float rtb_Add_d;
  float rtb_Add_k;
  float rtb_IDRef;
  float rtb_IQRef;
  float rtb_Product1;
  float rtb_Product2;
  bool rtb_act_ab;

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
   *  Constant: '<S24>/Constant'
   *  Constant: '<S9>/Constant'
   *  Gain: '<S28>/Gain'
   *  RelationalOperator: '<S24>/Compare'
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
            rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2], &rtb_Add1, &rtb_Add_k);

  /* End of Outputs for SubSystem: '<S9>/abc_zu_dq' */

  /* Outputs for Atomic SubSystem: '<S9>/IDQCtrl' */
  IDQCtrl(rtb_Add1, rtb_Add_k, rtb_IDRef, rtb_IQRef, rtb_Product2, &rtb_Add1,
          &rtb_Add_d, &localDW->IDQCtrl_c);

  /* End of Outputs for SubSystem: '<S9>/IDQCtrl' */

  /* Outputs for Atomic SubSystem: '<S9>/dq_zu_alphabeta' */
  /* Sum: '<S9>/Add' incorporates:
   *  Constant: '<S9>/Constant3'
   *  Product: '<S9>/Product'
   */
  dq_zu_alphabeta(struct_Ctrl_Config.Tsample * rtb_Product2 + rtb_Product1,
                  rtb_Add1, rtb_Add_d, &rtb_Add_k, &rtb_Add1);

  /* End of Outputs for SubSystem: '<S9>/dq_zu_alphabeta' */

  /* Outputs for Atomic SubSystem: '<S9>/Ueberstromabschaltung' */
  rtb_act_ab = Ueberstromabschaltung(rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[0],
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[1],
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2]);

  /* End of Outputs for SubSystem: '<S9>/Ueberstromabschaltung' */

  /* Logic: '<S9>/Logical Operator' incorporates:
   *  Constant: '<S22>/Constant'
   *  Constant: '<S23>/Constant'
   *  Logic: '<S9>/Logical Operator1'
   *  RelationalOperator: '<S22>/Compare'
   *  RelationalOperator: '<S23>/Compare'
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
    *rty_Ualpha = rtb_Add_k;
    *rty_Ubeta = rtb_Add1;
  }

  /* End of Switch: '<S9>/Switch' */
}

/* System initialize for enable system: '<S1>/Regelung' */
static void Regelung_Init(DW_Regelung *localDW)
{
  /* SystemInitialize for Enabled SubSystem: '<S3>/Drehzahlregelung' */
  Drehzahlregelung_o_Init(&localDW->Drehzahlregelung_hk);

  /* End of SystemInitialize for SubSystem: '<S3>/Drehzahlregelung' */
}

/* Disable for enable system: '<S1>/Regelung' */
static void Regelung_Disable(DW_Regelung *localDW)
{
  /* Disable for Enabled SubSystem: '<S3>/Drehzahlregelung' */
  if (localDW->Drehzahlregelung_hk.Drehzahlregelung_MODE) {
    Drehzahlregelung_Disable(&localDW->Drehzahlregelung_hk);
  }

  /* End of Disable for SubSystem: '<S3>/Drehzahlregelung' */
  localDW->Regelung_MODE = false;
}

/* Output and update for enable system: '<S1>/Regelung' */
static void Regelung(bool rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_PMSM_In
                     *rtu_PMSM_In_Inport_2, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_3, float *rty_Ualpha, float
                     *rty_Ubeta, bool rty_Dis[2], DW_Regelung *localDW)
{
  /* Outputs for Enabled SubSystem: '<S1>/Regelung' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (rtu_Enable) {
    localDW->Regelung_MODE = true;

    /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' */
    /* RelationalOperator: '<S7>/Compare' incorporates:
     *  Constant: '<S7>/Constant'
     */
    Drehzahlregelung_h((rtu_Bus_ZM_Out_Inport_3->Ist_Regelungsart <= Drehzahl),
                       rtu_Bus_Live_Out_PMSM_Inport_1->pmsm_Omega_mech,
                       rtu_PMSM_In_Inport_2, rtu_Bus_ZM_Out_Inport_3, rty_Dis,
                       &localDW->Abschaltenwennn_diff101nN2,
                       &localDW->Drehzahlregelung_hk);

    /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */

    /* Outputs for Atomic SubSystem: '<S3>/Stromregelung' */
    Stromregelung(localDW->Abschaltenwennn_diff101nN2,
                  rtu_Bus_Live_Out_PMSM_Inport_1, rtu_Bus_ZM_Out_Inport_3,
                  rty_Ualpha, rty_Ubeta, &localDW->Stromregelung_a);

    /* End of Outputs for SubSystem: '<S3>/Stromregelung' */
  } else if (localDW->Regelung_MODE) {
    Regelung_Disable(localDW);
  }

  /* End of Outputs for SubSystem: '<S1>/Regelung' */
}

/* System initialize for atomic system: '<S4>/state_chart' */
static void state_chart_Init(Bus_ZM_Out *rty_Bus_ZM_Out)
{
  rty_Bus_ZM_Out->En_Traj = false;
  rty_Bus_ZM_Out->Pulsfreigabe = false;
  rty_Bus_ZM_Out->Ist_Status = Error_Status;
  rty_Bus_ZM_Out->Ist_Regelungsart = Error;
  rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;
  rty_Bus_ZM_Out->Soll_id = 0.0F;
  rty_Bus_ZM_Out->Soll_iq = 0.0F;
}

/* Output and update for atomic system: '<S4>/state_chart' */
static void state_chart(const Bus_ZM_In *rtu_Bus_ZM_In, bool rtu_Dis, Bus_ZM_Out
  *rty_Bus_ZM_Out, DW_state_chart *localDW)
{
  /* Chart: '<S4>/state_chart' */
  /* Gateway: uz_codegen/Zustandsmaschine/state_chart */
  /* During: uz_codegen/Zustandsmaschine/state_chart */
  if (localDW->is_active_c3_uz_codegen0 == 0) {
    /* Entry: uz_codegen/Zustandsmaschine/state_chart */
    localDW->is_active_c3_uz_codegen0 = 1U;

    /* Entry Internal: uz_codegen/Zustandsmaschine/state_chart */
    /* Transition: '<S39>:11' */
    localDW->is_c3_uz_codegen0 = IN_NoError;

    /* Entry Internal 'NoError': '<S39>:32' */
    /* Transition: '<S39>:45' */
    localDW->is_NoError = IN_Ready;

    /* Entry 'Ready': '<S39>:19' */
    /* '<S39>:19:2' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
    rty_Bus_ZM_Out->Ist_Status = Ready;

    /* '<S39>:19:3' Bus_ZM_Out.Pulsfreigabe = false; */
    rty_Bus_ZM_Out->Pulsfreigabe = false;

    /* '<S39>:19:4' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
    rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

    /* '<S39>:19:5' Bus_ZM_Out.En_Traj=false; */
    rty_Bus_ZM_Out->En_Traj = false;

    /* '<S39>:19:6' Bus_ZM_Out.Soll_Drehzahl = 0; */
    rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

    /* '<S39>:19:7' Bus_ZM_Out.Soll_id = 0; */
    rty_Bus_ZM_Out->Soll_id = 0.0F;

    /* '<S39>:19:8' Bus_ZM_Out.Soll_iq = 0; */
    rty_Bus_ZM_Out->Soll_iq = 0.0F;
  } else if (localDW->is_c3_uz_codegen0 == IN_Error) {
    /* During 'Error': '<S39>:10' */
    /* '<S39>:14:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == false && Bus_ZM_In.Soll_Status == Status_Ctrl.Ready); */
    if ((!rtu_Bus_ZM_In->Fehlermeldung) && (rtu_Bus_ZM_In->Soll_Status == Ready))
    {
      /* Transition: '<S39>:14' */
      localDW->is_c3_uz_codegen0 = IN_NoError;

      /* Entry Internal 'NoError': '<S39>:32' */
      /* Transition: '<S39>:45' */
      localDW->is_NoError = IN_Ready;

      /* Entry 'Ready': '<S39>:19' */
      /* '<S39>:19:2' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
      rty_Bus_ZM_Out->Ist_Status = Ready;

      /* '<S39>:19:3' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S39>:19:4' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

      /* '<S39>:19:5' Bus_ZM_Out.En_Traj=false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S39>:19:6' Bus_ZM_Out.Soll_Drehzahl = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

      /* '<S39>:19:7' Bus_ZM_Out.Soll_id = 0; */
      rty_Bus_ZM_Out->Soll_id = 0.0F;

      /* '<S39>:19:8' Bus_ZM_Out.Soll_iq = 0; */
      rty_Bus_ZM_Out->Soll_iq = 0.0F;
    } else {
      /* '<S39>:10:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Error_Status; */
      rty_Bus_ZM_Out->Ist_Status = Error_Status;

      /* '<S39>:10:4' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S39>:10:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Error; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Error;

      /* '<S39>:10:6' Bus_ZM_Out.En_Traj = false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S39>:10:7' Bus_ZM_Out.Soll_Drehzahl = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

      /* '<S39>:10:8' Bus_ZM_Out.Soll_id = 0; */
      rty_Bus_ZM_Out->Soll_id = 0.0F;

      /* '<S39>:10:9' Bus_ZM_Out.Soll_iq = 0; */
      rty_Bus_ZM_Out->Soll_iq = 0.0F;
    }

    /* During 'NoError': '<S39>:32' */
    /* '<S39>:15:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == true); */
  } else if (rtu_Bus_ZM_In->Fehlermeldung) {
    /* Transition: '<S39>:15' */
    /* Exit Internal 'NoError': '<S39>:32' */
    /* Exit Internal 'Run': '<S39>:20' */
    /* Exit Internal 'Trapez': '<S39>:54' */
    localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
    localDW->is_Run = IN_NO_ACTIVE_CHILD;
    localDW->is_NoError = IN_NO_ACTIVE_CHILD;
    localDW->is_c3_uz_codegen0 = IN_Error;
  } else if (localDW->is_NoError == IN_Ready) {
    /* During 'Ready': '<S39>:19' */
    /* '<S39>:25:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Status == Status_Ctrl.En); */
    if (rtu_Bus_ZM_In->Soll_Status == En) {
      /* Transition: '<S39>:25' */
      localDW->is_NoError = IN_Run;

      /* Entry Internal 'Run': '<S39>:20' */
      /* Transition: '<S39>:55' */
      localDW->is_Run = IN_nCtrl;
    } else {
      /* '<S39>:19:2' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
      rty_Bus_ZM_Out->Ist_Status = Ready;

      /* '<S39>:19:3' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S39>:19:4' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

      /* '<S39>:19:5' Bus_ZM_Out.En_Traj=false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S39>:19:6' Bus_ZM_Out.Soll_Drehzahl = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

      /* '<S39>:19:7' Bus_ZM_Out.Soll_id = 0; */
      rty_Bus_ZM_Out->Soll_id = 0.0F;

      /* '<S39>:19:8' Bus_ZM_Out.Soll_iq = 0; */
      rty_Bus_ZM_Out->Soll_iq = 0.0F;
    }

    /* During 'Run': '<S39>:20' */
    /* '<S39>:26:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Status == Status_Ctrl.Dis); */
  } else if (rtu_Bus_ZM_In->Soll_Status == Dis) {
    /* Transition: '<S39>:26' */
    /* Exit Internal 'Run': '<S39>:20' */
    /* Exit Internal 'Trapez': '<S39>:54' */
    localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
    localDW->is_Run = IN_NO_ACTIVE_CHILD;
    localDW->is_NoError = IN_Ready;

    /* Entry 'Ready': '<S39>:19' */
    /* '<S39>:19:2' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
    rty_Bus_ZM_Out->Ist_Status = Ready;

    /* '<S39>:19:3' Bus_ZM_Out.Pulsfreigabe = false; */
    rty_Bus_ZM_Out->Pulsfreigabe = false;

    /* '<S39>:19:4' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
    rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

    /* '<S39>:19:5' Bus_ZM_Out.En_Traj=false; */
    rty_Bus_ZM_Out->En_Traj = false;

    /* '<S39>:19:6' Bus_ZM_Out.Soll_Drehzahl = 0; */
    rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

    /* '<S39>:19:7' Bus_ZM_Out.Soll_id = 0; */
    rty_Bus_ZM_Out->Soll_id = 0.0F;

    /* '<S39>:19:8' Bus_ZM_Out.Soll_iq = 0; */
    rty_Bus_ZM_Out->Soll_iq = 0.0F;
  } else {
    /* '<S39>:20:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Run; */
    rty_Bus_ZM_Out->Ist_Status = Run;

    /* '<S39>:20:4' Bus_ZM_Out.Pulsfreigabe = true; */
    rty_Bus_ZM_Out->Pulsfreigabe = true;
    switch (localDW->is_Run) {
     case IN_Stromregelung:
      /* During 'Stromregelung': '<S39>:86' */
      /* '<S39>:92:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Strom); */
      if (rtu_Bus_ZM_In->Soll_Regelungsart != Strom) {
        /* Transition: '<S39>:92' */
        localDW->is_Run = IN_nCtrl;
      } else {
        /* '<S39>:86:3' Bus_ZM_Out.Soll_id = Bus_ZM_In.Soll_id; */
        rty_Bus_ZM_Out->Soll_id = rtu_Bus_ZM_In->Soll_id;

        /* '<S39>:86:4' Bus_ZM_Out.Soll_iq = Bus_ZM_In.Soll_iq; */
        rty_Bus_ZM_Out->Soll_iq = rtu_Bus_ZM_In->Soll_iq;

        /* '<S39>:86:5' Bus_ZM_Out.Soll_Drehzahl = 0; */
        rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

        /* '<S39>:86:6' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Strom; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Strom;
      }
      break;

     case IN_Trapez:
      /* During 'Trapez': '<S39>:54' */
      /* '<S39>:90:1' sf_internal_predicateOutput = 0 | (Dis == 1 || Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Trajektorie); */
      if (rtu_Dis || (rtu_Bus_ZM_In->Soll_Regelungsart != Trajektorie)) {
        /* Transition: '<S39>:90' */
        /* Exit Internal 'Trapez': '<S39>:54' */
        localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
        localDW->is_Run = IN_nCtrl;
      } else {
        /* '<S39>:54:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Trajektorie; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Trajektorie;

        /* '<S39>:54:4' Bus_ZM_Out.Soll_Drehzahl = Bus_ZM_In.Soll_Drehzahl; */
        rty_Bus_ZM_Out->Soll_Drehzahl = rtu_Bus_ZM_In->Soll_Drehzahl;

        /* '<S39>:54:5' Bus_ZM_Out.Soll_id = 0; */
        rty_Bus_ZM_Out->Soll_id = 0.0F;

        /* '<S39>:54:6' Bus_ZM_Out.Soll_iq = 0; */
        rty_Bus_ZM_Out->Soll_iq = 0.0F;
        if (localDW->is_Trapez == IN_Run_c) {
          /* During 'Run': '<S39>:68' */
          /* '<S39>:70:1' sf_internal_predicateOutput = 0 | (Dis == 1); */
          /* '<S39>:68:2' Bus_ZM_Out.En_Traj = true; */
          rty_Bus_ZM_Out->En_Traj = true;

          /* During 'Warten': '<S39>:66' */
          /* '<S39>:69:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Start_Traj == 1); */
        } else if (rtu_Bus_ZM_In->Start_Traj == 1.0F) {
          /* Transition: '<S39>:69' */
          localDW->is_Trapez = IN_Run_c;

          /* Entry 'Run': '<S39>:68' */
          /* '<S39>:68:2' Bus_ZM_Out.En_Traj = true; */
          rty_Bus_ZM_Out->En_Traj = true;
        } else {
          /* '<S39>:66:2' Bus_ZM_Out.En_Traj = false; */
          rty_Bus_ZM_Out->En_Traj = false;
        }
      }
      break;

     default:
      /* During 'nCtrl': '<S39>:56' */
      /* '<S39>:89:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Trajektorie); */
      switch (rtu_Bus_ZM_In->Soll_Regelungsart) {
       case Trajektorie:
        /* Transition: '<S39>:89' */
        localDW->is_Run = IN_Trapez;

        /* Entry Internal 'Trapez': '<S39>:54' */
        /* Transition: '<S39>:67' */
        localDW->is_Trapez = IN_Warten;

        /* Entry 'Warten': '<S39>:66' */
        /* '<S39>:66:2' Bus_ZM_Out.En_Traj = false; */
        rty_Bus_ZM_Out->En_Traj = false;
        break;

       case Strom:
        /* '<S39>:91:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Strom); */
        /* Transition: '<S39>:91' */
        localDW->is_Run = IN_Stromregelung;
        break;

       default:
        /* '<S39>:56:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

        /* '<S39>:56:4' Bus_ZM_Out.Soll_Drehzahl = Bus_ZM_In.Soll_Drehzahl; */
        rty_Bus_ZM_Out->Soll_Drehzahl = rtu_Bus_ZM_In->Soll_Drehzahl;

        /* '<S39>:56:5' Bus_ZM_Out.Soll_id = 0; */
        rty_Bus_ZM_Out->Soll_id = 0.0F;

        /* '<S39>:56:6' Bus_ZM_Out.Soll_iq = 0; */
        rty_Bus_ZM_Out->Soll_iq = 0.0F;
        break;
      }
      break;
    }
  }

  /* End of Chart: '<S4>/state_chart' */
}

/* System initialize for atomic system: '<S1>/Zustandsmaschine' */
static void Zustandsmaschine_Init(Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1)
{
  /* SystemInitialize for Chart: '<S4>/state_chart' */
  state_chart_Init(rty_Bus_ZM_Out_Outport_1);
}

/* Output and update for atomic system: '<S1>/Zustandsmaschine' */
static void Zustandsmaschine(const Bus_ZM_In *rtu_Bus_ZM_In_Inport_1, bool
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
  Zustandsmaschine(&rtU->ZM_In, rtDW->UnitDelay_DSTATE, &rtDW->Bus_ZM_Out_o,
                   &rtDW->Zustandsmaschine_k);

  /* End of Outputs for SubSystem: '<S1>/Zustandsmaschine' */

  /* Outputs for Enabled SubSystem: '<S1>/Regelung' */

  /* SignalConversion generated from: '<S3>/Enable' */
  Regelung(rtDW->Bus_ZM_Out_o.Pulsfreigabe, &rtU->PMSM_Out, &rtU->PMSM_In,
           &rtDW->Bus_ZM_Out_o, &rtDW->Switch, &rtDW->Switch1, rtDW->Logic,
           &rtDW->Regelung_e);

  /* End of Outputs for SubSystem: '<S1>/Regelung' */

  /* Outputs for Atomic SubSystem: '<S1>/Raumzeigermodulation' */

  /* BusCreator generated from: '<S1>/Bus_Ctrl_Out_BusCreator' incorporates:
   *  Logic: '<S1>/Abschaten, wenn kein Zeiger vorhanden'
   *  Logic: '<S1>/Abschaten, wenn kein Zeiger vorhanden1'
   *  Outport: '<Root>/Bus_Ctrl_Out'
   */
  Raumzeigermodulation(rtDW->Switch, rtDW->Switch1,
                       rtY->Bus_Ctrl_Out_g.Dutycycle);

  /* End of Outputs for SubSystem: '<S1>/Raumzeigermodulation' */
  rtY->Bus_Ctrl_Out_g.act_pwm = (((rtDW->Switch != 0.0F) || (rtDW->Switch1 !=
    0.0F)) && rtDW->Bus_ZM_Out_o.Pulsfreigabe);
  rtY->Bus_Ctrl_Out_g.ctrl_Ualpha = rtDW->Switch;
  rtY->Bus_Ctrl_Out_g.ctrl_Ubeta = rtDW->Switch1;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  rtDW->UnitDelay_DSTATE = rtDW->Logic[0];
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;

  /* Registration code */

  /* states (dwork) */
  {
    rtDW->Bus_ZM_Out_o = uz_codegen0_rtZBus_ZM_Out;
  }

  /* external inputs */
  rtU->ZM_In = uz_codegen0_rtZBus_ZM_In;

  /* SystemInitialize for Atomic SubSystem: '<S1>/Zustandsmaschine' */
  Zustandsmaschine_Init(&rtDW->Bus_ZM_Out_o);

  /* End of SystemInitialize for SubSystem: '<S1>/Zustandsmaschine' */

  /* SystemInitialize for Enabled SubSystem: '<S1>/Regelung' */
  Regelung_Init(&rtDW->Regelung_e);

  /* End of SystemInitialize for SubSystem: '<S1>/Regelung' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
