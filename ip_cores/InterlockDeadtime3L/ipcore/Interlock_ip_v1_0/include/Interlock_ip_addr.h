/*
 * File Name:         C:\Ultrazohm\ultrazohm_sw\ip_cores\InterlockDeadtime3L\ipcore\Interlock_ip_v1_0\include\Interlock_ip_addr.h
 * Description:       C Header File
 * Created:           2026-01-13 14:47:35
*/

#ifndef INTERLOCK_IP_H_
#define INTERLOCK_IP_H_

#define  IPCore_Reset_Interlock_ip                     0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_Interlock_ip                    0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_Interlock_ip                 0x8  //contains unique IP timestamp (yymmddHHMM): 2601131447
#define  AXI_DelayCycles_readback_Data_Interlock_ip    0x100  //data register for Outport AXI_DelayCycles_readback
#define  AXI_DelayCycles_Data_Interlock_ip             0x104  //data register for Inport AXI_DelayCycles
#define  AXI_Type_Data_Interlock_ip                    0x108  //data register for Inport AXI_Type
#define  AXI_EnableOutput_Data_Interlock_ip            0x10C  //data register for Inport AXI_EnableOutput
#define  AXI_Type_readback_Data_Interlock_ip           0x110  //data register for Outport AXI_Type_readback
#define  AXI_EnableOutput_readback_Data_Interlock_ip   0x114  //data register for Outport AXI_EnableOutput_readback

#endif /* INTERLOCK_IP_H_ */
