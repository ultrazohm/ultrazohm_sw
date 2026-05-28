/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 10.17
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Thu May 21 14:36:31 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objective: Execution efficiency
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
#define IN_Run_i                       ((uint8_t)1U)
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
  0.00005F,
  0.00005F,
  0.004F,
  25.0F,
  0.0002F,
  0.0008F, //0008F
  10.0F,	//13
  0.005F,
  -0.005F,
  0.2F,
  1.0e-6F,
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
                                        *   '<S11>/Constant'
                                        *   '<S11>/Constant3'
                                        *   '<S12>/Constant3'
                                        *   '<S24>/Constant'
                                        *   '<S24>/Constant3'
                                        *   '<S25>/Constant'
                                        *   '<S25>/Constant3'
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
                                        *   '<S10>/Constant'
                                        *   '<S18>/Constant'
                                        *   '<S20>/Gain'
                                        *   '<S22>/Constant'
                                        *   '<S23>/Constant'
                                        *   '<S23>/Constant1'
                                        */

Bus_Inv_Config struct_Inv_Config = {
  PT1,
  540.0F,
  1.0F,
  20000.0F,
  false
} ;                                    /* Variable: struct_Inv_Config
                                        * Referenced by:
                                        *   '<S2>/Constant'
                                        *   '<S17>/Constant2'
                                        */

static void MinimaleSchaltzeit(const float rtu_Dutycycle[3], float rty_Out1[3]);
static void raumzeigermodulation(float rtu_Ualpha, float rtu_Ubeta, float
  rtu_Udc, float *rty_Dutycycle_A, float *rty_Dutycycle_B, float
  *rty_Dutycycle_C, float *rty_Sektor, float *rty_Quadrant);
static void Raumzeigermodulation(float rtu_Ualpha, float rtu_Ubeta, float
  rty_Dutycycle_A[3]);
static float Drehzahlregelung(float rtu_Soll_Drehzahl, float rtu_omega,
  DW_Drehzahlregelung_h *localDW);
static void Drehzahlregelung_o_Init(bool *rty_Dis);
static void Drehzahlregelung_c(bool rtu_Enable, float rtu_omega, const
  Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_2, bool *rty_Dis, float *rty_Soll_Moment,
  DW_Drehzahlregelung *localDW);
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
static void Regelung_Init(bool *rty_Dis);
static void Regelung(bool rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_2, float *rty_Ualpha, float
                     *rty_Ubeta, bool *rty_Dis, DW_Regelung *localDW);
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
  false,                               /* Start_Traj */
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
static float Drehzahlregelung(float rtu_Soll_Drehzahl, float rtu_omega,
  DW_Drehzahlregelung_h *localDW)
{
  float rty_M_Soll_0;
  float UnitDelay_DSTATE_tmp;
  float rtb_Add1_gm;
  float rtb_Product_i;

  /* Product: '<S11>/Product' incorporates:
   *  Constant: '<S11>/Constant'
   *  Gain: '<S10>/Gain'
   *  Sum: '<S11>/Subtract'
   *  UnitDelay: '<S12>/Unit Delay'
   */
  rtb_Product_i = (localDW->UnitDelay_DSTATE - GAIN_RADS_TO_HZ * rtu_omega) *
    struct_Ctrl_Config.KPn;

  /* Sum: '<S11>/Add1' incorporates:
   *  UnitDelay: '<S11>/Unit Delay'
   */
  rtb_Add1_gm = rtb_Product_i + localDW->UnitDelay_DSTATE_d;

  /* Switch: '<S13>/Switch2' incorporates:
   *  Constant: '<S10>/Constant'
   *  Gain: '<S10>/Gain1'
   *  RelationalOperator: '<S13>/LowerRelop1'
   *  RelationalOperator: '<S13>/UpperRelop'
   *  Switch: '<S13>/Switch'
   */
  if (rtb_Add1_gm > struct_PMSM_Config.mot_M_N) {
    rty_M_Soll_0 = struct_PMSM_Config.mot_M_N;
  } else if (rtb_Add1_gm < -struct_PMSM_Config.mot_M_N) {
    /* Switch: '<S13>/Switch' incorporates:
     *  Gain: '<S10>/Gain1'
     */
    rty_M_Soll_0 = -struct_PMSM_Config.mot_M_N;
  } else {
    rty_M_Soll_0 = rtb_Add1_gm;
  }

  /* End of Switch: '<S13>/Switch2' */

  /* Product: '<S12>/Product2' incorporates:
   *  Constant: '<S11>/Constant3'
   *  Constant: '<S12>/Constant3'
   *  Product: '<S11>/Product2'
   */
  UnitDelay_DSTATE_tmp = struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNn;

  /* Update for UnitDelay: '<S12>/Unit Delay' incorporates:
   *  Constant: '<S12>/Constant3'
   *  Product: '<S12>/Product2'
   *  Sum: '<S12>/Add'
   *  Sum: '<S12>/Add1'
   */
  localDW->UnitDelay_DSTATE += (rtu_Soll_Drehzahl - localDW->UnitDelay_DSTATE) *
    UnitDelay_DSTATE_tmp;

  /* Update for UnitDelay: '<S11>/Unit Delay' incorporates:
   *  Constant: '<S10>/Constant'
   *  Gain: '<S10>/Gain1'
   *  Logic: '<S11>/Logical Operator'
   *  Product: '<S11>/Product1'
   *  Product: '<S11>/Product2'
   *  RelationalOperator: '<S11>/Relational Operator'
   *  RelationalOperator: '<S11>/Relational Operator1'
   *  Sum: '<S11>/Add'
   */
  localDW->UnitDelay_DSTATE_d += ((rtb_Add1_gm <= struct_PMSM_Config.mot_M_N) &&
    (rtb_Add1_gm >= -struct_PMSM_Config.mot_M_N) ? rtb_Product_i : 0.0F) *
    UnitDelay_DSTATE_tmp;
  return rty_M_Soll_0;
}

