/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FrictionID.c
 *
 * Code generated for Simulink model 'FrictionID'.
 *
 * Model version                  : 2.381
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Dec 23 12:00:40 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "FrictionID_codegen.h"
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_MAX_INSTANCES > 0U

/* Named constants for Chart: '<Root>/FrictionID' */
#define IN_BreakawayTorqueEstimation   ((uint8_T)1U)
#define IN_CoulombFrictionTorqueEstimat ((uint8_T)2U)
#define IN_DecreaseSpeed               ((uint8_T)1U)
#define IN_FinishDataTransfer          ((uint8_T)3U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_ResetIntegrator             ((uint8_T)4U)
#define IN_ResetIntegrator1            ((uint8_T)5U)
#define IN_SmoothingCurrentAndOmega    ((uint8_T)2U)
#define IN_Waiting                     ((uint8_T)1U)
#define IN_frictionID                  ((uint8_T)2U)
#define IN_increaseCurrent             ((uint8_T)1U)
#define IN_waitstate                   ((uint8_T)2U)

/* Forward declaration for local functions */
static void gerade(real32_T u[2], ExtY_FrictionID_t *rtFrictionID_Y);
static void CoulombFrictionTorqueEstimation(ExtU_FrictionID_t *rtFrictionID_U,
  ExtY_FrictionID_t *rtFrictionID_Y, DW_FrictionID_t *rtFrictionID_DW);
static void reset_FOC_output(ExtU_FrictionID_t *rtFrictionID_U,
  ExtY_FrictionID_t *rtFrictionID_Y, DW_FrictionID_t *rtFrictionID_DW);
static void initParams(ExtU_FrictionID_t *rtFrictionID_U, ExtY_FrictionID_t
  *rtFrictionID_Y, DW_FrictionID_t *rtFrictionID_DW);

/*
 * Function for Chart: '<Root>/FrictionID'
 * function u=gerade
 * Evaluation of Coulomb and viscous torque
 * using a linear regression line
 */
static void gerade(real32_T u[2], ExtY_FrictionID_t *rtFrictionID_Y)
{
  int32_T k;
  real32_T Xx;
  real32_T Xy;
  real32_T iestSum;
  real32_T measSum;
  real32_T zaehler;

  /* MATLAB Function 'gerade': '<S1>:625' */
  /* --------initalizing--------------------------------------- */
  /* '<S1>:625:7' gerade=single(zeros(2,1)); */
  /* '<S1>:625:8' zaehler=single(0); */
  zaehler = 0.0F;

  /* '<S1>:625:9' measSum=single(0); */
  measSum = 0.0F;

  /* '<S1>:625:10' iestSum=single(0); */
  iestSum = 0.0F;

  /* '<S1>:625:11' Xy=single(0); */
  Xy = 0.0F;

  /* '<S1>:625:12' Xx=single(0); */
  Xx = 0.0F;

  /* '<S1>:625:13' meanMeas=single(0); */
  /* '<S1>:625:14' meanIest=single(0); */
  /* '<S1>:625:15' SS_xy=single(0); */
  /* '<S1>:625:16' SS_xx=single(0); */
  /* --------summing up---------------------------------- */
  /* '<S1>:625:19' for k=single(2):single(255) */
  for (k = 0; k < 254; k++) {
    real32_T tmp_1;

    /* Outport: '<Root>/FrictionID_output' */
    /* ----------reject outliers--------------------------- */
    /* '<S1>:625:22' if (FrictionID_output.measArraySpeed(k) >5 && ( FrictionID_output.measArrayTorque(k)<1.3*FrictionID_output.measArrayTorque(k+1).... */
    /* '<S1>:625:23'             || FrictionID_output.measArrayTorque(k)<1.3*FrictionID_output.measArrayTorque(k-1) ) &&.... */
    /* '<S1>:625:24'             ( FrictionID_output.measArrayTorque(k)>FrictionID_output.measArrayTorque(k+1)*0.7  ||.... */
    /* '<S1>:625:25'             FrictionID_output.measArrayTorque(k)>FrictionID_output.measArrayTorque(k-1)*0.7 )  ) */
    tmp_1 = rtFrictionID_Y->FrictionID_output.measArraySpeed[k + 1];
    if (tmp_1 > 5.0F) {
      real32_T tmp;
      real32_T tmp_0;

      /* Outport: '<Root>/FrictionID_output' */
      tmp = rtFrictionID_Y->FrictionID_output.measArrayTorque[k + 1];
      tmp_0 = rtFrictionID_Y->FrictionID_output.measArrayTorque[k + 2];
      if (((tmp < tmp_0 * 1.3F) || (tmp < 1.3F *
            rtFrictionID_Y->FrictionID_output.measArrayTorque[k])) && ((tmp >
            tmp_0 * 0.7F) || (tmp >
                              rtFrictionID_Y->
                              FrictionID_output.measArrayTorque[k] * 0.7F))) {
        /* . */
        /* '<S1>:625:26' zaehler=zaehler+1; */
        zaehler++;

        /* '<S1>:625:27' measSum=measSum+FrictionID_output.measArraySpeed(k); */
        measSum += tmp_1;

        /* '<S1>:625:28' iestSum=iestSum+FrictionID_output.measArrayTorque(k); */
        iestSum += tmp;

        /* '<S1>:625:29' Xy=FrictionID_output.measArraySpeed(k)*FrictionID_output.measArrayTorque(k)+Xy; */
        Xy += tmp_1 * tmp;

        /* '<S1>:625:30' Xx=FrictionID_output.measArraySpeed(k)*FrictionID_output.measArraySpeed(k)+Xx; */
        Xx += tmp_1 * tmp_1;
      }
    }
  }

  /* -------calculate mean------------------------------- */
  /* '<S1>:625:36' meanMeas=measSum/zaehler; */
  measSum /= zaehler;

  /* '<S1>:625:37' meanIest=iestSum/zaehler; */
  iestSum /= zaehler;

  /* ----------calculate varianz-------------------------- */
  /* '<S1>:625:40' SS_xy = Xy-zaehler*meanMeas*meanIest; */
  zaehler *= measSum;

  /* '<S1>:625:41' SS_xx = Xx- zaehler*meanMeas*meanMeas; */
  /* -------viscous friction-------------------------------     */
  /* '<S1>:625:44' gerade(1)=single(SS_xy/SS_xx); */
  zaehler = (Xy - zaehler * iestSum) / (Xx - zaehler * measSum);
  u[0] = zaehler;

  /* -------Coulomb friction----------------------------- */
  /* '<S1>:625:47' gerade(2)=single(meanIest-(SS_xy/SS_xx)*meanMeas); */
  u[1] = iestSum - zaehler * measSum;

  /* '<S1>:625:49' u=gerade; */
}

