/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FluxMapID_6ph_codegen.c
 *
 * Code generated for Simulink model 'FluxMapID_6ph_codegen'.
 *
 * Model version                  : 3.73
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Mar 23 15:14:24 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-R
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Passed (10), Warnings (2), Error (0)
 */


#include "FluxMapID_6ph_codegen.h"
#include "../mean_GqoxPyM9.h"
#include "../../uz_global_configuration.h"
#if UZ_PARAMETERID_6PH_MAX_INSTANCES > 0U

/* Named constants for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
#define IN_AMMcollectData              ((uint8_T)1U)
#define IN_AMMcompleted                ((uint8_T)2U)
#define IN_AMMcooling                  ((uint8_T)3U)
#define IN_AMMheating                  ((uint8_T)4U)
#define IN_AMMnewRef                   ((uint8_T)5U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_initAMM                     ((uint8_T)6U)

/* Named constants for Chart: '<Root>/FluxMapID_6ph_codegen' */
#define IN_AMMstate                    ((uint8_T)1U)
#define IN_Fluxmap                     ((uint8_T)1U)
#define IN_IdentificationDQ            ((uint8_T)1U)
#define IN_IdentificationXY            ((uint8_T)2U)
#define IN_IdentificationXY1           ((uint8_T)3U)
#define IN_NO_ACTIVE_CHILD_o           ((uint8_T)0U)
#define IN_Wait_select_subsystem       ((uint8_T)4U)
#define IN_Waiting                     ((uint8_T)2U)

/* Exported functions */
extern uint32_T Fluxmap_getExitPortIndex(DW_AMMstateIdentificationDQFl_t
  *localDW);
extern void Fluxmap_during(uint16_T *activeState, real32_T *PI_d_ref, real32_T
  *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig, uint32_T
  one_sec_transition_counter, uint32_T three_sec_transition_counter,
  uz_ParaID_FluxMapID_output_t *FluxMapID_output, const uz_3ph_dq_t
  *actual_voltages, real32_T omega_el, boolean_T feedback_printed, boolean_T
  *finished_calculation, uz_3ph_dq_t *mean_voltages, real32_T *mean_omega_el,
  uz_3ph_dq_t *mean_currents, uint32_T *repetitionCounter, const uz_3ph_dq_t
  *actual_currents, DW_AMMstateIdentificationDQFl_t *localDW);
extern void Fluxmap_enter(uint16_T *activeState, const
  uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig, DW_AMMstateIdentificationDQFl_t *
  localDW);
extern void Fluxmap_exit(real32_T *PI_d_ref, real32_T *PI_q_ref,
  uz_ParaID_FluxMapID_output_t *FluxMapID_output, boolean_T
  *finished_calculation, DW_AMMstateIdentificationDQFl_t *localDW);
extern void Fluxmap_init(DW_AMMstateIdentificationDQFl_t *localDW);

/* Forward declaration for local functions */
static void enter_atomic_AMMnewRef(uint16_T *activeState, real32_T *PI_d_ref,
  real32_T *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_AMMstateIdentificationDQFl_t *localDW);

/* Forward declaration for local functions */
static void initParams(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
  ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);
static void enter_atomic_Wait_select_subsys(ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y, DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW);
static void RefreshDataRegister(DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW);
static real32_T identRes(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
  DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);