/* System initialize for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_o_Init(bool *rty_Dis)
{
  /* SystemInitialize for SignalConversion generated from: '<S8>/Dis' */
  *rty_Dis = false;
}

/* Output and update for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_c(bool rtu_Enable, float rtu_omega, const
  Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_2, bool *rty_Dis, float *rty_Soll_Moment,
  DW_Drehzahlregelung *localDW)
{
  /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (rtu_Enable) {
    /* SignalConversion generated from: '<S8>/Dis' */
    *rty_Dis = false;

    /* Outputs for Atomic SubSystem: '<S8>/Drehzahlregelung' */
    /* Gain: '<S8>/Gain' */
    *rty_Soll_Moment = Drehzahlregelung(GAIN_UMIN_TO_HZ *
      rtu_Bus_ZM_Out_Inport_2->Soll_Drehzahl, rtu_omega,
      &localDW->Drehzahlregelung_i);

    /* End of Outputs for SubSystem: '<S8>/Drehzahlregelung' */
  }

  /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */
}

/* Output and update for atomic system: '<S9>/IDQCtrl' */
static void IDQCtrl(float rtu_ID, float rtu_IQ, float rtu_IDRef, float rtu_IQRef,
                    float rtu_OmegaMech, float *rty_UD, float *rty_UQ,
                    DW_IDQCtrl *localDW)
{
  float UnitDelay_DSTATE_tmp;
  float rtb_Add1_b;
  float rtb_Add1_k;
  float rtb_Add3;
  float rtb_Gain2;
  float rtb_Product_h;
  float rtb_Product_m;

  /* Product: '<S23>/Product' incorporates:
   *  Constant: '<S23>/Constant'
   *  Constant: '<S23>/Constant1'
   *  Product: '<S23>/Product1'
   *  Sum: '<S23>/Add'
   */
  *rty_UQ = (rtu_IDRef * struct_PMSM_Config.mot_Ld +
             struct_PMSM_Config.mot_psi_pm) * rtu_OmegaMech;

  /* Gain: '<S17>/Gain2' incorporates:
   *  Constant: '<S17>/Constant2'
   */
  rtb_Gain2 = DIVIDE_TWO_BY_THREE * struct_Inv_Config.Udc;

  /* Product: '<S24>/Product' incorporates:
   *  Constant: '<S24>/Constant'
   *  Sum: '<S24>/Subtract'
   */
  rtb_Product_m = (rtu_IDRef - rtu_ID) * struct_Ctrl_Config.KPi;

  /* Sum: '<S24>/Add1' incorporates:
   *  UnitDelay: '<S24>/Unit Delay'
   */
  rtb_Add1_k = rtb_Product_m + localDW->UnitDelay_DSTATE;

  /* Switch: '<S27>/Switch2' incorporates:
   *  Gain: '<S17>/Gain1'
   *  RelationalOperator: '<S27>/LowerRelop1'
   *  RelationalOperator: '<S27>/UpperRelop'
   *  Switch: '<S27>/Switch'
   */
  if (rtb_Add1_k > rtb_Gain2) {
    *rty_UD = rtb_Gain2;
  } else if (rtb_Add1_k < -rtb_Gain2) {
    /* Switch: '<S27>/Switch' incorporates:
     *  Gain: '<S17>/Gain1'
     */
    *rty_UD = -rtb_Gain2;
  } else {
    *rty_UD = rtb_Add1_k;
  }

  /* End of Switch: '<S27>/Switch2' */

  /* Sum: '<S17>/Add1' incorporates:
   *  Constant: '<S22>/Constant'
   *  Product: '<S22>/Product'
   *  Product: '<S22>/Product1'
   */
  *rty_UD -= rtu_OmegaMech * rtu_IQRef * struct_PMSM_Config.mot_Lq;

  /* Sum: '<S26>/Add3' incorporates:
   *  Product: '<S26>/Product'
   *  Product: '<S26>/Product1'
   *  Sqrt: '<S26>/Sqrt'
   *  Sum: '<S26>/Add2'
   */
  rtb_Add3 = sqrtf(rtb_Gain2 * rtb_Gain2 - *rty_UD * *rty_UD) - *rty_UQ;

  /* Product: '<S25>/Product' incorporates:
   *  Constant: '<S25>/Constant'
   *  Sum: '<S25>/Subtract'
   */
  rtb_Product_h = (rtu_IQRef - rtu_IQ) * struct_Ctrl_Config.KPi;

  /* Sum: '<S25>/Add1' incorporates:
   *  UnitDelay: '<S25>/Unit Delay'
   */
  rtb_Add1_b = rtb_Product_h + localDW->UnitDelay_DSTATE_f;

  /* Switch: '<S28>/Switch2' incorporates:
   *  Gain: '<S26>/Gain1'
   *  RelationalOperator: '<S28>/LowerRelop1'
   *  RelationalOperator: '<S28>/UpperRelop'
   *  Switch: '<S28>/Switch'
   */
  if (rtb_Add1_b > rtb_Add3) {
    UnitDelay_DSTATE_tmp = rtb_Add3;
  } else if (rtb_Add1_b < -rtb_Add3) {
    /* Switch: '<S28>/Switch' incorporates:
     *  Gain: '<S26>/Gain1'
     */
    UnitDelay_DSTATE_tmp = -rtb_Add3;
  } else {
    UnitDelay_DSTATE_tmp = rtb_Add1_b;
  }

  /* Sum: '<S17>/Add' incorporates:
   *  Switch: '<S28>/Switch2'
   */
  *rty_UQ += UnitDelay_DSTATE_tmp;

  /* Product: '<S24>/Product2' incorporates:
   *  Constant: '<S24>/Constant3'
   *  Constant: '<S25>/Constant3'
   *  Product: '<S25>/Product2'
   */
  UnitDelay_DSTATE_tmp = struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNi;

  /* Update for UnitDelay: '<S24>/Unit Delay' incorporates:
   *  Constant: '<S24>/Constant3'
   *  Gain: '<S17>/Gain1'
   *  Logic: '<S24>/Logical Operator'
   *  Product: '<S24>/Product1'
   *  Product: '<S24>/Product2'
   *  RelationalOperator: '<S24>/Relational Operator'
   *  RelationalOperator: '<S24>/Relational Operator1'
   *  Sum: '<S24>/Add'
   */
  localDW->UnitDelay_DSTATE += ((rtb_Add1_k <= rtb_Gain2) && (rtb_Add1_k >=
    -rtb_Gain2) ? rtb_Product_m : 0.0F) * UnitDelay_DSTATE_tmp;

  /* Update for UnitDelay: '<S25>/Unit Delay' incorporates:
   *  Gain: '<S26>/Gain1'
   *  Logic: '<S25>/Logical Operator'
   *  Product: '<S25>/Product1'
   *  Product: '<S25>/Product2'
   *  RelationalOperator: '<S25>/Relational Operator'
   *  RelationalOperator: '<S25>/Relational Operator1'
   *  Sum: '<S25>/Add'
   */
  localDW->UnitDelay_DSTATE_f += ((rtb_Add1_b <= rtb_Add3) && (rtb_Add1_b >=
    -rtb_Add3) ? rtb_Product_h : 0.0F) * UnitDelay_DSTATE_tmp;
}

