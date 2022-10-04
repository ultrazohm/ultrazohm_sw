/*
 * File Name:         hdl_prj\ipcore\uz_6_ph_voltages_ip_v1_0\include\uz_6_ph_voltages_ip_addr.h
 * Description:       C Header File
 * Created:           2022-10-04 11:16:09
*/

#ifndef UZ_6_PH_VOLTAGES_IP_H_
#define UZ_6_PH_VOLTAGES_IP_H_

#define  IPCore_Reset_uz_6_ph_voltages_ip        0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_6_ph_voltages_ip       0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_6_ph_voltages_ip    0x8  //contains unique IP timestamp (yymmddHHMM): 2210041116
#define  index_select_Data_uz_6_ph_voltages_ip   0x100  //data register for Inport index_select
#define  index_AXI_Data_uz_6_ph_voltages_ip      0x104  //data register for Inport index_AXI
#define  pu_vd_AXI_Data_uz_6_ph_voltages_ip      0x108  //data register for Outport pu_vd_AXI
#define  pu_vq_AXI_Data_uz_6_ph_voltages_ip      0x10C  //data register for Outport pu_vq_AXI
#define  pu_vx_AXI_Data_uz_6_ph_voltages_ip      0x110  //data register for Outport pu_vx_AXI
#define  pu_vy_AXI_Data_uz_6_ph_voltages_ip      0x114  //data register for Outport pu_vy_AXI

#endif /* UZ_6_PH_VOLTAGES_IP_H_ */
