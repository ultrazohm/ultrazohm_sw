#pragma once
#ifndef TEST

// Hardware version of the UltraZohm
#define UZ_HARDWARE_VERSION 4U

// If Hardware version is v4 and the external STOP should be used, this define has to be set to 1. Otherwise, the external stop does nothing.
// For Version 3, the external STOP always works, but the hardware loopback is required if no external stop is used.
#define UZ_USE_EXTERNAL_STOP 0U

#if (UZ_HARDWARE_VERSION < 4U) && (UZ_USE_EXTERNAL_STOP == 1U)
#error The UZ_USE_EXTERNAL_STOP flag must not be used on hardware version 3 or earlier. For hardware version 3, external stop can be used without the flag, prior versions to 3 do not have this feature.
#endif

#define UZ_HARDWARE_VERSION_MAX 6U // highest supported revision

/** ISR trigger source
 *
 * Choose here which PWM interrupt trigger you want to use.
 * If a 2L PWM trigger is selected, ensure that uz_PWM_SS_2L_config_t.trigger_source is aligned.
 * 0 for Interrupt_2L_max_min
 * 1 for Interrupt_2L_min
 * 2 for Interrupt_2L_max
 * 3 for Interrupt_3L_start_center
 * 4 for Interrupt_3L_start
 * 5 for Interrupt_3L_center
*/
#define INTERRUPT_ISR_SOURCE_USER_CHOICE        1U

#define INTERRUPT_ISR_TRIGGER_ON_ADC_DATA_READY 0U // 0: ISR triggers on selected PWM event. 1: ISR triggers on axi2tcm_write_done (ADC data in TCM). See r5_interrupts in docs.
#define INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE  1U  // Trigger the ADC at every PWM event, but trigger ISR_Control only every N-th interrupt event
#define ADC_TRIGGER_DELAY_IN_US                 0.01f // ADC trigger delay in us; applies in both ISR trigger modes. 10ns delay to keep default behavior. See uz_mux_axi in docs.

#define UZ_PWM_FREQUENCY                        10.0e3f
#define UZ_PWM_DEADTIME_IN_US                   1.0f
#define UZ_PWM_MINIMUM_PULSE_WIDTH_IN_US        0.5f

#define UZ_D5_INCREMENTAL_ENCODER_RESOLUTION    5000.0f
#define UZ_D5_MOTOR_POLE_PAIR_NUMBER            4.0f

