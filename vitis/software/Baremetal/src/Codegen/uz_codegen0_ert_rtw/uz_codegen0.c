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
 * C/C++ source code generated on : Wed Aug 12 22:46:38 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "uz_codegen0.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

/* Named constants for Chart: '<S4>/state_chart' */
#define IN_Error                       ((uint8_t)1U)
#define IN_Idle                        ((uint8_t)1U)
#define IN_NO_ACTIVE_CHILD             ((uint8_t)0U)
#define IN_NoError                     ((uint8_t)2U)
#define IN_Ready                       ((uint8_t)2U)
#define IN_Run                         ((uint8_t)3U)
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
                                        *   '<S13>/Constant3'
                                        *   '<S25>/Constant'
                                        *   '<S25>/Constant3'
                                        *   '<S26>/Constant'
                                        *   '<S26>/Constant3'
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
                                        *   '<S19>/Constant'
                                        *   '<S21>/Gain'
                                        *   '<S23>/Constant'
                                        *   '<S24>/Constant'
                                        *   '<S24>/Constant1'
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
                                        *   '<S18>/Constant2'
                                        */

static void raumzeigermodulation(float rtu_Ualpha, float rtu_Ubeta, float
  rtu_Udc, float *rty_Dutycycle_A, float *rty_Dutycycle_B, float
  *rty_Dutycycle_C, float *rty_Sektor, float *rty_Quadrant);
static void Raumzeigermodulation(bool rtu_Enable, float rtu_Ualpha, float
  rtu_Ubeta, float rty_Dutycycle_A[3]);
static void Drehzahlregelung_Init(bool *rty_Dis);
static void Drehzahlregelung(bool rtu_Enable, float rtu_omega, const Bus_ZM_Out *
  rtu_Bus_ZM_Out_Inport_2, bool *rty_Dis, float *rty_Soll_Moment,
  DW_Drehzahlregelung *localDW);
static void Stromregelung(float rtu_Soll_Moment, const Bus_PMSM_Out
  *rtu_Bus_Live_Out_PMSM_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  float *rty_Ualpha, float *rty_Ubeta, DW_Stromregelung *localDW);
static void Regelung_Init(bool *rty_Dis);
static void Regelung(bool rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_2, float *rty_Ualpha, float
                     *rty_Ubeta, bool *rty_Dis, DW_Regelung *localDW);
static void state_chart_Init(Bus_ZM_Out *rty_Bus_ZM_Out, DW_state_chart *localDW);
static void state_chart(const Bus_ZM_In *rtu_Bus_ZM_In, bool rtu_Dis, Bus_ZM_Out
  *rty_Bus_ZM_Out, DW_state_chart *localDW);
static void Zustandsmaschine_Init(Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1,
  DW_Zustandsmaschine *localDW);
