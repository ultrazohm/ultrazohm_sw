/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SMF.c
 *
 * Code generated for Simulink model 'FOC_SMF'.
 *
 * Model version                  : 5.64
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Feb 19 10:18:36 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_SMF.h"
#include "rtwtypes.h"
#include <math.h>
#include "FOC_SMF_types.h"
#include <string.h>

/* Named constants for Chart: '<S1>/FOC_Statemachine' */
#define FOC_SMF_IN_CTRL_IDLE           ((uint8_T)1U)
#define FOC_SMF_IN_CTRL_INIT           ((uint8_T)2U)
#define FOC_SMF_IN_CTRL_RE_INIT        ((uint8_T)3U)
#define FOC_SMF_IN_ERROR_MODE          ((uint8_T)4U)
#define FOC_SMF_IN_FOC_IDLE            ((uint8_T)1U)
#define FOC_SMF_IN_FOC_SPEED           ((uint8_T)2U)
#define FOC_SMF_IN_FOC_STANDBY         ((uint8_T)3U)
#define FOC_SMF_IN_FOC_TORQUE          ((uint8_T)4U)
#define FOC_SMF_IN_NO_ACTIVE_CHILD     ((uint8_T)0U)
#define FOC_SMF_IN_RUN_MODE            ((uint8_T)5U)
#define FOC_SMF_IN_SYS_INIT            ((uint8_T)6U)

const bus_SMF_t FOC_SMF_rtZbus_SMF_t = { 0.0F,/* SysStateAct */
  0.0F,                                /* FOC_Mode */
  0.0F,                                /* StateFOC */
  0.0F,                                /* FOC_Enable_PWM */
  0.0F,                                /* global_reset_errors */
  0.0F,                                /* SPEED_CTRL_Enable */
  0.0F                                 /* MaxMotTemp */
};

