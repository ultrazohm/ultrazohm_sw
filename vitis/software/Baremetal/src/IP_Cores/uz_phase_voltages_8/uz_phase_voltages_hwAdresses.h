#pragma once

#define  IPCore_Reset_parallel_8_sim_phase_voltages                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_8_sim_phase_voltages                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_8_sim_phase_voltages             0x8  //contains unique IP timestamp (yymmddHHMM): 2211231226
#define  theta_el_offset_AXI_Data_parallel_8_sim_phase_voltages     0x100  //data register for Inport theta_el_offset_AXI
#define  u_dc_link_voltage_AXI_Data_parallel_8_sim_phase_voltages   0x104  //data register for Inport u_dc_link_voltage_AXI
#define  Index_in_AXI_Data_parallel_8_sim_phase_voltages            0x108  //data register for Outport Index_in_AXI
