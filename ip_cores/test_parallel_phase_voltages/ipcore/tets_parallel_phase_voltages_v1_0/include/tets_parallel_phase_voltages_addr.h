/*
 * File Name:         C:\ultrazohm_sw\ip_cores\test_parallel_phase_voltages\ipcore\tets_parallel_phase_voltages_v1_0\include\tets_parallel_phase_voltages_addr.h
 * Description:       C Header File
 * Created:           2022-10-07 10:12:40
*/

#ifndef TETS_PARALLEL_PHASE_VOLTAGES_H_
#define TETS_PARALLEL_PHASE_VOLTAGES_H_

#define  IPCore_Reset_tets_parallel_phase_voltages                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_tets_parallel_phase_voltages                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_tets_parallel_phase_voltages             0x8  //contains unique IP timestamp (yymmddHHMM): 2210071012
#define  theta_el_offset_AXI_Data_tets_parallel_phase_voltages     0x100  //data register for Inport theta_el_offset_AXI
#define  u_dc_link_voltage_AXI_Data_tets_parallel_phase_voltages   0x104  //data register for Inport u_dc_link_voltage_AXI

#endif /* TETS_PARALLEL_PHASE_VOLTAGES_H_ */