/* Model step function */
void FOC_SMF_step(RT_MODEL_FOC_SMF_T *const FOC_SMF_M)
{
  B_FOC_SMF_T *FOC_SMF_B = FOC_SMF_M->blockIO;
  DW_FOC_SMF_T *FOC_SMF_DW = FOC_SMF_M->dwork;
  ExtU_FOC_SMF_T *FOC_SMF_U = (ExtU_FOC_SMF_T *) FOC_SMF_M->inputs;
  ExtY_FOC_SMF_T *FOC_SMF_Y = (ExtY_FOC_SMF_T *) FOC_SMF_M->outputs;
  int32_T i;
  real32_T bus_BSW_SMF;
  boolean_T tmpForInput[6];
  boolean_T tmp;
  boolean_T tmp_0;
  boolean_T tmp_1;
  boolean_T tmp_2;
  boolean_T tmp_3;
  boolean_T tmp_4;
  boolean_T tmp_5;
  boolean_T tmp_6;
  boolean_T tmp_7;
  boolean_T tmp_8;
  boolean_T tmp_9;
  boolean_T tmp_a;
  boolean_T tmp_b;
  boolean_T tmp_c;
  boolean_T tmp_d;
  boolean_T tmp_e;
  boolean_T tmp_f;
  boolean_T tmp_g;
  boolean_T tmp_h;
  boolean_T tmp_i;
  boolean_T tmp_j;
  boolean_T tmp_k;
  boolean_T tmp_l;
  boolean_T tmp_m;
  boolean_T tmp_n;
  boolean_T tmp_o;
  boolean_T tmp_p;
  boolean_T tmp_q;
  boolean_T tmp_r;
  boolean_T tmp_s;
  boolean_T tmp_t;

  /* MultiPortSwitch: '<S1>/DataSourceSwitch' incorporates:
   *  Constant: '<S1>/SELECT_DataSource'
   */
  if (FOC_SMF_P.SELECT_DataSource == 0) {
    /* MultiPortSwitch: '<S1>/DataSourceSwitch' */
    FOC_SMF_B->DataSourceSwitch[0] = FOC_SMF_U->bus_BSW_SMF.EXT_State_Request;
    FOC_SMF_B->DataSourceSwitch[1] = FOC_SMF_U->bus_BSW_SMF.EXT_Torque_Request;
    FOC_SMF_B->DataSourceSwitch[2] = FOC_SMF_U->bus_BSW_SMF.EXT_Speed_Request;
  } else {
    /* MultiPortSwitch: '<S1>/DataSourceSwitch' incorporates:
     *  Constant: '<S1>/Constant'
     *  Constant: '<S1>/MANUAL_StateReq'
     *  Constant: '<S1>/OmegaRot2'
     */
    FOC_SMF_B->DataSourceSwitch[0] = FOC_SMF_P.FOC_MANUAL_State_Request;
    FOC_SMF_B->DataSourceSwitch[1] = FOC_SMF_P.FOC_MANUAL_Torque_Request;
    FOC_SMF_B->DataSourceSwitch[2] = FOC_SMF_P.SPEED_CTRL_MANUAL_n_RPM;
  }

  /* End of MultiPortSwitch: '<S1>/DataSourceSwitch' */

  /* MultiPortSwitch: '<S1>/KL15_PG_SourceSwitch' incorporates:
   *  Constant: '<S1>/SELECT_KL15_PG'
   */
  if (FOC_SMF_P.SELECT_KL15_PG == 0) {
    /* MultiPortSwitch: '<S1>/KL15_PG_SourceSwitch' */
    FOC_SMF_B->KL15_PG_SourceSwitch = FOC_SMF_U->bus_BSW_SMF.EXT_KL15_PG;
  } else {
    /* MultiPortSwitch: '<S1>/KL15_PG_SourceSwitch' incorporates:
     *  Constant: '<S1>/FOC_MANUAL_KL15_PG'
     */
    FOC_SMF_B->KL15_PG_SourceSwitch = FOC_SMF_P.FOC_MANUAL_KL15_PG;
  }

  /* End of MultiPortSwitch: '<S1>/KL15_PG_SourceSwitch' */

  /* Chart: '<S1>/FOC_Statemachine' */
  if (FOC_SMF_DW->is_active_c1_FOC_SMF == 0U) {
    FOC_SMF_DW->is_active_c1_FOC_SMF = 1U;
    FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_SYS_INIT;
    FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_SYS_INIT;
    FOC_SMF_Y->bus_SMF.FOC_Mode = 1.0F;
    FOC_SMF_B->global_reset_errors = 1.0F;
  } else {
    switch (FOC_SMF_DW->is_c1_FOC_SMF) {
     case FOC_SMF_IN_CTRL_IDLE:
      FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_CTRL_IDLE;
      FOC_SMF_Y->bus_SMF.FOC_Mode = 1.0F;
      if (FOC_SMF_U->bus_FCF.FCF_Error) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_ERROR_MODE;
      } else if (FOC_SMF_B->DataSourceSwitch[0] == FOC_SMF_P.enumState_RUN_MODE)
      {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_RUN_MODE;
        FOC_SMF_Y->bus_SMF.FOC_Mode = 3.0F;
        FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_IDLE;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_RUN_MODE;
        FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_IDLE;
        FOC_SMF_Y->bus_SMF.FOC_Enable_PWM = 0.0F;
      }
      break;

     case FOC_SMF_IN_CTRL_INIT:
      FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_CTRL_INIT;
      if (FOC_SMF_U->bus_FCF.FCF_Error) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_ERROR_MODE;
      } else if (FOC_SMF_B->DataSourceSwitch[0] == FOC_SMF_P.enumState_CTRL_IDLE)
      {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_CTRL_IDLE;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_CTRL_IDLE;
        FOC_SMF_Y->bus_SMF.FOC_Mode = 1.0F;
      }
      break;

     case FOC_SMF_IN_CTRL_RE_INIT:
      FOC_SMF_Y->bus_SMF.SysStateAct = (real32_T)
        FOC_SMF_P.enumState_CTRL_RE_INIT;
      if ((FOC_SMF_B->DataSourceSwitch[0] == FOC_SMF_P.enumState_CTRL_IDLE) && (
           !FOC_SMF_U->bus_FCF.FCF_Error)) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_SYS_INIT;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_SYS_INIT;
        FOC_SMF_Y->bus_SMF.FOC_Mode = 1.0F;
        FOC_SMF_B->global_reset_errors = 1.0F;
      } else if (FOC_SMF_U->bus_FCF.FCF_Error) {
        FOC_SMF_B->global_reset_errors = 0.0F;
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_ERROR_MODE;
      }
      break;

     case FOC_SMF_IN_ERROR_MODE:
      FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_ERROR_MODE;
      if (FOC_SMF_B->DataSourceSwitch[0] == FOC_SMF_P.enumState_CTRL_IDLE) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_CTRL_RE_INIT;
        FOC_SMF_Y->bus_SMF.SysStateAct = (real32_T)
          FOC_SMF_P.enumState_CTRL_RE_INIT;
        FOC_SMF_B->global_reset_errors = 1.0F;
      }
      break;

     case FOC_SMF_IN_RUN_MODE:
      FOC_SMF_Y->bus_SMF.FOC_Mode = 3.0F;
      if (FOC_SMF_U->bus_FCF.FCF_Error) {
        if (FOC_SMF_DW->is_RUN_MODE == FOC_SMF_IN_FOC_SPEED) {
          FOC_SMF_Y->bus_SMF.SPEED_CTRL_Enable = 0.0F;
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
        } else {
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
        }

        FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_OFF;
        FOC_SMF_Y->bus_SMF.FOC_Enable_PWM = 0.0F;
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_ERROR_MODE;
      } else if (FOC_SMF_B->DataSourceSwitch[0] == FOC_SMF_P.enumState_CTRL_IDLE)
      {
        if (FOC_SMF_DW->is_RUN_MODE == FOC_SMF_IN_FOC_SPEED) {
          FOC_SMF_Y->bus_SMF.SPEED_CTRL_Enable = 0.0F;
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
        } else {
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
        }

        FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_OFF;
        FOC_SMF_Y->bus_SMF.FOC_Enable_PWM = 0.0F;
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_CTRL_IDLE;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_CTRL_IDLE;
        FOC_SMF_Y->bus_SMF.FOC_Mode = 1.0F;
      } else {
        switch (FOC_SMF_DW->is_RUN_MODE) {
         case FOC_SMF_IN_FOC_IDLE:
          FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_RUN_MODE;
          if ((FOC_SMF_B->DataSourceSwitch[1] == 0.0F) &&
              (FOC_SMF_B->DataSourceSwitch[2] == 0.0F)) {
            FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_STANDBY;
            FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_STANDBY;
            FOC_SMF_Y->bus_SMF.FOC_Enable_PWM = 1.0F;
          }
          break;

         case FOC_SMF_IN_FOC_SPEED:
          FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_SPEED_MODE;
          break;

         case FOC_SMF_IN_FOC_STANDBY:
          if (FOC_SMF_B->DataSourceSwitch[0] == FOC_SMF_P.enumState_TORQUE_MODE)
          {
            FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_TORQUE;
            FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_TORQUE_MODE;
            FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_TORQUE;
          } else if (FOC_SMF_B->DataSourceSwitch[0] ==
                     FOC_SMF_P.enumState_SPEED_MODE) {
            FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_SPEED;
            FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_SPEED_MODE;
            FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_SPEED;
            FOC_SMF_Y->bus_SMF.SPEED_CTRL_Enable = 1.0F;
          }
          break;

         default:
          /* case IN_FOC_TORQUE: */
          FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_TORQUE_MODE;
          break;
        }
      }
      break;

     default:
      /* case IN_SYS_INIT: */
      FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_SYS_INIT;
      FOC_SMF_Y->bus_SMF.FOC_Mode = 1.0F;
      if (FOC_SMF_U->bus_FCF.FCF_Error) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_ERROR_MODE;
      } else if ((FOC_SMF_B->DataSourceSwitch[0] ==
                  FOC_SMF_P.enumState_CTRL_IDLE) &&
                 FOC_SMF_B->KL15_PG_SourceSwitch) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_CTRL_INIT;
        FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_P.enumState_CTRL_INIT;
        FOC_SMF_B->global_reset_errors = 0.0F;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/FOC_Statemachine' */

  /* MinMax: '<S4>/MinMax1' incorporates:
   *  Inport: '<Root>/bus_BSW_SCF'
   */
  bus_BSW_SMF = FOC_SMF_U->bus_BSW_SMF.MotTemp[0];
  for (i = 0; i < 5; i++) {
    bus_BSW_SMF = fmaxf(bus_BSW_SMF, FOC_SMF_U->bus_BSW_SMF.MotTemp[i + 1]);
  }

  FOC_SMF_Y->bus_SMF.MaxMotTemp = bus_BSW_SMF;

  /* End of MinMax: '<S4>/MinMax1' */

  /* BusCreator: '<S1>/Bus Creator' incorporates:
   *  Outport: '<Root>/bus_SMF'
   */
  FOC_SMF_Y->bus_SMF.global_reset_errors = FOC_SMF_B->global_reset_errors;

  /* MinMax: '<S4>/MinMax' incorporates:
   *  Inport: '<Root>/bus_BSW_SCF'
   */
  bus_BSW_SMF = FOC_SMF_U->bus_BSW_SMF.InvTemp[0];
  for (i = 0; i < 8; i++) {
    bus_BSW_SMF = fmaxf(bus_BSW_SMF, FOC_SMF_U->bus_BSW_SMF.InvTemp[i + 1]);
  }

  /* MinMax: '<S4>/MinMax' */
  FOC_SMF_B->MinMax = bus_BSW_SMF;
  for (i = 0; i < 9; i++) {
    /* RelationalOperator: '<S6>/Compare' incorporates:
     *  Constant: '<S6>/Constant'
     *  Inport: '<Root>/bus_BSW_SCF'
     */
    FOC_SMF_B->Compare[i] = (FOC_SMF_U->bus_BSW_SMF.InvTemp[i] >
      FOC_SMF_P.LIMIT_Inverter_Over_Temp);
  }

  /* UnitDelay: '<S8>/Delay Input1'
   *
   * Block description for '<S8>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_SMF_B->Uk1 = FOC_SMF_DW->DelayInput1_DSTATE;

  /* Logic: '<S5>/Logical Operator3' incorporates:
   *  Constant: '<S5>/Reset_OT_Error'
   */
  FOC_SMF_B->LogicalOperator3 = ((FOC_SMF_P.FOC_RESET_OT_Error != 0.0) ||
    (FOC_SMF_B->global_reset_errors != 0.0F));

  /* RelationalOperator: '<S11>/Compare' incorporates:
   *  Constant: '<S11>/Constant'
   */
  FOC_SMF_B->Compare_m3 = ((int32_T)FOC_SMF_B->LogicalOperator3 > (int32_T)
    FOC_SMF_P.Constant_Value);

  /* RelationalOperator: '<S8>/FixPt Relational Operator' */
  FOC_SMF_B->FixPtRelationalOperator = ((int32_T)FOC_SMF_B->Compare_m3 >
    (int32_T)FOC_SMF_B->Uk1);

  /* Memory: '<S12>/Memory' */
  FOC_SMF_B->Memory = FOC_SMF_DW->Memory_PreviousInput;

  /* CombinatorialLogic: '<S12>/Logic' */
  tmp_s = FOC_SMF_B->FixPtRelationalOperator;
  tmp_t = FOC_SMF_B->Memory;

  /* Memory: '<S13>/Memory' */
  FOC_SMF_B->Memory_e = FOC_SMF_DW->Memory_PreviousInput_e;

  /* CombinatorialLogic: '<S13>/Logic' */
  tmp_p = FOC_SMF_B->FixPtRelationalOperator;
  tmp_q = FOC_SMF_B->Memory_e;

  /* Memory: '<S14>/Memory' */
  FOC_SMF_B->Memory_i = FOC_SMF_DW->Memory_PreviousInput_k;

  /* CombinatorialLogic: '<S14>/Logic' */
  tmp_n = FOC_SMF_B->FixPtRelationalOperator;
  tmp_o = FOC_SMF_B->Memory_i;

  /* Memory: '<S15>/Memory' */
  FOC_SMF_B->Memory_ej = FOC_SMF_DW->Memory_PreviousInput_m;

  /* CombinatorialLogic: '<S15>/Logic' */
  tmp_l = FOC_SMF_B->FixPtRelationalOperator;
  tmp_m = FOC_SMF_B->Memory_ej;

  /* Memory: '<S16>/Memory' */
  FOC_SMF_B->Memory_b = FOC_SMF_DW->Memory_PreviousInput_f;

  /* CombinatorialLogic: '<S16>/Logic' */
  tmp_j = FOC_SMF_B->FixPtRelationalOperator;
  tmp_k = FOC_SMF_B->Memory_b;

  /* Memory: '<S17>/Memory' */
  FOC_SMF_B->Memory_m = FOC_SMF_DW->Memory_PreviousInput_j;

  /* CombinatorialLogic: '<S17>/Logic' */
  tmp_h = FOC_SMF_B->FixPtRelationalOperator;
  tmp_i = FOC_SMF_B->Memory_m;

  /* Memory: '<S18>/Memory' */
  FOC_SMF_B->Memory_l = FOC_SMF_DW->Memory_PreviousInput_i;

  /* CombinatorialLogic: '<S18>/Logic' */
  tmp_e = FOC_SMF_B->Compare[0];
  tmp_f = FOC_SMF_B->FixPtRelationalOperator;
  tmp_g = FOC_SMF_B->Memory_l;

  /* Memory: '<S19>/Memory' */
  FOC_SMF_B->Memory_bk = FOC_SMF_DW->Memory_PreviousInput_p;

  /* CombinatorialLogic: '<S19>/Logic' */
  tmp_b = FOC_SMF_B->Compare[1];
  tmp_c = FOC_SMF_B->FixPtRelationalOperator;
  tmp_d = FOC_SMF_B->Memory_bk;

  /* Memory: '<S20>/Memory' */
  FOC_SMF_B->Memory_a = FOC_SMF_DW->Memory_PreviousInput_n;

  /* CombinatorialLogic: '<S20>/Logic' */
  tmp_8 = FOC_SMF_B->Compare[2];
  tmp_9 = FOC_SMF_B->FixPtRelationalOperator;
  tmp_a = FOC_SMF_B->Memory_a;

  /* Memory: '<S21>/Memory' */
  FOC_SMF_B->Memory_mt = FOC_SMF_DW->Memory_PreviousInput_fj;

  /* CombinatorialLogic: '<S21>/Logic' */
  tmp_5 = FOC_SMF_B->Compare[3];
  tmp_6 = FOC_SMF_B->FixPtRelationalOperator;
  tmp_7 = FOC_SMF_B->Memory_mt;

  /* Memory: '<S22>/Memory' */
  FOC_SMF_B->Memory_n = FOC_SMF_DW->Memory_PreviousInput_nt;

  /* CombinatorialLogic: '<S22>/Logic' */
  tmp_2 = FOC_SMF_B->Compare[4];
  tmp_3 = FOC_SMF_B->FixPtRelationalOperator;
  tmp_4 = FOC_SMF_B->Memory_n;

  /* Memory: '<S23>/Memory' */
  FOC_SMF_B->Memory_as = FOC_SMF_DW->Memory_PreviousInput_a;

  /* CombinatorialLogic: '<S23>/Logic' */
  tmp = FOC_SMF_B->Compare[5];
  tmp_0 = FOC_SMF_B->FixPtRelationalOperator;
  tmp_1 = FOC_SMF_B->Memory_as;
  for (i = 0; i < 6; i++) {
    /* RelationalOperator: '<S7>/Compare' incorporates:
     *  Inport: '<Root>/bus_BSW_SCF'
     */
    bus_BSW_SMF = FOC_SMF_U->bus_BSW_SMF.MotTemp[i];

    /* RelationalOperator: '<S7>/Compare' incorporates:
     *  Constant: '<S7>/Constant'
     */
    FOC_SMF_B->Compare_m[i] = (bus_BSW_SMF > FOC_SMF_P.LIMIT_EMotor_Over_Temp);

    /* Relay: '<S5>/LIMIT_EMotor_Warn_Temp' */
    if (bus_BSW_SMF >= FOC_SMF_P.LIMIT_EMotor_Warn_Temp) {
      FOC_SMF_DW->LIMIT_EMotor_Warn_Temp_Mode[i] = true;
    } else if (bus_BSW_SMF <= FOC_SMF_P.LIMIT_EMotor_Warn_Temp_OffVal) {
      FOC_SMF_DW->LIMIT_EMotor_Warn_Temp_Mode[i] = false;
    }

    if (FOC_SMF_DW->LIMIT_EMotor_Warn_Temp_Mode[i]) {
      bus_BSW_SMF = FOC_SMF_P.LIMIT_EMotor_Warn_Temp_YOn;
    } else {
      bus_BSW_SMF = FOC_SMF_P.LIMIT_EMotor_Warn_Temp_YOff;
    }

    FOC_SMF_B->LIMIT_EMotor_Warn_Temp[i] = bus_BSW_SMF;

    /* End of Relay: '<S5>/LIMIT_EMotor_Warn_Temp' */
  }

  /* CombinatorialLogic: '<S12>/Logic' */
  tmp_r = FOC_SMF_B->Compare_m[0];
  i = tmp_r;
  i = (int32_T)(((uint32_T)i << 1) + tmp_s);
  i = (int32_T)(((uint32_T)i << 1) + tmp_t);
  FOC_SMF_B->Logic[0U] = FOC_SMF_P.Logic_table[(uint32_T)i];
  FOC_SMF_B->Logic[1U] = FOC_SMF_P.Logic_table[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S13>/Logic' */
  tmp_r = FOC_SMF_B->Compare_m[1];
  i = tmp_r;
  i = (int32_T)(((uint32_T)i << 1) + tmp_p);
  i = (int32_T)(((uint32_T)i << 1) + tmp_q);
  FOC_SMF_B->Logic_f[0U] = FOC_SMF_P.Logic_table_l[(uint32_T)i];
  FOC_SMF_B->Logic_f[1U] = FOC_SMF_P.Logic_table_l[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S14>/Logic' */
  tmp_r = FOC_SMF_B->Compare_m[2];
  i = tmp_r;
  i = (int32_T)(((uint32_T)i << 1) + tmp_n);
  i = (int32_T)(((uint32_T)i << 1) + tmp_o);
  FOC_SMF_B->Logic_e[0U] = FOC_SMF_P.Logic_table_i[(uint32_T)i];
  FOC_SMF_B->Logic_e[1U] = FOC_SMF_P.Logic_table_i[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S15>/Logic' */
  tmp_r = FOC_SMF_B->Compare_m[3];
  i = tmp_r;
  i = (int32_T)(((uint32_T)i << 1) + tmp_l);
  i = (int32_T)(((uint32_T)i << 1) + tmp_m);
  FOC_SMF_B->Logic_fh[0U] = FOC_SMF_P.Logic_table_k[(uint32_T)i];
  FOC_SMF_B->Logic_fh[1U] = FOC_SMF_P.Logic_table_k[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S16>/Logic' */
  tmp_r = FOC_SMF_B->Compare_m[4];
  i = tmp_r;
  i = (int32_T)(((uint32_T)i << 1) + tmp_j);
  i = (int32_T)(((uint32_T)i << 1) + tmp_k);
  FOC_SMF_B->Logic_b[0U] = FOC_SMF_P.Logic_table_km[(uint32_T)i];
  FOC_SMF_B->Logic_b[1U] = FOC_SMF_P.Logic_table_km[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S17>/Logic' */
  tmp_r = FOC_SMF_B->Compare_m[5];
  i = tmp_r;
  i = (int32_T)(((uint32_T)i << 1) + tmp_h);
  i = (int32_T)(((uint32_T)i << 1) + tmp_i);
  FOC_SMF_B->Logic_o[0U] = FOC_SMF_P.Logic_table_h[(uint32_T)i];
  FOC_SMF_B->Logic_o[1U] = FOC_SMF_P.Logic_table_h[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S18>/Logic' */
  i = tmp_e;
  i = (int32_T)(((uint32_T)i << 1) + tmp_f);
  i = (int32_T)(((uint32_T)i << 1) + tmp_g);
  FOC_SMF_B->Logic_d[0U] = FOC_SMF_P.Logic_table_g[(uint32_T)i];
  FOC_SMF_B->Logic_d[1U] = FOC_SMF_P.Logic_table_g[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S19>/Logic' */
  i = tmp_b;
  i = (int32_T)(((uint32_T)i << 1) + tmp_c);
  i = (int32_T)(((uint32_T)i << 1) + tmp_d);
  FOC_SMF_B->Logic_bw[0U] = FOC_SMF_P.Logic_table_gb[(uint32_T)i];
  FOC_SMF_B->Logic_bw[1U] = FOC_SMF_P.Logic_table_gb[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S20>/Logic' */
  i = tmp_8;
  i = (int32_T)(((uint32_T)i << 1) + tmp_9);
  i = (int32_T)(((uint32_T)i << 1) + tmp_a);
  FOC_SMF_B->Logic_m[0U] = FOC_SMF_P.Logic_table_e[(uint32_T)i];
  FOC_SMF_B->Logic_m[1U] = FOC_SMF_P.Logic_table_e[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S21>/Logic' */
  i = tmp_5;
  i = (int32_T)(((uint32_T)i << 1) + tmp_6);
  i = (int32_T)(((uint32_T)i << 1) + tmp_7);
  FOC_SMF_B->Logic_dm[0U] = FOC_SMF_P.Logic_table_lq[(uint32_T)i];
  FOC_SMF_B->Logic_dm[1U] = FOC_SMF_P.Logic_table_lq[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S22>/Logic' */
  i = tmp_2;
  i = (int32_T)(((uint32_T)i << 1) + tmp_3);
  i = (int32_T)(((uint32_T)i << 1) + tmp_4);
  FOC_SMF_B->Logic_bj[0U] = FOC_SMF_P.Logic_table_m[(uint32_T)i];
  FOC_SMF_B->Logic_bj[1U] = FOC_SMF_P.Logic_table_m[(uint32_T)i + 8U];

  /* CombinatorialLogic: '<S23>/Logic' */
  i = tmp;
  i = (int32_T)(((uint32_T)i << 1) + tmp_0);
  i = (int32_T)(((uint32_T)i << 1) + tmp_1);
  FOC_SMF_B->Logic_a[0U] = FOC_SMF_P.Logic_table_g5[(uint32_T)i];
  FOC_SMF_B->Logic_a[1U] = FOC_SMF_P.Logic_table_g5[(uint32_T)i + 8U];

  /* Relay: '<S5>/LIMIT_WARN_Inverter_Warn_Temp' incorporates:
   *  Inport: '<Root>/bus_BSW_SCF'
   */
  for (i = 0; i < 9; i++) {
    bus_BSW_SMF = FOC_SMF_U->bus_BSW_SMF.InvTemp[i];
    if (bus_BSW_SMF >= FOC_SMF_P.LIMIT_Inverter_Warn_Temp) {
      FOC_SMF_DW->LIMIT_WARN_Inverter_Warn_Temp_M[i] = true;
    } else if (bus_BSW_SMF <= FOC_SMF_P.LIMIT_WARN_Inverter_Warn_Temp_O) {
      FOC_SMF_DW->LIMIT_WARN_Inverter_Warn_Temp_M[i] = false;
    }

    if (FOC_SMF_DW->LIMIT_WARN_Inverter_Warn_Temp_M[i]) {
      bus_BSW_SMF = FOC_SMF_P.LIMIT_WARN_Inverter_Warn_Temp_Y;
    } else {
      bus_BSW_SMF = FOC_SMF_P.LIMIT_WARN_Inverter_Warn_Temp_p;
    }

    FOC_SMF_B->LIMIT_WARN_Inverter_Warn_Temp[i] = bus_BSW_SMF;
  }

  /* End of Relay: '<S5>/LIMIT_WARN_Inverter_Warn_Temp' */

  /* MinMax: '<S5>/MinMax' */
  tmpForInput[0] = FOC_SMF_B->Logic_d[0];
  tmpForInput[1] = FOC_SMF_B->Logic_bw[0];
  tmpForInput[2] = FOC_SMF_B->Logic_m[0];
  tmpForInput[3] = FOC_SMF_B->Logic_dm[0];
  tmpForInput[4] = FOC_SMF_B->Logic_bj[0];
  tmpForInput[5] = FOC_SMF_B->Logic_a[0];
  tmp_s = tmpForInput[0];
  for (i = 0; i < 5; i++) {
    tmp_t = tmpForInput[i + 1];
    if ((int32_T)tmp_s < (int32_T)tmp_t) {
      tmp_s = true;
    }
  }

  /* MinMax: '<S5>/MinMax' */
  FOC_SMF_B->MinMax_a = tmp_s;

  /* MinMax: '<S5>/MinMax1' */
  tmpForInput[0] = FOC_SMF_B->Logic[0];
  tmpForInput[1] = FOC_SMF_B->Logic_f[0];
  tmpForInput[2] = FOC_SMF_B->Logic_e[0];
  tmpForInput[3] = FOC_SMF_B->Logic_fh[0];
  tmpForInput[4] = FOC_SMF_B->Logic_b[0];
  tmpForInput[5] = FOC_SMF_B->Logic_o[0];
  tmp_s = tmpForInput[0];
  for (i = 0; i < 5; i++) {
    tmp_t = tmpForInput[i + 1];
    if ((int32_T)tmp_s < (int32_T)tmp_t) {
      tmp_s = true;
    }
  }

  /* MinMax: '<S5>/MinMax1' */
  FOC_SMF_B->MinMax1_o = tmp_s;

  /* Logic: '<S5>/Logical Operator' */
  FOC_SMF_B->LogicalOperator = (FOC_SMF_B->MinMax_a || FOC_SMF_B->MinMax1_o);

  /* Update for UnitDelay: '<S8>/Delay Input1'
   *
   * Block description for '<S8>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_SMF_DW->DelayInput1_DSTATE = FOC_SMF_B->Compare_m3;

  /* Update for Memory: '<S12>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput = FOC_SMF_B->Logic[0];

  /* Update for Memory: '<S13>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_e = FOC_SMF_B->Logic_f[0];

  /* Update for Memory: '<S14>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_k = FOC_SMF_B->Logic_e[0];

  /* Update for Memory: '<S15>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_m = FOC_SMF_B->Logic_fh[0];

  /* Update for Memory: '<S16>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_f = FOC_SMF_B->Logic_b[0];

  /* Update for Memory: '<S17>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_j = FOC_SMF_B->Logic_o[0];

  /* Update for Memory: '<S18>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_i = FOC_SMF_B->Logic_d[0];

  /* Update for Memory: '<S19>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_p = FOC_SMF_B->Logic_bw[0];

  /* Update for Memory: '<S20>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_n = FOC_SMF_B->Logic_m[0];

  /* Update for Memory: '<S21>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_fj = FOC_SMF_B->Logic_dm[0];

  /* Update for Memory: '<S22>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_nt = FOC_SMF_B->Logic_bj[0];

  /* Update for Memory: '<S23>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_a = FOC_SMF_B->Logic_a[0];
}

/* Model initialize function */
void FOC_SMF_initialize(RT_MODEL_FOC_SMF_T *const FOC_SMF_M)
{
  B_FOC_SMF_T *FOC_SMF_B = FOC_SMF_M->blockIO;
  DW_FOC_SMF_T *FOC_SMF_DW = FOC_SMF_M->dwork;
  ExtY_FOC_SMF_T *FOC_SMF_Y = (ExtY_FOC_SMF_T *) FOC_SMF_M->outputs;
  ExtU_FOC_SMF_T *FOC_SMF_U = (ExtU_FOC_SMF_T *) FOC_SMF_M->inputs;

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) FOC_SMF_B), 0,
                sizeof(B_FOC_SMF_T));

  /* states (dwork) */
  (void) memset((void *)FOC_SMF_DW, 0,
                sizeof(DW_FOC_SMF_T));

  /* external inputs */
  (void)memset(FOC_SMF_U, 0, sizeof(ExtU_FOC_SMF_T));

  /* external outputs */
  FOC_SMF_Y->bus_SMF = FOC_SMF_rtZbus_SMF_t;

  /* InitializeConditions for UnitDelay: '<S8>/Delay Input1'
   *
   * Block description for '<S8>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FOC_SMF_DW->DelayInput1_DSTATE = FOC_SMF_P.DetectRisePositive_vinit;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput = FOC_SMF_P.OverTemp_Latching_1_initial_con;

  /* InitializeConditions for Memory: '<S13>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_e = FOC_SMF_P.OverTemp_Latching_2_initial_con;

  /* InitializeConditions for Memory: '<S14>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_k = FOC_SMF_P.OverTemp_Latching_3_initial_con;

  /* InitializeConditions for Memory: '<S15>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_m = FOC_SMF_P.OverTemp_Latching_4_initial_con;

  /* InitializeConditions for Memory: '<S16>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_f = FOC_SMF_P.OverTemp_Latching_5_initial_con;

  /* InitializeConditions for Memory: '<S17>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_j = FOC_SMF_P.OverTemp_Latching_6_initial_con;

  /* InitializeConditions for Memory: '<S18>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_i = FOC_SMF_P.OverTemp_Latching_1_initial_c_c;

  /* InitializeConditions for Memory: '<S19>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_p = FOC_SMF_P.OverTemp_Latching_2_initial_c_i;

  /* InitializeConditions for Memory: '<S20>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_n = FOC_SMF_P.OverTemp_Latching_3_initial_c_j;

  /* InitializeConditions for Memory: '<S21>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_fj =
    FOC_SMF_P.OverTemp_Latching_4_initial_c_e;

  /* InitializeConditions for Memory: '<S22>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_nt =
    FOC_SMF_P.OverTemp_Latching_5_initial_c_l;

  /* InitializeConditions for Memory: '<S23>/Memory' */
  FOC_SMF_DW->Memory_PreviousInput_a = FOC_SMF_P.OverTemp_Latching_6_initial_c_g;

  /* SystemInitialize for Chart: '<S1>/FOC_Statemachine' */
  FOC_SMF_Y->bus_SMF.SysStateAct = 0.0F;
  FOC_SMF_Y->bus_SMF.FOC_Mode = 0.0F;
  FOC_SMF_Y->bus_SMF.StateFOC = 49.0F;
  FOC_SMF_Y->bus_SMF.FOC_Enable_PWM = 0.0F;
  FOC_SMF_B->global_reset_errors = 0.0F;
  FOC_SMF_Y->bus_SMF.SPEED_CTRL_Enable = 0.0F;
  FOC_SMF_DW->is_active_c1_FOC_SMF = 0U;
  FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_NO_ACTIVE_CHILD;
  FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
}

/* Model terminate function */
void FOC_SMF_terminate(RT_MODEL_FOC_SMF_T *const FOC_SMF_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(FOC_SMF_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
