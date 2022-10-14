/*
 * File Name:         C:\ultrazohm_sw\ip_cores\test_phase_voltages_without_delays\ipcore\test_phase_voltages_without_delays_v1_0\include\test_phase_voltages_without_delays_addr.h
 * Description:       C Header File
 * Created:           2022-10-14 14:00:58
*/

#ifndef TEST_PHASE_VOLTAGES_WITHOUT_DELAYS_H_
#define TEST_PHASE_VOLTAGES_WITHOUT_DELAYS_H_

#define  IPCore_Reset_test_phase_voltages_without_delays                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_test_phase_voltages_without_delays                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_test_phase_voltages_without_delays             0x8  //contains unique IP timestamp (yymmddHHMM): 2210141400
#define  theta_el_offset_AXI_Data_test_phase_voltages_without_delays     0x100  //data register for Inport theta_el_offset_AXI
#define  u_dc_link_voltage_AXI_Data_test_phase_voltages_without_delays   0x104  //data register for Inport u_dc_link_voltage_AXI

#endif /* TEST_PHASE_VOLTAGES_WITHOUT_DELAYS_H_ */
