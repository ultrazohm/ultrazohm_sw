/*
 * File Name:         hdl_prj\ipcore\uz_dutycyclemeas_ip_v1_0\include\uz_dutycyclemeas_ip_addr.h
 * Description:       C Header File
 * Created:           2025-10-24 14:26:21
*/

#ifndef UZ_DUTYCYCLEMEAS_IP_H_
#define UZ_DUTYCYCLEMEAS_IP_H_

#define  IPCore_Reset_uz_dutycyclemeas_ip        0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_dutycyclemeas_ip       0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_dutycyclemeas_ip    0x8  //contains unique IP timestamp (yymmddHHMM): 2510241426
#define  AXI_period_Data_uz_dutycyclemeas_ip     0x100  //data register for Outport AXI_period
#define  AXI_hightime_Data_uz_dutycyclemeas_ip   0x104  //data register for Outport AXI_hightime
#define  AXI_lowtime_Data_uz_dutycyclemeas_ip    0x108  //data register for Outport AXI_lowtime

#endif /* UZ_DUTYCYCLEMEAS_IP_H_ */
