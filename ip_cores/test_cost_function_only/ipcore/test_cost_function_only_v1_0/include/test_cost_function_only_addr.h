/*
 * File Name:         C:\ultrazohm_sw\ip_cores\test_cost_function_only\ipcore\test_cost_function_only_v1_0\include\test_cost_function_only_addr.h
 * Description:       C Header File
 * Created:           2022-10-12 14:29:56
*/

#ifndef TEST_COST_FUNCTION_ONLY_H_
#define TEST_COST_FUNCTION_ONLY_H_

#define  IPCore_Reset_test_cost_function_only       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_test_cost_function_only      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_test_cost_function_only   0x8  //contains unique IP timestamp (yymmddHHMM): 2210121429
#define  id_ref_AXI_Data_test_cost_function_only    0x100  //data register for Inport id_ref_AXI
#define  iq_ref_AXI_Data_test_cost_function_only    0x104  //data register for Inport iq_ref_AXI
#define  ix_ref_AXI_Data_test_cost_function_only    0x108  //data register for Inport ix_ref_AXI
#define  iy_ref_AXI_Data_test_cost_function_only    0x10C  //data register for Inport iy_ref_AXI

#endif /* TEST_COST_FUNCTION_ONLY_H_ */