static void AMMstate(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                     ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                     DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
uint32_T Fluxmap_getExitPortIndex(DW_AMMstateIdentificationDQFl_t *localDW)
{
  uint32_T b;
  b = localDW->exitPortIndex;
  localDW->exitPortIndex = 0U;
  return b;
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
static void enter_atomic_AMMnewRef(uint16_T *activeState, real32_T *PI_d_ref,
  real32_T *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_AMMstateIdentificationDQFl_t *localDW)
{
  real32_T y;

  /* Entry 'AMMnewRef': '<S2>:93' */
  /* '<S2>:93:4' counter_time = uint32(1); */
  localDW->counter_time = 1U;

  /* '<S2>:93:5' activeState = uint16(402); */
  *activeState = 402U;

  /* '<S2>:93:6' if((FluxMapIDConfig.IDstart + single(AMMn) * IDstepsize_loc) <= FluxMapIDConfig.IDstop) */
  y = (real32_T)localDW->AMMn * localDW->IDstepsize_loc +
    FluxMapIDConfig->IDstart;
  if (y <= FluxMapIDConfig->IDstop) {
    real32_T r;

    /* '<S2>:93:7' PI_d_ref = single(FluxMapIDConfig.IDstart + single(AMMn) * IDstepsize_loc); */
    *PI_d_ref = y;

    /* '<S2>:93:8' if(mod(single(AMMn),((abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart))/IDstepsize_loc)+1) == 0) */
    y = fabsf(FluxMapIDConfig->IDstop - FluxMapIDConfig->IDstart) /
      localDW->IDstepsize_loc + 1.0F;
    r = (real32_T)localDW->AMMn;
    if (y == 0.0F) {
      if (localDW->AMMn == 0.0F) {
        r = y;
      }
    } else if (localDW->AMMn == 0.0F) {
      r = 0.0F / y;
    } else {
      boolean_T rEQ0;
      r = fmodf((real32_T)localDW->AMMn, y);
      rEQ0 = (r == 0.0F);
      if ((!rEQ0) && (y > floorf(y))) {
        real32_T q;
        q = fabsf((real32_T)localDW->AMMn / y);
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
      y = (real32_T)localDW->AMMj * localDW->IQstepsize_loc +
        FluxMapIDConfig->IQstart;
      if (y <= FluxMapIDConfig->IQstop) {
        uint32_T qY;

        /* '<S2>:93:10' PI_q_ref = single(FluxMapIDConfig.IQstart + single(AMMj) * IQstepsize_loc); */
        *PI_q_ref = y;

        /* '<S2>:93:11' AMMj = AMMj + 1; */
        qY = localDW->AMMj + /*MW:OvSatOk*/ 1U;
        if (localDW->AMMj + 1U < localDW->AMMj) {
          qY = MAX_uint32_T;
        }

        localDW->AMMj = qY;
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

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
void Fluxmap_during(uint16_T *activeState, real32_T *PI_d_ref, real32_T
                    *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t
                    *FluxMapIDConfig, uint32_T one_sec_transition_counter,
                    uint32_T three_sec_transition_counter,
                    uz_ParaID_FluxMapID_output_t *FluxMapID_output, const
                    uz_3ph_dq_t *actual_voltages, real32_T omega_el, boolean_T
                    feedback_printed, boolean_T *finished_calculation,
                    uz_3ph_dq_t *mean_voltages, real32_T *mean_omega_el,
                    uz_3ph_dq_t *mean_currents, uint32_T *repetitionCounter,
                    const uz_3ph_dq_t *actual_currents,
                    DW_AMMstateIdentificationDQFl_t *localDW)
{
  int32_T i;
  uint32_T qY;
  boolean_T guard1 = false;

  /* During: Fluxmap */
  guard1 = false;
  switch (localDW->is_c14_Subchart_FluxMapID_refer) {
   case IN_AMMcollectData:
    /* During 'AMMcollectData': '<S2>:99' */
    /* '<S2>:91:1' sf_internal_predicateOutput = feedback_printed == true; */
    if (feedback_printed) {
      /* Transition: '<S2>:91' */
      /* '<S2>:108:1' sf_internal_predicateOutput = repetitionCounter >= NumberOfPoints; */
      if (*repetitionCounter >= localDW->NumberOfPoints) {
        /* Transition: '<S2>:108' */
        /* Exit 'AMMcollectData': '<S2>:99' */
        /* '<S2>:99:48' FluxMapID_output.external_Measurement_Flag=boolean(0); */
        FluxMapID_output->external_Measurement_Flag = false;

        /* '<S2>:99:49' finished_calculation = false; */
        *finished_calculation = false;
        localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcompleted;

        /* Entry 'AMMcompleted': '<S2>:95' */
        /* '<S2>:95:4' counter_time = uint32(1); */
        localDW->counter_time = 1U;

        /* '<S2>:95:5' PI_d_ref = single(0.0); */
        *PI_d_ref = 0.0F;

        /* '<S2>:95:6' PI_q_ref = single(0.0); */
        *PI_q_ref = 0.0F;

        /* '<S2>:154:1' sf_internal_predicateOutput = repetitionCounter < NumberOfPoints; */
      } else if (*repetitionCounter < localDW->NumberOfPoints) {
        /* Transition: '<S2>:154' */
        /* '<S2>:107:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > 70; */
        if (FluxMapID_output->WindingTemp > 70.0F) {
          /* Transition: '<S2>:107' */
          /* Exit 'AMMcollectData': '<S2>:99' */
          /* '<S2>:99:48' FluxMapID_output.external_Measurement_Flag=boolean(0); */
          FluxMapID_output->external_Measurement_Flag = false;

          /* '<S2>:99:49' finished_calculation = false; */
          *finished_calculation = false;
          localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcooling;

          /* Entry 'AMMcooling': '<S2>:94' */
          /* '<S2>:94:4' activeState = uint16(410); */
          *activeState = 410U;

          /* '<S2>:94:5' i_d_ref_AMM_loc = PI_d_ref; */
          localDW->i_d_ref_AMM_loc_h = *PI_d_ref;

          /* '<S2>:94:6' i_q_ref_AMM_loc = PI_q_ref; */
          localDW->i_q_ref_AMM_loc_p = *PI_q_ref;

          /* '<S2>:94:7' PI_d_ref = single(0.0); */
          *PI_d_ref = 0.0F;

          /* '<S2>:94:8' PI_q_ref = single(0.0); */
          *PI_q_ref = 0.0F;

          /* '<S2>:104:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=60 && FluxMapID_output.WindingTemp <= 70; */
        } else if ((FluxMapID_output->WindingTemp >= 60.0F) &&
                   (FluxMapID_output->WindingTemp <= 70.0F)) {
          /* Transition: '<S2>:104' */
          /* Exit 'AMMcollectData': '<S2>:99' */
          /* '<S2>:99:48' FluxMapID_output.external_Measurement_Flag=boolean(0); */
          FluxMapID_output->external_Measurement_Flag = false;

          /* '<S2>:99:49' finished_calculation = false; */
          *finished_calculation = false;
          localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
          enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref,
            FluxMapIDConfig, localDW);

          /* '<S2>:101:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < 60; */
        } else if (FluxMapID_output->WindingTemp < 60.0F) {
          /* Transition: '<S2>:101' */
          /* Exit 'AMMcollectData': '<S2>:99' */
          /* '<S2>:99:48' FluxMapID_output.external_Measurement_Flag=boolean(0); */
          FluxMapID_output->external_Measurement_Flag = false;

          /* '<S2>:99:49' finished_calculation = false; */
          *finished_calculation = false;
          localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMheating;

          /* Entry 'AMMheating': '<S2>:88' */
          /* '<S2>:88:4' activeState = uint16(420); */
          *activeState = 420U;

          /* '<S2>:88:5' i_d_ref_AMM_loc = PI_d_ref; */
          localDW->i_d_ref_AMM_loc = *PI_d_ref;

          /* '<S2>:88:6' i_q_ref_AMM_loc = PI_q_ref; */
          localDW->i_q_ref_AMM_loc = *PI_q_ref;

          /* '<S2>:88:7' PI_q_ref = single(FluxMapIDConfig.IQstop); */
          *PI_q_ref = FluxMapIDConfig->IQstop;

          /* '<S2>:88:8' PI_d_ref = single(FluxMapIDConfig.IDstart); */
          *PI_d_ref = FluxMapIDConfig->IDstart;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    break;

   case IN_AMMcompleted:
    /* During 'AMMcompleted': '<S2>:95' */
    /* '<S2>:92:1' sf_internal_predicateOutput = one_sec_transition_counter == counter_time; */
    if (one_sec_transition_counter == localDW->counter_time) {
      /* Transition: '<S2>:92' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
      localDW->exitPortIndex = 2U;
    } else {
      /* '<S2>:95:8' counter_time = counter_time +1; */
      qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
      if (localDW->counter_time + 1U < localDW->counter_time) {
        qY = MAX_uint32_T;
      }

      localDW->counter_time = qY;
    }
    break;

   case IN_AMMcooling:
    /* During 'AMMcooling': '<S2>:94' */
    /* '<S2>:105:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp <= 60; */
    if (FluxMapID_output->WindingTemp <= 60.0F) {
      /* Transition: '<S2>:105' */
      /* Exit 'AMMcooling': '<S2>:94' */
      /* '<S2>:94:10' PI_d_ref = i_d_ref_AMM_loc; */
      *PI_d_ref = localDW->i_d_ref_AMM_loc_h;

      /* '<S2>:94:11' PI_q_ref = i_q_ref_AMM_loc; */
      *PI_q_ref = localDW->i_q_ref_AMM_loc_p;
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
      enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
        localDW);
    }
    break;

   case IN_AMMheating:
    /* During 'AMMheating': '<S2>:88' */
    /* '<S2>:106:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >= 60; */
    if (FluxMapID_output->WindingTemp >= 60.0F) {
      /* Transition: '<S2>:106' */
      /* Exit 'AMMheating': '<S2>:88' */
      /* '<S2>:88:10' PI_d_ref = i_d_ref_AMM_loc; */
      *PI_d_ref = localDW->i_d_ref_AMM_loc;

      /* '<S2>:88:11' PI_q_ref = i_q_ref_AMM_loc; */
      *PI_q_ref = localDW->i_q_ref_AMM_loc;
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
      enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
        localDW);
    }
    break;

   case IN_AMMnewRef:
    /* During 'AMMnewRef': '<S2>:93' */
    /* '<S2>:109:1' sf_internal_predicateOutput = three_sec_transition_counter == counter_time; */
    if (three_sec_transition_counter == localDW->counter_time) {
      /* Transition: '<S2>:109' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcollectData;

      /* Entry 'AMMcollectData': '<S2>:99' */
      localDW->i = 1U;
      memset(&localDW->u_d_array[0], 0, 1000U * sizeof(real32_T));
      memset(&localDW->u_q_array[0], 0, 1000U * sizeof(real32_T));
      memset(&localDW->omega_el_array[0], 0, 1000U * sizeof(real32_T));
      memset(&localDW->i_d_array[0], 0, 1000U * sizeof(real32_T));
      memset(&localDW->i_q_array[0], 0, 1000U * sizeof(real32_T));

      /* '<S2>:99:4' counter_time = uint32(1); */
      localDW->counter_time = 1U;

      /* '<S2>:99:5' activeState = uint16(403); */
      *activeState = 403U;

      /* '<S2>:99:6' repetitionCounter = repetitionCounter + 1; */
      qY = *repetitionCounter + /*MW:OvSatOk*/ 1U;
      if (*repetitionCounter + 1U < *repetitionCounter) {
        qY = MAX_uint32_T;
      }

      *repetitionCounter = qY;

      /* i_d_R_online = single(0.0); */
      /* '<S2>:99:8' if(AMMn >= (NumberOfIDpoints-1)) */
      qY = localDW->NumberOfIDpoints - /*MW:OvSatOk*/ 1U;
      if (localDW->NumberOfIDpoints - 1U > localDW->NumberOfIDpoints) {
        qY = 0U;
      }

      if (localDW->AMMn >= qY) {
        /* '<S2>:99:9' AMMn = uint32(0); */
        localDW->AMMn = 0U;
      } else {
        /* '<S2>:99:10' else */
        /* '<S2>:99:11' AMMn = AMMn + 1; */
        qY = localDW->AMMn + /*MW:OvSatOk*/ 1U;
        if (localDW->AMMn + 1U < localDW->AMMn) {
          qY = MAX_uint32_T;
        }

        localDW->AMMn = qY;
      }

      /* '<S2>:99:13' FluxMapID_output.external_Measurement_Flag=boolean(1); */
      FluxMapID_output->external_Measurement_Flag = true;
    } else {
      /* '<S2>:93:18' counter_time = counter_time +1; */
      qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
      if (localDW->counter_time + 1U < localDW->counter_time) {
        qY = MAX_uint32_T;
      }

      localDW->counter_time = qY;
    }
    break;

   default:
    /* During 'initAMM': '<S2>:90' */
    /* '<S2>:98:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > 70 && .... */
    /* '<S2>:98:2' FluxMapIDConfig.start_FM_ID==1; */
    /* . */
    if ((FluxMapID_output->WindingTemp > 70.0F) && FluxMapIDConfig->start_FM_ID)
    {
      /* Transition: '<S2>:98' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcooling;

      /* Entry 'AMMcooling': '<S2>:94' */
      /* '<S2>:94:4' activeState = uint16(410); */
      *activeState = 410U;

      /* '<S2>:94:5' i_d_ref_AMM_loc = PI_d_ref; */
      localDW->i_d_ref_AMM_loc_h = *PI_d_ref;

      /* '<S2>:94:6' i_q_ref_AMM_loc = PI_q_ref; */
      localDW->i_q_ref_AMM_loc_p = *PI_q_ref;

      /* '<S2>:94:7' PI_d_ref = single(0.0); */
      *PI_d_ref = 0.0F;

      /* '<S2>:94:8' PI_q_ref = single(0.0); */
      *PI_q_ref = 0.0F;

      /* '<S2>:100:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < 60 && .... */
      /* '<S2>:100:2' FluxMapIDConfig.start_FM_ID==1; */
      /* . */
    } else if ((FluxMapID_output->WindingTemp < 60.0F) &&
               FluxMapIDConfig->start_FM_ID) {
      /* Transition: '<S2>:100' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMheating;

      /* Entry 'AMMheating': '<S2>:88' */
      /* '<S2>:88:4' activeState = uint16(420); */
      *activeState = 420U;

      /* '<S2>:88:5' i_d_ref_AMM_loc = PI_d_ref; */
      localDW->i_d_ref_AMM_loc = *PI_d_ref;

      /* '<S2>:88:6' i_q_ref_AMM_loc = PI_q_ref; */
      localDW->i_q_ref_AMM_loc = *PI_q_ref;

      /* '<S2>:88:7' PI_q_ref = single(FluxMapIDConfig.IQstop); */
      *PI_q_ref = FluxMapIDConfig->IQstop;

      /* '<S2>:88:8' PI_d_ref = single(FluxMapIDConfig.IDstart); */
      *PI_d_ref = FluxMapIDConfig->IDstart;

      /* '<S2>:102:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=60 && .... */
      /* '<S2>:102:2' FluxMapID_output.WindingTemp <=70 && .... */
      /* '<S2>:102:3' FluxMapIDConfig.start_FM_ID==1; */
      /* . */
    } else if ((FluxMapID_output->WindingTemp >= 60.0F) &&
               (FluxMapID_output->WindingTemp <= 70.0F) &&
               FluxMapIDConfig->start_FM_ID) {
      /* Transition: '<S2>:102' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
      enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
        localDW);
    }
    break;
  }

  if (guard1) {
    /* '<S2>:99:15' if(i>=array_size+1) */
    if (localDW->i >= 1001U) {
      /* '<S2>:99:16' switch i */
      switch (localDW->i) {
       case 1001U:
        {
          real32_T x;

          /* '<S2>:99:17' case array_size+1 */
          /* '<S2>:99:18' mean_voltages.d = mean(u_d_array); */
          x = localDW->u_d_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->u_d_array[i + 1];
          }

          mean_voltages->d = x / 1000.0F;

          /* '<S2>:99:19' i = i+1; */
          qY = localDW->i + /*MW:OvSatOk*/ 1U;
          if (localDW->i + 1U < localDW->i) {
            qY = MAX_uint32_T;
          }

          localDW->i = qY;
        }
        break;

       case 1002U:
        {
          real32_T x;

          /* '<S2>:99:20' case array_size+2 */
          /* '<S2>:99:21' mean_voltages.q = mean(u_q_array); */
          x = localDW->u_q_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->u_q_array[i + 1];
          }

          mean_voltages->q = x / 1000.0F;

          /* '<S2>:99:22' i = i+1; */
          qY = localDW->i + /*MW:OvSatOk*/ 1U;
          if (localDW->i + 1U < localDW->i) {
            qY = MAX_uint32_T;
          }

          localDW->i = qY;
        }
        break;

       case 1003U:
        {
          real32_T x;

          /* '<S2>:99:23' case array_size+3 */
          /* '<S2>:99:24' mean_omega_el = mean(omega_el_array); */
          x = localDW->omega_el_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->omega_el_array[i + 1];
          }

          *mean_omega_el = x / 1000.0F;

          /* '<S2>:99:25' i = i+1; */
          qY = localDW->i + /*MW:OvSatOk*/ 1U;
          if (localDW->i + 1U < localDW->i) {
            qY = MAX_uint32_T;
          }

          localDW->i = qY;
        }
        break;

       case 1004U:
        {
          real32_T x;

          /* '<S2>:99:26' case array_size+4 */
          /* '<S2>:99:27' mean_currents.d = mean(i_d_array); */
          x = localDW->i_d_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->i_d_array[i + 1];
          }

          mean_currents->d = x / 1000.0F;

          /* '<S2>:99:28' i = i+1; */
          qY = localDW->i + /*MW:OvSatOk*/ 1U;
          if (localDW->i + 1U < localDW->i) {
            qY = MAX_uint32_T;
          }

          localDW->i = qY;
        }
        break;

       case 1005U:
        {
          real32_T x;

          /* '<S2>:99:29' case array_size+5 */
          /* '<S2>:99:30' mean_currents.q = mean(i_q_array); */
          x = localDW->i_q_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->i_q_array[i + 1];
          }

          mean_currents->q = x / 1000.0F;

          /* '<S2>:99:31' i = i+1; */
          qY = localDW->i + /*MW:OvSatOk*/ 1U;
          if (localDW->i + 1U < localDW->i) {
            qY = MAX_uint32_T;
          }

          localDW->i = qY;
        }
        break;

       case 1006U:
        /* '<S2>:99:32' case array_size+6 */
        /* '<S2>:99:33' finished_calculation = true; */
        *finished_calculation = true;

        /* '<S2>:99:34' i = i+1; */
        qY = localDW->i + /*MW:OvSatOk*/ 1U;
        if (localDW->i + 1U < localDW->i) {
          qY = MAX_uint32_T;
        }

        localDW->i = qY;
        break;
      }
    } else {
      /* '<S2>:99:36' else */
      /* '<S2>:99:37' counter_time = counter_time +1; */
      qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
      if (localDW->counter_time + 1U < localDW->counter_time) {
        qY = MAX_uint32_T;
      }

      localDW->counter_time = qY;

      /* '<S2>:99:38' if((mod(counter_time,20)==0)&&i<=array_size) */
      if ((localDW->counter_time - localDW->counter_time / 20U * 20U == 0U) &&
          (localDW->i <= 1000U)) {
        /* '<S2>:99:39' i_d_array(i) = actual_currents.d; */
        localDW->i_d_array[(int32_T)localDW->i - 1] = actual_currents->d;

        /* '<S2>:99:40' i_q_array(i) = actual_currents.q; */
        localDW->i_q_array[(int32_T)localDW->i - 1] = actual_currents->q;

        /* '<S2>:99:41' u_d_array(i) = actual_voltages.d; */
        localDW->u_d_array[(int32_T)localDW->i - 1] = actual_voltages->d;

        /* '<S2>:99:42' u_q_array(i) = actual_voltages.q; */
        localDW->u_q_array[(int32_T)localDW->i - 1] = actual_voltages->q;

        /* '<S2>:99:43' omega_el_array(i) = omega_el; */
        localDW->omega_el_array[(int32_T)localDW->i - 1] = omega_el;

        /* '<S2>:99:44' i = i+1; */
        qY = localDW->i + /*MW:OvSatOk*/ 1U;
        if (localDW->i + 1U < localDW->i) {
          qY = MAX_uint32_T;
        }

        localDW->i = qY;
      }
    }
  }
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
void Fluxmap_enter(uint16_T *activeState, const uz_ParaID_FluxMapIDConfig_t
                   *FluxMapIDConfig, DW_AMMstateIdentificationDQFl_t *localDW)
{
  uint64_T tmp;
  real32_T tmp_0;
  uint32_T tmp_1;
  localDW->counter_time = 0U;
  localDW->AMMn = 0U;
  localDW->AMMj = 0U;

  /* Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
  /* Entry: Fluxmap */
  /* Entry Internal: Fluxmap */
  /* Transition: '<S2>:97' */
  localDW->is_c14_Subchart_FluxMapID_refer = IN_initAMM;

  /* Entry 'initAMM': '<S2>:90' */
  /* '<S2>:90:4' activeState = uint16(401); */
  *activeState = 401U;

  /* '<S2>:90:5' IDstepsize_loc = FluxMapIDConfig.IDstepsize; */
  localDW->IDstepsize_loc = FluxMapIDConfig->IDstepsize;

  /* '<S2>:90:6' IQstepsize_loc = FluxMapIDConfig.IQstepsize; */
  localDW->IQstepsize_loc = FluxMapIDConfig->IQstepsize;

  /* '<S2>:90:7' NumberOfIDpoints = uint32(abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart)/IDstepsize_loc+1); */
  tmp_0 = roundf(fabsf(FluxMapIDConfig->IDstop - FluxMapIDConfig->IDstart) /
                 localDW->IDstepsize_loc + 1.0F);
  if (tmp_0 < 4.2949673E+9F) {
    if (tmp_0 >= 0.0F) {
      localDW->NumberOfIDpoints = (uint32_T)tmp_0;
    } else {
      localDW->NumberOfIDpoints = 0U;
    }
  } else {
    localDW->NumberOfIDpoints = MAX_uint32_T;
  }

  /* '<S2>:90:8' NumberOfIQpoints = uint32(abs(FluxMapIDConfig.IQstop-FluxMapIDConfig.IQstart)/IQstepsize_loc+1); */
  /* '<S2>:90:9' NumberOfPoints = uint32(NumberOfIDpoints*NumberOfIQpoints); */
  tmp_0 = roundf(fabsf(FluxMapIDConfig->IQstop - FluxMapIDConfig->IQstart) /
                 localDW->IQstepsize_loc + 1.0F);
  if (tmp_0 < 4.2949673E+9F) {
    if (tmp_0 >= 0.0F) {
      tmp_1 = (uint32_T)tmp_0;
    } else {
      tmp_1 = 0U;
    }
  } else {
    tmp_1 = MAX_uint32_T;
  }

  tmp = (uint64_T)localDW->NumberOfIDpoints * tmp_1;
  if (tmp > 4294967295ULL) {
    tmp = 4294967295ULL;
  }

  localDW->NumberOfPoints = (uint32_T)tmp;

  /* End of Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
void Fluxmap_exit(real32_T *PI_d_ref, real32_T *PI_q_ref,
                  uz_ParaID_FluxMapID_output_t *FluxMapID_output, boolean_T
                  *finished_calculation, DW_AMMstateIdentificationDQFl_t
                  *localDW)
{
  /* Exit Internal: Fluxmap */
  switch (localDW->is_c14_Subchart_FluxMapID_refer) {
   case IN_AMMcollectData:
    /* Exit 'AMMcollectData': '<S2>:99' */
    /* '<S2>:99:48' FluxMapID_output.external_Measurement_Flag=boolean(0); */
    FluxMapID_output->external_Measurement_Flag = false;

    /* '<S2>:99:49' finished_calculation = false; */
    *finished_calculation = false;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;

   case IN_AMMcooling:
    /* Exit 'AMMcooling': '<S2>:94' */
    /* '<S2>:94:10' PI_d_ref = i_d_ref_AMM_loc; */
    *PI_d_ref = localDW->i_d_ref_AMM_loc_h;

    /* '<S2>:94:11' PI_q_ref = i_q_ref_AMM_loc; */
    *PI_q_ref = localDW->i_q_ref_AMM_loc_p;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;

   case IN_AMMheating:
    /* Exit 'AMMheating': '<S2>:88' */
    /* '<S2>:88:10' PI_d_ref = i_d_ref_AMM_loc; */
    *PI_d_ref = localDW->i_d_ref_AMM_loc;

    /* '<S2>:88:11' PI_q_ref = i_q_ref_AMM_loc; */
    *PI_q_ref = localDW->i_q_ref_AMM_loc;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;

   default:
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<S1>/AMMstate.IdentificationDQ.Fluxmap' */
void Fluxmap_init(DW_AMMstateIdentificationDQFl_t *localDW)
{
  localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
  localDW->NumberOfIDpoints = 0U;
  localDW->NumberOfPoints = 0U;
  localDW->counter_time = 0U;
  localDW->AMMn = 0U;
  localDW->AMMj = 0U;
  localDW->IQstepsize_loc = 0.0F;
  localDW->IDstepsize_loc = 0.0F;
  localDW->i_d_ref_AMM_loc = 0.0F;
  localDW->i_q_ref_AMM_loc = 0.0F;
  localDW->i_d_ref_AMM_loc_h = 0.0F;
  localDW->i_q_ref_AMM_loc_p = 0.0F;
  localDW->i = 1U;
  memset(&localDW->u_d_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->u_q_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->omega_el_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->i_d_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->i_q_array[0], 0, 1000U * sizeof(real32_T));
}

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

  /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
  /* MATLAB Function 'initParams': '<S1>:651' */
  /* '<S1>:651:5' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  tmp = roundf(1.0F / rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_cx = (uint32_T)tmp;
    } else {
      rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_cx = 0U;
    }
  } else {
    rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_cx = MAX_uint32_T;
  }

  /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
  /* '<S1>:651:6' three_sec_transition_counter = uint32(3/GlobalConfig.sampleTimeISR); */
  tmp = roundf(3.0F / rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_b = (uint32_T)tmp;
    } else {
      rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_b = 0U;
    }
  } else {
    rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_b = MAX_uint32_T;
  }

  /* '<S1>:651:7' collection_transition_counter = uint32(FluxMapIDConfig.AMMsampleTime/GlobalConfig.sampleTimeISR); */
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

  /* Outport: '<Root>/finishedFluxMapID' */
  /* '<S1>:651:35' finishedFluxMapID                       = boolean(0); */
  rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = false;

  /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
  /* '<S1>:651:37' FluxMapID_output.R_s                    = single(FluxMapIDConfig.R_s_ref); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s =
    rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref;

  /* '<S1>:651:38' FluxMapID_output.WindingTemp            = single(FluxMapIDConfig.Temp_ref); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp =
    rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref;

  /* '<S1>:651:39' FluxMapID_output.external_Measurement_Flag = boolean(0); */
  rtFluxMapID_6ph_codegen_DW->FluxMapID_output.external_Measurement_Flag = false;
}

/* Function for Chart: '<Root>/FluxMapID_6ph_codegen' */
static void enter_atomic_Wait_select_subsys(ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y, DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW)
{
  /* Entry 'Wait_select_subsystem': '<S1>:762' */
  /* '<S1>:762:3' i_q_ref_AMM = single(0); */
  rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

  /* '<S1>:762:4' i_d_ref_AMM = single(0); */
  rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

  /* Outport: '<Root>/extended_controller_output' */
  /* '<S1>:762:5' extended_controller_output.ab_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d = 0.0F;

  /* '<S1>:762:6' extended_controller_output.ab_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.q = 0.0F;

  /* '<S1>:762:7' extended_controller_output.xy_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.d = 0.0F;

  /* '<S1>:762:8' extended_controller_output.xy_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.q = 0.0F;

  /* '<S1>:762:9' extended_controller_output.zero_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.d =
    0.0F;

  /* '<S1>:762:10' extended_controller_output.zero_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.q =
    0.0F;

  /* '<S1>:762:11' extended_controller_output.finished_calculation=false; */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation =
    false;

  /* '<S1>:762:12' extended_controller_output.psi_array = [0;0;0;0]; */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] = 0.0F;

  /* '<S1>:762:13' counter = uint32(1); */
  rtFluxMapID_6ph_codegen_DW->counter = 1U;
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

  /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
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
    /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
    /* meas */
    /* '<S1>:669:4' i_d_R_online = single(-FluxMapIDConfig.identRAmp); */
    rtFluxMapID_6ph_codegen_DW->i_d_R_online =
      -rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

    /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
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
        /* SystemInitialize for Inport: '<Root>/ActualValues' */
        /* '<S1>:669:6' vd1_counter = vd1_counter + ActualValues.v_dq_6ph.d; */
        rtFluxMapID_6ph_codegen_DW->vd1_counter +=
          rtFluxMapID_6ph_codegen_U->ActualValues.v_dq_6ph.d;

        /* '<S1>:669:7' id1_counter = id1_counter + ActualValues.i_dq_6ph.d; */
        rtFluxMapID_6ph_codegen_DW->id1_counter +=
          rtFluxMapID_6ph_codegen_U->ActualValues.i_dq_6ph.d;
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
    /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
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
      /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
      /* '<S1>:669:12' i_d_R_online = single(FluxMapIDConfig.identRAmp); */
      rtFluxMapID_6ph_codegen_DW->i_d_R_online =
        rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

      /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
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
          /* SystemInitialize for Inport: '<Root>/ActualValues' */
          /* '<S1>:669:14' vd2_counter = vd2_counter + ActualValues.v_dq_6ph.d; */
          rtFluxMapID_6ph_codegen_DW->vd2_counter +=
            rtFluxMapID_6ph_codegen_U->ActualValues.v_dq_6ph.d;

          /* '<S1>:669:15' id2_counter = id2_counter + ActualValues.i_dq_6ph.d; */
          rtFluxMapID_6ph_codegen_DW->id2_counter +=
            rtFluxMapID_6ph_codegen_U->ActualValues.i_dq_6ph.d;
        }
      }
    }
  }

  /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
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
    /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
    /* '<S1>:669:20' i_d_R_online = single(-FluxMapIDConfig.identRAmp); */
    rtFluxMapID_6ph_codegen_DW->i_d_R_online =
      -rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identRAmp;

    /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
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

