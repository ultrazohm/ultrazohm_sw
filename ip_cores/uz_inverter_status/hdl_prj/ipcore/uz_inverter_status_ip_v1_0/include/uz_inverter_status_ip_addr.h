/*
 * File Name:         hdl_prj\ipcore\uz_inverter_status_ip_v1_0\include\uz_inverter_status_ip_addr.h
 * Description:       C Header File
 * Created:           2025-10-29 14:24:01
*/

#ifndef UZ_INVERTER_STATUS_IP_H_
#define UZ_INVERTER_STATUS_IP_H_

#define  IPCore_Reset_uz_inverter_status_ip         0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_inverter_status_ip        0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_inverter_status_ip     0x8  //contains unique IP timestamp (yymmddHHMM): 2510291423
#define  AXI_RDY_Data_uz_inverter_status_ip         0x100  //data register for Outport AXI_RDY
#define  EN_GateDriver_Data_uz_inverter_status_ip   0x104  //data register for Inport EN_GateDriver
#define  AXI_FLT_Data_uz_inverter_status_ip         0x164  //data register for Outport AXI_FLT

#endif /* UZ_INVERTER_STATUS_IP_H_ */
