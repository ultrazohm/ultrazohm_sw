/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_SMF.c
 *
 * Code generated for Simulink model 'FOC_SMF'.
 *
 * Model version                  : 5.91
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Apr 17 13:36:23 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_SMF.h"
#include "rtwtypes.h"
#include "FOC_SMF_private.h"
#include <math.h>
#include "FOC_SMF_types.h"
#include <string.h>

/* Named constants for Chart: '<S1>/FOC_Statemachine' */
#define FOC_SMF_IN_CTRL_IDLE           ((uint8_T)1U)
#define FOC_SMF_IN_CTRL_INIT           ((uint8_T)2U)
#define FOC_SMF_IN_CTRL_RE_INIT        ((uint8_T)3U)
#define FOC_SMF_IN_ERROR_MODE          ((uint8_T)4U)
#define FOC_SMF_IN_FOC_IDLE            ((uint8_T)1U)
#define FOC_SMF_IN_FOC_If              ((uint8_T)2U)
#define FOC_SMF_IN_FOC_SPEED           ((uint8_T)3U)
#define FOC_SMF_IN_FOC_STANDBY         ((uint8_T)4U)
#define FOC_SMF_IN_FOC_TORQUE          ((uint8_T)5U)
#define FOC_SMF_IN_NO_ACTIVE_CHILD     ((uint8_T)0U)
#define FOC_SMF_IN_RUN_MODE            ((uint8_T)5U)
#define FOC_SMF_IN_SYS_INIT            ((uint8_T)6U)