/* Function for Chart: '<Root>/FrictionID' */
static void CoulombFrictionTorqueEstimation(ExtU_FrictionID_t *rtFrictionID_U,
  ExtY_FrictionID_t *rtFrictionID_Y, DW_FrictionID_t *rtFrictionID_DW)
{
  int32_T k;

  /* During 'CoulombFrictionTorqueEstimation': '<S1>:487' */
  /* '<S1>:451:1' sf_internal_predicateOutput = nextstate==1; */
  if (rtFrictionID_DW->nextstate == 1) {
    /* Transition: '<S1>:451' */
    /* Exit Internal 'CoulombFrictionTorqueEstimation': '<S1>:487' */
    if (rtFrictionID_DW->is_CoulombFrictionTorqueEstimat == IN_DecreaseSpeed) {
      /* Exit 'DecreaseSpeed': '<S1>:488' */
      /* '<S1>:488:25' mean_count=1; */
      rtFrictionID_DW->mean_count = 1.0F;
      rtFrictionID_DW->is_CoulombFrictionTorqueEstimat = IN_NO_ACTIVE_CHILD;
    } else {
      rtFrictionID_DW->is_CoulombFrictionTorqueEstimat = IN_NO_ACTIVE_CHILD;
    }

    /* Exit 'CoulombFrictionTorqueEstimation': '<S1>:487' */
    /* '<S1>:487:17' line=gerade; */
    gerade(rtFrictionID_DW->b_line_m, rtFrictionID_Y);

    /* Outport: '<Root>/FrictionID_output' */
    /* '<S1>:487:18' FrictionID_output.CoulTorque=single(line(2)); */
    rtFrictionID_Y->FrictionID_output.CoulTorque = rtFrictionID_DW->b_line_m[1];

    /* '<S1>:487:19' FrictionID_output.ViscoTorque=single(line(1)); */
    rtFrictionID_Y->FrictionID_output.ViscoTorque = rtFrictionID_DW->b_line_m[0];

    /* Outport: '<Root>/FrictionID_FOC_output' */
    /* '<S1>:487:20' FrictionID_FOC_output.n_ref_FOC=single(0); */
    rtFrictionID_Y->FrictionID_FOC_output.n_ref_FOC = 0.0F;
    rtFrictionID_DW->is_frictionID = IN_ResetIntegrator;

    /* Entry 'ResetIntegrator': '<S1>:599' */
    /* '<S1>:599:3' counter2=uint32(1); */
    rtFrictionID_DW->counter2 = 1U;

    /* Outport: '<Root>/FrictionID_FOC_output' */
    /* '<S1>:599:4' FrictionID_FOC_output.activeState=uint16(340); */
    rtFrictionID_Y->FrictionID_FOC_output.activeState = 340U;
  } else {
    /* Outport: '<Root>/FrictionID_FOC_output' */
    /* '<S1>:487:15' FrictionID_FOC_output.n_ref_FOC=n_eva; */
    rtFrictionID_Y->FrictionID_FOC_output.n_ref_FOC = rtFrictionID_DW->n_eva;
    if (rtFrictionID_DW->is_CoulombFrictionTorqueEstimat == IN_DecreaseSpeed) {
      /* During 'DecreaseSpeed': '<S1>:488' */
      /* '<S1>:483:1' sf_internal_predicateOutput = delay_transition_counter == counter2; */
      if (rtFrictionID_DW->delay_transition_counter == rtFrictionID_DW->counter2)
      {
        /* Transition: '<S1>:483' */
        /* Exit 'DecreaseSpeed': '<S1>:488' */
        /* '<S1>:488:25' mean_count=1; */
        rtFrictionID_DW->mean_count = 1.0F;
        rtFrictionID_DW->is_CoulombFrictionTorqueEstimat =
          IN_SmoothingCurrentAndOmega;

        /* Outport: '<Root>/FrictionID_FOC_output' */
        /* Entry 'SmoothingCurrentAndOmega': '<S1>:486' */
        /* '<S1>:486:2' FrictionID_FOC_output.activeState = uint16(331) */
        rtFrictionID_Y->FrictionID_FOC_output.activeState = 331U;

        /* '<S1>:486:3' meas_count=uint16(0); */
        rtFrictionID_DW->meas_count = 0U;

        /* '<S1>:486:4' switcher=boolean(1); */
        rtFrictionID_DW->switcher = true;
      } else {
        uint32_T qY;

        /* '<S1>:488:23' counter2 = counter2 +1; */
        qY = rtFrictionID_DW->counter2 + /*MW:OvSatOk*/ 1U;
        if (rtFrictionID_DW->counter2 + 1U < rtFrictionID_DW->counter2) {
          qY = MAX_uint32_T;
        }

        rtFrictionID_DW->counter2 = qY;
      }

      /* During 'SmoothingCurrentAndOmega': '<S1>:486' */
      /* '<S1>:493:1' sf_internal_predicateOutput = mean_count==256; */
    } else if (rtFrictionID_DW->mean_count == 256.0F) {
      /* Transition: '<S1>:493' */
      rtFrictionID_DW->is_CoulombFrictionTorqueEstimat = IN_DecreaseSpeed;

      /* Entry 'DecreaseSpeed': '<S1>:488' */
      /* '<S1>:488:3' counter2 = uint32(1); */
      rtFrictionID_DW->counter2 = 1U;

      /* Outport: '<Root>/FrictionID_FOC_output' */
      /* '<S1>:488:4' FrictionID_FOC_output.activeState = uint16(332) */
      rtFrictionID_Y->FrictionID_FOC_output.activeState = 332U;

      /* '<S1>:488:5' if(n_eva>0&&switcher==boolean(1)) */
      if ((rtFrictionID_DW->n_eva > 0.0F) && rtFrictionID_DW->switcher) {
        real32_T c_x;
        real32_T d_x;
        real32_T x;
        uint32_T qY;

        /* '<S1>:488:6' FrictionID_output.measArraySpeed(counter)=mean(measArray2(1:256,1)); */
        x = rtFrictionID_DW->measArray2[0];
        for (k = 0; k < 255; k++) {
          x += rtFrictionID_DW->measArray2[k + 1];
        }

        /* Outport: '<Root>/FrictionID_output' */
        rtFrictionID_Y->FrictionID_output.measArraySpeed[(int32_T)
          rtFrictionID_DW->counter - 1] = x / 256.0F;

        /* '<S1>:488:7' FrictionID_output.measArrayTorque(counter)=1.5*GlobalConfig.PMSM_config.polePairs*(GlobalConfig.PMSM_config.Psi_PM_Vs*mean(measArray2(1:256,2)).... */
        /* '<S1>:488:8'         +(GlobalConfig.PMSM_config.Ld_Henry - GlobalConfig.PMSM_config.Lq_Henry)*mean(measArray2(1:256,3))*mean(measArray2(1:256,2))); */
        x = rtFrictionID_DW->measArray2[2048];
        c_x = rtFrictionID_DW->measArray2[4096];
        d_x = rtFrictionID_DW->measArray2[2048];
        for (k = 0; k < 255; k++) {
          real32_T x_tmp;
          x_tmp = rtFrictionID_DW->measArray2[k + 2049];
          x += x_tmp;
          c_x += rtFrictionID_DW->measArray2[k + 4097];
          d_x += x_tmp;
        }

        /* Outport: '<Root>/FrictionID_output' */
        rtFrictionID_Y->FrictionID_output.measArrayTorque[(int32_T)
          rtFrictionID_DW->counter - 1] =
          ((rtFrictionID_U->GlobalConfig_out.PMSM_config.Ld_Henry -
            rtFrictionID_U->GlobalConfig_out.PMSM_config.Lq_Henry) * (c_x /
            256.0F) * (d_x / 256.0F) + x / 256.0F *
           rtFrictionID_U->GlobalConfig_out.PMSM_config.Psi_PM_Vs) * (1.5F *
          rtFrictionID_U->GlobalConfig_out.PMSM_config.polePairs);

        /* . */
        /* '<S1>:488:9' counter=counter+1; */
        qY = rtFrictionID_DW->counter + /*MW:OvSatOk*/ 1U;
        if (rtFrictionID_DW->counter + 1U < rtFrictionID_DW->counter) {
          qY = MAX_uint32_T;
        }

        rtFrictionID_DW->counter = qY;

        /* '<S1>:488:10' n_eva=n_eva-(n_eva_step); */
        rtFrictionID_DW->n_eva -= rtFrictionID_DW->n_eva_step;
      } else if ((rtFrictionID_DW->n_eva > 0.0F) && (!rtFrictionID_DW->switcher))
      {
        uint32_T qY;

        /* '<S1>:488:11' elseif(n_eva>0&&switcher==boolean(0)) */
        /* '<S1>:488:12' switch_count = switch_count + 1; */
        qY = rtFrictionID_DW->switch_count + /*MW:OvSatOk*/ 1U;
        if (rtFrictionID_DW->switch_count + 1U < rtFrictionID_DW->switch_count)
        {
          qY = MAX_uint32_T;
        }

        rtFrictionID_DW->switch_count = qY;
      }

      /* '<S1>:488:14' if (n_eva>0 && switch_count>=5) */
      if ((rtFrictionID_DW->n_eva > 0.0F) && (rtFrictionID_DW->switch_count >=
           5U)) {
        /* '<S1>:488:15' n_eva=n_eva-(n_eva_step); */
        rtFrictionID_DW->n_eva -= rtFrictionID_DW->n_eva_step;

        /* '<S1>:488:16' switch_count = uint32(0); */
        rtFrictionID_DW->switch_count = 0U;
      }

      /* '<S1>:488:18' if(abs(ActualValues.omega_m)<=omega_Brk&&counter>2) */
      if ((fabsf(rtFrictionID_U->ActualValues.omega_m) <=
           rtFrictionID_DW->omega_Brk) && (rtFrictionID_DW->counter > 2U)) {
        /* '<S1>:488:19' n_eva=single(0); */
        rtFrictionID_DW->n_eva = 0.0F;

        /* '<S1>:488:20' nextstate=uint16(1); */
        rtFrictionID_DW->nextstate = 1U;
      }
    } else {
      real32_T c_x;
      real32_T x;
      uint32_T qY;

      /* '<S1>:486:6' if(meas_count==uint32(0.02/GlobalConfig.sampleTimeISR)) */
      x = 0.02F / rtFrictionID_U->GlobalConfig_out.sampleTimeISR;
      c_x = roundf(x);
      if (c_x < 4.2949673E+9F) {
        if (c_x >= 0.0F) {
          qY = (uint32_T)c_x;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

      if (rtFrictionID_DW->meas_count == qY) {
        /* '<S1>:486:7' measArray2(mean_count,1)=meas_sum(1)/(0.02/GlobalConfig.sampleTimeISR); */
        rtFrictionID_DW->measArray2[(int32_T)rtFrictionID_DW->mean_count - 1] =
          rtFrictionID_DW->meas_sum[0] / x;

        /* '<S1>:486:8' measArray2(mean_count,2)=meas_sum(2)/(0.02/GlobalConfig.sampleTimeISR); */
        rtFrictionID_DW->measArray2[(int32_T)rtFrictionID_DW->mean_count + 2047]
          = rtFrictionID_DW->meas_sum[1] / x;

        /* '<S1>:486:9' measArray2(mean_count,3)=meas_sum(3)/(0.02/GlobalConfig.sampleTimeISR); */
        rtFrictionID_DW->measArray2[(int32_T)rtFrictionID_DW->mean_count + 4095]
          = rtFrictionID_DW->meas_sum[2] / x;

        /* '<S1>:486:10' meas_sum=single(zeros(3,1)); */
        rtFrictionID_DW->meas_sum[0] = 0.0F;
        rtFrictionID_DW->meas_sum[1] = 0.0F;
        rtFrictionID_DW->meas_sum[2] = 0.0F;

        /* '<S1>:486:11' if(measArray2(mean_count,1)<((1-FrictionIDConfig.eta)*n_eva*0.1047) ||measArray2(mean_count,1)>((1+FrictionIDConfig.eta)*n_eva*0.1047)) */
        x = rtFrictionID_DW->measArray2[(int32_T)rtFrictionID_DW->mean_count - 1];
        if (x < (1.0F - rtFrictionID_U->FrictionIDConfig.eta) *
            rtFrictionID_DW->n_eva * 0.1047F) {
          /* '<S1>:486:12' switcher=boolean(0); */
          rtFrictionID_DW->switcher = false;
        } else if (x > (rtFrictionID_U->FrictionIDConfig.eta + 1.0F) *
                   rtFrictionID_DW->n_eva * 0.1047F) {
          /* '<S1>:486:12' switcher=boolean(0); */
          rtFrictionID_DW->switcher = false;
        }

        /* '<S1>:486:14' mean_count = mean_count + 1; */
        rtFrictionID_DW->mean_count++;

        /* '<S1>:486:15' meas_count=uint16(0); */
        rtFrictionID_DW->meas_count = 0U;
      }

      /* '<S1>:486:17' meas_count=meas_count+1; */
      qY = rtFrictionID_DW->meas_count + 1U;
      if (rtFrictionID_DW->meas_count + 1U > 65535U) {
        qY = 65535U;
      }

      rtFrictionID_DW->meas_count = (uint16_T)qY;

      /* '<S1>:486:18' meas_sum(1)=meas_sum(1)+abs(ActualValues.omega_m); */
      rtFrictionID_DW->meas_sum[0] += fabsf(rtFrictionID_U->ActualValues.omega_m);

      /* '<S1>:486:19' meas_sum(2)=meas_sum(2)+abs(ActualValues.i_dq.q); */
      rtFrictionID_DW->meas_sum[1] += fabsf(rtFrictionID_U->ActualValues.i_dq.q);

      /* '<S1>:486:20' meas_sum(3)=meas_sum(3)+abs(ActualValues.i_dq.d); */
      rtFrictionID_DW->meas_sum[2] += fabsf(rtFrictionID_U->ActualValues.i_dq.d);
    }
  }
}

/*
 * Function for Chart: '<Root>/FrictionID'
 * function reset_FOC_output
 * Outputs
 */
static void reset_FOC_output(ExtU_FrictionID_t *rtFrictionID_U,
  ExtY_FrictionID_t *rtFrictionID_Y, DW_FrictionID_t *rtFrictionID_DW)
{
  /* Outport: '<Root>/FrictionID_FOC_output' */
  /* MATLAB Function 'reset_FOC_output': '<S1>:618' */
  /* '<S1>:618:4' FrictionID_FOC_output.n_ref_FOC             = single(0.0); */
  rtFrictionID_Y->FrictionID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S1>:618:5' FrictionID_FOC_output.M_ref_FOC             = single(0.0); */
  rtFrictionID_Y->FrictionID_FOC_output.M_ref_FOC = 0.0F;

  /* '<S1>:618:6' FrictionID_FOC_output.i_dq_ref.d            = single(0.0); */
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S1>:618:7' FrictionID_FOC_output.i_dq_ref.q            = single(M_eva); */
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.q = rtFrictionID_DW->M_eva;

  /* '<S1>:618:8' FrictionID_FOC_output.i_dq_ref.zero         = single(0.0); */
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S1>:618:9' FrictionID_FOC_output.enableFOC_speed       = boolean(0); */
  rtFrictionID_Y->FrictionID_FOC_output.enableFOC_speed = false;

  /* '<S1>:618:10' FrictionID_FOC_output.enableFOC_current     = boolean(0); */
  rtFrictionID_Y->FrictionID_FOC_output.enableFOC_current = false;

  /* '<S1>:618:11' FrictionID_FOC_output.resetIntegrator       = boolean(1); */
  rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = true;

  /* '<S1>:618:12' FrictionID_FOC_output.Kp_id_out             = single(GlobalConfig.Kp_id); */
  rtFrictionID_Y->FrictionID_FOC_output.Kp_id_out =
    rtFrictionID_U->GlobalConfig_out.Kp_id;

  /* '<S1>:618:13' FrictionID_FOC_output.Kp_iq_out             = single(GlobalConfig.Kp_iq); */
  rtFrictionID_Y->FrictionID_FOC_output.Kp_iq_out =
    rtFrictionID_U->GlobalConfig_out.Kp_iq;

  /* '<S1>:618:14' FrictionID_FOC_output.Kp_n_out              = single(GlobalConfig.Kp_n); */
  rtFrictionID_Y->FrictionID_FOC_output.Kp_n_out =
    rtFrictionID_U->GlobalConfig_out.Kp_n;

  /* '<S1>:618:15' FrictionID_FOC_output.Ki_id_out             = single(GlobalConfig.Ki_id); */
  rtFrictionID_Y->FrictionID_FOC_output.Ki_id_out =
    rtFrictionID_U->GlobalConfig_out.Ki_id;

  /* '<S1>:618:16' FrictionID_FOC_output.Ki_iq_out             = single(GlobalConfig.Ki_iq); */
  rtFrictionID_Y->FrictionID_FOC_output.Ki_iq_out =
    rtFrictionID_U->GlobalConfig_out.Ki_iq;

  /* '<S1>:618:17' FrictionID_FOC_output.Ki_n_out              = single(GlobalConfig.Ki_n); */
  rtFrictionID_Y->FrictionID_FOC_output.Ki_n_out =
    rtFrictionID_U->GlobalConfig_out.Ki_n;

  /* '<S1>:618:18' FrictionID_FOC_output.activeState               = uint16(0); */
  rtFrictionID_Y->FrictionID_FOC_output.activeState = 0U;
}

/*
 * Function for Chart: '<Root>/FrictionID'
 * function initParams
 * This is used instead of "after(1.0,sec) to ensure the same transition time
 * independelty of the sampletime in the c-code
 */
static void initParams(ExtU_FrictionID_t *rtFrictionID_U, ExtY_FrictionID_t
  *rtFrictionID_Y, DW_FrictionID_t *rtFrictionID_DW)
{
  real32_T tmp;

  /* MATLAB Function 'initParams': '<S1>:546' */
  /* '<S1>:546:5' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  tmp = roundf(1.0F / rtFrictionID_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFrictionID_DW->one_sec_transition_counter = (uint32_T)tmp;
    } else {
      rtFrictionID_DW->one_sec_transition_counter = 0U;
    }
  } else {
    rtFrictionID_DW->one_sec_transition_counter = MAX_uint32_T;
  }

  /* '<S1>:546:6' ten_sec_transition_counter = uint32(10/GlobalConfig.sampleTimeISR); */
  tmp = roundf(10.0F / rtFrictionID_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFrictionID_DW->ten_sec_transition_counter = (uint32_T)tmp;
    } else {
      rtFrictionID_DW->ten_sec_transition_counter = 0U;
    }
  } else {
    rtFrictionID_DW->ten_sec_transition_counter = MAX_uint32_T;
  }

  /* '<S1>:546:7' delay_transition_counter = uint32(single(5*(GlobalConfig.Kp_iq / GlobalConfig.Ki_iq))/GlobalConfig.sampleTimeISR); */
  tmp = roundf(rtFrictionID_U->GlobalConfig_out.Kp_iq /
               rtFrictionID_U->GlobalConfig_out.Ki_iq * 5.0F /
               rtFrictionID_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFrictionID_DW->delay_transition_counter = (uint32_T)tmp;
    } else {
      rtFrictionID_DW->delay_transition_counter = 0U;
    }
  } else {
    rtFrictionID_DW->delay_transition_counter = MAX_uint32_T;
  }

  /*  initialize variables */
  /* '<S1>:546:9' meas_sum            = single(zeros(3,1)); */
  rtFrictionID_DW->meas_sum[0] = 0.0F;
  rtFrictionID_DW->meas_sum[1] = 0.0F;
  rtFrictionID_DW->meas_sum[2] = 0.0F;

  /* '<S1>:546:10' measArray2 			= single(zeros(2048,3)); */
  memset(&rtFrictionID_DW->measArray2[0], 0, 6144U * sizeof(real32_T));

  /* '<S1>:546:11' counter             = uint32(1); */
  rtFrictionID_DW->counter = 1U;

  /* '<S1>:546:12' switch_count        = uint32(0); */
  rtFrictionID_DW->switch_count = 0U;

  /* '<S1>:546:13' Ustep               = single(zeros(103,1)); */
  memset(&rtFrictionID_DW->Ustep[0], 0, 103U * sizeof(real32_T));

  /* '<S1>:546:14' nextstate           = uint16(0); */
  rtFrictionID_DW->nextstate = 0U;

  /* '<S1>:546:15' M_eva               = single(0); */
  rtFrictionID_DW->M_eva = 0.0F;

  /* '<S1>:546:16' n_eva               = single(FrictionIDConfig.n_eva_max); */
  rtFrictionID_DW->n_eva = rtFrictionID_U->FrictionIDConfig.n_eva_max;

  /* '<S1>:546:17' n_eva_step          = single(n_eva/single(FrictionIDConfig.N_Visco)); */
  rtFrictionID_DW->n_eva_step = rtFrictionID_DW->n_eva / (real32_T)
    rtFrictionID_U->FrictionIDConfig.N_Visco;

  /* '<S1>:546:18' M_Brk               = single(0); */
  rtFrictionID_DW->M_Brk = 0.0F;

  /* '<S1>:546:19' mean_count          = single(0); */
  rtFrictionID_DW->mean_count = 0.0F;

  /* '<S1>:546:20' omega_Brk           = single(1); */
  rtFrictionID_DW->omega_Brk = 1.0F;

  /* '<S1>:546:21' delay               = single(5*(GlobalConfig.Kp_iq / GlobalConfig.Ki_iq)); */
  /* '<S1>:546:22' M_eva_step          = single(GlobalConfig.ratTorque*FrictionIDConfig.StepScale); */
  rtFrictionID_DW->M_eva_step = rtFrictionID_U->GlobalConfig_out.ratTorque *
    rtFrictionID_U->FrictionIDConfig.StepScale;

  /* Outport: '<Root>/FrictionID_FOC_output' */
  /* '<S1>:546:23' line                = single(zeros(2,1)); */
  /* Outputs */
  /* '<S1>:546:26' FrictionID_FOC_output.n_ref_FOC             = single(0.0); */
  rtFrictionID_Y->FrictionID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S1>:546:27' FrictionID_FOC_output.M_ref_FOC             = single(0.0); */
  rtFrictionID_Y->FrictionID_FOC_output.M_ref_FOC = 0.0F;

  /* '<S1>:546:28' FrictionID_FOC_output.i_dq_ref.d            = single(0.0); */
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S1>:546:29' FrictionID_FOC_output.i_dq_ref.q            = single(M_eva); */
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S1>:546:30' FrictionID_FOC_output.i_dq_ref.zero         = single(0.0); */
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S1>:546:31' FrictionID_FOC_output.enableFOC_speed       = boolean(0); */
  rtFrictionID_Y->FrictionID_FOC_output.enableFOC_speed = false;

  /* '<S1>:546:32' FrictionID_FOC_output.enableFOC_current     = boolean(0); */
  rtFrictionID_Y->FrictionID_FOC_output.enableFOC_current = false;

  /* '<S1>:546:33' FrictionID_FOC_output.resetIntegrator       = boolean(1); */
  rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = true;

  /* '<S1>:546:34' finishedFrictionID                          = boolean(0); */
  rtFrictionID_Y->finishedFrictionID = false;

  /* Outport: '<Root>/FrictionID_FOC_output' */
  /* '<S1>:546:35' FrictionID_FOC_output.Kp_id_out             = single(GlobalConfig.Kp_id); */
  rtFrictionID_Y->FrictionID_FOC_output.Kp_id_out =
    rtFrictionID_U->GlobalConfig_out.Kp_id;

  /* '<S1>:546:36' FrictionID_FOC_output.Kp_iq_out             = single(GlobalConfig.Kp_iq); */
  rtFrictionID_Y->FrictionID_FOC_output.Kp_iq_out =
    rtFrictionID_U->GlobalConfig_out.Kp_iq;

  /* '<S1>:546:37' FrictionID_FOC_output.Kp_n_out              = single(GlobalConfig.Kp_n); */
  rtFrictionID_Y->FrictionID_FOC_output.Kp_n_out =
    rtFrictionID_U->GlobalConfig_out.Kp_n;

  /* '<S1>:546:38' FrictionID_FOC_output.Ki_id_out             = single(GlobalConfig.Ki_id); */
  rtFrictionID_Y->FrictionID_FOC_output.Ki_id_out =
    rtFrictionID_U->GlobalConfig_out.Ki_id;

  /* '<S1>:546:39' FrictionID_FOC_output.Ki_iq_out             = single(GlobalConfig.Ki_iq); */
  rtFrictionID_Y->FrictionID_FOC_output.Ki_iq_out =
    rtFrictionID_U->GlobalConfig_out.Ki_iq;

  /* '<S1>:546:40' FrictionID_FOC_output.Ki_n_out              = single(GlobalConfig.Ki_n); */
  rtFrictionID_Y->FrictionID_FOC_output.Ki_n_out =
    rtFrictionID_U->GlobalConfig_out.Ki_n;

  /* '<S1>:546:41' FrictionID_FOC_output.activeState           = uint16(0); */
  rtFrictionID_Y->FrictionID_FOC_output.activeState = 0U;

  /* Outport: '<Root>/FrictionID_output' */
  /* '<S1>:546:43' FrictionID_output.BrkTorque                 = single(0.0); */
  rtFrictionID_Y->FrictionID_output.BrkTorque = 0.0F;

  /* '<S1>:546:44' FrictionID_output.CoulTorque                = single(0.0); */
  rtFrictionID_Y->FrictionID_output.CoulTorque = 0.0F;

  /* '<S1>:546:45' FrictionID_output.ViscoTorque               = single(0.0); */
  rtFrictionID_Y->FrictionID_output.ViscoTorque = 0.0F;

  /* '<S1>:546:46' FrictionID_output.measArraySpeed			= single(zeros(256,1)); */
  /* '<S1>:546:47' FrictionID_output.measArrayTorque           = single(zeros(256,1)); */
  memset(&rtFrictionID_Y->FrictionID_output.measArraySpeed[0], 0, sizeof
         (real32_T) << 8U);
  memset(&rtFrictionID_Y->FrictionID_output.measArrayTorque[0], 0, sizeof
         (real32_T) << 8U);
}

