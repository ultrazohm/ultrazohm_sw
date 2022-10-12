/*
 * File Name:         C:\ultrazohm_sw\ip_cores\test_prediction_only\ipcore\test_parallel_prediction_only_v1_0\include\test_parallel_prediction_only_addr.h
 * Description:       C Header File
 * Created:           2022-10-12 10:08:38
*/

#ifndef TEST_PARALLEL_PREDICTION_ONLY_H_
#define TEST_PARALLEL_PREDICTION_ONLY_H_

#define  IPCore_Reset_test_parallel_prediction_only                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_test_parallel_prediction_only                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_test_parallel_prediction_only             0x8  //contains unique IP timestamp (yymmddHHMM): 2210121008
#define  Lq_AXI_Data_test_parallel_prediction_only                  0x100  //data register for Inport Lq_AXI
#define  Ld_AXI_Data_test_parallel_prediction_only                  0x104  //data register for Inport Ld_AXI
#define  SampleTime_div_Ld_AXI_Data_test_parallel_prediction_only   0x108  //data register for Inport SampleTime_div_Ld_AXI
#define  SampleTime_div_Lq_AXI_Data_test_parallel_prediction_only   0x10C  //data register for Inport SampleTime_div_Lq_AXI
#define  SampleTime_div_Lx_AXI_Data_test_parallel_prediction_only   0x110  //data register for Inport SampleTime_div_Lx_AXI
#define  pole_pairs_AXI_Data_test_parallel_prediction_only          0x114  //data register for Inport pole_pairs_AXI
#define  SampleTime_div_Ly_AXI_Data_test_parallel_prediction_only   0x118  //data register for Inport SampleTime_div_Ly_AXI
#define  Rs_AXI_Data_test_parallel_prediction_only                  0x11C  //data register for Inport Rs_AXI
#define  psiPM_AXI_Data_test_parallel_prediction_only               0x120  //data register for Inport psiPM_AXI

#endif /* TEST_PARALLEL_PREDICTION_ONLY_H_ */
