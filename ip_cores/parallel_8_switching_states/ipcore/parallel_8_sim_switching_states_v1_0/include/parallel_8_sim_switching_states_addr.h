/*
 * File Name:         C:\ultrazohm_sw\ip_cores\parallel_8_switching_states\ipcore\parallel_8_sim_switching_states_v1_0\include\parallel_8_sim_switching_states_addr.h
 * Description:       C Header File
 * Created:           2022-11-16 09:43:00
*/

#ifndef PARALLEL_8_SIM_SWITCHING_STATES_H_
#define PARALLEL_8_SIM_SWITCHING_STATES_H_

#define  IPCore_Reset_parallel_8_sim_switching_states         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_8_sim_switching_states        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_8_sim_switching_states     0x8  //contains unique IP timestamp (yymmddHHMM): 2211160942
#define  min_Index_AXI_Data_parallel_8_sim_switching_states   0x100  //data register for Outport min_Index_AXI

#endif /* PARALLEL_8_SIM_SWITCHING_STATES_H_ */