/*
 * File Name:         C:\ultrazohm_sw\ip_cores\test_delay_compensation\ipcore\test2_parallel_delay_compensation_6Phase_v1_0\include\test2_parallel_delay_compensation_6Phase_addr.h
 * Description:       C Header File
 * Created:           2022-10-10 12:10:33
*/

#ifndef TEST2_PARALLEL_DELAY_COMPENSATION_6PHASE_H_
#define TEST2_PARALLEL_DELAY_COMPENSATION_6PHASE_H_

#define  IPCore_Reset_test2_parallel_delay_compensation_6Phase                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_test2_parallel_delay_compensation_6Phase                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_test2_parallel_delay_compensation_6Phase             0x8  //contains unique IP timestamp (yymmddHHMM): 2210101210
#define  psiPM_AXI_Data_test2_parallel_delay_compensation_6Phase               0x100  //data register for Inport psiPM_AXI
#define  Lq_AXI_Data_test2_parallel_delay_compensation_6Phase                  0x104  //data register for Inport Lq_AXI
#define  Ld_AXI_Data_test2_parallel_delay_compensation_6Phase                  0x108  //data register for Inport Ld_AXI
#define  Rs_AXI_Data_test2_parallel_delay_compensation_6Phase                  0x10C  //data register for Inport Rs_AXI
#define  SampleTime_div_Ld_AXI_Data_test2_parallel_delay_compensation_6Phase   0x110  //data register for Inport SampleTime_div_Ld_AXI
#define  pole_pairs_AXI_Data_test2_parallel_delay_compensation_6Phase          0x114  //data register for Inport pole_pairs_AXI
#define  SampleTime_div_Lq_AXI_Data_test2_parallel_delay_compensation_6Phase   0x118  //data register for Inport SampleTime_div_Lq_AXI
#define  SampleTime_div_Lx_AXI_Data_test2_parallel_delay_compensation_6Phase   0x11C  //data register for Inport SampleTime_div_Lx_AXI
#define  SampleTime_div_Ly_AXI_Data_test2_parallel_delay_compensation_6Phase   0x120  //data register for Inport SampleTime_div_Ly_AXI
#define  id_k_1_AXI_Data_test2_parallel_delay_compensation_6Phase              0x14C  //data register for Outport id_k_1_AXI
#define  iq_k_1_AXI_Data_test2_parallel_delay_compensation_6Phase              0x150  //data register for Outport iq_k_1_AXI
#define  ix_k_1_AXI_Data_test2_parallel_delay_compensation_6Phase              0x154  //data register for Outport ix_k_1_AXI
#define  iy_k_1_AXI_Data_test2_parallel_delay_compensation_6Phase              0x158  //data register for Outport iy_k_1_AXI

#endif /* TEST2_PARALLEL_DELAY_COMPENSATION_6PHASE_H_ */
