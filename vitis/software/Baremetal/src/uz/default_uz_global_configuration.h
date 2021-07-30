#ifndef TEST

// Hardware version of the UltraZohm
#define UZ_HARDWARE_VERSION 3U

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
#define Interrupt_ISR_source_user_choice        3U

// Configuration defines for the number of used instances
#define UZ_WAVEGEN_CHIRP_MAX_INSTANCES          2U
#define UZ_WAVEGEN_THREE_PHASE_MAX_INSTANCES    2U
#define UZ_MYIP2_MAX_INSTANCES                  0U
#define UZ_FOC_PI_CONTROLLER_MAX_INSTANCES      3U
#endif

// Configuration defines for the number of used instances for testing with ceedling
#ifdef TEST
    #define UZ_WAVEGEN_CHIRP_MAX_INSTANCES          13U
    #define UZ_WAVEGEN_THREE_PHASE_MAX_INSTANCES    5U
    #define UZ_MYIP2_MAX_INSTANCES                  5U
    #define UZ_MYIP_MAX_INSTANCES                   5U
    #define UZ_FOC_PI_CONTROLLER_MAX_INSTANCES      30U
#endif
