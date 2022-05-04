/*
 * File Name:         C:\ultrazohm_sw\ip_cores\Trans_123_dq_V12_ip\Simulation\ipcore\Trans_123_alphabeta_dq_V12_ip_v1_0\include\Trans_123_alphabeta_dq_V12_ip_addr.h
 * Description:       C Header File
 * Created:           2022-05-03 14:00:48
*/

#ifndef TRANS_123_ALPHABETA_DQ_V12_IP_H_
#define TRANS_123_ALPHABETA_DQ_V12_IP_H_

#define  IPCore_Reset_Trans_123_alphabeta_dq_V12_ip            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Trans_123_alphabeta_dq_V12_ip           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Trans_123_alphabeta_dq_V12_ip        0x8  //contains unique IP timestamp (yymmddHHMM): 2205031400
#define  theta_offset_AXI_Data_Trans_123_alphabeta_dq_V12_ip   0x100  //data register for Inport theta_offset_AXI
#define  id_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x104  //data register for Outport id_AXI
#define  iq_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x108  //data register for Outport iq_AXI
#define  i1_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x10C  //data register for Outport i1_AXI
#define  i2_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x110  //data register for Outport i2_AXI
#define  i3_AXI_Data_Trans_123_alphabeta_dq_V12_ip             0x114  //data register for Outport i3_AXI
#define  ialpha_AXI_Data_Trans_123_alphabeta_dq_V12_ip         0x118  //data register for Outport ialpha_AXI
#define  ibeta_AXI_Data_Trans_123_alphabeta_dq_V12_ip          0x11C  //data register for Outport ibeta_AXI

#endif /* TRANS_123_ALPHABETA_DQ_V12_IP_H_ */
