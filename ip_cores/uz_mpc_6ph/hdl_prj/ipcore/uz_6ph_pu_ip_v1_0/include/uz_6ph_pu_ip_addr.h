/*
 * File Name:         hdl_prj\ipcore\uz_6ph_pu_ip_v1_0\include\uz_6ph_pu_ip_addr.h
 * Description:       C Header File
 * Created:           2022-08-23 11:32:49
*/

#ifndef UZ_6PH_PU_IP_H_
#define UZ_6PH_PU_IP_H_

#define  IPCore_Reset_uz_6ph_pu_ip        0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_6ph_pu_ip       0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_6ph_pu_ip    0x8  //contains unique IP timestamp (yymmddHHMM): 2208231132
#define  index_select_Data_uz_6ph_pu_ip   0x100  //data register for Inport index_select
#define  index_AXI_Data_uz_6ph_pu_ip      0x104  //data register for Inport index_AXI
#define  pu_ud_AXI_Data_uz_6ph_pu_ip      0x108  //data register for Outport pu_ud_AXI
#define  pu_uq_AXI_Data_uz_6ph_pu_ip      0x10C  //data register for Outport pu_uq_AXI
#define  pu_ux_AXI_Data_uz_6ph_pu_ip      0x110  //data register for Outport pu_ux_AXI
#define  pu_uy_AXI_Data_uz_6ph_pu_ip      0x114  //data register for Outport pu_uy_AXI

#endif /* UZ_6PH_PU_IP_H_ */