// Configuration defines for the number of used instances
#define UZ_WAVEGEN_CHIRP_MAX_INSTANCES                  2U
#define UZ_MYIP2_MAX_INSTANCES                          0U
#define UZ_ADCLTC2311_MAX_INSTANCES                     3U
#define UZ_PI_CONTROLLER_MAX_INSTANCES                  3U
#define UZ_CURRENTCONTROL_MAX_INSTANCES                 2U
#define UZ_INCREMENTALENCODER_MAX_INSTANCES             1U
#define UZ_PWM_SS_2L_MAX_INSTANCES                      4U
#define UZ_NN_LAYER_MAX_INSTANCES                       0U
#define UZ_NN_MAX_INSTANCES                             0U
#define UZ_PMSMMODEL_MAX_INSTANCES                      0U
#define UZ_DQ_TRANSFORMATION_IP_CORE_MAX_INSTANCES      1U
#define UZ_MUX_AXI_MAX_INSTANCES                        1U
#define UZ_SPEEDCONTROL_MAX_INSTANCES                   1U
#define UZ_IIR_FILTER_MAX_INSTANCES                     1U
#define UZ_RAMP_MAX_INSTANCES                           1U
#define UZ_PARAMETERID_MAX_INSTANCES					1U
#define UZ_DAC_INTERFACE_MAX_INSTANCES                  0U
#define UZ_INVERTER_3PH_MAX_INSTANCES                   3U
#define UZ_PMSM6PH_TRANSFORMATION_MAX_INSTANCES         0U
#define UZ_PMSM9PH_TRANSFORMATION_MAX_INSTANCES         0U
#define UZ_SETPOINT_MAX_INSTANCES                       1U
#define UZ_PMSM_MODEL6PH_DQ_MAX_INSTANCES               0U
#define UZ_PMSM_MODEL9PH_DQ_MAX_INSTANCES               0U
#define UZ_SETPOINT_MAX_INSTANCES                       1U
#define UZ_INVERTER_3PH_MAX_INSTANCES                   3U
#define UZ_RESONANT_CONTROLLER_MAX_INSTANCES            0U
#define UZ_MOVINGAVERAGEFILTER_MAX_INSTANCES            0U
#define UZ_INVERTER_ADAPTER_MAX_INSTANCES               3U
#define UZ_TEMPERATURE_CARD_MAX_INSTANCES               0U
#define UZ_RESOLVERIP_MAX_INSTANCES                     3U
#define UZ_SYSMON_PS_MAX_INSTANCES                      0U // Can only be 1 or 0!
#define UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES          3U
#define UZ_AXI_GPIO_MAX_INSTANCES                       0U
#define UZ_6PH_OPEN_PHASE_FAULT_DETECTION               2U
#define UZ_ENCODER_OFFSET_ESTIMATION_MAX_INSTANCES      0U
#define UZ_FILTER_CUMULATIVEAVG_MAX_INSTANCES           0U
#define UZ_DQ_SETPOINT_FILTER_MAX_INSTANCES             0U
#define UZ_SUBSYSTEM_RESONANT_CONTROL_MAX_INSTANCES     0U
#define UZ_TRAJECTORY_MAX_INSTANCES                     0U
#define UZ_APPROXIMATE_FLUX_MAX_INSTANCES               0U
#define UZ_NN_ACC_IP_MAX_INSTANCES                  	0U
#define UZ_PRNG_SQUARES_MAX_INSTANCES                   0U
#define UZ_PRNG_MTWISTER_MAX_INSTANCES                  0U
#define UZ_PRNG_PCG_MAX_INSTANCES                       0U
#define UZ_PRNG_XOSHIRO_MAX_INSTANCES                   0U
#define UZ_PRNG_HALTON_MAX_INSTANCES                    0U
#define UZ_PRNG_MAX_INSTANCES                           0U
#define UZ_POS_TO_SPEED_PLL_MAX_INSTANCES               0U
#define UZ_PMSM_SWMODEL_MAX_INSTANCES                   0U
#define UZ_LUT_1D_MAX_INSTANCES                         0U
#define UZ_PMSMMODEL_6PH_DQXY_MAX_INSTANCES             0U
#define UZ_ENDAT_INTERFACE_MAX_INSTANCES				0U
#define UZ_SSI_INTERFACE_MAX_INSTANCES					0U
#endif

