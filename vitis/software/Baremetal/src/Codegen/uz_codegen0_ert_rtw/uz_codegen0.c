/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: uz_codegen0.c
 *
 * Code generated for Simulink model 'uz_codegen0'.
 *
 * Model version                  : 10.18
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Tue Aug 25 22:54:58 2026
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
#define IN_Stromregelung               ((uint8_t)1U)
#define IN_nCtrl                       ((uint8_t)2U)

const Bus_ZM_Out uz_codegen0_rtZBus_ZM_Out = {
  false,                               /* En_Traj */
  false,                               /* Pulsfreigabe */
  Error_Status,                        /* Ist_Status */
  Error,                               /* Ist_Regelungsart */
  0.0F,                                /* Soll_Drehzahl_Umin */
  0.0F,                                /* Soll_id_A */
  0.0F,                                /* Soll_iq_A */
  false,                               /* pwr_en */
  false,                               /* board_en */
  false                                /* reset */
};                                     /* Bus_ZM_Out ground */

/* Exported block parameters */
Bus_Ctrl_Config struct_Ctrl_Config = {
  0.0001F,
  0.0001F,
  0.004F,
  36.0F,
  0.0002F,
  9000.0F,
  0.0016F,
  0.5F,
  2.0F,
  0.15121232F,
  -0.15121232F,
  0.2F,
  0.0F,
  0.0F,
  false
} ;                                    /* Variable: struct_Ctrl_Config
                                        * Referenced by:
                                        *   '<S5>/Constant'
                                        *   '<S5>/Constant2'
                                        *   '<S5>/Switch1'
                                        *   '<S5>/Switch2'
                                        *   '<S5>/Switch3'
                                        *   '<S5>/Switch4'
                                        *   '<S9>/Constant2'
                                        *   '<S9>/Constant3'
                                        *   '<S12>/Constant'
                                        *   '<S12>/Constant1'
                                        *   '<S12>/Constant3'
                                        *   '<S13>/Constant3'
                                        *   '<S25>/Constant'
                                        *   '<S25>/Constant1'
                                        *   '<S25>/Constant3'
                                        *   '<S26>/Constant'
                                        *   '<S26>/Constant1'
                                        *   '<S26>/Constant3'
                                        */