static void Zustandsmaschine(const Bus_ZM_In *rtu_Bus_ZM_In_Inport_1, bool
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
    Dutycycle_A = abs_Ualpha + 1.0F + c;

    /* '<S6>:1:59' Dutycycle_B = (single(1) - b + c); */
    abs_Ubeta = 1.0F - abs_Ualpha + c;

    /* '<S6>:1:60' Dutycycle_C = (single(1) - b - c); */
    a = 1.0F - abs_Ualpha - c;
    break;

   case 2:
    /* '<S6>:1:62' case 2 */
    /* '<S6>:1:63' if Quadrant == single(1) */
    if (Quadrant == 1) {
      /* '<S6>:1:64' Dutycycle_A = (single(1) + a + b); */
      Dutycycle_A = a + 1.0F + abs_Ualpha;

      /* '<S6>:1:65' Dutycycle_B = (single(1) + a - b); */
      abs_Ubeta = a + 1.0F - abs_Ualpha;

      /* '<S6>:1:66' Dutycycle_C = (single(1) - a + b); */
      a = 1.0F - a + abs_Ualpha;
    } else {
      /* '<S6>:1:67' else */
      /* '<S6>:1:68' Dutycycle_A = (single(1) - a - b); */
      Dutycycle_A = 1.0F - a - abs_Ualpha;

      /* '<S6>:1:69' Dutycycle_B = (single(1) + a - b); */
      abs_Ubeta = a + 1.0F - abs_Ualpha;

      /* '<S6>:1:70' Dutycycle_C = (single(1) - a + b); */
      a = 1.0F - a + abs_Ualpha;
    }
    break;

   case 3:
    /* '<S6>:1:73' case 3 */
    /* '<S6>:1:74' Dutycycle_A = (single(1) - b - c); */
    Dutycycle_A = 1.0F - abs_Ualpha - c;

    /* '<S6>:1:75' Dutycycle_B = (single(1) + b + c); */
    abs_Ubeta = abs_Ualpha + 1.0F + c;

    /* '<S6>:1:76' Dutycycle_C = (single(1) + b - c); */
    a = abs_Ualpha + 1.0F - c;
    break;

   case 4:
    /* '<S6>:1:78' case 4 */
    /* '<S6>:1:79' Dutycycle_A = (single(1) - b - c); */
    Dutycycle_A = 1.0F - abs_Ualpha - c;

    /* '<S6>:1:80' Dutycycle_B = (single(1) + b - c); */
    abs_Ubeta = abs_Ualpha + 1.0F - c;

    /* '<S6>:1:81' Dutycycle_C = (single(1) + b + c); */
    a = abs_Ualpha + 1.0F + c;
    break;

   case 5:
    /* '<S6>:1:83' case 5 */
    /* '<S6>:1:84' if Quadrant == 3 */
    if (Quadrant == 3) {
      /* '<S6>:1:85' Dutycycle_A = (single(1) - a - b); */
      Dutycycle_A = 1.0F - a - abs_Ualpha;

      /* '<S6>:1:86' Dutycycle_B = (single(1) - a + b); */
      abs_Ubeta = 1.0F - a + abs_Ualpha;

      /* '<S6>:1:87' Dutycycle_C = (single(1) + a - b); */
      a = a + 1.0F - abs_Ualpha;
    } else {
      /* '<S6>:1:88' else */
      /* '<S6>:1:89' Dutycycle_A = (single(1) + b + a); */
      Dutycycle_A = abs_Ualpha + 1.0F + a;

      /* '<S6>:1:90' Dutycycle_B = (single(1) + b - a); */
      abs_Ubeta = abs_Ualpha + 1.0F - a;

      /* '<S6>:1:91' Dutycycle_C = (single(1) - b + a); */
      a += 1.0F - abs_Ualpha;
    }
    break;

   default:
    /* '<S6>:1:94' case 6 */
    /* '<S6>:1:95' Dutycycle_A = (single(1) + b + c); */
    Dutycycle_A = abs_Ualpha + 1.0F + c;

    /* '<S6>:1:96' Dutycycle_B = (single(1) - b - c); */
    abs_Ubeta = 1.0F - abs_Ualpha - c;

    /* '<S6>:1:97' Dutycycle_C = (single(1) - b + c); */
    a = 1.0F - abs_Ualpha + c;
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

/* Output and update for enable system: '<S1>/Raumzeigermodulation' */
static void Raumzeigermodulation(bool rtu_Enable, float rtu_Ualpha, float
  rtu_Ubeta, float rty_Dutycycle_A[3])
{
  float rtb_Dutycycle_A;
  float rtb_Dutycycle_B;
  float rtb_Dutycycle_C;
  float rtb_Quadrant;
  float rtb_Sektor;

  /* Outputs for Enabled SubSystem: '<S1>/Raumzeigermodulation' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  if (rtu_Enable) {
    /* MATLAB Function: '<S2>/raumzeigermodulation' incorporates:
     *  Constant: '<S2>/Constant'
     */
    raumzeigermodulation(rtu_Ualpha, rtu_Ubeta, struct_Inv_Config.Udc,
                         &rtb_Dutycycle_A, &rtb_Dutycycle_B, &rtb_Dutycycle_C,
                         &rtb_Sektor, &rtb_Quadrant);

    /* Switch: '<S5>/Switch2' */
    rtb_Sektor = struct_Ctrl_Config.IGBT_dc_min / 2.0F;

    /* Switch: '<S5>/Switch1' incorporates:
     *  Constant: '<S5>/Constant1'
     *  Switch: '<S5>/Switch2'
     */
    if (rtb_Dutycycle_A >= struct_Ctrl_Config.IGBT_dc_min) {
      rty_Dutycycle_A[0] = rtb_Dutycycle_A;
    } else if (rtb_Dutycycle_A >= rtb_Sektor) {
      /* Switch: '<S5>/Switch2' incorporates:
       *  Constant: '<S5>/Constant'
       */
      rty_Dutycycle_A[0] = struct_Ctrl_Config.IGBT_dc_min;
    } else {
      rty_Dutycycle_A[0] = 0.0F;
    }

    if (rtb_Dutycycle_B >= struct_Ctrl_Config.IGBT_dc_min) {
      rty_Dutycycle_A[1] = rtb_Dutycycle_B;
    } else if (rtb_Dutycycle_B >= rtb_Sektor) {
      /* Switch: '<S5>/Switch2' incorporates:
       *  Constant: '<S5>/Constant'
       */
      rty_Dutycycle_A[1] = struct_Ctrl_Config.IGBT_dc_min;
    } else {
      rty_Dutycycle_A[1] = 0.0F;
    }

    if (rtb_Dutycycle_C >= struct_Ctrl_Config.IGBT_dc_min) {
      rty_Dutycycle_A[2] = rtb_Dutycycle_C;
    } else if (rtb_Dutycycle_C >= rtb_Sektor) {
      /* Switch: '<S5>/Switch2' incorporates:
       *  Constant: '<S5>/Constant'
       */
      rty_Dutycycle_A[2] = struct_Ctrl_Config.IGBT_dc_min;
    } else {
      rty_Dutycycle_A[2] = 0.0F;
    }

    /* End of Switch: '<S5>/Switch1' */

    /* Switch: '<S5>/Switch4' */
    rtb_Sektor = 1.0F - struct_Ctrl_Config.IGBT_dc_min / 2.0F;

    /* Switch: '<S5>/Switch3' */
    if (rty_Dutycycle_A[0] > 1.0F - struct_Ctrl_Config.IGBT_dc_min) {
      /* Switch: '<S5>/Switch4' incorporates:
       *  Constant: '<S5>/Constant2'
       *  Constant: '<S5>/Constant3'
       */
      if (rty_Dutycycle_A[0] >= rtb_Sektor) {
        rty_Dutycycle_A[0] = 1.0F;
      } else {
        rty_Dutycycle_A[0] = 1.0F - struct_Ctrl_Config.IGBT_dc_min;
      }
    }

    if (rty_Dutycycle_A[1] > 1.0F - struct_Ctrl_Config.IGBT_dc_min) {
      /* Switch: '<S5>/Switch4' incorporates:
       *  Constant: '<S5>/Constant2'
       *  Constant: '<S5>/Constant3'
       */
      if (rty_Dutycycle_A[1] >= rtb_Sektor) {
        rty_Dutycycle_A[1] = 1.0F;
      } else {
        rty_Dutycycle_A[1] = 1.0F - struct_Ctrl_Config.IGBT_dc_min;
      }
    }

    if (rty_Dutycycle_A[2] > 1.0F - struct_Ctrl_Config.IGBT_dc_min) {
      /* Switch: '<S5>/Switch4' incorporates:
       *  Constant: '<S5>/Constant2'
       *  Constant: '<S5>/Constant3'
       */
      if (rty_Dutycycle_A[2] >= rtb_Sektor) {
        rty_Dutycycle_A[2] = 1.0F;
      } else {
        rty_Dutycycle_A[2] = 1.0F - struct_Ctrl_Config.IGBT_dc_min;
      }
    }

    /* End of Switch: '<S5>/Switch3' */
  }

  /* End of Outputs for SubSystem: '<S1>/Raumzeigermodulation' */
}

