/*
 * File Name:         C:\ultrazohm_sw\ip_cores\uz_axi_mytestIP\hdl_prj\ipcore\uz_axi_my_ip_v1_0\include\uz_axi_my_ip_addr.h
 * Description:       C Header File
 * Created:           2022-05-12 15:37:14
*/

#ifndef UZ_AXI_MY_IP_H_
#define UZ_AXI_MY_IP_H_

#define  IPCore_Reset_uz_axi_my_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_axi_my_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_axi_my_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2205121537
#define  A_int32_Data_uz_axi_my_ip       0x100  //data register for Inport A_int32
#define  B_int32_Data_uz_axi_my_ip       0x104  //data register for Inport B_int32
#define  A_uint32_Data_uz_axi_my_ip      0x108  //data register for Inport A_uint32
#define  B_uint32_Data_uz_axi_my_ip      0x10C  //data register for Inport B_uint32
#define  In6_Data_uz_axi_my_ip           0x110  //data register for Inport In6
#define  In5_Data_uz_axi_my_ip           0x114  //data register for Inport In5
#define  C_int32_Data_uz_axi_my_ip       0x118  //data register for Outport C_int32
#define  C_uint32_Data_uz_axi_my_ip      0x11C  //data register for Outport C_uint32
#define  Out3_Data_uz_axi_my_ip          0x120  //data register for Outport Out3

#endif /* UZ_AXI_MY_IP_H_ */
