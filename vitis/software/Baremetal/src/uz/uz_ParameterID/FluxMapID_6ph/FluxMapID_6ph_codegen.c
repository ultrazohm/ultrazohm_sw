/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: FluxMapID_6ph_codegen.c
 *
 * Code generated for Simulink model 'FluxMapID_6ph_codegen'.
 *
 * Model version                  : 3.94
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon May  1 14:29:48 2023
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
#define IN_AMMcooling                  ((uint8_T)2U)
#define IN_AMMheating                  ((uint8_T)3U)
#define IN_AMMnewRef                   ((uint8_T)4U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_initAMM                     ((uint8_T)5U)

/* Named constants for Chart: '<Root>/FluxMapID_6ph_codegen' */
#define IN_AMMstate                    ((uint8_T)1U)
#define IN_Fluxmap                     ((uint8_T)1U)
#define IN_IdentificationDQ            ((uint8_T)1U)
#define IN_IdentificationXY            ((uint8_T)2U)
#define IN_IdentificationZero          ((uint8_T)3U)
#define IN_NO_ACTIVE_CHILD_b           ((uint8_T)0U)
#define IN_Wait_select_subsystem       ((uint8_T)4U)
#define IN_Waiting                     ((uint8_T)2U)
#define TEMP_COEFFICIENT               (0.00393F)

/* Exported functions */
extern uint32_T Fluxmap_getExitPortIndex(DW_AMMstateIdentificationDQFl_t
  *localDW);
extern void Fluxmap_during(uint16_T *activeState, real32_T *PI_d_ref, real32_T
  *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig, uint32_T
  three_sec_transition_counter, uz_ParaID_FluxMapID_output_t *FluxMapID_output,
  const uz_3ph_dq_t *actual_voltages, real32_T omega_el, boolean_T
  feedback_printed, boolean_T *finished_calculation, uz_3ph_dq_t *mean_voltages,
  real32_T *mean_omega_el, uz_3ph_dq_t *mean_currents, uint32_T
  *repetitionCounter, const uz_3ph_dq_t *actual_currents,
  DW_AMMstateIdentificationDQFl_t *localDW);
extern void Fluxmap_enter(uint16_T *activeState, real32_T *PI_d_ref, real32_T
  *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_AMMstateIdentificationDQFl_t *localDW);
extern void Fluxmap_exit(real32_T *PI_d_ref, real32_T *PI_q_ref,
  uz_ParaID_FluxMapID_output_t *FluxMapID_output, boolean_T
  *finished_calculation, DW_AMMstateIdentificationDQFl_t *localDW);
extern void Fluxmap_init(DW_AMMstateIdentificationDQFl_t *localDW);

/* Forward declaration for local functions */
static void enter_atomic_AMMnewRef(uint16_T *activeState, real32_T *PI_d_ref,
  real32_T *PI_q_ref, const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
  DW_AMMstateIdentificationDQFl_t *localDW);

