/*
 * File Name:         hdl_prj\ipcore\uz_park_t_ip_v1_0\include\uz_park_t_ip_addr.h
 * Description:       C Header File
 * Created:           2022-08-11 11:31:08
*/

#ifndef UZ_PARK_T_IP_H_
#define UZ_PARK_T_IP_H_

#define  IPCore_Reset_uz_park_t_ip               0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_park_t_ip              0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_park_t_ip           0x8  //contains unique IP timestamp (yymmddHHMM): 2208111131
#define  factor_angle_el_AXI_Data_uz_park_t_ip   0x100  //data register for Inport factor_angle_el_AXI
#define  y1_AXI_Data_uz_park_t_ip                0x104  //data register for Outport y1_AXI
#define  y2_AXI_Data_uz_park_t_ip                0x108  //data register for Outport y2_AXI

#endif /* UZ_PARK_T_IP_H_ */
