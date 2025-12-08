/*
 * File Name:         C:\Ultrazohm\ultrazohm_sw\ip_cores\SS_debug_block\ipcore\SS_Debug_v1_0\include\SS_Debug_addr.h
 * Description:       C Header File
 * Created:           2025-12-02 18:40:35
*/

#ifndef SS_DEBUG_H_
#define SS_DEBUG_H_

#define  IPCore_Reset_SS_Debug       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_SS_Debug      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_SS_Debug   0x8  //contains unique IP timestamp (yymmddHHMM): 2512021839: 2512021840
#define  AXI_SS0_in_Data_SS_Debug    0x100  //data register for Inport AXI_SS0_in
#define  AXI_SS1_in_Data_SS_Debug    0x104  //data register for Inport AXI_SS1_in
#define  AXI_SS2_in_Data_SS_Debug    0x108  //data register for Inport AXI_SS2_in
#define  AXI_SS3_in_Data_SS_Debug    0x10C  //data register for Inport AXI_SS3_in
#define  AXI_SS0_out_Data_SS_Debug   0x110  //data register for Outport AXI_SS0_out
#define  AXI_SS1_out_Data_SS_Debug   0x114  //data register for Outport AXI_SS1_out
#define  AXI_SS2_out_Data_SS_Debug   0x118  //data register for Outport AXI_SS2_out
#define  AXI_SS3_out_Data_SS_Debug   0x11C  //data register for Outport AXI_SS3_out

#endif /* SS_DEBUG_H_ */
