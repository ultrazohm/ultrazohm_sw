/*
 * File Name:         C:\ultrazohm_sw\ip_cores\test_min_cost_function\ipcore\test_parallel_min_cost_function_v1_0\include\test_parallel_min_cost_function_addr.h
 * Description:       C Header File
 * Created:           2022-10-10 17:48:15
*/

#ifndef TEST_PARALLEL_MIN_COST_FUNCTION_H_
#define TEST_PARALLEL_MIN_COST_FUNCTION_H_

#define  IPCore_Reset_test_parallel_min_cost_function       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_test_parallel_min_cost_function      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_test_parallel_min_cost_function   0x8  //contains unique IP timestamp (yymmddHHMM): 2210101748
#define  J_AXI_Data_test_parallel_min_cost_function         0x100  //data register for Outport J_AXI
#define  Index_AXI_Data_test_parallel_min_cost_function     0x104  //data register for Outport Index_AXI

#endif /* TEST_PARALLEL_MIN_COST_FUNCTION_H_ */
