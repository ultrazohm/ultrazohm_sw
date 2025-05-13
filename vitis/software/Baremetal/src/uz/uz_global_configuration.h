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

#define UZ_HARDWARE_VERSION_MAX 5U // highest supported revision

/** ISR trigger source
 *
 * chose here which of the above interrupt trigger you want to use:
 * 0 for Interrupt_2L_max_min
 * 1 for Interrupt_2L_min
 * 2 for Interrupt_2L_max
 * 3 for Interrupt_3L_start_center
 * 4 for Interrupt_3L_start
 * 5 for Interrupt_3L_center
 * 6 for Interrupt_timer_fcc
*/
#define INTERRUPT_ISR_SOURCE_USER_CHOICE        1U
#define INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE	1U

#define UZ_D5_INCREMENTAL_ENCODER_RESOLUTION    5000.0f
#define UZ_D5_MOTOR_POLE_PAIR_NUMBER            4.0f
#define UZ_PWM_FREQUENCY                        10.0e3f

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
    #define UZ_INVERTER_3PH_MAX_INSTANCES                   20U
    #define UZ_PMSM6PH_TRANSFORMATION_MAX_INSTANCES         20U
	#define UZ_PARAMETERID_MAX_INSTANCES					100U
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
    #define UZ_NN_ACC_IP_MAX_INSTANCES                  	100U
#endif
