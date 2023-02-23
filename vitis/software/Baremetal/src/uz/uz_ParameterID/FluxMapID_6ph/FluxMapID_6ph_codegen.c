/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FluxMapID_6ph_codegen.c
 *
 * Code generated for Simulink model 'FluxMapID_6ph_codegen'.
 *
 * Model version                  : 3.50
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Feb 23 09:55:08 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#include "FluxMapID_6ph_codegen.h"
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

/* Named constants for Chart: '<S1>/AMMstate.Fluxmap' */
#define IN_AMMcollectData              ((uint8_T)1U)
#define IN_AMMcompleted                ((uint8_T)2U)
#define IN_AMMcooling                  ((uint8_T)3U)
#define IN_AMMheating                  ((uint8_T)4U)
#define IN_AMMnewRef                   ((uint8_T)5U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_initAMM                     ((uint8_T)6U)
#define IN_waitForCollectToFinish      ((uint8_T)7U)
#define IN_whatsNext                   ((uint8_T)8U)

/* Named constants for Chart: '<Root>/FluxMapID_6ph_codegen' */
#define IN_AMMstate                    ((uint8_T)1U)
#define IN_Waiting                     ((uint8_T)2U)

/* Forward declaration for local functions */
static void initParams(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
  ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);
static void RefreshDataRegister(DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW);
static real32_T identRes(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);
static void enter_atomic_AMMnewRef(uint16_T *activeState, real32_T *PI_d_ref,
  real32_T *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function initParams
 * This is used instead of "after(1.0,sec) to ensure the same transition time
 * independelty of the sampletime in the c-code
 */
static void initParams(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
  ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  real32_T tmp;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'initParams': '<S1>:651' */
  /* '<S1>:651:5' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  tmp = roundf(1.0F / rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_c = (uint32_T)tmp;
    } else {
      rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_c = 0U;
    }
  } else {
    rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_c = MAX_uint32_T;
  }

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:651:6' three_sec_transition_counter = uint32(3/GlobalConfig.sampleTimeISR); */
  tmp = roundf(3.0F / rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_k = (uint32_T)tmp;
    } else {
      rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_k = 0U;
    }
  } else {
    rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_k = MAX_uint32_T;
  }

  /* Inport: '<Root>/FluxMapIDConfig' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* '<S1>:651:7' collection_transition_counter = uint32(FluxMapIDConfig.AMMsampleTime/GlobalConfig.sampleTimeISR); */
  tmp = roundf(rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.AMMsampleTime /
               rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFluxMapID_6ph_codegen_DW->collection_transition_counter_m = (uint32_T)
        tmp;
    } else {
      rtFluxMapID_6ph_codegen_DW->collection_transition_counter_m = 0U;
    }
  } else {
    rtFluxMapID_6ph_codegen_DW->collection_transition_counter_m = MAX_uint32_T;
  }

  /*  initialize variables */
  /* '<S1>:651:9' vd1_counter 		= single(0.0); */
  rtFluxMapID_6ph_codegen_DW->vd1_counter = 0.0F;

  /* '<S1>:651:10' id1_counter        	= single(0.0); */
  rtFluxMapID_6ph_codegen_DW->id1_counter = 0.0F;

  /* '<S1>:651:11' vd2_counter 		= single(0.0); */
  rtFluxMapID_6ph_codegen_DW->vd2_counter = 0.0F;

  /* '<S1>:651:12' id2_counter        	= single(0.0); */
  rtFluxMapID_6ph_codegen_DW->id2_counter = 0.0F;

  /* '<S1>:651:13' i_d_R_online        = single(0.0); */
  rtFluxMapID_6ph_codegen_DW->i_d_R_online = 0.0F;

  /* '<S1>:651:14' R_s_array           = single(zeros(50,1)); */
  memset(&rtFluxMapID_6ph_codegen_DW->R_s_array[0], 0, 50U * sizeof(real32_T));

  /* '<S1>:651:15' counter = uint32(1); */
  rtFluxMapID_6ph_codegen_DW->counter = 1U;

  /* '<S1>:651:16' i_q_ref_AMM = single(0.0); */
  rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

  /* '<S1>:651:17' i_d_ref_AMM = single(0.0); */
  rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

  /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
   *  Inport: '<Root>/GlobalConfig'
   */
  /* '<S1>:651:18' IDstepsize_loc = single(FluxMapIDConfig.IDstepsize); */
  /* '<S1>:651:19' IQstepsize_loc = single(FluxMapIDConfig.IQstepsize); */
  /* Outputs */
  /* '<S1>:651:21' FluxMapID_FOC_output.n_ref_FOC         	= single(0.0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.n_ref_FOC = 0.0F;

  /* '<S1>:651:22' FluxMapID_FOC_output.i_dq_ref.d      	= single(0.0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;

  /* '<S1>:651:23' FluxMapID_FOC_output.i_dq_ref.q       	= single(0.0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;

  /* '<S1>:651:24' FluxMapID_FOC_output.i_dq_ref.zero      = single(0.0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.zero = 0.0F;

  /* '<S1>:651:25' FluxMapID_FOC_output.enableFOC_speed   	= boolean(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_speed = false;

  /* '<S1>:651:26' FluxMapID_FOC_output.enableFOC_current  = boolean(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = false;

  /* '<S1>:651:27' FluxMapID_FOC_output.resetIntegrator 	= boolean(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;

  /* '<S1>:651:28' FluxMapID_FOC_output.Kp_id_out          = single(GlobalConfig.Kp_id); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_id_out =
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Kp_id;

  /* '<S1>:651:29' FluxMapID_FOC_output.Kp_iq_out         	= single(GlobalConfig.Kp_iq); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_iq_out =
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Kp_iq;

  /* '<S1>:651:30' FluxMapID_FOC_output.Kp_n_out         	= single(GlobalConfig.Kp_n); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_n_out =
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Kp_n;

  /* '<S1>:651:31' FluxMapID_FOC_output.Ki_id_out         	= single(GlobalConfig.Ki_id); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_id_out =
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Ki_id;

  /* '<S1>:651:32' FluxMapID_FOC_output.Ki_iq_out        	= single(GlobalConfig.Ki_iq); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_iq_out =
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Ki_iq;

  /* '<S1>:651:33' FluxMapID_FOC_output.Ki_n_out          	= single(GlobalConfig.Ki_n); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_n_out =
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Ki_n;

  /* '<S1>:651:34' FluxMapID_FOC_output.activeState        = uint16(0); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 0U;

  /* Merge: '<S1>/ Merge 1' */
  /* '<S1>:651:35' finishedFluxMapID                       = boolean(0); */
  rtFluxMapID_6ph_codegen_DW->finishedFluxMapID = false;

  /* Inport: '<Root>/FluxMapIDConfig' */
  /* '<S1>:651:37' FluxMapID_output.R_s                    = single(FluxMapIDConfig.R_s_ref); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s =
    rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref;

  /* '<S1>:651:38' FluxMapID_output.WindingTemp            = single(FluxMapIDConfig.Temp_ref); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp =
    rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref;

  /* '<S1>:651:39' FluxMapID_output.external_Measurement_Flag = boolean(0); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.external_Measurement_Flag = false;
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function RefreshDataRegister
 */