/* System initialize for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_Init(bool *rty_Dis)
{
  /* SystemInitialize for SignalConversion generated from: '<S8>/Dis' */
  *rty_Dis = false;
}

/* Output and update for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung(bool rtu_Enable, float rtu_omega, const Bus_ZM_Out *
  rtu_Bus_ZM_Out_Inport_2, bool *rty_Dis, float *rty_Soll_Moment,
  DW_Drehzahlregelung *localDW)
{
  float UnitDelay_DSTATE_tmp;
  float rtb_Add1_a;
  float rtb_Product;
  float tmp;

  /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (rtu_Enable) {
    /* SignalConversion generated from: '<S8>/Dis' */
    *rty_Dis = false;

    /* Product: '<S12>/Product' incorporates:
     *  Constant: '<S12>/Constant'
     *  Gain: '<S11>/Gain'
     *  Sum: '<S12>/Subtract'
     *  UnitDelay: '<S13>/Unit Delay'
     */
    rtb_Product = (localDW->UnitDelay_DSTATE - GAIN_RADS_TO_HZ * rtu_omega) *
      struct_Ctrl_Config.KPn;

    /* Sum: '<S12>/Add1' incorporates:
     *  UnitDelay: '<S12>/Unit Delay'
     */
    rtb_Add1_a = rtb_Product + localDW->UnitDelay_DSTATE_c;

    /* Switch: '<S14>/Switch2' incorporates:
     *  Constant: '<S11>/Constant'
     *  Gain: '<S11>/Gain1'
     *  RelationalOperator: '<S14>/LowerRelop1'
     *  RelationalOperator: '<S14>/UpperRelop'
     *  Switch: '<S14>/Switch'
     */
    if (rtb_Add1_a > struct_PMSM_Config.mot_M_N) {
      *rty_Soll_Moment = struct_PMSM_Config.mot_M_N;
    } else if (rtb_Add1_a < -struct_PMSM_Config.mot_M_N) {
      /* Switch: '<S14>/Switch' incorporates:
       *  Gain: '<S11>/Gain1'
       */
      *rty_Soll_Moment = -struct_PMSM_Config.mot_M_N;
    } else {
      *rty_Soll_Moment = rtb_Add1_a;
    }

    /* End of Switch: '<S14>/Switch2' */

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

    /* Product: '<S13>/Product2' incorporates:
     *  Constant: '<S12>/Constant3'
     *  Constant: '<S13>/Constant3'
     *  Product: '<S12>/Product2'
     */
    UnitDelay_DSTATE_tmp = struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNn;

    /* Update for UnitDelay: '<S13>/Unit Delay' incorporates:
     *  Constant: '<S13>/Constant3'
     *  Product: '<S13>/Product2'
     *  Sum: '<S13>/Add'
     *  Sum: '<S13>/Add1'
     *  Switch: '<S8>/Switch'
     */
    localDW->UnitDelay_DSTATE += (tmp - localDW->UnitDelay_DSTATE) *
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
    localDW->UnitDelay_DSTATE_c += (rtb_Add1_a <= struct_PMSM_Config.mot_M_N &&
      rtb_Add1_a >= -struct_PMSM_Config.mot_M_N ? rtb_Product : 0.0F) *
      UnitDelay_DSTATE_tmp;
  }

  /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */
}

