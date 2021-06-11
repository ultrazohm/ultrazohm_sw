#ifndef TEST
// ISR trigger source
//chose here which of the above interrupt trigger you want to use:
// 0 for Interrupt_2L_max_min		
// 1 for Interrupt_2L_min			
// 2 for Interrupt_2L_max			
// 3 for Interrupt_3L_start_center	
// 4 for Interrupt_3L_start			
// 5 for Interrupt_3L_center		
// 6 for Interrupt_timer_fcc		
#define Interrupt_ISR_source_user_choice        3
#define UZ_WAVEGEN_CHIRP_MAX_INSTANCES          2
#define UZ_WAVEGEN_THREE_PHASE_MAX_INSTANCES    2
#endif

#ifdef TEST
	#define UZ_WAVEGEN_CHIRP_MAX_INSTANCES          13
    #define UZ_WAVEGEN_THREE_PHASE_MAX_INSTANCES    5
#endif