/* Forward declaration for local functions */
static void init(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                 ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                 DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW);
static void enter_atomic_Wait_select_subsys(ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y, DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW);
static void Wait_select_subsystem(ExtU_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_U, ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y, DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW);
static real32_T flux(real32_T u, real32_T i, real32_T omega_el, real32_T Rs);
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

  /* '<S2>:93:6' if((FluxMapIDConfig.IDstart + single(AMMn) * FluxMapIDConfig.IDstepsize) <= FluxMapIDConfig.IDstop) */
  y = (real32_T)localDW->AMMn * FluxMapIDConfig->IDstepsize +
    FluxMapIDConfig->IDstart;
  if (y <= FluxMapIDConfig->IDstop) {
    real32_T r;

    /* '<S2>:93:7' PI_d_ref = single(FluxMapIDConfig.IDstart + single(AMMn) * FluxMapIDConfig.IDstepsize); */
    *PI_d_ref = y;

    /* '<S2>:93:8' if(mod(single(AMMn),((abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart))/FluxMapIDConfig.IDstepsize)+1) == 0) */
    y = fabsf(FluxMapIDConfig->IDstop - FluxMapIDConfig->IDstart) /
      FluxMapIDConfig->IDstepsize + 1.0F;
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
      /* '<S2>:93:9' if((FluxMapIDConfig.IQstart + single(AMMj) * FluxMapIDConfig.IQstepsize) <= FluxMapIDConfig.IQstop) */
      y = (real32_T)localDW->AMMj * FluxMapIDConfig->IQstepsize +
        FluxMapIDConfig->IQstart;
      if (y <= FluxMapIDConfig->IQstop) {
        uint32_T qY;

        /* '<S2>:93:10' PI_q_ref = single(FluxMapIDConfig.IQstart + single(AMMj) * FluxMapIDConfig.IQstepsize); */
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
                    *FluxMapIDConfig, uint32_T three_sec_transition_counter,
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
    /* '<S2>:154:1' sf_internal_predicateOutput = (repetitionCounter < NumberOfPoints) && (feedback_printed==true); */
    if ((*repetitionCounter < localDW->NumberOfPoints) && feedback_printed) {
      /* Transition: '<S2>:154' */
      /* '<S2>:107:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > FluxMapIDConfig.upper_meas_temp; */
      if (FluxMapID_output->WindingTemp > FluxMapIDConfig->upper_meas_temp) {
        /* Transition: '<S2>:107' */
        /* Exit 'AMMcollectData': '<S2>:99' */
        /* '<S2>:99:47' FluxMapID_output.external_Measurement_Flag=boolean(0); */
        FluxMapID_output->external_Measurement_Flag = false;

        /* '<S2>:99:48' finished_calculation = false; */
        *finished_calculation = false;
        localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcooling;

        /* Entry 'AMMcooling': '<S2>:94' */
        localDW->PI_d_loc_h = 0.0F;

        /* '<S2>:94:4' activeState = uint16(410); */
        *activeState = 410U;

        /* '<S2>:94:5' PI_q_loc = PI_d_ref; */
        /* '<S2>:94:6' PI_q_loc = PI_q_ref; */
        localDW->PI_q_loc_b = *PI_q_ref;

        /* '<S2>:94:7' PI_d_ref = single(0); */
        *PI_d_ref = 0.0F;

        /* '<S2>:94:8' PI_q_ref = single(0); */
        *PI_q_ref = 0.0F;

        /* '<S2>:104:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=FluxMapIDConfig.lower_meas_temp && FluxMapID_output.WindingTemp <= FluxMapIDConfig.upper_meas_temp; */
      } else if ((FluxMapID_output->WindingTemp >=
                  FluxMapIDConfig->lower_meas_temp) &&
                 (FluxMapID_output->WindingTemp <=
                  FluxMapIDConfig->upper_meas_temp)) {
        /* Transition: '<S2>:104' */
        /* Exit 'AMMcollectData': '<S2>:99' */
        /* '<S2>:99:47' FluxMapID_output.external_Measurement_Flag=boolean(0); */
        FluxMapID_output->external_Measurement_Flag = false;

        /* '<S2>:99:48' finished_calculation = false; */
        *finished_calculation = false;
        localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
        enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
          localDW);

        /* '<S2>:101:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < FluxMapIDConfig.lower_meas_temp; */
      } else if (FluxMapID_output->WindingTemp <
                 FluxMapIDConfig->lower_meas_temp) {
        /* Transition: '<S2>:101' */
        /* Exit 'AMMcollectData': '<S2>:99' */
        /* '<S2>:99:47' FluxMapID_output.external_Measurement_Flag=boolean(0); */
        FluxMapID_output->external_Measurement_Flag = false;

        /* '<S2>:99:48' finished_calculation = false; */
        *finished_calculation = false;
        localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMheating;

        /* Entry 'AMMheating': '<S2>:88' */
        /* '<S2>:88:4' activeState = uint16(420); */
        *activeState = 420U;

        /* '<S2>:88:5' PI_d_loc = PI_d_ref; */
        localDW->PI_d_loc = *PI_d_ref;

        /* '<S2>:88:6' PI_q_loc = PI_q_ref; */
        localDW->PI_q_loc = *PI_q_ref;

        /* '<S2>:88:7' PI_d_ref = FluxMapIDConfig.IDstart; */
        *PI_d_ref = FluxMapIDConfig->IDstart;

        /* '<S2>:88:8' PI_q_ref = FluxMapIDConfig.IQstop; */
        *PI_q_ref = FluxMapIDConfig->IQstop;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    break;

   case IN_AMMcooling:
    /* During 'AMMcooling': '<S2>:94' */
    /* '<S2>:105:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp <= FluxMapIDConfig.upper_meas_temp; */
    if (FluxMapID_output->WindingTemp <= FluxMapIDConfig->upper_meas_temp) {
      /* Transition: '<S2>:105' */
      /* Exit 'AMMcooling': '<S2>:94' */
      /* '<S2>:94:10' PI_d_ref = PI_d_loc; */
      *PI_d_ref = localDW->PI_d_loc_h;

      /* '<S2>:94:11' PI_q_ref = PI_q_loc; */
      *PI_q_ref = localDW->PI_q_loc_b;
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
      enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
        localDW);
    }
    break;

   case IN_AMMheating:
    /* During 'AMMheating': '<S2>:88' */
    /* '<S2>:106:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >= FluxMapIDConfig.lower_meas_temp; */
    if (FluxMapID_output->WindingTemp >= FluxMapIDConfig->lower_meas_temp) {
      /* Transition: '<S2>:106' */
      /* Exit 'AMMheating': '<S2>:88' */
      /* '<S2>:88:10' PI_d_ref = PI_d_loc; */
      *PI_d_ref = localDW->PI_d_loc;

      /* '<S2>:88:11' PI_q_ref = PI_q_loc; */
      *PI_q_ref = localDW->PI_q_loc;
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

      /* '<S2>:99:7' if(AMMn >= (NumberOfIDpoints-1)) */
      qY = localDW->NumberOfIDpoints - /*MW:OvSatOk*/ 1U;
      if (localDW->NumberOfIDpoints - 1U > localDW->NumberOfIDpoints) {
        qY = 0U;
      }

      if (localDW->AMMn >= qY) {
        /* '<S2>:99:8' AMMn = uint32(0); */
        localDW->AMMn = 0U;
      } else {
        /* '<S2>:99:9' else */
        /* '<S2>:99:10' AMMn = AMMn + 1; */
        qY = localDW->AMMn + /*MW:OvSatOk*/ 1U;
        if (localDW->AMMn + 1U < localDW->AMMn) {
          qY = MAX_uint32_T;
        }

        localDW->AMMn = qY;
      }

      /* '<S2>:99:12' FluxMapID_output.external_Measurement_Flag=boolean(1); */
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
    /* '<S2>:98:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp > FluxMapIDConfig.upper_meas_temp && .... */
    /* '<S2>:98:2' FluxMapIDConfig.start_FM_ID==1; */
    /* . */
    if ((FluxMapID_output->WindingTemp > FluxMapIDConfig->upper_meas_temp) &&
        FluxMapIDConfig->start_FM_ID) {
      /* Transition: '<S2>:98' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMcooling;

      /* Entry 'AMMcooling': '<S2>:94' */
      localDW->PI_d_loc_h = 0.0F;

      /* '<S2>:94:4' activeState = uint16(410); */
      *activeState = 410U;

      /* '<S2>:94:5' PI_q_loc = PI_d_ref; */
      /* '<S2>:94:6' PI_q_loc = PI_q_ref; */
      localDW->PI_q_loc_b = *PI_q_ref;

      /* '<S2>:94:7' PI_d_ref = single(0); */
      *PI_d_ref = 0.0F;

      /* '<S2>:94:8' PI_q_ref = single(0); */
      *PI_q_ref = 0.0F;

      /* '<S2>:100:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp < FluxMapIDConfig.lower_meas_temp && .... */
      /* '<S2>:100:2' FluxMapIDConfig.start_FM_ID==1; */
      /* . */
    } else if ((FluxMapID_output->WindingTemp < FluxMapIDConfig->lower_meas_temp)
               && FluxMapIDConfig->start_FM_ID) {
      /* Transition: '<S2>:100' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMheating;

      /* Entry 'AMMheating': '<S2>:88' */
      /* '<S2>:88:4' activeState = uint16(420); */
      *activeState = 420U;

      /* '<S2>:88:5' PI_d_loc = PI_d_ref; */
      localDW->PI_d_loc = *PI_d_ref;

      /* '<S2>:88:6' PI_q_loc = PI_q_ref; */
      localDW->PI_q_loc = *PI_q_ref;

      /* '<S2>:88:7' PI_d_ref = FluxMapIDConfig.IDstart; */
      *PI_d_ref = FluxMapIDConfig->IDstart;

      /* '<S2>:88:8' PI_q_ref = FluxMapIDConfig.IQstop; */
      *PI_q_ref = FluxMapIDConfig->IQstop;

      /* '<S2>:102:1' sf_internal_predicateOutput = FluxMapID_output.WindingTemp >=FluxMapIDConfig.lower_meas_temp && .... */
      /* '<S2>:102:2' FluxMapID_output.WindingTemp <=FluxMapIDConfig.upper_meas_temp && .... */
      /* '<S2>:102:3' FluxMapIDConfig.start_FM_ID==1; */
      /* . */
    } else if ((FluxMapID_output->WindingTemp >=
                FluxMapIDConfig->lower_meas_temp) &&
               (FluxMapID_output->WindingTemp <=
                FluxMapIDConfig->upper_meas_temp) &&
               FluxMapIDConfig->start_FM_ID) {
      /* Transition: '<S2>:102' */
      localDW->is_c14_Subchart_FluxMapID_refer = IN_AMMnewRef;
      enter_atomic_AMMnewRef(activeState, PI_d_ref, PI_q_ref, FluxMapIDConfig,
        localDW);
    }
    break;
  }

  if (guard1) {
    /* '<S2>:165:1' sf_internal_predicateOutput = (repetitionCounter>=NumberOfPoints) && (feedback_printed==true); */
    if ((*repetitionCounter >= localDW->NumberOfPoints) && feedback_printed) {
      /* Transition: '<S2>:165' */
      /* Exit 'AMMcollectData': '<S2>:99' */
      /* '<S2>:99:47' FluxMapID_output.external_Measurement_Flag=boolean(0); */
      FluxMapID_output->external_Measurement_Flag = false;

      /* '<S2>:99:48' finished_calculation = false; */
      *finished_calculation = false;
      localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
      localDW->exitPortIndex = 2U;

      /* '<S2>:99:14' if(i>=array_size+1) */
    } else if (localDW->i >= 1001U) {
      /* '<S2>:99:15' switch i */
      switch (localDW->i) {
       case 1001U:
        {
          real32_T x;

          /* '<S2>:99:16' case array_size+1 */
          /* '<S2>:99:17' mean_voltages.d = mean(u_d_array); */
          x = localDW->u_d_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->u_d_array[i + 1];
          }

          mean_voltages->d = x / 1000.0F;

          /* '<S2>:99:18' i = i+1; */
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

          /* '<S2>:99:19' case array_size+2 */
          /* '<S2>:99:20' mean_voltages.q = mean(u_q_array); */
          x = localDW->u_q_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->u_q_array[i + 1];
          }

          mean_voltages->q = x / 1000.0F;

          /* '<S2>:99:21' i = i+1; */
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

          /* '<S2>:99:22' case array_size+3 */
          /* '<S2>:99:23' mean_omega_el = mean(omega_el_array); */
          x = localDW->omega_el_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->omega_el_array[i + 1];
          }

          *mean_omega_el = x / 1000.0F;

          /* '<S2>:99:24' i = i+1; */
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

          /* '<S2>:99:25' case array_size+4 */
          /* '<S2>:99:26' mean_currents.d = mean(i_d_array); */
          x = localDW->i_d_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->i_d_array[i + 1];
          }

          mean_currents->d = x / 1000.0F;

          /* '<S2>:99:27' i = i+1; */
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

          /* '<S2>:99:28' case array_size+5 */
          /* '<S2>:99:29' mean_currents.q = mean(i_q_array); */
          x = localDW->i_q_array[0];
          for (i = 0; i < 999; i++) {
            x += localDW->i_q_array[i + 1];
          }

          mean_currents->q = x / 1000.0F;

          /* '<S2>:99:30' i = i+1; */
          qY = localDW->i + /*MW:OvSatOk*/ 1U;
          if (localDW->i + 1U < localDW->i) {
            qY = MAX_uint32_T;
          }

          localDW->i = qY;
        }
        break;

       case 1006U:
        /* '<S2>:99:31' case array_size+6 */
        /* '<S2>:99:32' finished_calculation = true; */
        *finished_calculation = true;

        /* '<S2>:99:33' i = i+1; */
        qY = localDW->i + /*MW:OvSatOk*/ 1U;
        if (localDW->i + 1U < localDW->i) {
          qY = MAX_uint32_T;
        }

        localDW->i = qY;
        break;
      }
    } else {
      /* '<S2>:99:35' else */
      /* '<S2>:99:36' counter_time = counter_time +1; */
      qY = localDW->counter_time + /*MW:OvSatOk*/ 1U;
      if (localDW->counter_time + 1U < localDW->counter_time) {
        qY = MAX_uint32_T;
      }

      localDW->counter_time = qY;

      /* '<S2>:99:37' if((mod(counter_time,20)==0)&&i<=array_size) */
      if ((localDW->counter_time - localDW->counter_time / 20U * 20U == 0U) &&
          (localDW->i <= 1000U)) {
        /* '<S2>:99:38' i_d_array(i) = actual_currents.d; */
        localDW->i_d_array[(int32_T)localDW->i - 1] = actual_currents->d;

        /* '<S2>:99:39' i_q_array(i) = actual_currents.q; */
        localDW->i_q_array[(int32_T)localDW->i - 1] = actual_currents->q;

        /* '<S2>:99:40' u_d_array(i) = actual_voltages.d; */
        localDW->u_d_array[(int32_T)localDW->i - 1] = actual_voltages->d;

        /* '<S2>:99:41' u_q_array(i) = actual_voltages.q; */
        localDW->u_q_array[(int32_T)localDW->i - 1] = actual_voltages->q;

        /* '<S2>:99:42' omega_el_array(i) = omega_el; */
        localDW->omega_el_array[(int32_T)localDW->i - 1] = omega_el;

        /* '<S2>:99:43' i = i+1; */
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
void Fluxmap_enter(uint16_T *activeState, real32_T *PI_d_ref, real32_T *PI_q_ref,
                   const uz_ParaID_FluxMapIDConfig_t *FluxMapIDConfig,
                   DW_AMMstateIdentificationDQFl_t *localDW)
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

  /* '<S2>:90:5' NumberOfIDpoints = uint32(abs(FluxMapIDConfig.IDstop-FluxMapIDConfig.IDstart)/FluxMapIDConfig.IDstepsize+1); */
  tmp_0 = roundf(fabsf(FluxMapIDConfig->IDstop - FluxMapIDConfig->IDstart) /
                 FluxMapIDConfig->IDstepsize + 1.0F);
  if (tmp_0 < 4.2949673E+9F) {
    if (tmp_0 >= 0.0F) {
      localDW->NumberOfIDpoints = (uint32_T)tmp_0;
    } else {
      localDW->NumberOfIDpoints = 0U;
    }
  } else {
    localDW->NumberOfIDpoints = MAX_uint32_T;
  }

  /* '<S2>:90:6' NumberOfIQpoints = uint32(abs(FluxMapIDConfig.IQstop-FluxMapIDConfig.IQstart)/FluxMapIDConfig.IQstepsize+1); */
  /* '<S2>:90:7' NumberOfPoints = uint32(NumberOfIDpoints*NumberOfIQpoints); */
  tmp_0 = roundf(fabsf(FluxMapIDConfig->IQstop - FluxMapIDConfig->IQstart) /
                 FluxMapIDConfig->IQstepsize + 1.0F);
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

  /* '<S2>:90:8' PI_d_ref = single(0); */
  *PI_d_ref = 0.0F;

  /* '<S2>:90:9' PI_q_ref = single(0); */
  *PI_q_ref = 0.0F;

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
    /* '<S2>:99:47' FluxMapID_output.external_Measurement_Flag=boolean(0); */
    FluxMapID_output->external_Measurement_Flag = false;

    /* '<S2>:99:48' finished_calculation = false; */
    *finished_calculation = false;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;

   case IN_AMMcooling:
    /* Exit 'AMMcooling': '<S2>:94' */
    /* '<S2>:94:10' PI_d_ref = PI_d_loc; */
    *PI_d_ref = localDW->PI_d_loc_h;

    /* '<S2>:94:11' PI_q_ref = PI_q_loc; */
    *PI_q_ref = localDW->PI_q_loc_b;
    localDW->is_c14_Subchart_FluxMapID_refer = IN_NO_ACTIVE_CHILD;
    break;

   case IN_AMMheating:
    /* Exit 'AMMheating': '<S2>:88' */
    /* '<S2>:88:10' PI_d_ref = PI_d_loc; */
    *PI_d_ref = localDW->PI_d_loc;

    /* '<S2>:88:11' PI_q_ref = PI_q_loc; */
    *PI_q_ref = localDW->PI_q_loc;
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
  localDW->PI_d_loc = 0.0F;
  localDW->PI_q_loc = 0.0F;
  localDW->PI_d_loc_h = 0.0F;
  localDW->PI_q_loc_b = 0.0F;
  localDW->i = 1U;
  memset(&localDW->u_d_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->u_q_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->omega_el_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->i_d_array[0], 0, 1000U * sizeof(real32_T));
  memset(&localDW->i_q_array[0], 0, 1000U * sizeof(real32_T));
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function init
 */
static void init(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                 ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                 DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  real32_T tmp;

  /* Outport: '<Root>/extended_controller_output' */
  /* MATLAB Function 'init': '<S1>:868' */
  /* '<S1>:868:3' extended_controller_output.ab_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d = 0.0F;

  /* '<S1>:868:4' extended_controller_output.ab_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.q = 0.0F;

  /* '<S1>:868:5' extended_controller_output.xy_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.d = 0.0F;

  /* '<S1>:868:6' extended_controller_output.xy_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.q = 0.0F;

  /* '<S1>:868:7' extended_controller_output.zero_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.d =
    0.0F;

  /* '<S1>:868:8' extended_controller_output.zero_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.q =
    0.0F;

  /* '<S1>:868:9' extended_controller_output.finished_calculation=false; */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation =
    false;

  /* Outport: '<Root>/FluxMapID_FOC_output' */
  /* '<S1>:868:10' FluxMapID_FOC_output.enableFOC_current=boolean(1); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.enableFOC_current = true;

  /* Outport: '<Root>/extended_controller_output' */
  /* '<S1>:868:11' extended_controller_output.selected_subsystem = uint16(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem = 0U;

  /* '<S1>:868:12' extended_controller_output.psi_array = single([0;0;0;0]); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] = 0.0F;
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] = 0.0F;

  /* Inport: '<Root>/GlobalConfig' */
  /* '<S1>:868:13' one_sec_transition_counter = uint32(1/GlobalConfig.sampleTimeISR); */
  /* '<S1>:868:14' three_sec_transition_counter = uint32(3/GlobalConfig.sampleTimeISR); */
  tmp = roundf(3.0F / rtFluxMapID_6ph_codegen_U->GlobalConfig_out.sampleTimeISR);
  if (tmp < 4.2949673E+9F) {
    if (tmp >= 0.0F) {
      rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c = (uint32_T)tmp;
    } else {
      rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c = 0U;
    }
  } else {
    rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c = MAX_uint32_T;
  }
}

/* Function for Chart: '<Root>/FluxMapID_6ph_codegen' */
static void enter_atomic_Wait_select_subsys(ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y, DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW)
{
  /* Outport: '<Root>/FluxMapID_FOC_output' */
  /* Entry 'Wait_select_subsystem': '<S1>:762' */
  /* '<S1>:762:3' FluxMapID_FOC_output.activeState = uint16(400); */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState = 400U;

  /* '<S1>:762:4' FluxMapID_FOC_output.resetIntegrator = true; */
  rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = true;

  /* '<S1>:762:5' i_q_ref_AMM = single(0); */
  rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM = 0.0F;

  /* '<S1>:762:6' i_d_ref_AMM = single(0); */
  rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM = 0.0F;

  /* Outport: '<Root>/extended_controller_output' */
  /* '<S1>:762:7' extended_controller_output.ab_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d = 0.0F;

  /* '<S1>:762:8' extended_controller_output.ab_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.q = 0.0F;

  /* '<S1>:762:9' extended_controller_output.xy_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.d = 0.0F;

  /* '<S1>:762:10' extended_controller_output.xy_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.q = 0.0F;

  /* '<S1>:762:11' extended_controller_output.zero_i_dq_PI_ref.d = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.d =
    0.0F;

  /* '<S1>:762:12' extended_controller_output.zero_i_dq_PI_ref.q = single(0); */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.q =
    0.0F;

  /* '<S1>:762:13' extended_controller_output.finished_calculation=false; */
  rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation =
    false;
}

/* Function for Chart: '<Root>/FluxMapID_6ph_codegen' */
static void Wait_select_subsystem(ExtU_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_U, ExtY_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_Y, DW_FluxMapID_6ph_codegen_t
  *rtFluxMapID_6ph_codegen_DW)
{
  /* Outport: '<Root>/extended_controller_output' incorporates:
   *  Inport: '<Root>/ActualValues'
   *  Inport: '<Root>/FluxMapIDConfig'
   *  Inport: '<Root>/GlobalConfig'
   *  Inport: '<Root>/feedback_printed'
   *  Outport: '<Root>/FluxMapID_FOC_output'
   */
  /* During 'Wait_select_subsystem': '<S1>:762' */
  /* '<S1>:757:1' sf_internal_predicateOutput = extended_controller_output.selected_subsystem == 2 && GlobalConfig.ACCEPT==1; */
  if ((rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem ==
       2) && rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:757' */
    /* Exit 'Wait_select_subsystem': '<S1>:762' */
    /* '<S1>:762:17' FluxMapID_FOC_output.resetIntegrator = false; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationXY;

    /* Entry 'IdentificationXY': '<S1>:736' */
    /* '<S1>:736:3' extended_controller_output.psi_array = [0;0;0;0]; */
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] = 0.0F;

    /* Entry Internal 'IdentificationXY': '<S1>:736' */
    /* Transition: '<S1>:749' */
    rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_Fluxmap;
    Fluxmap_enter(&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
                  &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                  &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                  &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
                  &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);

    /* '<S1>:754:1' sf_internal_predicateOutput = extended_controller_output.selected_subsystem == 1 && GlobalConfig.ACCEPT==1; */
  } else if
      ((rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
        == 1) && rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:754' */
    /* Exit 'Wait_select_subsystem': '<S1>:762' */
    /* '<S1>:762:17' FluxMapID_FOC_output.resetIntegrator = false; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationDQ;

    /* Entry 'IdentificationDQ': '<S1>:717' */
    /* '<S1>:717:3' extended_controller_output.psi_array = [0;0;0;0]; */
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] = 0.0F;

    /* Entry Internal 'IdentificationDQ': '<S1>:717' */
    /* Transition: '<S1>:733' */
    rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_Fluxmap;
    Fluxmap_enter(&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
                  &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                  &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                  &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
                  &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);

    /* '<S1>:837:1' sf_internal_predicateOutput = FluxMapIDConfig.selected_subsystem == 3 && GlobalConfig.ACCEPT==1; */
  } else if ((rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem == 3)
             && rtFluxMapID_6ph_codegen_U->GlobalConfig_out.ACCEPT) {
    /* Transition: '<S1>:837' */
    /* Exit 'Wait_select_subsystem': '<S1>:762' */
    /* '<S1>:762:17' FluxMapID_FOC_output.resetIntegrator = false; */
    rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_IdentificationZero;

    /* Entry 'IdentificationZero': '<S1>:817' */
    /* '<S1>:817:3' extended_controller_output.psi_array = [0;0;0;0]; */
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] = 0.0F;
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] = 0.0F;

    /* Entry Internal 'IdentificationZero': '<S1>:817' */
    /* Transition: '<S1>:835' */
    rtFluxMapID_6ph_codegen_DW->is_IdentificationZero = IN_Fluxmap;
    Fluxmap_enter(&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
                  &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                  &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                  &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
                  &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
  } else {
    /* '<S1>:762:15' extended_controller_output.selected_subsystem = FluxMapIDConfig.selected_subsystem; */
    rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem =
      rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.selected_subsystem;
  }

  /* End of Outport: '<Root>/extended_controller_output' */
}