/* Output and update for atomic system: '<S9>/Ueberstromabschaltung' */
static bool Ueberstromabschaltung(float rtu_Iu, float rtu_Iv, float rtu_Iw)
{
  /* Logic: '<S18>/Logical Operator' incorporates:
   *  Abs: '<S18>/Abs'
   *  Abs: '<S18>/Abs1'
   *  Abs: '<S18>/Abs2'
   *  Constant: '<S18>/Constant'
   *  RelationalOperator: '<S18>/Relational Operator'
   *  RelationalOperator: '<S18>/Relational Operator1'
   *  RelationalOperator: '<S18>/Relational Operator2'
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

  /* Gain: '<S29>/Gain' incorporates:
   *  Gain: '<S29>/Gain2'
   *  Gain: '<S29>/Gain7'
   *  Sum: '<S29>/Add'
   */
  rtb_Gain_k = ((-0.5F * rtu_pmsm_Iv + rtu_pmsm_Iu) + -0.5F * rtu_pmsm_Iw) *
    DIVIDE_TWO_BY_THREE;

  /* Trigonometry: '<S30>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = cosf(rtu_theta);

  /* Gain: '<S29>/sqrt(3)//2' */
  *rty_ctrl_Iq = -DIVIDE_SQRT_THREE_BY_TWO * rtu_pmsm_Iw;

  /* Gain: '<S29>/Gain1' incorporates:
   *  Gain: '<S29>/Gain5'
   *  Sum: '<S29>/Add1'
   */
  *rty_ctrl_Iq = (DIVIDE_SQRT_THREE_BY_TWO * rtu_pmsm_Iv + *rty_ctrl_Iq) *
    DIVIDE_TWO_BY_THREE;

  /* Trigonometry: '<S30>/Trigonometric Function' */
  rtb_TrigonometricFunction = sinf(rtu_theta);

  /* Sum: '<S30>/Add' incorporates:
   *  Product: '<S30>/Product'
   *  Product: '<S30>/Product1'
   */
  *rty_ctrl_Id = rtb_TrigonometricFunction1 * rtb_Gain_k +
    rtb_TrigonometricFunction * *rty_ctrl_Iq;

  /* Sum: '<S30>/Add1' incorporates:
   *  Product: '<S30>/Product2'
   *  Product: '<S30>/Product3'
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

  /* Trigonometry: '<S21>/Trigonometric Function1' incorporates:
   *  Gain: '<S21>/Gain1'
   */
  rtb_TrigonometricFunction1 = cosf(-rtu_theta);

  /* Trigonometry: '<S21>/Trigonometric Function' incorporates:
   *  Gain: '<S21>/Gain1'
   */
  rtb_TrigonometricFunction = sinf(-rtu_theta);

  /* Sum: '<S21>/Add' incorporates:
   *  Product: '<S21>/Product'
   *  Product: '<S21>/Product1'
   */
  *rty_valAlpha = rtu_valD * rtb_TrigonometricFunction1 + rtu_valQ *
    rtb_TrigonometricFunction;

  /* Sum: '<S21>/Add1' incorporates:
   *  Product: '<S21>/Product2'
   *  Product: '<S21>/Product3'
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
  float rtb_Add_o;
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
   *  Constant: '<S16>/Constant'
   *  Constant: '<S9>/Constant'
   *  Gain: '<S20>/Gain'
   *  RelationalOperator: '<S16>/Compare'
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
            rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2], &rtb_Add1, &rtb_Add_o);

  /* End of Outputs for SubSystem: '<S9>/abc_zu_dq' */

  /* Outputs for Atomic SubSystem: '<S9>/IDQCtrl' */
  IDQCtrl(rtb_Add1, rtb_Add_o, rtb_IDRef, rtb_IQRef, rtb_Product2, &rtb_Add1,
          &rtb_Add_d, &localDW->IDQCtrl_o);

  /* End of Outputs for SubSystem: '<S9>/IDQCtrl' */

  /* Outputs for Atomic SubSystem: '<S9>/dq_zu_alphabeta' */
  /* Sum: '<S9>/Add' incorporates:
   *  Constant: '<S9>/Constant3'
   *  Product: '<S9>/Product'
   */
  dq_zu_alphabeta(struct_Ctrl_Config.Tsample * rtb_Product2 + rtb_Product1,
                  rtb_Add1, rtb_Add_d, &rtb_Add_o, &rtb_Add1);

  /* End of Outputs for SubSystem: '<S9>/dq_zu_alphabeta' */

  /* Outputs for Atomic SubSystem: '<S9>/Ueberstromabschaltung' */
  rtb_act_ab = Ueberstromabschaltung(rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[0],
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[1],
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2]);

  /* End of Outputs for SubSystem: '<S9>/Ueberstromabschaltung' */

  /* Logic: '<S9>/Logical Operator' incorporates:
   *  Constant: '<S14>/Constant'
   *  Constant: '<S15>/Constant'
   *  Logic: '<S9>/Logical Operator1'
   *  RelationalOperator: '<S14>/Compare'
   *  RelationalOperator: '<S15>/Compare'
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
    *rty_Ualpha = rtb_Add_o;
    *rty_Ubeta = rtb_Add1;
  }

  /* End of Switch: '<S9>/Switch' */
}

