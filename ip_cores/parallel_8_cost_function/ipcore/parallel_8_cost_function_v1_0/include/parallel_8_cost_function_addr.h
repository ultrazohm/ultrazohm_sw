/*
 * File Name:         C:\ultrazohm_sw\ip_cores\parallel_8_cost_function\ipcore\parallel_8_cost_function_v1_0\include\parallel_8_cost_function_addr.h
 * Description:       C Header File
 * Created:           2022-10-18 09:53:50
*/

#ifndef PARALLEL_8_COST_FUNCTION_H_
#define PARALLEL_8_COST_FUNCTION_H_

#define  IPCore_Reset_parallel_8_cost_function       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_8_cost_function      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_8_cost_function   0x8  //contains unique IP timestamp (yymmddHHMM): 2210180953
#define  id_ref_AXI_Data_parallel_8_cost_function    0x100  //data register for Inport id_ref_AXI
#define  iq_ref_AXI_Data_parallel_8_cost_function    0x104  //data register for Inport iq_ref_AXI
#define  ix_ref_AXI_Data_parallel_8_cost_function    0x108  //data register for Inport ix_ref_AXI
#define  iy_ref_AXI_Data_parallel_8_cost_function    0x10C  //data register for Inport iy_ref_AXI

#endif /* PARALLEL_8_COST_FUNCTION_H_ */
