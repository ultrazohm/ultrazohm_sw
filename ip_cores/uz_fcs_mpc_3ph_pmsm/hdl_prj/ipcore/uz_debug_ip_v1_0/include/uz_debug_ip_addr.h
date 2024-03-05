/*
 * File Name:         hdl_prj\ipcore\uz_debug_ip_v1_0\include\uz_debug_ip_addr.h
 * Description:       C Header File
 * Created:           2023-10-04 15:04:24
*/

#ifndef UZ_DEBUG_IP_H_
#define UZ_DEBUG_IP_H_

#define  IPCore_Reset_uz_debug_ip             0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_debug_ip            0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_debug_ip         0x8  //contains unique IP timestamp (yymmddHHMM): 2310041504
#define  in0_AXI_Data_uz_debug_ip             0x100  //data register for Inport in0_AXI
#define  in0_AXI1_Data_uz_debug_ip            0x104  //data register for Inport in0_AXI1
#define  in0_AXI2_Data_uz_debug_ip            0x108  //data register for Inport in0_AXI2
#define  in0_AXI3_Data_uz_debug_ip            0x10C  //data register for Inport in0_AXI3
#define  in0_AXI4_Data_uz_debug_ip            0x110  //data register for Inport in0_AXI4
#define  in0_AXI5_Data_uz_debug_ip            0x114  //data register for Inport in0_AXI5
#define  in0_AXI6_Data_uz_debug_ip            0x118  //data register for Inport in0_AXI6
#define  in0_AXI7_Data_uz_debug_ip            0x11C  //data register for Inport in0_AXI7
#define  in0_AXI8_Data_uz_debug_ip            0x120  //data register for Inport in0_AXI8
#define  real_or_debug_AXI_Data_uz_debug_ip   0x124  //data register for Inport real_or_debug_AXI

#endif /* UZ_DEBUG_IP_H_ */