Bus_PMSM_Config struct_PMSM_Config = {
  1.8F,
  0.13F,
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
                                        *   '<S11>/Constant'
                                        *   '<S19>/Constant'
                                        *   '<S23>/Constant'
                                        *   '<S24>/Constant'
                                        *   '<S24>/Constant1'
                                        *   '<S31>/Gain'
                                        */

Bus_Inv_Config struct_Inv_Config = {
  PT1,
  48.0F,
  1.0F,
  20000.0F,
  false
} ;                                    /* Variable: struct_Inv_Config
                                        * Referenced by:
                                        *   '<S2>/Constant'
                                        *   '<S17>/Constant2'
                                        */

static void raumzeigermodulation(float rtu_Ualpha, float rtu_Ubeta, float
  rtu_Udc, float *rty_Dutycycle_A, float *rty_Dutycycle_B, float
  *rty_Dutycycle_C, float *rty_Sektor, float *rty_Quadrant);
static void Raumzeigermodulation(bool rtu_Enable, float rtu_Ualpha, float
  rtu_Ubeta, float rty_Dutycycle_A[3]);
static void Drehzahlregelung_Init(bool *rty_Dis, DW_Drehzahlregelung *localDW);
static void Drehzahlregelung_Reset(DW_Drehzahlregelung *localDW);
static void Drehzahlregelung_Disable(DW_Drehzahlregelung *localDW);
static void Drehzahlregelung(bool rtu_Enable, float rtu_omega_mech_rad_s, const
  Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_2, bool *rty_Dis, float *rty_Soll_Moment,
  float *rty_ctrl_omega, float *rty_soll_omega, DW_Drehzahlregelung *localDW);
static void abc_zu_dq1(bool rtu_Enable, float rtu_theta_el, float rtu_pmsm_Iu,
  float rtu_pmsm_Iv, float rtu_pmsm_Iw, float *rty_ctrl_Id, float *rty_ctrl_Iq);
static void Stromregelung_Init(DW_Stromregelung *localDW);
static void Stromregelung_Reset(DW_Stromregelung *localDW);
static void Stromregelung(float rtu_Soll_Moment, const Bus_PMSM_Out
  *rtu_Bus_Live_Out_PMSM_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  bool rtu_trigger_actI_I_calc, float *rty_Ualpha, float *rty_Ubeta, float
  *rty_ref_Iq, float *rty_act_iq_P, float *rty_act_id_I, float *rty_act_iq_I,
  float *rty_act_id_P, float *rty_ref_Id, DW_Stromregelung *localDW);
static void Regelung_Init(bool *rty_Dis, DW_Regelung *localDW);
static void Regelung_Reset(DW_Regelung *localDW);
static void Regelung_Disable(DW_Regelung *localDW);
static void Regelung(bool rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_2, bool rtu_trigger_actI_I_calc,
                     float *rty_Ualpha, float *rty_Ubeta, bool *rty_Dis, float
                     *rty_Soll_Moment, float *rty_IQRef, float *rty_ctrl_omega,
                     float *rty_soll_omega, float *rty_ctrl_Iq, float
                     *rty_act_id_I, float *rty_act_iq_I, float *rty_act_id_P,
                     float *rty_ref_Id, DW_Regelung *localDW);
static void state_chart_Init(Bus_ZM_Out *rty_Bus_ZM_Out, DW_state_chart *localDW);
static void state_chart(const Bus_ZM_In *rtu_Bus_ZM_In, Bus_ZM_Out
  *rty_Bus_ZM_Out, DW_state_chart *localDW);
static void Zustandsmaschine_Init(Bus_ZM_Out *rty_Bus_ZM_Out_Outport_1,
  DW_Zustandsmaschine *localDW);
static void Zustandsmaschine(const Bus_ZM_In *rtu_Bus_ZM_In_Inport_1, Bus_ZM_Out
  *rty_Bus_ZM_Out_Outport_1, DW_Zustandsmaschine *localDW);
const Bus_Ctrl_Out uz_codegen0_rtZBus_Ctrl_Out = { { 0.0F, 0.0F, 0.0F },/* Dutycycle */
  false,                               /* act_pwm */
  0.0F,                                /* ctrl_Ualpha_V */
  0.0F,                                /* ctrl_Ubeta_V */
  false,                               /* pwr_en */
  false,                               /* board_en */
  false,                               /* reset */
  Error_Status                         /* ZM_Ist_Status */
};

const Bus_ZM_In uz_codegen0_rtZBus_ZM_In = { 0.0F,/* Soll_Drehzahl_Umin */
  0.0F,                                /* Soll_id_A */
  0.0F,                                /* Soll_iq_A */
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
static void Drehzahlregelung_Init(bool *rty_Dis, DW_Drehzahlregelung *localDW)
{
  /* InitializeConditions for UnitDelay: '<S13>/Unit Delay' */
  localDW->UnitDelay_DSTATE = 0.0F;

  /* InitializeConditions for UnitDelay: '<S12>/Unit Delay' */
  localDW->UnitDelay_DSTATE_i = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S8>/Dis' */
  *rty_Dis = false;
}

/* System reset for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_Reset(DW_Drehzahlregelung *localDW)
{
  /* InitializeConditions for UnitDelay: '<S13>/Unit Delay' */
  localDW->UnitDelay_DSTATE = 0.0F;

  /* InitializeConditions for UnitDelay: '<S12>/Unit Delay' */
  localDW->UnitDelay_DSTATE_i = 0.0F;
}

/* Disable for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung_Disable(DW_Drehzahlregelung *localDW)
{
  localDW->Drehzahlregelung_MODE = false;
}

/* Output and update for enable system: '<S3>/Drehzahlregelung' */
static void Drehzahlregelung(bool rtu_Enable, float rtu_omega_mech_rad_s, const
  Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_2, bool *rty_Dis, float *rty_Soll_Moment,
  float *rty_ctrl_omega, float *rty_soll_omega, DW_Drehzahlregelung *localDW)
{
  float rtb_Add1;
  float rtb_Add1_tmp;

  /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (rtu_Enable) {
    if (!localDW->Drehzahlregelung_MODE) {
      Drehzahlregelung_Reset(localDW);
      localDW->Drehzahlregelung_MODE = true;
    }

    /* SignalConversion generated from: '<S8>/Dis' */
    *rty_Dis = false;

    /* Gain: '<S11>/Gain' */
    *rty_ctrl_omega = GAIN_RADS_TO_HZ * rtu_omega_mech_rad_s;

    /* UnitDelay: '<S13>/Unit Delay' */
    *rty_soll_omega = localDW->UnitDelay_DSTATE;

    /* Sum: '<S12>/Subtract' incorporates:
     *  Sum: '<S12>/Subtract1'
     */
    rtb_Add1_tmp = *rty_soll_omega - *rty_ctrl_omega;

    /* Sum: '<S12>/Add1' incorporates:
     *  Constant: '<S12>/Constant'
     *  Product: '<S12>/Product'
     *  Sum: '<S12>/Subtract'
     *  UnitDelay: '<S12>/Unit Delay'
     */
    rtb_Add1 = rtb_Add1_tmp * struct_Ctrl_Config.KPn +
      localDW->UnitDelay_DSTATE_i;

    /* Switch: '<S14>/Switch2' incorporates:
     *  Constant: '<S11>/Constant'
     *  Gain: '<S11>/Gain1'
     *  RelationalOperator: '<S14>/LowerRelop1'
     *  RelationalOperator: '<S14>/UpperRelop'
     *  Switch: '<S14>/Switch'
     */
    if (rtb_Add1 > struct_PMSM_Config.mot_M_N_Nm) {
      *rty_Soll_Moment = struct_PMSM_Config.mot_M_N_Nm;
    } else if (rtb_Add1 < -struct_PMSM_Config.mot_M_N_Nm) {
      /* Switch: '<S14>/Switch' incorporates:
       *  Gain: '<S11>/Gain1'
       */
      *rty_Soll_Moment = -struct_PMSM_Config.mot_M_N_Nm;
    } else {
      *rty_Soll_Moment = rtb_Add1;
    }

    /* End of Switch: '<S14>/Switch2' */

    /* Update for UnitDelay: '<S13>/Unit Delay' incorporates:
     *  Constant: '<S13>/Constant3'
     *  Gain: '<S8>/Gain'
     *  Product: '<S13>/Product2'
     *  Sum: '<S13>/Add'
     *  Sum: '<S13>/Add1'
     */
    localDW->UnitDelay_DSTATE = (GAIN_UMIN_TO_HZ *
      rtu_Bus_ZM_Out_Inport_2->Soll_Drehzahl_Umin - *rty_soll_omega) *
      (struct_Ctrl_Config.Tsample / struct_Ctrl_Config.TNn) + *rty_soll_omega;

    /* Update for UnitDelay: '<S12>/Unit Delay' incorporates:
     *  Constant: '<S11>/Constant'
     *  Constant: '<S12>/Constant1'
     *  Constant: '<S12>/Constant3'
     *  Gain: '<S11>/Gain1'
     *  Logic: '<S12>/Logical Operator'
     *  Product: '<S12>/Product1'
     *  Product: '<S12>/Product2'
     *  Product: '<S12>/Product3'
     *  RelationalOperator: '<S12>/Relational Operator'
     *  RelationalOperator: '<S12>/Relational Operator1'
     *  Sum: '<S12>/Add'
     */
    localDW->UnitDelay_DSTATE_i += (rtb_Add1 <= struct_PMSM_Config.mot_M_N_Nm &&
      rtb_Add1 >= -struct_PMSM_Config.mot_M_N_Nm ? rtb_Add1_tmp : 0.0F) *
      struct_Ctrl_Config.KIn * struct_Ctrl_Config.Tsample;
  } else if (localDW->Drehzahlregelung_MODE) {
    Drehzahlregelung_Disable(localDW);
  }

  /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */
}

/* Output and update for enable system: '<S9>/abc_zu_dq1' */
static void abc_zu_dq1(bool rtu_Enable, float rtu_theta_el, float rtu_pmsm_Iu,
  float rtu_pmsm_Iv, float rtu_pmsm_Iw, float *rty_ctrl_Id, float *rty_ctrl_Iq)
{
  float rtb_Gain1_n;
  float rtb_Gain_a;
  float rtb_TrigonometricFunction1_b;
  float rtb_TrigonometricFunction_a;

  /* Outputs for Enabled SubSystem: '<S9>/abc_zu_dq1' incorporates:
   *  EnablePort: '<S21>/Enable'
   */
  if (rtu_Enable) {
    /* Gain: '<S34>/Gain' incorporates:
     *  Gain: '<S34>/Gain2'
     *  Gain: '<S34>/Gain7'
     *  Sum: '<S34>/Add'
     */
    rtb_Gain_a = (-0.5F * rtu_pmsm_Iv + rtu_pmsm_Iu + -0.5F * rtu_pmsm_Iw) *
      DIVIDE_TWO_BY_THREE;

    /* Trigonometry: '<S35>/Trigonometric Function1' */
    rtb_TrigonometricFunction1_b = cosf(rtu_theta_el);

    /* Gain: '<S34>/Gain1' incorporates:
     *  Gain: '<S34>/Gain5'
     *  Gain: '<S34>/sqrt(3)//2'
     *  Sum: '<S34>/Add1'
     */
    rtb_Gain1_n = (DIVIDE_SQRT_THREE_BY_TWO * rtu_pmsm_Iv +
                   -DIVIDE_SQRT_THREE_BY_TWO * rtu_pmsm_Iw) *
      DIVIDE_TWO_BY_THREE;

    /* Trigonometry: '<S35>/Trigonometric Function' */
    rtb_TrigonometricFunction_a = sinf(rtu_theta_el);

    /* Sum: '<S35>/Add' incorporates:
     *  Product: '<S35>/Product'
     *  Product: '<S35>/Product1'
     */
    *rty_ctrl_Id = rtb_TrigonometricFunction1_b * rtb_Gain_a +
      rtb_TrigonometricFunction_a * rtb_Gain1_n;

    /* Sum: '<S35>/Add1' incorporates:
     *  Product: '<S35>/Product2'
     *  Product: '<S35>/Product3'
     */
    *rty_ctrl_Iq = rtb_Gain1_n * rtb_TrigonometricFunction1_b - rtb_Gain_a *
      rtb_TrigonometricFunction_a;
  }

  /* End of Outputs for SubSystem: '<S9>/abc_zu_dq1' */
}

/* System initialize for atomic system: '<S3>/Stromregelung' */
static void Stromregelung_Init(DW_Stromregelung *localDW)
{
  /* InitializeConditions for UnitDelay: '<S25>/Unit Delay' */
  localDW->UnitDelay_DSTATE = 0.0F;

  /* InitializeConditions for UnitDelay: '<S26>/Unit Delay' */
  localDW->UnitDelay_DSTATE_i = 0.0F;
}

/* System reset for atomic system: '<S3>/Stromregelung' */
static void Stromregelung_Reset(DW_Stromregelung *localDW)
{
  /* InitializeConditions for UnitDelay: '<S25>/Unit Delay' */
  localDW->UnitDelay_DSTATE = 0.0F;

  /* InitializeConditions for UnitDelay: '<S26>/Unit Delay' */
  localDW->UnitDelay_DSTATE_i = 0.0F;
}

/* Output and update for atomic system: '<S3>/Stromregelung' */
static void Stromregelung(float rtu_Soll_Moment, const Bus_PMSM_Out
  *rtu_Bus_Live_Out_PMSM_Inport_2, const Bus_ZM_Out *rtu_Bus_ZM_Out_Inport_3,
  bool rtu_trigger_actI_I_calc, float *rty_Ualpha, float *rty_Ubeta, float
  *rty_ref_Iq, float *rty_act_iq_P, float *rty_act_id_I, float *rty_act_iq_I,
  float *rty_act_id_P, float *rty_ref_Id, DW_Stromregelung *localDW)
{
  float rtb_Add1;
  float rtb_Add1_a;
  float rtb_Add3;
  float rtb_Gain1_h;
  float rtb_Product1_b;
  float rtb_Product1_ki;
  float rtb_TrigonometricFunction1;
  float rtb_UnitDelay_a;
  float rtb_UnitDelay_g;
  bool rtb_intOnOff_b;

  /* Gain: '<S22>/Gain1' incorporates:
   *  Constant: '<S9>/Constant3'
   *  Product: '<S9>/Product'
   *  Sum: '<S9>/Add'
   */
  rtb_Gain1_h = -(struct_Ctrl_Config.Tsample * 1.5F *
                  rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Omega_el_rad_s +
                  rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_theta_el_rad);

  /* Trigonometry: '<S22>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = cosf(rtb_Gain1_h);

  /* Gain: '<S32>/Gain' incorporates:
   *  Gain: '<S32>/Gain2'
   *  Gain: '<S32>/Gain7'
   *  Sum: '<S32>/Add'
   */
  rtb_UnitDelay_g = (-0.5F * rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_P_A[1] +
                     rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_P_A[0] + -0.5F *
                     rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_P_A[2]) *
    DIVIDE_TWO_BY_THREE;

  /* Trigonometry: '<S33>/Trigonometric Function' */
  rtb_Add3 = sinf(rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_theta_el_rad);

  /* Trigonometry: '<S33>/Trigonometric Function1' */
  rtb_Product1_b = cosf(rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_theta_el_rad);

  /* Gain: '<S32>/Gain1' incorporates:
   *  Gain: '<S32>/Gain5'
   *  Gain: '<S32>/sqrt(3)//2'
   *  Sum: '<S32>/Add1'
   */
  rtb_UnitDelay_a = (DIVIDE_SQRT_THREE_BY_TWO *
                     rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_P_A[1] +
                     -DIVIDE_SQRT_THREE_BY_TWO *
                     rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_P_A[2]) *
    DIVIDE_TWO_BY_THREE;

  /* Sum: '<S33>/Add1' incorporates:
   *  Product: '<S33>/Product2'
   *  Product: '<S33>/Product3'
   */
  *rty_act_iq_P = rtb_UnitDelay_a * rtb_Product1_b - rtb_UnitDelay_g * rtb_Add3;

  /* Gain: '<S17>/Gain2' incorporates:
   *  Constant: '<S17>/Constant2'
   */
  rtb_Product1_ki = DIVIDE_ONE_BY_SQRT_THREE * struct_Inv_Config.Udc;

  /* RelationalOperator: '<S30>/Compare' incorporates:
   *  Constant: '<S30>/Constant'
   */
  rtb_intOnOff_b = rtu_Bus_ZM_Out_Inport_3->Ist_Regelungsart == Strom;

  /* Switch: '<S18>/Switch2' incorporates:
   *  Constant: '<S18>/Constant'
   */
  if (rtb_intOnOff_b) {
    *rty_ref_Id = rtu_Bus_ZM_Out_Inport_3->Soll_id_A;
  } else {
    *rty_ref_Id = 0.0F;
  }

  /* End of Switch: '<S18>/Switch2' */

  /* Sum: '<S33>/Add' incorporates:
   *  Product: '<S33>/Product'
   *  Product: '<S33>/Product1'
   */
  *rty_act_id_P = rtb_Product1_b * rtb_UnitDelay_g + rtb_Add3 * rtb_UnitDelay_a;

  /* Sum: '<S25>/Add1' incorporates:
   *  Constant: '<S25>/Constant'
   *  Product: '<S25>/Product'
   *  Sum: '<S25>/Subtract'
   *  UnitDelay: '<S25>/Unit Delay'
   */
  rtb_UnitDelay_g = (*rty_ref_Id - *rty_act_id_P) * struct_Ctrl_Config.KPi +
    localDW->UnitDelay_DSTATE;

  /* Switch: '<S28>/Switch2' incorporates:
   *  Gain: '<S17>/Gain1'
   *  RelationalOperator: '<S28>/LowerRelop1'
   *  RelationalOperator: '<S28>/UpperRelop'
   *  Switch: '<S28>/Switch'
   */
  if (rtb_UnitDelay_g > rtb_Product1_ki) {
    rtb_UnitDelay_a = rtb_Product1_ki;
  } else if (rtb_UnitDelay_g < -rtb_Product1_ki) {
    /* Switch: '<S28>/Switch' incorporates:
     *  Gain: '<S17>/Gain1'
     */
    rtb_UnitDelay_a = -rtb_Product1_ki;
  } else {
    rtb_UnitDelay_a = rtb_UnitDelay_g;
  }

  /* Sum: '<S17>/Add1' incorporates:
   *  Constant: '<S23>/Constant'
   *  Product: '<S23>/Product'
   *  Product: '<S23>/Product1'
   *  Switch: '<S28>/Switch2'
   */
  rtb_Add1 = rtb_UnitDelay_a -
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Omega_el_rad_s * *rty_act_iq_P *
    struct_PMSM_Config.mot_Lq_H;

  /* Product: '<S24>/Product' incorporates:
   *  Constant: '<S24>/Constant'
   *  Constant: '<S24>/Constant1'
   *  Product: '<S24>/Product1'
   *  Sum: '<S24>/Add'
   */
  rtb_Product1_b = (*rty_act_id_P * struct_PMSM_Config.mot_Ld_H +
                    struct_PMSM_Config.mot_psi_pm_Vs) *
    rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Omega_el_rad_s;

  /* Sum: '<S27>/Add3' incorporates:
   *  Product: '<S27>/Product'
   *  Product: '<S27>/Product1'
   *  Sqrt: '<S27>/Sqrt'
   *  Sum: '<S27>/Add2'
   */
  rtb_Add3 = sqrtf(rtb_Product1_ki * rtb_Product1_ki - rtb_Add1 * rtb_Add1) -
    rtb_Product1_b;

  /* Switch: '<S18>/Switch3' incorporates:
   *  Gain: '<S31>/Gain'
   */
  if (rtb_intOnOff_b) {
    *rty_ref_Iq = rtu_Bus_ZM_Out_Inport_3->Soll_iq_A;
  } else {
    /* Outputs for Atomic SubSystem: '<S18>/calcIq' */
    *rty_ref_Iq = 0.666666687F / struct_PMSM_Config.mot_psi_pm_Vs /
      struct_PMSM_Config.mot_p * rtu_Soll_Moment;

    /* End of Outputs for SubSystem: '<S18>/calcIq' */
  }

  /* End of Switch: '<S18>/Switch3' */

  /* Sum: '<S26>/Add1' incorporates:
   *  Constant: '<S26>/Constant'
   *  Product: '<S26>/Product'
   *  Sum: '<S26>/Subtract'
   *  UnitDelay: '<S26>/Unit Delay'
   */
  rtb_Add1_a = (*rty_ref_Iq - *rty_act_iq_P) * struct_Ctrl_Config.KPi +
    localDW->UnitDelay_DSTATE_i;

  /* Switch: '<S29>/Switch2' incorporates:
   *  Gain: '<S27>/Gain1'
   *  RelationalOperator: '<S29>/LowerRelop1'
   *  RelationalOperator: '<S29>/UpperRelop'
   *  Switch: '<S29>/Switch'
   */
  if (rtb_Add1_a > rtb_Add3) {
    rtb_UnitDelay_a = rtb_Add3;
  } else if (rtb_Add1_a < -rtb_Add3) {
    /* Switch: '<S29>/Switch' incorporates:
     *  Gain: '<S27>/Gain1'
     */
    rtb_UnitDelay_a = -rtb_Add3;
  } else {
    rtb_UnitDelay_a = rtb_Add1_a;
  }

  /* Sum: '<S17>/Add' incorporates:
   *  Switch: '<S29>/Switch2'
   */
  rtb_Product1_b += rtb_UnitDelay_a;

  /* Trigonometry: '<S22>/Trigonometric Function' */
  rtb_Gain1_h = sinf(rtb_Gain1_h);

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
  if (*rty_ref_Iq == 0.0F && *rty_ref_Id == 0.0F ||
      (struct_PMSM_Config.mot_I_max_A < fabsf
       (rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_P_A[0]) ||
       struct_PMSM_Config.mot_I_max_A < fabsf
       (rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_P_A[1]) ||
       struct_PMSM_Config.mot_I_max_A < fabsf
       (rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_P_A[2]))) {
    *rty_Ualpha = 0.0F;
    *rty_Ubeta = 0.0F;
  } else {
    *rty_Ualpha = rtb_Add1 * rtb_TrigonometricFunction1 + rtb_Product1_b *
      rtb_Gain1_h;
    *rty_Ubeta = rtb_Product1_b * rtb_TrigonometricFunction1 - rtb_Add1 *
      rtb_Gain1_h;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Outputs for Enabled SubSystem: '<S9>/abc_zu_dq1' */
  /* SignalConversion generated from: '<S21>/Enable' */
  abc_zu_dq1(rtu_trigger_actI_I_calc,
             rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_theta_el_rad,
             rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_I_A[0],
             rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_I_A[1],
             rtu_Bus_Live_Out_PMSM_Inport_2->pmsm_Iuvw_I_A[2], rty_act_id_I,
             rty_act_iq_I);

  /* End of Outputs for SubSystem: '<S9>/abc_zu_dq1' */

  /* Switch: '<S25>/Switch' incorporates:
   *  Constant: '<S9>/Constant2'
   */
  if (struct_Ctrl_Config.sel_act_I) {
    rtb_UnitDelay_a = *rty_act_id_I;
  } else {
    rtb_UnitDelay_a = *rty_act_id_P;
  }

  /* Update for UnitDelay: '<S25>/Unit Delay' incorporates:
   *  Constant: '<S25>/Constant1'
   *  Constant: '<S25>/Constant3'
   *  Gain: '<S17>/Gain1'
   *  Logic: '<S25>/Logical Operator'
   *  Product: '<S25>/Product1'
   *  Product: '<S25>/Product2'
   *  Product: '<S25>/Product3'
   *  RelationalOperator: '<S25>/Relational Operator'
   *  RelationalOperator: '<S25>/Relational Operator1'
   *  Sum: '<S25>/Add'
   *  Sum: '<S25>/Subtract1'
   *  Switch: '<S25>/Switch'
   */
  localDW->UnitDelay_DSTATE += (rtb_UnitDelay_g <= rtb_Product1_ki &&
    rtb_UnitDelay_g >= -rtb_Product1_ki ? *rty_ref_Id - rtb_UnitDelay_a : 0.0F) *
    struct_Ctrl_Config.KIi * struct_Ctrl_Config.Tsample;

  /* Switch: '<S26>/Switch' incorporates:
   *  Constant: '<S9>/Constant2'
   */
  if (struct_Ctrl_Config.sel_act_I) {
    rtb_UnitDelay_a = *rty_act_iq_I;
  } else {
    rtb_UnitDelay_a = *rty_act_iq_P;
  }

  /* Update for UnitDelay: '<S26>/Unit Delay' incorporates:
   *  Constant: '<S26>/Constant1'
   *  Constant: '<S26>/Constant3'
   *  Gain: '<S27>/Gain1'
   *  Logic: '<S26>/Logical Operator'
   *  Product: '<S26>/Product1'
   *  Product: '<S26>/Product2'
   *  Product: '<S26>/Product3'
   *  RelationalOperator: '<S26>/Relational Operator'
   *  RelationalOperator: '<S26>/Relational Operator1'
   *  Sum: '<S26>/Add'
   *  Sum: '<S26>/Subtract1'
   *  Switch: '<S26>/Switch'
   */
  localDW->UnitDelay_DSTATE_i += (rtb_Add1_a <= rtb_Add3 && rtb_Add1_a >=
    -rtb_Add3 ? *rty_ref_Iq - rtb_UnitDelay_a : 0.0F) * struct_Ctrl_Config.KIi *
    struct_Ctrl_Config.Tsample;
}

/* System initialize for enable system: '<S1>/Regelung' */
static void Regelung_Init(bool *rty_Dis, DW_Regelung *localDW)
{
  /* SystemInitialize for Enabled SubSystem: '<S3>/Drehzahlregelung' */
  Drehzahlregelung_Init(rty_Dis, &localDW->Drehzahlregelung_a);

  /* End of SystemInitialize for SubSystem: '<S3>/Drehzahlregelung' */

  /* SystemInitialize for Atomic SubSystem: '<S3>/Stromregelung' */
  Stromregelung_Init(&localDW->Stromregelung_b);

  /* End of SystemInitialize for SubSystem: '<S3>/Stromregelung' */
}

/* System reset for enable system: '<S1>/Regelung' */
static void Regelung_Reset(DW_Regelung *localDW)
{
  /* SystemReset for Atomic SubSystem: '<S3>/Stromregelung' */
  Stromregelung_Reset(&localDW->Stromregelung_b);

  /* End of SystemReset for SubSystem: '<S3>/Stromregelung' */
}

/* Disable for enable system: '<S1>/Regelung' */
static void Regelung_Disable(DW_Regelung *localDW)
{
  /* Disable for Enabled SubSystem: '<S3>/Drehzahlregelung' */
  if (localDW->Drehzahlregelung_a.Drehzahlregelung_MODE) {
    Drehzahlregelung_Disable(&localDW->Drehzahlregelung_a);
  }

  /* End of Disable for SubSystem: '<S3>/Drehzahlregelung' */
  localDW->Regelung_MODE = false;
}

/* Output and update for enable system: '<S1>/Regelung' */
static void Regelung(bool rtu_Enable, const Bus_PMSM_Out
                     *rtu_Bus_Live_Out_PMSM_Inport_1, const Bus_ZM_Out
                     *rtu_Bus_ZM_Out_Inport_2, bool rtu_trigger_actI_I_calc,
                     float *rty_Ualpha, float *rty_Ubeta, bool *rty_Dis, float
                     *rty_Soll_Moment, float *rty_IQRef, float *rty_ctrl_omega,
                     float *rty_soll_omega, float *rty_ctrl_Iq, float
                     *rty_act_id_I, float *rty_act_iq_I, float *rty_act_id_P,
                     float *rty_ref_Id, DW_Regelung *localDW)
{
  /* Outputs for Enabled SubSystem: '<S1>/Regelung' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (rtu_Enable) {
    if (!localDW->Regelung_MODE) {
      Regelung_Reset(localDW);
      localDW->Regelung_MODE = true;
    }

    /* Outputs for Enabled SubSystem: '<S3>/Drehzahlregelung' */
    /* RelationalOperator: '<S7>/Compare' incorporates:
     *  Constant: '<S7>/Constant'
     */
    Drehzahlregelung(rtu_Bus_ZM_Out_Inport_2->Ist_Regelungsart <= Drehzahl,
                     rtu_Bus_Live_Out_PMSM_Inport_1->pmsm_Omega_mech_rad_s,
                     rtu_Bus_ZM_Out_Inport_2, rty_Dis, rty_Soll_Moment,
                     rty_ctrl_omega, rty_soll_omega,
                     &localDW->Drehzahlregelung_a);

    /* End of Outputs for SubSystem: '<S3>/Drehzahlregelung' */

    /* Outputs for Atomic SubSystem: '<S3>/Stromregelung' */
    Stromregelung(*rty_Soll_Moment, rtu_Bus_Live_Out_PMSM_Inport_1,
                  rtu_Bus_ZM_Out_Inport_2, rtu_trigger_actI_I_calc, rty_Ualpha,
                  rty_Ubeta, rty_IQRef, rty_ctrl_Iq, rty_act_id_I, rty_act_iq_I,
                  rty_act_id_P, rty_ref_Id, &localDW->Stromregelung_b);

    /* End of Outputs for SubSystem: '<S3>/Stromregelung' */
  } else if (localDW->Regelung_MODE) {
    Regelung_Disable(localDW);
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
  rty_Bus_ZM_Out->Soll_Drehzahl_Umin = 0.0F;
  rty_Bus_ZM_Out->Soll_id_A = 0.0F;
  rty_Bus_ZM_Out->Soll_iq_A = 0.0F;
  rty_Bus_ZM_Out->pwr_en = false;
  rty_Bus_ZM_Out->board_en = false;
  rty_Bus_ZM_Out->reset = false;
  localDW->is_active_c3_uz_codegen0 = 0U;
  localDW->is_c3_uz_codegen0 = IN_NO_ACTIVE_CHILD;
  localDW->is_NoError = IN_NO_ACTIVE_CHILD;
  localDW->is_Run = IN_NO_ACTIVE_CHILD;
}

/* Output and update for atomic system: '<S4>/state_chart' */
static void state_chart(const Bus_ZM_In *rtu_Bus_ZM_In, Bus_ZM_Out
  *rty_Bus_ZM_Out, DW_state_chart *localDW)
{
  /* Chart: '<S4>/state_chart' */
  /* Gateway: uz_codegen/Zustandsmaschine/state_chart */
  /* During: uz_codegen/Zustandsmaschine/state_chart */
  if (localDW->is_active_c3_uz_codegen0 == 0) {
    /* Entry: uz_codegen/Zustandsmaschine/state_chart */
    localDW->is_active_c3_uz_codegen0 = 1U;

    /* Entry Internal: uz_codegen/Zustandsmaschine/state_chart */
    /* Transition: '<S36>:11' */
    localDW->is_c3_uz_codegen0 = IN_NoError;

    /* Entry Internal 'NoError': '<S36>:32' */
    /* Transition: '<S36>:45' */
    localDW->is_NoError = IN_Idle;
  } else if (localDW->is_c3_uz_codegen0 == IN_Error) {
    /* During 'Error': '<S36>:10' */
    /* '<S36>:14:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == false && Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state); */
    if (!rtu_Bus_ZM_In->Fehlermeldung && rtu_Bus_ZM_In->UZ_Platform_State ==
        idle_state) {
      /* Transition: '<S36>:14' */
      localDW->is_c3_uz_codegen0 = IN_NoError;

      /* Entry Internal 'NoError': '<S36>:32' */
      /* Transition: '<S36>:45' */
      localDW->is_NoError = IN_Idle;
    } else {
      /* '<S36>:10:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Error_Status; */
      rty_Bus_ZM_Out->Ist_Status = Error_Status;

      /* '<S36>:10:4' Bus_ZM_Out.Pulsfreigabe = false; */
      rty_Bus_ZM_Out->Pulsfreigabe = false;

      /* '<S36>:10:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Error; */
      rty_Bus_ZM_Out->Ist_Regelungsart = Error;

      /* '<S36>:10:6' Bus_ZM_Out.En_Traj = false; */
      rty_Bus_ZM_Out->En_Traj = false;

      /* '<S36>:10:7' Bus_ZM_Out.Soll_Drehzahl_Umin = 0; */
      rty_Bus_ZM_Out->Soll_Drehzahl_Umin = 0.0F;

      /* '<S36>:10:8' Bus_ZM_Out.Soll_id_A = 0; */
      rty_Bus_ZM_Out->Soll_id_A = 0.0F;

      /* '<S36>:10:9' Bus_ZM_Out.Soll_iq_A = 0; */
      rty_Bus_ZM_Out->Soll_iq_A = 0.0F;

      /* '<S36>:10:10' Bus_ZM_Out.reset  = true; */
      rty_Bus_ZM_Out->reset = true;

      /* '<S36>:10:11' Bus_ZM_Out.pwr_en  = false; */
      rty_Bus_ZM_Out->pwr_en = false;

      /* '<S36>:10:12' Bus_ZM_Out.board_en  = false; */
      rty_Bus_ZM_Out->board_en = false;
    }

    /* During 'NoError': '<S36>:32' */
    /* '<S36>:15:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Fehlermeldung == true || Bus_ZM_In.UZ_Platform_State == platform_state_t.error_state || Bus_ZM_In.IGBT_desat == true); */
  } else if (rtu_Bus_ZM_In->Fehlermeldung || rtu_Bus_ZM_In->UZ_Platform_State ==
             error_state || rtu_Bus_ZM_In->IGBT_desat) {
    /* Transition: '<S36>:15' */
    /* Exit Internal 'NoError': '<S36>:32' */
    /* Exit Internal 'Run': '<S36>:20' */
    localDW->is_Run = IN_NO_ACTIVE_CHILD;
    localDW->is_NoError = IN_NO_ACTIVE_CHILD;
    localDW->is_c3_uz_codegen0 = IN_Error;
  } else {
    switch (localDW->is_NoError) {
     case IN_Idle:
      /* During 'Idle': '<S36>:103' */
      /* '<S36>:104:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.running_state); */
      if (rtu_Bus_ZM_In->UZ_Platform_State == running_state) {
        /* Transition: '<S36>:104' */
        localDW->is_NoError = IN_Ready;
      } else {
        /* '<S36>:103:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
        rty_Bus_ZM_Out->Ist_Status = Ready;

        /* '<S36>:103:4' Bus_ZM_Out.Pulsfreigabe = false; */
        rty_Bus_ZM_Out->Pulsfreigabe = false;

        /* '<S36>:103:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

        /* '<S36>:103:6' Bus_ZM_Out.En_Traj=false; */
        rty_Bus_ZM_Out->En_Traj = false;

        /* '<S36>:103:7' Bus_ZM_Out.Soll_Drehzahl_Umin = 0; */
        rty_Bus_ZM_Out->Soll_Drehzahl_Umin = 0.0F;

        /* '<S36>:103:8' Bus_ZM_Out.Soll_id_A = 0; */
        rty_Bus_ZM_Out->Soll_id_A = 0.0F;

        /* '<S36>:103:9' Bus_ZM_Out.Soll_iq_A = 0; */
        rty_Bus_ZM_Out->Soll_iq_A = 0.0F;

        /* '<S36>:103:10' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S36>:103:11' Bus_ZM_Out.pwr_en  = false; */
        rty_Bus_ZM_Out->pwr_en = false;

        /* '<S36>:103:12' Bus_ZM_Out.board_en  = false; */
        rty_Bus_ZM_Out->board_en = false;
      }
      break;

     case IN_Ready:
      /* During 'Ready': '<S36>:19' */
      /* '<S36>:25:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.control_state && Bus_ZM_In.Inv_Ready == true); */
      if (rtu_Bus_ZM_In->UZ_Platform_State == control_state &&
          rtu_Bus_ZM_In->Inv_Ready) {
        /* Transition: '<S36>:25' */
        localDW->is_NoError = IN_Run;

        /* Entry Internal 'Run': '<S36>:20' */
        /* Transition: '<S36>:55' */
        localDW->is_Run = IN_nCtrl;

        /* '<S36>:105:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state); */
      } else if (rtu_Bus_ZM_In->UZ_Platform_State == idle_state) {
        /* Transition: '<S36>:105' */
        localDW->is_NoError = IN_Idle;
      } else {
        /* '<S36>:19:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Ready; */
        rty_Bus_ZM_Out->Ist_Status = Ready;

        /* '<S36>:19:4' Bus_ZM_Out.Pulsfreigabe = false; */
        rty_Bus_ZM_Out->Pulsfreigabe = false;

        /* '<S36>:19:5' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
        rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

        /* '<S36>:19:6' Bus_ZM_Out.En_Traj=false; */
        rty_Bus_ZM_Out->En_Traj = false;

        /* '<S36>:19:7' Bus_ZM_Out.Soll_Drehzahl_Umin = 0; */
        rty_Bus_ZM_Out->Soll_Drehzahl_Umin = 0.0F;

        /* '<S36>:19:8' Bus_ZM_Out.Soll_id_A = 0; */
        rty_Bus_ZM_Out->Soll_id_A = 0.0F;

        /* '<S36>:19:9' Bus_ZM_Out.Soll_iq_A = 0; */
        rty_Bus_ZM_Out->Soll_iq_A = 0.0F;

        /* '<S36>:19:10' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S36>:19:11' Bus_ZM_Out.pwr_en  = true; */
        rty_Bus_ZM_Out->pwr_en = true;

        /* '<S36>:19:12' Bus_ZM_Out.board_en  = true; */
        rty_Bus_ZM_Out->board_en = true;
      }
      break;

     default:
      /* During 'Run': '<S36>:20' */
      /* '<S36>:106:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.UZ_Platform_State == platform_state_t.idle_state || Bus_ZM_In.Inv_Ready == false); */
      if (rtu_Bus_ZM_In->UZ_Platform_State == idle_state ||
          !rtu_Bus_ZM_In->Inv_Ready) {
        /* Transition: '<S36>:106' */
        /* Exit Internal 'Run': '<S36>:20' */
        localDW->is_Run = IN_NO_ACTIVE_CHILD;
        localDW->is_NoError = IN_Idle;
      } else {
        /* '<S36>:20:3' Bus_ZM_Out.Ist_Status = Status_Ctrl.Run; */
        rty_Bus_ZM_Out->Ist_Status = Run;

        /* '<S36>:20:4' Bus_ZM_Out.Pulsfreigabe = true; */
        rty_Bus_ZM_Out->Pulsfreigabe = true;

        /* '<S36>:20:5' Bus_ZM_Out.reset  = false; */
        rty_Bus_ZM_Out->reset = false;

        /* '<S36>:20:6' Bus_ZM_Out.pwr_en  = true; */
        rty_Bus_ZM_Out->pwr_en = true;

        /* '<S36>:20:7' Bus_ZM_Out.board_en  = true; */
        rty_Bus_ZM_Out->board_en = true;
        if (localDW->is_Run == IN_Stromregelung) {
          /* During 'Stromregelung': '<S36>:86' */
          /* '<S36>:92:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart ~= Soll_Regelungsart_en.Strom); */
          if (rtu_Bus_ZM_In->Soll_Regelungsart != Strom) {
            /* Transition: '<S36>:92' */
            localDW->is_Run = IN_nCtrl;
          } else {
            /* '<S36>:86:3' Bus_ZM_Out.Soll_id_A = Bus_ZM_In.Soll_id_A; */
            rty_Bus_ZM_Out->Soll_id_A = rtu_Bus_ZM_In->Soll_id_A;

            /* '<S36>:86:4' Bus_ZM_Out.Soll_iq_A = Bus_ZM_In.Soll_iq_A; */
            rty_Bus_ZM_Out->Soll_iq_A = rtu_Bus_ZM_In->Soll_iq_A;

            /* '<S36>:86:5' Bus_ZM_Out.Soll_Drehzahl_Umin = 0; */
            rty_Bus_ZM_Out->Soll_Drehzahl_Umin = 0.0F;

            /* '<S36>:86:6' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Strom; */
            rty_Bus_ZM_Out->Ist_Regelungsart = Strom;
          }

          /* During 'nCtrl': '<S36>:56' */
          /* '<S36>:91:1' sf_internal_predicateOutput = 0 | (Bus_ZM_In.Soll_Regelungsart == Soll_Regelungsart_en.Strom); */
        } else if (rtu_Bus_ZM_In->Soll_Regelungsart == Strom) {
          /* Transition: '<S36>:91' */
          localDW->is_Run = IN_Stromregelung;
        } else {
          /* '<S36>:56:3' Bus_ZM_Out.Ist_Regelungsart = Soll_Regelungsart_en.Drehzahl; */
          rty_Bus_ZM_Out->Ist_Regelungsart = Drehzahl;

          /* '<S36>:56:4' Bus_ZM_Out.Soll_Drehzahl_Umin = Bus_ZM_In.Soll_Drehzahl_Umin; */
          rty_Bus_ZM_Out->Soll_Drehzahl_Umin = rtu_Bus_ZM_In->Soll_Drehzahl_Umin;

          /* '<S36>:56:5' Bus_ZM_Out.Soll_id_A = 0; */
          rty_Bus_ZM_Out->Soll_id_A = 0.0F;

          /* '<S36>:56:6' Bus_ZM_Out.Soll_iq_A = 0; */
          rty_Bus_ZM_Out->Soll_iq_A = 0.0F;
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
static void Zustandsmaschine(const Bus_ZM_In *rtu_Bus_ZM_In_Inport_1, Bus_ZM_Out
  *rty_Bus_ZM_Out_Outport_1, DW_Zustandsmaschine *localDW)
{
  /* Chart: '<S4>/state_chart' */
  state_chart(rtu_Bus_ZM_In_Inport_1, rty_Bus_ZM_Out_Outport_1,
              &localDW->sf_state_chart);
}

/* Model step function */
void uz_codegen0_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  ExtU *rtU = (ExtU *) rtM->inputs;
  ExtY *rtY = (ExtY *) rtM->outputs;
  bool OutportBufferForDis;

  /* Outputs for Atomic SubSystem: '<S1>/Zustandsmaschine' */
  Zustandsmaschine(&rtU->Bus_ZM_In_j, &rtDW->Bus_ZM_Out_h,
                   &rtDW->Zustandsmaschine_k);

  /* End of Outputs for SubSystem: '<S1>/Zustandsmaschine' */

  /* Outputs for Enabled SubSystem: '<S1>/Regelung' */

  /* SignalConversion generated from: '<S3>/Enable' */
  Regelung(rtDW->Bus_ZM_Out_h.Pulsfreigabe, &rtU->Bus_PMSM_Out_f,
           &rtDW->Bus_ZM_Out_h, rtU->trigger_actI_I_calc, &rtDW->Switch,
           &rtDW->Switch1, &OutportBufferForDis, &rtY->Soll_Moment, &rtY->IQRef,
           &rtY->ctrl_omega, &rtY->soll_omega, &rtY->Ist_Iq, &rtY->act_id_I,
           &rtY->act_iq_I, &rtY->act_id_P, &rtY->ref_Id, &rtDW->Regelung_f);

  /* End of Outputs for SubSystem: '<S1>/Regelung' */

  /* Outputs for Enabled SubSystem: '<S1>/Raumzeigermodulation' */

  /* SignalConversion generated from: '<S2>/Enable' */
  Raumzeigermodulation(rtDW->Bus_ZM_Out_h.Pulsfreigabe, rtDW->Switch,
                       rtDW->Switch1, rtY->Bus_Ctrl_Out_f.Dutycycle);

  /* End of Outputs for SubSystem: '<S1>/Raumzeigermodulation' */

  /* BusCreator generated from: '<S1>/Bus_Ctrl_Out_BusCreator' incorporates:
   *  Outport: '<Root>/Bus_Ctrl_Out'
   */
  rtY->Bus_Ctrl_Out_f.act_pwm = rtDW->Bus_ZM_Out_h.Pulsfreigabe;
  rtY->Bus_Ctrl_Out_f.ctrl_Ualpha_V = rtDW->Switch;
  rtY->Bus_Ctrl_Out_f.ctrl_Ubeta_V = rtDW->Switch1;
  rtY->Bus_Ctrl_Out_f.pwr_en = rtDW->Bus_ZM_Out_h.pwr_en;
  rtY->Bus_Ctrl_Out_f.board_en = rtDW->Bus_ZM_Out_h.board_en;
  rtY->Bus_Ctrl_Out_f.reset = rtDW->Bus_ZM_Out_h.reset;
  rtY->Bus_Ctrl_Out_f.ZM_Ist_Status = rtDW->Bus_ZM_Out_h.Ist_Status;
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
    rtDW->Bus_ZM_Out_h = uz_codegen0_rtZBus_ZM_Out;
  }

  /* external inputs */
  (void)memset(rtU, 0, sizeof(ExtU));
  rtU->Bus_ZM_In_j = uz_codegen0_rtZBus_ZM_In;

  /* external outputs */
  (void)memset(rtY, 0, sizeof(ExtY));
  rtY->Bus_Ctrl_Out_f = uz_codegen0_rtZBus_Ctrl_Out;

  {
    bool OutportBufferForDis;

    /* SystemInitialize for Atomic SubSystem: '<S1>/Zustandsmaschine' */
    Zustandsmaschine_Init(&rtDW->Bus_ZM_Out_h, &rtDW->Zustandsmaschine_k);

    /* End of SystemInitialize for SubSystem: '<S1>/Zustandsmaschine' */

    /* SystemInitialize for Enabled SubSystem: '<S1>/Regelung' */
    Regelung_Init(&OutportBufferForDis, &rtDW->Regelung_f);

    /* End of SystemInitialize for SubSystem: '<S1>/Regelung' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