/* Output and update for atomic system: '<S3>/Stromregelung' */
static void Stromregelung(float rtu_Soll_Moment, const Bus_PMSM_Out
  *rtu_Bus_Live_Out_PMSM_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  float *rty_Ualpha, float *rty_Ubeta, DW_Stromregelung *localDW)
{
  float rtb_Abs2;
  float rtb_Add1_d;
  float rtb_Add1_f;
  float rtb_Gain1_p;
  float rtb_Gain2;
  float rtb_IDRef;
  float rtb_IQRef;
  float rtb_Product;
  float rtb_Product1_h;
  float rtb_Product_g;
  float rtb_Product_kr;
  float rtb_TrigonometricFunction1;
  float rtb_TrigonometricFunction_p;
  float rtb_UnitDelay_a;
  float tmp;

  /* Product: '<S9>/Product2' incorporates:
   *  Constant: '<S9>/Constant2'
   */
  rtb_Product = rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Omega_mech *
    struct_PMSM_Config.mot_p;

  /* Product: '<S9>/Product1' incorporates:
   *  Constant: '<S9>/Constant2'
   */
  rtb_TrigonometricFunction_p = struct_PMSM_Config.mot_p *
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_phi_mech;

  /* Gain: '<S22>/Gain1' incorporates:
   *  Constant: '<S9>/Constant3'
   *  Product: '<S9>/Product'
   *  Sum: '<S9>/Add'
   */
  rtb_Gain1_p = -(struct_Ctrl_Config.Tsample * rtb_Product +
                  rtb_TrigonometricFunction_p);

  /* Trigonometry: '<S22>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = cosf(rtb_Gain1_p);

  /* Switch: '<S9>/Switch3' incorporates:
   *  Constant: '<S17>/Constant'
   *  Constant: '<S9>/Constant'
   *  Gain: '<S21>/Gain'
   *  RelationalOperator: '<S17>/Compare'
   *  Switch: '<S9>/Switch2'
   */
  if (rtu_Bus_ZM_Out_Inport_3->Ist_Regelungsart == Strom) {
    rtb_IQRef = rtu_Bus_ZM_Out_Inport_3->Soll_iq;
    rtb_IDRef = rtu_Bus_ZM_Out_Inport_3->Soll_id;
  } else {
    /* Outputs for Atomic SubSystem: '<S9>/calcIq' */
    rtb_IQRef = 0.666666687F / struct_PMSM_Config.mot_psi_pm /
      struct_PMSM_Config.mot_p * rtu_Soll_Moment;

    /* End of Outputs for SubSystem: '<S9>/calcIq' */
    rtb_IDRef = 0.0F;
  }

  /* End of Switch: '<S9>/Switch3' */

  /* Gain: '<S18>/Gain2' incorporates:
   *  Constant: '<S18>/Constant2'
   */
  rtb_Gain2 = DIVIDE_TWO_BY_THREE * struct_Inv_Config.Udc;

  /* Trigonometry: '<S31>/Trigonometric Function1' */
  rtb_Abs2 = cosf(rtb_TrigonometricFunction_p);

  /* Gain: '<S30>/Gain' incorporates:
   *  Gain: '<S30>/Gain2'
   *  Gain: '<S30>/Gain7'
   *  Sum: '<S30>/Add'
   */
  rtb_UnitDelay_a = (-0.5F * rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[1] +
                     rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[0] + -0.5F *
                     rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2]) *
    DIVIDE_TWO_BY_THREE;

  /* Trigonometry: '<S31>/Trigonometric Function' */
  rtb_TrigonometricFunction_p = sinf(rtb_TrigonometricFunction_p);

  /* Gain: '<S30>/Gain1' incorporates:
   *  Gain: '<S30>/Gain5'
   *  Gain: '<S30>/sqrt(3)//2'
   *  Sum: '<S30>/Add1'
   */
  rtb_Product_g = (DIVIDE_SQRT_THREE_BY_TWO *
                   rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[1] +
                   -DIVIDE_SQRT_THREE_BY_TWO *
                   rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2]) *
    DIVIDE_TWO_BY_THREE;

  /* Product: '<S25>/Product' incorporates:
   *  Constant: '<S25>/Constant'
   *  Product: '<S31>/Product'
   *  Product: '<S31>/Product1'
   *  Sum: '<S25>/Subtract'
   *  Sum: '<S31>/Add'
   */
  rtb_Product_kr = (rtb_IDRef - (rtb_Abs2 * rtb_UnitDelay_a +
    rtb_TrigonometricFunction_p * rtb_Product_g)) * struct_Ctrl_Config.KPi;

  /* Sum: '<S25>/Add1' incorporates:
   *  UnitDelay: '<S25>/Unit Delay'
   */
  rtb_Add1_f = rtb_Product_kr + localDW->UnitDelay_DSTATE;

  /* Switch: '<S28>/Switch2' incorporates:
   *  Gain: '<S18>/Gain1'
   *  RelationalOperator: '<S28>/LowerRelop1'
   *  RelationalOperator: '<S28>/UpperRelop'
   *  Switch: '<S28>/Switch'
   */
  if (rtb_Add1_f > rtb_Gain2) {
    tmp = rtb_Gain2;
  } else if (rtb_Add1_f < -rtb_Gain2) {
    /* Switch: '<S28>/Switch' incorporates:
     *  Gain: '<S18>/Gain1'
     */
    tmp = -rtb_Gain2;
  } else {
    tmp = rtb_Add1_f;
  }

  /* Sum: '<S18>/Add1' incorporates:
   *  Constant: '<S23>/Constant'
   *  Product: '<S23>/Product'
   *  Product: '<S23>/Product1'
   *  Switch: '<S28>/Switch2'
   */
  rtb_Add1_d = tmp - rtb_Product * rtb_IQRef * struct_PMSM_Config.mot_Lq;

  /* Product: '<S24>/Product' incorporates:
   *  Constant: '<S24>/Constant'
   *  Constant: '<S24>/Constant1'
   *  Product: '<S24>/Product1'
   *  Sum: '<S24>/Add'
   */
  rtb_Product *= rtb_IDRef * struct_PMSM_Config.mot_Ld +
    struct_PMSM_Config.mot_psi_pm;

  /* Sum: '<S27>/Add3' incorporates:
   *  Product: '<S27>/Product'
   *  Product: '<S27>/Product1'
   *  Sqrt: '<S27>/Sqrt'
   *  Sum: '<S27>/Add2'
   */
  rtb_Product1_h = sqrtf(rtb_Gain2 * rtb_Gain2 - rtb_Add1_d * rtb_Add1_d) -
    rtb_Product;

  /* Product: '<S26>/Product' incorporates:
   *  Constant: '<S26>/Constant'
   *  Product: '<S31>/Product2'
   *  Product: '<S31>/Product3'
   *  Sum: '<S26>/Subtract'
   *  Sum: '<S31>/Add1'
   */
  rtb_Product_g = (rtb_IQRef - (rtb_Product_g * rtb_Abs2 - rtb_UnitDelay_a *
    rtb_TrigonometricFunction_p)) * struct_Ctrl_Config.KPi;

  /* Sum: '<S26>/Add1' incorporates:
   *  UnitDelay: '<S26>/Unit Delay'
   */
  rtb_TrigonometricFunction_p = rtb_Product_g + localDW->UnitDelay_DSTATE_h;

  /* Switch: '<S29>/Switch2' incorporates:
   *  Gain: '<S27>/Gain1'
   *  RelationalOperator: '<S29>/LowerRelop1'
   *  RelationalOperator: '<S29>/UpperRelop'
   *  Switch: '<S29>/Switch'
   */
  if (rtb_TrigonometricFunction_p > rtb_Product1_h) {
    tmp = rtb_Product1_h;
  } else if (rtb_TrigonometricFunction_p < -rtb_Product1_h) {
    /* Switch: '<S29>/Switch' incorporates:
     *  Gain: '<S27>/Gain1'
     */
    tmp = -rtb_Product1_h;
  } else {
    tmp = rtb_TrigonometricFunction_p;
  }

  /* Sum: '<S18>/Add' incorporates:
   *  Switch: '<S29>/Switch2'
   */
  rtb_Product += tmp;

  /* Trigonometry: '<S22>/Trigonometric Function' */
  rtb_Gain1_p = sinf(rtb_Gain1_p);

  /* Switch: '<S9>/Switch' incorporates:
   *  Abs: '<S19>/Abs'
   *  Abs: '<S19>/Abs1'
   *  Abs: '<S19>/Abs2'
   *  Constant: '<S15>/Constant'
   *  Constant: '<S16>/Constant'
   *  Constant: '<S19>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Logic: '<S19>/Logical Operator'
   *  Logic: '<S9>/Logical Operator'
   *  Logic: '<S9>/Logical Operator1'
   *  Product: '<S22>/Product'
   *  Product: '<S22>/Product1'
   *  Product: '<S22>/Product2'
   *  Product: '<S22>/Product3'
   *  RelationalOperator: '<S15>/Compare'
   *  RelationalOperator: '<S16>/Compare'
   *  RelationalOperator: '<S19>/Relational Operator'
   *  RelationalOperator: '<S19>/Relational Operator1'
   *  RelationalOperator: '<S19>/Relational Operator2'
   *  Sum: '<S22>/Add'
   *  Sum: '<S22>/Add1'
   *  Switch: '<S9>/Switch1'
   */
  if (rtb_IQRef == 0.0F && rtb_IDRef == 0.0F || (struct_PMSM_Config.mot_I_max <
       fabsf(rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[0]) ||
       struct_PMSM_Config.mot_I_max < fabsf
       (rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[1]) ||
       struct_PMSM_Config.mot_I_max < fabsf
       (rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw[2]))) {
    *rty_Ualpha = 0.0F;
    *rty_Ubeta = 0.0F;
  } else {
    *rty_Ualpha = rtb_Add1_d * rtb_TrigonometricFunction1 + rtb_Product *
      rtb_Gain1_p;
    *rty_Ubeta = rtb_Product * rtb_TrigonometricFunction1 - rtb_Add1_d *
      rtb_Gain1_p;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Product: '<S25>/Product2' incorporates:
   *  Constant: '<S25>/Constant3'
   *  Constant: '<S26>/Constant3'
   *  Product: '<S26>/Product2'
   */
  rtb_Product = struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNi;

  /* Update for UnitDelay: '<S25>/Unit Delay' incorporates:
   *  Constant: '<S25>/Constant3'
   *  Gain: '<S18>/Gain1'
   *  Logic: '<S25>/Logical Operator'
   *  Product: '<S25>/Product1'
   *  Product: '<S25>/Product2'
   *  RelationalOperator: '<S25>/Relational Operator'
   *  RelationalOperator: '<S25>/Relational Operator1'
   *  Sum: '<S25>/Add'
   */
  localDW->UnitDelay_DSTATE += (rtb_Add1_f <= rtb_Gain2 && rtb_Add1_f >=
    -rtb_Gain2 ? rtb_Product_kr : 0.0F) * rtb_Product;

  /* Update for UnitDelay: '<S26>/Unit Delay' incorporates:
   *  Gain: '<S27>/Gain1'
   *  Logic: '<S26>/Logical Operator'
   *  Product: '<S26>/Product1'
   *  Product: '<S26>/Product2'
   *  RelationalOperator: '<S26>/Relational Operator'
   *  RelationalOperator: '<S26>/Relational Operator1'
   *  Sum: '<S26>/Add'
   */
  localDW->UnitDelay_DSTATE_h += (rtb_TrigonometricFunction_p <= rtb_Product1_h &&
    rtb_TrigonometricFunction_p >= -rtb_Product1_h ? rtb_Product_g : 0.0F) *
    rtb_Product;
}

