/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FOC_Statemachine.c
 *
 * Code generated for Simulink model 'FOC_Statemachine'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Aug 22 14:13:05 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FOC_Statemachine.h"
#include "rtwtypes.h"
#include <string.h>

/* Named constants for Chart: '<Root>/FOC_Statemachine' */
#define FOC_Statemac_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define FOC_Statemachine_IN_CTRL_IDLE  ((uint8_T)1U)
#define FOC_Statemachine_IN_CTRL_INIT  ((uint8_T)2U)
#define FOC_Statemachine_IN_ERROR_MODE ((uint8_T)3U)
#define FOC_Statemachine_IN_FOC_IDLE   ((uint8_T)1U)
#define FOC_Statemachine_IN_FOC_SPEED  ((uint8_T)2U)
#define FOC_Statemachine_IN_FOC_STANDBY ((uint8_T)3U)
#define FOC_Statemachine_IN_FOC_TORQUE ((uint8_T)4U)
#define FOC_Statemachine_IN_RUN_MODE   ((uint8_T)4U)
#define FOC_Statemachine_IN_SYS_INIT   ((uint8_T)5U)

/* Model step function */
void FOC_Statemachine_step(RT_MODEL_FOC_Statemachine_T *const FOC_Statemachine_M)
{
  DW_FOC_Statemachine_T *FOC_Statemachine_DW = FOC_Statemachine_M->dwork;
  ExtU_FOC_Statemachine_T *FOC_Statemachine_U = (ExtU_FOC_Statemachine_T *)
    FOC_Statemachine_M->inputs;
  ExtY_FOC_Statemachine_T *FOC_Statemachine_Y = (ExtY_FOC_Statemachine_T *)
    FOC_Statemachine_M->outputs;

  /* Chart: '<Root>/FOC_Statemachine' incorporates:
   *  Inport: '<Root>/SpeedReq'
   *  Inport: '<Root>/StateReq'
   *  Inport: '<Root>/TorqueReq'
   *  Inport: '<Root>/error'
   */
  if (FOC_Statemachine_DW->is_active_c1_FOC_Statemachine == 0U) {
    FOC_Statemachine_DW->is_active_c1_FOC_Statemachine = 1U;
    FOC_Statemachine_DW->is_c1_FOC_Statemachine = FOC_Statemachine_IN_SYS_INIT;

    /* Outport: '<Root>/State' */
    FOC_Statemachine_Y->State = 2.0;

    /* Outport: '<Root>/FOC_Mode' */
    FOC_Statemachine_Y->FOC_Mode = 1.0;

    /* Outport: '<Root>/global_reset_errors' */
    FOC_Statemachine_Y->global_reset_errors = 1.0;
  } else {
    switch (FOC_Statemachine_DW->is_c1_FOC_Statemachine) {
     case FOC_Statemachine_IN_CTRL_IDLE:
      /* Outport: '<Root>/State' */
      FOC_Statemachine_Y->State = 20.0;

      /* Outport: '<Root>/FOC_Mode' */
      FOC_Statemachine_Y->FOC_Mode = 1.0;
      if (FOC_Statemachine_U->FastCtrl_Error) {
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_ERROR_MODE;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 128.0;
      } else if (FOC_Statemachine_U->StateReq == 40.0) {
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_RUN_MODE;

        /* Outport: '<Root>/FOC_Mode' */
        FOC_Statemachine_Y->FOC_Mode = 3.0;
        FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemachine_IN_FOC_IDLE;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 40.0;

        /* Outport: '<Root>/StateFOC' */
        FOC_Statemachine_Y->StateFOC = 41.0;

        /* Outport: '<Root>/FOC_Enable_PWM' */
        FOC_Statemachine_Y->FOC_Enable_PWM = 0.0;
      }
      break;

     case FOC_Statemachine_IN_CTRL_INIT:
      /* Outport: '<Root>/State' */
      FOC_Statemachine_Y->State = 10.0;
      if (FOC_Statemachine_U->FastCtrl_Error) {
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_ERROR_MODE;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 128.0;
      } else if (FOC_Statemachine_U->StateReq == 20.0) {
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_CTRL_IDLE;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 20.0;

        /* Outport: '<Root>/FOC_Mode' */
        FOC_Statemachine_Y->FOC_Mode = 1.0;
      }
      break;

     case FOC_Statemachine_IN_ERROR_MODE:
      /* Outport: '<Root>/State' */
      FOC_Statemachine_Y->State = 128.0;
      if (FOC_Statemachine_U->StateReq == 20.0) {
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_SYS_INIT;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 2.0;

        /* Outport: '<Root>/FOC_Mode' */
        FOC_Statemachine_Y->FOC_Mode = 1.0;

        /* Outport: '<Root>/global_reset_errors' */
        FOC_Statemachine_Y->global_reset_errors = 1.0;
      }
      break;

     case FOC_Statemachine_IN_RUN_MODE:
      /* Outport: '<Root>/FOC_Mode' */
      FOC_Statemachine_Y->FOC_Mode = 3.0;
      if (FOC_Statemachine_U->FastCtrl_Error) {
        if (FOC_Statemachine_DW->is_RUN_MODE == FOC_Statemachine_IN_FOC_SPEED) {
          /* Outport: '<Root>/SPEED_CTRL_Enable' */
          FOC_Statemachine_Y->SPEED_CTRL_Enable = 0.0;
          FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemac_IN_NO_ACTIVE_CHILD;
        } else {
          FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemac_IN_NO_ACTIVE_CHILD;
        }

        /* Outport: '<Root>/StateFOC' */
        FOC_Statemachine_Y->StateFOC = 49.0;

        /* Outport: '<Root>/FOC_Enable_PWM' */
        FOC_Statemachine_Y->FOC_Enable_PWM = 0.0;
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_ERROR_MODE;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 128.0;
      } else if (FOC_Statemachine_U->StateReq == 20.0) {
        if (FOC_Statemachine_DW->is_RUN_MODE == FOC_Statemachine_IN_FOC_SPEED) {
          /* Outport: '<Root>/SPEED_CTRL_Enable' */
          FOC_Statemachine_Y->SPEED_CTRL_Enable = 0.0;
          FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemac_IN_NO_ACTIVE_CHILD;
        } else {
          FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemac_IN_NO_ACTIVE_CHILD;
        }

        /* Outport: '<Root>/StateFOC' */
        FOC_Statemachine_Y->StateFOC = 49.0;

        /* Outport: '<Root>/FOC_Enable_PWM' */
        FOC_Statemachine_Y->FOC_Enable_PWM = 0.0;
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_CTRL_IDLE;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 20.0;

        /* Outport: '<Root>/FOC_Mode' */
        FOC_Statemachine_Y->FOC_Mode = 1.0;
      } else {
        switch (FOC_Statemachine_DW->is_RUN_MODE) {
         case FOC_Statemachine_IN_FOC_IDLE:
          /* Outport: '<Root>/State' */
          FOC_Statemachine_Y->State = 40.0;
          if ((FOC_Statemachine_U->TorqueReq == 0.0) &&
              (FOC_Statemachine_U->SpeedReq == 0.0)) {
            FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemachine_IN_FOC_STANDBY;

            /* Outport: '<Root>/StateFOC' */
            FOC_Statemachine_Y->StateFOC = 42.0;

            /* Outport: '<Root>/FOC_Enable_PWM' */
            FOC_Statemachine_Y->FOC_Enable_PWM = 1.0;
          }
          break;

         case FOC_Statemachine_IN_FOC_SPEED:
          /* Outport: '<Root>/State' */
          FOC_Statemachine_Y->State = 42.0;
          break;

         case FOC_Statemachine_IN_FOC_STANDBY:
          if (FOC_Statemachine_U->StateReq == 41.0) {
            FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemachine_IN_FOC_TORQUE;

            /* Outport: '<Root>/State' */
            FOC_Statemachine_Y->State = 41.0;

            /* Outport: '<Root>/StateFOC' */
            FOC_Statemachine_Y->StateFOC = 43.0;
          } else if (FOC_Statemachine_U->StateReq == 42.0) {
            FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemachine_IN_FOC_SPEED;

            /* Outport: '<Root>/State' */
            FOC_Statemachine_Y->State = 42.0;

            /* Outport: '<Root>/StateFOC' */
            FOC_Statemachine_Y->StateFOC = 46.0;

            /* Outport: '<Root>/SPEED_CTRL_Enable' */
            FOC_Statemachine_Y->SPEED_CTRL_Enable = 1.0;
          }
          break;

         default:
          /* Outport: '<Root>/State' */
          /* case IN_FOC_TORQUE: */
          FOC_Statemachine_Y->State = 41.0;
          break;
        }
      }
      break;

     default:
      /* Outport: '<Root>/State' */
      /* case IN_SYS_INIT: */
      FOC_Statemachine_Y->State = 2.0;

      /* Outport: '<Root>/FOC_Mode' */
      FOC_Statemachine_Y->FOC_Mode = 1.0;
      if (FOC_Statemachine_U->FastCtrl_Error) {
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_ERROR_MODE;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 128.0;
      } else if (FOC_Statemachine_U->StateReq == 20.0) {
        FOC_Statemachine_DW->is_c1_FOC_Statemachine =
          FOC_Statemachine_IN_CTRL_INIT;

        /* Outport: '<Root>/State' */
        FOC_Statemachine_Y->State = 10.0;

        /* Outport: '<Root>/global_reset_errors' */
        FOC_Statemachine_Y->global_reset_errors = 0.0;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/FOC_Statemachine' */
}

/* Model initialize function */
void FOC_Statemachine_initialize(RT_MODEL_FOC_Statemachine_T *const
  FOC_Statemachine_M)
{
  DW_FOC_Statemachine_T *FOC_Statemachine_DW = FOC_Statemachine_M->dwork;
  ExtY_FOC_Statemachine_T *FOC_Statemachine_Y = (ExtY_FOC_Statemachine_T *)
    FOC_Statemachine_M->outputs;
  ExtU_FOC_Statemachine_T *FOC_Statemachine_U = (ExtU_FOC_Statemachine_T *)
    FOC_Statemachine_M->inputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)FOC_Statemachine_DW, 0,
                sizeof(DW_FOC_Statemachine_T));

  /* external inputs */
  (void)memset(FOC_Statemachine_U, 0, sizeof(ExtU_FOC_Statemachine_T));

  /* external outputs */
  (void)memset(FOC_Statemachine_Y, 0, sizeof(ExtY_FOC_Statemachine_T));

  /* SystemInitialize for Chart: '<Root>/FOC_Statemachine' */
  FOC_Statemachine_DW->is_RUN_MODE = FOC_Statemac_IN_NO_ACTIVE_CHILD;
  FOC_Statemachine_DW->is_active_c1_FOC_Statemachine = 0U;
  FOC_Statemachine_DW->is_c1_FOC_Statemachine = FOC_Statemac_IN_NO_ACTIVE_CHILD;

  /* SystemInitialize for Outport: '<Root>/State' incorporates:
   *  Chart: '<Root>/FOC_Statemachine'
   */
  FOC_Statemachine_Y->State = 0.0;

  /* SystemInitialize for Outport: '<Root>/FOC_Mode' incorporates:
   *  Chart: '<Root>/FOC_Statemachine'
   */
  FOC_Statemachine_Y->FOC_Mode = 0.0;

  /* SystemInitialize for Outport: '<Root>/StateFOC' incorporates:
   *  Chart: '<Root>/FOC_Statemachine'
   */
  FOC_Statemachine_Y->StateFOC = 49.0;

  /* SystemInitialize for Outport: '<Root>/FOC_Enable_PWM' incorporates:
   *  Chart: '<Root>/FOC_Statemachine'
   */
  FOC_Statemachine_Y->FOC_Enable_PWM = 0.0;

  /* SystemInitialize for Outport: '<Root>/global_reset_errors' incorporates:
   *  Chart: '<Root>/FOC_Statemachine'
   */
  FOC_Statemachine_Y->global_reset_errors = 0.0;

  /* SystemInitialize for Outport: '<Root>/SPEED_CTRL_Enable' incorporates:
   *  Chart: '<Root>/FOC_Statemachine'
   */
  FOC_Statemachine_Y->SPEED_CTRL_Enable = 0.0;
}

/* Model terminate function */
void FOC_Statemachine_terminate(RT_MODEL_FOC_Statemachine_T *const
  FOC_Statemachine_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(FOC_Statemachine_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
