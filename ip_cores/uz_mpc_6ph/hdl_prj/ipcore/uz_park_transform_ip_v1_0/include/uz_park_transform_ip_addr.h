/*
 * File Name:         hdl_prj\ipcore\uz_park_transform_ip_v1_0\include\uz_park_transform_ip_addr.h
 * Description:       C Header File
 * Created:           2022-10-12 15:32:42
*/

#ifndef UZ_PARK_TRANSFORM_IP_H_
#define UZ_PARK_TRANSFORM_IP_H_

#define  IPCore_Reset_uz_park_transform_ip               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_park_transform_ip              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_park_transform_ip           0x8  //contains unique IP timestamp (yymmddHHMM): 2210121532
#define  factor_angle_el_AXI_Data_uz_park_transform_ip   0x100  //data register for Inport factor_angle_el_AXI
#define  offset_angle_el_AXI_Data_uz_park_transform_ip   0x104  //data register for Inport offset_angle_el_AXI
#define  y1_AXI_Data_uz_park_transform_ip                0x108  //data register for Outport y1_AXI
#define  y2_AXI_Data_uz_park_transform_ip                0x10C  //data register for Outport y2_AXI

#endif /* UZ_PARK_TRANSFORM_IP_H_ */
