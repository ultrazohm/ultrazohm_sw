/*
 * File Name:         hdl_prj\ipcore\UZ_D_GaN_Inverter_v1_1\include\UZ_D_GaN_Inverter_addr.h
 * Description:       C Header File
 * Created:           2022-02-02 11:26:41
*/

#ifndef UZ_D_GAN_INVERTER_H_
#define UZ_D_GAN_INVERTER_H_

#define  IPCore_Reset_UZ_D_GaN_Inverter                   0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_UZ_D_GaN_Inverter                  0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_UZ_D_GaN_Inverter               0x8  //contains unique IP timestamp (yymmddHHMM): 2202021126
#define  AXI_en_in_Data_UZ_D_GaN_Inverter                 0x100  //data register for Inport AXI_en_in
#define  AXI_Gan_Temp_1_period_Data_UZ_D_GaN_Inverter     0x104  //data register for Outport AXI_Gan_Temp_1_period
#define  AXI_Gan_Temp_1_hightime_Data_UZ_D_GaN_Inverter   0x108  //data register for Outport AXI_Gan_Temp_1_hightime
#define  AXI_Gan_Temp_1_lowtime_Data_UZ_D_GaN_Inverter    0x10C  //data register for Outport AXI_Gan_Temp_1_lowtime
#define  AXI_Gan_Temp_1_dutycyc_Data_UZ_D_GaN_Inverter    0x110  //data register for Outport AXI_Gan_Temp_1_dutycyc
#define  AXI_Gan_Temp_2_period_Data_UZ_D_GaN_Inverter     0x114  //data register for Outport AXI_Gan_Temp_2_period
#define  AXI_Gan_Temp_2_hightime_Data_UZ_D_GaN_Inverter   0x118  //data register for Outport AXI_Gan_Temp_2_hightime
#define  AXI_Gan_Temp_2_lowtime_Data_UZ_D_GaN_Inverter    0x11C  //data register for Outport AXI_Gan_Temp_2_lowtime
#define  AXI_Gan_Temp_2_dutycyc_Data_UZ_D_GaN_Inverter    0x120  //data register for Outport AXI_Gan_Temp_2_dutycyc
#define  AXI_Gan_Temp_3_period_Data_UZ_D_GaN_Inverter     0x124  //data register for Outport AXI_Gan_Temp_3_period
#define  AXI_Gan_Temp_3_hightime_Data_UZ_D_GaN_Inverter   0x128  //data register for Outport AXI_Gan_Temp_3_hightime
#define  AXI_Gan_Temp_3_lowtime_Data_UZ_D_GaN_Inverter    0x12C  //data register for Outport AXI_Gan_Temp_3_lowtime
#define  AXI_Gan_Temp_3_dutycyc_Data_UZ_D_GaN_Inverter    0x130  //data register for Outport AXI_Gan_Temp_3_dutycyc
#define  AXI_Gan_Temp_4_period_Data_UZ_D_GaN_Inverter     0x134  //data register for Outport AXI_Gan_Temp_4_period
#define  AXI_Gan_Temp_4_hightime_Data_UZ_D_GaN_Inverter   0x138  //data register for Outport AXI_Gan_Temp_4_hightime
#define  AXI_Gan_Temp_4_lowtime_Data_UZ_D_GaN_Inverter    0x13C  //data register for Outport AXI_Gan_Temp_4_lowtime
#define  AXI_Gan_Temp_4_dutycyc_Data_UZ_D_GaN_Inverter    0x140  //data register for Outport AXI_Gan_Temp_4_dutycyc
#define  AXI_Gan_Temp_5_period_Data_UZ_D_GaN_Inverter     0x144  //data register for Outport AXI_Gan_Temp_5_period
#define  AXI_Gan_Temp_5_hightime_Data_UZ_D_GaN_Inverter   0x148  //data register for Outport AXI_Gan_Temp_5_hightime
#define  AXI_Gan_Temp_5_lowtime_Data_UZ_D_GaN_Inverter    0x14C  //data register for Outport AXI_Gan_Temp_5_lowtime
#define  AXI_Gan_Temp_5_dutycyc_Data_UZ_D_GaN_Inverter    0x150  //data register for Outport AXI_Gan_Temp_5_dutycyc
#define  AXI_Gan_Temp_6_period_Data_UZ_D_GaN_Inverter     0x154  //data register for Outport AXI_Gan_Temp_6_period
#define  AXI_Gan_Temp_6_hightime_Data_UZ_D_GaN_Inverter   0x158  //data register for Outport AXI_Gan_Temp_6_hightime
#define  AXI_Gan_Temp_6_lowtime_Data_UZ_D_GaN_Inverter    0x15C  //data register for Outport AXI_Gan_Temp_6_lowtime
#define  AXI_Gan_Temp_6_dutycyc_Data_UZ_D_GaN_Inverter    0x160  //data register for Outport AXI_Gan_Temp_6_dutycyc
#define  AXI_GaN_FAULT_Data_UZ_D_GaN_Inverter             0x164  //data register for Outport AXI_GaN_FAULT
#define  AXI_GaN_OC_Data_UZ_D_GaN_Inverter                0x178  //data register for Outport AXI_GaN_OC
#define  AXI_I_DIAG_Data_UZ_D_GaN_Inverter                0x190  //data register for Outport AXI_I_DIAG
#define  AXI_PWM_Enable_Data_UZ_D_GaN_Inverter            0x1A0  //data register for Inport AXI_PWM_Enable

#endif /* UZ_D_GAN_INVERTER_H_ */
