/*
 * File Name:         /home/ts/Dokumente/00_Master_Arbeit/1_Diss/ultrazohm_sw/ip_cores/interlock_deadtime/ipcore/interlock_ip_v1_0/include/interlock_ip_addr.h
 * Description:       C Header File
 * Created:           2020-12-13 16:28:15
*/

#ifndef INTERLOCK_IP_H_
#define INTERLOCK_IP_H_

#define  IPCore_Reset_interlock_ip                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_interlock_ip                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_interlock_ip               0x8  //contains unique IP timestamp (yymmddHHMM): 2012131628
#define  AXI_fb_InverseBotSwitch_Data_interlock_ip   0x100  //data register for Outport AXI_fb_InverseBotSwitch
#define  AXI_fb_DelayCycles_Data_interlock_ip        0x104  //data register for Outport AXI_fb_DelayCycles
#define  AXI_fb_enable_Data_interlock_ip             0x108  //data register for Outport AXI_fb_enable
#define  AXI_InverseBotSwitch_Data_interlock_ip      0x10C  //data register for Inport AXI_InverseBotSwitch
#define  AXI_EnableOutput_Data_interlock_ip          0x110  //data register for Inport AXI_EnableOutput
#define  AXI_DelayCycles_Data_interlock_ip           0x114  //data register for Inport AXI_DelayCycles

#endif /* INTERLOCK_IP_H_ */
