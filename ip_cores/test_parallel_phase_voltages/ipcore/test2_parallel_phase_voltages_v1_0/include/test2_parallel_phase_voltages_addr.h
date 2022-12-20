/*
 * File Name:         C:\ultrazohm_sw\ip_cores\test_parallel_phase_voltages\ipcore\test2_parallel_phase_voltages_v1_0\include\test2_parallel_phase_voltages_addr.h
 * Description:       C Header File
 * Created:           2022-10-10 13:27:11
*/

#ifndef TEST2_PARALLEL_PHASE_VOLTAGES_H_
#define TEST2_PARALLEL_PHASE_VOLTAGES_H_

#define  IPCore_Reset_test2_parallel_phase_voltages                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_test2_parallel_phase_voltages                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_test2_parallel_phase_voltages             0x8  //contains unique IP timestamp (yymmddHHMM): 2210101327
#define  theta_el_offset_AXI_Data_test2_parallel_phase_voltages     0x100  //data register for Inport theta_el_offset_AXI
#define  u_dc_link_voltage_AXI_Data_test2_parallel_phase_voltages   0x104  //data register for Inport u_dc_link_voltage_AXI

#endif /* TEST2_PARALLEL_PHASE_VOLTAGES_H_ */
