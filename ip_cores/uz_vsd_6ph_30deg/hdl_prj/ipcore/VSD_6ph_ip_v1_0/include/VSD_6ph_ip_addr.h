/*
 * File Name:         hdl_prj\ipcore\VSD_6ph_ip_v1_0\include\VSD_6ph_ip_addr.h
 * Description:       C Header File
 * Created:           2022-08-09 10:30:59
*/

#ifndef VSD_6PH_IP_H_
#define VSD_6PH_IP_H_

#define  IPCore_Reset_VSD_6ph_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_VSD_6ph_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_VSD_6ph_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2208091030
#define  alpha_AXI_Data_VSD_6ph_ip     0x100  //data register for Outport alpha_AXI
#define  beta_AXI_Data_VSD_6ph_ip      0x104  //data register for Outport beta_AXI
#define  y_AXI_Data_VSD_6ph_ip         0x108  //data register for Outport y_AXI
#define  x_AXI_Data_VSD_6ph_ip         0x10C  //data register for Outport x_AXI
#define  z1_AXI_Data_VSD_6ph_ip        0x110  //data register for Outport z1_AXI
#define  z2_AXI_Data_VSD_6ph_ip        0x114  //data register for Outport z2_AXI

#endif /* VSD_6PH_IP_H_ */