static void RefreshDataRegister(DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW)
{
  uint16_T k;

  /* MATLAB Function 'RefreshDataRegister': '<S1>:690' */
  /* '<S1>:690:3' m=length(R_s_array); */
  /* '<S1>:690:4' for k= uint16(0):uint16(m-2) */
  for (k = 0; k < 49; k++) {
    /* '<S1>:690:5' R_s_array(m-k)=R_s_array(m-(k+1)); */
    rtFluxMapID_6ph_codegen_DW->R_s_array[49 - k] =
      rtFluxMapID_6ph_codegen_DW->R_s_array[48 - k];
  }
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function fun = identRes
 */
static real32_T identRes(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  int32_T k;
  real32_T tmp;
  real32_T vd1_counter_tmp;
  uint32_T qY;

  /* Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'identRes': '<S1>:669' */
  /* '<S1>:669:3' if(counter <= uint32(0.2/GlobalConfig.sampleTimeISR)) */
  vd1_counter_tmp = roundf(0.2F /
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (vd1_counter_tmp < 4.2949673E+9F) {
    if (vd1_counter_tmp >= 0.0F) {
      qY = (uint32_T)vd1_counter_tmp;
    } else {
      qY = 0U;
    }
  } else {
    qY = MAX_uint32_T;
  }

  if (rtFluxMapID_6ph_codegen_DW->counter <= qY) {
    /* Inport: '<Root>/FluxMapIDConfig' */
    /* meas */
    /* '<S1>:669:4' i_d_R_online = single(-FluxMapIDConfig.identRAmp); */
    rtFluxMapID_6ph_codegen_DW->i_d_R_online =
      -rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

    /* Inport: '<Root>/GlobalConfig' */
    /* '<S1>:669:5' if(counter >= uint32(0.1/GlobalConfig.sampleTimeISR) && counter < uint32(0.2/GlobalConfig.sampleTimeISR)) */
    tmp = roundf(0.1F /
                 rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
    if (tmp < 4.2949673E+9F) {
      if (tmp >= 0.0F) {
        qY = (uint32_T)tmp;
      } else {
        qY = 0U;
      }
    } else {
      qY = MAX_uint32_T;
    }

    if (rtFluxMapID_6ph_codegen_DW->counter >= qY) {
      if (vd1_counter_tmp < 4.2949673E+9F) {
        if (vd1_counter_tmp >= 0.0F) {
          qY = (uint32_T)vd1_counter_tmp;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

      if (rtFluxMapID_6ph_codegen_DW->counter < qY) {
        /* Inport: '<Root>/ActualValues' */
        /* '<S1>:669:6' vd1_counter = vd1_counter + ActualValues.v_dq.d; */
        rtFluxMapID_6ph_codegen_DW->vd1_counter +=
          rtFluxMapID_6ph_codegen_U->ActualValues.v_dq.d;

        /* '<S1>:669:7' id1_counter = id1_counter + ActualValues.i_dq.d; */
        rtFluxMapID_6ph_codegen_DW->id1_counter +=
          rtFluxMapID_6ph_codegen_U->ActualValues.i_dq.d;
      }
    }
  }

  /* '<S1>:669:11' if(counter > uint32(0.2/GlobalConfig.sampleTimeISR) && counter <= uint32(0.4/GlobalConfig.sampleTimeISR)) */
  if (vd1_counter_tmp < 4.2949673E+9F) {
    if (vd1_counter_tmp >= 0.0F) {
      qY = (uint32_T)vd1_counter_tmp;
    } else {
      qY = 0U;
    }
  } else {
    qY = MAX_uint32_T;
  }

  if (rtFluxMapID_6ph_codegen_DW->counter > qY) {
    /* Inport: '<Root>/GlobalConfig' */
    vd1_counter_tmp = roundf(0.4F /
      rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
    if (vd1_counter_tmp < 4.2949673E+9F) {
      if (vd1_counter_tmp >= 0.0F) {
        qY = (uint32_T)vd1_counter_tmp;
      } else {
        qY = 0U;
      }
    } else {
      qY = MAX_uint32_T;
    }

    if (rtFluxMapID_6ph_codegen_DW->counter <= qY) {
      /* Inport: '<Root>/FluxMapIDConfig' */
      /* '<S1>:669:12' i_d_R_online = single(FluxMapIDConfig.identRAmp); */
      rtFluxMapID_6ph_codegen_DW->i_d_R_online =
        rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

      /* Inport: '<Root>/GlobalConfig' */
      /* '<S1>:669:13' if(counter >= uint32(0.3/GlobalConfig.sampleTimeISR) && counter < uint32(0.4/GlobalConfig.sampleTimeISR)) */
      tmp = roundf(0.3F /
                   rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
      if (tmp < 4.2949673E+9F) {
        if (tmp >= 0.0F) {
          qY = (uint32_T)tmp;
        } else {
          qY = 0U;
        }
      } else {
        qY = MAX_uint32_T;
      }

      if (rtFluxMapID_6ph_codegen_DW->counter >= qY) {
        if (vd1_counter_tmp < 4.2949673E+9F) {
          if (vd1_counter_tmp >= 0.0F) {
            qY = (uint32_T)vd1_counter_tmp;
          } else {
            qY = 0U;
          }
        } else {
          qY = MAX_uint32_T;
        }

        if (rtFluxMapID_6ph_codegen_DW->counter < qY) {
          /* Inport: '<Root>/ActualValues' */
          /* '<S1>:669:14' vd2_counter = vd2_counter + ActualValues.v_dq.d; */
          rtFluxMapID_6ph_codegen_DW->vd2_counter +=
            rtFluxMapID_6ph_codegen_U->ActualValues.v_dq.d;

          /* '<S1>:669:15' id2_counter = id2_counter + ActualValues.i_dq.d; */
          rtFluxMapID_6ph_codegen_DW->id2_counter +=
            rtFluxMapID_6ph_codegen_U->ActualValues.i_dq.d;
        }
      }
    }
  }

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:669:19' if(counter == uint32(0.4/GlobalConfig.sampleTimeISR + 1) ) */
  vd1_counter_tmp = roundf(0.4F /
    rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR + 1.0F);
  if (vd1_counter_tmp < 4.2949673E+9F) {
    if (vd1_counter_tmp >= 0.0F) {
      qY = (uint32_T)vd1_counter_tmp;
    } else {
      qY = 0U;
    }
  } else {
    qY = MAX_uint32_T;
  }

  if (rtFluxMapID_6ph_codegen_DW->counter == qY) {
    /* Inport: '<Root>/FluxMapIDConfig' */
    /* '<S1>:669:20' i_d_R_online = single(-FluxMapIDConfig.identRAmp); */
    rtFluxMapID_6ph_codegen_DW->i_d_R_online =
      -rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

    /* Inport: '<Root>/GlobalConfig' */
    /* '<S1>:669:21' vd1_counter=vd1_counter/(0.1/GlobalConfig.sampleTimeISR); */
    vd1_counter_tmp = 0.1F /
      rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR;
    rtFluxMapID_6ph_codegen_DW->vd1_counter /= vd1_counter_tmp;

    /* '<S1>:669:22' id1_counter=id1_counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtFluxMapID_6ph_codegen_DW->id1_counter /= vd1_counter_tmp;

    /* '<S1>:669:23' vd2_counter=vd2_counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtFluxMapID_6ph_codegen_DW->vd2_counter /= vd1_counter_tmp;

    /* '<S1>:669:24' id2_counter=id2_counter/(0.1/GlobalConfig.sampleTimeISR); */
    rtFluxMapID_6ph_codegen_DW->id2_counter /= vd1_counter_tmp;

    /* '<S1>:669:25' R_s_array(1,1) = single((vd2_counter-vd1_counter)/(id2_counter-id1_counter)); */
    rtFluxMapID_6ph_codegen_DW->R_s_array[0] =
      (rtFluxMapID_6ph_codegen_DW->vd2_counter -
       rtFluxMapID_6ph_codegen_DW->vd1_counter) /
      (rtFluxMapID_6ph_codegen_DW->id2_counter -
       rtFluxMapID_6ph_codegen_DW->id1_counter);

    /* '<S1>:669:26' RefreshDataRegister; */
    RefreshDataRegister(rtFluxMapID_6ph_codegen_DW);

    /* '<S1>:669:27' FluxMapID_output.R_s = mean(R_s_array); */
    vd1_counter_tmp = rtFluxMapID_6ph_codegen_DW->R_s_array[0];
    for (k = 0; k < 49; k++) {
      vd1_counter_tmp += rtFluxMapID_6ph_codegen_DW->R_s_array[k + 1];
    }

    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s = vd1_counter_tmp / 50.0F;

    /* '<S1>:669:28' counter = uint32(1); */
    rtFluxMapID_6ph_codegen_DW->counter = 1U;
  }

  /* '<S1>:669:31' counter = counter + 1; */
  qY = rtFluxMapID_6ph_codegen_DW->counter + /*MW:OvSatOk*/ 1U;
  if (rtFluxMapID_6ph_codegen_DW->counter + 1U <
      rtFluxMapID_6ph_codegen_DW->counter) {
    qY = MAX_uint32_T;
  }

  rtFluxMapID_6ph_codegen_DW->counter = qY;

  /* '<S1>:669:32' fun = single(FluxMapID_output.R_s); */
  return rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s;
}

/* Function for Chart: '<S1>/AMMstate.Fluxmap' */
static void enter_atomic_AMMnewRef(uint16_T *activeState, real32_T *PI_d_ref,
  real32_T *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  real32_T y;

  /* Entry 'AMMnewRef': '<S2>:93' */
  /* '<S2>:93:4' counter_time = uint32(1); */
  rtFluxMapID_6ph_codegen_DW->counter_time = 1U;

  /* '<S2>:93:5' activeState = uint16(402); */
  *activeState = 402U;

  /* '<S2>:93:6' if((FluxMapIDConfig.IDstart + single(AMMn) * IDstepsize_loc) <= FluxMapIDConfig.IDstop) */
  y = (real32_T)rtFluxMapID_6ph_codegen_DW->AMMn *
    rtFluxMapID_6ph_codegen_DW->IDstepsize_loc + FluxMapIDConfig->IDstart;
  if (y <= FluxMapIDConfig->IDstop) {
    real32_T r;

    /* '<S2>:93:7' PI_d_ref = single(FluxMapIDConfig.IDstart + single(AMMn) * IDstepsize_loc); */
    *PI_d_ref = y;

    /* '<S2>:93:8' if(mod(single(AMMn),((abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart))/IDstepsize_loc)+1) == 0) */
    y = fabsf(FluxMapIDConfig->IDstop - FluxMapIDConfig->IDstart) /
      rtFluxMapID_6ph_codegen_DW->IDstepsize_loc + 1.0F;
    r = (real32_T)rtFluxMapID_6ph_codegen_DW->AMMn;
    if (y == 0.0F) {
      if (rtFluxMapID_6ph_codegen_DW->AMMn == 0.0F) {
        r = y;
      }
    } else if (rtFluxMapID_6ph_codegen_DW->AMMn == 0.0F) {
      r = 0.0F / y;
    } else {
      boolean_T rEQ0;
      r = fmodf((real32_T)rtFluxMapID_6ph_codegen_DW->AMMn, y);
      rEQ0 = (r == 0.0F);
      if ((!rEQ0) && (y > floorf(y))) {
        real32_T q;
        q = fabsf((real32_T)rtFluxMapID_6ph_codegen_DW->AMMn / y);
        rEQ0 = (fabsf(q - floorf(q + 0.5F)) <= 1.1920929E-7F * q);
      }

      if (rEQ0) {
        r = 0.0F;
      } else if (y < 0.0F) {
        r += y;
      }
    }

    if (r == 0.0F) {
      /* '<S2>:93:9' if((FluxMapIDConfig.IQstart + single(AMMj) * IQstepsize_loc) <= FluxMapIDConfig.IQstop) */
      y = (real32_T)rtFluxMapID_6ph_codegen_DW->AMMj *
        rtFluxMapID_6ph_codegen_DW->IQstepsize_loc + FluxMapIDConfig->IQstart;
      if (y <= FluxMapIDConfig->IQstop) {
        uint32_T qY;

        /* '<S2>:93:10' PI_q_ref = single(FluxMapIDConfig.IQstart + single(AMMj) * IQstepsize_loc); */
        *PI_q_ref = y;

        /* '<S2>:93:11' AMMj = AMMj + 1; */
        qY = rtFluxMapID_6ph_codegen_DW->AMMj + /*MW:OvSatOk*/ 1U;
        if (rtFluxMapID_6ph_codegen_DW->AMMj + 1U <
            rtFluxMapID_6ph_codegen_DW->AMMj) {
          qY = MAX_uint32_T;
        }

        rtFluxMapID_6ph_codegen_DW->AMMj = qY;
      } else {
        /* '<S2>:93:12' else */
        /* '<S2>:93:13' PI_d_ref = single(0.0); */
        *PI_d_ref = 0.0F;

        /* '<S2>:93:14' PI_q_ref = single(0.0); */
        *PI_q_ref = 0.0F;
      }
    }
  }
}

/* Model step function */
void FluxMapID_6ph_codegen_step(RT_MODEL_FluxMapID_6ph_codege_t *const
  rtFluxMapID_6ph_codegen_M)
{
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW =
    rtFluxMapID_6ph_codegen_M->dwork;
  ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U =
    (ExtU_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->inputs;
  ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y =
    (ExtY_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->outputs;

  /* Chart: '<Root>/FluxMapID_6ph_codegen' incorporates:
   *  Inport: '<Root>/ControlFlags'
   *  Inport: '<Root>/FluxMapIDConfig'
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/FluxMapID_FOC_output'
   */
  /* Gateway: FluxMapID_6ph_codegen */
  /* During: FluxMapID_6ph_codegen */
  if (rtFluxMapID_6ph_codegen_DW->is_active_c16_FluxMapID_6ph_cod == 0U) {
    /* Entry: FluxMapID_6ph_codegen */
    rtFluxMapID_6ph_codegen_DW->is_active_c16_FluxMapID_6ph_cod = 1U;

    /* Entry Internal: FluxMapID_6ph_codegen */
    /* Transition: '<S1>:597' */
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
    /* FluxMapID */
    /* donothing */
  } else if (rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen ==
             IN_AMMstate) {
    /* During 'AMMstate': '<S1>:590' */
    /* '<S1>:667:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.FluxMapID==0.... */
    /* '<S1>:667:2' || GlobalConfig.enableParameterID==0; */
    if (rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset ||
        (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.FluxMapID) ||
        (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.enableParameterID)) {
      /* Merge: '<S1>/ Merge ' */
      /* Transition: '<S1>:667' */
      /* '<S1>:667:3' enteredFluxMapID=boolean(0); */
      rtFluxMapID_6ph_codegen_DW->enteredFluxMapID = false;

      /* '<S1>:667:3' initParams; */
      initParams(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
                 rtFluxMapID_6ph_codegen_DW);

      /* Exit Internal 'AMMstate': '<S1>:590' */
      /* Exit Internal: Fluxmap */
      switch (rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer) {
       case IN_AMMcollectData:
        /* Exit 'AMMcollectData': '<S2>:99' */
        /* '<S2>:99:15' FluxMapID_output.external_Measurement_Flag=boolean(0); */
        rtFluxMapID_6ph_codegen_DW->FluxMapID_output.external_Measurement_Flag =
          false;
        rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
          IN_NO_ACTIVE_CHILD;
        break;

       case IN_AMMcompleted:
        /* Merge: '<S1>/ Merge 1' */
        /* Exit 'AMMcompleted': '<S2>:95' */
        /* '<S2>:95:15' finishedFluxMapID=boolean(1); */
        rtFluxMapID_6ph_codegen_DW->finishedFluxMapID = true;

        /* Merge: '<S1>/ Merge ' */
        /* '<S2>:95:16' enteredFluxMapID = boolean(0); */
        rtFluxMapID_6ph_codegen_DW->enteredFluxMapID = false;

        /* '<S2>:95:17' reset_FOC_output */
        rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
          IN_NO_ACTIVE_CHILD;
        break;

       case IN_AMMcooling:
        /* Exit 'AMMcooling': '<S2>:94' */
        /* '<S2>:94:8' PI_d_ref = i_d_ref_AMM_loc; */
        /* '<S2>:94:9' PI_q_ref = i_q_ref_AMM_loc; */
        rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
          IN_NO_ACTIVE_CHILD;
        break;

       case IN_AMMheating:
        /* Exit 'AMMheating': '<S2>:88' */
        /* '<S2>:88:8' PI_d_ref = i_d_ref_AMM_loc; */
        /* '<S2>:88:9' PI_q_ref = i_q_ref_AMM_loc; */
        rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
          IN_NO_ACTIVE_CHILD;
        break;

       case IN_waitForCollectToFinish:
        /* Exit 'waitForCollectToFinish': '<S2>:96' */
        rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
          IN_NO_ACTIVE_CHILD;
        break;

       default:
        rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
          IN_NO_ACTIVE_CHILD;
        break;
      }

      /* Exit 'AMMstate': '<S1>:590' */
      /* '<S1>:590:36' counter = uint32(1); */
      rtFluxMapID_6ph_codegen_DW->counter = 1U;

      /* '<S1>:590:37' i_q_ref_AMM = single(0.0); */
      rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

      /* '<S1>:590:38' i_d_ref_AMM = single(0.0); */
      rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;
      rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

      /* Entry 'Waiting': '<S1>:652' */
      /* wait for activation of */
      /* FluxMapID */
      /* donothing */
    } else {
      uint32_T exitPortIndex;

      /* '<S1>:590:15' if(FluxMapIDConfig.start_FM_ID==1) */
      if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
        /* '<S1>:590:16' FluxMapID_FOC_output.i_dq_ref.d=i_d_R_online+i_d_ref_AMM; */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d =
          rtFluxMapID_6ph_codegen_DW->i_d_R_online +
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

        /* '<S1>:590:17' FluxMapID_FOC_output.i_dq_ref.q=i_q_ref_AMM; */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q =
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;

        /* '<S1>:590:18' if(FluxMapIDConfig.identR == 1) */
        if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identR) {
          /* '<S1>:590:19' if(FluxMapID_FOC_output.activeState ~= 403) */
          if (rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState != 403)
          {
            /* '<S1>:590:20' FluxMapID_output.R_s = identRes; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s = identRes
              (rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_DW);
          }

          /* '<S1>:590:22' if(FluxMapIDConfig.R_s_ref ~= 0.0 && FluxMapIDConfig.Temp_ref ~= 0.0) */
          if ((rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref != 0.0F) &&
              (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref != 0.0F)) {
            /* '<S1>:590:23' FluxMapID_output.WindingTemp = ((FluxMapID_output.R_s/FluxMapIDConfig.R_s_ref)-1).... */
            /* '<S1>:590:24'                 *254.453+FluxMapIDConfig.Temp_ref; */
            rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp =
              (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s /
               rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref - 1.0F) *
              254.453F + rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref;

            /* . */
          }
        }

        /* '<S1>:590:27' if(FluxMapIDConfig.identR == 0) */
        if (!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identR) {
          /* '<S1>:590:28' i_d_R_online = single(0.0); */
          rtFluxMapID_6ph_codegen_DW->i_d_R_online = 0.0F;

          /* '<S1>:590:29' FluxMapID_output.WindingTemp= single(65); */
          rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp = 65.0F;
        }
      } else {
        /* '<S1>:590:31' else */
        /* '<S1>:590:32' FluxMapID_FOC_output.i_dq_ref.d=single(0); */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;

        /* '<S1>:590:33' FluxMapID_FOC_output.i_dq_ref.q=single(0); */
        rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;
      }

      /* During 'Fluxmap': '<S1>:704' */
      /* During: Fluxmap */
      switch (rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer) {
       case IN_AMMcollectData:
        /* During 'AMMcollectData': '<S2>:99' */
        /* '<S2>:91:1' sf_internal_predicateOutput = collection_transition_counter == counter_time; */
        if (rtFluxMapID_6ph_codegen_DW->collection_transition_counter_m ==
            rtFluxMapID_6ph_codegen_DW->counter_time) {
          /* Transition: '<S2>:91' */
          /* Exit 'AMMcollectData': '<S2>:99' */
          /* '<S2>:99:15' FluxMapID_output.external_Measurement_Flag=boolean(0); */
          rtFluxMapID_6ph_codegen_DW->FluxMapID_output.external_Measurement_Flag
            = false;
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_waitForCollectToFinish;

          /* Entry 'waitForCollectToFinish': '<S2>:96' */
          /* '<S2>:96:3' counter_time = uint32(1); */
          rtFluxMapID_6ph_codegen_DW->counter_time = 1U;

          /* '<S2>:96:4' activeState = uint16(404); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 404U;
        } else {
          /* '<S2>:99:13' counter_time = counter_time +1; */
          exitPortIndex = rtFluxMapID_6ph_codegen_DW->counter_time +
            /*MW:OvSatOk*/ 1U;
          if (rtFluxMapID_6ph_codegen_DW->counter_time + 1U <
              rtFluxMapID_6ph_codegen_DW->counter_time) {
            exitPortIndex = MAX_uint32_T;
          }

          rtFluxMapID_6ph_codegen_DW->counter_time = exitPortIndex;
        }
        break;

       case IN_AMMcompleted:
        /* During 'AMMcompleted': '<S2>:95' */
        /* '<S2>:92:1' sf_internal_predicateOutput = one_sec_transition_counter == counter_time; */
        if (rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_c ==
            rtFluxMapID_6ph_codegen_DW->counter_time) {
          /* Merge: '<S1>/ Merge 1' */
          /* Transition: '<S2>:92' */
          /* Exit 'AMMcompleted': '<S2>:95' */
          /* '<S2>:95:15' finishedFluxMapID=boolean(1); */
          rtFluxMapID_6ph_codegen_DW->finishedFluxMapID = true;

          /* Merge: '<S1>/ Merge ' */
          /* '<S2>:95:16' enteredFluxMapID = boolean(0); */
          rtFluxMapID_6ph_codegen_DW->enteredFluxMapID = false;

          /* '<S2>:95:17' reset_FOC_output */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_NO_ACTIVE_CHILD;
          rtFluxMapID_6ph_codegen_DW->exitPortIndex_m = 2U;
        } else {
          /* '<S2>:95:12' counter_time = counter_time +1; */
          exitPortIndex = rtFluxMapID_6ph_codegen_DW->counter_time +
            /*MW:OvSatOk*/ 1U;
          if (rtFluxMapID_6ph_codegen_DW->counter_time + 1U <
              rtFluxMapID_6ph_codegen_DW->counter_time) {
            exitPortIndex = MAX_uint32_T;
          }

          rtFluxMapID_6ph_codegen_DW->counter_time = exitPortIndex;

          /* '<S2>:95:13' resetIntegrator=boolean(1); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = true;
        }
        break;

       case IN_AMMcooling:
        /* During 'AMMcooling': '<S2>:94' */
        /* '<S2>:105:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp <= 60; */
        if (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp <= 60.0F) {
          /* Transition: '<S2>:105' */
          /* Exit 'AMMcooling': '<S2>:94' */
          /* '<S2>:94:8' PI_d_ref = i_d_ref_AMM_loc; */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM =
            rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM_loc;

          /* '<S2>:94:9' PI_q_ref = i_q_ref_AMM_loc; */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM =
            rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM_loc;
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMnewRef;
          enter_atomic_AMMnewRef
            (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
             &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
             &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
             &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
             rtFluxMapID_6ph_codegen_DW);
        }
        break;

       case IN_AMMheating:
        /* During 'AMMheating': '<S2>:88' */
        /* '<S2>:106:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >= 60; */
        if (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp >= 60.0F) {
          /* Transition: '<S2>:106' */
          /* Exit 'AMMheating': '<S2>:88' */
          /* '<S2>:88:8' PI_d_ref = i_d_ref_AMM_loc; */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM =
            rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM_loc;

          /* '<S2>:88:9' PI_q_ref = i_q_ref_AMM_loc; */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM =
            rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM_loc;
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMnewRef;
          enter_atomic_AMMnewRef
            (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
             &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
             &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
             &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
             rtFluxMapID_6ph_codegen_DW);
        }
        break;

       case IN_AMMnewRef:
        /* During 'AMMnewRef': '<S2>:93' */
        /* '<S2>:109:1' sf_internal_predicateOutput = three_sec_transition_counter == counter_time; */
        if (rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_k ==
            rtFluxMapID_6ph_codegen_DW->counter_time) {
          /* Transition: '<S2>:109' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMcollectData;

          /* Entry 'AMMcollectData': '<S2>:99' */
          /* '<S2>:99:3' counter_time = uint32(1); */
          rtFluxMapID_6ph_codegen_DW->counter_time = 1U;

          /* '<S2>:99:4' activeState = uint16(403); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 403U;

          /* '<S2>:99:5' repetitionCounter = repetitionCounter + 1; */
          exitPortIndex = rtFluxMapID_6ph_codegen_DW->repetitionCounter +
            /*MW:OvSatOk*/ 1U;
          if (rtFluxMapID_6ph_codegen_DW->repetitionCounter + 1U <
              rtFluxMapID_6ph_codegen_DW->repetitionCounter) {
            exitPortIndex = MAX_uint32_T;
          }

          rtFluxMapID_6ph_codegen_DW->repetitionCounter = exitPortIndex;

          /* i_d_R_online = single(0.0); */
          /* '<S2>:99:7' if(AMMn >= (NumberOfIDpoints-1)) */
          exitPortIndex = rtFluxMapID_6ph_codegen_DW->NumberOfIDpoints -
            /*MW:OvSatOk*/ 1U;
          if (rtFluxMapID_6ph_codegen_DW->NumberOfIDpoints - 1U >
              rtFluxMapID_6ph_codegen_DW->NumberOfIDpoints) {
            exitPortIndex = 0U;
          }

          if (rtFluxMapID_6ph_codegen_DW->AMMn >= exitPortIndex) {
            /* '<S2>:99:8' AMMn = uint32(0); */
            rtFluxMapID_6ph_codegen_DW->AMMn = 0U;
          } else {
            /* '<S2>:99:9' else */
            /* '<S2>:99:10' AMMn = AMMn + 1; */
            exitPortIndex = rtFluxMapID_6ph_codegen_DW->AMMn + /*MW:OvSatOk*/ 1U;
            if (rtFluxMapID_6ph_codegen_DW->AMMn + 1U <
                rtFluxMapID_6ph_codegen_DW->AMMn) {
              exitPortIndex = MAX_uint32_T;
            }

            rtFluxMapID_6ph_codegen_DW->AMMn = exitPortIndex;
          }

          /* '<S2>:99:12' FluxMapID_output.external_Measurement_Flag=boolean(1); */
          rtFluxMapID_6ph_codegen_DW->FluxMapID_output.external_Measurement_Flag
            = true;
        } else {
          /* '<S2>:93:18' counter_time = counter_time +1; */
          exitPortIndex = rtFluxMapID_6ph_codegen_DW->counter_time +
            /*MW:OvSatOk*/ 1U;
          if (rtFluxMapID_6ph_codegen_DW->counter_time + 1U <
              rtFluxMapID_6ph_codegen_DW->counter_time) {
            exitPortIndex = MAX_uint32_T;
          }

          rtFluxMapID_6ph_codegen_DW->counter_time = exitPortIndex;
        }
        break;

       case IN_initAMM:
        /* During 'initAMM': '<S2>:90' */
        /* '<S2>:98:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > 70 && .... */
        /* '<S2>:98:2' FluxMapIDConfig.start_FM_ID==1; */
        /* . */
        if ((rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp > 70.0F) &&
            rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
          /* Transition: '<S2>:98' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMcooling;

          /* Entry 'AMMcooling': '<S2>:94' */
          /* '<S2>:94:4' activeState = uint16(410); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 410U;

          /* '<S2>:94:5' PI_d_ref = single(0.0); */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

          /* '<S2>:94:6' PI_q_ref = single(0.0); */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

          /* '<S2>:100:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < 60 && .... */
          /* '<S2>:100:2' FluxMapIDConfig.start_FM_ID==1; */
          /* . */
        } else if ((rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp <
                    60.0F) &&
                   rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
          /* Transition: '<S2>:100' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMheating;

          /* Entry 'AMMheating': '<S2>:88' */
          /* '<S2>:88:4' activeState = uint16(420); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 420U;

          /* '<S2>:88:5' PI_q_ref = single(FluxMapIDConfig.IQstop); */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM =
            rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IQstop;

          /* '<S2>:88:6' PI_d_ref = single(FluxMapIDConfig.IDstart); */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM =
            rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IDstart;

          /* '<S2>:102:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=60 && .... */
          /* '<S2>:102:2' FluxMapID_output.WindingTemp <=70 && .... */
          /* '<S2>:102:3' FluxMapIDConfig.start_FM_ID==1; */
          /* . */
        } else if ((rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp >=
                    60.0F) &&
                   (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp <=
                    70.0F) &&
                   rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
          /* Transition: '<S2>:102' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMnewRef;
          enter_atomic_AMMnewRef
            (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
             &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
             &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
             &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
             rtFluxMapID_6ph_codegen_DW);
        }
        break;

       case IN_waitForCollectToFinish:
        /* During 'waitForCollectToFinish': '<S2>:96' */
        /* '<S2>:110:1' sf_internal_predicateOutput = three_sec_transition_counter == counter_time; */
        if (rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_k ==
            rtFluxMapID_6ph_codegen_DW->counter_time) {
          /* Transition: '<S2>:110' */
          /* Exit 'waitForCollectToFinish': '<S2>:96' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_whatsNext;

          /* Entry 'whatsNext': '<S2>:103' */
          /* '<S2>:103:3' i_d_ref_AMM_loc = PI_d_ref; */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM_loc =
            rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

          /* '<S2>:103:4' i_q_ref_AMM_loc = PI_q_ref; */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM_loc =
            rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
        } else {
          /* '<S2>:96:6' counter_time = counter_time +1; */
          exitPortIndex = rtFluxMapID_6ph_codegen_DW->counter_time +
            /*MW:OvSatOk*/ 1U;
          if (rtFluxMapID_6ph_codegen_DW->counter_time + 1U <
              rtFluxMapID_6ph_codegen_DW->counter_time) {
            exitPortIndex = MAX_uint32_T;
          }

          rtFluxMapID_6ph_codegen_DW->counter_time = exitPortIndex;
        }
        break;

       default:
        /* During 'whatsNext': '<S2>:103' */
        /* '<S2>:108:1' sf_internal_predicateOutput = repetitionCounter >= NumberOfPoints; */
        if (rtFluxMapID_6ph_codegen_DW->repetitionCounter >=
            rtFluxMapID_6ph_codegen_DW->NumberOfPoints) {
          /* Transition: '<S2>:108' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMcompleted;

          /* Entry 'AMMcompleted': '<S2>:95' */
          /* '<S2>:95:4' counter_time = uint32(1); */
          rtFluxMapID_6ph_codegen_DW->counter_time = 1U;

          /* '<S2>:95:5' activeState = uint16(450); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 450U;

          /* '<S2>:95:6' AMMn = uint32(0); */
          rtFluxMapID_6ph_codegen_DW->AMMn = 0U;

          /* '<S2>:95:7' AMMj = uint32(0); */
          rtFluxMapID_6ph_codegen_DW->AMMj = 0U;

          /* '<S2>:95:8' repetitionCounter = uint32(0); */
          rtFluxMapID_6ph_codegen_DW->repetitionCounter = 0U;

          /* '<S2>:95:9' PI_d_ref = single(0.0); */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

          /* '<S2>:95:10' PI_q_ref = single(0.0); */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

          /* '<S2>:107:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > 70; */
        } else if (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp >
                   70.0F) {
          /* Transition: '<S2>:107' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMcooling;

          /* Entry 'AMMcooling': '<S2>:94' */
          /* '<S2>:94:4' activeState = uint16(410); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 410U;

          /* '<S2>:94:5' PI_d_ref = single(0.0); */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

          /* '<S2>:94:6' PI_q_ref = single(0.0); */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

          /* '<S2>:101:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < 60; */
        } else if (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp <
                   60.0F) {
          /* Transition: '<S2>:101' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMheating;

          /* Entry 'AMMheating': '<S2>:88' */
          /* '<S2>:88:4' activeState = uint16(420); */
          rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 420U;

          /* '<S2>:88:5' PI_q_ref = single(FluxMapIDConfig.IQstop); */
          rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM =
            rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IQstop;

          /* '<S2>:88:6' PI_d_ref = single(FluxMapIDConfig.IDstart); */
          rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM =
            rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IDstart;

          /* '<S2>:104:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=60 && FluxMapID_output.WindingTemp <= 70; */
        } else if ((rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp >=
                    60.0F) &&
                   (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp <=
                    70.0F)) {
          /* Transition: '<S2>:104' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_AMMnewRef;
          enter_atomic_AMMnewRef
            (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
             &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
             &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
             &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
             rtFluxMapID_6ph_codegen_DW);
        }
        break;
      }

      exitPortIndex = rtFluxMapID_6ph_codegen_DW->exitPortIndex_m;
      rtFluxMapID_6ph_codegen_DW->exitPortIndex_m = 0U;
      if (exitPortIndex == 2U) {
        /* Transition: '<S1>:706' */
        /* Exit Internal: Fluxmap */
        switch (rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer) {
         case IN_AMMcollectData:
          /* Exit 'AMMcollectData': '<S2>:99' */
          /* '<S2>:99:15' FluxMapID_output.external_Measurement_Flag=boolean(0); */
          rtFluxMapID_6ph_codegen_DW->FluxMapID_output.external_Measurement_Flag
            = false;
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_AMMcompleted:
          /* Merge: '<S1>/ Merge 1' */
          /* Exit 'AMMcompleted': '<S2>:95' */
          /* '<S2>:95:15' finishedFluxMapID=boolean(1); */
          rtFluxMapID_6ph_codegen_DW->finishedFluxMapID = true;

          /* Merge: '<S1>/ Merge ' */
          /* '<S2>:95:16' enteredFluxMapID = boolean(0); */
          rtFluxMapID_6ph_codegen_DW->enteredFluxMapID = false;

          /* '<S2>:95:17' reset_FOC_output */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_AMMcooling:
          /* Exit 'AMMcooling': '<S2>:94' */
          /* '<S2>:94:8' PI_d_ref = i_d_ref_AMM_loc; */
          /* '<S2>:94:9' PI_q_ref = i_q_ref_AMM_loc; */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_AMMheating:
          /* Exit 'AMMheating': '<S2>:88' */
          /* '<S2>:88:8' PI_d_ref = i_d_ref_AMM_loc; */
          /* '<S2>:88:9' PI_q_ref = i_q_ref_AMM_loc; */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_NO_ACTIVE_CHILD;
          break;

         case IN_waitForCollectToFinish:
          /* Exit 'waitForCollectToFinish': '<S2>:96' */
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_NO_ACTIVE_CHILD;
          break;

         default:
          rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer =
            IN_NO_ACTIVE_CHILD;
          break;
        }

        /* Exit 'AMMstate': '<S1>:590' */
        /* '<S1>:590:36' counter = uint32(1); */
        rtFluxMapID_6ph_codegen_DW->counter = 1U;

        /* '<S1>:590:37' i_q_ref_AMM = single(0.0); */
        rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

        /* '<S1>:590:38' i_d_ref_AMM = single(0.0); */
        rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;
        rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

        /* Entry 'Waiting': '<S1>:652' */
        /* wait for activation of */
        /* FluxMapID */
        /* donothing */
      }
    }

    /* During 'Waiting': '<S1>:652' */
    /* '<S1>:656:1' sf_internal_predicateOutput = ControlFlags.startFluxMapID==1 && .... */
    /* '<S1>:656:2' GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1; */
    /* . */
  } else if (rtFluxMapID_6ph_codegen_U->ControlFlags.startFluxMapID &&
             (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset) &&
             rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    uint64_T tmp;
    real32_T tmp_0;
    uint32_T exitPortIndex;

    /* Transition: '<S1>:656' */
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_AMMstate;

    /* Entry 'AMMstate': '<S1>:590' */
    /* '<S1>:590:4' initParams; */
    initParams(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
               rtFluxMapID_6ph_codegen_DW);

    /* Merge: '<S1>/ Merge ' */
    /* '<S1>:590:5' enteredFluxMapID = boolean(1); */
    rtFluxMapID_6ph_codegen_DW->enteredFluxMapID = true;

    /* '<S1>:590:6' FluxMapID_FOC_output.enableFOC_current=boolean(1); */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = true;

    /* '<S1>:590:7' FluxMapID_FOC_output.activeState = uint16(400); */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 400U;

    /* '<S1>:590:8' if(FluxMapIDConfig.IDstepsize==0) */
    /* '<S1>:590:11' if(FluxMapIDConfig.IQstepsize==0) */
    /* Entry Internal 'AMMstate': '<S1>:590' */
    /* Transition: '<S1>:708' */
    rtFluxMapID_6ph_codegen_DW->repetitionCounter = 0U;
    rtFluxMapID_6ph_codegen_DW->counter_time = 0U;
    rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM_loc = 0.0F;
    rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM_loc = 0.0F;
    rtFluxMapID_6ph_codegen_DW->AMMn = 0U;
    rtFluxMapID_6ph_codegen_DW->AMMj = 0U;
    rtFluxMapID_6ph_codegen_DW->IQstepsize_loc = 0.0F;
    rtFluxMapID_6ph_codegen_DW->IDstepsize_loc = 0.0F;

    /* Chart: '<S1>/AMMstate.Fluxmap' incorporates:
     *  Inport: '<Root>/FluxMapIDConfig'
     *  Outport: '<Root>/FluxMapID_FOC_output'
     */
    /* Entry: Fluxmap */
    /* Entry Internal: Fluxmap */
    /* Transition: '<S2>:97' */
    rtFluxMapID_6ph_codegen_DW->is_c14_Subchart_FluxMapID_refer = IN_initAMM;

    /* Entry 'initAMM': '<S2>:90' */
    /* '<S2>:90:4' activeState = uint16(401); */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 401U;

    /* '<S2>:90:5' if(FluxMapIDConfig.IDstepsize==0) */
    if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IDstepsize == 0.0F) {
      /* '<S2>:90:6' IDstepsize_loc = single(1.0); */
      rtFluxMapID_6ph_codegen_DW->IDstepsize_loc = 1.0F;
    }

    /* '<S2>:90:8' if(FluxMapIDConfig.IQstepsize==0) */
    if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IQstepsize == 0.0F) {
      /* '<S2>:90:9' IQstepsize_loc = single(1.0); */
      rtFluxMapID_6ph_codegen_DW->IQstepsize_loc = 1.0F;
    }

    /* '<S2>:90:11' NumberOfIDpoints = uint32(abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart)/IDstepsize_loc+1); */
    tmp_0 = roundf(fabsf(rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IDstop -
                         rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IDstart) /
                   rtFluxMapID_6ph_codegen_DW->IDstepsize_loc + 1.0F);
    if (tmp_0 < 4.2949673E+9F) {
      if (tmp_0 >= 0.0F) {
        rtFluxMapID_6ph_codegen_DW->NumberOfIDpoints = (uint32_T)tmp_0;
      } else {
        rtFluxMapID_6ph_codegen_DW->NumberOfIDpoints = 0U;
      }
    } else {
      rtFluxMapID_6ph_codegen_DW->NumberOfIDpoints = MAX_uint32_T;
    }

    /* '<S2>:90:12' NumberOfIQpoints = uint32(abs(FluxMapIDConfig.IQstop-FluxMapIDConfig.IQstart)/IQstepsize_loc+1); */
    /* '<S2>:90:13' NumberOfPoints = uint32(NumberOfIDpoints*NumberOfIQpoints); */
    tmp_0 = roundf(fabsf(rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IQstop -
                         rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.IQstart) /
                   rtFluxMapID_6ph_codegen_DW->IQstepsize_loc + 1.0F);
    if (tmp_0 < 4.2949673E+9F) {
      if (tmp_0 >= 0.0F) {
        exitPortIndex = (uint32_T)tmp_0;
      } else {
        exitPortIndex = 0U;
      }
    } else {
      exitPortIndex = MAX_uint32_T;
    }

    tmp = (uint64_T)rtFluxMapID_6ph_codegen_DW->NumberOfIDpoints * exitPortIndex;
    if (tmp > 4294967295ULL) {
      tmp = 4294967295ULL;
    }

    rtFluxMapID_6ph_codegen_DW->NumberOfPoints = (uint32_T)tmp;

    /* End of Chart: '<S1>/AMMstate.Fluxmap' */

    /* '<S1>:680:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
  } else if (rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset) {
    /* Merge: '<S1>/ Merge ' */
    /* Transition: '<S1>:680' */
    /* '<S1>:680:1' finishedFluxMapID=boolean(0); */
    /* '<S1>:680:2' enteredFluxMapID=boolean(0); */
    rtFluxMapID_6ph_codegen_DW->enteredFluxMapID = false;

    /* '<S1>:680:2' initParams; */
    initParams(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
               rtFluxMapID_6ph_codegen_DW);
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
    /* FluxMapID */
    /* donothing */
  }

  /* End of Chart: '<Root>/FluxMapID_6ph_codegen' */

  /* Outport: '<Root>/finishedFluxMapID' */
  rtFluxMapID_6ph_codegen_Y->finishedFluxMapID =
    rtFluxMapID_6ph_codegen_DW->finishedFluxMapID;

  /* Outport: '<Root>/enteredFluxMapID' */
  rtFluxMapID_6ph_codegen_Y->enteredFluxMapID =
    rtFluxMapID_6ph_codegen_DW->enteredFluxMapID;

  /* Outport: '<Root>/FluxMapID_output' */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_output =
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output;
}

/* Model initialize function */
void FluxMapID_6ph_codegen_initialize(RT_MODEL_FluxMapID_6ph_codege_t *const
  rtFluxMapID_6ph_codegen_M)
{
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW =
    rtFluxMapID_6ph_codegen_M->dwork;
  ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y =
    (ExtY_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->outputs;

  /* SystemInitialize for Chart: '<Root>/FluxMapID_6ph_codegen' incorporates:
   *  Outport: '<Root>/FluxMapID_FOC_output'
   */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.d = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.q = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.i_dq_ref.zero = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 0U;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.n_ref_FOC = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_speed = false;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = false;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_id_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_iq_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Kp_n_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_id_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_iq_out = 0.0F;
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.Ki_n_out = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.external_Measurement_Flag = false;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s = 0.0F;
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp = 0.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
#endif