// Configuration defines for the number of used instances for testing with ceedling
#ifdef TEST
    #define UZ_WAVEGEN_CHIRP_MAX_INSTANCES                  13U
    #define UZ_DAC_INTERFACE_MAX_INSTANCES                  10U
    #define UZ_MYIP2_MAX_INSTANCES                          5U
    #define UZ_MYIP_MAX_INSTANCES                           5U
    #define UZ_ADCLTC2311_MAX_INSTANCES                     50U
    #define UZ_PI_CONTROLLER_MAX_INSTANCES                  100U
    #define UZ_CURRENTCONTROL_MAX_INSTANCES                 100U
    #define UZ_INCREMENTALENCODER_MAX_INSTANCES             20U
    #define UZ_NN_LAYER_MAX_INSTANCES                       100U
    #define UZ_NN_MAX_INSTANCES                             20U
    #define UZ_PWM_SS_2L_MAX_INSTANCES                      50U
    #define UZ_MATRIX_MAX_INSTANCES                         201U
    #define UZ_PMSMMODEL_MAX_INSTANCES                      11U
    #define UZ_PLANTPT1_MAX_INSTANCES                       6U
    #define UZ_DQ_TRANSFORMATION_IP_CORE_MAX_INSTANCES      11U
    #define UZ_FILTER_1ST_ORDER_INSTANCES                   20U
    #define UZ_MUX_AXI_MAX_INSTANCES                        10U
    #define UZ_MLP_THREE_LAYER_IP_MAX_INSTANCES             20U
    #define UZ_SPEEDCONTROL_MAX_INSTANCES                   50U
    #define UZ_IIR_FILTER_MAX_INSTANCES                     20U
    #define UZ_RAMP_MAX_INSTANCES                           20U
    #define UZ_INVERTER_3PH_MAX_INSTANCES                   20U
    #define UZ_PMSM6PH_TRANSFORMATION_MAX_INSTANCES         20U
    #define UZ_PARAMETERID_MAX_INSTANCES		    		100U
    #define UZ_PMSM9PH_TRANSFORMATION_MAX_INSTANCES         20U
    #define UZ_PMSM_MODEL6PH_DQ_MAX_INSTANCES               20U
    #define UZ_PMSM_MODEL9PH_DQ_MAX_INSTANCES               20U
    #define UZ_SETPOINT_MAX_INSTANCES                       50U
    #define UZ_INVERTER_3PH_MAX_INSTANCES                   20U
    #define UZ_RESONANT_CONTROLLER_MAX_INSTANCES            6U
    #define UZ_SUM_MAX_INSTANCES                            5U
    #define UZ_MOVINGAVERAGEFILTER_MAX_INSTANCES            50U
    #define UZ_INVERTER_ADAPTER_MAX_INSTANCES               20U
    #define UZ_EXP_SMOOTH_MAX_INSTANCES                     5U
    #define UZ_TEMPERATURE_CARD_MAX_INSTANCES               10U
    #define UZ_RESOLVERIP_MAX_INSTANCES                     40U
    #define UZ_SYSMON_PS_MAX_INSTANCES                      10U 
    #define UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES          30U
    #define UZ_AXI_GPIO_MAX_INSTANCES                       10U
    #define UZ_6PH_OPEN_PHASE_FAULT_DETECTION               2U
    #define UZ_ENCODER_OFFSET_ESTIMATION_MAX_INSTANCES      10U
    #define UZ_FILTER_CUMULATIVEAVG_MAX_INSTANCES           20U
    #define UZ_DQ_SETPOINT_FILTER_MAX_INSTANCES             10U
    #define UZ_SUBSYSTEM_RESONANT_CONTROL_MAX_INSTANCES     10U
    #define UZ_TRAJECTORY_MAX_INSTANCES                     50U
    #define UZ_APPROXIMATE_FLUX_MAX_INSTANCES               5U
    #define UZ_NN_ACC_IP_MAX_INSTANCES                      100U
    #define UZ_PMSMMODEL_6PH_DQXY_MAX_INSTANCES             50U
    #define UZ_PRNG_SQUARES_MAX_INSTANCES                   50U
    #define UZ_PRNG_MTWISTER_MAX_INSTANCES                  50U
    #define UZ_PRNG_PCG_MAX_INSTANCES                       50U
    #define UZ_PRNG_XOSHIRO_MAX_INSTANCES                   50U
    #define UZ_PRNG_HALTON_MAX_INSTANCES                    50U
    #define UZ_PRNG_MAX_INSTANCES                           50U
    #define UZ_POS_TO_SPEED_PLL_MAX_INSTANCES               50U
    #define UZ_PMSM_SWMODEL_MAX_INSTANCES                   10U
    #define UZ_LUT_1D_MAX_INSTANCES                         20U
    #define UZ_ENDAT_INTERFACE_MAX_INSTANCES		    	30U
    #define UZ_SSI_INTERFACE_MAX_INSTANCES		    		30U
#endif
