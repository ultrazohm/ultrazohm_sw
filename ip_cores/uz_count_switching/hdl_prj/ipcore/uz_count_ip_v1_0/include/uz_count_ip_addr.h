/*
 * File Name:         C:\utrazohm_sw_2\ultrazohm_sw\ip_cores\uz_count_switching\hdl_prj\ipcore\uz_count_ip_v1_0\include\uz_count_ip_addr.h
 * Description:       C Header File
 * Created:           2026-03-19 09:20:18
*/

#ifndef UZ_COUNT_IP_H_
#define UZ_COUNT_IP_H_

#define  IPCore_Reset_uz_count_ip              0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_count_ip             0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_count_ip          0x8  //contains unique IP timestamp (yymmddHHMM): 2603190920
#define  count_out_0_AXI_Data_uz_count_ip      0x100  //data register for Outport count_out_0_AXI
#define  count_out_1_AXI_Data_uz_count_ip      0x104  //data register for Outport count_out_1_AXI
#define  count_out_2_AXI_Data_uz_count_ip      0x108  //data register for Outport count_out_2_AXI
#define  count_out_3_AXI_Data_uz_count_ip      0x10C  //data register for Outport count_out_3_AXI
#define  count_out_4_AXI_Data_uz_count_ip      0x110  //data register for Outport count_out_4_AXI
#define  count_out_5_AXI_Data_uz_count_ip      0x114  //data register for Outport count_out_5_AXI
#define  count_out_6_AXI_Data_uz_count_ip      0x118  //data register for Outport count_out_6_AXI
#define  count_out_7_AXI_Data_uz_count_ip      0x11C  //data register for Outport count_out_7_AXI
#define  count_out_8_AXI_Data_uz_count_ip      0x120  //data register for Outport count_out_8_AXI
#define  count_out_sum_AXI1_Data_uz_count_ip   0x124  //data register for Outport count_out_sum_AXI1
#define  bResetAXI_Data_uz_count_ip            0x128  //data register for Inport bResetAXI

#endif /* UZ_COUNT_IP_H_ */
