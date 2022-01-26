#pragma once
#ifndef TEST

// Hardware version of the UltraZohm
#define UZ_HARDWARE_VERSION 4U

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
#define Interrupt_ISR_source_user_choice        2U

#define UZ_D5_INCREMENTAL_ENCODER_RESOLUTION    5000.0f
#define UZ_D5_MOTOR_POLE_PAIR_NUMBER            4.0f
#define UZ_PWM_FREQUENCY                        10.0e3f


// Configuration defines for the number of used instances
#define UZ_WAVEGEN_CHIRP_MAX_INSTANCES                  2U
#define UZ_WAVEGEN_THREE_PHASE_MAX_INSTANCES            2U
#define UZ_MYIP2_MAX_INSTANCES                          0U
#define UZ_ADCLTC2311_MAX_INSTANCES                     3U
#define UZ_PI_CONTROLLER_MAX_INSTANCES                  5U
#define UZ_FOC_MAX_INSTANCES                            2U
#define UZ_INCREMENTALENCODER_MAX_INSTANCES             1U
#define UZ_PWM_SS_2L_MAX_INSTANCES                      3U
#define UZ_MATRIX_MAX_INSTANCES                         0U
#define UZ_NN_LAYER_MAX_INSTANCES                       0U
#define UZ_NN_MAX_INSTANCES                             0U
#define UZ_PMSMMODEL_MAX_INSTANCES                      1U
#define UZ_DQ_TRANSFORMATION_IP_CORE_MAX_INSTANCES      1U
#define UZ_PARAMETERID_ACTIVE                           1U
#endif

// Configuration defines for the number of used instances for testing with ceedling
#ifdef TEST
    #define UZ_WAVEGEN_CHIRP_MAX_INSTANCES                  13U
    #define UZ_WAVEGEN_THREE_PHASE_MAX_INSTANCES            5U
    #define UZ_MYIP2_MAX_INSTANCES                          5U
    #define UZ_MYIP_MAX_INSTANCES                           5U
    #define UZ_ADCLTC2311_MAX_INSTANCES                     50U
    #define UZ_PI_CONTROLLER_MAX_INSTANCES                  100U
    #define UZ_FOC_MAX_INSTANCES                            100U
    #define UZ_INCREMENTALENCODER_MAX_INSTANCES             5U
    #define UZ_MATRIX_MAX_INSTANCES                         201U
    #define UZ_NN_LAYER_MAX_INSTANCES                       100U
    #define UZ_NN_MAX_INSTANCES                             10U
	#define UZ_PWM_SS_2L_MAX_INSTANCES                      50U
	#define UZ_MATRIX_MAX_INSTANCES                         201U
    #define UZ_PMSMMODEL_MAX_INSTANCES                      11U
    #define UZ_PLANTPT1_MAX_INSTANCES                       6U
    #define UZ_DQ_TRANSFORMATION_IP_CORE_MAX_INSTANCES      11U
#define UZ_PARAMETERID_ACTIVE                           1U
#endif