/*
 * Function for Chart: '<Root>/FluxMapID_6ph_codegen'
 * function psi = flux(u, i, omega_el, Rs)
 */
static real32_T flux(real32_T u, real32_T i, real32_T omega_el, real32_T Rs)
{
  /* MATLAB Function 'flux': '<S1>:857' */
  /* '<S1>:857:2' psi = (u-Rs*i)/omega_el; */
  return (u - Rs * i) / omega_el;
}

/* Function for Chart: '<Root>/FluxMapID_6ph_codegen' */
static void AMMstate(ExtU_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_U,
                     ExtY_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_Y,
                     DW_FluxMapID_6ph_codegen_t *rtFluxMapID_6ph_codegen_DW)
{
  /* Inport: '<Root>/GlobalConfig' */
  /* During 'AMMstate': '<S1>:590' */
  /* '<S1>:667:1' sf_internal_predicateOutput = GlobalConfig.Reset==1 || GlobalConfig.FluxMapID==0.... */
  /* '<S1>:667:2' || GlobalConfig.enableParameterID==0; */
  if (rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset ||
      (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.FluxMapID) ||
      (!rtFluxMapID_6ph_codegen_U->GlobalConfig_out.enableParameterID)) {
    /* Transition: '<S1>:667' */
    /* '<S1>:667:3' enteredFluxMapID=boolean(0); */
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
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_NO_ACTIVE_CHILD_b;
      }

      /* Outport: '<Root>/extended_controller_output' */
      /* Exit 'IdentificationDQ': '<S1>:717' */
      /* '<S1>:717:25' extended_controller_output.selected_subsystem = uint16(0); */
      rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem =
        0U;
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_b;
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
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_NO_ACTIVE_CHILD_b;
      }

      /* Outport: '<Root>/extended_controller_output' */
      /* Exit 'IdentificationXY': '<S1>:736' */
      /* '<S1>:736:25' extended_controller_output.selected_subsystem = uint16(0); */
      rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem =
        0U;
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_b;
      break;

     case IN_IdentificationZero:
      /* Exit Internal 'IdentificationZero': '<S1>:817' */
      if (rtFluxMapID_6ph_codegen_DW->is_IdentificationZero == 1) {
        /* Outport: '<Root>/FluxMapID_FOC_output' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/FluxMapIDConfig'
         *  Inport: '<Root>/feedback_printed'
         */
        Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                     &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                     &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                     &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
        rtFluxMapID_6ph_codegen_DW->is_IdentificationZero = IN_NO_ACTIVE_CHILD_b;
      }

      /* Outport: '<Root>/extended_controller_output' */
      /* Exit 'IdentificationZero': '<S1>:817' */
      /* '<S1>:817:25' extended_controller_output.selected_subsystem = uint16(0); */
      rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem =
        0U;
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_b;
      break;

     case IN_Wait_select_subsystem:
      /* Outport: '<Root>/FluxMapID_FOC_output' */
      /* Exit 'Wait_select_subsystem': '<S1>:762' */
      /* '<S1>:762:17' FluxMapID_FOC_output.resetIntegrator = false; */
      rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.resetIntegrator = false;
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_b;
      break;

     default:
      rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_b;
      break;
    }

    /* Outport: '<Root>/finishedFluxMapID' */
    /* Exit 'AMMstate': '<S1>:590' */
    /* '<S1>:590:11' counter = uint32(1); */
    /* '<S1>:590:12' finishedFluxMapID=boolean(1); */
    rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = true;

    /* Outport: '<Root>/enteredFluxMapID' */
    /* '<S1>:590:13' enteredFluxMapID = boolean(0); */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = false;
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
    /* FluxMapID */
    /* '<S1>:652:5' init; */
    init(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
         rtFluxMapID_6ph_codegen_DW);
  } else {
    /* SystemInitialize for Inport: '<Root>/ActualValues' */
    /* '<S1>:590:7' FluxMapID_output.WindingTemp = ActualValues.average_winding_temp; */
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp =
      rtFluxMapID_6ph_codegen_U->ActualValues.average_winding_temp;

    /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' */
    /* '<S1>:590:8' FluxMapID_output.R_s = FluxMapIDConfig.R_s_ref*... */
    /* '<S1>:590:9'     (single(1)+TEMP_COEFFICIENT*(FluxMapID_output.WindingTemp - FluxMapIDConfig.Temp_ref)); */
    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s =
      ((rtFluxMapID_6ph_codegen_DW->FluxMapID_output.WindingTemp -
        rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.Temp_ref) * TEMP_COEFFICIENT
       + 1.0F) * rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.R_s_ref;
    switch (rtFluxMapID_6ph_codegen_DW->is_AMMstate) {
     case IN_IdentificationDQ:
      {
        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/feedback_printed'
         *  Outport: '<Root>/FluxMapID_FOC_output'
         *  Outport: '<Root>/extended_controller_output'
         */
        /* During 'IdentificationDQ': '<S1>:717' */
        /* '<S1>:866:1' sf_internal_predicateOutput = FluxMapIDConfig.start_FM_ID==0 && extended_controller_output.selected_subsystem ~= 1; */
        if ((!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) &&
            (rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
             != 1)) {
          /* Transition: '<S1>:866' */
          /* Exit Internal 'IdentificationDQ': '<S1>:717' */
          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ == 1) {
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ =
              IN_NO_ACTIVE_CHILD_b;
          }

          /* Exit 'IdentificationDQ': '<S1>:717' */
          /* '<S1>:717:25' extended_controller_output.selected_subsystem = uint16(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
            = 0U;
          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
          enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
            rtFluxMapID_6ph_codegen_DW);
        } else {
          uint32_T exitPortIndex_l;

          /* '<S1>:717:5' if(FluxMapIDConfig.start_FM_ID==true) */
          if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
            /* '<S1>:717:6' extended_controller_output.ab_i_dq_PI_ref.d=i_d_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d
              = rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

            /* '<S1>:717:7' extended_controller_output.ab_i_dq_PI_ref.q=i_q_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.q
              = rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
          } else {
            /* '<S1>:717:8' else */
            /* '<S1>:717:9' extended_controller_output.ab_i_dq_PI_ref.d=single(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.d
              = 0.0F;

            /* '<S1>:717:10' extended_controller_output.ab_i_dq_PI_ref.q=single(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.ab_i_dq_PI_ref.q
              = 0.0F;
          }

          /* '<S1>:717:12' if(finished_calculation) */
          if (rtFluxMapID_6ph_codegen_DW->finished_calculation_b) {
            /* '<S1>:717:13' extended_controller_output.psi_array(1)=mean_currents.d; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_m.d;

            /* '<S1>:717:14' extended_controller_output.psi_array(2)=mean_currents.q; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_m.q;

            /* '<S1>:717:15' extended_controller_output.psi_array(3)=flux(mean_voltages.q, mean_currents.q,... */
            /* '<S1>:717:16'         mean_omega_el, FluxMapID_output.R_s); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] =
              flux(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q,
                   rtFluxMapID_6ph_codegen_DW->mean_currents_m.q,
                   rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
                   rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s);

            /* '<S1>:717:17' extended_controller_output.psi_array(4)=single(-1)*flux(mean_voltages.d, mean_currents.d,... */
            /* '<S1>:717:18'         mean_omega_el, FluxMapID_output.R_s); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] =
              -flux(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d,
                    rtFluxMapID_6ph_codegen_DW->mean_currents_m.d,
                    rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
                    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s);

            /* '<S1>:717:19' extended_controller_output.array_index = repetition_counter; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.array_index =
              rtFluxMapID_6ph_codegen_DW->repetition_counter;

            /* '<S1>:717:20' extended_controller_output.finished_calculation=true; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
              = true;
          } else {
            /* '<S1>:717:21' else */
            /* '<S1>:717:22' extended_controller_output.finished_calculation=false; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
              = false;
          }

          /* During 'Fluxmap': '<S1>:704' */
          Fluxmap_during
            (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
             &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
             &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
             &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
             rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c,
             &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
             &rtFluxMapID_6ph_codegen_U->ActualValues.v_dq,
             rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
             rtFluxMapID_6ph_codegen_U->feedback_printed,
             &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
             &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
             &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
             &rtFluxMapID_6ph_codegen_DW->mean_currents_m,
             &rtFluxMapID_6ph_codegen_DW->repetition_counter,
             &rtFluxMapID_6ph_codegen_U->ActualValues.i_dq,
             &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
          exitPortIndex_l = Fluxmap_getExitPortIndex
            (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
          if (exitPortIndex_l == 2U) {
            /* Transition: '<S1>:729' */
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ =
              IN_NO_ACTIVE_CHILD_b;
            rtFluxMapID_6ph_codegen_DW->exitPortIndex = 2U;
          }

          if (rtFluxMapID_6ph_codegen_DW->exitPortIndex == 2U) {
            rtFluxMapID_6ph_codegen_DW->exitPortIndex = 0U;

            /* Transition: '<S1>:765' */
            /* Exit 'IdentificationDQ': '<S1>:717' */
            /* '<S1>:717:25' extended_controller_output.selected_subsystem = uint16(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
              = 0U;
            rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
            enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
              rtFluxMapID_6ph_codegen_DW);
          }
        }
      }
      break;

     case IN_IdentificationXY:
      {
        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/feedback_printed'
         *  Outport: '<Root>/FluxMapID_FOC_output'
         *  Outport: '<Root>/extended_controller_output'
         */
        /* During 'IdentificationXY': '<S1>:736' */
        /* '<S1>:867:1' sf_internal_predicateOutput = FluxMapIDConfig.start_FM_ID==0 && extended_controller_output.selected_subsystem ~= 2; */
        if ((!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) &&
            (rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
             != 2)) {
          /* Transition: '<S1>:867' */
          /* Exit Internal 'IdentificationXY': '<S1>:736' */
          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationXY == 1) {
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationXY =
              IN_NO_ACTIVE_CHILD_b;
          }

          /* Exit 'IdentificationXY': '<S1>:736' */
          /* '<S1>:736:25' extended_controller_output.selected_subsystem = uint16(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
            = 0U;
          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
          enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
            rtFluxMapID_6ph_codegen_DW);
        } else {
          uint32_T exitPortIndex_l;

          /* '<S1>:736:5' if(FluxMapIDConfig.start_FM_ID==true) */
          if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
            /* '<S1>:736:6' extended_controller_output.xy_i_dq_PI_ref.d=i_d_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.d
              = rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

            /* '<S1>:736:7' extended_controller_output.xy_i_dq_PI_ref.q=i_q_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.q
              = rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
          } else {
            /* '<S1>:736:8' else */
            /* '<S1>:736:9' extended_controller_output.xy_i_dq_PI_ref.d=single(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.d
              = 0.0F;

            /* '<S1>:736:10' extended_controller_output.xy_i_dq_PI_ref.q=single(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.xy_i_dq_PI_ref.q
              = 0.0F;
          }

          /* '<S1>:736:12' if(finished_calculation) */
          if (rtFluxMapID_6ph_codegen_DW->finished_calculation_b) {
            /* '<S1>:736:13' extended_controller_output.psi_array(1)=mean_currents.d; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_m.d;

            /* '<S1>:736:14' extended_controller_output.psi_array(2)=mean_currents.q; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_m.q;

            /* '<S1>:736:15' extended_controller_output.psi_array(3)=single(-1)*flux(mean_voltages.q, mean_currents.q, ... */
            /* '<S1>:736:16'         mean_omega_el, FluxMapID_output.R_s); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] =
              -flux(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q,
                    rtFluxMapID_6ph_codegen_DW->mean_currents_m.q,
                    rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
                    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s);

            /* '<S1>:736:17' extended_controller_output.psi_array(4)=flux(mean_voltages.d, mean_currents.d, ... */
            /* '<S1>:736:18'         mean_omega_el, FluxMapID_output.R_s); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] =
              flux(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d,
                   rtFluxMapID_6ph_codegen_DW->mean_currents_m.d,
                   rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
                   rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s);

            /* '<S1>:736:19' extended_controller_output.array_index = repetition_counter; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.array_index =
              rtFluxMapID_6ph_codegen_DW->repetition_counter;

            /* '<S1>:736:20' extended_controller_output.finished_calculation=true; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
              = true;
          } else {
            /* '<S1>:736:21' else */
            /* '<S1>:736:22' extended_controller_output.finished_calculation=false; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
              = false;
          }

          /* During 'Fluxmap': '<S1>:748' */
          Fluxmap_during
            (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
             &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
             &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
             &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
             rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c,
             &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
             &rtFluxMapID_6ph_codegen_U->ActualValues.v_xy_rotating,
             rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
             rtFluxMapID_6ph_codegen_U->feedback_printed,
             &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
             &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
             &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
             &rtFluxMapID_6ph_codegen_DW->mean_currents_m,
             &rtFluxMapID_6ph_codegen_DW->repetition_counter,
             &rtFluxMapID_6ph_codegen_U->ActualValues.i_xy_rotating,
             &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
          exitPortIndex_l = Fluxmap_getExitPortIndex
            (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
          if (exitPortIndex_l == 2U) {
            /* Transition: '<S1>:750' */
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationXY =
              IN_NO_ACTIVE_CHILD_b;
            rtFluxMapID_6ph_codegen_DW->exitPortIndex_i = 2U;
          }

          if (rtFluxMapID_6ph_codegen_DW->exitPortIndex_i == 2U) {
            rtFluxMapID_6ph_codegen_DW->exitPortIndex_i = 0U;

            /* Transition: '<S1>:764' */
            /* Exit 'IdentificationXY': '<S1>:736' */
            /* '<S1>:736:25' extended_controller_output.selected_subsystem = uint16(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
              = 0U;
            rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
            enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
              rtFluxMapID_6ph_codegen_DW);
          }
        }
      }
      break;

     case IN_IdentificationZero:
      {
        /* SystemInitialize for Inport: '<Root>/FluxMapIDConfig' incorporates:
         *  Inport: '<Root>/ActualValues'
         *  Inport: '<Root>/feedback_printed'
         *  Outport: '<Root>/FluxMapID_FOC_output'
         *  Outport: '<Root>/extended_controller_output'
         */
        /* During 'IdentificationZero': '<S1>:817' */
        /* '<S1>:865:1' sf_internal_predicateOutput = FluxMapIDConfig.start_FM_ID==0 && extended_controller_output.selected_subsystem ~= 3; */
        if ((!rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) &&
            (rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
             != 3)) {
          /* Transition: '<S1>:865' */
          /* Exit Internal 'IdentificationZero': '<S1>:817' */
          if (rtFluxMapID_6ph_codegen_DW->is_IdentificationZero == 1) {
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationZero =
              IN_NO_ACTIVE_CHILD_b;
          }

          /* Exit 'IdentificationZero': '<S1>:817' */
          /* '<S1>:817:25' extended_controller_output.selected_subsystem = uint16(0); */
          rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
            = 0U;
          rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
          enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
            rtFluxMapID_6ph_codegen_DW);
        } else {
          uint32_T exitPortIndex_l;

          /* '<S1>:817:5' if(FluxMapIDConfig.start_FM_ID==true) */
          if (rtFluxMapID_6ph_codegen_U->FluxMapIDConfig.start_FM_ID) {
            /* '<S1>:817:6' extended_controller_output.zero_i_dq_PI_ref.d=i_d_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.d
              = rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM;

            /* '<S1>:817:7' extended_controller_output.zero_i_dq_PI_ref.q=i_q_ref_AMM; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.q
              = rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM;
          } else {
            /* '<S1>:817:8' else */
            /* '<S1>:817:9' extended_controller_output.zero_i_dq_PI_ref.d=single(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.d
              = 0.0F;

            /* '<S1>:817:10' extended_controller_output.zero_i_dq_PI_ref.q=single(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.zero_i_dq_PI_ref.q
              = 0.0F;
          }

          /* '<S1>:817:12' if(finished_calculation) */
          if (rtFluxMapID_6ph_codegen_DW->finished_calculation_b) {
            /* '<S1>:817:13' extended_controller_output.psi_array(1)=mean_currents.d; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[0] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_m.d;

            /* '<S1>:817:14' extended_controller_output.psi_array(2)=mean_currents.q; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[1] =
              rtFluxMapID_6ph_codegen_DW->mean_currents_m.q;

            /* '<S1>:817:15' extended_controller_output.psi_array(3)=flux(mean_voltages.q, mean_currents.q, ... */
            /* '<S1>:817:16'         mean_omega_el, FluxMapID_output.R_s)/single(3); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[2] =
              flux(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q,
                   rtFluxMapID_6ph_codegen_DW->mean_currents_m.q,
                   rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
                   rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) / 3.0F;

            /* '<S1>:817:17' extended_controller_output.psi_array(4)=single(-1)*flux(mean_voltages.d, mean_currents.d, ... */
            /* '<S1>:817:18'         mean_omega_el, FluxMapID_output.R_s)/single(3); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.psi_array[3] =
              -flux(rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d,
                    rtFluxMapID_6ph_codegen_DW->mean_currents_m.d,
                    rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
                    rtFluxMapID_6ph_codegen_DW->FluxMapID_output.R_s) / 3.0F;

            /* '<S1>:817:19' extended_controller_output.array_index = repetition_counter; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.array_index =
              rtFluxMapID_6ph_codegen_DW->repetition_counter;

            /* '<S1>:817:20' extended_controller_output.finished_calculation=true; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
              = true;
          } else {
            /* '<S1>:817:21' else */
            /* '<S1>:817:22' extended_controller_output.finished_calculation=false; */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.finished_calculation
              = false;
          }

          /* During 'Fluxmap': '<S1>:830' */
          Fluxmap_during
            (&rtFluxMapID_6ph_codegen_Y->FluxMapID_FOC_output.activeState,
             &rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
             &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
             &rtFluxMapID_6ph_codegen_U->FluxMapIDConfig,
             rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c,
             &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
             &rtFluxMapID_6ph_codegen_U->ActualValues.v_zero_rotating,
             rtFluxMapID_6ph_codegen_U->ActualValues.omega_el,
             rtFluxMapID_6ph_codegen_U->feedback_printed,
             &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
             &rtFluxMapID_6ph_codegen_DW->mean_voltages_c,
             &rtFluxMapID_6ph_codegen_DW->mean_omega_el_k,
             &rtFluxMapID_6ph_codegen_DW->mean_currents_m,
             &rtFluxMapID_6ph_codegen_DW->repetition_counter,
             &rtFluxMapID_6ph_codegen_U->ActualValues.i_zero_rotating,
             &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
          exitPortIndex_l = Fluxmap_getExitPortIndex
            (&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
          if (exitPortIndex_l == 2U) {
            /* Transition: '<S1>:836' */
            Fluxmap_exit(&rtFluxMapID_6ph_codegen_DW->i_d_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->i_q_ref_AMM,
                         &rtFluxMapID_6ph_codegen_DW->FluxMapID_output,
                         &rtFluxMapID_6ph_codegen_DW->finished_calculation_b,
                         &rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
            rtFluxMapID_6ph_codegen_DW->is_IdentificationZero =
              IN_NO_ACTIVE_CHILD_b;
            rtFluxMapID_6ph_codegen_DW->exitPortIndex_o = 2U;
          }

          if (rtFluxMapID_6ph_codegen_DW->exitPortIndex_o == 2U) {
            rtFluxMapID_6ph_codegen_DW->exitPortIndex_o = 0U;

            /* Transition: '<S1>:838' */
            /* Exit 'IdentificationZero': '<S1>:817' */
            /* '<S1>:817:25' extended_controller_output.selected_subsystem = uint16(0); */
            rtFluxMapID_6ph_codegen_Y->extended_controller_output.selected_subsystem
              = 0U;
            rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
            enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
              rtFluxMapID_6ph_codegen_DW);
          }
        }
      }
      break;

     default:
      Wait_select_subsystem(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
                            rtFluxMapID_6ph_codegen_DW);
      break;
    }
  }

  /* End of Inport: '<Root>/GlobalConfig' */
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
    /* '<S1>:652:5' init; */
    init(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
         rtFluxMapID_6ph_codegen_DW);
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

    /* Outport: '<Root>/finishedFluxMapID' */
    /* Entry 'AMMstate': '<S1>:590' */
    /* '<S1>:590:4' finishedFluxMapID=boolean(0); */
    rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = false;

    /* Outport: '<Root>/enteredFluxMapID' */
    /* '<S1>:590:5' enteredFluxMapID = boolean(1); */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = true;

    /* Entry Internal 'AMMstate': '<S1>:590' */
    /* Transition: '<S1>:763' */
    rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_Wait_select_subsystem;
    enter_atomic_Wait_select_subsys(rtFluxMapID_6ph_codegen_Y,
      rtFluxMapID_6ph_codegen_DW);

    /* '<S1>:680:1' sf_internal_predicateOutput = GlobalConfig.Reset==1; */
  } else if (rtFluxMapID_6ph_codegen_U->GlobalConfig_out.Reset) {
    /* Outport: '<Root>/finishedFluxMapID' */
    /* Transition: '<S1>:680' */
    /* '<S1>:680:1' finishedFluxMapID=boolean(0); */
    rtFluxMapID_6ph_codegen_Y->finishedFluxMapID = false;

    /* Outport: '<Root>/enteredFluxMapID' */
    /* '<S1>:680:2' enteredFluxMapID=boolean(0); */
    rtFluxMapID_6ph_codegen_Y->enteredFluxMapID = false;
    rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen = IN_Waiting;

    /* Entry 'Waiting': '<S1>:652' */
    /* wait for activation of */
    /* FluxMapID */
    /* '<S1>:652:5' init; */
    init(rtFluxMapID_6ph_codegen_U, rtFluxMapID_6ph_codegen_Y,
         rtFluxMapID_6ph_codegen_DW);
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
   *  Inport: '<Root>/feedback_printed'
   *  Outport: '<Root>/FluxMapID_FOC_output'
   */
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationDQFlux);
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationXYFlux);
  Fluxmap_init(&rtFluxMapID_6ph_codegen_DW->sf_AMMstateIdentificationZeroFl);
  rtFluxMapID_6ph_codegen_DW->is_AMMstate = IN_NO_ACTIVE_CHILD_b;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationDQ = IN_NO_ACTIVE_CHILD_b;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationXY = IN_NO_ACTIVE_CHILD_b;
  rtFluxMapID_6ph_codegen_DW->is_IdentificationZero = IN_NO_ACTIVE_CHILD_b;
  rtFluxMapID_6ph_codegen_DW->is_active_c16_FluxMapID_6ph_cod = 0U;
  rtFluxMapID_6ph_codegen_DW->is_c16_FluxMapID_6ph_codegen =
    IN_NO_ACTIVE_CHILD_b;
  memset(&rtFluxMapID_6ph_codegen_DW->R_s_array[0], 0, 50U * sizeof(real32_T));
  rtFluxMapID_6ph_codegen_DW->three_sec_transition_counter_c = 0U;
  rtFluxMapID_6ph_codegen_DW->mean_omega_el_k = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.d = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.q = 0.0F;
  rtFluxMapID_6ph_codegen_DW->mean_voltages_c.zero = 0.0F;
  rtFluxMapID_6ph_codegen_DW->finished_calculation_b = false;
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