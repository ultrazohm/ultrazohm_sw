#pragma once

#define  IPCore_Reset_parallel_8_delay_compensation                 0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_parallel_8_delay_compensation                0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_parallel_8_delay_compensation             0x8  //contains unique IP timestamp (yymmddHHMM): 2210181218
#define  psiPM_AXI_Data_parallel_8_delay_compensation               0x100  //data register for Inport psiPM_AXI
#define  Lq_AXI_Data_parallel_8_delay_compensation                  0x104  //data register for Inport Lq_AXI
#define  Ld_AXI_Data_parallel_8_delay_compensation                  0x108  //data register for Inport Ld_AXI
#define  Rs_AXI_Data_parallel_8_delay_compensation                  0x10C  //data register for Inport Rs_AXI
#define  SampleTime_div_Ld_AXI_Data_parallel_8_delay_compensation   0x110  //data register for Inport SampleTime_div_Ld_AXI
#define  pole_pairs_AXI_Data_parallel_8_delay_compensation          0x114  //data register for Inport pole_pairs_AXI
#define  SampleTime_div_Lq_AXI_Data_parallel_8_delay_compensation   0x118  //data register for Inport SampleTime_div_Lq_AXI
#define  SampleTime_div_Lx_AXI_Data_parallel_8_delay_compensation   0x11C  //data register for Inport SampleTime_div_Lx_AXI
#define  SampleTime_div_Ly_AXI_Data_parallel_8_delay_compensation   0x120  //data register for Inport SampleTime_div_Ly_AXI
#define  id_k_1_AXI_Data_parallel_8_delay_compensation              0x14C  //data register for Outport id_k_1_AXI
#define  iq_k_1_AXI_Data_parallel_8_delay_compensation              0x150  //data register for Outport iq_k_1_AXI
#define  ix_k_1_AXI_Data_parallel_8_delay_compensation              0x154  //data register for Outport ix_k_1_AXI
#define  iy_k_1_AXI_Data_parallel_8_delay_compensation              0x158  //data register for Outport iy_k_1_AXI