/* System initialize for enable system: '<S1>/Regelung' */
static void Regelung_Init(bool *rty_Dis)
{
  /* SystemInitialize for Enabled SubSystem: '<S3>/Drehzahlregelung' */
  Drehzahlregelung_o_Init(rty_Dis);

  /* End of SystemInitialize for SubSystem: '<S3>/Drehzahlregelung' */
}

/* Output and update for enable system: '<S1>/Regelung' */
static void Regelung(bool rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_2, float *rty_Ualpha, float
                     *rty_Ubeta, bool *rty_Dis, DW_Regelung *localDW)
{
  /* Outputs for Enabled SubSystem: '<S1>/Regelung' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (rtu_Enable) {
    /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' */
    /* RelationalOperator: '<S7>/Compare' incorporates:
     *  Constant: '<S7>/Constant'
     */
    Drehzahlregelung_c((rtu_Bus_ZM_Out_Inport_2->Ist_Regelungsart <= Drehzahl),
                       rtu_Bus_Live_Out_PMSM_Inport_1->pmsm_Omega_mech,
                       rtu_Bus_ZM_Out_Inport_2, rty_Dis, &localDW->Switch2,
                       &localDW->Drehzahlregelung_ck);

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
    /* Transition: '<S31>:11' */
    localDW->is_c3_uz_codegen0 = IN_NoError;

    /* Entry Internal 'NoError': '<S31>:32' */
    /* Transition: '<S31>:45' */
    localDW->is_NoError = IN_Ready;

    /* Entry 'Ready': '<S31>:19' */
    /* '<S31>:19:2' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
    rty_Bus_ZM_Out->Ist_Status = Ready;

    /* '<S31>:19:3' Bus_ZM_Out.Pulsfreigabe = false; */
    rty_Bus_ZM_Out->Pulsfreigabe = false;

    /* '<S31>:19:4' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
    rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

    /* '<S31>:19:5' Bus_ZM_Out.En_Traj=false; */
    rty_Bus_ZM_Out->En_Traj = false;

    /* '<S31>:19:6' Bus_ZM_Out.Soll_Drehzahl = 0; */
    rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

    /* '<S31>:19:7' Bus_ZM_Out.Soll_id = 0; */
    rty_Bus_ZM_Out->Soll_id = 0.0F;

    /* '<S31>:19:8' Bus_ZM_Out.Soll_iq = 0; */
    rty_Bus_ZM_Out->Soll_iq = 0.0F;
  } else if (localDW->is_c3_uz_codegen0 == IN_Error) {
    /* During 'Error': '<S31>:10' */
    /* '<S31>:14:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == false && Bus_ZM_In.Soll_Status == Status_Ctrl.Ready); */
    if ((!rtu_Bus_ZM_In->Fehlermeldung) && (rtu_Bus_ZM_In->Soll_Status == Ready))
    {
      /* Transition: '<S31>:14' */
      localDW->is_c3_uz_codegen0 = IN_NoError;

      /* Entry Internal 'NoError': '<S31>:32' */
      /* Transition: '<S31>:45' */
      localDW->is_NoError = IN_Ready;

      /* Entry 'Ready': '<S31>:19' */
      /* '<S31>:19:2' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
      rty_Bus_ZM_Out->Ist_Status = Ready;

      /* '<S31>:19:3' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S31>:19:4' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

      /* '<S31>:19:5' Bus_ZM_Out.En_Traj=false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S31>:19:6' Bus_ZM_Out.Soll_Drehzahl = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

      /* '<S31>:19:7' Bus_ZM_Out.Soll_id = 0; */
      rty_Bus_ZM_Out->Soll_id = 0.0F;

      /* '<S31>:19:8' Bus_ZM_Out.Soll_iq = 0; */
      rty_Bus_ZM_Out->Soll_iq = 0.0F;
    } else {
      /* '<S31>:10:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Error_Status; */
      rty_Bus_ZM_Out->Ist_Status = Error_Status;

      /* '<S31>:10:4' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S31>:10:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Error; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Error;

      /* '<S31>:10:6' Bus_ZM_Out.En_Traj = false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S31>:10:7' Bus_ZM_Out.Soll_Drehzahl = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

      /* '<S31>:10:8' Bus_ZM_Out.Soll_id = 0; */
      rty_Bus_ZM_Out->Soll_id = 0.0F;

      /* '<S31>:10:9' Bus_ZM_Out.Soll_iq = 0; */
      rty_Bus_ZM_Out->Soll_iq = 0.0F;
    }

    /* During 'NoError': '<S31>:32' */
    /* '<S31>:15:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == true); */
  } else if (rtu_Bus_ZM_In->Fehlermeldung) {
    /* Transition: '<S31>:15' */
    /* Exit Internal 'NoError': '<S31>:32' */
    /* Exit Internal 'Run': '<S31>:20' */
    /* Exit Internal 'Trapez': '<S31>:54' */
    localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
    localDW->is_Run = IN_NO_ACTIVE_CHILD;
    localDW->is_NoError = IN_NO_ACTIVE_CHILD;
    localDW->is_c3_uz_codegen0 = IN_Error;
  } else if (localDW->is_NoError == IN_Ready) {
    /* During 'Ready': '<S31>:19' */
    /* '<S31>:25:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Status == Status_Ctrl.En); */
    if (rtu_Bus_ZM_In->Soll_Status == En) {
      /* Transition: '<S31>:25' */
      localDW->is_NoError = IN_Run;

      /* Entry Internal 'Run': '<S31>:20' */
      /* Transition: '<S31>:55' */
      localDW->is_Run = IN_nCtrl;
    } else {
      /* '<S31>:19:2' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
      rty_Bus_ZM_Out->Ist_Status = Ready;

      /* '<S31>:19:3' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S31>:19:4' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

      /* '<S31>:19:5' Bus_ZM_Out.En_Traj=false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S31>:19:6' Bus_ZM_Out.Soll_Drehzahl = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

      /* '<S31>:19:7' Bus_ZM_Out.Soll_id = 0; */
      rty_Bus_ZM_Out->Soll_id = 0.0F;

      /* '<S31>:19:8' Bus_ZM_Out.Soll_iq = 0; */
      rty_Bus_ZM_Out->Soll_iq = 0.0F;
    }

    /* During 'Run': '<S31>:20' */
    /* '<S31>:26:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Status == Status_Ctrl.Dis); */
  } else if (rtu_Bus_ZM_In->Soll_Status == Dis) {
    /* Transition: '<S31>:26' */
    /* Exit Internal 'Run': '<S31>:20' */
    /* Exit Internal 'Trapez': '<S31>:54' */
    localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
    localDW->is_Run = IN_NO_ACTIVE_CHILD;
    localDW->is_NoError = IN_Ready;

    /* Entry 'Ready': '<S31>:19' */
    /* '<S31>:19:2' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
    rty_Bus_ZM_Out->Ist_Status = Ready;

    /* '<S31>:19:3' Bus_ZM_Out.Pulsfreigabe = false; */
    rty_Bus_ZM_Out->Pulsfreigabe = false;

    /* '<S31>:19:4' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
    rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

    /* '<S31>:19:5' Bus_ZM_Out.En_Traj=false; */
    rty_Bus_ZM_Out->En_Traj = false;

    /* '<S31>:19:6' Bus_ZM_Out.Soll_Drehzahl = 0; */
    rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

    /* '<S31>:19:7' Bus_ZM_Out.Soll_id = 0; */
    rty_Bus_ZM_Out->Soll_id = 0.0F;

    /* '<S31>:19:8' Bus_ZM_Out.Soll_iq = 0; */
    rty_Bus_ZM_Out->Soll_iq = 0.0F;
  } else {
    /* '<S31>:20:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Run; */
    rty_Bus_ZM_Out->Ist_Status = Run;

    /* '<S31>:20:4' Bus_ZM_Out.Pulsfreigabe = true; */
    rty_Bus_ZM_Out->Pulsfreigabe = true;
    switch (localDW->is_Run) {
     case IN_Stromregelung:
      /* During 'Stromregelung': '<S31>:86' */
      /* '<S31>:92:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Strom); */
      if (rtu_Bus_ZM_In->Soll_Regelungsart != Strom) {
        /* Transition: '<S31>:92' */
        localDW->is_Run = IN_nCtrl;
      } else {
        /* '<S31>:86:3' Bus_ZM_Out.Soll_id = Bus_ZM_In.Soll_id; */
        rty_Bus_ZM_Out->Soll_id = rtu_Bus_ZM_In->Soll_id;

        /* '<S31>:86:4' Bus_ZM_Out.Soll_iq = Bus_ZM_In.Soll_iq; */
        rty_Bus_ZM_Out->Soll_iq = rtu_Bus_ZM_In->Soll_iq;

        /* '<S31>:86:5' Bus_ZM_Out.Soll_Drehzahl = 0; */
        rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

        /* '<S31>:86:6' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Strom; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Strom;
      }
      break;

     case IN_Trapez:
      /* During 'Trapez': '<S31>:54' */
      /* '<S31>:90:1' sf_internal_predicateOutput = 0 | (Dis == 1 || Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Trajektorie); */
      if (rtu_Dis || (rtu_Bus_ZM_In->Soll_Regelungsart != Trajektorie)) {
        /* Transition: '<S31>:90' */
        /* Exit Internal 'Trapez': '<S31>:54' */
        localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
        localDW->is_Run = IN_nCtrl;
      } else {
        /* '<S31>:54:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Trajektorie; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Trajektorie;

        /* '<S31>:54:4' Bus_ZM_Out.Soll_Drehzahl = Bus_ZM_In.Soll_Drehzahl; */
        rty_Bus_ZM_Out->Soll_Drehzahl = rtu_Bus_ZM_In->Soll_Drehzahl;

        /* '<S31>:54:5' Bus_ZM_Out.Soll_id = 0; */
        rty_Bus_ZM_Out->Soll_id = 0.0F;

        /* '<S31>:54:6' Bus_ZM_Out.Soll_iq = 0; */
        rty_Bus_ZM_Out->Soll_iq = 0.0F;
        if (localDW->is_Trapez == IN_Run_i) {
          /* During 'Run': '<S31>:68' */
          /* '<S31>:70:1' sf_internal_predicateOutput = 0 | (Dis == 1); */
          /* '<S31>:68:2' Bus_ZM_Out.En_Traj = true; */
          rty_Bus_ZM_Out->En_Traj = true;

          /* During 'Warten': '<S31>:66' */
          /* '<S31>:69:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Start_Traj == 1); */
        } else if (rtu_Bus_ZM_In->Start_Traj) {
          /* Transition: '<S31>:69' */
          localDW->is_Trapez = IN_Run_i;

          /* Entry 'Run': '<S31>:68' */
          /* '<S31>:68:2' Bus_ZM_Out.En_Traj = true; */
          rty_Bus_ZM_Out->En_Traj = true;
        } else {
          /* '<S31>:66:2' Bus_ZM_Out.En_Traj = false; */
          rty_Bus_ZM_Out->En_Traj = false;
        }
      }
      break;

     default:
      /* During 'nCtrl': '<S31>:56' */
      /* '<S31>:89:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Trajektorie); */
      switch (rtu_Bus_ZM_In->Soll_Regelungsart) {
       case Trajektorie:
        /* Transition: '<S31>:89' */
        localDW->is_Run = IN_Trapez;

        /* Entry Internal 'Trapez': '<S31>:54' */
        /* Transition: '<S31>:67' */
        localDW->is_Trapez = IN_Warten;

        /* Entry 'Warten': '<S31>:66' */
        /* '<S31>:66:2' Bus_ZM_Out.En_Traj = false; */
        rty_Bus_ZM_Out->En_Traj = false;
        break;

       case Strom:
        /* '<S31>:91:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Strom); */
        /* Transition: '<S31>:91' */
        localDW->is_Run = IN_Stromregelung;
        break;

       default:
        /* '<S31>:56:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

        /* '<S31>:56:4' Bus_ZM_Out.Soll_Drehzahl = Bus_ZM_In.Soll_Drehzahl; */
        rty_Bus_ZM_Out->Soll_Drehzahl = rtu_Bus_ZM_In->Soll_Drehzahl;

        /* '<S31>:56:5' Bus_ZM_Out.Soll_id = 0; */
        rty_Bus_ZM_Out->Soll_id = 0.0F;

        /* '<S31>:56:6' Bus_ZM_Out.Soll_iq = 0; */
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
  Zustandsmaschine(&rtU->Bus_ZM_In_f, rtDW->UnitDelay_DSTATE,
                   &rtDW->Bus_ZM_Out_c, &rtDW->Zustandsmaschine_p);

  /* End of Outputs for SubSystem: '<S1>/Zustandsmaschine' */

  /* Outputs for Enabled SubSystem: '<S1>/Regelung' */

  /* SignalConversion generated from: '<S3>/Enable' */
  Regelung(rtDW->Bus_ZM_Out_c.Pulsfreigabe, &rtU->Bus_PMSM_Out_e,
           &rtDW->Bus_ZM_Out_c, &rtDW->Switch, &rtDW->Switch1,
           &rtDW->OutportBufferForDis, &rtDW->Regelung_o);

  /* End of Outputs for SubSystem: '<S1>/Regelung' */

  /* Outputs for Atomic SubSystem: '<S1>/Raumzeigermodulation' */

  /* BusCreator generated from: '<S1>/Bus_Ctrl_Out_BusCreator' incorporates:
   *  Outport: '<Root>/Bus_Ctrl_Out'
   */
  Raumzeigermodulation(rtDW->Switch, rtDW->Switch1,
                       rtY->Bus_Ctrl_Out_k.Dutycycle);

  /* End of Outputs for SubSystem: '<S1>/Raumzeigermodulation' */
  rtY->Bus_Ctrl_Out_k.act_pwm = rtDW->Bus_ZM_Out_c.Pulsfreigabe;
  rtY->Bus_Ctrl_Out_k.ctrl_Ualpha = rtDW->Switch;
  rtY->Bus_Ctrl_Out_k.ctrl_Ubeta = rtDW->Switch1;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  rtDW->UnitDelay_DSTATE = rtDW->OutportBufferForDis;
}

/* Model initialize function */
void uz_codegen0_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;

  /* Registration code */

  /* states (dwork) */
  {
    rtDW->Bus_ZM_Out_c = uz_codegen0_rtZBus_ZM_Out;
  }

  /* external inputs */
  rtU->Bus_ZM_In_f = uz_codegen0_rtZBus_ZM_In;

  /* SystemInitialize for Atomic SubSystem: '<S1>/Zustandsmaschine' */
  Zustandsmaschine_Init(&rtDW->Bus_ZM_Out_c);

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