/* System initialize for enable system: '<S1>/Regelung' */
static void Regelung_Init(bool *rty_Dis)
{
  /* SystemInitialize for Enabled SubSystem: '<S3>/Drehzahlregelung' */
  Drehzahlregelung_Init(rty_Dis);

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
    Drehzahlregelung(rtu_Bus_ZM_Out_Inport_2->Ist_Regelungsart <= Drehzahl,
                     rtu_Bus_Live_Out_PMSM_Inport_1->pmsm_Omega_mech,
                     rtu_Bus_ZM_Out_Inport_2, rty_Dis, &localDW->Switch2,
                     &localDW->Drehzahlregelung_d);

    /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */

    /* Outputs for Atomic SubSystem: '<S3>/Stromregelung' */
    Stromregelung(localDW->Switch2, rtu_Bus_Live_Out_PMSM_Inport_1,
                  rtu_Bus_ZM_Out_Inport_2, rty_Ualpha, rty_Ubeta,
                  &localDW->Stromregelung_h);

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
    /* Transition: '<S32>:11' */
    localDW->is_c3_uz_codegen0 = IN_NoError;

    /* Entry Internal 'NoError': '<S32>:32' */
    /* Transition: '<S32>:45' */
    localDW->is_NoError = IN_Idle;
  } else if (localDW->is_c3_uz_codegen0 == IN_Error) {
    /* During 'Error': '<S32>:10' */
    /* '<S32>:14:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == false && Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state); */
    if (!rtu_Bus_ZM_In->Fehlermeldung && rtu_Bus_ZM_In->UZ_Platform_State ==
        idle_state) {
      /* Transition: '<S32>:14' */
      localDW->is_c3_uz_codegen0 = IN_NoError;

      /* Entry Internal 'NoError': '<S32>:32' */
      /* Transition: '<S32>:45' */
      localDW->is_NoError = IN_Idle;
    } else {
      /* '<S32>:10:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Error_Status; */
      rty_Bus_ZM_Out->Ist_Status = Error_Status;

      /* '<S32>:10:4' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S32>:10:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Error; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Error;

      /* '<S32>:10:6' Bus_ZM_Out.En_Traj = false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S32>:10:7' Bus_ZM_Out.Soll_Drehzahl = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

      /* '<S32>:10:8' Bus_ZM_Out.Soll_id = 0; */
      rty_Bus_ZM_Out->Soll_id = 0.0F;

      /* '<S32>:10:9' Bus_ZM_Out.Soll_iq = 0; */
      rty_Bus_ZM_Out->Soll_iq = 0.0F;

      /* '<S32>:10:10' Bus_ZM_Out.reset  = true; */
      rty_Bus_ZM_Out->reset = true;

      /* '<S32>:10:11' Bus_ZM_Out.pwr_en  = false; */
      rty_Bus_ZM_Out->pwr_en = false;

      /* '<S32>:10:12' Bus_ZM_Out.board_en  = false; */
      rty_Bus_ZM_Out->board_en = false;
    }

    /* During 'NoError': '<S32>:32' */
    /* '<S32>:15:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == true || Bus_ZM_In.UZ_Platform_State == platform_state_t.error_state || Bus_ZM_In.IGBT_desat == true); */
  } else if (rtu_Bus_ZM_In->Fehlermeldung || rtu_Bus_ZM_In->UZ_Platform_State ==
             error_state || rtu_Bus_ZM_In->IGBT_desat) {
    /* Transition: '<S32>:15' */
    /* Exit Internal 'NoError': '<S32>:32' */
    /* Exit Internal 'Run': '<S32>:20' */
    /* Exit Internal 'Trapez': '<S32>:54' */
    localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
    localDW->is_Run = IN_NO_ACTIVE_CHILD;
    localDW->is_NoError = IN_NO_ACTIVE_CHILD;
    localDW->is_c3_uz_codegen0 = IN_Error;
  } else {
    switch (localDW->is_NoError) {
     case IN_Idle:
      /* During 'Idle': '<S32>:103' */
      /* '<S32>:104:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.running_state); */
      if (rtu_Bus_ZM_In->UZ_Platform_State == running_state) {
        /* Transition: '<S32>:104' */
        localDW->is_NoError = IN_Ready;
      } else {
        /* '<S32>:103:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
        rty_Bus_ZM_Out->Ist_Status = Ready;

        /* '<S32>:103:4' Bus_ZM_Out.Pulsfreigabe = false; */
        rty_Bus_ZM_Out->Pulsfreigabe = false;

        /* '<S32>:103:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

        /* '<S32>:103:6' Bus_ZM_Out.En_Traj=false; */
        rty_Bus_ZM_Out->En_Traj = false;

        /* '<S32>:103:7' Bus_ZM_Out.Soll_Drehzahl = 0; */
        rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

        /* '<S32>:103:8' Bus_ZM_Out.Soll_id = 0; */
        rty_Bus_ZM_Out->Soll_id = 0.0F;

        /* '<S32>:103:9' Bus_ZM_Out.Soll_iq = 0; */
        rty_Bus_ZM_Out->Soll_iq = 0.0F;

        /* '<S32>:103:10' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S32>:103:11' Bus_ZM_Out.pwr_en  = false; */
        rty_Bus_ZM_Out->pwr_en = false;

        /* '<S32>:103:12' Bus_ZM_Out.board_en  = false; */
        rty_Bus_ZM_Out->board_en = false;
      }
      break;

     case IN_Ready:
      /* During 'Ready': '<S32>:19' */
      /* '<S32>:25:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.control_state && Bus_ZM_In.Inv_Ready == true); */
      if (rtu_Bus_ZM_In->UZ_Platform_State == control_state &&
          rtu_Bus_ZM_In->Inv_Ready) {
        /* Transition: '<S32>:25' */
        localDW->is_NoError = IN_Run;

        /* Entry Internal 'Run': '<S32>:20' */
        /* Transition: '<S32>:55' */
        localDW->is_Run = IN_nCtrl;

        /* '<S32>:105:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state); */
      } else if (rtu_Bus_ZM_In->UZ_Platform_State == idle_state) {
        /* Transition: '<S32>:105' */
        localDW->is_NoError = IN_Idle;
      } else {
        /* '<S32>:19:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
        rty_Bus_ZM_Out->Ist_Status = Ready;

        /* '<S32>:19:4' Bus_ZM_Out.Pulsfreigabe = false; */
        rty_Bus_ZM_Out->Pulsfreigabe = false;

        /* '<S32>:19:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

        /* '<S32>:19:6' Bus_ZM_Out.En_Traj=false; */
        rty_Bus_ZM_Out->En_Traj = false;

        /* '<S32>:19:7' Bus_ZM_Out.Soll_Drehzahl = 0; */
        rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

        /* '<S32>:19:8' Bus_ZM_Out.Soll_id = 0; */
        rty_Bus_ZM_Out->Soll_id = 0.0F;

        /* '<S32>:19:9' Bus_ZM_Out.Soll_iq = 0; */
        rty_Bus_ZM_Out->Soll_iq = 0.0F;

        /* '<S32>:19:10' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S32>:19:11' Bus_ZM_Out.pwr_en  = true; */
        rty_Bus_ZM_Out->pwr_en = true;

        /* '<S32>:19:12' Bus_ZM_Out.board_en  = true; */
        rty_Bus_ZM_Out->board_en = true;
      }
      break;

     default:
      /* During 'Run': '<S32>:20' */
      /* '<S32>:106:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state || Bus_ZM_In.Inv_Ready == false); */
      if (rtu_Bus_ZM_In->UZ_Platform_State == idle_state ||
          !rtu_Bus_ZM_In->Inv_Ready) {
        /* Transition: '<S32>:106' */
        /* Exit Internal 'Run': '<S32>:20' */
        /* Exit Internal 'Trapez': '<S32>:54' */
        localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
        localDW->is_Run = IN_NO_ACTIVE_CHILD;
        localDW->is_NoError = IN_Idle;
      } else {
        /* '<S32>:20:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Run; */
        rty_Bus_ZM_Out->Ist_Status = Run;

        /* '<S32>:20:4' Bus_ZM_Out.Pulsfreigabe = true; */
        rty_Bus_ZM_Out->Pulsfreigabe = true;

        /* '<S32>:20:5' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S32>:20:6' Bus_ZM_Out.pwr_en  = true; */
        rty_Bus_ZM_Out->pwr_en = true;

        /* '<S32>:20:7' Bus_ZM_Out.board_en  = true; */
        rty_Bus_ZM_Out->board_en = true;
        switch (localDW->is_Run) {
         case IN_Stromregelung:
          /* During 'Stromregelung': '<S32>:86' */
          /* '<S32>:92:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Strom); */
          if (rtu_Bus_ZM_In->Soll_Regelungsart != Strom) {
            /* Transition: '<S32>:92' */
            localDW->is_Run = IN_nCtrl;
          } else {
            /* '<S32>:86:3' Bus_ZM_Out.Soll_id = Bus_ZM_In.Soll_id; */
            rty_Bus_ZM_Out->Soll_id = rtu_Bus_ZM_In->Soll_id;

            /* '<S32>:86:4' Bus_ZM_Out.Soll_iq = Bus_ZM_In.Soll_iq; */
            rty_Bus_ZM_Out->Soll_iq = rtu_Bus_ZM_In->Soll_iq;

            /* '<S32>:86:5' Bus_ZM_Out.Soll_Drehzahl = 0; */
            rty_Bus_ZM_Out->Soll_Drehzahl = 0.0F;

            /* '<S32>:86:6' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Strom; */
            rty_Bus_ZM_Out->Ist_Regelungsart = Strom;
          }
          break;

         case IN_Trapez:
          /* During 'Trapez': '<S32>:54' */
          /* '<S32>:90:1' sf_internal_predicateOutput = 0 | (Dis == 1 || Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Trajektorie); */
          if (rtu_Dis || rtu_Bus_ZM_In->Soll_Regelungsart != Trajektorie) {
            /* Transition: '<S32>:90' */
            /* Exit Internal 'Trapez': '<S32>:54' */
            localDW->is_Trapez = IN_NO_ACTIVE_CHILD;
            localDW->is_Run = IN_nCtrl;
          } else {
            /* '<S32>:54:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Trajektorie; */
            rty_Bus_ZM_Out->Ist_Regelungsart = Trajektorie;

            /* '<S32>:54:4' Bus_ZM_Out.Soll_Drehzahl = Bus_ZM_In.Soll_Drehzahl; */
            rty_Bus_ZM_Out->Soll_Drehzahl = rtu_Bus_ZM_In->Soll_Drehzahl;

            /* '<S32>:54:5' Bus_ZM_Out.Soll_id = 0; */
            rty_Bus_ZM_Out->Soll_id = 0.0F;

            /* '<S32>:54:6' Bus_ZM_Out.Soll_iq = 0; */
            rty_Bus_ZM_Out->Soll_iq = 0.0F;
            if (localDW->is_Trapez == IN_Run_i) {
              /* During 'Run': '<S32>:68' */
              /* '<S32>:70:1' sf_internal_predicateOutput = 0 | (Dis == 1); */
              /* '<S32>:68:2' Bus_ZM_Out.En_Traj = true; */
              rty_Bus_ZM_Out->En_Traj = true;

              /* During 'Warten': '<S32>:66' */
              /* '<S32>:69:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Start_Traj == 1); */
            } else if (rtu_Bus_ZM_In->Start_Traj) {
              /* Transition: '<S32>:69' */
              localDW->is_Trapez = IN_Run_i;

              /* Entry 'Run': '<S32>:68' */
              /* '<S32>:68:2' Bus_ZM_Out.En_Traj = true; */
              rty_Bus_ZM_Out->En_Traj = true;
            } else {
              /* '<S32>:66:2' Bus_ZM_Out.En_Traj = false; */
              rty_Bus_ZM_Out->En_Traj = false;
            }
          }
          break;

         default:
          /* During 'nCtrl': '<S32>:56' */
          /* '<S32>:89:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Trajektorie); */
          switch (rtu_Bus_ZM_In->Soll_Regelungsart) {
           case Trajektorie:
            /* Transition: '<S32>:89' */
            localDW->is_Run = IN_Trapez;

            /* Entry Internal 'Trapez': '<S32>:54' */
            /* Transition: '<S32>:67' */
            localDW->is_Trapez = IN_Warten;

            /* Entry 'Warten': '<S32>:66' */
            /* '<S32>:66:2' Bus_ZM_Out.En_Traj = false; */
            rty_Bus_ZM_Out->En_Traj = false;
            break;

           case Strom:
            /* '<S32>:91:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Strom); */
            /* Transition: '<S32>:91' */
            localDW->is_Run = IN_Stromregelung;
            break;

           default:
            /* '<S32>:56:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
            rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

            /* '<S32>:56:4' Bus_ZM_Out.Soll_Drehzahl = Bus_ZM_In.Soll_Drehzahl; */
            rty_Bus_ZM_Out->Soll_Drehzahl = rtu_Bus_ZM_In->Soll_Drehzahl;

            /* '<S32>:56:5' Bus_ZM_Out.Soll_id = 0; */
            rty_Bus_ZM_Out->Soll_id = 0.0F;

            /* '<S32>:56:6' Bus_ZM_Out.Soll_iq = 0; */
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
  Zustandsmaschine(&rtU->Bus_ZM_In_a, rtDW->UnitDelay_DSTATE,
                   &rtDW->Bus_ZM_Out_d, &rtDW->Zustandsmaschine_d);

  /* End of Outputs for SubSystem: '<S1>/Zustandsmaschine' */

  /* Outputs for Enabled SubSystem: '<S1>/Regelung' */

  /* SignalConversion generated from: '<S3>/Enable' */
  Regelung(rtDW->Bus_ZM_Out_d.Pulsfreigabe, &rtU->Bus_PMSM_Out_j,
           &rtDW->Bus_ZM_Out_d, &rtDW->Switch, &rtDW->Switch1,
           &rtDW->OutportBufferForDis, &rtDW->Regelung_m);

  /* End of Outputs for SubSystem: '<S1>/Regelung' */

  /* Outputs for Enabled SubSystem: '<S1>/Raumzeigermodulation' */

  /* SignalConversion generated from: '<S2>/Enable' */
  Raumzeigermodulation(rtDW->Bus_ZM_Out_d.Pulsfreigabe, rtDW->Switch,
                       rtDW->Switch1, rtY->Bus_Ctrl_Out_i.Dutycycle);

  /* End of Outputs for SubSystem: '<S1>/Raumzeigermodulation' */

  /* BusCreator generated from: '<S1>/Bus_Ctrl_Out_BusCreator' incorporates:
   *  Outport: '<Root>/Bus_Ctrl_Out'
   */
  rtY->Bus_Ctrl_Out_i.act_pwm = rtDW->Bus_ZM_Out_d.Pulsfreigabe;
  rtY->Bus_Ctrl_Out_i.ctrl_Ualpha = rtDW->Switch;
  rtY->Bus_Ctrl_Out_i.ctrl_Ubeta = rtDW->Switch1;
  rtY->Bus_Ctrl_Out_i.pwr_en = rtDW->Bus_ZM_Out_d.pwr_en;
  rtY->Bus_Ctrl_Out_i.board_en = rtDW->Bus_ZM_Out_d.board_en;
  rtY->Bus_Ctrl_Out_i.reset = rtDW->Bus_ZM_Out_d.reset;

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
    rtDW->Bus_ZM_Out_d = uz_codegen0_rtZBus_ZM_Out;
  }

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));
  rtU->Bus_ZM_In_a = uz_codegen0_rtZBus_ZM_In;

  /* external outputs */
  rtY->Bus_Ctrl_Out_i = uz_codegen0_rtZBus_Ctrl_Out;

  /* SystemInitialize for Atomic SubSystem: '<S1>/Zustandsmaschine' */
  Zustandsmaschine_Init(&rtDW->Bus_ZM_Out_d, &rtDW->Zustandsmaschine_d);

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