/* Function for Chart: '<Root>/FluxMapID_6ph_codegen' */
static void AMMstate(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                     ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                     DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  /* SystemInitialize for Inport: '<Root>/GlobalConfig' */
  /* During 'AMMstate': '<S1>:590' */
  /* '<S1>:667:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.FluxMapID==0.... */
  /* '<S1>:667:2' || GlobalConfig.enableParameterID==0; */
  if (rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset ||
      (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.FluxMapID) ||
      (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.enableParameterID)) {
    /* Transition: '<S1>:667' */
    /* '<S1>:667:3' enteredFluxMapID=boolean(0); */
    /* '<S1>:667:3' initParams; */
    initParams(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
               rtFluxMapID_6ph_codegen_DW);

    /* Exit Internal 'AMMstate': '<S1>:590' */
    switch (rtFluxMapID_6ph_codegen_DW->is_AMMstate) {
     case IN_IdentificationDQ:
      /* Exit Internal 'IdentificationDQ': '<S1>:717' */
      if (rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ == 1) {
        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         *  Inport: '<Root>/feedback_printed'
         */
        Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_NO_ACTIVE_CHILD_o;
      }

      /* Outport: '<Root>/extended_controller_output' */
      /* Exit 'IdentificationDQ': '<S1>:717' */
      /* '<S1>:717:24' extended_controller_output.selected_subsystem = uint16(0); */
      rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem =
        0U;
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_o;
      break;

     case IN_IdentificationXY:
      /* Exit Internal 'IdentificationXY': '<S1>:736' */
      if (rtFluxMapID_6ph_codegen_DW->is_IdentificationXY == 1) {
        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         *  Inport: '<Root>/feedback_printed'
         */
        Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_NO_ACTIVE_CHILD_o;
      }

      /* Outport: '<Root>/extended_controller_output' */
      /* Exit 'IdentificationXY': '<S1>:736' */
      /* '<S1>:736:25' extended_controller_output.selected_subsystem = uint16(0); */
      rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem =
        0U;
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_o;
      break;

     case IN_IdentificationXY1:
      /* Exit Internal 'IdentificationXY1': '<S1>:817' */
      if (rtFluxMapID_6ph_codegen_DW->is_IdentificationXY1 == 1) {
        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         *  Inport: '<Root>/feedback_printed'
         */
        Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXY1Flu);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationXY1 = IN_NO_ACTIVE_CHILD_o;
      }

      /* Outport: '<Root>/extended_controller_output' */
      /* Exit 'IdentificationXY1': '<S1>:817' */
      /* '<S1>:817:24' extended_controller_output.selected_subsystem = uint16(0); */
      rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem =
        0U;
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_o;
      break;

     default:
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_o;
      break;
    }

    /* Exit 'AMMstate': '<S1>:590' */
    /* '<S1>:590:29' counter = uint32(1); */
    rtFluxMapID_6ph_codegen_DW->counter = 1U;

    /* Outport: '<Root>/finishedFluxMapID' */
    /* '<S1>:590:30' finishedFluxMapID=boolean(1); */
    rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = true;

    /* Outport: '<Root>/enteredFluxMapID' */
    /* '<S1>:590:31' enteredFluxMapID = boolean(0); */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = false;
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
    /* FluxMapID */
    /* donothing */
  } else {
    /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
    /* '<S1>:590:17' if((FluxMapIDConfig.identR == 1) && (FluxMapIDConfig.start_FM_ID==1)) */
    if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identR &&
        rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
      /* Outport: '<Root>/FluxMapID_FOC_output' */
      /* '<S1>:590:18' if(FluxMapID_FOC_output.activeState ~= 403) */
      if (rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState != 403) {
        /* '<S1>:590:19' FluxMapID_output.R_s = identRes; */
        rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s = identRes
          (rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_DW);
      } else {
        /* '<S1>:590:20' else */
        /* '<S1>:590:21' i_d_R_online = single(0); */
        rtFluxMapID_6ph_codegen_DW->i_d_R_online = 0.0F;
      }

      /* '<S1>:590:23' if(FluxMapIDConfig.R_s_ref ~= 0.0 && FluxMapIDConfig.Temp_ref ~= 0.0) */
      if ((rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref != 0.0F) &&
          (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref != 0.0F)) {
        /* '<S1>:590:24' FluxMapID_output.WindingTemp = ((FluxMapID_output.R_s/FluxMapIDConfig.R_s_ref)-1).... */
        /* '<S1>:590:25'             *254.453+FluxMapIDConfig.Temp_ref; */
        rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp =
          (rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s /
           rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref - 1.0F) * 254.453F
          + rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref;

        /* . */
      }
    }

    switch (rtFluxMapID_6ph_codegen_DW->is_AMMstate) {
     case IN_IdentificationDQ:
      {
        uint32_T exitPortIndex_o;

        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
        /* During 'IdentificationDQ': '<S1>:717' */
        /* '<S1>:717:4' if(FluxMapIDConfig.start_FM_ID==1) */
        if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:717:5' extended_controller_output.ab_i_dq_PI_ref.d=i_d_R_online+i_d_ref_AMM; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d
            = rtFluxMapID_6ph_codegen_DW->i_d_R_online +
            rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

          /* '<S1>:717:6' extended_controller_output.ab_i_dq_PI_ref.q=i_q_ref_AMM; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.q
            = rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
        } else {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:717:7' else */
          /* '<S1>:717:8' extended_controller_output.ab_i_dq_PI_ref.d=single(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d
            = 0.0F;

          /* '<S1>:717:9' extended_controller_output.ab_i_dq_PI_ref.q=single(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.q
            = 0.0F;
        }

        /* '<S1>:717:11' if(finished_calculation) */
        if (rtFluxMapID_6ph_codegen_DW->finished_calculation_p) {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:717:12' extended_controller_output.psi_array(1)=mean_currents.d; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] =
            rtFluxMapID_6ph_codegen_DW->mean_currents_m.d;

          /* '<S1>:717:13' extended_controller_output.psi_array(2)=mean_currents.q; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] =
            rtFluxMapID_6ph_codegen_DW->mean_currents_m.q;

          /* '<S1>:717:14' extended_controller_output.psi_array(3)=(mean_voltages.q-... */
          /* '<S1>:717:15'         extended_controller_output.psi_array(2)*FluxMapID_output.R_s)/mean_omega_el; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] =
            (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q -
             rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] *
             rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) /
            rtFluxMapID_6ph_codegen_DW->mean_omega_el_k;

          /* '<S1>:717:16' extended_controller_output.psi_array(4)=single(-1)*(mean_voltages.d-... */
          /* '<S1>:717:17'         extended_controller_output.psi_array(1)*FluxMapID_output.R_s)/mean_omega_el; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] =
            -(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d -
              rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0]
              * rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) /
            rtFluxMapID_6ph_codegen_DW->mean_omega_el_k;

          /* '<S1>:717:18' extended_controller_output.array_index = repetition_counter; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.array_index =
            rtFluxMapID_6ph_codegen_DW->repetition_counter;

          /* '<S1>:717:19' extended_controller_output.finished_calculation=true; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
            = true;
        } else {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:717:20' else */
          /* '<S1>:717:21' extended_controller_output.finished_calculation=false; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
            = false;
        }

        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         *  Inport: '<Root>/feedback_printed'
         */
        /* During 'Fluxmap': '<S1>:704' */
        Fluxmap_during
          (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
           &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
           &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
           &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
           rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_cx,
           rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_b,
           &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
           &rtFluxMapID_6ph_codegen_U->ActualValues.v_dq,
           rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
           rtFluxMapID_6ph_codegen_U->feedback_printed,
           &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
           &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
           &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
           &rtFluxMapID_6ph_codegen_DW->mean_currents_m,
           &rtFluxMapID_6ph_codegen_DW->repetition_counter,
           &rtFluxMapID_6ph_codegen_U->ActualValues.i_dq,
           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
        exitPortIndex_o = Fluxmap_getExitPortIndex
          (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
        if (exitPortIndex_o == 2U) {
          /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
           *  Inport: '<Root>/ActualValues'
           *  Inport: '<Root>/FluxMapIDConfig'
           *  Inport: '<Root>/feedback_printed'
           */
          /* Transition: '<S1>:729' */
          Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                       &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                       &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                       &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
                       &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
          rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_NO_ACTIVE_CHILD_o;
          rtFluxMapID_6ph_codegen_DW->exitPortIndex = 2U;
        }

        if (rtFluxMapID_6ph_codegen_DW->exitPortIndex == 2U) {
          rtFluxMapID_6ph_codegen_DW->exitPortIndex = 0U;

          /* Outport: '<Root>/extended_controller_output' */
          /* Transition: '<S1>:765' */
          /* '<S1>:765:1' finished_ab=true; */
          /* Exit 'IdentificationDQ': '<S1>:717' */
          /* '<S1>:717:24' extended_controller_output.selected_subsystem = uint16(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
            = 0U;
          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
          enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
            rtFluxMapID_6ph_codegen_DW);
        }
      }
      break;

     case IN_IdentificationXY:
      {
        uint32_T exitPortIndex_o;

        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
        /* During 'IdentificationXY': '<S1>:736' */
        /* '<S1>:736:4' if(FluxMapIDConfig.start_FM_ID==1) */
        if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:736:5' extended_controller_output.xy_i_dq_PI_ref.d=i_d_ref_AMM; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.d
            = rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

          /* '<S1>:736:6' extended_controller_output.xy_i_dq_PI_ref.q=i_q_ref_AMM; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.q
            = rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;

          /* '<S1>:736:7' extended_controller_output.ab_i_dq_PI_ref.d = i_d_R_online; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d
            = rtFluxMapID_6ph_codegen_DW->i_d_R_online;
        } else {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:736:8' else */
          /* '<S1>:736:9' extended_controller_output.xy_i_dq_PI_ref.d=single(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.d
            = 0.0F;

          /* '<S1>:736:10' extended_controller_output.xy_i_dq_PI_ref.q=single(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.q
            = 0.0F;
        }

        /* '<S1>:736:12' if(finished_calculation) */
        if (rtFluxMapID_6ph_codegen_DW->finished_calculation_p) {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:736:13' extended_controller_output.psi_array(1)=mean_currents.d; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] =
            rtFluxMapID_6ph_codegen_DW->mean_currents_m.d;

          /* '<S1>:736:14' extended_controller_output.psi_array(2)=mean_currents.q; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] =
            rtFluxMapID_6ph_codegen_DW->mean_currents_m.q;

          /* '<S1>:736:15' extended_controller_output.psi_array(3)=single(-1)*(mean_voltages.q-... */
          /* '<S1>:736:16'         extended_controller_output.psi_array(2)*FluxMapID_output.R_s)/mean_omega_el; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] =
            -(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q -
              rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1]
              * rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) /
            rtFluxMapID_6ph_codegen_DW->mean_omega_el_k;

          /* '<S1>:736:17' extended_controller_output.psi_array(4)=(mean_voltages.d-... */
          /* '<S1>:736:18'         extended_controller_output.psi_array(1)*FluxMapID_output.R_s)/mean_omega_el; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] =
            (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d -
             rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] *
             rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) /
            rtFluxMapID_6ph_codegen_DW->mean_omega_el_k;

          /* '<S1>:736:19' extended_controller_output.array_index = repetition_counter; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.array_index =
            rtFluxMapID_6ph_codegen_DW->repetition_counter;

          /* '<S1>:736:20' extended_controller_output.finished_calculation=true; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
            = true;
        } else {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:736:21' else */
          /* '<S1>:736:22' extended_controller_output.finished_calculation=false; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
            = false;
        }

        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         *  Inport: '<Root>/feedback_printed'
         */
        /* During 'Fluxmap': '<S1>:748' */
        Fluxmap_during
          (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
           &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
           &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
           &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
           rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_cx,
           rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_b,
           &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
           &rtFluxMapID_6ph_codegen_U->ActualValues.v_xy_rotating,
           rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
           rtFluxMapID_6ph_codegen_U->feedback_printed,
           &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
           &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
           &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
           &rtFluxMapID_6ph_codegen_DW->mean_currents_m,
           &rtFluxMapID_6ph_codegen_DW->repetition_counter,
           &rtFluxMapID_6ph_codegen_U->ActualValues.i_xy_rotating,
           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
        exitPortIndex_o = Fluxmap_getExitPortIndex
          (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
        if (exitPortIndex_o == 2U) {
          /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
           *  Inport: '<Root>/ActualValues'
           *  Inport: '<Root>/FluxMapIDConfig'
           *  Inport: '<Root>/feedback_printed'
           */
          /* Transition: '<S1>:750' */
          Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                       &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                       &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                       &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
                       &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
          rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_NO_ACTIVE_CHILD_o;
          rtFluxMapID_6ph_codegen_DW->exitPortIndex_d = 2U;
        }

        if (rtFluxMapID_6ph_codegen_DW->exitPortIndex_d == 2U) {
          rtFluxMapID_6ph_codegen_DW->exitPortIndex_d = 0U;

          /* Outport: '<Root>/extended_controller_output' */
          /* Transition: '<S1>:764' */
          /* '<S1>:764:1' finished_xy = true; */
          /* Exit 'IdentificationXY': '<S1>:736' */
          /* '<S1>:736:25' extended_controller_output.selected_subsystem = uint16(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
            = 0U;
          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
          enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
            rtFluxMapID_6ph_codegen_DW);
        }
      }
      break;

     case IN_IdentificationXY1:
      {
        uint32_T exitPortIndex_o;

        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
        /* During 'IdentificationXY1': '<S1>:817' */
        /* '<S1>:817:4' if(FluxMapIDConfig.start_FM_ID==1) */
        if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:817:5' extended_controller_output.zero_i_dq_PI_ref.d=i_d_R_online+i_d_ref_AMM; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.d
            = rtFluxMapID_6ph_codegen_DW->i_d_R_online +
            rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

          /* '<S1>:817:6' extended_controller_output.zero_i_dq_PI_ref.q=i_q_ref_AMM; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.q
            = rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
        } else {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:817:7' else */
          /* '<S1>:817:8' extended_controller_output.zero_i_dq_PI_ref.d=single(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.d
            = 0.0F;

          /* '<S1>:817:9' extended_controller_output.zero_i_dq_PI_ref.q=single(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.q
            = 0.0F;
        }

        /* '<S1>:817:11' if(finished_calculation) */
        if (rtFluxMapID_6ph_codegen_DW->finished_calculation_p) {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:817:12' extended_controller_output.psi_array(1)=mean_currents.d; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] =
            rtFluxMapID_6ph_codegen_DW->mean_currents_m.d;

          /* '<S1>:817:13' extended_controller_output.psi_array(2)=mean_currents.q; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] =
            rtFluxMapID_6ph_codegen_DW->mean_currents_m.q;

          /* '<S1>:817:14' extended_controller_output.psi_array(3)=(mean_voltages.q-... */
          /* '<S1>:817:15'         extended_controller_output.psi_array(2)*FluxMapID_output.R_s)/mean_omega_el/single(3); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] =
            (rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q -
             rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] *
             rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) /
            rtFluxMapID_6ph_codegen_DW->mean_omega_el_k / 3.0F;

          /* '<S1>:817:16' extended_controller_output.psi_array(4)=single(-1)*(mean_voltages.d-... */
          /* '<S1>:817:17'         extended_controller_output.psi_array(1)*FluxMapID_output.R_s)/mean_omega_el/single(3); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] =
            -(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d -
              rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0]
              * rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) /
            rtFluxMapID_6ph_codegen_DW->mean_omega_el_k / 3.0F;

          /* '<S1>:817:18' extended_controller_output.array_index = repetition_counter; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.array_index =
            rtFluxMapID_6ph_codegen_DW->repetition_counter;

          /* '<S1>:817:19' extended_controller_output.finished_calculation=true; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
            = true;
        } else {
          /* Outport: '<Root>/extended_controller_output' */
          /* '<S1>:817:20' else */
          /* '<S1>:817:21' extended_controller_output.finished_calculation=false; */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
            = false;
        }

        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         *  Inport: '<Root>/feedback_printed'
         */
        /* During 'Fluxmap': '<S1>:830' */
        Fluxmap_during
          (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
           &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
           &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
           &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
           rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_cx,
           rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_b,
           &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
           &rtFluxMapID_6ph_codegen_U->ActualValues.v_zero_rotating,
           rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
           rtFluxMapID_6ph_codegen_U->feedback_printed,
           &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
           &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
           &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
           &rtFluxMapID_6ph_codegen_DW->mean_currents_m,
           &rtFluxMapID_6ph_codegen_DW->repetition_counter,
           &rtFluxMapID_6ph_codegen_U->ActualValues.i_zero_rotating,
           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXY1Flu);
        exitPortIndex_o = Fluxmap_getExitPortIndex
          (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXY1Flu);
        if (exitPortIndex_o == 2U) {
          /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
           *  Inport: '<Root>/ActualValues'
           *  Inport: '<Root>/FluxMapIDConfig'
           *  Inport: '<Root>/feedback_printed'
           */
          /* Transition: '<S1>:836' */
          Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                       &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                       &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                       &rtFluxMapID_6ph_codegen_DW->finished_calculation_p,
                       &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXY1Flu);
          rtFluxMapID_6ph_codegen_DW->is_IdentificationXY1 =
            IN_NO_ACTIVE_CHILD_o;
          rtFluxMapID_6ph_codegen_DW->exitPortIndex_c = 2U;
        }

        if (rtFluxMapID_6ph_codegen_DW->exitPortIndex_c == 2U) {
          rtFluxMapID_6ph_codegen_DW->exitPortIndex_c = 0U;

          /* Outport: '<Root>/extended_controller_output' */
          /* Transition: '<S1>:838' */
          /* '<S1>:838:1' finished_zero = true; */
          /* Exit 'IdentificationXY1': '<S1>:817' */
          /* '<S1>:817:24' extended_controller_output.selected_subsystem = uint16(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
            = 0U;
          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
          enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
            rtFluxMapID_6ph_codegen_DW);
        }
      }
      break;

     default:
      /* Outport: '<Root>/extended_controller_output' incorporates:
       *  Inport: '<Root>/ActualValues'
       *  Inport: '<Root>/FluxMapIDConfig'
       *  Inport: '<Root>/feedback_printed'
       *  Outport: '<Root>/FluxMapID_FOC_output'
       */
      /* During 'Wait_select_subsystem': '<S1>:762' */
      /* '<S1>:757:1' sf_internal_predicateOutput = extended_controller_output.selected_subsystem == 2 && GlobalConfig.ACCEPT==1; */
      if ((rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
           == 2) && rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:757' */
        rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationXY;

        /* Entry 'IdentificationXY': '<S1>:736' */
        /* Entry Internal 'IdentificationXY': '<S1>:736' */
        /* Transition: '<S1>:749' */
        rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_Fluxmap;
        Fluxmap_enter
          (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
           &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);

        /* '<S1>:754:1' sf_internal_predicateOutput = extended_controller_output.selected_subsystem == 1 && GlobalConfig.ACCEPT==1; */
      } else if
          ((rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
            == 1) && rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:754' */
        rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationDQ;

        /* Entry 'IdentificationDQ': '<S1>:717' */
        /* Entry Internal 'IdentificationDQ': '<S1>:717' */
        /* Transition: '<S1>:733' */
        rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_Fluxmap;
        Fluxmap_enter
          (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
           &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);

        /* '<S1>:837:1' sf_internal_predicateOutput = extended_controller_output.selected_subsystem == 3 && GlobalConfig.ACCEPT==1; */
      } else if
          ((rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
            == 3) && rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
        /* Transition: '<S1>:837' */
        rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationXY1;

        /* Entry 'IdentificationXY1': '<S1>:817' */
        /* Entry Internal 'IdentificationXY1': '<S1>:817' */
        /* Transition: '<S1>:835' */
        rtFluxMapID_6ph_codegen_DW->is_IdentificationXY1 = IN_Fluxmap;
        Fluxmap_enter
          (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
           &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
           &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXY1Flu);
      } else {
        /* '<S1>:762:15' if(FluxMapIDConfig.identR == 0) */
        if (!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.identR) {
          /* '<S1>:762:16' i_d_R_online = single(0); */
          rtFluxMapID_6ph_codegen_DW->i_d_R_online = 0.0F;

          /* '<S1>:762:17' FluxMapID_output.WindingTemp= single(65); */
          rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp = 65.0F;
        }

        /* '<S1>:762:19' extended_controller_output.selected_subsystem = FluxMapIDConfig.selected_subsystem; */
        rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
          = rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem;
      }
      break;
    }
  }

  /* End of SystemInitialize for Inport: '<Root>/GlobalConfig' */
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
   *  Inport: '<Root>/GlobalConfig'
   *  Outport: '<Root>/FluxMapID_FOC_output'
   *  Outport: '<Root>/extended_controller_output'
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
    AMMstate(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
             rtFluxMapID_6ph_codegen_DW);

    /* During 'Waiting': '<S1>:652' */
    /* '<S1>:656:1' sf_internal_predicateOutput = ControlFlags.startFluxMapID==1 && .... */
    /* '<S1>:656:2' GlobalConfig.Reset==0 && GlobalConfig.ACCEPT==1; */
    /* . */
  } else if (rtFluxMapID_6ph_codegen_U->ControlFlags.startFluxMapID &&
             (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset) &&
             rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:656' */
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_AMMstate;

    /* Entry 'AMMstate': '<S1>:590' */
    /* '<S1>:590:4' initParams; */
    initParams(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
               rtFluxMapID_6ph_codegen_DW);

    /* Outport: '<Root>/enteredFluxMapID' */
    /*  init controllers in c */
    /* '<S1>:590:6' enteredFluxMapID = boolean(1); */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = true;

    /* '<S1>:590:7' FluxMapID_FOC_output.enableFOC_current=boolean(1); */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = true;

    /* '<S1>:590:8' FluxMapID_FOC_output.activeState = uint16(400); */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 400U;

    /* '<S1>:590:9' extended_controller_output.selected_subsystem = uint16(0); */
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem =
      0U;

    /* '<S1>:590:10' if(FluxMapIDConfig.IDstepsize==0) */
    /* '<S1>:590:13' if(FluxMapIDConfig.IQstepsize==0) */
    /* Entry Internal 'AMMstate': '<S1>:590' */
    /* Transition: '<S1>:763' */
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
    enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
      rtFluxMapID_6ph_codegen_DW);

    /* '<S1>:680:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
  } else if (rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset) {
    /* Outport: '<Root>/enteredFluxMapID' */
    /* Transition: '<S1>:680' */
    /* '<S1>:680:1' finishedFluxMapID=boolean(0); */
    /* '<S1>:680:2' enteredFluxMapID=boolean(0); */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = false;

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
  ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U =
    (ExtU_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->inputs;
  ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y =
    (ExtY_FluxMapID_6ph_codegen_t *) rtFluxMapID_6ph_codegen_M->outputs;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)rtFluxMapID_6ph_codegen_DW, 0,
                sizeof(DW_FluxMapID_6ph_codegen_t));

  /* external inputs */
  (void)memset(rtFluxMapID_6ph_codegen_U, 0, sizeof(ExtU_FluxMapID_6ph_codegen_t));

  /* external outputs */
  (void)memset(rtFluxMapID_6ph_codegen_Y, 0, sizeof(ExtY_FluxMapID_6ph_codegen_t));

  /* SystemInitialize for Chart: '<Root>/FluxMapID_6ph_codegen' incorporates:
   *  Inport: '<Root>/ActualValues'
   *  Inport: '<Root>/FluxMapIDConfig'
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/feedback_printed'
   *  Outport: '<Root>/FluxMapID_FOC_output'
   */
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXY1Flu);
  rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_o;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_NO_ACTIVE_CHILD_o;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_NO_ACTIVE_CHILD_o;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationXY1 = IN_NO_ACTIVE_CHILD_o;
  rtFluxMapID_6ph_codegen_DW->is_active_c16_FluxMapID_6ph_cod = 0U;
  rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen =
    IN_NO_ACTIVE_CHILD_o;
  rtFluxMapID_6ph_codegen_DW->counter = 0U;
  rtFluxMapID_6ph_codegen_DW->vd2_counter = 0.0F;
  rtFluxMapID_6ph_codegen_DW->i_d_R_online = 0.0F;
  rtFluxMapID_6ph_codegen_DW->id2_counter = 0.0F;
  rtFluxMapID_6ph_codegen_DW->vd1_counter = 0.0F;
  rtFluxMapID_6ph_codegen_DW->id1_counter = 0.0F;
  memset(&rtFluxMapID_6ph_codegen_DW->R_s_array[0], 0, 50U * sizeof(real32_T));
  rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_b = 0U;
  rtFluxMapID_6ph_codegen_DW->one_sec_transition_counter_cx = 0U;
  rtFluxMapID_6ph_codegen_DW->mean_omega_el_k = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.zero = 0.0F;
  rtFluxMapID_6ph_codegen_DW->finished_calculation_p = false;
  rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;
  rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_currents_m.d = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_currents_m.q = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_currents_m.zero = 0.0F;
  rtFluxMapID_6ph_codegen_DW->repetition_counter = 0U;

  /* SystemInitialize for Outport: '<Root>/finishedFluxMapID' incorporates:
   *  Chart: '<Root>/FluxMapID_6ph_codegen'
   */
  rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = false;

  /* SystemInitialize for Outport: '<Root>/enteredFluxMapID' incorporates:
   *  Chart: '<Root>/FluxMapID_6ph_codegen'
   */
  rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = false;

  /* SystemInitialize for Chart: '<Root>/FluxMapID_6ph_codegen' incorporates:
   *  Outport: '<Root>/FluxMapID_FOC_output'
   *  Outport: '<Root>/extended_controller_output'
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
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.control_active = false;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem = 0U;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.q = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.zero =
    0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.d = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.q = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.zero =
    0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.d =
    0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.q =
    0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.zero =
    0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation =
    false;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.array_index = 0U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
#endif