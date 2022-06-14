#pragma once 

#define  IPCore_Reset_Trans_123_alphabeta_dq_V12_ip            0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Trans_123_alphabeta_dq_V12_ip           0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Trans_123_alphabeta_dq_V12_ip        0x8U  //contains unique IP timestamp (yymmddHHMM): 2206031045
#define  theta_offset_AXI_Data_Trans_123_alphabeta_dq_V12_ip   0x100U  //data register for Inport theta_offset_AXI
#define  id_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x104U  //data register for Outport id_AXI
#define  iq_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x108U  //data register for Outport iq_AXI
#define  i1_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x10CU  //data register for Outport i1_AXI
#define  i2_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x110U  //data register for Outport i2_AXI
#define  i3_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x114U  //data register for Outport i3_AXI
#define  ialpha_AXI_Data_Trans_123_alphabeta_dq_V12_ip         0x118U  //data register for Outport ialpha_AXI
#define  ibeta_AXI_Data_Trans_123_alphabeta_dq_V12_ip          0x11CU  //data register for Outport ibeta_AXI
