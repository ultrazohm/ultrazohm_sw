/*
 * File Name:         C:\Ultrazohm\ultrazohm_sw\ip_cores\SS_debug_block\ipcore\Subsystem_ip_v1_0\include\Subsystem_ip_addr.h
 * Description:       C Header File
 * Created:           2025-12-02 18:39:40
*/

#ifndef SUBSYSTEM_IP_H_
#define SUBSYSTEM_IP_H_

#define  IPCore_Reset_Subsystem_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Subsystem_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Subsystem_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2512021839
#define  AXI_SS0_in_Data_Subsystem_ip    0x100  //data register for Inport AXI_SS0_in
#define  AXI_SS1_in_Data_Subsystem_ip    0x104  //data register for Inport AXI_SS1_in
#define  AXI_SS2_in_Data_Subsystem_ip    0x108  //data register for Inport AXI_SS2_in
#define  AXI_SS3_in_Data_Subsystem_ip    0x10C  //data register for Inport AXI_SS3_in
#define  AXI_SS0_out_Data_Subsystem_ip   0x110  //data register for Outport AXI_SS0_out
#define  AXI_SS1_out_Data_Subsystem_ip   0x114  //data register for Outport AXI_SS1_out
#define  AXI_SS2_out_Data_Subsystem_ip   0x118  //data register for Outport AXI_SS2_out
#define  AXI_SS3_out_Data_Subsystem_ip   0x11C  //data register for Outport AXI_SS3_out

#endif /* SUBSYSTEM_IP_H_ */