const bus_SMF_t FOC_SMF_rtZbus_SMF_t = { 0U,/* SysStateAct */
  0U,                                  /* FOC_Mode */
  0U,                                  /* StateFOC */
  false,                               /* FOC_Enable_PWM */
  false,                               /* global_reset_errors */
  false,                               /* SPEED_CTRL_Enable */
  0.0F,                                /* MaxMotTemp */
  false,                               /* Collective_Over_Temp_Error */
  false                                /* Enable_If_Mode */
};

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void FOC_SMF_step(RT_MODEL_FOC_SMF_T *const FOC_SMF_M)
{
  B_FOC_SMF_T *FOC_SMF_B = FOC_SMF_M->blockIO;
  DW_FOC_SMF_T *FOC_SMF_DW = FOC_SMF_M->dwork;
  ExtU_FOC_SMF_T *FOC_SMF_U = (ExtU_FOC_SMF_T *) FOC_SMF_M->inputs;
  ExtY_FOC_SMF_T *FOC_SMF_Y = (ExtY_FOC_SMF_T *) FOC_SMF_M->outputs;
  real_T tmp_1;
  int32_T k;
  real32_T tmp;
  uint8_T tmp_0;

  /* MultiPortSwitch: '<S1>/DataSourceSwitch' incorporates:
   *  Constant: '<S1>/SELECT_DataSource'
   */
  if (FOC_SMF_P.SELECT_DataSource == 0) {
    /* MultiPortSwitch: '<S1>/DataSourceSwitch' */
    FOC_SMF_B->DataSourceSwitch = FOC_SMF_U->bus_BSW_SMF.EXT_State_Request;

    /* MultiPortSwitch: '<S1>/DataSourceSwitch1' */
    FOC_SMF_B->DataSourceSwitch1[0] = FOC_SMF_U->bus_BSW_SMF.EXT_Torque_Request;
    FOC_SMF_B->DataSourceSwitch1[1] = FOC_SMF_U->bus_BSW_SMF.EXT_Speed_Request;
  } else {
    /* MultiPortSwitch: '<S1>/DataSourceSwitch' incorporates:
     *  Constant: '<S1>/MANUAL_StateReq'
     */
    FOC_SMF_B->DataSourceSwitch = FOC_SMF_P.FOC_MANUAL_State_Request;

    /* MultiPortSwitch: '<S1>/DataSourceSwitch1' incorporates:
     *  Constant: '<S1>/Constant'
     *  Constant: '<S1>/OmegaRot2'
     */
    FOC_SMF_B->DataSourceSwitch1[0] = FOC_SMF_P.FOC_MANUAL_Torque_Request;
    FOC_SMF_B->DataSourceSwitch1[1] = FOC_SMF_P.SPEED_CTRL_MANUAL_n_RPM;
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
    FOC_SMF_B->State = FOC_SMF_P.enumState_SYS_INIT;
    FOC_SMF_B->FOC_Mode = 1U;
  } else {
    switch (FOC_SMF_DW->is_c1_FOC_SMF) {
     case FOC_SMF_IN_CTRL_IDLE:
      FOC_SMF_B->State = FOC_SMF_P.enumState_CTRL_IDLE;
      FOC_SMF_B->FOC_Mode = 1U;
      if (FOC_SMF_U->bus_FCF.FCF_Error) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_B->State = FOC_SMF_P.enumState_ERROR_MODE;
      } else if (FOC_SMF_B->DataSourceSwitch == FOC_SMF_P.enumState_RUN_MODE) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_RUN_MODE;
        FOC_SMF_B->FOC_Mode = 3U;
        FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_IDLE;
        FOC_SMF_B->State = FOC_SMF_P.enumState_RUN_MODE;
        FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_IDLE;
        FOC_SMF_B->FOC_Enable_PWM = false;
      }
      break;

     case FOC_SMF_IN_CTRL_INIT:
      FOC_SMF_B->State = FOC_SMF_P.enumState_CTRL_INIT;
      if (FOC_SMF_U->bus_FCF.FCF_Error) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_B->State = FOC_SMF_P.enumState_ERROR_MODE;
      } else if (FOC_SMF_B->DataSourceSwitch == FOC_SMF_P.enumState_CTRL_IDLE) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_CTRL_IDLE;
        FOC_SMF_B->State = FOC_SMF_P.enumState_CTRL_IDLE;
        FOC_SMF_B->FOC_Mode = 1U;
      }
      break;

     case FOC_SMF_IN_CTRL_RE_INIT:
      FOC_SMF_B->State = FOC_SMF_P.enumState_CTRL_RE_INIT;
      if ((FOC_SMF_B->DataSourceSwitch == FOC_SMF_P.enumState_CTRL_IDLE) &&
          (!FOC_SMF_U->bus_FCF.FCF_Error)) {
        FOC_SMF_Y->bus_SMF.global_reset_errors = false;
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_SYS_INIT;
        FOC_SMF_B->State = FOC_SMF_P.enumState_SYS_INIT;
        FOC_SMF_B->FOC_Mode = 1U;
      } else if (FOC_SMF_U->bus_FCF.FCF_Error) {
        FOC_SMF_Y->bus_SMF.global_reset_errors = false;
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_B->State = FOC_SMF_P.enumState_ERROR_MODE;
      }
      break;

     case FOC_SMF_IN_ERROR_MODE:
      FOC_SMF_B->State = FOC_SMF_P.enumState_ERROR_MODE;
      if (FOC_SMF_B->DataSourceSwitch == FOC_SMF_P.enumState_CTRL_IDLE) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_CTRL_RE_INIT;
        FOC_SMF_B->State = FOC_SMF_P.enumState_CTRL_RE_INIT;
        FOC_SMF_Y->bus_SMF.global_reset_errors = true;
      }
      break;

     case FOC_SMF_IN_RUN_MODE:
      FOC_SMF_B->FOC_Mode = 3U;
      if (FOC_SMF_U->bus_FCF.FCF_Error) {
        switch (FOC_SMF_DW->is_RUN_MODE) {
         case FOC_SMF_IN_FOC_If:
          FOC_SMF_Y->bus_SMF.Enable_If_Mode = false;
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
          break;

         case FOC_SMF_IN_FOC_SPEED:
          FOC_SMF_Y->bus_SMF.SPEED_CTRL_Enable = false;
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
          break;

         default:
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
          break;
        }

        FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_OFF;
        FOC_SMF_B->FOC_Enable_PWM = false;
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_B->State = FOC_SMF_P.enumState_ERROR_MODE;
      } else if (FOC_SMF_B->DataSourceSwitch == FOC_SMF_P.enumState_CTRL_IDLE) {
        switch (FOC_SMF_DW->is_RUN_MODE) {
         case FOC_SMF_IN_FOC_If:
          FOC_SMF_Y->bus_SMF.Enable_If_Mode = false;
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
          break;

         case FOC_SMF_IN_FOC_SPEED:
          FOC_SMF_Y->bus_SMF.SPEED_CTRL_Enable = false;
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
          break;

         default:
          FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_NO_ACTIVE_CHILD;
          break;
        }

        FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_OFF;
        FOC_SMF_B->FOC_Enable_PWM = false;
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_CTRL_IDLE;
        FOC_SMF_B->State = FOC_SMF_P.enumState_CTRL_IDLE;
        FOC_SMF_B->FOC_Mode = 1U;
      } else {
        switch (FOC_SMF_DW->is_RUN_MODE) {
         case FOC_SMF_IN_FOC_IDLE:
          FOC_SMF_B->State = FOC_SMF_P.enumState_RUN_MODE;
          if ((FOC_SMF_B->DataSourceSwitch1[0] == 0.0F) &&
              (FOC_SMF_B->DataSourceSwitch1[1] == 0.0F)) {
            FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_STANDBY;
            FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_STANDBY;
            FOC_SMF_B->FOC_Enable_PWM = true;
          }
          break;

         case FOC_SMF_IN_FOC_If:
          tmp_1 = rt_roundd_snf(FOC_SMF_P.enumState_IF);
          if (tmp_1 < 256.0) {
            if (tmp_1 >= 0.0) {
              tmp_0 = (uint8_T)tmp_1;
            } else {
              tmp_0 = 0U;
            }
          } else {
            tmp_0 = MAX_uint8_T;
          }

          FOC_SMF_B->State = tmp_0;
          break;

         case FOC_SMF_IN_FOC_SPEED:
          FOC_SMF_B->State = FOC_SMF_P.enumState_SPEED_MODE;
          break;

         case FOC_SMF_IN_FOC_STANDBY:
          if (FOC_SMF_B->DataSourceSwitch == FOC_SMF_P.enumState_TORQUE_MODE) {
            FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_TORQUE;
            FOC_SMF_B->State = FOC_SMF_P.enumState_TORQUE_MODE;
            FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_TORQUE;
          } else if (FOC_SMF_B->DataSourceSwitch ==
                     FOC_SMF_P.enumState_SPEED_MODE) {
            FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_SPEED;
            FOC_SMF_B->State = FOC_SMF_P.enumState_SPEED_MODE;
            FOC_SMF_Y->bus_SMF.StateFOC = FOC_SMF_P.enumState_FOC_SPEED;
            FOC_SMF_Y->bus_SMF.SPEED_CTRL_Enable = true;
          } else if (FOC_SMF_B->DataSourceSwitch == FOC_SMF_P.enumState_IF) {
            FOC_SMF_DW->is_RUN_MODE = FOC_SMF_IN_FOC_If;
            tmp_1 = rt_roundd_snf(FOC_SMF_P.enumState_IF);
            if (tmp_1 < 256.0) {
              if (tmp_1 >= 0.0) {
                tmp_0 = (uint8_T)tmp_1;
              } else {
                tmp_0 = 0U;
              }
            } else {
              tmp_0 = MAX_uint8_T;
            }

            FOC_SMF_B->State = tmp_0;
            tmp_1 = rt_roundd_snf(FOC_SMF_P.enumState_FOC_IF);
            if (tmp_1 < 256.0) {
              if (tmp_1 >= 0.0) {
                tmp_0 = (uint8_T)tmp_1;
              } else {
                tmp_0 = 0U;
              }
            } else {
              tmp_0 = MAX_uint8_T;
            }

            FOC_SMF_Y->bus_SMF.StateFOC = tmp_0;
            FOC_SMF_Y->bus_SMF.Enable_If_Mode = true;
          }
          break;

         default:
          /* case IN_FOC_TORQUE: */
          FOC_SMF_B->State = FOC_SMF_P.enumState_TORQUE_MODE;
          break;
        }
      }
      break;

     default:
      /* case IN_SYS_INIT: */
      FOC_SMF_B->State = FOC_SMF_P.enumState_SYS_INIT;
      FOC_SMF_B->FOC_Mode = 1U;
      if (FOC_SMF_U->bus_FCF.FCF_Error) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_ERROR_MODE;
        FOC_SMF_B->State = FOC_SMF_P.enumState_ERROR_MODE;
      } else if ((FOC_SMF_B->DataSourceSwitch == FOC_SMF_P.enumState_CTRL_IDLE) &&
                 FOC_SMF_B->KL15_PG_SourceSwitch) {
        FOC_SMF_DW->is_c1_FOC_SMF = FOC_SMF_IN_CTRL_INIT;
        FOC_SMF_B->State = FOC_SMF_P.enumState_CTRL_INIT;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/FOC_Statemachine' */

  /* MinMax: '<S4>/MinMax1' incorporates:
   *  Inport: '<Root>/bus_BSW_SMF'
   */
  tmp = FOC_SMF_U->bus_BSW_SMF.MotTemp[0];
  for (k = 0; k < 5; k++) {
    tmp = fmaxf(tmp, FOC_SMF_U->bus_BSW_SMF.MotTemp[k + 1]);
  }

  FOC_SMF_Y->bus_SMF.MaxMotTemp = tmp;

  /* End of MinMax: '<S4>/MinMax1' */

  /* BusCreator: '<S1>/Bus Creator' incorporates:
   *  Outport: '<Root>/bus_SMF'
   */
  FOC_SMF_Y->bus_SMF.SysStateAct = FOC_SMF_B->State;
  FOC_SMF_Y->bus_SMF.FOC_Mode = FOC_SMF_B->FOC_Mode;
  FOC_SMF_Y->bus_SMF.FOC_Enable_PWM = FOC_SMF_B->FOC_Enable_PWM;
  FOC_SMF_Y->bus_SMF.Collective_Over_Temp_Error = false;

  /* MinMax: '<S4>/MinMax' incorporates:
   *  Inport: '<Root>/bus_BSW_SMF'
   */
  tmp = FOC_SMF_U->bus_BSW_SMF.InvTemp[0];
  for (k = 0; k < 8; k++) {
    tmp = fmaxf(tmp, FOC_SMF_U->bus_BSW_SMF.InvTemp[k + 1]);
  }

  /* MinMax: '<S4>/MinMax' */
  FOC_SMF_B->MinMax = tmp;
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

  /* SystemInitialize for Chart: '<S1>/FOC_Statemachine' */
  FOC_SMF_B->State = 0U;
  FOC_SMF_B->FOC_Mode = 0U;
  FOC_SMF_Y->bus_SMF.StateFOC = 49U;
  FOC_SMF_B->FOC_Enable_PWM = false;
  FOC_SMF_Y->bus_SMF.global_reset_errors = false;
  FOC_SMF_Y->bus_SMF.SPEED_CTRL_Enable = false;
  FOC_SMF_Y->bus_SMF.Enable_If_Mode = false;
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
