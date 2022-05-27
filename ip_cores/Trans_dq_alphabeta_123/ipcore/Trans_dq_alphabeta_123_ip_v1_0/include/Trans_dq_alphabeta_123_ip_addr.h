/*
 * File Name:         C:\ultrazohm_sw\ip_cores\Trans_dq_alphabeta_123\Simulation\ipcore\Trans_dq_alphabeta_123_ip_v1_0\include\Trans_dq_alphabeta_123_ip_addr.h
 * Description:       C Header File
 * Created:           2022-05-27 15:32:32
*/

#ifndef TRANS_DQ_ALPHABETA_123_IP_H_
#define TRANS_DQ_ALPHABETA_123_IP_H_

#define  IPCore_Reset_Trans_dq_alphabeta_123_ip            0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Trans_dq_alphabeta_123_ip           0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Trans_dq_alphabeta_123_ip        0x8  //contains unique IP timestamp (yymmddHHMM): 2205271532
#define  theta_offset_AXI_Data_Trans_dq_alphabeta_123_ip   0x100  //data register for Inport theta_offset_AXI
#define  Id_ref_AXI_Data_Trans_dq_alphabeta_123_ip         0x108  //data register for Inport Id_ref_AXI
#define  Iq_ref_AXI_Data_Trans_dq_alphabeta_123_ip         0x110  //data register for Inport Iq_ref_AXI
#define  i1_AXI_Data_Trans_dq_alphabeta_123_ip             0x114  //data register for Outport i1_AXI
#define  ialpha_AXI_Data_Trans_dq_alphabeta_123_ip         0x118  //data register for Outport ialpha_AXI
#define  ibeta_AXI_Data_Trans_dq_alphabeta_123_ip          0x11C  //data register for Outport ibeta_AXI
#define  i2_AXI_Data_Trans_dq_alphabeta_123_ip             0x120  //data register for Outport i2_AXI
#define  i3_AXI_Data_Trans_dq_alphabeta_123_ip             0x124  //data register for Outport i3_AXI

#endif /* TRANS_DQ_ALPHABETA_123_IP_H_ */
