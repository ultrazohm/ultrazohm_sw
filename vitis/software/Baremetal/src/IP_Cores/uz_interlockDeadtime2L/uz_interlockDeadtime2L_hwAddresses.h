/*
 * File Name:         /home/ts/Dokumente/ultrazohm_testbench/ultrazohm_test/ultrazohm_sw/ip_cores/InterlockDeadtime2L/ipcore/uz_interlockDeadtime2L_v1_0/include/uz_interlockDeadtime2L_addr.h
 * Description:       C Header File
 * Created:           2021-04-22 14:35:13
*/

#ifndef UZ_INTERLOCKDEADTIME2L_H_
#define UZ_INTERLOCKDEADTIME2L_H_

#define  IPCore_Reset_uz_interlockDeadtime2L                   0x0U  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_uz_interlockDeadtime2L                  0x4U  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_uz_interlockDeadtime2L               0x8U  //contains unique IP timestamp (yymmddHHMM): 2104221435
#define  axi_fb_InverseBotSwitch_Data_uz_interlockDeadtime2L   0x100U  //data register for Outport axi_fb_InverseBotSwitch
#define  axi_fb_DelayCycles_Data_uz_interlockDeadtime2L        0x104U  //data register for Outport axi_fb_DelayCycles
#define  axi_fb_enable_Data_uz_interlockDeadtime2L             0x108U  //data register for Outport axi_fb_enable
#define  axi_InverseBotSwitch_Data_uz_interlockDeadtime2L      0x10CU  //data register for Inport axi_InverseBotSwitch
#define  axi_EnableOutput_Data_uz_interlockDeadtime2L          0x110U  //data register for Inport axi_EnableOutput
#define  axi_DelayCycles_Data_uz_interlockDeadtime2L           0x114U  //data register for Inport axi_DelayCycles

#endif /* UZ_INTERLOCKDEADTIME2L_H_ */
