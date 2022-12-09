/*
 * File Name:         C:\ultrazohm_sw\ip_cores\parallel_8_phase_voltages\ipcore\parallel_8_sim_phase_voltages_v1_0\include\parallel_8_sim_phase_voltages_addr.h
 * Description:       C Header File
 * Created:           2022-12-08 12:16:47
*/

#ifndef PARALLEL_8_SIM_PHASE_VOLTAGES_H_
#define PARALLEL_8_SIM_PHASE_VOLTAGES_H_

#define  IPCore_Reset_parallel_8_sim_phase_voltages                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_8_sim_phase_voltages                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_8_sim_phase_voltages             0x8  //contains unique IP timestamp (yymmddHHMM): 2212081216
#define  theta_el_offset_AXI_Data_parallel_8_sim_phase_voltages     0x100  //data register for Inport theta_el_offset_AXI
#define  u_dc_link_voltage_AXI_Data_parallel_8_sim_phase_voltages   0x104  //data register for Inport u_dc_link_voltage_AXI

#endif /* PARALLEL_8_SIM_PHASE_VOLTAGES_H_ */