/* Model step function */
void FrictionID_step(RT_MODEL_FrictionID_t *const rtFrictionID_M)
{
  DW_FrictionID_t *rtFrictionID_DW = rtFrictionID_M->dwork;
  ExtU_FrictionID_t *rtFrictionID_U = (ExtU_FrictionID_t *)
    rtFrictionID_M->inputs;
  ExtY_FrictionID_t *rtFrictionID_Y = (ExtY_FrictionID_t *)
    rtFrictionID_M->outputs;

  /* Chart: '<Root>/FrictionID' incorporates:
   *  Outport: '<Root>/FrictionID_FOC_output'
   *  Outport: '<Root>/FrictionID_output'
   */
  /* Gateway: FrictionID */
  /* During: FrictionID */
  if (rtFrictionID_DW->is_active_c7_FrictionID == 0U) {
    /* Entry: FrictionID */
    rtFrictionID_DW->is_active_c7_FrictionID = 1U;

    /* Entry Internal: FrictionID */
    /* Transition: '<S1>:596' */
    rtFrictionID_DW->is_c7_FrictionID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:594' */
    /* wait for activation of */
    /* FrictionID */
    /* donothing */
  } else if (rtFrictionID_DW->is_c7_FrictionID == IN_Waiting) {
    /* During 'Waiting': '<S1>:594' */
    /* '<S1>:597:1' sf_internal_predicateOutput = ControlFlags.startFrictionID==1 && GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1; */
    if (rtFrictionID_U->ControlFlags.startFrictionID &&
        (!rtFrictionID_U->GlobalConfig_out.Reset) &&
        rtFrictionID_U->GlobalConfig_out.ACCEPT) {
      /* Transition: '<S1>:597' */
      rtFrictionID_DW->is_c7_FrictionID = IN_frictionID;

      /* Entry 'frictionID': '<S1>:39' */
      /* '<S1>:39:3' initParams; */
      initParams(rtFrictionID_U, rtFrictionID_Y, rtFrictionID_DW);

      /* Outport: '<Root>/enteredFrictionID' */
      /* '<S1>:39:4' enteredFrictionID=boolean(1); */
      rtFrictionID_Y->enteredFrictionID = true;

      /* '<S1>:39:5' FrictionID_FOC_output.activeState=uint16(300); */
      /* Entry Internal 'frictionID': '<S1>:39' */
      /* Transition: '<S1>:549' */
      rtFrictionID_DW->is_frictionID = IN_BreakawayTorqueEstimation;

      /* Entry 'BreakawayTorqueEstimation': '<S1>:492' */
      /* '<S1>:492:3' FrictionID_FOC_output.activeState = uint16(310); */
      /* '<S1>:492:4' FrictionID_FOC_output.enableFOC_torque=boolean(1); */
      rtFrictionID_Y->FrictionID_FOC_output.enableFOC_torque = true;

      /* '<S1>:492:5' FrictionID_FOC_output.resetIntegrator=boolean(0); */
      rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = false;

      /* Entry Internal 'BreakawayTorqueEstimation': '<S1>:492' */
      /* Transition: '<S1>:494' */
      rtFrictionID_DW->is_BreakawayTorqueEstimation = IN_waitstate;

      /* Entry 'waitstate': '<S1>:489' */
      /* '<S1>:489:4' counter2 = uint32(1); */
      rtFrictionID_DW->counter2 = 1U;

      /* '<S1>:489:5' FrictionID_FOC_output.activeState=uint16(311); */
      rtFrictionID_Y->FrictionID_FOC_output.activeState = 311U;

      /* '<S1>:612:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
    } else if (rtFrictionID_U->GlobalConfig_out.Reset) {
      /* Outport: '<Root>/enteredFrictionID' */
      /* Transition: '<S1>:612' */
      /* '<S1>:612:1' finishedFrictionID=boolean(0); */
      /* '<S1>:612:2' enteredFrictionID=boolean(0); */
      rtFrictionID_Y->enteredFrictionID = false;

      /* '<S1>:612:3' initParams; */
      initParams(rtFrictionID_U, rtFrictionID_Y, rtFrictionID_DW);

      /* Entry 'Waiting': '<S1>:594' */
      /* wait for activation of */
      /* FrictionID */
      /* donothing */
    }

    /* During 'frictionID': '<S1>:39' */
    /* '<S1>:595:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.FrictionID==0 || .... */
    /* '<S1>:595:2' GlobalConfig.enableParameterID==0; */
    /* . */
  } else if (rtFrictionID_U->GlobalConfig_out.Reset ||
             (!rtFrictionID_U->GlobalConfig_out.FrictionID) ||
             (!rtFrictionID_U->GlobalConfig_out.enableParameterID)) {
    /* Outport: '<Root>/enteredFrictionID' */
    /* Transition: '<S1>:595' */
    /* '<S1>:595:3' enteredFrictionID=boolean(0); */
    rtFrictionID_Y->enteredFrictionID = false;

    /* '<S1>:595:3' initParams; */
    initParams(rtFrictionID_U, rtFrictionID_Y, rtFrictionID_DW);

    /* Exit Internal 'frictionID': '<S1>:39' */
    switch (rtFrictionID_DW->is_frictionID) {
     case IN_BreakawayTorqueEstimation:
      {
        /* Exit Internal 'BreakawayTorqueEstimation': '<S1>:492' */
        rtFrictionID_DW->is_BreakawayTorqueEstimation = IN_NO_ACTIVE_CHILD;

        /* Exit 'BreakawayTorqueEstimation': '<S1>:492' */
        /* '<S1>:492:17' FrictionID_output.BrkTorque=max(Ustep); */
        rtFrictionID_DW->ex = rtFrictionID_DW->Ustep[0];
        for (rtFrictionID_DW->i = 0; rtFrictionID_DW->i < 102;
             rtFrictionID_DW->i++) {
          real32_T tmp;
          tmp = rtFrictionID_DW->Ustep[rtFrictionID_DW->i + 1];
          if (rtFrictionID_DW->ex < tmp) {
            rtFrictionID_DW->ex = tmp;
          }
        }

        rtFrictionID_Y->FrictionID_output.BrkTorque = rtFrictionID_DW->ex;

        /* '<S1>:492:18' FrictionID_FOC_output.M_ref_FOC = single(0.0); */
        rtFrictionID_Y->FrictionID_FOC_output.M_ref_FOC = 0.0F;
        rtFrictionID_DW->is_frictionID = IN_NO_ACTIVE_CHILD;
      }
      break;

     case IN_CoulombFrictionTorqueEstimat:
      /* Exit Internal 'CoulombFrictionTorqueEstimation': '<S1>:487' */
      if (rtFrictionID_DW->is_CoulombFrictionTorqueEstimat == IN_DecreaseSpeed)
      {
        /* Exit 'DecreaseSpeed': '<S1>:488' */
        /* '<S1>:488:25' mean_count=1; */
        rtFrictionID_DW->mean_count = 1.0F;
        rtFrictionID_DW->is_CoulombFrictionTorqueEstimat = IN_NO_ACTIVE_CHILD;
      } else {
        rtFrictionID_DW->is_CoulombFrictionTorqueEstimat = IN_NO_ACTIVE_CHILD;
      }

      /* Exit 'CoulombFrictionTorqueEstimation': '<S1>:487' */
      /* '<S1>:487:17' line=gerade; */
      gerade(rtFrictionID_DW->b_line, rtFrictionID_Y);

      /* '<S1>:487:18' FrictionID_output.CoulTorque=single(line(2)); */
      rtFrictionID_Y->FrictionID_output.CoulTorque = rtFrictionID_DW->b_line[1];

      /* '<S1>:487:19' FrictionID_output.ViscoTorque=single(line(1)); */
      rtFrictionID_Y->FrictionID_output.ViscoTorque = rtFrictionID_DW->b_line[0];

      /* '<S1>:487:20' FrictionID_FOC_output.n_ref_FOC=single(0); */
      rtFrictionID_Y->FrictionID_FOC_output.n_ref_FOC = 0.0F;
      rtFrictionID_DW->is_frictionID = IN_NO_ACTIVE_CHILD;
      break;

     case IN_FinishDataTransfer:
      /* Outport: '<Root>/finishedFrictionID' */
      /* Exit 'FinishDataTransfer': '<S1>:628' */
      /* '<S1>:628:9' finishedFrictionID=boolean(1); */
      rtFrictionID_Y->finishedFrictionID = true;

      /* '<S1>:628:10' enteredFrictionID=boolean(0); */
      /* '<S1>:628:11' reset_FOC_output; */
      reset_FOC_output(rtFrictionID_U, rtFrictionID_Y, rtFrictionID_DW);
      rtFrictionID_DW->is_frictionID = IN_NO_ACTIVE_CHILD;
      break;

     case IN_ResetIntegrator:
      /* Exit 'ResetIntegrator': '<S1>:599' */
      rtFrictionID_DW->is_frictionID = IN_NO_ACTIVE_CHILD;
      break;

     case IN_ResetIntegrator1:
      /* Exit 'ResetIntegrator1': '<S1>:604' */
      /* '<S1>:604:9' FrictionID_FOC_output.enableFOC_torque=boolean(0); */
      rtFrictionID_Y->FrictionID_FOC_output.enableFOC_torque = false;

      /* '<S1>:604:10' FrictionID_FOC_output.resetIntegrator=boolean(0); */
      rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = false;
      rtFrictionID_DW->is_frictionID = IN_NO_ACTIVE_CHILD;
      break;

     default:
      rtFrictionID_DW->is_frictionID = IN_NO_ACTIVE_CHILD;
      break;
    }

    rtFrictionID_DW->is_c7_FrictionID = IN_Waiting;

    /* Entry 'Waiting': '<S1>:594' */
    /* wait for activation of */
    /* FrictionID */
    /* donothing */
  } else {
    switch (rtFrictionID_DW->is_frictionID) {
     case IN_BreakawayTorqueEstimation:
      /* During 'BreakawayTorqueEstimation': '<S1>:492' */
      /* '<S1>:497:1' sf_internal_predicateOutput = counter>FrictionIDConfig.N_Brk; */
      if (rtFrictionID_DW->counter > rtFrictionID_U->FrictionIDConfig.N_Brk) {
        /* Transition: '<S1>:497' */
        /* Exit Internal 'BreakawayTorqueEstimation': '<S1>:492' */
        rtFrictionID_DW->is_BreakawayTorqueEstimation = IN_NO_ACTIVE_CHILD;

        /* Exit 'BreakawayTorqueEstimation': '<S1>:492' */
        /* '<S1>:492:17' FrictionID_output.BrkTorque=max(Ustep); */
        rtFrictionID_DW->ex = rtFrictionID_DW->Ustep[0];
        for (rtFrictionID_DW->i = 0; rtFrictionID_DW->i < 102;
             rtFrictionID_DW->i++) {
          if (rtFrictionID_DW->ex < rtFrictionID_DW->Ustep[rtFrictionID_DW->i +
              1]) {
            rtFrictionID_DW->ex = rtFrictionID_DW->Ustep[rtFrictionID_DW->i + 1];
          }
        }

        rtFrictionID_Y->FrictionID_output.BrkTorque = rtFrictionID_DW->ex;

        /* '<S1>:492:18' FrictionID_FOC_output.M_ref_FOC = single(0.0); */
        rtFrictionID_Y->FrictionID_FOC_output.M_ref_FOC = 0.0F;
        rtFrictionID_DW->is_frictionID = IN_ResetIntegrator1;

        /* Entry 'ResetIntegrator1': '<S1>:604' */
        /* '<S1>:604:3' counter2=uint32(1); */
        rtFrictionID_DW->counter2 = 1U;

        /* '<S1>:604:4' FrictionID_FOC_output.activeState=uint16(320); */
        rtFrictionID_Y->FrictionID_FOC_output.activeState = 320U;
      } else {
        /* '<S1>:492:7' FrictionID_FOC_output.M_ref_FOC=M_eva; */
        rtFrictionID_Y->FrictionID_FOC_output.M_ref_FOC = rtFrictionID_DW->M_eva;

        /* '<S1>:492:8' if(nextstate>=FrictionIDConfig.BrkCount) */
        if (rtFrictionID_DW->nextstate >=
            rtFrictionID_U->FrictionIDConfig.BrkCount) {
          /* '<S1>:492:9' M_eva=single(0); */
          rtFrictionID_DW->M_eva = 0.0F;

          /* '<S1>:492:10' if(counter<=FrictionIDConfig.N_Brk) */
          if (rtFrictionID_DW->counter <= rtFrictionID_U->FrictionIDConfig.N_Brk)
          {
            /* '<S1>:492:11' Ustep(counter)=M_Brk; */
            rtFrictionID_DW->Ustep[(int32_T)rtFrictionID_DW->counter - 1] =
              rtFrictionID_DW->M_Brk;
          }

          /* '<S1>:492:13' nextstate=uint16(0); */
          rtFrictionID_DW->nextstate = 0U;

          /* '<S1>:492:14' counter = counter + 1; */
          rtFrictionID_DW->qY = rtFrictionID_DW->counter + /*MW:OvSatOk*/ 1U;
          if (rtFrictionID_DW->counter + 1U < rtFrictionID_DW->counter) {
            rtFrictionID_DW->qY = MAX_uint32_T;
          }

          rtFrictionID_DW->counter = rtFrictionID_DW->qY;
        }

        if (rtFrictionID_DW->is_BreakawayTorqueEstimation == IN_increaseCurrent)
        {
          /* During 'increaseCurrent': '<S1>:495' */
          /* Transition: '<S1>:491' */
          rtFrictionID_DW->is_BreakawayTorqueEstimation = IN_waitstate;

          /* Entry 'waitstate': '<S1>:489' */
          /* '<S1>:489:4' counter2 = uint32(1); */
          rtFrictionID_DW->counter2 = 1U;

          /* '<S1>:489:5' FrictionID_FOC_output.activeState=uint16(311); */
          rtFrictionID_Y->FrictionID_FOC_output.activeState = 311U;

          /* During 'waitstate': '<S1>:489' */
          /* '<S1>:490:1' sf_internal_predicateOutput = delay_transition_counter == counter2; */
        } else if (rtFrictionID_DW->delay_transition_counter ==
                   rtFrictionID_DW->counter2) {
          /* Transition: '<S1>:490' */
          rtFrictionID_DW->is_BreakawayTorqueEstimation = IN_increaseCurrent;

          /* Entry 'increaseCurrent': '<S1>:495' */
          /* '<S1>:495:4' FrictionID_FOC_output.activeState = uint16(312); */
          rtFrictionID_Y->FrictionID_FOC_output.activeState = 312U;

          /* '<S1>:495:5' if(abs(ActualValues.omega_m)>single(0) && M_eva>single(0)) */
          rtFrictionID_DW->ex = fabsf(rtFrictionID_U->ActualValues.omega_m);
          if ((rtFrictionID_DW->ex > 0.0F) && (rtFrictionID_DW->M_eva > 0.0F)) {
            /* '<S1>:495:6' M_Brk=M_eva; */
            rtFrictionID_DW->M_Brk = rtFrictionID_DW->M_eva;

            /* '<S1>:495:7' nextstate=nextstate+1; */
            rtFrictionID_DW->nextstate++;
          }

          /* '<S1>:495:9' if(abs(ActualValues.omega_m)<=omega_Brk&&abs(M_eva)<FrictionIDConfig.maxCurrent) */
          if ((rtFrictionID_DW->ex <= rtFrictionID_DW->omega_Brk) && (fabsf
               (rtFrictionID_DW->M_eva) <
               rtFrictionID_U->FrictionIDConfig.maxCurrent)) {
            /* '<S1>:495:11' M_eva=M_eva+M_eva_step; */
            rtFrictionID_DW->M_eva += rtFrictionID_DW->M_eva_step;

            /* '<S1>:495:12' nextstate=uint16(0); */
            rtFrictionID_DW->nextstate = 0U;
          }
        } else {
          /* '<S1>:489:7' counter2 = counter2 + 1; */
          rtFrictionID_DW->qY = rtFrictionID_DW->counter2 + /*MW:OvSatOk*/ 1U;
          if (rtFrictionID_DW->counter2 + 1U < rtFrictionID_DW->counter2) {
            rtFrictionID_DW->qY = MAX_uint32_T;
          }

          rtFrictionID_DW->counter2 = rtFrictionID_DW->qY;
        }
      }
      break;

     case IN_CoulombFrictionTorqueEstimat:
      CoulombFrictionTorqueEstimation(rtFrictionID_U, rtFrictionID_Y,
        rtFrictionID_DW);
      break;

     case IN_FinishDataTransfer:
      /* During 'FinishDataTransfer': '<S1>:628' */
      /* '<S1>:629:1' sf_internal_predicateOutput = one_sec_transition_counter == counter2; */
      if (rtFrictionID_DW->one_sec_transition_counter ==
          rtFrictionID_DW->counter2) {
        /* Outport: '<Root>/finishedFrictionID' */
        /* Transition: '<S1>:629' */
        /* Exit 'FinishDataTransfer': '<S1>:628' */
        /* '<S1>:628:9' finishedFrictionID=boolean(1); */
        rtFrictionID_Y->finishedFrictionID = true;

        /* Outport: '<Root>/enteredFrictionID' */
        /* '<S1>:628:10' enteredFrictionID=boolean(0); */
        rtFrictionID_Y->enteredFrictionID = false;

        /* '<S1>:628:11' reset_FOC_output; */
        reset_FOC_output(rtFrictionID_U, rtFrictionID_Y, rtFrictionID_DW);
        rtFrictionID_DW->is_frictionID = IN_NO_ACTIVE_CHILD;
        rtFrictionID_DW->is_c7_FrictionID = IN_Waiting;

        /* Entry 'Waiting': '<S1>:594' */
        /* wait for activation of */
        /* FrictionID */
        /* donothing */
      } else {
        /* '<S1>:628:7' counter2 = counter2 +1; */
        rtFrictionID_DW->qY = rtFrictionID_DW->counter2 + /*MW:OvSatOk*/ 1U;
        if (rtFrictionID_DW->counter2 + 1U < rtFrictionID_DW->counter2) {
          rtFrictionID_DW->qY = MAX_uint32_T;
        }

        rtFrictionID_DW->counter2 = rtFrictionID_DW->qY;
      }
      break;

     case IN_ResetIntegrator:
      /* During 'ResetIntegrator': '<S1>:599' */
      /* '<S1>:600:1' sf_internal_predicateOutput = ten_sec_transition_counter == counter2; */
      if (rtFrictionID_DW->ten_sec_transition_counter ==
          rtFrictionID_DW->counter2) {
        /* Transition: '<S1>:600' */
        /* Exit 'ResetIntegrator': '<S1>:599' */
        rtFrictionID_DW->is_frictionID = IN_FinishDataTransfer;

        /* Entry 'FinishDataTransfer': '<S1>:628' */
        /* '<S1>:628:3' counter2=uint32(1); */
        rtFrictionID_DW->counter2 = 1U;

        /* '<S1>:628:4' FrictionID_FOC_output.resetIntegrator=boolean(1); */
        rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = true;

        /* '<S1>:628:5' FrictionID_FOC_output.activeState=uint16(341); */
        rtFrictionID_Y->FrictionID_FOC_output.activeState = 341U;
      } else {
        /* '<S1>:599:6' counter2 = counter2 +1; */
        rtFrictionID_DW->qY = rtFrictionID_DW->counter2 + /*MW:OvSatOk*/ 1U;
        if (rtFrictionID_DW->counter2 + 1U < rtFrictionID_DW->counter2) {
          rtFrictionID_DW->qY = MAX_uint32_T;
        }

        rtFrictionID_DW->counter2 = rtFrictionID_DW->qY;

        /* '<S1>:599:7' FrictionID_FOC_output.resetIntegrator=boolean(1); */
        rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = true;
      }
      break;

     default:
      /* During 'ResetIntegrator1': '<S1>:604' */
      /* '<S1>:607:1' sf_internal_predicateOutput = one_sec_transition_counter == counter2; */
      if (rtFrictionID_DW->one_sec_transition_counter ==
          rtFrictionID_DW->counter2) {
        /* Transition: '<S1>:607' */
        /* Exit 'ResetIntegrator1': '<S1>:604' */
        /* '<S1>:604:9' FrictionID_FOC_output.enableFOC_torque=boolean(0); */
        rtFrictionID_Y->FrictionID_FOC_output.enableFOC_torque = false;

        /* '<S1>:604:10' FrictionID_FOC_output.resetIntegrator=boolean(0); */
        rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = false;
        rtFrictionID_DW->is_frictionID = IN_CoulombFrictionTorqueEstimat;

        /* Entry 'CoulombFrictionTorqueEstimation': '<S1>:487' */
        /* '<S1>:487:3' FrictionID_FOC_output.activeState = uint16(330); */
        /* '<S1>:487:4' FrictionID_FOC_output.enableFOC_speed=boolean(1); */
        rtFrictionID_Y->FrictionID_FOC_output.enableFOC_speed = true;

        /* '<S1>:487:5' FrictionID_FOC_output.n_ref_FOC=single(0); */
        rtFrictionID_Y->FrictionID_FOC_output.n_ref_FOC = 0.0F;

        /* '<S1>:487:6' delay=single(0.1); */
        /* '<S1>:487:7' meas_sum=single(zeros(3,1)); */
        /* '<S1>:487:8' measArray2(1:1024,1:3)=zeros(1024,3); */
        for (rtFrictionID_DW->i = 0; rtFrictionID_DW->i < 3; rtFrictionID_DW->i
             ++) {
          rtFrictionID_DW->meas_sum[rtFrictionID_DW->i] = 0.0F;
          memset(&rtFrictionID_DW->measArray2[rtFrictionID_DW->i << 11], 0,
                 sizeof(real32_T) << 10U);
        }

        /* '<S1>:487:9' omega_Brk=single(5.0); */
        rtFrictionID_DW->omega_Brk = 5.0F;

        /* '<S1>:487:10' nextstate=uint16(0); */
        rtFrictionID_DW->nextstate = 0U;

        /* '<S1>:487:11' counter=uint32(1); */
        rtFrictionID_DW->counter = 1U;

        /* '<S1>:487:12' mean_count=single(256); */
        rtFrictionID_DW->mean_count = 256.0F;

        /* '<S1>:487:13' meas_count=uint16(0); */
        /* Entry Internal 'CoulombFrictionTorqueEstimation': '<S1>:487' */
        /* Transition: '<S1>:496' */
        rtFrictionID_DW->is_CoulombFrictionTorqueEstimat =
          IN_SmoothingCurrentAndOmega;

        /* Entry 'SmoothingCurrentAndOmega': '<S1>:486' */
        /* '<S1>:486:2' FrictionID_FOC_output.activeState = uint16(331) */
        rtFrictionID_Y->FrictionID_FOC_output.activeState = 331U;

        /* '<S1>:486:3' meas_count=uint16(0); */
        rtFrictionID_DW->meas_count = 0U;

        /* '<S1>:486:4' switcher=boolean(1); */
        rtFrictionID_DW->switcher = true;
      } else {
        /* '<S1>:604:6' FrictionID_FOC_output.resetIntegrator=boolean(1); */
        rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = true;

        /* '<S1>:604:7' counter2 = counter2 + 1; */
        rtFrictionID_DW->qY = rtFrictionID_DW->counter2 + /*MW:OvSatOk*/ 1U;
        if (rtFrictionID_DW->counter2 + 1U < rtFrictionID_DW->counter2) {
          rtFrictionID_DW->qY = MAX_uint32_T;
        }

        rtFrictionID_DW->counter2 = rtFrictionID_DW->qY;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/FrictionID' */
}

/* Model initialize function */
void FrictionID_initialize(RT_MODEL_FrictionID_t *const rtFrictionID_M)
{
  ExtY_FrictionID_t *rtFrictionID_Y = (ExtY_FrictionID_t *)
    rtFrictionID_M->outputs;

  /* SystemInitialize for Chart: '<Root>/FrictionID' incorporates:
   *  Outport: '<Root>/FrictionID_FOC_output'
   *  Outport: '<Root>/FrictionID_output'
   */
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.d = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.q = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.i_dq_ref.zero = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.M_ref_FOC = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.activeState = 0U;
  rtFrictionID_Y->FrictionID_FOC_output.n_ref_FOC = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.enableFOC_torque = false;
  rtFrictionID_Y->FrictionID_FOC_output.enableFOC_speed = false;
  rtFrictionID_Y->FrictionID_FOC_output.enableFOC_current = false;
  rtFrictionID_Y->FrictionID_FOC_output.resetIntegrator = false;
  rtFrictionID_Y->FrictionID_FOC_output.Kp_id_out = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.Kp_iq_out = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.Kp_n_out = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.Ki_id_out = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.Ki_iq_out = 0.0F;
  rtFrictionID_Y->FrictionID_FOC_output.Ki_n_out = 0.0F;
  memset(&rtFrictionID_Y->FrictionID_output.measArrayTorque[0], 0, sizeof
         (real32_T) << 8U);
  memset(&rtFrictionID_Y->FrictionID_output.measArraySpeed[0], 0, sizeof
         (real32_T) << 8U);
  rtFrictionID_Y->FrictionID_output.BrkTorque = 0.0F;
  rtFrictionID_Y->FrictionID_output.CoulTorque = 0.0F;
  rtFrictionID_Y->FrictionID_output.ViscoTorque = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

#endif
