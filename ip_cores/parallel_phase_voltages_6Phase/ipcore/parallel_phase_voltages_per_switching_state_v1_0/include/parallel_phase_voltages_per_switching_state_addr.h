/*
 * File Name:         C:\ultrazohm_sw\ip_cores\parallel_phase_voltages_6Phase\ipcore\parallel_phase_voltages_per_switching_state_v1_0\include\parallel_phase_voltages_per_switching_state_addr.h
 * Description:       C Header File
 * Created:           2022-10-06 14:16:16
*/

#ifndef PARALLEL_PHASE_VOLTAGES_PER_SWITCHING_STATE_H_
#define PARALLEL_PHASE_VOLTAGES_PER_SWITCHING_STATE_H_

#define  IPCore_Reset_parallel_phase_voltages_per_switching_state                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_phase_voltages_per_switching_state                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_phase_voltages_per_switching_state             0x8  //contains unique IP timestamp (yymmddHHMM): 2210061416
#define  theta_el_offset_AXI_Data_parallel_phase_voltages_per_switching_state     0x100  //data register for Inport theta_el_offset_AXI
#define  u_dc_link_voltage_AXI_Data_parallel_phase_voltages_per_switching_state   0x104  //data register for Inport u_dc_link_voltage_AXI

#endif /* PARALLEL_PHASE_VOLTAGES_PER_SWITCHING_STATE_H_ */
