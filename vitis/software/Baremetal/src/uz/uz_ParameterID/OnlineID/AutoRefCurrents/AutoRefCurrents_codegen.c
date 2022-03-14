/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ControlReference.c
 *
 * Code generated for Simulink model 'ControlReference'.
 *
 * Model version                  : 2.410
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Jan 13 10:19:48 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: All passed
 */

#include "../../../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U

#include "AutoRefCurrents_codegen.h"

/* Named constants for Chart: '<Root>/AutoRefCurrents' */
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_countstate                  ((uint8_T)1U)
#define IN_stepstate                   ((uint8_T)2U)
#define IN_superstate                  ((uint8_T)1U)
#define IN_waitState                   ((uint8_T)2U)

/* Model step function */
void AutoRefCurrents_step(RT_MODEL_AutoRefCurrents_t *const rtAutoRefCurrents_M)
{
  DW_AutoRefCurrents_t *rtAutoRefCurrents_DW = rtAutoRefCurrents_M->dwork;
  ExtU_AutoRefCurrents_t *rtAutoRefCurrents_U = (ExtU_AutoRefCurrents_t *)
    rtAutoRefCurrents_M->inputs;
  ExtY_AutoRefCurrents_t *rtAutoRefCurrents_Y = (ExtY_AutoRefCurrents_t *)
    rtAutoRefCurrents_M->outputs;
  real32_T idcount_tmp;
  real32_T tmp;

  /* Chart: '<Root>/AutoRefCurrents' incorporates:
   *  Inport: '<Root>/ActualValues'
   *  Inport: '<Root>/AutoRefCurrentsConfig'
   *  Inport: '<Root>/ControlFlags'
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/i_dq_ref'
   */
  /* Gateway: AutoRefCurrents */
  /* During: AutoRefCurrents */
  if (rtAutoRefCurrents_DW->is_active_c10_AutoRefCurrents == 0U) {
    /* Entry: AutoRefCurrents */
    rtAutoRefCurrents_DW->is_active_c10_AutoRefCurrents = 1U;

    /* Entry Internal: AutoRefCurrents */
    /* Transition: '<S1>:30' */
    rtAutoRefCurrents_DW->is_c10_AutoRefCurrents = IN_waitState;

    /* Entry 'waitState': '<S1>:29' */
    /* do nothing */
    /* wait for start */
  } else if (rtAutoRefCurrents_DW->is_c10_AutoRefCurrents == IN_superstate) {
    /* During 'superstate': '<S1>:20' */
    /* '<S1>:32:1' sf_internal_predicateOutput = AutoRefCurrentsConfig.enableCRS==0 ||.... */
    /* '<S1>:32:2'  AutoRefCurrentsConfig.Reset == 1 ||.... */
    /* '<S1>:32:3' GlobalConfig.Reset==1; */
    /* . */
    /* . */
    if ((!rtAutoRefCurrents_U->AutoRefCurrentsConfig.enableCRS) ||
        rtAutoRefCurrents_U->AutoRefCurrentsConfig.Reset ||
        rtAutoRefCurrents_U->GlobalConfig_out.Reset) {
      /* Transition: '<S1>:32' */
      /* '<S1>:32:4' i_dq_ref.d=single(0); */
      rtAutoRefCurrents_Y->i_dq_ref.d = 0.0F;

      /* '<S1>:32:4' i_dq_ref.q=single(0) */
      rtAutoRefCurrents_Y->i_dq_ref.q = 0.0F;

      /* Exit Internal 'superstate': '<S1>:20' */
      rtAutoRefCurrents_DW->is_superstate = IN_NO_ACTIVE_CHILD;
      rtAutoRefCurrents_DW->is_c10_AutoRefCurrents = IN_waitState;

      /* Entry 'waitState': '<S1>:29' */
      /* do nothing */
      /* wait for start */
    } else if (rtAutoRefCurrents_DW->is_superstate == IN_countstate) {
      /* During 'countstate': '<S1>:22' */
      /* '<S1>:23:1' sf_internal_predicateOutput = counter==(2.0/GlobalConfig.sampleTimeISR); */
      if (2.0F / rtAutoRefCurrents_U->GlobalConfig_out.sampleTimeISR ==
          rtAutoRefCurrents_DW->counter) {
        /* Transition: '<S1>:23' */
        rtAutoRefCurrents_DW->is_superstate = IN_stepstate;

        /* Entry 'stepstate': '<S1>:26' */
        /* '<S1>:26:3' if(ActualValues.omega_m>0) */
        if (rtAutoRefCurrents_U->ActualValues.omega_m > 0.0F) {
          /* '<S1>:26:4' imax=abs(AutoRefCurrentsConfig.max_current); */
          rtAutoRefCurrents_DW->imax = fabsf
            (rtAutoRefCurrents_U->AutoRefCurrentsConfig.max_current);
        }

        /* '<S1>:26:6' if(ActualValues.omega_m<0) */
        if (rtAutoRefCurrents_U->ActualValues.omega_m < 0.0F) {
          /* '<S1>:26:7' imax=abs(AutoRefCurrentsConfig.max_current)*-1; */
          rtAutoRefCurrents_DW->imax = -fabsf
            (rtAutoRefCurrents_U->AutoRefCurrentsConfig.max_current);
        }

        /* '<S1>:26:9' if((i_dq_ref.d*i_dq_ref.d+(imax*iqcount/AutoRefCurrentsConfig.iq_points)^2)^0.5<abs(imax)) */
        idcount_tmp = rtAutoRefCurrents_DW->imax * rtAutoRefCurrents_DW->iqcount
          / rtAutoRefCurrents_U->AutoRefCurrentsConfig.iq_points;
        if (sqrtf(rtAutoRefCurrents_Y->i_dq_ref.d *
                  rtAutoRefCurrents_Y->i_dq_ref.d + idcount_tmp * idcount_tmp) <
            fabsf(rtAutoRefCurrents_DW->imax)) {
          /* '<S1>:26:10' i_dq_ref.q=imax*iqcount/AutoRefCurrentsConfig.iq_points; */
          rtAutoRefCurrents_Y->i_dq_ref.q = idcount_tmp;
        } else {
          /* '<S1>:26:11' else */
          /* '<S1>:26:12' iqcount=single(1); */
          rtAutoRefCurrents_DW->iqcount = 1.0F;

          /* '<S1>:26:13' i_dq_ref.q=imax*iqcount/AutoRefCurrentsConfig.iq_points; */
          rtAutoRefCurrents_Y->i_dq_ref.q = rtAutoRefCurrents_DW->imax *
            rtAutoRefCurrents_DW->iqcount /
            rtAutoRefCurrents_U->AutoRefCurrentsConfig.iq_points;
        }

        /* '<S1>:26:15' if((i_dq_ref.q*i_dq_ref.q+(imax*idcount/AutoRefCurrentsConfig.id_points)^2)^0.5<abs(imax)) */
        idcount_tmp = rtAutoRefCurrents_DW->imax * rtAutoRefCurrents_DW->idcount
          / rtAutoRefCurrents_U->AutoRefCurrentsConfig.id_points;
        tmp = fabsf(rtAutoRefCurrents_DW->imax);
        if (sqrtf(rtAutoRefCurrents_Y->i_dq_ref.q *
                  rtAutoRefCurrents_Y->i_dq_ref.q + idcount_tmp * idcount_tmp) <
            tmp) {
          /* '<S1>:26:16' i_dq_ref.d=-1*abs(imax)*idcount/AutoRefCurrentsConfig.id_points; */
          rtAutoRefCurrents_Y->i_dq_ref.d = -tmp * rtAutoRefCurrents_DW->idcount
            / rtAutoRefCurrents_U->AutoRefCurrentsConfig.id_points;
        } else {
          /* '<S1>:26:17' else */
          /* '<S1>:26:18' idcount=single(-AutoRefCurrentsConfig.id_points/3); */
          rtAutoRefCurrents_DW->idcount =
            -rtAutoRefCurrents_U->AutoRefCurrentsConfig.id_points / 3.0F;

          /* '<S1>:26:19' i_dq_ref.d=-1*abs(imax)*idcount/AutoRefCurrentsConfig.id_points; */
          rtAutoRefCurrents_Y->i_dq_ref.d = -fabsf(rtAutoRefCurrents_DW->imax) *
            rtAutoRefCurrents_DW->idcount /
            rtAutoRefCurrents_U->AutoRefCurrentsConfig.id_points;
        }

        /* '<S1>:26:21' counter=single(0); */
        rtAutoRefCurrents_DW->counter = 0.0F;
      } else {
        /* '<S1>:22:14' counter=counter+1; */
        rtAutoRefCurrents_DW->counter++;
      }

      /* During 'stepstate': '<S1>:26' */
      /* '<S1>:24:1' sf_internal_predicateOutput = counter==0; */
    } else if (rtAutoRefCurrents_DW->counter == 0.0F) {
      /* Transition: '<S1>:24' */
      rtAutoRefCurrents_DW->is_superstate = IN_countstate;

      /* Entry 'countstate': '<S1>:22' */
      /* '<S1>:22:3' if(iqcount<AutoRefCurrentsConfig.iq_points) */
      if (rtAutoRefCurrents_DW->iqcount <
          rtAutoRefCurrents_U->AutoRefCurrentsConfig.iq_points) {
        /* '<S1>:22:4' iqcount=iqcount+1; */
        rtAutoRefCurrents_DW->iqcount++;
      } else {
        /* '<S1>:22:5' else */
        /* '<S1>:22:6' iqcount=single(0); */
        rtAutoRefCurrents_DW->iqcount = 0.0F;
      }

      /* '<S1>:22:8' if(idcount<AutoRefCurrentsConfig.id_points) */
      if (rtAutoRefCurrents_DW->idcount <
          rtAutoRefCurrents_U->AutoRefCurrentsConfig.id_points) {
        /* '<S1>:22:9' idcount=idcount+1; */
        rtAutoRefCurrents_DW->idcount++;
      } else {
        /* '<S1>:22:10' else */
        /* '<S1>:22:11' idcount=single(-AutoRefCurrentsConfig.id_points/3); */
        rtAutoRefCurrents_DW->idcount =
          -rtAutoRefCurrents_U->AutoRefCurrentsConfig.id_points / 3.0F;
      }
    }

    /* During 'waitState': '<S1>:29' */
    /* '<S1>:31:1' sf_internal_predicateOutput = AutoRefCurrentsConfig.enableCRS==1 &&.... */
    /* '<S1>:31:2' AutoRefCurrentsConfig.Reset==0 &&.... */
    /* '<S1>:31:3'  GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1&& .... */
    /* '<S1>:31:4' ControlFlags.finished_all_Offline_states==1; */
    /* . */
    /* . */
    /* . */
  } else if (rtAutoRefCurrents_U->AutoRefCurrentsConfig.enableCRS &&
             (!rtAutoRefCurrents_U->AutoRefCurrentsConfig.Reset) &&
             (!rtAutoRefCurrents_U->GlobalConfig_out.Reset) &&
             rtAutoRefCurrents_U->GlobalConfig_out.ACCEPT &&
             rtAutoRefCurrents_U->ControlFlags.finished_all_Offline_states) {
    /* Transition: '<S1>:31' */
    rtAutoRefCurrents_DW->is_c10_AutoRefCurrents = IN_superstate;

    /* Entry 'superstate': '<S1>:20' */
    /* '<S1>:20:3' counter=single(19998); */
    rtAutoRefCurrents_DW->counter = 19998.0F;

    /* counter=single(17498); */
    /* '<S1>:20:5' iqcount=single(0); */
    rtAutoRefCurrents_DW->iqcount = 0.0F;

    /* '<S1>:20:6' idcount=single(-AutoRefCurrentsConfig.id_points/3); */
    idcount_tmp = -rtAutoRefCurrents_U->AutoRefCurrentsConfig.id_points / 3.0F;
    rtAutoRefCurrents_DW->idcount = idcount_tmp;

    /* '<S1>:20:7' i_dq_ref.d=single(0); */
    rtAutoRefCurrents_Y->i_dq_ref.d = 0.0F;

    /* '<S1>:20:8' i_dq_ref.q=single(0); */
    rtAutoRefCurrents_Y->i_dq_ref.q = 0.0F;

    /* '<S1>:20:9' imax=single(0); */
    rtAutoRefCurrents_DW->imax = 0.0F;

    /* Entry Internal 'superstate': '<S1>:20' */
    /* Transition: '<S1>:21' */
    rtAutoRefCurrents_DW->is_superstate = IN_countstate;

    /* Entry 'countstate': '<S1>:22' */
    /* '<S1>:22:3' if(iqcount<AutoRefCurrentsConfig.iq_points) */
    if (rtAutoRefCurrents_DW->iqcount <
        rtAutoRefCurrents_U->AutoRefCurrentsConfig.iq_points) {
      /* '<S1>:22:4' iqcount=iqcount+1; */
      rtAutoRefCurrents_DW->iqcount++;
    } else {
      /* '<S1>:22:5' else */
      /* '<S1>:22:6' iqcount=single(0); */
      rtAutoRefCurrents_DW->iqcount = 0.0F;
    }

    /* '<S1>:22:8' if(idcount<AutoRefCurrentsConfig.id_points) */
    if (rtAutoRefCurrents_DW->idcount <
        rtAutoRefCurrents_U->AutoRefCurrentsConfig.id_points) {
      /* '<S1>:22:9' idcount=idcount+1; */
      rtAutoRefCurrents_DW->idcount++;
    } else {
      /* '<S1>:22:10' else */
      /* '<S1>:22:11' idcount=single(-AutoRefCurrentsConfig.id_points/3); */
      rtAutoRefCurrents_DW->idcount = idcount_tmp;
    }
  }

  /* End of Chart: '<Root>/AutoRefCurrents' */
}

/* Model initialize function */
void AutoRefCurrents_initialize(RT_MODEL_AutoRefCurrents_t *const
  rtAutoRefCurrents_M)
{
  ExtY_AutoRefCurrents_t *rtAutoRefCurrents_Y = (ExtY_AutoRefCurrents_t *)
    rtAutoRefCurrents_M->outputs;

  /* SystemInitialize for Chart: '<Root>/AutoRefCurrents' incorporates:
   *  Outport: '<Root>/i_dq_ref'
   */
  rtAutoRefCurrents_Y->i_dq_ref.d = 0.0F;
  rtAutoRefCurrents_Y->i_dq_ref.q = 0.0F;
  rtAutoRefCurrents_Y->i_dq_ref.zero = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
