#pragma once

#define  IPCore_Reset_parallel_8_sim_switching_states         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_8_sim_switching_states        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_8_sim_switching_states     0x8  //contains unique IP timestamp (yymmddHHMM): 2211160942
#define  min_Index_AXI_Data_parallel_8_sim_switching_states   0x100  //data register for Outport min_Index_AXI